import lief, zipfile, shutil, os, tempfile

APK_IN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\apk\original\base.apk"
TARGET_SO = "lib/arm64-v8a/libWGRecorderApi.so"
work = tempfile.mkdtemp(prefix="liefdiag_")
orig = os.path.join(work, "orig.so")
with zipfile.ZipFile(APK_IN) as z, open(orig, "wb") as out:
    shutil.copyfileobj(z.open(TARGET_SO), out)

b = lief.parse(orig)
print("=== ORIGINAL ===")
print("Type:", b.header.file_type)
print("Entrypoint:", hex(b.entrypoint) if hasattr(b, "entrypoint") else "n/a")
for seg in b.segments:
    print("SEG", seg.type, "vaddr", hex(seg.virtual_address), "filesz", seg.physical_size, "memsz", seg.virtual_size, "align", seg.alignment)
print("Dynamic entries:", len(b.dynamic_entries))
print("Libraries:", list(b.libraries))

b.add_library("libgadget.so")
patched = os.path.join(work, "patched.so")
b.write(patched)

p = lief.parse(patched)
print("\n=== PATCHED ===")
print("Libraries:", list(p.libraries))
for seg in p.segments:
    print("SEG", seg.type, "vaddr", hex(seg.virtual_address), "filesz", seg.physical_size, "memsz", seg.virtual_size, "align", seg.alignment)
print("Patched file valid parse:", p is not None)
print("orig size:", os.path.getsize(orig), "patched size:", os.path.getsize(patched))
shutil.copy(patched, r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\research\patched_diag.so")
