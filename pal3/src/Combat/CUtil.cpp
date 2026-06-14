#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CUtil.h"

// Forward declarations for unnamed functions
int sub_4431B0(...);
int sub_445FA0(void *a2); // from annotations
int sub_51DFD0(...);
int todo_064(...);
int todo_06C(...);

int crt_sub_00540D20(void); // from annotations

// Unnamed globals (extern)
extern int dword_17ADB04;
extern float flt_17ADB00;

// 0x005230F0
// attributes: thunk
void CUtil::_CUtil()
{

}

// 0x00523100
bool CUtil::Create()
{
  dword_17ADB04 = 1094713344;
  return 0;
}

// 0x00523110
// attributes: thunk
void CUtil::Destroy()
{

}

// 0x00523120
void CUtil::Init()
{
  flt_17ADB00 = 12.0 + 12.0;
}

// 0x00523130
CUtil::CUtil()
{
  *(_DWORD *)&this->m_szLogPath[68] = 800;
  *(_DWORD *)&this->m_szLogPath[72] = 600;
  this->_todo_168 = 0;
  this->_todo_16C = 0;
  ((ARC_PlayerAtt *)&this->_embed_UIItem_368)->Refresh();
  this->m_pScreenMode = 0;
  this->m_pBattleSystem = 0;
  this->m_pListView = 0;
  this->m_pPropUI = 0;
  this->m_nRenderMode = 0;
  this->_todo_160 = 0;
  *((_BYTE *)&this->_todo_160 + 4) = 0;
  *(&this->m_nRenderMode + 1) = 0;
  *((_BYTE *)&this->m_nRenderMode + 16) = 1;
}

// 0x005231D0
UIWnd * CUtil::WriteLog(CUtil *Block, char format)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (UIWnd *)this;
}

// 0x005231F0
void CUtil::_CUtil_31f0()
{
  CScreenMode *m_pScreenMode; // ecx
  char *m_pBattleSystem; // ecx
  char *m_pListView; // ecx
  PropUI *m_pPropUI; // ecx

  m_pScreenMode = this->m_pScreenMode;
  if ( m_pScreenMode )
  {
    (*((void ( **)(CScreenMode *, int))m_pScreenMode->m_pEnumeration + 5))(m_pScreenMode, 1);
    this->m_pScreenMode = 0;
  }
  m_pBattleSystem = this->m_pBattleSystem;
  if ( m_pBattleSystem )
  {
    (*(void ( **)(char *, int))(*(_DWORD *)m_pBattleSystem + 20))(m_pBattleSystem, 1);
    this->m_pBattleSystem = 0;
  }
  m_pListView = this->m_pListView;
  if ( m_pListView )
  {
    (*(void ( **)(char *, int))(*(_DWORD *)m_pListView + 20))(m_pListView, 1);
    this->m_pListView = 0;
  }
  m_pPropUI = this->m_pPropUI;
  if ( m_pPropUI )
  {
// [VFTABLE] ((void ( *)(PropUI *, int))m_pPropUI->__vftable->sub_4431B0)(m_pPropUI, 1);
    this->m_pPropUI = 0;
  }
  ((UIRoleDialog *)&this->_embed_UIItem_368)->_UIRoleDialog();
  ((UIListBox *)this)->_UIListBox();
}

// 0x005232B0
int CUtil::InitGameSystems()
{
  int v2; // eax
  int v3; // ecx
  int todo_064; // ecx
  int todo_06C; // edx
  CScreenMode *v6; // eax
  CScreenMode *v7; // eax
  CCBStage *v8; // eax
  char *d710; // eax
  UIListBox *v10; // eax
  char *v11; // eax
  PropUI *v12; // eax
  PropUI *inited; // eax
  CScreenMode *m_pScreenMode; // ecx
  UICursor *v15; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v18; // esi
  CScreenMode *v19; // eax
  int result; // eax
  int v21; // [esp+0x0] [ebp-0x30]
  int v22; // [esp+0x4] [ebp-0x2C]
  int nVal[4]; // [esp+0x14] [ebp-0x1C] BYREF
  int v24; // [esp+0x2C] [ebp-0x4]

  v2 = *(_DWORD *)&this->m_szLogPath[68];
  v3 = *(_DWORD *)&this->m_szLogPath[72];
  *(_DWORD *)&this->m_szLogPath[60] = v2;
  *(_DWORD *)&this->m_szLogPath[64] = v3;
  *(_DWORD *)&this->m_szLogPath[56] = 0;
  *(_DWORD *)&this->m_szLogPath[52] = 0;
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, *(_DWORD *)&this->m_szLogPath[60], *(_DWORD *)&this->m_szLogPath[64], 0);
  nVal[1] = 200;
  nVal[0] = 250;
  nVal[2] = 550;
  nVal[3] = 300;
  ((ARC_PlayerAtt *)&this->_embed_UIItem_368)->Create((int)&g_PlayerAttBuffer2, (int)nVal);
  ((UIItem *)&this->_embed_UIItem_368)->SetData(18);
  todo_064 = this->_embed_UIItem_368._todo_064;
  todo_06C = this->_embed_UIItem_368._todo_06C;
  *(&this->_embed_UIItem_368._todo_05C + 2) = this->_embed_UIItem_368._todo_068 + 12;
  *(&this->_embed_UIItem_368._todo_05C + 1) = todo_064 + 6;
  *(&this->_embed_UIItem_368._todo_05C + 4) = this->_embed_UIItem_368._todo_05C - 38;
  *(&this->_todo_544 + 91) = 0;
  *(&this->_todo_544 + 92) = 6;
  *(&this->_embed_UIItem_368._todo_05C + 3) = todo_06C - 6;
  sub_445FA0((char *)&this->_embed_UIItem_368 + 456);
  v6 = (CScreenMode *)operator new(0x1578u);
  v24 = 0;
  if ( v6 )
  {
  }
  else
    v7 = 0;
  v24 = -1;
  this->m_pScreenMode = v7;
  v8 = (CCBStage *)operator new(0xA4128u);
  v24 = 1;
  if ( v8 )
    d710 = (char *)((CCBStage *)v8)->Create_d710();
  else
    d710 = 0;
  v24 = -1;
  this->m_pBattleSystem = d710;
  v10 = (UIListBox *)operator new(0x1E56Cu);
  v24 = 2;
  if ( v10 )
    v11 = (char *)((UIListBox *)v10)->InitWithPalScript(v21, v22);
  else
    v11 = 0;
  v24 = -1;
  this->m_pListView = v11;
  v12 = (PropUI *)operator new(0x70DCu);
  v24 = 3;
  if ( v12 )
    inited = (PropUI *)((PropUI *)v12)->InitUI();
  else
    inited = 0;
  m_pScreenMode = this->m_pScreenMode;
  v24 = -1;
  this->m_pPropUI = inited;
  ((UIScene *)m_pScreenMode)->InitScriptScene((int)this);
  sub_51DFD0((UIListBox *)this->m_pBattleSystem, this);
  ((LineupUI *)this->m_pListView)->SetPageIndex(1);
  ((LineupUI *)this->m_pListView)->InitListView();
  ((PropUI *)this->m_pPropUI)->SetSlotLock(1);
  ((PropUI *)this->m_pPropUI)->InitPlayerList((int)this);
  ((UIRoleSelect *)this->m_pScreenMode)->SetFieldLeft((int)this->m_pBattleSystem);
  ((ScriptSystemData *)this->m_pBattleSystem)->_CCBResultWindow((int)this->m_pPropUI);
  ((ScriptSystemData *)this->m_pBattleSystem)->Update((int)this->m_pScreenMode);

  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v18 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->DetachAll3D();
      ((gbAudioManager *)v18)->StopSoundStream(0);
      ((gbAudioManager *)v18)->StopSoundStream(2);
      v19 = CScreenMode::GetInstance();
      ((SoundMgr *)v19)->PlayCPKStream();
    }
  }
  ((UICursor *)v15)->IRender();
  return result;
}

// 0x00523560
bool CUtil::RectIntersection()
{
  PAL3 *Instance_db10; // eax
  PAL3 *v3; // ecx
  float m_snaph; // ecx
  int v5; // eax
  PAL3 *v6; // eax
  gbTexture *ActiveTexture; // eax
  PAL3 *v8; // ecx
  unsigned __int8 v9; // bl
  PAL3 *v10; // ecx
  PAL3 *v11; // eax
  PAL3 *v12; // ecx
  PAL3 *v13; // eax

  Instance_db10 = ((PAL3 *)this)->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(1);
  m_snaph = ((PAL3 *)v3)->GetInstance_db10()->m_snaph;
  v5 = 1061158912;
  if ( m_snaph != 0.0 )
    v5 = 1065353216;
  *(&this->m_nRenderMode + 3) = v5;
  *(&this->m_nRenderMode + 2) = v5;
  v6 = ((PAL3 *)LODWORD(m_snaph))->GetInstance_db10();
  LOBYTE(ActiveTexture) = ((RenderTarget *)v6)->OnResetDevice(1);
  if ( (_BYTE)ActiveTexture )
  {
    v9 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    ((PAL3 *)v8)->Render();
    g_bGameFlag2 = v9;
    v11 = ((PAL3 *)v10)->GetInstance_db10();
    ((RenderTarget *)v11)->RenderToScreen();
    *(&this->m_nRenderMode + 1) = 0;
    v13 = ((PAL3 *)v12)->GetInstance_db10();
    ActiveTexture = ((RenderTarget *)v13)->GetActiveTexture();
    if ( ActiveTexture && ActiveTexture[1] )
      *(&this->m_nRenderMode + 1) = (int)ActiveTexture;
  }
  else
  {
    *(&this->m_nRenderMode + 1) = 0;
  }
  return (char)ActiveTexture;
}

// 0x00523600
int CUtil::CalulateParabola()
{
  int result; // eax

  result = *(&this->m_nRenderMode + 1);
  if ( result )
    return crt_sub_00540D20();
  return result;
}

// 0x00523670
int CUtil::RenderFrame()
{
  int result; // eax
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  result = this->m_nRenderMode;
  switch ( result )
  {
    case 0:
      ((CCBControlWindow *)this)->Render(v3);
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
// [VFTABLE] result = ((int ( *)(PropUI *))this->m_pPropUI->__vftable->Render)(this->m_pPropUI);
      break;
    default:
      return result;
  }
  return result;
}

// 0x005236E0
void CUtil::SetDisablePicDw()
{
  int v1; // ecx
  int v2; // esi
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  PalScriptMgr *v5; // ecx
  int a3; // [esp+0xC] [ebp+0x8]

  v2 = v1;
  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    ((gbAudioManager *)AudioManager)->DetachAll3D();
  }
  if ( !((UIParabolaCtrl *)(v2 + 368))->GetState() )
    ((CUtil *)v2)->Update(2.0f);
  switch ( *(_DWORD *)(v2 + 1752) )
  {
    case 0:
      ((UIListBox *)v2)->Update((int)pszScene, a3);
      break;
    case 1:
      (*(void ( **)(_DWORD, char *, int))(**(_DWORD **)(v2 + 1736) + 8))(*(_DWORD *)(v2 + 1736), pszScene, a3);
      break;
    case 2:
      ((PalScriptMgr *)v5)->RunSceneScript(pszScene);
      (*(void ( **)(_DWORD, char *, int))(**(_DWORD **)(v2 + 1740) + 8))(*(_DWORD *)(v2 + 1740), pszScene, a3);
      break;
    case 3:
      (*(void ( **)(_DWORD, char *, int))(**(_DWORD **)(v2 + 1744) + 8))(*(_DWORD *)(v2 + 1744), pszScene, a3);
      break;
    case 4:
      (*(void ( **)(_DWORD, char *, int))(**(_DWORD **)(v2 + 1748) + 8))(*(_DWORD *)(v2 + 1748), pszScene, a3);
      break;
    case 5:
      ((CGameData *)&g_gamefrm)->Load(0);
      break;
    case 6:
      ((CGameData *)&g_gamefrm)->Load((CUtil *)4);
      break;
    default:
      return;
  }
}

// 0x00523820
int CUtil::Update(float nDelta)
{
  CScreenMode *m_pScreenMode; // ecx
  char *m_pBattleSystem; // ecx
  char *m_pListView; // ecx
  PropUI *m_pPropUI; // ecx
  CScreenMode *v7; // ecx
  char *v8; // ecx
  char *v9; // ecx
  CScreenMode *v10; // ecx
  char *v11; // ecx
  char *v12; // ecx
  CScreenMode *v13; // ecx
  char *v14; // ecx
  char *v15; // ecx
  CScreenMode *v16; // ecx
  char *v17; // ecx
  char *v18; // ecx
  PropUI *v19; // ecx
  CScreenMode *v20; // ecx
  char *v21; // ecx
  char *v22; // ecx
  PropUI *v23; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v26; // edi
  CScreenMode *v27; // eax
  CScreenMode *v28; // eax
  int result; // eax

  *(float *)&this->m_nRenderMode = nDelta;
  switch ( LODWORD(nDelta) )
  {
    case 0:
      if ( this )
        (*(void ( **)(CUtil *, int, int, _DWORD))(*(_DWORD *)&this->m_bCanWarp + 24))(this, 1000, 1, 0);
      m_pScreenMode = this->m_pScreenMode;
      if ( m_pScreenMode )
        (*((void ( **)(CScreenMode *, int, _DWORD, _DWORD))m_pScreenMode->m_pEnumeration + 6))(
          m_pScreenMode,
          1000,
          0,
          0);
      m_pBattleSystem = this->m_pBattleSystem;
      if ( m_pBattleSystem )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)m_pBattleSystem + 24))(
          m_pBattleSystem,
          1000,
          0,
          0);
      m_pListView = this->m_pListView;
      if ( m_pListView )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)m_pListView + 24))(m_pListView, 1000, 0, 0);
      m_pPropUI = this->m_pPropUI;
      if ( m_pPropUI )
        goto LABEL_39;
      break;
    case 1:
      if ( this )
        (*(void ( **)(CUtil *, int, _DWORD, _DWORD))(*(_DWORD *)&this->m_bCanWarp + 24))(this, 1000, 0, 0);
      v7 = this->m_pScreenMode;
      if ( v7 )
        (*((void ( **)(CScreenMode *, int, int, _DWORD))v7->m_pEnumeration + 6))(v7, 1000, 1, 0);
      v8 = this->m_pBattleSystem;
      if ( v8 )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1000, 0, 0);
      v9 = this->m_pListView;
      if ( v9 )
        (*(void ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(1000, 0, 0);
      goto LABEL_38;
    case 2:
      if ( this )
        (*(void ( **)(CUtil *, int, _DWORD, _DWORD))(*(_DWORD *)&this->m_bCanWarp + 24))(this, 1000, 0, 0);
      v10 = this->m_pScreenMode;
      if ( v10 )
        (*((void ( **)(CScreenMode *, int, _DWORD, _DWORD))v10->m_pEnumeration + 6))(v10, 1000, 0, 0);
      v11 = this->m_pBattleSystem;
      if ( v11 )
        (*(void ( **)(char *, int, int, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 1, 0);
      v12 = this->m_pListView;
      if ( v12 )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 0, 0);
      m_pPropUI = this->m_pPropUI;
      if ( m_pPropUI )
        goto LABEL_39;
      break;
    case 3:
      if ( this )
        (*(void ( **)(CUtil *, int, _DWORD, _DWORD))(*(_DWORD *)&this->m_bCanWarp + 24))(this, 1000, 0, 0);
      v13 = this->m_pScreenMode;
      if ( v13 )
        (*((void ( **)(CScreenMode *, int, _DWORD, _DWORD))v13->m_pEnumeration + 6))(v13, 1000, 0, 0);
      v14 = this->m_pBattleSystem;
      if ( v14 )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)v14 + 24))(v14, 1000, 0, 0);
      v15 = this->m_pListView;
      if ( v15 )
        (*(void ( **)(int, int, _DWORD))(*(_DWORD *)v15 + 24))(1000, 1, 0);
LABEL_38:
      m_pPropUI = this->m_pPropUI;
      if ( m_pPropUI )
LABEL_39:
// [VFTABLE] ((void ( *)(PropUI *, int, _DWORD, _DWORD))m_pPropUI->__vftable->OnMessage)(m_pPropUI, 1000, 0, 0);
      break;
    case 4:
      if ( this )
        (*(void ( **)(CUtil *, int, _DWORD, _DWORD))(*(_DWORD *)&this->m_bCanWarp + 24))(this, 1000, 0, 0);
      v16 = this->m_pScreenMode;
      if ( v16 )
        (*((void ( **)(CScreenMode *, int, _DWORD, _DWORD))v16->m_pEnumeration + 6))(v16, 1000, 0, 0);
      v17 = this->m_pBattleSystem;
      if ( v17 )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)v17 + 24))(v17, 1000, 0, 0);
      v18 = this->m_pListView;
      if ( v18 )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)v18 + 24))(v18, 1000, 0, 0);
      v19 = this->m_pPropUI;
      if ( v19 )
// [VFTABLE] ((void ( *)(PropUI *, int, int, _DWORD))v19->__vftable->OnMessage)(v19, 1000, 1, 0);
      break;
    case 5:
      if ( this )
        (*(void ( **)(CUtil *, int, _DWORD, _DWORD))(*(_DWORD *)&this->m_bCanWarp + 24))(this, 1000, 0, 0);
      v20 = this->m_pScreenMode;
      if ( v20 )
        (*((void ( **)(CScreenMode *, int, _DWORD, _DWORD))v20->m_pEnumeration + 6))(v20, 1000, 0, 0);
      v21 = this->m_pBattleSystem;
      if ( v21 )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)v21 + 24))(v21, 1000, 0, 0);
      v22 = this->m_pListView;
      if ( v22 )
        (*(void ( **)(char *, int, _DWORD, _DWORD))(*(_DWORD *)v22 + 24))(v22, 1000, 0, 0);
      v23 = this->m_pPropUI;
      if ( v23 )
// [VFTABLE] ((void ( *)(PropUI *, int, _DWORD, _DWORD))v23->__vftable->OnMessage)(v23, 1000, 0, 0);
      if ( (g_dwGameFlags & 4) != 0 )
      {
        Instance = CScreenMode::GetInstance();
        AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
        v26 = AudioManager;
        if ( AudioManager )
        {
          ((gbAudioManager *)AudioManager)->StopSoundStream(1);
          ((gbAudioManager *)v26)->StopSoundStream(2);
        }
        if ( CScreenMode::GetInstance()->m_bRenderAlt )
        {
          v27 = CScreenMode::GetInstance();
          ((CScreenMode *)v27)->AudioFadeOut();
        }
        else
        {
          v28 = CScreenMode::GetInstance();
          ((CScreenMode *)v28)->AudioStopAll();
        }
      }
      break;
    default:
      break;
  }
  result = (this->m_nRenderMode == 5) + 1;
  g_nSceneState = result;
  return result;
}

// 0x00523E80
int CUtil::DispatchCommand(int *pCmd)
{
  int result; // eax
  char *m_pBattleSystem; // ecx

  ((RoleShadow *)this->m_pScreenMode)->LoadQuadData(pCmd);
  result = (int)((CCBStageRole *)this->m_pBattleSystem)->LoadSaveData(pCmd);
  m_pBattleSystem = this->m_pBattleSystem;
  if ( m_pBattleSystem )
    return (*(int ( **)(char *, int, int, _DWORD))(*(_DWORD *)m_pBattleSystem + 24))(
             m_pBattleSystem,
             1000,
             1,
             0);
  return result;
}
