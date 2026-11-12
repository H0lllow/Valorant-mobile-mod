import pyghidra
pyghidra.start()
BIN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtprt.so"
PROJ = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\ghidra_proj"
with pyghidra.open_program(BIN, PROJ, "tprt", analyze=False) as flat_api:
    p = flat_api.getCurrentProgram()
    fm = p.getFunctionManager()
    print("PROGRAM", p.getName(), "LANG", p.getLanguageID())
    print("MIN", p.getMinAddress(), "MAX", p.getMaxAddress())
    print("FUNCTIONS", fm.getFunctionCount())
    print("MEMORY_BLOCKS", p.getMemory().getNumAddresses())
    n = 0
    s = 0
    for d in p.getListing().getDefinedData(True):
        n += 1
        if d.hasStringValue():
            s += 1
    print("DEFINED_DATA", n, "STRINGS", s)
    print("SYMBOLS", p.getSymbolTable().getNumSymbols())
