# 虚调用转换失败台账（Task 7）

生成物 —— 由 `pipeline/gen/stages/stage3_cleanup.py` 在**识别为虚调用但无法转换**时追加。
规格：`docs/superpowers/specs/2026-09-25-vtable-mapping-design.md` §4.3。

契约：失败时**原文逐字保留**（不降级为裸偏移形态），并在此记账。每行一个
`(方法, 形态, cls_hint, 字节偏移, 原因)` 唯一站点（幂等：重复运行不重复追加）。

| 位置 | 形态 | cls_hint(cast 首参) | 字节偏移 | 原因 | 原始调用文本 |
|---|---|---|---|---|---|
| `CCBPanelSlot::ShowWindow` | vftable_local | `int` | 24 | self_arg_mismatch | `(*(int ( **)(int, int, _DWORD))(v3 + 24))(1000, nFlags, 0)` |
| `CCBProtectWindow::RenderText` | inline | `UIWnd` | 12 | name_declared_at_other_address | `(*(void ( **)(UIWnd *))(*(_DWORD *)this + 12))(this)` |
| `CCBRoleState::~CCBRoleState` | inline | `char` | 32 | non_class_hint | `(*(void (**)(char *, _DWORD, int *, CCBRoleState *, int *, int))(*(_DWORD *)v6 + 32))( v6, *(int *)((char *)&dword_56B294 + i * 4), &v14, this, &this->m_bLockPropUI, v8)` |
| `CCBRoleState::~CCBRoleState` | vftable_local | `UIStatic` | 16 | self_arg_mismatch | `(*(void (**)(UIStatic *, _DWORD, _DWORD *, CCBRoleState *))(v10 + 16))(&this->m_Static_20408, 0, v18, this)` |
| `CCBRoleState::~CCBRoleState` | vftable_local | `UIScene` | 28 | self_arg_mismatch | `(*(void (**)(UIScene *, int, int *, CCBRoleState *, int, _DWORD, int))(v12 + 28))( &this->m_pScene, 177, &v14, this, off_5B1604, 0, v11)` |
| `CCBUIPanel::InitPanel` | inline | `char` | 32 | non_class_hint | `(*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[27].m_Widget + 32))( this->m_Slots[27].m_Widget, 294, &this->m_Slots[27], this, (` |
| `CCBUIPanel::sub_449C20` | inline | `char` | 4 | non_class_hint | `(*(void ( **)(char *))(*(_DWORD *)v2 + 4))(v2)` |
| `CGameData::InitRoles` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, unsigned __int8 *, tagRECT *, CGameData *))(*(_DWORD *)&p_m_subObjA->UIWnd + 16))( p_m_subObjA, g_PalScriptTemplate, &this->m_rcWidgetRect, this)` |
| `CGameData::Cleanup` | inline | `char` | 20 | non_class_hint | `(*(void ( **)(char *, int))(*(_DWORD *)m_pGameObj + 20))(m_pGameObj, 1)` |
| `CGameData::Cleanup` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)m_nMode + 20))(m_nMode, 1)` |
| `CGameData::ProcessDialog` | inline | `char` | 4 | non_class_hint | `(*(void ( **)(char *))(*(_DWORD *)this->m_pGameObj + 4))(this->m_pGameObj)` |
| `CGameData::_init_44f8d0` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v31 + 24))(v31, 1000, 1, 0)` |
| `CJ_FindFile::Create` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, int *, CJ_FindFile *))(v6 + 16))(&this->m_fileName[100], 2, &a2, this)` |
| `CJ_FindFile::Create` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, int *, CJ_FindFile *))(*(_DWORD *)&this->m_strRoot[272] + 16))( &this->m_strRoot[272], 2, &a2, this)` |
| `CScreenMode::InitGameUI` | inline | `UIButton` | 28 | self_arg_mismatch | `(*(void ( **)(UIButton *, int, int *, CScreenMode *, char *, _DWORD, int))(*(_DWORD *)&this->m_BtnTooltipC.UIWnd + 28))( &this->m_BtnTooltipC, 7, p_m_nUIState, this, aSubgameHocksh` |
| `ChoseCompose::Init` | inline | `ChoseCompose` | 24 | self_arg_mismatch | `(*(void ( **)(ChoseCompose *, int, int, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1000, 1, 0)` |
| `ChoseCompose::Init` | inline | `int` | 24 | self_arg_mismatch | `(*(void ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v3 + 24))(1000, 0, 0)` |
| `ChoseCompose::Init` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v6 + 24))(v6, 1000, 0, 0)` |
| `GRPinput::Create` | inline | `IDirectInput8` | 12 | no_vtables_declaration | `(*(int ( **)(IDirectInput8 *, int *, IDirectInputDevice8 **, _DWORD))(*(_DWORD *)this->m_lpDI + 12))( this->m_lpDI, &dword_573810, &this->m_lpDIDMouse, 0)` |
| `GRPinput::Create` | inline | `IDirectInputDevice8` | 44 | no_vtables_declaration | `(*(void ( **)(IDirectInputDevice8 *, int *))(*(_DWORD *)*p_m_lpDIDMouse + 44))( *p_m_lpDIDMouse, &dword_573C64)` |
| `GRPinput::Create` | inline | `IDirectInputDevice8` | 52 | no_vtables_declaration | `(*(void ( **)(IDirectInputDevice8 *, int, int))(*(_DWORD *)v7 + 52))(v7, hwnd, 5)` |
| `GRPinput::AcquireDevices` | inline | `int` | 28 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)result + 28))(result)` |
| `GRPinput::AcquireDevices` | inline | `IDirectInputDevice8` | 28 | no_vtables_declaration | `(*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)this->m_lpDIDMouse + 28))(this->m_lpDIDMouse)` |
| `GRPinput::_thunk_vtbl8` | inline | `IDirectInputDevice8` | 32 | no_vtables_declaration | `(*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)m_lpDIDMouse + 32))(m_lpDIDMouse)` |
| `GRPinput::ReleaseDevices` | inline | `int` | 28 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)result + 28))(result)` |
| `GRPinput::ReleaseDevices` | inline | `IDirectInputDevice8` | 28 | no_vtables_declaration | `(*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)this->m_lpDIDKeyboard + 28))(this->m_lpDIDKeyboard)` |
| `GRPinput::GRPinput` | inline | `IDirectInputDevice8` | 36 | no_vtables_declaration | `(*(int (__stdcall **)(IDirectInputDevice8 *, int, _BYTE *))(*(_DWORD *)this->m_lpDIDKeyboard + 36))( this->m_lpDIDKeyboard, 256, &this->m_keyStates[270])` |
| `PAL3::Update` | inline | `int` | 20 | non_class_hint | `(*(void (**)(int))(*(_DWORD *)g_nRenderMode + 20))(g_nRenderMode)` |
| `PAL3::Render` | inline | `gbGfxManager` | 48 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 48))(gfxMgr)` |
| `PAL3::Render` | inline | `gbGfxManager` | 52 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 52))(gfxMgr)` |
| `PAL3::Render` | inline | `gbGfxManager` | 112 | slot_out_of_range | `(*(void ( **)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr->_tail_000 + 112))(gfxMgr, &g_nPAL3_D8E488)` |
| `PAL3::Render` | inline | `_DWORD` | 4 | non_class_hint | `(*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(g_fGameSpeed) + 4))(LODWORD(g_fGameSpeed))` |
| `PAL3::PrintScreen` | inline | `gbGfxManager` | 84 | slot_out_of_range | `(*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)gfxMgr->_tail_000 + 84))(gfxMgr, &v24, 1)` |
| `PAL3::PrintScreen` | inline | `gbGfxManager` | 88 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `PAL3::LoadingTimerCallback` | inline | `int` | 8 | non_class_hint | `(*(void ( **)(int, _DWORD, int))(*(_DWORD *)g_nsub_41FA90_DC10FC + 8))( g_nsub_41FA90_DC10FC, LODWORD(DeltaTime), 1)` |
| `PAL3::SceneUpdate` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)v4 + 4))(v4)` |
| `PAL3::SceneUpdate` | inline | `_BYTE` | 8 | non_class_hint | `(*(void ( **)(_BYTE *, int, int))(*(_DWORD *)v5 + 8))(v5, nVal, nVal2)` |
| `PalScript::Op_Team` | inline | `UISceneMap` | 8 | self_arg_mismatch | `(*(void ( **)(UISceneMap *, _DWORD, _DWORD))(*(_DWORD *)&g_UISceneMapDlg.UIWnd + 8))( &g_UISceneMapDlg, 0, 0)` |
| `PalScript::Op_AddItem` | inline | `CCBItemWindow` | 8 | self_arg_mismatch | `(*(void ( **)(CCBItemWindow *, _DWORD, _DWORD))(*(_DWORD *)&v4->UIWnd + 8))(v4, 0, 0)` |
| `PalScriptMgr::BuildCmdTransform` | inline | `int` | 56 | non_class_hint | `(*(void ( **)(int, gbMatrix4 *))(*(_DWORD *)this->m_nTodo_058 + 56))( this->m_nTodo_058, pMatrix)` |
| `PalScriptMgr::UpdateScriptRoles` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)this->m_nTodo_058 + 24))( this->m_nTodo_058, -1082130432)` |
| `PalScriptMgr::OnAnimFinish` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_nTodo_058 + 24))(this->m_nTodo_058, 0)` |
| `PalScriptMgr::ExecuteOpcode` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_nTodo_058 + 24))(this->m_nTodo_058, 0)` |
| `PalScriptMgr::ExecuteFrame` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)this->m_nTodo_058 + 24))( this->m_nTodo_058, -1082130432)` |
| `PropUI::InitPlayerList` | vftable_local | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, _DWORD *, PropUI *))(v7 + 16))(&this->m_Frame, 513, v79, this)` |
| `PropUI::InitPlayerList` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int, _PlugInfo **, PropUI *, char *, _DWORD, int))(*(_DWORD *)&this->ml_ListProp.m_column[3].head[32] + 28))( 547, &this->ml_ListProp.m_scrollbar.m_texarrayInfo[5], t` |
| `PropUI::InitPlayerList` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, LONG *, PropUI *))(*(_DWORD *)&this->m_btnGroup.m_btnUp.m_caption[20] + 16))( &this->m_btnGroup.m_btnUp.m_caption[20], 272, &this->m_btnGroup.m_btnDw.m_r` |
| `PropUI::InitPlayerList` | vftable_local | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int, tagRECT *, PropUI *, char *, _DWORD, int))(v43 + 28))( &this->m_btnGroup.m_btnDw.m_caption[12], 518, &this->m_PropRemark.m_rect, this, aUiGamemainuiMu_0,` |
| `PropUI::InitPlayerList` | inline | `UIStatic` | 28 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int *, PropUI *, char *, _DWORD, int))(*(_DWORD *)&this->m_OutFrameT.UIWnd + 28))( &this->m_OutFrameT, 514, &this->m_Flag.m_FVF, this, aUiGamemainuiC` |
| `RoleAtt::Render` | inline | `char` | 4 | non_class_hint | `(*(int ( **)(char *))(*(_DWORD *)((char *)&this->Remark.skillCount + 74) + 4))((char *)&this->Remark.skillCount + 74)` |
| `RoleAtt::Destroy` | inline | `char` | 12 | non_class_hint | `(*(void ( **)(char *))(*(_DWORD *)((char *)&this->Remark.skillCount + 74) + 12))((char *)&this->Remark.skillCount + 74)` |
| `RoleAtt::HandleInput` | inline | `char` | 8 | non_class_hint | `(*(void ( **)(char *, int, int))(*(_DWORD *)((char *)&this->Remark.skillCount + 74) + 8))( (char *)&this->Remark.skillCount + 74, nVal, nVal2)` |
| `RoleShadow::InitFromTemplate` | inline | `float` | 32 | non_class_hint | `(*(void ( **)(float *, _DWORD, int *, RoleShadow *, _DWORD, int))(*(_DWORD *)p_z + 32))( p_z, *(int *)((char *)&dword_56B220 + v9), &v32, this, *(int *)((char *)&off_5AC088 + v9), ` |
| `RoleSystem::BindRoleToScene` | vftable_local | `RoleSystem` | 4 | self_arg_mismatch | `(*(int ( **)(RoleSystem *, int, int))(v11 + 4))(this, v24, nVal2)` |
| `RoleSystem::BindRoleToScene` | inline | `RoleSystem` | 4 | self_arg_mismatch | `(*(int ( **)(RoleSystem *, int *, int *))(*(_DWORD *)&this->UIWnd + 4))(this, v9, v10)` |
| `RoleSystem::RenderRole` | inline | `gbGeomNode` | 16 | self_arg_mismatch | `(*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)&this->m_pRenderObj->gbChain1DNode + 16))( this->m_pRenderObj, 0)` |
| `RoleSystem::UpdateActionState` | inline | `gbActor` | 24 | self_arg_mismatch | `(*(void ( **)(gbActor *, int))(*(_DWORD *)&this->m_partyActor.m_pActor->gbChain1DNode + 24))( this->m_partyActor.m_pActor, -1082130432)` |
| `RoleSystem::SetupMoveState` | inline | `gbActor` | 24 | self_arg_mismatch | `(*(void ( **)(gbActor *, int))(*(_DWORD *)&this->m_partyActor.m_pActor->gbChain1DNode + 24))( this->m_partyActor.m_pActor, -1082130432)` |
| `RoleSystem::UpdateFollowerMovement` | inline | `UISceneMap` | 8 | self_arg_mismatch | `(*(void ( **)(UISceneMap *, _DWORD, _DWORD))(*(_DWORD *)&g_UISceneMapDlg.UIWnd + 8))( &g_UISceneMapDlg, 0, 0)` |
| `RoleSystem::UpdateFollowerMovement` | inline | `gbActor` | 24 | self_arg_mismatch | `(*(void ( **)(gbActor *, int))(*(_DWORD *)&this->m_partyActor.m_pActor->gbChain1DNode + 24))( this->m_partyActor.m_pActor, 1075137304)` |
| `RoleSystem::LoadRoleImage` | inline | `unsigned __int8` | 4 | non_class_hint | `(*(void ( **)(unsigned __int8 *, _DWORD, int, int, _DWORD, int, unsigned __int8 *))(*(_DWORD *)v5 + 4))( v5, LODWORD(this->m_fScale), this->m_nImageIdx, 2, 0, 2, v6)` |
| `RoleSystem::CheckScriptTrigger` | inline | `float` | 32 | self_arg_mismatch | `(*(void ( **)(float, float *))(*(_DWORD *)LODWORD(m_fDirY) + 32))(_pal3_coerce_f32(LODWORD(m_fDirY)), v14)` |
| `RoleSystem::InitUICtrlArray` | inline | `char` | 16 | non_class_hint | `(*(int ( **)(char *, _DWORD, int *, RoleSystem *))(*(_DWORD *)v3 + 16))(v3, 0, &v17, this)` |
| `SaleUI::InitCombatUI` | inline | `SaleUI_SortData` | 16 | self_arg_mismatch | `(*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&v6 + 16))( &this->m_sort[353][4], 257, v165, this)` |
| `SaleUI::InitCombatUI` | inline | `SaleUI_SortData` | 28 | self_arg_mismatch | `(*(void ( **)(SaleUI_SortData *, int, _DWORD *, char *, _DWORD, SaleUI *))(*(_DWORD *)&v8 + 28))( &this->m_sort[349][3], 257, v162, aUiFlexFramebar, 0, this)` |
| `SaleUI::InitCombatUI` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, int *, SaleUI *))(v28 + 16))( &this->ml_ResumeList.m_column[0].head[16], 161, &v150, this)` |
| `SaleUI::InitCombatUI` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, UILBColumn *, SaleUI *))(*(_DWORD *)&this->ml_ResumeList.m_column[4].head[16] + 16))( &this->ml_ResumeList.m_column[4].head[16], 272, &this->ml_ResumeLis` |
| `SaleUI::InitCombatUI` | inline | `SaleUI_SortData` | 16 | no_vtables_declaration | `(*(void ( **)(SaleUI_SortData *, _DWORD, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[369][38 * v36 + 3] + 16))( &this->m_sort[369][38 * v36 + 3], *(&dword_56B3C8 + v36), v147, th` |
| `SaleUI::InitCombatUI` | inline | `_BYTE` | 16 | non_class_hint | `(*(void ( **)(_BYTE *, _DWORD, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 23][1] + 16))( &this->m_IsEquip[216 * *(_DWORD *)&this->rema` |
| `SaleUI::InitCombatUI` | inline | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int, char *, SaleUI *, char *, _DWORD, int))(*(_DWORD *)&this->ml_TreasureList.m_column[1].head[36] + 28))( &this->ml_TreasureList.m_column[1].head[36], 264, ` |
| `SaleUI::InitCombatUI` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int, char *, SaleUI *, char *, _DWORD, int))(*(_DWORD *)&this->m_Icon[2][4].m_mouseoff + 28))( 304, this->m_Icon[3][2].m_text, this, aUiAssistantEqu_18, 0, v142)` |
| `SaleUI::OnMessage` | inline | `SaleUI` | 24 | self_arg_mismatch | `(*(void ( **)(SaleUI *, int, _DWORD, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1007, 0, 0)` |
| `SceneObj::HideAll` | inline | `int` | 12 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)v3 + 12))(v3)` |
| `SceneObj::Update` | inline | `int` | 8 | non_class_hint | `(*(int ( **)(int, int, int))(*(_DWORD *)v7 + 8))(v7, a2, v6)` |
| `ScriptSystem::Render` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)dword_C10CBC + 16))(dword_C10CBC, 0)` |
| `ScriptSystem::UpdateTimers` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)(_ESI + 56) + 4))(_ESI + 56)` |
| `SystemUI::Render` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, _DWORD))(*(_DWORD *)this->m_NoteItem[98].m_NoteTime.m_childs.m_pData + 16))( this->m_NoteItem[98].m_NoteTime.m_childs.m_pData, 0)` |
| `SystemUI::UIUpdate` | inline | `char` | 20 | non_class_hint | `(*(void ( **)(char *))(*(_DWORD *)m_pData + 20))(m_pData)` |
| `UIAnimateCtrlEX::UIAnimateCtrlEX_Render` | inline | `int` | 4 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)(v1 + 748) + 4))(v1 + 748)` |
| `UIAnimateCtrlEX::ComputeStatBonus` | inline | `UITextArea` | 8 | self_arg_mismatch | `(*(void ( **)(UITextArea *, int, _DWORD))(*(_DWORD *)&this->m_TextArea.UIWnd + 8))( &this->m_TextArea, nVal, 0)` |
| `UIBigMap::LoadScene` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)this->bkWndY + 24))(this->bkWndY, 0)` |
| `UIBigMap::RenderRole` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_bcreateok + 16))(this->m_bcreateok, 0)` |
| `UIBigMap::RenderRole` | inline | `_DWORD` | 16 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD))(*(_DWORD *)LODWORD(v18.x) + 16))(LODWORD(v18.x), 0)` |
| `UIBigMap::RenderRole` | inline | `_DWORD` | 16 | self_arg_mismatch | `(*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(x) + 16))(0)` |
| `UIGameOver::Create` | vftable_local | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, _DWORD, int *, UIGameOver *))(v2 + 16))(&this->m_Blood, 0, &v3, this)` |
| `UIListBox::CalScrollBarRange` | vftable_local | `UIScrollBar` | 28 | self_arg_mismatch | `(*(void ( **)(UIScrollBar *, int, tagRECT *, UIListBox *, char *, int, _DWORD))(v14 + 28))( &this->m_scrollbar, 1, &this->m_scrollRc, this, aUiCommonScroll, 1, 0)` |
| `UIListBox::Update` | inline | `int` | 24 | self_arg_mismatch | `(*(void ( **)(int, unsigned int, int))(*(_DWORD *)v32 + 24))( 1008, this->m_id, this->m_locksel)` |
| `UIListBox::Update` | vftable_local | `int` | 24 | self_arg_mismatch | `(*(void ( **)(int, unsigned int, int))(v22 + 24))(1007, this->m_id, m_locksel)` |
| `UIListBox::ProcessSelection` | vftable_local | `int` | 24 | self_arg_mismatch | `(*(int ( **)(int, unsigned int, int))(v22 + 24))(1007, this->m_id, result)` |
| `UILoadingFrm::InitFullScreen` | vftable_local | `UIProgressBar` | 16 | self_arg_mismatch | `(*(void ( **)(UIProgressBar *, _DWORD, _DWORD *, UILoadingFrm *))(v2 + 16))( &this->m_LoadProgress, 0, v3, this)` |
| `UIProgressBar::Render` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)*v19 + 16))(*v19, 0)` |
| `UIProgressBar::CheckRayHitRole` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)*p_m_progress + 20))(*p_m_progress)` |
| `UIProgressBar::CheckRayHitRole` | inline | `int` | 24 | self_arg_mismatch | `(*(void ( **)(int, unsigned int, int))(*(_DWORD *)m_pfather + 24))(1013, this->m_id, v17)` |
| `UIPushButton::Update` | inline | `int` | 24 | self_arg_mismatch | `(*(void ( **)(int, unsigned int, _DWORD))(*(_DWORD *)m_pfather + 24))(1001, this->m_id, 0)` |
| `UIScene::RenderVertexPool` | inline | `_DWORD` | 20 | non_class_hint | `(*(int (**)(_DWORD, int))(*(_DWORD *)LODWORD(v33.y) + 20))(LODWORD(v33.y), 1)` |
| `UIScene::CombatCheck` | inline | `gbVisNode` | 16 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)&v2->m_lights->gbChain1DNode + 16))(v2->m_lights, 0)` |
| `UIScene::CheckMouseHit` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)m_nViewW + 24))( m_nViewW, 1019, LODWORD(this->m_fScaleY), (__int64)*((float *)&this->m_hTexture + 6))` |
| `UIScene::Destroy_C910` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)v2 + 20))(v2, 1)` |
| `UIScene::PostRender` | inline | `int` | 4 | non_class_hint | `(*(void ( **)(int, UIScenePanel *))(*(_DWORD *)m_hSettingsUI + 4))(m_hSettingsUI, this)` |
| `UIScene::StopAllSounds` | inline | `int` | 8 | non_class_hint | `(*(void ( **)(int, _DWORD, int))(*(_DWORD *)v29 + 8))(v29, LODWORD(fFade), nFlags)` |
| `UISceneFrm::Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)v2 + 20))(v2, 1)` |
| `UIScenePanel::CreateSettingsUI` | vftable_local | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, _DWORD, _DWORD *, UIScenePanel *))(v3 + 16))(&this->m_Static_360, 0, v58, this)` |
| `UIScenePanel::CreateSettingsUI` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(int ( **)(UIStatic *, _DWORD, float *, UIScenePanel *))(*(_DWORD *)&this->m_Static_10800.UIWnd + 16))( &this->m_Static_10800, 0, p_m_fScaleY, this)` |
| `UIScenePanel::CreateSettingsUI` | vftable_local | `UIScene` | 32 | self_arg_mismatch | `(*(int ( **)(UIScene *, int, int *, UIScenePanel *, int, int))(v18 + 32))( &this->m_SceneA, 161, &v46, this, off_59DDB4, v17)` |
| `UITitle::RunFrame` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)m_hEffect + 4))(m_hEffect)` |
| `UITitle::OnCommand` | inline | `UISceneMap` | 8 | self_arg_mismatch | `(*(void ( **)(UISceneMap *, _DWORD, _DWORD))(*(_DWORD *)&g_UISceneMapDlg.UIWnd + 8))( &g_UISceneMapDlg, 0, 0)` |
| `::EnumJoystick` | inline | `IDirectInputDevice8` | 32 | no_vtables_declaration | `(*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)m_lpDIDKeyboard + 32))(m_lpDIDKeyboard)` |
| `::WinProc(HWND__ *,uint,uint,long)` | inline | `_DWORD` | 44 | non_class_hint | `(*(void ( **)(_DWORD, LONG, LONG, int))(*(_DWORD *)LODWORD(v7[1].InvViewMatrix.xy) + 44))( LODWORD(v7[1].InvViewMatrix.xy), Point.x, Point.y, 1)` |
| `::ScriptUpdate` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)dword_C10CBC + 20))(dword_C10CBC)` |
| `::PalScriptIdleObj_LoadScriptTexture` | inline | `` | 12 | self_arg_mismatch | `(*(void (**)(void))(*(_DWORD *)v1 + 12))()` |
| `::UIListBox_IsVisible` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)(v1 + 1296) + 4))(v1 + 1296)` |
| `::UITitle_BBTY_CreateFromScript` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, _DWORD, tagRECT *, UIWnd *))(*(_DWORD *)&p_m_rect->UIWnd + 16))( p_m_rect, 0, &pRect, v2)` |
| `::TaskBookUI_CreateEntry` | vftable_local | `int` | 16 | non_class_hint | `(*(int ( **)(int, _DWORD, int, int))(v4 + 16))(v2 + 360, 0, v3, v2)` |
| `::TaskBookUI_CreateEntry` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int, _DWORD *, int, char *, _DWORD, int))(v11 + 28))( v2 + 512, 209, v52, v2, off_5B0950[0], 0, v10)` |
| `::UIFrameWnd_OnPaintUpdate` | inline | `int` | 24 | self_arg_mismatch | `(*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(1000, 0, 0)` |
| `::UIFrameWnd_OnPaintUpdate` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1000, 0, 0)` |
| `Actor::_todo_00496190` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, int *, Actor *))(v11 + 16))(&this[5].m_curact[27], 161, &v73, this)` |
| `Actor::_todo_00496190` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, char *, int *, Actor *, const char *, int, _DWORD))(*(_DWORD *)v64 + 28))( v64, (char *)*v59, nVal2, this, v14, 1, 0)` |
| `Actor::_todo_004B7560` | inline | `float` | 16 | self_arg_mismatch | `(*(void ( **)(float, _DWORD))(*(_DWORD *)LODWORD(m_fMatrixParamB) + 16))( _pal3_coerce_f32(LODWORD(m_fMatrixParamB)), 0)` |
| `Actor::_todo_004B7560` | inline | `Actor` | 12 | self_arg_mismatch | `(*(void ( **)(Actor *, _DWORD))(*(_DWORD *)&this->m_actarray_type + 12))(this, 0)` |
| `Actor::_todo_0051DFD0` | vftable_local | `char` | 16 | non_class_hint | `(*(int ( **)(char *, char *, int *, Actor *))(v29 + 16))( &this[1].m_curact[19], &byte_A01B00, &v117, this)` |
| `Actor::SetParam` | inline | `Actor` | 20 | self_arg_mismatch | `(*(int ( **)(Actor *))(*(_DWORD *)&m_actarray_begin->m_actarray_type + 20))(m_actarray_begin)` |
| `Actor::SetMaterialName` | inline | `gbActorDef` | 60 | self_arg_mismatch | `(*(void ( **)(gbActorDef *, char *))(*(_DWORD *)&v16->pBody->gbRefObject + 60))(v16->pBody, m_szTexture)` |
| `Actor::QueryState` | inline | `gbActor` | 20 | self_arg_mismatch | `(*(int ( **)(gbActor *))(*(_DWORD *)&this->m_pact->gbChain1DNode + 20))(this->m_pact)` |
| `Actor::DispatchAction` | inline | `gbActor` | 16 | self_arg_mismatch | `(*(int ( **)(gbActor *, int))(*(_DWORD *)&this->m_pact->gbChain1DNode + 16))(this->m_pact, actionId)` |
| `Actor::PlayAction` | inline | `gbActorDef` | 28 | self_arg_mismatch | `(*(int ( **)(gbActorDef *, int, gbActor *))(*(_DWORD *)&this->m_pact->pBody->gbRefObject + 28))( this->m_pact->pBody, actionId, this->m_pact)` |
| `Actor::SetTextureName` | inline | `gbActorDef` | 60 | self_arg_mismatch | `(*(void ( **)(gbActorDef *, char *))(*(_DWORD *)&this->m_pact->pBody->gbRefObject + 60))( this->m_pact->pBody, this->m_szTexture)` |
| `Actor::SetVisible` | inline | `gbActorDef` | 60 | self_arg_mismatch | `(*(void ( **)(gbActorDef *, char *))(*(_DWORD *)&v7->pBody->gbRefObject + 60))(v7->pBody, m_szTexture)` |
| `ArcLocaleRole::HandleKeyInput` | inline | `ArcLocaleRole` | 24 | self_arg_mismatch | `(*(int ( **)(ArcLocaleRole *, int, int *, _DWORD))(*(_DWORD *)&this->active + 24))( this, 1001, &byte_A00604, 0)` |
| `ArcLocaleRole::Destroy` | inline | `float` | 20 | self_arg_mismatch | `(*(void ( **)(float, int))(*(_DWORD *)LODWORD(rotate) + 20))(_pal3_coerce_f32(LODWORD(rotate)), 1)` |
| `CCBCamControl::SwitchEditorCamPos` | inline | `gbGeomNode` | 20 | self_arg_mismatch | `(*(int ( **)(gbGeomNode *))(*(_DWORD *)&this->m_pPointer->gbChain1DNode + 20))(this->m_pPointer)` |
| `CCBControlWindow::Create` | inline | `UIWnd` | 28 | slot_out_of_range | `(*(void ( **)(UIWnd *, int, tagRECT *, CCBControlWindow *, int, _DWORD))(*(_DWORD *)v7 + 28))( v7, nCtrlID, rc, this, nDataIdx, 0)` |
| `CCBControlWindow::OnMessage` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int *, CCBControlWindow *))(*(_DWORD *)&this->m_pBack->UIWnd + 16))( this->m_pBack, 161, pRect, this)` |
| `CCBControlWindow::OnMessage` | inline | `UIButton` | 28 | self_arg_mismatch | `(*(void ( **)(UIButton *, int, int *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)&(*p_m_pButtonSkill)->UIWnd + 28))( *p_m_pButtonSkill, *v10, pRect, this, 0, 0, 0)` |
| `CCBControlWindow::Update` | inline | `UIButton` | 20 | self_arg_mismatch | `(*(int ( **)(UIButton *, int))(*(_DWORD *)&m_pButtonSkill->UIWnd + 20))(m_pButtonSkill, 1)` |
| `CCBControlWindow::Update` | inline | `UIStatic` | 20 | self_arg_mismatch | `(*(int ( **)(UIStatic *, int))(*(_DWORD *)&m_pBack->UIWnd + 20))(m_pBack, 1)` |
| `CCBFiveNimbusWindow::Destroy` | inline | `UIButtonEX` | 20 | self_arg_mismatch | `(*(void ( **)(UIButtonEX *, int))(*(_DWORD *)&(*v2)->UIWnd + 20))(*v2, 1)` |
| `CCBFiveNimbusWindow::Destroy` | inline | `float` | 20 | self_arg_mismatch | `(*(void ( **)(float, int))(*(_DWORD *)LODWORD(fWaitTime) + 20))(_pal3_coerce_f32(LODWORD(fWaitTime)), 1)` |
| `CCBFiveNimbusWindow::Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1)` |
| `CCBItemWindow::CCBItemWindow_Destroy` | inline | `UIStatic` | 20 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int))(*(_DWORD *)&(*p_m_pDescription)->UIWnd + 20))(*p_m_pDescription, 1)` |
| `CCBItemWindow::CCBItemWindow_Destroy` | inline | `UIPushButton` | 20 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int))(*(_DWORD *)&m_pButtonTreasure->UIWnd + 20))(m_pButtonTreasure, 1)` |
| `CCBItemWindow::CCBItemWindow_Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)m_nActivePage + 20))(m_nActivePage, 1)` |
| `CCBItemWindow::Create` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int *, CCBItemWindow *))(*(_DWORD *)&(*p_m_pBack)->UIWnd + 16))( *p_m_pBack, 232, pRect, this)` |
| `CCBItemWindow::Create` | inline | `UIPushButton` | 28 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)&(*p_m_pButtonAttack)->UIWnd + 28))( *p_m_pButtonAttack, 214, pRect, this, g_nUnkDataTable[22], ` |
| `CCBItemWindow::Create` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)*p_m_nActivePage + 28))( *p_m_nActivePage, 216, pRect, this, g_nUnkDataTable[24], 0)` |
| `CCBItemWindow::Create` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, CCBItemWindow *))(*(_DWORD *)&(*p_m_pDescription)->UIWnd + 16))( *p_m_pDescription, g_nPropIDs_208[i], pRect, this)` |
| `CCBItemWindow::Destroy` | inline | `UIStatic` | 20 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int))(*(_DWORD *)&m_pBack->UIWnd + 20))(m_pBack, 1)` |
| `CCBItemWindow::Destroy` | inline | `UIPushButton` | 20 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int))(*(_DWORD *)&m_pButtonAttack->UIWnd + 20))(m_pButtonAttack, 1)` |
| `CCBItemWindow::Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)m_nActivePage + 20))(m_nActivePage, 1)` |
| `CCBMagicWindow::CreateButton` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, CCBMagicWindow *))(*(_DWORD *)&(*p_m_pBack)->UIWnd + 16))( *p_m_pBack, 272, ppButton, this)` |
| `CCBMagicWindow::CreateButton` | inline | `UIScene` | 16 | self_arg_mismatch | `(*(void ( **)(UIScene *, int, int *, CCBMagicWindow *))(*(_DWORD *)&(*v8)->UIWnd + 16))( *v8, g_nPropIDs_241[8], ppButton, this)` |
| `CCBMagicWindow::CreateButton` | inline | `UIListBox` | 28 | self_arg_mismatch | `(*(void ( **)(UIListBox *, int, int *, CCBMagicWindow *, void *, _DWORD))(*(_DWORD *)&(*m_pMagicList)->UIWnd + 28))( *m_pMagicList, g_nPropIDs_241[5], ppButton, this, &unk_5DF6F4, ` |
| `CCBMagicWindow::CreateButton` | inline | `UIPushButton` | 28 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, CCBMagicWindow *, void *, _DWORD))(*(_DWORD *)&(*v22)->UIWnd + 28))( *v22, g_nPropIDs_241[6], ppButton, this, &unk_5DF6D0, 0)` |
| `CCBMagicWindow::Destroy` | inline | `UIStatic` | 20 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int))(*(_DWORD *)&m_pBack->UIWnd + 20))(m_pBack, 1)` |
| `CCBMagicWindow::Destroy` | inline | `UIListBox` | 20 | self_arg_mismatch | `(*(void ( **)(UIListBox *, int))(*(_DWORD *)&v4->UIWnd + 20))(v4, 1)` |
| `CCBMagicWindow::Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1)` |
| `CCBMagicWindow::Destroy` | inline | `unsigned int` | 20 | non_class_hint | `(*(void ( **)(unsigned int, int))(*(_DWORD *)Color + 20))(Color, 1)` |
| `CCBMagicWindow::Destroy` | inline | `LONG` | 20 | non_class_hint | `(*(void ( **)(LONG, int))(*(_DWORD *)left + 20))(left, 1)` |
| `CCBParabolaWindow::CCBParabolaWindow` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void (**)(UIPushButton *, int, CCBParabolaWindow **, CCBParabolaWindow *))(*(_DWORD *)&(*p_m_wndcolor)->UIWnd + 16))( *p_m_wndcolor, 240, thisa, this)` |
| `CCBParabolaWindow::~CCBParabolaWindow` | inline | `unsigned int` | 20 | non_class_hint | `(*(void (**)(unsigned int, int))(*(_DWORD *)Color + 20))(Color, 1)` |
| `CCBParabolaWindow::Destroy` | inline | `int` | 4 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)v2 + 4))(v2)` |
| `CCBParabolaWindow::Destroy_c880` | inline | `LONG` | 20 | non_class_hint | `(*(int ( **)(LONG, int))(*(_DWORD *)*p_right + 20))(*p_right, 1)` |
| `CCBParabolaWindow::Destroy_c880` | inline | `UIStatic` | 20 | self_arg_mismatch | `(*(int ( **)(UIStatic *, int))(*(_DWORD *)&m_pBack->UIWnd + 20))(m_pBack, 1)` |
| `CCBParabolaWindow::Destroy_c880` | inline | `UIListBox` | 20 | self_arg_mismatch | `(*(int ( **)(UIListBox *, int))(*(_DWORD *)&m_pItemList->UIWnd + 20))(m_pItemList, 1)` |
| `CCBParabolaWindow::Destroy_c880` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1)` |
| `CCBParabolaWindow::Destroy_c880` | inline | `unsigned int` | 20 | non_class_hint | `(*(int ( **)(unsigned int, int))(*(_DWORD *)Color + 20))(Color, 1)` |
| `CCBParabolaWindow::Destroy_c880` | inline | `gbTexture` | 20 | self_arg_mismatch | `(*(int ( **)(gbTexture *, int))(*(_DWORD *)&m_pbktex->gbRefObject + 20))(m_pbktex, 1)` |
| `CCBProtectWindow::Destroy` | inline | `UIStatic` | 20 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int))(*(_DWORD *)&m_pBack->UIWnd + 20))(m_pBack, 1)` |
| `CCBProtectWindow::Destroy` | inline | `UIPushButton` | 20 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int))(*(_DWORD *)&(*p_m_pWHFace)->UIWnd + 20))(*p_m_pWHFace, 1)` |
| `CCBProtectWindow::Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1)` |
| `CCBProtectWindow::Destroy` | inline | `UIButton` | 20 | self_arg_mismatch | `(*(void ( **)(UIButton *, int))(*(_DWORD *)&(*v6)->UIWnd + 20))(*v6, 1)` |
| `CCBResultWindow::Destroy` | inline | `UIStatic` | 20 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int))(*(_DWORD *)&m_pBack->UIWnd + 20))(m_pBack, 1)` |
| `CCBRoleState::UpdatePanel` | inline | `_DWORD` | 112 | self_arg_mismatch | `(***(void ( ****)(_DWORD))(*(_DWORD *)(this->m_nStepSize + 1116) + 112))(0)` |
| `CCBRoleState::UpdatePanel` | inline | `int` | 112 | self_arg_mismatch | `(***(void ( ****)(int))(*(_DWORD *)(this->m_nStepSize + 1116) + 112))(1)` |
| `CCBRoleState::SetupCombatLayout` | vptr_read | `_DWORD` | 0 | self_arg_mismatch | `(***(void ( ****)(_DWORD, int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3))( *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3), 1)` |
| `CCBRoleState::Init` | vftable_local | `_DWORD` | 1068 | self_arg_mismatch | `(***(void ( ****)(_DWORD, int))(v3 + 1068))(*(_DWORD *)(v3 + 1068), 1)` |
| `CCBSkillWindow::Create` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int *, CCBSkillWindow *))(*(_DWORD *)&(*p_m_pBack)->UIWnd + 16))( *p_m_pBack, 513, pRect, this)` |
| `CCBSkillWindow::Create` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, CCBSkillWindow *))(*(_DWORD *)&(*p_right)->UIWnd + 16))( *p_right, 528, pRect, this)` |
| `CCBSkillWindow::Create` | inline | `UIListBox` | 16 | self_arg_mismatch | `(*(void ( **)(UIListBox *, int, int *, CCBSkillWindow *))(*(_DWORD *)&(*m_pSkillList)->UIWnd + 16))( *m_pSkillList, 547, pRect, this)` |
| `CCBSkillWindow::Create` | inline | `gbTexture` | 16 | self_arg_mismatch | `(*(void ( **)(gbTexture *, int, int *, CCBSkillWindow *))(*(_DWORD *)&(*p_m_pbktex)->gbRefObject + 16))( *p_m_pbktex, 544, pRect, this)` |
| `CCBSkillWindow::Create` | inline | `unsigned int` | 16 | non_class_hint | `(*(void ( **)(unsigned int, int, int *, CCBSkillWindow *))(*(_DWORD *)p_m_fontcolor->Color + 16))( p_m_fontcolor->Color, 517, pRect, this)` |
| `CCBSkillWindow::Create` | inline | `LONG` | 16 | non_class_hint | `(*(void ( **)(LONG, int, int *, CCBSkillWindow *))(*(_DWORD *)p_m_rect->left + 16))( p_m_rect->left, 529, pRect, this)` |
| `CCBStage::GetReadyCount` | inline | `_DWORD` | 24 | non_class_hint | `(*(void ( **)(_DWORD))(*(_DWORD *)*p_m_nActiveRoleIndex + 24))(*p_m_nActiveRoleIndex)` |
| `CCBStage::EditorUpdate` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)(LODWORD(v3->m_DefaultUVSet[3].eu) + 16) + 16))( LODWORD(v3->m_DefaultUVSet[3].eu) + 16, 0)` |
| `CCBStage::ProcShowFiveLineup` | inline | `_DWORD` | 1080 | self_arg_mismatch | `(***(void ( ****)(_DWORD, int))(*(_DWORD *)(HIDWORD(v10) + 4) + 1080))( *(_DWORD *)(*(_DWORD *)(HIDWORD(v10) + 4) + 1080), 1)` |
| `CCBStage::IsDoTask` | inline | `unsigned int` | 16 | non_class_hint | `(*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)inited[1].dwMagicID[1][3] + 16))( inited[1].dwMagicID[1][3], 0)` |
| `CCBStage::SetParam` | inline | `gbChain1DNode` | 24 | no_vtables_declaration | `(*(void ( **)(gbChain1DNode *, _DWORD))(*(_DWORD *)this->m_nTodo_124->children.m_Tail + 24))( this->m_nTodo_124->children.m_Tail, 0)` |
| `CCBStage::ProcessSlotAction` | inline | `gbChain1DNode` | 24 | no_vtables_declaration | `(*(void ( **)(gbChain1DNode *, _DWORD))(*(_DWORD *)this->m_nTodo_124->children.m_Tail + 24))( this->m_nTodo_124->children.m_Tail, 0)` |
| `CCBStage::OnPhysicalHit` | inline | `gbChain1DNode` | 24 | no_vtables_declaration | `(*(void ( **)(gbChain1DNode *, _DWORD))(*(_DWORD *)this->m_nTodo_124->children.m_Tail + 24))( this->m_nTodo_124->children.m_Tail, 0)` |
| `CCBStageCam::UpdateTransition` | inline | `int` | 56 | non_class_hint | `(*(int ( **)(int, int))(*(_DWORD *)v8 + 56))(v8, v5)` |
| `CCBStageScene::SetBattleFieldAttr` | inline | `gbGeomNode` | 20 | self_arg_mismatch | `(*(void ( **)(gbGeomNode *))(*(_DWORD *)&m_pPointer->gbChain1DNode + 20))(m_pPointer)` |
| `CCBStageScene::GetBattleFieldSubdueAttr` | inline | `gbGeomNode` | 16 | self_arg_mismatch | `(*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)&m_pGeomNode->gbChain1DNode + 16))(m_pGeomNode, 0)` |
| `CCBStageScene::GetBattleFieldSubdueAttr` | inline | `gbVisNode` | 16 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)&m_pLights->gbChain1DNode + 16))(m_pLights, 0)` |
| `CCBSystem::ProcFling` | inline | `CCBUI` | 12 | self_arg_mismatch | `(*(void ( **)(CCBUI *))(*(_DWORD *)&m_pUI->UIWnd + 12))(m_pUI)` |
| `CCBSystem::ProcFling` | inline | `CCBUI` | 20 | self_arg_mismatch | `(*(void ( **)(CCBUI *, int))(*(_DWORD *)&v11->UIWnd + 20))(v11, 1)` |
| `CCBUI::_nearby_4ea4a0` | inline | `int` | 40 | non_class_hint | `(*(int ( **)(int, int))(*(_DWORD *)v6 + 40))(v6, v4)` |
| `CCBUI::~CCBUI` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void (**)(UIStatic *, int, int *, CCBUI *))(*(_DWORD *)&v3->UIWnd + 16))(v3, 1, &v8, this)` |
| `CCBUI::~CCBUI` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void (**)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)&v7->UIWnd + 16))(v7, *v4, &v8, this)` |
| `CCBUI::Reset` | inline | `UIProgressBar` | 16 | self_arg_mismatch | `(*(void ( **)(UIProgressBar *, int, int *, CCBUI *))(*(_DWORD *)&v8->UIWnd + 16))(v8, 784, &v10, this)` |
| `CCBUI::CreateItemWindow` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)&v4->UIWnd + 16))(v4, 531, &v19, this)` |
| `CCBUI::CreateImbibeNimbus` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int, CCBUI *))(*(_DWORD *)&this->m_pAttackSequenBack->UIWnd + 16))( this->m_pAttackSequenBack, 256, nCount, this)` |
| `CCBUI::WriteNimbusToPlayerMgr` | inline | `NameSys` | 28 | self_arg_mismatch | `(*(void ( **)(NameSys *, int, int, CCBUI *, int, int, _DWORD))(*(_DWORD *)Sys->m_Flag + 28))( Sys, v7, v8, this, v9, 1, 0)` |
| `CCBUI::CreateButton` | inline | `unsigned int` | 16 | non_class_hint | `(*(void ( **)(unsigned int, int, int, UIWnd *))(*(_DWORD *)v9[1].m_fontcolor.Color + 16))( v9[1].m_fontcolor.Color, 131, parent, v9)` |
| `CCBUI::CreateButton` | inline | `UIListBox` | 28 | self_arg_mismatch | `(*(void ( **)(UIListBox *, int, int, UIWnd *, _DWORD, int, _DWORD))(*(_DWORD *)&(*p_m_id)->UIWnd + 28))( *p_m_id, *v12, parent, v9, 0, 1, 0)` |
| `CCBUI::LineMove` | inline | `LONG` | 28 | non_class_hint | `(*(int ( **)(LONG, POINT *, int, CCBUI *, int, _DWORD))(*(_DWORD *)v5 + 28))( v5, pEnd, v10, this, v11, 0)` |
| `CCBUI::AddTask` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, tagUITask *, CCBUI *))(*(_DWORD *)&this->m_pAttackSequenBack->UIWnd + 16))( this->m_pAttackSequenBack, 150, pTask, this)` |
| `CCBUI::AddTask` | inline | `UIListBox` | 28 | self_arg_mismatch | `(*(void ( **)(UIListBox *, int, tagUITask *, CCBUI *, _DWORD, int, _DWORD))(*(_DWORD *)&(*p_pPanel)->UIWnd + 28))( *p_pPanel, *v6, pTask, this, 0, 1, 0)` |
| `CCBUI::InitSkillUI` | vftable_local | `_BYTE` | 16 | non_class_hint | `(*(int ( **)(_BYTE *, char *, int *, CCBUI *))(v3 + 16))( &this[1].m_Task[15].bValid, &g_PlayerAttBuffer._todo_074[140], &v52, this)` |
| `CCBUI::InitSkillUI` | inline | `UIPushButton` | 28 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, const char *, _DWORD *, CCBUI *, char *, int))(*(_DWORD *)&v17->UIWnd + 28))( v17, *v16, v71, this, aSubgameApprais_3, v15)` |
| `CEffAction::UpdateFrame` | inline | `CTaskTpl_tagEffTaskParam_CEffAction` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffAction *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2->_tail_000 + 4))( v2, *(_DWORD *)(*(_DWORD *)v4 + v6), *(_DWORD *)(*(_DWORD *)v4 + v6 + ` |
| `CEffAudio::UpdateInternal` | inline | `CTaskTpl_tagEffTaskParam_CEffQuake` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffQuake *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2->_tail_000 + 4))( v2, *(_DWORD *)(*v4 + v6), *(_DWORD *)(*v4 + v6 + 4), 0)` |
| `CEffCustomShape::_nearby_4cfe20` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int, _DWORD))(*(_DWORD *)v7 + 24))(v7, 0)` |
| `CEffCustomShape::_nearby_4cffb0` | inline | `CTaskTpl_tagEffTaskParam_CEffCustomShape` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffCustomShape *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v3->_tail_000 + 4))( v3, *(_DWORD *)(*v5 + v7), *(_DWORD *)(*v5 + v7 + 4), 0)` |
| `CEffCustomShape::_nearby_4cffb0` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)v17 + 20))(v17)` |
| `CEffCylinder::CreateTask` | inline | `CTaskTpl_tagEffTaskParam_CEffCylinder` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffCylinder *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4->_tail_000 + 4))( v4, *(_DWORD *)(*(_DWORD *)v5 + v7), *(_DWORD *)(*(_DWORD *)v5 + v7 ` |
| `CEffGrid::slot_5` | inline | `CTaskTpl_tagEffTaskParam_CEffGrid` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffGrid *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4->_tail_000 + 4))( v4, *(_DWORD *)(*(_DWORD *)v11 + v13), *(_DWORD *)(*(_DWORD *)v11 + v13 ` |
| `CEffMeteor::CreateTask` | inline | `CTaskTpl_tagEffTaskParam_CEffMeteor` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffMeteor *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4->_tail_000 + 4))( v4, *(_DWORD *)(*(_DWORD *)v5 + v7), *(_DWORD *)(*(_DWORD *)v5 + v7 + ` |
| `CEffMgr::ReleaseAllRefs` | inline | `_DWORD` | 12 | non_class_hint | `(*(int ( **)(_DWORD))(*(_DWORD *)*v4 + 12))(*v4)` |
| `CEffMgr::SetEffectsTimeScale` | inline | `_DWORD` | 44 | non_class_hint | `(*(int ( **)(_DWORD, int))(*(_DWORD *)*v2 + 44))(*v2, nVal)` |
| `CEffMgr::ReleaseCompletedEffects` | inline | `_DWORD` | 12 | non_class_hint | `(*(void ( **)(_DWORD))(*(_DWORD *)*v3 + 12))(*v3)` |
| `CEffMgr::ReleaseCompletedEffects` | inline | `_DWORD` | 32 | non_class_hint | `(*(unsigned __int8 ( **)(_DWORD))(*(_DWORD *)*v3 + 32))(*v3)` |
| `CEffModel::RenderScenePass` | inline | `gbGeomNode` | 16 | self_arg_mismatch | `(*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)&m_pGeomNode->gbChain1DNode + 16))(m_pGeomNode, 0)` |
| `CEffQuad::sub_4D17D0` | inline | `CTaskTpl_tagEffTaskParam_CEffQuad` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffQuad *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4->_tail_000 + 4))( v4, *(_DWORD *)(*(_DWORD *)v19 + v20), *(_DWORD *)(*(_DWORD *)v19 + v20 ` |
| `CEffSParticle::Create` | inline | `CTaskTpl_tagEffTaskParam_CEffSParticle` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffSParticle *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2->_tail_000 + 4))( v2, *(_DWORD *)(*v4 + v6), *(_DWORD *)(*v4 + v6 + 4), 0)` |
| `CEffShock::sub_4D3DC0` | inline | `CTaskTpl_tagEffTaskParam_CEffShock` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffShock *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2->_tail_000 + 4))( v2, *(_DWORD *)(*v4 + v5), *(_DWORD *)(*v4 + v5 + 4), 0)` |
| `CEffectSystem::IsVisible` | inline | `gbGfxManager` | 84 | slot_out_of_range | `(*(int ( **)(gbGfxManager *, _DWORD *, int))(*(_DWORD *)gfxMgr->_tail_000 + 84))(gfxMgr, v6, 1)` |
| `CEffectSystem::IsVisible` | inline | `gbGfxManager` | 88 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `CEffectSystem::IsVisible` | inline | `_DWORD` | 152 | non_class_hint | `(*(int ( **)(_DWORD, _DWORD, float *))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 152))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, &this[2].m_DefaultUVSet[5].ev)` |
| `CEffectSystem::IsVisible` | inline | `float` | 12 | non_class_hint | `(*(int ( **)(float *, int, int, int))(*(_DWORD *)p_eu + 12))(p_eu, 256, 256, v7)` |
| `CEffectSystem::IsVisible` | inline | `gbGfxManager` | 92 | slot_out_of_range | `(*(int ( **)(gbGfxManager *, float *))(*(_DWORD *)gfxMgr->_tail_000 + 92))(gfxMgr, p_eu)` |
| `CEffectSystem::IsVisible` | inline | `_DWORD` | 172 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 172))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, 0, 3, -16777216, 10653` |
| `CEffectSystem::IsVisible` | inline | `_DWORD` | 148 | non_class_hint | `(*(int ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 148))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, LODWORD(this[2].m_DefaultUVSet[5].ev))` |
| `CEffectSystem::HandleViewMove` | inline | `gbGfxManager` | 92 | slot_out_of_range | `(*(void ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr->_tail_000 + 92))(gfxMgr, 96 * v4 + v2 + 60)` |
| `CEffectSystem::HandleViewMove` | inline | `_DWORD` | 172 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 172))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, 0, 3, -16777216, 10653` |
| `CEffectSystem::Update` | inline | `_DWORD` | 148 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 148))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, LODWORD(this[2].m_DefaultUVSet[5].ev))` |
| `CEffectSystem::Update` | inline | `_DWORD` | 172 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 172))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, 0, 3, -16777216, 10653` |
| `CEffgbParticle::ProcCommonTask` | inline | `CTaskTpl_tagEffTaskParam_CEffgbParticle` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffgbParticle *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4->_tail_000 + 4))( v4, *(_DWORD *)(*v7 + v9), *(_DWORD *)(*v7 + v9 + 4), 0)` |
| `CScreenMode::InitEquipScreen` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int *, CScreenMode *))(*(_DWORD *)&this->m_FrameB.UIWnd + 16))( &this->m_FrameB, 1025, &v23, this)` |
| `CScreenMode::InitEquipScreen` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, CScreenMode *))(*(_DWORD *)&p_m_StaticArray->UIWnd + 16))( p_m_StaticArray, 1025, &v23, this)` |
| `CScreenMode::InitSceneAudio` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v3 + 24))(v3, 1000, 0, 0)` |
| `CScreenMode::IsSceneReady` | inline | `int` | 84 | self_arg_mismatch | `(*(int ( **)(int *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 84))(v6, 0)` |
| `CScreenMode::IsSceneReady` | inline | `gbGfxManager` | 88 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `CScreenMode::IsSceneReady` | inline | `_DWORD` | 68 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 68))( LODWORD(v3[1].InvViewMatrix.xy), 0, 0, 0, 0)` |
| `CScreenMode::PlayVideo` | inline | `_DWORD` | 172 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 172))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, 0, 1, -16777216, 10653` |
| `CScreenMode::PlayVideo` | inline | `_DWORD` | 68 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 68))( LODWORD(v3[1].InvViewMatrix.xy), 0, 0, 0, 0)` |
| `CUtil::_CUtil_31f0` | inline | `char` | 20 | non_class_hint | `(*(void ( **)(char *, int))(*(_DWORD *)m_pBattleSystem + 20))(m_pBattleSystem, 1)` |
| `CUtil::_CUtil_31f0` | inline | `PropUI` | 20 | self_arg_mismatch | `(*(void ( **)(PropUI *, int))(*(_DWORD *)&m_pPropUI->UIWnd + 20))(m_pPropUI, 1)` |
| `CUtil::RenderFrame` | inline | `char` | 4 | non_class_hint | `(*(int ( **)(char *))(*(_DWORD *)this->m_pBattleSystem + 4))(this->m_pBattleSystem)` |
| `CUtil::RenderFrame` | inline | `PropUI` | 4 | self_arg_mismatch | `(*(int ( **)(PropUI *))(*(_DWORD *)&this->m_pPropUI->UIWnd + 4))(this->m_pPropUI)` |
| `CUtil::RenderFrameY` | inline | `char` | 8 | non_class_hint | `(*(void ( **)(char *, PalScript *, int))(*(_DWORD *)this->m_pBattleSystem + 8))( this->m_pBattleSystem, fTime, nVal)` |
| `CUtil::RenderFrameY` | inline | `PropUI` | 8 | self_arg_mismatch | `(*(void ( **)(PropUI *, PalScript *, int))(*(_DWORD *)&this->m_pPropUI->UIWnd + 8))( this->m_pPropUI, fTime, nVal)` |
| `CUtil::DispatchCommand` | inline | `char` | 24 | non_class_hint | `(*(int ( **)(char *, int, int, _DWORD))(*(_DWORD *)m_pBattleSystem + 24))( m_pBattleSystem, 1000, 1, 0)` |
| `EquipUI::HandleInput` | vftable_local | `EquipUI` | 24 | self_arg_mismatch | `(*(int ( **)(EquipUI *, int, _DWORD, _DWORD))(v5 + 24))( this, 1001, *(&dword_56E148 + PrevSlot), 0)` |
| `EquipUI::HandleInput` | inline | `EquipUI` | 24 | self_arg_mismatch | `(*(int ( **)(EquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1010, 0, 0)` |
| `EquipUI::Init` | inline | `st_Manager` | 16 | self_arg_mismatch | `(*(void ( **)(st_Manager *, int, int *, EquipUI *))(*(_DWORD *)&this->m_EquipData.m_Type + 16))( &this->m_EquipData, 161, &v39, this)` |
| `EquipUI::Init` | vftable_local | `_BYTE` | 16 | non_class_hint | `(*(void ( **)(_BYTE *, int, int *, EquipUI *))(v6 + 16))( &this->m_EquipData.m_Dicker + 151, 161, &v39, this)` |
| `EquipUI::Init` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, _DWORD *, EquipUI *))(*(_DWORD *)&p_m_childs->UIWnd + 16))( p_m_childs, 161, v43, this)` |
| `LineupComp::ShowById` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, _DWORD, _BYTE *, LineupComp *, char *, int))(*(_DWORD *)v11 + 28))( v11, *ida, v15, this, v9, v10)` |
| `LineupUI::OnMessage` | inline | `LineupUI` | 24 | self_arg_mismatch | `(*(void ( **)(LineupUI *, int, int, int))(*(_DWORD *)&this->UIWnd + 24))( this, 1007, 773, this->m_TimeMoney.m_bfocus)` |
| `LineupUI::OnMessage` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_bvisible + 24))( this->m_CtrlPlank[11].m_Dw.m_bvisible, 0)` |
| `LineupUI::CreatePreviewScene` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int *, int *, LineupUI *))(*(_DWORD *)&this->m_Frame.UIWnd + 16))( &this->m_Frame, &byte_1234567, &v59, this)` |
| `LineupUI::CreatePreviewScene` | vftable_local | `char` | 16 | non_class_hint | `(*(int ( **)(char *, int *, char *, LineupUI *))(v12 + 16))( &this->m_CtrlPlank[11].m_Btn[172], &byte_A00001, &this->m_CtrlPlank[11].m_Btn[156], this)` |
| `LineupUI::CreatePreviewScene` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int *, StateUI **, LineupUI *))(*(_DWORD *)&v21->UIWnd + 16))( v21, &byte_A00001, v20, this)` |
| `LineupUI::RebuildNavPage` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[44] + 28))( &byte_A00105, &this->stp_Effect.m_childs.m_nSize, this, aUiGamemainuiCo` |
| `LineupUI::RebuildNavPage` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, _DWORD *, LineupUI *))(v19 + 16))(&this->stp_Exit.m_caption[44], 161, v46, this)` |
| `LineupUI::RebuildNavPage` | inline | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_BattleArray.m_caption[44] + 28))( &this->stp_BattleArray.m_caption[44], &byte_A00108, &this` |
| `LineupUI::RebuildNavPage` | vftable_local | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v33 + 28))( &this->stp_System.m_caption[44], &byte_A00110, &this->stp_Effect.m_childs.m_nSize, this, aUiGamemainu` |
| `LineupUI::RebuildExitPage` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, int *, LineupUI *, char *, int, gbTexture *))(*(_DWORD *)&this->stp_Magic.m_caption[60] + 28))( &byte_A00105, &this->stp_Effect.m_benable, this, aUiGamemainuiC` |
| `LineupUI::RebuildExitPage` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, _DWORD *, LineupUI *))(v13 + 16))(&this->stp_Exit.m_caption[60], 161, v47, this)` |
| `LineupUI::RebuildExitPage` | inline | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[60] + 28))( &this->stp_State.m_caption[60], &byte_A00104, &this->stp_Effect` |
| `LineupUI::RebuildExitPage` | vftable_local | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v34 + 28))( &this->stp_System.m_caption[60], &byte_A00110, &this->stp_Effect.m_benable, this, aUiGamemainuiCo_13,` |
| `LineupUI::RebuildCaptionPage` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, _DWORD *, LineupUI *))(v2 + 16))(&this->m_OutFrameL.m_text[12], 161, v43, this)` |
| `LineupUI::RebuildCaptionPage` | inline | `UIStatic` | 28 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int *, UIStatic *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_BarR.UIWnd + 28))( &this->stp_BarR, &byte_A00102, &this->m_GameMoney, this, aUiGam` |
| `LineupUI::RebuildCaptionPage` | inline | `_BYTE` | 28 | non_class_hint | `(*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_mouseoff + 28))( &this->stp_Equip.m_mouseoff, &byte_A00105, &this->m_GameMone` |
| `LineupUI::RebuildCaptionPage` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, UIStatic *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_Magic.m_mouseoff + 28))( &byte_A00104, &this->m_GameMoney, this, aUiGamemainuiCo_27, ` |
| `LineupUI::RebuildCaptionPage` | vftable_local | `_BYTE` | 28 | non_class_hint | `(*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, unsigned int))(v33 + 28))( &this->stp_Exit.m_mouseoff, &byte_A00110, &this->m_GameMoney, this, aUiGamemainuiCo_13` |
| `LineupUI::RebuildFontPage` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, _DWORD *, LineupUI *))(v8 + 16))(&this->stp_Exit.m_caption[52], 161, v42, this)` |
| `LineupUI::RebuildFontPage` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[52] + 28))( &byte_A00105, &this->stp_Effect.m_bcreateok, this, aUiGamemainuiCo_28, ` |
| `LineupUI::RebuildFontPage` | inline | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_BattleArray.m_caption[52] + 28))( &this->stp_BattleArray.m_caption[52], &byte_A00108, &this` |
| `LineupUI::RebuildFontPage` | vftable_local | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int *, int *, LineupUI *, char *, int, Parent_Data *))(v29 + 28))( &this->stp_System.m_caption[52], &byte_A00110, &this->stp_Effect.m_bcreateok, this, aUiGame` |
| `LineupUI::RebuildMainPage` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[44] + 28))( &byte_A00105, &this->stp_Effect.m_childs.m_nSize, this, aUiGamemainuiCo` |
| `LineupUI::RebuildMainPage` | inline | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int *, int *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_BattleArray.m_caption[44] + 28))( &this->stp_BattleArray.m_caption[44], &byte_A001` |
| `LineupUI::RebuildMainPage` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, _DWORD *, LineupUI *))(v30 + 16))(&this->stp_Exit.m_caption[44], 161, v43, this)` |
| `LineupUI::RebuildMainPage` | vftable_local | `char` | 28 | non_class_hint | `(*(int ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v38 + 28))( &this->stp_System.m_caption[44], &byte_A00110, &this->stp_Effect.m_childs.m_nSize, this, aUiGamemainui` |
| `MainEquipUI::InitMainEquipUI` | inline | `UIScene` | 16 | self_arg_mismatch | `(*(void ( **)(UIScene *, int, _DWORD *, MainEquipUI *))(*(_DWORD *)&v29->UIWnd + 16))(v29, 4371, a2, this)` |
| `MainEquipUI::InitMainEquipUI` | vftable_local | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int, int *, MainEquipUI *, _DWORD, int, int))(v32 + 28))( &this->me_Role[2].m_EquipAdorn1.m_caption[20], 4359, &p_DWORD, this, 0, 1, v30)` |
| `MainEquipUI::ShowWithCursor` | inline | `MainEquipUI` | 24 | self_arg_mismatch | `(*(void ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1007, 0, 0)` |
| `MainEquipUI::CreateFromData` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int *, int *, MainEquipUI *))(v11 + 16))( &this->me_Role[4].m_EquipHat.m_caption[16], &byte_ABAB09, &v54, this)` |
| `MainEquipUI::CreateFromData` | inline | `char` | 28 | non_class_hint | `(*(int ( **)(char *, int *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)&this->m_ClothName.m_text[12] + 28))( &this->m_ClothName.m_text[12], &byte_A00417, &p_DWORD, this, 0` |
| `MainEquipUI::CreateFromData` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, MainEquipUI *))(*(_DWORD *)&v25->UIWnd + 16))( v25, 161, &v50, this)` |
| `MainEquipUI::CreateFromData` | vftable_local | `_BYTE` | 28 | non_class_hint | `(*(int ( **)(_BYTE *, int *, _DWORD *, MainEquipUI *, char *, int, int))(v33 + 28))( &this->m_Ctrlbtn[0].m_bBigFont, &byte_A00429, v43, this, aUiGamemainuiCo_46, 1, v34)` |
| `MainEquipUI::CreateListPanel` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, int *, MainEquipUI *))(v7 + 16))(&this->m_TopFrame.m_text[12], 161, &v37, this)` |
| `MainEquipUI::CreateListPanel` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, _DWORD, int *, MainEquipUI *))(*(_DWORD *)&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i] + 16))( &this->me_Role[2].m_AttFramePose.m_text[4892 * this-` |
| `MainEquipUI::HandleMessage` | inline | `MainEquipUI` | 24 | self_arg_mismatch | `(*(int ( **)(MainEquipUI *, int, int, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1000, 1, 0)` |
| `MainEquipUI::HandleMessage` | inline | `unsigned int` | 24 | non_class_hint | `(*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)m_id + 24))(m_id, 1000, 0, 0)` |
| `MainEquipUI::HandleMessage` | inline | `LONG` | 24 | non_class_hint | `(*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)left + 24))(left, 1000, 0, 0)` |
| `MainEquipUI::HandleMessage` | inline | `int` | 24 | self_arg_mismatch | `(*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)bottom + 24))(1000, 0, 0)` |
| `MainPropUI::HandleKeyInput` | vftable_local | `MainPropUI` | 24 | self_arg_mismatch | `(*(int ( **)(MainPropUI *, int, _DWORD, _DWORD))(v4 + 24))( this, 1001, *(&dword_56D5F0 + NextValid), 0)` |
| `MainPropUI::HandleKeyInput` | inline | `MainPropUI` | 24 | self_arg_mismatch | `(*(void ( **)(MainPropUI *, int, int *, _DWORD))(*(_DWORD *)&this->UIWnd + 24))( this, 1001, &byte_A00323, 0)` |
| `MatrixStack::BeginScene` | inline | `MatrixStack` | 16 | no_vtables_declaration | `(*(void ( **)(MatrixStack *, _DWORD))(*(_DWORD *)v4 + 16))(v4, 0)` |
| `MatrixStack::BeginScene` | inline | `MatrixStack` | 16 | self_arg_mismatch | `(*(void ( **)(MatrixStack *, _DWORD))(*(_DWORD *)&this[834] + 16))(this + 834, 0)` |
| `MiniGame3::Render` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)v6 + 16))(v6, 0)` |
| `Object3D::CaculateRelative` | inline | `gbGeomNode` | 20 | self_arg_mismatch | `(*(void ( **)(gbGeomNode *))(*(_DWORD *)&this->m_pol->gbChain1DNode + 20))(this->m_pol)` |
| `Object3D::CaculateRelative` | inline | `gbGeomNode` | 24 | self_arg_mismatch | `(*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)&this->m_subObj->gbChain1DNode + 24))( this->m_subObj, 0)` |
| `PAL3::ClearAdditiveEffects` | inline | `gbRenderEffect` | 8 | self_arg_mismatch | `(*(void ( **)(gbRenderEffect *))(*(_DWORD *)&m_pAdditiveEffect->gbRefObject + 8))(m_pAdditiveEffect)` |
| `PAL3::ClearAdditiveEffects` | inline | `gbTexture` | 8 | self_arg_mismatch | `(*(void ( **)(gbTexture *))(*(_DWORD *)&m_pScnFrameTex->gbRefObject + 8))(this->m_pScnFrameTex)` |
| `PAL_GDB::InitSkillDisplay` | vftable_local | `char` | 16 | non_class_hint | `(*(int ( **)(char *, ARC_PlayerAtt *, int *, PAL_GDB *))(v3 + 16))( (char *)&this->m_RoleData[1].Remark.skillCount + 286, &g_PlayerAttBuffer, &v35, this)` |
| `PAL_GDB::InitSkillDisplay` | vftable_local | `char` | 28 | non_class_hint | `(*(void ( **)(char *, char *, int *, PAL_GDB *, char *, _DWORD, int))(v26 + 28))( (char *)&this->m_RoleData[0].Remark.skillCount + 186, (char *)&g_PlayerAttBuffer.id + 1, &v43, thi` |
| `PropUI::InitListUI` | inline | `PropUI` | 24 | self_arg_mismatch | `(*(void ( **)(PropUI *, int, _DWORD, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1007, 0, 0)` |
| `RenderTarget::RenderToTexture` | inline | `gbGfxManager` | 60 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 60))(gfxMgr)` |
| `RenderTarget::RenderToTexture` | inline | `float` | 368 | self_arg_mismatch | `(*(void ( **)(float, _DWORD))(*(_DWORD *)LODWORD(xy) + 368))(_pal3_coerce_f32(LODWORD(xy)), 0)` |
| `RenderTarget::RenderToTexture` | inline | `float` | 356 | self_arg_mismatch | `(*(void ( **)(float, int))(*(_DWORD *)LODWORD(xy) + 356))(_pal3_coerce_f32(LODWORD(xy)), 322)` |
| `RenderTarget::RenderToTexture` | inline | `float` | 228 | self_arg_mismatch | `(*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(_pal3_coerce_f32(LODWORD(xy)), 7, 1)` |
| `RenderTarget::RenderToTexture` | inline | `float` | 268 | self_arg_mismatch | `(*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 268))(_pal3_coerce_f32(LODWORD(xy)), 0, 1, 4)` |
| `RenderTarget::RenderToTexture` | inline | `float` | 276 | self_arg_mismatch | `(*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 276))(_pal3_coerce_f32(LODWORD(xy)), 0, 6, 2)` |
| `RenderTarget::RenderToTexture` | vftable_local | `float` | 260 | self_arg_mismatch | `(*(void ( **)(float, _DWORD, int))(v8 + 260))(_pal3_coerce_f32(LODWORD(xy)), 0, v33)` |
| `RenderTarget::RenderToTexture` | inline | `float` | 332 | self_arg_mismatch | `(*(void ( **)(float, int, int, float *, int))(*(_DWORD *)LODWORD(xy) + 332))( _pal3_coerce_f32(LODWORD(xy)), 6, 2, v90, 24)` |
| `RenderTarget::UpdateParticleEffect` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)this->m_nDefaultH + 20))(this->m_nDefaultH)` |
| `RenderTarget::Stop` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_nDefaultH + 16))(this->m_nDefaultH, 0)` |
| `RenderTarget::Create` | inline | `gbGfxManager` | 84 | slot_out_of_range | `(*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)gfxMgr->_tail_000 + 84))(gfxMgr, &v2, 1)` |
| `RenderTarget::Create` | inline | `gbGfxManager` | 88 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `RenderTarget::OnResetDevice` | inline | `gbGfxManager` | 92 | slot_out_of_range | `(*(int ( **)(gbGfxManager *, gbTexture_D3D **))(*(_DWORD *)gfxMgr->_tail_000 + 92))( gfxMgr, &this->m_ScreenPlane)` |
| `RenderTarget::OnResetDevice` | inline | `_DWORD` | 172 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 172))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, 0, 3, -16777216, 10653` |
| `RenderTarget::OnResetDevice` | inline | `gbGfxManager` | 48 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 48))(gfxMgr)` |
| `RenderTarget::OnResetDevice` | inline | `gbGfxManager` | 52 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 52))(gfxMgr)` |
| `RenderTarget::RenderToScreen` | inline | `gbGfxManager` | 92 | slot_out_of_range | `(*(void ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 92))(gfxMgr, 0)` |
| `RenderTarget::RenderToScreen` | inline | `int` | 72 | non_class_hint | `(*(int ( **)(int, _DWORD, int *))(*(_DWORD *)result + 72))(result, 0, &v5)` |
| `RenderTarget::RenderToScreen` | inline | `int` | 48 | non_class_hint | `(*(void ( **)(int, _BYTE *))(*(_DWORD *)v5 + 48))(v5, v8)` |
| `RenderTarget::RenderToScreen` | inline | `_DWORD` | 136 | non_class_hint | `(*(int ( **)(_DWORD, int, _DWORD *, int, _DWORD *, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 136))( LODWORD(v3[1].InvViewMatrix.xy), v5, v7, v4, v6, 0)` |
| `RenderTarget2::Init` | inline | `float` | 28 | self_arg_mismatch | `(*(void ( **)(float, _DWORD *))(*(_DWORD *)LODWORD(xy) + 28))(_pal3_coerce_f32(LODWORD(xy)), v52)` |
| `RenderTarget2::Init` | inline | `_DWORD` | 92 | non_class_hint | `(*(int ( **)(_DWORD, int, int, int, _DWORD, int, int, int *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy) + 92))( LODWORD(v2[1].InvViewMatrix.xy), 256, 256, 1, 0, 60, 1, &v1` |
| `RenderTarget2::Init` | inline | `int` | 76 | non_class_hint | `(*(void ( **)(int, _DWORD, _DWORD *, _DWORD, _DWORD))(*(_DWORD *)v1->m_SubObj + 76))( v1->m_SubObj, 0, v50, 0, 0)` |
| `RenderTarget2::Init` | inline | `int` | 80 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)v48->m_SubObj + 80))(v48->m_SubObj, 0)` |
| `RenderTarget2::Init` | inline | `float` | 268 | self_arg_mismatch | `(*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(v13) + 268))( _pal3_coerce_f32(LODWORD(v13)), 0, 7, 1008981770)` |
| `RenderTarget2::Init` | inline | `_DWORD` | 104 | non_class_hint | `(*(int ( **)(_DWORD, int, int, int, int, _BYTE *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy) + 104))( LODWORD(v2[1].InvViewMatrix.xy), 2800, 8, 514, 1, &v1->m_bActive, 0)` |
| `RenderTarget2::Init` | vftable_local | `float` | 108 | self_arg_mismatch | `(*(int ( **)(float, int, int, int, _DWORD, char **, _DWORD))(v29 + 108))( _pal3_coerce_f32(LODWORD(v27)), 1200, 512, 101, 0, p_m_pSurface, 0)` |
| `RenderTarget2::Init` | inline | `int` | 44 | non_class_hint | `(*(int ( **)(int, _DWORD, _DWORD, _BYTE **, _DWORD))(*(_DWORD *)v30 + 44))(v30, 0, 0, &v45, 0)` |
| `RenderTarget2::Init` | inline | `_DWORD` | 48 | non_class_hint | `(*(void ( **)(_DWORD))(*(_DWORD *)*p_m_bActive + 48))(*p_m_bActive)` |
| `RenderTarget2::Init` | inline | `char` | 44 | non_class_hint | `(*(int ( **)(char *, _DWORD, _DWORD, unsigned int *, int))(*(_DWORD *)v36 + 44))( v36, 0, 0, &i, 0x2000)` |
| `RenderTarget2::Begin` | inline | `_DWORD` | 172 | non_class_hint | `(*(int ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 172))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 0, 0, 3, -16777216, 106535` |
| `RenderTarget2::Resolve` | vftable_local | `gbGfxManager` | 60 | slot_out_of_range | `(*(void ( **)(gbGfxManager *))(v4 + 60))(v3)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 228 | non_class_hint | `(*(void ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))( LODWORD(v3[1].InvViewMatrix.xy), 22, 1)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 260 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 260))( LODWORD(v3[1].InvViewMatrix.xy), 0, *(_DWORD *)&v8[1].gbRefObject)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 268 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))( LODWORD(v3[1].InvViewMatrix.xy), 0, 11, 0)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 276 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 276))( LODWORD(v3[1].InvViewMatrix.xy), 0, 1, 3)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 356 | non_class_hint | `(*(void ( **)(_DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 356))( LODWORD(v3[1].InvViewMatrix.xy), 514)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 400 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 400))( LODWORD(v3[1].InvViewMatrix.xy), 0, *(_DWORD *)&this->m_bActive, 0, 28)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 416 | non_class_hint | `(*(void ( **)(_DWORD, char *))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 416))( LODWORD(v3[1].InvViewMatrix.xy), this->m_pSurface)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 328 | non_class_hint | `(*(void ( **)(_DWORD, int, _DWORD, _DWORD, int, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 328))( LODWORD(v3[1].InvViewMatrix.xy), 4, 0, 0, 100, 0, 200)` |
| `RenderTarget2::Resolve` | inline | `_DWORD` | 324 | non_class_hint | `(*(void ( **)(_DWORD, int, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 324))( LODWORD(v3[1].InvViewMatrix.xy), 5, 0, 2)` |
| `RenderTarget2::Update` | inline | `int` | 44 | non_class_hint | `(*(int ( **)(int, _DWORD, _DWORD, float *, _DWORD))(*(_DWORD *)v3 + 44))(v3, 0, 0, &fVal, 0)` |
| `RenderTarget2::CameraInterpCallback` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)m_szPrefix + 24))(m_szPrefix, 0)` |
| `RenderTarget3::Begin` | inline | `int` | 4 | non_class_hint | `(*(void ( **)(int, gbRenderEffect *))(*(_DWORD *)v5 + 4))(v5, this->m_ptr_4)` |
| `RenderTarget3::ResetAndRender` | inline | `_DWORD` | 172 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD, int, int))(*(_DWORD *)LODWORD(v10[1].InvViewMatrix.xy) + 172))( LODWORD(v10[1].InvViewMatrix.xy), 0, 0, v11, -16777216,` |
| `RenderTarget3::End` | inline | `_DWORD` | 228 | non_class_hint | `(*(int ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 228))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 168, 3)` |
| `RenderTarget3::Resolve` | inline | `_DWORD` | 228 | non_class_hint | `(*(void ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 228))( LODWORD(gfxMgr[1].InvViewMatrix.xy), 168, 7)` |
| `RoleStatePanel::RenderThrottled` | inline | `void` | 4 | non_class_hint | `(*(int ( **)(void *))(*(_DWORD *)this->m_pSubTab2 + 4))(this->m_pSubTab2)` |
| `RoleStatePanel::RenderThrottled` | inline | `LONG` | 4 | non_class_hint | `(*(int ( **)(LONG))(*(_DWORD *)this->m_roles[5].m_QiVal.m_rect.bottom + 4))(this->m_roles[5].m_QiVal.m_rect.bottom)` |
| `RoleStatePanel::UpdateCaptions` | inline | `void` | 8 | non_class_hint | `(*(void ( **)(void *, int, int))(*(_DWORD *)this->m_pSubTab2 + 8))(this->m_pSubTab2, nVal, a3)` |
| `RoleStatePanel::UpdateCaptions` | inline | `LONG` | 8 | non_class_hint | `(*(void ( **)(LONG, int, int))(*(_DWORD *)this->m_roles[5].m_QiVal.m_rect.bottom + 8))( this->m_roles[5].m_QiVal.m_rect.bottom, nVal, a3)` |
| `SceneMgr::RenderAll` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)*v1 + 24))(*v1)` |
| `SceneMgr::RenderUpdate` | inline | `int` | 16 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)*v1 + 16))(*v1)` |
| `ScreenEffectMgr::ProcessEffect` | inline | `void` | 12 | non_class_hint | `(*(void ( **)(void *))(*(_DWORD *)p_m_fadeOut + 12))(p_m_fadeOut)` |
| `ScreenEffectMgr::UpdateFrontEffect` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)v2 + 16))(v2)` |
| `ScreenEffectMgr::IsFadeActive` | inline | `float` | 4 | self_arg_mismatch | `(*(int ( **)(float))(*(_DWORD *)LODWORD(m_age) + 4))(_pal3_coerce_f32(LODWORD(m_age)))` |
| `StateUI::sub_485230` | inline | `gbVisNode` | 24 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)&(*v47)->gbChain1DNode + 24))(*v47, 0)` |
| `UI3DCtrl::LoadModel` | inline | `int` | 40 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)v3 + 40))(v3, 3)` |
| `UICoverFrm::ProcessInput` | inline | `int` | 8 | non_class_hint | `(*(void ( **)(int, int, int))(*(_DWORD *)this[1].m_column[0].width + 8))( this[1].m_column[0].width, nVal, nVal2)` |
| `UIEmote::Render` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, gbImage2D **, UIEmote *))(*(_DWORD *)&v3->UIWnd + 16))( v3, *v17, &this->m_needscriptdel, this)` |
| `UIListBox::ctor_79F0` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)width + 20))(width, 1)` |
| `UIListBox::RenderWithSceneMap` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)this[1].m_column[0].width + 4))(this[1].m_column[0].width)` |
| `UINote::RenderWithStack` | inline | `_DWORD` | 16 | non_class_hint | `(*(void ( **)(_DWORD, _DWORD))(*(_DWORD *)LODWORD(this->time) + 16))(LODWORD(this->time), 0)` |
| `UINote::CallVtableMethod` | inline | `_DWORD` | 48 | self_arg_mismatch | `(*(int ( **)(_DWORD))(*(_DWORD *)LODWORD(this->time) + 48))(LODWORD(v3))` |
| `UIRenderObj::~UIRenderObj` | inline | `gbGfxManager` | 104 | slot_out_of_range | `(*(void (**)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 104))( gfxMgr, (unsigned __int8)nVal1)` |
| `UIRoleDialog::RemoveChild` | inline | `UITextArea` | 4 | self_arg_mismatch | `(*(void ( **)(UITextArea *))(*(_DWORD *)&this->m_static.UIWnd + 4))(&this->m_static)` |
| `UIRoleDialog::ProcessFrame` | inline | `UIRoleDialog` | 24 | self_arg_mismatch | `(*(void ( **)(UIRoleDialog *, int, int, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1001, 655362, 0)` |
| `UIRoleDialog::Create` | inline | `UIRoleDialog` | 12 | self_arg_mismatch | `(*(void ( **)(UIRoleDialog *, _DWORD))(*(_DWORD *)&this->UIWnd + 12))(this, 0)` |
| `UIRoleSelectDialog::Render` | inline | `float` | 4 | non_class_hint | `(*(void ( **)(float *))(*(_DWORD *)p_m_ratioh + 4))(p_m_ratioh)` |
| `UITitle_ArcSave::Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)m_needscriptdel + 20))(m_needscriptdel, 3)` |
| `UITitle_ArcSave::Render` | inline | `int` | 4 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)this->m_YesNo.m_childs.m_needscriptdel + 4))(this->m_YesNo.m_childs.m_needscriptdel)` |
| `UITitle_ArcSave::ProcessPageAction` | inline | `int` | 8 | non_class_hint | `(*(void ( **)(int, struct PalScript *, int))(*(_DWORD *)this->m_YesNo.m_childs.m_needscriptdel + 8))( this->m_YesNo.m_childs.m_needscriptdel, p, nVal)` |
| `::LineupUI_InitListView` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, _DWORD *, int))(v5 + 16))(v2 + 100908, 769, v119, v2)` |
| `::LineupUI_InitListView` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int, _DWORD *, char *, _DWORD, int))(v7 + 28))( v2 + 100824, 769, v114, aUiFlexFramebar, 0, v2)` |
| `::LineupUI_InitListView` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, _DWORD *, int))(*(_DWORD *)&v11->UIWnd + 16))(v11, v15, v101, v2)` |
| `::LineupUI_InitListView` | inline | `int` | 16 | non_class_hint | `(*(int ( **)(int, _DWORD, _DWORD *, int))(*(_DWORD *)v10 + 16))( v10, *(int *)((char *)&dword_56B6F0 + v3), v101, v2)` |
| `::LineupUI_InitListView` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, int, int, int, _DWORD, int, int))(*(_DWORD *)(v2 + 115056) + 28))( v2 + 115056, 774, v2 + 113828, v2, 0, 1, v29)` |
| `::LineupUI_InitListView` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int, int, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 121500) + 28))( 822, v2 + 121140, v2, v43, 0, v81)` |
| `::LineupUI_Render3DModels` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1007, 0, 0)` |
| `::LineupUI_ProcessMouseInput` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1001, 822, 0)` |
| `::PAL3_DispatchModeCommand` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v1 + 24))(v1, 1000, 1, 0)` |
| `::MainEquipUI_CreateUI` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 157908) + 28))( v2 + 157908, &byte_A00604, v80, v2, aUiGamemainuiJu_0, 0, v4)` |
| `::MainEquipUI_CreateUI` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, int, char *, _DWORD, int))(v5 + 28))( v2 + 158252, &byte_A00605, v80, v2, aUiGamemainuiJu_2, 0, v6)` |
| `::MainEquipUI_CreateUI` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int *, int *, int))(v51 + 16))(v2 + 154956, &byte_A00602, &v76, v2)` |
| `::MainEquipUI_CreateUI` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int *, int *, int))(*(_DWORD *)(v2 + 155108) + 16))(v2 + 155108, &byte_A00602, &v76, v2)` |
| `::MainEquipUI_CreateUI` | inline | `UIScene` | 16 | self_arg_mismatch | `(*(void ( **)(UIScene *, int *, int *, int))(*(_DWORD *)&v55->UIWnd + 16))(v55, &byte_A00602, &v76, v2)` |
| `::MainPropUI_CreateCoverTemplate` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, _DWORD *))(v3 + 16))(v1 + 51492, 161, v45)` |
| `::MainPropUI_CreateCoverTemplate` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, _DWORD *, int))(*(_DWORD *)(v2 + 51796) + 16))(v2 + 51796, 161, v45, v2)` |
| `::MainPropUI_CreateCoverTemplate` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 51948) + 28))( v2 + 51948, &byte_A00102, v2 + 55196, v2, aUiGamemainuiCo_25, 1, v9)` |
| `::MainPropUI_CreateCoverTemplate` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 52980) + 28))( &byte_A00105, v2 + 55196, v2, aUiGamemainuiCo_28, 1, v10)` |
| `::MainPropUI_CreateCoverTemplate` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, int, int, char *, int, int))(v35 + 28))( v2 + 54700, &byte_A00110, v2 + 55196, v2, aUiGamemainuiCo_13, 1, v34)` |
| `::CameraCtrl_CreateCameraUI` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, int *, int))(*(_DWORD *)(v2 + 51036) + 16))(v2 + 51036, 161, &v85, v2)` |
| `::CameraCtrl_CreateCameraUI` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, int *, int))(v6 + 16))(v2 + 51188, 161, &v85, v2)` |
| `::CameraCtrl_CreateCameraUI` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, char *, _DWORD, int))(v14 + 28))( v2 + 210236, &byte_A00001, v98, aUiFlexBarTga, 0, v2)` |
| `::CameraCtrl_CreateCameraUI` | inline | `UIScene` | 16 | self_arg_mismatch | `(*(void ( **)(UIScene *, int *, int, int))(*(_DWORD *)&v17->UIWnd + 16))( v17, &byte_A00001, v2 + 55212, v2)` |
| `::CameraCtrl_CreateCameraUI` | inline | `int` | 28 | non_class_hint | `(*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 241020) + 28))( v2 + 241020, &byte_A00218, &v81, v2, 0, 0, v21)` |
| `::CameraCtrl_CreateCameraUI` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int *, int *, int))(*(_DWORD *)&v35->UIWnd + 16))( v35, &byte_A00001, &v94, v2)` |
| `::CameraCtrl_ProcessSaveSlotNav` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int, int, const char *, _DWORD))(*(_DWORD *)v1 + 24))( v1, 1001, (&off_56C548)[*(_DWORD *)(v1 + 900)], 0)` |
| `::Create__ovl_1` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, char *, ARC_PlayerAtt *))(*(_DWORD *)_this->_todo_130 + 16))( _this->_todo_130, 655360, _this->_todo_050, _this)` |
| `::Create__ovl_1` | vftable_local | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int, char *, ARC_PlayerAtt *, char *, _DWORD, int))(v25 + 28))( &_this->_todo_224[84], 655362, &_this->_todo_224[68], _this, v31, 0, v41)` |
| `::Create__ovl_1` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, char *, ARC_PlayerAtt *))(v10 + 16))( _this->_todo_130, 655360, _this->_todo_050, _this)` |
| `::UIGameFrm_Destroy` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int, int))(*(_DWORD *)v4 + 20))(v4, 1)` |
| `::SystemUI_LayoutWidgets` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, _DWORD *))(v3 + 16))(v1 + 23760, 161, v44)` |
| `::SystemUI_LayoutWidgets` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, _DWORD *, int))(*(_DWORD *)(v2 + 24064) + 16))(v2 + 24064, 161, v44, v2)` |
| `::SystemUI_LayoutWidgets` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 24216) + 28))( v2 + 24216, &byte_A00102, v2 + 27464, v2, aUiGamemainuiCo_25, 1, v9)` |
| `::SystemUI_LayoutWidgets` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 25248) + 28))( &byte_A00105, v2 + 27464, v2, aUiGamemainuiCo_28, 1, v10)` |
| `::SystemUI_LayoutWidgets` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, int, int, char *, int, int))(v34 + 28))( v2 + 26968, &byte_A00110, v2 + 27464, v2, aUiGamemainuiCo_13, 1, v33)` |
| `::Create__ovl_1_0` | inline | `_BYTE` | 28 | non_class_hint | `(*(int ( **)(_BYTE *, int *, int *, CCCTData *, _DWORD, int, int))(*(_DWORD *)&_this->m_Pool[1929].bLineMove + 28))( &_this->m_Pool[1929].bLineMove, &byte_A00532, &p_DWORD, _this, ` |
| `::Create__ovl_1_0` | inline | `float` | 16 | non_class_hint | `(*(void ( **)(float *, __int16 *, int *, CCCTData *))(*(_DWORD *)p_fSwingFre + 16))( p_fSwingFre, &word_A00552, &v78, _this)` |
| `::Create__ovl_1_0` | vftable_local | `_BYTE` | 28 | non_class_hint | `(*(void ( **)(_BYTE *, int *, _DWORD *, CCCTData *, char *, _DWORD, int))(v25 + 28))( &_this->m_Pool[1881].bStartCamValid, &byte_A00560, v68, _this, aUiGamemainuiEq_1, 0, v26)` |
| `::EquipUI_InitEquipUI` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, _DWORD *, int))(*(_DWORD *)(v2 + 23456) + 16))(v2 + 23456, 161, v110, v2)` |
| `::EquipUI_InitEquipUI` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, int *, int))(v6 + 16))(v2 + 23608, 161, &v97, v2)` |
| `::EquipUI_InitEquipUI` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v23 + 28))( v2 + 179108, &byte_A00571, v119, v2, aUiGamemainuiSw_1, 1, v22)` |
| `::EquipUI_InitEquipUI` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, unsigned __int8 *, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 182332) + 28))( v2 + 182332, &byte_A00543, a8, v2, aUiGamemainuiSw_27, 0, v32)` |
| `::UITitle_JDHY_PopulateContent` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, int *, int))(v6 + 16))(v2 + 368, 161, &v117, v2)` |
| `::UITitle_JDHY_PopulateContent` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, int *, int, char *, int))(v17 + 28))( v2 + 154796, &byte_A00704, &v113, v2, aUiGamemainuiSy_6, v16)` |
| `::UITitle_JDHY_PopulateContent` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int *, int *, int, char *, int, int))(*(_DWORD *)(v2 + 284520) + 28))( &byte_A00702, &v121, v2, aUiGamemainuiSy_1, 1, v23)` |
| `::UITitle_JDHY_HandleNavigation` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int, int, int *, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1001, &byte_A00704, 0)` |
| `::Object3D_RenderTransformed` | inline | `int` | 12 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)v2 + 12))(v2, 0)` |
| `::CombatEffectUpdate` | inline | `_DWORD` | 20 | non_class_hint | `(*(void ( **)(_DWORD, int, int))(*(_DWORD *)*v7 + 20))(*v7, v2[78], v2[79])` |
| `::SceneMgrUpdate` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int, _DWORD))(*(_DWORD *)*v4 + 20))(*v4, LODWORD(fVal))` |
| `::CCBUI_InitResultPanels` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, int))(*(_DWORD *)&v5->UIWnd + 16))(v5, 800, &v8, v2)` |
| `::CCBUI_SetupAIWindow` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, int *, int, int))(*(_DWORD *)v6 + 16))(v6, g_nItemTypeBase[v3], &v47, v2, v46)` |
| `::CCBUI_SetupAIWindow` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int, int *, int))(*(_DWORD *)&v11->UIWnd + 16))(v11, v12, &v47, v2)` |
| `::CCBUI_SetupAIWindow` | inline | `UIProgressBar` | 16 | self_arg_mismatch | `(*(void ( **)(UIProgressBar *, int, int *, int))(*(_DWORD *)&v21->UIWnd + 16))( v21, g_nMagicTabIDs[v16], &v47, v2)` |
| `::CCBUI_SetupAIWindow` | inline | `_DWORD` | 16 | non_class_hint | `(*(void ( **)(_DWORD, int, int *, int))(*(_DWORD *)*(v23 - 11) + 16))( *(v23 - 11), 79, &v47, v2)` |
| `::CUtil_Update` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v3 + 24))(v3, 1000, 0, 0)` |
| `::CUtil_Update` | inline | `int` | 24 | self_arg_mismatch | `(*(void ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(1000, 0, 0)` |
| `::UIScene_InitScriptScene` | vftable_local | `int` | 16 | non_class_hint | `(*(int ( **)(int, int *, int *, int))(v5 + 16))(v2 + 360, &byte_A00B00, &v40, v2)` |
| `::UIScene_InitScriptScene` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, int))(*(_DWORD *)(v2 + 1120) + 16))(v2 + 1120, &byte_A00B05, v53, v2)` |
| `::UIScene_InitScriptScene` | vftable_local | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, int, char *, int))(v12 + 28))( v2 + 1272, &byte_A00B01, v54, v2, aUiGamemainuiCo, v11)` |
| `::UIScene_InitScriptScene` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 1888) + 28))( v2 + 1888, &dword_A00B08, v44, v2, aUiGamemainuiMu_1, 0, v36)` |
| `::MiniGame2Update` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)v4 + 4))(v4)` |
| `::MiniGame2Scene_UpdateMiniGame2` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)v3 + 20))(v3)` |
| `::MatrixStack_BeginSceneWithRotation` | inline | `Actor` | 16 | self_arg_mismatch | `(*(void ( **)(Actor *, _DWORD))(*(_DWORD *)&v3[1]->m_actarray_type + 16))(v3[1], 0)` |
| `::RoleSystem_InitAllSystems` | vftable_local | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, _DWORD *, int))(v4 + 16))(v3 + 364, 10, v28, v3)` |
| `::RoleSystem_InitAllSystems` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int *, int *, int))(*(_DWORD *)&v10->UIWnd + 16))( v10, &byte_ABC00C, &v19, v3)` |
| `::RoleSystem_InitAllSystems` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int *, _DWORD *, int))(*(_DWORD *)(v3 + 7432) + 16))(v3 + 7432, &dword_AABC04, v27, v3)` |
| `::crt_sub_00541210` | inline | `float` | 8 | non_class_hint | `(*(int ( **)(float *))(*(_DWORD *)v26 + 8))(v26)` |
| `::crt_sub_00541210` | inline | `int` | 16 | self_arg_mismatch | `(*(void ( **)(int *, _DWORD, _DWORD, int, int))(*(_DWORD *)v26 + 16))( &v28, LODWORD(v16), LODWORD(v17), 1176256512, 1176256512)` |
| `::crt_sub_00541590` | inline | `gbGfxManager` | 100 | slot_out_of_range | `(*(int ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 100))( gfxMgr, *(_DWORD *)(result + 4 * v3))` |
| `CCBMagicWindow::Destroy` | inline | `UIPushButton` | 20 | self_arg_mismatch | `(*(void ( **)(UIPushButton *, int))(*(_DWORD *)&m_pButtonWater->UIWnd + 20))(m_pButtonWater, 1)` |
| `CCBProtectWindow::RenderText` | inline | `CCBProtectWindow` | 12 | self_arg_mismatch | `(*(void ( **)(CCBProtectWindow *))(*(_DWORD *)&this->UIWnd + 12))(this)` |
| `CEffAudio::UpdateInternal` | inline | `CTaskTpl_tagEffTaskParam_CEffAudio` | 4 | no_vtables_declaration | `(*(void ( **)(CTaskTpl_tagEffTaskParam_CEffAudio *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2->_tail_000 + 4))( v2, *(_DWORD *)(*v4 + v6), *(_DWORD *)(*v4 + v6 + 4), 0)` |
| `UIScene::Destroy_C910` | inline | `UIWnd` | 20 | name_not_declared_for_class | `(*(void ( **)(UIWnd *, int))(*(_DWORD *)m_pChildWnd + 20))(m_pChildWnd, 1)` |
| `CCBRoleState::FormatItemResultText` | inline | `_DWORD` | 1096 | self_arg_mismatch | `(***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)&this->UIWnd + 4) + 1096))(0)` |
| `CCBRoleState::FormatItemResultText` | inline | `_DWORD` | 1100 | self_arg_mismatch | `(***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)&this->UIWnd + 4) + 1100))(0)` |
| `CCBRoleState::FormatItemResultText` | inline | `_DWORD` | 1092 | self_arg_mismatch | `(***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)&this->UIWnd + 4) + 1092))(0)` |
| `CCBRoleState::FormatItemResultText` | inline | `_DWORD` | 1088 | self_arg_mismatch | `(***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)&this->UIWnd + 4) + 1088))(0)` |
| `CCBRoleState::FormatItemResultText` | inline | `_DWORD` | 1104 | self_arg_mismatch | `(***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)&this->UIWnd + 4) + 1104))(0)` |
| `CCBRoleState::FormatItemResultText` | inline | `_DWORD` | 1084 | self_arg_mismatch | `(***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)&this->UIWnd + 4) + 1084))(0)` |
| `CCBRoleState::FormatItemResultText` | inline | `int` | 1084 | self_arg_mismatch | `(***(void ( ****)(int))(*(_DWORD *)(*(_DWORD *)&this->UIWnd + 4) + 1084))(1)` |
| `CGameData::Cleanup` | inline | `SceneObj` | 20 | self_arg_mismatch | `(*(void ( **)(SceneObj *, int))(*(_DWORD *)&m_pSceneObjRef->UIWnd + 20))(m_pSceneObjRef, 1)` |
| `CGameData::ProcessDialog` | inline | `SceneObj` | 4 | self_arg_mismatch | `(*(void ( **)(SceneObj *))(*(_DWORD *)&this->m_pSceneObjRef->UIWnd + 4))(this->m_pSceneObjRef)` |
| `CGameData::Load` | inline | `SceneObj` | 24 | self_arg_mismatch | `(*(void ( **)(SceneObj *, int, _DWORD, _DWORD))(*(_DWORD *)&m_pSceneObjRef->UIWnd + 24))( m_pSceneObjRef, 1000, 0, 0)` |
| `CGameData::Load` | inline | `SceneObj` | 20 | self_arg_mismatch | `(*(void ( **)(SceneObj *, int))(*(_DWORD *)&v13->UIWnd + 20))(v13, 1)` |
| `CGameData::SceneUpdate` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)v4 + 4))(v4)` |
| `CGameData::SceneUpdate` | inline | `_BYTE` | 8 | non_class_hint | `(*(void ( **)(_BYTE *, int, int))(*(_DWORD *)v5 + 8))(v5, nVal, nVal2)` |
| `CGameData::SceneUpdate` | inline | `char` | 8 | non_class_hint | `(*(void ( **)(char *, int, int))(*(_DWORD *)this->m_pGameObj + 8))(this->m_pGameObj, nVal, nVal2)` |
| `CGameData::SceneUpdate` | inline | `SceneObj` | 8 | self_arg_mismatch | `(*(int ( **)(SceneObj *, int, bool))(*(_DWORD *)&this->m_pSceneObjRef->UIWnd + 8))( this->m_pSceneObjRef, nVal, v6 == 0)` |
| `CCBUI::CreateButton` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int, CCBUI *))(*(_DWORD *)&this->m_pAttackSequenBack->UIWnd + 16))( this->m_pAttackSequenBack, 131, parent, this)` |
| `CCBControlWindow::CreateControls` | inline | `UIStatic` | 16 | self_arg_mismatch | `(*(void ( **)(UIStatic *, int, int *, CCBControlWindow *))(*(_DWORD *)&this->m_pBack->UIWnd + 16))( this->m_pBack, 161, pRect, this)` |
| `CCBControlWindow::CreateControls` | inline | `UIButton` | 28 | self_arg_mismatch | `(*(void ( **)(UIButton *, int, int *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)&(*p_m_pButtonSkill)->UIWnd + 28))( *p_m_pButtonSkill, *v10, pRect, this, 0, 0, 0)` |
| `CCBPanelSlot::ShowClipped` | vftable_local | `int` | 24 | self_arg_mismatch | `(*(int ( **)(int, int, _DWORD))(v3 + 24))(1000, nFlags, 0)` |
| `EquipUI::NavigateSlots` | vftable_local | `EquipUI` | 24 | self_arg_mismatch | `(*(int ( **)(EquipUI *, int, _DWORD, _DWORD))(v5 + 24))( this, 1001, *(&dword_56E148 + PrevSlot), 0)` |
| `EquipUI::NavigateSlots` | inline | `EquipUI` | 24 | self_arg_mismatch | `(*(int ( **)(EquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)&this->UIWnd + 24))(this, 1010, 0, 0)` |
| `RoleStatePanel::RenderThrottled` | inline | `UITitle_XJTM` | 4 | self_arg_mismatch | `(*(int ( **)(UITitle_XJTM *))(*(_DWORD *)&this->m_pSubTab1->UIWnd + 4))(this->m_pSubTab1)` |
| `RoleStatePanel::UpdateCaptions` | inline | `UITitle_XJTM` | 8 | self_arg_mismatch | `(*(void ( **)(UITitle_XJTM *, int, int))(*(_DWORD *)&this->m_pSubTab1->UIWnd + 8))( this->m_pSubTab1, nVal, a3)` |
| `Actor::_todo_004B7980` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, Buffer)` |
| `Actor::_todo_004B7D30` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, aEffectSaveTga)` |
| `C2DSpark::C2DSpark` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, aEffectFlare3Bm)` |
| `C3DSpark::C3DSpark` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, aEffectFlare3Bm)` |
| `CCBParabolaWindow::LoadResourceEx` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v6 + 8))(gfxMgr, v7)` |
| `CCBParabolaWindow::LoadResourceEx` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, Buffer)` |
| `CCBStageScene::CCBStageScene` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, asc_5DBFD0)` |
| `CCBStageShadow::CCBStageShadow` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, asc_5DC254)` |
| `CEffCylinder::LoadTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)this->m_pEM->m_pDisplay + 8))( this->m_pEM->m_pDisplay, pFileName)` |
| `CEffExplosive::LoadTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)this->m_pEM->m_pDisplay + 8))( this->m_pEM->m_pDisplay, pFileName)` |
| `CEffQuad::ToNextFrame` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)this->m_pEM->m_pDisplay + 8))( this->m_pEM->m_pDisplay, nQuad)` |
| `CEffectSystem::IsVisible` | inline | `gbGfxManager` | 84 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, _DWORD *, int))(*(_DWORD *)gfxMgr->_tail_000 + 84))(gfxMgr, v6, 1)` |
| `CEffectSystem::IsVisible` | inline | `gbGfxManager` | 88 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `CEffectSystem::IsVisible` | inline | `gbGfxManager` | 92 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, float *))(*(_DWORD *)gfxMgr->_tail_000 + 92))(gfxMgr, p_eu)` |
| `CEffectSystem::HandleViewMove` | inline | `gbGfxManager` | 92 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr->_tail_000 + 92))(gfxMgr, 96 * v4 + v2 + 60)` |
| `CScreenMode::IsSceneReady` | inline | `gbGfxManager` | 88 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `PAL3::Render` | inline | `gbGfxManager` | 48 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 48))(gfxMgr)` |
| `PAL3::Render` | inline | `gbGfxManager` | 52 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 52))(gfxMgr)` |
| `PAL3::Render` | inline | `gbGfxManager` | 112 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr->_tail_000 + 112))(gfxMgr, &g_nPAL3_D8E488)` |
| `PAL3::PrintScreen` | inline | `gbGfxManager` | 84 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)gfxMgr->_tail_000 + 84))(gfxMgr, &v24, 1)` |
| `PAL3::PrintScreen` | inline | `gbGfxManager` | 88 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `PalScript::OpenScript` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6)` |
| `PalScript::OpenScript` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, Buffer)` |
| `PalScriptWaitObj::ReleaseObject` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, pszBuf)` |
| `RenderTarget::LoadTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, m_szTexPath)` |
| `RenderTarget::RenderToTexture` | inline | `gbGfxManager` | 60 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 60))(gfxMgr)` |
| `RenderTarget::Create` | inline | `gbGfxManager` | 84 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)gfxMgr->_tail_000 + 84))(gfxMgr, &v2, 1)` |
| `RenderTarget::Create` | inline | `gbGfxManager` | 88 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 88))(gfxMgr)` |
| `RenderTarget::OnResetDevice` | inline | `gbGfxManager` | 92 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, gbTexture_D3D **))(*(_DWORD *)gfxMgr->_tail_000 + 92))( gfxMgr, &this->m_ScreenPlane)` |
| `RenderTarget::OnResetDevice` | inline | `gbGfxManager` | 48 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 48))(gfxMgr)` |
| `RenderTarget::OnResetDevice` | inline | `gbGfxManager` | 52 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr->_tail_000 + 52))(gfxMgr)` |
| `RenderTarget::RenderToScreen` | inline | `gbGfxManager` | 92 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 92))(gfxMgr, 0)` |
| `RenderTarget2::Resolve` | vftable_local | `gbGfxManager` | 60 | no_vtables_declaration | `(*(void ( **)(gbGfxManager *))(v4 + 60))(v3)` |
| `RoleSystem::LoadRoleImage` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, 0)` |
| `ScreenEffectMgr::LoadResources` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, aEffectRayTga)` |
| `UI3DCtrl::CreateWithTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, nVal)` |
| `UIDialog::Create` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, tex)` |
| `UIFrameWnd::SetTextureByID` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, nTexID)` |
| `UIFrameWnd::SetTextureByName` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v3)` |
| `UIFrameWnd::SetTextureByName` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v7 + 8))(gfxMgr, v8)` |
| `UIFrameWnd::LoadFrameResources` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, Buffer)` |
| `UIListBox::SetSelTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, gbVFileSystem *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, m_plastsys)` |
| `UIListBox::CalScrollBarRange` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v9 + 8))(gfxMgr, v10)` |
| `UIListBox::CalScrollBarRange` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v7)` |
| `UIListBox::GetSel` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, v3)` |
| `UIListBox::LoadListItems` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, Source)` |
| `UIListBox::SetMouseMoveSel` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, Source)` |
| `UIManager::LoadShadowTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, aShadowTga)` |
| `UIPushButton::CreateWithTextures` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v10 + 8))(gfxMgr, v11)` |
| `UIPushButton::CreateWithTextures` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, Buffer)` |
| `UIPushButton::FormatText` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6)` |
| `UIPushButton::FormatText` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, pszName)` |
| `UIPushButton::LoadResource` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6)` |
| `UIPushButton::LoadResource` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, LPCSTR))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, lpString)` |
| `UIPushButton::LoadTexture` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6)` |
| `UIPushButton::LoadTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, pszName)` |
| `UIPushButton::SetText` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v3 + 8))(gfxMgr, v4)` |
| `UIPushButton::SetText` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, Buffer)` |
| `UIPushButton::LoadTextureByName` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v6 + 8))(gfxMgr, v7)` |
| `UIPushButton::LoadTextureByName` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v3)` |
| `UIPushButton::CreateFromTemplate` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v7 + 8))(gfxMgr, v8)` |
| `UIPushButton::CreateFromTemplate` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v3)` |
| `UIRenderObj::~UIRenderObj` | inline | `gbGfxManager` | 104 | no_vtables_declaration | `(*(void (**)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 104))( gfxMgr, (unsigned __int8)nVal1)` |
| `UIScene::SetTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v3)` |
| `UIScene::SetTexture` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v7 + 8))(gfxMgr, v8)` |
| `UIScene::CreateScrollWidget` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v18 + 8))(gfxMgr, v19)` |
| `UIScene::CreateScrollWidget` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, Buffer)` |
| `UIScene::GetChildCount` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v1)` |
| `UIScene::GetChildCount` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6)` |
| `UIScene::GetChildAt` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v1)` |
| `UIScene::GetChildAt` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6)` |
| `UIScene::SetTextParam` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, v1)` |
| `UIScene::SetTextParam` | vftable_local | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6)` |
| `::PalScriptIdleObj_LoadScriptTexture` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, nVal)` |
| `::ParticleEffect_LoadTextures` | inline | `gbGfxManager` | 8 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))( gfxMgr, Buffer)` |
| `::crt_sub_00541590` | inline | `gbGfxManager` | 100 | no_vtables_declaration | `(*(int ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr->_tail_000 + 100))( gfxMgr, *(_DWORD *)(result + 4 * v3))` |
| `MXTransport::UpdateFrontEffect` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)v2 + 16))(v2)` |
| `MXTransport::Create` | inline | `MXTransport` | 12 | self_arg_mismatch | `(*(void ( **)(MXTransport *, _DWORD))(*(_DWORD *)&this->gbChain1DNode + 12))(this, 0)` |
| `MXTransport::IsFadeActive` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)m_numNode + 4))(m_numNode)` |
| `UICoverFrm::RenderWithSceneMap` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)this[1].m_column[0].width + 4))(this[1].m_column[0].width)` |
| `CCBStage::SetParam` | inline | `gbChain1DNode` | 24 | slot_out_of_range | `(*(void ( **)(gbChain1DNode *, _DWORD))(*(_DWORD *)this->m_nTodo_124->children.m_Tail + 24))( this->m_nTodo_124->children.m_Tail, 0)` |
| `CCBStage::ProcessSlotAction` | inline | `gbChain1DNode` | 24 | slot_out_of_range | `(*(void ( **)(gbChain1DNode *, _DWORD))(*(_DWORD *)this->m_nTodo_124->children.m_Tail + 24))( this->m_nTodo_124->children.m_Tail, 0)` |
| `CCBStage::OnPhysicalHit` | inline | `gbChain1DNode` | 24 | slot_out_of_range | `(*(void ( **)(gbChain1DNode *, _DWORD))(*(_DWORD *)this->m_nTodo_124->children.m_Tail + 24))( this->m_nTodo_124->children.m_Tail, 0)` |
| `ScreenEffectNode::Object3D_RenderTransformed` | inline | `int` | 12 | non_class_hint | `(*(void ( **)(int, _DWORD))(*(_DWORD *)v2 + 12))(v2, 0)` |
| `CCBControlWindow::CreateControls` | inline | `UIListBox` | 28 | self_arg_mismatch | `(*(void ( **)(UIListBox *, int, int *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)&(*v11)->UIWnd + 28))( *v11, *v10, pRect, this, 0, 0, 0)` |
| `CCBControlWindow::Update` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1)` |
| `CCBFiveNimbusWindow::Destroy` | inline | `_DWORD` | 20 | non_class_hint | `(*(void ( **)(_DWORD, int))(*(_DWORD *)*v2 + 20))(*v2, 1)` |
| `CCBItemWindow::CCBItemWindow_Destroy` | inline | `_DWORD` | 20 | non_class_hint | `(*(void ( **)(_DWORD, int))(*(_DWORD *)*v2 + 20))(*v2, 1)` |
| `CCBItemWindow::Create` | inline | `_DWORD` | 16 | non_class_hint | `(*(void ( **)(_DWORD, int, int *, CCBItemWindow *))(*(_DWORD *)*v4 + 16))(*v4, 232, pRect, this)` |
| `CCBItemWindow::Create` | inline | `_DWORD` | 28 | non_class_hint | `(*(void ( **)(_DWORD, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)*v6 + 28))( *v6, 214, pRect, this, g_nUnkDataTable[22], 0)` |
| `CCBItemWindow::Destroy` | inline | `_DWORD` | 20 | non_class_hint | `(*(void ( **)(_DWORD, int))(*(_DWORD *)*v10 + 20))(*v10, 1)` |
| `CCBMagicWindow::CreateButton` | inline | `_DWORD` | 28 | non_class_hint | `(*(void ( **)(_DWORD, int, int *, CCBMagicWindow *, void *, int, _DWORD))(*(_DWORD *)*v26 + 28))( *v26, 282, ppButton, this, &unk_5DF59C, 1, 0)` |
| `CCBParabolaWindow::~CCBParabolaWindow` | inline | `int` | 20 | non_class_hint | `(*(void (**)(int, int))(*(_DWORD *)v2 + 20))(v2, 1)` |
| `CCBParabolaWindow::~CCBParabolaWindow` | inline | `_DWORD` | 20 | non_class_hint | `(*(void (**)(_DWORD, int))(*(_DWORD *)*v3 + 20))(*v3, 1)` |
| `CCBParabolaWindow::Destroy_c880` | inline | `_DWORD` | 20 | non_class_hint | `(*(int ( **)(_DWORD, int))(*(_DWORD *)*v3 + 20))(*v3, 1)` |
| `CCBProtectWindow::Destroy` | inline | `_DWORD` | 20 | non_class_hint | `(*(void ( **)(_DWORD, int))(*(_DWORD *)*v3 + 20))(*v3, 1)` |
| `CCBResultWindow::Destroy` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int, int))(*(_DWORD *)v2 + 20))(v2, 1)` |
| `CCBSkillWindow::Create` | inline | `_DWORD` | 16 | non_class_hint | `(*(void ( **)(_DWORD, int, int *, CCBSkillWindow *))(*(_DWORD *)*v4 + 16))(*v4, 513, pRect, this)` |
| `CCBSystem::ProcFling` | inline | `CCBUI` | 12 | no_vtables_declaration | `(*(void ( **)(CCBUI *))(*(_DWORD *)m_pUI + 12))(m_pUI)` |
| `CCBSystem::ProcFling` | inline | `CCBUI` | 20 | no_vtables_declaration | `(*(void ( **)(CCBUI *, int))(*(_DWORD *)v11 + 20))(v11, 1)` |
| `CCBUI::~CCBUI` | inline | `int` | 16 | non_class_hint | `(*(void (**)(int, int, int *, CCBUI *))(*(_DWORD *)v3 + 16))(v3, 1, &v8, this)` |
| `CCBUI::Reset` | inline | `int` | 16 | non_class_hint | `(*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v8 + 16))(v8, 784, &v10, this)` |
| `CCBUI::LineMove` | inline | `int` | 28 | non_class_hint | `(*(int ( **)(int, POINT *, int, CCBUI *, int, _DWORD))(*(_DWORD *)v5 + 28))( v5, pEnd, v10, this, v11, 0)` |
| `LineupUI::CreatePreviewScene` | inline | `char` | 28 | non_class_hint | `(*(void ( **)(char *, const char *, char *, LineupUI *, char *, int, int))(*(_DWORD *)v27 + 28))( v27, (&off_56B97C)[v25], pszName, this, &aUiGamemainuiLi[v46], 1, v24)` |
| `MainEquipUI::InitMainEquipUI` | inline | `UIPushButton` | 16 | self_arg_mismatch | `(*(int ( **)(UIPushButton *, int, int *, MainEquipUI *))(*(_DWORD *)&v33->UIWnd + 16))( v33, 4371, &v79, this)` |
| `MainEquipUI::HandleMessage` | inline | `int` | 24 | non_class_hint | `(*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(v4, 1000, 0, 0)` |
| `MainPropUI::HandleKeyInput` | vftable_local | `MainPropUI` | 24 | name_not_declared_for_class | `(*(int ( **)(MainPropUI *, int, _DWORD, _DWORD))(v4 + 24))( this, 1001, *(&dword_56D5F0 + NextValid), 0)` |
| `MainPropUI::HandleKeyInput` | inline | `MainPropUI` | 24 | name_not_declared_for_class | `(*(void ( **)(MainPropUI *, int, int *, _DWORD))(*(_DWORD *)this + 24))(this, 1001, &byte_A00323, 0)` |
| `PalScript::Op_AddItem` | inline | `CCBItemWindow` | 8 | name_declared_at_other_address | `(*(void ( **)(CCBItemWindow *, _DWORD, _DWORD))(*(_DWORD *)v4 + 8))(v4, 0, 0)` |
| `PropUI::InitListUI` | inline | `PropUI` | 24 | slot_out_of_range | `(*(void ( **)(PropUI *, int, _DWORD, _DWORD))(*(_DWORD *)this + 24))(this, 1007, 0, 0)` |
| `RoleStatePanel::RenderThrottled` | inline | `UITitle_XJTM` | 4 | no_vtables_declaration | `(*(int ( **)(UITitle_XJTM *))(*(_DWORD *)this->m_pSubTab1 + 4))(this->m_pSubTab1)` |
| `RoleStatePanel::UpdateCaptions` | inline | `UITitle_XJTM` | 8 | no_vtables_declaration | `(*(void ( **)(UITitle_XJTM *, int, int))(*(_DWORD *)this->m_pSubTab1 + 8))(this->m_pSubTab1, nVal, a3)` |
| `SaleUI::OnMessage` | inline | `SaleUI` | 24 | slot_out_of_range | `(*(void ( **)(SaleUI *, int, _DWORD, _DWORD))(*(_DWORD *)this + 24))(this, 1007, 0, 0)` |
| `SystemUI::UIUpdate` | inline | `int` | 20 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)v4 + 20))(v4)` |
| `TaskBookUI::RefreshTaskList` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int *, _DWORD *, TaskBookUI *))(*(_DWORD *)v5 + 16))(v5, &byte_A00703, v10, this)` |
| `UITitle_JDHY::InitNoteItems` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int *, _DWORD *, UITitle_JDHY *))(*(_DWORD *)v5 + 16))(v5, &byte_A00703, v10, this)` |
| `UITitle_XJTM::CreateSubWidgets` | inline | `char` | 16 | non_class_hint | `(*(int ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*(_DWORD *)v3 + 16))(v3, 0, &v16, this)` |
| `::WinProc` | inline | `_DWORD` | 44 | non_class_hint | `(*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v7[1].InvViewMatrix.xy) + 44))( LODWORD(v7[1].InvViewMatrix.xy), Point.x, Point.y, 1)` |
| `RenderTarget2::UpdatePost` | inline | `float` | 4 | non_class_hint | `(*(void ( **)(float *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2 + 4))( v2, *(_DWORD *)(*v4 + v6), *(_DWORD *)(*v4 + v6 + 4), 0)` |
| `CCBStage::RunActiveTask` | inline | `unsigned int` | 16 | non_class_hint | `(*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)inited[1].dwMagicID[1][3] + 16))( inited[1].dwMagicID[1][3], 0)` |
| `PalScriptMgr::BuildCmdTransform` | inline | `gbVisNode` | 56 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, gbMatrix4 *))(*(_DWORD *)&this->m_pScriptObjMain->gbChain1DNode + 56))( this->m_pScriptObjMain, pMatrix)` |
| `PalScriptMgr::UpdateScriptRoles` | inline | `gbVisNode` | 24 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, int))(*(_DWORD *)&this->m_pScriptObjMain->gbChain1DNode + 24))( this->m_pScriptObjMain, -1082130432)` |
| `PalScriptMgr::OnAnimFinish` | inline | `gbVisNode` | 24 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)&this->m_pScriptObjMain->gbChain1DNode + 24))( this->m_pScriptObjMain, 0)` |
| `PalScriptMgr::ExecuteOpcode` | inline | `gbVisNode` | 24 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)&this->m_pScriptObjMain->gbChain1DNode + 24))( this->m_pScriptObjMain, 0)` |
| `PalScriptMgr::ExecuteFrame` | inline | `gbVisNode` | 24 | self_arg_mismatch | `(*(void ( **)(gbVisNode *, int))(*(_DWORD *)&this->m_pScriptObjMain->gbChain1DNode + 24))( this->m_pScriptObjMain, -1082130432)` |
| `UIListBox::UIListBox_IsVisible` | inline | `int` | 4 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)(v1 + 1296) + 4))(v1 + 1296)` |
| `::GetCellStateByte` | inline | `_BYTE` | 24 | non_class_hint | `(*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 262, 0)` |
| `::GetInputFlag` | inline | `_BYTE` | 24 | non_class_hint | `(*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 518, 0)` |
| `::GetUpdateFlag` | inline | `_BYTE` | 24 | non_class_hint | `(*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 788, 0)` |
| `::CreateSceneEntities` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, int *, Actor *))(v11 + 16))(&_this[5].m_curact[27], 161, &v73, _this)` |
| `::CreateSceneEntities` | inline | `int` | 28 | non_class_hint | `(*(void ( **)(int, char *, int *, Actor *, const char *, int, _DWORD))(*(_DWORD *)v64 + 28))( v64, (char *)*v59, nVal2, _this, v14, 1, 0)` |
| `::_todo_0051DFD0` | vftable_local | `char` | 16 | non_class_hint | `(*(int ( **)(char *, char *, int *, Actor *))(v29 + 16))( &_this[1].m_curact[19], &byte_A01B00, &v117, _this)` |
| `CCBStage::GetReadyCount` | inline | `int` | 24 | non_class_hint | `(*(void ( **)(int))(*(_DWORD *)*p_gap_16 + 24))(*p_gap_16)` |
| `::_todo_004B7560` | inline | `float` | 16 | self_arg_mismatch | `(*(void ( **)(float, _DWORD))(*(_DWORD *)LODWORD(m_fMatrixParamB) + 16))( _pal3_coerce_f32(LODWORD(m_fMatrixParamB)), 0)` |
| `::_todo_004B7560` | inline | `Actor` | 12 | self_arg_mismatch | `(*(void ( **)(Actor *, _DWORD))(*(_DWORD *)&_this->m_actarray_type + 12))(_this, 0)` |
| `::SetTextureName` | inline | `gbActorDef` | 60 | self_arg_mismatch | `(*(void ( **)(gbActorDef *, char *))(*(_DWORD *)&_this->m_pact->pBody->gbRefObject + 60))( _this->m_pact->pBody, _this->m_szTexture)` |
| `::SetActionByName` | inline | `gbActorDef` | 60 | self_arg_mismatch | `(*(void ( **)(gbActorDef *, char *))(*(_DWORD *)&v9->pBody->gbRefObject + 60))(v9->pBody, m_szTexture)` |
| `::SetParam` | inline | `Actor` | 20 | self_arg_mismatch | `(*(int ( **)(Actor *))(*(_DWORD *)&m_actarray_begin->m_actarray_type + 20))(m_actarray_begin)` |
| `::SetMaterialName` | inline | `gbActorDef` | 60 | self_arg_mismatch | `(*(void ( **)(gbActorDef *, char *))(*(_DWORD *)&v16->pBody->gbRefObject + 60))(v16->pBody, m_szTexture)` |
| `::ActVec_Fn_6160` | inline | `Actor` | 20 | self_arg_mismatch | `(*(int ( **)(Actor *))(*(_DWORD *)&m_actarray_begin->m_actarray_type + 20))(m_actarray_begin)` |
| `CCBStage::IsIdle` | vftable_local | `_DWORD` | 1072 | self_arg_mismatch | `(***(void ( ****)(_DWORD, _DWORD))(v9 + 1072))(*(_DWORD *)(v9 + 1072), 0)` |
| `CCBStage::IsIdle` | vftable_local | `_DWORD` | 1076 | self_arg_mismatch | `(***(void ( ****)(_DWORD, _DWORD))(v9 + 1076))(*(_DWORD *)(v9 + 1076), 0)` |
| `::_todo_00536160` | inline | `Actor` | 20 | self_arg_mismatch | `(*(int ( **)(Actor *))(*(_DWORD *)&m_actarray_begin->m_actarray_type + 20))(m_actarray_begin)` |
| `::_todo_00537120` | inline | `gbActorDef` | 60 | self_arg_mismatch | `(*(void ( **)(gbActorDef *, char *))(*(_DWORD *)&_this->m_pact->pBody->gbRefObject + 60))( _this->m_pact->pBody, _this->m_szTexture)` |
| `::InitCombatUI` | inline | `SaleUI_SortData` | 16 | self_arg_mismatch | `(*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&v6 + 16))( &_this->m_sort[353][4], 257, v165, _this)` |
| `::InitCombatUI` | inline | `SaleUI_SortData` | 28 | self_arg_mismatch | `(*(void ( **)(SaleUI_SortData *, int, _DWORD *, char *, _DWORD, SaleUI *))(*(_DWORD *)&v8 + 28))( &_this->m_sort[349][3], 257, v162, aUiFlexFramebar, 0, _this)` |
| `::InitCombatUI` | vftable_local | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, int *, SaleUI *))(v28 + 16))( &_this->ml_ResumeList.m_column[0].head[16], 161, &v150, _this)` |
| `::InitCombatUI` | inline | `char` | 16 | non_class_hint | `(*(void ( **)(char *, int, UILBColumn *, SaleUI *))(*(_DWORD *)&_this->ml_ResumeList.m_column[4].head[16] + 16))( &_this->ml_ResumeList.m_column[4].head[16], 272, &_this->ml_Resume` |
| `::InitCombatUI` | inline | `SaleUI_SortData` | 16 | no_vtables_declaration | `(*(void ( **)(SaleUI_SortData *, _DWORD, _DWORD *, SaleUI *))(*(_DWORD *)&_this->m_sort[369][38 * v36 + 3] + 16))( &_this->m_sort[369][38 * v36 + 3], *(&dword_56B3C8 + v36), v147, ` |
| `::InitCombatUI` | inline | `_BYTE` | 16 | non_class_hint | `(*(void ( **)(_BYTE *, _DWORD, _DWORD *, SaleUI *))(*(_DWORD *)&_this->m_IsEquip[216 * *(_DWORD *)&_this->remarkbuf[20] + 23][1] + 16))( &_this->m_IsEquip[216 * *(_DWORD *)&_this->` |
| `::InitCombatUI` | inline | `char` | 28 | non_class_hint | `(*(void ( **)(char *, int, char *, SaleUI *, char *, _DWORD, int))(*(_DWORD *)&_this->ml_TreasureList.m_column[1].head[36] + 28))( &_this->ml_TreasureList.m_column[1].head[36], 264` |
| `::InitCombatUI` | inline | `int` | 28 | self_arg_mismatch | `(*(void ( **)(int, char *, SaleUI *, char *, _DWORD, int))(*(_DWORD *)&_this->m_Icon[2][4].m_mouseoff + 28))( 304, _this->m_Icon[3][2].m_text, _this, aUiAssistantEqu_18, 0, v142)` |
| `::SwitchEditorCamPos` | inline | `gbGeomNode` | 20 | self_arg_mismatch | `(*(int ( **)(gbGeomNode *))(*(_DWORD *)&_this->m_pPointer->gbChain1DNode + 20))(_this->m_pPointer)` |
| `::SetParam` | inline | `int` | 20 | non_class_hint | `(*(int ( **)(int))(*(_DWORD *)v5 + 20))(v5)` |
