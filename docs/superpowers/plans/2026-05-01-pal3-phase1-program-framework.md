# PAL3.exe Phase 1: 程序框架和主循环 - 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 实现游戏骨架，能启动窗口、初始化 DirectX 和 gbengine、进入主游戏循环

**Architecture:** WinMain 入口 → 窗口创建 → DirectX/gbengine 初始化 → 主循环 → 清理

**Tech Stack:** Win32 API, DirectX 9, gbengine.dll, MSVC 2022

**工期:** 1 个月  
**函数数:** 50-100 个  
**代码行数:** 2000-3000 行

---

## 前置条件

- ✅ Phase 0 已完成（基础设施搭建）
- ✅ Ghidra 分析完成
- ✅ 编译系统可用
- ✅ 导入库已生成

---

## 文件结构

将创建的文件：
```
src/pal3/
├── main.cpp                    # WinMain 入口（已存在，需扩展）
├── game_init.cpp               # 游戏初始化
├── game_init.h
├── game_loop.cpp               # 主游戏循环
├── game_loop.h
├── game_shutdown.cpp           # 游戏清理
├── game_shutdown.h
├── window.cpp                  # 窗口管理
├── window.h
├── d3d_init.cpp                # DirectX 初始化
├── d3d_init.h
├── gbengine_wrapper.cpp        # gbengine 接口包装
├── gbengine_wrapper.h
└── config.cpp                  # 配置管理
    config.h

include/pal3/
├── game_types.h                # 基本类型定义
├── game_globals.h              # 全局变量声明
└── pch.h                       # 预编译头（可选）

include/external/
├── gbengine.h                  # gbengine 完整接口（扩展）
└── topo.h                      # topo 完整接口（扩展）
```

---

## Task 1: 定义游戏全局类型和变量

**Files:**
- Create: `include/pal3/game_types.h`
- Create: `include/pal3/game_globals.h`

- [ ] **Step 1: 创建基本类型定义**

```cpp
// include/pal3/game_types.h
#pragma once

#include <windows.h>

/**
 * PAL3 基本类型定义
 * 
 * 定义游戏中使用的基本数据类型
 */

// 基本类型别名
typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef int             BOOL;

// 句柄类型
typedef void*           GBHANDLE;    // gbengine 句柄
typedef void*           TOPOHANDLE;  // topo 句柄

// 游戏状态
enum GameState {
    GAME_STATE_NONE = 0,
    GAME_STATE_INIT,
    GAME_STATE_MENU,
    GAME_STATE_LOADING,
    GAME_STATE_RUNNING,
    GAME_STATE_PAUSED,
    GAME_STATE_SHUTDOWN
};

// 配置结构
struct GameConfig {
    BOOL    windowed;           // 窗口模式
    int     screenWidth;        // 屏幕宽度
    int     screenHeight;       // 屏幕高度
    int     colorDepth;         // 色深
    BOOL    vsync;              // 垂直同步
    int     soundVolume;        // 音量
    int     musicVolume;        // 音乐音量
    BOOL    enableDebug;        // 调试模式
};

// 性能统计
struct PerformanceStats {
    float   fps;                // 当前 FPS
    float   frameTime;          // 帧时间（毫秒）
    int     triangleCount;      // 三角形数
    int     drawCallCount;      // 绘制调用数
};
```

- [ ] **Step 2: 创建全局变量声明**

```cpp
// include/pal3/game_globals.h
#pragma once

#include "game_types.h"
#include <d3d9.h>

/**
 * PAL3 全局变量声明
 * 
 * 声明所有全局变量，实际定义在各个 .cpp 文件中
 */

// ============================================================================
// 窗口相关
// ============================================================================
extern HINSTANCE    g_hInstance;        // 程序实例句柄
extern HWND         g_hWnd;             // 主窗口句柄
extern BOOL         g_bActive;          // 窗口是否激活
extern BOOL         g_bMinimized;       // 窗口是否最小化

// ============================================================================
// DirectX 相关
// ============================================================================
extern IDirect3D9*          g_pD3D;         // Direct3D 对象
extern IDirect3DDevice9*    g_pd3dDevice;   // D3D 设备

// ============================================================================
// gbengine 相关
// ============================================================================
extern GBHANDLE     g_pRenderDevice;    // 渲染设备
extern GBHANDLE     g_pResourceManager; // 资源管理器
extern GBHANDLE     g_pInputManager;    // 输入管理器
extern GBHANDLE     g_pAudioManager;    // 音频管理器
extern GBHANDLE     g_pSceneManager;    // 场景管理器

// ============================================================================
// 游戏状态
// ============================================================================
extern GameState    g_gameState;        // 当前游戏状态
extern BOOL         g_bGameRunning;     // 游戏是否运行中
extern GameConfig   g_config;           // 游戏配置

// ============================================================================
// 性能统计
// ============================================================================
extern PerformanceStats g_perfStats;    // 性能统计
extern float        g_deltaTime;        // 帧时间差（秒）

// ============================================================================
// 时间
// ============================================================================
extern LARGE_INTEGER    g_frequency;    // 性能计数器频率
extern LARGE_INTEGER    g_lastTime;     // 上一帧时间
```

- [ ] **Step 3: 编译验证**

```bash
cd D:/workspace/project-x/build
cmake --build . --config Release
```

Expected: 编译成功（虽然还没有实际使用这些声明）

- [ ] **Step 4: 提交类型定义**

```bash
git add include/pal3/game_types.h
git add include/pal3/game_globals.h
git commit -m "feat(phase1): define game types and globals

- GameState enum
- GameConfig and PerformanceStats structs
- Global variables for window, D3D, gbengine
- Type aliases and handle definitions"
```

Expected: Git 提交成功

---

## Task 2: 实现窗口创建和消息处理

**Files:**
- Create: `src/pal3/window.h`
- Create: `src/pal3/window.cpp`

- [ ] **Step 1: 创建窗口管理头文件**

```cpp
// src/pal3/window.h
#pragma once

#include <windows.h>

/**
 * 窗口管理模块
 * 
 * 负责创建和管理游戏窗口，处理 Windows 消息
 */

// 窗口创建
BOOL Window_Create(HINSTANCE hInstance, int nCmdShow);

// 窗口销毁
void Window_Destroy();

// 窗口过程
LRESULT CALLBACK Window_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 窗口居中
void Window_Center(HWND hWnd);

// 设置窗口标题
void Window_SetTitle(HWND hWnd, const char* title);
```

- [ ] **Step 2: 实现窗口创建**

```cpp
// src/pal3/window.cpp
#include "window.h"
#include "../include/pal3/game_globals.h"
#include "../include/pal3/game_types.h"
#include <stdio.h>

// 全局变量定义（在 game_globals.h 中声明）
HINSTANCE   g_hInstance = NULL;
HWND        g_hWnd = NULL;
BOOL        g_bActive = TRUE;
BOOL        g_bMinimized = FALSE;

// 0x004XXXXX  Window_Create
BOOL Window_Create(HINSTANCE hInstance, int nCmdShow)
{
    g_hInstance = hInstance;
    
    // 注册窗口类
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = Window_WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "PAL3";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    if (!RegisterClassEx(&wc)) {
        MessageBoxA(NULL, "注册窗口类失败", "错误", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    // 计算窗口大小（客户区 = 配置的分辨率）
    DWORD style = g_config.windowed 
        ? (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
        : WS_POPUP;
    
    RECT rect = { 0, 0, g_config.screenWidth, g_config.screenHeight };
    AdjustWindowRect(&rect, style, FALSE);
    
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;
    
    // 创建窗口
    g_hWnd = CreateWindowEx(
        0,
        "PAL3",
        "仙剑奇侠传三",
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowWidth,
        windowHeight,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (!g_hWnd) {
        MessageBoxA(NULL, "创建窗口失败", "错误", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    // 窗口居中
    Window_Center(g_hWnd);
    
    // 显示窗口
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);
    
    return TRUE;
}

// 0x004XXXXX  Window_Destroy
void Window_Destroy()
{
    if (g_hWnd) {
        DestroyWindow(g_hWnd);
        g_hWnd = NULL;
    }
    
    if (g_hInstance) {
        UnregisterClass("PAL3", g_hInstance);
    }
}

// 0x004XXXXX  Window_WndProc
LRESULT CALLBACK Window_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
        case WM_ACTIVATE:
            // 窗口激活/非激活
            g_bActive = (LOWORD(wParam) != WA_INACTIVE);
            return 0;
        
        case WM_SIZE:
            // 窗口大小改变
            if (wParam == SIZE_MINIMIZED) {
                g_bMinimized = TRUE;
                g_bActive = FALSE;
            } else {
                g_bMinimized = FALSE;
                g_bActive = TRUE;
            }
            return 0;
        
        case WM_CLOSE:
            // 关闭窗口
            g_bGameRunning = FALSE;
            return 0;
        
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        
        case WM_KEYDOWN:
            // 按键按下
            if (wParam == VK_ESCAPE) {
                g_bGameRunning = FALSE;
            }
            return 0;
        
        case WM_SYSKEYDOWN:
            // Alt+Enter 切换全屏
            if (wParam == VK_RETURN && (lParam & (1 << 29))) {
                // TODO: 切换全屏模式
            }
            return 0;
    }
    
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// 0x004XXXXX  Window_Center
void Window_Center(HWND hWnd)
{
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);
    
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;
    
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;
    
    SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// 0x004XXXXX  Window_SetTitle
void Window_SetTitle(HWND hWnd, const char* title)
{
    SetWindowTextA(hWnd, title);
}
```

- [ ] **Step 3: 更新 CMakeLists.txt 添加新文件**

```cmake
# CMakeLists.txt（修改 PAL3_SOURCES）
set(PAL3_SOURCES
    src/pal3/main.cpp
    src/pal3/window.cpp
)
```

- [ ] **Step 4: 编译测试**

```bash
cd D:/workspace/project-x/build
cmake --build . --config Release
```

Expected: 编译成功

- [ ] **Step 5: 提交窗口模块**

```bash
git add src/pal3/window.h
git add src/pal3/window.cpp
git add CMakeLists.txt
git commit -m "feat(phase1): implement window management

- Window creation with configurable size
- Window procedure with message handling
- Window centering and title setting
- Support windowed/fullscreen mode
- 5 functions implemented"
```

Expected: Git 提交成功

---

## Task 3: 实现 DirectX 初始化

**Files:**
- Create: `src/pal3/d3d_init.h`
- Create: `src/pal3/d3d_init.cpp`

- [ ] **Step 1: 创建 DirectX 初始化头文件**

```cpp
// src/pal3/d3d_init.h
#pragma once

#include <windows.h>

/**
 * DirectX 9 初始化模块
 * 
 * 负责初始化 Direct3D 设备和相关资源
 */

// DirectX 初始化
BOOL D3D_Initialize();

// DirectX 清理
void D3D_Shutdown();

// 检查硬件能力
BOOL D3D_CheckCapabilities();

// 重置设备
BOOL D3D_Reset();

// 设备丢失处理
BOOL D3D_HandleDeviceLost();
```

- [ ] **Step 2: 实现 DirectX 初始化**

```cpp
// src/pal3/d3d_init.cpp
#include "d3d_init.h"
#include "../include/pal3/game_globals.h"
#include "../include/pal3/game_types.h"
#include <d3d9.h>
#include <stdio.h>

#pragma comment(lib, "d3d9.lib")

// 全局变量定义
IDirect3D9*         g_pD3D = NULL;
IDirect3DDevice9*   g_pd3dDevice = NULL;

// 0x004XXXXX  D3D_Initialize
BOOL D3D_Initialize()
{
    // 创建 Direct3D 对象
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!g_pD3D) {
        MessageBoxA(NULL, "创建 Direct3D 对象失败", "错误", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    // 获取显示模式
    D3DDISPLAYMODE d3ddm;
    HRESULT hr = g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
    if (FAILED(hr)) {
        MessageBoxA(NULL, "获取显示模式失败", "错误", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    // 设置呈现参数
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    
    if (g_config.windowed) {
        // 窗口模式
        d3dpp.Windowed = TRUE;
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp.BackBufferFormat = d3ddm.Format;
    } else {
        // 全屏模式
        d3dpp.Windowed = FALSE;
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp.BackBufferWidth = g_config.screenWidth;
        d3dpp.BackBufferHeight = g_config.screenHeight;
        d3dpp.BackBufferFormat = (g_config.colorDepth == 32) 
            ? D3DFMT_X8R8G8B8 
            : D3DFMT_R5G6B5;
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    }
    
    // 深度/模板缓冲
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    
    // 垂直同步
    d3dpp.PresentationInterval = g_config.vsync 
        ? D3DPRESENT_INTERVAL_ONE 
        : D3DPRESENT_INTERVAL_IMMEDIATE;
    
    // 多重采样
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    
    // 创建设备
    hr = g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        g_hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &g_pd3dDevice
    );
    
    if (FAILED(hr)) {
        // 尝试软件顶点处理
        hr = g_pD3D->CreateDevice(
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            g_hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &d3dpp,
            &g_pd3dDevice
        );
        
        if (FAILED(hr)) {
            MessageBoxA(NULL, "创建 Direct3D 设备失败", "错误", MB_OK | MB_ICONERROR);
            return FALSE;
        }
    }
    
    // 检查硬件能力
    if (!D3D_CheckCapabilities()) {
        MessageBoxA(NULL, "显卡不支持游戏所需功能", "错误", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    // 设置渲染状态
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    
    return TRUE;
}

// 0x004XXXXX  D3D_Shutdown
void D3D_Shutdown()
{
    if (g_pd3dDevice) {
        g_pd3dDevice->Release();
        g_pd3dDevice = NULL;
    }
    
    if (g_pD3D) {
        g_pD3D->Release();
        g_pD3D = NULL;
    }
}

// 0x004XXXXX  D3D_CheckCapabilities
BOOL D3D_CheckCapabilities()
{
    D3DCAPS9 caps;
    HRESULT hr = g_pd3dDevice->GetDeviceCaps(&caps);
    if (FAILED(hr)) {
        return FALSE;
    }
    
    // 检查 Pixel Shader 版本
    if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1)) {
        MessageBoxA(NULL, 
            "显卡不支持 Pixel Shader 1.1\n游戏需要支持 Pixel Shader 的显卡",
            "警告", MB_OK | MB_ICONWARNING);
        return FALSE;
    }
    
    // 检查顶点着色器版本
    if (caps.VertexShaderVersion < D3DVS_VERSION(1, 1)) {
        // 可以使用软件顶点处理，只给警告
        MessageBoxA(NULL,
            "显卡不支持 Vertex Shader 1.1\n将使用软件顶点处理，性能可能较低",
            "警告", MB_OK | MB_ICONWARNING);
    }
    
    return TRUE;
}

// 0x004XXXXX  D3D_Reset
BOOL D3D_Reset()
{
    if (!g_pd3dDevice) {
        return FALSE;
    }
    
    // 构建呈现参数
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    
    d3dpp.Windowed = g_config.windowed;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferWidth = g_config.screenWidth;
    d3dpp.BackBufferHeight = g_config.screenHeight;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.PresentationInterval = g_config.vsync 
        ? D3DPRESENT_INTERVAL_ONE 
        : D3DPRESENT_INTERVAL_IMMEDIATE;
    
    // 重置设备
    HRESULT hr = g_pd3dDevice->Reset(&d3dpp);
    if (FAILED(hr)) {
        return FALSE;
    }
    
    // 恢复渲染状态
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    
    return TRUE;
}

// 0x004XXXXX  D3D_HandleDeviceLost
BOOL D3D_HandleDeviceLost()
{
    if (!g_pd3dDevice) {
        return FALSE;
    }
    
    HRESULT hr = g_pd3dDevice->TestCooperativeLevel();
    
    if (hr == D3DERR_DEVICELOST) {
        // 设备丢失，等待
        Sleep(50);
        return FALSE;
    }
    
    if (hr == D3DERR_DEVICENOTRESET) {
        // 设备可以重置
        return D3D_Reset();
    }
    
    return TRUE;
}
```

- [ ] **Step 3: 更新 CMakeLists.txt**

```cmake
set(PAL3_SOURCES
    src/pal3/main.cpp
    src/pal3/window.cpp
    src/pal3/d3d_init.cpp
)

# 添加 DirectX 库
target_link_libraries(PAL3 PRIVATE
    # ... 其他库 ...
    d3d9.lib
    d3dx9.lib
    dxguid.lib
)
```

- [ ] **Step 4: 编译测试**

```bash
cd D:/workspace/project-x/build
cmake --build . --config Release
```

Expected: 编译成功

- [ ] **Step 5: 提交 DirectX 模块**

```bash
git add src/pal3/d3d_init.h
git add src/pal3/d3d_init.cpp
git add CMakeLists.txt
git commit -m "feat(phase1): implement DirectX initialization

- D3D9 device creation
- Hardware capability checking
- Window/fullscreen mode support
- Device lost handling
- 5 functions implemented"
```

Expected: Git 提交成功

---

## Task 4: 实现配置管理

**Files:**
- Create: `src/pal3/config.h`
- Create: `src/pal3/config.cpp`

- [ ] **Step 1: 创建配置管理头文件**

```cpp
// src/pal3/config.h
#pragma once

#include <windows.h>

/**
 * 配置管理模块
 * 
 * 负责读取和保存游戏配置
 */

// 加载配置
BOOL Config_Load();

// 保存配置
BOOL Config_Save();

// 恢复默认配置
void Config_RestoreDefaults();

// 解析命令行参数
void Config_ParseCommandLine(LPSTR lpCmdLine);
```

- [ ] **Step 2: 实现配置管理**

```cpp
// src/pal3/config.cpp
#include "config.h"
#include "../include/pal3/game_globals.h"
#include "../include/pal3/game_types.h"
#include <stdio.h>

// 全局变量定义
GameConfig g_config;

// 配置文件路径
#define CONFIG_FILE "PAL3.ini"

// 0x004XXXXX  Config_Load
BOOL Config_Load()
{
    // 先设置默认值
    Config_RestoreDefaults();
    
    // 读取配置文件
    char buffer[256];
    
    // [Display]
    GetPrivateProfileStringA("Display", "Windowed", "1", buffer, sizeof(buffer), CONFIG_FILE);
    g_config.windowed = (buffer[0] == '1');
    
    g_config.screenWidth = GetPrivateProfileIntA("Display", "Width", 800, CONFIG_FILE);
    g_config.screenHeight = GetPrivateProfileIntA("Display", "Height", 600, CONFIG_FILE);
    g_config.colorDepth = GetPrivateProfileIntA("Display", "ColorDepth", 32, CONFIG_FILE);
    
    GetPrivateProfileStringA("Display", "VSync", "1", buffer, sizeof(buffer), CONFIG_FILE);
    g_config.vsync = (buffer[0] == '1');
    
    // [Audio]
    g_config.soundVolume = GetPrivateProfileIntA("Audio", "SoundVolume", 100, CONFIG_FILE);
    g_config.musicVolume = GetPrivateProfileIntA("Audio", "MusicVolume", 100, CONFIG_FILE);
    
    // [Debug]
    GetPrivateProfileStringA("Debug", "Enable", "0", buffer, sizeof(buffer), CONFIG_FILE);
    g_config.enableDebug = (buffer[0] == '1');
    
    return TRUE;
}

// 0x004XXXXX  Config_Save
BOOL Config_Save()
{
    char buffer[256];
    
    // [Display]
    WritePrivateProfileStringA("Display", "Windowed", 
        g_config.windowed ? "1" : "0", CONFIG_FILE);
    
    sprintf(buffer, "%d", g_config.screenWidth);
    WritePrivateProfileStringA("Display", "Width", buffer, CONFIG_FILE);
    
    sprintf(buffer, "%d", g_config.screenHeight);
    WritePrivateProfileStringA("Display", "Height", buffer, CONFIG_FILE);
    
    sprintf(buffer, "%d", g_config.colorDepth);
    WritePrivateProfileStringA("Display", "ColorDepth", buffer, CONFIG_FILE);
    
    WritePrivateProfileStringA("Display", "VSync",
        g_config.vsync ? "1" : "0", CONFIG_FILE);
    
    // [Audio]
    sprintf(buffer, "%d", g_config.soundVolume);
    WritePrivateProfileStringA("Audio", "SoundVolume", buffer, CONFIG_FILE);
    
    sprintf(buffer, "%d", g_config.musicVolume);
    WritePrivateProfileStringA("Audio", "MusicVolume", buffer, CONFIG_FILE);
    
    // [Debug]
    WritePrivateProfileStringA("Debug", "Enable",
        g_config.enableDebug ? "1" : "0", CONFIG_FILE);
    
    return TRUE;
}

// 0x004XXXXX  Config_RestoreDefaults
void Config_RestoreDefaults()
{
    g_config.windowed = TRUE;
    g_config.screenWidth = 800;
    g_config.screenHeight = 600;
    g_config.colorDepth = 32;
    g_config.vsync = TRUE;
    g_config.soundVolume = 100;
    g_config.musicVolume = 100;
    g_config.enableDebug = FALSE;
}

// 0x004XXXXX  Config_ParseCommandLine
void Config_ParseCommandLine(LPSTR lpCmdLine)
{
    if (!lpCmdLine || !*lpCmdLine) {
        return;
    }
    
    // 简单的命令行解析
    char* token = strtok(lpCmdLine, " ");
    
    while (token != NULL) {
        if (_stricmp(token, "-window") == 0) {
            g_config.windowed = TRUE;
        }
        else if (_stricmp(token, "-fullscreen") == 0) {
            g_config.windowed = FALSE;
        }
        else if (_stricmp(token, "-width") == 0) {
            token = strtok(NULL, " ");
            if (token) {
                g_config.screenWidth = atoi(token);
            }
        }
        else if (_stricmp(token, "-height") == 0) {
            token = strtok(NULL, " ");
            if (token) {
                g_config.screenHeight = atoi(token);
            }
        }
        else if (_stricmp(token, "-debug") == 0) {
            g_config.enableDebug = TRUE;
        }
        
        token = strtok(NULL, " ");
    }
}
```

- [ ] **Step 3: 更新 CMakeLists.txt**

```cmake
set(PAL3_SOURCES
    src/pal3/main.cpp
    src/pal3/window.cpp
    src/pal3/d3d_init.cpp
    src/pal3/config.cpp
)
```

- [ ] **Step 4: 编译测试**

```bash
cd D:/workspace/project-x/build
cmake --build . --config Release
```

Expected: 编译成功

- [ ] **Step 5: 提交配置模块**

```bash
git add src/pal3/config.h
git add src/pal3/config.cpp
git add CMakeLists.txt
git commit -m "feat(phase1): implement configuration management

- Load/save config from PAL3.ini
- Command line argument parsing
- Default configuration
- Support display and audio settings
- 4 functions implemented"
```

Expected: Git 提交成功

---

---

## Task 5-10: 概要说明

由于Phase 1剩余任务遵循类似模式，以下提供概要级别的任务描述。实际执行时可展开为详细步骤。

---

## Task 5: gbengine 接口包装 (10-15 个函数)

**目标:** 创建 gbengine.dll 的 C++ 包装层，提供类型安全的接口

**关键文件:**
- `src/pal3/gbengine_wrapper.h` - 包装接口声明
- `src/pal3/gbengine_wrapper.cpp` - 包装实现
- `include/external/gbengine.h` - 完整的 gbengine 接口定义（~1000个函数）

**主要函数:**
- `GBEngine_Initialize()` - 初始化所有 gbengine 子系统
- `GBEngine_Shutdown()` - 清理 gbengine
- `GBEngine_CheckVersion()` - 版本兼容性检查
- 各子系统包装函数（Render, Resource, Input, Audio, Scene）

**字节匹配提示:** 简单的包装函数通常能达到 95%+ 匹配率

---

## Task 6: 游戏初始化主流程 (8-12 个函数)

**目标:** 实现完整的游戏初始化流程

**关键文件:**
- `src/pal3/game_init.h`
- `src/pal3/game_init.cpp`

**主要函数:**
- `Game_Initialize(HINSTANCE)` - 主初始化函数
- `Game_InitWindow()` - 窗口初始化
- `Game_InitDirectX()` - DirectX 初始化
- `Game_InitGBEngine()` - gbengine 初始化
- `Game_InitSubsystems()` - 子系统初始化（Script, UI, Audio等）
- `Game_LoadStartupResources()` - 加载启动资源

**初始化顺序（关键）:**
1. 加载配置
2. 解析命令行
3. 创建窗口
4. 初始化 DirectX
5. 初始化 gbengine
6. 初始化各游戏子系统
7. 加载启动资源

---

## Task 7: 主游戏循环 (12-18 个函数)

**目标:** 实现游戏主循环，包含更新和渲染逻辑

**关键文件:**
- `src/pal3/game_loop.h`
- `src/pal3/game_loop.cpp`

**主要函数:**
- `Game_MainLoop()` - 主循环函数
- `Game_ProcessMessages()` - 处理 Windows 消息
- `Game_Update(deltaTime)` - 更新游戏逻辑
- `Game_Render()` - 渲染场景
- `Game_UpdateInput()` - 更新输入状态
- `Game_UpdateFPS()` - 计算 FPS
- `Game_LimitFrameRate()` - 限制帧率

**循环结构（MSVC 7.1 优化）:**
```cpp
while (g_bGameRunning) {
    // 消息处理
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            g_bGameRunning = FALSE;
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    if (!g_bGameRunning) break;
    
    // 计算帧时间
    CalculateDeltaTime();
    
    // 更新
    Game_Update(g_deltaTime);
    
    // 渲染
    Game_Render();
    
    // 帧率限制
    Sleep(1);
}
```

---

## Task 8: 游戏清理 (6-10 个函数)

**目标:** 实现游戏退出时的清理逻辑

**关键文件:**
- `src/pal3/game_shutdown.h`
- `src/pal3/game_shutdown.cpp`

**主要函数:**
- `Game_Shutdown()` - 主清理函数
- `Game_ShutdownSubsystems()` - 清理子系统
- `Game_ShutdownGBEngine()` - 清理 gbengine
- `Game_ShutdownDirectX()` - 清理 DirectX
- `Game_ShutdownWindow()` - 销毁窗口
- `Game_SaveConfig()` - 保存配置

**清理顺序（与初始化相反）:**
1. 清理子系统（Script, UI, Audio）
2. 清理 gbengine
3. 清理 DirectX
4. 销毁窗口
5. 保存配置

---

## Task 9: 完整 WinMain 实现 (1 个核心函数)

**目标:** 实现完整的程序入口点

**关键文件:**
- `src/pal3/main.cpp` - 替换骨架代码

**WinMain 函数 (地址: 0x0055507C, ~200 bytes):**
```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    // 1. 解析命令行
    Config_ParseCommandLine(lpCmdLine);
    
    // 2. 检查单实例
    HANDLE hMutex = CreateMutexA(NULL, FALSE, "PAL3_MUTEX");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBoxA(NULL, "游戏已在运行", "错误", MB_OK);
        CloseHandle(hMutex);
        return 1;
    }
    
    // 3. 初始化 COM
    CoInitialize(NULL);
    
    // 4. 加载配置
    Config_Load();
    
    // 5. 初始化游戏
    if (!Game_Initialize(hInstance)) {
        MessageBoxA(NULL, "游戏初始化失败", "错误", MB_OK);
        Game_Shutdown();
        CoUninitialize();
        CloseHandle(hMutex);
        return 1;
    }
    
    // 6. 进入主循环
    int result = Game_MainLoop();
    
    // 7. 清理
    Game_Shutdown();
    Config_Save();
    CoUninitialize();
    CloseHandle(hMutex);
    
    return result;
}
```

**字节匹配提示:**
- 变量声明顺序: `HANDLE hMutex`, `int result`
- 使用 `if (condition)` 而不是 `if (condition != FALSE)`
- 使用 `!= ERROR_ALREADY_EXISTS` 而不是 `== ERROR_SUCCESS`

---

## Task 10: Phase 1 字节匹配调优

**目标:** 对所有已实现函数进行字节匹配调优，达到 80%+ 整体匹配率

**方法:**
1. 使用 `compare_exe.py` 批量对比所有函数
2. 识别不匹配的函数
3. 应用匹配技术库中的技巧
4. 迭代调优直到达到目标

**重点函数（必须 100% 匹配）:**
- WinMain (0x0055507C)
- Game_MainLoop
- Window_WndProc

**匹配技术应用:**
- 变量声明顺序调整
- 循环形式转换 (`for (i=0; i!=n; i++)`)
- 条件表达式简化 (`if (ptr)` vs `if (ptr != NULL)`)
- 内联控制 (`__forceinline` vs `__declspec(noinline)`)

---

## Phase 1 验收标准

完成以下所有项目后，Phase 1 即为完成：

### 功能验收
- [ ] 游戏能启动，显示窗口
- [ ] DirectX 设备初始化成功
- [ ] gbengine.dll 成功加载并初始化
- [ ] 进入主游戏循环（虽然没有实际游戏内容）
- [ ] FPS 显示正常
- [ ] 能正常退出并清理资源

### 代码验收
- [ ] 实现 50-100 个函数
- [ ] 所有代码编译无错误无警告
- [ ] 代码结构清晰，注释完整

### 字节匹配验收
- [ ] WinMain 100% 匹配
- [ ] 主循环 100% 匹配
- [ ] 窗口过程 100% 匹配
- [ ] 整体匹配率 ≥ 80%

### 测试验收
- [ ] 编译测试通过
- [ ] PE 结构验证通过
- [ ] 窗口显示正常
- [ ] DirectX 初始化成功
- [ ] 能运行至少 5 分钟无崩溃

### 文档验收
- [ ] Phase 1 完成报告
- [ ] 更新 STATUS.md
- [ ] 字节匹配技巧记录
- [ ] 已知问题列表

---

## Phase 1 完成报告模板

```markdown
# PAL3.exe Phase 1 完成报告

**完成日期:** 2026-XX-XX  
**工期:** X 周  
**进度:** 2-3%

## 实现统计
- 实现函数数: XX/~4500 (X.X%)
- 代码行数: XXXX 行
- 字节匹配率: XX%

## 主要成果
- ✅ 游戏窗口创建和消息处理
- ✅ DirectX 9 初始化
- ✅ gbengine.dll 集成
- ✅ 主游戏循环框架
- ✅ 配置管理系统

## 字节匹配情况
- WinMain: 100%
- 主循环: XX%
- 窗口过程: XX%
- 其他函数: XX%

## 已知问题
1. [列出遇到的问题和解决方案]

## 下一步: Phase 2
目标: 实现 SCE 脚本引擎（140 个操作码）
```

---

**Phase 1 计划完成！准备进入 Phase 2：脚本引擎**