import pyghidra
pyghidra.start()
BIN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtprt.so"
PROJ = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\ghidra_proj"
with pyghidra.open_program(BIN, PROJ, "tprt", analyze=False) as flat_api:
    p = flat_api.getCurrentProgram()
    fm = p.getFunctionManager()
    refmgr = p.getReferenceManager()
    lst = p.getListing()
    with open(r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\tprt_strings.txt", "w", encoding="utf-8") as f:
        for d in lst.getDefinedData(True):
            if d.hasStringValue():
                refs = list(refmgr.getReferencesTo(d.getAddress()))
                fns = []
                for r in refs:
                    fn = fm.getFunctionContaining(r.getFromAddress())
                    fns.append(fn.getName() if fn else "?")
                f.write("%s | refs=%d | %s | %s\n" % (d.getAddress(), len(refs), str(d.getValue())[:90], ",".join(fns[:5])))
    with open(r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\tprt_funcs.txt", "w", encoding="utf-8") as f:
        for fn in fm.getFunctions(True):
            f.write("%s %s thunk=%s\n" % (fn.getEntryPoint(), fn.getName(), fn.isThunk()))
    print("DONE")
