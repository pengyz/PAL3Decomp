// manual/pal3/mock/mock_interfaces.cpp — 关键接口 mock 实现（临时——代换替）
// TODO: 调用链推进时逐个替换为实函数（codegen 输出迁移）

#include "mock_interfaces.h"

// 窗口 mock
BOOL Mock_InitWindow(HINSTANCE hInstance, int nCmdShow) {
    // TODO: 实函数迁移（窗口类注册/初始化）
    return TRUE;
}

HWND Mock_CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    // TODO: 实函数迁移（窗口创建）
    return NULL;
}

BOOL Mock_ShowWindow(HWND hWnd, int nCmdShow) {
    // TODO: 实函数迁移（窗口显示）
    return TRUE;
}

// 消息 mock
int Mock_MessageLoop() {
    // TODO: 实函数迁移（消息循环）
    return 0;
}

LRESULT Mock_HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // TODO: 实函数迁移（消息处理）
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// 资源 mock
BOOL Mock_LoadResources() {
    // TODO: 实函数迁移（资源加载）
    return TRUE;
}

void Mock_FreeResources() {
    // TODO: 实函数迁移（资源释放）
}

// 游戏状态 mock
BOOL Mock_InitGameState() {
    // TODO: 实函数迁移（游戏状态初始化）
    return TRUE;
}

void Mock_UpdateGame() {
    // TODO: 实函数迁移（游戏更新）
}

void Mock_RenderFrame() {
    // TODO: 实函数迁移（渲染）
}

void Mock_Shutdown() {
    // TODO: 实函数迁移（清理）
}
