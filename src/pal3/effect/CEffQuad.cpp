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
  gbGeomQuad *v4; // eax
  int v5; // ebp
  int v6; // ebx
  int v7; // ebp
  int *v8; // eax
  tagQuad *m_pQuad; // ecx
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
  gbGeomQuad *v21; // [esp+10h] [ebp-810h]
  char pExceptionObject[1024]; // [esp+14h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+414h] [ebp-40Ch] BYREF
  int v24; // [esp+81Ch] [ebp-4h]

  this->m_bAniFrame = 1;
  this->m_bNoZTest = *(_BYTE *)(a2 + 215);
  this->m_bAdditiveBlend = *(_BYTE *)(a2 + 213);
  this->m_byMaxFrame = *(_BYTE *)(a2 + 176);
  this->m_nRequireLoops = (int)&unk_FFFFFF;
  sub_4D1FD0(this->_pad_0000, *(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  this->m_pQuad = (tagQuad *)operator new(80 * *(_DWORD *)(a2 + 208));
  v3 = *(_DWORD *)(a2 + 208);
  v4 = (gbGeomQuad *)operator new(68 * v3);
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
  this->m_pGeomQuad = v4;
  v20 = 4 * *(_DWORD *)(a2 + 208);
  v24 = -1;
  v8 = (int *)operator new(v20);
  m_pQuad = (tagQuad *)this->m_pQuad;
  this->m_pnG2Q = v8;
  if ( !m_pQuad || !this->m_pGeomQuad || !v8 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffq, aDProjectPal3Co_16, 127),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->m_nMaxQuad = *(_DWORD *)(a2 + 208);
  sub_4D1EF0(this);
  for ( i = 0; i < this->m_nMaxQuad; ++i )
    this->m_pnG2Q[i] = i;
  this->ToNextFrame(a2 + 40);
  v11 = (_DWORD *)operator new(0x4C0u);
  *(_DWORD *)&this->_pad_0000[24] = v11;
  if ( v11 )
  {
    v12 = 0;
    v13 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v13 + *(_DWORD *)&this->_pad_0000[24]) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v13 + *(_DWORD *)&this->_pad_0000[24]) )
        break;
      v13 += 152;
      ++v12;
      if ( v13 >= 1216 )
      {
        v14 = 0;
        *(_DWORD *)&this->_pad_0000[40] = 8;
        *(_DWORD *)&this->_pad_0000[44] = 10;
        v15 = 0;
        do
        {
          *(_BYTE *)(v15 + *(_DWORD *)&this->_pad_0000[24] + 148) = 0;
          v16 = 0;
          if ( *(int *)&this->_pad_0000[44] > 0 )
          {
            v17 = 0;
            do
            {
              ++v16;
              v17 += 72;
              *(_BYTE *)(*(_DWORD *)(v15 + *(_DWORD *)&this->_pad_0000[24]) + v17 - 8) = 0;
            }
            while ( v16 < *(_DWORD *)&this->_pad_0000[44] );
          }
          ++v14;
          v15 += 152;
        }
        while ( v14 < *(_DWORD *)&this->_pad_0000[40] );
        return 1;
      }
    }
    if ( v12 > 0 && v12 - 1 >= 0 )
    {
      v19 = 152 * (v12 - 1);
      do
      {
        operator delete(*(void **)(v19 + *(_DWORD *)&this->_pad_0000[24]));
        v19 -= 152;
        --v12;
      }
      while ( v12 );
    }
    operator delete(*(void **)&this->_pad_0000[24]);
  }
  return 1;
}

// 0x004D1BE0
char CEffQuad::DestroyOneQuad(const void *a2)
{
  int m_nMaxQuad; // ecx
  int v4; // ebp
  tagQuad *m_pQuad; // esi
  __int32 *i; // eax
  int v8; // eax
  int m_nQuadNum; // ecx

  m_nMaxQuad = this->m_nMaxQuad;
  if ( this->m_nGeomQuadNum > m_nMaxQuad )
    return 0;
  v4 = 0;
  if ( m_nMaxQuad <= 0 )
    return 0;
  m_pQuad = (tagQuad *)this->m_pQuad;
  for ( i = &m_pQuad->bValid; *(_BYTE *)i; i += 20 )
  {
    if ( ++v4 >= m_nMaxQuad )
      return 0;
  }
  v8 = 80 * v4;
  qmemcpy((char *)m_pQuad + 80 * v4, a2, 0x50u);
  *((_BYTE *)&this->m_pQuad->bValid + v8) = 1;
  *(__int32 *)((char *)&this->m_pQuad->byFrame + v8) = 0;
  *((_BYTE *)&this->m_pQuad->bValid + v8 + 2) = 0;
  *((_BYTE *)&this->m_pQuad->bValid + v8 + 3) = 0;
  m_nQuadNum = this->m_nQuadNum;
  if ( v4 > m_nQuadNum - 1 )
    this->m_nQuadNum = m_nQuadNum + 1;
  *(int *)((char *)&this->m_pQuad->nGeomQuad + v8) = this->m_nGeomQuadNum;
  this->m_pnG2Q[this->m_nGeomQuadNum++] = v4;
  this->SetQuad(v4);
  this->m_nLastCreatedQuad = v4;
  return 1;
}

// 0x004D1CA0
int CEffQuad::SetQuad(int a2)
{
  char *v2; // edx
  int result; // eax
  double v4; // st7

  v2 = (char *)this->m_pQuad + 80 * a2;
  result = 68 * *(_DWORD *)v2;
  *(int *)((char *)&this->m_pGeomQuad->color.ColorQuadFmt + result) = *((_DWORD *)v2 + 19);
  if ( this->m_bBillBoard )
  {
    *(float *)((char *)&this->m_pGeomQuad->vec[0].x + result) = *((float *)v2 + 4) - *((float *)v2 + 7);
    *(float *)((char *)&this->m_pGeomQuad->vec[1].x + result) = *((float *)v2 + 7) + *((float *)v2 + 4);
    *(float *)((char *)&this->m_pGeomQuad->vec[2].x + result) = *((float *)v2 + 7) + *((float *)v2 + 4);
    *(float *)((char *)&this->m_pGeomQuad->vec[3].x + result) = *((float *)v2 + 4) - *((float *)v2 + 7);
    *(float *)((char *)&this->m_pGeomQuad->vec[0].y + result) = *((float *)v2 + 5);
    *(float *)((char *)&this->m_pGeomQuad->vec[1].y + result) = *((float *)v2 + 5);
    *(float *)((char *)&this->m_pGeomQuad->vec[2].y + result) = *((float *)v2 + 5);
    *(float *)((char *)&this->m_pGeomQuad->vec[3].y + result) = *((float *)v2 + 5);
    *(float *)((char *)&this->m_pGeomQuad->vec[0].z + result) = *((float *)v2 + 8) + *((float *)v2 + 6);
    *(float *)((char *)&this->m_pGeomQuad->vec[1].z + result) = *((float *)v2 + 8) + *((float *)v2 + 6);
    *(float *)((char *)&this->m_pGeomQuad->vec[2].z + result) = *((float *)v2 + 6) - *((float *)v2 + 8);
    v4 = *((float *)v2 + 6) - *((float *)v2 + 8);
  }
  else
  {
    *(float *)((char *)&this->m_pGeomQuad->vec[0].x + result) = -*((float *)v2 + 7);
    *(float *)((char *)&this->m_pGeomQuad->vec[1].x + result) = *((float *)v2 + 7);
    *(float *)((char *)&this->m_pGeomQuad->vec[2].x + result) = *((float *)v2 + 7);
    *(float *)((char *)&this->m_pGeomQuad->vec[3].x + result) = -*((float *)v2 + 7);
    *(float *)((char *)&this->m_pGeomQuad->vec[0].y + result) = 0.0;
    *(float *)((char *)&this->m_pGeomQuad->vec[1].y + result) = 0.0;
    *(float *)((char *)&this->m_pGeomQuad->vec[2].y + result) = 0.0;
    *(float *)((char *)&this->m_pGeomQuad->vec[3].y + result) = 0.0;
    *(float *)((char *)&this->m_pGeomQuad->vec[0].z + result) = *((float *)v2 + 8);
    *(float *)((char *)&this->m_pGeomQuad->vec[1].z + result) = *((float *)v2 + 8);
    *(float *)((char *)&this->m_pGeomQuad->vec[2].z + result) = -*((float *)v2 + 8);
    v4 = -*((float *)v2 + 8);
  }
  *(float *)((char *)&this->m_pGeomQuad->vec[3].z + result) = v4;
  *(float *)((char *)&this->m_pGeomQuad->vec[4].x + result) = 0.0;
  *(float *)((char *)&this->m_pGeomQuad->eu + result) = 0.0;
  *(float *)((char *)&this->m_pGeomQuad->sv + result) = 0.0;
  *(float *)((char *)&this->m_pGeomQuad->ev + result) = 0.0;
  return result;
}

// 0x004D1E50
_DWORD * CEffQuad::DestroyAllQuad(int a2)
{
  _DWORD *result; // eax
  char *v3; // ecx
  int v4; // edx
  int v5; // ebx
  int v6; // ecx

  result = (_DWORD *)this->_pad_0000;
  v3 = (char *)this->m_pQuad + 80 * a2;
  v4 = result[16] - 1;
  v5 = *(_DWORD *)v3;
  v3[4] = 0;
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
  gbTexture *m_pTexture; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(***(_DWORD ***)&this->_pad_0000[4] + 8))(
                      **(_DWORD **)&this->_pad_0000[4],
                      a2);
  this->m_pTexture = v3;
  v3->LoadTexture(1);
  result = (_DWORD *)operator new(0x44u);
  if ( result )
  {
    m_pTexture = (gbTexture *)this->m_pTexture;
    result[16] = 1;
    *result = m_pTexture;
  }
  else
  {
    result = 0;
  }
  this->m_pTextureArray = (gbTextureArray *)result;
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

  v2 = (int *)&this->_pad_0000[12];
  v3 = 0;
  this->m_nRequireLoops = a2[20];
  result = *(_DWORD *)&this->_pad_0000[40];
  if ( result > 0 )
  {
    v5 = *(_DWORD *)&this->_pad_0000[24];
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
