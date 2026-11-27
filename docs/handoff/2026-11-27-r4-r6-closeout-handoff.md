# R4/R6 收口交接（上篇）

> 取数时间：2026-11-27 05:02（Asia/Shanghai）。HEAD `aa894e694`，`master...origin/master`（无 ahead）。
> 本文件是 **上篇**：只写 R6 六项、提交状态与下一步卡；R4 读数留占位，由 #46 在 #45/#50 收口后补“下篇”，同文件顺序写，不另建副本。
> 本版不把任何“已验收未提交”写成“已生效”，也不把 `s4_baseline` 工作树的 L1=192 当作 R4 收口结论。

## 0. 一分钟结论

1. R6 六项都已有 A/B 级取证和施工图，但**六项注解都还没有对应的已验收落地卡**；当前工作树只有 ① UITitle_JDHY、④ PropUI 等 `M`，不能按“已落地”提交。
2. 六项数字的终态与 #35 §16 一致；唯一状态漂移是 ④：工作树已是 28,892/50（#48 C2 实测），#35 终态表仍写 29,056/95 的旧注解。
3. 需要 Human 拍板的是 5 个问题（⑥身份句、③大洞、⑤删15员、②语义后置、①④是否现在提交），见 §2。不替 Human 勾选。
4. R4 边界二（#45）仍未收口：owner 已 failed，卡片仍 `in_progress`；#49 只读评估已落盘，结论是“A 一步没落、B 已齐”，接管执行在进行中。R4 读数见 §4 占位，本版不填。
5. 提交面：HEAD 之后的已验收文档/台账都还在工作树；#30 与未验收注解是 WIP，绝不能 `git add -A`。

## 1. R6 六项终态（与 #35 §16 对账）

来源：`docs/audit/2026-11-26-r6-decision-brief.md` §16、`docs/specs/2026-11-27-r6-six-plan-integration-audit.md` §2/§5；取证原文见每行“证据”。

| # | 终态数字（等级） | 证据 | 当前注解/工作树（05:02） | Human 待拍板 |
|---|---|---|---|---|
| ① UITitle_JDHY / Note_Item | **290,488**；Note_Item **3,560**；`m_NoteItem[36]@0x262C8`；`m_isItemShow[36]@0x262A4`（A） | #22 `docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md`；#35 §16 | `data/annotations/structs/UITitle_JDHY.json` **M**：290,488/43；HEAD 377,700/28；census 8B/1 | 是否现在验收并提交（#48 Q5） |
| ② C2DSpark / tagSpark | **22,640**；tagSpark **44**；512×44=0x5800，尾员 `m_Quad@0x5848`（A） | #29 `docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md`；#47 施工图 | `data/annotations/structs/C2DSpark.json` 24,688/20、`data/annotations/structs/C2DSpark_tagSpark.json` 48/12，均 clean；census 无条目 | 是否接受“先尺寸/偏移、元素语义后置”（#48 Q4） |
| ③ CCBStage | **672,040**；673,968 是另一对象（尺寸 A/归属 B）；673,988 是 +20B 幻影（B） | #27 `docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md` | `data/annotations/structs/CCBStage.json` 673,988/20，clean；census 36B/2 | 是否接受先改尺寸、留 670,520B 洞（#48 Q2） |
| ④ PropUI | **28,892**（0x70DC）；164=52+16+96（A） | #31 `docs/specs/2026-11-27-propui-size-164-evidence.md`；#47 施工图 | `data/annotations/structs/PropUI.json` **M**：28,892/**50**（#48 C2）；HEAD 29,056/95；#47 文本仍记 47 员，属现场漂移；census（04:31:10 版）50 员/292B/12 洞 | 是否现在验收并提交；需按 50 员重验（#48 Q5） |
| ⑤ CCBRoleState | **20,568**（A 分配/写界）；22,224 是派生+混装（B）；23 尾员分属 20,644B 类 15、零访问 4、CCBUIPanel 3、PropUI 1 | #24 `docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md` | `data/annotations/structs/CCBRoleState.json` 22,224/89，clean；census 6,483B/27 | 是否接受先删 15 员、20,644B 类留无名洞（#48 Q3） |
| ⑥ CCCTData / 类 Y | PDB `CCCTData`=**430,000** 池 union；类 Y=**402,824** UIListBox 派生；`CCBCamControl`=**430,256** | #18 `docs/specs/2026-11-26-ccctdata-recast-plan.md`；D-1 | `data/annotations/structs/CCCTData.json` 430,256/0；`data/annotations/structs/CCBCamControl.json` 430,256/28，均 clean；census 430,256B/1 | ⑥身份句：P-1（推荐）还是 P-2（#48 Q1，最高优先） |

对账说明：

- ①④ 是当前工作树 `M`，但都**没有对应落地卡验收**；#35 的“六项均未落地”在 ①④ 上已变成“已改未验收”，本表按当前状态写，不按 #35 旧句写。
- ②③⑤⑥ 的注解仍是旧值且 `git status` 干净；本表数字是证据支持的终态，不是已发生值。
- #48 的“④ 已落地”只表示**工作树被改**，不表示有验收卡；#47/#48 都明确 ④ 需按 50 员重验。
- census（04:31:10 版）`classes_with_holes=199`、`total_holes=1006`、`total_hole_bytes=785280`；#48 §2 引用的是 03:58 版 1040/801950，两版不可混用。它是派生文件，**不是已提交基线**。
- 六项都不需要改 `pipeline/gen`，但都要重新生成产物（apply→export→codegen→probe→match），因此必须独占管线窗口。

## 2. Human 一次拍板清单（5 问，不替拍板）

来自 #48 §5，逐条保留选项与影响：

| # | 问题 | 选项 | 影响 |
|---|---|---|---|
| Q1 | ⑥ 身份句：采信 PDB（`CCCTData`=430,000 池 union，402,824 类是未名 UIListBox 派生）还是维持 twin（402,824=CCCTData）？ | A=P-1（推荐，PDB 三重证据）；B=P-2（重写卡面，补类 Y 成员/方法/dtor）。注：#48 的 A/B 是选项编号，不是证据等级 | A 可开工，另开“402,824 类命名”卡；B 需推翻 PDB 或承认注解/PDB 分叉，工期显著变长 |
| Q2 | ③ 是否接受先改尺寸、留 670,520B 洞？ | A=先尺寸后成员；B=先开 B 正名+成员重建，再改尺寸 | A 一轮落地、洞变大；B 多两轮但洞可解释 |
| Q3 | ⑤ 是否接受先删 15 员、20,644B 类留无名洞？ | A=先删（洞 6,483→4,915）；B=先命名 20,644B 类再删 | A 快但丢唯一线索；B 稳但多一轮 |
| Q4 | ② 是否接受先尺寸/偏移、tagSpark 元素语义另卡？ | A=先尺寸；B=先重建元素语义再改尺寸 | A 尺寸立刻闭合但元素仍是伪语义；B 更彻底但 A 级证据只覆盖尺寸 |
| Q5 | ①④ 是否现在验收并提交？ | A=现在验收+提交；B=等各自 owner；C=继续留工作树 | A 证据齐、风险低，但提交权在 PMO，④ 需按 50 员重验 |

原 #35 的三条（⑥身份句、①③⑤④②落地顺序、R4 边界与 R6 先后）已被上表吸收；落地顺序建议见 §5。

## 3. 提交状态（git 实跑，05:02）

- HEAD：`aa894e694`（docs: archive accepted R5/R6 evidence, decision briefs and gotchas），`master...origin/master` 无 ahead。
- 工作树计数：**28 M + 2 m + 111 ??**（`git status --short`，05:04 复跑，含本文件自身）；暂存区 0。计数会漂移，执行提交前必须重跑。
- `data/status/s4_baseline.json` 是 **M**：工作树 L1=192/symbols1265/matched1154/sha256 `66c193fe…`，HEAD 版 L1=189/sha `f3aa8279…`。这是 R4 未收口状态的观察项，**不属于任何已验收提交**；不得写成“已重锚”。

### 3.1 已提交（HEAD 已有）

最近提交：

```
aa894e694 docs: archive accepted R5/R6 evidence, decision briefs and gotchas
ac3799b43 annotations(r4): split ScreenEffectRingNode from ScreenEffectMgr chimera (#19)
2a2f9b419 fix(codegen): restore base_size projection and array-decay pointer classification (#6/#8)
9f4436c2b annotations(SaleUI): 按 #22 独立复核补 3 员，洞 44,560B→0B（58 成员）
5b15fc482 docs(r5-saleui): 六池第二路径复核（IDA 文本清单 ??_L/??_M 双证，可 grep 复跑）+ 0x10564 索引语义与 0x3E08 数组基址两条旁证
```

### 3.2 已验收未提交（可进入 PMO 提交分组）

以 #44 `docs/audit/2026-11-27-commit-inventory.md` §3 的 5 组为基线；#44 之后又新增 #47/#48 两份已验收文档，按同组追加：

| 组 | 代表文件（当前状态） | 卡/验收 |
|---|---|---|
| G1 R6 决策/施工/缺口 | `docs/audit/2026-11-26-r6-decision-brief.md`（M）、`docs/specs/2026-11-27-r6-annotation-landing-plan.md`（??，#37）、`docs/specs/2026-11-27-r6-2-4-annotation-landing-plan.md`（??，#47）、`docs/specs/2026-11-27-r6-six-plan-integration-audit.md`（??，#48）、`docs/audit/2026-11-27-r6-evidence-ledger-gap.md`（??，#38） | #35/#37/#47/#48/#38，均白砚/对影验收 |
| G2 架构债路线图 | `docs/specs/2026-11-27-architecture-debt-roadmap.md`（??） | #36，白砚 |
| G3 R4 取证/投影/fade | `data/status/base_projection_fix_20261126.md`、`data/status/match_red_attribution_20261126.md`、`data/status/match_red_attribution_qa_20261126.md`、`docs/specs/2026-11-27-r4-screenfade-landing-plan.md`（??）、`docs/specs/2026-11-27-r4-45-takeover-assessment.md`（??，#49）等 | #8/#1/#7/#39/#49（白砚验收） |
| G4 知识库 | `docs/knowledge/pattern_chimera_class_split_by_object_identity.md`（??，93行）、`docs/knowledge/MEMORY.md`（M）、`docs/knowledge/kairos/2026/11/2026-11-27.md`（M） | #33/#42 |
| G5 证据台账 | `data/status/evidence_ledger.json`（M；新增 ev_0016–ev_0021） | #40 |

`docs/audit/2026-11-27-commit-inventory.md`（#44）和 `docs/specs/2026-11-27-r4-45-takeover-assessment.md`（#49）当前都是 **??**；两张均已被验收（#49 白砚 05:01:45，rev4 done），**#44 与 #49 均已验收，勿与 WIP 混**。

### 3.3 未验收 WIP（绝不能进提交）

- **#30**：`include/gbengine/gbVisNode.h`（M）、`pipeline/gen/stages/stage5_fixup.py`（M）、`tests/test_gbvisnode_0x44.py`（??）、`tests/test_stage5_this_alias_reassign.py`（??）。
- **R4 接管**：`tests/test_r4_screenfade_sizes.py`（??）；`data/annotations/structs/PalScriptWaitObj.json`、`data/annotations/structs/UICaption.json` 截至本版仍为 HEAD 版（mtime 11-23，`git status` 空），#50 接管若后续写入，须另取快照。
- **无落地卡的工作树注解**：`data/annotations/structs/UITitle_JDHY.json`（M；290,488/43）、`data/annotations/structs/PropUI.json`（M；28,892/50）、`data/annotations/structs/UIGameFrm.json`（M）、`data/annotations/structs/SaleUI.json`（M）、`data/annotations/structs/MainPropUI.json`（M）。
- **不得提交**：以上任何文件在对应卡验收前都不能进 commit；尤其不能把 ①④ 的 `M` 当成“已落地”。#49 报告已验收，已归入 §3.2 的 G3，不在本清单。

### 3.4 无关/他人/生成物（不提交）

- 他人/来源不明：`README.md`（旧读数）、`docs/handoff/2026-11-26-struct-hole-campaign-handoff.md`（+9 行修正注）、`docs/audit/2026-11-27-round-readout-reconciliation.md`。
- 派生数据：`data/status/struct_holes_20261125.json`、`data/status/n22_pair_closure.json`、`data/status/s4_baseline.json`、`data/status/s4_diff_detail.json`、`data/status/s4_l1_identity_cur.json`、`data/status/probe_census.json`、`data/status/pal3_registry.jsonl`、`data/status/vtable_transform_failures.md`、`data/status/adjudication_queue.json`。
- 生成物/日志/子模块/备份：`pipeline/_logs/*`、`thirdparty/ghidra-mcp`、`thirdparty/pal3-redivivus`、`original/PAL3.exe.i64.bak-20261125-retire`、`data/status/archive/*`、`data/annotations/archive/*`、`.zcode/workflow-drafts/`、`memory/`、`docs/ui-inventory/`。

提交时必须逐文件 add；pre-commit 的 check 读整棵工作树，不读暂存区（#23 文档已固化），#30/未验收注解仍在树时可能被挡。

## 4. R4 读数（占位，本版不填）

> **待 #45/#50 收口后的同一轮 `S2/总错误/L1/check` 与四类 fade/Mgr 尺寸读数。本版不填数字、不写成已收口。**

当前只记录事实边界，不作结论：

- #45 仍 `in_progress`；owner（玄策）已 failed；04:52 硬截止后 A 方案没有落盘（PSWO/UICaption mtime 仍 11-23）。
- #49 只读评估报告 `docs/specs/2026-11-27-r4-45-takeover-assessment.md`（180 行）结论：A 一步没落；B 已齐（五类尺寸 28/24/24/24/152、PSWO 非多态病灶、红测试 3 failed/2 passed、patch45 dry-run 安全）；推荐关闭 #45 按 B 收口 + 新开只写 PSWO/UICaption 的 A 落地卡，不重派。
- #50 接管执行在进行中；它完成后由 #46 在本节补同一轮读数。
- `data/status/s4_baseline.json` 工作树 M、L1=192，HEAD 版 L1=189；**不得把 192 当 R4 收口结果，也不得据此重锚**。
- R4 两处边界：#30（gbVisNode +0x44 / C2039）与 #34（四个 fade 各多 4B）仍未收口，R6 六项不受它们阻塞，但 R4 最终收口前必须消掉。

## 5. 下一步卡（≤5，含依赖）

| # | 卡 | writeScopes | 依赖/验收 |
|---|---|---|---|
| K1 | #46 下篇：R4 同一轮读数与四态 | 本文件（仅补 §4 与提交状态） | blockedBy #45/#50；验收：S2/总错误/L1/check 同一轮，baseline 未重锚或已明确恢复 |
| K2 | R6①④ 验收与提交 | 无代码（PMO 提交权） | Human Q5；① 290,488/43、④ 28,892/50 按 #48 重验；只提交已验收项 |
| K3 | R6③ CCBStage 落地（含 B 正名） | `data/annotations/structs/CCBStage.json` + `tests/test_r6_ccbstage_size.py`（待建） | Human Q2；672,040/18 员，670,520B 洞记录在案 |
| K4 | R6⑥ P-1 重铸 | `data/annotations/structs/CCCTData.json`、`data/annotations/structs/CCBCamControl.json`、`data/annotations/functions.json`（仅15条 owner）、`tests/test_r6_ccctdata_pool.py`（待建） | Human Q1；430,000/3 员、430,256/26 员含 m_CCT；洞归零 |
| K5 | 架构债 B2：注解直读 38→0 + lint | 按 #36 B2 的 8 个 gen 文件 + `pipeline/gen/test_annotation_read_single_point.py`（待建） | 无 R6 依赖；R6 主链收口后开，避免与管线通道争用 |

未进前五但已排队的：R6②（#48 批2）、R6⑤（#48 批3）、R6 收口后的 402,824 类命名卡、R4 #30/#34 边界卡。顺序与写域以 #48 §4 为准；②③⑤不要合成一张大卡（读数无法归因）。

## 6. 边界与使用说明

- 本文件是上篇；R4 节是占位，**不得把本版当最终交接**。下篇由 #46 在同一文件顺序追加。
- 所有数字标“终态/证据支持”不等于已落地；①④ 是工作树改动、②③⑤⑥ 是旧注解。
- 未验收 WIP 不得进提交；`s4_baseline` 192 不重锚。
- 本卡只新增本文件；未跑 apply/export/codegen/probe/match/loop，未改代码/注解/数据/基线，未 commit。
