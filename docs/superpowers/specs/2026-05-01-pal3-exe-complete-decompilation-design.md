# PAL3.exe 完整反编译设计方案

**日期：** 2026-05-01  
**作者：** Claude Sonnet 4.5  
**项目：** PAL3.exe 匹配反编译  
**目标：** 100% 完整反编译，95%+ 核心函数字节精确匹配

---

## 1. 项目概述

### 1.1 项目目标

完整反编译仙剑奇侠传3主程序（PAL3.exe，2.1MB），生成可编译的 C/C++ 源代码，最终能够：
- 完全替换游戏目录中的原版 PAL3.exe
- 游戏正常启动、运行、无崩溃
- 核心函数达到 95%+ 字节精确匹配
- 整体字节匹配率达到 85%+
- 支持完整游戏流程（通关）

### 1.2 项目规模

- **二进制大小：** 2.1MB（脱壳后）
- **代码段大小：** ~1.4MB
- **预估函数数：** 3500-5000 个
- **预估工期：** 9-10 个月
- **字节匹配目标：** 95%+ 核心函数，85%+ 整体

### 1.3 技术栈

- **原始编译器：** MSVC 7.0/7.1 (Visual Studio .NET 2003)
- **开发编译器：** MSVC 2022（配置兼容模式）
- **目标平台：** Windows 32位 (x86)
- **静态链接：** MSVCRT 7.1, D3DX9
- **动态链接：** gbengine.dll, topo.dll, DirectX, Bink, Miles

### 1.4 依赖策略

- 使用**原版 gbengine.dll 和 topo.dll**
- 通过导入表调用引擎功能
- 独立开发 PAL3.exe，不依赖 DLL 反编译进度
- 后续可选择性替换为反编译版本 DLL

### 1.5 参考资源

- **PAL3patch（zhangboyang）**：完整的结构体定义和游戏修改代码
- **OpenPAL3（dontpanic92）**：Rust 重新实现，文件格式解析器
- **PAL3A.PDB**：gbengine.dll 的完整符号文件
- **topo.dll 反编译经验**：结构定义、字节匹配技术、测试验证流程

---

## 2. 整体架构

### 2.1 项目目录结构

```
project-x/
├── original/
│   ├── PAL3.exe                    # 脱壳后的原版 exe (2.1MB)
│   ├── gbengine.dll                # 原版引擎 DLL (1.3MB)
│   └── topo.dll                    # 原版数学库 DLL (104KB)
│
├── src/
│   └── pal3/                       # PAL3.exe 源代码
│       ├── main.cpp                # WinMain 入口点
│       ├── game_init.cpp           # 游戏初始化
│       ├── game_loop.cpp           # 主游戏循环
│       ├── script/                 # SCE 脚本引擎
│       │   ├── vm_core.cpp         # 虚拟机核心
│       │   ├── opcodes.cpp         # 操作码实现
│       │   └── script_loader.cpp   # 脚本加载
│       ├── ui/                     # UI 系统
│       │   ├── menu.cpp            # 菜单系统
│       │   ├── dialog.cpp          # 对话框
│       │   ├── hud.cpp             # 游戏 HUD
│       │   └── widgets/            # UI 组件
│       ├── battle/                 # 战斗系统
│       │   ├── battle_core.cpp     # 战斗核心逻辑
│       │   ├── skill_system.cpp    # 技能系统
│       │   ├── ai.cpp              # 战斗 AI
│       │   └── effects.cpp         # 战斗特效
│       ├── scene/                  # 场景管理
│       │   ├── scene_manager.cpp   # 场景管理器
│       │   ├── map_loader.cpp      # 地图加载
│       │   ├── collision.cpp       # 碰撞检测
│       │   └── camera.cpp          # 相机控制
│       ├── save/                   # 存档系统
│       │   ├── save_manager.cpp    # 存档管理
│       │   ├── encryption.cpp      # 加密解密
│       │   └── serialization.cpp   # 序列化
│       ├── audio/                  # 音频管理
│       ├── video/                  # 视频播放
│       ├── resource/               # 资源管理
│       └── utils/                  # 工具函数
│
├── include/
│   ├── pal3/                       # PAL3.exe 头文件
│   │   ├── game_types.h            # 游戏数据类型
│   │   ├── game_structs.h          # 游戏结构体
│   │   ├── game_globals.h          # 全局变量声明
│   │   └── modules/                # 各模块头文件
│   │       ├── script.h
│   │       ├── ui.h
│   │       ├── battle.h
│   │       ├── scene.h
│   │       └── save.h
│   └── external/                   # 外部依赖接口
│       ├── gbengine.h              # gbengine.dll 导入声明
│       ├── topo.h                  # topo.dll 导入声明
│       ├── directx9.h              # DirectX 9 接口
│       ├── bink.h                  # Bink Video 接口
│       └── miles.h                 # Miles Sound System
│
├── asm/
│   └── pal3/                       # Ghidra 导出数据
│       ├── functions/              # 函数 JSON（按地址）
│       │   ├── WinMain_00555XXX.json
│       │   ├── GameLoop_004XXXXX.json
│       │   └── ...（3500-5000 个）
│       ├── structs/                # 结构体定义
│       ├── globals/                # 全局变量
│       └── analysis/               # 分析结果
│           ├── function_classification.json
│           ├── call_graph.json
│           └── module_mapping.json
│
├── tools/
│   ├── ghidra/                     # Ghidra 分析脚本
│   │   ├── export_functions.py    # 导出函数 JSON
│   │   ├── analyze_structs.py     # 结构体分析
│   │   └── build_callgraph.py     # 构建调用图
│   ├── analyze_pal3.py             # PAL3.exe 函数分析器
│   ├── compare_exe.py              # 二进制对比工具
│   ├── progress_pal3.py            # 进度跟踪
│   ├── generate_import_lib.py     # 生成导入库
│   └── test_framework.py           # 自动化测试框架
│
├── build/
│   ├── pal3/                       # 编译输出
│   │   ├── PAL3.exe
│   │   ├── PAL3.map                # 内存映射
│   │   └── PAL3.pdb                # 调试符号
│   ├── libs/                       # 导入库
│   │   ├── gbengine.lib
│   │   └── topo.lib
│   └── reports/                    # 分析报告
│       ├── byte_matching.html
│       ├── function_coverage.txt
│       └── test_results.json
│
└── docs/
    └── pal3/                       # PAL3.exe 文档
        ├── architecture.md         # 架构设计文档
        ├── modules/                # 各模块设计文档
        │   ├── script_engine.md
        │   ├── ui_system.md
        │   ├── battle_system.md
        │   └── ...
        ├── matching_notes.md       # 字节匹配技巧记录
        ├── api_reference.md        # API 参考文档
        └── build_guide.md          # 构建指南
```

### 2.2 编译系统架构

```
PAL3.exe (2.1MB)
    │
    ├─ 静态链接
    │   ├─ MSVCRT 7.1 (C Runtime Library)
    │   ├─ D3DX9 静态库 (DirectX SDK Summer 2003)
    │   ├─ 异常处理代码 (MSVC generated)
    │   └─ C++ 标准库部分组件
    │
    └─ 动态链接（通过导入表）
        ├─ gbengine.dll (游戏引擎，~1000 个导入函数)
        ├─ topo.dll (数学库，~100 个导入函数)
        ├─ binkw32.dll (Bink 视频播放)
        ├─ Mss32.dll (Miles Sound System)
        ├─ dinput8.dll (DirectInput 8)
        ├─ KERNEL32.dll (Windows 核心 API)
        ├─ USER32.dll (Windows UI API)
        └─ ADVAPI32.dll (高级 Windows API)
```

### 2.3 内存布局（PE 结构）

```
基地址: 0x00400000

Section       起始地址      结束地址      大小        属性
----------   -----------   -----------   ---------   --------
.text        0x00401000    0x00569018    ~1.4 MB     CODE, EXECUTE, READ
.rdata       0x0056A000    0x0057F1F2    ~84 KB      DATA, READ (常量、字符串、IAT)
.data        0x00580000    0x0060C000    ~560 KB     DATA, READ, WRITE (全局变量)
.rsrc        0x01897000    0x0189C3CA    ~20 KB      DATA, READ (资源：图标、清单)

入口点（OEP）: 0x0055507C
导入表: 位于 .rdata 段
导出表: 无（exe 不导出函数）
```

---

## 3. 实施方案：模块化分阶段

### 3.1 Phase 0：基础设施搭建（2-3 周）

**目标：** 建立完整的分析、编译、测试工具链

#### 3.1.1 Ghidra 完整分析（1 周）

**任务：**
1. 加载脱壳后的 PAL3.exe 到 Ghidra 10.x+
2. 运行自动分析（Auto Analysis）
   - 函数识别
   - 签名匹配（Windows API、CRT 函数）
   - 字符串引用分析
   - 跳转表识别
3. 手动修正分析错误
   - 检查函数边界（特别是优化代码和异常处理）
   - 标记数据区域（常量、字符串池）
   - 识别 RTTI 信息（虚函数表、类型信息）
4. 编写 Ghidra 脚本导出数据
   ```python
   # tools/ghidra/export_functions.py
   # 导出每个函数到单独的 JSON 文件
   # 包含：地址、大小、签名、反编译 C 代码、汇编代码
   ```
5. 验证导出质量
   - 检查函数数量（预期 3500-5000）
   - 检查反编译代码可读性
   - 交叉验证关键函数

**输出：**
- Ghidra 项目文件（.gpr）
- 函数 JSON 文件（~5000 个）
- 结构体定义
- 全局变量列表

#### 3.1.2 函数分类和优先级分析（3-4 天）

**任务：**
1. 开发函数分类工具
   ```python
   # tools/analyze_pal3.py
   # 分析 JSON 文件，按多个维度分类
   ```

2. 分类维度
   - **功能模块：** 入口、初始化、游戏循环、UI、战斗、场景、存档、音视频等
   - **调用频率：** 热点函数（高频调用）vs 冷函数（少调用）
   - **依赖关系：** 叶子函数（无依赖）vs 核心函数（多依赖）
   - **函数大小：** 小（<50B）、中（50-200B）、大（>200B）

3. 构建调用图
   ```python
   # tools/ghidra/build_callgraph.py
   # 分析函数间调用关系，生成有向图
   ```

4. 识别关键路径
   - WinMain → 初始化 → 主循环 → 渲染/更新
   - 找出必须先实现的函数

**输出：**
- `asm/pal3/analysis/function_classification.json` - 函数分类结果
- `asm/pal3/analysis/call_graph.dot` - 调用图（Graphviz 格式）
- `asm/pal3/analysis/priority_list.txt` - 优先级排序列表

#### 3.1.3 编译系统搭建（3-4 天）

**任务：**
1. 创建 CMakeLists.txt
   ```cmake
   # CMakeLists.txt
   cmake_minimum_required(VERSION 3.20)
   project(PAL3 CXX)

   # 目标平台：Windows 32位
   set(CMAKE_SYSTEM_NAME Windows)
   set(CMAKE_SYSTEM_PROCESSOR X86)

   # 创建可执行文件
   add_executable(PAL3 WIN32
       src/pal3/main.cpp
       src/pal3/game_init.cpp
       src/pal3/game_loop.cpp
       # ... 其他源文件
   )

   # 包含目录
   target_include_directories(PAL3 PRIVATE
       include
       include/pal3
       include/external
   )

   # MSVC 编译选项（模拟 MSVC 7.1）
   target_compile_options(PAL3 PRIVATE
       /O2                 # 最大优化
       /Ob1                # 内联展开（仅 __inline）
       /Oi                 # 启用内部函数
       /Ot                 # 优先速度
       /Oy-                # 禁用帧指针省略（部分函数需要）
       /GF                 # 字符串池
       /Gy                 # 函数级链接
       /EHsc               # C++ 异常处理
       /GR                 # 启用 RTTI
       /Zc:wchar_t         # wchar_t 是内置类型
       /fp:precise         # 浮点精度
       /arch:SSE           # SSE 指令集
       /W3                 # 警告级别 3
       /D WIN32            # Windows 平台
       /D NDEBUG           # Release 模式
   )

   # 链接选项
   target_link_options(PAL3 PRIVATE
       /SUBSYSTEM:WINDOWS          # GUI 应用
       /ENTRY:WinMainCRTStartup    # 入口点
       /BASE:0x00400000            # 基地址（匹配原版）
       /FIXED                      # 固定基地址
       /OPT:REF                    # 移除未引用函数
       /OPT:ICF                    # 合并相同函数
       /SAFESEH:NO                 # 不使用 SafeSEH
       /MAP                        # 生成 .map 文件
   )

   # 静态链接 MSVCRT
   set_property(TARGET PAL3 PROPERTY
       MSVC_RUNTIME_LIBRARY "MultiThreaded")

   # 链接导入库
   target_link_libraries(PAL3 PRIVATE
       ${CMAKE_SOURCE_DIR}/build/libs/gbengine.lib
       ${CMAKE_SOURCE_DIR}/build/libs/topo.lib
       d3d9.lib
       d3dx9.lib
       dinput8.lib
       dxguid.lib
       winmm.lib
       user32.lib
       kernel32.lib
       advapi32.lib
   )
   ```

2. 生成导入库
   ```bash
   # tools/generate_import_lib.py
   # 从 gbengine.dll 和 topo.dll 生成 .lib
   python tools/generate_import_lib.py original/gbengine.dll -o build/libs/gbengine.lib
   python tools/generate_import_lib.py original/topo.dll -o build/libs/topo.lib
   ```

3. 创建最小化骨架代码
   ```cpp
   // src/pal3/main.cpp
   #include <windows.h>
   
   int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow)
   {
       MessageBoxA(NULL, "PAL3 Skeleton", "Info", MB_OK);
       return 0;
   }
   ```

4. 验证编译
   ```bash
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A Win32
   cmake --build . --config Release
   ```

5. 检查生成的 exe
   ```bash
   # 验证 PE 结构
   dumpbin /headers build/Release/PAL3.exe
   # 检查大小（应该很小，因为只有骨架）
   ls -lh build/Release/PAL3.exe
   ```

**输出：**
- 可工作的 CMakeLists.txt
- 导入库（gbengine.lib, topo.lib）
- 能成功编译的空壳 PAL3.exe

#### 3.1.4 工具链开发（3-4 天）

**任务：**
1. 二进制对比工具
   ```python
   # tools/compare_exe.py
   # 对比编译的 PAL3.exe 和原版 PAL3.exe
   # 支持：
   # - 按地址对比单个函数
   # - 批量对比所有函数
   # - 生成匹配率报告
   ```

2. 进度跟踪工具
   ```python
   # tools/progress_pal3.py
   # 统计实现进度
   # - 已实现函数数 / 总函数数
   # - 按模块统计
   # - 字节匹配率统计
   # - 生成 HTML 进度报告
   ```

3. 自动化测试框架
   ```python
   # tools/test_framework.py
   # 测试套件：
   # - 编译测试
   # - 结构体大小验证
   # - 函数签名验证
   # - 字节匹配测试
   # - 功能测试（启动、脚本、UI 等）
   ```

4. 持续集成配置
   ```yaml
   # .github/workflows/pal3-build.yml
   name: PAL3 Build and Test
   on: [push, pull_request]
   jobs:
     build:
       runs-on: windows-latest
       steps:
         - uses: actions/checkout@v2
         - uses: microsoft/setup-msbuild@v1
         - name: Build
           run: cmake --build build --config Release
         - name: Test
           run: python tools/test_framework.py
         - name: Compare
           run: python tools/compare_exe.py
   ```

**输出：**
- 完整的工具链
- 自动化测试框架
- CI/CD 配置

#### 3.1.5 Phase 0 验收标准

- ✅ Ghidra 分析完成，导出 3500+ 函数 JSON
- ✅ 函数分类完成，生成调用图
- ✅ 编译系统可用，能生成空壳 exe
- ✅ 工具链完整，能自动测试和对比
- ✅ 文档完整，团队成员能快速上手

---

### 3.2 Phase 1：程序框架和主循环（1 个月）

**目标：** 实现游戏骨架，能启动并进入主循环

**核心函数数：** 50-100 个  
**预计代码行数：** 2000-3000 行

#### 3.2.1 Week 1：程序入口和初始化

**实现函数（预计 15-20 个）：**

1. **WinMain 入口**（地址：0x0055507C）
   ```cpp
   // src/pal3/main.cpp
   // 0x0055507C  WinMain  (~200 bytes)
   int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow)
   {
       // 1. 解析命令行参数
       ParseCommandLine(lpCmdLine);
       
       // 2. 检查单实例
       if (!CheckSingleInstance()) {
           MessageBox(NULL, "游戏已在运行", "错误", MB_OK);
           return 1;
       }
       
       // 3. 初始化 COM
       CoInitialize(NULL);
       
       // 4. 初始化游戏
       if (!Game_Initialize(hInstance)) {
           return 1;
       }
       
       // 5. 进入主循环
       int result = Game_MainLoop();
       
       // 6. 清理
       Game_Shutdown();
       CoUninitialize();
       
       return result;
   }
   ```

2. **命令行解析**
   ```cpp
   // 0x004XXXXX  ParseCommandLine
   void ParseCommandLine(LPSTR lpCmdLine)
   {
       // 解析参数：-window, -fullscreen, -debug 等
   }
   ```

3. **单实例检查**
   ```cpp
   // 0x004XXXXX  CheckSingleInstance
   bool CheckSingleInstance()
   {
       HANDLE hMutex = CreateMutexA(NULL, FALSE, "PAL3_MUTEX");
       if (GetLastError() == ERROR_ALREADY_EXISTS) {
           CloseHandle(hMutex);
           return false;
       }
       return true;
   }
   ```

4. **游戏初始化主函数**
   ```cpp
   // 0x004XXXXX  Game_Initialize
   bool Game_Initialize(HINSTANCE hInstance)
   {
       // 1. 创建窗口
       if (!Window_Create(hInstance)) return false;
       
       // 2. 初始化 DirectX
       if (!D3D_Initialize()) return false;
       
       // 3. 初始化 gbengine
       if (!GBEngine_Initialize()) return false;
       
       // 4. 加载游戏配置
       Config_Load();
       
       // 5. 初始化各子系统
       Script_Initialize();
       UI_Initialize();
       Audio_Initialize();
       
       return true;
   }
   ```

**里程碑：**
- ✅ 程序能启动
- ✅ 显示错误消息框（如果初始化失败）
- ✅ 能正确退出

#### 3.2.2 Week 2：DirectX 初始化

**实现函数（预计 15-20 个）：**

1. **窗口创建**
   ```cpp
   // 0x004XXXXX  Window_Create
   bool Window_Create(HINSTANCE hInstance)
   {
       WNDCLASSEX wc = {0};
       wc.cbSize = sizeof(WNDCLASSEX);
       wc.lpfnWndProc = Window_WndProc;
       wc.hInstance = hInstance;
       wc.lpszClassName = "PAL3";
       RegisterClassEx(&wc);
       
       g_hWnd = CreateWindowEx(
           0, "PAL3", "仙剑奇侠传三",
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT, CW_USEDEFAULT,
           800, 600,
           NULL, NULL, hInstance, NULL
       );
       
       ShowWindow(g_hWnd, SW_SHOW);
       return g_hWnd != NULL;
   }
   ```

2. **窗口过程**
   ```cpp
   // 0x004XXXXX  Window_WndProc
   LRESULT CALLBACK Window_WndProc(HWND hWnd, UINT msg,
                                   WPARAM wParam, LPARAM lParam)
   {
       switch (msg) {
           case WM_DESTROY:
               PostQuitMessage(0);
               return 0;
           case WM_KEYDOWN:
               // 处理按键
               return 0;
           // ... 其他消息
       }
       return DefWindowProc(hWnd, msg, wParam, lParam);
   }
   ```

3. **D3D 设备创建**
   ```cpp
   // 0x004XXXXX  D3D_Initialize
   bool D3D_Initialize()
   {
       g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
       if (!g_pD3D) return false;
       
       D3DPRESENT_PARAMETERS d3dpp = {0};
       d3dpp.Windowed = TRUE;
       d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
       d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
       d3dpp.EnableAutoDepthStencil = TRUE;
       d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
       
       HRESULT hr = g_pD3D->CreateDevice(
           D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
           D3DCREATE_HARDWARE_VERTEXPROCESSING,
           &d3dpp, &g_pd3dDevice
       );
       
       return SUCCEEDED(hr);
   }
   ```

4. **硬件能力检查**
   ```cpp
   // 0x004XXXXX  D3D_CheckCapabilities
   bool D3D_CheckCapabilities()
   {
       D3DCAPS9 caps;
       g_pd3dDevice->GetDeviceCaps(&caps);
       
       // 检查必需功能
       if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1)) {
           return false;
       }
       
       return true;
   }
   ```

**里程碑：**
- ✅ 显示游戏窗口
- ✅ D3D 设备创建成功
- ✅ 能响应窗口消息（关闭、最小化等）

#### 3.2.3 Week 3：gbengine 接口集成

**实现函数（预计 10-15 个 + ~1000 个导入存根）：**

1. **定义 gbengine 导入接口**
   ```cpp
   // include/external/gbengine.h
   #pragma once
   
   // gbengine.dll 导出函数声明
   // 从 PAL3A.PDB 符号文件提取函数签名
   
   namespace gbengine {
   
   // 渲染接口
   extern "C" {
       __declspec(dllimport) void* __cdecl gbRenderDevice_Create(int, int);
       __declspec(dllimport) void __cdecl gbRenderDevice_BeginScene(void*);
       __declspec(dllimport) void __cdecl gbRenderDevice_EndScene(void*);
       __declspec(dllimport) void __cdecl gbRenderDevice_Clear(void*, DWORD);
       // ... 其他渲染函数（约 200 个）
   }
   
   // 资源管理
   extern "C" {
       __declspec(dllimport) void* __cdecl gbResourceManager_Create();
       __declspec(dllimport) void* __cdecl gbResourceManager_LoadTexture(void*, const char*);
       __declspec(dllimport) void* __cdecl gbResourceManager_LoadModel(void*, const char*);
       // ... 其他资源函数（约 150 个）
   }
   
   // 输入管理
   extern "C" {
       __declspec(dllimport) void* __cdecl gbInputManager_Create(HWND);
       __declspec(dllimport) void __cdecl gbInputManager_Update(void*);
       __declspec(dllimport) bool __cdecl gbInputManager_IsKeyDown(void*, int);
       // ... 其他输入函数（约 50 个）
   }
   
   // 音频接口
   extern "C" {
       __declspec(dllimport) void* __cdecl gbAudioManager_Create();
       __declspec(dllimport) void __cdecl gbAudioManager_PlayMusic(void*, const char*);
       __declspec(dllimport) void __cdecl gbAudioManager_PlaySound(void*, const char*);
       // ... 其他音频函数（约 100 个）
   }
   
   // 场景管理
   extern "C" {
       __declspec(dllimport) void* __cdecl gbSceneManager_Create();
       __declspec(dllimport) void __cdecl gbSceneManager_LoadScene(void*, const char*);
       // ... 其他场景函数（约 200 个）
   }
   
   // ... 其他模块（总计约 1000 个导入函数）
   
   } // namespace gbengine
   ```

2. **gbengine 初始化包装**
   ```cpp
   // src/pal3/game_init.cpp
   // 0x004XXXXX  GBEngine_Initialize
   bool GBEngine_Initialize()
   {
       // 检查 gbengine.dll 是否存在
       HMODULE hGBEngine = LoadLibraryA("gbengine.dll");
       if (!hGBEngine) {
           MessageBoxA(NULL, "找不到 gbengine.dll", "错误", MB_OK);
           return false;
       }
       
       // 初始化 gbengine 渲染设备
       g_pRenderDevice = gbengine::gbRenderDevice_Create(800, 600);
       if (!g_pRenderDevice) {
           return false;
       }
       
       // 初始化资源管理器
       g_pResourceManager = gbengine::gbResourceManager_Create();
       
       // 初始化输入管理器
       g_pInputManager = gbengine::gbInputManager_Create(g_hWnd);
       
       // 初始化音频管理器
       g_pAudioManager = gbengine::gbAudioManager_Create();
       
       return true;
   }
   ```

3. **接口版本验证**
   ```cpp
   // 0x004XXXXX  GBEngine_VerifyVersion
   bool GBEngine_VerifyVersion()
   {
       // 检查 gbengine.dll 版本是否兼容
       // 避免 DLL 版本不匹配导致的崩溃
   }
   ```

**里程碑：**
- ✅ gbengine.dll 成功加载
- ✅ 所有导入函数可调用
- ✅ 渲染设备初始化成功

#### 3.2.4 Week 4：主游戏循环

**实现函数（预计 15-20 个）：**

1. **主循环框架**
   ```cpp
   // src/pal3/game_loop.cpp
   // 0x004XXXXX  Game_MainLoop
   int Game_MainLoop()
   {
       MSG msg = {0};
       
       // 初始化计时器
       LARGE_INTEGER frequency, lastTime;
       QueryPerformanceFrequency(&frequency);
       QueryPerformanceCounter(&lastTime);
       
       while (g_bGameRunning) {
           // 处理 Windows 消息
           while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
               if (msg.message == WM_QUIT) {
                   g_bGameRunning = false;
                   break;
               }
               TranslateMessage(&msg);
               DispatchMessage(&msg);
           }
           
           if (!g_bGameRunning) break;
           
           // 计算帧时间
           LARGE_INTEGER currentTime;
           QueryPerformanceCounter(&currentTime);
           float deltaTime = (float)(currentTime.QuadPart - lastTime.QuadPart) 
                           / frequency.QuadPart;
           lastTime = currentTime;
           
           // 更新游戏逻辑
           Game_Update(deltaTime);
           
           // 渲染
           Game_Render();
           
           // 限制帧率
           Sleep(1);
       }
       
       return (int)msg.wParam;
   }
   ```

2. **游戏更新**
   ```cpp
   // 0x004XXXXX  Game_Update
   void Game_Update(float deltaTime)
   {
       // 更新输入
       gbengine::gbInputManager_Update(g_pInputManager);
       
       // 更新脚本
       Script_Update(deltaTime);
       
       // 更新 UI
       UI_Update(deltaTime);
       
       // 更新场景
       Scene_Update(deltaTime);
       
       // 更新音频
       Audio_Update();
       
       // 更新 FPS 计数
       UpdateFPS();
   }
   ```

3. **游戏渲染**
   ```cpp
   // 0x004XXXXX  Game_Render
   void Game_Render()
   {
       // 开始渲染
       gbengine::gbRenderDevice_BeginScene(g_pRenderDevice);
       gbengine::gbRenderDevice_Clear(g_pRenderDevice, 0xFF000000);
       
       // 渲染场景
       Scene_Render();
       
       // 渲染 UI
       UI_Render();
       
       // 结束渲染
       gbengine::gbRenderDevice_EndScene(g_pRenderDevice);
   }
   ```

4. **FPS 计算**
   ```cpp
   // 0x004XXXXX  UpdateFPS
   void UpdateFPS()
   {
       static int frameCount = 0;
       static float timeAccum = 0.0f;
       
       frameCount++;
       timeAccum += g_deltaTime;
       
       if (timeAccum >= 1.0f) {
           g_currentFPS = frameCount;
           frameCount = 0;
           timeAccum = 0.0f;
       }
   }
   ```

5. **游戏清理**
   ```cpp
   // 0x004XXXXX  Game_Shutdown
   void Game_Shutdown()
   {
       // 清理各子系统
       Audio_Shutdown();
       UI_Shutdown();
       Script_Shutdown();
       Scene_Shutdown();
       
       // 清理 gbengine
       GBEngine_Shutdown();
       
       // 清理 DirectX
       D3D_Shutdown();
       
       // 销毁窗口
       Window_Destroy();
   }
   ```

**里程碑：**
- ✅ 进入主游戏循环
- ✅ 能正常更新和渲染（虽然还没有实际内容）
- ✅ FPS 计算正常
- ✅ 能正常退出和清理

#### 3.2.5 Phase 1 字节匹配

**策略：**
- 这个阶段的函数通常较小且逻辑清晰
- 目标：80%+ 函数字节匹配
- 重点调优：WinMain、主循环、窗口过程

**匹配技术：**
```cpp
// 技术 1：变量声明顺序
// 错误（可能不匹配）：
float deltaTime;
int frameCount;
LARGE_INTEGER currentTime;

// 正确（按使用顺序声明，匹配栈布局）：
LARGE_INTEGER currentTime;
float deltaTime;
int frameCount;

// 技术 2：循环形式
// 错误：
for (int i = 0; i < count; i++)

// 正确（MSVC 7.1 优化偏好）：
for (int i = 0; i != count; i++)

// 技术 3：条件表达式
// 错误：
if (ptr != NULL)

// 正确（生成更紧凑的代码）：
if (ptr)
```

#### 3.2.6 Phase 1 验收标准

- ✅ 实现 50-100 个函数
- ✅ 游戏能启动到主循环
- ✅ 窗口显示正常
- ✅ 能正常退出
- ✅ 80%+ 函数字节匹配
- ✅ 代码文档完整
- ✅ 进度：2-3%

---

### 3.3 Phase 2：脚本引擎（SCE VM）（1.5 个月）

**目标：** 实现 SCE 字节码虚拟机，能执行游戏脚本

**重要性：** ⭐⭐⭐⭐⭐ 脚本引擎是游戏逻辑的核心

**核心函数数：** 200-300 个  
**预计代码行数：** 5000-8000 行

#### 3.3.1 Week 1-2：VM 核心

**实现函数（预计 30-40 个）：**

1. **虚拟机结构**
   ```cpp
   // include/pal3/script.h
   struct SCE_VM {
       uint8_t* code;           // 字节码
       uint32_t codeSize;       // 代码大小
       uint32_t pc;             // 程序计数器（PC）
       
       uint32_t stack[256];     // 栈（256 个槽位）
       int sp;                  // 栈指针（SP）
       
       uint32_t registers[16];  // 寄存器
       
       bool running;            // 运行状态
       bool paused;             // 暂停状态
       
       void* userData;          // 用户数据
   };
   ```

2. **VM 初始化**
   ```cpp
   // src/pal3/script/vm_core.cpp
   // 0x004XXXXX  SCE_VM_Create
   SCE_VM* SCE_VM_Create()
   {
       SCE_VM* vm = (SCE_VM*)malloc(sizeof(SCE_VM));
       memset(vm, 0, sizeof(SCE_VM));
       vm->sp = -1;
       return vm;
   }
   ```

3. **加载字节码**
   ```cpp
   // 0x004XXXXX  SCE_VM_LoadBytecode
   bool SCE_VM_LoadBytecode(SCE_VM* vm, const uint8_t* code, uint32_t size)
   {
       vm->code = (uint8_t*)malloc(size);
       memcpy(vm->code, code, size);
       vm->codeSize = size;
       vm->pc = 0;
       return true;
   }
   ```

4. **VM 主执行循环**
   ```cpp
   // 0x004XXXXX  SCE_VM_Execute
   void SCE_VM_Execute(SCE_VM* vm)
   {
       vm->running = true;
       
       while (vm->running && vm->pc < vm->codeSize) {
           // 取指令
           uint8_t opcode = vm->code[vm->pc++];
           
           // 解码和执行
           switch (opcode) {
               case OP_NOP:
                   // 空操作
                   break;
                   
               case OP_PUSH:
                   SCE_OP_Push(vm);
                   break;
                   
               case OP_POP:
                   SCE_OP_Pop(vm);
                   break;
                   
               case OP_ADD:
                   SCE_OP_Add(vm);
                   break;
                   
               // ... 其他 140 个操作码
                   
               case OP_HALT:
                   vm->running = false;
                   break;
                   
               default:
                   // 未知操作码，报错
                   SCE_VM_Error(vm, "Unknown opcode: 0x%02X", opcode);
                   vm->running = false;
                   break;
           }
           
           // 检查是否暂停
           if (vm->paused) {
               break;
           }
       }
   }
   ```

5. **栈操作**
   ```cpp
   // 0x004XXXXX  SCE_Stack_Push
   void SCE_Stack_Push(SCE_VM* vm, uint32_t value)
   {
       if (vm->sp >= 255) {
           SCE_VM_Error(vm, "Stack overflow");
           return;
       }
       vm->stack[++vm->sp] = value;
   }
   
   // 0x004XXXXX  SCE_Stack_Pop
   uint32_t SCE_Stack_Pop(SCE_VM* vm)
   {
       if (vm->sp < 0) {
           SCE_VM_Error(vm, "Stack underflow");
           return 0;
       }
       return vm->stack[vm->sp--];
   }
   ```

**里程碑：**
- ✅ VM 能加载字节码
- ✅ 能执行简单指令（NOP, PUSH, POP）
- ✅ 栈操作正确
- ✅ 错误处理机制完善

#### 3.3.2 Week 3-5：140 个操作码实现

**操作码分类（参考 `docs/sce_opcodes.md`）：**

1. **栈操作（10 个）**
   - PUSH, POP, DUP, SWAP, LOAD, STORE 等

2. **算术运算（15 个）**
   - ADD, SUB, MUL, DIV, MOD, NEG, INC, DEC 等

3. **逻辑运算（10 个）**
   - AND, OR, NOT, XOR, SHL, SHR 等

4. **比较运算（8 个）**
   - EQ, NE, LT, LE, GT, GE, CMP 等

5. **流程控制（15 个）**
   - JMP, JZ, JNZ, CALL, RET, IF, ELSE, ENDIF 等

6. **内存操作（12 个）**
   - LOADB, LOADW, LOADD, STOREB, STOREW, STORED 等

7. **字符串操作（8 个）**
   - STRCAT, STRCMP, STRLEN, STRCPY 等

8. **游戏特定操作（60+ 个）**
   - SHOW_DIALOG - 显示对话
   - PLAY_MUSIC - 播放音乐
   - PLAY_SOUND - 播放音效
   - LOAD_SCENE - 加载场景
   - START_BATTLE - 开始战斗
   - ADD_ITEM - 添加物品
   - REMOVE_ITEM - 移除物品
   - SET_FLAG - 设置标志
   - GET_FLAG - 获取标志
   - WAIT - 等待
   - FADE_IN - 淡入
   - FADE_OUT - 淡出
   - CAMERA_MOVE - 移动相机
   - CHARACTER_MOVE - 移动角色
   - ... 等等

**实现示例：**

```cpp
// src/pal3/script/opcodes.cpp

// 算术运算
// 0x004XXXXX  SCE_OP_Add
void SCE_OP_Add(SCE_VM* vm)
{
    uint32_t b = SCE_Stack_Pop(vm);
    uint32_t a = SCE_Stack_Pop(vm);
    SCE_Stack_Push(vm, a + b);
}

// 流程控制
// 0x004XXXXX  SCE_OP_Jump
void SCE_OP_Jump(SCE_VM* vm)
{
    // 读取跳转目标（4 字节）
    uint32_t target = *(uint32_t*)(&vm->code[vm->pc]);
    vm->pc = target;
}

// 游戏特定
// 0x004XXXXX  SCE_OP_ShowDialog
void SCE_OP_ShowDialog(SCE_VM* vm)
{
    // 读取对话 ID
    uint32_t dialogID = SCE_Stack_Pop(vm);
    
    // 调用 UI 系统显示对话
    UI_ShowDialog(dialogID);
    
    // 暂停 VM，等待用户关闭对话
    vm->paused = true;
}

// 0x004XXXXX  SCE_OP_PlayMusic
void SCE_OP_PlayMusic(SCE_VM* vm)
{
    // 读取音乐 ID
    uint32_t musicID = SCE_Stack_Pop(vm);
    
    // 调用音频系统播放音乐
    gbengine::gbAudioManager_PlayMusic(g_pAudioManager, 
                                       GetMusicPath(musicID));
}

// 0x004XXXXX  SCE_OP_StartBattle
void SCE_OP_StartBattle(SCE_VM* vm)
{
    // 读取战斗 ID
    uint32_t battleID = SCE_Stack_Pop(vm);
    
    // 切换到战斗场景
    Battle_Start(battleID);
    
    // 暂停脚本，等待战斗结束
    vm->paused = true;
}
```

**实施策略：**
- 先实现基础操作码（栈、算术、流程控制）
- 再实现游戏特定操作码
- 每实现 20 个操作码编译测试一次
- 用简单脚本测试（如显示文字、播放音乐）

#### 3.3.3 Week 6：脚本资源加载

**实现函数（预计 20-30 个）：**

1. **SCE 文件加载**
   ```cpp
   // src/pal3/script/script_loader.cpp
   // 0x004XXXXX  SCE_LoadFile
   bool SCE_LoadFile(const char* filename, SCE_VM* vm)
   {
       // 1. 从 CPK 包加载文件
       uint8_t* data = CPK_LoadFile(filename);
       if (!data) return false;
       
       // 2. 解析 SCE 文件头
       SCE_Header* header = (SCE_Header*)data;
       if (header->magic != SCE_MAGIC) {
           free(data);
           return false;
       }
       
       // 3. 加载字节码到 VM
       SCE_VM_LoadBytecode(vm, 
                          data + header->codeOffset, 
                          header->codeSize);
       
       // 4. 加载字符串表
       SCE_LoadStringTable(vm, 
                          data + header->stringOffset,
                          header->stringSize);
       
       free(data);
       return true;
   }
   ```

2. **CPK 文件系统集成**
   ```cpp
   // 0x004XXXXX  CPK_LoadFile
   uint8_t* CPK_LoadFile(const char* filename)
   {
       // 调用 gbengine 的 CPK 读取接口
       return gbengine::gbResourceManager_LoadFile(g_pResourceManager, 
                                                   filename);
   }
   ```

3. **脚本缓存**
   ```cpp
   // 0x004XXXXX  SCE_Cache_Get
   SCE_VM* SCE_Cache_Get(const char* filename)
   {
       // 检查缓存
       for (int i = 0; i < g_scriptCacheCount; i++) {
           if (strcmp(g_scriptCache[i].filename, filename) == 0) {
               return g_scriptCache[i].vm;
           }
       }
       
       // 未找到，加载新脚本
       SCE_VM* vm = SCE_VM_Create();
       if (SCE_LoadFile(filename, vm)) {
           // 添加到缓存
           g_scriptCache[g_scriptCacheCount].vm = vm;
           strcpy(g_scriptCache[g_scriptCacheCount].filename, filename);
           g_scriptCacheCount++;
           return vm;
       }
       
       SCE_VM_Destroy(vm);
       return NULL;
   }
   ```

**里程碑：**
- ✅ 能从 CPK 加载 .sce 文件
- ✅ 脚本缓存机制工作正常
- ✅ 能执行游戏开场脚本

#### 3.3.4 Phase 2 测试

**测试用例：**

1. **测试简单脚本**
   ```
   脚本：开场对话
   期望：显示"欢迎来到仙剑奇侠传三"对话框
   ```

2. **测试音乐播放**
   ```
   脚本：播放背景音乐
   期望：听到游戏音乐
   ```

3. **测试场景切换**
   ```
   脚本：从主菜单进入新游戏
   期望：场景切换成功，显示开场动画
   ```

#### 3.3.5 Phase 2 字节匹配

**策略：**
- VM 核心循环：100% 匹配（关键热点）
- 常用操作码（前 30 个）：95%+ 匹配
- 其他操作码：功能正确即可（80%+ 匹配）

**匹配技巧：**
- 操作码 switch 语句使用跳转表（编译器优化）
- 栈操作内联（`__forceinline`）
- 指令解码使用位操作而非条件判断

#### 3.3.6 Phase 2 验收标准

- ✅ 实现 200-300 个函数
- ✅ 140 个操作码全部实现
- ✅ 能执行复杂脚本（开场剧情）
- ✅ VM 核心 100% 字节匹配
- ✅ 常用操作码 95%+ 匹配
- ✅ 代码文档完整
- ✅ 进度：8-10%

---

### 3.4 Phase 3-7：核心游戏系统（6-7 个月）

由于篇幅限制，这里概述各阶段，详细设计在实施时展开。

#### 3.4.1 Phase 3：UI 系统（1.5 个月）

**目标：** 实现完整的 UI 系统

**核心模块：**
- 菜单系统（主菜单、游戏菜单、系统菜单）
- 对话框（消息框、选择框、输入框）
- HUD（生命值、法力值、小地图）
- UI 组件（按钮、文本框、列表、滚动条）
- UI 动画和过渡效果

**函数数：** 500-800 个  
**预计进度：** 10% → 22-25%

#### 3.4.2 Phase 4：战斗系统（2 个月）

**目标：** 实现完整的回合制战斗系统

**核心模块：**
- 战斗流程控制（回合制逻辑）
- 技能系统（仙术、武技、合击）
- 战斗 AI（敌人行为、伙伴 AI）
- 伤害计算（攻击、防御、属性克制）
- 战斗特效和动画
- 战斗 UI（指令选择、角色状态）

**函数数：** 800-1200 个  
**预计进度：** 25% → 45-50%

#### 3.4.3 Phase 5：场景管理（1 个月）

**目标：** 实现场景加载和管理

**核心模块：**
- 地图加载（场景文件解析）
- 场景切换（淡入淡出、加载画面）
- 碰撞检测（地形、物体、NPC）
- 相机控制（跟随、缩放、旋转）
- 角色移动（寻路、动画）
- 互动对象（宝箱、机关、NPC）

**函数数：** 400-600 个  
**预计进度：** 50% → 60-65%

#### 3.4.4 Phase 6：存档系统（2 周）

**目标：** 实现存档读写

**核心模块：**
- 存档结构定义
- 存档序列化/反序列化
- 存档加密/解密
- 存档槽位管理
- 快速存档/读档

**函数数：** 100-200 个  
**预计进度：** 65% → 65-70%

#### 3.4.5 Phase 7：其他系统（1.5 个月）

**目标：** 实现剩余辅助系统

**核心模块：**
- 音频管理（音乐、音效、语音）
- 视频播放（Bink 集成）
- 配置管理（设置读写）
- 物品系统（背包、装备）
- 任务系统（任务日志）
- 商店系统
- 小游戏（猜拳、钓鱼等）

**函数数：** 600-800 个  
**预计进度：** 70% → 85-90%

---

### 3.5 Phase 8：字节匹配调优和测试（1-2 个月）

**目标：** 达到 95%+ 核心函数字节匹配，完成测试

#### 3.5.1 字节匹配批量调优（3-4 周）

**流程：**

1. **批量对比**
   ```bash
   python tools/compare_exe.py --all --output build/reports/final_matching.html
   ```

2. **按优先级调优**
   - P0（必须 100%）：关键路径函数（WinMain、主循环、VM 核心）
   - P1（目标 95%+）：热点函数（战斗、渲染、脚本）
   - P2（目标 80%+）：其他函数

3. **调优技术库应用**
   ```cpp
   // 已记录的匹配技巧：
   // - 变量声明顺序
   // - 循环形式
   // - 条件表达式
   // - 内联控制
   // - 寄存器提示
   // - 编译器指令
   ```

4. **难以匹配的函数处理**
   - 尝试不同编译选项组合
   - 手写汇编（极少数情况）
   - 接受功能等价（非关键函数）

5. **记录匹配模式**
   ```bash
   # 每个成功匹配的函数记录技巧
   python tools/record_match_pattern.py 0x004XXXXX "variable-ordering+loop-form"
   ```

**目标：**
- 核心函数（前 500 个）：95%+ 字节匹配
- 整体函数：85%+ 字节匹配

#### 3.5.2 全面测试（3-4 周）

**Level 1：编译测试**
```bash
# 清理构建
rm -rf build/
cmake --build build --config Release

# 检查编译结果
- 无错误
- 无警告
- exe 大小接近原版（±5%）
```

**Level 2：结构测试**
```bash
# PE 结构验证
dumpbin /headers build/Release/PAL3.exe > headers_new.txt
dumpbin /headers original/PAL3.exe > headers_old.txt
diff headers_old.txt headers_new.txt

# 导入表验证
dumpbin /imports build/Release/PAL3.exe > imports_new.txt
dumpbin /imports original/PAL3.exe > imports_old.txt
diff imports_old.txt imports_new.txt
```

**Level 3：字节匹配测试**
```bash
# 批量对比
python tools/compare_exe.py --all --report html

# 检查报告
- 核心函数匹配率 ≥ 95%
- 整体匹配率 ≥ 85%
- 生成详细报告
```

**Level 4：功能测试**

测试用例列表：
1. 启动测试
   - 游戏能正常启动
   - 显示主菜单
   - 菜单交互正常

2. 新游戏测试
   - 能开始新游戏
   - 开场动画播放
   - 进入游戏场景

3. 剧情测试
   - 对话显示正常
   - 剧情推进正常
   - 过场动画播放

4. 战斗测试
   - 能触发战斗
   - 战斗流程完整
   - 技能释放正常
   - 战斗胜利/失败正确

5. 场景测试
   - 场景切换正常
   - 角色移动正确
   - 碰撞检测准确
   - 互动对象有效

6. 存档测试
   - 能保存游戏
   - 能加载游戏
   - 存档数据正确

7. 长时间测试
   - 连续运行 6+ 小时
   - 无崩溃
   - 无内存泄漏
   - 性能稳定

8. 通关测试
   - 完整游戏流程
   - 所有主线关卡
   - 通关无异常

**自动化测试**
```python
# tools/test_framework.py
class PAL3TestSuite:
    def test_startup(self):
        """测试启动"""
        
    def test_new_game(self):
        """测试新游戏"""
        
    def test_battle(self):
        """测试战斗"""
        
    def test_save_load(self):
        """测试存档"""
        
    def test_stability(self):
        """测试稳定性（6 小时）"""
```

#### 3.5.3 Bug 修复（持续）

**Bug 跟踪：**
- 使用 GitHub Issues 跟踪 bug
- 按严重性分级（P0-P3）
- P0（崩溃、数据损坏）：立即修复
- P1（功能异常）：优先修复
- P2（体验问题）：批量修复
- P3（美化）：时间允许修复

#### 3.5.4 Phase 8 验收标准

- ✅ 核心函数字节匹配率 ≥ 95%
- ✅ 整体字节匹配率 ≥ 85%
- ✅ 所有 Level 1-3 测试通过
- ✅ 所有 Level 4 功能测试通过
- ✅ 6 小时稳定性测试通过
- ✅ 能完整通关
- ✅ P0/P1 bug 全部修复
- ✅ 生成完整测试报告
- ✅ 进度：100%

---

## 4. 关键技术方案

### 4.1 编译器配置和字节匹配

#### 4.1.1 CMake 配置

```cmake
# CMakeLists.txt（完整版本）
cmake_minimum_required(VERSION 3.20)
project(PAL3 CXX)

# 目标平台
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR X86)

# 源文件
file(GLOB_RECURSE PAL3_SOURCES
    src/pal3/*.cpp
    src/pal3/**/*.cpp
)

# 头文件
file(GLOB_RECURSE PAL3_HEADERS
    include/pal3/*.h
    include/pal3/**/*.h
)

# 创建可执行文件
add_executable(PAL3 WIN32
    ${PAL3_SOURCES}
    ${PAL3_HEADERS}
)

# 包含目录
target_include_directories(PAL3 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/pal3
    ${CMAKE_SOURCE_DIR}/include/external
)

# MSVC 编译选项（模拟 MSVC 7.1）
if(MSVC)
    target_compile_options(PAL3 PRIVATE
        /O2                 # 最大优化
        /Ob1                # 内联展开（仅 __inline）
        /Oi                 # 启用内部函数
        /Ot                 # 优先速度
        /Oy-                # 禁用帧指针省略（部分函数）
        /GF                 # 字符串池
        /Gy                 # 函数级链接
        /EHsc               # C++ 异常处理
        /GR                 # 启用 RTTI
        /Zc:wchar_t         # wchar_t 是内置类型
        /fp:precise         # 浮点精度
        /arch:SSE           # SSE 指令集
        /W3                 # 警告级别 3
        /D WIN32            # Windows 平台
        /D _WINDOWS         # GUI 应用
        /D NDEBUG           # Release 模式
        /D _MBCS            # 多字节字符集
    )
    
    # 链接选项
    target_link_options(PAL3 PRIVATE
        /SUBSYSTEM:WINDOWS          # GUI 应用
        /ENTRY:WinMainCRTStartup    # 入口点
        /BASE:0x00400000            # 基地址（匹配原版）
        /FIXED                      # 固定基地址
        /OPT:REF                    # 移除未引用函数
        /OPT:ICF                    # 合并相同函数
        /SAFESEH:NO                 # 不使用 SafeSEH
        /MAP                        # 生成 .map 文件
        /MAPINFO:EXPORTS            # 导出信息
        /MAPINFO:LINES              # 行号信息
    )
    
    # 静态链接 MSVCRT
    set_property(TARGET PAL3 PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded")
        
    # 预编译头（可选，加速编译）
    # target_precompile_headers(PAL3 PRIVATE include/pal3/pch.h)
endif()

# 链接库
target_link_libraries(PAL3 PRIVATE
    # gbengine 和 topo 导入库
    ${CMAKE_SOURCE_DIR}/build/libs/gbengine.lib
    ${CMAKE_SOURCE_DIR}/build/libs/topo.lib
    
    # DirectX
    d3d9.lib
    d3dx9.lib
    dinput8.lib
    dxguid.lib
    
    # Windows API
    winmm.lib
    user32.lib
    kernel32.lib
    advapi32.lib
    gdi32.lib
    comdlg32.lib
    ole32.lib
    oleaut32.lib
)

# 输出目录
set_target_properties(PAL3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release
)

# 安装规则（可选）
install(TARGETS PAL3
    RUNTIME DESTINATION bin
)
```

#### 4.1.2 字节匹配技术库

```cpp
// docs/pal3/matching_techniques.h
// 字节匹配技巧汇总

// ============================================================================
// 技巧 1：变量声明顺序影响栈布局
// ============================================================================

// ❌ 错误（可能不匹配）
void Function1() {
    float a;
    int b;
    char* c;
    double d;
}

// ✅ 正确（按使用顺序或类型大小）
void Function1() {
    double d;      // 8 字节，先声明
    char* c;       // 4 字节
    float a;       // 4 字节
    int b;         // 4 字节
}

// ============================================================================
// 技巧 2：循环形式影响指令模式
// ============================================================================

// ❌ 错误
for (int i = 0; i < count; i++) {
    // CMP + JL 指令
}

// ✅ 正确（MSVC 7.1 偏好）
for (int i = 0; i != count; i++) {
    // CMP + JNE 指令（更紧凑）
}

// ❌ 错误
int i = 0;
while (i < count) {
    // ...
    i++;
}

// ✅ 正确
for (int i = 0; i != count; i++) {
    // for 循环生成更优化的代码
}

// ============================================================================
// 技巧 3：条件表达式影响代码生成
// ============================================================================

// ❌ 错误
if (ptr != NULL) {
    // TEST + JE 指令
}

// ✅ 正确
if (ptr) {
    // TEST + JZ 指令（更紧凑）
}

// ❌ 错误
if (value == 0) {
}

// ✅ 正确
if (!value) {
}

// ============================================================================
// 技巧 4：内联控制影响函数调用
// ============================================================================

// 强制内联（小函数）
__forceinline int Add(int a, int b) {
    return a + b;
}

// 禁止内联（需要地址的函数）
__declspec(noinline) void ComplexFunction() {
    // ...
}

// ============================================================================
// 技巧 5：寄存器提示影响变量分配
// ============================================================================

// 提示编译器使用寄存器
void HotLoop() {
    register int counter;  // 尝试分配到寄存器
    for (counter = 0; counter != 1000; counter++) {
        // ...
    }
}

// ============================================================================
// 技巧 6：编译指令精细控制优化
// ============================================================================

// 禁用特定函数的优化
#pragma optimize("", off)
void DebugFunction() {
    // 不优化，便于调试
}
#pragma optimize("", on)

// 指定内联深度
#pragma inline_depth(2)

// ============================================================================
// 技巧 7：数据对齐影响结构体布局
// ============================================================================

// 自然对齐（编译器默认）
struct Aligned {
    int a;      // offset 0
    char b;     // offset 4
    // padding 3 bytes
    int c;      // offset 8
};

// 紧凑对齐（匹配原版）
#pragma pack(push, 1)
struct Packed {
    int a;      // offset 0
    char b;     // offset 4
    int c;      // offset 5
};
#pragma pack(pop)

// ============================================================================
// 技巧 8：常量表达式影响编译时计算
// ============================================================================

// ❌ 运行时计算
int size = 10 * 20;

// ✅ 编译时常量
enum { SIZE = 10 * 20 };
// 或
#define SIZE (10 * 20)

// ============================================================================
// 技巧 9：函数调用约定影响参数传递
// ============================================================================

// __cdecl（C 默认，调用者清栈）
int __cdecl CdeclFunc(int a, int b);

// __stdcall（Win32 API，被调用者清栈）
int __stdcall StdcallFunc(int a, int b);

// __fastcall（寄存器传参）
int __fastcall FastcallFunc(int a, int b);

// __thiscall（C++ 成员函数，this 指针通过 ECX）
class MyClass {
    int __thiscall MemberFunc(int a);
};

// ============================================================================
// 技巧 10：switch 语句影响跳转表生成
// ============================================================================

// ❌ 稀疏 case（可能生成 if-else 链）
switch (value) {
    case 1: break;
    case 100: break;
    case 1000: break;
}

// ✅ 密集 case（生成跳转表）
switch (value) {
    case 0: break;
    case 1: break;
    case 2: break;
    case 3: break;
    // ... 连续的 case
}
```

### 4.2 导入表和外部依赖

#### 4.2.1 生成导入库工具

```python
# tools/generate_import_lib.py
#!/usr/bin/env python3
"""
从 DLL 生成导入库 (.lib)

用法：
    python generate_import_lib.py original/gbengine.dll -o build/libs/gbengine.lib
"""

import sys
import subprocess
import os

def generate_def_file(dll_path, def_path):
    """从 DLL 生成 .def 文件"""
    # 使用 dumpbin 导出函数列表
    result = subprocess.run(
        ['dumpbin', '/exports', dll_path],
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"Error: Failed to run dumpbin on {dll_path}")
        return False
    
    # 解析输出
    lines = result.stdout.split('\n')
    exports = []
    
    in_exports = False
    for line in lines:
        if 'ordinal' in line.lower() and 'name' in line.lower():
            in_exports = True
            continue
        
        if in_exports:
            parts = line.strip().split()
            if len(parts) >= 4:
                # ordinal hint RVA name
                name = parts[3]
                if not name.startswith('?'):  # 跳过 C++ mangled names
                    exports.append(name)
    
    # 写入 .def 文件
    with open(def_path, 'w') as f:
        f.write(f"LIBRARY {os.path.basename(dll_path)}\n")
        f.write("EXPORTS\n")
        for name in exports:
            f.write(f"    {name}\n")
    
    print(f"Generated {def_path} with {len(exports)} exports")
    return True

def generate_lib_file(def_path, lib_path, machine='X86'):
    """从 .def 文件生成 .lib 文件"""
    # 使用 lib.exe 生成导入库
    result = subprocess.run(
        ['lib', f'/def:{def_path}', f'/out:{lib_path}', f'/machine:{machine}'],
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"Error: Failed to generate lib file")
        print(result.stderr)
        return False
    
    print(f"Generated {lib_path}")
    return True

def main():
    if len(sys.argv) < 3:
        print("Usage: python generate_import_lib.py <dll> -o <lib>")
        sys.exit(1)
    
    dll_path = sys.argv[1]
    lib_path = sys.argv[3] if len(sys.argv) > 3 else dll_path.replace('.dll', '.lib')
    
    if not os.path.exists(dll_path):
        print(f"Error: {dll_path} not found")
        sys.exit(1)
    
    # 生成 .def 文件
    def_path = lib_path.replace('.lib', '.def')
    if not generate_def_file(dll_path, def_path):
        sys.exit(1)
    
    # 生成 .lib 文件
    if not generate_lib_file(def_path, lib_path):
        sys.exit(1)
    
    print("Done!")

if __name__ == "__main__":
    main()
```

#### 4.2.2 gbengine 接口定义

```cpp
// include/external/gbengine.h
#pragma once

// 从 PAL3A.PDB 符号文件提取的 gbengine.dll 接口

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// 渲染接口（~200 个函数）
// ============================================================================

// 设备管理
__declspec(dllimport) void* __cdecl gbRenderDevice_Create(int width, int height, int windowed);
__declspec(dllimport) void __cdecl gbRenderDevice_Destroy(void* device);
__declspec(dllimport) void __cdecl gbRenderDevice_BeginScene(void* device);
__declspec(dllimport) void __cdecl gbRenderDevice_EndScene(void* device);
__declspec(dllimport) void __cdecl gbRenderDevice_Clear(void* device, unsigned int color);
__declspec(dllimport) void __cdecl gbRenderDevice_Present(void* device);

// 状态管理
__declspec(dllimport) void __cdecl gbRenderDevice_SetRenderState(void* device, int state, int value);
__declspec(dllimport) void __cdecl gbRenderDevice_SetTexture(void* device, int stage, void* texture);
__declspec(dllimport) void __cdecl gbRenderDevice_SetMaterial(void* device, void* material);
__declspec(dllimport) void __cdecl gbRenderDevice_SetLight(void* device, int index, void* light);

// 视口和变换
__declspec(dllimport) void __cdecl gbRenderDevice_SetViewport(void* device, int x, int y, int w, int h);
__declspec(dllimport) void __cdecl gbRenderDevice_SetTransform(void* device, int type, void* matrix);

// ... 其他约 180 个渲染函数

// ============================================================================
// 资源管理接口（~150 个函数）
// ============================================================================

__declspec(dllimport) void* __cdecl gbResourceManager_Create();
__declspec(dllimport) void __cdecl gbResourceManager_Destroy(void* mgr);
__declspec(dllimport) void* __cdecl gbResourceManager_LoadTexture(void* mgr, const char* filename);
__declspec(dllimport) void* __cdecl gbResourceManager_LoadModel(void* mgr, const char* filename);
__declspec(dllimport) void* __cdecl gbResourceManager_LoadMesh(void* mgr, const char* filename);
__declspec(dllimport) void* __cdecl gbResourceManager_LoadFile(void* mgr, const char* filename);
__declspec(dllimport) void __cdecl gbResourceManager_ReleaseTexture(void* mgr, void* texture);
__declspec(dllimport) void __cdecl gbResourceManager_ReleaseModel(void* mgr, void* model);

// ... 其他约 142 个资源函数

// ============================================================================
// 输入管理接口（~50 个函数）
// ============================================================================

__declspec(dllimport) void* __cdecl gbInputManager_Create(void* hwnd);
__declspec(dllimport) void __cdecl gbInputManager_Destroy(void* mgr);
__declspec(dllimport) void __cdecl gbInputManager_Update(void* mgr);
__declspec(dllimport) int __cdecl gbInputManager_IsKeyDown(void* mgr, int keycode);
__declspec(dllimport) int __cdecl gbInputManager_IsKeyPressed(void* mgr, int keycode);
__declspec(dllimport) void __cdecl gbInputManager_GetMousePos(void* mgr, int* x, int* y);
__declspec(dllimport) int __cdecl gbInputManager_IsMouseButtonDown(void* mgr, int button);

// ... 其他约 43 个输入函数

// ============================================================================
// 音频管理接口（~100 个函数）
// ============================================================================

__declspec(dllimport) void* __cdecl gbAudioManager_Create();
__declspec(dllimport) void __cdecl gbAudioManager_Destroy(void* mgr);
__declspec(dllimport) void __cdecl gbAudioManager_PlayMusic(void* mgr, const char* filename);
__declspec(dllimport) void __cdecl gbAudioManager_StopMusic(void* mgr);
__declspec(dllimport) void __cdecl gbAudioManager_PauseMusic(void* mgr);
__declspec(dllimport) void __cdecl gbAudioManager_ResumeMusic(void* mgr);
__declspec(dllimport) void __cdecl gbAudioManager_SetMusicVolume(void* mgr, float volume);
__declspec(dllimport) void* __cdecl gbAudioManager_LoadSound(void* mgr, const char* filename);
__declspec(dllimport) void __cdecl gbAudioManager_PlaySound(void* mgr, void* sound);
__declspec(dllimport) void __cdecl gbAudioManager_StopSound(void* mgr, void* sound);

// ... 其他约 90 个音频函数

// ============================================================================
// 场景管理接口（~200 个函数）
// ============================================================================

__declspec(dllimport) void* __cdecl gbSceneManager_Create(void* renderDevice);
__declspec(dllimport) void __cdecl gbSceneManager_Destroy(void* mgr);
__declspec(dllimport) void* __cdecl gbSceneManager_LoadScene(void* mgr, const char* filename);
__declspec(dllimport) void __cdecl gbSceneManager_UnloadScene(void* mgr, void* scene);
__declspec(dllimport) void __cdecl gbSceneManager_Update(void* mgr, float deltaTime);
__declspec(dllimport) void __cdecl gbSceneManager_Render(void* mgr);
__declspec(dllimport) void* __cdecl gbSceneManager_GetActiveScene(void* mgr);
__declspec(dllimport) void __cdecl gbSceneManager_SetActiveScene(void* mgr, void* scene);

// ... 其他约 192 个场景函数

// ============================================================================
// 相机接口（~50 个函数）
// ============================================================================

__declspec(dllimport) void* __cdecl gbCamera_Create();
__declspec(dllimport) void __cdecl gbCamera_Destroy(void* camera);
__declspec(dllimport) void __cdecl gbCamera_SetPosition(void* camera, float x, float y, float z);
__declspec(dllimport) void __cdecl gbCamera_SetTarget(void* camera, float x, float y, float z);
__declspec(dllimport) void __cdecl gbCamera_SetFOV(void* camera, float fov);
__declspec(dllimport) void __cdecl gbCamera_Update(void* camera, float deltaTime);
__declspec(dllimport) void __cdecl gbCamera_GetViewMatrix(void* camera, void* outMatrix);
__declspec(dllimport) void __cdecl gbCamera_GetProjectionMatrix(void* camera, void* outMatrix);

// ... 其他约 42 个相机函数

// ============================================================================
// 动画接口（~100 个函数）
// ============================================================================

__declspec(dllimport) void* __cdecl gbAnimation_Create();
__declspec(dllimport) void __cdecl gbAnimation_Destroy(void* anim);
__declspec(dllimport) void __cdecl gbAnimation_Load(void* anim, const char* filename);
__declspec(dllimport) void __cdecl gbAnimation_Play(void* anim);
__declspec(dllimport) void __cdecl gbAnimation_Stop(void* anim);
__declspec(dllimport) void __cdecl gbAnimation_Update(void* anim, float deltaTime);
__declspec(dllimport) void __cdecl gbAnimation_SetSpeed(void* anim, float speed);
__declspec(dllimport) void __cdecl gbAnimation_SetLoop(void* anim, int loop);

// ... 其他约 92 个动画函数

// ============================================================================
// 特效接口（~150 个函数）
// ============================================================================

__declspec(dllimport) void* __cdecl gbEffect_Create();
__declspec(dllimport) void __cdecl gbEffect_Destroy(void* effect);
__declspec(dllimport) void __cdecl gbEffect_Load(void* effect, const char* filename);
__declspec(dllimport) void __cdecl gbEffect_Play(void* effect);
__declspec(dllimport) void __cdecl gbEffect_Stop(void* effect);
__declspec(dllimport) void __cdecl gbEffect_Update(void* effect, float deltaTime);
__declspec(dllimport) void __cdecl gbEffect_Render(void* effect);
__declspec(dllimport) void __cdecl gbEffect_SetPosition(void* effect, float x, float y, float z);

// ... 其他约 142 个特效函数

// ============================================================================
// 总计：约 1000 个导入函数
// ============================================================================

#ifdef __cplusplus
}
#endif
```

---

## 5. 风险管理

### 5.1 技术风险

| 风险 | 可能性 | 影响 | 应对措施 |
|------|--------|------|---------|
| **R1: 字节匹配率达不到 95%** | 中 | 高 | • 建立匹配技术知识库<br>• 难以匹配函数降级为功能等价<br>• 预留充足调优时间<br>• 考虑使用 MSVC 6.0/7.0 |
| **R2: Ghidra 反编译质量不佳** | 中 | 中 | • 使用多工具交叉验证<br>• 关键函数人工阅读汇编<br>• 利用社区研究成果 |
| **R3: 复杂算法难以理解** | 高 | 中 | • 参考社区文档<br>• 逐步调试验证<br>• 容许部分函数不追求字节匹配 |
| **R4: 内存布局无法精确控制** | 中 | 高 | • 使用链接脚本<br>• 手动调整对齐<br>• 必要时修改链接器 |
| **R5: gbengine 接口不兼容** | 低 | 高 | • 详细记录接口<br>• 编写测试程序<br>• 参考原版 exe |

### 5.2 进度风险

| 风险 | 可能性 | 影响 | 应对措施 |
|------|--------|------|---------|
| **R6: 时间估算过于乐观** | 高 | 中 | • 每阶段预留 20% 缓冲<br>• 每月评审进度<br>• 优先核心功能 |
| **R7: 关键模块卡住** | 中 | 高 | • 识别关键路径<br>• 准备备用方案<br>• 定期技术攻关 |

### 5.3 质量风险

| 风险 | 可能性 | 影响 | 应对措施 |
|------|--------|------|---------|
| **R8: 引入新 bug** | 高 | 中 | • 每个函数完成后测试<br>• 回归测试套件<br>• 内存检查工具 |
| **R9: 匹配牺牲可读性** | 中 | 中 | • 注释解释技巧<br>• 保持逻辑清晰<br>• 考虑双版本 |

---

## 6. 资源需求

### 6.1 硬件需求

**开发机器：**
- CPU: Intel i5/i7 或 AMD Ryzen 5/7+
- 内存: 16GB+ RAM
- 硬盘: 100GB+ SSD
- 操作系统: Windows 10/11（64位）

### 6.2 软件工具

**必需：**
- MSVC 2022 (Visual Studio 2022)
- Ghidra 10.x+
- Python 3.8+
- Git 2.x
- Hex Editor (HxD / 010 Editor)

**可选：**
- IDA Pro / Binary Ninja
- WinDbg
- PE Tools (CFF Explorer)

### 6.3 人力投入

**单人完成：**
- 总工作量：~1500-2000 小时
- 工期：9-12 个月（每天 6-8 小时）

**团队协作（2-3 人）：**
- 总工期：6-8 个月
- 需协调沟通

---

## 7. 成功标准

### 7.1 必须达成（P0）

- ✅ 100% 函数实现（3500-5000 个）
- ✅ 核心函数字节匹配率 ≥ 95%
- ✅ 整体字节匹配率 ≥ 85%
- ✅ 编译无错误无警告
- ✅ 游戏能启动到主菜单

### 7.2 应该达成（P1）

- ✅ 完成一次完整游戏流程（通关）
- ✅ 存档系统正常工作
- ✅ 无明显 bug

### 7.3 期望达成（P2）

- ✅ 字节匹配率 ≥ 90%
- ✅ 代码文档完整
- ✅ 24 小时稳定运行

---

## 8. 交付物清单

### 8.1 代码交付

- ✅ 完整的 PAL3.exe 源代码
- ✅ 构建系统（CMakeLists.txt）
- ✅ 所有头文件和结构体定义
- ✅ Git 仓库（完整提交历史）

### 8.2 文档交付

- ✅ 架构设计文档
- ✅ 各模块详细设计文档
- ✅ API 参考文档
- ✅ 构建和测试指南
- ✅ 字节匹配技巧手册

### 8.3 测试交付

- ✅ 测试套件
- ✅ 测试报告
- ✅ 已知问题列表

### 8.4 工具交付

- ✅ Ghidra 分析脚本
- ✅ 二进制对比工具
- ✅ 进度跟踪工具
- ✅ 自动化测试框架

---

## 9. 总结

这是一个完整、详细、可行的 PAL3.exe 反编译设计方案。

**关键特点：**
- ✅ 100% 完整反编译
- ✅ 95%+ 核心函数字节匹配
- ✅ 模块化分 8 个阶段实施
- ✅ 9-10 个月可行时间线
- ✅ 完善的工具链和测试
- ✅ 充分的风险管理
- ✅ 明确的成功标准

**实施建议：**
1. 严格按照 Phase 顺序执行
2. 每个 Phase 完成后进行验收
3. 持续进行字节匹配调优
4. 建立知识库记录经验
5. 定期评审进度并调整

**预期成果：**
- 完全可编译的 PAL3.exe 源代码
- 能够完全替换原版 exe
- 游戏正常运行并通关
- 为后续 mod 和增强提供基础

---

**文档版本：** 1.0  
**最后更新：** 2026-05-01  
**下一步：** 生成详细实施计划
