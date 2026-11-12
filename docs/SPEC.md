# Spec

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
