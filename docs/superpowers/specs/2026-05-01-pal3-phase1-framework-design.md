# PAL3.exe Phase 1: 主框架反编译设计

## 目标

实现 PAL3.exe 游戏主框架的匹配反编译。最终交付一个能启动、创建窗口、进入消息循环的可执行文件，同时对框架中约 35 个核心/高频函数达到字节级匹配。

## 方案

自顶向下框架驱动：从 WinMain 沿调用链逐函数反编译，每个函数写完即验证字节匹配。

## 约束

- **编译器**：MSVC 2022，x86 32位，编译选项 /O2 /EHsc /GR /Oy /GF /Gy /MD
- **基地址**：0x00400000（匹配原版）
- **参考材料**：PAL3patch 命名和结构体作为参考，通过 Ghidra 反编译验证
- **外部依赖**：gbengine.dll 通过 LoadLibrary + GetProcAddress 动态加载
- **匹配标准**：.text 段代码字节逐字节匹配

## 核心调用链

```
entry (0x0055507c, 235 bytes) — CRT 启动代码
  └─ WinMain (0x00541900, 388 bytes)
       ├─ FindWindow 防双开
       ├─ SetWindowsHookEx 键盘钩子 (FUN_005417c0)
       ├─ ReadRegistry (0x00541c40, 114 bytes) — 读光驱路径
       ├─ DetectCDDrive (0x00541860, 118 bytes) — 自动检测光驱
       ├─ CheckFileExists (0x005382d0, 69 bytes) — 检查光盘文件
       ├─ PAL3_Create (0x00404800) — 游戏初始化
       │    ├─ PAL3_InitGFX (0x00404ff0) — D3D 初始化
       │    ├─ WndProc (0x00404d60) — 窗口消息处理
       │    └─ 子系统初始化...
       ├─ 消息循环
       │    ├─ gbUpdateCurTime (gbengine 外部)
       │    ├─ PAL3_Update (0x004055d0) — 每帧更新
       │    └─ FUN_00405c00 (1542 bytes) — 每帧渲染
       └─ PAL3_Destroy (0x00406230) — 清理退出
```

## 源码文件结构

```
src/pal3/
├── winmain.cpp          # entry + WinMain + 消息循环
├── pal3.cpp             # PAL3_Create, PAL3_Destroy, PAL3_Update
├── pal3_gfx.cpp         # PAL3_InitGFX, D3D 相关初始化
├── pal3_wndproc.cpp     # WndProc 窗口消息处理
├── pal3_utils.cpp       # 高频工具函数 (callers > 50)
└── gbengine_dynamic.cpp # gbengine.dll 动态加载封装

include/pal3/
├── pal3.h               # 主头文件（扩展已有）
├── pal3_game.h          # 游戏框架函数声明
├── gbengine_dynamic.h   # gbengine 动态接口声明
└── pal3_globals.h       # 全局变量定义（扩展已有）
```

## gbengine.dll 动态加载

原版 PAL3.exe 通过导入表静态链接 gbengine.dll。Phase 1 使用动态加载方便开发测试：

```cpp
// gbengine_dynamic.h
typedef void (*pfn_gbUpdateCurTime)(void);
extern pfn_gbUpdateCurTime gbUpdateCurTime;

bool LoadGBEngine();
void UnloadGBEngine();

// gbengine_dynamic.cpp
HMODULE g_hGBEngine = NULL;
pfn_gbUpdateCurTime gbUpdateCurTime = NULL;

bool LoadGBEngine() {
    g_hGBEngine = LoadLibraryA("gbengine.dll");
    if (!g_hGBEngine) return false;
    // C++ mangled names from gbengine.dll exports
    gbUpdateCurTime = (pfn_gbUpdateCurTime)
        GetProcAddress(g_hGBEngine, "?gbUpdateCurTime@@YAXXZ");
    return true;
}
```

后续 Phase 转为静态导入（使用已生成的 gbengine.lib）以匹配原版导入表。

## 字节匹配目标函数

### A. 主框架函数（8 个）

| 地址 | 名称 | 字节数 | 说明 |
|------|------|--------|------|
| 0x0055507c | entry | 235 | CRT 入口 |
| 0x00541900 | WinMain | 388 | 主函数 |
| 0x00404800 | PAL3_Create | 待确认 | 游戏初始化 |
| 0x004055d0 | PAL3_Update | 待确认 | 每帧更新 |
| 0x00405c00 | FrameRender | 1542 | 每帧渲染 |
| 0x00406230 | PAL3_Destroy | 待确认 | 退出清理 |
| 0x00404ff0 | PAL3_InitGFX | 待确认 | 图形初始化 |
| 0x00404d60 | WndProc | 待确认 | 窗口消息 |

### B. 高频工具函数（callers > 50，22 个）

| 地址 | 被调用次数 | 字节数 | PAL3patch 已知名称 |
|------|-----------|--------|-------------------|
| 0x00442390 | 733 | 136 | — |
| 0x00541d10 | 538 | 11 | — |
| 0x0043a810 | 370 | 92 | — |
| 0x00553549 | 272 | 104 | — |
| 0x00553082 | 228 | 82 | sprintf 封装 |
| 0x0055353b | 173 | 14 | operator_new |
| 0x00553514 | 155 | 39 | __ftol |
| 0x00401f90 | 134 | 11 | — |
| 0x0043dd10 | 127 | 79 | — |
| 0x004427c0 | 115 | 205 | — |
| 0x00553041 | 110 | 18 | — |
| 0x0053df70 | 95 | 6 | — |
| 0x004426b0 | 91 | 227 | — |
| 0x004a1410 | 88 | 168 | — |
| 0x00445fa0 | 80 | 52 | UIWnd_SetRect |
| 0x0043e120 | 72 | 160 | — |
| 0x005541f8 | 69 | 30 | — |
| 0x004ed010 | 67 | 46 | CCBRoleState_IsAlive |
| 0x0053e2e0 | 67 | 45 | — |
| 0x00445e50 | 62 | 17 | — |
| 0x00401f50 | 61 | 25 | — |
| 0x004407c0 | 61 | 79 | — |

### C. WinMain 直接依赖（5 个）

| 地址 | 名称 | 字节数 | 说明 |
|------|------|--------|------|
| 0x00541c40 | ReadRegistry | 114 | 读注册表光驱路径 |
| 0x00541860 | DetectCDDrive | 118 | 自动检测光驱 |
| 0x005382d0 | CheckFileExists | 69 | 检查文件存在 |
| 0x005417c0 | KbdHookProc | 待确认 | 键盘钩子回调 |
| 0x00513380 | IsGameWindow | 待确认 | 判断活动窗口 |

**总计约 35 个函数，预估 4000-5000 字节代码。**

## 全局变量处理

字节匹配关注 .text 段代码字节。全局变量的影响在于引用方式（绝对地址）。策略：

1. 在 `pal3_globals.h` 中用固定地址声明已知全局变量
2. 编译使用 `/FIXED` + 基地址 0x00400000
3. 对于需要固定地址的全局变量，使用链接器段控制：
   ```cpp
   #pragma section(".pal3g", read, write)
   __declspec(allocate(".pal3g")) int PAL3_s_gamestate;
   ```
4. 代码匹配优先，段布局后期统一调整

### 已知全局变量（来自 PAL3patch）

| 地址 | 类型 | 名称 |
|------|------|------|
| 0x00BFDA48 | HINSTANCE | g_hInstance |
| 0x00BFDA60 | gbGfxManager_D3D* | GB_GfxMgr |
| 0x00BFDA6C | int | PAL3_s_gamestate |
| 0x00BFD6C8 | gbGfxDriverInfo | PAL3_s_drvinfo |
| 0x005833B8 | int | PAL3_s_bActive |
| 0x005833BC | unsigned | PAL3_s_flag |
| 0x00BFDAA0 | float | PAL3_m_gametime |
| 0x00BFDA74 | CCBSystem* | PAL3_m_pCBSystem |
| 0x00BFAD70 | GRPinput | g_input |
| 0x01894970 | char[260] | g_cdDrivePath |
| 0x01894a74 | char[260] | g_exePath |
| 0x01895070 | double(低位) | g_lastFrameTime |
| 0x01896d10 | char* | g_cmdLine |

## 单函数反编译工作流

1. **读取 Ghidra JSON** — `asm/pal3/functions/<name>_<addr>.json`，获取反编译 C 和汇编
2. **交叉参考 PAL3patch** — 确认函数名、参数类型、结构体布局
3. **改写为可编译 C++** — 保持控制流一致，注意：
   - 局部变量声明顺序 → 栈布局
   - SEH 异常处理框架 → `__try/__except`
   - 循环形式（for/while/do-while）→ 不同指令模式
   - 类型转换表达式 → 影响指令选择
4. **编译** — `cmake --build . --config Release`
5. **字节比对** — `python tools/compare_function.py <addr> <size>`
6. **迭代调优** — 根据 diff 调整代码直到 100% 匹配

## 阶段性交付

### Phase 1a（约 1 周）：WinMain 骨架能编译运行

- entry + WinMain + 消息循环编译通过
- gbengine 动态加载层实现
- 窗口创建、消息分发正常
- 验证：exe 启动后显示窗口

### Phase 1b（约 1-2 周）：框架函数字节匹配

- PAL3_Create / PAL3_Update / PAL3_Destroy 逐个匹配
- WndProc 匹配
- PAL3_InitGFX 匹配
- WinMain 本身匹配

### Phase 1c（约 1 周）：高频工具函数匹配

- 22 个 callers > 50 的热函数逐个匹配
- 大部分 < 200 字节，预计进度较快

### 最终验收

- ~35 个函数字节匹配
- exe 能启动进入消息循环
- 进度报告显示覆盖字节数

## 不在范围内

- 子系统内部实现（战斗、UI、脚本引擎、场景管理）
- gbengine.dll 的反编译（属于独立 Phase）
- 完整 CRT 函数匹配（使用链接器提供的标准 CRT）
- 游戏逻辑还原（PAL3_Update 内部的深层 callee）
- 导入表精确匹配（Phase 1 用动态加载，后续切换）
