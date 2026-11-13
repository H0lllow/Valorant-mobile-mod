// Ghidra headless post-script (Java, Jython/PyGhidra unavailable in Ghidra 12.2 setup).
// Decompiles functions containing known self-defense addresses, plus their
// direct callers, to understand the anti-inline-hook detection routine.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public class tersafe_find extends GhidraScript {

    // corrected via Ghidra's own ReferenceManager (tersafe_strxref.java); the
    // earlier Python ADRP/ADD scanner was off by +0x100000 (wrong page base).
    static final String[] TARGET_HEX = {
        "0056080c", "00560284", "00560d04",  // sibling checks ORed with FUN_00560190 in the detector
        "0057b724",  // action taken when any check trips
    };

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = args.length > 0 ? args[0] : "tersafe_out.txt";

        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager refmgr = currentProgram.getReferenceManager();

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        List<String> lines = new ArrayList<>();
        lines.add("=== PROGRAM: " + currentProgram.getName() + "  base=" + currentProgram.getImageBase() + " ===");

        Set<Address> seen = new LinkedHashSet<>();
        List<Function> targetFuncs = new ArrayList<>();
        for (String h : TARGET_HEX) {
            Address addr = currentProgram.getAddressFactory().getAddress(h);
            if (addr == null) {
                lines.add("bad addr " + h);
                continue;
            }
            Function fn = fm.getFunctionContaining(addr);
            if (fn == null) {
                lines.add("NO FUNCTION containing 0x" + h);
                continue;
            }
            Address ep = fn.getEntryPoint();
            if (!seen.contains(ep)) {
                seen.add(ep);
                targetFuncs.add(fn);
                lines.add("addr 0x" + h + " -> function " + fn.getName() + " @ " + ep + " (size " + fn.getBody().getNumAddresses() + ")");
            } else {
                lines.add("addr 0x" + h + " -> function " + fn.getName() + " @ " + ep + " (dup)");
            }
        }

        lines.add("\n--- " + targetFuncs.size() + " unique target functions ---");

        List<Function> callerFuncs = new ArrayList<>();
        for (Function fn : targetFuncs) {
            Address ep = fn.getEntryPoint();
            Set<Function> callers = new LinkedHashSet<>();
            for (Reference r : refmgr.getReferencesTo(ep)) {
                Function caller = fm.getFunctionContaining(r.getFromAddress());
                if (caller != null && !caller.getEntryPoint().equals(ep)) {
                    callers.add(caller);
                }
            }
            lines.add("\nCallers of " + fn.getName() + " @ " + ep + ": " + callers.size());
            for (Function c : callers) {
                lines.add("   <- " + c.getName() + " @ " + c.getEntryPoint());
                if (!seen.contains(c.getEntryPoint())) {
                    seen.add(c.getEntryPoint());
                    callerFuncs.add(c);
                }
            }
        }

        List<Function> allFuncs = new ArrayList<>(targetFuncs);
        allFuncs.addAll(callerFuncs);
        lines.add("\n=== DECOMPILING " + allFuncs.size() + " FUNCTIONS ===");

        for (Function fn : allFuncs) {
            lines.add("\n===== " + fn.getName() + " @ " + fn.getEntryPoint() + " (size " + fn.getBody().getNumAddresses() + " bytes) =====");
            try {
                DecompileResults res = decomp.decompileFunction(fn, 90, monitor);
                if (res != null && res.decompileCompleted()) {
                    lines.add(res.getDecompiledFunction().getC());
                } else {
                    lines.add("// decompile failed: " + (res != null ? res.getErrorMessage() : "null result"));
                }
            } catch (Exception e) {
                lines.add("// error: " + e);
            }
        }

        try (FileWriter f = new FileWriter(outPath)) {
            for (String l : lines) {
                f.write(l);
                f.write("\n");
            }
        }
        println("WROTE " + outPath + " (" + lines.size() + " lines, " + allFuncs.size() + " funcs)");
    }
}
