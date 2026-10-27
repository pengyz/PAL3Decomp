#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/MainEquipUI.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Role/Actor.h"
#include "Misc/ArcSceneMonster.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBUI.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Misc/ECBStageTaskState.h"
#include "UI/EquipUI.h"
#include "Misc/LineupComp.h"
#include "Misc/LineupUI.h"
#include "Misc/MUIDialog.h"
#include "Misc/NameSys.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "UI/StateUI.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIButtonEX.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "Misc/UIParticle.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UITitle_XJTM.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern char asc_5B74B8[];
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DCD03C[256];
extern CHAR byte_DCD13C[256];
extern CHAR byte_DCFC3C[512];

// 0x00479300
MainEquipUI::MainEquipUI()
{
  _DWORD *p_m_IsMsg; // eax
  int v3; // ecx
  int *p_m_nSize; // eax
  int v5; // ecx
  _PlugInfo **m_texarrayInfo; // eax
  int v7; // ecx
  _DWORD *p_m_benable_snd; // eax
  int v9; // ecx

  ((UIListBox *)this)->UIListBox::UIListBox();
  p_m_IsMsg = (_DWORD *)&this->m_IsMsg;
  v3 = 99;
  do
  {
    *p_m_IsMsg = 0xFFFF;
    p_m_IsMsg[1] = 0;
    p_m_IsMsg[2] = 0;
    p_m_IsMsg += 3;
    --v3;
  }
  while ( v3 );
  p_m_nSize = (int *)&this->m_OutFrameL.m_childs.m_nSize;
  v5 = 99;
  do
  {
    *p_m_nSize = 0xFFFF;
    p_m_nSize[1] = 0;
    p_m_nSize[2] = 0;
    p_m_nSize += 3;
    --v5;
  }
  while ( v5 );
  m_texarrayInfo = (_PlugInfo **)this->stp_Magic.m_texarrayInfo;
  v7 = 99;
  do
  {
    *m_texarrayInfo = (_PlugInfo *)0xFFFF;
    m_texarrayInfo[1] = 0;
    m_texarrayInfo[2] = 0;
    m_texarrayInfo += 3;
    --v7;
  }
  while ( v7 );
  p_m_benable_snd = (_DWORD *)&this->stp_BattleArray.m_benable_snd;
  v9 = 99;
  do
  {
    *p_m_benable_snd = 0xFFFF;
    p_m_benable_snd[1] = 0;
    p_m_benable_snd[2] = 0;
    p_m_benable_snd += 3;
    --v9;
  }
  while ( v9 );
  this->me_Role[2].m_RoleAttCng[2].m_bfocus = 0xFFFF;
  this->me_Role[2].m_RoleAttCng[2].pDebugTex = ((gbTexture *)0);
  this->me_Role[2].m_RoleAttCng[2].m_align = 0;
  LODWORD(this->me_Role[2].m_RoleAttCng[2].m_ratiow) = 0xFFFF;
  this->me_Role[2].m_RoleAttCng[2].m_ratioh = 0.0f;
  this->me_Role[2].m_RoleAttCng[2].m_textx = ((void *)0);
  this->me_Role[2].m_RoleAttCng[2].m_texty = (void *)0xFFFF;
  this->me_Role[2].m_RoleAttCng[2].m_fonttype = ((Parent_Data *)0);
  *(_DWORD *)this->me_Role[2].m_RoleAttCng[2].m_text = 0;
  ((UI3DCtrl *)&this->me_Role[2].m_RoleAttCng[2].m_ppicInfo)->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[3].m_bvisible))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[4].m_bvisible))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[5].m_bvisible))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[6].m_bvisible))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible))->UIFrameContainer::ResetContainerState();
  ((PalScript *)&this->me_Role[2].m_RoleAttCng[8].m_bvisible)->PalScript::PalScript();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[9].pDebugTex))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[2].pDebugTex))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[3].pDebugTex))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[4].pDebugTex))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[5].pDebugTex))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11]))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::UpdateKeyCtrl();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  ((UIRoleDialog *)&this->me_Role[3].m_Qi.m_rect.top)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this->me_Role[3].m_RoleAtt[3].m_ratioh)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh)->UIRoleDialog::UIRoleDialog();
  (((UIProgressBar *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh))->UIProgressBar::ctor();
  LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) = 0;
  this->me_Role[3].m_RoleAttEqual[3].m_texty = ((void *)0);
  this->me_Role[3].m_RoleAttEqual[3].m_textx = ((void *)0);
  this->me_Role[3].m_RoleAttEqual[3].m_text[8] = 0;
  *(_DWORD *)&this->me_Role[3].m_RoleAttEqual[3].m_text[4] = 0;
  *(_DWORD *)this->me_Role[3].m_RoleAttEqual[3].m_text = 0;
  this->bkWndX = 800;
  this->bkWndY = 600;
  this->j = 0;
  this->i = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] = 0;
  this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)-1;
  this->me_Role[2].m_RoleAttCng[2].m_pbkInfo = ((_PlugInfo *)0);
  memset(&this->me_Role[2].m_RoleAttCng[1].m_pbkInfo, 0, 0x60u);
  LOWORD(this->me_Role[2].m_RoleAttCng[2].m_benable) = 0;
  BYTE2(this->me_Role[2].m_RoleAttCng[2].m_benable) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_align = 0;
  this->me_Role[2].m_RoleAttCng[2].m_ratiow = 0.0f;
  this->me_Role[2].m_RoleAttCng[2].m_ratioh = 0.0f;
  this->me_Role[2].m_RoleAttCng[2].m_textx = ((void *)0);
  this->me_Role[2].m_RoleAttCng[2].m_texty = ((void *)0);
  this->me_Role[2].m_RoleAttCng[2].m_fonttype = ((Parent_Data *)0);
  this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 0;
  *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) = 1;
}

// 0x00479680
MainEquipUI::~MainEquipUI()
{
  (((PalScript *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh))->PalScript::Reset();
  (((UIRoleDialog *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)&this->me_Role[3].m_RoleAtt[3].m_ratioh))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)&this->me_Role[3].m_Qi.m_rect.top))->UIRoleDialog::~UIRoleDialog();
  (((UICaption *)&this->me_Role[3].m_ShenBar.m_decorateRc))->UICaption::Destroy2();
  (((UICaption *)&this->me_Role[3].m_JingVal.m_pfather))->UICaption::Destroy2();
  (((UICaption *)&this->me_Role[3].m_Jing.m_textx))->UICaption::Destroy2();
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::DeleteRow();
  (((UIFrameContainer *)&this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[5].pDebugTex))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[4].pDebugTex))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[3].pDebugTex))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[2].pDebugTex))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[9].pDebugTex))->UIFrameContainer::~UIFrameContainer();
  (((PalScript *)&this->me_Role[2].m_RoleAttCng[8].m_bvisible))->PalScript::ctor();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[6].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[5].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[4].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->me_Role[2].m_RoleAttCng[3].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)&this->me_Role[2].m_RoleAttCng[2].m_ppicInfo);
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x00479890
int MainEquipUI::InitMainEquipUI(int arg0)
{
  LONG bkWndY; // ecx
  gbTexture *pDebugTex; // edx
  int v5; // edx
  gbTexture *v6; // edx
  int v7; // edx
  _PlugInfo *m_ppicInfo; // edx
  int v9; // edx
  LONG v10; // edx
  int m_bvisible; // edx
  int v12; // edx
  gbTexture *v13; // edx
  int v14; // edx
  gbTexture *v15; // edx
  gbTexture *v16; // edx
  gbTexture *v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // edx
  gbTexture *v27; // eax
  int v28; // eax
  UIScene *v29; // edi
  int v30; // ecx
  int v31; // eax
  int v32; // edx
  gbTexture **p_pDebugTex; // edi
  int v34; // ebp
  int v35; // eax
  int v36; // ecx
  int v37; // eax
  void ( **m_textx)(void **, int, int *, MainEquipUI *, char *, _DWORD, int); // edx
  int v39; // edx
  int v40; // ecx
  int v41; // ecx
  LONG left; // eax
  int v43; // edx
  int v44; // edx
  int v45; // ecx
  gbTexture *v46; // edx
  unsigned int Color; // edx
  UIWnd *v48; // ecx
  LONG top; // edx
  int result; // eax
  int v51; // [esp+E0h] [ebp-E4h]
  int v52; // [esp+E4h] [ebp-E0h] BYREF
  int v53; // [esp+E8h] [ebp-DCh]
  int v54; // [esp+ECh] [ebp-D8h]
  int v55; // [esp+F0h] [ebp-D4h]
  int v56; // [esp+F4h] [ebp-D0h] BYREF
  int v57; // [esp+F8h] [ebp-CCh]
  int v58; // [esp+FCh] [ebp-C8h]
  int v59; // [esp+0x100] [ebp-C4h]
  _DWORD a2[2]; // [esp+0x104] [ebp-C0h] BYREF
  int v61; // [esp+0x10C] [ebp-B8h]
  int v62; // [esp+0x110] [ebp-B4h]
  int v63; // [esp+0x114] [ebp-B0h] BYREF
  int v64; // [esp+0x118] [ebp-ACh]
  int v65; // [esp+0x11C] [ebp-A8h]
  int v66; // [esp+0x120] [ebp-A4h]
  int p_DWORD; // [esp+0x124] [ebp-A0h] BYREF
  int v68; // [esp+0x128] [ebp-0x9C]
  int nHeight; // [esp+0x12C] [ebp-0x98]
  int v70; // [esp+0x130] [ebp-0x94]
  int v71; // [esp+0x134] [ebp-0x90]
  int v72; // [esp+0x138] [ebp-0x8C]
  int v73; // [esp+0x13C] [ebp-0x88]
  int v74; // [esp+0x140] [ebp-0x84]
  _DWORD v75[2]; // [esp+0x144] [ebp-0x80] BYREF
  int v76; // [esp+0x14C] [ebp-0x78]
  int v77; // [esp+0x150] [ebp-0x74]
  int v78; // [esp+0x154] [ebp-0x70] BYREF
  int v79; // [esp+0x158] [ebp-0x6C]
  int v80; // [esp+0x15C] [ebp-0x68]
  int v81; // [esp+0x160] [ebp-0x64]
  int v82; // [esp+0x164] [ebp-0x60] BYREF
  int v83; // [esp+0x168] [ebp-0x5C]
  int v84; // [esp+0x16C] [ebp-0x58]
  int v85; // [esp+0x170] [ebp-0x54]
  _DWORD v86[4]; // [esp+0x174] [ebp-0x50] BYREF
  _DWORD v87[4]; // [esp+0x184] [ebp-0x40] BYREF
  gbVec3D pDir; // [esp+0x194] [ebp-0x30] BYREF
  int v89; // [esp+0x1A0] [ebp-0x24]
  _DWORD v90[4]; // [esp+0x1A4] [ebp-0x20] BYREF
  gbVec3D pPos; // [esp+0x1B4] [ebp-0x10] BYREF
  int v92; // [esp+0x1C0] [ebp-0x4]

  bkWndY = this->bkWndY;
  this->rc.top = 0;
  this->rc.left = 0;
  this->rc.right = this->bkWndX;
  this->rc.bottom = bkWndY;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom) /* [ROWTABLE] */;
  pDebugTex = (gbTexture *)this->me_Role[2].m_RoleAttEqual[3].pDebugTex;
  *((_DWORD *)&this->mb_SortDefault + 1320) = arg0;
  v75[1] = 0;
  v75[0] = 0;
  v76 = 14;
  v77 = 600;
  ((void ( *)(gbTexture **, int, _DWORD *, MainEquipUI *))pDebugTex->IsLoaded)(
    &this->me_Role[2].m_RoleAttEqual[3].pDebugTex,
    4353,
    v75,
    this);
  LOBYTE(v5) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttEqual[3].pDebugTex))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\smt_Line.tga", v5);
  v6 = (gbTexture *)this->me_Role[2].m_RoleAttEqual[4].pDebugTex;
  v75[0] = 786;
  v76 = 800;
  ((void ( *)(gbTexture **, int, _DWORD *, MainEquipUI *))v6->IsLoaded)(
    &this->me_Role[2].m_RoleAttEqual[4].pDebugTex,
    4353,
    v75,
    this);
  LOBYTE(v7) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttEqual[4].pDebugTex))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\smt_Line.tga", v7);
  m_ppicInfo = (_PlugInfo *)this->me_Role[2].m_RoleAttCng[2].m_ppicInfo;
  v90[1] = 565;
  v90[0] = 0;
  v90[2] = 800;
  v90[3] = 600;
  (*(void ( **)(_PlugInfo **, int, _DWORD *, char *, _DWORD, MainEquipUI *))&m_ppicInfo->name[24])(
    &this->me_Role[2].m_RoleAttCng[2].m_ppicInfo,
    4353,
    (_DWORD *)(v90),
    "UI\\Flex\\framebar.tga",
    0,
    this);
  (((CScreenMode *)&this->me_Role[2].m_RoleAttCng[2].m_ppicInfo))->CScreenMode::SetPosition(30,   35);
  v9 = this->bkWndY;
  this->rc.top = 0;
  this->rc.left = 0;
  v10 = this->rc.top + v9;
  this->rc.right = this->bkWndX;
  this->rc.bottom = v10;
  m_bvisible = this->me_Role[2].m_RoleAttCng[3].m_bvisible;
  v86[1] = 6;
  v86[0] = 220;
  v86[2] = 348;
  v86[3] = 134;
  (*(void ( **)(int *, int, _DWORD *, MainEquipUI *))(m_bvisible + 16))(
    &this->me_Role[2].m_RoleAttCng[3].m_bvisible,
    4353,
    (_DWORD *)(v86),
    this);
  LOBYTE(v12) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttCng[3].m_bvisible))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Smelting\\smt_Flag.tga", v12);
  v13 = (gbTexture *)this->me_Role[2].m_RoleAttCng[9].pDebugTex;
  v53 = 132;
  v52 = 80;
  v54 = 312;
  v55 = 546;
  ((void ( *)(gbTexture **, int, int *, MainEquipUI *))v13->IsLoaded)(
    &this->me_Role[2].m_RoleAttCng[9].pDebugTex,
    4353,
    &v52,
    this);
  LOBYTE(v14) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttCng[9].pDebugTex))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Info.tga", v14);
  v15 = (gbTexture *)this->me_Role[2].m_RoleAttEqual[0].pDebugTex;
  v53 = 380;
  v52 = 92;
  v54 = 312;
  v55 = 508;
  ((void ( *)(gbTexture **, int, int *, MainEquipUI *))v15->IsLoaded)(
    &this->me_Role[2].m_RoleAttEqual[0].pDebugTex,
    4353,
    &v52,
    this);
  (((UIScene *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex))->UIScene::SetShow(0);
  v16 = (gbTexture *)this->me_Role[2].m_RoleAttEqual[1].pDebugTex;
  v53 = 510;
  v52 = 92;
  v54 = 312;
  v55 = 542;
  ((void ( *)(gbTexture **, int, int *, MainEquipUI *))v16->IsLoaded)(
    &this->me_Role[2].m_RoleAttEqual[1].pDebugTex,
    4353,
    &v52,
    this);
  (((UIScene *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex))->UIScene::SetShow(0);
  v17 = (gbTexture *)this->me_Role[2].m_RoleAttEqual[2].pDebugTex;
  v53 = 150;
  v52 = 265;
  v54 = 281;
  v55 = 182;
  ((void ( *)(gbTexture **, int, int *, MainEquipUI *))v17->IsLoaded)(
    &this->me_Role[2].m_RoleAttEqual[2].pDebugTex,
    4353,
    &v52,
    this);
  LOBYTE(v18) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttEqual[2].pDebugTex))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Smelt_word.tga", v18);
  v19 = this->me_Role[2].m_RoleAttCng[4].m_bvisible;
  *((_DWORD *)&this->mb_SortDefault + 1317) = 168;
  *((_DWORD *)&this->mb_SortDefault + 1316) = 168;
  *((_DWORD *)&this->mb_SortDefault + 1318) = 268;
  *((_DWORD *)&this->mb_SortDefault + 1319) = 328;
  v57 = 426;
  v56 = 368;
  v58 = 398;
  v59 = 545;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v19 + 16))(
    &this->me_Role[2].m_RoleAttCng[4].m_bvisible,
    4353,
    &v56,
    this);
  LOBYTE(v20) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttCng[4].m_bvisible))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameLS.tga", v20);
  v21 = this->me_Role[2].m_RoleAttCng[5].m_bvisible;
  v56 = v58;
  v58 += 256;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v21 + 16))(
    &this->me_Role[2].m_RoleAttCng[5].m_bvisible,
    4353,
    &v56,
    this);
  LOBYTE(v22) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttCng[5].m_bvisible))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\PropTopFrame\\TopFrameRM.tga", v22);
  v23 = this->me_Role[2].m_RoleAttCng[6].m_bvisible;
  v56 = v58;
  v58 += 32;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v23 + 16))(
    &this->me_Role[2].m_RoleAttCng[6].m_bvisible,
    4353,
    &v56,
    this);
  LOBYTE(v24) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_RoleAttCng[6].m_bvisible))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameR.tga", v24);
  v25 = this->me_Role[2].m_RoleAttCng[7].m_bvisible;
  v57 = 428;
  v56 = 395;
  v58 = 677;
  v59 = 556;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v25 + 16))(
    &this->me_Role[2].m_RoleAttCng[7].m_bvisible,
    4374,
    &v56,
    this);
  (((UIScene *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible))->UIScene::SetShow(0);
  AllocObject(&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
  v26 = this->me_Role[2].m_RoleAttCng[8].m_bvisible;
  v87[1] = v59 - 46;
  v87[0] = v58 - 40;
  v87[3] = v59 - 46 + 32;
  v87[2] = v58 - 40 + 24;
  this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
  (*(void ( **)(int *, int, _DWORD *, MainEquipUI *))(v26 + 16))(
    &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
    2,
    (_DWORD *)(v87),
    this);
  (((UIScene *)&this->me_Role[2].m_RoleAttCng[8].m_bvisible))->UIScene::LoadResource("ui\\scene\\page");
  UIScene_SetController(0x40000000);
  (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
    &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
    0);
  v27 = (gbTexture *)this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11];
  v83 = 20;
  v82 = 342;
  v84 = 715;
  v85 = 414;
  v28 = ((int ( *)(gbTexture **, int, int *, MainEquipUI *))v27->IsLoaded)(
          &this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11],
          4371,
          &v82,
          this);
  LOBYTE(v28) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
  (((UIPushButton *)&this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\ListFrame.tga", v28);
  a2[0] = v82 + 18;
  a2[1] = v83 + 16;
  v61 = v82 + 126;
  v62 = v83 + 48;
  v29 = (UIScene *)&this->me_Role[2].m_EquipCloth.m_caption[100];
  v51 = 4;
  do
  {
    (*(void ( **)(UIScene *, int, _DWORD *, MainEquipUI *))(*(_DWORD *)((UIWnd *)v29) + 16))(v29, 4371, (_DWORD *)(a2), this);
    (((UIScene *)v29))->UIScene::SetShow(0);
    v29 = (UIScene *)((char *)v29 + 152);
    --v51;
  }
  while ( v51 );
  SetEnable((UICaption *)&this->me_Role[2].m_EquipCloth.m_caption[100]);
  a2[0] = v61;
  v61 += 64;
  (((UIWnd *)&this->me_Role[2].m_EquipShoes.m_texarray.m_ptex[1]))->UIWnd::sub_445FA0(a2);
  SetEnable((UICaption *)&this->me_Role[2].m_EquipShoes.m_texarray.m_ptex[1]);
  a2[0] = v61 - 26;
  v61 = v61 - 26 + 108;
  (((UIWnd *)&this->me_Role[2].m_EquipShoes.m_caption[60]))->UIWnd::sub_445FA0(a2);
  SetEnable((UICaption *)&this->me_Role[2].m_EquipShoes.m_caption[60]);
  a2[0] = v61;
  v61 += 64;
  (((UIWnd *)&this->me_Role[2].m_EquipAdorn1.m_benable))->UIWnd::sub_445FA0(a2);
  SetEnable((UICaption *)&this->me_Role[2].m_EquipAdorn1.m_benable);
  v30 = 667;
  LODWORD(pPos.z) = 689;
  LODWORD(pDir.z) = 689;
  v31 = *((_DWORD *)&this->mb_SortDefault + 1320);
  v32 = *(_DWORD *)&this->me_Role[2].m_EquipAdorn1.m_caption[20];
  v68 = 68;
  p_DWORD = 362;
  nHeight = 698;
  v70 = 368;
  LODWORD(pPos.y) = 83;
  LODWORD(pPos.x) = 667;
  v92 = 109;
  LODWORD(pDir.y) = 326;
  LODWORD(pDir.x) = 667;
  v89 = 352;
  LOBYTE(v30) = *(_BYTE *)(v31 + 4000);
  (*(void ( **)(char *, int, int *, MainEquipUI *, _DWORD, int, int))(v32 + 28))(
    &this->me_Role[2].m_EquipAdorn1.m_caption[20],
    4359,
    &p_DWORD,
    this,
    0,
    1,
    v30);
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", 0);
  this->me_Role[3].m_Jing.m_childs.m_pData = (char *)-8;
  this->me_Role[3].m_Jing.m_childs.capacity = -8;
  this->me_Role[3].m_Jing.m_childs.m_nSize = 14;
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100]))->CCBUI::ShowEffect(v68 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100]))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100]))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100]))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetLockSel(29);
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetColumnHead((int)"Bone", 111);
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetColumnHead((int)"Smelt", 111);
  (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100]))->CCBUI::VirtualCall(1);
  v78 = p_DWORD;
  v80 = p_DWORD + 333;
  v79 = v68 + 2;
  v81 = v68 + 31;
  p_pDebugTex = (gbTexture **)&this->me_Role[2].m_RoleAttEqual[6].pDebugTex;
  v34 = 10;
  do
  {
    v35 = ((int ( *)(gbTexture **, int, int *, MainEquipUI *))(*p_pDebugTex)->IsLoaded)(
            p_pDebugTex,
            4371,
            &v78,
            this);
    LOBYTE(v35) = *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000);
    (((UIPushButton *)p_pDebugTex))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Smelting\\List_Grid.tga", v35);
    p_pDebugTex += 38;
    v79 = v81;
    --v34;
    v81 += 29;
  }
  while ( v34 );
  v37 = *((_DWORD *)&this->mb_SortDefault + 1320);
  m_textx = (void ( **)(void **, int, int *, MainEquipUI *, char *, _DWORD, int))this->me_Role[3].m_Jing.m_textx;
  v64 = 570;
  v63 = 206;
  v65 = 298;
  v66 = 596;
  LOBYTE(v36) = *(_BYTE *)(v37 + 4000);
  m_textx[7](&this->me_Role[3].m_Jing.m_textx, 4372, &v63, this, "UI\\GameMainUI\\MUIDialog\\Normal\\Yes", 0, v36);
  (((PalScript *)&this->me_Role[3].m_Jing.m_textx))->PalScript::OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnYes.tga", *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000));
  v39 = v65;
  v40 = *((_DWORD *)&this->mb_SortDefault + 1320);
  v63 = v65 + 204;
  v65 += 296;
  LOBYTE(v39) = *(_BYTE *)(v40 + 4000);
  ((void ( *)(UIWnd **, int, int *, MainEquipUI *, char *, _DWORD, int))this->me_Role[3].m_JingVal.m_pfather->m_rect.bottom)(
    &this->me_Role[3].m_JingVal.m_pfather,
    4373,
    &v63,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v39);
  (((PalScript *)&this->me_Role[3].m_JingVal.m_pfather))->PalScript::OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnNo.tga", *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000));
  v41 = *((_DWORD *)&this->mb_SortDefault + 1320);
  left = this->me_Role[3].m_ShenBar.m_decorateRc.left;
  v64 = 549;
  v63 = 762;
  v65 = 800;
  v66 = 597;
  LOBYTE(v43) = *(_BYTE *)(v41 + 4000);
  (*(void ( **)(tagRECT *, int, int *, MainEquipUI *, char *, _DWORD, int))(left + 28))(
    &this->me_Role[3].m_ShenBar.m_decorateRc,
    4354,
    &v63,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    0,
    v43);
  (((PalScript *)&this->me_Role[3].m_ShenBar.m_decorateRc))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnExit.tga", *(_BYTE *)(*((_DWORD *)&this->mb_SortDefault + 1320) + 4000));
  (((CCBFiveNimbusWindow *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&g_PlayerAttBuffer2._todo_074[118], (int)this);
  this->me_Role[3].m_RoleAttEqual[2].m_fontcolor.Color = 0;
  this->me_Role[3].m_RoleAttEqual[1].m_nTextW = 1;
  (((CCBFiveNimbusWindow *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh))->CCBFiveNimbusWindow::SetFloatParam(210.0);
  (((Camera *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh))->Camera::UpdateCameraLookAt(198, 264, 600);
  sub_43A090((int)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh, 1, 0.0);
  v71 = 300;
  v74 = 300;
  v72 = 200;
  v73 = 500;
  Create__ovl_1((ARC_PlayerAtt *)&this->me_Role[3].m_Qi.m_rect.top);
  (((UIItem *)&this->me_Role[3].m_Qi.m_rect.top))->UIItem::SetData(31);
  v44 = *(_DWORD *)&this->me_Role[3].m_Qi.m_text[4];
  this->me_Role[3].m_Qi.m_ppic = (gbTexture *)(*(_DWORD *)&this->me_Role[3].m_Qi.m_text[8] + 14);
  v45 = *(_DWORD *)&this->me_Role[3].m_Qi.m_text[12];
  this->me_Role[3].m_Qi.m_pbkInfo = (_PlugInfo *)(v44 + 8);
  v46 = (gbTexture *)((char *)this->me_Role[3].m_Qi.m_pbk - 38);
  this->me_Role[3].m_Qi.m_ppicInfo = (_PlugInfo *)(v45 - 6);
  this->me_Role[3].m_RoleAtt[3].m_bvisible = 2;
  this->me_Role[3].m_RoleAtt[3].m_benable = 8;
  this->me_Role[3].m_Qi.m_disablepic = v46;
  (((UIWnd *)&this->me_Role[3].m_QiVal.m_ratioh))->UIWnd::sub_445FA0(&this->me_Role[3].m_Qi.m_pbkInfo);
  Create__ovl_1((ARC_PlayerAtt *)&this->me_Role[3].m_RoleAtt[3].m_ratioh);
  (((UIItem *)&this->me_Role[3].m_RoleAtt[3].m_ratioh))->UIItem::SetData(31);
  Color = this->me_Role[3].m_RoleAtt[4].m_wndcolor.Color;
  this->me_Role[3].m_RoleAtt[4].m_rect.bottom = this->me_Role[3].m_RoleAtt[4].m_id + 14;
  v48 = (UIWnd *)(this->me_Role[3].m_RoleAtt[4].m_rect.left - 6);
  this->me_Role[3].m_RoleAtt[4].m_rect.right = Color + 8;
  top = this->me_Role[3].m_RoleAtt[4].m_rect.top;
  this->me_Role[3].m_RoleAttCng[2].m_bvisible = 2;
  this->me_Role[3].m_RoleAttCng[2].m_benable = 8;
  this->me_Role[3].m_RoleAtt[4].m_pfather = v48;
  this->me_Role[3].m_RoleAtt[4].m_childs.m_pData = (char *)(top - 38);
  (((UIWnd *)&this->me_Role[3].m_RoleAtt[6].m_ratioh))->UIWnd::sub_445FA0(&this->me_Role[3].m_RoleAtt[4].m_rect.right);
  v73 += 100;
  v74 += 100;
  Create__ovl_1((ARC_PlayerAtt *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh);
  (((UIItem *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh))->UIItem::SetData(31);
  this->MainEquipUI::ValidateRoles();
  this->me_Role[3].m_RoleAttEqual[3].m_FVF = 0;
  this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)-1;
  return result;
}

// 0x0047A580
void MainEquipUI::ValidateRoles()
{
  unsigned int v2; // esi
  _DWORD *v3; // eax
  char *v4; // edx
  int v5; // edx
  unsigned int v6; // esi
  int *v7; // eax
  int *v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  _PlugInfo **v14; // edx
  char *v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int ListItems; // edi
  int v22; // ecx
  int v23; // eax
  UIListBox *v24; // ebx
  _BYTE pOut[12]; // [esp+0x10] [ebp-0xC] BYREF

  memset(&this->m_IsMsg, 0, 0x4A4u);
  memset(&this->m_OutFrameL.m_childs.m_nSize, 0, 0x4A4u);
  memset(this->stp_Magic.m_texarrayInfo, 0, 0x4A4u);
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] = 0;
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(3);
  this->i = 0;
  v2 = 0;
  if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
  {
    do
    {
      v3 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v2);
      v4 = (char *)&this->buf[12 * this->i + 256];
      *(_DWORD *)v4 = (unsigned long)*v3;
      *((_DWORD *)v4 + 1) = (unsigned long)v3[1];
      *((_DWORD *)v4 + 2) = (unsigned long)v3[2];
      v5 = this->i + 1;
      ++*(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4];
      this->i = v5;
      v2 = v5;
    }
    while ( v5 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
  }
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(10);
  this->i = 0;
  v6 = 0;
  if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
  {
    do
    {
      v7 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v6);
      v8 = (int *)(&this->m_OutFrameL.m_childs.m_nSize + 3 * this->i);
      *v8 = *v7;
      v8[1] = (unsigned long)v7[1];
      v8[2] = (unsigned long)v7[2];
      v9 = this->i + 1;
      ++*(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8];
      this->i = v9;
      v6 = v9;
    }
    while ( v9 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
  }
  v10 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8];
  this->i = 0;
  if ( v10 > 0 )
  {
    do
    {
      v11 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4];
      this->j = 0;
      if ( v11 > 0 )
      {
        do
        {
          v12 = *(&this->m_OutFrameL.m_bcreateok + 3 * this->i);
          if ( *(_DWORD *)(v12 + 776) == *(_DWORD *)&this->buf[12 * this->j + 256] )
          {
            this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]] = *(_PlugInfo **)(v12 + 780);
            this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 2] = (_PlugInfo *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum((int)this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]]);
            this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 1] = (_PlugInfo *)1;
            *(&this->m_GameMoney.m_bcreateok + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = (int)this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]];
            lstrcpyA(
              (LPSTR)&this->stp_Effect.m_disablepicInfo + 796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12],
              this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 2]->name);
            *((_DWORD *)&this->m_DlgEx.m_static.m_pbkInfo + 199
                                                          * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = *(_DWORD *)&this->buf[12 * this->j + 256];
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 12] = *(_DWORD *)&this->m_Is[12 * this->j + 3];
            lstrcpyA(
              (LPSTR)&this->m_DlgEx.m_bk.m_childs.capacity
            + 796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12],
              (LPCSTR)(*(&this->m_SelNum + 3 * this->j) + 4));
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 16] = *(&this->m_OutFrameL.m_childs.m_nSize + 3 * this->i);
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 8] = *(&this->m_OutFrameL.m_childs.m_needscriptdel + 3 * this->i);
            lstrcpyA(
              (LPSTR)&this->m_GameMoney.m_bvisible + 796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12],
              (LPCSTR)(*(&this->m_OutFrameL.m_bcreateok + 3 * this->i) + 4));
            *((_DWORD *)&this->m_DlgEx.m_static.m_ppic + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = this->i;
            *((_DWORD *)&this->m_DlgEx.m_static.m_ppicInfo
            + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = this->j;
            qmemcpy(
              &this->m_btnPar2[2][4]._texName[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 80],
              &this->stp_Effect.m_disablepicInfo + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12],
              0x31Cu);
            v13 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
            v14 = (_PlugInfo **)&this->stp_Magic.m_texarrayInfo[3 * v13];
            v15 = (char *)&this->stp_BattleArray.m_caption[12 * v13 + 128];
            *(_DWORD *)v15 = (unsigned long)*v14;
            *((_DWORD *)v15 + 1) = (unsigned long)v14[1];
            *((_DWORD *)v15 + 2) = (unsigned long)v14[2];
            ++*(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
          }
          v16 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4];
          v17 = this->j + 1;
          this->j = v17;
        }
        while ( v17 < v16 );
      }
      v18 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8];
      v19 = this->i + 1;
      this->i = v19;
    }
    while ( v19 < v18 );
  }
  if ( *(int *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] <= 0 )
  {
    this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)5;
    SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
    (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
      &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
      1);
  }
  v20 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
  this->i = 0;
  if ( v20 > 0 )
  {
    do
    {
      ListItems = (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::LoadListItems((char *)&this->m_GameMoney.m_bvisible + 796 * this->i, 0);
      sprintf(this->buf, (const char *)&dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 8]);
      (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetMouseMoveSel(1, ListItems, this->buf, 0);
      sprintf(this->buf, "%s", &this->m_DlgEx.m_bk.m_childs.capacity + 199 * this->i);
      (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetMouseMoveSel(2, ListItems, this->buf, 0);
      sprintf(this->buf, (const char *)&dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 12]);
      (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::SetMouseMoveSel(3, ListItems, this->buf, 0);
      v22 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
      v23 = this->i + 1;
      this->i = v23;
    }
    while ( v23 < v22 );
  }
  (((LineupUI *)this))->LineupUI::CountVisibleItems(0) /* [ROWTABLE] */;
  v24 = (UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20];
  (((UIListBox *)v24))->UIListBox::GetItem();
  (((UIListBox *)v24))->UIListBox::GetItem();
}

// 0x0047B140
void MainEquipUI::FormatItemPath(int nVal)
{
  char *buf; // ebx
  CHAR *v4; // ebp
  RoleAtt *v5; // ecx
  LPCSTR v6; // eax
  CHAR String1[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v8; // [esp+0x10D] [ebp-0x3]
  char v9; // [esp+0x10F] [ebp-0x1]

  buf = this->buf;
  sprintf(this->buf, unk_C10D38);
  memset(String1, 0, sizeof(String1));
  v8 = 0;
  v9 = 0;
  v4 = (CHAR *)sub_458F70(&this->stp_Magic.m_texarrayInfo[3 * nVal + 2]->name[92], (int)asc_5B74B8, String1);
  if ( lstrlenA((const char *)v4) <= 0 )
  {
    (((RoleAtt *)v5))->RoleAtt::FormatAttributeText();
    lstrcatA(buf, v6);
  }
  else
  {
    lstrcpyA(buf, v4);
  }
  SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex);
  SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex);
}

// 0x0047B200
void MainEquipUI::Render()
{
  UIParticle *p_m_nTextW; // esi
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  int fYb; // [esp+0x4] [ebp-0x20]
  CCBMagicWindow *v15; // [esp+0x14] [ebp-0x10]
  int v16; // [esp+0x18] [ebp-0xC]
  int v17; // [esp+0x1C] [ebp-0x8]
  int v18; // [esp+0x20] [ebp-0x4]

  (((CCBControlWindow *)this))->CCBControlWindow::Render(v15) /* [ROWTABLE] */;
  if ( this->me_Role[3].m_RoleAttEqual[3].m_mouseoff )
  {
    p_m_nTextW = (UIParticle *)&this->me_Role[3].m_RoleAttEqual[3].m_nTextW;
    v16 = 60;
    do
    {
      if ( IsVisible((RenderTarget *)p_m_nTextW) )
      {
        (((UIParticle *)p_m_nTextW))->UIParticle::Apply(12);
      }
      else
      {
        v3 = *((_DWORD *)&this->mb_SortDefault + 1316);
        v4 = *((_DWORD *)&this->mb_SortDefault + 1318) - v3;
        v5 = rand();
        v17 = *((_DWORD *)&this->mb_SortDefault + 1317);
        v18 = v3 + v5 % (v4 / 2);
        v6 = *((_DWORD *)&this->mb_SortDefault + 1319) - v17;
        (((RenderTarget *)p_m_nTextW))->RenderTarget::LoadTexture(szFilename);
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetSize(32);
        fY = rand() % 10 + 252;
        fX = rand() % 10 + 36;
        v7 = rand();
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetColor(v7 % 10 - 37, fX, fY);
        v8 = rand();
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetAlpha(v8 % 135 + 120);
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetField084(1070386381);
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetState(1061997773);
        fYa = (float)v17;
        fXa = (float)v18;
        (((RenderTarget *)p_m_nTextW))->RenderTarget::UpdateTransform(fXa, fYa);
        (((RenderTarget *)p_m_nTextW))->RenderTarget::CalcRenderDimensions(v4, v6);
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetOffset(10.0, 2.0);
        *(float *)&fYb = (float)(rand() % 8 + 2);
        *(float *)&fXb = (float)(rand() % 8 + 2);
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetScale(fXb, fYb);
        (((RenderTarget *)p_m_nTextW))->RenderTarget::SetVisible(1);
      }
      ++p_m_nTextW;
      --v16;
    }
    while ( v16 );
  }
}

// 0x0047B3B0
BOOL MainEquipUI::Render3DModel()
{
  void *TickCount; // eax
  _BYTE *v3; // eax
  unsigned int v4; // ecx
  const char *v5; // ebp
  _PlugInfo *v6; // eax
  const char *v7; // ebp
  int m_align; // ecx
  char *v9; // eax
  UICursor *v10; // ecx
  const char *v12; // [esp+0x8] [ebp-0x104]
  char Buffer[253]; // [esp+0xC] [ebp-0x100] BYREF
  __int16 v14; // [esp+0x109] [ebp-0x3]
  char v15; // [esp+0x10B] [ebp-0x1]
  int a2; // [esp+0x110] [ebp+0x4]
  int a3; // [esp+0x114] [ebp+0x8]

  if ( this->me_Role[3].m_RoleAttEqual[3].m_mouseoff )
  {
    if ( !LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) )
    {
      TickCount = (void *)GetTickCount();
      this->me_Role[3].m_RoleAttEqual[3].m_textx = TickCount;
      this->me_Role[3].m_RoleAttEqual[3].m_texty = TickCount;
      LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) = 1;
    }
    v3 = (_BYTE *)GetTickCount();
    v4 = (unsigned int)v3 - (char *)this->me_Role[3].m_RoleAttEqual[3].m_texty;
    this->me_Role[3].m_RoleAttEqual[3].m_textx = v3;
    if ( v4 > 0x1388 )
    {
      this->me_Role[3].m_RoleAttEqual[3].m_texty = v3;
      LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) = 0;
      this->MainEquipUI::FormatItemPath((int)this->me_Role[2].m_RoleAttCng[2].m_pbk);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive((int *)this + 3 * (int)&this->me_Role[2].m_RoleAttCng[2].m_pbk[2].InFmt.a_mask);
      if ( !strcmp(
              &this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2]->name[32],
              unk_C10D38) )
      {
        sprintf(this->buf, "%s", "NONE");
      }
      else
      {
        v5 = (const char *)&this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2]->name[32];
        sprintf(this->buf, "Item\\%s\\%s.pol", v5, v5);
      }
      (((PalScript *)&this->me_Role[3].m_RoleAttEqual[2]))->PalScript::LoadModel(this->buf, 0);
      v6 = this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2];
      v7 = (const char *)&v6->name[32];
      v12 = (const char *)&v6->name[62];
      if ( !strcmp(&v6->name[32], unk_C10D38) )
      {
        sprintf(this->buf, "%s", "NONE");
      }
      else
      {
        memset(Buffer, 0, sizeof(Buffer));
        v14 = 0;
        v15 = 0;
        sprintf(Buffer, "%s%s", v7, v12);
        sprintf(this->buf, "Item\\%s\\%s.tga", v7, Buffer);
      }
      (((gbGeomNode *)this->me_Role[3].m_RoleAttEqual[2].m_rect.left))->gbGeomNode::ReplaceTexture(this->buf);
      m_align = this->me_Role[2].m_RoleAttCng[2].m_align;
      v9 = (char *)this->me_Role[2].m_RoleAttCng[2].m_textx + 4;
      this->me_Role[3].m_RoleAttEqual[2].m_fontcolor.Color = 1;
      sprintf(
        this->buf,
        (const char *)&szFilename[36],
        byte_DCD03C,
        this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2]->name,
        byte_DCD13C,
        m_align + 4,
        v9);
      SetEnable((UICaption *)&this->me_Role[3].m_RoleAttCng[5].m_ratioh);
      (((UIRoleSelect *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh))->UIRoleSelect::SetByte(1);
      SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
      (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
        &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
        1);
      this->me_Role[2].m_RoleAttCng[2].m_ppic = ((gbTexture *)0);
      this->me_Role[2].m_RoleAttCng[2].m_bfocus = 0;
      this->me_Role[2].m_RoleAttCng[2].pDebugTex = ((gbTexture *)0);
      this->me_Role[2].m_RoleAttCng[2].m_align = 0;
      this->me_Role[2].m_RoleAttCng[2].m_ratiow = 0.0f;
      this->me_Role[2].m_RoleAttCng[2].m_ratioh = 0.0f;
      this->me_Role[2].m_RoleAttCng[2].m_textx = ((void *)0);
      (((LineupUI *)this))->LineupUI::CountVisibleItems((int)this->me_Role[2].m_RoleAttCng[2].m_pbk) /* [ROWTABLE] */;
      sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
      sub_445E50((int)&this->me_Role[3].m_Jing.m_textx);
      sub_445E50((int)&this->me_Role[3].m_JingVal.m_pfather);
      sub_445E50((int)&this->me_Role[3].m_ShenBar.m_decorateRc);
      (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::GetItem();
      *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) = 1;
      this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 0;
      this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)-1;
      (((UICursor *)v10))->UICursor::_todo_541CC0();
    }
  }
  return (((SceneObj *)this))->SceneObj::Update(a2, a3) /* [ROWTABLE] */;
}

// 0x0047B6C0
int MainEquipUI::OnMessage(int nVal, int nVal2, int nVal3)
{
  int result; // eax
  CScreenMode *Instance; // eax
  gbTexture *LockedSel; // eax
  gbTexture *v8; // eax
  CScreenMode *v9; // eax
  CScreenMode *v10; // eax
  CScreenMode *v11; // eax
  const char *v12; // [esp-0x8] [ebp-0x10]
  const char *v13; // [esp-0x8] [ebp-0x10]
  const void *v14; // [esp-0x8] [ebp-0x10]
  const void *v15; // [esp-0x8] [ebp-0x10]
  int v16; // [esp+0x0] [ebp-0x8]

  switch ( nVal )
  {
    case 1000:
      if ( !nVal2 || this->me_Role[2].m_RoleAttCng[2].m_ppic == (gbTexture *)5 )
        return 1;
      this->me_Role[2].m_RoleAttCng[2].m_ppic = ((gbTexture *)0);
      SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
      (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
        &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
        1);
      return 1;
    case 1001:
      if ( nVal2 == 4354 )
      {
        if ( this->me_Role[2].m_RoleAttCng[2].m_ppic == (gbTexture *)3 )
        {
          SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex);
          SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex);
          sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
          (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::GetItem();
          PAL3_DispatchModeCommand(0);
        }
        else
        {
          this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)3;
          SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
          (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
            &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
            1);
        }
        v13 = (const char *)off_5BC90C;
        goto LABEL_24;
      }
      if ( nVal2 == 4372 )
      {
        if ( *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) )
        {
          LockedSel = (gbTexture *)(((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::GetLockedSel();
          this->me_Role[2].m_RoleAttCng[2].m_pbk = LockedSel;
          if ( (int)LockedSel >= 0 )
          {
            MainEquipUI_UpdateLayout((int)LockedSel);
            SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
            (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
              &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
              1);
            this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)1;
            v13 = (const char *)off_5BC90C;
          }
          else
          {
            v13 = g_pCScreenMode_5BC918;
          }
        }
        else
        {
          v13 = g_pCScreenMode_5BC918;
        }
        goto LABEL_24;
      }
      if ( nVal2 != 4373 )
        return 1;
      if ( !*(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) )
        goto LABEL_23;
      MainEquipUI_UpdateCompareLayout((int)this->me_Role[2].m_RoleAttCng[2].m_pbk);
      v12 = (const char *)off_5BC90C;
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v12, 1);
      SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
      (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
        &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
        1);
      this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)2;
      return 1;
    case 1008:
      if ( nVal2 == 4359 )
      {
        if ( *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) )
        {
          v8 = (gbTexture *)(((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::GetLockedSel();
          this->me_Role[2].m_RoleAttCng[2].m_pbk = v8;
          if ( (int)v8 >= 0 )
          {
            MainEquipUI_UpdateLayout((int)v8);
            v14 = (const void *)off_5BC914;
            v9 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v9))->CScreenMode::AudioSetPosition(v14, 1);
            SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
            (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
              &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
              1);
            this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)1;
            return 1;
          }
        }
LABEL_23:
        v13 = g_pCScreenMode_5BC918;
LABEL_24:
        v10 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v10))->CScreenMode::AudioSetPosition(v13, 1);
      }
      return 1;
    case 1009:
      if ( nVal2 == 4359 )
      {
        this->me_Role[3].m_RoleAttEqual[2].m_fontcolor.Color = 0;
        this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)(((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::CreateChild();
        SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex);
        SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex);
        SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
        (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
          &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
          0);
        if ( (int)this->me_Role[2].m_RoleAttCng[2].m_pbk >= 0 )
          this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 0;
        this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
        return 1;
      }
      if ( nVal2 != 4374 )
        return 1;
      switch ( (unsigned int)this->me_Role[2].m_RoleAttCng[2].m_ppic )
      {
        case 0u:
        case 2u:
          this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
          SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
          (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
            &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
            0);
          result = 1;
          break;
        case 1u:
          this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
          SetEnable((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
          (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
            &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
            0);
          RenderTarget_InitParticleRenders(v16);
          sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
          sub_445E50((int)&this->me_Role[3].m_Jing.m_textx);
          sub_445E50((int)&this->me_Role[3].m_JingVal.m_pfather);
          sub_445E50((int)&this->me_Role[3].m_ShenBar.m_decorateRc);
          this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 1;
          v15 = (const void *)off_5BC940;
          v11 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v11))->CScreenMode::AudioSetPosition(v15, 1);
          result = 1;
          break;
        case 3u:
          SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex);
          SetEnable((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex);
          sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
          (((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20]))->UIListBox::GetItem();
          PAL3_DispatchModeCommand(0);
          result = 1;
          break;
        default:
          return 1;
      }
      return result;
    default:
      return this->UIWnd::OnMessage(nVal, nVal2, nVal3);
  }
}

// 0x0047EC00
// write access to const memory has been detected, the output may be wrong!
int MainEquipUI::ClearState()
{
  int result; // eax

  this->me_Role[2].m_Qi.m_fontcolor.Color = 0;
  this->me_Role[2].m_Qi.m_wndcolor.Color = 0;
  memset(&this->me_Role[2].m_Qi.m_id, 0, 0x18u);
  memset(&this->me_Role[2].m_Qi.m_childs, 0, 0x960u);
  this->me_Role[2].m_RoleAttCng[0].m_ratiow = 0.0f;
  this->me_Role[2].m_RoleAttCng[0].m_align = 0;
  this->me_Role[2].m_RoleAttCng[0].m_bfocus = 0;
  this->me_Role[2].m_RoleAttCng[0].pDebugTex = ((gbTexture *)0);
  LOBYTE(this->me_Role[2].m_RoleAttCng[1].m_FVF) = 0;
  BYTE1(this->me_Role[2].m_RoleAttCng[1].m_FVF) = 0;
  this->me_Role[2].m_RoleAttCng[1].m_nTextW = -1;
  *(_DWORD *)((UIWnd *)&this->me_Role[2].m_RoleAttCng[2]) = 0;
  memset32(&this->me_Role[2].m_RoleAttCng[1].m_ppic, (int)&byte_1010101, 6u);
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  result = gbColorQuad::ColorQuadFmt;
  gbColorQuad::ColorQuadFmt = 1;
  BYTE2(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  BYTE1(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  HIBYTE(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  return result;
}

// 0x00480530
int * MainEquipUI::UpdateFadeAlpha(float fVal)
{
  float v3; // st7
  int *p_m_bcreateok; // ebx
  int v5; // ebp
  char *v6; // ebx
  int v7; // ebp

  v3 = fVal * 120.0f + *(float *)&this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color;
  *(float *)&this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = v3;
  if ( v3 >= 255.0f )
  {
    this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 1132396544;
    LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  }
  HIBYTE(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = (__int64)*(float *)&this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color;
  AllocObject(&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok);
  AllocObject(&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok);
  AllocObject(&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok);
  p_m_bcreateok = (int *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v5 = 5;
  do
  {
    AllocObject(p_m_bcreateok + 190);
    AllocObject(p_m_bcreateok);
    p_m_bcreateok += 38;
    --v5;
  }
  while ( v5 );
  v6 = (char *)&this->me_Role[1].m_EquipHat.m_caption[124];
  v7 = 4;
  do
  {
    AllocObject(v6);
    v6 += 152;
    --v7;
  }
  while ( v7 );
  return (int *)AllocObject(&this->me_Role[1].m_EquipShoes.m_caption[108]);
}

// 0x00481BA0
unsigned __int8 MainEquipUI::SetAdornVisible(unsigned __int8 pData)
{
  int *p_m_bcreateok; // ebp
  int v4; // ebx
  int *v5; // ebp
  int v6; // ebx
  char *v7; // ebp
  int v8; // ebx
  unsigned __int8 result; // al

  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn1.m_caption[68])((char *)(&this->me_Role[1].m_EquipAdorn1.m_caption[68]), (_DWORD)(pData));
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn2.m_caption[68])((char *)(&this->me_Role[1].m_EquipAdorn2.m_caption[68]), (_DWORD)(pData));
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    pData);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    pData);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    pData);
  p_m_bcreateok = (int *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v4 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_bcreateok)(p_m_bcreateok, pData);
    p_m_bcreateok += 38;
    --v4;
  }
  while ( v4 );
  v5 = (int *)&this->me_Role[1].m_EquipPic.m_bcreateok;
  v6 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*v5)(v5, pData);
    v5 += 38;
    --v6;
  }
  while ( v6 );
  v7 = (char *)&this->me_Role[1].m_EquipHat.m_caption[124];
  v8 = 4;
  do
  {
    (**(void ( ***)(char *, _DWORD))v7)((char *)(v7), (_DWORD)(pData));
    v7 += 152;
    --v8;
  }
  while ( v8 );
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipShoes.m_caption[108])((char *)(&this->me_Role[1].m_EquipShoes.m_caption[108]), (_DWORD)(pData));
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]))(
    &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
    pData);
  if ( *((int *)&this->me_Role[2].m_Qi.m_id + (int)this->me_Role[2].m_RoleAttCng[0].pDebugTex) > 0 )
    this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = (_PlugInfo *)pData;
  else
    this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = ((_PlugInfo *)0);
  result = pData;
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = pData;
  if ( !pData )
    this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  return result;
}

// 0x00481CB0
void MainEquipUI::SelectWithSound(int nVal)
{
  int *p_m_bcreateok; // edi
  int v4; // ebp
  int *v5; // edi
  int v6; // ebp
  char *v7; // edi
  int v8; // ebp
  CScreenMode *Instance; // eax
  const void *v10; // [esp+0x18] [ebp-0x10]

  this->me_Role[2].m_Head.m_alignmode = 0;
  LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 0;
  this->me_Role[2].m_Name.m_fonttype = ((Parent_Data *)0);
  LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 0;
  this->me_Role[2].m_JingBar.m_childs.m_pData = ((char *)0);
  LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 0;
  this->me_Role[2].m_JingVal.m_childs.capacity = 0;
  LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 0;
  this->me_Role[2].m_Shen.m_pbk2 = ((gbTexture *)0);
  LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 0;
  *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 0;
  LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 0;
  switch ( nVal )
  {
    case 0:
      this->me_Role[2].m_Head.m_alignmode = 1;
      LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 1;
      break;
    case 1:
      this->me_Role[2].m_Name.m_fonttype = (Parent_Data *)1;
      LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 1;
      break;
    case 2:
      this->me_Role[2].m_JingBar.m_childs.m_pData = (char *)1;
      LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 1;
      break;
    case 3:
      this->me_Role[2].m_JingVal.m_childs.capacity = 1;
      LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 1;
      break;
    case 4:
      this->me_Role[2].m_Shen.m_pbk2 = (gbTexture *)1;
      LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 1;
      break;
    case 5:
      *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 1;
      LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 1;
      break;
    default:
      break;
  }
  (((gbVisNode *)this->me_Role[1].m_RoleAttCng[8].m_disablepicInfo))->gbVisNode::SetTimeScale(2.0);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn1.m_caption[68])((char *)(&this->me_Role[1].m_EquipAdorn1.m_caption[68]), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn2.m_caption[68])((char *)(&this->me_Role[1].m_EquipAdorn2.m_caption[68]), (_DWORD)(0));
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    0);
  p_m_bcreateok = (int *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v4 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_bcreateok)(p_m_bcreateok, 0);
    p_m_bcreateok += 38;
    --v4;
  }
  while ( v4 );
  v5 = (int *)&this->me_Role[1].m_EquipPic.m_bcreateok;
  v6 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*v5)(v5, 0);
    v5 += 38;
    --v6;
  }
  while ( v6 );
  v7 = (char *)&this->me_Role[1].m_EquipHat.m_caption[124];
  v8 = 4;
  do
  {
    (**(void ( ***)(char *, _DWORD))v7)((char *)(v7), (_DWORD)(0));
    v7 += 152;
    --v8;
  }
  while ( v8 );
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipShoes.m_caption[108])((char *)(&this->me_Role[1].m_EquipShoes.m_caption[108]), (_DWORD)(0));
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]))(
    &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
    0);
  this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = ((_PlugInfo *)0);
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  this->MainEquipUI::RenderEquipDetails(nVal);
  v10 = (const void *)off_5C3ED4;
  Instance = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v10, 1);
}

// 0x00481EB0
void MainEquipUI::ShowPanelsWithSound(int nVal, int nVal2)
{
  int *p_m_bcreateok; // edi
  int v5; // ebp
  int *v6; // edi
  int v7; // ebp
  char *v8; // edi
  int v9; // ebp
  CScreenMode *Instance; // eax
  const void *v11; // [esp-0x8] [ebp-0x10]
  int m_bfocus; // [esp-0x4] [ebp-0xC]

  this->me_Role[2].m_RoleAttCng[0].m_bfocus = nVal;
  this->me_Role[2].m_RoleAttCng[0].pDebugTex = (gbTexture *)nVal;
  this->me_Role[2].m_Head.m_alignmode = 0;
  LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 0;
  this->me_Role[2].m_Name.m_fonttype = ((Parent_Data *)0);
  LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 0;
  this->me_Role[2].m_JingBar.m_childs.m_pData = ((char *)0);
  LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 0;
  this->me_Role[2].m_JingVal.m_childs.capacity = 0;
  LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 0;
  this->me_Role[2].m_Shen.m_pbk2 = ((gbTexture *)0);
  LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 0;
  *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 0;
  LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 0;
  switch ( this->me_Role[2].m_RoleAttCng[0].m_bfocus )
  {
    case 0:
      this->me_Role[2].m_Head.m_alignmode = 1;
      LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 1;
      break;
    case 1:
      this->me_Role[2].m_Name.m_fonttype = (Parent_Data *)1;
      LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 1;
      break;
    case 2:
      this->me_Role[2].m_JingBar.m_childs.m_pData = (char *)1;
      LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 1;
      break;
    case 3:
      this->me_Role[2].m_JingVal.m_childs.capacity = 1;
      LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 1;
      break;
    case 4:
      this->me_Role[2].m_Shen.m_pbk2 = (gbTexture *)1;
      LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 1;
      break;
    case 5:
      *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 1;
      LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 1;
      break;
    default:
      break;
  }
  if ( nVal2 == 2 )
  {
    (((PalScript *)&this->me_Role[1].m_RoleAttCng[8].m_pbkInfo))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
    *(_DWORD *)((UIWnd *)&this->me_Role[2].m_RoleAttCng[2]) = 2;
    this->me_Role[2].m_RoleAttCng[1].m_nTextW = 1;
  }
  else if ( nVal2 == 1 )
  {
    (((PalScript *)&this->me_Role[1].m_RoleAttCng[8].m_pbkInfo))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
    *(_DWORD *)((UIWnd *)&this->me_Role[2].m_RoleAttCng[2]) = 1;
    this->me_Role[2].m_RoleAttCng[1].m_nTextW = 0;
  }
  (((StateUI *)this))->StateUI::ShowPanels(this->me_Role[2].m_RoleAttCng[0].m_bfocus, 0, (UIWnd *)this->me_Role[2].m_RoleAttCng[1].m_nTextW) /* [ROWTABLE] */;
  (((gbVisNode *)this->me_Role[1].m_RoleAttCng[8].m_disablepicInfo))->gbVisNode::SetTimeScale(2.0);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn1.m_caption[68])((char *)(&this->me_Role[1].m_EquipAdorn1.m_caption[68]), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn2.m_caption[68])((char *)(&this->me_Role[1].m_EquipAdorn2.m_caption[68]), (_DWORD)(0));
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    0);
  p_m_bcreateok = (int *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v5 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_bcreateok)(p_m_bcreateok, 0);
    p_m_bcreateok += 38;
    --v5;
  }
  while ( v5 );
  v6 = (int *)&this->me_Role[1].m_EquipPic.m_bcreateok;
  v7 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*v6)(v6, 0);
    v6 += 38;
    --v7;
  }
  while ( v7 );
  v8 = (char *)&this->me_Role[1].m_EquipHat.m_caption[124];
  v9 = 4;
  do
  {
    (**(void ( ***)(char *, _DWORD))v8)((char *)(v8), (_DWORD)(0));
    v8 += 152;
    --v9;
  }
  while ( v9 );
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipShoes.m_caption[108])((char *)(&this->me_Role[1].m_EquipShoes.m_caption[108]), (_DWORD)(0));
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]))(
    &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
    0);
  m_bfocus = this->me_Role[2].m_RoleAttCng[0].m_bfocus;
  this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = ((_PlugInfo *)0);
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  this->MainEquipUI::RenderEquipDetails(m_bfocus);
  BYTE1(this->me_Role[2].m_RoleAttCng[1].m_FVF) = 1;
  v11 = (const void *)off_5C3ED4;
  Instance = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v11, 1);
}

// 0x00482140
void MainEquipUI::RenderEquipDetails(int arg0)
{
  int v3; // ebx
  int *v4; // esi
  int v5; // ebx
  UICaption *v6; // esi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  UICaption *v14; // esi
  bool v15; // zf
  int *p_m_bcreateok; // esi
  int v17; // ebx
  UICaption *v18; // esi
  int v19; // ebx
  const CHAR *v20; // [esp-0x4] [ebp-A0h]
  int *v21; // [esp+0x10] [ebp-0x8C]
  char *a2; // [esp+0x14] [ebp-0x88]
  int v23; // [esp+0x18] [ebp-0x84]
  char Buffer[128]; // [esp+0x1C] [ebp-0x80] BYREF

  v3 = 0;
  if ( *((int *)&this->me_Role[2].m_Qi.m_id + arg0) > 0 )
  {
    switch ( arg0 )
    {
      case 0:
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)&this->me_Role[2].m_Qi.m_childs.m_pData + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v8;
        lstrcpyA(this->buf, (LPCSTR)&dword_DC433C);
        break;
      case 1:
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(&this->me_Role[2].m_QiVal.m_childs.capacity + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v9;
        lstrcpyA(this->buf, (LPCSTR)&dword_DCF83C);
        break;
      case 2:
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)&this->me_Role[2].m_AttFramePose.m_pbk2 + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v10;
        v20 = (const CHAR *)&dword_DCF93C;
        goto LABEL_14;
      case 3:
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)&this->me_Role[2].m_RoleAtt[2].m_ratioh + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v11;
        lstrcpyA(this->buf, (LPCSTR)&dword_DCFA3C);
        break;
      case 4:
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(&this->me_Role[2].m_RoleAtt[5].m_rect.right + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v12;
        lstrcpyA(this->buf, (LPCSTR)&dword_DCFB3C);
        break;
      case 5:
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)&this->me_Role[2].m_RoleAtt[7].m_ppic + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v13;
        v20 = byte_DCFC3C;
LABEL_14:
        lstrcpyA(this->buf, v20);
        break;
      default:
        break;
    }
    sprintf(Buffer, (const char *)&dir[20], LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow) + 1);
    lstrcatA(this->buf, Buffer);
    SetEnable((UICaption *)&this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]);
    if ( *((int *)&this->me_Role[2].m_Qi.m_id + arg0) <= 0 )
    {
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok);
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok);
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok);
      p_m_bcreateok = (int *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
      v17 = 5;
      do
      {
        SetEnable((UICaption *)(p_m_bcreateok + 190));
        SetEnable((UICaption *)p_m_bcreateok);
        p_m_bcreateok += 38;
        --v17;
      }
      while ( v17 );
      v18 = (UICaption *)&this->me_Role[1].m_EquipHat.m_caption[124];
      v19 = 4;
      do
      {
        SetEnable(v18);
        v18 = (UICaption *)((char *)v18 + 152);
        --v19;
      }
      while ( v19 );
      SetEnable((UICaption *)&this->me_Role[1].m_EquipShoes.m_caption[108]);
    }
    else
    {
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok);
      sprintf(this->buf, (const char *)&dir[20], *(_DWORD *)(v3 + 636));
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok);
      sprintf(this->buf, (const char *)&dir[20], *(_DWORD *)(v3 + 644));
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok);
      sprintf(this->buf, "%s%d", (const char *)g_bSlotFlag, *(_DWORD *)(v3 + 664));
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok);
      sprintf(this->buf, "%s%d", (const char *)&g_bSlotFlag[256], *(_DWORD *)(v3 + 668));
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[6].m_bcreateok);
      sprintf(this->buf, "%s%d", (const char *)&g_bSlotFlag[512], *(_DWORD *)(v3 + 676));
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[8].m_bcreateok);
      sprintf(this->buf, "%s%d", byte_DC3F3C, *(_DWORD *)(v3 + 672));
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[7].m_bcreateok);
      sprintf(this->buf, "%s%d", byte_DC403C, *(_DWORD *)(v3 + 680));
      SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[9].m_bcreateok);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 648));
      SetEnable((UICaption *)&this->me_Role[1].m_EquipPic.m_bcreateok);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 652));
      SetEnable((UICaption *)&this->me_Role[1].m_EquipWeapon.m_bcreateok);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 656));
      SetEnable((UICaption *)&this->me_Role[1].m_EquipWeapon.m_caption[12]);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 660));
      SetEnable((UICaption *)&this->me_Role[1].m_EquipHat.m_id);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 740));
      SetEnable((UICaption *)this->me_Role[1].m_EquipHat.m_texarrayInfo);
      v14 = (UICaption *)&this->me_Role[1].m_EquipHat.m_caption[124];
      a2 = (char *)&this->me_Role[1].m_EquipShoes.m_caption[44];
      v21 = (int *)(v3 + 760);
      v23 = 4;
      do
      {
        if ( *v21 )
        {
          (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v21);
          (((UIWnd *)v14))->UIWnd::sub_445FA0(a2);
          SetEnable(v14);
          a2 += 16;
        }
        else
        {
          SetEnable(v14);
        }
        v14 = (UICaption *)((char *)v14 + 152);
        v15 = v23 == 1;
        ++v21;
        --v23;
      }
      while ( !v15 );
      SetEnable((UICaption *)&this->me_Role[1].m_EquipShoes.m_caption[108]);
      (((PalScript *)&this->me_Role[1].m_RoleAttEqual[0].m_ppic))->PalScript::LoadModel((const char *)(v3 + 518), 50);
    }
  }
  else
  {
    SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok);
    SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok);
    SetEnable((UICaption *)&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok);
    v4 = (int *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
    v5 = 5;
    do
    {
      SetEnable((UICaption *)(v4 + 190));
      SetEnable((UICaption *)v4);
      v4 += 38;
      --v5;
    }
    while ( v5 );
    v6 = (UICaption *)&this->me_Role[1].m_EquipHat.m_caption[124];
    v7 = 4;
    do
    {
      SetEnable(v6);
      v6 = (UICaption *)((char *)v6 + 152);
      --v7;
    }
    while ( v7 );
    SetEnable((UICaption *)&this->me_Role[1].m_EquipShoes.m_caption[108]);
    SetEnable((UICaption *)&this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]);
  }
}

// 0x004844A0
int MainEquipUI::CountVisibleStats()
{
  int result; // eax
  int *p_m_nSize; // ecx
  int *p_m_align; // ebp
  int v5; // edi
  int *v6; // eax
  int v7; // ecx
  bool v8; // cc
  int *v9; // [esp+0x10] [ebp-0xC]
  int v10; // [esp+0x14] [ebp-0x8]
  int v11; // [esp+0x18] [ebp-0x4]

  result = 0;
  p_m_nSize = (int *)&this->me_Role[1].m_RoleAttEqual[0].m_childs.m_nSize;
  v10 = 0;
  v11 = 0;
  v9 = (int *)p_m_nSize;
  p_m_align = (int *)&this->me_Role[2].m_RoleAttCng[5].m_align;
  do
  {
    if ( this->m_Is[result] )
    {
      v5 = 0;
      while ( 1 )
      {
        if ( v5 == 5 )
        {
          if ( *((_BYTE *)p_m_nSize + 5) == 2 )
          {
            (((LineupComp *)this))->LineupComp::GetSlotWidget(result, 1u);
            p_m_align[3] = 1;
            *(_BYTE *)p_m_align = 1;
          }
          else
          {
            *p_m_nSize = 0;
            *((_WORD *)p_m_nSize + 2) = 0;
            (((LineupComp *)this))->LineupComp::GetSlotWidget(result, 0);
            sub_445E50((int)(p_m_align - 17));
            v6 = (int *)(p_m_align - 310);
            v7 = 6;
            do
            {
              v6[3] = 0;
              *(_BYTE *)v6 = 0;
              v6 += 62;
              --v7;
            }
            while ( v7 );
          }
        }
        else
        {
          sub_445E50((int)&this->me_Role[2].m_RoleAtt[6].m_disablepicInfo + 248 * v5 + v11);
          if ( *((_BYTE *)v9 + v5) )
          {
            if ( *((_BYTE *)v9 + v5) == 1 )
            {
              *(int *)((char *)&this->me_Role[2].m_RoleAtt[7].m_benable + 248 * v5 + v11) = 0;
              *((_BYTE *)&this->me_Role[2].m_RoleAtt[7].m_childs.m_needscriptdel + 248 * v5 + v11) = 0;
            }
            else if ( *((_BYTE *)v9 + v5) == 2 )
            {
              *(int *)((char *)&this->me_Role[2].m_RoleAtt[7].m_benable + 248 * v5 + v11) = 1;
              *((_BYTE *)&this->me_Role[2].m_RoleAtt[7].m_childs.m_needscriptdel + 248 * v5 + v11) = 1;
            }
          }
          else
          {
            *(int *)((char *)&this->me_Role[2].m_RoleAtt[7].m_benable + 248 * v5 + v11) = 0;
            *((_BYTE *)&this->me_Role[2].m_RoleAtt[7].m_childs.m_needscriptdel + 248 * v5 + v11) = 0;
            sub_445E50((int)&this->me_Role[2].m_RoleAtt[6].m_disablepicInfo + 248 * v5 + v11);
          }
        }
        if ( ++v5 >= 6 )
          break;
        result = v10;
        p_m_nSize = (int *)v9;
      }
      sub_445E50((int)(p_m_align - 17));
      result = v10;
      p_m_nSize = (int *)v9;
    }
    ++result;
    p_m_nSize = (int *)((char *)p_m_nSize + 6);
    p_m_align += 486;
    v8 = v11 + 1944 < 9720;
    v10 = result;
    v9 = (int *)p_m_nSize;
    v11 += 1944;
  }
  while ( v8 );
  return result;
}

// 0x004930E0
void MainEquipUI::UpdateTooltip(int nVal)
{
  int v3; // eax
  int v4; // ecx
  char *v5; // esi
  RoleAtt *v6; // eax
  RoleAtt *v7; // eax
  RoleAtt *v8; // eax
  RoleAtt *v9; // ebx
  CHAR *v10; // [esp-0x4] [ebp-0x10]

  v3 = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nVal);
  if ( v3 )
  {
    switch ( lstrlenA((LPCSTR)(v3 + 4)) )
    {
      case 4:
        *((_DWORD *)&this->mb_SortDefault + 172) = 32;
        break;
      case 6:
        *((_DWORD *)&this->mb_SortDefault + 172) = 26;
        break;
      case 8:
        *((_DWORD *)&this->mb_SortDefault + 172) = 20;
        break;
      case 10:
        *((_DWORD *)&this->mb_SortDefault + 172) = 14;
        break;
      default:
        break;
    }
    *((_DWORD *)&this->mb_SortDefault + 174) = *((_DWORD *)&this->mb_SortDefault + 172) + 108;
    (((UIWnd *)((char *)&this->mb_SortDefault + 700)))->UIWnd::sub_445FA0((char *)&this->mb_SortDefault + 684);
    SetEnable((UICaption *)((char *)&this->mb_SortDefault + 700));
  }
  else
  {
    SetEnable((UICaption *)((char *)&this->mb_SortDefault + 700));
  }
  v4 = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nVal);
  if ( v4 )
    v10 = (CHAR *)(v4 + 4);
  else
    v10 = unk_C10D38;
  v5 = (char *)this + 9980 * nVal;
  (((CScreenMode *)(v5 + 162768)))->CScreenMode::SetTooltipText((int)v10);
  v6 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nVal];
  if ( v6 )
    (((CScreenMode *)(v5 + 163112)))->CScreenMode::SetTooltipText((int)&v6->type);
  else
    (((CScreenMode *)(v5 + 163112)))->CScreenMode::SetTooltipText((int)unk_C10D38);
  v7 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nVal];
  if ( v7 )
    (((CScreenMode *)(v5 + 163456)))->CScreenMode::SetTooltipText((int)&v7->type);
  else
    (((CScreenMode *)(v5 + 163456)))->CScreenMode::SetTooltipText((int)unk_C10D38);
  v8 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nVal + 3];
  if ( v8 )
    (((CScreenMode *)(v5 + 163800)))->CScreenMode::SetTooltipText((int)&v8->type);
  else
    (((CScreenMode *)(v5 + 163800)))->CScreenMode::SetTooltipText((int)unk_C10D38);
  v9 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nVal + 6];
  if ( v9 )
    (((CScreenMode *)(v5 + 164144)))->CScreenMode::SetTooltipText((int)&v9->type);
  else
    (((CScreenMode *)(v5 + 164144)))->CScreenMode::SetTooltipText((int)unk_C10D38);
}

// 0x0049AEA0
void MainEquipUI::ShowWithCursor(int nVal)
{
  int *p_capacity; // edi
  int v4; // ebp
  char *m_text; // edi
  int v6; // ebp
  UICursor *v7; // ecx
  char *p_m_bcreateok; // edi
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx

  this->m_TimeMoney.m_text[13] = 0;
  (((EquipUI *)this))->EquipUI::SetGroupVisible(1u) /* [ROWTABLE] */;
  p_capacity = (int *)&this->me_Role[4].m_RoleAttCng[1].m_childs.capacity;
  v4 = 6;
  do
  {
    sub_445E50((int)p_capacity);
    p_capacity += 86;
    --v4;
  }
  while ( v4 );
  this->MainEquipUI::SetupRoleList(nVal, 0);
  m_text = this->me_Role[2].m_AttFramePose.m_text;
  v6 = 5;
  do
  {
    (**(void ( ***)(char *, _DWORD))m_text)((char *)(m_text), (_DWORD)(0));
    m_text += 4892;
    --v6;
  }
  while ( v6 );
  SetEnable((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right);
  SetEnable((UICaption *)&this->me_Role[4].m_RoleAtt[8].m_rect.right);
  this->m_Ctrlbtn[1].m_texarrayInfo[2] = 0;
  switch ( nVal )
  {
    case 0:
      p_m_bcreateok = (char *)&this->me_Role[5].m_Jing.m_bcreateok;
      (*(void ( **)(int *, int))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        1);
      (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])((char *)(&this->m_ClothName.m_text[12]), (_DWORD)(0));
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[1].Remark.skillCount + 210))((char *)((char *)&this->m_role[1].Remark.skillCount + 210), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])((char *)(&this->m_role[2].ImageID[24]), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[4].Remark.skillCount + 70))((char *)((char *)&this->m_role[4].Remark.skillCount + 70), (_DWORD)(0));
      this->m_TimeMoney.m_fonttype = ((Parent_Data *)0);
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[1].m_childs.capacity);
      LOBYTE(v9) = g_bDebugMode;
      (((UIPushButton *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Resume_word.tga", v9);
      goto LABEL_11;
    case 1:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      p_m_bcreateok = (char *)&this->m_ClothName.m_text[12];
      (**(void ( ***)(char *, int))&this->m_ClothName.m_text[12])((char *)(&this->m_ClothName.m_text[12]), (int)(1));
      (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::GetItem();
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[1].Remark.skillCount + 210))((char *)((char *)&this->m_role[1].Remark.skillCount + 210), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])((char *)(&this->m_role[2].ImageID[24]), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[4].Remark.skillCount + 70))((char *)((char *)&this->m_role[4].Remark.skillCount + 70), (_DWORD)(0));
      this->m_TimeMoney.m_fonttype = ((Parent_Data *)((Parent_Data *)1));
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[3].m_ratioh);
      LOBYTE(v10) = g_bDebugMode;
      (((UIPushButton *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Treasure_word.tga", v10);
      goto LABEL_11;
    case 2:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])((char *)(&this->m_ClothName.m_text[12]), (_DWORD)(0));
      p_m_bcreateok = (char *)&this->m_typeWord.m_childs;
      (*(void ( **)(PtrArray *, int))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 1);
      (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::GetItem();
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[1].Remark.skillCount + 210))((char *)((char *)&this->m_role[1].Remark.skillCount + 210), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])((char *)(&this->m_role[2].ImageID[24]), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[4].Remark.skillCount + 70))((char *)((char *)&this->m_role[4].Remark.skillCount + 70), (_DWORD)(0));
      this->m_TimeMoney.m_fonttype = ((Parent_Data *)((Parent_Data *)2));
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[5].m_ppic);
      LOBYTE(v11) = g_bDebugMode;
      (((UIPushButton *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Attack_word.tga", v11);
      goto LABEL_11;
    case 3:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])((char *)(&this->m_ClothName.m_text[12]), (_DWORD)(0));
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      p_m_bcreateok = (char *)&this->m_role[1].Remark.skillCount + 210;
      (**(void ( ***)(char *, int))((char *)&this->m_role[1].Remark.skillCount + 210))((char *)((char *)&this->m_role[1].Remark.skillCount + 210), (int)(1));
      (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])((char *)(&this->m_role[2].ImageID[24]), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[4].Remark.skillCount + 70))((char *)((char *)&this->m_role[4].Remark.skillCount + 70), (_DWORD)(0));
      this->m_TimeMoney.m_fonttype = ((Parent_Data *)((Parent_Data *)3));
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[8].m_wndcolor);
      LOBYTE(v12) = g_bDebugMode;
      (((UIPushButton *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Smelt_word.tga", v12);
      goto LABEL_11;
    case 4:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])((char *)(&this->m_ClothName.m_text[12]), (_DWORD)(0));
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[1].Remark.skillCount + 210))((char *)((char *)&this->m_role[1].Remark.skillCount + 210), (_DWORD)(0));
      p_m_bcreateok = (char *)&this->m_role[2].ImageID[24];
      (**(void ( ***)(char *, int))&this->m_role[2].ImageID[24])((char *)(&this->m_role[2].ImageID[24]), (int)(1));
      (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::GetItem();
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[4].Remark.skillCount + 70))((char *)((char *)&this->m_role[4].Remark.skillCount + 70), (_DWORD)(0));
      this->m_TimeMoney.m_fonttype = ((Parent_Data *)((Parent_Data *)4));
      sub_445E50((int)&this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel);
      LOBYTE(v13) = g_bDebugMode;
      (((UIPushButton *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Ancient_word.tga", v13);
LABEL_11:
      if ( (((UIListBox *)p_m_bcreateok))->UIListBox::GetItemData() > 0 )
        goto LABEL_14;
      break;
    case 5:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])((char *)(&this->m_ClothName.m_text[12]), (_DWORD)(0));
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[1].Remark.skillCount + 210))((char *)((char *)&this->m_role[1].Remark.skillCount + 210), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])((char *)(&this->m_role[2].ImageID[24]), (_DWORD)(0));
      (**(void ( ***)(char *, int))((char *)&this->m_role[4].Remark.skillCount + 70))((char *)((char *)&this->m_role[4].Remark.skillCount + 70), (int)(1));
      (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::GetItem();
      this->m_TimeMoney.m_fonttype = ((Parent_Data *)((Parent_Data *)5));
      sub_445E50((int)&this->me_Role[4].m_RoleAttEqual[2].m_texty);
      LOBYTE(v14) = g_bDebugMode;
      (((UIPushButton *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Special_word.tga", v14);
      if ( (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::GetItemData() > 0 )
LABEL_14:
        (*(void ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(this, 1007, 0, 0);
      break;
    default:
      break;
  }
  (((UICursor *)v7))->UICursor::_todo_541CC0();
}

// 0x0049B2E0
void MainEquipUI::SetupRoleList(int arg0, char arg4)
{
  MainEquipUI *v3; // ebx
  signed int i; // ebp
  int *v5; // eax
  int j; // ebp
  int v7; // eax
  int ItemData; // eax
  signed int v9; // esi
  int *v10; // eax
  const char *v11; // esi
  signed int k; // ebp
  int *v13; // eax
  int m; // ebp
  int v15; // eax
  int v16; // eax
  signed int v17; // esi
  int *v18; // eax
  UIListBox *p_m_childs; // edi
  void *v20; // ebx
  signed int v21; // ebp
  char *v22; // esi
  int *v23; // eax
  int ListItems; // ebx
  int v25; // eax
  signed int v26; // esi
  int *v27; // eax
  char *v28; // ebx
  const char *v29; // ebp
  UIListBox *v30; // edi
  void *v31; // ebx
  signed int v32; // ebp
  char *v33; // esi
  int *v34; // eax
  int v35; // ebx
  int v36; // eax
  signed int v37; // esi
  int *v38; // eax
  UIListBox *v39; // edi
  void *v40; // ebx
  signed int v41; // ebx
  char *v42; // esi
  int *v43; // eax
  int v44; // ebp
  int v45; // eax
  signed int v46; // esi
  int *v47; // eax
  UIListBox *v48; // edi
  void *v49; // ebx
  signed int v50; // ebp
  char *v51; // esi
  int *v52; // eax
  int v53; // ebx
  int v54; // eax
  signed int v55; // esi
  int *v56; // eax
  int *v57; // eax
  int nVala; // [esp+0x10] [ebp-0x1C0]
  int nValb; // [esp+0x10] [ebp-0x1C0]
  int nIndex; // [esp+0x14] [ebp-0x1BC]
  int sel; // [esp+0x18] [ebp-0x1B8]
  int sela; // [esp+0x18] [ebp-0x1B8]
  int selb; // [esp+0x18] [ebp-0x1B8]
  int selc; // [esp+0x18] [ebp-0x1B8]
  int seld; // [esp+0x18] [ebp-0x1B8]
  int sele; // [esp+0x18] [ebp-0x1B8]
  int p_DWORD; // [esp+0x1C] [ebp-0x1B4] BYREF
  int v69; // [esp+0x20] [ebp-0x1B0]
  int v70; // [esp+0x24] [ebp-0x1AC]
  gbColorQuad v71; // [esp+0x28] [ebp-0x1A8] BYREF
  gbColorQuad v72; // [esp+0x2C] [ebp-0x1A4] BYREF
  gbColorQuad v73; // [esp+0x30] [ebp-0x1A0] BYREF
  gbColorQuad v74; // [esp+0x34] [ebp-0x19C] BYREF
  gbColorQuad v75; // [esp+0x38] [ebp-0x198] BYREF
  gbColorQuad v76; // [esp+0x3C] [ebp-0x194] BYREF
  int nVal2[3]; // [esp+0x40] [ebp-0x190] BYREF
  char Buffer; // [esp+0x4C] [ebp-0x184] BYREF
  _BYTE v79[252]; // [esp+0x4D] [ebp-0x183] BYREF
  __int16 v80; // [esp+0x149] [ebp-0x87]
  char v81; // [esp+0x14B] [ebp-0x85]
  _BYTE v82[12]; // [esp+0x14C] [ebp-0x84] BYREF
  _BYTE v83[12]; // [esp+0x158] [ebp-0x78] BYREF
  _BYTE v84[12]; // [esp+0x164] [ebp-0x6C] BYREF
  _BYTE v85[12]; // [esp+0x170] [ebp-0x60] BYREF
  _BYTE v86[12]; // [esp+0x17C] [ebp-0x54] BYREF
  _BYTE v87[12]; // [esp+0x188] [ebp-0x48] BYREF
  _BYTE v88[12]; // [esp+0x194] [ebp-0x3C] BYREF
  _BYTE v89[12]; // [esp+0x1A0] [ebp-0x30] BYREF
  _BYTE pOut[12]; // [esp+0x1AC] [ebp-0x24] BYREF
  _BYTE v91[12]; // [esp+0x1B8] [ebp-0x18] BYREF
  _BYTE v92[12]; // [esp+0x1C4] [ebp-0xC] BYREF
p_DWORD = 0xFFFF;
  v69 = 0;
  v70 = 0;
  nIndex = 0;
  *(_DWORD *)this->m_TimeMoney.m_text = arg0;
  if ( arg0 == 5 )
  {
    (((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray))->CCBFiveNimbusWindow::SetFloatParam(228.0);
    (((Camera *)&this->m_Ctrlbtn[1].m_texarray))->Camera::UpdateCameraLookAt(128, 262, 600);
  }
  else
  {
    (((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray))->CCBFiveNimbusWindow::SetFloatParam(160.0);
    (((Camera *)&this->m_Ctrlbtn[1].m_texarray))->Camera::UpdateCameraLookAt(128, 258, 600);
  }
  switch ( arg0 )
  {
    case 0:
      sel = (int)this->me_Role[5].m_JingBar.m_pbk;
      nIndex = (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::CreateChild();
      if ( !arg4 )
        (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(0);
      if ( *(int *)&this->m_Ctrlbtn[1].m_bBigFont >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( !arg4 )
      {
        for ( i = 0; i < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize(); ++i )
        {
          v5 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, i);
          p_DWORD = (unsigned long)*v5;
          v69 = (unsigned long)v5[1];
          v70 = (unsigned long)v5[2];
          sprintf(&this->buf[4], "%s", v70 + 4);
          nVala = (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::LoadListItems(&this->buf[4], 0);
          sprintf(&this->buf[4], (const char *)&dir[20], v69);
          (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::SetMouseMoveSel(1, nVala, &this->buf[4], 0);
        }
      }
      for ( j = 0; j < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize(); ++j )
      {
        if ( (((PAL_GDB *)this))->PAL_GDB::LoadByType(j, 0) )
        {
          if ( j < 0 || j >= (int)this->me_Role[5].m_Shen.m_wndcolor.Color )
            v7 = 0;
          else
            v7 = *(_DWORD *)(this->me_Role[5].m_Shen.m_fontcolor.Color + 4 * j);
          *(_DWORD *)(v7 + 68) = this->me_Role[5].m_Jing.m_bvisible;
        }
        else
        {
          UITabCtrl_SetItemParam(j);
        }
      }
      (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::SetSel(sel);
      ItemData = (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::GetItemData();
      v9 = nIndex;
      if ( ItemData <= nIndex )
      {
        v9 = ItemData - 1;
        nIndex = ItemData - 1;
      }
      (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::GetItem();
      if ( v9 >= 0 )
      {
        v10 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v82, v9);
        p_DWORD = (unsigned long)*v10;
        v69 = (unsigned long)v10[1];
        v70 = (unsigned long)v10[2];
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
          sprintf(&this->buf[4], "%s", "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        (((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1]))->PalScript::LoadModel(&this->buf[4], 0);
        v11 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), unk_C10D38) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v11, (const char *)(v70 + 66));
          goto LABEL_54;
        }
        goto LABEL_52;
      }
      break;
    case 1:
      sela = this->m_HatName.m_childs.capacity;
      nIndex = (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::CreateChild();
      if ( !arg4 )
        (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(1);
      if ( *(int *)&this->m_Ctrlbtn[1].m_bBigFont >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( !arg4 )
      {
        for ( k = 0; k < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize(); ++k )
        {
          v13 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v92, k);
          p_DWORD = (unsigned long)*v13;
          v69 = (unsigned long)v13[1];
          v70 = (unsigned long)v13[2];
          sprintf(&this->buf[4], "%s", v70 + 4);
          nValb = (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::LoadListItems(&this->buf[4], 0);
          sprintf(&this->buf[4], (const char *)&dir[20], v69);
          (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::SetMouseMoveSel(1, nValb, &this->buf[4], 0);
        }
      }
      for ( m = 0; m < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize(); ++m )
      {
        if ( (((PAL_GDB *)this))->PAL_GDB::LoadByType(m, 0) )
        {
          if ( m < 0 || m >= (int)this->m_Adorn1Name.m_disablepicInfo )
            v15 = 0;
          else
            v15 = *((_DWORD *)((gbRefObject *)this->m_Adorn1Name.m_disablepic) + m);
          *(_DWORD *)(v15 + 68) = (_DWORD)this->m_ClothName.m_pbk;
        }
        else
        {
          UITabCtrl_SetItemParam(m);
        }
      }
      (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::SetSel(sela);
      v16 = (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::GetItemData();
      v17 = nIndex;
      if ( v16 <= nIndex )
      {
        v17 = v16 - 1;
        nIndex = v16 - 1;
      }
      (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::GetItem();
      if ( v17 >= 0 )
      {
        v18 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v91, v17);
        p_DWORD = (unsigned long)*v18;
        v69 = (unsigned long)v18[1];
        v70 = (unsigned long)v18[2];
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
          sprintf(&this->buf[4], "%s", "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        (((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1]))->PalScript::LoadModel(&this->buf[4], 0);
        v11 = (const char *)(v70 + 36);
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
        {
LABEL_52:
          sprintf(&this->buf[4], "%s", "NONE");
        }
        else
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v11, (const char *)(v70 + 66));
LABEL_54:
          sprintf(&this->buf[4], "Item\\%s\\%s.tga", v11, &Buffer);
        }
        (((gbGeomNode *)*(gbGeomNode **)&this->m_Ctrlbtn[1].m_mouseoff))->gbGeomNode::ReplaceTexture(&this->buf[4]);
        this->m_Ctrlbtn[1].m_texarrayInfo[2] = (_PlugInfo *)1;
        goto LABEL_114;
      }
      break;
    case 2:
      p_m_childs = (UIListBox *)&this->m_typeWord.m_childs;
      selb = *(_DWORD *)((char *)&this->m_role[0].Remark.skillCount + 106);
      nIndex = (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::CreateChild();
      (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(2);
      v20 = (void *)(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( (int)v20 >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(v20);
      v21 = 0;
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v22 = (char *)&this->buf[4];
        do
        {
          v23 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v85, v21);
          p_DWORD = (unsigned long)*v23;
          v69 = (unsigned long)v23[1];
          v70 = (unsigned long)v23[2];
          sprintf(v22, "%s", v70 + 4);
          ListItems = (((UIListBox *)p_m_childs))->UIListBox::LoadListItems(v22, 0);
          sprintf(v22, (const char *)&dir[20], v69);
          (((UIListBox *)p_m_childs))->UIListBox::SetMouseMoveSel(1, ListItems, v22, 0);
          UITabCtrl_SetItemParam(ListItems);
          ++v21;
        }
        while ( v21 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      (((UIListBox *)p_m_childs))->UIListBox::SetSel(selb);
      v25 = (((UIListBox *)p_m_childs))->UIListBox::GetItemData();
      v26 = nIndex;
      if ( v25 <= nIndex )
      {
        v26 = v25 - 1;
        nIndex = v25 - 1;
      }
      (((UIListBox *)p_m_childs))->UIListBox::GetItem();
      if ( v26 >= 0 )
      {
        v27 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v89, v26);
        p_DWORD = (unsigned long)*v27;
        v69 = (unsigned long)v27[1];
        v28 = (char *)&this->buf[4];
        v70 = (unsigned long)v27[2];
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
          sprintf(&this->buf[4], "%s", "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        (((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1]))->PalScript::LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), unk_C10D38) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
          goto LABEL_112;
        }
        goto LABEL_110;
      }
      break;
    case 3:
      v30 = (UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210);
      selc = *(_DWORD *)((char *)&this->m_role[1].Remark + 462);
      nIndex = (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::CreateChild();
      (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(3);
      v31 = (void *)(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( (int)v31 >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(v31);
      v32 = 0;
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v33 = (char *)&this->buf[4];
        do
        {
          v34 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v87, v32);
          p_DWORD = (unsigned long)*v34;
          v69 = (unsigned long)v34[1];
          v70 = (unsigned long)v34[2];
          sprintf(v33, "%s", v70 + 4);
          v35 = (((UIListBox *)v30))->UIListBox::LoadListItems(v33, 0);
          sprintf(v33, (const char *)&dir[20], v69);
          (((UIListBox *)v30))->UIListBox::SetMouseMoveSel(1, v35, v33, 0);
          UITabCtrl_SetItemParam(v35);
          ++v32;
        }
        while ( v32 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      (((UIListBox *)v30))->UIListBox::SetSel(selc);
      v36 = (((UIListBox *)v30))->UIListBox::GetItemData();
      v37 = nIndex;
      if ( v36 <= nIndex )
      {
        v37 = v36 - 1;
        nIndex = v36 - 1;
      }
      (((UIListBox *)v30))->UIListBox::GetItem();
      if ( v37 >= 0 )
      {
        v38 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v83, v37);
        p_DWORD = (unsigned long)*v38;
        v69 = (unsigned long)v38[1];
        v28 = (char *)&this->buf[4];
        v70 = (unsigned long)v38[2];
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
          sprintf(&this->buf[4], "%s", "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        (((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1]))->PalScript::LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), unk_C10D38) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
          goto LABEL_112;
        }
        goto LABEL_110;
      }
      break;
    case 4:
      v39 = (UIListBox *)&this->m_role[2].ImageID[24];
      seld = this->m_role[2].normalplunder;
      nIndex = (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::CreateChild();
      (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(4);
      v40 = (void *)(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( (int)v40 >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(v40);
      v41 = 0;
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v42 = (char *)&this->buf[4];
        do
        {
          v43 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v84, v41);
          p_DWORD = (unsigned long)*v43;
          v69 = (unsigned long)v43[1];
          v70 = (unsigned long)v43[2];
          if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD) && v69 > 1 )
          {
            --v69;
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          }
          sprintf(v42, "%s", v70 + 4);
          v44 = (((UIListBox *)v39))->UIListBox::LoadListItems(v42, 0);
          sprintf(v42, (const char *)&dir[20], v69);
          (((UIListBox *)v39))->UIListBox::SetMouseMoveSel(1, v44, v42, 0);
          UITabCtrl_SetItemParam(v44);
          ++v41;
        }
        while ( v41 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      (((UIListBox *)v39))->UIListBox::SetSel(seld);
      v45 = (((UIListBox *)v39))->UIListBox::GetItemData();
      v46 = nIndex;
      if ( v45 <= nIndex )
      {
        v46 = v45 - 1;
        nIndex = v45 - 1;
      }
      (((UIListBox *)v39))->UIListBox::GetItem();
      if ( v46 >= 0 )
      {
        v47 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v86, v46);
        p_DWORD = (unsigned long)*v47;
        v69 = (unsigned long)v47[1];
        v28 = (char *)&this->buf[4];
        v70 = (unsigned long)v47[2];
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
          sprintf(&this->buf[4], "%s", "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        (((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1]))->PalScript::LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), unk_C10D38) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
          goto LABEL_112;
        }
        goto LABEL_110;
      }
      break;
    case 5:
      v48 = (UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70);
      sele = *(_DWORD *)((char *)&this->m_role[4].Remark + 322);
      nIndex = (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::CreateChild();
      (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(5);
      v49 = (void *)(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( (int)v49 >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(v49);
      v50 = 0;
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v51 = (char *)&this->buf[4];
        do
        {
          v52 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v88, v50);
          p_DWORD = (unsigned long)*v52;
          v69 = (unsigned long)v52[1];
          v70 = (unsigned long)v52[2];
          sprintf(v51, "%s", v70 + 4);
          v53 = (((UIListBox *)v48))->UIListBox::LoadListItems(v51, 0);
          sprintf(v51, (const char *)&dir[20], v69);
          (((UIListBox *)v48))->UIListBox::SetMouseMoveSel(1, v53, v51, 0);
          UITabCtrl_SetItemParam(v53);
          ++v50;
        }
        while ( v50 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      (((UIListBox *)v48))->UIListBox::SetSel(sele);
      v54 = (((UIListBox *)v48))->UIListBox::GetItemData();
      v55 = nIndex;
      if ( v54 <= nIndex )
      {
        v55 = v54 - 1;
        nIndex = v54 - 1;
      }
      (((UIListBox *)v48))->UIListBox::GetItem();
      if ( v55 >= 0 )
      {
        v56 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(nVal2, v55);
        p_DWORD = (unsigned long)*v56;
        v69 = (unsigned long)v56[1];
        v28 = (char *)&this->buf[4];
        v70 = (unsigned long)v56[2];
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
          sprintf(&this->buf[4], "%s", "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        (((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1]))->PalScript::LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( !strcmp((const char *)(v70 + 36), unk_C10D38) )
        {
LABEL_110:
          sprintf(v28, "%s", "NONE");
        }
        else
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
LABEL_112:
          sprintf(v28, "Item\\%s\\%s.tga", v29, &Buffer);
        }
        (((gbGeomNode *)*(gbGeomNode **)&this->m_Ctrlbtn[1].m_mouseoff))->gbGeomNode::ReplaceTexture(v28);
        this->m_Ctrlbtn[1].m_texarrayInfo[2] = (_PlugInfo *)1;
goto LABEL_114;
      }
      break;
    default:
LABEL_114:
      v57 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(nVal2, nIndex);
      (((MainEquipUI *)this))->MainEquipUI::SetSlotLabel(*v57, v57[1], v57[2]);
      break;
  }
}

// 0x0049C9F0
void MainEquipUI::SetSlotLabel(int nVal, int nVal2, int nVal3)
{
  CHAR *v5; // edi
  CHAR *v6; // ebp
  LPCSTR v7; // eax

  v5 = (CHAR *)&this->buf[4];
  sprintf(&this->buf[4], unk_C10D38);
  v6 = (CHAR *)sub_458F70((LPCSTR)(nVal3 + 96), (int)asc_5B74B8, &this->m_Is[3]);
  if ( lstrlenA((const char *)v6) <= 0 )
  {
    (((RoleAtt *)nVal3))->RoleAtt::FormatAttributeText();
    lstrcpyA((char *)v5, v7);
  }
  else
  {
    lstrcpyA((char *)v5, v6);
  }
  SetEnable((UICaption *)&this->me_Role[4].m_RoleAtt[8].m_rect.right);
  SetEnable((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right);
}

// 0x0049E670
void MainEquipUI::ResetControls()
{
  int i; // eax
  int v3; // eax

  this->i = 0;
  do
  {
    i = this->i;
    if ( *((_BYTE *)&this->m_TimeMoney.m_ratiow + i + 1) )
    {
      (((UIListBox *)&this->me_Role[1].m_EquipHat.m_caption[4892 * i + 144]))->UIListBox::GetCurSel();
      (((UIListBox *)(&this->me_Role[1].m_EquipAdorn2.m_bvisible + 1223 * this->i)))->UIListBox::GetCurSel();
      (((UIListBox *)&this->me_Role[1].m_EquipShoes.m_caption[4892 * this->i + 4]))->UIListBox::GetCurSel();
      sprintf(
        &this->buf[4],
        "%d/%d",
        (int)*(float *)&this->me_Role[1].m_EquipCloth.m_texarray.m_ptex[1223 * this->i + 13],
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->i));
      SetEnable((UICaption *)&this->me_Role[1].m_EquipCloth.m_caption[4892 * this->i + 44]);
      sprintf(
        &this->buf[4],
        "%d/%d",
        (int)*(float *)&this->me_Role[1].m_EquipAdorn2.m_caption[4892 * this->i + 20],
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->i + 1));
      SetEnable((UICaption *)&this->me_Role[1].m_EquipAdorn2.m_caption[4892 * this->i + 108]);
      sprintf(
        &this->buf[4],
        "%d/%d",
        (int)*((float *)&this->me_Role[1].m_EquipAdorn1.m_wndcolor.Color + 1223 * this->i),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->i + 2));
      SetEnable((UICaption *)((char *)&this->me_Role[1].m_EquipAdorn1.m_texarray + 4892 * this->i));
      (**(void ( ***)(char *, _DWORD))&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i])((char *)(&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i]), (_DWORD)(0));
    }
    v3 = this->i + 1;
    this->i = v3;
  }
  while ( v3 < 5 );
  SetEnable((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right);
  SetEnable((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right);
  this->m_Ctrlbtn[1].m_texarrayInfo[2] = 0;
}

// 0x0049E8E0
int MainEquipUI::CreateFromData(int *pBuffer)
{
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int v24; // eax
  UIPushButton *v25; // edi
  int v26; // ebp
  int v27; // ecx
  int v28; // ebx
  int v29; // edx
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // eax
  int p_DWORD; // [esp+0x160] [ebp-0x70] BYREF
  int v37; // [esp+0x164] [ebp-0x6C]
  int nHeight; // [esp+0x168] [ebp-0x68]
  int v39; // [esp+0x16C] [ebp-0x64]
  _DWORD v40[2]; // [esp+0x170] [ebp-0x60] BYREF
  int v41; // [esp+0x178] [ebp-0x58]
  int v42; // [esp+0x17C] [ebp-0x54]
  _DWORD v43[2]; // [esp+0x180] [ebp-0x50] BYREF
  int v44; // [esp+0x188] [ebp-0x48]
  int v45; // [esp+0x18C] [ebp-0x44]
  gbVec3D pDir; // [esp+0x190] [ebp-0x40] BYREF
  int v47; // [esp+0x19C] [ebp-0x34]
  gbVec3D pPos; // [esp+0x1A0] [ebp-0x30] BYREF
  int v49; // [esp+0x1AC] [ebp-0x24]
  int v50; // [esp+0x1B0] [ebp-0x20] BYREF
  int v51; // [esp+0x1B4] [ebp-0x1C]
  int v52; // [esp+0x1B8] [ebp-0x18]
  int v53; // [esp+0x1BC] [ebp-0x14]
  int v54; // [esp+0x1C0] [ebp-0x10] BYREF
  int v55; // [esp+0x1C4] [ebp-0xC]
  int v56; // [esp+0x1C8] [ebp-0x8]
  int v57; // [esp+0x1CC] [ebp-0x4]

  v3 = (unsigned long)(pBuffer[1] - 2);
  v40[0] = (unsigned long)(*pBuffer + 15);
  v4 = v40[0] + 42;
  v41 = v40[0] + 42;
  LOBYTE(v4) = g_bDebugMode;
  v40[1] = v3;
  v42 = v3 + 50;
  (*(void ( **)(int *, int *, _DWORD *, MainEquipUI *, char *, int, int))(this->me_Role[4].m_RoleAttCng[1].m_childs.capacity
                                                                                             + 28))(
    &this->me_Role[4].m_RoleAttCng[1].m_childs.capacity,
    &byte_A00403,
    (_DWORD *)(v40),
    this,
    "UI\\GameMainUI\\Prop\\Resume",
    1,
    v4);
  (((PalScript *)&this->me_Role[4].m_RoleAttCng[1].m_childs.capacity))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Resume2.tga", g_bDebugMode);
  sub_445E50((int)&this->me_Role[4].m_RoleAttCng[1].m_childs.capacity);
  LOBYTE(v5) = g_bDebugMode;
  v40[0] = v41 + 11;
  v41 += 53;
  (*(void ( **)(float *, int *, _DWORD *, MainEquipUI *, char *, int, int))(LODWORD(this->me_Role[4].m_RoleAttCng[3].m_ratioh)
                                                                                    + 28))(
    &this->me_Role[4].m_RoleAttCng[3].m_ratioh,
    &byte_A00404,
    (_DWORD *)(v40),
    this,
    "UI\\GameMainUI\\Prop\\Treasure",
    1,
    v5);
  (((PalScript *)&this->me_Role[4].m_RoleAttCng[3].m_ratioh))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Treasure2.tga", g_bDebugMode);
  LOBYTE(v6) = g_bDebugMode;
  v40[0] = v41 + 11;
  v41 += 53;
  ((void ( *)(gbTexture **, int *, _DWORD *, MainEquipUI *, char *, int, int))this->me_Role[4].m_RoleAttCng[5].m_ppic->Height)(
    &this->me_Role[4].m_RoleAttCng[5].m_ppic,
    &byte_A00405,
    v40,
    this,
    "UI\\GameMainUI\\Prop\\Attack",
    1,
    v6);
  (((PalScript *)&this->me_Role[4].m_RoleAttCng[5].m_ppic))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Attack2.tga", g_bDebugMode);
  LOBYTE(v7) = g_bDebugMode;
  v40[0] = v41 + 11;
  v41 += 53;
  (*(void ( **)(gbColorQuad *, int *, _DWORD *, MainEquipUI *, char *, int, int))(this->me_Role[4].m_RoleAttCng[8].m_wndcolor.Color
                                                                                          + 28))(
    &this->me_Role[4].m_RoleAttCng[8].m_wndcolor,
    &byte_A00406,
    (_DWORD *)(v40),
    this,
    "UI\\GameMainUI\\Prop\\Smelt",
    1,
    v7);
  (((PalScript *)&this->me_Role[4].m_RoleAttCng[8].m_wndcolor))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Smelt2.tga", g_bDebugMode);
  LOBYTE(v8) = g_bDebugMode;
  v40[0] = v41 + 11;
  v41 += 53;
  (*(void ( **)(int *, int *, _DWORD *, MainEquipUI *, char *, int, int))(this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel
                                                                                             + 28))(
    &this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel,
    &byte_A00407,
    (_DWORD *)(v40),
    this,
    "UI\\GameMainUI\\Prop\\Ancient",
    1,
    v8);
  (((PalScript *)&this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Ancient2.tga", g_bDebugMode);
  LOBYTE(v9) = g_bDebugMode;
  v40[0] = v41 + 9;
  v41 += 51;
  (*((void ( **)(void **, int *, _DWORD *, MainEquipUI *, char *, int, int))this->me_Role[4].m_RoleAttEqual[2].m_texty
   + 7))(
    &this->me_Role[4].m_RoleAttEqual[2].m_texty,
    &dword_A00408,
    v40,
    this,
    "UI\\GameMainUI\\Prop\\Special",
    1,
    v9);
  (((PalScript *)&this->me_Role[4].m_RoleAttEqual[2].m_texty))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Special2.tga", g_bDebugMode);
  v10 = (unsigned long)*pBuffer;
  v11 = *(_DWORD *)&this->me_Role[4].m_EquipHat.m_caption[16];
  v55 = (unsigned long)(pBuffer[1] + 52);
  v54 = v10 + 18;
  v57 = v55 + 32;
  v56 = v10 + 394;
  (*(void ( **)(char *, int *, int *, MainEquipUI *))(v11 + 16))(
    &this->me_Role[4].m_EquipHat.m_caption[16],
    &byte_ABAB09,
    &v54,
    this);
  (((UIScene *)&this->me_Role[4].m_EquipHat.m_caption[16]))->UIScene::SetShow(0);
  AllocObject(&this->me_Role[4].m_EquipHat.m_caption[16]);
  sprintf(&this->buf[4], "%s                       %s", (const char *)&dword_DC353C, (const char *)&dword_DC373C);
  SetEnable((UICaption *)&this->me_Role[4].m_EquipHat.m_caption[16]);
  v12 = (unsigned long)(pBuffer[1] + 76);
  p_DWORD = (unsigned long)(*pBuffer + 18);
  v37 = v12;
  nHeight = p_DWORD + 298;
  LODWORD(pPos.y) = v12 + 15;
  v13 = p_DWORD + 267;
  v39 = v12 + 288;
  LODWORD(pPos.x) = p_DWORD + 267;
  v49 = v12 + 41;
  LODWORD(pDir.x) = p_DWORD + 267;
  LOBYTE(v13) = g_bDebugMode;
  LODWORD(pDir.y) = v12 + 247;
  LODWORD(pPos.z) = p_DWORD + 289;
  LODWORD(pDir.z) = p_DWORD + 289;
  v47 = v12 + 273;
  v14 = (*(int ( **)(int *, int *, int *, MainEquipUI *, _DWORD, int, int))(this->me_Role[5].m_Jing.m_bcreateok
                                                                                               + 28))(
          &this->me_Role[5].m_Jing.m_bcreateok,
          &byte_A00416,
          &p_DWORD,
          this,
          0,
          1,
          v13);
  LOBYTE(v14) = g_bDebugMode;
  (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v14);
  this->m_ClothName.m_benable = -4;
  this->m_ClothName.m_bfocus = -6;
  this->m_ClothName.pDebugTex = ((gbTexture *)((gbTexture *)10));
  (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo))->CCBUI::ShowEffect(v37 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::SetLockSel(23);
  (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::SetColumnHead((int)"Name", 220);
  (((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo))->CCBUI::VirtualCall(1);
  (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
    &this->me_Role[5].m_Jing.m_bcreateok,
    0);
  LOBYTE(v15) = g_bDebugMode;
  v16 = (*(int ( **)(char *, int *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)&this->m_ClothName.m_text[12]
                                                                                     + 28))(
          &this->m_ClothName.m_text[12],
          &byte_A00417,
          &p_DWORD,
          this,
          0,
          1,
          v15);
  LOBYTE(v16) = g_bDebugMode;
  (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v16);
  this->m_RemarkVal.m_nTextW = -4;
  *((_DWORD *)&this->m_RemarkVal + 38) = -6;
  *((_DWORD *)&this->m_RemarkVal + 39) = 10;
  (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&this->m_ShoesName.m_rect.bottom))->CCBUI::ShowEffect(v37 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&this->m_ShoesName.m_rect.bottom))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->m_ShoesName.m_rect.bottom))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->m_ShoesName.m_rect.bottom))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::SetLockSel(23);
  (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::SetColumnHead((int)"Name", 220);
  (((UIListBox *)&this->m_ClothName.m_text[12]))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((CCBUI *)&this->m_ShoesName.m_rect.bottom))->CCBUI::VirtualCall(1);
  (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])((char *)(&this->m_ClothName.m_text[12]), (_DWORD)(0));
  LOBYTE(v17) = g_bDebugMode;
  v18 = (*((int ( **)(PtrArray *, int *, int *, MainEquipUI *, _DWORD, int, int))this->m_typeWord.m_childs.m_pData
         + 7))(
          &this->m_typeWord.m_childs,
          &byte_A00418,
          &p_DWORD,
          this,
          0,
          1,
          v17);
  LOBYTE(v18) = g_bDebugMode;
  (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v18);
  *(_DWORD *)((char *)&this->m_role[1].Remark.skillCount + 162) = -4;
  *(_DWORD *)((char *)&this->m_role[1].Remark.skillCount + 166) = -6;
  *(_DWORD *)((char *)&this->m_role[1].Remark.skillCount + 170) = 10;
  (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&this->m_typeWord.m_pbkInfo))->CCBUI::ShowEffect(v37 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&this->m_typeWord.m_pbkInfo))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->m_typeWord.m_pbkInfo))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->m_typeWord.m_pbkInfo))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::SetLockSel(23);
  (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::SetColumnHead((int)"Name", 220);
  (((UIListBox *)&this->m_typeWord.m_childs))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((CCBUI *)&this->m_typeWord.m_pbkInfo))->CCBUI::VirtualCall(1);
  (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
  LOBYTE(v19) = g_bDebugMode;
  v20 = (*(int ( **)(char *, int *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)((char *)&this->m_role[1].Remark.skillCount
                                                                                                 + 210)
                                                                                     + 28))(
          (char *)&this->m_role[1].Remark.skillCount + 210,
          &byte_A00419,
          &p_DWORD,
          this,
          0,
          1,
          v19);
  LOBYTE(v20) = g_bDebugMode;
  (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v20);
  *(_DWORD *)&this->m_role[2].ModelID[6] = -4;
  *(_DWORD *)&this->m_role[2].ModelID[10] = -6;
  *(_DWORD *)&this->m_role[2].ModelID[14] = 10;
  (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&this->m_role[1].Remark.skillCount.skillCount))->CCBUI::ShowEffect(v37 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&this->m_role[1].Remark.skillCount.skillCount))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->m_role[1].Remark.skillCount.skillCount))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->m_role[1].Remark.skillCount.skillCount))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::SetLockSel(23);
  (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::SetColumnHead((int)"Name", 220);
  (((UIListBox *)((char *)&this->m_role[1].Remark.skillCount + 210)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((CCBUI *)&this->m_role[1].Remark.skillCount.skillCount))->CCBUI::VirtualCall(1);
  (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[1].Remark.skillCount + 210))((char *)((char *)&this->m_role[1].Remark.skillCount + 210), (_DWORD)(0));
  LOBYTE(v21) = g_bDebugMode;
  v22 = (*(int ( **)(char *, int *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)&this->m_role[2].ImageID[24]
                                                                                     + 28))(
          &this->m_role[2].ImageID[24],
          &byte_A00420,
          &p_DWORD,
          this,
          0,
          1,
          v21);
  LOBYTE(v22) = g_bDebugMode;
  (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v22);
  *(_DWORD *)((char *)&this->m_role[4].Remark.skillCount + 22) = -4;
  *(_DWORD *)((char *)&this->m_role[4].Remark.skillCount + 26) = -6;
  *(_DWORD *)((char *)&this->m_role[4].Remark.skillCount + 30) = 10;
  (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&this->m_role[2].rolevalue[4]))->CCBUI::ShowEffect(v37 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&this->m_role[2].rolevalue[4]))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->m_role[2].rolevalue[4]))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->m_role[2].rolevalue[4]))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::SetLockSel(23);
  (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::SetColumnHead((int)"Name", 220);
  (((UIListBox *)&this->m_role[2].ImageID[24]))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((CCBUI *)&this->m_role[2].rolevalue[4]))->CCBUI::VirtualCall(1);
  (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])((char *)(&this->m_role[2].ImageID[24]), (_DWORD)(0));
  LOBYTE(v23) = g_bDebugMode;
  v24 = (*(int ( **)(char *, int *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)((char *)&this->m_role[4].Remark.skillCount
                                                                                                 + 70)
                                                                                     + 28))(
          (char *)&this->m_role[4].Remark.skillCount + 70,
          &byte_A00421,
          &p_DWORD,
          this,
          0,
          1,
          v23);
  LOBYTE(v24) = g_bDebugMode;
  (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v24);
  this->m_Dlg.m_static.m_ratioh = NAN;
  this->m_Dlg.m_static.m_textx = ((void *)((void *)-6));
  this->m_Dlg.m_static.m_texty = ((void *)((void *)10));
  (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)((char *)&this->m_role[4].Remark.skillCount + 150)))->CCBUI::ShowEffect(v37 + 1, nHeight - 38, nHeight);
  (((CCBUI *)((char *)&this->m_role[4].Remark.skillCount + 150)))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)((char *)&this->m_role[4].Remark.skillCount + 150)))->CCBUI::SetSelection(27);
  (((CCBUI *)((char *)&this->m_role[4].Remark.skillCount + 150)))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::SetLockSel(23);
  (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::SetColumnHead((int)"Name", 220);
  (((UIListBox *)((char *)&this->m_role[4].Remark.skillCount + 70)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((CCBUI *)((char *)&this->m_role[4].Remark.skillCount + 150)))->CCBUI::VirtualCall(1);
  (**(void ( ***)(char *, _DWORD))((char *)&this->m_role[4].Remark.skillCount + 70))((char *)((char *)&this->m_role[4].Remark.skillCount + 70), (_DWORD)(0));
  v51 = v37 + 2;
  v50 = p_DWORD;
  v52 = p_DWORD + 256;
  v53 = v37 + 25;
  v25 = (UIPushButton *)&this->me_Role[4].m_EquipCloth.m_caption[60];
  v26 = 12;
  do
  {
    (*(void ( **)(UIPushButton *, int, int *, MainEquipUI *))(*(_DWORD *)((UIWnd *)v25) + 16))(
      v25,
      161,
      &v50,
      this);
    LOBYTE(v27) = g_bDebugMode;
    (((UIPushButton *)v25))->UIPushButton::CreateFromTemplate(String2, v27);
    v25 = (UIPushButton *)((char *)v25 + 152);
    v51 = v53;
    --v26;
    v53 += 23;
  }
  while ( v26 );
  v28 = (unsigned long)*pBuffer;
  v29 = *((_DWORD *)&this->m_Dlg.m_btRc + 39);
  v43[1] = v39 + 3;
  v30 = v39 + 23;
  v45 = v39 + 23;
  LOBYTE(v30) = g_bDebugMode;
  v43[0] = v28 + 20;
  v44 = v28 + 114;
  (*(void ( **)(char *, int *, _DWORD *, MainEquipUI *, char *, int, int))(v29 + 28))(
    (char *)&this->m_Dlg.m_btRc + 156,
    &byte_A00427,
    (_DWORD *)(v43),
    this,
    "UI\\GameMainUI\\Communal\\SortUse",
    1,
    v30);
  v31 = *((_DWORD *)&this->m_Dlg.pCallbackVtable2 + 39);
  v43[0] = v44 + 8;
  v44 += 102;
  v32 = v44;
  LOBYTE(v32) = g_bDebugMode;
  (*(void ( **)(void **, int *, _DWORD *, MainEquipUI *, char *, int, int))(v31 + 28))(
    &this->m_Dlg.pCallbackVtable2 + 39,
    &byte_A00428,
    (_DWORD *)(v43),
    this,
    "UI\\GameMainUI\\Communal\\SortPrice",
    1,
    v32);
  v33 = *(_DWORD *)&this->m_Ctrlbtn[0].m_bBigFont;
  v43[0] = v44 + 8;
  v44 += 102;
  v34 = v44;
  LOBYTE(v34) = g_bDebugMode;
  return (*(int ( **)(_BYTE *, int *, _DWORD *, MainEquipUI *, char *, int, int))(v33 + 28))(
           &this->m_Ctrlbtn[0].m_bBigFont,
           &byte_A00429,
           (_DWORD *)(v43),
           this,
           "UI\\GameMainUI\\Communal\\SortFunc",
           1,
           v34);
}

// 0x0049F2E0
void * MainEquipUI::CreateListPanel(int FC)
{
  LONG bkWndX; // eax
  LONG bkWndY; // ecx
  int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  unsigned int Color; // eax
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  LONG right; // eax
  int v17; // edx
  LONG v18; // edx
  LONG v19; // eax
  int capacity; // edx
  int v21; // ecx
  gbTexture *v22; // eax
  int v23; // edx
  LONG left; // edx
  void *result; // eax
  int v26; // [esp+0x60] [ebp-0x94]
  int *v27; // [esp+0x64] [ebp-0x90]
  int v28; // [esp+0x68] [ebp-0x8C]
  int v29; // [esp+0x74] [ebp-0x80] BYREF
  int v30; // [esp+0x78] [ebp-0x7C]
  int v31; // [esp+0x7C] [ebp-0x78]
  int v32; // [esp+0x80] [ebp-0x74]
  int v33; // [esp+0x84] [ebp-0x70] BYREF
  int v34; // [esp+0x88] [ebp-0x6C]
  int v35; // [esp+0x8C] [ebp-0x68]
  int v36; // [esp+0x90] [ebp-0x64]
  int v37; // [esp+0x94] [ebp-0x60] BYREF
  int v38; // [esp+0x98] [ebp-0x5C]
  int v39; // [esp+0x9C] [ebp-0x58]
  int v40; // [esp+A0h] [ebp-0x54]
  int pnVal; // [esp+A4h] [ebp-0x50] BYREF
  int v42; // [esp+A8h] [ebp-0x4C]
  int v43; // [esp+ACh] [ebp-0x48]
  int v44; // [esp+B0h] [ebp-0x44]
  int pBuffer; // [esp+B4h] [ebp-0x40] BYREF
  int v46; // [esp+B8h] [ebp-0x3C]
  int v47; // [esp+BCh] [ebp-0x38]
  int v48; // [esp+C0h] [ebp-0x34]
  int nVal2[4]; // [esp+C4h] [ebp-0x30] BYREF
  _DWORD v50[4]; // [esp+D4h] [ebp-0x20] BYREF
  _DWORD v51[4]; // [esp+E4h] [ebp-0x10] BYREF

  bkWndX = this->bkWndX;
  bkWndY = this->bkWndY;
  this->rc.right = bkWndX;
  this->rc.top = 0;
  this->rc.left = 0;
  this->rc.bottom = bkWndY;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom) /* [ROWTABLE] */;
  v5 = this->rc.top + 18;
  v37 = this->rc.left + 592;
  v38 = v5;
  v39 = v37 + 192;
  v40 = v5 + 526;
  (*(void ( **)(_PlugInfo **, int, int *, MainEquipUI *))&this->m_TimeMoney.m_pbkInfo->name[12])(
    &this->m_TimeMoney.m_pbkInfo,
    161,
    &v37,
    this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&this->m_TimeMoney.m_pbkInfo))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Prop\\Frame.tga", v6);
  v7 = *(_DWORD *)&this->m_TopFrame.m_text[12];
  v38 += 26;
  v37 = v39;
  v40 = v38 + 526;
  v39 += 17;
  (*(void ( **)(char *, int, int *, MainEquipUI *))(v7 + 16))(&this->m_TopFrame.m_text[12], 161, &v37, this);
  LOBYTE(v8) = g_bDebugMode;
  (((UIPushButton *)&this->m_TopFrame.m_text[12]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Frame_Line.tga", v8);
  v30 = 0;
  v29 = v39 - 205;
  v31 = v39 - 205 + 203;
  v9 = *(_DWORD *)&this->m_TopFrameZB.m_text[4];
  v32 = 64;
  (*(void ( **)(char *, int, int *, MainEquipUI *))(v9 + 16))(&this->m_TopFrameZB.m_text[4], 161, &v29, this);
  LOBYTE(v10) = g_bDebugMode;
  (((UIPushButton *)&this->m_TopFrameZB.m_text[4]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\TimeMoney.tga", v10);
  Color = this->stp_Effect.m_wndcolor.Color;
  v30 = -4;
  v29 = 618;
  v31 = 738;
  v32 = 28;
  (*(void ( **)(gbColorQuad *, int, int *, MainEquipUI *))(Color + 16))(
    &this->stp_Effect.m_wndcolor,
    161,
    &v29,
    this);
  (((UIScene *)&this->stp_Effect.m_wndcolor))->UIScene::SetShow(0);
  AllocObject(&this->stp_Effect.m_wndcolor);
  v12 = *(_DWORD *)&this->stp_Exit.m_caption[8];
  v30 = 16;
  v29 = 668;
  v31 = 748;
  v32 = 48;
  (*(void ( **)(char *, int, int *, MainEquipUI *))(v12 + 16))(&this->stp_Exit.m_caption[8], 161, &v29, this);
  (((UIScene *)&this->stp_Exit.m_caption[8]))->UIScene::SetShow(0);
  AllocObject(&this->stp_Exit.m_caption[8]);
  (((LineupUI *)this))->LineupUI::RebuildCaptionPage() /* [ROWTABLE] */;
  v42 = 0;
  pnVal = 0;
  v43 = 0;
  v44 = 32;
  nVal2[1] = 0;
  nVal2[0] = 12;
  nVal2[2] = 590;
  nVal2[3] = 126;
  this->i = 0;
  do
  {
    (((UITitle_XJTM *)this))->UITitle_XJTM::UpdateMonsterEntry2(this->i, &pnVal);
    (((ArcSceneMonster *)this))->ArcSceneMonster::CreateStatusPanel(this->i, (int)nVal2, v26, v27, v28);
    v13 = this->i + 1;
    this->i = v13;
  }
  while ( v13 < 5 );
  this->i = 0;
  do
  {
    (*(void ( **)(char *, _DWORD, int *, MainEquipUI *))(*(_DWORD *)&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i]
                                                                 + 16))(
      &this->me_Role[2].m_AttFramePose.m_text[4892 * this->i],
      (_DWORD)(*(&g_ArcSceneMonsterTable2 + this->i)),
      (int *)(nVal2),
      this);
    LOBYTE(v14) = g_bDebugMode;
    (((UIPushButton *)&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\NeedArrow.tga", v14);
    (**(void ( ***)(char *, _DWORD))&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i])((char *)(&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i]), (_DWORD)(0));
    v15 = this->i + 1;
    this->i = v15;
  }
  while ( v15 < 5 );
  right = this->me_Role[4].m_RoleAtt[6].m_rect.right;
  v34 = 125;
  v33 = 10;
  v35 = 242;
  v36 = 539;
  (*(void ( **)(LONG *, int *, int *, MainEquipUI *))(right + 16))(
    &this->me_Role[4].m_RoleAtt[6].m_rect.right,
    &byte_A00401,
    &v33,
    this);
  LOBYTE(v17) = g_bDebugMode;
  (((UIPushButton *)&this->me_Role[4].m_RoleAtt[6].m_rect.right))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Info.tga", v17);
  v18 = this->me_Role[4].m_RoleAtt[7].m_rect.right;
  v34 = 372;
  v33 = 22;
  v35 = 234;
  v36 = 540;
  (*(void ( **)(LONG *, int *, int *, MainEquipUI *))(v18 + 16))(
    &this->me_Role[4].m_RoleAtt[7].m_rect.right,
    &byte_A00401,
    &v33,
    this);
  (((UIScene *)&this->me_Role[4].m_RoleAtt[7].m_rect.right))->UIScene::SetShow(0);
  AllocObject(&this->me_Role[4].m_RoleAtt[7].m_rect.right);
  v19 = this->me_Role[4].m_RoleAtt[8].m_rect.right;
  v34 = 504;
  v33 = 22;
  v35 = 234;
  v36 = 536;
  (*(void ( **)(LONG *, int *, int *, MainEquipUI *))(v19 + 16))(
    &this->me_Role[4].m_RoleAtt[8].m_rect.right,
    &byte_A00401,
    &v33,
    this);
  (((UIScene *)&this->me_Role[4].m_RoleAtt[8].m_rect.right))->UIScene::SetShow(0);
  AllocObject(&this->me_Role[4].m_RoleAtt[8].m_rect.right);
  capacity = this->me_Role[4].m_RoleAtt[9].m_childs.capacity;
  v50[1] = 142;
  v50[0] = 195;
  v50[2] = 211;
  v50[3] = 174;
  (*(void ( **)(int *, int *, _DWORD *, MainEquipUI *))(capacity + 16))(
    &this->me_Role[4].m_RoleAtt[9].m_childs.capacity,
    &byte_A00401,
    (_DWORD *)(v50),
    this);
  LOBYTE(v21) = g_bDebugMode;
  (((UIPushButton *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Resume_word.tga", v21);
  v22 = (gbTexture *)this->me_Role[4].m_EquipCloth.m_texarray.m_ptex[1];
  v46 = 125;
  pBuffer = 251;
  v47 = 587;
  v48 = 518;
  ((void ( *)(gbTexture **, int, int *, MainEquipUI *))v22->IsLoaded)(
    &this->me_Role[4].m_EquipCloth.m_texarray.m_ptex[1],
    161,
    &pBuffer,
    this);
  LOBYTE(v23) = g_bDebugMode;
  (((UIPushButton *)&this->me_Role[4].m_EquipCloth.m_texarray.m_ptex[1]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ListFrame.tga", v23);
  left = this->me_Role[4].m_EquipCloth.m_rect.left;
  v51[1] = v46;
  v51[0] = pBuffer + 7;
  v51[3] = v46 + 32;
  v51[2] = pBuffer + 327;
  (*(void ( **)(tagRECT *, int *, _DWORD *, char *, _DWORD, MainEquipUI *))(left + 28))(
    &this->me_Role[4].m_EquipCloth.m_rect,
    &byte_A00400,
    (_DWORD *)(v51),
    "UI\\Flex\\Bar.tga",
    0,
    this);
  (((CScreenMode *)&this->me_Role[4].m_EquipCloth.m_rect))->CScreenMode::SetPosition(32,   32);
  this->MainEquipUI::CreateFromData(&pBuffer);
  (((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&dword_A00430, (int)this);
  if ( !strcmp("D16", unk_C10D38) )
    sprintf(&this->buf[4], "%s", "NONE");
  else
    sprintf(&this->buf[4], "Item\\%s\\%s.pol", "D16", "D16");
  (((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1]))->PalScript::LoadModel(&this->buf[4], 0);
  this->m_Ctrlbtn[1].m_texarrayInfo[2] = 0;
  this->m_Ctrlbtn[1].m_texarrayInfo[0] = (_PlugInfo *)1;
  (((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray))->CCBFiveNimbusWindow::SetFloatParam(160.0);
  (((Camera *)&this->m_Ctrlbtn[1].m_texarray))->Camera::UpdateCameraLookAt(128, 258, 600);
  sub_43A090((int)&this->m_Ctrlbtn[1].m_texarray, 1, 0.0);
  pnVal = 300;
  v44 = 300;
  v42 = 200;
  v43 = 500;
  Create__ovl_1((ARC_PlayerAtt *)&this->me_Role[1].m_RoleAttEqual[1].m_pfather);
  result = (((UIItem *)&this->me_Role[1].m_RoleAttEqual[1].m_pfather))->UIItem::SetData(31);
  BYTE1(this->m_TimeMoney.m_texty) = 1;
  this->m_TimeMoney.m_pbk = ((gbTexture *)((gbTexture *)FC));
  return result;
}

// 0x004A4ED0
int MainEquipUI::ShowPage()
{
  char *v2; // ebx

  v2 = (char *)&this->m_OutFrameT.m_text[8];
  (((PalScript *)&this->m_OutFrameT.m_text[8]))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnState.tga", g_bDebugMode);
  if ( !g_bRoleFlag1 )
    (((PalScript *)&this->stp_Magic.m_bBigFont))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_Magic.m_bBigFont);
  if ( !g_bRoleFlag2 )
    (((PalScript *)&this->stp_Equip.m_bBigFont))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_Equip.m_bBigFont);
  sub_445E50((int)v2);
  sub_445E50((int)&this->m_OutFrameL.m_disablepic);
  sub_445E50((int)(&this->stp_BarL + 1));
  sub_445E50((int)&this->stp_State.m_bBigFont);
  sub_445E50((int)&this->stp_Prop.m_bBigFont);
  sub_445E50((int)&this->stp_BattleArray.m_bBigFont);
  return sub_445E50((int)&this->stp_TaskBook.m_bBigFont);
}

// 0x004A5010
BOOL MainEquipUI::HandleMessage(int a1)
{
  BOOL result; // eax
  unsigned int m_id; // ecx
  LONG left; // ecx
  LONG top; // ecx
  LONG right; // ecx
  unsigned int Color; // ecx
  LONG bottom; // ecx
  unsigned int v10; // ecx
  LONG v11; // ecx
  LONG v12; // ecx
  LONG v13; // ecx
  unsigned int v14; // ecx
  unsigned int v15; // ecx
  LONG v16; // ecx
  LONG v17; // ecx
  LONG v18; // ecx
  unsigned int v19; // ecx
  unsigned int v20; // ecx
  LONG v21; // ecx
  LONG v22; // ecx
  LONG v23; // ecx
  unsigned int v24; // ecx
  unsigned int v25; // ecx
  LONG v26; // ecx
  LONG v27; // ecx
  LONG v28; // ecx
  unsigned int v29; // ecx
  unsigned int v30; // ecx
  LONG v31; // ecx
  LONG v32; // ecx
  LONG v33; // ecx
  unsigned int v34; // ecx
  LONG v35; // ecx
  unsigned int v36; // ecx
  LONG v37; // ecx
  LONG v38; // ecx
  LONG v39; // ecx
  unsigned int v40; // ecx
  LONG v41; // ecx
  UIWnd *m_pfather; // ecx
  unsigned int v43; // ecx
  LONG v44; // ecx
  LONG v45; // ecx
  LONG v46; // ecx
  unsigned int v47; // ecx
  LONG v48; // ecx
  UIWnd *v49; // ecx
  unsigned int v50; // ecx
  LONG v51; // ecx
  LONG v52; // ecx
  LONG v53; // ecx
  unsigned int v54; // ecx
  unsigned int v55; // ecx
  LONG v56; // ecx
  LONG v57; // ecx
  LONG v58; // ecx
  unsigned int v59; // ecx
  LONG v60; // ecx
  UIWnd *v61; // ecx

  result = a1;
  this->me_Role[3].m_EquipShoes.m_childs.m_pData = (char *)a1;
  switch ( a1 )
  {
    case 0:
      LOBYTE(gfxMgr->pSceneGraph->pnodebuf[713]) = 0;
      result = (*(int ( **)(MainEquipUI *, int, int, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(this, 1000, 1, 0);
      m_id = this->me_Role[3].m_EquipShoes.m_id;
      if ( m_id )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)m_id + 24))(m_id, 1000, 0, 0);
      left = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( left )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)left + 24))(left, 1000, 0, 0);
      top = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( top )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)top + 24))(top, 1000, 0, 0);
      right = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( right )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)right + 24))(right, 1000, 0, 0);
      Color = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( Color )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)Color + 24))(
                   Color,
                   1000,
                   0,
                   0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( !bottom )
        break;
      goto LABEL_115;
    case 1:
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v20 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v20 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v20 + 24))(v20, 1000, 0, 0);
      v21 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v21 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v21 + 24))(v21, 1000, 0, 0);
      v22 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v22 )
        result = (*(int ( **)(LONG, int, int, _DWORD))(*(_DWORD *)v22 + 24))(v22, 1000, 1, 0);
      v23 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v23 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v23 + 24))(v23, 1000, 0, 0);
      v24 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v24 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v24 + 24))(v24, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 2:
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v15 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v15 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v15 + 24))(v15, 1000, 0, 0);
      v16 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v16 )
        result = (*(int ( **)(LONG, int, int, _DWORD))(*(_DWORD *)v16 + 24))(v16, 1000, 1, 0);
      v17 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v17 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v17 + 24))(v17, 1000, 0, 0);
      v18 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v18 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v18 + 24))(v18, 1000, 0, 0);
      v19 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v19 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v19 + 24))(v19, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 3:
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v10 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v10 )
        result = (*(int ( **)(unsigned int, int, int, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1000, 1, 0);
      v11 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v11 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 0, 0);
      v12 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v12 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 0, 0);
      v13 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v13 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v13 + 24))(v13, 1000, 0, 0);
      v14 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v14 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v14 + 24))(v14, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 4:
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v36 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v36 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v36 + 24))(v36, 1000, 0, 0);
      v37 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v37 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v37 + 24))(v37, 1000, 0, 0);
      v38 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v38 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v38 + 24))(v38, 1000, 0, 0);
      v39 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v39 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v39 + 24))(v39, 1000, 0, 0);
      v40 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v40 )
        result = (*(int ( **)(unsigned int, int, int, _DWORD))(*(_DWORD *)v40 + 24))(v40, 1000, 1, 0);
      v41 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v41 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v41 + 24))(v41, 1000, 0, 0);
      m_pfather = this->me_Role[3].m_EquipShoes.m_pfather;
      if ( m_pfather )
        return m_pfather->OnMessage(1000, 0, 0);
      return result;
    case 5:
      LOBYTE(result) = g_bRoleFlag1;
      if ( !g_bRoleFlag1 )
        return result;
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v25 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v25 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v25 + 24))(v25, 1000, 0, 0);
      v26 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v26 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v26 + 24))(v26, 1000, 0, 0);
      v27 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v27 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v27 + 24))(v27, 1000, 0, 0);
      v28 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v28 )
        result = (*(int ( **)(LONG, int, int, _DWORD))(*(_DWORD *)v28 + 24))(v28, 1000, 1, 0);
      v29 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v29 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v29 + 24))(v29, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
LABEL_115:
        result = (*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)bottom + 24))(1000, 0, 0);
      break;
    case 6:
      LOBYTE(result) = g_bRoleFlag2;
      if ( !g_bRoleFlag2 )
        return result;
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v30 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v30 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v30 + 24))(v30, 1000, 0, 0);
      v31 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v31 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v31 + 24))(v31, 1000, 0, 0);
      v32 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v32 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v32 + 24))(v32, 1000, 0, 0);
      v33 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v33 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v33 + 24))(v33, 1000, 0, 0);
      v34 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v34 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v34 + 24))(v34, 1000, 0, 0);
      v35 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v35 )
        result = (*(int ( **)(int, int, _DWORD))(*(_DWORD *)v35 + 24))(1000, 1, 0);
      break;
    case 7:
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v43 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v43 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v43 + 24))(v43, 1000, 0, 0);
      v44 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v44 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v44 + 24))(v44, 1000, 0, 0);
      v45 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v45 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v45 + 24))(v45, 1000, 0, 0);
      v46 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v46 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v46 + 24))(v46, 1000, 0, 0);
      v47 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v47 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v47 + 24))(v47, 1000, 0, 0);
      v48 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v48 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v48 + 24))(v48, 1000, 0, 0);
      v49 = this->me_Role[3].m_EquipShoes.m_pfather;
      if ( v49 )
        return v49->OnMessage(1000, 1, 0);
      return result;
    case 8:
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v50 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v50 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v50 + 24))(v50, 1000, 0, 0);
      v51 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v51 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v51 + 24))(v51, 1000, 0, 0);
      v52 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v52 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v52 + 24))(v52, 1000, 0, 0);
      v53 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v53 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v53 + 24))(v53, 1000, 0, 0);
      v54 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v54 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v54 + 24))(v54, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 9:
      result = (*(int ( **)(MainEquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1000,
                 0,
                 0);
      v55 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v55 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v55 + 24))(v55, 1000, 0, 0);
      v56 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v56 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v56 + 24))(v56, 1000, 0, 0);
      v57 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v57 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v57 + 24))(v57, 1000, 0, 0);
      v58 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v58 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v58 + 24))(v58, 1000, 0, 0);
      v59 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v59 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v59 + 24))(v59, 1000, 0, 0);
      v60 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v60 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v60 + 24))(v60, 1000, 0, 0);
      v61 = this->me_Role[3].m_EquipShoes.m_pfather;
      if ( v61 )
        result = v61->OnMessage(1000, 0, 0);
      LOBYTE(result) = BYTE1(this->me_Role[3].m_EquipShoes.m_childs.capacity);
      *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4] = 0;
      if ( result )
      {
        g_bRoleSystem_5CEFA9 = this->me_Role[3].m_EquipShoes.m_childs.capacity;
        BYTE1(this->me_Role[3].m_EquipShoes.m_childs.capacity) = 0;
      }
      return result;
    case 10:
      *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4] = 0;
      return result;
    default:
      return result;
  }
  m_pfather = this->me_Role[3].m_EquipShoes.m_pfather;
  if ( m_pfather )
    return m_pfather->OnMessage(1000, 0, 0);
  return result;
}
