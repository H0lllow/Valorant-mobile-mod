import pyghidra
pyghidra.start()

BIN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtprt.so"
PROJ = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\ghidra_proj"
OUT = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\tprt_checks.c"

# ELF vaddr xrefs -> Ghidra addr (+0x100000)
ELF_ADDRS = {
    "debuggable_check": 0xbbed8,
    "zip_verify_data":  0xecde8,
    "zip_verify_hdr":   0xecf44,
    "zip_parse":        0xef8ac,
    "magisk_check":     0xf15d8,
}
BASE = 0x100000

with pyghidra.open_program(BIN, PROJ, "tprt", analyze=False) as flat_api:
    program = flat_api.getCurrentProgram()
    from ghidra.app.decompiler import DecompInterface
    from ghidra.util.task import ConsoleTaskMonitor
    from ghidra.app.cmd.function import CreateFunctionCmd

    fm = program.getFunctionManager()
    af = program.getAddressFactory().getDefaultAddressSpace()
    mon = ConsoleTaskMonitor()
    decomp = DecompInterface()
    decomp.openProgram(program)

    lines = []
    done = set()
    for label, elf in ELF_ADDRS.items():
        ga = af.getAddress(elf + BASE)
        fn = fm.getFunctionContaining(ga)
        if fn is None:
            lines.append("\n// %s @ %x : NO FUNCTION, creating" % (label, elf + BASE))
            CreateFunctionCmd(ga).applyTo(program)
            fn = fm.getFunctionContaining(ga)
        if fn is None:
            lines.append("// still no function at %x" % (elf + BASE))
            continue
        key = fn.getEntryPoint().toString()
        lines.append("\n// ===== %s -> func %s @ %s =====" % (label, fn.getName(), fn.getEntryPoint()))
        if key in done:
            lines.append("// (already dumped)")
            continue
        done.add(key)
        res = decomp.decompileFunction(fn, 90, mon)
        if res and res.decompileCompleted():
            lines.append(res.getDecompiledFunction().getC())
        else:
            lines.append("// decompile failed")

    with open(OUT, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    print("WROTE", OUT, len(lines))
