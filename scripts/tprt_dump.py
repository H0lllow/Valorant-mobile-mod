# Opens the already-analyzed libtprt.so in the Ghidra project via PyGhidra and dumps
# decompiled functions that reference hint strings or abort/exit/ptrace calls.
# Usage: python tprt_dump.py <out.txt>
import sys
import pyghidra

pyghidra.start()

PROJ_DIR = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\ghidra_proj"
PROJ_NAME = "tprt"
BIN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtprt.so"
OUT = sys.argv[1] if len(sys.argv) > 1 else r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\tprt_ghidra.txt"

STR_HINTS = ["incorrect header check", "incorrect data check", "Zip-bug", "magisk",
             "debuggable", "cert", "crc", "inline_hook", "TracerPid", "safe_ptrace"]
IMPORT_HINTS = ["_exit", "exit", "abort", "kill", "ptrace", "raise", "pthread_exit",
                "android_set_abort_message"]

with pyghidra.open_program(BIN, PROJ_DIR, PROJ_NAME, analyze=False) as flat_api:
    program = flat_api.getCurrentProgram()

    from ghidra.app.decompiler import DecompInterface
    from ghidra.util.task import ConsoleTaskMonitor

    fm = program.getFunctionManager()
    listing = program.getListing()
    refmgr = program.getReferenceManager()
    decomp = DecompInterface()
    decomp.openProgram(program)
    mon = ConsoleTaskMonitor()

    lines = ["=== PROGRAM %s ===" % program.getName()]
    targets = {}

    lines.append("\n--- STRING XREFS ---")
    for d in listing.getDefinedData(True):
        if not d.hasStringValue():
            continue
        v = str(d.getValue())
        if not any(h.lower() in v.lower() for h in STR_HINTS):
            continue
        for r in refmgr.getReferencesTo(d.getAddress()):
            fn = fm.getFunctionContaining(r.getFromAddress())
            if fn:
                targets[fn.getEntryPoint().toString()] = fn
                lines.append("STR '%s' <- %s" % (v[:60], fn.getName()))

    lines.append("\n--- CALLERS OF ABORT/EXIT/PTRACE ---")
    for fn in fm.getFunctions(True):
        if fn.getName().lstrip("_") in IMPORT_HINTS:
            for r in refmgr.getReferencesTo(fn.getEntryPoint()):
                caller = fm.getFunctionContaining(r.getFromAddress())
                if caller:
                    targets[caller.getEntryPoint().toString()] = caller
                    lines.append("CALL %s <- %s @ %s" % (fn.getName(), caller.getName(), r.getFromAddress()))

    lines.append("\n--- DECOMPILED (%d functions) ---" % len(targets))
    for key in sorted(targets.keys()):
        fn = targets[key]
        lines.append("\n===== %s @ %s =====" % (fn.getName(), key))
        res = decomp.decompileFunction(fn, 60, mon)
        if res and res.decompileCompleted():
            lines.append(res.getDecompiledFunction().getC())
        else:
            lines.append("// decompile failed")

    with open(OUT, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    print("WROTE", OUT, len(lines))
