# R6 六项挂账决策简报：每题选项、证据、影响与推荐

> **时点说明（2026-11-27）**：§0–§9 保留 2026-11-26 23:18 原文（含提交后三处行号校正），保持不动；§10 是 2026-11-27 R6① 增量（#22 已验收），§11 是 R6⑤ 增量（#24 已验收），§12 是 R6③ 增量（#27 已验收），§13 是 R6② 增量（#29 已验收）。任务卡原写“§7/§8”“§9/§10”为增量，因原文 §7 已是表 A、§10/§11 已被前两次增量占用，实际落 §10–§13，不重排旧编号。

- 性质：**只汇编、不裁决**。本文把 R6 卷宗（`docs/audit/2026-11-26-r6-backlog-dossier.md`，225 行）转成一页可拍板清单；不新增未取证结论，不声称任何一项已经拍板。
- 编制：墨痕（Task #17，`tsk_01M8C6RYCZZC4WTE5QYR91`），2026-11-26 23:1x（Asia/Shanghai）。
- 数据时点：注解尺寸/成员取工作树 JSON（各族 mtime 见各题）；金表 `data/status/goldtable_size_corrections_20261126.md` mtime 01:27:27；堆分配普查 `data/status/probe_heap_alloc_census_20261126.json` 读于本次、来源提交 `1a52354e2`；洞普查 `data/status/struct_holes_20261125.json` 读于本次（201 类 / 1,123 洞 / 875,232B；文件 mtime 23:15:51，并发 loop 重写过但数值未变）；双类裁决 `data/status/ccbcamcontrol_twin_adjudication_20261126.md` mtime 08:59:33。
- 写面：仅本文件。未改 annotation、代码、基线、生成树；未跑 apply/export/codegen/probe/match/loop。
- 状态前提（必须带进执行）：R4 的 `data/annotations/structs/ScreenEffectMgr.json` 仍是工作树未提交改动（`M`，+60 行）；R5 的 `SaleUI.json` 已随 HEAD `5b15fc482` 提交（binary_size 105,912 / 55 员）。六项均不直接改这两个类；但任何执行卡都不得与在跑 loop/#6 验收并发。

## 0. 一页结论

| # | 挂账项 | 证据等级 | 本文推荐 | 优先 |
|---|---|---|---|---|
| ① | UITitle_JDHY / Note_Item 双布局 | A（尺寸矛盾）/ 缺口：布局判据 | 先取证 Note_Item 尺寸与 99/50 步进，暂保 377,700 + `void*` | P1 |
| ② | C2DSpark / tagSpark 重验 | B（48B 是反推） | 先观测 stride×count，暂保 24,688 | P1 |
| ③ | CCBStage 三数字 | B（两笔分配 A 级，第三数无分配行） | 先辨两个 new 站点的接收者，暂保 673,988 | P1 |
| ④ | PropUI 差 164 | B | 先确认两处 InitUI 是否同类、尾 96B，暂保 29,056 | P2 |
| ⑤ | CCBRoleState ctor 写界 | B（两侧 A 级互斥） | 先只读取界；证据出来前保持回退态 22,224 | **P0** |
| ⑥ | 堆类 402,824 / CCCTData | A（身份定谳）/ 缺口：重铸未做 | 按 402,824 重铸 `CCCTData.json`，非从零命名 | **P0** |

建议开工顺序：**⑥ → ⑤ → ① → ③ → ② → ④**。⑥/⑤ 都卡在「注解与金表互斥」，且会反向影响域边界；① 影响 R2 的 `EquipUI+0x2AFD0` 指针类型化；③②④ 是单类收尾，可并行。

---

## 1. ① UITitle_JDHY / Note_Item 双布局

**决策问题**：`UITitle_JDHY` 的真实 sizeof 是金表 290,488 还是注解 377,700；`m_NoteItem` 的 99 个元素应按 `Note_Item` 3,560B 还是槽跨反推的 3,728B 排；是否存在另一套 `Role[50]` 布局。

**现状与关键数字（并列，不取平均）**

| 数字 | 出处 | 等级/时点 |
|---|---|---|
| `binary_size=377,700`；`m_NoteItem@0x634 = Note_Item[99]`；下一员 `0x5a7e4 m_Title_JDHY UIStatic` | `data/annotations/structs/UITitle_JDHY.json`（28 员，mtime 11-25 22:03） | 注解，B |
| `Note_Item binary_size=3,560`（12 员，末端 `m_NoteLv` @0x9c0） | `data/annotations/structs/Note_Item.json` | 注解，B |
| 数组跨度 `99×3,560=352,440`，绝对末端 `0x634(1,588)+352,440=354,028` | 本文按注解算术 | A（算术） |
| 槽跨 `0x5a7e4-0x634=369,072`；`/99=3,728.0` | 卷宗 `:55`；本文复算 | A（算术） |
| 金表 `290,488=0x46EB8`，ctor 名义 `?DestroyPages@UITitle_JDHY`，store `EquipUI+0x2AFD0`，site `0x4a46c4` | `probe_heap_alloc_census_20261126.json`；金表 `:18-20` | A（push 字面量+mangle） |
| 金表比槽跨少 `78,584`；比注解少 `87,212`；比数组末端少 `63,540` | 本文复算 | A（算术） |
| 洞 `19,396B/14` | `struct_holes_20261125.json` | 普查，B |

**选项与影响**

| 方案 | 动作 | 影响面 | R4/R5/风险 |
|---|---|---|---|
| A 按金表重铸 | `UITitle_JDHY` → 290,488，同时把 `Note_Item[99]` 改到能收口 | 触发 binary_size 门禁；现有 99×3,560 末端 354,028 > 290,488，**loop 必拦**；洞 19,396/14 全表重算 | 不触 R4/R5；需先证明 290,488 对应的数组长度/步进，否则是把一个矛盾换成另一个 |
| B 按注解保形 | 保持 377,700，`EquipUI+0x2AFD0` 继续 `void*`+note | 不动门禁；洞 19,396/14 保留；金表冲突继续挂账 | 不触 R4/R5；`void*` 是当前正确的临时态，但类型化继续被阻塞 |
| C 先取证（推荐） | 只读取 `Note_Item` UDT readback、`PopulateContent`/`SaveData`/ctor 的 `stride×count` 字面量（99 或 50）、`0x4a46c4` 分配后 store 链 | 不动门禁、不改注解；产出是裁决依据 | 不触 R4/R5；`Role[50]` 目前只见于金表挂账段（卷宗 `:207`），必须显式标为假设 |

**推荐**：C。A 在现有成员布局下数学上收不了口（99×3,560 已越过 290,488），B 只是继续挂账；先拿出「Note_Item 真实尺寸 + 99/50 的来源」才能一次改对。

**需要 Human 拍板**：选 C（先做只读取证，暂不动 binary_size），还是直接选 A/B？

---

## 2. ② C2DSpark / tagSpark 重验

**决策问题**：`C2DSpark` 的真实 sizeof 是金表 22,640 还是注解 24,688；`m_Spark` 是 512×48B（24,576）还是元素数/元素尺寸另有其值。

**现状与关键数字（并列）**

| 数字 | 出处 | 等级/时点 |
|---|---|---|
| `C2DSpark binary_size=24,688`；`m_Spark@0x0 = C2DSpark_tagSpark[512]`；数组末端 24,576，之后 112B 尾员 | `data/annotations/structs/C2DSpark.json`（mtime 11-18 18:41） | 注解，B |
| `tagSpark binary_size=48`，note 原文「Size=48 from array stride (24576/512)」 | `C2DSpark_tagSpark.json` | **反推值**，B |
| 金表 `22,640=0x5870`，`??0C2DSpark`，site `0x512af0` | `probe_heap_alloc_census`；金表 `:21-22` | A（push 字面量+mangle） |
| 24,576 − 22,640 = **+1,936**（数组已超金表） | 本文算术 | A（算术） |
| 洞 | 普查无该类条目（未列） | `struct_holes` |

**选项与影响**

| 方案 | 动作 | 影响面 | R4/R5/风险 |
|---|---|---|---|
| A 按金表重铸 | `C2DSpark` → 22,640 | 触发门禁；现有 512×48 数组末端 24,576 > 22,640，**loop 必拦**；必须同时改元素数或 tagSpark 尺寸 | 不触 R4/R5；候选算术（471×48=22,608、512×44=22,528）都不等于 22,640，不能硬凑 |
| B 保注解挂账 | 24,688/48 不动 | 不动门禁；A 级金表冲突保留 | 不触 R4/R5；48B 仍是反推值 |
| C 先观测（推荐） | 从 `CreateSingle@0x4d5ec0` / `Render@0x4d6380` 取数组步进与 512 循环上界；`CreateMore`/`DestroyAll` 交叉 | 不动门禁；产出 stride/count 的原值 | 不触 R4/R5；这是把「反推」变「观测」的最小成本 |

**推荐**：C。B 级证据的根因就是 48B 从未被直接观测；先拿到步进常数，再决定是改元素数还是改 `tagSpark`。

**需要 Human 拍板**：选 C（先做步进观测，暂保 24,688），还是直接按金表 A / 保注解 B？

---

## 3. ③ CCBStage 三数字

**决策问题**：672,040（`??0CCBStage`）、673,968（`InitFromDescriptor@CCBStage`）、673,988（注解）是「一个对象的三个口径」还是「两个对象/两态各自尺寸」；若采信 673,968，`m_dwAniFlagOver@0xa48c0` 是否仍在类内。

**现状与关键数字（并列）**

| 数字 | 出处 | 等级/时点 |
|---|---|---|
| `binary_size=673,988`；`base_size=72`，`bases=[UIListBox@0]`；末员 `m_dwAniFlagOver` 末端 `0xa48c4=673,988` 顶格 | `CCBStage.json`（mtime 11-25 10:34） | 注解，B |
| ctor `672,040=0xA4128`，site `0x5233cd`，store `esi+0x6CC`，caller `InitGameSystems@CUtil` | `probe_heap_alloc_census`；金表 `:23-25` | A（分配行） |
| `InitFromDescriptor` `673,968=0xA48B0`，site `0x512856`，store `esi+0x14`，caller `ProcNormalAttack@CCBSystem` | 同上 | A（分配行，但被 new 的类需二次确认） |
| 673,968−673,988=**−20B**；672,040−673,988=**−1,948B** | 本文算术 | A（算术） |
| 洞 `36B/2`：`[0x48,0x58)=16`、`[0xa48ac,0xa48c0)=20` | `struct_holes` | 普查，B |

**选项与影响**

| 方案 | 动作 | 影响面 | R4/R5/风险 |
|---|---|---|---|
| A 采信 ctor 672,040 | 缩到 672,040，尾部 1,948B 成员移出/重挂 | 触发门禁；`m_dwAniFlagOver` 等尾部成员落到类外，loop 会拦；洞 36/2 重算 | 不触 R4/R5；可能把「池态对象」与「完整对象」混为一谈 |
| B 采信 673,968 | 缩 20B（尾部 20B 洞消失或成员边界调整） | 触发门禁；改动小但必须解释 `InitFromDescriptor` new 的是不是 CCBStage | 不触 R4/R5；−20B 恰好是尾部洞宽度，可能是强线索也可能是巧合 |
| C 先辨接收者（推荐） | 只读两个 new 站点：返回值去向、`mov ecx` 后 call 的 mangle、是否同一 this；再看 ctor/Init 写偏移上界 | 不动门禁；产出「一对象三数/两对象各自数」定性 | 不触 R4/R5；与本轮 R4/R5 无交集 |

**推荐**：C。两笔分配都是 A 级，但「谁被 new」未证；先定性再改尺寸，避免重演 ⑤ 的越界回退。

**需要 Human 拍板**：选 C（先辨两站点接收者，暂保 673,988），还是直接采信 672,040（A）/673,968（B）？

---

## 4. ④ PropUI 差 164

**决策问题**：`PropUI` 的真实 sizeof 是金表 28,892 还是注解 29,056；两处 `InitUI@PropUI` new 的是否同一类；注解末端 28,960 超金表 68B 是尾部多算还是金表对象是派生/子对象。

**现状与关键数字（并列）**

| 数字 | 出处 | 等级/时点 |
|---|---|---|
| `binary_size=29,056`；95 员；末员 `mb_OKRc` 末端 `0x7120=28,960` | `PropUI.json`（mtime 11-24 21:20） | 注解，B |
| 金表 `28,892=0x70DC` ×2，`?InitUI@PropUI`，site `0x45975e`/`0x523431` | `probe_heap_alloc_census`；金表 `:36` | A（两笔分配行） |
| 29,056−28,892=**164**；28,960−28,892=**+68**（末端越界） | 本文算术 | A（算术） |
| 洞 `18,652B/45` | `struct_holes` | 普查，B |

**选项与影响**

| 方案 | 动作 | 影响面 | R4/R5/风险 |
|---|---|---|---|
| A 按金表 28,892 | 缩 164，并处理 68B 尾部越界 | 触发门禁；现有成员末端 28,960 > 28,892，**loop 必拦**；洞 18,652/45 重算 | 不触 R4/R5；若两处 new 不同类，28,892 不是 PropUI 的 sizeof |
| B 保注解挂账 | 29,056 不动 | 不动门禁；差 164 保留 | 不触 R4/R5；成本最低，但金表冲突继续 |
| C 先确认同类+尾 96B（推荐） | 两处 `InitUI` 的 `mov ecx` 后 mangle/接收者；查 28,960 之后是否还有派生成员（现注解到 0x7110 为止） | 不动门禁；产出「谁是 sizeof」判据 | 不触 R4/R5；可并入金表第二批，但不要批量改 |

**推荐**：C，若只求低风险可先按 B 挂账。两笔 28,892 同值同 mangle，但仍需排除其中一笔是子对象；先确认再动，避免 68B 尾部被硬删。

**需要 Human 拍板**：选 C（先确认同类/尾部，暂保 29,056），还是直接按金表 A / 保注解 B？

---

## 5. ⑤ CCBRoleState ctor 写界（P0）

**决策问题**：`??0CCBRoleState` 的分配 20,568 与注解成员写至 0x56cc（末端 22,224）互斥——是 ctor 名义误挂到另一个类，还是 0x55c8..0x56cc 段成员越界；`ClearAndSetGP` 的 20,644 是 self-new 还是工厂。

**现状与关键数字（并列）**

| 数字 | 出处 | 等级/时点 |
|---|---|---|
| `binary_size=22,224`；89 员；`bases=[UIListBox@0]`；`m_BattleFlags@0x56cc` 末端 `0x56d0=22,224` 顶格 | `CCBRoleState.json`（mtime 11-26 01:00） | 注解，B |
| ctor `20,568=0x5058`，site `0x44c5f8`，caller `CreateSettingsUI@UIScenePanel` | `probe_heap_alloc_census`；金表 `:15` | A（分配行） |
| `ClearAndSetGP` `20,644=0x50A4`，site `0x512730`，store `esi+0x10`，caller `ProcNormalAttack@CCBSystem` | 同上 | A（分配行，self/工厂未辨） |
| 22,224−20,568=**1,656**；22,224−20,644=**1,580** | 本文算术 | A（算术） |
| 第一遍 loop 已把 20,568 **回退**为 22,224（成员末端越界触发拦截） | 金表 `:44-47` | 现场记录，A（已发生） |
| 洞 `6,483B/27` | `struct_holes` | 普查，B |

**选项与影响**

| 方案 | 动作 | 影响面 | R4/R5/风险 |
|---|---|---|---|
| A 采信 ctor 20,568 | 缩 1,656，0x55c8..0x56cc 段移出/重挂 | 触发门禁；当前成员末端顶格 22,224，缩后大面积越界；**已有一次回退先例** | 不触 R4/R5；误判会丢 89 员中的尾部语义，代价最高 |
| B 保 22,224、改 ctor 名 | 若 ctor 体只写到 0x5058，则 0x5058 字面量属另一个类；保留成员并把 ctor 重挂/改名 | 不改 binary_size 则不一定触发尺寸门禁，但改 functions/归属需独立验收；洞 6,483/27 不变 | 不触 R4/R5；需 ctor 体写偏移上界作硬证据，不能只凭名字 |
| C 先只读取界（推荐） | 反汇编 `0x44c5f8` new 后 `mov ecx,eax; call ??0CCBRoleState`，取 ctor 写偏移最大值；再看 `0x512730` 是否 self-new | 不动门禁、不改注解；产出「ctor 误名 vs 成员越界」判据 | 不触 R4/R5；P0 但首卡只读，避免再次盲改回退 |

**推荐**：C。这是「成员越界 vs ctor 误名」的判据问题；在写界证据出来前保持 22,224（现回退态），不要再用 20,568 试错。

**需要 Human 拍板**：批准先做只读 ctor 写界取证（不动 binary_size）吗？还是直接选 A（缩 20,568）/B（保 22,224 改 ctor 名）？

---

## 6. ⑥ 堆类 402,824 / CCCTData 重铸（P0）

**决策问题**：`402,824=0x62588` 的类 Y 身份已由 twin 裁决定为 `CCCTData`，但 `CCCTData.json` 仍是 chimera（430,256=类 X 的尺寸、`known_members=0`）——是现在按 402,824 重铸 `CCCTData.json`，还是继续把「待名」挂账/另立新类。

**现状与关键数字（并列）**

| 数字 | 出处 | 等级/时点 |
|---|---|---|
| `CCCTData.json binary_size=430,256`，`known_members=0`，`bases=None`，methods 22 | 工作树注解（mtime 11-26 09:51） | 注解，chimera 实锤 |
| 类 Y `402,824=0x62588`，ctor `CCCTData_6F10@0x4a6f10`，store `EquipUI+0x2AFC8`，site `0x4a4660` | `probe_heap_alloc_census`；twin `:145/:205-209` | A（分配行+store+ctor） |
| 类 X `430,256=0x690B0`（CCBCamControl），池方法 disp `0x68FD0=425,424 > 402,824` ⇒ 池属 X 非 Y | twin `:205-209` | A（判别式） |
| 402,824 与 430,256 差 **27,432** | 本文算术 | A（算术） |
| 洞 `430,256B/1`（整类一洞） | `struct_holes` | 普查，B |
| 方法表：注解 22 条 vs twin 指「15 PDB API」 | `CCCTData.json`；twin `:215` | 冲突，需重铸时对齐 |

**选项与影响**

| 方案 | 动作 | 影响面 | R4/R5/风险 |
|---|---|---|---|
| A 重铸 CCCTData（推荐） | `binary_size=402,824`；方法表按 15 条 PDB API 重挂；池/表成员重验；`EquipUI+0x2AFC8` 从 `void*` 升 `CCCTData*`；ctor 名 `CCCTData_6F10` 语义化 | 触发门禁；洞从 430,256/1 按新成员表重算（目标显著下降，不承诺 0）；影响 EquipUI 七槽与 CCBCamControl 域分离 | 不触 R4/R5；与 R2 的 EquipUI 七槽类型化直接相关；必须一次 loop |
| B 维持 chimera 挂账 | 430,256/0 员不动，`+0x2AFC8` 继续 `void*` | 不动门禁；洞 430,256/1 保留；普查继续把类 X 尺寸算在 CCCTData 头上 | 不触 R4/R5；会持续误导洞排名与指针类型化 |
| C 另立新类给 402,824 | 新建类名，`CCCTData` 保留 430,256 | 触发门禁/归属迁移；与 twin「类 Y=CCCTData」冲突，等于把已定谳身份再拆一次 | 不触 R4/R5；不建议，违反「同一语义不发明两个名字」 |

**推荐**：A。身份已有 A 级裁决（ctor/store/disp 判别），「待名」实际是「重铸未做」；按 402,824 重铸并语义化 `CCCTData_6F10`，不要从零命名，也不要另立新类。

**需要 Human 拍板**：选 A（按 402,824 重铸）/ B（继续挂账）/ C（另立新类）？

---

## 7. 表 A：优先级、依赖、owner 技能面

| # | 优先 | 关键依赖 | owner 技能面 | 为什么这个顺序 |
|---|---|---|---|---|
| ⑥ | P0 | EquipUI 七槽类型化、CCBCamControl 域分离 | coder（需读 PDB/堆分配/池方法） | 身份已定谳，落地会反向修正 EquipUI/CCBCamControl 的域边界 |
| ⑤ | P0 | binary_size 修正必过 loop 门禁 | coder（需反汇编 ctor 写界） | 误判会再次触发越界回退，必须先定「ctor 误名/成员越界」 |
| ① | P1 | R2 `EquipUI+0x2AFD0` 指针类型化 | coder（Note_Item UDT/stride） | ① 的裁决决定该槽 pointee 是 JDHY 还是数组本身 |
| ③ | P1 | 无 | coder（两 new 站点接收者） | 单类收尾，可与 ②/④ 并行 |
| ② | P1 | 无 | coder（stride/count 观测） | 单类收尾，48B 反推值需一次直接观测 |
| ④ | P2 | 可并入金表第二批 | coder（InitUI 同类/尾部） | 差 164 且末端仅超 68B，风险最低，可最后做 |

## 8. 表 B：决策后第一张执行卡草案（只写草案，未创建）

以下按「本文推荐方案」写；若 Human 选 A/B，首卡应改为对应落地卡。表内 docs/specs 下的路径均为**草案、尚未创建**，不作为已存在证据引用。

| # | 首卡类型 | 建议 writeScopes | 验收读数 / 停止条件 |
|---|---|---|---|
| ⑥ | 落地：CCCTData 重铸 | `data/annotations/structs/CCCTData.json`、`data/annotations/structs/EquipUI.json`、`data/status/ccctdata_recast_20261126.md`、`tests/` | `CCCTData binary_size=402,824`、方法表=15 条 PDB API、`EquipUI+0x2AFC8` 为 `CCCTData*`；洞从 430,256/1 重算且低于原值；loop S2 不低于执行前当轮基线、L1 不低于 189（若基线未被并发改写）；不重锚 |
| ⑤ | 只读取证：ctor 写界 | `docs/specs/2026-11-26-ccbrolestate-ctor-writebound.md` | 给出 ctor 写偏移最大值（≤0x5058 或 ≥0x56cc）、`ClearAndSetGP` 是否 self-new；不动 binary_size、不跑 apply/export/codegen |
| ① | 只读取证：JDHY/Note_Item 布局 | `docs/specs/2026-11-26-jdhy-noteitem-layout-evidence.md` | `Note_Item` UDT 实测尺寸（3,560 或 3,728）、`stride×count` 的 99/50 字面量、`0x4a46c4` store 链；不动 binary_size |
| ③ | 只读取证：CCBStage 两 new 接收者 | `docs/specs/2026-11-26-ccbstage-two-new-receivers.md` | 两个 site 的返回值去向、`mov ecx` 后 mangle、是否同一 this；给出「一对象三数/两对象各自数」定性；不动 binary_size |
| ② | 只读取证：C2DSpark stride/count | `docs/specs/2026-11-26-c2dspark-tagspark-stride-evidence.md` | `CreateSingle@0x4d5ec0`/`Render@0x4d6380` 的步进与 512 上界；给出元素数或 tagSpark 尺寸的唯一候选；不动 binary_size |
| ④ | 只读取证：PropUI 同类/尾部 | `docs/specs/2026-11-26-propui-size-evidence.md` | 两处 `InitUI` 的 mangle/接收者、28,960 后是否还有成员；给出 28,892/29,056 的判据；不动 binary_size |

**共同验收前提**：任何落地卡先 `apply→export→codegen→probe→match` 全链；证前确认 `asm/pal3/ida_structs.json` 晚于最近 annotation 改动；不与 #6 验收或在跑 loop 并发；四份基线不重锚；执行后回填 `evidence_ledger`（六项目前均无 ev 条目）。

## 9. 共同边界与证据索引

- **六项都不在裁定队列**：`data/status/adjudication_queue.json` 读于 2026-11-26 23:10:21，`queue={}`；六项也无 ev 条目（`data/status/evidence_ledger.json` 当前 8 条，ev_0003–ev_0008 均为 RoleState/ScreenEffect/MagicUI，无本题六项）。本文只给选项，不代表已入队/已裁决。
- **数字并列原则**：① 的 377,700/290,488/352,440/3,728 四个数、② 的 24,688/22,640/24,576/48、③ 的 672,040/673,968/673,988、④ 的 29,056/28,892/28,960、⑤ 的 22,224/20,568/20,644、⑥ 的 430,256/402,824 均按原样并列；本文未取平均、未静默选一个。
- **已提交/工作树/仅盘点三态**：R4 `ScreenEffectMgr.json` 为工作树 `M`（+60 行，未提交），不得写成已生效；R5 `SaleUI.json` 已随 HEAD `5b15fc482` 提交（105,912/55 员）；六项均为工作树注解或已提交金表/普查的盘点，不是已落地改动。
- **#6 状态**：`pending_acceptance`；其自测 S2 158/229、L1 189 未验收，不作为本文或执行卡的基线。
- **卷宗与一手账本**：`docs/audit/2026-11-26-r6-backlog-dossier.md`（第 45–219 行，六项账目与指针）；`data/status/goldtable_size_corrections_20261126.md`（第 14–47 行，差异与回退先例）；`data/status/probe_heap_alloc_census_20261126.json`（33 笔分配，六项尺寸行）；`data/status/ccbcamcontrol_twin_adjudication_20261126.md`（第 140–222 行，类 X/Y 定谳与手术清单）；`data/status/struct_holes_20261125.json`（201 类/1,123 洞/875,232B）。
- **约束自证**：本文件是本次唯一新增；本卡未改 `data/annotations`、`pal3/src`、`pipeline`、四份基线、README/handoff；未跑 apply/export/codegen/probe/match/loop；未创建执行卡、未写 `adjudication_queue`/`evidence_ledger`。工作树里 `s4_baseline.json`/`s4_diff_detail.json`/`s4_l1_identity_cur.json`/`struct_holes_20261125.json` 等 `M` 来自并发 loop 或他人卡，不是本卡动作。

## 10. 2026-11-27 取证增量（R6①，#22 已验收）

- 性质：**增量，不改写历史正文**。§0–§9 保持 23:18 原文；本节只摘 #22 的 A 级结论与判别链，并把 ① 的推荐从“先取证”更新为“A 级支持 290,488”，但**不替 Human 拍板**。
- #22 状态：`tsk_01M8C9B3E8ZEPN20YSX515`（R6① 双布局取证）已由白砚验收。报告全文：`docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md`（353 行）。
- 本卡不改注解、不跑管线；下面所有数字都指到 #22 的章节、VA 或仓库产物。

### 10.1 A 级判别链（逐条带指令/VA）

1. **对象分配尺寸**（#22 §0 结论1、§2.1）：`0x4A46B5 push 0x46EB8`（290,488）→ `0x4A46C4 call 0x55353B`（operator new）→ `0x4A46DE call 0x4B01D0`（真 ctor）→ `0x4A46F2 mov [esi+0x2AFD0],eax`（存入 RoleStatePanel 第 7 槽）。对应 `data/status/_disasm_cache.txt:207302-207319`。
2. **ctor 写界闭合**（#22 §2.2）：末子对象 `UIRoleDialog@0x46960`，尺寸 1,368=0x558，`0x46960+0x558=0x46EB8`，与分配立即数精确相等；最高标量写只到 `[esi+0x45EA8]`。
3. **数组 stride×count 闭合**（#22 §2.3）：两处 vector-ctor-iterator 都是 `(ptr=esi+0x262C8, size=0xDE8, count=0x24=36, ctor=0x454AA0)`；`0x262C8+36×3,560=0x45768`，正好接下一员 `m_unk_0x45768`，成员链无缝。`m_isItemShow` 的清零是 `mov ecx,9; rep stos dword`=36 字节。
4. **Note_Item 自身 ctor**（#22 §2.4）：`0xD50+0x98=0xDE8=3,560`，ctor 无 ≥0xDE8 的成员写。
5. **访问位移直方图**（#22 §2.6，B 级佐证）：1,359 条带位移指令，最大 `0x46E9D`；`>=0x46EB8` 的访问为 **0 条**。没有方法把对象当大于 290,488 使用。
6. **反向排除**（#22 §2.1、§2.7）：全库没有 `push 0x5C364`（377,700）或 `push 0x5C404`（377,860）；`ctor_layout_decode.json` 对该类记 `status=no-func`；PDB 的 377,860/3,728 是 PAL3A 构建（PDB `UIStatic=160` vs 本 exe 152，差 168=21×8）。

结论（#22 §4，A 级）：**本 exe `sizeof(UITitle_JDHY)=290,488`、`sizeof(Note_Item)=3,560`、`m_NoteItem[36]@0x262C8`**。377,700 是旧注解、352,440 是 `99×3,560` 的混算、3,728 是旧布局派生量/PAL3A PDB 值，三条线都没有本 exe 证据。

### 10.2 ① 的推荐变化（不是拍板）

原文 §0/§1 的推荐是“先取证 Note_Item 尺寸与 99/50 步进，暂保 377,700 + `void*`”。增量改为：

> **A 级证据支持 290,488 / 3,560 / `[36]@0x262C8`；377,700、99×3,560=352,440、3,728 不应作为本 exe 目标。**

但这只是推荐更新，**不是 Human 已拍板**。待拍板问题改为：

> **是否按 290,488 重铸 ①？**

| 选项 | 动作 | 影响与风险 |
|---|---|---|
| **A. 按 290,488 重铸（推荐）** | 改 `binary_size=290,488`；`m_NoteItem` 改 `Note_Item[36]@0x262C8`；`m_isItemShow` 改 36 字节；旧 `0x5A7E4..0x5B91C` 成员**移除而非搬家**；再把 `RoleStatePanel+0x2AFD0` 类型化为 `UITitle_JDHY*` | 与四路闭合证据一致；落地后必须重跑 census 才能得到新洞账；需在无并发 loop 的窗口跑 apply→export→codegen→probe |
| **B. 暂不重铸** | 保留旧注解，只在文档标“已过时” | 不立即冒险，但 census 继续按 377,700 记 19,396B 假洞，`+0x2AFD0` 仍只能 `void*`；下一张卡还要重来 |
| **C. 先补内部空隙再重铸（两步）** | 先只读取证 290,488 布局内部的未命名段，再改 `binary_size`/数组 | 风险最低但最慢；仍要面对“旧成员是删除不是搬家”，不能绕过尺寸修正 |

### 10.3 三态（必须带进执行）

- **#22 已验收**：A 级结论可用；报告是 `docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md`。
- **工作树 `UITitle_JDHY.json` 是他人未提交改动**：现为 `binary_size=290,488`、43 员、`git status` 为 `M`；本卡实读 mtime 为 **2026-11-27 00:21:56**（#22 报告 §7 记录的 23:50:11 是更早一次写入，其间并发任务又改过），**不算本卡生效，也未提交**。HEAD 版仍是 377,700/28 员。
- **census 仍是旧账**：`data/status/struct_holes_20261125.json`（mtime 2026-11-27 00:10:25）中 `UITitle_JDHY` 仍为 `size=377,700 / members=28 / hole_bytes=19,396 / 14 段`；`Note_Item` 不在该普查的 201 类内。落地后必须重跑 census 才能得新洞账，不能拿旧 19,396B 当重铸后结果。

### 10.4 影响面（只写，不改）

- `binary_size` 从 377,700 改 290,488，直接改变该类的洞普查口径。
- `m_NoteItem` 从 `[99]@0x634` 改为 `[36]@0x262C8`，元素尺寸 3,560；`m_isItemShow` 从 `[99]` 改 `[36]`。
- 旧布局 `0x5A7E4..0x5B91C` 的成员（`m_Title_JDHY`、`m_TopBar`、`m_noteState` 等）在 290,488 内不存在，应删除；不能原偏移搬家。
- `RoleStatePanel+0x2AFD0` 第 7 槽可从 `void*` 类型化为 `UITitle_JDHY*`；其余六槽不受影响。
- 旧 census 的 `0x566EC..0x5A7E4`（16,632B）与 `0x5B920..0x5C364`（2,628B）两段是 377,700 假设的产物，重铸后应消失；`Note_Item` 不进本 census 的类账。
- 本卡没有改任何注解/数据/代码，以上只是落地卡的影响清单。

### 10.5 与原文的关系

原文 §0 的 ① 行、§1 的并列数与“先取证”推荐保留作历史；凡与本节冲突处，**以本节为准**。本节不重写 §1–§9，也不把 #22 的结论写成已落地。

## 11. 2026-11-27 取证增量（R6⑤，#24 已验收）

- 性质：**增量，不改写历史正文**。§0–§10 保持原样；本节只摘 #24 的判别链与定谳，并把 ⑤ 的推荐从“二选一、先核对 ctor 是否越界”更新为“ctor 不越界；20,568 有二进制支撑；22,224 是注解 89 员末端算术 + 三类混装”，但**不替 Human 拍板**。
- #24 状态：`tsk_01M8CADS47F7XPAYVYGK37`（R6⑤ ctor 写界取证）已由白砚验收。报告全文：`docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md`（246 行）。
- 证据等级要分开读：分配行与 ctor 写界是 **A 级**；尾部 23 员的跨类归属是 **B 级**；总体定谳 **B（伪命题）**。本节不把 B 级归属写成 A 级。

### 11.1 判别链（逐条带 #24 章节/VA）

1. **唯一分配**（#24 §2.2）：`0x44c5f3 push 0x5058`（20,568）→ `0x44c5f8 call 0x55353B`（`operator new`）→ `0x44c60e call 0x456ab0`（`??0CCBRoleState`）。`data/status/_disasm_cache.txt:101376-101384`；`push 0x5058` 全库仅此一处。
2. **ctor 写界闭合**（#24 §2.3）：ctor 体 `0x456ab0..0x456b58` 的最远对象写入是 `0x456b2a mov DWORD PTR [esi+0x5054],edi`，写入终点 `0x5054+4=0x5058`，与分配立即数**逐字节相等**；vptr 在 `0x456b36` 写 `0x56b364`，该表只属 CCBRoleState，排除“ctor 是另一个类”。
3. **22,224 没有分配支撑**（#24 §3.3）：全库 `grep -cE "push\s+0x56d0\b"` = **0**；22,224 只出现在注解与 IDB，而 IDB 的 size 由注解导出，不是独立证据。
4. **尾部 23 员跨类混装**（#24 §4.1，B 级）：`0x5060..0x50A0` 15 员属另一个 20,644B 类（`0x51272b push 0x50a4` → `0x51274e call 0x4ec680`，该 ctor 用 `mov ecx,0x1429; rep stos` 清零 `0x50A4`）；`0x55C8/0x55C9/0x55CC/0x55D0` 4 员全库零访问；`0x5654/0x5658/0x565C` 3 员属 `CCBUIPanel`（22,112B，访问者 `0x44a2e0` 由 `CCBUIPanel::Update` 同 this 调用）；`0x56CC` 1 员属 `PropUI`（29,056B，访问者 `0x46d2be` 位于 `PropUI::InitUI`）。15+4+3+1=23。

结论（#24 §0、§5.1，B 级定谳）：**ctor 不越界，`binary_size` 应为 20,568（0x5058）；22,224 是注解 89 员末端算术值 + 三个别的类混装，不是本类尺寸；这不是 ctor 写错，也不是 CCBRoleState 尺寸偏小。**

### 11.2 ⑤ 的推荐变化（不是拍板）

原文 §0/§5 的推荐是“先只读取界，暂保 22,224，不要再用 20,568 试错”。增量改为：

> **A 级证据支持 `binary_size=20,568`；ctor 写入终点与分配逐字节相等；22,224 无分配支撑，23 个尾员分属三类，不应留在 CCBRoleState。**

但这只是推荐更新，**不是 Human 已拍板**。待拍板问题改为：

> **是否按 20,568 重铸 CCBRoleState，并把 23 个尾部混装员按三类处理？**

| 选项 | 动作 | 影响与风险 |
|---|---|---|
| **A. 按 20,568 重铸（推荐）** | 改 `binary_size=20,568`；把 23 员移出 `known_members`：15 员迁往 20,644B 类（需先命名，另卡；命名前先记录挂账，不静默丢）、4 员幻影删除、3 员迁 `CCBUIPanel`、1 员迁 `PropUI`；再跑 `audit_type_layout --only CCBRoleState`、`check_annotations`、`census_struct_holes` | 与唯一分配 + ctor 终点两条 A 级闭合一致；census 洞从 6,483B/27 至少减 1,568B（预期 ≤4,915B）；需在无并发 loop 窗口跑 apply→export→codegen→probe→match；`0x55C8..0x55D0` 删除前要确认不是别处仍在用的别名 |
| **B. 暂保 22,224 挂账** | 只改 ctor 归属说明，不改 `binary_size` | 不动门禁，但 census 继续按 22,224/89 员记 6,483B/27 假洞；22,224 已被证无分配支撑，下一张卡仍要重来 |
| **C. 先补 20,644B 类命名再重铸（两步）** | 先只读取证 20,644B 类的身份与 15 员归属，命名后再缩 `binary_size` | 语义损失风险最低但最慢；4 员幻影、3 员 CCBUIPanel、1 员 PropUI 仍需在第二步一并处置，不能绕过尺寸修正 |

### 11.3 三态（必须带进执行）

- **#24 已验收**：A 级分配/写界与 B 级跨类归属可用；报告是 `docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md`（246 行）。
- **注解未改**：当场核 `data/annotations/structs/CCBRoleState.json` 工作树与 `HEAD` 都是 `binary_size=22,224`、89 员，`git status` 该路径为空，mtime `2026-11-26 01:00:12`；本卡没有未提交的注解改动，也没有把 20,568 写进去。IDB 的 size 是注解投影，不作独立尺寸证据。
- **census 仍是旧账**：`data/status/struct_holes_20261125.json`（mtime 2026-11-27 00:32:47）中 `CCBRoleState` 仍为 `size=22,224 / members=89 / hole_bytes=6,483 / 27 段`；落地后必须重跑 census 才能得新账，不能拿当前 6,483B 当重铸后结果。

### 11.4 影响面（只写，不改）

- `binary_size` 22,224 → 20,568，直接改变该类的洞普查口径。
- 23 个尾员按 #24 §4.1 分三类：15 员（`0x5060..0x50A0`）归 20,644B 类、4 员（`0x55C8..0x55D0`）为幻影、3 员（`0x5654..0x565C`）归 CCBUIPanel、1 员（`0x56CC`）归 PropUI；**删除而非原地搬家**，且不能在未命名/未裁决时静默丢语义。
- 当前 27 段洞中 `0x5058` 之后的 `[0x5058,0x5060)` 8B、`[0x506C,0x5070)` 4B、`[0x5084,0x5088)` 4B、`[0x50A4,0x55C8)` 1,316B、`[0x55D4,0x5654)` 128B、`[0x5660,0x56CC)` 108B，合计 **1,568B** 属类外空间，重铸后应消失。
- 第一遍 loop 把 20,568 回退为 22,224，是注解自洽性（成员末端越界）拦截，不是二进制要求；`ClearAndSetGP` 的 20,644 是另一个类对象，不能挂回 CCBRoleState。
- R4/R5 不直接受影响：`CCBAI/CCBControl/CCBEditor/CCBStageRole/CCBSystem/CCBAttackSequen` 只存 `CCBRoleState *`，尺寸变化不改变这些指针布局。

### 11.5 与原文的关系

原文 §0 的 ⑤ 行、§5 的并列数、“先只读取界/暂保 22,224”推荐保留作历史；凡与本节冲突处，**以本节为准**。本节不重写 §0–§10，也不把 #24 的结论写成已落地。

## 12. 2026-11-27 取证增量（R6③，#27 已验收）

**决策问题**：CCBStage 的本 exe 真尺寸是 672,040 还是 673,968；673,988 是什么；是否按 672,040 重铸，并把 20 个尾部成员迁出。

### 12.1 A 级判别链（逐条带指令/VA）

| 数字 | 性质 | 判别链 | 等级 |
|---|---|---|---|
| **672,040 (0xA4128)** | **本 exe 的 CCBStage 真尺寸** | `0x5233BE push 0xa4128` 全库唯一（#27 C1）→ `0x5233CD call 0x55353B`（operator new）→ `0x5233E7 call 0x51D710`（`??0CCBStage`）。ctor 尾部 `0x51DD33 lea ecx,[esi+0xa3bd0]` + `0x51DD3E call 0x4a12f0`（UIRoleDialog，0x558）+ `0x51DD43 mov DWORD PTR [esi],0x5705d0`；`0xA3BD0 + 0x558 = 0xA4128`，与分配立即数逐字节相等。第二入口 `0x51DDA0` 同界、同 vptr。 | **A** |
| 673,968 (0xA48B0) | **另一个对象**的真实尺寸；类名、vtable 归属未定 | `0x512851 push 0xa48b0` → `0x512856 call 0x55353B` → `0x512874 call 0x4FB9A0`（IDB 名 `InitFromDescriptor@CCBStage`）。该对象 offset 0 写描述符指针、不是 vptr；`0xAC0` 起 256 槽、步长 `0xA48` 清零，末槽起点 `0xA4878`、写 44B 到 `0xA48A4`，距分配余 12B。 | A（该对象尺寸）/ B（归属） |
| 673,988 (0xA48C4) | **注解派生值，无二进制支撑** | `CCBStage.json binary_size`，末员 `m_dwAniFlagOver@0xA48C0` 末端 `0xA48C4`；恰为 `673,968 + 20B` 幻影尾员。没有 673,988 的分配点；IDB/census 都只是继承注解，不是独立证据。 | B |

补充两点，避免下一轮再被旧记录带偏：
- `probe_heap_alloc_census` 该行把 A 的 store 记作 `[esi+0x6C8]`；反汇编实际是 `0x5233F9 mov [esi+0x6CC],eax`。`0x5233C7 mov [esi+0x6C8],eax` 在 new 之前，存的是上一个对象 `gbBinkVideo`。以反汇编为准（#27 §2.1）。
- 673,968 的对象不是 CCBStage：它的 offset 0 不是 vptr，`0x4FB9A0` 的 `[this]` 写描述符；IDB 把 `InitFromDescriptor@CCBStage` 挂在 CCBStage 名下是初始化器归属错误（#27 §2.4、§4.2 G2）。

### 12.2 ③ 的推荐变化（不是拍板）

原文 §0 的③行与 §3 的“三数并列、先辨两个 new 站点、暂保 673,988”保留作历史。按 #27 的 A 级链，现应改为：

> **672,040 是本 exe 的 CCBStage 真尺寸；673,988 不再作为候选；673,968 是另一个对象，需先正名，不能直接并回 CCBStage。**

| 方案 | 动作 | 影响面 | 风险/前置 |
|---|---|---|---|
| A 重铸 + B 正名（推荐，但需先给 B 命名） | `CCBStage.binary_size=672040`；20 个尾部成员迁往 B；`m_dwAniFlagOver` 作废；`0x4FB9A0` 从 CCBStage.methods 移到 B | census 从 36B/2 降到 16B/1；IDB 随 apply/export 更新；`0x4FC7xx` 一带按 `+0xA48` 步进的方法跟随 B | 必须先给 B 正名并逐员复核；否则 20 员无处可挂，不能静默删 |
| B 暂保 673,988 挂账 | 不动注解 | 门禁不动；chimera 保留，census 继续按 36B/2 统计 | 下一轮还会重复“三数并列”；不解决成员混装 |
| C 先只做 B 正名/逐员取证，再决定重铸 | 只新增 B 的取证与命名，不改 CCBStage | 不动门禁；产出 B 的类名、vtable、20 员归属 | 周期长，但可避免“先缩尺寸、成员无家可归” |

**需要 Human 拍板**：选 A（按 672,040 重铸 CCBStage，并授权 B 正名卡迁移 20 员）、B（暂保 673,988 挂账），还是 C（先给 B 正名/逐员取证，再重铸）？

### 12.3 三态（必须带进执行）

- #27 已验收（白砚）；本文只摘其 A 级结论，不新增推断。
- 工作树 `data/annotations/structs/CCBStage.json` 本次实读仍是 `binary_size=673,988`、20 员、`bases=1`；**未落地**。
- `data/status/struct_holes_20261125.json` 本次实读仍是 `CCBStage size=673,988 / members=20 / hole_bytes=36 / holes=[[0x48,0x58,16],[0xa48ac,0xa48c0,20]]`；落地后必须重跑 `apply→export→census` 才能得到“洞只剩 16B”的新账。
- `asm/pal3/ida_structs.json` 的 `CCBStage.size` 是注解导出值，不是独立证据。

### 12.4 影响面（只写，不改）

- `binary_size` 673,988 → 672,040；20 个成员迁往 B，`m_dwAniFlagOver@0xA48C0` 落在两个对象之外，作废。
- census 当前 `[0x48,0x58)=16` 保留；`[0xA48AC,0xA48C0)=20` 中 `[0xA48AC,0xA48B0)` 是 B 的尾对齐、`[0xA48B0,0xA48C0)` 落在 B 之外，都不再属于 CCBStage；预期 CCBStage 洞 ≤16B。
- 下游 `CCBStageScene 1012`、`CCBStageRole 6848`、`CCBStageCam 6272`、`CCBStageEffect 25488`、`CCBStageShadow 1556` 是独立类，不受影响；`0x4FC7xx` 一带按 `+0xA48` 步进的方法跟随 B 走，需与 B 的卡一起迁移。
- IDB 尺寸会经 apply→export 跟随注解更新，不手改。

### 12.5 与原文的关系

原文 §0 的③行、§3 的三数并列与“暂保 673,988”推荐保留作历史；凡与本节冲突处，**以本节为准**。本节不重写 §0–§11，也不把 #27 的结论写成已落地。

## 13. 2026-11-27 取证增量（R6②，#29 已验收）

**决策问题**：C2DSpark 的真尺寸是 22,640 还是 24,688；`tagSpark` 元素是 44B 还是 48B；是否按 22,640/44 重铸。

### 13.1 A 级判别链（逐条带指令/VA）

| 结论 | 判别链 | 等级 |
|---|---|---|
| **`sizeof(C2DSpark)=0x5870=22,640`** | `0x512AE1 push 0x5870` 全库唯一 → `0x512AF0 call 0x55353B`（operator new）→ `0x512B1B call 0x4D5AB0`（`??0C2DSpark`）。ctor `0x4D5AC4 mov ecx,0x161C; 0x4D5ADB rep stos`（`0x161C×4=22,640`），最大写 `0x4D5ACB/0x4D5D77 [esi+0x586C]`，+4 终点 `0x5870`。分配立即数、清零常量、最大写终点三链逐字节相等。 | **A** |
| **`sizeof(tagSpark)=0x2C=44`，元素数 512** | 三处独立步长均为 `0x2C`：`CreateSingle 0x4D5EC5/0x4D5ECE`、`CreateStars 0x4D61A0/0x4D61AB`、`Render 0x4D62B3/0x4D6350`；元素数 `0x200=512`（`0x4D5ED1/0x4D61A3`）；`CreateSingle 0x4D5EEA mov ecx,0xb; rep movs` 整元素拷贝 11 dword = 44B。`512×44=22,528=0x5800`，与尾部 19 员起点逐字节对齐。 | **A** |
| 注解 24,688/48 是派生量 | `C2DSpark_tagSpark.json` note 自述“Size=48 from array stride (24576/512)”；24,576 来自注解自己的尾部起点 `0x6000`，比实测多 `0x800=512×4`。`push 0x6000`、`push 0x6070` 在反汇编缓存零命中；PDB（PAL3A）24,688/48 只作参考。 | A（派生关系） |

闭合算术：`512×44=22,528=0x5800`；尾部 19 员从 `0x5800` 起；`m_Quad@0x5848 + 0x28 = 0x5870`；`0x5800 + 112 = 0x5870`。注解尾部同样是 112B，但整体高 `0x800`，正好是“元素 48 而非 44”乘 512（#29 §3.4–§3.6）。

### 13.2 ② 的推荐变化（不是拍板）

原文 §0 的②行与 §2 的“48B 待判、暂保 24,688、推荐先观测步进”保留作历史。按 #29 的 A 级链，现应改为：

> **A 级支持 `C2DSpark=22,640`、`tagSpark=44`；48/24,688 是注解自身的循环派生量，不再作为候选。**

| 方案 | 动作 | 影响面 | 风险/前置 |
|---|---|---|---|
| A 按 22,640/44 重铸（推荐） | `C2DSpark.binary_size 24,688→22,640`；元素尺寸 `48→44`；19 个尾员偏移整体 `−0x800`（`0x6000..0x6048 → 0x5800..0x5848`） | 门禁触发；census 新增 C2DSpark 记录；按 48 计算的索引全部要改 | 顺序不可颠倒：先改元素类型/尺寸，再改尾员偏移；`pRenderEffect@0x2C` 是伪成员，重铸时必须处理，不能把 44B 外的成员留在数组元素里 |
| B 暂保 24,688/48 挂账 | 不动注解 | 门禁不动；A 级冲突保留，48B 仍是反推值 | 下一轮还会把“注解派生”当“待观测” |
| C 先补 D-1 元素语义 / D-2 方法名，再重铸 | 只做取证/正名，不改尺寸 | 不动门禁；D-1/D-2 缺口先闭合 | 周期长；但能避免重铸后元素字段名与 44B 布局错配 |

**需要 Human 拍板**：选 A（按 22,640/44 重铸 C2DSpark，先元素类型、后尾员偏移）、B（暂保 24,688/48 挂账），还是 C（先补 D-1/D-2 再重铸）？

### 13.3 三态（必须带进执行）

- #29 已验收（白砚）；本文只摘其 A 级结论，不新增推断。
- 工作树 `data/annotations/structs/C2DSpark.json` 本次实读仍是 `binary_size=24,688`、20 员；`C2DSpark_tagSpark.json` 仍是 `binary_size=48`、12 员；**均未落地**。
- `data/status/struct_holes_20261125.json` 本次实读 200 类中没有 C2DSpark/C2DSpark_tagSpark 条目；重铸后应新增一条 0 洞记录（该类不存在 `0x48..0x58` 那类空隙）。
- `data/pdb/pdb_export.json` 的 24,688/48 来自 PAL3A，只能作参考，不能压过本 exe 的三条 A 级链。

### 13.4 影响面（只写，不改）

- `binary_size 24,688→22,640`；`m_Spark` 仍为 `C2DSpark_tagSpark[512]`，元素尺寸 48→44，数组占 22,528B。
- 19 个尾员偏移整体 `−0x800`：`0x6000..0x6048 → 0x5800..0x5848`；`m_Quad` 到 `0x5848+40=0x5870` 闭合。
- 任何按 48 计算 `m_Spark` 索引的代码都会错位；落地顺序必须先改元素类型、再改尾员偏移。
- D-1（元素字段语义）：12 员中仅 `+0x00/+0x04/+0x18/+0x20/+0x28/+0x29` 有使用证据，`+0x08/+0x0C/+0x10/+0x14/+0x1C` 与两个尾字节未定；`pRenderEffect@0x2C` 是伪成员。D-2（方法名）：`0x4D61C0`（现名 `DestroyAll`）实际是绘制循环，`0x4D6380`（现名 `Render`）实际是鼠标轨迹更新。两项只列为缺口，本卡不改名、不臆造语义。
- 不触 R4/R5：C2DSpark 与 ScreenEffectMgr/SaleUI 无包含关系；但共享树的 loop 窗口仍需独占。

### 13.5 与原文的关系

原文 §0 的②行、§2 的并列数、“暂保 24,688 / 推荐先观测”保留作历史；凡与本节冲突处，**以本节为准**。本节不重写 §0–§12，也不把 #29 的结论写成已落地。
