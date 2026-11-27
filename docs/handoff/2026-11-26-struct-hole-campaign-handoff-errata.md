# 交接文档勘误与 R4 现状刷新（errata）

- 日期：2026-11-26
- 适用对象：`docs/handoff/2026-11-26-struct-hole-campaign-handoff.md`（commit `e4378a1c4`，107 行）
- 用法：**只替代原 handoff 中已失效的段落**（§1 编译读数、§1 单位/计数、§4 PDB 路径、§5 R4 归因与入口），其余章节仍然有效；不要删除原 handoff 的历史记录。
- 时点：勘误读数取自 **2026-11-26T19:14:46（probe）与 19:29:02（match）** 两个已完成产物；写作时点（21:31）工作区有并发改动与一次运行中的 loop，另列 §2.3，不混入勘误表。

---

## 0. 一分钟结论

1. 原 handoff §1 的「S2 **158**/229 · L1 **189**（重锚）」不是当前读数：**158/189 是 R2 终点（`cf70c0b48`）**；R3（`ac9c67673`）之后实测为 **S2 157/229、L1 188**。189 是 R2 在 14:17:46 的**合法显式重锚**，不是基线错误，也不是 R4 的动作。
2. 原 handoff §5 的「s_RoleState.cpp 单元重渲组内联决策变化」是**误归因**。真实机制是 `pal3/src/Misc/RoleStatePanel.cpp:777` 的 C2440 使整个单元退出 match；`s_RoleState.cpp` 两轮都在（3 条 partial），析构体也没有被内联掉。
3. 原 handoff §4 的 PDB 路径 `data/status/probe_pdb_camera_family_20261126.json` **不存在**；正确文件是 `data/status/pdb_camera_family_20261126.json`。
4. R4 目前**未闭环**：归因已完成并验收（#1），但布局修复（#8）只是「已提交待验收、工作区未 commit」，cast 修复（#6）尚未开始；`0x4A2150` 的 30B 删除析构仍不在 L1。
5. 下一会话按 **#8 验收落地 → #6 cast → R5/R6** 推进；**验证前必须 apply→export**，否则 `asm/pal3/ida_structs.json` 是旧数据，后面所有读数无效。**未归因/未全绿不得 `--rebaseline`。**

---

## 1. 勘误表（原 handoff 位置 → 正确读数 → 证据）

> 行号指 commit `e4378a1c4` 的 107 行版本。原文摘录只摘关键片段，不改写原文。

| # | 原位置 | 原文（摘录） | 正确读数 | 证据 |
|---|---|---|---|---|
| 1 | §1 表 L17「编译读数」行 | `S2 **158**/229 · L1 **189**（重锚）` | **S2 157/229 · L1 188**（19:14:46 / 19:29:02）。158/189 是 R2 终点；R3 回退 −1 单元、−1 个 L1。 | `data/status/probe_census.json`：`generated_at=2026-11-26T19:14:46`、`s2.ok=157/229`、`fail_own=72`、总错误 633；`pipeline/_logs/loop_match.log` 19:29:02：`L1 rate over matched: 188/998`、`matched 1132/1238`；`data/status/archive/s4_diff_detail_regressed_20261126T192902.json`：`l1=188`、`partial=810`、`units=148` |
| 2 | §1 表 L17 同格「重锚」措辞 | `L1 **189**（重锚）` | 189 是 **R2 的显式重锚**（`cf70c0b48`，`rebaseline.at=2026-11-26T14:17:46`），不是 R3/R4 的动作，也不能据此说「基线写错」。R3 之后**没有**重锚，棘轮保持 189、实况 188 是**正确的红**。 | `data/status/s4_baseline.json`：`stats.match_L1=189`、`rebaseline.at=2026-11-26T14:17:46`、sha256 `f3aa8279df6d0440dd9e28b85366ad935755415b6f7cf93b8d151c78f659d372`、`git diff` 为空；`data/status/match_red_attribution_20261126.md` §④ 与 `data/status/match_red_attribution_qa_20261126.md` ② 均确认「未改未重锚」 |
| 3 | §5 L72「R4 首查」段 | `s_RoleState.cpp 单元重渲组内联决策变化` | **误归因**。真实机制：`pal3/src/Misc/RoleStatePanel.cpp:777` 的 C2440 使该单元 `status=fail`，match 只比对 S2 通过单元 ⇒ 整单元 18 行（17 条 partial + 1 条 L1 删除析构）退出可比域。`s_RoleState.cpp` 两轮都在（3 条 partial）；析构体也没有被内联（直编为完整 32B 函数）。 | `data/status/match_red_attribution_20261126.md`（逐单元差分：唯一差异单元 `RoleStatePanel.cpp`，17 条 partial；148 个共有单元中 147 个逐行相同，仅 `CCBControlWindow.cpp` 第 7 行 3 个计量字段漂移——#7 复核修正）；`data/status/match_red_attribution_qa_20261126.md`（两次独立 match 均报 LOST RoleStatePanel 的 scalar deleting destructor(uint) @4858192 size=30；only-reg 为空；s_RoleState 两轮都在）；`data/status/probe_census.json` 该单元 `line 777 C2440`；`pipeline/_logs/loop_match.log` 19:29:02 的 LOST 行 |
| 4 | §4 表 L65 | `data/status/probe_pdb_camera_family_20261126.json` | **该路径不存在（勿引用）**。正确文件：`data/status/pdb_camera_family_20261126.json`（3,220 B，2026-11-26 08:06）。 | `ls -l data/status/pdb_camera_family_20261126.json`；`test -e data/status/probe_pdb_camera_family_20261126.json` 返回不存在 |
| 5 | §1 表 L16「RoleStatePanel」行 | `156KB 洞` | 单位错：156,453 B = **152.8KiB**（R2 后 156,433 B = 152.8KiB）；终点 **556B 正确**。 | `data/status/struct_holes_20261125.json`；对账报告 `docs/audit/2026-11-26-handoff-reconciliation.md` §3-B |
| 6 | §1 表 L18「语义清理」行 | `触达 7 类 38+ 非语义名` | 扫描面 7 类，**实际迁移 42 员、只发生在 2 类**（RoleStatePanel 40 + EquipUI 2）；「38+」无产物来源。 | `data/status/r35_semantic_cleanup_20261126.json`：`tally={"迁移留白形":42,"total":42}`、`scan` 七类明细；`git show 22417d35d -- data/annotations | grep -c '"name": "m_unk_'` = 42 |
| 7 | §1 表 L18 与 §5 L77 | `全库 538 员存量待批次` | **不可复现，列未决**。在档可复现量：伪语义名台账 **61 类 323 员**、注解 todo 词 **149**；没有命令/产物能得到 538。 | 对账报告 §3-D / §6-1（`grep -rn "538"` 在交接文档外无产物命中；各类在档量组合均不等于 538） |

### 1.1 关于「对账报告」与「原 handoff 修正注」的注意

- 工作区里已有人（非本卡）给原 handoff 加了 **9 行未提交修正注**，并写了 `docs/audit/2026-11-26-handoff-reconciliation.md`（191 行，未跟踪）。本勘误表**不依赖**它们，且不改原 handoff。
- 对账报告 §3-A（L120）仍写着「`s_RoleState.cpp` 单元重渲后组内内联决策变化」，**与 #1/#7 的逐单元证据相反**，属于同一处误归因的残留；引用该报告时以本表第 3 行为准。
- 该报告 §6-6 已提示：20:52 有人给两个 struct 注解加 `base_size: 72`，其后重跑 loop 的读数会不同。这正是 §2.3 要单独交代的原因。

---

## 2. R4 当前状态（截至写作时点 2026-11-26 21:36）

> 本文件的 **R4 = 当前「match 棘轮红归因/修复」轮**（卡面口径）。战役 spec 里的 R4 是 ScreenEffectMgr 355KB 诊断（另一张卡 #4），两者不是一回事，别混。

### 2.1 卡面状态

| 卡 | 状态 | 结论/产物 | 是否落地 |
|---|---|---|---|
| #1 `tsk_01M8BW9PT0DT4XBQ7TMX01` R4 归因 | **done（对影已验收）** | 真退化；唯一消失单元 `RoleStatePanel.cpp`；机制=C2440@777 使整单元退出 match；非内联、非 churn、非基线错误；**拒绝重锚** | 报告已提交，无代码改动 |
| #2 `tsk_01M8BWFAS4FT282VX3NPP2` L-VAR 试验 | **done（对影已验收）** | 只改声明行不可行（`unsigned long*`/`unsigned char*` 仍 C2440；`char*` 退化 1+1 字节）；最小替代是赋值行 cast，但地址仍受布局缺陷影响 | 只读试验，无生产改动 |
| #7 `tsk_01M8BX9NMYAZ6W5F7VVBPV` 独立复核 #1 | **done（白砚已验收）** | 两次独立 match 读数一致；确认 L1=188、dtor 状态=单元未参与比对；确认基线未改未重锚；另发现布局 +0x2A8 缺陷 | 复核报告，无生产改动 |
| #8 `tsk_01M8BYKHXM15J0SRFP2F57` 布局修复 | **pending_acceptance（已 submit，等验收）** | 两个 struct 各补 `"base_size": 72`；**自测称** apply→export 后 bases 恢复、六项 offsetof/sizeof 对上（待验收）；自测 S2 157→160、match 曾 189→194 | **未 commit**；工作区仅两 JSON + 新测试未提交 |
| #6 `tsk_01M8BX8WS2XASCCC5Z9VXV` cast 修复 | **pending（未 claim 成功）** | 已定 B 变体：修 `pipeline/gen/stages/stage5_fixup.py` 的 `_path_is_pointer` 数组退化分类（约 4 行）+ R15 单测 | **未落地** |

### 2.2 基线事实（R4 归因时点）

- `data/status/s4_baseline.json`：`stats.match_L1=189`，sha256 `f3aa8279df6d0440dd9e28b85366ad935755415b6f7cf93b8d151c78f659d372`，与 `HEAD` 同值；`rebaseline` 记录仍是 R2 的 `2026-11-26T14:17:46`；对该文件 `git diff` 为空。**R4 没有改基线、没有重锚。**
- `pipeline/_logs/loop_match.log` 19:29:02 明确：`[L1 ratchet] previous 189 -> current 188`、`LOST ... @4858192 size=30`、`REGRESSION ... investigate before committing`。这是**应该保持的红**。

### 2.3 写作时点的额外变化（未提交，不能当成已落地）

- **#8 的验证轮**把 `probe_census` 刷新到 `2026-11-26T21:01:14`、`S2 160/229`；同一轮 match 曾报 **L1 194**，随后按 #8 卡边界 `checkout` 还原了 `s4_baseline.json`/`s4_diff_detail.json`（#8 线程 seq15 自述，当前基线仍 189）。因此：**194 不是落地读数，189 仍是仓库可见基线；160 也不是已验收读数。**
- 21:31 执行 `python3 pipeline/cli.py status` 时，`probe_census` 已被一次**正在运行的并发 loop** 改写到 `2026-11-26T21:24:21`、`S2 0/229`、总错误 4348（编译中间态）。**运行中取样不可引用**；本文件所有数字都带完成时间戳。
- 当前 `RoleStatePanel.cpp` 仍 `status=fail`、`line 777 C2440`；`data/status/s4_l1_identity_cur.json`（188 条）中没有 `0x4a2150`。⇒ **R4 尚未闭环。**

---

## 3. 下一会话入口（按顺序执行）

### 第 0 步：预检（先确认没有别人的未提交改动被覆盖）

```bash
cd /home/peng/workspace/PAL3Decomp
git rev-parse --short HEAD          # 预期 e4378a1c4（写作时点）
git status --short                  # 先看清哪些是并发改动，别 checkout/覆盖
ps aux | grep -E "pipeline/cli.py (loop|apply|export|codegen|probe|match)" | grep -v grep
python3 pipeline/cli.py check       # 秒级门禁
python3 pipeline/cli.py status      # 只读；看 S2/L1 与产物时间戳
```

**若 `git status` 里出现 `data/annotations/structs/RoleStatePanel.json`、`UIFrameContainer.json` 的 `base_size` 改动**：那是 #8 的未提交产物。先在对影/项目负责人处确认它是**被接受的修复**再继续；不要自己 `git checkout` 掉，也不要在它之上重复改。

### 第 1 步：#8 布局修复验收/落地

前置门：无并发 loop 在跑；#8 已 submit；对影验收通过。

```bash
# 验证前必须 apply→export（禁止跳过 export，否则 ida_structs 陈旧）
python3 pipeline/cli.py apply
python3 pipeline/cli.py export
python3 pipeline/cli.py codegen
python3 pipeline/cli.py probe
python3 pipeline/cli.py match

python3 tools/audit_type_layout.py --only RoleStatePanel
python3 tools/audit_type_layout.py --only UIFrameContainer
```

验收数字（与 #8 resultDefinition/线程一致）。**以下是待验证的验收判据，不是已达成事实：**

| 判据 | 期望值 | 修复前 |
|---|---|---|
| `offsetof(RoleStatePanel, m_bRtVisible)` | **0x25B78** | 0x25E20（Δ+0x2A8） |
| `offsetof(RoleStatePanel, m_unk_0x174)` | **0x174** | 0x1B8 |
| `offsetof(RoleStatePanel, m_nRtIndex)` | **0x25B80** | — |
| `offsetof(UIFrameContainer, m_bFlag96)` | **0x60** | — |
| `sizeof(UIFrameContainer)` | **152** | 220 |
| `sizeof(RoleStatePanel)` | **176256** | 177956 |
| `asm/pal3/ida_structs.json` 两类 `bases` | 非空（RoleStatePanel→UIListBox、UIFrameContainer→UIFrameWnd） | `[]` |
| S2 | **≥158/229** | 157/229 |
| L1 | **≥189** | 188（棘轮 189） |

注意：`S2 160` 与 `L1 194` 是 #8 验证轮的**未验收**读数，不能直接当验收结论；以对影独立复跑为准。

### 第 2 步：#6 cast 修复（#8 验收通过后 claim）

落点（已由 PMO 裁定 B 变体，不是注解驱动 A 方案）：

- `pipeline/gen/stages/stage5_fixup.py` 的 `_path_is_pointer`：给「数组成员无下标」的纯成员访问按数组退化判为指针（约 4 行），**带下标仍是元素值**；复用已审计的 Family 2 cast 管线。
- 补 R15 单测（基本站点 / 幂等 / 其它成员不动）。
- 不新增 annotation 面；若全链出现 L1 回退或新错误族，退回 A 方案（#6 线程 seq11 已备原型）。

验收口径：

1. `RoleStatePanel.cpp` 恢复 `ok`（无 C2440@777）；
2. `0x4A2150` 的 30B 删除析构**恢复为 L1**（不是 partial）；
3. `OnMessage` case1000 仍是两笔 dword 清零，地址回到 **+0x25B78 / +0x25B7C**；case1003 的 byte 清零不被改成 dword；
4. S2 ≥158/229、L1 ≥189、无新增错误族；
5. `s4_baseline.json` 未被重锚；
6. 与原始 `add esi,0x25B78` 的整段编码差异（我方 disp32 直接寻址 vs 原始指针基）**如实标为 Phase2**，不在 #6 强求全字节相同。

### 第 3 步：R5/R6

- 入口仍按原 handoff §5 L79-L82：R5 = MagicUI 43KB + SaleUI 43KB（+UIGameFrm 27KB）；R6 = 挂账批（UITitle_JDHY 双布局、C2DSpark、CCBStage 三数字、PropUI 差 164、CCBRoleState ctor 写界、堆类身份定谳）。
- 战役 spec 的 R4（ScreenEffectMgr 355KB）在独立卡 #4 `tsk_01M8BWGRZZZQCT9Z1BPSZG`，不要和本文件的 R4 混。
- 每轮仍按「先归因、再修复、全链复跑、最后才谈基线」的顺序；`loop --expect-*` 的基线数字必须按当轮实况刷新，不能照抄旧值。

---

## 4. 边界与红线（下一会话勿犯）

1. **未归因或未全绿，不得 `--rebaseline`。** L1 红先按 #1/#7 的方法做单元差分；能定位到具体单元就不重锚。
2. **不手改 `pal3/src` 生成物**：修复只能落在 annotation/codegen 层；`pal3/src` 是产物，会被 codegen 覆盖。
3. **验证前必须 `apply → export → codegen → probe → match`**；跳过 export 会让 `ida_structs.json` 陈旧，读数无效（CLAUDE.md 已列的强制顺序）。
4. **不把未提交工作区当已落地**：`git status` 里的 annotation/测试/日志改动，未经对影验收和项目负责人 commit，只能写「待验证」。
5. **不引用不存在的路径**：PDB 族谱用 `data/status/pdb_camera_family_20261126.json`；`probe_pdb_camera_family_20261126.json` 不存在。
6. **不在 loop 运行中取样**：`probe_census` 会被中间态覆盖（本次实测 21:24:21 出现 0/229、4348 错误的中间态）；引用读数必须带 `generated_at`。
7. **成员不 git commit/push**：由 Project owner 提交；成员只提交证据。

---

## 5. 引用索引

### 5.1 任务与报告

| 对象 | 路径/编号 | 状态 |
|---|---|---|
| 原 handoff | `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md`（`e4378a1c4`，107 行） | 已提交；工作区另有他人 9 行未提交修正注 |
| #1 归因报告 | `data/status/match_red_attribution_20261126.md`（252 行） | 未跟踪（工作区） |
| #7 独立复核 | `data/status/match_red_attribution_qa_20261126.md`（248 行） | 未跟踪（工作区） |
| #2 L-VAR 试验 | `data/status/lvar_feasibility_20261126.md`（161 行） | 未跟踪（工作区） |
| 交接对账（并发） | `docs/audit/2026-11-26-handoff-reconciliation.md`（191 行） | 未跟踪；其 §3-A 的内联归因已被本文件第 3 行纠正 |
| #8 卡 | `tsk_01M8BYKHXM15J0SRFP2F57` | pending_acceptance，未 commit |
| #6 卡 | `tsk_01M8BX8WS2XASCCC5Z9VXV` | pending，未落地 |
| #7 卡 | `tsk_01M8BX9NMYAZ6W5F7VVBPV` | done（白砚已验收） |

### 5.2 提交

| commit | 内容 |
|---|---|
| `e4378a1c4` | 原交接文档（本 errata 的勘误对象） |
| `ac9c67673` | R3：RoleStatePanel 40 员落位；引入 `m_bRtVisible unsigned char[8]@0x25b78`，导致 C2440@777 |
| `cf70c0b48` | R2：EquipUI 九数组；R2 终点 S2 158/L1 189（14:17:46 显式重锚） |
| `ed73fd85e` | R1：CCBCamControl 池区闭合 |
| `22417d35d` | R3.5：42 员迁移 `m_unk_<offset>` |

### 5.3 数据产物

| 产物 | 关键读数 |
|---|---|
| `data/status/probe_census.json` | 19:14:46：S2 157/229、总错误 633；RoleStatePanel.cpp fail、L777 C2440 |
| `pipeline/_logs/loop_match.log` | 19:29:02：L1 188/998、matched 1132/1238、LOST dtor@0x4A2150 size=30 |
| `data/status/archive/s4_diff_detail_regressed_20261126T192902.json` | l1=188、partial=810、units=148 |
| `data/status/s4_baseline.json` | match_L1=189、rebaseline=14:17:46、sha256 `f3aa8279…372` |
| `data/status/s4_l1_identity_cur.json` | 188 条，无 `0x4a2150` |
| `data/status/pdb_camera_family_20261126.json` | 3,220 B（原 handoff 的 `probe_` 路径不存在） |
| `data/status/r35_semantic_cleanup_20261126.json` | tally 迁移 42、total 42 |

---

## 6. 本文件未覆盖/维护说明

- 未修改原 handoff（其工作区 9 行修正注非本卡所写）；未改代码、annotation、数据或任何基线；本文件为唯一新增。
- #8 的六项 offsetof/sizeof 与 S2 160/L1 194 均来自其**未提交验证轮**，只能标「待验证」；本文件不把它们写成已完成。
- 若后续 #8/#6 落地并 commit，请按 §3 的验收数字复核本文件 §2 的卡面状态与 §5 的产物读数，再更新；不要直接沿用 21:31 的快照。
- R5/R6 的具体入口仍以原 handoff §5 为准；本文件只刷新被 R4 影响的段落。
