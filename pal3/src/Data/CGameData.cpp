#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Data/CGameData.h"

// Forward declarations for unnamed functions
int sub_445FA0(void *a2); // from annotations

gbGfxManager * CombatEnter(void); // from annotations

// Unnamed globals (extern)
extern char byte_AABEF7;
extern char byte_AABEF8;
extern char byte_AABEF9;
extern char byte_D92785;
extern void *off_59BA94;
extern float unk_D91780;
extern int unk_D91781;
extern int unk_D91782;
extern int unk_D91783;

// 0x00445A60
char CGameData::SetDefaultColors()
{
  char result; // al

  result = 64;
  if ( gbColorQuad::ColorQuadFmt )
  {
    unk_D91782 = 60;
    unk_D91781 = 64;
    LOBYTE(unk_D91780) = 64;
  }
  else
  {
    LOBYTE(unk_D91780) = 60;
    unk_D91782 = 64;
    unk_D91781 = 64;
  }
  unk_D91783 = -56;
  return result;
}

// 0x0044ADE0
int CGameData::InitRoles(int nVal)
{
  int d06C; // ecx
  int d070; // eax
  UIWnd *d07C; // edx
  int *p_m_subObjA; // edi
  int result; // eax
  int v8; // [esp+0x84] [ebp-0x10] BYREF
  int v9; // [esp+0x88] [ebp-0xC]
  int v10; // [esp+0x8C] [ebp-0x8]
  int v11; // [esp+0x90] [ebp-0x4]
  int nVala; // [esp+0x98] [ebp+0x4]

  this->_d050 = 0;
  this->_d04C = 0;
  this->_d054 = 800;
  this->_d058 = 600;
  ((PalScript *)this)->Create((int)g_PalScriptTemplate, (tagRECT *)&this->_d04C, nVal);
  d06C = this->_d06C;
  d070 = this->_d070;
  d07C = this->_d07C;
  this->_d060 = d070;
  this->_d05C = d06C;
  this->_d064 = d06C + 68;
  LODWORD(this->_d068) = d070 + 32;
  ((void ( *)(UIWnd **, unsigned __int8 *, int *, CGameData *))d07C->m_rect.left)(
    &this->_d07C,
    g_PalScriptTemplate,
    &this->_d05C,
    this);
  ((UIStatic *)&this->_d07C)->CreateFromTemplate();this->_d07C->ShowWindow(0);
p_m_subObjA = &this->m_subObjA;
  nVala = 3;
  do
  {
    (*(void ( **)(int *, unsigned __int8 *, int *, CGameData *))(*p_m_subObjA + 16))(
      p_m_subObjA,
      g_PalScriptTemplate,
      &this->_d05C,
      this);
    ((UIStatic *)p_m_subObjA)->CreateFromTemplate();
    (*(void ( **)(int *, _DWORD))*p_m_subObjA)(p_m_subObjA, 0);
    p_m_subObjA += 38;
    --nVala;
  }
  while ( nVala );
  ((void ( *)(UIWnd **, unsigned __int8 *, int *, CGameData *))this->m_nInitRoles->m_rect.left)(
    &this->m_nInitRoles,
    g_PalScriptTemplate,
    &this->_d05C,
    this);
  ((UIStatic *)&this->m_nInitRoles)->CreateFromTemplate();this->m_nInitRoles->ShowWindow(0);
((void ( *)(CScreenMode **, char *, int *, CGameData *, char *, _DWORD, int))LODWORD(this->m_RoleDataA->m_fFadeAlpha))(
    &this->m_RoleDataA,
    &byte_AABEF7,
    &this->_d05C,
    this,
    off_59BA94,
    0,
    1);
  ((CScreenMode *)&this->m_RoleDataA)->SetTooltipText();
  this->_d3DC = 0;
  this->_d3E0 = 2;
  ((void ( *)(CScreenMode **, _DWORD))this->m_RoleDataA->m_pEnumeration)(&this->m_RoleDataA, 0);
  ((void ( *)(CScreenMode **, char *, int *, CGameData *, char *, _DWORD, int))LODWORD(this->m_RoleDataB->m_fFadeAlpha))(
    &this->m_RoleDataB,
    &byte_AABEF8,
    &this->_d05C,
    this,
    off_59BA94,
    0,
    1);
  ((CScreenMode *)&this->m_RoleDataB)->SetTooltipText();
  this->_d534 = 0;
  this->_d538 = 2;
  ((void ( *)(CScreenMode **, _DWORD))this->m_RoleDataB->m_pEnumeration)(&this->m_RoleDataB, 0);
  ((void ( *)(CScreenMode **, char *, int *, CGameData *, char *, _DWORD, int))LODWORD(this->m_RoleDataC->m_fFadeAlpha))(
    &this->m_RoleDataC,
    byte_AABEF9,
    &this->_d05C,
    this,
    off_59BA94,
    0,
    1);
  ((CScreenMode *)&this->m_RoleDataC)->SetTooltipText();
  this->_d68C = 0;
  this->_d690 = 2;
  ((void ( *)(CScreenMode **, _DWORD))this->m_RoleDataC->m_pEnumeration)(&this->m_RoleDataC, 0);
  v9 = 200;
  v8 = 300;
  v10 = 600;
  v11 = 456;
  ((ARC_PlayerAtt *)&this->m_ItemSlotA)->Create((int)&g_PlayerAttBuffer2.skill[2], (int)&v8);
  ((UIItem *)&this->m_ItemSlotA)->SetData(31);
  v10 = v8 + 256;
  v11 = v9 + 128;
  ((ARC_PlayerAtt *)&this->m_ItemSlotB)->Create((int)&g_PlayerAttBuffer2.id + 1, (int)&v8);
  ((UIItem *)&this->m_ItemSlotB)->SetData(31);
  ((ARC_PlayerAtt *)&this->m_ItemSlotC)->Create((int)&g_PlayerAttBuffer2.id + 2, (int)&v8);
  ((UIItem *)&this->m_ItemSlotC)->SetData(18);
  ((ARC_PlayerAtt *)&this->m_ItemSlotD)->Create((int)&g_PlayerAttBuffer2.id + 3, (int)&v8);
  result = (int)((UIItem *)&this->m_ItemSlotD)->SetData(31);
  this->m_nScriptHandleB = 0;
  this->m_nScriptHandleA = 0;
  this->m_nScriptHandleC = 0;
  this->m_nScriptHandleD = 0;
  this->m_nScriptHandleE = 0;
  this->m_nScriptHandleF = 0;
  this->m_bInitRoles = 0;
  this->m_bScriptActive = 0;
  this->m_nScriptResult = 0;
  this->_todo_CE8 = 0;
  this->_todo_CE9 = 0;
  this->_todo_CD8 = 0;
  this->m_bScriptRunning = 0;
  return result;
}

// 0x0044E660
int CGameData::InitItems(int nVal)
{
  int v3; // edi
  LONG *v4; // ebp
  UIScene *p_m_pStartScene; // esi
  LONG v6; // eax
  UIWnd **v8; // [esp+0x10] [ebp-0x1B4]
  tagRECT pRect; // [esp+0x14] [ebp-0x1B0] BYREF
  int v10; // [esp+0x24] [ebp-0x1A0]
  _DWORD v11[15]; // [esp+0x28] [ebp-0x19C] BYREF
  _DWORD v12[23]; // [esp+0x64] [ebp-0x160] BYREF
  char Buffer[260]; // [esp+C0h] [ebp-0x104] BYREF

  pRect.top = 0;
  pRect.left = 0;
  pRect.bottom = 600;
  pRect.right = 800;
  ((PalScript *)this)->Create(0, &pRect, nVal);
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
  v8 = (UIWnd **)v11;
  v4 = v12;
  p_m_pStartScene = (UIScene *)&this->m_pStartScene;
  do
  {
// [VFTABLE] ((void ( *)(UIScene *, _DWORD, tagRECT *, CGameData *))p_m_pStartScene->__vftable->Create)(
// [VFTABLE]   p_m_pStartScene,
// [VFTABLE]   0,
// [VFTABLE]   &pRect,
// [VFTABLE]   this);
// [VFTABLE] ((void ( *)(UIScene *, _DWORD))p_m_pStartScene->__vftable->ShowWindow)(p_m_pStartScene, 0);
    v6 = *(v4 - 1);
    pRect.bottom = *v4;
    pRect.right = v6;
    sub_445FA0(p_m_pStartScene);
    sprintf(Buffer, "ui\\EMOTE\\EM_%02d.tga", v3);
    ((UIScene *)p_m_pStartScene)->OpenAndLoadResource((BOOL)Buffer, *v8);
    ((UIScene *)p_m_pStartScene)->SetController(1084227584);
    ++v3;
    v4 += 2;
    p_m_pStartScene = (UIScene *)((char *)p_m_pStartScene + 164);
    ++v8;
  }
  while ( v3 < 13 );
  return (*(int ( **)(CGameData *, _DWORD))this->_vftable)(this, 0);
}

// 0x0044F050
void CGameData::ctor()
{

  ((UITitle *)&this->m_UITitle)->_UITitle();
  ((RoleAtt *)&this->m_nRender)->_RoleAtt();
  ((UIListBox *)&this->m_nGameMode)->DestroyContent();
  ((RoleCameraCtrl *)&this->m_nSaveSlot)->InitBaseWidget();
  ((UIWnd *)&this->m_nInit)->RenderText();
  ((UIWnd *)this)->_UIWnd();
}

// 0x0044F430
void CGameData::Cleanup()
{
  char *m_pGameObj; // ecx
  int m_nMode; // ecx
  int m_nPrevSceneState; // eax
  SceneObj *m_pSceneObjRef; // ecx

  ((UIWnd *)this)->HideAll();
  ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[68])->FreeScriptBuffers();
  (*(void ( **)(int *))(this->m_nRender + 12))(&this->m_nRender);
  m_pGameObj = this->m_pGameObj;
  if ( m_pGameObj )
  {
    (*(void ( **)(char *, int))(*(_DWORD *)m_pGameObj + 20))(m_pGameObj, 1);
    this->m_pGameObj = 0;
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
    m_pSceneObjRef = this->m_pSceneObjRef;
    if ( m_pSceneObjRef )
// [VFTABLE] (*((void ( **)(SceneObj *, int))m_pSceneObjRef->__vftable + 5))(m_pSceneObjRef, 1);
    this->m_pSceneObjRef = 0;
  }
}

// 0x0044F4C0
int CGameData::SceneUpdate(int nVal, int nVal2)
{
  int v3; // ecx
  _BYTE *v4; // ecx
  int v5; // edi
  int result; // eax
  int a3; // [esp+0x18] [ebp+0x8]

  if ( !*(_BYTE *)(nVal + 653) )
  {
    if ( *(_BYTE *)(nVal + 652) )
    {
      v3 = *(_DWORD *)(nVal + 648);
      if ( v3 )
      {
        if ( !(*(int ( **)(int))(*(_DWORD *)v3 + 4))(v3) )
        {
          *(_BYTE *)(nVal + 652) = 1;
          *(_BYTE *)(nVal + 653) = 1;
          *(_DWORD *)(nVal + 648) = 0;
          ((CGameData *)nVal)->Load((CUtil *)0xA);
        }
      }
    }
  }
  if ( *(_DWORD *)(nVal + 14536) == 12 )
    (*(void ( **)(_DWORD, int, int))(**(_DWORD **)(nVal + 28176) + 8))(*(_DWORD *)(nVal + 28176), nVal2, a3);
  v4 = *(_BYTE **)(nVal + 28184);
  if ( v4 && v4[3829] )
    (*(void ( **)(_BYTE *, int, int))(*(_DWORD *)v4 + 8))(v4, nVal2, a3);
  v5 = ((UIListBox *)nVal)->Update(nVal2, a3);
  if ( !*(_DWORD *)(nVal + 14536)
    && ((*(int ( **)(int, int, int))(*(_DWORD *)(nVal + 3904) + 8))(nVal + 3904, nVal2, a3) || v5) )
  {
    v5 = 1;
  }
  result = (*(int ( **)(_DWORD, int, bool))(**(_DWORD **)(nVal + 14532) + 8))(
             *(_DWORD *)(nVal + 14532),
             nVal2,
             v5 == 0);
  if ( result || v5 )
    return 1;
  return result;
}

// 0x0044F5B0
int CGameData::ProcessDialog()
{
  char *m_pGameObjB; // ecx
  int result; // eax

// [VFTABLE] (*((void ( **)(SceneObj *))this->m_pSceneObjRef->__vftable + 1))(this->m_pSceneObjRef);
  if ( this->m_nPrevSceneState == 12 )
    (*(void ( **)(char *))(*(_DWORD *)this->m_pGameObj + 4))(this->m_pGameObj);
  m_pGameObjB = this->m_pGameObjB;
  if ( m_pGameObjB && m_pGameObjB[3829] )
    (*(void ( **)(char *))(*(_DWORD *)m_pGameObjB + 4))(m_pGameObjB);
  ((UIWnd *)this)->Render();
  result = this->m_nPrevSceneState;
  if ( !result )
    return (*(int ( **)(int *))(this->m_nRender + 4))(&this->m_nRender);
  return result;
}

// 0x0044F610
int CGameData::Load(CUtil *pUtil)
{
  int v2; // ebx
  int result; // eax
  SceneObj *m_pSceneObjRef; // ecx
  ScreenEffectMgr *v6; // ecx
  void *v7; // esi
  ScreenEffect *Instance; // eax
  int v9; // eax
  char *m_pGameObj; // ecx
  int m_nPrevSceneState; // eax
  SceneObj *v12; // ecx
  void *v13; // esi

  v2 = (int)pUtil;
  if ( pUtil != (CUtil *)8 || this->m_nPrevSceneState || (result = (unsigned __int8)byte_D92785, !byte_D92785) )
  {
    result = this->m_nPrevSceneState;
    if ( (CUtil *)result != pUtil )
    {
      this->m_nSceneTransition = result;
      if ( result == 7 )
        qmemcpy(pCmd, (const void *)((UISceneMap *)this->m_pSceneObjRef)->fn_523E60(), 0x27848u);
      if ( this->m_nPrevSceneState == 8 )
        ((SceneObj *)this->m_pSceneObjRef)->GetVisibleFlag(&p_BYTE);
      if ( this->m_nPrevSceneState == 9 )
      {
        m_pSceneObjRef = this->m_pSceneObjRef;
        if ( m_pSceneObjRef )
// [VFTABLE] (*((void ( **)(SceneObj *, int, _DWORD, _DWORD))m_pSceneObjRef->__vftable + 6))(
// [VFTABLE]   m_pSceneObjRef,
// [VFTABLE]   1000,
// [VFTABLE]   0,
// [VFTABLE]   0);
      }
      v6 = (ScreenEffectMgr *)g_nMiniGameParam;
      if ( g_nMiniGameParam == g_nMiniGameState )
      {
        if ( g_bSceneLoaded_0 )
        {
          v7 = g_pMiniGame3;
          if ( g_pMiniGame3 )
          {
            ((ArcPastScene *)g_pMiniGame3)->FreeChildList();
            operator delete(v7);
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
              v12 = this->m_pSceneObjRef;
              if ( v12 )
              {
// [VFTABLE] (*((void ( **)(SceneObj *, int))v12->__vftable + 5))(v12, 1);
                this->m_pSceneObjRef = 0;
              }
            }
          }
        }
        if ( this->m_nPrevSceneState == 10 )
        {
          v13 = g_pMiniGame1;
          if ( g_pMiniGame1 )
          {
            ((CCBStageScene *)g_pMiniGame1)->CleanupCamera();
            operator delete(v13);
            g_pMiniGame1 = 0;
          }
        }
        result = (int)init_44f8d0((int)this, (int)pUtil);
        this->m_pSceneObjRef = (SceneObj *)result;
        this->m_nPrevSceneState = (int)pUtil;
      }
      else
      {
        Instance = ((ScreenEffectMgr *)v6)->GetInstance();
        v9 = ((ScreenEffectMgr *)Instance)->ProcessEffect();
        m_pGameObj = this->m_pGameObj;
        this->m_nSceneLoadParam = v9;
        result = (**(int ( ***)(char *, _DWORD))m_pGameObj)(m_pGameObj, 0);
        v2 = this->m_nPrevSceneState;
        this->m_bSceneLoaded = 1;
        this->m_bSceneActive = 0;
        g_nSceneState = 1;
      }
    }
    switch ( v2 )
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

// 0x0044FF60
int CGameData::GetMode()
{
  return this->m_nSceneTransition;
}
