# Ghidra headless post-script (Jython).
# Finds functions referencing key strings/imports and dumps their decompiled C.
# Usage: analyzeHeadless <proj_dir> <proj> -import <lib.so> -postScript ghidra_find.py <out.txt>
# or on an already-imported program with -process.

import re
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

args = getScriptArgs()
out_path = args[0] if args else "ghidra_out.txt"

# strings/imports of interest for anti-tamper triage
STR_HINTS = [
    "incorrect header check", "incorrect data check", "Zip-bug",
    "magisk", "debuggable", "cert_md5", "crc", "code_size",
    "inline_hook", "root_alert", "emulator", "TracerPid",
    "safe_ptrace", "abort", "wait_verify", "sec_signature",
    "ano_ignore_detect", "ano_cert_md5", "check_state",
]
IMPORT_HINTS = ["_exit", "exit", "abort", "kill", "ptrace", "raise",
                "android_set_abort_message", "pthread_exit"]

fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
st = currentProgram.getSymbolTable()
refmgr = currentProgram.getReferenceManager()

decomp = DecompInterface()
decomp.openProgram(currentProgram)
monitor = ConsoleTaskMonitor()

lines = []
def emit(s):
    lines.append(s)

emit("=== PROGRAM: %s ===" % currentProgram.getName())

# 1) find defined strings matching hints, collect functions referencing them
emit("\n--- STRING XREFS ---")
target_funcs = set()
data_it = listing.getDefinedData(True)
count = 0
for d in data_it:
    if not d.hasStringValue():
        continue
    v = str(d.getValue())
    low = v.lower()
    hit = None
    for h in STR_HINTS:
        if h.lower() in low:
            hit = h
            break
    if hit is None:
        continue
    addr = d.getAddress()
    refs = refmgr.getReferencesTo(addr)
    for r in refs:
        fromA = r.getFromAddress()
        fn = fm.getFunctionContaining(fromA)
        if fn:
            target_funcs.add(fn.getEntryPoint())
            emit("STR '%s' @ %s  <- %s (ref @ %s)" % (v[:50], addr, fn.getName(), fromA))
    count += 1
emit("matched %d strings, %d funcs" % (count, len(target_funcs)))

# 2) find calls to dangerous imports
emit("\n--- IMPORT XREFS (abort/exit/kill/ptrace) ---")
for sym in st.getExternalSymbols():
    nm = sym.getName()
    if nm in IMPORT_HINTS:
        for r in refmgr.getReferencesTo(sym.getAddress()):
            fn = fm.getFunctionContaining(r.getFromAddress())
            if fn:
                target_funcs.add(fn.getEntryPoint())
                emit("IMPORT %s <- %s @ %s" % (nm, fn.getName(), r.getFromAddress()))

# also scan thunks/functions by name
for fn in fm.getFunctions(True):
    nm = fn.getName()
    for h in IMPORT_HINTS:
        if nm == h:
            for r in refmgr.getReferencesTo(fn.getEntryPoint()):
                caller = fm.getFunctionContaining(r.getFromAddress())
                if caller:
                    target_funcs.add(caller.getEntryPoint())
                    emit("CALL %s <- %s @ %s" % (nm, caller.getName(), r.getFromAddress()))

# 3) decompile each target function
emit("\n--- DECOMPILED TARGETS (%d) ---" % len(target_funcs))
for ep in sorted(target_funcs, key=lambda a: a.getOffset()):
    fn = fm.getFunctionAt(ep)
    if fn is None:
        continue
    emit("\n===== %s @ %s =====" % (fn.getName(), ep))
    try:
        res = decomp.decompileFunction(fn, 60, monitor)
        if res and res.decompileCompleted():
            emit(res.getDecompiledFunction().getC())
        else:
            emit("// decompile failed")
    except Exception as e:
        emit("// error: %s" % e)

with open(out_path, "w") as f:
    f.write("\n".join(lines))
print("WROTE %s (%d lines)" % (out_path, len(lines)))
