// manual/pal3/mock/mock_interfaces.h — 关键接口 mock（临时——代换替）
// 缺依赖 mock（窗口/消息/资源）——可编译解锁
// 迁移策略：mock→实函数（调用链推进时逐个替换）

#ifndef MOCK_INTERFACES_H
#define MOCK_INTERFACES_H

#include <windows.h>

// 窗口 mock（初始化/创建/显示）
BOOL Mock_InitWindow(HINSTANCE hInstance, int nCmdShow);
HWND Mock_CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
BOOL Mock_ShowWindow(HWND hWnd, int nCmdShow);

// 消息 mock（主循环/消息处理）
int Mock_MessageLoop();
LRESULT Mock_HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 资源 mock（加载/释放）
BOOL Mock_LoadResources();
void Mock_FreeResources();

// 游戏状态 mock（初始化/更新/渲染/退出）
BOOL Mock_InitGameState();
void Mock_UpdateGame();
void Mock_RenderFrame();
void Mock_Shutdown();

#endif // MOCK_INTERFACES_H
