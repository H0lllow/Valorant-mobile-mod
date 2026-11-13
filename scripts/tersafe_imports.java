// Ghidra headless post-script (Java). Lists imported/external functions whose
// name suggests memory-scan / anti-hook detection (mmap, mprotect, ptrace,
// /proc reads), and their callers, to find the real RWX-scan routine
// (the error-string dispatcher chase turned out to be generic SDK telemetry).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class tersafe_imports extends GhidraScript {

    static final String[] NAME_HINTS = {
        "mmap", "mprotect", "ptrace", "open", "read", "pread", "fopen", "fgets",
        "madvise", "mincore", "msync",
    };

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = args.length > 0 ? args[0] : "tersafe_imports_out.txt";
        List<String> lines = new ArrayList<>();
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager refmgr = currentProgram.getReferenceManager();

        for (Function fn : fm.getExternalFunctions()) {
            String nm = fn.getName();
            for (String h : NAME_HINTS) {
                if (nm.equals(h) || nm.startsWith(h + "@") || nm.contains("_" + h) ) {
                    lines.add("\nIMPORT " + nm + " @ " + fn.getEntryPoint());
                }
            }
        }

        lines.add("\n--- thunks/PLT referencing these imports ---");
        for (Function fn : fm.getFunctions(true)) {
            if (!fn.isThunk()) continue;
            Function thunked = fn.getThunkedFunction(true);
            if (thunked == null) continue;
            String nm = thunked.getName();
            for (String h : NAME_HINTS) {
                if (nm.equals(h) || nm.contains("_" + h)) {
                    Address ep = fn.getEntryPoint();
                    List<Reference> refs = new ArrayList<>();
                    for (Reference r : refmgr.getReferencesTo(ep)) refs.add(r);
                    lines.add("\nTHUNK " + fn.getName() + " @ " + ep + " -> " + nm + "  (" + refs.size() + " callers)");
                    for (Reference r : refs) {
                        Address from = r.getFromAddress();
                        Function caller = fm.getFunctionContaining(from);
                        lines.add("   <- " + from + "  in " + (caller != null ? caller.getName() + "@" + caller.getEntryPoint() : "?"));
                    }
                }
            }
        }

        try (FileWriter f = new FileWriter(outPath)) {
            for (String l : lines) {
                f.write(l);
                f.write("\n");
            }
        }
        println("WROTE " + outPath + " (" + lines.size() + " lines)");
    }
}
