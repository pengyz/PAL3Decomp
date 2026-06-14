#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CCBFiveNimbusWindow.h"

// 0x00439740
int * CCBFiveNimbusWindow::CreateScriptAndCamera(int id, int parent)
{
  gbCamera *v4; // eax
  gbCamera *v5; // eax
  int *result; // eax
  tagRECT pRect; // [esp+0x8] [ebp-0x1C] BYREF
  int v8; // [esp+0x20] [ebp-0x4]

  memset(&pRect, 0, sizeof(pRect));
  ((PalScript *)this)->Create(id, &pRect, parent);
  v4 = (gbCamera *)operator new(0x178u);
  v8 = 0;
  if ( v4 )
    // [AUTO-COMMENTED] v5 = ((gbCamera *)v4)->gbCamera(gfxMgr);
  else
    v5 = 0;
  *((_DWORD *)this + 73) = v5;
  v8 = -1;
  ((gbCamera *)v5)->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  result = (int *)*((_DWORD *)this + 73);
  *((_DWORD *)this + 58) = 1161527296;
  result[1] = 1161527296;
  *result = 0;
  *((_DWORD *)this + 62) = 0;
  return result;
}

// 0x0043A070
int CCBFiveNimbusWindow::SetFloatParam(float value)
{
  int v3; // ecx

  *((float *)this + 58) = value;
  v3 = *((_DWORD *)this + 73);
  *(float *)(v3 + 4) = value;
  *(_DWORD *)v3 = 0;
  return LODWORD(value);
}

// 0x0043FD20
int CCBFiveNimbusWindow::CalcHitAngle(int nVal)
{
  int result; // eax
  double v3; // st7
  double v4; // st6

  result = nVal;
  this->m_pbktex = (gbTexture *)nVal;
  if ( !nVal )
  {
    v3 = (double)this->m_rect.right - *(float *)&this->m_state[3] - *(float *)&this->m_state[1];
    v4 = (double)this->m_rect.left + *(float *)&this->m_state[2];
    goto LABEL_5;
  }
  result = nVal - 1;
  if ( nVal == 1 )
  {
    v3 = (double)this->m_rect.bottom - *(float *)&this->m_nimbusStep - *(float *)&this->m_state[1];
    v4 = (double)this->m_rect.top + *(float *)&this->m_state[4];
LABEL_5:
    *(float *)&this->m_nimbus[3] = v3 - (v4 + *(float *)&this->m_state[1]);
  }
  *(float *)this->m_state = *(float *)&this->m_nimbus[3] / *(float *)&this->m_nimbus[4];
  *(float *)&this->m_bShow = *(float *)&this->m_nimbus[4] / *(float *)&this->m_nimbus[3];
  return result;
}

// 0x00443AF0
int CCBFiveNimbusWindow::UpdateDisplay()
{
  int result; // eax
  int v2; // esi
  int v3; // eax
  double v4; // st7
  int v5; // edx
  int v6; // edx
  double v7; // st7
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
        v4 = (double)*(int *)(v3 + 4);
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
  v7 = (double)*(int *)(v6 + 24) - *(float *)(v6 + 40);
  this->m_state[0] = 0;
  this->m_nimbus[4] = 0;
  *(float *)&this->m_state[2] = v7;
  return result;
}

// 0x00443BA0
bool CCBFiveNimbusWindow::IsHitLeft(float fVal)
{
  return (double)((unsigned int)this->pMiddle + (unsigned int)this->pCtrlButton[1] - 256) < *(float *)(80 * this->m_nimbus[0] + this->m_nimbus[1] - 44)
                                                                                          - fVal
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

// 0x00519B60
void CCBFiveNimbusWindow::_CCBFiveNimbusWindow()
{
  ((CCBUI *)this)->Render();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00519FE0
int CCBFiveNimbusWindow::HandleInput(int a2, unsigned int nVal, int nVal2)
{
  CScreenMode *v5; // eax
  CScreenMode *Instance; // eax

  if ( a2 == 1001 )
  {
    if ( nVal < 0xB5 || nVal > 0xB7 )
      return ((PalScript *)this)->OnMessage(a2, nVal, nVal2);
    ((CCBUI *)this)->GravityDown(nVal - 181);
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa001", 1);
LABEL_11:
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(nVal, nVal2);
    return ((PalScript *)this)->OnMessage(a2, nVal, nVal2);
  }
  if ( a2 == 1006 )
  {
    if ( nVal2 == -1 )
      return ((PalScript *)this)->OnMessage(a2, nVal, nVal2);
    goto LABEL_11;
  }
  if ( a2 == 1007 && nVal2 != -1 )
  {
    v5 = CScreenMode::GetInstance();
    ((CScreenMode *)v5)->AudioSetPosition("wa002", 1);
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(nVal, nVal2);
  }
  return ((PalScript *)this)->OnMessage(a2, nVal, nVal2);
}

// 0x0051B570
void CCBFiveNimbusWindow::HandleInput(CCBItemWindow *thisa)
{
  int a3; // [esp+0xC] [ebp+0x8]

  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(214, -1);
  }
  ((UIListBox *)this)->Update((int)thisa, a3);
}

// 0x0051C9B0
int CCBFiveNimbusWindow::OnMessage(
        
        CCBSkillWindow *thisa,
        unsigned int a3,
        unsigned int a2,
        unsigned int a5)
{
  if ( thisa == (CCBSkillWindow *)1001 )
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(a3, a2);
  return ((PalScript *)this)->OnMessage((int)thisa, a3, a2);
}

// 0x0052E2F0
char CCBFiveNimbusWindow::UpdateAnimation(int nVal)
{
  char result; // al
  char v4; // bl
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7

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
  ((UIScene *)this)->CalcViewTransform(1);
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
int CCBFiveNimbusWindow::fn_52F300(int nVal)
{
  *((_DWORD *)this + 75) = nVal;
  return nVal;
}

// 0x0052FBB0
int CCBFiveNimbusWindow::GetSlotA(int nVal)
{
  return (int)this + 76 * nVal + 1752;
}

// 0x0052FC30
int CCBFiveNimbusWindow::GetSlotB(int nVal)
{
  return (int)this + 76 * nVal + 3100;
}

// 0x00530BC0
int CCBFiveNimbusWindow::ApplySelection(int nVal)
{
  return ((RoleSystem *)*((RoleSystem **)this + 145))->ApplyRotationAxis(nVal, *((_BYTE *)this + 772));
}
