# DX SDK / D3DX 与系统库静态件边界调研（补充件，只读取证）

> 2026-10-28 · 只读取证调研。主报告（CRT/STL 实验）另有代理在写，本文不重复其 CRT/STL 实验，
> 仅在裁决表中交叉引用（`data/status/crt_skip_census_20261028.md`）。
> 本文只写此一个文件；所有编译/抽取实验在 `/tmp/dx_research/` 下进行，未改任何产品/标注/管线文件。
> IDA 取证走 `mcp__idapro__*`（session `278944bc`，`original/PAL3.exe.i64`）；
> 字节比对脚本 `/tmp/dx_research/coff_cmp2.py`（COFF 节 + 重定位掩码比对，可复跑）。

---

## 1. 边界定义原文（用户裁定）+ 摘要

**用户裁定原文（逐字抄录）**：

> 「静态链接与否只是表象，判据是『是否持有可重现的构建输入（同版库/同版头/同编译器+flags）』；
> 可再生产者无需逆向，链接/重编即再产。」

边界标题判据：**构建系统可再生产 ⇒ 无需逆向**。

### 摘要（结论先行）

1. **PAL3.exe 的 D3DX 面不是 DLL 导入面，而是 D3DX9 数学库 PSGP 的静态链接面**。
   exe 导入表 7 个 DLL（ADVAPI32/DINPUT8/KERNEL32/USER32/WINMM/BINKW32/GBENGINE）**零 D3DX 导入**；
   gbengine.def 与 gbengine.dll 导入表同样无任何 D3DX 导入符号（d3dx9.dll 全链缺席）。
   → 任务书/`crt_skip_census_20261028.md` 的前提「j_D3DXVec3TransformCoord 是导入跳板（D3DX 从 DLL 导入）」**被证伪**（见 §2.2 三条更名证据）。
2. **供给源在手且部分字节实证通过**：`tools/vc6/Lib/d3dx9.lib`（D3DX9 静态库，205 个 obj，obj 时间戳 2002-12-11）
   与 exe 内 3 个 D3DX 实现函数**逐字节相同**（等长 + 重定位 4B don't-care + 0 mismatch），
   另有 1 处 `d3dx9math.inl` 头内联展开与 MSVC6 同头/同 flags 编译产物**逐字节相同**（16B 核心序列）。
   ⇒ 按用户判据，这些面**属"可再生产 ⇒ 无需逆向"**，只需按库/头/编译器原样链接重编。
3. **但存在版本偏斜（供给源≠精确构建输入）**：exe 的 PSGP 调度脚手架（`_D3DXCpuOptimizations`）
   为 **73 项快速表 + new/delete 一致性检查调用**的较新构建；在手 d3dx9.lib 为 **71 项、无该检查**的旧构建
   （obj 时间戳 2002-12-11 = DX9.0 首发 SDK 世代）。项目文档所称「D3DX Summer 2003」与该偏斜方向一致。
   已按用户授权搜网下载精确版（Summer 2003 / 9.0b SDK）：**本机网络 archive.org DNS 污染不可达**，
   legacyupdate.net 403，GitHub 现存镜像均为 Jun2010/更早无关版本 ⇒ **精确件暂未到手**（详见 §3.4）。
   内核（d3dxmath.obj）逐字节一致，故实际风险收敛为「73 项调度脚手架 + 2 个新增表项」的定点重建/补给。
4. **其它系统库**：Miles / Bink / Intel JPEG / DirectInput 全部**动态导入**（无静态件），
   exe 静态面除 CRT/STL（主报告辖域）外**只有 D3DX PSGP 一系**；libpng 1.0.5 + zlib 1.1.4 静态件在
   **gbengine.dll**（不在 exe）；topo.dll 有本仓重建线（`original/build/`、`topo/`）。

---

## 2. DX 面辨识证据表

### 2.0 导入面清点（先回答任务书的「已知 D3DX 导入面」）

| 检查点 | 方法 | 结果 |
|---|---|---|
| PAL3.exe 导入表 | `objdump -p original/PAL3.exe` + IDA `imports`（session 278944bc） | 7 DLL：ADVAPI32(6) / DINPUT8(1) / KERNEL32(61) / USER32(37) / WINMM(1) / BINKW32(10) / GBENGINE(~260)。**D3DX 导入符号 = 0** |
| gbengine/gbengine.def | grep d3dx/d3d9/ddraw/dsound/dinput | 仅 2 条**含 D3DX 字样的 gb* 方法**（`??0gbRenderEffect@@AAE@PAUID3DXEffect@@I@Z` 等，是 gbEngine 自己的 API 面），**无 D3DX 导入** |
| gbengine.dll 导入表 | `objdump -p` | KERNEL32/USER32/GDI32/ADVAPI32/WINMM/**d3d9.dll**/mss32/topo/ijl15。**无 d3dx9.dll** |
| IDB 内 D3DX 名字 | `entity_query(names, regex=D3DX)` | 仅 3 个：`j_D3DXVec3TransformCoord@0x4B8200`、`j_D3DXVec3TransformCoord_0@0x542533`、`j_D3DXMatrixMultiply@0x544771` —— **三条全是错名**（§2.2） |

⇒ D3DX 与游戏代码的边界**不在导入表**，必须靠代码面辨识（下表）。

### 2.1 D3DX 面总体构成（PAL3.exe 内）

| 面 | 地址/形态 | 识别证据 | 判定 |
|---|---|---|---|
| **PSGP 调度初始化** | `0x546F41`（86 条指令，`retn 4`） | 读注册表 `"DisablePSGP"`(0x572B78)/`"DisableD3DXPSGP"`(0x572B68)；`IsProcessorFeaturePresent(6/7)`（SSE/3DNow!）；`rep movsd` 拷 0x49=73 项表 `off_6091D0 → off_6090A8`；状态字 `dword_6092F8`（0xFFFF=未初始化）。与 d3dx9.lib `cpudetect.obj` 的 `_D3DXCpuOptimizations@4` 结构逐段对应（`GetD3DRegValue`/`IsIntelSSEProcessor`/`x86/sse/sse2/x3d_D3DXInitFastTable`） | **D3DX 库产物（静态）**，版本偏斜见 §3.3 |
| **PSGP 快速表** | live 表 `off_6090A8`（73 dword）、default 表 `off_6091D0`（73 dword，x86/C 默认实现） | 表项=函数指针；`dword_6092F8` 状态字同 cpudetect.obj 的 `g_CpuOptimization`（reloc 带 -4 偏差，= `0x6092FC-4`） | **D3DX 库产物** |
| **入口跳板 + 惰性桩簇** | `0x5424xx–0x543Axx`（间距 5–13B 的微跳板簇，即普查所称"微跳板簇"） | 形态两种：`jmp [slot]`（公开入口 `_D3DXFoo@N`）与 `push 1; call 0x546F41; jmp [slot]`（惰性初始化桩）。例：`0x542533: jmp [0x6090C4]`；`0x542526: push 1; call 0x546F41; jmp [0x6090C4]`（槽初始值=桩本身，PSGPInit 后被改写为选定实现——经典惰性分派） | **D3DX 库产物** |
| **默认实现簇（c_/x86_）** | ~`0x543Axx–0x546Exx`（含 `0x544777`/`0x544884`/`0x5450B5` 等） | 与 d3dx9.lib `d3dxmath.obj` COMDAT **逐字节相同**（§3.2 三例） | **D3DX 库产物（静态）**，内核=在手库可再生产 |
| **CPU 变体簇（x3d/sse/sse2 + 安装器）** | `0x547042`/`0x5471BA`/`0x54740C`（安装器，IDA 名 `__m128::_static_547042` 等）+ `__m64/__m128::_static_*` 簇 | `_D3DXCpuOptimizations` 按 CPU 特性 push 表基址后 call 这三个安装器（分别对应 `sse_/sse2_/x3d_D3DXInitFastTable`），状态字写 3/2/1 | **D3DX 库产物**（crt_skip_census 把 `__m64/__m128::_static_*` 归"真 CRT 段/静态簇保持 skip"——**归属应改为 D3DX PSGP 变体件**，见 §6 矛盾记录） |
| **new/delete 一致性检查** | `0x547B27`（IDA 错名 `??3@YAXPAX@Z_0`） | 一次性自检（`dword_1895304` guard）：`new(0)`×2 + `delete` 探针，失败则 `OutputDebugStringA` 打印 `"D3DX: (WARN) Overloaded ::new and ::delete operators do not conform to C++ standards…"`（0x572DB0 等 4 条） | **D3DX 库产物（较新版）**——在手 d3dx9.lib **不含**这些字符串（§3.3） |
| **头内联展开（d3dx9math.inl）** | 散布在游戏代码（例：`0x41380B`，位于游戏函数 `Vec3Cross@0x413800` 内） | `D3DXVECTOR3::operator-` 内联体与 MSVC6（同头同 flags）编译产物字节相同（§3.2 例 D） | **SDK 头内联展开**（编译期来源=头文件，再生产靠同版头+同编译器） |
| **模板实例化** | 未发现 D3DX 模板面 | d3dx9math.inl 的 214 个 `D3DXINLINE` 全部是 C++ 类成员/运算符重载（D3DXVECTOR2/3/4、D3DXMATRIX、D3DXQUATERNION、D3DXPLANE、D3DXFLOAT16），无模板 | — |

### 2.2 三条 `j_D3DX*` 命名更正（全部有字节证据；均非「导入跳板」）

| IDB 名 | 地址 | 实际内容（证据） | 更正为 |
|---|---|---|---|
| `j_D3DXVec3TransformCoord` | `0x4B8200` | **游戏代码**：`if(a==b) return a; else return a + (rand()%10000+1)*flt_56F494*(b-a)` —— rand 驱动的两浮点随机插值（11 个 xref，调用者 `sg_emission_control::_todo_004BA800`、`sub_4B91E0`、`sub_4B9EA0`、`sub_4BABC0`）。与 D3DX 无关 | 建议语义名（如 `RandLerpF`），**删去 D3DX 名** |
| `j_D3DXVec3TransformCoord_0` | `0x542533` | `jmp [0x6090C4]`＝PSGP 公开入口跳板；槽 #7 default 目标 `0x5450B5`＝`c_D3DXVec3Normalize`（157B 逐字节相同，§3.2 例 C） | `_D3DXVec3Normalize@8`（PSGP 入口） |
| `j_D3DXMatrixMultiply` | `0x544771` | `jmp [0x609134]`＝PSGP 公开入口跳板；槽 #35 default 目标 `0x544777`＝`c_D3DXQuaternionSlerp`（227B 逐字节相同，§3.2 例 B）；调用方 `sub_544884`＝`c_D3DXQuaternionSquad`（Slerp×3 + `2t(1-t)` 权重） | `_D3DXQuaternionSlerp@16`（PSGP 入口） |

**连锁证据链（示例）**：`c_D3DXQuaternionSquad@0x544884` 内 3 处 `call`（reloc 24/46/76）→ `0x544771`
（= `jmp [0x609134]`），语义为 Slerp(v8,Q0,A,t)、Slerp(v9,B,Q1,t)、Slerp(out,v8,v9,2t(1-t))——
与 d3dx9math.h `D3DXQuaternionSquad` 定义逐句对应，坐实 0x544771 是 **Slerp 而非 MatrixMultiply**。

⚠️ 对 `crt_skip_census_20261028.md` 的更正：其「j_D3DXVec3TransformCoord = D3DX 导入跳板」一句不成立
（该地址是游戏函数；真正的 D3DX 件是 0x542533/0x544771 两条 PSGP 跳板与 0x5424xx-0x543Axx 整簇）。
其"`sg_emission_control` overlay 里 C2065 `j_D3DXVec3TransformCoord_0` 注释债"的处置建议仍有效，
但**解法应按更正后符号（`_D3DXVec3Normalize@8`，链接期由 d3dx9.lib 供给）供给声明**，而非按"导入跳板"。

### 2.3 PAL3A PDB 交叉印证（历史构建同型）

`original/PAL3A.pdb.xml` section_contrib 出现整套 D3DX PSGP 符号（PAL3A 映像内地址）：
`?init_D3DXVec3TransformCoord@@…`(0x32462a) · `?sse2_D3DXVec3TransformCoordArray@@…`(0x32e83e) ·
`?sse_D3DX…` · `?x86_D3DX…` · `?c_D3DX…` · `_AMDSSE_D3DXVec3TransformCoordArray@24` · `_x3d_D3DXVec3TransformCoord@12`
（undecorated 可读：`struct D3DXVECTOR3 * __stdcall sse2_D3DXVec3TransformCoord(...)` 等）。
⇒ **PAL3A 同样静态链接 D3DX PSGP**（同一代构建形态）；PDB 中 `j_D3DX` 前缀名=0 命中，说明 IDB 三条错名不是 PDB 导入，来源为人工误名（推测：按调用场景望文生义）。

---

## 3. 供给源实证（实验设计 + 输出摘录 + 字节比对结果）

### 3.0 盘库存（本仓/系统）

| 件 | 路径 | 版本线索 |
|---|---|---|
| D3DX9 头 | `tools/vc6/Include/d3dx9math.h` / `d3dx9math.inl`（214 个 D3DXINLINE）/ `d3dx9core.h` … | `d3dx9core.h:25-26`：`#define D3DX_VERSION 0x0900`、`#define D3DX_SDK_VERSION 9` |
| D3DX9 静态库 | `tools/vc6/Lib/d3dx9.lib`（4,383,332B，205 成员） | 成员时间戳 **2002-12-11 13:23**（obj/i386/*.obj）；含 `cpudetect.obj`/`d3dxmath.obj`/`d3dxmathx86.obj`/`d3dxmathsse.obj`/`d3dxmathsse2.obj`/`d3dxmathx3d.obj`/`amdmath.obj`/`arraymath.obj`/`arraymath2.obj`/`psgpmesh.obj`/`init.obj`/`pchmath.obj`…；符号系 `?c_/init_/x86_/sse_/sse2_/x3d_D3DX…@@YG…@Z`、`_AMDSSE_D3DX…`、`_D3DXCpuOptimizations@4`；字符串 `DisablePSGP`/`DisableD3DXPSGP` |
| 其余 d3dx 变体 | `tools/vc6/Lib/d3dx9d.lib`、`d3dx9dt.lib`（cpudetect 同为 `push 0x47`=71 项） | 同世代 |
| 系统其它副本 | 全盘 find：仅 `/usr/share/mingw-w64/include/d3dx9math.h`（mingw 头，无关）与 `/tmp/rev_stage3_head/…`（本仓副本） | — |

### 3.1 实验 A（头内联编译实验，/tmp 只读）

**设计**：TU `/tmp/dx_research/probe/dx_inline_probe.cpp` 用 `#include <d3dx9math.h>` 包四个函数
（`*out = *a + *b` / `*a * s` / `*a * *b` / `*a - *b`），MSVC6 实编（wine 调 cl，参照 `pipeline/probe_compile.py::run_cl`）：

```
wine Z:\...\tools\compilers\msvc6.0\Bin\CL.EXE /nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy
     /I tools\compilers\msvc6.0\Include /I tools\vc6\Include  dx_inline_probe.cpp
→ 0 error（dx_inline_probe.obj 1564B）
```

**产物摘录**（objdump -d）：

* `D3DXVECTOR3::operator-` 内联体：`d9 00 d8 21 d9 5c 24 00 d9 40 04 d8 61 04 …`（flds/fsubs/fstp ×3）
* `D3DXMATRIX::operator*` **并非算术展开**，编译为 `call _D3DXMatrixMultiply@12`（头内联=薄壳，转调库/PSGP 入口）
  —— 印证「头内联面」与「库函数面」在 ABI 上同一供给链。

**与 exe 比对**（IDA `find_bytes`，全字节直搜）：

| 函数 | 搜索序列 | 结果 |
|---|---|---|
| D3DXVECTOR3::operator- | `d9 00 d8 21 d9 5c 24 00 d9 40 04 d8 61 04`（12B+） | **命中 1 处：`0x41380B`**，位于 `Vec3Cross@0x413800` 内 —— 同寄存器分配、逐字节相同 |
| D3DXVECTOR3::operator+ | 同法 16B（eax/ecx 分配形态） | 0 命中（上下文寄存器分配不同，形态随调用点变化；不构成反证，记为"未抽到同型样本"）|
| D3DXVECTOR3::operator* (scale) | 16B | 0 命中（同上） |

### 3.2 实验 B（库函数字节比对，match 三限定）

**方法**：从 `tools/vc6/Lib/d3dx9.lib` 解出 obj（自写 COFF 归档解析，`/tmp/dx_research/libobjs/`），
按 **COMDAT 节级** 与 exe 函数比对；比对规则=任务书三限定（截断到原长度 / 等长 / 重定位 4B don't-care），
脚本 `/tmp/dx_research/coff_cmp2.py`（重定位覆盖字节免比，其余全字节）。exe 侧字节取自 `original/PAL3.exe`
（VA→文件偏移按 PE 节表换算，.text VA 0x1000 → 文件 0x1000）。

| 例 | exe 地址 | 库符号（d3dxmath.obj 节号） | 长度 | 重定位覆盖 | 不符字节 | 判定 |
|---|---|---|---|---|---|---|
| A | `sub_544884`（=D3DXQuaternionSquad 实现） | `?c_D3DXQuaternionSquad@@YGPAUD3DXQUATERNION@@PAU1@PBU1@111M@Z`（节 459） | **87 = 87 等长** | 3 站点 12B（3×call rel32） | **0** | ✅ 字节全同（三限定内） |
| B | `0x544777`（槽 #35 default 目标） | `?c_D3DXQuaternionSlerp@@YGPAUD3DXQUATERNION@@PAU1@PBU1@1M@Z`（节 453） | **227 = 227 等长** | 3 站点 12B | **0** | ✅ 字节全同 |
| C | `0x5450B5`（槽 #7 default 目标） | `?c_D3DXVec3Normalize@@YGPAUD3DXVECTOR3@@PAU1@PBU1@@Z`（节 542） | **157 = 157 等长** | 3 站点 12B | **0** | ✅ 字节全同 |
| D | `0x41380B`（Vec3Cross 内联体，实验 A） | `d3dx9math.inl` `D3DXVECTOR3::operator-`（tools/vc6/Include） | 核心序列 12B+ 精确命中 | 0 | **0** | ✅ 头内联字节同 |

**输出摘录**（原样）：

```
---slerp---
section 453 '.text' size 227 relocs [45, 86, 103]
obj fn len 227 exe fn len 227
compared 227 reloc-covered bytes 12 mismatches 0 []  LEN EQUAL
---tcoord(实为 Vec3Normalize)---
section 542 '.text' size 157 relocs [59, 86, 107]
obj fn len 157 exe fn len 157
compared 157 reloc-covered bytes 12 mismatches 0 []  LEN EQUAL
---squad---
section 459 '.text' size 87 relocs [24, 46, 76]
obj fn len 87 exe fn len 87
compared 87 reloc-covered bytes 12 mismatches 0 []  LEN EQUAL
```

**覆盖度**：任务书要求 ≥2 函数（1 头内联 + 1 库函数/第二内联）——实际 **1 头内联 + 3 库函数**，全部字节实证通过。

### 3.3 版本偏斜（供给源 ≠ 精确构建输入）——矛盾如实记录

| 对比点 | exe（`0x546F41` = `_D3DXCpuOptimizations@4`） | 在手 `tools/vc6/Lib/d3dx9.lib` `cpudetect.obj` | 判定 |
|---|---|---|---|
| 快速表项数 | `push 0x49` = **73 项**（live `0x6090A8→0x6091CC`，default `0x6091D0`） | `push 0x47` = **71 项** | **不一致** |
| 入口序列 | `push esi; push edi; call 0x547B27`（new/delete 一致性检查）**再** `cmp [ebp+8],0` | `cmp [ebp+8],0` **先于** push esi/edi，**无**该 call | **不一致**（指令调度+插call） |
| `"D3DX: (WARN) Overloaded ::new and ::delete…"` 4 串 | exe 在（0x572CC8–0x572DB0） | d3dx9.lib **全库字符串检索无** | **不一致** |
| 版本横幅 | exe 无版本串；gbengine.dll 有 `"Microsoft (R) D3DX9 Shader Assembler 4.09.00.1126"`/`"D3DX9.1 Effect Compiler"` | d3dx9.lib 无 `4.09.00` 串 | gbengine 侧 D3DX 亦非在手库同版 |
| 数学内核（d3dxmath.obj） | 例 A/B/C **逐字节相同** | 同 | **一致** |

⇒ 在手库=**旧世代**（2002-12-11，DX9.0 首发 SDK 世代）；exe=**较新世代**（73 项 + new/delete 检查），
与项目文档「D3DX Summer 2003」方向一致（**推测**：精确件即 DirectX 9.0 SDK Update (Summer 2003) / 9.0b 的 d3dx9.lib；
未到手前不升格为结论）。按用户判据的裁定：
**内核面=可再生产（在手库字节实证）；PSGP 调度脚手架=近似可再生产（差 2 表项 + 1 处 call/调度），精确件补到后可完全免逆向。**

### 3.4 精确件下载尝试（用户授权后实录）

* web_search 定位：MS 下载中心 FamilyId=`9216652F-51E0-402E-B7B5-FEB68D00F298`
  （"DirectX 9.0 SDK Update - (Summer 2003)"，Wayback 快照可查）；archive.org 条目 **`dx90bsdk`**
  （"Microsoft DirectX 9.0b SDK"，2003-07-17，218.1MB，`dx90bsdk.exe` 自解压）。
* 可达性实测：`archive.org` / `web.archive.org` / `ia801504.us.archive.org` 全部 **TCP 超时**；
  `getent hosts archive.org` 返回 `2a03:2880:…`(Meta 段) 与 IPv4 `198.44.185.131`——**DNS 污染特征**；
  DoH（cloudflare-dns.com）返回 `104.244.43.228`（Twitter 段）同为污染；allorigins/codetabs/corsproxy/r.jina.ai 代理均失败。
  `legacyupdate.net` 403；dssz.net / csdn / 百度盘均需登录/积分。
* GitHub 实测镜像：`madebr/dxsdk`（D3DX1/2 世代）、`walker-WSH/DXSDK`、`devKlausS/dxsdk`、`NovaRain/DXSDK_Collection`
  （Aug2007/Feb2010/Jun2010）、`sigmaco/dxsdk`（Jun2010）、`prefetchnta/dxsdk_old`（DXSDK10/20/30）——**无 Summer 2003 件**。
* **结论：精确件暂未到手，留待补给（见 §6）**。一旦到手只需对 `cpudetect.obj` 重跑 §3.2 同款比对即可定谳。

---

## 4. 其它系统库裁决表（除 CRT/STL/DX）

exe 形态证据：导入表（§2.0）+ 全串扫描（`strings original/PAL3.exe`）+ 已知名（`_sprintf` 等归主报告）。

| 库 | 在 PAL3.exe 的形态 | 证据 | 供给源是否在手 | 裁决（按用户判据） |
|---|---|---|---|---|
| CRT/STL（MSVC6 SP0） | 静态（0x55xxxx 真 CRT 段等） | 主报告辖域；交叉引用 `crt_skip_census_20261028.md`（`_sprintf`/`_rand`@0x5541F8/`??2@YAPAXI@Z` 等） | **在手**（`tools/compilers/msvc6.0/`） | 可再生产（主报告验证） |
| D3DX9 数学 PSGP | **静态**（§2.1 全表） | 字节实证 3 例 + 头内联 1 例 | **在手但版本偏旧**（§3.3） | 内核可再生产；调度脚手架待精确件（边缘情形） |
| Direct3D 9 | 动态（gbengine.dll → d3d9.dll） | gbengine 导入表 | 系统运行时 | 无需逆向 |
| Miles Sound System | **动态**（gbengine.dll → mss32.dll；`original/Mss32.dll` 随附） | exe 零 AIL_/mss 串（仅 `_BinkOpenMiles@4` 这个 Bink 导入名）；gbengine 导入 `_AIL_*@N` 一系 | 运行时 DLL 在手 | 无需逆向（若重链 gbengine 需 mss32.lib——归 gbengine 线） |
| Bink Video | **动态**（exe 直接导入 BINKW32.DLL 10 符号：`_BinkOpen@8`/`_BinkDoFrame@4`/`_BinkCopyToBuffer@28`/`_BinkOpenMiles@4`…） | exe 导入表 + `original/binkw32.dll` 随附 | 运行时 DLL 在手 | 无需逆向 |
| Intel JPEG Library (ijl15) | **动态**（gbengine.dll → ijl15.dll；`original/ijl15.dll` + `lib/ijl15.def/.lib`） | gbengine 导入表 | 在手 | 无需逆向 |
| libpng 1.0.5 + zlib 1.1.4 | **静态、但在 gbengine.dll 不在 exe** | gbengine.dll 串：`deflate 1.1.4 Copyright 1995-2002` / `inflate 1.1.4 …` / `@Incompatible libpng version…`；exe 无 | **不在手**（来源推测=D3DX 纹理件或自嵌；`d3dx9.lib` 串里有 `libpng version 1.0.5` ⇒ **推测** gbengine 静态链了 d3dx9.lib 的纹理面） | exe 裁决=不适用；gbengine 线=边缘情形（退化为逆向对象或补 D3DX 纹理件供给） |
| topo.dll | 动态（gbengine.dll → topo.dll） | 本仓重建线：`topo/`（CMake+def）、`original/build/`（topo.dll/lib/map）、`original/topo.dll` | **在手**（自有件） | 无需逆向（gbengine 线） |
| DirectInput 8 | 动态（exe → DINPUT8.DLL `DirectInput8Create`） | exe 导入表 | 系统运行时 | 无需逆向 |
| 其它（Miles/Bink 之外的音频视频编解码、加密狗、压缩库…） | 未发现 | exe 全串扫描无 zinflate/lzo/crypt/hasp 等特征串 | — | — |

**裁决总结**：exe 的静态系统件 = **CRT/STL（主报告）+ D3DX PSGP（本文）**，别无其它。
Miles/Bink/JPEG/DInput 全部动态导入 ⇒ 不落入"静态件逆向"面。唯一退化为逆向对象的边缘件是
**gbengine.dll 内的 libpng/zlib 静态面**（不在 exe，归 gbengine 重建线裁定）。

---

## 5. 完备性 spec（登记 schema + 验证环）

### 5.1 「系统库静态件清单」登记 schema（建议落 `data/annotations/system_lib_statics.json`）

每个条目 = 一个**可字节定位的系统库产物单元**（一个库函数 / 一段头内联展开 / 一簇变体实现）：

```jsonc
{
  "id": "d3dx9.c_D3DXVec3Normalize",            // <库>.<符号或语义名>，无名件用 addr 哈希
  "kind": "dx-d3dx",                             // crt | stl | dx-d3dx | dx-d3d | third-party-static
  "symbol": "c_D3DXVec3Normalize",               // 库内符号（mangled 原名），头内联件=头文件符号
  "exe_ranges": [ {"start": "0x5450B5", "end": "0x545152"} ],   // IDA 可解析地址区间（多区间可列）
  "supply": {
    "source": "tools/vc6/Lib/d3dx9.lib",         // 供给源路径（仓内相对路径）
    "member": "obj/i386/d3dxmath.obj",           // 归档成员（头内联件填头文件路径）
    "comdat_section": 542,                       // obj 内节号（头内联件填 行号区间）
    "version": "D3DX9, lib obj ts 2002-12-11, D3DX_SDK_VERSION 9",
    "exact_version_match": false                  // 与 exe 实际构建输入是否同版（§3.3 的偏斜位）
  },
  "build": { "compiler": "MSVC6.0 SP0", "flags": "/O2 /Ob2 /Oi /Ot /Oy", "link_mode": "static|inline-header" },
  "verify": {
    "status": "byte-match",                      // byte-match | byte-match-exact-version | mismatch | unverified
    "method": "3qual: truncate-to-orig / equal-len / reloc-4B-dontcare",
    "evidence": [ {"exe": "0x5450B5", "len": 157, "len_rule": "equal", "reloc_bytes": 12, "mismatch": 0,
                   "at": "2026-10-28", "tool": "/tmp/dx_research/coff_cmp2.py"} ],
    "naming_fix": {"old_ida_name": "j_D3DXVec3TransformCoord_0", "new_name": "_D3DXVec3Normalize@8",
                   "evidence": "slot#7 default target 0x5450B5 == lib sec542"}
  },
  "disposition": "no-reverse-needed"             // no-reverse-needed | reverse-edge（供给源不在手/不匹配）| reverse-target
}
```

### 5.2 验证环（每供给源至少一例字节实证 + 新疑似件入册流程）

**环 0（供给源登记）**：`supply.source` 必须是可复指路径（仓内或记录下载 URL+SHA），
`exact_version_match=false` 的条目必须写明偏斜点（如"73 vs 71 表项"）与补给计划。

**环 1（字节实证闸）**：每个供给源（库/头）**至少一例**走 §3.2 三限定比对并把 `(len_rule, reloc_bytes, mismatch)` 三元组写进 `verify.evidence`；
`mismatch>0` ⇒ `status=mismatch` ⇒ 自动降级 `disposition=reverse-edge`，禁止标 `no-reverse-needed`。

**环 2（新疑似 SDK 代码入册流程）**，六步、只读：
1. **线索**：指令形态（x87 三点积/lerp 簇）、常量表（flt_56F494 类）、字符串（`DisablePSGP`/`D3DX: (WARN)`）、地址分布（0x5424xx-0x543Axx 跳板簇）；
2. **定位供给源**：库成员（`nm/objdump -t` 按符号/节）或头文件行（d3dx9math.inl 的 D3DXINLINE）；
3. **复现**：库件=解 obj；头内联= /tmp wine cl 编 TU（同头同 flags，参照 `pipeline/probe_compile.py::run_cl`）；
4. **比对**：`coff_cmp2.py` 三限定（等长/截断/重定位 don't-care）；
5. **入册**：写 schema 条目；若与 IDB 现名冲突 → 同条 `naming_fix` 记录并**提议** IDA 更名（标注改动仍走 annotation 证据纪律，本调研不落改）；
6. **复核**：`evidence` 至少 1 例由第二轮独立重跑脚本核对（脚本可复跑是关键）。

**环 3（回归钩）**：清单变更须与 `pipeline/cli.py match` 的 L1 读数并读——系统库静态件**不应**计入游戏逻辑匹配目标；
若某 `d3dx9.*` 条目被误收进游戏函数 match 集，属登记错误（反向信号）。

**环 4（命名更正环）**：`j_D3DX*` 三例的更正须成对记录（old→new→evidence），
任何后续会话引用 `j_D3DXVec3TransformCoord*`/`j_D3DXMatrixMultiply` 时必须注明"已被字节证据更正，勿再据名推断语义"。

---

## 6. 遗留未知 / 矛盾记录

1. **精确版 D3DX 未到手**（最大未知）：Summer 2003 / 9.0b 的 `d3dx9.lib`（73 项快速表 + new/delete 检查）
   下载受阻（§3.4）。补给后需对 `cpudetect.obj` 重跑 §3.2 比对定谳；在手期间
   「73 vs 71 的 2 个新增表项分别是什么函数」未知（槽位表 73 项**只命名了 2 项**：#7=Vec3Normalize、#35=QuaternionSlerp）。
   完整槽位命名可按 §5.2 环 2 批量做（对 73 个 default 表目标逐个与 d3dxmath.obj 试配）。
2. **0x54474D 的库符号未定谳**：`push 1; call 0x546F41; fld [arg_C]; …; call [0x609134]; ret 10`
   （36B，含参数编组）——语义=D3DXQuaternionSlerp 的 C++ 重载/惰性桩形态，但与在手库
   `init_D3DXQuaternionSlerp`/`c_D3DXQuaternionSlerp` 均非等长，**未做**逐字节配对（记"待核"）。
3. **j_D3DXVec3TransformCoord_0（0x542533）名字是按槽#7 更正的**；sg_emission_control 实际调用语义
   （粒子发射用 Vec3Normalize 合理）与更正一致，但**未逐调用点复核**。
4. **头内联面抽样偏窄**：仅 operator- 命中同型样本（operator+/scale 因寄存器分配上下文不同未抽到）。
   更系统的做法是按"内联体核心形态库"（fld/fadd 三连等）做模糊检索——记为后续工作。
5. **libpng/zlib 在 gbengine.dll 的来源未定**：`d3dx9.lib` 串里含 `libpng version 1.0.5` ⇒ **推测** gbengine
   静态链了 D3DX 纹理件（同一次链接），但未做 gbengine.dll↔lib 的字节比对（gbengine 线辖域）。
6. **矛盾如实记录**：
   - 任务书前提「j_D3DXVec3TransformCoord 是导入跳板（D3DX 从 DLL 导入）」→ **证伪**（§2.0/2.2）。
   - `crt_skip_census_20261028.md` 同句 + 「`__m64/__m128::_static_*` 簇=真 CRT/静态簇保持 skip」
     → 后者应更正为 **D3DX PSGP CPU 变体件**（0x547042/0x5471BA/0x54740C 是 `sse_/sse2_/x3d_D3DXInitFastTable`
     安装器，由 `_D3DXCpuOptimizations` 直调）；其 skip 结论可维持（链接期由库供给）但**理由要换**。
   - IDA 对 0x546F41/0x547B27 的自动名（`CRT_scalar_delete`/`??3@YAXPAX@Z_0`）均为误名——
     引用这两处须带本报告更正。
7. **D3DX_SDK_VERSION 9 的发布对应关系未考证**（在手头文件自述值；与"Summer 2003"的版本号序列关系待精确件到手后一并定谳）。

---

### 附：可复跑命令清单

```bash
# 导入表
objdump -p original/PAL3.exe | grep -i "DLL Name"
# 库成员解包（自写 COFF 归档解析）
python3 /tmp/dx_research/ghget.py …   # （下载用）
python3 /tmp/dx_research/coff_cmp2.py 'libobjs/obj\i386\d3dxmath.obj' <节号> <exe函数hex>
# 头内联实验（/tmp）
wine Z:\...\CL.EXE /nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /I tools\vc6\Include dx_inline_probe.cpp
# IDA 侧
idb_open(input_path="original/PAL3.exe.i64"); entity_query(names, regex="D3DX"); find_bytes(...)
```
