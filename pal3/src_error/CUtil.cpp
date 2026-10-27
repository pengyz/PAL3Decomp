#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CUtil.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Role/Actor.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "GameBase/PAL3.h"
#include "Script/PalScript.h"
#include "UI/PropUI.h"
#include "Render/RenderTarget.h"
#include "Role/Role.h"
#include "Misc/RoleShadow.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/SoundMgr.h"
#include "Misc/SystemUI.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int todo_0051DFD0(...);

// Unnamed globals (extern)
extern CHAR byte_DC7D3C[512];
extern void * off_5E2BC4;

// 0x005230F0
// attributes: thunk
CUtil::~CUtil()
{
  this->CUtil::Create();
}

// 0x00523100
bool CUtil::Create()
{
  bool result; // al

  result = 0;
  dword_17ADB04 = 1094713344;
  return result;
}

// 0x00523110
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CUtil::Destroy()
{
  this->CUtil::Init();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00523120
void CUtil::Init()
{
  flt_17ADB00 = 12.0 + 12.0;
}

// 0x00523130
CUtil::CUtil()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  *(_DWORD *)&this->m_szLogPath[68] = 800;
  *(_DWORD *)&this->m_szLogPath[72] = 600;
  this->m_nListIndex = 0;
  this->m_nUpdateCounter = 0;
  ((UIRoleDialog *)&this->m_uiItemSlot)->UIRoleDialog::UIRoleDialog();
  this->m_pScreenMode = ((CScreenMode *)0);
  this->m_pBattleSystem = ((char *)0);
  this->m_pListView = ((char *)0);
  this->m_pPropUI = ((PropUI *)0);
  this->m_nRenderMode = 0;
  this->m_nTodo_160[0] = 0;
  LOBYTE(this->m_nTodo_160[1]) = 0;
  *(&this->m_nRenderMode + 1) = 0;
  *((_BYTE *)&this->m_nRenderMode + 16) = 1;
}

// 0x005231F0
void CUtil::_CUtil_31f0()
{
  CScreenMode *m_pScreenMode; // ecx
  char *m_pBattleSystem; // ecx
  char *m_pListView; // ecx
  PropUI *m_pPropUI; // ecx

  m_pScreenMode = (CScreenMode *)this->m_pScreenMode;
  if ( m_pScreenMode )
  {
    (*((void ( **)(CScreenMode *, int))m_pScreenMode->m_pEnumeration + 5))(m_pScreenMode, 1);
    this->m_pScreenMode = ((CScreenMode *)0);
  }
  m_pBattleSystem = (char *)this->m_pBattleSystem;
  if ( m_pBattleSystem )
  {
    (*(void ( **)(char *, int))(*(_DWORD *)m_pBattleSystem + 20))(m_pBattleSystem, 1);
    this->m_pBattleSystem = ((char *)0);
  }
  m_pListView = (char *)this->m_pListView;
  if ( m_pListView )
  {
    (*(void ( **)(char *, int))(*(_DWORD *)m_pListView + 20))(m_pListView, 1);
    this->m_pListView = ((char *)0);
  }
  m_pPropUI = (PropUI *)this->m_pPropUI;
  if ( m_pPropUI )
  {
    (*(void ( **)(PropUI *, int))(*(_DWORD *)((UIWnd *)m_pPropUI) + 20))(m_pPropUI, 1);
    this->m_pPropUI = ((PropUI *)0);
  }
  (((UIRoleDialog *)&this->m_uiItemSlot))->UIRoleDialog::~UIRoleDialog();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x005232B0
int CUtil::InitGameSystems()
{
  int v2; // eax
  int v3; // ecx
  int m_nTodo_050; // ecx
  int m_nTodo_058; // edx
  CScreenMode *v6; // eax
  CScreenMode *v7; // eax
  CCBStage *v8; // eax
  char *d710; // eax
  char *v10; // eax
  PropUI *v11; // eax
  PropUI *inited; // eax
  UICursor *v13; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v16; // esi
  CScreenMode *v17; // eax
  int result; // eax
  int v19; // [esp+0x0] [ebp-0x30]

  v2 = *(_DWORD *)&this->m_szLogPath[68];
  v3 = *(_DWORD *)&this->m_szLogPath[72];
  *(_DWORD *)&this->m_szLogPath[60] = v2;
  *(_DWORD *)&this->m_szLogPath[64] = v3;
  *(_DWORD *)&this->m_szLogPath[56] = 0;
  *(_DWORD *)&this->m_szLogPath[52] = 0;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, 0, 0, *(_DWORD *)&this->m_szLogPath[60], *(_DWORD *)&this->m_szLogPath[64]) /* [ROWTABLE] */;
  Create__ovl_1((ARC_PlayerAtt *)&this->m_uiItemSlot);
  (((UIItem *)&this->m_uiItemSlot))->UIItem::SetData(18);
  m_nTodo_050 = this->m_uiItemSlot.m_nTodo_050;
  m_nTodo_058 = this->m_uiItemSlot.m_nTodo_058;
  *(&this->m_uiItemSlot.m_nTodo_05C + 2) = this->m_uiItemSlot.m_nTodo_054 + 12;
  *(&this->m_uiItemSlot.m_nTodo_05C + 1) = m_nTodo_050 + 6;
  *(&this->m_uiItemSlot.m_nTodo_05C + 4) = this->m_uiItemSlot.m_nTodo_05C - 38;
  *(&this->m_nTodo_544 + 91) = 0;
  *(&this->m_nTodo_544 + 92) = 6;
  *(&this->m_uiItemSlot.m_nTodo_05C + 3) = m_nTodo_058 - 6;
  (((UIWnd *)((char *)&this->m_uiItemSlot + 456)))->UIWnd::sub_445FA0(&this->m_uiItemSlot.m_nTodo_05C + 1);
  v6 = (CScreenMode *)operator new(0x1578u);
  if ( v6 )
    v6->CScreenMode::CScreenMode();
  else
    v7 = 0;
  this->m_pScreenMode = ((CScreenMode *)(v7));
  v8 = (CCBStage *)operator new(0xA4128u);
  if ( v8 )
    d710 = (char *)(((CCBStage *)v8))->CCBStage::Create_d710();
  else
    d710 = 0;
  this->m_pBattleSystem = ((char *)(d710));
  if ( operator new(0x1E56Cu) )
    v10 = (char *)UIListBox_InitWithPalScript(v19);
  else
    v10 = 0;
  this->m_pListView = ((char *)(v10));
  v11 = (PropUI *)operator new(0x70DCu);
  if ( v11 )
    inited = (PropUI *)(((PropUI *)v11))->PropUI::InitUI();
  else
    inited = 0;
  this->m_pPropUI = ((PropUI *)(inited));
  UIScene_InitScriptScene((int)this);
  todo_0051DFD0((Actor *)this->m_pBattleSystem, (int)this);
  LineupUI_SetPageIndex(1);
  LineupUI_InitListView((int)this);
  (((PropUI *)this->m_pPropUI))->PropUI::SetSlotLock(1);
  (((PropUI *)this->m_pPropUI))->PropUI::InitPlayerList((int)this);
  UIRoleSelect_SetFieldLeft((int)this->m_pBattleSystem);
  (((CCBStage *)this->m_pBattleSystem))->CCBStage::SetWeaponSlotB();
  (((CCBStage *)this->m_pBattleSystem))->CCBStage::SetWeaponSlotA();
  (((CCBStage *)this->m_pBattleSystem))->CCBStage::UpdateWeaponSlots();
  this->CUtil::RectIntersection();
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    v16 = (gbAudioManager *)AudioManager;
    if ( AudioManager )
    {
      (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v16))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v16))->gbAudioManager::StopSoundStream(2);
      v17 = (CScreenMode *)CScreenMode::GetInstance();
      (((SoundMgr *)v17))->SoundMgr::PlayCPKStream(1);
    }
  }
  (((UICursor *)v13))->UICursor::_todo_541CC0();
  return result;
}

// 0x00523560
bool CUtil::RectIntersection()
{
  PAL3 *Instance_db10; // eax
  float m_snaph; // ecx
  int v4; // eax
  PAL3 *v5; // eax
  gbTexture *ActiveTexture; // eax
  PAL3 *v7; // ecx
  unsigned __int8 v8; // bl
  PAL3 *v9; // eax
  PAL3 *v10; // eax

  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(1);
  m_snaph = PAL3::GetInstance_db10()->m_snaph;
  v4 = 1061158912;
  if ( m_snaph != 0.0f )
    v4 = 1065353216;
  *(&this->m_nRenderMode + 3) = v4;
  *(&this->m_nRenderMode + 2) = v4;
  v5 = (PAL3 *)PAL3::GetInstance_db10();
  LOBYTE(ActiveTexture) = (((RenderTarget *)v5))->RenderTarget::OnResetDevice(1);
  if ( (_BYTE)ActiveTexture )
  {
    v8 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    (((PAL3 *)v7))->PAL3::Render();
    g_bGameFlag2 = v8;
    v9 = (PAL3 *)PAL3::GetInstance_db10();
    (((RenderTarget *)v9))->RenderTarget::RenderToScreen();
    *(&this->m_nRenderMode + 1) = 0;
    v10 = (PAL3 *)PAL3::GetInstance_db10();
    ActiveTexture = (((RenderTarget *)v10))->RenderTarget::GetActiveTexture();
    if ( ActiveTexture && *(_DWORD *)((gbRefObject *)&ActiveTexture[1]) )
      *(&this->m_nRenderMode + 1) = (int)ActiveTexture;
  }
  else
  {
    *(&this->m_nRenderMode + 1) = 0;
  }
  return (char)ActiveTexture;
}

// 0x00523670
int CUtil::RenderFrame()
{
  int result; // eax
  int v3; // [esp+0x0] [ebp-0x4]
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0x4]

  CUtil_CalulateParabola(v3);
  result = this->m_nRenderMode;
  switch ( result )
  {
    case 0:
      (((CCBControlWindow *)this))->CCBControlWindow::Render(v4) /* [ROWTABLE] */;
      break;
    case 1:
      result = (*((int ( **)(CScreenMode *))this->m_pScreenMode->m_pEnumeration + 1))(this->m_pScreenMode);
      break;
    case 2:
      result = (*(int ( **)(char *))(*(_DWORD *)this->m_pBattleSystem + 4))(this->m_pBattleSystem);
      break;
    case 3:
      result = (*(int ( **)(char *))(*(_DWORD *)this->m_pListView + 4))(this->m_pListView);
      break;
    case 4:
      result = (*(int ( **)(PropUI *))(*(_DWORD *)((UIWnd *)this->m_pPropUI) + 4))(this->m_pPropUI);
      break;
    default:
      return result;
  }
  return result;
}

// 0x005236E0
int CUtil::RenderFrameY(PalScript *fTime, int nVal)
{
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  int result; // eax
  int v7; // [esp+0x0] [ebp-0x4]

  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
  }
  if ( !UIParabolaCtrl_GetState(v7) )
    CUtil_Update(2);
  switch ( this->m_nRenderMode )
  {
    case 0:
      (((SceneObj *)this))->SceneObj::Update((int)fTime, nVal) /* [ROWTABLE] */;
      result = 1;
      break;
    case 1:
      (*((void ( **)(CScreenMode *, PalScript *, int))this->m_pScreenMode->m_pEnumeration + 2))(
        this->m_pScreenMode,
        fTime,
        nVal);
      result = 1;
      break;
    case 2:
      StopSceneScripts((const char *)fTime);
      (*(void ( **)(char *, PalScript *, int))(*(_DWORD *)this->m_pBattleSystem + 8))(
        this->m_pBattleSystem,
        fTime,
        nVal);
      result = 1;
      break;
    case 3:
      (*(void ( **)(char *, PalScript *, int))(*(_DWORD *)this->m_pListView + 8))(
        this->m_pListView,
        fTime,
        nVal);
      result = 1;
      break;
    case 4:
      (*(void ( **)(PropUI *, PalScript *, int))(*(_DWORD *)((UIWnd *)this->m_pPropUI) + 8))(
        this->m_pPropUI,
        fTime,
        nVal);
      result = 1;
      break;
    case 5:
      (((CGameData *)&g_gamefrm))->CGameData::Load(0);
      result = 1;
      break;
    case 6:
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)4);
      goto LABEL_14;
    default:
LABEL_14:
      result = 1;
      break;
  }
  return result;
}

// 0x00523B90
int CUtil::OnMessage(int nVal, int nMsg, int wParam)
{
  int v6; // eax
  int v7; // edi
  int updated; // eax
  CScreenMode *Instance; // eax
  int v10; // eax
  const void *v11; // [esp-0xC] [ebp-0x10]

  if ( nVal != 1000 )
    return (((UIWnd *)this))->UIWnd::OnMessage(nVal, nMsg, wParam) /* [ROWTABLE] */;
  if ( nMsg )
  {
    FindByName(&this->m_bCanWarp);
    v7 = v6;
    if ( v6 && *(int *)(v6 + 4) > 0 )
    {
      updated = (((SystemUI *)this->m_pBattleSystem))->SystemUI::UpdateParticles();
      this->m_nUpdateCounter = updated;
      if ( updated > 0 )
        *(_DWORD *)(v7 + 4) = 0;
    }
    else
    {
      this->m_nUpdateCounter = 0;
    }
    if ( this->m_nUpdateCounter > 0 )
    {
      sprintf(&this->m_szLogPath[76], "%s: %d", &byte_DC7D3C[256], this->m_nUpdateCounter);
      SetEnable((UICaption *)((char *)&this->m_uiItemSlot + 456));
      (((UIRoleSelect *)&this->m_uiItemSlot))->UIRoleSelect::SetByte(1);
      v11 = off_5E2BC4;
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v11, 1);
      *(&g_RoleSlotBuf.dword_17AA450 + 147) += this->m_nUpdateCounter;
      return 1;
    }
    v10 = *((_DWORD *)&this->m_pScreenMode->m_RoleDialog + 345);
    this->m_nListIndex = v10;
    if ( v10 > 0 )
    {
      CUtil_Update(2);
      return 1;
    }
    CUtil_Update(1);
  }
  return 1;
}

// 0x00523E80
int CUtil::DispatchCommand(int *pCmd)
{
  int result; // eax
  char *m_pBattleSystem; // ecx

  (((RoleShadow *)this->m_pScreenMode))->RoleShadow::LoadQuadData(pCmd);
  result = CCBStageRole_LoadSaveData((int)pCmd);
  m_pBattleSystem = (char *)this->m_pBattleSystem;
  if ( m_pBattleSystem )
    return (*(int ( **)(char *, int, int, _DWORD))(*(_DWORD *)m_pBattleSystem + 24))(
             m_pBattleSystem,
             1000,
             1,
             0);
  return result;
}
