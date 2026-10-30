# 跳板（thunk/jump trampoline）识别与消解机制调研（2026-10-28）

> 只读取证调研。IDA 证据源：`original/PAL3.exe.i64`（idapro MCP session `278944bc`，2026-10-28）。
> 语料：`data/annotations/skip_functions.json`（1910 条）· `gbengine/gbengine.def`（1021 导出）·
> `asm/pal3/decomp/*.json`（3695）· `pal3/src/` · `tools/vc6/Lib/d3dx9.lib`。
> 所有结论带地址+指令字节；推测均标「推测」。本文件为唯一写入物，未动任何产品/标注/管线文件。

---

## 1. 结论摘要

### 1.1 分类学表（全部跳板族）

| # | 族 | 指令形态特征（字节签名） | 地址分布 | 数量 | 性质 |
|---|---|---|---|---|---|
| T1 | **PE 导入跳板（gbengine.dll）** | 6B `FF 25 imm32`（jmp [IAT@0x56Axxx]） | 0x542072–0x54212C 连排 | 31 | 链接器从 gbengine 导入库生成 |
| T2 | **PE 导入跳板（系统库）** | 6B `FF 25 imm32`（jmp [IAT]） | 0x55EF80 `DirectInput8Create`(DINPUT8)、0x55EF86 `RtlUnwind`(KERNEL32) | 2 | 同上（dinput8.lib/kernel32.lib） |
| T3 | **D3DX PSGP 分发跳板（=「微跳板簇」）** | A 形 13B `6A 01 E8 rel32 FF 25 [分发表]`（push 1; call init; jmp [slot]）· B 形 6B `FF 25 [分发表]` · C 形 17B `55 8B EC 6A 01 E8 rel32 5D FF 25 [分发表]` | 0x5424BA–0x546xxx；微簇 0x5424xx–0x543Axx | 微簇 34（A11/B12/C11）；全区 55（A17/B22/C16） | d3dx9.lib 静态 PSGP 分发层 |
| T4 | **D3DX PSGP 本体**（init + generic/MMX/SSE/3DNow 实现 + 分发表） | init: SEH-less 长函数 @0x546F41；generic 42–209B；表 @0x6090A8(73 槽)+模板 @0x6091D0 | 0x542169–0x546B0E + .data 0x6090A8 | ~70 函数 + 2 表 | 同 T3（静态链接，非导入） |
| T5 | **单例/静态对象 this 装载跳板（SingletonThunk）** | 10B `B9 imm32 E9 rel32`（mov ecx,&obj; jmp method） | 0x4044B0–0x53DF60 散布 | 45（另 1 个同形误归 compiler_thunk：0x53C890） | MSVC6 静态对象 ctor/dtor 跳板 |
| T6 | **this-adjustor 跳板** | 8B `83 E9 imm8 E9 rel32`（sub ecx,N; jmp target） | 0x41BE20(sub 0x38)·0x4506C0(sub 0x48)·0x451800·0x451C70·0x47E570(sub 0x48)·0x4C88B0/0x4C9530/0x4CB340/0x4CD9F0/0x4D5850(sub 0x0C) | **10** | 多继承 this 调整，编译器产物 |
| T7 | **5B 直跳别名（ILT/COMDAT/tail-jmp 族）** | 5B `E9 rel32` + `90 90 90` 对齐填充，目标多在 +0x10 | 全文散布（compiler_thunk 筐 188 + reason:thunk 筐内 `_nearby_`/j_ 多数） | ≈300+（仅 compiler_thunk 筐可数 188） | 链接器/编译器布局产物 |
| T8 | **10B 胶水跳板** | `E8 rel32 E9 rel32`（call 真身/跳板; jmp atexit 登记段） | 与 T7 交错（0x401BB0/0x401BF0/0x401C30`$E153`…） | 28（compiler_thunk 筐）+ 真名件（PalScript::_StaticInit 0x431D80 等） | MSVC6 静态初始化胶水 |
| T9 | **SEH 构造/析构包装** | `6A FF 68 <handler> 64 A1 00 00 00 00 50 64 89 25 00...` + 真身（含 vtable 写入） | 0x43A1F0·0x43A810·0x4411D0 | 3 | SEH 包装的完整函数（非纯跳板） |
| T10 | **vcall 包装/wrapper**（Hex-Rays `// attributes: thunk`） | 短真身：存 this 字段 + call 真 impl + `ret n`，或 5B 转发 | 散布 | 85 个 decomp 文件带该标 | 源码级薄包装 |
| T11 | **名实不符筐（其它）** | j_ 前缀但为真函数体 | 0x41CA30(90B)·0x41D590(20B)·0x485DC0(34B)·0x4B8200(66B)·0x5044F0(23B)·0x401800(1B `C3`) | 6 | 命名债，非跳板 |
| T12 | **CRT/STL 跳板** | 5B `E9` | 0x504E20→0x4D70B0(std::codecvt_base::do_always_noconv)·0x505400(双跳) | 2–3 | CRT/STL 库供给 |

### 1.2 合理性裁决表（字节匹配 + 可链接 双目标；a=源码显式重写 b=编译器自动再生 c=链接期库/导入表供给 d=手工合成 stub）

| # | 族 | 裁决 | 理由（一句话） | 现状处置 | 现状合理性 |
|---|---|---|---|---|---|
| T1/T2 | 导入跳板 | **(c)** | 导入库（gbengine.lib/dinput8.lib/kernel32.lib）在链接期生成同形 `FF 25` 跳板，源码只需正常 extern 声明 | skip(crt_runtime 筐) | 处置方向对、**reason 错**（不是 CRT） |
| T3/T4 | D3DX PSGP 全家 | **(c)** | d3dx9.lib 静态供给整个 PSGP 子系统（已在 `tools/vc6/Lib/d3dx9.lib`，含 `DisablePSGP`/`DisableD3DXPSGP`/`c_*`/`SSE_*` 符号、0 个 `__imp__D3DX*`）；**调用点应以 D3DX API 真名+SDK 头声明** | skip(crt_runtime 筐) | 方向对、reason 错；**调用点声明缺失=C2065 事故根因** |
| T5 | SingletonThunk | **(b)** 优先，(d) 保底 | MSVC6 对命名空间级静态对象（非平凡 ctor/dtor）的固定产物（ctor/dtor 跳板+atexit 注册）；源码恢复全局对象定义即再生 | skip + 6 个 functions.json `declaration_only` | **不合理**：有声明无定义体 ⇒ 链接期 LNK2001 待爆；且 skip_reason 字节描述错误 |
| T6 | adjustor thunk | **(b)** | 偏移（0x38/0x48/0x0C）必须由继承布局推导，MSVC6 自动产出 `sub ecx,N; jmp`；手写即错 | skip(compiler_thunk/thunk) | 处置方向对（不手写），但未利用（b）再生，字节匹配无落位路径 |
| T7 | 5B/10B ILT·别名 | **(b)** 能再生者优先，**(d)** 纯布局桩 | tail-jmp 别名（如 dtor→base dtor）可由源码写法再生；纯 ILT/COMDAT 桩是布局产物，保底用 `__declspec(naked)`+`_asm jmp` 手工合成 | skip(compiler_thunk/thunk) | 抑制可接受，但**无验证环**（跳板字节不进 match） |
| T8 | 10B 胶水跳板 | **(b)** | 静态初始化胶水（call 构造跳板→jmp atexit 登记段），MSVC6 按全局对象自动产出 | skip | 同 T5：链上真身（如 SingletonThunk）无定义体则胶水再生也断链 |
| T9 | SEH 构造/析构包装 | **(b)** | 源码成员 ctor 可抛/有 try 时 MSVC6 自动包 SEH prologue；`decompile None` 不是 skip 理由 | skip(seh_thunk) | **不合理**：体是完整可反汇编的真身（vtable 写入+ctor 链），跳过=丢定义体 |
| T10 | vcall 包装 | **(a)/(b)** 按字节裁判 | 现状已正确：decomp→codegen 生成体（Actor.cpp:2268 实证） | 正常导出+codegen | **合理** ✓ |
| T11 | 名实不符 | **正名+走正常流程** | 不是跳板问题，是命名/归属债 | 混杂：0x4B8200 被当真函数生成**错误签名**的定义体；0x41CA30/0x41D590 被 skip 但为真函数 | **不合理**（双向都错） |
| T12 | CRT/STL 跳板 | **(c)** | CRT/STL 库链接期供给（同版 MSVC6 CRT 保证字节） | skip | 合理 ✓ |

---

## 2. 逐类取证

### T1/T2 导入跳板（`FF 25 [IAT]`，6B）

字节实证：
- `0x542072: FF 25 18 A5 56 00` = jmp [0x56A518]，IDA 目标名 `__imp_?EnableShadow@gbGeomNode@@UAEXH@Z`（gbengine.def 导出）；
- `0x55EF80 DirectInput8Create: FF 25 1C A0 56 00` → [0x56A01C]（DINPUT8，导入表仅 1 个导入）；
- `0x55EF86 RtlUnwind: FF 25 90 A0 56 00` → [0x56A090]（KERNEL32）；其后 `CC CC CC CC` 填充，0x55EF90 起为真函数。

导入表全量（enum_import_names 实测）：**ADVAPI32(6)/DINPUT8(1)/KERNEL32(28)/USER32(34)/WINMM(1)/BINKW32(10)/GBENGINE(80)** —— 无任何 d3dx*.dll / d3d9.dll。
6B `FF 25` 全文共 55 个 = IAT 目标 33（31 个 gbengine 连排 @0x542072–0x54212C + DirectInput8Create + RtlUnwind）+ PSGP 分发表目标 22（见 T3）。

⚠️ 名实漂移：skip_functions.json 给 0x542072 起的条目挂 gbengine.def 导出名（`?EnableShadow@gbGeomNode@@UAEXH@Z`…），IDA 同址却叫 `?WeatherEffectNode_adjthunk1@...`——两套名字都不是「adjustor」，是导入跳板被误冠 adjthunk（T6 的污染源）。
地址分布与数量：0x542072–0x54212C 一格 6 字节共 31 个（0x5420D8/0x5420DE 两格为 `?EnableShadow@ScreenEffectMgr@@…` 等）。

### T3 微跳板簇 = D3DX PSGP 分发跳板（重点：≥10 样本实测）

**实际反汇编/字节样本**（0x5424xx–0x543Axx，形态三型）：

| 型 | 样本地址 | 字节 | 反汇编语义 |
|---|---|---|---|
| A(13B) | 0x5424BA | `6A 01 E8 80 4A 00 00 FF 25 A8 90 60 00` | push 1; call 0x546F41(PSGP init); jmp [0x6090A8](槽0) |
| B(6B) | 0x5424C7 | `FF 25 A8 90 60 00` | jmp [0x6090A8](槽0，同上槽) |
| C(17B) | 0x5424CD | `55 8B EC 6A 01 E8 6A 4A 00 00 5D FF 25 94 91 60 00` | push ebp; mov ebp,esp; push 1; call init; pop ebp; jmp [0x609194] |
| A | 0x5424DE | `6A 01 E8 5C 4A 00 00 FF 25 CC 90 60 00` | push 1; call init; jmp [0x6090CC] |
| B | 0x5424EB | `FF 25 CC 90 60 00` | jmp [0x6090CC] |
| C | 0x5424F1 | `55 8B EC 6A 01 E8 46 4A 00 00 5D FF 25 98 91 60 00` | 同 C 形，槽 [0x609198] |
| A | 0x542502 | `6A 01 E8 38 4A 00 00 FF 25 BC 90 60 00` | jmp [0x6090BC] |
| B | 0x54250F | `FF 25 BC 90 60 00` | 同槽 |
| C | 0x542515 | `55 8B EC 6A 01 E8 22 4A 00 00 5D FF 25 9C 91 60 00` | 槽 [0x60919C] |
| A | 0x542526 | `6A 01 E8 14 4A 00 00 FF 25 C4 90 60 00` | jmp [0x6090C4] |
| **B** | **0x542533 = j_D3DXVec3TransformCoord_0** | `FF 25 C4 90 60 00` | **jmp [0x6090C4]（事故主角）** |
| A | 0x542798 / 0x5428EE / 0x542918 | 同 A 形 | 槽 [0x6090AC]/[0x6090D0]/[0x6090C0] |
| **B** | **0x544771 = j_D3DXMatrixMultiply** | `FF 25 34 91 60 00` | jmp [0x609134] |

**它们是什么（定谳）**：0x6090C4 等目标不在 IAT（0x56Axxx）而在 .data **PSGP 分发表**（0x6090A8 起 0x124=73 槽×4B；模板表 0x6091D0）。表初值指向 A 形懒初始化跳板，运行时被 init 改写为真身：
- init @0x546F41（被误命名 `CRT_scalar_delete`）：`rep movsd` 复制模板 0x6091D0→0x6090A8（0x49 个 dword）→ 读注册表 `"DisablePSGP"`/`"DisableD3DXPSGP"`（字符串 @0x572B68/0x572B78）→ `IsProcessorFeaturePresent(6/7)` + `crt_sub_00546E9C()&8` 选型 → `__m64::_static_54740C`（MMX）/`__m128::_static_547042`（SSE）/`__m128::_static_5471BA`（3DNow?）改写分发表；
- 模板槽位指向 generic C 实现：槽[7] tmpl=0x5450B5（字节 `55 8B EC 83 EC 0C 56 8B 75 0C D9 46 08 …` = 矩阵×向量变换真身）、槽[35] tmpl=0x544777（矩阵乘法真身）。

⇒ 这是 **D3DX9 数学库的 PSGP（Processor-Specific Generic Processor）运行时 CPU 分发机制**，整个子系统静态链接于 exe。**库证**：`tools/vc6/Lib/d3dx9.lib` 含 `?c_D3DXVec3TransformCoord@@…`（generic）、`?SSE_D3DXVec3TransformArray@@…`、`?D3DXPSGP*`、`??_C@_0BA@…@DisableD3DXPSGP` 等 782 个相关符号，`__imp__D3DX*` = 0（纯静态，非导入）。

配套本体数量：generic 真身约 30 个（42–209B，如 sub_5422B7 42B、sub_542539 42B、sub_542563 174B、sub_54263B 209B）+ `__m64/__m128/_static_*` 优化实现簇（0x547042–0x552116，百余）+ init。

### T5 SingletonThunk（45 个）

字节实证（全部 45 个均 10B 同形）：
- `0x4044B0: B9 60 AB BF 00 E9 B6 D3 02 00` = mov ecx, 0x00BFAB60; jmp 0x431870
- `0x434BA0: B9 C0 E4 D8 00 E9 B6 7F FE FF` = mov ecx, 0x00D8E4C0; jmp 0x41CB60（任务所述实例）
- `0x431D90: B9 38 C3 D8 00 E9 26 6E FD FF` = mov ecx, 0x00D8C338; jmp 0x408BC0

⚠️ **skip_reason 文档口径错误**：自述「mov ecx,[0x00D8E4C0]」（内存加载），实际字节 `B9` = `mov ecx, imm32`（**取对象地址**，即 this=&g_obj）。证据级：A 级（指令字节）。

**它们是什么（定谳）**：xref 实测成对出现于 MSVC6 静态对象初始化链——
- 0x431D80 `PalScript::_StaticInit`（10B 胶水）: `call 0x431D90(ctor 跳板); jmp 0x431DA5(登记段)`，登记段= `push 0x431DB0(dtor 跳板); call _atexit; pop; ret`；
- decomp `PalScript_StaticInitvoid_00431d80.json` 合并视图 = `SingletonThunk_00431D90(this); atexit(SingletonThunk_00431DB0);`；
- functions.json 对 0x431D90 的自述：「Iostream_init::Iostream_init(&unk_D8C338) 0 参 CRT iostream 静态初始化跳板」。
⇒ **MSVC6 对命名空间级静态对象（非平凡 ctor/dtor）自动产出的 ctor/dtor 跳板**（ctor 对、dtor 对经 atexit 注册），「singleton accessor」是部分实例的语义近似，机制统一为 this 装载尾跳。

### T6 this-adjustor（10 个）

- `0x4506C0 _UICaption_adjthunk: 83 E9 48 E9 A8 FC FF FF` = sub ecx, 0x48; **jmp 0x450370 `_sdtor_15`**（任务所述实例，「内调 sdtor_15」成立——目标是 scalar deleting dtor 形态：`56 8B F1 E8 18 00 00 00 F6 44 24 08 01 74 09 56 E8 …` = 调基类 dtor → test [esp+8],1 → operator delete）；
- 其余 9 个：0x41BE20(sub 0x38)、0x451800/0x451C70/0x47E570(sub 0x48 → sdtor)、0x4C88B0/0x4C9530/0x4CB340/0x4CD9F0/0x4D5850(sub 0x0C → 各类 Create/Task 方法)。
- IDA 中另有 25 个 `*_adjthunkN*` 名字挂在 T1 导入跳板上（0x542072–0x542126），系命名污染，非 adjustor。

### T7/T8 5B 直跳 + 10B 胶水

- compiler_thunk 筐 217 条实测拆分：**5B `E9`×188 + 10B `E8..E9..`×28 + 误归 1**（0x53C890 实为 T5 形态 `B9 C0 1E 7B 01 E9 …`）。
- 5B 样本：`0x401840: E9 0B 00 00 00` → jmp 0x401850（+0x10，16B 对齐布局）；`0x44BE70 j_UIFrameWnd::~UIFrameWnd: E9 1B 65 FF FF` → jmp 0x442390 `??1UIFrameContainer`（远距别名：派生类平凡 dtor 尾跳基类 dtor）；`0x452560 NavFaceLayer::GetVertexBuf: E9 0B 00 00 00` → 0x452570。
- 10B 样本：`0x401BB0: E8 0B 00 00 00 E9 16 00 00 00` = call 0x401BC0(`mov ecx,0x7CC178; jmp [IAT]` 静态对象构造跳板) ; jmp 0x401BD0(`68 E0 1B 40 00 E8 67 14 15 00 59 C3` = push 0x401BE0; call _atexit-ish; pop; ret 登记段)。xref：0x401BB0 被 **.data 表 0x58001C** 引用、0x401840 被 0x580008 引用（初始化/回调表）。
- reason:thunk 筐 135 条抽样同形（`GRPinput::SetMouseLimits_2b80`/`Array::_nearby_411770`/`RoleSystem::_nearby_414a00` 等均 5B `E9 0B 00 00 00`）。
- **机制判定**：+0x10/16B 对齐 + `90 90 90` 填充 + 表引用 ⇒ 布局跳板（ILT/COMDAT 簇）；`jmp +0x10` 邻接型与远距别名型（tail-jmp）混在同筐。精确生成器归属（/INCREMENTAL ILT vs COMDAT 折叠 vs 编译器尾跳）**逐个待复核（推测）**。

### T9 SEH 包装（3 个）

- `0x43A1F0 (?ctor@PalScript) 92B / 0x43A810 (?Destroy2@UICaption) 92B / 0x4411D0 (??0UIMap) 108B`，统一序言 `6A FF 68 <handler> 64 A1 00 00 00 00 50 64 89 25 00 00 00 00`（push -1; push handler; mov eax,fs:[0]; push eax; mov fs:[0],esp）+ 真身（含 `C7 06 xx xx 56 00` vtable 写入）。
- 是**完整构造/析构函数**（SEH 包装），非跳板；skip 理由「decompile returns None」是 Hex-Rays 局限，不是「无需定义体」。

### T10 vcall 包装（85 个 decomp 带 `// attributes: thunk`）

- 样本：`Actor::GetDefaultDist2_thunk(0x536A60)` = call SetDefaultDist2(this); return——Hex-Rays FUNC_THUNK 标；
- **NavFaceLayer::GetVertexBuf（0x452560，5B jmp→0x452570）**：decomp `NavFaceLayer_GetVertexBufvoid_00452560.json` 显示 body 调 `UITitle_BBTY::_nearby_452570()`——**伪名**（`_nearby_` 是自动命名占位），0x452570 真身为 `D9 05 B8 B1 56 00 DC C0 …` float 访问器。任务所述「疑似跳到 UITitle_BBTY::_nearby_452570」按地址成立，按语义是命名债。
- 现状：正常导出+codegen（`Actor.cpp:2268/2327` 有体，`Actor.h:206/215` 有 decl+地址注记）✓。

### T11 名实不符（j_ 伪名）

- `j_D3DXVec3TransformCoord @0x4B8200`（66B，**非跳板**）：`51 D9 44 24 08 D8 5C 24 0C DF E0 F6 C4 40 74 06 … E8 … 99 B9 10 27 00 00 F7 F9 42 …` = 浮点相等短路 + rand()%10000+1 插值（random-lerp helper）。名字与 D3DXVec3TransformCoord 无关（命名事故）。
- `j_InputSystem::ProcessKeyboard @0x41CA30`（90B 真 setter：`8B 44 24 08 8B 54 24 04 89 81 C4 01 00 00 …` 存 this+0x1C4 等 4 字段）——被 skip(reason:thunk) 但为真函数。
- `j_InputSystem::ProcessKeyboard_2 @0x41D590`（20B）：存字段 + call 0x41C710(真 ProcessKeyboard) + `C2 04 00`——真 wrapper。
- `j_j_codecvt_base @0x401800`（1B `C3`）。
- `j_*` 全家 20 个拆分：5B 直跳×12 + PSGP B 形×2（0x542533/0x544771）+ 真函数误名×5 + 1B ret×1。

---

## 3. 事故关联

### 3.1 `j_D3DXVec3TransformCoord_0` C2065 根因链（闭合）

1. **跳板本体**：0x542533 = PSGP B 形分发跳板（`FF 25 C4 90 60 00`，槽7=真 D3DXVec3TransformCoord 分发位）；
2. **被筐抑制**：skip_functions.json `0x00542533 {"name":"j_D3DXVec3TransformCoord","reason":"crt_runtime"}` ⇒ `export_full.py:417` 跳过 decomp 导出 ⇒ codegen 既无声明也无定义体；
3. **调用点存在**：`sg_emission_control::_todo_004BA800`（0x4BA800）内 0x4BA97F 等 5 处经 0x542533 调真变换（xrefs_to 0x542533：0x4B9350/0x4BA97F/0x543C84/0x544288/0x544BD2）；
4. **同名分叉放大**：0x4B8200（random-lerp 真函数）被 IDA 命名 `j_D3DXVec3TransformCoord`、**未** skip ⇒ codegen 生成 `free_functions.h:393` 声明 + `free_functions.cpp:20093` 定义体（签名 `void(void*,void*,void*)` 与真身语义不符）；0x542533 在 IDA 被去重为 `j_D3DXVec3TransformCoord_0`；
5. **事故显形**：decomp（`sg_emission_control_todo_004BA800…json`）调用名 `j_D3DXVec3TransformCoord_0` ⇒ 全项目无声明 ⇒ **C2065** ⇒ overlay 注释掉调用（`pal3/src/Misc/sg_emission_control.cpp:381-382`「[overlay-fix 2026-10-27] C2065…待归属定谳」；原始调用保留在 `phase2/base/Misc/sg_emission_control.cpp:377`）；
6. **二次语义损伤**：同函数另一些调用点以 `j_D3DXVec3TransformCoord(0, LODWORD(浮点), …)` 形式落进 0x4B8200 的伪定义体——参数位型（浮点位型当指针）与真语义（变换）都错。

**正解**（裁决 T3=(c)）：跳板不需要定义体（d3dx9.lib 供给），但调用点必须声明 `D3DXVec3TransformCoord`（`#include <d3dx9math.h>`）——把调用名改为 D3DX API 真名即同时消 C2065 与语义损伤；0x4B8200 正名后其伪定义体一并回收。

### 3.2 SingletonThunk 无定义体

- 6 个双注件（0x431D90/0x431DB0/0x431E70/0x431EC0/0x4B6D70/0x4BFD60）：functions.json 声明（`declaration_only: true`，自述「声明收编形=extern 兜底」）→ `free_functions.h:279-284` 有声明；**无任何定义体**；
- 调用面已进源码：`PalScript.cpp:1462-1463`（call + atexit）、`PAL3.cpp:3660/3698`（atexit）⇒ 链接期 **LNK2001** 待爆（S2 编译层全盲区，link_probe 应显形）；
- 其余 39 个无声明无定义，调用面仅 10B 胶水跳板（本身也被 skip）⇒ 现链上不可见，但**完整镜像匹配时其字节（10B/槽位）仍需落位**——当前没有任何机制承担。

---

## 4. 完备性 spec + 落地清单

### 4.1 闭环流程（识别→分类→处置→验证）

```
①识别（全自动）          ②分类（半自动+人工裁决）        ③处置（按族路由）              ④验证（三环）
形态签名扫描            thunk_registry.json 登记        T1/T2/T3/T4/T12 → (c)抑制导出   环A 字节：
FF 25 [IAT]            {addr, family, shape,           T5/T6/T8/T9 → (b)源码再生       跳板地址进 match 地址清单
FF 25 [分发表]          target, provider,               T7 → (b)/(d) 逐个              （截断/重定位三限定适用）
6A 01 E8.. FF 25        decl_policy, verify_policy,     T10 → (a)/(b) 现状             环B 链接：
55 8B EC 6A 01 E8..     evidence}                       T11 → 正名+正常流程            link_probe expected 集合
B9 imm32 E9             （annotation=真相源，            声明来源：(c)=SDK/导入库头      （(c)类不得现 unresolved；
83 E9 imm8 E9           check_annotations 可校验；      (b)(d)=annotation 声明          (b)(d)类 unresolved=回归）
E8 rel32 E9 rel32       不塞 skip_functions——那是        环C 形态：探针编译确认 (b) 类
E9 rel32 +90 填充       「不导出」抑制表，语义正交，      的编译器输出形态签名
SEH 6A FF 68..          筐滥用即混淆两者）
```

- **识别可以完全自动化**：上述字节签名是充分判据（本次普查全部按此定类，误归仅 1/1910（0x53C890）且可由签名纠正）；
  **【2026-10-31 勘误（review_thunk_mechanism_20261028 D4/D5/B5 定谳，禁止维持原表述）】**：
  ①「充分判据」缺**第 9 形 `B9 imm32 FF 25 [IAT]`（`static_obj_ctor_thunk_to_import`）**——实测 12 件
  （0x401BC0/0x401BE0/0x401C00/0x401C20/0x401C40/0x401C60/0x404530/0x404550/0x404670/0x4046A4/0x4CE0D0/0x4CE0F0），
  = 6 个 gbengine 导入类静态对象 ×(ctor+dtor)（gbVFileSystem×3(0x7CC178/0x6EBFA0/0x60BDC8)·gbVolModNode(0xA3A6F8)·
  gbImage2D(0x8ACC10)·CPK(0xDE9CB0)；2026-10-31 PE 字节形 11B 直证 + PE 导入表 IAT 名双证）——
  不匹配 T5（`B9 imm32 E9`）且会被 `FF 25 [IAT]` 规则误归 T1/T2 ⇒ 已入册 `thunk_registry.json`（form 字段 12 条）；
  ②「1/1910」自相矛盾（T11 四件名实不符 + unknown_libname 族 210 条未经字节形分流，均不在分母定义内）⇒
  **误归率定义改窄为「跳板形条目的族间误归」**（选项一，禁维持 1/1910 原句）；
  ③unknown_libname 族 210 条按字节形分流（真身→非跳板、E9/E8E9→既有筐）**挂账后续普查**（须逐条二进制证据）。
  **【2026-10-31 分流收账（tools/thunk_scan.py 全量字节形 census，head_hex 逐条可复验）】**：
  210/210 全部 `real_body`（**零跳板**）——`8a0d…` 守卫旗标检查簇（287–306+ 大簇共享 prologue，
  静态初始化守卫真身）+ 549–552 CRT 微体（call+ret/fstsw）⇒ E9/E8E9 既有筐零收入，
  「跳板形条目的族间误归」分母在本族为空。全量 skip 1717 条族分布（`data/status/
  all_skip_shape_census_20261031.json`）：real_body 1198 · tail_alias 344 · singleton_thunk 46
  （=T5 表 45+1 误归件**精确吻合**）· static_init_glue 38 · import_thunk 30 · psgp_dispatch 22
  （=T3 B 形 22 **精确**）· psgp_lazy_init 17 · this_adjustor 15 · form9 7（12 件中 5 件不在 skip 集）。
- **判定数据结构放 annotation**：新建 `data/annotations/thunk_registry.json`。理由：annotation 是唯一真相源、可被 check_annotations 验证、可经 apply 写入 IDB 命名（IDA 名实漂移一并治理）；
- **验证环覆盖跳板字节**：现行 `match`/L1 只比「有源码函数」，跳板被 skip 后**完全不可见** ⇒ 把跳板地址作为独立地址条目纳入 compare_pal3 对象清单（(c) 类比「链接产物一致性」：两侧同址同形即绿；(b)(d) 类按普通函数字节比对）。

### 4.2 落地改动清单（只列不动手）

1. **新建 `data/annotations/thunk_registry.json`**：收录本报告 T1–T12 全部条目（地址+族+形态签名+target+provider+decl_policy+verify_policy+证据）；
2. **skip_functions.json 拆筐**：`crt_runtime` 中的 T1/T2/T3/T5/T7/T8 条目迁入 thunk_registry（reason 正名：`import_thunk`/`d3dx_psgp_dispatch`/`static_obj_ctor_dtor_thunk`/`layout_stub`/`static_init_glue`），保留真 CRT（0x55xxxx 族）；
3. **修正 T5 文档口径**：skip_reason「mov ecx,[0x…]」→「mov ecx, 0x…（= &obj，B9 立即数）」；
4. **C2065 事故修复**：sg_emission_control 调用点改 `D3DXVec3TransformCoord` 真名 + `#include <d3dx9math.h>`，回收 `pal3/src/Misc/sg_emission_control.cpp:381-382` overlay 注释；`j_D3DXVec3TransformCoord`(0x4B8200) 正名（random-lerp）并修正 `free_functions.h:393`/`free_functions.cpp:20093` 伪签名体；
5. **T5 定义体供给**：6 个 declaration_only 件补 (b) 路径（恢复全局对象源码构造）或 (d) stub；39 个未见件按探针编译确认 MSVC6 输出形态后排期；
6. **跳板入验证环**：compare_pal3/match 对象清单并入跳板地址条目；link_probe `--check` 为 (c) 类建 expected-supplied 集合、为 (b)(d) 类建 must-define 集合（LNK2001 即回归）；
7. **形态自动识别脚本** `tools/thunk_scan.py`：产出 thunk_registry 草稿（全量 1910+ 函数扫描），人工复核后入库；
8. **IDA 名实漂移清理**：`*_adjthunkN`（挂 T1 导入跳板）与 `UITitle_BBTY::_nearby_452570` 一类伪名，经 apply 正名；
9. **T9 SEH 3 个从 skip 恢复**：asm 层重建定义体（SEH 序言可模板化），或标注走 codegen asm→C 路径；
10. **门禁**：thunk_registry 变更走 check_annotations + 批量改动四道门（布局等价/loop-errors 不增/l1 不降/证据自校验）。

---

## 5. 遗留未知

1. **T7 精确生成器三分**（/INCREMENTAL ILT vs COMDAT 折叠 vs 编译器尾跳别名）：逐个 xref+布局复核未完（本报告按布局证据统称「布局跳板」，机制标推测）——直接影响 (b) 与 (d) 的细分裁决与字节可再生性；
2. **d3dx9.lib 版本核对**：机制符号齐备，但是否恰为「D3DX9 Summer 2003」且链接布局与原 exe 一致，需链接字节级验证；
3. **gbengine 导入库在仓形态**：`gbengine/`（CMakeLists+def 1021 导出）可生成导入库，但 T1 31 个跳板的 .text 落位依赖链接顺序，未验证；
4. **39 个未声明 SingletonThunk 的最终字节承担者**：若重建链保持胶水跳板也 skip，则其 10B 字节在完整镜像匹配中无人供给；
5. **0x53C890**（compiler_thunk 筐内的 T5 形态件）及 T5/T7 筐边界模糊实例的逐一归位；
6. **j_InputSystem::ProcessKeyboard(90B) 真语义**（4 字段 setter？与 0x41C710 真 ProcessKeyboard 的关系）与 skip 理由证伪后的处置；
7. **NavFaceLayer::GetVertexBuf 跳转目标 0x452570 的真名**（现 `UITitle_BBTY::_nearby_452570` 伪名，float 访问器语义仅从字节推测）；
8. **A 形 13B 与 C 形 17B 的语义差**（同为「init+分发」为何两种栈帧形态——推测为不同 TU/编译选项产物，未定谳）。

---

*附：本报告全部 IDA 查询经 idapro MCP（session 278944bc）只读进行；未修改 IDB/标注/管线。字节证据均可按地址复验。*

---

## 【勘误 2026-10-28 · DX 对抗复核终裁】（review_dx_static_boundary_20261028.md）

- **槽位语义标签双证伪**（:83/:143 涉及）：「槽[7]=矩阵×向量变换（D3DXVec3TransformCoord）、槽[35]=矩阵乘法（D3DXMatrixMultiply）」**错**。字节+反编译终裁：槽[7]@0x5450B5=`c_D3DXVec3Normalize`(157B, dot+1/sqrt)、槽[35]@0x544777=`c_D3DXQuaternionSlerp`(227B, atan2/sin 球面插值)；真 `D3DXMatrixMultiply` 在**槽#3 @0x543098**（566B）、真 `D3DXVec3TransformCoord` 在**槽#10 @0x545152**（188B）。命名以 d3dx9.lib 符号字节配对为准。
- 其余 T3/T4 定性（PSGP 静态面、(c) 裁决）经复核 CONFIRMED 不变。
