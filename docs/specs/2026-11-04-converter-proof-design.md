# 转换器完备性与正确性证明——设计 spec v2

日期：2026-11-04 · 状态：v2（对抗复核 review_converter_proof_spec_20261104 R1-R10 修订后·待终审）· 前序：review_bypass_drift_20261103 · review_multiclaim_audit_20261103

> v2 变更：期望投影独立化（R1）· mutation 自证（R2）· 归一层+extra 域过滤（R3）· unverifiable 二分（R4）· 矩阵=语料扫描+分类账（R5）· 缺口清单+4 实测项（R6）· gen_plan 确定性修（R7）· fixture 独立 oracle+缺形补（R8）· 门禁触发面修（R9）· PROVEN/DROPPED 二态+导入前提（R10）。

## 0. 意图与边界

**目标**：把「B 转换器（annotation → B 面标准数据）正确且完备」从宣称变成**可执行证明**并门禁化。

**证明对象边界**：转换器只对「忠实搬运 annotation 语义」负责；annotation 对二进制为真归 A 面真值轴（复核确认边界切对）。

**范围（甲案）**：annotation 全语义域（known_members/methods/vtables/bases/inline-union/struct dict/adjudication/owner/evidence/name_source/global/type 族+skip/墓碑语义）。不转字段须显式 dropped+理由。

**约束**：标准数据通路（daemon 工具面+apply_changeset，禁旁路）· TDD · R15/病灶层/防旁路三纪律兼容。

## 1. 证明模型（v2 修补）

```
① 矩阵（静态）：语料机械键扫描（机器触发）+ 人写 disposition 分类账
     ≙ 完备性=可枚举可审计（无条目键=红）
② 回读（运行时）：diff(norm(project_b_facts(session)), norm(project_ann_facts(annotation))) = ∅
     ≙ 投影面内搬运保真——只证「没走样」，完备性由①+缺口显式分账补（复核裁定：diff=∅ 不直接等于完备）
③ fixture（锚）：独立 oracle（手写期望，禁从 annotation 派生）全链对拍 ≙ 正确性
④ mutation 自证（R2·新增）：向转换链注入 6 类已知错误，diff 必须逐类抓红
     ≙ 证明器自身有效（防假绿——复核裁定的最大风险件）
```

**投影独立性铁则（R1·假绿根防）**：`verify_b_import.py` **禁止 import 转换器模块**（gen_plan/import_annotation/plan_to_changeset/import_standard）——期望侧解析与归并语义**独立实现**，归并规则显式钉死=对齐 apply_annotations.py:1382-1385（first-wins+owner 优先+**sorted 遍历序**）并单测锁定。反例（复核实锤）：变体键 `int("144_1")==1441`（import_annotation.py:59）双侧同错=发明偏移被证正确=假绿。

**归一层（R3）**：norm() 单源——地址 int 归一（lstrip 陷阱禁）· 型名归一 · **extra 域过滤**（B 侧自动分析产物名/未认领函数不计入 extra，否则恒红）。

**unverifiable 二分（R4）**：
- 有载体效果验（indirect 可操作）：adjudication → 胜者名/签效果可验；owner → 归属效果可验
- 无载体二选一：**set_comment 载体转载**（CommandHandler.java:117 实存）或 dropped+理由入矩阵。evidence/name_source 走此路。**禁空话验法**（v1 的 indirect 表述不具可操作性=复核驳）。

**fail-loud**：diff 非空 ∨ unverifiable 无理由 ∨ 矩阵静默丢 ∨ **导入 fail>0 未入分账** ⇒ BROKEN ⇒ exit 1。

## 2. 组件与接口

| 构件 | 位置 | 职责 |
|---|---|---|
| `verify_b_import.py` | `ghidra_track/` | 回读对账核（独立投影·禁 import 转换器）|
| `proof_matrix.json` | `ghidra_track/` | 语料键扫描产物+disposition 分类账（transfer/verify/status）|
| `fixture_proof.py` | `ghidra_track/` | 金标链跑器（独立 oracle 对拍）|
| `mutation_proof.py` | `ghidra_track/` | 证明器自证：6 类注入→diff 必须逐类抓红 |
| `test_proof_matrix.py` | `tests/` | 语料键扫描×矩阵全覆盖（机器触发，非手维护）|
| `test_verify_roundtrip.py` | `tests/` | 投影/diff/归一 纯函数（R15）|
| `test_fixture_proof.py` | `tests/` | case-01+case-02 零差 |
| `test_mutation_proof.py` | `tests/` | 6 类注入逐类红（改名/移偏移/换型/删字段/多字段/调换多注胜者）|

**回读工具面（复核勘误正名）**：`list_functions`/`get_function_info`/`list_data_types`/`get_data_type`（FieldDetail 字段名/偏移/型/尺寸 GhidraEngine.java:960-965）/`get_global_variables`（CommandHandler.java:208；v1 误写 get_global_value）/`set_comment`（evidence 载体候选）。

**门禁接线（R9 勘误）**：触发面=转换器全链 5 件（**import_annotation.py（build_import_plan 真身 :38-81）**+gen_plan.py+plan_to_changeset.py+import_standard.py+verify 自身）改动必跑 fixture+mutation 二证。接线=仓内 pre-commit 钩子链+独立 `ghidra_track/gate.sh`（勘误：「pre-commit/loop」混称不成立——loop=IDA 轨 cli.py，B 面门禁独立立；daemon 互斥持库+端口 8432 环境约束随 gate 注明）。

## 3. 确定性与归并语义（R7·v1 遗漏）

- `gen_plan.py:17` glob **加 sorted**（现状=dict 覆盖序=文件系统偶然序 ⇒ 多注 232 组胜者随机器漂移，「可重放」不成立——且在证明域内）
- 归并 tie-break 钉死：**owner 优先 > adjudication=confirmed > sorted 类名序 > 首个**（对齐 apply_annotations.py:1382-1385 并单测）
- `plan_to_changeset` key 空间对齐 Changeset.java:313-322 targetKey（`fn-name:`/`global-name:` 分立——现状 `'name:'+addr` 同址函数+全局互吃）

## 4. 缺口清单（v2·补复核实测 4 项+形名勘误）

| 缺口 | 出处（复核实测）| 处置 |
|---|---|---|
| **变体键 int() 错位发明偏移**（`'144_1'`→1441·`'50814_0'`→508140）| import_annotation.py:59 · PalScript.json:659,666/SceneMgr.json:138/scVARIANT_data.json:13 | **真 bug 首修**：变体键解析修 |
| adjudication 不消费 | 25367 三连（session 记录·仓内无原始档=未复验项）| gen_plan 过滤+prefer（§3 tie-break）|
| define_global type 不转 | plan_to_changeset.py:22-24 vs 注释 :8 | 补 set_global_type op（词表支持 Changeset.java:252）|
| skip/墓碑不消费 | functions skip 199·globals skip 203+deleted 13·skip_functions.json 不读 | 转 skip 语义或 dropped+理由（A 侧语义 apply_annotations.py:2422-2423 对齐）|
| inline-struct dict 4 件+union 内嵌 dict 型 9+ 件降 byte | import_standard.py:28,33（**形名勘误**：顶层 union 已转 define_union import_annotation.py:63-69，降 byte 的是 inline-struct dict 族）| 拒转+理由 或转 |
| owner 不转 | 转换链现状 | 转（效果验）|
| vtables | — | dropped+理由（**勘误**：annotation vtables 带 slot from 归属字段 UIWnd.json，Ghidra 无从复现——理由=「带归属来源信息不可转」，非「Ghidra 重算」）|

## 5. fixture 要求（R8·v1 不实勘误）

v1 声称 case-01 含「union 嵌套/占位名形」**不实**（Complex.json:4 平 union·fixture `_todo_` 全库 0 命中）——新建 **case-02** 补缺形：嵌套 union/inline-struct dict/变体键形/占位名/adjudication 对。期望=**手写独立 oracle**（expected 文件人工写定，禁从 annotation 派生=防循环论证）；布局维现有机器 oracle（expected/layout.json:5）保留为布局独立源。

## 6. 实施序（v2 修订）

1. **RED-0**：变体键发明偏移 bug 复现测（import_annotation.py:59 病灶首轮修——独立于证明器）
2. **RED-1**：test_verify_roundtrip 含 adjudication 漏转用例（病灶真身=gen_plan.py:23-25 归并段——v1 挂错构件勘误）
3. 投影/diff/归一 纯函数（独立实现·R15）→ GREEN
4. verify_b_import.py CLI+真实 session 首份 proof（预期 BROKEN=缺口显形入矩阵）
5. proof_matrix.json（语料键扫描器+分类账）+ test_proof_matrix
6. **mutation_proof 6/6 抓红——不绿不得进下一步**（证明器自证门）
7. 修转换器缺口（§4 全表）→ proof 转 **PROVEN/DROPPED 二态分账**（R10）
8. case-02 fixture（独立 oracle）→ 零差 → 门禁接线（R9 触发面）
9. **B 面现状重看**（被证明的转换器重灌=读数可信）

## 7. 完成判据

`mutation 6/6 抓红 ∧ case-01/02 独立 oracle 零差 ∧ 矩阵语料键全条目 ∧ 真实 session proof ∈ {PROVEN, DROPPED 全显式}` ⇒ 「正确且完备」成立。导入前提（R10）：import_standard fail=0 或 fail 全入分账——实测 24 条「No transaction is open」仅计数不 fail-loud（import_standard.py:66-68）=违则，并入首修。

## 8. 非目标

annotation 真值验证（A 面）· 引擎缺口（union 视图/型一致性/B3）· 全树编译质量战。

## 9. 未复验项（复核移交·不判定）

25367 三连仓内无原始档 · 活体 daemon tools/list 未实测（依源码注册面）· get_data_type 回读序列化形未跑活样 · 时间成本未测 · dryRun 乐观锁行为 · case-01 report.json 现存 D1 act:null 全空（链现状未复跑）。
