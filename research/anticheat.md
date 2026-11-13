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

## Test 4 (executed on device): phantom-frida gadget — RESULT: FAILED
- Installed `base_lief4_signed.apk`, launched cleanly (no overlapping adb commands), full logcat captured
- `GAME_START` at 11:20:20.611 (main pid 19654)
- `:plugin` process (pid 26008) crashed ~8.5s later: `Fatal signal 7 (SIGBUS), code 1 (BUS_ADRALN), fault addr 0xb93`, thread `Thread-6` — same pattern as tests 1-3
- ~6.7s after that, the **main** process (pid 19654) also crashed, this time with a **different signal**: `Fatal signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x5f5`, again thread `Thread-6` — near-null fault address, same obfuscated-crash shape as the SIGBUS variant, just a different signal number
- Main process declared dead at 11:20:37.161 (~16.5s total uptime)
- **Conclusion: phantom-frida's deeper patch set (recursive symbol renaming, runtime string aliasing, `--strict-wx` memory hardening, forbidden-marker verification) is still detected by tersafe/ACE.** The detection is not defeated by renaming strings/symbols or hardening W^X memory — it appears to key off something more fundamental (likely scanning loaded library code/behavior directly, independent of specific symbol names).
- This rules out both `undetected-frida` and `phantom-frida` as solutions for this specific anti-cheat (tersafe/ACE in this APK). Both are well-regarded stealth-gadget projects; neither got past this wall.

## Overall conclusion on no-root Frida injection
Four independent attempts (stock gadget via LIEF on two different libraries, `undetected-frida`, `phantom-frida`) all end in the same obfuscated-crash pattern (near-null fault address, thread named "Thread-N", first in a secondary process then the main process) within seconds to tens of seconds of the gadget initializing. This strongly suggests tersafe/ACE detects the Frida runtime itself (code/behavior-based), not just known strings or file names — a wall that gadget renaming/hardening tools are not designed to defeat. Remaining options: root/Zygisk-based injection (different attack surface, was deferred pending new phone), or a much deeper investigation into tersafe's detection routine itself (static reverse engineering of the OLLVM-obfuscated detection code) to find and patch the specific check — both are larger efforts than gadget substitution.

## Infra fix: zipalign required after LIEF rebuild
Our LIEF-based zip rebuild (`scripts/lief_inject.py`) rewrites every zip entry via Python's `zipfile`, which does not preserve Android's 4-byte alignment requirement for uncompressed entries (`resources.arsc`, native libs). This caused install failures on Android 11+ with:
`Failed parse during installPackageLI: Targeting R+ (version 30 and above) requires the resources.arsc of installed APKs to be stored uncompressed and aligned on a 4-byte boundary`
Confirmed via logcat (`PackageInstallerSession: Marking session ... as failed: -124`). Not Play Protect — Play Protect's own verifier explicitly returned `VERIFICATION_ALLOW` in the same log.
**Fix**: run `zipalign -f -p 4` on the LIEF output *before* signing (zipalign must happen before apksigner v2/v3, which seals the final byte layout). Confirmed via `zipalign -c -v 4`: `resources.arsc (OK)`.
This should be a permanent step in the build pipeline going forward, independent of the anti-cheat investigation — it's a packaging correctness issue, not security-related, but it silently caused some earlier device-install attempts to fail for the wrong reason (need to re-verify whether any earlier "flaky install" symptom in this investigation was actually this bug rather than tooling flakiness).

## Test 5 (executed on device, after zipalign fix): phantom-frida gadget on `libmmkv.so` — RESULT: FAILED
- `base_lief5_aligned_signed.apk` installed successfully after the zipalign fix
- Launched: `GAME_START` at 11:52:01.844, crash at 11:52:05.326 — **same obfuscated-crash pattern**: `Fatal signal 7 (SIGBUS), code 1 (BUS_ADRALN), fault addr 0xdc5`, thread `Thread-7`
- Crash happened in the **main process directly** (pid 29986), during `SplashActivity` (before `GameActivity` even starts) — earliest crash yet (~4s after GAME_START)
- **Conclusion: `libmmkv.so` is NOT on tersafe's explicit `System.loadLibrary()` list (gsdk/UE4/tersafe/gcloud/gcloudcore/WGRecorderApi/WGRecorder/GCloudVoice/pxauth/c++_shared), yet the crash is identical.** This refutes the "specific-library-checksum" hypothesis from the CRC-manipulator research.

## Revised conclusion (supersedes the per-library-checksum theory)
Five independent tests — stock gadget via LIEF on 2 libraries, `undetected-frida`, `phantom-frida` on `libpxauth.so`, `phantom-frida` on `libmmkv.so` (explicitly NOT on any known checked-library list) — all produce the **same obfuscated crash signature** (SIGBUS/SIGSEGV, near-null fault address, thread named "Thread-N", first a secondary process/early activity then the main process). The common factor across every test is simply: *a Frida gadget gets loaded and initializes inside the process*, regardless of which host library carries the `NEEDED` entry or which gadget build is used.
This points to tersafe/ACE detecting the **Frida runtime's own presence/initialization behavior** (likely via memory-region/thread/GumJS-engine-pattern scanning, not per-file checksums and not simple string matching — both of which we've now ruled out across 5 tests). No gadget-renaming or injection-target change defeats this; a working bypass would need either root-based injection (different code path, not subject to this userspace self-check the same way) or reverse-engineering tersafe's actual detection routine to neutralize the specific check.

## Deep RE of tersafe detection routine (Ghidra, project saved at research/ghidra_proj/tersafe)
- Initial string-xref attempt (`scripts/tersafe_xref.py`, raw ADRP/ADD byte scan) produced a false-positive "self-defense cluster" — off by +0x100000 due to a page-base bug. Superseded by Ghidra's own ReferenceManager (`scripts/tersafe_strxref.java`), which gives correct results.
- Real self-defense string function: `FUN_0046476c` (0x46476c) — a generic one-shot error *telemetry* dispatcher (~50 internal error codes: crc, hook, mmap, file I/O, thread start failures). Not the detection logic itself.
- Its caller `FUN_003cafcc` is a generic internal RPC command dispatcher ("mrpcs") — also not the detection logic. Dead end for the string-based approach.
- Pivoted to import-based search (`scripts/tersafe_imports.java`): listed callers of `mmap`/`mprotect`/`ptrace`/`open`/`fgets`/`mincore`/`fopen` thunks.
- Found `FUN_0055d324`, called once by `FUN_00560190`: builds a table of ~30 resolved libc function pointers (getenv, send, recv, fopen, mmap, ptrace, dlopen, pthread_create, fork, connect, syscall, access, opendir, execl, clock_gettime, select, stat/fstat, getpid, gettimeofday, sleep, write, read, open, fread/fgets, kill, readdir, fseek).
- `FUN_00560190` checks each of those pointers falls inside libc.so's real mapped range (via `FUN_005d0110` + `FUN_0055ce24`) — a **GOT/PLT hook-integrity check**.
- `FUN_00560190`'s caller `FUN_00559c3c` is the real detection gate: ORs four checks —
  1. `FUN_0056080c` — iterates process threads via `getpid()` + a per-thread syscall wrapper (`FUN_005d316c`, buffer 0x10) — thread-count/thread-scan check.
  2. `FUN_00560284` — same pattern, second thread-scan variant.
  3. `FUN_00560190` — the GOT/PLT pointer-range check above.
  4. `FUN_00560d04` — compares against a resource-string/list (ids 0x6794/0x67b5) — likely a blacklist check.
- If any of the four trips, `FUN_00559c3c` calls `FUN_0057b724`, a **shared violation-report function used from 34 call sites across the whole binary** (root check, emulator check, hook check, etc. all funnel through it) — not specific to anti-hook. It gates on internal state flags, then calls `FUN_0057b884` (not yet decompiled — the actual terminal action, presumably abort/kill).
- **Conclusion**: tersafe's Frida detection is not one simple check but an OR of independent thread-scanning and GOT-integrity checks, feeding a generic, widely-reused violation handler. No single string/byte patch target identified yet; next step (not done) would be locating `FUN_00559c3c`'s own caller(s) (likely a periodic watchdog) and evaluating whether patching that call site is feasible without tripping tersafe's own code-integrity self-check on itself.
- Scripts used (kept in `scripts/`): `tersafe_find.java`, `tersafe_disasm.java`, `tersafe_strxref.java`, `tersafe_imports.java` — all Ghidra headless Java postScripts (Ghidra 12.2 dropped Jython; `.py` postScripts now require PyGhidra/CPython, unavailable in this JDK-only setup). Run via `-process <name> -noanalysis -postScript <file>.java <output>` against the already-analyzed `research/ghidra_proj/tersafe` project (one-time analysis took ~76 min; subsequent runs are seconds).

## Decision: root is not the end goal, only an experimental track
User confirmed: attempting a root-based bypass is worth trying once a device is available, but the shipped mod must also work on non-rooted devices (the common case). Root-based injection (if it works) and the no-root path (gadget injection, blocked by tersafe as documented above) are two separate, parallel tracks — not a replacement of one by the other.
