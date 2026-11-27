# R4/R6 收口交接（#46 定稿）

> 取数时间：2026-11-27 11:25（Asia/Shanghai）。HEAD `74d9bdbd0`（`annotations(LineupUI): R7-T5 洞区落位`）。
> 本文件替代 #51“上篇”的占位版，作为 R4/R6 交接的现行版；同文件顺序写，不另建副本。
> **读数口径**：#45 的最终 rollback 轮是本交接采用的同轮读数（S2 162/230、总错误 576、check PASS、L1=189），由 #45 提交与验收 note 固定。本文另列 11:23/11:02 的并发产物（159/601、L1=193），只作“之后的漂移”，不得与 #45 轮混成一组。

## 0. 一分钟结论

1. **R6 六项**都已有 A/B 级证据与施工图，终态数字与 #35 §16 一致；六项注解仍未全部落地：① UITitle_JDHY、④ PropUI 是工作树 `M` 但无落地验收卡；②③⑤⑥仍是旧注解。Human 还有 5 个问题未拍板（§2）。
2. **R4 边界二（#45）已按 B 收口并验收**：A 方案实跑过但卡在门禁文件、已回退；PSWO/UICaption 仍是 HEAD 版，`tests/test_r4_screenfade_sizes.py` 仍是 3 failed / 2 passed。B 收口只交付了“尺寸值已核 + 病灶 + 红测试 + /tmp 证成”，**不等于编译尺寸已闭合**。
3. **R4 的同轮读数用 #45 最终 rollback 轮**：S2 **162/230**、总错误 **576**、`check` **PASS**、L1 **189**（baseline 已恢复 HEAD）。之后 11:23 的 probe 159/230·601 与 11:02 的 L1=193 是并发漂移，不是 #45 轮。
4. `data/status/s4_baseline.json` 工作树现在是 **M**（L1=193、symbols1277、matched1162、sha256 `993d474c…`），HEAD 是 L1=189、sha `f3aa8279…`；#45 交付时已恢复 HEAD，193 是 11:02 并发 match 写的。**本卡没有重锚，也没有恢复它**；交接按 HEAD 189 写，193 交 PMO 收口时恢复或另案。
5. 下一张真正能解锁 R4 的是 **#53**（A 落地：PSWO 三槽 + UICaption 去重 + 两台账 + tests）；它现在只剩 #50 的两个 JSON 写域未释放。R6 侧优先 ①④ 的验收/提交与 Human 五问。

## 1. R6 六项终态（与 #35 §16/#48 对账）

来源：`docs/audit/2026-11-26-r6-decision-brief.md` §16、`docs/specs/2026-11-27-r6-six-plan-integration-audit.md` §2/§5。下表“当前注解”为 11:25 `git status` + 文件实读。

| # | 终态数字（等级） | 证据 | 当前注解/工作树（11:25） | Human 待拍板 |
|---|---|---|---|---|
| ① UITitle_JDHY / Note_Item | **290,488**；Note_Item **3,560**；`m_NoteItem[36]@0x262C8`（A） | #22 `docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md` | `data/annotations/structs/UITitle_JDHY.json` **M**：290,488/43；HEAD 377,700/28 | 是否现在验收并提交（#48 Q5） |
| ② C2DSpark / tagSpark | **22,640**；tagSpark **44**；512×44=0x5800（A） | #29 `docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md` | `C2DSpark.json` 24,688/20、`C2DSpark_tagSpark.json` 48/12，均 clean；census 无条目 | 是否接受先尺寸/偏移、元素语义后置（Q4） |
| ③ CCBStage | **672,040**；673,968 是另一对象（尺寸 A/归属 B）；673,988 是 +20B 幻影（B） | #27 `docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md` | `CCBStage.json` 673,988/20，clean | 是否接受先改尺寸、留 670,520B 洞（Q2） |
| ④ PropUI | **28,892**（0x70DC）；164=52+16+96（A） | #31 `docs/specs/2026-11-27-propui-size-164-evidence.md`；#47 | `PropUI.json` **M**：28,892/**50**（#48 C2）；HEAD 29,056/95；#47 文本仍记 47，属漂移 | 是否现在验收并提交；按 50 员重验（Q5） |
| ⑤ CCBRoleState | **20,568**（A 分配/写界）；22,224 是派生+混装（B）；23 尾员：20,644B 类 15、零访问 4、CCBUIPanel 3、PropUI 1 | #24 `docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md` | `CCBRoleState.json` 22,224/89，clean | 是否接受先删 15 员、20,644B 类留无名洞（Q3） |
| ⑥ CCCTData / 类 Y | PDB `CCCTData`=**430,000** 池 union；类 Y=**402,824** UIListBox 派生；`CCBCamControl`=**430,256** | #18 `docs/specs/2026-11-26-ccctdata-recast-plan.md`；D-1 | `CCCTData.json` 430,256/0；`CCBCamControl.json` 430,256/28，均 clean | ⑥身份句：P-1（推荐）还是 P-2（Q1） |

对账说明：

- ①④ 是工作树 `M`，但没有对应落地验收卡；按“已改未验收”写，不按“已落地”写。
- ②③⑤⑥ 注解仍是旧值且干净；表中数字是证据支持的终态，不是已发生值。
- 六项都不需要改 `pipeline/gen`；但落地都要走同一管线通道（apply→export→codegen→probe→match），必须独占窗口。
- `#48` 的 A/B 是**选项编号**，不是证据等级；不要混。

## 2. Human 一次拍板清单（5 问，不替拍板）

| # | 问题 | 选项 | 影响 |
|---|---|---|---|
| Q1 | ⑥ 身份句：采信 PDB（`CCCTData`=430,000 池 union，402,824 类是未名 UIListBox 派生）还是维持 twin（402,824=CCCTData）？ | A=P-1（推荐，PDB 三重证据）；B=P-2（重写卡面，补类 Y 成员/方法/dtor） | A 可开工，另开“402,824 类命名”卡；B 需推翻 PDB 或承认注解/PDB 分叉 |
| Q2 | ③ 是否接受先改尺寸、留 670,520B 洞？ | A=先尺寸后成员；B=先开 B 正名+成员重建，再改尺寸 | A 一轮落地、洞变大；B 多两轮但洞可解释 |
| Q3 | ⑤ 是否接受先删 15 员、20,644B 类留无名洞？ | A=先删（洞 6,483→4,915）；B=先命名 20,644B 类再删 | A 快但丢唯一线索；B 稳但多一轮 |
| Q4 | ② 是否接受先尺寸/偏移、tagSpark 元素语义另卡？ | A=先尺寸；B=先重建元素语义再改尺寸 | A 尺寸立刻闭合但元素仍是伪语义；B 更彻底但 A 级证据只覆盖尺寸 |
| Q5 | ①④ 是否现在验收并提交？ | A=现在验收+提交；B=等各自 owner；C=继续留工作树 | A 证据齐、风险低，但提交权在 PMO，④ 需按 50 员重验 |

## 3. R4 边界二（#45）的最终状态

**#45 已 `done`（按 B 收口）**。B 的内容必须按字面理解：

- **A 方案没有落地**：`data/annotations/structs/PalScriptWaitObj.json`、`UICaption.json` 与 HEAD 字节一致；`git status` 对两者为空，mtime 仍是 11-23。A 实跑过一轮（PSWO 三槽 + UICaption 去重，导出尺寸 28/24/24/24/152 全中，S2 161/230、L1 198），但卡在 `C7/CLAIM_GATE/CXX_GATE` 三处 `data/status` 门禁文件、超出 #45 写域，已回退。
- **B 已交付**：五类 fade/Mgr JSON 的当前值已是 28/24/24/24/152（#49 复核），真病灶是 `PalScriptWaitObj` 非多态 POD 使派生 vfptr 后移 4；`tests/test_r4_screenfade_sizes.py` 保留，当前 **3 failed / 2 passed**（失败：PSWO 非多态、UICaption 双表、生成头尺寸 C2118）。
- 因此 **R4 边界二仍未真正闭合**：B 只是“证据与红测试齐”，编译尺寸仍是 32/28/28/28、Mgr 168，直到 #53 落地 A。

## 4. 当前读数（分项，非同一轮）

| 读数 | 值 | 来源/时点 | 口径 |
|---|---|---|---|
| S2 | **162 / 230** | #45 最终 rollback 轮，`task/submitted` 证据与 `task/accepted` note | 同轮（#45 收口） |
| 总错误 | **576** | 同上 | 同轮 |
| check | **PASS，EXIT 0** | 同上；0 ERROR | 同轮 |
| L1 | **189** | 同上；baseline 恢复 HEAD `f3aa8279…` | 同轮 |
| 观察：之后 probe | 159 / 230、601 | `probe_census.json` 11:23:00（mtime 11:24:34） | 并发漂移，非 #45 轮 |
| 观察：之后 match | 193 | `s4_diff_detail.json` 11:02:07；`s4_baseline.json` 工作树 M | 并发 match 自动写，非 #45 轮 |

**口径说明**：#45 的提交与白砚验收 note 明确要求“最近一轮用最终 rollback 组（162/230、576、check PASS、189），别混用 A 轮 161/593/198”。本文照此执行。11:23 的 probe 与 11:02 的 match 晚于 #45 收口、且中间有 R7/LineupUI 并发改动，只能说明“之后漂移”，不能并入 #45 轮。

基线异常（必须交给 PMO）：

- 工作树 `data/status/s4_baseline.json` 是 **M**：L1=193、symbols1277、matched1162、sha256 `993d474ce552845d25dc56f74d19e8f135f8391b731ff78ab439ebdc97e4da9d`。
- `rebaseline` 记录仍是 R2 的 2026-11-26T14:17:46（prev/cur L1=189），**没有 193 的重锚记录**。
- 这不是本卡改的，也不是 #45 B 的写域；#45 交付时已恢复 HEAD，193 是 11:02 的并发 match 自动写。本卡未 checkout、未重锚。建议 PMO 收口时恢复 HEAD 版（f3aa8279…），或在确认 193 为诚实增益后另案重锚；不要在交接里把它当结论。

## 5. 提交状态（11:25 实跑）

- HEAD：`74d9bdbd0`（R7-T5 LineupUI 落位）。工作树：**36 M + 168 ??**；暂存区 0。计数会漂移，执行前必须重跑。
- `data/status/s4_baseline.json`、`s4_diff_detail.json`、`probe_census.json` 都是 **M/派生**，不属于任何已验收提交。

### 5.1 已提交（HEAD 已有）

`74d9bdbd0` 及之前的 R7/R5/R6/R4 已提交部分；具体 hash 用 `git log --oneline -10` 复核。已推送范围以 `git status -sb` 为准。

### 5.2 已验收未提交（可进入 PMO 提交分组）

以 #44 `docs/audit/2026-11-27-commit-inventory.md` §3 的五组为基线，加上 #47/#48/#49/#51：

| 组 | 代表文件（当前状态） | 卡/验收 |
|---|---|---|
| G1 R6 决策/施工/缺口 | `docs/audit/2026-11-26-r6-decision-brief.md`（M）、`docs/specs/2026-11-27-r6-annotation-landing-plan.md`（??，#37）、`docs/specs/2026-11-27-r6-2-4-annotation-landing-plan.md`（??，#47）、`docs/specs/2026-11-27-r6-six-plan-integration-audit.md`（??，#48）、`docs/audit/2026-11-27-r6-evidence-ledger-gap.md`（??，#38） | #35/#37/#47/#48/#38，白砚/对影验收 |
| G2 架构债路线图 | `docs/specs/2026-11-27-architecture-debt-roadmap.md`（??） | #36，白砚 |
| G3 R4 取证/投影/fade | `data/status/base_projection_fix_20261126.md`、`data/status/match_red_attribution_20261126.md`、`data/status/match_red_attribution_qa_20261126.md`、`docs/specs/2026-11-27-r4-screenfade-landing-plan.md`（??）、`docs/specs/2026-11-27-r4-45-takeover-assessment.md`（??，#49）等 | #8/#1/#7/#39/#49，白砚/对影验收 |
| G4 知识库 | `docs/knowledge/pattern_chimera_class_split_by_object_identity.md`（??）、`docs/knowledge/MEMORY.md`（M）、`docs/knowledge/kairos/2026/11/2026-11-27.md`（M） | #33/#42 |
| G5 证据台账 | `data/status/evidence_ledger.json`（M；新增 ev_0016–ev_0021） | #40 |

`docs/audit/2026-11-27-commit-inventory.md`（#44）和 `docs/specs/2026-11-27-r4-45-takeover-assessment.md`（#49）均已验收；#51 上篇已被本文件取代，不要再单独提交旧版。

### 5.3 未验收 WIP（绝不能进提交）

- **#30**：`include/gbengine/gbVisNode.h`（M）、`pipeline/gen/stages/stage5_fixup.py`（M）、`tests/test_gbvisnode_0x44.py`（??）、`tests/test_stage5_this_alias_reassign.py`（??）。
- **#53/R4 A 落地**：`data/annotations/structs/PalScriptWaitObj.json`、`UICaption.json`、`data/status/multi_claim_ledger.json`、`data/status/dossier_pending.json`、`tests/`（PSWO/UICaption 当前与 HEAD 一致，尚未写）。
- **#54 dry-run**：`docs/specs/2026-11-27-pswo-a-dryrun.md`（??，in_progress）。
- **无落地卡的工作树注解**：`UITitle_JDHY.json`（M；290,488/43）、`PropUI.json`（M；28,892/50）、`UIGameFrm.json`（M）、`SaleUI.json`（M）、`MainPropUI.json`（M）。
- 以上任何文件在对应卡验收前都不能进 commit；①④ 的 `M` 不是“已落地”。

### 5.4 无关/他人/生成物（不提交）

- 他人/来源不明：`README.md`（旧读数）、`docs/handoff/2026-11-26-struct-hole-campaign-handoff.md`（+9 行修正注）、`docs/audit/2026-11-27-round-readout-reconciliation.md`、`docs/audit/2026-11-27-commit-inventory.md` 之外的临时清单。
- 派生数据：`struct_holes_20261125.json`、`n22_pair_closure.json`、`s4_baseline.json`、`s4_diff_detail.json`、`s4_l1_identity_cur.json`、`probe_census.json`、`pal3_registry.jsonl`、`vtable_transform_failures.md`、`adjudication_queue.json`。
- 生成物/日志/子模块/备份：`pipeline/_logs/*`、`thirdparty/*`、`original/PAL3.exe.i64.bak-*`、`data/status/archive/*`、`data/annotations/archive/*`、`.zcode/*`、`memory/*`、`docs/ui-inventory/*`。

pre-commit 的 `check` 读整棵工作树，不读暂存区；#30/未验收注解仍在树时可能被挡。必须逐文件 add，禁用 `git add -A`/`--no-verify`。

## 6. 下一步卡（≤5，含依赖）

| # | 卡 | writeScopes | 依赖/验收 |
|---|---|---|---|
| K1 | **#53** R4 A 落地（PSWO 三槽 + UICaption 去重 + 两台账 + tests） | 现有 #53 写域 | 只剩 #50 两 JSON 锁；#45 已 done，`tests/` 冲突已释放；验收见 #53 卡面 |
| K2 | **#52** PSWO 三槽归属定谳（只读） | `docs/specs/2026-11-27-pswo-slot-ownership-evidence.md` | 无；#53 落地前应先有结论 |
| K3 | **#54** A 方案 /tmp 预演（只读） | `docs/specs/2026-11-27-pswo-a-dryrun.md` | 无；给 #53 可粘贴 diff 与门禁判定 |
| K4 | R6①④ 验收与提交 | 无代码（PMO 提交权） | Human Q5；① 290,488/43、④ 28,892/50 按 #48 重验 |
| K5 | R6③/⑥ 落地 | `CCBStage.json`+`tests/test_r6_ccbstage_size.py`；`CCCTData.json`/`CCBCamControl.json`/`functions.json`+`tests/test_r6_ccctdata_pool.py` | Human Q1/Q2；②⑤待排 |

未进前五但已排队：R6②（#48 批2）、R6⑤（#48 批3）、R6 收口后的 402,824 类命名卡、R4 #30/#34 边界卡、架构债 B2。顺序与写域以 #48 §4 为准；②③⑤不要合成一张大卡。

## 7. 边界与使用说明

- 本文件是 #46 定稿；只新增/改写这一份，未改代码/注解/数据/基线，未 commit。
- §4 的同轮读数只取 #45 最终 rollback 组（162/230、576、check PASS、189）；11:23/11:02 的 159/601/193 是之后漂移，引用时必须分开，不得合并成“同轮全绿”。
- `s4_baseline` 工作树 193 是未重锚的 M，不是收口结论；HEAD 仍是 189。
- #45 按 B 收口不等于 R4 编译尺寸已闭合；#53 才是 A 落地。
- R6 六项数字是“证据支持的终态”，不是已落地值；Human 的 5 问仍未拍板。
