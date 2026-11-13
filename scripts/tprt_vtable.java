// Ghidra headless post-script (Java). libtprt thread body 0x1f1008 calls
// obj->vtable[2] (vtable slot +0x10). Vtable for the object is stored at
// file 0x23f300 (Ghidra 0x33f300). This dumps the slots, resolves the slot-2
// target, and disassembles it, plus the starter FUN_001f0f94 callers.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class tprt_vtable extends GhidraScript {

    static final int INSTR_AFTER = 70;

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = args.length > 0 ? args[0] : "tprt_vtable_out.txt";
        List<String> lines = new ArrayList<>();
        Listing listing = currentProgram.getListing();
        var mem = currentProgram.getMemory();
        var af = currentProgram.getAddressFactory();

        // 1) vtable slots at Ghidra 0x33f300..0x33f330
        lines.add("=== VTABLE @ 0x33f300 ===");
        // adrp operands in the disassembly are already Ghidra-space addresses
        Address vt = af.getAddress("0023f300");
        for (int i = 0; i < 8; i++) {
            Address slot = vt.add(i * 8L);
            try {
                long val = mem.getLong(slot);
                lines.add("slot[" + i + "] @ " + slot + " = 0x" + Long.toHexString(val));
            } catch (Exception e) {
                lines.add("slot[" + i + "] @ " + slot + " unreadable: " + e);
            }
        }

        // 2) resolve slot 2 and disassemble its target
        try {
            long slot2 = mem.getLong(vt.add(2 * 8L));
            Address tgt = af.getDefaultAddressSpace().getAddress(slot2);
            Function fn = currentProgram.getFunctionManager().getFunctionContaining(tgt);
            lines.add("=== SLOT2 TARGET " + tgt + " ===");
            lines.add("function: " + (fn != null ? fn.getName() + " @ " + fn.getEntryPoint() : "none defined"));
            Instruction ins = listing.getInstructionAt(tgt);
            if (ins == null) {
                ins = listing.getInstructionContaining(tgt);
            }
            if (ins != null) {
                Instruction cur = listing.getInstructionAt(ins.getMinAddress());
                for (int i = 0; i < INSTR_AFTER && cur != null; i++) {
                    lines.add(cur.getAddress() + "  " + cur.toString());
                    cur = listing.getInstructionAfter(cur.getMinAddress());
                }
            } else {
                lines.add("no instructions defined at slot2 target (not disassembled by Ghidra)");
            }
        } catch (Exception e) {
            lines.add("slot2 resolve failed: " + e);
        }

        // 3) who calls the starter FUN_001f0f94
        lines.add("=== CALLERS of FUN_001f0f94 ===");
        Address starter = af.getAddress("001f0f94");
        for (Reference r : currentProgram.getReferenceManager().getReferencesTo(starter)) {
            Function c = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
            lines.add("  <- " + r.getFromAddress() + " in " + (c != null ? c.getName() + "@" + c.getEntryPoint() : "?"));
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
