// Overlay menu — toggle mods in-game
// Communicates with Android overlay service via RPC

'use strict';

const state = {
    inMatch: false,
    aimbot: false,
    wallhack: false,
    netPatch: false,
};

// Detect game state: lobby vs match
function hookGameState() {
    // TODO: hook UE4 GameState transitions
    // Set state.inMatch accordingly
    // Overlay auto-shows on match start, auto-hides on match end
}

rpc.exports = {
    getState: function() { return JSON.stringify(state); },
    toggle: function(feature) {
        if (!state.inMatch && feature !== 'forceEnable') return;
        state[feature] = !state[feature];
        return JSON.stringify(state);
    },
    setInMatch: function(v) { state.inMatch = v; },
};
