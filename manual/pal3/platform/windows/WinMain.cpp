// manual/pal3/platform/windows/WinMain.cpp - Windows entry (migration from original)
// Source: PAL3::CheckSystemRequire (0x406310) + WinProc (0x404d60) + _WinMain@16 (0x541900)
// Original game logic: window class + WinProc (message handling) + game loop

#include <windows.h>
#include "../../mock/mock_interfaces.h"

// WinProc (migration from original 0x404d60 - window procedure)
int __stdcall WinProc(HWND hWnd, UINT Msg, unsigned int pvParam, LPARAM lParam) {
    // Message handling (from original WinProc 0x404d60)
    if (Msg > WM_AFXFIRST) {
        if (Msg == WM_CHAR) {
            // TODO: Logger::WinProc_HWND_InputLine
        } else {
            if (Msg != WM_SYSCOMMAND) {
                if (Msg == WM_MOUSEMOVE) {
                    // TODO: mouse move handling (UIQuadManager)
                }
                return DefWindowProcA(hWnd, Msg, pvParam, lParam);
            }
            // WM_SYSCOMMAND handling (macros instead of numbers)
            if (pvParam > SC_MOUSEMENU) {
                if (pvParam != SC_TASKLIST && pvParam != SC_SCREENSAVE && pvParam != SC_HOTKEY)
                    return DefWindowProcA(hWnd, Msg, pvParam, lParam);
            } else if (pvParam != SC_MOVE && pvParam != SC_SIZE && pvParam != SC_MINIMIZE && pvParam != SC_MAXIMIZE) {
                return DefWindowProcA(hWnd, Msg, pvParam, lParam);
            }
        }
        return 0;
    }
    if (Msg == WM_COPYDATA) {
        // TODO: Logger::WinProc_HWND_SetAndExec
        return DefWindowProcA(hWnd, Msg, pvParam, lParam);
    }
    switch (Msg) {
        case WM_CREATE:
            pvParam = 0;
            SystemParametersInfoA(SPI_SETSCREENSAVERRUNNING, 1, 0, 0);
            SystemParametersInfoA(SPI_SETMOUSETRAILS, 1, 0, 0);
            SystemParametersInfoA(SPI_SETMOUSE, 1, &pvParam, 0);
            SystemParametersInfoA(SPI_SETSCREENSAVERRUNNING, 1, &pvParam, 0);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcA(hWnd, Msg, pvParam, lParam);
    }
}

// WinMain (migration from original game logic)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Window class registration (from CheckSystemRequire 0x406310)
    CHAR ClassName[20];
    strcpy(ClassName, "PAL3--SOFTSTAR.sh");
    WNDCLASSA WndClass;
    WndClass.style = 32;
    WndClass.lpfnWndProc = (LRESULT (__stdcall *)(HWND__ *,unsigned int,unsigned int,long))WinProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    memset(&WndClass.hIcon, 0, 16);
    WndClass.lpszClassName = ClassName;
    if (!RegisterClassA(&WndClass)) return 1;

    // Window creation
    HWND hWnd = CreateWindowA(ClassName, "PAL3--SOFTSTAR.sh", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (!hWnd) return 1;
    ShowWindow(hWnd, nCmdShow);

    // Game init (mock - TODO: migrate from original)
    if (!Mock_LoadResources()) return 1;
    if (!Mock_InitGameState()) return 1;

    // Main loop (mock - TODO: migrate from original)
    while (true) {
        int msgResult = Mock_MessageLoop();
        if (msgResult != 0) break;
        Mock_UpdateGame();
        Mock_RenderFrame();
    }

    // Shutdown (mock - TODO: migrate from original)
    Mock_FreeResources();
    Mock_Shutdown();
    return 0;
}
