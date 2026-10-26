// manual/pal3/platform/windows/WinMain.cpp — Windows 入口（手动改写版）
// 独立于 codegen（pal3/src=生成物·codegen 覆盖）——手动改写域（manual/）
//
// 迁移起点 2026-10-27（逐步代换方案——主入口起）
// 平台分层：manual/pal3/platform/windows（后续 linux/android 适配）
// 来源：original/PAL3.exe 的 _WinMain@16（0x541900——skip_functions 定位）
//
// 迁移策略：codegen 输出+关键接口 mock→可编译→调用链推进→可运行→字节一致
// codegen 成果吸收：函数体从 pal3/src 搬移（byte-identical 修复）

#include <windows.h>
#include "../../mock/mock_interfaces.h"

// WinMain（Windows 入口——迁移起点）
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 初始化（窗口/资源/游戏状态）——mock（TODO: codegen 迁移）
    if (!Mock_InitWindow(hInstance, nCmdShow)) return 1;
    HWND hWnd = Mock_CreateMainWindow(hInstance, nCmdShow);
    if (!hWnd) return 1;
    if (!Mock_ShowWindow(hWnd, nCmdShow)) return 1;
    if (!Mock_LoadResources()) return 1;
    if (!Mock_InitGameState()) return 1;

    // 主循环（消息/渲染/逻辑）——mock（TODO: codegen 迁移）
    while (true) {
        int msgResult = Mock_MessageLoop();
        if (msgResult != 0) break;  // 退出条件
        Mock_UpdateGame();
        Mock_RenderFrame();
    }

    // 退出（清理）——mock（TODO: codegen 迁移）
    Mock_FreeResources();
    Mock_Shutdown();
    return 0;
}
