# Roadmap

## Lifecycle

| State | Mod behavior |
|---|---|
| Lobby | everything off, no traces |
| Match start | overlay appears, manual toggle |
| In game | wallhack + aimbot active, humanizer running |
| Match end | auto-cleanup: memory, stats, network data |
| Lobby | back to off |

## Features

- **Aimbot** — auto-aim headshot, smooth curve + jitter + delay (~80-150ms) to look human
- **Wallhack/ESP** — players visible through walls
- **Humanizer** — headshot rate capped ~65%, non-linear aim movement
- **Network patch** — intercept outgoing stats, normalize suspicious values before send
- **Overlay menu** — simple in-game overlay, toggle wallhack/aimbot, auto-hides on match end

## Stack

- Static analysis: apktool + Ghidra (find functions/offsets)
- Runtime: Frida scripts (hook, patch, cleanup)
- Final: bake Frida logic into modified .so → repacked APK

## Frida scripts

| File | Purpose |
|---|---|
| `frida/aimbot.js` | aim hook + humanizer |
| `frida/wallhack.js` | ESP rendering hook |
| `frida/net_hook.js` | intercept + normalize outgoing stats |
| `frida/cleanup.js` | post-match memory + state reset |
| `frida/bypass/ssl_pinning.js` | certificate pinning bypass |
| `frida/overlay.js` | in-game menu overlay trigger |

## Roadmap

| Phase | Task | Status |
|---|---|---|
| 1 | Project structure + repo | done |
| 2 | Static analysis (APK, libs, engine) | done |
| 3 | Frida gadget injection into APK | done (blocked by ACE) |
| 3b | Anti-cheat static analysis (tprt/tersafe) | in progress |
| 3c | Patch tprt APK-verify + tersafe self-check | done — resign alone works, no deobf needed |
| 3e | Decide runtime injection method (root+frida-server vs alternative) | pending |
| 3d | Handle server-side cert/crc handshake | pending (hard) |
| 4 | Runtime SDK dump (GWorld, GNames, offsets) | pending |
| 5 | Wallhack/ESP | pending |
| 6 | Aimbot + humanizer | pending |
| 7 | Network stats patch + SSL pinning bypass | pending |
| 8 | Post-match cleanup lifecycle | pending |
| 9 | In-game overlay menu | pending |
| 10 | Bake gadget+scripts into final repacked APK | pending |
