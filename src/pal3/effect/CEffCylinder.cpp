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
  *(_DWORD *)this = &off_56F62C;
}

// 0x004C3EC0
int CEffCylinder::Init(int a2, float a3, float a4, float a5)
{
  int result; // eax
  int v7; // ecx
  int v8; // edx

  *((_BYTE *)this + 8) = 0;
  *((_BYTE *)this + 60) = 0;
  *((float *)this + 43) = a3 + *(float *)(a2 + 184);
  *((float *)this + 44) = a4 + *(float *)(a2 + 188);
  *((float *)this + 45) = a5 + *(float *)(a2 + 192);
  *((_DWORD *)this + 40) = *(_DWORD *)(a2 + 216);
  *((_DWORD *)this + 41) = *(_DWORD *)(a2 + 196);
  *((_DWORD *)this + 42) = *(_DWORD *)(a2 + 220);
  *((_DWORD *)this + 48) = 0;
  *((_DWORD *)this + 47) = 0;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 19) = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *((float *)this + 20) = (float)HIBYTE(*((_DWORD *)this + 19));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *((float *)this + 21) = (float)(unsigned __int8)BYTE2(*((_DWORD *)this + 19));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  result = (unsigned __int8)BYTE1(*((_DWORD *)this + 19));
  *((float *)this + 22) = (float)result;
  LOBYTE(result) = g_bCursorVisible;
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    result = atexit(nullsub_1);
  }
  *((_DWORD *)this + 39) = 0;
  v7 = *((unsigned __int8 *)this + 76);
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 17) = 0;
  *((float *)this + 23) = (float)v7;
  v8 = *(_DWORD *)(a2 + 200);
  *((_DWORD *)this + 25) = 1065353216;
  *((_DWORD *)this + 24) = v8;
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
  void *v11; // eax
  int v12; // ebx
  int v13; // edi
  char ArgList[1024]; // [esp+Ch] [ebp-810h] BYREF
  _BYTE pExceptionObject[1024]; // [esp+40Ch] [ebp-410h] BYREF
  void *Block; // [esp+80Ch] [ebp-10h]
  int v18; // [esp+818h] [ebp-4h]
  int v19; // [esp+824h] [ebp+8h]

  v3 = (_DWORD *)operator new(0x4C0u);
  *((_DWORD *)this + 6) = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v5 + *((_DWORD *)this + 6)) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v5 + *((_DWORD *)this + 6)) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *((_DWORD *)this + 10) = 8;
        *((_DWORD *)this + 11) = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(v7 + *((_DWORD *)this + 6) + 148) = 0;
          v8 = 0;
          if ( *((int *)this + 11) > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(*(_DWORD *)(v7 + *((_DWORD *)this + 6)) + v9 - 8) = 0;
            }
            while ( v8 < *((_DWORD *)this + 11) );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *((_DWORD *)this + 10) );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v13 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v13 + *((_DWORD *)this + 6)));
        v13 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*((void **)this + 6));
  }
LABEL_10:
  *((_DWORD *)this + 26) = *(_DWORD *)(a2 + 224);
  *((_DWORD *)this + 27) = *(_DWORD *)(a2 + 228);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *((_DWORD *)this + 28) = (int)*(float *)(a2 + 232);
  *((_DWORD *)this + 29) = *(_DWORD *)(a2 + 236);
  *((_DWORD *)this + 30) = *(_DWORD *)(a2 + 240);
  *((_DWORD *)this + 31) = *(_DWORD *)(a2 + 244);
  *((_DWORD *)this + 32) = *(_DWORD *)(a2 + 248);
  *((_DWORD *)this + 33) = *(_DWORD *)(a2 + 252);
  *((_DWORD *)this + 34) = *(_DWORD *)(a2 + 256);
  *((_DWORD *)this + 35) = *(_DWORD *)(a2 + 260);
  *((_DWORD *)this + 36) = *(_DWORD *)(a2 + 264);
  *((_DWORD *)this + 37) = *(_DWORD *)(a2 + 268);
  *((_DWORD *)this + 38) = *(_DWORD *)(a2 + 180);
  *((_DWORD *)this + 43) = *(_DWORD *)(a2 + 184);
  *((_DWORD *)this + 44) = *(_DWORD *)(a2 + 188);
  *((_DWORD *)this + 45) = *(_DWORD *)(a2 + 192);
  *((_DWORD *)this + 40) = *(_DWORD *)(a2 + 216);
  *((_DWORD *)this + 41) = *(_DWORD *)(a2 + 196);
  *((_DWORD *)this + 42) = *(_DWORD *)(a2 + 220);
  *((_DWORD *)this + 61) = *(CEffCylinder *)(a2 + 213);
  *((_DWORD *)this + 62) = *(CEffCylinder *)(a2 + 215);
  *((_DWORD *)this + 63) = *(CEffCylinder *)(a2 + 176);
  *((_DWORD *)this + 16) = &unk_FFFFFF;
  *((_DWORD *)this + 19) = *(_DWORD *)(a2 + 204);
  this->InitDefaultUVSet(*(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  v19 = *((_DWORD *)this + 28);
  v11 = (void *)operator new(68 * v19);
  Block = v11;
  v18 = 0;
  if ( v11 )
  {
    v12 = (int)v11;
    if ( v19 - 1 >= 0 )
    {
      do
      {
        ArraySort(v12, 12, 4, gbVec3D::`default constructor closure');
        v12 += 68;
        --v19;
      }
      while ( v19 );
      v11 = Block;
    }
  }
  else
  {
    v11 = 0;
  }
  v18 = -1;
  *((_DWORD *)this + 12) = v11;
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
  char v2; // al
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
  if ( !*((_BYTE *)this + 8) && *((_BYTE *)this + 60) )
  {
    ((gbVertPoolMgr *)*(gbVertPoolMgr **)(**((_DWORD **)this + 1) + 196))->GetDynVertBuf(0x15u);
    v2 = *((_BYTE *)this + 61);
    if ( *((_BYTE *)this + 62) )
    {
      v3 = v2 == 0;
      v4 = (_DWORD *)*((_DWORD *)this + 1);
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[3];
      else
        v5 = (struct gbRenderEffect *)v4[2];
    }
    else
    {
      v3 = v2 == 0;
      v4 = (_DWORD *)*((_DWORD *)this + 1);
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[5];
      else
        v5 = (struct gbRenderEffect *)v4[4];
    }
    v6 = (gbMatrixStack *)*(gbMatrixStack **)(*v4 + 216);
    v6->Push();
    v7 = *((float *)this + 46) + *((float *)this + 43);
    retaddr = v7;
    v6->Translate((struct gbVec3D *)&retaddr);
    v6->Rotate(*((float *)this + 40), (struct gbVec3D *)&dword_DE9370);
    v6->Rotate(*((float *)this + 41), (struct gbVec3D *)&dword_DE9360);
    v6->Rotate(*((float *)this + 42), (struct gbVec3D *)&dword_DE9350);
    v6->Scale(*((float *)this + 24), *((float *)this + 25), *((float *)this + 24));
    ((gbDynVertBuf *)*((struct gbGeomQuad **)this + 12))->RenderGeomQuadViaStrip(*((_DWORD *)this + 28), v5, *((struct gbTextureArray **)this + 14), *((_DWORD *)this + 19));
    v6->Pop();
  }
}

// 0x004C45A0
void CEffCylinder::CreateTask(float a2)
{
  CEffCylinder *v2; // edi
  double v3; // st7
  CEffCylinder *v4; // esi
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
  v3 = a2 - *((float *)this + 4);
  v4 = (CEffCylinder *)this + 12;
  *((float *)this + 4) = a2;
  *((float *)this + 5) = v3;
  if ( *((float *)this + 5) > 0.0 )
  {
    a2a = 0;
    if ( *((int *)this + 10) > 0 )
    {
      v24 = 0;
      while ( 1 )
      {
        v5 = v24 + *(_DWORD *)&v4[12];
        if ( *(_BYTE *)(v5 + 148) )
        {
          if ( *(_DWORD *)(v5 + 12) == 3 )
          {
            v6 = 0;
            v22 = 0;
            if ( *(int *)&v4[32] > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++a2a < *(_DWORD *)&v4[28];
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
                if ( *(float *)&v4[4] - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  sub_4D4D30(v4, a2a, v6);
                  *(_DWORD *)&v4[16] = a2a;
                  *(_DWORD *)&v4[20] = v22;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)(v24 + *(_DWORD *)&v4[12]) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)(v24 + *(_DWORD *)&v4[12]) + v7 + 16) = *(_DWORD *)&v4[4];
LABEL_21:
                *(_DWORD *)&v4[20] = v6;
                *(_DWORD *)&v4[16] = a2a;
LABEL_24:
                (*(void (**)(CEffCylinder *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4 + 4))(
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
        if ( ++v22 >= *(_DWORD *)&v4[32] )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)&v2[36] <= 0 )
      v2[8] = (CEffCylinder)1;
    if ( !*(_BYTE *)&v2[8] && (*(float *)&v2[152] != 0.0 && *(_BYTE *)&v2[63] != 1 || *(float *)&v2[156] != 0.0) )
    {
      v20 = *(float *)&v2[148] / (double)*(int *)&v2[112];
      *(float *)&v2[72] = *(float *)&v2[152] * *(float *)&v2[20] + *(float *)&v2[72];
      if ( (g_bCursorVisible & 1) == 0 )
      {
        g_bCursorVisible |= 1u;
        ((CEffMgr *)&g_nCursorState)->Reset();
        atexit(nullsub_1);
      }
      v12 = (int)abs32(*(_DWORD *)&v2[72]) % *(_BYTE *)&v2[63];
      v13 = v12 + 13;
      v14 = (float *)&v2[16 * v12];
      v25 = v14[49];
      v21 = (v14[51] - v25) * v20;
      a2b = v14[50] + *(float *)&v2[156];
      v23 = *(float *)&v2[16 * v13] + *(float *)&v2[156];
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
      if ( *(int *)&v2[112] > 0 )
      {
        v17 = v25;
        v18 = 0;
        do
        {
          ++v16;
          *(float *)(v18 + *(_DWORD *)&v2[48] + 48) = v17;
          v17 = v17 + v21;
          v18 += 68;
          *(float *)(v18 + *(_DWORD *)&v2[48] - 12) = v17;
          *(float *)(v18 + *(_DWORD *)&v2[48] - 16) = a2b;
          *(float *)(v18 + *(_DWORD *)&v2[48] - 8) = v23;
        }
        while ( v16 < *(_DWORD *)&v2[112] );
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

  v2 = (int *)(this + 12);
  v3 = *((_DWORD *)this + 10);
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
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
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

  v3 = *((float *)this + 4);
  v4 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v5 = 9 * *((_DWORD *)this + 8);
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  v16 = *((float *)this + 5);
  if ( v6 > *(float *)(v7 + 24) )
    v16 = v16 - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    *((_BYTE *)this + 60) = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  *((float *)this + 40) = v16 * *(float *)(v4 + 64) + *((float *)this + 40);
  *((float *)this + 41) = v16 * *(float *)(v4 + 68) + *((float *)this + 41);
  *((float *)this + 42) = v16 * *(float *)(v4 + 72) + *((float *)this + 42);
  *((float *)this + 43) = v16 * *(float *)(v4 + 28) + *((float *)this + 43);
  *((float *)this + 44) = v16 * *(float *)(v4 + 32) + *((float *)this + 44);
  *((float *)this + 45) = v16 * *(float *)(v4 + 36) + *((float *)this + 45);
  ((gbMatrix4 *)v23)->gbMatrix4();
  memset(&v21, 0, sizeof(v21));
  memset(&v22, 0, sizeof(v22));
  ((gbMatrix4 *)v23)->LoadIdentity();
  v21 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v21)->Normalize();
  v15 = (*((float *)this + 4) - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  ((gbMatrix4 *)v23)->SetAxisAngle(&v21, v15);
  v22.z = *(float *)(v4 + 56);
  v22.x = 0.0;
  v22.y = 0.0;
  ((gbMatrix4 *)v23)->Rotate(&v22, (struct gbVec3D *)(this + 184));
  v8 = v16 * *(float *)(v4 + 108) + *((float *)this + 39);
  *((float *)this + 39) = v8;
  if ( v8 > 1.0 )
    *((_DWORD *)this + 39) = 0;
  if ( *(float *)(v4 + 80) != 0.0
    || *(float *)(v4 + 84) != 0.0
    || *(float *)(v4 + 92) != 0.0
    || *(float *)(v4 + 88) != 0.0 )
  {
    *((float *)this + 20) = v16 * *(float *)(v4 + 80) + *((float *)this + 20);
    *((float *)this + 21) = v16 * *(float *)(v4 + 84) + *((float *)this + 21);
    *((float *)this + 22) = v16 * *(float *)(v4 + 88) + *((float *)this + 22);
    *((float *)this + 23) = v16 * *(float *)(v4 + 92) + *((float *)this + 23);
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( *((float *)this + 20) <= 255.0 )
    {
      if ( *((float *)this + 20) >= 0.0 )
        v9 = *((float *)this + 20);
      else
        v9 = 0.0;
    }
    else
    {
      v9 = 255.0;
    }
    *((float *)this + 20) = v9;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( *((float *)this + 21) <= 255.0 )
    {
      if ( *((float *)this + 21) >= 0.0 )
        v10 = *((float *)this + 21);
      else
        v10 = 0.0;
    }
    else
    {
      v10 = 255.0;
    }
    *((float *)this + 21) = v10;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( *((float *)this + 22) <= 255.0 )
    {
      if ( *((float *)this + 22) >= 0.0 )
        v11 = *((float *)this + 22);
      else
        v11 = 0.0;
    }
    else
    {
      v11 = 255.0;
    }
    *((float *)this + 22) = v11;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( *((float *)this + 23) <= 255.0 )
    {
      if ( *((float *)this + 23) >= 0.0 )
        v12 = *((float *)this + 23);
      else
        v12 = 0.0;
    }
    else
    {
      v12 = 255.0;
    }
    *((float *)this + 23) = v12;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v17 = *((float *)this + 20) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v18 = *((float *)this + 21) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v19 = *((float *)this + 22) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v20 = *((float *)this + 23) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    HIBYTE(v13) = LOBYTE(v17);
    LOBYTE(v13) = LOBYTE(v18);
    *((_DWORD *)this + 19) = LOBYTE(v20) | ((LOBYTE(v19) | (v13 << 8)) << 8);
  }
  *((float *)this + 24) = v16 * *(float *)(v4 + 24) + *((float *)this + 24);
  *((float *)this + 25) = v16 * *(float *)(v4 + 116) + *((float *)this + 25);
  if ( *(_BYTE *)(v7 + 66) == 1 || *((float *)this + 4) - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
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
  CEffCylinder *v4; // edi
  int v5; // ecx
  double v6; // st7
  CEffCylinder *v7; // eax
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
    v4 = (CEffCylinder *)this + 204;
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
          *(float *)&v7[-24] = v11;
          *(float *)&v7[-16] = 1.0 / v6 + v11;
          *(float *)&v7[-20] = v9;
          *(float *)&v7[-12] = 1.0 - v13;
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
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(***((_DWORD ***)this + 1) + 8))(**((_DWORD **)this + 1), a2);
  *((_DWORD *)this + 13) = v3;
  v3->LoadTexture(1);
  result = (_DWORD *)operator new(0x44u);
  if ( result )
  {
    v5 = *((_DWORD *)this + 13);
    result[16] = 1;
    *result = v5;
  }
  else
  {
    result = 0;
  }
  *((_DWORD *)this + 14) = result;
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
