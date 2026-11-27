# R4/R6 已验收产物提交清单与提交分组草案

- 盘点时间：2026-11-27 03:10（Asia/Shanghai）
- 仓库基线：`aa894e694`，`master...origin/master`（无 ahead/behind）
- 盘点范围：`git status --short` 的 96 条工作树条目（22 M + 2 小写 m + 72 ??）
- 本文件是只读盘点，不执行 `git add/commit/push`，不改变工作树

> 说明：本文件自身会新增为第 97 条未跟踪文件；下表统计的是写文件之前的 96 条。本清单固定为 03:10 快照；03:1x 复跑已漂移到 100 条、25 files/1346+/3830-，差值是并发卡与 SaleUI 重生成。执行前必须重跑 `git status`，计数以执行时为准。

## 1. 实跑输出

```text
$ git status --short
 M README.md
 M data/annotations/structs/SaleUI.json
 M data/annotations/structs/UIGameFrm.json
 M data/annotations/structs/UITitle_JDHY.json
 ...
 m thirdparty/ghidra-mcp
 m thirdparty/pal3-redivivus
?? docs/knowledge/pattern_chimera_class_split_by_object_identity.md
?? docs/specs/2026-11-27-architecture-debt-roadmap.md
...
```

计数与暂存区：

```text
22  M
 2  m（thirdparty 子模块）
72  ??
git diff --cached --name-only | wc -l  -> 0
```

`git log --oneline -10`：

```text
aa894e694 docs: archive accepted R5/R6 evidence, decision briefs and gotchas
ac3799b43 annotations(r4): split ScreenEffectRingNode from ScreenEffectMgr chimera (#19)
2a2f9b419 fix(codegen): restore base_size projection and array-decay pointer classification (#6/#8)
9f4436c2b annotations(SaleUI): 按 #22 独立复核补 3 员，洞 44,560B→0B（58 成员）
5b15fc482 docs(r5-saleui): 六池第二路径复核（IDA 文本清单 ??_L/??_M 双证，可 grep 复跑）+ 0x10564 索引语义与 0x3E08 数组基址两条旁证
4c41bd644 docs(r5-saleui): 独立对抗复核任务书（7 条可判定问题 + 只读纪律 + 交付格式）
e5cd8a187 docs(r5-saleui): 追加语料↔布局交叉校验（54/55 名可解析、6 处越界索引判定非布局错误）与 3 条既存问题上报
b6f6b9385 docs(r5-saleui): 提交前自检表（QA checklist 逐条对照、覆盖/残留复算、证据形态分布）
7f9d6a636 annotations(SaleUI): 池证据落位（无 union 版），洞 44,560B→7,684B
e4378a1c4 docs(交接文档): 字节空洞填充战役 R1-R3.5 全程交接——状态/证据/入口/法律/验证命令
```

`git diff --stat`（仅 tracked 修改，不含未跟踪）：

```text
24 files changed, 1332 insertions(+), 2174 deletions(-)
```

其中 `pipeline/_logs/*` 与 `thirdparty/*` 是 loop/子模块痕迹，不属于本清单的提交候选。

## 2. 四类划分

### 2.1 已提交（HEAD 已有）

最近提交与主题：

| commit | 主题 | 主要产物 |
|---|---|---|
| aa894e694 | 归档已验收 R5/R6 证据、决策简报与 gotcha | 39 个文档/索引，含 R6 简报 426 行版、R5/R6 取证、knowledge #21/#23/#28、kairos 两天 |
| ac3799b43 | R4 拆 ScreenEffectRingNode | `ScreenEffectMgr.json`、`PAL3VisNode.json`、functions/vtables、#19 测试 |
| 2a2f9b419 | #6/#8 codegen 修复 | `stage5_fixup.py`、base_size 投影、数组退化测试 |
| 9f4436c2b | R5 SaleUI 落地 | `SaleUI.json` 58 员、105,912B、洞 0 |
| 5b15fc482 / 4c41bd644 / e5cd8a187 / b6f6b9385 / 7f9d6a636 | R5 池落位与复核 | SaleUI 六池、对抗复核、语料↔布局、自检 |
| e4378a1c4 | R1-R3.5 交接 | 战役纪要、交接文档 |

> 已提交文件不在下面三张表里。`git ls-files` 可确认路径已入库。

### 2.2 已验收未提交（可进入提交分组）

共 **18 个文件**，分 5 组，全部能在卡面找到验收人；文件状态与分组见 §3。

### 2.3 未验收 WIP（绝不能进提交）

**#30（pending_acceptance）**：

- `include/gbengine/gbVisNode.h`（M）
- `pipeline/gen/stages/stage5_fixup.py`（M；#30 的别名折叠改动，不能与 #6 已提交版混在一起）
- `tests/test_gbvisnode_0x44.py`（??）
- `tests/test_stage5_this_alias_reassign.py`（??）

**注解改动，尚无已验收的落地卡**：

- `data/annotations/structs/UITitle_JDHY.json`（M；HEAD 377,700/28 → 工作树 290,488/43。R6①证据已是 A 级，但落地卡未验收）
- `data/annotations/structs/UIGameFrm.json`（M；HEAD 28,268/63 → 工作树 28,268/36。R6②/T2 施工图未验收）
- `data/annotations/structs/SaleUI.json`（M；仍 105,912/58，仅把 `m_unk_0xf574` 等改成语义名。R5 后续正名，无独立验收卡）

**归属待定的未跟踪文档/报告**：

- `docs/specs/2026-11-27-r6-t2-uigamefrm-placement.md`
- `docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md`
- `data/status/r4_sefmgr_placement_report_20261126.md`
- `docs/audit/2026-11-27-402824-identity.md`
- `docs/audit/2026-11-27-ccctdata-430k-hole-census.md`
- `docs/audit/2026-11-27-equipui-expectation-baseline.md`
- `docs/audit/2026-11-27-lineupui-expectation-baseline.md`
- `docs/audit/2026-11-27-mainpropui-expectation-baseline.md`
- `docs/audit/2026-11-27-propui-expectation-baseline.md`
- `docs/audit/2026-11-27-propui-placement-exec-plan.md`
- `docs/audit/2026-11-27-r7-manifest-gen.py`
- `docs/audit/2026-11-27-r7-placement-exec-plans.md`
- `docs/audit/2026-11-27-swordui-attribution-evidence.md`

这些文件没有出现在已验收卡的 `writeScopes`/submission 里，不能按“已验收”提交。

### 2.4 无关/他人/生成物（不提交）

**他人或来源不明的 tracked 修改**：

- `README.md`（+20/−3；仍是 2026-11-26 旧读数 S2 158/229、L1 189/188，无卡归属）
- `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md`（+9 行修正注，并发方写；本任务的 errata 已单独在 G3）
- `docs/audit/2026-11-27-round-readout-reconciliation.md`（仅措辞/时点补充，aa894e 收录后再次 M，无卡归属）

**派生数据（是否随文档提交需 Human/PMO 决定）**：

- `data/status/struct_holes_20261125.json`（M；#37 已按 PMO 选项 A 确认重算，但它是派生 census，不是卡片交付物）
- `data/status/n22_pair_closure.json`（M；#19 拆类后的派生配对更新，无独立验收卡）

**纯生成物/日志/子模块/备份**：

- `data/status/adjudication_queue.json`（仅 `generated_at` 19:11→03:07，queue 空）
- `data/status/pal3_registry.jsonl`
- `data/status/vtable_transform_failures.md`
- `pipeline/_logs/loop_apply.log`
- `pipeline/_logs/loop_codegen.log`
- `pipeline/_logs/loop_export.log`
- `pipeline/_logs/loop_match.log`
- `pipeline/_logs/loop_probe.log`
- `thirdparty/ghidra-mcp`（子模块指针）
- `thirdparty/pal3-redivivus`（子模块指针）
- `original/PAL3.exe.i64.bak-20261125-retire`
- `data/annotations/archive/gbBinkVideo_retired_20261125.json`
- `data/status/archive/*` 下的 loop/check/match 日志与 census/s4 快照（含 `r4_*`、`r5_*`、`r6_t1_*`、`r6_t2_*`、`s4_*`、`probe_census_after_*`、`struct_holes_after_*`）
- `pipeline/_logs/apply_export_basefix_20261126.log`
- `pipeline/_logs/codegen_basefix_20261126.log`
- `pipeline/_logs/match_basefix_20261126.log`

**工作区/草稿/未知目录**：

- `.zcode/workflow-drafts/`
- `memory/`
- `docs/ui-inventory/`

## 3. 建议提交分组（5 组，18 个文件）

### G1 — R6 决策与施工/缺口文档

| 项 | 内容 |
|---|---|
| 主题 | R6 决策简报收口 + ④/⑥ 施工图 + 台账缺口 |
| 文件 | `docs/audit/2026-11-26-r6-decision-brief.md`（M，589 行，sha256 `f083a566…`）<br>`docs/specs/2026-11-27-r6-annotation-landing-plan.md`（??，366 行）<br>`docs/specs/2026-11-27-propui-size-164-evidence.md`（??，333 行）<br>`docs/audit/2026-11-27-r6-evidence-ledger-gap.md`（??，255 行） |
| 依据 | #35（对影）、#37（白砚）、#31（白砚）、#38（对影），均已 done |
| 必须排除 | 三个注解 JSON、`struct_holes`、`docs/specs/2026-11-27-r6-t2-uigamefrm-placement.md`、`docs/audit/2026-11-27-propui-placement-exec-plan.md` |
| 风险 | 简报 §14–§16 引用了工作树注解读数；提交后若注解被改写，文档需附一句时点说明（当前已在文首写） |

建议 commit message：

```text
docs(r6): 收口决策简报并归档④⑥施工图与台账缺口 (#31/#35/#37/#38)

Evidence: #22 A级 push0x46EB8→new0x4A46C4→ctor0x4A46DE；#24 B级 ctor0x456ab0 写界0x5058；#27 A级 push0xa4128；#29 A级 push0x5870；#31 A级 push0x70DC；#38 六项 query 缺口
Confidence: 90
```

### G2 — 管线架构债路线图与可执行性复核

| 项 | 内容 |
|---|---|
| 主题 | 14 条架构债拆成 B1–B6，并复核批次 1 |
| 文件 | `docs/specs/2026-11-27-architecture-debt-roadmap.md`（??，230 行）<br>`docs/specs/2026-11-27-architecture-debt-batch1-check.md`（??，273 行） |
| 依据 | #36（对影）、#41（白砚），均已 done |
| 必须排除 | `pipeline/gen/stages/stage5_fixup.py`、`tests/test_*`、所有注解 |
| 风险 | 路线图计数（tests 158/177、collect 1794）会随 #30 变化；#41 已记录当时的漂移，提交时不要当成永久值 |

建议 commit message：

```text
docs(arch): 管线架构债执行路线图与批次1复核 (#36/#41)

Evidence: #5 审计381行 D1-D14；#41 26个引用文件/20个行号锚点复核
Confidence: 85
```

### G3 — R4 取证、投影与 fade 边界

| 项 | 内容 |
|---|---|
| 主题 | R4 洞填充/基类投影/数组退化/fade 边界证据 |
| 文件 | `data/status/screeneffect_diag_20261126.md`（??，218 行）<br>`data/status/base_projection_fix_20261126.md`（??）<br>`data/status/lvar_feasibility_20261126.md`（??）<br>`data/status/match_red_attribution_20261126.md`（??）<br>`data/status/match_red_attribution_qa_20261126.md`（??）<br>`docs/handoff/2026-11-26-struct-hole-campaign-handoff-errata.md`（??）<br>`docs/specs/2026-11-27-screenfade-size-4b-evidence.md`（??）<br>`docs/specs/2026-11-27-r4-screenfade-landing-plan.md`（??） |
| 依据 | #4（白砚）、#13（对影）、#8（对影）、#2（对影）、#1（对影）、#7（白砚）、#9（对影）、#34（白砚）、#39（白砚） |
| 必须排除 | `data/status/r4_sefmgr_placement_report_20261126.md`、`docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md`、`data/status/archive/r4_*` 日志/脚本（均归属待定或生成物） |
| 风险 | 文档引用了 #8/#6 的未提交自测读数；提交时只声明“文档记录”，不声明代码已落地 |

建议 commit message：

```text
docs(r4): 归档R4洞填充/基类投影/数组退化/fade边界证据 (#1/#2/#4/#7/#8/#9/#34/#39)

Evidence: #8 base_size=72 六项 offsetof 判据；#2 L-VAR 六组矩阵；#1 L1 188 vs 189 逐单元差分；#34/#39 fade 各减4B
Confidence: 90
```

### G4 — 知识库 pattern 与索引

| 项 | 内容 |
|---|---|
| 主题 | chimera 拆类模式入库，并同步 MEMORY/kairos |
| 文件 | `docs/knowledge/pattern_chimera_class_split_by_object_identity.md`（??，93 行）<br>`docs/knowledge/MEMORY.md`（M，+6 行参考索引）<br>`docs/knowledge/kairos/2026/11/2026-11-27.md`（M，+6 条事件） |
| 依据 | #33（对影）、#42（对影），均已 done |
| 必须排除 | `docs/knowledge/` 下其他未跟踪文件（无） |
| 风险 | MEMORY/kairos 的 diff 各 7 行，其中 1 行是 #33 的前序索引；#42 只对 6 行新事件负责，提交说明不要写成全部本卡 |

建议 commit message：

```text
docs(knowledge): 固化chimera拆类模式并同步索引 (#33/#42)

Evidence: #33 ScreenEffectMgr 363,968→RingNode363,968/Mgr152/ScreenEffect24；#19 拆类测试7 passed；#42 6条索引
Confidence: 90
```

### G5 — 证据台账补登记

| 项 | 内容 |
|---|---|
| 主题 | R6 六项结论的 ev 条目补登记 |
| 文件 | `data/status/evidence_ledger.json`（M，15→21 条） |
| 依据 | #40（对影），已 done；#38 缺口清单 |
| 必须排除 | 不能只 stage JSON 的一部分；若前 15 条里仍有未验收条目，整文件暂缓 |
| 风险 | `git diff` 295 insertions 中只有 6 条（ev_0016–ev_0021）属 #40；其余 13 条是 #40 之前既有未提交。提交前必须确认前 15 条来源，否则不要提交整个 JSON |

建议 commit message：

```text
data(status): 补登记R6六项证据台账 (#40)

Evidence: ev_0016 ⑥CCCTData A；ev_0017 ③672,040 A；ev_0018 ③673,968 归属B；ev_0019 ⑤20,568/22,224 B；ev_0020 ②22,640/44 A；ev_0021 ④28,892 A；add前query 0命中、add后各1命中
Confidence: 90
```

## 4. pre-commit 风险

`pipeline/hooks/pre-commit:12` 只做一件事：

```bash
PYTHONUTF8=1 exec python pipeline/cli.py check
```

`pipeline/check_annotations.py` 读的是整棵工作树（`load_annotations(struct_dir=None)`，`:94`/`:237`），最后与 `data/status/check_baseline_errors.json` 比新增错误（`:2540-2549`），**不读 git index**。

因此：

- 只 stage 本组文件，不能消除 #30 或注解 WIP 产生的 check 错误；
- #30 未验收时，`stage5_fixup.py`/`gbVisNode.h` 仍在树里，check 可能 FAIL；
- UITitle/UIGameFrm/SaleUI 三个注解也是未验收改动，同样可能触发 check 或 N13 告警；
- 不要用 `--no-verify` 绕过；也不要把未验收文件一起 stage 来“凑绿”。

**建议**：先等 #30 收口（或由 PMO 明确把它移出工作树），再提交 G1–G5。若 Human 要求立即提交，只能在完整工作树上先跑一次 `python pipeline/cli.py check`，确认 PASS 后逐组提交；FAIL 就停，不提交。

## 5. 不可提交 / 需 Human 决定

| 项 | 为什么不能直接提交 | 需要谁决定 |
|---|---|---|
| #30 的 4 个文件 | pending_acceptance，未验收 | #30 owner + PMO |
| UITitle_JDHY.json / UIGameFrm.json | R6 注解落位无验收卡；尺寸/成员改变 | PMO 决定开落地卡或回退 |
| SaleUI.json | R5 语义正名，无独立验收卡 | PMO/R5 owner |
| `struct_holes_20261125.json` | #37 已确认重算，但属派生 census | Human/PMO 决定是否随文档提交 |
| `n22_pair_closure.json` | #19 派生更新，无独立卡 | PMO |
| README.md | 仍是旧读数，无卡归属 | 文档 owner |
| 原 handoff | 并发方 +9 行修正注 | handoff owner |
| round-readout | 已被 aa894e 收录后再次改，无卡 | 文档 owner |
| 13 个未归属文档/报告 | 无验收卡/无 writeScope | PMO 分配或留在工作区 |
| archive/loop 日志、子模块、备份、`memory/`、`.zcode/`、`docs/ui-inventory/` | 生成物/草稿/本地状态 | 不提交 |

## 6. PMO 执行顺序（≤5 步）

1. **冻结现场**：确认没有 `pipeline/cli.py loop` 在跑；执行 `git status --short` 与 `git diff --cached --name-only`，核对本清单的 18 个 G1–G5 文件仍在、未被改写。
2. **处理 #30**：让 #30 走完验收并单独提交，或由 PMO 明确把它移出工作树；在此前不要把 `stage5_fixup.py`、`gbVisNode.h`、两个 #30 测试加入任何提交。
3. **跑干净窗口 check**：`python pipeline/cli.py check`；只有 PASS 才继续。FAIL 且错误来自 #30/注解 WIP 时停止，不用 `--no-verify`。
4. **逐组提交**：按 G2 → G1 → G3 → G4 → G5 顺序，用显式路径 `git add <本组文件>`，每组提交后 `git show --stat` 核对只含本组；G5 提交前先确认台账前 15 条来源。
5. **推送与复核**：每组 push 后跑 `git status --short`，确认 #30、三个注解、生成物仍在工作树且未被带入；把未归属文档留给 PMO 分配，不擅自删除。

## 7. 引用

- 工作树：`git status --short`、`git log --oneline -10`、`git diff --stat`（2026-11-27 03:10）
- 提交门禁：`pipeline/hooks/pre-commit:12`、`pipeline/hooks/commit-msg:1-50`
- 检查实现：`pipeline/check_annotations.py:94`、`:237`、`:2540-2549`
- 卡面：`#30`、`#33`、`#34`、`#35`、`#36`、`#37`、`#38`、`#39`、`#40`、`#41`、`#42`
- 台账：`data/status/evidence_ledger.json`（15→21，ev_0016–ev_0021）
