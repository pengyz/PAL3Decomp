// manual/pal3/platform/windows/WinMain.cpp - Windows entry (manual rewrite)
// Migration start 2026-10-27 (gradual substitution - main entry)
// Platform layer: manual/pal3/platform/windows (linux/android later)
// Source: original/PAL3.exe _WinMain@16 (0x541900 - skip_functions)
//
// Strategy: codegen output + key interface mock -> compilable -> call chain -> runnable -> byte-identical

#include <windows.h>
#include "../../mock/mock_interfaces.h"

// WinMain (Windows entry - migration start)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Init (window/resource/game state) - mock (TODO: codegen migration)
    if (!Mock_InitWindow(hInstance, nCmdShow)) return 1;
    HWND hWnd = Mock_CreateMainWindow(hInstance, nCmdShow);
    if (!hWnd) return 1;
    if (!Mock_ShowWindow(hWnd, nCmdShow)) return 1;
    if (!Mock_LoadResources()) return 1;
    if (!Mock_InitGameState()) return 1;

    // Main loop (message/render/logic) - mock (TODO: codegen migration)
    while (true) {
        int msgResult = Mock_MessageLoop();
        if (msgResult != 0) break;
        Mock_UpdateGame();
        Mock_RenderFrame();
    }

    // Shutdown (cleanup) - mock (TODO: codegen migration)
    Mock_FreeResources();
    Mock_Shutdown();
    return 0;
}
