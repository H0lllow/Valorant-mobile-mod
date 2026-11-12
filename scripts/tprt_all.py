import pyghidra
pyghidra.start()

BIN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtprt.so"
PROJ = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\ghidra_proj"
OUT = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\tprt_all.c"

with pyghidra.open_program(BIN, PROJ, "tprt", analyze=False) as flat_api:
    program = flat_api.getCurrentProgram()
    from ghidra.app.decompiler import DecompInterface
    from ghidra.util.task import ConsoleTaskMonitor

    fm = program.getFunctionManager()
    mon = ConsoleTaskMonitor()
    decomp = DecompInterface()
    decomp.openProgram(program)

    count = 0
    with open(OUT, "w", encoding="utf-8") as f:
        for fn in fm.getFunctions(True):
            ep = fn.getEntryPoint()
            f.write("\n// ===== %s @ %s =====\n" % (fn.getName(), ep))
            try:
                res = decomp.decompileFunction(fn, 45, mon)
                if res and res.decompileCompleted():
                    f.write(res.getDecompiledFunction().getC())
                else:
                    f.write("// decompile failed\n")
            except Exception as e:
                f.write("// error %s\n" % e)
            count += 1
    print("WROTE", OUT, count, "functions")
