#!/usr/bin/env python3
# Root-track experiment: spawn the game via frida-server (root), catch
# libtersafe.so's dlopen, and patch its Frida-detection gate (FUN_00559c3c,
# offset 0x559c3c) to an immediate RET before resuming. If this survives
# where all no-root gadget tests crashed, the gate patch is the real fix.
import sys
import time
import frida

PACKAGE = "com.tencent.tmgp.codev"
GATE_OFFSET = 0x559c3c  # FUN_00559c3c entry point (self-defense OR gate)

JS = r"""
const GATE_OFFSET = ptr(%d);
function patchGate(base) {
    const addr = base.add(GATE_OFFSET);
    Memory.protect(addr, 4, 'rwx');
    // AArch64 RET (0xD65F03C0, little-endian bytes)
    addr.writeByteArray([0xC0, 0x03, 0x5F, 0xD6]);
    send("PATCHED tersafe gate @ " + addr);
}

const dlopen = Module.findGlobalExportByName("android_dlopen_ext");
Interceptor.attach(dlopen, {
    onEnter(args) {
        try { this.path = args[0].readCString(); } catch (e) { this.path = null; }
    },
    onLeave(retval) {
        if (this.path && this.path.indexOf("libtersafe.so") !== -1) {
            const m = Process.findModuleByName("libtersafe.so");
            if (m) {
                patchGate(m.base);
            } else {
                send("WARN: libtersafe.so dlopen seen but module not found yet");
            }
        }
    }
});
send("HOOK_READY");
""" % GATE_OFFSET


def on_message(pid, message, data):
    print(f"[script pid={pid}]", message)


def instrument(device, pid):
    # tersafe is loaded independently in every process of this package
    # (main, :plugin, :xg_vip_service) - each needs its own gate patch.
    session = device.attach(pid)
    script = session.create_script(JS)
    script.on("message", lambda m, d: on_message(pid, m, d))
    script.load()
    return session


def main():
    device = frida.get_usb_device(timeout=10)
    sessions = {}

    def on_spawn_added(spawn):
        # enable_spawn_gating() pauses every new process on the device, not
        # just ours - resume anything unrelated immediately or the whole
        # system stalls (this is what killed frida-server last run).
        if PACKAGE in spawn.identifier:
            print("Child spawn:", spawn.identifier, spawn.pid)
            try:
                sessions[spawn.pid] = instrument(device, spawn.pid)
            except Exception as e:
                print("  instrument failed:", e)
        device.resume(spawn.pid)

    device.on("spawn-added", on_spawn_added)
    device.enable_spawn_gating()

    print("Spawning", PACKAGE)
    pid = device.spawn([PACKAGE])
    sessions[pid] = instrument(device, pid)
    device.resume(pid)
    print("Resumed, pid =", pid)
    print("Monitoring for 70s (Ctrl+C to stop early)...")
    try:
        time.sleep(70)
    except KeyboardInterrupt:
        pass
    for p, s in sessions.items():
        try:
            print(f"pid {p} still attached:", s.is_detached == False)
        except Exception as e:
            print(f"pid {p} session check failed:", e)


if __name__ == "__main__":
    sys.exit(main())
