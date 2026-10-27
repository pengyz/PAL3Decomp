// manual/pal3/platform/windows/WinMain.cpp - Windows entry (manual rewrite)
// System APIs = direct calls (ShowWindow/CreateWindow) - no mock
// Mock = gbengine interface + PAL3 own functions (migration)

#include <windows.h>
#include "../../mock/mock_interfaces.h"

// WinMain (Windows entry - migration start)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Window creation (system API - direct)
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = hInstance;
    wc.lpszClassName = "PAL3Manual";
    RegisterClassA(&wc);
    HWND hWnd = CreateWindowA("PAL3Manual", "PAL3 Manual", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (!hWnd) return 1;
    ShowWindow(hWnd, nCmdShow);

    // Game init (mock - TODO: gbengine/migrated)
    if (!Mock_LoadResources()) return 1;
    if (!Mock_InitGameState()) return 1;

    // Main loop (mock - TODO: migrated)
    while (true) {
        int msgResult = Mock_MessageLoop();
        if (msgResult != 0) break;
        Mock_UpdateGame();
        Mock_RenderFrame();
    }

    // Shutdown (mock - TODO: migrated)
    Mock_FreeResources();
    Mock_Shutdown();
    return 0;
}
