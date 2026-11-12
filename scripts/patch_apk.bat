@echo off
set "PATH=%LOCALAPPDATA%\Programs\Python\Python313\Scripts;%LOCALAPPDATA%\Android\sdk\build-tools\34.0.0;%LOCALAPPDATA%\Android\sdk\platform-tools;C:\Users\giada\Documents\Forge\Valorant-mobile-mod\tools;%PATH%"
set "PYTHONUTF8=1"
set "PYTHONIOENCODING=utf-8"
cd /d "C:\Users\giada\Documents\Forge\Valorant-mobile-mod\apk\original"
objection patchapk -s base.apk -a arm64-v8a -j 2
