#!/usr/bin/env python3
# Root-track: patch libtersafe.so on disk so every process (main, :plugin,
# :xg_vip_service) and every relaunch loads the neutralized version, no
# Frida timing/spawn-gating race involved.
# Targets are Ghidra-displayed addresses (Ghidra assigns a synthetic
# 0x100000 image base for this ET_DYN lib; real ELF vaddr = ghidra_addr -
# 0x100000, verified by confirming the bytes there decode as real AArch64
# function prologues, e.g. "sub sp,sp,#.." / "stp x.., [sp,..]"):
#   0x559c3c FUN_00559c3c - the 4-check self-defense OR-gate
#   0x57b724 FUN_0057b724 - shared violation-report/action fn (34 callers)
# Patch: overwrite each function's first instruction with AArch64 RET
# (0xD65F03C0, bytes C0 03 5F D6) so they return immediately as a no-op.
import struct
import sys

SRC = "research/libs/libtersafe.so"
OUT = "research/libs/libtersafe_patched.so"
GHIDRA_IMAGE_BASE = 0x100000
TARGETS_VADDR = [a - GHIDRA_IMAGE_BASE for a in (0x559c3c, 0x57b724)]
RET = bytes([0xC0, 0x03, 0x5F, 0xD6])


def file_offset_for_vaddr(data, vaddr):
    assert data[:4] == b"\x7fELF"
    e_phoff = struct.unpack_from("<Q", data, 0x20)[0]
    e_phentsize = struct.unpack_from("<H", data, 0x36)[0]
    e_phnum = struct.unpack_from("<H", data, 0x38)[0]
    for i in range(e_phnum):
        o = e_phoff + i * e_phentsize
        p_type = struct.unpack_from("<I", data, o)[0]
        if p_type != 1:  # PT_LOAD
            continue
        p_offset = struct.unpack_from("<Q", data, o + 0x08)[0]
        p_vaddr = struct.unpack_from("<Q", data, o + 0x10)[0]
        p_filesz = struct.unpack_from("<Q", data, o + 0x20)[0]
        if p_vaddr <= vaddr < p_vaddr + p_filesz:
            return p_offset + (vaddr - p_vaddr)
    raise ValueError("vaddr 0x%x not in any PT_LOAD segment" % vaddr)


def main():
    data = bytearray(open(SRC, "rb").read())
    for vaddr in TARGETS_VADDR:
        off = file_offset_for_vaddr(data, vaddr)
        before = data[off:off + 4].hex()
        data[off:off + 4] = RET
        print("patched vaddr 0x%x -> file offset 0x%x  before=%s after=%s" %
              (vaddr, off, before, data[off:off + 4].hex()))
    open(OUT, "wb").write(data)
    print("wrote", OUT, len(data), "bytes")


if __name__ == "__main__":
    sys.exit(main())
