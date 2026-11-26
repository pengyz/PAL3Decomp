# R6 挂账四项事实清册

任务：#29 · tsk_01M8CBERX40CDC2A5AB8NN
日期：2026-11-27
性质：**只读事实清册**，为将来立项提供可验收的起点；不做裁决、不改 annotation、不跑管线。

## 0. 结论摘要

| 项 | 一句话现状 | 证据等级 | 值不值得开卡 |
|---|---|---|---|
| 堆类 402,824B | 分配/ctor/持有链全部可证；**类名未定**（表 0x56F29C 现被 Scene 声明为 SystemUI 表，而 census 名义是 CCCTData） | 事实 A / 命名 无 | 先开「表 0x56F29C 归属」小卡，再开重铸卡 |
| C2DSpark | 真 sizeof = **22,640**（ctor 写界 0x586C 恰顶到分配常量 0x5870）；注解 24,688 多 2,048；`m_Spark[512]` 元素应为 **44B** 而非 48B | A | **最值得**：证据齐、风险低、可直接开卡 |
| CCBStage 三数字 | 672,040 是写表 0x5705D0 的 ctor 分配；**673,968 不是 CCBStage**（CBSystem 里的零填 arena，不写表）；673,988 是注解算术值，且尾部 28B 落在 672,040 之外 | 672,040 A / 673,968 A（非同类）/ 673,988 算术 | 先做身份裁决，再谈尺寸 |
| CCBRoleState ctor 写界 | ctor 最后一次写 `[esi+5054h]`，边界 **0x5058 = 20,568 = 分配常量**；注解 22,224 比它多 1,656B，多出成员只有 decomp 证据、ctor 不写 | A（两端都硬） | 值得，但先裁决尾字段是否属同一对象 |

三条被本次实测证伪的旧口径：
1. 「673,968 是 CCBStage 的另一种分配」——该对象 ctor `sub_4FB9A0` **不写 vtable**，只是零填 arena。
2. 「402,824 的 ctor 名义是 CCCTData」——该地址的 ctor 实际是 `sub_4A6F10`（census 的 `CCCTData_6F10` 是地址后缀名），表却是 SystemUI 的 0x56F29C。
3. 「CCBRoleState 的 ctor 写到 22,224」——ctor 写界精确到 20,568，22,224 是成员表算术值。

## 1. 复现命令

```bash
grep -n "push    62588h\|push    0A4128h\|push    0A48B0h\|push    5058h\|push    5870h\|push    50A4h" original/PAL3.exe.asm
grep -n "call    sub_4A6F10\|call    sub_51D710\|call    sub_4FB9A0\|call    sub_456AB0\|call    sub_4D5AB0\|call    sub_4EC680" original/PAL3.exe.asm
grep -n "off_56F29C" original/PAL3.exe.asm
```

原样输出（关键行）：

```
240548:                push    62588h          ; Size
240558:                call    sub_4A6F10
438657:                push    0A4128h         ; Size
438668:                call    sub_51D710
413390:                push    0A48B0h         ; Size
413398:                call    sub_4FB9A0
118489:                push    5058h           ; Size
118500:                call    sub_456AB0
413627:                push    5870h           ; Size
413640:                call    sub_4D5AB0
413290:                push    50A4h           ; Size
413300:                call    sub_4EC680
245101:                mov     dword ptr [esi], offset off_56F29C
537911:off_56F29C      dd offset sub_445E70
```

## 2. 堆类 402,824B（RoleStatePanel+0x2AFC8 的 pointee）

### 2.1 二进制事实

| 事实 | 值 | 证据 |
|---|---|---|
| 分配指令 | `push 62588h` @ **0x4A4651**（`sub_4A4220`） | asm:240548 |
| 分配调用 | `call ??2@YAPAXI@Z` → 结果判空 → `call sub_4A6F10` | asm:240549–240558 |
| ctor | **0x4A6F10**（399 行），首部/尾部均写 `[esi]=off_56F29C`（DATA XREF 记 `sub_4A6F10+697`）| asm:245101 |
| vtables | **0x56F29C**，7 槽：`0x445E70 / 0x4AD140 / 0x4AD540 / 0x43DE40 / 0x445B90 / 0x4A7670 / 0x4ADC30` | asm:537911–537919 |
| ctor 初值 | `[+58h]=0x320`、`[+5Ch]=0x258`、`[+555Ch]=180.0f`、`[+5B94h]=0x12C`、`[+5D8E8h]=100`、`[+5D8E4h]=0x3E8` | sub_4A6F10 体 |
| 持有 | `mov [esi+2AFC8h], eax`（loc_4A4683 后，注解记 site 0x4A468C），`esi` = **RoleStatePanel**（`InitUIComponents` 里 `mov ecx,eax; call sub_4A4220`，eax 来自 0x2B080 的 RoleStatePanel 分配） | asm:122431–122442、240565–240570 |
| 三写点 | InitUI 清零 0x4A20DD / Init 构造存储 0x4A468C / HideAll 再清零 0x4A66A5 | `RoleStatePanel.json` m_unk_0x2afc8 source（0x4A468C 本卡已复核） |
| 当前注解 | `RoleStatePanel.m_unk_0x2afc8: void*`；`CCCTData.json` size=**430,256**、members=**0**、methods=22、bases=None | 两文件直读 |

### 2.2 命名能不能定

**不能。** 两个候选互相冲突：

- 候选一 **SystemUI/Scene**：`Scene.json` 的 members_note 明确写「SystemUI vtable@0x56F29C/slots(Render/Update/HideAll)」，且槽函数 0x4AD140/0x4AD540/0x4A7670/0x4ADC30 的语料名都是 `SystemUI_*`。但 Scene/SystemUI 的 sizeof=**0x78664=493,156**，与分配 402,824 不合。
- 候选二 **CCCTData**：census 名义与 `EquipUI.cpp:1837 v23 = (CCCTData *)operator new(0x62588u)` 都指向它。但 PDB 里 CCCTData 是战斗任务数据类（`GetCCT`/`AddTaskToList`/`GetFreeSpaceInPool`/`SwapTask`），与「RoleStatePanel 的 UI 子面板、表槽是 ShowClipped/Create/HideAll」不相容；且 CCCTData 注解尺寸 430,256 也不等于 402,824。

缺的证据：**表 0x56F29C 的槽归属**——把 7 个槽函数逐一归到某个类的成员表（或确认无主），并解释 Scene 声明与实际分配尺寸差 90,332B。在表归属定谳前，任何改名都会撞 bases/成员晶格。

### 2.3 值不值得开卡

- 规模：402,824B（当前 `CCCTData.json` 成员为 0，等价于整类空洞）。
- 证据就绪度：分配/ctor/表/持有链 **A**；类名 **无**。
- 判断：**先开一张只做「表 0x56F29C 归属裁决」的小卡**（只读、无写盘），出结论后再开重铸卡（尺寸+成员+methods 归位）。直接开重铸卡会把错误类名固化进 402KB 的结构。

## 3. C2DSpark

| 事实 | 值 | 证据 |
|---|---|---|
| 注解尺寸 | 24,688（0x6070） | `C2DSpark.json` |
| 分配 | `push 5870h`（22,640）@ **0x512AE1**（CBSystem ctor `sub_5125E0`） | asm:413627 |
| ctor | **0x4D5AB0**（266 行，非多态，无 vtable）；入参两个 int（x/y） | asm:413640；PDB `??0C2DSpark@@QAE@HH@Z` |
| 持有 | `mov [esi+34h], eax`，`esi`=CCBSystem（注解 `m_p2DSpark C2DSpark*` @0x34） | asm:4136xx；`CCBSystem.json` |
| ctor 写界 | 最大写偏移 `[esi+586Ch]=-1`，边界 **0x5870 = 22,640 = 分配常量** | sub_4D5AB0 体 |
| 方法集 | ctor 0x4D5AB0 / ~0x4D5DC0 / CreateSingle 0x4D5EC0 / CreateTrack 0x4D5F20 / SetEnableMouseTrack 0x4D5F40 / CreateMore 0x4D6050 / CreateStars 0x4D61A0 / DestroyAll 0x4D61C0 / Render 0x4D6380（9 个语料文件齐） | `asm/pal3/decomp/C2DSpark_*.json` |
| 渲染链位置 | `C2DSpark::Render` 由 **0x513060** 调用（同为 CBSystem 模块，asm:414328） | asm:414328 |

**尺寸判定（已证）**：真 sizeof = **22,640**。分配常量 0x5870 与 ctor 最后写点 0x586C 精确吻合；注解 24,688 多出 2,048，来源是 `m_Spark` 按 48B 反推：`512×48=24,576`（`CHANGE_LOG.md:3945` 自述这是 stride 反推值）。若元素 44B：`512×44=22,528=0x5800`，尾部 112B 正好容纳 ctor 写的 `0x5868/0x586C` 等字段。

**下一步取证入口**：已不需要——分配+ctor 写界两端闭合。开卡时只需按 44B 元素重排尾部字段并过 `check/loop/verify_fix`。

**值不值得**：**最值得**。规模 22.6KB、证据就绪 A、无 bases 依赖、与在跑卡无交集；建议列为 R6 第一张实现卡。

## 4. CCBStage 三数字（逐个来源）

### 4.1 数字一：672,040（0xA4128）

- 分配：`push 0A4128h` @ **0x5233BE**，位于 `sub_5232B0`（`CUtil` 的方法，调用者 `UIGameFrm::_init_44F8D0` case7：`new(0x6EC)`→CUtil ctor `sub_523130`→`call sub_5232B0`）。
- ctor：`call sub_51D710`（409 行），首部写 `[esi]=off_5705D0`（注解 CCBStage 的表）。
- 持有：`mov [esi+6C8h], eax`，`esi`=CUtil；注解把 +0x6C8 命名为 `m_pScreenMode CScreenMode*`（与 CCBStage 类型冲突）。
- ctor 写界：最大 `[esi+0xa3bd0h]`=**670,672**，在 672,040 内（差 1,368B）。
- 等级：**A**（分配+表+ctor 三者闭合）。

### 4.2 数字二：673,968（0xA48B0）

- 分配：`push 0A48B0h` @ **0x512851**，位于 **CCBSystem ctor `sub_5125E0`**；ctor `sub_4FB9A0`（31 行）；存 `[esi+14h]`（注解 `m_pStage CCBStage*`）。
- `sub_4FB9A0` 体：①`rep stosd 0x2922C` 个 dword = 673,968B 全域清零；②从 `+0xAC0` 起循环 **256** 次、步长 **0xA48**，每段清 44B；③`[obj]=arg0`（父对象）、`[obj+4]=arg0->+0x10`。
- **不写任何 vtable** ⇒ 不是 0x5705D0 表所代表的 CCBStage。
- 尺寸异常：`0xAC0 + 256×0xA48 = 676,544 > 673,968`（差 2,576）；但每段只写 44B，最后一次写落在 673,956，未真正越界。
- 等级：分配与体 **A**；「它是 CCBStage」**无证据**（且体形态反证）。

### 4.3 数字三：673,988（注解 binary_size）

- 来源是成员算术，不是分配读数：`m_TaskGroups@0xa8`（`CCBTaskGroup[256]`，元素 0xA48=2,632）→ 止 `0xa48a8`；`m_nTodo_A48A8`@0xa48a8（4B）；`m_dwAniFlagOver`@0xa48c0（4B）→ 末 `0xa48c4`=**673,988**。
- 反证：`0xa48a8/0xa48c0` 都 **大于** 672,040，即这两员落在唯一带表的分配之外；673,988 与 arena 673,968 差 **20B**，但 arena 实际只写到 673,956，两者不是同一布局的读数。
- 等级：算术 **A**，但「这是 CCBStage 的 sizeof」**推定**。

### 4.4 结论

三个数字**不是同一个类的三个尺寸**：672,040 是带表对象的分配；673,968 是 CCBSystem 持有的零填 arena（256×0xA48，元素尺寸恰等于 `CCBTaskGroup` 2,632）；673,988 是注解按成员表算出的值。所谓「20B 差」是「arena 与注解」的差，不是「两个 CCBStage 分配」的差。

**值不值得开卡**：规模 672KB、证据就绪度中低。**先做身份裁决**：①0x5705D0 表的主人是 CCBStage 还是 CScreenMode（CUtil+0x6C8 声明为后者）；②CCBSystem+0x14（`m_pStage`）到底是什么类（若是 `CCBTaskGroup[256]` arena，注解类型就是错的）。两项定了再谈尺寸。

## 5. CCBRoleState ctor 写界

| 事实 | 值 | 证据 |
|---|---|---|
| 分配 | `push 5058h`（20,568）@ **0x44C5F8**（`sub_44C120`） | asm:118489 |
| ctor | **0x456AB0**（52 行 + chunk），首调基类 `0x43DCD0`；写 `[esi]=off_56B364` | asm:118500 |
| ctor 构造的复合体 | `sub_4422E0`@+0x168（152B）、`??_L(+0x200,0x178,0x34)`=52×376B、`sub_43A770`@+0x4E60（344B）、`sub_4422E0`@+0x4FB8（152B） | sub_456AB0 体 |
| ctor 最后一次写 | `[esi+5054h]=0`；`[+4Ch]=0`、`[+48h]=0`、`[+50h]=0x320`、`[+54h]=0x258` | sub_456AB0 体 |
| 写界 | **0x5058 = 20,568**，与分配常量精确相等 | 算术 |
| 注解边界 | 22,224（0x56D0），末员 `m_BattleFlags@0x56CC` | `CCBRoleState.json` |
| 差 | **1,656B（0x678）**：0x5058 = 20,568；0x56D0 = 22,224 | 算术 |
| 超界成员 | 0x5060–0x50A0（effect 参数 11 员）、0x55C8–0x55D0（fade/scroll 4 员）、0x5654–0x565C（fade 3 员）、0x56CC `m_BattleFlags`；source 全为 decomp（方法访问） | 注解直读 |
| 另 20,644 分配 | `push 50A4h`@0x51272B→`sub_4EC680`：`rep stosd 0x1429` dwords=20,644B 全域清零，`[+208h]=arg0`、`[+210h]=arg0->+4`，**无表** ⇒ 另一个零填类，**不是** CCBRoleState | asm:413290–413300 |

**判定**：ctor 写界 = 20,568，与分配常量一致；注解 22,224 比它多 1,656B，多出的成员**不是复合体**（ctor 没有任何对应构造），而是「方法会访问、ctor 不初始化」的尾字段。两种解释：
- (a) 真 sizeof=20,568，尾字段属于**另一个对象**（decomp 把这些访问归到了 CCBRoleState 名下，可能是误挂）；
- (b) 真 sizeof≥22,224，分配常量 0x5058 偏小（原程序依赖堆尾恰好可用，风险高）。

**缺的证据**：对 `sub_44C120` 的 `[+0x3620]` 消费点做 buffer bound 检查（是否有访问越过 0x5058），或 IDA UDT readback 看 IDB 里的成员上界。二者取其一即可定谳。

**值不值得**：规模 20.5KB→22.2KB，证据就绪 A（两端都硬）。值得开卡，但**先裁尾字段归属**；这是「成员背书 vs ctor 字面量」的判据问题，改错会再触发「binary_size 修正必过 loop 门禁」红线。

## 6. 四项横向对比（只给判断，不定优先级）

| 项 | 规模 | 分配证据 | 类名证据 | 风险 | 建议 |
|---|---|---|---|---|---|
| C2DSpark | 22,640 | A（两端闭合） | A（PDB+ctor+持有） | 低（无 bases） | **可直接开实现卡** |
| CCBRoleState | 20,568 / 22,224 | A | A | 中（尾字段归属未定） | 先裁归属，再开尺寸卡 |
| 堆类 402,824 | 402,824 | A | 无（SystemUI vs CCCTData） | 高（改错污染 402KB） | 先开表归属小卡 |
| CCBStage 三数字 | 672,040 / 673,968 / 673,988 | A（三项各自） | 中（表主与 arena 类型待裁） | 高（三项混用会错改 672KB） | 先做身份裁决 |

## 7. 未决

1. 表 **0x56F29C** 的主人：Scene/SystemUI（现有注解说法）还是 402,824 那个对象自己的类？缺槽归属逐条判定。
2. 402,824 的类名：SystemUI 与 CCCTData 都因尺寸/域不符被排除，仍无第三个候选。
3. `CBSystem+0x14`（注解 `m_pStage CCBStage*`）的真实类型：arena 形态（256×0xA48 零填、无表）与 CCBStage 不符。
4. arena 的 `0xAC0 + 256×0xA48 = 676,544` 超出分配 673,968（差 2,576），但实际只写 44B/段未越界——是「记录池按 255 条截断」还是「stride 假设错」，需 IDB UDT readback。
5. CCBRoleState 尾字段 1,656B 是否属同一对象（见 §5 两种解释）。
6. 402,824 在 `EquipUI.cpp:1837` 被强转为 `CCCTData*`，但实际 store 在 RoleStatePanel::InitUI——**文件级归属与对象级持有不一致**，将来改 ctor 归属时要一并处理。

## 8. 只读自证

- 只写 `docs/audit/`；未改 `data/annotations/`、未改 `pal3/src`、未改基线。
- 未运行任何 `pipeline/cli.py` 命令（无 apply/export/codegen/probe/match）。
- 输入全部为只读：`original/PAL3.exe.asm`、`data/annotations/structs/*.json`、`data/pdb/pdb_export.json`、`asm/pal3/decomp/`。
- 本卡写面仅 `docs/audit/`（新增本报告）；`git status --short` 里的 `M data/annotations/*`、`?? data/status/*`、`?? data/annotations/structs/ScreenEffectRingNode.json` 等均为并发卡产物，非本卡写入。
