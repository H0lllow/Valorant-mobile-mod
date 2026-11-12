// Post-match cleanup — disable all mods, clear traces
// Triggered on match end event

'use strict';

const scripts = {}; // references to other loaded scripts

function onMatchEnd() {
    console.log('[CLEANUP] Match ended, disabling all mods');

    // Disable aimbot + wallhack
    if (scripts.aimbot) scripts.aimbot.exports.disable();
    if (scripts.wallhack) scripts.wallhack.exports.disable();

    // Reset stats counters
    if (scripts.aimbot) scripts.aimbot.exports.resetStats();

    // Flush network hooks — let clean data through
    if (scripts.netHook) scripts.netHook.exports.disable();

    console.log('[CLEANUP] All mods disabled');
}

// Detect match state changes
// TODO: hook UE4 GameState or match flow function
// Look for: AGameState::HandleMatchHasEnded, MatchState transitions
function hookMatchState() {
    // Placeholder — exact function depends on SDK dump
    console.log('[CLEANUP] Match state hook ready');
}

rpc.exports = {
    registerScripts: function(refs) { Object.assign(scripts, refs); },
    forceCleanup: function() { onMatchEnd(); },
    hookMatchState: hookMatchState,
};
