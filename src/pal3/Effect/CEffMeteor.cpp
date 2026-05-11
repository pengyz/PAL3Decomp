#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffMeteor.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/CEffgbParticle.h"
#include "pal3/gen/CMeteorChain.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4CB3A0(...);
int sub_4CCC60(...);
int sub_4CCD10(...);
int sub_4CD070(...);
int sub_4CD0D0(...);
int sub_4CD3D0(...);
int sub_4D4D30(...);
int sub_4D4D70(...);

// Unnamed globals (extern)
extern char aDProjectPal3Co_0[];
extern char aNewFailInCeffm[];
extern int nullsub_1;
extern int nullsub_3;
extern void *off_56F62C;
extern void *off_56F96C;
extern void *off_56F978;
extern void *off_56F9B4;
extern int unk_FFFFFF;

// 0x004CB480
CEffMeteor::CEffMeteor()
{
  _DWORD *v0; // eax

  v0 = (_DWORD *)operator new(0x10D0u);
  if ( v0 )
  sub_4CB3A0(v0);
  else
  0;
}

// 0x004CB4C0
CEffMeteor::~CEffMeteor()
{
  int v2; // edi
  void *v3; // eax
  int v4; // ebp
  char *v5; // eax
  char *v6; // esi
  gbRefObject *v7; // ecx
  int v8; // esi
  int v9; // eax
  bool v10; // cc
  int v11; // edi

  v2 = a1 + 12;
  *(_DWORD *)a1 = &off_56F978;
  *(_DWORD *)(a1 + 12) = &off_56F96C;
  v3 = (void *)*(void **)(a1 + 48);
  v4 = 0;
  if ( v3 )
    operator delete(v3);
  if ( *(_DWORD *)(a1 + 56) )
    operator delete(*(void **)(a1 + 56));
  v5 = (char *)*(char **)(a1 + 52);
  if ( v5 )
  {
    v6 = (char *)v5 - 4;
    `eh vector destructor iterator'(
      v5,
      0x38u,
      *((_DWORD *)v5 - 1),
      (void (*)(void *))CMeteorChain::CMeteorChain);
    operator delete(v6);
  }
  v7 = (gbRefObject *)*(gbRefObject **)(a1 + 60);
  if ( v7 )
    v7->Release();
  if ( *(_DWORD *)(a1 + 64) )
    operator delete(*(void **)(a1 + 64));
  v8 = a1 != 0 ? v2 : 0;
  *(_DWORD *)v8 = &off_56F9B4;
  v9 = *(_DWORD *)(v8 + 0x1C);
  v10 = v9 <= 0;
  if ( !v9 )
  {
    if ( !*(_DWORD *)(a1 != 0 ? v2 + 0x20 : 32) )
      goto LABEL_18;
    v10 = 1;
  }
  if ( !v10 )
  {
    v11 = 0;
    do
    {
      operator delete(*(void **)(*(_DWORD *)(v8 + 12) + v11));
      ++v4;
      *(_DWORD *)(*(_DWORD *)(v8 + 12) + v11) = 0;
      v11 += 152;
    }
    while ( v4 < *(_DWORD *)(v8 + 28) );
  }
  operator delete(*(void **)(v8 + 12));
  *(_DWORD *)(v8 + 12) = 0;
  *(_DWORD *)(v8 + 28) = 0;
  *(_DWORD *)(v8 + 32) = 0;
LABEL_18:
  *(_DWORD *)a1 = &off_56F62C;
}

// 0x004CB5E0
int CEffMeteor::Init(int a2, float a3, float a4, float a5)
{
  int m_dwStartColor_low; // ecx
  int result; // eax
  int v8; // ecx

  this->_base[8] = 0;
  this->m_bVisible = 0;
  *(float *)this->m_vecPos = a3 + *(float *)(a2 + 184);
  *(float *)&this->m_vecPos[4] = a4 + *(float *)(a2 + 188);
  *(float *)&this->m_vecPos[8] = a5 + *(float *)(a2 + 192);
  *(_DWORD *)this->m_vecRot = *(_DWORD *)(a2 + 216);
  *(_DWORD *)&this->m_vecRot[4] = *(_DWORD *)(a2 + 196);
  *(_DWORD *)&this->m_vecRot[8] = *(_DWORD *)(a2 + 220);
  *(float *)this->m_vecTarget = a3 + *(float *)(a2 + 252);
  *(float *)&this->m_vecTarget[4] = a4 + *(float *)(a2 + 256);
  *(float *)&this->m_vecTarget[8] = a5 + *(float *)(a2 + 260);
  *(_DWORD *)&this->m_vecOffsetPos[8] = 0;
  *(_DWORD *)&this->m_vecOffsetPos[4] = 0;
  *(_DWORD *)this->m_vecOffsetPos = 0;
  this->m_dwStartColor = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_fAlpha = (float)HIBYTE(this->m_dwStartColor);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_fRed = (float)(unsigned __int8)BYTE2(this->m_dwStartColor);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_fGreen = (float)(unsigned __int8)BYTE1(this->m_dwStartColor);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_fCurFrame = 0.0;
  m_dwStartColor_low = LOBYTE(this->m_dwStartColor);
  this->m_nLoops = 0;
  this->m_fBlue = (float)m_dwStartColor_low;
  this->m_fXSize = *(float *)(a2 + 200);
  this->m_fZSize = *(float *)(a2 + 200);
  nullsub_3(this);
  result = this->m_nMaxChain;
  v8 = 0;
  if ( result > 0 )
  {
    result = 0;
    do
    {
      ++v8;
      *(unsigned int *)((char *)&this->m_pChain->m_dwColor + result) = this->m_dwStartColor;
      *(float *)((char *)&this->m_pChain->m_fMaxWidth + result) = this->m_fMeteorWidth;
      *(float *)((char *)&this->m_pChain->m_fLumDecSpeed + result) = this->m_fLumDecSpeed;
      *(float *)((char *)&this->m_pChain->m_fWidthDecSpeed + result) = this->m_fWidthDecSpeed;
      *(float *)((char *)&this->m_pChain->m_fMaxLum + result) = this->m_fMaxLum;
      result += 56;
    }
    while ( v8 < this->m_nMaxChain );
  }
  return result;
}

// 0x004CB800
char CEffMeteor::Create(int base)
{
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v11; // edi
  int m_nMaxChain; // ebx
  gbGeomQuad *v13; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  tagMeteor *v17; // eax
  int v18; // ebx
  _DWORD *p_z; // ecx
  int v20; // ebx
  int v21; // ebx
  char *v22; // eax
  CMeteorChain *v23; // eax
  gbGeomQuad *m_pGeomQuad; // ecx
  int v25; // edi
  int v26; // ebx
  char ArgList[1024]; // [esp+Ch] [ebp-810h] BYREF
  _BYTE pExceptionObject[1024]; // [esp+40Ch] [ebp-410h] BYREF
  void *Block; // [esp+80Ch] [ebp-10h]
  int v31; // [esp+818h] [ebp-4h]
  int basea; // [esp+824h] [ebp+8h]
  int baseb; // [esp+824h] [ebp+8h]

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
      v11 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v11 + *(_DWORD *)&this->_base[24]));
        v11 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)&this->_base[24]);
  }
LABEL_10:
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_nMaxChain = abs32((int)*(float *)(base + 224));
  this->m_fMeteorWidth = *(float *)(base + 228);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_nMaxTrail = (int)*(float *)(base + 232);
  this->m_fLumDecSpeed = *(float *)(base + 244);
  this->m_fWidthDecSpeed = *(float *)(base + 248);
  this->m_fMaxLum = *(float *)(base + 268);
  this->m_bHaveHead = *(float *)(base + 224) > 0.0;
  this->m_fFramePerSec = *(float *)(base + 180);
  *(_DWORD *)this->m_vecPos = *(_DWORD *)(base + 184);
  *(_DWORD *)&this->m_vecPos[4] = *(_DWORD *)(base + 188);
  *(_DWORD *)&this->m_vecPos[8] = *(_DWORD *)(base + 192);
  *(_DWORD *)this->m_vecRot = *(_DWORD *)(base + 216);
  *(_DWORD *)&this->m_vecRot[4] = *(_DWORD *)(base + 196);
  *(_DWORD *)&this->m_vecRot[8] = *(_DWORD *)(base + 220);
  *(_DWORD *)this->m_vecTarget = *(_DWORD *)(base + 252);
  *(_DWORD *)&this->m_vecTarget[4] = *(_DWORD *)(base + 256);
  *(_DWORD *)&this->m_vecTarget[8] = *(_DWORD *)(base + 260);
  *(_DWORD *)this->m_vecStartSpeed = *(_DWORD *)(base + 264);
  *(_DWORD *)&this->m_vecStartSpeed[4] = *(_DWORD *)(base + 236);
  *(_DWORD *)&this->m_vecStartSpeed[8] = *(_DWORD *)(base + 240);
  this->m_bAdditiveBlend = *(_BYTE *)(base + 213);
  this->m_bNoZTest = *(_BYTE *)(base + 215);
  this->m_byMaxFrame = *(_BYTE *)(base + 176);
  this->m_nRequireLoops = (int)&unk_FFFFFF;
  this->m_dwStartColor = *(_DWORD *)(base + 204);
  sub_4CCC60(this->_base, *(_DWORD *)(base + 168), *(_DWORD *)(base + 172));
  m_nMaxChain = this->m_nMaxChain;
  v13 = (gbGeomQuad *)operator new(68 * m_nMaxChain);
  Block = v13;
  v31 = 0;
  if ( v13 )
  {
    v14 = m_nMaxChain - 1;
    basea = (int)v13;
    if ( v14 >= 0 )
    {
      v15 = v14 + 1;
      do
      {
        ArraySort(basea, 12, 4, gbVec3D::`default constructor closure');
        --v15;
        basea += 68;
      }
      while ( v15 );
      v13 = (gbGeomQuad *)Block;
    }
  }
  else
  {
    v13 = 0;
  }
  v16 = this->m_nMaxChain;
  this->m_pGeomQuad = v13;
  v31 = -1;
  v17 = (tagMeteor *)operator new(48 * v16);
  if ( v17 )
  {
    v18 = v16 - 1;
    if ( v18 >= 0 )
    {
      p_z = (_DWORD *)&v17->vecSpeed.z;
      v20 = v18 + 1;
      do
      {
        *(p_z - 5) = 0;
        *(p_z - 4) = 0;
        *(p_z - 3) = 0;
        *(p_z - 2) = 0;
        *(p_z - 1) = 0;
        *p_z = 0;
        p_z[1] = 0;
        p_z[2] = 0;
        p_z[3] = 0;
        p_z[4] = 0;
        p_z[5] = 0;
        p_z[6] = 0;
        p_z += 12;
        --v20;
      }
      while ( v20 );
    }
  }
  else
  {
    v17 = 0;
  }
  v21 = this->m_nMaxChain;
  this->m_pMeteor = v17;
  v22 = (char *)operator new(56 * v21 + 4);
  Block = v22;
  v31 = 1;
  if ( v22 )
  {
    *(_DWORD *)v22 = v21;
    baseb = (int)(v22 + 4);
    `eh vector constructor iterator'(
      v22 + 4,
      0x38u,
      v21,
      (void (*)(void *))sub_4CD070,
      (void (*)(void *))CMeteorChain::CMeteorChain);
    v23 = (CMeteorChain *)baseb;
  }
  else
  {
    v23 = 0;
  }
  m_pGeomQuad = (gbGeomQuad *)this->m_pGeomQuad;
  v31 = -1;
  this->m_pChain = v23;
  if ( !m_pGeomQuad || !v23 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffm, aDProjectPal3Co_0, 144),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  sub_4CCD10((int)this, base + 40);
  v25 = 0;
  if ( this->m_nMaxChain > 0 )
  {
    v26 = 0;
    do
    {
      sub_4CD0D0(
        &this->m_pChain[v26],
        *(_DWORD *)&this->_base[4],
        this->m_nMaxTrail,
        this->m_bHaveHead == 0,
        (int)this->m_pTextureArray);
      ++v25;
      ++v26;
    }
    while ( v25 < this->m_nMaxChain );
  }
  return 1;
}

// 0x004CBFC0
void CEffMeteor::CreateTask(int arg0)
{
  CEffMeteor *v2; // edi
  double v3; // st7
  char *v4; // esi
  int v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // ebx
  int v13; // esi
  int v14; // esi
  int v15; // edx
  int v16; // eax
  char *v17; // ecx
  int v19; // [esp+4h] [ebp-Ch]
  int v20; // [esp+8h] [ebp-8h]
  int a2; // [esp+Ch] [ebp-4h]

  v2 = this;
  v3 = *(float *)&arg0 - *(float *)&this->_base[16];
  v4 = (char *)&this->_base[12];
  *(float *)&this->_base[16] = *(float *)&arg0;
  *(float *)&this->_base[20] = v3;
  if ( *(float *)&this->_base[20] > 0.0 )
  {
    a2 = 0;
    if ( *(int *)&this->_base[40] > 0 )
    {
      v20 = 0;
      while ( 1 )
      {
        v5 = v20 + *((_DWORD *)v4 + 3);
        if ( *(_BYTE *)(v5 + 148) )
        {
          if ( *(_DWORD *)(v5 + 12) == 3 )
          {
            v6 = 0;
            v19 = 0;
            if ( *((int *)v4 + 8) > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++a2 < *((_DWORD *)v4 + 7);
        v20 += 152;
        if ( !v11 )
          goto LABEL_30;
      }
      v7 = 0;
      while ( 1 )
      {
        v8 = v7 + *(_DWORD *)v5;
        if ( !*(_BYTE *)(v8 + 64) || v7 > 0 && *(_DWORD *)(v8 - 64) == 2 )
        {
LABEL_28:
          v2 = this;
          goto LABEL_29;
        }
        switch ( *(_DWORD *)(v8 + 8) )
        {
          case 2:
            if ( v7 > 0 )
            {
              if ( *(float *)(v8 + 20) >= 0.0 )
              {
                if ( *((float *)v4 + 1) - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  sub_4D4D30(v4, a2, v6);
                  *((_DWORD *)v4 + 4) = a2;
                  *((_DWORD *)v4 + 5) = v19;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)(v20 + *((_DWORD *)v4 + 3)) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)(v20 + *((_DWORD *)v4 + 3)) + v7 + 16) = *((_DWORD *)v4 + 1);
LABEL_21:
                *((_DWORD *)v4 + 5) = v6;
                *((_DWORD *)v4 + 4) = a2;
LABEL_24:
                (*(void (**)(char *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4 + 4))(
                  v4,
                  *(_DWORD *)(*(_DWORD *)v5 + v7),
                  *(_DWORD *)(*(_DWORD *)v5 + v7 + 4),
                  0);
              }
            }
            break;
          case 3:
            goto LABEL_21;
          case 4:
            if ( sub_4D4D70(v4, a2) )
            {
              v9 = *(_DWORD *)(v5 + 4);
              *(_DWORD *)(v5 + 12) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = *(_BYTE *)(v5 + 149);
              *(_DWORD *)(v5 + 20) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                ((CEffgbParticle *)v4)->Init(a2);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v19 + 1;
        v7 += 72;
        if ( ++v19 >= *((_DWORD *)v4 + 8) )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)&v2->_base[36] <= 0 )
      v2->_base[8] = 1;
    if ( !v2->_base[8] )
    {
      v12 = 0;
      if ( v2->m_nMaxChain > 0 )
      {
        v13 = 0;
        do
        {
          v2->m_pChain[v13].m_dwColor = v2->m_dwStartColor;
          v2->m_pChain[v13].m_fMaxLum = v2->m_fMaxLum;
          sub_4CD3D0((int)&v2->m_pChain[v13], arg0);
          ++v12;
          ++v13;
        }
        while ( v12 < v2->m_nMaxChain );
      }
      if ( v2->m_bHaveHead )
      {
        v2->m_fCurFrame = v2->m_fFramePerSec * *(float *)&v2->_base[20] + v2->m_fCurFrame;
        if ( (g_bCursorVisible & 1) == 0 )
        {
          g_bCursorVisible |= 1u;
          ((CEffMgr *)&g_nCursorState)->Reset();
          atexit(nullsub_1);
        }
        v14 = 0;
        v15 = (int)abs32((int)v2->m_fCurFrame) % v2->m_byMaxFrame;
        if ( v2->m_nMaxChain > 0 )
        {
          v16 = 0;
          v17 = (char *)&v2->_base[16 * v15];
          do
          {
            ++v14;
            v16 += 68;
            *(_DWORD *)((char *)&v2->m_pGeomQuad->vec[-1] + v16 - 8) = *(_DWORD *)&v2->m_DefaultUVSet[16 * v15];
            *(float *)((char *)&v2->m_pGeomQuad->vec[-1].x + v16) = *((float *)v17 + 54);
            *(_DWORD *)((char *)&v2->m_pGeomQuad->vec[-1] + v16 - 4) = *((_DWORD *)v17 + 53);
            *(_DWORD *)((char *)v2->m_pGeomQuad->vec + v16 - 8) = *((_DWORD *)v17 + 55);
            *(_DWORD *)((char *)v2->m_pGeomQuad->vec + v16 - 4) = v2->m_dwStartColor;
          }
          while ( v14 < v2->m_nMaxChain );
        }
      }
    }
  }
}
