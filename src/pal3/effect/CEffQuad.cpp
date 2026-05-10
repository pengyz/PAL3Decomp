#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffQuad.h"
#include "pal3/gen/CEffect.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4D1EF0(...);
int sub_4D1FD0(...);
int sub_4D22F0(...);
int sub_4D2E10(...);
int sub_4D3010(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co_16[];
extern char aNewFailInCeffq[];
extern int dword_17A7BC0;
extern int unk_FFFFFF;

// 0x004D1090
char CEffQuad::Create(int a2)
{
  int v3; // ebp
  _DWORD *v4; // eax
  int v5; // ebp
  int v6; // ebx
  int v7; // ebp
  _DWORD *v8; // eax
  int v9; // ecx
  int i; // eax
  _DWORD *v11; // eax
  int v12; // ebx
  int v13; // edi
  int v14; // edi
  int v15; // edx
  int v16; // eax
  int v17; // ecx
  int v19; // edi
  size_t v20; // [esp-4h] [ebp-824h]
  _DWORD *v21; // [esp+10h] [ebp-810h]
  char pExceptionObject[1024]; // [esp+14h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+414h] [ebp-40Ch] BYREF
  int v24; // [esp+81Ch] [ebp-4h]

  *((_BYTE *)this + 50) = 1;
  *((_DWORD *)this + 53) = *(CEffQuad *)(a2 + 215);
  *((_DWORD *)this + 52) = *(CEffQuad *)(a2 + 213);
  *((_DWORD *)this + 54) = *(CEffQuad *)(a2 + 176);
  *((_DWORD *)this + 14) = &unk_FFFFFF;
  sub_4D1FD0((char *)this, *(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  *((_DWORD *)this + 39) = operator new(80 * *(_DWORD *)(a2 + 208));
  v3 = *(_DWORD *)(a2 + 208);
  v4 = (_DWORD *)operator new(68 * v3);
  v21 = v4;
  v24 = 0;
  if ( v4 )
  {
    v5 = v3 - 1;
    v6 = (int)v4;
    if ( v5 >= 0 )
    {
      v7 = v5 + 1;
      do
      {
        ArraySort(v6, 12, 4, gbVec3D::`default constructor closure');
        v6 += 68;
        --v7;
      }
      while ( v7 );
      v4 = v21;
    }
  }
  else
  {
    v4 = 0;
  }
  *((_DWORD *)this + 40) = v4;
  v20 = 4 * *(_DWORD *)(a2 + 208);
  v24 = -1;
  v8 = (_DWORD *)operator new(v20);
  v9 = *((_DWORD *)this + 39);
  *((_DWORD *)this + 41) = v8;
  if ( !v9 || !*((_DWORD *)this + 40) || !v8 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffq, aDProjectPal3Co_16, 127),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *((_DWORD *)this + 17) = *(_DWORD *)(a2 + 208);
  sub_4D1EF0(this);
  for ( i = 0; i < *((_DWORD *)this + 17); ++i )
    *(_DWORD *)(*((_DWORD *)this + 41) + 4 * i) = i;
  this->ToNextFrame(a2 + 40);
  v11 = (_DWORD *)operator new(0x4C0u);
  *((_DWORD *)this + 6) = v11;
  if ( v11 )
  {
    v12 = 0;
    v13 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v13 + *((_DWORD *)this + 6)) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v13 + *((_DWORD *)this + 6)) )
        break;
      v13 += 152;
      ++v12;
      if ( v13 >= 1216 )
      {
        v14 = 0;
        *((_DWORD *)this + 10) = 8;
        *((_DWORD *)this + 11) = 10;
        v15 = 0;
        do
        {
          *(_BYTE *)(v15 + *((_DWORD *)this + 6) + 148) = 0;
          v16 = 0;
          if ( *((int *)this + 11) > 0 )
          {
            v17 = 0;
            do
            {
              ++v16;
              v17 += 72;
              *(_BYTE *)(*(_DWORD *)(v15 + *((_DWORD *)this + 6)) + v17 - 8) = 0;
            }
            while ( v16 < *((_DWORD *)this + 11) );
          }
          ++v14;
          v15 += 152;
        }
        while ( v14 < *((_DWORD *)this + 10) );
        return 1;
      }
    }
    if ( v12 > 0 && v12 - 1 >= 0 )
    {
      v19 = 152 * (v12 - 1);
      do
      {
        operator delete(*(void **)(v19 + *((_DWORD *)this + 6)));
        v19 -= 152;
        --v12;
      }
      while ( v12 );
    }
    operator delete(*((void **)this + 6));
  }
  return 1;
}

// 0x004D1BE0
char CEffQuad::DestroyOneQuad(const void *a2)
{
  int v3; // ecx
  int v4; // ebp
  int v5; // esi
  _BYTE *i; // eax
  int v8; // eax
  int v9; // ecx

  v3 = *((_DWORD *)this + 17);
  if ( *((_DWORD *)this + 16) > v3 )
    return 0;
  v4 = 0;
  if ( v3 <= 0 )
    return 0;
  v5 = *((_DWORD *)this + 39);
  for ( i = (_BYTE *)(v5 + 4); *i; i += 80 )
  {
    if ( ++v4 >= v3 )
      return 0;
  }
  v8 = 80 * v4;
  qmemcpy((void *)(v5 + 80 * v4), a2, 0x50u);
  *(_BYTE *)(v8 + *((_DWORD *)this + 39) + 4) = 1;
  *(_DWORD *)(v8 + *((_DWORD *)this + 39) + 12) = 0;
  *(_BYTE *)(v8 + *((_DWORD *)this + 39) + 6) = 0;
  *(_BYTE *)(v8 + *((_DWORD *)this + 39) + 7) = 0;
  v9 = *((_DWORD *)this + 15);
  if ( v4 > v9 - 1 )
    *((_DWORD *)this + 15) = v9 + 1;
  *(_DWORD *)(v8 + *((_DWORD *)this + 39)) = *((_DWORD *)this + 16);
  *(_DWORD *)(*((_DWORD *)this + 41) + 4 * (*((_DWORD *)this + 16))++) = v4;
  this->SetQuad(v4);
  *((_DWORD *)this + 18) = v4;
  return 1;
}

// 0x004D1CA0
int CEffQuad::SetQuad(int a2)
{
  int v2; // edx
  int result; // eax
  double v4; // st7

  v2 = 80 * a2 + *((_DWORD *)this + 39);
  result = 68 * *(_DWORD *)v2;
  *(_DWORD *)(result + *((_DWORD *)this + 40) + 64) = *(_DWORD *)(v2 + 76);
  if ( *((_BYTE *)this + 51) )
  {
    *(float *)(result + *((_DWORD *)this + 40)) = *(float *)(v2 + 16) - *(float *)(v2 + 28);
    *(float *)(result + *((_DWORD *)this + 40) + 12) = *(float *)(v2 + 28) + *(float *)(v2 + 16);
    *(float *)(result + *((_DWORD *)this + 40) + 24) = *(float *)(v2 + 28) + *(float *)(v2 + 16);
    *(float *)(result + *((_DWORD *)this + 40) + 36) = *(float *)(v2 + 16) - *(float *)(v2 + 28);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 4) = *(_DWORD *)(v2 + 20);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 16) = *(_DWORD *)(v2 + 20);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 28) = *(_DWORD *)(v2 + 20);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 40) = *(_DWORD *)(v2 + 20);
    *(float *)(result + *((_DWORD *)this + 40) + 8) = *(float *)(v2 + 32) + *(float *)(v2 + 24);
    *(float *)(result + *((_DWORD *)this + 40) + 20) = *(float *)(v2 + 32) + *(float *)(v2 + 24);
    *(float *)(result + *((_DWORD *)this + 40) + 32) = *(float *)(v2 + 24) - *(float *)(v2 + 32);
    v4 = *(float *)(v2 + 24) - *(float *)(v2 + 32);
  }
  else
  {
    *(float *)(result + *((_DWORD *)this + 40)) = -*(float *)(v2 + 28);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 12) = *(_DWORD *)(v2 + 28);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 24) = *(_DWORD *)(v2 + 28);
    *(float *)(result + *((_DWORD *)this + 40) + 36) = -*(float *)(v2 + 28);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 4) = 0;
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 16) = 0;
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 28) = 0;
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 40) = 0;
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 8) = *(_DWORD *)(v2 + 32);
    *(_DWORD *)(result + *((_DWORD *)this + 40) + 20) = *(_DWORD *)(v2 + 32);
    *(float *)(result + *((_DWORD *)this + 40) + 32) = -*(float *)(v2 + 32);
    v4 = -*(float *)(v2 + 32);
  }
  *(float *)(result + *((_DWORD *)this + 40) + 44) = v4;
  *(_DWORD *)(result + *((_DWORD *)this + 40) + 48) = 0;
  *(_DWORD *)(result + *((_DWORD *)this + 40) + 56) = 0;
  *(_DWORD *)(result + *((_DWORD *)this + 40) + 52) = 0;
  *(_DWORD *)(result + *((_DWORD *)this + 40) + 60) = 0;
  return result;
}

// 0x004D1E50
_DWORD * CEffQuad::DestroyAllQuad(int a2)
{
  _DWORD *result; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // ebx
  int v6; // ecx

  result = this;
  v3 = *((_DWORD *)this + 39) + 80 * a2;
  v4 = result[16] - 1;
  v5 = *(_DWORD *)v3;
  *(_BYTE *)(v3 + 4) = 0;
  if ( v4 != v5 )
  {
    qmemcpy((void *)(result[40] + 68 * v5), (const void *)(result[40] + 68 * v4), 0x44u);
    *(_DWORD *)(80 * *(_DWORD *)(result[41] + 4 * v4) + result[39]) = v5;
    *(_DWORD *)(result[41] + 4 * v5) = *(_DWORD *)(result[41] + 4 * v4);
  }
  v6 = result[15] - 1;
  --result[16];
  if ( a2 == v6 )
    result[15] = v6;
  if ( a2 == result[18] )
    result[18] = -1;
  return result;
}

// 0x004D1F30
_DWORD * CEffQuad::ToNextFrame(int a2)
{
  gbTexture *v3; // eax
  _DWORD *result; // eax
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(***((_DWORD ***)this + 1) + 8))(**((_DWORD **)this + 1), a2);
  *((_DWORD *)this + 1066) = v3;
  v3->LoadTexture(1);
  result = (_DWORD *)operator new(0x44u);
  if ( result )
  {
    v5 = *((_DWORD *)this + 1066);
    result[16] = 1;
    *result = v5;
  }
  else
  {
    result = 0;
  }
  *((_DWORD *)this + 1067) = result;
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_16, 540),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004D2080
int CEffQuad::CreateTask(_DWORD *a2)
{
  int *v2; // ebp
  int v3; // edx
  int result; // eax
  int v5; // esi
  _BYTE *i; // ecx
  int v7; // ebx
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // esi
  _BYTE *v12; // edi
  int (**v13)(CEffect *, int); // edx
  unsigned int v14; // eax
  int v15; // edx
  int v16; // ecx
  _DWORD *v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // esi
  _BYTE *v21; // edi
  int (**v22)(CEffect *, int); // edx
  unsigned int v23; // eax
  int v24; // edx
  int v25; // ecx
  _DWORD *v26; // eax
  int v27; // [esp+10h] [ebp-Ch]

  v2 = (int *)(this + 12);
  v3 = 0;
  *((_DWORD *)this + 14) = a2[20];
  result = *((_DWORD *)this + 10);
  if ( result > 0 )
  {
    v5 = *((_DWORD *)this + 6);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v3 >= result )
        return result;
    }
    v27 = v3;
    v7 = 152 * v3;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(v2[3] + v7 + 148) = 1;
    *(_BYTE *)(v2[3] + v7 + 149) = 1;
    v8 = ++dword_17A7BC0;
    if ( !dword_17A7BC0 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      dword_17A7BC0 = 1;
    }
    *(_DWORD *)(v2[3] + v7 + 16) = v8;
    *(_DWORD *)(v2[3] + v7 + 4) = 0;
    *(_DWORD *)(v2[3] + v7 + 8) = 0;
    *(_DWORD *)(v2[3] + v7 + 20) = 0;
    if ( a2 )
    {
      result = v2[3];
      qmemcpy((void *)(result + v7 + 24), a2, 0x7Cu);
    }
    else
    {
      result = 0;
      memset((void *)(v2[3] + v7 + 24), 0, 0x7Cu);
    }
    ++v2[6];
    if ( v3 != -1 )
    {
      v9 = v2[8];
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(v7 + v2[3]);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int (**)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *((_BYTE *)v13 + 65) = 0;
        * v13 = (*)CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        v13[1] = 0;
        v13[2] = (int (*)(CEffect *, int))2;
        v14 = ++dword_17A7BC0;
        if ( !dword_17A7BC0 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          dword_17A7BC0 = 1;
        }
        v13[3] = (int (*)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        v15 = v2[3];
        v16 = *(_DWORD *)(v7 + v15 + 4);
        v17 = (_DWORD *)(v7 + v15 + 4);
        v3 = v27;
        * v17 = (*)v16 + 1;
      }
LABEL_22:
      v18 = v2[8];
      v19 = 0;
      if ( v18 > 0 )
      {
        v20 = *(_DWORD *)(v2[3] + v7);
        v21 = (_BYTE *)(v20 + 64);
        while ( *v21 )
        {
          ++v19;
          v21 += 72;
          if ( v19 >= v18 )
            goto LABEL_31;
        }
        v22 = (int (**)(CEffect *, int))(v20 + 72 * v19);
        memset(v22, 0, 0x48u);
        *((_BYTE *)v22 + 64) = 1;
        * v22 = (*)CEffect::SetParam;
        *((_BYTE *)v22 + 65) = 0;
        v22[1] = 0;
        v22[2] = (int (*)(CEffect *, int))2;
        v23 = ++dword_17A7BC0;
        if ( !dword_17A7BC0 || v23 >= 0x7FFFFFFF )
        {
          v23 = 1;
          dword_17A7BC0 = 1;
        }
        v22[3] = (int (*)(CEffect *, int))v23;
        v22[5] = 0;
        v22[4] = 0;
        v22[6] = 0;
        v24 = v2[3];
        v25 = *(_DWORD *)(v24 + v7 + 4);
        v26 = (_DWORD *)(v24 + v7 + 4);
        v3 = v27;
        * v26 = (*)v25 + 1;
      }
LABEL_31:
      sub_4D3010(v2, v3, (int)sub_4D22F0, 0, 0, a2[18], a2[19]);
      sub_4D3010(v2, v27, (int)sub_4D2E10, 0, 0, 0, a2[19]);
      *(_DWORD *)(v2[3] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(v2[3] + v7) + 8) = 3;
      result = *(_DWORD *)(v2[3] + v7);
      *(_DWORD *)(result + 16) = v2[1];
    }
  }
  return result;
}
