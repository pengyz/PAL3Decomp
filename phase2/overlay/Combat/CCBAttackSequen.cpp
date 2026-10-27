#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBAttackSequen.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Role/NPC.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/tagRoleState.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x004DB5C0
int CCBAttackSequen::ResetTimers()
{
  float *v2; // eax
  int v3; // ecx
  float *p_fLastTime; // eax
  int v5; // ecx

  if ( this->m_bPause || !this->m_bEnable )
  {
    p_fLastTime = (float *)&this->m_Sequen[0].fLastTime;
    v5 = 11;
    do
    {
      *(p_fLastTime - 1) = 0.0;
      p_fLastTime += 10;
      --v5;
      *(p_fLastTime - 10) = this->m_pCBSystem->m_fTimeFund;
    }
    while ( v5 );
  }
  else
  {
    v2 = (float *)&this->m_Sequen[0].fLastTime;
    v3 = 11;
    do
    {
      if ( *((_BYTE *)v2 + 31) )
        *(v2 - 1) = 0.0;
      else
        *(v2 - 1) = this->m_pCBSystem->m_fTimeFund - *v2;
      v2 += 10;
      --v3;
      *(v2 - 10) = this->m_pCBSystem->m_fTimeFund;
    }
    while ( v3 );
  }
  this->CCBAttackSequen::ProcessQueue();
  this->CCBAttackSequen::CheckComplete();
  return this->CCBAttackSequen::AdvanceStep();
}

// 0x004DB640
int CCBAttackSequen::CalcSpeed(int roleIdx, int nVal)
{
  return 5 * ((((CCBRoleState *)this->m_pRole))->CCBRoleState::GetSpeedBonus(roleIdx) + 4);
}

// 0x004DB660
int CCBAttackSequen::GetCmdSlot(int idx)
{
  char *v3; // ebx
  int result; // eax

  v3 = (char *)this + 40 * idx;
  v3[44] = this->CCBAttackSequen::CalcSpeed(idx, 0);
  result = this->CCBAttackSequen::CalcSpeed(idx, 1);
  v3[45] = result;
  return result;
}

// 0x004DB7A0
int CCBAttackSequen::ProcessAllCmds()
{
  int v2; // edi
  int v3; // esi
  int *p_nSlot2; // ebx
  CCBRoleState *m_pRole; // ecx
  CCBRoleState *v6; // ecx
  float v7; // st7
  float v9; // [esp+0x10] [ebp-0xC]
  int v10; // [esp+0x14] [ebp-0x8]

  v2 = 0;
  v9 = 100000000.0f;
  v10 = -1;
  v3 = 0;
  p_nSlot2 = (int *)&this->m_Sequen[0].nSlot2;
  do
  {
    m_pRole = (CCBRoleState *)this->m_pRole;
    if ( m_pRole->m_pObjMsgBuffer[v3 + 153] )
    {
      if ( !(((CCBRoleState *)m_pRole))->CCBRoleState::IsActive(v2) )
      {
        v6 = (CCBRoleState *)this->m_pRole;
        if ( !v6->m_info.depend_scenename[v3 + 26]
          && !HIBYTE((((CCBRoleState *)v6))->CCBRoleState::InitUI(v2)[1].dwMagicID[2][4])
          && (((CCBRoleState *)this->m_pRole))->CCBRoleState::SetRoleField(v2, 0) > 0 )
        {
          if ( *((_BYTE *)p_nSlot2 + 10) )
            v7 = (float)(11500 - *p_nSlot2) / ((float)*((unsigned __int8 *)p_nSlot2 + 9) * 50.0f);
          else
            v7 = (float)(11500 - *(p_nSlot2 - 1)) / ((float)*((unsigned __int8 *)p_nSlot2 + 8) * 50.0f) + 10000.0f;
          if ( v7 < v9 )
          {
            v9 = v7;
            v10 = v2;
          }
        }
      }
    }
    v3 += 892;
    ++v2;
    p_nSlot2 += 10;
  }
  while ( v3 < 9812 );
  return v10;
}

// 0x004DB910
double CCBAttackSequen::SetPause(char bPause)
{
  double result; // st7

  this->m_bPause = bPause;
  return result;
}

// 0x004DBA60
char CCBAttackSequen::ProcessQueue()
{
  int v2; // ebx
  int *p_nSlot2; // esi
  __int64 v4; // rax
  int v5; // edi

  v2 = 0;
  p_nSlot2 = (int *)&this->m_Sequen[0].nSlot2;
  do
  {
    LOBYTE(v4) = *((_BYTE *)p_nSlot2 + 12);
    if ( (_BYTE)v4 )
    {
      LOBYTE(v4) = (((CCBRoleState *)this->m_pCBSystem->m_pRoleState))->CCBRoleState::IsRoleAlive(v2);
      if ( (_BYTE)v4 )
      {
        if ( *((_BYTE *)p_nSlot2 + 10) )
        {
          v4 = (__int64)((double)*((unsigned __int8 *)p_nSlot2 + 9) * (*((float *)p_nSlot2 - 6) * 50.0)
                       + (double)*p_nSlot2);
          *p_nSlot2 = v4;
          if ( (int)v4 > 11500 )
            *p_nSlot2 = 11500;
        }
        else
        {
          v5 = *(p_nSlot2 - 1);
          v4 = (__int64)(*((float *)p_nSlot2 - 6) * 50.0 * (double)*((unsigned __int8 *)p_nSlot2 + 8) + (double)v5);
          *(p_nSlot2 - 1) = v4;
          if ( (int)v4 >= 11500 )
          {
            if ( v5 < 11500 )
              ++p_nSlot2[1];
            *(p_nSlot2 - 1) = 11500;
          }
        }
      }
    }
    ++v2;
    p_nSlot2 += 10;
  }
  while ( v2 < 11 );
  return v4;
}

// 0x004DBB20
char CCBAttackSequen::CheckComplete()
{
  int v2; // edi
  _BYTE *p_bSlot2Running; // esi
  char result; // al
  float v5; // st7

  v2 = 76;
  p_bSlot2Running = (_BYTE *)&this->m_Sequen[0].bSlot2Running;
  do
  {
    result = p_bSlot2Running[2];
    if ( result )
    {
      if ( *p_bSlot2Running )
        v5 = (float)*(int *)(p_bSlot2Running - 10) * 0.007826087065041065f + 659.0f;
      else
        v5 = (float)*(int *)(p_bSlot2Running - 14) * 0.01713043451309204f + 460.0f;
      result = (((UIWnd *)*(UIWnd **)((char *)((UIWnd *)this->m_pUI) + v2)))->UIWnd::MoveToAbsolute((__int64)v5, 8);
    }
    v2 += 4;
    p_bSlot2Running += 40;
  }
  while ( v2 < 120 );
  return result;
}

// 0x004DBB80
int CCBAttackSequen::CalcTurnOrder()
{
  int v2; // ebp
  int v3; // ebx
  _BYTE *p_bSlot2Running; // esi
  CCBRoleState *m_pRole; // eax
  int result; // eax
  int *p_nSlot1; // ecx
  int *v8; // ecx
  int SpeedBonus; // ebp
  int v10; // ebx
  int i; // esi
  CCBRoleState *v12; // ecx
  int v13; // ebp
  int *v14; // ebx
  int v15; // esi
  int v16; // ecx
  int v17; // [esp+0x10] [ebp-0x4]

  v2 = 0;
  v3 = 0;
  p_bSlot2Running = (_BYTE *)&this->m_Sequen[0].bSlot2Running;
  do
  {
    if ( this->m_pRole->m_pObjMsgBuffer[v3 + 153] )
    {
      p_bSlot2Running[2] = 1;
      *p_bSlot2Running = 0;
      *(p_bSlot2Running - 2) = this->CCBAttackSequen::CalcSpeed(v2, 0);
      *(p_bSlot2Running - 1) = this->CCBAttackSequen::CalcSpeed(v2, 1);
      *(_DWORD *)(p_bSlot2Running - 10) = 0;
      *(_DWORD *)(p_bSlot2Running - 6) = 0;
    }
    v3 += 892;
    ++v2;
    p_bSlot2Running += 40;
  }
  while ( v3 < 9812 );
  m_pRole = (CCBRoleState *)this->m_pRole;
  if ( m_pRole->m_pObjMsgBuffer[113] )
  {
    result = 0;
    p_nSlot1 = (int *)&this->m_Sequen[0].nSlot1;
    do
    {
      if ( this->m_pRole->m_pObjMsgBuffer[result + 153] )
      {
        if ( result < 4460 )
          *p_nSlot1 = 0;
        else
          *p_nSlot1 = 11500;
      }
      result += 892;
      p_nSlot1 += 10;
    }
    while ( result < 9812 );
  }
  else if ( m_pRole->m_pObjMsgBuffer[112] )
  {
    result = 0;
    v8 = (int *)&this->m_Sequen[0].nSlot1;
    do
    {
      if ( this->m_pRole->m_pObjMsgBuffer[result + 153] )
      {
        if ( (unsigned int)result >= 0x116C )
          *v8 = 0;
        else
          *v8 = 11500;
      }
      result += 892;
      v8 += 10;
    }
    while ( result < 9812 );
  }
  else
  {
    SpeedBonus = 0;
    v10 = 0;
    for ( i = 0; i < 9812; i += 892 )
    {
      v12 = (CCBRoleState *)this->m_pRole;
      if ( v12->m_pObjMsgBuffer[i + 153] && (((CCBRoleState *)v12))->CCBRoleState::GetSpeedBonus(v10) > SpeedBonus )
        SpeedBonus = (((CCBRoleState *)this->m_pRole))->CCBRoleState::GetSpeedBonus(v10);
      ++v10;
    }
    v13 = 0;
    result = 0;
    v17 = 0;
    v14 = (int *)&this->m_Sequen[0].nSlot1;
    do
    {
      if ( this->m_pRole->m_pObjMsgBuffer[result + 153] )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
        v15 = ((int)g_nCombatRandSeed >> 16) & 0x7FFF;
        v16 = 319 * (((CCBRoleState *)this->m_pRole))->CCBRoleState::GetSpeedBonus(v13);
        result = v17;
        *v14 = v15 % 638 + 2 * v16;
      }
      result += 892;
      ++v13;
      v14 += 10;
      v17 = result;
    }
    while ( result < 9812 );
  }
  return result;
}

// 0x004DBD40
int CCBAttackSequen::AdvanceStep()
{
  int v1; // ebx
  int v3; // esi
  CCBRoleState *m_pRole; // ecx
  CCBUI *m_pUI; // eax
  long double v6; // st7
  char v7; // al
  int result; // eax
  int v9; // [esp+0xC] [ebp-0x18]
  float v10; // [esp+0x14] [ebp-0x10]
  float v11; // [esp+0x14] [ebp-0x10]
  float v12; // [esp+0x18] [ebp-0xC]
  int roleIdx; // [esp+0x1C] [ebp-0x8]
  int v14; // [esp+0x20] [ebp-0x4]

  v1 = 0;
  roleIdx = 0;
  v3 = 76;
  do
  {
    m_pRole = (CCBRoleState *)this->m_pRole;
    if ( m_pRole->m_pObjMsgBuffer[v1 + 153] )
    {
      if ( !(((CCBRoleState *)m_pRole))->CCBRoleState::IsRoleAlive(roleIdx) || this->m_pRole->m_info.depend_scenename[v1 + 26] == 1 )
      {
        (***(void ( ****)(_DWORD, _DWORD))((char *)((UIWnd *)this->m_pUI) + v3))((_DWORD)(*(_DWORD *)((char *)((UIWnd *)this->m_pUI) + v3)), (_DWORD)(0));
      }
      else
      {
        m_pUI = (CCBUI *)this->m_pUI;
        if ( m_pUI->m_pAttackSequenBack->m_bvisible == 1 )
          (***(void ( ****)(_DWORD, int))((char *)((UIWnd *)m_pUI) + v3))((_DWORD)(*(_DWORD *)((char *)((UIWnd *)m_pUI) + v3)), (int)(1));
        v14 = -1;
        if ( *(_BYTE *)(*(_DWORD *)((char *)this->m_pCBSystem->m_pStage + v3 - 52) + 280) )
        {
          v6 = sin(this->m_pCBSystem->m_fTimeFund * 16.0);
          v10 = v6;
          v11 = v10 * 50.0f;
          v9 = (int)v11;
          if ( v3 < 96 )
          {
            v7 = v9 - 56;
            BYTE2(v14) = v9 - 56;
          }
          else
          {
            v12 = v6 * 125.0f;
            v7 = (int)v12 + 126;
          }
          BYTE1(v14) = v7;
          LOBYTE(v14) = v7;
          sub_446030(*(_DWORD **)((char *)((UIWnd *)this->m_pUI) + v3));
        }
        (((NPC *)*(NPC **)((char *)((UIWnd *)this->m_pUI) + v3)))->NPC::UpdateAnim(v14);
      }
    }
    v3 += 4;
    result = roleIdx + 1;
    v1 += 892;
    ++roleIdx;
  }
  while ( v3 < 120 );
  return result;
}

// 0x004DBE60
void CCBAttackSequen::InitCombatSlot(int roleIdx)
{
  char *v3; // edi
  tagRoleState *inited; // eax

  if ( this->m_pRole->m_pObjMsgBuffer[892 * roleIdx + 153] )
  {
    v3 = (char *)this + 40 * roleIdx;
    v3[48] = 1;
    v3[46] = 0;
    v3[44] = this->CCBAttackSequen::CalcSpeed(roleIdx, 0);
    v3[45] = this->CCBAttackSequen::CalcSpeed(roleIdx, 1);
    *((_DWORD *)v3 + 8) = 0;
    *((_DWORD *)v3 + 9) = 0;
    this->m_Sequen[roleIdx].nRound = 0;
    inited = (((CCBRoleState *)this->m_pRole))->CCBRoleState::InitUI(roleIdx);
    // [overlay-fix 2026-10-27] C2065: Buffer 无声明（Hex-Rays 局部名泄漏，声明丢失）——待语义修复
    // sprintf(Buffer, "%s\\%s.tga", "ui\\combat\\attacksequen", inited->sModel);
    // (((UIPushButton *)*((UIPushButton **)&this->m_pUI->pPanel + roleIdx)))->UIPushButton::CreateFromTemplate(Buffer, 0);
  }
}

// 0x005270C0
int CCBAttackSequen::FindSequenceSlot(int nVal)
{
  int result; // eax
  int v3; // edx
  int *p_nIndex; // esi
  int *v5; // edx

  result = 0;
  v3 = 0;
  p_nIndex = (int *)&this->m_Sequen[10].nIndex;
  do
  {
    if ( !*((_BYTE *)&this[32].m_Sequen[10].nIndex + v3 + 1) )
    {
      ++result;
      p_nIndex[3] = 0;
      *(_BYTE *)p_nIndex = 0;
    }
    ++v3;
    p_nIndex += 62;
  }
  while ( v3 < 5 );
  v5 = (int *)(&this->m_Sequen[8].nSlot1 + 62 * nVal);
  v5[20] = 1;
  *((_BYTE *)v5 + 68) = 1;
  if ( result )
  {
    if ( *((_BYTE *)&this[32].m_Sequen[10].nIndex + nVal + 1) )
      return -1;
  }
  return result;
}
