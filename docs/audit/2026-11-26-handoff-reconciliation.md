# 交接对账报告：交接文档 §1 读数 vs 仓库实测

- 日期：2026-11-26
- 执行：观澜（业务）· Task #4（`tsk_01M8BX0KP709VNMFZJEH2H`）
- 对账对象：`docs/handoff/2026-11-26-struct-hole-campaign-handoff.md`（commit `e4378a1c4`）§1「一页状态」
- 方法：只读实跑（`cli.py status` / `cli.py check`）+ 现存产物读数（空洞普查、probe census、match 日志、基线文件）；写盘项（`census_struct_holes`、`loop`）不重跑
- 边界：本卡只写 `docs/audit/` 与 `README.md`；未改任何 annotation / 基线 / 生成树（见 §7）

## 0. 结论摘要

1. 六行状态表中，**三行终点值完全吻合**：空洞目标面（201 类/1142 洞/1246KB）、CCBCamControl（12B）、EquipUI（15.6KB）。
2. **「编译读数」行两项都与当前实测不符**：文档「现在」记 S2 **158**/229 · L1 **189**；实测 S2 **157**/229 · L1 **188**。差异不是记录笔误，而是文档取的是 **R2 终点读数**（`cf70c0b48`），R3（`ac9c67673`）已把它回退：S2 −1 单元（`RoleStatePanel.cpp` C2440@777）、L1 −1（`RoleStatePanel::scalar deleting destructor'(uint) @0x4A2150` 30B LOST）。这正是交接文档 §5 的 R4 首查项——**本报告只做归因，不构成任何重锚依据**。
3. **RoleStatePanel「156KB 洞」单位标注错**：实测为 156,453 B = **152.8KB**（R2 后为 156,433 B），不是 156KB。
4. **语义清理「触达 7 类 38+ 非语义名」**：迁移终值 42 员可复现（台账 `tally=42`、`git diff` 中 `"name": "m_unk_` 42 条），但「38+」无产物来源，实际迁移只发生在 2 类（RoleStatePanel 40 + EquipUI 2）。
5. **「全库 538 员存量」无任何命令/产物支撑** → 列「未决」。当前可复现的在档量：伪语义名台账 61 类 323 员；注解内 todo 词 149。
6. **README「当前读数（2026-11-23）」三项全部陈旧**（S2 160/233、L1 181、check 13 警告）；本卡已按实测刷新（§4）。

## 1. 三列对账（交接文档 §1）

| 项 | 文档值（§1） | 实测值（证据见 §2） | 差异 / 判定 |
|---|---|---|---|
| 空洞目标面 | 战役前 201 类/1168 洞/1478KB；现在 **201 类/1142 洞/1246KB** | 战役前（`git show 1c0be6473`）：201/1168/1,513,593 B=**1478.1KB**；现在：201/1142/1,275,908 B=**1246.0KB** | 0 ✓ 完全吻合 |
| CCBCamControl | 348KB 洞 → **12B** | 战前（`1c0be6473`）357,092 B=**348.7KB** → 现 **12 B**（1 洞） | 0 ✓（「348KB」=348.7 取整） |
| EquipUI | 164KB 洞 → **15.6KB** | 战前 168,244 B=**164.3KB** → 现 15,960 B=**15.6KB**（7 洞） | 0 ✓ |
| RoleStatePanel | 156KB 洞 → **556B** | 战役起点 156,453 B=**152.8KB**（R2 后 156,433 B=152.8KB）→ 现 **556 B**（9 洞） | 终点 ✓；**「156KB」单位错**（差约 3.2KB，系把字节数当 KB 写） |
| 编译读数 | 战役前 S2 157/229 · L1 188；现在 **S2 158/229 · L1 189（重锚）** | **S2 157/229，总错误 633**（`probe_census.json` `generated_at=2026-11-26T19:14:46`，`cli.py status` 实读一致）；**L1 188**（`pipeline/_logs/loop_match.log` 19:29:02：`L1 rate 188/998`、`matched 1132/1238`）；L1 棘轮记录 189（`s4_baseline.json` `stats.match_L1=189`，内容为 14:17:46 的 R2 重锚态） | **S2 −1、L1 −1**。文档「现在」= R2 终点（`cf70c0b48`），R3 已回退，见 §3-A |
| 语义清理 | 触达 7 类 **38+** 非语义名 → **42 员**迁移 `m_unk_<offset>`；全库 **538 员**存量待批次 | 迁移 **42**（`data/status/r35_semantic_cleanup_20261126.json` `tally={"迁移留白形":42,"total":42}`；`git show 22417d35d` 中 `"name": "m_unk_` 命中 42 条）；迁移分布 RoleStatePanel 40 + EquipUI 2（2 类）；7 类扫描面 touch 明细 `0/28·0/0·0/53·2/23·40/55·0/2·0/1`；正名 0、退役 0；**538 无产物**（在档伪语义台账 61 类 323 员；注解 todo 词 149） | 42 ✓；**「38+」无源（疑为预估稿）**；**538 未决** |

附：README 行（不属 §1 表，但属本卡刷新范围）

| 项 | 文档值（README 2026-11-23） | 实测值 | 差异 / 判定 |
|---|---|---|---|
| README 当前读数 | S2 160/233 ok（fail 73）· L1 181 · check 13 警告 | S2 **157/229**（fail 72，总错误 633）· L1 **188** · check **0 new + 37 frozen + 109 warnings — PASS** | 三项全陈旧，见 §3-E |

## 2. 证据（命令与输出片段 / 产物时间戳）

核对时点：本卡开工 20:24 时 `ps aux | grep pipeline/cli.py` **无进程**（实跑前确认无 loop 在跑）。以下读数全部来自现有产物，未重跑写盘项。

### 2.1 空洞普查（写盘项，未重跑；引用产物）

产物：`data/status/struct_holes_20261125.json`，内容与 `ac9c67673` 提交态一致（`git diff --stat` 为空）；文件 mtime 2026-11-26 20:39:47（并发方重跑，零漂移）。

```
$ python3 -c "import json;d=json.load(open('data/status/struct_holes_20261125.json'));m=d['_meta'];print(m['classes_with_holes'],m['total_holes'],m['total_hole_bytes'])"
201 1142 1275908        # = 1246.0KB
# 分级：CCBCamControl 12 / EquipUI 15960 / RoleStatePanel 556
```

战役前值（逐提交核对，`git show <sha>:data/status/struct_holes_20261125.json`）：

| commit | 时点 | 类/洞/字节 | KB |
|---|---|---|---|
| `1c0be6473` | 01:27（R1 前） | 201 / 1168 / 1,513,593 | **1478** |
| `ed73fd85e` | 11:49（R1 后） | 201 / 1161 / 1,584,073 | 1547 |
| `cf70c0b48` | 15:04（R2 后） | 201 / 1139 / 1,431,785 | 1398 |
| `ac9c67673` | 18:40（R3 后） | 201 / 1142 / 1,275,908 | **1246** |

> 注：R1 后全库反而从 1478KB 升至 1547KB，是 CCCTData 中间态显形（`hole_bytes` 256 → 430,256）所致；文档 §1 的「战役前」取 R1 前快照，口径正确。

### 2.2 S2 编译读数（只读实跑）

```
$ python3 pipeline/cli.py status
当前普查（data/status/probe_census.json）：
  S2 157/229 · 总错误 633 · 2026-11-26T19:14:46
```

产物字段 `data/status/probe_census.json`：`s2.total=229, s2.ok=157, s2.fail_own=72`；`generated_at=2026-11-26T19:14:46`。

### 2.3 L1 / match（引用 19:29 已完成的 loop 日志）

```
$ tail -40 pipeline/_logs/loop_match.log
L1 rate over matched: 188/998 = 18.8%
[L1 ratchet] previous 189 -> current 188
[L1 ratchet] population: previous matched=1152/1259 -> current matched=1132/1238
[L1 ratchet] 丢失函数 1 个(身份差分):
[L1 ratchet]   LOST RoleStatePanel::`scalar deleting destructor'(uint) @4858192 size=30
[L1 ratchet] REGRESSION: byte-perfect functions lost — investigate before committing
```

`data/status/_loop_last.json`：`match: {rc:1, matched:1132, symbols:1238, L1:188, L1_prev:189, L1_cur:188}`。
棘轮基线（`s4_baseline.json`）：`stats.match_L1=189`、`matched=1152/symbols=1259`；`rebaseline` 记录 = `2026-11-26T14:17:46`「R2 诚实增益重锚 … L1 188→189」。

### 2.4 秒级门禁（只读实跑）

```
$ python3 pipeline/cli.py check
...
0 new errors + 37 frozen(advisory), 109 warnings — PASS
```
退出码 0。警告构成（`grep '^WARN'` 分类计数）：`name_drift 91 + functions 11 + N20a 4 + N22 1 + N20b 1 + N15 1 = 109`。

### 2.5 语义清理（引用台账 + 提交 diff）

```
$ git show 22417d35d -- data/annotations | grep -c '"name": "m_unk_'
42
$ python3 -c "...r35_semantic_cleanup_20261126.json..."
tally: {"正名":0,"退役":0,"迁移留白形":42,"total":42}
scan: CCBCamControl 0/28 · CCCTData 0/0 · SkillUI 0/53 · EquipUI 2/23 · RoleStatePanel 40/55 · UIFrameContainer 0/2 · UIListBox 0/1
```

### 2.6 读数产物时间戳表

| 产物 | 生成时间 | 用途 |
|---|---|---|
| `data/status/struct_holes_20261125.json` | mtime 20:39:47（内容=18:40 提交态） | 空洞目标面/三大锚 |
| `data/status/probe_census.json` | 19:14:46 | S2 157/229 · 633 |
| `data/status/baselines/latest.json` | 19:16:35 | probe 对账基线（900/995 文件集） |
| `pipeline/_logs/loop_match.log` | 19:29:02 | L1 188、LOST 1 |
| `data/status/s4_baseline.json` | 内容时点 14:17:46（文件 mtime 20:33:55 由并发 match 运行回写「保持上一轮」） | L1 棘轮 189 |
| `data/status/check_baseline_errors.json` | 19:30:52 | 冻结基线（52 条，当前命中 37） |

## 3. 差异逐条归因

### A. S2 158→157、L1 189→188：R3 提交 `ac9c67673`（18:40）

- S2：`RoleStatePanel.cpp` 由 ok→fail，唯一新错误 `L777: C2440 '=' : cannot convert from 'char [8]' to 'unsigned long *'`；总错误 632→633。归因链：R3 Task2 把 0x25b78 键入 `m_bRtVisible unsigned char[8]`，`OnMessage` 中 hexrays 建了 dword 指针局部（L745），L777 `m_bRtVisible = this->m_bRtVisible;` 无 cast → C2440。证据：`.superpowers/sdd/2026-11-26-r3-implementation-plan/task-4-report.md` §3/§5/§6（逐单元 diff，仅此 1 单元实质变化）。
- L1：同轮 `s_RoleState.cpp` 单元重渲后组内内联决策变化，`RoleStatePanel::`scalar deleting destructor'(uint) @0x4A2150`（30B）丢失；match 日志逐条列出（§2.3），regressed detail 存档 `data/status/archive/s4_diff_detail_regressed_20261126T192902.json`。交接文档 §5 已把它列为 R4 首查阻塞项。
- 结论：**已归因 = R3 的真回归（文档 §5 自记「拒绝重锚是正确状态」）**。本报告不重锚、不写基线；R4 首查由玄策在办（并发产物 `data/status/match_red_attribution_20261126.md`、`docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md`，均未提交）。

### B. RoleStatePanel「156KB」：单位标注错

156,453 B / 1024 = 152.8KB。文档把字节数直接写成 KB（156KB），与同表其他行（348KB/164KB 系正确 KB 换算）口径不一致。建议改注为「152.8KB（156,453 B）」。

### C. 语义清理「38+」：预估稿残留

实际扫描 touch 合计 = 42，迁移 = 42；「38+」在台账/提交说明/产物中均无对应统计口径，判为写作前的预估数字未回填。不影响终点值 42。

### D. 「全库 538 员」：未决

`grep -rn "538"` 在交接文档外无产物命中；各类在档量（伪语义台账 61 类 323 员、todo 词 149、迁移前 7 类非语义 162）组合均不等于 538。无命令可复现 → 列未决（§6-1）。

### E. README 三项陈旧：分层归因

- 快照时点：README 段标题即「2026-11-23」，其后 11-24/25 的类型注册表/域排除/模板别名大改（`427af3232`、`807f74cea`、`089ac3dd5` 等）与 11-26 战役均未回填。
- S2 160/233 →157/229：总单元 233→229 的四个单元去向**无单点产物记录**（`probe_census` 只记当前 229；229 = 当前 `pal3/src/**/*.cpp` 文件数，实测 `find pal3/src -name '*.cpp' | wc -l` = 229）→ 归因未决；ok 160→157 部分由 R3 回退（−1）与其后各自收敛构成。
- L1 181→188：期间经历多次显式重锚与该轮 +30B 配对（14:17:46 R2 重锚链），README 未跟随。
- check 13→109：聚合器把 `name_drift`（91 条）等族计入总数（`pipeline/check_annotations.py:2536-2552`），旧「13 警告」的度量口径无产物留存 → 部分归因，逐族去向未决（§6-3）。

### F. 附：R1 提交说明 337,092 vs 普查 357,092

不在 §1 表，但同类「文字 vs 产物」矛盾，已由 `docs/knowledge/struct_hole_fill_campaign_20261126.md` §6-1 记录（337,092 = 357,092 − 20,000，疑把 `m_TaskListIndex` 段算作已填）。本报告复核一致，不重复展开。

## 4. README「当前读数」刷新

原文（2026-11-23）：

```
## 当前读数（2026-11-23）

- S2 编译单元 160/233 ok（fail 73）· L1 字节匹配 181 · check 13 警告（起点 210）
```

刷新为（2026-11-26 实测，注明日期与口径）：

```
## 当前读数（2026-11-26）

- S2 编译单元 **157/229** ok（fail 72，总错误 633）· L1 字节匹配 **188**（棘轮记录 189 未重锚，match 红=R4 首查项）· check **0 new + 37 frozen + 109 warnings — PASS**
- 结构体空洞：201 类 / 1142 洞 / 1,275,908 B（1246KB），产物 `data/status/struct_holes_20261125.json`
- 读数来源与历史差异归因见 [交接对账报告](docs/audit/2026-11-26-handoff-reconciliation.md)（2026-11-26）
```

## 5. 交接文档「修正注」（建议内容；本卡 writeScope 不含 `docs/handoff/`，未写入原文件）

按任务要求「被证伪的数字以修正注标注，不改历史记录」，以下为逐行修正注，待授权后由有写权限的一方落地（或由本卡改派扩权）：

| 原文行 | 原文片段 | 建议修正注 |
|---|---|---|
| L16 | `RoleStatePanel \| 156KB 洞 \| 556B` | 〔修正注 2026-11-26：单位应为 152.8KB（156,453 B）；556B 终点值实测无误〕 |
| L17 | `S2 **158**/229 · L1 **189**（重锚）` | 〔修正注 2026-11-26：158/189 是 R2 终点（`cf70c0b48`）；R3（`ac9c67673`）回退为 S2 157/229（总错误 633）、L1 188（LOST `RoleStatePanel` deleting dtor@0x4A2150 30B），即 §5 R4 首查项；未重锚〕 |
| L18 | `触达 7 类 38+ 非语义名` | 〔修正注 2026-11-26：扫描面 7 类，实际迁移 2 类 42 员；「38+」无产物来源〕 |
| L18/L77 | `全库 538 员存量待批次` | 〔修正注 2026-11-26：538 无产物可复现（未决）；在档可复现量=伪语义台账 61 类 323 员、注解 todo 词 149〕 |

## 6. 未决清单（交回）

1. 「全库 538 员」无产物/命令可复现（§3-D）。
2. README 233→229 的四个 S2 单元去向无记录（§3-E）。
3. check 警告 13→109 的逐族口径变化无单点记录（构成已列：name_drift 91 等）。
4. §2「伪语义名台账 58 类 296 员（20261118 在档）」与现文件 **61 类 323 员**不一致（+3 类/+27 员；progress 提到 R6 补登 22 名，余 5 员未逐条核对）。
5. 「38+」原始统计来源（§3-C）。
6. 20:52:54 有并发方给 `RoleStatePanel.json`/`UIFrameContainer.json` 各加 `"base_size": 72`（各 +1 行）；本卡读数取自其前的 19:06–19:29 产物，基于 20:52 后重跑 loop 的读数可能不同。

## 7. 约束遵守（可核）

- 开工前确认无管线在跑：`ps aux | grep -E "pipeline/cli.py..."` → 无匹配（exit 1）。
- 实跑仅两条只读命令：`python3 pipeline/cli.py status`（rc=0）、`python3 pipeline/cli.py check`（rc=0）。未跑 `loop`/`apply`/`export`/`codegen`/`census_struct_holes` 写盘项。
- 未改 annotation / 基线 / 生成树：本卡写入仅 `docs/audit/2026-11-26-handoff-reconciliation.md` 与 `README.md`；`find pal3/src -newermt "2026-11-26 20:24" -type f` → 0 个文件。
- 并发方改动（非本卡）：20:30–20:33 R4 取证产物（`data/status/archive/s4_lost_0x4a2150_repro_20261126.*`、`s4_diff_detail_regressed_20261126T203355.json`、`match_red_attribution*`）、20:39 空洞普查重跑（内容零漂移）、20:52 两处 struct 注解加 `base_size`。收尾时（20:57 后）`git status` 另见并发方新增：`M data/status/evidence_ledger.json`、`?? tests/test_base_size_projection.py`、`?? pipeline/_logs/apply_export_basefix_20261126.log`、`?? data/status/lvar_feasibility_20261126.md`、`?? docs/specs/2026-11-26-pipeline-architecture-audit.md`、`?? docs/handoff/r5-20261126/`。这些均未计入本报告实测值，但会改变后续重跑读数；本卡写入仅 `README.md`（+4/−2 行）与本文件。
