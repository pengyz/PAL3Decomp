# 设计：`binary_size` 级联扫描与统一修复工具（cascade）

状态：**待用户复核** → 随后交 `subagent_kiro` + `subagent_codex` 双路对抗复核 → 转 `writing-plans`
日期：2026-09-20 ｜ 架构路径：**方案 A（一工具两模式 + dry-run + `--check` 钩子）** ｜ 范围：**全五类语义**

## 1. 背景（两起失败的共同机制：**注解层改动经 C++ 语义放大** ✗）
| 事件 | 机制 | 后果 |
|---|---|---|
| **B34** | 给 `tagRoleSlot` 加 **ctor/dtor** ⇒ 破坏含它的 **union 平凡性** | **208 单元 C2620** ✗、S2 76→0 |
| **UIStatic 152→248** | **基类尺寸级联**改变 `UIStaticFlip`/`UIStaticRM` **子类布局** | **76 单元 `C2079 uses undefined class`** ✗、L1 回归 ✗ |
**两起的证据都是 A 级** ✓（`??_L size=248`+ctor+vtable / `??_L` ctor/dtor 契约 ✓）——
**失败不在"证据"，而在"爆炸半径未评估 + 配套修改未同批"** ✗。
⇒ 需要一个工具：**改前扫描影响面** ✓、**统一配套修复** ✓、**输出修复范围** ✓。

**既有积木（复用，勿重造 ✓）**：注解里的 `base_class` 图 ✓ · `tools/mi_base_offsets.py` ✓ ·
`tools/apply_annotation_batch.py`（落盘 ✓）· **`tools/check_union_member_triviality.py`（本工具 ④ 的特例，泛化它 ✓）** ·
`pipeline/gen/stages/emit_cpp.py::_detect_needed_includes`（**只处理指针解引用 ✗ ⇒ 本工具需扩展到"按值成员"** ✓）·
`pipeline/gen/stages/emit_headers.py` 的 `_gap_*`/`_tail_*` 与按值成员 include 逻辑 ✓

## 2. 目标与非目标
**目标**
- G1 **五类级联扫描**（继承 / 按值成员 / 数组元素 / union 平凡性 / `_variants`·内嵌 union 重叠）✓，**只读** ✓。
- G2 **统一修复**：把"配套修改"（补 include 与完整类型、调子类布局、union 契约规避、重叠清单）**一次做完并落盘** ✓。
- G3 **输出修复范围**：受影响类/文件/动作/证据等级表 ✓ + `--dry-run` 的 unified diff ✓ + 可入 commit message 的摘要 ✓。
- G4 **事先报出**两次历史失败（B34 与 UIStatic 的回放 ✓）——**这是核心验收** ✓。
- G5 `--check` 钩子：可挂进 `cli.py check`，对**现存注解**报"未处理的级联隐患" ✓（advisory 起步 ✓，与 `codegen_invariants` 同模式 ✓）。

**非目标（明确不做）**
- ❌ **不判定 `binary_size` 的真伪**（证据仍由人/第二判据给 ✓）；工具只负责"爆炸半径与配套修改" ✓。
- ❌ **不自动编排管线** ✗（`apply→export→codegen→probe→match` 仍由既有流程/人执行 ✓；方案 C 被显式否决 ✓）。
- ❌ 不改 `apply`/`export`/codegen 的语义 ✗；❌ 不做"批量猜尺寸" ✗；❌ 不新增硬门禁（`--check` 先 advisory ✓）。

## 3. 接口（4 个子命令）
```
python3 tools/cascade.py scan  <Class> --new-size N           # 只读；输出五类影响面
python3 tools/cascade.py fix   <Class> --new-size N --dry-run # 输出将做的修改（不落盘）
python3 tools/cascade.py fix   <Class> --new-size N --apply   # 统一修复并落盘
python3 tools/cascade.py check [--advisory]                   # 对现存注解报级联隐患
```
- 护栏（沿用本仓范式 ✓）：**任何以 `-` 开头且非已知开关的参数 ⇒ 拒绝执行、不写盘** ✓（防 `--help` 覆盖产物 ✓）；
  缺输入 ⇒ `return 2` ✓；`scan`/`dry-run` **绝不写盘** ✓。
- 输出：人类可读表 + `--json <path>` 机器可读（含输入哈希与生成时刻 ✓，便于 stale 检测 ✓）。

## 4. 五类扫描器（各自判据）
| # | 类 | 判据（证据来源） |
|---|---|---|
| ① | **继承级联** | `base_class` 图反查派生类 ✓；**子类尺寸随基类尺寸平移** ✓；子类是否被**按值**使用 ✓ |
| ② | **按值成员** | 注解 `known_members[*].type` 为**类名（非指针、非内联 dict）** ✓；**跨 header** ⇒ 检查生成头里该类型**是否完整可见** ✓（`C2079` 的成因 ✓）|
| ③ | **数组元素** | `T name[N]` / 内联 `tagX[N]` 的元素类型 ✓（B34 的 `tagRoleSlot[64]` / `Role[50]` ✓）|
| ④ | **union 平凡性** | 泛化 `check_union_member_triviality`：union 的**按值成员类不得有 ctor/dtor 形态方法**（名==类名 或 `~类名` ✓）|
| ⑤ | **`_variants` / 内嵌 union 重叠** | 新尺寸是否使 `[old, new)` 与**已有重叠声明/成员**冲突 ✓；内联 `union`/`struct` 的区间 ✓ |
**输出每项须带**：`class / file / kind(①–⑤) / action / evidence_grade / risk_units(受影响编译单元数估计)` ✓

## 5. 修复动作（统一 fix，全部可审计 ✓）
| 受影响项 | 动作 |
|---|---|
| ②③ 跨 header 的按值成员 | **补 `#include` 或前置完整定义** ✓（**扩展** `emit_cpp` 的 include 检测：新增"按值成员"规则 ✓）|
| ① 派生类 | 若子类尺寸需平移 ⇒ **同步调整**（并递归处理 ✓）；若子类被按值使用 ⇒ 回到 ②✓ |
| ④ union 成员 | 生成**规避方案**：改 union 视图（降级为扁平视图 ✓）或**不使用 ctor/dtor 名** ✓（**禁止伪语义名** ✗，遵 `CLAUDE.md` ✓）|
| ⑤ 重叠 | 输出**逐条冲突清单** ✓ + 建议（拆 union / 改 `_variants` ✓），**不自动改写语义** ✗ |
**⇒ 修复只做"配套性、可机械判定"的修改** ✓；任何涉及语义取舍的（④⑤ 的方案选择 ✓）**必须列清单交人裁决** ✓。

## 6. 验收（**核心：两个历史失败必须能被 `scan` 事先报出** ✓）
| 负例 | 期望（`scan` 必须报出） |
|---|---|
| **回放 B34**：副本里给 `tagRoleSlot` 加 `tagRoleSlot()`/`~tagRoleSlot()` | 报 ④ **union 平凡性将被破坏** ✓，并给出受影响单元数（应为 **208** ✓）|
| **回放 UIStatic**：`UIStatic 152→248` | 报 ① **2 个派生类**（`UIStaticFlip`/`UIStaticRM` ✓）+ ② 受影响按值成员所在 header 清单 ✓ |
| 无级联的类 | 报"无级联" ✓ 且 `fix --dry-run` **无 diff** ✓ |
| 注入式判别力 | 把上述任一负例的**扫描器关掉** ⇒ 验收必须**失败** ✓（断言契约，不是断言现状 ✓）|
**每批改动仍走"一批一管线"** ✓：`new_failures=0` · `L1==34` 不回退 · `s2 ok≥76` · `check` PASS ✓；
**总错误不作判据** ✓；破线即回退（**回退必须含 `apply→export→codegen→probe`** ✗ —— 只回退注解不够 ✓，B34 教训 ✓）。

## 7. 风险与缓解
| 风险 | 缓解 |
|---|---|
| **工具自身成为"恒假闸"** （本仓已多次发生 ✓）| ⑤ 的注入式负例作为**必跑命令** ✓；`--check` 先 advisory ✓；连续 N 次"零判据"即报警 ✓ |
| ①的"子类尺寸平移"假设过强（子类可能另有独立尺寸 ✓）| 只**报告**需人工确认的项 ✓；不自动改子类尺寸 ✗（除非可机械推导 ✓）|
| ②的"完整类型"判定可能漏（模板/前置声明 ✓）| 以**生成头 + 编译**为准：扫描后**必须**跑一批一管线验证 ✓（工具的报出是**必要非充分** ✓）|
| ⑤的重叠判定误报（`union` 本身即 overlap ✓）| 沿用 `check_annotations` 的既有规则（`type={"union":[…]}` 自动跳过 overlap ✓）|
| 工具与 `annotation_view` 单一读点冲突 | **必须经 `pipeline/gen/annotation_view.py` 读取注解** ✓（`CLAUDE.md` 红线 ✓）|

## 8. 开箱清单（实现计划将细化）
**新增**：`tools/cascade.py`（CLI）· `pipeline/gen/cascade/{inheritance,byvalue,arrayelem,uniontrivial,overlap}.py`（五类扫描器 ✓）·
`pipeline/gen/cascade/fixers.py`（统一修复 ✓）· `tests/test_cascade_*.py`（**含两个历史失败的回放负例** ✓）
**修改**：`pipeline/gen/stages/emit_cpp.py`（include 检测**新增"按值成员"规则** ✓）· `pipeline/cli.py`（`check` 挂 advisory ✓）·
`CLAUDE.md`（加"改 `binary_size` 前必须过 `cascade scan`" ✓）
