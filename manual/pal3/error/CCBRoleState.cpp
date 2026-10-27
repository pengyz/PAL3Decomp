#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBRoleState.h"
#include "Role/Actor.h"
#include "Effect/C2DSpark.h"
#include "Combat/CCBAI.h"
#include "Combat/CCBAttackSequen.h"
#include "Combat/CCBCamControl.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBParabolaWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBStageScene.h"
#include "Combat/CCBStageShadow.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Misc/CCBUIPanel.h"
#include "Effect/CEffMgr.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/CameraCtrl.h"
#include "Misc/ChoseCompose.h"
#include "Combat/Combat.h"
#include "Misc/ECBStageTaskState.h"
#include "Misc/FightInfo.h"
#include "GameBase/GRPinput.h"
#include "GameBase/Logger.h"
#include "Role/NPC.h"
#include "Misc/NameSys.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PlayerItem.h"
#include "UI/PropUI.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleCameraCtrl.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/UIAnimateCtrl.h"
#include "Misc/UIButton.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/tagCmdData.h"
#include "Misc/tagRoleState.h"
#include "Misc/unchar.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern char aWa014[];
extern char aWa015[];
extern CHAR byte_DC6A3C[256];
extern int dword_DCA13C;
extern int dword_DCA23C;
extern int dword_DDB93C;
extern LPCSTR off_5B0E28;

// 0x0043DE40
int CCBRoleState::Destroy(int nMode)
{
  gbRefObject *v2; // ecx
  int result; // eax

  v2 = (gbRefObject *)*(gbRefObject **)(nMode + 68);
  if ( v2 )
  {
    (((gbRefObject *)v2))->gbRefObject::Release();
    *(_DWORD *)(nMode + 68) = 0;
  }
  (((SceneObj *)nMode))->SceneObj::HideAll();
  return result;
}

// 0x004499A0
char CCBRoleState::sub_4499A0(void *thisa, unsigned int a2, int a3)
{
  char result; // al
  int ( ***v5)(int, int); // esi
  int ( ***v6)(int, int); // esi
  char *v7; // esi

  result = (char)thisa;
  if ( (unsigned int)thisa <= 0x25 )
  {
    if ( a2 )
    {
      if ( a2 == 1 )
      {
        v6 = (int ( ***)(int, int))((char *)this + 476 * (_DWORD)thisa);
        result = *((_BYTE *)v6 + 984);
        if ( result )
        {
          result = (*v6[152])((int)(v6 + 152), 1);
          *((_BYTE *)v6 + 985) = 1;
        }
        *((_BYTE *)v6 + 512) = 1;
        *((_BYTE *)v6 + 596) = 0;
      }
      else if ( a2 == 2 )
      {
        v5 = (int ( ***)(int, int))((char *)this + 476 * (_DWORD)thisa);
        result = *((_BYTE *)v5 + 984);
        if ( result )
        {
          result = (*v5[152])((int)(v5 + 152), 1);
          *((_BYTE *)v5 + 985) = 1;
        }
        *((_BYTE *)v5 + 512) = 1;
        *((_BYTE *)v5 + 596) = 1;
      }
    }
    else
    {
      v7 = (char *)this + 476 * (_DWORD)thisa;
      result = v7[984];
      if ( result )
      {
        result = (**((int ( ***)(int, _DWORD))v7 + 152))((int)((int)(v7 + 608)), (_DWORD)(0));
        v7[985] = 0;
      }
      v7[512] = 0;
      v7[596] = 0;
    }
  }
  return result;
}

// 0x00449F00
__int64 CCBRoleState::CalcSpringForce(int nVal, int nVal2)
{
  float m_fSpringPrevX_low; // st7
  __int64 result; // rax
  int nVala; // [esp+0x10] [ebp+0x4]

  CCBUIPanel_EnsureSize(nVal);
  LODWORD(this->m_fSpringPrevX) = nVal;
  LODWORD(this->m_fSpringPrevY) = nVal2;
  m_fSpringPrevX_low = (float)SLODWORD(this->m_fSpringPrevX);
  *(float *)&this->m_nSpringTargetX = m_fSpringPrevX_low;
  *(float *)&nVala = (float)SLODWORD(this->m_fSpringPrevY);
  this->m_nSpringTargetY = nVala;
  LODWORD(this->m_fSpringPrevX) = (__int64)m_fSpringPrevX_low;
  result = (__int64)*(float *)&nVala;
  LODWORD(this->m_fSpringPrevY) = result;
  this->m_bSpringDoneX = 1;
  return result;
}

// 0x00449FE0
int CCBRoleState::UpdateSpringAnim(float fDelta)
{
  float m_fSpringTargX; // eax
  float m_fSpringPrevX; // ecx
  float v5; // st7
  float v6; // st7
  float m_fSpringTargY; // eax
  float m_fSpringPrevY; // ecx
  float v9; // st7
  float v10; // st7
  float m_fSpringPosY; // st7
  float v12; // edi
  int result; // eax
  float v14; // [esp+0x4] [ebp-0x4]
  float v15; // [esp+0x4] [ebp-0x4]
  float fDeltaa; // [esp+0xC] [ebp+0x4]
  float fDeltab; // [esp+0xC] [ebp+0x4]

  m_fSpringTargX = this->m_fSpringTargX;
  m_fSpringPrevX = this->m_fSpringPrevX;
  this->m_bSpringDoneY = 0;
  if ( SLODWORD(m_fSpringTargX) >= SLODWORD(m_fSpringPrevX) )
  {
    if ( SLODWORD(m_fSpringTargX) > SLODWORD(m_fSpringPrevX) )
    {
      v6 = this->m_fSpringPosX - fDelta * this->m_fSpringSpeed * (float)this->m_nSpringDir;
      this->m_fSpringPosX = v6;
      v15 = (float)SLODWORD(m_fSpringPrevX);
      if ( v6 <= v15 )
        this->m_fSpringPosX = v15;
    }
  }
  else
  {
    v5 = fDelta * this->m_fSpringSpeed * (float)this->m_nSpringDir + this->m_fSpringPosX;
    this->m_fSpringPosX = v5;
    v14 = (float)SLODWORD(m_fSpringPrevX);
    if ( v5 >= v14 )
      this->m_fSpringPosX = v14;
  }
  m_fSpringTargY = this->m_fSpringTargY;
  m_fSpringPrevY = this->m_fSpringPrevY;
  if ( SLODWORD(m_fSpringTargY) >= SLODWORD(m_fSpringPrevY) )
  {
    if ( SLODWORD(m_fSpringTargY) > SLODWORD(m_fSpringPrevY) )
    {
      v10 = this->m_fSpringPosY - fDelta * this->m_fSpringSpeed * (float)this->m_nSpringDir;
      this->m_fSpringPosY = v10;
      fDeltab = (float)SLODWORD(m_fSpringPrevY);
      if ( v10 <= fDeltab )
        this->m_fSpringPosY = fDeltab;
    }
  }
  else
  {
    v9 = fDelta * this->m_fSpringSpeed * (float)this->m_nSpringDir + this->m_fSpringPosY;
    this->m_fSpringPosY = v9;
    fDeltaa = (float)SLODWORD(m_fSpringPrevY);
    if ( v9 >= fDeltaa )
      this->m_fSpringPosY = fDeltaa;
  }
  m_fSpringPosY = this->m_fSpringPosY;
  LODWORD(v12) = (__int64)this->m_fSpringPosX;
  this->m_fSpringTargX = v12;
  LODWORD(this->m_fSpringTargY) = (__int64)m_fSpringPosY;
  *(_DWORD *)&this->m_RoleXor[11].sModel[4] = (__int64)m_fSpringPosY;
  *(float *)this->m_RoleXor[11].sModel = v12;
  *(_DWORD *)&this->m_RoleXor[11].sModel[8] = LODWORD(v12) + 64;
  *(_DWORD *)&this->m_RoleXor[11].sModel[12] = (__int64)m_fSpringPosY + 64;
  (((UIWnd *)&this->m_SlotUIWnd))->UIWnd::sub_445FA0(this->m_RoleXor[11].sModel);
  result = LODWORD(this->m_fSpringPrevX);
  if ( LODWORD(this->m_fSpringTargX) == result )
  {
    result = LODWORD(this->m_fSpringPrevY);
    if ( LODWORD(this->m_fSpringTargY) == result )
      this->m_bSpringDoneY = 1;
  }
  return result;
}

// 0x0044A2E0
void CCBRoleState::UpdateFadeAlpha()
{
  int m_nFadeTimer; // eax
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // edi
  NPC *v7; // ebp
  int *v8; // eax
  gbColorQuad v9; // [esp+0x10] [ebp-0x4] BYREF

  if ( LOBYTE(this->m_nFadeFlags) )
  {
    m_nFadeTimer = this->m_nFadeTimer;
    if ( m_nFadeTimer > 0 )
    {
      if ( BYTE1(this->m_nFadeFlags) )
      {
        v3 = this->m_nFadeAlpha + 10;
        this->m_nFadeAlpha = v3;
        if ( v3 >= 255 )
        {
          v4 = m_nFadeTimer - 1;
          BYTE1(this->m_nFadeFlags) = 0;
          this->m_nFadeAlpha = 255;
          this->m_nFadeTimer = v4;
          if ( v4 <= 0 )
            this->m_nFadeAlpha = 255;
        }
      }
      else
      {
        v5 = this->m_nFadeAlpha - 10;
        this->m_nFadeAlpha = v5;
        if ( v5 <= 0 )
        {
          BYTE1(this->m_nFadeFlags) = 1;
          this->m_nFadeAlpha = 0;
        }
      }
      v6 = 0;
      v7 = (NPC *)&this->m_pObjMsgBuffer[184];
      do
      {
        if ( *((_BYTE *)&g_pSceneTransitionEnd + v6) )
        {
          if ( this->m_nFadeTimer <= 0 )
            *((_BYTE *)&g_pSceneTransitionEnd + v6) = 0;
          (((NPC *)v7))->NPC::UpdateAnim(*v8);
        }
        ++v6;
        v7 = (NPC *)((char *)v7 + 476);
      }
      while ( v6 < 38 );
    }
  }
}

// 0x0044A3D0
int CCBRoleState::InitFadeAndSpring()
{
  char *v2; // ebp
  char *v3; // esi
  int i; // ebx
  int v5; // ecx
  float v6; // st7
  int v7; // ecx
  int v8; // edx
  float v9; // st7
  int v11; // [esp+0x0] [ebp-0x10]

  *(_DWORD *)&this->m_pObjMsgBuffer[52] = 1077936128;
  (((CCBFiveNimbusWindow *)&this->mOBBox.trans.xw))->CCBFiveNimbusWindow::UpdateDisplay();
  LOBYTE(this->m_nFadeFlags) = 0;
  this->m_nFadeAlpha = 255;
  BYTE1(this->m_nFadeFlags) = 1;
  this->m_nFadeTimer = 2;
  v2 = 0;
  v3 = (char *)&this->m_pObjMsgBuffer[96];
  for ( i = 68; i < 220; i += 4 )
  {
    *((_DWORD *)v3 - 1) = *((_DWORD *)v3 + 3);
    *(_DWORD *)v3 = *((_DWORD *)v3 + 4);
    *((_DWORD *)v3 + 1) = *((_DWORD *)v3 + 5);
    v5 = *((_DWORD *)v3 + 6);
    *((_DWORD *)v3 + 9) = *((_DWORD *)v3 + 13);
    *((_DWORD *)v3 + 2) = v5;
    v6 = (float)*(int *)v3;
    v7 = *((_DWORD *)v3 + 15);
    v8 = *((_DWORD *)v3 + 16);
    *((_DWORD *)v3 + 10) = *((_DWORD *)v3 + 14);
    *((_DWORD *)v3 + 11) = v7;
    *((float *)v3 + 8) = v6;
    v9 = (float)*((int *)v3 - 1);
    *((_DWORD *)v3 + 12) = v8;
    *((float *)v3 + 7) = v9;
    this->CCBRoleState::sub_4499A0(v2, *(int *)((char *)&g_gamefrm + i), v11);
    if ( *((_BYTE *)&g_pSceneTransitionEnd + (_DWORD)v2) )
      LOBYTE(this->m_nFadeFlags) = 1;
    ++v2;
    v3 += 476;
  }
  if ( LOBYTE(this->m_nFadeFlags) )
    this->m_nFadeAlpha = 0;
  this->m_nSpringDir = 1;
  this->m_fSpringAccelY = 3.0f;
  this->m_fSpringAccelX = 3.0f;
  this->m_bSpringDoneX = 0;
  this->m_bSpringDoneY = 1;
  (((CCBUIPanel *)this))->CCBUIPanel::FocusCurrentRole() /* [ROWTABLE] */;
  CCBUIPanel_UpdateSlotPositions(0);
  this->m_pObjMsgBuffer[84] = 0;
  return CCBUIPanel_SetAllSlotsVisible(1);
}

// 0x00456AB0
void CCBRoleState::_todo_456AB0()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  (((UIFrameContainer *)&this->mOBBox.trans.xw))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->m_Static_20408))->UIFrameContainer::ResetContainerState();
  this->m_nVideoState = 0;
  this->_SaveTaskInfo.mTouchCounter = 0;
  *(&this->m_fTimerLimit + 1) = 0;
  this->_SaveTaskInfo.m_iState = 800;
  *(_DWORD *)&this->_SaveTaskInfo.m_bCVDOver = 600;
}

// 0x00456C20
CCBRoleState::~CCBRoleState()
{
  int *v2; // ebx
  float xw; // edx
  int v4; // eax
  int v5; // ebp
  char *v6; // edi
  int i; // ebx
  int v8; // eax
  int *v9; // eax
  int v10; // edx
  int v11; // eax
  UIScene *m_pScene; // edx
  gbColorQuad v13; // [esp+0x38] [ebp-0x24] BYREF
  int v14; // [esp+0x3C] [ebp-0x20] BYREF
  int v15; // [esp+0x40] [ebp-0x1C]
  int v16; // [esp+0x44] [ebp-0x18]
  int v17; // [esp+0x48] [ebp-0x14]
  _DWORD v18[4]; // [esp+0x4C] [ebp-0x10] BYREF
  int v19; // [esp+0x60] [ebp+0x4]
  int v20; // [esp+0x60] [ebp+0x4]

  v2 = (int *)(&this->m_fTimerLimit + 1);
  (((UIListBox *)this))->UIListBox::SetSelTexture(0, *(&this->m_fTimerLimit + 1), this->_SaveTaskInfo.SceneObj::mTouchCounter, this->_SaveTaskInfo.m_iState, *(_DWORD *)&this->_SaveTaskInfo.m_bCVDOver) /* [ROWTABLE] */;
  xw = this->mOBBox.trans.xw;
  this->m_nVideoState = v19;
  v4 = (*(int (**)(float *, _DWORD, int *, CCBRoleState *))(LODWORD(xw) + 16))(
         &this->mOBBox.trans.xw,
         0,
         v2,
         this);
  LOBYTE(v4) = (unsigned long)byte_5B1A26;
  (((UIPushButton *)&this->mOBBox.trans.xw))->UIPushButton::CreateFromTemplate((void *)off_5B0E28, v4);
  v5 = 0;
  v15 = 60;
  v14 = 44;
  v16 = 130;
  v17 = 123;
  v20 = 1;
  v6 = (char *)&this->m_pObjMsgBuffer[88];
  for ( i = 0; i < 52; ++i )
  {
    v8 = sprintf((char *const)&this->m_bLockPropUI, "%s", (&off_5B0E2C)[i]);
    LOBYTE(v8) = (unsigned long)byte_5B1A26;
    (*(void (**)(char *, _DWORD, int *, CCBRoleState *, int *, int))(*(_DWORD *)v6 + 32))(
      v6,
      *(int *)((char *)&dword_56B294 + i * 4),
      &v14,
      this,
      &this->m_bLockPropUI,
      v8);
    CCBUIPanel_SetUserData(*v9);
    if ( ++v5 / 8 < v20 )
    {
      v14 = v16 + 3;
      v16 += 89;
    }
    else
    {
      v14 = 44;
      v16 = 130;
      v15 += 68;
      v17 = v15 + 63;
      ++v20;
    }
    v6 += 376;
  }
  v10 = (int)((UIWnd *)&this->m_Static_20408);
  v18[1] = 476;
  v18[0] = 408;
  v18[2] = 744;
  v18[3] = 526;
  (*(void (**)(UIStatic *, _DWORD, _DWORD *, CCBRoleState *))(v10 + 16))(&this->m_Static_20408, 0, (_DWORD *)(v18), this);
  (((UIScene *)&this->m_Static_20408))->UIScene::SetShow(0);
  SetEnable((UICaption *)&this->m_Static_20408);
  LOBYTE(v11) = (unsigned long)byte_5B1A26;
  m_pScene = (UIScene *)this->m_pScene;
  v15 = 537;
  v14 = 745;
  v16 = 801;
  v17 = 599;
  ((void (*)(UIScene **, int, int *, CCBRoleState *, int, _DWORD, int))m_pScene->m_rect.bottom)(
    &this->m_pScene,
    177,
    &v14,
    this,
    off_5B1604,
    0,
    v11);
}

// 0x00457020
BOOL CCBRoleState::PlayVideoIfReady(int nVal, int nVal2)
{
  unsigned __int8 v5; // [esp+0x0] [ebp-0x4]

  if ( this->m_bVideoPlayed && (((CScreenMode *)&g_ScreenMode))->CScreenMode::PlayVideo(1) )
  {
    (((CScreenMode *)this))->CScreenMode::PauseAllStreams((void *)1, v5) /* [ROWTABLE] */;
    this->m_bVideoPlayed = 0;
  }
  return this->SceneObj::Update(nVal, nVal2);
}

// 0x00457070
int CCBRoleState::ctor(int nVal, int nVal2, int nVal3)
{
  int result; // eax
  int v6; // eax
  int *v7; // ecx
  CScreenMode *Instance; // eax
  int Width; // eax
  int v10; // ecx
  int *v11; // eax
  int *v12; // eax
  const void *v13; // [esp-0x8] [ebp-0x10]
  int v14; // [esp-0x4] [ebp-0xC]
  unsigned __int8 v15; // [esp+0x0] [ebp-0x8]

  switch ( nVal )
  {
    case 1000:
      if ( !nVal2 )
        goto LABEL_20;
      (((Actor *)this))->Actor::ApplyStateArray();
      this->m_bVideoPlayed = 0;
      result = 1;
      break;
    case 1001:
      v6 = 0;
      v7 = (int *)&dword_56B294;
      do
      {
        if ( nVal2 == *v7 )
        {
          sprintf((char *const)&this->m_bLockPropUI, "Movie\\%s.bik", (const char *)(30 * v6 + 5967612));
          (((CScreenMode *)&g_ScreenMode))->CScreenMode::CreateDevice((int)&this->m_bLockPropUI, g_todo_BFDA4C, 0, 0);
          v14 = (600 - (((CScreenMode *)&g_ScreenMode))->CScreenMode::GetHeight()) / 2;
          Width = (((CScreenMode *)&g_ScreenMode))->CScreenMode::GetWidth();
          (((CScreenMode *)&g_ScreenMode))->CScreenMode::SetViewport((800 - Width) / 2, v14);
          (((CScreenMode *)this))->CScreenMode::PauseAllStreams(0, v15) /* [ROWTABLE] */;
          this->m_bVideoPlayed = 1;
          return 1;
        }
        ++v7;
        ++v6;
      }
      while ( (int)v7 < (int)0x56B364 );
      if ( nVal2 != 177 )
        goto LABEL_20;
      v13 = (const void *)off_5B0DA4;
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v13, 1);
      (((ChoseCompose *)this->m_nVideoState))->ChoseCompose::Init(0);
      result = 1;
      break;
    case 1002:
      v10 = 0;
      v11 = (int *)&dword_56B294;
      do
      {
        if ( nVal2 == *v11 )
          goto LABEL_19;
        ++v11;
        ++v10;
      }
      while ( (int)v11 < (int)0x56B364 );
      result = 1;
      break;
    case 1003:
      v12 = (int *)&dword_56B294;
      while ( nVal2 != *v12 )
      {
        if ( (int)++v12 >= (int)0x56B364 )
          return 1;
      }
LABEL_19:
      SetEnable((UICaption *)&this->m_Static_20408);
LABEL_20:
      result = 1;
      break;
    default:
      result = this->UIWnd::OnMessage(nVal, nVal2, nVal3);
      break;
  }
  return result;
}

// 0x0046D770
int CCBRoleState::LayoutSlotPanelA(unsigned __int8 pData)
{
  void ( **m_SlotWidgets)(UIWnd *, _DWORD); // edx
  float fMoneyIncPerCombat; // edi
  int result; // eax

  m_SlotWidgets = (void ( **)(UIWnd *, _DWORD))this->m_SlotWidgets;
  this->m_bySlotVisible = (unsigned char)pData;
  (*m_SlotWidgets)(&this->m_SlotWidgets, pData);
  this->m_RoleXor[10].fRecoverItemPowerInc = 0.0f;
  this->m_RoleXor[10].fMoneyIncPerCombat = 0.0f;
  do
  {
    fMoneyIncPerCombat = this->m_RoleXor[10].fMoneyIncPerCombat;
    if ( *(&this->m_bySlotVisible + LODWORD(fMoneyIncPerCombat)) )
    {
      *(&this->m_SlotRects + 4 * LODWORD(fMoneyIncPerCombat) + 39) = LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc)
                                                                   * this->m_nSlotSpacing
                                                                   + (this->m_nSlotSpacing - this->m_nSlotWidth) / 2;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38) = this->m_nSlotStartY;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 40) = this->m_nSlotHeight
                                                                                       + *(&this->m_SlotRects
                                                                                         + 4
                                                                                         * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                         + 38);
      *(&this->m_SlotRightEdge + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)) = this->m_nSlotWidth
                                                                                      + *(&this->m_SlotRects
                                                                                        + 4
                                                                                        * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                        + 39);
      (((UIWnd *)((char *)&this->m_SlotWidgets + 152 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat))))->UIWnd::sub_445FA0(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38);
      ++LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc);
    }
    result = LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 1;
    LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046D890
int CCBRoleState::LayoutSlotPanelB(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  float fMoneyIncPerCombat; // edi
  int result; // eax

  v3 = (void ( **)(char *, _DWORD))*((_DWORD *)&this->m_SlotWidgets + 38);
  *(&this->m_bySlotVisible + 1) = (unsigned char)pData;
  (*v3)((char *)&this->m_SlotWidgets + 152, pData);
  this->m_RoleXor[10].fRecoverItemPowerInc = 0.0f;
  this->m_RoleXor[10].fMoneyIncPerCombat = 0.0f;
  do
  {
    fMoneyIncPerCombat = this->m_RoleXor[10].fMoneyIncPerCombat;
    if ( *(&this->m_bySlotVisible + LODWORD(fMoneyIncPerCombat)) )
    {
      *(&this->m_SlotRects + 4 * LODWORD(fMoneyIncPerCombat) + 39) = LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc)
                                                                   * this->m_nSlotSpacing
                                                                   + (this->m_nSlotSpacing - this->m_nSlotWidth) / 2;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38) = this->m_nSlotStartY;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 40) = this->m_nSlotHeight
                                                                                       + *(&this->m_SlotRects
                                                                                         + 4
                                                                                         * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                         + 38);
      *(&this->m_SlotRightEdge + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)) = this->m_nSlotWidth
                                                                                      + *(&this->m_SlotRects
                                                                                        + 4
                                                                                        * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                        + 39);
      (((UIWnd *)((char *)&this->m_SlotWidgets + 152 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat))))->UIWnd::sub_445FA0(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38);
      ++LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc);
    }
    result = LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 1;
    LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046D9B0
int CCBRoleState::LayoutSlotPanelC(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  float fMoneyIncPerCombat; // edi
  int result; // eax

  v3 = (void ( **)(char *, _DWORD))*((_DWORD *)&this->m_SlotWidgets + 76);
  *(&this->m_bySlotVisible + 2) = (unsigned char)pData;
  (*v3)((char *)&this->m_SlotWidgets + 304, pData);
  this->m_RoleXor[10].fRecoverItemPowerInc = 0.0f;
  this->m_RoleXor[10].fMoneyIncPerCombat = 0.0f;
  do
  {
    fMoneyIncPerCombat = this->m_RoleXor[10].fMoneyIncPerCombat;
    if ( *(&this->m_bySlotVisible + LODWORD(fMoneyIncPerCombat)) )
    {
      *(&this->m_SlotRects + 4 * LODWORD(fMoneyIncPerCombat) + 39) = LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc)
                                                                   * this->m_nSlotSpacing
                                                                   + (this->m_nSlotSpacing - this->m_nSlotWidth) / 2;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38) = this->m_nSlotStartY;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 40) = this->m_nSlotHeight
                                                                                       + *(&this->m_SlotRects
                                                                                         + 4
                                                                                         * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                         + 38);
      *(&this->m_SlotRightEdge + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)) = this->m_nSlotWidth
                                                                                      + *(&this->m_SlotRects
                                                                                        + 4
                                                                                        * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                        + 39);
      (((UIWnd *)((char *)&this->m_SlotWidgets + 152 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat))))->UIWnd::sub_445FA0(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38);
      ++LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc);
    }
    result = LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 1;
    LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046DAD0
int CCBRoleState::LayoutSlotPanelD(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  float fMoneyIncPerCombat; // edi
  int result; // eax

  v3 = (void ( **)(char *, _DWORD))*((_DWORD *)&this->m_SlotWidgets + 114);
  *(&this->m_bySlotVisible + 3) = (unsigned char)pData;
  (*v3)((char *)&this->m_SlotWidgets + 456, pData);
  this->m_RoleXor[10].fRecoverItemPowerInc = 0.0f;
  this->m_RoleXor[10].fMoneyIncPerCombat = 0.0f;
  do
  {
    fMoneyIncPerCombat = this->m_RoleXor[10].fMoneyIncPerCombat;
    if ( *(&this->m_bySlotVisible + LODWORD(fMoneyIncPerCombat)) )
    {
      *(&this->m_SlotRects + 4 * LODWORD(fMoneyIncPerCombat) + 39) = LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc)
                                                                   * this->m_nSlotSpacing
                                                                   + (this->m_nSlotSpacing - this->m_nSlotWidth) / 2;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38) = this->m_nSlotStartY;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 40) = this->m_nSlotHeight
                                                                                       + *(&this->m_SlotRects
                                                                                         + 4
                                                                                         * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                         + 38);
      *(&this->m_SlotRightEdge + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)) = this->m_nSlotWidth
                                                                                      + *(&this->m_SlotRects
                                                                                        + 4
                                                                                        * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                        + 39);
      (((UIWnd *)((char *)&this->m_SlotWidgets + 152 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat))))->UIWnd::sub_445FA0(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38);
      ++LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc);
    }
    result = LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 1;
    LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046DBF0
int CCBRoleState::LayoutSlotPanelE(unsigned __int8 pData)
{
  void ( **m_SlotRects)(int *, _DWORD); // edx
  float fMoneyIncPerCombat; // edi
  int result; // eax

  m_SlotRects = (void ( **)(int *, _DWORD))this->m_SlotRects;
  *(&this->m_bySlotVisible + 4) = (unsigned char)pData;
  (*m_SlotRects)(&this->m_SlotRects, pData);
  this->m_RoleXor[10].fRecoverItemPowerInc = 0.0f;
  this->m_RoleXor[10].fMoneyIncPerCombat = 0.0f;
  do
  {
    fMoneyIncPerCombat = this->m_RoleXor[10].fMoneyIncPerCombat;
    if ( *(&this->m_bySlotVisible + LODWORD(fMoneyIncPerCombat)) )
    {
      *(&this->m_SlotRects + 4 * LODWORD(fMoneyIncPerCombat) + 39) = LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc)
                                                                   * this->m_nSlotSpacing
                                                                   + (this->m_nSlotSpacing - this->m_nSlotWidth) / 2;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38) = this->m_nSlotStartY;
      *(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 40) = this->m_nSlotHeight
                                                                                       + *(&this->m_SlotRects
                                                                                         + 4
                                                                                         * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                         + 38);
      *(&this->m_SlotRightEdge + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)) = this->m_nSlotWidth
                                                                                      + *(&this->m_SlotRects
                                                                                        + 4
                                                                                        * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat)
                                                                                        + 39);
      (((UIWnd *)((char *)&this->m_SlotWidgets + 152 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat))))->UIWnd::sub_445FA0(&this->m_SlotRects + 4 * LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 38);
      ++LODWORD(this->m_RoleXor[10].fRecoverItemPowerInc);
    }
    result = LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) + 1;
    LODWORD(this->m_RoleXor[10].fMoneyIncPerCombat) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046F390
int CCBRoleState::NotifyStateChange(unsigned __int8 nState)
{
  (*(void ( **)(int *, _DWORD))this->m_BattleFlags)(&this->m_BattleFlags, nState);
  return (**((int ( ***)(float *, _DWORD))&this->m_fSpringSpeed + 16))((float *)(&this->m_fSpringSpeed + 16), (_DWORD)(nState));
}

// 0x004A3360
int CCBRoleState::sub_4A3360(CHAR *thisa, int a2, int *a3)
{
  char *v4; // edi
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int *p_m_bLockPropUI; // ebx
  int v12; // ecx
  int v13; // edx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // esi
  int v23; // [esp+0x14] [ebp-0x40] BYREF
  int v24; // [esp+0x18] [ebp-0x3C]
  int v25; // [esp+0x1C] [ebp-0x38]
  int v26; // [esp+0x20] [ebp-0x34]
  int v27; // [esp+0x24] [ebp-0x30] BYREF
  int v28; // [esp+0x28] [ebp-0x2C]
  int v29; // [esp+0x2C] [ebp-0x28]
  int v30; // [esp+0x30] [ebp-0x24]
  int v31; // [esp+0x34] [ebp-0x20] BYREF
  int v32; // [esp+0x38] [ebp-0x1C]
  int v33; // [esp+0x3C] [ebp-0x18]
  int v34; // [esp+0x40] [ebp-0x14]
  _DWORD v35[4]; // [esp+0x44] [ebp-0x10] BYREF

  v4 = (char *)this + 3788 * (_DWORD)thisa;
  (((UIWnd *)(v4 + 157240)))->UIWnd::sub_445FA0((void *)a2);
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)(v4 + 157240)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\State\\Shade.tga", v5);
  if ( thisa == (CHAR *)2 )
  {
    v6 = *(_DWORD *)(a2 + 4) + 32;
    v27 = *(_DWORD *)a2 + 10;
    v28 = v6;
    v29 = v27 + 128;
    v7 = v6 + 283;
  }
  else
  {
    v8 = *(_DWORD *)(a2 + 4);
    v9 = *(_DWORD *)a2 + 10;
    if ( thisa == (CHAR *)4 )
    {
      v28 = v8 + 16;
      v27 = v9;
      v29 = v9 + 128;
      v7 = v8 + 317;
    }
    else
    {
      v28 = v8 + 30;
      v27 = v9;
      v29 = v9 + 128;
      v7 = v8 + 318;
    }
  }
  v30 = v7;
  (((UIWnd *)(v4 + 157392)))->UIWnd::sub_445FA0(&v27);
  v10 = *(_DWORD *)(a2 + 4) + 3;
  v35[0] = *(_DWORD *)(a2 + 8) - 42;
  v35[1] = v10;
  v35[2] = v35[0] + 32;
  v35[3] = v10 + 138;
  (((UIWnd *)(v4 + 157544)))->UIWnd::sub_445FA0(v35);
  if ( *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * (_DWORD)thisa) >= 99 )
    *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * (_DWORD)thisa) = 99;
  p_m_bLockPropUI = (int *)&this->m_bLockPropUI;
  FormatChineseNumber(*(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * (_DWORD)thisa), (LPSTR)&this->m_bLockPropUI);
  lstrcatA((LPSTR)&this->m_bLockPropUI, byte_DC6A3C);
  SetEnable((UICaption *)(v4 + 157544));
  v12 = *(_DWORD *)a2;
  v13 = *(_DWORD *)(a2 + 8);
  v32 = *(_DWORD *)(a2 + 12) - 86;
  v34 = v32 + 64;
  v31 = v12 + 10;
  v33 = v13;
  (((UIWnd *)(v4 + 157696)))->UIWnd::sub_445FA0(&v31);
  sprintf(
    (char *const)&this->m_bLockPropUI,
    "%s\\n  %d",
    (const char *)dword_DCA13C,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + 352 * (_DWORD)thisa));
  SetEnable((UICaption *)(v4 + 157696));
  v32 = v34 - 28;
  v34 = v34 - 28 + 64;
  (((UIWnd *)(v4 + 157848)))->UIWnd::sub_445FA0(&v31);
  v14 = (((CCBRoleState *)g_pCBSystem->m_pRoleState))->CCBRoleState::GetRoleCount(*(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * (_DWORD)thisa) + 1)
      - *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + 352 * (_DWORD)thisa);
  if ( v14 < 0 )
    v14 = 0;
  if ( *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * (_DWORD)thisa) >= 99 )
    sprintf((char *const)p_m_bLockPropUI, "%s\\n  %s", dword_DCA23C, dword_DDB93C);
  else
    sprintf((char *const)p_m_bLockPropUI, "%s\\n  %d", dword_DCA23C, v14);
  SetEnable((UICaption *)(v4 + 157848));
  v15 = *(_DWORD *)a2 + 63;
  v24 = *(_DWORD *)(a2 + 4) + 335;
  v23 = v15;
  v26 = v24 + 32;
  v25 = v15 + 150;
  (((UIWnd *)(v4 + 158000)))->UIWnd::sub_445FA0(&v23);
  v16 = *(_DWORD *)(a2 + 4) + 370;
  v23 = *(_DWORD *)a2 + 113;
  v25 = v23 + 150;
  v24 = v16;
  v26 = v16 + 32;
  (((UIWnd *)(v4 + 158152)))->UIWnd::sub_445FA0(&v23);
  v17 = *(_DWORD *)(a2 + 4) + 420;
  v23 = *(_DWORD *)a2 + 95;
  v24 = v17;
  v25 = v23 + 150;
  v26 = v17 + 32;
  (((UIWnd *)(v4 + 158456)))->UIWnd::sub_445FA0(&v23);
  v18 = *(_DWORD *)a2 + 36;
  v24 = *(_DWORD *)(a2 + 4) + 420;
  v23 = v18;
  v26 = v24 + 32;
  v25 = v18 + 150;
  ((UIWnd *)((UIWnd *)v4 + 2328))->UIWnd::sub_445FA0(&v23);
  v19 = *(_DWORD *)(a2 + 4);
  v20 = *(_DWORD *)a2 + 17;
  v24 = v19 + 370;
  v23 = v20;
  v25 = v20 + 150;
  v26 = v19 + 402;
  return (((UIWnd *)(v4 + 158608)))->UIWnd::sub_445FA0(&v23);
}

// 0x004DC250
int CCBRoleState::UpdatePanel(BOOL bRefresh)
{
  int result; // eax

  if ( bRefresh )
  {
    if ( this->m_pfather
      || !*(_DWORD *)&(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->byMagicUseTime[3][5]
      || *(float *)&(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->byMagicUseTime[4][3] <= 199.89999f )
    {
      (***(void ( ****)(_DWORD))(*(_DWORD *)(this->m_rect.left + 1116) + 112))((_DWORD)(0));
    }
    else
    {
      (***(void ( ****)(int))(*(_DWORD *)(this->m_rect.left + 1116) + 112))((int)(1));
    }
    (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 15);
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 84));
    (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 16);
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 88));
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 104));
    this->CCBRoleState::CheckSelfMP();
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 96));
    if ( !this->m_pfather )
      (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0);
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 108));
    LOBYTE(result) = ((*((CCBUI **)this + 4)))->CCBUI::CreateSkillWindow(1);
  }
  else
  {
    LOBYTE(result) = ((*((CCBUI **)this + 4)))->CCBUI::CreateSkillWindow(0);
  }
  return result;
}

// 0x004DC720
BOOL CCBRoleState::IsRoleShelved(int nVal1)
{
  BOOL result; // eax

  result = nVal1 << 6;
  if ( this->sCGSHELF[64 * nVal1 + 43] )
  {
    memset(&this->m_bProcessLinkObj + 16 * nVal1, 0, 0x40u);
    result = *(_DWORD *)&this->m_bLockCamera - 1;
    *(_DWORD *)&this->m_bLockCamera = result;
    LOBYTE(result) = 1;
  }
  else
  {
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004DC760
char CCBRoleState::GetCombatDialogPos(int *p_DWORD, int *p_DWORD2, int *p_DWORD3)
{
  if ( !LOBYTE(this->m_bcreateok) )
    return 0;
  *p_DWORD = this->m_childs.capacity;
  *p_DWORD2 = this->m_childs.m_nSize;
  *p_DWORD3 = this->m_childs.m_needscriptdel;
  LOBYTE(this->m_bcreateok) = 0;
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_needscriptdel = 0;
  return 1;
}

// 0x004DC7A0
void CCBRoleState::InitCombatDialog()
{
  int m_bLockPropUI; // eax
  CScreenMode *Instance; // eax
  int v4; // ecx
  UIWnd *m_pfather; // eax
  int v6; // edx
  int p_DWORD; // [esp+0x10] [ebp-0xC] BYREF
  int p_DWORD3; // [esp+0x14] [ebp-0x8] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x4] BYREF

  m_bLockPropUI = this->m_bLockPropUI;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !this->sCGSHELF[64 * m_bLockPropUI + 44] )
  {
    this->CCBRoleState::UpdatePanel(1);
    *(_BYTE *)(*(_DWORD *)(this->m_wndcolor.Color + 4 * (int)this->m_pfather + 24) + 280) = 1;
    this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa003", 1);
  }
  (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 15);
  sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 84));
  (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 16);
  sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 88));
  sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 104));
  this->CCBRoleState::CheckSelfMP();
  sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 96));
  if ( !this->m_pfather
    && *(_DWORD *)&(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->byMagicUseTime[8][3] == 6
    && ((((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(1)->bValid
     || (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(2)->bValid
     || (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(3)->bValid) )
  {
    v4 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 108);
  }
  else
  {
    v4 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 108);
  }
  sub_445E50(v4);
  if ( this->CCBRoleState::GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3) )
  {
    switch ( p_DWORD )
    {
      case 259:
        this->CCBRoleState::UpdatePanel(0);
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::DispatchCombatAction) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
          0,
          0,
          0,
          259);
        goto LABEL_36;
      case 260:
        this->CCBRoleState::UpdatePanel(0);
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleItemMenu) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
          0,
          0,
          0,
          260);
        goto LABEL_36;
      case 261:
        if ( (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 15) )
          goto LABEL_34;
        this->CCBRoleState::UpdatePanel(0);
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleMagicMenu) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
          0,
          0,
          0,
          261);
        goto LABEL_36;
      case 262:
        if ( (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 16) )
          goto LABEL_34;
        this->CCBRoleState::UpdatePanel(0);
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleTargetMenu) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
          0,
          0,
          0,
          262);
        goto LABEL_36;
      case 264:
        if ( !this->CCBRoleState::CheckSelfMP() )
          goto LABEL_34;
        this->CCBRoleState::UpdatePanel(0);
        this->m_bvisible = 264;
        this->m_benable = 0;
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::EndRoundTasks) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
          0,
          0,
          0,
          264);
        goto LABEL_36;
      case 265:
        this->CCBRoleState::UpdatePanel(0);
        LOBYTE(this->m_fTimeScale) = 1;
        this->m_bvisible = 265;
        goto LABEL_21;
      case 266:
        this->CCBRoleState::UpdatePanel(0);
        this->m_bvisible = 266;
        this->m_benable = 0;
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::StartLineupPhase) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
          0,
          0,
          0,
          266);
        goto LABEL_36;
      case 267:
        if ( (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 16) )
          goto LABEL_34;
        this->CCBRoleState::UpdatePanel(0);
        LOBYTE(this->m_fTimeScale) = 1;
        this->m_bvisible = 267;
LABEL_21:
        v6 = this->m_bLockPropUI;
        this->m_bfocus = (int)this->m_pfather;
        this->m_benable = 0;
        this->m_fTimerLimit = -1;
        *((_BYTE *)&this->m_fTimerLimit + 5) = 0;
        *((_BYTE *)&this->m_fTimerLimit + 4) = 0;
        this->CCBRoleState::IsRoleShelved(v6);
        break;
      case 268:
        if ( this->m_pfather
          || *(_DWORD *)&(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->byMagicUseTime[8][3] != 6
          || !(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(1)->bValid
          && !(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(2)->bValid
          && !(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(3)->bValid )
        {
          goto LABEL_34;
        }
        this->CCBRoleState::UpdatePanel(0);
        this->m_benable = 0;
        this->m_bvisible = 268;
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::InitSelectionUI) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
          0,
          0,
          0,
          268);
        this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
        break;
      case 269:
        this->CCBRoleState::UpdatePanel(0);
        m_pfather = this->m_pfather;
        LOBYTE(this->m_fTimeScale) = 1;
        this->m_bvisible = 269;
        this->m_benable = 0;
        this->m_bfocus = (int)m_pfather;
        this->m_fTimerLimit = -1;
        *((_BYTE *)&this->m_fTimerLimit + 5) = 0;
        *((_BYTE *)&this->m_fTimerLimit + 4) = 0;
        goto LABEL_36;
      default:
        goto LABEL_34;
    }
  }
  else
  {
LABEL_34:
    if ( BYTE1(this->m_childs.m_pData) )
    {
      (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
      this->CCBRoleState::UpdatePanel(0);
LABEL_36:
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
    }
  }
}

// 0x004DCD00
int CCBRoleState::HandleItemMenu(int nState)
{
  int v3; // eax
  CScreenMode *Instance; // eax
  int *v5; // ecx
  int DialogSlot; // esi
  CCBRoleState *m_id; // ecx
  const char *v8; // esi
  int p_DWORD3; // [esp+0x10] [ebp-0x138] BYREF
  int p_DWORD; // [esp+0x14] [ebp-0x134] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x130] BYREF
  _DWORD pOut[11]; // [esp+0x1C] [ebp-0x12C] BYREF
  char v14[256]; // [esp+0x48] [ebp-0x100] BYREF

  memset(pOut, 0, sizeof(pOut));
  v3 = this->m_bLockPropUI << 6;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !this->sCGSHELF[v3 + 44] )
  {
    (((CCBRoleState *)this->m_id))->CCBRoleState::PopulateItemList((int)this->m_pfather);
    SetEnable(*(UICaption **)(*(_DWORD *)(this->m_rect.left + 1128) + 72));
    (***(void ( ****)(_DWORD, int))(this->m_rect.left + 1128))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1128)), (int)(1));
    this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa003", 1);
  }
  if ( this->CCBRoleState::GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3) && p_DWORD == 160 )
  {
    (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1128))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1128)), (_DWORD)(0));
    if ( p_DWORD2 == -1 )
    {
      v5 = (int *)((char *)((UIWnd *)this) + 64 * this->m_bLockPropUI + 128);
      FindFreeThread((CCBSystem *)this, *v5, v5[1], v5[2], v5[3], 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleItemMenu) */, 0, 0, 0, 0);
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
      return 0;
    }
    DialogSlot = (((CCBRoleState *)this->m_id))->CCBRoleState::GetDialogSlot((int)this->m_pfather, p_DWORD2);
    if ( p_DWORD3 != 1 )
    {
      FindFreeThread(
        (CCBSystem *)this,
        0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::DispatchCombatAction) */,
        0,
        0,
        0,
        0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleItemMenu) */,
        0,
        0,
        0,
        *(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 23]);
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
      return 0;
    }
    memset(pOut, 0, sizeof(pOut));
    pOut[2] = (unsigned long)(this->m_pfather);
    m_id = (CCBRoleState *)this->m_id;
    LOBYTE(pOut[10]) = 1;
    pOut[0] = 260;
    pOut[1] = DialogSlot;
    pOut[3] = -1;
    if ( (((CCBRoleState *)m_id))->CCBRoleState::GetRoleAI(pOut) )
    {
      v8 = (const char *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(DialogSlot) + 60);
      if ( strrchr(v8, 36) )
        strcpy((char *)v14, strrchr(v8, 36) + 1);
      SetEnable(*(UICaption **)(*(_DWORD *)(this->m_rect.left + 1128) + 72));
    }
    (***(void ( ****)(_DWORD, int))(this->m_rect.left + 1128))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1128)), (int)(1));
  }
  if ( BYTE1(this->m_childs.m_pData) )
  {
    (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
    (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1128))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1128)), (_DWORD)(0));
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  return 0;
}

// 0x004DCF80
int CCBRoleState::HandleMagicMenu(int nState)
{
  int v3; // eax
  CScreenMode *Instance; // eax
  int v5; // esi
  int v6; // eax
  int *v7; // ecx
  int v8; // edi
  int MagicSlotData; // esi
  int v10; // eax
  UIWnd *m_pfather; // edx
  CCBRoleState *m_id; // ecx
  const char *v13; // esi
  int p_DWORD; // [esp+0x10] [ebp-0x138] BYREF
  int p_DWORD3; // [esp+0x14] [ebp-0x134] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x130] BYREF
  _DWORD pOut[11]; // [esp+0x1C] [ebp-0x12C] BYREF
  char v19[256]; // [esp+0x48] [ebp-0x100] BYREF

  memset(pOut, 0, sizeof(pOut));
  v3 = this->m_bLockPropUI << 6;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !this->sCGSHELF[v3 + 44] )
  {
    (((CCBRoleState *)this->m_id))->CCBRoleState::PopulateMagicList((int)this->m_pfather);
    (((CCBControlWindow *)*(CCBControlWindow **)(this->m_rect.left + 1124)))->CCBControlWindow::HandleInput(*(UIButton **)(*(_DWORD *)((UIWnd *)this) + 52 * (int)this->m_pfather + 90308));
    SetEnable(*(UICaption **)(*(_DWORD *)(this->m_rect.left + 1124) + 72));
    (***(void ( ****)(_DWORD, int))(this->m_rect.left + 1124))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1124)), (int)(1));
    this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa003", 1);
  }
  v5 = *(_DWORD *)((UIWnd *)this) + 52 * (int)this->m_pfather + 90264;
  (((CCBControlWindow *)*(CCBControlWindow **)(this->m_rect.left + 1124)))->CCBControlWindow::KeyPressed();
  *(_DWORD *)(v5 + 44) = v6;
  if ( this->CCBRoleState::GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (unsigned int)p_DWORD >= 0x90
    && (unsigned int)p_DWORD <= 0x95 )
  {
    (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1124))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1124)), (_DWORD)(0));
    if ( p_DWORD2 == -1 )
    {
      v7 = (int *)((char *)((UIWnd *)this) + 64 * this->m_bLockPropUI + 128);
      FindFreeThread((CCBSystem *)this, *v7, v7[1], v7[2], v7[3], 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleMagicMenu) */, 0, 0, 0, 0);
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
      return 0;
    }
    v8 = p_DWORD - 144;
    MagicSlotData = (((CCBRoleState *)this->m_id))->CCBRoleState::GetMagicSlotData((int)this->m_pfather, p_DWORD - 144, p_DWORD2);
    if ( p_DWORD3 != 1 )
    {
      FindFreeThread(
        (CCBSystem *)this,
        0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::DispatchCombatAction) */,
        0,
        0,
        0,
        0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleMagicMenu) */,
        0,
        0,
        0,
        *(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 23]);
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
      return 0;
    }
    (((CCBControlWindow *)*(CCBControlWindow **)(this->m_rect.left + 1124)))->CCBControlWindow::KeyPressed();
    if ( v10 == v8 )
    {
      m_pfather = this->m_pfather;
      memset(pOut, 0, sizeof(pOut));
      m_id = (CCBRoleState *)this->m_id;
      LOBYTE(pOut[10]) = 1;
      pOut[0] = 261;
      pOut[1] = MagicSlotData;
      pOut[3] = -1;
      pOut[2] = (unsigned long)m_pfather;
      if ( (((CCBRoleState *)m_id))->CCBRoleState::GetRoleAI(pOut) )
      {
        v13 = (const char *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(MagicSlotData) + 60);
        memset(v19, 0, sizeof(v19));
        if ( strrchr(v13, 36) )
          strcpy((char *)v19, strrchr(v13, 36) + 1);
        SetEnable(*(UICaption **)(*(_DWORD *)(this->m_rect.left + 1124) + 72));
      }
    }
    (***(void ( ****)(_DWORD, int))(this->m_rect.left + 1124))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1124)), (int)(1));
  }
  if ( (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 15) )
  {
    (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1124))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1124)), (_DWORD)(0));
    FindFreeThread(
      (CCBSystem *)this,
      *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 32),
      *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 33),
      *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 34),
      *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 35),
      0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleMagicMenu) */,
      0,
      0,
      0,
      0);
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  else if ( BYTE1(this->m_childs.m_pData) )
  {
    (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
    (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1124))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1124)), (_DWORD)(0));
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  return 0;
}

// 0x004DD300
int CCBRoleState::HandleTargetMenu(int nState)
{
  int v3; // eax
  CScreenMode *Instance; // eax
  unsigned int v5; // eax
  int *v6; // ecx
  int v7; // esi
  CCBRoleState *m_id; // ecx
  const char *v9; // esi
  int *v10; // ecx
  int p_DWORD; // [esp+0x10] [ebp-0x144] BYREF
  int p_DWORD3; // [esp+0x14] [ebp-0x140] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x13C] BYREF
  _DWORD v15[11]; // [esp+0x1C] [ebp-0x138] BYREF
  char pOut[12]; // [esp+0x48] [ebp-0x10C] BYREF
  char v17[256]; // [esp+0x54] [ebp-0x100] BYREF

  memset(v15, 0, sizeof(v15));
  v3 = this->m_bLockPropUI << 6;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !this->sCGSHELF[v3 + 44] )
  {
    SetEnable(*(UICaption **)(*(_DWORD *)(this->m_rect.left + 1120) + 76));
    (***(void ( ****)(_DWORD, int))(this->m_rect.left + 1120))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1120)), (int)(1));
    (((CCBRoleState *)this->m_id))->CCBRoleState::PopulateTargetList((int)this->m_pfather, *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1120) + 104));
    this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa003", 1);
  }
  if ( this->CCBRoleState::GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3) )
  {
    v5 = p_DWORD;
    if ( (unsigned int)p_DWORD >= 0x80 && (unsigned int)p_DWORD <= 0x90 )
    {
      (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1120))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1120)), (_DWORD)(0));
      if ( p_DWORD2 == -1 )
      {
        v6 = (int *)((char *)((UIWnd *)this) + 64 * this->m_bLockPropUI + 128);
        FindFreeThread((CCBSystem *)this, *v6, v6[1], v6[2], v6[3], 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleTargetMenu) */, 0, 0, 0, 0);
        this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
        return 0;
      }
      if ( p_DWORD3 != 1 )
      {
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, p_DWORD2);
        FindFreeThread(
          (CCBSystem *)this,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::DispatchCombatAction) */,
          0,
          0,
          0,
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleTargetMenu) */,
          0,
          0,
          0,
          *(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 23]);
        this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
        return 0;
      }
      v7 = *(_DWORD *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, p_DWORD2);
      memset(v15, 0, sizeof(v15));
      v15[2] = (unsigned long)(this->m_pfather);
      m_id = (CCBRoleState *)this->m_id;
      LOBYTE(v15[10]) = 1;
      v15[0] = 262;
      v15[1] = v7;
      v15[3] = -1;
      if ( (((CCBRoleState *)m_id))->CCBRoleState::GetRoleAI(v15) )
      {
        v9 = (const char *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v7) + 96);
        if ( strrchr(v9, 36) )
          strcpy((char *)v17, strrchr(v9, 36) + 1);
        SetEnable(*(UICaption **)(*(_DWORD *)(this->m_rect.left + 1120) + 76));
      }
      (***(void ( ****)(_DWORD, int))(this->m_rect.left + 1120))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1120)), (int)(1));
      v5 = p_DWORD;
    }
    if ( v5 >= 0xB5 && v5 <= 0xB7 )
      (((CCBRoleState *)this->m_id))->CCBRoleState::PopulateTargetList((int)this->m_pfather, *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1120) + 104));
  }
  if ( (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleField((int)this->m_pfather, 16) )
  {
    (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1120))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1120)), (_DWORD)(0));
    v10 = (int *)((char *)((UIWnd *)this) + 64 * this->m_bLockPropUI + 128);
    FindFreeThread((CCBSystem *)this, *v10, v10[1], v10[2], v10[3], 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::HandleTargetMenu) */, 0, 0, 0, 0);
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  else if ( BYTE1(this->m_childs.m_pData) )
  {
    (***(void ( ****)(_DWORD, _DWORD))(this->m_rect.left + 1120))((_DWORD)(*(_DWORD *)(this->m_rect.left + 1120)), (_DWORD)(0));
    (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  return 0;
}

// 0x004DD650
int CCBRoleState::StartLineupPhase(int nVal)
{
  int m_bLockPropUI; // eax
  CScreenMode *Instance; // eax
  int *v5; // ecx
  CScreenMode *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  CScreenMode *v13; // eax
  int v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  CScreenMode *v21; // eax
  int v22; // eax
  CScreenMode *v23; // eax
  int v24; // eax
  CScreenMode *v25; // eax
  int v26; // eax
  CScreenMode *v27; // eax
  int v28; // eax
  CScreenMode *v29; // eax
  CScreenMode *v30; // eax
  bool v31; // bl
  char v32; // bl
  _DWORD *v33; // eax
  char v34; // cl
  int *v35; // edx
  int v36; // ecx
  int v37; // eax
  UIWnd *m_pfather; // eax
  char v39; // [esp+0xF] [ebp-0xD]
  char v40; // [esp+0xF] [ebp-0xD]
  char v41; // [esp+0xF] [ebp-0xD]
  char v42; // [esp+0xF] [ebp-0xD]
  int p_DWORD2; // [esp+0x10] [ebp-0xC] BYREF
  int p_DWORD; // [esp+0x14] [ebp-0x8] BYREF
  int p_DWORD3; // [esp+0x18] [ebp-0x4] BYREF

  p_DWORD = 0;
  p_DWORD2 = 0;
  m_bLockPropUI = this->m_bLockPropUI;
  p_DWORD3 = 0;
  if ( !this->sCGSHELF[64 * m_bLockPropUI + 44] )
  {
    (((CCBRoleState *)this->m_id))->CCBRoleState::UpdateCommandButtons((int)this->m_pfather);
    ((*((CCBUI **)this + 4)))->CCBUI::CreateLineupWindow((int)this->m_pfather, 1);
    byte_17A8EF8 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116) + 68);
    byte_17A8EF7 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 112) + 68);
    byte_17A8EF6 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 108) + 68);
    byte_17A8EF5 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 104) + 68);
    LOBYTE(g_pCCBRoleStateArrayEnd) = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 100) + 68);
    this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa003", 1);
  }
  if ( this->CCBRoleState::GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (unsigned int)p_DWORD >= 0xD6
    && (unsigned int)p_DWORD <= 0xDC )
  {
    if ( p_DWORD2 == -1 )
    {
      ((*((CCBUI **)this + 4)))->CCBUI::CreateLineupWindow((int)this->m_pfather, 0);
      v5 = (int *)((char *)((UIWnd *)this) + 64 * this->m_bLockPropUI + 128);
      FindFreeThread((CCBSystem *)this, *v5, v5[1], v5[2], v5[3], 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::StartLineupPhase) */, 0, 0, 0, 0);
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
      return 0;
    }
    switch ( p_DWORD )
    {
      case 214:
        if ( p_DWORD2 == 1 )
        {
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116) + 68) )
          {
            v15 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v15))->CScreenMode::AudioSetPosition("wa001", 1);
          }
          else
          {
            v13 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v13))->CScreenMode::AudioSetPosition("wa004", 1);
            v14 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 96);
            *(_DWORD *)(v14 + 80) = 0;
            *(_BYTE *)(v14 + 68) = 0;
          }
        }
        if ( !p_DWORD2 )
        {
          v16 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v16))->CScreenMode::AudioSetPosition("wa001", 1);
          v17 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 108);
          *(_DWORD *)(v17 + 80) = 0;
          *(_BYTE *)(v17 + 68) = 0;
          v18 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 100);
          *(_DWORD *)(v18 + 80) = 0;
          *(_BYTE *)(v18 + 68) = 0;
          v19 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 104);
          *(_DWORD *)(v19 + 80) = 0;
          *(_BYTE *)(v19 + 68) = 0;
          v20 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116);
          *(_DWORD *)(v20 + 80) = 0;
          *(_BYTE *)(v20 + 68) = 0;
        }
        break;
      case 215:
        if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116) + 68) )
          goto LABEL_29;
        v21 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v21))->CScreenMode::AudioSetPosition("wa004", 1);
        v22 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 100);
        *(_DWORD *)(v22 + 80) = 0;
        *(_BYTE *)(v22 + 68) = 0;
        break;
      case 216:
        if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116) + 68) )
          goto LABEL_29;
        v23 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v23))->CScreenMode::AudioSetPosition("wa004", 1);
        v24 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 104);
        *(_DWORD *)(v24 + 80) = 0;
        *(_BYTE *)(v24 + 68) = 0;
        break;
      case 217:
        if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116) + 68) )
          goto LABEL_29;
        v25 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v25))->CScreenMode::AudioSetPosition("wa004", 1);
        v26 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 108);
        *(_DWORD *)(v26 + 80) = 0;
        *(_BYTE *)(v26 + 68) = 0;
        break;
      case 218:
        if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116) + 68) )
        {
LABEL_29:
          v29 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v29))->CScreenMode::AudioSetPosition("wa001", 1);
        }
        else
        {
          v27 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v27))->CScreenMode::AudioSetPosition("wa004", 1);
          v28 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 112);
          if ( *(_BYTE *)(v28 + 68) )
          {
            *(_DWORD *)(v28 + 80) = 0;
            *(_BYTE *)(v28 + 68) = 0;
          }
          else
          {
            *(_DWORD *)(v28 + 80) = 1;
            *(_BYTE *)(v28 + 68) = 1;
          }
        }
        break;
      case 219:
        v7 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v7))->CScreenMode::AudioSetPosition("wa001", 1);
        if ( p_DWORD2 == 1 )
        {
          v8 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 96);
          *(_DWORD *)(v8 + 80) = 1;
          *(_BYTE *)(v8 + 68) = 1;
        }
        if ( !p_DWORD2 )
        {
          v9 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 108);
          *(_DWORD *)(v9 + 80) = 0;
          *(_BYTE *)(v9 + 68) = 0;
          v10 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 100);
          *(_DWORD *)(v10 + 80) = 0;
          *(_BYTE *)(v10 + 68) = 0;
          v11 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 104);
          *(_DWORD *)(v11 + 80) = 0;
          *(_BYTE *)(v11 + 68) = 0;
          v12 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 96);
          *(_DWORD *)(v12 + 80) = 0;
          *(_BYTE *)(v12 + 68) = 0;
        }
        break;
      default:
        break;
    }
    if ( p_DWORD == 220 )
    {
      v30 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v30))->CScreenMode::AudioSetPosition("wa001", 1);
      v39 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 96) + 68);
      LOBYTE((((CCBRoleState *)this->m_id))->CCBRoleState::InitUI((int)this->m_pfather)[1].dwMagicID[0][5]) = v39;
      v40 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 104) + 68);
      BYTE2((((CCBRoleState *)this->m_id))->CCBRoleState::InitUI((int)this->m_pfather)[1].dwMagicID[0][5]) = v40;
      v41 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 108) + 68);
      BYTE1((((CCBRoleState *)this->m_id))->CCBRoleState::InitUI((int)this->m_pfather)[1].dwMagicID[0][5]) = v41;
      v42 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 100) + 68);
      HIBYTE((((CCBRoleState *)this->m_id))->CCBRoleState::InitUI((int)this->m_pfather)[1].dwMagicID[0][5]) = v42;
      v31 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 112) + 68) == 0;
      LOBYTE((((CCBRoleState *)this->m_id))->CCBRoleState::InitUI((int)this->m_pfather)[1].dwMagicID[1][0]) = v31;
      v32 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1132) + 116) + 68);
      BYTE1((((CCBRoleState *)this->m_id))->CCBRoleState::InitUI((int)this->m_pfather)[1].dwMagicID[1][0]) = v32;
      ((*((CCBUI **)this + 4)))->CCBUI::CreateLineupWindow((int)this->m_pfather, 0);
      v33 = (_DWORD *)*(_DWORD **)(this->m_rect.left + 1132);
      v34 = *(_BYTE *)(v33[29] + 68);
      if ( (!v34
         || byte_17A8EF7 == *(_BYTE *)(v33[28] + 68)
         && byte_17A8EF6 == *(_BYTE *)(v33[27] + 68)
         && byte_17A8EF5 == *(_BYTE *)(v33[26] + 68)
         && (_BYTE)g_pCCBRoleStateArrayEnd == *(_BYTE *)(v33[25] + 68))
        && byte_17A8EF8 == v34 )
      {
        v35 = (int *)((char *)((UIWnd *)this) + 64 * this->m_bLockPropUI + 128);
        FindFreeThread((CCBSystem *)this, *v35, v35[1], v35[2], v35[3], 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::StartLineupPhase) */, 0, 0, 0, 0);
        this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
        return 0;
      }
      v36 = this->m_bLockPropUI;
      LOBYTE(this->m_fTimeScale) = 1;
      v36 <<= 6;
      this->m_bvisible = *(_DWORD *)&this->sCGSHELF[v36 + 23];
      v37 = *(_DWORD *)&this->sCGSHELF[v36 + 27];
      this->m_fTimerLimit = -1;
      this->m_benable = v37;
      m_pfather = this->m_pfather;
      this->m_bfocus = (int)m_pfather;
      *((_BYTE *)&this->m_fTimerLimit + 4) = 0;
      *((_BYTE *)&this->m_fTimerLimit + 5) = 0;
      (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)m_pfather, 0);
      goto LABEL_41;
    }
  }
  if ( BYTE1(this->m_childs.m_pData) )
  {
    ((*((CCBUI **)this + 4)))->CCBUI::CreateLineupWindow((int)this->m_pfather, 0);
    (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
LABEL_41:
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  return 0;
}

// 0x004DDC90
int CCBRoleState::EndRoundTasks(int B4)
{
  int v3; // edi
  int v4; // ebp
  int v5; // ebx
  CCBRoleState *m_id; // ecx
  int v7; // ecx
  int RoleIndex; // eax
  int v9; // edi
  int v10; // eax
  CScreenMode *Instance; // eax
  unsigned int Color; // eax
  int v13; // ebp
  int v14; // ebx
  int i; // edi
  int v16; // ecx
  int v17; // edi
  int v18; // ebx
  int v19; // ebp
  BYTE *v20; // edi
  CCBRoleState *v21; // ecx
  int v22; // ebp
  CCBStage *v23; // ecx
  int v24; // edi
  int *v25; // ecx
  char *v26; // eax
  int v27; // edx
  UIWnd *m_pfather; // eax
  CCBSystem *v29; // ecx
  int v30; // ebp
  CCBStage *v31; // ecx
  int v32; // edi
  int *v33; // eax
  int v34; // edx
  int v35; // ebx
  unsigned int v36; // eax
  int *v37; // eax
  int v38; // edx
  int v39; // ebp
  LONG left; // ecx
  int v41; // eax
  int x; // edi
  int v43; // ecx
  int y; // edx
  DWORD v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  char v49; // al
  int v50; // eax
  LONG v51; // ecx
  int v52; // ebp
  int v53; // eax
  int j; // edi
  CCBRoleState *v55; // ecx
  tagRoleState *inited; // eax
  CCBRoleState *v57; // ecx
  tagRoleState *v58; // ebx
  tagRoleState *v59; // eax
  int v60; // edi
  int v61; // ebp
  CCBStage *v62; // ecx
  int v63; // edi
  CCBStage *v64; // ecx
  int v65; // edi
  Combat *v67; // [esp-0x10] [ebp-C0h]
  int nVal5; // [esp+0x0] [ebp-B0h]
  int v69; // [esp+0x4] [ebp-ACh]
  int v70; // [esp+0x18] [ebp-0x98]
  int v71; // [esp+0x18] [ebp-0x98]
  int v72; // [esp+0x18] [ebp-0x98]
  int v73; // [esp+0x1C] [ebp-0x94]
  int v74; // [esp+0x1C] [ebp-0x94]
  int v75; // [esp+0x1C] [ebp-0x94]
  int v76; // [esp+0x20] [ebp-0x90]
  int v77; // [esp+0x20] [ebp-0x90]
  int v78; // [esp+0x20] [ebp-0x90]
  int v79; // [esp+0x24] [ebp-0x8C] BYREF
  int v80; // [esp+0x28] [ebp-0x88]
  int v81; // [esp+0x2C] [ebp-0x84]
  int v82; // [esp+0x30] [ebp-0x80]
  struct tagPOINT Point; // [esp+0x34] [ebp-0x7C] BYREF
  int p_DWORD2; // [esp+0x3C] [ebp-0x74] BYREF
  int p_DWORD; // [esp+0x40] [ebp-0x70] BYREF
  _DWORD pData[11]; // [esp+0x44] [ebp-0x6C] BYREF
  int p_DWORD3; // [esp+0x70] [ebp-0x40] BYREF
  _DWORD v88[11]; // [esp+0x74] [ebp-0x3C] BYREF
  _BYTE a2[16]; // [esp+A0h] [ebp-0x10] BYREF

  memset(v88, 0, sizeof(v88));
  if ( !this->sCGSHELF[64 * this->m_bLockPropUI + 44] )
  {
    v3 = 24;
    v4 = 0;
    v5 = 0;
    *(_BYTE *)(*(_DWORD *)(this->m_wndcolor.Color + 4 * (int)this->m_pfather + 24) + 280) = 0;
    do
    {
      m_id = (CCBRoleState *)this->m_id;
      if ( m_id->m_pObjMsgBuffer[v5 + 153] )
      {
        *(_DWORD *)(&unk_17A8EE0 + v3 - 24) = *(_DWORD *)&(((CCBRoleState *)m_id))->CCBRoleState::InitUI(v4)->byMagicUseTime[8][3];
        v7 = *(_DWORD *)(this->m_wndcolor.Color + v3);
        if ( *(_BYTE *)(v7 + 373) && *(_BYTE *)(v7 + 374) )
          return 0;
        if ( *(_BYTE *)(v7 + 373) == 1 )
          (((CCBStage *)v7))->CCBStage::GetCurrentTaskIndex();
        (((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v3)))->CCBStage::DelAllTask(0x7FFFFFFF, 1);
      }
      v3 += 4;
      ++v4;
      v5 += 892;
    }
    while ( v3 < 44 );
    nID = 0;
    ((*((CCBUI **)this + 4)))->CCBUI::CreateFiveNimbus(1);
    (((CCBCamControl *)*(CCBCamControl **)(this->m_wndcolor.Color + 16)))->CCBCamControl::ClearFinishedTask(6);
    RoleIndex = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleIndex(3, 0, 1);
    v9 = RoleIndex;
    if ( RoleIndex != -1 )
    {
      LOBYTE(v10) = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::EndTask(RoleIndex);
      nID = v10;
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::IsTaskValid) */, 0, 0, 0, 0, -1082130432, 1056964608);
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(v9);
    }
    this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa003", 1);
  }
  if ( !(unsigned __int8)(((CCBSystem *)this->m_wndcolor.Color))->CCBSystem::FindThreadByID(nID) )
  {
    Color = this->m_wndcolor.Color;
    EndTurnAndAdvance(
      *(_DWORD *)(Color + 68),
      *(_DWORD *)(*(_DWORD *)(Color + 20) + 900),
      *(_DWORD *)(*(_DWORD *)(Color + 20) + 904),
      *(_DWORD *)(*(_DWORD *)(Color + 20) + 908),
      COERCE_INT(*(float *)(*(_DWORD *)(Color + 20) + 916)));
  }
  v13 = 0;
  v14 = 0;
  for ( i = 96; i < 116; i += 4 )
  {
    if ( *(_BYTE *)(v14 + this->m_id + 577) && (((CCBRoleState *)v13))->CCBRoleState::SetVisible() )
      v16 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1136) + i);
    else
      v16 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1136) + i);
    sub_445E50(v16);
    ++v13;
    v14 += 892;
  }
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( this->CCBRoleState::GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (unsigned int)p_DWORD >= 0xF1
    && (unsigned int)p_DWORD <= 0xF5
    && p_DWORD2 == -1 )
  {
    g_nTargetSlot = -1;
    ((*((CCBUI **)this + 4)))->CCBUI::CreateFiveNimbus(0);
    (((CCBCamControl *)*(CCBCamControl **)(this->m_wndcolor.Color + 16)))->CCBCamControl::ClearFinishedTask(7);
    v17 = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleIndex(3, 0, 1);
    if ( v17 != -1 )
    {
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v17, 0 /* TODO: (int)CCBStage::IsSubTaskValid */, 0, 0, 0, 0, -1082130432, 1056964608);
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(v17);
    }
    v18 = 0;
    v19 = 0;
    v20 = (BYTE *)&unk_17A8EE0;
    while ( 1 )
    {
      v21 = (CCBRoleState *)this->m_id;
      if ( v21->m_pObjMsgBuffer[v19 + 153] )
      {
        if ( *(_DWORD *)v20 != *(_DWORD *)&(((CCBRoleState *)v21))->CCBRoleState::InitUI(v18)->byMagicUseTime[8][3] )
          break;
      }
      v20 += 4;
      ++v18;
      v19 += 892;
      if ( (int)v20 >= (int)&g_pCCBRoleStateArrayEnd )
      {
        v22 = 24;
        v70 = 0;
        v73 = 0;
        v76 = 24;
        do
        {
          if ( *(_BYTE *)(this->m_id + v73 + 577) )
          {
            (((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v22)))->CCBStage::GetCurrentTask(0x7FFFFFFF);
            (((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v22)))->CCBStage::TryRelease();
            if ( !(((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v22)))->CCBStage::ForceEndTaskByPFN() )
            {
              memset(pData, 0, sizeof(pData));
              v23 = (CCBStage *)this->m_wndcolor.Color;
              LOBYTE(pData[10]) = 1;
              pData[2] = v70;
              pData[1] = 264;
              v24 = (((CCBStage *)v23))->CCBStage::GetRoleIndex(9, pData, 1);
              if ( v24 != -1 )
              {
                v81 = pData[3];
                v80 = pData[2];
                v79 = 0;
                (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v24, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, &v79, -1082130432, 0);
                (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v24, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcShowItemName) */, 0, 0, 0, &v79, -1082130432, 0);
                (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v24, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, &v79, -1082130432, 0);
                (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(v24);
                v22 = v76;
              }
            }
          }
          v22 += 4;
          ++v70;
          v76 = v22;
          v73 += 892;
        }
        while ( v22 < 44 );
        v25 = (int *)((char *)((UIWnd *)this) + 64 * this->m_bLockPropUI + 128);
        FindFreeThread((CCBSystem *)this, *v25, v25[1], v25[2], v25[3], 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::EndRoundTasks) */, 0, 0, 0, 0);
        this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
        return 0;
      }
    }
    v26 = (char *)this + 64 * this->m_bLockPropUI;
    this->m_fTimerLimit = 0;
    LOBYTE(this->m_fTimeScale) = 1;
    this->m_bvisible = *((_DWORD *)v26 + 38);
    v27 = *((_DWORD *)v26 + 39);
    v29 = (CCBSystem *)this->m_fontcolor.Color;
    m_pfather = this->m_pfather;
    this->m_benable = v27;
    this->m_bfocus = (int)m_pfather;
    this->m_fTimerLimit = -1;
    *((_BYTE *)&this->m_fTimerLimit + 4) = 0;
    *((_BYTE *)&this->m_fTimerLimit + 5) = 0;
    (((CCBSystem *)v29))->CCBSystem::SetCmdParam((int)m_pfather, 0);
    v30 = 24;
    v71 = 0;
    v74 = 0;
    v77 = 24;
    do
    {
      if ( *(_BYTE *)(this->m_id + v74 + 577) )
      {
        (((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v30)))->CCBStage::GetCurrentTask(0x7FFFFFFF);
        (((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v30)))->CCBStage::TryRelease();
        if ( !(((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v30)))->CCBStage::ForceEndTaskByPFN() )
        {
          memset(pData, 0, sizeof(pData));
          v31 = (CCBStage *)this->m_wndcolor.Color;
          LOBYTE(pData[10]) = 1;
          pData[2] = v71;
          pData[1] = 264;
          v32 = (((CCBStage *)v31))->CCBStage::GetRoleIndex(9, pData, 1);
          if ( v32 != -1 )
          {
            v79 = 0;
            v81 = pData[3];
            v80 = pData[2];
            (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v32, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, &v79, -1082130432, 0);
            (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v32, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcShowItemName) */, 0, 0, 0, &v79, -1082130432, 0);
            (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v32, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, &v79, -1082130432, 0);
            (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(v32);
            v30 = v77;
          }
        }
      }
      v30 += 4;
      ++v71;
      v77 = v30;
      v74 += 892;
    }
    while ( v30 < 44 );
    goto LABEL_79;
  }
  v33 = (int *)sub_445FE0(a2);
  v69 = (unsigned long)v33[1];
  nVal5 = (unsigned long)*v33;
  v34 = (unsigned long)v33[3];
  v67 = (Combat *)*(Combat **)(this->m_wndcolor.Color + 68);
  v81 = (unsigned long)v33[2];
  v82 = v34;
  (((Combat *)v67))->Combat::LogMessage((char *)0x12C, 200, "face %d, %d", nVal5, v69);
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&Point);
  if ( (((GRPinput *)&g_Input))->GRPinput::GetKeyState(0x100u) )
  {
    v35 = g_nTargetSlot;
    if ( g_nTargetSlot != -1 )
    {
      v45 = dword_17A8EDC;
      v43 = g_RoleSystemCombat.m_partyActor.m_bChangedMat;
      y = Point.y;
      x = Point.x;
LABEL_69:
      MoveToAbsolute(*(_DWORD **)(*(_DWORD *)(this->m_rect.left + 1136) + 4 * v35 + 96), x - v43, y - v45);
      goto LABEL_70;
    }
    v36 = CCBParabolaWindow_Update(Point.x, Point.y);
    g_nTargetSlot = v36;
    if ( v36 <= 0xA )
    {
      if ( !*(_BYTE *)(this->m_id + 892 * v36 + 577) )
      {
        g_nTargetSlot = -1;
        goto LABEL_70;
      }
      if ( !(((CCBRoleState *)v36))->CCBRoleState::SetVisible() )
      {
        g_nTargetSlot = -1;
        goto LABEL_70;
      }
      v36 = g_nTargetSlot;
    }
    if ( v36 != -1 )
    {
      (((CCBMagicWindow *)*(CCBMagicWindow **)(this->m_rect.left + 1136)))->CCBMagicWindow::Create(v36);
      v37 = (int *)sub_445FE0(a2);
      v38 = (unsigned long)*v37;
      v39 = (unsigned long)v37[1];
      v81 = (unsigned long)v37[2];
      left = this->m_rect.left;
      v82 = (unsigned long)v37[3];
      v41 = *(_DWORD *)(*(_DWORD *)(left + 1136) + 4 * g_nTargetSlot + 96);
      *(_DWORD *)(v41 + 76) = 1068708659;
      *(_DWORD *)(v41 + 80) = 1068708659;
      x = Point.x;
      v35 = g_nTargetSlot;
      v43 = Point.x - v38;
      y = Point.y;
      g_RoleSystemCombat.m_partyActor.m_bChangedMat = v43;
      v45 = Point.y - v39;
      dword_17A8EDC = Point.y - v39;
      if ( g_nTargetSlot != -1 )
        goto LABEL_69;
    }
  }
  else if ( g_nTargetSlot != -1 )
  {
    v46 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1136) + 4 * g_nTargetSlot + 96);
    *(_DWORD *)(v46 + 76) = 1065353216;
    *(_DWORD *)(v46 + 80) = 1065353216;
    (((CCBMagicWindow *)*(CCBMagicWindow **)(this->m_rect.left + 1136)))->CCBMagicWindow::_todo_0051BAB0(g_nTargetSlot);
    if ( v47 == -1
      || ((((CCBMagicWindow *)*(CCBMagicWindow **)(this->m_rect.left + 1136)))->CCBMagicWindow::_todo_0051BAB0(g_nTargetSlot),
          (((CCBRoleState *)this->m_id))->CCBRoleState::UnloadWeaponModel(v48),
          v49) )
    {
      (((RoleCameraCtrl *)*(RoleCameraCtrl **)(this->m_rect.left + 1136)))->RoleCameraCtrl::InitViewSlots();
      g_nTargetSlot = -1;
    }
    else
    {
      (((CCBMagicWindow *)*(CCBMagicWindow **)(this->m_rect.left + 1136)))->CCBMagicWindow::_todo_0051BAB0(g_nTargetSlot);
      (((CCBMagicWindow *)*(CCBMagicWindow **)(this->m_rect.left + 1136)))->CCBMagicWindow::Reset(g_nTargetSlot, v50);
      v51 = this->m_rect.left;
      LOBYTE(v88[10]) = 1;
      v88[2] = g_nTargetSlot;
      (((CCBMagicWindow *)*(CCBMagicWindow **)(v51 + 1136)))->CCBMagicWindow::_todo_0051BAB0(g_nTargetSlot);
      v88[3] = -1;
      v52 = 0;
      v88[1] = v53;
      for ( j = 0; j < 4460; j += 892 )
      {
        v55 = (CCBRoleState *)this->m_id;
        if ( v55->m_pObjMsgBuffer[j + 153] )
        {
          inited = (((CCBRoleState *)v55))->CCBRoleState::InitUI(v52);
          if ( *(_DWORD *)&inited->byMagicUseTime[8][3] == v88[1] )
          {
            v57 = (CCBRoleState *)this->m_id;
            v88[3] = v52;
            v58 = (((CCBRoleState *)v57))->CCBRoleState::InitUI(g_nTargetSlot);
            *(_DWORD *)&(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(v52)->byMagicUseTime[8][3] = *(_DWORD *)&v58->byMagicUseTime[8][3];
          }
        }
        ++v52;
      }
      v59 = (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(g_nTargetSlot);
      *(_DWORD *)&v59->byMagicUseTime[8][3] = v88[1];
      v60 = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleIndex(27, v88, 1);
      if ( v60 != -1 )
      {
        (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v60, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::SetupCombatAction) */, 0, 0, 0, 0, -1082130432, 0);
        (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(v60);
      }
      g_nTargetSlot = -1;
    }
  }
LABEL_70:
  if ( BYTE1(this->m_childs.m_pData) )
  {
    g_nTargetSlot = -1;
    ((*((CCBUI **)this + 4)))->CCBUI::CreateFiveNimbus(0);
    (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
    v61 = 24;
    v72 = 0;
    v75 = 0;
    v78 = 24;
    do
    {
      if ( *(_BYTE *)(this->m_id + v75 + 577) )
      {
        (((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v61)))->CCBStage::GetCurrentTask(0x7FFFFFFF);
        (((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v61)))->CCBStage::TryRelease();
        if ( !(((CCBStage *)*(CCBStage **)(this->m_wndcolor.Color + v61)))->CCBStage::ForceEndTaskByPFN() )
        {
          memset(pData, 0, sizeof(pData));
          v62 = (CCBStage *)this->m_wndcolor.Color;
          LOBYTE(pData[10]) = 1;
          pData[2] = v72;
          pData[1] = 264;
          v63 = (((CCBStage *)v62))->CCBStage::GetRoleIndex(9, pData, 1);
          if ( v63 != -1 )
          {
            v79 = 0;
            v80 = pData[2];
            v81 = pData[3];
            v64 = (CCBStage *)this->m_wndcolor.Color;
            v79 = 0;
            (((CCBStage *)v64))->CCBStage::GetRoleName(v63, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, &v79, -1082130432, 0);
            (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v63, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcShowItemName) */, 0, 0, 0, &v79, -1082130432, 0);
            (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v63, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, &v79, -1082130432, 0);
            (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(v63);
            v61 = v78;
          }
        }
      }
      v61 += 4;
      ++v72;
      v78 = v61;
      v75 += 892;
    }
    while ( v61 < 44 );
    (((CCBCamControl *)*(CCBCamControl **)(this->m_wndcolor.Color + 16)))->CCBCamControl::ClearFinishedTask(7);
    v65 = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleIndex(3, 0, 1);
    if ( v65 != -1 )
    {
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(v65, 0 /* TODO: (int)CCBStage::IsSubTaskValid */, 0, 0, 0, 0, -1082130432, 1056964608);
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(v65);
    }
LABEL_79:
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  return 0;
}

// 0x004DE8C0
int CCBRoleState::InitSelectionUI(int nVal)
{
  int m_bLockPropUI; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  CScreenMode *Instance; // eax
  unsigned int m_id; // ecx
  int v12; // ecx
  unsigned int v13; // ecx
  int v14; // ecx
  unsigned int v15; // ecx
  int v16; // ecx
  int v18; // edx
  CCBSystem *Color; // ecx
  UIWnd *m_pfather; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  float fValue; // [esp+0x0] [ebp-0x20]
  float fValuea; // [esp+0x0] [ebp-0x20]
  float fValueb; // [esp+0x0] [ebp-0x20]
  int p_DWORD; // [esp+0x14] [ebp-0xC] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x8] BYREF
  int p_DWORD3; // [esp+0x1C] [ebp-0x4] BYREF

  m_bLockPropUI = this->m_bLockPropUI;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( this->sCGSHELF[64 * m_bLockPropUI + 44] )
    goto LABEL_17;
  (((UIListBox *)*(UIListBox **)(*(_DWORD *)(this->m_rect.left + 1140) + 88)))->UIListBox::GetCurSel();
  (((UIListBox *)*(UIListBox **)(*(_DWORD *)(this->m_rect.left + 1140) + 92)))->UIListBox::GetCurSel();
  (((UIListBox *)*(UIListBox **)(*(_DWORD *)(this->m_rect.left + 1140) + 96)))->UIListBox::GetCurSel();
  (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)(this->m_rect.left + 1140) + 88)))->UIScrollBar::SetRange(100.0);
  (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)(this->m_rect.left + 1140) + 92)))->UIScrollBar::SetRange(100.0);
  (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)(this->m_rect.left + 1140) + 96)))->UIScrollBar::SetRange(100.0);
  fValue = (float)(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(1)->nLove;
  (((UIProgressBar *)*(UIProgressBar **)(*(_DWORD *)(this->m_rect.left + 1140) + 88)))->UIProgressBar::FindChildByName(fValue);
  fValuea = (float)(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(2)->nLove;
  (((UIProgressBar *)*(UIProgressBar **)(*(_DWORD *)(this->m_rect.left + 1140) + 92)))->UIProgressBar::FindChildByName(fValuea);
  fValueb = (float)(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(3)->nLove;
  (((UIProgressBar *)*(UIProgressBar **)(*(_DWORD *)(this->m_rect.left + 1140) + 96)))->UIProgressBar::FindChildByName(fValueb);
  v4 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76);
  *(_DWORD *)(v4 + 80) = 0;
  *(_BYTE *)(v4 + 68) = 0;
  v5 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80);
  *(_DWORD *)(v5 + 80) = 0;
  *(_BYTE *)(v5 + 68) = 0;
  v6 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84);
  *(_DWORD *)(v6 + 80) = 0;
  *(_BYTE *)(v6 + 68) = 0;
  if ( !(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(1)->bValid )
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76));
  if ( !(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(2)->bValid )
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80));
  if ( !(((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(3)->bValid )
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84));
  dword_5D5FEC = (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole;
  v7 = (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole - 1;
  if ( !v7 )
  {
    v9 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76);
    goto LABEL_15;
  }
  v8 = v7 - 1;
  if ( !v8 )
  {
    v9 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80);
    goto LABEL_15;
  }
  if ( v8 == 1 )
  {
    v9 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84);
LABEL_15:
    *(_DWORD *)(v9 + 80) = 1;
    *(_BYTE *)(v9 + 68) = 1;
    goto LABEL_16;
  }
  (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole = -1;
  dword_5D5FEC = -1;
LABEL_16:
  ((*((CCBStage **)this + 4)))->CCBStage::SetActionVisible(1);
  this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
  Instance = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa003", 1);
LABEL_17:
  m_id = this->m_id;
  if ( *(_BYTE *)(m_id + 1469) && (((CCBRoleState *)m_id))->CCBRoleState::IsRoleAlive(1) )
    v12 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76);
  else
    v12 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76);
  sub_445E50(v12);
  v13 = this->m_id;
  if ( *(_BYTE *)(v13 + 2361) && (((CCBRoleState *)v13))->CCBRoleState::IsRoleAlive(2) )
    v14 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80);
  else
    v14 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80);
  sub_445E50(v14);
  v15 = this->m_id;
  if ( *(_BYTE *)(v15 + 3253) && (((CCBRoleState *)v15))->CCBRoleState::IsRoleAlive(3) )
    v16 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84);
  else
    v16 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84);
  sub_445E50(v16);
  if ( this->CCBRoleState::GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (p_DWORD == 272 || p_DWORD == 282 || (unsigned int)p_DWORD >= 0x111 && (unsigned int)p_DWORD <= 0x113) )
  {
    if ( p_DWORD2 == -1 )
    {
      ((*((CCBStage **)this + 4)))->CCBStage::SetActionVisible(0);
      FindFreeThread(
        (CCBSystem *)this,
        *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 32),
        *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 33),
        *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 34),
        *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 35),
        0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::InitSelectionUI) */,
        0,
        0,
        0,
        0);
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
      return 0;
    }
    if ( p_DWORD == 282 )
    {
      (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole = -1;
      if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76) + 68) )
        (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole = 1;
      if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80) + 68) )
        (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole = 2;
      if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84) + 68) )
        (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole = 3;
      ((*((CCBStage **)this + 4)))->CCBStage::SetActionVisible(0);
      if ( dword_5D5FEC == (((CCBRoleState *)this->m_id))->CCBRoleState::InitUI(0)->nProtectRole )
      {
        FindFreeThread(
          (CCBSystem *)this,
          *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 32),
          *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 33),
          *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 34),
          *((_DWORD *)((UIWnd *)this) + 16 * this->m_bLockPropUI + 35),
          0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::InitSelectionUI) */,
          0,
          0,
          0,
          0);
      }
      else
      {
        v18 = this->m_bLockPropUI;
        LOBYTE(this->m_fTimeScale) = 1;
        v18 <<= 6;
        this->m_bvisible = *(_DWORD *)&this->sCGSHELF[v18 + 23];
        Color = (CCBSystem *)this->m_fontcolor.Color;
        m_pfather = this->m_pfather;
        this->m_benable = *(_DWORD *)&this->sCGSHELF[v18 + 27];
        this->m_bfocus = (int)m_pfather;
        *((_BYTE *)&this->m_fTimerLimit + 4) = 0;
        *((_BYTE *)&this->m_fTimerLimit + 5) = 0;
        (((CCBSystem *)Color))->CCBSystem::SetCmdParam((int)m_pfather, 0);
      }
      this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
      return 0;
    }
    if ( (unsigned int)p_DWORD >= 0x111 && p_DWORD2 == 1 )
    {
      v21 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76);
      *(_DWORD *)(v21 + 80) = 0;
      *(_BYTE *)(v21 + 68) = 0;
      v22 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80);
      *(_DWORD *)(v22 + 80) = 0;
      *(_BYTE *)(v22 + 68) = 0;
      v23 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84);
      *(_DWORD *)(v23 + 80) = 0;
      *(_BYTE *)(v23 + 68) = 0;
      switch ( p_DWORD )
      {
        case 273:
          v24 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 76);
LABEL_55:
          *(_DWORD *)(v24 + 80) = 1;
          *(_BYTE *)(v24 + 68) = 1;
          break;
        case 274:
          v24 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 80);
          goto LABEL_55;
        case 275:
          v24 = *(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1140) + 84);
          goto LABEL_55;
      }
    }
  }
  if ( BYTE1(this->m_childs.m_pData) )
  {
    ((*((CCBStage **)this + 4)))->CCBStage::SetActionVisible(0);
    (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
    this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  }
  return 0;
}

// 0x004DEE80
int CCBRoleState::DispatchCombatAction(int nVal)
{
  int RoleIndex; // esi
  char *v4; // eax
  UIWnd *m_pfather; // ecx
  int RoleNum; // edi
  int ActionPriority; // eax
  int SkillNum; // edi
  UIWnd *v9; // eax
  unsigned int m_id; // edx
  unsigned int v11; // eax
  int v12; // eax
  int v13; // eax
  int m_bLockPropUI; // ecx
  char *v15; // eax
  int v17; // esi
  CCBStage *Color; // ecx
  int v19; // eax
  int *p_m_bvisible; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  char *v25; // ecx
  char p_BYTE; // [esp+0x13] [ebp-0x41] BYREF
  int v27; // [esp+0x14] [ebp-0x40] BYREF
  int idx; // [esp+0x18] [ebp-0x3C]
  int p_DWORD[3]; // [esp+0x1C] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x28] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  LOBYTE(pData[10]) = 0;
  LOBYTE(pData[4]) = 0;
  RoleIndex = 0;
  v4 = (char *)this + 64 * this->m_bLockPropUI;
  v27 = 0;
  p_BYTE = 0;
  pData[0] = *((_DWORD *)v4 + 38);
  m_pfather = this->m_pfather;
  pData[1] = *((_DWORD *)v4 + 39);
  pData[2] = (unsigned long)m_pfather;
  pData[3] = -1;
  if ( !v4[173] )
  {
    switch ( *((_DWORD *)v4 + 38) )
    {
      case 0x103:
        RoleIndex = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleIndex(2, pData, 0);
        if ( RoleIndex != -1 )
        {
          v9 = this->m_pfather;
          m_id = this->m_id;
          p_DWORD[0] = 1;
          v11 = m_id + 892 * (_DWORD)v9;
          if ( *(_BYTE *)(v11 + 649) )
          {
            p_DWORD[0] = 5;
            goto LABEL_12;
          }
          v12 = -(*(_BYTE *)(v11 + 650) != 0);
          LOBYTE(v12) = v12 & 0xF8;
          ActionPriority = v12 + 17;
          goto LABEL_11;
        }
        break;
      case 0x104:
      case 0x105:
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*((_DWORD *)v4 + 39));
        RoleIndex = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleIndex(2, pData, 0);
        if ( RoleIndex != -1 )
        {
          ActionPriority = this->CCBRoleState::GetActionPriority(*(unsigned __int8 *)(RoleNum + 577));
          goto LABEL_11;
        }
        break;
      case 0x106:
        SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*((_DWORD *)v4 + 39));
        RoleIndex = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleIndex(2, pData, 0);
        if ( RoleIndex != -1 )
        {
          ActionPriority = this->CCBRoleState::GetActionPriority(*(unsigned __int8 *)(SkillNum + 629));
LABEL_11:
          p_DWORD[0] = ActionPriority;
LABEL_12:
          (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::HasNormalAttackRole) */, 0, 0, 0, p_DWORD, -1082130432, 0);
          (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRoleByIdx(RoleIndex);
        }
        break;
      default:
        break;
    }
    *(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 35] = RoleIndex;
    LOBYTE(v13) = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::EndTask(RoleIndex);
    *(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 39] = v13;
    this->sCGSHELF[64 * this->m_bLockPropUI + 44] = 1;
  }
  m_bLockPropUI = this->m_bLockPropUI;
  if ( BYTE1(this->m_childs.m_pData) != 1 )
  {
    v17 = *(_DWORD *)&this->sCGSHELF[64 * m_bLockPropUI + 35];
    Color = (CCBStage *)this->m_wndcolor.Color;
    idx = v17;
    (((CCBStage *)Color))->CCBStage::DelTask(v17, &p_BYTE, &v27);
    if ( p_BYTE == 1 )
    {
      LOBYTE(v19) = (((CCBStage *)this->m_wndcolor.Color))->CCBStage::IsDoTask(v17);
      p_m_bvisible = (int *)&this->m_bvisible;
      qmemcpy(&this->m_bvisible, (const void *)(v19 + 2584), 0x2Cu);
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::GetStageRole(idx);
      *(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 35] = -1;
      if ( v27 == -1 )
      {
        v21 = this->m_bLockPropUI;
        if ( *((_DWORD *)((UIWnd *)this) + 16 * v21 + 32) )
        {
LABEL_22:
          *(_BYTE *)(*(_DWORD *)(this->m_wndcolor.Color + 4 * (int)this->m_pfather + 24) + 280) = 1;
          v22 = this->m_bLockPropUI + 2;
          FindFreeThread(
            (CCBSystem *)this,
            *((_DWORD *)((UIWnd *)this) + 16 * v22),
            *(&this->m_fontcolor.Color + 16 * v22),
            *(&this->m_wndcolor.Color + 16 * v22),
            *(&this->m_id + 16 * v22),
            0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */,
            0,
            0,
            0,
            *(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 23]);
          this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
          return 0;
        }
LABEL_29:
        this->sCGSHELF[64 * v21 + 44] = 0;
        LOBYTE(this->m_fTimeScale) = 0;
        return 0;
      }
      v23 = (unsigned long)*p_m_bvisible;
      if ( (*p_m_bvisible == 259 || v23 == 261 || v23 == 260 || v23 == 262)
        && !(((CCBRoleState *)this->m_id))->CCBRoleState::SumGPCost((int)&this->m_bvisible) )
      {
        v21 = this->m_bLockPropUI;
        if ( *((_DWORD *)((UIWnd *)this) + 16 * v21 + 32) )
          goto LABEL_22;
        goto LABEL_29;
      }
      v24 = this->m_bLockPropUI;
      LOBYTE(this->m_fTimeScale) = 1;
      v25 = (char *)this + 64 * v24;
      *p_m_bvisible = *((_DWORD *)v25 + 38);
      this->m_benable = *((_DWORD *)v25 + 39);
      this->CCBRoleState::IsRoleShelved(v24);
    }
    return 0;
  }
  v15 = (char *)this + 64 * m_bLockPropUI;
  if ( *((_DWORD *)v15 + 41) != -1 )
  {
    if ( (unsigned __int8)(((CCBSystem *)this->m_wndcolor.Color))->CCBSystem::FindThreadByID(*((_DWORD *)v15 + 42)) )
      (((CCBStage *)this->m_wndcolor.Color))->CCBStage::Procced(*(_DWORD *)&this->sCGSHELF[64 * this->m_bLockPropUI + 35]);
  }
  (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
  memset(&this->m_bvisible, 0, 0x2Cu);
  this->CCBRoleState::IsRoleShelved(this->m_bLockPropUI);
  return 0;
}

// 0x004DF2F0
int CCBRoleState::ExecuteCombatCommand(int nVal)
{
  int v3; // eax
  char v4; // cl
  char *v5; // eax
  int m_bLockPropUI; // [esp-0x4] [ebp-0x8]

  v3 = this->m_bLockPropUI << 6;
  v4 = this->sCGSHELF[v3 + 44];
  v5 = (char *)&this->sCGSHELF[v3 + 44];
  if ( !v4 )
    *v5 = 1;
  if ( *(_DWORD *)&this->m_bLockCamera == 1 )
  {
    this->m_childs.capacity = 0;
    this->m_childs.m_nSize = 0;
    this->m_childs.m_needscriptdel = 0;
    this->m_bcreateok = 0;
    LOBYTE(this->m_childs.m_pData) = 0;
    (((CCBAttackSequen *)this->m_fontcolor.Color))->CCBAttackSequen::SetPause(0);
    (((CCBSystem *)this->m_fontcolor.Color))->CCBSystem::SetCmdParam((int)this->m_pfather, 0);
    *(_BYTE *)(*(_DWORD *)(this->m_wndcolor.Color + 4 * (int)this->m_pfather + 24) + 280) = 0;
    m_bLockPropUI = this->m_bLockPropUI;
    this->m_pfather = ((UIWnd *)((UIWnd *)-1));
    BYTE1(this->m_childs.m_pData) = 0;
    this->CCBRoleState::IsRoleShelved(m_bLockPropUI);
  }
  return 0;
}

// 0x004DF370
int CCBRoleState::GetActionPriority(int nVal)
{
  int result; // eax

  switch ( nVal )
  {
    case 1:
      result = 16;
      break;
    case 2:
      result = 2;
      break;
    case 4:
      result = 3;
      break;
    case 5:
      result = 5;
      break;
    case 6:
      result = 9;
      break;
    default:
      result = 17;
      break;
  }
  return result;
}

// 0x004DF3D0
char CCBRoleState::CheckSelfMP()
{
  (((CCBRoleState *)this->m_id))->CCBRoleState::GetRoleMP(1);
  return 1;
}

// 0x004DF6D0
int CCBRoleState::ResetDialogSlots()
{
  int result; // eax

  memset(&this->m_rect.top, 0, 0x4600u);
  this->m_wndcolor.Color = -1;
  result = 0;
  LOBYTE(this->m_RoleXor[9].byMagicUseTime[5][3]) = 0;
  this->m_rect.left = 0;
  return result;
}

// 0x004E1A40
int CCBRoleState::CombatDialogProc(
        
        int nVal,
        HWND hDlg,
        unsigned int uMsg,
        int wParam,
        int lParam)
{
  HWND DlgItem; // ebx
  HWND v8; // ebp
  HWND v9; // eax
  unsigned int v10; // eax
  int result; // eax
  LRESULT v12; // eax
  BOOL v13; // edx
  int v14; // ecx
  CCBRoleState *v15; // esi
  int Float; // edi
  HWND DialogParamA; // eax
  int v18; // esi
  _DWORD *v19; // eax
  HWND v20; // [esp+0x10] [ebp-0x28]
  HWND hWnd; // [esp+0x14] [ebp-0x24]
  LPARAM lParama[8]; // [esp+0x18] [ebp-0x20] BYREF
  HWND hDlga; // [esp+0x40] [ebp+0x8]

  DlgItem = GetDlgItem(hDlg, 1000);
  hDlga = GetDlgItem(hDlg, 1086);
  GetDlgItem(hDlg, 1042);
  v20 = GetDlgItem(hDlg, 1205);
  hWnd = GetDlgItem(hDlg, 1041);
  v8 = GetDlgItem(hDlg, 1209);
  v9 = GetDlgItem(hDlg, 1206);
  if ( uMsg <= 0x110 )
  {
    if ( uMsg == 272 )
    {
      memset(lParama, 0, sizeof(lParama));
      v12 = SendMessageA(DlgItem, 0x1037u, 0, 0);
      LOBYTE(v12) = v12 | 0x21;
      SendMessageA(DlgItem, 0x1036u, 0, v12);
      lParama[0] = 7;
      lParama[1] = 0;
      lParama[2] = 50;
      lParama[3] = (LPARAM)"ROLE";
      SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 22;
      lParama[3] = (LPARAM)"V";
      SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParama);
      lParama[2] = 49;
      lParama[3] = (LPARAM)"HP";
      SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParama);
      lParama[3] = (LPARAM)"GP";
      SendMessageA(DlgItem, 0x101Bu, 3u, (LPARAM)lParama);
      lParama[3] = (LPARAM)"MP";
      SendMessageA(DlgItem, 0x101Bu, 4u, (LPARAM)lParama);
      SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
      LOBYTE(v13) = (_BYTE)unk_5DFDEB == 0;
      EditBoxSetReadOnly(v20, v13);
      v14 = nVal;
      LOBYTE(v14) = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)nVal + 16) + 516);
      EditBoxSetReadOnly(v8, v14);
      EnableWindow(hWnd, g_bFullScreen);
      return 0;
    }
    if ( uMsg == 16 )
    {
      EndDialog(hDlg, (unsigned __int16)wParam);
      return 1;
    }
    if ( uMsg == 78 && wParam == 1000 && *(_DWORD *)(lParam + 8) == -2 )
    {
      v10 = *(_DWORD *)(lParam + 12);
      if ( v10 != -1 )
      {
        roleIdx = *(_DWORD *)(lParam + 12);
        byte_17A9934 = 1;
        if ( v10 > 4 )
          EnableWindow(hDlga, 0);
        else
          EnableWindow(hDlga, 1);
        return 0;
      }
    }
    return 0;
  }
  if ( uMsg != 273 )
    return 0;
  switch ( (__int16)wParam )
  {
    case 1038:
      byte_17A9935 = 1;
      return 0;
    case 1040:
      DialogParamA = (HWND)g_hCombatDlg2;
      if ( !g_hCombatDlg2 )
      {
        DialogParamA = CreateDialogParamA(hInstance, (LPCSTR)0x6D, (HWND)g_todo_BFDA4C, (DLGPROC)CCBUI::DlgProcMain, 0);
        g_hCombatDlg2 = (int)DialogParamA;
      }
      goto LABEL_25;
    case 1041:
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)5);
      return 0;
    case 1042:
      DialogParamA = (HWND)g_hCombatDlg1;
      if ( !g_hCombatDlg1 )
      {
        DialogParamA = CreateDialogParamA(
                         hInstance,
                         (LPCSTR)0x6C,
                         (HWND)g_todo_BFDA4C,
                         (DLGPROC)CCBUI::HandleWindowMessage,
                         0);
        g_hCombatDlg1 = (int)DialogParamA;
      }
      goto LABEL_25;
    case 1043:
      DialogParamA = (HWND)dwInitParam;
      if ( !dwInitParam )
      {
        DialogParamA = CreateDialogParamA(
                         hInstance,
                         (LPCSTR)0x6B,
                         (HWND)g_todo_BFDA4C,
                         (DLGPROC)CCBUI::SettingsDialogProc,
                         0);
        dwInitParam = (int)DialogParamA;
      }
LABEL_25:
      ::ShowWindow(DialogParamA, 5);
      result = 0;
      break;
    case 1044:
      v19 = (_DWORD *)*(_DWORD **)(*(_DWORD *)(*(_DWORD *)nVal + 20) + 16);
      v19[107519] = 1092616192;
      v19[107521] = 1119092736;
      v19[107520] = 1092616192;
      return 0;
    case 1045:
      (((CCBStage *)((unsigned __int16)wParam - 1038)))->CCBStage::DestroyPreviewWindow();
      result = 0;
      break;
    case 1086:
      byte_17A9936 = 1;
      result = 0;
      break;
    case 1159:
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)6);
      result = 0;
      break;
    case 1205:
      LOBYTE(unk_5DFDEB) = !EditBoxIsModified(v20);
      result = 0;
      break;
    case 1207:
      v15 = (CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)nVal + 16);
      Float = (__int64)EditBoxGetFloat(v9);
      (((CCBRoleState *)v15))->CCBRoleState::InitUI(0)->nMoney = Float;
      result = 0;
      break;
    case 1209:
      v18 = *(_DWORD *)(*(_DWORD *)nVal + 16);
      *(_BYTE *)(v18 + 516) = EditBoxIsModified(v8);
      result = 0;
      break;
    default:
      return 0;
  }
  return result;
}

// 0x004E28F0
LRESULT CCBRoleState::UpdateDebugTreeView()
{
  LRESULT result; // eax
  HWND DlgItem; // ebp
  int i; // esi
  int v5; // eax
  int v6; // edx
  tagRoleState *inited; // eax
  int v8; // eax
  tagRoleState *v9; // eax
  int v10; // ecx
  tagRoleState *v11; // eax
  LPARAM lParam[10]; // [esp+0x4] [ebp-0x128] BYREF
  char Buffer[256]; // [esp+0x2C] [ebp-0x100] BYREF

  result = g_nCombatViewMode;
  if ( g_nCombatViewMode == 2 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1000);
    memset(lParam, 0, sizeof(lParam));
    SendMessageA(DlgItem, 0x1009u, 0, 0);
    for ( i = 0; i < 11; ++i )
    {
      lParam[0] = 1;
      lParam[1] = i;
      lParam[2] = 0;
      lParam[5] = (LPARAM)Buffer;
      switch ( i )
      {
        case 0:
          sprintf(Buffer, byte_5D899C, 0);
          break;
        case 1:
          sprintf(Buffer, byte_5D8994, 1);
          break;
        case 2:
          sprintf(Buffer, byte_5D898C, 2);
          break;
        case 3:
          sprintf(Buffer, byte_5D8984, 3);
          break;
        case 4:
          sprintf(Buffer, byte_5D897C, 4);
          break;
        default:
          sprintf(Buffer, (const char *)&unk_5D8974, i);
          break;
      }
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      v5 = (int)((UIWnd *)this);
      lParam[2] = 1;
      if ( *(_BYTE *)(*(_DWORD *)(v5 + 16) + 892 * i + 577) )
      {
        sprintf(Buffer, aY);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      }
      v6 = (int)((UIWnd *)this);
      lParam[2] = 2;
      inited = (((CCBRoleState *)*(CCBRoleState **)(v6 + 16)))->CCBRoleState::InitUI(i);
      sprintf(Buffer, (const char *)&dir[20], inited->nHP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      v8 = (int)((UIWnd *)this);
      lParam[2] = 3;
      v9 = (((CCBRoleState *)*(CCBRoleState **)(v8 + 16)))->CCBRoleState::InitUI(i);
      sprintf(Buffer, (const char *)&dir[20], v9->nGP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      v10 = (int)((UIWnd *)this);
      lParam[2] = 4;
      v11 = (((CCBRoleState *)*(CCBRoleState **)(v10 + 16)))->CCBRoleState::InitUI(i);
      sprintf(Buffer, (const char *)&dir[20], v11->nMP);
      result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
  }
  return result;
}

// 0x004E2C10
LRESULT CCBRoleState::HandleDlgMessage()
{
  LRESULT result; // eax
  HWND DlgItem; // esi
  tagRoleState *inited; // eax

  result = g_nCombatViewMode;
  if ( g_nCombatViewMode == 2 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1206);
    inited = (((CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)((UIWnd *)this) + 16)))->CCBRoleState::InitUI(0);
    return EditBoxSetInt(DlgItem, inited->nMoney);
  }
  return result;
}

// 0x004E30E0
unsigned __int8 CCBRoleState::SyncRoleUIData()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  unsigned __int8 result; // al
  int v5; // ebx
  int v6; // ebx
  int v7; // ebx
  unsigned int v8; // ebx
  int v9; // ebx
  tagRoleState *inited; // eax
  int v11; // ebx
  CCBSystem *v12; // ebx
  unsigned int v13; // ebx
  int v14; // ebx
  tagRoleState *v15; // eax
  CCBStage *v16; // ebx
  int v17; // ebx
  unsigned int v18; // ebx
  int v19; // ebx
  tagRoleState *v20; // eax
  int v21; // ebx
  unsigned int v22; // ebx
  int v23; // ebx
  unsigned int v24; // ebx
  int v25; // ebx
  unsigned int v26; // ebx
  int v27; // ebx
  unsigned int v28; // ebx
  int v29; // edi
  float fValue; // [esp+0x0] [ebp-0x40]
  float fValuea; // [esp+0x0] [ebp-0x40]
  float fValueb; // [esp+0x0] [ebp-0x40]
  HWND hWnd; // [esp+0x18] [ebp-0x28]
  HWND v34; // [esp+0x1C] [ebp-0x24]
  HWND v35; // [esp+0x20] [ebp-0x20]
  HWND v36; // [esp+0x24] [ebp-0x1C]
  HWND v37; // [esp+0x28] [ebp-0x18]
  HWND v38; // [esp+0x2C] [ebp-0x14]
  HWND v39; // [esp+0x30] [ebp-0x10]
  HWND v40; // [esp+0x34] [ebp-0xC]
  HWND v41; // [esp+0x38] [ebp-0x8]
  HWND v42; // [esp+0x3C] [ebp-0x4]

  GetDlgItem(g_hMainWnd, 1024);
  DlgItem = GetDlgItem(g_hMainWnd, 1026);
  v3 = GetDlgItem(g_hMainWnd, 1032);
  hWnd = GetDlgItem(g_hMainWnd, 1025);
  v34 = GetDlgItem(g_hMainWnd, 1033);
  v35 = GetDlgItem(g_hMainWnd, 1027);
  v36 = GetDlgItem(g_hMainWnd, 1034);
  v37 = GetDlgItem(g_hMainWnd, 1028);
  v38 = GetDlgItem(g_hMainWnd, 1029);
  v39 = GetDlgItem(g_hMainWnd, 1030);
  v40 = GetDlgItem(g_hMainWnd, 1031);
  v41 = GetDlgItem(g_hMainWnd, 1035);
  v42 = GetDlgItem(g_hMainWnd, 1036);
  result = roleIdx;
  if ( roleIdx <= 0xA )
  {
    result = *(_BYTE *)(this->m_fontcolor.Color + 892 * roleIdx + 577);
    if ( result )
    {
      SendMessageA(DlgItem, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v5 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nHP = v5;
      if ( !(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->bAlive
        && (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nHP > 0 )
      {
        (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 25, 0, 1);
        (((CCBStage *)*(CCBStage **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + 4 * roleIdx + 24)))->CCBStage::Release(1);
        v6 = atoi((const char *)&g_CCBStageCamBuffer);
        (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nHP = v6;
      }
      if ( (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->bAlive == 1
        && !(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nHP )
      {
        (((CCBSystem *)*(CCBSystem **)((UIWnd *)this)))->CCBSystem::ProcMessage(roleIdx);
        (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 25, 1, 1);
        (((CCBStage *)*(CCBStage **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + 4 * roleIdx + 24)))->CCBStage::Release(0);
      }
      SendMessageA(v3, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v7 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nFullHP = v7;
      if ( roleIdx <= 4 )
      {
        v8 = 1408 * roleIdx;
        *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_nPathEnabled + v8) += (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nFullHP
                                                                                      - *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame
                                                                                                  + v8);
        v9 = *(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4);
        fValue = (float)atoi((const char *)&g_CCBStageCamBuffer);
        inited = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx);
        (((UIScrollBar *)*(UIScrollBar **)(v9 + 4 * (unsigned __int8)inited->byUIIndex + 1020)))->UIScrollBar::SetRange(fValue);
      }
      SendMessageA(hWnd, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v11 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nGP = v11;
      SendMessageA(v34, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v12 = (CCBSystem *)atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->pCCBSystem = v12;
      if ( roleIdx <= 4 )
      {
        v13 = 1408 * roleIdx;
        *(_DWORD *)(&g_RoleSlotBuf.m_partyActor.m_fScale + v13) += (unsigned long)(char *)(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->pCCBSystem
                                                                 - *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame
                                                                             + v13
                                                                             + 4);
        v14 = *(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4);
        fValuea = (float)atoi((const char *)&g_CCBStageCamBuffer);
        v15 = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx);
        (((UIScrollBar *)*(UIScrollBar **)(v14 + 4 * (unsigned __int8)v15->byUIIndex + 1036)))->UIScrollBar::SetRange(fValuea);
      }
      SendMessageA(v35, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v16 = (CCBStage *)atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nMP = v16;
      SendMessageA(v36, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v17 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nFullMP = v17;
      if ( roleIdx <= 4 )
      {
        v18 = 1408 * roleIdx;
        *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixA + v18) += (unsigned long)(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nFullMP
                                                                           - *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame
                                                                                       + v18
                                                                                       + 8);
        v19 = *(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4);
        fValueb = (float)atoi((const char *)&g_CCBStageCamBuffer);
        v20 = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx);
        (((UIScrollBar *)*(UIScrollBar **)(v19 + 4 * (unsigned __int8)v20->byUIIndex + 1052)))->UIScrollBar::SetRange(fValueb);
      }
      SendMessageA(v37, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v21 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nLevel = v21;
      SendMessageA(v38, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx);
      atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleLevel(roleIdx);
      v22 = 1408 * roleIdx;
      *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_nMatrixParam + v22) += (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nSpeed
                                                                                     - *(unsigned int *)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v22 + 8);
      SendMessageA(v39, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v23 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nAttack = v23;
      v24 = 1408 * roleIdx;
      *(_DWORD *)(&g_RoleSlotBuf.m_partyActor.m_fMatrixB + v24) += (unsigned long)(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nAttack
                                                                 - *(unsigned int *)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData
                                                                                   + v24);
      SendMessageA(v40, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v25 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nDefence = v25;
      v26 = 1408 * roleIdx;
      *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + v26) += (unsigned long)(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nDefence
                                                                         - *(unsigned int *)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData
                                                                                           + v26
                                                                                           + 4);
      SendMessageA(v41, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v27 = atoi((const char *)&g_CCBStageCamBuffer);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nLuck = v27;
      v28 = 1408 * roleIdx;
      *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamA + v28) += (unsigned long)(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->nLuck
                                                                              - *(unsigned int *)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData
                                                                                                + v28
                                                                                                + 12);
      SendMessageA(v42, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v29 = atoi((const char *)&g_CCBStageCamBuffer);
      *(_DWORD *)&(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(roleIdx)->bLostMoneyGetLife = v29;
      (((CCBUI *)this))->CCBUI::HandleRoleStateDialog(roleIdx);
      return (((RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * roleIdx)))->RoleSystem::RecalcAggregatedStats(0);
    }
  }
  return result;
}

// 0x004E40B0
LRESULT CCBRoleState::UpdateDebugDialog()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  HWND v4; // edi
  LRESULT result; // eax
  CCBRoleState *Color; // ecx
  BOOL v7; // eax
  BOOL v8; // eax
  BOOL v9; // eax
  BOOL v10; // eax
  BOOL v11; // eax
  BOOL v12; // eax
  BOOL v13; // eax
  BOOL v14; // eax
  BOOL v15; // eax
  BOOL v16; // eax
  BOOL v17; // eax
  BOOL v18; // eax
  BOOL v19; // eax
  BOOL v20; // eax
  BOOL v21; // eax
  BOOL v22; // eax
  BOOL v23; // eax
  BOOL v24; // eax
  BOOL v25; // eax
  BOOL v26; // eax
  BOOL v27; // eax
  BOOL v28; // eax
  BOOL v29; // eax
  BOOL v30; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x54]
  HWND v32; // [esp+0x14] [ebp-0x50]
  HWND v33; // [esp+0x18] [ebp-0x4C]
  HWND v34; // [esp+0x1C] [ebp-0x48]
  HWND v35; // [esp+0x20] [ebp-0x44]
  HWND v36; // [esp+0x24] [ebp-0x40]
  HWND v37; // [esp+0x28] [ebp-0x3C]
  HWND v38; // [esp+0x2C] [ebp-0x38]
  HWND v39; // [esp+0x30] [ebp-0x34]
  HWND v40; // [esp+0x34] [ebp-0x30]
  HWND v41; // [esp+0x38] [ebp-0x2C]
  HWND v42; // [esp+0x3C] [ebp-0x28]
  HWND v43; // [esp+0x40] [ebp-0x24]
  HWND v44; // [esp+0x44] [ebp-0x20]
  HWND v45; // [esp+0x48] [ebp-0x1C]
  HWND v46; // [esp+0x4C] [ebp-0x18]
  HWND v47; // [esp+0x50] [ebp-0x14]
  HWND v48; // [esp+0x54] [ebp-0x10]
  HWND v49; // [esp+0x58] [ebp-0xC]
  HWND v50; // [esp+0x5C] [ebp-0x8]
  HWND v51; // [esp+0x60] [ebp-0x4]

  DlgItem = GetDlgItem((HWND)g_hCombatDlg1, 1116);
  v3 = GetDlgItem((HWND)g_hCombatDlg1, 1117);
  hWnd = GetDlgItem((HWND)g_hCombatDlg1, 1119);
  v32 = GetDlgItem((HWND)g_hCombatDlg1, 1118);
  v33 = GetDlgItem((HWND)g_hCombatDlg1, 1120);
  v34 = GetDlgItem((HWND)g_hCombatDlg1, 1121);
  v35 = GetDlgItem((HWND)g_hCombatDlg1, 1122);
  v36 = GetDlgItem((HWND)g_hCombatDlg1, 1123);
  v37 = GetDlgItem((HWND)g_hCombatDlg1, 1124);
  v38 = GetDlgItem((HWND)g_hCombatDlg1, 1125);
  v39 = GetDlgItem((HWND)g_hCombatDlg1, 1126);
  v40 = GetDlgItem((HWND)g_hCombatDlg1, 1127);
  v41 = GetDlgItem((HWND)g_hCombatDlg1, 1128);
  v42 = GetDlgItem((HWND)g_hCombatDlg1, 1129);
  v43 = GetDlgItem((HWND)g_hCombatDlg1, 1130);
  v44 = GetDlgItem((HWND)g_hCombatDlg1, 1131);
  v45 = GetDlgItem((HWND)g_hCombatDlg1, 1132);
  v46 = GetDlgItem((HWND)g_hCombatDlg1, 1133);
  v47 = GetDlgItem((HWND)g_hCombatDlg1, 1134);
  v48 = GetDlgItem((HWND)g_hCombatDlg1, 1135);
  v49 = GetDlgItem((HWND)g_hCombatDlg1, 1136);
  v50 = GetDlgItem((HWND)g_hCombatDlg1, 1137);
  v51 = GetDlgItem((HWND)g_hCombatDlg1, 1138);
  v4 = GetDlgItem((HWND)g_hCombatDlg1, 1140);
  result = roleIdx;
  if ( roleIdx <= 0xA )
  {
    Color = (CCBRoleState *)this->m_fontcolor.Color;
    if ( Color->m_pObjMsgBuffer[892 * roleIdx + 153] )
    {
      LOBYTE(v7) = (((CCBRoleState *)Color))->CCBRoleState::GetRoleField(roleIdx, 3);
      EditBoxSetReadOnly(DlgItem, v7);
      LOBYTE(v8) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 4);
      EditBoxSetReadOnly(v3, v8);
      LOBYTE(v9) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 1);
      EditBoxSetReadOnly(hWnd, v9);
      LOBYTE(v10) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 2);
      EditBoxSetReadOnly(v32, v10);
      LOBYTE(v11) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 5);
      EditBoxSetReadOnly(v33, v11);
      LOBYTE(v12) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 6);
      EditBoxSetReadOnly(v34, v12);
      LOBYTE(v13) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 7);
      EditBoxSetReadOnly(v35, v13);
      LOBYTE(v14) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 8);
      EditBoxSetReadOnly(v36, v14);
      LOBYTE(v15) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 9);
      EditBoxSetReadOnly(v37, v15);
      LOBYTE(v16) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 10);
      EditBoxSetReadOnly(v38, v16);
      LOBYTE(v17) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 11);
      EditBoxSetReadOnly(v39, v17);
      LOBYTE(v18) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 12);
      EditBoxSetReadOnly(v40, v18);
      LOBYTE(v19) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 13);
      EditBoxSetReadOnly(v41, v19);
      LOBYTE(v20) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 14);
      EditBoxSetReadOnly(v42, v20);
      LOBYTE(v21) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 15);
      EditBoxSetReadOnly(v43, v21);
      LOBYTE(v22) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 16);
      EditBoxSetReadOnly(v44, v22);
      LOBYTE(v23) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 17);
      EditBoxSetReadOnly(v45, v23);
      LOBYTE(v24) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 18);
      EditBoxSetReadOnly(v46, v24);
      LOBYTE(v25) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 19);
      EditBoxSetReadOnly(v47, v25);
      LOBYTE(v26) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 20);
      EditBoxSetReadOnly(v48, v26);
      LOBYTE(v27) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 21);
      EditBoxSetReadOnly(v49, v27);
      LOBYTE(v28) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 22);
      EditBoxSetReadOnly(v50, v28);
      LOBYTE(v29) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 23);
      EditBoxSetReadOnly(v51, v29);
      LOBYTE(v30) = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleField(roleIdx, 26);
      return EditBoxSetReadOnly(v4, v30);
    }
  }
  return result;
}

// 0x004E4570
char CCBRoleState::ApplyDebugEdits()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  HWND v4; // edi
  char result; // al
  BOOL IsModified; // eax
  BOOL v7; // eax
  BOOL v8; // eax
  BOOL v9; // eax
  BOOL v10; // eax
  BOOL v11; // eax
  BOOL v12; // eax
  BOOL v13; // eax
  BOOL v14; // eax
  BOOL v15; // eax
  BOOL v16; // eax
  BOOL v17; // eax
  BOOL v18; // eax
  BOOL v19; // eax
  BOOL v20; // eax
  BOOL v21; // eax
  BOOL v22; // eax
  BOOL v23; // eax
  BOOL v24; // eax
  BOOL v25; // eax
  BOOL v26; // eax
  BOOL v27; // eax
  BOOL v28; // eax
  BOOL v29; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x54]
  HWND v31; // [esp+0x14] [ebp-0x50]
  HWND v32; // [esp+0x18] [ebp-0x4C]
  HWND v33; // [esp+0x1C] [ebp-0x48]
  HWND v34; // [esp+0x20] [ebp-0x44]
  HWND v35; // [esp+0x24] [ebp-0x40]
  HWND v36; // [esp+0x28] [ebp-0x3C]
  HWND v37; // [esp+0x2C] [ebp-0x38]
  HWND v38; // [esp+0x30] [ebp-0x34]
  HWND v39; // [esp+0x34] [ebp-0x30]
  HWND v40; // [esp+0x38] [ebp-0x2C]
  HWND v41; // [esp+0x3C] [ebp-0x28]
  HWND v42; // [esp+0x40] [ebp-0x24]
  HWND v43; // [esp+0x44] [ebp-0x20]
  HWND v44; // [esp+0x48] [ebp-0x1C]
  HWND v45; // [esp+0x4C] [ebp-0x18]
  HWND v46; // [esp+0x50] [ebp-0x14]
  HWND v47; // [esp+0x54] [ebp-0x10]
  HWND v48; // [esp+0x58] [ebp-0xC]
  HWND v49; // [esp+0x5C] [ebp-0x8]
  HWND v50; // [esp+0x60] [ebp-0x4]

  DlgItem = GetDlgItem((HWND)g_hCombatDlg1, 1116);
  v3 = GetDlgItem((HWND)g_hCombatDlg1, 1117);
  hWnd = GetDlgItem((HWND)g_hCombatDlg1, 1119);
  v31 = GetDlgItem((HWND)g_hCombatDlg1, 1118);
  v32 = GetDlgItem((HWND)g_hCombatDlg1, 1120);
  v33 = GetDlgItem((HWND)g_hCombatDlg1, 1121);
  v34 = GetDlgItem((HWND)g_hCombatDlg1, 1122);
  v35 = GetDlgItem((HWND)g_hCombatDlg1, 1123);
  v36 = GetDlgItem((HWND)g_hCombatDlg1, 1124);
  v37 = GetDlgItem((HWND)g_hCombatDlg1, 1125);
  v38 = GetDlgItem((HWND)g_hCombatDlg1, 1126);
  v39 = GetDlgItem((HWND)g_hCombatDlg1, 1127);
  v40 = GetDlgItem((HWND)g_hCombatDlg1, 1128);
  v41 = GetDlgItem((HWND)g_hCombatDlg1, 1129);
  v42 = GetDlgItem((HWND)g_hCombatDlg1, 1130);
  v43 = GetDlgItem((HWND)g_hCombatDlg1, 1131);
  v44 = GetDlgItem((HWND)g_hCombatDlg1, 1132);
  v45 = GetDlgItem((HWND)g_hCombatDlg1, 1133);
  v46 = GetDlgItem((HWND)g_hCombatDlg1, 1134);
  v47 = GetDlgItem((HWND)g_hCombatDlg1, 1135);
  v48 = GetDlgItem((HWND)g_hCombatDlg1, 1136);
  v49 = GetDlgItem((HWND)g_hCombatDlg1, 1137);
  v50 = GetDlgItem((HWND)g_hCombatDlg1, 1138);
  v4 = GetDlgItem((HWND)g_hCombatDlg1, 1140);
  result = roleIdx;
  if ( roleIdx <= 0xA )
  {
    result = *(_BYTE *)(this->m_fontcolor.Color + 892 * roleIdx + 577);
    if ( result )
    {
      IsModified = EditBoxIsModified(DlgItem);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 3, IsModified, 1);
      v7 = EditBoxIsModified(v3);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 4, v7, 1);
      v8 = EditBoxIsModified(hWnd);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 1, v8, 1);
      v9 = EditBoxIsModified(v31);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 2, v9, 1);
      v10 = EditBoxIsModified(v32);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 5, v10, 1);
      v11 = EditBoxIsModified(v33);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 6, v11, 1);
      v12 = EditBoxIsModified(v34);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 7, v12, 1);
      v13 = EditBoxIsModified(v35);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 8, v13, 1);
      v14 = EditBoxIsModified(v36);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 9, v14, 1);
      v15 = EditBoxIsModified(v37);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 10, v15, 1);
      v16 = EditBoxIsModified(v38);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 11, v16, 1);
      v17 = EditBoxIsModified(v39);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 12, v17, 1);
      v18 = EditBoxIsModified(v40);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 13, v18, 1);
      v19 = EditBoxIsModified(v41);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 14, v19, 1);
      v20 = EditBoxIsModified(v42);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 15, v20, 1);
      v21 = EditBoxIsModified(v43);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 16, v21, 1);
      v22 = EditBoxIsModified(v44);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 17, v22, 1);
      v23 = EditBoxIsModified(v45);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 18, v23, 1);
      v24 = EditBoxIsModified(v46);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 19, v24, 1);
      v25 = EditBoxIsModified(v47);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 20, v25, 1);
      v26 = EditBoxIsModified(v48);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 21, v26, 1);
      v27 = EditBoxIsModified(v49);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 22, v27, 1);
      v28 = EditBoxIsModified(v50);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 23, v28, 1);
      v29 = EditBoxIsModified(v4);
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::ProcessRound(roleIdx, 26, v29, 1);
      result = EndDialog((HWND)g_hCombatDlg1, 0);
      g_hCombatDlg1 = 0;
    }
  }
  return result;
}

// 0x004E5110
int CCBRoleState::GetTargetCommand()
{
  int *TargetRole; // eax
  int result; // eax
  int p_DWORD; // [esp+0x0] [ebp-0x18] BYREF
  int v3; // [esp+0x4] [ebp-0x14]
  int v4; // [esp+0x8] [ebp-0x10]
  char pOut[12]; // [esp+0xC] [ebp-0xC] BYREF

  v3 = 0;
  v4 = 0;
  p_DWORD = 0xFFFF;
  TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
  p_DWORD = (unsigned long)*TargetRole;
  v3 = (unsigned long)TargetRole[1];
  v4 = (unsigned long)TargetRole[2];
  result = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
  LOBYTE(g_bCommandEdited) = 1;
  return result;
}

// 0x004EC680
CCBRoleState * CCBRoleState::ClearAndSetGP(int nVal)
{
  memset(this, 0, 0x50A4u);
  *(_DWORD *)&this->m_pObjMsgBuffer[96] = nVal;
  *(_DWORD *)&this->m_pObjMsgBuffer[104] = *(_DWORD *)(nVal + 4);
  return this;
}

// 0x004EC6B0
int CCBRoleState::ClearRoleMemory()
{
  int result; // eax

  this->m_pObjMsgBuffer[112] = 0;
  this->m_pObjMsgBuffer[113] = 0;
  result = 0;
  memset(&this->m_pObjMsgBuffer[128], 0, 0x2654u);
  memset(this->m_BufferData, 0, 0x2654u);
  memset(&this->m_nEffCurA, 0, 0x24u);
  memset(&this->m_nEffCurC, 0, 0x18u);
  return result;
}

// 0x004EC7D0
char CCBRoleState::IterateMagicSlots()
{
  char *v1; // ebp
  char *v2; // esi
  int v3; // edi
  void ( ***v4)(_DWORD, int); // ecx
  int v6; // [esp+0x10] [ebp-0x4]

  v1 = (char *)&this->m_info.depend_scenename[6];
  v6 = 5;
  do
  {
    v2 = (char *)v1;
    v3 = 3;
    do
    {
      v4 = (void ( ***)(_DWORD, int))*((_DWORD *)v2 - 3);
      if ( v4 )
      {
        (**v4)((_DWORD)((_DWORD)(v4)), (int)(1));
        *((_DWORD *)v2 - 3) = 0;
      }
      if ( *(_DWORD *)v2 )
      {
        (***(void ( ****)(_DWORD, int))v2)((_DWORD)(*(_DWORD *)v2), (int)(1));
        *(_DWORD *)v2 = 0;
      }
      v2 += 4;
      --v3;
    }
    while ( v3 );
    v1 += 892;
    --v6;
  }
  while ( v6 );
  return 1;
}

// 0x004EC830
char CCBRoleState::DestroyAndReinit()
{
  _DWORD *v2; // eax
  int v3; // eax
  char v4; // cl
  int v5; // eax
  int v6; // ecx
  char result; // al

  v2 = (_DWORD *)(*(_DWORD **)&this->m_pObjMsgBuffer[96]);
  *(_DWORD *)&this->m_pObjMsgBuffer[100] = (unsigned long)v2[5];
  *(_DWORD *)&this->m_pObjMsgBuffer[108] = (unsigned long)*v2;
  this->CCBRoleState::Destroy();
  this->CCBRoleState::ClearRoleMemory();
  v3 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
  *(float *)&this->m_pObjMsgBuffer[88] = *(float *)(v3 + 80);
  *(_DWORD *)&this->m_pObjMsgBuffer[120] = 0;
  *(_DWORD *)&this->m_pObjMsgBuffer[116] = *(_DWORD *)(*(_DWORD *)(v3 + 112) + 28);
  v4 = *(_BYTE *)(*(_DWORD *)(v3 + 112) + 72);
  this->m_pObjMsgBuffer[125] = 0;
  this->m_pObjMsgBuffer[124] = v4;
  this->CCBRoleState::ShuffleSlots();
  this->CCBRoleState::LoadPartyData();
  (((PAL_GDB *)this))->PAL_GDB::LoadSkillData();
  this->CCBRoleState::RollInitiative();
  this->CCBRoleState::CCBRoleState();
  this->CCBRoleState::UpdateRolePositions();
  this->CCBRoleState::Create();
  v5 = this->CCBRoleState::CheckDeath(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 112) + 64));
  this->CCBRoleState::SwapEffectParams(v5);
  this->CCBRoleState::SetupCombatLayout();
  v6 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
  this->m_nCurrentTaskID = 0;
  result = 1;
  this->m_fTimeFund = *(float *)(v6 + 80);
  return result;
}

// 0x004EC910
int CCBRoleState::SetupCombatLayout()
{
  int v2; // eax
  int v3; // ebp
  int *i; // ebx
  void (***v5)(_DWORD, _DWORD); // ecx
  int result; // eax
  int v7; // edi
  void ( ***v8)(_DWORD, int); // ecx
  int v9; // ecx
  float fValue; // [esp+0x0] [ebp-0x20]
  float fValuea; // [esp+0x0] [ebp-0x20]
  float fValueb; // [esp+0x0] [ebp-0x20]
  int v13; // [esp+0x14] [ebp-0xC]
  int v14; // [esp+0x18] [ebp-0x8]
  int v15; // [esp+0x1C] [ebp-0x4]

  v2 = 0;
  v15 = 0;
  v3 = 156;
  for ( i = (int *)&this->m_pObjMsgBuffer[168]; ; i += 223 )
  {
    if ( *((_BYTE *)i - 15) )
    {
      *((_BYTE *)i - 16) = v2;
      v7 = v2;
      v15 = v2 + 1;
      fValue = (float)*i;
      (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v2 + 1020)))->UIScrollBar::SetRange(fValue);
      fValuea = (float)i[2];
      (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v7 + 1036)))->UIScrollBar::SetRange(fValuea);
      fValueb = (float)i[4];
      (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v7 + 1052)))->UIScrollBar::SetRange(fValueb);
      this->CCBRoleState::Init(*((unsigned __int8 *)i - 16), 1);
      v8 = *(void ( ****)(_DWORD, int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3 - 20);
      (**v8)((_DWORD)((_DWORD)(v8)), (int)(1));
      (***(void ( ****)(_DWORD, int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3))((_DWORD)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3)), (int)(1));
      result = g_nStatePanelL[v7];
      v9 = g_nStatePanelT[v7];
      v14 = result;
      v13 = v9;
      switch ( v7 )
      {
        case 0:
          MoveToAbsolute(*(_DWORD **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3 - 20), result + 43, v9 + 14);
          result = MoveToAbsolute(*(_DWORD **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3), v14 + 38, v13 + 39);
          break;
        case 1:
        case 2:
          MoveToAbsolute(*(_DWORD **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3 - 20), result + 33, v9 + 15);
          result = MoveToAbsolute(*(_DWORD **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3), v14 + 24, v13 + 41);
          break;
        case 3:
          MoveToAbsolute(*(_DWORD **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3 - 20), result + 33, v9 + 15);
          result = MoveToAbsolute(*(_DWORD **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3), v14 + 23, v13 + 41);
          break;
        default:
          break;
      }
    }
    else
    {
      *((_BYTE *)i - 16) = -1;
      v5 = *(void ( ****)(_DWORD, _DWORD))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3 - 20);
      (**v5)((_DWORD)(v5), (_DWORD)(0));
      result = (***(int ( ****)(_DWORD, _DWORD))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3))((_DWORD)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + v3)), (_DWORD)(0));
    }
    v3 += 4;
    if ( v3 >= 176 )
      return result;
    v2 = v15;
  }
}

// 0x004ECB00
int CCBRoleState::Update()
{
  this->CCBRoleState::CheckStatus();
  this->CCBRoleState::ProcessActions();
  return this->CCBRoleState::UpdateEffects();
}

// 0x004ECB20
char CCBRoleState::ProcessCombatAction(int roleIdx)
{
  CCBSystem *v5; // ecx
  int v6; // eax
  char *v7; // edi
  char v8; // al
  int v9; // eax
  float v10; // st7
  CCBStage *v11; // ecx
  int RoleIndex; // edi
  CCBStage *v13; // ecx
  int v14; // eax
  char *v15; // ecx
  int v16; // eax
  char *i; // ecx
  _DWORD pData[11]; // [esp+0xC] [ebp-0x40] BYREF
  int p_DWORD[2]; // [esp+0x38] [ebp-0x14] BYREF
  int v21; // [esp+0x40] [ebp-0xC]
  int v22; // [esp+0x44] [ebp-0x8]
  char *v23; // [esp+0x48] [ebp-0x4]
  int roleIdxa; // [esp+0x54] [ebp+0x8]
  int roleIdxb; // [esp+0x54] [ebp+0x8]
  float roleIdxc; // [esp+0x54] [ebp+0x8]

  if ( *(_DWORD *)&this->m_pObjMsgBuffer[120] >= *(_DWORD *)&this->m_pObjMsgBuffer[116] )
    return 1;
  v5 = (CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12);
  v6 = *(_DWORD *)&this->m_info.depend_scenename[892 * roleIdx + 18];
  v7 = (char *)this + 892 * roleIdx;
  v23 = (char *)v7;
  roleIdxa = v6;
  if ( v6 < (((CCBSystem *)v5))->CCBSystem::GetCmdValue(roleIdx) )
  {
    *((_DWORD *)v7 + 356) = roleIdxa + 1;
    if ( roleIdx == 10 )
      ++*(_DWORD *)&this->m_pObjMsgBuffer[120];
    this->CCBRoleState::TickDebuffs(roleIdx);
    if ( !v7[1390] )
      goto LABEL_17;
    v8 = v7[1391] + 1;
    v7[1391] = v8;
    if ( (unsigned __int8)v8 >= 4u )
      v7[1390] = 0;
    v9 = this->CCBRoleState::SetRoleField(roleIdx, 1);
    roleIdxb = 0;
    switch ( v7[1391] )
    {
      case 1:
        v10 = (float)-v9 * 0.05000000074505806f;
        break;
      case 2:
        v10 = (float)-v9 * 0.10000000149011612f;
        break;
      case 3:
        v10 = (float)-v9 * 0.15000000596046448f;
        break;
      default:
LABEL_16:
        this->CCBRoleState::AddCommand(roleIdx, roleIdxb, 1);
        this->CCBRoleState::AddCommand(3, -roleIdxb, 1);
LABEL_17:
        if ( *((float *)v7 + 168) > 0.0 && *((_DWORD *)v7 + 147) < *((_DWORD *)v7 + 148) )
          this->CCBRoleState::AddCommand(roleIdx, (__int64)((double)*((int *)v7 + 148) * *((float *)v7 + 168) * 0.0099999998), 1);
        if ( *((float *)v7 + 169) > 0.0 && *((_DWORD *)v7 + 149) < *((_DWORD *)v7 + 150) )
          this->CCBRoleState::CalcAttackPower(roleIdx);
        if ( *((float *)v7 + 170) > 0.0 && *((_DWORD *)v7 + 151) < *((_DWORD *)v7 + 152) )
          this->CCBRoleState::CalcDefensePower(roleIdx);
        if ( roleIdx >= 5 && roleIdx < 11 && *((int *)v7 + 359) > 0 )
        {
          roleIdxc = (float)*((int *)v7 + 359) * 10.239999771118164f;
          v22 = (int)roleIdxc;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
          if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < v22 )
          {
            v7[1431] = 1;
            memset(pData, 0, sizeof(pData));
            v11 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
            pData[2] = roleIdx;
            RoleIndex = (((CCBStage *)v11))->CCBStage::GetRoleIndex(21, pData, 1);
            if ( RoleIndex != -1 )
            {
              v21 = 0;
              p_DWORD[0] = 0;
              p_DWORD[1] = roleIdx;
              v13 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
              v21 = -1;
              (((CCBStage *)v13))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
              (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskMoveToStart) */, 0, 0, 0, p_DWORD, -1082130432, 0);
              (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
              (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
            }
            v7 = (char *)v23;
          }
        }
        if ( *((_DWORD *)v7 + 138) == 7372 && *((_DWORD *)v7 + 356) == 3 )
          this->CCBRoleState::ProcessRound(roleIdx, 6, 1, 1);
        if ( *((_DWORD *)v7 + 138) == 7378 && *((int *)v7 + 356) >= 3 )
        {
          v22 = (int)51.199997;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
          if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)51.199997 )
          {
            v14 = 0;
            v15 = (char *)&this->m_pObjMsgBuffer[154];
            while ( v14 < 5 || *(v15 - 1) && *v15 )
            {
              ++v14;
              v15 += 892;
              if ( v14 >= 11 )
                goto LABEL_46;
            }
            this->CCBRoleState::InitSlot(v14, 7378);
          }
        }
LABEL_46:
        if ( *((_DWORD *)v7 + 138) == 7395 && *((_DWORD *)v7 + 356) == 2 )
        {
          v22 = (int)204.79999;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
          if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)204.79999 )
          {
            v16 = 0;
            for ( i = &this->m_pObjMsgBuffer[153]; v16 < 5 || *i; i += 892 )
            {
              if ( ++v16 >= 11 )
                return 0;
            }
            this->CCBRoleState::InitSlot(v16, 7395);
          }
        }
        return 0;
    }
    roleIdxb = (__int64)v10;
    goto LABEL_16;
  }
  return 0;
}

// 0x004ED010
char CCBRoleState::IsRoleAlive(int roleIdx)
{
  if ( this->m_pObjMsgBuffer[892 * roleIdx + 153] )
    return this->m_pObjMsgBuffer[892 * roleIdx + 154];
  else
    return 0;
}

// 0x004ED040
char CCBRoleState::IsActive(int index)
{
  return this->m_pObjMsgBuffer[892 * index + 155];
}

// 0x004ED060
char CCBRoleState::GetRoleType(int roleIdx)
{
  char *v2; // eax

  v2 = (char *)this + 892 * roleIdx;
  if ( !v2[577] )
    return 0;
  if ( v2[579] == 1 )
    return 0;
  return v2[580];
}

// 0x004ED0A0
char CCBRoleState::ApplyHitEffect(char pData)
{
  int v2; // edx
  int *i; // eax
  int v5; // edx
  char *j; // eax

  if ( pData )
  {
    v2 = 0;
    for ( i = (int *)&this->m_pObjMsgBuffer[164]; !*((_BYTE *)i - 11) || *i <= 0; i += 223 )
    {
      if ( ++v2 >= 5 )
        return 1;
    }
  }
  else
  {
    v5 = 0;
    for ( j = &this->m_pObjMsgBuffer[154]; !*(j - 1) || *j != 1; j += 892 )
    {
      if ( ++v5 >= 5 )
        return 1;
    }
  }
  return 0;
}

// 0x004ED100
int CCBRoleState::GetForce(int roleIdx)
{
  int v2; // edx
  int result; // eax

  v2 = 5;
  if ( (_BYTE)roleIdx )
  {
    result = (int)((SceneObj *)this) + 5048;
    while ( !*(_BYTE *)(result - 11) || *(int *)result <= 0 || *(_BYTE *)(result + 844) )
    {
      ++v2;
      result += 892;
      if ( v2 >= 11 )
      {
        return 1;
      }
    }
  }
  else
  {
    result = (int)((SceneObj *)this) + 5038;
    while ( !*(_BYTE *)(result - 1) || *(_BYTE *)result != 1 || *(_BYTE *)(result + 854) )
    {
      ++v2;
      result += 892;
      if ( v2 >= 11 )
      {
        return 1;
      }
    }
  }
  return 0;
}

// 0x004ED170
char CCBRoleState::ShuffleSlots()
{
  _BYTE *v1; // ebx
  int v2; // eax
  int v3; // ecx
  int v4; // edi
  int v5; // ecx
  int v6; // esi
  int v7; // edx
  int v8; // edx
  _DWORD v10[6]; // [esp+0x4] [ebp-0x18] BYREF

  v1 = (_BYTE *)*(_BYTE **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 112);
  LOBYTE(v2) = (unsigned long)v1[80];
  if ( !(_BYTE)v2 )
  {
    LOBYTE(v2) = (unsigned long)v1[72];
    if ( !(_BYTE)v2 )
    {
      qmemcpy(v10, v1, sizeof(v10));
      v3 = g_nCombatRandSeed;
      v4 = 100;
      do
      {
        v5 = 214013 * v3 + 2531011;
        *(_DWORD *)&g_TempBuffer1024[912] += 2;
        v6 = ((v5 >> 16) & 0x7FFF) % 6;
        v3 = 214013 * v5 + 2531011;
        g_nCombatRandSeed = v3;
        v2 = ((v3 >> 16) & 0x7FFF) / 6;
        v7 = ((v3 >> 16) & 0x7FFF) % 6;
        if ( v6 != v7 )
        {
          v2 = (int)&v10[v7];
          v8 = v10[v6];
          v10[v6] = *(_DWORD *)v2;
          *(_DWORD *)v2 = v8;
          v3 = g_nCombatRandSeed;
        }
        --v4;
      }
      while ( v4 );
      qmemcpy(v1, v10, 0x18u);
    }
  }
  return v2;
}

// 0x004ED250
int CCBRoleState::LoadPartyData()
{
    CCBRoleState *_this = this;
  int v1; // edx
  int v2; // eax
  float *p_z; // ebx
  char *v4; // ebp
  int v5; // eax
  int v6; // esi
  char v7; // al
  int v8; // edi
  int v9; // eax
  int result; // eax
  CCBRoleState *v11; // [esp+0x10] [ebp-0xC]
  unsigned int dwVal; // [esp+0x14] [ebp-0x8]
  int v13; // [esp+0x18] [ebp-0x4]

  v1 = 0;
  v2 = -20;
  v11 = _this;
  dwVal = 0;
  p_z = (float *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z;
  v4 = (char *)&_this->m_pObjMsgBuffer2[4];
  v13 = -20;
  do
  {
    if ( v2 < 0 )
    {
      *(v4 - 105) = 1;
      *(v4 - 104) = 0;
      *(v4 - 101) = 0;
      *((_DWORD *)v4 + 113) = *((unsigned __int8 *)p_z + 666);
      if ( g_RoleSlotBuf.m_partyActor.m_szTexture[10] )
        *(float *)v4 = *(float *)v4 + 20.0;
      if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v1) )
      {
        *(v4 - 107) = 1;
        *(v4 - 106) = 1;
        *((float *)v4 - 33) = *(p_z - 185);
        *((_DWORD *)v4 - 32) = v1;
        *((float *)v4 + 5) = *p_z;
        *((float *)v4 - 25) = *(p_z - 27);
        *((float *)v4 - 23) = p_z[46];
        *((float *)v4 - 21) = p_z[47];
        *((float *)v4 - 19) = p_z[48];
        *((float *)v4 - 24) = p_z[58];
        *((float *)v4 - 22) = p_z[59];
        *((float *)v4 - 20) = p_z[60];
        *((_DWORD *)v4 + 113) = *((unsigned __int8 *)p_z + 666);
        *((float *)v4 - 18) = p_z[49];
        *((float *)v4 - 17) = p_z[50];
        *((float *)v4 - 16) = p_z[51];
        *((float *)v4 - 15) = p_z[52];
        *((_DWORD *)v4 - 13) = *(&g_RoleSlotBuf.dword_17AA450 + 147);
        *((_DWORD *)v4 - 12) = 0;
        *((_DWORD *)v4 - 14) = *(int *)((char *)&g_nRoleInitLevel[5] + v2);
        qmemcpy(v4 + 28, p_z + 73, 0x1Eu);
        qmemcpy(v4 + 60, p_z + 81, 0xC0u);
        qmemcpy(v4 + 252, p_z + 129, 0x30u);
        qmemcpy(v4 + 300, p_z + 141, 0x30u);
        qmemcpy(v4 + 348, p_z + 153, 0x30u);
        v4[705] = *((_BYTE *)p_z + 660);
        v4[700] = *((_BYTE *)p_z + 661);
        v4[701] = *((_BYTE *)p_z + 662);
        v4[704] = *((_BYTE *)p_z + 665);
        v4[702] = *((_BYTE *)p_z + 663);
        v4[703] = *((_BYTE *)p_z + 664);
      }
LABEL_29:
      _this = v11;
      goto LABEL_30;
    }
    *(v4 - 105) = 0;
    if ( v1 > 4 && v1 < 11 )
      *((_DWORD *)v4 + 113) = v1 - 4;
    if ( *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&_this->m_pObjMsgBuffer[96] + 112) + v2) )
    {
      *(v4 - 107) = 1;
      *(v4 - 106) = 1;
      *((_DWORD *)v4 - 32) = v1;
      *((_DWORD *)v4 - 33) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&_this->m_pObjMsgBuffer[96] + 112) + v2);
      *((_DWORD *)v4 + 177) = -1;
      if ( *((_DWORD *)v4 - 33) == 708 )
        *((_BYTE *)((SceneObj *)_this) + 3259) = 1;
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v4 - 33));
      v6 = v5;
      *(v4 - 104) = 0;
      v7 = *(_BYTE *)(v5 + 518);
      if ( v7 == 98 || v7 == 66 )
      {
        *(v4 - 104) = 1;
        v4[483] = 1;
        *((_WORD *)v4 + 295) = 0x7FFF;
      }
      if ( *(_BYTE *)(v6 + 709) )
      {
        v4[483] = 1;
        *((_WORD *)v4 + 295) = 0x7FFF;
      }
      v8 = 0;
      *((_DWORD *)v4 - 23) = *(_DWORD *)(v6 + 636);
      *((_DWORD *)v4 - 21) = *(_DWORD *)(v6 + 640);
      *((_DWORD *)v4 - 19) = *(_DWORD *)(v6 + 644);
      *((_DWORD *)v4 - 24) = *((_DWORD *)v4 - 23);
      *((_DWORD *)v4 - 22) = *((_DWORD *)v4 - 21);
      *((_DWORD *)v4 - 20) = *((_DWORD *)v4 - 19);
      *((_DWORD *)v4 - 25) = *(_DWORD *)(v6 + 632);
      *((_DWORD *)v4 - 18) = *(_DWORD *)(v6 + 648);
      *((_DWORD *)v4 - 17) = *(_DWORD *)(v6 + 652);
      *((_DWORD *)v4 - 16) = *(_DWORD *)(v6 + 656);
      *((_DWORD *)v4 - 15) = *(_DWORD *)(v6 + 660);
      *((_DWORD *)v4 + 5) = *(_DWORD *)(v6 + 740);
      *((_DWORD *)v4 - 11) = *(_DWORD *)(v6 + 748);
      *((_DWORD *)v4 - 10) = *(_DWORD *)(v6 + 780);
      *((_DWORD *)v4 + 103) = *(__int16 *)(v6 + 842);
      *((_DWORD *)v4 + 104) = *(_DWORD *)(v6 + 844);
      *((_DWORD *)v4 + 105) = *(__int16 *)(v6 + 848);
      *((_DWORD *)v4 + 102) = 0;
      v4[746] = *(float *)(v6 + 796) <= 0.0f;
      *((_DWORD *)v4 + 188) = (__int64)*(float *)(v6 + 724);
      v4[748] = 0;
      v4[747] = 0;
      v9 = *((_DWORD *)v4 - 24);
      if ( v9 >= 1000 )
      {
        if ( v9 >= 10000 )
        {
          if ( v9 >= 100000 )
            *((_DWORD *)v4 + 189) = (unsigned long)"??????/??????";
          else
            *((_DWORD *)v4 + 189) = (unsigned long)"?????/?????";
        }
        else
        {
          *((_DWORD *)v4 + 189) = (unsigned long)"????/????";
        }
      }
      else
      {
        *((_DWORD *)v4 + 189) = (unsigned long)"???/???";
      }
      do
      {
        if ( *(_BYTE *)(v6 + v8 + 684) )
          (((CCBRoleState *)v11))->CCBRoleState::ProcessRound(dwVal, v8 + 1, 1, 0);
        ++v8;
      }
      while ( v8 < 23 );
      v2 = v13;
      v1 = dwVal;
      goto LABEL_29;
    }
LABEL_30:
    v2 += 4;
    ++v1;
    p_z += 352;
    v4 += 892;
    dwVal = v1;
    v13 = v2;
  }
  while ( v2 < 24 );
  result = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&_this->m_pObjMsgBuffer[96] + 112) + 76);
  if ( result != -1 )
    _this->m_pObjMsgBuffer[892 * result + 159] = 1;
  return result;
}

// 0x004ED680
char CCBRoleState::SavePartyData()
{
  CCBRoleState *v1; // edi
  int *v2; // esi
  int *p_m_pRoleObj; // ebp
  char *v4; // ebx
  int v5; // esi
  int *v6; // edi
  char result; // al
  int *v8; // [esp+0x10] [ebp-0x8]
v2 = g_nRoleInitLevel;
  v8 = g_nRoleInitLevel;
  p_m_pRoleObj = (int *)&g_RoleSlotBuf.m_partyActor.m_pRoleObj;
  v4 = (char *)&this->m_pObjMsgBuffer2[24];
  do
  {
    if ( *(v4 - 127) )
    {
      p_m_pRoleObj[27] = *(_DWORD *)v4;
      *p_m_pRoleObj = *((_DWORD *)v4 - 30);
      p_m_pRoleObj[85] = *((_DWORD *)v4 - 29);
      p_m_pRoleObj[86] = *((_DWORD *)v4 - 27);
      p_m_pRoleObj[87] = *((_DWORD *)v4 - 25);
      p_m_pRoleObj[88] = *((_DWORD *)v4 - 23);
      p_m_pRoleObj[89] = *((_DWORD *)v4 - 22);
      p_m_pRoleObj[90] = *((_DWORD *)v4 - 21);
      p_m_pRoleObj[91] = *((_DWORD *)v4 - 20);
      (((RoleSystem *)(p_m_pRoleObj - 158)))->RoleSystem::RecalcAggregatedStats(0);
      *v2 = *((_DWORD *)v4 - 19);
      qmemcpy(p_m_pRoleObj + 100, v4 + 8, 0x1Eu);
      qmemcpy(p_m_pRoleObj + 108, v4 + 40, 0xC0u);
      qmemcpy(p_m_pRoleObj + 156, v4 + 232, 0x30u);
      qmemcpy(p_m_pRoleObj + 168, v4 + 280, 0x30u);
      qmemcpy(p_m_pRoleObj + 180, v4 + 328, 0x30u);
v2 = (int *)v8;
      p_m_pRoleObj[99] = *((_DWORD *)v4 + 96);
    }
    ++v2;
    v4 += 892;
    p_m_pRoleObj += 352;
    v8 = (int *)v2;
  }
  while ( (int)v2 < (int)&g_nRoleInitLevel[5] );
  *(&g_RoleSlotBuf.dword_17AA450 + 147) = (((CCBRoleState *)this))->CCBRoleState::GetTotalRounds();
  (((CCBRoleState *)this))->CCBRoleState::UpdateDefenceStats();
  v5 = 0;
  v6 = (int *)&this->m_pObjMsgBuffer[164];
  do
  {
    result = *((_BYTE *)v6 - 11);
    if ( result && v5 >= 5 && *v6 <= 0 )
      result = (((NPC *)(&g_RoleSlotBuf.dword_17AA450 + 134)))->NPC::ShiftBufferData(*(v6 - 9));
    ++v5;
    v6 += 223;
  }
  while ( v5 < 11 );
  return result;
}

// 0x004ED800
char * CCBRoleState::UpdateDefenceStats()
{
  char *result; // eax
  char *p_bottom; // ecx

  result = (char *)&g_RoleSlotBuf.m_nAnimCopy1;
  p_bottom = (char *)&this->m_info.rect.bottom;
  do
  {
    if ( *(p_bottom - 559) )
    {
      result[6] = *p_bottom;
      *result = p_bottom[253];
      result[1] = p_bottom[248];
      result[2] = p_bottom[249];
      result[5] = p_bottom[252];
      result[3] = p_bottom[250];
      result[4] = p_bottom[251];
    }
    result += 1408;
    p_bottom += 892;
  }
  while ( (int)result < (int)&unk_C06498 );
  return result;
}

// 0x004ED870
char CCBRoleState::SyncSkillCent()
{
  int v2; // ebx
  unsigned int *v3; // edi
  char *v4; // esi
  unsigned int v5; // eax

  v2 = 0;
  v3 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
  v4 = (char *)&this->m_pObjMsgBuffer[164];
  do
  {
    LOBYTE(v5) = *(v4 - 11);
    if ( (_BYTE)v5 )
    {
      if ( *(int *)v4 <= 0 )
      {
        *(_DWORD *)v4 = 1;
        this->CCBRoleState::CanUseSkill(v2);
      }
      v5 = *(_DWORD *)v4;
      *v3 = *(_DWORD *)v4;
    }
    v3 += 352;
    ++v2;
    v4 += 892;
  }
  while ( (int)v3 < (int)dword_C062EC );
  return v5;
}

// 0x004EDC60
int CCBRoleState::RollInitiative()
{
  int v1; // eax
  int result; // eax

  v1 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
  this->m_pObjMsgBuffer[113] = 0;
  this->m_pObjMsgBuffer[112] = 0;
  result = *(_DWORD *)(v1 + 112);
  if ( !*(_BYTE *)(result + 80) )
  {
    result = *(_DWORD *)(result + 68);
    if ( result == 1 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
      result = ((int)g_nCombatRandSeed >> 16) & 0x3FF;
      if ( result < (int)512.0 )
        this->m_pObjMsgBuffer[113] = 1;
    }
    else if ( result == 2 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
      result = ((int)g_nCombatRandSeed >> 16) & 0x3FF;
      if ( result < (int)512.0 )
        this->m_pObjMsgBuffer[112] = 1;
    }
  }
  return result;
}

// 0x004EDD60
CCBRoleState::CCBRoleState()
{
  float *p_y; // ebp
  void **p_m_pSelfAtt; // esi
  float *v3; // ebx
  int v4; // eax
  float *v5; // ecx
  int v6; // eax
  float *v7; // ecx
  int v8; // edx
  int v9; // eax
  float *v10; // ecx
  int v11; // edx
  int v12; // eax
  float *v13; // ecx
  int v14; // edx
  int v15; // eax
  float *v16; // ecx
  int v17; // edx
  int v18; // eax
  float *v19; // ecx
  int v20; // edx
  int v21; // edi
  int v22; // eax
  int v23; // ebp
  int v24; // eax
  int v25; // ecx
  int *v26; // [esp+0x10] [ebp-0x8]
  float *v27; // [esp+0x14] [ebp-0x4]

  p_y = (float *)&this->m_info.pos.y;
  p_m_pSelfAtt = (void **)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt;
  v27 = (float *)&this->m_info.pos.y;
  do
  {
    v3 = (float *)(p_y - 1);
    if ( *((_BYTE *)p_y - 535) )
    {
      memset(v3, 0, 0x1Cu);
      if ( (int)p_m_pSelfAtt < (int)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt || (int)p_m_pSelfAtt >= (int)&dword_C062B8 )
      {
        v21 = 580;
        v26 = (int *)p_y;
        do
        {
          (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v3 - 139));
          v23 = *(_DWORD *)(v22 + v21) << 16;
          (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v3 - 139));
          v25 = *(_DWORD *)(v24 + v21);
          v21 += 4;
          *v26++ = v25 | v23;
        }
        while ( v21 < 600 );
        p_y = (float *)v27;
      }
      else
      {
        if ( *(p_m_pSelfAtt - 2) )
        {
          v4 = 0;
          v5 = (float *)p_y;
          do
            *((_DWORD *)++v5 - 1) = *((unsigned __int8 *)*p_m_pSelfAtt + v4++ + 619) << 16;
          while ( v4 < 5 );
        }
        if ( *(p_m_pSelfAtt - 17) )
        {
          v6 = 0;
          v7 = (float *)p_y;
          do
          {
            v8 = *((unsigned __int8 *)*(p_m_pSelfAtt - 15) + v6++ + 619) + *((_DWORD *)++v7 - 1);
            *((_DWORD *)v7 - 1) = v8;
          }
          while ( v6 < 5 );
        }
        if ( *(p_m_pSelfAtt - 14) )
        {
          v9 = 0;
          v10 = (float *)p_y;
          do
          {
            v11 = *((unsigned __int8 *)*(p_m_pSelfAtt - 12) + v9++ + 619) + *((_DWORD *)++v10 - 1);
            *((_DWORD *)v10 - 1) = v11;
          }
          while ( v9 < 5 );
        }
        if ( *(p_m_pSelfAtt - 11) )
        {
          v12 = 0;
          v13 = (float *)p_y;
          do
          {
            v14 = *((unsigned __int8 *)*(p_m_pSelfAtt - 9) + v12 + 619) + *((_DWORD *)++v13 - 1);
            ++v12;
            *((_DWORD *)v13 - 1) = v14;
          }
          while ( v12 < 5 );
        }
        if ( *(p_m_pSelfAtt - 8) )
        {
          v15 = 0;
          v16 = (float *)p_y;
          do
          {
            v17 = *((unsigned __int8 *)*(p_m_pSelfAtt - 6) + v15++ + 619) + *((_DWORD *)++v16 - 1);
            *((_DWORD *)v16 - 1) = v17;
          }
          while ( v15 < 5 );
        }
        if ( *(p_m_pSelfAtt - 5) )
        {
          v18 = 0;
          v19 = (float *)p_y;
          do
          {
            v20 = *((unsigned __int8 *)*(p_m_pSelfAtt - 3) + v18++ + 619) + *((_DWORD *)++v19 - 1);
            *((_DWORD *)v19 - 1) = v20;
          }
          while ( v18 < 5 );
        }
      }
    }
    p_m_pSelfAtt += 352;
    p_y += 223;
    v27 = (float *)p_y;
  }
  while ( (int)p_m_pSelfAtt < (int)&unk_C08160.m_partyActor.m_fInterpEnd );
}

// 0x004EDF10
char CCBRoleState::UpdateRolePositions()
{
  int v2; // ebp
  RoleAtt **m_pEquipAtt1; // edi
  char *v4; // esi
  char result; // al

  v2 = 0;
  m_pEquipAtt1 = (RoleAtt **)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1;
  v4 = (char *)&this->m_pObjMsgBuffer[232];
  do
  {
    result = *(v4 - 79);
    if ( result )
    {
      if ( *(m_pEquipAtt1 - 5) )
      {
        *(float *)v4 = (double)SLOWORD((*(m_pEquipAtt1 - 3))->skill[2]) + *(float *)v4;
        *((float *)v4 + 1) = (double)SHIWORD((*(m_pEquipAtt1 - 3))->skill[2]) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)SHIWORD((*(m_pEquipAtt1 - 3))->skill[3]) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)SLOWORD((*(m_pEquipAtt1 - 3))->skill[3]) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)SLOWORD((*(m_pEquipAtt1 - 3))->rolevalue[2]) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)SHIWORD((*(m_pEquipAtt1 - 3))->rolevalue[2]) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)SLOWORD((*(m_pEquipAtt1 - 3))->rolevalue[3]) + *((float *)v4 + 6);
        if ( HIWORD((*(m_pEquipAtt1 - 3))->NormalAtkID) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->CCBRoleState::Reset(v2, (char *)(unsigned __int8)(*(m_pEquipAtt1 - 3))->name[28]);
      }
      if ( *(m_pEquipAtt1 - 2) )
      {
        *(float *)v4 = (double)SLOWORD((*m_pEquipAtt1)->skill[2]) + *(float *)v4;
        *((float *)v4 + 1) = (double)SHIWORD((*m_pEquipAtt1)->skill[2]) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)SHIWORD((*m_pEquipAtt1)->skill[3]) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)SLOWORD((*m_pEquipAtt1)->skill[3]) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)SLOWORD((*m_pEquipAtt1)->rolevalue[2]) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)SHIWORD((*m_pEquipAtt1)->rolevalue[2]) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)SLOWORD((*m_pEquipAtt1)->rolevalue[3]) + *((float *)v4 + 6);
        if ( HIWORD((*m_pEquipAtt1)->NormalAtkID) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->CCBRoleState::Reset(v2, (char *)(unsigned __int8)(*m_pEquipAtt1)->name[28]);
      }
      if ( m_pEquipAtt1[1] )
      {
        *(float *)v4 = (double)SLOWORD(m_pEquipAtt1[3]->skill[2]) + *(float *)v4;
        *((float *)v4 + 1) = (double)SHIWORD(m_pEquipAtt1[3]->skill[2]) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)SHIWORD(m_pEquipAtt1[3]->skill[3]) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)SLOWORD(m_pEquipAtt1[3]->skill[3]) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)SLOWORD(m_pEquipAtt1[3]->rolevalue[2]) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)SHIWORD(m_pEquipAtt1[3]->rolevalue[2]) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)SLOWORD(m_pEquipAtt1[3]->rolevalue[3]) + *((float *)v4 + 6);
        if ( HIWORD(m_pEquipAtt1[3]->NormalAtkID) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->CCBRoleState::Reset(v2, (char *)(unsigned __int8)m_pEquipAtt1[3]->name[28]);
      }
      if ( m_pEquipAtt1[4] )
      {
        *(float *)v4 = (double)SLOWORD(m_pEquipAtt1[6]->skill[2]) + *(float *)v4;
        *((float *)v4 + 1) = (double)SHIWORD(m_pEquipAtt1[6]->skill[2]) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)SHIWORD(m_pEquipAtt1[6]->skill[3]) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)SLOWORD(m_pEquipAtt1[6]->skill[3]) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)SLOWORD(m_pEquipAtt1[6]->rolevalue[2]) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)SHIWORD(m_pEquipAtt1[6]->rolevalue[2]) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)SLOWORD(m_pEquipAtt1[6]->rolevalue[3]) + *((float *)v4 + 6);
        if ( HIWORD(m_pEquipAtt1[6]->NormalAtkID) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->CCBRoleState::Reset(v2, (char *)(unsigned __int8)m_pEquipAtt1[6]->name[28]);
      }
      if ( m_pEquipAtt1[7] )
      {
        *(float *)v4 = (double)SLOWORD(m_pEquipAtt1[9]->skill[2]) + *(float *)v4;
        *((float *)v4 + 1) = (double)SHIWORD(m_pEquipAtt1[9]->skill[2]) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)SHIWORD(m_pEquipAtt1[9]->skill[3]) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)SLOWORD(m_pEquipAtt1[9]->skill[3]) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)SLOWORD(m_pEquipAtt1[9]->rolevalue[2]) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)SHIWORD(m_pEquipAtt1[9]->rolevalue[2]) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)SLOWORD(m_pEquipAtt1[9]->rolevalue[3]) + *((float *)v4 + 6);
        if ( HIWORD(m_pEquipAtt1[9]->NormalAtkID) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->CCBRoleState::Reset(v2, (char *)(unsigned __int8)m_pEquipAtt1[9]->name[28]);
      }
      if ( *(m_pEquipAtt1 - 5) == (RoleAtt *)80015 )
      {
        if ( *(m_pEquipAtt1 - 2) == (RoleAtt *)84018
          && m_pEquipAtt1[1] == (RoleAtt *)83012
          && m_pEquipAtt1[4] == (RoleAtt *)8153
          && m_pEquipAtt1[7] == (RoleAtt *)8154 )
        {
          v4[44] = 1;
        }
        if ( *(m_pEquipAtt1 - 5) == (RoleAtt *)80015
          && *(m_pEquipAtt1 - 2) == (RoleAtt *)84018
          && m_pEquipAtt1[1] == (RoleAtt *)83012
          && m_pEquipAtt1[4] == (RoleAtt *)8154
          && m_pEquipAtt1[7] == (RoleAtt *)8153 )
        {
          v4[44] = 1;
        }
      }
      result = -82;
      if ( m_pEquipAtt1[4] == (RoleAtt *)8110 || m_pEquipAtt1[7] == (RoleAtt *)8110 )
        v4[45] = 1;
    }
    m_pEquipAtt1 += 352;
    ++v2;
    v4 += 892;
  }
  while ( (int)m_pEquipAtt1 < (int)&unk_C06288 );
  return result;
}

// 0x004EE430
char * CCBRoleState::Reset(int nVal, char *pszBuf)
{
  char *result; // eax
  float *v4; // edx

  switch ( (unsigned int)pszBuf )
  {
    case 0x14u:
      result = (char *)&this->m_pObjMsgBuffer2[892 * nVal + 4];
      *(float *)result = *(float *)result + 5.0;
      break;
    case 0x15u:
      v4 = (float *)((char *)this + 892 * nVal);
      v4[171] = v4[171] + 15.0;
      v4[172] = v4[172] + 5.0;
      goto LABEL_4;
    case 0x16u:
LABEL_4:
      result = (char *)&this->m_pObjMsgBuffer2[892 * nVal + 12];
      *(float *)result = *(float *)result + 10.0;
      break;
    case 0x17u:
      result = (char *)&this->m_pObjMsgBuffer2[892 * nVal + 16];
      *(_DWORD *)result += 5;
      break;
    case 0x18u:
      result = (char *)&this->m_pObjMsgBuffer2[892 * nVal + 4];
      *(float *)result = *(float *)result + 20.0;
      break;
    default:
      result = (char *)pszBuf;
      break;
  }
  return result;
}

// 0x004EE540
bool CCBRoleState::Create()
{
  void **p_m_pSelfAtt; // ebp
  gbGeomNode **p_z; // edi
  int v3; // eax
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // esi
  gbGeomNode *v6; // ecx
  gbGeomNode *v7; // eax
  gbGeomNode *v8; // esi
  gbGeomNode *v9; // ecx
  char Buffer[256]; // [esp+0x14] [ebp-0x120C] BYREF
  char v12[256]; // [esp+0x114] [ebp-0x110C] BYREF
  _BYTE pExceptionObject[1024]; // [esp+0x214] [ebp-0x100C] BYREF
  char v14[1024]; // [esp+0x614] [ebp-C0Ch] BYREF
  char ArgList; // [esp+A14h] [ebp-0x80C] BYREF
  char v16; // [esp+E14h] [ebp-0x40C] BYREF
  int v17; // [esp+0x121C] [ebp-0x4]

  p_m_pSelfAtt = (void **)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt;
  p_z = (gbGeomNode **)&this->m_info.path.pt[15].z;
  do
  {
    LOBYTE(v3) = *((_BYTE *)p_z - 823);
    if ( (_BYTE)v3 )
    {
      v3 = (int)*(p_m_pSelfAtt - 2);
      if ( v3 )
      {
        sprintf(Buffer, "weapon\\%s\\%s.pol", (const char *)*p_m_pSelfAtt + 36, (const char *)*p_m_pSelfAtt + 36);
        sprintf(
          v12,
          "weapon\\%s\\%s%s.tga",
          (const char *)*p_m_pSelfAtt + 36,
          (const char *)*p_m_pSelfAtt + 36,
          (const char *)*p_m_pSelfAtt + 66);
        v4 = (gbGeomNode *)operator new(0x118u);
        v5 = (gbGeomNode *)v4;
        v17 = 0;
        if ( v4 )
        {
          v4->gbGeomNode::gbGeomNode();
          v6 = (gbGeomNode *)v5;
        }
        else
        {
          v6 = 0;
        }
        v17 = -1;
        *p_z = v6;
        if ( !v6 )
        {
          qmemcpy(
            pExceptionObject,
            (((Logger *)&ArgList))->Logger::FormatException(aFailToCreateWe, "D:\\Project\\PAL3\\combat\\EffCylinder.cpp", 1484),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        (((gbGeomNode *)v6))->gbGeomNode::LoadFromFile(Buffer, 0, 0);
        (((gbGeomNode *)*p_z))->gbGeomNode::ReplaceTexture(v12);
        v7 = (gbGeomNode *)operator new(0x118u);
        v8 = (gbGeomNode *)v7;
        v17 = 1;
        if ( v7 )
        {
          v7->gbGeomNode::gbGeomNode();
          v9 = (gbGeomNode *)v8;
        }
        else
        {
          v9 = 0;
        }
        v17 = -1;
        p_z[3] = v9;
        if ( !v9 )
        {
          qmemcpy(v14, (((Logger *)&v16))->Logger::FormatException(aFailToCreateWe, "D:\\Project\\PAL3\\combat\\EffCylinder.cpp", 1494), sizeof(v14));
          _CxxThrowException(v14, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        (((gbGeomNode *)v9))->gbGeomNode::LoadFromFile(Buffer, 0, 0);
        (((gbGeomNode *)p_z[3]))->gbGeomNode::ReplaceTexture(v12);
        LOBYTE(v3) = 1;
        (*p_z)->bBlade = 1;
        p_z[3]->bBlade = 1;
      }
    }
    p_m_pSelfAtt += 352;
    p_z += 223;
  }
  while ( (int)p_m_pSelfAtt < (int)&dword_C062B8 );
  return v3;
}

// 0x004EE760
bool CCBRoleState::Destroy()
{
  char *v1; // ebp
  char *v2; // esi
  int v3; // edi
  void ( ***v4)(_DWORD, int); // ecx
  bool result; // al
  int v6; // [esp+0x10] [ebp-0x4]

  v1 = (char *)&this->m_info.depend_scenename[6];
  v6 = 5;
  do
  {
    v2 = (char *)v1;
    v3 = 3;
    do
    {
      v4 = (void ( ***)(_DWORD, int))*((_DWORD *)v2 - 3);
      if ( v4 )
      {
        (**v4)((_DWORD)((_DWORD)(v4)), (int)(1));
        *((_DWORD *)v2 - 3) = 0;
      }
      if ( *(_DWORD *)v2 )
      {
        (***(void ( ****)(_DWORD, int))v2)((_DWORD)(*(_DWORD *)v2), (int)(1));
        *(_DWORD *)v2 = 0;
      }
      v2 += 4;
      --v3;
    }
    while ( v3 );
    v1 += 892;
    result = --v6;
  }
  while ( v6 );
  return result;
}

// 0x004EE7C0
bool CCBRoleState::Init(int nVal, char pData)
{
  int v3; // esi

  v3 = *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 4);
  if ( pData == 1 )
  {
    if ( !nVal )
      (***(void ( ****)(_DWORD, int))(v3 + 1068))((_DWORD)(*(_DWORD *)(v3 + 1068)), (int)(1));
    (***(void ( ****)(_DWORD, int))(v3 + 4 * nVal + 120))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 120)), (int)(1));
    (***(void ( ****)(_DWORD, int))(v3 + 4 * nVal + 1020))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 1020)), (int)(1));
    (***(void ( ****)(_DWORD, int))(v3 + 4 * nVal + 1052))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 1052)), (int)(1));
    return (***(int ( ****)(_DWORD, int))(v3 + 4 * nVal + 1036))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 1036)), (int)(1));
  }
  else
  {
    if ( !nVal )
      (***(void ( ****)(_DWORD, _DWORD))(v3 + 1068))((_DWORD)(*(_DWORD *)(v3 + 1068)), (_DWORD)(0));
    (***(void ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 120))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 120)), (_DWORD)(0));
    (***(void ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 1020))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 1020)), (_DWORD)(0));
    (***(void ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 1052))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 1052)), (_DWORD)(0));
    return (***(int ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 1036))((_DWORD)(*(_DWORD *)(v3 + 4 * nVal + 1036)), (_DWORD)(0));
  }
}

// 0x004EE870
tagRoleState * CCBRoleState::InitUI(int nVal)
{
  return (tagRoleState *)&this->m_pObjMsgBuffer[892 * nVal + 128];
}

// 0x004EE890
int CCBRoleState::UpdateRoleMP(int roleIdx)
{
  this->CCBRoleState::GetRoleMP(roleIdx);
  return 0;
}

// 0x004EE910
int CCBRoleState::CheckRoleMP(int roleIdx)
{
  this->CCBRoleState::GetRoleMP(roleIdx);
  return -1;
}

// 0x004EE990
bool CCBRoleState::VarianceRoundCounter(int *nRoleIndex)
{
  int RoleNum; // eax
  unsigned __int8 v5; // al
  int *nRoleIndexa; // [esp+0x14] [ebp+0x8]
  float nRoleIndexb; // [esp+0x14] [ebp+0x8]

  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nRoleIndex[1]);
  if ( *nRoleIndex == 261 )
    return 1;
  v5 = *(_BYTE *)(RoleNum + 616);
  if ( v5 <= 1u )
  {
    nRoleIndexa = (int *)this->CCBRoleState::ApplyDamage(1, nRoleIndex[2]);
    if ( (int)nRoleIndexa > 0 )
    {
      nRoleIndexb = (float)(int)nRoleIndexa * 10.239999771118164f;
      ++*(_DWORD *)&g_TempBuffer1024[912];
      g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
      return (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)nRoleIndexb;
    }
  }
  else if ( v5 == 100 )
  {
    return 1;
  }
  return 0;
}

// 0x004EEA70
void CCBRoleState::CheckVarianceRound(int nRoleIndex, int nVal, int *pnVal)
{
  int v4; // edi
  signed int v5; // esi
  char v6; // bl
  int RoleBySlot; // eax
  int v8; // eax
  int v9; // edi
  _DWORD *v10; // ebp
  int v11; // ecx
  char *v12; // esi
  unsigned __int8 v13; // cl
  bool v14; // zf
  int v15; // edx
  int v16; // ecx
  int *v17; // edi
  int v18; // ebp
  int v19; // esi
  int v20; // eax
  signed int v22; // [esp+0x14] [ebp-0x8]
  int ItemNum; // [esp+0x18] [ebp-0x4]

  v4 = nRoleIndex;
  if ( nRoleIndex >= 5 && nRoleIndex < 11 )
    return;
  v5 = 0;
  ItemNum = GDB_GetItemNum((PAL_GDB *)&g_pGDB);
  v22 = 0;
  if ( ItemNum <= 0 )
    return;
  do
  {
    v6 = 1;
    RoleBySlot = (((UIAnimateCtrl *)&g_pGDB))->UIAnimateCtrl::GetRoleBySlot(v5);
    *pnVal = RoleBySlot;
    v8 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(RoleBySlot);
    if ( *(_DWORD *)(v8 + 56) != nVal )
      goto LABEL_53;
    if ( *(_DWORD *)(v8 + 36) != *(_DWORD *)&this->m_pObjMsgBuffer[892 * v4 + 128] )
      goto LABEL_52;
    v9 = 0;
    v10 = (_DWORD *)(v8 + 36);
    do
    {
      if ( !*v10 )
        goto LABEL_33;
      v11 = -1;
      switch ( *v10 )
      {
        case 'e':
          v11 = 0;
          break;
        case 'f':
          v11 = 4;
          break;
        case 'h':
          v11 = 1;
          break;
        case 'i':
        case 'j':
          v11 = 2;
          break;
        case 'k':
          v11 = 3;
          break;
        default:
          break;
      }
      v12 = (char *)this + 892 * v11;
      if ( !v12[577] )
        v6 = 0;
      v13 = *(_BYTE *)(v8 + v9 + 52);
      if ( v13 )
      {
        v14 = v13 == 7;
        if ( v13 >= 7u )
          goto LABEL_21;
        if ( v13 != v12[1136] )
          v6 = 0;
      }
      v14 = v13 == 7;
LABEL_21:
      if ( v14 )
      {
        v15 = *((_DWORD *)v12 + 284);
        if ( v15 != 3 && v15 != 2 && v15 != 4 )
          v6 = 0;
      }
      if ( v13 == 8 )
      {
        v16 = *((_DWORD *)v12 + 284);
        if ( v16 != 1 && v16 != 2 && v16 != 5 )
          v6 = 0;
      }
      if ( *(_BYTE *)(v8 + v9 + 60) != v12[648] )
        v6 = 0;
LABEL_33:
      ++v9;
      ++v10;
    }
    while ( v9 < 4 );
    if ( v6 )
    {
      v17 = (int *)(v8 + 68);
      v18 = 3;
      do
      {
        switch ( *(v17 - 7) )
        {
          case 'e':
            v19 = 0;
            goto LABEL_42;
          case 'f':
            v19 = 4;
            goto LABEL_42;
          case 'h':
            v19 = 1;
            goto LABEL_42;
          case 'i':
          case 'j':
            v19 = 2;
            goto LABEL_42;
          case 'k':
            v19 = 3;
LABEL_42:
            v20 = (unsigned long)*v17;
            if ( *v17 >= 0 && v20 < 26 && !this->CCBRoleState::GetRoleField(v19, v20 + 1) )
              v6 = 0;
            if ( *v17 == 26 && !this->CCBRoleState::IsRoleInForce(v19) )
              v6 = 0;
            break;
          default:
            break;
        }
        ++v17;
        --v18;
      }
      while ( v18 );
      if ( v6 )
        break;
    }
    v5 = v22;
LABEL_52:
    v4 = nRoleIndex;
LABEL_53:
    v22 = ++v5;
  }
  while ( v5 < ItemNum );
}

// 0x004EECB0
void CCBRoleState::CancelVariance(int *nRoleIndex, unsigned int dwVal)
{
  char *v3; // eax

  if ( dwVal <= 0xA )
  {
    v3 = (char *)this + 892 * dwVal;
    if ( v3[577] )
    {
      if ( v3[578] && !v3[1432] && !v3[1431] && (v3[1164] != 1 || nRoleIndex[1] == 4401) && *nRoleIndex == 259 )
        this->CCBRoleState::CalSneakAttack(nRoleIndex[2], dwVal);
    }
  }
}

// 0x004EED60
char CCBRoleState::ForceRoleTaskByCond(int roleIdx)
{
  int v3; // eax
  char result; // al
  int v5; // esi
  int v6; // esi

  v3 = *(_DWORD *)&this->m_pObjMsgBuffer[212];
  if ( !v3 )
    return 0;
  if ( v3 != roleIdx )
    return 0;
  result = this->CCBRoleState::IsRoleAlive(0);
  if ( result )
  {
    v5 = this->CCBRoleState::SetRoleField(0, 1) / 2;
    if ( this->CCBRoleState::SetRoleField(0, 0) >= v5 )
    {
      v6 = this->CCBRoleState::SetRoleField(roleIdx, 1) / 10;
      if ( this->CCBRoleState::SetRoleField(roleIdx, 0) <= v6 )
      {
        if ( this->m_info.rect.bottom == 6 )
        {
          result = (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 24)))->CCBStage::ForceDelTaskByPFN();
          if ( result )
          {
            result = (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 24)))->CCBStage::ForceEndTaskByPFN();
            if ( result )
              return (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * roleIdx + 24)))->CCBStage::ForceEndTaskByPFN();
          }
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004EEE60
char CCBRoleState::IsAlive(int nIndex, int nVal)
{
  char result; // al
  int v5; // eax

  if ( !this->m_pObjMsgBuffer[153] )
    return 0;
  v5 = *(_DWORD *)&this->m_pObjMsgBuffer[212];
  if ( !v5 )
    return 0;
  if ( v5 != nIndex )
    return 0;
  result = this->CCBRoleState::IsRoleAlive(0);
  if ( result )
  {
    if ( this->m_info.rect.bottom == 6 )
    {
      if ( this->CCBRoleState::GetRoleField(0, 14) )
      {
        return 0;
      }
      else
      {
        result = (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 24)))->CCBStage::MoveToAbsolute(nIndex, nVal);
        if ( result )
        {
          result = (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * nIndex + 24)))->CCBStage::ForceEndTaskByPFN();
          if ( result )
            return (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::ForceDelTask(18);
        }
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004EEF20
int CCBRoleState::CalcCombatDamage(const void *pData, unsigned int roleIdx)
{
  int v3; // ebx
  CCBRoleState *v4; // ecx
  int v6; // edi
  CCBRoleState *v7; // kr10_4
  int v8; // eax
  __int16 v9; // ax
  int v10; // edx
  __int16 v11; // ax
  int v12; // eax
  __int16 v13; // ax
  char *v14; // eax
  int v15; // ebx
  CScreenMode *Instance; // eax
  char *v18; // [esp+0x4] [ebp-0x58]
  int nCmdData[11]; // [esp+0xC] [ebp-0x50] BYREF
  int v20; // [esp+0x38] [ebp-0x24]
  int v21; // [esp+0x3C] [ebp-0x20]
  int SkillNum; // [esp+0x40] [ebp-0x1C]
  int ItemNum; // [esp+0x44] [ebp-0x18]
  int RoleNum; // [esp+0x48] [ebp-0x14]
  char v25[4]; // [esp+0x4C] [ebp-0x10]
  int v26; // [esp+0x50] [ebp-0xC]
  CCBRoleState *v27; // [esp+0x54] [ebp-0x8]
  char v28; // [esp+0x5B] [ebp-0x1]
  char pData_3; // [esp+0x67] [ebp+0xB]
  float roleIdxb; // [esp+0x68] [ebp+0xC]
  signed int roleIdxa; // [esp+0x68] [ebp+0xC]
  float roleIdxc; // [esp+0x68] [ebp+0xC]
v3 = 0;
  qmemcpy(nCmdData, pData, sizeof(nCmdData));
  v26 = 0;
  *(_DWORD *)v25 = 0;
  RoleNum = 0;
  SkillNum = 0;
  ItemNum = 0;
  switch ( nCmdData[0] )
  {
    case 0x104:
    case 0x105:
    case 0x10D:
      RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nCmdData[1]);
      break;
    case 0x106:
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nCmdData[1]);
      break;
    case 0x10E:
      ItemNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(nCmdData[1]);
      break;
    default:
      v4 = 0;
      break;
  }
  v28 = 0;
  pData_3 = 0;
  v6 = 0;
  while ( 2 )
  {
    v7 = (CCBRoleState *)v4;
    v4 = 0;
    switch ( nCmdData[0] )
    {
      case 0x104:
        v9 = *(_WORD *)(RoleNum + 2 * v6 + 592);
        if ( v9 )
        {
          v3 = v9;
          if ( (int)roleIdx >= 5 && (int)roleIdx < 11 )
          {
            if ( (_BYTE)unk_5DFDEB )
            {
              roleIdxb = (float)v9 * 0.10000000149011612f;
              v21 = (int)roleIdxb;
              roleIdxa = abs32(v21);
              if ( roleIdxa )
              {
                v10 = (((int)(214013 * g_nCombatRandSeed + 2531011) >> 16) & 0x7FFF) % roleIdxa;
                *(_DWORD *)&g_TempBuffer1024[912] += 2;
                g_nCombatRandSeed = 214013 * (214013 * g_nCombatRandSeed + 2531011) + 2531011;
                v4 = (CCBRoleState *)(((int)g_nCombatRandSeed >> 16) & 0x3FF);
                if ( (unsigned int)v4 < 0x200 )
                  v3 = v9 - v10;
                else
                  v3 = v10 + v9;
              }
            }
          }
          if ( !BYTE1(nCmdData[4]) && roleIdx <= 4 )
            *(_DWORD *)v25 = 1;
          if ( nCmdData[1] == 4102 )
          {
            v4 = (CCBRoleState *)v27;
            v3 = 2 * *(_DWORD *)&this->m_pObjMsgBuffer[160] + 40;
          }
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x105:
        if ( *(_WORD *)(RoleNum + 2 * v6 + 592) )
        {
          v8 = (((CCBRoleState *)this))->CCBRoleState::ApplyDamage(2, nCmdData[2]);
          v4 = (CCBRoleState *)RoleNum;
          v3 = v8;
          *(_DWORD *)v25 = *(unsigned __int8 *)(RoleNum + v6 + 579);
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x106:
        v4 = (CCBRoleState *)SkillNum;
        v13 = *(_WORD *)(SkillNum + 2 * v6 + 644);
        if ( v13 )
        {
          v3 = v13;
          if ( v13 > 0 && nCmdData[2] <= 4u )
          {
            roleIdxc = (float)v13 * *(float *)&this->m_pObjMsgBuffer2[892 * nCmdData[2] + 12] * 0.009999999776482582f;
            v20 = (int)roleIdxc;
            v3 = v20 + v13;
          }
          *(_DWORD *)v25 = *(unsigned __int8 *)(SkillNum + v6 + 631);
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x10D:
        v11 = *(_WORD *)(RoleNum + 2 * v6 + 592);
        if ( v11 )
        {
          if ( roleIdx <= 4 )
            *(_DWORD *)v25 = 1;
          v3 = v11;
          if ( nCmdData[1] == 2224 )
            v3 = (__int64)(((double)dword_C10CC4 * 0.5 + 1.0) * (double)v11);
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x10E:
        v4 = (CCBRoleState *)ItemNum;
        if ( *(_WORD *)(ItemNum + 2 * v6 + 606) )
        {
          v12 = (((CCBRoleState *)this))->CCBRoleState::ApplyItemEffect((int)nCmdData, roleIdx);
          v4 = (CCBRoleState *)ItemNum;
          if ( *(__int16 *)(ItemNum + 2 * v6 + 606) <= 0 )
            v3 = (v12 >> 31) - ((v12 >> 31) ^ v12);
          else
            v3 = abs32(v12);
          goto LABEL_36;
        }
        goto LABEL_67;
      default:
        v4 = (CCBRoleState *)v7;
LABEL_36:
        if ( v6 )
        {
          if ( v6 == 1 )
          {
            if ( *(_DWORD *)v25 > 2u )
              goto LABEL_67;
            if ( *(_DWORD *)v25 == 1 )
            {
              (((CCBRoleState *)this))->CCBRoleState::GetRoleGPBak(roleIdx, 1);
              v3 = (((CCBRoleState *)this))->CCBRoleState::CalcAttackPower(roleIdx);
            }
            else
            {
              if ( *(_DWORD *)v25 == 2 )
              {
                (((CCBRoleState *)this))->CCBRoleState::GetRoleGPBak(roleIdx, 1);
                (((CCBRoleState *)this))->CCBRoleState::GetRoleGPBak(roleIdx, 0);
              }
              v3 = (((CCBRoleState *)this))->CCBRoleState::CalcAttackPower(roleIdx);
            }
            goto LABEL_66;
          }
          if ( v6 != 2 )
          {
            (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::CreateUIObj(&dword_5D8E98, 0, 0x40u);
            goto LABEL_67;
          }
          if ( *(int *)v25 >= 0 )
          {
            if ( *(int *)v25 <= 2 )
            {
              if ( *(_DWORD *)v25 == 1 )
              {
                (((CCBRoleState *)this))->CCBRoleState::GetRole(roleIdx);
              }
              else if ( *(_DWORD *)v25 == 2 )
              {
                (((CCBRoleState *)this))->CCBRoleState::GetRole(roleIdx);
                (((CCBRoleState *)this))->CCBRoleState::GetRole(roleIdx);
              }
              v3 = (((CCBRoleState *)this))->CCBRoleState::CalcDefensePower(roleIdx);
              if ( v3 > 0 )
                pData_3 = 1;
LABEL_66:
              v26 = v3;
              goto LABEL_67;
            }
            if ( *(_DWORD *)v25 == 3 )
            {
              v14 = (char *)&this->m_pObjMsgBuffer[892 * roleIdx + 184];
              v4 = (CCBRoleState *)(v3 + *(_DWORD *)v14);
              *(_DWORD *)v14 = (_DWORD)v4;
            }
          }
        }
        else
        {
          if ( *(int *)v25 < 0 )
            goto LABEL_67;
          if ( *(int *)v25 <= 2 )
          {
            if ( *(_DWORD *)v25 == 1 )
            {
              v3 = v3 * (((CCBRoleState *)this))->CCBRoleState::SetRoleField(roleIdx, 1) / 100;
            }
            else if ( *(_DWORD *)v25 == 2 )
            {
              v15 = (((CCBRoleState *)this))->CCBRoleState::SetRoleField(roleIdx, 1);
              v3 = v15 - (((CCBRoleState *)this))->CCBRoleState::SetRoleField(roleIdx, 0);
            }
            v3 = (((CCBRoleState *)this))->CCBRoleState::AddCommand(roleIdx, v3, 1);
            if ( v3 > 0 )
              v28 = 1;
            goto LABEL_66;
          }
          if ( *(_DWORD *)v25 == 3 )
          {
            v26 = 0;
            v4 = (CCBRoleState *)(v3 + *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 168]);
            *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 168] = (_DWORD)v4;
          }
        }
LABEL_67:
        if ( ++v6 < 12 )
          continue;
        if ( v28 )
        {
          if ( pData_3 )
            v18 = (char *)"wd003";
          else
            v18 = (char *)"wd001";
LABEL_74:
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v18, 1);
        }
        else if ( pData_3 )
        {
          v18 = (char *)"wd002";
          goto LABEL_74;
        }
        return v26;
    }
  }
}

// 0x004EF4A0
void CCBRoleState::IsBoss(int *arg0, unsigned int nRoleIndex)
{
  int RoleNum; // edi
  int SkillNum; // ebp
  int v5; // esi
  __int16 *v6; // ebx
  __int16 *v7; // ebp
  int v8; // eax
  int v9; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  char v17; // [esp+0x12] [ebp-0xA]
  char v18; // [esp+0x13] [ebp-0x9]
  char v19; // [esp+0x14] [ebp-0x8]
  char v20; // [esp+0x15] [ebp-0x7]
  char v21; // [esp+0x16] [ebp-0x6]
  char v22; // [esp+0x17] [ebp-0x5]

  RoleNum = 0;
  SkillNum = 0;
  if ( *arg0 == 262 )
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(arg0[1]);
  else
    RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(arg0[1]);
  v5 = 0;
  v6 = (__int16 *)(RoleNum + 618);
  v22 = 0;
  v17 = 0;
  v18 = 0;
  v19 = 0;
  v20 = 0;
  v21 = 0;
  v7 = (__int16 *)(SkillNum + 700);
  do
  {
    if ( *arg0 == 262 )
      v8 = (unsigned long)*v7;
    else
      v8 = (unsigned long)*v6;
    v9 = v8 - 1;
    if ( v9 )
    {
      if ( v9 == 1 )
      {
        this->CCBRoleState::ProcessRound(nRoleIndex, v5 + 1, 0, 1);
        switch ( v5 )
        {
          case 13:
            v22 = 1;
            break;
          case 14:
            v17 = 1;
            break;
          case 15:
            v18 = 1;
            break;
          case 16:
            v19 = 1;
            break;
          case 17:
            v21 = 1;
            break;
          case 18:
            v20 = 1;
            break;
          default:
            break;
        }
      }
    }
    else
    {
      this->CCBRoleState::ProcessRound(nRoleIndex, v5 + 1, 1, 1);
    }
    ++v5;
    ++v7;
    ++v6;
  }
  while ( v5 < 25 );
  if ( v22 )
  {
    if ( v17 && v18 && v19 && v20 && v21 )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wd019", 1);
      return;
    }
    v11 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v11))->CScreenMode::AudioSetPosition("wd017", 1);
  }
  if ( v17 )
  {
    v12 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v12))->CScreenMode::AudioSetPosition("wd017", 1);
  }
  if ( v18 )
  {
    v13 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v13))->CScreenMode::AudioSetPosition("wd017", 1);
  }
  if ( v19 )
  {
    v14 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v14))->CScreenMode::AudioSetPosition("wd018", 1);
  }
  if ( v20 )
  {
    v15 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v15))->CScreenMode::AudioSetPosition("wd018", 1);
  }
  if ( v21 )
  {
    v16 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v16))->CScreenMode::AudioSetPosition("wd018", 1);
  }
}

// 0x004EF6A0
bool CCBRoleState::IsAllWeDead(int bCheckHP)
{
  return *(&this->m_info.rect.bottom + 223 * bCheckHP);
}

// 0x004EF6C0
int * CCBRoleState::IsAllEnemyDead(int bCheckHP, int *pnVal, int *pnVal2)
{
  int RoleNum; // eax
  int v5; // ecx
  int *result; // eax

  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(bCheckHP);
  v5 = 1;
  result = (int *)(RoleNum + 8);
  *pnVal2 = 0;
  *pnVal = 0;
  do
  {
    if ( *result == 1 )
    {
      if ( *pnVal )
        *pnVal2 = v5;
      else
        *pnVal = v5;
    }
    ++result;
    ++v5;
  }
  while ( v5 - 1 <= 4 );
  return result;
}

// 0x004EF710
bool CCBRoleState::CanAction(int nIndex, int nVal, int nVal2)
{
  int v5; // eax
  float *i; // ecx
  int v7; // edi
  float *j; // eax
  int v9; // ebp

  v5 = 1;
  for ( i = &this->m_info.pos.y + 223 * nVal; !*(_DWORD *)i; ++i )
  {
    if ( ++v5 >= 6 )
      return 0;
  }
  v7 = 1;
  for ( j = &this->m_info.pos.y + 223 * nIndex; (*(_DWORD *)j & 0xFFFF0000) == 0; ++j )
  {
    if ( ++v7 >= 6 )
      return 0;
  }
  v9 = this->CCBRoleState::CheckDeath(v7);
  return (*((_DWORD *)&this->m_info.pos.x + 223 * nVal + v9) != 0)
       - (*((_DWORD *)&this->m_info.pos.x + 223 * nVal + this->CCBRoleState::GetSlotType(v7)) != 0);
}

// 0x004EF7E0
void CCBRoleState::SetCanAction(unsigned int dmg, int roleIdx, int nVal)
{
  int v5; // eax
  int v6; // ecx

  if ( this->CCBRoleState::GetRoleField(roleIdx, 21) != 1 && this->CCBRoleState::GetRoleField(roleIdx, 23) != 1 )
  {
    v5 = this->CCBRoleState::ApplyDamage(7, dmg);
    if ( dmg <= 4 )
    {
      v6 = *(_DWORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * dmg) + 764);
      if ( v6 > 1 )
        v5 /= v6;
    }
    if ( LOBYTE(this->m_info.param[223 * dmg + 4]) )
      v5 *= 2;
    if ( v5 >= 0 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    }
  }
}

// 0x004EF8B0
void CCBRoleState::RandSetEnemyPos(const void *arg0)
{
  struct tagCmdData nVal; // [esp+0x8] [ebp-0x2C] BYREF

  qmemcpy(&nVal, arg0, sizeof(nVal));
  switch ( nVal.dwCmdKind )
  {
    case 0x103u:
      this->CCBRoleState::CalcCombatDamage((int)&nVal);
      break;
    case 0x104u:
      this->CCBRoleState::GetDeadRoleNumInForce((int *)&nVal);
      break;
    case 0x105u:
      this->CCBRoleState::GetAliveRoleNumInForce(&nVal);
      break;
    case 0x106u:
      this->CCBRoleState::GetCastFightSkillSuccess((int)&nVal);
      break;
    case 0x10Du:
      this->CCBRoleState::SetCoAttack((unsigned int)&nVal);
      break;
    case 0x10Eu:
      (((CCBSystem *)this))->CCBSystem::ValidateThreadAction((int)&nVal);
      break;
    default:
      return;
  }
}

// 0x004EF980
int CCBRoleState::CalcHealAmount(int roleIdx)
{
  int RoleHP; // eax
  char *v4; // eax
  int result; // eax
  int v6; // [esp+0xC] [ebp-0xC]

  *(_DWORD *)(roleIdx + 29) = 0;
  *(_DWORD *)(roleIdx + 33) = 0;
  *(_WORD *)(roleIdx + 37) = 0;
  *(_BYTE *)(roleIdx + 39) = 0;
  RoleHP = this->CCBRoleState::GetRoleHP(*(_DWORD *)(roleIdx + 12));
  this->CCBRoleState::GetRoleMP(RoleHP);
  v4 = (char *)this + 892 * *(_DWORD *)(roleIdx + 8);
  if ( v4[651] )
  {
    v6 = 1;
  }
  else if ( v4[649] )
  {
    v6 = 2;
  }
  else
  {
    v6 = (unsigned long)v4[650] != 0 ? 3 : 0;
  }
  result = v6;
  if ( v6 )
  {
    *(_BYTE *)(roleIdx + 17) = 1;
    *(_DWORD *)(roleIdx + 12) = -1;
  }
  else
  {
    *(_BYTE *)(roleIdx + 17) = 0;
  }
  return result;
}

// 0x004EFAF0
void CCBRoleState::WriteBackRoleData(int nVal, int *p_DWORD, int *pnVal)
{
  int *v4; // edi
  int v5; // ebx
  char v6; // dl
  int v7; // eax
  int *p_roleIdx; // esi
  char v9; // al
  int v10; // edi
  int v11; // esi
  int roleIdx; // [esp+0x10] [ebp-0x2C] BYREF
  int v13; // [esp+0x14] [ebp-0x28]

  v4 = (int *)pnVal;
  *pnVal = -1;
  *p_DWORD = -1;
  if ( *(_BYTE *)(nVal + 17) )
  {
    v5 = 0;
    v6 = 0;
    v7 = 0;
    p_roleIdx = (int *)&roleIdx;
    do
    {
      if ( *(_BYTE *)(nVal + v7 + 29) )
      {
        *p_roleIdx = v7;
        ++v5;
        ++p_roleIdx;
        if ( (unsigned int)v7 <= 4 )
        {
          v4 = (int *)pnVal;
          v6 = 1;
        }
      }
      ++v7;
    }
    while ( v7 < 11 );
    if ( v5 != 1 )
    {
      if ( v6 )
      {
        v10 = v13;
        v11 = roleIdx;
        if ( this->CCBRoleState::WriteBackConfig(roleIdx, v13) && v5 == 2 )
        {
          *p_DWORD = v11;
          *pnVal = v10;
        }
      }
      else if ( *(_BYTE *)(nVal + 37) && *(_BYTE *)(nVal + 38) )
      {
        *p_DWORD = 8;
        *v4 = 9;
      }
      else
      {
        v9 = *(_BYTE *)(nVal + 34);
        if ( (!v9
           || (!*(_BYTE *)(nVal + 39) || !*(_BYTE *)(nVal + 36)) && (*(_BYTE *)(nVal + 39) || !*(_BYTE *)(nVal + 36)))
          && (!*(_BYTE *)(nVal + 35) || *(_BYTE *)(nVal + 39)) )
        {
          if ( v9 )
          {
            if ( *(_BYTE *)(nVal + 39) )
            {
              if ( !*(_BYTE *)(nVal + 36) )
              {
                *p_DWORD = 5;
                *v4 = 10;
              }
            }
          }
          else if ( *(_BYTE *)(nVal + 39) && *(_BYTE *)(nVal + 36) )
          {
            *p_DWORD = 10;
            *v4 = 7;
          }
        }
      }
    }
  }
}

// 0x004EFD70
bool CCBRoleState::WriteBackConfig(int roleIdx, int nVal)
{
  int RoleHP; // ebp
  int v7; // eax
  bool result; // al
  int v9; // ecx
  int *p_m_nEffCurA; // eax
  int v11; // edx
  int v12; // eax
  int *i; // ecx
  int v14; // [esp+0x10] [ebp-0x4]
  int roleIdxa; // [esp+0x18] [ebp+0x4]
  int nVala; // [esp+0x1C] [ebp+0x8]

  v14 = -1;
  RoleHP = this->CCBRoleState::GetRoleHP(roleIdx);
  v7 = this->CCBRoleState::GetRoleHP(nVal);
  roleIdxa = *(&this->m_info.rect.bottom + 223 * roleIdx);
  nVala = *(&this->m_info.rect.bottom + 223 * nVal);
  if ( roleIdx == nVal )
    return 1;
  if ( RoleHP != v7 )
    return 0;
  if ( RoleHP == 2 )
  {
    switch ( roleIdx )
    {
      case 5:
      case 7:
      case 10:
        return nVal == 5 || nVal == 10 || nVal == 7;
      case 8:
      case 9:
        if ( nVal != 9 && nVal != 8 )
          return 0;
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    v9 = 0;
    p_m_nEffCurA = (int *)&this->m_nEffCurA;
    do
    {
      v11 = 3;
      do
      {
        if ( *p_m_nEffCurA == roleIdxa )
          v14 = v9;
        ++p_m_nEffCurA;
        --v11;
      }
      while ( v11 );
      ++v9;
    }
    while ( v9 < 3 );
    v12 = 0;
    for ( i = &this->m_nEffCurA + 3 * v14; *i != nVala; ++i )
    {
      if ( ++v12 >= 3 )
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004EFE90
bool CCBRoleState::ReviveAllFriendAtEnd(int roleIdx, int nVal)
{
  int RoleHP; // ebp
  int v7; // eax
  bool result; // al
  int v9; // ecx
  int *p_m_nEffCurC; // eax
  int v11; // edx
  int v12; // eax
  int *i; // ecx
  int v14; // [esp+0x10] [ebp-0x4]
  int roleIdxa; // [esp+0x18] [ebp+0x4]
  int nVala; // [esp+0x1C] [ebp+0x8]

  v14 = -1;
  RoleHP = this->CCBRoleState::GetRoleHP(roleIdx);
  v7 = this->CCBRoleState::GetRoleHP(nVal);
  roleIdxa = *(&this->m_info.rect.bottom + 223 * roleIdx);
  nVala = *(&this->m_info.rect.bottom + 223 * nVal);
  if ( roleIdx == nVal )
    return 1;
  if ( RoleHP != v7 )
    return 0;
  if ( RoleHP == 2 )
  {
    switch ( roleIdx )
    {
      case 5:
      case 8:
        if ( nVal != 8 && nVal != 5 )
          return 0;
        result = 1;
        break;
      case 6:
      case 10:
        if ( nVal != 10 && nVal != 6 )
          return 0;
        result = 1;
        break;
      case 7:
      case 9:
        return nVal == 9 || nVal == 7;
      default:
        return 0;
    }
  }
  else
  {
    v9 = 0;
    p_m_nEffCurC = (int *)&this->m_nEffCurC;
    do
    {
      v11 = 2;
      do
      {
        if ( *p_m_nEffCurC == roleIdxa )
          v14 = v9;
        ++p_m_nEffCurC;
        --v11;
      }
      while ( v11 );
      ++v9;
    }
    while ( v9 < 3 );
    v12 = 0;
    for ( i = &this->m_nEffCurC + 2 * v14; *i != nVala; ++i )
    {
      if ( ++v12 >= 2 )
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004EFFC0
bool CCBRoleState::IsRoleReady(int roleIdx)
{
  int *v2; // eax

  v2 = (int *)((char *)this + 892 * roleIdx);
  return *((_BYTE *)v2 + 577)
      && !*((_BYTE *)v2 + 1432)
      && !*((_BYTE *)v2 + 1431)
      && v2[147] > 0
      && this->CCBRoleState::GetRoleField(roleIdx, 23) == 0;
}

// 0x004F0020
void CCBRoleState::SetEnemyBeImbibeNimbus(char pData, char pData2)
{
  int v4; // ebp
  int v5; // esi
  int v6; // ebp
  int v7; // edi
  int v8; // esi
  _DWORD v9[9]; // [esp+0x14] [ebp-0x24] BYREF

  memset(v9, 0xFFu, sizeof(v9));
  if ( pData2 )
  {
    if ( pData )
    {
      v4 = 0;
      if ( this->CCBRoleState::IsRoleReady(8) )
      {
        v9[0] = 8;
        v4 = 1;
      }
      if ( this->CCBRoleState::IsRoleReady(9) )
        v9[v4] = 9;
      v5 = 0;
      if ( this->CCBRoleState::IsRoleReady(5) )
      {
        v9[3] = 5;
        v5 = 1;
      }
      if ( this->CCBRoleState::IsRoleReady(10) )
        v9[v5++ + 3] = 10;
      if ( this->CCBRoleState::IsRoleReady(7) )
        v9[v5 + 3] = 7;
      this->CCBRoleState::IsRoleReady(6);
    }
    else
    {
      v6 = 0;
      if ( this->CCBRoleState::IsRoleReady(5) )
      {
        v9[0] = 5;
        v6 = 1;
      }
      if ( this->CCBRoleState::IsRoleReady(8) )
        v9[v6] = 8;
      v7 = 0;
      if ( this->CCBRoleState::IsRoleReady(6) )
      {
        v9[3] = 6;
        v7 = 1;
      }
      if ( this->CCBRoleState::IsRoleReady(10) )
        v9[v7 + 3] = 10;
      v8 = 0;
      if ( this->CCBRoleState::IsRoleReady(7) )
      {
        v9[6] = 7;
        v8 = 1;
      }
      if ( this->CCBRoleState::IsRoleReady(9) )
        v9[v8 + 6] = 9;
    }
  }
}

// 0x004F0210
bool CCBRoleState::CalSneakAttack(int nVal, unsigned int dwVal)
{
  signed int v4; // esi
  int v5; // ebx
  char *v6; // esi

  if ( nVal < 5 || nVal >= 11 )
  {
LABEL_14:
    v4 = dwVal;
  }
  else
  {
    v4 = dwVal;
    if ( dwVal <= 4 )
    {
      if ( this->m_pObjMsgBuffer[892 * nVal + 226] || this->m_pObjMsgBuffer[892 * nVal + 227] )
        return 1;
      if ( *(&this->m_info.rect.bottom + 223 * dwVal) == this->CCBRoleState::CheckDeath(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96]
                                                                                 + 112)
                                                                     + 64)) )
      {
        v5 = 0;
        v6 = (char *)&this->m_info.depend_scenename[26];
        while ( !*(v6 - 855)
             || *v6
             || *(v6 - 1)
             || *((_DWORD *)v6 - 74) != 6
             || this->CCBRoleState::SetRoleField(v5, 0) <= 0 )
        {
          ++v5;
          v6 += 892;
          if ( v5 >= 5 )
            goto LABEL_14;
        }
        return 0;
      }
    }
  }
  return (unsigned int)nVal > 4
      || v4 < 5
      || v4 >= 11
      || this->m_pObjMsgBuffer[892 * nVal + 226]
      || this->m_pObjMsgBuffer[892 * nVal + 227]
      || v4 != 6
      || !*(&this->m_byteFlags + 1821)
      || this->m_nTodo_2870
      || *(&this->m_byteFlags + 2675)
      || this->CCBRoleState::SetRoleField(10, 0) <= 0;
}

// 0x004F0360
unsigned int CCBRoleState::InitRoleFiveMagic(int nVal)
{
  unsigned int result; // eax

  result = *(unsigned __int8 *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(*(_DWORD *)(nVal + 4)) + 592);
  switch ( result )
  {
    case 0u:
      goto LABEL_12;
    case 1u:
      this->CCBRoleState::GetRoleMP(1);
      *(_BYTE *)(nVal + 17) = 1;
      *(_DWORD *)(nVal + 29) = 0;
      *(_DWORD *)(nVal + 33) = 0;
      *(_WORD *)(nVal + 37) = 0;
      *(_BYTE *)(nVal + 39) = 0;
      result = 0;
      goto LABEL_14;
    case 2u:
      result = *(_DWORD *)(nVal + 12);
      if ( result <= 4 )
      {
        this->CCBRoleState::GetRoleMP(2);
        result = *(_DWORD *)(nVal + 12);
        if ( result <= 4 )
        {
          result = 0;
          *(_DWORD *)(nVal + 12) = 0;
        }
      }
      if ( *(_DWORD *)(nVal + 12) != -1 )
        goto LABEL_12;
      result = 0;
      break;
    case 3u:
      this->CCBRoleState::GetRoleMP(2);
      *(_BYTE *)(nVal + 17) = 1;
      *(_DWORD *)(nVal + 29) = 0;
      *(_DWORD *)(nVal + 33) = 0;
      *(_WORD *)(nVal + 37) = 0;
      *(_BYTE *)(nVal + 39) = 0;
      result = 0;
LABEL_14:
      *(_DWORD *)(nVal + 12) = -1;
      return result;
    default:
      return result;
  }
  while ( !*(_BYTE *)(result + nVal + 29) )
  {
    if ( (int)++result >= 11 )
    {
      *(_BYTE *)(nVal + 17) = 0;
      return result;
    }
  }
  *(_DWORD *)(nVal + 12) = result;
LABEL_12:
  *(_BYTE *)(nVal + 17) = 0;
  return result;
}

// 0x004F05A0
char CCBRoleState::IsAllyTargetCmd(int *p_DWORD)
{
  char v2; // al
  char result; // al
  char v4; // al

  switch ( *p_DWORD )
  {
    case 260:
    case 261:
    case 269:
      v2 = *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(p_DWORD[1]) + 577);
      goto LABEL_4;
    case 262:
      v2 = *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_DWORD[1]) + 629);
LABEL_4:
      if ( v2 != 2 && v2 != 4 )
        goto LABEL_10;
      result = 1;
      break;
    case 270:
      v4 = *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(p_DWORD[1]) + 592);
      if ( v4 != 1 && v4 != 3 )
        goto LABEL_10;
      result = 1;
      break;
    default:
LABEL_10:
      result = 0;
      break;
  }
  return result;
}

// 0x004F0640
void CCBRoleState::InitRoleSpecEquipAttrib(int nRoleIndex)
{
  int v2; // edx
  char *v3; // eax

  if ( *(_DWORD *)(nRoleIndex + 12) > 0xAu )
  {
    v2 = 0;
    v3 = (char *)&this->m_pObjMsgBuffer[164];
    do
    {
      if ( *(_BYTE *)(nRoleIndex + v2 + 29) && *(v3 - 11) && *(int *)v3 > 0 && !v3[844] )
        break;
      ++v2;
      v3 += 892;
    }
    while ( v2 < 11 );
  }
}

// 0x004F0700
void CCBRoleState::UnloadWeaponModel(int nVal)
{
  int v2; // esi
  LONG *p_bottom; // edi

  v2 = 0;
  p_bottom = (LONG *)&this->m_info.rect.bottom;
  do
  {
    if ( *((_BYTE *)p_bottom - 559) && *p_bottom == nVal && !(((CCBRoleState *)v2))->CCBRoleState::SetVisible() )
      break;
    ++v2;
    p_bottom += 223;
  }
  while ( v2 < 5 );
}

// 0x004F0750
bool CCBRoleState::SetVisible(int nPanelIndex)
{
  CCBRoleState *v1; // ecx
  CCBRoleState *v2; // edi

  v2 = (CCBRoleState *)v1;
  if ( !v1->m_pObjMsgBuffer[892 * nPanelIndex + 154] )
    return 0;
  if ( (((CCBRoleState *)v1))->CCBRoleState::GetRoleField(nPanelIndex, 14) )
    return 0;
  if ( (((CCBRoleState *)v2))->CCBRoleState::GetRoleField(nPanelIndex, 18) )
    return 0;
  if ( (((CCBRoleState *)v2))->CCBRoleState::GetRoleField(nPanelIndex, 19) )
    return 0;
  return (((CCBRoleState *)v2))->CCBRoleState::GetRoleField(nPanelIndex, 17) == 0;
}

// 0x004F07D0
char CCBRoleState::IsRoleIndexEqual(int nIndex, int nVal)
{
  switch ( nIndex )
  {
    case 1:
      if ( nVal == 1 )
        return 1;
      break;
    case 2:
      if ( nVal == 2 )
        return 1;
      break;
    case 4:
      if ( nVal == 4 )
        return 1;
      break;
    case 3:
      if ( nVal == 3 )
        return 1;
      break;
    default:
      if ( nIndex == 5 && nVal == 5 )
        return 1;
      break;
  }
  return 0;
}

// 0x004F0830
unsigned __int8 CCBRoleState::GetRoleNum(int *pnVal)
{
  int v2; // eax
  int SkillNum; // ebp
  unsigned __int8 result; // al
  int RoleHP; // eax
  int RoleNum; // ebp

  v2 = (unsigned long)*pnVal;
  if ( *pnVal == 261 || v2 == 260 || v2 == 269 )
  {
    RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pnVal[1]);
    result = *(_BYTE *)(RoleNum + 577);
    if ( result && result <= 4u )
    {
      if ( result != 1 && result != 3 )
      {
        RoleHP = this->CCBRoleState::GetRoleHP(pnVal[2]);
        if ( *(_BYTE *)(RoleNum + 577) > 2u )
          RoleHP = this->CCBRoleState::IsForce1(RoleHP);
        goto LABEL_10;
      }
      goto LABEL_18;
    }
  }
  else
  {
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(pnVal[1]);
    result = *(_BYTE *)(SkillNum + 629);
    if ( result && result <= 4u )
    {
      if ( result != 1 && result != 3 )
      {
        RoleHP = this->CCBRoleState::GetRoleHP(pnVal[2]);
        if ( *(_BYTE *)(SkillNum + 629) > 2u )
          RoleHP = this->CCBRoleState::IsForce1(RoleHP);
LABEL_10:
        this->CCBRoleState::GetRoleMP(RoleHP);
        result = 0;
        *((_BYTE *)pnVal + 17) = 1;
        return result;
      }
LABEL_18:
      *((_BYTE *)pnVal + 17) = 0;
      return result;
    }
  }
  return (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::CreateUIObj(&dword_5D8EC8, 0, 0x40u);
}

// 0x004F0A10
char CCBRoleState::CalcCombatDamage(int nVal)
{
  unsigned int v3; // ebx
  int v4; // edx
  unsigned int v5; // edi
  bool v6; // al
  BOOL v7; // eax
  int v8; // eax
  int *v9; // edx
  int v10; // eax
  int *v11; // edx
  CCBStage *v12; // ecx
  int RoleIndex; // eax
  int v14; // ebx
  bool v15; // cc
  CCBStage *v17; // ecx
  bool v18; // zf
  void *v19; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x80] BYREF
  int v21; // [esp+0x38] [ebp-0x54]
  int nVal2; // [esp+0x44] [ebp-0x48]
  int p_DWORD[3]; // [esp+0x50] [ebp-0x3C] BYREF
  int v24; // [esp+0x5C] [ebp-0x30]
  int v25; // [esp+0x60] [ebp-0x2C]
  int v26; // [esp+0x64] [ebp-0x28]
  int v27; // [esp+0x68] [ebp-0x24]
  int v28; // [esp+0x6C] [ebp-0x20]
  unsigned int v29; // [esp+0x70] [ebp-0x1C]
  float v30; // [esp+0x74] [ebp-0x18]
  char *v31; // [esp+0x78] [ebp-0x14]
  unsigned int nRoleIndex; // [esp+0x7C] [ebp-0x10]
  BOOL bImmediate; // [esp+0x80] [ebp-0xC]
  int v34; // [esp+0x84] [ebp-0x8]
  bool v35; // [esp+0x8A] [ebp-0x2]
  bool v36; // [esp+0x8B] [ebp-0x1]

  memset(pData, 0, sizeof(pData));
  memset(p_DWORD, 0, sizeof(p_DWORD));
  LOBYTE(pData[10]) = 1;
  v3 = *(_DWORD *)(nVal + 8);
  pData[3] = -1;
  pData[0] = 259;
  v29 = v3;
  v30 = _pal3_coerce_f32(this->CCBRoleState::ApplyDamage(6, v3));
  if ( SLODWORD(v30) > 0 )
  {
    v30 = (float)SLODWORD(v30) * 10.239999771118164f;
    v31 = (char *)(int)v30;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    v36 = (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)v31;
  }
  else
  {
    v36 = 0;
  }
  v4 = 24;
  v5 = 0;
  v34 = 24;
  v31 = (char *)&this->m_pObjMsgBuffer2[21];
  do
  {
    if ( *(_BYTE *)(nVal + 17) )
    {
      if ( !*(_BYTE *)(v5 + nVal + 29) )
        goto LABEL_53;
    }
    else if ( *(_DWORD *)(nVal + 12) != v5 )
    {
      goto LABEL_53;
    }
    if ( (((CCBStage *)*(CCBStage **)(v4 + *(_DWORD *)&this->m_pObjMsgBuffer[100])))->CCBStage::ForceEndTaskByPFN()
      && this->CCBRoleState::IsRoleAlive(v5) == 1
      && !this->CCBRoleState::GetRoleField(v5, 21) )
    {
      if ( v34 < 44 || v34 >= 68 )
      {
        *(float *)&nRoleIndex = _pal3_coerce_f32(this->CCBRoleState::ApplyDamage(5, v3));
        if ( (int)nRoleIndex > 0 )
        {
          *(float *)&nRoleIndex = (double)(int)nRoleIndex * 10.24;
          v28 = (int)*(float *)&nRoleIndex;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
          v6 = (((int)g_nCombatRandSeed >> 16) & 0x3FF) < v28;
        }
        else
        {
          v6 = 0;
        }
      }
      else
      {
        v6 = 0;
      }
      v35 = v6;
      if ( this->CCBRoleState::GetRoleField(v5, 20)
        || this->CCBRoleState::GetRoleField(v5, 14)
        || this->CCBRoleState::GetRoleField(v5, 17) )
      {
        v35 = 0;
      }
      this->CCBRoleState::SetCanAction(v3, v5, 0);
      bImmediate = v7;
      if ( !v35 && v7 < 0 )
      {
        if ( v36 )
        {
          *(float *)&nRoleIndex = (double)bImmediate * 1.3;
          LODWORD(v30) = (int)*(float *)&nRoleIndex;
          *(float *)&nRoleIndex = (double)SLODWORD(v30)
                                * *(float *)&this->m_pObjMsgBuffer[892 * v3 + 240]
                                * 0.0099999998;
          v27 = (int)*(float *)&nRoleIndex;
          bImmediate = LODWORD(v30) + v27;
        }
        if ( this->CCBRoleState::GetRoleField(v5, 20)
          || (v26 = 1109645066,
              v25 = (int)40.959999,
              ++*(_DWORD *)&g_TempBuffer1024[912],
              g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011,
              (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)40.959999)
          && *v31 )
        {
          this->CCBRoleState::AddCommand(v3, bImmediate, 0);
          goto LABEL_53;
        }
        nRoleIndex = v5;
        if ( v34 >= 24 && v34 < 44 && this->CCBRoleState::IsAlive(v5, v3) )
        {
          this->CCBRoleState::AddCommand(0, bImmediate, 1);
          *(float *)&nRoleIndex = 0.0;
          this->CCBRoleState::CanUseSkill(v5);
          if ( v36 )
          {
            v8 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
            v9 = (int *)(*(_DWORD *)(*(_DWORD *)(v8 + 20) + 24) + 6584);
            nVal2 = (unsigned long)*v9;
            (((CEffMgr *)*(CEffMgr **)(v8 + 44)))->CEffMgr::Init(470, nVal2, v9[1], v9[2], 0);
          }
          if ( v34 >= 24 && v34 < 44 )
            goto LABEL_45;
        }
        else
        {
          if ( bImmediate < 0
            && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdEmpty(v5)
            && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdReady(v5) )
          {
            (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdString(v5);
          }
          if ( v36 )
          {
            v10 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
            v11 = (int *)(*(_DWORD *)(*(_DWORD *)(v10 + 20) + v34) + 6584);
            v21 = (unsigned long)*v11;
            (((CEffMgr *)*(CEffMgr **)(v10 + 44)))->CEffMgr::Init(470, v21, v11[1], v11[2], 0);
          }
          this->CCBRoleState::AddCommand(v5, bImmediate, 1);
          if ( v34 >= 24 && v34 < 44 )
LABEL_45:
            this->CCBRoleState::CalcAttackPower(v5);
        }
        this->CCBRoleState::CanBeImbibeNimbus(v3, nRoleIndex);
        this->CCBRoleState::ValidateSlotIndex(v3, nRoleIndex);
        bImmediate = *(BOOL *)&this->m_pObjMsgBuffer2[892 * v3 + 16];
        if ( bImmediate > 0 )
        {
          *(float *)&bImmediate = (double)bImmediate * 10.24;
          v24 = (int)*(float *)&bImmediate;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
          if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < v24 )
            this->CCBRoleState::GetFirstAliveRoleInForce(v3, nRoleIndex);
        }
        goto LABEL_53;
      }
      v12 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
      pData[2] = v5;
      RoleIndex = (((CCBStage *)v12))->CCBStage::GetRoleIndex(5, pData, 1);
      v14 = RoleIndex;
      if ( RoleIndex != -1 )
      {
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0x4FEEF0, 0, 0, 0, p_DWORD, -1082130432, 0);
        this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v14, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::SelectRole) */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v14);
      }
      v3 = v29;
    }
    else if ( this->CCBRoleState::IsRoleAlive(v5) || this->CCBRoleState::GetRoleField(v5, 21) )
    {
      v17 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
      pData[2] = v5;
      *(float *)&nRoleIndex = _pal3_coerce_f32((((CCBStage *)v17))->CCBStage::GetRoleIndex(7, pData, 1));
      if ( *(float *)&nRoleIndex != NAN )
      {
        this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
        v18 = this->CCBRoleState::GetRoleField(v5, 21) == 0;
        *(int (CCBStage::**)(int))&(v19) = CCBStage::GetRoleTaskNum;
        if ( v18 )
          *(void (CCBStage::**)(int))&(v19) = CCBStage::SelectRole;
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(nRoleIndex, (int)v19, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(nRoleIndex);
      }
    }
LABEL_53:
    v4 = v34 + 4;
    ++v5;
    v15 = v34 + 4 < 68;
    v34 += 4;
    v31 += 892;
  }
  while ( v15 );
  return 1;
}

// 0x004F1070
char CCBRoleState::GetAliveRoleNumInForce(tagCmdData *force)
{
  int v3; // edi
  int v4; // ecx
  tagCmdData *v5; // esi
  CCBStage *v6; // ecx
  int RoleIndex; // edi
  unsigned int v8; // esi
  int v9; // eax
  int v10; // ecx
  bool v11; // cc
  unsigned int nSrcRole; // eax
  int v13; // edx
  char v14; // al
  int v16; // [esp+0x0] [ebp-0x90]
  int nRoleIndex[11]; // [esp+0xC] [ebp-0x84] BYREF
  _DWORD pData[11]; // [esp+0x38] [ebp-0x58] BYREF
  int roleIdx[3]; // [esp+0x64] [ebp-0x2C] BYREF
  int v20; // [esp+0x70] [ebp-0x20]
  int v21; // [esp+0x74] [ebp-0x1C]
  float v22; // [esp+0x78] [ebp-0x18]
  int v23; // [esp+0x7C] [ebp-0x14]
  int p_DWORD; // [esp+0x80] [ebp-0x10] BYREF
  int pnVal; // [esp+0x84] [ebp-0xC] BYREF
  char *v26; // [esp+0x88] [ebp-0x8]
  unsigned int v27; // [esp+0x8C] [ebp-0x4]

  memset(nRoleIndex, 0, sizeof(nRoleIndex));
  v3 = 0;
  v4 = 24;
  v21 = 0;
  pnVal = 0;
  p_DWORD = 6;
  v27 = 0;
  v23 = 24;
  v26 = (char *)&this->m_info.name[20];
  do
  {
    v5 = (tagCmdData *)force;
    if ( force->bMultiDestRole )
    {
      if ( !force->m_destRoleView.bDestRole[v3] )
        goto LABEL_27;
    }
    else if ( force->nDestRole != v3 )
    {
      goto LABEL_27;
    }
    if ( (((CCBStage *)*(CCBStage **)(v4 + *(_DWORD *)&this->m_pObjMsgBuffer[100])))->CCBStage::ForceEndTaskByPFN()
      || *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(force->dwItemID) + 666) == 2 )
    {
      if ( this->CCBRoleState::GetRoleField(v3, 22) )
        goto LABEL_27;
      qmemcpy(nRoleIndex, force, sizeof(nRoleIndex));
      nRoleIndex[3] = v27;
      if ( this->CCBRoleState::VarianceRoundCounter(nRoleIndex) )
      {
        v8 = v27;
        v21 = this->CCBRoleState::CheckTargetCombo(force, v27);
        if ( v21 < 0
          && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdEmpty(v8)
          && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdReady(v8) )
        {
          (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(force->dwItemID);
          (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdData(v8);
        }
        if ( v23 >= 44 && v23 < 68 && this->CCBRoleState::SetRoleField(v27, 0) <= 0 )
        {
          if ( (unsigned __int8)this->CCBRoleState::Revive(v16) )
          {
            (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v26 - 135));
            if ( v9 )
            {
              if ( *(_DWORD *)(v9 + 832) )
              {
                if ( *(_DWORD *)(v9 + 836) == force->dwItemID )
                {
                  v10 = *(__int16 *)(v9 + 840);
                  v22 = *(float *)&v10;
                  if ( v10 > 0 )
                  {
                    v22 = (float)SLODWORD(v22) * 10.239999771118164f;
                    v20 = (int)v22;
                    ++*(_DWORD *)&g_TempBuffer1024[912];
                    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
                    if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < v20 )
                      *(_DWORD *)v26 = *(_DWORD *)(v9 + 832);
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      memset(pData, 0, sizeof(pData));
      pData[2] = v27;
      v6 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
      LOBYTE(pData[10]) = 1;
      pData[1] = 0;
      RoleIndex = (((CCBStage *)v6))->CCBStage::GetRoleIndex(7, pData, 1);
      if ( RoleIndex == -1 )
        goto LABEL_27;
      this->CCBRoleState::CheckRoleStatus((int)roleIdx);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::SelectRole) */, 0, 0, 0, roleIdx, 0, 1065353216);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
    }
    v5 = (tagCmdData *)force;
LABEL_27:
    v4 = v23 + 4;
    v3 = v27 + 1;
    v11 = v23 + 4 < 68;
    ++v27;
    v23 += 4;
    v26 += 892;
  }
  while ( v11 );
  this->CCBRoleState::SetRoleHP(v5->nSrcRole, v5->dwItemID);
  nSrcRole = v5->nSrcRole;
  if ( nSrcRole <= 4 )
  {
    (((PAL_GDB *)this))->PAL_GDB::SearchItemLoop(nSrcRole, v5->dwItemID, &p_DWORD, &pnVal);
    v13 = pnVal + 892 * v5->nSrcRole + 8 * p_DWORD + 984;
    v14 = *((_BYTE *)((UIWnd *)this) + v13);
    if ( v14 != -1 )
      *((_BYTE *)((UIWnd *)this) + v13) = v14 + 1;
  }
  if ( *(_DWORD *)&this->m_pObjMsgBuffer[892 * v5->nSrcRole + 128] == 7312
    && v5->dwCmdKind == 261
    && v5->dwItemID == 210 )
  {
    this->CCBRoleState::CheckRoleCanAct(v5->nSrcRole);
  }
  return 1;
}

// 0x004F1420
char CCBRoleState::GetDeadRoleNumInForce(int *force)
{
  int v3; // edx
  CCBStage *v4; // ecx
  int v5; // esi
  CCBStage *v6; // ecx
  int RoleIndex; // esi
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  bool v11; // cc
  int v13; // [esp+0x0] [ebp-C0h]
  int nRoleIndex[11]; // [esp+0xC] [ebp-B4h] BYREF
  _DWORD v15[11]; // [esp+0x38] [ebp-0x88] BYREF
  _DWORD pData[11]; // [esp+0x64] [ebp-0x5C] BYREF
  int p_DWORD[3]; // [esp+0x90] [ebp-0x30] BYREF
  int roleIdx[3]; // [esp+0x9C] [ebp-0x24] BYREF
  int v19; // [esp+A8h] [ebp-0x18]
  int v20; // [esp+ACh] [ebp-0x14]
  float v21; // [esp+B0h] [ebp-0x10]
  char *v22; // [esp+B4h] [ebp-0xC]
  int v23; // [esp+B8h] [ebp-0x8]
  int idx; // [esp+BCh] [ebp-0x4]

  v3 = 0;
  memset(nRoleIndex, 0, sizeof(nRoleIndex));
  v20 = 0;
  idx = 0;
  v23 = 24;
  v22 = (char *)&this->m_info.name[20];
  do
  {
    if ( *((_BYTE *)force + 17) )
    {
      if ( !*((_BYTE *)force + v3 + 29) )
        goto LABEL_30;
    }
    else if ( force[3] != v3 )
    {
      goto LABEL_30;
    }
    qmemcpy(nRoleIndex, force, sizeof(nRoleIndex));
    nRoleIndex[3] = v3;
    if ( this->CCBRoleState::VarianceRoundCounter(nRoleIndex) )
    {
      if ( this->CCBRoleState::IsAllyTargetCmd(force)
        || (((CCBStage *)*(CCBStage **)(v23 + *(_DWORD *)&this->m_pObjMsgBuffer[100])))->CCBStage::ForceEndTaskByPFN()
        || *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(force[1]) + 666) == 2 )
      {
        v8 = idx;
        v20 = this->CCBRoleState::CheckBoss(force, idx);
        if ( v20 < 0
          && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdEmpty(v8)
          && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdReady(v8) )
        {
          (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdData(v8);
        }
        if ( force[1] == 4101 )
          this->CCBRoleState::GetFirstAliveRoleInForce(0, force[3]);
        if ( v23 >= 44 && v23 < 68 && this->CCBRoleState::SetRoleField(idx, 0) <= 0 )
        {
          if ( (unsigned __int8)this->CCBRoleState::Revive(v13) )
          {
            (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v22 - 135));
            if ( v9 )
            {
              if ( *(_DWORD *)(v9 + 832) )
              {
                if ( *(_DWORD *)(v9 + 836) == force[1] )
                {
                  v10 = *(__int16 *)(v9 + 840);
                  v21 = *(float *)&v10;
                  if ( v10 > 0 )
                  {
                    v21 = (float)SLODWORD(v21) * 10.239999771118164f;
                    v19 = (int)v21;
                    ++*(_DWORD *)&g_TempBuffer1024[912];
                    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
                    if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < v19 )
                      *(_DWORD *)v22 = *(_DWORD *)(v9 + 832);
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        memset(v15, 0, sizeof(v15));
        v6 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
        LOBYTE(v15[10]) = 1;
        v15[2] = idx;
        v15[1] = 0;
        RoleIndex = (((CCBStage *)v6))->CCBStage::GetRoleIndex(7, v15, 1);
        if ( RoleIndex != -1 )
        {
          this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::SelectRole) */, 0, 0, 0, p_DWORD, 0, 1065353216);
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
        }
      }
    }
    else
    {
      memset(pData, 0, sizeof(pData));
      v4 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
      pData[1] = 0;
      LOBYTE(pData[10]) = 1;
      pData[2] = idx;
      v5 = (((CCBStage *)v4))->CCBStage::GetRoleIndex(7, pData, 1);
      if ( v5 != -1 )
      {
        this->CCBRoleState::CheckRoleStatus((int)roleIdx);
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v5, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::SelectRole) */, 0, 0, 0, roleIdx, 0, 1065353216);
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v5);
      }
    }
LABEL_30:
    v3 = idx + 1;
    v11 = v23 + 4 < 68;
    ++idx;
    v23 += 4;
    v22 += 892;
  }
  while ( v11 );
  this->CCBRoleState::SetRoleHP(force[2], force[1]);
  return 1;
}

// 0x004F17C0
char CCBRoleState::GetFirstAliveRoleInForce(int roleIdx, int arg4)
{
  int v4; // ebp
  int v5; // eax
  _DWORD *v6; // esi
  int v7; // ecx
  int v8; // edi
  int RoleIndex; // eax
  int v10; // ecx
  int v11; // edi
  CScreenMode *Instance; // eax
  int SkillNum; // eax
  int p_DWORD; // [esp+0x10] [ebp-0x44] BYREF
  int v16; // [esp+0x14] [ebp-0x40]
  int v17; // [esp+0x18] [ebp-0x3C]
  int pConfig; // [esp+0x1C] [ebp-0x38] BYREF
  int v19; // [esp+0x20] [ebp-0x34]
  int v20; // [esp+0x24] [ebp-0x30]
  _DWORD pData[11]; // [esp+0x28] [ebp-0x2C] BYREF

  p_DWORD = 0;
  v16 = 0;
  v17 = 0;
  memset(pData, 0, sizeof(pData));
  v4 = -1;
  pData[3] = arg4;
  pConfig = 0xFFFF;
  v19 = 0;
  v20 = 0;
  v5 = *(_DWORD *)&this->m_info.name[892 * arg4 + 24];
  LOBYTE(pData[10]) = 1;
  v6 = (_DWORD *)((char *)this + 892 * arg4);
  pData[0] = 260;
  pData[1] = 0;
  if ( v5 > 0 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    v7 = (unsigned long)v6[274];
    v8 = (((int)g_nCombatRandSeed >> 16) & 0x7FFF) % v7 + 1;
    v6[274] = v7 - v8;
    RoleIndex = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(28, pData, 1);
    v4 = RoleIndex;
    if ( RoleIndex != -1 )
    {
      p_DWORD = 1;
      v17 = v8;
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FormatAttackResultText) */, 0, 0, 0, &p_DWORD, -1082130432, 0x40000000);
      this->CCBRoleState::CheckBuff(roleIdx);
    }
  }
  if ( v6[275] && (int)v6[276] > 0 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    v10 = (unsigned long)v6[276];
    v11 = (((int)g_nCombatRandSeed >> 16) & 0x7FFF) % v10 + 1;
    v6[276] = v10 - v11;
    if ( v4 == -1 )
    {
      v4 = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(28, pData, 1);
      if ( v4 == -1 )
        return 0;
    }
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa006", 1);
    v16 = (unsigned long)v6[275];
    p_DWORD = 0;
    v17 = v11;
    (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v4, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FormatAttackResultText) */, 0, 0, 0, &p_DWORD, -1082130432, 0x40000000);
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v6[275]);
    pConfig = (unsigned long)v6[275];
    v20 = SkillNum;
    v19 = v11;
    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&pConfig);
  }
  if ( v4 != -1 )
  {
    (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v4);
    return 1;
  }
  return 0;
}

// 0x004F1A30
bool CCBRoleState::GetCastFightSkillSuccess(int pCmd)
{
  int v4; // esi
  int i; // ebp
  int v6; // eax
  int pCmda; // [esp+0x14] [ebp+0x4]

  pCmda = *(_DWORD *)(pCmd + 8);
  v4 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( *(_BYTE *)(pCmd + 17) )
    {
      if ( !*(_BYTE *)(v4 + pCmd + 29) )
        goto LABEL_13;
    }
    else if ( *(_DWORD *)(pCmd + 12) != v4 )
    {
      goto LABEL_13;
    }
    if ( (this->CCBRoleState::IsAllyTargetCmd((int *)pCmd)
       || (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + i)))->CCBStage::ForceEndTaskByPFN()
       || *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(_DWORD *)(pCmd + 4)) + 748) == 2)
      && CCBRoleState_CheckBoss((int *)pCmd, v4) < 0
      && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdEmpty(v4)
      && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdReady(v4) )
    {
      (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdData(v4);
    }
LABEL_13:
    ++v4;
  }
  v6 = *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1120);
  if ( *(_DWORD *)(v6 + 56) == 1 )
    this->CCBRoleState::PopulateTargetList(pCmda, *(_DWORD *)(v6 + 104));
  return 1;
}

// 0x004F1B20
void CCBRoleState::SetCoAttack(unsigned int dwCoAttackID)
{
  unsigned int v4; // edi
  signed int dwCoAttackIDa; // [esp+0x14] [ebp+0x4]

  v4 = 0;
  for ( dwCoAttackIDa = 24; dwCoAttackIDa < 68; dwCoAttackIDa += 4 )
  {
    if ( *(_BYTE *)(dwCoAttackID + 17) )
    {
      if ( !*(_BYTE *)(v4 + dwCoAttackID + 29) )
        goto LABEL_12;
    }
    else if ( *(_DWORD *)(dwCoAttackID + 12) != v4 )
    {
      goto LABEL_12;
    }
    if ( (this->CCBRoleState::IsAllyTargetCmd((int *)dwCoAttackID)
       || (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + dwCoAttackIDa)))->CCBStage::ForceEndTaskByPFN())
      && this->CCBRoleState::GetV4((int *)dwCoAttackID, v4) < 0
      && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdEmpty(v4)
      && !(((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::IsCmdReady(v4) )
    {
      (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdData(v4);
    }
LABEL_12:
    ++v4;
  }
  this->CCBRoleState::SetRoleHP(*(_DWORD *)(dwCoAttackID + 8), *(_DWORD *)(dwCoAttackID + 4));
  (((UIListBox *)*(UIListBox **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1068)))->UIListBox::GetCurSel();
  (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1068)))->UIScrollBar::SetRange(50.0);
  (((UIProgressBar *)*(UIProgressBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1068)))->UIProgressBar::FindChildByName(0.0);
  *(_DWORD *)&this->m_info.name[892 * *(_DWORD *)(dwCoAttackID + 8) + 16] = 0;
}

// 0x004F1CC0
bool CCBRoleState::CanBeImbibeNimbus(int dmg, unsigned int nRoleIndex)
{
  bool result; // al
  char *v6; // [esp+0xC] [ebp-0x4]
  int dmga; // [esp+0x18] [ebp+0x8]
  float dmgb; // [esp+0x18] [ebp+0x8]

  if ( dmg < 5 )
    return 0;
  if ( dmg >= 11 )
    return 0;
  v6 = (char *)this + 892 * dmg;
  if ( !v6[577] )
    return 0;
  dmga = this->CCBRoleState::ApplyDamage(4, dmg);
  if ( dmga <= 0 )
    return 0;
  dmgb = (float)dmga * 10.239999771118164f;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
  if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) >= (int)dmgb )
    return 0;
  switch ( *((_DWORD *)v6 + 160) )
  {
    case 0x385:
      this->CCBRoleState::ProcessRound(nRoleIndex, 3, 1, 1);
      goto LABEL_8;
    case 0x386:
    case 0x396:
    case 0x39E:
      this->CCBRoleState::ProcessRound(nRoleIndex, 4, 1, 1);
      result = 1;
      break;
    case 0x387:
      this->CCBRoleState::ProcessRound(nRoleIndex, 1, 1, 1);
      result = 1;
      break;
    case 0x388:
      this->CCBRoleState::ProcessRound(nRoleIndex, 2, 1, 1);
      result = 1;
      break;
    case 0x389:
    case 0x398:
    case 0x39F:
      this->CCBRoleState::ProcessRound(nRoleIndex, 5, 1, 1);
      result = 1;
      break;
    case 0x38A:
      this->CCBRoleState::ProcessRound(nRoleIndex, 14, 1, 1);
      result = 1;
      break;
    case 0x38B:
    case 0x397:
    case 0x399:
      this->CCBRoleState::ProcessRound(nRoleIndex, 15, 1, 1);
      result = 1;
      break;
    case 0x38C:
    case 0x3A0:
      this->CCBRoleState::ProcessRound(nRoleIndex, 16, 1, 1);
      result = 1;
      break;
    case 0x38D:
      this->CCBRoleState::ProcessRound(nRoleIndex, 17, 1, 1);
      result = 1;
      break;
    case 0x38E:
    case 0x394:
      this->CCBRoleState::ProcessRound(nRoleIndex, 18, 1, 1);
      result = 1;
      break;
    case 0x38F:
    case 0x395:
      this->CCBRoleState::ProcessRound(nRoleIndex, 19, 1, 1);
      result = 1;
      break;
    case 0x390:
      this->CCBRoleState::GetMaxHP(nRoleIndex);
      this->CCBRoleState::GetMaxMP(nRoleIndex);
      result = 1;
      break;
    case 0x391:
      result = this->CCBRoleState::CheckRoleValid(dmg, nRoleIndex, 27);
      break;
    case 0x392:
      result = this->CCBRoleState::CheckRoleValid(dmg, nRoleIndex, 28);
      break;
    case 0x393:
      result = this->CCBRoleState::CheckRoleValid(dmg, nRoleIndex, 1);
      break;
    case 0x3A1:
      result = this->CCBRoleState::CheckRoleValid(dmg, nRoleIndex, 30);
      break;
    default:
LABEL_8:
      result = 1;
      break;
  }
  return result;
}

// 0x004F1FA0
bool CCBRoleState::CheckRoleValid(int nRoleIndex, unsigned int roleIdx, int nVal)
{
  bool result; // al
  CCBSystem *v6; // edx
  CCBStage *v7; // ecx
  int RoleIndex; // edi
  CCBSystem *v9; // ecx
  int v10; // edi
  int v11; // edi
  void *TargetRole; // eax
  int p_DWORD[3]; // [esp+0x10] [ebp-0x70] BYREF
  _BYTE pOut[12]; // [esp+0x1C] [ebp-0x64] BYREF
  _DWORD v15[11]; // [esp+0x28] [ebp-0x58] BYREF
  _DWORD pData[11]; // [esp+0x54] [ebp-0x2C] BYREF

  switch ( nVal )
  {
    case 1:
      return this->CCBRoleState::CanRoleAct(roleIdx);
    case 2:
      v6 = (CCBSystem *)(*(CCBSystem **)&this->m_pObjMsgBuffer[96]);
      if ( LOBYTE(v6->m_pFightInfo->nRoleWillNotBeAttack) )
      {
        memset(pData, 0, sizeof(pData));
        pData[2] = nRoleIndex;
        v7 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
        LOBYTE(pData[10]) = 1;
        pData[0] = 267;
        pData[1] = 0;
        pData[3] = -1;
        RoleIndex = (((CCBStage *)v7))->CCBStage::GetRoleIndex(26, pData, 1);
        if ( RoleIndex != -1 )
        {
          memset(p_DWORD, 0, sizeof(p_DWORD));
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessRoleEffect) */, 0, 0, 0, p_DWORD, 0, 1077936128);
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
        }
        goto LABEL_6;
      }
      this->m_pObjMsgBuffer[125] = 1;
      memset(v15, 0, sizeof(v15));
      LOBYTE(v15[10]) = 1;
      LOWORD(v15[4]) = 0;
      v15[1] = (((CCBSystem *)v6))->CCBSystem::ProcProtect();
      v15[3] = roleIdx;
      v15[2] = nRoleIndex;
      v9 = (CCBSystem *)(*(CCBSystem **)&this->m_pObjMsgBuffer[96]);
      v15[0] = 267;
      (((CCBSystem *)v9))->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::PassCmdToThread, 0, 0, 0, v15);
      return 1;
    case 24:
    case 30:
      return 1;
    case 25:
      this->CCBRoleState::CheckRoundComplete();
      return 1;
    case 27:
      if ( roleIdx > 4 )
        return 1;
      v10 = this->CCBRoleState::GetTotalRounds() / 200;
      v11 = v10 - this->CCBRoleState::GetTotalRounds() / 100;
      if ( v11 > 0 )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
        v11 = (((int)g_nCombatRandSeed >> 16) & 0x7FFF) % v11;
      }
      if ( v11 + this->CCBRoleState::GetTotalRounds() / 200 <= 0 )
        return 1;
      this->CCBRoleState::CheckBuff(roleIdx);
      return 1;
    case 28:
      if ( roleIdx > 4 )
        return 1;
      if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(14) <= 0 )
        goto LABEL_6;
      ++*(_DWORD *)&g_TempBuffer1024[912];
      g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
      TargetRole = (((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(TargetRole);
      result = 1;
      break;
    case 29:
      if ( this->CCBRoleState::UpdateRoleMP(2) == 1 )
        this->CCBRoleState::SpawnRandomEnemies(nRoleIndex, roleIdx);
      return 1;
    default:
LABEL_6:
      result = 0;
      break;
  }
  return result;
}

// 0x004F2310
char CCBRoleState::CheckRoleNimbus(int nRoleIndex, unsigned int dwVal)
{
  int SkillNum; // eax

  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(_DWORD *)(nRoleIndex + 4));
  return this->CCBRoleState::CheckRoleValid(*(_DWORD *)(nRoleIndex + 8), dwVal, *(unsigned __int8 *)(SkillNum + 628));
}

// 0x004F2350
bool CCBRoleState::CanBeSelect(tagCmdData *pCmd, unsigned int nDestRole)
{
  int RoleNum; // eax

  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pCmd->dwItemID);
  return this->CCBRoleState::CheckRoleValid(pCmd->nSrcRole, nDestRole, *(unsigned __int8 *)(RoleNum + 578));
}

// 0x004F2390
char CCBRoleState::CheckRoundComplete()
{
  unsigned int v2; // ebx
  int v3; // esi
  char *v4; // ebp
  int v5; // eax
  CCBControl *v6; // ecx
  int v7; // ecx
  int v8; // ebx
  int v9; // ecx
  int v10; // esi
  int v11; // edx
  _DWORD *v12; // eax
  int v13; // edx
  int v14; // ecx
  LONG *p_bottom; // esi
  LONG v16; // eax
  int v17; // edx
  int v18; // ebp
  float v19; // st7
  float v20; // st6
  int v21; // eax
  float v22; // edx
  int v23; // eax
  int v24; // edx
  int v26; // [esp+0x0] [ebp-0x34] BYREF
  float v27; // [esp+0x14] [ebp-0x20]
  int v28; // [esp+0x18] [ebp-0x1C]
  _DWORD v29[6]; // [esp+0x1C] [ebp-0x18] BYREF

  v2 = 0;
  v3 = 24;
  v4 = (char *)&this->m_pObjMsgBuffer[153];
  do
  {
    if ( *v4 )
    {
      if ( !(((CCBStage *)*(CCBStage **)(v3 + *(_DWORD *)&this->m_pObjMsgBuffer[100])))->CCBStage::ForceEndTaskByPFN() )
        return 0;
      LOBYTE(v5) = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::IsTaskExist(v2);
      if ( v5 > 0 )
        return 0;
    }
    v3 += 4;
    ++v2;
    v4 += 892;
  }
  while ( v3 < 44 );
  v6 = (CCBControl *)*(CCBControl **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 8);
  if ( v6->m_bActive )
    (((CCBControl *)v6))->CCBControl::GetState();
  v7 = g_nCombatRandSeed;
  v29[0] = 1;
  v29[1] = 2;
  v29[2] = 3;
  v29[3] = 4;
  v29[4] = 5;
  v29[5] = 6;
  v8 = 32;
  do
  {
    v9 = 214013 * v7 + 2531011;
    *(_DWORD *)&g_TempBuffer1024[912] += 2;
    v10 = ((v9 >> 16) & 0x7FFF) % 6;
    v7 = 214013 * v9 + 2531011;
    g_nCombatRandSeed = v7;
    v11 = ((v7 >> 16) & 0x7FFF) % 6;
    if ( v10 != v11 )
    {
      v12 = (_DWORD *)&v29[v11];
      v13 = v29[v10];
      v29[v10] = (unsigned long)*v12;
      *v12 = v13;
      v7 = g_nCombatRandSeed;
    }
    --v8;
  }
  while ( v8 );
  v14 = 24;
  p_bottom = (LONG *)&this->m_info.rect.bottom;
  do
  {
    if ( *((_BYTE *)p_bottom - 559) )
    {
      v16 = *(int *)((char *)&v26 + v14 + 4);
      *p_bottom = v16;
      v17 = *(_DWORD *)&this->m_pObjMsgBuffer[100];
      v16 *= 3;
      v18 = *(_DWORD *)(v17 + 20);
      v19 = *(float *)(v18 + 4 * v16 + 8);
      v20 = *(float *)(v18 + 4 * v16 + 12);
      v27 = *(float *)(v18 + 4 * v16 + 12);
      v28 = *(_DWORD *)(v18 + 4 * v16 + 16);
      v21 = *(_DWORD *)(v14 + v17) + 6584;
      *(_DWORD *)(v21 + 8) = v28;
      v22 = v27;
      *(float *)v21 = v19;
      *(float *)(v21 + 4) = v20;
      v23 = *(_DWORD *)(v14 + *(_DWORD *)&this->m_pObjMsgBuffer[100]);
      *(float *)(v23 + 6600) = v22;
      v24 = v28;
      v23 += 6596;
      *(float *)v23 = v19;
      *(_DWORD *)(v23 + 8) = v24;
    }
    v14 += 4;
    p_bottom += 223;
  }
  while ( v14 < 44 );
  return 1;
}

// 0x004F2560
char CCBRoleState::ValidateSlotIndex(unsigned int arg0, unsigned int dwVal)
{
  void **v3; // edi
  int v4; // esi
  int v5; // edx
  float arg0a; // [esp+0x18] [ebp+0x8]

  if ( arg0 > 4 )
    return 0;
  if ( !this->m_pObjMsgBuffer[892 * arg0 + 153] )
    return 0;
  v3 = (void **)(&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * arg0);
  if ( !*v3 )
    return 0;
  v4 = 0;
  v5 = 700;
  while ( 1 )
  {
    if ( *((_BYTE *)*v3 + v4 + 668) )
    {
      if ( *(__int16 *)((char *)*v3 + v5) > 0 )
      {
        arg0a = (float)*(__int16 *)((char *)*v3 + v5) * 10.239999771118164f;
        ++*(_DWORD *)&g_TempBuffer1024[912];
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
        if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)arg0a )
          break;
      }
    }
    v5 += 2;
    ++v4;
    if ( v5 >= 746 )
      return 0;
  }
  this->CCBRoleState::ProcessRound(dwVal, v4 + 1, 1, 1);
  return 1;
}

// 0x004F2660
int CCBRoleState::CheckTargetCombo(tagCmdData *p, unsigned int roleIdx)
{
  this->CCBRoleState::CanBeSelect(p, roleIdx);
  this->CCBRoleState::IsBoss((int *)p, roleIdx);
  return this->CCBRoleState::CalcCombatDamage(roleIdx);
}

// 0x004F2690
int CCBRoleState::CheckBoss(int *arg0, int roleIdx)
{
  int v5; // ebp
  int result; // eax
  char *v7; // esi
  int v8; // eax
  int roleIdxa; // [esp+0x18] [ebp+0x8]

  this->CCBRoleState::IsBoss(arg0, roleIdx);
  v5 = this->CCBRoleState::SetRoleField(roleIdx, 0);
  result = this->CCBRoleState::CalcCombatDamage(roleIdx);
  roleIdxa = result;
  switch ( arg0[1] )
  {
    case 4201:
      v8 = this->CCBRoleState::SetRoleField(roleIdx, 0);
      this->CCBRoleState::AddCommand(arg0[2], abs32((v5 - v8) / 2), 1);
      return roleIdxa;
    case 4304:
      this->CCBRoleState::CalcDefensePower(arg0[2]);
      return roleIdxa;
    case 4402:
      v7 = (char *)this + 892 * roleIdx;
      v7[1390] = 1;
      v7[1391] = 0;
      break;
  }
  return result;
}

// 0x004F27B0
int CCBRoleState::GetV4(int *arg0, unsigned int roleIdx)
{
  int v4; // ebp

  v4 = this->CCBRoleState::CalcCombatDamage(roleIdx);
  this->CCBRoleState::IsBoss(arg0, roleIdx);
  return v4;
}

// 0x004F27E0
int CCBRoleState::CalcComboDirect(const void *pData, unsigned int roleIdx)
{
  return this->CCBRoleState::CalcCombatDamage(roleIdx);
}

// 0x004F2800
int CCBRoleState::ApplyItemEffect(int nCmdData, int nParam)
{
  int v4; // edi
  int *v5; // ebx
  unsigned int RoleByID; // eax
  int v7; // eax
  int v8; // edi
  signed int v9; // esi
  int v10; // edx
  int nCmdDataa; // [esp+0x14] [ebp+0x8]
  float nCmdDatab; // [esp+0x14] [ebp+0x8]

  v4 = 0;
  v5 = (int *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(*(_DWORD *)(nCmdData + 4)) + 36);
  nCmdDataa = 4;
  do
  {
    if ( *v5 )
    {
      RoleByID = this->CCBRoleState::FindRoleByID(*v5);
      this->CCBRoleState::SetCanAction(RoleByID, nParam, 0);
      v4 += v7;
    }
    ++v5;
    --nCmdDataa;
  }
  while ( nCmdDataa );
  v8 = 2 * v4;
  if ( (_BYTE)unk_5DFDEB )
  {
    nCmdDatab = (float)v8 * 0.10000000149011612f;
    v9 = abs32((int)nCmdDatab);
    if ( v9 )
    {
      v10 = (((int)(214013 * g_nCombatRandSeed + 2531011) >> 16) & 0x7FFF) % v9;
      *(_DWORD *)&g_TempBuffer1024[912] += 2;
      g_nCombatRandSeed = 214013 * (214013 * g_nCombatRandSeed + 2531011) + 2531011;
      if ( (((int)g_nCombatRandSeed >> 16) & 0x3FFu) >= 0x200 )
        return v10 + v8;
      v8 -= v10;
    }
  }
  return v8;
}

// 0x004F2910
int CCBRoleState::SetRoleHP(int roleIdx, int value)
{
  int RoleNum; // ebx
  int result; // eax
  int v6; // ebx
  int p_DWORD; // [esp+0x10] [ebp-0x18] BYREF
  int v8; // [esp+0x14] [ebp-0x14]
  int v9; // [esp+0x18] [ebp-0x10]
  int nVal4[3]; // [esp+0x1C] [ebp-0xC] BYREF

  p_DWORD = 0xFFFF;
  v8 = 0;
  v9 = 0;
  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(value);
  this->CCBRoleState::CalcAttackPower(roleIdx);
  this->CCBRoleState::CalcDefensePower(roleIdx);
  result = *(_DWORD *)(RoleNum + 696);
  if ( result != -1 )
  {
    switch ( result )
    {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
        result = (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::CreateUIObj(&dword_5D8F0C, 0, 0x40u);
        break;
      case 5:
        LOBYTE(result) = this->CCBRoleState::CanUseSkill(roleIdx);
        break;
      case 6:
        result = (int)&this->m_pObjMsgBuffer2[892 * roleIdx + 28];
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 7:
        result = this->CCBRoleState::GetRoleLevel(roleIdx);
        break;
      case 8:
        result = (int)&this->m_pObjMsgBuffer[892 * roleIdx + 200];
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 9:
        result = (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::CreateUIObj(&dword_5D8EF8, 0, 0x40u);
        break;
      case 10:
        LOBYTE(result) = this->CCBRoleState::CheckBuff(roleIdx);
        break;
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        result = (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::CreateUIObj(&dword_5D8EE0, 0, 0x40u);
        break;
      case 16:
        p_DWORD = 6113;
        result = (int)(((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD);
        if ( result )
        {
          v9 = *(_DWORD *)(result + 8);
          v8 = 1;
          p_DWORD = 6113;
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          result = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(8, 0, 1);
          v6 = result;
          if ( result != -1 )
          {
            this->CCBRoleState::CheckRoleStatus((int)nVal4);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcWait) */, 0, 0, 0, nVal4, 0, 1080033280);
            LOBYTE(result) = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v6);
          }
        }
        break;
      default:
        return result;
    }
  }
  return result;
}

// 0x004F2BB0
int CCBRoleState::SetRoleField(int roleIdx, int value)
{
  if ( (_BYTE)value == 1 )
    return *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 168];
  else
    return *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 164];
}

// 0x004F2BF0
int CCBRoleState::GetRoleGPBak(int nVal, char pData)
{
  if ( pData == 1 )
    return *(_DWORD *)&this->m_pObjMsgBuffer[892 * nVal + 176];
  else
    return *(_DWORD *)&this->m_pObjMsgBuffer[892 * nVal + 172];
}

// 0x004F2C30
void * CCBRoleState::GetRole(int index)
{
  char v3; // [esp+0x8] [ebp+0x8]

  if ( v3 == 1 )
    return *(void **)&this->m_pObjMsgBuffer[892 * index + 184];
  else
    return *(void **)&this->m_pObjMsgBuffer[892 * index + 180];
}

// 0x004F2C70
int CCBRoleState::AddCommand(int nCmdType, BOOL bImmediate, int nParam)
{
  char *v6; // ebp
  int v8; // ebx
  int TotalRounds; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // esi
  int RoleIndex; // ebp
  int v14; // eax
  char v15; // [esp+0x13] [ebp-0x39]
  int p_DWORD[3]; // [esp+0x14] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x20] [ebp-0x2C] BYREF
  int nCmdTypea; // [esp+0x50] [ebp+0x4]
  int bImmediatea; // [esp+0x54] [ebp+0x8]
  int v20; // [esp+0x5C] [ebp+0x10]

  memset(pData, 0, sizeof(pData));
  v15 = 1;
  v6 = (char *)this + 892 * nCmdType;
  nCmdTypea = (int)v6;
  if ( !v6[578] )
  {
    *((_DWORD *)v6 + 147) = 0;
    return 0;
  }
  if ( v6[1432] )
    return 0;
  if ( this->CCBRoleState::GetRoleField(nCmdType, 23) )
    return 0;
  v8 = bImmediate;
  if ( bImmediate < 0 && v6[1140] && bImmediate < -1 )
    v8 = bImmediate / 2;
  if ( !*(_BYTE *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * nCmdType + 24) + 272) )
    v15 = 0;
  if ( v8 < 0 && v6[700] )
  {
    TotalRounds = this->CCBRoleState::GetTotalRounds();
    if ( TotalRounds >= -v8 )
    {
      this->CCBRoleState::CheckBuff(nCmdType);
      return 0;
    }
    v8 += TotalRounds;
    this->CCBRoleState::CheckBuff(nCmdType);
  }
  bImmediatea = *((_DWORD *)v6 + 147);
  *((_DWORD *)v6 + 147) = v8 + bImmediatea;
  v10 = *((_DWORD *)v6 + 148);
  if ( v8 + bImmediatea <= v10 )
    v10 = v8 + bImmediatea < 0 ? 0 : v8 + bImmediatea;
  *((_DWORD *)v6 + 147) = v10;
  if ( v8 < 0 && (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::CreateRoleStateObj((CCBRoleState **)nCmdType) )
    (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdData(nCmdType);
  v11 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
  if ( *(_BYTE *)(v11 + 133) )
    (((CCBUI *)*(CCBUI **)(v11 + 28)))->CCBUI::HandleRoleStateDialog(nCmdType);
  if ( v8 < 0 && this->CCBRoleState::GetRoleField(nCmdType, 17) )
    this->CCBRoleState::ProcessRound(nCmdType, 17, 0, 1);
  if ( this->m_pObjMsgBuffer[124] && nCmdType == 10 )
    *((_DWORD *)&this->m_byteFlags + 458) = *((_DWORD *)&this->m_byteFlags + 459);
  if ( *((int *)v6 + 147) <= 0 )
  {
    if ( *((_DWORD *)v6 + 138) == 738 )
    {
      (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::ProcMessage(nCmdType);
      this->CCBRoleState::LoadRoleModel(nCmdType);
      v12 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
      if ( *(_BYTE *)(v12 + 133) )
        (((CCBUI *)*(CCBUI **)(v12 + 28)))->CCBUI::HandleRoleStateDialog(nCmdType);
      return -bImmediatea;
    }
    *((_DWORD *)v6 + 147) = 0;
    *((float *)v6 + 349) = *(float *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 80);
    *((_DWORD *)v6 + 348) = v20;
    (((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::ProcMessage(nCmdType);
  }
  if ( v15 )
  {
    LOBYTE(pData[10]) = 1;
    pData[2] = nCmdType;
    pData[0] = 259;
    pData[1] = 0;
    pData[3] = nCmdType;
    LOWORD(pData[4]) = 0;
    if ( v8 > 0 )
    {
      RoleIndex = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(6, pData, 1);
      if ( RoleIndex != -1 )
      {
        if ( v8 > *(_DWORD *)(nCmdTypea + 592) - bImmediatea )
          v8 = *(_DWORD *)(nCmdTypea + 592) - bImmediatea;
        this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::GetRoleTaskNum) */, 0, 0, 0, p_DWORD, -1082130432, 1075838976);
        goto LABEL_48;
      }
    }
    else
    {
      RoleIndex = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(6, pData, 1);
      if ( RoleIndex != -1 )
      {
        if ( (_BYTE)nParam && v8 < 0 )
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::HandleKeyFriend) */, 0, 0, 0, p_DWORD, -1082130432, 0);
        this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::GetRoleTaskNum) */, 0, 0, 0, p_DWORD, -1082130432, 0x40000000);
LABEL_48:
        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
      }
    }
    v6 = (char *)nCmdTypea;
  }
  v14 = *((_DWORD *)v6 + 148);
  if ( *((_DWORD *)v6 + 147) > v14 )
    *((_DWORD *)v6 + 147) = v14;
  if ( v8 <= 0 )
    return -abs32(bImmediatea - *((_DWORD *)v6 + 147));
  else
    return v8;
}

// 0x004F3020
int CCBRoleState::CalcAttackPower(int roleIdx)
{
  int v2; // edi
  int v4; // edx
  char *v5; // esi
  int v6; // eax
  int v7; // ecx
  CCBStage *v8; // ecx
  int RoleIndex; // edi
  int v10; // esi
  int v11; // ebx
  _DWORD pData[11]; // [esp+0xC] [ebp-0x40] BYREF
  int p_DWORD[3]; // [esp+0x38] [ebp-0x14] BYREF
  int v15; // [esp+0x44] [ebp-0x8]
  int v16; // [esp+0x48] [ebp-0x4]
  int v17; // [esp+0x58] [ebp+0xC]
  float v18; // [esp+0x58] [ebp+0xC]
  char v19; // [esp+0x5C] [ebp+0x10]

  v2 = v17;
  if ( !v17 )
    return 0;
  v4 = roleIdx;
  v5 = (char *)this + 892 * roleIdx;
  if ( !v5[578] )
    return 0;
  v16 = *((_DWORD *)v5 + 149);
  if ( v17 < 0 )
  {
    v18 = (float)v17 * *((float *)v5 + 164) * 0.009999999776482582f;
    v15 = (int)v18;
    v2 -= v15;
    v17 = v2;
  }
  v6 = v2 + *((_DWORD *)v5 + 149);
  *((_DWORD *)v5 + 149) = v6;
  v7 = *((_DWORD *)v5 + 150);
  if ( v6 <= v7 )
    v7 = v6 < 0 ? 0 : v6;
  *((_DWORD *)v5 + 149) = v7;
  if ( v19 )
  {
    memset(pData, 0, sizeof(pData));
    v8 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
    pData[2] = roleIdx;
    pData[3] = roleIdx;
    LOBYTE(pData[10]) = 1;
    pData[0] = 259;
    pData[1] = 0;
    LOWORD(pData[4]) = 0;
    RoleIndex = (((CCBStage *)v8))->CCBStage::GetRoleIndex(6, pData, 1);
    if ( RoleIndex != -1 )
    {
      if ( v17 <= 0 )
      {
        if ( v16 + v17 < 0 )
          v17 = -v16;
      }
      else
      {
        v10 = *((_DWORD *)v5 + 150) - v16;
        if ( v17 > v10 )
          v17 = v10;
      }
      this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::GetRoleTaskNum) */, 0, 0, 0, p_DWORD, -1082130432, 1075838976);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
    }
    v4 = roleIdx;
    v2 = v17;
  }
  v11 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
  if ( *(_BYTE *)(v11 + 133) )
    (((CCBUI *)*(CCBUI **)(v11 + 28)))->CCBUI::HandleRoleStateDialog(v4);
  return v2;
}

// 0x004F31C0
int CCBRoleState::CalcDefensePower(int roleIdx)
{
  int v2; // edi
  char *v4; // esi
  int v5; // eax
  int v6; // ecx
  CCBStage *v7; // ecx
  int RoleIndex; // edi
  int v9; // esi
  int v10; // ebx
  _DWORD pData[11]; // [esp+0xC] [ebp-0x40] BYREF
  int p_DWORD[3]; // [esp+0x38] [ebp-0x14] BYREF
  int v14; // [esp+0x44] [ebp-0x8]
  int v15; // [esp+0x48] [ebp-0x4]
  int v16; // [esp+0x58] [ebp+0xC]
  float v17; // [esp+0x58] [ebp+0xC]
  char v18; // [esp+0x5C] [ebp+0x10]

  v2 = v16;
  if ( !v16 )
    return 0;
  v4 = (char *)this + 892 * roleIdx;
  if ( !v4[578] || this->CCBRoleState::GetRoleField(roleIdx, 23) && v16 > 0 )
    return 0;
  v15 = *((_DWORD *)v4 + 151);
  if ( v16 < 0 )
  {
    v17 = (float)v16 * *((float *)v4 + 165) * 0.009999999776482582f;
    v14 = (int)v17;
    v2 -= v14;
    v16 = v2;
  }
  v5 = v2 + *((_DWORD *)v4 + 151);
  *((_DWORD *)v4 + 151) = v5;
  v6 = *((_DWORD *)v4 + 152);
  if ( v5 <= v6 )
    v6 = v5 < 0 ? 0 : v5;
  *((_DWORD *)v4 + 151) = v6;
  if ( v18 )
  {
    memset(pData, 0, sizeof(pData));
    v7 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
    pData[2] = roleIdx;
    pData[3] = roleIdx;
    LOBYTE(pData[10]) = 1;
    pData[0] = 259;
    pData[1] = 0;
    LOWORD(pData[4]) = 0;
    RoleIndex = (((CCBStage *)v7))->CCBStage::GetRoleIndex(6, pData, 1);
    if ( RoleIndex != -1 )
    {
      if ( v16 <= 0 )
      {
        if ( v15 + v16 < 0 )
          v16 = -v15;
      }
      else
      {
        v9 = *((_DWORD *)v4 + 152) - v15;
        if ( v16 > v9 )
          v16 = v9;
      }
      this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::GetRoleTaskNum) */, 0, 0, 0, p_DWORD, -1082130432, 1075838976);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
    }
    v2 = v16;
  }
  v10 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
  if ( *(_BYTE *)(v10 + 133) )
    (((CCBUI *)*(CCBUI **)(v10 + 28)))->CCBUI::HandleRoleStateDialog(roleIdx);
  return v2;
}

// 0x004F3380
int CCBRoleState::GetMaxHP(int roleIdx)
{
  int v4; // [esp+0x14] [ebp+0x8]
  int v5; // [esp+0x18] [ebp+0xC]

  if ( (int)this->CCBRoleState::GetRole(roleIdx) < (int)abs32(v5) )
    this->CCBRoleState::GetRole(roleIdx);
  this->CCBRoleState::CalcDefensePower(roleIdx);
  return this->CCBRoleState::CalcDefensePower(v4);
}

// 0x004F33D0
int CCBRoleState::GetMaxMP(int roleIdx)
{
  int v4; // [esp+0x14] [ebp+0x8]
  int v5; // [esp+0x18] [ebp+0xC]

  if ( this->CCBRoleState::GetRoleGPBak(roleIdx, 0) < (int)abs32(v5) )
    this->CCBRoleState::GetRoleGPBak(roleIdx, 0);
  this->CCBRoleState::CalcAttackPower(roleIdx);
  return this->CCBRoleState::CalcAttackPower(v4);
}

// 0x004F3420
int CCBRoleState::GetTotalRounds()
{
  return *(_DWORD *)&this->m_pObjMsgBuffer[208];
}

// 0x004F3430
char CCBRoleState::CheckBuff(int roleIdx)
{
  int RoleIndex; // edi
  int v4; // esi
  char result; // al
  int p_DWORD[3]; // [esp+0x10] [ebp-0xC] BYREF
  int v7; // [esp+0x24] [ebp+0x8]

  *(_DWORD *)&this->m_pObjMsgBuffer[208] += v7;
  if ( v7 < 0 )
  {
    RoleIndex = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(8, 0, 1);
    if ( RoleIndex != -1 )
    {
      this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcWait) */, 0, 0, 0, p_DWORD, 0, 1077936128);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
    }
  }
  v4 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
  result = *(_BYTE *)(v4 + 133);
  if ( result )
    return (((CCBRoleState *)*(CCBRoleState **)(v4 + 28)))->CCBRoleState::HandleDlgMessage();
  return result;
}

// 0x004F34E0
char CCBRoleState::CanUseSkill(int roleIdx)
{
  char result; // al
  char *v3; // esi
  bool v4; // sf
  CScreenMode *Instance; // eax
  CScreenMode *v6; // eax
  int v7; // [esp+0xC] [ebp+0x8]

  result = this->m_pObjMsgBuffer[153];
  if ( result )
  {
    result = roleIdx;
    if ( roleIdx != 4 )
    {
      v3 = (char *)&this->m_pObjMsgBuffer[892 * roleIdx + 204];
      v4 = v7 < 0;
      *(_DWORD *)v3 += v7;
      if ( v7 > 0 )
      {
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa010", 1);
        v4 = v7 < 0;
      }
      if ( v4 )
      {
        v6 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v6))->CScreenMode::AudioSetPosition("wa048", 1);
      }
      if ( *(int *)v3 < 0 )
        *(_DWORD *)v3 = 0;
      if ( *(int *)v3 > 999 )
        *(_DWORD *)v3 = 999;
    }
  }
  return result;
}

// 0x004F3570
int CCBRoleState::CalcMagicAttack(int roleIdx)
{
  this->CCBRoleState::GetRoleMP(roleIdx);
  return 0;
}

// 0x004F3620
int CCBRoleState::CalcMPRegen(int roleIdx)
{
  this->CCBRoleState::GetRoleMP(roleIdx);
  return 0;
}

// 0x004F36D0
int CCBRoleState::CalcMagicDefense(int roleIdx)
{
  this->CCBRoleState::GetRoleMP(roleIdx);
  return 99999;
}

// 0x004F37A0
int CCBRoleState::GetAttackBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = (char *)this + 892 * roleIdx;
  if ( v2[1147] )
  {
    v3 = *((_DWORD *)v2 + 153);
    roleIdxa = (float)v3 * 0.25f;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1148];
    result = *((_DWORD *)v2 + 153);
    if ( v5 )
    {
      roleIdxb = (float)result * -0.25f;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F3820
int CCBRoleState::GetDefenseBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = (char *)this + 892 * roleIdx;
  if ( v2[1149] )
  {
    v3 = *((_DWORD *)v2 + 154);
    roleIdxa = (float)v3 * 0.25f;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1150];
    result = *((_DWORD *)v2 + 154);
    if ( v5 )
    {
      roleIdxb = (float)result * -0.25f;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F38A0
int CCBRoleState::GetRoleState(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = (char *)this + 892 * roleIdx;
  if ( v2[1151] )
  {
    v3 = *((_DWORD *)v2 + 156);
    roleIdxa = (float)v3 * 0.25f;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1152];
    result = *((_DWORD *)v2 + 156);
    if ( v5 )
    {
      roleIdxb = (float)result * -0.25f;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F3920
int CCBRoleState::GetSpeedBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = (char *)this + 892 * roleIdx;
  if ( v2[1153] )
  {
    v3 = *((_DWORD *)v2 + 155);
    roleIdxa = (float)v3 * 0.25f;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1154];
    result = *((_DWORD *)v2 + 155);
    if ( v5 )
    {
      roleIdxb = (float)result * -0.25f;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F39A0
int CCBRoleState::GetRoleLevel(int roleIdx)
{
  int v2; // edi
  char *v3; // edx
  int v5; // [esp+0x10] [ebp+0x8]

  v2 = *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 196];
  v3 = (char *)&this->m_pObjMsgBuffer[892 * roleIdx + 196];
  *(_DWORD *)v3 = v2 + v5;
  if ( v2 + v5 < 0 )
    *(_DWORD *)v3 = 0;
  (((CCBAttackSequen *)*(CCBAttackSequen **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBAttackSequen::GetCmdSlot(roleIdx);
  return v2;
}

// 0x004F39F0
int CCBRoleState::GetRoleExp(int roleIdx)
{
  int result; // eax
  int i; // edx
  int v4; // [esp+0x10] [ebp+0x8]

  result = 0;
  for ( i = 0; i < 8; ++i )
    result += *((unsigned __int8 *)&this->m_mdl.m_mdltype + 892 * roleIdx + 8 * v4 + i);
  return result;
}

// 0x004F3A30
char CCBRoleState::SetRoleFlag(int roleIdx, char flag)
{
  char result; // al

  result = flag;
  *(&this->m_info.type + 892 * roleIdx) = flag;
  return result;
}

// 0x004F3A50
int CCBRoleState::GetRoleAttr(int roleIdx)
{
  int v3; // ecx
  int v4; // esi

  v3 = this->CCBRoleState::SetRoleField(roleIdx, 0);
  v4 = *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 168];
  if ( v3 == v4 )
    return 1;
  if ( v3 >= v4 / 2 && v3 < v4 )
    return 2;
  if ( v3 < v4 / 4 )
    return (v3 <= 0) + 4;
  return 3;
}

// 0x004F3AD0
int CCBRoleState::CalcMPCost(int roleIdx)
{
  this->CCBRoleState::GetRoleMP(roleIdx);
  return -1;
}

// 0x004F3B90
int CCBRoleState::GetRoleMP(int roleIdx)
{
  int result; // eax
  _DWORD *v3; // [esp+0x8] [ebp+0x8]
  _DWORD *v4; // [esp+0xC] [ebp+0xC]

  *v3 = 0;
  result = roleIdx - 1;
  *v4 = 11;
  if ( roleIdx == 1 )
  {
    *v4 = 5;
  }
  else
  {
    result = roleIdx - 2;
    if ( roleIdx == 2 )
      *v3 = 5;
  }
  return result;
}

// 0x004F3BC0
int CCBRoleState::GetRoleHP(int roleIdx)
{
  if ( this->m_pObjMsgBuffer[892 * roleIdx + 153] )
    return (roleIdx >= 5) + 1;
  else
    return 0;
}

// 0x004F3C00
int CCBRoleState::IsForce1(int force)
{
  if ( force == 1 )
    return 2;
  else
    return force == 2;
}

// 0x004F3C20
char CCBRoleState::IsPlayerTeam(int force)
{
  char result; // al

  switch ( force )
  {
    case 0:
    case 6:
    case 8:
    case 10:
    case 12:
    case 20:
    case 21:
    case 22:
    case 23:
    case 26:
    case 27:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004F3C70
char CCBRoleState::GetRoleForce(int roleIdx)
{
  int v3; // esi
  _BYTE *v4; // ebx

  v3 = 1;
  v4 = (_BYTE *)(&this->m_info.savestate + 892 * roleIdx);
  while ( v4[v3] != 1 || this->CCBRoleState::IsPlayerTeam(v3) )
  {
    if ( ++v3 >= 27 )
      return 0;
  }
  return 1;
}

// 0x004F3CC0
bool CCBRoleState::IsRoleInForce(int roleIdx)
{
  bool result; // al
  char *v3; // ecx

  result = 1;
  v3 = (char *)this + 892 * roleIdx;
  if ( v3[1142] != 1 && v3[1143] != 1 && v3[1144] != 1 && v3[1145] != 1 )
    return v3[1146] == 1;
  return result;
}

// 0x004F3D10
char CCBRoleState::CanRoleAct(int roleIdx)
{
  if ( this->CCBRoleState::GetRoleField(roleIdx, 26) )
    return 0;
  if ( !this->CCBRoleState::IsRoleInForce(roleIdx) )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    this->CCBRoleState::ProcessRound(roleIdx, (((int)g_nCombatRandSeed >> 16) & 0x7FFF) % 5 + 1, 1, 1);
  }
  return 1;
}

// 0x004F3D90
char CCBRoleState::GetRoleField(int roleIdx, int fieldOff)
{
  return *(&this->m_info.savestate + 892 * roleIdx + fieldOff);
}

// 0x004F3DC0
int CCBRoleState::FindFirstEnemySlot(int roleIdx)
{
  int v3; // esi

  if ( !this->m_pObjMsgBuffer[154] )
    return 0;
  v3 = 1;
  while ( !*(&this->m_info.savestate + 892 * roleIdx + v3) || this->CCBRoleState::IsPlayerTeam(v3) )
  {
    if ( ++v3 >= 27 )
      return 0;
  }
  return v3;
}

// 0x004F3E20
char * CCBRoleState::ProcessRound(unsigned int dwVal, int force, int a4, int a5)
{
  char *result; // eax
  int i; // edi
  CCBStage *v8; // ecx
  int RoleIndex; // eax
  int v10; // edi
  unsigned int v12; // ebp
  unsigned int v13; // edi
  CScreenMode *Instance; // eax
  char *v15; // edi
  int v16; // edx
  char *v17; // edi
  void ( ***v18)(_DWORD, int); // ecx
  CCBStage *v19; // ecx
  int v20; // edi
  int v21; // edi
  CScreenMode *v22; // eax
  char *v23; // [esp-0x8] [ebp-0x50]
  char *v24; // [esp-0x8] [ebp-0x50]
  int p_DWORD[3]; // [esp+0x10] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x1C] [ebp-0x2C] BYREF
  char *forcea; // [esp+0x50] [ebp+0x8]

  LOBYTE(result) = this->CCBRoleState::GetRoleField(dwVal, 23);
  if ( (_BYTE)result && force != 23 )
    return result;
  if ( force < 1 || force > 5 )
    goto LABEL_7;
  if ( (_BYTE)a4 )
  {
    LOBYTE(result) = this->CCBRoleState::IsRoleInForce(dwVal);
    if ( (_BYTE)result )
      return result;
LABEL_7:
    if ( (_BYTE)a4 )
    {
      if ( force >= 1 && force <= 5 )
      {
        result = (char *)this + 892 * dwVal;
        *(_DWORD *)(result + 1142) = 0;
        result[1146] = 0;
        if ( result[1167] )
          return result;
      }
      if ( force >= 14 && force <= 23 )
      {
        for ( i = 14; i <= 23; ++i )
          this->CCBRoleState::ProcessRound(dwVal, i, 0, 0);
      }
      if ( !this->CCBRoleState::IsPlayerTeam(force)
        && force != 24
        && force != 25
        && *(int *)&this->m_pObjMsgBuffer[892 * dwVal + 164] > 0 )
      {
        memset(pData, 0, sizeof(pData));
        v8 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
        LOBYTE(pData[10]) = 1;
        pData[2] = dwVal;
        pData[0] = 0;
        pData[1] = 0;
        pData[3] = dwVal;
        LOWORD(pData[4]) = 0;
        RoleIndex = (((CCBStage *)v8))->CCBStage::GetRoleIndex(10, pData, 1);
        v10 = RoleIndex;
        if ( RoleIndex != -1 )
        {
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::HandleKeyFriend) */, 0, 0, 0, p_DWORD, -1082130432, 0);
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v10);
        }
      }
    }
  }
  v12 = 223 * dwVal;
  result = (char *)(&this->m_info.savestate + 892 * dwVal + force);
  *result = a4;
  v13 = force + 446 * dwVal;
  forcea = (char *)v13;
  *((_WORD *)&this->m_info.param[6] + v13) = 0;
  *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 0;
  if ( (_BYTE)a4 )
  {
    switch ( force )
    {
      case 1:
        *((_WORD *)&this->m_info.param[6] + v13) = 3;
        goto LABEL_24;
      case 2:
        *((_WORD *)&this->m_info.param[6] + v13) = 3;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 2;
        goto LABEL_25;
      case 3:
        *((_WORD *)&this->m_info.param[6] + v13) = 0;
LABEL_24:
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        goto LABEL_25;
      case 4:
      case 5:
        *((_WORD *)&this->m_info.param[6] + v13) = 0;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 0x7FFF;
LABEL_25:
        LOBYTE(result) = a5;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd005";
        break;
      case 6:
        HIBYTE(this->m_info.param[v12]) = 0;
        LOBYTE(this->m_info.param[v12 + 1]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        goto LABEL_38;
      case 7:
        HIBYTE(this->m_info.param[v12]) = 0;
        LOBYTE(this->m_info.param[v12 + 1]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        goto LABEL_41;
      case 8:
        BYTE1(this->m_info.param[v12 + 1]) = 0;
        BYTE2(this->m_info.param[v12 + 1]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        goto LABEL_38;
      case 9:
        BYTE1(this->m_info.param[v12 + 1]) = 0;
        BYTE2(this->m_info.param[v12 + 1]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        goto LABEL_41;
      case 10:
        HIBYTE(this->m_info.param[v12 + 1]) = 0;
        LOBYTE(this->m_info.param[v12 + 2]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        goto LABEL_38;
      case 11:
        HIBYTE(this->m_info.param[v12 + 1]) = 0;
        LOBYTE(this->m_info.param[v12 + 2]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        goto LABEL_41;
      case 12:
        BYTE1(this->m_info.param[v12 + 2]) = 0;
        BYTE2(this->m_info.param[v12 + 2]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        result = (char *)(((CCBAttackSequen *)*(CCBAttackSequen **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBAttackSequen::GetCmdSlot(dwVal);
LABEL_38:
        LOBYTE(result) = a5;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd021";
        break;
      case 13:
        BYTE1(this->m_info.param[v12 + 2]) = 0;
        BYTE2(this->m_info.param[v12 + 2]) = 0;
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        result = (char *)(((CCBAttackSequen *)*(CCBAttackSequen **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBAttackSequen::GetCmdSlot(dwVal);
LABEL_41:
        LOBYTE(result) = a5;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd022";
        break;
      case 14:
        (((Combat *)this))->Combat::HandleControlCmd(dwVal);
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 4;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd007";
        break;
      case 15:
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 0x7FFF;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd008";
        break;
      case 16:
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 0x7FFF;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd009";
        break;
      case 17:
        (((Combat *)this))->Combat::HandleControlCmd(dwVal);
        ++*(_DWORD *)&g_TempBuffer1024[912];
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
        result = (char *)((((int)g_nCombatRandSeed >> 16) & 0x7FFF) / 7);
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = (((int)g_nCombatRandSeed >> 16) & 0x7FFF) % 7 + 2;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd010";
        break;
      case 18:
        (((Combat *)this))->Combat::HandleControlCmd(dwVal);
        (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * dwVal + 24)))->CCBStage::DangerForceRelease(0);
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 0x7FFF;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd012";
        break;
      case 19:
        (((Combat *)this))->Combat::HandleControlCmd(dwVal);
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 0x7FFF;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd011";
        break;
      case 20:
        if ( dwVal > 4 )
          *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        else
          *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 3;
        LOBYTE(result) = a5;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd016";
        break;
      case 21:
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 4;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd013";
        break;
      case 22:
        LOBYTE(result) = a5;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 4;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd014";
        break;
      case 23:
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 5;
        if ( this->CCBRoleState::IsRoleAlive(dwVal) )
        {
          result = (char *)(((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(22, 0, 1);
          v15 = (char *)result;
          if ( result != (char *)-1 )
          {
            this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName((int)v15, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskBlendToReady) */, 0, 0, 0, p_DWORD, 0, 1065353216);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx((int)v15);
          }
        }
        LOBYTE(result) = a5;
        if ( !(_BYTE)a5 )
          return result;
        v23 = (char *)"wd015";
        break;
      case 24:
        result = (char *)&this->m_pObjMsgBuffer[v12 * 4 + 164];
        v16 = *(_DWORD *)&this->m_pObjMsgBuffer[v12 * 4 + 168] / 10;
        if ( *(_DWORD *)result > v16 )
          *(_DWORD *)result = v16;
        return result;
      case 25:
        result = (char *)(*(char **)&this->m_pObjMsgBuffer[v12 * 4 + 164]);
        if ( (int)result > 0 )
          *(_DWORD *)&this->m_pObjMsgBuffer[v12 * 4 + 164] = 0;
        return result;
      case 26:
        *result = 1;
        *((_WORD *)&this->m_info.path.pt[0].z + v13 + 1) = 0x7FFF;
        return result;
      default:
        return result;
    }
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v23, 1);
  }
  else
  {
    switch ( force )
    {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        if ( (_BYTE)a5 )
        {
          v24 = (char *)"wd006";
          break;
        }
        goto LABEL_91;
      case 12:
      case 13:
        (((CCBAttackSequen *)*(CCBAttackSequen **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBAttackSequen::GetCmdSlot(dwVal);
        goto LABEL_91;
      case 14:
        (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * dwVal + 24)))->CCBStage::DangerForceRelease(0);
        goto LABEL_91;
      case 20:
      case 21:
      case 22:
        goto LABEL_86;
      case 23:
        if ( this->CCBRoleState::IsRoleAlive(dwVal) )
        {
          v21 = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(22, 0, 1);
          if ( v21 != -1 )
          {
            this->CCBRoleState::CheckRoleStatus((int)p_DWORD);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v21, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskBlendToEnd) */, 0, 0, 0, p_DWORD, 0, 1065353216);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v21);
          }
        }
LABEL_86:
        if ( !(_BYTE)a5 )
          goto LABEL_91;
        v24 = (char *)"wd020";
        break;
      case 25:
        if ( this->m_pObjMsgBuffer[v12 * 4 + 154] )
          goto LABEL_91;
        this->m_pObjMsgBuffer[v12 * 4 + 154] = 1;
        *(_DWORD *)&this->m_pObjMsgBuffer[v12 * 4 + 164] = 0;
        memset(&this->m_info.savestate + v12 * 4, 0, 0x18u);
        v17 = (char *)&this->m_info.param[v12 + 5] + 1;
        *(_WORD *)v17 = 0;
        v17[2] = 0;
        memset(&this->m_info.param[v12 + 6], 0, 0x34u);
        *(_WORD *)((char *)&this->m_info.path.pt[0].z + v12 * 4) = 0;
        memset((char *)&this->m_info.path.pt[0].z + v12 * 4 + 2, 0, 0x34u);
        *(_WORD *)((char *)&this->m_info.path.pt[5].x + v12 * 4 + 2) = 0;
        *(&this->m_info.type + v12 * 4) = 0;
        (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * dwVal + 24)))->CCBStage::DangerForceRelease(0);
        (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * dwVal + 24)))->CCBStage::Release(1);
        v18 = *(void ( ****)(_DWORD, int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * dwVal + 76);
        (**v18)((_DWORD)((_DWORD)(v18)), (int)(1));
        (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::SetCmdParam(dwVal, 0);
        (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdData(dwVal);
        if ( !(((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * dwVal + 24)))->CCBStage::ForceEndTaskByPFN() )
        {
          memset(pData, 0, sizeof(pData));
          v19 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
          LOBYTE(pData[10]) = 1;
          pData[2] = dwVal;
          pData[1] = 259;
          v20 = (((CCBStage *)v19))->CCBStage::GetRoleIndex(9, pData, 1);
          if ( v20 != -1 )
          {
            p_DWORD[2] = pData[3];
            p_DWORD[1] = pData[2];
            p_DWORD[0] = 0;
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v20, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v20, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcShowItemName) */, 0, 0, 0, p_DWORD, -1082130432, 0);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v20, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v20);
          }
        }
        if ( !(_BYTE)a5 )
          goto LABEL_91;
        v24 = (char *)"wd004";
        break;
      default:
        goto LABEL_91;
    }
    v22 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v22))->CScreenMode::AudioSetPosition(v24, 1);
LABEL_91:
    result = (char *)forcea;
    *((_WORD *)&this->m_info.param[6] + (_DWORD)forcea) = 0;
    *((_WORD *)&this->m_info.path.pt[0].z + (_DWORD)forcea + 1) = 0;
  }
  return result;
}

// 0x004F48C0
void CCBRoleState::TickDebuffs(int roleIdx)
{
  int v4; // ebx
  int v5; // ecx
  __int16 v6; // dx
  _WORD *v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  _BYTE *v11; // [esp+0x14] [ebp-0x4]
  __int16 *roleIdxa; // [esp+0x20] [ebp+0x8]

  v4 = 1;
  v11 = (_BYTE *)(&this->m_info.savestate + 892 * roleIdx);
  do
  {
    if ( v11[v4] )
    {
      v5 = 446 * roleIdx + v4;
      v6 = *((_WORD *)&this->m_info.param[6] + v5);
      v7 = (_WORD *)&this->m_info.param[6] + v5;
      if ( v6 <= 0 )
      {
        roleIdxa = (__int16 *)&this->m_info.path.pt[0].z + 446 * roleIdx + v4 + 1;
        if ( *roleIdxa > 0 )
        {
          switch ( v4 )
          {
            case 1:
              v8 = this->CCBRoleState::SetRoleField(roleIdx, 1);
              this->CCBRoleState::AddCommand(roleIdx, 3 * v8 / -4, 1);
              break;
            case 2:
              v9 = this->CCBRoleState::SetRoleField(roleIdx, 1);
              goto LABEL_10;
            case 3:
              v9 = this->CCBRoleState::SetRoleField(roleIdx, 0);
LABEL_10:
              this->CCBRoleState::AddCommand(roleIdx, v9 / -2, 1);
              break;
            case 4:
              v10 = this->CCBRoleState::SetRoleField(roleIdx, 1);
              this->CCBRoleState::AddCommand(roleIdx, 5 * v10 / -100, 1);
              break;
            case 5:
              if ( *roleIdxa == 0x7FFF )
                *(&flt_17AA550 + roleIdx) = (double)this->CCBRoleState::SetRoleField(roleIdx, 1) * -0.02;
              this->CCBRoleState::AddCommand(roleIdx, (int)*(&flt_17AA550 + roleIdx), 1);
              *(&flt_17AA550 + roleIdx) = *(&flt_17AA550 + roleIdx) * 1.5;
              break;
            default:
              break;
          }
        }
        if ( --*roleIdxa <= 0 )
        {
          this->CCBRoleState::ProcessRound(roleIdx, v4, 0, 1);
          *roleIdxa = 0;
          if ( v4 == 23 )
          {
            if ( this->CCBRoleState::IsRoleAlive(roleIdx) )
              (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * roleIdx + 24)))->CCBStage::ForceRelease(1);
          }
        }
      }
      else
      {
        *v7 = v6 - 1;
      }
    }
    ++v4;
  }
  while ( v4 <= 23 );
}

// 0x004F4B90
unsigned int CCBRoleState::CalcSpellDamage(int roleIdx, int nMagicID)
{
  int SlotCount; // ebx
  int v5; // esi
  int v7; // eax
  unsigned int v8; // eax
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x18] BYREF
  _BYTE v10[12]; // [esp+0x1C] [ebp-0xC] BYREF

  this->CCBRoleState::GetRoleHP(roleIdx);
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  v5 = 0;
  if ( SlotCount <= 0 )
    return -1;
  while ( *((int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut) + 1) <= 0
       || *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v10) != nMagicID )
  {
    if ( ++v5 >= SlotCount )
      return -1;
  }
  v7 = *((_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v10) + 2);
  if ( !*(_BYTE *)(v7 + 631) )
    return *(__int16 *)(v7 + 644);
  if ( *(_BYTE *)(v7 + 631) != 1 )
    return 0;
  v8 = (int)((unsigned __int64)(1374389535i64
                              * *(__int16 *)(v7 + 644)
                              * *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 168]) >> 32) >> 5;
  return (v8 >> 31) + v8;
}

// 0x004F4C80
unsigned int CCBRoleState::CalcSkillDamage(int roleIdx, int nSkillID)
{
  int SlotCount; // ebx
  int v5; // esi
  int v7; // eax
  unsigned int v8; // eax
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x18] BYREF
  _BYTE v10[12]; // [esp+0x1C] [ebp-0xC] BYREF

  this->CCBRoleState::GetRoleHP(roleIdx);
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  v5 = 0;
  if ( SlotCount <= 0 )
    return -1;
  while ( *((int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut) + 1) <= 0
       || *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v10) != nSkillID )
  {
    if ( ++v5 >= SlotCount )
      return -1;
  }
  v7 = *((_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v10) + 2);
  switch ( *(_BYTE *)(v7 + 631) )
  {
    case 0:
      return *(__int16 *)(v7 + 644);
    case 1:
      v8 = (int)((unsigned __int64)(1374389535i64
                                  * *(__int16 *)(v7 + 644)
                                  * *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 168]) >> 32) >> 5;
      return (v8 >> 31) + v8;
    case 2:
      return *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 168]
           - *(_DWORD *)&this->m_pObjMsgBuffer[892 * roleIdx + 164];
    default:
      return 0;
  }
}

// 0x004F4DA0
int CCBRoleState::ProcessAttackResult(int roleIdx)
{
  int v2; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int RoleNum; // eax
  int v10; // ebp
  int v11; // esi
  int *v12; // ebx
  int v13; // edi
  int v14; // eax
  bool v15; // cc
  int v16; // esi
  int *v17; // ebp
  CCBStageRole *Role; // ecx
  int v19; // [esp+0x10] [ebp-0x48]
  int v21; // [esp+0x18] [ebp-0x40]
  int v22; // [esp+0x1C] [ebp-0x3C]
  int *v23; // [esp+0x20] [ebp-0x38]
  signed int v24; // [esp+0x24] [ebp-0x34]
  int v25; // [esp+0x28] [ebp-0x30]
  _DWORD pOut[11]; // [esp+0x2C] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x5C] [ebp+0x4]
  char v28; // [esp+0x60] [ebp+0x8]
  int v29; // [esp+0x64] [ebp+0xC]

  v2 = roleIdx;
  memset(pOut, 0, sizeof(pOut));
  v19 = 0;
  v25 = -1;
  v24 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v5 = this->CCBRoleState::GetRoleHP(roleIdx) - 1;
  if ( v5 )
  {
    if ( v5 != 1 )
      return 0;
    roleIdxa = (int *)&g_RoleSystemCombat.dword_17AA450;
    v6 = 760;
    while ( 1 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)&this->m_pObjMsgBuffer[892 * v2 + 128]);
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
        if ( *(_BYTE *)(RoleNum + 4) == 3 )
        {
          if ( v28 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 2 )
              goto LABEL_14;
          }
          else if ( !v28 && *(_BYTE *)(RoleNum + 577) == 1 )
          {
LABEL_14:
            pOut[1] = v8;
            if ( this->CCBRoleState::GetRoleAI(pOut) )
            {
              *roleIdxa = v8;
              ++v19;
              ++roleIdxa;
            }
          }
        }
      }
      v6 += 4;
      if ( v6 >= 776 )
      {
        if ( !v19 )
          return 0;
LABEL_37:
        v16 = 0;
        if ( v19 <= 0 )
          return 0;
        v17 = (int *)&g_RoleSystemCombat.dword_17AA450;
        do
        {
          Role = (((CCBStage *)this))->CCBStage::GetRole(v2) /* [ROWTABLE] */;
          if ( (int)abs32((int)Role - v29) < v24 )
          {
            v25 = v16;
            v24 = abs32(abs32((int)Role) - abs32(v29));
          }
          ++v16;
          ++v17;
        }
        while ( v16 < v19 );
        if ( v25 == -1 )
          return 0;
        else
          return *(&g_RoleSystemCombat.dword_17AA450 + v25);
      }
    }
  }
  v21 = 0;
  v22 = 936;
  while ( 2 )
  {
    v10 = 0;
    v11 = 892 * v2;
    v23 = (int *)(4 * v19 + 24814672);
    v12 = (int *)&this->m_pObjMsgBuffer2[892 * v2 + 64 + v21];
    do
    {
      v13 = (unsigned long)*v12;
      if ( *v12 )
      {
        if ( *((_BYTE *)((UIWnd *)this) + v10 + v11 + v22) )
        {
          v14 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v12);
          if ( *(_BYTE *)(v14 + 4) == 3 )
          {
            if ( v28 == 1 )
            {
              if ( *(_BYTE *)(v14 + 577) != 2 )
                goto LABEL_32;
            }
            else if ( v28 || *(_BYTE *)(v14 + 577) != 1 )
            {
              goto LABEL_32;
            }
            pOut[1] = v13;
            if ( this->CCBRoleState::GetRoleAI(pOut) )
            {
              *v23 = v13;
              ++v19;
              ++v23;
            }
          }
        }
      }
LABEL_32:
      ++v10;
      ++v12;
    }
    while ( v10 < 8 );
    v15 = v22 + 8 < 984;
    v21 += 32;
    v22 += 8;
    if ( v15 )
    {
      v2 = roleIdx;
      continue;
    }
    break;
  }
  if ( v19 )
  {
    v2 = roleIdx;
    goto LABEL_37;
  }
  return 0;
}

// 0x004F5070
int CCBRoleState::ProcessMagicResult(int roleIdx)
{
  int v2; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int RoleNum; // eax
  int v10; // ebp
  int v11; // esi
  int *v12; // ebx
  int v13; // edi
  int v14; // eax
  bool v15; // cc
  int v16; // edi
  int *v17; // esi
  unsigned int v18; // ebp
  __int64 v19; // rax
  int v20; // eax
  int v21; // [esp+0x10] [ebp-0x48]
  int v23; // [esp+0x18] [ebp-0x40]
  int v24; // [esp+0x1C] [ebp-0x3C]
  int *v25; // [esp+0x20] [ebp-0x38]
  int v26; // [esp+0x24] [ebp-0x34]
  int v27; // [esp+0x28] [ebp-0x30]
  _DWORD pOut[11]; // [esp+0x2C] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x5C] [ebp+0x4]
  char v30; // [esp+0x60] [ebp+0x8]
  int v31; // [esp+0x64] [ebp+0xC]

  v2 = roleIdx;
  memset(pOut, 0, sizeof(pOut));
  v21 = 0;
  v27 = -1;
  v26 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v5 = this->CCBRoleState::GetRoleHP(roleIdx) - 1;
  if ( v5 )
  {
    if ( v5 != 1 )
      return 0;
    roleIdxa = (int *)&dword_17AA350;
    v6 = 760;
    while ( 1 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)&this->m_pObjMsgBuffer[892 * v2 + 128]);
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
        if ( *(_BYTE *)(RoleNum + 4) == 2 )
        {
          if ( v30 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 4 )
              goto LABEL_14;
          }
          else if ( !v30 && *(_BYTE *)(RoleNum + 577) == 3 )
          {
LABEL_14:
            pOut[1] = v8;
            if ( this->CCBRoleState::GetRoleAI(pOut) )
            {
              *roleIdxa = v8;
              ++v21;
              ++roleIdxa;
            }
          }
        }
      }
      v6 += 4;
      if ( v6 >= 776 )
      {
        if ( !v21 )
          return 0;
LABEL_37:
        v16 = 0;
        if ( v21 <= 0 )
          return 0;
        v17 = (int *)&dword_17AA350;
        v18 = abs32(v31);
        do
        {
          v19 = (int)(abs32((int)(((CCBStage *)this))->CCBStage::GetRole(v2) /* [ROWTABLE] */) - v18);
          v20 = (HIDWORD(v19) ^ v19) - HIDWORD(v19);
          if ( v20 < v26 )
          {
            v26 = v20;
            v27 = v16;
          }
          ++v16;
          ++v17;
        }
        while ( v16 < v21 );
        if ( v27 == -1 )
          return 0;
        else
          return *(&dword_17AA350 + v27);
      }
    }
  }
  v23 = 0;
  v24 = 936;
  while ( 2 )
  {
    v10 = 0;
    v11 = 892 * v2;
    v25 = (int *)(4 * v21 + 24814416);
    v12 = (int *)&this->m_pObjMsgBuffer2[892 * v2 + 64 + v23];
    do
    {
      v13 = (unsigned long)*v12;
      if ( *v12 )
      {
        if ( *((_BYTE *)((UIWnd *)this) + v10 + v11 + v24) )
        {
          v14 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v12);
          if ( *(_BYTE *)(v14 + 4) == 2 )
          {
            if ( v30 == 1 )
            {
              if ( *(_BYTE *)(v14 + 577) != 4 )
                goto LABEL_32;
            }
            else if ( v30 || *(_BYTE *)(v14 + 577) != 3 )
            {
              goto LABEL_32;
            }
            pOut[1] = v13;
            if ( this->CCBRoleState::GetRoleAI(pOut) )
            {
              *v25 = v13;
              ++v21;
              ++v25;
            }
          }
        }
      }
LABEL_32:
      ++v10;
      ++v12;
    }
    while ( v10 < 8 );
    v15 = v24 + 8 < 984;
    v23 += 32;
    v24 += 8;
    if ( v15 )
    {
      v2 = roleIdx;
      continue;
    }
    break;
  }
  if ( v21 )
  {
    v2 = roleIdx;
    goto LABEL_37;
  }
  return 0;
}

// 0x004F5330
int CCBRoleState::AISelectItem(int roleIdx, char pData)
{
  int v6; // eax
  int v7; // edi
  int *v8; // ebx
  int v9; // eax
  int v10; // esi
  int RoleNum; // eax
  int v12; // ecx
  bool v13; // cc
  int v14; // ebp
  int v15; // edi
  int v16; // eax
  int v17; // [esp+0x10] [ebp-0x40]
  int v19; // [esp+0x18] [ebp-0x38]
  int v20; // [esp+0x1C] [ebp-0x34]
  int *v21; // [esp+0x20] [ebp-0x30]
  _DWORD pOut[11]; // [esp+0x24] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x54] [ebp+0x4]
  int *roleIdxb; // [esp+0x54] [ebp+0x4]

  memset(pOut, 0, sizeof(pOut));
  v17 = 0;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v6 = this->CCBRoleState::GetRoleHP(roleIdx) - 1;
  if ( v6 )
  {
    if ( v6 != 1 )
      return 0;
    v7 = 760;
    v8 = (int *)&dword_17AA250;
    roleIdxa = (int *)&this->m_pObjMsgBuffer[892 * roleIdx + 128];
    while ( 1 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*roleIdxa);
      v10 = *(_DWORD *)(v7 + v9);
      if ( v10 )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(_DWORD *)(v7 + v9));
        if ( *(_BYTE *)(RoleNum + 4) == 1 )
        {
          if ( pData == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 2 )
              goto LABEL_14;
          }
          else if ( !pData && *(_BYTE *)(RoleNum + 577) == 1 )
          {
LABEL_14:
            pOut[1] = v10;
            if ( this->CCBRoleState::GetRoleAI(pOut) )
            {
              *v8++ = v10;
              ++v17;
            }
          }
        }
      }
      v7 += 4;
      if ( v7 >= 776 )
      {
        v12 = v17;
        v13 = v17 <= 0;
        if ( !v17 )
          return 0;
LABEL_36:
        if ( v13 )
          return -1;
        ++*(_DWORD *)&g_TempBuffer1024[912];
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
        return *(&dword_17AA250 + (((int)g_nCombatRandSeed >> 16) & 0x7FFF) % v12);
      }
    }
  }
  v19 = 0;
  v20 = 936;
  do
  {
    v14 = 0;
    v21 = (int *)(4 * v17 + 24814160);
    roleIdxb = (int *)&this->m_pObjMsgBuffer2[892 * roleIdx + 64 + v19];
    do
    {
      v15 = (unsigned long)*roleIdxb;
      if ( *roleIdxb )
      {
        if ( *((_BYTE *)((UIWnd *)this) + 892 * roleIdx + v14 + v20) )
        {
          v16 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*roleIdxb);
          if ( *(_BYTE *)(v16 + 4) == 1 )
          {
            if ( pData == 1 )
            {
              if ( *(_BYTE *)(v16 + 577) != 2 )
                goto LABEL_31;
            }
            else if ( pData || *(_BYTE *)(v16 + 577) != 1 )
            {
              goto LABEL_31;
            }
            pOut[1] = v15;
            if ( this->CCBRoleState::GetRoleAI(pOut) )
            {
              *v21 = v15;
              ++v17;
              ++v21;
            }
          }
        }
      }
LABEL_31:
      ++v14;
      ++roleIdxb;
    }
    while ( v14 < 8 );
    v13 = v20 + 8 < 984;
    v19 += 32;
    v20 += 8;
  }
  while ( v13 );
  if ( v17 )
  {
    v12 = v17;
    v13 = v17 <= 0;
    goto LABEL_36;
  }
  return 0;
}

// 0x004F55D0
int CCBRoleState::CalcPhysicalDamage(int roleIdx)
{
  signed int v2; // ebp
  int result; // eax
  int v4; // ebx
  char *v5; // eax
  int v6; // esi
  int RoleNum; // edi
  int v8; // esi
  int *v9; // ebx
  CCBStageRole *Role; // ecx
  int v12; // [esp+0x14] [ebp-0x40]
  int *v13; // [esp+0x18] [ebp-0x3C]
  int *v14; // [esp+0x1C] [ebp-0x38]
  int v15; // [esp+0x20] [ebp-0x34]
  _DWORD pOut[11]; // [esp+0x28] [ebp-0x2C] BYREF
  char v17; // [esp+0x5C] [ebp+0x8]
  int v18; // [esp+0x60] [ebp+0xC]

  memset(pOut, 0, sizeof(pOut));
  v12 = 0;
  v15 = -1;
  v2 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  pOut[3] = -1;
  v4 = 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 260;
  v5 = (char *)this + 892 * roleIdx;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  LOWORD(pOut[4]) = 0;
  v14 = (int *)&dword_17AA150;
  v13 = (int *)(v5 + 712);
  while ( 1 )
  {
    v6 = (unsigned long)*v13;
    if ( *v13 )
    {
      if ( v5[v4 + 736] )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v13);
        if ( !*(_BYTE *)(RoleNum + 4) && (((PAL_GDB *)this))->PAL_GDB::IsRoleAlive(v6) )
        {
          if ( v17 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) != 2 )
              goto LABEL_16;
          }
          else if ( v17 || *(_BYTE *)(RoleNum + 577) != 1 )
          {
            goto LABEL_16;
          }
          pOut[1] = v6;
          if ( this->CCBRoleState::GetRoleAI(pOut) )
          {
            *v14 = v6;
            ++v12;
            ++v14;
          }
        }
      }
    }
LABEL_16:
    ++v4;
    ++v13;
    if ( v4 >= 6 )
      break;
    v5 = (char *)this + 892 * roleIdx;
  }
  result = v12;
  if ( v12 )
  {
    v8 = 0;
    if ( v12 <= 0 )
      return 0;
    v9 = (int *)&dword_17AA150;
    do
    {
      Role = (((CCBStage *)this))->CCBStage::GetRole(roleIdx) /* [ROWTABLE] */;
      if ( (int)abs32((int)Role - v18) < v2 )
      {
        v15 = v8;
        v2 = abs32(abs32((int)Role) - abs32(v18));
      }
      ++v8;
      ++v9;
    }
    while ( v8 < v12 );
    if ( v15 == -1 )
      return 0;
    else
      return *(&dword_17AA150 + v15);
  }
  return result;
}

// 0x004F57A0
int CCBRoleState::CalcMagicDamage(int roleIdx)
{
  signed int v3; // ebx
  int result; // eax
  int v5; // eax
  char *v6; // ecx
  int v7; // esi
  int RoleNum; // edi
  char v9; // al
  bool v10; // cc
  int v11; // esi
  int *v12; // ebp
  CCBStageRole *Role; // ecx
  int v14; // [esp+0x10] [ebp-0x48]
  int *v15; // [esp+0x14] [ebp-0x44]
  int *v16; // [esp+0x18] [ebp-0x40]
  int v17; // [esp+0x1C] [ebp-0x3C]
  int v18; // [esp+0x20] [ebp-0x38]
  _DWORD pOut[11]; // [esp+0x2C] [ebp-0x2C] BYREF
  char v21; // [esp+0x60] [ebp+0x8]
  int v22; // [esp+0x64] [ebp+0xC]

  memset(pOut, 0, sizeof(pOut));
  v14 = 0;
  v18 = -1;
  v3 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  v5 = 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 260;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  v6 = (char *)this + 892 * roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v17 = 0;
  v16 = (int *)&dword_17AA050;
  v15 = (int *)(v6 + 712);
  while ( 1 )
  {
    v7 = (unsigned long)*v15;
    if ( *v15 )
    {
      if ( v6[v5 + 736] )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v15);
        if ( !*(_BYTE *)(RoleNum + 4) && (((PAL_GDB *)this))->PAL_GDB::IsRoleDead(v7) )
        {
          v9 = *(_BYTE *)(RoleNum + 577);
          if ( v21 == 1 )
          {
            if ( v9 != 4 )
              goto LABEL_15;
          }
          else if ( v9 != 3 )
          {
            goto LABEL_15;
          }
          pOut[1] = v7;
          if ( this->CCBRoleState::GetRoleAI(pOut) )
          {
            *v16 = v7;
            ++v14;
            ++v16;
          }
        }
      }
    }
LABEL_15:
    v5 = v17 + 1;
    v10 = ++v17 < 6;
    ++v15;
    if ( !v10 )
      break;
    v6 = (char *)this + 892 * roleIdx;
  }
  result = v14;
  if ( v14 )
  {
    v11 = 0;
    if ( v14 <= 0 )
      return 0;
    v12 = (int *)&dword_17AA050;
    do
    {
      Role = (((CCBStage *)this))->CCBStage::GetRole(roleIdx) /* [ROWTABLE] */;
      if ( (int)abs32((int)Role - v22) < v3 )
      {
        v18 = v11;
        v3 = abs32(abs32((int)Role) - abs32(v22));
      }
      ++v11;
      ++v12;
    }
    while ( v11 < v14 );
    if ( v18 == -1 )
      return 0;
    else
      return *(&dword_17AA050 + v18);
  }
  return result;
}

// 0x004F5970
int CCBRoleState::ProcessSkillEffect(int roleIdx)
{
  CCBRoleState *v2; // ebp
  int v3; // edi
  int v5; // ebx
  int v6; // esi
  char v7; // al
  unsigned int v8; // ebp
  unsigned int v9; // ecx
  __int64 v10; // rax
  signed int v12; // [esp+0x14] [ebp-0x88]
  int v13; // [esp+0x18] [ebp-0x84]
  int SlotCount; // [esp+0x1C] [ebp-0x80]
  _DWORD v15[11]; // [esp+0x20] [ebp-0x7C] BYREF
  _BYTE v16[12]; // [esp+0x4C] [ebp-0x50] BYREF
  unsigned int pdwVal[11]; // [esp+0x58] [ebp-0x44] BYREF
  _BYTE pOut[12]; // [esp+0x84] [ebp-0x18] BYREF
  _BYTE v19[12]; // [esp+0x90] [ebp-0xC] BYREF
  char v20; // [esp+A4h] [ebp+0x8]
  int v21; // [esp+A8h] [ebp+0xC]
memset(v15, 0, sizeof(v15));
  v3 = roleIdx;
  v13 = -1;
  v12 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  v5 = 0;
  LOBYTE(v15[10]) = 1;
  v15[0] = 262;
  v15[1] = 0;
  v15[2] = roleIdx;
  v15[3] = -1;
  LOWORD(v15[4]) = 0;
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  while ( 1 )
  {
    if ( *((int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v19);
      v15[1] = v6;
      if ( (((CCBRoleState *)this))->CCBRoleState::GetRoleAI(v15) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v16) + 2) + 629);
        if ( v20 )
        {
          if ( v7 == 1 || v7 == 3 )
            goto LABEL_21;
        }
        else if ( v7 == 2 || v7 == 4 )
        {
          goto LABEL_21;
        }
        if ( (((PAL_GDB *)this))->PAL_GDB::GetSkillLevel(v6) )
        {
          v8 = (((CCBRoleState *)this))->CCBRoleState::CalcSkillDamage(v3, v6);
          memset(pdwVal, 0, sizeof(pdwVal));
          pdwVal[0] = 262;
          pdwVal[1] = v6;
          if ( (((CCBStage *)this))->CCBStage::CheckGDBTypeCompat(pdwVal) /* [ROWTABLE] */ )
            v8 += 100000;
          v9 = abs32(v8);
          if ( (int)abs32(v9 - v21) < v12 )
          {
            v13 = v5;
            v10 = (int)(v9 - abs32(v21));
            v12 = (HIDWORD(v10) ^ v10) - HIDWORD(v10);
          }
}
      }
    }
LABEL_21:
    if ( ++v5 >= SlotCount )
      break;
    v3 = roleIdx;
  }
  if ( v13 == -1 )
    return 0;
  else
    return *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v16);
}

// 0x004F5B70
int CCBRoleState::ProcessItemEffect(int roleIdx)
{
  signed int v3; // esi
  int i; // edi
  int v6; // ebp
  char v7; // al
  unsigned int v8; // ecx
  int v9; // [esp+0x10] [ebp-0x58]
  int SlotCount; // [esp+0x14] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x18] [ebp-0x50] BYREF
  _BYTE v12[12]; // [esp+0x24] [ebp-0x44] BYREF
  _BYTE v13[12]; // [esp+0x30] [ebp-0x38] BYREF
  _DWORD v14[11]; // [esp+0x3C] [ebp-0x2C] BYREF
  char v15; // [esp+0x70] [ebp+0x8]
  int v16; // [esp+0x74] [ebp+0xC]

  memset(v14, 0, sizeof(v14));
  v9 = -1;
  v3 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(v14[10]) = 1;
  v14[0] = 262;
  v14[1] = 0;
  v14[2] = roleIdx;
  v14[3] = -1;
  LOWORD(v14[4]) = 0;
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  for ( i = 0; i < SlotCount; ++i )
  {
    if ( *((int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v12);
      v14[1] = v6;
      if ( this->CCBRoleState::GetRoleAI(v14) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v13) + 2) + 629);
        if ( v15 )
        {
          if ( v7 == 1 || v7 == 3 )
            continue;
        }
        else if ( v7 == 2 || v7 == 4 )
        {
          continue;
        }
        if ( (((PAL_GDB *)this))->PAL_GDB::IsSkillUsable(v6) )
        {
          v8 = abs32(this->CCBRoleState::CalcSpellDamage(roleIdx, v6));
          if ( (int)abs32(v8 - v16) < v3 )
          {
            v9 = i;
            v3 = abs32(v8 - abs32(v16));
          }
        }
      }
    }
  }
  if ( v9 == -1 )
    return 0;
  else
    return *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v13);
}

// 0x004F5D00
int CCBRoleState::AISelectMagic(unsigned int roleIdx, char pData, int nVal)
{
  unsigned int v4; // ebx
  int v7; // eax
  int v8; // ebp
  int v9; // eax
  unsigned int v10; // esi
  int RoleNum; // edi
  int v12; // ebp
  int v13; // esi
  unsigned int v14; // edi
  int v15; // ebx
  bool v16; // cc
  int v17; // edi
  int *v18; // esi
  unsigned int v19; // ebp
  __int64 v20; // rax
  int v21; // eax
  int v22; // [esp+0x10] [ebp-0x4C]
  int *v24; // [esp+0x18] [ebp-0x44]
  int v25; // [esp+0x1C] [ebp-0x40]
  int v26; // [esp+0x20] [ebp-0x3C]
  int *v27; // [esp+0x24] [ebp-0x38]
  unsigned int *v28; // [esp+0x24] [ebp-0x38]
  int v29; // [esp+0x28] [ebp-0x34]
  int v30; // [esp+0x2C] [ebp-0x30]
  unsigned int pdwVal[11]; // [esp+0x30] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x60] [ebp+0x4]

  v4 = roleIdx;
  memset(pdwVal, 0, sizeof(pdwVal));
  v22 = 0;
  v30 = -1;
  v29 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 261;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  v7 = this->CCBRoleState::GetRoleHP(roleIdx) - 1;
  if ( v7 )
  {
    if ( v7 != 1 )
      return 0;
    roleIdxa = (int *)&dword_17A9F50;
    v8 = 760;
    v27 = (int *)&this->m_pObjMsgBuffer[892 * v4 + 128];
    while ( 1 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*v27);
      v10 = *(_DWORD *)(v9 + v8);
      if ( v10 )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(_DWORD *)(v9 + v8));
        if ( *(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v10;
          if ( (((CCBStage *)this))->CCBStage::CheckGDBTypeCompat(pdwVal) /* [ROWTABLE] */ )
          {
            if ( pData == 1 )
            {
              if ( *(_BYTE *)(RoleNum + 577) == 2 )
                goto LABEL_15;
            }
            else if ( !pData && *(_BYTE *)(RoleNum + 577) == 1 )
            {
LABEL_15:
              if ( this->CCBRoleState::GetRoleAI(pdwVal) )
              {
                *roleIdxa = v10;
                ++v22;
                ++roleIdxa;
              }
            }
          }
        }
      }
      v8 += 4;
      if ( v8 >= 776 )
      {
        if ( !v22 )
          return 0;
LABEL_37:
        v17 = 0;
        if ( v22 <= 0 )
          return 0;
        v18 = (int *)&dword_17A9F50;
        v19 = abs32(nVal);
        do
        {
          v20 = (int)(abs32((int)(((CCBStage *)this))->CCBStage::GetRole(v4) /* [ROWTABLE] */) - v19);
          v21 = (HIDWORD(v20) ^ v20) - HIDWORD(v20);
          if ( v21 < v29 )
          {
            v29 = v21;
            v30 = v17;
          }
          ++v17;
          ++v18;
        }
        while ( v17 < v22 );
        if ( v30 == -1 )
          return 0;
        else
          return *(&dword_17A9F50 + v30);
      }
    }
  }
  v25 = 0;
  v26 = 936;
  do
  {
    v12 = 0;
    v13 = 892 * v4;
    v28 = (unsigned int *)(4 * v22 + 24813392);
    v24 = (int *)&this->m_pObjMsgBuffer2[892 * v4 + 64 + v25];
    do
    {
      v14 = (unsigned long)*v24;
      if ( *v24 && *((_BYTE *)((UIWnd *)this) + v12 + v13 + v26) )
      {
        v15 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v24);
        pdwVal[1] = v14;
        if ( (((CCBStage *)this))->CCBStage::CheckGDBTypeCompat(pdwVal) /* [ROWTABLE] */ )
        {
          if ( pData == 1 )
          {
            if ( *(_BYTE *)(v15 + 577) != 2 )
              goto LABEL_32;
          }
          else if ( pData || *(_BYTE *)(v15 + 577) != 1 )
          {
            goto LABEL_32;
          }
          if ( this->CCBRoleState::GetRoleAI(pdwVal) )
          {
            *v28 = v14;
            ++v22;
            ++v28;
          }
        }
LABEL_32:
        v4 = roleIdx;
      }
      ++v12;
      ++v24;
    }
    while ( v12 < 8 );
    v16 = v26 + 8 < 984;
    v25 += 32;
    v26 += 8;
  }
  while ( v16 );
  if ( v22 )
    goto LABEL_37;
  return 0;
}

// 0x004F6000
int CCBRoleState::AISelectHealItem(unsigned int roleIdx, char pData, int nVal)
{
  signed int v4; // ebp
  int result; // eax
  int v6; // ebx
  char *v7; // eax
  unsigned int v8; // esi
  int RoleNum; // edi
  char v10; // al
  int v11; // esi
  int *v12; // ebx
  CCBStageRole *Role; // ecx
  int v15; // [esp+0x14] [ebp-0x40]
  int *v16; // [esp+0x18] [ebp-0x3C]
  int *v17; // [esp+0x1C] [ebp-0x38]
  int v18; // [esp+0x20] [ebp-0x34]
  unsigned int pdwVal[11]; // [esp+0x28] [ebp-0x2C] BYREF

  memset(pdwVal, 0, sizeof(pdwVal));
  v15 = 0;
  v18 = -1;
  v4 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  pdwVal[3] = -1;
  v6 = 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 260;
  v7 = (char *)this + 892 * roleIdx;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  LOWORD(pdwVal[4]) = 0;
  v17 = (int *)&g_AISelectHealItems;
  v16 = (int *)(v7 + 712);
  while ( 1 )
  {
    v8 = (unsigned long)*v16;
    if ( *v16 )
    {
      if ( v7[v6 + 736] )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v16);
        if ( !*(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v8;
          if ( (((CCBStage *)this))->CCBStage::CheckGDBTypeCompat(pdwVal) /* [ROWTABLE] */ )
          {
            v10 = *(_BYTE *)(RoleNum + 577);
            if ( pData == 1 )
            {
              if ( v10 != 2 )
                goto LABEL_15;
            }
            else if ( v10 != 1 )
            {
              goto LABEL_15;
            }
            if ( this->CCBRoleState::GetRoleAI(pdwVal) )
            {
              *v17 = v8;
              ++v15;
              ++v17;
            }
          }
        }
      }
    }
LABEL_15:
    ++v6;
    ++v16;
    if ( v6 >= 6 )
      break;
    v7 = (char *)this + 892 * roleIdx;
  }
  result = v15;
  if ( v15 )
  {
    v11 = 0;
    if ( v15 <= 0 )
      return 0;
    v12 = (int *)&g_AISelectHealItems;
    do
    {
      Role = (((CCBStage *)this))->CCBStage::GetRole(roleIdx) /* [ROWTABLE] */;
      if ( (int)abs32((int)Role - nVal) < v4 )
      {
        v18 = v11;
        v4 = abs32(abs32((int)Role) - abs32(nVal));
      }
      ++v11;
      ++v12;
    }
    while ( v11 < v15 );
    if ( v18 == -1 )
      return 0;
    else
      return *(&g_AISelectHealItems + v18);
  }
  return result;
}

// 0x004F61D0
int CCBRoleState::AISelectTarget(unsigned int roleIdx, char pData, int nVal)
{
  signed int v4; // edi
  int i; // esi
  int v7; // ebp
  char v8; // al
  unsigned int v9; // ecx
  int v11; // [esp+0x10] [ebp-0x58]
  int SlotCount; // [esp+0x14] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x18] [ebp-0x50] BYREF
  _BYTE v14[12]; // [esp+0x24] [ebp-0x44] BYREF
  _BYTE v15[12]; // [esp+0x30] [ebp-0x38] BYREF
  unsigned int pdwVal[11]; // [esp+0x3C] [ebp-0x2C] BYREF

  memset(pdwVal, 0, sizeof(pdwVal));
  v11 = -1;
  v4 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 262;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  for ( i = 0; i < SlotCount; ++i )
  {
    if ( *((int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut) + 1) <= 0 )
      continue;
    v7 = *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v14);
    v8 = *(_BYTE *)(*((_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v15) + 2) + 629);
    if ( pData )
    {
      if ( v8 == 1 || v8 == 3 )
        continue;
    }
    else if ( v8 == 2 || v8 == 4 )
    {
      continue;
    }
    pdwVal[1] = v7;
    if ( (((CCBStage *)this))->CCBStage::CheckGDBTypeCompat(pdwVal) /* [ROWTABLE] */ )
    {
      if ( this->CCBRoleState::GetRoleAI(pdwVal) )
      {
        v9 = abs32(this->CCBRoleState::CalcSpellDamage(roleIdx, v7));
        if ( (int)abs32(v9 - nVal) < v4 )
        {
          v11 = i;
          v4 = abs32(v9 - abs32(nVal));
        }
      }
    }
  }
  if ( v11 == -1 )
    return 0;
  else
    return *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v15);
}

// 0x004F6370
int CCBRoleState::AISelectSkill(unsigned int roleIdx, int nVal, char pData)
{
  unsigned int v4; // ebx
  CCBRoleState *v5; // ebp
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // esi
  int RoleNum; // edi
  int v12; // ebp
  int v13; // esi
  unsigned int v14; // edi
  int v15; // ebx
  bool v16; // cc
  int v17; // esi
  int *v18; // edi
  CCBStageRole *Role; // ecx
  int v20; // [esp+0x10] [ebp-0x4C]
  int *v22; // [esp+0x18] [ebp-0x44]
  int v23; // [esp+0x1C] [ebp-0x40]
  int v24; // [esp+0x20] [ebp-0x3C]
  int v25; // [esp+0x20] [ebp-0x3C]
  unsigned int *v26; // [esp+0x24] [ebp-0x38]
  signed int v27; // [esp+0x28] [ebp-0x34]
  int v28; // [esp+0x2C] [ebp-0x30]
  unsigned int pdwVal[11]; // [esp+0x30] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x60] [ebp+0x4]

  v4 = roleIdx;
memset(pdwVal, 0, sizeof(pdwVal));
  v20 = 0;
  v28 = -1;
  v27 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 261;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  v7 = (((CCBRoleState *)this))->CCBRoleState::GetRoleHP(roleIdx) - 1;
  if ( v7 )
  {
    if ( v7 != 1 )
      return 0;
    v8 = 760;
    roleIdxa = (int *)&g_AISelectSkills;
    v24 = 760;
    while ( 1 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)&this->m_pObjMsgBuffer[892 * v4 + 128]);
      v10 = *(_DWORD *)(v8 + v9);
      if ( v10 )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v10);
        if ( *(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v10;
          if ( (((PAL_GDB *)this))->PAL_GDB::IsRoleSkillValid(pdwVal, nVal) )
          {
            if ( pData == 1 )
            {
              if ( *(_BYTE *)(RoleNum + 577) == 2 )
                goto LABEL_15;
            }
            else if ( !pData && *(_BYTE *)(RoleNum + 577) == 1 )
            {
LABEL_15:
              if ( (((CCBRoleState *)this))->CCBRoleState::GetRoleAI(pdwVal) )
              {
                *roleIdxa = v10;
                ++v20;
                ++roleIdxa;
              }
            }
          }
        }
      }
      v8 = v24 + 4;
      v24 += 4;
      if ( v24 >= 776 )
      {
        if ( !v20 )
          return 0;
LABEL_38:
        v17 = 0;
        if ( v20 <= 0 )
          return 0;
        v18 = (int *)&g_AISelectSkills;
        do
        {
          Role = (((CCBStage *)this))->CCBStage::GetRole(v4);
          if ( (int)abs32((int)Role) < v27 )
          {
            v28 = v17;
            v27 = abs32(abs32((int)Role));
          }
          ++v17;
          ++v18;
        }
        while ( v17 < v20 );
        if ( v28 == -1 )
          return 0;
        else
          return *(&g_AISelectSkills + v28);
      }
    }
  }
  v23 = 0;
  v25 = 936;
  do
  {
    v12 = 0;
    v13 = 892 * v4;
    v26 = (unsigned int *)(4 * v20 + 24812880);
    v22 = (int *)&this->m_pObjMsgBuffer2[892 * v4 + 64 + v23];
    do
    {
      v14 = (unsigned long)*v22;
      if ( *v22 && *((_BYTE *)((UIWnd *)this) + v12 + v13 + v25) )
      {
        v15 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v22);
        pdwVal[1] = v14;
        if ( (((PAL_GDB *)this))->PAL_GDB::IsRoleSkillValid(pdwVal, nVal) )
        {
          if ( pData == 1 )
          {
            if ( *(_BYTE *)(v15 + 577) != 2 )
              goto LABEL_32;
          }
          else if ( pData || *(_BYTE *)(v15 + 577) != 1 )
          {
            goto LABEL_32;
          }
          if ( this->CCBRoleState::GetRoleAI(pdwVal) )
          {
            *v26 = v14;
            ++v20;
            ++v26;
          }
        }
LABEL_32:
        v4 = roleIdx;
      }
      ++v12;
      ++v22;
    }
    while ( v12 < 8 );
    v16 = v25 + 8 < 984;
    v23 += 32;
    v25 += 8;
  }
  while ( v16 );
  if ( v20 )
  {
goto LABEL_38;
  }
  return 0;
}

// 0x004F6690
int CCBRoleState::AISelectItemForSkill(unsigned int roleIdx, int nSkillID, char pData)
{
  int v7; // ebx
  char *v8; // eax
  unsigned int v9; // esi
  int RoleNum; // edi
  char v11; // al
  int v12; // esi
  int *v13; // edi
  CCBStageRole *Role; // ecx
  int v15; // [esp+0x10] [ebp-0x44]
  int *v17; // [esp+0x18] [ebp-0x3C]
  signed int v18; // [esp+0x1C] [ebp-0x38]
  int v19; // [esp+0x20] [ebp-0x34]
  char *v20; // [esp+0x24] [ebp-0x30]
  unsigned int pdwVal[11]; // [esp+0x28] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x58] [ebp+0x4]

  memset(pdwVal, 0, sizeof(pdwVal));
  v15 = 0;
  v19 = -1;
  v18 = 0x7FFFFFFF;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  pdwVal[3] = -1;
  v7 = 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 260;
  pdwVal[1] = 0;
  v8 = (char *)this + 892 * roleIdx;
  pdwVal[2] = roleIdx;
  LOWORD(pdwVal[4]) = 0;
  v17 = (int *)&g_AISelectItems;
  v20 = (char *)v8;
  roleIdxa = (int *)(v8 + 712);
  while ( 1 )
  {
    v9 = (unsigned long)*roleIdxa;
    if ( *roleIdxa )
    {
      if ( v8[v7 + 736] )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*roleIdxa);
        if ( !*(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v9;
          if ( (((PAL_GDB *)this))->PAL_GDB::IsRoleSkillValid(pdwVal, nSkillID) )
          {
            v11 = *(_BYTE *)(RoleNum + 577);
            if ( pData == 1 )
            {
              if ( v11 != 2 )
                goto LABEL_15;
            }
            else if ( v11 != 1 )
            {
              goto LABEL_15;
            }
            if ( this->CCBRoleState::GetRoleAI(pdwVal) )
            {
              *v17 = v9;
              ++v15;
              ++v17;
            }
          }
        }
      }
    }
LABEL_15:
    ++v7;
    ++roleIdxa;
    if ( v7 >= 6 )
      break;
    v8 = (char *)v20;
  }
  if ( !v15 )
    return 0;
  v12 = 0;
  if ( v15 <= 0 )
    return 0;
  v13 = (int *)&g_AISelectItems;
  do
  {
    Role = (((CCBStage *)this))->CCBStage::GetRole(roleIdx) /* [ROWTABLE] */;
    if ( (int)abs32((int)Role) < v18 )
    {
      v19 = v12;
      v18 = abs32(abs32((int)Role));
    }
    ++v12;
    ++v13;
  }
  while ( v12 < v15 );
  if ( v19 == -1 )
    return 0;
  else
    return *(&g_AISelectItems + v19);
}

// 0x004F6860
int CCBRoleState::AISelectSkillTarget(unsigned int roleIdx, int nSkillID, char pData)
{
  signed int v5; // ebp
  int i; // esi
  int v8; // edi
  char v9; // al
  int v10; // ecx
  int v11; // [esp+0x10] [ebp-0x58]
  int SlotCount; // [esp+0x14] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x18] [ebp-0x50] BYREF
  _BYTE v14[12]; // [esp+0x24] [ebp-0x44] BYREF
  _BYTE v15[12]; // [esp+0x30] [ebp-0x38] BYREF
  unsigned int pdwVal[11]; // [esp+0x3C] [ebp-0x2C] BYREF

  v5 = 0x7FFFFFFF;
  memset(pdwVal, 0, sizeof(pdwVal));
  v11 = -1;
  if ( !this->CCBRoleState::IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 262;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  for ( i = 0; i < SlotCount; ++i )
  {
    if ( *((int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut) + 1) <= 0 )
      continue;
    v8 = *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v14);
    v9 = *(_BYTE *)(*((_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v15) + 2) + 629);
    if ( pData )
    {
      if ( v9 == 1 || v9 == 3 )
        continue;
    }
    else if ( v9 == 2 || v9 == 4 )
    {
      continue;
    }
    pdwVal[1] = v8;
    if ( (((PAL_GDB *)this))->PAL_GDB::IsRoleSkillValid(pdwVal, nSkillID) )
    {
      if ( this->CCBRoleState::GetRoleAI(pdwVal) )
      {
        v10 = abs32(this->CCBRoleState::CalcSpellDamage(roleIdx, v8));
        if ( (int)abs32(v10) < v5 )
        {
          v11 = i;
          v5 = abs32(v10);
        }
      }
    }
  }
  if ( v11 == -1 )
    return 0;
  else
    return *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v15);
}

// 0x004F6DA0
char CCBRoleState::ValidateCommandTarget(int *pCmd)
{
  unsigned int v2; // eax
  int v3; // edx
  char *j; // eax
  int v6; // edi
  int v7; // edx
  char *v8; // esi
  int v9; // ecx
  int v10; // eax
  _DWORD *i; // eax

  v2 = (unsigned long)pCmd[2];
  if ( v2 > 4 )
  {
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)&this->m_pObjMsgBuffer[892 * v2 + 128]);
    v9 = 0;
    for ( i = (_DWORD *)(v10 + 760); *i != pCmd[1]; ++i )
    {
      if ( ++v9 >= 4 )
        return 0;
    }
  }
  else if ( *pCmd == 260 )
  {
    v3 = 0;
    for ( j = &this->m_pObjMsgBuffer2[892 * v2 + 32]; *(_DWORD *)j != (unsigned long)pCmd[1]; j += 4 )
    {
      if ( ++v3 >= 6 )
        return 0;
    }
  }
  else
  {
    v6 = 0;
LABEL_8:
    v7 = 0;
    v8 = (char *)&this->m_pObjMsgBuffer2[892 * v2 + 64 + v6];
    while ( *(_DWORD *)v8 != (unsigned long)pCmd[1] )
    {
      ++v7;
      v8 += 4;
      if ( v7 >= 8 )
      {
        v6 += 32;
        if ( v6 < 192 )
          goto LABEL_8;
        return 0;
      }
    }
  }
  return 1;
}

// 0x004F7200
char CCBRoleState::CheckEventCondition(int pEvent)
{
  int RoleNum; // esi
  char *v4; // ecx
  char result; // al
  int v6; // ebp
  bool v7; // cc
  int updated; // esi
  int v9; // [esp-0x4] [ebp-0x1C]
  int p_DWORD[3]; // [esp+0xC] [ebp-0xC] BYREF

  v9 = *(_DWORD *)(pEvent + 4);
  p_DWORD[0] = 0xFFFF;
  p_DWORD[1] = 0;
  p_DWORD[2] = 0;
  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v9);
  v4 = (char *)this + 892 * *(_DWORD *)(pEvent + 8);
  if ( !v4[578] )
    return 0;
  switch ( *(_DWORD *)(RoleNum + 696) )
  {
    case 0xFFFFFFFF:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
      goto LABEL_31;
    case 0:
      if ( *((_DWORD *)v4 + 147) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 1:
      if ( *((_DWORD *)v4 + 149) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 2:
      if ( *((_DWORD *)v4 + 151) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 3:
      if ( this->CCBRoleState::GetAttackBonus(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 4:
      if ( this->CCBRoleState::GetDefenseBonus(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 5:
      if ( *((_DWORD *)v4 + 157) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 6:
      if ( *((_DWORD *)v4 + 176) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 7:
      if ( this->CCBRoleState::GetSpeedBonus(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 8:
      if ( this->CCBRoleState::GetRoleState(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 9:
      if ( *((_DWORD *)v4 + 146) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 0xA:
      if ( this->CCBRoleState::GetTotalRounds() < *(_DWORD *)(RoleNum + 704) )
        return 0;
      v6 = *(_DWORD *)(pEvent + 4);
      if ( v6 == 4102 )
      {
        updated = this->CCBRoleState::UpdateRoleMP(1);
        v7 = this->CCBRoleState::GetTotalRounds() < 2 * updated * (*(_DWORD *)&this->m_pObjMsgBuffer[160] + 20);
      }
      else
      {
        if ( v6 != 4305 )
          goto LABEL_31;
        v7 = this->CCBRoleState::GetTotalRounds() < 1000;
      }
      if ( v7 )
        return 0;
LABEL_31:
      result = 1;
      break;
    case 0x10:
      p_DWORD[0] = 6113;
      if ( !(((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(p_DWORD) )
        return 0;
      goto LABEL_31;
    default:
      return 0;
  }
  return result;
}

// 0x004F7480
char CCBRoleState::CheckMagicCost(int *p_DWORD)
{
  int RoleNum; // eax

  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(p_DWORD[1]);
  if ( *p_DWORD == 260 )
  {
    if ( *(_DWORD *)(RoleNum + 688) > *(_DWORD *)&this->m_pObjMsgBuffer[892 * p_DWORD[2] + 172] )
      return 0;
  }
  else if ( *p_DWORD == 261 && *(_DWORD *)(RoleNum + 692) > *(_DWORD *)&this->m_pObjMsgBuffer[892 * p_DWORD[2] + 180] )
  {
    return 0;
  }
  return 1;
}

// 0x004F7500
char CCBRoleState::GetRoleAI(void *pOut)
{
  int v3; // eax
  char v4; // dl
  char *v5; // ecx
  char result; // al

  v3 = *((_DWORD *)pOut + 2);
  v4 = this->m_pObjMsgBuffer[892 * v3 + 154];
  v5 = (char *)this + 892 * v3;
  if ( !v4 )
    return 0;
  if ( v5[1432] )
    return 0;
  this->CCBRoleState::GetRoleHP(*((_DWORD *)pOut + 2));
  result = (((PAL_GDB *)this))->PAL_GDB::IterateInventory((int *)pOut);
  if ( result )
  {
    switch ( *(_DWORD *)pOut )
    {
      case 0x104:
        result = this->CCBRoleState::ValidateCommandTarget((int *)pOut);
        if ( !result )
          return result;
        result = this->CCBRoleState::CheckMagicCost((int *)pOut);
        if ( !result )
          return result;
        result = this->CCBRoleState::CheckEventCondition((int)pOut);
        if ( !result )
          return result;
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*((_DWORD *)pOut + 1));
        break;
      case 0x105:
        result = this->CCBRoleState::ValidateCommandTarget((int *)pOut);
        if ( !result )
          return result;
        result = this->CCBRoleState::CheckMagicCost((int *)pOut);
        if ( !result )
          return result;
        result = this->CCBRoleState::CheckEventCondition((int)pOut);
        if ( !result )
          return result;
        if ( this->CCBRoleState::GetRoleField(*((_DWORD *)pOut + 2), 15) )
          return 0;
        if ( *((_DWORD *)pOut + 1) == 7710 )
        {
          if ( this->CCBRoleState::UpdateRoleMP(2) != 1 )
            return 0;
          if ( *((_BYTE *)((SceneObj *)this) + 5038) && !*((_BYTE *)((SceneObj *)this) + 5892) )
            return 0;
          if ( *((_BYTE *)((SceneObj *)this) + 6822) && !this->m_byteFlags )
            return 0;
        }
        break;
      case 0x106:
        result = (((PAL_GDB *)this))->PAL_GDB::BuildItemArray((int)pOut);
        if ( result )
        {
          if ( this->CCBRoleState::GetRoleField(*((_DWORD *)pOut + 2), 16) )
          {
            return 0;
          }
          else if ( !(((CCBSystem *)this))->CCBSystem::IsMagicSlotMsg((int)pOut)
                 || (result = (((CCBSystem *)this))->CCBSystem::HandleMagicCommand((int)pOut)) != 0 )
          {
            (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*((_DWORD *)pOut + 1));
            return 1;
          }
        }
        return result;
      default:
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004F76C0
int CCBRoleState::GetSkillCostLevel(unsigned int dwSlot, int nSkillID)
{
  int v4; // ebx
  int v5; // edx
  char *v6; // edi
  int v8; // eax
  int v9; // ecx
  _DWORD *v10; // edx
  int v11; // [esp+0x10] [ebp-0x4]
  unsigned int dwSlota; // [esp+0x18] [ebp+0x4]

  if ( dwSlot > 4 )
  {
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)&this->m_pObjMsgBuffer[892 * dwSlot + 128]);
    v9 = 0;
    v10 = (_DWORD *)(v8 + 760);
    do
    {
      if ( *v10 == nSkillID )
        return *(unsigned __int8 *)(v8 + v9 + 776);
      ++v9;
      ++v10;
    }
    while ( v9 < 3 );
    if ( *(_DWORD *)(v8 + 772) == nSkillID )
      return 4;
    else
      return nSkillID == 207 || nSkillID == 215 || nSkillID == 232 || nSkillID == 224 || nSkillID == 240;
  }
  else
  {
    v11 = 0;
    dwSlota = 0;
    v4 = 936;
    while ( 2 )
    {
      v5 = 0;
      v6 = (char *)&this->m_pObjMsgBuffer2[892 * dwSlot + 64 + dwSlota];
      do
      {
        if ( *(_DWORD *)v6 == nSkillID && *((_BYTE *)((UIWnd *)this) + 892 * dwSlot + v5 + v4) )
          return *((unsigned __int8 *)&this->m_mdl.box.trans.zz + 892 * dwSlot + 8 * v11 + v5) + 1;
        ++v5;
        v6 += 4;
      }
      while ( v5 < 8 );
      v4 += 8;
      ++v11;
      dwSlota += 32;
      if ( v4 < 984 )
        continue;
      break;
    }
    return 0;
  }
}

// 0x004F7820
char CCBRoleState::SumGPCost(int nVal)
{
  int v3; // edx
  char *i; // eax

  if ( *(_DWORD *)(nVal + 12) > 0xAu )
  {
    v3 = 0;
    for ( i = &this->m_pObjMsgBuffer[154]; !*(i - 1) || !*i || i[854] || i[853] || !*(_BYTE *)(v3 + nVal + 29); i += 892 )
    {
      if ( ++v3 >= 11 )
        return 0;
    }
  }
  return 1;
}

// 0x004F7880
unsigned int CCBRoleState::CheckStatus()
{
  char *v1; // ecx
  int v2; // edi
  int v3; // esi
  unsigned int result; // eax

  v1 = (char *)&this->m_pObjMsgBuffer[180];
  v2 = 11;
  do
  {
    *((_DWORD *)v1 - 4) &= (*((int *)v1 - 4) < 0) - 1;
    *((_DWORD *)v1 - 2) &= (*((int *)v1 - 2) < 0) - 1;
    *(_DWORD *)v1 &= (*(int *)v1 < 0) - 1;
    if ( *((int *)v1 - 4) <= 0 )
    {
      *(v1 - 26) = 0;
      v1[562] = 1;
      v1[561] = 0;
    }
    v3 = *((_DWORD *)v1 - 4);
    result = (unsigned int)((unsigned __int64)(1717986919i64 * *((int *)v1 - 3)) >> 32) >> 31;
    if ( v3 < *((_DWORD *)v1 - 3) / 10 && v3 > 0 )
      v1[561] = 1;
    v1 += 892;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004F7910
void * CCBRoleState::ProcessActions()
{
  int RoleIndex; // edi
  int v3; // edi
  char *v4; // ebx
  int v5; // ebx
  char *v6; // ebp
  CCBStage *v7; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // eax
  int v11; // edi
  void *result; // eax
  int v13; // ecx
  int v14; // [esp+0x0] [ebp-0x44]
  gbColorQuad v15; // [esp+0x4] [ebp-0x40]
  int v16; // [esp+0x10] [ebp-0x34]
  char *v17; // [esp+0x14] [ebp-0x30]
  _DWORD pData[11]; // [esp+0x18] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  if ( this->CCBRoleState::ApplyHitEffect(0) == 1
    && *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 120) == 2
    && !(((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::ForceDelTask(12) )
  {
    this->CCBRoleState::UpdateDefenceStats();
    RoleIndex = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(25, pData, 1);
    if ( RoleIndex != -1 )
    {
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FadeMusicOut) */, 0, 0, 0, 0, -1082130432, 1056964608);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskShowSkillLearned) */, 0, 0, 0, 0, -1082130432, 1084227584);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::CCBRoleState_Func) */, 0, 0, 0, 0, -1082130432, 1065353216);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FadeMusicIn) */, 0, 0, 0, 0, -1082130432, 1045220557);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
    }
    (((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 16)))->CCBCamControl::ClearFinishedTask(10);
    v3 = 24;
    v4 = (char *)&this->m_pObjMsgBuffer[153];
    *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 120) = 7;
    do
    {
      if ( *v4 )
      {
        *(_BYTE *)(*(_DWORD *)(v3 + *(_DWORD *)&this->m_pObjMsgBuffer[100]) + 280) = 0;
        *(_BYTE *)(*(_DWORD *)(v3 + *(_DWORD *)&this->m_pObjMsgBuffer[100]) + 274) = 0;
        (((CCBStage *)*(CCBStage **)(v3 + *(_DWORD *)&this->m_pObjMsgBuffer[100])))->CCBStage::TryRelease();
      }
      v3 += 4;
      v4 += 892;
    }
    while ( v3 < 68 );
  }
  if ( ((unsigned __int8)this->CCBRoleState::GetForce(0) == 1
     || *(_DWORD *)&this->m_pObjMsgBuffer[120] >= *(_DWORD *)&this->m_pObjMsgBuffer[116] && !this->m_pObjMsgBuffer[124])
    && *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 120) == 2
    && !(((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::ForceDelTask(12) )
  {
    this->CCBRoleState::ProcessControlInput();
    this->CCBRoleState::UpdateRoleMP(1, -1);
    (((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 16)))->CCBCamControl::ClearFinishedTask(3);
    v5 = 0;
    v6 = (char *)&this->m_pObjMsgBuffer[154];
    v16 = 0;
    v17 = (char *)&this->m_pObjMsgBuffer[154];
    do
    {
      if ( *(v6 - 1) )
      {
        if ( *v6 )
        {
          v7 = (CCBStage *)(*(CCBStage **)&this->m_pObjMsgBuffer[100]);
          pData[2] = v5;
          v8 = (((CCBStage *)v7))->CCBStage::GetRoleIndex(24, pData, 1);
          if ( v8 != -1 )
          {
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v8, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, 0, -1082130432, 0);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v8, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskReturnToIdle) */, 0, 0, 0, 0, -1082130432, 0);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v8, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, 0, -1082130432, 0);
            (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v8);
            v6 = (char *)v17;
            v5 = v16;
          }
        }
      }
      ++v5;
      v6 += 892;
      v16 = v5;
      v17 = (char *)v6;
    }
    while ( v5 < 5 );
    v9 = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(23, pData, 1);
    if ( v9 != -1 )
    {
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FadeMusicOut) */, 0, 0, 0, 0, -1082130432, 1056964608);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskShowLevelUp) */, 0, 0, 0, 0, -1082130432, 1077936128);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::GetCombatDialogEntry) */, 0, 0, 0, 0, -1082130432, 0x40000000);
      this->CCBRoleState::UpdateRoleMP(0, v9);
      this->CCBRoleState::CheckMPRequirement(v9);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::StartSubTask) */, 0, 0, 0, 0, -1082130432, 1084227584);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FadeMusicIn) */, 0, 0, 0, 0, -1082130432, 1045220557);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::CCBRoleState_Func) */, 0, 0, 0, 0, -1082130432, 1065353216);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v9);
      LOBYTE(v10) = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::EndTask(v9);
      this->m_nCurrentTaskID = v10;
    }
    this->CCBRoleState::SyncSkillCent();
    this->CCBRoleState::SavePartyData();
    (((C2DSpark *)*(C2DSpark **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 52)))->C2DSpark::CreateStars();
    (((C2DSpark *)1))->C2DSpark::CreateTrack(v14, v15);
    *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 120) = 5;
    (((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 20) + 20)))->CCBStageScene::Destroy();
  }
  if ( *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 120) == 4 )
  {
    this->CCBRoleState::UpdateRoleMP(1, -1);
    (((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 20) + 16)))->CCBCamControl::ClearFinishedTask(8);
    (((CCBAttackSequen *)*(CCBAttackSequen **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBAttackSequen::SetPause(1);
    StoreThreadFlag(*(_BYTE **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12), 0);
    (((CCBUI *)*(CCBUI **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 4)))->CCBUI::CreateMagicWindow();
    v11 = (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleIndex(23, pData, 1);
    if ( v11 != -1 )
    {
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v11, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::GetCombatDialogEntry) */, 0, 0, 0, 0, -1082130432, 0x40000000);
      this->CCBRoleState::UpdateRoleMP(0, v11);
      this->CCBRoleState::CheckMPRequirement(v11);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(v11, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::StartSubTask) */, 0, 0, 0, 0, -1082130432, 1097859072);
      (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(v11);
    }
    this->CCBRoleState::SavePartyData();
    *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 120) = 5;
    (((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 20) + 20)))->CCBStageScene::Destroy();
  }
  result = (void *)(*(void **)&this->m_pObjMsgBuffer[96]);
  v13 = *((_DWORD *)result + 30);
  if ( v13 == 5 )
  {
    result = (void *)(((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[100]))->CCBSystem::FindThreadByID(this->m_nCurrentTaskID);
    if ( (_BYTE)result )
      return result;
    *(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 124) = 2;
    return (void *)(((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::GetRenderFlag(1);
  }
  if ( v13 == 7 )
  {
    if ( *(int *)(*((_DWORD *)result + 5) + 156) > 0 )
      return result;
    *((_DWORD *)result + 31) = 3;
    return (void *)(((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::GetRenderFlag(1);
  }
  if ( v13 == 6 && *(int *)(*((_DWORD *)result + 5) + 156) <= 0 )
  {
    *((_DWORD *)result + 31) = 4;
    this->CCBRoleState::SyncSkillCent();
    return (void *)(((CCBSystem *)*(CCBSystem **)&this->m_pObjMsgBuffer[96]))->CCBSystem::GetRenderFlag(1);
  }
  return result;
}

// 0x004F7FC0
void CCBRoleState::ProcessCombatDialog(unsigned int dwVal)
{
  int v3; // esi
  char *v4; // ebp
  int v5; // ecx
  int v6; // edi
  CCBRoleState *v7; // ebx
  CCBStage *v8; // ecx
  int RoleIndex; // esi
  int nVal; // [esp+0x38] [ebp-0x39C]
  CIniFile v11; // [esp+0x3C] [ebp-0x398] BYREF
  CCBRoleState *v12; // [esp+0x44] [ebp-0x390]
  int v13; // [esp+0x48] [ebp-0x38C]
  int v14; // [esp+0x4C] [ebp-0x388]
  _DWORD pData[11]; // [esp+0x50] [ebp-0x384] BYREF
  int roleIdx[3]; // [esp+0x7C] [ebp-0x358] BYREF
  char v17[32]; // [esp+0x88] [ebp-0x34C] BYREF
  char v18[32]; // [esp+A8h] [ebp-0x32C] BYREF
  char v19[256]; // [esp+C8h] [ebp-0x30C] BYREF
  char v20[256]; // [esp+0x1C8] [ebp-0x20C] BYREF
  char Buffer[256]; // [esp+0x2C8] [ebp-0x10C] BYREF
  int v22; // [esp+0x3D0] [ebp-0x4]

  v3 = 0;
  ++*(_DWORD *)&g_TempBuffer1024[912];
v14 = 0;
  v13 = 0;
  g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
  memset(pData, 0, sizeof(pData));
  if ( !this->m_pObjMsgBuffer[92]
    || dwVal > 4
    || *(int *)&this->m_pObjMsgBuffer[892 * dwVal + 164] <= 0
    || *(float *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 80) - *(float *)&this->m_pObjMsgBuffer[88] < 10.0 )
  {
    return;
  }
  v22 = 0;
  (((CIniFile *)&v11))->CIniFile::OpenFileRead("datascript\\combat.ini");
  this->CCBRoleState::GetSlotActionType(dwVal, v18);
  sprintf(Buffer, "%s-CombatDialog", v18);
  (((CIniFile *)&v11))->CIniFile::ReadSection(Buffer);
  this->CCBRoleState::GetRoleMP(1);
  nVal = v14;
  if ( v14 >= v13 )
    goto LABEL_29;
  v4 = (char *)&this->m_pObjMsgBuffer[892 * v14 + 168];
  v5 = g_nCombatRandSeed;
  while ( 1 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    v5 = 214013 * v5 + 2531011;
    g_nCombatRandSeed = v5;
    v6 = ((v5 >> 16) & 0x7FFF) % 10;
    if ( *(v4 - 15) )
    {
      if ( *(v4 - 14) )
        break;
    }
LABEL_24:
    v4 += 892;
    if ( ++nVal >= v13 )
      goto LABEL_25;
  }
  (((CCBRoleState *)this))->CCBRoleState::GetSlotActionType(nVal, v17);
  if ( nVal != dwVal )
  {
    if ( *((_DWORD *)v4 - 1) < 3 * *(_DWORD *)v4 / 10 )
    {
      sprintf(v19, "%sHPLow%d", v17, v6);
      v3 = (((CIniFile *)&v11))->CIniFile::ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    goto LABEL_15;
  }
  if ( *((_DWORD *)v4 - 1) >= *(_DWORD *)v4 / 10
    || (sprintf(v19, "Dying%d", v6), v3 = (((CIniFile *)&v11))->CIniFile::ReadLine(v19, v20, 255), v3 != 1) )
  {
LABEL_15:
    if ( (((CCBRoleState *)this))->CCBRoleState::IsRoleInForce(nVal) )
    {
      sprintf(v19, "Poison%d", v6);
      v3 = (((CIniFile *)&v11))->CIniFile::ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    if ( v4[566] || v4[567] || v4[568] )
    {
      sprintf(v19, "%sSleep%d", v17, v6);
      v3 = (((CIniFile *)&v11))->CIniFile::ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    if ( *((_DWORD *)v4 + 1) == *((_DWORD *)v4 + 2) )
    {
      sprintf(v19, "GPFull%d", v6);
      v3 = (((CIniFile *)&v11))->CIniFile::ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    v5 = g_nCombatRandSeed;
    goto LABEL_24;
  }
LABEL_25:
  if ( !v3 )
    goto LABEL_29;
LABEL_26:
  v7 = (CCBRoleState *)v12;
  pData[2] = dwVal;
  strcpy((char *)this, (const char *)v20);
  pData[3] = dwVal;
  v8 = (CCBStage *)(*(CCBStage **)&v7->m_pObjMsgBuffer[100]);
  LOBYTE(pData[10]) = 1;
  pData[0] = 259;
  pData[1] = 0;
  LOWORD(pData[4]) = 0;
  RoleIndex = (((CCBStage *)v8))->CCBStage::GetRoleIndex(29, pData, 1);
  if ( RoleIndex != -1 )
  {
    (((CCBRoleState *)v7))->CCBRoleState::CheckRoleStatus((int)roleIdx);
    (((CCBStage *)*(CCBStage **)&v7->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcShowFiveLineup) */, 0, 0, 0, roleIdx, -1082130432, 0x40000000);
    (((CCBStage *)*(CCBStage **)&v7->m_pObjMsgBuffer[100]))->CCBStage::GetStageRoleByIdx(RoleIndex);
  }
  *(_DWORD *)&v7->m_pObjMsgBuffer[88] = *(_DWORD *)(*(_DWORD *)&v7->m_pObjMsgBuffer[96] + 80);
LABEL_29:
  v22 = -1;
  (((CIniFile *)&v11))->CIniFile::~CIniFile();
}

// 0x004F8480
int CCBRoleState::UpdateEffects()
{
  int i; // ebx
  int result; // eax
  int v4; // edi
  int v5; // eax
  int v6; // ecx
  char RoleField; // al
  void ( **v8)(int); // edx
  char v9; // al
  void ( **v10)(int); // edx
  char v11; // al
  void ( **v12)(int); // edx
  char v13; // al
  void ( **v14)(int); // edx
  char v15; // al
  void ( **v16)(int); // edx
  char v17; // al
  void ( **v18)(int); // edx
  char v19; // al
  void ( **v20)(int); // edx
  char v21; // al
  void ( **v22)(int); // edx
  char v23; // al
  void ( **v24)(int); // edx
  char v25; // al
  void ( **v26)(int); // edx
  char v27; // al
  void ( **v28)(int); // edx
  char v29; // al
  void ( **v30)(int); // edx
  char v31; // al
  void ( **v32)(int); // edx
  char v33; // al
  void ( **v34)(int); // edx
  char v35; // al
  void ( **v36)(int); // edx
  char v37; // al
  void ( **v38)(int); // edx
  char v39; // al
  void ( **v40)(int); // edx
  char v41; // al
  void ( **v42)(int); // edx
  char v43; // al
  int ( **v44)(int); // edx
  float fValue; // [esp+0x0] [ebp-0x30]
  float fValuea; // [esp+0x0] [ebp-0x30]
  float fValueb; // [esp+0x0] [ebp-0x30]
  float fValuec; // [esp+0x0] [ebp-0x30]
  float fValued; // [esp+0x0] [ebp-0x30]
  float fValuee; // [esp+0x0] [ebp-0x30]
  float fValuef; // [esp+0x0] [ebp-0x30]
  int fValueg; // [esp+0x0] [ebp-0x30]
  int fValueh; // [esp+0x0] [ebp-0x30]
  int *v54; // [esp+0x2C] [ebp-0x4]

  for ( i = 0; i < 5; ++i )
  {
    result = (int)this + 892 * i;
    v54 = (int *)result;
    if ( *(_BYTE *)(result + 577) )
    {
      v4 = *(unsigned __int8 *)(result + 576);
      fValue = (float)*(int *)(result + 592);
      (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 1020)))->UIScrollBar::SetRange(fValue);
      fValuea = (float)v54[150];
      (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 1036)))->UIScrollBar::SetRange(fValuea);
      fValueb = (float)v54[152];
      (((UIScrollBar *)*(UIScrollBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 1052)))->UIScrollBar::SetRange(fValueb);
      fValuec = (float)v54[147];
      (((UIProgressBar *)*(UIProgressBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 1020)))->UIProgressBar::FindChildByName(fValuec);
      fValued = (float)v54[149];
      (((UIProgressBar *)*(UIProgressBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 1036)))->UIProgressBar::FindChildByName(fValued);
      fValuee = (float)v54[151];
      (((UIProgressBar *)*(UIProgressBar **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 1052)))->UIProgressBar::FindChildByName(fValuee);
      if ( !i )
      {
        v5 = *(_DWORD *)&this->m_pObjMsgBuffer[104];
        if ( *(_DWORD *)(*(_DWORD *)(v5 + 120) + 56) == 1 )
        {
          fValuef = *(float *)&this->m_info.name[16] * 0.25f;
          (((UIProgressBar *)*(UIProgressBar **)(v5 + 1068)))->UIProgressBar::FindChildByName(fValuef);
          if ( *(int *)&this->m_pObjMsgBuffer[164] > 0 )
          {
            v6 = *(_DWORD *)&this->m_pObjMsgBuffer[96];
            if ( *(float *)(v6 + 80) - this->m_fTimeFund > 0.1 )
            {
              *(float *)&fValueg = *(float *)&this->m_info.name[16] * 0.1;
              (((C2DSpark *)*(C2DSpark **)(v6 + 52)))->C2DSpark::CreateMore(25, 570, 20, fValueg);
              if ( *(float *)&this->m_info.name[16] > 199.89999f )
              {
                *(float *)&fValueh = *(float *)&this->m_info.name[16] * 0.1;
                (((C2DSpark *)*(C2DSpark **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 52)))->C2DSpark::CreateMore(25, 570, 20, fValueh);
              }
              this->m_fTimeFund = *(float *)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 80);
            }
          }
        }
      }
      result = *(_DWORD *)&this->m_pObjMsgBuffer[104];
      if ( *(_DWORD *)(*(_DWORD *)(result + 4 * v4 + 120) + 56) == 1 )
      {
        CCBStage_AddTextLabel(*(&dword_17AA808 + v4) + 22);
        CCBStage_AddTextLabel(*(&dword_17AA828 + v4) + 31);
        CCBStage_AddTextLabel(*(&dword_17AA848 + v4) + 23);
        if ( this->CCBRoleState::GetRoleField(i, 3) )
        {
          (((NPC *)*(NPC **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * i + 136)))->NPC::UpdateAnim(-13002067);
        }
        else if ( this->CCBRoleState::GetRoleField(i, 4) )
        {
          (((NPC *)*(NPC **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * i + 136)))->NPC::UpdateAnim(-2198223);
        }
        else if ( this->CCBRoleState::GetRoleField(i, 2) )
        {
          (((NPC *)*(NPC **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * i + 136)))->NPC::UpdateAnim(-6002966);
        }
        else if ( this->CCBRoleState::GetRoleField(i, 1) )
        {
          (((NPC *)*(NPC **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * i + 136)))->NPC::UpdateAnim(-11356565);
        }
        else if ( this->CCBRoleState::GetRoleField(i, 5) )
        {
          (((NPC *)*(NPC **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * i + 136)))->NPC::UpdateAnim(-2707878);
        }
        else
        {
          (((NPC *)*(NPC **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * i + 136)))->NPC::UpdateAnim(-1);
        }
        if ( v54[147] <= 0 )
          (((NPC *)*(NPC **)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * i + 136)))->NPC::UpdateAnim(-11513776);
        RoleField = this->CCBRoleState::GetRoleField(i, 6);
        v8 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 176);
        if ( RoleField )
          (*v8)(1);
        else
          (*v8)(0);
        v9 = this->CCBRoleState::GetRoleField(i, 7);
        v10 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 220);
        if ( v9 )
          (*v10)(1);
        else
          (*v10)(0);
        v11 = this->CCBRoleState::GetRoleField(i, 8);
        v12 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 264);
        if ( v11 )
          (*v12)(1);
        else
          (*v12)(0);
        v13 = this->CCBRoleState::GetRoleField(i, 9);
        v14 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 308);
        if ( v13 )
          (*v14)(1);
        else
          (*v14)(0);
        v15 = this->CCBRoleState::GetRoleField(i, 12);
        v16 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 440);
        if ( v15 )
          (*v16)(1);
        else
          (*v16)(0);
        v17 = this->CCBRoleState::GetRoleField(i, 13);
        v18 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 484);
        if ( v17 )
          (*v18)(1);
        else
          (*v18)(0);
        v19 = this->CCBRoleState::GetRoleField(i, 10);
        v20 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 352);
        if ( v19 )
          (*v20)(1);
        else
          (*v20)(0);
        v21 = this->CCBRoleState::GetRoleField(i, 11);
        v22 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 396);
        if ( v21 )
          (*v22)(1);
        else
          (*v22)(0);
        v23 = this->CCBRoleState::GetRoleField(i, 14);
        v24 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 528);
        if ( v23 )
          (*v24)(1);
        else
          (*v24)(0);
        v25 = this->CCBRoleState::GetRoleField(i, 15);
        v26 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 572);
        if ( v25 )
          (*v26)(1);
        else
          (*v26)(0);
        v27 = this->CCBRoleState::GetRoleField(i, 16);
        v28 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 616);
        if ( v27 )
          (*v28)(1);
        else
          (*v28)(0);
        v29 = this->CCBRoleState::GetRoleField(i, 17);
        v30 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 660);
        if ( v29 )
          (*v30)(1);
        else
          (*v30)(0);
        v31 = this->CCBRoleState::GetRoleField(i, 18);
        v32 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 704);
        if ( v31 )
          (*v32)(1);
        else
          (*v32)(0);
        v33 = this->CCBRoleState::GetRoleField(i, 19);
        v34 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 748);
        if ( v33 )
          (*v34)(1);
        else
          (*v34)(0);
        v35 = this->CCBRoleState::GetRoleField(i, 20);
        v36 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 792);
        if ( v35 )
          (*v36)(1);
        else
          (*v36)(0);
        v37 = this->CCBRoleState::GetRoleField(i, 21);
        v38 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 836);
        if ( v37 )
          (*v38)(1);
        else
          (*v38)(0);
        v39 = this->CCBRoleState::GetRoleField(i, 22);
        v40 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 880);
        if ( v39 )
          (*v40)(1);
        else
          (*v40)(0);
        v41 = this->CCBRoleState::GetRoleField(i, 23);
        v42 = **(void ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 924);
        if ( v41 )
          (*v42)(1);
        else
          (*v42)(0);
        v43 = this->CCBRoleState::GetRoleField(i, 26);
        v44 = **(int ( ****)(int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * v4 + 968);
        if ( v43 )
          result = (*v44)(1);
        else
          result = (*v44)(0);
      }
    }
  }
  return result;
}

// 0x004F8AF0
void CCBRoleState::ProcessControlInput()
{
  unsigned __int8 *v2; // edi
  int v3; // ebp
  char *v4; // ebx
  CCBControl *v5; // ecx
  int v6; // [esp+0x0] [ebp-0x10]
  int v7; // [esp+0x4] [ebp-0xC]

  v2 = 0;
  v3 = 24;
  v4 = (char *)&this->m_pObjMsgBuffer[153];
  do
  {
    if ( *v4 )
    {
      *(float *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + v3) + 6632) = *(float *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + v3)
                                                                                             + 6636);
      *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + v3) + 280) = 0;
      this->CCBRoleState::ProcessRound((unsigned int)v2, 14, 0, 1);
      this->CCBRoleState::ProcessRound((unsigned int)v2, 17, 0, 1);
      this->CCBRoleState::ProcessRound((unsigned int)v2, 23, 0, 1);
      v5 = (CCBControl *)*(CCBControl **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 8);
      if ( v5->m_bActive )
      {
        if ( (unsigned __int8 *)(((CCBControl *)v5))->CCBControl::GetControl() == v2 )
          (((CCBControl *)*(CCBControl **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 8)))->CCBControl::GetState();
      }
      (((CCBStage *)v2))->CCBStage::IsTaskValidButNotFinish(v6, v7);
    }
    v3 += 4;
    ++v2;
    v4 += 892;
  }
  while ( v3 < 44 );
}

// 0x004F8BB0
int CCBRoleState::InitSlot(int idx, int nRoleID)
{
  char *v4; // ebp
  int v5; // eax
  int v6; // ecx
  char v7; // al
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  void ( ***v16)(_DWORD, int); // ecx
  int *v17; // eax
  int result; // eax
  int *idxa; // [esp+0x18] [ebp+0x4]

  v4 = (char *)this + 892 * idx;
  memset(v4 + 552, 0, 0x37Cu);
  v4[577] = 1;
  v4[578] = 1;
  v4[579] = 0;
  *((_DWORD *)v4 + 138) = nRoleID;
  *((_DWORD *)v4 + 348) = -1;
  *((_DWORD *)v4 + 284) = idx - 4;
  v4[1389] = 1;
  v4[1384] = 1;
  v4[1385] = 1;
  v4[1386] = 1;
  v4[1387] = 1;
  v4[1388] = 1;
  (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v4 + 138));
  v6 = v5;
  v4[580] = 0;
  v7 = *(_BYTE *)(v5 + 518);
  if ( v7 == 98 || v7 == 66 )
  {
    v4[580] = 1;
    v4[1167] = 1;
    *((_WORD *)v4 + 637) = 0x7FFF;
  }
  if ( *(_BYTE *)(v6 + 709) )
  {
    v4[1167] = 1;
    *((_WORD *)v4 + 637) = 0x7FFF;
  }
  *((_DWORD *)v4 + 148) = *(_DWORD *)(v6 + 636);
  *((_DWORD *)v4 + 150) = *(_DWORD *)(v6 + 640);
  *((_DWORD *)v4 + 152) = *(_DWORD *)(v6 + 644);
  *((_DWORD *)v4 + 147) = *((_DWORD *)v4 + 148);
  *((_DWORD *)v4 + 149) = *((_DWORD *)v4 + 150);
  *((_DWORD *)v4 + 151) = *((_DWORD *)v4 + 152);
  *((_DWORD *)v4 + 146) = *(_DWORD *)(v6 + 632);
  *((_DWORD *)v4 + 153) = *(_DWORD *)(v6 + 648);
  *((_DWORD *)v4 + 154) = *(_DWORD *)(v6 + 652);
  *((_DWORD *)v4 + 155) = *(_DWORD *)(v6 + 656);
  *((_DWORD *)v4 + 156) = *(_DWORD *)(v6 + 660);
  *((_DWORD *)v4 + 176) = *(_DWORD *)(v6 + 740);
  *((_DWORD *)v4 + 160) = *(_DWORD *)(v6 + 748);
  *((_DWORD *)v4 + 274) = *(__int16 *)(v6 + 842);
  *((_DWORD *)v4 + 275) = *(_DWORD *)(v6 + 844);
  *((_DWORD *)v4 + 276) = *(__int16 *)(v6 + 848);
  v4[1430] = *(float *)(v6 + 796) <= 0.0f;
  *((_DWORD *)v4 + 359) = (__int64)*(float *)(v6 + 724);
  v4[1432] = 0;
  v4[1431] = 0;
  v8 = *((_DWORD *)v4 + 147);
  if ( v8 >= 1000 )
  {
    if ( v8 >= 10000 )
    {
      if ( v8 >= 100000 )
        *((_DWORD *)v4 + 360) = (unsigned long)"??????/??????";
      else
        *((_DWORD *)v4 + 360) = (unsigned long)"?????/?????";
    }
    else
    {
      *((_DWORD *)v4 + 360) = (unsigned long)"????/????";
    }
  }
  else
  {
    *((_DWORD *)v4 + 360) = (unsigned long)"???/???";
  }
  v9 = *((_DWORD *)v4 + 160);
  if ( v9 == 916 || v9 == 917 || v9 == 921 || v9 == 922 || v9 == 926 || v9 == 927 )
    v4[649] = 1;
  v10 = *((_DWORD *)v4 + 160);
  if ( v10 == 918 || v10 == 919 || v10 == 920 || v10 == 923 || v10 == 928 )
    v4[650] = 1;
  strcpy(v4 + 560, (const char *)(v6 + 518));
  v11 = 580;
  idxa = (int *)(v4 + 1112);
  do
  {
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v4 + 138));
    v13 = *(_DWORD *)(v12 + v11) << 16;
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v4 + 138));
    v15 = *(_DWORD *)(v14 + v11) | v13;
    v11 += 4;
    *idxa++ = v15;
  }
  while ( v11 < 600 );
  v16 = *(void ( ****)(_DWORD, int))(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 4 * idx + 76);
  (**v16)((_DWORD)((_DWORD)(v16)), (int)(1));
  (((CCBAttackSequen *)*(CCBAttackSequen **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBAttackSequen::InitCombatSlot(idx);
  (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::GetCmdData(idx);
  (((CCBAttackSequen *)*(CCBAttackSequen **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBAttackSequen::GetCmdSlot(idx);
  (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12)))->CCBSystem::SetCmdParam(idx, 0);
  (((CCBStage *)*(CCBStage **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * idx + 24)))->CCBStage::IsAtProtectPos(idx, nRoleID, 0);
  (((CCBStageShadow *)*(CCBStageShadow **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 72)))->CCBStageShadow::Reset();
  (((CCBAI *)*(CCBAI **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 24)))->CCBAI::RepeatPlayerLastOperation();
  v17 = (int *)*(int **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * idx + 24);
  return (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 44)))->CEffMgr::Init(321, v17[1649], v17[1650], v17[1651], 0);
}

// 0x004F8FA0
char CCBRoleState::LoadRoleModel(int nVal)
{
  this->CCBRoleState::InitSlot(nVal, 739);
  return (((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 20)))->CCBStageScene::LoadModel(aZ39);
}

// 0x004F8FD0
char CCBRoleState::SpawnRandomEnemies(int nVal, int nVal2)
{
  int updated; // eax
  int v5; // ecx
  int v6; // ebx
  int v7; // ecx
  int v8; // esi
  int v9; // edx
  int *v10; // eax
  int v11; // edx
  int nRoleID; // [esp+0x4] [ebp-0xC] BYREF
  int v14; // [esp+0x8] [ebp-0x8]
  int v15; // [esp+0xC] [ebp-0x4]

  nRoleID = 7369;
  v14 = 7368;
  v15 = 7370;
  updated = this->CCBRoleState::UpdateRoleMP(2);
  if ( updated == 1 )
  {
    if ( !*((_BYTE *)((SceneObj *)this) + 5038) || (LOBYTE(updated) = *((_BYTE *)((SceneObj *)this) + 5892), (_BYTE)updated) )
    {
      if ( !*((_BYTE *)((SceneObj *)this) + 6822) || (LOBYTE(updated) = this->m_byteFlags, (_BYTE)updated) )
      {
        v5 = g_nCombatRandSeed;
        v6 = 16;
        do
        {
          v7 = 214013 * v5 + 2531011;
          *(_DWORD *)&g_TempBuffer1024[912] += 2;
          v8 = ((v7 >> 16) & 0x7FFF) % 3;
          v5 = 214013 * v7 + 2531011;
          g_nCombatRandSeed = v5;
          v9 = ((v5 >> 16) & 0x7FFF) % 3;
          if ( v8 != v9 )
          {
            v10 = (int *)(&nRoleID + v9);
            v11 = *(&nRoleID + v8);
            *(&nRoleID + v8) = *v10;
            *v10 = v11;
            v5 = g_nCombatRandSeed;
          }
          --v6;
        }
        while ( v6 );
        this->CCBRoleState::InitSlot(5, nRoleID);
        LOBYTE(updated) = this->CCBRoleState::InitSlot(7, v14);
      }
    }
  }
  return updated;
}

// 0x004F90F0
char * CCBRoleState::CheckRoleCanAct(int roleIdx)
{
  char *result; // eax
  int *v4; // edx
  int v5; // ebx
  int v6; // ebp
  int v7; // eax
  int nVal4; // [esp+0x10] [ebp-0x4]

  result = (char *)this + 892 * roleIdx;
  if ( result[577] && !result[1432] && !result[1431] )
  {
    v4 = (int *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * roleIdx + 24) + 6584);
    v5 = (unsigned long)*v4;
    v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * roleIdx + 24) + 6588);
    nVal4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[100] + 4 * roleIdx + 24) + 6592);
    (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 44)))->CEffMgr::Init(324, *v4, v6, nVal4, 0);
    (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 44)))->CEffMgr::Init(325, v5, v6, nVal4, 0);
    v7 = this->CCBRoleState::SetRoleField(roleIdx, 0);
    return (char *)this->CCBRoleState::AddCommand(roleIdx, -v7, 0);
  }
  return result;
}

// 0x004F91B0
char * CCBRoleState::PopulateItemList(int nSlot)
{
  int v3; // ecx
  char *result; // eax
  int v5; // ebx
  int RoleNum; // ebp
  int ListItems; // edi
  bool v8; // cc
  int v9; // [esp+0x10] [ebp-0x34]
  char *v10; // [esp+0x14] [ebp-0x30]
  int p_DWORD[11]; // [esp+0x18] [ebp-0x2C] BYREF
  int *nSlota; // [esp+0x48] [ebp+0x4]

  memset(p_DWORD, 0, sizeof(p_DWORD));
  (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1128) + 80)))->UIListBox::ClearAll();
  v3 = 0;
  p_DWORD[2] = nSlot;
  p_DWORD[3] = -1;
  LOWORD(p_DWORD[4]) = 0;
  LOBYTE(p_DWORD[10]) = 1;
  p_DWORD[0] = 260;
  v9 = 0;
  result = (char *)this + 892 * nSlot;
  v10 = (char *)result;
  nSlota = (int *)(result + 712);
  while ( 1 )
  {
    v5 = (unsigned long)*nSlota;
    if ( result[v3 + 736] && v5 )
    {
      RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*nSlota);
      ListItems = (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1128) + 80)))->UIListBox::LoadListItems("0", 0);
      (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1128) + 80)))->UIListBox::SetMouseMoveSel(0, ListItems, (char *)(RoleNum + 28), 0);
      sprintf(unk_17A9B50, off_5D8FEC, *(_DWORD *)(RoleNum + 688));
      (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1128) + 80)))->UIListBox::SetMouseMoveSel(1, ListItems, unk_17A9B50, 0);
      p_DWORD[1] = v5;
      if ( this->CCBRoleState::CheckMagicCost(p_DWORD) )
        this->CCBRoleState::CheckEventCondition((int)p_DWORD);
      result = (char *)UIListBox_SetChildParam(ListItems);
    }
    v3 = v9 + 1;
    v8 = ++v9 < 6;
    ++nSlota;
    if ( !v8 )
      break;
    result = (char *)v10;
  }
  return result;
}

// 0x004F9340
int CCBRoleState::GetDialogSlot(int nVal, int nVal2)
{
  int v3; // edi
  int v4; // edx
  char *v5; // esi
  int *i; // ecx
  int result; // eax

  v3 = 0;
  v4 = 0;
  v5 = (char *)this + 892 * nVal;
  for ( i = (int *)(v5 + 712); ; ++i )
  {
    result = (unsigned long)*i;
    if ( v5[v4 + 736] )
      ++v3;
    if ( v3 == nVal2 + 1 )
      break;
    if ( ++v4 >= 6 )
      return 0;
  }
  return result;
}

// 0x004F9390
unsigned int CCBRoleState::PopulateMagicList(int nSlot)
{
  int v3; // edi
  char *v4; // eax
  unsigned int *v5; // ebx
  int v6; // ecx
  unsigned int result; // eax
  int RoleNum; // ebx
  int ListItems; // ebp
  bool v10; // cc
  int v11; // [esp+0x10] [ebp-0x38]
  unsigned int *v12; // [esp+0x14] [ebp-0x34]
  int v13; // [esp+0x18] [ebp-0x30]
  int p_DWORD[11]; // [esp+0x1C] [ebp-0x2C] BYREF
  int nSlota; // [esp+0x4C] [ebp+0x4]

  memset(p_DWORD, 0, sizeof(p_DWORD));
  p_DWORD[3] = -1;
  p_DWORD[2] = nSlot;
  LOWORD(p_DWORD[4]) = 0;
  LOBYTE(p_DWORD[10]) = 1;
  p_DWORD[0] = 261;
  v3 = 76;
  v4 = (char *)this + 892 * nSlot;
  v5 = (unsigned int *)(v4 + 744);
  nSlota = (int)(v4 + 984);
  do
  {
    (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1124) + v3)))->UIListBox::ClearAll();
    v6 = 0;
    v12 = (unsigned int *)v5;
    v11 = 0;
    do
    {
      result = (unsigned long)*v5;
      v13 = (unsigned long)*v5;
      if ( *(_BYTE *)(nSlota + v6 - 48) && result )
      {
        RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(result);
        ListItems = (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1124) + v3)))->UIListBox::LoadListItems("0", 0);
        (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1124) + v3)))->UIListBox::SetMouseMoveSel(0, ListItems, (char *)(RoleNum + 28), 0);
        sprintf(unk_17A9A50, off_5D8FEC, *(_DWORD *)(RoleNum + 692));
        (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1124) + v3)))->UIListBox::SetMouseMoveSel(1, ListItems, unk_17A9A50, 0);
        sprintf(unk_17A9A50, "%d/%02d", *(unsigned __int8 *)(nSlota + v11 + 48) + 1, *(unsigned __int8 *)(nSlota + v11));
        (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1124) + v3)))->UIListBox::SetMouseMoveSel(2, ListItems, unk_17A9A50, 0);
        p_DWORD[1] = v13;
        if ( this->CCBRoleState::CheckMagicCost(p_DWORD) )
          this->CCBRoleState::CheckEventCondition((int)p_DWORD);
        result = UIListBox_SetChildParam(ListItems);
      }
      v6 = v11 + 1;
      v5 = (unsigned int *)(v12 + 1);
      v10 = ++v11 < 8;
      ++v12;
    }
    while ( v10 );
    v3 += 4;
    nSlota += 8;
  }
  while ( v3 < 100 );
  return result;
}

// 0x004F9590
int CCBRoleState::GetMagicSlotData(int nVal, int nVal2, int nVal3)
{
  int v4; // ebx
  int v5; // esi
  int *v6; // edx
  char *v7; // ecx
  int result; // eax

  v4 = 0;
  v5 = 0;
  v6 = (int *)&this->m_pObjMsgBuffer2[892 * nVal + 64 + 32 * nVal2];
  v7 = (char *)&this->m_renderpos + 892 * nVal + 8 * nVal2;
  while ( 1 )
  {
    result = (unsigned long)*v6;
    if ( v7[v5] )
      ++v4;
    if ( nVal3 + 1 == v4 )
      break;
    ++v5;
    ++v6;
    if ( v5 >= 8 )
      return 0;
  }
  return result;
}

// 0x004F95F0
int CCBRoleState::PopulateTargetList(int nSlot, int nType)
{
  signed int v4; // ebp
  int v5; // eax
  int result; // eax
  int ListItems; // ebx
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  int v10; // [esp+0xC] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x50] BYREF
  _BYTE v12[12]; // [esp+0x1C] [ebp-0x44] BYREF
  _BYTE v13[12]; // [esp+0x28] [ebp-0x38] BYREF
  int nVal[11]; // [esp+0x34] [ebp-0x2C] BYREF

  v4 = 0;
  memset(nVal, 0, sizeof(nVal));
  v10 = 0;
  if ( nType )
  {
    if ( nType == 1 )
    {
      v5 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(2);
    }
    else
    {
      if ( nType != 2 )
        goto LABEL_8;
      v5 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(15);
    }
  }
  else
  {
    v5 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(14);
  }
  v10 = v5;
LABEL_8:
  (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert((void *)3);
  result = (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1120)
                                             + 4 * nType
                                             + 80)))->UIListBox::ClearAll();
  if ( v10 > 0 )
  {
    do
    {
      ListItems = (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1120) + 4 * nType + 80)))->UIListBox::LoadListItems("0", 0);
      v8 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v4);
      (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1120) + 4 * nType + 80)))->UIListBox::SetMouseMoveSel(0, ListItems, (char *)(v8[2] + 4), 0);
      v9 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v12, v4);
      sprintf(unk_17A9950, off_5D8FEC, v9[1]);
      (((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1120) + 4 * nType + 80)))->UIListBox::SetMouseMoveSel(1, ListItems, unk_17A9950, 0);
      nVal[1] = **((_DWORD **)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v13, v4) + 2);
      if ( (((CCBSystem *)this))->CCBSystem::IsMagicSlotMsg((int)nVal) )
        (((CCBSystem *)this))->CCBSystem::HandleMagicCommand((int)nVal);
      UIListBox_SetChildParam(ListItems);
      result = v10;
      ++v4;
    }
    while ( v4 < v10 );
  }
  return result;
}

// 0x004F9790
int CCBRoleState::UpdateCommandButtons(int nSlot)
{
  int result; // eax
  char *v3; // esi
  int v4; // edx
  int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // ecx

  result = 0;
  v3 = (char *)this + 892 * nSlot;
  v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1132) + 96);
  if ( v3[1384] )
  {
    *(_DWORD *)(v4 + 80) = 1;
    *(_BYTE *)(v4 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v4 + 80) = 0;
    *(_BYTE *)(v4 + 68) = 0;
  }
  v5 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1132) + 104);
  if ( v3[1386] )
  {
    *(_DWORD *)(v5 + 80) = 1;
    *(_BYTE *)(v5 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v5 + 80) = 0;
    *(_BYTE *)(v5 + 68) = 0;
  }
  v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1132) + 108);
  if ( v3[1385] )
  {
    *(_DWORD *)(v6 + 80) = 1;
    *(_BYTE *)(v6 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v6 + 80) = 0;
    *(_BYTE *)(v6 + 68) = 0;
  }
  v7 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1132) + 100);
  if ( v3[1387] )
  {
    *(_DWORD *)(v7 + 80) = 1;
    *(_BYTE *)(v7 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v7 + 80) = 0;
    *(_BYTE *)(v7 + 68) = 0;
  }
  v8 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1132) + 112);
  if ( v3[1388] )
  {
    *(_DWORD *)(v8 + 80) = 0;
    *(_BYTE *)(v8 + 68) = 0;
  }
  else
  {
    *(_DWORD *)(v8 + 80) = 1;
    *(_BYTE *)(v8 + 68) = 1;
  }
  if ( v3[1389] )
  {
    result = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1132) + 116);
    *(_DWORD *)(result + 80) = 1;
    *(_BYTE *)(result + 68) = 1;
  }
  else
  {
    v9 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_pObjMsgBuffer[104] + 1132) + 116);
    *(_DWORD *)(v9 + 80) = 0;
    *(_BYTE *)(v9 + 68) = 0;
  }
  return result;
}

// 0x004F98B0
int CCBRoleState::ApplyDamage(int roleIdx, int dmg)
{
  int v3; // ebx
  int v4; // edi
  int RoleState; // eax
  int v7; // ebx
  signed int v8; // esi
  int v9; // edx
  int v10; // edi
  __int64 v11; // rax
  unsigned int v12; // ebx
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int RoleHP; // eax
  int v19; // ecx
  char *v20; // edx
  int v21; // eax
  int v22; // edi
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  int SpeedBonus; // edi
  int v27; // edi
  int v28; // ebx
  int AttackBonus; // edi
  int v30; // edi
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // eax
  int v36; // [esp-0x4] [ebp-0x1C]
  int v37; // [esp-0x4] [ebp-0x1C]
  int v38; // [esp+0xC] [ebp-0xC]
  int nIndex; // [esp+0x10] [ebp-0x8] BYREF
  int pnVal2; // [esp+0x14] [ebp-0x4] BYREF
  int *roleIdxa; // [esp+0x20] [ebp+0x8]
  int roleIdxb; // [esp+0x20] [ebp+0x8]
  int *roleIdxc; // [esp+0x20] [ebp+0x8]
  int pnVal; // [esp+0x28] [ebp+0x10] BYREF
  int v45; // [esp+0x2C] [ebp+0x14]
  int nVal; // [esp+0x30] [ebp+0x18]

  v3 = 0;
  v4 = 0;
  nIndex = 0;
  pnVal2 = 0;
  switch ( roleIdx )
  {
    case 1:
      RoleState = this->CCBRoleState::GetRoleState(pnVal);
      v7 = dmg;
      v45 = 10 * (this->CCBRoleState::GetRoleState(dmg) + 8 - RoleState);
      *(float *)&dmg = (double)v45 * *(float *)&this->m_pObjMsgBuffer[892 * v7 + 244] * 0.0099999998;
      pnVal = (int)*(float *)&dmg;
      v4 = pnVal + v45;
      dmg = pnVal + v45;
      if ( !(_BYTE)unk_5DFDEB )
        goto LABEL_76;
      *(float *)&dmg = (double)dmg * 0.2;
      pnVal = (int)*(float *)&dmg;
      v8 = abs32(pnVal);
      if ( !v8 )
        goto LABEL_76;
      v9 = (((int)(214013 * g_nCombatRandSeed + 2531011) >> 16) & 0x7FFF) % v8;
      *(_DWORD *)&g_TempBuffer1024[912] += 2;
      g_nCombatRandSeed = 214013 * (214013 * g_nCombatRandSeed + 2531011) + 2531011;
      if ( (((int)g_nCombatRandSeed >> 16) & 0x3FFu) < 0x200 )
        v10 = v4 - v9;
      else
        v10 = v9 + v4;
      LODWORD(v11) = v10;
      return v11;
    case 2:
      if ( *(float *)&v45 == 0.0f )
        goto LABEL_54;
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nVal);
      v12 = dmg;
      if ( (unsigned int)dmg > 4 )
      {
        roleIdxa = (int *)((char *)this + 892 * dmg);
        v4 = abs32((__int64)(((double)roleIdxa[146] * 0.050000001 + 0.1) * (double)v45));
        dmg = v4;
        if ( (_BYTE)unk_5DFDEB )
        {
          *(float *)&dmg = (double)dmg * 0.1;
          *(float *)&dmg = _pal3_coerce_f32(abs32((int)*(float *)&dmg));
          if ( *(float *)&dmg != 0.0f )
          {
            v14 = (((int)(214013 * g_nCombatRandSeed + 2531011) >> 16) & 0x7FFF) % dmg;
            *(_DWORD *)&g_TempBuffer1024[912] += 2;
            g_nCombatRandSeed = 214013 * (214013 * g_nCombatRandSeed + 2531011) + 2531011;
            if ( (((int)g_nCombatRandSeed >> 16) & 0x3FFu) < 0x200 )
              v4 -= v14;
            else
              v4 += v14;
          }
        }
        if ( v45 <= 0 )
          goto LABEL_23;
      }
      else
      {
        roleIdxa = (int *)((char *)this + 892 * dmg);
        v4 = abs32((__int64)(((double)roleIdxa[146] * 0.050000001 + 1.0) * (double)v45));
        dmg = v4;
        if ( (_BYTE)unk_5DFDEB )
        {
          *(float *)&dmg = (double)dmg * 0.1;
          *(float *)&dmg = _pal3_coerce_f32(abs32((int)*(float *)&dmg));
          if ( *(float *)&dmg != 0.0f )
          {
            v13 = (((int)(214013 * g_nCombatRandSeed + 2531011) >> 16) & 0x7FFF) % dmg;
            *(_DWORD *)&g_TempBuffer1024[912] += 2;
            g_nCombatRandSeed = 214013 * (214013 * g_nCombatRandSeed + 2531011) + 2531011;
            if ( (((int)g_nCombatRandSeed >> 16) & 0x3FFu) < 0x200 )
              v4 -= v13;
            else
              v4 += v13;
          }
        }
        if ( v45 <= 0 )
LABEL_23:
          v4 = -v4;
      }
      if ( v12 > 4 )
        goto LABEL_76;
      *(float *)&dmg = 0.0;
      pnVal = 0;
      this->CCBRoleState::CountValidSlots(v12, nVal, &dmg, &pnVal);
      this->CCBRoleState::IsAllEnemyDead(nVal, &nIndex, &pnVal2);
      if ( this->CCBRoleState::IsRoleIndexEqual(nIndex, roleIdxa[284])
        || this->CCBRoleState::IsRoleIndexEqual(pnVal2, roleIdxa[284]) )
      {
        v4 += v4 / 2;
      }
      if ( nIndex > 0 && nIndex < 6 )
      {
        v36 = (unsigned long)roleIdxa[284];
        v15 = this->CCBRoleState::CheckDeath(nIndex);
        if ( this->CCBRoleState::IsRoleIndexEqual(v15, v36) )
          v4 += v4 / -2;
      }
      if ( pnVal2 <= 0 )
        goto LABEL_76;
      if ( pnVal2 >= 6 )
        goto LABEL_76;
      v37 = (unsigned long)roleIdxa[284];
      v16 = this->CCBRoleState::CheckDeath(pnVal2);
      if ( !this->CCBRoleState::IsRoleIndexEqual(v16, v37) )
        goto LABEL_76;
      LODWORD(v11) = v4 / -2 + v4;
      return v11;
    case 3:
      v17 = dmg;
      this->CCBRoleState::GetRoleHP(dmg);
      RoleHP = this->CCBRoleState::GetRoleHP(pnVal);
      *(float *)&v45 = 0.0;
      *(float *)&dmg = 0.0;
      pnVal = 0;
      roleIdxb = *(_DWORD *)&this->m_pObjMsgBuffer[892 * v17 + 160];
      this->CCBRoleState::GetRoleMP(RoleHP);
      if ( v45 < dmg )
      {
        v19 = dmg - v45;
        v20 = (char *)&this->m_pObjMsgBuffer[892 * v45 + 160];
        do
        {
          if ( *(v20 - 7) )
          {
            ++pnVal;
            v3 += *(_DWORD *)v20;
          }
          v20 += 892;
          --v19;
        }
        while ( v19 );
      }
      v38 = v3 / pnVal;
      v21 = this->CCBRoleState::GetRoleState(v17);
      v22 = v45;
      v23 = v21;
      nVal = (int)&byte_FFFFFF;
      if ( v45 < dmg )
      {
        pnVal = (int)&this->m_pObjMsgBuffer[892 * v45 + 153];
        do
        {
          if ( *(_BYTE *)pnVal )
          {
            v24 = this->CCBRoleState::GetRoleState(v22);
            if ( v24 < nVal )
              nVal = this->CCBRoleState::GetRoleState(v22);
          }
          ++v22;
          pnVal += 892;
        }
        while ( v22 < dmg );
      }
      LODWORD(v11) = 10 * ((roleIdxb - v38) * (v23 - nVal) + 3);
      return v11;
    case 4:
      v25 = 5 - this->CCBRoleState::GetRoleState(pnVal);
      LODWORD(v11) = this->CCBRoleState::GetRoleState(dmg) + v25;
      return v11;
    case 5:
      SpeedBonus = this->CCBRoleState::GetSpeedBonus(dmg);
      v4 = 5 * (this->CCBRoleState::GetSpeedBonus(pnVal) - SpeedBonus);
      if ( v4 >= 0 )
        goto LABEL_76;
      LODWORD(v11) = 0;
      return v11;
    case 6:
      v27 = dmg;
      if ( this->CCBRoleState::GetRoleState(dmg) > 0 )
        return (__int64)(sqrt((double)(this->CCBRoleState::GetRoleState(v27) / 2)) * 10.0);
      else
LABEL_54:
        LODWORD(v11) = 0;
      return v11;
    case 7:
      v28 = dmg;
      roleIdxc = (int *)((char *)this + 892 * dmg);
      AttackBonus = this->CCBRoleState::GetAttackBonus(dmg);
      *(float *)&v45 = (double)(AttackBonus - this->CCBRoleState::GetDefenseBonus(pnVal))
                     * ((double)roleIdxc[146] * 0.0049999999 + 1.0);
      nVal = (int)*(float *)&v45;
      v30 = -nVal;
      v45 = -nVal;
      if ( (_BYTE)unk_5DFDEB )
      {
        *(float *)&v45 = (double)v45 * 0.1;
        nVal = (int)*(float *)&v45;
        *(float *)&v45 = _pal3_coerce_f32(abs32(nVal));
        if ( *(float *)&v45 == 0.0f )
        {
          v45 = v30;
        }
        else
        {
          v31 = (((int)(214013 * g_nCombatRandSeed + 2531011) >> 16) & 0x7FFF) % v45;
          *(_DWORD *)&g_TempBuffer1024[912] += 2;
          g_nCombatRandSeed = 214013 * (214013 * g_nCombatRandSeed + 2531011) + 2531011;
          if ( (((int)g_nCombatRandSeed >> 16) & 0x3FFu) < 0x200 )
            v30 -= v31;
          else
            v30 += v31;
          v28 = dmg;
          v45 = v30;
        }
      }
      else
      {
        v45 = -nVal;
      }
      if ( *((_BYTE *)roleIdxc + 650) || *((_BYTE *)roleIdxc + 649) )
      {
        if ( (_BYTE)unk_5DFDEB )
        {
          nVal = (int)5.0;
          *(float *)&v45 = _pal3_coerce_f32(abs32((int)5.0));
          if ( *(float *)&v45 == 0.0f )
          {
            v32 = 100;
          }
          else
          {
            v33 = (((int)(214013 * g_nCombatRandSeed + 2531011) >> 16) & 0x7FFF) % v45;
            *(_DWORD *)&g_TempBuffer1024[912] += 2;
            g_nCombatRandSeed = 214013 * (214013 * g_nCombatRandSeed + 2531011) + 2531011;
            if ( (((int)g_nCombatRandSeed >> 16) & 0x3FFu) < 0x200 )
              v32 = 100 - v33;
            else
              v32 = v33 + 100;
            v28 = dmg;
          }
        }
        else
        {
          v32 = 100;
        }
        v45 = v30 * (v32 - 45) / 100;
      }
      LOBYTE(v34) = this->CCBRoleState::CanAction(v28, pnVal, 0);
      *(float *)&dmg = (1.0 - (double)v34 * 0.050000001) * (double)v45;
      pnVal = (int)*(float *)&dmg;
      v4 = pnVal;
      goto LABEL_76;
    default:
LABEL_76:
      LODWORD(v11) = v4;
      return v11;
  }
}

// 0x004FA210
int CCBRoleState::GetSlotState(int nVal, int nVal2)
{
  int result; // eax

  result = 0;
  switch ( nVal )
  {
    case 0:
      result = 8 * nVal2 + 80;
      break;
    case 1:
      result = 7 * nVal2 + 75;
      break;
    case 2:
      result = 9 * nVal2 + 80;
      break;
    case 3:
      result = 7 * nVal2 + 60;
      break;
    case 4:
      result = 9 * nVal2 + 100;
      break;
    default:
      return result;
  }
  return result;
}

// 0x004FA280
int CCBRoleState::CalcSpeedByLevel(int nRole, int nLevel)
{
  double v3; // st7
  long double v4; // st7
  float v6; // [esp+0x0] [ebp-0x4]
  float nLevela; // [esp+0x10] [ebp+0xC]

  v3 = (double)nLevel;
  nLevela = 0.0f;
  v6 = v3;
  switch ( nRole )
  {
    case 0:
      v4 = sqrt(v6) * 9.0 + 8.0;
      goto LABEL_7;
    case 1:
      v4 = sqrt(v6) * 9.0 + 6.0;
      goto LABEL_7;
    case 2:
      v4 = sqrt(v6) * 9.0 + 7.0;
      goto LABEL_7;
    case 3:
      v4 = sqrt(v6) * 9.0 + 5.0;
      goto LABEL_7;
    case 4:
      v4 = (sqrt(v6) + 1.0) * 9.0;
LABEL_7:
      nLevela = v4;
      break;
    default:
      return (int)nLevela;
  }
  return (int)nLevela;
}

// 0x004FA330
int CCBRoleState::GetActionTypeBySlot(int nVal, int nVal2)
{
  int result; // eax

  result = 0;
  switch ( nVal )
  {
    case 0:
      result = 4 * nVal2 + 25;
      break;
    case 1:
      result = 5 * nVal2 + 25;
      break;
    case 2:
      result = 4 * nVal2 + 22;
      break;
    case 3:
      result = 2 * (3 * nVal2 + 15);
      break;
    case 4:
      result = 4 * nVal2 + 20;
      break;
    default:
      return result;
  }
  return result;
}

// 0x004FA3A0
int CCBRoleState::CalcDefenseByLevel(int nRole, int nLevel)
{
  float v3; // st7
  float v5; // [esp+0x0] [ebp-0x4]
  float nLevela; // [esp+0x10] [ebp+0xC]

  v5 = 0.0f;
  nLevela = (float)nLevel;
  switch ( nRole )
  {
    case 0:
      v3 = nLevela * 4.5f + 26.0f;
      goto LABEL_7;
    case 1:
      v3 = nLevela * 4.0f + 24.0f;
      goto LABEL_7;
    case 2:
      v3 = nLevela * 4.5f + 20.0f;
      goto LABEL_7;
    case 3:
      v3 = nLevela * 4.0f + 22.0f;
      goto LABEL_7;
    case 4:
      v3 = nLevela * 5.0f + 35.0f;
LABEL_7:
      v5 = v3;
      break;
    default:
      return (int)v5;
  }
  return (int)v5;
}

// 0x004FA440
int CCBRoleState::CalcDamage(int nVal, int nVal2)
{
  float v3; // st7
  float v5; // [esp+0x0] [ebp-0x4]
  float nVal2a; // [esp+0x10] [ebp+0xC]

  v5 = 0.0f;
  nVal2a = (float)nVal2;
  switch ( nVal )
  {
    case 0:
      v3 = nVal2a * 3.299999952316284f + 17.0f;
      goto LABEL_7;
    case 1:
      v3 = nVal2a * 3.0f + 13.0f;
      goto LABEL_7;
    case 2:
      v3 = nVal2a * 3.5f + 16.0f;
      goto LABEL_7;
    case 3:
      v3 = nVal2a * 3.0f + 16.0f;
      goto LABEL_7;
    case 4:
      v3 = nVal2a * 3.0f + 18.0f;
LABEL_7:
      v5 = v3;
      break;
    default:
      return (int)v5;
  }
  return (int)v5;
}

// 0x004FA4E0
int CCBRoleState::FindSlotByHP(unsigned int nVal, unsigned int dwVal)
{
  int result; // eax
  UIScene **i; // ecx

  result = 0;
  for ( i = &this->m_pScene + 28; (unsigned int)*i <= nVal; ++i )
  {
    if ( ++result >= 100 )
      return 100;
  }
  return result;
}

// 0x004FA510
int CCBRoleState::GetRoleCount(int nVal)
{
  int v2; // eax

  v2 = nVal;
  if ( nVal < 1 )
    return *((_DWORD *)&this->m_pScene + 28);
  if ( nVal > 100 )
    v2 = 100;
  return *((_DWORD *)&this->m_pScene + v2 + 27);
}

// 0x004FA540
int CCBRoleState::CheckRoleStatus(int roleIdx)
{
  int result; // eax
  int v3; // [esp+0x8] [ebp+0x8]
  int v4; // [esp+0xC] [ebp+0xC]
  int v5; // [esp+0x10] [ebp+0x10]

  result = roleIdx;
  *(_DWORD *)roleIdx = v3;
  *(_DWORD *)(roleIdx + 4) = v4;
  *(_DWORD *)(roleIdx + 8) = v5;
  return result;
}

// 0x004FA560
int CCBRoleState::GetSlotActionType(int nVal, char *Buffer)
{
  int result; // eax

  result = nVal;
  switch ( nVal )
  {
    case 0:
      result = sprintf(Buffer, "Jingtian");
      break;
    case 1:
      result = sprintf(Buffer, "Xuejian");
      break;
    case 2:
      result = sprintf(Buffer, "Longkui");
      break;
    case 3:
      result = sprintf(Buffer, "Zixuan");
      break;
    case 4:
      result = sprintf(Buffer, "Changqing");
      break;
    default:
      return result;
  }
  return result;
}

// 0x004FA5F0
int CCBRoleState::FindRoleByID(int nVal)
{
  int result; // eax
  char *i; // ecx

  result = 0;
  for ( i = &this->m_pObjMsgBuffer[128]; !i[25] || nVal != *(_DWORD *)i; i += 892 )
  {
    if ( ++result >= 11 )
      return -1;
  }
  return result;
}

// 0x004FA620
int CCBRoleState::CountValidSlots(int nVal, int nVal2, int *p_DWORD, int *pnVal)
{
  int v5; // ebx
  int v6; // edi
  int result; // eax
  char *v8; // edx

  v5 = 0;
  v6 = 0;
  while ( 2 )
  {
    result = 0;
    v8 = (char *)&this->m_pObjMsgBuffer2[892 * nVal + 64 + v6];
    do
    {
      if ( *(_DWORD *)v8 == nVal2 )
      {
        *p_DWORD = v5;
        *pnVal = result;
        return result;
      }
      ++result;
      v8 += 4;
    }
    while ( result < 8 );
    v6 += 32;
    ++v5;
    if ( v6 < 192 )
      continue;
    break;
  }
  result = (int)pnVal;
  *pnVal = -1;
  *p_DWORD = -1;
  return result;
}

// 0x004FA6A0
int CCBRoleState::CheckDeath(int roleIdx)
{
  int result; // eax

  switch ( roleIdx )
  {
    case 1:
      result = 5;
      break;
    case 2:
      result = 1;
      break;
    case 3:
      result = 4;
      break;
    case 4:
      result = 2;
      break;
    case 5:
      result = 3;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004FA700
int CCBRoleState::GetSlotType(int nVal)
{
  int result; // eax

  switch ( nVal )
  {
    case 1:
      result = 2;
      break;
    case 2:
      result = 4;
      break;
    case 3:
      result = 5;
      break;
    case 4:
      result = 3;
      break;
    case 5:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004FA760
int CCBRoleState::SwapEffectParams(int nVal)
{
  int v2; // eax
  int v3; // edx
  int v4; // edi
  int *v5; // esi
  int v6; // eax
  int v7; // esi
  int v8; // edx
  int v9; // esi
  int v10; // edx
  int m_nEffCurA; // eax
  int m_nEffCurB; // eax
  int m_nEffCurC; // eax
  int m_nEffCurD; // eax
  int result; // eax

  v2 = dword_5D8DC0[0];
  v3 = 0;
  v4 = 0;
  if ( nVal == dword_5D8DC0[0] )
  {
LABEL_5:
    v3 = v4;
  }
  else
  {
    v5 = dword_5D8DC0;
    while ( v2 != 6 )
    {
      v2 = (unsigned long)v5[1];
      ++v5;
      ++v4;
      if ( nVal == v2 )
        goto LABEL_5;
    }
  }
  this->m_nEffCurA = dword_5D8DC0[v3];
  v6 = v3 + 1;
  v7 = dword_5D8DC0[v3 + 1];
  v8 = v3 + 2;
  this->m_nEffTarget1 = v7;
  v9 = dword_5D8DC0[v8++];
  this->m_nEffSwapA = v9;
  v6 += 2;
  this->m_nEffSwapB = dword_5D8DC0[v8];
  this->m_nEffTarget2 = dword_5D8DC4[v8];
  this->m_nEffTransFrames = 6;
  v10 = dword_5D8DB8[v6++];
  this->m_nEffCurC = v10;
  this->m_nEffSwapC = dword_5D8DB8[v6];
  this->m_nEffSwapE = dword_5D8DBC[v6];
  this->m_nEffCurE = dword_5D8DC0[v6];
  this->m_nEffCurD = dword_5D8DC4[v6];
  this->m_nEffTransFrames2 = 6;
  m_nEffCurA = this->m_nEffCurA;
  this->m_nEffCurA = this->m_nEffSwapA;
  this->m_nEffSwapA = m_nEffCurA;
  m_nEffCurB = this->m_nEffCurB;
  this->m_nEffCurB = this->m_nEffSwapB;
  this->m_nEffSwapB = m_nEffCurB;
  m_nEffCurC = this->m_nEffCurC;
  this->m_nEffCurC = this->m_nEffSwapC;
  this->m_nEffSwapC = m_nEffCurC;
  m_nEffCurD = this->m_nEffCurD;
  this->m_nEffCurD = this->m_nEffTransFrames2;
  this->m_nEffTransFrames2 = m_nEffCurD;
  result = this->m_nEffCurE;
  this->m_nEffCurE = this->m_nEffSwapE;
  this->m_nEffSwapE = result;
  return result;
}

// 0x004FA8B0
int CCBRoleState::Revive(int roleIdx)
{
  this->CCBRoleState::GetRoleMP(1);
  return 1;
}

// 0x004FA930
char CCBRoleState::UpdateRoleMP(char arg0, int nVal)
{
  int v3; // ebx
  char result; // al
  char *v6; // ecx
  char *v7; // eax
  unsigned int v8; // edi
  int SlotByHP; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int ActionTypeBySlot; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // edi
  int v26; // eax
  int v27; // edi
  int v28; // eax
  char *v29; // edi
  unsigned __int8 v30; // al
  int *v31; // eax
  bool v32; // cc
  char *v33; // edi
  int *v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // eax
  _BYTE *v38; // ecx
  unsigned __int8 v39; // al
  int v40; // ecx
  bool v41; // zf
  int *v42; // eax
  int v43; // ecx
  int v44; // eax
  int v45; // eax
  int v46; // eax
  char *v47; // eax
  int v48; // eax
  int v49; // ecx
  int *v50; // eax
  int v51; // ecx
  int v52; // eax
  int v53; // eax
  int v54; // edx
  int v55; // edx
  unsigned int v56; // [esp+0x0] [ebp-0x5C]
  int p_DWORD; // [esp+0xC] [ebp-0x50] BYREF
  int v58; // [esp+0x10] [ebp-0x4C]
  int v59; // [esp+0x14] [ebp-0x48]
  int nVal2; // [esp+0x18] [ebp-0x44]
  int v61; // [esp+0x1C] [ebp-0x40]
  int v62; // [esp+0x20] [ebp-0x3C]
  int SlotState; // [esp+0x24] [ebp-0x38]
  int v64; // [esp+0x28] [ebp-0x34]
  int v65; // [esp+0x2C] [ebp-0x30]
  int v66; // [esp+0x30] [ebp-0x2C]
  int *v67; // [esp+0x34] [ebp-0x28]
  int *RoleNum; // [esp+0x38] [ebp-0x24]
  int v69; // [esp+0x3C] [ebp-0x20]
  _DWORD *p_m_fScale; // [esp+0x40] [ebp-0x1C]
  int v71; // [esp+0x44] [ebp-0x18]
  int v72; // [esp+0x48] [ebp-0x14]
  int v73; // [esp+0x4C] [ebp-0x10] BYREF
  char *v74; // [esp+0x50] [ebp-0xC]
  int nLevel; // [esp+0x54] [ebp-0x8]
  int pnVal; // [esp+0x58] [ebp-0x4] BYREF
  int arg0a; // [esp+0x64] [ebp+0x8]
  int arg0b; // [esp+0x64] [ebp+0x8]
  int arg0c; // [esp+0x64] [ebp+0x8]
  int *arg0d; // [esp+0x64] [ebp+0x8]
  char v81; // [esp+0x67] [ebp+0xB]

  v3 = 0;
  v71 = 0;
  v72 = 0;
  p_m_fScale = 0;
  pnVal = -1;
  if ( arg0 )
  {
    this->CCBRoleState::GetRoleMP(2);
    v69 = v71;
    this->CCBRoleState::UpdateRoleMP(1);
    return this->CCBRoleState::GetRoleMP(1);
  }
  else
  {
    v69 = 0;
    v74 = (char *)&this->m_pObjMsgBuffer[154];
    v6 = (char *)&this->m_pObjMsgBuffer[154];
    v66 = 0;
    p_m_fScale = (_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fScale;
    v62 = -578 - (_DWORD)this;
    do
    {
      if ( *(v6 - 1) && *v6 )
      {
        v7 = (char *)v74;
        v8 = *(_DWORD *)(v74 + 130) + *(_DWORD *)(v74 + 126);
        *(_DWORD *)(v74 + 126) = v8;
        arg0a = *(_DWORD *)(v7 + 6);
        SlotByHP = this->CCBRoleState::FindSlotByHP(v8, v56);
        nLevel = SlotByHP;
        if ( SlotByHP > arg0a )
        {
          p_DWORD = v3;
          v58 = SlotByHP;
          (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(nVal, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FormatSkillResultText) */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
          *(_DWORD *)(v74 + 6) = SlotByHP;
          SlotState = this->CCBRoleState::GetSlotState(v3, arg0a);
          v10 = this->CCBRoleState::GetSlotState(v3, SlotByHP);
          *(p_m_fScale - 1) += v10 - SlotState;
          v11 = this->CCBRoleState::CalcSpeedByLevel(v3, arg0a);
          v12 = this->CCBRoleState::CalcSpeedByLevel(v3, nLevel);
          *p_m_fScale += v12 - v11;
          ActionTypeBySlot = this->CCBRoleState::GetActionTypeBySlot(v3, arg0a);
          v14 = this->CCBRoleState::GetActionTypeBySlot(v3, nLevel);
          p_m_fScale[1] += v14 - ActionTypeBySlot;
          v15 = this->CCBRoleState::CalcDefenseByLevel(v3, arg0a);
          v16 = this->CCBRoleState::CalcDefenseByLevel(v3, nLevel);
          p_m_fScale[2] += v16 - v15;
          v17 = this->CCBRoleState::CalcDamage(v3, arg0a);
          v18 = this->CCBRoleState::CalcDamage(v3, nLevel);
          p_m_fScale[3] += v18 - v17;
          v19 = this->CCBRoleState::GetSlotState(v3, arg0a);
          v20 = this->CCBRoleState::GetSlotState(v3, nLevel);
          *(_DWORD *)(v74 + 14) += v20 - v19;
          v21 = this->CCBRoleState::CalcSpeedByLevel(v3, arg0a);
          v22 = this->CCBRoleState::CalcSpeedByLevel(v3, nLevel);
          *(_DWORD *)(v74 + 22) += v22 - v21;
          v23 = this->CCBRoleState::GetActionTypeBySlot(v3, arg0a);
          v24 = this->CCBRoleState::GetActionTypeBySlot(v3, nLevel);
          *(_DWORD *)(v74 + 30) += v24 - v23;
          v25 = this->CCBRoleState::CalcDefenseByLevel(v3, arg0a);
          v26 = this->CCBRoleState::CalcDefenseByLevel(v3, nLevel);
          *(_DWORD *)(v74 + 34) += v26 - v25;
          v27 = this->CCBRoleState::CalcDamage(v3, arg0a);
          v28 = this->CCBRoleState::CalcDamage(v3, nLevel) - v27;
          v29 = (char *)v74;
          arg0b = 0;
          *(_DWORD *)(v74 + 38) += v28;
          *(_DWORD *)(v29 + 10) = *(_DWORD *)(v29 + 14);
          *(_DWORD *)(v29 + 18) = *(_DWORD *)(v29 + 22);
          *(_DWORD *)(v29 + 26) = *(_DWORD *)(v29 + 30);
          RoleNum = (int *)(v29 + 134);
          do
          {
            if ( *RoleNum )
            {
              if ( !v29[arg0b + 158] )
              {
                v30 = *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*RoleNum) + 713);
                if ( v30 )
                {
                  if ( nLevel >= v30 )
                  {
                    v31 = (int *)RoleNum;
                    p_DWORD = v3;
                    v29[arg0b + 158] = 1;
                    v58 = (unsigned long)*v31;
                    (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(nVal, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FormatItemResultText) */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                  }
                }
              }
            }
            v32 = ++arg0b < 6;
            ++RoleNum;
          }
          while ( v32 );
        }
        v33 = (char *)&v74[v62];
        do
        {
          v65 = 6;
          v34 = (int *)(v74 + 166);
          arg0c = (int)(v74 + 454);
          SlotState = (int)v34;
          v64 = -48 - (_DWORD)this;
          do
          {
            v35 = 0;
            v67 = (int *)v34;
            nLevel = 0;
            do
            {
              v36 = (unsigned long)*v34;
              if ( v36 )
              {
                if ( *(_BYTE *)(arg0c + v35 - 96) )
                {
                  RoleNum = (int *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v36);
                  if ( *(unsigned __int8 *)(arg0c + nLevel) < 3u
                    && *((_BYTE *)RoleNum + *(unsigned __int8 *)(arg0c + nLevel) + 710) <= *(_BYTE *)(arg0c + nLevel - 48) )
                  {
                    v37 = 2;
                    v38 = (_BYTE *)RoleNum + 178;
                    while ( *((_BYTE *)((UIWnd *)this) + nLevel + arg0c + v64) < *v38 )
                    {
                      --v37;
                      --v38;
                      if ( v37 < 0 )
                        goto LABEL_26;
                    }
                    v39 = v37 + 1;
                    *(_BYTE *)(arg0c + nLevel) = v39;
                    p_DWORD = v3;
                    v40 = (unsigned long)*v67;
                    v59 = v39 + 1;
                    v58 = v40;
                    (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(nVal, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FormatMagicResultText) */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                  }
                }
              }
LABEL_26:
              v35 = nLevel + 1;
              v34 = (int *)(v67 + 1);
              v32 = ++nLevel < 8;
              ++v67;
            }
            while ( v32 );
            v41 = v65 == 1;
            arg0c += 8;
            --v65;
          }
          while ( !v41 );
          v64 = 6;
          nVal2 = (int)(v33 + 1032);
          v67 = (int *)(v33 + 1032);
          v42 = (int *)SlotState;
          do
          {
            v43 = 0;
            v65 = (int)v42;
            nLevel = 0;
            do
            {
              v44 = (unsigned long)*v42;
              if ( v44 && *((_BYTE *)this + (_DWORD)v67 + v43 - 96) )
              {
                v45 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v44);
                RoleNum = (int *)(v45 + 754);
                arg0d = (int *)(v45 + 724);
                v61 = -754 - v45;
                do
                {
                  if ( *arg0d )
                  {
                    if ( *((unsigned __int8 *)RoleNum - 3) <= *((unsigned __int8 *)((UIWnd *)this) + (_DWORD)v67 + nLevel)
                                                            + 1
                      && *(unsigned __int8 *)RoleNum <= *(int *)(v74 + 6) )
                    {
                      v46 = (unsigned long)arg0d[3];
                      if ( v46 )
                      {
                        if ( (((PAL_GDB *)this))->PAL_GDB::SearchItemLoop(v3, v46, &v73, &pnVal) )
                        {
                          if ( v33[8 * v73 + 936 + pnVal + (_DWORD)this] )
                          {
                            if ( *((unsigned __int8 *)RoleNum - 6) <= (unsigned __int8)v33[8 * v73
                                                                                         + 1032
                                                                                         + pnVal
                                                                                         + (_DWORD)this]
                                                                    + 1 )
                            {
                              if ( (((PAL_GDB *)this))->PAL_GDB::SearchItemLoop(v3, *arg0d, &v73, &pnVal) )
                              {
                                v47 = (char *)&v33[8 * v73 + 936 + pnVal + (_DWORD)this];
                                if ( !*v47 )
                                {
                                  *v47 = 1;
                                  v33[8 * v73 + 1032 + pnVal + (_DWORD)this] = 0;
                                  v48 = v66;
                                  v33[8 * v73 + 984 + pnVal + (_DWORD)this] = 0;
                                  p_DWORD = v3;
                                  v58 = *(_DWORD *)&this->m_pObjMsgBuffer2[32 * v73 + 64 + 4 * pnVal + 4 * v48];
                                  (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(nVal, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FormatItemResultText) */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                                  v3 = v69;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                  ++arg0d;
                  v49 = (int)RoleNum + v61 + 1;
                  RoleNum = (int *)((char *)RoleNum + 1);
                }
                while ( v49 < 3 );
              }
              v43 = nLevel + 1;
              v42 = (int *)(v65 + 4);
              v32 = ++nLevel < 8;
              v65 += 4;
            }
            while ( v32 );
            v41 = v64 == 1;
            v67 += 2;
            --v64;
          }
          while ( !v41 );
          v50 = (int *)SlotState;
          v81 = 0;
          v67 = (int *)nVal2;
          v64 = 6;
          do
          {
            v51 = 0;
            SlotState = (int)v50;
            nLevel = 0;
            do
            {
              v52 = (unsigned long)*v50;
              if ( v52 )
              {
                if ( *((_BYTE *)this + (_DWORD)v67 + v51 - 96) )
                {
                  v53 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v52);
                  nVal2 = *(_DWORD *)(v53 + 716);
                  if ( nVal2 )
                  {
                    if ( *(unsigned __int8 *)(v53 + 714) <= *((unsigned __int8 *)((UIWnd *)this) + (_DWORD)v67 + nLevel)
                                                          + 1
                      && *(unsigned __int8 *)(v53 + 713) <= *(int *)(v74 + 6) )
                    {
                      (((PAL_GDB *)this))->PAL_GDB::SearchItemLoop(v3, nVal2, &v73, &pnVal);
                      v54 = (int)&v33[8 * v73 + 936 + pnVal];
                      if ( !*((_BYTE *)((UIWnd *)this) + v54) )
                      {
                        *((_BYTE *)((UIWnd *)this) + v54) = 1;
                        v81 = 1;
                        v33[8 * v73 + 1032 + pnVal + (_DWORD)this] = 0;
                        v55 = v66;
                        v33[8 * v73 + 984 + pnVal + (_DWORD)this] = 0;
                        p_DWORD = v3;
                        v58 = *(_DWORD *)&this->m_pObjMsgBuffer2[32 * v73 + 64 + 4 * pnVal + 4 * v55];
                        (((CCBStage *)*(CCBStage **)&this->m_pObjMsgBuffer[100]))->CCBStage::GetRoleName(nVal, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::FormatItemResultText) */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                      }
                    }
                  }
                }
              }
              v51 = nLevel + 1;
              v50 = (int *)(SlotState + 4);
              v32 = ++nLevel < 8;
              SlotState += 4;
            }
            while ( v32 );
            v41 = v64 == 1;
            v67 += 2;
            --v64;
          }
          while ( !v41 );
        }
        while ( v81 );
      }
      result = (_BYTE)p_m_fScale + 0x80;
      ++v3;
      v6 = (char *)(v74 + 892);
      v32 = (int)(p_m_fScale + 352) < (int)&unk_C061A0;
      v69 = v3;
      p_m_fScale += 352;
      v74 += 892;
      v66 += 223;
    }
    while ( v32 );
  }
  return result;
}

// 0x004FB370
int CCBRoleState::CheckMPRequirement(int nVal)
{
  this->CCBRoleState::GetRoleMP(2);
  return 0;
}

// 0x004FB6B0
int CCBRoleState::RandomizeSpecialSkill(int nSkillId)
{
  int result; // eax

  if ( nSkillId != 7711 )
    return nSkillId;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
  switch ( (((int)g_nCombatRandSeed >> 16) & 0x7FFF) % 5 )
  {
    case 0:
      result = 207;
      break;
    case 1:
      result = 215;
      break;
    case 2:
      result = 232;
      break;
    case 3:
      result = 224;
      break;
    case 4:
      result = 240;
      break;
    default:
      return nSkillId;
  }
  return result;
}

// 0x00502000
int CCBRoleState::CCBRoleState_Func(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  float v7; // st7
  char v8; // al
  float fVal; // [esp+0x8] [ebp-0x4]

  v3 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v4 = 80 * *(_DWORD *)&this->sCGSHELF[35];
  v5 = (char *)&this->sCGSHELF[8 * v3 + 55 + v4];
  if ( *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) )
  {
    v7 = (*(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *(float *)((char *)&this->rCGSelfArea.bottom + 8 * v3 + v4))
       / *(float *)((char *)&this->rTouchAreaCG.top + 8 * v3 + v4)
       * 255.0;
    fVal = v7;
    if ( v7 > 255.0f )
      fVal = 255.0f;
    (((CCBStage *)this->m_fTimerLimit))->CCBStage::CalculateTurnOrder(fVal, *(_DWORD *)((char *)&this->fLastTime + 8 * v3 + v4));
    if ( v5[43] == 1
      || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *((float *)v5 + 6) > *((float *)v5 + 8)
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v8) )
    {
      (((CCBStage *)this->m_fTimerLimit))->CCBStage::CalculateTurnOrder(255.0, *((_DWORD *)v5 + 11));
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) = 1;
    return 0;
  }
}

// 0x005021C0
int CCBRoleState::FadeMusicIn(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  float v9; // st7
  CScreenMode *v10; // eax
  gbAudioManager *v11; // eax
  CScreenMode *v12; // eax
  gbAudioManager *v13; // eax
  float v14; // [esp-0x8] [ebp-0x14]
  float v15; // [esp+0x8] [ebp-0x4]

  v3 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v4 = 80 * *(_DWORD *)&this->sCGSHELF[35];
  v5 = (char *)&this->sCGSHELF[8 * v3 + 55 + v4];
  if ( !*((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) )
  {
    *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) = 1;
    if ( (g_dwGameFlags & 4) == 0 )
    {
      *(LONG *)((char *)&this->rCGSelfArea.top + 8 * v3 + v4) = 4;
      return 0;
    }
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    if ( AudioManager )
      *((float *)v5 + 16) = *(float *)(AudioManager + 212);
    if ( *((float *)v5 + 16) >= (double)*(float *)&this->sCGSHELF[19] )
    {
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
    v5[41] = 1;
  }
  v9 = (1.0f - (*(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *((float *)v5 + 6)) / *((float *)v5 + 8))
     * (*(float *)&this->sCGSHELF[19] - *((float *)v5 + 16))
     + *((float *)v5 + 16);
  v15 = v9;
  if ( v9 > *(float *)&this->sCGSHELF[19] )
    v15 = *(float *)&this->sCGSHELF[19];
  if ( v15 < 0.0f )
    v15 = 0.0f;
  v10 = (CScreenMode *)CScreenMode::GetInstance();
  v11 = (gbAudioManager *)(((CScreenMode *)v10))->CScreenMode::GetAudioManager();
  (((gbAudioManager *)v11))->gbAudioManager::SetMusicMasterVolume(v15);
  if ( v5[43] == 1 || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *((float *)v5 + 6) > *((float *)v5 + 8) )
  {
    v14 = *(float *)&this->sCGSHELF[19];
    v12 = (CScreenMode *)CScreenMode::GetInstance();
    v13 = (gbAudioManager *)(((CScreenMode *)v12))->CScreenMode::GetAudioManager();
    (((gbAudioManager *)v13))->gbAudioManager::SetMusicMasterVolume(v14);
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00502300
int CCBRoleState::FadeMusicOut(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // edi
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  float v9; // st7
  CScreenMode *v10; // eax
  gbAudioManager *v11; // eax
  CScreenMode *v12; // eax
  gbAudioManager *v13; // esi
  float v14; // [esp+0x8] [ebp-0x4]

  v3 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v4 = 80 * *(_DWORD *)&this->sCGSHELF[35];
  v5 = (char *)&this->sCGSHELF[8 * v3 + 55 + v4];
  if ( !*((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) )
  {
    if ( (g_dwGameFlags & 4) == 0 )
    {
      *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) = 1;
      *(LONG *)((char *)&this->rCGSelfArea.top + 8 * v3 + v4) = 4;
      return 0;
    }
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    if ( AudioManager )
      *(float *)&this->sCGSHELF[19] = *(float *)(AudioManager + 212);
    v5[41] = 1;
  }
  v9 = (1.0f - (*(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *((float *)v5 + 6)) / *((float *)v5 + 8))
     * *(float *)&this->sCGSHELF[19];
  v14 = v9;
  if ( v9 > *(float *)&this->sCGSHELF[19] )
    v14 = *(float *)&this->sCGSHELF[19];
  if ( v14 < 0.0f )
    v14 = 0.0f;
  v10 = (CScreenMode *)CScreenMode::GetInstance();
  v11 = (gbAudioManager *)(((CScreenMode *)v10))->CScreenMode::GetAudioManager();
  (((gbAudioManager *)v11))->gbAudioManager::SetMusicMasterVolume(v14);
  if ( v5[43] == 1 || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *((float *)v5 + 6) > *((float *)v5 + 8) )
  {
    v12 = (CScreenMode *)CScreenMode::GetInstance();
    v13 = (gbAudioManager *)(((CScreenMode *)v12))->CScreenMode::GetAudioManager();
    (((gbAudioManager *)v13))->gbAudioManager::StopSoundStream(1);
    (((gbAudioManager *)v13))->gbAudioManager::StopSoundStream(0);
    (((gbAudioManager *)v13))->gbAudioManager::StopSoundStream(2);
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00502430
int CCBRoleState::GetCombatDialogEntry(int nVal)
{
  int v3; // ecx
  char *v4; // eax
  int v5; // edi
  char v7; // al

  v3 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v4 = (char *)this + 80 * *(_DWORD *)&this->sCGSHELF[35];
  v5 = (int)&v4[8 * v3 + 184];
  if ( v4[8 * v3 + 225] )
  {
    if ( (((CCBUI *)*(CCBUI **)(*(_DWORD *)((UIWnd *)this) + 4)))->CCBUI::CreateProtectWindow() )
      *(_DWORD *)(v5 + 16) = 4;
    if ( *(_BYTE *)(v5 + 43) == 1
      || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *(float *)(v5 + 24) > *(float *)(v5 + 32)
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v7) )
    {
      *(_DWORD *)(v5 + 16) = 4;
    }
    return 0;
  }
  else
  {
    (((CCBUI *)*(CCBUI **)(*(_DWORD *)((UIWnd *)this) + 4)))->CCBUI::InitRoleDisplay(1);
    *(_BYTE *)(v5 + 41) = 1;
    return 0;
  }
}

// 0x005025C0
int CCBRoleState::FormatSkillResultText(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  char *v6; // eax
  void ( ***v7)(_DWORD, int); // ecx
  CScreenMode *Instance; // eax
  char v10; // al
  void (***v11)(_DWORD, _DWORD); // ecx
  char *v12; // [esp-0x10] [ebp-0x98]
  char *v13; // [esp-0xC] [ebp-0x94]
  char *v14; // [esp-0xC] [ebp-0x94]
  int v15; // [esp-0x8] [ebp-0x90]
  int v16; // [esp-0x8] [ebp-0x90]
  char *v17; // [esp-0x4] [ebp-0x8C]
  char *v18; // [esp-0x4] [ebp-0x8C]
  char Buffer[128]; // [esp+0x8] [ebp-0x80] BYREF

  v3 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v4 = 80 * *(_DWORD *)&this->sCGSHELF[35];
  v5 = (char *)&this->sCGSHELF[8 * v3 + 55 + v4];
  if ( *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) )
  {
    if ( *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 3) == 1
      || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *(float *)((char *)&this->rCGSelfArea.bottom + 8 * v3 + v4) > *(float *)((char *)&this->rTouchAreaCG.top + 8 * v3 + v4)
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v10) )
    {
      v11 = *(void ( ****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1084);
      (**v11)((_DWORD)(v11), (_DWORD)(0));
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    switch ( *(_DWORD *)((char *)&this->fLastTime + 8 * v3 + v4) )
    {
      case 0:
        v17 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v6 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Jingtian");
        goto LABEL_9;
      case 1:
        v17 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v6 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Xuejian");
        goto LABEL_9;
      case 2:
        v18 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v16 = *((_DWORD *)v5 + 12);
        v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v12 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Longkui");
        sprintf(Buffer, "%s%s %d %s", v12, v14, v16, v18);
        break;
      case 3:
        v17 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v6 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Zixuan");
        goto LABEL_9;
      case 4:
        v17 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v6 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Changqing");
LABEL_9:
        sprintf(Buffer, "%s%s %d %s", v6, v13, v15, v17);
        break;
      default:
        break;
    }
    SetEnable(*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1084));
    v7 = *(void ( ****)(_DWORD, int))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1084);
    (**v7)((_DWORD)((_DWORD)(v7)), (int)(1));
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWa014, 1);
    v5[41] = 1;
    return 0;
  }
}

// 0x005027E0
int CCBRoleState::FormatAttackResultText(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  int v6; // eax
  int SkillNum; // eax
  char *v8; // eax
  void ( ***v9)(_DWORD, int); // ecx
  char v11; // al
  void (***v12)(_DWORD, _DWORD); // ecx
  char *v13; // [esp-0xC] [ebp-0x114]
  char *v14; // [esp-0xC] [ebp-0x114]
  int v15; // [esp-0x8] [ebp-0x110]
  int v16; // [esp-0x8] [ebp-0x110]
  char *v17; // [esp-0x4] [ebp-0x10C]
  const char *v18; // [esp-0x4] [ebp-0x10C]
  int v19; // [esp-0x4] [ebp-0x10C]
  char Buffer[256]; // [esp+0x8] [ebp-0x100] BYREF

  v3 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v4 = 80 * *(_DWORD *)&this->sCGSHELF[35];
  v5 = (char *)&this->sCGSHELF[8 * v3 + 55 + v4];
  if ( *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 1) )
  {
    if ( *((_BYTE *)&this->rTouchAreaCG.bottom + 8 * v3 + v4 + 3) == 1
      || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *(float *)((char *)&this->rCGSelfArea.bottom + 8 * v3 + v4) > *(float *)((char *)&this->rTouchAreaCG.top + 8 * v3 + v4)
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v11) )
    {
      v12 = *(void ( ****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1112);
      (**v12)((_DWORD)(v12), (_DWORD)(0));
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    v6 = *(_DWORD *)((char *)&this->fLastTime + 8 * v3 + v4);
    if ( v6 )
    {
      if ( v6 == 1 )
      {
        v17 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aMoney);
        v15 = *((_DWORD *)v5 + 13);
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aGetitem_0);
        sprintf(Buffer, "%s %d %s", v13, v15, v17);
      }
    }
    else
    {
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(_DWORD *)((char *)&this->mParam.f1 + 8 * v3 + v4));
      if ( *((_DWORD *)v5 + 13) == 1 )
      {
        v18 = (const char *)(SkillNum + 4);
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aGetitem_0);
        sprintf(Buffer, "%s %s", v8, v18);
      }
      else
      {
        v19 = *((_DWORD *)v5 + 13);
        v16 = SkillNum + 4;
        v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aGetitem_0);
        sprintf(Buffer, "%s %s %d", v14, v16, v19);
      }
    }
    SetEnable(*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1112));
    v9 = *(void ( ****)(_DWORD, int))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1112);
    (**v9)((_DWORD)((_DWORD)(v9)), (int)(1));
    v5[41] = 1;
    return 0;
  }
}

// 0x00502950
int CCBRoleState::FormatItemResultText(int nVal)
{
  UICaption *v3; // edi
  int v4; // ecx
  int v5; // edx
  char *v6; // ebx
  int RoleNum; // eax
  char *v8; // eax
  CScreenMode *Instance; // eax
  char v11; // al
  char *v12; // [esp-0xC] [ebp-A4h]
  char *v13; // [esp-0x8] [ebp-A0h]
  char *v14; // [esp-0x8] [ebp-A0h]
  int v15; // [esp-0x4] [ebp-0x9C]
  int v16; // [esp-0x4] [ebp-0x9C]
  int p_DWORD; // [esp+0xC] [ebp-0x8C] BYREF
  int p_DWORD2; // [esp+0x10] [ebp-0x88] BYREF
  int pnVal; // [esp+0x14] [ebp-0x84] BYREF
  char Buffer[128]; // [esp+0x18] [ebp-0x80] BYREF

  p_DWORD2 = -1;
  pnVal = -1;
  v3 = 0;
  v4 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v5 = 80 * *(_DWORD *)&this->sCGSHELF[35];
  v6 = (char *)&this->sCGSHELF[8 * v4 + 55 + v5];
  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(_DWORD *)((char *)&this->mParam.f1 + 8 * v4 + v5));
  if ( v6[41] )
  {
    if ( v6[43] == 1
      || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *((float *)v6 + 6) > *((float *)v6 + 8)
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v11) )
    {
      if ( (((PAL_GDB *)this->m_fontcolor.Color))->PAL_GDB::IsItemConsumable(*((_DWORD *)v6 + 12)) )
      {
        (((PAL_GDB *)this->m_fontcolor.Color))->PAL_GDB::SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
        switch ( p_DWORD )
        {
          case 0:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1096))((_DWORD)(0));
            break;
          case 1:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1100))((_DWORD)(0));
            break;
          case 2:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1092))((_DWORD)(0));
            break;
          case 3:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1088))((_DWORD)(0));
            break;
          case 4:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1104))((_DWORD)(0));
            break;
          case 5:
            v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1108);
            goto LABEL_32;
          default:
LABEL_32:
            (**(void ( ***)(_DWORD))((UIWnd *)v3))((_DWORD)(0));
            break;
        }
      }
      else
      {
        (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1084))((_DWORD)(0));
      }
      *((_DWORD *)v6 + 4) = 4;
    }
    return 0;
  }
  else
  {
    switch ( *((_DWORD *)v6 + 11) )
    {
      case 0:
        v15 = RoleNum + 28;
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aMastered);
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Jingtian");
        goto LABEL_9;
      case 1:
        v15 = RoleNum + 28;
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aMastered);
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Xuejian");
        goto LABEL_9;
      case 2:
        v16 = RoleNum + 28;
        v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aMastered);
        v12 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Longkui");
        sprintf(Buffer, "%s%s %s", v12, v14, v16);
        break;
      case 3:
        v15 = RoleNum + 28;
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aMastered);
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Zixuan");
        goto LABEL_9;
      case 4:
        v15 = RoleNum + 28;
        v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aMastered);
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Changqing");
LABEL_9:
        sprintf(Buffer, "%s%s %s", v8, v13, v15);
        break;
      default:
        break;
    }
    if ( (((PAL_GDB *)this->m_fontcolor.Color))->PAL_GDB::IsItemConsumable(*((_DWORD *)v6 + 12)) )
    {
      (((PAL_GDB *)this->m_fontcolor.Color))->PAL_GDB::SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
      switch ( p_DWORD )
      {
        case 0:
          v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1096);
          break;
        case 1:
          v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1100);
          break;
        case 2:
          v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1092);
          break;
        case 3:
          v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1088);
          break;
        case 4:
          v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1104);
          break;
        case 5:
          v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1108);
          break;
        default:
          break;
      }
      SetEnable(v3);
      (**(void ( ***)(int))((UIWnd *)v3))((int)(1));
    }
    else
    {
      SetEnable(*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1084));
      (***(void ( ****)(int))(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1084))((int)(1));
    }
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWa015, 1);
    v6[41] = 1;
    return 0;
  }
}

// 0x00502CC0
int CCBRoleState::FormatMagicResultText(int nVal)
{
  UICaption *v3; // ebp
  int v4; // ecx
  int v5; // edx
  char *v6; // edi
  int RoleNum; // ebx
  char *v8; // eax
  CScreenMode *Instance; // eax
  char v10; // al
  char *v12; // [esp-0x14] [ebp-B0h]
  int v13; // [esp-0x10] [ebp-ACh]
  char *v14; // [esp-0xC] [ebp-A8h]
  char *v15; // [esp-0xC] [ebp-A8h]
  int v16; // [esp-0x8] [ebp-A4h]
  int v17; // [esp-0x8] [ebp-A4h]
  char *v18; // [esp-0x4] [ebp-A0h]
  char *v19; // [esp-0x4] [ebp-A0h]
  int p_DWORD; // [esp+0x10] [ebp-0x8C] BYREF
  int p_DWORD2; // [esp+0x14] [ebp-0x88] BYREF
  int pnVal; // [esp+0x18] [ebp-0x84] BYREF
  char Buffer[128]; // [esp+0x1C] [ebp-0x80] BYREF

  p_DWORD2 = -1;
  pnVal = -1;
  v3 = 0;
  v4 = 329 * *(_DWORD *)&this->sCGSHELF[31];
  v5 = 80 * *(_DWORD *)&this->sCGSHELF[35];
  v6 = (char *)&this->sCGSHELF[8 * v4 + 55 + v5];
  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(_DWORD *)((char *)&this->mParam.f1 + 8 * v4 + v5));
  if ( !v6[41] )
  {
    switch ( *((_DWORD *)v6 + 11) )
    {
      case 0:
        v18 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Jingtian");
        goto LABEL_9;
      case 1:
        v18 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Xuejian");
        goto LABEL_9;
      case 2:
        v19 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v17 = *((_DWORD *)v6 + 13);
        v15 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v12 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Longkui");
        sprintf(Buffer, "%s %s %s %d %s", v12, RoleNum + 28, v15, v17, v19);
        break;
      case 3:
        v18 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Zixuan");
        goto LABEL_9;
      case 4:
        v18 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Changqing");
LABEL_9:
        sprintf(Buffer, "%s %s %s %d %s", v8, v13, v14, v16, v18);
        break;
      default:
        break;
    }
    (((PAL_GDB *)this->m_fontcolor.Color))->PAL_GDB::SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
    switch ( p_DWORD )
    {
      case 0:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1096);
        break;
      case 1:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1100);
        break;
      case 2:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1092);
        break;
      case 3:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1088);
        break;
      case 4:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1104);
        break;
      case 5:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1108);
        break;
      default:
        break;
    }
    SetEnable(v3);
    (**(void ( ***)(UICaption *, int))((UIWnd *)v3))((UICaption *)(v3), (int)(1));
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWa015, 1);
    v6[41] = 1;
  }
  if ( v6[43] == 1
    || *(float *)(*(_DWORD *)((UIWnd *)this) + 80) - *((float *)v6 + 6) > *((float *)v6 + 8)
    || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v10) )
  {
    (((PAL_GDB *)this->m_fontcolor.Color))->PAL_GDB::SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
    switch ( p_DWORD )
    {
      case 0:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1096);
        break;
      case 1:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1100);
        break;
      case 2:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1092);
        break;
      case 3:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1088);
        break;
      case 4:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1104);
        break;
      case 5:
        v3 = (UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 4) + 1108);
        break;
      default:
        break;
    }
    (**(void ( ***)(UICaption *, _DWORD))((UIWnd *)v3))((UICaption *)(v3), (_DWORD)(0));
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x00503AE0
int CCBRoleState::GetRoleMPValue(int nVal, int nVal2, int nVal3)
{
  int v5; // edi
  float *p_m_fDeltaTime; // ecx
  int v7; // esi
  int result; // eax

  v5 = 0;
  p_m_fDeltaTime = (float *)&this->m_fDeltaTime;
  v7 = 2;
  *p_m_fDeltaTime = 0.0;
  p_m_fDeltaTime[1] = 0.0;
  *((_WORD *)p_m_fDeltaTime + 4) = 0;
  *((_BYTE *)p_m_fDeltaTime + 10) = 0;
  do
  {
    if ( ((unsigned int)(__int64)pow(2.0, (double)(v7 - 1)) & nVal2) != 0 )
      ++v5;
    ++v7;
  }
  while ( v7 < 5 );
  if ( v5 <= 1 )
  {
    if ( (nVal2 & 1) != 0 )
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleMP(2);
    else
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleMP(1);
    return 0;
  }
  else
  {
    result = nVal;
    *((_BYTE *)&this->m_fDeltaTime + nVal) = 1;
  }
  return result;
}

// 0x00524970
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBRoleState::Render(const char *a2, tagRECT *a3, int a4, int a5, bool a6)
{
  (((CCBControlWindow *)this))->CCBControlWindow::Render((CCBMagicWindow *)a2) /* [ROWTABLE] */;
}
#pragma auto_inline(on)
#pragma inline_depth()
