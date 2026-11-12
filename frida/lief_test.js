// Minimal probe script for LIEF-injected gadget — confirms it loaded and runs.
'use strict';
console.log("[lief-gadget] alive, pid=" + Process.id);
setTimeout(function() {
    try {
        Java.perform(function() {
            console.log("[lief-gadget] Java.perform OK");
        });
    } catch (e) {
        console.log("[lief-gadget] Java.perform failed: " + e);
    }
}, 1000);
