# Anti-Cheat Analysis

## Libraries

| Lib | Size | Packed | Role |
|---|---|---|---|
| libtprt.so | 1.4MB | no (.text ent 6.86) | TP runtime: PLT/GOT hooks, root check, APK zip/signature verify |
| libtersafe.so | 7MB | no (.text 6.71) | ACE core: emulator/root/debugger detection, CRC+cert checks, self anti-hook, server handshake |
| libtgpa.so | 1.6MB | ? | perf/guard |
| libturinggame.so | 235KB | ? | Turing anti-cheat module |
| libgamemaster.so | 671KB | ? | game master hooks |

## tprt checks (crash cause)
- Reads + inflates APK zip (zlib strings present) → signature/CRC verify
- Root: `/data/data/com.topjohnwu.magisk`
- `android:debuggable` flag
- Hook table: `g_tprt_pfn_array`, `g_tprt_ori_array`

## tersafe checks (ACE core)
- Emulator: `check_ext_emu_feature`, emulator warning string
- Root: `root_alert`, `is_root=%d`
- Debugger: `safe_ptrace`, `TracerPid`, `/proc/%d/status`, GPU Profiler warning
- Integrity: `code_size`, `crc`, `cert_md5`, `9003_cert_md5`, `ano_cert_md5`, `ms_data_crc`, `spgp_verify`
- **Self anti-hook**: `set_inline_hook_error`, `inline_hook_opcode_dismatch`, `ms_hook_opcode` — detects patches to its own code
- Possible config flags: `ano_ignore_detect`, `ano_cert_md5`
- Abort path: `_exit`, `abort`, `android_set_abort_message`, `mrpcs_abort.dat`

## Server-side handshake (hard wall)
- `tss_recv_sec_signature`, `tss_sdk_wait_verify`, `TssSDKOnRecvSignature`, `tss_sdk_rcv_anti_data`
- Client sends anti-data (cert_md5, crc, root/emu flags) → waits server verify signature
- `ver:%s app_ver:%s code_size:%s crc:%s`, `jar_ver:%s,cert_env:%s`

## Two walls for static patching
1. **Self-integrity / anti-inline-hook** inside tersafe: patching its .text triggers `inline_hook_opcode_dismatch` → abort. Must neutralize the self-check before/with any patch.
2. **Server validation**: cert_md5 + crc are sent upstream. A perfect local patch still reports a wrong cert to Tencent → server-side ban risk even if client runs.

## Packer (confirmed via jadx)
- `com.tencent.tpshell.TPShellApplication` is the app shell (加固 packer)
- `static { System.loadLibrary("tprt"); }` then `attachBaseContext()` calls native `initialize()`
- tprt `initialize()` unpacks the real DEX at runtime + runs integrity checks
- `catch (Exception e2) {}` swallows "initialize failed." → real DEX never loaded → startup crash
- tprt CANNOT be skipped: without initialize() no real code runs
- libtprt.so is OLLVM-obfuscated (control-flow flattening, confirmed in decompiler output)

## Discriminating test — RESULT
- `apk/original/base_resign.apk`: original code, only re-signed with our key (v1+v2+v3 verified)
- Installed + launched on device: process PID alive (main + `:plugin` + `:xg_vip_service`), no crash, no tombstone
- **Conclusion: tprt accepts re-signing.** The earlier crash was caused by the Frida gadget injection (objection patchapk), not by the APK signature check.
- No OLLVM deobfuscation needed for this wall.

## Revised plan
- Do NOT inject frida-gadget into the APK (detected, causes crash)
- Options instead:
  1. Root device (Magisk+Zygisk) + frida-server — standard runtime injection, no APK repack
  2. Frida without root: spawn via `frida` against a re-signed-only APK + USB, no gadget baked in (requires root anyway for frida-server/frida-inject on a locked device)
- Since user wants to avoid root: test whether tersafe/UE4 do further checks once in a live match (this test only reached splash/menu, not live gameplay) before committing to a runtime-injection plan
