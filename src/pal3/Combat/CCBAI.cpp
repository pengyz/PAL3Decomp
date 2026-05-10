#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBAI.h"

// Forward declarations for unnamed functions
int sub_4D8580(...);
int sub_4F2C30(...);
int sub_4F5330(...);
int sub_4F5D00(...);
int sub_4F6000(...);
int sub_4F61D0(...);
int sub_4F6370(...);
int sub_4F6690(...);
int sub_4F6860(...);
int sub_4F6A80(...);
int sub_4F6BB0(...);
int sub_4FB6B0(...);
int sub_515CE0(...);

// Unnamed globals (extern)
extern int dword_17A89C8;
extern int dword_17A89CC;
extern int dword_17A89D0;
extern int dword_17A89D4;
extern int dword_17A89D8;
extern int dword_17A89DC;
extern int dword_17A89E0;
extern int dword_17A89E4;
extern int unk_1010101;

// 0x004014F0
char CCBAI::Thunk_GetValue(int a1, int a2)
{
  return 0;
}

// 0x0040CFE0
void * CCBAI::GetTargetRole(void *pOut)
{
  _DWORD *v2; // edx
  int v4; // [esp+Ch] [ebp+8h]

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
  return 709;
}

// 0x004D7030
// attributes: thunk
int CCBAI::~CCBAI()
{
  return CCBAI::Reset();
}

// 0x004D7040
int CCBAI::Reset()
{
  dword_17A89D8 = 573;
  dword_17A89DC = 573;
  dword_17A89E0 = 573;
  dword_17A89E4 = 573;
  return 573;
}

// 0x004D7080
_DWORD * CCBAI::Create(_DWORD *a2)
{
  memset(this, 0, 0xE50u);
  this->m_bNewRole[3] = (__int32)a2;
  this->m_bNewRole[4] = a2[4];
  this->m_bNewRole[5] = *a2;
  return this->m_bNewRole;
}

// 0x004D70C0
char CCBAI::Init()
{
  memset(&this->m_Demand[1][3], 0, 0x6E0u);
  memset(&this->m_FriendDemand[4], 0, 0xA0u);
  memset((char *)this + 3504, 0, 0xA0u);
  this->SetNewRole();
  this->RepeatPlayerLastOperation();
  return 1;
}

// 0x004D7100
int CCBAI::Update()
{
  CCBAI::DemandThreadTracer((int)this);
  return this->FillAllDemandSatisfy();
}

// 0x004D7120
char CCBAI::Render(int a2)
{
  char v3; // bl
  int v4; // eax
  char RoleField; // al
  CCBRoleState *v6; // ecx
  char result; // al

  v3 = 0;
  if ( (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a2, 0) > 0 )
  {
    v4 = *(_DWORD *)(*(_DWORD *)(this->m_bNewRole[3] + 20) + 4 * a2 + 24);
    *(float *)(v4 + 6632) = *(float *)(v4 + 6636);
  }
  RoleField = (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 18);
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( RoleField )
  {
    if ( v6->GetRoleAttr(a2) != 5 )
      return sub_4D8580(this, a2);
    return v3;
  }
  else
  {
    switch ( v6->GetRoleAttr(a2) )
    {
      case 1:
      case 2:
        result = this->HandleEnemyAction(a2);
        break;
      case 3:
        result = this->HandleEnemyWell(a2);
        break;
      case 4:
        result = this->HandleEnemyWeak(a2);
        break;
      case 5:
        result = 0;
        break;
      default:
        return v3;
    }
  }
  return result;
}

// 0x004D71E0
char CCBAI::HandleEnemyAction(int a2)
{
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // edi
  CCBRoleState *v8; // ecx
  CCBRoleState *v9; // ecx
  int v10; // [esp+38h] [ebp-Ch]
  tagDemand *a4; // [esp+3Ch] [ebp-8h]
  int roleIdx; // [esp+40h] [ebp-4h]

  if ( this->CastReviveSkill(a2) == 1 )
    return 1;
  v4 = g_RandSeed;
  v5 = 0;
  roleIdx = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v4 = 214013 * v4 + 2531011;
    g_RandSeed = v4;
    if ( ((v4 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( *(_BYTE *)(this->m_bNewRole[4] + v5 + 577) )
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
    v10 = 892 * v6;
    for ( a4 = &this->m_Demand[1][10 * v6 + 7]; ; a4 += 10 )
    {
      v8 = (CCBRoleState *)this->m_bNewRole[4];
      if ( v8->m_Role[0].sModel[v7 + 5] )
      {
        if ( !v8->IsRoleAlive(v6)
          || (v9 = (CCBRoleState *)this->m_bNewRole[4], v9->m_Role[0].sModel[v7 + 11] == 1) )
        {
          v6 = roleIdx;
        }
        else
        {
          if ( (unsigned int)v7 < 0x116C
            || v9->GetRoleField(a2, 19)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7)
            || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 18)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
          {
            if ( a4[2].nSatisfy < 100 && this->DemandChecker(a2, roleIdx, (int)&a4[2]) == 1 )
              return 1;
          }
          if ( this->m_FriendDemand[5].nSatisfy < 100
            && this->CastRecoverMagic(a2, (int)&this->m_FriendDemand[5]) )
          {
            return 1;
          }
          if ( v7 >= 4460 )
          {
            if ( v7 < 9812 && a4[-3].nSatisfy < 100 && this->CastNormalAttack(a2, roleIdx, (int)&a4[-3]) )
              return 1;
            if ( v7 < 9812 && a4->nSatisfy < 100 )
            {
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x3FF) < (int)512.0 )
              {
                if ( this->CastAttackBigItem(a2, roleIdx, (int)a4) )
                  return 1;
              }
            }
          }
          if ( *((int *)this + 896) < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)378.88 )
            {
              if ( this->CastAttackMagic(a2, (int)this + 3584) )
                return 1;
            }
            if ( (CCBRoleState *->GetRoleType()this->m_bNewRole[4], a2) )
            {
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
              {
                if ( a2->Thunk_GetValue((int)this + 3584) )
                  return 1;
              }
            }
          }
          if ( v10 >= 0 )
          {
            if ( v10 >= 4460 )
            {
              if ( v10 < 9812 )
              {
                ++g_nRandCallCount;
                g_RandSeed = 214013 * g_RandSeed + 2531011;
                if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
                {
                  if ( a4[-3].nSatisfy < 100 && this->CastNormalAttack(a2, roleIdx, 0) )
                    return 1;
                  ++g_nRandCallCount;
                  g_RandSeed = 214013 * g_RandSeed + 2531011;
                  if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
                  {
                    if ( this->CastAttackBigMagic(a2, roleIdx) )
                      return 1;
                  }
                }
              }
            }
            else
            {
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x3FF) < (int)153.59999
                && (this->CastAttackMagic(a2, 0) || this->CastRecoverBigMagic(a2, roleIdx, 0)) )
              {
                return 1;
              }
            }
          }
          if ( (unsigned int)v10 < 0x116C
            || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7)
            || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 18)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
          {
            if ( this->DemandChecker(a2, roleIdx, 0) )
              return 1;
          }
          v6 = roleIdx;
          v7 = v10;
        }
      }
      v7 += 892;
      roleIdx = ++v6;
      v10 = v7;
      if ( v7 >= 9812 )
        return 0;
    }
  }
  if ( v6 < 11 )
    goto LABEL_12;
  return 0;
}

// 0x004D7820
char CCBAI::HandleEnemyWell(int a2)
{
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // edi
  CCBRoleState *v7; // ecx
  CCBRoleState *v8; // ecx
  int v9; // edx
  int v10; // edx
  int v11; // edi
  tagDemand *a4; // [esp+40h] [ebp-Ch]
  int v14; // [esp+44h] [ebp-8h]
  int roleIdx; // [esp+48h] [ebp-4h]

  v3 = g_RandSeed;
  v4 = 0;
  roleIdx = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v3 = 214013 * v3 + 2531011;
    g_RandSeed = v3;
    if ( ((v3 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( *(_BYTE *)(this->m_bNewRole[4] + v4 + 577) )
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
    v14 = 892 * v5;
    for ( a4 = &this->m_Demand[1][10 * v5 + 4]; ; a4 += 10 )
    {
      v7 = (CCBRoleState *)this->m_bNewRole[4];
      if ( v7->m_Role[0].sModel[v6 + 5] )
        break;
LABEL_75:
      v6 += 892;
      roleIdx = ++v5;
      v14 = v6;
      if ( v6 >= 9812 )
        return 0;
    }
    if ( !v7->IsRoleAlive(v5)
      || (v8 = (CCBRoleState *)this->m_bNewRole[4], v8->m_Role[0].sModel[v6 + 11] == 1) )
    {
LABEL_74:
      v5 = roleIdx;
      goto LABEL_75;
    }
    if ( (unsigned int)v6 < 0x116C
      || v8->GetRoleField(a2, 19)
      && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7)
      || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 18)
      && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
    {
      if ( a4[5].nSatisfy < 100 && this->DemandChecker(a2, roleIdx, (int)&a4[5]) )
        return 1;
    }
    if ( this->m_FriendDemand[5].nSatisfy < 100 && this->CastRecoverMagic(a2, (int)&this->m_FriendDemand[5]) )
      return 1;
    v9 = roleIdx;
    if ( roleIdx == a2 && a4->nSatisfy < 100 )
    {
      if ( this->CastNormalAttack(a2, roleIdx, (int)a4) )
        return 1;
      v9 = roleIdx;
    }
    if ( v6 >= 4460 )
    {
      if ( v6 < 9812 && a4->nSatisfy < 100 )
      {
        if ( this->CastNormalAttack(a2, v9, (int)a4) )
          return 1;
        v9 = roleIdx;
      }
      if ( v6 < 9812 && a4[3].nSatisfy < 100 )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        if ( ((g_RandSeed >> 16) & 0x3FF) < (int)512.0 )
        {
          if ( this->CastAttackBigItem(a2, v9, (int)&a4[3]) )
            return 1;
        }
      }
    }
    if ( *((int *)this + 896) < 100 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)256.0 )
      {
        if ( this->CastAttackMagic(a2, (int)this + 3584) )
          return 1;
      }
      if ( (CCBRoleState *->GetRoleType()this->m_bNewRole[4], a2) )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
        {
          if ( a2->Thunk_GetValue((int)this + 3584) )
            return 1;
        }
      }
    }
    v10 = v14;
    if ( v14 < 0 )
      goto LABEL_82;
    if ( v14 >= 4460
      || a4[7].nSatisfy >= 100
      || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x3FF) >= (int)716.79999) )
    {
      v11 = roleIdx;
    }
    else
    {
      v11 = roleIdx;
      if ( this->CastRecoverBigMagic(a2, roleIdx, (int)&a4[7]) )
        return 1;
      v10 = v14;
    }
    if ( v10 < 0 )
      goto LABEL_82;
    if ( v10 < 4460 && a4[8].nSatisfy < 100 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)716.79999 && this->DemandChecker(a2, v11, (int)&a4[8]) )
        return 1;
      v10 = v14;
    }
    if ( v10 < 4460 && a4[6].nSatisfy < 100 )
    {
      if ( this->CastRecoverBigMagic(a2, v11, (int)&a4[6]) )
        return 1;
      v10 = v14;
    }
    if ( v10 < 4460 && a4[6].nSatisfy < 100 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)256.0 && this->CastRecoverBigMagic(a2, v11, (int)&a4[6]) )
        return 1;
      v10 = v14;
    }
    if ( v10 < 4460 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)102.39999 )
      {
        if ( this->CastAttackMagic(a2, 0) || this->CastRecoverBigMagic(a2, v11, 0) )
          return 1;
        v10 = v14;
      }
    }
    if ( v10 >= 4460 )
    {
LABEL_82:
      if ( !(CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19)
        || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 <= 7) )
      {
LABEL_73:
        v6 = v14;
        goto LABEL_74;
      }
      v11 = roleIdx;
    }
    if ( this->DemandChecker(a2, v11, 0) )
      return 1;
    goto LABEL_73;
  }
  if ( v5 < 11 )
    goto LABEL_10;
  return 0;
}

// 0x004D7EF0
char CCBAI::HandleEnemyWeak(int a2)
{
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // edi
  CCBRoleState *v7; // ecx
  CCBRoleState *v8; // ecx
  int v9; // edx
  int v10; // edx
  int v11; // edi
  int v13; // [esp+40h] [ebp-Ch]
  tagDemand *a4; // [esp+44h] [ebp-8h]
  int roleIdx; // [esp+48h] [ebp-4h]

  v3 = g_RandSeed;
  v4 = 0;
  roleIdx = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v3 = 214013 * v3 + 2531011;
    g_RandSeed = v3;
    if ( ((v3 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( *(_BYTE *)(this->m_bNewRole[4] + v4 + 577) )
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
  v13 = 892 * v5;
  for ( a4 = &this->m_Demand[1][10 * v5 + 4]; ; a4 += 10 )
  {
    v7 = (CCBRoleState *)this->m_bNewRole[4];
    if ( v7->m_Role[0].sModel[v6 + 5] )
      break;
LABEL_76:
    v6 += 892;
    roleIdx = ++v5;
    v13 = v6;
    if ( v6 >= 9812 )
      return 0;
  }
  if ( !v7->IsRoleAlive(v5)
    || (v8 = (CCBRoleState *)this->m_bNewRole[4], v8->m_Role[0].sModel[v6 + 11] == 1) )
  {
    v5 = roleIdx;
    goto LABEL_76;
  }
  if ( (unsigned int)v6 >= 0x116C
    && (!v8->GetRoleField(a2, 19)
     || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 <= 7)
     || a4[5].nSatisfy >= 100)
    || !this->DemandChecker(a2, roleIdx, (int)&a4[5]) )
  {
    if ( this->m_FriendDemand[5].nSatisfy >= 100 || !this->CastRecoverMagic(a2, (int)&this->m_FriendDemand[5]) )
    {
      v9 = roleIdx;
      if ( roleIdx == a2 && a4->nSatisfy < 100 )
      {
        if ( this->CastNormalAttack(a2, roleIdx, (int)a4) || this->CastRecoverMagic(a2, (int)a4) )
          return 1;
        v9 = roleIdx;
      }
      if ( v6 < 4460 )
        goto LABEL_81;
      if ( v6 < 9812 && a4->nSatisfy < 100 )
      {
        if ( this->CastNormalAttack(a2, v9, (int)a4) )
          return 1;
        v9 = roleIdx;
      }
      if ( v6 >= 9812
        || a4[3].nSatisfy >= 100
        || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x3FF) >= (int)512.0)
        || !this->CastAttackBigItem(a2, v9, (int)&a4[3]) )
      {
LABEL_81:
        if ( *((int *)this + 896) >= 100
          || ((++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011,
                                   ((g_RandSeed >> 16) & 0x3FF) >= (int)256.0)
           || !this->CastAttackMagic(a2, (int)this + 3584))
          && (!(CCBRoleState *->GetRoleType()this->m_bNewRole[4], a2)
           || (++g_nRandCallCount,
               g_RandSeed = 214013 * g_RandSeed + 2531011,
               ((g_RandSeed >> 16) & 0x3FF) >= (int)307.19998)
           || !a2->Thunk_GetValue((int)this + 3584)) )
        {
          v10 = v13;
          if ( v13 < 0 )
            goto LABEL_82;
          if ( v13 >= 4460
            || a4[7].nSatisfy >= 100
            || (++g_nRandCallCount,
                g_RandSeed = 214013 * g_RandSeed + 2531011,
                ((g_RandSeed >> 16) & 0x3FF) >= (int)716.79999) )
          {
            v11 = roleIdx;
          }
          else
          {
            v11 = roleIdx;
            if ( this->CastRecoverBigMagic(a2, roleIdx, (int)&a4[7]) )
              return 1;
            v10 = v13;
          }
          if ( v10 < 0 )
            goto LABEL_82;
          if ( v10 < 4460 && a4[8].nSatisfy < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)716.79999 && this->DemandChecker(a2, v11, (int)&a4[8]) )
              return 1;
            v10 = v13;
          }
          if ( v10 < 4460 && a4[6].nSatisfy < 100 )
          {
            if ( this->CastRecoverBigMagic(a2, v11, (int)&a4[6]) )
              return 1;
            v10 = v13;
          }
          if ( v10 < 4460 && a4[6].nSatisfy < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)256.0 && this->CastRecoverBigMagic(a2, v11, (int)&a4[6]) )
              return 1;
            v10 = v13;
          }
          if ( v10 < 4460 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)102.39999 )
            {
              if ( this->CastAttackMagic(a2, 0) || this->CastRecoverBigMagic(a2, v11, 0) )
                return 1;
              v10 = v13;
            }
          }
          if ( v10 < 4460 )
          {
LABEL_71:
            if ( this->DemandChecker(a2, v11, 0) )
              return 1;
          }
          else
          {
LABEL_82:
            if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
            {
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7 )
              {
                v11 = roleIdx;
                goto LABEL_71;
              }
            }
          }
          v5 = roleIdx;
          v6 = v13;
          goto LABEL_76;
        }
      }
    }
  }
  return 1;
}

// 0x004D86D0
char CCBAI::HandleEnemyChaos(int a2)
{
  CCBRoleState *v3; // ecx
  int v4; // eax
  CCBAI *v5; // ecx
  char result; // al
  int v7; // [esp-4h] [ebp-10h]

  v3 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v3->m_Role[0].sModel[892 * a2 + 5]
    || !v3->IsRoleAlive(a2)
    || !*(_DWORD *)((CCBRoleState *->InitUI()this->m_bNewRole[4], a2) + 36) )
  {
    return 0;
  }
  v7 = a2;
  v4 = *(_DWORD *)(*(_DWORD *)(this->m_bNewRole[3] + 20) + 4 * a2 + 24);
  v5 = this;
  *(float *)(v4 + 6632) = *(float *)(v4 + 6636);
  if ( *(_BYTE *)(892 * a2 + this->m_bNewRole[4] + 1388) )
  {
    result = this->HandleFriendAction(a2);
    if ( result )
      return result;
    v7 = a2;
    v5 = this;
  }
  return v5->HandleFriendNegative(v7);
}

// 0x004D8760
char CCBAI::HandleFriendAction(int a2)
{
  int v3; // ebx
  int v4; // eax
  CCBRoleState *v5; // ecx
  bool v6; // cc
  int v8; // [esp+10h] [ebp-8h]
  tagDemand *a4; // [esp+14h] [ebp-4h]

  v3 = 0;
  v4 = 0;
  v8 = 0;
  for ( a4 = &this->m_Demand[1][4]; ; a4 += 10 )
  {
    v5 = (CCBRoleState *)this->m_bNewRole[4];
    if ( v5->m_Role[0].sModel[v4 + 5] )
    {
      if ( v5->GetRoleField(a2, 18) )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        switch ( (g_RandSeed >> 16) & 0x3F )
        {
          case 0:
            if ( !this->CastRecoverBigItem(a2, v3, 0) )
              goto LABEL_46;
            return 1;
          case 1:
            if ( !this->CastRecoverItem(a2, v3, 0) )
              goto LABEL_46;
            return 1;
          case 2:
            if ( this->CastAttackItem(a2, v3, 0) != 1 )
              goto LABEL_46;
            return 1;
          case 3:
            if ( !this->CastRecoverMagic(a2, 0) )
              goto LABEL_46;
            return 1;
          case 4:
            if ( !this->CastBFAMagic(a2, 0) )
              goto LABEL_46;
            return 1;
          case 5:
            if ( !this->CastRecoverBigSkill(a2, 0) )
              goto LABEL_46;
            return 1;
          case 6:
            if ( !this->CastNormalAttack(a2, v3, 0) )
              goto LABEL_46;
            return 1;
          case 7:
            if ( !this->CastSpecifyMagic(a2, v3, 0) )
              goto LABEL_46;
            return 1;
          case 8:
            if ( !this->CastRecoverSkill(a2, v3, 0) )
              goto LABEL_46;
            return 1;
          default:
            goto LABEL_46;
        }
      }
      if ( (unsigned int)v8 < 0x116C
        && a4[1].nSatisfy < 100
        && (this->CastRecoverBigItem(a2, v3, (int)&a4[1])
         || this->CastRecoverItem(a2, v3, (int)&a4[1])
         || this->CastAttackItem(a2, v3, (int)&a4[1]) == 1) )
      {
        break;
      }
      if ( (CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], v3)
        && *(_BYTE *)((CCBRoleState *->InitUI()this->m_bNewRole[4], v3) + 880) != 1 )
      {
        if ( *((int *)this + 880) < 100
          && (this->CastRecoverMagic(a2, (int)this + 3520)
           || this->CastBFAMagic(a2, (int)this + 3520)
           || this->CastRecoverBigSkill(a2, (int)this + 3520)) )
        {
          break;
        }
        if ( v8 >= 0 )
        {
          if ( v8 < 4460
            && a4->nSatisfy < 50
            && (this->CastNormalAttack(a2, v3, (int)a4)
             || this->CastSpecifyMagic(a2, v3, (int)a4)
             || this->CastRecoverSkill(a2, v3, (int)a4)) )
          {
            break;
          }
          if ( v8 < 4460 && a4[3].nSatisfy < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)512.0
              && (this->CastAttackBigItem(a2, v3, (int)&a4[3])
               || this->CastBossPhysicalAttack(a2, v3, (int)&a4[3])
               || this->CastReviveMagic(a2, v3, (int)&a4[3])) )
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
char CCBAI::HandleFriendNegative(int a2)
{
  int v4; // edi
  int v5; // ebx
  CCBRoleState *v6; // ecx
  int v7; // ebx
  char result; // al
  int v9; // edi
  CCBRoleState *v10; // ecx
  int v11; // ebx
  CCBRoleState *v12; // ecx
  char v13; // al
  int v14; // [esp+10h] [ebp-4h]
  tagDemand *roleIdx; // [esp+18h] [ebp+4h]
  int roleIdxa; // [esp+18h] [ebp+4h]

  if ( !(CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 18) )
  {
    v4 = 0;
    v5 = 0;
    v14 = 0;
    for ( roleIdx = &this->m_Demand[1][9]; ; roleIdx += 10 )
    {
      v6 = (CCBRoleState *)this->m_bNewRole[4];
      if ( !v6->m_Role[0].sModel[v5 + 5]
        || !v6->IsRoleAlive(v4)
        || *(_BYTE *)((CCBRoleState *->InitUI()this->m_bNewRole[4], v4) + 880) )
      {
        goto LABEL_30;
      }
      if ( this->m_FriendDemand[9].nSatisfy < 100
        && (this->CastAttackMagic(a2, (int)&this->m_FriendDemand[9]) == 1
         || this->CastRandEnemyMagic(a2, (int)&this->m_FriendDemand[9]) == 1
         || this->CastAttackBigSkill(a2, (int)&this->m_FriendDemand[9]) == 1) )
      {
        return 1;
      }
      if ( v14 < 4460 )
      {
        v7 = (int)roleIdx;
      }
      else
      {
        v7 = (int)roleIdx;
        if ( v14 < 9812 && roleIdx->nSatisfy < 100 )
        {
LABEL_17:
          if ( this->DemandChecker(a2, v4, v7) == 1
            || this->CastRecoverBigMagic(a2, v4, v7) == 1
            || this->CastBFAAttackMagic(a2, v4, v7) == 1
            || this->CastAttackSkill(a2, v4, v7) == 1 )
          {
            return 1;
          }
          goto LABEL_21;
        }
      }
      if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        if ( ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7 )
          goto LABEL_17;
      }
LABEL_21:
      if ( v14 >= 4460 && v14 < 9812
        || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19)
        && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
      {
        if ( this->DemandChecker(a2, v4, 0) == 1
          || this->CastRecoverBigMagic(a2, v4, 0) == 1
          || this->CastBFAAttackMagic(a2, v4, 0) == 1
          || this->CastAttackSkill(a2, v4, 0) == 1 )
        {
          return 1;
        }
      }
      v5 = v14;
LABEL_30:
      v5 += 892;
      ++v4;
      v14 = v5;
      if ( v5 >= 9812 )
        return 0;
    }
  }
  v9 = g_RandSeed;
  roleIdxa = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v9 = 214013 * v9 + 2531011;
    g_RandSeed = v9;
    v10 = (CCBRoleState *)this->m_bNewRole[4];
    v11 = ((v9 >> 16) & 0x7FFF) % 11;
    if ( v10->m_Role[0].sModel[892 * v11 + 5] )
      break;
LABEL_37:
    if ( ++roleIdxa >= 1024 )
      goto LABEL_38;
  }
  if ( !*(_BYTE *)(v10->InitUI(((v9 >> 16) & 0x7FFF) % 11) + 880) || v11 == a2 )
  {
    v9 = g_RandSeed;
    goto LABEL_37;
  }
LABEL_38:
  v12 = (CCBRoleState *)this->m_bNewRole[4];
  if ( v12->m_Role[0].sModel[892 * v11 + 5] && !*(_BYTE *)(v12->InitUI(v11) + 880) )
  {
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    switch ( ((g_RandSeed >> 16) & 0x7FFF) % 11 )
    {
      case 0:
        v13 = this->CastAttackMagic(a2, 0);
        return v13 == 1;
      case 1:
        v13 = this->CastRandEnemyMagic(a2, 0);
        return v13 == 1;
      case 2:
        result = this->CastAttackBigSkill(a2, 0);
        goto LABEL_49;
      case 3:
      case 10:
        v13 = this->DemandChecker(a2, v11, 0);
        return v13 == 1;
      case 4:
      case 7:
        result = this->CastRecoverBigMagic(a2, v11, 0);
        if ( result != 1 )
          return 0;
        return result;
      case 5:
      case 8:
        result = this->CastBFAAttackMagic(a2, v11, 0);
        if ( result != 1 )
          return 0;
        return result;
      case 6:
      case 9:
        result = this->CastAttackSkill(a2, v11, 0);
LABEL_49:
        if ( result == 1 )
          return result;
        return 0;
      default:
        return 0;
    }
  }
  return 0;
}

// 0x004D8F20
char CCBAI::HandleFriendAffirmative(int a2, char a3)
{
  int v4; // ebx
  int v5; // edi
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBRoleState *v8; // ecx
  double v9; // st7
  int v11; // ebx
  int v12; // edi
  CCBRoleState *v13; // ecx
  __int32 v15; // ecx
  CCBAI *v16; // edx
  _DWORD v17[11]; // [esp+Ch] [ebp-44h] BYREF
  CCBAI *v18; // [esp+38h] [ebp-18h]
  int v19; // [esp+3Ch] [ebp-14h]
  int v20; // [esp+40h] [ebp-10h]
  float v21; // [esp+44h] [ebp-Ch]
  int v22; // [esp+48h] [ebp-8h]
  int v23; // [esp+4Ch] [ebp-4h]
  char a2_3; // [esp+5Bh] [ebp+Bh]

  v4 = 0;
  v18 = this;
  v21 = 1.1;
  v23 = -1;
  v22 = 0;
  v5 = 0;
  do
  {
    if ( v4 >= 4460 )
    {
      v6 = (CCBRoleState *)this->m_bNewRole[4];
      if ( v6->m_Role[0].sModel[v4 + 5] )
      {
        if ( v6->IsRoleAlive(v5) )
        {
          ++v22;
          v7 = (CCBRoleState *->SetRoleField()this->m_bNewRole[4], v5, 0);
          v8 = (CCBRoleState *)this->m_bNewRole[4];
          *(float *)&v19 = (float)v7;
          v20 = v8->SetRoleField(v5, 1);
          v9 = *(float *)&v19 / (double)v20;
          if ( v9 < v21 )
          {
            v21 = v9;
            v23 = v5;
          }
        }
      }
    }
    v4 += 892;
    ++v5;
  }
  while ( v4 < 9812 );
  if ( v22 <= 0 )
    return 0;
  if ( v23 == -1 )
  {
    v11 = 0;
    v12 = 0;
    while ( 1 )
    {
      if ( v12 >= 4460 )
      {
        v13 = (CCBRoleState *)this->m_bNewRole[4];
        if ( v13->m_Role[0].sModel[v12 + 5] )
        {
          if ( v13->IsRoleAlive(v11) )
          {
            v19 = 100 / v22;
            if ( 100 / v22 > 0 )
            {
              *(float *)&v19 = (double)v19 * 10.24;
              v20 = (int)*(float *)&v19;
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x3FF) < v20 )
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
    v23 = v11;
    if ( v11 != -1 )
      goto LABEL_21;
    return 0;
  }
  else
  {
LABEL_21:
    *(_BYTE *)((CCBRoleState *->InitUI()this->m_bNewRole[4], a2) + 832) = 1;
    a2_3 = this->DemandChecker(a2, v23, 0);
    *(_BYTE *)((CCBRoleState *->InitUI()this->m_bNewRole[4], a2) + 832) = 0;
    if ( a3 )
    {
      memset(v17, 0, sizeof(v17));
      LOWORD(v17[4]) = 0;
      v17[3] = v23;
      v15 = this->m_bNewRole[3];
      v16 = v18;
      LOBYTE(v17[10]) = 1;
      v17[0] = 259;
      v17[2] = a2;
      qmemcpy((void *)(v15 + 52 * a2 + 90264), v17, 0x2Cu);
      *((_BYTE *)v16->m_bNewRole + a2) = 0;
    }
    return a2_3;
  }
}

// 0x004D9130
char CCBAI::HandlePlayerNormalAttack(int a2, int a3)
{
  int (*v4)(int, int); // eax
  char result; // al
  int v6; // eax
  int v7; // eax
  int v8; // eax

  switch ( *(_DWORD *)a3 )
  {
    case 0x103:
      result = 1;
      goto LABEL_5;
    case 0x104:
    case 0x105:
    case 0x106:
      result = (CCBRoleState *->GetRoleAI()this->m_bNewRole[4], (void *)a3);
      if ( !result )
        goto LABEL_11;
LABEL_5:
      switch ( *(_DWORD *)a3 )
      {
        case 0x103:
          if ( (CCBRoleState *->InitRoleSpecEquipAttrib()this->m_bNewRole[4], a3)
            || *((_BYTE *)this->m_bNewRole + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            *(_DWORD *)(a3 + 12) = (CCBRoleState *->CalcMPCost()this->m_bNewRole[4], 2);
            *(_BYTE *)(a3 + 17) = 0;
            (CCBRoleState *->CalcHealAmount()this->m_bNewRole[4], a3);
          }
          v4 = CCBSystem::IsRoleWaitForFlee;
          goto LABEL_33;
        case 0x104:
          if ( (CCBRoleState *->InitRoleSpecEquipAttrib()this->m_bNewRole[4], a3)
            || *((_BYTE *)this->m_bNewRole + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            if ( sub_4F6A80(*(_DWORD *)(a3 + 4)) )
              v7 = (CCBRoleState *->CalcMPCost()this->m_bNewRole[4], 2);
            else
              v7 = (CCBRoleState *->CalcMPCost()this->m_bNewRole[4], 1);
            *(_DWORD *)(a3 + 12) = v7;
            *(_BYTE *)(a3 + 17) = 0;
            (CCBRoleState *->GetRoleNum()this->m_bNewRole[4], (int *)a3);
          }
          v4 = CCBSystem::GetThreadIndex;
          goto LABEL_33;
        case 0x105:
          if ( (CCBRoleState *->InitRoleSpecEquipAttrib()this->m_bNewRole[4], a3)
            || *((_BYTE *)this->m_bNewRole + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            if ( sub_4F6A80(*(_DWORD *)(a3 + 4)) )
              v6 = (CCBRoleState *->CalcMPCost()this->m_bNewRole[4], 2);
            else
              v6 = (CCBRoleState *->CalcMPCost()this->m_bNewRole[4], 1);
            *(_DWORD *)(a3 + 12) = v6;
            *(_BYTE *)(a3 + 17) = 0;
            (CCBRoleState *->GetRoleNum()this->m_bNewRole[4], (int *)a3);
          }
          v4 = CCBSystem::GetSameThreadNum;
          goto LABEL_33;
        case 0x106:
          if ( (CCBRoleState *->InitRoleSpecEquipAttrib()this->m_bNewRole[4], a3)
            || *((_BYTE *)this->m_bNewRole + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            if ( sub_4F6BB0(*(_DWORD *)(a3 + 4)) )
              v8 = (CCBRoleState *->CalcMPCost()this->m_bNewRole[4], 2);
            else
              v8 = (CCBRoleState *->CalcMPCost()this->m_bNewRole[4], 1);
            *(_DWORD *)(a3 + 12) = v8;
            *(_BYTE *)(a3 + 17) = 0;
            (CCBRoleState *->GetRoleNum()this->m_bNewRole[4], (int *)a3);
          }
          v4 = CCBSystem::PassCmdToThread;
          goto LABEL_33;
        default:
          return result;
      }
    case 0x109:
      v4 = CCBSystem::PassCmdViaThread;
      goto LABEL_33;
    case 0x10B:
      v4 = CCBSystem::PassCmdToThread;
LABEL_33:
      (CCBSystem *->CreateObj()this->m_bNewRole[3], v4, 0, 0, 0, (const void *)a3);
      result = 1;
      break;
    default:
LABEL_11:
      result = this->HandleFriendAffirmative(a2, 0);
      break;
  }
  return result;
}

// 0x004D9360
void * CCBAI::RepeatPlayerLastOperation()
{
  this->m_bNewRole[0] = (__int32)&unk_1010101;
  this->m_bNewRole[1] = (__int32)&unk_1010101;
  LOWORD(this->m_bNewRole[2]) = (unsigned __int16)&unk_1010101;
  BYTE2(this->m_bNewRole[2]) = (unsigned __int8)&unk_1010101;
  return &unk_1010101;
}

// 0x004D9380
_DWORD * CCBAI::SetNewRole()
{
  tagDemand *v1; // eax
  int v2; // esi
  int v3; // edx
  _DWORD *result; // eax
  int v5; // ecx

  v1 = (tagDemand *)&this->m_Demand[1][3];
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
  result = (_DWORD *)((char *)this + 3504);
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
int CCBAI::FillAllDemandSatisfy()
{
  __int32 *p_bHandle; // esi
  int v3; // ebp
  int i; // edi
  __int32 *v5; // esi
  int v6; // ebp
  int result; // eax
  int v8; // edi
  int v9; // [esp+10h] [ebp-8h]
  __int32 *v10; // [esp+14h] [ebp-4h]

  p_bHandle = (__int32 *)&this->m_Demand[1][4].bHandle;
  v9 = 0;
  v3 = 99;
  v10 = (__int32 *)&this->m_Demand[1][4].bHandle;
  do
  {
    if ( *(_BYTE *)(v9 + this->m_bNewRole[4] + 577) )
    {
      for ( i = 1; i < 10; ++i )
      {
        if ( *(p_bHandle - 1) )
        {
          if ( sub_515CE0((char *)this->m_bNewRole[3], *(p_bHandle - 1)) )
          {
            *(_BYTE *)p_bHandle = 1;
            this->m_bNewRole[4 * i + 4 * v3] = 100;
          }
          else
          {
            *(p_bHandle - 1) = 0;
            *(_BYTE *)p_bHandle = 0;
          }
        }
        p_bHandle += 4;
      }
    }
    v3 += 10;
    v9 += 892;
    p_bHandle = (__int32 *)v10 + 40;
    v10 += 40;
  }
  while ( v3 < 209 );
  v5 = (__int32 *)&this->m_FriendDemand[5].bHandle;
  v6 = 9;
  do
  {
    result = *(v5 - 1);
    v8 = v5[39];
    if ( result )
    {
      LOBYTE(result) = sub_515CE0((char *)this->m_bNewRole[3], *(v5 - 1));
      if ( (_BYTE)result )
      {
        *(_BYTE *)v5 = 1;
        *(v5 - 2) = 100;
      }
      else
      {
        *(v5 - 1) = 0;
        *(_BYTE *)v5 = 0;
      }
    }
    if ( v8 )
    {
      LOBYTE(result) = sub_515CE0((char *)this->m_bNewRole[3], v8);
      if ( (_BYTE)result )
      {
        *((_BYTE *)v5 + 160) = 1;
        v5[38] = 100;
      }
      else
      {
        v5[39] = 0;
        *((_BYTE *)v5 + 160) = 0;
      }
    }
    v5 += 4;
    --v6;
  }
  while ( v6 );
  return result;
}

// 0x004D94F0
char CCBAI::DemandThreadTracer(int _this)
{
  int v2; // edi
  int v3; // ebp
  int v4; // esi
  int v5; // esi
  int v6; // edi
  int v7; // ebp
  int v8; // esi
  int v9; // ebp
  int v10; // esi
  int v11; // edi
  int v12; // esi
  char result; // al
  int v14; // [esp+10h] [ebp-8h] BYREF
  int v15; // [esp+14h] [ebp-4h] BYREF

  v2 = 0;
  v15 = 0;
  v14 = 0;
  v3 = 0;
  v4 = this + 1616;
  do
  {
    if ( *(_BYTE *)(*(_DWORD *)(this + 16) + v3 + 577) )
    {
      if ( (unsigned __int8)v2->IsRoleAlive() )
      {
        *(_DWORD *)v4 = 100;
      }
      else if ( !*(_BYTE *)(v4 + 8) )
      {
        *(_DWORD *)v4 = 0;
      }
      if ( (int)v2->GetRoleAttr() < 3 )
      {
        *(_DWORD *)(v4 - 16) = 100;
        *(_DWORD *)(v4 + 48) = 80;
      }
      else
      {
        if ( !*(_BYTE *)(v4 - 8) )
          *(_DWORD *)(v4 - 16) = 40;
        if ( !*(_BYTE *)(v4 + 56) )
          *(_DWORD *)(v4 + 48) = 40;
      }
      if ( v2->GetRoleAttr() == 4 )
      {
        if ( !*(_BYTE *)(v4 - 8) )
          *(_DWORD *)(v4 - 16) = 10;
        if ( !*(_BYTE *)(v4 + 56) )
          *(_DWORD *)(v4 + 48) = 10;
      }
      if ( (unsigned __int8)v2->GetRoleForce() )
      {
        if ( !*(_BYTE *)(v4 + 40) )
        {
          *(_DWORD *)(v4 + 44) = v2->GetRoleSpeed();
          *(_DWORD *)(v4 + 32) = 50;
        }
      }
      else
      {
        *(_DWORD *)(v4 + 32) = 100;
      }
    }
    v3 += 892;
    ++v2;
    v4 += 160;
  }
  while ( v3 < 9812 );
  CCBRoleState::GetRoleMP(2, &v15, &v14);
  v5 = 0;
  v6 = v15;
  if ( v15 >= v14 )
    goto LABEL_30;
  v7 = 892 * v15;
  do
  {
    if ( *(_BYTE *)(*(_DWORD *)(this + 16) + v7 + 577) && (int)v6->GetRoleAttr() >= 3 )
      ++v5;
    ++v6;
    v7 += 892;
  }
  while ( v6 < v14 );
  if ( v5 >= 2 )
  {
    if ( v5 == 2 )
      v8 = 60;
    else
      v8 = v5 != 3 ? 20 : 40;
  }
  else
  {
LABEL_30:
    v8 = 100;
  }
  if ( !*(_BYTE *)(this + 3368) )
    *(_DWORD *)(this + 3360) = v8 + 10;
  if ( !*(_BYTE *)(this + 3432) )
    *(_DWORD *)(this + 3424) = 100 - v8;
  CCBRoleState::GetRoleMP(1, &v15, &v14);
  v9 = v15;
  v10 = 0;
  if ( v15 >= v14 )
    goto LABEL_45;
  v11 = 892 * v15;
  do
  {
    if ( *(_BYTE *)(v11 + *(_DWORD *)(this + 16) + 577) && (int)v9->GetRoleAttr() >= 3 )
      ++v10;
    ++v9;
    v11 += 892;
  }
  while ( v9 < v14 );
  if ( v10 >= 2 )
  {
    if ( v10 == 2 )
      v12 = 60;
    else
      v12 = v10 != 3 ? 20 : 40;
  }
  else
  {
LABEL_45:
    v12 = 100;
  }
  if ( !*(_BYTE *)(this + 3528) )
    *(_DWORD *)(this + 3520) = v12 + 10;
  result = *(_BYTE *)(this + 3592);
  if ( !result )
    *(_DWORD *)(this + 3584) = v12;
  return result;
}

// 0x004D9740
char CCBAI::DemandChecker(unsigned int a2, int a3, int a4)
{
  unsigned int v5; // eax
  CCBRoleState *v6; // ecx
  CCBRoleState *v7; // ecx
  unsigned int v8; // edi
  CCBRoleState *v10; // ecx
  int Obj; // eax
  int a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = a2;
  if ( a3 == a2 )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !LOBYTE(v6->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) )
  {
    if ( !v6->GetRoleField(a2, 18)
      && !(CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    {
      return 0;
    }
    v5 = a2;
  }
  v7 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v7->m_Role[0].sModel[892 * a2 + 5]
    || !v7->m_Role[0].sModel[892 * a3 + 5]
    || !v7->IsRoleAlive(v5)
    || !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3)
    || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a3, 23) == 1 )
  {
    return 0;
  }
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a3, 21) == 1
    && (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a3, 20) == 1 )
  {
    v8 = a2;
    if ( a2 <= 4 )
      return 0;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    if ( ((g_RandSeed >> 16) & 0x3FF) < (int)716.79999 )
      return 0;
  }
  else
  {
    v8 = a2;
  }
  if ( !CCBStageRole::ForceEndTaskByPFN(*(CCBStageRole **)(*(_DWORD *)(this->m_bNewRole[3] + 20) + 4 * a3 + 24))
    || !this->m_bNewRole[4]->CalSneakAttack(v8, a3) )
  {
    return 0;
  }
  v10 = (CCBRoleState *)this->m_bNewRole[4];
  LOBYTE(a6[10]) = 1;
  a6[0] = 259;
  a6[2] = v8;
  a6[3] = a3;
  LOWORD(a6[4]) = 0;
  v10->CalcHealAmount((int)a6);
  Obj = (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::IsRoleWaitForFlee, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004D9920
char CCBAI::CastNormalAttack(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 1);
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0);
  v7 = (CCBRoleState *->ProcessAttackResult()this->m_bNewRole[4], a2);
  if ( !v7 )
    return 0;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  LOWORD(a6[4]) = 0;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  a6[0] = 261;
  a6[2] = a2;
  Obj = v8->CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004D9A70
char CCBAI::CastRecoverMagic(int a2, int a3)
{
  CCBRoleState *v4; // ecx
  char result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int v8; // eax
  CCBRoleState *v9; // ecx
  int Obj; // eax
  int a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v4 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v4->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v4->GetRoleField(a2, 18)
    || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
  {
    return 0;
  }
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  result = v6->IsRoleAlive(a2);
  if ( result )
  {
    RoleHP = (CCBRoleState *->GetRoleHP()this->m_bNewRole[4], a2);
    (CCBRoleState *->CalcMagicDefense()this->m_bNewRole[4], RoleHP);
    v8 = (CCBRoleState *->ProcessAttackResult()this->m_bNewRole[4], a2);
    if ( v8 )
    {
      v9 = (CCBRoleState *)this->m_bNewRole[4];
      a6[1] = v8;
      LOBYTE(a6[10]) = 1;
      LOWORD(a6[4]) = 0;
      a6[0] = 261;
      a6[2] = a2;
      a6[3] = -1;
      v9->GetRoleNum(a6);
      Obj = (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = Obj;
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
char CCBAI::CastRecoverBigMagic(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *v9; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  if ( (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0) <= 0 )
    return 0;
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0);
  v7 = (CCBRoleState *->ProcessMagicResult()this->m_bNewRole[4], a2);
  if ( !v7 )
    return 0;
  v8 = sub_4FB6B0(v7);
  a6[2] = a2;
  a6[1] = v8;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  v9 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 261;
  Obj = v9->CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004D9D00
char CCBAI::CastAttackMagic(int a2, int a3)
{
  CCBRoleState *v4; // ecx
  int RoleHP; // eax
  int IsForce1; // eax
  int v7; // edx
  CCBRoleState *v8; // ecx
  int a6[11]; // [esp+10h] [ebp-2Ch] BYREF

  v4 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v4->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v4->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  (CCBRoleState *->GetRoleHP()this->m_bNewRole[4], a2);
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a2) )
    return 0;
  RoleHP = (CCBRoleState *->GetRoleHP()this->m_bNewRole[4], a2);
  IsForce1 = RoleHP->IsForce1();
  if ( !(CCBRoleState *->CalcMagicAttack()this->m_bNewRole[4], IsForce1) )
    return 0;
  v7 = (CCBRoleState *->ProcessMagicResult()this->m_bNewRole[4], a2);
  if ( !v7 )
    return 0;
  memset(a6, 0, sizeof(a6));
  LOBYTE(a6[10]) = 1;
  v8 = (CCBRoleState *)this->m_bNewRole[4];
  LOWORD(a6[4]) = 0;
  a6[0] = 261;
  a6[1] = v7;
  a6[2] = a2;
  a6[3] = -1;
  v8->GetRoleNum(a6);
  (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
  return 1;
}

// 0x004D9E20
char CCBAI::CastAttackBigMagic(int a2, int a3)
{
  CCBRoleState *v4; // ecx
  CCBRoleState *v5; // ecx
  int v6; // eax
  CCBSystem *v7; // ecx
  _DWORD a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v4 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v4->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v4->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v5->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v5->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v5->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  if ( (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0) <= 0 )
    return 0;
  v6 = sub_4F5330((CCBRoleState *)this->m_bNewRole[4], a2, 0);
  if ( !v6 )
    return 0;
  a6[2] = a2;
  a6[1] = v6;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  v7 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 261;
  v7->CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
  return 1;
}

// 0x004D9F50
char CCBAI::CastSpecifyMagic(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 1);
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0);
  v7 = (CCBRoleState *->CalcPhysicalDamage()this->m_bNewRole[4], a2);
  if ( !v7 )
    return 0;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  LOWORD(a6[4]) = 0;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  a6[0] = 260;
  a6[2] = a2;
  Obj = v8->CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DA0A0
char CCBAI::CastBFAMagic(int a2, int a3)
{
  CCBRoleState *v4; // ecx
  char result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int v8; // eax
  CCBRoleState *v9; // ecx
  int Obj; // eax
  int a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v4 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE2(v4->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v4->GetRoleField(a2, 18)
    || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
  {
    return 0;
  }
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  result = v6->IsRoleAlive(a2);
  if ( result )
  {
    RoleHP = (CCBRoleState *->GetRoleHP()this->m_bNewRole[4], a2);
    (CCBRoleState *->CalcMagicDefense()this->m_bNewRole[4], RoleHP);
    v8 = (CCBRoleState *->CalcPhysicalDamage()this->m_bNewRole[4], a2);
    if ( v8 )
    {
      v9 = (CCBRoleState *)this->m_bNewRole[4];
      a6[1] = v8;
      LOBYTE(a6[10]) = 1;
      LOWORD(a6[4]) = 0;
      a6[0] = 260;
      a6[2] = a2;
      a6[3] = -1;
      v9->GetRoleNum(a6);
      Obj = (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::GetThreadIndex, 0, 0, 0, a6);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = Obj;
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
char CCBAI::CastBFAAttackMagic(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE2(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  if ( (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0) <= 0 )
    return 0;
  ++g_nRandCallCount;
  g_RandSeed = 214013 * g_RandSeed + 2531011;
  v7 = (CCBRoleState *->CalcMagicDamage()this->m_bNewRole[4], a2);
  if ( !v7 )
    return 0;
  a6[2] = a2;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 260;
  Obj = v8->CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DA350
char CCBAI::CastRandEnemyMagic(int a2, int a3)
{
  CCBRoleState *v4; // ecx
  char result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int IsForce1; // ebp
  int v9; // eax
  CCBRoleState *v10; // ecx
  int Obj; // eax
  int a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v4 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE2(v4->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v4->GetRoleField(a2, 18)
    || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
  {
    return 0;
  }
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  result = v6->IsRoleAlive(a2);
  if ( result )
  {
    RoleHP = (CCBRoleState *->GetRoleHP()this->m_bNewRole[4], a2);
    IsForce1 = RoleHP->IsForce1();
    if ( (CCBRoleState *->CalcMPRegen()this->m_bNewRole[4], IsForce1) > 0 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      (CCBRoleState *->CalcMPRegen()this->m_bNewRole[4], IsForce1);
      v9 = (CCBRoleState *->CalcMagicDamage()this->m_bNewRole[4], a2);
      if ( v9 )
      {
        v10 = (CCBRoleState *)this->m_bNewRole[4];
        LOBYTE(a6[10]) = 1;
        LOWORD(a6[4]) = 0;
        a6[0] = 260;
        a6[1] = v9;
        a6[2] = a2;
        a6[3] = -1;
        v10->GetRoleNum(a6);
        Obj = (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::GetThreadIndex, 0, 0, 0, a6);
        if ( a3 )
          *(_DWORD *)(a3 + 4) = Obj;
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
char CCBAI::CastRecoverSkill(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !HIBYTE(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 1);
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0);
  v7 = (CCBRoleState *->ProcessSkillEffect()this->m_bNewRole[4], a2);
  if ( !v7 )
    return 0;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  LOWORD(a6[4]) = 0;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  a6[0] = 262;
  a6[2] = a2;
  Obj = v8->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DA640
char CCBAI::CastRecoverBigSkill(int a2, int a3)
{
  CCBRoleState *v4; // ecx
  char result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int v8; // eax
  CCBRoleState *v9; // ecx
  int Obj; // eax
  int a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v4 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !HIBYTE(v4->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v4->GetRoleField(a2, 18)
    || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
  {
    return 0;
  }
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  result = v6->IsRoleAlive(a2);
  if ( result )
  {
    RoleHP = (CCBRoleState *->GetRoleHP()this->m_bNewRole[4], a2);
    (CCBRoleState *->CalcMagicDefense()this->m_bNewRole[4], RoleHP);
    v8 = (CCBRoleState *->ProcessSkillEffect()this->m_bNewRole[4], a2);
    if ( v8 )
    {
      v9 = (CCBRoleState *)this->m_bNewRole[4];
      a6[1] = v8;
      LOBYTE(a6[10]) = 1;
      LOWORD(a6[4]) = 0;
      a6[0] = 262;
      a6[2] = a2;
      a6[3] = -1;
      v9->GetRoleNum(a6);
      Obj = (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::PassCmdToThread, 0, 0, 0, a6);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = Obj;
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
char CCBAI::CastAttackSkill(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !HIBYTE(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  if ( (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0) <= 0 )
    return 0;
  ++g_nRandCallCount;
  g_RandSeed = 214013 * g_RandSeed + 2531011;
  (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a3, 0);
  v7 = (CCBRoleState *->ProcessItemEffect()this->m_bNewRole[4], a2);
  if ( !v7 )
    return 0;
  a6[2] = a2;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 262;
  Obj = v8->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DA900
char CCBAI::CastAttackBigSkill(int a2, int a3)
{
  CCBRoleState *v4; // ecx
  char result; // al
  CCBRoleState *v6; // ecx
  int RoleHP; // eax
  int IsForce1; // eax
  int v9; // eax
  CCBRoleState *v10; // ecx
  int Obj; // eax
  int a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v4 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !HIBYTE(v4->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v4->GetRoleField(a2, 18)
    || (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
  {
    return 0;
  }
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  result = v6->IsRoleAlive(a2);
  if ( result )
  {
    RoleHP = (CCBRoleState *->GetRoleHP()this->m_bNewRole[4], a2);
    IsForce1 = RoleHP->IsForce1();
    (CCBRoleState *->CalcMagicAttack()this->m_bNewRole[4], IsForce1);
    v9 = (CCBRoleState *->ProcessItemEffect()this->m_bNewRole[4], a2);
    if ( v9 )
    {
      v10 = (CCBRoleState *)this->m_bNewRole[4];
      a6[1] = v9;
      LOBYTE(a6[10]) = 1;
      LOWORD(a6[4]) = 0;
      a6[0] = 262;
      a6[2] = a2;
      a6[3] = -1;
      v10->GetRoleNum(a6);
      Obj = (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::PassCmdToThread, 0, 0, 0, a6);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = Obj;
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
char CCBAI::CastRecoverItem(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *v9; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( (CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) == 1 )
    return 0;
  v7 = (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a2, 1);
  v8 = sub_4F5D00((CCBRoleState *)this->m_bNewRole[4], a2, 0, v7);
  if ( !v8 )
    return 0;
  a6[3] = a3;
  a6[1] = v8;
  a6[2] = a2;
  LOBYTE(a6[10]) = 1;
  v9 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 261;
  Obj = v9->CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DAB70
char CCBAI::CastRecoverBigItem(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *v9; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE2(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( (CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) == 1 )
    return 0;
  v7 = (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a2, 1);
  v8 = sub_4F6000((CCBRoleState *)this->m_bNewRole[4], a2, 0, v7);
  if ( !v8 )
    return 0;
  a6[3] = a3;
  a6[1] = v8;
  a6[2] = a2;
  LOBYTE(a6[10]) = 1;
  v9 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 260;
  Obj = v9->CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DACA0
char CCBAI::CastAttackItem(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  int v8; // eax
  CCBSystem *v9; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !HIBYTE(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( (CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) == 1 )
    return 0;
  v7 = (CCBRoleState *->SetRoleField()this->m_bNewRole[4], a2, 1);
  v8 = sub_4F61D0((CCBRoleState *)this->m_bNewRole[4], a2, 0, v7);
  if ( !v8 )
    return 0;
  a6[3] = a3;
  a6[1] = v8;
  a6[2] = a2;
  LOBYTE(a6[10]) = 1;
  v9 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 262;
  Obj = v9->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DADD0
char CCBAI::CastAttackBigItem(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE1(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  v7 = sub_4F6370((CCBRoleState *)this->m_bNewRole[4], a2, *(_DWORD *)(a4 + 12), 0);
  if ( !v7 )
    return 0;
  a6[2] = a2;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 261;
  Obj = v8->CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DAF00
char CCBAI::CastBossPhysicalAttack(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !BYTE2(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  v7 = sub_4F6690((CCBRoleState *)this->m_bNewRole[4], a2, *(_DWORD *)(a4 + 12), 0);
  if ( !v7 )
    return 0;
  a6[2] = a2;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 260;
  Obj = v8->CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DB030
char CCBAI::CastReviveMagic(int a2, int a3, int a4)
{
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // ecx
  int v7; // eax
  CCBSystem *v8; // ecx
  int Obj; // eax
  _DWORD a6[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !HIBYTE(v5->m_Role[0].byMagicUseTime[4][223 * a2 + 4]) && !v5->GetRoleField(a2, 18) )
    return 0;
  if ( (CCBRoleState *->GetRoleField()this->m_bNewRole[4], a2, 19) )
    return 0;
  v6 = (CCBRoleState *)this->m_bNewRole[4];
  if ( !v6->m_Role[0].sModel[892 * a2 + 5] )
    return 0;
  if ( !v6->m_Role[0].sModel[892 * a3 + 5] )
    return 0;
  if ( !v6->IsRoleAlive(a2) )
    return 0;
  if ( !(CCBRoleState *->IsRoleAlive()this->m_bNewRole[4], a3) )
    return 0;
  v7 = sub_4F6860((CCBRoleState *)this->m_bNewRole[4], a2, *(_DWORD *)(a4 + 12), 0);
  if ( !v7 )
    return 0;
  a6[2] = a2;
  a6[1] = v7;
  a6[3] = a3;
  LOBYTE(a6[10]) = 1;
  v8 = (CCBSystem *)this->m_bNewRole[3];
  LOWORD(a6[4]) = 0;
  a6[0] = 262;
  Obj = v8->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, a6);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = Obj;
  return 1;
}

// 0x004DB160
char CCBAI::CastReviveSkill(int a2)
{
  int v4; // edi
  CCBRoleState *v5; // ecx
  int a6[11]; // [esp+Ch] [ebp-2Ch] BYREF

  if ( *(_DWORD *)(CCBRoleState *->InitUI()this->m_bNewRole[4], a2) != 739 )
    return 0;
  v4 = sub_4F2C30((_DWORD *)this->m_bNewRole[4], a2, 0);
  if ( v4 != sub_4F2C30((_DWORD *)this->m_bNewRole[4], a2, 1) )
    return 0;
  memset(a6, 0, sizeof(a6));
  v5 = (CCBRoleState *)this->m_bNewRole[4];
  LOWORD(a6[4]) = 0;
  LOBYTE(a6[10]) = 1;
  a6[0] = 261;
  a6[1] = 7709;
  a6[2] = a2;
  a6[3] = -1;
  v5->GetRoleNum(a6);
  (CCBSystem *->CreateObj()this->m_bNewRole[3], CCBSystem::GetSameThreadNum, 0, 0, 0, a6);
  CEffMgr::Init(*(CEffMgr **)(this->m_bNewRole[3] + 44), 559, 0, 0, 0, 0);
  return 1;
}

// 0x004DB270
// attributes: thunk
int CCBAI::CastCureSpecStateMagic()
{
  return CCBAI::CastCureSpecStateSkill();
}

// 0x004DB280
int CCBAI::CastCureSpecStateSkill()
{
  *(_DWORD *)&Buffer[900] = 1094713344;
  return 1094713344;
}

// 0x004DB290
// attributes: thunk
void CCBAI::CastCureSpecStateItem()
{
  CCBAI::HasVeryPunyFiveMagicRole();
}

// 0x004DB2A0
void CCBAI::HasVeryPunyFiveMagicRole()
{
  *(float *)&Buffer[896] = 12.0 + 12.0;
}

// 0x004DB2B0
// attributes: thunk
int CCBAI::CreateValueAutomation()
{
  return CCBAI::AddValueFunction();
}

// 0x004DB2C0
int CCBAI::AddValueFunction()
{
  *(_DWORD *)&Buffer[908] = 119;
  *(_DWORD *)&Buffer[912] = 314;
  *(_DWORD *)&Buffer[916] = 510;
  *(_DWORD *)&Buffer[920] = 707;
  return 707;
}

// 0x004DB300
// attributes: thunk
int CCBAI::AddValueItem()
{
  return CCBAI::DestroyValueAutomation();
}

// 0x004DB310
int CCBAI::DestroyValueAutomation()
{
  *(_DWORD *)&Buffer[924] = 519;
  *(_DWORD *)&Buffer[928] = 519;
  *(_DWORD *)&Buffer[932] = 519;
  *(_DWORD *)&Buffer[936] = 519;
  return 519;
}

// 0x004DB350
// attributes: thunk
int CCBAI::RunValueAutomation()
{
  return CCBAI::SpecAI();
}

// 0x004DB360
int CCBAI::SpecAI()
{
  *(_DWORD *)&Buffer[940] = 128;
  *(_DWORD *)&Buffer[944] = 323;
  *(_DWORD *)&Buffer[948] = 519;
  *(_DWORD *)&Buffer[952] = 716;
  return 716;
}
