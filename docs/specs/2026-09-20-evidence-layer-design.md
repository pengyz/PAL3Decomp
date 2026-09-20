# 设计：注解证据层（Evidence Layer）—— 让"尺寸/归属"判据重新具备判别力

状态：**待用户复核**（随后交 `subagent_kiro` 与 `subagent_codex` 双向复核，再转 `writing-plans`）
日期：2026-09-20 ｜ 架构路径：**A（共享证据层 + 单一台账 + 薄消费者）** ｜ 执行模式：**逐闸毕业生效**

## 1. 背景（全部为已实测事实，出处见括号）
1. **判据的参照物被污染** → 现有闸判别力 ≈ 0：`pipeline/check_annotations.py` 报 `0 errors PASS`，
   而全库 881 个 struct 中 **91 个 `binary_size > 3× 最大成员末端`**，其中 **9 个精确 = 2×**
   （`safe_size = max_offset*2` 指纹）。（独立复核实测 + `tools/audit_layout.py:70-71` 3×/50× 阈值）
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
`codegen_invariants` 29 条 → `alloc_sizeof` 17 条 → 归属双源 27 条 → **尺寸污染 91 条（最后，部分属长尾）**。
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
  （B34 的 `C2065 'GetActorMgr'` 即此 ✓）⇒ 先按预期名单核销，不算新根因 ✓
- **超约束即回退**：回退＝恢复注解 → **`apply → export → codegen → probe`**（**只回退注解不够** ✗，
  IDB + `asm/pal3/ida_structs.json` 都是 stale 层 ✓）；禁止 `git checkout/restore/stash/clean -fd` ✓

## 7. 风险与缓解
| 风险 | 缓解 |
|---|---|
| `??_L` 的 `size` **不唯一**（8704 同时匹配 `Role`/`RoleSystem`）| **必须用 ctor 指针锚定元素类** ✓ |
| **ctor 归属本身可能错**（`sub_411CA0` 被注成 `~PalScript` ✓ 实测）| 台账记录**归属证据等级**；低等级不作结论 ✓ |
| 17 条 MISMATCH **不可自动落地**（混 base-subobject/phantom）| 逐条裁定 + 台账 ✓ |
| **91 条尺寸污染部分是"成员缺失"而非"尺寸错"**（14 条 HIGH 已裁定）| 先分级；长尾单独批次 ✓，
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

## 9. 待用户复核时确认的两点
1. **"逐闸毕业生效"**（§5）是否符合你的"直接硬失败"意图 ✓
2. `placeholder` 判定三条规则（§3）是否采纳 ✓（尤其第 1 条 `2×` 指纹 ✓）
