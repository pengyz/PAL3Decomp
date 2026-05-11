#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffCylinder.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/CEffect.h"
#include "pal3/gen/CEffgbParticle.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4C5350(...);
int sub_4C55F0(...);
int sub_4D4D30(...);
int sub_4D4D70(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co[];
extern char aNewFailInCeffc[];
extern unsigned char byte_DE937C;
extern int dword_DE9350;
extern int dword_DE9354;
extern int dword_DE9358;
extern int dword_DE9360;
extern int dword_DE9364;
extern int dword_DE9368;
extern int dword_DE9370;
extern int dword_DE9374;
extern int dword_DE9378;
extern int dword_DE9380;
extern int nullsub_1;
extern int nullsub_76;
extern int nullsub_77;
extern int nullsub_78;
extern void *off_56F62C;
extern void *off_56F7BC;
extern void *off_56F7C8;
extern void *off_56F804;
extern int unk_5D4D3C;
extern int unk_5D4D7C;
extern int unk_5D4DAC;
extern int unk_5D4DB8;
extern int unk_5D4DC4;
extern int unk_5D4DCC;
extern int unk_5D4DD4;
extern int unk_5D4DF4;
extern int unk_5D4E00;
extern int unk_5D4E24;
extern int unk_5D4E30;
extern int unk_5D4E38;
extern int unk_5D4E40;
extern int unk_5D4FD0;
extern int unk_5D4FE0;
extern int unk_5D4FF0;
extern int unk_5D4FFC;
extern int unk_5D5008;
extern int unk_5D5014;
extern int unk_5D5020;
extern int unk_5D502C;
extern int unk_5D5038;
extern int unk_5D5040;
extern int unk_5D5048;
extern int unk_5D5050;
extern int unk_5D505C;
extern int unk_5D5068;
extern int unk_5D5074;
extern int unk_5D5080;
extern int unk_5D508C;
extern int unk_5D5098;
extern int unk_5D50A4;
extern int unk_5D50B0;
extern int unk_5D50B8;
extern int unk_5D50C0;
extern int unk_5D50CC;
extern int unk_5D50D8;
extern int unk_5D50E4;
extern int unk_FFFFFF;

// 0x004C3DD0
CEffCylinder::CEffCylinder(int a1)
{
  int v2; // edi
  void *v3; // eax
  int v4; // ebx
  gbRefObject *v5; // ecx
  int v6; // esi
  int v7; // eax
  bool v8; // cc
  int v9; // edi

  v2 = a1 + 12;
  *(_DWORD *)a1 = &off_56F7C8;
  *(_DWORD *)(a1 + 12) = &off_56F7BC;
  v3 = (void *)*(void **)(a1 + 48);
  v4 = 0;
  if ( v3 )
    operator delete(v3);
  v5 = (gbRefObject *)*(gbRefObject **)(a1 + 52);
  if ( v5 )
    v5->Release();
  if ( *(_DWORD *)(a1 + 56) )
    operator delete(*(void **)(a1 + 56));
  v6 = a1 != 0 ? v2 : 0;
  *(_DWORD *)v6 = &off_56F804;
  v7 = *(_DWORD *)(v6 + 0x1C);
  v8 = v7 <= 0;
  if ( !v7 )
  {
    if ( !*(_DWORD *)(a1 != 0 ? v2 + 0x20 : 32) )
      goto LABEL_14;
    v8 = 1;
  }
  if ( !v8 )
  {
    v9 = 0;
    do
    {
      operator delete(*(void **)(*(_DWORD *)(v6 + 12) + v9));
      ++v4;
      *(_DWORD *)(*(_DWORD *)(v6 + 12) + v9) = 0;
      v9 += 152;
    }
    while ( v4 < *(_DWORD *)(v6 + 28) );
  }
  operator delete(*(void **)(v6 + 12));
  *(_DWORD *)(v6 + 12) = 0;
  *(_DWORD *)(v6 + 28) = 0;
  *(_DWORD *)(v6 + 32) = 0;
LABEL_14:
  *(_DWORD *)a1 = &off_56F62C;
}

// 0x004C3EB0
CEffCylinder::~CEffCylinder()
{
  *(_DWORD *)this->_base = &off_56F62C;
}

// 0x004C3EC0
int CEffCylinder::Init(int a2, float a3, float a4, float a5)
{
  int result; // eax
  int m_dwStartColor_low; // ecx
  float v8; // edx

  this->_base[8] = 0;
  this->m_bVisible = 0;
  *(float *)this->m_vecPos = a3 + *(float *)(a2 + 184);
  *(float *)&this->m_vecPos[4] = a4 + *(float *)(a2 + 188);
  *(float *)&this->m_vecPos[8] = a5 + *(float *)(a2 + 192);
  *(_DWORD *)this->m_vecRot = *(_DWORD *)(a2 + 216);
  *(_DWORD *)&this->m_vecRot[4] = *(_DWORD *)(a2 + 196);
  *(_DWORD *)&this->m_vecRot[8] = *(_DWORD *)(a2 + 220);
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
  result = (unsigned __int8)BYTE1(this->m_dwStartColor);
  this->m_fGreen = (float)result;
  LOBYTE(result) = g_bCursorVisible;
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    result = atexit(nullsub_1);
  }
  this->m_fCurTextureV = 0.0;
  m_dwStartColor_low = LOBYTE(this->m_dwStartColor);
  this->m_fCurFrame = 0.0;
  this->m_nLoops = 0;
  this->m_fBlue = (float)m_dwStartColor_low;
  v8 = *(float *)(a2 + 200);
  this->m_fHeight = 1.0;
  this->m_fSize = v8;
  return result;
}

// 0x004C4060
char CEffCylinder::Create(int a2)
{
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  gbGeomQuad *v11; // eax
  int v12; // ebx
  int v13; // edi
  char ArgList[1024]; // [esp+Ch] [ebp-810h] BYREF
  _BYTE pExceptionObject[1024]; // [esp+40Ch] [ebp-410h] BYREF
  void *Block; // [esp+80Ch] [ebp-10h]
  int v18; // [esp+818h] [ebp-4h]
  int m_nDivision; // [esp+824h] [ebp+8h]

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
      v13 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v13 + *(_DWORD *)&this->_base[24]));
        v13 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)&this->_base[24]);
  }
LABEL_10:
  this->m_fRotAngle = *(float *)(a2 + 224);
  this->m_fWide = *(float *)(a2 + 228);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_nDivision = (int)*(float *)(a2 + 232);
  this->m_fTopShrink = *(float *)(a2 + 236);
  this->m_fBottomShrink = *(float *)(a2 + 240);
  this->m_fTopRadius = *(float *)(a2 + 244);
  this->m_fBottomRadius = *(float *)(a2 + 248);
  this->m_fTopRadiusIncSpeed = *(float *)(a2 + 252);
  this->m_fBottomRadiusIncSpeed = *(float *)(a2 + 256);
  this->m_fTopRiseSpeed = *(float *)(a2 + 260);
  this->m_fBottomRiseSpeed = *(float *)(a2 + 264);
  this->m_fTextureRepeat = *(float *)(a2 + 268);
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
  this->m_nRequireLoops = (int)&unk_FFFFFF;
  this->m_dwStartColor = *(_DWORD *)(a2 + 204);
  this->InitDefaultUVSet(*(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  m_nDivision = this->m_nDivision;
  v11 = (gbGeomQuad *)operator new(68 * m_nDivision);
  Block = v11;
  v18 = 0;
  if ( v11 )
  {
    v12 = (int)v11;
    if ( m_nDivision - 1 >= 0 )
    {
      do
      {
        ArraySort(v12, 12, 4, gbVec3D::`default constructor closure');
        v12 += 68;
        --m_nDivision;
      }
      while ( m_nDivision );
      v11 = (gbGeomQuad *)Block;
    }
  }
  else
  {
    v11 = 0;
  }
  v18 = -1;
  this->m_pGeomQuad = v11;
  if ( !v11 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffc, aDProjectPal3Co, 127),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->LoadTexture(a2 + 40);
  sub_4C5350((int)this);
  return 1;
}

// 0x004C4370
void CEffCylinder::Destroy()
{
  unsigned __int8 m_bAdditiveBlend; // al
  bool v3; // zf
  _DWORD *v4; // eax
  struct gbRenderEffect *v5; // ebp
  gbMatrixStack *v6; // edi
  float v7; // [esp+3Ch] [ebp-Ch]
  float retaddr; // [esp+48h] [ebp+0h] BYREF

  if ( (byte_DE937C & 1) == 0 )
  {
    dword_DE9370 = 1065353216;
    byte_DE937C |= 1u;
    dword_DE9374 = 0;
    dword_DE9378 = 0;
    atexit(nullsub_78);
  }
  if ( (byte_DE937C & 2) == 0 )
  {
    dword_DE9360 = 0;
    byte_DE937C |= 2u;
    dword_DE9364 = 1065353216;
    dword_DE9368 = 0;
    atexit(nullsub_77);
  }
  if ( (byte_DE937C & 4) == 0 )
  {
    dword_DE9350 = 0;
    byte_DE937C |= 4u;
    dword_DE9354 = 0;
    dword_DE9358 = 1065353216;
    atexit(nullsub_76);
  }
  if ( !this->_base[8] && this->m_bVisible )
  {
    ((gbVertPoolMgr *)*(gbVertPoolMgr **)(**(_DWORD **)&this->_base[4] + 196))->GetDynVertBuf(0x15u);
    m_bAdditiveBlend = this->m_bAdditiveBlend;
    if ( this->m_bNoZTest )
    {
      v3 = m_bAdditiveBlend == 0;
      v4 = (_DWORD *)*(_DWORD **)&this->_base[4];
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[3];
      else
        v5 = (struct gbRenderEffect *)v4[2];
    }
    else
    {
      v3 = m_bAdditiveBlend == 0;
      v4 = (_DWORD *)*(_DWORD **)&this->_base[4];
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[5];
      else
        v5 = (struct gbRenderEffect *)v4[4];
    }
    v6 = (gbMatrixStack *)*(gbMatrixStack **)(*v4 + 216);
    v6->Push();
    v7 = *(float *)this->m_vecOffsetPos + *(float *)this->m_vecPos;
    retaddr = v7;
    v6->Translate((struct gbVec3D *)&retaddr);
    v6->Rotate(*(float *)this->m_vecRot, (struct gbVec3D *)&dword_DE9370);
    v6->Rotate(*(float *)&this->m_vecRot[4], (struct gbVec3D *)&dword_DE9360);
    v6->Rotate(*(float *)&this->m_vecRot[8], (struct gbVec3D *)&dword_DE9350);
    v6->Scale(this->m_fSize, this->m_fHeight, this->m_fSize);
    ((gbDynVertBuf *)this->m_pGeomQuad)->RenderGeomQuadViaStrip(this->m_nDivision, v5, this->m_pTextureArray, this->m_dwStartColor);
    v6->Pop();
  }
}

// 0x004C45A0
void CEffCylinder::CreateTask(float a2)
{
  CEffCylinder *v2; // edi
  double v3; // st7
  char *v4; // esi
  int v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // eax
  int v13; // edx
  float *v14; // eax
  double v15; // st7
  int v16; // ecx
  double v17; // st7
  int v18; // eax
  float v20; // [esp+4h] [ebp-Ch]
  float v21; // [esp+4h] [ebp-Ch]
  int v22; // [esp+8h] [ebp-8h]
  float v23; // [esp+8h] [ebp-8h]
  int v24; // [esp+Ch] [ebp-4h]
  float v25; // [esp+Ch] [ebp-4h]
  int a2a; // [esp+18h] [ebp+8h]
  float a2b; // [esp+18h] [ebp+8h]

  v2 = this;
  v3 = a2 - *(float *)&this->_base[16];
  v4 = (char *)&this->_base[12];
  *(float *)&this->_base[16] = a2;
  *(float *)&this->_base[20] = v3;
  if ( *(float *)&this->_base[20] > 0.0 )
  {
    a2a = 0;
    if ( *(int *)&this->_base[40] > 0 )
    {
      v24 = 0;
      while ( 1 )
      {
        v5 = v24 + *((_DWORD *)v4 + 3);
        if ( *(_BYTE *)(v5 + 148) )
        {
          if ( *(_DWORD *)(v5 + 12) == 3 )
          {
            v6 = 0;
            v22 = 0;
            if ( *((int *)v4 + 8) > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++a2a < *((_DWORD *)v4 + 7);
        v24 += 152;
        if ( !v11 )
          goto LABEL_30;
      }
      v7 = 0;
      while ( 1 )
      {
        v8 = *(_DWORD *)v5 + v7;
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
                  sub_4D4D30(v4, a2a, v6);
                  *((_DWORD *)v4 + 4) = a2a;
                  *((_DWORD *)v4 + 5) = v22;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)(v24 + *((_DWORD *)v4 + 3)) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)(v24 + *((_DWORD *)v4 + 3)) + v7 + 16) = *((_DWORD *)v4 + 1);
LABEL_21:
                *((_DWORD *)v4 + 5) = v6;
                *((_DWORD *)v4 + 4) = a2a;
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
            if ( sub_4D4D70(v4, a2a) )
            {
              v9 = *(_DWORD *)(v5 + 4);
              *(_DWORD *)(v5 + 12) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = *(_BYTE *)(v5 + 149);
              *(_DWORD *)(v5 + 20) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                ((CEffgbParticle *)v4)->Init(a2a);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v22 + 1;
        v7 += 72;
        if ( ++v22 >= *((_DWORD *)v4 + 8) )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)&v2->_base[36] <= 0 )
      v2->_base[8] = 1;
    if ( !v2->_base[8] && (v2->m_fFramePerSec != 0.0 && v2->m_byMaxFrame != 1 || v2->m_fCurTextureV != 0.0) )
    {
      v20 = v2->m_fTextureRepeat / (double)v2->m_nDivision;
      v2->m_fCurFrame = v2->m_fFramePerSec * *(float *)&v2->_base[20] + v2->m_fCurFrame;
      if ( (g_bCursorVisible & 1) == 0 )
      {
        g_bCursorVisible |= 1u;
        ((CEffMgr *)&g_nCursorState)->Reset();
        atexit(nullsub_1);
      }
      v12 = (int)abs32((int)v2->m_fCurFrame) % v2->m_byMaxFrame;
      v13 = v12 + 13;
      v14 = (float *)&v2->_base[16 * v12];
      v25 = v14[49];
      v21 = (v14[51] - v25) * v20;
      a2b = v14[50] + v2->m_fCurTextureV;
      v23 = *(float *)&v2->_base[16 * v13] + v2->m_fCurTextureV;
      if ( (g_bCursorVisible & 1) == 0 )
      {
        g_bCursorVisible |= 1u;
        ((CEffMgr *)&g_nCursorState)->Reset();
        atexit(nullsub_1);
      }
      v15 = (double)(int)a2b;
      if ( v15 > 1.0 )
      {
        a2b = a2b - v15;
        v23 = v23 - v15;
      }
      v16 = 0;
      if ( v2->m_nDivision > 0 )
      {
        v17 = v25;
        v18 = 0;
        do
        {
          ++v16;
          *(float *)((char *)&v2->m_pGeomQuad->vec[4].x + v18) = v17;
          v17 = v17 + v21;
          v18 += 68;
          *(float *)((char *)&v2->m_pGeomQuad->vec[-1].x + v18) = v17;
          *(float *)((char *)&v2->m_pGeomQuad->vec[-1] + v18 - 4) = a2b;
          *(float *)((char *)v2->m_pGeomQuad->vec + v18 - 8) = v23;
        }
        while ( v16 < v2->m_nDivision );
      }
    }
  }
}

// 0x004C48D0
void CEffCylinder::ProcInitTask(_DWORD *a2)
{
  int *v2; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int (**v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int (**v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v2 = (int *)&this->_base[12];
  v3 = *(_DWORD *)&this->_base[40];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = v2[3];
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(v2[3] + v7 + 148) = 1;
    *(_BYTE *)(v2[3] + v7 + 149) = 1;
    v8 = ++dword_DE9380;
    if ( !dword_DE9380 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      dword_DE9380 = 1;
    }
    *(_DWORD *)(v2[3] + v7 + 16) = v8;
    *(_DWORD *)(v2[3] + v7 + 4) = 0;
    *(_DWORD *)(v2[3] + v7 + 8) = 0;
    *(_DWORD *)(v2[3] + v7 + 20) = 0;
    if ( a2 )
      qmemcpy((void *)(v2[3] + v7 + 24), a2, 0x7Cu);
    else
      memset((void *)(v2[3] + v7 + 24), 0, 0x7Cu);
    ++v2[6];
    if ( v4 != -1 )
    {
      v9 = v2[8];
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(v2[3] + 152 * v4);
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
        * v13 = (*)CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int (*)(CEffect *, int))2;
        v14 = ++dword_DE9380;
        if ( !dword_DE9380 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          dword_DE9380 = 1;
        }
        v13[3] = (int (*)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(v2[3] + v7 + 4);
      }
LABEL_22:
      v15 = v2[8];
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(v2[3] + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int (**)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        * v19 = (*)CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int (*)(CEffect *, int))2;
        v20 = ++dword_DE9380;
        if ( !dword_DE9380 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          dword_DE9380 = 1;
        }
        v19[3] = (int (*)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(v2[3] + v7 + 4);
      }
LABEL_31:
      sub_4C55F0(v2, v4, (int)CEffCylinder::ProcCommonTask, 0, 0, a2[18], a2[19]);
      *(_DWORD *)(v2[3] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(v2[3] + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(v2[3] + v7) + 16) = v2[1];
    }
  }
}

// 0x004C4B00
int CEffCylinder::ProcCommonTask(int a2)
{
  double v3; // st7
  int v4; // edi
  int v5; // ecx
  double v6; // st7
  int v7; // ebp
  double v8; // st7
  double m_fAlpha; // st7
  double m_fRed; // st7
  double m_fGreen; // st7
  double m_fBlue; // st7
  unsigned __int16 v13; // cx
  float v15; // [esp+0h] [ebp-80h]
  float v16; // [esp+14h] [ebp-6Ch]
  float v17; // [esp+18h] [ebp-68h]
  float v18; // [esp+1Ch] [ebp-64h]
  float v19; // [esp+20h] [ebp-60h]
  float v20; // [esp+24h] [ebp-5Ch]
  gbVec3D v21; // [esp+28h] [ebp-58h] BYREF
  struct gbVec3D v22; // [esp+34h] [ebp-4Ch] BYREF
  _BYTE v23[64]; // [esp+40h] [ebp-40h] BYREF

  v3 = *(float *)&this->_base[16];
  v4 = *(_DWORD *)&this->_base[24] + 152 * *(_DWORD *)&this->_base[28];
  v5 = 9 * *(_DWORD *)&this->_base[32];
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  v16 = *(float *)&this->_base[20];
  if ( v6 > *(float *)(v7 + 24) )
    v16 = v16 - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    this->m_bVisible = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  *(float *)this->m_vecRot = v16 * *(float *)(v4 + 64) + *(float *)this->m_vecRot;
  *(float *)&this->m_vecRot[4] = v16 * *(float *)(v4 + 68) + *(float *)&this->m_vecRot[4];
  *(float *)&this->m_vecRot[8] = v16 * *(float *)(v4 + 72) + *(float *)&this->m_vecRot[8];
  *(float *)this->m_vecPos = v16 * *(float *)(v4 + 28) + *(float *)this->m_vecPos;
  *(float *)&this->m_vecPos[4] = v16 * *(float *)(v4 + 32) + *(float *)&this->m_vecPos[4];
  *(float *)&this->m_vecPos[8] = v16 * *(float *)(v4 + 36) + *(float *)&this->m_vecPos[8];
  ((gbMatrix4 *)v23)->gbMatrix4();
  memset(&v21, 0, sizeof(v21));
  memset(&v22, 0, sizeof(v22));
  ((gbMatrix4 *)v23)->LoadIdentity();
  v21 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v21)->Normalize();
  v15 = (*(float *)&this->_base[16] - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  ((gbMatrix4 *)v23)->SetAxisAngle(&v21, v15);
  v22.z = *(float *)(v4 + 56);
  v22.x = 0.0;
  v22.y = 0.0;
  ((gbMatrix4 *)v23)->Rotate(&v22, (struct gbVec3D *)this->m_vecOffsetPos);
  v8 = v16 * *(float *)(v4 + 108) + this->m_fCurTextureV;
  this->m_fCurTextureV = v8;
  if ( v8 > 1.0 )
    this->m_fCurTextureV = 0.0;
  if ( *(float *)(v4 + 80) != 0.0
    || *(float *)(v4 + 84) != 0.0
    || *(float *)(v4 + 92) != 0.0
    || *(float *)(v4 + 88) != 0.0 )
  {
    this->m_fAlpha = v16 * *(float *)(v4 + 80) + this->m_fAlpha;
    this->m_fRed = v16 * *(float *)(v4 + 84) + this->m_fRed;
    this->m_fGreen = v16 * *(float *)(v4 + 88) + this->m_fGreen;
    this->m_fBlue = v16 * *(float *)(v4 + 92) + this->m_fBlue;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( this->m_fAlpha <= 255.0 )
    {
      if ( this->m_fAlpha >= 0.0 )
        m_fAlpha = this->m_fAlpha;
      else
        m_fAlpha = 0.0;
    }
    else
    {
      m_fAlpha = 255.0;
    }
    this->m_fAlpha = m_fAlpha;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( this->m_fRed <= 255.0 )
    {
      if ( this->m_fRed >= 0.0 )
        m_fRed = this->m_fRed;
      else
        m_fRed = 0.0;
    }
    else
    {
      m_fRed = 255.0;
    }
    this->m_fRed = m_fRed;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( this->m_fGreen <= 255.0 )
    {
      if ( this->m_fGreen >= 0.0 )
        m_fGreen = this->m_fGreen;
      else
        m_fGreen = 0.0;
    }
    else
    {
      m_fGreen = 255.0;
    }
    this->m_fGreen = m_fGreen;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( this->m_fBlue <= 255.0 )
    {
      if ( this->m_fBlue >= 0.0 )
        m_fBlue = this->m_fBlue;
      else
        m_fBlue = 0.0;
    }
    else
    {
      m_fBlue = 255.0;
    }
    this->m_fBlue = m_fBlue;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v17 = this->m_fAlpha + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v18 = this->m_fRed + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v19 = this->m_fGreen + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v20 = this->m_fBlue + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    HIBYTE(v13) = LOBYTE(v17);
    LOBYTE(v13) = LOBYTE(v18);
    this->m_dwStartColor = LOBYTE(v20) | ((LOBYTE(v19) | (v13 << 8)) << 8);
  }
  this->m_fSize = v16 * *(float *)(v4 + 24) + this->m_fSize;
  this->m_fHeight = v16 * *(float *)(v4 + 116) + this->m_fHeight;
  if ( *(_BYTE *)(v7 + 66) == 1 || *(float *)&this->_base[16] - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
    *(_DWORD *)(v7 + 8) = 4;
  return 0;
}

// 0x004C5010
void * CEffCylinder::GetEditorTaskDescription(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = (void *)&unk_5D5050;
      break;
    case 1:
      result = (void *)&unk_5D4E40;
      break;
    case 2:
      result = (void *)&unk_5D4E38;
      break;
    case 3:
      result = (void *)&unk_5D4E30;
      break;
    case 4:
      result = (void *)&unk_5D4E24;
      break;
    case 5:
      result = (void *)&unk_5D5048;
      break;
    case 6:
      result = (void *)&unk_5D5040;
      break;
    case 7:
      result = (void *)&unk_5D5038;
      break;
    case 8:
      result = (void *)&unk_5D4E00;
      break;
    case 9:
      result = (void *)&unk_5D4DF4;
      break;
    case 10:
      result = (void *)&unk_5D502C;
      break;
    case 11:
      result = (void *)&unk_5D5020;
      break;
    case 12:
      result = (void *)&unk_5D4DD4;
      break;
    case 13:
      result = (void *)&unk_5D4DCC;
      break;
    case 14:
      result = (void *)&unk_5D4DC4;
      break;
    case 15:
      result = (void *)&unk_5D4DB8;
      break;
    case 16:
      result = (void *)&unk_5D4DAC;
      break;
    case 17:
      result = (void *)&unk_5D5014;
      break;
    case 18:
      result = (void *)&unk_5D5008;
      break;
    case 19:
      result = (void *)&unk_5D4FFC;
      break;
    case 20:
      result = (void *)&unk_5D4D7C;
      break;
    case 21:
      result = (void *)&unk_5D4FF0;
      break;
    case 22:
      result = (void *)&unk_5D4FE0;
      break;
    case 23:
      result = (void *)&unk_5D4FD0;
      break;
    default:
      result = (void *)&unk_5D4D3C;
      break;
  }
  return result;
}

// 0x004C5150
void * CEffCylinder::GetEditorObjDescription(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = (void *)&unk_5D50E4;
      break;
    case 1:
      result = (void *)&unk_5D50D8;
      break;
    case 2:
      result = (void *)&unk_5D50CC;
      break;
    case 3:
      result = (void *)&unk_5D50C0;
      break;
    case 4:
      result = (void *)&unk_5D50B8;
      break;
    case 5:
      result = (void *)&unk_5D50B0;
      break;
    case 6:
      result = (void *)&unk_5D50A4;
      break;
    case 7:
      result = (void *)&unk_5D5098;
      break;
    case 8:
      result = (void *)&unk_5D508C;
      break;
    case 9:
      result = (void *)&unk_5D5080;
      break;
    case 10:
      result = (void *)&unk_5D5074;
      break;
    case 11:
      result = (void *)&unk_5D5068;
      break;
    case 12:
      result = (void *)&unk_5D505C;
      break;
    default:
      result = (void *)&unk_5D4D3C;
      break;
  }
  return result;
}

// 0x004C5210
void CEffCylinder::InitDefaultUVSet(int a2, int a3)
{
  int v3; // ebx
  char *v4; // edi
  int v5; // ecx
  double v6; // st7
  char *v7; // eax
  double v8; // st5
  double v9; // st5
  double v10; // st3
  double v11; // st3
  int v12; // [esp+8h] [ebp-8h]
  float v13; // [esp+8h] [ebp-8h]
  int v14; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v12 = 0;
  if ( a3 > 0 )
  {
    v4 = (char *)&this->m_DefaultUVSet[8];
    do
    {
      v5 = 0;
      v14 = 0;
      if ( a2 > 0 )
      {
        v6 = (double)a2;
        v7 = v4;
        v4 += 16 * a2;
        v8 = (double)a3;
        v13 = (double)v12 / v8;
        v9 = 1.0 - (1.0 / v8 + v13);
        do
        {
          v10 = (double)v14;
          v7 += 16;
          v14 = ++v5;
          v11 = v10 / v6;
          *((float *)v7 - 6) = v11;
          *((float *)v7 - 4) = 1.0 / v6 + v11;
          *((float *)v7 - 5) = v9;
          *((float *)v7 - 3) = 1.0 - v13;
        }
        while ( v5 < a2 );
      }
      v12 = ++v3;
    }
    while ( v3 < a3 );
  }
}

// 0x004C52C0
_DWORD * CEffCylinder::LoadTexture(int a2)
{
  gbTexture *v3; // eax
  _DWORD *result; // eax
  gbTexture *m_pTexture; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(***(_DWORD ***)&this->_base[4] + 8))(
                      **(_DWORD **)&this->_base[4],
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
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co, 504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}
