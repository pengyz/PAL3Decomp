# R6 落地施工图：① UITitle_JDHY 290,488 / ③ CCBStage 672,040 / ⑤ CCBRoleState 20,568

日期：2026-11-27　卡：#37（tsk_01M8CGQWB95BQ0W4K751RJ）　性质：只读施工图（不改仓库）

三项都已有 A/B 级取证（#22 / #27 / #24），本文件只回答「改哪个 JSON 的哪个字段、删/移哪些成员、怎么验、风险在哪、先做哪件」。
**本卡未改任何注解/代码/基线**；唯一新增是本文件。另有一次误跑把**派生文件** `data/status/struct_holes_20261125.json` 重算（非注解/代码/基线），见 §9.2：含确定性证据、重算前后差异表，以及需 PMO 确认的口径变更。

---

## 0. 摘要（先看这一节）

| 项 | 真值（等级） | 当前注解 | 差距 | 本施工图动作 |
|---|---|---|---|---|
| ① UITitle_JDHY | **290,488**（A，#22） | 290,488 / 43 员 / 末端 0x46EB8 | 已一致 | **无需改成员**：工作树已由他人落地、未提交（`M`，+236/−146，mtime 00:21）；本卡只给验收与提交边界 |
| ③ CCBStage | **672,040**（A，#27） | 673,988 / 20 员 / 末端 0xA48C4 | 尺寸 +1,948；3 员越界 | 改 `binary_size`、删 3 员、加 1 员（UIRoleDialog@0xA3BD0） |
| ⑤ CCBRoleState | **20,568**（A，#24） | 22,224 / 89 员 / 末端 0x56CC | 尺寸 +1,656；23 员越界/跨类 | 改 `binary_size`、删 23 员（15 员属无名 20,644B 类，另卡） |

推荐顺序：**⑤ → ③ →（① 只验收）**。理由：⑤ 改动面最小、无新类、洞立刻 −1,568B，且不牵动任何其他类的 sizeof；③ 会留下一个 670,504B 的大洞（A 的成员表本身还没重建），适合单独一轮；① 已在工作树落地，属「验证 + 提交」而不是「再改一次」，贸然重写会覆盖他人改动。

必须 Human 拍板的点（§5）：⑤ 是否接受「先删 15 员、把 20,644B 类留成洞」；③ 是否接受「先改尺寸、成员表后置」；① 是否现在提交工作树里他人未提交的 290,488 版本。

---

## 1. ① UITitle_JDHY（290,488）

### 1.1 目标值与现状

| 量 | 值 | 来源 |
|---|---|---|
| 真尺寸 | **290,488 = 0x46EB8** | #22 报告 §2/§3（三类独立证据：`push 0x46EB8` 唯一分配、ctor 0x4B01D0 的 UIRoleDialog@0x46960+0x558 闭合、`m_NoteItem[36]×3560` 数组 ctor 参数 0x24/0xDE8） |
| 当前注解 | 290,488 | `data/annotations/structs/UITitle_JDHY.json`（mtime 2026-11-27 00:21） |
| 成员 | 43 员，首个 0x48 `rc`，末个 0x46960 `m_unk_0x46960 UIRoleDialog`（+1,368 → 0x46EB8） | 同上 |
| bases / base_size | `UIFrameWnd@0` / 72 | 同上 |
| 方法 | 23 条 | 同上 |
| census | size 290,488 / 43 员 / 洞 8B（`[0x160,0x168)`） | `data/status/struct_holes_20261125.json`（2026-11-27 02:1x 重算） |
| 依赖 | `Note_Item` = 3,560（12 员，无 bases/vtable），`m_NoteItem Note_Item[36]@0x262C8`；`m_isItemShow uchar[36]@0x262A4` | `Note_Item.json`（mtime 11-16 21:22，未变） |

### 1.2 改动表

**无成员级改动。** 工作树当前版本（`M`，`git diff --stat` = 236+/146−）已经把 377,700 的旧布局改成 290,488 / 43 员，且末端精确闭合到 0x46EB8。
本卡建议的「改动」只有流程项：

| 项 | before | after | 说明 |
|---|---|---|---|
| 文件状态 | 未提交（`M`） | 提交 | 由该改动的作者/主理人提交；本卡不重复改 |
| `Note_Item.json` | 3,560 / 12 员 | **不动** | 与真实步长 0xDE8 一致，#22 已定谳 |
| 旧值 377,700 | 存在于 HEAD | 废弃 | 3,728/99 两条旧线均无本 exe 证据（#22 §3） |

### 1.3 验收

- `python3 tools/audit_type_layout.py --only UITitle_JDHY`：`sizeof == 290488`；`offsetof(m_NoteItem) == 0x262C8`、`offsetof(m_isItemShow) == 0x262A4`、末员 `m_unk_0x46960 + sizeof(UIRoleDialog) == 0x46EB8`。
- `python3 pipeline/cli.py check`：无新增 union/overlap 硬错。
- census：洞应为 8B（`[0x160,0x168)`，即 `buf` 与 `m_unk_0x168` 之间的对齐缝），任何 ≥0x46EB8 的洞都说明成员越界。
- 全链读数（§4）：只允许「不比落地前差」。

### 1.4 风险

- **覆盖他人未提交改动**：文件当前是 `M`，本卡若「再改一次」会与在办方冲突；RE 施工卡应先确认该改动的 owner。
- **回退陷阱**：`git checkout -- data/annotations/structs/UITitle_JDHY.json` 会回到 377,700 的错误旧值，回退时必须明确「退到 290,488 的工作树版本」而不是 HEAD。

---

## 2. ③ CCBStage（672,040）

### 2.1 目标值与现状

| 量 | 值 | 来源 |
|---|---|---|
| 真尺寸 | **672,040 = 0xA4128** | #27 §2.1–§2.3：`0x5233BE push 0xa4128`（全库唯一）→ `0x5233CD call 0x55353B` → `0x5233E7 call 0x51D710` → `0x5233F9 mov [esi+0x6CC]`；ctor 0x51D710 与变体 0x51DDA0 的末子对象 `UIRoleDialog@0xA3BD0 (+0x558)`；vptr `0x5705D0` 只属 CCBStage |
| 当前注解 | 673,988 / 20 员 / 末端 `m_dwAniFlagOver@0xA48C0`+4=0xA48C4 | `data/annotations/structs/CCBStage.json`（mtime 11-25 10:34） |
| bases / base_size | `UIListBox@0` / 72 | 同上 |
| 方法 / vtable | 229 条 / 0x5705D0（7 槽） | 同上 |
| census | 673,988 / 20 员 / 洞 36B（`[0x48,0x58)`=16、`[0xA48AC,0xA48C0)`=20） | `struct_holes_20261125.json` |
| 关键反证 | 673,968 是**另一个对象**：`0x512851 push 0xA48B0` → new → `0x512874 call 0x4FB9A0`，该初始化器把 673,968B 全清零、offset 0 写描述符指针（不是 0x5705D0）；`0x4FB9A0` 的 256 槽数组在 **0xAC0 起、步长 0xA48**，即注解 `m_TaskGroups@0xA8` 的模型来自 B，不属于 A | #27 §2.4 |

### 2.2 改动表（`data/annotations/structs/CCBStage.json`）

| # | 字段/成员 | before | after | 依据 |
|---|---|---|---|---|
| 1 | `binary_size` | 673988 | **672040** | 分配立即数 + 两 ctor 写界 + vptr 三链（#27 §2.1–2.3） |
| 2 | `known_members["0xa8"]` `m_TaskGroups CCBTaskGroup[256]` | 存在（span 0xa8..0xA48A8） | **删除** | `0xA8+256×0xA48=0xA48A8 > 0xA4128`，越界 **1,920B**（`0xA48A8 − 0xA4128 = 0x780`）；该数组实测属 B（`0xAC0` 起、步长 0xA48、末槽止 0xA48A4） |
| 3 | `known_members["0xa48a8"]` `m_nTodo_A48A8 int` | 存在 | **删除** | ≥0xA4128，越界；其偏移恰是 B 的 `m_nTodo_A48A8`（B 内合法） |
| 4 | `known_members["0xa48c0"]` `m_dwAniFlagOver uint` | 存在 | **删除** | ≥0xA4128，且落在 B 之外（B 止于 0xA48B0） |
| 5 | `known_members["0xa3bd0"]` | 无 | **新增** `m_unk_0xA3BD0`，type `UIRoleDialog`，evidence_level B，source 记 `ctor 0x51DD33 lea ecx,[esi+0xa3bd0]; 0x51DD3E call 0x4a12f0; 0x51DD2E/0x51DD3E 两处 UIRoleDialog ctor；0xA3BD0+0x558=0xA4128` | ctor 写界与分配闭合 |
| 6 | `base_size` / `bases` / `vtables` / `methods` | 72 / UIListBox@0 / 0x5705D0 / 229 | **不动** | ctor 首调 0x43DCD0（基类），vptr 未变 |
| 7 | 其余 17 员（0x58..0xA4） | 保留 | **不动** | 它们都在 0xA8 之前、落在 A 内；但 `0x58=m_pShadow`/`0x5c=m_pEffect` 与 ctor 写入 `0x58=0x80`/`0x5c=0x200` 矛盾（#27 G3），**类型重取证另卡**，本卡不动 |

结果：成员 **20 → 18**；`max(member_end)` = `0xA3BD0+0x558 = 0xA4128` = `binary_size`，闭合。

### 2.3 预期 census

| 量 | before | after（预期） |
|---|---|---|
| size | 673,988 | 672,040 |
| members | 20 | 18 |
| 洞 | 36B（`[0x48,0x58)`16 + `[0xA48AC,0xA48C0)`20） | **670,520B** = `[0x48,0x58)` 16 + `[0xA8,0xA3BD0)` 670,504 |

> **对 #27 的一处修正**：#27 §4.3 写「重铸后 CCBStage 只剩 `[0x48,0x58)` 的 16B」——那只在「保留 0xA8 之后的成员」时成立；按本施工图删掉 `m_TaskGroups` 后，`0xA8..0xA3BD0` 变成未解析区（670,504B）。这不是新造数字，是删除该成员后的直接算术。**如果 Human 认为「670KB 洞」不可接受，就走 §5 的备选：先建 B 的正名卡与 A 的成员重建卡，再改尺寸。**

### 2.4 风险

- **大洞**：672,040 里有 670,520B 未解析；`check`/S2 不会因此报错（洞是计量不是错误），但 census 报告会显眼。
- **G3 类型疑点**：`m_pShadow/m_pEffect` 等 17 员的类型未重取证；本卡保留它们只为缩小改动面，不代表类型已证。
- **B 的成员搬迁**：删除的 3 员里，`m_TaskGroups` 与 `m_nTodo_A48A8` 是 B 的合法成员，应在 B 的正名卡里以 `0xAC0`/`0xA48A8` 重新加入；`m_dwAniFlagOver@0xA48C0` 落在 B 之外，作废。
- **census 记录的 store 槽不准**：`probe_heap_alloc_census` 记 `esi+0x6C8`，反汇编是 `0x5233F9 mov [esi+0x6CC]`；不要用 census 的 store 槽做证据。

---

## 3. ⑤ CCBRoleState（20,568）

### 3.1 目标值与现状

| 量 | 值 | 来源 |
|---|---|---|
| 真尺寸 | **20,568 = 0x5058** | #24：`0x44C5F3 push 0x5058`（唯一）→ new → `0x44C60E call 0x456AB0` → `0x44C621 [esi+0x3620]=eax`；ctor 最远写 `0x456B2A [esi+0x5054]` → 0x5058；vptr 0x56B364 |
| 当前注解 | 22,224 / 89 员 / 末端 `m_BattleFlags@0x56CC` | `CCBRoleState.json`（mtime 11-26 01:00） |
| bases / base_size | `UIListBox@0` / 72 | 同上 |
| 方法 / vtable | 213 条 / 0x56B364（7 槽） | 同上 |
| census | 22,224 / 89 员 / 洞 6,483B / 27 段；其中 ≥0x5058 的洞合计 **1,568B** | `struct_holes_20261125.json`（本卡实测重算） |

### 3.2 改动表（`data/annotations/structs/CCBRoleState.json`）

| # | 字段/成员 | before | after |
|---|---|---|---|
| 1 | `binary_size` | 22224 | **20568** |
| 2 | `known_members` 数 | 89 | **66**（删 23） |
| 3 | `base_size` / `bases` / `vtables` / `methods` | 72 / UIListBox@0 / 0x56B364 / 213 | **不动** |

**删除的 23 员**（全部 ≥0x5058，越出真尺寸；分组见 #24 §4）：

| 组 | 偏移 | 成员 | 归属（#24 结论） |
|---|---|---|---|
| A（15 员） | 0x5060..0x50A0 | `m_nCurrentTaskID`、`m_nEffCurA/B`、`m_nEffTarget1/2`、`m_nEffTransFrames`、`m_nEffSwapA/B`、`m_nEffCurC`、`m_nEffSwapC`、`m_nEffCurD`、`m_nEffTransFrames2`、`m_nEffCurE`、`m_nEffSwapE`、`m_fTimeFund` | 属**另一个 20,644B 类**（`0x51272B push 0x50A4` → `0x51274E call 0x4EC680`，该函数 `mov ecx,0x1429; rep stos` = 20,644B；方法 0x4EC830/0x4F7910/0x4F8480 访达）——本卡**只删不加**，等该类的正名卡 |
| B（4 员，幻影） | 0x55C8/0x55C9/0x55CC/0x55D0 | `m_bScrollEnableA/B`、`m_nScrollOffset`、`m_nScrollTarget` | 全库零访问（`+0x55c8/+0x55cc/+0x55d0` 0 命中）；偏移与 `CG_UI` 的 `m_nNoteMoney/m_pBuyUI` 重合 ⇒ 作废，不再加回 |
| C（3 员） | 0x5654/0x5658/0x565C | `m_nFadeFlags`、`m_nFadeAlpha`、`m_nFadeTimer` | 属 **CCBUIPanel**（22,112=0x5660；访问者 0x44A2E0 由 `CCBUIPanel::Update 0x44A1B0` 同 this 调用，max 0x565C+4=0x5660）——已在 CCBUIPanel，不需迁 |
| D（1 员） | 0x56CC | `m_BattleFlags` | 属 **PropUI**（29,056=0x7180；`0x46D2BE lea ecx,[esi+0x56CC]` 在 `PropUI::InitUI 0x46D140`）——已在 PropUI，不需迁 |

保留的 66 员中，末员为 `m_nVideoState@0x5054`（4B → 0x5058），正好闭合。

### 3.3 预期 census

| 量 | before | after（预期） |
|---|---|---|
| size | 22,224 | 20,568 |
| members | 89 | 66 |
| 洞 | 6,483B / 27 段 | **4,915B**（= 6,483 − 1,568，与 #24 的 −1,568B 一致） |

### 3.4 风险

- **删 15 员会丢信息**：它们属实的 20,644B 类目前无名字、无注解；在正名卡之前，这块语义只存在于 #24 报告里。缓解：本卡在 `source` 里留一行「原 CCBRoleState 0x5060..0x50A0 15 员，实属 XX 类（见 docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md）」——但 `source` 不能挂到被删成员上，所以改为在该类的 `note` 字段留指针（不新增成员）。
- **`m_BattleFlags` 删了会不会断引用**：全仓 grep `m_BattleFlags` 需为 0（落地卡前置检查）；若 codegen 侧有引用，先跑一次 codegen 观察。
- **没有任何数组/内嵌依赖**：三项的所有外部引用都是指针（`CCBSystem+0x10`、`CCBAI+0x10`、`CCBEditor+0x4` 等），sizeof 变化不移动其他类。

---

## 4. 验收（三项共用，按阶段分别执行）

### 4.1 秒级闸

```bash
python3 pipeline/cli.py check          # 注解内部一致性；不刷新任何基线
```

### 4.2 编译器裁判（逐类）

```bash
python3 tools/audit_type_layout.py --only UITitle_JDHY
python3 tools/audit_type_layout.py --only CCBStage
python3 tools/audit_type_layout.py --only CCBRoleState
```

期望：`sizeof` 分别 **290,488 / 672,040 / 20,568**；`max(member_end) <= binary_size` 且无 overlap 硬错。
具体 offset 断言（落地卡的单测里写成 static_assert）：

| 类 | 断言 |
|---|---|
| UITitle_JDHY | `sizeof==290488`；`offsetof(m_NoteItem)==0x262C8`；`offsetof(m_isItemShow)==0x262A4`；`offsetof(m_unk_0x46960)+sizeof(UIRoleDialog)==0x46EB8` |
| CCBStage | `sizeof==672040`；`offsetof(m_nRoleSlot)==0xA4`；`offsetof(m_unk_0xA3BD0)==0xA3BD0`；`0xA3BD0+sizeof(UIRoleDialog)==0xA4128` |
| CCBRoleState | `sizeof==20568`；`offsetof(m_nVideoState)==0x5054`；`0x5054+4==0x5058` |

### 4.3 证物报告

```bash
python3 tools/verify_fix.py --class CCBStage
python3 tools/verify_fix.py --class CCBRoleState
```

### 4.4 census

```bash
python3 tools/census_struct_holes.py     # 重算 data/status/struct_holes_*.json
```

期望（本卡实测基线 + 预期）：

| 类 | size | members | hole_bytes |
|---|---|---|---|
| UITitle_JDHY | 290,488（不变） | 43 | 8（不变） |
| CCBStage | 673,988 → **672,040** | 20 → **18** | 36 → **670,520** |
| CCBRoleState | 22,224 → **20,568** | 89 → **66** | 6,483 → **4,915** |

### 4.5 全链（独占窗口，每阶段一次）

```bash
python3 pipeline/cli.py loop --expect-s2 159/230 --expect-errors 622 --expect-l1 189
```

**读数基线（本卡 2026-11-27 02:09 实测 + 只读预检）**：

- `probe_census.json`：S2 **159/230**、总错误 **622**（time 2026-11-27T02:09:27）。
- `s4_baseline.json`：L1 棘轮记录 **189**、matched 1,138、symbols 1,246、partial 815。
- 已知恒红（不是本卡引入）：`compile_baseline.json` 159/233 vs `baselines/latest.json` 900/995 两份 S2 基线互相矛盾；`match` 的 L1 棘轮在无 loop 读数前显示「待测」。

⇒ 落地的通过标准：**S2 不降、总错误不增、L1 不降、check 无新错**。数字以「落地前当场重取」为准，本文数字只作参照（并发 #19/#30 在写 `data/annotations`，读数会漂）。

### 4.6 baseline 不重锚

- 不跑 `python3 pipeline/cli.py match --rebaseline`；loop 内不得出现 `[ratchet] REBASELINE` 行。
- **本文不采用 sha256 断言**：任务书里的 `f3aa8279…` 已失效——本卡 02:09 实测 `data/status/s4_baseline.json` sha256 为 `6707abf3…`，02:20 再读已变为 `20d5dd1b…`，L1 记录值同时也从 189 变成 **192**。两次读数不同即证明该判据不可用（每次 `match` 都会重写它，并发管线也在写）。改用「无 REBASELINE + L1 记录值不被改写为更低值」作为判据；落地卡执行时必须重取当时的 S2/L1，不得沿用本卡数字。

---

## 5. 顺序、依赖与拍板点

### 5.1 推荐顺序

1. **⑤ CCBRoleState 先行**：只动一个 JSON 的 `binary_size` + 删 23 员；不牵动任何其他类 sizeof（全部外部引用是指针）；洞立刻精确减 1,568B，收益可当场用 census 验证。
2. **③ CCBStage 次之**：尺寸修正是「类身份 + 分配」层面的硬错误（673,988 无任何分配支撑）；但会留下 670,504B 的洞，需要 Human 接受「成员表后置」。
3. **① UITitle_JDHY 只验收**：工作树已是 290,488/43 员且末端闭合，属他人未提交改动；本卡的动作是「确认归属 → 提交 → 跑 §4 验收」，不是再改。

### 5.2 与 R4 的冲突

- R4 #30/#34（gbVisNode+0x44、ScreenEffect/PalScriptWaitObj 多态化）与 #19（ScreenEffectRingNode 落地）都在写 `data/annotations/structs/`；R6 三项也在同一目录。**必须单写者串行**：同一窗口只允许一张 annotation 落地卡在跑，且落地前后各跑一次 `loop` 取读数。
- 本卡不占写域冲突（只新增 docs/specs）。

### 5.3 必须 Human 拍板的点

| 点 | 选项 | 建议 |
|---|---|---|
| ① 是否现在提交工作树里他人写的 290,488 | 提交 / 等 owner 自己提交 | 先确认 owner；无人在办时由落地卡提交 |
| ③ 是否接受「先改尺寸、670KB 洞后置」 | 接受（本卡方案）/ 先做成员重建卡 | 接受：尺寸错误比洞更硬；洞有 census 计量，不会误导 codegen |
| ⑤ 是否接受「删 15 员、20,644B 类后置」 | 接受 / 先给该类命名建卡 | 接受：15 员留在 CCBRoleState 里是**确定错误**（越界 1,656B），先删更安全 |

---

## 6. 风险与回退（逐项）

| 项 | 最坏情况 | 停止条件 | 回退 |
|---|---|---|---|
| ① | 覆盖他人未提交改动，或误 `checkout` 回 377,700 | 文件 owner 不明 / `git diff --stat` 与本文不符 | 不 checkout；用 `git stash` 前先 `cp` 备份工作树文件 |
| ③ | 成员删错导致 `check` 报 overlap；或 sizeof 变化影响 codegen 后的布局断言 | `audit_type_layout` 报 size≠672040 或 overlap | `git checkout -- data/annotations/structs/CCBStage.json`（已跟踪，可退） |
| ⑤ | 删 23 员时多删/少删；`m_BattleFlags` 仍有引用 | `grep -rn m_BattleFlags` 非空 / check 报未定义 | `git checkout -- data/annotations/structs/CCBRoleState.json` |
| 全链 | C1003 掩盖（CCBStage.cpp 等截断单元） | 总错误持平但截断单元最大行号变小 | 用 `cli.py status` 的截断单元行号判定，不只看总错误 |
| 并发 | 与 #19/#30/#34 的 annotation 写入交错 | `git status` 出现非本卡的 `M` annotation | 停手，让主理人排序；不 `git clean` |

**是否需要最小实验**：三项的尺寸都已有 ≥2 条独立 A 级证据（#22/#24/#27），不需要再做 sizeof 探针；但落地卡仍应把 §4.2 的 static_assert 写进 `tests/`，防止后续改动把尺寸改回去。

---

## 7. 给 PMO 的下一张实现卡草案（不建卡）

**卡 A（推荐先发）：CCBRoleState 尺寸与越界成员清理**

- 标题：`R6⑤ 落地：CCBRoleState binary_size 22224→20568，删除 23 个越界/跨类成员`
- writeScopes：`data/annotations/structs/CCBRoleState.json`、`tests/`
- 验收：§4.1–§4.6 中 CCBRoleState 那一列 + census 6,483→4,915 + `loop` S2/错误/L1 不退化
- blockedBy：无（但需与 #19/#30/#34 错峰）

**卡 B：CCBStage 尺寸修正与 B 对象剥离**

- 标题：`R6③ 落地：CCBStage binary_size 673988→672040，删 3 员、加 UIRoleDialog@0xA3BD0`
- writeScopes：`data/annotations/structs/CCBStage.json`、`tests/`
- 验收：§4 对应列 + census size/members/洞（670,520B）+ 大洞说明写进卡面
- blockedBy：卡 A（串行）

**卡 C：20,644B 无名类与 CCBStage-B 的正名/成员重建**（后置，可选）

- 标题：`R6 后续：为 CCBRoleState 尾 15 员所属 20,644B 类与 CCBStage 的 673,968B 兄弟对象建类取证`
- writeScopes：`data/annotations/structs/`、`docs/specs/`、`tests/`

**只批一件时先做哪件**：**卡 A（⑤ CCBRoleState）**。理由：它是三项里唯一「删掉的部分 100% 有反证、保留的部分 100% 在界内」的改动，失败面最小；且洞减少量可精确核验（−1,568B），能最快给出「施工图 → 落地 → 读数」的闭环样本，为 ③ 的大洞决策提供信心。

---

## 8. 复现命令（本文数字的来源）

```bash
# 1) 三项注解现状
python3 - <<'PY'
import json
for c in ['UITitle_JDHY','CCBStage','CCBRoleState']:
    d=json.load(open('data/annotations/structs/%s.json'%c))
    km=d.get('known_members') or {}
    offs=sorted(km,key=lambda k:int(k,16))
    print(c, d.get('binary_size'), 'members', len(km), 'base_size', d.get('base_size'),
          'bases', [b.get('name') for b in (d.get('bases') or [])],
          'first', offs[0], 'last', offs[-1], km[offs[-1]].get('name'), km[offs[-1]].get('type'))
PY

# 2) census 现状与 ≥0x5058 的洞合计（CCBRoleState 的 −1,568B）
python3 - <<'PY'
import json
h=json.load(open('data/status/struct_holes_20261125.json'))
for x in h['classes']:
    if x['cls'] in ('UITitle_JDHY','CCBStage','CCBRoleState'):
        print(x['cls'], x['size'], x['members'], x['hole_bytes'], x['holes'][:4])
x=[c for c in h['classes'] if c['cls']=='CCBRoleState'][0]
print('beyond 0x5058 =', sum(n for a,b,n in x['holes'] if int(a,16)>=0x5058))
PY

# 3) CCBStage 分配与 ctor 写界（A 级）
sed -n '/5233be:/,/5233f9:/p' data/status/_disasm_cache.txt
sed -n '/51dd2e:/,/51dd43:/p' data/status/_disasm_cache.txt

# 4) CCBStage-B 的 256 槽数组（证明 m_TaskGroups 属 B）
sed -n '/4fb9a5:/,/4fb9d8:/p' data/status/_disasm_cache.txt

# 5) CCBRoleState 分配与 ctor 写界
sed -n '/44c5f3:/,/44c621:/p' data/status/_disasm_cache.txt
sed -n '/456b2a:/,/456b3c:/p' data/status/_disasm_cache.txt

# 6) 三项的外部引用都是指针（sizeof 变化不移动别人）
grep -rn "CCBRoleState \*\|CCBStage \*\|UITitle_JDHY \*" data/annotations/structs/*.json | head
```

---

## 9. 边界与自检

- 本卡只读部分：未改 `data/annotations`、`pal3/src`、`pipeline`、`tests`、任何基线；未跑 `apply/export/codegen/probe/loop/match`；未 `git commit`。
- **只读边界有一处偏差（必须记录，不能算“已披露所以只读”）**：本卡为查工具参数执行了 `python3 tools/census_struct_holes.py --help`，该脚本不解析 `--help`，直接重写了**派生文件** `data/status/struct_holes_20261125.json`（mtime 02:12:21）。事实与影响见下面 §9.2；本卡**已改变该文件**，这一点不含糊。
- 只读预检：执行过 `python3 pipeline/cli.py status`（设计为只读、不刷新基线），§4.5 的 S2 159/230、总错误 622、L1 189 即来自该输出（02:09:27）。**02:20 再读已变为 L1 192**：基线与 census 都在被并发管线改写，落地卡必须重取当时读数，本文数字只证明「施工图写成时的状态」。
- 数字回源核对：三项注解值、census 洞、$0x5058 洞合计、CCBStage 的 `0xA4128` 与 `0x4FB9A0` 反汇编锚点均在本卡当场重跑；#22/#24/#27 的报告数字与实测一致（唯一差异：#27 §4.3 的「只剩 16B」已在 §2.3 更正并说明原因）。
- QA 四条自检：①三项 before→after 精确到 JSON 路径/成员且未改文件——是；②每项给 offsetof/sizeof/全链/census/不重锚与回退——是；③排序有依据（⑤→③→①验收），与 R4 串行、拍板点列明，给出「只批一件先做 ⑤」——是；④唯一新增本文件、未改注解/代码/基线、未跑管线——**是；但另有一次 census 重算，属派生状态文件，须按 §9.2 由 PMO 确认口径**（不宣称“纯只读”）。

### 9.2 census 重算：事实、确定性、差异与授权请求

**事实**：02:12:21 执行 `python3 tools/census_struct_holes.py --help`，脚本无参数解析，按当前注解 + `asm/pal3/ida_structs.json` 重算了 `data/status/struct_holes_20261125.json`。本文所有 census 数字（200 类 / 1,074 洞 / 820,538B、CCBStage 36B、CCBRoleState 6,483B 与 ≥0x5058 的 1,568B、UITitle_JDHY 8B）都取自这次重算后的文件。

**为什么没有回滚**：

1. 该文件在我执行前已是并发管线写的 `M`（mtime 01:44:37），`HEAD` 版本是更旧的 201 类 / 1,142 洞 / 1,275,908B；`git checkout` 会把并发管线的真实重算回退成旧数据，比不回滚更糟。
2. 它是**纯派生文件**：唯一输入是注解 JSON 与 IDB 导出，工具可随时重建，不承载人工信息。

**确定性证据（当场跑）**：先把重算版复制到 `/tmp/holes_at_misrun.json`，再执行一次 `python3 tools/census_struct_holes.py`（RC=0），两份 sha256 **完全相同**（`ab7f7cd8347292b9e44fb9d15fe86cd14b2379f80588199f03bc532cf49c9a2d`），`classes` 负载 `json.dumps(sort_keys=True)` 逐字节相等 ⇒ 当前文件就是「当前注解 + IDB」的纯函数输出，没有夹带、没有信息损失。

**重算前（HEAD）→ 重算后（当前）差异表**（按类，右侧全部可由他人已落地的注解改动解释；本卡不动注解，因此**没有一项差异来自本卡**）：

| 类 | HEAD hole_bytes | 当前 hole_bytes | Δ | HEAD size → 当前 size | 归因 |
|---|---|---|---|---|---|
| ScreenEffectMgr | 363,820 | 4 | −363,816 | 363,968 → **152** | #19/#34 已把 Mgr 落成 152B，洞自然塌缩 |
| SaleUI | 44,560 | —（类消失） | −44,560 | 105,912 → — | 该类已从注解移除 |
| UIGameFrm | 27,916 | 258 | −27,658 | 28,268 → 28,268 | 成员补全（他人落地） |
| UITitle_JDHY | 19,396 | 8 | −19,388 | 377,700 → **290,488** | ① 的 290,488 已由他人落进工作树（`M`，未提交） |
| CEffGroupNode | 4 | —（类消失） | −4 | 116 → — | 与 ScreenEffectRingNode 拆类一起调整 |
| ScreenEffectNode | 124 | 120 | −4 | 220 → 220 | 基类尺寸变化（PAL3VisNode 88→92） |
| UI3DModelNode | 68 | 64 | −4 | 248 → 248 | 同上 |
| ScreenEffectRingNode | —（无） | 64 | +64 | — → 363,968 | #19 新建离类 |
| **合计** | 1,275,908 | 820,538 | **−455,370** | | 8 类，逐项归因如上 |

**卡面口径变更请求（另一处需要 PMO 更新卡面）**：卡面验收条件写「`s4_baseline` 不重锚（sha256 仍 f3aa8279…）」，实测该值已失效，而且**在半小时内变了两次**：02:09 为 `6707abf3…`、02:20 为 `20d5dd1b…`（期间 L1 记录 189→192）。这不是一次性的漂移，而是 `match` 每次重写该文件的固有行为，任何固定 sha 断言都会立刻过期。本文改用「`loop` 输出不出现 REBASELINE 行 + L1 记录值不被改写为更低值」作为不重锚判据，**请 PMO 把卡面 sha 断言改成这条**。

**PMO 裁定（已回，选项 A）**：PMO 自动决策选「A：接受重算版为基线，卡面补一句『派生 census 允许重算，须附确定性证据与差异表』」（决策单 `inb_01M8CHAW4RVM1CCCXJYMSN`，#37 thread seq 4）。因此本文 census 数字即为准；同时本文已按要求附上确定性证据（sha256 两次相同 + `classes` 逐字节相等）、差异表（8 类、−455,370B、逐项归因），以及“为什么未回滚”。

后续落地卡（§7 的卡 A/B/C）的卡面应带上这句授权措辞，避免下次再就同一件事退回；若某张卡要求严格只读，须在卡面写明「禁止执行 `tools/census_struct_holes.py` 等会重写派生文件的工具」，不能只写「只读 census」。

