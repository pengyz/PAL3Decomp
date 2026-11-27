# R6 六项结论的证据台账缺口核对（只读）

> 核对时点：2026-11-27 02:14 +08:00；HEAD `aa894e694`。
> 台账文件：`data/status/evidence_ledger.json`（M，未提交，sha256 `f1c1f9a2…2a29`）。
> 洞普查：`data/status/struct_holes_20261125.json`（mtime 2026-11-27 02:12:21）。
> 本文件只做缺口核对与补登记草案：**没有执行 `evidence_ledger.py add`，没有改台账、注解、代码、数据或基线，没有跑管线。**

## §0 结论

六项结论里，只有① UITitle_JDHY 已有台账条目；②–⑥ 五项在 `query --subject` 下都是 0 命中。

| 项 | 结论 | 现有 ev | 是否缺口 |
|---|---|---|---|
| ① UITitle_JDHY 290,488 | #22 A 级 | ev_0013 / ev_0014（均 A/open） | **不缺口**；但要带 id，且注意①的注解仍是工作树 M |
| ② C2DSpark 22,640 / tagSpark 44 | #29 A 级 | 无 | 缺口 |
| ③ CCBStage 672,040（另一对象 673,968） | #27 A 尺寸 / B 归属 | 无 | 缺口 |
| ④ PropUI 28,892（差 164） | #31 A 级 | 无 | 缺口 |
| ⑤ CCBRoleState 20,568 | #24 B 级 | 无 | 缺口 |
| ⑥ CCCTData 430,000 池 union / 类 Y 402,824 | #18 A 身份反证 | 无 | 缺口（D-1 未裁） |

台账总览：14 条，open 12 / resolved 2 / contradicted 0；A 级 11、B 级 3；下一个 id 是 `ev_0015`。

**决策就绪度**：按“引用结论必须带 ev id”的纪律，当前六项简报只有①有据可引；②–⑥ 在上会材料里只能先标“ev 待补”，不能写成已登记。

**分级摘要**（详见 §5）：

- **Human 拍板前必须补**：⑥（身份冲突，决定 P-1/P-2 走哪条）、③（真尺寸 + 第二对象归属，牵动 20 个成员）、⑤（B 级总体定谳，牵动 23 个跨类成员）。
- **可与落地卡合并补**：②、④（都是单链 A 级、无身份冲突；但上会引用时必须标“ev 待补”，不能当成已闭合）。
- **只需文档引用**：① 的 ev_0013/ev_0014 已经存在，不新增；其余“施工步骤/缺口清单”属方案，不进台账。

## §1 核对口径

1. **台账条目是二进制结论的指针，不是计划书。** “建议按 P-1 重铸”“下一卡要改哪些成员”这类内容留在源文档；进台账的应是“尺寸/归属/身份是什么、等级多少、证据在哪”。
2. **等级沿用源文档**，本文件不重新裁决。②③④⑥的尺寸/身份是 A 级；③的第二对象归属、⑤的总体定谳是 B 级；⑥的施工路线 P-1/P-2 仍是待裁方案。
3. **“已有 ev”与“相关 ev”要分开。** `RoleState` 能查到 ev_0003/0004，但那是 RoleStatePanel 的 C2440/0x25B78 类型，不是 CCBRoleState 的尺寸；`ScreenEffect` 能查到 ev_0005/0006/0011/0012，但那是 ScreenEffectMgr，不是 CCCTData。两者都不能替代⑤/⑥。
4. **状态四态分开写**：已验收 / 已提交（HEAD）/ 工作树未提交（M）/ 仅盘点。① 的注解是“工作树 M、HEAD 仍旧值”，census 已随工作树更新；这不是“已提交生效”。
5. **census 是派生账，不是裁决源。** 文档定谳但注解未落地时，census 仍是旧值；落地后必须重跑，不能拿旧 census 反推结论。

## §2 六项对照表

| # | 结论（源文档） | 原等级 | 现有 ev | 与现状/旧结论的冲突 |
|---|---|---|---|---|
| ① | UITitle_JDHY `sizeof=290,488`；`Note_Item[36]@0x262C8`（`docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md:9-14`） | A | ev_0013、ev_0014（A/open） | HEAD 仍是 377,700/28；工作树 290,488/43（M）；census 已到 290,488/43/8B。旧 377,700/99×3,560 无本 exe 构造证据。 |
| ② | C2DSpark `22,640`；tagSpark `44`、512 元素（`docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md:8-11`） | A | 无（0 命中） | HEAD=工作树=24,688/20，tag 48/12；census 无 C2DSpark 条目。24,688/48 是注解派生量，PDB 同值但只是参考。 |
| ③ | CCBStage `672,040`；另对象 `673,968`；`673,988` 是 +20B 幻影（`docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md:6-14`） | A（尺寸）/ B（第二对象归属） | 无（0 命中） | HEAD=工作树=673,988/20；census 673,988/20/36B/2。20 个成员与 673,968 对象吻合，不是 672,040 那个类。 |
| ④ | PropUI `28,892=0x70DC`；差 164=52+16+96（`docs/specs/2026-11-27-propui-size-164-evidence.md:9-26`） | A | 无（0 命中） | HEAD=工作树=29,056/95；census 29,056/95/18,652B/45，末洞 `0x7120-0x7180=96`。不能只改尺寸，须与尾部重排成对。 |
| ⑤ | CCBRoleState `20,568=0x5058`；22,224 是混装（`docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md:6-13`） | B（总体）/ A（分配+写界） | 无（0 命中） | HEAD=工作树=22,224/89；census 22,224/89/6,483B/27。尾部 23 员分属 20,644B 类、零访问、CCBUIPanel、PropUI，不能静默删。 |
| ⑥ | PDB `CCCTData=430,000` 池 union；类 Y `402,824`；`CCBCamControl=430,256`（`docs/specs/2026-11-26-ccctdata-recast-plan.md:9-30`） | A（身份反证） | 无（0 命中） | HEAD=工作树=430,256/0；census 430,256/0/430,256B/1。twin 裁决说“类 Y=CCCTData”，与 PDB 冲突，D-1 交 Human；P-1/P-2 未执行。 |

## §3 查询实录

实际执行（只读）：

```bash
python3 tools/evidence_ledger.py query --subject UITitle_JDHY --full
python3 tools/evidence_ledger.py query --subject C2DSpark
python3 tools/evidence_ledger.py query --subject CCBStage
python3 tools/evidence_ledger.py query --subject PropUI
python3 tools/evidence_ledger.py query --subject CCBRoleState
python3 tools/evidence_ledger.py query --subject CCCTData
python3 tools/evidence_ledger.py query --subject RoleState
python3 tools/evidence_ledger.py query --subject ScreenEffect
```

输出摘要：

- `UITitle_JDHY --full`：命中 2 条。`ev_0013`（A/open，UITitle 尺寸 0x46EB8=290,488；`0x4A46B5 push 0x46EB8`→`0x4A46C4 call 0x55353B`→`0x4A46DE call 0x4B01D0`；旧 0x5C364/377,700 全 disasm 0；refs 含 `original/PAL3.exe.asm:240584`、`docs/specs/2026-11-27-r6-t1-uititle-jdhy-placement.md`、注解）；`ev_0014`（A/open，43 员落位、vtable 五表、census 19,396B→8B；refs 含归档脚本、R6-T1 文档、census）。
- `C2DSpark` / `CCBStage` / `PropUI` / `CCBRoleState` / `CCCTData`：各 **共 0 条命中**。
- `RoleState`：2 条（ev_0003/0004），都是 RoleStatePanel 的 C2440 / 0x25B78 类型结论，**不是 CCBRoleState 尺寸**。
- `ScreenEffect`：4 条（ev_0005/0006/0011/0012），都是 ScreenEffectMgr，**不是 CCCTData**。
- 台账总览：14 条，open 12 / resolved 2；A 11 / B 3；`next_id=ev_0015`。

## §4 逐项补登记指针与 add 草案

> 下面只是字段草案，**没有执行**。对应命令形态：`python3 tools/evidence_ledger.py add --subject … --authority … --claim … --ref …`；状态默认 `open`，由裁决流程再改 resolved。

### 4.1 ① UITitle_JDHY：不新增，只核对

已有 `ev_0013`/`ev_0014`，均 A/open。上会引用时直接带这两个 id，不重复建条目；若制度要求“决策引用必须 resolved”，那要先按台账流程裁决，不在本文件代做。

补登记指针（核对现有条目是否仍对得上）：

- 源文档：`docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md:9-14`；`docs/specs/2026-11-27-r6-t1-uititle-jdhy-placement.md`（ev 的 refs 指向此篇）。
- VA/指令：`0x4A46B5 push 0x46EB8` → `0x4A46C4 call 0x55353B` → `0x4A46DE call 0x4B01D0`；`0x4A46F2 mov [esi+0x2AFD0],eax`。
- 现状：`data/annotations/structs/UITitle_JDHY.json` M，工作树 290,488/43；HEAD 377,700/28；census 290,488/43/8B/1。
- 复现：`git show HEAD:data/annotations/structs/UITitle_JDHY.json`；`python3 tools/census_struct_holes.py`。

### 4.2 ② C2DSpark：A 级，可随落地卡补

- 源文档：`docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md:8-11`（§0 结论）、§4.1 分级、§4.3 缺口。
- VA/指令：`0x512AE1 push 0x5870`（唯一分配）→`0x512AF0 call 0x55353B`→`0x512B1B call 0x4D5AB0`；ctor 清零 `mov ecx,0x161C; rep stos`（0x161C×4=22,640）；tagSpark 步长 `0x2C`、元素数 `0x200=512`。
- 冲突：HEAD/工作树 24,688/20、tag 48/12；census 无该类条目；PDB 同旧值但只能作参考。
- add 草案：

```text
subject: C2DSpark 类尺寸 22,640 / tagSpark 元素 44
authority: A
claim: 唯一 operator new 立即数 push 0x5870、ctor 清零常量 0x161C×4 与最大写 [esi+0x586C]+4 三链闭合；tagSpark 三处步长 0x2C、512 元素、整元素 11 dword 拷贝，512×44=0x5800 与尾部成员起点对齐。
evidence_refs:
  - docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md:8-11
  - original/PAL3.exe.asm（0x512AE1/0x512AF0/0x512B1B 及 §3.2 步长点）
  - data/annotations/structs/C2DSpark.json（WT 24,688/20）
  - data/annotations/structs/C2DSpark_tagSpark.json（WT 48/12）
status: open
```

### 4.3 ③ CCBStage：A 尺寸 + B 归属，拆两条

- 源文档：`docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md:6-14`（§0 表）、§4.2 缺口、§4.3 影响面。
- VA/指令：`0x5233BE push 0xa4128`→`0x5233CD call 0x55353B`→`0x5233E7 call 0x51D710`；ctor 尾 `0x51DD33 lea ecx,[esi+0xa3bd0]`、`0x51DD3E call 0x4a12f0`、`0x51DD43 mov [esi],0x5705d0`；0xA3BD0+0x558=0xA4128。第二对象：`0x512851 push 0xa48b0`→`0x512874 call 0x4FB9A0`；末槽到 0xA48A4，余 12B。
- 冲突：HEAD/工作树 673,988/20；census 673,988/20/36B/2；673,988=673,968+20B 幻影。
- add 草案（两条，A/B 分开，不把归属混进尺寸）：

```text
subject: CCBStage 真尺寸 672,040
authority: A
claim: 唯一 ctor 分配点 push 0xa4128 → operator new → ctor 0x51D710，ctor 末端 0xA3BD0+0x558=0xA4128 与分配逐字节闭合；vptr 0x5705D0 认类。
evidence_refs:
  - docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md:6-14
  - original/PAL3.exe.asm（0x5233BE/0x5233CD/0x5233E7/0x51DD33/0x51DD43）
  - data/annotations/structs/CCBStage.json（WT 673,988/20）
status: open
```

```text
subject: CCBStage 第二对象 673,968 的归属
authority: B
claim: 0x512851 push 0xa48b0 独立分配、256 槽循环末槽到 0xA48A4（余 12B）、全对象清零；offset 0 写描述符指针而非 vptr，20 个注解成员与该对象吻合，归属暂定另一类、类名未定。
evidence_refs:
  - docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md:6-14 与 §2.2/§4.2
  - original/PAL3.exe.asm（0x512851/0x512874/0x4FB9B0/0x4FB9B9/0x4FB9C0）
  - data/status/struct_holes_20261125.json（CCBStage 673,988/20/36B/2）
status: open
```

### 4.4 ④ PropUI：A 级，可随尾部重排卡补

- 源文档：`docs/specs/2026-11-27-propui-size-164-evidence.md:9-26`（§0）、§3.2 可执行性约束、§4 影响面。
- VA/指令：两处 `push 0x70DC`（`0x45975E`、`0x523431`）→`call 0x55353B`→同一 ctor `0x46D140`；ctor 最大写 `0x46D49F [esi+0x70D8]`，终点 0x70DC；0x70DC 以上零访问。
- 冲突：HEAD/工作树 29,056/95；census 29,056/95/18,652B/45，末洞 0x7120-0x7180=96；164=52（mb_OK UIButton 越界）+16（mb_OKRc 幻影）+96（尾垫）。
- add 草案：

```text
subject: PropUI 真尺寸 28,892（0x70DC）
authority: A
claim: 两处 operator new 立即数 0x70DC 相同、同一 ctor 0x46D140、最大写 [esi+0x70D8]+4=0x70DC、0x70DC 以上零访问；164=52+16+96，尺寸与尾部重排必须成对。
evidence_refs:
  - docs/specs/2026-11-27-propui-size-164-evidence.md:9-26
  - original/PAL3.exe.asm（0x45975E/0x523431/0x46D140/0x46D49F）
  - data/annotations/structs/PropUI.json（WT 29,056/95）
  - data/status/struct_holes_20261125.json（29,056/95/18,652B/45）
status: open
```

### 4.5 ⑤ CCBRoleState：B 级总体，A 级只覆盖分配/写界

- 源文档：`docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md:6-13`（§0）、§4.1 尾部 23 员、§5.1 定谳。
- VA/指令：`0x44c5f3 push 0x5058`→`0x44c5f8 call 0x55353B`→`0x44c60e call 0x456ab0`；ctor 最远写 `0x456b2a [esi+0x5054]`，终点 0x5058；vptr `0x456b36` 写 0x56b364；全库 `push 0x56d0` 0 次。
- 冲突：HEAD/工作树 22,224/89；census 22,224/89/6,483B/27；尾部 15+4+3+1=23 员跨类，不能静默删。
- add 草案：

```text
subject: CCBRoleState ctor 写界 20,568 与 22,224 混装
authority: B
claim: 唯一分配 push 0x5058、ctor 最远写 [esi+0x5054]+4=0x5058、vptr 0x56B364 闭合 ctor 不越界；尾部 23 员分属 20,644B 类15、零访问4、CCBUIPanel3、PropUI1，故 22,224 是混装产物，不是单对象尺寸。
evidence_refs:
  - docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md:6-13 与 §4.1
  - original/PAL3.exe.asm（0x44c5f3/0x44c5f8/0x44c60e/0x456b2a/0x456b36）
  - data/annotations/structs/CCBRoleState.json（WT 22,224/89）
  - data/status/struct_holes_20261125.json（22,224/89/6,483B/27）
status: open
```

### 4.6 ⑥ CCCTData：A 级身份反证，D-1 未裁

- 源文档：`docs/specs/2026-11-26-ccctdata-recast-plan.md:9-30`（§1 PDB/类 Y/CCBCam）、§5 D-1（`:241-249`）、§2.1 P-1/P-2。
- 证据：PDB `CCCTData`=430,000 池 union（m_Pool 408,000 + m_bPoolInUse 2,000 + m_nCCTIndex 20,000）；类 Y=402,824 UIListBox 派生，ctor `0x4A6F10`、vptr `0x56F29C`、存 `RoleStatePanel+0x2AFC8`；`CCBCamControl`=430,256（池+256B 尾）。
- 冲突：注解/census 的 `CCCTData` 是 430,256/0/430,256B/1 的 chimera；twin 裁决“类 Y=CCCTData”与 PDB 冲突；**D-1 未裁前 P-1/P-2 都不执行**。
- add 草案（只登记身份反证，不登记施工路线）：

```text
subject: CCCTData 身份反证（430,000 池 union vs 402,824 类 Y）
authority: A
claim: PDB 定义 CCCTData=430,000（池408,000+在位表2,000+索引20,000）；本 exe 402,824 类是未名 UIListBox 派生（ctor 0x4A6F10/vptr 0x56F29C，存 RoleStatePanel+0x2AFC8）；CCBCamControl=430,256（池+256B尾）。现有注解 CCCTData 430,256/0 是 chimera，D-1 未裁前不改。
evidence_refs:
  - docs/specs/2026-11-26-ccctdata-recast-plan.md:9-30 与 §5 D-1
  - original/PAL3.exe.asm（0x4A6F10/0x44F200/0x44F206/0x4A4220）
  - data/annotations/structs/CCCTData.json（WT 430,256/0）
  - data/annotations/structs/CCBCamControl.json（WT 430,256/28）
  - data/status/struct_holes_20261125.json（CCCTData 430,256/0/430,256B/1）
status: open
```

## §5 缺口分级与补登记顺序

### 5.1 分级

**A. Human 拍板前必须补（P0）**

| 项 | 理由 |
|---|---|
| ⑥ 身份反证 | D-1 是“PDB 池 union vs twin 类 Y”的二选一；没有 ev，Human 无法在 P-1/P-2 之间拍板，且执行者会按旧句动手。 |
| ③ 672,040 + 第二对象 | 尺寸虽 A，但“20 个成员迁给 673,968 那个 B 对象”是 B 级归属；决策会直接改 20 个成员，必须留下可挑战的归属条目。 |
| ⑤ 20,568 | 总体定谳是 B 级，尾部 23 员跨四类；没有 ev，删除/迁移就无据，容易把他人字段静默丢掉。 |

**B. 可与落地卡合并补（P1）**

| 项 | 理由 |
|---|---|
| ② C2DSpark | 单链 A 级，尺寸/步长闭合，无身份冲突；第一消费者就是落地卡。 |
| ④ PropUI | 单链 A 级，但“不能单独改尺寸、必须与尾部重排成对”；落地卡本来就要带证据，登记可同步做。 |

> 注意：P1 不是“可以永远不带 id”。上会材料引用②④时必须标“ev 待补”，不能写成已闭合；若 PMO 要求上会零缺口，则②④升 P0，顺序不变。

**C. 只需文档引用（P2）**

- ① 已有 ev_0013/ev_0014，不新增；核对 id 仍指向当前 R6-T1/注解/census 即可。
- ②–⑥ 的“施工步骤、下一卡成员清单、D-1 之后的 P-1/P-2 路线”属方案，留在源文档；台账只登记可裁决的二进制结论。

### 5.2 补登记顺序（≤6 行）

1. ⑥ 身份反证（A）——先登，D-1 才有据可裁。
2. ③ 真尺寸 672,040（A）+ 第二对象 673,968 归属（B）——两条一起登。
3. ⑤ CCBRoleState 20,568 混装（B）——登完再谈 23 员迁移。
4. ② C2DSpark 22,640/44（A）——随②落地卡登记。
5. ④ PropUI 28,892（A）——随尾部重排卡登记。
6. ① 不新增；核对 ev_0013/ev_0014 仍为当前指针，按制度决定是否 resolve。

## §6 census 与文档定谳的冲突

| 类 | HEAD 注解 | 工作树注解 | census（02:12） | 文档定谳 | 处置 |
|---|---|---|---|---|---|
| UITitle_JDHY | 377,700/28 | 290,488/43（M） | 290,488/43/8B/1 | 290,488/43 | census 已随工作树，HEAD 未提交；**不要拿 HEAD 当基线**，落地后重跑 census。 |
| C2DSpark / tagSpark | 24,688/20；48/12 | 同 HEAD | 无条目 | 22,640/44 | 落地后 census 应新增一条 0 洞记录；当前无条目不是“无洞”。 |
| CCBStage | 673,988/20 | 同 HEAD | 673,988/20/36B/2 | 672,040（另对象673,968） | 落地后预期洞 16B/1；当前 36B/2 是旧注解派生。 |
| PropUI | 29,056/95 | 同 HEAD | 29,056/95/18,652B/45 | 28,892/94（尺寸与尾员成对） | 预期 18,540B/44 是派生值，**必须重跑 census 确认**。 |
| CCBRoleState | 22,224/89 | 同 HEAD | 22,224/89/6,483B/27 | 20,568（23员迁出） | 预期 ≤4,915B 是派生值，必须重跑。 |
| CCCTData | 430,256/0 | 同 HEAD | 430,256/0/430,256B/1 | P-1：430,000 池 union + 类 Y 402,824 另立 | D-1 未裁前不改；census 待 P-1 落地后重跑。 |

**统一口径**：以上“预期洞值”都是文档按布局算出的派生值，不是实测；只有重跑 `python3 tools/census_struct_holes.py` 后的数字才能写进 census/验收。

## §7 引用索引与边界

- 台账：`data/status/evidence_ledger.json`（14 条，M，sha256 `f1c1f9a2…2a29`）；当前没有 `evidence_ledger.md` 视图，引用以 JSON 为准。
- 六项源文档：
  - `docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md:9-14`
  - `docs/specs/2026-11-27-r6-t1-uititle-jdhy-placement.md`
  - `docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md:8-11`
  - `docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md:6-14`
  - `docs/specs/2026-11-27-propui-size-164-evidence.md:9-26`
  - `docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md:6-13`
  - `docs/specs/2026-11-26-ccctdata-recast-plan.md:9-30`、`:241-249`
- 现状文件：六项类与 `CCBCamControl` 的注解均在 `data/annotations/structs/` 目录下（同名 JSON 文件）；`data/status/struct_holes_20261125.json`。
- 任务：R6① #22、R6② #29、R6③ #27、R6④ #31、R6⑤ #24、R6⑥ #18；本核对 #38。
- 边界：只新增本文件；没有 `add`、没有改台账/注解/代码/数据/基线；没有跑 apply/export/codegen/probe/loop；没有 commit。所有“应登记/建议”均为草案，执行前需按台账流程批准。
