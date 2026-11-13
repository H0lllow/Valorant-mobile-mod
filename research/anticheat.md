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
- apktool-based gadget injection (objection patchapk) is detected — crashes on launch
- Root cause likely: apktool decode/rebuild cycle changes APK zip structure (resources.arsc re-encoding, entry order/compression), tripping tprt's zip-integrity check — not the gadget content itself

## New method: LIEF ELF injection (no apktool, no DEX changes) — TESTED
- Source: https://lief.re/doc/stable/tutorials/09_frida_lief.html
- Adds `NEEDED libgadget.so` directly into a native lib's ELF dynamic section (`lief.add_library()`)
- Zip stays byte-identical to original except: target .so replaced + gadget .so/.config.so added
- Script: `scripts/lief_inject.py`

### Test 1: target `libWGRecorderApi.so` (tiny, 5.8KB)
- Installed, launched: process (PID 13498) survived splash, loaded a provider, ~15s of normal activity
- Then: `F/libc: Fatal signal 7 (SIGBUS), code 1 (BUS_ADRALN), fault addr 0x0000000000000bb6 in tid ... (Thread-7)`
- `pc 0000000000000bb6 <unknown>` in backtrace — jump through a near-null/garbage function pointer
- Process died ~1s after the signal, native tombstone generated

### Test 2: target `libpxauth.so` (1MB, "normal" profile matching the LIEF tutorial's Telegram example)
- Installed, launched: process (PID 17049) progressed much further — full activity lifecycle, GAME_START, provider loaded, `:plugin` service started successfully
- Then, later (much longer uptime than test 1): **identical crash signature**: `F/libc: Fatal signal 7 (SIGBUS), code 1 (BUS_ADRALN), fault addr 0x...f35 in tid ... (Thread-7)`
- Same thread name ("Thread-7"), same signal/code, only the exact fault address and timing differ

### Interpretation
Two different target libraries, two different injection points, two different crash timings — but the **exact same crash signature** (SIGBUS/BUS_ADRALN, tiny/garbage fault address, thread "Thread-7"). This is not a structural ELF bug from LIEF (checked dynamic section entries — well-formed, correct NEEDED count, no missing tags). The pattern matches a **deliberate, delayed, obfuscated anti-tamper response**: instead of calling `abort()`/`exit()` (easy to hook/detect), the protector corrupts a function pointer so the crash looks like a random bug. This lines up with tersafe's documented self-defense strings (`set_inline_hook_error`, `inline_hook_opcode_dismatch`, `ms_hook_opcode`) — ACE detecting the Frida gadget's presence in-process (regardless of how it was injected — apktool smali patch or LIEF ELF patch, both load the same gadget) and punishing it after a delay, not at load time.

### Conclusion
The wall is **not** the zip/signature check (that one is bypassed fine by both resign-only and LIEF-injection). The wall is **tersafe/ACE detecting the Frida gadget's runtime presence** and killing the process via an obfuscated crash. Any Frida gadget baked into this APK — by any injection method — will likely hit this same detection once it initializes.

### Next directions (unexplored)
- Anti-Frida-detection techniques exist in the wild for Tencent-hardened apps (found during research: community threads on bypassing a "加固"'s Sept 2023 Frida detection). These typically: rename the gadget library/thread names, strip Frida signature strings, delay/unload the gadget after initial hooks are set, or avoid common detection vectors (checking `/proc/self/maps`, named pipes, `TracerPid`).
- This is a deeper rabbit hole than the zip-check fix and not guaranteed to work — tersafe's self-defense is specifically designed to catch this.

## Test 3 (prepared, not yet installed): undetected-frida stealth gadget on `libpxauth.so`
- Gadget: `zer0def/undetected-frida` release `17.26.2`, android-arm64, decompressed to `research/gadgets/undetected-frida-gadget-17.26.2-android-arm64.so`
- `scripts/lief_inject.py` updated: `GADGET_SRC` → stealth gadget, `APK_OUT` → `apk/original/base_lief3.apk`
- Injection + signing done: `apk/original/base_lief3_signed.apk` (v1/v2/v3 verified true, same as prior working builds)
- Not installed on device yet — awaiting user go-ahead per project rule.

## Test 3 (executed on device): undetected-frida stealth gadget — RESULT: FAILED
- Installed `base_lief3_signed.apk`, launched via monkey, live logcat capture
- App progressed much further than any prior test: full UE4 GameActivity lifecycle, video decoder init, audio tracks, TGPA cloud config, GameManager/oiface bind — all normal, ~12s uptime
- Then: **same crash signature as test 1/2** — `signal 7 (SIGBUS), code 1 (BUS_ADRALN), fault addr 0x0000000000000dc5`, pc/lr/x8 all equal to the fault addr (jump through near-null pointer), named thread `Thread-6`, tombstone written
- Difference from tests 1/2: this time the crash hit the `:plugin` sub-process (pid 20026), not the main process
- ~6s later the main process also died (OPPO `theia` diagnostic logger recorded `appCrash_com.tencent.tmgp.codev` at the same timestamp as the plugin crash, full app log bundle captured by the OEM crash reporter)
- **Conclusion: renaming the gadget binary, RPC strings, thread names, and pipe name (undetected-frida's patch set) is not sufficient.** tersafe/ACE's detection does not rely purely on those strings — it still finds and kills the gadget, now manifesting in a different process. The obfuscated near-null-pointer-jump crash pattern is consistent across stock gadget and stealth gadget.

### Next direction
- `undetected-frida` (fixed string/name patches) ruled out as a solution on its own.
- Remaining options: `phantom-frida` (deeper patch set, 90 patches/16 vectors — may hit vectors undetected-frida doesn't cover, e.g. `--strict-wx` memory protection scanning) or root/Zygisk once the new phone arrives.

## Test 4 (prepared, not yet installed): phantom-frida custom build on `libpxauth.so`
- Environment: WSL2 Ubuntu 22.04, JDK17, Android NDK r29, Android SDK (build-tools 34.0.0 + platform 34, Linux-native, for `d8`/`android.jar`), Node 20.20.2
- Built `TheQmaks/phantom-frida` from source: Frida 17.16.4, arch android-arm64, name `pxcache`, port 27342, `--extended --strict-wx --verify`
- Build succeeded, forbidden-marker scan passed (both pxcache-server and pxcache-gadget), SHA256SUMS verified
- Output: `research/gadgets/pxcache-gadget-17.16.4-android-arm64.so` (24MB stripped), `pxcache-build-info.json`
- `scripts/lief_inject.py` updated: `GADGET_SRC` → pxcache gadget, library/config names → `libpxcache-gadget.so` / `libpxcache-gadget.config.so` (per phantom-frida's naming convention), `APK_OUT` → `apk/original/base_lief4.apk`
- Injection + signing done: `apk/original/base_lief4_signed.apk` (v1/v2/v3 verified true)
- Not installed on device yet — awaiting user go-ahead per project rule.
- Caveat from phantom-frida's own docs: marker absence does not prove resistance to behavioral/integrity/timing detection — tersafe's crash pattern in tests 1-3 did not key off simple string markers, so this is a deeper patch set than undetected-frida but still not a guarantee.
