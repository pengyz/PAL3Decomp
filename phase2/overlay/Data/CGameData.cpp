#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Data/CGameData.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Misc/ArcLocaleRole.h"
#include "Misc/ArcPastScene.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageScene.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Misc/CCBUIPanel.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/CameraCtrl.h"
#include "Misc/MainEquipUI.h"
#include "Script/PalScript.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleCameraCtrl.h"
#include "Misc/RoleStatePanel.h"
#include "Role/RoleSystem.h"
#include "Misc/RoleTask.h"
#include "Scene/SceneMgr.h"
#include "Scene/SceneObj.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "UI/UICursor.h"
#include "Misc/UIEmote.h"
#include "Misc/UIGameOver.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "Misc/UILoadingFrm.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleSelectDialog.h"
#include "UI/UIScene.h"
#include "Misc/UISceneFrm.h"
#include "Misc/UISceneMap.h"
#include "Misc/UIScenePanel.h"
#include "Misc/UITitle.h"
#include "Misc/UITitle_ArcSave.h"
#include "Misc/UITitle_BBTY.h"
#include "Misc/UITitle_YXXX.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_523CD0(...);
int sub_523D20(...);
int sub_523D70(...);
int sub_523DC0(...);
int sub_523E10(...);

// Unnamed globals (extern)
extern int dword_D92780;
extern char dword_DD8F3C[];
extern char dword_DD903C[];
extern char dword_DD913C[];
extern LPCSTR off_59BA88;
extern LPCSTR off_59BA8C;
extern LPCSTR off_59BA90;

// 0x00445A60
char CGameData::SetDefaultColors()
{
  char result; // al

  result = 64;
  if ( gbColorQuad::ColorQuadFmt )
  {
    g_DefaultColorG = 60;
    g_DefaultColorR = 64;
    LOBYTE(g_fUIColorParam) = 64;
  }
  else
  {
    LOBYTE(g_fUIColorParam) = 60;
    g_DefaultColorG = 64;
    g_DefaultColorR = 64;
  }
  g_DefaultColorB = -56;
  return result;
}

// 0x0044ADE0
int CGameData::InitRoles(int nVal)
{
  LONG m_nTodo_06C; // ecx
  LONG m_nTodo_070; // eax
  UIWnd *m_nTodo_07C; // edx
  UIPushButton *p_m_subObjA; // edi
  int result; // eax
  int nVala; // [esp+0x98] [ebp+0x4]

  this->m_rcWindow.top = 0;
  this->m_rcWindow.left = 0;
  this->m_rcWindow.right = 800;
  this->m_rcWindow.bottom = 600;
  (((UIWnd *)this))->UIWnd::Create((int)g_PalScriptTemplate, &this->m_rcWindow, (UIWnd *)nVal) /* [ROWTABLE] */;
  m_nTodo_06C = this->m_nTodo_06C;
  m_nTodo_070 = this->m_nTodo_070;
  m_nTodo_07C = (UIWnd *)this->m_nTodo_07C;
  this->m_rcWidgetRect.top = m_nTodo_070;
  this->m_rcWidgetRect.left = m_nTodo_06C;
  this->m_rcWidgetRect.right = m_nTodo_06C + 68;
  this->m_rcWidgetRect.bottom = m_nTodo_070 + 32;
  ((void ( *)(UIWnd **, unsigned __int8 *, tagRECT *, CGameData *))m_nTodo_07C->m_rect.left)(
    &this->m_nTodo_07C,
    g_PalScriptTemplate,
    &this->m_rcWidgetRect,
    this);
  (((UIPushButton *)&this->m_nTodo_07C))->UIPushButton::CreateFromTemplate((void *)off_59BA88, 1);
  (*(void ( **)(UIWnd **, _DWORD))this->m_nTodo_07C)(&this->m_nTodo_07C, 0);
  p_m_subObjA = (UIPushButton *)&this->m_subObjA;
  nVala = 3;
  do
  {
    (*(void ( **)(UIPushButton *, unsigned __int8 *, tagRECT *, CGameData *))(*(_DWORD *)((UIWnd *)p_m_subObjA)
                                                                                      + 16))(
      p_m_subObjA,
      g_PalScriptTemplate,
      &this->m_rcWidgetRect,
      this);
    (((UIPushButton *)p_m_subObjA))->UIPushButton::CreateFromTemplate((void *)off_59BA90, 1);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)p_m_subObjA))((UIPushButton *)(p_m_subObjA), (_DWORD)(0));
    p_m_subObjA = (UIPushButton *)((char *)p_m_subObjA + 152);
    --nVala;
  }
  while ( nVala );
  ((void ( *)(UIWnd **, unsigned __int8 *, tagRECT *, CGameData *))this->m_nInitRoles->m_rect.left)(
    &this->m_nInitRoles,
    g_PalScriptTemplate,
    &this->m_rcWidgetRect,
    this);
  (((UIPushButton *)&this->m_nInitRoles))->UIPushButton::CreateFromTemplate((void *)off_59BA8C, 1);
  (*(void ( **)(UIWnd **, _DWORD))this->m_nInitRoles)(&this->m_nInitRoles, 0);
  ((void ( *)(CScreenMode **, int *, tagRECT *, CGameData *, int, _DWORD, int))LODWORD(this->m_RoleDataA->m_fFadeAlpha))(
    &this->m_RoleDataA,
    &byte_AABEF7,
    &this->m_rcWidgetRect,
    this,
    off_59BA94,
    0,
    1);
  (((CScreenMode *)&this->m_RoleDataA))->CScreenMode::SetTooltipText((int)dword_DD8F3C);
  this->m_nTodo_3DC = 0;
  this->m_nTodo_3E0 = 2;
  ((void ( *)(CScreenMode **, _DWORD))this->m_RoleDataA->m_pEnumeration)(&this->m_RoleDataA, 0);
  ((void ( *)(CScreenMode **, int *, tagRECT *, CGameData *, int, _DWORD, int))LODWORD(this->m_RoleDataB->m_fFadeAlpha))(
    &this->m_RoleDataB,
    &byte_AABEF8,
    &this->m_rcWidgetRect,
    this,
    off_59BA94,
    0,
    1);
  (((CScreenMode *)&this->m_RoleDataB))->CScreenMode::SetTooltipText((int)dword_DD903C);
  this->m_nTodo_534 = 0;
  this->m_nTodo_538 = 2;
  ((void ( *)(CScreenMode **, _DWORD))this->m_RoleDataB->m_pEnumeration)(&this->m_RoleDataB, 0);
  ((void ( *)(CScreenMode **, int *, tagRECT *, CGameData *, int, _DWORD, int))LODWORD(this->m_RoleDataC->m_fFadeAlpha))(
    &this->m_RoleDataC,
    &byte_AABEF9,
    &this->m_rcWidgetRect,
    this,
    off_59BA94,
    0,
    1);
  (((CScreenMode *)&this->m_RoleDataC))->CScreenMode::SetTooltipText((int)dword_DD913C);
  this->m_nTodo_68C = 0;
  this->m_nTodo_690 = 2;
  ((void ( *)(CScreenMode **, _DWORD))this->m_RoleDataC->m_pEnumeration)(&this->m_RoleDataC, 0);
  Create__ovl_1((ARC_PlayerAtt *)&this->m_ItemSlotA);
  (((UIItem *)&this->m_ItemSlotA))->UIItem::SetData(31);
  Create__ovl_1((ARC_PlayerAtt *)&this->m_ItemSlotB);
  (((UIItem *)&this->m_ItemSlotB))->UIItem::SetData(31);
  Create__ovl_1((ARC_PlayerAtt *)&this->m_ItemSlotC);
  (((UIItem *)&this->m_ItemSlotC))->UIItem::SetData(18);
  Create__ovl_1((ARC_PlayerAtt *)&this->m_ItemSlotD);
  result = (int)(((UIItem *)&this->m_ItemSlotD))->UIItem::SetData(31);
  this->m_nScriptHandleB = 0;
  this->m_nScriptHandleA = 0;
  this->m_nScriptHandleC = 0;
  this->m_nScriptHandleD = 0;
  this->m_nScriptHandleE = 0;
  this->m_nScriptHandleF = 0;
  this->m_bInitRoles = 0;
  this->m_bScriptActive = 0;
  this->m_nScriptResult = 0;
  this->m_nTodo_CE8 = 0;
  this->m_nTodo_CE9 = 0;
  this->m_nTodo_CD8 = 0;
  this->m_bScriptRunning = 0;
  return result;
}

// 0x0044E660
int CGameData::InitItems(int nVal)
{
  int v3; // edi
  _DWORD *v4; // ebp
  UIScene **p_m_pStartScene; // esi
  LONG v6; // eax
  _DWORD *v8; // [esp+0x10] [ebp-0x1B4]
  tagRECT pRect; // [esp+0x14] [ebp-0x1B0] BYREF
  int v10; // [esp+0x24] [ebp-0x1A0]
  _DWORD v11[15]; // [esp+0x28] [ebp-0x19C] BYREF
  _DWORD v12[23]; // [esp+0x64] [ebp-0x160] BYREF
  char Buffer[260]; // [esp+C0h] [ebp-0x104] BYREF

  pRect.top = 0;
  pRect.left = 0;
  pRect.bottom = 600;
  pRect.right = 800;
  (((UIWnd *)this))->UIWnd::Create(0, &pRect, (UIWnd *)nVal) /* [ROWTABLE] */;
  memset32(&this->m_pItemArray, 3, 0xDu);
  v12[8] = 32;
  v12[0] = 54;
  v12[7] = 54;
  v12[15] = 54;
  v12[16] = 32;
  v11[0] = 6;
  v11[1] = 10;
  v11[2] = 10;
  v11[10] = 6;
  v3 = 1;
  v12[3] = 31;
  v12[9] = 31;
  v12[21] = 0;
  v12[22] = 0;
  v10 = 0;
  memset(&v11[11], 0, 12);
  this->m_nInitItems = 1;
  this->m_nItemCount2 = 1;
  this->m_nEquipCount = 1;
  this->m_nConsumableCount = 1;
  v11[14] = 38;
  v12[1] = 25;
  v12[2] = 57;
  v12[4] = 43;
  v12[5] = 82;
  v12[6] = 51;
  v12[10] = 41;
  v12[11] = 16;
  v12[12] = 111;
  v12[13] = 64;
  v12[14] = 46;
  v12[17] = 49;
  v12[18] = 40;
  v12[19] = 70;
  v12[20] = 42;
  v11[3] = 3;
  v11[4] = 2;
  v11[5] = 4;
  v11[6] = 7;
  v11[7] = 3;
  v11[8] = 2;
  v11[9] = 8;
  v8 = v11;
  v4 = v12;
  p_m_pStartScene = (UIScene **)&this->m_pStartScene;
  do
  {
    ((void ( *)(UIScene **, _DWORD, tagRECT *, CGameData *))(*p_m_pStartScene)->m_rect.left)(
      p_m_pStartScene,
      0,
      &pRect,
      this);
    ((void ( *)(UIScene **, _DWORD))((UIWnd *)(*p_m_pStartScene)))(p_m_pStartScene, 0);
    v6 = *(v4 - 1);
    pRect.bottom = *v4;
    pRect.right = v6;
    (((UIWnd *)p_m_pStartScene))->UIWnd::sub_445FA0(&pRect);
    sprintf(Buffer, "ui\\EMOTE\\EM_%02d.tga", v3);
    UIScene_OpenAndLoadResource((int)Buffer);
    UIScene_SetController(1084227584);
    ++v3;
    v4 += 2;
    p_m_pStartScene += 41;
    ++v8;
  }
  while ( v3 < 13 );
  // [overlay-fix 2026-10-27] C2039: _vftable 合成成员不存在（虚调用垃圾形）——待语义修复
  // return (*(int ( **)(CGameData *, _DWORD))this->_vftable)(this, 0);
  return 0;
}

// 0x0044F050
CGameData::~CGameData()
{
  this->CGameData::Cleanup();
  (((UITitle *)&this->m_UITitle))->UITitle::~UITitle();
  (((RoleAtt *)&this->m_nRender))->RoleAtt::~RoleAtt();
  (((UIListBox *)&this->m_nGameMode))->UIListBox::DestroyContent();
  (((RoleCameraCtrl *)&this->m_nSaveSlot))->RoleCameraCtrl::InitBaseWidget();
  UIWnd_RenderText();
  (((UIWnd *)this))->UIWnd::_UIWnd() /* [ROWTABLE] */;
}

// 0x0044F430
void CGameData::Cleanup()
{
  char *m_pGameObj; // ecx
  int m_nMode; // ecx
  int m_nPrevSceneState; // eax
  SceneObj *m_pSceneObjRef; // ecx
  int v6; // [esp+0x0] [ebp-0x4]

  (((SceneObj *)this))->SceneObj::HideAll() /* [ROWTABLE] */;
  PalScript_FreeScriptBuffers(v6);
  (*(void ( **)(int *))(this->m_nRender + 12))(&this->m_nRender);
  m_pGameObj = (char *)this->m_pGameObj;
  if ( m_pGameObj )
  {
    (*(void ( **)(char *, int))(*(_DWORD *)m_pGameObj + 20))(m_pGameObj, 1);
    this->m_pGameObj = ((char *)0);
  }
  m_nMode = this->m_nMode;
  if ( m_nMode )
  {
    (*(void ( **)(int, int))(*(_DWORD *)m_nMode + 20))(m_nMode, 1);
    this->m_nMode = 0;
  }
  m_nPrevSceneState = this->m_nPrevSceneState;
  if ( m_nPrevSceneState != 6 && m_nPrevSceneState && m_nPrevSceneState != 5 )
  {
    m_pSceneObjRef = (SceneObj *)this->m_pSceneObjRef;
    if ( m_pSceneObjRef )
      (*(void ( **)(SceneObj *, int))(*(_DWORD *)((UIWnd *)m_pSceneObjRef) + 20))(m_pSceneObjRef, 1);
    this->m_pSceneObjRef = ((SceneObj *)0);
  }
}

// 0x0044F4C0
int CGameData::SceneUpdate(int nVal, int nVal2)
{
  int m_nSceneLoadParam; // ecx
  char *m_pGameObjB; // ecx
  int v6; // edi
  int result; // eax

  if ( !this->m_bSceneActive )
  {
    if ( this->m_bSceneLoaded )
    {
      m_nSceneLoadParam = this->m_nSceneLoadParam;
      if ( m_nSceneLoadParam )
      {
        if ( !(*(int ( **)(int))(*(_DWORD *)m_nSceneLoadParam + 4))(m_nSceneLoadParam) )
        {
          this->m_bSceneLoaded = 1;
          this->m_bSceneActive = 1;
          this->m_nSceneLoadParam = 0;
          this->CGameData::Load((CUtil *)0xA);
        }
      }
    }
  }
  if ( this->m_nPrevSceneState == 12 )
    (*(void ( **)(char *, int, int))(*(_DWORD *)this->m_pGameObj + 8))(this->m_pGameObj, nVal, nVal2);
  m_pGameObjB = (char *)this->m_pGameObjB;
  if ( m_pGameObjB && m_pGameObjB[3829] )
    (*(void ( **)(char *, int, int))(*(_DWORD *)m_pGameObjB + 8))(m_pGameObjB, nVal, nVal2);
  v6 = (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  if ( !this->m_nPrevSceneState
    && ((*(int ( **)(int *, int, int))(this->m_nRender + 8))(&this->m_nRender, nVal, nVal2) || v6) )
  {
    v6 = 1;
  }
  result = (*(int ( **)(SceneObj *, int, bool))(*(_DWORD *)((UIWnd *)this->m_pSceneObjRef) + 8))(
             this->m_pSceneObjRef,
             nVal,
             v6 == 0);
  if ( result || v6 )
    return 1;
  return result;
}

// 0x0044F5B0
int CGameData::ProcessDialog()
{
  char *m_pGameObjB; // ecx
  int result; // eax

  (*(void ( **)(SceneObj *))(*(_DWORD *)((UIWnd *)this->m_pSceneObjRef) + 4))(this->m_pSceneObjRef);
  if ( this->m_nPrevSceneState == 12 )
    (*(void ( **)(char *))(*(_DWORD *)this->m_pGameObj + 4))(this->m_pGameObj);
  m_pGameObjB = (char *)this->m_pGameObjB;
  if ( m_pGameObjB && m_pGameObjB[3829] )
    (*(void ( **)(char *))(*(_DWORD *)m_pGameObjB + 4))(m_pGameObjB);
  (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  result = this->m_nPrevSceneState;
  if ( !result )
    return (*(int ( **)(int *))(this->m_nRender + 4))(&this->m_nRender);
  return result;
}

// 0x0044F610
int CGameData::Load(CUtil *pUtil)
{
  int v2; // esi
  int v3; // ebx
  int result; // eax
  SceneObj *m_pSceneObjRef; // ecx
  ScreenEffectMgr *v7; // ecx
  void *v8; // esi
  ScreenEffect *Instance; // eax
  int v10; // eax
  char *m_pGameObj; // ecx
  int m_nPrevSceneState; // eax
  SceneObj *v13; // ecx
  void *v14; // esi
  int v15; // [esp-0x4] [ebp-0x10]

  v3 = (int)pUtil;
  if ( pUtil != (CUtil *)8 || this->m_nPrevSceneState || (result = (unsigned __int8)byte_D92785, !(_BYTE)byte_D92785) )
  {
    result = this->m_nPrevSceneState;
    v15 = v2;
    if ( (CUtil *)result != pUtil )
    {
      this->m_nSceneTransition = result;
      if ( result == 7 )
        qmemcpy(
          &g_SceneTransitionBuffer,
          (const void *)(((UISceneMap *)this->m_pSceneObjRef))->UISceneMap::GetSceneInfo(),
          0x27848u);
      if ( this->m_nPrevSceneState == 8 )
        (((SceneObj *)this->m_pSceneObjRef))->SceneObj::GetVisibleFlag(&p_BYTE);
      if ( this->m_nPrevSceneState == 9 )
      {
        m_pSceneObjRef = (SceneObj *)this->m_pSceneObjRef;
        if ( m_pSceneObjRef )
          (*(void ( **)(SceneObj *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)m_pSceneObjRef) + 24))(
            m_pSceneObjRef,
            1000,
            0,
            0);
      }
      v7 = (ScreenEffectMgr *)g_nMiniGameParam;
      if ( g_nMiniGameParam == g_nMiniGameState )
      {
        if ( g_bSceneLoaded_0 )
        {
          v8 = g_pMiniGame3;
          if ( g_pMiniGame3 )
          {
            (((ArcPastScene *)g_pMiniGame3))->ArcPastScene::FreeChildList();
            operator delete(v8);
            g_pMiniGame3 = 0;
            g_bSceneLoaded_0 = 0;
            g_nMiniGameParam = 1;
            g_nMiniGameState = 0;
          }
        }
      }
      if ( pUtil != (CUtil *)10 || this->m_bSceneLoaded )
      {
        m_nPrevSceneState = this->m_nPrevSceneState;
        this->m_bSceneLoaded = 0;
        if ( m_nPrevSceneState != 6 )
        {
          if ( m_nPrevSceneState )
          {
            if ( m_nPrevSceneState != 5 && m_nPrevSceneState != 12 && m_nPrevSceneState != 10 )
            {
              v13 = (SceneObj *)this->m_pSceneObjRef;
              if ( v13 )
              {
                (*(void ( **)(SceneObj *, int))(*(_DWORD *)((UIWnd *)v13) + 20))(v13, 1);
                this->m_pSceneObjRef = ((SceneObj *)0);
              }
            }
          }
        }
        if ( this->m_nPrevSceneState == 10 )
        {
          v14 = g_pMiniGame1;
          if ( g_pMiniGame1 )
          {
            (((CCBStageScene *)g_pMiniGame1))->CCBStageScene::CleanupCamera();
            operator delete(v14);
            g_pMiniGame1 = 0;
          }
        }
        result = (int)this->CGameData::_init_44f8d0((int)pUtil, v15);
        this->m_pSceneObjRef = ((SceneObj *)((SceneObj *)result));
        this->m_nPrevSceneState = (int)pUtil;
      }
      else
      {
        Instance = (((ScreenEffectMgr *)v7))->ScreenEffectMgr::GetInstance();
        v10 = (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(1);
        m_pGameObj = (char *)this->m_pGameObj;
        this->m_nSceneLoadParam = v10;
        result = (**(int ( ***)(char *, _DWORD))m_pGameObj)((char *)(m_pGameObj), (_DWORD)(0));
        v3 = this->m_nPrevSceneState;
        this->m_bSceneLoaded = 1;
        this->m_bSceneActive = 0;
        g_nSceneState = 1;
      }
    }
    switch ( v3 )
    {
      case 0:
        g_nSceneState = 2;
        result = (int)CombatEnter();
        break;
      case 6:
        g_nSceneState = 3;
        break;
      case 9:
      case 13:
      case 14:
        g_nSceneState = 1;
        break;
      case 10:
        g_nSceneState = 4;
        break;
      case 11:
        g_nSceneState = 5;
        break;
      case 12:
        g_nSceneState = 6;
        break;
      case 15:
        g_nSceneState = 9;
        result = (int)CombatEnter();
        break;
      default:
        break;
    }
    if ( this->m_nSceneTransFlag )
      result = (*(int ( **)(int *, _DWORD))this->m_nSaveSlot)(&this->m_nSaveSlot, 0);
    if ( this->m_nPrevSceneState == 14 )
    {
      result = (int)this->m_pSceneObjRef;
      g_nsub_41FA90_DC10FC = result;
    }
    else
    {
      g_nsub_41FA90_DC10FC = 0;
    }
  }
  return result;
}

// 0x0044F8A0
int CGameData::SetMode(int nVal)
{
  if ( !nVal )
    return (int)this->m_pGameObj;
  if ( nVal == 5 )
    return this->m_nMode;
  return (int)this->m_pSceneObjRef;
}

// 0x0044F8D0
CCBUI * CGameData::_init_44f8d0(int thisa, int a2)
{
  UILoadingFrm *v4; // eax
  UILoadingFrm *v5; // eax
  CCBUI *v6; // esi
  CCBUI *result; // eax
  UISceneMap *v8; // eax
  UIGameOver *v9; // eax
  int *v10; // esi
  UIScenePanel *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // esi
  UISceneFrm *v14; // eax
  CScreenMode *v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // ecx
  UITitle_ArcSave *v21; // eax
  CScreenMode *v22; // eax
  CScreenMode *v23; // esi
  CUtil *v24; // eax
  CUtil *v25; // eax
  CUtil *v26; // esi
  UIListBox *v27; // eax
  CScreenMode *v28; // esi
  UIRoleSelectDialog *v29; // eax
  UIEmote *v30; // eax
  _DWORD *inited; // esi
  SceneMgr *v32; // eax
  int *CurrentNode; // esi
  void *v34; // ecx
  ArcPastScene *v35; // eax
  UICursor *v36; // eax
  int v37; // ecx
  CCBUIPanel *v38; // eax
  CScreenMode *v39; // eax
  double v40; // [esp+0x4] [ebp-0x14]
  unsigned __int8 v41; // [esp+0x4] [ebp-0x14]
  unsigned __int8 v42; // [esp+0x4] [ebp-0x14]
  unsigned __int8 v43; // [esp+0x4] [ebp-0x14]
  unsigned __int8 v44; // [esp+0x4] [ebp-0x14]

  switch ( thisa )
  {
    case 0:
      return (CCBUI *)this->m_pGameObj;
    case 2:
      v14 = (UISceneFrm *)operator new(0xCD8u);
      if ( v14 )
      {
        v14->UISceneFrm::UISceneFrm();
        v13 = (CScreenMode *)v15;
      }
      else
      {
        v13 = 0;
      }
      (((CScreenMode *)v13))->CScreenMode::InitGameUI();
      (((UITitle_YXXX *)v13))->UITitle_YXXX::LayoutWidgets();
      LOWORD(v16) = (((CCBUI *)v13))->CCBUI::ForwardToPlayerMgr(&p_WORD);
      LOBYTE(v16) = *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 592);
      (((CCBStage *)v13))->CCBStage::sub_00459fa0(v16, LOBYTE(v40));
      LOBYTE(v17) = *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 593);
      (((CCBStage *)v13))->CCBStage::sub_0045a020(v17, v41);
      LOBYTE(v18) = *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 594);
      (((CCBStage *)v13))->CCBStage::sub_0045a0a0(v18, v42);
      LOBYTE(v19) = *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 596);
      (((CCBStage *)v13))->CCBStage::sub_0045a1a0(v19, v43);
      LOBYTE(v20) = *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 595);
      (((CCBStage *)v13))->CCBStage::sub_0045a120(v20, v44);
      goto LABEL_60;
    case 3:
      v21 = (UITitle_ArcSave *)operator new(0xFA4u);
      if ( v21 )
      {
        v21->UITitle_ArcSave::UITitle_ArcSave();
        v23 = (CScreenMode *)v22;
      }
      else
      {
        v23 = 0;
      }
      (((CScreenMode *)v23))->CScreenMode::InitEquipScreen();
      PAL3_DispatchModeCommand(0);
      return (CCBUI *)v23;
    case 4:
      v11 = (UIScenePanel *)operator new(0x379Cu);
      if ( v11 )
      {
        v11->UIScenePanel::UIScenePanel();
        v13 = (CScreenMode *)v12;
      }
      else
      {
        v13 = 0;
      }
      (((UIScenePanel *)v13))->UIScenePanel::CreateSettingsUI();
      goto LABEL_12;
    case 5:
      (((RoleStatePanel *)this->m_nMode))->RoleStatePanel::HandleDeviceLostB();
      (((MainEquipUI *)this->m_nMode))->MainEquipUI::HandleMessage(0);
      return (CCBUI *)this->m_nMode;
    case 6:
      return g_pCBSystem->m_pUI;
    case 7:
      v24 = (CUtil *)operator new(0x6ECu);
      if ( v24 )
      {
        v24->CUtil::CUtil();
        v26 = (CUtil *)v25;
      }
      else
      {
        v26 = 0;
      }
      (((CUtil *)v26))->CUtil::InitGameSystems();
      sub_523CD0(*((unsigned __int8 *)&g_RoleSlotBuf.dword_17AA450 + 592));
      sub_523D20(*((unsigned __int8 *)&g_RoleSlotBuf.dword_17AA450 + 593));
      sub_523D70(*((unsigned __int8 *)&g_RoleSlotBuf.dword_17AA450 + 594));
      sub_523E10(*((unsigned __int8 *)&g_RoleSlotBuf.dword_17AA450 + 596));
      sub_523DC0(*((unsigned __int8 *)&g_RoleSlotBuf.dword_17AA450 + 595));
      (((CUtil *)v26))->CUtil::DispatchCommand(&g_SceneTransitionBuffer);
      CUtil_Update(0);
      return (CCBUI *)v26;
    case 8:
      v27 = (UIListBox *)operator new(0x6E0u);
      if ( v27 )
        v28 = (CScreenMode *)(((UIListBox *)v27))->UIListBox::ctor();
      else
        v28 = 0;
      SoundContext_CreateSubPanels(this->m_nPrevSceneState);
      (((CScreenMode *)v28))->CScreenMode::InitSceneAudio(0);
      return (CCBUI *)v28;
    case 9:
      v29 = (UIRoleSelectDialog *)operator new(0x89Cu);
      if ( v29 )
      {
        v29->UIRoleSelectDialog::UIRoleSelectDialog();
        v13 = (CScreenMode *)v30;
        (((UIEmote *)v30))->UIEmote::Render();
      }
      else
      {
        v13 = 0;
        (((UIEmote *)0))->UIEmote::Render();
      }
LABEL_12:
      if ( !v13 )
        goto LABEL_62;
      (*((void ( **)(CScreenMode *, int, int, _DWORD))v13->m_pEnumeration + 6))(v13, 1000, 1, 0);
      result = (CCBUI *)v13;
      break;
    case 10:
      if ( operator new(0x414u) )
        inited = (_DWORD *)CCBStageScene_InitCameraPositions(SLODWORD(v40));
      else
        inited = 0;
      CCBStageScene_CreateCamera(this->m_nMoneySub);
      g_pMiniGame1 = inited;
      v13 = (CScreenMode *)inited[1];
      goto LABEL_60;
    case 11:
      v32 = (SceneMgr *)operator new(0x130u);
      if ( v32 )
        CurrentNode = (((SceneMgr *)v32))->SceneMgr::GetCurrentNode();
      else
        CurrentNode = 0;
      (((CCBFiveNimbusWindow *)CurrentNode))->CCBFiveNimbusWindow::GetValue(this->m_nPrevSceneState);
      (((CScreenMode *)CurrentNode))->CScreenMode::InitEndScreen();
      g_pMiniGame2 = (void *)CurrentNode;
      return (CCBUI *)CurrentNode[2];
    case 12:
      v34 = g_pMiniGame3;
      if ( g_pMiniGame3 )
      {
        if ( !g_nMiniGameState && dword_D92780 == g_nMiniGameParam && this->m_nPrevSceneState != 5 )
        {
          (((ArcLocaleRole *)g_pMiniGame3))->ArcLocaleRole::GetScreenLeft(v40);
          v34 = g_pMiniGame3;
        }
        return (CCBUI *)*((_DWORD *)v34 + 5);
      }
      else
      {
        v35 = (ArcPastScene *)operator new(0x40u);
        if ( v35 )
          v36 = (UICursor *)(((ArcPastScene *)v35))->ArcPastScene::ResetCityName();
        else
          v36 = 0;
        g_pMiniGame3 = v36;
        (((UICursor *)v36))->UICursor::Update(v40);
        g_bSceneLoaded_0 = 0;
        v37 = *((_DWORD *)g_pMiniGame3 + 5);
        if ( v37 )
          (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v37 + 24))(v37, 1000, 1, 0);
        return (CCBUI *)*((_DWORD *)g_pMiniGame3 + 5);
      }
    case 13:
      v38 = (CCBUIPanel *)operator new(0x5660u);
      if ( v38 )
      {
        v38->CCBUIPanel::CCBUIPanel();
        v13 = (CScreenMode *)v39;
      }
      else
      {
        v13 = 0;
      }
      (((CCBUIPanel *)v13))->CCBUIPanel::InitPanel();
LABEL_60:
      if ( v13 )
        (*((void ( **)(CScreenMode *, int, int, _DWORD))v13->m_pEnumeration + 6))(v13, 1000, 1, 0);
LABEL_62:
      result = (CCBUI *)v13;
      break;
    case 14:
      v4 = (UILoadingFrm *)operator new(0x14Cu);
      if ( v4 )
      {
        v4->UILoadingFrm::UILoadingFrm();
        v6 = (CCBUI *)v5;
        (((UILoadingFrm *)v5))->UILoadingFrm::InitFullScreen();
        result = (CCBUI *)v6;
      }
      else
      {
        (((UILoadingFrm *)0))->UILoadingFrm::InitFullScreen();
        result = 0;
      }
      break;
    case 15:
      v8 = (UISceneMap *)operator new(0xE8u);
      if ( v8 )
      {
        v8->UISceneMap::UISceneMap();
        // [overlay-fix 2026-10-27] C2440: CCBUI* 赋 int* 局部量（垃圾形）——待语义修复
        // v10 = (CCBUI *)v9;
        v10 = 0;
        (((UIGameOver *)v9))->UIGameOver::Create();
        result = (CCBUI *)v10;
      }
      else
      {
        (((UIGameOver *)0))->UIGameOver::Create();
        result = 0;
      }
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x0044FF60
int CGameData::GetMode()
{
  return this->m_nSceneTransition;
}
