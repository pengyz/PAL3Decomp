# 命名仲裁设计（v2 · 经两路对抗复核修订）

**日期**：2026-10-08
**状态**：待 kiro 独立复核
**范围**：修仲裁机制 + 120 同址多声明 + 8/21 归因并入
**依据**：全二进制实证（项目红线）
**表达**：`methods` 加 `owner` 字段（**不拆 schema**）
**成功**：机制验收 + 基线恢复

---

## 0. 背景与问题

### 0.1 当前退化

| 指标 | 基线（10-06） | 现在 | 备注 |
|---|---|---|---|
| S2 | 108/**209** | 86–88/**210** | **分母变了，不可直接比** |
| 总错误 | 1515 | **2054** | 当前 C2440 375 / C2664 239 / C2039 236 / C2228 160 / C2273 138 / **C2660 131** / C2227 128 / … |
| 退化单元 | — | **23**（改善 1）| 20 个 ok→fail，0 个 fail→ok |

### 0.2 病灶链（已实测）

```
data/annotations/structs/*.json 的 methods 同址多声明（120 个地址）
  ⇒ load_annotations() 合并（pipeline/ida/apply_annotations.py:1331）
  ⇒ 「首合并者胜出」且 os.listdir 非排序 ⇒ 胜出者随机
  ⇒ apply 用 set_name 写 IDB（:2033/:2037）
  ⇒ export 导出（decomp: name 与 signature 自相矛盾）
  ⇒ ast_transform.py:1419 的 first_arg.type=='this' 分支见 class_name 既非 cls_name
     也非其基类 ⇒ 落 else ⇒ :1466 broken 形
  ⇒ C2660/C2661
```

**实测**：`0x00445D10` decomp 的 `name: "CGameData::OnMessage(int,int,int)"` 但
`signature: "virtual int __thiscall(UIWnd *this, …)"` —— **自相矛盾**。

### 0.3 两条复核路线的**颠覆性发现**

| # | 发现 | 证据 |
|---|---|---|
| **F1** | 「120 多声明」**100% 是一次批量机器复制的产物** | `_d1_ledger.md:3600-3603`（2026-09-25 批次 A「methods 表跨类填充 176 条×53 类…全部复制入缺口类（`source=vtable_gap_fill_v1`）」）；**120/120 冲突地址都含 `vtable_gap_fill_v1`** |
| **F2** | **C2 的证据层是注解回声，不是二进制证据** | `tools/check_export_annotation_consistency.py:9` 原文：「vtables/methods/_variants **透传**进导出产物 `ida_structs.json` … 761/761 零不一致 ⇒ 这些字段是"**注解的副本**"，而不是"IDB 状态的证据"」；`audit_attribution_evidence.py:34` 就读该文件 ⇒ 与 `audit_layout.py` 的"同源比较、恒等、无判别力"同一失效模式 |
| **F3** | **C1 单独落地会翻转正确属主** | `sorted()` 翻 **60/120** 胜出者；字母序系统性偏向 `C*` 压过真根类 `UIWnd`；4 个有考古结论的址里 **3 个被选错**（`0x00445B90`→`CCBItemWindow`、`0x00445E70`→`CCBPanelSlot` 均被 `arch_gbui_seven_slot_vtables_inheritance_chain.md:22` 判为**漂移命名**）|
| **F4** | **C3 前提对 header 层不成立** | `pal3/src/Data/CGameData.h:208` 与 `pal3/src/UI/UIWnd.h:45` **都**有 `virtual int OnMessage(...); // 0x00445D10` ⇒ 多类声明在 header 层**已合法**；「首合并者胜出」只发生在 `load_annotations()` 的 functions 合并，**不在 header 发射路径** |
| **F5** | **L1 目标形态本身字节不安全** | `ast_transform.py:1447-1452` 原注释："unqualified `this->M()` on a virtual M compiles to vtable dispatch — **different bytes**"；`0x00445D10` 是 7 槽 vtable 的 slot6 |
| **F6** | **C1 不是本轮退化根因** | 同一 ext4 连续 6 次 `os.listdir` 哈希**恒定**（`bf57ee246a3053e2`）；`git log --diff-filter=AD --since=2026-09-20` = **0 条** ⇒ 本机胜出者在退化窗口内恒定 |
| **F7** | **20 个 ok→fail 单元自身 struct JSON 全未被改** | `git log` 空 ⇒ **病灶在同簇他类或 codegen 层，不在它们自己的注解** |
| **F8** | **爆炸半径被低估 3 倍** | 实测 **16+ 模块**读 `methods`（非 6）；**漏列 `ast_transform.py`**（设计声称要修的正是它）；另有 `tests/` 15 文件 + `.claude/hooks/validate-annotations.py`（写入守卫，schema 改动静默失效）|
| **F9** | **机械消解上限 24/120**（非 75/120）| 层②「全声明者 from-chase 收敛单根」= **24**，与层①**完全同集**（零新增）；**队列是 96 项而非 45** |
| **F10** | **TOLERATED 粒度过粗** | `pipeline/cli.py:980,1011` 使**整个 `match` 阶段**被豁免（不只 L1 棘轮）|

---

## 1. 七阶段架构

```
P0-1  归因（只读，不改代码）
  20 个 ok→fail 单元逐一 diff 生成物 + 关联注解变更
  ⚠️ 这些单元自身 struct JSON 全未被改 ⇒ 病灶在同簇他类或 codegen
        ↓
P0-2  C1 扩面：统一改走 annotation_view.iter_structs（已 sorted）
  apply_annotations.py:1331 · export_full.py:197/218 ·
  check_annotations.py:38 · tools/verify_fix.py:388 ·
  tools/audit_retn_param_count.py:137
        ↓
P0-3  确定性测试 tests/test_annotation_determinism.py
  shuffle os.listdir 30 次 × PYTHONHASHSEED=random × 3
  断言 load_annotations()['functions'] 的 {addr:(class,name)} 逐字节相同
  ⚠️ 当前应报 winner 变动 120 / 同名 struct 覆盖 17
        ↓
P1-4  独立二进制裁判 tools/audit_attribution_binary.py
  直接从 PAL3.exe / objdump -d 读 .rdata vtable 槽值 + ctor `mov [ecx],offset vtbl_X`
  ⇒ 产出冻结 JSON + SHA256（离线可复现、可 CI）
  ⇒ from 字段与冻结表冲突即报警（斩断注解回声）
        ↓
P1-5  加 owner 字段（不拆 schema）
  methods[addr] 加可选字段 "owner":"Cls"（本设计唯一形态；`disposition` 三值形态不在本范围）
  读点缺省回退旧语义（16 个消费点零破坏）
  ⚠️ 保留 emit_headers:938 多声明豁免（多类声明在 header 层已合法）
        ↓
P2-6  未决项暴露 + 棘轮
  data/annotations/vtable_ownership_evidence.json 显式 unresolved 段
  cli.py check 对 unresolved 计数做只降不升棘轮（推进需 --rebaseline "<reason>"）
        ↓
P2-7  修 C5 粒度
  tolerated 判定从「阶段名 ∈ red_gates」→「阶段名 + 失败条件」双匹配
  （否则 match 阶段永久豁免）
```

---

## 2. 组件

| # | 组件 | 职责 | 类型 | 复用/新建 |
|---|---|---|---|---|
| **P0-2** | `annotation_view.iter_structs` | 单一读点（已 sorted） | 改造 | **复用**（红线指定） |
| **P0-3** | `tests/test_annotation_determinism.py` | 确定性验收 | 新建 | — |
| **P1-4** | `tools/audit_attribution_binary.py` | **独立**二进制裁判 | 新建 | 参考 `audit_attribution_evidence.py` 的证据分类 |
| **P1-5** | `methods[addr].owner` | 显式属主 | schema 扩展 | **不拆 schema** |
| **P2-6** | `vtable_ownership_evidence.json` + 棘轮 | 未决项暴露 | 扩展 | 复用 `cli.py check` |
| **P2-7** | `pipeline/cli.py` tolerated 判定 | 粒度修复 | 改造 | — |

**不新建**：不建 `method_owner_resolver.py` / `conflict_audit`（避免第 8/9 个归属工具的"双真相源"反模式）

---

## 3. 数据流

```
data/annotations/structs/*.json
    │
    ▼ (P0-2 单一读点)
annotation_view.iter_structs  ←── 5 个消费者统一改走
    │
    ▼ (P1-4 独立裁判)
tools/audit_attribution_binary.py
    ├─ 读 PAL3.exe / objdump -d   .rdata vtable 槽值
    ├─ 读 ctor `mov [ecx], offset vtbl_X`  写入点
    └─ 冻结 JSON + SHA256  ──→  与注解 from 字段比对
                                 ├─ 一致 ⇒ 采纳
                                 └─ 冲突 ⇒ 报警 + 进 P2-6 unresolved
    │
    ▼ (P1-5)
methods[addr].owner = "Cls"（可选；缺省回退旧语义）
    │
    ▼
apply_annotations（读 owner 或回退）→ set_name 写 IDB
    │
    ▼
export → decomp（name = 二进制实证属主）
    │
    ▼
ast_transform:1419  class_name = 实证属主
    ⇒ 走 1443 合法分支
    ⚠️ 需逐点字节证据（F5）
    │
    ▼
codegen → probe（regression_detector 逐单元 (code,msg) 多重集）→ match（当场读 L1）
    │
    ▼ (P2-6/P2-7)
cli.py check：unresolved 只降不升棘轮 + TOLERATED 条件级豁免
```

---

## 4. 错误处理

| 场景 | 行为 |
|---|---|
| 二进制裁判与注解 `from` 冲突 | **报警 + 进 unresolved**（TOLERATED，不阻塞） |
| `owner` 字段缺失 | **回退旧语义**（首合并者胜）+ 记 unresolved |
| `from` 图有环（3 条已知回边）| **seen 集终止** + 记 cycle |
| 确定性测试失败 | **直接红**（非 TOLERATED） |
| L1 字节不安全 | **当场读** `cli.py match`（棘轮虽防滑落，仍须同轮读数） |

---

## 5. 测试（TDD）

| 组件 | 测试 |
|---|---|
| **P0-2** | 现有 `pipeline/gen/test_pipeline.py` 全绿；新增：5 个消费点改走后产物 byte-equal |
| **P0-3** | shuffle 30 次 × 3 seeds ⇒ winner 变动==0、同名 struct 覆盖==0 |
| **P1-4** | 合成 PE/.rdata fixture；冻结 JSON SHA256 稳定；from 冲突检测 |
| **P1-5** | 16 个消费点零破坏；缺省回退旧语义 |
| **P2-6** | 棘轮：unresolved 上升 ⇒ exit 1；`--rebaseline "<reason>"` 可推进 |
| **P2-7** | TOLERATED 条件级豁免：`match` 真退化不被豁免 |

---

## 6. 验收（判别力优先）

| 层 | 判据 | 命令 | 说明 |
|---|---|---|---|
| **确定性** | shuffle 30 次 winner 变动 == **0** | `tests/test_annotation_determinism.py` | v1 缺失 |
| **独立裁判** | 冻结 JSON SHA256 稳定；`from` 冲突数单调不升 | `tools/audit_attribution_binary.py` | v1 缺失 |
| **红线** | 每处 annotation 改动有二进制证据 | `audit_attribution_evidence.py`（**非** `verify_fix.py`） | v1 用错裁判 |
| **回归** | 逐单元 `(code,msg)` 多重集 | `tools/regression_detector.py`（剔 C1003 + churn + `--before/--after/--self-test`） | v1 用 S2≥108（分母已变） |
| **C1003** | 最大行号不下降 | `cli.py status` | ⚠️ 数量有争议（见 §9） |
| **L1** | **当场读** | `cli.py match` | v1 用 L1≥94（不可机验） |
| **marker** | `[MISATTRIBUTED]` 全仓 ≤ **83**（不增） | `grep -r` | v1 用两簇=0（但全仓 83 个） |

---

## 7. 回退

| 层 | 可回退？ | 机制 |
|---|---|---|
| 注解（924 文件）| ✅ | git |
| **`asm/`（decomp）** | ❌ | gitignored ⇒ **P0-1 前先建 IDB↔annotation 一致性基线** |
| **IDB（87MB）** | ❌ | 不跟踪、无 unapply |
| `methods.owner` 字段 | ✅ | 缺省回退旧语义（非破坏） |
| 冻结裁判 JSON | ✅ | git |

---

## 8. 硬约束（不可违反）

| # | 约束 | 来源 |
|---|---|---|
| **L1 字节安全** | `this->UIWnd::OnMessage(...)` 直调 vs `this->OnMessage(...)` 虚分派，**字节不同** ⇒ 改发射形态须逐点字节证据 | `ast_transform.py:1447-1452` |
| **多类声明合法** | `CGameData.h:208` 与 `UIWnd.h:45` 并存 `// 0x00445D10` 是合法虚覆写，不得去重 | `emit_headers.py:938-940` |
| **禁止双真相源** | 不新建第 8/9 个归属工具；扩展 `audit_attribution_evidence.py` | `.git/hooks/pre-commit` 注释 |
| **禁止批量未验证改动** | `vtable_gap_fill_v1` 是反例（120 冲突根源） | CLAUDE.md |
| **禁止仅凭 signature this 修归属** | 必须有 decomp member access evidence | CLAUDE.md |
| **export 不读 annotation** | `export_full.py` 只能从 IDB 读 | CLAUDE.md |
| **codegen 注解读取经单一读点** | `annotation_view.py`（尚有 3 处直读待收敛） | CLAUDE.md |

---

## 9. 残留与不确定

| # | 项 | 状态 |
|---|---|---|
| 1 | **C1003 截断单元数量有争议** | CLAUDE.md（2026-09-28 复核）说 **2 个**（`CCBStage.cpp`/`free_functions.cpp`）；复核 #2 实测 status 报 **1 个**（`UIScene.cpp`）⇒ **需实测定谳** |
| 2 | **P0-1 归因结果未定** | 20 个 ok→fail 单元的病灶在同簇他类或 codegen 层，**具体是哪一层未定** |
| 3 | **L1 形态的逐点字节证据** | F5 已指出不安全，但**改后是否真破 L1 未实测** |
| 4 | **`source` 溯源字段** | 也是注解元数据（批量工具写入）⇒ 可作候选但需二进制裁判确认 |
| 5 | **`from` 字段只读无人写** | 17 对同名 struct 覆盖问题（P0-3 需测）|
| 6 | **本机 vs 跨机确定性** | 本机恒定（F6），跨环境不恒定（tmpfs vs ext4）|

---

## 10. 与 v1 的差异（5 处推翻 + 4 处新增）

| 类型 | 项 | v1 | **v2** |
|---|---|---|---|
| 推翻 | C1 | 一行 `sorted()` | **改走 `annotation_view.iter_structs`**（5 站点）|
| 推翻 | C2 | 三层证据消解 75/120 | **独立二进制裁判**；上限 24/120，队列 96 |
| 推翻 | C3 | 拆 `methods`/`defines`/`inherits` | **加 `owner` 字段**（不拆 schema）|
| 推翻 | C4 | 45 项人工 + `verify_fix.py` | **96 项** + `audit_attribution_evidence.py` |
| 推翻 | C5 | TOLERATED 范式 | **修粒度**（阶段名+失败条件）|
| 新增 | — | — | **P0-1 归因** |
| 新增 | — | — | **P1-4 独立二进制裁判**（斩断注解回声）|
| 新增 | — | — | **P0-3 确定性测试** |
| 新增 | — | — | **IDB↔annotation 一致性基线**（C3 之前必建）|