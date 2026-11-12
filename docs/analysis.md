# Static Analysis

## Engine
- Unreal Engine 4 (libUE4.so, 180MB, arm64-v8a)
- Not fully stripped — UE4 class/function strings present

## Key Libraries

| Library | Size | Role |
|---|---|---|
| libUE4.so | 180MB | Game engine + logic — main target |
| libtersafe.so | 7MB | Tencent ACE anti-cheat |
| libgcloud.so | 11MB | Tencent Cloud networking |
| libapp.so | 7.8MB | Flutter/Dart (lobby UI) |
| libflutter.so | 10MB | Flutter engine |
| libMSDKCore.so | 5MB | Tencent MSDK |

## Confirmed Strings in libUE4.so

| Symbol | Offset |
|---|---|
| PlayerController | 0x267C5CE |
| ACharacter | 0x268C25D |
| WorldToScreen | 0x280B25F |
| LineOfSightTo | 0x27BE1CB |

## Architecture
- 5 DEX files (Java/Kotlin layer)
- arm64-v8a only
- Flutter for lobby, UE4 for game
- Tencent infra: MSDK, GCloud, TerSafe

## Next Steps
- Runtime SDK dump via Frida (GWorld, GNames, GObjects)
- Find UWorld, ULevel, APlayerController, APawn offsets at runtime
- Analyze libtersafe.so hooks for anti-cheat bypass
