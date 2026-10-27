#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIScenePanel.h"
#include "Role/Actor.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBUI.h"
#include "Misc/CCBUIPanel.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Misc/ChoseCompose.h"
#include "Misc/NameSys.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/Parent_Data.h"
#include "Misc/RoleShadow.h"
#include "Role/RoleSystem.h"
#include "Misc/SoundMgr.h"
#include "Misc/TaskBookUI.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIBigMap.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UIStatic.h"
#include "Misc/UITitle_XJTM.h"
#include "UI/UIWnd.h"
#include "Misc/_Texture_Info.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

class TextureLibDataBase;

// Unnamed globals (extern)
extern LPCSTR off_59DD08;
extern LPCSTR off_59DD0C;
extern LPCSTR off_59DD10;
extern LPCSTR off_59DD14;
extern LPCSTR off_59DDCC;
extern LPCSTR off_59DDD0;
extern LPCSTR off_59DDD4;
extern LPCSTR off_59DDDC;
extern TextureLibDataBase stru_1894B78;

// 0x0043B4D0
UIScenePanel::~UIScenePanel()
{
  if ( this->m_SlotData )
  {
    operator delete((void *)this->m_SlotData);
    this->m_SlotData = 0;
  }
  (((UICaption *)this))->UICaption::Destroy2() /* [ROWTABLE] */;
}

// 0x0043B570
int UIScenePanel::CreateLabelWidget(
        
        int id,
        void *pRect,
        int parent,
        LPCSTR lpString,
        char a6)
{
  int result; // eax
  const CHAR *v8; // edi
  CHAR *v9; // eax

  result = parent;
  if ( parent )
  {
    v8 = lpString;
    if ( lpString )
    {
      ((OpenBaseFile *)&lpString)->OpenBaseFile::OpenBaseFile();
      this->m_bVisible = ((Parent_Data *)0);
      this->m_hFont = 0;
      this->m_bEnabled = ((Parent_Data *)0);
      *(_DWORD *)&this->m_bOverlayRender = 0;
      if ( a6 )
      {
        this->m_bVisible = ((Parent_Data *)((((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(v8)));
        v9 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(v8);
        if ( !LoadUISceneTexture((int)v9, 1) )
        {
LABEL_5:
          (((UIWnd *)&this->m_nClipW))->UIWnd::MoveWindow();
LABEL_8:
          ((OpenNULLFile *)&lpString)->OpenNULLFile::OpenNULLFile();
          return result;
        }
      }
      else if ( !LoadUISceneTexture((int)v8, 2) )
      {
        goto LABEL_5;
      }
      this->UIWnd::Create(id, (tagRECT *)pRect, parent);
      goto LABEL_8;
    }
  }
  return result;
}

// 0x0044BA60
UIScenePanel::UIScenePanel()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  (((UIFrameContainer *)&this->m_Static_360))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_10496))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_10648))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_10800))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_10952))->UIFrameContainer::ResetContainerState();
  (((CCBResultWindow *)&this->m_nTodo_11116))->CCBResultWindow::Create();
  (((CCBResultWindow *)&this->m_nTodo_11308))->CCBResultWindow::Create();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  *(&this->m_hSettingsUI + 1) = 0;
  *(_DWORD *)&this->m_bPanelFlagA = 0;
  this->m_nPanelState = 0;
  this->m_nSceneIdx = 0;
  this->m_bFlags0 = 1;
  this->m_bFlags1 = 1;
  *(&this->m_bFlags1 + 1) = 0;
  (((UIFrameContainer *)&this->m_Static_13904))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_14080))->UIFrameContainer::ResetContainerState();
  this->m_fScaleX = 0.0;
  this->m_fScaleY = 0.0;
  *(_DWORD *)&this->m_nTodo_050 = 800;
  this->m_nScrollState = 600;
  *((_BYTE *)&this->m_nObjStore + 4) = 0;
  *((_BYTE *)&this->m_nObjStore + 5) = 0;
  *(&this->m_nObjStore + 2) = 0;
  *(&this->m_nObjStore + 3) = 0;
  this->m_hSettingsUI = 0;
}

// 0x0044C120
void UIScenePanel::CreateSettingsUI()
{
  float *p_m_fScaleY; // ebp
  int v3; // edx
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int m_nTodo_11116; // edx
  int v13; // ecx
  int m_nTodo_11308; // eax
  int v15; // edx
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  CCBRoleState *v29; // eax
  CCBRoleState *v30; // eax
  CCBUIPanel *v31; // eax
  RoleShadow *v32; // eax
  TaskBookUI *v33; // eax
  int v34; // eax
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v37; // edi
  CScreenMode *v38; // eax
  UICursor *v39; // ecx
  void *m_nPanelState; // eax
  void *v41; // edi
  unsigned int v42; // edx
  BYTE Data[4]; // [esp+E4h] [ebp-0x68] BYREF
  BYTE v44[4]; // [esp+E8h] [ebp-0x64] BYREF
  BYTE v45[4]; // [esp+ECh] [ebp-0x60] BYREF
  int v46; // [esp+F0h] [ebp-0x5C] BYREF
  int v47; // [esp+F4h] [ebp-0x58]
  int v48; // [esp+F8h] [ebp-0x54]
  int v49; // [esp+FCh] [ebp-0x50]
  int v50; // [esp+0x100] [ebp-0x4C] BYREF
  int v51; // [esp+0x104] [ebp-0x48]
  int v52; // [esp+0x108] [ebp-0x44]
  int v53; // [esp+0x10C] [ebp-0x40]
  int v54; // [esp+0x110] [ebp-0x3C] BYREF
  int v55; // [esp+0x114] [ebp-0x38]
  int v56; // [esp+0x118] [ebp-0x34]
  int v57; // [esp+0x11C] [ebp-0x30]
  _DWORD v58[4]; // [esp+0x120] [ebp-0x2C] BYREF
  _DWORD v59[4]; // [esp+0x130] [ebp-0x1C] BYREF
  int v60; // [esp+0x148] [ebp-0x4]

  p_m_fScaleY = (float *)&this->m_fScaleY;
  (((UIListBox *)this))->UIListBox::SetSelTexture(0, LODWORD(this->m_fScaleY), LODWORD(this->m_fScaleX), *(_DWORD *)&this->m_nTodo_050, this->m_nScrollState) /* [ROWTABLE] */;
  g_nSceneState = 1;
  v3 = (int)((UIWnd *)&this->m_Static_360);
  v58[1] = 80;
  v58[0] = 169;
  v58[2] = 611;
  v58[3] = 526;
  (*(void ( **)(UIStatic *, _DWORD, _DWORD *, UIScenePanel *))(v3 + 16))(&this->m_Static_360, 0, (_DWORD *)(v58), this);
  LOBYTE(v4) = g_bSceneLoaded;
  (((UIPushButton *)&this->m_Static_360))->UIPushButton::CreateFromTemplate((void *)off_59DD0C, v4);
  (((RoleSystem *)this))->RoleSystem::InitUICtrlArray() /* [ROWTABLE] */;
  v5 = (int)((UIWnd *)&this->m_Static_10496);
  v51 = 192;
  v50 = 79;
  v52 = 409;
  v53 = 424;
  (*(void ( **)(UIStatic *, _DWORD, int *, UIScenePanel *))(v5 + 16))(&this->m_Static_10496, 0, &v50, this);
  LOBYTE(v6) = g_bSceneLoaded;
  (((UIPushButton *)&this->m_Static_10496))->UIPushButton::CreateFromTemplate((void *)off_59DD10, v6);
  (((UITitle_XJTM *)this))->UITitle_XJTM::CreateSubWidgets();
  v7 = (int)((UIWnd *)&this->m_Static_10648);
  v51 = 203;
  v50 = 556;
  v52 = 610;
  v53 = 318;
  (*(void ( **)(UIStatic *, _DWORD, int *, UIScenePanel *))(v7 + 16))(&this->m_Static_10648, 0, &v50, this);
  LOBYTE(v8) = g_bSceneLoaded;
  (((UIPushButton *)&this->m_Static_10648))->UIPushButton::CreateFromTemplate((void *)off_59DD14, v8);
  InitParticles((Actor *)this);
  v9 = (int)((UIWnd *)&this->m_Static_14080);
  this->m_fAnimRate = 1099264164;
  this->m_fAnimBase = 1140948992;
  this->m_nCoverTop = 518;
  this->m_nCoverLeft = 220;
  this->m_nCoverRight = 586;
  this->m_nCoverBottom = 1542;
  (*(void ( **)(UIStatic *, _DWORD, int *, UIScenePanel *))(v9 + 16))(
    &this->m_Static_14080,
    0,
    &this->m_nCoverLeft,
    this);
  (((UIPushButton *)&this->m_Static_14080))->UIPushButton::CreateFromTemplate((void *)off_59DDDC, 0);
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)&this->m_Static_14080))((UIStatic *)(&this->m_Static_14080), (_DWORD)(0));
  v10 = (int)((UIWnd *)&this->m_Static_10952);
  *(_BYTE *)((UIWnd *)&this[1]) = 0;
  v59[1] = 223;
  v59[0] = 200;
  v59[2] = 581;
  v59[3] = 366;
  (*(void ( **)(UIStatic *, _DWORD, _DWORD *, UIScenePanel *))(v10 + 16))(&this->m_Static_10952, 0, (_DWORD *)(v59), this);
  LOBYTE(v11) = g_bSceneLoaded;
  (((UIPushButton *)&this->m_Static_10952))->UIPushButton::CreateFromTemplate((void *)off_59DDD4, v11);
  m_nTodo_11116 = (int)this->m_nTodo_11116;
  v55 = 83;
  v54 = 170;
  v56 = 502;
  v57 = 519;
  (*(void ( **)(UIWnd *, _DWORD, int *, UIScenePanel *))(m_nTodo_11116 + 16))(
    &this->m_nTodo_11116,
    0,
    &v54,
    this);
  LOBYTE(v13) = g_bSceneLoaded;
  (((UIPushButton *)&this->m_nTodo_11116))->UIPushButton::CreateFromTemplate((void *)off_59DDCC, v13);
  (((UIBigMap *)&this->m_nTodo_11116))->UIBigMap::SetViewParams(406, 590);
  this->m_nTodo_2C14 = 0;
  this->m_nTodo_2C08 = 1;
  this->m_nTodo_2C0C = 1118044160;
  LOBYTE(this->m_nTodo_2C18) = 0;
  this->m_nTodo_2C10 = 0;
  LOBYTE(this->m_nTodo_2C18) = 1;
  m_nTodo_11308 = (int)this->m_nTodo_11308;
  v55 = 86;
  v54 = 278;
  v56 = 610;
  v57 = 522;
  (*(void ( **)(UIWnd *, _DWORD, int *, UIScenePanel *))(m_nTodo_11308 + 16))(
    &this->m_nTodo_11308,
    0,
    &v54,
    this);
  LOBYTE(v15) = g_bSceneLoaded;
  (((UIPushButton *)&this->m_nTodo_11308))->UIPushButton::CreateFromTemplate((void *)off_59DDD0, v15);
  (((UIBigMap *)&this->m_nTodo_11308))->UIBigMap::SetViewParams(336, 28);
  this->m_nTodo_2CD4 = 0;
  this->m_nTodo_2CC8 = 1;
  this->m_nTodo_2CCC = 1118044160;
  LOBYTE(this->m_nTodo_2CD8) = 0;
  this->m_nTodo_2CD0 = 0;
  LOBYTE(this->m_nTodo_2CD8) = 1;
  v16 = (*(int ( **)(UIStatic *, _DWORD, float *, UIScenePanel *))(*(_DWORD *)((UIWnd *)&this->m_Static_10800) + 16))(
          &this->m_Static_10800,
          0,
          p_m_fScaleY,
          this);
  LOBYTE(v16) = g_bSceneLoaded;
  (((UIPushButton *)&this->m_Static_10800))->UIPushButton::CreateFromTemplate((void *)off_59DD08, v16);
  LOBYTE(v17) = g_bSceneLoaded;
  v18 = (int)((UIWnd *)&this->m_SceneA);
  v47 = 0;
  v46 = 152;
  v48 = 388;
  v49 = 156;
  v19 = (*(int ( **)(UIScene *, int, int *, UIScenePanel *, int, int))(v18 + 32))(
          &this->m_SceneA,
          161,
          &v46,
          this,
          off_59DDB4,
          v17);
  LOBYTE(v19) = g_bSceneLoaded;
  v20 = (int)((UIWnd *)&this->m_SceneB);
  v47 = 175;
  v46 = 59;
  v48 = 187;
  v49 = 431;
  v21 = (*(int ( **)(UIScene *, int, int *, UIScenePanel *, int, int))(v20 + 32))(
          &this->m_SceneB,
          162,
          &v46,
          this,
          off_59DDB8,
          v19);
  LOBYTE(v21) = g_bSceneLoaded;
  v22 = (int)((UIWnd *)&this->m_SceneC);
  v47 = 446;
  v46 = 142;
  v48 = 378;
  v49 = 602;
  v23 = (*(int ( **)(UIScene *, int, int *, UIScenePanel *, int, int))(v22 + 32))(
          &this->m_SceneC,
          163,
          &v46,
          this,
          off_59DDBC,
          v21);
  v47 = 446;
  v46 = 410;
  LOBYTE(v23) = g_bSceneLoaded;
  v24 = (int)((UIWnd *)&this->m_SceneD);
  v48 = 646;
  v49 = 602;
  v25 = (*(int ( **)(UIScene *, int, int *, UIScenePanel *, int, int))(v24 + 32))(
          &this->m_SceneD,
          164,
          &v46,
          this,
          off_59DDC0,
          v23);
  LOBYTE(v25) = g_bSceneLoaded;
  v26 = (int)((UIWnd *)&this->m_SceneE);
  v47 = 179;
  v46 = 585;
  v48 = 713;
  v49 = 435;
  v27 = (*(int ( **)(UIScene *, int, int *, UIScenePanel *, int, int))(v26 + 32))(
          &this->m_SceneE,
          165,
          &v46,
          this,
          off_59DDC4,
          v25);
  LOBYTE(v27) = g_bSceneLoaded;
  v28 = (int)((UIWnd *)&this->m_SceneF);
  v47 = 0;
  v46 = 416;
  v48 = 652;
  v49 = 156;
  (*(void ( **)(UIScene *, int, int *, UIScenePanel *, int, int))(v28 + 32))(
    &this->m_SceneF,
    166,
    &v46,
    this,
    off_59DDC8,
    v27);
  v29 = (CCBRoleState *)operator new(0x5058u);
  *(_DWORD *)v45 = (_DWORD)v29;
  v60 = 0;
  if ( v29 )
    (((CCBRoleState *)v29))->CCBRoleState::_todo_456AB0();
  else
    v30 = 0;
  v60 = -1;
  *(&this->m_nObjStore + 2) = (int)v30;
  (((CCBRoleState *)v30))->CCBRoleState::~CCBRoleState();
  v31 = (CCBUIPanel *)operator new(0x14C4u);
  *(_DWORD *)v45 = (_DWORD)v31;
  v60 = 1;
  if ( v31 )
    (((CCBUIPanel *)v31))->CCBUIPanel::_todo_453D10();
  else
    v32 = 0;
  v60 = -1;
  *(&this->m_nObjStore + 3) = (int)v32;
  (((RoleShadow *)v32))->RoleShadow::InitFromTemplate((int)this);
  v33 = (TaskBookUI *)operator new(0x207F0u);
  *(_DWORD *)v45 = (_DWORD)v33;
  v60 = 2;
  if ( v33 )
    (((TaskBookUI *)v33))->TaskBookUI::~TaskBookUI();
  else
    v34 = 0;
  v60 = -1;
  this->m_hSettingsUI = v34;
  TaskBookUI_CreateEntry((int)this);
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    v37 = (gbAudioManager *)AudioManager;
    if ( AudioManager )
    {
      (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v37))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v37))->gbAudioManager::StopSoundStream(2);
      v38 = (CScreenMode *)CScreenMode::GetInstance();
      (((SoundMgr *)v38))->SoundMgr::PlayCPKStream(1);
    }
  }
  *(_DWORD *)Data = 0;
  *(_DWORD *)v44 = 0;
  *(_DWORD *)v45 = 0;
  ReadRegistryString(szSubKey, szValueName, (char *)Data);
  ReadRegistryString(szSubKey, "S_GAME_B", (char *)v44);
  ReadRegistryString(szSubKey, "S_GAME_C", (char *)v45);
  LOBYTE(g_dwUISettings) = *(_DWORD *)Data != 0;
  BYTE1(g_dwUISettings) = *(_DWORD *)v44 != 0;
  LOBYTE(v39) = *(_DWORD *)v45 != 0;
  BYTE2(g_dwUISettings) = *(_DWORD *)v45 != 0;
  *(&this->m_bFlags1 + 3) = 0;
  *((_BYTE *)&this->m_nObjStore + 5) = 0;
  this->m_nTodo_2B64 = 0;
  LOBYTE(this->m_nTodo_2B60) = 1;
  (((UICursor *)v39))->UICursor::_todo_541CC0();
  m_nPanelState = (void *)this->m_nPanelState;
  *(_DWORD *)&this->m_bPanelFlagA = 16;
  if ( m_nPanelState )
  {
    operator delete(m_nPanelState);
    this->m_nPanelState = 0;
  }
  v41 = (void *)operator new(4 * *(_DWORD *)&this->m_bPanelFlagA);
  v42 = 4 * *(_DWORD *)&this->m_bPanelFlagA;
  this->m_nPanelState = (int)v41;
  memset(v41, 0, v42);
  this->m_nSceneIdx = 0;
  this->m_bFlags0 = 1;
  this->m_bFlags1 = 0;
  *(&this->m_bFlags1 + 1) = 0;
  if ( (((CGameData *)&g_gamefrm))->CGameData::GetMode() == 8
    || (((CGameData *)&g_gamefrm))->CGameData::GetMode() == 11
    || (_BYTE)g_bGameUpdating )
  {
    (((ChoseCompose *)this))->ChoseCompose::Init(3);
    LOBYTE(g_bGameUpdating) = 0;
  }
}

// 0x0046DF10
char UIScenePanel::ValidateIndex(int nVal)
{
  if ( nVal >= (int)this->m_Static_13904.m_textx )
    return 0;
  if ( nVal >= 0 )
    return *((_BYTE *)&this[1].m_pPanelSlot4 + nVal + 128);
  return 0;
}

// 0x0052CAF0
int UIScenePanel::ActivatePanel(int id)
{
  char *v3; // edi
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  const char *v7; // eax
  void (***v8)(_DWORD, _DWORD); // ebx
  int v9; // edx
  int result; // eax
  UIPushButton *v11; // [esp+0x70] [ebp-0x3C]
  UIPushButton *v12; // [esp+0x74] [ebp-0x38]
  void (***v13)(_DWORD, _DWORD); // [esp+0x78] [ebp-0x34]
  void (***v14)(_DWORD, _DWORD); // [esp+0x7C] [ebp-0x30]
  void (***v15)(_DWORD, _DWORD); // [esp+0x80] [ebp-0x2C]
  void (***v16)(_DWORD, _DWORD); // [esp+0x84] [ebp-0x28]
  void (***v17)(_DWORD, _DWORD); // [esp+0x88] [ebp-0x24]
  _BYTE v18[16]; // [esp+0x8C] [ebp-0x20] BYREF
  _DWORD v19[4]; // [esp+0x9C] [ebp-0x10] BYREF

  v3 = (char *)this + 1552 * id;
  v11 = (UIPushButton *)(v3 + 2424);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 606) + 16))(
    (&off_5707D0)[id],
    (_BYTE *)(v18),
    this);
  LOBYTE(v4) = *((_BYTE *)&this->m_SceneD.m_hTexture + 69);
  (((UIPushButton *)(v3 + 2424)))->UIPushButton::CreateFromTemplate("SubGame\\Encampment\\BlanceBk.tga", v4);
  v13 = (void ( ***)(_DWORD, _DWORD))(v3 + 2576);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 644) + 16))(
    (&off_5707D0)[id],
    (_BYTE *)(v18),
    this);
  v12 = (UIPushButton *)(v3 + 2728);
  v5 = (*(int ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 682) + 16))(
         (&off_5707D0)[id],
         (_BYTE *)(v18),
         this);
  LOBYTE(v5) = *((_BYTE *)&this->m_SceneD.m_hTexture + 69);
  ((UIPushButton *)((UIPushButton *)v3 + 11))->UIPushButton::CreateFromTemplate((void *)(0x57081C)[id], v5);
  v6 = *((_DWORD *)v3 + 758);
  v19[1] = 0;
  v19[0] = 0;
  v7 = (&off_5707D0)[id];
  v19[2] = 76;
  v19[3] = 12;
  v15 = (void ( ***)(_DWORD, _DWORD))(v3 + 3032);
  (*(void ( **)(const char *, _DWORD *, UIScenePanel *))(v6 + 16))(v7, (_DWORD *)(v19), this);
  v14 = (void ( ***)(_DWORD, _DWORD))(v3 + 2880);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 720) + 16))(
    (&off_5707D0)[id],
    (_BYTE *)(v18),
    this);
  v8 = (void ( ***)(_DWORD, _DWORD))(v3 + 3276);
  (*(void ( **)(char *, const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 819) + 16))(
    v3 + 3276,
    (&off_5707D0)[id],
    (_BYTE *)(v18),
    this);
  AllocObject(v3 + 3276);
  v17 = (void ( ***)(_DWORD, _DWORD))(v3 + 3580);
  (*(void ( **)(const char *, _DWORD *, UIScenePanel *))(*((_DWORD *)v3 + 895) + 16))(
    (&off_5707D0)[id],
    (_DWORD *)(v19),
    this);
  v16 = (void ( ***)(_DWORD, _DWORD))(v3 + 3428);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 857) + 16))(
    (&off_5707D0)[id],
    (_BYTE *)(v18),
    this);
  v9 = *((_DWORD *)v3 + 956);
  v3 += 3824;
  (*(void ( **)(char *, const char *, _BYTE *, UIScenePanel *))(v9 + 16))(v3, (&off_5707D0)[id], (_BYTE *)(v18), this);
  AllocObject(v3);
  (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v11))((UIPushButton *)(v11), (_DWORD)(0));
  (**v13)((_DWORD)(v13), (_DWORD)(0));
  (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v12))((UIPushButton *)(v12), (_DWORD)(0));
  (**v14)((_DWORD)(v14), (_DWORD)(0));
  (**v15)((_DWORD)(v15), (_DWORD)(0));
  (**v8)((_DWORD)(v8), (_DWORD)(0));
  (**v16)((_DWORD)(v16), (_DWORD)(0));
  (**v17)((_DWORD)(v17), (_DWORD)(0));
  result = (**(int ( ***)(char *, _DWORD))v3)((char *)(v3), (_DWORD)(0));
  this->m_bPanelActive = 1;
  return result;
}
