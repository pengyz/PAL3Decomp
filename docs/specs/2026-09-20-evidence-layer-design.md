# 设计：注解证据层（Evidence Layer）—— 让"尺寸/归属"判据重新具备判别力

状态：**待用户复核**（随后交 `subagent_kiro` 与 `subagent_codex` 双向复核，再转 `writing-plans`）
日期：2026-09-20 ｜ 架构路径：**A（共享证据层 + 单一台账 + 薄消费者）** ｜ 执行模式：**逐闸毕业生效**

## 1. 背景（全部为已实测事实，出处见括号）
1. **判据的参照物被污染** → 现有闸判别力 ≈ 0：`pipeline/check_annotations.py` 报 `0 errors PASS`，
   而实测 **38 个 struct 的 `binary_size > 3× 最大成员末端`**，其中 **4 个精确 = 2×**
   （`safe_size = max_offset*2` 指纹：`AudioContext`/`ComposeUI`/`LinkerVersion`/`gbSingleton_gbGfxManager`）。
   **【2026-09-20 更正】本规格初稿写的是"91 个 / 9 个"，经独立复核指出后由主 agent 亲自复算证伪** ✗：
   用 `tools/audit_layout.py` 自己的 `declared_size_geometry()` 在当前树与 `32326e886^`（修复前）上
   均得 **38 / 4**；5 天前的 A 级纪要 **AT-200 记 52 个** ⇒ 真实计数**随时间下降**，而"91"高于历史峰值 ✗。
   **复算命令（只读）**：`python3 -c "..."` 复用 `al.load_annotations()` + `al.declared_size_geometry()` 全量扫描
   （见 commit message 与本节脚注；禁止把未经复算的数字写进规格 ✓）。
   **元教训**：该数字来自一份 subagent 报告，我**未复算就搬进规格** ✗ —— 这正是本仓历次审计点名的
   "把'独立复核'当标签用"的失败模式 ✓；**今后凡引用数字必须附可复跑的复算命令** ✓。
2. **同源恒真**：`ida_structs.json` 是**注解的复制**（761/761），`export_full.py` 有 8 处
   `[t4-DECLARED-EXCEPTION]` 直读注解 ⇒ `audit_layout` 的 check1（`binary_size == ida_size`）
   **由构造必然相等**，永无判别力。（复核 + `tools/audit_layout.py:14-27` 自述）
3. **缺独立尺寸源**：仓库自己的 `pipeline/decomp_quality.py:105-112` 原文——
   "this check is DILUTED… **zero power**… Fixing that needs an **IDB-independent size source**"。
4. **秒级可判别的闸没接线**：`tools/codegen_invariants.py` **零调用**（grep 无引用），
   而它可拦 27 条 signature/JSON 类名矛盾、`__vftable` 残留、`sub_` 形参不一致。
5. **已有 17 条 ctor-anchored 尺寸 MISMATCH 未被消费**：`data/status/alloc_sizeof.json`
   （Camera 544 vs **12956**、ScreenEffectNode 1060 vs 220、UIListBox 1760 vs 1208、
   JusticeBookUI 56192 vs 11404 …），而 `tools/_land_sizes.py` **只硬编码落地 8 条**。
6. **偏移来源修正已有实现（避免重复劳动）**：`tools/attribution_offset_match.py:8-13` 早已用
   asm `[reg+imm]` 并举例 CIniFile×8；实跑 `--func 0x4EC700` 得正确字节偏移 ⇒ **只缺 `--scan`**。
   反例：`tools/audit_structural_attribution.py` 用 decomp `this+N`（报 2571，asm 真值 `[ebp+505Ch]`=20572，**8× 差**）。
7. **层 1 门禁的天生盲区**：错误分三类 —— (a) 注解主张错；(b) **注解正确但通路错**（C2208 型，
   `gotcha_codegen_multi_inheritance_anon_member` 记载其**经 globals.h 炸穿 205 个 .cpp**）；
   (c) codegen 改写错。**本设计只针对 (a)，必须显式声明 (b)/(c) 不在射程内。**
8. **层 1 自身还有"归属双源矛盾 27 条"无人消费**（复核点名：比"能否从二进制验证"更便宜也更该先修）。

## 2. 目标与非目标
**目标**
- G1 建立**独立于注解的尺寸证据源**（来自 exe/asm，非注解自述）。
- G2 建立**独立于注解的归属证据源**（vtable 写表签名 / `operator new(N)`+ctor / `??_L`·`??_M` 元素尺寸 / ctor 的 vfptr 安装次序）。
- G3 把"某类的 `binary_size` 是否有独立证据"**显式化**（分级 + `placeholder` 标记），并让**所有以 `binary_size` 为界的判据在 placeholder 上拒绝出结论**。
- G4 接线既有秒级闸（`codegen_invariants`），并让 4–5 个消费点改用**带证据等级**的输入。
- G5 **逐闸**把存量清零并升为硬失败；最终挂到 `cli.py check`（`apply/export` **之前**），且 `apply_annotation_batch.py --run-pipeline` 也过这道门。

**非目标（明确不做）**
- ❌ 不新建"一致性/重叠/越界"门禁（**已存在**，`0 errors PASS` 而 91 个污染 ⇒ 边际收益 ≈ 0）。
- ❌ 不把几何比值当尺寸真值（pre-fix `Scene` 比值 = **1.0，永不触发**）。
- ❌ **未建锚点前不批量改 `binary_size`**（本仓有"无证据批量改名被整体撤销"的前例）。
- ❌ 不解决 (b) C2208 型与 (c) codegen 改写错（**声明为已知射程外**，另立工作）。
- ❌ 不删除 `_longterm_plan.md` 等历史文档（只作废其"唯一路线"声明）。
- ❌ 不追求"自动落地尺寸修正"（17 条 MISMATCH 混有 base-subobject/phantom，**必须逐条裁定**）。

## 3. 架构：一个证据层 + 一个台账 + 薄消费者
```
pipeline/evidence/                     ← 新增（Python，无 IDA 依赖者用 exe/asm；需要 IDA 的走 idat -A -S）
  exe_image.py         # VA→offset、读 dword、节边界（复用 tools/pe_probe.py 的能力，抽成库）
  element_size.py      # ??_L/??_M 扫描器：抽 (ptr, size, count, ctor, dtor) —— 133 站点
  alloc_sizes.py       # operator new(N)+ctor 配对（读 alloc_sizeof.json 的产物协议）
  attribution.py       # 归属证据：vtable 写表签名 / ctor vfptr / asm [reg+imm] 越界侦察
  ledger.py            # 生成/校验 data/status/evidence_ledger.json（唯一台账）
data/status/evidence_ledger.json       ← 新增：每类的证据等级与 placeholder 标记（机器可读，tracked）
pipeline/cli.py                        ← 新增 `evidence` 子命令（build / check / show）
```
**台账条目（每类一条）**
| 字段 | 语义 |
|---|---|
| `class` | 类名 |
| `binary_size_claim` | 注解当前值 |
| `size_evidence` | `{kind, value, source}` 或 `null`；kind ∈ `alloc`/`??_L`/`??_M`/`bss_span` |
| `size_conflict` | 独立证据与 claim 的差 |
| `grade` | `verified` / `conflict` / **`placeholder`** / `unknown` |
| `attribution_sources` | 归属证据列表（vtable/ctor/asm-offset） |
| `dual_source_conflict` | 27 条双源矛盾的显式记录 |

**placeholder 判定（G3 的语义核心）**：满足任一即 `placeholder`
1. `binary_size` 精确等于 `2 × max_member_end`（`safe_size` 指纹）；
2. 无任何独立尺寸证据，且 `binary_size > 3 × max_member_end`；
3. 已有 A 级纪要标记为污染（如 AT-200 的 52 个）。
⇒ 所有 offsets-vs-size 判据（`decomp_quality.py:102`、`audit_layout`、`check_annotations:600`、
`scan_misattribution:142`、`audit_structural_attribution`）在 `placeholder` 上**必须输出
`INCONCLUSIVE`（而非 PASS/FAIL）**，并在报告里计数。

## 4. 组件与判据（每个都要求"注入式负例"）
| 组件 | 输入 | 输出 | 判据/证据等级 | 注入式负例 |
|---|---|---|---|---|
| `element_size.py` | `original/PAL3.exe.asm` | 133 个站点的 `(size, count, ctor, dtor, ptr)` | **A**（指令字面量）| 伪造一个站点 ⇒ 必须报出 |
| `alloc_sizes.py` | exe + `alloc_sizeof.json` | `{class: sizeof}` | **A**（`operator new(N)`+ctor）| 篡改 N ⇒ 必须报冲突 |
| `attribution.py` | asm + `ida_structs.json` | 每函数的归属证据集 | **A**（vtable 写表 / ctor vfptr）；越界侦察**仅信号** | 注入一个越界偏移 ⇒ 必须报 |
| `ledger.py` | 上述三者 + 注解 | `evidence_ledger.json` | 分级规则见 §3 | 把一个类改成 placeholder ⇒ 消费点必须 `INCONCLUSIVE` |
| `codegen_invariants` 接线 | 生成物 | check A/B/C | **B**（结构不变量）| 已有自测；补 check C 白名单 |

## 5. 分阶段与"逐闸毕业生效"
**P1 建证据源（advisory，只读为主）**：`codegen_invariants` **接线** → `element_size.py` →
`alloc_sizes.py` → `ledger.py`（分级+placeholder）→ `attribution.py` 的 `--scan`。
**P2 逐闸清零（每批一次管线 ≈13 min；判据见 §6）**，顺序＝**由易到难**：
`codegen_invariants` **A132/B56/C27/D10（Codex 实测 ✗ 初稿只数了 C 的 29）** → `alloc_sizeof` 17 条 → 归属双源 27 条 → **尺寸污染 38 条（最后，部分属长尾）**。
**P3 逐闸升硬 + 挂 `cli.py check`**（`apply/export` 之前 ✓）＋ 作废 `_structural_contradictions.json` 及其派生数字 ✓
＋ 可选项 BSS 相邻上界 `binary_size(T) ≤ next_global_addr − this_addr` ✓。

**"逐闸毕业生效"定义（回应执行模式）**：某闸的**自身存量**清零 + 注入式负例通过 ⇒ **立即**把该闸升为硬失败 ✓,
**不等待其它闸** ✓（否则整条工作流会被 91 条长尾堵住数天 ✗）。

## 6. 验收与判据（每批一次管线）
- **必须**：`new_failures == 0`；`L1 == 34`（**不回退**）；`s2 ok ≥ 76`；`pipeline/cli.py check` PASS；
  工作区 clean；提交推送 ✓
- **总错误不作判据** ⚠️（同状态可差 ±18，见 `_longterm_plan.md:11` 与
  `gotcha_error_census_not_a_pure_function_of_the_tree.md`）⇒ 只作**参考记录** ✓
- **预期偏差要预先核销**：改归属会**新增 TU**（`s2_total` 增加 ✓）与"新 TU include 缺失"类错误 ✓
  （B34 的 `C2065 'GetActorMgr'` 即此 ✓；**可追溯证据**：`data/status/archive/20260920_b34_incident/20260920_153924/all_errors.txt` ✓ —— 初稿未给出处，经复核指出后补 ✓）⇒ 先按预期名单核销，不算新根因 ✓
- **超约束即回退**：回退＝恢复注解 → **`apply → export → codegen → probe`**（**只回退注解不够** ✗，
  IDB + `asm/pal3/ida_structs.json` 都是 stale 层 ✓）；禁止 `git checkout/restore/stash/clean -fd` ✓

## 7. 风险与缓解
| 风险 | 缓解 |
|---|---|
| `??_L` 的 `size` **不唯一**（8704 同时匹配 `Role`/`RoleSystem`）| **必须用 ctor 指针锚定元素类** ✓ |
| **ctor 归属本身可能错**（`sub_411CA0` 被注成 `~PalScript` ✓ 实测）| 台账记录**归属证据等级**；低等级不作结论 ✓ |
| 17 条 MISMATCH **不可自动落地**（混 base-subobject/phantom）| 逐条裁定 + 台账 ✓ |
| **38 条尺寸污染部分是"成员缺失"而非"尺寸错"**（14 条 HIGH 已裁定）| 先分级；长尾单独批次 ✓，
  **不得**为了清零而乱改尺寸 ✓ |
| 层 1 对 C2208 天生不可见 ⚠️ | **写进文档与 `CLAUDE.md`**：本层只证 (a)；C2208 另立工作 ✓ |
| **union 平凡性**（B34 事故根因）| 已加 `tools/check_union_member_triviality.py` ✓ 纳入 P1 接线 ✓ |
| 消费点改造（4–5 处）可能引入回归 | 每处改完先跑既有套件 + `check`；`INCONCLUSIVE` 只**新增**语义、不改原有 PASS/FAIL 路径 ✓ |

## 8. 开箱清单（实现计划将细化）
**新增**：`pipeline/evidence/{exe_image,element_size,alloc_sizes,attribution,ledger}.py` ·
`data/status/evidence_ledger.json` · `tools/audit_element_sizes.py`（CLI 壳）·
`tests/test_element_size.py` / `test_alloc_sizes.py` / `test_ledger_placeholder.py`（**注入式负例**）
**修改**：`pipeline/cli.py`（`evidence` 子命令 + 挂 check）· `tools/codegen_invariants.py`（接线 + check C 白名单）·
`tools/attribution_offset_match.py`（`--scan`）· 5 个消费点（`INCONCLUSIVE`）·
`tools/apply_annotation_batch.py`（`--run-pipeline` 过门）· `CLAUDE.md`（检查点表补 probe + 声明 (b) 射程外 + 措辞更正）
**作废**：`data/status/_structural_contradictions.json` 及其派生数字 ✓

## 9. 待确认（规格复核关卡）
1. **"逐闸毕业生效"**（§5）是否符合你的"直接硬失败"意图 ✓
2. `placeholder` 判定三条规则（§3）是否采纳 ✓（尤其第 1 条 `2×` 指纹 ✓）
3. **【复核要求·必补】新词汇的映射表**：`verified/conflict/placeholder/unknown` 与本仓**已并存的
   多套状态词汇**（`check_annotations` 的 errors/warnings · `audit_layout` 的 ERROR/WARN/HIGH ·
   `alloc_sizeof` 的 OK/MISMATCH/**OPAQUE** · `_cleanup_scan_attribution` 的 `[A]/[B]`+AT/CG/AR 编号族 ·
   probe 的 L1 与总错误 · `gotcha_error_census_*` 的"可信/带噪声"）之间**是否需要一张显式映射表、由谁维护** ✓
   —— **这是防止本设计沦为"第 N 套等级词汇"（本仓已有 8 套）的最低成本护栏** ⚠️
4. **【复核要求·必补】台账单向红线**：`evidence_ledger.json` 必须是**单向消费品** ✗ ——
   **禁止任何自动/半自动的"按 ledger 回写注解"通路** ✗（否则会绕一圈重新制造"同源污染" ✗）
5. **【复核要求·必补】新模块必须套用护栏**：5 个 evidence 模块（尤其写盘的 `ledger.py`）必须复用
   `tools/_land_sizes.py` 的"任何 `-` 开头参数即拒绝执行"护栏 ✓（防重演已发生 2 起的 `--help` 覆盖产物事故 ✗）

## 10. 实现批次（复核要求：**Spike-first + 拆批**，替代原"一次性开箱"）
| 批 | 内容 | 验收（门槛）|
|---|---|---|
| **B1（Spike，先做）** | `exe_image.py` + `element_size.py` + **最小 ledger**（只支持 size 证据）+ 1 个测试 ⇒ **对 Role/Scene 历史案例做回放** | 能否在 `32326e886^` 的树/asm 上**自动**标出 `Role`(8928 vs 8704) 与 `Scene` 尺寸问题 ✓ —— **这是决定是否推进后续批次的门** ✓ |
| B2 | 接线 `codegen_invariants`（纯增量、有自测） | 29 条存量清零 + 注入式负例 ✓ |
| B3 | `alloc_sizes.py` + 消费点 `INCONCLUSIVE` 改造 | 17 条台账化 ✓ |
| B4 | `attribution.py` + `--scan` + 归属双源 27 条 | 27 条裁定 ✓ |
| B5 | 尺寸污染 38 条（**先按"缺成员 vs 真错"二分** ✗ 再动手） | 分批清零 ✓ |
`cli.py`/`CLAUDE.md` 的改动**随各批增量提交** ✓（不攒到最后 ✗）


---

# 附录：三路对抗性复核结论与**修订要求**（2026-09-20，Kiro + Codex + 内部）

**三路一致裁定**：**带条件批准 / 需先改规格 + 先做一个窄 Spike** ✓ —— 核心诉求（需独立于注解的尺寸/归属证据源）
被三路**独立证实** ✓；但**按原文不可直接实现** ✗。以下为**必须修**的项（按来源标注）。

## A. Blocker（三路共同/各自）
| # | 问题 | 来源 | 证据 | 修法 |
|---|---|---|---|---|
| **B1** | **`codegen_invariants` 接线会立刻红** ✗ | Codex 实测 | 默认检查集 A/B/D 均失败：**A=132 exit1 · B=56 exit1 · C=27 exit0 · D=10 exit1**；初稿"29 条"**只数 C** ✗ | P1 只接 **C 为 advisory + whitelist**；A/B/D 各自建存量清单、修复或 grandfather，再逐项升硬 ✓ |
| **B2** | **ctor 归属循环污染尺寸证据** ✗ | Kiro(P7/D3) + Codex | `sub_4236D0` 被注成 **`BINK::Reset`** ✗（`BINK=932`）却作为 `Scene` 内嵌数组的 **ctor** 出现在 `??_L` ⇒ 用错锚会把 896 证据挂到 BINK ⇒ **假 conflict + 漏掉真 `tagRoleSlot`** ✗；`sub_411CA0` 同时被注成 `~PalScript` 与当作 `Role::~Role` 使用 ✗（**注解树里真实存在的双源矛盾，至今无闸捕获** ✓）| **ledger 分两层**：`raw_site`（仅地址/字节/size/count ✓）与 `ownership_candidate`（单独记证据 ✓）；**annotation-derived ctor 只能是 candidate，不得直接产生 class A 级尺寸** ✓；BINK/tagRoleSlot/sub_411CA0 作为 fixture ✓ |
| **B3** | **placeholder 存量口径无共识** ✗ | 三路 + 我 | 三路复算：**>3× = 38**（一致 ✓）；**精确 2× = 4**（Kiro/我）vs **0**（Codex）✗ ⇒ **仍有分歧，必须固定唯一计算器与基线** ✓；AT-200 的 52 是**历史名单**，不能整批导入 ✓ | §0 写"唯一计算器 + 命令 + 期望输出 + 输入参数" ✓；复算并锁定 4 vs 0 ✓ |
| **B4** | **台账生命周期未定义** ✗ | Codex | 现成反例：`misattribution_ledger.json` 生成于 9/14，而 `Scene.json` 9/20 又变 ⇒ **已 stale** ✓，且其生成器**写死 Windows 路径** ✗ | schema 加 `schema_version`/输入 hash/generator version/generated_at ✓；`evidence check` 每次从**当前 raw inputs 重建比对**，stale/missing ⇒ **exit 2（前置失败，不是假 PASS）** ✓；明确废弃或迁移 `misattribution_ledger.json` ✓ |

## B. Major（必须写进规格）
1. **`alloc_sizes.py` 并不独立** ✗（Codex E3）：只读现有 `alloc_sizeof.json` ⇒ **新增证据 = 0** ✓ ⇒ 必须**重算**并保留 raw exhibit + ownership candidate ✓；且**CCBUI 有两个不同尺寸** ⇒ **不能压成 `{class: sizeof}`** ✓
2. **`audit_structural_attribution` 无机器可读通道** ✗（Codex E4）：全库模式只有 print + exit0 ⇒ 必须先加 JSON/stdout 协议 ✓
3. **`scan_misattribution` 默认写状态文件** ✗ ⇒ 消费者接入前须支持 stdout/explicit-out ✓
4. **grade 优先级未定义** ✗ ⇒ 建议：`invalid/stale prerequisite → conflict → placeholder → evidenced → unknown`（**必须进规格** ✓）
5. **clean-checkout 可复现性** ✗：`original/*.asm` 与 `asm/` **均 gitignore** ✓ ⇒ 台账必须能从 **tracked** 输入（exe）或 tracked 快照复验 ✓，**不得假设本地 asm/export 存在** ✓
6. **attribution scan 有已知漏采** ✗（indexed addressing / this 重载 / 中间指针）⇒ **全库结果只能给 candidate/signal，不能当"漏检为零"** ✓；且 `--scan` **不是一行改动** ✗（需先建 proc index，否则 4752 proc × 579k 行不可接受 ✓）
7. **B 分类器精度未闭合** ✗ ⇒ 未校准前不得升硬 ✓
8. **`??_M` 是四元组** ✗（`ptr,size,count,dtor`，**无 ctor**）⇒ 不得与 `??_L` 共用五元组描述 ✓
9. **`test_smoke.py`**：三路之一（内部）把它列为 P0"恒真" ✗ —— **该前提已过期** ✓：P0-1 已改为 `assert`（`MIN_S2` 读基线），且注入 `PAL3_MIN_S2=9999` **实测失败** ✓（`_architecture_cleanup_plan_20260920.md` P0-1 ✓）⇒ **本条不适用** ✓

## C. 三路共同要求的**结构与顺序修订**
- **§0 口径固定**（唯一计算器 + 命令 + 输入参数 ✓）
- **§2.5 ROI 前置归因**：**必须先把尺寸污染归因到具体错误码并计数** ✗ —— 否则无法判断是否"在便宜处用力"；内部复核实测：**射程外占 ≥1279/2150 ≈ 59%** ✗（C2440 359 + C2227 226 + C2660 202 + C2664 196 + C2039 152 + C2228 144 ✓），而 **C2208 现已 0 条**（`status: fixed` ✓）⇒ **初稿拿一个已修复的事故论证射程 ✗，必须改写** ✓
- **§3.5 词汇治理**（内部复核 F1 的核心）：新 4 态与**已并存的 9 套词汇**（不是 8 套 ✗）**实测打架** ✗ —— **临床样本**：`Camera.json` 成员标 `source:"A:FPU_binary_evidence..."` ✗ 而同类 `ratio 31.8×` ⇒ 新体系判 `placeholder` ⇒ **"A 级证据"与 `placeholder` 同时成立** ✗ ⇒ **`verified` 必须改名 `evidenced`/`corroborated`** ✓（它只证明"等于某值"、不证明"正确" ✗，且与 skill/command 的 A 级对撞 ✓）；并要求 (a) 正交性 (b) 覆盖性 (c) 机械映射 三检验 ✓
- **§4.5 消费点存在性验证**：内部复核实测**一处不符** ✗ —— `tools/scan_misattribution.py:142` **只是构建 dict** ✓，判据描述在 `:14`、尺寸参与判定在 `:459` ✓ ⇒ 照初稿改会**改错地方** ✓
- **§5.5 闸的接线与活性**：① 必须**真的串到写盘路径** ✗（`cmd_check()` 只跑 `check_annotations.py` ✓；**`apply`/`export` 不调用它** ✗ ⇒ 只改 `cmd_check` 就是**空门** ✓）；② 注入式负例升为 **§6 必跑命令**（不能只作表格一列 ✗）；③ **恒假检测**（连续 N 次"全 INCONCLUSIVE"即报警 ✓）；④ **单一责任人 = 用户本人**（AI 会话**不得**列为责任人 ✓）
- **§7.5 本设计自身的沉淀与接线**（内部 F4）：台账落 `data/status/`（**293 tracked / 373 文件** ✓，而知识库对它只有 `CLAUDE.md:159,162` 两处引用 ✗）⇒ **精确落在"沉淀死面"** ✗ ⇒ 必须规定：哪类结论进 `docs/knowledge/` ✓、写入触发器 ✓、**`MEMORY.md` 入链** ✓、并把"审计→status→消失"本身落成一条 `gotcha` ✓
- **独立性口径**：`ida_structs.json` 是**本地再生产物且被注解污染** ✓ ⇒ **不能当独立归属真值**，只能提供待核对线索 ✓
- **§8 拆分**：三路一致要求 **Spike-first + 拆 3 个交付** ✓（见 Codex 的依赖图与交付验收 ✓；核心：**raw evidence 与 adjudicated evidence 分层**，避免伪循环 ✓）

## D. 三路的"先做一小步"（与我原 P1 不同 ✓）
1. **接线 `codegen_invariants` 的 C 为 advisory + whitelist** ✓（分钟级；**不可直接接 A/B/D** ✗）
2. **固定"尺寸污染"口径**（38 / 4-or-0 / 14，**附命令与输入参数** ✓）
3. **修 `tools/_land_sizes.py`**（**已修 ✓**：REVERT 分支不再重生成 + **真正的 `SystemExit(1)`** ✓ —— 初稿声称"非零退出"却**从未实现** ✗，系第三路复核发现 ✓）
4. **Spike**：只读 `??_L` parser 抽全部 133 站点 + 手核 Role/tagRoleSlot/BINK 三例 + 最小 ledger schema + 复算 placeholder 并解释 91 vs 38 差异 ✓；**成功判据**：133/133 参数完整 ✓、**Role 可由独立证据解析而 BINK 错锚被判 unknown/conflict** ✓、不改注解/不改生成物/**不接硬门禁** ✓


---

# 补齐的 6 节（2026-09-20，按三路复核要求；**口径已锁定**）

## §0 口径固定（唯一计算器）
**"尺寸污染"的唯一权威定义与算法**：`tools/audit_layout.py::declared_size_geometry(name, struct, all_structs)`
（**只读**；模块级无副作用，已用 AST 核实）。
**复算命令**（可复跑，无写盘）：
```bash
python3 -c "import importlib.util as iu; spec=iu.spec_from_file_location('al','tools/audit_layout.py'); \
 al=iu.module_from_spec(spec); spec.loader.exec_module(al); ann,_=al.load_annotations(); \
 print(sum(1 for n,d in ann.items() if (al.declared_size_geometry(n,d,ann) or {}).get('ratio',0)>3.0))"
```
**锁定基线（2026-09-20，881 structs）**：
| 量 | 值 | 口径 |
|---|---|---|
| `ratio > 3.0` | **38** | 三路一致 ✓ |
| `ratio > 50.0`（HIGH）| **14** | 与 `data/status/_geometry_strict_report.json` 的 `high_count: 14` 对齐 ✓ |
| `ratio == 2.0`（**四舍五入后**）| **4** | `AudioContext` / `ComposeUI` / `LinkerVersion` / `gbSingleton_gbGfxManager` |
| `binary_size **精确** == 2×max_member_end` | **3** | 上述去掉 `ComposeUI` |
**⇒ 复核分歧的裁定**：Kiro/主 agent 用"四舍五入比值"得 **4**；Codex 报 **0** 在**两种口径下都不可复现** ✓（其计算方式未记录，故**以本条口径为准**）。
**⇒ 产物纪律**：任何写入 `data/status/` 的几何/尺寸产物**必须记录输入参数**（阈值环境变量、算法 commit、生成时刻）✓ ——
反例：`_geometry_strict_report.json` 的 `warn_count: 6` **无任何阈值可复现** ✗（必然在某个**未记录**的
`PAL3_GEOMETRY_WARN_RATIO` 下生成 ✗）⇒ 该产物**不得再作权威读数**，引用前必须按本条口径重算 ✓。

## §2.5 ROI 前置归因（本规格**不解决**当前最贵的错误类别）
**当前错误分布**（`data/status/baselines/latest.json`，206 单元 / 2150 错误）：
**C2440 359（16.7%）· C2227 226 · C2660 202 · C2664 196 · C2039 152 · C2228 144 …**
⇒ **射程外（(b) 通路错 / (c) codegen 改写错）合计 ≥1279/2150 ≈ 59%** ✗
**本规格的受益面**：可机判的尺寸/归属类 = **O(10–38)** 个类 ✓（`alloc_sizeof.json` 仅 28 行：MISMATCH 17 / OK 8 / OPAQUE 3；`operator_new` 仅 10 ✓）
**⇒ 两处必须改写**：
1. 初稿拿 **C2208 型**论证"射程外"✗ —— 该 gotcha 的 `status` 已是 **`fixed`（2026-08-29 已修）** ✓，且 **C2208 现已 0 条**（不在前 22）✗ ⇒ **不得用已修复的事故论证射程** ✓
2. 必须新增一句：**"本规格不得被当作'当前最贵问题'的解决方案"** ✓，并给出与 **C2440 型（359 条 / 71 文件 / 形态高度同构，前 6 种模板覆盖 134/359）** 的排序关系 ✓
**前置动作**：把 38 条尺寸污染**归因到具体错误码并计数** ✓ —— 若归因不出足够错误码，须在规格明说"本设计的直接错误收益有限" ✓

## §3.5 词汇治理（防"第 N 套等级词汇"）
**现状：已并存 9 套**（不是 8 套 ✗）—— skill A–D · command A/A+/B/C/D · `sig_evidence.py` 机器判级 · `enum_promote.py` · `_pdb_nonauthority_notice.json` 的 1/2/3/X · 注解 `source` 前缀（**实测 417 条 `A:`/`A+:`/`B:`**）· commit-msg 门禁 · `_longterm_plan.md` 的 D/A/B/C 不变量图 · `docs/knowledge` 的 `confidence: 0-100`
**⇒ 修订（强制）**：
1. **`verified` 改名 `evidenced`/`corroborated`** ✗→✓ —— 它只证明"尺寸**等于**某值"，**不证明"正确"** ✓（规格 §7 自承 `??_L` 的 size **不唯一**：8704 同时匹配 `Role`/`RoleSystem` ✗），且与 skill/command 的 A 级（"偏移正确"）**语义对撞** ✗
2. 降级为**闸输入侧的单一状态字段** `size_evidence_state ∈ {evidenced, conflicted, unestablished}` ✓ —— **只**作为消费点输出 `INCONCLUSIVE` 的判据 ✓，**不进"证据强度"语境、不写 change log、不进 commit message** ✓
3. **提供映射表**（既有 9 套 → 新字段，允许多数为空映射 ✓），并以下列**三检验**为验收项：
   **(a) 正交性**：不得与既有词在同一维度打架 ✗ —— **临床样本**：`Camera.json` 成员标 `source:"A:FPU_binary_evidence | ida_xref"` ✗ 而同类 `ratio 31.8×` ⇒ 新字段判 `unestablished` ⇒ **"A 级证据"与 `unestablished` 同时成立** ✗ ⇒ 必须显式给出**冲突解释规则** ✓
   **(b) 覆盖性**：每类**恰好**落一个状态，不重不漏 ✓（初稿 `placeholder` 与 `unknown` 边界模糊 ✗ —— 规则1 `=2×` 与规则2 `无独立证据且>3×` 落在同一真实轴上 ✗ ⇒ 合并或机械化 ✓）
   **(c) 机械映射**：能给出既有 9 套 → 新字段的函数（哪怕偏序/空映射）✓
4. **grade 优先级**（必须进规格）：`前置失败(stale/missing) → conflicted → unestablished → evidenced → unknown` ✓

## §4.5 消费点存在性验证（逐处核实，**已发现一处不符**）
| # | 位置 | 实测用途 | 结论 |
|---|---|---|---|
| 1 | `pipeline/decomp_quality.py:121`（加载 `:21`）| 用 `binary_size` 作**上界** | ✓ 可低风险加 `INCONCLUSIVE`+计数 |
| 2 | `tools/audit_layout.py:304`（读尺寸 `:251`）| 越界判断 | ✓ 可加 severity/count |
| 3 | `pipeline/check_annotations.py:600`（另 `:606-615` 只查**单方向**）| 成员越界 | ✓ 可加 warning；**注意**：`binary_size` 的使用**不止此处**（globals/union/nested 也用 ✗）⇒ 改造**不能只 patch 一个 if** ✓ |
| 4 | `tools/scan_misattribution.py:459`（加载 `:142`）| 尺寸参与 impossible 判断 | ✗ **初稿指错了位置**：`:142` **只是构建 dict** ✓；且该工具**默认写状态文件**（`:630`）✗ ⇒ 接入前须支持 stdout/explicit-out ✓ |
| 5 | `tools/audit_structural_attribution.py:116`（加载 `:69`）| 尺寸比较 | ✗ **无机器可读通道**（全库模式只有 print + exit 0；仅 `--addr` 写 `/tmp` ✓）⇒ **必须先加 JSON/stdout 协议** ✓ |
**独立性口径（三路一致）**：`ida_structs.json` 是**本地再生产物且被注解污染** ✓ ⇒ **不得当独立归属真值**，只能提供待核对线索 ✓

## §5.5 闸的接线与活性（"逐闸毕业生效"的必要条件）
1. **必须真的串到写盘路径** ✗→✓：`cmd_check()` 现在只 `subprocess.run(check_annotations.py)` ✓；**`cmd_apply`/`cmd_export` 不调用它** ✗ ⇒ **只改 `cmd_check` 就是空门** ✓；正面先例：`tools/apply_annotation_batch.py:241` 已先跑 `cli.py check` ✓
2. **注入式负例升为验收必跑命令** ✓（不能只作 §4 表格一列 ✗）—— 元教训：两起 `--help` 事故的"回滚成功"**没有留下负例** ✗ ⇒ **"回滚成功" ≠ "门禁能防住下一次"** ✓
3. **恒假检测** ✓：某闸连续 N 次运行呈"全 `INCONCLUSIVE` / 零判据"⇒ **报警**（而非报 PASS ✓）—— 否则"恒 INCONCLUSIVE"就是**新的"恒真"** ✗
4. **单一责任人 = 用户本人** ✓（本仓为单人 + AI 会话；**AI 会话不得列为责任人** ✗ —— 会话结束即无人，这正是 `check-gstack.sh` 恒 deny 至今未修的原因 ✓）
5. **接线实测状态（Codex）**：`codegen_invariants` 默认检查集 = **A/B/D 硬失败 ✗**（实测 **A=132 exit1 · B=56 exit1 · D=10 exit1**），**C 仅 strict 失败**（**C=27 exit0** ✓）⇒ **只能先接 C 为 advisory + whitelist** ✓，**A/B/D 须各自建存量清单、修复或 grandfather 后再逐项升硬** ✓ —— 初稿"29 条"**只数了 C** ✗，错了约 200 条 ✓

## §7.5 本设计自身的沉淀与接线（防重演"审计→status→消失"）
**病灶校正**：不是"没落盘"，而是**"落错面"** ✗ —— `data/status/` **373 文件 / 293 tracked** ✓，而知识库对它只有 `CLAUDE.md:159,162` 两处引用（且当"基线输入路径"✓，**非知识入口** ✗）；`docs/knowledge/README.md:13` 明令"门禁失效/流程漏洞"须写 gotcha，**审计的核心发现恰好全属此类却一条未进** ✗
**四条可检查要求**：
1. **哪类结论进 `docs/knowledge/`**：通用规律/门禁坑进 knowledge ✓；单字段证据仍归 `data/annotations/CHANGE_LOG.md` ✓；**证据台账跨了这条边界 ⇒ 必须显式指定归属** ✓
2. **写入触发器**：台账某类的 `size_evidence_state` 发生**类别变化**时，由谁、在哪个 commit 提炼成 knowledge 条目 ✓
3. **可发现性**：`evidence_ledger.json` **必须在 `docs/knowledge/MEMORY.md` 有入链条目** ✓，并登记进 README 的"引用前验证"清单 ✓
4. **本纪律自身要落盘**：把"审计 → status → 消失"写成一条 **gotcha** ✓ —— 它现在只存在于 `data/status/_knowledge_process_diagnosis_20260920.md:56` ✗，**又一个"诊断只落在 status"的实例，递归证明本节必须加** ✓
**台账 schema 强制字段**：`schema_version` / `input_hash`（输入=注解+tracked exe 快照 ✓）/ `generator_version` / `generated_at` ✓；**clean-checkout 可复现** ✗：`original/*.asm` 与 `asm/` **均 gitignore** ✓ ⇒ 台账必须能从 **tracked 输入**（exe）复验 ✓，**不得假设本地 asm/export 存在** ✓
**单向红线**：`evidence_ledger.json` **禁止任何自动/半自动"按 ledger 回写注解"通路** ✗（否则绕一圈重建"同源污染" ✓）
