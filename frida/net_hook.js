// Network hook — intercept outgoing stats, normalize suspicious values
// Run: frida -U -f <package> -l net_hook.js

'use strict';

const config = {
    enabled: false,
    maxHeadshotPct: 65,   // cap reported headshot %
    maxAccuracyPct: 55,   // cap reported accuracy %
    fakeReactionMs: 200,  // minimum reported reaction time
};

// Hook SSL_write to intercept outgoing data before encryption
// Must bypass certificate pinning first (see bypass/ssl_pinning.js)

function hookSSLWrite() {
    const SSL_write = Module.findExportByName('libssl.so', 'SSL_write');
    if (!SSL_write) {
        console.log('[-] SSL_write not found, trying libgcloud.so');
        return;
    }

    Interceptor.attach(SSL_write, {
        onEnter: function(args) {
            const buf = args[1];
            const len = args[2].toInt32();
            const data = buf.readUtf8String(len);
            if (data && data.indexOf('headshot') !== -1) {
                console.log('[NET] Stats payload intercepted, len=' + len);
                this.buf = buf;
                this.len = len;
                this.data = data;
            }
        },
        onLeave: function(retval) {
            // TODO: parse and patch stats payload
            // Normalize headshot%, accuracy%, reaction times
        }
    });
}

// Hook HTTP/protobuf layer if game uses custom protocol
function hookGCloudSend() {
    // libgcloud.so handles Tencent network protocol
    // Look for send/post/request functions
    const gcloud = Module.findBaseAddress('libgcloud.so');
    if (!gcloud) return;

    const exports = Module.enumerateExports('libgcloud.so');
    exports.forEach(exp => {
        if (exp.name.match(/send|post|request|write/i)) {
            console.log('[GCLOUD] ' + exp.name + ' at ' + exp.address);
        }
    });
}

rpc.exports = {
    enable: function() { config.enabled = true; hookSSLWrite(); hookGCloudSend(); },
    disable: function() { config.enabled = false; },
};
