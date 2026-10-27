// manual/pal3/mock/mock_interfaces.h - mock interfaces (temporary, replace with real)
// Mock role: gbengine interface (DLL import) + PAL3 own functions (migration)
// System APIs (ShowWindow/CreateWindow) = direct calls (no mock needed)

#ifndef MOCK_INTERFACES_H
#define MOCK_INTERFACES_H

#include <windows.h>

// gbengine interface mock (TODO: replace with real gbengine calls)
BOOL Mock_InitGameState();
void Mock_UpdateGame();
void Mock_RenderFrame();
void Mock_Shutdown();

// PAL3 own function mock (TODO: replace with migrated functions)
int Mock_MessageLoop();
BOOL Mock_LoadResources();
void Mock_FreeResources();

#endif // MOCK_INTERFACES_H
