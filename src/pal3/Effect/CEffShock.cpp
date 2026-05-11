#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffShock.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4D3870(...);
int sub_4D48B0(...);
int sub_4D4AB0(...);

// Unnamed globals (extern)
extern char aDProjectPal3Co_17[];
extern char aNewFailInCeffs[];
extern unsigned char byte_1895561;
extern int dword_17A7E88;
extern int dword_1895984;
extern int dword_1895988;
extern int nullsub_1;

// 0x004D3910
CEffShock::CEffShock()
{
  _DWORD *v0; // eax

  v0 = (_DWORD *)operator new(0x10B0u);
  if ( v0 )
  sub_4D3870(v0);
  else
  0;
}

// 0x004D3A50
int CEffShock::Init(int a2, float a3, float a4, float a5)
{
  int result; // eax

  this->_base[8] = 0;
  this->m_fSize = *(float *)(a2 + 200);
  *(float *)this->m_vecPos = a3 + *(float *)(a2 + 184);
  *(float *)&this->m_vecPos[4] = a4 + *(float *)(a2 + 188);
  *(float *)&this->m_vecPos[8] = a5 + *(float *)(a2 + 192);
  *(_DWORD *)this->m_vecRot = *(_DWORD *)(a2 + 216);
  *(_DWORD *)&this->m_vecRot[4] = *(_DWORD *)(a2 + 196);
  *(_DWORD *)&this->m_vecRot[8] = *(_DWORD *)(a2 + 220);
  result = *(_DWORD *)(a2 + 204);
  this->m_dwStartColor = result;
  return result;
}

// 0x004D3AD0
char CEffShock::Create(int a2)
{
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int m_nMaxGeomQuad; // ebx
  gbGeomQuad *v12; // eax
  int v13; // ebx
  int v14; // ebp
  int v15; // ebx
  int v16; // edi
  tagShockUnit *v17; // eax
  gbGeomQuad *m_pGeomQuad; // ecx
  size_t v20; // [esp-4h] [ebp-820h]
  gbGeomQuad *v21; // [esp+Ch] [ebp-810h]
  char pExceptionObject[1024]; // [esp+10h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+410h] [ebp-40Ch] BYREF
  int v24; // [esp+818h] [ebp-4h]

  v3 = (_DWORD *)operator new(0x4C0u);
  *(_DWORD *)&this->_base[24] = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v5 + *(_DWORD *)&this->_base[24]) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v5 + *(_DWORD *)&this->_base[24]) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *(_DWORD *)&this->_base[40] = 8;
        *(_DWORD *)&this->_base[44] = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(v7 + *(_DWORD *)&this->_base[24] + 148) = 0;
          v8 = 0;
          if ( *(int *)&this->_base[44] > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(*(_DWORD *)(v7 + *(_DWORD *)&this->_base[24]) + v9 - 8) = 0;
            }
            while ( v8 < *(_DWORD *)&this->_base[44] );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *(_DWORD *)&this->_base[40] );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v16 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v16 + *(_DWORD *)&this->_base[24]));
        v16 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)&this->_base[24]);
  }
LABEL_10:
  this->m_nNodeOfShock = (__int64)*(float *)(a2 + 224);
  this->m_nCascade = (__int64)*(float *)(a2 + 228);
  this->m_fWidthOfNode = *(float *)(a2 + 232);
  this->m_fHeightOfNode = *(float *)(a2 + 244);
  v10 = this->m_nNodeOfShock * this->m_nCascade;
  this->m_fSpeedOfDisappear = *(float *)(a2 + 248);
  this->m_fInterleaving = *(float *)(a2 + 268);
  this->m_nMaxGeomQuad = v10;
  this->m_fFramePerSec = *(float *)(a2 + 180);
  *(_DWORD *)this->m_vecPos = *(_DWORD *)(a2 + 184);
  *(_DWORD *)&this->m_vecPos[4] = *(_DWORD *)(a2 + 188);
  *(_DWORD *)&this->m_vecPos[8] = *(_DWORD *)(a2 + 192);
  *(_DWORD *)this->m_vecRot = *(_DWORD *)(a2 + 216);
  *(_DWORD *)&this->m_vecRot[4] = *(_DWORD *)(a2 + 196);
  *(_DWORD *)&this->m_vecRot[8] = *(_DWORD *)(a2 + 220);
  this->m_bAdditiveBlend = *(_BYTE *)(a2 + 213);
  this->m_bNoZTest = *(_BYTE *)(a2 + 215);
  this->m_byMaxFrame = *(_BYTE *)(a2 + 176);
  this->m_nRequireLoops = 0xFFFF;
  this->m_dwStartColor = *(_DWORD *)(a2 + 204);
  this->CreateGeom(*(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  m_nMaxGeomQuad = this->m_nMaxGeomQuad;
  v12 = (gbGeomQuad *)operator new(68 * m_nMaxGeomQuad);
  v21 = v12;
  v24 = 0;
  if ( v12 )
  {
    v13 = m_nMaxGeomQuad - 1;
    v14 = (int)v12;
    if ( v13 >= 0 )
    {
      v15 = v13 + 1;
      do
      {
        ArraySort(v14, 12, 4, gbVec3D::`default constructor closure');
        v14 += 68;
        --v15;
      }
      while ( v15 );
      v12 = v21;
    }
  }
  else
  {
    v12 = 0;
  }
  this->m_pGeomQuad = v12;
  v20 = 8 * this->m_nMaxGeomQuad;
  v24 = -1;
  v17 = (tagShockUnit *)operator new(v20);
  m_pGeomQuad = (gbGeomQuad *)this->m_pGeomQuad;
  this->m_pShock = v17;
  if ( !m_pGeomQuad || !v17 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffs, aDProjectPal3Co_17, 91),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  sub_4D4AB0((int)this, a2 + 40);
  sub_4D48B0((int)this);
  return 1;
}

// 0x004D45D0
int CEffShock::StartShock(int a2)
{
  int i; // edi
  tagShockUnit *m_pShock; // ecx
  double v5; // st7
  float *p_fRequireLoops; // eax
  int result; // eax
  int v8; // edx
  int j; // edi
  int v10; // ecx
  double v11; // st7
  tagShockUnit *v12; // eax
  float v13; // [esp+8h] [ebp-4h]
  int k; // [esp+10h] [ebp+4h]

  for ( i = 0; i < this->m_nMaxGeomQuad; *p_fRequireLoops = v5 )
  {
    if ( (byte_1895561 & 1) == 0 )
    {
      byte_1895561 |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    ++dword_1895988;
    dword_1895984 = 214013 * dword_1895984 + 2531011;
    this->m_pShock[i].fCurFrame = (double)(((dword_1895984 >> 16) & 0x7FFF) % (100 * this->m_byMaxFrame)) * 0.0099999998;
    v13 = (float)a2;
    this->m_pShock[i].fRequireLoops = v13;
    m_pShock = (tagShockUnit *)this->m_pShock;
    v5 = m_pShock[i].fCurFrame + m_pShock[i].fRequireLoops;
    p_fRequireLoops = (float *)&m_pShock[i++].fRequireLoops;
  }
  result = this->m_nNodeOfShock;
  v8 = 0;
  for ( j = 0; j < result; ++j )
  {
    v10 = 0;
    for ( k = 0; v10 < this->m_nCascade; v12->fRequireLoops = v11 * this->m_fSpeedOfDisappear + v12->fRequireLoops )
    {
      v11 = (double)k;
      k = ++v10;
      v12 = (tagShockUnit *)&this->m_pShock[v8++];
    }
    result = this->m_nNodeOfShock;
  }
  return result;
}

// 0x004D49F0
int CEffShock::CreateGeom(int a2, int a3)
{
  int result; // eax
  int v4; // ebx
  char *v6; // edi
  int v7; // esi
  int v8; // ecx
  char *v9; // eax
  double v10; // st7
  double v11; // st7
  double v12; // st6
  float v13; // [esp+0h] [ebp-14h]
  float v14; // [esp+4h] [ebp-10h]
  int v15; // [esp+8h] [ebp-Ch]
  float v16; // [esp+8h] [ebp-Ch]
  float v17; // [esp+Ch] [ebp-8h]
  float v18; // [esp+10h] [ebp-4h]
  int a2a; // [esp+18h] [ebp+4h]

  result = a3;
  v4 = 0;
  v14 = (float)a2;
  v15 = 0;
  v13 = (float)a3;
  if ( a3 > 0 )
  {
    v6 = (char *)&this->m_DefaultUVSet[8];
    v7 = 16 * a2;
    do
    {
      v8 = 0;
      a2a = 0;
      if ( a2 > 0 )
      {
        v9 = v6;
        v6 += v7;
        v10 = (double)v15 / v13;
        v17 = 1.0 / v13;
        v16 = 1.0 - (v10 + v17);
        v11 = 1.0 - v10;
        do
        {
          v9 += 16;
          ++v8;
          v12 = (double)a2a / v14;
          a2a = v8;
          *((float *)v9 - 6) = v12;
          v18 = 1.0 / v14;
          *((float *)v9 - 4) = v12 + v18;
          *((float *)v9 - 5) = v16;
          *((float *)v9 - 3) = v11;
        }
        while ( v8 < a2 );
      }
      result = a3;
      v15 = ++v4;
    }
    while ( v4 < a3 );
  }
  return result;
}

// 0x004D4B50
int CEffShock::LoadTexture(int a2, int a3, int a4, _DWORD *a5, int a6, int a7)
{
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  _DWORD *v15; // edx

  v8 = *(_DWORD *)&this->_base[32];
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*(_DWORD *)&this->_base[12] + 152 * a2);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = a3;
  v13[1] = a4;
  v13[2] = 2;
  v14 = ++dword_17A7E88;
  if ( !dword_17A7E88 || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    dword_17A7E88 = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = a6;
  v13[6] = a7;
  if ( a5 )
  {
    v15 = (_DWORD *)v13 + 7;
    * v15 = (*)*a5;
    v15[1] = a5[1];
    v15[2] = a5[2];
    v15[3] = a5[3];
  }
  ++*(_DWORD *)(*(_DWORD *)&this->_base[12] + 152 * a2 + 4);
  return v9;
}
