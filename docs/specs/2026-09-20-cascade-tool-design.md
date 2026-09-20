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


---

# 复核后修订 + **Spike 范围**（2026-09-21，双路复核 Kiro + Codex 共同裁定）

## A. 本规格被推翻的 6 处（详见 `data/status/_d1_ledger.md`）
1. **§1/§8 的落点错** ✗：`emit_cpp.py::_detect_needed_includes` 是**面向 .cpp 的文本启发式** ✓，
   **不区分指针/按值** ✗；真正做「按值⇒include / 指针⇒前向声明」分流的是 **`emit_headers.py:1138-1167`** ✓，
   **且它已处理按值成员** ✓ ⇒ 原处方**落错文件** ✗。
2. **UIStatic 的真因不是"漏补 include"** ✗：基类改 248 后派生类仍 **156**/`base_size=152` ⇒
   **apply 把 248 字节基类塞进总长 156 的 UDT ⇒ 越界检查拒绝**（`apply_annotations.py:914/920/926/675/681` ✓）
   ⇒ 头文件消失 ✓ ⇒ 正确处方是「**派生布局 proposal + apply/export/codegen 验证**」✓，include 只作下游检查 ✓。
3. **§4① 的"平移"不完整** ✗：还要**平移派生类的自有成员 offset** ✓；**MI 缺 `bases` 偏移时必须降级**
   （`bases` 完整仅 **11/179** ✓、31 个 MI 中仅 10 个有完整偏移 ✓）⇒ 输出三态 `mechanical / proposal / unresolved` ✓。
4. **§4⑤ 的复用声明不成立** ✗：没有「`type={"union":[…]}` 自动跳过」的显式规则 ✓；实际跳过是 **同 offset 变体 +
   两个硬编码类 + `source` 文本含 `overlap` 的自由文本后门** ✗ ⇒ 必须**自建区间代数**，**不得继承该后门** ✓。
5. **§3/§5 的 `--apply` 写入通道不足** ✗：现有 writer **只支持 `set_size`** ✓、**非原子**（循环中逐文件保存 ✗）
   ⇒ **MVP 直接删除 `--apply`** ✓。
6. **§6 的 `risk_units=208/76`** ✗：那是**历史编译普查结果**，**不是扫描器可推导的普适值** ⇒ 必须拆为
   `estimated_exposed_tus` 与 `historical_observation` 两字段 ✓（**不得把历史数伪装成预测能力** ✓）。
**另**：UIStatic 的直接派生类是 **4 个**（`UIStaticEX`/`UIStaticFlip`/`UIStaticRM`/`UIStaticCB` ✓），非 2 ✗；
④ 还须覆盖**生成器语义**（codegen 为 scalar deleting destructor **自动生成 virtual dtor** ✓）；
数组/区间**不得复用** `check_annotations.py:54` 的估算器（`total` 被循环覆盖 ⇒ 非同长二维算错 ✗）。

## B. 历史教训（必须回填，避免重新发明 ✓）
- 同名工具 `pipeline/cascade_binary_size.py`（**05-23 建 / 06-08 删** ✓）已写明约束：
  **「只改 annotation 不改 TIL 不安全、必须 leaf-to-root」** ✓；`fb57ef3bf` 修过一批 **over-cascade** ✗
  ⇒ **绝不能把 delta 自动加到组合类 owner 尺寸上** ✓（owner **只报影响** ✓）。
- **3 起历史成功的手工级联** ✓：`UIWnd 88→68` · **`UIFrameWnd 132→72（41 个类）`** · **`Actor 596→820`（5 层，`PDB_size + n×224`）**
  ⇒ 真实模型是「**基类 + n × 嵌入次数**」而非线性平移 ✓；且**病灶更像"纪律未执行"** ⇒ ④ 仅 2 个类**不值得工具化** ✗✓。

## C. **Spike 范围（本阶段唯一要做的事）** ✓
**做**：`annotation_view` 读入 ✓ · **④完整泛化**（named union `is_union` ✓ + 生成器 scalar dtor ✓ + reverse usage ✓）·
**SI①最小实现**（直接派生类 + 其尺寸是否 stale ✓，三态 ✓）· **②③直接引用枚举**（按值成员 / 数组元素 ✓）
**不做** ✗：MI 推断 · overlap · `--apply` · 挂 check（**B① 已完成** ✓：union 门禁已接进 `cli.py check` 硬失败 ✓）
**成功判据** ✓：
1. B34 副本 ⇒ **必报** `tagRoleSlot → PalScript union` ✓
2. UIStatic 副本 ⇒ **必报 4 个直接派生类 + 8 个按值引用 + stale apply hazard** ✓
3. **关掉任一扫描器 ⇒ 注入测试失败** ✓（断言契约 ✓）
4. **仓库零写入** ✓
**退出判据** ✓：**若两个历史案例仍需生成物或编译结果才能解释 ⇒ 收缩为手工 checklist，不建全量工具** ✓
