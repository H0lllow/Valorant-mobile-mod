import lief, zipfile, shutil, os, tempfile

APK_IN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\apk\original\base.apk"
TARGET_SO = "lib/arm64-v8a/libWGRecorderApi.so"
work = tempfile.mkdtemp(prefix="liefdiag2_")
orig = os.path.join(work, "orig.so")
with zipfile.ZipFile(APK_IN) as z, open(orig, "wb") as out:
    shutil.copyfileobj(z.open(TARGET_SO), out)

def dump_dyn(path, label):
    b = lief.parse(path)
    print("===", label, "===")
    for e in b.dynamic_entries:
        print(" ", e.tag, getattr(e, "value", None))

dump_dyn(orig, "ORIGINAL DYNAMIC")

b = lief.parse(orig)
b.add_library("libgadget.so")
patched = os.path.join(work, "patched.so")
b.write(patched)
dump_dyn(patched, "PATCHED DYNAMIC")
