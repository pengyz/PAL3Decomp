// manual/pal3/mock/mock_interfaces.cpp - mock interfaces (temporary, replace with real)
// TODO: replace with real functions (codegen migration)

#include "mock_interfaces.h"

// Window mock
BOOL Mock_InitWindow(HINSTANCE hInstance, int nCmdShow) {
    // TODO: real function (window class registration)
    return TRUE;
}

HWND Mock_CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    // TODO: real function (window creation)
    return NULL;
}

BOOL Mock_ShowWindow(HWND hWnd, int nCmdShow) {
    // TODO: real function (window show)
    return TRUE;
}

// Message mock
int Mock_MessageLoop() {
    // TODO: real function (message loop)
    return 0;
}

LRESULT Mock_HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // TODO: real function (message handling)
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Resource mock
BOOL Mock_LoadResources() {
    // TODO: real function (resource loading)
    return TRUE;
}

void Mock_FreeResources() {
    // TODO: real function (resource release)
}

// Game state mock
BOOL Mock_InitGameState() {
    // TODO: real function (game state init)
    return TRUE;
}

void Mock_UpdateGame() {
    // TODO: real function (game update)
}

void Mock_RenderFrame() {
    // TODO: real function (render)
}

void Mock_Shutdown() {
    // TODO: real function (cleanup)
}
