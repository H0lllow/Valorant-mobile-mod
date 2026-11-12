#!/usr/bin/env python3
# Injects Frida gadget via ELF NEEDED entry (LIEF), no apktool, no DEX changes.
# Keeps the APK zip byte-identical except: patched target .so, + gadget .so/.config.so added.
import sys, os, shutil, zipfile, tempfile
import lief

APK_IN = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\apk\original\base.apk"
APK_OUT = r"C:\Users\giada\Documents\Forge\Valorant-mobile-mod\apk\original\base_lief.apk"
TARGET_SO = "lib/arm64-v8a/libWGRecorderApi.so"
GADGET_SRC = r"C:\Users\giada\.objection\android\arm64-v8a\libfrida-gadget.so"
GADGET_NAME = "libgadget.so"
GADGET_CONF_NAME = "libgadget.config.so"
SCRIPT_PATH_ON_DEVICE = "/data/local/tmp/frida_script.js"

work = tempfile.mkdtemp(prefix="liefinj_")
target_tmp = os.path.join(work, "target.so")
patched_tmp = os.path.join(work, "target_patched.so")

with zipfile.ZipFile(APK_IN, "r") as z:
    with z.open(TARGET_SO) as f, open(target_tmp, "wb") as out:
        shutil.copyfileobj(f, out)

binf = lief.parse(target_tmp)
assert binf is not None, "failed to parse target .so"
print("Existing NEEDED:", list(binf.libraries))
binf.add_library(GADGET_NAME)
binf.write(patched_tmp)
print("Patched written:", patched_tmp, os.path.getsize(patched_tmp))

config = '{\n  "interaction": {\n    "type": "script",\n    "path": "%s",\n    "on_change": "reload"\n  }\n}\n' % SCRIPT_PATH_ON_DEVICE
config_tmp = os.path.join(work, "gadget.config")
with open(config_tmp, "w") as f:
    f.write(config)

if not os.path.exists(GADGET_SRC):
    print("ERROR: gadget source not found:", GADGET_SRC)
    sys.exit(1)

with zipfile.ZipFile(APK_IN, "r") as zin, zipfile.ZipFile(APK_OUT, "w") as zout:
    for item in zin.infolist():
        if item.filename == TARGET_SO:
            data = open(patched_tmp, "rb").read()
        else:
            data = zin.read(item.filename)
        # preserve compression type per original entry
        zi = zipfile.ZipInfo(item.filename, date_time=item.date_time)
        zi.compress_type = item.compress_type
        zi.external_attr = item.external_attr
        zout.writestr(zi, data, compress_type=item.compress_type)
    # add gadget lib + config next to target, same dir
    gdir = os.path.dirname(TARGET_SO)
    gadget_data = open(GADGET_SRC, "rb").read()
    zi = zipfile.ZipInfo(f"{gdir}/{GADGET_NAME}", date_time=(2024,1,1,0,0,0))
    zi.compress_type = zipfile.ZIP_DEFLATED
    zout.writestr(zi, gadget_data, compress_type=zipfile.ZIP_DEFLATED)
    zi2 = zipfile.ZipInfo(f"{gdir}/{GADGET_CONF_NAME}", date_time=(2024,1,1,0,0,0))
    zi2.compress_type = zipfile.ZIP_DEFLATED
    zout.writestr(zi2, config.encode(), compress_type=zipfile.ZIP_DEFLATED)

print("WROTE", APK_OUT, os.path.getsize(APK_OUT))
shutil.rmtree(work, ignore_errors=True)
