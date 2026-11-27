# 洞填充语义账：语义名 / 占位名 / gap 声明各换掉多少洞字节

> 只读清点，2026-11-27 22:45 重算当前工作树。数据源：`data/annotations/structs/*.json`（913 类 / 9,174 员）、`data/status/struct_holes_20261125.json`（196 类有洞 / 205,775B）、起点 census `git show 1c0be6473:data/status/struct_holes_20261125.json`（201 类 / 1,168 洞 / 1,513,593B）。本文件是唯一新增物，未改注解/JSON/工具/基线，未跑 apply/export/codegen/probe/match。

## 0. 直接回答「我们填充的是语义名吗？」

**按字节：是，约九成是语义名；按个数：不完全是，新增名字里仍有过半是占位名。** 洞总量从 1,513,593B 降到 205,775B（**−1,307,818B / −86.4%**），逐成员分账为：

- **语义名**：占存量成员字节的 **97.28%**（14,177,484B / 13,845KB）；自起点新增成员中语义名占新增字节 **88.03%**（2,254,305B）、占新增个数 **44.9%**（214/477）。
- **占位名**：占存量字节 **2.71%**（395,019B）；新增成员中占位名占新增字节 **11.97%**（306,641B）、占新增个数 **55.1%**（263/477）。今日新增 279 个名字里占位占 62%（174/279），但只占 10.65% 字节。
- **`_gap_`/`_pad_` 声明**：全库仅 9 员 / 820B（存量字节 **0.0056%**），新增 **0B**，**没有一处是用 gap 声明把洞「记成已填充」的**。

一句话：**洞字节的下降 ≈ 88% 由语义名贡献、≈ 12% 由占位名贡献、0% 由 gap 声明贡献；但新增名字的多数（55%）仍是无语义占位——洞清了，名字还没清。**

## 1. 口径

- 成员占位字节 = 下一成员起始偏移 − 本成员起始偏移（末员用 `binary_size` 收尾），不依赖类型表。
- 名字分类：**语义**（其余）、**占位**（`m_unk_*`、`m_nTodo_*`/`m_todo_*`、`_tail_*`、`<name>_<6 位以上十六进制>` 地址后缀）、**gap 声明**（`_gap_*`、`_pad_*`）。
- 三列口径并列：**(a) 存量**（当前全部成员）、**(b) 增量**（起点提交 → 当前工作树新增名字）、**(c) 按类**（每类的三列字节与占比）。

## 2. 全局三列合计

| 类别 | 成员数 | 字节 | 占成员字节比 |
|---|---|---|---|
| 语义名 | 8567 | 14,177,484 | 97.28% |
| 占位名 | 598 | 395,019 | 2.71% |
| `_gap_`/`_pad_` 声明 | 9 | 820 | 0.01% |
| **合计** | **9,174** | **14,573,323** | 100% |

占位名细分：`m_unk_*` 263、`m_nTodo_*` 240、`_tail_*` 94、地址后缀 1；`_gap_*` 7、`_pad_*` 2。

## 3. 按类三列（有占位或 gap 声明的 147 类）

| 类 | 语义字节 | 占位字节 | gap 字节 | 占位占比 | 现存洞字节 |
|---|---|---|---|---|---|
| UITitle_JDHY | 129,588 | 160,828 | 0 | 55.4% | 8 |
| SaleUI | 264 | 105,576 | 0 | 99.8% | 0 |
| PropUI | 17,660 | 11,324 | 0 | 39.1% | 18,652 |
| UIScenePanel | 3,522 | 10,642 | 0 | 75.1% | 285 |
| MainPropUI | 210,344 | 9,568 | 0 | 4.4% | 0 |
| RoleStatePanel | 168,647 | 7,521 | 0 | 4.3% | 556 |
| LineupUI | 156,348 | 6,352 | 0 | 3.9% | 210 |
| elelife_emitter_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| direction_emitter_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| rotation_particle_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| sizemulti_emitter_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| rgbcolor_particle_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| elerandvec_emitter_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| vertexalpha_particle_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| emissionrate_emitter_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| rotmulti_emitter_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| size_particle_graph | 0 | 5,300 | 0 | 100.0% | 0 |
| RenderTarget2 | 0 | 4,292 | 0 | 100.0% | 0 |
| RoleSystem | 4,997 | 3,636 | 3 | 42.1% | 5,522 |
| PAL3 | 1,608 | 3,328 | 0 | 67.4% | 4,540 |
| PathObj | 4,152 | 3,056 | 0 | 42.4% | 3,048 |
| UITitle | 7,212 | 2,232 | 0 | 23.6% | 18 |
| EquipUI | 264,285 | 1,903 | 0 | 0.7% | 0 |
| Logger | 4,856 | 1,504 | 0 | 23.6% | 1,596 |
| tagEffMgrData | 0 | 1,500 | 0 | 100.0% | 0 |
| TextureLib_Data | 0 | 1,116 | 0 | 100.0% | 0 |
| CCBUIPanel | 21,124 | 916 | 0 | 4.2% | 284 |
| ScriptSystem | 7,833 | 871 | 0 | 10.0% | 8,446 |
| tagCombatTimerState | 9 | 860 | 0 | 99.0% | 836 |
| SwordUI | 401,997 | 755 | 0 | 0.2% | 536 |
| CCBRoleState | 19,816 | 680 | 0 | 3.3% | 4,486 |
| tagCpkAudioOvl | 916,848 | 0 | 656 | 0.1% | 0 |
| PalScriptMgr | 8,897 | 615 | 0 | 6.5% | 8,741 |
| CUtil | 1,372 | 400 | 0 | 22.6% | 1,214 |
| ScriptVM | 656 | 228 | 0 | 25.8% | 784 |
| CameraCtrl | 3,907 | 181 | 0 | 4.4% | 3,467 |
| UIItem | 8 | 156 | 0 | 95.1% | 136 |
| UI3DModelNode | 0 | 156 | 0 | 100.0% | 64 |
| _Console__ConCmd | 0 | 136 | 0 | 100.0% | 0 |
| ScriptSystemData | 4,024 | 104 | 0 | 2.5% | 2,008 |
| RenderTargetNode | 0 | 96 | 0 | 100.0% | 0 |
| PalScript | 2,012 | 96 | 0 | 4.6% | 555 |
| DPINFO___unnamed | 0 | 96 | 0 | 100.0% | 0 |
| NPC | 1,060 | 88 | 0 | 7.7% | 756 |
| SceneMgrCamBlock | 680 | 4 | 84 | 11.5% | 0 |
| SkillUI | 101,785 | 83 | 0 | 0.1% | 0 |
| CCBAI | 3,592 | 72 | 0 | 2.0% | 144 |
| UIInventory | 0 | 68 | 0 | 100.0% | 0 |
| UITextArea | 56 | 68 | 0 | 54.8% | 0 |
| C3DSpark_tagSpark | 0 | 56 | 0 | 100.0% | 0 |
| tagRoleTaskData | 24 | 0 | 48 | 66.7% | 12 |
| RoleCamera | 620 | 44 | 0 | 6.6% | 32 |
| CCBStageRole | 6,804 | 44 | 0 | 0.6% | 53 |
| TaskMgr_SceneObjParam_SceneObj | 0 | 40 | 0 | 100.0% | 36 |
| Role_SPECIAL_ACTION | 0 | 36 | 0 | 100.0% | 0 |
| SceneObj_SubObj | 0 | 36 | 0 | 100.0% | 0 |
| InputSystem | 0 | 36 | 0 | 100.0% | 0 |
| EffMultiPassNode | 0 | 32 | 0 | 100.0% | 0 |
| UIRenderObj | 0 | 32 | 0 | 100.0% | 0 |
| EffCallBackNode | 0 | 32 | 0 | 100.0% | 0 |
| EffBinkNode | 0 | 32 | 0 | 100.0% | 0 |
| EffAudioNode | 0 | 32 | 0 | 100.0% | 0 |
| CCBStage | 673,869 | 31 | 0 | 0.0% | 36 |
| CEffGroupNode | 0 | 24 | 0 | 100.0% | 0 |
| RenderTarget | 176 | 24 | 0 | 12.0% | 32 |
| Scene | 493,132 | 20 | 0 | 0.0% | 368 |
| PlayerAtts | 0 | 16 | 0 | 100.0% | 196 |
| GeomNode | 272 | 16 | 0 | 5.6% | 128 |
| CLoad3DS | 24 | 12 | 0 | 33.3% | 0 |
| Camera | 532 | 12 | 0 | 2.2% | 348 |
| UIManager | 3,744 | 0 | 12 | 0.3% | 0 |
| WeatherEffectNode | 0 | 8 | 0 | 100.0% | 0 |
| SceneVisNode | 0 | 8 | 0 | 100.0% | 0 |
| ParticleVisNode | 0 | 8 | 0 | 100.0% | 0 |
| tagCmdDataDestRoleView | 4 | 0 | 7 | 63.6% | 0 |
| UIScene | 269 | 7 | 0 | 2.5% | 134 |
| UIRoleDialog | 1,290 | 2 | 4 | 0.5% | 0 |
| UIButton_UIBUTTON_STATE | 0 | 4 | 0 | 100.0% | 0 |
| gbMeshData | 0 | 4 | 0 | 100.0% | 0 |
| OpenSceneFile | 0 | 4 | 0 | 100.0% | 0 |
| CameraSystem | 0 | 4 | 0 | 100.0% | 0 |
| std | 0 | 4 | 0 | 100.0% | 0 |
| UIParabolaCtrl | 0 | 4 | 0 | 100.0% | 0 |
| CFadeOutAlphaPolicy | 0 | 4 | 0 | 100.0% | 0 |
| Parent_Data | 0 | 4 | 0 | 100.0% | 0 |
| MvcController | 0 | 4 | 0 | 100.0% | 0 |
| SoundContext | 0 | 4 | 0 | 100.0% | 0 |
| SaleUI_SortData | 0 | 4 | 0 | 100.0% | 0 |
| UIStaticFlex_State | 0 | 4 | 0 | 100.0% | 0 |
| CParticleSystem_ParticleUnit | 0 | 4 | 0 | 100.0% | 0 |
| Math | 0 | 4 | 0 | 100.0% | 0 |
| UIQuadManager | 0 | 4 | 0 | 100.0% | 0 |
| CSimplePosPolicy | 0 | 4 | 0 | 100.0% | 0 |
| CParticleSystem_ParticleAttribute | 0 | 4 | 0 | 100.0% | 0 |
| ScriptObj | 0 | 4 | 0 | 100.0% | 0 |
| VideoPlayer | 0 | 4 | 0 | 100.0% | 0 |
| CCentripetalPolicy | 0 | 4 | 0 | 100.0% | 0 |
| CEffectSimple | 0 | 4 | 0 | 100.0% | 0 |
| gbVolumeModifier | 0 | 4 | 0 | 100.0% | 0 |
| ScriptHelper | 0 | 4 | 0 | 100.0% | 0 |
| String | 12 | 0 | 4 | 25.0% | 0 |
| gbSceneNode | 0 | 4 | 0 | 100.0% | 0 |
| RenderTarget4 | 0 | 4 | 0 | 100.0% | 0 |
| Iostream_init | 0 | 4 | 0 | 100.0% | 0 |
| UIObj | 0 | 4 | 0 | 100.0% | 0 |
| MiniGame3 | 0 | 4 | 0 | 100.0% | 0 |
| CEffectBubble | 0 | 4 | 0 | 100.0% | 0 |
| PalScriptIdleObj | 4 | 4 | 0 | 50.0% | 0 |
| CFadeInAlphaPolicy | 0 | 4 | 0 | 100.0% | 0 |
| UIListView | 0 | 4 | 0 | 100.0% | 0 |
| UISceneObj | 0 | 4 | 0 | 100.0% | 0 |
| MatrixStack | 0 | 4 | 0 | 100.0% | 0 |
| UIGameFrm | 28,196 | 4 | 0 | 0.0% | 256 |
| Combat | 0 | 4 | 0 | 100.0% | 0 |
| UICamera | 504 | 4 | 0 | 0.8% | 508 |
| TileMap | 0 | 4 | 0 | 100.0% | 0 |
| MiniGame2Scene | 0 | 4 | 0 | 100.0% | 0 |
| filebuf | 0 | 4 | 0 | 100.0% | 0 |
| CG_Scene_ArrayErase | 0 | 4 | 0 | 100.0% | 0 |
| ParabolaCalculator_PRBL_STATE | 0 | 4 | 0 | 100.0% | 0 |
| VertPoolMgr | 0 | 4 | 0 | 100.0% | 0 |
| collision | 0 | 4 | 0 | 100.0% | 0 |
| UISlider | 0 | 4 | 0 | 100.0% | 0 |
| CSimpleDirPolicy | 0 | 4 | 0 | 100.0% | 0 |
| UIBase | 0 | 4 | 0 | 100.0% | 0 |
| CRenderTarget2 | 0 | 4 | 0 | 100.0% | 0 |
| CRenderTarget | 0 | 4 | 0 | 100.0% | 0 |
| CDamplyCentripetalPolicy | 0 | 4 | 0 | 100.0% | 0 |
| UIAnimCtrl | 0 | 4 | 0 | 100.0% | 0 |
| SPECIAL_ACTION | 0 | 4 | 0 | 100.0% | 0 |
| gbFileStream | 0 | 4 | 0 | 100.0% | 0 |
| ExternalStatistics | 0 | 4 | 0 | 100.0% | 0 |
| ECBRoleSpecState | 0 | 4 | 0 | 100.0% | 0 |
| MvcViewport | 0 | 4 | 0 | 100.0% | 0 |
| UIScrollBar_SB_AREA | 0 | 4 | 0 | 100.0% | 0 |
| SoundSystem | 0 | 4 | 0 | 100.0% | 0 |
| tagEffClass | 0 | 4 | 0 | 100.0% | 0 |
| MeshFxCreator | 0 | 4 | 0 | 100.0% | 0 |
| gbRenderEffect_D3D | 0 | 4 | 0 | 100.0% | 0 |
| MiniGame1 | 0 | 4 | 0 | 100.0% | 0 |
| SceneObj_Common_State | 0 | 4 | 0 | 100.0% | 0 |
| CRandomColorPolicy | 0 | 4 | 0 | 100.0% | 0 |
| UISelectDialog | 0 | 4 | 0 | 100.0% | 0 |
| CAccelCentripetalPolicy | 0 | 4 | 0 | 100.0% | 0 |
| NameSys_NAMEFLAG | 0 | 4 | 0 | 100.0% | 0 |
| UIBigDialog | 0 | 4 | 0 | 100.0% | 0 |
| tagPartyInitView | 400 | 0 | 2 | 0.5% | 0 |
| （其余 766 类，全语义名） | 10,498,449 | 0 | 0 | 0.0% | — |

## 4. 洞下降归因（三种独立口径互证）

| 口径 | 结果 |
|---|---|
| 洞 census 净变化 | 1,513,593B → 205,775B，**−1,307,818B（−86.4%）** |
| 起点→当前新增成员（按 span 计） | 477 员 / 2,560,946B = 语义 2,254,305B（88.03%）+ 占位 306,641B（11.97%）+ gap 0B |
| `binary_size` 未变的 13 个可比类 | 吸收洞 900,144B；新增 1,340,744B = 语义 1,206,753B（90.0%）+ 占位 133,991B（10.0%）+ gap 0B |
| 起点洞被新成员覆盖的 269 处（原洞 924,707B） | 语义成员覆盖 856,404B（196 处）/ 占位成员覆盖 68,303B（73 处）/ gap 声明覆盖 0B（0 处） |

> 269 处 ≠ census 的 1,168→910 洞差：部分旧洞只是「起点变了」而不是消失（相邻成员挪位后洞从某偏移开始），这里只统计**起点提交里存在、当前已不存在**的洞，故口径偏保守；但三条口径都指向同一结论（语义 ≈ 88–90%、占位 ≈ 10–12%、gap ≈ 0）。

## 5. 靠 `_gap_*` / 占位名把洞抹掉的类（按字节）

**gap 声明抹洞：0 处 / 0B** —— 起点提交里消失的 269 处洞中，没有任何一处是被 `_gap_*`/`_pad_*` 成员覆盖的（全库这类声明只有 9 员 824B）。


**占位名抹洞：73 处 / 68,303B** —— 这些区间的洞消失了，但覆盖它的成员名字仍是无义占位（洞清了、名字没清）。

| 类 | 原洞区间 | 原洞字节 | 覆盖的占位成员 |
|---|---|---|---|
| SaleUI | 0x4c4–0x46b4 | 16,880 | `m_unk_0x178` |
| SaleUI | 0xf1c0–0x13064 | 16,036 | `m_unk_0x11558_view` |
| MainPropUI | 0x33d1c–0x35b50 | 7,732 | `m_unk_0x3498C` |
| SaleUI | 0x5e10–0x756c | 5,980 | `m_unk_0x66f4_view` |
| UIScenePanel | 0x13e4–0x20e0 | 3,324 | `m_unk_0x13e4` |
| UIScenePanel | 0x20e4–0x2900 | 2,076 | `m_unk_0x20e4` |
| RoleStatePanel | 0x2a800–0x2afbc | 1,980 | `m_unk_0x2ab08` |
| UIScenePanel | 0x488–0x978 | 1,264 | `m_unk_0x488` |
| UIScenePanel | 0xef4–0x13e0 | 1,260 | `m_unk_0xef4` |
| SaleUI | 0x1946c–0x1992c | 1,216 | `m_unk_0x196c4` |
| SaleUI | 0x18f60–0x19420 | 1,216 | `m_unk_0x192ac` |
| SaleUI | 0x18a54–0x18f14 | 1,216 | `m_unk_0x189a4` |
| SaleUI | 0x19930–0x19db8 | 1,160 | `m_unk_0x19974` |
| UITitle | 0x1cfc–0x210c | 1,040 | `m_unk_0x1cfc` |
| UITitle | 0x2110–0x2510 | 1,024 | `m_unk_0x2110` |
| UIScenePanel | 0x208–0x486 | 638 | `m_unk_0x208` |
| CCBRoleState | 0x4e64–0x4fb8 | 340 | `m_unk_0x4E60` |
| SaleUI | 0x348–0x488 | 320 | `m_unk_0x178` |
| RoleStatePanel | 0x64–0x169 | 261 | `m_unk_0x68` |
| UIScenePanel | 0xe00–0xef0 | 240 | `m_unk_0xe00` |

## 6. 正名优先级 top15

| # | 类 | 占位个数 | 占位字节 | 现存洞字节 | 先做理由 |
|---|---|---|---|---|---|
| 1 | SaleUI | 61 | 105,576 | 0 | 占位 61 个 / 105,576B，最大一块 `m_unk_0x66f4_view` 36,480B@0x66f4；现存洞 0B |
| 2 | UIScenePanel | 56 | 10,642 | 285 | 占位 56 个 / 10,642B，最大一块 `m_unk_0x13e4` 3,324B@0x13e4；现存洞 285B |
| 3 | RoleStatePanel | 39 | 7,521 | 556 | 占位 39 个 / 7,521B，最大一块 `m_unk_0x2ab08` 840B@0x2ab08；现存洞 556B |
| 4 | LineupUI | 33 | 6,352 | 210 | 占位 33 个 / 6,352B，最大一块 `m_unk_0x268d4` 344B@0x268d4；现存洞 210B |
| 5 | UITitle_JDHY | 31 | 160,828 | 8 | 占位 31 个 / 160,828B，最大一块 `m_unk_0x12F0` 74,752B@0x12f0；现存洞 8B |
| 6 | PAL3 | 27 | 3,328 | 4,540 | 占位 27 个 / 3,328B，最大一块 `m_nTodo_894` 1,036B@0x894；现存洞 4,540B |
| 7 | PropUI | 21 | 11,324 | 18,652 | 占位 21 个 / 11,324B，最大一块 `m_nTodo_1118` 9,520B@0x1118；现存洞 18,652B |
| 8 | MainPropUI | 21 | 9,568 | 0 | 占位 21 个 / 9,568B，最大一块 `m_unk_0x3498C` 1,824B@0x3498c；现存洞 0B |
| 9 | EquipUI | 19 | 1,903 | 0 | 占位 19 个 / 1,903B，最大一块 `m_unk_0x294` 152B@0x294；现存洞 0B |
| 10 | PalScriptMgr | 18 | 615 | 8,741 | 占位 18 个 / 615B，最大一块 `m_nTodo_CE9` 391B@0xced；现存洞 8,741B |
| 11 | ScriptSystem | 17 | 871 | 8,446 | 占位 17 个 / 871B，最大一块 `m_nTodo_10C` 180B@0x10c；现存洞 8,446B |
| 12 | ScriptSystemData | 15 | 104 | 2,008 | 占位 15 个 / 104B，最大一块 `m_nTodo_FB0` 32B@0xfb0；现存洞 2,008B |
| 13 | RoleSystem | 14 | 3,636 | 5,522 | 占位 14 个 / 3,636B，最大一块 `dword_17AA450` 2,188B@0x1968；现存洞 5,522B |
| 14 | SkillUI | 12 | 83 | 0 | 占位 12 个 / 83B，最大一块 `m_unk_0x638` 32B@0x638；现存洞 0B |
| 15 | ScriptVM | 8 | 228 | 784 | 占位 8 个 / 228B，最大一块 `m_nTodo_20` 128B@0x20；现存洞 784B |

## 7. 附录：复算命令

```bash
python3 /tmp/ccct70/analyze.py       # 存量三列 + top15
python3 /tmp/ccct70/delta.py         # 起点 → 当前新增（按 span）
python3 /tmp/ccct70/delta_start.py   # 起点提交口径（1c0be6473）
python3 /tmp/ccct70/delta2.py        # 今日新增（按名字）
python3 /tmp/ccct70/attrib.py        # size 稳定的 13 类归因
python3 /tmp/ccct70/build_final.py   # 按类三列 + 覆盖归因
python3 /tmp/ccct70/build_md.py      # 生成本文档
```
