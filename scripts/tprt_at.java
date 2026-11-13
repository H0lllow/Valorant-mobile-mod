// Ghidra headless post-script (Java). Reports the function containing each
// given address, plus its direct callers. Used to name the libtprt thread
// start routine seen via Frida pthread_create (libtprt.so+0xf1008).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class tprt_at extends GhidraScript {

    static final String[] TARGETS = {
        "000f1008", "001f1008",   // raw ELF vaddr and Ghidra base-0x100000 form
    };

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = args.length > 0 ? args[0] : "tprt_at_out.txt";
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager refmgr = currentProgram.getReferenceManager();
        List<String> lines = new ArrayList<>();
        lines.add("PROGRAM " + currentProgram.getName() + " base=" + currentProgram.getImageBase());

        for (String h : TARGETS) {
            Address a = currentProgram.getAddressFactory().getAddress(h);
            if (a == null) {
                lines.add("bad address " + h);
                continue;
            }
            Function fn = fm.getFunctionContaining(a);
            if (fn == null) {
                lines.add(h + " -> no function contains it");
                continue;
            }
            lines.add(h + " -> " + fn.getName() + " @ " + fn.getEntryPoint()
                + " size " + fn.getBody().getNumAddresses());
            for (Reference r : refmgr.getReferencesTo(fn.getEntryPoint())) {
                Function caller = fm.getFunctionContaining(r.getFromAddress());
                lines.add("   called/ref from " + r.getFromAddress()
                    + " in " + (caller != null ? caller.getName() : "?"));
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
