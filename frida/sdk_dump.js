// UE4 SDK Dumper — finds GWorld, GNames, GObjects at runtime
// Run: frida -U -f <package> -l sdk_dump.js

'use strict';

const UE4 = Module.findBaseAddress('libUE4.so');
if (!UE4) { console.log('[!] libUE4.so not loaded'); }
else { console.log('[+] libUE4.so base: ' + UE4); }

// Pattern scan for GWorld, GNames, GObjects pointers
// These are global pointers in UE4 — exact patterns vary per build
function scanForGWorld() {
    // GWorld is usually referenced near "GWorld" string
    const results = Memory.scanSync(UE4, Module.findExportByName('libUE4.so', null) ? 0xFFFFFF : 0xB000000,
        '47 57 6F 72 6C 64'); // "GWorld" ASCII
    results.forEach(r => {
        console.log('[+] "GWorld" string at: ' + r.address);
    });
}

function scanForGNames() {
    const results = Memory.scanSync(UE4, 0xB000000,
        '47 4E 61 6D 65 73'); // "GNames" ASCII
    results.forEach(r => {
        console.log('[+] "GNames" string at: ' + r.address);
    });
}

function dumpPointerAt(name, addr) {
    try {
        const ptr = addr.readPointer();
        console.log('[+] ' + name + ' -> ' + ptr);
        return ptr;
    } catch (e) {
        console.log('[-] ' + name + ' read failed: ' + e);
        return null;
    }
}

// Export scan — look for known UE4 exports
function findExports() {
    const exports = Module.enumerateExports('libUE4.so');
    const interesting = ['GWorld', 'GNames', 'GObjects', 'GUObjectArray',
        'FNamePool', 'ProcessEvent', 'GetPlayerViewPoint',
        'GetActorLocation', 'WorldToScreen', 'LineOfSightTo'];

    exports.forEach(exp => {
        interesting.forEach(name => {
            if (exp.name.indexOf(name) !== -1) {
                console.log('[EXPORT] ' + exp.name + ' at ' + exp.address);
            }
        });
    });
}

// Main
setTimeout(function() {
    console.log('=== UE4 SDK Dump ===');
    findExports();
    console.log('=== String Scan ===');
    scanForGWorld();
    scanForGNames();
    console.log('=== Done ===');
}, 3000);
