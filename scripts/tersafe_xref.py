#!/usr/bin/env python3
# ARM64 xref finder for libtersafe.so: scans .text for ADRP(+ADD) pairs whose
# computed target equals a given string's virtual address. No Ghidra needed.
import struct

LIB = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\libs\libtersafe.so"
HINTS = [
    b"/proc/%d", b"%lx-%lx %c%c%c%c %x %x:%x %u %s",
    b"set_inline_hook_error", b"ms_set_inlie_hook",
    b"inline_hook_opcode_dismatch", b"ms_hook_opcode",
    b"ms_mmap", b"mmap_fialed",
    b"TracerPid", b"safe_ptrace:%d:%d",
    b"/proc/%d/task/%d/status", b"/proc/%d/task",
    b"check_ext_emu_feature", b"root_alert",
    b"debugger:%s", b"check_state:%s",
]

b = open(LIB, "rb").read()
assert b[:4] == b"\x7fELF"
e_shoff = struct.unpack_from("<Q", b, 0x28)[0]
e_shentsize = struct.unpack_from("<H", b, 0x3a)[0]
e_shnum = struct.unpack_from("<H", b, 0x3c)[0]
e_shstrndx = struct.unpack_from("<H", b, 0x3e)[0]
shstr_off = struct.unpack_from("<Q", b, e_shoff + e_shstrndx*e_shentsize + 0x18)[0]

secs = {}
for i in range(e_shnum):
    o = e_shoff + i*e_shentsize
    name_idx = struct.unpack_from("<I", b, o)[0]
    sh_addr = struct.unpack_from("<Q", b, o+0x10)[0]
    sh_off = struct.unpack_from("<Q", b, o+0x18)[0]
    sh_size = struct.unpack_from("<Q", b, o+0x20)[0]
    end = b.index(b"\x00", shstr_off+name_idx)
    nm = b[shstr_off+name_idx:end].decode("latin1")
    secs[nm] = (sh_addr, sh_off, sh_size)

text_addr, text_off, text_size = secs[".text"]

def file_to_vaddr_of_string(pat):
    hits = []
    start = 0
    while True:
        idx = b.find(pat, start)
        if idx < 0:
            break
        for nm, (a, o, s) in secs.items():
            if o <= idx < o+s and a != 0:
                hits.append(a + (idx - o))
        start = idx + 1
    return hits

def sxt(v, bits):
    if v & (1 << (bits-1)):
        return v - (1 << bits)
    return v

targets = {}
for h in HINTS:
    for va in file_to_vaddr_of_string(h):
        targets[va] = h.decode("latin1")[:60]

print("TARGET STRINGS (vaddr): %d found" % len(targets))
for va, s in sorted(targets.items()):
    print("  %08x  %s" % (va, s))

adrp_reg = {}
n = text_size // 4
found = 0
print("\nXREFS (code vaddr -> string):")
for i in range(n):
    off = text_off + i*4
    word = struct.unpack_from("<I", b, off)[0]
    va = text_addr + i*4
    if (word & 0x9f000000) == 0x90000000:
        rd = word & 0x1f
        immlo = (word >> 29) & 0x3
        immhi = (word >> 5) & 0x7ffff
        imm = sxt((immhi << 2) | immlo, 21)
        page = (va & ~0xFFF) + (imm << 12)
        adrp_reg[rd] = (page, va)
    elif (word & 0xff800000) == 0x91000000:
        rn = (word >> 5) & 0x1f
        rd = word & 0x1f
        sh = (word >> 22) & 0x1
        imm12 = (word >> 10) & 0xfff
        val = imm12 << (12 if sh else 0)
        if rn in adrp_reg:
            page, at = adrp_reg[rn]
            tgt = page + val
            if tgt in targets:
                print("  %08x: ADRP@%08x + ADD -> %08x  (%s)" % (va, at, tgt, targets[tgt]))
                found += 1
    # also catch ADRP + LDR (str loaded as pointer, e.g. for a table) imm9 scaled
    elif (word & 0x3b000000) == 0x39000000 or (word & 0xffc00000) == 0xf9400000:
        rn = (word >> 5) & 0x1f
        if rn in adrp_reg and (word & 0xffc00000) == 0xf9400000:
            imm12 = (word >> 10) & 0xfff
            page, at = adrp_reg[rn]
            tgt = page + imm12*8
            if tgt in targets:
                print("  %08x: ADRP@%08x + LDR -> %08x  (%s)" % (va, at, tgt, targets[tgt]))
                found += 1
print("TOTAL XREFS:", found)
