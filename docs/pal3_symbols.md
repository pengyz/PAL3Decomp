# PAL3.exe Known Symbols

Extracted from PAL3patch reverse engineering project.
Total: 111 symbols

## Game Functions

| Address | Name | Type | Size |
|---------|------|------|------|
| 0x00402150 | call_site_GRPinput_AcquireMouse_wrapper | call_site | ?B |
| 0x00402198 | call_site_GRPinput_AcquireKeyboard_wrapper | call_site | ?B |
| 0x004021c1 | patched_by_GetCursorPos_wrapper | patch_site | ?B |
| 0x00402290 | patched_by_SetCursorPos_wrapper | patch_site | 19B |
| 0x004022e0 | patched_by_GetCursorPos_wrapper | patch_site | 14B |
| 0x00402310 | GRPinput_AcquireMouse | method | 65B |
| 0x00402380 | GRPinput_AcquireKeyboard | method | 75B |
| 0x00402497 | patched_by_GetCursorPos_wrapper | patch_site | ?B |
| 0x00402d20 | HeadMsg_Render | method | 638B |
| 0x00404840 | call_site_PAL3_InitGFX_wrapper | call_site | ?B |
| 0x00404f8d | patched_by_DefWindowProcA_wrapper | patch_site | ?B |
| 0x00405013 | patched_by_gbCreateGraphManager_wrapper | patch_site | ?B |
| 0x00405f84 | call_site_GrayScale_End_wrapper | call_site | ?B |
| 0x00405fe0 | call_site_PlayerMgr_DrawMsg_hookpart1 | call_site | ?B |
| 0x004061d2 | call_site_UICursor_IRender_wrapper | call_site | ?B |
| 0x00406230 | patched_by_do_exit | patch_site | ?B |
| 0x0040637f | patched_by_WndProc_wrapper | patch_site | ?B |
| 0x004063a7 | patched_by_RegisterClass_wrapper | patch_site | ?B |
| 0x00406564 | patched_by_CreateWindowExA_wrapper | patch_site | ?B |
| 0x004066ad | patched_by_scursor_PAL3_HasCommandLineParam | patch_site | ?B |
| 0x0040c7f4 | call_site_HeadMsg_Render_wrapper | call_site | ?B |
| 0x0040c808 | call_site_PlayerMgr_DrawMsg_hookpart2 | call_site | ?B |
| 0x00411e00 | Role_UpdateMove | method | 342B |
| 0x004142e0 | Role_OnBehaviourFinish | method | 98B |
| 0x0041fa84 | call_site_UpdateLoading_wrapper | call_site | ?B |
| 0x00439410 | UI3DCtrl_Render | method | ?B |
| 0x00439850 | UI3DCtrl_SetOriginPt_XY | method | 224B |
| 0x00439930 | UI3DCtrl_SetOriginPt_XYFromY | method | 232B |
| 0x00439a20 | UI3DCtrl_Update | method | ?B |
| 0x00439fe0 | UI3DCtrl_GetMouseRay | method | 140B |
| 0x0043a270 | UIAnimateCtrl_Render | method | 363B |
| 0x0043ddf0 | UIFrameWnd_Render | method | 74B |
| 0x00442e90 | UIStaticEX_Render | method | ?B |
| 0x00443200 | UIStaticEXA_Render | method | ?B |
| 0x00445b90 | UIWnd_Create | method | 87B |
| 0x00445c60 | patched_by_UIWnd_Update | patch_site | 99B |
| 0x00445cd0 | UIWnd_Render_rewrited | method | 49B |
| 0x00445d20 | UIWnd_MoveWindow | method | 28B |
| 0x00445fa0 | UIWnd_SetRect | method | 52B |
| 0x0044f130 | UIGameFrm_Create | method | 763B |
| 0x0044f19a | call_site__TextureLib_Data_GetLibInfo_wrapper | call_site | ?B |
| 0x0044f2e9 | call_site_UIRoleDialog_Create_wrapper | call_site | ?B |
| 0x004500f0 | UIGameOver_Create | method | 161B |
| 0x00450f90 | UIRoleDialog_Create | method | 610B |
| 0x00451360 | UIRoleDialog_SetFace | method | 569B |
| 0x00452ceb | call_site_UISceneMap_Render_hookpart2 | call_site | ?B |
| 0x00483650 | LineupUI_Create | method | 2376B |
| 0x004a46f8 | call_site_LineupUI_Create_wrapper | call_site | ?B |
| 0x004b295a | call_site_Archive_Save_wrapper | call_site | ?B |
| 0x004b6e20 | GrayScale_End | method | 282B |
| 0x004b6fde | patched_by_gb_mem_allocator | patch_site | ?B |
| 0x004bdccf | patched_by_gbCamera_SetDimention_wrapper_for_RenderTarget_Begin | patch_site | ?B |
| 0x004c6460 | CTrail_Create | method | ?B |
| 0x004c65f0 | CTrail_Begin | method | 124B |
| 0x004d5ec0 | C2DSpark_CreateSingle | method | 83B |
| 0x004d6050 | C2DSpark_CreateStars | method | 330B |
| 0x004d61c0 | C2DSpark_Render | method | 421B |
| 0x004d6216 | patched_by_GetCursorPos_wrapper | patch_site | ?B |
| 0x004dba60 | patched_by_CCBAttackSequen_RunOneStep | patch_site | 185B |
| 0x004ed010 | CCBRoleState_IsAlive | method | 46B |
| 0x004fc3e1 | call_site_CTrail_Begin_wrapper | call_site | ?B |
| 0x0051270b | call_site_CCBUI_Create_wrapper | call_site | ?B |
| 0x00513141 | call_site_C2DSpark_Render_wrapper | call_site | ?B |
| 0x005163d0 | CCBUI_Create | method | 244B |
| 0x0051b920 | patched_by_CCBLineupWindow_Render | patch_site | 22B |
| 0x0051b950 | patched_by_CCBLineupWindow_IsPtOnFace | patch_site | 80B |
| 0x00529e40 | UIKillFlyer_Update | method | ?B |
| 0x0052beb0 | UIEncampment_Create | method | 1435B |
| 0x0052ee78 | call_site_UISkee_Create_wrapper | call_site | ?B |
| 0x00531f50 | UISkee_Create | method | 885B |
| 0x0053529f | call_site_UIRowing_Create_wrapper | call_site | ?B |
| 0x00536560 | UIRowing_Create | method | 825B |
| 0x00538500 | Archive_Save | method | 2013B |
| 0x0053c440 | patched_by_gbBinkVideo_OpenFile | patch_site | 32B |
| 0x0053c460 | gbBinkVideo_BinkWait | method | 16B |
| 0x0053c470 | patched_by_gbBinkVideo_DrawFrame | patch_site | 190B |
| 0x0053c530 | gbBinkVideo_DrawFrameEx | method | 106B |
| 0x0053c544 | patched_by_BinkDoFrame_wrapper | patch_site | ?B |
| 0x0053c571 | patched_by_BinkCopyToBuffer_wrapper | patch_site | ?B |
| 0x0053c672 | call_site_gbBinkVideo_BinkWait_wrapper | call_site | ?B |
| 0x0053c710 | gbBinkVideo_Width | method | 11B |
| 0x0053c720 | gbBinkVideo_Height | method | 12B |
| 0x0053d41e | patched_by_gb_mem_allocator | patch_site | ?B |
| 0x0053dd70 | SoundMgr_Create | method | ?B |
| 0x0053ddd7 | patched_by_gbAudioManager_Ctor_wrapper | patch_site | ?B |
| 0x0053def0 | SoundMgr_Destroy | method | 49B |
| 0x0053f960 | _TextureLib_Data_GetLibInfo | method | 901B |
| 0x00540f60 | UIRenderObj_Ctor | method | 58B |
| 0x00540fa0 | UIRenderObj_Dtor | method | 34B |
| 0x00541640 | UICursor_IRender | method | 203B |
| 0x00541710 | UICursor_Show | method | 51B |
| 0x00541ac0 | call_site_PAL3_Create_wrapper | call_site | ?B |
| 0x00541bc0 | call_site_PAL3_Update_wrapper | call_site | ?B |
| 0x00552f55 | pal3free | function | 47B |
| 0x005536a9 | pal3malloc | function | 18B |
| 0x00553a81 | patched_by_my_fopen | patch_site | 19B |
| 0x0055514a | patched_by_do_exit | patch_site | ?B |

## Global Variables

| Address | Name | Type |
|---------|------|------|
| 0x005833b8 | PAL3_s_bActive | int |
| 0x005833bc | PAL3_s_flag | unsigned |
| 0x008acc10 | PAL3_m_screenImg | struct gbImage2D |
| 0x00a3a7d8 | g_bink | struct gbBinkVideo |
| 0x00bfad70 | g_input | struct GRPinput |
| 0x00bfd6c8 | PAL3_s_drvinfo | struct gbGfxDriverInfo |
| 0x00bfda60 | GB_GfxMgr | struct gbGfxManager_D3D * |
| 0x00bfda6c | PAL3_s_gamestate | int |
| 0x00bfda74 | PAL3_m_pCBSystem | struct CCBSystem * |
| 0x00bfdaa0 | PAL3_m_gametime | float |
| 0x00bfdab0 | g_msgbk | struct UIStaticFlex |
| 0x00c12b20 | g_lastupdateloading | DWORD |
| 0x00db9fd0 | g_gamefrm | struct UIGameFrm |
| 0x01895058 | ui_tex_color_gbf | struct gbRenderEffect * |