#!/usr/bin/env python3
# Triage a native .so: ELF sections, strip status, entropy (packing), key strings.
import sys, struct, math, re

def read(path):
    with open(path, "rb") as f:
        return f.read()

def entropy(b):
    if not b:
        return 0.0
    freq = [0]*256
    for x in b:
        freq[x] += 1
    e = 0.0
    n = len(b)
    for c in freq:
        if c:
            p = c/n
            e -= p*math.log2(p)
    return e

def parse_elf(b):
    if b[:4] != b"\x7fELF":
        return None
    is64 = b[4] == 2
    le = b[5] == 1
    end = "<" if le else ">"
    info = {"class": "64" if is64 else "32", "endian": "LE" if le else "BE"}
    if is64:
        e_shoff = struct.unpack_from(end+"Q", b, 0x28)[0]
        e_shentsize = struct.unpack_from(end+"H", b, 0x3a)[0]
        e_shnum = struct.unpack_from(end+"H", b, 0x3c)[0]
        e_shstrndx = struct.unpack_from(end+"H", b, 0x3e)[0]
    else:
        e_shoff = struct.unpack_from(end+"I", b, 0x20)[0]
        e_shentsize = struct.unpack_from(end+"H", b, 0x2e)[0]
        e_shnum = struct.unpack_from(end+"H", b, 0x30)[0]
        e_shstrndx = struct.unpack_from(end+"H", b, 0x32)[0]
    secs = []
    if e_shoff and e_shnum:
        shstr_off = e_shoff + e_shstrndx*e_shentsize
        if is64:
            str_off = struct.unpack_from(end+"Q", b, shstr_off+0x18)[0]
        else:
            str_off = struct.unpack_from(end+"I", b, shstr_off+0x10)[0]
        for i in range(e_shnum):
            o = e_shoff + i*e_shentsize
            name_idx = struct.unpack_from(end+"I", b, o)[0]
            if is64:
                sh_off = struct.unpack_from(end+"Q", b, o+0x18)[0]
                sh_size = struct.unpack_from(end+"Q", b, o+0x20)[0]
            else:
                sh_off = struct.unpack_from(end+"I", b, o+0x10)[0]
                sh_size = struct.unpack_from(end+"I", b, o+0x14)[0]
            end_name = b.index(b"\x00", str_off+name_idx)
            nm = b[str_off+name_idx:end_name].decode("latin1")
            secs.append((nm, sh_off, sh_size))
    info["sections"] = secs
    return info

def strings(b, minlen=5):
    return re.findall(rb"[\x20-\x7e]{%d,}" % minlen, b)

def main():
    path = sys.argv[1]
    b = read(path)
    print(f"FILE {path}  SIZE {len(b)} bytes")
    print(f"OVERALL ENTROPY {entropy(b):.3f} (8.0=fully random/encrypted)")
    info = parse_elf(b)
    if not info:
        print("NOT AN ELF")
        return
    print(f"ELF {info['class']}-bit {info['endian']}")
    secs = info["sections"]
    print(f"SECTIONS: {len(secs)}")
    names = [s[0] for s in secs]
    stripped = ".symtab" not in names
    print(f"STRIPPED: {stripped}  (.symtab {'absent' if stripped else 'present'})")
    for nm, off, size in secs:
        if size > 0 and off+size <= len(b) and nm:
            e = entropy(b[off:off+size])
            flag = "  <== HIGH (packed/encrypted?)" if e > 7.2 and size > 4096 else ""
            print(f"  {nm:20s} off=0x{off:08x} size={size:9d} ent={e:.2f}{flag}")
    # interesting strings
    print("\n--- KEY STRINGS ---")
    pats = [b"sign", b"Sign", b"cert", b"CRC", b"crc", b"integrity", b"tamper",
            b"frida", b"Frida", b"ptrace", b"debug", b"root", b"magisk", b"xposed",
            b"emulator", b"detect", b"hook", b"inject", b"verify", b"md5", b"sha",
            b"/proc/", b"maps", b"TracerPid", b".so", b"libc", b"dlopen", b"mmap",
            b"ACE", b"tprt", b"tersafe", b"anti", b"check", b"kill", b"exit", b"abort"]
    seen = set()
    allstr = strings(b)
    for s in allstr:
        for p in pats:
            if p in s and s not in seen:
                seen.add(s)
                try:
                    print("  " + s.decode("latin1")[:120])
                except:
                    pass
                break
        if len(seen) > 200:
            break

if __name__ == "__main__":
    main()
