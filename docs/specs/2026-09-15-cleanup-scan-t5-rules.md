# t5 triage 强制规则（captain 追加，2026-09-15）

本文件是 `docs/specs/2026-09-15-cleanup-scan-taxonomy.md`（分类学）与
`docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md`（裁决）的**消费侧规则集**：
t5 的产物（`data/status/_cleanup_scan_triage.json` + `docs/specs/2026-09-15-cleanup-scan-triage.md`）
**必须**逐条满足以下规则，缺任一条即视为 t5 不合格。

---

## 0. 基线锚点（三次独立复核一致，固定不变）

| 门禁项 | 锚点 | 复核来源 |
|--------|------|----------|
| L1 字节全同函数数 | **≥ 5** | `data/status/s4_baseline.json` → `stats.match_L1 = 5`（我 `python3 pipeline/cli.py match` 实跑输出 `L1 5`、`[L1 ratchet] previous 5 -> current 5`） |
| S2 ok 文件数 | **≥ 53 / 198** | `data/status/baselines/latest.json`（name `20260915_100946`）→ `ok=53, fail=145, total=198` |
| 分母变动 | **198 变动即判"不可比"** | captain 裁定 + spec §4.6 |

**全局否决规则（captain 背书，不接受例外）**：任一条修复若使 **L1 或 ok 回退**，
**该条修复判失败**，不接受"整体净收益"式辩解。

---

## 1. 新增类别 `M_UNDETERMINED` —— 只准进"需补证据"批次

### 案例型（由 engineer-annotation 报入，我已独立复核）

callee 的 decomp 是**桩**（`return 0;`）而真实实现不在该地址——
即"地址真实存在、vtable 槽也确认了它，但它不提供任何有意义的返回值"。

### 规则（t5 输出须固化）

1. 登记为 `subclass=M_UNDETERMINED` + `evidence_grade=E` + `recommended_action=NEED_EVIDENCE`。
2. **禁止进入"可立即修"批次**（硬约束）。
3. 每条**必须**带 `proof_needed` 四项（缺一不可）：
   - ① **反汇编 0xADDR 本体**：是否读 `this->member` / `ret N` / 恒返常量；
   - ② **vtable slot 实指地址 与 同名真实现地址 的比对**；
   - ③ **名字来源**（annotation vs IDA vs PDB）；
   - ④ **caller 与 callee 的继承/归属关系**。
4. **scan 范围限定**（captain 已下发给 scanner-attribution）：仅 **ledger 197 cluster +
   343 个 `[MISATTRIBUTED]` 站点涉及的 callee** 内做同类候选普查，产出一律按本类别登记。

### 我对该案例的独立复核结果（比原报告更精确，请 t5/t13 采用）

实例：**`0x004014F0` `AStarPathFinder::GetHeuristicIdx(int nX, int nY)`**

**已实测（字节级证据）**：
```
0x004014F0  .text  32 C0 C2 08 00   →  xor al,al ; ret 8    （= return 0，thiscall 2 参）
0x004014E0  .text  33 C0 C2 08 00   →  xor eax,eax ; ret 8  （= return 0）
0x00401500  .text  8b 49 04 8b 41 3c 85 c0 ...             （FindInOpen，真实实现）
```
- decomp 记录：`address=0x004014F0`、`size_bytes=5`、`signature=virtual unsigned __int8 __thiscall(AStarPathFinder *this, int nX, int nY)`、`decompiled_c` 仅 `return 0;`。
- 生成源码 `pal3/src/Misc/AStarPathFinder.cpp` 对应体同为 `return 0;`（**一致，故"真实实现另有地址"这一提法在此地址上不成立**）。
- **vtable `0x0056A600` 的 3 个槽实测为 `0x00401030` / `0x004014E0` / `0x004014F0`**
  → `0x004014F0` **确为该类虚表的 slot 2**，槽位归属正确。
- 该类 14 个被标注方法中**只有 2 个是桩**（`0x004014E0`、`0x004014F0`，即两个虚槽），
  其余 12 个（含 `FindInOpen`/`FindInClosed`/`TryExpand`/`UpdateNeighbors`/`Reset`…）**都有真实实现**。
- caller 侧（captain 所述，我已复核 `pal3/src/Combat/CCBAI.cpp:246/444/646`）：
  `AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, nRoleIndex, (int)&this->m_nHandleEnemyWell)`
  其中 `this` 是 **CCBAI**，返回值被当 **bool** 使用。

**由此得出的四条结论（供 t5/t13 判据）**：
1. **归因已由 vtable 确认正确** → 本类**不得**填 `FIX_ATTRIBUTION`（改名不是修复）。
2. `this` 是 `CCBAI` 而非 `AStarPathFinder`（调用处显式写了 `(AStarPathFinder *)this` 强转），
   而目标确为虚方法 → 属**静态形态 + `[MISATTRIBUTED]` 标记**的既有设计信号。
3. **真正的缺陷在 callee 的体是桩**（`return 0` ⇒ 调用方条件恒为 false）。
   **该缺陷位于 `pal3/src/`，不在 t6–t16 任何任务的 inScope 内**（见 §5 缺口）。
4. 因此本类的 `proof_needed` 四项中，**②（vtable slot vs 同名真实现路径比对）已有部分答案**：
   槽位正确、无"另一处同名实现"→ 剩下的取证应转向
   **"该桩是否为原二进制真实体，还是 decomp/IDB 未解析出体"**（即尺寸 5 字节 + `ret 8` 是否符合原始编译产物）。

---

## 2. ledger 无 `evidence_grade` 字段 → 缺失即视为 C，禁止 `FIX_*`

**实测**：`data/status/misattribution_ledger.json` 的 197 条**全部**只有
`callee/callee_class/method/sites/callers/files/addrs/vtable_owners/struct_owners/full_callers/bucket/rename_to`
——**`evidence_grade` 字段存在数 = 0/197**（读作 `None`）。

规则（captain 认可 engineer-annotation 的做法，t5 必须一致）：

1. t5 的**批次项必须显式写出 `evidence_grade`**（不得继承 ledger 的缺失值）。
2. 门禁按 **"grade 缺失即视为 `C`"** 执行 → **禁止 `FIX_ATTRIBUTION` / `FIX_ANNOTATION`**。
3. **不得**把"缺失 grade"当成"未评级可修"。缺失 = `C` = 不可直接修。

---

## 3. 四条既有硬约束（重复声明，t5 必须保留）

1. **M4 不进任何"改名"批次**。M4 = callee 归属正确、错在**调用方 `this` 类型**；
   合法动作仅 `FIX_ANNOTATION` / `DOCUMENT` / `NEED_EVIDENCE`，**禁止 `FIX_ATTRIBUTION`**。
   （实测 t3 产物：109 条 M4 全为 `NEED_EVIDENCE`/`KEEP_AS_SIGNAL`，当前无违规。）
2. **`evidence_grade ∈ {C,D,E}` 禁止填 `FIX_ATTRIBUTION` / `FIX_ANNOTATION`**（spec §5.1）。
3. **`binary_size` 撑大项按逐 struct 取证排批**（53 个 >3×、10 个 >50×）。
   **严禁批量改尺寸**（CLAUDE.md 禁止批量未验证修改）。
   每条须写明所需证据（指令级 `max_offset` **下界** + 分配点尺寸）与验证方式。
   **不得**把 `binary_size` 直接降到 `max_offset`（用下界冒充精确值同样违规）。
4. **§5 字段自洽**：归一化 M 码后必须重跑 `class` 计数 == `subclass` 计数之和 的校验。
   （实测 t3 产物当前**不通过**：`class==C3` 210 条，其中 7 条 subclass 为 `M_UNDETERMINED` 不含 `C3x` 码。）
   归一化方式：`subclass` 维持单一取值（`C3a`/`C3b`/`C3c`/`C3d`/`null`），
   M 码移入**新增字段 `m_code`**（`M1_callee_name` / `M4_caller_this_type` / `M_UNDETERMINED` / `null`）。

---

## 4. 冻结证据与声明范围必须分开列示（沿用 spec §6.3.1）

- `data/status/baselines/verifier_prefix_s2.json`（**修复前**快照，实测 `ok=53/198`、`errors=3090`、
  `generated_at=2026-09-15T10:09:20`）**不得删除**；它 **untracked 且未被 .gitignore 忽略**，
  会被 `git reset --hard` / `git clean -fd` 清除 → t12 须显式纳入版本控制，
  并在"应删除"批次登记为**保护条目**。
- 清理总账至少分两个独立区段：**「冻结/基线类」** 与 **「修复类」**，**不得合并为一个数字**。

---

## 5. 本轮 DAG 的 inScope 缺口（t5 须登记，不得静默吞掉）

实测各任务 inScope：
```
t6  data/annotations/, docs/knowledge/            t13 pipeline/gen/ast_transform.py
t7  pipeline/ida/apply_annotations.py             t14 pipeline/ida/export_full.py
t8  data/status/baselines/, tools/*, pipeline/cli.py, pipeline/gen/codegen.py, docs/decompilation_workflow.md
t12 data/status/, docs/knowledge/, data/annotations/CHANGE_LOG.md
t15 pipeline/gen/stages/stage3_cleanup.py         t16 pipeline/gen/stages/emit_headers.py, pipeline/gen/data.py
```
**`pal3/src/` 不在任何任务 inScope 内**。受影响的已知条目：
- `M_UNDETERMINED` 案例的真实缺陷体（`0x004014F0` 为 `return 0` 桩）落在 `pal3/src/Misc/AStarPathFinder.cpp`；
- 生成源码本身是 codegen 产物（**不入库**，`.gitignore:125`），其修改须经 codegen 层或 Phase 2 手工修正路径，
  而**该路径不属于本轮任何任务**。

→ t5 必须把此项写入产物（作为"本轮不做 + 理由 + 后续触发条件"），
并回报 captain 决定是否另立任务。

**为什么不能顺手塞给 t6**（我最初把理由写成"t6 的 outOfScope 已含 codegen 产物"，**该说法不准确，已更正**）：
实测 t6 的 `outOfScope` = `['pipeline/gen/', 'pipeline/ida/apply_annotations.py', 'tools/']`
——**并不包含 `pal3/src/`**。正确的理由是**性质与生命周期**不同：
- t6 是按 triage 的 A/B 级证据批次修正**归属与注解**（inScope `data/annotations/`）；
- `pal3/src/Misc/AStarPathFinder.cpp` 是 **codegen 生成物**（`.gitignore:125 pal3/src/` 已实测确认），
  对它手改属 **Phase 2 手工 fix 路径**，且**下次 codegen 会覆盖**。
  故它不是"注解修复"的一个条目，而需要独立的 Phase 2 任务（或在 codegen 层解决）。
- t13 只管 `pipeline/gen/ast_transform.py` 的**跨类 this 直呼策略**，改不到 callee 的函数体，
  故也不能归给 t13（t13 需要的是本条提供的**裁决输入**，见下）。

---

## 6. t5 产物的最小合格清单

- [ ] 四批次（可立即修 / 需补证据 / 应删除 / 有意保留）划分完成，每条唯一类别 + 确定 `evidence_grade`
- [ ] `m_code` 归一化完成，并重跑 §5 计数自洽校验（结果写入产物）
- [ ] `M_UNDETERMINED` 全部落在"需补证据"，每条含四项 `proof_needed`
- [ ] "可立即修"每条给出具体修改内容 + 责任任务 + 验证命令
- [ ] ledger 来源条目显式写出 grade（缺失按 `C`），无 `FIX_*`
- [ ] 53 个撑大项逐 struct 排批（禁批量），逐条写明证据与验证方式
- [ ] M4 无一进入改名批次
- [ ] 删除批次含 `verifier_prefix_s2.json` 保护条目；总账分「冻结/基线类」与「修复类」两区段
- [ ] §5 的 inScope 缺口已登记并回报
- [ ] 基线锚点 L1 ≥ 5、ok ≥ 53/198 写入产物；分母变动判不可比