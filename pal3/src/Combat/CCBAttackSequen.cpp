#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBAttackSequen.h"

// Forward declarations for unnamed functions
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations
int sub_445E50(int a2); // from annotations
void sub_446030(_DWORD *newElement); // from annotations

// Unnamed globals (extern)
extern void * off_5E7F24;
extern unsigned int unk_5DFDEC;

// 0x004DB5C0
int CCBAttackSequen::ResetTimers()
{
  float *v2; // eax
  int v3; // ecx
  float *p_fLastTime; // eax
  int v5; // ecx

  if ( this->m_bPause || !this->m_bEnable )
  {
    p_fLastTime = &this->m_Sequen[0].fLastTime;
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
    v2 = &this->m_Sequen[0].fLastTime;
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


  return this->AdvanceStep();
}

// 0x004DB910
double CCBAttackSequen::SetPause()
{
  double result; // st7
  char v2; // [esp+0x4] [ebp+0x4]

  this->m_bPause = v2;
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
  p_nSlot2 = &this->m_Sequen[0].nSlot2;
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
  _BYTE *p_bSlot2Running; // esi
  char result; // al
  double v5; // st7

  v2 = 76;
  p_bSlot2Running = &this->m_Sequen[0].bSlot2Running;
  do
  {
    result = p_bSlot2Running[2];
    if ( result )
    {
      if ( *p_bSlot2Running )
        v5 = (double)*(int *)(p_bSlot2Running - 10) * 0.0078260871 + 659.0;
      else
        v5 = (double)*(int *)(p_bSlot2Running - 14) * 0.017130435 + 460.0;
// [VFTABLE] result = sub_445D20(*(_DWORD **)((char *)&this->m_pUI->__vftable + v2), (__int64)v5, 8);
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
  p_bSlot2Running = &this->m_Sequen[0].bSlot2Running;
  do
  {
    if ( this->m_pRole->m_Role[0].bMagicMastered[5][v3 + 4] )
    {
      p_bSlot2Running[2] = 1;
      *p_bSlot2Running = 0;
      *(p_bSlot2Running - 2) = ((CCBSystem *)this)->CalcSpeed(v2, 0);
      *(p_bSlot2Running - 1) = ((CCBSystem *)this)->CalcSpeed(v2, 1);
      *(_DWORD *)(p_bSlot2Running - 10) = 0;
      *(_DWORD *)(p_bSlot2Running - 6) = 0;
    }
    v3 += 892;
    ++v2;
    p_bSlot2Running += 40;
  }
  while ( v3 < 9812 );
  m_pRole = this->m_pRole;
  if ( BYTE2(m_pRole->m_Role[0].dwMagicID[8][4]) )
  {
    result = 0;
    p_nSlot1 = &this->m_Sequen[0].nSlot1;
    do
    {
      if ( this->m_pRole->m_Role[0].bMagicMastered[5][result + 4] )
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
  else if ( BYTE1(m_pRole->m_Role[0].dwMagicID[8][4]) )
  {
    result = 0;
    v8 = &this->m_Sequen[0].nSlot1;
    do
    {
      if ( this->m_pRole->m_Role[0].bMagicMastered[5][result + 4] )
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
      v12 = this->m_pRole;
      if ( v12->m_Role[0].bMagicMastered[5][i + 4] && ((CCBRoleState *)v12)->GetSpeedBonus(v10) > SpeedBonus )
        SpeedBonus = ((CCBRoleState *)this->m_pRole)->GetSpeedBonus(v10);
      ++v10;
    }
    v13 = 0;
    result = 0;
    v17 = 0;
    v14 = &this->m_Sequen[0].nSlot1;
    do
    {
      if ( this->m_pRole->m_Role[0].bMagicMastered[5][result + 4] )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        v15 = ((int)unk_5DFDEC >> 16) & 0x7FFF;
        v16 = 319 * ((CCBRoleState *)this->m_pRole)->GetSpeedBonus(v13);
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
  int result; // eax
  int roleIdx; // [esp+0x1C] [ebp-0x8]

  v1 = 0;
  roleIdx = 0;
  v3 = 76;
  do
  {
    m_pRole = this->m_pRole;
    if ( m_pRole->m_Role[0].bMagicMastered[5][v1 + 4] )
    {
      if ( !((CCBRoleState *)m_pRole)->IsRoleAlive(roleIdx)
        || *((_BYTE *)&this->m_pRole->m_Role[2].fSkillCentInc + v1 + 1) == 1 )
      {
// [VFTABLE] (***(void ( ****)(_DWORD, _DWORD))((char *)&this->m_pUI->__vftable + v3))(
// [VFTABLE]   *(vtbl_0056AE2C **)((char *)&this->m_pUI->__vftable + v3),
// [VFTABLE]   0);
      }
      else
      {
        m_pUI = this->m_pUI;
        if ( m_pUI->m_pAttackSequenBack->m_bvisible == 1 )
// [VFTABLE] (***(void ( ****)(_DWORD, int))((char *)&m_pUI->__vftable + v3))(
// [VFTABLE]   *(vtbl_0056AE2C **)((char *)&m_pUI->__vftable + v3),
// [VFTABLE]   1);
        if ( *(_BYTE *)(*(_DWORD *)((char *)this->m_pCBSystem->m_pStage + v3 - 52) + 280) )
// [VFTABLE] sub_446030(*(_DWORD **)((char *)&this->m_pUI->__vftable + v3));
// [VFTABLE] ((NPC *)*(NPC **)((char *)&this->m_pUI->__vftable + v3))->UpdateAnim();
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

// 0x005270C0
int CCBAttackSequen::FindSequenceSlot(int nVal)
{
  int result; // eax
  int v3; // edx
  int *p_nIndex; // esi
  int *v5; // edx

  result = 0;
  v3 = 0;
  p_nIndex = &this->m_Sequen[10].nIndex;
  do
  {
    if ( !*((_BYTE *)this + v3 + 15013) )
    {
      ++result;
      p_nIndex[3] = 0;
      *(_BYTE *)p_nIndex = 0;
    }
    ++v3;
    p_nIndex += 62;
  }
  while ( v3 < 5 );
  v5 = &this->m_Sequen[8].nSlot1 + 62 * nVal;
  v5[20] = 1;
  *((_BYTE *)v5 + 68) = 1;
  if ( result )
  {
    if ( *((_BYTE *)this + nVal + 15013) )
      return -1;
  }
  return result;
}

// 0x00527510
void CCBAttackSequen::AdvanceToNextSlot()
{
  int v2; // edx
  int SequenceSlot; // eax
  bool v4; // sf
  bool v5; // cc
  int v6; // eax
  CScreenMode *Instance; // eax
  const void *v8; // [esp-0x8] [ebp-0x10]

  sub_445E50((int)(&this->m_Sequen[8].nSlot1 + 62 * *((_DWORD *)this + 3752)));
  *((_BYTE *)this + *((_DWORD *)this + 3752) + 15013) = 1;
  *((_DWORD *)this + 811) = 0;
  *((_BYTE *)this + 3232) = 0;
  *((_DWORD *)this + 873) = 0;
  *((_BYTE *)this + 3480) = 0;
  (**((void ( ***)(char *, _DWORD))this + 915))((char *)this + 3660, 0);
  v2 = *((_DWORD *)this + 3752);
  *((_BYTE *)this + 15012) = 0;
  *((_DWORD *)this + 3752) = v2 + 1;
  if ( v2 + 1 >= 5 )
    *((_DWORD *)this + 3752) = 0;
  SequenceSlot = this->FindSequenceSlot(*((_DWORD *)this + 3752));
  v4 = SequenceSlot < 0;
  v5 = SequenceSlot <= 0;
  if ( !SequenceSlot )
  {
LABEL_10:
    *((_BYTE *)this + 6204) = 1;
    *((_BYTE *)this + 15038) = 1;
    *((_BYTE *)this + 15037) = 1;
    ((CCBUI *)this)->UpdateCaptions();
    v8 = off_5E7F24;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v8, 1);
    return;
  }
  while ( 1 )
  {
    if ( v4 )
    {
      v6 = *((_DWORD *)this + 3752) + 1;
      *((_DWORD *)this + 3752) = v6;
      if ( v6 >= 5 )
        *((_DWORD *)this + 3752) = 0;
      SequenceSlot = this->FindSequenceSlot(*((_DWORD *)this + 3752));
      goto LABEL_9;
    }
    if ( !v5 )
      break;
LABEL_9:
    v4 = SequenceSlot < 0;
    v5 = SequenceSlot <= 0;
    if ( !SequenceSlot )
      goto LABEL_10;
  }
  ((MUIDialog *)this)->SetSlotCaption(*((_DWORD *)this + 3752));
  *((_BYTE *)this + 6204) = 0;
}
