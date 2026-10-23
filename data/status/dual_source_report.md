# 双源 diff 报表（只读）

> **口径 = 往返保真**（非「IDA vs 注解」）：`asm/pal3/ida_structs.json` 是 `annotation → apply → IDB → export` 的**下游产物**，两源不并列。本表任何差异只读作**往返保真缺口**（注解未在 apply→export 往返中保真 / export 侧合成成员），不得读成「IDA 反对注解」或「注解错误」。
>
> **位面复用 ≠ 偏移冲突**：`known_members` 的 dict 形态（inline union/struct）、`source:overlap`、同偏移 `_N` 变体键是**同一存储的多解释视图声明**，单列「位面复用」账，不计缺失/冲突（CLAUDE.md 2026-10-16 反向审计定谳）。
>
> **陈旧拒报**：export 时间戳早于注解最新改动 ⇒ 本报表**不生成**（rc=2）。

## 0. 输入与时间戳（陈旧拒报判据）

| 项 | 值 |
|---|---|
| 导出产物 | `asm/pal3/ida_structs.json` |
| 注解目录 | `data/annotations/structs`（942 个 JSON） |
| export 时间戳 | 2026-10-23 20:08:16 +0800（epoch 1792757296.852603） |
| 注解最新改动 | 2026-10-23 17:25:09 +0800（epoch 1792747509.578609） |
| 注解最新改动文件 | `data/annotations/structs/CCBStage.json` |
| 陈旧判定 | FRESH（export 不早于注解最新改动） |

## 1. 量化统计

| 指标 | 值 |
|---|---|
| 结构：双侧共有 / 仅导出 / 仅注解 | 861 / 310 / 64 |
| 成员全同（type 串全同） | 7748 |
| 成员拼写归一（语义等价，不计差异） | 1083 |
| **类型差异（语义不等）** | **34** |
| **成员缺失（注解有 · 导出缺，真缺口）** | **0** |
| **成员新增（导出有 · 注解缺）** | **109** |
| └ 其中 export 合成补尾 `_tail_*` | 109 |
| 位面复用声明（dict / overlap / 同偏移变体） | 259 |
| 已解释·基类区域成员（偏移 < base_size） | 69 |
| 已解释·vptr/base 声明迁移到 vtables/bases | 13 |
| 结构 sizeof 不一致 | 0 |
| `_inline_*` 引用 / 定义 / 引用无定义 / 定义未引用 | 27 / 27 / 0 / 0 |

**多少类不一致？** 399 个结构存在任一差异（成员数/偏移/类型），见 §8；**多少成员缺失？** 真缺口 0 个，见 §2（另 82 个已解释不计缺口）。

## 2. 成员缺失（注解有 · 导出缺）

往返丢失真缺口（**未**被基类区域 / vptr·base 归位解释的）：

（无）

### 已解释（不计缺口）

| 解释类 | 数量 | 说明 |
|---|---|---|
| 基类区域成员 | 69 | 偏移 < base_size：IDB 只在基类声明，派生类不重复 |
| vptr 声明迁移 | 9 | `__vftable`/`_vftable` 归位 IDB `vtables`/`bases` 字段 |
| baseclass 声明迁移 | 4 | `baseclass*` 归位 IDB `bases` 字段 |

### 基类区域成员（69）

| 类 | 偏移键 | 成员 |
|---|---|---|
| CCBRoleState | 0 | m_sCombatDialog |
| CCBRoleState | 100 | m_nCombatResult |
| CCBRoleState | 12 | m_nActiveRoleIdx |
| CCBRoleState | 132 | m_nState |
| CCBRoleState | 148 | m_nTargetRoleIdx |
| CCBRoleState | 156 | m_nSelectedAction |
| CCBRoleState | 16 | m_nPhase |
| CCBRoleState | 160 | m_nSelectedTarget |
| CCBRoleState | 164 | m_nSelectedItem |
| CCBRoleState | 168 | m_nState2 |
| CCBRoleState | 20 | m_nState_014 |
| CCBRoleState | 24 | m_nState_018 |
| CCBRoleState | 280 | m_nDamageThisRound |
| CCBRoleState | 288 | m_nState3 |
| CCBRoleState | 32 | m_nState_020 |
| CCBRoleState | 360 | m_nTodo_168 |
| CCBRoleState | 4 | m_nRoundCounter |
| CCBRoleState | 48 | m_nState_030 |
| CCBRoleState | 512 | m_fLastDialogTime |
| CCBRoleState | 516 | m_bCombatDialog |
| CCBRoleState | 520 | m_pCBSystem |
| CCBRoleState | 524 | m_pStage |
| CCBRoleState | 528 | m_pUI |
| CCBRoleState | 532 | m_pUtil |
| CCBRoleState | 536 | m_bWeSneakAttackEnemy |
| CCBRoleState | 537 | m_bEnemySneakAttackUs |
| CCBRoleState | 540 | m_nMaxRound |
| CCBRoleState | 544 | m_nBossRound |
| CCBRoleState | 548 | m_bMustFail |
| CCBRoleState | 549 | m_bFleeAlwaysSuccess |
| CCBRoleState | 550 | m_bCreatedNewRole |
| CCBRoleState | 552 | m_Role |
| CCBRoleState | 64 | m_nState_040 |
| CCBRoleState | 68 | m_nState_044 |
| CCBRoleState | 76 | m_nState_04C |
| CCBRoleState | 8 | m_nCurrentRound |
| CCBRoleState | 96 | m_nState_060 |
| CEffBase | 4 | m_pEffectSystem |
| CEffBase | 8 | m_eKind |
| CEffTrackCustomShape | 172 | m_pTrack |
| CEffTrackCustomShape | 176 | m_fTrackSpeed |
| CEffTrackCustomShape | 180 | m_fTrackDecPart |
| CEffTrackCylinder | 4292 | m_pTrack |
| CEffTrackCylinder | 4296 | m_fTrackSpeed |
| CEffTrackCylinder | 4300 | m_fTrackDecPart |
| CEffTrackGrid | 4280 | m_pTrack |
| CEffTrackGrid | 4284 | m_fTrackSpeed |
| CEffTrackGrid | 4288 | m_fTrackDecPart |
| CEffTrackModel | 104 | m_pTrack |
| CEffTrackModel | 108 | m_fTrackSpeed |
| CEffTrackModel | 112 | m_fTrackDecPart |
| CEffTrackQuad | 4272 | m_pTrack |
| CEffTrackQuad | 4276 | m_fTrackSpeed |
| CEffTrackQuad | 4280 | m_fTrackDecPart |
| CEffTrackSParticle | 100 | m_pTrack |
| CEffTrackSParticle | 104 | m_fTrackSpeed |
| CEffTrackSParticle | 108 | m_fTrackDecPart |
| RoleCamera | 28 | m_nStackIdx |
| RoleCamera | 32 | m_nStackSize |
| SaleUI | 16 | m_underctrl |
| SaleUI | 20 | m_bStartNGHEffect |
| SaleUI | 24 | m_nHuaYingMode |
| TextureLib_Data | 12 | _libfolder |
| TextureLib_Data | 4 | Seps |
| TextureLib_Data | 524 | _realNum |
| TextureLib_Data | 528 | m_pData |
| TextureLib_Data | 532 | _isLoadTLI |
| TextureLib_Data | 8 | tok |
| UIAnimateCtrlEX | 68 | m_Scene |

### vptr 声明迁移（9）

| 类 | 偏移键 | 成员 |
|---|---|---|
| CGameData | 0 | _vftable |
| EffAudioNode | 0 | __vftable |
| EffBinkNode | 0 | __vftable |
| EffMultiPassNode | 0 | __vftable |
| GameObject | 0 | __vftable |
| PalScript | 0 | __vftable |
| PalScriptFadeOutTimer | 0 | __vftable |
| PalScriptProgressTimer | 0 | __vftable |
| PalScriptWaitTimer | 0 | __vftable |

### baseclass 声明迁移（4）

| 类 | 偏移键 | 成员 |
|---|---|---|
| UIEmote | 68 | baseclass2 |
| UIHeadDialog | 72 | baseclass2 |
| UIRoleDialog | 72 | baseclass2 |
| UIRoleSelect | 72 | baseclass2 |

## 3. 成员新增（导出有 · 注解缺）

export 侧合成补尾 `_tail_*`（109 个，合成填充非注解声明）：

| 类 | 偏移 | 名 | type |
|---|---|---|---|
| C3DSpark_tagSpark | 0 | _tail_000 | `_BYTE[56]` |
| CAccelCentripetalPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CCentripetalPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CDamplyCentripetalPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CEffCamera | 0 | _tail_000 | `_BYTE[4]` |
| CEffMgr | 0 | _tail_000 | `_BYTE[43312]` |
| CEffTemplate | 0 | _tail_000 | `_BYTE[4]` |
| CEffTime | 0 | _tail_000 | `_BYTE[4]` |
| CEffectBubble | 0 | _tail_000 | `_BYTE[4]` |
| CEffectSimple | 0 | _tail_000 | `_BYTE[4]` |
| CFadeInAlphaPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CFadeOutAlphaPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CG_Scene_ArrayErase | 0 | _tail_000 | `_BYTE[4]` |
| CParticleSystem_ParticleAttribute | 0 | _tail_000 | `_BYTE[4]` |
| CParticleSystem_ParticleUnit | 0 | _tail_000 | `_BYTE[4]` |
| CRandomColorPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CRenderTarget | 0 | _tail_000 | `_BYTE[4]` |
| CRenderTarget2 | 0 | _tail_000 | `_BYTE[4]` |
| CSimpleDirPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CSimplePosPolicy | 0 | _tail_000 | `_BYTE[4]` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0 | _tail_000 | `_BYTE[36]` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0 | _tail_000 | `_BYTE[36]` |
| CameraSystem | 0 | _tail_000 | `_BYTE[4]` |
| Combat | 0 | _tail_000 | `_BYTE[4]` |
| DPINFO___unnamed | 0 | _tail_000 | `_BYTE[96]` |
| ECBRoleSpecState | 0 | _tail_000 | `_BYTE[4]` |
| ExternalStatistics | 0 | _tail_000 | `_BYTE[4]` |
| InputSystem | 0 | _tail_000 | `_BYTE[36]` |
| Iostream_init | 0 | _tail_000 | `_BYTE[4]` |
| Math | 0 | _tail_000 | `_BYTE[4]` |
| MatrixStack | 0 | _tail_000 | `_BYTE[4]` |
| MeshFxCreator | 0 | _tail_000 | `_BYTE[4]` |
| MiniGame1 | 0 | _tail_000 | `_BYTE[4]` |
| MiniGame2Scene | 0 | _tail_000 | `_BYTE[4]` |
| MiniGame3 | 0 | _tail_000 | `_BYTE[4]` |
| MvcController | 0 | _tail_000 | `_BYTE[4]` |
| MvcViewport | 0 | _tail_000 | `_BYTE[4]` |
| NameSys_NAMEFLAG | 0 | _tail_000 | `_BYTE[4]` |
| OpenSceneFile | 0 | _tail_000 | `_BYTE[4]` |
| ParabolaCalculator_PRBL_STATE | 0 | _tail_000 | `_BYTE[4]` |
| Parent_Data | 0 | _tail_000 | `_BYTE[4]` |
| RenderTarget2 | 0 | _tail_000 | `_BYTE[4292]` |
| RenderTarget4 | 0 | _tail_000 | `_BYTE[4]` |
| RenderTargetNode | 0 | _tail_000 | `_BYTE[96]` |
| Role_SPECIAL_ACTION | 0 | _tail_000 | `_BYTE[36]` |
| SPECIAL_ACTION | 0 | _tail_000 | `_BYTE[4]` |
| SaleUI_SortData | 0 | _tail_000 | `_BYTE[4]` |
| SceneObj_Common_State | 0 | _tail_000 | `_BYTE[4]` |
| SceneObj_SubObj | 0 | _tail_000 | `_BYTE[36]` |
| ScriptHelper | 0 | _tail_000 | `_BYTE[4]` |
| ScriptObj | 0 | _tail_000 | `_BYTE[4]` |
| SoundContext | 0 | _tail_000 | `_BYTE[4]` |
| SoundSystem | 0 | _tail_000 | `_BYTE[4]` |
| String | 0 | _tail_000 | `_BYTE[4]` |
| TileMap | 0 | _tail_000 | `_BYTE[4]` |
| UIAnimCtrl | 0 | _tail_000 | `_BYTE[4]` |
| UIBase | 0 | _tail_000 | `_BYTE[4]` |
| UIBigDialog | 0 | _tail_000 | `_BYTE[4]` |
| UIButton_UIBUTTON_STATE | 0 | _tail_000 | `_BYTE[4]` |
| UIInventory | 0 | _tail_000 | `_BYTE[68]` |
| UIListView | 0 | _tail_000 | `_BYTE[4]` |
| UIManager | 0 | _tail_000 | `_BYTE[4]` |
| UIObj | 0 | _tail_000 | `_BYTE[4]` |
| UIParabolaCtrl | 0 | _tail_000 | `_BYTE[4]` |
| UIQuadManager | 0 | _tail_000 | `_BYTE[4]` |
| UIRenderObj | 0 | _tail_000 | `_BYTE[32]` |
| UISceneObj | 0 | _tail_000 | `_BYTE[4]` |
| UIScrollBar_SB_AREA | 0 | _tail_000 | `_BYTE[4]` |
| UISelectDialog | 0 | _tail_000 | `_BYTE[4]` |
| UISlider | 0 | _tail_000 | `_BYTE[4]` |
| UIStaticFlex_State | 0 | _tail_000 | `_BYTE[4]` |
| UISystem | 0 | _tail_000 | `_BYTE[4]` |
| VertPoolMgr | 0 | _tail_000 | `_BYTE[4]` |
| VideoPlayer | 0 | _tail_000 | `_BYTE[4]` |
| _Console__ConCmd | 0 | _tail_000 | `_BYTE[136]` |
| collision | 0 | _tail_000 | `_BYTE[4]` |
| direction_emitter_graph | 0 | _tail_000 | `_BYTE[5300]` |
| elelife_emitter_graph | 0 | _tail_000 | `_BYTE[5300]` |
| elerandvec_emitter_graph | 0 | _tail_000 | `_BYTE[5300]` |
| emissionrate_emitter_graph | 0 | _tail_000 | `_BYTE[5300]` |
| gbFileStream | 0 | _tail_000 | `_BYTE[4]` |
| gbMeshData | 0 | _tail_000 | `_BYTE[4]` |
| gbRenderEffect_D3D | 0 | _tail_000 | `_BYTE[4]` |
| gbSceneNode | 0 | _tail_000 | `_BYTE[4]` |
| gbSingleton_gbGfxManager | 0 | _tail_000 | `_BYTE[8]` |
| gbVolumeModifier | 0 | _tail_000 | `_BYTE[4]` |
| rgbcolor_particle_graph | 0 | _tail_000 | `_BYTE[5300]` |
| rotation_particle_graph | 0 | _tail_000 | `_BYTE[5300]` |
| rotmulti_emitter_graph | 0 | _tail_000 | `_BYTE[5300]` |
| size_particle_graph | 0 | _tail_000 | `_BYTE[5300]` |
| sizemulti_emitter_graph | 0 | _tail_000 | `_BYTE[5300]` |
| tagEffClass | 0 | _tail_000 | `_BYTE[4]` |
| tagEffMgrData | 0 | _tail_000 | `_BYTE[1500]` |
| vertexalpha_particle_graph | 0 | _tail_000 | `_BYTE[5300]` |

非合成补尾的新增（0 个）：

（无）

## 4. 类型差异（语义不等）

归一化后仍不同的类型对（往返降级 / 重解释，**真差异**）：

| 类 | 偏移键 | 成员 | 注解 type | 导出 type |
|---|---|---|---|---|
| ARC_Inventory | 0 | m_items | `std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >` | `char[16]` |
| ARC_Inventory | 20 | m_typeitems | `std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >` | `char[16]` |
| ARC_Reoccupy | 0 | m_id | `std::vector<unsigned int,std::allocator<unsigned int> >` | `char[16]` |
| ArcScene | 132 | objArray | `std::vector<ArcSceneObject,std::allocator<ArcSceneObject> >` | `char[16]` |
| ArcScene | 148 | npcArray | `std::vector<ArcSceneMonster,std::allocator<ArcSceneMonster> >` | `char[16]` |
| Archive | 0 | m_scene | `std::vector<ArcScene,std::allocator<ArcScene> >` | `char[16]` |
| Archive | 16 | m_past | `std::vector<ArcPastScene,std::allocator<ArcPastScene> >` | `char[16]` |
| Archive | 32 | m_objNotLoad | `std::vector<unsigned int,std::allocator<unsigned int> >` | `char[16]` |
| CCBUIPanel | 1560 | m_pVfTable | `char *` | `vtbl_0056B22C *` |
| CEffCustomShape | 156 | m_UVData | `std::vector<gbVec2D,std::allocator<gbVec2D> >` | `char[16]` |
| CParticleSystem | 16 | _strParticleName | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` | `char[16]` |
| CParticleSystem | 192 | _TexCoordData | `std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >` | `char[16]` |
| EffectItem | 8 | _pixelInfo | `std::vector<EffectInfo,std::allocator<EffectInfo> >` | `char[16]` |
| HandlerType | 4 | pType | `const struct TypeDescriptor *` | `TypeDescriptor *` |
| HeadMsg | 8 | m_szMsg | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` | `char[16]` |
| Inventory | 0 | m_items | `std::vector<PlayerItem,std::allocator<PlayerItem> >` | `char[16]` |
| Inventory | 20 | m_typeitems | `std::vector<PlayerItem,std::allocator<PlayerItem> >` | `char[16]` |
| LayerNode | 28 | m_tri | `std::vector<Triangle,std::allocator<Triangle> >` | `char[16]` |
| PurgeEffect | 408 | EffItem | `std::vector<EffectItem,std::allocator<EffectItem> >` | `char[16]` |
| Reoccupy | 0 | m_id | `std::vector<unsigned int,std::allocator<unsigned int> >` | `char[16]` |
| Role | 96 | m_cmdqueue | `std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >` | `char[48]` |
| RoleTaskPool | 0 | m_TaskData | `std::vector<RoleTask,std::allocator<RoleTask> >` | `char[16]` |
| RoleTaskPool | 16 | m_TaskLine | `std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >` | `char[16]` |
| SceneObj | 1708 | m_common | `std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >` | `char[48]` |
| ScriptVM | 796 | m_pCmdList | `RoleSystem **` | `RoleSystem *` |
| SoundMgr | 8 | m_szScriptMusic | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` | `char[16]` |
| SoundMgr | 828 | m_cbbuf | `std::vector<SoundItem,std::allocator<SoundItem> >` | `char[16]` |
| UITabBtn | 0 | m_BtnAndID | `std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >` | `char[16]` |
| _Item | 0 | title | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` | `char[16]` |
| _Item | 16 | info | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` | `char[16]` |
| _SCOPETABLE_ENTRY | 4 | FilterFunc | `char *` | `void *` |
| _SCOPETABLE_ENTRY | 8 | HandlerFunc | `char *` | `void *` |
| t3DModel | 24 | pObject | `std::vector<t3DObject,std::allocator<t3DObject> >` | `char[16]` |
| t3DModel | 8 | pMaterials | `std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >` | `char[16]` |

## 5. 类型拼写归一（语义等价 · 不计差异）

同型异拼（MSVC6 x86 等价：DWORD/UINT/uint=unsigned int、WORD=unsigned __int16、BYTE=_BYTE=unsigned char、long=int、short=signed __int16…），逐拼写族计数：

| 注解 type | 导出 type | 数量 | 样例 |
|---|---|---|---|
| `DWORD` | `unsigned int` | 505 | ARC_ArcHeader@152, ARC_ArcHeader@156 |
| `long` | `int` | 137 | ASISTAGE@92, BINK@180 |
| `UINT` | `unsigned int` | 94 | ArtistPlugIn@520, Average@0 |
| `WORD` | `unsigned __int16` | 69 | ARC_RoleAtt@4, CameraCtrl@620 |
| `short` | `signed __int16` | 66 | ARC_FightItem@768, ARC_FightItem@770 |
| `unsigned char[5]` | `_BYTE[5]` | 23 | ARC_ArcBrief@4, ARC_ArcMsic@22 |
| `unsigned char[4]` | `_BYTE[4]` | 13 | ARC_ComboAttack@52, ARC_ComboAttack@60 |
| `BYTE *` | `_BYTE *` | 12 | BINK@476, BINK@648 |
| `DWORD *` | `unsigned int *` | 11 | BINK@268, BINK@496 |
| `unsigned short` | `unsigned __int16` | 11 | ScriptSystemData@10204, ScriptSystemData@7852 |
| `unsigned char[3]` | `_BYTE[3]` | 9 | ARC_FightSkill@748, ARC_FightSkill@751 |
| `unsigned char[7]` | `_BYTE[7]` | 9 | LineupUI@139244, MagicUI@181564 |
| `unsigned char[12]` | `_BYTE[12]` | 8 | ARC_ArcMsic@0, ARC_ComboAttack@593 |
| `short[12]` | `signed __int16[12]` | 6 | ARC_ComboAttack@606, ARC_FightItem@644 |
| `long[8]` | `int[8]` | 4 | _DIG_DRIVER@68, _SAMPLE@132 |
| `short[31]` | `signed __int16[31]` | 4 | ARC_FightItem@700, ARC_FightSkill@618 |
| `unsigned char[6]` | `_BYTE[6]` | 4 | ARC_PlayerAtt@1060, LINEUPINFO@0 |
| `unsigned char[8]` | `_BYTE[8]` | 4 | ARC_PlayerMgrInfo@7316, ObjectInfo@404 |
| `unsigned char[8][6]` | `_BYTE[8][6]` | 4 | ARC_PlayerAtt@1260, ARC_PlayerAtt@1308 |
| `void*` | `void *` | 4 | Actor@496, NPC@60 |
| `__int64` | `signed __int64` | 3 | LARGE_INTEGER@16, localVar1@0 |
| `long[2]` | `int[2]` | 3 | _SAMPLE@44, _STREAM@80 |
| `unsigned char *` | `_BYTE *` | 3 | Config@4, gbImage2D@184 |
| `unsigned char[11]` | `_BYTE[11]` | 3 | CCBAI@0, CCBStage@116 |
| `unsigned char[31]` | `_BYTE[31]` | 3 | ARC_FightItem@668, FightItem@668 |
| `unsigned char[99]` | `_BYTE[99]` | 3 | ArcMsic@645, SystemUI@141928 |
| `unsigned char[9]` | `_BYTE[9]` | 3 | CG_UI@21944, PlayerAtt@1072 |
| `unsigned char[9][6]` | `_BYTE[9][6]` | 3 | PlayerAtt@1300, PlayerAtt@1462 |
| `unsigned short[256]` | `unsigned __int16[256]` | 3 | gbGammaRamp@0, gbGammaRamp@1024 |
| `BYTE[270]` | `_BYTE[270]` | 2 | GRPinput@104, GRPinput@3872 |
| `_DWORD[4]` | `unsigned int[4]` | 2 | PAL3@320, PAL3@336 |
| `long[3]` | `int[3]` | 2 | _STREAM@44, _STREAM@56 |
| `struct _EH3_EXCEPTION_REGISTRATION *` | `_EH3_EXCEPTION_REGISTRATION *` | 2 | EH3_EXCEPTION_REGISTRATION@0, _EH3_EXCEPTION_REGISTRATION@0 |
| `unsigned char[128]` | `_BYTE[128]` | 2 | BINKIO@76, BINKSND@64 |
| `unsigned char[16]` | `_BYTE[16]` | 2 | UIGameFrm@140, UIListBox@1192 |
| `unsigned char[299][5]` | `_BYTE[299][5]` | 2 | SaleUI@83904, SaleUI@85399 |
| `unsigned char[40]` | `_BYTE[40]` | 2 | ARC_ArcMsic@88, ArcMsic@0 |
| `unsigned char[8][5]` | `_BYTE[8][5]` | 2 | ARC_ArcMsic@33, MagicUI@72 |
| `unsigned char[8][6][5]` | `_BYTE[8][6][5]` | 2 | EquipUI@82672, EquipUI@82916 |
| `unsigned short[9][6]` | `unsigned __int16[9][6]` | 2 | PlayerAtt@1354, tagRoleState@482 |
| `BYTE[256]` | `_BYTE[256]` | 1 | GRPinput@376 |
| `DWORD[3]` | `unsigned int[3]` | 1 | CCBUI_funcptr_t@4 |
| `_Item * *` | `_Item **` | 1 | _Item@44 |
| `_SAMPLE * *` | `_SAMPLE **` | 1 | _DIG_DRIVER@184 |
| `gbTexture * *` | `gbTexture **` | 1 | gbTexFlipAnim@0 |
| `int (__thiscall *)(void *, unsigned long)` | `int (__thiscall *)(void *, unsigned int)` | 1 | tagNewItem@8 |
| `short *` | `signed __int16 *` | 1 | _Ctypevec@8 |
| `struct _EH3_EXCEPTION_REGISTRATION` | `_EH3_EXCEPTION_REGISTRATION` | 1 | CPPEH_RECORD@8 |
| `uint` | `unsigned int` | 1 | primitive@72 |
| `unsigned char *[3]` | `_BYTE *[3]` | 1 | _STREAM@20 |
| `unsigned char[2000]` | `_BYTE[2000]` | 1 | CCCTData@408000 |
| `unsigned char[20]` | `_BYTE[20]` | 1 | ArcHeader@200 |
| `unsigned char[241]` | `_BYTE[241]` | 1 | ScriptPoolPage@8 |
| `unsigned char[256]` | `_BYTE[256]` | 1 | ARC_ArcMsic@296 |
| `unsigned char[27]` | `_BYTE[27]` | 1 | ARC_ArcLocaleRole@1 |
| `unsigned char[2]` | `_BYTE[2]` | 1 | _cpinfo@4 |
| `unsigned char[2][5]` | `_BYTE[2][5]` | 1 | EquipUI@110080 |
| `unsigned char[32]` | `_BYTE[32]` | 1 | ArcLocale@452 |
| `unsigned char[512]` | `_BYTE[512]` | 1 | _CONTEXT@204 |
| `unsigned char[5][2]` | `_BYTE[5][2]` | 1 | ARC_ArcMsic@12 |
| `unsigned char[64]` | `_BYTE[64]` | 1 | scScriptBlock@4 |
| `unsigned char[6][5]` | `_BYTE[6][5]` | 1 | EquipUI@109917 |
| `unsigned char[80]` | `_BYTE[80]` | 1 | _FLOATING_SAVE_AREA@28 |
| `unsigned char[8][4]` | `_BYTE[8][4]` | 1 | code_page_info@16 |
| `unsigned long` | `unsigned int` | 1 | UICursor@44 |
| `unsigned long *` | `unsigned int *` | 1 | JusticeBookUI@8940 |
| `unsigned long[100][6]` | `unsigned int[100][6]` | 1 | JusticeBookUI@8972 |
| `unsigned long[15]` | `unsigned int[15]` | 1 | _EXCEPTION_RECORD@20 |
| `unsigned long[384]` | `unsigned int[384]` | 1 | CCBEditor@8080 |
| `unsigned short *` | `unsigned __int16 *` | 1 | gbMeshMemCache@8 |
| `unsigned short[10]` | `unsigned __int16[10]` | 1 | _IMAGE_DOS_HEADER@40 |
| `unsigned short[16]` | `unsigned __int16[16]` | 1 | _ADPCMDATATAG@40 |
| `unsigned short[3]` | `unsigned __int16[3]` | 1 | NavFace@0 |
| `unsigned short[4]` | `unsigned __int16[4]` | 1 | _IMAGE_DOS_HEADER@28 |
| `unsigned short[5]` | `unsigned __int16[5]` | 1 | RoleAtt@728 |
| `unsigned short[6]` | `unsigned __int16[6]` | 1 | code_page_info@4 |
| `wavehdr_tag * *` | `wavehdr_tag **` | 1 | _DIG_DRIVER@124 |

## 6. 位面复用（非偏移冲突）

**位面复用 ≠ 偏移冲突**：以下成员是同一存储的多解释视图（dict 形态 inline union/struct · `source:overlap` · 同偏移 `_N` 变体键），IDB 侧同偏移多成员属预期，**不计**缺失/类型差异/冲突。dict 形态的往返形是合成名 `_inline_<类>_<成员>`：

| 形态 | 数量 |
|---|---|
| dict | 14 |
| dict+overlap | 1 |
| dict+overlap+suffix | 2 |
| overlap | 236 |
| suffix | 6 |
| 合计（条目） | 259 |

| 类 | 偏移键 | 成员 | 形态 | 导出 type | 备注 |
|---|---|---|---|---|---|
| Actor | 512 | m_pParticleData | overlap | `void *` | — |
| Actor | 680 | m_InnerActor | overlap | `void *` | — |
| ArcSceneMonster | 304 | m_pSkillList | overlap | `void *` | — |
| ArcSceneMonster | 320 | m_pDropItems | overlap | `void *` | — |
| ArcSceneMonster | 4 | m_pMonsterData | overlap | `void *` | — |
| CCBAI | 3344 | m_EnemyDemand | overlap | `tagDemand[5]` | — |
| CCBAI | 3504 | m_FriendDemand | overlap | `tagDemand[5]` | — |
| CCBCamControl | 236 | m_nTodo_EC | overlap | `gbVolModNode` | — |
| CCBStage | 128 | m_fDamageNumPosY | overlap | `float[5]` | — |
| CCBStage | 4504 | m_nTodo_1198 | overlap | `void *` | — |
| CCBStageScene | 92 | m_vecInitFiveLineup | overlap | `gbVec3D[3]` | — |
| CCBTaskSlot | 20 | _ovl_20 | dict | `_inline_CCBTaskSlot__ovl_20` | — |
| CCBTaskSlot | 28 | _ovl_28 | dict | `_inline_CCBTaskSlot__ovl_28` | — |
| CCBTaskSlot208 | 0 | m_nBase | overlap | `int` | — |
| CCBUI | 1208 | m_Task | overlap | `tagUITask[19]` | — |
| CCBUIPanel | 20664 | m_EmbedCaption | overlap | `void *` | — |
| CGameData | 12992 | m_fUIColorParam | overlap | `float` | — |
| CGameData | 16424 | m_bGameUpdating | overlap | `unsigned char` | — |
| CGameData | 2220 | m_pItemArray | overlap | `_QWORD` | — |
| CGameData | 7072 | m_fTimerC | overlap | `float` | — |
| CScreenMode | 2608 | m_pGameUI | overlap | `void *` | — |
| CScreenMode | 636 | _embed_UIFrameWnd_816 | overlap | `UIFrameWnd` | — |
| CScreenMode | 728 | _embed_UIFrameWnd_968 | overlap | `UIFrameWnd` | — |
| CameraCtrl | 2044 | m_nViewBase | overlap | `void *` | — |
| FightItem | 96 | desc | dict | `_inline_FightItem_desc` | — |
| LineupComp | 68 | m_ObjPos | overlap | `gbVec3D[4]` | — |
| Logger | 4652 | m_szCmdBuf2 | overlap | `_DWORD` | — |
| Logger | 4656 | m_szCmdBuf | overlap | `char[100]` | — |
| MUIDialog | 632 | m_btRc | dict | `_inline_MUIDialog_m_btRc` | — |
| MUIDialog | 976 | pCallbackVtable2 | overlap | `void *` | — |
| PalScript | 1300 | m_szDialog1 | dict | `_inline_PalScript_m_szDialog1` | — |
| PalScript | 144_1 | m_pCurrentTask_f | suffix | `float` | — |
| PalScript | 144_2 | m_pCurrentTask_p | suffix | `char *` | — |
| PalScript | 260 | m_WaitObjList | overlap | `PtrArray` | — |
| PalScript | 396 | m_RoleSlotArray | dict | `_inline_PalScript_m_RoleSlotArray` | — |
| PalScriptDialogOverlay | 140 | overlay | dict | `_inline_PalScriptDialogOverlay_overlay` | — |
| PalScriptRoleSlotOverlay | 0 | overlay | dict | `_inline_PalScriptRoleSlotOverlay_overlay` | — |
| RoleAtt | 6 | Remark | dict | `_inline_RoleAtt_Remark` | — |
| RoleAttRemarkSkills | 290 | skillCount | dict | `_inline_RoleAttRemarkSkills_skillCount` | — |
| RoleCameraCtrl | 8_1 | m_pVtable_f | suffix | `float` | — |
| RoleCameraCtrl | 8_2 | m_pVtable_i | suffix | `int` | — |
| RoleStatePanel | 176064 | m_pSubTab2 | overlap | `void *` | — |
| RoleSystem | 1316 | m_FrameA | overlap | `UIFrameWnd` | — |
| RoleSystem | 1572 | m_nTodo_624 | overlap | `UIWnd` | — |
| RoleSystem | 1684_0 | m_teamSlotOverlay | dict+overlap+suffix | `_inline_RoleSystem_m_teamSlotOverlay` | — |
| RoleSystem | 3072 | m_teamSlotsB | dict | `_inline_RoleSystem_m_teamSlotsB` | — |
| RoleSystemTeamSlotOverlay | 4 | m_teamSlots | dict | `_inline_RoleSystemTeamSlotOverlay_m_teamSlots` | — |
| SceneMgr | 11104 | m_nTodo_61D8 | overlap | `int` | — |
| SceneMgr | 50814_0 |  | dict+overlap+suffix | `_inline_SceneMgr_` | — |
| SceneMgr | 5648 | m_nTodo_C059A0 | overlap | `_BYTE[5444]` | — |
| ScriptSystemData | 2216 | m_fTimerA | overlap | `float` | — |
| ScriptSystemData | 2312 | g_vRotateAxis | overlap | `gbVec3D` | — |
| ScriptSystemData | 2324 | m_bMapRenderFlags | overlap | `unsigned char` | — |
| ScriptSystemData | 2328 | m_nScriptCounter0 | overlap | `int` | — |
| ScriptSystemData | 2332 | m_nScriptCounter1 | overlap | `int` | — |
| ScriptSystemData | 2336 | m_nScriptFlag | overlap | `int` | — |
| ScriptSystemData | 3032 | m_fTimerB | overlap | `float` | — |
| ScriptSystemData | 3684 | m_fScriptTileSize2 | overlap | `float` | — |
| SystemUI | 180 | m_nTodo_0B4 | overlap | `void *` | — |
| TextureLib | 408 | m_pPalette | overlap | `void *` | — |
| UIGameFrm | 260 | m_cap | overlap | `_BYTE[96]` | — |
| scVARIANT_data | 0_1 | as_float | suffix | `float` | — |
| tag17A7BData | 0 | m_nEffParamBase | overlap | `int[3]` | — |
| tag17A7BData | 12 | m_nEffParam0 | overlap | `int` | — |
| tag17A7BData | 20 | m_nEffParam14 | overlap | `int` | — |
| tag17A7BData | 24 | m_nEffParam1 | overlap | `int` | — |
| tag17A7BData | 28 | m_nEffParam1C | overlap | `int` | — |
| tag17A7BData | 36 | m_nEffParam24 | overlap | `int` | — |
| tag17A7BData | 40 | m_nEffTypeCode | overlap | `int` | — |
| tag17A7BData | 44 | m_nEffParam2C | overlap | `int` | — |
| tag17A8Data | 0 | m_nEffParamBase | overlap | `int[3]` | — |
| tag17A8Data | 12 | m_nEffParam0 | overlap | `float` | — |
| tag17A8Data | 16 | m_nEffParam10 | overlap | `int` | — |
| tag17A8Data | 20 | m_nEffParam14 | overlap | `float` | — |
| tag17A8Data | 24 | m_nEffParam1 | overlap | `int` | — |
| tag17A8Data | 28 | m_nEffParam1C | overlap | `int` | — |
| tag17A8Data | 32 | m_nEffTypeID | overlap | `int` | — |
| tag17A8Data | 36 | m_nEffParam24 | overlap | `int` | — |
| tag17A8Data | 40 | m_nEffTypeCode | overlap | `int` | — |
| tag17A8Data | 44 | m_nEffParam2C | overlap | `int` | — |
| tag17A8Data | 48 | m_nEffParam30 | overlap | `int` | — |
| tagC10Data | 0 | m_nEffParamBase | overlap | `int[2]` | — |
| tagC10Data | 12 | m_nEffParam0 | overlap | `int` | — |
| tagC10Data | 16 | m_nEffParam10 | overlap | `int` | — |
| tagC10Data | 20 | m_nEffParam14 | overlap | `int` | — |
| tagC10Data | 24 | m_nEffParam1 | overlap | `int` | — |
| tagC10Data | 28 | m_nEffParam1C | overlap | `int` | — |
| tagC10Data | 32 | m_nEffTypeID | overlap | `int` | — |
| tagC10Data | 36 | m_nEffParam24 | overlap | `int` | — |
| tagC10Data | 40 | m_nEffTypeCode | overlap | `int` | — |
| tagC10Data | 44 | m_nEffParam2C | overlap | `int` | — |
| tagC10Data | 48 | m_nEffParam30 | overlap | `int` | — |
| tagC10Data | 52 | m_nEffParam34 | overlap | `int` | — |
| tagC10Data | 56 | m_nEffParam38 | overlap | `int` | — |
| tagCCBStageData | 0 | m_nEffParamBase0 | overlap | `int` | — |
| tagCCBStageData | 20 | m_nEffParam14 | overlap | `int` | — |
| tagCCBStageData | 28 | m_nEffParam1C | overlap | `int` | — |
| tagCCBStageData | 32 | m_nEffTypeID | overlap | `int` | — |
| tagCCBStageData | 40 | m_nEffTypeCode | overlap | `int` | — |
| tagCam | 12 | yaw | dict | `_inline_tagCam_yaw` | — |
| tagCmdData | 29 | m_destRoleView | dict+overlap | `_inline_tagCmdData_m_destRoleView` | — |
| tagCombatTaskData | 0 | m_nEffParamBase | overlap | `int[2]` | — |
| tagCombatTaskData | 104 | m_nEffParam4 | overlap | `int` | — |
| tagCombatTaskData | 12 | m_nEffParam0 | overlap | `int` | — |
| tagCombatTaskData | 132 | m_nEffParam7 | overlap | `float` | — |
| tagCombatTaskData | 140 | m_nEffParam8 | overlap | `int` | — |
| tagCombatTaskData | 148 | m_nEffParam9 | overlap | `int` | — |
| tagCombatTaskData | 152 | m_nEffParam98 | overlap | `int` | — |
| tagCombatTaskData | 156 | m_nEffParam9C | overlap | `float` | — |
| tagCombatTaskData | 16 | m_nEffParam10 | overlap | `int` | — |
| tagCombatTaskData | 160 | m_nEffParamA0 | overlap | `int` | — |
| tagCombatTaskData | 164 | m_nEffParamA4 | overlap | `int` | — |
| tagCombatTaskData | 168 | m_nEffParamA8 | overlap | `float` | — |
| tagCombatTaskData | 172 | m_nEffParamAC | overlap | `int` | — |
| tagCombatTaskData | 176 | m_nEffParamB0 | overlap | `int` | — |
| tagCombatTaskData | 20 | m_nEffParam14 | overlap | `float` | — |
| tagCombatTaskData | 200 | m_nEffParamC8 | overlap | `float` | — |
| tagCombatTaskData | 204 | m_nEffParamCC | overlap | `int` | — |
| tagCombatTaskData | 208 | m_nEffParamD0 | overlap | `int` | — |
| tagCombatTaskData | 212 | m_nEffParamD4 | overlap | `float` | — |
| tagCombatTaskData | 216 | m_nEffParamD8 | overlap | `int` | — |
| tagCombatTaskData | 220 | m_nEffParamDC | overlap | `int` | — |
| tagCombatTaskData | 224 | m_nEffParamE0 | overlap | `float` | — |
| tagCombatTaskData | 228 | m_nEffParamE4 | overlap | `int` | — |
| tagCombatTaskData | 232 | m_nEffParamE8 | overlap | `int` | — |
| tagCombatTaskData | 236 | m_nEffParamEC | overlap | `float` | — |
| tagCombatTaskData | 24 | m_nEffParam1 | overlap | `int` | — |
| tagCombatTaskData | 240 | m_nEffParamF0 | overlap | `int` | — |
| tagCombatTaskData | 28 | m_nEffParam1C | overlap | `int` | — |
| tagCombatTaskData | 284 | _todo_11C | overlap | `int` | — |
| tagCombatTaskData | 296 | _todo_128 | overlap | `int` | — |
| tagCombatTaskData | 308 | _todo_134 | overlap | `int` | — |
| tagCombatTaskData | 32 | m_nEffTypeID | overlap | `float` | — |
| tagCombatTaskData | 340 | _todo_154 | overlap | `int` | — |
| tagCombatTaskData | 348 | _todo_15C | overlap | `float` | — |
| tagCombatTaskData | 356 | _todo_164 | overlap | `int` | — |
| tagCombatTaskData | 36 | m_nEffParam24 | overlap | `int` | — |
| tagCombatTaskData | 364 | _todo_16C | overlap | `int` | — |
| tagCombatTaskData | 372 | _todo_174 | overlap | `float` | — |
| tagCombatTaskData | 380 | _todo_17C | overlap | `int` | — |
| tagCombatTaskData | 40 | m_nEffTypeCode | overlap | `int` | — |
| tagCombatTaskData | 64 | m_nEffParam40 | overlap | `float` | — |
| tagCombatTaskData | 68 | m_nEffParam44 | overlap | `int` | — |
| tagCombatTaskData | 72 | m_nEffParam48 | overlap | `int` | — |
| tagCombatTaskData | 76 | m_nEffParam4C | overlap | `float` | — |
| tagCombatTaskData | 80 | m_nEffParam50 | overlap | `int` | — |
| tagCombatTaskData | 84 | m_nEffParam2 | overlap | `int` | — |
| tagCombatTaskData | 88 | m_nEffParam58 | overlap | `float` | — |
| tagCombatTaskData | 92 | m_nEffParam5C | overlap | `int` | — |
| tagCombatTaskData | 96 | m_nEffParam3 | overlap | `int` | — |
| tagNewItem | 12_1 | fMP | suffix | `float` | — |
| tagPAL3GameState | 0 | m_nEffParamBase0 | overlap | `int` | — |
| tagPAL3GameState | 104 | m_nEffParam4 | overlap | `int` | — |
| tagPAL3GameState | 112 | m_nEffParam5 | overlap | `int` | — |
| tagPAL3GameState | 120 | m_nEffParam6 | overlap | `int` | — |
| tagPAL3GameState | 140 | m_nEffParam8 | overlap | `int` | — |
| tagPAL3GameState | 152 | m_nEffParam98 | overlap | `int` | — |
| tagPAL3GameState | 156 | m_nEffParam9C | overlap | `int` | — |
| tagPAL3GameState | 160 | m_nEffParamA0 | overlap | `int` | — |
| tagPAL3GameState | 168 | m_nEffParamA8 | overlap | `int` | — |
| tagPAL3GameState | 172 | m_nEffParamAC | overlap | `int` | — |
| tagPAL3GameState | 176 | m_nEffParamB0 | overlap | `int` | — |
| tagPAL3GameState | 184 | m_nEffParamB8 | overlap | `int` | — |
| tagPAL3GameState | 188 | m_nEffParamBC | overlap | `int` | — |
| tagPAL3GameState | 192 | m_nEffParamC0 | overlap | `int` | — |
| tagPAL3GameState | 200 | m_nEffParamC8 | overlap | `int` | — |
| tagPAL3GameState | 204 | m_nEffParamCC | overlap | `int` | — |
| tagPAL3GameState | 208 | m_nEffParamD0 | overlap | `int` | — |
| tagPAL3GameState | 216 | m_nEffParamD8 | overlap | `int` | — |
| tagPAL3GameState | 220 | m_nEffParamDC | overlap | `int` | — |
| tagPAL3GameState | 224 | m_nEffParamE0 | overlap | `int` | — |
| tagPAL3GameState | 232 | m_nEffParamE8 | overlap | `int` | — |
| tagPAL3GameState | 236 | m_nEffParamEC | overlap | `int` | — |
| tagPAL3GameState | 24 | m_nEffParam1 | overlap | `int` | — |
| tagPAL3GameState | 240 | m_nEffParamF0 | overlap | `int` | — |
| tagPAL3GameState | 248 | m_nEffParam_F8 | overlap | `int` | — |
| tagPAL3GameState | 284 | _todo_11C | overlap | `int` | — |
| tagPAL3GameState | 296 | _todo_128 | overlap | `int` | — |
| tagPAL3GameState | 316 | _todo_13C | overlap | `int` | — |
| tagPAL3GameState | 32 | m_nEffTypeID | overlap | `int` | — |
| tagPAL3GameState | 332 | _todo_14C | overlap | `int` | — |
| tagPAL3GameState | 348 | _todo_15C | overlap | `int` | — |
| tagPAL3GameState | 364 | _todo_16C | overlap | `int` | — |
| tagPAL3GameState | 380 | _todo_17C | overlap | `int` | — |
| tagPAL3GameState | 396 | _todo_18C | overlap | `int` | — |
| tagPAL3GameState | 40 | m_nEffTypeCode | overlap | `int` | — |
| tagPAL3GameState | 412 | _todo_19C | overlap | `int` | — |
| tagPAL3GameState | 428 | _todo_1AC | overlap | `int` | — |
| tagPAL3GameState | 44 | m_nEffParam2C | overlap | `int` | — |
| tagPAL3GameState | 460 | _todo_1CC | overlap | `int` | — |
| tagPAL3GameState | 48 | m_nEffParam30 | overlap | `int` | — |
| tagPAL3GameState | 548 | _todo_224 | overlap | `int` | — |
| tagPAL3GameState | 56 | m_nEffParam38 | overlap | `int` | — |
| tagPAL3GameState | 564 | _todo_234 | overlap | `int` | — |
| tagPAL3GameState | 580 | _todo_244 | overlap | `int` | — |
| tagPAL3GameState | 592 | _todo_0250 | overlap | `int` | — |
| tagPAL3GameState | 596 | _todo_0254 | overlap | `int` | — |
| tagPAL3GameState | 60 | m_nEffParam3C | overlap | `int` | — |
| tagPAL3GameState | 600 | _todo_0258 | overlap | `int` | — |
| tagPAL3GameState | 604 | _todo_025C | overlap | `int` | — |
| tagPAL3GameState | 608 | _todo_0260 | overlap | `int` | — |
| tagPAL3GameState | 612 | _todo_0264 | overlap | `int` | — |
| tagPAL3GameState | 616 | _todo_0268 | overlap | `int` | — |
| tagPAL3GameState | 620 | _todo_026C | overlap | `int` | — |
| tagPAL3GameState | 624 | _todo_0270 | overlap | `int` | — |
| tagPAL3GameState | 628 | _todo_0274 | overlap | `int` | — |
| tagPAL3GameState | 632 | _todo_0278 | overlap | `int` | — |
| tagPAL3GameState | 636 | _todo_027C | overlap | `int` | — |
| tagPAL3GameState | 64 | m_nEffParam40 | overlap | `int` | — |
| tagPAL3GameState | 640 | _todo_0280 | overlap | `int` | — |
| tagPAL3GameState | 644 | _todo_0284 | overlap | `int` | — |
| tagPAL3GameState | 648 | _todo_0288 | overlap | `int` | — |
| tagPAL3GameState | 652 | _todo_028C | overlap | `int` | — |
| tagPAL3GameState | 656 | _todo_0290 | overlap | `int` | — |
| tagPAL3GameState | 660 | _todo_0294 | overlap | `int` | — |
| tagPAL3GameState | 664 | _todo_0298 | overlap | `int` | — |
| tagPAL3GameState | 668 | _todo_029C | overlap | `int` | — |
| tagPAL3GameState | 72 | m_nEffParam48 | overlap | `int` | — |
| tagPAL3GameState | 76 | m_nEffParam4C | overlap | `int` | — |
| tagPAL3GameState | 80 | m_nEffParam50 | overlap | `int` | — |
| tagPAL3GameState | 88 | m_nEffParam58 | overlap | `int` | — |
| tagPAL3GameState | 92 | m_nEffParam5C | overlap | `int` | — |
| tagPAL3GameState | 96 | m_nEffParam3 | overlap | `int` | — |
| tagRoleSystemData | 0 | m_nEffParamBase0 | overlap | `int` | — |
| tagRoleSystemData | 180 | m_nEffParamB4 | overlap | `int` | — |
| tagRoleSystemData | 20 | m_nEffParam14 | overlap | `int` | — |
| tagRoleSystemData | 200 | m_nEffParamC8 | overlap | `int` | — |
| tagRoleSystemData | 220 | m_nEffParamDC | overlap | `int` | — |
| tagRoleSystemData | 240 | m_nEffParamF0 | overlap | `int` | — |
| tagRoleSystemData | 260 | _todo_104 | overlap | `float` | — |
| tagRoleSystemData | 340 | _todo_154 | overlap | `int` | — |
| tagRoleSystemData | 380 | _todo_17C | overlap | `int` | — |
| tagRoleSystemData | 40 | m_nEffTypeCode | overlap | `int` | — |
| tagRoleSystemData | 60 | m_nEffParam3C | overlap | `int` | — |
| tagRoleSystemData | 80 | m_nEffParam50 | overlap | `int` | — |
| tagRoleTask | 16 | vec1 | dict | `_inline_tagRoleTask_vec1` | — |
| tagStageRoleData | 0 | m_nEffParamBase0 | overlap | `float` | — |
| tagStageRoleData | 112 | m_nEffParam5 | overlap | `float` | — |
| tagStageRoleData | 120 | m_nEffParam6 | overlap | `float` | — |
| tagStageRoleData | 132 | m_nEffParam7 | overlap | `float` | — |
| tagStageRoleData | 140 | m_nEffParam8 | overlap | `int` | — |
| tagStageRoleData | 156 | m_nEffParam9C | overlap | `float` | — |
| tagStageRoleData | 28 | m_nEffParam1C | overlap | `int` | — |
| tagStageRoleData | 32 | m_nEffTypeID | overlap | `int` | — |
| tagStageRoleData | 36 | m_nEffParam24 | overlap | `int` | — |
| tagStageRoleData | 4 | m_nEffParamBase4 | overlap | `int` | — |
| tagStageRoleData | 40 | m_nEffTypeCode | overlap | `int` | — |
| tagStageRoleData | 44 | m_nEffParam2C | overlap | `int` | — |
| tagStageRoleData | 48 | m_nEffParam30 | overlap | `int` | — |
| tagStageRoleData | 52 | m_nEffParam34 | overlap | `int` | — |
| tagStageRoleData | 56 | m_nEffParam38 | overlap | `int` | — |
| tagStageRoleData | 60 | m_nEffParam3C | overlap | `int` | — |
| tagStageRoleData | 64 | m_nEffParam40 | overlap | `int` | — |
| tagStageRoleData | 68 | m_nEffParam44 | overlap | `int` | — |
| tagStageRoleData | 72 | m_nEffParam48 | overlap | `int` | — |
| tagStageRoleData | 76 | m_nEffParam4C | overlap | `int` | — |
| tagStageRoleData | 80 | m_nEffParam50 | overlap | `int` | — |
| tagStageRoleData | 84 | m_nEffParam2 | overlap | `int` | — |
| tagStageRoleData | 88 | m_nEffParam58 | overlap | `int` | — |

## 7. `_inline_*` 引用 vs 定义对称性

| 项 | 数量 |
|---|---|
| 引用（成员 type 里的合成名） | 27 |
| 定义（ida_structs 顶层 `_inline_*` 键） | 27 |
| 引用无定义 | 0 |
| 定义未被引用 | 0 |

## 8. 逐类差异（成员数 / 偏移 / 类型）

每类一行：成员数（注解/导出）+ 差异计数（拼写/类型/位面/缺口/新增）。

| 类 | 成员数(注解/导出) | 拼写归一 | 类型差异 | 位面复用 | 缺失 | 新增 |
|---|---|---|---|---|---|---|
| ARC_ArcBrief | 4/4 | 1 | 0 | 0 | 0 | 0 |
| ARC_ArcHeader | 14/14 | 8 | 0 | 0 | 0 | 0 |
| ARC_ArcLocaleRole | 2/2 | 1 | 0 | 0 | 0 | 0 |
| ARC_ArcMsic | 17/17 | 9 | 0 | 0 | 0 | 0 |
| ARC_ComboAttack | 12/12 | 6 | 0 | 0 | 0 | 0 |
| ARC_FightItem | 28/28 | 14 | 0 | 0 | 0 | 0 |
| ARC_FightSkill | 28/28 | 10 | 0 | 0 | 0 | 0 |
| ARC_Inventory | 4/4 | 0 | 2 | 0 | 0 | 0 |
| ARC_MonsterStar | 4/4 | 1 | 0 | 0 | 0 | 0 |
| ARC_OutFile | 9/9 | 4 | 0 | 0 | 0 | 0 |
| ARC_PlayerAtt | 25/25 | 4 | 0 | 0 | 0 | 0 |
| ARC_PlayerItem | 3/3 | 2 | 0 | 0 | 0 | 0 |
| ARC_PlayerMgrInfo | 10/10 | 2 | 0 | 0 | 0 | 0 |
| ARC_Reoccupy | 1/1 | 0 | 1 | 0 | 0 | 0 |
| ARC_RoleAtt | 19/19 | 2 | 0 | 0 | 0 | 0 |
| ASISTAGE | 24/24 | 18 | 0 | 0 | 0 | 0 |
| Actor | 118/118 | 3 | 0 | 2 | 0 | 0 |
| ArcBrief | 4/4 | 1 | 0 | 0 | 0 | 0 |
| ArcHeader | 14/14 | 9 | 0 | 0 | 0 | 0 |
| ArcLocale | 16/16 | 1 | 0 | 0 | 0 | 0 |
| ArcLocaleRole | 5/5 | 1 | 0 | 0 | 0 | 0 |
| ArcMsic | 9/9 | 3 | 0 | 0 | 0 | 0 |
| ArcScene | 3/3 | 0 | 2 | 0 | 0 | 0 |
| ArcSceneMonster | 12/12 | 0 | 0 | 3 | 0 | 0 |
| Archive | 3/3 | 0 | 3 | 0 | 0 | 0 |
| ArtistPlugIn | 8/8 | 1 | 0 | 0 | 0 | 0 |
| Average | 8/8 | 3 | 0 | 0 | 0 | 0 |
| BINK | 95/95 | 85 | 0 | 0 | 0 | 0 |
| BINKIO | 20/20 | 13 | 0 | 0 | 0 | 0 |
| BINKRECT | 4/4 | 4 | 0 | 0 | 0 | 0 |
| BINKSND | 17/17 | 9 | 0 | 0 | 0 | 0 |
| C3DSpark_tagSpark | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CAccelCentripetalPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CCBAI | 14/14 | 1 | 0 | 2 | 0 | 0 |
| CCBCamControl | 37/37 | 0 | 0 | 1 | 0 | 0 |
| CCBEditor | 14/14 | 1 | 0 | 0 | 0 | 0 |
| CCBStage | 75/75 | 1 | 0 | 2 | 0 | 0 |
| CCBStageScene | 109/109 | 0 | 0 | 1 | 0 | 0 |
| CCBTaskSlot | 9/9 | 0 | 0 | 2 | 0 | 0 |
| CCBTaskSlot208 | 12/12 | 0 | 0 | 1 | 0 | 0 |
| CCBUI | 57/57 | 0 | 0 | 1 | 0 | 0 |
| CCBUIPanel | 58/58 | 0 | 1 | 1 | 0 | 0 |
| CCBUI_funcptr_t | 2/2 | 1 | 0 | 0 | 0 | 0 |
| CCCTData | 3/3 | 1 | 0 | 0 | 0 | 0 |
| CCentripetalPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CDamplyCentripetalPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffCamera | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffCustomShape | 22/22 | 0 | 1 | 0 | 0 | 0 |
| CEffMgr | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffTemplate | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffTime | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffectBubble | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffectSimple | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CFadeInAlphaPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CFadeOutAlphaPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CG_Scene | 34/34 | 1 | 0 | 0 | 0 | 0 |
| CG_Scene_ArrayErase | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CG_UI | 63/63 | 1 | 0 | 0 | 0 | 0 |
| CGameData | 115/114 | 1 | 0 | 4 | 0 | 0 |
| CONTEXT | 23/23 | 23 | 0 | 0 | 0 | 0 |
| CPPEH_RECORD | 3/3 | 2 | 0 | 0 | 0 | 0 |
| CParticleSystem | 31/31 | 0 | 2 | 0 | 0 | 0 |
| CParticleSystem_ParticleAttribute | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CParticleSystem_ParticleUnit | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CRandomColorPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CRenderTarget | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CRenderTarget2 | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CSEHException | 2/2 | 1 | 0 | 0 | 0 | 0 |
| CScreenMode | 88/88 | 0 | 0 | 3 | 0 | 0 |
| CSimpleDirPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CSimplePosPolicy | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffAction | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffBink | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffShock | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffTime | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CTrail | 11/11 | 2 | 0 | 0 | 0 | 0 |
| CUSTOMSHAPEVERTEX | 4/4 | 1 | 0 | 0 | 0 | 0 |
| CUtil | 18/18 | 1 | 0 | 0 | 0 | 0 |
| CameraCtrl | 88/88 | 2 | 0 | 1 | 0 | 0 |
| CameraSystem | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CatchableType | 5/5 | 1 | 0 | 0 | 0 | 0 |
| Combat | 0/1 | 0 | 0 | 0 | 0 | 1 |
| ComboAttack | 13/13 | 6 | 0 | 0 | 0 | 0 |
| Comp_Donate | 3/3 | 1 | 0 | 0 | 0 | 0 |
| Comp_Donate_Detail | 9/9 | 4 | 0 | 0 | 0 | 0 |
| Config | 1/1 | 1 | 0 | 0 | 0 | 0 |
| DICOLORSET | 9/9 | 9 | 0 | 0 | 0 | 0 |
| DIDEVCAPS | 11/11 | 11 | 0 | 0 | 0 | 0 |
| DIDEVICEINSTANCEA | 9/9 | 4 | 0 | 0 | 0 | 0 |
| DIDEVICEOBJECTDATA | 5/5 | 5 | 0 | 0 | 0 | 0 |
| DIDEVICEOBJECTINSTANCEA | 15/15 | 13 | 0 | 0 | 0 | 0 |
| DIEFFECT | 14/14 | 11 | 0 | 0 | 0 | 0 |
| DIEFFECTINFOA | 6/6 | 4 | 0 | 0 | 0 | 0 |
| DIEFFESCAPE | 6/6 | 4 | 0 | 0 | 0 | 0 |
| DIENVELOPE | 5/5 | 5 | 0 | 0 | 0 | 0 |
| DIFILEEFFECT | 4/4 | 1 | 0 | 0 | 0 | 0 |
| DIPROPDWORD | 2/2 | 1 | 0 | 0 | 0 | 0 |
| DIPROPHEADER | 4/4 | 4 | 0 | 0 | 0 | 0 |
| DPINFO | 3/3 | 2 | 0 | 0 | 0 | 0 |
| DPINFO___unnamed | 0/1 | 0 | 0 | 0 | 0 | 1 |
| DealUI | 23/23 | 3 | 0 | 0 | 0 | 0 |
| ECBRoleSpecState | 0/1 | 0 | 0 | 0 | 0 | 1 |
| EH3_EXCEPTION_REGISTRATION | 4/4 | 2 | 0 | 0 | 0 | 0 |
| EffectInfo | 4/4 | 2 | 0 | 0 | 0 | 0 |
| EffectItem | 3/3 | 0 | 1 | 0 | 0 | 0 |
| EquipUI | 90/90 | 5 | 0 | 0 | 0 | 0 |
| ExternalStatistics | 0/1 | 0 | 0 | 0 | 0 | 1 |
| FLOATING_SAVE_AREA | 8/8 | 8 | 0 | 0 | 0 | 0 |
| FLTSTAGE | 2/2 | 1 | 0 | 0 | 0 | 0 |
| FightItem | 29/29 | 14 | 0 | 1 | 0 | 0 |
| FightSkill | 28/28 | 10 | 0 | 0 | 0 | 0 |
| GRPinput | 38/38 | 23 | 0 | 0 | 0 | 0 |
| GhostParam | 5/5 | 1 | 0 | 0 | 0 | 0 |
| HandlerType | 4/4 | 0 | 1 | 0 | 0 | 0 |
| HeadMsg | 5/5 | 0 | 1 | 0 | 0 | 0 |
| InputSystem | 0/1 | 0 | 0 | 0 | 0 | 1 |
| Inventory | 4/4 | 0 | 2 | 0 | 0 | 0 |
| Iostream_init | 0/1 | 0 | 0 | 0 | 0 | 1 |
| JusticeBookUI | 48/48 | 2 | 0 | 0 | 0 | 0 |
| LARGE_INTEGER | 4/4 | 1 | 0 | 0 | 0 | 0 |
| LINEUPINFO | 1/1 | 1 | 0 | 0 | 0 | 0 |
| LINEUP_SEQUENCE | 1/1 | 1 | 0 | 0 | 0 | 0 |
| LayerNode | 4/4 | 0 | 1 | 0 | 0 | 0 |
| LineupComp | 14/14 | 2 | 0 | 1 | 0 | 0 |
| LineupUI | 65/65 | 3 | 0 | 0 | 0 | 0 |
| Logger | 12/12 | 0 | 0 | 2 | 0 | 0 |
| MUIDialog | 11/11 | 0 | 0 | 2 | 0 | 0 |
| MXCEft | 4/4 | 2 | 0 | 0 | 0 | 0 |
| MXFire | 8/8 | 1 | 0 | 0 | 0 | 0 |
| MagicUI | 76/76 | 3 | 0 | 0 | 0 | 0 |
| MainEquipUI | 76/76 | 2 | 0 | 0 | 0 | 0 |
| MainPropUI | 80/80 | 2 | 0 | 0 | 0 | 0 |
| Math | 0/1 | 0 | 0 | 0 | 0 | 1 |
| MatrixStack | 0/1 | 0 | 0 | 0 | 0 | 1 |
| MeshFxCreator | 0/1 | 0 | 0 | 0 | 0 | 1 |
| MiniGame1 | 0/1 | 0 | 0 | 0 | 0 | 1 |
| MiniGame2Scene | 0/1 | 0 | 0 | 0 | 0 | 1 |
| MiniGame3 | 0/1 | 0 | 0 | 0 | 0 | 1 |
| MonsterStar | 4/4 | 1 | 0 | 0 | 0 | 0 |
| MvcController | 0/1 | 0 | 0 | 0 | 0 | 1 |
| MvcViewport | 0/1 | 0 | 0 | 0 | 0 | 1 |
| NMHDR | 3/3 | 2 | 0 | 0 | 0 | 0 |
| NPC | 19/19 | 1 | 0 | 0 | 0 | 0 |
| NPCInfo | 21/21 | 4 | 0 | 0 | 0 | 0 |
| NameSys_NAMEFLAG | 0/1 | 0 | 0 | 0 | 0 | 1 |
| NavFace | 1/1 | 1 | 0 | 0 | 0 | 0 |
| NavFaceLayer | 5/5 | 2 | 0 | 0 | 0 | 0 |
| NavHeader | 5/5 | 1 | 0 | 0 | 0 | 0 |
| Note_Item | 12/12 | 1 | 0 | 0 | 0 | 0 |
| ObjParam | 13/13 | 2 | 0 | 0 | 0 | 0 |
| ObjectCamera | 19/19 | 1 | 0 | 0 | 0 | 0 |
| ObjectInfo | 34/34 | 11 | 0 | 0 | 0 | 0 |
| OpenSceneFile | 0/1 | 0 | 0 | 0 | 0 | 1 |
| OutFile | 9/9 | 4 | 0 | 0 | 0 | 0 |
| PAL3 | 43/43 | 2 | 0 | 0 | 0 | 0 |
| PARTICLEVERTEX | 4/4 | 2 | 0 | 0 | 0 | 0 |
| PalScript | 63/62 | 1 | 0 | 5 | 0 | 0 |
| PalScriptDialogOverlay | 1/1 | 0 | 0 | 1 | 0 | 0 |
| PalScriptMgr | 202/202 | 10 | 0 | 0 | 0 | 0 |
| PalScriptRoleSlotOverlay | 1/1 | 0 | 0 | 1 | 0 | 0 |
| ParabolaCalculator_PRBL_STATE | 0/1 | 0 | 0 | 0 | 0 | 1 |
| Param0 | 5/5 | 4 | 0 | 0 | 0 | 0 |
| Param1 | 5/5 | 4 | 0 | 0 | 0 | 0 |
| Param2 | 8/8 | 7 | 0 | 0 | 0 | 0 |
| Parent_Data | 0/1 | 0 | 0 | 0 | 0 | 1 |
| PlayerAtt | 24/24 | 6 | 0 | 0 | 0 | 0 |
| PlayerItem | 3/3 | 1 | 0 | 0 | 0 | 0 |
| PlayerSkill | 4/4 | 3 | 0 | 0 | 0 | 0 |
| PropUI | 95/95 | 1 | 0 | 0 | 0 | 0 |
| PurgeEffect | 6/6 | 0 | 1 | 0 | 0 | 0 |
| RGNDATAHEADER | 5/5 | 4 | 0 | 0 | 0 | 0 |
| RenderTarget2 | 0/1 | 0 | 0 | 0 | 0 | 1 |
| RenderTarget4 | 0/1 | 0 | 0 | 0 | 0 | 1 |
| RenderTargetNode | 0/1 | 0 | 0 | 0 | 0 | 1 |
| Reoccupy | 1/1 | 0 | 1 | 0 | 0 | 0 |
| Role | 47/47 | 0 | 1 | 0 | 0 | 0 |
| RoleAtt | 35/35 | 16 | 0 | 1 | 0 | 0 |
| RoleAttRemarkSkills | 1/1 | 0 | 0 | 1 | 0 | 0 |
| RoleCameraCtrl | 15/15 | 0 | 0 | 2 | 0 | 0 |
| RoleStatePanel | 10/10 | 1 | 0 | 1 | 0 | 0 |
| RoleSystem | 152/152 | 1 | 0 | 4 | 0 | 0 |
| RoleSystemTeamSlotOverlay | 1/1 | 0 | 0 | 1 | 0 | 0 |
| RoleTask | 5/5 | 1 | 0 | 0 | 0 | 0 |
| RoleTaskPool | 4/4 | 0 | 2 | 0 | 0 | 0 |
| Role_SPECIAL_ACTION | 0/1 | 0 | 0 | 0 | 0 | 1 |
| SCNHeader | 6/6 | 5 | 0 | 0 | 0 | 0 |
| SPECIAL_ACTION | 0/1 | 0 | 0 | 0 | 0 | 1 |
| S_Distribute | 4/4 | 1 | 0 | 0 | 0 | 0 |
| SaleUI | 65/62 | 3 | 0 | 0 | 0 | 0 |
| SaleUI_SortData | 0/1 | 0 | 0 | 0 | 0 | 1 |
| SceHeader | 3/3 | 1 | 0 | 0 | 0 | 0 |
| SceIndex | 3/3 | 2 | 0 | 0 | 0 | 0 |
| SceOpcodeEntry | 5/5 | 2 | 0 | 0 | 0 | 0 |
| SceneInfo | 7/7 | 2 | 0 | 0 | 0 | 0 |
| SceneMap | 3/3 | 1 | 0 | 0 | 0 | 0 |
| SceneMgr | 23/23 | 1 | 0 | 3 | 0 | 0 |
| SceneObj | 46/46 | 0 | 1 | 0 | 0 | 0 |
| SceneObj_Common_State | 0/1 | 0 | 0 | 0 | 0 | 1 |
| SceneObj_SubObj | 0/1 | 0 | 0 | 0 | 0 | 1 |
| SceneProp | 15/15 | 1 | 0 | 0 | 0 | 0 |
| ScreenEffectMgr | 16/16 | 1 | 0 | 0 | 0 | 0 |
| ScriptData | 7/7 | 1 | 0 | 0 | 0 | 0 |
| ScriptHelper | 0/1 | 0 | 0 | 0 | 0 | 1 |
| ScriptObj | 0/1 | 0 | 0 | 0 | 0 | 1 |
| ScriptPoolPage | 5/5 | 4 | 0 | 0 | 0 | 0 |
| ScriptSystemData | 216/216 | 37 | 0 | 8 | 0 | 0 |
| ScriptVM | 26/26 | 0 | 1 | 0 | 0 | 0 |
| SkyboxEff | 24/24 | 1 | 0 | 0 | 0 | 0 |
| SoundAttachObj | 3/3 | 1 | 0 | 0 | 0 | 0 |
| SoundContext | 0/1 | 0 | 0 | 0 | 0 | 1 |
| SoundItem | 2/2 | 1 | 0 | 0 | 0 | 0 |
| SoundMgr | 13/13 | 0 | 2 | 0 | 0 | 0 |
| SoundSystem | 0/1 | 0 | 0 | 0 | 0 | 1 |
| StateUI | 66/66 | 2 | 0 | 0 | 0 | 0 |
| String | 0/1 | 0 | 0 | 0 | 0 | 1 |
| SwitchVariable | 1/1 | 1 | 0 | 0 | 0 | 0 |
| SwordUI | 134/134 | 3 | 0 | 0 | 0 | 0 |
| SystemUI | 64/64 | 2 | 0 | 1 | 0 | 0 |
| TaskBookUI | 46/46 | 1 | 0 | 0 | 0 | 0 |
| TextureLib | 40/40 | 0 | 0 | 1 | 0 | 0 |
| ThrowInfo | 3/3 | 1 | 0 | 0 | 0 | 0 |
| TileMap | 0/1 | 0 | 0 | 0 | 0 | 1 |
| TimeCtl | 3/3 | 2 | 0 | 0 | 0 | 0 |
| UIAnimCtrl | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIAnimate | 5/5 | 2 | 0 | 0 | 0 | 0 |
| UIBase | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIBigDialog | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIButton_UIBUTTON_STATE | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIChatRest | 38/38 | 1 | 0 | 0 | 0 | 0 |
| UICoverFrm | 51/51 | 1 | 0 | 0 | 0 | 0 |
| UICursor | 6/6 | 1 | 0 | 0 | 0 | 0 |
| UIGameFrm | 27/27 | 1 | 0 | 1 | 0 | 0 |
| UIGroupCtrl | 19/19 | 1 | 0 | 0 | 0 | 0 |
| UIInventory | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIListBox | 24/24 | 1 | 0 | 0 | 0 | 0 |
| UIListView | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIManager | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIObj | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIPar_TimeCtrl | 3/3 | 2 | 0 | 0 | 0 | 0 |
| UIParabolaCtrl | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIParticle | 42/42 | 1 | 0 | 0 | 0 | 0 |
| UIQuadManager | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIRenderObj | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIRoleDialog | 14/13 | 1 | 0 | 0 | 0 | 0 |
| UISceneObj | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIScrollBar_SB_AREA | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UISelectDialog | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UISlider | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UIStaticFlex_State | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UISystem | 0/1 | 0 | 0 | 0 | 0 | 1 |
| UITabBtn | 3/3 | 0 | 1 | 0 | 0 | 0 |
| UITitle_JDHY | 28/28 | 1 | 0 | 0 | 0 | 0 |
| VertPoolMgr | 0/1 | 0 | 0 | 0 | 0 | 1 |
| VideoPlayer | 0/1 | 0 | 0 | 0 | 0 | 1 |
| WAVEFORMAT | 5/5 | 5 | 0 | 0 | 0 | 0 |
| _ADPCMDATATAG | 11/11 | 11 | 0 | 0 | 0 | 0 |
| _Btn_BtnID | 2/2 | 1 | 0 | 0 | 0 | 0 |
| _CONTEXT | 25/25 | 24 | 0 | 0 | 0 | 0 |
| _Collvec | 2/2 | 2 | 0 | 0 | 0 | 0 |
| _Console__ConCmd | 0/1 | 0 | 0 | 0 | 0 | 1 |
| _Ctypevec | 4/4 | 3 | 0 | 0 | 0 | 0 |
| _Cvtvec | 2/2 | 2 | 0 | 0 | 0 | 0 |
| _DIACTIONA | 7/7 | 6 | 0 | 0 | 0 | 0 |
| _DIACTIONFORMATA | 14/14 | 9 | 0 | 0 | 0 | 0 |
| _DICOLORSET | 9/9 | 9 | 0 | 0 | 0 | 0 |
| _DICONFIGUREDEVICESPARAMSA | 8/8 | 3 | 0 | 0 | 0 | 0 |
| _DIDATAFORMAT | 6/6 | 5 | 0 | 0 | 0 | 0 |
| _DIDEVICEIMAGEINFOA | 9/9 | 5 | 0 | 0 | 0 | 0 |
| _DIDEVICEIMAGEINFOHEADERA | 9/9 | 8 | 0 | 0 | 0 | 0 |
| _DIG_DRIVER | 68/68 | 52 | 0 | 0 | 0 | 0 |
| _DIOBJECTDATAFORMAT | 4/4 | 3 | 0 | 0 | 0 | 0 |
| _EH3_EXCEPTION_REGISTRATION | 4/4 | 2 | 0 | 0 | 0 | 0 |
| _EXCEPTION_RECORD | 6/6 | 1 | 0 | 0 | 0 | 0 |
| _FLOATING_SAVE_AREA | 9/9 | 9 | 0 | 0 | 0 | 0 |
| _FLTPROVIDER | 18/18 | 2 | 0 | 0 | 0 | 0 |
| _IMAGE_DATA_DIRECTORY | 2/2 | 2 | 0 | 0 | 0 | 0 |
| _IMAGE_DOS_HEADER | 19/19 | 19 | 0 | 0 | 0 | 0 |
| _IMAGE_FILE_HEADER | 7/7 | 7 | 0 | 0 | 0 | 0 |
| _IMAGE_NT_HEADERS | 3/3 | 1 | 0 | 0 | 0 | 0 |
| _IMAGE_OPTIONAL_HEADER | 31/31 | 28 | 0 | 0 | 0 | 0 |
| _Item | 6/6 | 1 | 2 | 0 | 0 | 0 |
| _LARGE_INTEGER | 2/2 | 1 | 0 | 0 | 0 | 0 |
| _PURGE_INFO | 2/2 | 2 | 0 | 0 | 0 | 0 |
| _PlugInfo | 16/16 | 10 | 0 | 0 | 0 | 0 |
| _RGNDATAHEADER | 5/5 | 4 | 0 | 0 | 0 | 0 |
| _SAMPLE | 50/50 | 36 | 0 | 0 | 0 | 0 |
| _SCOPETABLE_ENTRY | 3/3 | 0 | 2 | 0 | 0 | 0 |
| _STREAM | 50/50 | 44 | 0 | 0 | 0 | 0 |
| _Texture_Info | 14/14 | 7 | 0 | 0 | 0 | 0 |
| _TimeMgr | 3/3 | 2 | 0 | 0 | 0 | 0 |
| _UDACCEL | 2/2 | 2 | 0 | 0 | 0 | 0 |
| _UIPOS | 3/3 | 1 | 0 | 0 | 0 | 0 |
| _XCPT_ACTION | 3/3 | 1 | 0 | 0 | 0 | 0 |
| _btnOPTDATA | 4/4 | 4 | 0 | 0 | 0 | 0 |
| _count_string | 3/3 | 2 | 0 | 0 | 0 | 0 |
| _cpinfo | 3/3 | 2 | 0 | 0 | 0 | 0 |
| _s__CatchableType | 5/5 | 1 | 0 | 0 | 0 | 0 |
| code_page_info | 3/3 | 2 | 0 | 0 | 0 | 0 |
| collision | 0/1 | 0 | 0 | 0 | 0 | 1 |
| direction_emitter_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| elelife_emitter_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| elerandvec_emitter_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| emissionrate_emitter_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| errentry | 2/2 | 1 | 0 | 0 | 0 | 0 |
| gbFileStream | 0/1 | 0 | 0 | 0 | 0 | 1 |
| gbGammaRamp | 3/3 | 3 | 0 | 0 | 0 | 0 |
| gbGfxManager_D3D | 30/30 | 1 | 0 | 0 | 0 | 0 |
| gbImage2D | 9/9 | 1 | 0 | 0 | 0 | 0 |
| gbMeshData | 0/1 | 0 | 0 | 0 | 0 | 1 |
| gbMeshMemCache | 4/4 | 1 | 0 | 0 | 0 | 0 |
| gbPrintFont | 18/18 | 1 | 0 | 0 | 0 | 0 |
| gbRenderEffect_D3D | 0/1 | 0 | 0 | 0 | 0 | 1 |
| gbSceneNode | 0/1 | 0 | 0 | 0 | 0 | 1 |
| gbSingleton_gbGfxManager | 0/1 | 0 | 0 | 0 | 0 | 1 |
| gbTexFlipAnim | 4/4 | 1 | 0 | 0 | 0 | 0 |
| gbVertexElement | 6/6 | 2 | 0 | 0 | 0 | 0 |
| gbVolumeModifier | 0/1 | 0 | 0 | 0 | 0 | 1 |
| h3DPOBJECT | 1/1 | 1 | 0 | 0 | 0 | 0 |
| ioinfo | 3/3 | 1 | 0 | 0 | 0 | 0 |
| localVar0 | 3/3 | 3 | 0 | 0 | 0 | 0 |
| localVar1 | 5/5 | 5 | 0 | 0 | 0 | 0 |
| localVar2 | 4/4 | 3 | 0 | 0 | 0 | 0 |
| magic_tab | 4/4 | 1 | 0 | 0 | 0 | 0 |
| pcmwaveformat_tag | 2/2 | 1 | 0 | 0 | 0 | 0 |
| primitive | 3/3 | 1 | 0 | 0 | 0 | 0 |
| rgbcolor_particle_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| rotation_particle_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| rotmulti_emitter_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| s_SpecialPropItem | 2/2 | 1 | 0 | 0 | 0 | 0 |
| scCmdDef | 3/3 | 2 | 0 | 0 | 0 | 0 |
| scScriptBlock | 7/7 | 5 | 0 | 0 | 0 | 0 |
| scScriptInstance | 7/7 | 1 | 0 | 0 | 0 | 0 |
| scUserVarInfo | 3/3 | 2 | 0 | 0 | 0 | 0 |
| scVARIANT | 3/3 | 1 | 0 | 0 | 0 | 0 |
| scVARIANT_data | 2/2 | 0 | 0 | 1 | 0 | 0 |
| size_particle_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| sizemulti_emitter_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| skill_tab | 2/2 | 1 | 0 | 0 | 0 | 0 |
| t3DModel | 4/4 | 0 | 2 | 0 | 0 | 0 |
| tChunk | 3/3 | 3 | 0 | 0 | 0 | 0 |
| tMaterialInfo | 9/9 | 1 | 0 | 0 | 0 | 0 |
| tag17A7BData | 8/8 | 0 | 0 | 8 | 0 | 0 |
| tag17A8Data | 11/11 | 0 | 0 | 11 | 0 | 0 |
| tagAttackSequen | 13/13 | 1 | 0 | 0 | 0 | 0 |
| tagC10Data | 13/13 | 0 | 0 | 13 | 0 | 0 |
| tagCCBStageData | 5/5 | 0 | 0 | 5 | 0 | 0 |
| tagCCT | 51/51 | 1 | 0 | 0 | 0 | 0 |
| tagCOPYDATASTRUCT | 3/3 | 2 | 0 | 0 | 0 | 0 |
| tagCPKHeader | 13/13 | 12 | 0 | 0 | 0 | 0 |
| tagCPKTable | 7/7 | 7 | 0 | 0 | 0 | 0 |
| tagCam | 6/6 | 0 | 0 | 1 | 0 | 0 |
| tagCamTask | 9/9 | 1 | 0 | 0 | 0 | 0 |
| tagCmdData | 9/9 | 3 | 0 | 1 | 0 | 0 |
| tagCombatTaskData | 69/69 | 0 | 0 | 49 | 0 | 0 |
| tagControlData | 4/4 | 2 | 0 | 0 | 0 | 0 |
| tagControlThread | 11/11 | 6 | 0 | 0 | 0 | 0 |
| tagDemand | 4/4 | 1 | 0 | 0 | 0 | 0 |
| tagEffClass | 0/1 | 0 | 0 | 0 | 0 | 1 |
| tagEffLinker | 17/17 | 1 | 0 | 0 | 0 | 0 |
| tagEffMgrData | 0/1 | 0 | 0 | 0 | 0 | 1 |
| tagEffObjType | 34/34 | 3 | 0 | 0 | 0 | 0 |
| tagEffTaskParam | 29/29 | 2 | 0 | 0 | 0 | 0 |
| tagHeader | 5/5 | 3 | 0 | 0 | 0 | 0 |
| tagLVITEMA | 10/10 | 1 | 0 | 0 | 0 | 0 |
| tagNMITEMACTIVATE | 9/9 | 1 | 0 | 0 | 0 | 0 |
| tagNewItem | 5/5 | 2 | 0 | 1 | 0 | 0 |
| tagPAL3GameState | 137/137 | 0 | 0 | 72 | 0 | 0 |
| tagPartical | 18/18 | 1 | 0 | 0 | 0 | 0 |
| tagQuad | 23/23 | 1 | 0 | 0 | 0 | 0 |
| tagRoleActionState | 38/38 | 1 | 0 | 0 | 0 | 0 |
| tagRoleSlot | 1/1 | 1 | 0 | 0 | 0 | 0 |
| tagRoleState | 53/53 | 5 | 0 | 0 | 0 | 0 |
| tagRoleSystemData | 16/16 | 0 | 0 | 12 | 0 | 0 |
| tagRoleTask | 10/10 | 1 | 0 | 1 | 0 | 0 |
| tagScriptCmd | 4/4 | 1 | 0 | 0 | 0 | 0 |
| tagStageRoleData | 26/26 | 0 | 0 | 23 | 0 | 0 |
| tagStageSubTask | 20/20 | 2 | 0 | 0 | 0 | 0 |
| tagStageTask | 10/10 | 2 | 0 | 0 | 0 | 0 |
| tagTCITEMA | 7/7 | 1 | 0 | 0 | 0 | 0 |
| tagThread | 9/9 | 3 | 0 | 0 | 0 | 0 |
| tagUITask | 9/9 | 1 | 0 | 0 | 0 | 0 |
| tagVAO | 4/4 | 1 | 0 | 0 | 0 | 0 |
| util | 6/6 | 1 | 0 | 0 | 0 | 0 |
| vertexalpha_particle_graph | 0/1 | 0 | 0 | 0 | 0 | 1 |
| waveformat_tag | 5/5 | 5 | 0 | 0 | 0 | 0 |
| wavehdr_tag | 8/8 | 6 | 0 | 0 | 0 | 0 |

## 9. 结构覆盖（单侧独有）

| 侧 | 数量 | 说明 |
|---|---|---|
| 仅导出（IDB 独有） | 310 | 多为 CRT/系统类型（无注解属预期） |
| 仅注解（导出缺） | 64 | 注解结构未见于导出 ⇒ 整类往返缺口，须查 apply 是否跳过 |

仅注解（导出缺）清单：

- `D3DAdapterInfo`
- `D3DDeviceCombo`
- `D3DDeviceInfo`
- `D3DDriverBug`
- `D3DXCOLOR`
- `D3DXFLOAT16`
- `D3DXMATRIX`
- `D3DXPlane`
- `D3DXVECTOR2`
- `D3DXVECTOR3`
- `D3DXVECTOR4`
- `HBRUSH__`
- `HDC__`
- `HHOOK__`
- `HICON__`
- `HINSTANCE__`
- `HKEY__`
- `HMONITOR__`
- `HWAVEOUT__`
- `HWND__`
- `_D3DADAPTER_IDENTIFIER9`
- `_D3DBOX`
- `_D3DCAPS9`
- `_D3DCLIPSTATUS9`
- `_D3DCOLORVALUE`
- `_D3DDEVICE_CREATION_PARAMETERS`
- `_D3DDISPLAYMODE`
- `_D3DGAMMARAMP`
- `_D3DINDEXBUFFER_DESC`
- `_D3DLIGHT9`
- `_D3DLOCKED_BOX`
- `_D3DLOCKED_RECT`
- `_D3DMATERIAL9`
- `_D3DMATRIX`
- `_D3DPRESENT_PARAMETERS_`
- `_D3DPSHADERCAPS2_0`
- `_D3DRASTER_STATUS`
- `_D3DRECT`
- `_D3DRECTPATCH_INFO`
- `_D3DSURFACE_DESC`
- `_D3DTRIPATCH_INFO`
- `_D3DVECTOR`
- `_D3DVERTEXBUFFER_DESC`
- `_D3DVERTEXELEMENT9`
- `_D3DVIEWPORT9`
- `_D3DVOLUME_DESC`
- `_D3DVSHADERCAPS2_0`
- `_D3DXEFFECT_DESC`
- `_D3DXFUNCTION_DESC`
- `_D3DXPARAMETER_DESC`
- `_D3DXPASS_DESC`
- `_D3DXSEMANTIC`
- `_D3DXTECHNIQUE_DESC`
- `_ThrowInfo`
- `__m64`
- `__old_sbh_page_struct`
- `__unnamed`
- `_s__ThrowInfo`
- `exception`
- `filebuf`
- `gbSingleton<gbGfxManager>`
- `std`
- `tagOFNA`
- `tagPOINT`

## 10. 口径附注

- **只读**：本工具不改任何输入；只写本报表。
- **陈旧拒报**：export 时间戳早于注解最新改动 ⇒ 拒报（rc=2），避免拿过期快照当读数（2026-10-19 陈旧验证误判同型坑）。
- **dict 形态识别**：inline union/struct（dict `type`）、`source:overlap`、同偏移 `_N` 变体键 ⇒ 位面复用（非偏移冲突），见 §6。
- **拼写归一只做等价变换**（§5 判据），不抹真实差异（§4）：STL 折叠 `char[N]`、指针级变化、const 丢失等都留在 §4。
- 配对键是 **(基偏移, 成员名)**：同偏移多视图靠名字区分，`12` / `12_1` 同基偏移属位面复用变体。
- 同输入 ⇒ 同输出：全表排序输出，不含 wall-clock。

