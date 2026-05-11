#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/SoundContext.h"

// Forward declarations for unnamed functions
int UISceneUpdate(...);
int sub_407DC0(...);
int sub_408460(...);
int sub_4122C0(...);
int sub_4126D0(...);
int sub_412D90(...);
int sub_4132B0(...);
int sub_413C00(...);
int sub_4142E0(...);
int sub_416550(...);
int sub_416620(...);
int sub_41C1E0(...);
int sub_421020(...);
int sub_421230(...);
int sub_421440(...);
int sub_4215B0(...);
int sub_4218B0(...);
int sub_424C20(...);

// Unnamed globals (extern)
extern char aTagWeapon1[];
extern char aTagWeapon2[];
extern unsigned char byte_C116EA;
extern int dword_58615C;
extern int dword_58B29C;
extern int dword_58B2B0;
extern int dword_58B2C4;
extern int dword_58B328;
extern int dword_58B33C;
extern int dword_58B350;
extern int dword_58B38C;
extern int dword_58B3B4;
extern int dword_58B3C8;
extern int dword_58B3DC;
extern int dword_58B3F0;
extern int dword_5D0750;
extern int nullsub_5;
extern int unk_C1109C;

// 0x0040BE50
int * RoleSystem::Init()
{
  int *result; // eax
  int v2; // esi
  int v3; // edx

  result = (int *)&this->_gap_0278[340];
  v2 = 12;
  do
  {
    v3 = *(result - 12);
    if ( *result < v3 )
    {
      if ( *result <= 0 )
        *result = 0;
    }
    else
    {
      *result = v3;
    }
    ++result;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x0040BE80
int RoleSystem::LoadData(char a2)
{
  int i; // edx
  int *v3; // esi
  int v4; // eax
  bool v5; // cf
  int v6; // esi
  _BYTE *v7; // esi
  bool v8; // cf
  _BYTE *v9; // esi
  bool v10; // cf
  _BYTE *v11; // esi
  bool v12; // cf
  _BYTE *v13; // esi
  bool v14; // cf
  _BYTE *v15; // esi
  bool v16; // cf
  int result; // eax

  for ( i = 0; i < 12; ++i )
  {
    v3 = (int *)*(int **)&this->_gap_0278[288];
    v4 = 0;
    if ( !v3 )
      goto LABEL_33;
    if ( !*((_BYTE *)v3 + i + 631) && i < 7 )
      v4 = *((__int16 *)v3 + i + 322);
    switch ( i )
    {
      case 7:
        v5 = *((_BYTE *)v3 + 619) != 0;
        goto LABEL_12;
      case 8:
        v5 = *((_BYTE *)v3 + 620) != 0;
        goto LABEL_12;
      case 9:
        v5 = *((_BYTE *)v3 + 621) != 0;
        goto LABEL_12;
      case 10:
        v5 = *((_BYTE *)v3 + 622) != 0;
        goto LABEL_12;
      case 11:
        v5 = *((_BYTE *)v3 + 623) != 0;
LABEL_12:
        v4 += v5;
        break;
      default:
        break;
    }
    v6 = *v3;
    if ( v6 == 6603 && !dword_5D0750 && i == 7 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( v6 != 6603 )
      goto LABEL_31;
    if ( dword_5D0750 == 1 && i == 8 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( dword_5D0750 == 3 && i == 9 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( dword_5D0750 == 2 && i == 10 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( dword_5D0750 == 4 && i == 11 )
    {
      ++v4;
    }
    else
    {
LABEL_31:
      if ( i == 3 && v6 == 6603 )
        v4 += dword_58615C;
    }
LABEL_33:
    v7 = (_BYTE *)*(_BYTE **)&this->_gap_0278[240];
    if ( v7 )
    {
      if ( !v7[i + 631] )
        v4 += *(__int16 *)&v7[2 * i + 644];
      switch ( i )
      {
        case 7:
          v8 = v7[619] != 0;
          goto LABEL_42;
        case 8:
          v8 = v7[620] != 0;
          goto LABEL_42;
        case 9:
          v8 = v7[621] != 0;
          goto LABEL_42;
        case 10:
          v8 = v7[622] != 0;
          goto LABEL_42;
        case 11:
          v8 = v7[623] != 0;
LABEL_42:
          v4 += v8;
          break;
        default:
          break;
      }
    }
    v9 = (_BYTE *)*(_BYTE **)&this->_gap_0278[228];
    if ( v9 )
    {
      if ( !v9[i + 631] )
        v4 += *(__int16 *)&v9[2 * i + 644];
      switch ( i )
      {
        case 7:
          v10 = v9[619] != 0;
          goto LABEL_52;
        case 8:
          v10 = v9[620] != 0;
          goto LABEL_52;
        case 9:
          v10 = v9[621] != 0;
          goto LABEL_52;
        case 10:
          v10 = v9[622] != 0;
          goto LABEL_52;
        case 11:
          v10 = v9[623] != 0;
LABEL_52:
          v4 += v10;
          break;
        default:
          break;
      }
    }
    v11 = (_BYTE *)*(_BYTE **)&this->_gap_0278[252];
    if ( v11 )
    {
      if ( !v11[i + 631] )
        v4 += *(__int16 *)&v11[2 * i + 644];
      switch ( i )
      {
        case 7:
          v12 = v11[619] != 0;
          goto LABEL_62;
        case 8:
          v12 = v11[620] != 0;
          goto LABEL_62;
        case 9:
          v12 = v11[621] != 0;
          goto LABEL_62;
        case 10:
          v12 = v11[622] != 0;
          goto LABEL_62;
        case 11:
          v12 = v11[623] != 0;
LABEL_62:
          v4 += v12;
          break;
        default:
          break;
      }
    }
    v13 = (_BYTE *)*(_BYTE **)&this->_gap_0278[264];
    if ( v13 )
    {
      if ( !v13[i + 631] )
        v4 += *(__int16 *)&v13[2 * i + 644];
      switch ( i )
      {
        case 7:
          v14 = v13[619] != 0;
          goto LABEL_72;
        case 8:
          v14 = v13[620] != 0;
          goto LABEL_72;
        case 9:
          v14 = v13[621] != 0;
          goto LABEL_72;
        case 10:
          v14 = v13[622] != 0;
          goto LABEL_72;
        case 11:
          v14 = v13[623] != 0;
LABEL_72:
          v4 += v14;
          break;
        default:
          break;
      }
    }
    v15 = (_BYTE *)*(_BYTE **)&this->_gap_0278[276];
    if ( v15 )
    {
      if ( !v15[i + 631] )
        v4 += *(__int16 *)&v15[2 * i + 644];
      switch ( i )
      {
        case 7:
          v16 = v15[619] != 0;
          goto LABEL_82;
        case 8:
          v16 = v15[620] != 0;
          goto LABEL_82;
        case 9:
          v16 = v15[621] != 0;
          goto LABEL_82;
        case 10:
          v16 = v15[622] != 0;
          goto LABEL_82;
        case 11:
          v16 = v15[623] != 0;
LABEL_82:
          v4 += v16;
          break;
        default:
          break;
      }
    }
    result = *(_DWORD *)&this->_gap_0278[4 * i + 4] + v4;
    *(_DWORD *)&this->_gap_0278[4 * i + 292] = result;
    if ( a2 || (unsigned int)i > 2 )
      *(_DWORD *)&this->_gap_0278[4 * i + 340] = result;
  }
  return result;
}

// 0x00410E40
int RoleSystem::CheckVisible(int a1)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // ebx
  _DWORD *v3; // ecx
  unsigned int v4; // esi
  int v5; // edi
  unsigned int v6; // ebp
  int v7; // edx
  unsigned int v8; // eax
  _DWORD *v10; // edx
  _DWORD *k; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // ebx
  _DWORD *v14; // edi
  _DWORD *v15; // eax
  int result; // eax
  int v17; // ecx
  int v18; // kr00_4
  int v20; // ebp
  _DWORD *v21; // edx
  _DWORD *v22; // eax
  _DWORD *v23; // ebx
  unsigned int j; // esi
  int v25; // eax
  int v26; // ecx
  _DWORD *v27; // edi
  int v28; // esi
  _DWORD *v29; // eax
  _DWORD *i; // edx
  _DWORD *v31; // ecx
  _DWORD *v32; // eax
  _DWORD *v33; // ebx
  _DWORD *v34; // [esp+10h] [ebp-8h]
  _DWORD *v35; // [esp+14h] [ebp-4h]
  int a1a; // [esp+1Ch] [ebp+4h]
  int a1b; // [esp+1Ch] [ebp+4h]
  unsigned int v38; // [esp+20h] [ebp+8h]
  unsigned int v39; // [esp+20h] [ebp+8h]
  _DWORD *v40; // [esp+20h] [ebp+8h]
  _DWORD *v41; // [esp+24h] [ebp+Ch]

  v2 = v1;
  v3 = (_DWORD *)v1[2];
  v4 = v38;
  v34 = v2;
  if ( (v2[3] - (int)v3) / 12 >= v38 )
  {
    result = (unsigned int)((unsigned __int64)(715827883LL * ((int)v3 - a1)) >> 32) >> 31;
    if ( ((int)v3 - a1) / 12 >= v38 )
    {
      if ( v38 )
      {
        v28 = 12 * v38;
        v29 = (_DWORD *)&v3[-3 * v38];
        for ( i = v3; v29 != v3; i += 3 )
        {
          if ( i )
          {
            * i = (*)*v29;
            i[1] = v29[1];
            i[2] = v29[2];
            v28 = 12 * v38;
            v2 = v34;
          }
          v29 += 3;
        }
        v31 = (_DWORD *)v2[2];
        v32 = (_DWORD *)&v31[v28 / 0xFFFFFFFC];
        if ( (_DWORD *)a1 != &v31[v28 / 0xFFFFFFFC] )
        {
          do
          {
            v32 -= 3;
            v31 -= 3;
            * v31 = (*)*v32;
            v31[1] = v32[1];
            v31[2] = v32[2];
          }
          while ( v32 != (_DWORD *)a1 );
          v2 = v34;
        }
        result = a1;
        if ( a1 != v28 + a1 )
        {
          do
          {
            v33 = (_DWORD *)result;
            result += 12;
            * v33 = (*)*v41;
            v33[1] = v41[1];
            v33[2] = v41[2];
          }
          while ( result != v28 + a1 );
          v2 = v34;
        }
        v2[2] += v28;
      }
    }
    else
    {
      v20 = 12 * v38;
      a1b = 12 * v38;
      v21 = (_DWORD *)(a1 + 12 * v38);
      v40 = v21;
      if ( (_DWORD *)a1 != v3 )
      {
        v22 = (_DWORD *)((char *)v21 - v20);
        do
        {
          if ( v21 )
          {
            * v21 = (*)*v22;
            v21[1] = v22[1];
            v20 = a1b;
            v21[2] = v22[2];
            v21 = v40;
            v2 = v34;
          }
          v22 += 3;
          v21 += 3;
          v40 = v21;
        }
        while ( v22 != v3 );
      }
      v23 = (_DWORD *)v2[2];
      for ( j = v4 - ((int)v23 - a1) / 12; j; --j )
      {
        if ( v23 )
        {
          * v23 = (*)*v41;
          v23[1] = v41[1];
          v23[2] = v41[2];
        }
        v23 += 3;
      }
      v25 = a1;
      v26 = v34[2];
      if ( a1 != v26 )
      {
        do
        {
          v27 = (_DWORD *)v25;
          v25 += 12;
          * v27 = (*)*v41;
          v27[1] = v41[1];
          v27[2] = v41[2];
        }
        while ( v25 != v26 );
      }
      result = v20 + v34[2];
      v34[2] = result;
    }
  }
  else
  {
    v5 = v2[1];
    if ( !v5 || (v6 = ((int)v3 - v5) / 12, v38 >= v6) )
      v6 = v38;
    if ( v5 )
      v7 = ((int)v3 - v5) / 12;
    else
      v7 = 0;
    v8 = v7 + v6;
    v39 = v7 + v6;
    if ( (int)(v7 + v6) < 0 )
      v8 = 0;
    v35 = (_DWORD *)operator new(12 * v8);
    v10 = v35;
    for ( k = (_DWORD *)v2[1]; k != (_DWORD *)a1; v10 += 3 )
    {
      if ( v10 )
      {
        * v10 = (*)*k;
        v10[1] = k[1];
        v10[2] = k[2];
      }
      k += 3;
    }
    v12 = v10;
    if ( v4 )
    {
      a1a = v4;
      do
      {
        if ( v12 )
        {
          * v12 = (*)*v41;
          v12[1] = v41[1];
          v12[2] = v41[2];
        }
        v12 += 3;
        --a1a;
      }
      while ( a1a );
    }
    v13 = (_DWORD *)v2[2];
    v14 = (_DWORD *)&v10[3 * v4];
    if ( (_DWORD *)a1 != v13 )
    {
      v15 = (_DWORD *)a1;
      do
      {
        if ( v14 )
        {
          * v14 = (*)*v15;
          v14[1] = v15[1];
          v14[2] = v15[2];
        }
        v15 += 3;
        v14 += 3;
      }
      while ( v15 != v13 );
    }
    operator delete((void *)v34[1]);
    result = v34[1];
    v34[3] = &v35[3 * v39];
    if ( result )
    {
      v17 = v34[2];
      v34[1] = v35;
      v18 = v17 - result;
      result = (unsigned int)((unsigned __int64)(715827883LL * (v17 - result)) >> 32) >> 31;
      v4 += v18 / 12;
    }
    else
    {
      v34[1] = v35;
    }
    v34[2] = &v35[3 * v4];
  }
  return result;
}

// 0x00412400
void RoleSystem::RenderRole(void *pStack, int a3)
{
  _BYTE v4[64]; // [esp+38h] [ebp-40h] BYREF

  if ( *(_DWORD *)this->_gap_0278 )
  {
    if ( (g_SceneMgr.m_szUIString[92] & 1) == 0 )
    {
      *(_DWORD *)&g_SceneMgr.m_szUIString[80] = 0;
      g_SceneMgr.m_szUIString[92] |= 1u;
      *(_DWORD *)&g_SceneMgr.m_szUIString[84] = 1065353216;
      *(_DWORD *)&g_SceneMgr.m_szUIString[88] = 0;
      atexit(nullsub_5);
    }
    ((gbMatrixStack *)pStack)->Push();
    ((gbMatrixStack *)pStack)->Translate((struct gbVec3D *)&this->m_fPosX);
    if ( this->_d4F0 == 4 && this->_d4CC == 11 )
      ((gbMatrixStack *)pStack)->Rotate(this->_f540, (struct gbVec3D *)&this->_f510);
    ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->_end[7196], (struct gbVec3D *)&g_SceneMgr.m_szUIString[80]);
    ((gbMatrixStack *)pStack)->Scale(*(float *)&this->_gap_0278[8], *(float *)&this->_gap_0278[8], *(float *)&this->_gap_0278[8]);
    *(_DWORD *)&this->_gap_0018[120] = ((Actor *)&this->_gap_0278[48])->DispatchAction(a3);
    if ( *(_DWORD *)&this->_gap_0574[44] )
    {
      ((gbMatrix4 *)v4)->gbMatrix4();
      if ( this->_gap_0574[49] )
      {
        ((gbMatrixStack *)pStack)->Push();
        ((gbActor *)*(gbActor **)&this->_gap_0278[64])->GetTagNodeTM((struct gbMatrix4 *)v4, aTagWeapon1);
        ((gbMatrixStack *)pStack)->MultMatrix((struct gbMatrix4 *)v4);
        (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)&this->_gap_0574[44] + 16))(
          *(_DWORD *)&this->_gap_0574[44],
          0);
        ((gbMatrixStack *)pStack)->Pop();
      }
      if ( this->_gap_0574[48] )
      {
        ((gbMatrixStack *)pStack)->Push();
        ((gbActor *)*(gbActor **)&this->_gap_0278[64])->GetTagNodeTM((struct gbMatrix4 *)v4, aTagWeapon2);
        ((gbMatrixStack *)pStack)->MultMatrix((struct gbMatrix4 *)v4);
        (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)&this->_gap_0574[44] + 16))(
          *(_DWORD *)&this->_gap_0574[44],
          0);
        ((gbMatrixStack *)pStack)->Pop();
      }
    }
    ((gbMatrixStack *)pStack)->Pop();
  }
}

// 0x00412710
int RoleSystem::UpdateTransform()
{
  __int64 m_nCoreState; // rax
  char v3; // al
  int v4; // [esp-4h] [ebp-Ch]
  int v5; // [esp-4h] [ebp-Ch]
  int v6; // [esp-4h] [ebp-Ch]
  int v7; // [esp-4h] [ebp-Ch]

  m_nCoreState = (unsigned int)this->m_nCoreState;
  if ( (unsigned int)m_nCoreState > 0x3A )
    this->m_nCoreState = 0;
  switch ( this->m_nCoreState )
  {
    case 0:
    case 5:
    case 7:
      this->_d508 = 0;
      this->_f50C = 0.0;
      this->_f510 = 0.0;
      this->_f514 = 0.0;
      this->_f518 = 0.0;
      this->_d51C = 0;
      this->_d520 = LODWORD(this->_f514);
      *(float *)this->_gap_0524 = this->_f518;
      return this->UpdatePath(this->m_nCoreState);
    case 1:
    case 3:
      LODWORD(this->_f50C) = dword_58B3B4;
      v3 = this->_gap_00AC[1];
      if ( v3 == -1 )
      {
        HIDWORD(m_nCoreState) = dword_58B3DC;
LABEL_7:
        this->_d508 = HIDWORD(m_nCoreState);
        return this->UpdatePath(this->m_nCoreState);
      }
      if ( v3 == 2 )
      {
        if ( *(_DWORD *)&this->_gap_0574[20] == 1 )
        {
          if ( *(_BYTE *)(*(_DWORD *)&this->_gap_0574[24] + 756) == 1 )
          {
            v5 = this->m_nCoreState;
            this->_d508 = dword_58B33C;
            return this->UpdatePath(v5);
          }
          else if ( *(_BYTE *)(*(_DWORD *)&this->_gap_0574[24] + 756) == 2 )
          {
            this->_d508 = dword_58B350;
            return this->UpdatePath(this->m_nCoreState);
          }
          else
          {
            v4 = this->m_nCoreState;
            this->_d508 = dword_58B328;
            return this->UpdatePath(v4);
          }
        }
        else
        {
          switch ( *(_BYTE *)(*(_DWORD *)&this->_gap_0574[24] + 755) )
          {
            case 0:
              goto LABEL_7;
            case 1:
              this->_d508 = dword_58B29C;
              return this->UpdatePath(this->m_nCoreState);
            case 2:
              v6 = this->m_nCoreState;
              this->_d508 = dword_58B2B0;
              return this->UpdatePath(v6);
            default:
              this->_d508 = dword_58B2C4;
              return this->UpdatePath(this->m_nCoreState);
          }
        }
      }
      else
      {
        LODWORD(m_nCoreState) = *(_DWORD *)&this->_gap_00AC[336];
        v7 = this->m_nCoreState;
        if ( (_DWORD)m_nCoreState == HIDWORD(m_nCoreState) )
          this->_d508 = dword_58B38C;
        else
          *(float *)&this->_d508 = (float)m_nCoreState;
        return this->UpdatePath(v7);
      }
    case 2:
      this->_d508 = dword_58B3F0;
      LODWORD(this->_f50C) = dword_58B3C8;
      return this->UpdatePath(this->m_nCoreState);
    default:
      return this->UpdatePath(this->m_nCoreState);
  }
}

// 0x00412940
int RoleSystem::UpdatePath(int a2)
{
  int v3; // ebp
  Actor *v4; // edi
  int result; // eax
  int v6; // [esp-8h] [ebp-14h]

  if ( this->_gap_00AC[2] == 49 )
  {
    ((Actor *)&this->_gap_0278[48])->CompareAction(a2, 2);
    ((Actor *)&this->_gap_0278[48])->SetTimeScale(1.0);
    this->_gap_0574[49] = 0;
    this->_gap_0574[48] = 0;
    return result;
  }
  v3 = sub_4126D0(a2, this->_gap_00AC[1]);
  if ( this->_gap_00AC[2] == 50 )
    goto LABEL_10;
  if ( v3 == 50 )
  {
    v4 = (Actor *)&this->_gap_0278[48];
    if ( !((Actor *)&this->_gap_0278[48])->LoadAction(aZ0) )
      v4->CompareAction(50, 0);
    goto LABEL_12;
  }
  if ( v3 != 52 && v3 != 58 )
  {
LABEL_10:
    v4 = (Actor *)&this->_gap_0278[48];
    v6 = 2;
    goto LABEL_11;
  }
  v4 = (Actor *)&this->_gap_0278[48];
  if ( !((Actor *)&this->_gap_0278[48])->LoadAction(aZ4) )
  {
    v6 = 0;
LABEL_11:
    v4->CompareAction(v3, v6);
  }
LABEL_12:
  if ( this->m_nCoreState == 2 )
    v4->SetTimeScale(2.4000001);
  else
    v4->SetTimeScale(1.0);
  this->_gap_0574[49] = 0;
  this->_gap_0574[48] = 0;
  return result;
}

// 0x00412E60
int RoleSystem::MoveRole(float *pPos, int a3, int a4, int a5)
{
  int result; // eax
  int d4F4; // ecx
  RoleSystem *v8; // eax
  int RolePtr; // ebx
  RoleSystem *v10; // eax
  int v11; // edx
  int v12; // [esp-18h] [ebp-34h]
  int v13; // [esp-14h] [ebp-30h]
  int v14; // [esp-10h] [ebp-2Ch]
  int v15; // [esp-Ch] [ebp-28h]
  int m_nState; // [esp-8h] [ebp-24h]
  int v17; // [esp-8h] [ebp-24h]

  this->_f540 = *pPos;
  result = a3;
  this->_f544 = pPos[1];
  this->_f548 = pPos[2];
  d4F4 = this->_d4F4;
  *(_DWORD *)this->_gap_054C = a3;
  *(_DWORD *)&this->_gap_0574[64] = 1;
  if ( d4F4 != 2 )
  {
    LOBYTE(result) = this->UpdateRole((int)pPos, a3, a4);
    this->_d5B8 = 0;
    return result;
  }
  if ( a3 == this->m_nState )
  {
    m_nState = this->m_nState;
    v8 = (RoleSystem *)UISceneUpdate();
    RolePtr = v8->GetRolePtr(m_nState);
    v17 = (__int64)((pPos[2] - *(float *)(RolePtr + 136)) / unk_C1109C);
    v15 = (__int64)((*pPos - *(float *)(RolePtr + 128)) / unk_C1109C);
    v14 = (__int64)((this->m_fTargetZ - *(float *)(RolePtr + 136)) / unk_C1109C);
    v13 = (__int64)((this->m_fTargetX - *(float *)(RolePtr + 128)) / unk_C1109C);
    v12 = this->m_nState;
    v10 = (RoleSystem *)UISceneUpdate();
    if ( sub_4215B0(v10, v12, v13, v14, v15, v17) )
    {
      *(_DWORD *)&this->_end[3060] = 2;
      *(float *)&this->_gap_05BC[12] = this->m_fTargetX;
      *(float *)&this->_gap_05BC[16] = this->m_fTargetY;
      this->_d5D0 = LODWORD(this->m_fTargetZ);
      *(float *)this->_end = *pPos;
      *(float *)&this->_end[4] = pPos[1];
      *(float *)&this->_end[8] = pPos[2];
      return sub_407DC0((float *)&this->_gap_05BC[12]);
    }
    result = a3;
  }
  if ( a5 || (v11 = this->_d5B8 + 1, this->_d5B8 = v11, v11 > 30) )
  {
    this->_d5B8 = 0;
    LOBYTE(result) = this->UpdateRole((int)pPos, result, a4);
  }
  return result;
}

// 0x00413010
char RoleSystem::UpdateRole(int a2, int a3, int a4)
{
  float v5; // eax
  RoleSystem *v6; // eax
  int RolePtr; // ebp
  int v8; // esi
  int v9; // edx
  int *v10; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // kr00_4
  int v14; // eax
  int v15; // ecx
  float v16; // eax
  int m_nState; // [esp-4h] [ebp-48h]
  int v19; // [esp+10h] [ebp-34h]
  int v20; // [esp+14h] [ebp-30h]
  int v21; // [esp+18h] [ebp-2Ch]
  int v22; // [esp+1Ch] [ebp-28h]
  int v23; // [esp+20h] [ebp-24h]
  int v24; // [esp+24h] [ebp-20h]
  int v25; // [esp+28h] [ebp-1Ch]
  float v26[2]; // [esp+2Ch] [ebp-18h] BYREF
  float v27; // [esp+34h] [ebp-10h]
  float v28; // [esp+38h] [ebp-Ch]
  float v29; // [esp+3Ch] [ebp-8h]
  float v30; // [esp+40h] [ebp-4h]

  if ( a3 == this->m_nState )
    return sub_412D90((int)this, (float *)a2, a4);
  m_nState = this->m_nState;
  v6 = (RoleSystem *)UISceneUpdate();
  RolePtr = v6->GetRolePtr(m_nState);
  v21 = RolePtr;
  v24 = (__int64)((this->m_fTargetX - *(float *)(RolePtr + 128)) / unk_C1109C);
  v8 = v22;
  v9 = 0x7FFFF;
  v25 = (__int64)((this->m_fTargetZ - *(float *)(RolePtr + 136)) / unk_C1109C);
  v20 = 0x7FFFF;
  v19 = 0;
  v10 = (int *)(RolePtr + 8);
  do
  {
    v11 = *(v10 - 2);
    v12 = *v10;
    if ( v11 != *v10 || v12 )
    {
      v8 = (v12 + v11) / 2;
      v13 = v10[1] + *(v10 - 1);
      v9 = v20;
      RolePtr = v21;
      if ( (v8 - v24) * (v8 - v24) + (v13 / 2 - v25) * (v13 / 2 - v25) >= v20 )
      {
        v8 = v22;
      }
      else
      {
        v23 = v13 / 2;
        v9 = (v8 - v24) * (v8 - v24) + (v13 / 2 - v25) * (v13 / 2 - v25);
        v20 = v9;
        v22 = (v12 + v11) / 2;
        *(_DWORD *)&this->_gap_054C[4] = v19;
      }
    }
    v10 += 4;
    LOBYTE(v5) = ++v19;
  }
  while ( v19 < 8 );
  if ( v9 <= 32 )
  {
    v29 = 0.0;
    v28 = ((double)v22 + 0.5) * unk_C1109C + *(float *)(RolePtr + 128);
    v30 = ((double)v23 + 0.5) * unk_C1109C + *(float *)(RolePtr + 136);
    if ( v8 < 0 || (v14 = *(_DWORD *)(RolePtr + 152), v8 >= v14) )
    {
      v15 = v23;
    }
    else
    {
      v15 = v23;
      if ( v23 >= 0 && v23 < *(_DWORD *)(RolePtr + 156) )
        v29 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (v8 + v23 * v14));
    }
    v26[0] = v28;
    v27 = v30;
    v26[1] = 0.0;
    if ( v24 == v8 && v25 == v15 )
    {
      sub_413C00((int)this, a3, *(_DWORD *)&this->_gap_054C[4]);
      LOBYTE(v5) = sub_412D90((int)this, v26, a4);
    }
    else
    {
      v16 = v27;
      this->_f540 = v26[0];
      this->_f544 = 0.0;
      this->_f548 = v16;
      if ( sub_408460(
             &g_SceneMgr.m_szUIString[184],
             this->m_nState,
             &this->m_fTargetX,
             v26,
             (float *)&this->_gap_05BC[12],
             this->_gap_00AC[0]) )
      {
        this->_d4F4 = 7;
        this->m_nCoreState = a4;
        this->UpdateTransform();
        this->_f540 = *(float *)a2;
        this->_f544 = *(float *)(a2 + 4);
        v5 = *(float *)(a2 + 8);
        this->_f548 = v5;
        this->_f544 = 0.0;
        *(_DWORD *)this->_gap_054C = a3;
      }
      else
      {
        LOBYTE(v5) = sub_4142E0(this);
      }
    }
  }
  return LOBYTE(v5);
}

// 0x00414980
void RoleSystem::GetPosition(void *pOut, int a3)
{
  gbVec3D *p_d51C; // esi
  double v5; // st7

  p_d51C = (gbVec3D *)&this->_d51C;
  this->_d51C = *(_DWORD *)pOut;
  this->_d520 = *((_DWORD *)pOut + 1);
  *(_DWORD *)this->_gap_0524 = *((_DWORD *)pOut + 2);
  this->m_nCoreState = a3;
  this->UpdateTransform();
  if ( a3 )
  {
    this->_d520 = 0;
    p_d51C->Normalize();
    v5 = *(float *)&this->_d508;
    p_d51C->x = v5 * p_d51C->x;
    p_d51C->y = v5 * p_d51C->y;
    p_d51C->z = v5 * p_d51C->z;
    this->_d4F4 = 12;
  }
  else
  {
    this->_d4F4 = 0;
  }
}

// 0x00414A30
int RoleSystem::PathFind(float *pTarget)
{
  int d4F0; // eax
  double v4; // st7
  double v5; // st7
  float y; // ecx
  double v7; // st7
  double v8; // st7
  float *p_d4D8; // ebp
  float v10; // ecx
  RoleSystem *v11; // eax
  RoleSystem *v12; // eax
  int RolePtr; // edi
  int v14; // ebx
  double v15; // st7
  __int64 v16; // rax
  double v17; // st7
  RoleSystem *v18; // eax
  double v19; // st7
  int v20; // ecx
  int v21; // edx
  int v22; // eax
  float v23; // eax
  RoleSystem *v24; // eax
  long double v25; // st7
  long double v26; // st6
  double v27; // st7
  double v28; // st7
  float v29; // edx
  double v30; // st7
  double v31; // st7
  int result; // eax
  double v33; // st7
  int v34; // [esp-18h] [ebp-5Ch]
  int m_nState; // [esp-10h] [ebp-54h]
  int v36; // [esp-10h] [ebp-54h]
  int v37; // [esp-10h] [ebp-54h]
  int v38; // [esp-Ch] [ebp-50h]
  int v39; // [esp-Ch] [ebp-50h]
  int v40; // [esp-8h] [ebp-4Ch]
  int v41; // [esp-8h] [ebp-4Ch]
  int v42; // [esp-4h] [ebp-48h]
  int v43; // [esp+10h] [ebp-34h] BYREF
  int v44; // [esp+14h] [ebp-30h]
  int v45; // [esp+18h] [ebp-2Ch]
  float v46; // [esp+20h] [ebp-24h]
  float v47; // [esp+24h] [ebp-20h]
  float v48; // [esp+28h] [ebp-1Ch]
  gbVec3D v49; // [esp+2Ch] [ebp-18h] BYREF
  gbVec3D v50; // [esp+38h] [ebp-Ch] BYREF

  d4F0 = this->_d4F0;
  this->_d4CC = 0;
  this->_d4D0 = 0;
  if ( d4F0 != 4 )
    this->_d4EC = d4F0;
  this->_d4F0 = 4;
  v50.x = *pTarget - this->m_fTargetX;
  v4 = pTarget[1] - this->m_fTargetY;
  v49.x = v50.x;
  v50.y = v4;
  v5 = pTarget[2] - this->m_fTargetZ;
  y = v50.y;
  pTarget[1] = 0.0;
  v49.y = y;
  v50.z = v5;
  v49.z = v50.z;
  v7 = ((gbVec3D *)&v49)->Length();
  if ( v7 <= *(float *)&g_SceneMgr.m_szUIString[16] )
  {
    p_d4D8 = (float *)&this->_d4D8;
    this->_d4D8 = *(int *)pTarget;
    this->_f4DC = pTarget[1];
    this->_d4E0 = (int)pTarget[2];
  }
  else
  {
    v8 = *(float *)&g_SceneMgr.m_szUIString[16] / v7;
    p_d4D8 = (float *)&this->_d4D8;
    v49.x = v49.x * v8;
    v49.y = v49.y * v8;
    v49.x = v49.x + this->m_fTargetX;
    v49.y = v49.y + this->m_fTargetY;
    v10 = v49.y;
    v7 = v8 * v49.z + this->m_fTargetZ;
    this->_d4D8 = LODWORD(v49.x);
    this->_f4DC = v10;
    v49.z = v7;
    *(float *)&this->_d4E0 = v7;
  }
  m_nState = this->m_nState;
  v11 = (RoleSystem *)UISceneUpdate();
  sub_421440(v11, m_nState, p_d4D8, 0, 0);
  this->_f4DC = v7;
  if ( !byte_C116EA )
  {
    v42 = this->m_nState;
    v12 = (RoleSystem *)UISceneUpdate();
    RolePtr = v12->GetRolePtr(v42);
    v14 = (__int64)((this->m_fTargetX - *(float *)(RolePtr + 128)) / unk_C1109C);
    v15 = *p_d4D8 - *(float *)(RolePtr + 128);
    LODWORD(v47) = (__int64)((this->m_fTargetZ - *(float *)(RolePtr + 136)) / unk_C1109C);
    v16 = (__int64)(v15 / unk_C1109C);
    v17 = p_d4D8[2] - *(float *)(RolePtr + 136);
    v45 = v16;
    v40 = (__int64)(v17 / unk_C1109C);
    v38 = v16;
    v36 = LODWORD(v47);
    v34 = this->m_nState;
    v18 = (RoleSystem *)UISceneUpdate();
    if ( !sub_4218B0(v18, v34, v14, v36, v38, v40, &v43) )
    {
      v19 = 0.0;
      v20 = v43;
      v21 = v44;
      v46 = ((double)v43 + 0.5) * unk_C1109C + *(float *)(RolePtr + 128);
      v48 = ((double)v44 + 0.5) * unk_C1109C + *(float *)(RolePtr + 136);
      if ( v43 >= 0 )
      {
        v22 = *(_DWORD *)(RolePtr + 152);
        if ( v43 < v22 && v44 >= 0 && v44 < *(_DWORD *)(RolePtr + 156) )
          v19 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (v43 + v44 * v22));
      }
      v23 = v46;
      p_d4D8[1] = v19;
      *p_d4D8 = v23;
      v41 = v21;
      p_d4D8[2] = v48;
      v39 = v20;
      v37 = this->m_nState;
      v24 = (RoleSystem *)UISceneUpdate();
      this->_f4DC = sub_421230(v24, v37, v39, v41, 0);
    }
  }
  this->_f510 = *p_d4D8;
  this->_f514 = p_d4D8[1];
  this->_f518 = p_d4D8[2];
  this->_f510 = this->_f510 - this->m_fPosX;
  this->_f514 = this->_f514 - this->m_fPosY;
  this->_f518 = this->_f518 - this->m_fPosZ;
  this->_f514 = 0.0;
  ((gbVec3D *)&this->_f510)->Normalize();
  sub_4122C0((int)this);
  v25 = sqrt((50.0 + 50.0) / 490.0);
  this->_f4E4 = v25;
  v26 = fabs(this->_f4DC - this->m_fPosY);
  this->_d4E8 = 0;
  this->_f4E4 = sqrt((v26 + 50.0 + v26 + 50.0) / 490.0) + v25;
  v46 = *p_d4D8 - this->m_fPosX;
  v27 = p_d4D8[1] - this->m_fPosY;
  v50.x = v46;
  v47 = v27;
  v28 = p_d4D8[2] - this->m_fPosZ;
  this->_f514 = 0.0;
  v48 = v28;
  v29 = v48;
  this->_f510 = v50.x;
  v50.z = v29;
  v50.y = 0.0;
  this->_f518 = v29;
  ((gbVec3D *)&this->_f510)->Normalize();
  v30 = ((gbVec3D *)&v50)->Length() / this->_f4E4;
  this->_f510 = v30 * this->_f510;
  this->_f514 = v30 * this->_f514;
  this->_f518 = v30 * this->_f518;
  v31 = 50.0;
  if ( this->_f4DC > (double)this->m_fPosY )
    v31 = this->_f4DC - this->m_fPosY + 50.0;
  this->m_nCoreState = 4;
  this->_f514 = sqrt((v31 + v31) / 490.0) * 490.0;
  ((Actor *)&this->_gap_0278[48])->CompareAction(4, 2);
  ((Actor *)&this->_gap_0278[48])->SetTimeScale(4.0);
  v33 = this->_f4E4 + 0.5;
  this->_f4E4 = v33;
  this->_f4E4 = v33 + 0.5;
  return result;
}

// 0x00416790
void RoleSystem::UpdateAnimation(int a2)
{
  float m_fTargetZ; // eax
  double v5; // st7
  int m_nRoleCount; // ecx
  double v7; // st7
  int *v8; // eax
  int v9; // ecx
  PtrArray *Instance; // eax
  double v11; // st7
  float v12; // edx
  int v13; // ecx
  RoleSystem *v14; // ebx
  int v15; // ecx
  int RolePtr; // edi
  bool v17; // cc
  int v18; // eax
  int v19; // ecx
  float *v20; // eax
  double v21; // st7
  double v22; // st6
  int v23; // [esp-4h] [ebp-38h]
  gbVec3D v24; // [esp+10h] [ebp-24h] BYREF
  float v25; // [esp+1Ch] [ebp-18h]
  float v26; // [esp+20h] [ebp-14h]
  float v27; // [esp+24h] [ebp-10h]
  float v28; // [esp+28h] [ebp-Ch]
  int v29; // [esp+2Ch] [ebp-8h]
  float v30; // [esp+30h] [ebp-4h]
  float a2a; // [esp+38h] [ebp+4h]
  float a2c; // [esp+38h] [ebp+4h]
  int a2b; // [esp+38h] [ebp+4h]
  float a2d; // [esp+38h] [ebp+4h]

  if ( a2 && *(_DWORD *)(a2 + 1388) != 4 && *(_BYTE *)(a2 + 173) != 2 )
  {
    if ( this->_d56C && a2 != this->m_nRoleCount )
      this->GetActiveRole();
    this->_d56C = 1;
    this->m_nRoleCount = a2;
    v24.x = this->m_fTargetX;
    m_fTargetZ = this->m_fTargetZ;
    v24.y = this->m_fTargetY;
    v24.z = m_fTargetZ;
    v24.x = v24.x - *(float *)(a2 + 4);
    v24.y = v24.y - *(float *)(a2 + 8);
    v24.z = m_fTargetZ - *(float *)(a2 + 12);
    v5 = ((gbVec3D *)&v24)->Length();
    m_nRoleCount = this->m_nRoleCount;
    v7 = v5 - *(float *)(m_nRoleCount + 16);
    if ( v7 >= 0.0 )
      a2a = v7;
    else
      a2a = 0.0;
    *(_DWORD *)(m_nRoleCount + 1388) = 4;
    if ( *(_BYTE *)(a2 + 173) == 1 )
    {
      if ( a2a >= (double)*(float *)&g_SceneMgr.m_szUIString[12] )
      {
        v11 = *(float *)(a2 + 20);
        v12 = *(float *)(a2 + 28);
        v26 = 0.0;
        v27 = v12;
        v28 = *(float *)(a2 + 20);
        v13 = *(_DWORD *)(a2 + 24);
        a2c = unk_C1109C + unk_C1109C;
        v30 = v12;
        v29 = v13;
        v27 = v12 * a2c;
        v25 = v11 * a2c + *(float *)(a2 + 4);
        v26 = *(float *)(a2 + 8) + 0.0;
        v27 = v27 + *(float *)(a2 + 12);
        v28 = unk_C1109C * v28;
        v30 = v12 * unk_C1109C;
        v14 = (RoleSystem *)UISceneUpdate();
        RolePtr = v14->GetRolePtr(*(_DWORD *)(a2 + 628));
        a2b = 0;
        do
        {
          LOBYTE(v15) = this->_gap_00AC[0];
          if ( sub_421020(
                 v14,
                 this->m_nState,
                 (__int64)((v25 - *(float *)(RolePtr + 128)) / unk_C1109C),
                 (__int64)((v27 - *(float *)(RolePtr + 136)) / unk_C1109C),
                 v15) )
          {
            break;
          }
          v25 = v28 + v25;
          v17 = ++a2b < 10;
          v27 = v30 + v27;
        }
        while ( v17 );
        v27 = v30 + v27;
        sub_4132B0(
          (int)this,
          (__int64)((v28 + v25 - *(float *)(RolePtr + 128)) / unk_C1109C),
          (__int64)((v27 - *(float *)(RolePtr + 136)) / unk_C1109C),
          1);
      }
      else
      {
        v8 = ((PalScriptMgr *)*(_DWORD *)(this->m_nRoleCount + 264))->Destroy(0);
        *(_DWORD *)this->_gap_0574 = v8;
        if ( v8 )
        {
          sub_416550((int)this, (float *)(this->m_nRoleCount + 4), 1);
          RoleSystemNotify((int)this);
          v9 = *(_DWORD *)this->_gap_0574;
          this->_d56C = 2;
          v23 = v9;
          Instance = (PtrArray *)SoundContext::GetInstance();
          CScreenMode_SetResolution(Instance, 0, v23);
        }
        else
        {
          this->GetActiveRole();
        }
      }
    }
    else
    {
      v18 = this->m_nRoleCount;
      if ( !*(_DWORD *)(v18 + 500) )
      {
        v19 = *(_DWORD *)(v18 + 1268);
        if ( v19 != 3 )
        {
          *(_DWORD *)&this->_gap_0574[4] = v19;
          *(_DWORD *)&this->_gap_0574[12] = *(_DWORD *)(v18 + 8688);
          *(_DWORD *)&this->_gap_0574[8] = *(_DWORD *)(v18 + 1284);
          *(float *)(v18 + 1296) = this->m_fTargetX;
          *(float *)(v18 + 1300) = this->m_fTargetY;
          *(float *)(v18 + 1304) = this->m_fTargetZ;
          v20 = (float *)this->m_nRoleCount;
          v20[324] = v20[324] - v20[1];
          v20[325] = v20[325] - v20[2];
          v20[326] = v20[326] - v20[3];
          sub_4122C0(this->m_nRoleCount);
          RoleSystemNotify(this->m_nRoleCount);
        }
      }
      if ( a2a >= (double)*(float *)&g_SceneMgr.m_szUIString[12] )
      {
        v24.y = v24.y * -1.0;
        v24.z = v24.z * -1.0;
        v21 = v24.x * -1.0 / a2a;
        v24.y = v24.y / a2a;
        v24.z = v24.z / a2a;
        v22 = *(float *)&g_SceneMgr.m_szUIString[12] - 10.0;
        a2d = v22;
        v24.y = v24.y * a2d;
        v24.z = v24.z * a2d;
        v24.x = v21 * v22 + *(float *)(a2 + 4);
        v24.y = v24.y + *(float *)(a2 + 8);
        v24.z = v24.z + *(float *)(a2 + 12);
        sub_412D90((int)this, &v24.x, 1);
      }
      else
      {
        this->_d56C = 2;
      }
    }
  }
}

// 0x00416F10
int RoleSystem::GetActiveRole()
{
  int result; // eax

  result = this->m_nRoleCount;
  this->_d56C = 0;
  if ( result )
  {
    if ( *(_BYTE *)(result + 173) != 1 && !*(_DWORD *)(result + 500) && *(_DWORD *)(result + 1268) != 3 )
    {
      *(_DWORD *)(result + 1284) = *(_DWORD *)&this->_gap_0574[8];
      *(_DWORD *)(this->m_nRoleCount + 1268) = *(_DWORD *)&this->_gap_0574[4];
      sub_416620(this->m_nRoleCount, *(float *)&this->_gap_0574[12], 1);
      result = ((RoleSystem *)this->m_nRoleCount)->UpdateTransform();
    }
    *(_DWORD *)(this->m_nRoleCount + 1388) = 0;
    this->m_nRoleCount = 0;
  }
  return result;
}

// 0x00417AC0
char RoleSystem::SetState(int state)
{
  double v2; // st6
  double v3; // st7
  int v5; // eax
  RoleSystem *v7; // eax
  int v8; // ecx
  int v9; // edi
  int v10; // esi
  RoleSystem *v11; // eax
  int v13; // [esp-10h] [ebp-28h]
  int m_nState; // [esp-4h] [ebp-1Ch]
  int v15; // [esp-4h] [ebp-1Ch]
  int v16; // [esp+10h] [ebp-8h]
  int v17; // [esp+14h] [ebp-4h]
  int statea; // [esp+1Ch] [ebp+4h]

  LOBYTE(v5) = *(_BYTE *)(state + 244);
  if ( (_BYTE)v5 == 14 )
  {
    m_nState = this->m_nState;
    v7 = (RoleSystem *)UISceneUpdate();
    v7->GetRolePtr(m_nState);
    v5 = *(_DWORD *)(state + 236) - *(_DWORD *)(state + 228);
    v17 = v5;
    v16 = *(_DWORD *)(state + 240) - *(_DWORD *)(state + 232);
    if ( v16 >= 0 )
    {
      while ( 1 )
      {
        statea = v5;
        if ( v5 >= 0 )
          break;
LABEL_7:
        if ( --v16 < 0 )
          return v5;
      }
      while ( 1 )
      {
        v8 = v16;
        v9 = v16 + *(_DWORD *)(state + 232);
        LOBYTE(v8) = this->_gap_00AC[0];
        v10 = *(_DWORD *)(state + 228) + statea;
        v15 = v8;
        v13 = this->m_nState;
        v11 = (RoleSystem *)UISceneUpdate();
        if ( sub_421020(v11, v13, v10, v9, v15) )
          break;
        if ( --statea < 0 )
        {
          v5 = v17;
          goto LABEL_7;
        }
      }
      LOBYTE(v5) = sub_4132B0((int)this, v10, v9, 1);
    }
  }
  else if ( this->_d4F0 != 4 )
  {
    sub_424C20(state, v3, v2, this, 1, 0, 0.001);
  }
  return v5;
}

// 0x00419A80
int RoleSystem::GetDirection(float *pOut)
{
  int result; // eax
  _BYTE v4[68]; // [esp+8h] [ebp-4Ch] BYREF
  float v5; // [esp+4Ch] [ebp-8h]

  *pOut = this->m_fPosX;
  pOut[1] = this->m_fPosY;
  pOut[2] = this->m_fPosZ;
  ((gbMatrix4 *)v4)->gbMatrix4();
  result = ((Actor *)&this->_gap_0278[48])->PlayAction((int)v4);
  pOut[1] = v5 + pOut[1];
  return result;
}

// 0x0041BBE0
int RoleSystem::GetCount()
{
  int result; // eax

  result = this->_d4F0;
  if ( result != 4 )
  {
    this->_d4EC = result;
    this->_d4F0 = 4;
    this->_f4E4 = 2.0;
    this->_d4E8 = 0;
    this->_d4CC = 44;
    ((Actor *)&this->_gap_0278[48])->SetVisible((int)aC08);
  }
  return result;
}

// 0x0041C170
int RoleSystem::SetActive(int a2)
{
  int result; // eax

  result = a2;
  *(_DWORD *)&this->_gap_00AC[212] = 0;
  *(_DWORD *)&this->_gap_00AC[208] = a2;
  if ( !a2 )
    return sub_41C1E0((int)this);
  return result;
}

// 0x00420F30
int RoleSystem::GetRolePtr(int index)
{
  return (int)this + 164 * index + 492776;
}
