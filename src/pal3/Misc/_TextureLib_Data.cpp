#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/_TextureLib_Data.h"

// 0x0053FFA0
void sub_53FFA0()
{
  if ( dword_1895048 )
  {
    (gbRefObject *->Release()dword_1895048);
    dword_1895048 = 0;
  }
  if ( dword_189504C )
  {
    (gbRefObject *->Release()dword_189504C);
    dword_189504C = 0;
  }
  if ( dword_1895054 )
  {
    (gbRefObject *->Release()dword_1895054);
    dword_1895054 = 0;
  }
  if ( dword_189505C )
  {
    (gbRefObject *->Release()dword_189505C);
    dword_189505C = 0;
  }
  if ( dword_1895068 )
  {
    (gbRefObject *->Release()dword_1895068);
    dword_1895068 = 0;
  }
  if ( dword_1895050 )
  {
    (gbRefObject *->Release()dword_1895050);
    dword_1895050 = 0;
  }
  if ( dword_1895058 )
  {
    (gbRefObject *->Release()dword_1895058);
    dword_1895058 = 0;
  }
  if ( dword_1895060 )
  {
    (gbRefObject *->Release()dword_1895060);
    dword_1895060 = 0;
  }
  if ( dword_1895064 )
  {
    (gbRefObject *->Release()dword_1895064);
    dword_1895064 = 0;
  }
  if ( dword_189506C )
  {
    (gbRefObject *->Release()dword_189506C);
    dword_189506C = 0;
  }
}

// 0x00540070
void sub_540070(int a1, int a2, int a3, int a4, float *a5)
{
  gbDynVertBuf *DynVertBuf; // eax
  float v6[10]; // [esp+4h] [ebp-28h] BYREF

  v6[8] = 0.0;
  v6[0] = (float)a1;
  v6[9] = *a5;
  v6[3] = (float)a2;
  v6[2] = (float)a3;
  v6[1] = (float)a4;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x114u);
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)v6, 1, (struct gbRenderEffect *)dword_1895050, 0);
}

// 0x005400E0
void sub_5400E0(int *a1, struct gbTextureArray *a2, int a3, int a4)
{
  float v4; // ecx
  int v5; // ecx
  long double v6; // st7
  double v7; // st7
  struct gbRenderEffect *v8; // esi
  gbDynVertBuf *DynVertBuf; // eax
  float v10[4]; // [esp+8h] [ebp-28h] BYREF
  int v11; // [esp+18h] [ebp-18h]
  int v12; // [esp+1Ch] [ebp-14h]
  float v13; // [esp+20h] [ebp-10h]
  float v14; // [esp+24h] [ebp-Ch]
  int v15; // [esp+28h] [ebp-8h]
  int v16; // [esp+2Ch] [ebp-4h]
  int v17; // [esp+3Ch] [ebp+Ch]
  int v18; // [esp+3Ch] [ebp+Ch]
  float v19; // [esp+3Ch] [ebp+Ch]

  v16 = a3;
  v15 = 0;
  if ( a4 )
  {
    v11 = *(_DWORD *)(a4 + 1048);
    v12 = *(_DWORD *)(a4 + 1052);
    v4 = *(float *)(a4 + 1068);
    v13 = *(float *)(a4 + 1064);
    v14 = v4;
  }
  else
  {
    v5 = *(_DWORD *)a2;
    v17 = a1[2] - *a1;
    v12 = 0;
    v11 = 0;
    v6 = (fabs((double)v17) + -0.5) / (double)*(int *)(v5 + 24);
    v18 = a1[3] - a1[1];
    v13 = v6;
    v14 = (fabs((double)v18) + -0.5) / (double)*(int *)(v5 + 28);
  }
  v7 = (double)MEMORY[0xBFD6D0];
  v8 = (struct gbRenderEffect *)dword_1895048;
  v10[0] = ((double)*a1 + (double)*a1) / v7 - 1.0;
  v19 = (float)MEMORY[0xBFD6D4];
  v10[3] = 1.0 - ((double)a1[1] + (double)a1[1]) / v19;
  v10[2] = ((double)a1[2] + (double)a1[2]) / v7 - 1.0;
  v10[1] = 1.0 - ((double)a1[3] + (double)a1[3]) / v19;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x15u);
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)v10, 1, v8, a2);
}

// 0x00540210
void sub_540210(_DWORD *a1, int *a2, struct gbTextureArray *a3, int a4, unsigned int a5, float *a6)
{
  int v6; // edx
  float v7; // eax
  float v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  struct gbRenderEffect *v11; // esi
  double v12; // st7
  double v14; // st7
  __int64 v15; // rax
  double v16; // st7
  gbDynVertBuf *DynVertBuf; // eax
  __int64 v18; // [esp+10h] [ebp-30h]
  __int64 v19; // [esp+10h] [ebp-30h]
  float v20; // [esp+18h] [ebp-28h] BYREF
  float v21; // [esp+1Ch] [ebp-24h]
  float v22; // [esp+20h] [ebp-20h]
  float v23; // [esp+24h] [ebp-1Ch]
  int v24; // [esp+28h] [ebp-18h]
  int v25; // [esp+2Ch] [ebp-14h]
  float v26; // [esp+30h] [ebp-10h]
  float v27; // [esp+34h] [ebp-Ch]
  int v28; // [esp+38h] [ebp-8h]
  int v29; // [esp+3Ch] [ebp-4h]
  float v30; // [esp+48h] [ebp+8h]
  int v31; // [esp+50h] [ebp+10h]

  v28 = 0;
  v29 = a4;
  if ( a6 )
  {
    v6 = *((_DWORD *)a6 + 263);
    v7 = a6[266];
    v24 = *((_DWORD *)a6 + 262);
    v8 = a6[267];
    v25 = v6;
    v26 = v7;
    v27 = v8;
  }
  else
  {
    v9 = *(_DWORD *)a3;
    v25 = 0;
    v24 = 0;
    v31 = a1[3] - a1[1];
    v26 = (fabs((double)(a1[2] - *a1)) + -0.5) / (double)*(int *)(v9 + 24);
    v27 = (fabs((double)v31) + -0.5) / (double)*(int *)(v9 + 28);
  }
  if ( (a5 & 0x100) != 0 )
  {
    v20 = (float)*a2;
    v23 = (double)a2[1] - 0.5;
    if ( a6 )
    {
      v10 = *((_DWORD *)a6 + 260);
      v18 = v10;
      *(float *)&v18 = a6[261];
      v11 = (struct gbRenderEffect *)dword_189504C;
      v22 = (double)v10 + v20 + 0.5;
      v12 = (double)v18 + v23 + 0.5;
    }
    else
    {
      v11 = (struct gbRenderEffect *)dword_189504C;
      v22 = (float)a2[2];
      v12 = (double)a2[3];
    }
    v21 = v12;
  }
  else
  {
    v14 = (double)MEMORY[0xBFD6D0];
    v20 = ((double)*a2 + (double)*a2) / v14 - 1.0;
    v30 = (float)MEMORY[0xBFD6D4];
    v23 = 1.0 - ((double)a2[1] + (double)a2[1]) / v30;
    if ( a6 )
    {
      v15 = (__int64)((double)*((unsigned int *)a6 + 260) + v20 + 0.5);
      v19 = *((unsigned int *)a6 + 261);
      v22 = ((double)(int)v15 + (double)(int)v15) / v14 - 1.0;
      v16 = (double)(int)(__int64)((double)v19 + v23 + 0.5);
    }
    else
    {
      v22 = ((double)a2[2] + (double)a2[2]) / v14 - 1.0;
      v16 = (double)a2[3];
    }
    v11 = (struct gbRenderEffect *)dword_1895048;
    v21 = 1.0 - (v16 + v16) / v30;
  }
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), a5);
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)&v20, 1, v11, a3);
}

// 0x00540440
void sub_540440(
        int *a1,
        unsigned int *a2,
        struct gbTextureArray *a3,
        unsigned int a4,
        unsigned int *a5,
        float a6)
{
  __int64 v6; // rcx
  unsigned int v7; // ecx
  float v8; // edx
  float v9; // ecx
  int v10; // ecx
  long double v11; // st7
  double v12; // st7
  struct gbRenderEffect *v13; // esi
  double v14; // st6
  __int64 v15; // rax
  double v16; // st5
  gbDynVertBuf *DynVertBuf; // eax
  __int64 v18; // [esp+10h] [ebp-30h]
  float v19; // [esp+18h] [ebp-28h] BYREF
  float v20; // [esp+1Ch] [ebp-24h]
  float v21; // [esp+20h] [ebp-20h]
  float v22; // [esp+24h] [ebp-1Ch]
  unsigned int v23; // [esp+28h] [ebp-18h]
  unsigned int v24; // [esp+2Ch] [ebp-14h]
  float v25; // [esp+30h] [ebp-10h]
  float v26; // [esp+34h] [ebp-Ch]
  int v27; // [esp+38h] [ebp-8h]
  int v28; // [esp+3Ch] [ebp-4h]
  int v29; // [esp+48h] [ebp+8h]
  int v30; // [esp+48h] [ebp+8h]
  float v31; // [esp+48h] [ebp+8h]
  float v32; // [esp+58h] [ebp+18h]

  v6 = *a2;
  v27 = 0;
  v28 = v6;
  if ( a5 )
  {
    v7 = a5[263];
    v23 = a5[262];
    v8 = *((float *)a5 + 266);
    v24 = v7;
    v9 = *((float *)a5 + 267);
    v25 = v8;
    v26 = v9;
  }
  else
  {
    v10 = *(_DWORD *)a3;
    v29 = a1[2] - *a1;
    v24 = 0;
    v23 = 0;
    v11 = (fabs((double)v29) + -0.5) / (double)*(int *)(v10 + 24);
    v30 = a1[3] - a1[1];
    v25 = v11;
    v26 = (fabs((double)v30) + -0.5) / (double)*(int *)(v10 + 28);
  }
  if ( (a4 & 0x100) != 0 )
  {
    v12 = (double)*a1;
    v22 = (float)a1[1];
    if ( a5 == (unsigned int *)HIDWORD(v6) || LOBYTE(a6) == BYTE4(v6) )
    {
      v14 = (double)a1[2];
      v13 = (struct gbRenderEffect *)dword_189504C;
      v20 = (float)a1[3];
    }
    else
    {
      LODWORD(v6) = a5[261];
      v13 = (struct gbRenderEffect *)dword_189504C;
      v14 = (double)a5[260] + v12;
      v20 = (double)v6 + v22;
    }
  }
  else
  {
    v32 = (float)MEMORY[0xBFD6D0];
    v12 = ((double)*a1 + (double)*a1) / v32 - 1.0;
    v31 = (float)MEMORY[0xBFD6D4];
    v22 = 1.0 - ((double)a1[1] + (double)a1[1]) / v31;
    if ( a5 == (unsigned int *)HIDWORD(v6) )
    {
      v14 = ((double)a1[2] + (double)a1[2]) / v32 - 1.0;
      v16 = (double)a1[3];
    }
    else
    {
      v15 = (__int64)((double)__SPAIR64__(HIDWORD(v6), a5[260]) + v12);
      LODWORD(v18) = a5[261];
      HIDWORD(v18) = HIDWORD(v6);
      v14 = ((double)(int)v15 + (double)(int)v15) / v32 - 1.0;
      v16 = (double)(int)(__int64)((double)v18 + v22);
    }
    v13 = (struct gbRenderEffect *)dword_1895048;
    v20 = 1.0 - (v16 + v16) / v31;
  }
  v19 = v12 - -0.5;
  v21 = v14 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), a4);
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)&v19, 1, v13, a3);
}

// 0x00540650
void sub_540650(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, int a7, unsigned int *a8)
{
  unsigned int v8; // ecx
  float v9; // edx
  float v10; // ecx
  int v11; // ecx
  double v12; // st7
  double v13; // st6
  double v14; // st5
  gbDynVertBuf *DynVertBuf; // eax
  struct gbRenderEffect *v16; // edx
  struct gbTextureArray *v17; // [esp-4h] [ebp-38h]
  float v18[3]; // [esp+Ch] [ebp-28h] BYREF
  float v19; // [esp+18h] [ebp-1Ch]
  unsigned int v20; // [esp+1Ch] [ebp-18h]
  unsigned int v21; // [esp+20h] [ebp-14h]
  float v22; // [esp+24h] [ebp-10h]
  float v23; // [esp+28h] [ebp-Ch]
  int v24; // [esp+2Ch] [ebp-8h]
  int v25; // [esp+30h] [ebp-4h]

  v24 = 0;
  v25 = *a5;
  if ( a8 )
  {
    v8 = a8[263];
    v20 = a8[262];
    v9 = *((float *)a8 + 266);
    v21 = v8;
    v10 = *((float *)a8 + 267);
    v22 = v9;
    v23 = v10;
  }
  else
  {
    v11 = *(_DWORD *)a6;
    v21 = 0;
    v20 = 0;
    v22 = (fabs((double)(a3 - a1)) + -0.5) / (double)*(int *)(v11 + 24);
    v23 = (fabs((double)(a4 - a2)) + -0.5) / (double)*(int *)(v11 + 28);
  }
  v12 = (double)a1;
  v19 = (float)a2;
  if ( a8 )
  {
    v13 = (double)a8[260] + v12;
    v14 = (double)a8[261] + v19;
  }
  else
  {
    v13 = (double)a3;
    v14 = (double)a4;
  }
  v18[1] = v14;
  v18[0] = v12 - -0.5;
  v18[2] = v13 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x114u);
  if ( !a7 )
  {
    v17 = a6;
    goto LABEL_11;
  }
  v17 = a6;
  if ( a7 != 1 )
  {
LABEL_11:
    v16 = (struct gbRenderEffect *)dword_1895058;
    goto LABEL_12;
  }
  v16 = (struct gbRenderEffect *)dword_1895054;
LABEL_12:
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)v18, 1, v16, v17);
}

// 0x005407A0
void sub_5407A0(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, unsigned int a7)
{
  int v7; // ecx
  __int64 v8; // rax
  int v9; // ecx
  double v10; // st7
  double v11; // st6
  double v12; // st5
  gbDynVertBuf *DynVertBuf; // eax
  float v14[3]; // [esp+Ch] [ebp-28h] BYREF
  float v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h]
  int v17; // [esp+20h] [ebp-14h]
  float v18; // [esp+24h] [ebp-10h]
  float v19; // [esp+28h] [ebp-Ch]
  int v20; // [esp+2Ch] [ebp-8h]
  int v21; // [esp+30h] [ebp-4h]

  v7 = *a5;
  v8 = a7;
  v20 = 0;
  v21 = v7;
  if ( a7 )
  {
    v16 = *(_DWORD *)(a7 + 1048);
    v17 = *(_DWORD *)(a7 + 1052);
    v18 = *(float *)(a7 + 1064);
    v19 = *(float *)(a7 + 1068);
  }
  else
  {
    v9 = *(_DWORD *)a6;
    v17 = 0;
    v16 = 0;
    v18 = (fabs((double)(a3 - a1)) + -0.5) / (double)*(int *)(v9 + 24);
    v19 = (fabs((double)(a4 - a2)) + -0.5) / (double)*(int *)(v9 + 28);
  }
  v10 = (double)a1;
  v15 = (float)a2;
  if ( a7 )
  {
    LODWORD(v8) = *(_DWORD *)(a7 + 1044);
    v11 = (double)*(unsigned int *)(a7 + 1040) + v10;
    v12 = (double)v8 + v15;
  }
  else
  {
    v11 = (double)a3;
    v12 = (double)a4;
  }
  v14[1] = v12;
  v14[0] = v10 - -0.5;
  v14[2] = v11 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x114u);
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)v14, 1, (struct gbRenderEffect *)dword_189505C, a6);
}

// 0x005408E0
void sub_5408E0(_DWORD *a1, int *a2, int *a3, struct gbTextureArray *a4, unsigned int *a5)
{
  unsigned int v5; // ecx
  float v6; // edx
  float v7; // ecx
  int v8; // edx
  int v9; // ebx
  double v10; // st7
  gbDynVertBuf *DynVertBuf; // eax
  __int64 v12; // [esp+4h] [ebp-30h]
  float v13[2]; // [esp+Ch] [ebp-28h] BYREF
  float v14; // [esp+14h] [ebp-20h]
  float v15; // [esp+18h] [ebp-1Ch]
  unsigned int v16; // [esp+1Ch] [ebp-18h]
  unsigned int v17; // [esp+20h] [ebp-14h]
  float v18; // [esp+24h] [ebp-10h]
  float v19; // [esp+28h] [ebp-Ch]
  int v20; // [esp+2Ch] [ebp-8h]
  int v21; // [esp+30h] [ebp-4h]
  int v22; // [esp+40h] [ebp+Ch]

  v20 = 0;
  v21 = *a3;
  if ( a5 )
  {
    v5 = a5[263];
    v16 = a5[262];
    v6 = *((float *)a5 + 266);
    v17 = v5;
    v7 = *((float *)a5 + 267);
    v18 = v6;
    v19 = v7;
  }
  else
  {
    v8 = *(_DWORD *)a4;
    v9 = a1[2] - *a1;
    v17 = 0;
    v16 = 0;
    v22 = a1[3] - a1[1];
    v18 = (fabs((double)v9) + -0.5) / (double)*(int *)(v8 + 24);
    v19 = (fabs((double)v22) + -0.5) / (double)*(int *)(v8 + 28);
  }
  v13[0] = (float)*a2;
  v15 = (float)a2[1];
  if ( a5 )
  {
    v12 = a5[261];
    v14 = (double)a5[260] + v13[0];
    v10 = (double)v12 + v15;
  }
  else
  {
    v14 = (float)a2[2];
    v10 = (double)a2[3];
  }
  v13[1] = v10;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x114u);
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)v13, 1, (struct gbRenderEffect *)dword_1895054, a4);
}

// 0x00540A20
void sub_540A20(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, unsigned int *a7)
{
  double v7; // st7
  double v8; // st6
  double v9; // st5
  gbDynVertBuf *DynVertBuf; // eax
  float v11[3]; // [esp+8h] [ebp-28h] BYREF
  float v12; // [esp+14h] [ebp-1Ch]
  unsigned int v13; // [esp+18h] [ebp-18h]
  unsigned int v14; // [esp+1Ch] [ebp-14h]
  int v15; // [esp+20h] [ebp-10h]
  int v16; // [esp+24h] [ebp-Ch]
  int v17; // [esp+28h] [ebp-8h]
  int v18; // [esp+2Ch] [ebp-4h]

  v17 = 0;
  v18 = *a5;
  if ( a7 )
  {
    v13 = a7[262];
    v14 = a7[263];
    v15 = a7[266];
    v16 = a7[267];
  }
  else
  {
    v13 = 0;
    v14 = 0;
    v15 = 1065353216;
    v16 = 1065353216;
  }
  v7 = (double)a1;
  v12 = (float)a2;
  if ( a7 )
  {
    v8 = (double)a7[260] + v7;
    v9 = (double)a7[261] + v12;
  }
  else
  {
    v8 = (double)a3;
    v9 = (double)a4;
  }
  v11[1] = v9;
  v11[0] = v7 - -0.5;
  v11[2] = v8 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x114u);
  DynVertBuf->RenderUIQuad((struct gbUIQuad *)v11, 1, (struct gbRenderEffect *)dword_1895058, a6);
}
