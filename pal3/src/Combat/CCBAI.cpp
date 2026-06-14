#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBAI.h"

// Unnamed globals (extern)
extern char byte_1010101;
extern int dword_17A89C8;
extern int dword_17A89CC;
extern int dword_17A89D0;
extern int dword_17A89D4;
extern int dword_17A89D8;
extern int dword_17A89DC;
extern int dword_17A89E0;
extern int dword_17A89E4;
extern unsigned int unk_5DFDEC;

// 0x0040CFE0
void * CCBAI::GetTargetRole(void *pOut)
{
  _DWORD *v2; // edx
  int v4; // [esp+0xC] [ebp+0x8]

  v2 = (_DWORD *)(*(_DWORD *)&this->m_bNewRole[4] + 12 * v4);
  *(_DWORD *)pOut = *v2;
  *((_DWORD *)pOut + 1) = v2[1];
  *((_DWORD *)pOut + 2) = v2[2];
  return pOut;
}

// 0x004D6FF0
CCBAI::CCBAI()
{
  dword_17A89C8 = 121;
  dword_17A89CC = 316;
  dword_17A89D0 = 512;
  dword_17A89D4 = 709;
}

// 0x004D7030
// attributes: thunk
void CCBAI::_CCBAI()
{

}

// 0x004D7040
void CCBAI::Reset()
{
  dword_17A89D8 = 573;
  dword_17A89DC = 573;
  dword_17A89E0 = 573;
  dword_17A89E4 = 573;
}

// 0x004D7080
CCBAI * CCBAI::Create(int *p_DWORD)
{
  memset(this, 0, sizeof(CCBAI));
  this->m_pCBSystem = (CCBSystem *)p_DWORD;
  this->m_pRoleState = (CCBRoleState *)p_DWORD[4];
  this->m_pUtil = (CUtil *)*p_DWORD;
  return this;
}

// 0x004D70C0
bool CCBAI::Init()
{
  memset(this->m_Demand, 0, sizeof(this->m_Demand));
  memset(this->m_EnemyDemand, 0, 0xA0u);
  memset(this->m_FriendDemand, 0, 0xA0u);


  return 1;
}

// 0x004D7100
void CCBAI::Update()
{


}

// 0x004D7120
void CCBAI::Render(int nVal)
{
  CCBStageRole *v3; // eax
  char RoleField; // al
  CCBRoleState *m_pRoleState; // ecx

  if ( ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nVal, 0) > 0 )
  {
    v3 = this->m_pCBSystem->m_pStage->m_pRole[nVal];
    v3->m_Task[63].vec1.z = *(float *)&v3->m_Task[63].cmd.dwCmdKind;
  }
  RoleField = ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nVal, 18);
  m_pRoleState = this->m_pRoleState;
  if ( RoleField )
  {
    if ( ((CCBRoleState *)m_pRoleState)->GetRoleAttr(nVal) != 5 )
      this->ChooseRandomAction(nVal);
  }
  else
  {
    switch ( ((CCBRoleState *)m_pRoleState)->GetRoleAttr(nVal) )
    {
      case 1:
      case 2:
        this->HandleEnemyAction(nVal);
        break;
      case 3:
        this->HandleEnemyWell(nVal);
        break;
      case 4:
        this->HandleEnemyWeak(nVal);
        break;
      default:
        return;
    }
  }
}

// 0x004D71E0
bool CCBAI::HandleEnemyAction(int nRoleIndex)
{
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // edi
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v9; // ecx
  char v10; // al
  char v11; // al
  int v12; // [esp+0x38] [ebp-0xC]
  tagDemand *nVal; // [esp+0x3C] [ebp-0x8]
  int roleIdx; // [esp+0x40] [ebp-0x4]

  if ( this->CastReviveSkill(nRoleIndex) )
    return 1;
  v4 = unk_5DFDEC;
  v5 = 0;
  roleIdx = 0;
  while ( 1 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    v4 = 214013 * v4 + 2531011;
    unk_5DFDEC = v4;
    if ( ((v4 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v5 + 4] )
        break;
    }
    v5 += 892;
    v6 = ++roleIdx;
    if ( v5 >= 9812 )
      goto LABEL_9;
  }
  v6 = roleIdx;
LABEL_9:
  if ( v6 == 10 )
  {
    roleIdx = 0;
    v6 = 0;
LABEL_12:
    v7 = 892 * v6;
    v12 = 892 * v6;
    for ( nVal = &this->m_Demand[0][10 * v6 + 4]; ; nVal += 10 )
    {
      m_pRoleState = this->m_pRoleState;
      if ( m_pRoleState->m_Role[0].bMagicMastered[5][v7 + 4] )
      {
        if ( !((CCBRoleState *)m_pRoleState)->IsRoleAlive(v6)
          || (v9 = this->m_pRoleState, v9->m_Role[0].bMagicMastered[6][v7 + 4] == 1) )
        {
          v6 = roleIdx;
        }
        else
        {
          if ( (unsigned int)v7 < 0x116C
            || ((CCBRoleState *)v9)->GetRoleField(nRoleIndex, 19)
            && (++*(_DWORD *)&g_TempBuffer1024[912],
                unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
                (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7)
            || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 18)
            && (++*(_DWORD *)&g_TempBuffer1024[912],
                unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
                (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7) )
          {
            if ( nVal[2].nSatisfy < 100 )
            {
              this->DemandChecker(nRoleIndex, roleIdx, (int)&nVal[2]);
              if ( v10 == 1 )
                return 1;
            }
          }
          if ( this->m_EnemyDemand[1].nSatisfy < 100
            && this->CastRecoverMagic(nRoleIndex, (int)&this->m_EnemyDemand[1]) )
          {
            return 1;
          }
          if ( v7 >= 4460 )
          {
            if ( v7 < 9812
              && nVal[-3].nSatisfy < 100
              && this->CastNormalAttack(nRoleIndex, roleIdx, (int)&nVal[-3]) )
            {
              return 1;
            }
            if ( v7 < 9812 && nVal->nSatisfy < 100 )
            {
              ++*(_DWORD *)&g_TempBuffer1024[912];
              unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
              if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)512.0
                && this->CastAttackBigItem(nRoleIndex, roleIdx, (int)nVal) )
              {
                return 1;
              }
            }
          }
          if ( this->m_nHandleEnemyWell < 100 )
          {
            ++*(_DWORD *)&g_TempBuffer1024[912];
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)378.88
              && this->CastAttackMagic(nRoleIndex, (int)&this->m_nHandleEnemyWell) )
            {
              return 1;
            }
            if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleType(nRoleIndex) )
            {
              ++*(_DWORD *)&g_TempBuffer1024[912];
              unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
              if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)307.19998 )
              {
                if ( ((AStarPathFinder *)this)->GetHeuristicIdx(nRoleIndex, (int)&this->m_nHandleEnemyWell) )
                {
                  return 1;
                }
              }
            }
          }
          if ( v12 >= 0 )
          {
            if ( v12 >= 4460 )
            {
              if ( v12 < 9812 )
              {
                ++*(_DWORD *)&g_TempBuffer1024[912];
                unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
                if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)307.19998 )
                {
                  if ( nVal[-3].nSatisfy < 100 && this->CastNormalAttack(nRoleIndex, roleIdx, 0) )
                    return 1;
                  ++*(_DWORD *)&g_TempBuffer1024[912];
                  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
                  if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)307.19998
                    && this->CastAttackBigMagic(nRoleIndex, roleIdx) )
                  {
                    return 1;
                  }
                }
              }
            }
            else
            {
              ++*(_DWORD *)&g_TempBuffer1024[912];
              unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
              if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)153.59999
                && (this->CastAttackMagic(nRoleIndex, 0)
                 || this->CastRecoverBigMagic(nRoleIndex, roleIdx, 0)) )
              {
                return 1;
              }
            }
          }
          if ( (unsigned int)v12 < 0x116C
            || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19)
            && (++*(_DWORD *)&g_TempBuffer1024[912],
                unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
                (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7)
            || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 18)
            && (++*(_DWORD *)&g_TempBuffer1024[912],
                unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
                (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7) )
          {
            this->DemandChecker(nRoleIndex, roleIdx, 0);
            if ( v11 )
              return 1;
          }
          v6 = roleIdx;
          v7 = v12;
        }
      }
      v7 += 892;
      roleIdx = ++v6;
      v12 = v7;
      if ( v7 >= 9812 )
        return 0;
    }
  }
  if ( v6 < 11 )
    goto LABEL_12;
  return 0;
}

// 0x004D7820
bool CCBAI::HandleEnemyWell(int nRoleIndex)
{
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // edi
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v8; // ecx
  char v9; // al
  int v10; // edx
  int v11; // edx
  int v12; // edi
  char v13; // al
  char v14; // al
  tagDemand *pDemand; // [esp+0x40] [ebp-0xC]
  int v17; // [esp+0x44] [ebp-0x8]
  int roleIdx; // [esp+0x48] [ebp-0x4]

  v3 = unk_5DFDEC;
  v4 = 0;
  roleIdx = 0;
  while ( 1 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    v3 = 214013 * v3 + 2531011;
    unk_5DFDEC = v3;
    if ( ((v3 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v4 + 4] )
        break;
    }
    v4 += 892;
    v5 = ++roleIdx;
    if ( v4 >= 9812 )
      goto LABEL_7;
  }
  v5 = roleIdx;
LABEL_7:
  if ( v5 == 10 )
  {
    roleIdx = 0;
    v5 = 0;
LABEL_10:
    v6 = 892 * v5;
    v17 = 892 * v5;
    for ( pDemand = &this->m_Demand[0][10 * v5 + 1]; ; pDemand += 10 )
    {
      m_pRoleState = this->m_pRoleState;
      if ( m_pRoleState->m_Role[0].bMagicMastered[5][v6 + 4] )
        break;
LABEL_75:
      v6 += 892;
      roleIdx = ++v5;
      v17 = v6;
      if ( v6 >= 9812 )
        return 0;
    }
    if ( !((CCBRoleState *)m_pRoleState)->IsRoleAlive(v5)
      || (v8 = this->m_pRoleState, v8->m_Role[0].bMagicMastered[6][v6 + 4] == 1) )
    {
LABEL_74:
      v5 = roleIdx;
      goto LABEL_75;
    }
    if ( (unsigned int)v6 < 0x116C
      || ((CCBRoleState *)v8)->GetRoleField(nRoleIndex, 19)
      && (++*(_DWORD *)&g_TempBuffer1024[912],
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
          (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7)
      || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 18)
      && (++*(_DWORD *)&g_TempBuffer1024[912],
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
          (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7) )
    {
      if ( pDemand[5].nSatisfy < 100 )
      {
        this->DemandChecker(nRoleIndex, roleIdx, (int)&pDemand[5]);
        if ( v9 )
          return 1;
      }
    }
    if ( this->m_EnemyDemand[1].nSatisfy < 100
      && this->CastRecoverMagic(nRoleIndex, (int)&this->m_EnemyDemand[1]) )
    {
      return 1;
    }
    v10 = roleIdx;
    if ( roleIdx == nRoleIndex && pDemand->nSatisfy < 100 )
    {
      if ( this->CastNormalAttack(nRoleIndex, roleIdx, (int)pDemand) )
        return 1;
      v10 = roleIdx;
    }
    if ( v6 >= 4460 )
    {
      if ( v6 < 9812 && pDemand->nSatisfy < 100 )
      {
        if ( this->CastNormalAttack(nRoleIndex, v10, (int)pDemand) )
          return 1;
        v10 = roleIdx;
      }
      if ( v6 < 9812 && pDemand[3].nSatisfy < 100 )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)512.0
          && this->CastAttackBigItem(nRoleIndex, v10, (int)&pDemand[3]) )
        {
          return 1;
        }
      }
    }
    if ( this->m_nHandleEnemyWell < 100 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)256.0
        && this->CastAttackMagic(nRoleIndex, (int)&this->m_nHandleEnemyWell) )
      {
        return 1;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleType(nRoleIndex) )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)307.19998 )
        {
          if ( ((AStarPathFinder *)this)->GetHeuristicIdx(nRoleIndex, (int)&this->m_nHandleEnemyWell) )
            return 1;
        }
      }
    }
    v11 = v17;
    if ( v17 < 0 )
      goto LABEL_82;
    if ( v17 >= 4460
      || pDemand[7].nSatisfy >= 100
      || (++*(_DWORD *)&g_TempBuffer1024[912],
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
          (((int)unk_5DFDEC >> 16) & 0x3FF) >= (int)716.79999) )
    {
      v12 = roleIdx;
    }
    else
    {
      v12 = roleIdx;
      if ( this->CastRecoverBigMagic(nRoleIndex, roleIdx, (int)&pDemand[7]) )
        return 1;
      v11 = v17;
    }
    if ( v11 < 0 )
      goto LABEL_82;
    if ( v11 < 4460 && pDemand[8].nSatisfy < 100 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)716.79999 )
      {
        this->DemandChecker(nRoleIndex, v12, (int)&pDemand[8]);
        if ( v13 )
          return 1;
      }
      v11 = v17;
    }
    if ( v11 < 4460 && pDemand[6].nSatisfy < 100 )
    {
      if ( this->CastRecoverBigMagic(nRoleIndex, v12, (int)&pDemand[6]) )
        return 1;
      v11 = v17;
    }
    if ( v11 < 4460 && pDemand[6].nSatisfy < 100 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)256.0
        && this->CastRecoverBigMagic(nRoleIndex, v12, (int)&pDemand[6]) )
      {
        return 1;
      }
      v11 = v17;
    }
    if ( v11 < 4460 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)102.39999 )
      {
        if ( this->CastAttackMagic(nRoleIndex, 0) || this->CastRecoverBigMagic(nRoleIndex, v12, 0) )
          return 1;
        v11 = v17;
      }
    }
    if ( v11 >= 4460 )
    {
LABEL_82:
      if ( !((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19)
        || (++*(_DWORD *)&g_TempBuffer1024[912],
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
            (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 <= 7) )
      {
LABEL_73:
        v6 = v17;
        goto LABEL_74;
      }
      v12 = roleIdx;
    }
    this->DemandChecker(nRoleIndex, v12, 0);
    if ( v14 )
      return 1;
    goto LABEL_73;
  }
  if ( v5 < 11 )
    goto LABEL_10;
  return 0;
}

// 0x004D7EF0
bool CCBAI::HandleEnemyWeak(int nRoleIndex)
{
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // edi
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v8; // ecx
  char v9; // al
  int v10; // edx
  int v11; // edx
  int v12; // edi
  char v13; // al
  char v14; // al
  int v16; // [esp+0x40] [ebp-0xC]
  tagDemand *pDemand; // [esp+0x44] [ebp-0x8]
  int roleIdx; // [esp+0x48] [ebp-0x4]

  v3 = unk_5DFDEC;
  v4 = 0;
  roleIdx = 0;
  while ( 1 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    v3 = 214013 * v3 + 2531011;
    unk_5DFDEC = v3;
    if ( ((v3 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v4 + 4] )
        break;
    }
    v4 += 892;
    v5 = ++roleIdx;
    if ( v4 >= 9812 )
      goto LABEL_7;
  }
  v5 = roleIdx;
LABEL_7:
  if ( v5 == 10 )
  {
    roleIdx = 0;
    v5 = 0;
  }
  else if ( v5 >= 11 )
  {
    return 0;
  }
  v6 = 892 * v5;
  v16 = 892 * v5;
  for ( pDemand = &this->m_Demand[0][10 * v5 + 1]; ; pDemand += 10 )
  {
    m_pRoleState = this->m_pRoleState;
    if ( m_pRoleState->m_Role[0].bMagicMastered[5][v6 + 4] )
      break;
LABEL_76:
    v6 += 892;
    roleIdx = ++v5;
    v16 = v6;
    if ( v6 >= 9812 )
      return 0;
  }
  if ( !((CCBRoleState *)m_pRoleState)->IsRoleAlive(v5)
    || (v8 = this->m_pRoleState, v8->m_Role[0].bMagicMastered[6][v6 + 4] == 1) )
  {
    v5 = roleIdx;
    goto LABEL_76;
  }
  if ( (unsigned int)v6 >= 0x116C
    && (!((CCBRoleState *)v8)->GetRoleField(nRoleIndex, 19)
     || (++*(_DWORD *)&g_TempBuffer1024[912],
         unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
         (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 <= 7)
     || pDemand[5].nSatisfy >= 100)
    || (this->DemandChecker(nRoleIndex, roleIdx, (int)&pDemand[5]), !v9) )
  {
    if ( this->m_EnemyDemand[1].nSatisfy >= 100
      || !this->CastRecoverMagic(nRoleIndex, (int)&this->m_EnemyDemand[1]) )
    {
      v10 = roleIdx;
      if ( roleIdx == nRoleIndex && pDemand->nSatisfy < 100 )
      {
        if ( this->CastNormalAttack(nRoleIndex, roleIdx, (int)pDemand)
          || this->CastRecoverMagic(nRoleIndex, (int)pDemand) )
        {
          return 1;
        }
        v10 = roleIdx;
      }
      if ( v6 < 4460 )
        goto LABEL_81;
      if ( v6 < 9812 && pDemand->nSatisfy < 100 )
      {
        if ( this->CastNormalAttack(nRoleIndex, v10, (int)pDemand) )
          return 1;
        v10 = roleIdx;
      }
      if ( v6 >= 9812
        || pDemand[3].nSatisfy >= 100
        || (++*(_DWORD *)&g_TempBuffer1024[912],
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
            (((int)unk_5DFDEC >> 16) & 0x3FF) >= (int)512.0)
        || !this->CastAttackBigItem(nRoleIndex, v10, (int)&pDemand[3]) )
      {
LABEL_81:
        if ( this->m_nHandleEnemyWell >= 100
          || ((++*(_DWORD *)&g_TempBuffer1024[912],
               unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
               (((int)unk_5DFDEC >> 16) & 0x3FF) >= (int)256.0)
           || !this->CastAttackMagic(nRoleIndex, (int)&this->m_nHandleEnemyWell))
          && (!((CCBRoleState *)this->m_pRoleState)->GetRoleType(nRoleIndex)
           || (++*(_DWORD *)&g_TempBuffer1024[912],
               unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
               (((int)unk_5DFDEC >> 16) & 0x3FF) >= (int)307.19998)
           || !((AStarPathFinder *)this)->GetHeuristicIdx(nRoleIndex, (int)&this->m_nHandleEnemyWell)) )
        {
          v11 = v16;
          if ( v16 < 0 )
            goto LABEL_82;
          if ( v16 >= 4460
            || pDemand[7].nSatisfy >= 100
            || (++*(_DWORD *)&g_TempBuffer1024[912],
                unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
                (((int)unk_5DFDEC >> 16) & 0x3FF) >= (int)716.79999) )
          {
            v12 = roleIdx;
          }
          else
          {
            v12 = roleIdx;
            if ( this->CastRecoverBigMagic(nRoleIndex, roleIdx, (int)&pDemand[7]) )
              return 1;
            v11 = v16;
          }
          if ( v11 < 0 )
            goto LABEL_82;
          if ( v11 < 4460 && pDemand[8].nSatisfy < 100 )
          {
            ++*(_DWORD *)&g_TempBuffer1024[912];
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)716.79999 )
            {
              this->DemandChecker(nRoleIndex, v12, (int)&pDemand[8]);
              if ( v13 )
                return 1;
            }
            v11 = v16;
          }
          if ( v11 < 4460 && pDemand[6].nSatisfy < 100 )
          {
            if ( this->CastRecoverBigMagic(nRoleIndex, v12, (int)&pDemand[6]) )
              return 1;
            v11 = v16;
          }
          if ( v11 < 4460 && pDemand[6].nSatisfy < 100 )
          {
            ++*(_DWORD *)&g_TempBuffer1024[912];
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)256.0
              && this->CastRecoverBigMagic(nRoleIndex, v12, (int)&pDemand[6]) )
            {
              return 1;
            }
            v11 = v16;
          }
          if ( v11 < 4460 )
          {
            ++*(_DWORD *)&g_TempBuffer1024[912];
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)102.39999 )
            {
              if ( this->CastAttackMagic(nRoleIndex, 0) || this->CastRecoverBigMagic(nRoleIndex, v12, 0) )
                return 1;
              v11 = v16;
            }
          }
          if ( v11 < 4460 )
          {
LABEL_71:
            this->DemandChecker(nRoleIndex, v12, 0);
            if ( v14 )
              return 1;
          }
          else
          {
LABEL_82:
            if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
            {
              ++*(_DWORD *)&g_TempBuffer1024[912];
              unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
              if ( (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7 )
              {
                v12 = roleIdx;
                goto LABEL_71;
              }
            }
          }
          v5 = roleIdx;
          v6 = v16;
          goto LABEL_76;
        }
      }
    }
  }
  return 1;
}

// 0x004D8580
void CCBAI::ChooseRandomAction(int nSelfIdx)
{
  int v2; // esi
  int i; // ebx
  int v4; // edx

  v2 = unk_5DFDEC;
  for ( i = 0; i < 512; ++i )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    v2 = 214013 * v2 + 2531011;
    unk_5DFDEC = v2;
    v4 = ((v2 >> 16) & 0x7FFF) % 11;
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][892 * v4 + 4] && v4 != nSelfIdx )
      break;
  }
  if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][892 * v4 + 4] )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * v2 + 2531011;
    switch ( ((int)unk_5DFDEC >> 16) & 7 )
    {
      case 1:
        this->CastRecoverMagic(nSelfIdx, 0);
        break;
      case 2:
        this->CastNormalAttack(nSelfIdx, ((v2 >> 16) & 0x7FFF) % 11, 0);
        break;
      case 4:
        this->CastAttackMagic(nSelfIdx, 0);
        break;
      case 5:
        this->CastRecoverBigMagic(nSelfIdx, ((v2 >> 16) & 0x7FFF) % 11, 0);
        break;
      default:
        this->DemandChecker(nSelfIdx, ((v2 >> 16) & 0x7FFF) % 11, 0);
        break;
    }
  }
}

// 0x004D86D0
bool CCBAI::HandleEnemyChaos(int nRoleIndex)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBStageRole *v4; // eax
  CCBAI *v5; // ecx
  bool result; // al
  int v7; // [esp-0x4] [ebp-0x10]

  m_pRoleState = this->m_pRoleState;
  if ( !m_pRoleState->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4]
    || !((CCBRoleState *)m_pRoleState)->IsRoleAlive(nRoleIndex)
    || !((CCBRoleState *)this->m_pRoleState)->InitUI(nRoleIndex)->nHP )
  {
    return 0;
  }
  v7 = nRoleIndex;
  v4 = this->m_pCBSystem->m_pStage->m_pRole[nRoleIndex];
v4->m_Task[63].vec1.z = *(float *)&v4->m_Task[63].cmd.dwCmdKind;
  if ( *((_BYTE *)&this->m_pRoleState->m_Role[2].nLuck + 892 * nRoleIndex + 1) )
  {
    result = this->HandleFriendAction(nRoleIndex);
    if ( result )
      return result;
    v7 = nRoleIndex;
}
  return ((CCBAI *)v5)->HandleFriendNegative(v7);
}

// 0x004D8760
bool CCBAI::HandleFriendAction(int nRoleIndex)
{
  int v3; // ebx
  int v4; // eax
  CCBRoleState *m_pRoleState; // ecx
  bool v6; // cc
  int v8; // [esp+0x10] [ebp-0x8]
  tagDemand *pDemand; // [esp+0x14] [ebp-0x4]

  v3 = 0;
  v4 = 0;
  v8 = 0;
  for ( pDemand = &this->m_Demand[0][1]; ; pDemand += 10 )
  {
    m_pRoleState = this->m_pRoleState;
    if ( m_pRoleState->m_Role[0].bMagicMastered[5][v4 + 4] )
    {
      if ( ((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        switch ( ((int)unk_5DFDEC >> 16) & 0x3F )
        {
          case 0:
            if ( !this->CastRecoverBigItem(nRoleIndex, v3, 0) )
              goto LABEL_46;
            return 1;
          case 1:
            if ( !this->CastRecoverItem(nRoleIndex, v3, 0) )
              goto LABEL_46;
            return 1;
          case 2:
            if ( !this->CastAttackItem(nRoleIndex, v3, 0) )
              goto LABEL_46;
            return 1;
          case 3:
            if ( !this->CastRecoverMagic(nRoleIndex, 0) )
              goto LABEL_46;
            return 1;
          case 4:
            if ( !this->CastBFAMagic(nRoleIndex, 0) )
              goto LABEL_46;
            return 1;
          case 5:
            if ( !this->CastRecoverBigSkill(nRoleIndex, 0) )
              goto LABEL_46;
            return 1;
          case 6:
            if ( !this->CastNormalAttack(nRoleIndex, v3, 0) )
              goto LABEL_46;
            return 1;
          case 7:
            if ( !this->CastSpecifyMagic(nRoleIndex, v3, 0) )
              goto LABEL_46;
            return 1;
          case 8:
            if ( !this->CastRecoverSkill(nRoleIndex, v3, 0) )
              goto LABEL_46;
            return 1;
          default:
            goto LABEL_46;
        }
      }
      if ( (unsigned int)v8 < 0x116C
        && pDemand[1].nSatisfy < 100
        && (this->CastRecoverBigItem(nRoleIndex, v3, (int)&pDemand[1])
         || this->CastRecoverItem(nRoleIndex, v3, (int)&pDemand[1])
         || this->CastAttackItem(nRoleIndex, v3, (int)&pDemand[1])) )
      {
        break;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v3)
        && LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v3)[1].dwMagicID[2][5]) != 1 )
      {
        if ( this->m_FriendDemand[1].nSatisfy < 100
          && (this->CastRecoverMagic(nRoleIndex, (int)&this->m_FriendDemand[1])
           || this->CastBFAMagic(nRoleIndex, (int)&this->m_FriendDemand[1])
           || this->CastRecoverBigSkill(nRoleIndex, (int)&this->m_FriendDemand[1])) )
        {
          break;
        }
        if ( v8 >= 0 )
        {
          if ( v8 < 4460
            && pDemand->nSatisfy < 50
            && (this->CastNormalAttack(nRoleIndex, v3, (int)pDemand)
             || this->CastSpecifyMagic(nRoleIndex, v3, (int)pDemand)
             || this->CastRecoverSkill(nRoleIndex, v3, (int)pDemand)) )
          {
            break;
          }
          if ( v8 < 4460 && pDemand[3].nSatisfy < 100 )
          {
            ++*(_DWORD *)&g_TempBuffer1024[912];
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)512.0
              && (this->CastAttackBigItem(nRoleIndex, v3, (int)&pDemand[3])
               || this->CastBossPhysicalAttack(nRoleIndex, v3, (int)&pDemand[3])
               || this->CastReviveMagic(nRoleIndex, v3, (int)&pDemand[3])) )
            {
              break;
            }
          }
        }
      }
    }
LABEL_46:
    v4 = v8 + 892;
    ++v3;
    v6 = v8 + 892 < 9812;
    v8 += 892;
    if ( !v6 )
      return 0;
  }
  return 1;
}

// 0x004D8AF0
bool CCBAI::HandleFriendNegative(int nRoleIndex)
{
  int v4; // edi
  int v5; // ebx
  CCBRoleState *m_pRoleState; // ecx
  int v7; // ebx
  char v8; // al
  char v9; // al
  bool result; // al
  int v11; // edi
  CCBRoleState *v12; // ecx
  int v13; // ebx
  CCBRoleState *v14; // ecx
  bool v15; // al
  int v16; // [esp+0x10] [ebp-0x4]
  tagDemand *nRoleIndexa; // [esp+0x18] [ebp+0x4]
  int nRoleIndexb; // [esp+0x18] [ebp+0x4]

  if ( !((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    v4 = 0;
    v5 = 0;
    v16 = 0;
    for ( nRoleIndexa = &this->m_Demand[0][6]; ; nRoleIndexa += 10 )
    {
      m_pRoleState = this->m_pRoleState;
      if ( !m_pRoleState->m_Role[0].bMagicMastered[5][v5 + 4]
        || !((CCBRoleState *)m_pRoleState)->IsRoleAlive(v4)
        || LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v4)[1].dwMagicID[2][5]) )
      {
        goto LABEL_30;
      }
      if ( this->m_nDemandThreadTracer < 100
        && (this->CastAttackMagic(nRoleIndex, (int)&this->m_nDemandThreadTracer)
         || this->CastRandEnemyMagic(nRoleIndex, (int)&this->m_nDemandThreadTracer)
         || this->CastAttackBigSkill(nRoleIndex, (int)&this->m_nDemandThreadTracer)) )
      {
        return 1;
      }
      if ( v16 < 4460 )
      {
        v7 = (int)nRoleIndexa;
      }
      else
      {
        v7 = (int)nRoleIndexa;
        if ( v16 < 9812 && nRoleIndexa->nSatisfy < 100 )
        {
LABEL_17:
          this->DemandChecker(nRoleIndex, v4, v7);
          if ( v8 == 1
            || this->CastRecoverBigMagic(nRoleIndex, v4, v7)
            || this->CastBFAAttackMagic(nRoleIndex, v4, v7)
            || this->CastAttackSkill(nRoleIndex, v4, v7) )
          {
            return 1;
          }
          goto LABEL_21;
        }
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        if ( (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7 )
          goto LABEL_17;
      }
LABEL_21:
      if ( v16 >= 4460 && v16 < 9812
        || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19)
        && (++*(_DWORD *)&g_TempBuffer1024[912],
            unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
            (((int)unk_5DFDEC >> 16) & 0x7FFF) % 10 > 7) )
      {
        this->DemandChecker(nRoleIndex, v4, 0);
        if ( v9 == 1
          || this->CastRecoverBigMagic(nRoleIndex, v4, 0)
          || this->CastBFAAttackMagic(nRoleIndex, v4, 0)
          || this->CastAttackSkill(nRoleIndex, v4, 0) )
        {
          return 1;
        }
      }
      v5 = v16;
LABEL_30:
      v5 += 892;
      ++v4;
      v16 = v5;
      if ( v5 >= 9812 )
        return 0;
    }
  }
  v11 = unk_5DFDEC;
  nRoleIndexb = 0;
  while ( 1 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    v11 = 214013 * v11 + 2531011;
    unk_5DFDEC = v11;
    v12 = this->m_pRoleState;
    v13 = ((v11 >> 16) & 0x7FFF) % 11;
    if ( v12->m_Role[0].bMagicMastered[5][892 * v13 + 4] )
      break;
LABEL_37:
    if ( ++nRoleIndexb >= 1024 )
      goto LABEL_38;
  }
  if ( !LOBYTE(((CCBRoleState *)v12)->InitUI(((v11 >> 16) & 0x7FFF) % 11)[1].dwMagicID[2][5]) || v13 == nRoleIndex )
  {
    v11 = unk_5DFDEC;
    goto LABEL_37;
  }
LABEL_38:
  v14 = this->m_pRoleState;
  if ( v14->m_Role[0].bMagicMastered[5][892 * v13 + 4] && !LOBYTE(((CCBRoleState *)v14)->InitUI(v13)[1].dwMagicID[2][5]) )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    switch ( (((int)unk_5DFDEC >> 16) & 0x7FFF) % 11 )
    {
      case 0:
        return this->CastAttackMagic(nRoleIndex, 0);
      case 1:
        return this->CastRandEnemyMagic(nRoleIndex, 0);
      case 2:
        result = this->CastAttackBigSkill(nRoleIndex, 0);
        goto LABEL_49;
      case 3:
      case 10:
        this->DemandChecker(nRoleIndex, v13, 0);
        return v15;
      case 4:
      case 7:
        result = this->CastRecoverBigMagic(nRoleIndex, v13, 0);
        if ( !result )
          return 0;
        return result;
      case 5:
      case 8:
        result = this->CastBFAAttackMagic(nRoleIndex, v13, 0);
        if ( !result )
          return 0;
        return result;
      case 6:
      case 9:
        result = this->CastAttackSkill(nRoleIndex, v13, 0);
LABEL_49:
        if ( result )
          return result;
        return 0;
      default:
        return 0;
    }
  }
  return 0;
}

// 0x004D8F20
bool CCBAI::HandleFriendAffirmative(int nRoleIndex, char pData)
{
  int v4; // ebx
  int v5; // edi
  CCBRoleState *m_pRoleState; // ecx
  int v7; // eax
  CCBRoleState *v8; // ecx
  double v9; // st7
  int v11; // ebx
  int v12; // edi
  CCBRoleState *v13; // ecx
  bool v15; // al
  CCBSystem *m_pCBSystem; // ecx
  CCBAI *v17; // edx
  _DWORD v18[11]; // [esp+0xC] [ebp-0x44] BYREF
  CCBAI *v19; // [esp+0x38] [ebp-0x18]
  int v20; // [esp+0x3C] [ebp-0x14]
  int v21; // [esp+0x40] [ebp-0x10]
  float v22; // [esp+0x44] [ebp-0xC]
  int v23; // [esp+0x48] [ebp-0x8]
  int nVal; // [esp+0x4C] [ebp-0x4]
  bool nRoleIndex_3; // [esp+0x5B] [ebp+0xB]

  v4 = 0;
v22 = 1.1;
  nVal = -1;
  v23 = 0;
  v5 = 0;
  do
  {
    if ( v4 >= 4460 )
    {
      m_pRoleState = this->m_pRoleState;
      if ( m_pRoleState->m_Role[0].bMagicMastered[5][v4 + 4] )
      {
        if ( ((CCBRoleState *)m_pRoleState)->IsRoleAlive(v5) )
        {
          ++v23;
          v7 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(v5, 0);
          v8 = this->m_pRoleState;
          *(float *)&v20 = (float)v7;
          v21 = ((CCBRoleState *)v8)->SetRoleField(v5, 1);
          v9 = *(float *)&v20 / (double)v21;
          if ( v9 < v22 )
          {
            v22 = v9;
            nVal = v5;
          }
        }
      }
    }
    v4 += 892;
    ++v5;
  }
  while ( v4 < 9812 );
  if ( v23 <= 0 )
    return 0;
  if ( nVal == -1 )
  {
    v11 = 0;
    v12 = 0;
    while ( 1 )
    {
      if ( v12 >= 4460 )
      {
        v13 = this->m_pRoleState;
        if ( v13->m_Role[0].bMagicMastered[5][v12 + 4] )
        {
          if ( ((CCBRoleState *)v13)->IsRoleAlive(v11) )
          {
            v20 = 100 / v23;
            if ( 100 / v23 > 0 )
            {
              *(float *)&v20 = (double)v20 * 10.24;
              v21 = (int)*(float *)&v20;
              ++*(_DWORD *)&g_TempBuffer1024[912];
              unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
              if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < v21 )
                break;
            }
          }
        }
      }
      v12 += 892;
      ++v11;
      if ( v12 >= 9812 )
        return 0;
    }
    nVal = v11;
    if ( v11 != -1 )
      goto LABEL_21;
    return 0;
  }
  else
  {
LABEL_21:
    LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(nRoleIndex)[1].dwMagicID[0][5]) = 1;
    this->DemandChecker(nRoleIndex, nVal, 0);
    nRoleIndex_3 = v15;
    LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(nRoleIndex)[1].dwMagicID[0][5]) = 0;
    if ( pData )
    {
      memset(v18, 0, sizeof(v18));
      LOWORD(v18[4]) = 0;
      v18[3] = nVal;
      m_pCBSystem = this->m_pCBSystem;
      v17 = v19;
      LOBYTE(v18[10]) = 1;
      v18[0] = 259;
      v18[2] = nRoleIndex;
      qmemcpy(&m_pCBSystem->m_Player[nRoleIndex], v18, 0x2Cu);
      v17->m_bNewRole[nRoleIndex] = 0;
    }
    return nRoleIndex_3;
  }
}

// 0x004D9130
bool CCBAI::HandlePlayerNormalAttack(int nRoleIndex, int bPlayerCmd)
{
  int ( *v4)(int, int); // eax
  bool result; // al
  char v6; // al
  char v7; // al
  int v8; // eax
  char v9; // al
  int v10; // eax
  char v11; // al
  int v12; // eax

  switch ( *(_DWORD *)bPlayerCmd )
  {
    case 0x103:
      result = 1;
      goto LABEL_5;
    case 0x104:
    case 0x105:
    case 0x106:
      result = ((CCBRoleState *)this->m_pRoleState)->GetRoleAI((void *)bPlayerCmd);
      if ( !result )
        goto LABEL_11;
LABEL_5:
      switch ( *(_DWORD *)bPlayerCmd )
      {
        case 0x103:
          ((CCBRoleState *)this->m_pRoleState)->InitRoleSpecEquipAttrib(bPlayerCmd);
          if ( v6 || this->m_bNewRole[nRoleIndex] )
          {
            *(_DWORD *)(bPlayerCmd + 29) = 0;
            *(_DWORD *)(bPlayerCmd + 33) = 0;
            *(_WORD *)(bPlayerCmd + 37) = 0;
            *(_BYTE *)(bPlayerCmd + 39) = 0;
            *(_DWORD *)(bPlayerCmd + 12) = ((CCBRoleState *)this->m_pRoleState)->CalcMPCost(2);
            *(_BYTE *)(bPlayerCmd + 17) = 0;
            ((CCBRoleState *)this->m_pRoleState)->CalcHealAmount(bPlayerCmd);
          }
          v4 = (int ( *)(int, int))CCBSystem::IsRoleWaitForFlee;
          goto LABEL_33;
        case 0x104:
          ((CCBRoleState *)this->m_pRoleState)->InitRoleSpecEquipAttrib(bPlayerCmd);
          if ( v9 || this->m_bNewRole[nRoleIndex] )
          {
            *(_DWORD *)(bPlayerCmd + 29) = 0;
            *(_DWORD *)(bPlayerCmd + 33) = 0;
            *(_WORD *)(bPlayerCmd + 37) = 0;
            *(_BYTE *)(bPlayerCmd + 39) = 0;
            if ( ((PAL_GDB *)this->m_pRoleState)->IsRoleAlive2(*(_DWORD *)(bPlayerCmd + 4)) )
              v10 = ((CCBRoleState *)this->m_pRoleState)->CalcMPCost(2);
            else
              v10 = ((CCBRoleState *)this->m_pRoleState)->CalcMPCost(1);
            *(_DWORD *)(bPlayerCmd + 12) = v10;
            *(_BYTE *)(bPlayerCmd + 17) = 0;
            ((CCBRoleState *)this->m_pRoleState)->GetRoleNum((int *)bPlayerCmd);
          }
          v4 = (int ( *)(int, int))CCBSystem::GetThreadIndex;
          goto LABEL_33;
        case 0x105:
          ((CCBRoleState *)this->m_pRoleState)->InitRoleSpecEquipAttrib(bPlayerCmd);
          if ( v7 || this->m_bNewRole[nRoleIndex] )
          {
            *(_DWORD *)(bPlayerCmd + 29) = 0;
            *(_DWORD *)(bPlayerCmd + 33) = 0;
            *(_WORD *)(bPlayerCmd + 37) = 0;
            *(_BYTE *)(bPlayerCmd + 39) = 0;
            if ( ((PAL_GDB *)this->m_pRoleState)->IsRoleAlive2(*(_DWORD *)(bPlayerCmd + 4)) )
              v8 = ((CCBRoleState *)this->m_pRoleState)->CalcMPCost(2);
            else
              v8 = ((CCBRoleState *)this->m_pRoleState)->CalcMPCost(1);
            *(_DWORD *)(bPlayerCmd + 12) = v8;
            *(_BYTE *)(bPlayerCmd + 17) = 0;
            ((CCBRoleState *)this->m_pRoleState)->GetRoleNum((int *)bPlayerCmd);
          }
          v4 = (int ( *)(int, int))CCBSystem::GetSameThreadNum;
          goto LABEL_33;
        case 0x106:
          ((CCBRoleState *)this->m_pRoleState)->InitRoleSpecEquipAttrib(bPlayerCmd);
          if ( v11 || this->m_bNewRole[nRoleIndex] )
          {
            *(_DWORD *)(bPlayerCmd + 29) = 0;
            *(_DWORD *)(bPlayerCmd + 33) = 0;
            *(_WORD *)(bPlayerCmd + 37) = 0;
            *(_BYTE *)(bPlayerCmd + 39) = 0;
            if ( ((PAL_GDB *)this->m_pRoleState)->IsSkillEmpty(*(_DWORD *)(bPlayerCmd + 4)) )
              v12 = ((CCBRoleState *)this->m_pRoleState)->CalcMPCost(2);
            else
              v12 = ((CCBRoleState *)this->m_pRoleState)->CalcMPCost(1);
            *(_DWORD *)(bPlayerCmd + 12) = v12;
            *(_BYTE *)(bPlayerCmd + 17) = 0;
            ((CCBRoleState *)this->m_pRoleState)->GetRoleNum((int *)bPlayerCmd);
          }
          v4 = (int ( *)(int, int))CCBSystem::PassCmdToThread;
          goto LABEL_33;
        default:
          return result;
      }
    case 0x109:
      v4 = (int ( *)(int, int))CCBSystem::PassCmdViaThread;
      goto LABEL_33;
    case 0x10B:
      v4 = (int ( *)(int, int))CCBSystem::PassCmdToThread;
LABEL_33:
      ((CCBSystem *)this->m_pCBSystem)->CreateObj(v4, 0, 0, 0, (const void *)bPlayerCmd);
      result = 1;
      break;
    default:
LABEL_11:
      result = this->HandleFriendAffirmative(nRoleIndex, 0);
      break;
  }
  return result;
}

// 0x004D9360
void * CCBAI::RepeatPlayerLastOperation()
{
  *(_DWORD *)this->m_bNewRole = byte_1010101;
  *(_DWORD *)&this->m_bNewRole[4] = byte_1010101;
  *(_WORD *)&this->m_bNewRole[8] = (unsigned __int16)byte_1010101;
  this->m_bNewRole[10] = (unsigned __int8)byte_1010101;
  return (void*)byte_1010101;
}

// 0x004D9380
int * CCBAI::SetNewRole()
{
  tagDemand *v1; // eax
  int v2; // esi
  int v3; // edx
  int *result; // eax
  int v5; // ecx

  v1 = this->m_Demand[0];
  v2 = 11;
  do
  {
    v3 = 10;
    do
    {
      v1->nSatisfy = 100;
      ++v1;
      --v3;
    }
    while ( v3 );
    --v2;
  }
  while ( v2 );
  result = &this->m_FriendDemand[0].nSatisfy;
  v5 = 10;
  do
  {
    *(result - 40) = 100;
    *result = 100;
    result += 4;
    --v5;
  }
  while ( v5 );
  return result;
}

// 0x004D93D0
void CCBAI::FillAllDemandSatisfy()
{
  _BYTE *p_bHandle; // esi
  int v3; // ebp
  int i; // edi
  _BYTE *v5; // esi
  int v6; // ebp
  int v7; // edi
  int v8; // [esp+0x10] [ebp-0x8]
  _BYTE *v9; // [esp+0x14] [ebp-0x4]

  p_bHandle = &this->m_Demand[0][1].bHandle;
  v8 = 0;
  v3 = 99;
  v9 = &this->m_Demand[0][1].bHandle;
  do
  {
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v8 + 4] )
    {
      for ( i = 1; i < 10; ++i )
      {
        if ( *((_DWORD *)p_bHandle - 1) )
        {
          if ( (unsigned __int8)((CCBResultWindow *)this->m_pCBSystem)->FindChildByID(*((_DWORD *)p_bHandle - 1)) )
          {
            *p_bHandle = 1;
            *(_DWORD *)&this->m_bNewRole[16 * i + 16 * v3] = 100;
          }
          else
          {
            *((_DWORD *)p_bHandle - 1) = 0;
            *p_bHandle = 0;
          }
        }
        p_bHandle += 16;
      }
    }
    v3 += 10;
    v8 += 892;
    p_bHandle = v9 + 160;
    v9 += 160;
  }
  while ( v3 < 209 );
  v5 = &this->m_EnemyDemand[1].bHandle;
  v6 = 9;
  do
  {
    v7 = *((_DWORD *)v5 + 39);
    if ( *((_DWORD *)v5 - 1) )
    {
      if ( (unsigned __int8)((CCBResultWindow *)this->m_pCBSystem)->FindChildByID(*((_DWORD *)v5 - 1)) )
      {
        *v5 = 1;
        *((_DWORD *)v5 - 2) = 100;
      }
      else
      {
        *((_DWORD *)v5 - 1) = 0;
        *v5 = 0;
      }
    }
    if ( v7 )
    {
      if ( (unsigned __int8)((CCBResultWindow *)this->m_pCBSystem)->FindChildByID(v7) )
      {
        v5[160] = 1;
        *((_DWORD *)v5 + 38) = 100;
      }
      else
      {
        *((_DWORD *)v5 + 39) = 0;
        v5[160] = 0;
      }
    }
    v5 += 16;
    --v6;
  }
  while ( v6 );
}

// 0x004D94F0
void CCBAI::DemandThreadTracer()
{
  int v2; // edi
  int v3; // ebp
  tagDemand *v4; // esi
  CCBRoleState *m_pRoleState; // ecx

  v2 = 0;
  v3 = 0;
  v4 = &this->m_Demand[0][2];
  do
  {
    m_pRoleState = this->m_pRoleState;
    if ( m_pRoleState->m_Role[0].bMagicMastered[5][v3 + 4] )
    {
      if ( ((CCBRoleState *)m_pRoleState)->IsRoleAlive(v2) )
      {
        v4->nSatisfy = 100;
      }
      else if ( !v4->bHandle )
      {
        v4->nSatisfy = 0;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(v2) < 3 )
      {
        v4[-1].nSatisfy = 100;
        v4[3].nSatisfy = 80;
      }
      else
      {
        if ( !v4[-1].bHandle )
          v4[-1].nSatisfy = 40;
        if ( !v4[3].bHandle )
          v4[3].nSatisfy = 40;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(v2) == 4 )
      {
        if ( !v4[-1].bHandle )
          v4[-1].nSatisfy = 10;
        if ( !v4[3].bHandle )
          v4[3].nSatisfy = 10;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleForce(v2) )
      {
        if ( !v4[2].bHandle )
        {
          v4[2].eSpecState = (ECBRoleSpecState)((CCBRoleState *)this->m_pRoleState)->FindFirstEnemySlot(v2);
          v4[2].nSatisfy = 50;
        }
      }
      else
      {
        v4[2].nSatisfy = 100;
      }
    }
    v3 += 892;
    ++v2;
    v4 += 10;
  }
  while ( v3 < 9812 );
  ((CCBRoleState *)this->m_pRoleState)->GetRoleMP(2);
  if ( !this->m_EnemyDemand[1].bHandle )
    this->m_EnemyDemand[1].nSatisfy = 110;
  if ( !this->m_bDemandThreadTracer )
    this->m_nDemandThreadTracer = 0;
  ((CCBRoleState *)this->m_pRoleState)->GetRoleMP(1);
  if ( !this->m_FriendDemand[1].bHandle )
    this->m_FriendDemand[1].nSatisfy = 110;
  if ( !this->_todo_E08 )
    this->m_nHandleEnemyWell = 100;
}

// 0x004D9740
void CCBAI::DemandChecker(unsigned int dwVal, int nVal, int nVal2)
{
  unsigned int v5; // eax
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v7; // ecx
  unsigned int v8; // edi
  CCBRoleState *v9; // ecx
  int Obj; // eax
  int roleIdx[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(roleIdx, 0, sizeof(roleIdx));
  v5 = dwVal;
  if ( nVal != dwVal )
  {
    m_pRoleState = this->m_pRoleState;
    if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * dwVal + 1) )
    {
      if ( !((CCBRoleState *)m_pRoleState)->GetRoleField(dwVal, 18)
        && !((CCBRoleState *)this->m_pRoleState)->GetRoleField(dwVal, 19) )
      {
        return;
      }
      v5 = dwVal;
    }
    v7 = this->m_pRoleState;
    if ( v7->m_Role[0].bMagicMastered[5][892 * dwVal + 4]
      && v7->m_Role[0].bMagicMastered[5][892 * nVal + 4]
      && ((CCBRoleState *)v7)->IsRoleAlive(v5)
      && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nVal)
      && ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nVal, 23) != 1 )
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nVal, 21) == 1
        && ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nVal, 20) == 1 )
      {
        v8 = dwVal;
        if ( dwVal <= 4 )
          return;
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)716.79999 )
          return;
      }
      else
      {
        v8 = dwVal;
      }
      if ( ((CCBStageRole *)this->m_pCBSystem->m_pStage->m_pRole[nVal])->ForceEndTaskByPFN()
        && ((CCBRoleState *)this->m_pRoleState)->CalSneakAttack(v8, nVal) )
      {
        v9 = this->m_pRoleState;
        LOBYTE(roleIdx[10]) = 1;
        roleIdx[0] = 259;
        roleIdx[2] = v8;
        roleIdx[3] = nVal;
        LOWORD(roleIdx[4]) = 0;
        ((CCBRoleState *)v9)->CalcHealAmount((int)roleIdx);
        Obj = ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::IsRoleWaitForFlee, 0, 0, 0, roleIdx);
        if ( nVal2 )
          *(_DWORD *)(nVal2 + 4) = Obj;
      }
    }
  }
}

// 0x004D9920
bool CCBAI::CastNormalAttack(int nRoleIndex, int nDestRole, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0x10] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nDestRole + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nDestRole) )
    return 0;
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 1);
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 0);
  v7 = ((CCBRoleState *)this->m_pRoleState)->ProcessAttackResult(nRoleIndex);
  if ( !v7 )
    return 0;
  pData[1] = v7;
  pData[3] = nDestRole;
  LOBYTE(pData[10]) = 1;
  LOWORD(pData[4]) = 0;
  m_pCBSystem = this->m_pCBSystem;
  pData[0] = 261;
  pData[2] = nRoleIndex;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pData);
  if ( pDemand )
    *(_DWORD *)(pDemand + 4) = Obj;
  return 1;
}

// 0x004D9A70
bool CCBAI::CastRecoverMagic(int nRoleIndex, int nDestRole)
{
  CCBRoleState *m_pRoleState; // ecx
  bool result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int v8; // eax
  CCBRoleState *v9; // ecx
  int Obj; // eax
  int pnVal[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pnVal, 0, sizeof(pnVal));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18)
    || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
  {
    return 0;
  }
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  result = ((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex);
  if ( result )
  {
    RoleHP = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(nRoleIndex);
    ((CCBRoleState *)this->m_pRoleState)->CalcMagicDefense(RoleHP);
    v8 = ((CCBRoleState *)this->m_pRoleState)->ProcessAttackResult(nRoleIndex);
    if ( v8 )
    {
      v9 = this->m_pRoleState;
      pnVal[1] = v8;
      LOBYTE(pnVal[10]) = 1;
      LOWORD(pnVal[4]) = 0;
      pnVal[0] = 261;
      pnVal[2] = nRoleIndex;
      pnVal[3] = -1;
      ((CCBRoleState *)v9)->GetRoleNum(pnVal);
      Obj = ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pnVal);
      if ( nDestRole )
        *(_DWORD *)(nDestRole + 4) = Obj;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004D9BA0
bool CCBAI::CastRecoverBigMagic(int nRoleIndex, int pDemand, int nVal)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * pDemand + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(pDemand) )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->SetRoleField(pDemand, 0) <= 0 )
    return 0;
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(pDemand, 0);
  v7 = ((CCBRoleState *)this->m_pRoleState)->ProcessMagicResult(nRoleIndex);
  if ( !v7 )
    return 0;
  v8 = ((CCBRoleState *)this->m_pRoleState)->RandomizeSpecialSkill(v7);
  pData[2] = nRoleIndex;
  pData[1] = v8;
  pData[3] = pDemand;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 261;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pData);
  if ( nVal )
    *(_DWORD *)(nVal + 4) = Obj;
  return 1;
}

// 0x004D9D00
bool CCBAI::CastAttackMagic(int nRoleIndex, int nDestRole)
{
  CCBRoleState *m_pRoleState; // ecx
  int RoleHP; // eax
  int IsForce1; // eax
  int v7; // edx
  CCBRoleState *v8; // ecx
  int pnVal[11]; // [esp+0x10] [ebp-0x2C] BYREF

  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(nRoleIndex);
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nRoleIndex) )
    return 0;
  RoleHP = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(nRoleIndex);
  IsForce1 = ((CCBRoleState *)this->m_pRoleState)->IsForce1(RoleHP);
  if ( !((CCBRoleState *)this->m_pRoleState)->CalcMagicAttack(IsForce1) )
    return 0;
  v7 = ((CCBRoleState *)this->m_pRoleState)->ProcessMagicResult(nRoleIndex);
  if ( !v7 )
    return 0;
  memset(pnVal, 0, sizeof(pnVal));
  LOBYTE(pnVal[10]) = 1;
  v8 = this->m_pRoleState;
  LOWORD(pnVal[4]) = 0;
  pnVal[0] = 261;
  pnVal[1] = v7;
  pnVal[2] = nRoleIndex;
  pnVal[3] = -1;
  ((CCBRoleState *)v8)->GetRoleNum(pnVal);
  ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pnVal);
  return 1;
}

// 0x004D9E20
bool CCBAI::CastAttackBigMagic(int nRoleIndex, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v5; // ecx
  int v6; // eax
  CCBSystem *m_pCBSystem; // ecx
  _DWORD pData[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v5 = this->m_pRoleState;
  if ( !v5->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v5->m_Role[0].bMagicMastered[5][892 * pDemand + 4] )
    return 0;
  if ( !((CCBRoleState *)v5)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(pDemand) )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->SetRoleField(pDemand, 0) <= 0 )
    return 0;
  v6 = ((CCBRoleState *)this->m_pRoleState)->AISelectItem(nRoleIndex, 0);
  if ( !v6 )
    return 0;
  pData[2] = nRoleIndex;
  pData[1] = v6;
  pData[3] = pDemand;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 261;
  ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pData);
  return 1;
}

// 0x004D9F50
bool CCBAI::CastSpecifyMagic(int nRoleIndex, int nDestRole, int dwID)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0x10] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nDestRole + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nDestRole) )
    return 0;
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 1);
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 0);
  v7 = ((CCBRoleState *)this->m_pRoleState)->CalcPhysicalDamage(nRoleIndex);
  if ( !v7 )
    return 0;
  pData[1] = v7;
  pData[3] = nDestRole;
  LOBYTE(pData[10]) = 1;
  LOWORD(pData[4]) = 0;
  m_pCBSystem = this->m_pCBSystem;
  pData[0] = 260;
  pData[2] = nRoleIndex;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, pData);
  if ( dwID )
    *(_DWORD *)(dwID + 4) = Obj;
  return 1;
}

// 0x004DA0A0
bool CCBAI::CastBFAMagic(int nRoleIndex, int nDestRole)
{
  CCBRoleState *m_pRoleState; // ecx
  bool result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int v8; // eax
  CCBRoleState *v9; // ecx
  int Obj; // eax
  int pnVal[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pnVal, 0, sizeof(pnVal));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 3)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18)
    || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
  {
    return 0;
  }
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  result = ((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex);
  if ( result )
  {
    RoleHP = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(nRoleIndex);
    ((CCBRoleState *)this->m_pRoleState)->CalcMagicDefense(RoleHP);
    v8 = ((CCBRoleState *)this->m_pRoleState)->CalcPhysicalDamage(nRoleIndex);
    if ( v8 )
    {
      v9 = this->m_pRoleState;
      pnVal[1] = v8;
      LOBYTE(pnVal[10]) = 1;
      LOWORD(pnVal[4]) = 0;
      pnVal[0] = 260;
      pnVal[2] = nRoleIndex;
      pnVal[3] = -1;
      ((CCBRoleState *)v9)->GetRoleNum(pnVal);
      Obj = ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, pnVal);
      if ( nDestRole )
        *(_DWORD *)(nDestRole + 4) = Obj;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004DA1D0
bool CCBAI::CastBFAAttackMagic(int nRoleIndex, int pDemand, int nVal)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 3)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * pDemand + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(pDemand) )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->SetRoleField(pDemand, 0) <= 0 )
    return 0;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  v7 = ((CCBRoleState *)this->m_pRoleState)->CalcMagicDamage(nRoleIndex);
  if ( !v7 )
    return 0;
  pData[2] = nRoleIndex;
  pData[1] = v7;
  pData[3] = pDemand;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 260;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, pData);
  if ( nVal )
    *(_DWORD *)(nVal + 4) = Obj;
  return 1;
}

// 0x004DA350
bool CCBAI::CastRandEnemyMagic(int nRoleIndex, int nDestRole)
{
  CCBRoleState *m_pRoleState; // ecx
  bool result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int IsForce1; // ebp
  int v9; // eax
  CCBRoleState *v10; // ecx
  int Obj; // eax
  int pnVal[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pnVal, 0, sizeof(pnVal));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 3)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18)
    || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
  {
    return 0;
  }
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  result = ((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex);
  if ( result )
  {
    RoleHP = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(nRoleIndex);
    IsForce1 = ((CCBRoleState *)this->m_pRoleState)->IsForce1(RoleHP);
    if ( ((CCBRoleState *)this->m_pRoleState)->CalcMPRegen(IsForce1) > 0 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      ((CCBRoleState *)this->m_pRoleState)->CalcMPRegen(IsForce1);
      v9 = ((CCBRoleState *)this->m_pRoleState)->CalcMagicDamage(nRoleIndex);
      if ( v9 )
      {
        v10 = this->m_pRoleState;
        LOBYTE(pnVal[10]) = 1;
        LOWORD(pnVal[4]) = 0;
        pnVal[0] = 260;
        pnVal[1] = v9;
        pnVal[2] = nRoleIndex;
        pnVal[3] = -1;
        ((CCBRoleState *)v10)->GetRoleNum(pnVal);
        Obj = ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, pnVal);
        if ( nDestRole )
          *(_DWORD *)(nDestRole + 4) = Obj;
        return 1;
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

// 0x004DA4F0
bool CCBAI::CastRecoverSkill(int nRoleIndex, int nDestRole, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0x10] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nLuck + 892 * nRoleIndex)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nDestRole + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nDestRole) )
    return 0;
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 1);
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 0);
  v7 = ((CCBRoleState *)this->m_pRoleState)->ProcessSkillEffect(nRoleIndex);
  if ( !v7 )
    return 0;
  pData[1] = v7;
  pData[3] = nDestRole;
  LOBYTE(pData[10]) = 1;
  LOWORD(pData[4]) = 0;
  m_pCBSystem = this->m_pCBSystem;
  pData[0] = 262;
  pData[2] = nRoleIndex;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, pData);
  if ( pDemand )
    *(_DWORD *)(pDemand + 4) = Obj;
  return 1;
}

// 0x004DA640
bool CCBAI::CastRecoverBigSkill(int nRoleIndex, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  bool result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int v8; // eax
  CCBRoleState *v9; // ecx
  int Obj; // eax
  int pnVal[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pnVal, 0, sizeof(pnVal));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nLuck + 892 * nRoleIndex)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18)
    || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
  {
    return 0;
  }
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  result = ((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex);
  if ( result )
  {
    RoleHP = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(nRoleIndex);
    ((CCBRoleState *)this->m_pRoleState)->CalcMagicDefense(RoleHP);
    v8 = ((CCBRoleState *)this->m_pRoleState)->ProcessSkillEffect(nRoleIndex);
    if ( v8 )
    {
      v9 = this->m_pRoleState;
      pnVal[1] = v8;
      LOBYTE(pnVal[10]) = 1;
      LOWORD(pnVal[4]) = 0;
      pnVal[0] = 262;
      pnVal[2] = nRoleIndex;
      pnVal[3] = -1;
      ((CCBRoleState *)v9)->GetRoleNum(pnVal);
      Obj = ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, pnVal);
      if ( pDemand )
        *(_DWORD *)(pDemand + 4) = Obj;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004DA770
bool CCBAI::CastAttackSkill(int nRoleIndex, int nDestRole, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nLuck + 892 * nRoleIndex)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nDestRole + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nDestRole) )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 0) <= 0 )
    return 0;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nDestRole, 0);
  v7 = ((CCBRoleState *)this->m_pRoleState)->ProcessItemEffect(nRoleIndex);
  if ( !v7 )
    return 0;
  pData[2] = nRoleIndex;
  pData[1] = v7;
  pData[3] = nDestRole;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 262;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, pData);
  if ( pDemand )
    *(_DWORD *)(pDemand + 4) = Obj;
  return 1;
}

// 0x004DA900
bool CCBAI::CastAttackBigSkill(int nRoleIndex, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  bool result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int IsForce1; // eax
  int v9; // eax
  CCBRoleState *v10; // ecx
  int Obj; // eax
  int pnVal[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pnVal, 0, sizeof(pnVal));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nLuck + 892 * nRoleIndex)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18)
    || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
  {
    return 0;
  }
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  result = ((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex);
  if ( result )
  {
    RoleHP = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(nRoleIndex);
    IsForce1 = ((CCBRoleState *)this->m_pRoleState)->IsForce1(RoleHP);
    ((CCBRoleState *)this->m_pRoleState)->CalcMagicAttack(IsForce1);
    v9 = ((CCBRoleState *)this->m_pRoleState)->ProcessItemEffect(nRoleIndex);
    if ( v9 )
    {
      v10 = this->m_pRoleState;
      pnVal[1] = v9;
      LOBYTE(pnVal[10]) = 1;
      LOWORD(pnVal[4]) = 0;
      pnVal[0] = 262;
      pnVal[2] = nRoleIndex;
      pnVal[3] = -1;
      ((CCBRoleState *)v10)->GetRoleNum(pnVal);
      Obj = ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, pnVal);
      if ( pDemand )
        *(_DWORD *)(pDemand + 4) = Obj;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004DAA40
bool CCBAI::CastRecoverItem(int nRoleIndex, int nDestRole, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nDestRole + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nDestRole) == 1 )
    return 0;
  v7 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nRoleIndex, 1);
  v8 = ((CCBRoleState *)this->m_pRoleState)->AISelectMagic(nRoleIndex, 0, v7);
  if ( !v8 )
    return 0;
  pData[3] = nDestRole;
  pData[1] = v8;
  pData[2] = nRoleIndex;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 261;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pData);
  if ( pDemand )
    *(_DWORD *)(pDemand + 4) = Obj;
  return 1;
}

// 0x004DAB70
bool CCBAI::CastRecoverBigItem(int nRoleIndex, int pDemand, int nVal)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 3)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * pDemand + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(pDemand) == 1 )
    return 0;
  v7 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nRoleIndex, 1);
  v8 = ((CCBRoleState *)this->m_pRoleState)->AISelectHealItem(nRoleIndex, 0, v7);
  if ( !v8 )
    return 0;
  pData[3] = pDemand;
  pData[1] = v8;
  pData[2] = nRoleIndex;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 260;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, pData);
  if ( nVal )
    *(_DWORD *)(nVal + 4) = Obj;
  return 1;
}

// 0x004DACA0
bool CCBAI::CastAttackItem(int nRoleIndex, int nDestRole, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nLuck + 892 * nRoleIndex)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nDestRole + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nDestRole) == 1 )
    return 0;
  v7 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(nRoleIndex, 1);
  v8 = ((CCBRoleState *)this->m_pRoleState)->AISelectTarget(nRoleIndex, 0, v7);
  if ( !v8 )
    return 0;
  pData[3] = nDestRole;
  pData[1] = v8;
  pData[2] = nRoleIndex;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 262;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, pData);
  if ( pDemand )
    *(_DWORD *)(pDemand + 4) = Obj;
  return 1;
}

// 0x004DADD0
bool CCBAI::CastAttackBigItem(int nRoleIndex, int pDemand, int nVal)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0x10] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 2)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * pDemand + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(pDemand) )
    return 0;
  v7 = ((CCBRoleState *)this->m_pRoleState)->AISelectSkill(nRoleIndex, *(_DWORD *)(nVal + 12), 0);
  if ( !v7 )
    return 0;
  pData[2] = nRoleIndex;
  pData[1] = v7;
  pData[3] = pDemand;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 261;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pData);
  if ( nVal )
    *(_DWORD *)(nVal + 4) = Obj;
  return 1;
}

// 0x004DAF00
bool CCBAI::CastBossPhysicalAttack(int nRoleIndex, int pDemand, int nVal)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0x10] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nSpeed + 892 * nRoleIndex + 3)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * pDemand + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(pDemand) )
    return 0;
  v7 = ((CCBRoleState *)this->m_pRoleState)->AISelectItemForSkill(nRoleIndex, *(_DWORD *)(nVal + 12), 0);
  if ( !v7 )
    return 0;
  pData[2] = nRoleIndex;
  pData[1] = v7;
  pData[3] = pDemand;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 260;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, pData);
  if ( nVal )
    *(_DWORD *)(nVal + 4) = Obj;
  return 1;
}

// 0x004DB030
bool CCBAI::CastReviveMagic(int nRoleIndex, int nDestRole, int pDemand)
{
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *m_pCBSystem; // ecx
  int Obj; // eax
  _DWORD pData[11]; // [esp+0x10] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  m_pRoleState = this->m_pRoleState;
  if ( !*((_BYTE *)&m_pRoleState->m_Role[2].nLuck + 892 * nRoleIndex)
    && !((CCBRoleState *)m_pRoleState)->GetRoleField(nRoleIndex, 18) )
  {
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nRoleIndex, 19) )
    return 0;
  v6 = this->m_pRoleState;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nRoleIndex + 4] )
    return 0;
  if ( !v6->m_Role[0].bMagicMastered[5][892 * nDestRole + 4] )
    return 0;
  if ( !((CCBRoleState *)v6)->IsRoleAlive(nRoleIndex) )
    return 0;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(nDestRole) )
    return 0;
  v7 = ((CCBRoleState *)this->m_pRoleState)->AISelectSkillTarget(nRoleIndex, *(_DWORD *)(pDemand + 12), 0);
  if ( !v7 )
    return 0;
  pData[2] = nRoleIndex;
  pData[1] = v7;
  pData[3] = nDestRole;
  LOBYTE(pData[10]) = 1;
  m_pCBSystem = this->m_pCBSystem;
  LOWORD(pData[4]) = 0;
  pData[0] = 262;
  Obj = ((CCBSystem *)m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, pData);
  if ( pDemand )
    *(_DWORD *)(pDemand + 4) = Obj;
  return 1;
}

// 0x004DB160
bool CCBAI::CastReviveSkill(int nRoleIndex)
{
  void *Role; // edi
  CCBRoleState *m_pRoleState; // ecx
  int pnVal[11]; // [esp+0xC] [ebp-0x2C] BYREF

  if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(nRoleIndex)->dwID != 739 )
    return 0;
  Role = ((CCBRoleState *)this->m_pRoleState)->GetRole(nRoleIndex);
  if ( Role != ((CCBRoleState *)this->m_pRoleState)->GetRole(nRoleIndex) )
    return 0;
  memset(pnVal, 0, sizeof(pnVal));
  m_pRoleState = this->m_pRoleState;
  LOWORD(pnVal[4]) = 0;
  LOBYTE(pnVal[10]) = 1;
  pnVal[0] = 261;
  pnVal[1] = 7709;
  pnVal[2] = nRoleIndex;
  pnVal[3] = -1;
  ((CCBRoleState *)m_pRoleState)->GetRoleNum(pnVal);
  ((CCBSystem *)this->m_pCBSystem)->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, pnVal);
  ((CEffMgr *)this->m_pCBSystem->m_pEffMgr)->Init(559, 0, 0, 0, 0);
  return 1;
}

// 0x004DB270
// attributes: thunk
bool CCBAI::CastCureSpecStateMagic()
{
  return this->CastCureSpecStateSkill();
}

// 0x004DB280
bool CCBAI::CastCureSpecStateSkill()
{
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[3] = 1094713344;
  return 0;
}

// 0x004DB290
// attributes: thunk
void CCBAI::CastCureSpecStateItem()
{

}

// 0x004DB2A0
void CCBAI::HasVeryPunyFiveMagicRole()
{
  *(float *)&g_RoleSystemCombat.m_partyActor.m_dwMatMsg[2] = 12.0 + 12.0;
}

// 0x004DB2B0
// attributes: thunk
bool CCBAI::CreateValueAutomation()
{
  return this->AddValueFunction();
}

// 0x004DB2C0
bool CCBAI::AddValueFunction()
{
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[5] = 119;
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[6] = 314;
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[7] = 510;
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[8] = 707;
  return -61;
}

// 0x004DB300
// attributes: thunk
bool CCBAI::AddValueItem(int nData, unsigned int dwData)
{
  return this->DestroyValueAutomation();
}

// 0x004DB310
bool CCBAI::DestroyValueAutomation()
{
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[9] = 519;
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[10] = 519;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_bChangedMat = 519;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[3] = 519;
  return 7;
}

// 0x004DB350
// attributes: thunk
int CCBAI::RunValueAutomation()
{
  int result; // eax

  LOBYTE(result) = this->SpecAI();
  return result;
}

// 0x004DB360
bool CCBAI::SpecAI()
{
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[7] = 128;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[11] = 323;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[15] = 519;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[19] = 716;
  return -52;
}
