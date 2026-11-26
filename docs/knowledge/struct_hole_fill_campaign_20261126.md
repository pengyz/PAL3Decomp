---
name: struct-hole-fill-campaign-20261126
description: 字节空洞填充战役 R1-R3.5 的可复用方法：洞普查口径、三锚（CCBCamControl/EquipUI/RoleStatePanel）的二进制闭合路径、证据分级与留白命名、当前开放洞与 R4-R6 入口。
type: pattern
created: 2026-11-26
sources: [ed73fd85e, cf70c0b48, ac9c67673, 22417d35d, e4378a1c4]
---

# 字节空洞填充战役技术纪要（R1-R3.5）

**这篇文档能帮你做什么**：下次遇到「结构体注解里有一大片空档」时，先按这里的口径把「洞」量准，再用二进制证据决定填什么、留什么；同时知道哪几个锚已经闭合、方法怎么复刻、下一轮从哪里接。

**怎么用**：赶时间只看 §1（一页状态 + 复现命令）；动手前读 §2（洞的定义，避免把对齐填充当洞）和 §4（证据分级 / 命名铁律）；要复刻某一锚看 §3；接下一轮看 §5。本文只写已提交的事实，每个结论都带 commit 或 `data/status/` 产物路径；未跑出的数字不写。

**为什么值得沉淀**：三个锚的闭合路径各不相同——池区靠「计数 + 乘法链 + 文件布局」，数组区靠「`??_L` 三元组 + ABI 压栈序」，基类链靠「析构地址 + 就地构造回调」；把这三条路和各自的翻车点写下来，下一次遇到同类大洞可以直接套，不必重新发明探针。

---

## 1. 一页状态（截至 HEAD `e4378a1c4`）

| 项 | 战役起点 | 现在 | 证据落点 |
|---|---|---|---|
| 洞目标面 | 201 类 / 1168 洞 / 1478KB（1,513,593B） | 201 类 / 1142 洞 / 1246KB（1,275,908B） | 起点：`git show 1c0be6473:data/status/struct_holes_20261125.json`；现在：`data/status/struct_holes_20261125.json` `_meta` |
| CCBCamControl | 357,092B / 11 洞 | **12B / 1 洞** | 同上（R1 前后） |
| EquipUI | 168,244B / 28 洞 | **15,960B / 7 洞** | 同上（R2 前后） |
| RoleStatePanel | 156,453B / 7 洞 | **556B / 9 洞** | 同上（R3 前后） |
| S2（编译单元） | 157/229 · L1 188（matched 1146/1254） | S2 **157/229**（总错误 633）· L1 棘轮 189 / 实况 **188**（match 棘轮红） | `data/status/probe_census.json`（`generated_at` 2026-11-26T19:14:46）；`data/status/s4_baseline.json` `stats.match_L1=189`；`data/status/archive/s4_diff_detail_regressed_20261126T192902.json` `l1=188` |

**状态解读（先看这三句）**

1. 三大锚合计收掉约 650KB（357,080 + 152,284 + 155,897 = 665,261B）；但全库洞只从 1478KB 降到 1246KB（净 −232KB）——因为 CCCTData 中间态显形 +430,000B，另有 SkillUI 退赔实消 2,440B 等小项。剩下的最大单块是 **CCCTData 430,256B 的「chimera 中间态」**（R1 孪生定谳后全洞化，等 R6 类 Y 重铸收口），不能拿它当退化信号。
2. **洞数不是进度条**：R3 的 RoleStatePanel 字节从 156,433B 降到 556B，洞数反而从 6 变成 9——一个大洞被落位成员切成若干小缝。验收看**字节**，洞数只作辅助（见 §2 末）。
3. `match` 当前是**红的**，且是「拒绝重锚的正确状态」：RoleStatePanel 的 `scalar deleting destructor` @0x4A2150（30B）从 L1 消失，L1 实况 188 低于棘轮 189。归因（R4 首查）完成前不得 rebaseline（`22417d35d`；交接文档 `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md` §5）。

---

## 2. 「洞」的定义与普查口径

**工具与产物**：`tools/census_struct_holes.py` → `data/status/struct_holes_20261125.json`。这是本战役唯一的洞口径来源；`_meta.rule` 记录了完整规则，下面的解释都可在脚本 docstring 与 `_meta` 里逐字核对。

### 2.1 什么算洞

- **成员间洞** = `next.offset - prev_end` 再减去**自然对齐 pad**（VC6：char 族 1 / short 族 2 / 其余含指针 4 / double·__int64 8）；只有**溢出部分**计入洞，区间起点 = `prev_end + pad`。
- **尾洞** = 最后覆盖末端 → `binary_size`；先扣掉 struct 自身对齐取整（**基类 bases 的对齐也算进去**）。
- **只列 ≥4B 的洞**（脚本 docstring 明示）。

### 2.2 什么不算洞（这五条最容易被误判）

| 不算洞的情形 | 为什么 | 依据 |
|---|---|---|
| 编译器对齐 pad | 用户裁定「对齐 pad 是默认」，不需要手写 `_gap_` 填充 | 脚本 docstring；`596609786`（v3 口径修复） |
| 多态确证类的 vptr 槽 `[0,4)` | 有 `vtables` 注解即视为多态确证 | `_meta.vptr_exempt_classes=59` |
| 基类子对象区 | bases 区域计覆盖，不算空档 | `_meta.rule` |
| 已注解的 `_gap_*` 成员 | 显式填充声明，计入覆盖 | `_meta.rule` |
| `dword_`/`byte_`/`unk_` 型无名成员 | **不是豁免**：它们照常计入覆盖，是「语义化欠账」 | 脚本 docstring 用户裁定第 2 条 |

**已知拼写表**：Win32 ABI 定尺寸别名（`tagRECT` 16 / `tagPOINT` 8 / `_GUID` 16 / `ULONG` 等）直接解析，防止把定长别名当未知类型。反例：`GRPinput ULONG[270]` 曾被当成 154 个成员、16KB 伪洞。

**未知类型兜底**：类型仍不可估的成员，用「下一已知成员偏移」闭合区间（注解偏移=真值，不是猜）；这类成员记入 `_meta.unresolved_type_members=6`，欠账可见。

**overlay 孪生**：union 变体类单列，不计入目标面——当前 `overlay_twin_bytes=919,151`，涉及 `tagCpkAudioOvl` / `tagRoleSlot` / `tagTeamSlotsBOverlay` / `FightItemScriptBlock` / `RoleAttRemarkSkills` 五类。

### 2.3 口径演进中踩过的坑

- **枚举前缀不能猜**：v3 曾把 `tag` 前缀当枚举，令 `tagCPKTable` 4×32768 膨胀成 CPK 768KB 伪洞；现在枚举名只读 `data/annotations/enums.json`（数据驱动）。
- **对齐 pad 争议**：v2 之前按字面「4B 对齐」算，与自然对齐语义总差仅 4B；v2 用户裁定后统一扣除。
- **洞数会因切分而变多**：R3 落位后 RoleStatePanel 洞数 6→9，但字节 −155,877B（`156,433→556`）。所以**不能用洞数判进展**。

### 2.4 每轮验收的三件事（spec §1）

1. `python3 pipeline/cli.py check` PASS（新增违规阻断制）；
2. `python3 pipeline/cli.py loop` 全链绿（恒红的 codegen 容错；apply/export/probe/match 的 rc=0）；
3. 洞字节下降达到当轮预期值的 ±10%（超出必须归因）。

终态口径是**证据背书填充、残洞诚实留**：每个落位成员必须 `evidence_level + source` 齐备；无证据区不做占位填充，洞清单就是债务清单（`docs/specs/2026-11-26-struct-hole-filling-campaign-design.md` §1）。

---

## 3. 三锚怎么闭合（可复刻的路径）

### 3.0 四段式与「六证择二」

每轮固定四段（spec §3）：

1. **填充段**：写 idalib 探针（产物落 `data/status/probe_*.json`）→ 证据链 → 注解落位（`evidence_level + source` 齐备）→ `cli.py check`。
2. **对抗复核段**：独立子 agent 只读复核；**自己重写探针、不 import 原探针**；逐条重验证据链 + 归因读数差 + 出裁决表（真 bug / 可接受近似 / 口径解释题）。发现真 bug 当轮修复，不带病进下一轮。R1 的复核基线说明见 `data/status/r1_adversarial_review_20261126.json` 的 `_doc` 字段。
3. **管线段**：`cli.py loop` 全链；codegen 中途夭折会留下部分再生头树，**先独立跑 `codegen all` 补完再进 loop**。
4. **落账段**：独立提交（commit-msg 的 Evidence 格式）+ 记忆更新 + 重跑 census + 裁决表落 `data/status/`。

**六证择二**（落位成员至少要两条独立证据）：

> ctor 写序 / disp 聚类 / 工厂解码 / 调用点 ecx 回溯 / PDB mangle / 金表字面量

其中 PDB 只作线索不作定谳（见 §4.3）。

### 3.1 R1 · CCBCamControl：池区四段闭合

- **洞**：357,092B / 11 洞（战役起点 census）。
- **闭合结果**：12B / 1 洞（`data/status/struct_holes_20261125.json`，R1 提交 `ed73fd85e`）。
- **四段算术**（台账 `data/status/ccbcamcontrol_r1_retirement_20261126.json` `consistency.arithmetic`）：

  ```
  204 × 2000 = 408,000 = 0x639C0      m_Pool tagCCT[2000] @0x0
  0x639C0 + 0x7D0 = 0x64190            m_bPoolInUse uchar[2000] @0x639C0
  0x64190 + 20,000 = 0x68FB0 = 430,000 m_TaskListIndex int[100][50] @0x64190
  [0x68FB0, 0x690B0) = 256B            尾域 25 员
  合计 = 430,256 = 0x690B0 = binary_size（精确收口）
  ```

- **证据链**：
  - 池计数：字面量 `0x7D0` 五址 + `ResetAllData` 三组派生常量 + 乘法链（`204×2000`）。探针 `data/status/probe_ccbcamcontrol_poolcount_20261126.json`。
  - 活性标志：`m_bPoolInUse` 由 `flexcam.dat` 存读布局自证，并有活性消费者 0x5052c0（空闲槽分配器）——`probe_ccbcamcontrol_pooldecode_20261126.json`。
  - 句柄表：`idx = 4·(T + 50L + 102500) = 410,000 = 0x64190`，`InsertTaskToList` 0x5075ec–0x5075f9 与 `SwapTask` 0x507b35–0x507b42 两方法同式；行步距 200B = 50 项/行（`r1_adversarial_review_20261126.json` 独立反汇编复核）。
  - 孪生定谳：`g_CCBCamControlData` BSS「全局」被证伪为零装载形静态变量块；双堆类终局（类 X = CCBCamControl 0x690B0，类 Y = 0x62588）——`417d3a34a` / `b93e53921` / `1a52354e2` / `4bcc8fbae`。
- **冲突面处置**：17 个头域/中域成员与池模型**几何互斥**，整表退役（不保留「都保留」解）。逐员 access 证据与退役理由在台账 `decisions[3..19]`。
- **副线 SkillUI 53 退赔重挂**：53/53 与 `data/annotations/archive/ccbui_identity_adjudication_20261121.json` 的 `retired_members` 三元组（name/type/reason）程序化对全等；`evidence_level` 保持 `unverified`（重挂 ≠ 升级）；census 实消 2,440B（spec 预估 240B 为误差，T5 已归因）。
- **CCCTData 中间态**：三员（`m_Pool`/`m_bPoolInUse`/`m_nCCTIndex`）删除，`binary_size=430,256` 不动，全洞 430,256B 是**诚实中间态**，等 R6 类 Y 重铸。**不要拿它做回归对比**。
- **管线**：loop 全链绿，S2 157/229 · L1 188 双稳（`ed73fd85e`）。

**可复用动作**：大洞 + 零直接访问 ≠ 无主空间。先查间接寻址（`pool[idx] × stride`）与文件读写布局，再判无主；计数没有代码字面量时**不猜**，挂探针案推迟。

### 3.2 R2 · EquipUI：尾区九数组落位

- **洞**：168,244B / 28 洞 → 15,960B / 7 洞（`cf70c0b48`）。
- **证据链**：
  - ctor `??0EquipUI`（0x498820）里九笔 `??_L@YGXPAXIHP6EX0@Z1@Z` 构造现场三元组；**gate① 用 ABI 压栈序实证**（dtor→ctor→count→size→ptr），裁定终版落位表在 `data/status/equipui_r2_adjustments_20261126.json` `gate1_table`。探针：`data/status/probe_equipui_arrays_20261126.json`。
  - 元素类鉴定：`UIParticle`（584B）×4 用**三角定位**（stride + ctor 回调足迹 + PDB/census 交叉；`0x1414`/`0x13814` 两阵各 128×584=74,752B，收口 0x25C14）；`UIPushButton` / `tagPlayerSet` / `UIFrameContainer[12]` 分别由 ABI 与消费面锚定。
  - 76 个旧成员退役：与九区间几何互斥；PDB 只作**独立佐证**（旧注解系 PAL3A 布局导入），不是单独定谳依据。
  - `UIFrameContainer` 136→152：ctor 写表 0x56add0 `verdict=CONFIRMED` + stride 0x98=152 + 足迹 0x94 + PDB `UIStatic=152` 交叉。
- **副线 RoleStatePanel 七模块指针**：分配 + 存储 + 消费面三证；读点数 27/26/26/26/15/14/9（`equipui_r2_adjustments_20261126.json` `task3_rolestatepanel_seven_ptrs`）。
- **读数**：census 164KB→15.6KB；全库 1546KB→1398KB；loop 全绿；S2 157→158、L1 188→189（`+30B resize` 的**诚实配对**后显式重锚，理由见 `data/status/s4_baseline.json` `rebaseline.reason`；S2 的该轮读数与最新实读的差异见 §6 第 2 条）；`EquipUI.cpp` 42→9 churn 属真修复（类型实配）。

**可复用动作**：数组落位必须 **stride 乘法链 + 计数闭合**；元素类名拿不到时落 `unsigned char[整体跨度]` + note「元素 N B stride，类名待鉴定」，**不许发明名字**。

### 3.3 R3 · RoleStatePanel：40 员落位 + 基类链裁决

- **洞**：156,433B / 6 洞 → 556B / 9 洞（`ac9c67673`，−155,877B，−99.64%）。
- **阻塞项先裁：基类链双类**（`data/status/uilistbox_chain_adjudication_20261126.json`）：
  - `0x43DCD0` = **72B 类**的 ctor（8 条指令：call UIWnd ctor 0x445AA0 + 写表 0x56AD20 + `[esi+0x44]=0`；对象尾 0x48=72）。
  - `0x43DFC0` = **1208B 另类**的 ctor（写表 0x56AD40，写面最大 `[esi+0x4B4]+4=0x4B8`；真 new 面 `push 0x4B8 → operator new 0x55353B → call 0x43DFC0` ×3）。
  - **两条旧假说被证伪**：①「ctor 双写 0x56AD20+0x56AD40 = MI 双表形」——两个 ctor 各写一表，全 .text 写者仅 4 处；②「`push 0x4B8` = operator new」——0x4E11A9/0x4E9D20 等 6 处实为对话框控制 ID 序列（`WM_INITDIALOG` 分派）。
  - RoleStatePanel 落地：`InitUI@0x4a1e40` 首调 0x43DCD0 @this+0 → +0 子对象是 72B 类（UIWnd 内嵌 `[0,0x44)`，`[0x44,0x48)` 是基类纹理句柄成员）→ `bases=[UIListBox@0]` + `vtables[0].base` 同步；own 区自 0x48 起。
  - **名义债**：当前 `UIListBox` 名仍绑 72B 类（下游 SkillUI/StateUI/CCBUICtrl 的 bases 晶格全部锚定它；换成 1208 会触发 check C10 布局冲突 280 项），1208B 类挂 address-tag `cls_43dfc0`，名义重锚留作后续战役（须用户裁决，台账 `debt_ledger` #2）。
- **成员落位证据**（`data/status/rolestatepanel_r3_adjustments_20261126.json`；探针 `probe_rolestatepanel_layout_20261126.json`、`probe_rolestatepanel_holes_20261126.json`）：
  - 五笔 `??_L`：`UIParticle[128]×2` @0x12f8 / 0x136f8（128×584=74,752=0x12400，无缝，收口 0x25af8；元素类用三角定位：584 == `UIParticle.binary_size`、ctor 回调足迹 0x244 ⊆ 584、与 EquipUI 同款误名回调对）；`s_RoleState[5]` @0x25e04（5×3,788=18,940B，收口 0x2a800）；`UIFrameContainer[4]` @0x2a800（4×152=608）与 `[5]` @0x2ab08（5×152=760），`verdict=both`。
  - 子对象构造对（152B / 344B 群）按 ctor 现场逐对落位；未名者用 byte 形 + note，合规。
  - `m_RoleStatics UIStatic[5]@0x210` 退役：三面证据压倒旧类型——① ctor 对 `[0x210,0x508)` 五段就地构造回调 `ResetContainerState(0x4422e0)`，与 `??_L[4]/[5]` 同款；② `~RoleStatePanel` 对同址 mangle 直调 `??1UIFrameContainer@@QAE@XZ`；③ `UIStatic.json` 无任何回调链锚定本区。`UIStatic` 与 `UIFrameContainer` 同为 152B，旧的「sizeof 对账」**不具区分力**。
- **残洞**：9 洞 / 556B，全部「零证据诚实留」，独立双通道复验（台账 `census` 与探针交叉）。
- **一处必须知道的伪影**：`RoleStatePanel.cpp` 新增 1 条 C2440 是 Hex-Rays 局部类型化伪影（ASM 全字节粒度实证），不是 codegen 退化；L-VAR 引脚提案呈报待批（`ac9c67673` 第 ⑧ 条）。

**可复用动作**：遇到「基类尺寸与 ctor 真身矛盾」时，**先裁阻塞项再落成员**；判类身份优先用**析构函数地址 / 就地构造回调**这类强钥匙，尺寸相同不构成证据（152B 孪生案）。

### 3.4 R3.5 语义清理：留白形落地（战役边界）

- **范围**：触达 7 类（CCBCamControl / CCCTData(空) / SkillUI / EquipUI / RoleStatePanel / UIFrameContainer / UIListBox），实际改 2 个结构体文件（另 +1 条冻结基线：`data/status/check_baseline_errors.json`）。
- **三态结果**：正名 0 / 退役 0 / **迁移留白形 42**（RoleStatePanel 40 + EquipUI 2）。正名 0 是**判据诚实产出**，不是没干活：候选 `0x58/0x5c`（ctor 写 800/600）消费面零读，按「语义实锤才正名；拿不准 → `m_unk_`」判迁移。
- **用户两裁定**：① 留白命名统一形 = `m_unk_<小写 hex 自身偏移>`（KEYCASE）；② 正名判据 = 语义实锤，拿不准即留白。
- **门⑥ 四项**：扩展正则零残留 / 白名单零误伤 / 41 条冻结逐字 / census 零漂移。台账：`data/status/r35_semantic_cleanup_20261126.json`。
- **流程**：改名 → 语料悬空报 N13a 新错误 → 精确冻结 41 串 → loop 重渲 → 解冻验证。census 零漂移证明「改名不改几何」。
- **代价**：重渲后 `match` 棘轮红——`RoleStatePanel::scalar deleting destructor` @0x4A2150（30B）LOST，属 `s_RoleState.cpp` 单元重渲的组内联决策变化；L1 实况 188 / 棘轮 189，**拒绝重锚**，交 R4 首查（`22417d35d`；`data/status/archive/s4_diff_detail_regressed_20261126T192902.json`）。

---

## 4. 证据分级、留白与命名铁律

### 4.1 两个「级」不要混

- **注解字段级**（结构体 JSON）：`evidence_level: verified | unverified`。`verified` = 有二进制证据；`unverified` = 只有语料/旧注解（欠账可见）。**重挂不升级**（R1 SkillUI 53 员保持 `unverified`）。
- **主张类型级**（全局证据规则，`docs/knowledge/rule_evidence_tiering_no_unobtainable_gate.md`）：
  - **A 档（结构性）**：参数个数 / 成员偏移 / 调用点 / vtable 归属 / 值位型 / 成员尺寸——必须有 objdump / `retn` 级证据；
  - **B 档（语义性）**：参数类型 / 语义名 / 返回语义——需 decomp 消费证据，落盘时标 `type_evidence: "B"`；
  - **C 档（证据不足）**：冻结留白，禁止伪语义命名。

### 4.2 留白形与命名铁律

- 禁止：`slot_N`、`sub_XXXXXX`、`_todo_`、`v1_` 等一切无语义名（含注解 methods/slots.name、头文件发射、IDB 名）。
- 数据成员留白统一形：**`m_unk_<offset>`**，offset 用**小写 hex、成员自身偏移**（例：`m_unk_0x2afc8`）。
- 函数名遵循 C++ 重载规则，**禁止数字后缀做地址消歧**（用户裁定 2026-11-26，提交 `24ea738ce`，撤销 `HideAll_3DE40` 先例）。
- ctor 注解三件套 = 类名 + `flags:["ctor"]` + sig 返 this/void（`emit_headers` fail-loud 强制）。
- `bases` 变更必须落 `data/status/bases_adjudications.json`（C11 门禁）。
- **正名判据从紧**：消费 / 写值证据实锤才正名；只有写、没有读，或语义身份未知，一律留白（R3.5 先例：`m_nTodo_174` 有置位/门标/清零，仍不发明真名）。

### 4.3 PDB 与假名

- **PDB 非权威**：单一 PDB mangle 不定谳，必须与二进制证据组合。实证：`DoTask`/`AddTask` 不在 PDB 的 CCBCamControl 表（构建漂移）；4 个「CCCTData 方法」是 FLIRT/ICF 假名。在档声明：`data/status/_pdb_nonauthority_notice.json`。
- **FLIRT 假名第四形态**：5–15B 微函数挂语义名（判据：体长 + 体语义失配）。例：`0x43DEA0 AddColumn` 实为读表尾 float 12.0 的初始化 stub；`0x43DF10/0x43DF20` 实为 1208B 类 `@0x1B4` 列数组的 elem ctor/dtor 对（`uilistbox_chain_adjudication_20261126.json` `evidence_refutations`）。

### 4.4 退役 / 迁移 / 留洞 三选一

- **几何互斥**（新落位的数组/池与旧成员占同一段）→ 退役，逐员记账（R1 17 员 / R2 76 员 / R3 1 员）。
- **只改名字、几何不变** → 迁移留白形（R3.5 42 员），census 应零漂移。
- **零证据** → 留洞，不填占位（RoleStatePanel 9 洞 556B）。

### 4.5 N13a 冻结过渡协议

改名/退役后语料里的旧名会悬空，`check` 报 N13a 新错误。正确姿势：**精确冻结涉及的旧串**（不要 blanket）→ 跑 loop 重渲 → 解冻验证旧名清零。N13a 是预期过渡，不是回归；但也**不许拿它当「已修复」的证据**，最终以 census/check/loop 读数为准。

---

## 5. 当前仍开放的洞与 R4/R5/R6 入口

### 5.1 当前最大的开放洞（`data/status/struct_holes_20261125.json`，R3 后）

| 类 | 洞字节 | 洞数 | 承接 |
|---|---:|---:|---|
| CCCTData | 430,256 | 1 | R6（chimera 中间态；尺寸争议未裁前勿据此回归） |
| ScreenEffectMgr | 363,820 | 2 | **R4**（从零诊断） |
| SkillUI | 99,428 | 4 | 未排轮次（R1 副线只做 53 员退赔重挂，未做填充） |
| MagicUI | 44,652 | 16 | **R5** |
| SaleUI | 44,560 | 23 | **R5** |
| UIGameFrm | 27,916 | 37 | R5 副线 |
| UITitle_JDHY | 19,396 | 14 | R6 挂账（`Note_Item` 双布局 / 377,700 vs 金表 290,488） |
| PropUI | 18,652 | 45 | R6 挂账（差 164） |
| CG_UI | 18,492 | 31 | 长尾未排 |
| DealData | 17,260 | 1 | 长尾未排 |
| EquipUI | 15,960 | 7 | 本轮残洞（诚实留） |
| RoleStatePanel | 556 | 9 | 本轮残洞（零证据诚实留） |
| CCBCamControl | 12 | 1 | 本轮残洞（诚实留） |

> 口径提醒：census 只列 ≥4B 的洞；spec §1 已声明 189 个非点名类长尾约 443KB 无轮次承接，上表「未排轮次 / 长尾」只是其中最大的几个，不是全部。

### 5.2 R4 首查（阻塞级，先做）

`match` 棘轮红归因：`RoleStatePanel::scalar deleting destructor @0x4A2150`（30B）从 L1 消失；退化明细已存档 `data/status/archive/s4_diff_detail_regressed_20261126T192902.json`。**归因（是真退化 / 渲染 churn / 基线错误）完成前不得重锚**；此卡与 R4 正式开工分开，见交接文档 §5。

### 5.3 轮次入口（按交接文档 §5）

- **R4**：`ScreenEffectMgr` 355KB 从零诊断（新立案；`binary_size=363,968` 是金表修正后的首轮读数）。
- **R5**：`MagicUI` 43KB + `SaleUI` 43KB 批量小锚，副线 `UIGameFrm` 27KB。
- **R6 挂账批**：`UITitle_JDHY Note_Item` 双布局仲裁 / `C2DSpark tagSpark` 重验 / `CCBStage` 三数字 / `PropUI` 差 164 / `CCBRoleState` ctor 写界 / **堆类身份定谳**（430,256 类 X 已裁；402,824 类 Y 待名；425,136 候选已除名——`0x68FB0=430,000≠425,136`，见 spec §2 R6）。
- **语义名主战役（跨轮）**：存量非语义名分批迁移留白形；正名判据 = 消费 / 写值证据实锤（交接文档 §5）。
- **基类链债务**：`cls_43dfc0`（1208B）建 struct JSON + 存量方法迁归位；`UIListBox` 名义重锚需用户裁决并联动 4 类 bases 晶格（`uilistbox_chain_adjudication_20261126.json` `debt_ledger` #1/#2）。
- **待批管线项**：RoleStatePanel `C2440@777` 的 L-VAR 引脚提案（三选一，见交接文档 §5「待用户批准」）。

---

## 6. 数字口径注意：commit 文字与产物不一致处

写这份纪要时逐条对账，发现 4 处「提交说明的字面数字」与产物/台账对不上。**以产物为准**，并把差异记在这里，避免后来者把产物改成迎合文字：

1. **R1 洞字节**：`ed73fd85e` 提交说明写「洞 337092B→12B（−329KB）」「尾域 25 员（1256B）」；战役起点 census 产物是 **357,092B**，台账四段算术的尾域是 **`[0x68FB0,0x690B0)`=256B**，且 `408,000+2,000+20,000+256=430,256` 才精确收口。337,092 = 357,092 − 20,000（恰为 `m_TaskListIndex` 段跨度），疑为把该段算作已填的口径差。
2. **当前 S2**：交接文档 `e4378a1c4` §1 记「S2 158/229」；最新 probe 产物 `data/status/probe_census.json`（`generated_at` 2026-11-26T19:14:46）是 **157/229**，`cli.py status` 实读一致。以产物为准。
3. **PDB 族谱路径**：交接文档 §4 写的 `data/status/probe_pdb_camera_family_20261126.json` **不存在（勿引用）**；实际文件是 **`data/status/pdb_camera_family_20261126.json`**（无 `probe_` 前缀，`git ls-files` 可证）。
4. **R3 自有区起点**：`ac9c67673` 提交说明写「`[0x44,0x4B8)` 归自有」；裁决台账 `rolestatepanel_resolution` 的正确表述是 own 区**自 0x48 起**，`[0x44,0x48)` 的 dword 是基类子对象的纹理句柄成员。以裁决台账为准。

另有一处**算术笔误**：R3 台账 `consistency.arithmetic` 写「5×3788=18940=0x4AFC」，正确十六进制是 **0x49FC**（18,940）；`0x25E04+0x49FC=0x2A800` 才与下一数组起点闭合。

> 原则：**注解产物 / 复算能闭合的算术 > 提交说明的转述**。发现文字与产物冲突时，先复算，再在文档里标注，不要静默二选一。

---

## 7. 验证命令（复制即跑）

```bash
# 0) 先存一份现状，便于对比 census 是否被你跑出差异
cp data/status/struct_holes_20261125.json /tmp/holes_before.json

# 1) 洞普查（注意：会覆写 data/status/struct_holes_20261125.json）
python3 tools/census_struct_holes.py
python3 -c "import json;d=json.load(open('data/status/struct_holes_20261125.json'));m=d['_meta'];print(m['classes_with_holes'],m['total_holes'],m['total_hole_bytes'])"
# 预期：201 1142 1275908（即 1246KB；若不同，先归因再继续）
git diff --stat data/status/struct_holes_20261125.json   # 预期为空

# 2) 秒级门禁（约 2.3s，不进 IDB）
python3 pipeline/cli.py check

# 3) 只读状态预检（S2/L1/恒红门禁一屏看完）
python3 pipeline/cli.py status

# 4) 单类洞明细
python3 tools/census_struct_holes.py --class RoleStatePanel

# 5) 全链（约 20 分钟；match 棘轮红 = R4 首查项，勿重锚）
python3 pipeline/cli.py loop
```

---

## 8. 引用物索引

| 路径 | 用途 |
|---|---|
| `docs/specs/2026-11-26-struct-hole-filling-campaign-design.md` | 战役目标、终态口径、R1–R6 规划、证据红线 |
| `docs/specs/2026-11-26-r1-implementation-plan.md`、`docs/specs/2026-11-26-r2-implementation-plan.md`、`docs/specs/2026-11-26-r3-implementation-plan.md` | 三轮实施计划（任务级验收） |
| `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md` | R1–R3.5 全程交接（状态/新定律/入口/验证/红线） |
| `tools/census_struct_holes.py` | 洞普查器（口径唯一实现） |
| `data/status/struct_holes_20261125.json` | 洞清单与 `_meta` 口径 |
| `data/status/ccbcamcontrol_r1_retirement_20261126.json` | R1 四段算术、17 员退役、SkillUI 重挂 |
| `data/status/probe_ccbcamcontrol_poolcount_20261126.json` 等探针产物 | R1 孪生/池区证据链 |
| `data/status/r1_adversarial_review_20261126.json` | R1 对抗复核裁决（真 bug 0 / 近似 3 / 口径题 5 / 确认 4） |
| `data/status/equipui_r2_adjustments_20261126.json` | R2 九数组 gate① 落位表、76 员退役、136→152 |
| `data/status/probe_equipui_arrays_20261126.json` | R2 九笔 `??_L` 探针产物 |
| `data/status/rolestatepanel_r3_adjustments_20261126.json` | R3 40 员落位、`m_RoleStatics` 退役、bases 落地 |
| `data/status/probe_rolestatepanel_layout_20261126.json`、`data/status/probe_rolestatepanel_holes_20261126.json` | R3 ctor 解码 / 残洞双通道验证 |
| `data/status/uilistbox_chain_adjudication_20261126.json` | 72B/1208B 双类裁决、名义债、假名证伪 |
| `data/status/r35_semantic_cleanup_20261126.json` | R3.5 三态、42 条改名、门⑥ 四项 |
| `data/status/bases_adjudications.json` | C11 bases 变更台账 |
| `data/status/s4_baseline.json` | L1 棘轮 189、R2 重锚理由 |
| `data/status/archive/s4_diff_detail_regressed_20261126T192902.json` | L1 实况 188 / 退化明细 |
| `data/status/probe_census.json` | 当前 S2 157/229（`generated_at` 19:14:46） |
| `data/status/pdb_camera_family_20261126.json` | PDB 方法族谱（仅线索） |
| `.superpowers/sdd/2026-11-26-r1-implementation-plan/progress.md`、`.superpowers/sdd/2026-11-26-r2-implementation-plan/progress.md`、`.superpowers/sdd/2026-11-26-r3-implementation-plan/progress.md` | 三轮 SDD 任务级裁定与门①–⑥记录 |

---

## 9. 本文的边界

- 只覆盖 R1 / R2 / R3 / R3.5 的**方法与已提交结果**；W2 孪生定谳的完整探针细节只作上下文引用（见 §3.1 的 4 个提交）。
- 当前读数取自产物与 `cli.py status` 实读（2026-11-26），没有重跑 20 分钟的全链 loop；需要最新 S2/L1 时按 §7 自己跑。
- 按本 Task 的 writeScope，本次**只新增本文件**；文件名按 Task 指定（未走 README 的 `<type>_<slug>.md` 前缀约定，type 已写在 frontmatter）。`docs/knowledge/README.md` 要求的 `MEMORY.md` 索引行与 `kairos/` 日志行**未同步**，留作后续单独补（避免改动既有文件）。
