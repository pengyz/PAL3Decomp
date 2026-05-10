#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBAI.h"

// Forward declarations for unnamed functions
int sub_4D6FF0(...);
int sub_4D7040(...);
int sub_4D7080(...);
int sub_4D70C0(...);
int sub_4D7120(...);
int sub_4D71E0(...);
int sub_4D7820(...);
int sub_4D7EF0(...);
int sub_4D8580(...);
int sub_4D86D0(...);
int sub_4D8760(...);
int sub_4D8AF0(...);
int sub_4D8F20(...);
int sub_4D9130(...);
int sub_4D9360(...);
int sub_4D9380(...);
int sub_4D93D0(...);
int sub_4D94F0(...);
int sub_4D9740(...);
int sub_4D9920(...);
int sub_4D9A70(...);
int sub_4D9BA0(...);
int sub_4D9D00(...);
int sub_4D9E20(...);
int sub_4D9F50(...);
int sub_4DA0A0(...);
int sub_4DA1D0(...);
int sub_4DA350(...);
int sub_4DA4F0(...);
int sub_4DA640(...);
int sub_4DA770(...);
int sub_4DA900(...);
int sub_4DAA40(...);
int sub_4DAB70(...);
int sub_4DACA0(...);
int sub_4DADD0(...);
int sub_4DAF00(...);
int sub_4DB030(...);
int sub_4DB160(...);
int sub_4DB280(...);
int sub_4DB2A0(...);
int sub_4DB2C0(...);
int sub_4DB310(...);
int sub_4DB360(...);
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
int sub_4D6FF0()
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
int sub_4D7040()
{
  dword_17A89D8 = 573;
  dword_17A89DC = 573;
  dword_17A89E0 = 573;
  dword_17A89E4 = 573;
  return 573;
}

// 0x004D7080
_DWORD * sub_4D7080(_DWORD *a2)
{
  memset(this, 0, 0xE50u);
  *((_DWORD *)this + 3) = a2;
  *((_DWORD *)this + 4) = a2[4];
  *((_DWORD *)this + 5) = *a2;
  return this;
}

// 0x004D70C0
char sub_4D70C0(int _this)
{
  memset((void *)(this + 1584), 0, 0x6E0u);
  memset((void *)(this + 3344), 0, 0xA0u);
  memset((void *)(this + 3504), 0, 0xA0u);
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
char sub_4D7120(int a2)
{
  char v3; // bl
  int v4; // eax
  char result; // al

  v3 = 0;
  if ( (int)a2->SetRoleField(0) > 0 )
  {
    v4 = *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 3) + 20) + 4 * a2 + 24);
    *(float *)(v4 + 6632) = *(float *)(v4 + 6636);
  }
  if ( (unsigned __int8)a2->GetRoleField(18) )
  {
    if ( a2->GetRoleAttr() != 5 )
      return sub_4D8580(a2);
    return v3;
  }
  else
  {
    switch ( a2->GetRoleAttr() )
    {
      case 1:
      case 2:
        result = a2->HandleEnemyAction();
        break;
      case 3:
        result = a2->HandleEnemyWell();
        break;
      case 4:
        result = a2->HandleEnemyWeak();
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
char sub_4D71E0(int a2)
{
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // edi
  int v8; // [esp+38h] [ebp-Ch]
  int *i; // [esp+3Ch] [ebp-8h]
  int v10; // [esp+40h] [ebp-4h]

  if ( (unsigned __int8)a2->CastReviveSkill() == 1 )
    return 1;
  v4 = g_RandSeed;
  v5 = 0;
  v10 = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v4 = 214013 * v4 + 2531011;
    g_RandSeed = v4;
    if ( ((v4 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( *(_BYTE *)(*((_DWORD *)this + 4) + v5 + 577) )
        break;
    }
    v5 += 892;
    v6 = ++v10;
    if ( v5 >= 9812 )
      goto LABEL_9;
  }
  v6 = v10;
LABEL_9:
  if ( v6 == 10 )
  {
    v10 = 0;
    v6 = 0;
LABEL_12:
    v7 = 892 * v6;
    v8 = 892 * v6;
    for ( i = this + 40 * v6 + 412; ; i += 40 )
    {
      if ( *(_BYTE *)(v7 + *((_DWORD *)this + 4) + 577) )
      {
        if ( !(unsigned __int8)v6->IsRoleAlive() || *(_BYTE *)(v7 + *((_DWORD *)this + 4) + 583) == 1 )
        {
          v6 = v10;
        }
        else
        {
          if ( (unsigned int)v7 < 0x116C
            || (unsigned __int8)a2->GetRoleField(19)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7)
            || (unsigned __int8)a2->GetRoleField(18)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
          {
            if ( i[8] < 100 && (unsigned __int8)a2->DemandChecker(v10, i + 8) == 1 )
              return 1;
          }
          if ( (int)*((_DWORD *)this + 840) < 100 && (unsigned __int8)a2->CastRecoverMagic(this + 840) )
            return 1;
          if ( v7 >= 4460 )
          {
            if ( v7 < 9812 && *(i - 12) < 100 && (unsigned __int8)a2->CastNormalAttack(v10, i - 12) )
              return 1;
            if ( v7 < 9812 && *i < 100 )
            {
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x3FF) < (int)512.0 )
              {
                if ( (unsigned __int8)a2->CastAttackBigItem(v10, i) )
                  return 1;
              }
            }
          }
          if ( (int)*((_DWORD *)this + 896) < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)378.88 )
            {
              if ( (unsigned __int8)a2->CastAttackMagic(this + 896) )
                return 1;
            }
            if ( (unsigned __int8)a2->GetRoleType() )
            {
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
              {
                if ( a2->Thunk_GetValue((int)(this + 896)) )
                  return 1;
              }
            }
          }
          if ( v8 >= 0 )
          {
            if ( v8 >= 4460 )
            {
              if ( v8 < 9812 )
              {
                ++g_nRandCallCount;
                g_RandSeed = 214013 * g_RandSeed + 2531011;
                if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
                {
                  if ( *(i - 12) < 100 && (unsigned __int8)a2->CastNormalAttack(v10, 0) )
                    return 1;
                  ++g_nRandCallCount;
                  g_RandSeed = 214013 * g_RandSeed + 2531011;
                  if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
                  {
                    if ( (unsigned __int8)a2->CastAttackBigMagic(v10) )
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
                && ((unsigned __int8)a2->CastAttackMagic(0)
                 || (unsigned __int8)a2->CastRecoverBigMagic(v10, 0)) )
              {
                return 1;
              }
            }
          }
          if ( (unsigned int)v8 < 0x116C
            || (unsigned __int8)a2->GetRoleField(19)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7)
            || (unsigned __int8)a2->GetRoleField(18)
            && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
          {
            if ( (unsigned __int8)a2->DemandChecker(v10, 0) )
              return 1;
          }
          v6 = v10;
          v7 = v8;
        }
      }
      v7 += 892;
      v10 = ++v6;
      v8 = v7;
      if ( v7 >= 9812 )
        return 0;
    }
  }
  if ( v6 < 11 )
    goto LABEL_12;
  return 0;
}

// 0x004D7820
char sub_4D7820(int a2)
{
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // edx
  int v8; // edx
  int v9; // edi
  int *v11; // [esp+40h] [ebp-Ch]
  int v12; // [esp+44h] [ebp-8h]
  int v13; // [esp+48h] [ebp-4h]

  v3 = g_RandSeed;
  v4 = 0;
  v13 = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v3 = 214013 * v3 + 2531011;
    g_RandSeed = v3;
    if ( ((v3 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( *(_BYTE *)(*((_DWORD *)this + 4) + v4 + 577) )
        break;
    }
    v4 += 892;
    v5 = ++v13;
    if ( v4 >= 9812 )
      goto LABEL_7;
  }
  v5 = v13;
LABEL_7:
  if ( v5 == 10 )
  {
    v13 = 0;
    v5 = 0;
LABEL_10:
    v6 = 892 * v5;
    v12 = 892 * v5;
    v11 = this + 40 * v5 + 400;
    while ( !*(_BYTE *)(v6 + *((_DWORD *)this + 4) + 577) )
    {
LABEL_75:
      v6 += 892;
      v13 = ++v5;
      v12 = v6;
      v11 += 40;
      if ( v6 >= 9812 )
        return 0;
    }
    if ( !(unsigned __int8)v5->IsRoleAlive() || *(_BYTE *)(v6 + *((_DWORD *)this + 4) + 583) == 1 )
    {
LABEL_74:
      v5 = v13;
      goto LABEL_75;
    }
    if ( (unsigned int)v6 < 0x116C
      || (unsigned __int8)a2->GetRoleField(19)
      && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7)
      || (unsigned __int8)a2->GetRoleField(18)
      && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
    {
      if ( v11[20] < 100 && (unsigned __int8)a2->DemandChecker(v13, v11 + 20) )
        return 1;
    }
    if ( (int)*((_DWORD *)this + 840) < 100 && (unsigned __int8)a2->CastRecoverMagic(this + 840) )
      return 1;
    v7 = v13;
    if ( v13 == a2 && *v11 < 100 )
    {
      if ( (unsigned __int8)a2->CastNormalAttack(v13, v11) )
        return 1;
      v7 = v13;
    }
    if ( v6 >= 4460 )
    {
      if ( v6 < 9812 && *v11 < 100 )
      {
        if ( (unsigned __int8)a2->CastNormalAttack(v7, v11) )
          return 1;
        v7 = v13;
      }
      if ( v6 < 9812 && v11[12] < 100 )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        if ( ((g_RandSeed >> 16) & 0x3FF) < (int)512.0 )
        {
          if ( (unsigned __int8)a2->CastAttackBigItem(v7, v11 + 12) )
            return 1;
        }
      }
    }
    if ( (int)*((_DWORD *)this + 896) < 100 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)256.0 )
      {
        if ( (unsigned __int8)a2->CastAttackMagic(this + 896) )
          return 1;
      }
      if ( (unsigned __int8)a2->GetRoleType() )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        if ( ((g_RandSeed >> 16) & 0x3FF) < (int)307.19998 )
        {
          if ( a2->Thunk_GetValue((int)(this + 896)) )
            return 1;
        }
      }
    }
    v8 = v12;
    if ( v12 < 0 )
      goto LABEL_82;
    if ( v12 >= 4460
      || v11[28] >= 100
      || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x3FF) >= (int)716.79999) )
    {
      v9 = v13;
    }
    else
    {
      v9 = v13;
      if ( (unsigned __int8)a2->CastRecoverBigMagic(v13, v11 + 28) )
        return 1;
      v8 = v12;
    }
    if ( v8 < 0 )
      goto LABEL_82;
    if ( v8 < 4460 && v11[32] < 100 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)716.79999 && (unsigned __int8)a2->DemandChecker(v9, v11 + 32) )
        return 1;
      v8 = v12;
    }
    if ( v8 < 4460 && v11[24] < 100 )
    {
      if ( (unsigned __int8)a2->CastRecoverBigMagic(v9, v11 + 24) )
        return 1;
      v8 = v12;
    }
    if ( v8 < 4460 && v11[24] < 100 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)256.0 && (unsigned __int8)a2->CastRecoverBigMagic(v9, v11 + 24) )
        return 1;
      v8 = v12;
    }
    if ( v8 < 4460 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)102.39999 )
      {
        if ( (unsigned __int8)a2->CastAttackMagic(0) || (unsigned __int8)a2->CastRecoverBigMagic(v9, 0) )
          return 1;
        v8 = v12;
      }
    }
    if ( v8 >= 4460 )
    {
LABEL_82:
      if ( !(unsigned __int8)a2->GetRoleField(19)
        || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 <= 7) )
      {
LABEL_73:
        v6 = v12;
        goto LABEL_74;
      }
      v9 = v13;
    }
    if ( (unsigned __int8)a2->DemandChecker(v9, 0) )
      return 1;
    goto LABEL_73;
  }
  if ( v5 < 11 )
    goto LABEL_10;
  return 0;
}

// 0x004D7EF0
char sub_4D7EF0(int a2)
{
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // edx
  int v8; // edx
  int v9; // edi
  int v11; // [esp+40h] [ebp-Ch]
  int *v12; // [esp+44h] [ebp-8h]
  int v13; // [esp+48h] [ebp-4h]

  v3 = g_RandSeed;
  v4 = 0;
  v13 = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v3 = 214013 * v3 + 2531011;
    g_RandSeed = v3;
    if ( ((v3 >> 16) & 0x7FFF) % 3 == 1 )
    {
      if ( *(_BYTE *)(*((_DWORD *)this + 4) + v4 + 577) )
        break;
    }
    v4 += 892;
    v5 = ++v13;
    if ( v4 >= 9812 )
      goto LABEL_7;
  }
  v5 = v13;
LABEL_7:
  if ( v5 == 10 )
  {
    v13 = 0;
    v5 = 0;
  }
  else if ( v5 >= 11 )
  {
    return 0;
  }
  v6 = 892 * v5;
  v11 = 892 * v5;
  v12 = this + 40 * v5 + 400;
  while ( !*(_BYTE *)(v6 + *((_DWORD *)this + 4) + 577) )
  {
LABEL_76:
    v6 += 892;
    v13 = ++v5;
    v11 = v6;
    v12 += 40;
    if ( v6 >= 9812 )
      return 0;
  }
  if ( !(unsigned __int8)v5->IsRoleAlive() || *(_BYTE *)(v6 + *((_DWORD *)this + 4) + 583) == 1 )
  {
    v5 = v13;
    goto LABEL_76;
  }
  if ( (unsigned int)v6 >= 0x116C
    && (!(unsigned __int8)a2->GetRoleField(19)
     || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 <= 7)
     || v12[20] >= 100)
    || !(unsigned __int8)a2->DemandChecker(v13, v12 + 20) )
  {
    if ( (int)*((_DWORD *)this + 840) >= 100 || !(unsigned __int8)a2->CastRecoverMagic(this + 840) )
    {
      v7 = v13;
      if ( v13 == a2 && *v12 < 100 )
      {
        if ( (unsigned __int8)a2->CastNormalAttack(v13, v12) || (unsigned __int8)a2->CastRecoverMagic(v12) )
          return 1;
        v7 = v13;
      }
      if ( v6 < 4460 )
        goto LABEL_81;
      if ( v6 < 9812 && *v12 < 100 )
      {
        if ( (unsigned __int8)a2->CastNormalAttack(v7, v12) )
          return 1;
        v7 = v13;
      }
      if ( v6 >= 9812
        || v12[12] >= 100
        || (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x3FF) >= (int)512.0)
        || !(unsigned __int8)a2->CastAttackBigItem(v7, v12 + 12) )
      {
LABEL_81:
        if ( (int)*((_DWORD *)this + 896) >= 100
          || ((++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011,
                                   ((g_RandSeed >> 16) & 0x3FF) >= (int)256.0)
           || !(unsigned __int8)a2->CastAttackMagic(this + 896))
          && (!(unsigned __int8)a2->GetRoleType()
           || (++g_nRandCallCount,
               g_RandSeed = 214013 * g_RandSeed + 2531011,
               ((g_RandSeed >> 16) & 0x3FF) >= (int)307.19998)
           || !a2->Thunk_GetValue((int)(this + 896))) )
        {
          v8 = v11;
          if ( v11 < 0 )
            goto LABEL_82;
          if ( v11 >= 4460
            || v12[28] >= 100
            || (++g_nRandCallCount,
                g_RandSeed = 214013 * g_RandSeed + 2531011,
                ((g_RandSeed >> 16) & 0x3FF) >= (int)716.79999) )
          {
            v9 = v13;
          }
          else
          {
            v9 = v13;
            if ( (unsigned __int8)a2->CastRecoverBigMagic(v13, v12 + 28) )
              return 1;
            v8 = v11;
          }
          if ( v8 < 0 )
            goto LABEL_82;
          if ( v8 < 4460 && v12[32] < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)716.79999
              && (unsigned __int8)a2->DemandChecker(v9, v12 + 32) )
            {
              return 1;
            }
            v8 = v11;
          }
          if ( v8 < 4460 && v12[24] < 100 )
          {
            if ( (unsigned __int8)a2->CastRecoverBigMagic(v9, v12 + 24) )
              return 1;
            v8 = v11;
          }
          if ( v8 < 4460 && v12[24] < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)256.0
              && (unsigned __int8)a2->CastRecoverBigMagic(v9, v12 + 24) )
            {
              return 1;
            }
            v8 = v11;
          }
          if ( v8 < 4460 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)102.39999 )
            {
              if ( (unsigned __int8)a2->CastAttackMagic(0)
                || (unsigned __int8)a2->CastRecoverBigMagic(v9, 0) )
              {
                return 1;
              }
              v8 = v11;
            }
          }
          if ( v8 < 4460 )
          {
LABEL_71:
            if ( (unsigned __int8)a2->DemandChecker(v9, 0) )
              return 1;
          }
          else
          {
LABEL_82:
            if ( (unsigned __int8)a2->GetRoleField(19) )
            {
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7 )
              {
                v9 = v13;
                goto LABEL_71;
              }
            }
          }
          v5 = v13;
          v6 = v11;
          goto LABEL_76;
        }
      }
    }
  }
  return 1;
}

// 0x004D86D0
char sub_4D86D0(int a2)
{
  int v3; // eax
  char result; // al
  int v5; // [esp-4h] [ebp-10h]

  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 577)
    || !(unsigned __int8)a2->IsRoleAlive()
    || !*(_DWORD *)(a2->InitUI() + 36) )
  {
    return 0;
  }
  v5 = a2;
  v3 = *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 3) + 20) + 4 * a2 + 24);
  *(float *)(v3 + 6632) = *(float *)(v3 + 6636);
  if ( *(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1388) )
  {
    result = a2->HandleFriendAction();
    if ( result )
      return result;
    v5 = a2;
  }
  return v5->HandleFriendNegative();
}

// 0x004D8760
char sub_4D8760(int a2)
{
  int v3; // ebx
  int v4; // eax
  bool v5; // cc
  int v7; // [esp+10h] [ebp-8h]
  int *i; // [esp+14h] [ebp-4h]

  v3 = 0;
  v4 = 0;
  v7 = 0;
  for ( i = this + 400; ; i += 40 )
  {
    if ( *(_BYTE *)(v4 + *((_DWORD *)this + 4) + 577) )
    {
      if ( (unsigned __int8)a2->GetRoleField(18) )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        switch ( (g_RandSeed >> 16) & 0x3F )
        {
          case 0:
            if ( !(unsigned __int8)a2->CastRecoverBigItem(v3, 0) )
              goto LABEL_46;
            return 1;
          case 1:
            if ( !(unsigned __int8)a2->CastRecoverItem(v3, 0) )
              goto LABEL_46;
            return 1;
          case 2:
            if ( (unsigned __int8)a2->CastAttackItem(v3, 0) != 1 )
              goto LABEL_46;
            return 1;
          case 3:
            if ( !(unsigned __int8)a2->CastRecoverMagic(0) )
              goto LABEL_46;
            return 1;
          case 4:
            if ( !(unsigned __int8)a2->CastBFAMagic(0) )
              goto LABEL_46;
            return 1;
          case 5:
            if ( !(unsigned __int8)a2->CastRecoverBigSkill(0) )
              goto LABEL_46;
            return 1;
          case 6:
            if ( !(unsigned __int8)a2->CastNormalAttack(v3, 0) )
              goto LABEL_46;
            return 1;
          case 7:
            if ( !(unsigned __int8)a2->CastSpecifyMagic(v3, 0) )
              goto LABEL_46;
            return 1;
          case 8:
            if ( !(unsigned __int8)a2->CastRecoverSkill(v3, 0) )
              goto LABEL_46;
            return 1;
          default:
            goto LABEL_46;
        }
      }
      if ( (unsigned int)v7 < 0x116C
        && i[4] < 100
        && ((unsigned __int8)a2->CastRecoverBigItem(v3, i + 4)
         || (unsigned __int8)a2->CastRecoverItem(v3, i + 4)
         || (unsigned __int8)a2->CastAttackItem(v3, i + 4) == 1) )
      {
        break;
      }
      if ( (unsigned __int8)v3->IsRoleAlive() && *(_BYTE *)(v3->InitUI() + 880) != 1 )
      {
        if ( *((_DWORD *)this + 880) < 100
          && ((unsigned __int8)a2->CastRecoverMagic(this + 880)
           || (unsigned __int8)a2->CastBFAMagic(this + 880)
           || (unsigned __int8)a2->CastRecoverBigSkill(this + 880)) )
        {
          break;
        }
        if ( v7 >= 0 )
        {
          if ( v7 < 4460
            && *i < 50
            && ((unsigned __int8)a2->CastNormalAttack(v3, i)
             || (unsigned __int8)a2->CastSpecifyMagic(v3, i)
             || (unsigned __int8)a2->CastRecoverSkill(v3, i)) )
          {
            break;
          }
          if ( v7 < 4460 && i[12] < 100 )
          {
            ++g_nRandCallCount;
            g_RandSeed = 214013 * g_RandSeed + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FF) < (int)512.0
              && ((unsigned __int8)a2->CastAttackBigItem(v3, i + 12)
               || (unsigned __int8)a2->CastBossPhysicalAttack(v3, i + 12)
               || (unsigned __int8)a2->CastReviveMagic(v3, i + 12)) )
            {
              break;
            }
          }
        }
      }
    }
LABEL_46:
    v4 = v7 + 892;
    ++v3;
    v5 = v7 + 892 < 9812;
    v7 += 892;
    if ( !v5 )
      return 0;
  }
  return 1;
}

// 0x004D8AF0
char sub_4D8AF0(int a2)
{
  int v4; // edi
  int v5; // ebx
  int *v6; // ebx
  char result; // al
  int v8; // edi
  int v9; // ebx
  char v10; // al
  int v11; // [esp+10h] [ebp-4h]
  int *i; // [esp+18h] [ebp+4h]
  int v13; // [esp+18h] [ebp+4h]

  if ( !(unsigned __int8)a2->GetRoleField(18) )
  {
    v4 = 0;
    v5 = 0;
    v11 = 0;
    for ( i = this + 420; ; i += 40 )
    {
      if ( !*(_BYTE *)(v5 + *((_DWORD *)this + 4) + 577)
        || !(unsigned __int8)v4->IsRoleAlive()
        || *(_BYTE *)(v4->InitUI() + 880) )
      {
        goto LABEL_30;
      }
      if ( *((_DWORD *)this + 856) < 100
        && ((unsigned __int8)a2->CastAttackMagic(this + 856) == 1
         || (unsigned __int8)a2->CastRandEnemyMagic(this + 856) == 1
         || (unsigned __int8)a2->CastAttackBigSkill(this + 856) == 1) )
      {
        return 1;
      }
      if ( v11 < 4460 )
      {
        v6 = i;
      }
      else
      {
        v6 = i;
        if ( v11 < 9812 && *i < 100 )
        {
LABEL_17:
          if ( (unsigned __int8)a2->DemandChecker(v4, v6) == 1
            || (unsigned __int8)a2->CastRecoverBigMagic(v4, v6) == 1
            || (unsigned __int8)a2->CastBFAAttackMagic(v4, v6) == 1
            || (unsigned __int8)a2->CastAttackSkill(v4, v6) == 1 )
          {
            return 1;
          }
          goto LABEL_21;
        }
      }
      if ( (unsigned __int8)a2->GetRoleField(19) )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        if ( ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7 )
          goto LABEL_17;
      }
LABEL_21:
      if ( v11 >= 4460 && v11 < 9812
        || (unsigned __int8)a2->GetRoleField(19)
        && (++g_nRandCallCount, g_RandSeed = 214013 * g_RandSeed + 2531011, ((g_RandSeed >> 16) & 0x7FFF) % 10 > 7) )
      {
        if ( (unsigned __int8)a2->DemandChecker(v4, 0) == 1
          || (unsigned __int8)a2->CastRecoverBigMagic(v4, 0) == 1
          || (unsigned __int8)a2->CastBFAAttackMagic(v4, 0) == 1
          || (unsigned __int8)a2->CastAttackSkill(v4, 0) == 1 )
        {
          return 1;
        }
      }
      v5 = v11;
LABEL_30:
      v5 += 892;
      ++v4;
      v11 = v5;
      if ( v5 >= 9812 )
        return 0;
    }
  }
  v8 = g_RandSeed;
  v13 = 0;
  while ( 1 )
  {
    ++g_nRandCallCount;
    v8 = 214013 * v8 + 2531011;
    g_RandSeed = v8;
    v9 = ((v8 >> 16) & 0x7FFF) % 11;
    if ( *(_BYTE *)(*((_DWORD *)this + 4) + 892 * v9 + 577) )
      break;
LABEL_37:
    if ( ++v13 >= 1024 )
      goto LABEL_38;
  }
  if ( !*(_BYTE *)(CCBRoleState::InitUI(((v8 >> 16) & 0x7FFF) % 11) + 880) || v9 == a2 )
  {
    v8 = g_RandSeed;
    goto LABEL_37;
  }
LABEL_38:
  if ( *(_BYTE *)(*((_DWORD *)this + 4) + 892 * v9 + 577) && !*(_BYTE *)(v9->InitUI() + 880) )
  {
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    switch ( ((g_RandSeed >> 16) & 0x7FFF) % 11 )
    {
      case 0:
        v10 = a2->CastAttackMagic(0);
        return v10 == 1;
      case 1:
        v10 = a2->CastRandEnemyMagic(0);
        return v10 == 1;
      case 2:
        result = a2->CastAttackBigSkill(0);
        goto LABEL_49;
      case 3:
      case 10:
        v10 = a2->DemandChecker(v9, 0);
        return v10 == 1;
      case 4:
      case 7:
        result = a2->CastRecoverBigMagic(v9, 0);
        if ( result != 1 )
          return 0;
        return result;
      case 5:
      case 8:
        result = a2->CastBFAAttackMagic(v9, 0);
        if ( result != 1 )
          return 0;
        return result;
      case 6:
      case 9:
        result = a2->CastAttackSkill(v9, 0);
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
char sub_4D8F20(int a2, char a3)
{
  int v4; // ebx
  int v5; // edi
  double v6; // st7
  int v8; // ebx
  int v9; // edi
  int v11; // ecx
  _DWORD *v12; // edx
  _DWORD v13[11]; // [esp+Ch] [ebp-44h] BYREF
  _DWORD *v14; // [esp+38h] [ebp-18h]
  int v15; // [esp+3Ch] [ebp-14h]
  int v16; // [esp+40h] [ebp-10h]
  float v17; // [esp+44h] [ebp-Ch]
  int v18; // [esp+48h] [ebp-8h]
  int v19; // [esp+4Ch] [ebp-4h]
  char v20; // [esp+5Bh] [ebp+Bh]

  v4 = 0;
  v14 = this;
  v17 = 1.1;
  v19 = -1;
  v18 = 0;
  v5 = 0;
  do
  {
    if ( v4 >= 4460 )
    {
      if ( *(_BYTE *)(v4 + *((_DWORD *)this + 4) + 577) )
      {
        if ( (unsigned __int8)v5->IsRoleAlive() )
        {
          ++v18;
          *(float *)&v15 = (float)(int)v5->SetRoleField(0);
          v16 = v5->SetRoleField(1);
          v6 = *(float *)&v15 / (double)v16;
          if ( v6 < v17 )
          {
            v17 = v6;
            v19 = v5;
          }
        }
      }
    }
    v4 += 892;
    ++v5;
  }
  while ( v4 < 9812 );
  if ( v18 <= 0 )
    return 0;
  if ( v19 == -1 )
  {
    v8 = 0;
    v9 = 0;
    while ( 1 )
    {
      if ( v9 >= 4460 )
      {
        if ( *(_BYTE *)(v9 + *((_DWORD *)this + 4) + 577) )
        {
          if ( (unsigned __int8)v8->IsRoleAlive() )
          {
            v15 = 100 / v18;
            if ( 100 / v18 > 0 )
            {
              *(float *)&v15 = (double)v15 * 10.24;
              v16 = (int)*(float *)&v15;
              ++g_nRandCallCount;
              g_RandSeed = 214013 * g_RandSeed + 2531011;
              if ( ((g_RandSeed >> 16) & 0x3FF) < v16 )
                break;
            }
          }
        }
      }
      v9 += 892;
      ++v8;
      if ( v9 >= 9812 )
        return 0;
    }
    v19 = v8;
    if ( v8 != -1 )
      goto LABEL_21;
    return 0;
  }
  else
  {
LABEL_21:
    *(_BYTE *)(a2->InitUI() + 832) = 1;
    v20 = a2->DemandChecker(v19, 0);
    *(_BYTE *)(a2->InitUI() + 832) = 0;
    if ( a3 )
    {
      memset(v13, 0, sizeof(v13));
      LOWORD(v13[4]) = 0;
      v13[3] = v19;
      v11 = *((_DWORD *)this + 3);
      v12 = v14;
      LOBYTE(v13[10]) = 1;
      v13[0] = 259;
      v13[2] = a2;
      qmemcpy((void *)(v11 + 52 * a2 + 90264), v13, 0x2Cu);
      *((_BYTE *)v12 + a2) = 0;
    }
    return v20;
  }
}

// 0x004D9130
char sub_4D9130(int a2, int a3)
{
  int (__stdcall *v4)(int); // eax
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
      result = a3->GetRoleAI();
      if ( !result )
        goto LABEL_11;
LABEL_5:
      switch ( *(_DWORD *)a3 )
      {
        case 0x103:
          if ( (unsigned __int8)a3->InitRoleSpecEquipAttrib() || *((_BYTE *)this + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            *(_DWORD *)(a3 + 12) = CCBRoleState::CalcMPCost(2);
            *(_BYTE *)(a3 + 17) = 0;
            a3->CalcHealAmount();
          }
          v4 = CCBSystem::IsRoleWaitForFlee;
          goto LABEL_33;
        case 0x104:
          if ( (unsigned __int8)a3->InitRoleSpecEquipAttrib() || *((_BYTE *)this + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            if ( (unsigned __int8)sub_4F6A80(*(_DWORD *)(a3 + 4)) )
              v7 = CCBRoleState::CalcMPCost(2);
            else
              v7 = CCBRoleState::CalcMPCost(1);
            *(_DWORD *)(a3 + 12) = v7;
            *(_BYTE *)(a3 + 17) = 0;
            a3->GetRoleNum();
          }
          v4 = CCBSystem::GetThreadIndex;
          goto LABEL_33;
        case 0x105:
          if ( (unsigned __int8)a3->InitRoleSpecEquipAttrib() || *((_BYTE *)this + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            if ( (unsigned __int8)sub_4F6A80(*(_DWORD *)(a3 + 4)) )
              v6 = CCBRoleState::CalcMPCost(2);
            else
              v6 = CCBRoleState::CalcMPCost(1);
            *(_DWORD *)(a3 + 12) = v6;
            *(_BYTE *)(a3 + 17) = 0;
            a3->GetRoleNum();
          }
          v4 = CCBSystem::GetSameThreadNum;
          goto LABEL_33;
        case 0x106:
          if ( (unsigned __int8)a3->InitRoleSpecEquipAttrib() || *((_BYTE *)this + a2) )
          {
            *(_DWORD *)(a3 + 29) = 0;
            *(_DWORD *)(a3 + 33) = 0;
            *(_WORD *)(a3 + 37) = 0;
            *(_BYTE *)(a3 + 39) = 0;
            if ( (unsigned __int8)sub_4F6BB0(*(_DWORD *)(a3 + 4)) )
              v8 = CCBRoleState::CalcMPCost(2);
            else
              v8 = CCBRoleState::CalcMPCost(1);
            *(_DWORD *)(a3 + 12) = v8;
            *(_BYTE *)(a3 + 17) = 0;
            a3->GetRoleNum();
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
      v4->CreateObj(0, 0, 0, a3);
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
void * sub_4D9360()
{
  *this = &unk_1010101;
  *((_DWORD *)this + 1) = &unk_1010101;
  *((_WORD *)this + 4) = (unsigned __int16)&unk_1010101;
  *((_BYTE *)this + 10) = (unsigned __int8)&unk_1010101;
  return &unk_1010101;
}

// 0x004D9380
_DWORD * sub_4D9380()
{
  _DWORD *v1; // eax
  int v2; // esi
  int v3; // edx
  _DWORD *result; // eax
  int v5; // ecx

  v1 = this + 396;
  v2 = 11;
  do
  {
    v3 = 10;
    do
    {
      *v1 = 100;
      v1 += 4;
      --v3;
    }
    while ( v3 );
    --v2;
  }
  while ( v2 );
  result = this + 876;
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
int sub_4D93D0()
{
  _BYTE *v2; // esi
  int v3; // ebp
  int i; // edi
  _DWORD *v5; // esi
  int v6; // ebp
  int result; // eax
  int v8; // edi
  int v9; // [esp+10h] [ebp-8h]
  _DWORD *v10; // [esp+14h] [ebp-4h]

  v2 = this + 402;
  v9 = 0;
  v3 = 99;
  v10 = this + 402;
  do
  {
    if ( *(_BYTE *)(v9 + *((_DWORD *)this + 4) + 577) )
    {
      for ( i = 1; i < 10; ++i )
      {
        if ( *((_DWORD *)v2 - 1) )
        {
          if ( (unsigned __int8)sub_515CE0(*((_DWORD *)v2 - 1)) )
          {
            *v2 = 1;
            *(this + 4 * i + 4 * v3) = 100;
          }
          else
          {
            *((_DWORD *)v2 - 1) = 0;
            *v2 = 0;
          }
        }
        v2 += 16;
      }
    }
    v3 += 10;
    v9 += 892;
    v2 = v10 + 40;
    v10 += 40;
  }
  while ( v3 < 209 );
  v5 = this + 842;
  v6 = 9;
  do
  {
    result = *(v5 - 1);
    v8 = v5[39];
    if ( result )
    {
      result = sub_515CE0(*(v5 - 1));
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
      result = sub_515CE0(v8);
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
char sub_4D94F0(int _this)
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
char sub_4D9740(unsigned int a2, int a3, int a4)
{
  unsigned int v5; // eax
  int v6; // ecx
  unsigned int v7; // edi
  int v9; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  v5 = a2;
  if ( a3 == a2 )
    return 0;
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1384) )
  {
    if ( !(unsigned __int8)a2->GetRoleField(18) && !(unsigned __int8)a2->GetRoleField(19) )
      return 0;
    v5 = a2;
  }
  v6 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v6 + 577)
    || !*(_BYTE *)(v6 + 892 * a3 + 577)
    || !(unsigned __int8)v5->IsRoleAlive()
    || !(unsigned __int8)a3->IsRoleAlive()
    || (unsigned __int8)a3->GetRoleField(23) == 1 )
  {
    return 0;
  }
  if ( (unsigned __int8)a3->GetRoleField(21) == 1
    && (unsigned __int8)a3->GetRoleField(20) == 1 )
  {
    v7 = a2;
    if ( a2 <= 4 )
      return 0;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    if ( ((g_RandSeed >> 16) & 0x3FF) < (int)716.79999 )
      return 0;
  }
  else
  {
    v7 = a2;
  }
  if ( !(unsigned __int8)CCBStageRole::ForceEndTaskByPFN(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 3) + 20) + 4 * a3 + 24))
    || !(unsigned __int8)v7->CalSneakAttack(a3) )
  {
    return 0;
  }
  LOBYTE(v10[10]) = 1;
  v10[0] = 259;
  v10[2] = v7;
  v10[3] = a3;
  LOWORD(v10[4]) = 0;
  v10->CalcHealAmount();
  v9 = CCBSystem::CreateObj(CCBSystem::IsRoleWaitForFlee, 0, 0, 0, v10);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v9;
  return 1;
}

// 0x004D9920
char sub_4D9920(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD v11[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(v11, 0, sizeof(v11));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1385) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  v6 = a3->SetRoleField(1);
  v7 = a3->SetRoleField(0);
  v8 = a2->ProcessAttackResult(0, v6 - v7);
  if ( !v8 )
    return 0;
  v11[1] = v8;
  v11[3] = a3;
  LOBYTE(v11[10]) = 1;
  LOWORD(v11[4]) = 0;
  v11[0] = 261;
  v11[2] = a2;
  v9 = CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v11);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v9;
  return 1;
}

// 0x004D9A70
char sub_4D9A70(int a2, int a3)
{
  char result; // al
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v9[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v9, 0, sizeof(v9));
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 1385) && !(unsigned __int8)a2->GetRoleField(18)
    || (unsigned __int8)a2->GetRoleField(19) )
  {
    return 0;
  }
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 577) )
    return 0;
  result = a2->IsRoleAlive();
  if ( result )
  {
    v5 = a2->GetRoleHP();
    v6 = v5->CalcMagicDefense(0);
    v7 = a2->ProcessAttackResult(1, v6);
    if ( v7 )
    {
      v9[1] = v7;
      LOBYTE(v9[10]) = 1;
      LOWORD(v9[4]) = 0;
      v9[0] = 261;
      v9[2] = a2;
      v9[3] = -1;
      v9->GetRoleNum();
      v8 = CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v9);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = v8;
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
char sub_4D9BA0(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD v11[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v11, 0, sizeof(v11));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1385) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  if ( (int)a3->SetRoleField(0) <= 0 )
    return 0;
  v6 = a3->SetRoleField(0);
  v7 = a2->ProcessMagicResult(0, v6);
  if ( !v7 )
    return 0;
  v8 = sub_4FB6B0(v7);
  v11[2] = a2;
  v11[1] = v8;
  v11[3] = a3;
  LOBYTE(v11[10]) = 1;
  LOWORD(v11[4]) = 0;
  v11[0] = 261;
  v9 = CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v11);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v9;
  return 1;
}

// 0x004D9D00
char sub_4D9D00(int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // edx
  _DWORD v8[11]; // [esp+10h] [ebp-2Ch] BYREF

  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 1385) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  a2->GetRoleHP();
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  v3 = a2->GetRoleHP();
  v4 = v3->IsForce1();
  v5 = v4->CalcMagicAttack(0);
  if ( !v5 )
    return 0;
  v6 = a2->ProcessMagicResult(1, v5);
  if ( !v6 )
    return 0;
  memset(v8, 0, sizeof(v8));
  LOBYTE(v8[10]) = 1;
  LOWORD(v8[4]) = 0;
  v8[0] = 261;
  v8[1] = v6;
  v8[2] = a2;
  v8[3] = -1;
  v8->GetRoleNum();
  CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v8);
  return 1;
}

// 0x004D9E20
char sub_4D9E20(int a2, int a3)
{
  int v4; // ecx
  int v5; // eax
  _DWORD v7[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v7, 0, sizeof(v7));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1385) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v4 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v4 + 577) )
    return 0;
  if ( !*(_BYTE *)(v4 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  if ( (int)a3->SetRoleField(0) <= 0 )
    return 0;
  v5 = sub_4F5330(a2, 0);
  if ( !v5 )
    return 0;
  v7[2] = a2;
  v7[1] = v5;
  v7[3] = a3;
  LOBYTE(v7[10]) = 1;
  LOWORD(v7[4]) = 0;
  v7[0] = 261;
  CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v7);
  return 1;
}

// 0x004D9F50
char sub_4D9F50(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD v11[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(v11, 0, sizeof(v11));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1385) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  v6 = a3->SetRoleField(1);
  v7 = a3->SetRoleField(0);
  v8 = a2->CalcPhysicalDamage(0, v6 - v7);
  if ( !v8 )
    return 0;
  v11[1] = v8;
  v11[3] = a3;
  LOBYTE(v11[10]) = 1;
  LOWORD(v11[4]) = 0;
  v11[0] = 260;
  v11[2] = a2;
  v9 = CCBSystem::CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, v11);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v9;
  return 1;
}

// 0x004DA0A0
char sub_4DA0A0(int a2, int a3)
{
  char result; // al
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v9[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v9, 0, sizeof(v9));
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 1386) && !(unsigned __int8)a2->GetRoleField(18)
    || (unsigned __int8)a2->GetRoleField(19) )
  {
    return 0;
  }
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 577) )
    return 0;
  result = a2->IsRoleAlive();
  if ( result )
  {
    v5 = a2->GetRoleHP();
    v6 = v5->CalcMagicDefense(0);
    v7 = a2->CalcPhysicalDamage(1, v6);
    if ( v7 )
    {
      v9[1] = v7;
      LOBYTE(v9[10]) = 1;
      LOWORD(v9[4]) = 0;
      v9[0] = 260;
      v9[2] = a2;
      v9[3] = -1;
      v9->GetRoleNum();
      v8 = CCBSystem::CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, v9);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = v8;
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
char sub_4DA1D0(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1386) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  v6 = a3->SetRoleField(0);
  if ( v6 <= 0 )
    return 0;
  ++g_nRandCallCount;
  g_RandSeed = 214013 * g_RandSeed + 2531011;
  v7 = a2->CalcMagicDamage(0, ((g_RandSeed >> 16) & 0x7FFF) % v6);
  if ( !v7 )
    return 0;
  v10[2] = a2;
  v10[1] = v7;
  v10[3] = a3;
  LOBYTE(v10[10]) = 1;
  LOWORD(v10[4]) = 0;
  v10[0] = 260;
  v8 = CCBSystem::CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, v10);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v8;
  return 1;
}

// 0x004DA350
char sub_4DA350(int a2, int a3)
{
  char result; // al
  int v5; // eax
  int v6; // ebp
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 1386) && !(unsigned __int8)a2->GetRoleField(18)
    || (unsigned __int8)a2->GetRoleField(19) )
  {
    return 0;
  }
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 577) )
    return 0;
  result = a2->IsRoleAlive();
  if ( result )
  {
    v5 = a2->GetRoleHP();
    v6 = v5->IsForce1();
    if ( (int)v6->CalcMPRegen(0) > 0 )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      v7 = v6->CalcMPRegen(0);
      v8 = a2->CalcMagicDamage(1, ((g_RandSeed >> 16) & 0x7FFF) % v7);
      if ( v8 )
      {
        LOBYTE(v10[10]) = 1;
        LOWORD(v10[4]) = 0;
        v10[0] = 260;
        v10[1] = v8;
        v10[2] = a2;
        v10[3] = -1;
        v10->GetRoleNum();
        v9 = CCBSystem::CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, v10);
        if ( a3 )
          *(_DWORD *)(a3 + 4) = v9;
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
char sub_4DA4F0(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD v11[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(v11, 0, sizeof(v11));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1387) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  v6 = a3->SetRoleField(1);
  v7 = a3->SetRoleField(0);
  v8 = a2->ProcessSkillEffect(0, v6 - v7);
  if ( !v8 )
    return 0;
  v11[1] = v8;
  v11[3] = a3;
  LOBYTE(v11[10]) = 1;
  LOWORD(v11[4]) = 0;
  v11[0] = 262;
  v11[2] = a2;
  v9 = CCBSystem::CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v11);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v9;
  return 1;
}

// 0x004DA640
char sub_4DA640(int a2, int a3)
{
  char result; // al
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v9[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v9, 0, sizeof(v9));
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 1387) && !(unsigned __int8)a2->GetRoleField(18)
    || (unsigned __int8)a2->GetRoleField(19) )
  {
    return 0;
  }
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 577) )
    return 0;
  result = a2->IsRoleAlive();
  if ( result )
  {
    v5 = a2->GetRoleHP();
    v6 = v5->CalcMagicDefense(0);
    v7 = a2->ProcessSkillEffect(1, v6);
    if ( v7 )
    {
      v9[1] = v7;
      LOBYTE(v9[10]) = 1;
      LOWORD(v9[4]) = 0;
      v9[0] = 262;
      v9[2] = a2;
      v9[3] = -1;
      v9->GetRoleNum();
      v8 = CCBSystem::CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v9);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = v8;
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
char sub_4DA770(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1387) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  if ( (int)a3->SetRoleField(0) <= 0 )
    return 0;
  ++g_nRandCallCount;
  g_RandSeed = 214013 * g_RandSeed + 2531011;
  v6 = a3->SetRoleField(0);
  v7 = a2->ProcessItemEffect(0, ((g_RandSeed >> 16) & 0x7FFF) % v6);
  if ( !v7 )
    return 0;
  v10[2] = a2;
  v10[1] = v7;
  v10[3] = a3;
  LOBYTE(v10[10]) = 1;
  LOWORD(v10[4]) = 0;
  v10[0] = 262;
  v8 = CCBSystem::CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v10);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v8;
  return 1;
}

// 0x004DA900
char sub_4DA900(int a2, int a3)
{
  char result; // al
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 1387) && !(unsigned __int8)a2->GetRoleField(18)
    || (unsigned __int8)a2->GetRoleField(19) )
  {
    return 0;
  }
  if ( !*(_BYTE *)(*((_DWORD *)this + 4) + 892 * a2 + 577) )
    return 0;
  result = a2->IsRoleAlive();
  if ( result )
  {
    v5 = a2->GetRoleHP();
    v6 = v5->IsForce1();
    v7 = v6->CalcMagicAttack(0);
    v8 = a2->ProcessItemEffect(1, v7);
    if ( v8 )
    {
      v10[1] = v8;
      LOBYTE(v10[10]) = 1;
      LOWORD(v10[4]) = 0;
      v10[0] = 262;
      v10[2] = a2;
      v10[3] = -1;
      v10->GetRoleNum();
      v9 = CCBSystem::CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v10);
      if ( a3 )
        *(_DWORD *)(a3 + 4) = v9;
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
char sub_4DAA40(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1385) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( (unsigned __int8)a3->IsRoleAlive() == 1 )
    return 0;
  v6 = a2->SetRoleField(1);
  v7 = sub_4F5D00(a2, 0, v6);
  if ( !v7 )
    return 0;
  v10[3] = a3;
  v10[1] = v7;
  v10[2] = a2;
  LOBYTE(v10[10]) = 1;
  LOWORD(v10[4]) = 0;
  v10[0] = 261;
  v8 = CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v10);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v8;
  return 1;
}

// 0x004DAB70
char sub_4DAB70(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1386) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( (unsigned __int8)a3->IsRoleAlive() == 1 )
    return 0;
  v6 = a2->SetRoleField(1);
  v7 = sub_4F6000(a2, 0, v6);
  if ( !v7 )
    return 0;
  v10[3] = a3;
  v10[1] = v7;
  v10[2] = a2;
  LOBYTE(v10[10]) = 1;
  LOWORD(v10[4]) = 0;
  v10[0] = 260;
  v8 = CCBSystem::CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, v10);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v8;
  return 1;
}

// 0x004DACA0
char sub_4DACA0(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v10[11]; // [esp+Ch] [ebp-2Ch] BYREF

  memset(v10, 0, sizeof(v10));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1387) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( (unsigned __int8)a3->IsRoleAlive() == 1 )
    return 0;
  v6 = a2->SetRoleField(1);
  v7 = sub_4F61D0(a2, 0, v6);
  if ( !v7 )
    return 0;
  v10[3] = a3;
  v10[1] = v7;
  v10[2] = a2;
  LOBYTE(v10[10]) = 1;
  LOWORD(v10[4]) = 0;
  v10[0] = 262;
  v8 = CCBSystem::CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v10);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v8;
  return 1;
}

// 0x004DADD0
char sub_4DADD0(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  _DWORD v9[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(v9, 0, sizeof(v9));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1385) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  v6 = sub_4F6370(a2, *(_DWORD *)(a4 + 12), 0);
  if ( !v6 )
    return 0;
  v9[2] = a2;
  v9[1] = v6;
  v9[3] = a3;
  LOBYTE(v9[10]) = 1;
  LOWORD(v9[4]) = 0;
  v9[0] = 261;
  v7 = CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v9);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v7;
  return 1;
}

// 0x004DAF00
char sub_4DAF00(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  _DWORD v9[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(v9, 0, sizeof(v9));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1386) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  v6 = sub_4F6690(a2, *(_DWORD *)(a4 + 12), 0);
  if ( !v6 )
    return 0;
  v9[2] = a2;
  v9[1] = v6;
  v9[3] = a3;
  LOBYTE(v9[10]) = 1;
  LOWORD(v9[4]) = 0;
  v9[0] = 260;
  v7 = CCBSystem::CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, v9);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v7;
  return 1;
}

// 0x004DB030
char sub_4DB030(int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  _DWORD v9[11]; // [esp+10h] [ebp-2Ch] BYREF

  memset(v9, 0, sizeof(v9));
  if ( !*(_BYTE *)(892 * a2 + *((_DWORD *)this + 4) + 1387) && !(unsigned __int8)a2->GetRoleField(18) )
    return 0;
  if ( (unsigned __int8)a2->GetRoleField(19) )
    return 0;
  v5 = *((_DWORD *)this + 4);
  if ( !*(_BYTE *)(892 * a2 + v5 + 577) )
    return 0;
  if ( !*(_BYTE *)(v5 + 892 * a3 + 577) )
    return 0;
  if ( !(unsigned __int8)a2->IsRoleAlive() )
    return 0;
  if ( !(unsigned __int8)a3->IsRoleAlive() )
    return 0;
  v6 = sub_4F6860(a2, *(_DWORD *)(a4 + 12), 0);
  if ( !v6 )
    return 0;
  v9[2] = a2;
  v9[1] = v6;
  v9[3] = a3;
  LOBYTE(v9[10]) = 1;
  LOWORD(v9[4]) = 0;
  v9[0] = 262;
  v7 = CCBSystem::CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v9);
  if ( a4 )
    *(_DWORD *)(a4 + 4) = v7;
  return 1;
}

// 0x004DB160
char sub_4DB160(int a2)
{
  int v4; // edi
  _DWORD v5[11]; // [esp+Ch] [ebp-2Ch] BYREF

  if ( *(_DWORD *)a2->InitUI() != 739 )
    return 0;
  v4 = sub_4F2C30(a2, 0);
  if ( v4 != sub_4F2C30(a2, 1) )
    return 0;
  memset(v5, 0, sizeof(v5));
  LOWORD(v5[4]) = 0;
  LOBYTE(v5[10]) = 1;
  v5[0] = 261;
  v5[1] = 7709;
  v5[2] = a2;
  v5[3] = -1;
  v5->GetRoleNum();
  CCBSystem::CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v5);
  CEffMgr::Init(*(int **)(*((_DWORD *)this + 3) + 44), 559, 0, 0, 0, 0);
  return 1;
}

// 0x004DB270
// attributes: thunk
int CCBAI::CastCureSpecStateMagic()
{
  return CCBAI::CastCureSpecStateSkill();
}

// 0x004DB280
int sub_4DB280()
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
void sub_4DB2A0()
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
int sub_4DB2C0()
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
int sub_4DB310()
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
int sub_4DB360()
{
  *(_DWORD *)&Buffer[940] = 128;
  *(_DWORD *)&Buffer[944] = 323;
  *(_DWORD *)&Buffer[948] = 519;
  *(_DWORD *)&Buffer[952] = 716;
  return 716;
}
