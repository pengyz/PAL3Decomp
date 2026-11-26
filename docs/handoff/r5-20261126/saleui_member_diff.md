# SaleUI 重建草案 vs 现有注解（R5）

- 现有注解成员 62 条；草案成员 55 条。
- 草案覆盖 0x48–0x19DB8 共 98156 B / 105840 B = 92.7%。
- 剩余无证据缺口 7684 B：0xf574(3840B)、0x10564(4B)、0x10658(3840B)。
- 洞区 44,560B → 预计 7,684B（降幅约 36876 B ≈ 36.0KB）。

## 被撤销的既有成员（逐条附归属判断）

| 偏移 | 名称 | 类型 | 落在草案哪段内 | 判断 |
|---|---|---|---|---|
| 0x0250 | m_SelNum | int | 0x178 m_unk_0x178 | 位面视图或真错，需裁决 |
| 0x0254 | m_data | st_Manager | 0x178 m_unk_0x178 | 位面视图或真错，需裁决 |
| 0x0488 | m_inventory | Inventory | 0x178 m_unk_0x178 | 位面视图或真错，需裁决 |
| 0x04b0 | m_reoccupy | Reoccupy | 0x178 m_unk_0x178 | 位面视图或真错，需裁决 |
| 0x04c0 | dwWeaponWU | int | 0x178 m_unk_0x178 | 位面视图或真错，需裁决 |
| 0x46b4 | m_sort | int[299][5] | 0x45dc m_unk_0x45dc | 位面视图或真错，需裁决 |
| 0x756c | m_ListSelNum | int[299][5] | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0x8cc8 | m_Max | int[299][5] | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0xa424 | m_Sum | int[5] | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0xa438 | _isCreatable | unsigned char | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0xa43c | m_SaleData | PlayerItem[299][5] | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0xea50 | m_TempData | PlayerItem[158] | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0xf1b8 | m_bNGHS | int | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0xf1bc | m_bWPXS | int | 0x66f4 m_unk_0x66f4 | 位面视图或真错，需裁决 |
| 0x13064 | m_NotesNull | int[299][5] | 0x11558 m_unk_0x11558 | 位面视图或真错，需裁决 |
| 0x147c0 | m_IsEquip | unsigned char[299][5] | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x14d97 | m_TempIsEquip | unsigned char[299][5] | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15370 | x | int | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15374 | rc | tagRECT | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15384 | m_Frame | UIStatic | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15424 | m_FrameBar | UIFlexBar | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15478 | m_Flag | UIStatic | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15518 | m_OutFrameT | UIStatic | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x155b8 | m_OutFrameR | UIStatic | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15658 | m_OutFrameL | UIStatic | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x156f8 | m_OutFrameB | UIStatic | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15798 | mb_Exit | UIButton | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x158f0 | m_ExitRc | tagRECT | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15900 | m_ani | UIAnimateCtrl | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x159a4 | m_Role | UIStatic[5] | 0x14618 m_unk_0x14618 | 位面视图或真错，需裁决 |
| 0x15cc4 | m_RoleRc | tagRECT[5] | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x15d14 | RoleX | int | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x15d18 | RoleY | int | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x15d1c | HeadW | int | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x15d20 | HeadH | int | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x15d24 | m_Is | unsigned char[5] | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x15d2c | m_Msg | MUIDialog | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16294 | m_3DObj | UI3DCtrl | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x163c8 | m_FlagRc | tagRECT | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x163d8 | m_TalkFrame | UIStatic | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16478 | m_Ready | UIStatic | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16518 | m_ReadyRc | tagRECT | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16528 | m_entryTalk | char[256] | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16628 | m_btn | UIButton[5] | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16ce0 | m_TabRc | tagRECT | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16cf0 | m_ListSaleTitle | UIStatic | 0x15b30 m_unk_0x15b30 | 位面视图或真错，需裁决 |
| 0x16d90 | m_ListEquipTitleRc | tagRECT | 0x16d00 m_unk_0x16d00 | 清零区内的标量，可能真错 |
| 0x16da0 | m_Icon | UIStaticRM[5][5] | 0x16d00 m_unk_0x16d00 | 清零区内的标量，可能真错 |
| 0x17ffc | m_ListFrame | UIStatic | 0x17a9c m_unk_0x17a9c | 位面视图或真错，需裁决 |
| 0x1809c | m_ScrollHB | UIStatic | 0x17a9c m_unk_0x17a9c | 位面视图或真错，需裁决 |
| 0x1813c | m_ListGrid | UIStatic[14] | 0x17a9c m_unk_0x17a9c | 位面视图或真错，需裁决 |
| 0x189fc | m_ListRc | tagRECT | 0x189a4 m_unk_0x189a4 | 清零区内的标量，可能真错 |
| 0x18a0c | ml_ResumeList | UIListBox | 0x189a4 m_unk_0x189a4 | 清零区内的标量，可能真错 |
| 0x18f14 | ResumeNum | int | 0x18e70 m_unk_0x18e70 | 清零区内的标量，可能真错 |
| 0x18f18 | ml_TreasureList | UIListBox | 0x18e70 m_unk_0x18e70 | 清零区内的标量，可能真错 |
| 0x19420 | TreasureNum | int | 0x19414 m_unk_0x19414 | 清零区内的标量，可能真错 |
| 0x19424 | ml_AttackList | UIListBox | 0x19414 m_unk_0x19414 | 清零区内的标量，可能真错 |
| 0x1992c | AttackNum | int | 0x1981c m_unk_0x1981c | 清零区内的标量，可能真错 |

## 证据等级

- 草案 55 条中 54 条为 A 级（ctor 写序 / ??_L·??_M 三元组 / ctor-dtor 邻接双证），`buf` 1 条维持 unverified（本轮未取得证据）。
- 未使用任何 PDB 单证；IDB 尺寸只在与邻接间距一致时引用（UIRoleDialog 1368、UIFrameContainer 152、CCBResultWindow 180），不一致的（UI3DCtrl、PalScript）按邻接间距记并在 source 里写明理由。

## 离线 check 验证（2026-11-26 21:12，未动仓库）

把草案作为 `data/annotations/structs/SaleUI.json` 放进 `data/annotations` 的**离线副本**（/tmp/r5_check/annotations），再以 `pipeline.check_annotations.check()` 跑（把模块 `ANN_DIR` 指向副本）：

| 运行 | errors | warnings |
|---|---|---|
| 现树（baseline） | 20 | 12 |
| 草案（候选） | 20 | 12 |
| 差集 | **NEW 0 / GONE 0** | NEW 0 |

- 首次跑出 2 条 NEW：`m_unk_0x6204(UI3DCtrl, size=308)@25092 ends@25400 > next m_unk_0x6258@25176` 与 `m_unk_0x62f0(PalScript, size=2176)@25328 ends@27504 > next m_unk_0x6394@25492`——原因是 check 会按类名查结构体尺寸（UI3DCtrl=308 / PalScript=2176），盖过我按邻接算出的 84B / 164B。
- 改法：这两条改成 `unsigned char[84]` / `unsigned char[164]`（source 里写明「ctor 调用目标是 ??0UI3DCtrl / ??0PalScript，但 IDB 该类尺寸与本类邻接间距矛盾，故按邻接字节留白」）。重跑后 NEW 0。
- 过程未写仓库：`git status` 里出现的改动（evidence_ledger.json、pipeline/_logs/*、thirdparty/*）是他人在跑的管线改动，与本验证无关。

## census v3 实测（2026-11-26 21:20，离线副本）

用 `tools/census_struct_holes.py` 的 `main()`，把 `STRUCT_DIR` 指向离线副本、`OUT_PATH` 指到 /tmp 跑：

| 口径 | SaleUI 洞数 | SaleUI 洞字节 | 全库洞字节 | 全库洞数 |
|---|---|---|---|---|
| 现树 baseline | 23 | 44,560 | 1,275,908 | 1,142 |
| 草案 | 17 | **9,518** | **1,240,866** | 1,136 |

- 全库降幅 = 1,275,908 − 1,240,866 = **35,042B ≈ 34.2KB**。
- 三类合计 116,128B → 81,586B（−34,542B），与「72–88KB」验收带差得远——这是 A 方案把验收带必须改成实测口径的直接依据。
- 草案残留 17 洞中，3,840+3,840+4=7,684B 是真缺口；余下 1,834B 来自「声明类型尺寸 < 邻接段长」：
  · 7 处 `UICaption` 段各 344B，但结构表里 UICaption=96B ⇒ 每段余 248B 被计成洞（7×248=1,736B）；
  · 6 处 `UIFrameContainer` 段各 168B（类尺寸 152B）⇒ 每段余 16B（6×16=96B）；另有 2B。
- 结论：若把上述 13 处按「邻接段长」改成字节留白，残留可降到约 7,782B；但这会丢掉 UICaption/UIFrameContainer 的类型信息，需先定谳「本类里 UICaption 到底是 96B 还是 344B」——这是下一步取证项，不是本轮能拍的。

## 待定谳：344B 段到底是什么类（下一步取证项）

- IDB 结构表：`UICaption = 96`，而拆除侧在这些段上调的是 `?Destroy2@UICaption@@QAEXXZ`（继承方法），段长实测 344B。
- 同尺寸候选：`UIButton = 344`、`UIScene = 344`；另有 `UIButtonEXA = 376`、`UIAnimateCtrl = 164`、`CEffectSystem = 360`、`NavigationInfo = 364`。
- 推测：344B 段更可能是 **UIButton**（派生自 UICaption，调继承的 Destroy2 自然），`0x62F0` 的 164B 段更可能是 **UIAnimateCtrl**（164 与邻接完全吻合），而不是构造侧注解里写的 PalScript。
- 若成立，残留能从 9,518B 降到约 7,782B 且不丢类型；验证方法：读 UIButton 的 ctor/dtor 体，确认其是否调用 UICaption::Destroy2，并比对 ctor 写序末尾字段（如 `[esi+0x150]` 段）。

## 21:30 修正：按「段长」字节闭合后重测

把「声明类型尺寸 ≠ 邻接段长」的 13 处改成字节留白（`unsigned char[段长]`），其余不动，重跑离线 check + census：

| 口径 | SaleUI 洞数 | SaleUI 洞字节 | 全库洞字节 | 全库洞数 |
|---|---|---|---|---|
| baseline | 23 | 44,560 | 1,275,908 | 1,142 |
| 草案（首版，按类名定型） | 17 | 9,518 | 1,240,866 | 1,136 |
| 草案（21:30 修正，字节闭合） | **3** | **7,684** | **1,239,032** | **1,122** |

- check 仍 **NEW 0 / GONE 0**（base 20 errors / 12 warns，cand 20/12）。
- 草案 55 成员、零重叠、覆盖 98,156B、缺口 7,684B（= 0xF574 3,840B + 0x10658 3,840B + 0x10564 4B，三处 ctor/dtor 均无构造证据）。
- 三类合计 44,652 + 27,916 + 7,684 = **80,252B**（原 116,128B），全库降 **36,876B ≈ 36.0KB**。

## 一条独立发现：UICaption 的 binary_size 字段是陈旧的

- `data/annotations/structs/UICaption.json`：`binary_size: 96`，但同文件 `size_evidence` 明写「96 → 344（A 级 new-ctor 三元组：push 0x158(344)）」。
- IDB 侧复核：0x4A79F3–0x4A7A10 是 `??_M`（析构迭代器），压栈 `dtor=?Destroy2@UICaption` / count=5 / ptr=esi+0x2BD34 / size=0x158(344) ⇒ 被析构元素确实是 344B，且 dtor 名挂在 UICaption 上。
- 另外 `?GetSys@NameSys@@QACPAV1@XZ`(0x43A770) 实测写 vtable `off_56AC70`、`rep stosd` 到 `[esi+0x154]`，是**构造函数**而非 getter；IDB 名字不可信。
- 结论：SaleUI 里 7 处 344B 段按 `UICaption` 定型在语义上可能没错，错的是**尺寸表(96)**。这属于结构表/导出层的独立缺陷，不在本卡 writeScopes 的修复范围，已作为发现上报，不在 R5 里顺手改。

## ⚠️ 落地风险：草案要撤的成员里有 22 个正在被语料具名引用

用 `asm/pal3/decomp/*.json` 扫「函数体内出现某个 SaleUI 成员名」：62 个旧成员里 **22 个**在 `SaleUI::ConsumeItems` / `DestroySubFrames` / `CreatePanelElements` / `InitCombatUI` / `HandleInput` 等函数体里被具名引用（如 `this->m_sort` / `this->ml_ResumeList` / `this->m_Icon`）。

它们**全部**落在草案的字节区里：

| 被引用成员 | 偏移 | 落在草案哪个 span |
|---|---|---|
| buf / remarkbuf / m_data / dwWeaponWU | 0x50 / 0x150 / 0x254 / 0x4C0 | 0x178 起 17,504B 清零区 |
| m_sort | 0x46B4 | 0x45DC 起 7,040B（5×1,408B 记录区） |
| m_ListSelNum / m_bWPXS | 0x756C / 0xF1BC | 0x66F4 起 36,480B（240×152B 池） |
| m_NotesNull | 0x13064 | 0x11558 起 12,480B（240×52B 池） |
| m_IsEquip / m_Role | 0x147C0 / 0x159A4 | 0x14618 起 5,400B（30×180B 池） |
| m_RoleRc / m_Msg / m_ListSaleTitle | 0x15CC4 / 0x15D2C / 0x16CF0 | 0x15B30 起 4,560B（30×152B 池） |
| m_ListEquipTitleRc / m_Icon | 0x16D90 / 0x16DA0 | 0x16D00 起 176B |
| m_ListGrid | 0x1813C | 0x17A9C 起 1,976B（13×152B 池） |
| ml_ResumeList / ml_TreasureList / ml_AttackList / AttackNum | 0x18A0C / 0x18F18 / 0x19424 / 0x1992C | 0x189A4/0x18E70/0x19414/0x1981C 字节区 |

含义：
1. 这些「具名视图」是 IDB UDT 里的字段名，Hex-Rays 就是按它们生成 `this->m_sort[...]` 的；把成员删掉，下一轮 export 会把这些访问退化成裸偏移，生成代码大面积改写，S2 可能抖动。
2. 池（`??_L` 三元组，A 级）与这些成员**不是简单的谁对谁错**：240×152B 池与 `int[299][5]` 网格是同一段内存的两种解释——真按共享内存建模，应走 inline union（spec 允许，check 也认 `type={"union":...}`），而不是删一侧。
3. 字节留白版把洞算到 7,684B 是**记账正确**，但**语义上是丢一侧视图**；按 union 建模同样能把洞压到 7,684B 且保留具名视图，代价是 union 写法复杂、check 需要逐条确认。

⇒ 建议 A 方案落成 **A′**：洞用 union 闭合、保留 22 条具名视图；若主理人要求最快落地，则用现草案（删视图）但要预期 S2/生成树抖动需归因。这条已写进给 lead 的裁定请求。

## 第三种方案 A″：纯增量（不删任何既有成员）

顾虑「删 22 条具名视图会改生成代码」之后，做了一版**不删成员**的对照：只往洞里加 `m_unk_<off> unsigned char[N]`，且只加在「ctor 清零跨度覆盖」的洞段（A/B 级证据），其余洞保留为缺口。

| 方案 | 做法 | SaleUI 洞 | SaleUI 洞字节 | 全库洞字节 | 全库降幅 | 既有成员 |
|---|---|---|---|---|---|---|
| A | 按池/邻接重建，删 58 条 | 3 | 7,684 | 1,239,032 | **−36,876B** | 改（丢 22 条具名视图） |
| A′ | A 的口径 + union 保留具名视图 | 3 | 7,684 | 1,239,032 | −36,876B | 保（union 写法复杂） |
| A″ | 纯增量，只填空零区 | 22 | 26,736 | 1,258,084 | **−17,824B** | 全保、零删除 |

- A″ 的 check 同样 **NEW 0 / GONE 0**（base 20/12，cand 20/12）。
- A″ 只覆盖了 3 个洞（16,860B + 844B + 120B 量级），其余 19 个洞不在清零跨度内，按「无证据不占位」原则留白。

三个方案的取舍已经很清楚：**要 36.9KB 就必须动既有成员（A 删 / A′ union）；不动成员最多 17.8KB。**

## A′ 可行性验（union 形态能不能过 check）

在草案基础上，把 0x178 的 17,504B 字节区改成 union：一侧是 `unsigned char[17504]`，另一侧是内联 struct（`offset` 用相对偏移 0xDC/0x310/0x338/0x348 放回 `m_data`/`m_inventory`/`m_reoccupy`/`dwWeaponWU`）。

结果：check **NEW 0 / GONE 0**（base 20 errors/12 warns，cand 20/12），census 仍 SaleUI 3 洞/7,684B、全库 1,239,032/1,122。⇒ **union 形态在 check 层是可行的**，A′ 不是空想。

但做全量 A′ 时撞上一个语义硬约束：`m_NotesNull`@0x13064 声明 `int[299][5]`（5,980B，到 0x147C0），而 0x14618 是 `CCBResultWindow[30]` 池的起点（A 级 `??_L` 站点）。**一个数组成员不可能横跨到下一个成员体内** ⇒ 旧网格视图至少这一条在尺寸上就是错的，union 也救不了（union 成员不能超出并集跨度）。

所以严格说：A′ 能保住的只是「不越界的那部分视图」，`m_NotesNull` 这类越界视图无论如何要改。这进一步支持 A（按 A 级池重建、删未验证网格视图）是**证据驱动的结论**，不只是图快。

## A 方案的影响面（不是全库炸裂）

扫全部 3,589 个 decomp JSON 找 62 个旧成员名：命中 602 个文件是误报（`buf`/`x`/`rc`/`m_Is` 这类通用名撞了别的类）。按「函数体里有 SaleUI 成员引用且属于 SaleUI 方法」筛，真正受影响的是：

**SaleUI 的 29 个方法**（InitColumnWidths / HandleInput / GetValue / ToggleSlot0–4 / Update / InitCombatUI / CreatePanelElements / LoadState / SetupPlayerDisplay / DestroySubFrames / ConsumeItems / ctor / dtor / SetRange / AddItem / GetCellStateByte / ResetGridState / SetSelectionFlags / UpdateSkillPanel / SendInputToRole / InitMode / SetValue / OnMessage_19 等），另加 `EquipUI::InitEquipUI`（共用 `buf` 名）。

⇒ 删视图的编译影响面 = **SaleUI.cpp 一个翻译单元（29 个函数）+ EquipUI.cpp 的 1 个函数**，S2 若抖动也集中在那里，便于按「衰退纪律」定位与归因。
