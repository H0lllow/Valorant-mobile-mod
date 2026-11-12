import sys
import pyghidra
pyghidra.start()

BIN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtprt.so"
PROJ = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\ghidra_proj"
OUT = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\tprt_hints.txt"
HINTS = ["incorrect header check", "incorrect data check", "Zip-bug", "magisk",
         "debuggable", "TracerPid", "safe_ptrace", "cert_md5", "inline_hook", "code_size"]

with pyghidra.open_program(BIN, PROJ, "tprt", analyze=False) as flat_api:
    program = flat_api.getCurrentProgram()
    from ghidra.app.decompiler import DecompInterface
    from ghidra.util.task import ConsoleTaskMonitor

    mem = program.getMemory()
    fm = program.getFunctionManager()
    refmgr = program.getReferenceManager()
    mon = ConsoleTaskMonitor()
    decomp = DecompInterface()
    decomp.openProgram(program)

    lines = []
    funcs = {}
    for h in HINTS:
        pat = h.encode("ascii")
        addr = program.getMinAddress()
        found = []
        while addr is not None:
            addr = mem.findBytes(addr, pat, None, True, mon)
            if addr is None:
                break
            found.append(addr)
            addr = addr.add(1)
        for a in found:
            lines.append("HINT '%s' @ %s" % (h, a))
            for r in refmgr.getReferencesTo(a):
                fn = fm.getFunctionContaining(r.getFromAddress())
                if fn:
                    funcs[fn.getEntryPoint().toString()] = fn
                    lines.append("   <- %s @ %s" % (fn.getName(), r.getFromAddress()))
        if not found:
            lines.append("HINT '%s' NOT FOUND" % h)

    lines.append("\n=== DECOMPILED %d FUNCTIONS ===" % len(funcs))
    for key in sorted(funcs.keys()):
        fn = funcs[key]
        lines.append("\n===== %s @ %s =====" % (fn.getName(), key))
        res = decomp.decompileFunction(fn, 60, mon)
        if res and res.decompileCompleted():
            lines.append(res.getDecompiledFunction().getC())
        else:
            lines.append("// decompile failed")

    with open(OUT, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    print("WROTE", OUT, len(lines))
