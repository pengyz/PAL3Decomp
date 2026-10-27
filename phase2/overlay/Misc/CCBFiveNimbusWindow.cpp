#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBUI.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIButton.h"
#include "Misc/UIButtonEX.h"
#include "UI/UIListBox.h"
#include "UI/UIScene.h"
#include "Misc/UISceneMap.h"
#include "Misc/UIStatic.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x00439740
int * CCBFiveNimbusWindow::CreateScriptAndCamera(int id, int parent)
{
  gbCamera *v4; // eax
  gbCamera *v5; // eax
  int *result; // eax
  tagRECT pRect; // [esp+0x8] [ebp-0x1C] BYREF
  int v8; // [esp+0x20] [ebp-0x4]

  memset(&pRect, 0, sizeof(pRect));
  this->UIWnd::Create(id, &pRect, (UIWnd *)parent);
  v4 = (gbCamera *)operator new(0x178u);
  v8 = 0;
  if ( v4 )
    v4->gbCamera::gbCamera(gfxMgr);
  else
    v5 = 0;
  this[1].m_state[1] = (int)v5;
  v8 = -1;
  (((gbCamera *)v5))->gbCamera::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  result = (int *)this[1].m_state[1];
  this[1].pCtrlButton[0] = (UIButtonEX *)1161527296;
  result[1] = 1161527296;
  *result = 0;
  this[1].pCtrlButton[4] = 0;
  return result;
}

// 0x0043A070
int CCBFiveNimbusWindow::SetFloatParam(float value)
{
  int result; // eax
  int v3; // ecx

  result = LODWORD(value);
  *(float *)this[1].pCtrlButton = value;
  v3 = this[1].m_state[1];
  *(float *)(v3 + 4) = value;
  *(_DWORD *)v3 = 0;
  return result;
}

// 0x0043FD20
int CCBFiveNimbusWindow::CalcHitAngle(int nVal)
{
  int result; // eax
  float v3; // st7
  float v4; // st6

  result = nVal;
  this->m_pbktex = ((gbTexture *)((gbTexture *)nVal));
  if ( !nVal )
  {
    v3 = (float)this->m_rect.right - *(float *)&this->m_state[3] - *(float *)&this->m_state[1];
    v4 = (float)this->m_rect.left + *(float *)&this->m_state[2];
    goto LABEL_5;
  }
  result = nVal - 1;
  if ( nVal == 1 )
  {
    v3 = (float)this->m_rect.bottom - *(float *)&this->m_nimbusStep - *(float *)&this->m_state[1];
    v4 = (float)this->m_rect.top + *(float *)&this->m_state[4];
LABEL_5:
    *(float *)&this->m_nimbus[3] = v3 - (v4 + *(float *)&this->m_state[1]);
  }
  *(float *)this->m_state = *(float *)&this->m_nimbus[3] / *(float *)&this->m_nimbus[4];
  *(float *)&this->m_bShow = *(float *)&this->m_nimbus[4] / *(float *)&this->m_nimbus[3];
  return result;
}

// 0x004438F0
void CCBFiveNimbusWindow::Destroy_38f0()
{
  int v2; // ebx
  int v3; // edi
  gbRefObject *v4; // ecx

  if ( this->m_nimbus[1] )
  {
    v2 = 0;
    if ( this->m_nimbus[0] > 0 )
    {
      v3 = 0;
      do
      {
        v4 = (gbRefObject *)*(gbRefObject **)(v3 + this->m_nimbus[1] + 44);
        if ( v4 )
          (((gbRefObject *)v4))->gbRefObject::Release();
        ++v2;
        v3 += 80;
      }
      while ( v2 < this->m_nimbus[0] );
    }
    operator delete((void *)this->m_nimbus[1]);
    this->m_nimbus[1] = 0;
  }
  (((SceneObj *)this))->SceneObj::HideAll() /* [ROWTABLE] */;
}

// 0x00443950
void CCBFiveNimbusWindow::Render()
{
  if ( this->m_bvisible )
  {
    (((TextureLibDataBase *)this))->TextureLibDataBase::CountEntries();
    (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  }
}

// 0x00443970
BOOL CCBFiveNimbusWindow::UpdateIfVisible(int nVal, int nVal2)
{
  int v5; // eax

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( LOBYTE(this->m_nimbusStep) )
    return 0;
  (((UISceneMap *)this))->UISceneMap::sub_443CA0(*(float *)&nVal) /* [ROWTABLE] */;
  if ( LOBYTE(this->m_nimbus[3]) )
  {
    v5 = this->m_nimbus[1];
    *(float *)&this->m_state[1] = -*(float *)(v5 + 36);
    *(float *)&this->m_state[2] = -*(float *)(v5 + 40);
  }
  else
  {
    this->m_state[0] = 0;
    this->m_nimbus[4] = 0;
  }
  CCBUIPanel_UpdateSlotPositions(nVal);
  (((TextureLibDataBase *)this))->TextureLibDataBase::SearchByIndex();
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x00443AF0
int CCBFiveNimbusWindow::UpdateDisplay()
{
  int result; // eax
  int v2; // esi
  int v3; // eax
  float v4; // st7
  int v5; // edx
  int v6; // edx
  float v7; // st7
  int v8; // [esp+0x4] [ebp-0x4]

  result = 0;
  if ( LOBYTE(this->m_state[3]) )
  {
    v2 = 0;
    if ( this->m_nimbus[0] > 0 )
    {
      v8 = 0;
      do
      {
        v3 = this->m_nimbus[1] + result;
        ++v2;
        *(_DWORD *)(v3 + 4) = *(_DWORD *)(v3 + 20);
        *(_DWORD *)(v3 + 8) = *(_DWORD *)(v3 + 24);
        *(_DWORD *)(v3 + 12) = *(_DWORD *)(v3 + 28);
        *(_DWORD *)(v3 + 16) = *(_DWORD *)(v3 + 32);
        *(float *)(v3 + 40) = (float)*(int *)(v3 + 8);
        v4 = (float)*(int *)(v3 + 4);
        *(_DWORD *)(v3 + 48) = *(_DWORD *)(v3 + 64);
        v5 = *(_DWORD *)(v3 + 68);
        *(float *)(v3 + 36) = v4;
        *(_DWORD *)(v3 + 52) = v5;
        *(_DWORD *)(v3 + 56) = *(_DWORD *)(v3 + 72);
        *(_DWORD *)(v3 + 60) = *(_DWORD *)(v3 + 76);
        result = v8 + 80;
        v8 += 80;
      }
      while ( v2 < this->m_nimbus[0] );
      result = 0;
    }
  }
  v6 = this->m_nimbus[1];
  LOBYTE(this->m_nimbus[3]) = 0;
  *(float *)&this->m_state[1] = (double)*(int *)(v6 + 20) - *(float *)(v6 + 36);
  v7 = (float)*(int *)(v6 + 24) - *(float *)(v6 + 40);
  this->m_state[0] = 0;
  this->m_nimbus[4] = 0;
  *(float *)&this->m_state[2] = v7;
  return result;
}

// 0x00443BA0
bool CCBFiveNimbusWindow::IsHitLeft()
{
  float v2; // [esp+0x4] [ebp+0x4]

  return (double)((unsigned int)this->pMiddle + (unsigned int)this->pCtrlButton[1] - 256) < *(float *)(80 * this->m_nimbus[0] + this->m_nimbus[1] - 44)
                                                                                          - v2
                                                                                          * *(float *)&this->m_state[4]
                                                                                          * *(float *)&this->m_nimbus[2];
}

// 0x00443BF0
bool CCBFiveNimbusWindow::IsAboveThreshold(float fVal)
{
  return (double)(int)this->pCtrlButton[1] > fVal * *(float *)&this->m_state[4] * *(float *)&this->m_nimbus[2]
                                           + *(float *)(this->m_nimbus[1] + 36);
}

// 0x00443C20
bool CCBFiveNimbusWindow::IsHitRight(float fVal)
{
  return (double)((unsigned int)this->pCtrlButton[2] + LODWORD(this->m_OpenWindow.fWaitTime) - 256) < *(float *)(80 * this->m_nimbus[0] + this->m_nimbus[1] - 40) - fVal * *(float *)&this->m_state[4] * *(float *)&this->m_nimbus[2];
}

// 0x00443C70
bool CCBFiveNimbusWindow::IsHitBottom(float fVal)
{
  return (double)(int)this->pCtrlButton[2] > fVal * *(float *)&this->m_state[4] * *(float *)&this->m_nimbus[2]
                                           + *(float *)(this->m_nimbus[1] + 40);
}

// 0x00519B40
CCBUI * CCBFiveNimbusWindow::GetNimbusColor(int nNimbusType)
{
  this->~CCBFiveNimbusWindow();
  if ( (nNimbusType & 1) != 0 )
    operator delete(this);
  return (CCBUI *)this;
}

// 0x00519B60
CCBFiveNimbusWindow::~CCBFiveNimbusWindow()
{
  (((CCBUI *)this))->CCBUI::Render();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x00519F50
void CCBFiveNimbusWindow::Destroy()
{
  UIButtonEX **v2; // esi
  int v3; // ebx
  UIButtonEX *v4; // ecx
  UIButtonEX *v5; // ecx
  UIButtonEX *pMiddle; // ecx
  float fWaitTime; // ecx
  int v8; // ecx

  // [overlay-fix 2026-10-27] C2065: Destroy__ovl_03 无定义/声明（IDA overlay 合成名）——待归属定谳
  // Destroy__ovl_03((int)this);
  v2 = (UIButtonEX **)&this->pCtrlButton[2];
  v3 = 3;
  do
  {
    if ( *v2 )
    {
      (*(void ( **)(UIButtonEX *, int))(*(_DWORD *)((UIWnd *)(*v2)) + 20))(*v2, 1);
      *v2 = 0;
    }
    ++v2;
    --v3;
  }
  while ( v3 );
  v4 = (UIButtonEX *)this->pCtrlButton[0];
  if ( v4 )
  {
    (*(void ( **)(UIButtonEX *, int))(*(_DWORD *)((UIWnd *)v4) + 20))(v4, 1);
    this->pCtrlButton[0] = 0;
  }
  v5 = (UIButtonEX *)this->pCtrlButton[1];
  if ( v5 )
  {
    (*(void ( **)(UIButtonEX *, int))(*(_DWORD *)((UIWnd *)v5) + 20))(v5, 1);
    this->pCtrlButton[1] = 0;
  }
  pMiddle = (UIButtonEX *)this->pMiddle;
  if ( pMiddle )
  {
    (*(void ( **)(UIButtonEX *, int))(*(_DWORD *)((UIWnd *)pMiddle) + 20))(pMiddle, 1);
    this->pMiddle = ((UIButtonEX *)0);
  }
  fWaitTime = this->m_OpenWindow.fWaitTime;
  if ( fWaitTime != 0.0f )
  {
    (*(void ( **)(float, int))(*(_DWORD *)LODWORD(fWaitTime) + 20))(_pal3_coerce_f32(LODWORD(fWaitTime)), 1);
    this->m_OpenWindow.fWaitTime = 0.0f;
  }
  v8 = *(_DWORD *)&this->m_OpenWindow.bOpen;
  if ( v8 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)&this->m_OpenWindow.bOpen = 0;
  }
}

// 0x00519FE0
int CCBFiveNimbusWindow::HandleInput(int a2, unsigned int nVal, int nVal2)
{
  CScreenMode *v5; // eax
  CScreenMode *Instance; // eax
  int v8; // [esp-0x4] [ebp-0x14]

  if ( a2 == 1001 )
  {
    if ( nVal < 0xB5 || nVal > 0xB7 )
      return this->UIWnd::OnMessage(a2, nVal, nVal2);
    (((CCBUI *)this))->CCBUI::GravityDown(nVal - 181);
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa001", 1);
    v8 = 0;
LABEL_11:
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(nVal, nVal2, v8);
    return this->UIWnd::OnMessage(a2, nVal, nVal2);
  }
  if ( a2 == 1006 )
  {
    if ( nVal2 == -1 )
      return this->UIWnd::OnMessage(a2, nVal, nVal2);
    v8 = 1;
    goto LABEL_11;
  }
  if ( a2 == 1007 && nVal2 != -1 )
  {
    v5 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v5))->CScreenMode::AudioSetPosition("wa002", 1);
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(nVal, nVal2, 0);
  }
  return this->UIWnd::OnMessage(a2, nVal, nVal2);
}

// 0x0051A090
BOOL CCBFiveNimbusWindow::AddResultWindowAni(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(g_nSkillItemIDTable[15], -1, 0);
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x0051C9B0
int CCBFiveNimbusWindow::OnMessage(
        
        unsigned int arg0,
        unsigned int a2,
        unsigned int a4)
{
  if ( arg0 == 1001 )
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(a2, a4, 0);
  return this->UIWnd::OnMessage(arg0, a2, a4);
}

// 0x0052E2F0
char CCBFiveNimbusWindow::UpdateAnimation(int nVal)
{
  char result; // al
  char v4; // bl
  float v5; // st7
  float v6; // st7
  float v7; // st7
  float v8; // st7
  float v9; // st7
  float v10; // st7
  float v11; // st7
  float v12; // st7

  result = this->m_bShow;
  if ( !result )
    return result;
  v4 = 0;
  if ( *(float *)&this->m_nimbus[3] >= (double)*(float *)&this->m_OpenWindow.nOpenFlag )
  {
    if ( *(float *)&this->m_nimbus[3] <= (double)*(float *)&this->m_OpenWindow.nOpenFlag )
      goto LABEL_9;
    v6 = *(float *)&this->m_nimbus[3] - *(float *)&this->m_state[2];
    *(float *)&this->m_nimbus[3] = v6;
    if ( v6 <= *(float *)&this->m_OpenWindow.nOpenFlag )
    {
      v4 = 0;
      this->m_nimbus[3] = this->m_OpenWindow.nOpenFlag;
      goto LABEL_9;
    }
  }
  else
  {
    v5 = *(float *)&this->m_state[2] + *(float *)&this->m_nimbus[3];
    *(float *)&this->m_nimbus[3] = v5;
    if ( v5 >= *(float *)&this->m_OpenWindow.nOpenFlag )
    {
      this->m_nimbus[3] = this->m_OpenWindow.nOpenFlag;
      goto LABEL_9;
    }
  }
  v4 = 1;
LABEL_9:
  *(float *)&this->m_bcreateok = *(float *)&this->m_bcreateok + *(float *)&this->m_nimbus[3];
  if ( *(float *)&this->m_nimbus[4] >= (double)*(float *)this->m_nimbus )
  {
    if ( *(float *)&this->m_nimbus[4] <= (double)*(float *)this->m_nimbus )
      goto LABEL_16;
    v8 = *(float *)&this->m_nimbus[4] - *(float *)&this->m_state[3];
    *(float *)&this->m_nimbus[4] = v8;
    if ( v8 <= *(float *)this->m_nimbus )
    {
      v4 = 0;
      this->m_nimbus[4] = this->m_nimbus[0];
      goto LABEL_16;
    }
  }
  else
  {
    v7 = *(float *)&this->m_state[3] + *(float *)&this->m_nimbus[4];
    *(float *)&this->m_nimbus[4] = v7;
    if ( v7 >= *(float *)this->m_nimbus )
    {
      v4 = 0;
      this->m_nimbus[4] = this->m_nimbus[0];
      goto LABEL_16;
    }
  }
  v4 = 1;
LABEL_16:
  *(float *)&this->m_bvisible = *(float *)&this->m_nimbus[4] + *(float *)&this->m_bvisible;
  if ( *(float *)this->m_state >= (double)*(float *)&this->m_nimbus[1] )
  {
    if ( *(float *)this->m_state <= (double)*(float *)&this->m_nimbus[1] )
      goto LABEL_23;
    v10 = *(float *)this->m_state - *(float *)&this->m_state[4];
    *(float *)this->m_state = v10;
    if ( v10 <= *(float *)&this->m_nimbus[1] )
    {
      v4 = 0;
      this->m_state[0] = this->m_nimbus[1];
      goto LABEL_23;
    }
  }
  else
  {
    v9 = *(float *)&this->m_state[4] + *(float *)this->m_state;
    *(float *)this->m_state = v9;
    if ( v9 >= *(float *)&this->m_nimbus[1] )
    {
      v4 = 0;
      this->m_state[0] = this->m_nimbus[1];
      goto LABEL_23;
    }
  }
  v4 = 1;
LABEL_23:
  *(float *)&this->m_benable = *(float *)this->m_state + *(float *)&this->m_benable;
  if ( *(float *)&this->m_state[1] >= (double)*(float *)&this->m_nimbus[2] )
  {
    if ( *(float *)&this->m_state[1] <= (double)*(float *)&this->m_nimbus[2] )
      goto LABEL_30;
    v12 = *(float *)&this->m_state[1] - *(float *)&this->m_nimbusStep;
    *(float *)&this->m_state[1] = v12;
    if ( v12 <= *(float *)&this->m_nimbus[2] )
    {
      v4 = 0;
      this->m_state[1] = this->m_nimbus[2];
      goto LABEL_30;
    }
LABEL_29:
    v4 = 1;
    goto LABEL_30;
  }
  v11 = *(float *)&this->m_nimbusStep + *(float *)&this->m_state[1];
  *(float *)&this->m_state[1] = v11;
  if ( v11 < *(float *)&this->m_nimbus[2] )
    goto LABEL_29;
  v4 = 0;
  this->m_state[1] = this->m_nimbus[2];
LABEL_30:
  *(float *)&this->m_bfocus = *(float *)&this->m_state[1] + *(float *)&this->m_bfocus;
  (((UIScene *)this))->UIScene::CalcViewTransform(1) /* [ROWTABLE] */;
  result = this->m_bShow;
  if ( result )
  {
    if ( !v4 )
      this->m_bLock = 1;
  }
  this->m_bShow = v4;
  return result;
}

// 0x0052F300
int CCBFiveNimbusWindow::GetValue(int nVal)
{
  int result; // eax

  result = nVal;
  this[1].m_state[3] = nVal;
  return result;
}

// 0x0052FBB0
int CCBFiveNimbusWindow::GetSlotA(int nVal)
{
  return (int)(&this[10].m_bShow + 76 * nVal);
}

// 0x0052FC30
int CCBFiveNimbusWindow::GetSlotB(int nVal)
{
  return (int)(&this[19].m_benable + 19 * nVal);
}

// 0x00530BC0
int CCBFiveNimbusWindow::ApplySelection(int nVal)
{
  return (((RoleSystem *)*(RoleSystem **)&this[3].m_OpenWindow.bOpen))->RoleSystem::ApplyRotationAxis(nVal, this[4].m_state[1]);
}
