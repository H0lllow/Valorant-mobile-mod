// Ghidra headless post-script (Java). Finds self-defense strings via defined
// data (not raw byte scanning) and reports Ghidra's own computed references
// to them, which respect real control/data flow (unlike the standalone
// Python ADRP/ADD scanner, which produced false positives on this OLLVM binary).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class tersafe_strxref extends GhidraScript {

    static final String[] HINTS = {
        "set_inline_hook_error", "ms_set_inlie_hook",
        "inline_hook_opcode_dismatch", "ms_hook_opcode",
        "ms_mmap", "mmap_fialed",
        "TracerPid", "safe_ptrace:",
        "check_ext_emu_feature", "root_alert",
        "debugger:", "check_state:",
    };

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = args.length > 0 ? args[0] : "tersafe_strxref_out.txt";
        List<String> lines = new ArrayList<>();
        ReferenceManager refmgr = currentProgram.getReferenceManager();
        FunctionManager fm = currentProgram.getFunctionManager();

        DataIterator it = currentProgram.getListing().getDefinedData(true);
        while (it.hasNext()) {
            Data d = it.next();
            if (!d.hasStringValue()) continue;
            Object val = d.getValue();
            if (val == null) continue;
            String s = val.toString();
            for (String h : HINTS) {
                if (s.contains(h)) {
                    Address a = d.getAddress();
                    lines.add("\nSTRING \"" + s + "\" @ " + a);
                    List<Reference> refs = new ArrayList<>();
                    for (Reference r : refmgr.getReferencesTo(a)) refs.add(r);
                    lines.add("  refs: " + refs.size());
                    for (Reference r : refs) {
                        Address from = r.getFromAddress();
                        Function fn = fm.getFunctionContaining(from);
                        lines.add("   <- " + from + "  in " + (fn != null ? fn.getName() + "@" + fn.getEntryPoint() : "?"));
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
