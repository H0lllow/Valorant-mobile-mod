# Ghidra headless post-script (Jython) for libtersafe.so.
# Decompiles functions containing known self-defense addresses, plus their
# direct callers, to understand the anti-inline-hook detection routine.
import re
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.address import Address

args = getScriptArgs()
out_path = args[0] if args else "tersafe_out.txt"

# known addresses from Python xref scan (file vaddr, hex, no prefix)
TARGET_HEX = [
    "001ab6f0", "001ab748",           # check_ext_emu_feature xrefs
    "001cd7f8", "001cd834",           # root_alert xrefs
    "001e5b70", "001e5bd4",           # check_state / debugger xrefs
    "00364da4", "00364e78", "00364eec", "00364fc0",  # inline-hook self-defense cluster
    "00365550", "00365624",           # mmap_fialed / ms_mmap
]

fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
refmgr = currentProgram.getReferenceManager()
addrFactory = currentProgram.getAddressFactory()

decomp = DecompInterface()
decomp.openProgram(currentProgram)
monitor = ConsoleTaskMonitor()

lines = []
def emit(s):
    lines.append(s)

emit("=== PROGRAM: %s  base=%s ===" % (currentProgram.getName(), currentProgram.getImageBase()))

seen_funcs = set()
target_funcs = []
for h in TARGET_HEX:
    try:
        addr = addrFactory.getAddress(h)
    except Exception as e:
        emit("bad addr %s: %s" % (h, e))
        continue
    fn = fm.getFunctionContaining(addr)
    if fn is None:
        emit("NO FUNCTION containing 0x%s" % h)
        continue
    ep = fn.getEntryPoint()
    if ep not in seen_funcs:
        seen_funcs.add(ep)
        target_funcs.append(fn)
        emit("addr 0x%s -> function %s @ %s (size %d)" % (h, fn.getName(), ep, fn.getBody().getNumAddresses()))
    else:
        emit("addr 0x%s -> function %s @ %s (dup)" % (h, fn.getName(), ep))

emit("\n--- %d unique target functions ---" % len(target_funcs))

# for each target function, also find its direct callers (1 level up)
caller_funcs = []
for fn in target_funcs:
    ep = fn.getEntryPoint()
    callers = set()
    for r in refmgr.getReferencesTo(ep):
        caller = fm.getFunctionContaining(r.getFromAddress())
        if caller and caller.getEntryPoint() != ep:
            callers.add(caller)
    emit("\nCallers of %s @ %s: %d" % (fn.getName(), ep, len(callers)))
    for c in callers:
        emit("   <- %s @ %s" % (c.getName(), c.getEntryPoint()))
        if c.getEntryPoint() not in seen_funcs:
            seen_funcs.add(c.getEntryPoint())
            caller_funcs.append(c)

all_funcs = target_funcs + caller_funcs
emit("\n=== DECOMPILING %d FUNCTIONS ===" % len(all_funcs))

for fn in all_funcs:
    emit("\n===== %s @ %s (size %d bytes) =====" % (fn.getName(), fn.getEntryPoint(), fn.getBody().getNumAddresses()))
    try:
        res = decomp.decompileFunction(fn, 90, monitor)
        if res and res.decompileCompleted():
            emit(res.getDecompiledFunction().getC())
        else:
            emit("// decompile failed: %s" % (res.getErrorMessage() if res else "null result"))
    except Exception as e:
        emit("// error: %s" % e)

with open(out_path, "w") as f:
    f.write("\n".join(lines))
print("WROTE %s (%d lines, %d funcs)" % (out_path, len(lines), len(all_funcs)))
