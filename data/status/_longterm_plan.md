# PAL3Decomp 长线计划（2026-09-19 制定）

> 本文件是**唯一的前进路线**，优先于零散待办。制定依据全部来自本会话的实测
> （`_session_handoff_20260919.md`、`_baseline_repro_20260919.md`、`_size_evidence_20260919.md`、
> `_attribution_evidence_20260919.md`、`_codegen_invariants_review.md`）。
> **每完成一项就在本文件勾掉并更新数字。**

## 0. 先立规矩（违反其中任一条的结论一律作废）

1. **同一 IDB 谱系内比较**。跨谱系（`init --force` ↔ 长寿命 IDB）出现 ±1 文件 / ±3 符号是常态，
   不是信号。总错误数**不作判据**（同状态重跑可差 ±18）。
2. **门禁顺序**：`codegen` → **`tools/codegen_invariants.py`（秒级）** → `probe` → `match`。
   不变量检查放在最前，别再花 15 分钟才发现生成物内部就矛盾。
3. **硬线**：`new_failures = 0`、**L1 不得回退**。不满足就回退该批，不留"反正更好"的改动。
4. **不许留未验证改动**（本会话已有 4 批因此回退）。
5. **归属/尺寸只落"有二进制证据"的条目**；"证明了它是错的" ≠ "证明了改成对的是安全的"。

## 1. 现状（2026-09-19 实测）

| 量 | 值 |
|---|---|
| `check` 门禁 | 0 errors / 13 warnings PASS |
| 本地 S2 | **70/201** · matched 222/256 · **L1 21** |
| 对发布基线 | 新失败 **3** / 已修复 **4** |
| 不变量图（秒级可复现） | **D 80 类**（有 vtables 但头里 +0x0 无 vptr）· **A 150 行/29 文件**（code 位置用 `__vftable`）· **B 72 候选**（`sub_` 形参/实参不一致，精度下界 21%）· **C 29 潜伏** |
| 编译普查里 C2660+C2664 | **644 处 / 641 个 file:line** ← **最大的单一系统性缺陷类** |
| 已落盘标注修正 | 10 条（尺寸 2 / 归属 6 / 签名 2） |

## 2. 阶段（每阶段入口/出口判据明确，按序推进）

### P0｜让测量可信（**当前最高优先**）
* **问题**：读数依赖 IDB 构建**历史**；已证伪四种解释（apply 趟数 3/5、apply+fix_vtable 成对跑、
  `[6b3]` 收敛判据、export 改 IDB）。剩唯一解释="注解版本序列残留"。
* **动作**：① 从干净 IDB 按"改动前注解 → 改动后注解"分两步 apply，验证该解释；
  ② 若成立，做**确定性构建**（`apply --reset`：先清除注解创建的条目再重建；或把 IDB 内容哈希
  纳入基线，规定"同哈希内才可比"）。
* **出口**：**同注解两次独立构建的 S2/matched 完全一致**（当前不一致，故现在任何"干净重建复算历史读数"都无效）。
* **不阻塞**：P1/P2 都在**单条 IDB 内**做 A/B，不必等 P0，但结论要标注谱系。

### P1｜治根：vptr 发射（**收益最大、改动最小**）
* **问题**：`emit_headers` 只发射 `data_members`，把 +0x0 的 vptr 发射成 `char _gap_000[N]`；
  于是 **80 个类**的头都没有 vptr，而 .cpp 里有 **150 行**在用 `__vftable` ⇒ 全是 C2039/C2227。
* **落地位置（本轮已勘察）**：`pipeline/gen/stages/emit_headers.py` 第 **1798-1799** 行——
  代码里明确写着
  ```python
  # Skip vfptr at +0 for classes with vtables (compiler-generated)
  if mname == 'vfptr' and off == 0 and class_vtable_slots(cls_name):   # → 跳过 ⇒ 变成 _gap_000[4]
  ```
  即"**有意跳过** +0 的 vptr"。P1 就是把这条从"跳过"改成"**发射一个 vptr 成员**"（名字要与
  `stage3_cleanup` 期望的 `__vftable` 对齐），使头与 .cpp 两侧一致；另一条路线是反过来让
  `stage3_cleanup` 统一改写成 `(*(void***)obj)[slot]` 形态（见 `_baseline_repro` §14）。
  ⚠️ 注意还有个分支（第 2015 行 `'__vftable' in sig`）与 `class_vtable_slots`（第 243 行）；
  先用 **3 个类**（`AStarPathFinder`/`CCBPanelSlot`/`CEffModel`，都是 `_gap_000` 且类小）做实验，
  确认"名为 `__vftable` 的注解成员"走的是哪条分支，再决定改哪一处。
* **本轮进一步勘察（把根因又推上游一层）**：emitter 的成员来源**不是**注解 JSON 的 `known_members`，
  而是 **export 出来的 `data_members`**（`emit_headers.py:1643-1652`：`ann_struct_fb.get('data_members', [])`；
  第 928-944 行的 `known_members` 只用于**改名 overlay**）。而实测 `ida_structs.json` 里 `UIWnd` 的
  `data_members` **从 offset 4 开始** ⇒ **IDB 结构本身就没有 +0 成员**，所以头里只能填 `_gap_000[4]`。
  ⇒ 真正的修法有三处可选，按成本/风险排序：
  1. **`emit_headers.py`（最小、最局部）**：在第 1798 行那个 skip 处**不要跳过**，改为发射
     `void * __vftable; // +0x0` —— 头与 `stage3_cleanup` 期望的名字一致，且是**加性**改动（填掉现有 gap，尺寸不变）；
  2. `export_full.py`：把 IDB 结构里该类的 +0 vptr 也写进 `data_members`；
  3. `apply_annotations.py`：让 +0 `__vftable` 真正进入 IDB 结构（最上游，但会改变 IDB 内容，
     可能扰动本会话仍未闭合的"IDB 谱系"问题 ⇒ **最后再考虑**）。
  **实验顺序**：先做 (1)，用 3 个小类验证 D/A 是否归零、L1 是否守住；不成立再试 (2)。
* **出口**：`codegen_invariants.py` 的 **D=0 且 A=0**；对发布基线 `new_failures ≤ 1`（目标 0）；**L1 ≥ 21**。
* **预期**：至少消掉 `UIProgressBar.cpp`、`UIStatic.cpp` 两个新失败；`CCBUI.cpp` 等一批文件的
  错误数大降（它现在是 102 条截断，其中 21 条是 `'__vftable' is not a member of 'CCBUI'`）。

### P2｜治面：签名/调用点一致性（644 处）
* **问题**：C2660/C2664 共 **644 处**，绝大多数是**已注解成员函数**（`sprintf`/`Init`/`Create`/
  `SetParam`/`ShowWindow`/`UpdateAnim`…）的形参与调用实参不一致 ⇒ 注解签名或调用点渲染有系统性偏差。
* **动作**：把 `codegen_invariants.py` 的 B 思路**从 `sub_` 扩到成员函数**
  （`Class::Method(...)` 的声明 vs 全部调用点），并**先算精度**（对 census 的 C2660/C2664 逐条对账），
  再按"同一根因聚簇"批量修（而非逐条修症状）。
* **出口**：该类错误下降 **≥50%**；`new_failures` 不增；**L1 不回退**。

### P3｜主攻字节匹配存量（**真正的产出目标**）
* **问题**：L1 只占 **21/(21+176) ≈ 11%**；继续抠 L1 已进入"改 1 个函数、掉 1 个 L1"的平台期
  （本会话 3 批因此回退）。存量在 **176 个 partial**。
* **动作**：建"逐函数字节 diff → 差异分类（寄存器分配/常量/调用序/结构体布局…）→ 按类修复"的工具链；
  指标从"L1 ±1"改为"**partial 收敛多少个函数**"。
* **出口**：L1 从 **21 → ≥30**，且中途每一批都在同谱系内可复现。

### P4｜回到 §49.4 归属/尺寸（**低优先，且只在证据齐时落盘**）
* 已定案 10 条（见 `_session_handoff` §1）；剩余项都诊断到"需 dataflow / 宿主成员表有缺口 / 很可能
  不是成员函数"，属另一个量级的工作。
* **动作**：只做"证据已齐"的落盘（队列式累积），不再为它开新的深挖；把省下的额度给 P1–P3。

## 3. 每阶段的验证协议（固定命令序列）

```powershell
python tools/codegen_invariants.py            # 秒级：D/A/B（阻塞项）
python pipeline/cli.py apply
python pipeline/cli.py export
python pipeline/cli.py codegen all
python tools/codegen_invariants.py            # codegen 后再跑一次（生成物已更新）
python pipeline/probe_compile.py all          # 只出 census，不刷新共享基线
python tools/regression_detector.py --check --format text   # 只读对账
python pipeline/cli.py match                  # 注意：会推进共享棘轮，之后 git checkout 还原
```
判定：**`new_failures = 0` 且 L1 不回退**；否则回退该批。共享基线 `s4_baseline.json` /
`pal3_registry.jsonl` / `baselines/latest.json` **一律不推进**（本机 IDA 9.2 读数与发布值不同源）。

## 4. 明确不做（负结果清单，别再试）

* 加 apply 趟数（3/5 趟）或 apply+fix_vtable 成对跑 —— 复现不出长寿命读数；
* 用 `[6b3] Global names (re)applied` 当收敛判据 —— 217 处持平；
* 靠"export 改 IDB"解释差异 —— 单跑 export：type 数 1031→1031、IDB 字节数完全相同；
* 判据："同一地址被两个 JSON 声明"（当前树 = 0）；"无 owner 的 `__thiscall(`"（2184 条纯噪声）；
* 把 `OnMessage` 加进 `UIWnd` 方法表（`0x00445D10` 已属 `CGameData`，会重复拥有同一地址）；
* 用"成员区间覆盖偏移"筛宿主类（会命中上百个类）。

## 5. 风险与止损

| 风险 | 止损 |
|---|---|
| P1 改 `emit_headers` 波及 80 个类的头 | 先做"只对 3–5 个类"的小实验（改前后对比 + L1），通过再全量 |
| P2 误判（签名本就该不同） | 先算精度对账 census，精度 <70% 就先收紧判据，不动注解 |
| P3 平台期反复 | 指标改 partial 收敛数；单批 >3 个函数才提交 |
| 任何阶段 L1 掉 | 立即回退该批（本会话已 3 次如此） |

## 6. 立即的下一步（本计划的第一个动作）

**P0 的验法**：从干净 IDB 按"改动前注解 → 改动后注解"分两步 apply，看是否复现 71/201；
**同时**启动 **P1 的小实验**（选 3 个 `_gap_000` 类，让 `emit_headers` 发射 vptr，跑 invariants+probe+match，
看 D/A 是否归零、L1 是否守住）。两者互不依赖，可并行。

---

## 6.5 独立复核轮（2026-09-19）—— 第一手实测事实

派了 4 个子 agent 独立复核（方案 P1(b)、`hexrays_limit` 分类、partial 归因、vtable 布局假设）。
在等待其结论的同时，本会话自己先取到的**可复现事实**如下（每条都可用给出的命令重放）：

### F1 三个新失败的**确切**错误与"已修复"数目修正
* 新失败 3：`UIProgressBar.cpp`（4× `C2227 left of '->OnMessage' must point to class/struct/union`）、
  `UIStatic.cpp`（4× 同）、`ScreenEffect.cpp`（1× `C2664 'sub_4B59B0' : char* → float*`）。
* 已修复是 **5** 个而非 4：`CCBProtectWindow.cpp`、`Combat.cpp`、**`CG_Entry.cpp`**、`UICaption.cpp`、`UIMap.cpp`。
* **这 8 处 `C2227` 被 `tools/error_classifier.py` 判为 `hexrays_limit`（= 项目规定"不修"的桶）**，
  而按构造它们 100% 是 codegen 发射出的非法文本 ⇒ 分类器把"可修的回归"藏进了"不修"桶。

### F2 那 8 处的**确切**放弃点与"最小修法"（比我原方案更小）
* 发射点：`pipeline/gen/stages/stage3_cleanup.py:597-640` 的 `visit()`。
  裸链 `RECV->__vftable->NAME(...)` 走了 `_decode_vtbl_call` 的 `mn` 分支（`ret/params/cls_hint` 全 None）
  ⇒ `_resolve_vtbl_method`（第 508-518 行）第 ③ 分支返回 `None` ⇒ 第 634-636 行 `repl = None`
  ⇒ 原文本保留 ⇒ C2227。
* **接收者的静态类型就在同一个函数里**：`pal3/src/Misc/UIStatic.cpp:370-376` 声明了
  `UIWnd *v6/v9/m_pfather/v11/v12;`。
* **类的 vtable 槽已经标注好**：`data/annotations/structs/UIWnd.json` 的
  `known_methods["6"] = {name: OnMessage, address: 0x00445D10}`，且生成的
  `pal3/src/UI/UIWnd.h:35` 已经有 `int OnMessage(int nMsg, int wParam, int lParam); // 0x00445D10`。
* ⇒ **只要把 `cls_hint` 补成接收者类型，既有分支 ①（第 513 行）就会返回 `OnMessage`，
  发射 `m_pfather->OnMessage(...)` 即可编译。不需要改任何 annotation，也不需要 `((Owner*)...)` 强制转换**
  （后者是 `_baseline_repro` §14 的方案：Owner=CGameData 会让调用改走 CGameData 的 vtable 槽位，
  与字节匹配无关且更危险；接收者自己的类已经能解析）。

### F3 vtable 一致性：**71/75 个带 vtable 注解的类，生成的 `virtual` 数与二进制槽数不符**
* 统计：`data/annotations/structs/*.json` 里有 `vtables` 的 80 个类，75 个有生成头文件，
  **71 个** 满足 `len(slots) != header 里 ^virtual 计数`（多数是**短缺**，个别多余：`PalScript` 6 槽 vs 9 virtual）。
* 只用"槽的 `from` 全是自身/null"的 13 个类（无外来实现）重算，**10/13 仍不符**：
  `RenderTarget2` 99→40、`CEffAction` 15→7、`CEffectSystem` 9→5、`ScriptObj` 5→1、`PalScriptMgr` 6→3 …
* 具体到本次新失败涉及的 `UIWnd`：注解 vtable 有 **7 槽**（槽 0=0x00445E70 … 槽 6=0x00445D10），
  生成头只发 5 个 `virtual` + 1 个**非 virtual** 的 `OnMessage`；头内注释自称 "vtable (6 methods, order matches binary layout)"。
* **影响面**：`data/status/s4_baseline.json` 的 200 个 matched 行里，**60 行（30%）属于 vtable 不符的类**
  （`UIStatic` 14、`UI3DCtrl` 11、`AStarPathFinder` 7 …）。而**当前没有任何检查覆盖这件事**
  （`codegen_invariants.py` 的 D 只查"+0x0 是不是 vptr"）。
* **未决**：这是"条目短缺"还是"整体错位（自动插入的 `virtual ~X(){}` 挪了槽 0）"，
  已另派子 agent 用 PE 原始字节（`original/PAL3.exe` 的 vtable VA→文件偏移）独立判定。

### F5 子 agent 复核之一：`hexrays_limit` 43.5% 是**误分类**（已收到，含我自己的反证）
子 agent（独立、只读）读 `tools/error_classifier.py` + `probe_census.json` + `error_classification.json` + decomp JSON 后结论：
* **规则表是"错误码 + 消息正则"的顺序匹配，先命中先赢**（L27–139/L142–148）。
  `C2660 "function does not take.*parameters" → hexrays_limit`（L59）排在所有类型错误兜底（L87）**之前**
  ⇒ **每一条"参数个数不对"都被无条件归入"不修"**；C2065/C2227/C2228/C2059 同理。
* 文件桶 = 错误的**简单多数票**（L219–222），**单条错误无阈值**；唯一的后门 `_cascade_reclassify`（L160–200）
  实测只改写了 6 条错误/3 个文件 ⇒ 等于失效。
* 57 个 hexrays 桶文件共 1025 条错误；按机制逐条溯源后认为 **54/57 可重分类**（真·上限只剩 3–4 个：
  `std::operator+` × `gbVec3D` 那 4 个）。修正后估计 annotation_fix ≈18–22、codegen_fix ≈32–36。
* 它给的三个最大机制：①"把首个实参当 `this` 吃掉"（21 units）；②vtable 发射错误（双指针/`__sdtor` 当成员/`static virtual` 桩，~18 units）；
  ③跨二进制原型未同步（`gbVFileSystem::Read` 3 参 vs DLL 4 参，7 units）。
* **它对分类器自身的抽样检查**：桶标签层面 0/15 硬错，但规则层面 5/15 含"明显是 codegen 却被标 hexrays_limit"的错误。
* 它标注未验证：`_sdtor_call_dtor` 槽名可否解析、9 处 `ShowWindow` 遮蔽、未真正跑编译器。

**我的第一手核验（对它的机制①既证实又纠正）**：
* 证实：`pal3/src/Effect/C3DSpark.cpp:380` 确实是
  `(((gbDynVertBuf *)(v16 + 7216)))->gbDynVertBuf::RenderGeomQuad(v18, …, …);`（3 实参），
  而 decomp（`asm/pal3/decomp/C3DSpark_RendergbVec3D_004d6bc0.json`）是
  `gbDynVertBuf::RenderGeomQuad((gbGeomQuad*)(v16+7216), v18, eff, tex);`（4 实参）。
* **纠正**：它建议的"把 `_ret_param_slots == len(args)-1` 这个闸门推广到 cast_expression 分支"，
  **正是本项目已经测量过并明确否决的改法**：`pipeline/gen/ast_transform.py:770-776` 写着
  "the ret-N gate alone rewrites **298 sites / 189 files** on this corpus … NEITHER condition alone is admissible"。
  所以照它的建议做会得到一次 298 站点的爆炸半径，而不是 21 个 unit 的精确命中。
* **更锐利的判别式（我的结论）**：真正的分界不是"闸门通过与否"，而是
  **声明形参数是否等于实参数**（`gbengine_api.h:479` 的 `__thiscall gbDynVertBuf::RenderGeomQuad(struct gbGeomQuad *,int,…,…)`
  是**4 个形参且第 1 个就是对象**，即 IDA 风格的"显式 this 原型"）。当 `declared == len(args)` 时把首参当 `this` 吃掉就是错的；
  当 `declared == len(args)-1` 时才是对的。21 个 unit 全部落在前一种。
  ⇒ 修法应对准"**手写 API 头的显式-this 原型 vs C++ 成员语义**"这一条，先用同一套工具测出它的爆炸半径再动手。

### F6 我自己的不变量 B 打偏了（顺带发现）
* `tools/codegen_invariants.py --check B` 报 55 处"声明形参 vs 调用实参"不符，但**全部是 `sub_XXXX` 自由函数**
  （`sub_407790 声明 1 参 vs 调用 0 实参` 之类）。这些之所以不算错，是因为声明形如 `void sub_407790();`
  ——**空参数表在 C 里表示"参数未指定"**，所以能编译。这解释了此前独立复核给出的"B 精度下限只有 21%"。
* 而**真正的 21-unit 缺陷簇（`X->Cls::M(...)` 的实参数 ≠ 声明数）B 根本没检测到**。
  ⇒ B 应当：(i) 跳过空参数表 `()` 的声明；(ii) 增加"成员限定调用 `X->Cls::M(args)` 的实参数 vs `Cls::M` 声明数"这一项。
  验收用例已经现成：`gbengine_api.h:479` 声明 4 参 ↔ `C3DSpark.cpp:380` 传 3 参。

### F7 最大可修簇的**确切形状**（我自己量出来的，与复核者的描述不同）
* 复核者说机制①是"codegen 把首个实参当 `this` 吃掉"（21 units）。实测**同一现象有两种相反的成因**：
  * **形态甲（大头）**：`Cls::M(obj, rest…)` 这种**限定式静态调用**根本没被改写成实例调用。
    实例：`pal3/src/Combat/CCBMagicWindow.cpp:168` 生成 `UIScene::GetChildCount(*v8);`，
    而 `pal3/src/UI/UIScene.h:87` 声明的是 **0 参成员** `int GetChildCount();`
    （IDA 侧的 signature 是 `int __thiscall(UIScene *this)` —— **对象是显式首参**，头文件生成器把它去掉了）
    ⇒ 正确写法是 `(*v8)->GetChildCount();`。判别式：`成员声明形参数 == 实参数 - 1` ⇒ 首参就是对象。
    **这正是项目里已有的 ret-N 闸门**（`ast_transform.py:749-750/782`）。
  * **形态乙（小头）**：`Cls::M(all-real-args)`（声明形参数 == 实参数，`this` 在 ECX 里、
    由前一条调用产生）被 codegen 硬造了一个接收者并吃掉首参 ⇒ 例 `C3DSpark.cpp:380`（3 参 vs 声明 4 参）。
    我全仓扫描：`declared == args+1` 只有 **4 key / 7 站点**（`Logger::Write` 4、`CCBItemWindow::Create`、
    `CCBRoleState::Create`、`CCBSystem::SetTimeScale`）——**形态乙是小头**。
* ⇒ 复核者的"21 units"应主要落在**形态甲**；但**形态甲的修法就是被项目已测量并否决的那一次**：
  `ast_transform.py:770-776` 明写 "the ret-N gate alone rewrites **298 sites / 189 files** … NEITHER condition alone is admissible"。
  **所以下一步不是照抄复核建议，而是先回答一个问题**：那 298 站点里有多少是"限定式调用本该改成实例调用"的真缺陷，
  有多少是当时判定为"不可信"的？这需要一次可复现的 blast-radius 测量（同一 IDB 谱系），而不是直接动手。

### F8 vtable 残留与限定式调用的**独立量化**（我自己扫生成源码得到）
* **`__vftable->` / `__vftable[` 的"活代码"残留：135 行，分布在 21 个 .cpp**
  （`CCBUI` 69、`CEffectSystem` 7、`RoleSystem` 6、`SaleUI`/`LineupUI` 5、`UIStatic`/`UIProgressBar`/`UIScene`/`CScreenMode`/`PalScript`/`CCBMagicWindow` 4 …）。
  另有 119 行出现在注释里（`// [VFTABLE-STUB] original: …`）。⇒ 这与复核者给的"vtable 簇 ~18 units"**独立吻合**。
* **`static virtual`（非法组合）确认存在**：`pal3/src/Combat/CCBUI.cpp:554/584`（声明+定义各一处）。
* **限定式调用 `Cls::M(args)`（无 `->` 接收者）的两种形态**（我按"成员声明形参数 vs 实参数"分类，注释行已排除）：
  * `declared == args - 1`（首参就是对象 ⇒ 本应写成 `a->M(rest)`）：**160 站点 / 32 文件**；
  * `declared == args`（实参全是真参、`this` 在 ECX 里）：353 站点 / 45 文件；无匹配 2 站点。
  * **注意**：我的正则在"静态成员/自由函数"上无法判别，所以 353 这个数**偏大、不可直接引用**；
    而项目注释里的"ret-N gate alone rewrites **298 sites / 189 files**"与我的 160/32 **口径不同、未能复现**。
    ⇒ 结论不是"照 298 或 160 动手"，而是"**先用真正的检测器把爆炸半径量出来**"（见下）。
* 两个残留簇的**共同上游**是同一个发射分支（`stage3_cleanup.py:597-640` 的 `visit()`），
  所以"修 vtable 发射"这件事同时覆盖：本次 2 个自伤回归 + 21 文件/135 站点 + 复核者的 18 units 估计。

**第 51 轮甄别**：候选① `OpenBaseFile::OpenBaseFile` **不属于 F23 族**。decomp 索引里查不到该名字（VA 取不到），
而生成物是 `{ this->m_plastsys = g_pVFileSys; g_pVFileSys = (gbVFileSystem *)&g_BaseVFileSystem; }`
—— 两条全局赋值，**没有调用**；而二进制首条是 `mov ecx,[0x56a598…]` ⇒ 原函数开头有一个"**对全局对象调构造/方法**"的调用，
被 decomp 丢掉了 ⇒ 与 `ObjectCamera::ObjectCamera` 的"空函数体"同族（**丢调用**），不是"丢 ECX"。
⇒ 下一批应改做候选② `TextureLib::ClearGlobalVars`（`mov ecx,0x1894b78` 是真·全局对象 this），
并把"丢调用"单独列为一个机制（与 F19 尝试过的 dtor-call 保留同族，但需按目标签名发射）。
**本轮无生成物改动**；门禁维持：`new_failures` 0 · S2 73/201 · **L1 32/219** · partial 187。

**第 52 轮真值（候选② `TextureLib::ClearGlobalVars`）**：生成物是
```cpp
int * TextureLib::ClearGlobalVars() {
  _DWORD *v1; // esi                                   // ← **未初始化的局部量**
  (((CScreenMode *)&stru_1894B78))->CScreenMode::_nearby_53f4c0(v1);   // ← 拿它当实参
  ...
}
```
而二进制首分歧是 `mov ecx, 0x1894b78`（原）vs `push ecx`（我们）⇒ **我们多推了一个实参**。
即 `_nearby_53f4c0` 的注解签名**多了一个形参**（那个"形参"其实是隐式的 `this`=ECX），
与 F7 记录的"IDA 那类把 `this` 当显式首参的原型"同族。
⇒ 修法：把 `_nearby_53f4c0` 的注解签名改成**0 个栈参**（`this` 走 ECX），
decomp 会渲染 `((CScreenMode*)&stru_1894B78)->_nearby_53f4c0()` ⇒ 编译成 `mov ecx,global; call`，
与二进制一致。**落地前须先确认 callee 的 `ret N`**（`ret`/`ret 0` ⇒ 0 栈参；`ret 4` 则说明我们的实参是对的，
真因在别处）。本节与 F24 的 5 候选清单合并为下一批的输入。
**本轮无生成物改动**；门禁维持：`new_failures` 0 · S2 73/201 · **L1 32/219** · partial 187。

**第 53 轮确认（候选② 成立，grade A）**：callee `CScreenMode::_nearby_53f4c0`（**0x53F4C0**，9 字节）本体：
```
0053F4C0  8B C1              mov eax, ecx                    ; eax = this（ECX 传入）
0053F4C2  C7 00 58 0A 57 00  mov dword ptr [eax], 0x570A58   ; *this = 0x570A58
0053F4C8  C3                 ret                             ; ← **ret 无立即数 = 0 个栈参**
```
而其注解签名（`data/annotations/functions.json` 里名为 `CScreenMode::_nearby_53f4c0` 的条目）是
`_DWORD *__thiscall(CScreenMode *this, _DWORD *a2)` —— **多了一个幻影形参 `a2`**。
⇒ 调用点因此多推一个实参（我们的 `push ecx`），而二进制只有 `mov ecx,<global>; call`。
**修法（一行）**：把该条目签名里的 `, _DWORD *a2` 删掉 ⇒ 调用点渲染成
`((CScreenMode*)&stru_1894B78)->CScreenMode::_nearby_53f4c0()`，编译即 `mov ecx,global; call`，与二进制一致。
**下批落地**（`functions.json` 一行 + apply → export → codegen → probe → match；门禁 `new_failures` 0、L1 > 32）。
**本轮无生成物改动**；门禁维持：`new_failures` 0 · S2 73/201 · **L1 32/219** · partial 187。

### F49-bis ★ 第 103 轮：**纠正 F49** —— 不是读数问题，是"透过全局指针写"与"写全局"的语义差异
**决定性对照**（编译 `pal3/src/Misc/OpenNULLFile.cpp` + 反汇编原函数）：
```
原函数 0x401F90（11 字节）：
  8B 01              mov eax, [ecx]            ; eax = this->m_plastsys
  8B 0D 98 A5 56 00  mov ecx, [0x56A598]       ; ecx = *g_pVFileSys（全局里存的是指针）
  89 01              mov [ecx], eax            ; **透过该指针写入**
  C3                 ret

我们的 symbol ??0OpenNULLFile@@QAE@XZ = **58 字节**（有栈帧 push ebp/…/mov [ebp-4],ecx …）
```
⇒ 两点纠正：
1. **F49 的"源码平凡"是错的**：我用 `[^}]*` 抓函数体，被**嵌套大括号**提前截断，只看到第一行。
   真实 ctor 体比那长得多（58 字节的产物为证）。
2. **这是真实差异**：二进制是 **`*g_pVFileSys = this->m_plastsys;`**（透过全局指针写），
   而我们的 decomp 渲染成 **`g_pVFileSys = this->m_plastsys;`**（写全局本身）——语义不同 ⇒ 4 字节差异。
**修法方向**：查 `g_pVFileSys`（全局 0x56A598）与 `m_plastsys` 的注解类型；
二进制证据表明"全局持有指针、被写的是**指针所指对象**"，所以要么全局类型应为 `gbVFileSystem *`，
且 decomp 丢失了解引用（需查是注解还是 Hex-Rays 渲染所致），要么 `m_plastsys` 的类型错。
**教训（本会话第 11 次校正）**：**别用简易正则提取函数体**（嵌套大括号会截断，导致"源码看起来平凡"的假象）。
提取函数体要用**大括号配平**（或 tree-sitter）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F49 第 102 轮：triage 第 1 项 `OpenNULLFile::OpenNULLFile` —— **源码平凡，疑为读数侧问题**
* 事实：生成物与 decomp **逐字一致**且**平凡**：
  ```c
  class OpenNULLFile { public: gbVFileSystem * m_plastsys; // +0x0 };   // 无 vptr，size 4
  OpenNULLFile::OpenNULLFile() { g_pVFileSys = this->m_plastsys; }      // 一行
  ```
  按此源码，MSVC 应发 `mov eax,[ecx]; mov g_pVFileSys,eax; ret`（与二进制一致）。
* 但解释器（`s4_diff_explain.json`）显示首分歧为 **原 `mov eax,[ecx]` vs 我们 `mov eax,ecx`** ——
  后者等于把**对象地址**存进全局，与本源码的语义不符。
* ⇒ **两种可能**：(a) 解释器读到的 `.obj` 与我读的 `.cpp` **不同源**（`s4_diff_detail.json` 的 obj 来自上一次 match，
  其后若单独跑过 codegen 就会错位）；(b) `s4_diff_detail.json` 里该行记录的单位/符号与我读的文件不是同一个。
**下一轮一步定性**：直接**编译 `pal3/src/Misc/OpenNULLFile.cpp`** 并反汇编 `?OpenNULLFile@...` 的首两条指令，
看是 `8B 01`（`mov eax,[ecx]`）还是 `8B C1`（`mov eax,ecx`）——
* 若为 `8B 01` ⇒ **是解释器/匹配的读数错位**（工具问题），该项应从队列移除；
* 若为 `8B C1` ⇒ 是真差异，需查 codegen 为何生成等值于"取对象地址"的代码。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F48 第 101 轮：**刷新"最接近 L1"队列**（n_diff ≤ 12 的只有 27/187）
按最新分类（F46 之后）统计：**n_diff ≤ 12 的函数 27 个 / 187 个 partial（14.4%）**，其余 160 个需结构性投入。
清单（前 16，已标注本会话的处置状态）：
| 函数 | n_diff | size | cause | 本会话处置 |
|---|---|---|---|---|
| `AStarPathFinder::FindInClosed/FindInOpen` | 1 | 34 | this-register | **已关闭**（寄存器分配硬尾巴，F46-bis） |
| `SceneMgr::ClearInactiveRoles` | 1 | 58 | cond-jump signedness | **已关闭**（无已知修法，F44） |
| `TextureLib::ClearAndJump` | 2 | 10 | opcode/flow | **已关闭**（`JUMPOUT` 不可修，F37-bis） |
| `TextureLib::SetPath` | 2 | 63 | register choice | 硬尾巴，未处置 |
| **`OpenNULLFile::OpenNULLFile`** | 4 | 11 | this/member disp | **待定性** |
| **`PlayerAtt::CheckCurRV`** | 4 | 44 | operand shape | **待定性** |
| `UICaption::DestroyPanel` | 4 | 8 | adjustor-thunk | **已降级**（多继承归属，F40） |
| **`ObjectCamera::ObjectCamera`** | 5 | 5 | opcode/flow | **待定性**（ctor thunk「丢调用」，F19 曾试过并回归） |
| **`Parent_Data::_CheckStr`** | 5 | 11 | this/member disp | **待定性**（疑似 Hex-Rays 把全局常量折叠） |
| **`_Console::SetActive`** | 5 | 32 | immediate/const | **待定性** |
| **`CCBProtectWindow::CCBProtectWindow`** | 6 | 11 | opcode/flow | 待定性 |
| **`Comp_Donate::Reset`** | 6 | 11 | register choice | 待定性 |
| **`SceneObjParam::FlushCommands`** | 7 | 11 | opcode/flow | 待定性 |
| **`UI3DCtrl::ctor`** | 7 | 11 | opcode/flow | 待定性 |
| **`UICursor::IRender`** | 7 | 22 | operand shape | 待定性 |
⇒ **下一批应triaged 的是那 9 个"待定性"项**（每个都 ≤7 字节）；已关闭/降级的 5 项不再投入。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F47 第 100 轮：**目标状态确认 + 交接（roundsStarted 100 / maxGoalRounds 120）**
`get_goal` 实测：`phase = active` · `roundsStarted = 100` · `maxGoalRounds = 120` · `activation = armed`
⇒ **目标未完成（未收敛），保持 active**，剩余 **20 个目标轮次**。
**"未完成"的证据（不是主观判断）**：① L1 32/219 ≈ 14.6%（会话初 21/219 ≈ 10.8%）—— 有进展但远未收敛；
② 128 个失败 unit 中 codegen 发射缺陷仍是主体（C2664/C2440 93 · C2660/C2661 72 · vftable 残留 39）；
③ partial 仍有 187 个，剩余桶以**硬尾巴/结构性**为主（`register choice` 50 · `immediate/const` 30 ·
`opcode/flow` 70 · `operand shape` 18 · `this/member disp` 15 · `this-register` 2 · 其余 2）。
**主上下文预算已枯竭**（这是"会话容量"限制，不是目标被阻塞），因此近 10 轮只做**零风险证据工作**
（F38 台账、F39 早期修复回归、F40/F44/F46-bis 三次类别关闭、F41 门禁快照、F42 子代理合规、F43/F45/F46 工具批）。
**下一步（20 个目标轮次内的优先顺序）**：
1. **消费两个在途设计调查**：`fa592148`（`0.0f` 字面量变换 —— **唯一可能带来真实收益的在途项**）、
   `3ffcd6e3`（调整器 thunk + `JUMPOUT` 交叉确认；后者我已判定不可修）；
2. 按设计给出的**逐字补丁**落地 → 跑全链（门禁 `new_failures` 0、L1 ≥ 32）；
3. 若 `0.0f` 落地后 L1 不涨，则本会话的"可机械定位批次"基本耗尽 ⇒ 应转入**结构性投入**
   （TU 划分/内联、多继承归属、20 个 thunk 签名对齐），或宣告**本阶段收敛**（剩余仅硬尾巴与已证不可修项）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32** · partial 187 · tracked 基线干净 · 三态一致。

### F46-bis 第 99 轮：`this-register` 族定性 —— **与 decomp 逐字相同，是寄存器分配差异（硬尾巴）**
生成物与 decomp **逐字一致**：
```c
AStarPathFinder::NODE *OPEN; // ecx
OPEN = this->OPEN;
for ( i = OPEN->next; i; i = i->next ) { if ( i->key == nTileIdx ) break; OPEN = i; }
```
而首分歧是 `mov eax,[ecx+0x3c]`（原）vs `mov eax,[eax+0x3c]`（我们）——
即**原函数在这一刻 `this` 仍在 `ecx`，我们已把对象放进 `eax`**；34 字节里只差这 1 个寄存器字节。
⇒ **这不是注解/原型问题**（源文本与 decomp 完全相同），而是**寄存器分配差异** ——
与 `register choice differs`（50 个）属同一类**字节匹配硬尾巴**。
**处置**：从"+2 L1 的确定性目标"**降级为硬尾巴**（除非能找到"源码形态微调"让分配一致；
那需要实验，代价高于 2 个 L1 的收益）。
**本轮净结果**：无生成物改动；用一次三侧对照**避免把硬尾巴误当可修目标**（否则会像 F35 那样白花数轮）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F46 第 98 轮：`this-register` 探测**用正确方法落地**，量化出 **2 个函数 / 各差 1 字节 / 同一成因**
* 做法（对照 F45 的失败）：改用 **`edit` 工具**（多行、无字符串拼接）在
  `tools/byte_diff_explain.py` 的 `classify()` 里插入基址寄存器比较 —— 一次成功，`py_compile OK`。
* 结果（187 partial）：新桶 **`this-register differs (this in a different reg)` = 2**，
  成员为 **`AStarPathFinder::FindInClosed` / `FindInOpen`**（各 `n_diff=1`，34 字节）：
  ```
  原函数: mov eax, dword ptr [ecx + 0x3c]
  我们:   mov eax, dword ptr [eax + 0x3c]
  ```
* 分桶变化：`this/member disp differs` 17 → **15**（2 个移入新桶）。
⇒ **这是一个"一次修复、+2 L1"级别的确定性目标**（同一成因、各只差 1 字节），
且与 F18 同型（F18 也是"一个成因、多个函数受益"）。
**下一批首选**：定性 `AStarPathFinder::FindInOpen` 为何把 `this` 放进 `eax`（是局部量的静态类型/别名问题，
还是 codegen 生成了 `this->…` 之外的取址方式），拿到证据后按注解/codegen 正途修复。
**本轮净结果**：工具探测落地（且验证了 F45 的流程教训），并**新产出一个 +2 L1 的候选批**。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F45 第 97 轮：一次**写坏—修复** + 流程教训（用 `python -c` 改代码不可靠）
* 意图：给解释器再加一类探测（`this` 落在不同寄存器，即 `AStarPathFinder` 那族 `[ecx+…]` vs `[eax+…]`）。
* 过程：用 `python -c` + PowerShell 字符串拼接生成新代码行 → **括号不匹配 ⇒ `tools/byte_diff_explain.py` 语法错误**。
* 处置：**立即定位该行并还原**（按行前缀匹配替换回原句）→ `py_compile OK`、`byte_diff_explain.py` 输出恢复正常
  （直方图与 F44 之后一致：`opcode/flow` 70 · `register choice` 50 · `immediate/const` 30 · `operand shape` 18 ·
  `this/member disp` 17 · `adjustor-thunk` 1 · `cond-jump signedness` 1）✓
* **未落地**：`this-register` 探测**没有**加入（留待用正确方法实现）。
**流程教训（本会话第 3 次踩到，值得写成规则）**：**不要用 `python -c` + PowerShell 字符串拼接去改代码**。
本会话已因此失败 3 次（两写 CHANGE_LOG、本次改解释器），原因各异但同源：
PowerShell 双引号内 **反引号是转义符**、**三引号/多行字符串会被拆**、**拼出来的括号/引号易错**。
⇒ **改代码一律用 `write`/`edit` 工具或临时 `.py` 脚本文件**；`python -c` 只用于**只读查询**。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（工具已恢复可用，无残留破坏）。

### F44 第 96 轮：给解释器加"有符号/无符号跳转"探测 → **爆炸半径 = 1**
* 改动：`tools/byte_diff_explain.py` 的 `classify()` 在"助记符不同"分支里，若两侧都是条件跳转
  （`jl/jle/jg/jge/jb/jbe/ja/jae`）则单列一类 **`cond-jump signedness differs (annotation type)`**。
* 验证 + 量化（187 partial）：新桶 **1 个** —— `SceneMgr::ClearInactiveRoles`（n_diff=1，58 字节，`jl 0x18`）。
* 分桶随之变化：`opcode/flow` 71→**70**、`this/member disp` 18→**17**、`immediate/const` 29→30。
⇒ **该注解类缺陷的"首分歧"家族只有 1 个函数**。结合 F35-bis（`m_nRoleCount@57568` 本来就是 `int`）
与 F35-ter（改 `UISceneUpdate` 返回类型已证无效），**这一项目前没有已知可行修法**。
**处置：把它并入"结构性/待定"清单**（与多继承归属、TU 划分同类），不再当作可快修项；若后续找到
"让基址获得类型"的通用手段（例如把 `dword_D8BBEC` 那两个全局数组标注为某个类的实例），可重新评估。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F43 第 95 轮：清掉 F41 记录的工具债（不变量 A 文案口径）
* 改动：`tools/codegen_invariants.py` 的 A 检查提示由
  `（生成头从不声明 __vftable ⇒ 每一行都是 C2039/C2227 编译错误）`
  改为 **`（**结构性**指标：活代码位置的 __vftable 残留行数；不等于编译错误数 —— F11/F12 之后这些行多数已不再是错误）`**。
* 验证：`py_compile` 通过；`--check A` 输出确认新文案生效（131 行 / 25 文件，逐文件列出）。
* 价值：防止后续会话把 131 当成"待修的 131 个错误"去追（当前实际只有 128 个失败 unit 且 `new_failures = 0`）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F42 第 94 轮：**子代理只读合规审计 + 会话容量说明**
* 工作区 `M` 清单与本会话已知改动**逐一吻合**（13 个注解 + 2 个头文件 + 6 个 pipeline + 2 个 tools），
  另有 **2 个非本会话项**（`tools/vc6/Lib/LIBCMT*.LIB` 由工具链重写、`data/status/annotation_fix_batch.json` 0 字节遗留），
  均在第 86 轮就存在 ⇒ **8 个已完成的只读调查子代理没有改动任何仓库文件** ✓
* `data/status` 内**无 scratch 残留**（无 `_ab_*`、无 `.i`）✓
* 仍在跑：`fa592148`（`0.0f` 字面量变换）、`3ffcd6e3`（调整器 thunk + `JUMPOUT` 交叉确认）。
**会话容量说明（诚实记录）**：本会话已推进到主上下文预算枯竭，剩余轮次**不足以完成"改动 + 全链 A/B"一整个周期**。
因此近几轮改为**只做零风险的证据性工作**（回归校验 F39、门禁快照 F41、只读合规审计 F42、收敛台账 F38），
**不新开无法验证的改动** —— 这是本会话反复验证过的纪律（第 55 轮归因错误、第 81 轮遗留混合态，代价都很高）。
**满足门禁的可续接状态**：S2 **73/201** · `new_failures` **0** · **L1 32** · partial 187 · tracked 基线干净 · 三态一致 ·
早期修复未回退（F39）· 门禁未被污染（F41）· **尚未收敛**（F38 台账：剩余多为寄存器分配/内联结构/多继承归属类结构性工作）。

### F41 第 93 轮：**工具/门禁健康快照**（与记录一致）
| 检查 | 结果 | 与记录对比 |
|---|---|---|
| `cli.py check`（注解合法性） | **0 errors, 13 warnings — PASS** | 一致 ✓ |
| `pytest pipeline/gen/test_pipeline.py` | **6 failed / 38 passed** | **仍是 HEAD 既有那 6 个**（本会话新增 0）✓ |
| 不变量 A / B / D | A 131 行/25 文件 · B 55 处 · D 10 类 | 与 F30/F16 记录一致 ✓ |
⇒ **本会话的改动（6 个 pipeline 文件 + 2 个头文件 + 13 个注解 + 4 个工具）没有污染任何门禁或测试。**
**顺带发现的工具债（记录，避免后人误追）**：不变量 **A 的提示文案已过时**——
它写着"生成头从不声明 `__vftable` ⇒ 每一行都是 C2039/C2227 编译错误"，
但自 F11（virtual 类不再发 +0 占位）与 F12（语句位裸链改 stub）之后，
那 131 行**不全是**编译错误（当前只有 128 个失败 unit 且 `new_failures = 0`）。
⇒ 该文案应改为"活代码位置残留（**结构性**指标，不等于错误数）"，否则会误导后续会话去追 131 个幻影错误。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F40 第 92 轮：调整器 thunk **定性为多继承归属问题**（不是 codegen 快修）
事实：
* 生成物 `void UICaption::DestroyPanel() { UICaption_Destroy2(); }` —— **无接收者**，故缺 `add ecx,0x60`；
* `UICaption` 的 `binary_size = 96 (0x60)`，基类为 **`['UIWnd', 'PalScriptWaitObj']`（多继承！）**；
* 而二进制里的调整量正是 **+0x60** ⇒ `this+0x60` **恰好是 UICaption 之后** ⇒ 该调用是针对
  **第二个基类子对象/派生类**发出的 **adjustor thunk**（MSVC 为 MI 生成的那种）。
* 注解层还存在**重复登记**：`UICaption.json:54` 有成员方法 `Destroy2`，`functions.json:819` 又有自由函数 `UICaption_Destroy2`
  ⇒ Hex-Rays 选了自由函数渲染，于是 ECX 调整整条消失。
**结论**：这不是"给 codegen 加一条规则"能修的，而是**多继承归属（哪段代码属于哪个基类子对象）**的注解问题，
属于 F30-quater 复核里点出的"UIProgressBar/UIButton 整类重映射"同一类**结构性**工作。
**处置：从"形态明确的小目标"降级为"需多继承归属工作的结构性目标"**，不再当作快修；上限 1 个函数，优先级下调。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F39 第 91 轮：**早期修复的回归校验（全绿）**
在后续又做了 10+ 处改动之后，复查本会话早期三个已验证修复是否被静默回退：
| 修复 | 判据 | 复查结果 |
|---|---|---|
| **F11** 有 virtual 的类不发 +0 占位 | 含 `void * __vftable;` 的头文件数 | **0** ✓ 保持 |
| **F18** 基类重复计数 | "首个 gap 起点 < `base_size`"（吃进基类区）的头文件数 | **0 个真 bug** ✓（合法类内空隙 38 个） |
| **F16** 不变量 D 口径修正 | 报出的真问题类数 | **10**（与修正后预期一致）✓ |
⇒ **本会话的累积改动没有互相破坏**；早期收益稳定。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F38 第 90 轮：**收敛台账**（本会话结束时的客观状态，供直接续接）
**指标轨迹（全部同谱系 A/B 验证，`new_failures` 全程 0）**
| 阶段 | S2 ok | L1 | partial | 关键改动 |
|---|---|---|---|---|
| 会话开始 | 70/201 | 21 | 195 | — |
| +0 占位/vfptr（F11） | 70 | 22 | 195 | `emit_headers` 去掉 virtual 类的 +0 占位 |
| stub 路径两处通用缺陷（F12） | 72 | 22 | 191 | 签名清洗 + 未解析裸链通用 stub |
| `0x004B59B0` 归属（F13） | 73 | 22 | 191 | `TextureLibDataBase::sub_4B59B0` |
| F18 基类重复计数 | 73 | **28** | 191 | `base_size` 从 `bases[]` 推导 + 有真实基类时不发 +0 占位 |
| F20 thunk 尾跳 | 73 | **31** | 188 | `#pragma inline_depth(0)` + ctor/dtor 门 |
| F23 `0x00445FA0` 成员化 | 73 | **32** | 187 | 自由函数 → `UIWnd::sub_445FA0` |
| F29/F30/F36（中性或纠正） | 73 | 32 | 187 | 原型修正、pack、HIBYTE（差异 80→79 但不翻 L1） |

**已主动关闭的机制（判定无可测收益或不可修）**
1. **F30** `gbGfxManager` +4：只影响部分 TU（依赖包含顺序），对当前可测集合收益 0（pack 补丁保留）；
2. **F37-bis** `JUMPOUT`（6 处）：跳进函数中部，codegen 不可修；
3. **`std::operator+` × `gbVec3D`**（复核 B）：真实 Hex-Rays/类型边界。

**剩余队列（按可测性）**
① `0.0f` 后缀变换（设计 `fa592148` 在跑；覆盖 `immediate/const` 桶 27 个的一部分）；
② 调整器 thunk（`UICaption::DestroyPanel`，全仓仅 1 个；设计 `3ffcd6e3` 在跑）；
③ `SceneMgr::ClearInactiveRoles` 的 `jl`/`jb`（成员类型已正确，改返回类型已证无效——需另找有符号化路径，或判不可修）；
④ thunk 签名对齐 20 个（4 个虚函数需单独评估 vtable 扰动）；
⑤ `HIBYTE` 后续收益（每个受影响函数约 −1 字节，需与其它修改叠加才可能翻 L1）。

**收敛判据的当前读数**
* 编译轴：128 个失败 unit 中，**codegen 发射缺陷仍是主体**（C2664/C2440 93 unit、C2660/C2661 72、vftable 残留 39）；
  但**本会话已证明"编译轴增益不自动转化为 L1"**（F12 +2 unit 而 L1 不变）；
* 字节轴：**L1 32/219 ≈ 14.6%**（会话初 21/219 ≈ 10.8%），partial 187；
  剩余原因分布：`opcode/flow` 71 · `register choice` 50 · `immediate/const` 29 · `operand shape` 18 · `this/member disp` 18 · `adjustor-thunk` 1
  ⇒ **尚未收敛**，但**"可机械定位 + 一轮内可验证"的批次正在变少**（从会话初的低残余 7 个 1 字节函数，到现在多为寄存器分配/内联结构类）。
* 结论：**未达收敛**，但已进入"收益变稀疏、需要更大结构性投入（TU 划分 / 内联 / 20 个签名对齐 / 整类重映射）"的阶段。

**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（tracked 基线干净、三态一致）。

### F37-bis 第 89 轮：`JUMPOUT` 类**判定不可修**（A 级证据，关闭该类）
* `0x53F570` **不是任何函数的起点**；它落在 **`TextureLib::ClearGlobalVars`（0x53F560，89 字节，止于 0x53F5B9）内部**（= 该函数 +0x10）。
* 而 `TextureLib::ClearAndJump`（0x53F550，10 字节）的 decomp 是
  `{ TextureLib::ClearGlobalVars(this); JUMPOUT(0x53F570); }`
  ⇒ 它是一个**跳进另一个函数中部**的尾部跳转（共享代码片段 / IDA 边界识别所致）。
* 从 C++ 复现这种"跳到函数中部"**不可行**（需要内联汇编/裸函数），且 `JUMPOUT(x)` 是**空宏**，
  所以生成物里那条跳转彻底消失 —— 这不是 codegen 能修的问题，其上游在 IDA/反编译层。
**处置：把 `JUMPOUT` 类（全仓 6 处）判定为"已证不可修"，记入收敛清单，不再投入。**
（同族对照：`TextureLib::ClearGlobalVars` 本身已在 F29 因 `_nearby_53f4c0` 去幻影形参而受益，
其 n_diff=17 的残余**不属**本类。）
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F37 第 88 轮：`JUMPOUT` 目标快速定性（队列④第 2 项）
* `include/pal3/ida_defs.h:73`：`#define JUMPOUT(x)` —— **空宏** ⇒ 生成物里的 `JUMPOUT(0x53F570);`
  **编译后什么都不剩** ⇒ 原函数的那条 `call`/`jmp` 在我们的代码里**完全消失**（这就是 `mov {R}` vs `call` 的由来）。
* 全仓只有 **6 处** `JUMPOUT(`（`free_functions.cpp` 4 处 + 另 2 处），不是一大类。
* 目标 `0x53F570` **在任何注解里都不存在** ⇒ 要发出一条**直接 `call`**（字节匹配所需）就必须先让该地址
  成为**具名符号**。**判定要点**：`0x53F570` 是**函数起点**（则补注解即可修）还是**函数中部**（则不可修，属 IDA 不可解析跳转）。
**结论（待子代理交叉确认）**：这一项**上限只有 6 个函数**，且取决于目标是否为函数起点；
若为函数中部则**应判定为不可修并记录**，不再投入。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F36 ★ 第 85 轮：**纠正第 55 轮的误判** —— HIBYTE 修复本身无害，已重新落地（有正面证据）
**背景**：第 55 轮我把 `HIBYTE` 由 `+1` 改成 `(sizeof(x)-1)` 后观测到退化（S2 73→72、new_failures 1、L1 32→30），
遂回滚并把"HIBYTE 修复"记为危险。**但真正的元凶是同一轮我用 python 重写 `ida_defs.h` 时把 CRLF 改成 LF，
激活了 GBK 续行坑**（该坑已于第 63 轮修复：给中文注释行末补 ASCII 空格）。二者当时被混为一谈。
**本轮重测**（用**二进制级字节替换**，完全不碰行尾）：
* `include/pal3/ida_defs.h`：`#define HIBYTE(x) (*(((_BYTE*)&(x))+1))` → `(sizeof(x)-1)`
  （Hex-Rays 的 HIBYTE 语义 = **操作数自身类型的最高字节**：`__int16`→+1、4 字节指针→+3；`HIWORD/HIDWORD` 本来就是类型化指针算术，只有 HIBYTE 写死成 +1）；
* 同谱系 A/B：S2 **73/201**、`new_failures` **0**、**L1 32（不变）**；
* **正面证据**：`UI3DCtrl::UpdateOscillationX` 的 `n_diff` **80 → 79**（其余三个 `Update*` 本来都是 79）
  ⇒ 修掉了复核预测的那 1 字节（`[ecx+0x121]` → `[ecx+0x123]`），四个兄弟终于一致。
**处置：保留该修复**（语义经实验证明、门禁全绿、有可测的差异下降；只是 1 字节不足以翻 L1）。
**沉淀的教训**：① **一次改动只能引入一个变量**——第 55 轮同时"改宏"与"重写整个文件"，
导致归因错误并浪费约 30 轮；② **重写含中文注释的文件必须保持原行尾**（现已写入 `docs/knowledge/` 的 GBK 条）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F35-quater 第 82 轮：**再同步完成**，三态一致，门禁恢复
按 F35-ter 的提示先做再同步：`apply → export → codegen all → probe_compile s2 → 对账 → match`。
结果：**S2 73/201** · `new_failures` **0** · **L1 32** ⇒ **注解文件 / IDB+export / 生成物 三态一致**，
门禁恢复健康；tracked 基线（`s4_baseline.json`/`pal3_registry.jsonl`）已备份还原、未推进。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

**⚠ 沉淀的流程教训（写入文档，供后续会话遵守）**：**回滚注解后必须立刻再同步**——
因为 `apply` 已把改动写进 IDB，仅还原注解文件会让 **IDB/export 领先于注解**，
此时任何 probe/match 读数都对应"混合态"（不可信）。正确顺序：
`还原注解 → apply → export → codegen → probe → match`（本轮即按此执行）。

### F35-ter 第 81 轮：`UISceneUpdate` 返回类型改动 → **无任何效果 → 已回滚**（第 9 次校正/回退）
* 定位到：**`SceneMgr` 已有偏移 57568 的成员**，且它**已经是 `int`**
  （`{"name": "m_nRoleCount", "type": "int", "source": "binary:*((_DWORD *)this+14392) count for Role array"}`）
  ⇒ **成员类型没标错**，F35-bis 的推断只对了一半。
* 真正的原因是**基址没有类型**：`UISceneUpdate()` 返回 `int`，Hex-Rays 只能做整数算术
  `*(_DWORD *)(result + 57568)`（`_DWORD` 无符号）⇒ 与 `int v1` 比较提升为无符号 ⇒ `jb`。
* **尝试**：把 `functions.json` 里 `UISceneUpdate` 的签名由 `int __cdecl()` 改为 `SceneMgr *__cdecl()`，
  走 apply → export → codegen → probe → match 全链。
* **结果：完全无变化**（S2 **73/201**、`new_failures` **0**、**L1 32**）⇒ 该注解改动**既无收益也无害**。
* **处置**：按"不保留无收益的推测性注解改动"原则**已回滚**（签名恢复 `int __cdecl()`，
  `SceneMgr.json` 从备份还原）。`functions.json` 相对 HEAD 的 8 处差异 = 本会话 F23（删 `0x00445fa0`）+ F29（`_nearby_53f4c0` 去幻影形参），均为已验证改动。
* **⚠ 状态提示（下一轮第一件事）**：回滚只改了**注解文件**，而上一轮链路已把 `SceneMgr *` 写进了 **IDB 与 export** ⇒
  **IDB/export 当前领先于注解**。下一轮必须**先重跑 apply → export → codegen → probe → match** 把三者同步回去，
  确认回到 **73 / 0 / 32**，再继续队列。
**当前状态（注解已回滚，但 IDB/导出待同步）**：注解文件为本会话已验证集合；`s4_baseline.json`/`pal3_registry.jsonl` 干净。

### F35-bis 第 80 轮：**修正 F35 的修法方向** —— `UISceneUpdate` 真的返回地址常量
反汇编/反编译 `UISceneUpdate`（0x004226F0，50 字节）：
```c
int __cdecl UISceneUpdate() { return 493156 * (dword_D8BBEC == 1) + 12722152; }
```
⇒ 它返回的是**两个相邻全局数组之一的基址**（`0xC23F88` 或 `+493156=0x78664` → `0xC9A18C`），
**`int` 返回类型本身没错**（原代码确实把地址当整数用）。
因此真正的修法是**让 Hex-Rays 把 `result + 57568` 处的读取识别为 `int`**：
* 现状：读取被渲染成 `*(_DWORD *)(result + 57568)`（`_DWORD` = **无符号**）⇒ 与 `int v1` 比较时提升为无符号 ⇒ `jb`；
* 正解：在**拥有那两个全局数组的类**上，把偏移 **57568 (0xE0E0)** 的成员标注为 **`int`**
  （该类的对象即 `UISceneUpdate` 返回的地址）⇒ 渲染成 `p->m_xxx`（有符号 int）⇒ 比较回到 `jl`。
**下一轮**：(a) 由两个全局基址 `0xC23F88` / `0xC9A18C` 反查它们所属的类（哪个注解类/结构体对应这片 .data），
(b) 在该类加一条 `offset 0xE0E0, type int` 的成员注解，走 apply → export → codegen → probe → match 全链
（门禁 `new_failures` 0、L1 ≥ 32），预期 **+1 L1**。
**教训（第 8 次结论校正）**：F35 把"`int` 返回类型"当成错误，实际是**成员类型缺失**导致操作数退化为 `_DWORD`；
凡是"有符号/无符号"或"裸 `_DWORD` 偏移"的差异，优先怀疑**成员类型注解缺失**，而不是返回类型。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F35 第 79 轮：`SceneMgr::ClearInactiveRoles` 的 `jl`/`jb` **根因锁定**（注解类，1 字节）
生成物与 decomp 逐字一致，函数体是：
```c
result = UISceneUpdate();                 // ← result 被当成 int
if ( *(int *)(result + 57568) > 0 ) { … while ( v1 < *(_DWORD *)(result + 57568) ); }
```
* `v1` 是 `int`（有符号）；而 `*(_DWORD *)(result + 57568)` 里的 **`_DWORD` 是无符号 long**
  ⇒ `int < unsigned` 触发**算术转换到无符号** ⇒ MSVC 发 **`jb`**；二进制发 **`jl`**（有符号比较）。
* **根因**：`UISceneUpdate()` 的**返回类型注解**是 `int`，于是 Hex-Rays 只能把返回值当整数基址、
  成员访问退化成 `_DWORD` 裸偏移（**丢掉了成员的真实类型**）。这也解释了为什么该函数体里全是 `result + 57568`
  这种巨大裸偏移（而不是 `p->m_xxx`）。
**修法（注解类、有原则、非局部 hack）**：把 `UISceneUpdate()` 的返回类型改成**正确的指针/类类型**
（即它真正返回的那个单例对象），让 Hex-Rays 渲染成 `p->m_field` / 保符号的整型访问 ⇒ 比较回到有符号 `jl`。
**预期**：+1 L1（58 字节里只差这 1 字节），且很可能顺带改善同族函数。
**下一轮**：先取 `UISceneUpdate` 的注解现状与其真实返回对象（反汇编其本体 / 看调用点用法），
再决定返回类型；改动需走 apply → export → codegen → probe → match 全链（门禁 `new_failures` 0、L1 ≥ 32）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F34 第 78 轮：解释器修正（call/jmp 目标两侧掩码）→ 暴露两个真目标
**问题**：`byte_diff_explain.py` 的 `key()` 只对我们这侧的重定位操作数做掩码（`{R}`），
原函数侧却显示真实相对位移 ⇒ `call 0xfffff1f0` vs `call {R}` 被**误报为首个分歧**，
把"调用目标"假推到最低残余榜首（`SceneMgr::ClearInactiveRoles` 就是被这样误报的）。
**修正**：`call`/`jmp`（非 `dword ptr`/非 `[` 形态）两侧统一掩码为 `{T}` —— 目标是否一致是 match 的
relocation 判据职责，解释器只做**掩码后**的指令对齐。
**修正后立刻暴露两个真目标**：
* **`SceneMgr::ClearInactiveRoles`（n_diff=1，58 字节）**：首分歧变为 **`jl 0x18`（原）vs `jb 0x18`（我们）**
  ⇒ **有符号/无符号条件跳转不同**，与复核 C 早先采到的同类实例（`7C` jl vs `72` jb）完全一致
  ⇒ **这是可修的注解类型问题（该比较的操作数应为有符号/无符号之一）**，且只差 1 字节。
* 分桶随之修正：`opcode/flow` 65→**71**、`operand shape` 27→**18**、`register choice` 49→50、`immediate/const` 27→29
  （原被误算进 `operand shape` 的调用目标项回归到 `opcode/flow`）。
**下一批首选**：`SceneMgr::ClearInactiveRoles` 的 `jl`/`jb` —— 先定位该比较的操作数与它的注解类型，
按 A 级证据修正；预期 +1 L1。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F33 第 77 轮：用最新数据重排（187 个 partial，本会话全部改动落地之后）
| cause | 会话初（195） | F18 后 | F20 后 | **现在（187）** |
|---|---|---|---|---|
| `opcode/flow differs` | 73 | 70 | 69 | **65** ↓ |
| `register choice differs` | 47 | 47 | 47 | **49** ↑ |
| `immediate/const differs` | 21 | 23 | 24 | **27** ↑ |
| `operand shape differs` | 27 | 28 | 28 | **27** |
| **`this/member disp differs`** | **27** | 20 | 19 | **18** ↓（F18 的直接贡献） |
| `adjustor-thunk` | — | — | 1 | 1 |
⇒ **`this/member disp` 从 27 降到 18（−9）**、`opcode/flow` 从 73 降到 65（−8），而 `register choice` 与 `immediate/const` 略升
（说明"修好一批后，残余相对集中到寄存器分配/常量这两类硬尾巴"）。
**最低残余清单（前 8，均已多轮稳定）**：`AStarPathFinder::FindInOpen/FindInClosed`(1)、`SceneMgr::ClearInactiveRoles`(1)、
`TextureLib::ClearAndJump`(2)、`TextureLib::SetPath`(2)、`OpenNULLFile::OpenNULLFile`(4)、`PlayerAtt::CheckCurRV`(4)、
`UICaption::DestroyPanel`(4，调整器 thunk)、`ObjectCamera::ObjectCamera`(5，ctor thunk)。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F32 第 75 轮：`0.0` vs `0.0f` 定性（队列①，codegen）
生成物与 decomp **逐字相同**，所以字面量直接来自 Hex-Rays：
```c
if ( this->m_tradius > 0.0 )     // m_tradius 是 float
if ( fValue < 0.0 )
m_tradius = 0.0;
```
在 C++ 里 `float > 0.0` 会把左值**提升为 double**，于是 MSVC 发射 **`fcomp qword ptr [double 0.0]`**；
而二进制做的是**float 比较**（`fcomp dword ptr [0x56A644]`）。
⇒ **修法（codegen 等价变换）**：当比较/赋值的一侧是 `float` 类型、另一侧是 `0.0`/`1.0` 这类**双精度字面量**时，
把字面量写成 **`0.0f`/`1.0f`**（保持语义，去掉提升）。这是通用规则、不针对任何具体函数。
**落点（下轮实现）**：`pipeline/gen/stages/` 里做文本/AST 变换的阶段（stage5_fixup 或 stage3）加一条：
匹配 `<float-typed-expr> (>|<|>=|<=|==|!=) <double-literal>` 与 `=` 赋值形态，替换字面量后缀为 `f`。
**先要判定的风险**：项目里是否已有类似"补 f 后缀"的既有 pass（避免重复/冲突）；以及
`0.0` 出现在**确实需要 double** 的上下文（例如 `double` 变量比较）时**不能**改 —— 因此规则必须以"另一侧是 float"为条件。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F31 第 74 轮：清掉归档债
`data/annotations/CHANGE_LOG.md` 补上了 F29（`CScreenMode::_nearby_53f4c0` 去幻影形参）的条目：
含 A 级证据（`8B C1` / `C7 00 58 0A 57 00` / `C3` = 0 栈参）与同谱系 A/B 结论（S2 73/201、new_failures 0、L1 32 中性）。
`0x00445FA0` 的条目已在第 49 轮归档。**至此本会话所有注解改动都有 CHANGE_LOG 记录。**
（工具提示：PowerShell 双引号内**反引号是转义符**，会把 python 源码里的反引号吃掉 → 写 python -c 时文本里不要用反引号。
另：`data/status/s4_baseline.json` / `pal3_registry.jsonl` 状态干净，未推进 tracked 基线。）
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F30-nonies ★ 第 73 轮：**F30 结案** —— "+4" 只影响**部分 TU（取决于包含顺序）**，且**不影响被测量的那 14 个函数**
**直接编译 + 反汇编**（绕开 match 与所有缓存）`pal3/src/Misc/UIProgressBar.cpp` 的
`?Render@UIProgressBar@@UAEXXZ`（obj 内 1179 字节）：
```
mov ecx, dword ptr [eax + 0xd8]   ← pMatrixStack[1]（0xD4+4）
mov eax, dword ptr [edx + 0xd4]   ← pMatrixStack[0] = 0xD4  ✓ 纸面/二进制
mov edx, dword ptr [ecx + 0x1c0]  ← pSceneGraph   = 0x1C0  ✓ 二进制
```
⇒ **该 TU 从一开始就是正确的纸面布局**（0xD4 / 0x1C0），**从来没有 +4**。
而我上一轮"探针 TU 里 +4"也是真的（那个 TU 只包含 `gbGfxManager.h`）。
⇒ **结论**：`gbGfxManager` 的 +4 是**按 TU 的包含顺序**出现的（某条包含链会先把 pack 设成 8，
另一条链会先设成 4），**不是全局现象**；而被 s4 测量的那 14 个函数所在的 TU **本来就在正确的那一侧**
—— 这解释了"补丁生效、n_diff 却一个不变"的矛盾，也说明**复核当时给我的"`UIProgressBar::Render` 首个分歧是 gfxMgr +4"
是基于 %TEMP% 里的旧 probe obj**（它自己也说明是复用管线既有 .obj）。
**处置**：F30 的 `#pragma pack(push,4)` 补丁**保留**（它把"另一侧"的 TU 也钉成正确布局，属正向且门禁全绿：
S2 73/201、`new_failures` 0、L1 32），但**其在当前可测集合上的收益为 0**，因此 F30 这条线**到此不再投入**。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F30-octies 第 72 轮：矛盾进一步收紧 —— 补丁生效却"无影响"的三个已证事实
对 `pal3/src/Misc/UIProgressBar.cpp` 做 `/P` 落盘（`UIProgressBar.i`）后实测：
| 检查 | 结果 |
|---|---|
| `.i` 里 `class gbGfxManager {` 定义数 | **1** |
| `.i` 里 `struct gbGfxManager {` 定义数 | **0** ⇒ 不存在"struct 版本" |
| `.i` 里 `#pragma pack(push,4)` 出现 | **1** ⇒ **我的补丁确实在这个 TU 生效** |
| 该定义来自 | `#line … include/gbengine/gbGfxManager.h` ⇒ 就是我修补的那份 |
| 生成源码里的访问 | `75: v2 = gfxMgr->pMatrixStack[1];` / `76: …pMatrixStack[0];` / `81: pSceneGraph = gfxMgr->pSceneGraph;` |
⇒ **三个事实互相矛盾**：补丁在、定义唯一且正确、源码确实访问这些成员，**但**同轮 match 产出的
`s4_diff_detail.json` 里这些函数的 `n_diff` **完全没变**（`UIProgressBar::Render` 仍 594/814）。
**这指向一个更基础的问题：读数链路本身**（要么 `gfxMgr` 的声明类型不是 `gbGfxManager`，
要么 `s4_diff_detail.json`/match 用的 `.obj` 与当前头文件不同源，要么 match 的增量缓存）。
**下轮直查（绕开管线缓存，一步定性）**：
① 查 `gfxMgr` 的声明类型（`pal3/src/globals.h` / 生成源码的 extern 行）——若不是 `gbGfxManager*`，则偏移来自别的类型；
② **直接**用探针方式编译 `UIProgressBar.cpp` 并反汇编 `?Render@UIProgressBar@@…` 符号的字节，
   找 `pMatrixStack` 的位移是 **0xD4 还是 0xD8**（这是独立于 match 的 ground truth）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁绿；F30 的补丁保留，收益待①/②定性）。

### F30-septies 第 71 轮：修法**在探针里生效、对真实 TU 却无效**（重大线索）
* **改动**：在 `include/gbengine/gbGfxManager.h` 内、**紧贴类定义**（所有 `#include` 之后）插入
  `#pragma pack(push,4)` … `class gbGfxManager { … };` … `#pragma pack(pop)`（第 103–208 行外包裹）。
* **探针验证（生效）**：`m_nState` +8→**+4**、`pVertPoolMgr` 0xC8→**0xC4**、`pMatrixStack[0]` 0xD8→**0xD4**、
  `pSceneGraph` 0x1C4→**0x1C0**（**与二进制一致**）、`sizeof` 0x5F8→0x5F4。
* **完整 A/B**：S2 **73/201**、`new_failures` **0**、**L1 32**（门禁绿，无回退）。
* **但**：同一轮 `s4_diff_detail.json` 里那 14 个相关函数的 **n_diff 一个都没变**
  （`UIProgressBar::Render` 仍 **594/814**、`UI3DCtrl::Render` 192/357、`UpdateTransform` 249/288 …）
  ⇒ **该头文件的修改对真实 TU 完全没有影响**。
⇒ **结论（新线索）**：这些 TU 实际采用的 `gbGfxManager` 定义**不是** `include/gbengine/gbGfxManager.h` 那份
（与 F30-bis 发现的"两份定义"呼应：`gbengine_api.h:63` 也定义了同名类）。**修好一份、另一份仍在生效。**
**下一轮一步到位**：把 `pal3/src/Effect/UIProgressBar.cpp`（或 `UI3DCtrl.cpp`）用 `/P` 预处理落盘，
在 `.i` 里 `grep -c 'class gbGfxManager {'` 并打印**所有**命中处的成员列表与 `#line` 来源，
即可确定这些 TU 用的是哪一份定义；然后对那一份做同样处理（或统一收敛为一份）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁绿；本轮改动为"已验证正确、但当前测量下收益为 0"，
暂留并在 F30-septies 标注其未生效原因）。

### F30-sexies ★★ 第 70 轮：**机制锁定** —— MSVC 6 对"有 vptr + 含 8 字节成员"的类会**把首个成员推到 +8**
**机制实验**（同款 flags，三个最小类）：
| 类 | `a` 的编译位移 |
|---|---|
| `class T1 { public: int a; double d; virtual ~T1(); }` | **[ecx+8]** ⇒ vptr(4) 之后**多 4 字节填充** |
| `class T2 { public: int a; int b; virtual ~T2(); }` | [ecx+4]（正常） |
| `class T3 { public: int a; double d; }`（无 vptr） | [ecx+0]（正常） |
⇒ **MSVC 6 会把"含 `double`（8 字节对齐成员）且有 vptr 的类"对齐到 8，从而在 vptr 后插 4 字节填充**
—— 这正是 `gbGfxManager`（含 `double LastTime/CurTime`）`m_nState` 落在 +0x08 的原因，
也是 `pMatrixStack` 0xD8（纸面 0xD4）、`sizeof` 0x5F8（纸面 0x5F0）的总根源。
**注意**：原始二进制里 `m_nState` 在 +0x04（由 pMatrixStack@0xD4 反推）⇒ **原工程的该类没有这个头部填充**
（原编译单元里 pack/对齐是 4）。**修法方向：让该类的对齐回到 4。**
**本轮验证（未成功）**：在**外部**用 `#pragma pack(push,4)` 包住 `#include` **无效**（偏移照旧）
⇒ 说明类定义处生效的 pack **被某个嵌套头（`d3d9.h` 等）覆盖**（本项目 `include/` 内 `#pragma pack` 计数为 0，
所以嫌疑在编译器自带的 SDK 头）。
**下轮确切落点（一步可验证）**：把
```c
#pragma pack(push,4)
class gbGfxManager { … };
#pragma pack(pop)
```
**放进 `include/gbengine/gbGfxManager.h` 内部**（紧贴类定义、在所有 `#include` 之后），
然后重跑位移探针，期望：`m_nState@0x04`、`pMatrixStack@0xD4`、`sizeof=0x5F0`；通过后再跑完整 A/B
（这是**影响面很大**的头文件改动，门禁 `new_failures` 必须为 0、L1 不得低于 32）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁健康）。

### F30-quinquies ★ 第 69 轮：**+4 的根源 = 类起始处 8 字节的 vptr 区**（即两条 vtable）
按顺序读前几个成员的编译位移（一次探针，直接读出）：
| 成员 | 编译位移 | 纸面 | 结论 |
|---|---|---|---|
| `m_nState` | **[ecx+0x08]** | 0x04 | ⇒ **`+0x00` 处占了 8 字节** |
| `hGfxWnd` | `[ecx+0x0C]` | 0x08 | +4 |
| `DrvInfo.type` | `[ecx+0x10]` | 0x0C | +4 |
| `DrvInfo.width` | `[ecx+0x18]` | 0x14 | +4（且证实 type@0x10/subtype@0x14/width@0x18 一致） |
| `pVertPoolMgr` | `[ecx+0xC8]` | 0xC4 | +4 |

并且在探针 TU 的 `cl /E` 输出里，**`class gbGfxManager {` 只出现 1 处定义**，其成员列表与 `gbGfxManager.h:103` **逐字一致**
（`m_nState / hGfxWnd / DrvInfo / 4 指针 / pMatrixStack[4] / …`，**没有基类**）。
⇒ **矛盾点被隔离到极致**：定义文本无基类、成员顺序正确，但编译后 `+0x00` 是 **8 字节**。
MSVC 6 中类起始 8 字节只可能是**两条 vfptr（多继承或虚基类）**。
**下一轮两步即可定案**：
1. 把探针 TU 的 `.i` 里**从 `class gbGfxManager {` 到配对的 `};` 全部打印**（本轮只打了前 20 行），
   看是否在**尾部**出现 `: public …`/`virtual` 基类相关的痕迹，或是否有第二个同名声明被合并；
2. 搜仓内是否存在 **`#define gbGfxManager …`** 之类的宏（会把类名替换成别的东西），以及
   `gbGfxManager.h` 是否被某个 **`#pragma pack`/`#pragma vtordisp`** 上下文包裹（`vtordisp` 会为虚基类插入 4 字节！）。
   —— **`#pragma vtordisp` 是当前最强候选**：它会在有虚基类/虚函数的类里插入 4 字节，使类头变成 8 字节。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁健康）。

### F30-quater 第 68 轮：第一处 +4 定位到**类起始的第二条 vptr/基类**（证据链已很强）
实测（同一探针技术）：
| 读取 | 编译位移 | 纸面 |
|---|---|---|
| `pVertPoolMgr` | **[ecx+0xC8]** | 0xC4 ⇒ **从这里起 +4** |
| `pEffectMgr` / `pTexResMgr` / `pFontMgr` | 0xCC / 0xD0 / 0xD4 | +4 |
| `pMatrixStack[0]` | 0xD8 | 0xD4 ⇒ +4 |
| `m_pCurTexture[0]` | 0x5D4 | 0x5CC ⇒ **+8**（与 `sizeof(gbGfxManager)=0x5F8` vs 纸面 0x5F0 一致） |
| `hGfxWnd` | **[ecx+0xC]** | 0x08 ⇒ **+4** |
| `DrvInfo.type` | **[ecx+0x10]** | 0x0C ⇒ +4 |
- `sizeof(gbGfxDriverInfo)` = **0xB8**（纸面一致）；`struct A{char c; gbGfxDriverInfo d;}` = **0xBC**
  ⇒ 该结构体**对齐是 4、尺寸正常** ⇒ **排除"结构体胖/对齐"**。
- ⇒ 偏移从**类的最前面**就开始偏：`m_nState@0x04`（推定）、`hGfxWnd@0x0C`、`DrvInfo@0x10`
  ⇒ **`+0x00` 处有 8 字节而不是 4 字节（两个 vptr）**，或等价地**多了一个基类子对象**。
  这与 `gbGfxManager.h:103` 的 `class gbGfxManager {`（无基类、单 vptr）**矛盾** ⇒
  **该 TU 实际使用的类定义不是 `gbGfxManager.h` 那一份**（尽管它 include 的就是这个文件）。
**下一轮一步到位**：把该探针 TU 的 `cl /E` 输出落盘，在 `.i` 里搜 `class gbGfxManager`，
**直接看编译器真正采用的那份定义**（基类列表/成员列表）——这能立刻解释"两个 vptr"从哪来，
并指向最终修法（收敛成单一定义）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁健康）。

### F30-ter 第 67 轮：**+4 的成因排除 `gbGfxDriverInfo`，并发现是两处 +4（类总共 +8）**
用"把 `sizeof` 当位移写进数组下标"的探针（`void p(char* p){ p[sizeof(T)]=1; }` → 反汇编直接读出数值）实测：
| 类型 | 实测 | 纸面/注释 |
|---|---|---|
| `gbGfxDriverInfo` | **0xB8** | 0xB8 ✓ **一致 ⇒ 不是它胖** |
| **`gbGfxManager`** | **0x5F8** | 0x5F0 ⇒ **+8** |
| `gbColorFlt` | 0x10 | — |
| `gbViewPort` | 0x18 | — |
| `gbMatrix4` | 0x40 | — |

而成员位移探针（`g->pMatrixStack[2]` → `[ecx+0xE0]`，`g->pSceneGraph` → `[ecx+0x1C4]`）说明
**`pMatrixStack` 起点是 0xD8（纸面 0xD4，+4）**、`pSceneGraph` 0x1C4（纸面 0x1C0，+4）。
⇒ **不是"某结构体整体胖 4"，而是类内至少两处各 +4（总计 +8）**：
第一处出现在 `hGfxWnd`(0x08) 与 `pMatrixStack` 之间（该区间只有 `DrvInfo`，而它实测 0xB8 正常）
⇒ **下一个测量**：用同一探针逐个读 `pVertPoolMgr/pEffectMgr/pTexResMgr/pFontMgr/pMatrixStack[0]` 的位移，
定位**第一个 +4 从哪个成员开始**（若 `pVertPoolMgr` 就是 0xC8 而非 0xC4 ⇒ 问题在 `DrvInfo` 的**起始偏移**，
即 `hGfxWnd` 之后多出 4 字节 —— 那更像是**有两个 vptr**或基类子对象）。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁健康）。

### F30-bis 第 66 轮：两份 `gbGfxManager` **结构完全不同**（ODR 冲突确认）；sizeof 测量未出结果
用 python（避开行尾坑）取出两处类体并对比：
* `include/gbengine/gbGfxManager.h:103` —— **真定义**：`m_nState / hGfxWnd / DrvInfo(0xB8) / 4 个指针 /
  pMatrixStack[4] / 3×gbMatrix4 / … / _pad5EC[4]`，逐成员都带 `// +0x…` 偏移注释，纸面 `sizeof=0x5F0`。
* `include/gbengine_api.h:63` —— **同类名的另一份定义，但只有方法原型**（
  `virtual __thiscall gbGfxManager::~gbGfxManager(void);` … 一串 `gbGfxManager::` 限定名声明），**没有任何数据成员**。
⇒ **ODR 冲突确认**：若某个 TU 先见到 API 那份，`gbGfxManager` 就只剩 vptr（4 字节），偏移会**完全错**（不是只差 +4）。
⇒ 因此 +4 的成因**另有其人**（很可能仍在 `DrvInfo` 链上的某个结构体，或 `gbMatrix4/gbColorFlt/gbViewPort` 等被重复定义而尺寸不同）。
**本轮未完成的测量**：写了一个 `sizeof(gbGfxDriverInfo)` / `sizeof(gbGfxManager)` 探针（用 `struct S{char c[sizeof(T)];}` 的符号长度读尺寸），
**未产生输出**（编译或符号解析问题，未打印错误）。下一轮先把这个探针调通（**打印编译错误**），一次就能确定是哪个结构体胖了 4。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁健康）。

### F30 第 65 轮：`gbGfxManager` +4 的**头号嫌疑：类定义重复（ODR）**
复核对 `UIProgressBar::Render`（814B/594 差异，最大单函数）与 9 个 partial unit 的诊断——
"`gbGfxManager` 编译布局整体 +4（纸面 `pMatrixStack@0xD4`、实际 `0xD8`）"。本轮排查：
1. `gbGfxManager.h:106-113` 纸面算术**正确**：`DrvInfo` 0xB8 @0x0C ⇒ `pMatrixStack@0xD4`。实际 +4 ⇒ 某成员胖 4。
2. **`gbGfxDriverInfo` 有两份定义**：`include/gbengine/gbGfxManager.h:80` 与 `include/pal3_structs.h:343`；
   逐成员比对**结构完全相同**（10×int + `char winname[0x80]` + u32×2 + int×2 = 0xB8）⇒ **不是** +4 的来源（但仍是 ODR 卫生问题）。
3. **`class gbGfxManager` 也出现两处**：`include/gbengine/gbGfxManager.h:103` **与 `include/gbengine_api.h:63`**
   （Select-String 行号）⇒ **同一个类有两份定义**，谁先被包含谁生效 ⇒ **这正是"+4 只在部分 TU 出现"的机制**。
   下一轮：用 **python**（不要用 `Get-Content`，见下）读 `gbengine_api.h` 里那份的成员表，与 `gbGfxManager.h` 逐项 diff，
   找出多出的 4 字节成员，然后**收敛成单一定义**（保留与二进制一致的那份，另一份删掉或改为 `#include`）。
**工具坑（本轮再次踩到，与 F28 同族）**：`Get-Content` 与 `Select-String` 对**同一文件的行号不一致** ——
说明这些头文件里混有**孤立 CR / CRLF 混排**；`Get-Content` 按 `\r\n` 切、`Select-String` 按 `\n` 切。
⇒ 读这些文件**一律用 python**（`open(...,encoding='utf-8')` 会把 CR/CRLF 都归一成 `\n`）。
**本轮净结果**：无生成物改动；把 +4 的排查从"某结构体胖"收敛到"**整个类的 ODR 重复**"，并给出下轮一步到位的做法。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F29 第 64 轮：`_nearby_53f4c0` 去幻影形参**已落地**（结果中性，但纠正了 IDA 原型）
- 事实校正：`functions.json` 里该条目的**实际文本**是
  `{"name": "CScreenMode::_nearby_53f4c0", "class": "CScreenMode", "signature": "_DWORD *__thiscall(_DWORD *)"}` ——
  `class` 字段已提供隐式 `this`，签名里那一个 `_DWORD *` 就是**幻影形参**（二进制是 `ret` 无立即数 = 0 栈参）。
  （我第 53 轮是从 decomp 的 signature 推断的，文本形态不同；第 64 轮先搜错文本导致空操作，随后按实际文本改对。）
- 改动：`_DWORD *__thiscall(_DWORD *)` → `_DWORD *__thiscall()`（一行）。
- 同谱系 A/B（check → apply → export → codegen → probe → match）：S2 **73/201**、`new_failures` **0**、
  **L1 32（不变）** ⇒ **中性**。符合复核结论："这类成员表/原型修正属正确性收益，字节收益接近零"。
  预期副作用（未单独测量）：`TextureLib::ClearGlobalVars`（原 n_diff=17）应少一条 `push`。
- **待办**：本条的 `CHANGE_LOG.md` 条目尚未补（下轮补），因为本轮预算耗尽。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**。

### F28 ★★ 第 63 轮：**退化根因确认并修复 → 状态恢复 73/0/32**
**根因（GBK 续行坑）**：`include/pal3/ida_defs.h` 第 98–103 行是 2026-09-15 加的中文注释块，
其中某行的**末字符在 GBK 编码下的次字节是 `0x5C`（`\`）** ⇒ **MSVC 6 的行拼接（line splicing）把下一行并进该行**，
而该行是 `//` 注释 ⇒ **第 104 行的 `__forceinline float _pal3_coerce_f32(...)` 定义被整行吞掉**
（第 105 行的 `_f64` 无恙，与"只缺 `_f32`、只报一处 C2065"完全吻合）。
`pipeline/gen/ast_transform.py:930` 会把 `COERCE_FLOAT` 改写成 `_pal3_coerce_f32(...)`，
于是所有用到该形态的 TU 都编不过 —— 本次是 `UI3DCtrl.cpp:384/389`。

**辨别关键（第 63 轮的决定性一步）**：`grep _pal3_coerce_f32 pal3/src/Misc/UI3DCtrl.cpp` → **2 处，且都是使用点**（384/389）。
⇒ 第 61 轮"`.i` 里出现 2 次 = 定义+使用，故定义存在"的反证**基于错误假设，予以撤回**；
第 59 轮"定义未被发射"的判断**是对的**。（本会话第 5 次结论校正。）

**修复**：给该注释块 6 行各补一个 **ASCII 空格**（让末字节不再是 0x5C）—— 纯机械、不改语义、不改中文内容。
**同谱系 A/B**：S2 **72 → 73/201**、`new_failures` **1 → 0**、**L1 30 → 32** ⇒ **完全恢复到已验证好状态**。

**通用教训（本项目高危坑，建议进 `docs/knowledge/`）**：源码是中文注释 + MSVC 6 按 GBK 读盘，
**凡 `//` 注释行末字符的 GBK 次字节为 `0x5C`，下一行必被吞**。
规避：中文注释行末尾**统一补一个 ASCII 空格**（或句末用 ASCII 标点）。本次的触发点很可能是我第 55 轮
用 python 重写该文件时把 CRLF 改成 LF，改变了行末字节序列，从而把一个"潜伏的坑"激活。
**当前状态**：S2 **73/201** · `new_failures` **0** · **L1 32**（门禁恢复）⇒ 下轮可继续队列。

### F27-septies 第 62 轮：**务实恢复失败**（状态稳定在 72/1/30），并给出两条下轮路线
- 复测：`UI3DCtrl.cpp:384` 仍是 `v11 = _pal3_coerce_f32(GetTickCount());`，直接 `/c` 编译仍报 **C2065**（非陈旧数据）。
- 尝试**重跑 `apply` → `export` → `codegen all`** 以回到变化前谱系：**失败** —— 仍是 S2 **72/201**、
  `new_failures` **1**、**L1 30**。⇒ 该退化**不是**一次 export 漂移，而是**稳定复现**的编译问题。
- 已知事实汇总：helper 定义在 `ida_defs.h:104`（无条件、文件文本正常）；**真实 TU 的预处理输出里
  `_pal3_coerce_f32` 出现 2 次**（定义+使用）；同一 TU 编译却报 C2065。
  ⇒ 这是"预处理可见、编译不可见"的**矛盾**，最可能是**编译调用方式/预处理与编译条件不一致**（例如
  `/P` 与 `/c` 走的宏分支不同），这正是下轮要证伪的点。
**下轮两条路线（取其一，均比继续读头文件更快）**：
1. **定位矛盾**：把 `/P` 的输出固定落到已知路径（上次落在仓库根），在 `.i` 里用 `#line 384` 反查使用点，
   打印其前后各 40 行；再对同一 TU 用**与探针完全相同的 flags** 跑一次 `/c`，对比两者是否真的同源。
2. **绕过（在管线自己的控制面内，更可能一举解决）**：该调用是 codegen 对 `COERCE_FLOAT(rvalue)` 形态的产物
   —— 让 codegen **不要**生成 `_pal3_coerce_f32(...)`，改为生成**临时量 + `COERCE_FLOAT(tmp)`**（等价且不依赖该 helper）。
   这样既修 UI3DCtrl.cpp，又去掉对该 helper 的依赖（该 helper 的存在本身就是为了补这个形态）。
**当前状态（仍未恢复）**：S2 **72/201** · `new_failures` **1** · **L1 30**；好状态 73/0/32。

### F27-sexies 第 61 轮：**"定义缺失"被否** —— 真实 TU 的预处理输出里 helper 出现 **2 次**
把预处理结果**落盘**后复查（不再依赖 `run_cl` 的 stdout）：
| 文件 | 字节 | `_pal3_coerce_f32` 次数 | 搜 `return *(float *)&v;` |
|---|---|---|---|
| `A_only_ida_defs.i`（最小 TU） | 2,673,157 | 1 | -1 |
| **`UI3DCtrl.i`（真实 TU）** | 2,936,501 | **2** | -1 |

⇒ **对真实 TU，`_pal3_coerce_f32` 在预处理输出里出现两次**（定义 + 使用都在）
⇒ **"头文件里的定义没被保留"这一假设被否**（前两轮的采集假象/`#line` 推断都不成立）。
`defbody = -1` 两种文件都一样，说明只是**字面间距/归一化**差异，不能作为"定义缺失"的证据。

**因此问题回到**：定义在 `.i` 里明明可见，编译器却在 `UI3DCtrl.cpp:384` 报 C2065。
下一轮应改看**使用点所在的上下文**而不是头文件：
① 打印 `pal3/src/Misc/UI3DCtrl.cpp` 第 384 行所属函数的完整签名与 `#line` 映射，
   确认该行是否落在某个 `extern "C"`/嵌套作用域/被 `#if` 包裹的区块里；
② 直接对 `UI3DCtrl.cpp` 用 `/E` 并**在落盘的 `.i` 里定位第 384 行对应位置**（用 `#line 384` 反查），
   看那一刻 `_pal3_coerce_f32` 的声明是否已在作用域内；
③ 若 `.i` 里可见却仍报错 ⇒ 怀疑**探针/编译器的调用方式**（如 `/TP` 与文件被当 C 处理、或多 TU 串扰），
   可用"把该 TU 单独手工编译一次"复核。
**当前状态（仍未恢复，最高优先）**：S2 **72/201** · `new_failures` **1** · **L1 30**；好状态 73/0/32。

### F27-quinquies 第 60 轮：**撤回上一轮的"整段跳过"结论**，改为怀疑 `run_cl` 的 stdout 捕获
- 实测 `#line` 序列对 `ida_defs.h` 只有 `… 16..24, 33, 37, 63, **180**`（共 23 处）。
  我上一轮据此判定"64–179 行被跳过"——**这是错的**：MSVC 只在需要**重同步**时才发 `#line`，不是每行都发。
  反证：输出尾部明明有 `mfp_cast`（该模板位于 `ida_defs.h` **173–179 行**）却没带自己的 `#line` 标记。
  ⇒ **撤回"整段丢弃"结论**（该文件 55–72、174–182 行的原文都是正常内容：`#pragma warning`、`#define`、
  `__forceinline` helper、模板 `mfp_cast`、`#ifndef None`）。
- 仍然成立的事实：`_pal3_coerce_f32` 在 2,329,883 字节的 `/E` 输出里**只出现 1 次**，而定义体
  `return *(float *)&v;` **搜不到**；同一 TU 编译报 C2065。
- **新的（当前最强）假设**：**`pc.run_cl` 对 2.3MB 量级 stdout 的捕获有损/截断**（例如只保留头尾或中间丢块），
  于是"定义缺失"可能是**采集假象**而非编译事实。
- **下一轮一步到位**：不要再用 `run_cl` 的返回值判断，改为**把预处理结果落盘**再查：
  ① `cd %TEMP% && cl /E /TP <src> > pp.i`（真实重定向）；
  ② 在 `pp.i` 里 `grep -c _pal3_coerce_f32` 与 `grep -n "return \*(float \*)&v;"`；
  ③ 若文件里定义**存在** ⇒ 采集假象，则回到"为什么 C2065"；若**不存在** ⇒ 才回到条件编译方向，
  并用"在被怀疑区间前后各插一个独有标识符"的方式二分定位（而不是靠 `#line` 推断）。
**当前状态（仍未恢复，最高优先）**：S2 **72/201** · `new_failures` **1**（`UI3DCtrl.cpp` C2065）· **L1 30**；好状态 73/0/32。

### F27-quater 第 59 轮：**精确定位** —— 定义体未进预处理输出（`#line` 证据）
实测（`cl /E`，最小 TU = `#include "pal3/ida_defs.h"` + 使用该 helper）：
* 预处理输出 2,329,883 字节；`_pal3_coerce_f32` **只出现 1 次**；搜定义体 `return *(float *)&v;` **未命中（-1）**；
* 输出尾部的 `#line` 序列暴露了发射顺序：
  ```
  ... template <typename F, typename M> inline F mfp_cast(M mfp) {...}
  #line 180 "D:\workspace\PAL3Decomp\include\pal3/ida_defs.h"
  #line 2   "C:\Users\Slaye\AppData\Local\Temp\A_only_ida_defs.cpp"
  float f(unsigned long v){ return _pal3_coerce_f32(v); }        ← 唯一那 1 次 = **使用点**
  ```
  ⇒ 预处理在 **ida_defs.h 第 180 行** 之后直接跳到 .cpp；而第 **104/105 行**的
  `__forceinline float _pal3_coerce_f32/_f64` **没有出现在输出里**。
* 结合前几轮的否定结果（无块注释、无孤立 CR、无反斜杠续行、无 include 致命错误），
  结论收敛为：**该定义所在区域在预处理阶段被整段丢弃**（最可能是某个条件编译/宏分支；
  注意 `#line 180` 说明 180 行之后的内容是正常发射的）。
**下一轮一步到位的验证**：把 `cl /E` 的输出**落盘成 `.i`**，然后
① `grep -n '#line .*ida_defs'` 列出所有涉及该头文件的 `#line` —— 直接读出"哪些行区间被发射/被跳过"；
② 打印 `#line 180` 之前 200 行的原文，看定义区是被吞掉、被宏替换，还是被 `#if` 分支排除。
**当前状态（仍未恢复，最高优先）**：S2 **72/201** · `new_failures` **1**（`UI3DCtrl.cpp` C2065）· **L1 30**；好状态 73/0/32。

### F27-ter 第 58 轮：三个假设被否，问题定位到**预处理后的定义缺失**（仍未修复）
逐个否掉（都是实测，避免下一轮重复）：
- **块注释**：`/*`/`*/` 计数 0/0 —— 否；
- **孤立 CR 行尾**：CRLF 0 / lone CR 0 / LF 184（纯 LF），行尾规范化写入内容与原文完全相同 —— 否；
- **注释行尾反斜杠续行**：全文**0 行**以 `\` 结尾 —— 否；
- **include 链提前中止**：该 TU 编译输出 81 行里**只有 1 条 error**（就是 C2065），没有 C1083/致命错误 —— 否；
- **helper 是否根本不存在**：文件里第 104 行是无条件定义，且**单独包含 `ida_defs.h` 的最小 TU 也报 C2065**（决定性实验）
  ⇒ 与调用点/包含顺序无关，**是该定义在预处理阶段没有被保留**。
- 线索：`cl /E` 预处理输出 2.3MB，其中 `_pal3_coerce_f32` **只出现 1 次**（若定义与用法都在，应为 2 次）
  ⇒ 极可能"出现的那 1 次"是**使用点**（未声明标识符），定义那一行被某个条件/宏处理掉了。
**下一轮精确验证（一步到位）**：把 `cl /E` 的输出**落盘成 `.i` 文件**，在其中搜索
`return *(float *)&v;`（定义体）与 `_pal3_coerce_f32`，打印命中处上下各 30 行，
即可看清定义是被 `#if` 丢弃、被宏替换，还是根本没被读到。
**当前状态（仍未恢复，最高优先）**：S2 **72/201** · `new_failures` **1**（`UI3DCtrl.cpp` C2065）· **L1 30**；好状态 73/0/32。

### F27-bis 第 57 轮：两个假设被**否掉**，范围进一步收窄
- **假设 A（块注释吞掉定义）**：否 —— 文件里 `/*` 与 `*/` 计数均为 **0**。
- **假设 B（孤立 CR 行尾导致 MSVC 把定义并进上一行注释）**：否 —— 实测该文件 **CRLF 0、孤立 CR 0、LF 184**（纯 LF），
  我做了一次行尾规范化，写入内容与原文**完全相同**（6558 字节，185 行）。
  （先前 `Get-Content` 看到的"注释吞定义"确实只是 PowerShell 的显示假象。）
- **`ida_defs.h` 的结构是干净的**：只有第 1 行 `#pragma once`，**没有 include guard、没有 `#if 0`**；
  第 104/105 行的 `__forceinline float _pal3_coerce_f32/_f64` 是**无条件定义**；文件自身也 `#include "pal3/pal3_stl.h"` 等 20 个头。
- ⇒ **新的（当前最强）假设**：`ida_defs.h` 第 5–36 行的**某个 include 链在这个 TU 里提前中止/致命失败**，
  使第 104 行之后的定义根本没被处理（与本仓已知的"`gbActorMgr.h` 阻塞 2 个 cpp"现象一致）。
  **下一轮验证**：用 `cl /P`（或 `cl /E`）把 `UI3DCtrl.cpp` 预处理成 `.i` 文件，直接搜索
  `_pal3_coerce_f32` 是否存在、以及第 384 行附近上下文；同时看该 TU 的**完整**错误列表（不止 C2065 一条）。
- **当前状态（仍未恢复）**：S2 **72/201** · `new_failures` **1** · **L1 30**；好状态为 73/0/32。
  **这仍是下一轮的第一优先**（先把门禁恢复到 73/0/32，再谈新批）。

### F27 第 56 轮：退化根因**缩小到 `ida_defs.h` 的可见性**（仍未修复，状态待恢复）
- 失败单元 `pal3/src/Misc/UI3DCtrl.cpp` 的唯一错误：`C2065 '_pal3_coerce_f32' : undeclared identifier`（line 384）。
- 该 helper **确实定义在** `include/pal3/ida_defs.h:104`（`__forceinline float  _pal3_coerce_f32(unsigned long v) {...}`），
  且 UI3DCtrl.cpp 第 1 行就 `#include "pal3/ida_defs.h"`；文件里**没有任何 `/*`/`*/`**（0/0）⇒ 不是块注释吞掉。
- 尝试"补换行"无效：实测该定义行**前面本来就是换行**（我之前看到的"注释吞掉定义"是 `Get-Content | Select-Object`
  对中英混排/行尾混合的**显示假象**）。
- `/EP` 预处理该头文件只得到 110 字节且不含该定义 ⇒ **该定义对编译器不可见**（条件编译/include guard 关闭过早在起作用，
  或 `run_cl` 的 `/EP` 调用本身不适用）。**这是下一轮的第一个调查点**（用 `cl /P` 落地一个 .i 文件再查，而不是复用 run_cl）。
- **当前状态（未恢复）**：S2 **72/201** · `new_failures` **1** · **L1 30**（第 49/54 轮已验证的好状态是 73/0/32）。
  **下一轮第一优先：修 `ida_defs.h` 的可见性 → 恢复 73/0/32**，然后才继续队列。
- 时间线：该 helper 是本仓 2026-09-15 为修 `UI3DCtrl.cpp:384` 的 `C2102`（对 rvalue 取地址）而加的，
  文件内注释明确写了这一点 ⇒ **它曾经有效**；如今不可见，说明该头文件在之后被改坏过（或在某种编译条件下被跳过）。

### F26 第 55 轮：`HIBYTE` 修正**已回滚**，但暴露出一处**未解释的状态退化**（必须在下一轮先解决）
**动作**：把 `include/pal3/ida_defs.h:44` 按复核建议改成 `#define HIBYTE(x) (*(((_BYTE*)&(x))+(sizeof(x)-1)))`（201 处用法）。
**A/B 结果**：S2 73 → **72/201**、`new_failures` **1**（`pal3/src/Misc/UI3DCtrl.cpp`）、**L1 32 → 30** ⇒ 触发硬门禁。
**已立即回滚**（该行恢复为 `+1` 版本，`git status` 显示该文件仍为 M 但仅为行尾归一）。

**⚠ 关键发现（回滚后复验）**：回滚并重新 codegen + probe + match 后，读数**仍是 72/201、new_failures 1、L1 30**
⇒ **`UI3DCtrl.cpp` 的失败与 HIBYTE 改动无关**（否则回滚应恢复到 73/0/32）。
即：**在第 54 轮结束时的已验证好状态（73/0/32）与第 55 轮首次 probe 之间，树发生了另一处退化**，
最可能是第 54 轮那次 `apply + export` 循环改变了 IDB/导出谱系（同谱系读数漂移），也可能与 `ida_defs.h`
被写为 LF 行尾有关（不影响编译，但 `git status` 报 M）。
**下一轮第一件事（优先于任何新批）**：
1. 抓 `UI3DCtrl.cpp` 的**具体错误**（`data/status/_ab_probe_after.json` 或重跑 probe 打印 errors），
   判断是注解/IDB 谱系问题还是真实代码问题；
2. 目标：把状态恢复为 **73/201、new_failures 0、L1 32**（第 49/54 轮已验证过的读数）；
3. 恢复后用 `L1 ≥ 32` 作为门禁基线，再继续队列。
**本轮净结果**：无新增收益，**不可留下退化状态**（记住规则：门禁不满足就必须恢复到上一已验证状态）。

### F25 第 54 轮：整类混淆调查的**颠覆性结论**（子 agent db264eb8）——混淆是真的，但**不是那 14 个 partial 的成因**
**关键机制**：IDA 结构体与生成的 C++ 头**同源于同一份注解**，Hex-Rays 会把每个原始偏移解析成"注解在该偏移放的成员"
⇒ **整体 −0x14 位移只是把成员改了名，位移量不变**。实测：`UIProgressBar::Render`(814B) 的**所有 `esi` 位移与二进制逐一相同**；
`FindChildByName`/`Destroy` 同理。⇒ **改归属/偏移是正确性与文档收益，不是字节收益。** 我此前把它列为"最大可测批次"是**判断错误**。

**报告给出的真实字节收益排序（均为实测）**：
1. **`gbGfxManager` 的编译布局整体 +4** —— 影响 `UIProgressBar::Render`（814B/594 差异，当前最大单函数）**及 9 个 partial unit**。
   原函数读 `[eax+0xD4]/[eax+0xD8]/[eax+0x1C0]`，我们读 `[eax+0xD8]/[eax+0xDC]/[eax+0x1C4]`，并因此把错的 gfxMgr 槽当 `pSceneGraph`
   （`[ebx+0x4DF9]` vs 原 `[ebx+0x4B2C]`）。而 `include/gbengine/gbGfxManager.h:103-134` **纸上算出来的偏移是对的**
   （`pMatrixStack@0xD4`、`pSceneGraph@0x1C0`）⇒ 有**别的东西胖了 4 字节**（疑似 `gbGfxDriverInfo` 被展开或 `DrvInfo` 前多了一个成员）。
2. **`HIBYTE` 宏语义错** —— `include/pal3/ida_defs.h:44` 硬编码 `+1`：
   `#define HIBYTE(x) (*(((_BYTE*)&(x))+1))`。Hex-Rays 的 `HIBYTE` 指**该操作数自身类型的最高字节**
   （`__int16` → +1；4 字节指针 `m_lightobj@0x120` → **+3**）。实测 `UI3DCtrl::UpdateOscillationX`
   编译出 `mov al,[ecx+0x121]`，二进制是 `[ecx+0x123]`。修法（零风险、通用、grade A）：
   `#define HIBYTE(x) (*(((_BYTE*)&(x))+(sizeof(x)-1)))`；**落地前须先扫 201 处 `HIBYTE` 用法的操作数宽度**
   （`sizeof==1` 或 `==8` 的需要显式处理）。`HIWORD`/`HIDWORD` 已经是类型化指针算术，本来就对。
3. **`0.0` vs `0.0f` 字面量**：`FindChildByName` 发 `fcomp qword ptr [0.0]`，MSVC 发 `fcomp dword ptr [0x56A644]`。
4. **TU 划分/内联**（架构性）：我们的 `.cpp` 让 MSVC 把 `UpdateRotation/UpdateOscillation*` 内联进 `UpdateTransform`
   （`m_scaley` 我们出现 7 次、原函数 0 次）⇒ 该函数**结构上无法 L1**。
5. `0x439030` 上的 `type:skip` 让它只能是个 stub。

**`UpdateOscillation*` 四兄弟并非同一根因**：三个位移全对、只差 FPU/分支形态（`fabs(v) >= x` 的写法差异），
只有 `UpdateOscillationX` 是真错（HIBYTE）。

**第 54 轮我自己的动作与结果（透明记录）**：尝试落地"候选② `_nearby_53f4c0` 去幻影形参"的一行修正，
**因 PowerShell heredoc 转义问题 python 报 SyntaxError，编辑未写入**（文件未改动）；随后跑的完整链得到
S2 73/201、`new_failures` 0、**L1 32**（= 未改动状态），即该候选**仍未落地**。tree 干净、无未验证改动。
**门禁基线更新**：以后判据用 **L1 ≥ 32**（不是 >31）。

**新队列（按报告的实测收益重排）**：① `HIBYTE` 宏修正（零风险、通用）；② `gbGfxManager` +4 的根因定位
（影响 814B 的最大函数 + 9 个 unit）；③ `0.0f` 字面量；④ `_nearby_53f4c0` 去幻影形参（已确认，一行）；
⑤ 整类重映射（正确性/文档收益，非字节；若要做得按报告的分阶段：先 S1 成员表、最后才是 S3 地址/vtable）。

### F24 第 50 轮：F23 机制**可成批**——用特征扫出 5 个同类候选（工具批）
F23（0x00445FA0 成员化）落地后，用它的**字节特征**在最新 `s4_diff_explain.json`（187 partial）里扫
"原函数以 `lea/mov ecx,<obj>` 起首、而我们不是"的站点 —— 即 **decomp 丢掉了 callee 的 `this`(ECX)** 这一族：

| 函数 | n_diff | size | 原函数首条 vs 我们 |
|---|---|---|---|
| `OpenBaseFile::OpenBaseFile` | 9 | 25 | `mov ecx,[0x56a598…]` vs `mov {R}` |
| `TextureLib::ClearGlobalVars` | 17 | 89 | `mov ecx,0x1894b78` vs `push ecx` |
| `UINote::CallVtableMethod` | 22 | 22 | `mov ecx,[ecx+0x…]` vs `fld …[esp+4]` |
| `ExternalStatistics::CheckKeyPress` | 51 | 83 | `lea ecx,[eax+0xbfad70]` vs `mov {R}` |
| `C2DSpark::CreateSingle` | 76 | 83 | `lea ecx,[ebx+0x29]` vs `mov dl,[ebx+…]` |

**共 5 个（n_diff ≤ 12 的高把握 1 个）**，且这 5 个所在的 unit（`OpenBaseFile/TextureLib/UINote/
ExternalStatistics/C2DSpark`）**当前都是编译通过的** ⇒ 立即可测。
**注意形态比 F23 更宽**：前两条的 `this` 是**全局对象地址**（`0x56a598`、`0x1894b78`），
即"全局对象的成员函数被调用时，Hex-Rays 丢了 `mov ecx,<global>`"——与 F23 同源（原型层缺 `__thiscall`/成员归属），
修法应同样是**把对应 callee 从自由函数表移入其所属类的 `methods`**。下一批先做 n_diff 最小的两条，
逐条 A/B（`new_failures` 必须保持 0、L1 > 32）。
**本轮无生成物改动**；门禁维持：`new_failures` 0 · S2 73/201 · **L1 32/219** · partial 187。

### F23-ter 第 46 轮：`sub_445FA0` 是 **UIWnd 的成员**，`UIMap+0x48` 是一个 **UIWnd 派生的子窗口子对象**
反汇编 `0x445FA0` 本体（前 22 条，A 级）：
```
00445FA0  mov edx, [esp+4]        ; 形参 = 调用方传的 &UIMap[+0x10]
00445FA5  lea eax, [ecx+0x10]     ; this+0x10
00445FA8  mov esi, [edx]  / mov [eax], esi       ;
00445FAC  mov esi, [edx+4]/ mov [eax+4], esi     ; 把 16 字节（tagRECT）从实参**拷进 this+0x10**
00445FB2  mov esi, [edx+8]/ mov [eax+8], esi     ;
00445FB9  mov edx, [edx+0xc]/ mov [eax+0xc], edx ;
00445FBC  test ecx, ecx / je ...
00445FC3  mov eax, [ecx]                          ; ← this 的 **vptr**
00445FC5  push 0 / push 0 / push 0x3fe            ; 0x3FE = 1022
00445FCE  call dword ptr [eax+0x18]               ; ← **vtable 槽 6**，三参 (1022,0,0)
00445FD1  ret 4
```
三条独立事实锁定归属：
1. `this+0x10` 被写入一个 16 字节 `tagRECT` ⇒ 与 `UIWnd::m_rect @+0x10`（tagRECT，16 字节）**逐字节吻合**；
2. `call [vptr+0x18]` = **槽 6**，参数 `(1022, 0, 0)` ⇒ 与既有结论
   "**UIWnd 槽 6 = `0x00445D10` = `CGameData::OnMessage(int,int,int)`**"、以及调用点自己的
   `if (nVal == 1022)` **完全一致**；
3. 调用点 `lea ecx,[esi+0x48]` 把 UIMap+0x48 当 `this` 传入 ⇒ **+0x48 是 UIWnd 派生的子窗口子对象**，
   而注解写的是 `int m_screenWidth`（类型标错）。
⇒ 语义即"把本对象的矩形拷给子窗口并通知它 OnMessage(1022,0,0)"。
**修法（形式已定，下一批）**：把 `0x00445FA0` 从 `functions.json` 移入 **`UIWnd.json` 的 `methods`**
（`__thiscall`，形参 `const tagRECT&`/`tagRECT*`），并把 `UIMap` 的 +0x48 改成该子窗口类型。
**第 48 轮纠偏（阻止一次错误改动）**：路线 (c) 的**后半截不能做**。
把 `UIMap+0x48` 从 `int` 改成 `UIWnd`（68 字节）子对象会**与既有成员冲突**：
注解在 `0x4C/0x50/0x54/0x58/0x5C/0x60` 已有 `m_screenHeight/m_xMapNum/m_yMapNum/m_MapNum/m_pSubMap/m_moveSpeed`
—— 一个 68 字节子对象占据 `0x48..0x8C` 会与它们**全部重叠**，生成头必然错乱。⇒ **类型不改**。

**安全的那半截（下批落地）**：只把 `0x00445FA0` 从 `data/annotations/functions.json`（自由函数）
**移入 `UIWnd.json` 的 `methods`**，签名按反汇编是 `void __thiscall(tagRECT *)`（非虚、`ret 4`），
名字用仓库既有约定 `_todo_445FA0`。这样 `UIMap::OnMessage` 的 decomp 会渲染成
`((UIWnd *)&this->m_screenWidth)->UIWnd::_todo_445FA0(&this->m_rect)` 一类形态 ⇒ **ECX 重新出现**，
编译后即 `lea ecx,[esi+0x48]` + `lea eax,[esi+0x10]` + `call` —— 与二进制一致，**且不改任何成员布局**。
**必须先测的爆炸半径**：早期审计记录 `sub_445FA0` 有 **17 个调用点**（`char*`→`void*` 类），
改成 `__thiscall` 后这 17 处的渲染都会变 ⇒ 下一批先只做这**一个**改动并跑全链，
判据 `new_failures` 保持 0（若那 17 处引入新失败则回滚，改为更小的局部方案）。
**第 47 轮尝试记录（避免重复劳动）**：`asm/pal3/decomp/` 里**没有** `UIMap::UIMap*` 条目（ctor 查不到），
所以"从 ctor 读 +0x48 的 vptr"这条路走不通。可行的替代路线（下轮用其一）：
(a) 反汇编 `UIMap` 的同族方法里所有 `lea ecx,[reg+0x48]` 调用点，看被调函数的 vtable 槽用法；
(b) 直接扫 `UIMap` 所在 TU 的构造序列（若 ctor 名带 `_todo_`/`sub_` 前缀，用地址扫描 `mov dword ptr [reg+0x48], imm`）；
(c) 从运行期语义反推：该子对象被调用的槽 6 = OnMessage(1022,0,0)，与 `UIWnd` 一致，
    因此**先按"UIWnd 派生"处理**（把 `UIWnd` 作为类型）也能让调用点重新出现 ECX——**但类型精确到基类即可**，
    因为生成物只需要 `__thiscall` 的接收者，不需要子类特有成员。
**本轮无生成物改动**；门禁维持：`new_failures` 0 · S2 73/201 · **L1 31/219** · partial 188。

### F23-bis 第 45 轮：`sub_445FA0` 的**注册位置**就是丢 ECX 的直接原因（已定位到具体文件）
* `0x00445FA0` **不在任何类的 `methods` 里**，而是登记在 `data/annotations/functions.json`（自由函数签名表）
  ⇒ IDA 按自由函数建原型 ⇒ Hex-Rays 渲染成 `sub_445FA0(&x)`，**ECX(`this`) 的半个调用自然丢失**。
  这解释了为什么"生成物与 decomp 完全一致、却与二进制差 4 字节"。
* `UIMap.json` 的 `+0x48` 是 `m_screenWidth`（`int`，`source: annotation`）；而二进制在 +0x48 上取地址当 `this`
  ⇒ 该偏移是**子对象**，类型标错。
* `data/annotations/structs/_SUBMAP.json` 存在（`UIMap` 另有 `_SUBMAP * m_pSubMap @+0x5C`）——**但 +0x48 是否就是
  `_SUBMAP` 尚不能定**（若 +0x48 是 `_SUBMAP` 子对象，则 +0x5C 的 `_SUBMAP*` 语义可疑）。
  ⇒ 下一轮必须先定 +0x48 的真实类（该类的 ctor/vtable/其余成员访问），**定了才动注解**（规则：禁止猜测）。
* 修法形式已明确：把 `0x00445FA0` 从 `functions.json` **移入该类的 `methods`**（并给正确的 `__thiscall` 签名），
  同时把 `UIMap` 的 +0x48 成员改成该子对象类型；两处必须同批。
**本轮无生成物改动**；门禁维持：`new_failures` 0 · S2 73/201 · **L1 31/219** · partial 188。

### F23 第 44 轮：`UIMap::OnMessage` 定性完成 —— **Hex-Rays 丢掉了 callee 的 ECX(`this`)，且 +0x48 是子对象不是 int**
反汇编 `0x4420C0`（UIMap::OnMessage，51 字节）前 11 条：
```
004420C6  8B F1              mov esi, ecx              ; esi = this
004420C8  81 FF FE 03 00 00  cmp edi, 0x3fe           ; nVal == 1022
004420D0  8D 46 10           lea eax, [esi + 0x10]     ; ← 第一个**栈实参**
004420D3  8D 4E 48           lea ecx, [esi + 0x48]     ; ← 第二个实参进了 **ECX** = callee 的 this
004420D6  50                 push eax
004420D7  E8 C4 3E 00 00     call 0x445fa0
```
⇒ `sub_445FA0` 是 **`__thiscall` 成员函数**：`this = &[esi+0x48]`，唯一栈实参 `&[esi+0x10]`。
而我们的 decomp/生成物只有 `sub_445FA0(&this->m_screenWidth);` —— **ECX 的那半个调用被 Hex-Rays 丢掉了**
（等价于把成员调用渲染成了自由函数调用）。所以 51 字节里差的那 4 字节是"少了一条 `lea ecx,[esi+0x48]` 语义"，
**不是成员表位移**。

**更重要的附带结论**：能对 `&[esi+0x48]` 调成员函数 ⇒ **+0x48 处是一个类子对象，而不是 `int m_screenWidth`**。
即 `UIMap.json` 在该偏移的类型标注错了（把子对象标成了 int）。这与复核在 `UIProgressBar`/`UIButton`
发现的"整类混淆/成员类型错"同型，但**证据链独立且更硬**（一条 `lea ecx,[imm]` 直接证明子对象）。

**修法（下一批）**：① 在注解里把 `0x00445FA0` 标成**某个类的成员**（该类即 +0x48 子对象的类型），
② `UIMap` 的 +0x48 成员改为该子对象类型（而非 `int`）。两者需一起做，且要先从二进制确定 +0x48 子对象的真实类
（其 ctor/vtable/其他成员访问），否则仍是猜测。
**本轮无生成物改动**；门禁维持：`new_failures` 0 · S2 73/201 · **L1 31/219** · partial 188。

### F22 第 42 轮：调整器 thunk 的**爆炸半径 = 1**（工具批，已落地）
给 `tools/byte_diff_explain.py` 加了调整器 thunk 识别（原函数形态 `add ecx,<imm>` 紧跟 `jmp/call`），
单独成桶并写入 `s4_diff_explain.json` 的 `adjustor_thunk` 字段。实测 188 个 partial 里：

**只有 1 个** —— `UICaption::DestroyPanel`（`add ecx, 0x60`，8 字节，n_diff=4）。

⇒ 候选②（调整器 thunk 发射规则）**不构成一批**（最多 +1 L1），应折进更大的重映射批，不值得单独开工。
分桶变化：`opcode/flow` 70 → **69**（那 1 个被单列出来），其余不变。
**本轮无生成物改动**（工具类），门禁状态维持：`new_failures` 0 · S2 73/201 · **L1 31/219** · partial 188。

### F21 第 41 轮：`UIMap::OnMessage` 的 +0x38 —— **不是简单的成员偏移错，须先定真值**
事实（三侧对照）：
* 生成物：`if (nVal == 1022) sub_445FA0(&this->m_screenWidth);`，`UIMap.h:12` 里 `m_screenWidth // +0x48`；
* decomp 与生成物一致（`sub_445FA0(&this->m_screenWidth)`）——**注解/反编译/生成物三者自洽**；
* **二进制却是 `lea eax,[esi+0x10]`**（解释器首分歧，且之前的指令都匹配 ⇒ 序言里 `esi` 就是 `this`）。
⇒ 二进制用的是 **+0x10**，而 +0x10 落在**基类 `UIWnd` 的子对象内部**（`UIWnd::m_rect @+0x10`，`UIWnd` 68 字节）。
所以这不是"成员表整体位移"（那种是 F18，成因在头文件 gap），而更像下面三者之一：
(a) `m_screenWidth` 的注解偏移本身错（0x48 → 0x10，但那样它就与基类成员重叠）；
(b) **该函数并不属于 `UIMap`**（`esi` 是另一个类的对象）——与复核发现的 `UIProgressBar`/`UIButton`
    两处**整类混淆**同型；
(c) `sub_445FA0` 的参数语义不是"某成员地址"（例如它是 `char*` 形参，见早期 C2664 审计里
    `sub_445FA0 (17 处 char*→void*)`），`&m_screenWidth` 只是 IDA 的猜法。
**结论**：**不落地**（缺证据就改注解＝猜测，违项目规则）。下一轮先取真值：反汇编 0x4420C0 全文、
确认 `sub_445FA0` 的目标与实参语义、核对 `UIMap` 的 ctor/vtable（ctor 写入的 vfptr 与基类初始化）
以判定 UIMap 的真实基类与成员表；若判为整类混淆，则按 F18-quater 的方式整类重映射。
**本轮无生成物改动**，门禁状态维持：`new_failures` 0 · S2 73/201 · **L1 31/219** · partial 188。

### F20-bis ★ 第 39 轮：thunk 尾跳批**已落地并验证：L1 28 → 31（+3）**
改动：`pipeline/gen/stages/transform.py` 新增 stage6 `_thunk_keep_tailjump()`，在 `run_transforms` 末尾调用
（唯一入口，不动 emit_cpp 调用点）。判据三条：
1. `// attributes: thunk` 出现在 `code` **前 4 行内**（实测标记**不在第一行**——前面常有 `// 0x004EC480`
   这类地址注释；首版写成 `lstrip().startswith(...)` 导致 stage6 **完全空转**，靠 A/B 的 "L1 未变" 暴露）；
2. **非 ctor/dtor**（`ctx.is_ctor/is_dtor`；dtor thunk 加 pragma 反而多出基类 dtor + EH 帧）；
3. 大括号之间**恰好一条**以 `;` 结尾的语句（首版误把**函数签名行**当语句 ⇒ 门恒不通过；改为按 `{`/`}` 取体）。
满足则把函数定义用 `#pragma inline_depth(0)` … `#pragma inline_depth()` 夹住。

**同谱系 A/B**：S2 73/201（不变）· `new_failures` **0** ✅ · **L1 24→28→31** · partial 191 → **188**。
新增三个 L1 与复核预测**逐一吻合**：`Parent_Data::_CheckKeyWord`、`Parent_Data::GetSize`、
`ObjectCamera::GetCameraDirect`。ctor thunk（`ObjectCamera::ObjectCamera`）被门正确排除。

**本会话 L1 轨迹**：21 → 22（+0 占位/vfptr）→ 24（S2 增益带来的比对面扩大）→ 28（F18 基类重复计数）
→ **31**（F20 thunk 尾跳）。**剩余 thunk**：82 个里 74 个在 24 个失败 unit 中（编译好了才可测），
且 **20 个签名与目标硬不符**（须先做注解批，其中 4 个是虚函数，需独立评估对 vtable 布局的影响）。

### F20 第 38 轮：thunk 族的**已验证修法**（子 agent 1dd9a1ab，实验可复现）
**结论**：MSVC 6 **确实**会做尾调用优化 —— `void C::f(){ this->C::T(); }` 与 `int C::f(){ return C::T(); }`
都编译成**恰好 5 字节 `E9 00 00 00 00`**。所以**我们现有的发射形态本来就是对的**（`return` 形式对 void 反而
编译失败 C2562）。真正的阻塞是 **`/Ob2` 把 callee 在同一个 TU 里内联掉了**。

**已验证的修法**：把 thunk 的函数定义用 **`#pragma inline_depth(0)` … `#pragma inline_depth()`** 夹住
（唯一能在保留全局优化器——TCO 由它做——的同时阻止 /Ob2 内联的局部手段；`auto_inline(off)`/`inline_recursion(off)`
都无效，`optimize("g",off)` 更糟）。**必须 gate 在 `not ctx.is_ctor and not ctx.is_dtor`**：
dtor thunk（`~CCBProtectWindow`、`~UILBColumn`）加 pragma 会**变差**（多出基类 dtor 调用 + EH 帧）。

**改动点**：`// attributes: thunk` 标记在 `collect.py:138` 进来后**没有任何阶段读它**，
到 `emit_cpp.py:412-415/:466-469` 仍是 `code` 里的注释 ⇒ 在 `transform.py:42` 追加一个 stage6
（或在 `emit_cpp.py:356/:457` 的 `run_transforms` 调用处包一层），判据：
`code.lstrip().startswith('// attributes: thunk')` **且** 非 ctor/dtor **且** 函数体只有一条调用语句。
**保持 `ast_transform.py:641-642` 的 `this->Cls::M(...)` 形态不动**（接收者必须是显式 `this`）。

**爆炸半径与收益**：82 个 thunk 标记（79 个 `E9 rel32` + 3 个 `FF 25` 导入桩）；80 个进了当前生成树；
**6 个在 S2 已通过的 unit 里**（`Parent_Data.cpp`×2、`ObjectCamera.cpp`×2、`CCBProtectWindow.cpp`、
`UILBColumn.cpp`），**74 个在 24 个失败 unit 里**。今天这 6 个**没有一个**产出 E9（都是内联后的 callee 副本，
11–64 字节）。子 agent 在真实 unit 上打补丁验证：`Parent_Data::GetSize`、`Parent_Data::_CheckKeyWord`、
`ObjectCamera::GetCameraDirect` → 恰好 `E9 00 00 00 00`，rc=0 ⇒ **立即可得 +3 L1**。
**签名前提**：82 个里 **20 个签名与其目标硬不符**（jmp 直通 eax/参数 ⇒ thunk 签名必须等于目标签名），
需先做注解修正；另 8 个目标无 decomp 条目（不可核）；3 个 `FF 25` 导入桩无解。
⇒ 完整收敛上限约 +51，但**必须先修那 20 个签名**。

### F19 第 37 轮：**"thunk 体保留 dtor 调用"尝试 → 回归 → 已回滚并复验**（否定性结果，值得存档）
动机：`ObjectCamera::ObjectCamera` 的 decomp 是 `{ ~ObjectCamera(this); }`（IDA 标 `// attributes: thunk`，
二进制 5 字节 `jmp`），而 `stage3_cleanup.py:277-296` 对成员函数里的显式 ctor/dtor 调用**一律注释/删除**
⇒ 我们的函数体变空。我加了"**函数体只有这一条语句时保留**"的守卫（`parent.type=='compound_statement'
and named_child_count==1`）。

**A/B 结果（回归，立即回滚）**：
| 指标 | 改前 | 改后 |
|---|---|---|
| S2 ok | 73 | **72** |
| new failures | 0 | **1**（`UIStatic.cpp`，6× `C2521 destructors do not take parameters`） |
| **L1** | **28** | **26** |

原因：decomp 里的 dtor 调用**可能带参数**（`~X(this, 1)` 形态 = `_scalar_dtor(this,1)` 语义，即"delete this"），
原样发射即 C2521。⇒ 正确修法必须**按目标函数的真实签名**发射（或只保留无附加参数的形态），
不能只看"是不是唯一语句"。已 `git` 回滚该 hunk 并重建复验：**S2 73/201、new_failures 0、L1 28、partial 191**
（与回滚前的好状态逐项一致）。**thunk 族仍待修，但必须带签名一致性判据。**

### F18-quater 独立复核对 F18 的纠正与新增线索（子 agent 8d485ced）
* **独立验证**：用仓库自带 CL.EXE 对当前头文件编译，四个函数与二进制**逐字节相同**
  （`GetWidth db 44 24 04 d9 99 8c 00 00 00 c2 04 00` == 0x43FDC0 等）；
  `sizeof(UIProgressBar)` 从 308 → **244**，**恰好等于 PDB 的 `0xf4`** ⇒ 旧值 308 本身是 bug 产物；
  `SceneMapPlayer::ClearName` 的 0x10 也是同一 bug；**121/122 个派生类头文件受影响**。
* **F18 代码质量问题（下批修）**：① F18 在 codegen 里直读 `data/annotations/`，违反"codegen 不读 annotation"；
  ② 我加的 `binary_size` 回退是**死代码**（`ida_structs.json` 1028 个条目里 0 个有该键）；
  ③ 正解：用 `ida_structs.json` 的 `bases[]`（176 个 struct 都有）+ `size(name)` 推导 `base_size`。
* **更大的误归属（A 级证据已备，待整类重映射）**：
  `UIProgressBar.json` 里的 `0x439030(ctor)/0x439410(Render)/0x439810(Destroy)/0x439A20(CheckRayHitRole)`
  **不属于 UIProgressBar**：其 ctor 写 `[esi+0x44]=0` + 在 `+0x48` 构造 `5×0x20` 数组 + `m_speed=98@0xf4`
  + `m_camera@0x124`（Destroy 里 operator delete），类大小恰 `0x134=308`，且 ctor 调用点间距 0x134
  ⇒ 与 PDB 的 **UI3DCtrl**（`pdb.xml:34519`，`UI3DObj` 长 0x20 @`:34563`）吻合；
  而 `UIButton.json` 反而持有 UIProgressBar 的 ctor/vtable（`0x43F7F0`/`0x56AD64`）。
  另：注解的成员名映射整体偏 **−0x14**（PDB `UIProgressBar length=0xf4`：`m_IsGetit@0xa0`、`m_bkColor@0xa4`、
  `m_foColor@0xa8`…），**但绝不能零散搬名**——那会弄坏刚拿到 L1 的三条 getter；必须**整类重映射**并全链验证。

### F18-ter 第 36 轮：**F18 家族已收敛**（并纠正上一轮的一处误判）
上一轮我把"47 个仍有 gap 的真实基类头文件"说成"同一 bug 的下一批"——**错了**。按 gap 起点分类后：
* **gap 起点 < `base_size`（吃进基类区 = 真 bug）：0 个**；
* gap 起点 ≥ `base_size`（合法类内空隙，稀疏注解本来就有洞）：47 个（`CCBRoleState` gap@0x6F8 size 5892、
  `UITitle` gap@0x48 size 3216、`SaleUI` gap@0x348 size 320 …）。
⇒ **F18 这条机制桶收敛**：142 → 0 个实例，判据是"首个 gap 的起点是否小于 base_size"。

**同轮用新数据重排（`s4_diff_explain.json`，191 个 partial）**：
| cause | F18 前 | F18 后 |
|---|---|---|
| `opcode/flow differs` | 73 | **73** |
| `register choice differs` | 47 | 47 |
| `operand shape differs` | 27 | 28 |
| `immediate/const differs` | 21 | 23 |
| **`this/member disp differs`** | **27** | **20** ↓（F18 的直接贡献） |

**新的最接近 L1 清单（前 5）**：
| 函数 | n_diff | 首个分歧 |
|---|---|---|
| `AStarPathFinder::FindInOpen/FindInClosed` | 1 | `mov eax,[ecx+…]` vs `[eax+…]`（this 落在不同寄存器） |
| `SceneMgr::ClearInactiveRoles` | 1 | `call 0xfffff1f0` vs `call {R}`（调用目标/重定位未记录） |
| `TextureLib::SetPath` | 2 | `mov ebp,[0x56a028]` vs `mov {R}` |
| `Parent_Data::GetSize` / `_CheckKeyWord` | 2 / 4 | 原函数 5 字节 `jmp`，我们发了 callee 的副本 —— **同 TU 内联**（F17） |
| `ObjectCamera::ObjectCamera` | 5 | 原函数 `jmp ~ObjectCamera`，我们发了**空函数体**（调用被丢弃） |

⇒ 下一批候选（按当前数据）：① `opcode/flow` 73 里的 **同 TU 内联/尾跳**子族（F17 已诊断，结构性）；
② `ObjectCamera::ObjectCamera` 式 **codegen 丢调用**（小、确定）；③ 调整器 thunk `add ecx,N`（`UICaption::DestroyPanel`）。

### F18-bis ★ **F18 已落地并验证：L1 24 → 28（+4），且四个新 L1 全是预测中的**
改动（`pipeline/gen/stages/emit_headers.py`，两处，均为"基类/vptr 与成员起点"的记账修正）：
1. `base_size` 从导出数据取不到（<8）时，回退到注解 JSON 的 `base_size`，再回退到基类自身的
   `binary_size`（`base_class` 列表求和/取大）；
2. **有真实生成基类时不发射 +0 占位**（vfptr 由基类子对象提供）。

**同谱系 A/B（codegen → invariants → probe → match；tracked 基线已还原、ratchet 未推进）**：
| 指标 | 改前 | 改后 |
|---|---|---|
| 含假 gap 的"真实基类"头文件 | **142** | **47** |
| `UIProgressBar.h` 首个成员 | `char _gap_004[64] // +0x4` | **`int m_mode; // +0x44`**（假 gap 消失） |
| S2 ok | 73/201 | 73/201 |
| new failures | 0 | **0** |
| **L1** | **24** | **28** |
| partial | 195 | **191** |

**新增的 4 个 L1 与预测逐一对上**：`UIProgressBar::GetWidth/GetHeight/GetPosition`（三条 getter）
+ `SceneMapPlayer::ClearName`（原以为的"codegen 多加 0x10"其实也是同一个基类记账 bug）。
⇒ 之前所有"注解偏移错"的猜测全部作废，真因是基类子对象被重复计数。

**剩余**：仍有 **47** 个"真实基类 + 首个 gap ≥ 8"的头文件（基类是模板/gbengine 类型、
或基类 `binary_size` 缺失，回退链仍未解出），是同一 bug 的下一批；另有
`CCBRoleState : public SceneObj` 这类极端 gap（7676 字节）。

### F18 ★★ 第 34 轮：**基类子对象被重复计数 ⇒ 142 个子类的成员布局整体偏移**（目前发现的最大系统性缺陷）
追查 `UIProgressBar` 三条 getter 的 1 字节差异时，链条收敛到一个**通用**缺陷：

1. **生成物与二进制其实一致**：我们的源码写的是
   `*(float *)&this->m_IsGetit = (float)nWidth;`，注解里 `m_IsGetit` 在 **0x8C**，而二进制指令正是
   `fstp dword ptr [ecx + 0x8c]` —— 注释层面完全对得上。
2. **但编译出来的偏移是 0xCC**（`s4_diff_explain.json` 长期显示 ours=`[ecx+0xcc]`），差 **0x40 = 64**。
3. 差值的来源在头文件里：`pal3/src/Misc/UIProgressBar.h:12-14`
   ```cpp
   class UIProgressBar : public UIWnd {      // 基类 UIWnd 是**真实 C++ 基类**，编译后占 0x44 字节
       char _gap_004[64]; // +0x4            // ← 又多补了 64 字节
       int m_mode; // +0x44                  // 注解偏移是**绝对值**（已含基类）
   ```
   编译器先放 UIWnd 子对象（0x44），**再**放这 64 字节 gap ⇒ 其后每个成员实际偏移 = 注解值 + 64。
   实测印证：`m_IsGetit` 注解 0x8C、编译后 0xCC（0x8C+0x40）。**同一个 bug 也解释了 `FindInOpen` 之外
   大批 `this/member disp differs`（27 个）与 `register choice`（47 个）partial。**
4. **影响面（实测）**：**142 个头文件**同时存在「真实 `public` 基类」与「首个 `_gap_*` ≥ 8 字节」：
   `CCBControlWindow : public UIFrameWnd` + `_gap_004[68]`、`CCBProtectWindow` 同、
   `CCBItemWindow`/`CCBParabolaWindow`/`CCBResultWindow`/`CCBSkillWindow` 同（+68）、
   `CCBAIWindow : public UIFrameWnd` + `_gap_000[72]`、`CCBLineupWindow`/`CCBMagicWindow` 同（+72）、
   极端例 **`CCBRoleState : public SceneObj` + `_gap_000[7676]`**（该类所有成员偏 7676 字节）。
5. **修法（明确、无需 IDB）**：`emit_headers` 计算首个成员起点时，对有**真实生成基类**的类，
   `start_off` 必须取**基类编译后的实际大小**（注解的 `base_size`，UIWnd=68），而注解偏移是绝对值、
   **不应再补 gap**。当前显然是把基类当成"只有 vptr（4 字节）"来算 gap，于是**重复计数**。
   注意与第 1 条修复（有 virtual 时不发 +0 占位）是同一族问题：都属"基类/vptr 与成员起点"的记账。
6. **验收**：同谱系 A/B（codegen → invariants → probe → match），判据 `new_failures` 保持 0、
   **L1 必须明显高于 24**（仅 `UIProgressBar` 三条 getter 就应回到 L1，预期 24 → ≥27），
   且 `s4_diff_explain.json` 里 `this/member disp differs` 桶应显著下降。
   **这是下一轮的第一批**（此前若干"注解偏移"猜测全部应废弃——真因在基类记账）。

### F17 第 33 轮：thunk 批的**决定性实验**（结论是否定性的，但把批次拆成了真成因）
**实验**（`%TEMP%\thunk_probe2.py`，用仓库自带 `CL.EXE` + 项目同款 flags `/O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MD /Gd`，
callee **只声明不定义**以模拟分 TU 编译；首版把 callee 定义在同一 TU，被常量折叠污染，已废弃）：
| 形态 | 产物 |
|---|---|
| `void C::B(){ A(); }` | **`E9 rel32`（5 字节尾跳）** |
| `void C::B(){ this->C::A(); }` | **`E9 rel32`** |
| `void C::B(){ ((C*)this)->C::A(); }` | **`E9 rel32`** |
| `int C::B2(){ return A2(); }` | **`E9 rel32`** |
| `void C::B(){ return A(); }` | **编译失败**（MSVC 6 不接受 void 函数 return void 表达式） |
⇒ **我们当前的发射形态（末句调用）本来就是对的，不需要改 codegen。** 这否掉了 thunk 批的天真版本。

**那 5 个低残余 thunk 函数的真实成因各不相同（逐个看 decomp + 生成物）**：
| 函数 | 真实成因 |
|---|---|
| `Parent_Data::GetSize`（5B） | callee `Parent_Data::spstr` **就定义在同一个 .cpp 的紧后面** ⇒ 被 MSVC 内联，我们的函数体变成 spstr 的副本（解释器显示 ours=`mov {R}`）——**同 TU 内联**，不是发射形态问题 |
| `Parent_Data::_CheckKeyWord`（5B） | 同上（`_CheckStr` 同 TU），我们发的是 `return this->_CheckStr();` |
| `ObjectCamera::ObjectCamera`（5B） | 我们发射了**空函数体**——decomp 里的 `ObjectCamera::~ObjectCamera(this);` 调用被**丢掉了**（codegen drop） |
| `UICaption::DestroyPanel`（8B） | 原函数是**调整器 thunk**（`add ecx,0x60; jmp`），decomp 里 `this` 已消失（`{ UICaption_Destroy2(); }`），我们发了不带 ecx 调整的直接调用 |
| `TextureLib::ClearAndJump`（10B） | decomp 含 `JUMPOUT(0x53F570)`（IDA 不可解析跳转），我们原样发射 |

**⇒ 新机制（也是复核 C 独立指出的第一大population 成因）：同 TU 内联 / TU 划分**。
`// attributes: thunk` 的 82 个条目里，凡是"原函数是 5 字节 `jmp`、而 callee 被我们放进同一个 .cpp"的，
都会被内联成真实函数体 ⇒ 永不可能 L1。**原工程的 TU 划分与我们的生成划分不同**，
这些 thunk 正是"两者之间曾经跨 TU"的**二进制证据**（原编译器没能内联 ⇒ 它们当时不在同一 TU）。
⇒ 下批方向：用这 82 个 thunk 反推"必须拆开的 TU 对"，或对这类 callee 加内联屏障。

### F16 工具批（第 32 轮）：不变量 D 口径修正 → 80 个假阳性收敛到 **10 个真问题**
`tools/codegen_invariants.py` 的 D 判据原为"注解有 vtables ⇒ 生成头 +0x0 必须是显式 vptr/占位"。
第 1 条修复（有 virtual 的类不再发射占位，因为编译器自己提供 vfptr）之后，这条判据把 80 个类
全报成 FAIL —— **假的**。现改为「显式 vptr/占位」**∨**「声明了 virtual」二者之一成立即通过。

修正后 D 报 **10 个**，全是真问题，其中 **4 个是新暴露的**：
`CCBLineupWindow`/`MainPropUI`/`RoleStatePanel`/`TaskBookUI` —— 有 vtable 注解却只发射
`_gap_000[72]/[96]` 且**没有任何 virtual**（vtable 没被建模）；另 5 个缺生成头（`CPK`/`filebuf`/
`gbGfxManager`/`gbLightObj`/`gbTexture`），`scScriptInstance` 无 virtual 也无占位。
A（131 行/25 文件）、B（55 处）不变。**本轮数据无变化**（工具类改动不影响生成物）：
S2 **73/201**、new_failures **0**、机制桶不变（C2664 93 unit / C2660 72 / vftable 残留 39）。

### F15 **ROI-1 工具直接发现的新机制：thunk 发射错误**（第 31 轮，来自 `s4_diff_explain.json`）
* 事实：`asm/pal3/decomp/` 里有 **82 个条目**带 IDA 标记 `// attributes: thunk`，其反编译体就是
  **一条对目标函数的调用**（例：`PalScript::Cleanup` → `PalScript::FreeLoadBuffer(this);`），
  且 `size_bytes` 多为 **5**（即二进制是 5 字节 `E9 rel32` 尾跳）。标记还活着进了生成产物（81 处）。
* 我们当前发射的是 **`this->PalScript::FreeLoadBuffer();` + `}`**（`call` + `ret`），
  与 5 字节 `jmp` 不等价 ⇒ 这类函数**不可能 L1**。低残余清单里已见 5 个
  （`Parent_Data::GetSize/_CheckKeyWord`、`ObjectCamera::ObjectCamera/GetCameraDirect`、`UICaption::DestroyPanel`），
  但全量是 **82 个函数**——这是目前发现的最大单一批量字节轴目标（若全中，L1 24 → 100+）。
* 待定（必须先测，不能猜）：**哪种源码形态能让 MSVC 6 /O2 发射 `E9 rel32`**。
  候选：`return <call>;`（尾调用；void→void 合法）、纯粹把调用作为最后一条语句、
  以及函数返回类型与 callee 不一致时（decomp 里出现 `int result; … return result;`，
  而二进制是裸跳转 ⇒ 该 thunk 的真实签名应与 callee 一致，属**注解/签名问题**）。
  已派子 agent 用仓库自带 `CL.EXE /O2` 做对照实验并给出精确改动点与爆炸半径。

### F14 **ROI-1 落地：partial 首次可解释**（195 个函数，含原因分布与"最接近 L1"清单）
改动（都只增不改判据）：
* `tools/gbengine_compare.py` `compare_bytes()` 现在**返回** `diffs`/`reloc_diffs`/`first_diff`
  （原先算完就丢——这就是"没有任何工具能解释 partial"的根因）；
* `pipeline/compare_pal3.py`：每个 partial 记 `obj`/`compiled_len`/`n_diff`/`first_diff`/`diffs[:64]`，
  写入**新文件** `data/status/s4_diff_detail.json`（ratchet 的 `s4_baseline.json`/`pal3_registry.jsonl`
  形状不变）；`.obj` 名从内建 `hash()` 改为 `hashlib.md5`（跨进程稳定，可复用产物）；
* 新工具 `tools/byte_diff_explain.py`：capstone 双侧反汇编（**两侧同基址**，否则分支目标会假阳性）+
  重定位操作数归一 `{R}` + difflib 指令对齐 ⇒ 首个分歧点与原因分类，输出 `data/status/s4_diff_explain.json`。

**195 个 partial 的原因分布（首次实测）**：
`opcode/flow differs` 73（37%）· `register choice differs` 47（24%）· `this/member disp differs` 27（14%）·
`operand shape differs` 27（14%）· `immediate/const differs` 21（11%）。

**最接近 L1 的清单（n_diff 升序，前 7 个只差 1 字节）**：
| 函数 | n_diff | 首个分歧（原函数 vs 我们） |
|---|---|---|
| `UIProgressBar::GetWidth` | 1 | `fstp [ecx+0x8c]` vs `[ecx+0xcc]`（**+0x40**） |
| `UIProgressBar::GetHeight` | 1 | `fstp [ecx+0x90]` vs `[ecx+0xd0]`（**+0x40**） |
| `UIProgressBar::GetPosition` | 1 | `fstp [ecx+0x94]` vs `[ecx+0xd4]`（**+0x40**） |
| `SceneMapPlayer::ClearName` | 1 | `lea edi,[edx+0x105]` vs `[edx+0x115]`（**+0x10**） |
| `AStarPathFinder::FindInOpen/FindInClosed` | 1 | `mov eax,[ecx+…]` vs `[eax+…]`（this 落在不同寄存器） |
| `SceneMgr::ClearInactiveRoles` | 1 | `call 0xfffff1f0` vs `call {R}`（未记录的重定位/目标不同） |
| 其余 n_diff≤5 | 2-5 | `Parent_Data::GetSize/_CheckKeyWord`、`ObjectCamera::ObjectCamera/GetCameraDirect`、`UICaption::DestroyPanel` —— **原函数是 5 字节 `jmp` thunk，我们发射了完整函数体** |

⇒ **ROI-2 的第一个具体目标**：`UIProgressBar` 三条 getter 共享同一个 +0x40 偏移错误
⇒ **一条注解修正换来 3 个 L1**；再加 `SceneMapPlayer::ClearName` 的 +0x10 ⇒ 4 个 L1（相对 L1 提升 ~17%）。
证据是逐字节的（`fstp [ecx+0x90]` vs `[ecx+0xd0]`），符合 A 级门槛。
**ROI-3**：thunk 发射规则（原函数体只有一条 `jmp` 时必须发 thunk），覆盖清单里的 5 个 + `opcode/flow` 桶里的同类。

**同轮 L1 顺带提升**：`match` 报 **L1 24**（matche 24/219）—— 因为 S2 从 70 涨到 73，更多 unit 进入比对。

### F13 **已落盘并验证（第 3 条：注解级）—— `new_failures` 首次归零**
`0x004B59B0` 补录为 `TextureLibDataBase::sub_4B59B0`（`__thiscall`，4 栈参），
证据与验证全文见 `data/annotations/CHANGE_LOG.md` 同日条目。要点：
* 根因是**同一个 ECX 值被 IDA 猜了两次**（callee 侧 `float *this`、caller 侧 `(char *)this`），两侧都无注解；
* A 级证据：`mov esi,ecx`（__thiscall）+ `ret 0x10`（恰 4 栈参）+ 成员访问命中 `+0x244 = m_fScrollSpeed`
  （该类唯一有二进制证据的成员，584B 类内不越界），而 `ScreenEffect` 注解只有 24B；
* **不是子对象偏移错**：`Apply` 的 13 个分支形状逐字节相同，`esi` 只在入口设一次、**无任何 `lea ecx,[esi+K]`**；
* 结果（含 apply + export 的同谱系 A/B）：S2 **70 → 73/201**、**new_failures 3 → 0**、FIXED 5、
  matched 222/256、**L1 22（不回退）**；爆炸半径 1 条注解 / 1 个调用点。

**本轮暴露的三个工具债（都不影响上面的结论，但必须记账）**：
1. `tools/annotation_diff.py` **跑不起来**：`❌ GIT 不可读 —— 898 file(s) are tracked at HEAD but their content
   could not be read (first: ARC_ArcBrief.json)`。CLAUDE.md 规定"apply 后必须跑 annotation diff"，
   这个强制检查点当前**形同失效**。本次改用"调用点文本 + probe + match"三重独立确认代替。
2. `codegen_invariants.py` 检查 **D 的口径因第 1 条改动而失真**：从 24 个类变成 **80 个类**报
   "+0x0 不是 vptr"。这是**预期副作用**——我的修复正是让有 virtual 的类不再发射显式 vptr（由编译器提供），
   而 D 只认"头文件里显式的 vptr/占位"。**D 需要升级为"显式占位 ∨ 类声明了 virtual"二者之一成立即通过**，
   否则它会长期报假阳性，掩盖真正的 24 类问题。
3. `python pipeline/cli.py codegen all` 内置的后置步骤报 `compile_regression.py exited 1`
   并提示 `--update-baseline`——这是因为本机读数（73/201、5 fixed）优于**发布基线**。
   按项目规则**不得从本机推进 tracked 基线**，故保持不动。

### F12 **已落盘并验证的收益（第 2 条：stub 路径两处通用缺陷）**
`pipeline/gen/stages/stage3_cleanup.py` 两处修改，都是"把文档化的设计意图补齐"，无 narrowing：

1. **`_sanitize_stub_sig()`（新增）**：stub 签名清洗。实测 `pal3/src/Combat/CCBUI.cpp:554/584` 发射的是
   `static virtual int pal3_vtbl_unk_…(void *, UIFrameWnd *this, void *Block, char a3)`
   —— `virtual` 与 `static` 不能并用、`this` 不能作形参名，**两者都是硬语法错误**（C2059/C2143），
   只可能来自反编译文本/cast 的转写。同时用于 `_vtbl_stub_name()` 的哈希（保证名字与清洗后签名一致）。
2. **未解析裸链的通用 stub 兜底**：`visit()` 里原来对"无 cast 信息"的裸链 `RECV->__vftable->NAME(args)`
   直接 `repl = None`（= 保留文本）⇒ `__vftable` 残留 ⇒ C2039/C2227（21 文件 / 135 活代码站点）。
   而本函数上方注释明确写着设计意图是"unresolved calls are rewritten to synthesized stubs"。
   现在：**仅当调用处于语句位置**（`node.parent.type == 'expression_statement'`，即返回值未被使用）时，
   补一个通用可变参数 stub `static void pal3_vtbl_unk_va(...)`，调用点发射 `pal3_vtbl_unk_va(RECV, args)`。
   签名无关 ⇒ 必然可编译。

**同谱系 A/B（codegen → probe → match；tracked 基线已还原、ratchet 未推进）**：

| 指标 | 本轮开始 | 第 1 条后 | **第 2 条后** |
|---|---|---|---|
| S2 ok | 70/201 | 70/201 | **72/201** |
| new failures | 3 | 3 | **1**（只剩 `ScreenEffect.cpp`） |
| fixed | 5 | 5 | 5 |
| **L1** | 21 | **22** | **22**（不回退） |

⇒ **`UIProgressBar.cpp` 与 `UIStatic.cpp` 两个自伤回归被清掉**，`new_failures` 3 → 1；
硬线（L1 不回退）满足；`AStarPathFinder::FindInOpen/FindInClosed` 保持 97.1%。
测试集无新增失败（仍是 HEAD 上那 6 个红的：`6 failed / 38 passed`）。

**必须记下的代价（诚实标注）**：第 2 条是**编译轴**收益，L1 一点没涨（22 → 22）。
这些站点现在编译成"调用一个本地空 stub"，与二进制里的间接分发**不等价** ⇒ 那些函数仍是 partial。
真正让它们字节忠实的仍是"按二进制槽号发射虚调用"（第 3 条），而它压着注解级阻塞（见 F11 末段）。
唯一剩下的新失败 `ScreenEffect.cpp`（`sub_4B59B0` 实参/形参不符）属 IDB 谱系问题（`_baseline_repro` §11），
要判定 `4B5570/4B5830/4B59B0/4B5BB0` 家族的真身再补注解。

### F11 **已落盘并验证的收益（第 1 条：+0 占位与 vfptr 冲突）**
子 agent（复核 D）实测：56 个生成头同时有 `void * __vftable;` **和** virtual 方法，而 MSVC 6 **不会**
把这个成员当作编译器 vfptr —— 它自己在 +0 放 vfptr，把显式占位挤到 +4 ⇒ **其后每个成员偏 4 字节**。
判据函数：`AStarPathFinder::FindInOpen` 只差 2/34 字节（`8B 49 08` vs `8B 49 04`），
**与 registry 记录的 94.1% 完全吻合**。

**改动**（`pipeline/gen/stages/emit_headers.py`，函数返回前加一段后处理）：
类一旦声明了 virtual 方法，就删掉 +0 的 4 字节占位（`void * __vftable;` 或 `char _gap_000[4];`）——
vfptr 由编译器在 +0 隐式提供，占位反而把成员顶偏。占位当初是为让 `.cpp` 里残留的
`X->__vftable` 能编译；那些站点本来就产不出字节忠实的代码，按"字节匹配 > 编译通过"取舍。

**同谱系 A/B（完整链：codegen → probe → match，tracked 基线已还原、未推进 ratchet）**：

| 指标 | 改前 | 改后 |
|---|---|---|
| 含 `void * __vftable;` 的头文件 | 56 | **0** |
| S2 ok | 70/201 | **70/201**（不变） |
| new / fixed | 3 / 5 | **3 / 5**（不变） |
| **L1** | **21**（10.8%） | **22（11.3%）** |
| `AStarPathFinder::FindInOpen` | 94.1% | **97.1%** |
| `AStarPathFinder::FindInClosed` | 94.1% | **97.1%** |

⇒ 硬线（new_failures 不增、L1 不回退）全部满足，且 L1 +1。**残余 1 字节**是寄存器选择字节（复核 D 已指出）。
副作用（已知、非新增失败）：`UIProgressBar.cpp`/`UIStatic.cpp` 的错误由 `C2227` 变成
`C2227 + C2039 '__vftable' is not a member of 'UIWnd'` —— 因为占位没了；这两个文件在 P1(a) 之前
本来就是失败的，所以 new_failures 不变。**它们真正的修法**是第 2 条：按二进制槽号发射虚调用
（`UIWnd::OnMessage` 需要显式 `virtual` 且落在槽 6），届时既编译又字节忠实。
另需注意：那条路还压着一个**注解级**阻塞 —— 调用点把 `this->m_id`（现注解为 `void *`）
传进 `OnMessage(int,int,int)` 的第 2 参 ⇒ C2664；而 0x00445D10 的函数体是 `33 C0 C2 0C 00`
（`xor eax,eax; ret 0Ch` = 3 个栈 dword），说明**原源码里 `m_id` 必须是整型**（C++ 不允许 void*→int 隐式转换）。

### F9 子 agent 复核之三：partial 的**逐字节**归因（已收到）
复核者自己在 %TEMP% 里用仓库自带模块重跑了 S4，**逐数字复现**：symbols 256 / matched 222 / unmatched 34 /
synth 28 / compared 194 / **L1 21 / partial 173**。**同时给出数据完整性告警**：
`data/status/s4_baseline.json`（13:22:12）里是 **L1 18 / partial 182 / 200 行 / symbols 262 / matched 228**
—— 那是**发布基线**（ratchet 的"恢复上一版"路径写回旧 blob），**不能当本机的 L1 真值引用**。
这与本会话一直坚持的"只有同谱系 A/B 有效"一致。

**它测到的总体信号（全部 173 个，名字无关、字节级）**：
* **首个差异字节就在 0-1 偏移的：85 个；0-7 以内：137 个（79%）** ⇒ 79% 的 partial 在**序言就已经错**，后面全被顶偏。
* 指令对齐后平均命中率仅 **36–39%**；最小编辑距离 **1**。
* 缺 C++ EH 帧（`64 A1 00 00 00 00` 系）**23 个**；`??0` 构造调用多余 **35 个**；调用计数不一致 **55 个**；
  三者并集 **84/173（49%）** ⇒ "本地方对象 / EH / 内联结构错了"。
* `this` 相对位移集合不同的 **111/173（64%）**。
* 编译出的 COMDAT 段比原函数**短**的 **57 个**（其中 45 个短 >16B，最多 −410B）⇒ 真的少代码。
* **残余差异 ≤12 字节的 30 个（17%），≤2 字节的 6 个** —— 这 6 个是最接近 L1 的。
* 手查 14 个函数的原因分布：(a) 偏移/布局/类型 5、(b) 归属/虚性/thunk 4、(f) codegen 等价变换 3、(g) decomp 层 2。
  三个"只差一个字节"的实例：`lea edi,[edx+0x105]` vs `[0x115]`、`7C`(jl) vs `72`(jb)、`[ecx+4]` vs `[ecx+8]`。

**它给出的"缺失工具"规格（这是本轮最有价值的一条）**：真正的逐函数 diff 距现有代码只有 3 行——
`tools/gbengine_compare.py:283` 的 `compare_bytes()` **算出了 `diffs`/`reloc_diffs` 却不返回**；
`pipeline/compare_pal3.py:397` 还把编译结果**静默截断**到原函数长度（长度不符永远看不见），
行里只留 `{file,symbol,name,va,status,match_pct,size}`，**丢掉全部差异偏移**。
⇒ 补 ~4 行（返回 diff）+ ~15 行（行里记 `n_diff/first_diff/compiled_len`）+ 2 行（`hash()`→`hashlib` 稳定命名）
+ 新工具 `tools/byte_diff_explain.py`（~150-200 行，capstone 已装且仓库未用），输出到**新**文件
`data/status/s4_diff_detail.json` 以免动 ratchet 文件。

**预期收益（它自己标为中等置信）**：①本地方对象/EH/内联 15-30 个 partial→L1；②`this` 位移/大小/符号性 8-15；
③归属/虚性/thunk 3-8。

### F10 **HEAD 上就有 6 个测试是红的**（我实测，与本次改动无关）
`python -m pytest pipeline/gen/test_pipeline.py -q` → **6 failed / 38 passed**；
把 `stage3_cleanup.py`/`data.py`/`emit_headers.py` 三个文件全部 `git stash` 回 HEAD 后**仍然是同样的 6 个失败**
（`TestOopTransform::{test_complex_expr_as_first_arg,test_identifier_as_first_arg,test_inter_class_call_with_this_gate_blocked_by_arity}`、
`TestTrack1EvidenceGate::{test_both_halves_needed,test_ctor_dtor_excluded}`、`TestVftableFallback::test_qualified_vftable_left_alone`）。
⇒ 测试集**在 HEAD 上就不是绿的**，它编码的是"旧行为"（例如断言限定式 `this->GlowObj::__vftable` 必须原样保留，
而现行代码已把它折成 `(*(void **)(this))`）。**任何"跑测试当门禁"的做法当前都不可用**，
要么把测试更新到现行语义，要么把这些行为改回去——这是一项独立的、必须先决的工程债。

### F4 工具缺陷（顺带发现）
* `error_classifier.py` 的优先级把"codegen 发射的非法文本"归入 `hexrays_limit`（F1）。
* `codegen_invariants.py` 缺一条"header `virtual` 集合/顺序 vs 注解 vtable 槽"的检查（F3）。

## 7. 进度日志（按时间倒序，只记"已实测"的结论）

### 2026-09-19 · **基线统计（当前树 = 含 P1(a) 与 P1(b) 通用修法）**

| 轴 | 值 |
|---|---|
| S1 | 730/751 ok |
| S2 | **70/201**，总错误 **2432** |
| 对发布基线 | 新失败 **3**（`ScreenEffect.cpp` / `UIProgressBar.cpp` / `UIStatic.cpp`）· 已修复 **4** |
| S4 字节匹配 | matched **222/256** · **L1 21** · partial **173** · unmatched **34** · synth **28** ⇒ L1 仅占 21/194 ≈ **11%** |
| 不变量 | **D 24 类** · **A 147 行/29 文件** · **B 55 处** · C（潜伏，默认不计） |
| 错误分类（131 失败文件） | **hexrays_limit 57（43.5%）** · annotation_fix 40（30.5%）· codegen_fix 25（19.1%）· manual_idb 2 · unknown 7 |

**复盘结论（用于定方向）**：
1. **hexrays_limit 已占 43.5%** ⇒ 光靠修编译错误，S2 的理论天花板 ≈ 70+65 = **135/201**，而且这是**另一条轴**——它不自动带来字节匹配；
2. **本轮的"不变量下降"没换来文件级收益**（D 80→24、A 150→147、错误 −28，`new_failures` 不变）⇒ 不变量与文件级收益**非线性**；要文件级收益，P1 必须补完三步 plumbing；
3. **字节匹配的存量在 173 个 partial + 34 unmatched + 28 synth**，而"partial 为什么不是 L1"**目前没有任何工具能回答**（`match` 只给百分比）⇒ 这是最大且最未被测量的存量。


### 2026-09-19 · P1 第一刀（已落地并验证，**门禁中性**）
* **改动**：`emit_headers.py` 成员循环前补发射 `void * __vftable; // +0x0`
  —— 条件"该类有 vtable 槽 **且** 首个成员不在 +0"（**加性**：填掉原 gap，尺寸不变）。
* **实测**：
  * **D：80 → 24**（56 个类的头已有 vptr；实验三类 `AStarPathFinder`/`CCBPanelSlot`/`CEffModel` 均出现该成员）
  * **总错误 2460 → 2432**（−28）
  * **L1 21 守住**、matched 222/256 不变、`new_failures` 3 不变（**中性**）
  * `UIProgressBar.cpp` / `UIStatic.cpp`：**8 → 4 条**，且 **C2039 `'__vftable' is not a member of 'UIWnd'` 全部消失** ✓
* **未达出口**（出口要求 D=0 且 A=0）：剩余 **C2227 `left of '->OnMessage' must point to class/struct/union`**
  —— 因为 vptr 现在是 `void *`，`obj->__vftable->OnMessage(...)` 变成 `void*->OnMessage(...)`。
  ⇒ **P1 必须做两半**：**(a) 发射 vptr（已完成）** + **(b) 把裸链/cast 链重写成可编译的调用形态**（即
  `_baseline_repro` §14 的 `((Owner *)RECV)->Owner::NAME(...)`，先例 `free_functions.cpp:5798`）。
  另需把 (a) 覆盖到**剩余 24 个类**（其中 `CCBStage` 连 gap 都没有，走的是另一条发射分支）。
* **顺带修掉工具的一个假阳性**：A 把**头里的声明行** `void * __vftable;` 也算成违规
  （P1 一改，A 从 150 涨到 206，全是假阳性）⇒ 已加 `DECL_VFT` 跳过；A 回到 150。
  ⚠️ A 的**消息**现在过期（"生成头从不声明 `__vftable`"不再成立），且 A 仍是"文本计数"而非
  "因果判据"——要降到 0 必须解析接收者类型、只统计"接收者类确实没有 vptr"的用途。

### 2026-09-19 · P1(b) 的**确切放弃点已定位**（读代码得到，下一轮可直接动手）

`pipeline/gen/stages/stage3_cleanup.py:488-503` 的 `_resolve_vtbl_method(d)`：

```python
sv = store.struct_vtables                     # {类: {槽号: 方法名}}
if d['method']:
    if d['cls_hint'] and d['method'] in sv.get(d['cls_hint'], {}).values():
        return d['method']                    # ① 有 cls_hint 且确实是槽 ⇒ 用方法名
    owners = [c for c, slots in sv.items() if d['method'] in slots.values()]
    if len(owners) == 1:
        return d['method']                    # ② 全局唯一所有者 ⇒ 也能解析
    return None                               # ③ 否则放弃 ⇒ 原文本保留 ⇒ __vftable 残留
```

**`OnMessage` 走的就是 ③**：它是**12 个类的实现**、出现在很多类的 vtable 里 ⇒ `len(owners) > 1`，
而**形态 A（裸链）没有 cast ⇒ `cls_hint is None`** ⇒ 解析失败 ⇒ 调用文本被原样保留。

⇒ **P1(b) 的修法（两条，建议先做 1）**：
1. **给形态 A 补 `cls_hint`**：接收者的声明类型就在同一函数的 decomp 文本里
   （`UIWnd *m_pfather;`、`UIWnd *v29; // ecx`）。拿到后走分支 ① ⇒ 直接发射 `RECV->OnMessage(...)`
   （因为 **P1(a) 已让头声明了 `__vftable`**，但 `OnMessage` 仍不在 `UIWnd` 的方法表里 ⇒ 这一步还需
   发射成 `((Owner *)RECV)->Owner::NAME(...)` 形态，其中 Owner 由 `sv` 反查槽归属 —— 见 `_baseline_repro` §14）。
2. **让 stub 路径覆盖它**：第 592 行已有 `_vtbl_stub_name(...)`（`unresolved_synth=28` 就是它产出的），
   但显然没覆盖这 11 处；查清为什么漏掉，比新写一条规则更省。
* **验收**：这 11 处消失 ⇒ `UIProgressBar.cpp`/`UIStatic.cpp` 的 4+4 条 `C2227` 清零 ⇒
  `new_failures` 应从 3 降到 **1**（只剩 `ScreenEffect.cpp` 的 `sub_` 形参问题，属 P2）。

### 2026-09-19 · P1(b) **已落地的通用修法**（拒绝窄化；实测收益见下）

**改动（通用，不针对任何具体方法名）**：`stage3_cleanup.py`
1. `_decode_vtbl_call`：裸链无 cast 时 `ret`/`params` 为 `None` ⇒ 原代码在第 591 行**跳过 stub 兜底**
   导致文本原样保留。现补：用 `store.method_sigs` 里**该方法所有声明者签名一致**时的签名
   补出 `ret`/`params`，并标记 `synthetic_self`；
2. `visit()`：裸链实参里**没有对象**，而 stub 形参表把对象放首位 ⇒ 调用时把对象补回首参。

**实测收益**：**A 150 → 147**（3 处被重写）；`L1 21` 守住；`new_failures` 未变。
**为什么只 3 处**：`OnMessage` 的注解签名有 **18 种**、`ShowWindow` 有 **4 种** ⇒ "签名一致"判据
**正确地**拒用它们 —— 不能靠不可靠的注解签名硬凑（这正是拒绝窄化的理由）。

**要拿到文件级收益（`new_failures` 3→1）还差三步 plumbing（已查清，明确可做）**：
1. `data.py:_load_vtable_data`（226-259 行）：解析槽地址→方法名时**顺带记下"实现该槽的类"**
   （`struct_vtable_slot_owner[cls][slot] = Owner`）；
2. `_decode_vtbl_call`：给裸链求**接收者静态类型**（`m_pfather` 这类成员：在 `store.struct_members
   [当前类]` 里按名反查其类型；当前类可从 `ctx` 取）；
3. 发射 `((Owner *)obj)->Owner::method(args)` —— 与 `free_functions.cpp:5798` 既有形态一致。
   ⇒ 8 处 `OnMessage`（UIProgressBar×4 + UIStatic×4）即可编译 ⇒ **两个文件转 ok**。


## 8. 第 104 轮（2026-09-19 夜）：**导入符号 dllimport 机制** + JUMPOUT 尾调用 + 门禁工具修复

### F50 `g_pVFileSys` 的"丢失解引用"是**导入符号未声明 dllimport**（A 级，IDB 导入表）

**起因**：F49-bis 留下的谜题——`OpenNULLFile::OpenNULLFile` @0x00401F90 原始 11 字节
`8B 01 | 8B 0D 98A55600 | 89 01 | C3`（`mov eax,[ecx]; mov ecx,[IAT]; mov [ecx],eax; ret`）
而 Hex-Rays 输出 `g_pVFileSys = this->m_plastsys;`（少一层解引用）。

**判定（用 IDA 直接查 IDB，非推断）**：把 `original/PAL3.exe.i64` 拷到临时目录后跑只读脚本
（`%TEMP%\idaprobe\probe*.py`；不写仓库、不保存 IDB）：

| 证据 | 结果 |
|---|---|
| `0x0056A598` 所在段 | **`.idata`**，perm=read（只读 → 正是 Hex-Rays "write access to const memory" 警告的来源） |
| 该地址的名字/类型 | `?g_pVFileSys@@3PAVgbVFileSystem@@A` / `gbVFileSystem * g_pVFileSys` |
| `ida_nalt.enum_import_names` | **模块 GBENGINE，IAT 槽 0x0056A598** ✔ |
| 同一导入表里的**非函数**符号 | 共 7 个：vtable ×4（`??_7gbRefObject/gbVolumeModifier/gbNBTreeNode/gbVisNode`）、全局数据 ×2（`?g_CurrentTime@@3NA` @0x56A4F4、`?g_pVFileSys@@3PAVgbVFileSystem@@A` @0x56A598）、静态成员 ×1（`?ColorQuadFmt@gbColorQuad@@2HA` @0x56A558）；其余 242 个是函数 |

⇒ 语义正解：**0x56A598 是"变量 g_pVFileSys 的地址槽"**，PAL3.exe 不定义它，只是导入。
Hex-Rays 的 `g_pVFileSys = …` **本来就是对的**；错的是我们把它声明成普通 `extern`，
于是 MSVC 生成**直接绝对写**（`C7 05 <addr>`，5~6 字节），而原二进制用 IAT 间接形态
（`8B 0D <addr>` + 经指针写，多 1~2 字节）。**这是 codegen/头文件层的缺陷，不是注解错。**

**落地**（`GBAPI` = `include/gbengine/gbengine_export.h` 的 `__declspec(dllimport)`，与
`class GBAPI gbActorMgr` 既有用法一致）：
* `include/gbengine/gbVFileSystem.h`：加 `#include "gbengine/gbengine_export.h"`；`g_pVFileSys` → `extern GBAPI`
* `include/gbengine/gbengine_types.h`：`g_CurrentTime` → `extern GBAPI`；`static GBAPI int ColorQuadFmt`
* `include/pal3_globals.h`（镜像声明，避免同一 TU 内两种声明冲突）：`g_CurrentTime` / `g_pVFileSys` → `extern GBAPI`

**单文件字节验证**（仓库自带 CL.EXE + 与 `match` 同款 `/O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MD /Gd`）：

| 函数 | 原始 | 改动后 | 结论 |
|---|---|---|---|
| `OpenBaseFile::OpenBaseFile` @0x401F50 (25B) | `8BC1 8B0D<rel> 8B11 8910 8B0D<rel> C701<rel> C3` | **逐字节相同**（含 7 字节 align 90） | ✅ L1 |
| `OpenBaseFile::~OpenBaseFile` @0x401F70 | 同上形状，25B | 22B（MSVC 改用 `A1`/eax 装载） | 寄存器选择差异（partial） |
| `OpenNULLFile::OpenNULLFile` @0x401F90 | `8B01 8B0D<rel> 8901 C3` (11B) | 16B：先装 IAT 到 edx 再装成员 | 寄存器/求值顺序差异（partial，n_diff 4→6） |

### F51 `JUMPOUT(addr)` 还原成真尾调用（codegen-only，独立复核已闭环）

`include/pal3/ida_defs.h` 的 `#define JUMPOUT(x)` 展开为**空** ⇒ `TextureLib::ClearAndJump`
@0x0053F550（10 字节 `E8 rel32` + `E9 rel32`）被生成 33 字节（`/Ob2` 把 callee 内联 + 尾跳消失）。
落地：`pipeline/gen/stages/transform.py` 新增 `_jumpout_to_tailcall()`（在 `_thunk_keep_tailjump` 之后执行），
两道实测闸：① 目标须在 `[0x401000,0x56A000)`（挡掉 `PAL3.cpp:4042` 的 `0x2EE3E9A` 伪造 je 目标）；
② 函数体须含 ≥1 条非 JUMPOUT 语句（挡掉 `free_functions.cpp` 4 处 `align 10h` 填充里的**函数边界假函数**）。
命中**恰好 1 个函数**；`#pragma inline_depth(0)` 与 F20 同机制且实测必需。
> 代价：`codegen_invariants` 检查 B 196 → **197**（新增 `sub_53F570 声明 1 参 vs 调用 0 实参`）——
> 与既有 120 个 `int sub_X(...)` 同族，且该门禁**本来就红**；未用改名（`loc_`）掩盖，如实记录。

### F52 门禁工具修复：`probe_compile` 写 census 未指定编码 ⇒ `regression_detector` 读崩（连带修全部读者）

`probe_compile.py:253` `open(args.out,'w')` 在本机写 **GBK**，而 `tools/regression_detector.py`
按 UTF-8 读 ⇒ `UnicodeDecodeError`，**"new_failures" 门禁实际不可用**。修复：写/读都显式
`encoding='utf-8'`，并把 `UnicodeDecodeError` 纳入旧文件容错（与 `snapshots/snapshot.py` 的既有修法一致）。
**写端改编码后必须同步全部读者**（否则立刻炸——实测第二轮 `cli.py match` 直接
`[ERROR] probe census is unreadable/invalid`，即 `compare_pal3.py` 的默认编码读）：本轮一次性修了
`probe_compile.py`（写）、`compare_pal3.py:494`、`link_probe.py:106`、`tools/compile_regression.py:25`、
`tools/error_classifier.py:239`、`tests/e2e/test_smoke.py:35`；`snapshot.py`/`regression_detector.py` 本来就是 UTF-8。
（顺带核查：`compare_pal3.load_decomp_index` 用默认编码读 `asm/pal3/decomp/*.json`——实测 3597 个文件
**全部纯 ASCII**，无静默丢弃，故不动。）

> **顺序教训**：`probe_compile.py` 结尾 `shutil.rmtree(OBJ_DIR)` 会删掉 `match` 产出的 `.obj`，
> 而 `s4_diff_detail.json` 里存的是这些 obj 的路径 ⇒ **`byte_diff_explain.py` 必须在 `match` 之后、
> 下一次 `probe_compile` 之前立即运行**（本轮第一次 explain 因此得到 "(obj missing) 185"）。

### 本轮 A/B（完整管线：check → apply → export → codegen all → codegen_invariants → audit_layout → probe_compile s2 → error_classifier → compile_regression → match）

| 指标 | 前 | 后 | 门禁 |
|---|---|---|---|
| S1 | 730/751 | **0 errors, 13 warnings → PASS** | ✅ |
| S2（文件级） | 73/201 | **73/201**（14s） | ✅ |
| `new_failures`（对发布基线 20260919_000552） | 0 | **0**（两种独立算法：手写 census diff + `regression_detector --check`） | ✅ |
| **L1** | 32 | **34** | ✅ 不回退 |
| partial | 187 | 185 | ✅ |
| matched | 249/289 | 249/289 | — |
| invariants | A 131 行/25 文件 · B 196 · D 10 | A 131 行/25 文件 · B **197** · D 10 | 记录差异 |

**L1 +2 的逐函数归属（用新旧 `s4_diff_detail.json` 按符号求差，非人工声称）**：
* `+ OpenBaseFile.cpp ??0OpenBaseFile@@QAE@XZ`（n_diff 9 → L1）← F50 dllimport
* `+ TextureLib.cpp ?ClearAndJump@TextureLib@@QAEXXZ`（n_diff 2 → L1）← F51 JUMPOUT
* **新进 partial：0**（无 L1 回退）

**n_diff 变差（如实记录，均为 partial 且非 L1）**：
`UICursor::Update(double)` 278→282、`UICursor::IRender` 7→11（两者都因 `g_CurrentTime` 的 dllimport
补出了原本缺失的 `mov eax, ds:__imp_g_CurrentTime`；反汇编确认原始 22 字节为
`FF15<gbUpdateCurTime> A1<g_CurrentTime> DDD8 DD00 DD1D<dst> C3`，**我们的形态现在与原始前 3 条一致**，
剩余 4 字节差来自另外两个独立缺陷：`gbUpdateCurTime` 本身未 GBAPI（`E8 rel32` vs `FF15`）、
以及 `0x1895070` 的声明类型不是 double（我们发整数 8 字节拷贝而非 `fld/fstp`））；
`OpenNULLFile::OpenNULLFile` 4→6（寄存器/求值顺序，见 F50 表）。
> 这些是"语义变正确但字节计数变差"的度量假象；L1 与 new_failures 两个硬门禁均未受影响。

**噪声澄清**：`PAL3.cpp` census 出现 +6 `C2248`、`CCCTData.cpp` +4、`UISceneMap.cpp` +1 ——
用"旧头文件目录前置"的受控 A/B（`%TEMP%\ddab\inc_old`，`git show HEAD:…` 还原 3 个头文件）重编 `PAL3.cpp`：
两臂 census **完全相同**（total 102，`C2248=17`）⇒ 与本轮改动**无关**；且 `regression_detector` 自报
"⚠️ C1003 截断单元(逐码增减不可测): 7"，`PAL3.cpp` 正在其中（其自身含 `C1003`）⇒ 逐码增减本就不可测。

**本轮最新机制分布**（`match` 后立即跑 `byte_diff_explain.py`，185/185 全部可解释）：

| 原因 | 数 |
|---|---|
| opcode/flow differs | 69 |
| register choice differs | 49 |
| immediate/const differs | 30 |
| operand shape differs | 18 |
| this/member disp differs | 15 |
| this-register differs | 2 |
| adjustor-thunk | 1 |
| cond-jump signedness | 1 |

**n_diff ≤ 5 的真实靶子（下一批优先）**：`AStarPathFinder::FindInClosed/FindInOpen`（各 n_diff=1，
this-register）、`SceneMgr::ClearInactiveRoles`（n_diff=1，`jl` vs `jb` 符号性）、`TextureLib::SetPath`（2）、
`PlayerAtt::CheckCurRV`（4）、**`UICaption::DestroyPanel`（4，`add ecx,0x60` 缺失 ⇒ 正是下面 ROI #3）**、
`ObjectCamera::ObjectCamera`（5）。
`error_classifier`：annotation_fix 51 / codegen_fix 24 / hexrays_limit 44 / manual_idb 2 / unknown 7（128 失败文件）。
`compile_regression.py`：**No regressions detected**，5 处改善。

**基线纪律**：`match` 写过的 `data/status/s4_baseline.json`、`pal3_registry.jsonl` 已 `git checkout --` 还原
（不从本机推进 tracked 基线）；新证据只落在**未跟踪**的 `data/status/s4_diff_detail.json`。

### 第 105 轮 ROI 排序（按证据强度 × 影响面）

1. **【最大】GBAPI 覆盖 gbengine 的 242 个导入函数与相关类**：原始二进制对 gbengine 函数的调用是
   `FF 15 <IAT>`（6 字节），我们发 `E8 rel32`（5 字节）⇒ 每个调用点 1 字节差并**整体移位**，
   足以把大量 partial 卡在 "opcode/flow differs"。证据：本轮已在 `gbUpdateCurTime` 上直接看到
   `FF15f8a45600`，且 IDA 导入表列出全部 242 个函数（模块 GBENGINE）。
   做法：给 `include/gbengine/*.h` 里的导入函数/类加 `GBAPI`（类用 `class GBAPI X`，与 `gbActorMgr` 一致），
   逐 TU 复编 + `match` 验证（该项**可能一次带来两位数 L1**，也最需要小步 A/B）。
2. **4 个 gbengine vtable 导入**（`??_7gbRefObject/gbVolumeModifier/gbNBTreeNode/gbVisNode`）：
   同机制；先定位 PAL3 代码里引用它们的函数（IDA 导入表已给出槽地址 0x56A1F4/0x56A2D4/0x56A3BC/0x56A5C4）。
3. **`UIScenePanel::~UIScenePanel` 归属（T1，独立复核给了逐字节验证但未执行 export）**：
   `0x0043B4D0` 现被 `functions.json:1837` 当 `void __cdecl()` 自由函数（另有一条 `:818` 的 skip 孪生条目
   写"misattributed in struct, removed"）。证据：函数首条 `mov [esi],0x56AC90`（**UIScenePanel.json:433 的
   vtable 地址**）、`[esi+0x158]` = `m_SlotData`（base_size 344）、ctor `0x43B3E0` 已在该类 methods 里。
   预期：`UICaption::DestroyPanel`（`83 C1 60 E9 rel32`）转 L1（+1），但**必须先查清上一轮为何把它移出**
   （同文件 `0x43B3E0` 上留着 `_misattrib_evidence: max_offset=372>class_size=96`，class_size=96 是 UICaption 的尺寸，
   疑为旧审计口径错误）——**与既有回退冲突，需单独一轮裁决**。
4. **浮点字面量提升**（独立复核 fa592148，补丁 `%TEMP%\pal3probe\stage4_promotion.patch`）：
   `float x > 0.0` 提升为 double ⇒ 我们发 `FCOMP qword`，原始是 `FCOMP dword`。判据
   `_expr_type(另一操作数)=='float'` 且 `(double)(float)v==v`；272 处/44 文件，其中 9 处在 S2-passing 单元。
   实测：S2 无翻转、**L1 32 → 32**（4 个函数各 −1 字节差，均未达 L1）⇒ **今天 L1 中性**，
   价值是正确性 + 263 处潜在红利。可作为"零 L1 但有真实修复"的批次，排在 GBAPI 之后。
5. **`0x1895070`（`dbl_1895070`）类型**：原始用 `fld qword ptr [eax]; fstp qword ptr [dst]`，我们发整数 8 字节拷贝
   ⇒ 该全局的声明类型需要 A 级证据裁决（本轮已在 `UICursor::IRender` 反汇编里拿到原始形态）。
6. 硬尾巴不变：`this`/寄存器选择类（`OpenNULLFile::OpenNULLFile`、`OpenBaseFile::~OpenBaseFile` 等）。


## 9. 第 105 轮（2026-09-19 深夜）：**gbengine 导入符号全部 GBAPI（dllimport）** + 发现 CRT 是 /MT

### F53 GBAPI 覆盖 gbengine 的 40 个类 + 4 个自由函数（A 级证据：原始二进制 1549 处 IAT 调用）

**证据链（全部实测，不靠推断）**
1. `original/PAL3.exe` 的导入表只有 7 个模块：ADVAPI32/DINPUT8/KERNEL32/USER32/WINMM/BINKW32/**GBENGINE(249 项)**，
   其中 242 个函数 + 4 个 vtable（`??_7gbRefObject/gbVolumeModifier/gbNBTreeNode/gbVisNode`）+ 2 个全局数据
   （`g_CurrentTime`@0x56A4F4、`g_pVFileSys`@0x56A598）+ 1 个静态成员（`gbColorQuad::ColorQuadFmt`@0x56A558）。
   （导入表由只读 IDA 脚本导出：`%TEMP%\dd105\dump_imports.py` → `imports.json`。）
2. 扫 `.text`：**`FF 15 <GBENGINE IAT>` 1477 处 / 228 个槽**，`FF 25 <槽>` 尾跳 72 处；
   而"函数被直接 `E8` 调用 + 本地 `FF 25` thunk"的**非 dllimport 形态 = 0 处**（`%TEMP%\dd105\scan_iat.py`）。
   ⇒ 原始 PAL3.exe 对 gbengine 的每一个调用都是**导入表间接调用**，我们此前的 `E8 rel32`（少 1 字节 + 语义不同）
   是**声明缺失**，不是 codegen 错。
3. 按调用点排序（`%TEMP%\dd105\rank.py`）：gbVec3D 301、gbMatrixStack 184、gbMatrix4 126、gbGeomNode 110、
   gbColorQuad 102、gbVisNode 72、gbVFileSystem 67、gbDynVertBuf 47、gbVertPoolMgr 45、gbTexture 45、
   CIniFile 45、gbCamera 42、gbRefObject 42、gbAudioManager 32 … 共 **42 个类占 1534/1549 处**；
   自由函数只有 5 个 15 处（gbCrc32Compute 6、gbLoadLightFile 4、gbUpdateCurTime 3、gbTimeCounterInit 1、
   gbCreateGraphManager 1）。

**落地**（`include/gbengine/*.h` 加 `GBAPI`，与既有 `class GBAPI gbActorMgr` 一致）：
16 个头文件、40 个类 + `gbMisc.h` 4 个自由函数；`gbengine/CMakeLists.txt` 加
`target_compile_definitions(gbengine PRIVATE GBENGINE_EXPORTS)`（让定义侧走 `dllexport`，宏本来就是为此写的）。

**踩到的坑（必记）**：类已 GBAPI 后，类内 `static GBAPI int ColorQuadFmt;` 触发
**C2487 'ColorQuadFmt' : member of dll interface class may not be declared with dll interface**
⇒ **201/201 单元全灭**（每个文件恰好 1 条）。改回 `static int ColorQuadFmt;`（类级 GBAPI 已覆盖）即恢复。

**受控 A/B（HEAD 头文件 vs 当前，同单元同 flag，`%TEMP%\dd105\ab_head.py`）**：
| 函数 | HEAD | GBAPI | |
|---|---|---|---|
| `C2DSpark::DestroyAll` | 356 | **351** | 改善 |
| `OpenSceneFile::OpenSceneFile(char*)` | 113 | 193 | 变差（寄存器分配/入栈顺序被 dllimport 改变） |
| `C2DSpark::C2DSpark(int,int)` | 551 | 582 | 变差 |

⇒ GBAPI **不是**纯收益：它把"调用形态"改对了，却改变了 MSVC 的寄存器分配，使部分 partial 的字节差变大
（都不在 L1 附近）。**保留**的理由：原始 1477 处 FF15 是语义硬证据，且 L1 净 +2、无 L1 回退、无新 partial。

**本轮管线结果**：S2 **73/207**（新增 6 个单元：CIniFile/CPK/gbChain1DNode/gbLightObj/gbOBBox/gbVec3D，
都是"PAL3.exe 里属于 gbengine 类的函数"，`own-fail 128→134`）、**new_failures 0**（对发布基线）、
**L1 34 → 36**、partial 185 → 183、matched 249/289 不变。
**+2 归属**：`PAL3VisNode::PAL3VisNode()`（n_diff 12 → L1）、`Parent_Data::NewEffect()`（84 → L1）。
**大幅改善**：`s_RoleState::LoadSkeletonModel` 85→10、`RoleCamera::UpdateAudioListener` 44→4、
`TextureLib::LoadTexture` 20→1、`MatrixStack::RenderScenePass` 44→21、`UIStatic::LoadResource` 86→67、
`CScreenModeNode::ctor` 31→14、`UINote::RenderWithStack` 33→17、`UIStatic::RenderQuadSlice` 348→342。
**变差（如实记录）**：`OpenSceneFile::ctor` 113→193、`UIProgressBar::Render` 594→649、`C2DSpark::ctor` 551→582、
`SceneMgr::Create` 126→146、`Scene::Render2` 278→296、`MatrixStack::BeginScene` 339→354、
`CCBPanelSlot::Render` 294→307、`UICaption::Render` 345→356。

### F54 `emit_headers` 扫 gbengine 类型时必须跳过导出宏（否则生成重复头 ⇒ C2011）

引入 `class GBAPI Foo` 后，`emit_headers.py` 的两处 `^(?:class|struct|enum)\s+(\w+)` 把 `GBAPI` 当成了类型名
⇒ `Foo` 不再被认作 gbengine 类型 ⇒ codegen 为它再生成一份 pal3 侧头文件
（`pal3/src/Misc/gbVec3D.h` 等）⇒ **C2011 type redefinition，match 阶段 73/73 单元全部 compile-skip**
（表现为 `matched 0/0 symbols | L1 0 | compile-skip 73`）。修复：新增 `_class_decl_name()`，
先剥 `__declspec(...)`、再剥 `GBAPI/DLLAPI/DLLEXPORT/DECLSPEC/EXPORT/API` 宏前缀，两处共用。

### F55 **【第 106 轮第一优先】原始 PAL3.exe 用的是静态 CRT（/MT），不是 /MD**

**证据**
1. 导入表 7 个模块里**没有 MSVCRT**（也没有任何 CRT 相关模块）⇒ CRT 是静态链接的。
2. 原始 `OpenSceneFile::OpenSceneFile` 里 `_strcmpi` 是 **`E8 rel32` 直接调用 0x55EF90**（本映像 `.text` 内），
   而我们的 /MD 版发 `FF 15 <msvcrt IAT>`。
3. 受控 A/B（同源码同其它 flag，仅换 `/MD`→`/MT`）：
   `??0OpenSceneFile@@QAE@PAD@Z` n_diff **193 → 59**（compiled_len 304 / orig 328）。
   命令：`%TEMP%\dd105` 内联脚本；全量测量 = `python pipeline/compare_pal3.py --flags "/nologo /TP /c /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MT /Gd"`。

⚠️ **这动摇的是全项目基线**：`HYPOTHESIS_FLAGS`（`pipeline/compare_pal3.py:331`）、
`cmake/toolchain-vc6.cmake`、`docs/compiler_setup.md` 都写着 `/MD`。

**全量 /MT 实测（`--flags "/nologo /TP /c /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MT /Gd"`）**：

| | /MD（当前基线） | /MT |
|---|---|---|
| matched | 249/**289** | 249/**362** |
| L1 | 36 | **37** |
| partial | 183 | 182 |
| unmatched | 40 | **113** |
| compile-skip | 0 | 0 |

⇒ **/MT 只带来 L1 +1**，而候选符号数暴增 73（≈每单元多 1 个未映射符号）、unmatched 40→113：
"C2DSpark 类单函数 193→59" 的红利**没有**转化为 L1。**结论：先别换 flag**。
第 106 轮要做的是**先解释那 113 个 unmatched 是什么**（每单元多 1 个 —— 怀疑是 /MT 下多出来的 CRT 侧符号，
需要一个只比 `?…@@` 游戏符号的过滤器），再决定是否重测；若只是比较器噪声，则 /MT 的 +1 不足以推动基线变更。
（`gc.compare_bytes` 与 `compare_pal3` 的 unmatched 统计见 `pipeline/compare_pal3.py` 的 `match_symbols`。）

### 第 106 轮 ROI（按"证据强度 × 影响面"）
1. **解释 /MT 下的 113 个 unmatched**（每单元多 1 个）——决定 /MD↔/MT 是否值得重测；若只是比较器噪声，
   则用"只比游戏符号"的过滤重测一次，再决定是否动 flag（**不动 tracked 基线**）。
2. **`UICaption::DestroyPanel`（n_diff=4，唯一 adjustor-thunk）**：`0x0043B4D0` = `UIScenePanel::~UIScenePanel`
   （vtable 0x56AC90、`[esi+0x158]`=m_SlotData、ctor 已在类内）。需先查清上一轮为何把它移出（skip 孪生条目 +
   `0x43B3E0` 上的 `_misattrib_evidence: max_offset=372>class_size=96`，class_size=96 是 UICaption 的尺寸，疑为旧口径错误）。
3. **浮点字面量提升**（272 处；L1 中性，正确性红利，补丁已备）。
4. **`0x1895070` 类型裁决**（`fld/fstp` vs 我们的整数 8 字节拷贝）、gbengine vtable 导入（4 个，同 F53 机制）。
5. 寄存器分配硬尾巴（`AStarPathFinder::FindInClosed/FindInOpen` n_diff=1 this-register、
   `SceneMgr::ClearInactiveRoles` n_diff=1 条件跳转符号性）。


## 10. 第 106 轮：**归属翻案 0x0043B4D0 = `UIScenePanel::~UIScenePanel`** ⇒ L1 36 → 37（唯一目标函数命中）

### F56 注解归属修正（A 级四重证据），删除旧审计的错误结论

**改动**（`data/annotations/CHANGE_LOG.md` 有完整条目）：
`functions.json` 删掉 0x0043B4D0 的两条自由函数条目（活动 `void __cdecl()` + 旧的 skip 孪生条目
"misattributed in struct, removed"）；`structs/UIScenePanel.json` 的 `methods` 加
`"0x0043B4D0": {"name":"~UIScenePanel","signature":"void __thiscall UIScenePanel::~UIScenePanel()"}`。

**本轮自己重做的 IDA 只读探针（不依赖任何转述）**：
- 0x0043B4D0 本体 47 字节：`push esi / mov esi,ecx / mov [esi],offset stru_56AC90`（vptr=**0x0056AC90**）
  `/ mov eax,[esi+158h] / … operator delete / mov [esi+158h],0 / mov ecx,esi / call ?Destroy2@UICaption@@QAEXXZ / pop esi / retn`。
- 0x0056AC90 = `UIScenePanel.json` 的 **`vtables[0].addr`**；全 .text 里**只有两处**写这个 vptr：
  0x43B497（在已属本类的 ctor 0x0043B3E0 内）与 0x43B4D3（本函数）⇒ ctor/dtor 对。
- `[this+0x158]`(=344) = 本类 `known_members["344"]`(`m_SlotData`)，析构删除+清零 ✓。
- 调用者 0x004461F0 = `UICaption::DestroyPanel`，原始形态正是 **`add ecx,0x60; jmp 0x43B4D0`**
  （adjustor thunk）；`UICaption.binary_size = 96 = 0x60` ⇒ 多继承下 UIScenePanel 子对象紧接 UICaption。
- 旧结论的来源查明：0x0043B3E0 上遗留 `_misattrib_evidence: max_offset=372>class_size=96`，
  而 96 是 **UICaption** 的尺寸 —— 口径错用（拿 UICaption 的尺寸判 UICaption 名下函数）。

**导出闸（改动的 A/B 判据，先看反编译再看字节）**：
`asm/pal3/decomp/UICaption_DestroyPanelvoid_004461f0.json` 由 `UICaption_Destroy2();` 变为
**`UIScenePanel::~UIScenePanel((UIScenePanel *)(this + 1));`**；
`UIScenePanel_~UIScenePanelvoid_0043b4d0.json` 变为 `__thiscall UIScenePanel::~UIScenePanel(UIScenePanel *this)`
（体内 `this->m_SlotData`）✓ 两者都如预期。

**管线结果**：S2 **73/207**（不变）、**new_failures 0**（对发布基线）、
**L1 36 → 37**、partial 183 → 182、matched 249/289、unmatched 40。
**逐函数归属**（新旧 detail 求差）：`+ UICaption.cpp ?DestroyPanel@UICaption@@QAEXXZ`（n_diff 4 → L1），
**新 partial 0 个、其余函数 n_diff 全部零变化** —— 单函数、可完全归因，是本会话最干净的一轮。

**最新机制分布（182 partial，`s4_diff_explain.json`）**：opcode/flow 69 · register 48 · immediate 30 ·
operand shape 17 · this/member disp 15 · this-register 2 · cond-jump signedness 1 · **adjustor-thunk 0（本轮清零）**。

### 第 107 轮 ROI
1. **`SceneMgr::ClearInactiveRoles`（n_diff=1，`jl` vs `jb`）**：解释器判为"annotation type"⇒ 若能定位到
   **成员/全局**的符号性错误，则是又一个可完全归因的 +1；若来自 Hex-Rays 局部变量类型，则记入硬尾巴。
2. **`TextureLib::LoadTexture(char*)`（n_diff=1，this/member disp）** 与 `TextureLib::SetPath`（2）：
   同一单元内两处，值得看是否同一处成员偏移。
3. **`AStarPathFinder::FindInClosed/FindInOpen`（n_diff=1，this-register）**：先判"ECX↔EAX 寄存器选择"
   是否由 `__thiscall` 原型/形参个数引起（历史上此族为 MSVC 分配硬尾巴，但这两处是 34/34 字节全同仅 1 字节寄存器差）。
4. **`/MT` 的 113 个 unmatched 符号**（每单元 ≈1 个）：先解释（obj 符号集差集）再决定是否重测 flag。
5. 浮点字面量提升（272 处，L1 中性）与 `0x1895070` 类型裁决。


## 11. 第 107 轮：**发现"隐式 vfptr 使 +0 成员把全表推 +4"（F57，试修违反门禁 ⇒ 已回退）** + **落地浮点字面量提升（F58）**

### F57 机制发现（负结果，证据完整；**未保留代码改动**）

**现象**：`TextureLib::LoadTexture` @0x004A6930 首条是 `8B B1 CC 00 00 00`（`lea esi,[ecx+0xcc]`），
而我们的编译结果是 `lea esi,[ecx+0xd0]` —— 单元里唯一的一字节差（n_diff=1）。

**根因（本轮实测）**：`TextureLib` 头声明了 2 个 `virtual` 方法 ⇒ MSVC 在 +0 隐式放 4 字节 vfptr；
而注解/发射的头在 +0 又声明了一个"真实成员"（`m_pResultTex`，注解 +0x0）⇒ 它被挤到 +4，
**其后每个成员整体偏 4 字节**。编译期偏移探针（`%TEMP%\dd107\probe_off2.cpp`，函数返回 `&((T*)16)->m - 16`）：

| 成员 | 注解 | 实测编译 | |
|---|---|---|---|
| `m_szPathBuf` | 0xC | **0x10** | +4 |
| `m_nTexWidth` | 0xB8 | **0xBC** | +4 |
| `m_nTexHeight` | 0xBC | **0xC0** | +4 |
| `m_Image` | 0xCC | **0xD0** | +4 |
| `sizeof` | 0x214 | **0x218** | +4 |

**影响面**（`%TEMP%\dd107\count_poly.py`）：711 个发射头里 **77 个声明 `virtual`**，其中 **17 个在 +0 带成员**；
这 17 个里 **14 个注解带 vtable**（CCBStage/CUtil/CEffect/CEffectSystem/ScreenEffectMgr/RoleAtt/CScreenMode/
RenderTarget/RenderTarget2/**TextureLib**/CameraCtrl/PalScript/PalScriptMgr/ScriptObj），
另 3 个（CCBCamControl/PAL3/SceneMgr）注解**无** vtable ⇒ 属另一问题（要么 `virtual` 标错，要么注解缺 vtable）。

**试修（已回退）**：在 `emit_headers.py` 已有的 P1(a) 后处理里加一条"类有 vtable（本函数自己发射
`// vtable (N methods…)` 注释）且 +0 是成员 ⇒ 删掉该成员"。结果**同时违反两个硬门禁**：

| | 基线（回退后） | 试修 |
|---|---|---|
| S2 | 73/207 | **72/207**（1 个单元新失败） |
| L1 | **37** | 36 |
| matched | 249/289 | 241/278 |

**为何失败**：被删的 12 个成员名字在生成代码里**被大量引用**（`m_pCBSystem` 319 次、`id` 134、
`m_bGetSceneScript` 54、`m_pCamera` 50、`m_pEnumeration` 50、`m_bLoadSceneScript` 46、`m_pDisplay` 31、
`m_iMode` 27、`m_pES` 25、`m_pVTable` 19、`m_pResultTex` 18、`m_bCanWarp` 0）⇒ C2039 等编译错误。
⇒ **必须与补偿 codegen 一起落地**：把"某类 +0 成员"的引用改写成编译器 vfptr 表达式
（同既有 `X->__vftable` → `(*(void**)X)` 的做法，含裸链虚调用改写）。
`pipeline/gen/stages/emit_headers.py` 已 **git 级别回退**（该文件只保留第 105 轮的 F54 修复）；
管线复测恢复 **S2 73/207、L1 37、partial 182**。

### F58 落地：浮点字面量提升（`float x > 0.0` → `0.0f`）

- 改动：`pipeline/gen/stages/stage4_substitution.py` **+123 行**（补丁 `%TEMP%\pal3probe\stage4_promotion.patch`，
  由独立复核给出并已 `git apply --check` 通过）：仅当**另一操作数可证明是 float**（`_expr_type(...)=='float'`）
  且字面量满足 `(double)(float)v == v` 时，给比较里的双精度字面量补 `f`；整数、double、赋值一律不动。
- 依据：原始 `UIProgressBar::FindChildByName` @0x43FDF3 是 `D8 1D 44 A6 56 00`（**FCOMP m32fp**），
  我们发 `DC 1D`（FCOMP m64fp）；类型条件化后变 `D8 1D` ✓。
- **本轮实测（完整管线）**：S2 **73/207**、**new_failures 0**、**L1 37（不回退）**、partial 182。
  逐函数：`PathObj::GetPosition` 264→263、`C2DSpark::CreateMore` 236→235、
  `UIProgressBar::FindChildByName` 120→119、`UIScrollBar::SetRange` 84→83（**各 −1 字节**，与独立复核数值完全一致）。
  ⇒ L1 中性、**n_diff 正向**；272 处里只有 9 处在当前可编译单元，其余 263 处是随 S2 提升自动兑现的潜在红利。

### 第 108 轮 ROI
1. **F57 + 补偿改写**（最高价值）：先做"被删 +0 成员的引用改写"（stage3_cleanup，按类名映射，
   与 `__vftable` 同一机制），再打开 emit_headers 的删除；预期 `TextureLib::LoadTexture` 直接 +1 L1，
   另有 13 个类（含 61 槽的 `RenderTarget2`、`CScreenMode`、`PalScript`）的成员访问整体归位。
2. `SceneMgr::ClearInactiveRoles`（n_diff=1，`jl` vs `jb`）：先判有无符号性来自成员/全局类型（可注解修）。
3. `AStarPathFinder::FindInClosed/FindInOpen`（各 n_diff=1，this-register，34/34 字节仅 1 字节差）。
4. `/MT` 那 113 个 unmatched 符号先解释再决定 flag。
5. `0x1895070` 类型裁决；以及本轮浮点补丁剩下的 12 处"非精确 float 字面量"（需改字面量值，单独批次）。


## 12. 第 108 轮：**F59 落地 —— 多态类 +0 成员改成 `static` 别名**（布局归位，L1 37 → 38）

### F59 做法（F57 的可编译版本）

F57 的结论是"+0 成员把其后每个成员推 +4"。直接把该成员**删掉**会破坏生成代码里大量 `X->成员`
引用（S2 73→72、L1 37→36）。本轮改用 **`static` 别名**：

- C++ 允许 `obj->静态成员`（VC6 实测 4 种用法全部可编译），而**静态成员不占对象字节**
  ⇒ 编译器隐式 vfptr 独占 +0，其后成员偏移全部归位，**且既有引用一行都不用改**。
- 判据门（证据化）：类里有 `virtual` **且** 本函数自己发射了 `// vtable (N methods…)` 注释
  （= 注解带 vtable）**且** 存在 `+0x0` 成员行 ⇒ 把该行改写成 `static <type> <name>;`。
  代码：`pipeline/gen/stages/emit_headers.py` 的 P1(a) 后处理块内（F59 注释）。

**实测（编译期 offsetof 探针 `%TEMP%\dd107\probe_off2.cpp`，改前→改后）**：

| | 注解 | 改前 | 改后 |
|---|---|---|---|
| `m_szPathBuf` | 0xC | 0x10 | **0xC** |
| `m_nTexWidth` | 0xB8 | 0xBC | **0xB8** |
| `m_nTexHeight` | 0xBC | 0xC0 | **0xBC** |
| `m_Image` | 0xCC | 0xD0 | **0xCC** |
| `sizeof(TextureLib)` | 0x214 | 0x218 | **0x214** |

**管线结果**：S2 **73/207**（不变）、**new_failures 0**（对发布基线）、**L1 37 → 38**、partial 182 → 181、
matched 249/289。
**逐函数归属**（对 L1=36 的旧 detail 求差）：`+ TextureLib.cpp ?LoadTexture@TextureLib@@QAEDPAD@Z`（n_diff 1 → L1，
正是 F57 锁定的目标函数）；**新 partial 0 个**；n_diff −1：`JusticeBookUI_Render`（F59）+ 上一轮浮点的 4 个函数。

**如实记录的代价（同单元 2 个 partial 变差）**：
- `TextureLib::SetPath` **2 → 37**、`TextureLib::CreateFromFile` 646 → 657。
- 原因已定位：这两个函数里有 **取地址**用法，例如
  `*((_BYTE *)&this->m_pResultTex + (_DWORD)result + 11) != 92`；
  `static` 别名下 `&成员` 变成**全局地址常量**（不再是对象基址 +0），整段寻址形态随之改变。
- ⇒ 正解是"**删成员 + 类型化 vptr 改写**"：`obj->M` → `(*(T*)obj)`、`&obj->M` → `((T*)obj)`
  （T = 注解里该成员的类型），既保持对象相对寻址、又不动其它成员布局。这是下一轮的第一优先。

### 第 109 轮 ROI
1. **F60 = F57 + 类型化 vptr 改写**（`obj->M` → `(*(T*)obj)`、`&obj->M` → `((T*)obj)`，按类名映射，
   放在 stage3_cleanup；映射可由 `ida_structs` 的"有 virtual + 有 vtables + data_members['0']"推出）。
   预期：保住 `TextureLib::LoadTexture` 的 L1，并把 `SetPath` 拉回 ≤2、`CreateFromFile` 回落到 ≤646；
   另有 13 个类（CScreenMode/PalScript/RenderTarget2(61 槽)/CEffect/…）成员偏移同时归位。
2. `SceneMgr::ClearInactiveRoles`（jl vs jb，1 字节）。
3. `AStarPathFinder::FindInClosed/FindInOpen`（各 1 字节 this-register）。
4. `/MT` 那 113 个 unmatched 先解释；`0x1895070` 类型裁决；12 处非精确 float 字面量。


## 13. 第 109 轮：**mangler 回指缺陷修复（matched 248 → 253）+ 原型修正（符号性归位）**

### F61a 原型修正：`UISceneUpdate` / `SceneMgr::ClearInactiveRoles` 返回类型 `int` → `SceneMgr *`

**动机**：`SceneMgr::ClearInactiveRoles`（n_diff=1）首差是 `jl`（原始）vs `jb`（我们）——同一表达式
两处符号性不一致。根因：该函数被标注为 `int` 返回，Hex-Rays 把 `result` 钉成 `int`，
只能发裸指针算术 `*(int*)(result+57568)` / **`*(_DWORD*)(result+57568)`**（同一地址两种渲染）。
**A 级依据**：返回值被当对象基址用（`[eax+0xe0e0]`=`SceneMgr.json m_nRoleCount`），且函数尾部没有 `mov eax,…`
⇒ eax 一直保留 `UISceneUpdate()` 的返回指针。
**结果**：反编译变为 `result->m_nRoleCount`（两处都带符号）✓，与二进制 `jl` 一致。

### F61b **工具缺陷修复（本轮可测收益）**：mangler 的"当前类自身"必须用回指编码

顺带暴露：改完原型后该函数被判 **unmatched**（matched 249→248、unmatched 40→41）。
对比真实 .obj 符号与 mangler 输出（A 级）：

| | 值 |
|---|---|
| MSVC 实际符号 | `?ClearInactiveRoles@SceneMgr@@SA`**`PAV1@`**`XZ` |
| mangler 原输出 | `?ClearInactiveRoles@SceneMgr@@SAPAVSceneMgr@@XZ` |

⇒ VC6 对"当前类自身"的类型引用用**回指**（`tag + 1@`），而 mangler 写全了类名。
修 `pipeline/ida/vc6_mangler.py::_self_ref_backref()`（返回类型 + 形参类型；只处理**当前类自身**——
父类/嵌套类编号语义无实测证据，不动）。**注意首版写成 `PA1@`（丢了 `V`），对照真实符号后改为 `PAV1@`。**

### 本轮管线结果

| 指标 | 前 | 后 |
|---|---|---|
| S2 | 73/207 | **73/207** |
| `new_failures` | 0 | **0** |
| **L1** | 38 | **38**（不回退） |
| **matched** | 248/289 | **253/289**（+5） |
| **unmatched** | 41 | **36**（−5） |
| partial | 180 | 185（新增的 5 个"以前根本比不到"的函数进入 partial 统计） |

**逐函数**：`SceneMgr::ClearInactiveRoles` n_diff 1 → **3**，首差从"条件跳转符号性"变为
`mov ecx,[eax+0xe0e0]`（原始）vs `mov ecx,[eax+0xe0cc]`（我们）——**差 4 字节**。

### 根因已定位（留给第 110 轮）：SceneMgr 也中 +4 错位

`SceneMgr.json` 的 `m_nRoleCount`=57568，但我们编译出 **57564** ⇒ 又一处 F57/F59 的 +4 错位。
SceneMgr **在注解里 `vtables=0`**，因此 F59 的门（"有 vtable 才处理 +0 成员"）**没有命中**。
第 108 轮统计过：17 个"虚函数 + 有 +0 成员"的类里，**3 个注解无 vtable**（CCBCamControl / PAL3 / **SceneMgr**）。

### 第 110 轮 ROI
1. **F62：对那 3 个"声明了 virtual 但注解 vtables=0"的类做真值裁决**：
   查它们 ctor 是否在 `[this+0]` 写 vtable 地址（F59 的探针方法）——
   - 若写 ⇒ 类确实是多态、IDA 的 vtables 列表不全 ⇒ 把 F59 的门从"注解有 vtable"放宽为
     "**编译期确实会插入 vfptr**"（即：类声明了 virtual），预期 `SceneMgr::ClearInactiveRoles` 归位到 n_diff 0/1（**+1 L1**），
     且 PAL3/CCBCamControl 的成员偏移同时归位；
   - 若不写 ⇒ 我们的 `virtual` 标错，应删（同样是布局归位）。
2. `/MT` 的 113 个 unmatched 先解释（现在 unmatched 已降到 36，需重测）；
3. 12 处非精确 float 字面量；`0x1895070` 类型裁决；AStarPathFinder 两处 this-register（各 1 字节）。


## 14. 第 110 轮：**F62 试放宽 F59 的门（负结果，已回退）** —— 但拿到两条新的 A 级证据

### 新证据 1：SceneMgr **确实是多态类**（注解 `vtables=0` 是 IDA 的缺漏）

扫 SceneMgr 的 15 个方法体（`%TEMP%\dd110\poly_check.py`，在原始 exe 上反汇编，找"把 .rdata 地址写进 [reg]"）：
`_scalar_dtor` **@0x004CD930**: `004CD936  mov dword ptr [esi], 0x56f9b4`
⇒ 二进制在建/析构时把 vtable(0x56F9B4) 写进 `[this+0]` ⇒ **类有 vfptr**。
而它的 +0 成员 `m_pGfxMgr` 让其后所有成员偏 4（`m_nRoleCount` 注解 57568、编译 57564）。

### 新证据 2：**`static` 别名会打乱生成器的 `_gap_` 记账**（这是回退的原因）

把 F59 的门从"注解带 vtable"放宽为"类声明了 virtual"后：
- 头文件层面**生效**（`SceneMgr.h`:23 变成 `static gbGfxManager * m_pGfxMgr; // +0x0 …`）；
- 但编译结果**更差**：`SceneMgr::ClearInactiveRoles` 里 `mov ecx,[eax+…]` 由
  **−4**（我们 0xe0cc / 原始 0xe0e0）恶化到 **−24**（我们 0xe0c8）。

⇒ 结论：**必须先修生成器的 gap 记账**（+0 成员被 static 化后，后续 `_gap_XXX[N]` 的起点/长度要按
"编译器隐式 vfptr 占 0..3" 重算），否则放宽门只会让偏移更远。
`emit_headers.py` 已回退到 F59 的窄门（原地保留 F62 的注释与实测数据），管线复测恢复
**S2 73/207、matched 253/289、L1 38、partial 185**。

### 本轮数据（无 byte 级落地，如实记录）

| 指标 | 值 |
|---|---|
| S2 | 73/207 |
| `new_failures` | 0 |
| L1 | 38（不变，无回退） |
| matched / unmatched | 253/289 · 36 |

### 第 111 轮 ROI
1. **F63：修 `_gap_` 记账 + 放宽门**（唯一能把 SceneMgr/PAL3/CCBCamControl 三个类拉回来的路径）。
   做法：在生成器里把"类的声明起点"设为 `4`（有虚函数时），或对每个类用**编译期 offsetof 探针**
   （`%TEMP%\dd107\probe_off2.cpp` 的模式）逐个类核对 gap；预期 `SceneMgr::ClearInactiveRoles` → n_diff 0/1（**+1 L1**）。
2. `AStarPathFinder::FindInClosed/FindInOpen`（各 1 字节 this-register，34/34 字节仅 1 字节差）。
3. 12 处非精确 float 字面量（改字面量值，需二进制常量对账）；`0x1895070` 类型裁决。


## 15. 第 111 轮：**F63 定位到"offset 键格式混用"（负结果，已回退）**

**目标**：修掉 SceneMgr 的 −20 偏移（`SceneMgr::ClearInactiveRoles` 残差 3 字节的根因）。

**测量（编译期 offsetof 探针 `%TEMP%\dd111\probe_scenemgr.cpp`）**：

| 成员 | 注解 | 编译 | |
|---|---|---|---|
| `m_pGfxMgr` | 0 | **4** | +4（隐式 vfptr，正常） |
| `m_nRoleCount` | 0xE0E0 | **0xE0CC** | **−20** |
| `sizeof` | 0xE544 | **0xE530** | **−20** |

**定位过程**：写了一个"按声明逐行累加偏移 vs 行尾 `// +0xXXX` 注释"的走查脚本
（`%TEMP%\dd111\gap_check.py`），漂移被夹在 **0xC660 与 0xC67E 之间**（26 字节未补）。
再查注解：`SceneMgr.json` 的 `known_members` 在 0xC660..0xC6A0 **只有** `m_nTodo_C660`，
而 `+0xC67E` 的联合**只存在于 IDA `_variants`**。

**试修**：给 `_variants` 分支补上 sibling 分支（多成员 union）已有的 gap 逻辑
（`if off > start_off: emit _gap_XXX`）——**没有生效**（头里仍无 `_gap_C664`）。

**更深一层的原因（本轮最有价值的一条）**：该分支发射的内部 gap 名是**十进制**——
`char _gap_50814[2]; // +0xC67E`（50814 = 0xC67E）——说明 **offset 键格式混用**：
注解/`_variants` 里既有十六进制串（`"0xC67E"`）又有十进制串（`"50814"`），
而外层 `sorted_offsets` 与 `_variants.get(off_str)` 都按**字符串**处理
⇒ **排序与查找都会错位**，`start_off` 记账随之漂移（这解释了我补的 gap 为何不触发：
处理到该联合时 `start_off` 已 ≥ `off`）。

**动作**：回退该 hunk（原地保留带实测数据的 F63 注释），管线复测恢复
**S2 73/207、matched 253/289、L1 38、partial 185**（本轮无 byte 级落地，如实记录）。

### 第 112 轮 ROI
1. **F64：把 emit 路径的 offset 键全部规范化成 `int`**（`sorted(..., key=int)` + 所有
   `_variants.get()`/`ann_members[]` 查找先用 `int(k,0)` 归一），再用 offsetof 探针逐类复核
   （SceneMgr 期望：`m_nRoleCount`=0xE0E0、`sizeof`=0xE544）⇒ 预期 `SceneMgr::ClearInactiveRoles` → L1（**+1**），
   且所有带 `_variants` 的类（SceneMgr/PAL3/CCBCamControl/…）成员偏移同时归位。
   风险：整段重构，必须全量 `codegen+probe+match` 回归。
2. 若 F64 收益不达预期，回到 F62（放宽 static 门）+ F64 一起做。
3. `AStarPathFinder::FindInClosed/FindInOpen`（各 1 字节 this-register）；12 处非精确 float 字面量；`0x1895070`。


## 16. 第 112 轮：**新工具 `tools/check_member_offsets.py`（布局桶的自动化度量）+ 三个定论**

**落地（工具，非猜测）**：`tools/check_member_offsets.py` —— 输入类名，自动
①从生成头里抓 `成员 → 注解偏移`，②生成 `&((Cls*)16)->member - 16` 的编译期探针并编译，
③反汇编 obj 读出**真实偏移**，④与注解对比：**均匀 +4 = 正常 vfptr 位移**，
**非均匀漂移 = 结构布局 bug**（`s4_diff_explain` 只能看到"某处 disp 不同"，看不到全貌）。
只写 `%TEMP%\pal3_offset_probe`，不碰仓库源码；有非均匀漂移时 `exit 1`。

**首跑结果（本轮三个定论）**：

| 类 | deltas | sizeof | 结论 |
|---|---|---|---|
| **TextureLib** | **{0}** | 0x214（=注解） | **F59（第 108 轮）的 `static` 别名修复端到端验证通过**：全部成员精确落在注解偏移 |
| **SceneMgr** | {−22, −20, **+4**} | 0xE530（注解 0xE544） | 首个漂移 = **`m_pRoleSystemArrayEnd` 注解 0xC67E、编译 0xC668（−22）**——精确落在第 111 轮怀疑的那段 `_variants` 联合上 |
| **PAL3** | {**+8**} | 0x16398 | 均匀 +8 ⇒ 比"一个 vfptr"多 4（另有基类 vfptr）；PAL3 属那 3 个"注解 `vtables=0`"的类，F59 窄门未命中 |

⇒ 第 111 轮"漂移夹在 0xC660..0xC67E"的判断被工具**独立证实并精确到成员**
（`m_nTodo_C660` 之后、`m_pRoleSystemArrayEnd` 就是第一个错的）。第 111 轮补的 gap 之所以不触发，
是因为该联合的**偏移来自十进制键路径**（发射名 `_gap_50814` = 0xC67E 的十进制），
`0xC668` 很可能是另一条键被误当偏移使用 —— 第 113 轮从这个锚点查即可。

**本轮管线数据**：无 byte 级改动（工具本身不影响产物）；保持
**S2 73/207、new_failures 0、L1 38、partial 185、matched 253/289**（回退 F63 后复测）。

### 第 113 轮 ROI
1. **F65：拿 `check_member_offsets.py` 的输出直接定位 `_variants` 联合的偏移来源**
   （为什么是 0xC668 而不是 0xC67E；键格式/大小写/十进制混用），修完用工具复测 SceneMgr 到
   `deltas={+4}`（或 {0}）；预期 `SceneMgr::ClearInactiveRoles` → L1（**+1**）。
2. **F66：PAL3/CCBCamControl 的均匀 +8** —— 用同一工具核对，判"多出的 4 字节"来自哪个基类，
   按 F59 的 `static` 别名法（或修 `virtual`）归位。
3. 之后：`AStarPathFinder` 两处 this-register、12 处非精确 float 字面量、`0x1895070`。


## 17. 第 113 轮：**F65 定位到 inline-UDT 分支（修正一半，另一半互相牵制 ⇒ 回退）**

**落地（工具）**：`emit_headers.py` 加 `PAL3_EMIT_TRACE=<ClassName>` 调试开关——逐成员打印
`(注解偏移 off, 记账起点 start_off, 成员名)`。它立刻给出关键事实：
**发射器的 `start_off` 一直落后注解**（如 `m_nRoleCount`：off=0xE0E0 而 start_off=0xDB98，差 0x548），
而各处 `_gap_` 已把差值补齐 —— 所以"某处少 26 字节"只可能发生在**没有 gap 逻辑的分支**。

**结论 1（已证实）**：SceneMgr.h 里 `union { // +0xC67E` 由 **inline-UDT 分支**
（`mtype.startswith('_inline_')`，约 1791 行）发射，而该分支**是四个 union/struct 分支里唯一没有 gap 逻辑的**
（另三处都有 `if off > start_off: emit _gap`）⇒ 该联合被摆在前一成员末尾（+0xC664）而非 +0xC67E（−26）。

**结论 2（修正一半）**：给该分支补上同样的 gap 后，**确实修好了这一段**
（头里出现 `char _gap_C664[26]; // +0xC664`，−22 漂移消失）。

**结论 3（互相牵制 ⇒ 回退）**：但 offset 工具复测显示**更早的区域被推多了**：
deltas 由 `{−22,−20,+4}` 变成 **`{4,20,22,24}`**、`sizeof` 0xE55C（注解 0xE544，**+24**）、
首个漂移 `m_pCCBStageRoleFind` ann=0x2B54 → 编译 **0x2B68（+20）**
⇒ inline-UDT 分支的**尺寸记账另有问题**（内联体的 `member_size`/`start_off` 推进），
必须与 gap 一起解，否则按下葫芦浮起瓢。**已回退**（原地保留 F65 注释与实测数字），
管线复测恢复 **S2 73/207、matched 253/289、L1 38、partial 185**。

### 第 114 轮 ROI
1. **F65-bis（唯一已缩小到单分支的问题）**：查 inline-UDT 分支的 `member_size` 计算与 `start_off` 推进
   （为什么补 gap 会把它推多 20/24；怀疑内联体尺寸用了 IDA `size` 而实际发射的更小/更大），
   用 `PAL3_EMIT_TRACE=SceneMgr` + `tools/check_member_offsets.py SceneMgr` 双工具闭环
   ⇒ 目标 `deltas={+4}`（或 `{0}`）⇒ 预期 `SceneMgr::ClearInactiveRoles` → L1（**+1**）。
2. **F66**：PAL3/CCBCamControl 的均匀 +8（工具已给出，两个类各差 4 字节的基类 vfptr）。
3. 之后：`AStarPathFinder` 两处 this-register、12 处非精确 float 字面量、`0x1895070`。


## 18. 第 114 轮：F67 浮点字面量判据放宽（**latent-only，实测全中性**）+ F65-bis 未落地

### F67 落地：`_is_exact_float_literal` 不再要求"精确可表示"

**依据**：Hex-Rays 把 float 常量渲染成 **double 字面量**（`%.7g`，如 `318.60001`、`0.0099999998`、
`3.1415927`），我们照抄成 double ⇒ 比较被提升为 64 位（`DC 1D` = FCOMP **m64fp**），而二进制是
`D8 1D` = FCOMP **m32fp**（第 107 轮已在 `UIProgressBar::FindChildByName` 逐字节验证）。
补 `f` 后编译器把该 double 字面量舍入到**最近的 float**，正是原常量值。
改动：`pipeline/gen/stages/stage4_substitution.py::_is_exact_float_literal` 去掉 `(double)(float)v == v`
要求，保留"含 `.`/`e` 且无后缀"与"另一操作数须为 float"两道门。

**实测（完整管线）**：S2 **73/207**、new_failures **0**、**L1 38（不回退）**、partial 185、matched 253/289，
**逐函数 n_diff 零变化** —— 这 12 处"非精确"字面量**都不在当前可编译单元里**
（第 107 轮落地的 9 处恰好全是可精确表示的那些）。
⇒ 定位为 **latent-only 正确性修复**：等这些单元进 S2 后随比较宽度一起兑现；本轮无字节收益（如实记录）。

### F65-bis：未动代码

上一轮已定位：SceneMgr 的 `union { // +0xC67E` 由 **inline-UDT 分支**发射，而该分支是四个 union/struct
分支里唯一没有 gap 逻辑的；补 gap 能修好这一段，却把更早区域推多（工具复测 `{4,20,22,24}`、sizeof +24）
⇒ 该分支的**尺寸记账**必须一起改。本轮为避免再留半成品而未改。

### 第 115 轮 ROI
1. F65-bis：inline-UDT 分支的 `member_size`/`start_off` 记账（`PAL3_EMIT_TRACE=SceneMgr` +
   `tools/check_member_offsets.py SceneMgr` 双工具闭环；目标 `deltas={+4}`）⇒ 预期 SceneMgr::ClearInactiveRoles → L1（+1）。
2. F66：PAL3/CCBCamControl 的均匀 +8（工具已给出）。
3. `AStarPathFinder` 两处 this-register（各 1 字节）；`0x1895070` 类型裁决。


## 19. 第 115 轮：**F65-bis 根因确定（estimate vs 实际发射字节）+ 工具加 `--verbose`**

**读代码得到的确定结论**（`emit_headers.py`）：
1. 通用 gap 逻辑在 **1858-1861 行**（`if off > start_off: emit _gap_%03X`），只有走到那里的"普通成员"才有；
   `_gap_C5E0[128]` 这类**十六进制**命名的 gap 就是它合成的。
2. **inline-UDT 分支在 1850-1853 行 `continue`**（`start_off = off + _inline_data['size']`），
   **永远不会走到 1858 行的通用 gap** ⇒ 内联体既没有"外层 gap"，其后的成员记账又改用 IDA size。
3. 记账用的 `start_off` 是 **`off_prev + _estimate_member_size(...)`＝估计值**，**不是实际发射的字节位置**；
   当某成员（数组/内联体）实际发射的字节 > 估计值时，`start_off` 就落后于真实位置 ⇒
   第 113 轮"按 `off > start_off` 补 gap"会在这些地方**多补**（实测 0x2B54 区域 +20、sizeof +24）——
   这就是"按下一个葫芦浮起一个瓢"的机制。

**落地（工具）**：`tools/check_member_offsets.py --verbose` 打印逐成员表并标注
"<-- drift changes here"。SceneMgr 首跑即定位到两个转折点：
`m_pRoleSystemArrayEnd`（ann 0xC67E → 0xC668，**−22**）与 `m_nTodo_C848`（ann 0xC848 → 0xC834，−20）。

**管线**：本轮无功能改动 ⇒ **S2 73/207、new_failures 0、L1 38、partial 185、matched 253/289**。

### 第 116 轮 ROI（F65-bis 的可执行形态）
1. 把 inline-UDT 分支的**记账改成"实际发射末尾"**：分支内已知内联体各成员的
   `_iab/_iiab + _estimate_member_size`，用其最大值作为 `member_size`；或更彻底地为
   `_emit_member` 增加"返回实际发射字节数"的第二个返回值，全循环统一用实际值。
   然后用 `PAL3_EMIT_TRACE` + `--verbose` 复测 SceneMgr 到 `deltas={+4}` ⇒
   预期 `SceneMgr::ClearInactiveRoles` → L1（**+1**）。
2. F66：PAL3/CCBCamControl 的均匀 +8（工具已给出）。
3. 若 F65-bis 再次失败：按收敛判据把该机制记为"已定位但需结构级重构"，
   转入硬尾巴归档与收敛总结（L1 38 已停留 8 轮）。


## 20. 第 116 轮：**布局桶全量清点（新工具 `--all`）——机制桶首次被完全枚举**

**落地（工具扩展）**：`tools/check_member_offsets.py --all [--limit N]` —— 扫出全部"声明了 virtual"
的生成头（**77 个类**），逐类编译 offsetof 探针并分类 drift，输出全量清单。

**清点结果（本轮核心证据）**：

| 类别 | 数量 | 含义 |
|---|---|---|
| **uniform `[0]`（布局与注解完全一致）** | **50**（53 uniform 中 50 个是 0） | 这些类的结构**已经正确**（多数是 F59 的 `static` 别名在起作用） |
| uniform 非 0（常量漂移） | **3** | `PAL3 +8`、`CCBFiveNimbusWindow +16`、`CCBUIPanel +108` —— 都是"某处少一块"，与成员无关的常量位移 |
| **non-uniform（注解/发射器不一致）** | **21** | 形态高度一致：`[0, 40]`、`[0, 68]`、`[0, 64]`、`[0, 96]`… ⇒ **每类恰好一个"洞"**，从某个成员之后整体偏一个常量（与 SceneMgr 的 union 洞同型） |
| 探针编译失败 | 1 | `RoleAtt`（另需单独看） |

⇒ **这是本会话第一次把"结构布局"这个机制桶完全枚举**：不是"到处都错"，而是
**21 个类各有一个洞 + 3 个类的常量漂移**；其余 50 个多态类布局已精确。
每个洞都能用 `--verbose`（逐成员 + "drift changes here"）在**几分钟内定位到具体成员**。

**管线**：本轮无功能改动 ⇒ **S2 73/207、new_failures 0、L1 38、partial 185、matched 253/289**。

### 第 117 轮 ROI（可执行、已枚举）
1. 对 21 个 non-uniform 类跑 `--verbose`，把"洞"归到具体成员，抽样验证是否都是**同一个发射路径**
   （inline-UDT / `_variants` / 显式 gap 三选一）；若是，则 F65-bis 的修法可一次性覆盖 21 个类。
2. 3 个常量漂移类（+8/+16/+108）：用 `--verbose` 二分定位"少的那一块"，多半是基类尺寸或 +0 成员。
3. 剩余（register/opcode-flow 桶）按收敛判据归档为硬尾巴。

### 收敛判断（截至第 116 轮）
- **L1：21 → 38（本会话 +17）**，其中第 105/106/108 轮各 +2/+1/+1；自第 108 轮起连续 9 轮持平。
- 机制桶现状：① 结构布局 = **21 类各一洞 + 3 类常量漂移**（已枚举、已工具化、修法已定位到单分支）；
  ② partial 差异分布（185 个）仍以 opcode/flow 69 + register 48 + immediate 30 为主 —— 属**寄存器分配/调度硬尾巴**
  （多次尝试均无字节收益）；③ 注解/导入/归属三类此前的机制桶**已全部清零**
  （adjustor-thunk 0、vftable 残留无新增、gbengine 导入已 GBAPI 化）。
- ⇒ 目标**未收敛**（第 ① 桶仍可推进），但增长点已收敛到"结构布局"这一条线。


## 21. 第 117 轮：**21 个洞归类 —— 不是"缺洞"，而是"内嵌成员被多发射"**

### 方法与一个自我修正

先写了一个"按声明累加 vs 注释偏移"的走查脚本给 21 个类分类，结果把它自己否掉了：
它报的 first hole 全部紧邻 `char _gap_XXX[N];` 行（即发射器**确实补了 gap**），
那些 `+4` 的"洞"其实是**我这张粗糙尺寸表**漏算了一个 4 字节成员造成的假阳性
⇒ **走查脚本不可作为判据，`--verbose` 的"drift changes here"标记（来自真实编译）才是**。

### 真实分类（工具实测，4 个抽样类的首个漂移点）

| 类 | 首个漂移成员 | 注解 → 编译 | 漂移 |
|---|---|---|---|
| UIListBox | `m_numcol` | 0x1B0 → 0x210 | **+96** |
| JusticeBookUI | `m_OutFrameT` | 0x364 → 0x3A8 | **+68** |
| UITitle_BBTY | `m_exit`（随后 `m_Name` 再 +68） | 0x710 → 0x7DC | **+204** |
| CCBStage | `m_TempStorageNGH` | 0x44 → 0x6C | **+40** |

**关键读数：漂移是正的**（编译 > 注解）⇒ 在漂移点**之前**有成员**被多发射**了 N 字节，
而不是"某处缺一块"。结合前几轮已知事实（gap 行由注解偏移算出、内嵌 UDT 走
`start_off = off + _inline_data['size']`、`_ann_var` 会"恢复注解保存的数组类型"），
指向**同一个成因**：**内嵌 UDT / 被恢复的数组类型成员的实际发射宽度 > 注解槽位**，
把其后所有成员整体推后（SceneMgr 的 −26 是同一记账机制在另一个方向上的表现）。

⇒ 21 个类 + 3 个常量漂移类，很可能都落在**同一条"成员宽度记账"线**上（可一次性修）。

### 管线
本轮无功能改动 ⇒ **S2 73/207、new_failures 0、L1 38、partial 185、matched 253/289**。

### 第 118 轮 ROI（已收敛到单点）
1. 对抽样类跑 `--verbose`（**不过滤**），看漂移点**前一个成员**的声明与注解槽位之差，
   确认是否 = 该成员的"发射宽度 − 注解宽度"；再查该成员走的是哪条分支
   （`_inline_*` 内嵌体 / `_ann_var` 数组恢复 / 显式嵌套 UDT）。
2. 若确认，则修"成员宽度记账"一处，预期同时修好 21+3 个类的布局，
   并用 `tools/check_member_offsets.py --all` 复测（目标：non-uniform 21 → 0）
   ⇒ 这是**本会话最后一个能成批转 L1 的机制**（SceneMgr::ClearInactiveRoles 等已锁定）。
3. 之后按收敛判据收尾（L1 38 已停留 10 轮）。


## 22. 第 118 轮：**根因再上一层 —— 21 个"洞"是少数"尺寸错类"的级联**

**实测（offset 工具）**：

| 类 | 编译 sizeof | 注解 binary_size | 差 |
|---|---|---|---|
| **UIScrollBar** | **0x1C0** | **0x160** | **+96** |
| **UIButton** | **0x19C** | **0x158** | **+68** |
| **UIRoleDialog** | **0x358** | **0x2D0** | **+136** |
| UIListBox | 0x524 | 0x4B8 | +108（含上面的级联） |

而 UIListBox 的漂移点正是 **`m_scrollbar`（UIScrollBar 内嵌成员）之后**：
`m_scrollbar` 编译在 0x50（精确 ✓），但其后的 `m_numcol` 由注解 0x1B0 被推到 0x210（**+96 = UIScrollBar 的尺寸差**）。
JusticeBookUI 的 +68 = UIButton 的尺寸差，同型。

⇒ **21 个 non-uniform 类并不是各自有洞，而是少数"尺寸错的类"被内嵌后把宿主的后续成员整体推后**；
每个"尺寸错的类"自己又有首个漂移成员（`UIScrollBar::m_keytime` +96、`UIButton::m_disablepic` +68、
`UIRoleDialog::m_ani` +64）⇒ 真正要修的是**这几条根**（成员宽度记账），修好后 21 个级联一起消失。

**工具**：给 `--all` 加了"SIZE-WRONG（编译 sizeof vs 注解 binary_size）"小节；但注意
`--all` 目前只扫**声明了 virtual** 的类，而根类（UIScrollBar/UIButton/UIRoleDialog）**不是多态类**
⇒ 该小节本轮报 none；已记录需按漂移点反查内嵌类、或把扫描范围扩到"被内嵌引用的类"。

### 第 119 轮 ROI（最后一批，若成立可一次修好 21 个级联）
1. 对三个根类跑 `check_member_offsets.py UIScrollBar UIButton UIRoleDialog --verbose`，
   定位它们各自"发射宽度 > 注解宽度"的那个成员，**修成员宽度记账一处**。
2. 修后用 `--all` 复测（目标 non-uniform 21 → 0），再跑完整管线看 L1
   （预期至少 `SceneMgr::ClearInactiveRoles`、`UIListBox`/`UIButton` 相关函数转 L1）。
3. 若不成立：按收敛判据把该机制记为"已定位到根类、需结构级重构"，转入收敛总结。


## 23. 第 119 轮：**根因链追到底 —— "尺寸错的类型"是一条级联链（可逐环修）**

**逐环实测（全部来自 `check_member_offsets.py` 的编译期探针）**：

```
UIListBox          +96  ⇐ 内嵌 UIScrollBar（编译 0x1C0 / 注解 0x160）
 UIScrollBar       +96  ⇐ 成员 m_texarray @0xC0：注解槽位 68 字节（下一成员 m_texarrayInfo @0x104 定界），
                          但排放类型 UITextureArray 编译 sizeof = 0x80 = 128 字节 ⇒ 该成员多出 0x3C(60)
                          再加上其后的 _gap_108[36] 被一起顶高 ⇒ m_keytime 由 0x12C 推到 0x18C（+0x60=96）
  UITextureArray   +60  ⇐ 其 m_num 注解 0x40、编译 0x7C ⇒ 它自己的前导成员又大了 60 字节（链再下一环）
```

⇒ **这不是"发射器 bug"，而是"重建的类/类型尺寸比二进制大"，且以类型内嵌的方式级联**。
证据规则（A 级、可机械套用）：**用"容器类里下一个成员的注解偏移"给上一个内嵌成员定界**，
即 `slot = next.offset − member.offset`；凡 `sizeof(该类型) > slot` 就是一环。

**修法（留给后续，已验证可定位、未实施）**：沿链向下找到"自己的前导成员也过大"的那个类型，
在它的注解里按同一规则修正（`data/annotations/structs/<Type>.json`），改一层即消掉其上游所有级联。
每环定位耗时约 1 分钟（`check_member_offsets.py <Type> --verbose`）。
本轮**未改代码**：链条 ≥3 环且每环都需独立 A 级定界，避免再留半成品。

### 第 120 轮（末轮）ROI / 收尾
1. 若时间允许：只做**一环**——`UITextureArray` 前导成员的定界修正（证据：`m_num`@0x40 与容器槽位），
   然后用 `--all` + 完整管线验证（不得回退门禁）。
2. 无论是否实施：按收敛判据出**收敛总结**：本会话 L1 21→38（+17），
   注解/导入/归属/vftable 四族机制清零；剩余 = "尺寸错类型的级联链"（已定位到环、定位手段已工具化）
   \+ 185 个寄存器分配/调度硬尾巴 partial。

**本会话交付物清单（供末轮总结引用）**：
`tools/check_member_offsets.py`（含 `--all` 清点 + `--verbose` 逐成员 + SIZE-WRONG 小节）、
`tools/byte_diff_explain.py`（partial 归因）、`pipeline/gen/stages/transform.py`（F20/F51 尾跳）、
`pipeline/gen/stages/stage4_substitution.py`（浮点字面量两批）、`emit_headers.py`（F54/F59/F62/F63/F65 注释与门）、
`pipeline/probe_compile.py` 等一批编码修复、`data/status/_longterm_plan.md` §8–§23、
`data/annotations/CHANGE_LOG.md`（F56/F61 条目）。


## 24. 第 120 轮（末轮）：**F68 根因修复 —— `_estimate_member_size` 的"数组 vs 指针"顺序**

**根因**（`emit_headers.py:_estimate_member_size` 第一行）：
```python
if '*' in mtype: return 4        # ← F68 之前：`gbTexture *[16]` 被判成 4 字节
```
数组判断排在指针判断**之后** ⇒ **所有"指针数组"成员都被只算一个指针**，
循环的 gap 决策据此**多补** (N−1)×4 字节。

**实测印证（编译期探针 + 生成头）**：`UITextureArray` 里
`gbTexture * m_ptex[16];`（64 字节）之后又被补了 `char _gap_004[60]; // +0x4`，
`m_num` 由注解 0x40 被推到 0x7C（+60）、类尺寸 0x80（注解 0x44）——
这正是第 119 轮追到的**级联链唯一根**：`UIListBox +96 ⇐ UIScrollBar +96 ⇐ m_texarray(UITextureArray) +96 ⇐ 本行`。

**修复**：把数组分支移到指针分支**之前**（数组分支内部递归，指针基类型仍返回 4）。

**修复后（工具复测）**：`UITextureArray` `deltas={0}` sizeof **0x44**（=注解）、
`UIScrollBar` `deltas={0}` sizeof **0x160**（=注解，原 0x1C0）、`UIListBox` `deltas={0}`（原 +96）。

**管线结果**：S2 **73/207**、**new_failures 0**、**L1 38（不回退）**、partial 185、matched 253/289；
逐函数：改善 `JusticeBookUI::ProcessInput` 271→268、`SwordUI::RenderSword` 629→627、
`UIPushButton::SetAnimOffset` 39→37；变差 `Scene::GetTileHeight` 377→406、`UITitle_BBTY::ctor` 111→112。
⇒ **修掉了真实的成批 root bug（布局全部归位），但本轮 L1 未变**（受影响函数距字节全同仍远）。

---

## 25. 会话收敛总结（第 104–120 轮，objective 的最终评估）

### 硬门禁（全程未破）
| 指标 | 起点（第 103 轮） | 终点（第 120 轮） |
|---|---|---|
| S2 ok | 73/201 | **73/207**（+6 个新单元，ok 数不变） |
| `new_failures`（对发布基线 20260919_000552） | 0 | **0** |
| **L1** | **32** | **38**（partial 187 → 185） |
| matched / unmatched | 249/289 · 40 | **253/289 · 36** |
| tracked 基线 | 未推进 | **未推进**（每轮 `git checkout` 还原） |

> 若从本会话最早记录算起：**L1 21 → 38（+17）**。

### 已耗尽/已修的机制桶
1. **导入符号**：gbengine 全部导入（40 类 + 4 自由函数）补 `GBAPI`（证据：原始 .text 里 1549 处 `FF 15` IAT 调用、0 处本地 thunk）⇒ 第 105 轮 L1 +2。
2. **归属**：`0x43B4D0 = UIScenePanel::~UIScenePanel`（同 vptr + 同成员 + ctor/dtor 对 + 调用者 thunk 四重证据）⇒ 第 106 轮 L1 +1，adjustor-thunk 桶清零。
3. **虚函数类 +0 成员把全表推 +4**：F59 的 `static` 别名 ⇒ 第 108 轮 L1 +1（TextureLib 布局 50 个类现已 `deltas={0}`）。
4. **浮点字面量比较宽度**（两批：精确 + 非精确）⇒ n_diff 正向，L1 中性。
5. **mangler 回指缺陷**（`SAPAV1@XZ` vs 写全类名）⇒ matched 248→253、unmatched 41→36。
6. **F68 数组/指针尺寸顺序**（本轮）⇒ 尺寸错类型的级联链根除。
7. **工具链/门禁**：`probe_census` 编码（写/读全链）、`byte_diff_explain`、`check_member_offsets`（逐成员 + `--all` 清点 + SIZE-WRONG）。

### 剩余（按收敛判据）
- **寄存器分配/调度硬尾巴**：185 个 partial 的差异分布（opcode/flow 69 · register 48 · immediate 30 · operand shape 17 · this-member 15 · this-register 2）——多轮尝试（签名/类型/代码形状）均无字节收益。
- **两处仍已定位但未修**：① inline-UDT 分支缺外层 gap（SceneMgr 的 −26，需与"实际发射宽度"记账一起改）；
  ② 三个常量漂移类（PAL3 +8、CCBFiveNimbusWindow +16、CCBUIPanel +108，工具已给出）。
- ⇒ **L1 增量已趋零**（第 108 轮后 12 轮持平），增长点仅剩上述结构级项与硬尾巴 —— 与 objective 的收敛判据一致，
  但上述两项仍属"已定位、可修"，故目标**保持 active**交由下一会话。


## 26. 【目标重设】第 121 轮起：**以"编译错误数"为核心收敛指标**

用户裁定：本会话一直用 S2 ok / L1 汇报，**错误数才是判据**（它涨了 +127：+108 新增编译面、+21 共享单元净增）。
目标已重设（`max_goal_rounds` 120 → 140）并把口径固定为：

**核心指标：总编译错误数（基线 2446）**，每轮**分两栏**报告：
- **A. 共享单元错误数**（起点 **2465**）+ 逐码增减：当前 `+C2039 12 · +C2660 8 · +C2027 7 · +C2784 6 · +C2248 6 ·
  +C2059 5 · +C2501 4 · +C2334 4 · +C2018 4 · … · −C2440 16 · −C2679 14 · −C2451 4 · −C2385 3 · −C2227 2`；
- **B. 新增编译面**（基线不存在的单元，起点 6 个 / **108** 条：CPK 46、CIniFile 21、gbOBBox 20、
  gbLightObj 17、gbChain1DNode 3、gbVec3D 1）——这些函数 IDA 早有反编译（`asm/pal3/decomp/` 里就有），
  基线里被**静默漏编**，属"新增可见面"而非既有代码退化。

**任何指标退化（错误数/S2/L1/matched/invariants）都必须有 A/B 解释并写入本文档；无法解释的退化一律回退。**

### 第一批（本轮启动）：共享单元 +41 的二分归因
- 已**排除** GBAPI：受控 A/B（同源码、仅把头换成 HEAD 版 gbengine 头）⇒ PalScriptMgr 80 vs 80、
  ScriptVM 102 vs 102，**逐码 delta 全 0**。
- 正在二分 **F59**（虚函数类 +0 成员 `static` 别名）：脚本 `%TEMP%\bisect_f59.py`
  （关掉门 → `codegen all` + `probe_compile s2` 测共享/总错误与两个关注单元 → **恢复并复测**，
  try/finally 保证不留半成品）。
- 若 F59 排除，继续二分 **F54**（`_class_decl_name`）与 **F68**（数组先于指针）。

### 后续优先级（按错误码）
C2039（"不是成员"，+12）→ C2660（形参个数，+8）→ C2027（未定义类型，+7）→ C2784/C2248/C2059；
每项都要"错误数下降 + 无解释不了的退化"双满足。


## 27. 第 121 轮（新目标首轮）：**F69 落地 —— IDA thunk 签名污染生成头**

### 归因（本轮先做排除法，证据全部来自 A/B）
| 候选 | 方法 | 结果 |
|---|---|---|
| GBAPI | 同源码换 HEAD 版 gbengine 头，编两个单元 | **80/80 · 102/102，逐码 delta 全 0 ⇒ 排除** |
| F59（+0 成员 static 别名） | 关闸 → codegen+probe → 恢复 | 总/共享/两单元 **全 0 delta ⇒ 排除** |
| F68（数组先于指针） | 同上 | **全 0 delta ⇒ 排除** |
| F54（`_class_decl_name`） | 同上 | **反向：关掉它 +975 错误、S2 ok 0 ⇒ 它是巨大净收益** |
| include/ 全部会话头改动 | 同源码换 HEAD 的 5 个头 | **全 0 delta ⇒ 排除** |
| 管线幂等性（无改动跑 apply+export+codegen+probe） | — | **全 0 delta ⇒ 无漂移** |
⇒ 真正的元凶由**错误消息 diff**（census vs 基线，无需编译）当场锁定：

```
PalScriptMgr.cpp  now 80 base 54：+18 C2039 'GetCGEntry' : is not a member of 'CG_Entry'
                                  +1 C2059 syntax error '[' / +1 C2334 / +1 C2018 unknown character 0x60
                                  +1 C2146 missing ';' before 'm_BossHurt' / +1 C2501
ScriptVM.cpp      now 102 base 87：+6 同上 C2039 GetCGEntry / +4 C2027 undefined type 'CameraCtrl' …
```

### 根因与修复（F69）
注解/IDA 里的签名是 **PDB 的 thunk 渲染**：
`"[thunk]:class GetCGEntry \`public: static class GetCGEntry * ()"`（含 `[thunk]:`、**反引号 0x60**、`public:`）
⇒ 生成头里出现 **非法声明行**，一个 CG_Entry 方法消失 → 20 处调用点 C2039 + 同行的解析连锁错误。
修复：`pipeline/gen/stages/emit_headers.py::parse_signature()` 开头统一清洗
（取最后一个反引号之后的部分 → 去 `[thunk]:…` 前缀 → 去 `public:/protected:/private:`），**对所有类生效**。

### 本轮指标（新目标的两栏口径）
| | 基线 | 本轮前 | **本轮后** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2465 | **2425（−19，首次低于基线）** |
| B. 新增编译面（6 单元） | — | 108 | **108** |
| 总错误数 | 2446 | 2573 | **2533（−40）** |
| PalScriptMgr / ScriptVM | 54 / 87 | 80 / 102 | **54（=基线） / 88（+1）** |
| S2 ok / new_failures / L1 / matched | 68 / 0 / — / — | 73 / 0 / 38 / 253 | **73 / 0 / 38 / 253（无退化）** |

（遗留外观问题：发射行变成 `static static class GetCGEntry * GetCGEntry();` —— 双 `static`，对错误数无影响，记为待清理。）

### 第 122 轮 ROI（按错误数排序）
1. **C2673 ×39**（基线 0；全部在新编译面）：`'LoadData' : global functions do not have 'this' pointers`
   —— 函数体用了 `this->` 却按自由函数发射（CIniFile 21 / CPK 46 里的主体）⇒ **归属/签名类修复**，
   是新增面最大的单一错误族。
2. 共享单元残余增量逐个用"census 消息 diff"归因（ScriptVM +1、CCCTData +6、PalScript +5、UIBigMap +2 …）。
3. 新增面按量级攻：CPK 46 → CIniFile 21 → gbOBBox 20 → gbLightObj 17（这些代码原本被静默漏编，现在才可见）。


## 28. 第 122 轮：C2673 ×39 的根因链（诊断完成，修复需先解 dllimport 冲突）

**错误族**：`C2673 'LoadData'/'InitPackFiles' : global functions do not have 'this' pointers`，基线 0、现在 **39**
（全部落在新编译面：CIniFile、CPK 等）。

**根因链（本轮读完即定，A 级）**：
1. 生成单元里有定义：`pal3/src/Misc/CIniFile.cpp:10  char CIniFile::LoadData() { … v3 = this + 2522; … }`
   （注解/IDA 类型：`char __thiscall CIniFile::LoadData()` @0x004EC700 ✓ 成员）。
2. 但**类头里没有该方法的声明**：`CIniFile` 是 **gbengine 类型**，声明在
   `include/gbengine/gbVFileSystem.h:275 class GBAPI CIniFile { … }`，其方法表**只列了引擎侧方法**
   （OpenFileRead/ReadSection/ReadLine/…），没有 `LoadData` / `LoadStructuredConfig`。
3. ⇒ MSVC 认为 `char CIniFile::LoadData()` **不是成员定义**（C2511 之后按非成员继续解析），
   于是函数体里的 `this` 变成"全局函数里的 this" ⇒ **C2673**，并连带 C2039 等。

**为什么不能直接加声明（本轮未改代码的原因）**：该类是 **`class GBAPI CIniFile` = dllimport**
⇒ 在类里补声明会把 `LoadData` 也变成**导入成员**，而它恰恰是 **PAL3.exe 自己实现**的函数
（0x4EC700 在 PAL3 的 .text 里）⇒ 定义导入成员会触发 **C2491**，调用点还会去引用不存在的 `__imp_`。
这正是第 105 轮 **F53「按类整体加 GBAPI」的副作用**：对"引擎导出 + 游戏侧又实现/扩展"的类
（CIniFile、CPK）**类级 dllimport 是错的**。

### 第 123 轮批次（已定位，含 A 级证据来源）
1. **F70：把 GBAPI 从"类级"改为"按成员"**，成员集合直接取**真实 IAT 清单**
   （`%TEMP%\dd105\imports.json`：GBENGINE 249 项；`enum_import_names` 导出，A 级）——
   只给"确实来自 gbengine.dll"的方法加 `GBAPI`，引擎头里被 PAL3 实现/扩展的方法（CIniFile::LoadData、
   CPK::InitPackFiles…）保持普通成员，并在类里**补上声明**。
2. 预期：C2673 39 → 0，并消掉 CIniFile/CPK 两个新单元里的大半 C2039/C2511；
   验收口径 = 共享单元错误数继续下降、**新编译面错误数也下降**，且 S2/L1 不回退（新单元当前 S2 本就 fail）。
3. 注意：改动涉及 16 个头里的 GBAPI 位置，必须用 `tools/mangler_bench.py`/`probe` 双重复核，
   并按门禁 4 记录任何退化。


## 29. 第 123 轮：**F70 落地（CIniFile 改为按成员 GBAPI）—— 总错误 2533 → 2508**

**改动**（`include/gbengine/gbVFileSystem.h`）：`class GBAPI CIniFile { … }` → `class CIniFile { … }`，
把 `GBAPI` **按成员**加到 15 个引擎侧方法上（ctor/dtor/OpenFileRead/OpenFileWrite/ReadSection/ReadStart/
ReadLine×4/WriteLine/WriteSection — 依 IAT 实测清单），并**补上 PAL3 侧实现的两个成员声明**
（`char LoadData();` / `void LoadStructuredConfig();`，注解/IDA 类型 A 级：0x004EC700 / 0x00504130）。

**指标（新目标两栏口径）**：

| | 基线 | 上一轮 | **本轮** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2425 | **2421（−23）** |
| **B. 新增编译面** | — | 6 单元 / 108 | **5 单元 / 87（−21）** |
| 总错误数 | 2446 | 2533 | **2508（−25）** |
| S2 ok / new_failures / L1 / matched | 68 / 0 / — / — | 73 / 0 / 38 / 253 | **73 / 0 / 38 / 253（无退化）** |

⇒ CIniFile 的 4 条 C2673 与其 C2039 连锁全部消失（该单元不再出现在失败清单里）；
pytest 仍为 HEAD 的 6 failed/38 passed；tracked 基线未推进。

### 第 124 轮 ROI（同一个 F70 模板，按 C2673 余量排序）
| 类 | 剩余 C2673 | 要补的 PAL3 侧声明（注解/IDA 类型 A 级） |
|---|---|---|
| **CPK** | 16（`Init` 12、`InitPackFiles` 4） | `CPK* Init();`（0x0053DB90）、`CPK* InitPackFiles();`（0x0053C250） |
| **gbOBBox** | 14（`GetBBox`） | `??? GetBBox();`（按注解签名） |
| **gbLightObj** | 5（`IsIdle` 等） | 按注解签名补 |

做法与验收完全照抄本轮：类级 GBAPI → 按成员（只给 IAT 成员）；补 PAL3 侧声明；`codegen all` +
`probe_compile s2` 量两栏错误数 + `regression_detector` / `match` 验门禁；每次只动一个类。


## 30. 第 124 轮：**F70 推广到 CPK —— 总错误 2508 → 2462（逼近基线 2446）**

**改动**（同一文件）：`class GBAPI CPK` → `class CPK`；`GBAPI` 只加到 **IAT 实测的 9 个成员**
（ctor/dtor/Load/IsValidCPK/Open/Close/DeCompress/Seek/SetOpenMode —— A 级清单来自
`%TEMP%\dd105\imports.json` 的 GBENGINE 模块）；补上 PAL3 侧实现的两个声明
`CPK* Init();`(0x0053DB90)、`CPK* InitPackFiles();`(0x0053C250)（注解/IDA 类型 A 级，不带 GBAPI）。

**指标**：

| | 基线 | 上轮 | **本轮** |
|---|---|---|---|
| A. 共享单元错误数 | 2444 | 2421 | **2421（−23）** |
| B. 新增编译面 | — | 5 单元 / 87 | **4 单元 / 41（−46）** |
| **总错误数** | **2446** | 2508 | **2462（+16，已逼近基线）** |
| C2673 族 | 0 | 19 | **19**（余 gbOBBox 14 + gbLightObj 5） |
| S2 ok / new_failures / L1 / matched | 68 / 0 / — / — | 73 / 0 / 38 / 253 | **73 / 0 / 38 / 253（无退化）** |

⇒ CPK.cpp 的 46 条错误整体消失（该单元不再出现在失败清单）；pytest 仍 6 failed/38 passed；
tracked 基线未推进。

### 第 125 轮 ROI
1. **F70 第三、四类**：`gbOBBox`（C2673 14，`GetBBox`）与 `gbLightObj`（C2673 5，`IsIdle` 等）
   —— 同样"类级 GBAPI → 按成员 + 补 PAL3 侧声明"，预期再消 ~19 条 C2673 及其 C2039 连锁
   ⇒ 新增面 41 有望降到 ~10，**总错误数可望首次低于发布基线 2446**。
2. 之后按 `error_classifier` 的 annotation_fix 前几名继续（共享单元 2421 中的主要码：C2039 / C2660 / C2027）。
3. 备注（门禁 4 的诚实记录）：CIniFile 那一批我给 15 个成员加了 GBAPI，其中
   `CloseFile`/`operator=`/部分 `WriteLine` 重载**不在 IAT 里**；本轮 CPK 已改为**只给 IAT 成员**，
   下次可把 CIniFile 收敛到同样口径（预期仅影响字节细节，不影响错误数）。


## 31. 第 125 轮：C2673 余量（gbOBBox 14 + gbLightObj 5）为何不能照抄 —— 需先做"声明同步"工具

**本轮结论：不手改**（门禁 5「禁止猜测性修改」），先把两处障碍查清并给出可执行方案。

**余量 19 条 C2673 的两个类，缺声明的方式与 CIniFile/CPK 不同**：
1. **gbOBBox**（14 条，`GetBBox`）：`include/gbengine/gbengine_types.h:211 struct GBAPI gbOBBox {…}` 的方法表里
   **没有 `GetBBox`**；而 decomp 里它的签名是 **struct-return（sret）**形态：
   `gbOBBox::GetBBox()` → `struct OBBox *__thiscall(gbOBBox *this, struct OBBox *thisa)`
   —— 隐藏的 sret 形参 + 一个**我们头里不存在的类型 `struct OBBox`**。
   ⇒ 手写声明必须把 sret 还原成"按值返回"，并确定返回类型；**猜类型违反门禁 5**。
   （注：`emit_headers.parse_signature()` **已经**实现了 sret 归一化 —— 应当复用它而不是手写。）
2. **gbLightObj**（5 条，`IsIdle`/`GetAABBox`/`GetGfxManager`/`GetCGEntry`）：这些在 decomp 里都是
   **`virtual`** 方法 ⇒ 声明它们会**占用 vtable 槽位**，插入位置/顺序必须来自
   `asm/pal3/ida_structs.json` 的 `vtables[*].slots`（否则 vtable 布局错位，反而制造字节退化）。

### 第 126 轮批次（F71：把 F70 工具化，一次解决剩余全部同类）
写 `tools/sync_gbengine_decls.py`（只读+生成建议，落地仍走人工复核）：
1. 输入：`include/gbengine/*.h`（手写声明）、`asm/pal3/ida_structs.json`（类方法 + vtable 槽）、
   `%TEMP%\dd105\imports.json`（IAT 真值清单）。
2. 对每个"在 gbengine 头里声明、又被 PAL3 实现"的类：列出 **缺声明的方法**，用
   `emit_headers.parse_signature()` 渲染成 C++ 声明（自动处理 sret/`__hidden this`），
   `virtual` 的按 **vtable 槽序**插入到对应位置，非 virtual 的追加到类尾；
   同时按 IAT 清单决定**哪些成员带 GBAPI**（类级 GBAPI 一律去掉）。
3. 验收：`codegen all` + `probe_compile s2` 量两栏错误数（预期 C2673 19 → 0、新增面 41 → ~10、
   总错误 **首次低于发布基线 2446**）+ `regression_detector` / `match` 验门禁。
4. 若无把握（例如 `struct OBBox` 归属查不清），该类**先跳过**并记录，不猜。

**本轮指标**（无功能改动，与第 124 轮相同）：A 2421（基线 2444，−23）· B 4 单元/41 · 总 **2462** ·
S2 ok 73 · new_failures 0 · L1 38 · matched 253/289。


## 32. 第 126 轮：gbOBBox 的 sret 类型查证（不可猜）⇒ **ROI 转向共享单元 top 码**

**查证结果（A 级）**：`gbOBBox::GetBBox` @**0x0052F6C0**（317 字节），decomp 签名
`struct OBBox *__thiscall(gbOBBox *this, struct OBBox *thisa)`。调用者 `CScreenMode::InitEndScreen` 显示：

```c
v9 = (gbOBBox *)operator new(0xEB8u);
if ( v9 ) BBox = gbOBBox::GetBBox(v9, v41);      // 显式 this + 独立的 sret 缓冲 v41
```

- `struct OBBox` 在**任何**头文件与 `ida_structs.json` 里都**不存在**（只有 `gbOBBox`，size=76）——是 IDA 给 sret 缓冲起的合成类型；
- 而调用点给它分配的缓冲是 **0xEB8 (3768) 字节**，远超 `gbOBBox` 的 76 字节
  ⇒ **返回类型不是 gbOBBox，也无法从现有注解推出**。
⇒ 写声明必须先读 0x0052F6C0 的**函数体**（它往 sret 缓冲写哪些字段/多大），才谈得上 A 级证据；
本轮**不猜**（门禁 5），也不做半成品。

**ROI 重排（新数据）**：C2673 余量只有 **19 条**，而共享单元（A 栏 2421）的错误码分布已是
**C2660 +8 · C2784 +6 · C2248 +6 · C2159 +4 · C2661 +3 · C2273 +2**（C2039 已被 F69/F70 清空出榜首）
—— **共享单元才是大头**。因此第 127 轮起把 ROI 切回：

1. **C2660/C2661（形参族，共 +11）**：`function does not take N parameters` —— 多为注解原型形参个数与调用不符；
   用 census 的 (unit,line,msg) 直接定位，按"注解原型 vs 二进制 ret 立即数/寄存器使用"做 A 级裁决（历史同族已成功多次）。
2. **C2784 +6 / C2248 +6 / C2159 +4 / C2273 +2**：分别用 census 消息 diff 逐条定位，能归因到注解/sizeof/`static` 的按注解批处理，不能的记入 hexrays_limit 或硬尾巴。
3. C2673 尾（19 条）：待 0x0052F6C0 函数体读完后再动 gbOBBox；gbLightObj 的 virtual 需按 `vtables[*].slots` 定序。
4. 每批仍走完整管线 + 两栏错误数 + 门禁（new_failures 0 / S2 ok 不降 / L1 不退 / 退化必须可解释）。


## 33. 第 127 轮：**F70 用到 gbVec3D —— 总错误首次低于发布基线（2418 < 2446）**

**线索**：`C2661 'Copy' : no overloaded function takes 2 parameters` **×47**（本族最大单条）。
定位到 `include/gbengine/gbengine_types.h` 的 `gbVec3D`：它只有两个**内联 1 参** `Copy`
（`Copy(const gbVec3D&)` / `Copy(const gbVec3D*)`），而调用点是 **2 参**形式
（`gbVec3D::Copy(nSrcIndex, pSrc)` —— PAL3 自己实现的 `gbVec3D *__thiscall gbVec3D::Copy(int, gbVec3D*)` @0x0042FD40，
第 105 轮就在 `pal3/src/Misc/gbVec3D.cpp` 里见过这个定义）。

**改动**：`struct GBAPI gbVec3D` → `struct gbVec3D`；`GBAPI` 按成员只给 IAT 实测的 9 个
（ctor×2 / operator= / operator*= / operator+= / CrossProduct / DotProduct / Length / Normalize）；
**补上** `gbVec3D * Copy(int nSrcIndex, gbVec3D *pSrc);`（PAL3 侧实现，不带 GBAPI）。

**指标**：

| | 基线 | 上轮 | **本轮** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2421 | **2378（−43；对基线 −66）** |
| B. 新增编译面 | — | 4 单元 / 41 | **3 单元 / 40** |
| **总错误数** | **2446** | 2462 | **2418（−28，首次低于基线）** |
| S2 ok / new_failures / L1 / matched | 68 / 0 / — / — | 73 / 0 / 38 / 253 | **73 / 0 / 38 / 253（无退化）** |

（`gbVec3D.cpp` 自身的错误也一并消失；pytest 仍 6 failed/38 passed；tracked 基线未推进。）

**剩余 C2660/C2661 池（下一批按量级）**：`'Read' 33` · `'=' 27` · `'SetParam' 17` · `'RenderGeomQuad' 17` ·
`'ReplaceTexture' 12` —— 与 `Copy` 同族（引擎类 + PAL3 侧实现/扩展的声明/原型不一致），照 F70 模板逐个吃。

### 第 128 轮 ROI
1. `C2660 'Read' : function does not take 0 parameters` ×33（`gbVFileSystem::Read` 的重载/形参问题）
2. `C2660 '=' : function does not take 2 parameters` ×27（`operator=` 声明缺失）
3. `SetParam` ×17 / `RenderGeomQuad` ×17 / `ReplaceTexture` ×12
4. C2673 尾 19（gbOBBox 需先读 0x0052F6C0 函数体；gbLightObj 需按 vtable 槽序）


## 34. 第 128 轮：C2660/C2661 剩余池的**系统性根因**：显式 this 实参 + dllimport 成员

**逐族取证（census (unit,line,msg) + 生成源码）**：

| 消息 | 量 | 首个样例 | 生成源码形态 |
|---|---|---|---|
| `'=' : function does not take 2 parameters` | 27 | CCBCamControl.cpp:654 | **`gbVec3D::operator=(&v21.Direction, ViewTarget);`** |
| `'Read' : function does not take 0 parameters` | 33 | CCBStageEffect.cpp:36 | `...->gbVFileSystem::Read();`（decomp 丢参） |
| `'SetParam'` / `'RenderGeomQuad'` / `'ReplaceTexture'` | 17/17/12 | CCBControlWindow.cpp:424 … | 同类调用形态 |

**根因**：这两族都卡在"**成员函数被当成普通函数调用**"：
1. `'='` 族：decomp 给出的是**显式 this 实参**的调用（`Class::method(obj, args)`），
   而 `operator=` 是 **IAT 里的导入成员（GBAPI/dllimport）** ⇒ MSVC 把 dllimport 成员按**无 this 的
   普通函数**处理 ⇒ 调用点多出的对象实参变成"多了一个参数" ⇒ C2660。
   **正确修法不是去掉 GBAPI**（那会让调用点从 `FF 15 <IAT>` 退化成直接调用 = 字节退化），
   而是让 codegen 把这种形态改写成 **隐式 this**：`((gbVec3D*)&v21.Direction)->gbVec3D::operator=(ViewTarget);`
   —— 与既有 `(((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::OpenFile(...)` 形态一致（stage2 的 OOP 改写，
   但 `operator=` 这类**特殊名**没走到）。
2. `'Read'` 族：`gbVFileSystem::Read()` **零实参**是 **IDB 缺原型**造成的（注解里没有 gbVFileSystem 的
   Read/Write/Seek 原型，只有手写头里有）⇒ Hex-Rays 按无参导入函数渲染。
   A 级原型来源是 **IAT 的 mangled 名**（`?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z` = `void(void*, unsigned int, gbVFile*)`）
   ⇒ 修法是在注解/IDB 层给导入成员补原型，之后调用点会**带上实参**（错误数与字节同时改善）。

**本轮指标**（无功能改动）：A **2378**（基线 2444，−66）· B 3 单元/**40** · 总 **2418（−28，低于基线）** ·
S2 ok 73/204 · new_failures 0 · L1 38 · matched 253/289 · pytest 6 failed/38 passed。

### 第 129 轮 ROI（两族一起做，量最大）
1. **stage2 OOP 改写补"特殊名 + 显式 this 实参"**：`Class::name(obj, args…)` → `((Class*)obj)->Class::name(args…)`，
   仅当 `obj` 是对象指针/地址表达式（A/B 用生成源码 + 两栏错误数验证）⇒ 预期吃掉 `'='` 27 + `SetParam` 17 +
   `RenderGeomQuad` 17 + `ReplaceTexture` 12 ≈ **73 条**。
2. **导入成员原型补全**：把 gbVFileSystem 的 Read/Write/Seek 等原型（IAT mangled 名即证据）写进注解/IDB，
   使 `'Read' 33` 的调用点带上实参（错误数 + 字节双收益）。
3. 每批照旧：完整管线 + 两栏错误数 + 四门禁；退化必须能解释否则回退。


## 35. 第 129 轮：**判定性微实验 —— 显式 this 调用形式对"普通成员"同样非法**（修法唯一化）

**实验**（`%TEMP%\dd129\explicit_this.cpp`，仓库自带 CL.EXE）：

```cpp
struct A { int v; void f(int x); A& operator=(const A& o); };
void g(A* p, A* q) { A::f(p, 1);  A::operator=(p, *q); }
```

结果：**两条都是 C2660**（`'f' : function does not take 2 parameters` / `'=' : function does not take 2 parameters`）。

⇒ **排除了"把成员改成非导入（去掉 GBAPI）就能过"的便宜路线**：VC6 对**任何成员的**
`Class::method(obj, args)` 形式都按普通函数解析，多出的对象实参必然报 C2660。
**唯一正确修法 = codegen 改写**：`Class::name(obj, args…)` → `((Class*)obj)->Class::name(args…)`
（即 `pipeline/gen/ast_transform.py::transform_oop_calls`，显式 this 分支在 **686–740 行**一带；
`operator=`/`SetParam`/`RenderGeomQuad`/`ReplaceTexture` 这些**特殊名或未覆盖形状**没有走到该分支）。
这也顺带说明：**不能**用"改声明"绕过 —— 那会同时丢掉字节忠实性与类型信息（违反项目红线）。

**本轮指标**（无功能改动）：A **2378**（基线 2444，−66）· B 3 单元/**40** · 总 **2418（−28，低于基线）** ·
S2 ok 73/204 · new_failures 0 · L1 38 · matched 253/289 · pytest 6 failed/38 passed。

### 第 130 轮批次（唯一路径，量最大）
1. 扩 `transform_oop_calls` 的显式 this 分支：覆盖 `operator=`（qualified_identifier 名含 `operator`）、
   `pointer_expression` 首参（`&v21.Direction`）、以及 `SetParam`/`RenderGeomQuad`/`ReplaceTexture` 的调用形状；
   改写为 `((Class*)obj)->Class::name(rest…)`（对象取值/取址语义不变）。
2. 预期消除：`'=' 27` + `SetParam 17` + `RenderGeomQuad 17` + `ReplaceTexture 12` ≈ **73 条**；
   之后 `'Read' 33` 需另做"导入成员原型补全"（IAT mangled 名即 A 级证据）。
3. 门禁照旧；改完必须用"共享单元错误数 + S2 ok + L1 + matched + invariants"五项对账，退化必须能解释。


## 36. 第 130 轮：把"改写为何不生效"缩到**同一函数的相邻两行**（ctor 通过、operator= 不通过）

**取证（`pal3/src/Combat/CCBCamControl.cpp` 与对应 decomp 0x005054F0）**：

```cpp
647  m_pDisplayChain = (CCBDisplayChain *)v5->m_pDisplayChain;
648  ViewTarget = (float *)(((CameraCtrl *)v6))->CameraCtrl::GetViewTarget(pTarget, &pPos);  // ← 已改写 ✓
654  gbVec3D::operator=(&v21.Direction, ViewTarget);                                        // ← 未改写 ✗（C2660）
```
decomp 原文同样是显式 this 形态：
`gbVec3D::gbVec3D(&v21.Direction, 0.0, 0.0, 0.0);`（**ctor：没有报错**）与 `gbVec3D::operator=(&v21.Direction, …)`。

⇒ **同一个类、同一个对象表达式、相邻两行**：`CameraCtrl::GetViewTarget`（普通成员）与 `gbVec3D::gbVec3D`（ctor）
**都被改写成合法形态**，而 **`operator=` 没有** ⇒ 不是"形状不匹配"，而是 `transform_oop_calls` 里针对
**特殊成员名（`operator…`）**的某个门把它挡掉了（或 `_qual`/`_is_ctor_or_dtor` 之类的判据只覆盖了 ctor/dtor）。
**这是最省力的入手点**：把 ctor/dtor 通过的路径推广到 `operator=` 等特殊名即可，改动面比新增一条规则小得多。

**本轮指标**（无功能改动）：A **2378**（基线 2444，−66）· B 3 单元/**40** · 总 **2418（−28，低于基线）** ·
S2 ok 73/204 · new_failures 0 · L1 38 · matched 253/289 · pytest 6 failed/38 passed。

### 第 131 轮批次（最锐利的入手点）
1. 在 `ast_transform.transform_oop_calls` 里定位"ctor 通过、`operator=` 不通过"的那个门
   （`_is_ctor_or_dtor`/`_qual`/`static_methods`/名字匹配），把**特殊成员名**（`operator=`/`operator+` 等）
   纳入同样的 `((T*)obj)->T::name(args)` 改写；用两个已知站点做 A/B：
   `CCBCamControl.cpp:654`（`'='`）与 `CCBCamControl.cpp` 的 `SetParam`/`RenderGeomQuad` 站点。
2. 预期消除 `'=' 27` + `SetParam 17` + `RenderGeomQuad 17` + `ReplaceTexture 12` ≈ **73 条**；
   随后再做 `'Read' 33`（导入成员原型补全，IAT mangled 名为 A 级证据）。
3. 门禁照旧，五项对账。


## 37. 第 131 轮：**F71 落地 —— 显式取址 this 形态改写 ⇒ 总错误 2418 → 2353（低于基线 93）**

**定位过程**：`transform_oop_calls` 的 `pointer_expression` 分支（826 行起）**只处理 `*ptr`**，
`&obj`（如 `&v21.Direction`）落空；而同文件的 `identifier` 分支早就在**无 ret-N 证据门**的情况下
按"Hex-Rays 显式 this 习惯"改写（668–685 行）⇒ `&obj` 与新证据并不冲突。
第 129 轮的判定性实验（VC6 对**任何**成员的 `Class::method(obj,args)` 都报 C2660）已排除"改声明"路线。

**改动**（`pipeline/gen/ast_transform.py`）：在 `pointer_expression` 分支内新增一条 arm ——
当 `_op == '&'` 且内部表达式形如 `v21.Direction` / `this->m_v`（正则 `^[A-Za-z_][\w\.\[\]\->]*$`）时，
改写为 `((Cls *)&obj)->Cls::method(rest)`（this 值不变、调用目标不变）。

**指标**：

| | 基线 | 上轮 | **本轮** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2378 | **2314（−64；对基线 −130）** |
| B. 新增编译面 | — | 3 单元 / 40 | **3 单元 / 39** |
| **总错误数** | **2446** | 2418 | **2353（−65；对基线 −93）** |
| **S2 ok** | 68 | 73/204 | **74/204（+1，无退化）** |
| new_failures / L1 / matched | 0 / — / — | 0 / 38 / 253 | **0 / 38 / 259（+6）** |
| unmatched | — | 36 | 37（**可解释**：多一个单元进入编译 ⇒ 多 1 个无对应 exe 符号；matched 同期 +6） |
| pytest | — | 6 failed/38 passed | **6 failed/38 passed（不变）** |

`C2660/C2661` 榜首的 `'=' 27` 已清零；剩余 `'Read' 33` · `'SetParam' 17` · `'RenderGeomQuad' 17` · `'ShowWindow' 14`。

### 第 132 轮 ROI
1. `SetParam` / `RenderGeomQuad` / `ReplaceTexture`（17/17/12）：查它们的首参形状（可能不是 `&obj` 而是
   `this->m_x`、`(*pp)` 或带下标），按同一约定扩 arm；每次只扩一种形状并用两栏错误数 + 四门禁验证。
2. `'Read' 33`：导入成员原型补全（`?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z` = A 级证据）。
3. C2673 尾 19（gbOBBox sret / gbLightObj virtual 槽序）。


## 38. 第 132 轮：**F72 落地 —— `*简单表达式` 首参的显式 this 改写 ⇒ 总错误 2353 → 2339**

**定位**：`transform_oop_calls` 的 `pointer_expression` 分支里，`_op == '*'` 那条 arm 的
准入条件是 `_this_consistent`——即"被调方函数体尾部 `ret N` 的字节数 == （实参个数−1）×4"。
这个证据**只能从反编译出的函数体里取**；而 `ReplaceTexture` / `SetParam` 等的被调方是
**gbengine 导入成员（没有函数体）** ⇒ `_ret_param_slots()` 恒为 `None` ⇒ 该 arm 对整族**永远不可达**。
同文件的 `identifier` 分支（668–685 行）与第 131 轮新增的 `&obj` 分支都没有这个门，
按的是同一条"Hex-Rays 显式 this 习惯"约定 ⇒ 门本身是多余的。

**改动**（`pipeline/gen/ast_transform.py`）：在 `pointer_expression` 分支内新增
`_op == '*' and not _this_consistent and re.match(r'^[A-Za-z_][\w\.\[\]\->]*$', _ptr_inner)`
的 arm，改写为 `(*expr)->Cls::method(rest)`（this 值不变、调用目标不变）。
只覆盖"简单标识符/成员路径"取指，`*(T**)x` 这类复杂表达式仍保持原样交给 MSVC 报错。

**指标**：

| | 发布基线 | 上轮(131) | **本轮(132)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2314 | **2300（−14；对基线 −144）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2353 | **2339（−14；对基线 −107）** |
| **S2 ok** | 68 | 74/204 | **74/204（不变）** |
| new_failures / L1 / matched | 0 / — / — | 0 / 38 / 259 | **0 / 38 / 259** |
| unmatched | — | 37 | **37** |
| invariants（阻塞项/A/B/D） | — | 197 / 131 行 · 56 · 10 | **197 / 131 行 · 56 · 10（不变）** |
| pytest | 6 failed/38 passed | 6 failed/38 passed | **6 failed/38 passed** |

**逐轮 A/B 归因（快照 20260920_070855 = 第 131 轮，2353 条 → 本轮 census 2339 条）**：
`cl.exe` 原始报文**消失 15 条 / 新增 1 条**，逐条可指认——消失的是 14 条
C2660/C2661（`GetChildCount`/`GetChildAt`/`SetTextParam`/`SetText`/`IsTaskFinished`/
`LoadFromFile`/`ReplaceTexture` 等的 `*ptr` 首参站点）+ 1 条 `C1003`；
新增的 1 条是 `CCBStage.cpp` 的 `C2440 '=' ... (__thiscall CCBStage::*)(float)`。

**这 1 条新增属于 `cl.exe` 的 100 错误截断窗口位移，不是退化**：
`CCBStage.cpp` 两轮的真实错误条目都是 **101 条**（上轮 = 101 真错 + `C1003` 收尾行 = 102 行；
本轮 = 101 行）。上轮该文件在第 100 条处被 `C1003` 截断，一条 `C2440` 落在窗口之外；
本轮少了一条 `IsTaskFinished` ⇒ 窗口内**多显示**那条 `C2440`。
逐码核对：`C2661 1 → 0`、`C1003 1 → 0`、`C2440 12 → 13`，其余 18 个错误码**逐条相同**。

**剩余调用族（本轮 census，码 + 符号）**：
`C2039 __vftable 82` · `C2664 '=' 37` · `C2039 TaskMgr_SceneObjParam_SceneObj 35` ·
`C2660 Read 33` · `C2664 void(char*,unsigned long,int*,ArcSceneMonster*) 33` ·
`C2660 SetParam 17` · `C2660 RenderGeomQuad 17` · `C2660 ShowWindow 14` ·
`C2660 PAL_GDB::~PAL_GDB 14` · `C2660 NewIndexPool 14` · `C2673 GetBBox 14`。

### 第 133 轮 ROI（已在本轮定位）
`'Read' 33` 的根因**不在 codegen**：见 §39。


## 39. 第 133 轮：**F73 根因锁定 —— gbengine 导入槽上的"退化原型"吞掉真实参数**

### 证据链（全部 A 级，均可在 IDB 里复现）
1. **现象**：33 处调用点的伪代码是 `gbVFileSystem::Read(g_pVFileSys);`——**三个实参凭空消失**，
   于是生成 C++ 报 `C2660: 'Read' : function does not take 0 parameters`。
   反编译产物（`asm/pal3/decomp/PAL_GDB_PAL_GDBvoid_00478e00.json` 等 15 个文件）里就已经是 0 参。
2. **二进制里参数是在的**（反汇编，0x004BB050 `RenderTarget::ReadVFile`）：
   ```
   push edi (pFile) / push 40h (size) / push esi (buf) / mov ecx,[eax] / call ebx
   ```
   ⇒ 不是"原程序没传参"，而是**反编译侧丢的**。
3. **IDA 自己知道正确签名**：同一条 `call` 的注释就是
   `gbVFileSystem::Read(void *,uint,gbVFile *)`（来自修饰名解算）。
4. **对照实验**：同类成员 `Seek`/`TellPos`/`Write`/`OpenFile` 的 IAT 槽类型为 `<none>` ⇒
   Hex-Rays 回退到修饰名 ⇒ 参数**完整**（`Seek(g_pVFileSys, v1, 0, 1)`）。
5. **槽类型才是错的那个**（IDB 实测）：
   `?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z` 的槽 = `void __thiscall(gbVFileSystem *__hidden this)`
   ——**零栈参**。Hex-Rays 对 `call ds:<slot>` 优先采用槽类型 ⇒ 参数被吞。
   同类退化槽还有 `?TransformPlane@gbMatrix4@@QAEXQAM@Z`、`?Transform@gbMatrix4@@QBEXPBUgbVec3D@@PAU2@@Z`。
6. **判定性实验（IDB 副本上做，不落盘）**：把该槽设为
   `void (__thiscall *)(gbVFileSystem *, void *, unsigned int, gbVFile *)` 并
   `clear_cached_cfuncs()` 后重反编译，33 处的参数**全部回来**：
   `Read(g_pVFileSys, this, 0xA0u, v3)` / `Read(g_pVFileSys, &this->m_fRenderX, 4u, pFile)`。
   （注意：`idc.SetType` 对导入槽返回失败，必须用 `ida_nalt.set_tinfo`；且 Hex-Rays 有缓存，
   必须 `clear_cached_cfuncs()` 才看得到效果。）

### 做法（注解/IDA 层，符合"IDA 层能解决的问题在 IDA 层解决"）
`pipeline/ida/apply_annotations.py` 新增 `_fix_gbengine_import_slots()`，在 `apply` 的**最后**
（`save_database` 之前，避免被其它类型写入覆盖）执行：
对 GBENGINE 模块的每个导入名，若修饰名是**非静态 `__thiscall` 成员**（`@@[QUI]?E`）且
解出的参数个数**多于**槽里显式写出的栈参个数，则用 `ida_nalt.set_tinfo` 把槽类型写成
`ret (__thiscall *)(Cls *, <修饰名参数表>)`。签名**完全来自修饰名**（VC6 mangling 自带参数表），
不做任何推断；参数个数不比修饰名少的槽一律不碰（幂等、可重跑、可审计——每条改动都打日志）。
另一条判据覆盖"参数个数碰巧够但**调用约定写错**"：`?RenderGeomQuad@gbDynVertBuf@@` /
`?RenderGeomQuadViaStrip@…` 的槽被写成 `__stdcall`（this 从参数表里消失）⇒ 同样按修饰名改写。

**工具副产物（门禁健康）**：`tools/compile_regression.py` 与 `tools/audit_layout.py` 的结论行用
emoji（✅/⚠️/🎉），GBK 控制台下 `print` 抛 `UnicodeEncodeError` ⇒ **门禁自己以非零退出**，
被 `cli.py` 读成"有退化"。两处加 `sys.stdout.reconfigure(encoding='utf-8')`
（实测：compile_regression 现在 `Net change: +7 files`、退出码 0；audit_layout `PASSED with 38 warnings`、退出码 0）。

### 实测结果（第 133 轮）

| | 发布基线 | 上轮(132) | **本轮(133)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2300 | **2247（−53；对基线 −197）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2339 | **2286（−53；对基线 −160）** |
| **S2 ok** | 68 | 74/204 | **75/204（+1）** |
| new_failures | 0 | 0 | **0**（`compile_regression.py` 独立复核：0 regressions） |
| L1 | — | 38 | **38（不回退）** |
| matched / partial / unmatched | — | 259 · 191 · 37 | **263 · 194 · 40** |
| invariants（阻塞项 / A / B / D） | — | 197 / 131 行 · 56 · 10 | **197 / 131 行 · 56 · 10（不变）** |
| audit_layout | — | — | **PASSED with 38 warnings** |
| pytest | — | — | e2e 冒烟 **4 passed**；`pytest tests -q --continue-on-collection-errors` = 35 failed / 76 passed / 11 skipped / 2 collection errors（失败全在 pal3a/PE/symbol-index/项目配置区域，与本轮改动无关） |

**逐轮 A/B 归因（第 132 轮 census 2339 → 本轮 2286，消失 54 / 新增 1）**：
- 消失：`C2660 'Read'` **−33**、`C2660 'RenderGeomQuad'` **−17**、`'Transform' −1`、`'TransformPlane' −1`、
  `C2664 void __thiscall gbDynVertBuf::… −1`（F73 的 5 个槽全部兑现）；
- 新增：`PAL3.cpp` 的 `C2440 '=' : cannot convert from 'char *' to 'int'` ×1 —— 同一文件
  **两轮都是 101 条**（`TransformPlane` 的 C2660 退场、这条 C2440 进场），属 F73 恢复真实参数后
  Hex-Rays 对同一表达式重新定型所致的**等量替换**，不是净退化。
- `matched 259→263 · unmatched 37→40`：本轮有 **7 个函数**因所在单元恢复编译而首次进入符号普查
  （+4 有成对 exe 符号 = matched，+3 没有 = unmatched）；L1 仍 38 ⇒ 这些新可见函数里没有字节全同者。

### 第 134 轮 ROI（按剩余错误量 × 证据强度）
1. `C2664 void (char*,unsigned long,int*,ArcSceneMonster*) : from 'void *' to 'unsigned long'`（33）
   + 同族 `void (unsigned long,int)`（19）/`void (unsigned long,unsigned long)`（17）≈ **69 条**：
   都是**合成 vtable stub 的形参类型**（`pal3_vtbl_unk_*`）与实参不兼容，属 codegen 侧可一次修的一族。
2. `C2039 '__vftable' is not a member of 'UIXxx'`（82）：**是 P1(a) 的有意代价**（见 §P1(a) 注释：
   `__vftable` 占位被删以保布局；真修法=按槽号发射虚调用，`vtbl_defs.h` 方案已废弃）⇒ 本轮不碰。
3. `C2039 TaskMgr_SceneObjParam_SceneObj`（35，单文件）：`&this->SceneObj::TaskMgr_SceneObjParam_SceneObj::m_nTodo_000 + N`
   ——IDA 侧嵌套类型名进了伪代码，需要"嵌套类型别名"或 stage4 改写，先定性再动手。
4. `C2660 ShowWindow`（14）/`NewIndexPool`（14）/`CreateFromMemory`（12）/`~PAL_GDB`（14）：
   已抽样定性（§39 附注）——`~PAL_GDB` 的**注解名是错的**：0x00478FD0 的函数体是
   "在 `m_RoleData[i].id == nVal` 里查找"，**不是析构函数**（析构不能有参数，体里也没有析构动作），
   同类"带参数的析构名"注解共 **12 处**（census 里因此产生的错误 20 条）⇒ 需按函数体证据改名。


## 40. 第 134 轮：**F74 落地 —— 间接调用实参显式转换 ⇒ 总错误 2286 → 2216（−70，零新增）**

### 量化（先量后修）
报文里 **callee 名是一个类型串**（形如 `'void (char *,unsigned long,int *,class ArcSceneMonster *)'`）
的错误 = **经函数指针 cast 的间接调用**：共 **175 条 / 38 个文件**，是当时剩余错误里最大的单一机制。

### 根因
Hex-Rays 把间接虚调用渲染成显式 cast：
```c
(*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v22 + 16))(
    v8 + 215804, *(&g_ArcSceneMonsterTable + nVal), &v39, this);
```
VC6 **按 cast 的原型逐个检查实参**：第 2 实参 `*(&g_ArcSceneMonsterTable + nVal)`
（`g_ArcSceneMonsterTable` 在 `include/pal3/globals.h:38` 声明为 `extern void *` ⇒ `&G+n` 是 `void**`、
解引用是 `void *`）传不给形参 `_DWORD` ⇒ C2664。原源码在这里带显式转换，Hex-Rays 丢了。

### 改动（`pipeline/gen/stages/stage4_substitution.py`，与既有 C2440 赋值批同一判据）
1. 新增 `_collect_indirect_call_cast_edits()`：识别 `call_expression → parenthesized_expression →
   pointer_expression → cast_expression → type_descriptor → abstract_function_declarator → parameter_list`，
   把每个形参类型与实参推断类型对比；**只在一侧是指针、另一侧是整数**时插入显式转换
   `(PTEXT)(ARG)`（转换本身不产码 ⇒ 字节等价）。
2. `_expr_type` 补两处类型推断缺口（否则这一族永远判不出来）：
   - `*(&X + n)` / `*(&X)` 惯用法：元素类型 = **X 自身的类型**（只看加法的左操作数）；
   - `this` → 指针（`ctx.cls_name *`）；标识符回退到 **`include/pal3/globals.h` 的 `extern` 声明表**
     （部分全局只在这个手写头里声明，`store.global_types` 里没有——这正是 33 条 ArcSceneMonster 家族卡住的点）。

### 安全性论证（为什么不可能碰到已通过的字节）
该转换只在**实参/形参类型不兼容**时插入；不兼容的站点一定编译失败 ⇒ 只出现在失败单元里，
而失败单元本来就产不出 `.obj`。实测印证：`matched 263/303`、**L1 38**、`partial 194`、`unmatched 40`
与上一轮**逐项相同**。

### 实测结果

| | 发布基线 | 上轮(133) | **本轮(134)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2247 | **2177（−70；对基线 −267）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2286 | **2216（−70；对基线 −230）** |
| **S2 ok** | 68 | 75/204 | **75/204（不变）** |
| new_failures | 0 | 0 | **0**（`compile_regression.py`：0 regressions，退出码 0） |
| L1 / matched / partial / unmatched | — | 38 · 263 · 194 · 40 | **38 · 263 · 194 · 40（逐项不变）** |
| invariants（阻塞项 / A / B / D） | — | 197 / 131 行 · 56 · 10 | **197 / 131 行 · 56 · 10（不变）** |
| audit_layout | — | PASSED 38 warnings | **PASSED 38 warnings** |
| 错误分类（annotation/codegen/hexrays/idb/unknown） | — | 52/29/37/2/9 | **53/27/38/2/9** |

**逐轮 A/B 归因（第 133 轮 census 2286 → 本轮 2216）：消失 70 / 新增 0。**
消失逐条可指认，全部是"经函数指针 cast 的间接调用"族：
`ArcSceneMonster.cpp` 33+7+2+2+1、`UITitle_XJTM.cpp` 14、`UIBigMap.cpp` 5+3、`MainEquipUI.cpp` 1、
外加 `CEffMgr.cpp` 一条 `C2440 '=' : from 'class CEffMgr *const' to 'unsigned long'`。
**新增 0 条** ⇒ 无截断位移、无新错误。

### 第 135 轮 ROI
1. `void (unsigned long,int)`（19）+ `void (unsigned long,unsigned long)`（17）= **36 条**：
   同一个 F74 机制，但 callee 不是显式 cast 而是**函数指针型局部变量**（`(**v5)(v5, 1)`，
   `v5 = *(void ( ****)(_DWORD, int))v4;`）。缺的是"局部变量的完整 fnptr 类型文本"
   （现有 `_declared_local_types` 只记 `*`，丢掉参数表）⇒ 扩一个 `_declared_fnptr_params()` 即可。
2. `'=' / '+=' : from 'float *'|'int' to 'const struct gbVecND &'`（17+8+8）= **33 条**：需先定性
   `gbVecND` 是什么（IDA 侧的基类名？）以及为何实参是 `float *`。
3. CRT/Win32 参数族：`MessageBoxA` 12 · `sprintf` 8 · `_mbsrchr` 6 · `ProcessKeyboard` 8 ·
   `PushMatrixStacks`/`PopMatrixStacks` 14 —— 形参类型与实参不兼容（多为注解/签名批）。


## 41. 第 135 轮：**F75 落地 —— 函数指针型局部变量的间接调用 ⇒ 2200（−16）**，含一次"0 收益"的自我纠正

### 目标族（第 134 轮 ROI 第 1 条）
`void (unsigned long,int)`（19）+ `void (unsigned long,unsigned long)`（17）= 36 条：
同一个 F74 机制，但 callee 不是显式 cast 而是**函数指针型局部变量**：
```c
void ( ***v5)(_DWORD, int);   // ecx
v5 = *(void ( ****)(_DWORD, int))v4;
(**v5)(v5, 1);                // ← 第 1 实参 v5 是 `void(***)(...)`，形参是 `_DWORD`
```

### 改动（`pipeline/gen/stages/stage4_substitution.py`）
新增 `_declared_fnptr_params(tree)`：扫描 `declaration`，凡声明器里有 `function_declarator`
+ `parameter_list`（即"指向函数的指针"）的变量，记下 `{变量名: [形参类型文本]}`；
F74 的收集器据此对第二种形态（`(**v5)(...)` / `v5(...)`）套用同一套"指针↔整数"判定与显式转换插入。

### 第一次尝试 = **0 收益**（负结果，值得存档）
第一版直接在 `_apply()` 里用 `_expr_type(an)` 取实参类型 ⇒ 管线里**一个转换都没插**，
两栏错误数 2216 → 2216（delta 0）。
根因：`_declared_local_types` 的 `type_text_of()` 只拼接 `primitive_type` 与 `pointer_declarator`，
对 `void ( ***v5)(_DWORD, int);` 只看得见返回类型 `void` ⇒ `_classify_type_text('void')` 返回
`(None,'void','void')` ⇒ 判定为"类型未知"⇒ 不插。
（我最初的**整文件**验证之所以"看起来通过"，是因为同一文件里 `v5` 在另一个函数里被声明成别的类型，
`_declared_local_types` 用**赋值**语义（后写覆盖）⇒ 偶然拿到了 pointer 分类。**逐函数**跑就复现不了。）
修法：形参表来自 fnptr 表的实参（其文本正是该变量名）**直接判为指针**，不再依赖 locals_。

### 实测结果（第二次跑）

| | 发布基线 | 上轮(134) | **本轮(135)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2177 | **2161（−16；对基线 −283）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2216 | **2200（−16；对基线 −246）** |
| **S2 ok** | 68 | 75/204 | **76/204（+1）** |
| new_failures | 0 | 0 | **0**（`compile_regression.py`：0 regressions） |
| L1 / matched / partial / unmatched | — | 38 · 263 · 194 · 40 | **38 · 265 · 196 · 40** |
| invariants（阻塞项 / A / B / D） | — | 197 / 131 行 · 56 · 10 | **197 / 131 行 · 56 · 10（不变）** |
| audit_layout | — | PASSED 38 warnings | **PASSED 38 warnings** |
| 错误分类 | — | 53/27/38/2/9 | **53/25/39/2/9** |

**逐轮 A/B 归因（第 134 轮 census 2216 → 本轮 2200）：消失 22 / 新增 6。**
- 消失 22：`void (unsigned long,int)` / `int (unsigned long,int)` / `void (unsigned long,unsigned long)`
  族（`CCBParabolaWindow` · `PAL3` · `PalScript` · `StateUI` · `free_functions` · `CEffMgr` ·
  `BINK` · `CCBEditor` · `GeomNode`）。
- 新增 6 **全部是 `cl.exe` 100 错误截断窗口位移，逐文件净额为零**（与 §F "错误普查不是树的纯函数" 同因）：
  - `free_functions.cpp`：两轮都是 **102 条且都带 `C1003`** —— 少 4 条 C2664 ⇒ 窗口内多显示 4 条 C2679
    （C2679 33→37、C2664 20→16）；
  - `PAL3.cpp`：两轮都是 **101 条** —— C2664 12→11、C2440 28→29。
- `matched 263→265 · unmatched 40→40`：符号普查 303→305（+2 个函数因所在单元恢复编译而首次可见，
  且两个都成对 ⇒ matched +2、unmatched 不变）。

### 第 136 轮 ROI
1. **具名被调方的"指针/整数实参"族（`_named.py` 实测 215 条中最大几族）**：
   `MessageBoxA` 12（p2 `int *`→`const char *`）· `sprintf` 9（p2）· `_mbsrchr` 6（p1）·
   `lstrcpyA` 3（p1）—— CRT/Win32 原型是**固定且可枚举**的（A 级），可沿用 F74 的"插显式转换"判据，
   只是形参表来自一张小表而不是 decomp 的类型串。
2. `gbVec3D` 赋值族 41 条（`'=' 17+8+4` · `'+=' 8+4`：实参是 `float *`/`int`，形参是 `const gbVec3D &`）
   —— 对"引用形参 + 指针实参"可改写为 `*(gbVec3D *)arg`（传的是同一个地址 ⇒ 字节等价）。
3. `~PAL_GDB` 等"带参数的析构名"注解 12 处（census 影响 20 条）：按函数体证据改名（0x00478FD0 实为查找函数）。


## 42. 第 136 轮：**F76 落地 —— CRT/Win32 固定原型下给实参插显式转换 ⇒ 2187（−13）**

**目标族**：`MessageBoxA` 12（p2 `int *`→`const char *`）· `sprintf` 9（p2）· `_mbsrchr` 6（p1）·
`lstrcpyA` 3（p1）。这些原型**不是我们的注解**（系统/CRT 固定 API，A 级可枚举）⇒ "注解改错"的解释不适用，
错的是 Hex-Rays 给实参推断出的类型。

**改动**（`pipeline/gen/stages/stage4_substitution.py`）：新增 `_CRT_ARG_TYPES` 小表
（`MessageBoxA/W` · `sprintf` · `lstrcpyA/lstrcatA/lstrlenA` · `_mbsrchr/_mbschr` ·
`strcpy/strcat/strlen/atoi/atof`，逐函数给"第 N 个形参的声明类型"）
与 `_collect_crt_arg_cast_edits()`：当该实参的推断类型是指针/整数且与声明类型不同（指针基类型不同或整数）时，
插一个显式转换（`(const char *)arg`）。结构体/浮点实参一律跳过 ⇒ 不可能产生非法转换；
在**本来能编译**的站点最多插入恒等转换（不产码、不改字节）。

### 实测结果

| | 发布基线 | 上轮(135) | **本轮(136)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2161 | **2148（−13；对基线 −296）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2200 | **2187（−13；对基线 −259）** |
| **S2 ok** | 68 | 76/204 | **77/204（+1）** |
| new_failures | 0 | 0 | **0**（`compile_regression.py`：0 regressions） |
| L1 / matched / partial / unmatched | — | 38 · 265 · 196 · 40 | **38 · 266 · 197 · 42** |
| invariants（阻塞项 / A / B / D） | — | 197 / 131 行 · 56 · 10 | **197 / 131 行 · 56 · 10（不变）** |
| audit_layout | — | PASSED 38 warnings | **PASSED 38 warnings** |
| 错误分类 | — | 53/25/39/2/9 | **53/23/40/2/9** |

**逐轮 A/B 归因（第 135 轮 census 2200 → 本轮 2187）：消失 29 / 新增 16。**
逐单元核对（只有 7 个单元发生变化）：改善 `CCBStageCam −7` · `PAL_GDB −3` ·
`CCBCamControl/ArcSceneObject/DealData/UISceneFrm 各 −1` = −14；
`CCBStage.cpp` **101 → 102（+1）**。16 条"新增"全部是 **`cl.exe` 100 错误截断窗口位移**：
- `CCBUI.cpp`：两轮都是 **102 条且都带 `C1003`** —— 少了 12 条（`_mbsrchr` 6 · `MessageBoxA` p2 5 ·
  `sprintf` p2 1）⇒ 窗口内多显示 12 条（`C2227 ->ShowWindow` 6 · `__vftable` 3 · `C2440` 2 ·
  `MessageBoxA` p3 1），**文件净额 0**；
- `CCBStage.cpp`：101（无 C1003）→ 102（有 C1003）—— 少 1 条 `sprintf` ⇒ 正好落到 100 条上限，
  cl 追加 `C1003` 本身并放行一条原本被截断的 `C2059`；**净 +1 = `C1003` 那一行**。
⇒ 无任何真实退化；`matched 265→266`（符号普查 305→308：+3 个新可见函数，其中 1 个成对、2 个无对应
exe 符号 ⇒ `unmatched 40→42`）。

### 第 137 轮 ROI（按"证据强度 × 剩余量"）
1. `gbVec3D` 赋值族 **48 条**（`'=' 17+8+4` · `'+=' 8+4`，实参 `float *`/`char *`/`int`，形参 `const gbVec3D &`）：
   形态已抽样（`(((gbVec3D *)&v21.Direction))->gbVec3D::operator=(ViewTarget);`）——
   需先判定"实参本该是什么"（`ViewTarget` 是 `CameraCtrl::GetViewTarget` 的返回值，
   其返回类型注解可疑），再决定是"注解修返回类型"还是"引用形参 + 指针实参 ⇒ `*(gbVec3D *)arg`"。
2. `PushMatrixStacks`/`PopMatrixStacks` 22 条：实参是 `&local`/`char[4]` 而形参声明为 `int`
   ⇒ **形参声明可疑**（真参数很可能是指针）⇒ 属注解批，须有函数体/调用点证据，不能靠插转换掩盖。
3. `~PAL_GDB` 等"带参数的析构名"注解 12 处（census 影响 20 条）。


## 43. 本会话收敛总结（第 132–136 轮）

### 指标（对发布基线 `20260919_000552`，全程未推进任何 tracked 基线）

| | 基线 | 132 轮前 | **136 轮后** | 本会话净变化 |
|---|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2314 | **2148** | **−166** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** | 0 |
| **总错误数** | **2446** | 2339 | **2187** | **−152（对基线 −259）** |
| **S2 ok** | 68 | 74/204 | **77/204** | **+3** |
| new_failures | 0 | 0 | **0** | 0（每轮 `compile_regression.py` 独立复核） |
| **L1** | — | 38 | **38** | 0（**从未回退**） |
| matched / partial / unmatched | — | 259 · 191 · 37 | **266 · 197 · 42** | +7 · +6 · +5（全部为"新可见函数进入普查"，见各轮归因） |
| invariants 阻塞项 | — | 197 | **197** | 0（A 131 行/25 文件 · B 56 · D 10，均未变） |
| audit_layout | — | PASSED 38 warnings | **PASSED 38 warnings** | 未变 |

### 本会话落地的机制（全部有 A/B 数字与证据链）
1. **F72**（codegen）：`transform_oop_calls` 的 `*简单表达式` 首参 arm 不再要求 ret-N 证据（导入成员没有函数体 ⇒ 该门恒不可达）⇒ **−14**。
2. **F73**（IDA 层）：IAT 槽上的"退化原型"会盖掉 Hex-Rays 从修饰名解出的签名（`Read` 33 处实参被吞）；
   新增 `_fix_gbengine_import_slots()`，按**修饰名**纠正 5 个槽（含约定写错的 `RenderGeomQuad*`）⇒ **−53**，S2 +1。
3. **F74**（codegen）：经函数指针 cast 的间接调用按形参类型给实参插显式转换（175 条机制）⇒ **−70，零新增**。
4. **F75**（codegen）：同一机制推广到函数指针型局部变量（`(**v5)(v5,1)`）⇒ **−16**（含一次 0 收益的自我纠正）。
5. **F76**（codegen）：CRT/Win32 固定原型下给实参插显式转换 ⇒ **−13**。
6. **工具/门禁**：`compile_regression.py` 与 `audit_layout.py` 的结论行 emoji 在 GBK 控制台抛
   `UnicodeEncodeError` ⇒ **门禁自己崩**；两处加 `sys.stdout.reconfigure(encoding='utf-8')`（现均退出码 0）。
7. **知识库**：`docs/knowledge/gotcha_import_slot_prototype_overrides_hexrays_signature.md`（含"改槽必须用
   `ida_nalt.set_tinfo` + `clear_cached_cfuncs`"与"导入名回调拿到的是修饰名、不含括号"两个坑）。

### 剩余（按收敛判据的诚实评估）
- **已耗尽**：C2660/C2661 形参族在"调用形态"这一侧（-156 对基线）、导入槽签名族、间接调用实参族、
  结构尺寸链族（F68）、归属族（F56）、vftable 发射族（F59/F11/F12）。
- **剩余大头**（均有明确下次入手点，见 §42 第 137 轮 ROI）：
  `C2039 __vftable 82`（**P1(a) 的有意代价**：为保布局删掉 +0 占位；真修法=按槽号发射虚调用，
  `vtbl_defs.h` 方案已废弃）、`gbVec3D` 赋值族 48、`TaskMgr_SceneObjParam_SceneObj` 35、
  `C2660 ShowWindow/NewIndexPool/…` 与"带参数的析构名"注解族 20+。
- **硬尾巴**：`hexrays_limit` 40 个单元（30.5%）与寄存器分配/调度 partial（197 个，
  opcode/flow 75 · register 49 · immediate 30 · operand shape 19 · this/member 16 · this-register 2）。


## 44. 第 137 轮：**F77（导入槽"占位形参"）+ F78（引用形参实参取址）⇒ 2187 → 2156（−31），L1 38 → 40**

### F77 根因（本轮真正的大鱼）
`??4gbVec3D@@QAEXABU0@@Z`（`gbVec3D::operator=(gbVec3D const &)`）的导入槽类型是
`int __thiscall(_DWORD, _DWORD)` —— **参数个数对，但形参类型是占位符 `_DWORD`**。
Hex-Rays 于是认为该形参是整数/指针，把调用点写成 `gbVec3D::operator=(&v21.Direction, ViewTarget)`
（直接把 `float *` 传进去）⇒ 生成头里声明是 `const gbVec3D &` ⇒ 一整族 C2664
（`'=' 17+8+4`、`'+=' 8+4` ≈ **52 条**，是当时最大的具名族）。第 133 轮的 F73 只比"参数个数"，
所以这一族被漏掉。

**改动**（`pipeline/ida/apply_annotations.py::_fix_gbengine_import_slots`）：新增第三条判据——
槽里**显式列出的参数类型是 `_DWORD`/`_UNKNOWN`/`_QWORD`/`int`，而修饰名在该位置是指针或引用** ⇒ 按修饰名改写。
（槽里显式列 this 时参数个数比修饰名多 1，两种排版都做了对齐处理。）
实测修正 **5 个槽**：`?SetVariant@gbRenderEffect` · `??YgbVec3D` · `??4gbMatrix4` ·
`?GetBlend@gbVisNode` · `??4gbVec3D`。

**F77 单独的净效果 = +1（2187 → 2188）**：错误"换了个报法"——消失 52 / 新增 52
（`from 'float *'` → `from 'const struct gbVec3D *'`），另外 `RenderTarget2.cpp` **+1 条**：
`?GetBlend@gbVisNode` 的槽被改正后，Hex-Rays 在该处改写成
`((int (*)(int, float *))gbVisNode::GetBlend)(v10, &v14)` —— 取成员函数名的 cast 拼法 VC6 不收
（`C2440 'type cast' : cannot convert from '' to 'int (__cdecl *)(int,float *)'`）。
**这是可解释的单点副作用，且修法已知**（把"cast 成员函数名"形态改写为
`((gbVisNode *)v10)->gbVisNode::GetBlend(&v14)`，即 F71/F72 的同族改写；留作 ROI）。
F77 的真正价值是**语义/类型正确化**：`ViewTarget` 由 `float *` 变成 `const gbVec3D *`，
调用点从"浮点指针算术"变成 `ViewTarget->x` / `++ViewTarget` / `ViewTarget[-1].y`。

### F78：引用形参 + 同类指针实参 ⇒ `*(arg)`（codegen）
F77 之后错误变成 `cannot convert parameter 1 from 'const struct gbVec3D *' to 'const struct gbVec3D &'`。
**为什么不在 IDA 侧直接把槽设成真引用**：实测 IDA 的 Python 类型 API **构造不出引用类型**——
`ida_typeinf.parse_decl` 与 `idc.SetType` 都把 `T &` 落成 `T *`（`dstr()` 打印 `*`），也没有 `create_ref`。
所以在生成侧做**地址等价**改写：传给 `const T &` 的 `*(p)` 与传给 `const T *` 的 `p`
是同一条指令、同一个地址 ⇒ 字节等价（与 F71/F72 同性质的适配）。
**门**：被调必须是**运算符**（C++ 约定取 `const T &`）、实参必须是指向**被调类自身**的指针、
显式 this 形态的首参（接收者）不碰。实测全仓命中 **46 处 / 9 个文件**。

**顺带修掉两个真实的工具缺口（否则 F78 根本不触发）**：
1. **tree-sitter-cpp 对 `ptr->Class::method(args)` 产出 `ERROR` 节点**
   （AST：`call_expression → parenthesized_expression + ERROR('->gbVec3D::operator=') + argument_list`）
   ⇒ 任何走 AST 的 pass 对"限定成员调用"都是瞎的。F78 现在从 `ERROR` 子节点里取类名/方法名。
2. **`_type_text_of` 漏了 `struct_specifier`**：`const struct gbVec3D *ViewTarget;` 的类型文本
   退化成 `'*'`（类名丢失）⇒ 依赖"指针指向哪个类"的判据恒不成立。已改为取 specifier 的 `name`，
   并把 `_declared_local_types` / `_param_types` 两处重复实现合并为一个函数。
   附带把 `_expr_type` 的取址分支补上"被指向的类名"（`&v19` ⇒ `('pointer','', 'gbVec3D')`）。

### 实测结果（F77+F78 一个批次）

| | 发布基线 | 上轮(136) | **本轮(137)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2148 | **2117（−31；对基线 −327）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2187 | **2156（−31；对基线 −290）** |
| **S2 ok** | 68 | 77/204 | **78/204（+1）** |
| new_failures | 0 | 0 | **0**（`compile_regression.py`：0 regressions） |
| **L1** | — | **38** | **40（+2）** |
| matched / partial / unmatched | — | 266 · 197 · 42 | **275 · 203 · 43** |
| invariants / audit_layout | — | 197 / PASSED 38 warn | **197 / PASSED 38 warn（不变）** |
| 错误分类 | — | 53/23/40/2/9 | **53/21/41/2/9** |

**逐轮 A/B（137a=census 2188 → 137b=2156）：10 个单元改善、0 个单元变差**：
`UIScene −10` · `UIBigMap −7` · `Actor −5` · `PalScriptMgr −3` · `ScriptSystem −2` ·
`CCBCamControl/CCBStage/CCBStageShadow/RoleSystem/UIManager 各 −1` = **−32**；
`CCBStage`、`RoleSystem` 同时从"带 `C1003` 截断"变成不带（各自 102→101）。
`L1 +2`：F77 带来的类型正确化让两个函数首次字节全同（`matched 266→275`，符号普查 308→318）。

### 第 138 轮 ROI（重排后）
1. `C2039 GlowObj` 12 · `_nearby_41cbc0` 8 · `CEffObj` 6：成员/类型名族（先定性 `GlowObj` 是不是注解里的旧名）。
2. `PushMatrixStacks`/`PopMatrixStacks` 22 + `ProcessKeyboard` 11：**形参声明可疑**（实参是 `&local`），
   属注解批（须有函数体/调用点证据，不能用插转换掩盖）。
3. `CreateFromMemory` 12 · `ReplaceTexture` 11 · `_Eos` 9 · `NewMesh` 6 —— 逐个定性形参/重载。
4. 单点但修法已知：`RenderTarget2.cpp` 的"cast 成员函数名"形态（`((T (*)(...))Class::Method)(recv, ...)`
   ⇒ `((Class *)recv)->Class::Method(...)`），即 F71/F72 的同族改写。
5. `__vftable` 82 仍是 P1(a) 的有意代价（需"按槽号发射虚调用"才能真修）。


## 45. 第 138 轮：**F79 落地 —— 基类限定成员访问 ⇒ 2128（−28，且 `CCBRoleState.cpp` 首次解除截断）**

### 判定性实验（本仓自带 VC6，先证后改）
```cpp
class A { public: int x; };
class B : public A { };
void f(B *p) { p->B::A::x = 1; }   // error C2039: 'A' : is not a member of 'B'
void g(B *p) { p->A::x   = 1; }   // 合法
// 间接基类同样：class C : public B {};  p->B::A::x 报 C2039，p->A::x / p->B::x 合法
```
⇒ `this->X::Y::member` 里的 `Y` 被当成 **X 的成员**（C++ 名字查找规则），而 Hex-Rays 用它表达
"这个成员来自基类子对象"；正确拼法是 `this->Y::member`。

### 命中族（本轮 census）
`this->SceneObj::GlowObj::m_nTodo_000` 与 `this->SceneObj::TaskMgr_SceneObjParam_SceneObj::m_nTodo_000`
（`CCBRoleState : public SceneObj`；`SceneObj : public PalScriptWaitObj, public GlowObj,
public TaskMgr_SceneObjParam_SceneObj`）。全仓文本计数：`SceneObj::GlowObj::` 66 处、
`SceneObj::TaskMgr_SceneObjParam_SceneObj::` 57 处。

### 改动（`pipeline/gen/stages/stage4_substitution.py`，文本级收尾 pass）
`_class_bases_index()` 直接读**生成头**的继承表（`class X : public A, public B {`，
编译器看到的就是它 —— 注意 IDB 侧 `store.struct_bases['SceneObj']` 只列出 1 个基类，
与生成头的 3 个不一致），再对 `cls` 求**基类闭包**，把
`this->X::Y::`（X∈{当前类}∪闭包、Y∈bases(X)）逐级改写成 `this->Y::`（最多收敛 3 层）。

### 实测结果

| | 发布基线 | 上轮(137) | **本轮(138)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2117 | **2089（−28；对基线 −355）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2156 | **2128（−28；对基线 −318）** |
| **S2 ok** | 68 | 78/204 | **78/204（不变）** |
| new_failures / **L1** | 0 / — | 0 / **40** | **0 / 40（不回退）** |
| matched / partial / unmatched | — | 275 · 203 · 43 | **275 · 203 · 43（不变）** |
| invariants / audit_layout | — | 197 / PASSED 38 warn | **197 / PASSED 38 warn（不变）** |

**逐单元 A/B（138a=2156 → 138b=2128）**：只有两个单元变化 ——
`CCBRoleState.cpp` **102（带 `C1003` 截断）→ 76（不再截断）= −26**、
`MUIDialog.cpp 7 → 5 = −2`。
`CCBRoleState.cpp` 的"消失 101 / 新增 73"正是**截断窗口打开**：该文件原本被 `cl.exe` 的 100 错误上限
截断，F79 拆掉 47 条基类限定错误后，文件真实错误数降到 100 以下，~21 条原本被截断的错误首次显示。
⇒ 报告值 −28，**真实修复量 ≥ 47 条**（该文件不再带 `C1003`，说明上限已不再是瓶颈）。

### 第 139 轮 ROI（重排后，均已抽样定性）
1. `PushMatrixStacks`/`PopMatrixStacks`（22）：声明 `void f(int nMode=0)` 在 `include/pal3/ida_defs.h`，
   与二进制 ABI 不符（调用点全是 `lea ecx,[esp+..]` + `call`；被调方 0 栈参、原样返回该指针）
   ⇒ 应改为 `__fastcall` + `void *`（本轮已落地，见 §46）。
2. `ProcessKeyboard`（11）：`InputSystem.json` 的方法签名是 `void __thiscall(int a1)`（this 被写成 int），
   与 `functions.json` 的 `void __thiscall InputSystem::ProcessKeyboard(InputSystem *this)` **冲突** ⇒ 注解一致性修复。
3. `_nearby_41cbc0`（8）：`skip_functions.json` 标为 `empty_stub` 的**自由函数**，但反编译写成
   `this->CameraCtrl::_nearby_41cbc0()`（成员调用）⇒ 应改写为自由函数调用。
4. `ReplaceTexture`（11）· `GetCmdData`（10）· `_Eos`（9）· `NewMesh`（6）· `IsColOBB`（6）·`CreateFromMemory`（12）：逐个定性。
5. `__vftable` 82：仍是有意代价（P1(a)）。


## 46. 第 138 轮续：**F80 —— Push/PopMatrixStacks 声明按二进制 ABI 修正 ⇒ 2116（−12）**

### 证据（IDA 反汇编，A 级）
`include/pal3/ida_defs.h` 里这两个 stub 原声明是 `void f(int nMode = 0)`（自由函数、参数走**栈**）：
- **调用点**：全部 22 处都是 `lea ecx, [esp+..]`（或 `mov ecx, …`）**紧接** `call 0x00540F60 / 0x00540FA0`
  —— 参数走 **ECX**，一条 `push` 都没有；
- **被调方 0x00540F60**：`mov eax, dword_BFDA60; … mov ebx, ecx; … mov eax, ebx; retn`
  ⇒ 0 个栈参、且把 ECX 原样返回 ⇒ 形参是**指针**不是 int。

⇒ 正确声明：`void __fastcall PushMatrixStacks(void *a1 = 0);`（`__fastcall` 的第一个参数放 ECX，
被调方自己 `retn`）。这既清掉 11+11 条 `cannot convert parameter 1 … to 'int'`，
也让生成代码的调用序列与二进制一致（`lea ecx` 而不是 `push`）。

### 一次失败尝试（负结果，值得存档）
第一版把说明写成**中文注释**放在同一段 ⇒ 编译后**新增 15 条错误**，其中 9 条是
`'PushMatrixStacks' : undeclared identifier`（C2065）——**声明行被整行吞掉**。
根因就是仓库已记录的坑：MSVC6 按 GBK 读 UTF-8 源码，中文注释行末字符的 GBK 次字节为 `0x5C`（`\`）
⇒ 行拼接把下一行并进注释（`docs/knowledge/gotcha_gbk_comment_trailing_backslash_eats_next_line.md`）。
改成 **ASCII-only 注释**后复测即正常。**教训：直接参与编译的头/源里的注释一律 ASCII**。

### 实测结果

| | 发布基线 | 本轮前(138b) | **本轮末(138c)** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2089 | **2077** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2128 | **2116（−12；对基线 −330）** |
| **S2 ok** | 68 | 78/204 | **78/204（不变）** |
| new_failures / **L1** | 0 / — | 0 / 40 | **0 / 40（不回退）** |
| matched / partial / unmatched | — | 275 · 203 · 43 | **275 · 203 · 43（不变）** |
| invariants / audit_layout | — | 197 / PASSED 38 warn | **197 / PASSED 38 warn（不变）** |

**逐单元 A/B（2128 → 2116）**：`ScreenEffectMgr −4` · `RenderTarget −2` · `RenderTarget2 −2` ·
`RenderTarget3 −2` · `UIRenderObj −2` · `Logger −1` · `StateUI −1` = −14；
`CCBStage.cpp 101→102`、`PAL3.cpp 101→102`（**两处都是刚触到 100 错误上限、多出一行 `C1003` 本身**）
= +2 ⇒ 净 **−12**，无真实退化。

### 本轮（第 138 轮）合计：2156 → **2116（−40）**
F79（基类限定成员访问，−28，`CCBRoleState.cpp` 首次解除截断）+ F80（Push/Pop 声明，−12）。
S2 78/204、L1 40、new_failures 0、invariants 197、audit_layout PASSED 均未变。

### 第 139 轮 ROI（已把证据取到，可直接动手）
1. **`ProcessKeyboard`（11-12 条）——证据链已完整**：
   - 被调方 `0x0041C710`：`sub esp,1Ch` 起手就用 `ecx` 作 this（`[ecx+1C8h]` / `[ecx+210h]`），
     收尾 `add esp,1Ch; **retn 4**` ⇒ **有 1 个栈参**（4 字节）；
   - 调用点（0x0041C526-28、0x0041C9F5-F6）：`mov ecx, esi`（或 `push edx`）后 `call`，
     即 `push <int>; mov ecx, this; call` ⇒ 真签名 = `void __thiscall(InputSystem *this, int a1)`；
   - 现状：`data/annotations/structs/InputSystem.json` 的 `0x0041C710` 写的是
     `void __thiscall(int a1)`（**省略了 this**），note 里正是第 10 轮"ret-N 判定：callee 清 4 字节 ⇒ 1 个参数"
     —— 结论对、**写法丢了 this**，于是 IDB 里该函数变成 0 栈参，Hex-Rays 把调用渲染成
     `InputSystem::ProcessKeyboard(this)`（**真正被 push 的常量整条丢失**），生成代码报
     `cannot convert parameter 1 from 'class InputSystem *const' to 'int'`。
   ⇒ 修法：把该方法签名写成**显式 this** 形式 `void __thiscall(InputSystem *this, int nVal)`
     （仓库里 `CCBStage`/`functions.json` 已有同写法先例），需 apply+export 验证
     "调用点恢复为 2 实参 + 生成 `push n; mov ecx,this; call`"。
2. `_nearby_41cbc0`（8）：`skip_functions.json` 标为 `empty_stub`，但反编译写成成员调用
   `this->CameraCtrl::_nearby_41cbc0()` ⇒ 先查 0x0041CBC0 的调用点 ABI（`ecx` 还是栈）再决定
   "改自由函数调用"还是"给类补声明"。
3. `ReplaceTexture`（11）· `GetCmdData`（10）· `_Eos`（9）· `NewMesh`（6）· `IsColOBB`（6）·
   `CreateObj`（5）· `UpdateAnim`（5）· `Init`（5，gbLightObj 的 `LIGHT_TYPE` 枚举实参）逐个定性。
4. `__vftable` 82：P1(a) 的有意代价，需"按槽号发射虚调用"才能真修（不是单轮可完成）。


## 47. 第 139 轮：**F81 —— `ProcessKeyboard` 恢复被丢掉的实参（净 +1，但修好了"参数被吞"的字节缺陷）**

### 证据与两处注解（都按二进制）
`0x0041C710`：`sub esp,1Ch` 起手用 `ecx` 作 this，收尾 `add esp,1Ch; **retn 4**`；
调用点（0x0041C526-28 / 0x0041C9F5-F6）= `push <int>; mov ecx,<InputSystem*>; call`
⇒ 真签名 `void __thiscall(InputSystem *this, int a1)`。
- `data/annotations/structs/InputSystem.json`：`void __thiscall(int a1)` → `void __thiscall(InputSystem *this, int a1)`（显式 this，避免 applier 再插一个）；
- `data/annotations/functions.json`（**这里才是生效的那份**）：`...ProcessKeyboard(InputSystem *this)` → 补 `, int a1`。
  （第一次只改 struct 侧 ⇒ 两栏 **delta 0**：`functions.json` 的条目覆盖了它。）

### 实测（apply → export → codegen → probe）
**反编译侧成功**：调用点恢复为 `InputSystem::ProcessKeyboard(this, 1)` —— 原先被判为 0 栈参而**整条丢掉的 `push 1` 回来了**
（这是字节层面的真实修复：旧形态生成的代码根本没有那条参数）。
**编译侧净 +1（2116 → 2117）**：11 条 `C2664 'ProcessKeyboard' : cannot convert parameter 1 from 'class InputSystem *…' to 'int'`
消失，同址冒出 **12 条 `C2660 'ProcessKeyboard' : function does not take 2 parameters`**——
因为生成代码保留的是 Hex-Rays 的**显式 this 形态** `InputSystem::ProcessKeyboard(this, 1)`，
而 VC6 只在 `Class` 的**类作用域**里解析它、把两个实参都算进去（对应 `InputSystem.h` 的 `void ProcessKeyboard(int a1)`）
⇒ 必须像 F71/F72 那样改写成成员调用 `((InputSystem *)this)->InputSystem::ProcessKeyboard(1)`。
逐单元核对：只有 `InputSystem.cpp` 净 +1，其余 4 个文件是"1 条 C2664 换成 1 条 C2660"（同址同因，文件净额 0）。

### 判定（按门禁 4）
这是**已完整解释的 +1**，且伴随一处真实的字节修复（参数不再被吞）；**保留**，并把缺的那一步列为下一轮第一优先：
`ast_transform.transform_oop_calls` 里目前只处理 `Cls::M((Cls*)this, rest)`（cast 分支）与标识符首参，
**没有 `first_arg.type == 'this'` 的 arm** ⇒ `Cls::M(this, rest)` 原样留下。补这个 arm
（`((Cls*)this)->Cls::M(rest)`，`Cls` 为当前类或其基类时）应清掉这 12 条；
`CameraCtrl.cpp` 那 6 处首参是 `(InputSystem *)this->m_pTarget`（cast 分支存在但 `Cls` 非当前类）
需要单独定性（rowtable 家族处理逻辑已在同一分支里）。

### 新工具（下一轮直接可用）
`tools/audit_retn_param_count.py`（IDA 内运行）：对每个"被调方清栈"约定
（`__thiscall`/`__stdcall`）的已注解函数，读取**二进制 `retn N`** 与**注解声明的栈参数个数**并列出不一致者，
输出 `%TEMP%/retn_param_audit.txt` + `.json`。这正是 `ProcessKeyboard` 这类"参数个数被写错"的系统化探测手段
（本次是单点；扫描结果将决定下一批的规模）。注意：`__cdecl/__fastcall` 由调用方清栈，`retn` 不带信息 ⇒ 工具跳过、不下结论。

### 本轮两栏（对照）
| | 发布基线 | 上轮末 | **本轮末** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2077 | **2078（+1）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2116 | **2117（+1；对基线 −329）** |
| S2 ok / new_failures / L1 | 68 / 0 / — | 78 / 0 / 40 | **78 / 0 / 40（均不变）** |
| invariants / audit_layout | — | 197 / PASSED 38 warn | **197 / PASSED 38 warn（不变）** |


## 48. 第 140 轮：**F81 那 12 条 C2660 的精确根因（可复现，含单元测试）**

### 结论：不是"缺 `first_arg.type == 'this'` 的 arm"，而是**那条 arm 只在"限定被调方"分支里**
用真实反编译文本跑完整 per-function 管线（`stages.transform.run_transforms`，`cls_name='InputSystem'`）实测：

| 输入（decomp 原文） | 输出（生成代码） |
|---|---|
| `ProcessKeyboard(this, bTargetCoord == 0);` | **原样不变** |
| `ProcessKeyboard(this, 1);` | **原样不变** |

而 `ast_transform.transform_oop_calls` 的单元测试（人工写成限定形态）显示该 arm 工作正常：
`InputSystem::ProcessKeyboard(this, 1)` + `cls_name='InputSystem'` ⇒ `this->InputSystem::ProcessKeyboard(1);` ✓
（`cls_name='CameraCtrl'` 时第一条走 `[MISATTRIBUTED]` 标记、两条 cast 形态仍被改写 ✓）。

⇒ **根因**：decomp 里 Hex-Rays 写的是**非限定**调用 `ProcessKeyboard(this, …)`；
this-arm 位于**限定被调方**（`qualified_identifier`，`class_name`/`method_name` 已解析）的分支内，
非限定 callee 的路径根本不进那段代码 ⇒ 文本原样输出；**之后**某一步（emit_cpp 一侧的名字解析）
把它**限定成** `InputSystem::ProcessKeyboard(...)` —— 只加前缀、没动接收者，于是 VC6 按类作用域的
`void ProcessKeyboard(int a1)` 检查两个实参 ⇒ `C2660 : function does not take 2 parameters`。

### 下一轮唯一的修法（位置已定位）
在**非限定被调方**路径补一条：callee 是标识符 `M`、首参是 `this`（或 `(Cls *)this`），
且 `Cls::M` 确实是当前类或其基类的方法（`store.method_sigs` 有该键）时，改写为
`this->Cls::M(rest)`（this 值不变、调用目标不变；与限定分支同一约定，判据是"方法确实存在"而非猜测）。
预计覆盖 12 条中的 11 条；`CameraCtrl.cpp` 那 6 处首参是 `(InputSystem *)this->m_pTarget`（`Cls` 非当前类），
需按 rowtable 家族规则另判。

### 本轮状态
无功能改动（仅诊断 + 单元级验证，未动生成物）；两栏保持 **A 2078 / B 39 / 总 2117**，
S2 78/204 · new_failures 0 · L1 40 · invariants 197 · audit_layout PASSED 均不变，tracked 基线未推进。
新工具 `tools/audit_retn_param_count.py` 待首次运行（与上述改动同批）。


## 49. 第 141 轮：**F82 落地 —— 非限定成员直调限定化 ⇒ 2113（−4）**，并收敛收尾

### 改动（`pipeline/gen/ast_transform.py`）
新增 `_qualify_this_member_calls(code, cls_name)`（`transform_oop_calls` 收尾调用）：
callee 是**标识符** `M`、首参是 `this`、且 `Cls` 的**生成头**里确实声明了成员 `M` 时，
改写为 `this->Cls::M(rest)`。判据是"生成头里有这个成员"（编译器将来就按那份声明检查），不是猜测；
this 值不变、调用目标不变，且 `this->Cls::M(...)` 是合法非虚直调形式。
方法索引 `_class_method_index()` 直接读 `pal3/src/**/*.h`（文件名即类名）。

**单元验证（真实反编译文本走完整 per-function 管线）**：
`ProcessKeyboard(this, 1);` ⇒ `this->InputSystem::ProcessKeyboard(1);` ✓（同一函数两处均改写）。
全仓作用面：**7 个函数 / 16 处**。

### 实测结果

| | 发布基线 | 上轮末 | **本轮末** |
|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2078 | **2074（−4；对基线 −370）** |
| B. 新增编译面 | — | 3 单元 / 39 | **3 单元 / 39** |
| **总错误数** | **2446** | 2117 | **2113（−4；对基线 −333）** |
| S2 ok / new_failures / L1 | 68 / 0 / — | 78 / 0 / 40 | **78 / 0 / 40（均不变）** |
| matched · partial · unmatched | — | 275 · 203 · 43 | **275 · 203 · 43（不变）** |
| invariants / audit_layout | — | 197 / PASSED 38 warn | **197 / PASSED 38 warn（不变）** |
| 错误分类（annotation/codegen/hexrays/idb/unknown） | — | 54/18/43/2/9 | **54/18/43/2/9** |

**逐单元（2117 → 2113）**：`InputSystem.cpp −2`（ProcessKeyboard 12 → 2，余下两处接收者不是 `this`）、
`CCBSystem.cpp −1`（`FindFreeThread`）、`PAL3.cpp −1`；**无单元变差**。
消失 6 / 新增 2（新增的 2 条是 `CCBStage.cpp` 的 `C2227 left of '->m_Task'` 与 `PAL3.cpp` 的
`C2440 '=' from 'char *' to 'int'`，均为同文件的截断窗口/定型位移，两文件净额 −1/-1 已计入）。

### 本会话收敛总结（第 132→141 轮）
| 指标 | 发布基线 | 会话起点(131 末) | **现在** | 净变化 |
|---|---|---|---|---|
| **A. 共享单元错误数** | 2444 | 2314 | **2074** | **−240** |
| **总错误数** | **2446** | 2339 | **2113** | **−226（对基线 −333）** |
| S2 ok | 68 | 74/204 | **78/204** | +4 |
| L1 | — | 38 | **40** | **+2（从未回退）** |
| new_failures | 0 | 0 | **0** | 0（每轮 `compile_regression.py` 独立复核） |
| matched · partial | — | 259 · 191 | **275 · 203** | +16 · +12 |
| invariants 阻塞项 | — | 197 | **197** | 0 |
| tracked 基线 | 未推进 | 未推进 | **未推进** | 0 |

**本会话落地机制**：F72（`*ptr` 显式 this 改写 −14）· F73（导入槽退化原型 −53）·
F74（间接调用实参转换 −70）· F75（fnptr 局部变量同族 −16）· F76（CRT 固定原型 −13）·
F77（导入槽**占位形参** −1/+语义修复）· F78（引用形参取址 −31，L1 +2）·
F79（基类限定成员访问 −28，`CCBRoleState.cpp` 解除截断）· F80（`Push/PopMatrixStacks` ABI −12）·
F81（`ProcessKeyboard` 恢复被吞实参，+1 但修字节缺陷）· F82（非限定成员直调限定化 −4）；
外加门禁工具修复（`compile_regression`/`audit_layout` 的 emoji 在 GBK 控制台抛异常导致门禁自崩）
与知识库条目（导入槽原型覆盖 Hex-Rays 修饰名签名）。

**剩余 ROI（交下一会话）**：
1. `__vftable` 82 —— P1(a) 的**有意代价**（为保布局删掉 +0 占位），真修法是"按槽号发射虚调用"，非单轮可完成；
2. `CreateFromMemory` 12 · `ReplaceTexture` 11 · `GetCmdData` 10 · `_Eos` 9 · `_nearby_41cbc0` 8 ·
   `CEffObj` 6 · `NewMesh` 6 · `IsColOBB` 6 · `UpdateAnim` 5 · `Init` 5 · `CreateObj` 5 —— 逐个定性（多为形参/枚举/归属）；
3. **新工具已就位未跑**：`tools/audit_retn_param_count.py`（按二进制 `retn N` 审计注解声明的栈参数个数）
   —— 这正是 `ProcessKeyboard` 这类"参数个数写错"的系统化探测手段，下一会话先跑它决定批次规模；
4. `ProcessKeyboard` 余下 2 处（接收者不是 `this` 的调用点）。












