@echo off
java -jar ..\tools\apktool.jar b ..\apk\decompiled -o ..\apk\output.apk
java -jar ..\tools\signapk.jar ..\tools\testkey.x509.pem ..\tools\testkey.pk8 ..\apk\output.apk ..\apk\output_signed.apk
