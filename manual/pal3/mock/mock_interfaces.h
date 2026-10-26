// manual/pal3/mock/mock_interfaces.h - mock interfaces (temporary, replace with real)
// Migration: mock -> real functions (call chain advance)

#ifndef MOCK_INTERFACES_H
#define MOCK_INTERFACES_H

#include <windows.h>

// Window mock (init/create/show)
BOOL Mock_InitWindow(HINSTANCE hInstance, int nCmdShow);
HWND Mock_CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
BOOL Mock_ShowWindow(HWND hWnd, int nCmdShow);

// Message mock (main loop/handling)
int Mock_MessageLoop();
LRESULT Mock_HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Resource mock (load/free)
BOOL Mock_LoadResources();
void Mock_FreeResources();

// Game state mock (init/update/render/shutdown)
BOOL Mock_InitGameState();
void Mock_UpdateGame();
void Mock_RenderFrame();
void Mock_Shutdown();

#endif // MOCK_INTERFACES_H
