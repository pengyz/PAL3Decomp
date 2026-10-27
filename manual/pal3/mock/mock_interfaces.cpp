// manual/pal3/mock/mock_interfaces.cpp - mock implementations (temporary)
// System APIs = direct calls (ShowWindow/CreateWindow/DefWindowProc)
// Mock = gbengine interface + PAL3 own functions (migration)

#include "mock_interfaces.h"

// gbengine interface mock
BOOL Mock_InitGameState() {
    // TODO: replace with gbengine call (game state init)
    return TRUE;
}

void Mock_UpdateGame() {
    // TODO: replace with gbengine call (game update)
}

void Mock_RenderFrame() {
    // TODO: replace with gbengine call (render)
}

void Mock_Shutdown() {
    // TODO: replace with gbengine call (cleanup)
}

// PAL3 own function mock
int Mock_MessageLoop() {
    // TODO: replace with migrated function (message loop)
    return 0;
}

BOOL Mock_LoadResources() {
    // TODO: replace with migrated function (resource load)
    return TRUE;
}

void Mock_FreeResources() {
    // TODO: replace with migrated function (resource free)
}
