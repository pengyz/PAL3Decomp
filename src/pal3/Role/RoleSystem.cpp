#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/SoundContext.h"

// Forward declarations for unnamed functions
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

// 0x0040BE50
int * RoleSystem::Init()
{
  int *result; // eax
  int v2; // esi
  int v3; // edx

  result = (int *)((char *)this + 972);
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
    v3 = (int *)*((_DWORD *)this + 230);
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
    v7 = (_BYTE *)*((_DWORD *)this + 218);
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
    v9 = (_BYTE *)*((_DWORD *)this + 215);
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
    v11 = (_BYTE *)*((_DWORD *)this + 221);
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
    v13 = (_BYTE *)*((_DWORD *)this + 224);
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
    v15 = (_BYTE *)*((_DWORD *)this + 227);
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
    result = *((_DWORD *)this + i + 159) + v4;
    *((_DWORD *)this + i + 231) = result;
    if ( a2 || (unsigned int)i > 2 )
      *((_DWORD *)this + i + 243) = result;
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
  int v35; // [esp+14h] [ebp-4h]
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
    v35 = ((operator *)12 * v8)->new();
    v10 = (_DWORD *)v35;
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
    v34[3] = v35 + 12 * v39;
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
    v34[2] = v35 + 12 * v4;
  }
  return result;
}

// 0x00412400
void RoleSystem::RenderRole(void *pStack, int a3)
{
  _BYTE v4[64]; // [esp+38h] [ebp-40h] BYREF

  if ( *((_DWORD *)this + 158) )
  {
    if ( (g_SceneMgr.?[5].?.normal[12].x & 1) == 0 )
    {
      g_SceneMgr.?[5].?.normal[11].x = 0;
      LOBYTE(g_SceneMgr.?[5].?.normal[12].x) |= 1u;
      g_SceneMgr.?[5].?.normal[11].y = 1065353216;
      g_SceneMgr.?[5].?.normal[11].z = 0;
      atexit(nullsub_5);
    }
    ((gbMatrixStack *)pStack)->Push();
    ((gbMatrixStack *)pStack)->Translate((struct gbVec3D *)((char *)this + 160));
    if ( *((_DWORD *)this + 316) == 4 && *((_DWORD *)this + 307) == 11 )
      ((gbMatrixStack *)pStack)->Rotate(*((float *)this + 336), (struct gbVec3D *)this + 108);
    ((gbMatrixStack *)pStack)->Rotate(*((float *)this + 2172), &g_SceneMgr.?[5].?.normal[11]);
    ((gbMatrixStack *)pStack)->Scale(*((float *)this + 160), *((float *)this + 160), *((float *)this + 160));
    *((_DWORD *)this + 36) = ((Actor *)((char *)this + 680))->DispatchAction(a3);
    if ( *((_DWORD *)this + 360) )
    {
      ((gbMatrix4 *)v4)->gbMatrix4();
      if ( *((_BYTE *)this + 1445) )
      {
        ((gbMatrixStack *)pStack)->Push();
        ((gbActor *)*((gbActor **)this + 174))->GetTagNodeTM((struct gbMatrix4 *)v4, aTagWeapon1);
        ((gbMatrixStack *)pStack)->MultMatrix((struct gbMatrix4 *)v4);
        (*(void (**)(_DWORD, _DWORD))(**((_DWORD **)this + 360) + 16))(*((_DWORD *)this + 360), 0);
        ((gbMatrixStack *)pStack)->Pop();
      }
      if ( *((_BYTE *)this + 1444) )
      {
        ((gbMatrixStack *)pStack)->Push();
        ((gbActor *)*((gbActor **)this + 174))->GetTagNodeTM((struct gbMatrix4 *)v4, aTagWeapon2);
        ((gbMatrixStack *)pStack)->MultMatrix((struct gbMatrix4 *)v4);
        (*(void (**)(_DWORD, _DWORD))(**((_DWORD **)this + 360) + 16))(*((_DWORD *)this + 360), 0);
        ((gbMatrixStack *)pStack)->Pop();
      }
    }
    ((gbMatrixStack *)pStack)->Pop();
  }
}

// 0x00412710
int RoleSystem::UpdateTransform()
{
  __int64 v1; // rax
  char v3; // al
  int v4; // [esp-4h] [ebp-Ch]
  int v5; // [esp-4h] [ebp-Ch]
  int v6; // [esp-4h] [ebp-Ch]
  int v7; // [esp-4h] [ebp-Ch]

  v1 = *((unsigned int *)this + 321);
  if ( (unsigned int)v1 > 0x3A )
    *((_DWORD *)this + 321) = 0;
  switch ( *((_DWORD *)this + 321) )
  {
    case 0:
    case 5:
    case 7:
      *((_DWORD *)this + 322) = 0;
      *((_DWORD *)this + 323) = 0;
      *((_DWORD *)this + 324) = 0;
      *((_DWORD *)this + 325) = 0;
      *((_DWORD *)this + 326) = 0;
      *((_DWORD *)this + 327) = 0;
      *((_DWORD *)this + 328) = *((_DWORD *)this + 325);
      *((_DWORD *)this + 329) = *((_DWORD *)this + 326);
      return ((int)this)->UpdatePath(*((_DWORD *)this + 321));
    case 1:
    case 3:
      *((_DWORD *)this + 323) = dword_58B3B4;
      v3 = *((_BYTE *)this + 173);
      if ( v3 == -1 )
      {
        HIDWORD(v1) = dword_58B3DC;
LABEL_7:
        *((_DWORD *)this + 322) = HIDWORD(v1);
        return ((int)this)->UpdatePath(*((_DWORD *)this + 321));
      }
      if ( v3 == 2 )
      {
        if ( *((_DWORD *)this + 354) == 1 )
        {
          if ( *(_BYTE *)(*((_DWORD *)this + 355) + 756) == 1 )
          {
            v5 = *((_DWORD *)this + 321);
            *((_DWORD *)this + 322) = dword_58B33C;
            return ((int)this)->UpdatePath(v5);
          }
          else if ( *(_BYTE *)(*((_DWORD *)this + 355) + 756) == 2 )
          {
            *((_DWORD *)this + 322) = dword_58B350;
            return ((int)this)->UpdatePath(*((_DWORD *)this + 321));
          }
          else
          {
            v4 = *((_DWORD *)this + 321);
            *((_DWORD *)this + 322) = dword_58B328;
            return ((int)this)->UpdatePath(v4);
          }
        }
        else
        {
          switch ( *(_BYTE *)(*((_DWORD *)this + 355) + 755) )
          {
            case 0:
              goto LABEL_7;
            case 1:
              *((_DWORD *)this + 322) = dword_58B29C;
              return ((int)this)->UpdatePath(*((_DWORD *)this + 321));
            case 2:
              v6 = *((_DWORD *)this + 321);
              *((_DWORD *)this + 322) = dword_58B2B0;
              return ((int)this)->UpdatePath(v6);
            default:
              *((_DWORD *)this + 322) = dword_58B2C4;
              return ((int)this)->UpdatePath(*((_DWORD *)this + 321));
          }
        }
      }
      else
      {
        LODWORD(v1) = *((_DWORD *)this + 127);
        v7 = *((_DWORD *)this + 321);
        if ( (_DWORD)v1 == HIDWORD(v1) )
          *((_DWORD *)this + 322) = dword_58B38C;
        else
          *((float *)this + 322) = (float)v1;
        return ((int)this)->UpdatePath(v7);
      }
    case 2:
      *((_DWORD *)this + 322) = dword_58B3F0;
      *((_DWORD *)this + 323) = dword_58B3C8;
      return ((int)this)->UpdatePath(*((_DWORD *)this + 321));
    default:
      return ((int)this)->UpdatePath(*((_DWORD *)this + 321));
  }
}

// 0x00412940
int RoleSystem::UpdatePath(int a2)
{
  int v3; // ebp
  char *v4; // edi
  int result; // eax
  int v6; // [esp-8h] [ebp-14h]

  if ( *((_BYTE *)this + 174) == 49 )
  {
    ((Actor *)(const char *)this + 680)->CompareAction(a2, 2);
    ((Actor *)(gbVisNode **)this + 170)->SetTimeScale(1.0);
    *((_BYTE *)this + 1445) = 0;
    *((_BYTE *)this + 1444) = 0;
    return result;
  }
  v3 = sub_4126D0(a2, *((_BYTE *)this + 173));
  if ( *((_BYTE *)this + 174) == 50 )
    goto LABEL_10;
  if ( v3 == 50 )
  {
    v4 = (char *)this + 680;
    if ( !((Actor *)(int)this + 680)->LoadAction(aZ0, 0) )
      v4->CompareAction(50, 0);
    goto LABEL_12;
  }
  if ( v3 != 52 && v3 != 58 )
  {
LABEL_10:
    v4 = (char *)this + 680;
    v6 = 2;
    goto LABEL_11;
  }
  v4 = (char *)this + 680;
  if ( !((Actor *)(int)this + 680)->LoadAction(aZ4, 0) )
  {
    v6 = 0;
LABEL_11:
    v4->CompareAction(v3, v6);
  }
LABEL_12:
  if ( *((_DWORD *)this + 321) == 2 )
    ((gbVisNode **)v4)->SetTimeScale(2.4000001);
  else
    ((gbVisNode **)v4)->SetTimeScale(1.0);
  *((_BYTE *)this + 1445) = 0;
  *((_BYTE *)this + 1444) = 0;
  return result;
}

// 0x00412E60
int RoleSystem::MoveRole(float *pPos, int a3, int a4, int a5)
{
  int result; // eax
  int v7; // ecx
  void *v8; // eax
  int v9; // ebx
  char *v10; // eax
  int v11; // edx
  int v12; // [esp-18h] [ebp-34h]
  int v13; // [esp-14h] [ebp-30h]
  int v14; // [esp-10h] [ebp-2Ch]
  int v15; // [esp-Ch] [ebp-28h]
  int v16; // [esp-8h] [ebp-24h]
  int v17; // [esp-8h] [ebp-24h]

  *((float *)this + 336) = *pPos;
  result = a3;
  *((float *)this + 337) = pPos[1];
  *((float *)this + 338) = pPos[2];
  v7 = *((_DWORD *)this + 317);
  *((_DWORD *)this + 339) = a3;
  *((_DWORD *)this + 365) = 1;
  if ( v7 != 2 )
  {
    LOBYTE(result) = this->UpdateRole((int)pPos, a3, a4);
    *((_DWORD *)this + 366) = 0;
    return result;
  }
  if ( a3 == *((_DWORD *)this + 157) )
  {
    v16 = *((_DWORD *)this + 157);
    v8 = (void *)UISceneUpdate();
    v9 = v8->GetRolePtr(v16);
    v17 = (__int64)((pPos[2] - *(float *)(v9 + 136)) / *(float *)&g_SceneMgr.m_info[52492]);
    v15 = (__int64)((*pPos - *(float *)(v9 + 128)) / *(float *)&g_SceneMgr.m_info[52492]);
    v14 = (__int64)((*((float *)this + 3) - *(float *)(v9 + 136)) / *(float *)&g_SceneMgr.m_info[52492]);
    v13 = (__int64)((*((float *)this + 1) - *(float *)(v9 + 128)) / *(float *)&g_SceneMgr.m_info[52492]);
    v12 = *((_DWORD *)this + 157);
    v10 = (char *)UISceneUpdate();
    if ( sub_4215B0(v10, v12, v13, v14, v15, v17) )
    {
      *((_DWORD *)this + 1138) = 2;
      *((_DWORD *)this + 370) = *((_DWORD *)this + 1);
      *((_DWORD *)this + 371) = *((_DWORD *)this + 2);
      *((_DWORD *)this + 372) = *((_DWORD *)this + 3);
      *((float *)this + 373) = *pPos;
      *((float *)this + 374) = pPos[1];
      *((float *)this + 375) = pPos[2];
      return sub_407DC0((_DWORD *)this + 370);
    }
    result = a3;
  }
  if ( a5 || (v11 = *((_DWORD *)this + 366) + 1, *((_DWORD *)this + 366) = v11, v11 > 30) )
  {
    *((_DWORD *)this + 366) = 0;
    LOBYTE(result) = this->UpdateRole((int)pPos, result, a4);
  }
  return result;
}

// 0x00413010
char RoleSystem::UpdateRole(int a2, int a3, int a4)
{
  int v5; // eax
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
  int v18; // [esp-4h] [ebp-48h]
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

  if ( a3 == *((_DWORD *)this + 157) )
  {
    LOBYTE(v5) = sub_412D90((int)this, (float *)a2, a4);
  }
  else
  {
    v18 = *((_DWORD *)this + 157);
    v6 = (RoleSystem *)UISceneUpdate();
    RolePtr = v6->GetRolePtr(v18);
    v21 = RolePtr;
    v24 = (__int64)((*((float *)this + 1) - *(float *)(RolePtr + 128)) / *(float *)&g_SceneMgr.m_info[52492]);
    v8 = v22;
    v9 = 0x7FFFF;
    v25 = (__int64)((*((float *)this + 3) - *(float *)(RolePtr + 136)) / *(float *)&g_SceneMgr.m_info[52492]);
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
          *((_DWORD *)this + 340) = v19;
        }
      }
      v10 += 4;
      LOBYTE(v5) = ++v19;
    }
    while ( v19 < 8 );
    if ( v9 <= 32 )
    {
      v29 = 0.0;
      v28 = ((double)v22 + 0.5) * *(float *)&g_SceneMgr.m_info[52492] + *(float *)(RolePtr + 128);
      v30 = ((double)v23 + 0.5) * *(float *)&g_SceneMgr.m_info[52492] + *(float *)(RolePtr + 136);
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
        sub_413C00((int)this, a3, *((_DWORD *)this + 340));
        LOBYTE(v5) = sub_412D90((int)this, v26, a4);
      }
      else
      {
        v16 = v27;
        *((float *)this + 336) = v26[0];
        *((_DWORD *)this + 337) = 0;
        *((float *)this + 338) = v16;
        if ( sub_408460(
               &g_SceneMgr.m_info[51808],
               *((_DWORD *)this + 157),
               (float *)this + 1,
               v26,
               (_DWORD *)this + 370,
               *((_BYTE *)this + 172)) )
        {
          *((_DWORD *)this + 317) = 7;
          *((_DWORD *)this + 321) = a4;
          this->UpdateTransform();
          *((_DWORD *)this + 336) = *(_DWORD *)a2;
          *((_DWORD *)this + 337) = *(_DWORD *)(a2 + 4);
          v5 = *(_DWORD *)(a2 + 8);
          *((_DWORD *)this + 338) = v5;
          *((_DWORD *)this + 337) = 0;
          *((_DWORD *)this + 339) = a3;
        }
        else
        {
          LOBYTE(v5) = sub_4142E0(this);
        }
      }
    }
  }
  return v5;
}

// 0x00414980
void RoleSystem::GetPosition(void *pOut, int a3)
{
  float *v4; // esi
  double v5; // st7

  v4 = (float *)((char *)this + 1308);
  *((_DWORD *)this + 327) = *(_DWORD *)pOut;
  *((_DWORD *)this + 328) = *((_DWORD *)pOut + 1);
  *((_DWORD *)this + 329) = *((_DWORD *)pOut + 2);
  *((_DWORD *)this + 321) = a3;
  this->UpdateTransform();
  if ( a3 )
  {
    *((_DWORD *)this + 328) = 0;
    ((gbVec3D *)v4)->Normalize();
    v5 = *((float *)this + 322);
    * v4 = (*)v5 * *v4;
    v4[1] = v5 * v4[1];
    v4[2] = v5 * v4[2];
    *((_DWORD *)this + 317) = 12;
  }
  else
  {
    *((_DWORD *)this + 317) = 0;
  }
}

// 0x00414A30
int RoleSystem::PathFind(float *pTarget)
{
  int v3; // eax
  double v4; // st7
  double v5; // st7
  float v6; // ecx
  double v7; // st7
  double v8; // st7
  float *v9; // ebp
  float v10; // ecx
  void *v11; // eax
  void *v12; // eax
  int v13; // edi
  int v14; // ebx
  double v15; // st7
  __int64 v16; // rax
  double v17; // st7
  char *v18; // eax
  double v19; // st7
  int v20; // ecx
  int v21; // edx
  int v22; // eax
  float v23; // eax
  char *v24; // eax
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
  int v35; // [esp-10h] [ebp-54h]
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
  float v49; // [esp+2Ch] [ebp-18h] BYREF
  float v50; // [esp+30h] [ebp-14h]
  float v51; // [esp+34h] [ebp-10h]
  float v52; // [esp+38h] [ebp-Ch] BYREF
  float v53; // [esp+3Ch] [ebp-8h]
  float v54; // [esp+40h] [ebp-4h]

  v3 = *((_DWORD *)this + 316);
  *((_DWORD *)this + 307) = 0;
  *((_DWORD *)this + 308) = 0;
  if ( v3 != 4 )
    *((_DWORD *)this + 315) = v3;
  *((_DWORD *)this + 316) = 4;
  v52 = *pTarget - *((float *)this + 1);
  v4 = pTarget[1] - *((float *)this + 2);
  v49 = v52;
  v53 = v4;
  v5 = pTarget[2] - *((float *)this + 3);
  v6 = v53;
  pTarget[1] = 0.0;
  v50 = v6;
  v54 = v5;
  v51 = v54;
  v7 = ((gbVec3D *)&v49)->Length();
  if ( v7 <= *(float *)&g_SceneMgr.m_info[51640] )
  {
    v9 = (float *)((char *)this + 1240);
    *((float *)this + 310) = *pTarget;
    *((float *)this + 311) = pTarget[1];
    *((float *)this + 312) = pTarget[2];
  }
  else
  {
    v8 = *(float *)&g_SceneMgr.m_info[51640] / v7;
    v9 = (float *)((char *)this + 1240);
    v49 = v49 * v8;
    v50 = v50 * v8;
    v49 = v49 + *((float *)this + 1);
    v50 = v50 + *((float *)this + 2);
    v10 = v50;
    v7 = v8 * v51 + *((float *)this + 3);
    *((float *)this + 310) = v49;
    *((float *)this + 311) = v10;
    v51 = v7;
    *((float *)this + 312) = v7;
  }
  v35 = *((_DWORD *)this + 157);
  v11 = (void *)UISceneUpdate();
  sub_421440(v11, v35, v9, 0, 0);
  *((float *)this + 311) = v7;
  if ( !g_SceneMgr.m_info[54106] )
  {
    v42 = *((_DWORD *)this + 157);
    v12 = (void *)UISceneUpdate();
    v13 = v12->GetRolePtr(v42);
    v14 = (__int64)((*((float *)this + 1) - *(float *)(v13 + 128)) / *(float *)&g_SceneMgr.m_info[52492]);
    v15 = *v9 - *(float *)(v13 + 128);
    LODWORD(v47) = (__int64)((*((float *)this + 3) - *(float *)(v13 + 136)) / *(float *)&g_SceneMgr.m_info[52492]);
    v16 = (__int64)(v15 / *(float *)&g_SceneMgr.m_info[52492]);
    v17 = v9[2] - *(float *)(v13 + 136);
    v45 = v16;
    v40 = (__int64)(v17 / *(float *)&g_SceneMgr.m_info[52492]);
    v38 = v16;
    v36 = LODWORD(v47);
    v34 = *((_DWORD *)this + 157);
    v18 = (char *)UISceneUpdate();
    if ( !sub_4218B0(v18, v34, v14, v36, v38, v40, &v43) )
    {
      v19 = 0.0;
      v20 = v43;
      v21 = v44;
      v46 = ((double)v43 + 0.5) * *(float *)&g_SceneMgr.m_info[52492] + *(float *)(v13 + 128);
      v48 = ((double)v44 + 0.5) * *(float *)&g_SceneMgr.m_info[52492] + *(float *)(v13 + 136);
      if ( v43 >= 0 )
      {
        v22 = *(_DWORD *)(v13 + 152);
        if ( v43 < v22 && v44 >= 0 && v44 < *(_DWORD *)(v13 + 156) )
          v19 = *(float *)(*(_DWORD *)(v13 + 160) + 8 * (v43 + v44 * v22));
      }
      v23 = v46;
      v9[1] = v19;
      *v9 = v23;
      v41 = v21;
      v9[2] = v48;
      v39 = v20;
      v37 = *((_DWORD *)this + 157);
      v24 = (char *)UISceneUpdate();
      *((float *)this + 311) = sub_421230(v24, v37, v39, v41, 0);
    }
  }
  *((float *)this + 324) = *v9;
  *((float *)this + 325) = v9[1];
  *((float *)this + 326) = v9[2];
  *((float *)this + 324) = *((float *)this + 324) - *((float *)this + 40);
  *((float *)this + 325) = *((float *)this + 325) - *((float *)this + 41);
  *((float *)this + 326) = *((float *)this + 326) - *((float *)this + 42);
  *((_DWORD *)this + 325) = 0;
  ((RoleSystem *)((char *)this + 1296))->Normalize();
  sub_4122C0((int)this);
  v25 = sqrt((50.0 + 50.0) / 490.0);
  *((float *)this + 313) = v25;
  v26 = fabs(*((float *)this + 311) - *((float *)this + 41));
  *((_DWORD *)this + 314) = 0;
  *((float *)this + 313) = sqrt((v26 + 50.0 + v26 + 50.0) / 490.0) + v25;
  v46 = *v9 - *((float *)this + 40);
  v27 = v9[1] - *((float *)this + 41);
  v52 = v46;
  v47 = v27;
  v28 = v9[2] - *((float *)this + 42);
  *((_DWORD *)this + 325) = 0;
  v48 = v28;
  v29 = v48;
  *((float *)this + 324) = v52;
  v54 = v29;
  v53 = 0.0;
  *((float *)this + 326) = v29;
  ((RoleSystem *)((char *)this + 1296))->Normalize();
  v30 = ((gbVec3D *)&v52)->Length() / *((float *)this + 313);
  *((float *)this + 324) = v30 * *((float *)this + 324);
  *((float *)this + 325) = v30 * *((float *)this + 325);
  *((float *)this + 326) = v30 * *((float *)this + 326);
  v31 = 50.0;
  if ( *((float *)this + 311) > (double)*((float *)this + 41) )
    v31 = *((float *)this + 311) - *((float *)this + 41) + 50.0;
  *((_DWORD *)this + 321) = 4;
  *((float *)this + 325) = sqrt((v31 + v31) / 490.0) * 490.0;
  ((Actor *)(const char *)this + 680)->CompareAction(4, 2);
  ((Actor *)(gbVisNode **)this + 170)->SetTimeScale(4.0);
  v33 = *((float *)this + 313) + 0.5;
  *((float *)this + 313) = v33;
  *((float *)this + 313) = v33 + 0.5;
  return result;
}

// 0x00416790
void RoleSystem::UpdateAnimation(int a2)
{
  float v4; // eax
  double v5; // st7
  int v6; // ecx
  double v7; // st7
  _DWORD *v8; // eax
  int v9; // ecx
  int *Instance; // eax
  double v11; // st7
  float v12; // edx
  int v13; // ecx
  void *v14; // ebx
  int v15; // ecx
  int v16; // edi
  bool v17; // cc
  _DWORD *v18; // eax
  int v19; // ecx
  float *v20; // eax
  double v21; // st7
  double v22; // st6
  int v23; // [esp-4h] [ebp-38h]
  float v24; // [esp+10h] [ebp-24h] BYREF
  float v25; // [esp+14h] [ebp-20h]
  float v26; // [esp+18h] [ebp-1Ch]
  float v27; // [esp+1Ch] [ebp-18h]
  float v28; // [esp+20h] [ebp-14h]
  float v29; // [esp+24h] [ebp-10h]
  float v30; // [esp+28h] [ebp-Ch]
  int v31; // [esp+2Ch] [ebp-8h]
  float v32; // [esp+30h] [ebp-4h]
  float a2a; // [esp+38h] [ebp+4h]
  float a2c; // [esp+38h] [ebp+4h]
  int a2b; // [esp+38h] [ebp+4h]
  float a2d; // [esp+38h] [ebp+4h]

  if ( a2 && *(_DWORD *)(a2 + 1388) != 4 && *(_BYTE *)(a2 + 173) != 2 )
  {
    if ( *((_DWORD *)this + 347) && a2 != *((_DWORD *)this + 348) )
      this->GetActiveRole();
    *((_DWORD *)this + 347) = 1;
    *((_DWORD *)this + 348) = a2;
    v24 = *((float *)this + 1);
    v4 = *((float *)this + 3);
    v25 = *((float *)this + 2);
    v26 = v4;
    v24 = v24 - *(float *)(a2 + 4);
    v25 = v25 - *(float *)(a2 + 8);
    v26 = v4 - *(float *)(a2 + 12);
    v5 = ((gbVec3D *)&v24)->Length();
    v6 = *((_DWORD *)this + 348);
    v7 = v5 - *(float *)(v6 + 16);
    if ( v7 >= 0.0 )
      a2a = v7;
    else
      a2a = 0.0;
    *(_DWORD *)(v6 + 1388) = 4;
    if ( *(_BYTE *)(a2 + 173) == 1 )
    {
      if ( a2a >= (double)*(float *)&g_SceneMgr.m_info[51636] )
      {
        v11 = *(float *)(a2 + 20);
        v12 = *(float *)(a2 + 28);
        v28 = 0.0;
        v29 = v12;
        v30 = *(float *)(a2 + 20);
        v13 = *(_DWORD *)(a2 + 24);
        a2c = *(float *)&g_SceneMgr.m_info[52492] + *(float *)&g_SceneMgr.m_info[52492];
        v32 = v12;
        v31 = v13;
        v29 = v12 * a2c;
        v27 = v11 * a2c + *(float *)(a2 + 4);
        v28 = *(float *)(a2 + 8) + 0.0;
        v29 = v29 + *(float *)(a2 + 12);
        v30 = *(float *)&g_SceneMgr.m_info[52492] * v30;
        v32 = v12 * *(float *)&g_SceneMgr.m_info[52492];
        v14 = (void *)UISceneUpdate();
        v16 = v14->GetRolePtr(*(_DWORD *)(a2 + 628));
        a2b = 0;
        do
        {
          LOBYTE(v15) = *((_BYTE *)this + 172);
          if ( sub_421020(
                 (char *)v14,
                 *((_DWORD *)this + 157),
                 (__int64)((v27 - *(float *)(v16 + 128)) / *(float *)&g_SceneMgr.m_info[52492]),
                 (__int64)((v29 - *(float *)(v16 + 136)) / *(float *)&g_SceneMgr.m_info[52492]),
                 v15) )
          {
            break;
          }
          v27 = v30 + v27;
          v17 = ++a2b < 10;
          v29 = v32 + v29;
        }
        while ( v17 );
        v29 = v32 + v29;
        sub_4132B0(
          (int)this,
          (__int64)((v30 + v27 - *(float *)(v16 + 128)) / *(float *)&g_SceneMgr.m_info[52492]),
          (__int64)((v29 - *(float *)(v16 + 136)) / *(float *)&g_SceneMgr.m_info[52492]),
          1);
      }
      else
      {
        v8 = ((PalScriptMgr *)*(_DWORD *)(*((_DWORD *)this + 348) + 264))->Destroy(0);
        *((_DWORD *)this + 349) = v8;
        if ( v8 )
        {
          sub_416550((int)this, (float *)(*((_DWORD *)this + 348) + 4), 1);
          RoleSystemNotify((int)this);
          v9 = *((_DWORD *)this + 349);
          *((_DWORD *)this + 347) = 2;
          v23 = v9;
          Instance = (int *)SoundContext::GetInstance();
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
      v18 = (_DWORD *)*((_DWORD *)this + 348);
      if ( !v18[125] )
      {
        v19 = v18[317];
        if ( v19 != 3 )
        {
          *((_DWORD *)this + 350) = v19;
          *((_DWORD *)this + 352) = v18[2172];
          *((_DWORD *)this + 351) = v18[321];
          v18[324] = *((_DWORD *)this + 1);
          v18[325] = *((_DWORD *)this + 2);
          v18[326] = *((_DWORD *)this + 3);
          v20 = (float *)*((_DWORD *)this + 348);
          v20[324] = v20[324] - v20[1];
          v20[325] = v20[325] - v20[2];
          v20[326] = v20[326] - v20[3];
          sub_4122C0(*((_DWORD *)this + 348));
          RoleSystemNotify(*((_DWORD *)this + 348));
        }
      }
      if ( a2a >= (double)*(float *)&g_SceneMgr.m_info[51636] )
      {
        v25 = v25 * -1.0;
        v26 = v26 * -1.0;
        v21 = v24 * -1.0 / a2a;
        v25 = v25 / a2a;
        v26 = v26 / a2a;
        v22 = *(float *)&g_SceneMgr.m_info[51636] - 10.0;
        a2d = v22;
        v25 = v25 * a2d;
        v26 = v26 * a2d;
        v24 = v21 * v22 + *(float *)(a2 + 4);
        v25 = v25 + *(float *)(a2 + 8);
        v26 = v26 + *(float *)(a2 + 12);
        sub_412D90((int)this, &v24, 1);
      }
      else
      {
        *((_DWORD *)this + 347) = 2;
      }
    }
  }
}

// 0x00416F10
int RoleSystem::GetActiveRole()
{
  int result; // eax

  result = *((_DWORD *)this + 348);
  *((_DWORD *)this + 347) = 0;
  if ( result )
  {
    if ( *(_BYTE *)(result + 173) != 1 && !*(_DWORD *)(result + 500) && *(_DWORD *)(result + 1268) != 3 )
    {
      *(_DWORD *)(result + 1284) = *((_DWORD *)this + 351);
      *(_DWORD *)(*((_DWORD *)this + 348) + 1268) = *((_DWORD *)this + 350);
      sub_416620(*((_DWORD *)this + 348), *((float *)this + 352), 1);
      result = ((RoleSystem *)*((_DWORD *)this + 348))->UpdateTransform();
    }
    *(_DWORD *)(*((_DWORD *)this + 348) + 1388) = 0;
    *((_DWORD *)this + 348) = 0;
  }
  return result;
}

// 0x00417AC0
char RoleSystem::SetState(int state)
{
  int v3; // eax
  void *v5; // eax
  int v6; // ecx
  int v7; // edi
  int v8; // esi
  char *v9; // eax
  int v11; // [esp-10h] [ebp-28h]
  int v12; // [esp-4h] [ebp-1Ch]
  int v13; // [esp-4h] [ebp-1Ch]
  int v14; // [esp+10h] [ebp-8h]
  int v15; // [esp+14h] [ebp-4h]
  int statea; // [esp+1Ch] [ebp+4h]

  LOBYTE(v3) = *(_BYTE *)(state + 244);
  if ( (_BYTE)v3 == 14 )
  {
    v12 = *((_DWORD *)this + 157);
    v5 = (void *)UISceneUpdate();
    v5->GetRolePtr(v12);
    v3 = *(_DWORD *)(state + 236) - *(_DWORD *)(state + 228);
    v15 = v3;
    v14 = *(_DWORD *)(state + 240) - *(_DWORD *)(state + 232);
    if ( v14 >= 0 )
    {
      while ( 1 )
      {
        statea = v3;
        if ( v3 >= 0 )
          break;
LABEL_7:
        if ( --v14 < 0 )
          return v3;
      }
      while ( 1 )
      {
        v6 = v14;
        v7 = v14 + *(_DWORD *)(state + 232);
        LOBYTE(v6) = *((_BYTE *)this + 172);
        v8 = *(_DWORD *)(state + 228) + statea;
        v13 = v6;
        v11 = *((_DWORD *)this + 157);
        v9 = (char *)UISceneUpdate();
        if ( sub_421020(v9, v11, v8, v7, v13) )
          break;
        if ( --statea < 0 )
        {
          v3 = v15;
          goto LABEL_7;
        }
      }
      LOBYTE(v3) = sub_4132B0((int)this, v8, v7, 1);
    }
  }
  else if ( *((_DWORD *)this + 316) != 4 )
  {
    sub_424C20(state, (int)this, 1, 0, 0.001);
  }
  return v3;
}

// 0x00419A80
int RoleSystem::GetDirection(float *pOut)
{
  int result; // eax
  _BYTE v4[76]; // [esp+8h] [ebp-4Ch] BYREF

  * pOut = (*)*((float *)this + 40);
  pOut[1] = *((float *)this + 41);
  pOut[2] = *((float *)this + 42);
  ((gbMatrix4 *)v4)->gbMatrix4();
  result = ((Actor *)((char *)this + 680))->PlayAction((int)v4);
  pOut[1] = *(float *)&v4[68] + pOut[1];
  return result;
}

// 0x0041BBE0
int RoleSystem::GetCount()
{
  int result; // eax

  result = *((_DWORD *)this + 316);
  if ( result != 4 )
  {
    *((_DWORD *)this + 315) = result;
    *((_DWORD *)this + 316) = 4;
    *((_DWORD *)this + 313) = 0x40000000;
    *((_DWORD *)this + 314) = 0;
    *((_DWORD *)this + 307) = 44;
    LOBYTE(result) = ((Actor *)(int)this + 680)->SetVisible(aC08, 0, 0);
  }
  return result;
}

// 0x0041C170
int RoleSystem::SetActive(int a2)
{
  int result; // eax

  result = a2;
  *((_DWORD *)this + 96) = 0;
  *((_DWORD *)this + 95) = a2;
  if ( !a2 )
    return sub_41C1E0((int)this);
  return result;
}

// 0x00420F30
int RoleSystem::GetRolePtr(int index)
{
  return (int)this + 164 * index + 492776;
}
