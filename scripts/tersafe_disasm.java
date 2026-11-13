// Ghidra headless post-script (Java). Dumps raw disassembly windows around
// known self-defense string-xref addresses, since OLLVM control-flow
// flattening makes the decompiler prune these blocks as "unreachable".
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class tersafe_disasm extends GhidraScript {

    static final String[] TARGETS = {
        "00364da4", "00364e78", "00364eec", "00364fc0",
        "00365550", "00365624",
    };
    static final int BEFORE = 25;
    static final int AFTER = 15;

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = args.length > 0 ? args[0] : "tersafe_disasm_out.txt";
        Listing listing = currentProgram.getListing();
        List<String> lines = new ArrayList<>();

        for (String h : TARGETS) {
            Address target = currentProgram.getAddressFactory().getAddress(h);
            lines.add("\n=== WINDOW AROUND 0x" + h + " ===");

            // walk backwards BEFORE instructions
            List<Instruction> before = new ArrayList<>();
            Instruction ins = listing.getInstructionContaining(target);
            if (ins == null) {
                lines.add("NO INSTRUCTION at 0x" + h);
                continue;
            }
            Instruction cur = ins;
            for (int i = 0; i < BEFORE && cur != null; i++) {
                before.add(0, cur);
                cur = listing.getInstructionBefore(cur.getMinAddress());
            }
            for (Instruction b : before) {
                String marker = b.getMinAddress().equals(ins.getMinAddress()) ? " <== TARGET" : "";
                lines.add(b.getAddress() + "  " + b.toString() + marker);
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
