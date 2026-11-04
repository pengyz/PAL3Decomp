# 转换器完备性与正确性证明——设计 spec

日期：2026-11-04 · 状态：待对抗复核 · 前序：review_bypass_drift_20261103.md（旁路复盘）、review_multiclaim_audit_20261103.md（adjudication 缺口实锤）

## 0. 意图与边界

**目标**：把「B 转换器（annotation → B 面标准数据）正确且完备」从宣称变成**可执行证明**，并门禁化——此后转换器任何改动必须过证明链。

**证明对象的边界（防证错对象）**：转换器只对「**忠实搬运 annotation 语义**」负责。annotation 本身对二进制为真是 A 面真值轴（A 级证据/字节棘轮）的事，不在本证明域内。

**范围裁定（用户裁=甲案）**：完备性域=**annotation 全语义域**——含 known_members/methods/vtables/bases/inline-union dict 形/adjudication/owner/evidence/name_source/global/type 字段族。不转字段须显式「dropped+理由」，禁「域外」静默丢（2026-11-03 实证：adjudication 漏转正是「域外」思维产物）。

**约束**：标准数据通路（ghidra-mcp daemon 工具面+apply_changeset，禁旁路）· TDD（RED 先行）· 与既有纪律兼容（R15 纯函数先测、病灶层三问、防旁路三纪律）。

## 1. 证明模型

完备性=两个互补证明；正确性=传递保真：

```
矩阵（静态）：annotation schema 每字段 → 转换路径 → 验证方法 → 状态（transfer/verify）
  ≙ 完备性=可枚举可审计（无映射字段=不完备自证）
回读（运行时）：diff(project_b_facts(session), project_ann_facts(annotation)) = ∅
  ≙ 完备性实证 + 传递正确性
fixture（锚）：case-01 真值已知形全链零差 ≙ 形变不失真（正确性）
```

**证明失效条件（fail-loud）**：diff 非空 ∨ unverifiable 面无理由 ∨ 矩阵出现「静默丢」字段 ⇒ verdict=BROKEN ⇒ 门禁 exit 1。

## 2. 组件与接口

### 2.1 构件

| 构件 | 位置 | 职责 |
|---|---|---|
| `verify_b_import.py` | `ghidra_track/` | 回读对账核：daemon 回读 B 程序事实 → 投影 → diff → proof 报告 |
| `proof_matrix.json` | `ghidra_track/` | 字段覆盖矩阵（静态证明件，随 schema 演进） |
| `fixture_proof.py` | `ghidra_track/` | 金标链跑器：case-01 → gen_plan → plan_to_changeset → import_standard → 回读 → 零差断言 |
| `test_proof_matrix.py` | `tests/` | 矩阵完备性守护（schema 字段枚举×矩阵=全覆盖，新字段无条目=红） |
| `test_verify_roundtrip.py` | `tests/` | 投影/diff 纯函数测试（R15） |
| `test_fixture_proof.py` | `tests/` | case-01 全链零差（含 union 嵌套/thiscall/占位名形） |

### 2.2 关键接口契约

1. **`project_b_facts(session)`** → annotation 形事实（名/签/结构字段/全局/owner/adjudication 映射态）——B 侧事实的唯一取出口（TOS 单源）。回读工具面：`list_functions`/`get_function_info`/`list_data_types`/`get_data_type` 等 ghidra-mcp 标准工具。
2. **`diff_facts(expected, actual)`** → 五类：`match`/`missing`/`changed`/`extra`/`unverifiable`——纯函数。
3. **矩阵驱动测试**：遍历 annotation schema 字段断言矩阵条目存在——完备性随 schema 演进自动守护。
4. **门禁接入**：fixture_proof 进 pre-commit/loop 检查点（转换器三文件 gen_plan.py/plan_to_changeset.py/import_standard.py 改动时必跑）；红=exit 1 不静默。

### 2.3 失败面（unverifiable 显式语义）

daemon 回读面缺口（如 adjudication 字段 B 侧无对应存储=只能验「效果」不能验「字段」）⇒ 矩阵 `verify: indirect:<效果验法>` + 回读报 unverifiable 带理由。**禁把不可验当已验**；unverifiable 无理由=红。

## 3. 测试与实施序

TDD · RED 先行：

1. **RED**：`test_verify_roundtrip` 含「adjudication 漏转」用例（现必红=已知缺口当第一条红）。
2. diff 引擎+投影纯函数（R15）→ GREEN。
3. `verify_b_import.py` CLI 接线（daemon 回读面）→ 真实 session 首份 proof 报告（预期 BROKEN：adjudication/inline-union/owner 三缺口显形=矩阵首批「待转」条目）。
4. `proof_matrix.json` 初版（全语义域枚举）+ `test_proof_matrix` 红→补矩阵→绿。
5. 修转换器缺口：adjudication 消费（gen_plan 跳 rejected/prefer confirmed+owner）· inline-union dict 形（显式「拒转+理由」或转 union）· owner 转 → 回读 proof 转 PROVEN。
6. `fixture_proof.py`（case-01 全链）→ 零差 → 门禁接线。
7. **B 面现状重看**（被证明的转换器重灌=读数才可信）。

## 4. 错误处理

| 面 | 处置 |
|---|---|
| diff 非空 | 报告逐条（field/expected/actual/转换路径）⇒ BROKEN exit 1 |
| 回读工具缺口 | unverifiable+理由入矩阵；无理由=红 |
| fixture 非零差 | 逐形分类（丢真/形变/发明）——转换器病修转换器，**禁改 fixture 迁就** |
| 证明件变更 | 矩阵/验证器改动=证明契约变更 ⇒ 全链重证+commit 注明 |

## 5. 完成判据

`fixture 零差 ∧ 矩阵全字段有归属 ∧ 真实 session proof=PROVEN（或 BROKEN 面全部显式入矩阵）` ⇒ 「正确且完备」成立 ⇒ 进 B 面现状重看（步骤 3.7）。

## 6. 已知缺口清单（首份 proof 预期红项）

| 缺口 | 出处 | 处置方向 |
|---|---|---|
| adjudication 不消费（败者条目进 plan） | 2026-11-03 25367 三连不变实锤 | gen_plan 过滤+prefer |
| inline-union dict 形被降级 byte | import_standard coerce 实证 | 拒转+理由 或转 union |
| owner 字段不转 | 转换链现状 | 转（方法归属维）|
| vtables | 待矩阵裁 | 预期 dropped+理由（Ghidra 重算）|

## 7. 非目标

- annotation 对二进制的真值验证（A 面真值轴）
- 引擎缺口（union 视图/型一致性/B3 机制）——另账
- B 面全树编译质量战（已裁定非本阶段目标）
