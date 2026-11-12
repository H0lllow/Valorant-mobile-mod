// SSL certificate pinning bypass
// Must run before net_hook.js

'use strict';

// Generic Android SSL pinning bypass
function bypassSSLPinning() {
    // OkHttp CertificatePinner
    try {
        const CertificatePinner = Java.use('okhttp3.CertificatePinner');
        CertificatePinner.check.overload('java.lang.String', 'java.util.List').implementation = function() {
            console.log('[SSL] OkHttp pin bypassed');
        };
    } catch (e) {}

    // TrustManager
    try {
        const TrustManagerFactory = Java.use('javax.net.ssl.TrustManagerFactory');
        const X509TrustManager = Java.use('javax.net.ssl.X509TrustManager');
        // Accept all certs
        const TrustAllCerts = Java.registerClass({
            name: 'com.mod.TrustAllCerts',
            implements: [X509TrustManager],
            methods: {
                checkClientTrusted: function() {},
                checkServerTrusted: function() {},
                getAcceptedIssuers: function() { return []; },
            }
        });
        console.log('[SSL] TrustManager bypassed');
    } catch (e) {}

    // Native SSL verify
    try {
        const SSL_CTX_set_verify = Module.findExportByName('libssl.so', 'SSL_CTX_set_custom_verify');
        if (SSL_CTX_set_verify) {
            Interceptor.attach(SSL_CTX_set_verify, {
                onEnter: function(args) { args[1] = ptr(0); } // disable verify callback
            });
            console.log('[SSL] Native SSL verify bypassed');
        }
    } catch (e) {}
}

Java.perform(function() {
    bypassSSLPinning();
});
