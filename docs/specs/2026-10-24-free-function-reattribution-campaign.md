# 自由函数重归属战役设计（free-function reattribution campaign）

日期：2026-10-24 · 状态：**v2 已实施（批 0 落地，2026-10-24 22:39 四门验证）** ·
关联：`docs/knowledge/gotcha_thiscall_free_function_is_model_error.md` · N1 注记（collect.py:200 / data.py:391）

> **实施结果（批 0）**：判定 14 条过 G1-G7 路由（28 名单 − G2 撞名 8 − G6 值引用 1 − G7 泛型 this 5），
> `FlushCommandQueue→RoleSystem` 等 14 函数单发射、ABI 归正。
> 四门：S2 123/213 持平零翻转 ✓ · L1 棘轮 107=107 ✓ · link_probe ✓ ·
> (code,msg) 净增 +11 已归因 = **C1003 截断去掩盖**（路由体搬出 102 条截断的
> free_functions.cpp，潜在错误在 Actor/CCBStage 显形；C2664 全仓净降 173→169）。
> 实施中新发现的门（已入 reattrib.py）：G6 值引用（ProcCommonTask__ovl 回调传值）、
> G7 this 类型一致（泛型 this 体按泛型渲染，路由后 C2664 浮出）——泛型 this 者留 Phase 2
> 走 IDB 重定型+重导出。

> v1 → v2 修订记录：判定谓词换轴（(name,元数) 唯一 → 裸名→地址→归属唯一）；
> 补 emit_headers.collect_methods 盲区（~30/59 头-体签名冲突）；补 vtable 槽章节；
> A1 基数 69→89（20 条 `_` 前缀命名漂移）；批 0 = 29 条零裸调用（附全名单）；
> 裸站口径 561（A2 面）+ 349 限定（已 ABI 正确）；撤销 sub_4C4B00→_D3DCAPS9 改判；
> 85 条构成改写（19 拐杖 + 27 sub_* + 20 `_todo_` 漂移 + 19 CRT）；advisory 拆 185+11 两集合。

## 1. 定性：一个根因、三类缺陷、指标全盲

**根因**：decomp 语料的**名字形态**（有无 `::`）与二进制真相（`__thiscall` ⇒ 类方法）脱节。
collect/data 的归属路由全跟名字形态走（N1 回退决策），注解侧的**地址归属**（A 级）无人消费。

实测基线（fresh-IDB 语料，S2 123/213 基线日，双复核修正后）：

| 缺陷类 | 数量 | 机理 |
|---|---|---|
| A1 错误归属 | **89 条地址**（88 自由体 + 1 ProcessKeyboard 已成员形态）| 地址已归属某类 methods，仍以 `__cdecl` 自由函数发射。20 条被名字级交集漏掉：decomp 名 `_todo_*`/`_UIFrameWnd`/`_UIWnd`/`_scalar_dtor_0_0` 与 cpp 定义名存在 `_` 前缀漂移 ⇒ **路由必须按地址、不得按名** |
| A2 ABI 错裸调用站 | **40/69 名字、561 站**（裸形态精确计数） | 裸调用 `Name(v12, x)` 决议到自由声明 ⇒ this 不走 ECX ⇒ 字节永不匹配。另有 349 站 `Cls::Name(` 限定调用（ABI 已正确，不需转写） |
| B 归属缺口 | 23 类型丢失 + advisory 185（`Cls_` 前缀）+ 11（撞名，7 已跑/4 asm 无函数跳过） | 需逐条取证（§4 队列） |
| C 声明面债 | 85 = 19 拐杖 + 27 sub_*（等 Phase 2）+ 20 `_todo_` 头/体漂移 + 19 CRT/杂项（永不收敛） | ⚠️ 地雷：`sub_421830` h:471 声明 + free_functions.cpp:2421 实调 + 全树无定义 = 潜在链接错误 |

**为什么错误指标全盲**：`__cdecl` 自由函数是合法 C++ ⇒ S2/错误 census 零信号；
只有字节比对能暴露 ⇒ 这批函数及其调用站是 L1 的结构性天花板。

**历史教训**：2026-09-29 N1 单侧拆声明拐杖 ⇒ C2065 洪泛（S2 100→91、100→67）。
发射、声明、调用形三者必须成对闭合。

## 2. 现有机制盘点（不重建，只接缺口）

| 件 | 位置 | 状态 |
|---|---|---|
| 调用形转写器 | `ast_transform.py:1442 rewrite_unqualified_member_call`（stage2:126 挂钩） | ✅ 在役；现有门 = recv∈(this,_this) + (name,元数) 唯一 + cast 形正则 |
| 裸名方法签名喂入 | `data.py:479`（T27，method_sigs['Cls::Name']） | ✅ 在役 |
| 归属证据引擎 | `tools/attribution_offset_match.py` | ✅ 在役 |
| free_func_sigs | `data.py:380-523` | ⚠️ 刻意含成员地址（N1 拐杖）；⚠️ functions.json 的 thiscall 条目本就进不了（data.py:538 只收 cdecl/stdcall） |
| **缺口 1** | 非 this 接收者裸/cast 调用转写 | ❌ 本战役 Phase 1 |
| **缺口 2** | emit_headers.collect_methods 裸名收编（:1041-1058 裸名 continue；ida_structs 补充 sig 与 decomp 冲突 ~30/59） | ❌ 本战役 Phase 1 |

## 3. Phase 1：发射-调用-声明成对闭合（TDD，REATTRIB 门控）

**判定谓词（v2 换轴，复核裁决 1）**：
`裸名 → decomp 名索引唯一地址 → 地址归属唯一 (Cls, Method)`。
不用 (name,元数)-in-method_sigs 作主门（SetEnable/Update 被 50+ 类同名同元数命中 ⇒ 恒不转 ⇒ 1c 落地即 N1 复发）。
辅助门：①同名同 sig 成员撞名扫描（GDB_GetRoleNum/GDB_GetItemNum 实证第二同址 ⇒ C2084）——**撞名一律不路由、保留自由形态、记裁**；
②自由名 == 归属方法名（禁止改名路由）；③1c 拆声明仅限本谓词命中集。

**三件套**：
- **1a 调用形转写**（ast_transform）：**新增裸形态正则分支** `Name(recv, args)`（recv 文法 = 非限定标识符/this/_this，排除 `->`/`.`/`::`/`&` 前缀与定义/声明行）+
  **cast 形非 this 接收者分流**（`Name((T *)recv, ...)` 现被 recv 门拒——主导形态，free_functions.cpp:5746+ 一片）。
  转写 `→ (((Cls *)recv))->Cls::Name(args)`。门 = 谓词命中集（自由声明已移除的同批集合）。
- **1b 发射路由**（collect.py）：按**地址**查归属索引（annotation_view 单一读点）→ 命中且过门 ⇒ 该函数进 by_class（cls/method 用注解名）；
  stage1 已能重建 `Cls::Method` 定义并剥 this 形参（复核实证 stage1_structural.py:209-284），**无需 `_this→this` 改名**（decomp 体本就写 this）。
- **1c 声明收敛**（data.py + emit_cpp）：free_func_sigs 排除路由集。**已知不可拆项**（裸调用者存在且名字不在谓词命名空间，1a 救不了）：
  `Destroy__ovl_03`(18 站)、`NullCallback`(37 站)、`~UIFrameWnd`(1 站) —— 保留自由声明，记 Phase 3。
- **头声明收编**（emit_headers.collect_methods）：裸名候选按地址归属收进类声明（用 decomp sig），ida_structs 补充经既有 seen_addrs 让位 ⇒ 消除 ~30/59 头-体签名冲突。
- **vtable 槽（8/59，7 条在批 0）**：stage3 `struct_vtables`/`_resolve_vtbl_method` 按注解类自己的 methods 建槽，路由不改其输入 ⇒ 槽声明保持通用 `slot_N` 形，路由体并存无害。
  `ReleaseAllTextures`（归属 UI3DModelNode vs 自由声明接收者 UI3DModelNode 矛盾）单独裁决后才可路由。
- **自由函数体内的裸调用**：generate_free_funcs_cpp 路径同套转写（若现状未跑 transform 则补挂）。

**分批（验证 checkpoints，机制统一数据驱动）**：
- 批 0 = 29 条零裸调用（精确名单见复核裁决；其中 16 条有 1-24 个限定调用站、不依赖自由声明）+ 撞名扫描通过
- 批 1 = 裸站 ≤10 族；批 2 = 大站族（SetEnable 386 / IsVisible 31 / FindFreeThread 22 / Create__ovl_1 21 / ctor_17 20；Update/GDB_GetRoleNum 裸站仅 1/3）
- 批 3（移出本战役）：`MoveToAbsolute` 0x445D20 **无归属**（functions.json declaration_only），与 CCBStage.h:296 同名成员撞车 + 20 处 `::` 限定调用——属 Phase 2 待裁项，非 Phase 1 可执行项
- 全部批次全树 `&Name` 取址 = 0（复核实证，无函数指针拆桩风险）

**验收门**：TDD 单测（谓词/正则/路由/声明四点）+ 全链 probe：S2 不降、L1 不降、link_probe 不恶化、(code,msg) 多重集新增须归因。

## 4. Phase 2：归属裁决队列（v2 修正）

引擎批量跑毕（`data/status/reattribution_queue_20261024.json`）：

| 判定 | 数量 | 处置 |
|---|---|---|
| UNAMBIGUOUS | 2 可提交 | `InitSceneScriptLoader→CG_Entry`(4/4，手工核实 ✓)、`sub_4BAE60→sg_emitter`(18/18，手工逐指令核实 ✓ 无 this 重装) |
| 维持薄证据 | 1 | `sub_421830→Scene`(2/2，且存在声明+调用+无定义链接地雷，优先处置) |
| **撤销改判** | 1 | `sub_4C4B00`：asm 实为带状态更新器（fadd 累加/钳制/数组索引，无任何 D3D 调用）；`_D3DCAPS9` 注解 [0x10,0xB8] 零空洞无判别力且布局自 0x54 起错位 12 字节（304≠296）——**先修注解再裁** |
| AMBIGUOUS:2 | 1 | `sub_5306A0`（Actor/BINK 二选一）手工读即裁 |
| AMBIGUOUS:12–415 | 11 | 偏移脚印太小 ⇒ IDA 逐访问溯源/手工读 |
| NO-EVIDENCE | 7 | 仅 3/7 零偏移（asm 覆盖问题）；GetCellStateByte/sub_44F130/sub_47F590/sub_4912D0 = 有偏移但无单类覆盖（外来访问击穿 strict/空洞/混合对象）⇒ 手工读 |

advisory 两集合：`Cls_` 前缀 185 条（0 已跑）+ 撞名 11 条（7 已跑；SetPitch/GetGlobalUserVar/NextRole/SetRadiusWidth 因 decomp 地址非 asm 函数起点被跳过，记录在案）。

## 5. 非目标

不动 gbengine/topo；不重命名已有 A 级归属；`_misattrib_`/skip_classes/scalar_dtor 既有分支顺序保持
（scalar_dtor → _misattrib_ → ovl，实现若重排守卫须在测试中钉死）；CRT/编译器初始化族（SingletonThunk_* 等 19 条）永不收敛，不强行归属。

## 6. 退出判据

- 89 条地址级归属全部单发射；561 裸调用站 ABI 正确（partial diff 抽样验证）；
- 队列 23 条全部落裁；L1 总体（matched 695/915）随 ABI 修复自然扩容。
