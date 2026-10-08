# 命名仲裁设计（v3 · 经 kiro 独立复核修订，范围拆分）

**日期**：2026-10-08
**状态**：v3 · **范围已按 kiro 建议拆分为两个独立可交付物**
**依据**：全二进制实证（项目红线）
**前序**：`data/status/_vtable_fix_plan_v3_20261008.md`（**本设计的核心例证已被该文档的 S2/S3 方案解决**，本设计是其**一般化**）

---

## 0. 范围定位（kiro 建议 7：拆分）

> **核心问题**：v2 把一个**已有更简单、更具体、更早被交叉验证过的解法**（`_vtable_fix_plan_v3_20261008.md` 的 S1-S3：枚举冲突 → 按 vtable `from:None` 根表槽判定 → 删除污染条目 + 轻量审计器）当成"待设计问题"重新展开成 7 阶段大计划，**没交代为什么不采用现成方案**。
>
> **v3 修正**：拆成两个独立可交付物，**低风险与高风险变更不打包一次验收**。

| 交付物 | 内容 | 风险 | 验收 |
|---|---|---|---|
| **A（低风险，可立即做）** | 修 120 冲突 + 冲突检测器 | 低 | 注解可回退；产物 byte-equal |
| **B（高价值，单独立项）** | owner schema + 二进制裁判 + 棘轮治理 | 中 | 单独验收 |

---

## 1. 背景与问题（已核实部分）

### 1.1 当前退化

| 指标 | 基线（10-06） | 现在 | 备注 |
|---|---|---|---|
| S2 | 108/**209** | 86–88/**210** | **分母变了，不可直接比** |
| 总错误 | 1515 | **2054** | C2440 375 / C2664 239 / C2039 236 / C2228 160 / C2273 138 / **C2660 131** / … |
| 退化单元 | — | **23**（改善 1）| 20 个 ok→fail，0 个 fail→ok |

### 1.2 病灶链（已实测）

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

### 1.3 已核实的发现（F1–F10，经 kiro 独立复核）

| # | 发现 | 状态 |
|---|---|---|
| **F1** | 120/120 冲突地址至少含 1 条 `vtable_gap_fill_v1`（批量复制产物）| ✅ 证实（措辞需精确）|
| **F2** | `check_export_annotation_consistency.py:9` 自认"注解的副本，而非 IDB 状态的证据" | ✅ 证实（⚠️ `audit_layout.py` **已删除**，不应再作对比基准）|
| **F3** | `sorted()` 翻 **60/120** 胜出者；字母序系统性偏向 `C*` 压过真根类 | ✅ **精确复现** |
| **F4** | `UIWnd.h:45` 与 `CGameData.h:208` 并存 `// 0x00445D10` 是**合法虚覆写** | ✅ **行号精确** |
| **F5** | `this->UIWnd::OnMessage()` vs `this->OnMessage()` **字节不同** | ✅ **VC6 实测：限定形被完全内联，非限定形保留 `FF 10` 间接派发** |
| **F6** | C1 **不是**本轮退化根因（本机 `os.listdir` 哈希恒定、git 无文件增删）| ✅ **精确** |
| **F7** | 20 个 ok→fail 单元自身 struct JSON 全未被改 | ⚠️ **无法判定**（缺可独立核验的产物引用）|
| **F8** | 爆炸半径被低估 | ✅ **实测 43 个生产模块读 `methods`**（非 16+）；`tests/` 实测 **5-7**（非 15）|
| **F9** | 机械消解上限 **24/120**，队列 **96** | ✅ 核心数字复现（⚠️ `from-chase` 全仓零命中，新术语未定义）|
| **F10** | `cli.py:980,1011` 使**整个 `match` 阶段**被 TOLERATED | ✅ **行号精确** |

### 1.4 kiro 独立发现的**更精确病灶**（P0-1 修正）

> `vtable_gap_fill_v1` 批量工具是**从 `CGameData.json` 往 `UIWnd.json`/`PalScript.json` 复制**，
> **复制方向与 vtable `from` 证据正好相反**（`CGameData` 自己的 vtable 槽标 `from:"UIWnd"`
> ⇒ `UIWnd` 才是真根）。
> ⇒ 这比"同簇他类或 codegen"的泛化归因精确得多。

---

## 2. 交付物 A（低风险，可立即做）

### A1. 只读审计：枚举 120 冲突 + 机械消解

```python
# 可机械消解判据（kiro 已验证）：vtable 槽 from=None 的唯一类 = 真属主
# 实测 24/120 可解，96 转队列
```

### A2. 按 v3 doc S2 方案处理 24 个可解项

- **删除被 `vtable_gap_fill_v1` 污染注入的 `methods` 重复条目**
- **保留 vtable 继承记录**（`from` 字段）
- ⚠️ **不动**合法的多类声明（`UIWnd.h:45` 与 `CGameData.h:208` 并存是合法虚覆写）

### A3. 冲突检测器（轻量，扩展现有工具）

**不新建工具**（避免第 8/9 个归属工具的"双真相源"反模式）；扩展 `tools/audit_attribution_evidence.py`：
- 修 `reconcile()` 的**自比对漏洞**（`src = s.get('from') or cls` ⇒ owner 恒匹配自身）
- 输出 `(source 溯源属主, live IDB 类名, vtable from)` 三元组 + 一致性判定

### A4. 确定性修复（C1 扩面）

统一改走 `pipeline/gen/annotation_view.iter_structs`（**已 sorted**，红线指定的单一读点）：
| 站点 | 行号 | 现状 |
|---|---|---|
| `pipeline/ida/apply_annotations.py` | `:1331` | `os.listdir` |
| `pipeline/ida/export_full.py` | `:197/218` | `glob.glob` |
| `pipeline/check_annotations.py` | `:38` | `os.listdir` |
| `tools/verify_fix.py` | `:388` | `os.listdir` |
| `tools/audit_retn_param_count.py` | `:137` | `os.listdir` |

⚠️ **`sorted()` 不是中性一行**（F3）：必须配合 A2 的属主修正，否则会翻转正确属主。

### A5. 确定性测试

`tests/test_annotation_determinism.py`：
- shuffle `os.listdir` 30 次 × `PYTHONHASHSEED=random` × 3
- 断言 `load_annotations()['functions']` 的 `{addr:(class,name)}` **逐字节相同**
- 断言同名 struct 覆盖 == 0（当前 **17 对**）
- **⚠️ 盲区**：只测确定性**不测正确性**（清理错了方向也会全绿）⇒ 配合 A2 的属主核对

### 交付物 A 验收

| 判据 | 命令 |
|---|---|
| 24 个可解项属主正确（有二进制证据）| `audit_attribution_evidence.py` |
| 产物 byte-equal | `pipeline/gen/test_pipeline.py` + diff |
| 确定性 | `tests/test_annotation_determinism.py` |
| 不破 L1 | `cli.py match` **当场读** |
| 注解可回退 | git（924 文件跟踪）|

---

## 3. 交付物 B（高价值，单独立项）

### B1. 独立二进制裁判 `tools/audit_attribution_binary.py`

**kiro 已用 ~30 行 Python 跑通**，可直接基于其验证代码起步：
- 解析 PE 头拿 `.text`/`.rdata` 的 VA↔文件偏移映射
- 读 `.rdata` vtable 槽值（4 字节小端）
- 扫 `.text` 的 ctor `mov [ecx], offset vtbl_X`（字节模式 `C7 01` + imm32）
- **产出冻结 JSON + SHA256**（离线可复现、可 CI）
- ⚠️ **验收需加"抽样人工核对字节与注解"**（SHA256 稳定 ≠ 读取逻辑无 bug）

### B2. 补 `base_class` 链（**P1-5 的前置**）

⚠️ **`UIWnd.base_class` 和 `CGameData.base_class` 都是 `None`** —— 继承链缺失
⇒ `ancestors()` 算法失明、未来的 `owner` 回退逻辑也会失明
⇒ 先把 `UIWnd`/`CGameData`/`SceneObj` 已有考古结论写回 `base_class`

### B3. `owner` 字段（**不拆 schema**）

`methods[addr]` 加可选 `"owner":"Cls"`（**唯一形态**；`disposition` 三值不在范围）
- 读点缺省回退旧语义（**非破坏**）
- ⚠️ **术语撞车**：`tests/test_owner_self_drop.py` 的 "owner" 是对象表达式链，**与本字段无关**

### B4. 未决项棘轮

`data/annotations/vtable_ownership_evidence.json` **已存在**（45 条记录，**零代码读者**）
⇒ **三选一**（不能沉默）：① 废弃重建 ② 迁移 45 条 ③ 改 schema
⇒ `cli.py check` 对 `unresolved` 计数做**只降不升棘轮**
⇒ **`--rebaseline` 必须加滥用防护**（理由含 issue/commit 引用，或长度约束）

### B5. 修 TOLERATED 粒度（P2-7 形式化）

现状：`cli.py:980,1011` 只按**阶段名**匹配 ⇒ 整个 `match` 阶段永久豁免
**形式化定义**：`tolerated = (stage, specific_reason) in expected_red_set`
- `specific_reason` 来自 `_loop_parse()` 的结构化字段（如 `L1 棘轮`）
- 匹配失败 ⇒ 非 TOLERATED ⇒ 真退化可见

### 交付物 B 验收

| 判据 | 命令 |
|---|---|
| 独立裁判冻结 JSON SHA256 稳定 | `audit_attribution_binary.py` |
| **抽样人工核对字节与注解** | 新增（B1 修正）|
| `base_class` 链正确 | `audit_attribution_evidence.py` |
| `owner` 字段 16+ 消费点零破坏 | 全量测试 |
| `unresolved` 棘轮生效 | `cli.py check` |
| TOLERATED 条件级豁免 | `cli.py status` |

---

## 4. 硬约束（不可违反）

| # | 约束 | 来源 |
|---|---|---|
| **L1 字节安全** | `this->UIWnd::OnMessage()` 直调（可内联）vs `this->OnMessage()` 虚分派（`FF 10`），**字节不同** | `ast_transform.py:1448-1451` + kiro VC6 实测 |
| **多类声明合法** | `CGameData.h:208` 与 `UIWnd.h:45` 并存 `// 0x00445D10` 是合法虚覆写，**不得去重** | `emit_headers.py:938-940` |
| **禁止双真相源** | 不新建第 8/9 个归属工具；扩展 `audit_attribution_evidence.py` | `.git/hooks/pre-commit` 注释 |
| **禁止批量未验证改动** | `vtable_gap_fill_v1` 是 120 冲突根源 | CLAUDE.md |
| **禁止仅凭 signature this 修归属** | 必须有 decomp member access evidence | CLAUDE.md |
| **export 不读 annotation** | `export_full.py` 只能从 IDB 读 | CLAUDE.md |
| **codegen 注解读取经单一读点** | `annotation_view.py`（**A4 正在修这条**）| CLAUDE.md |

---

## 5. 回退（**修正 v2 的过度悲观**）

| 层 | 可回退？ | 机制 |
|---|---|---|
| 注解（924 文件）| ✅ | git |
| **IDB 命名** | ✅ | **`apply` 是幂等、注解驱动**（`apply_annotations.py:1952` "Un-name stale functions"）⇒ 命名是**派生状态**，重新 `apply` 即可 |
| IDB 二进制 | ❌ | 不跟踪、无 unapply（**但与命名修复无关**）|
| `asm/`（decomp）| ❌ | gitignored ⇒ 可重新 `export` |
| `methods.owner` | ✅ | 缺省回退旧语义（非破坏）|
| 冻结裁判 JSON | ✅ | git |

⚠️ v2 把"IDB 二进制不可回退"与"IDB 命名不可回退"混淆 —— **后者实际风险远低于前者**。

---

## 6. 与前序文档的关系

| 文档 | 内容 | 与本设计的关系 |
|---|---|---|
| `data/status/_vtable_fix_plan_v3_20261008.md` | S1 只读审计 / S2 修命名 / S3 冲突审计器 | **核心例证已被其解决**；本设计是**一般化**（从 2 个簇 → 120 个冲突）|
| `data/status/_vtable_fix_plan_20261008.md` | v2 修复方案 | 已被两路对抗复核推翻，仅作历史 |
| `data/status/_vtable_next_step_plan_v2_20261008.md` | vtable 待办 | `/GR`、T3、T2、T4 仍在队列 |

---

## 7. 残留与不确定

| # | 项 | 状态 |
|---|---|---|
| 1 | **F7 无法判定** | 20 个 ok→fail 单元清单缺可独立核验的产物引用 |
| 2 | **`from-chase` 术语未定义** | 全仓零命中，是本设计新引入概念，需落地成代码 |
| 3 | **消费者计数方法不一致** | 43（生产）/ 5-7（tests）vs v2 的 16+/15 ⇒ 验收分母需先稳 |
| 4 | **`vtable_ownership_evidence.json` 45 条** | 零读者，需三选一处置 |
| 5 | **C1003 截断单元数量有争议** | CLAUDE.md（09-28）说 2 个；复核 #2 实测 1 个（`UIScene.cpp`）|
| 6 | **L1 形态逐点字节证据** | F5 已证字节不同，但改后是否真破 L1 未实测 |
| 7 | **本机 vs 跨机确定性** | 本机恒定（F6）；跨环境不恒定（tmpfs vs ext4）|

---

## 8. 与 v2 的差异（kiro 建议全采纳）

| # | 建议 | v3 处理 |
|---|---|---|
| 1 | 先用 v3 doc S1-S3 修当前例 | **交付物 A2**（24 个可解项，今天可做）|
| 2 | P1-5 前补 `base_class` 链 | **交付物 B2**（前置）|
| 3 | P1-4 基于 kiro 验证代码起步 | **交付物 B1**（~30 行已跑通）|
| 4 | 先修 `audit_attribution_evidence.py` 自比对漏洞 | **交付物 A3** |
| 5 | P2-6 加 `--rebaseline` 滥用防护 | **交付物 B4** |
| 6 | 处理 `vtable_ownership_evidence.json` | **交付物 B4**（三选一）|
| 7 | **范围拆分为两个独立可交付物** | **A（低风险）/ B（高价值）** |

**其他修正**：F7 标"无法判定" · F8 数字改 43/5-7 · `audit_layout.py` 删除引用 · 回退路径修正（命名可回退）· 术语撞车警示 · 验收加"抽样人工核对" · P2-7 形式化定义