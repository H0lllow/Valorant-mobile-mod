// Ghidra headless post-script (Java). Dumps raw disassembly around the libtprt
// thread start routine (file vaddr 0xf1008 = Ghidra 0x1f1008, base 0x100000).
// Also reports the nearest defined function start before the target, since
// Ghidra did not create a function at the exact address.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class tprt_disasm extends GhidraScript {

    static final String TARGET = "001f1008";
    static final int BEFORE = 40;
    static final int AFTER = 60;

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = args.length > 0 ? args[0] : "tprt_disasm_out.txt";
        Listing listing = currentProgram.getListing();
        List<String> lines = new ArrayList<>();

        Address target = currentProgram.getAddressFactory().getAddress(TARGET);
        lines.add("=== TARGET " + TARGET + " ===");

        // nearest function starting at or before the target
        Function prev = null;
        for (Function f : currentProgram.getFunctionManager().getFunctionsNoStubs(true)) {
            if (f.getEntryPoint().compareTo(target) <= 0) {
                if (prev == null || f.getEntryPoint().compareTo(prev.getEntryPoint()) > 0) {
                    prev = f;
                }
            }
        }
        if (prev != null) {
            lines.add("nearest defined function at/before target: " + prev.getName()
                + " @ " + prev.getEntryPoint() + " size " + prev.getBody().getNumAddresses());
        } else {
            lines.add("no defined function at/before target");
        }

        Instruction ins = listing.getInstructionContaining(target);
        if (ins == null) {
            lines.add("no instruction at target (undefined bytes)");
            // still dump raw bytes so we can see what is there
            byte[] raw = new byte[64];
            currentProgram.getMemory().getBytes(target, raw);
            StringBuilder sb = new StringBuilder();
            for (byte b : raw) sb.append(String.format("%02x ", b & 0xff));
            lines.add("raw bytes: " + sb.toString().trim());
        } else {
            List<Instruction> before = new ArrayList<>();
            Instruction cur = ins;
            for (int i = 0; i < BEFORE && cur != null; i++) {
                before.add(0, cur);
                cur = listing.getInstructionBefore(cur.getMinAddress());
            }
            for (Instruction b : before) {
                String mark = b.getMinAddress().equals(ins.getMinAddress()) ? " <== TARGET" : "";
                lines.add(b.getAddress() + "  " + b.toString() + mark);
            }
            cur = listing.getInstructionAfter(ins.getMinAddress());
            for (int i = 0; i < AFTER && cur != null; i++) {
                lines.add(cur.getAddress() + "  " + cur.toString());
                cur = listing.getInstructionAfter(cur.getMinAddress());
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
