# R6 挂账批：六项账目与可认领切分（只读盘点）

- 盘点人：观澜（业务视角，Task #11，`tsk_01M8BZQJP90X6JPTXFYVQQ`）
- 盘点时间：2026-11-26 21:1x–21:3x（Asia/Shanghai）
- 性质：**只读账目整理，不做裁决**。本文只回答「已知什么、卡在哪、证据在哪、还缺什么、能不能独立成卡」，不给出尺寸/归属的最终结论。
- 写面：仅本文件（`docs/audit/`）。未改 annotation、未改基线、未改生成树、未跑管线。
- 六项来源：`docs/specs/2026-11-26-struct-hole-filling-campaign-design.md:36`、`docs/knowledge/struct_hole_fill_campaign_20261126.md:230`、`docs/handoff/2026-11-26-struct-hole-campaign-handoff.md:91`。

## 0. 摘要

六项挂账全部**有账可查**，但成熟度分两档：

- **数字已闭合、只差裁决**（3 项）：① UITitle_JDHY/Note_Item、④ PropUI 差 164、⑤ CCBRoleState ctor 写界——两/三个尺寸都有明确出处，缺的是「哪个是真布局」的判据。
- **有尺寸、缺结构观测**（2 项）：② C2DSpark/tagSpark（48B 是反推值）、③ CCBStage 三数字（三个数都在，缺两态分辨）。
- **身份已定谳、剩落地**（1 项）：⑥ 402,824 类 Y——twin 裁决已写「类 Y = CCCTData」，但「待名」的旧措辞与 `CCCTData.json` 的 chimera 状态（尺寸仍是类 X 的 430,256、成员 0）同时存在，建议把该卡改定义成「CCCTData.json 重铸」，不要从零命名。

| # | 挂账项 | 证据等级 | 建议 | 优先级 | owner 技能面 | 关键依赖 |
|---|---|---|---|---|---|---|
| ① | UITitle_JDHY / Note_Item 双布局 | A（尺寸矛盾）/ 缺口：布局判据 | 独立成卡 | P1 | coder | R2 七模块指针类型化（+0x2AFD0） |
| ② | C2DSpark / tagSpark 重验 | B | 独立小卡 | P1 | coder | 无 |
| ③ | CCBStage 三数字 | B（两数字 A 级在表、第三数字无分配行） | 独立成卡 | P1 | coder | 无 |
| ④ | PropUI 差 164 | B | 独立小卡或并入金表第二批 | P2 | coder | 无 |
| ⑤ | CCBRoleState ctor 写界 | B（两侧 A 级证据互斥） | 独立成卡 | **P0** | coder | 触发 §7 红线「binary_size 修正必过 loop 门禁」 |
| ⑥ | 堆类 402,824 待名 | A（身份定谳）/ 缺口：命名未落地、注解未重铸 | 独立成卡（改定义为「CCCTData.json 重铸」） | **P0** | coder | EquipUI 七槽类型化、CCBCamControl 域冲突 |

**建议开工顺序**：⑥ → ⑤ → ① → ③ → ② → ④。理由：⑥/⑤ 都卡在「注解与金表互斥」，且会反过来影响其它类的域边界；① 影响 R2 指针类型化；③②④ 是单类收尾，可并行。

**与在跑卡的关系**：本卡写面 `docs/audit/` 唯一，与 #5/#7/#9 无文件重叠；但 #9（SaleUI）若跑 loop，会刷新 `probe_census.json` / `struct_holes_20261125.json`，本文引用的产物时点需在执行时重取（见 §7-6）。

## 1. 账目来源与数据时点

| 账目/产物 | 路径 | 时点 | 用途 |
|---|---|---|---|
| 金表（编译器 sizeof 首批对账） | `data/status/goldtable_size_corrections_20261126.md` | mtime 2026-11-26 01:27:27 | ①②③④⑤ 的一手差异描述 |
| 堆分配普查（33 笔 ≥0x4000） | `data/status/probe_heap_alloc_census_20261126.json` | 提交 `1a52354e2`（W2 重建①），本次读取未改动 | ①②③④⑤⑥ 的 A 级尺寸行 |
| 双堆类终局裁决 | `data/status/ccbcamcontrol_twin_adjudication_20261126.md` | mtime 2026-11-26 08:59:33 | ⑥ 的身份与手术清单 |
| 战役设计 spec（R6 行） | `docs/specs/2026-11-26-struct-hole-filling-campaign-design.md:36` | — | 六项范围与堆类候选 |
| knowledge 汇总 | `docs/knowledge/struct_hole_fill_campaign_20261126.md:212-213/230` | — | 残余洞表与 R6 清单 |
| 交接文档 §5 | `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md:91`（另 :98 有 JDHY 尺寸矛盾） | 2026-11-26 19:50 提交 + 修正注 | 轮次归属 |
| 裁定队列 | `data/status/adjudication_queue.json` | `generated_at=2026-11-26 20:59:01`，`queue={}` | **空队列**：六项均未入队，无现成待裁条目 |
| 证据台账 | `data/status/evidence_ledger.json` | 8 条（ev_0003…ev_0008 等） | **六项无一有 ev 条目**；最近的是 ScreenEffectMgr/MagicUI；且 `ev_0006` 明确「头区成员不得据现有注解命名，需 IDA UDT readback」 |

金表判据（原文 `goldtable_size_corrections_20261126.md:6`）：`push SIZE; call ??2@YAPAXI@Z; mov ecx,eax; call ??0ClassName@@` —— 构造 mangle + 尺寸字面量 = 编译器 sizeof A 级。

## 2. ① UITitle_JDHY / Note_Item 双布局仲裁

**现状一句话**：`UITitle_JDHY` 注解 377,700、金表分配 290,488、`Note_Item[99]` 按注解尺寸排到 352,440、按槽跨度反推每元素 3,728，四个数互不相容；卡点是「99 元素 × 哪个 Note_Item 尺寸」，以及是否另有一套 `Role[50]` 布局。

### 证据指针

| 指针 | 内容 |
|---|---|
| `data/annotations/structs/UITitle_JDHY.json` | `binary_size=377700`，`base_size=72`，`bases=[UIFrameWnd@0]`，28 员全 `unverified`；`0x634 m_NoteItem = Note_Item[99]`；下一员 `0x5a7e4 m_Title_JDHY UIStatic` |
| `data/annotations/structs/Note_Item.json` | `binary_size=3560`，12 员（0x0 m_ItemRc tagRECT … 0x9c0 m_NoteLv UIStatic[5]） |
| 算术（本文计算） | 槽跨度 `0x5a7e4-0x634=369,072`；`369,072/99=3,728.0`；`99×3560=352,440`；金表 290,488 比分项少 `61,952`，比槽跨度少 `78,584` |
| `data/status/probe_heap_alloc_census_20261126.json` | `{"size":290488,"ctor":"?DestroyPages@UITitle_JDHY@@QAEHXZ","store":"esi+0x2AFD0","caller":"?Init@EquipUI@@QAEXXZ","site":"0x4a46c4"}`（`0x46EB8=290488`） |
| `data/status/goldtable_size_corrections_20261126.md:18-21` | 「UITitle_JDHY 377700→290488（push 0x46EB8）：m_NoteItem@0x634（Note_Item[99]）末端 352440 > 290488 越界——与挂账案「Role[50] vs Note_Item[99] 双布局仲裁」纠缠」，缓修 |
| `asm/pal3/ida_structs.json:109908` | EquipUI `+0x2AFD0` 槽 source 详注：pointee 290,488 = 金表分配尺寸但 `UITitle_JDHY.json` 377,700 不合；ctor 名义 `DestroyPages` 系误名；三写（InitUI 清零 0x4a20ef / Init 构造 0x4a46f2 / HideAll 再清零 0x4a66b1）；9 读点；callee 簇 PopulateContent/SaveData |
| `docs/specs/2026-11-26-r2-implementation-plan.md:78/96` | 该槽落 `void*`+note（透明指针先例，禁预判 JDHY 归属）；:96 列「UITitle_JDHY 尺寸仲裁（Note_Item 双布局，挂账批）」 |
| `docs/knowledge/struct_hole_fill_campaign_20261126.md:212` | UITitle_JDHY 现洞 19,396B / 14 洞 |

### 等级与缺口

- 等级：**A（尺寸矛盾本身）**——金表 push 字面量 + 成员末端算术都硬；但**「哪个是真布局」无任何产物证据**。
- 缺什么才能裁决：
  1. `Note_Item` 的 IDA UDT readback / 大小实测（3560 vs 3728 谁对；若 3,728 则哪 168B 被注解漏掉）；
  2. 语料里 `PopulateContent`/`SaveData`（或 ctor）对 `m_NoteItem` 的 stride×count 乘法链——须见 99 或 50 的字面量与步进；
  3. `0x4a46c4` 分配后 `esi+0x2AFD0` 的写入链确认 pointee 是 JDHY 还是 Note_Item 数组本身（ctor 名义已判误名）。

### 切分建议

- **独立成卡（coder，P1）**：一卡只做「JDHY/Note_Item 布局裁决」，产出=两文件修正 + loop 门禁通过；不与「全库 538 员」「RoleStatePanel 升级候选」混做。
- 前置关系：R6 先出裁决，再做 `+0x2AFD0` 的类型化（当前 `void*` 是正确的临时态）。

## 3. ② C2DSpark / tagSpark 重验

**现状一句话**：`C2DSpark` 注解 24,688、金表 ctor 分配 22,640，而 `m_Spark=C2DSpark_tagSpark[512]` 已占 24,576 —— 超金表 1,936；`tagSpark=48B` 本身是从 `24,576/512` 反推的，不是观测值。

### 证据指针

| 指针 | 内容 |
|---|---|
| `data/annotations/structs/C2DSpark.json` | `binary_size=24688`；`0x0 m_Spark = C2DSpark_tagSpark[512]`；0x6000 起 m_fDisplayWidth/m_fDisplayHeight/m_nCurrentSpark/…（全 unverified） |
| `data/annotations/structs/C2DSpark_tagSpark.json` | `binary_size=48`；note 原文「Size=48 from array stride (24576/512)」；12 员 0x0 pTexture1…0x2c pRenderEffect（pTextureWrap2/4、pRenderEffect 标 int 待指针对齐） |
| `data/status/probe_heap_alloc_census_20261126.json` | `{"size":22640,"ctor":"??0C2DSpark@@QAE@HH@Z","site":"0x512af0"}`（`0x5870=22640`） |
| `data/status/goldtable_size_corrections_20261126.md:21-24` | 「C2DSpark 24688→22640（??0C2DSpark + push 0x5870）：m_Spark@0x0 末端 24576 > 22640 —— tagSpark 型尺寸或元素数须重验」 |
| `data/annotations/CHANGE_LOG.md:3933/3945` | 48B/56B「从 m_Spark array stride 推导」；`:3945`「[A] C2DSpark: m_Spark[512] at +0, next member at +24576 → 24576/512=48B per tagSpark」——**反推值**，本次重验即针对它 |
| PDB | `?CreateSingle@C2DSpark@@AAE_NPAUtagSpark@1@@Z`（`data/pdb/pdb_export.json:24580-24595`，this_type=C2DSpark*）、`?CreateMore@C2DSpark@@QAEXHHUgbColorQuad@@@Z`（:44260）、`??1C2DSpark@@QAE@XZ`（:47679） |
| 语料（9 个） | `asm/pal3/decomp/C2DSpark_{C2DSparkint_int_004d5ab0, CreateMoreint_int_int_int_004d6050, CreateSinglevoid_const_004d5ec0, CreateStarsvoid_004d61a0, CreateTrackint_int_004d5f20, DestroyAllvoid_004d61c0, Renderfloat_004d6380, SetEnableMouseTrackint_int_004d5f40, ~C2DSparkvoid_004d5dc0}.json` |

### 等级与缺口

- 等级：**B**——金表尺寸 A 级在档，但 `tagSpark` 结构本身没有直接观测（48B 是推算）。
- 缺什么：`CreateSingle`（0x4d5ec0）体内的数组字面量/步进（若 48B×512 则 24,576，金表只给 22,640；若 471×48=22,608、若 512×44=22,528，均不等）；或 `Render` 里的 512 循环上界。需要 objdump/IDA 的步进常数，不是在注解里再算一遍。

### 切分建议

- **独立小卡（coder，P1）**：范围仅 `C2DSpark.json` + `C2DSpark_tagSpark.json`；产出=元素数或 tagSpark 尺寸二选一定谳 + loop 门禁。与在跑卡无交集。

## 4. ③ CCBStage 三数字

**现状一句话**：三个尺寸都在——ctor `??0CCBStage` 分配 0xA4128=672,040、`InitFromDescriptor@CCBStage` 分配 0xA48B0=673,968、注解 673,988（且成员末端 `m_dwAniFlagOver@0xa48c0+4` 恰好 673,988 顶格）；卡点是这三个数是「两态（池/派生）还是注解多算」。

### 证据指针

| 指针 | 内容 |
|---|---|
| `data/annotations/structs/CCBStage.json` | `binary_size=673988`，`base_size=72`，`bases=[UIListBox@0]`，20 员；末员 `0xa48c0 m_dwAniFlagOver unsigned int`（末端 0xa48c4=673,988） |
| `data/status/probe_heap_alloc_census_20261126.json` | `{"size":672040,"ctor":"??0CCBStage@@QAE@XZ","site":"0x5233cd"}` 与 `{"size":673968,"ctor":"?InitFromDescriptor@CCBStage@@QAEHH@Z","site":"0x512856"}`（0xA4128 / 0xA48B0） |
| `data/status/goldtable_size_corrections_20261126.md:23-25` | 「CCBStage 三数字：ctor ??0CCBStage new 0xA4128=672040 / InitFromDescriptor new 0xA48B0=673968 / 注解 673988 —— 两分配两态分辨（池?派生?）独立成役」 |
| 算术（本文） | 673,968−673,988 = **−20B**：若 0xA48B0 那个对象按现注解布局，末端 20B 越界；672,040 与注解差 1,948B |

### 等级与缺口

- 等级：**B**——两笔分配是 A 级（census 有行、mangle 清楚），注解第三数无独立分配行；「三数对应几个对象」无证据。
- 缺什么：
  1. `0x5233cd` 与 `0x512856` 两个 new 站点的**接收者/返回值去向**（同一 this 两次 new？还是工厂 vs 成员构造？）；
  2. `0x512856` 是否确为 `CCBStage`（mangle 是 `InitFromDescriptor`，被 new 的是**另一个类**也完全可能——这正是「两态」说的来源）；
  3. 若采信 673,968，`m_dwAniFlagOver` 是否真在类内（需 ctor 写偏移上界）。

### 切分建议

- **独立成卡（coder，P1）**：三站点 objdump + 接收者分析一卡做完；产出=「一对象三数」或「两对象各自数」的定性，附 loop 门禁（若动 binary_size）。与 #9 SaleUI、#7/#8 裁决无交集。

## 5. ④ PropUI 差 164

**现状一句话**：注解 29,056、金表 `0x70DC=28,892` 两处（都在 `InitUI@PropUI`）——差 164；且注解成员末端 0x7120=28,960 **大于** 28,892，若采信金表则末端越界 68B。

### 证据指针

| 指针 | 内容 |
|---|---|
| `data/annotations/structs/PropUI.json` | `binary_size=29056`，95 员，`bases=[UIFrameWnd@0]`；末员 `0x7110 mb_OKRc tagRECT`（末端 0x7120=28,960） |
| `data/status/probe_heap_alloc_census_20261126.json` | 两笔 `{"size":28892,"ctor":"?InitUI@PropUI@@QAEHXZ"}`，site `0x45975e` / `0x523431`（`0x70DC`） |
| `data/status/goldtable_size_corrections_20261126.md:36` | 「0x70DC=28892 ×2（InitUI@PropUI——PropUI 注解 29056 差 164 待核）」，列在「待名新类」清单 |
| 算术（本文） | 29,056−28,892 = **164** ✓；28,960（成员末端）−28,892 = **+68**（越界） |

### 等级与缺口

- 等级：**B**——两数字都可复现，缺「谁是 sizeof」的判据。
- 缺什么：两处 `InitUI` new 的是否**同一类**（若其中一处是派生/子对象，则 28,892 不是 PropUI 的 sizeof）；以及 PropUI 是否有 28,960 之后的派生成员（当前注解到 0x7110 为止，可能少 96B 尾）。需 ctor/InitUI 的 `mov ecx` 后 call 的 mangle 二次确认。

### 切分建议

- **独立小卡（coder，P2）**，或并入「金表第二批」批量对账（因为同批还有 0x56630/0x29CEC/0x207F0/0x1E56C×2 等「分配有尺寸无注解」的类）。与在跑卡无交集。

## 6. ⑤ CCBRoleState ctor 写界

**现状一句话**：ctor `??0CCBRoleState` 分配 0x5058=20,568，而注解成员已写到 `m_BattleFlags@0x56cc`（末端 22,224，恰好等于现 binary_size）；两侧都有 A 级证据、互斥，且第一遍 loop 已把 20,568 回退为 22,224。

### 证据指针

| 指针 | 内容 |
|---|---|
| `data/annotations/structs/CCBRoleState.json` | `binary_size=22224`，89 员，`bases=[UIListBox@0]`；`0x56cc m_BattleFlags int`（末端 0x56d0=22,224，顶格）；0x5050 起还有 m_bVideoPlayed/m_nVideoState/m_nCurrentTaskID/m_nEffCurA...（0x55c8..0x56cc 段） |
| `data/status/probe_heap_alloc_census_20261126.json` | `{"size":20568,"ctor":"??0CCBRoleState@@QAE@XZ","site":"0x44c5f8"}`；`{"size":20644,"ctor":"?ClearAndSetGP@CCBRoleState@@QAEHH@XZ","site":"0x512730"}`（`0x5058` / `0x50A4`） |
| `data/status/goldtable_size_corrections_20261126.md:15` | 落地表「CCBRoleState 22224→20568（??0CCBRoleState + push 0x5058）；另 ClearAndSetGP 分配 0x50A4=20644 待辨」 |
| `data/status/goldtable_size_corrections_20261126.md:44-47` | 「第一遍 loop 拦截: m_BattleFlags@0x56CC 末端 22224 越界 → 回退 20568→22224（成员背书保守胜出），挂构造字面量冲突案（??0CCBRoleState new 0x5058 vs 成员证据，待 ctor 写界取证裁定是 ctor 误名还是成员越界）」 |

### 等级与缺口

- 等级：**B**——两侧 A 级但互斥（0x5058 字面量 vs 成员写至 0x56cc）。
- 缺什么才能裁决：
  1. `0x44c5f8` 站点 `new 0x5058` 后 `mov ecx,eax; call ??0CCBRoleState` 的完整调用，以及**该 ctor 体的写偏移上界**（若只写到 0x5058，则 0x5058 之后成员不在该类；若写到 0x56cc，则 ctor 是另一个类/误名）；
  2. `0x512730` 的 `ClearAndSetGP` 分配 20,644 是 self-new 还是工厂（同一 this 二次分配？）；
  3. 0x55c8..0x56cc 段成员的 source 证据链（现均为 unverified 还是有实写点）。

### 切分建议

- **独立成卡（coder，P0）**：这是「成员越界 vs ctor 误名」的判据问题，误判会再触发交接文档 §7 红线「binary_size 修正必过 loop 门禁」（本次已实证一次回退）。与在跑卡无冲突。

## 7. ⑥ 堆类 402,824 待名

**现状一句话**：`402,824=0x62588` 的分配（site `0x4a4660`，ctor `CCCTData_6F10@0x4a6f10`，实例 `EquipUI+0x2AFC8`）在 spec/handoff 里还写「类 Y 待名」，但 twin 裁决已写「类 Y = CCCTData」；同时 `CCCTData.json` 仍是 chimera（`binary_size=430256`＝类 X 尺寸、`known_members=0`）——**「待名」其实是「重铸未做」**。

### 证据指针

| 指针 | 内容 |
|---|---|
| `docs/specs/2026-11-26-struct-hole-filling-campaign-design.md:36` | 「430256=X 已裁（金表 site 0x4fbc2e+ctor 链）；402824=类Y（site 0x4a4660）待名；425136 候选**除名**——0x68FB0=430,000≠425,136；继承边界候选=430,000，须 CCBCamControl ctor 基类直调证据（0x5052e0 已解码无显式基类调用[内联可能]，弱证据待另证）」 |
| `data/status/probe_heap_alloc_census_20261126.json` | `{"size":402824,"ctor":"?CCCTData_6F10@CCCTData@@QAEXXZ","store":"esi+0x2AFC8","caller":"?Init@EquipUI@@QAEXXZ","site":"0x4a4660"}`（`0x62588`）；另一笔 `{"size":430256,...,"site":"0x4fbc2e"}` |
| `data/status/ccbcamcontrol_twin_adjudication_20261126.md:145` | 终局结构表：类 X `0x690B0=430256` / 类 Y `0x62588=402824` |
| 同上 `:205-209` | 「**类 Y = CCCTData**（0x62588=402824）：ctor=??0CCCTData（PAL3 0x4a6f10，UIListBox 派生——任务编辑对话框数据类），实例=EquipUI+0x2AFC8」；「判别证据：池方法 disp 0x68FD0=425424 > 402824 ⇒ 池方法属类 X 非 Y」；「**现注解 chimera 实锤**：CCCTData.json binary_size=430256(=X 的尺寸!)+成员池模型(=X 的域)」 |
| 同上 `:215/:221` | 手术清单 1「CCCTData.json 重铸：binary_size 0x62588=402824、方法表=15 PDB API、池/表成员重验」；5「类名定谳收官：类 Y 在 EquipUI+0x2AFC8 的完整证据链落 globals」 |
| `data/annotations/structs/CCCTData.json`（实测，mtime 2026-11-26 09:51:40） | `binary_size=430256`，`known_members=0`，`bases=None`，`note` 空 ⇒ chimera 仍在 |
| `docs/specs/2026-11-26-r2-implementation-plan.md:78/95` | `+0x2AFC8`（402,824 类 Y）落 `void*`+note；「171244/353840/402824 三未名类的类名定谳（R6/命名战役）」 |
| `docs/specs/2026-11-26-r5-magicui-identity-verdict.md:80` | 表行「（0x2afc8）| 0x2afc8 | 0x62588 = 402,824 | 0x4a6f10 | —」 |

### 等级与缺口

- 等级：**A（身份定谳）/ 缺口：命名与注解落地**。twin 裁决的证据（ctor 地址、store、disp 判别）足以支持「类 Y=CCCTData」，但：「待名」措辞与之冲突；`CCCTData.json` 未按 402,824 重铸；census 里的 ctor 名 `CCCTData_6F10` 带地址后缀（疑似过渡形，命名铁律要求语义名）。
- 缺什么才落位：`CCCTData.json` 重铸（402,824 + 15 PDB API 方法表 + 池/表成员重验）+ `+0x2AFC8` 从 `void*` 升 `CCCTData*` + 类名/mangle 语义化（`CCCTData_6F10` 正名）+ loop 门禁。

### 切分建议

- **独立成卡（coder，P0）**，但**改定义**为「CCCTData.json 重铸（尺寸 402,824 / 方法表 / 池成员）」，而不是「从零命名 402,824」。理由：身份已有 A 级裁决，重命名式表述会让执行者再做一遍已完成的取证，且容易与 CCBCamControl（类 X）的域再次混装。与 #9 SaleUI、#7 MagicUI 无交集。

## 8. 六项共同的账目问题（不影响认领，但影响执行）

1. **六项都不在裁定队列**：`adjudication_queue.json` 为空（20:59:01），六项也未登记 ev 条目 ⇒ 按仓库纪律「引用结论必须带 ev id」，R6 每项裁决落地后应回填 `evidence_ledger`。
2. **goldtable 文档是唯一差异账本**：①②③④⑤ 的差异都只写在 `data/status/goldtable_size_corrections_20261126.md` 的挂账段，census 只给尺寸行，没有「差异原因」字段。
3. **口径不一致（需 R6 内统一）**：
   - `CCCTData_6F10`（census ctor 名）是地址后缀过渡形，与命名铁律「禁止地址后缀伪语义」冲突，正名属 ⑥；
   - 402,824 在 spec/handoff 写「待名」、twin 裁决写「=CCCTData」，两处需在 R6 卡内统一为后者；
   - ① 的「Role[50] vs Note_Item[99]」中 `Role[50]` 只在 goldtable 挂账段出现，**无其它产物指向**，执行时需先确认这是哪来的布局（若无出处，应作为假设显式标注）。
4. **回退先例**：⑤ 的 20,568→22,224 回退说明「成员末端」在 loop 门禁里是硬拦截；R6 任何 binary_size 修正都必须预留一次 loop。

## 9. 复现命令（只读；本卡未执行 loop）

```bash
# 金表尺寸行（A 级）
python3 -c "import json;d=json.load(open('data/status/probe_heap_alloc_census_20261126.json'));print([a for a in d['allocs'] if a['size'] in (290488,22640,672040,673968,28892,20568,20644,402824,430256)])"
# 注解尺寸与成员
python3 -c "import json;d=json.load(open('data/annotations/structs/Note_Item.json'));print(d['binary_size'],list(d['known_members'])[-3:])"
# 差异账本
sed -n '14,47p' data/status/goldtable_size_corrections_20261126.md
# 堆类身份
sed -n '140,150p;203,222p' data/status/ccbcamcontrol_twin_adjudication_20261126.md
```

## 10. 约束自证

- 写面：本卡只写 `docs/audit/2026-11-26-r6-backlog-dossier.md`。实测 `git status --short` 里与本卡相关的只有 `?? docs/audit/`（该目录另含 #4 的对账报告）；`M data/annotations/structs/{RoleStatePanel,SaleUI,UIFrameContainer}.json` 等改动均来自并发卡，非本卡。
- 未改 annotation/基线/生成树；未运行 `pipeline/cli.py loop`（本卡全程只读 `status` 级产物与注解 JSON）。
- 注：盘点期间（约 21:18 起）**有另一轮 loop 在跑**（`/tmp/r5_loop.log`，由并发卡启动，非本卡），`probe_census.json` 的 mtime 21:24 属于该轮；本文引用的六项尺寸来自**已提交**的 `probe_heap_alloc_census_20261126.json`（提交 `1a52354e2`）与 `goldtable_size_corrections_20261126.md`（mtime 01:27:27），不受该轮影响。若执行 R6 时金表已被重跑，须以那时产物为准重取。
