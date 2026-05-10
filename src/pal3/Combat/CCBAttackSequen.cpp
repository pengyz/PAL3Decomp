#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBAttackSequen.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/NPC.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_446030(...);

// 0x004DB5C0
int CCBAttackSequen::Update()
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
  this->ProcessQueue();
  this->CheckComplete();
  return this->AdvanceStep();
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
      LOBYTE(v4) = ((CCBRoleState *)this->m_pCBSystem->m_pRoleState)->IsRoleAlive(v2);
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
  unsigned __int8 *p_bSlot2Running; // esi
  char result; // al
  double v5; // st7

  v2 = 76;
  p_bSlot2Running = (unsigned __int8 *)&this->m_Sequen[0].bSlot2Running;
  do
  {
    result = p_bSlot2Running[2];
    if ( result )
    {
      if ( *p_bSlot2Running )
        v5 = (double)*(int *)(p_bSlot2Running - 10) * 0.0078260871 + 659.0;
      else
        v5 = (double)*(int *)(p_bSlot2Running - 14) * 0.017130435 + 460.0;
      result = ((UIWnd *)*(UIWnd **)&this->m_pUI->_data[v2])->ScreenToClient((__int64)v5, 8);
    }
    v2 += 4;
    p_bSlot2Running += 40;
  }
  while ( v2 < 120 );
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
  int v9; // [esp+Ch] [ebp-18h]
  float v10; // [esp+14h] [ebp-10h]
  float v11; // [esp+14h] [ebp-10h]
  float v12; // [esp+18h] [ebp-Ch]
  int roleIdx; // [esp+1Ch] [ebp-8h]
  int v14; // [esp+20h] [ebp-4h]

  v1 = 0;
  roleIdx = 0;
  v3 = 76;
  do
  {
    m_pRole = (CCBRoleState *)this->m_pRole;
    if ( *(&m_pRole->m_Role[0].bValid + v1 * 4) )
    {
      if ( !m_pRole->IsRoleAlive(roleIdx)
        || LOBYTE(this->m_pRole->m_Role[0].nSpecStateRound[v1 + 10]) == 1 )
      {
        (***(void (****)(_DWORD, _DWORD))&this->m_pUI->_data[v3])(*(_DWORD *)&this->m_pUI->_data[v3], 0);
      }
      else
      {
        m_pUI = (CCBUI *)this->m_pUI;
        if ( *(_DWORD *)(*(_DWORD *)&m_pUI->_data[72] + 56) == 1 )
          (***(void (****)(_DWORD, int))&m_pUI->_data[v3])(*(_DWORD *)&m_pUI->_data[v3], 1);
        v14 = -1;
        if ( *(_BYTE *)(*(_DWORD *)((char *)this->m_pCBSystem->m_pStage + v3 - 52) + 280) )
        {
          v6 = sin(this->m_pCBSystem->m_fTimeFund * 16.0);
          v10 = v6;
          v11 = v10 * 50.0;
          v9 = (int)v11;
          if ( v3 < 96 )
          {
            v7 = v9 - 56;
            BYTE2(v14) = v9 - 56;
          }
          else
          {
            v12 = v6 * 125.0;
            v7 = (int)v12 + 126;
          }
          BYTE1(v14) = v7;
          LOBYTE(v14) = v7;
          sub_446030(*(_DWORD **)&this->m_pUI->_data[v3]);
        }
        v14->UpdateAnim();
      }
    }
    v3 += 4;
    result = roleIdx + 1;
    v1 += 223;
    ++roleIdx;
  }
  while ( v3 < 120 );
  return result;
}
