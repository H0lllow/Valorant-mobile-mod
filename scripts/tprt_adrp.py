import pyghidra
pyghidra.start()

BIN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtprt.so"
PROJ = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\ghidra_proj"
OUT = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\tprt_adrp.txt"
# string addresses found by byte search (tprt_hints.py)
TARGETS = {
    "incorrect header check": 0x002202ae,
    "incorrect data check": 0x002202d5,
    "Zip-bug": 0x0022054a,
    "magisk": 0x00222217,
    "debuggable": 0x0021feca,
}

with pyghidra.open_program(BIN, PROJ, "tprt", analyze=False) as flat_api:
    program = flat_api.getCurrentProgram()
    from ghidra.app.decompiler import DecompInterface
    from ghidra.util.task import ConsoleTaskMonitor

    fm = program.getFunctionManager()
    listing = program.getListing()
    mon = ConsoleTaskMonitor()
    decomp = DecompInterface()
    decomp.openProgram(program)

    pages = {}
    for name, off in TARGETS.items():
        pages.setdefault(off & ~0xFFF, []).append((name, off))

    cands = {}
    lines = []
    ins_iter = listing.getInstructions(True)
    for ins in ins_iter:
        if not ins.getMnemonicString().lower().startswith("adrp"):
            continue
        for i in range(ins.getNumOperands()):
            for obj in ins.getOpObjects(i):
                try:
                    v = obj.getOffset()
                except Exception:
                    continue
                if v in pages:
                    fn = fm.getFunctionContaining(ins.getAddress())
                    label = ", ".join(n for n, _ in pages[v])
                    lines.append("ADRP %s -> page %X (%s) in %s" % (
                        ins.getAddress(), v, label, fn.getName() if fn else "NOFUNC"))
                    if fn:
                        cands[fn.getEntryPoint().toString()] = fn

    lines.append("\n=== DECOMPILED %d CANDIDATE FUNCTIONS ===" % len(cands))
    for key in sorted(cands.keys()):
        fn = cands[key]
        lines.append("\n===== %s @ %s =====" % (fn.getName(), key))
        res = decomp.decompileFunction(fn, 60, mon)
        if res and res.decompileCompleted():
            lines.append(res.getDecompiledFunction().getC())
        else:
            lines.append("// decompile failed")

    with open(OUT, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    print("WROTE", OUT, len(lines))
