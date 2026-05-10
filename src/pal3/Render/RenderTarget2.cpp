#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/RenderTarget2.h"

// Forward declarations for unnamed functions
int sub_4BDD90(...);
int sub_4BDEB0(...);
int sub_5541EE(...);

// 0x004BF780
int RenderTarget2::Init()
{
  RenderTarget2 *v1; // esi
  gbGfxManager *v2; // ebp
  int v3; // eax
  unsigned int CurTick; // eax
  _DWORD *Instance; // eax
  DWORD Time; // eax
  _BYTE *v7; // edi
  unsigned int v8; // esi
  long double v9; // st7
  long double v10; // st6
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  RenderTarget2 *v15; // esi
  int result; // eax
  int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // eax
  double v20; // st7
  unsigned int v21; // eax
  unsigned int v22; // edx
  double v23; // st7
  RenderTarget2 *v24; // edi
  int *v25; // ebp
  RenderTarget2 *v26; // esi
  int v27; // edx
  int v28; // eax
  double v29; // st7
  double v30; // st6
  int v31; // eax
  int v32; // edx
  float *v33; // ecx
  int v34; // eax
  __int16 v35; // di
  __int16 v36; // bp
  int v37; // eax
  __int16 v38; // di
  unsigned int i; // [esp+D4h] [ebp-168h] BYREF
  float v40; // [esp+D8h] [ebp-164h]
  float j; // [esp+DCh] [ebp-160h]
  float v42; // [esp+E0h] [ebp-15Ch]
  _BYTE *v43; // [esp+E4h] [ebp-158h] BYREF
  float v44; // [esp+E8h] [ebp-154h]
  float v45; // [esp+ECh] [ebp-150h]
  RenderTarget2 *v46; // [esp+F0h] [ebp-14Ch]
  __int64 v47; // [esp+F4h] [ebp-148h]
  _DWORD v48[2]; // [esp+FCh] [ebp-140h] BYREF
  __int64 v49; // [esp+104h] [ebp-138h]
  _DWORD v50[76]; // [esp+10Ch] [ebp-130h] BYREF

  v1 = this;
  *((_DWORD *)this + 4) = 0;
  v2 = g_pGfxManager;
  v3 = *(_DWORD *)&g_pGfxManager[1816];
  v46 = this;
  (*(void (__stdcall **)(int, _DWORD *))(*(_DWORD *)v3 + 28))(v3, v50);
  if ( (v50[36] & 0x200000) == 0 )
    *(_DWORD *)&v1[16] = 1;
  if ( v2[1648] )
    CurTick = *(_DWORD *)&v2[1660];
  else
    CurTick = *(_DWORD *)&v2[1716];
  if ( (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int, int))(**(_DWORD **)&v2[1812] + 40))(
         *(_DWORD *)&v2[1812],
         v50[1],
         v50[0],
         *(_DWORD *)(CurTick + 8),
         0,
         3,
         60) < 0 )
    *(_DWORD *)&v1[16] = 1;
  v44 = 1.0;
  Instance = (_DWORD *)CRenderTarget::GetInstance();
  Instance->OnDeviceLost(1);
  if ( !*CRenderTarget::GetInstance() )
    v44 = 0.75;
  if ( *(_DWORD *)&v1[16] )
    goto LABEL_22;
  if ( (*(int (__stdcall **)(_DWORD, int, int, int, _DWORD, int, int, RenderTarget2 *, _DWORD))(**(_DWORD **)&v2[1816]
                                                                                              + 92))(
         *(_DWORD *)&v2[1816],
         256,
         256,
         1,
         0,
         60,
         1,
         v1 + 12,
         0) >= 0 )
  {
    (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD *, _DWORD, _DWORD))(**(_DWORD **)&v1[12] + 76))(
      *(_DWORD *)&v1[12],
      0,
      v48,
      0,
      0);
    v43 = (_BYTE *)v48[1];
    Time = timeGetTime();
    sub_5541EE(Time);
    for ( i = 0; i < 0x100; ++i )
    {
      v49 = i;
      v7 = v43;
      v8 = 0;
      v45 = (double)i * 0.00390625 - 0.5;
      do
      {
        v47 = v8;
        j = (v45 + (double)v8 * 0.00390625 - 0.5) * 12.566371;
        v42 = (double)(rand() % 16) + cos(j) * 48.0;
        LODWORD(v40) = rand() % 16;
        v9 = (double)SLODWORD(v40) + sin(j) * 48.0;
        v10 = v42 - v9;
        *v7 = (__int64)((v9 + v42) * 0.5);
        v7[1] = (__int64)v10;
        ++v8;
        v7 += 2;
      }
      while ( v8 < 0x100 );
      v43 += v48[0];
    }
    (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)&v46[12] + 80))(*(_DWORD *)&v46[12], 0);
    v11 = *(_DWORD *)&v2[1816];
    v40 = 0.0099999998;
    (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)v11 + 268))(v11, 0, 7, 1008981770);
    v12 = *(_DWORD *)&v2[1816];
    v40 = 0.0;
    (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)v12 + 268))(v12, 0, 8, 0);
    v13 = *(_DWORD *)&v2[1816];
    v40 = 0.0;
    (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)v13 + 268))(v13, 0, 9, 0);
    v14 = *(_DWORD *)&v2[1816];
    v40 = 0.0099999998;
    (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)v14 + 268))(v14, 0, 10, 1008981770);
    v1 = v46;
  }
  else
  {
    *(_DWORD *)&v1[16] = 1;
  }
  if ( *(_DWORD *)&v1[16] )
  {
LABEL_22:
    v24 = (RenderTarget2 *)v1 + 8;
    result = (*(int (__stdcall **)(_DWORD, int, int, int, int, RenderTarget2 *, _DWORD))(**(_DWORD **)&v2[1816] + 104))(
               *(_DWORD *)&v2[1816],
               2800,
               8,
               514,
               1,
               v1 + 8,
               0);
    if ( result >= 0 )
    {
      v25 = (int *)*(int **)&v2[1816];
      v26 = (RenderTarget2 *)v1 + 4;
      v27 = *v25;
      v45 = *(float *)&v26;
      result = (*(int (__stdcall **)(int *, int, int, int, _DWORD, RenderTarget2 *, _DWORD))(v27 + 108))(
                 v25,
                 1200,
                 512,
                 101,
                 0,
                 v26,
                 0);
      if ( result >= 0 )
      {
        v28 = *(_DWORD *)v24;
        v43 = 0;
        result = (*(int (__stdcall **)(int, _DWORD, _DWORD, _BYTE **, _DWORD))(*(_DWORD *)v28 + 44))(v28, 0, 0, &v43, 0);
        if ( result >= 0 )
        {
          v29 = -1.0;
          v30 = 0.0;
          v42 = -1.0;
          j = v44;
          v31 = 0;
          v40 = v44 * 0.1;
          do
          {
            v32 = 10;
            do
            {
              v33 = (float *)&v43[v31];
              v31 += 28;
              v33[1] = v42;
              v33[2] = 0.0;
              *v33 = v29;
              v29 = v29 + 0.22222222;
              v30 = v30 + 0.1;
              --v32;
              *(float *)&v43[v31 - 16] = v30;
              *(float *)&v43[v31 - 12] = j;
            }
            while ( v32 );
            v42 = v42 + 0.22222222;
            v29 = -1.0;
            v30 = 0.0;
            j = j - v40;
          }
          while ( v31 < 2800 );
          (*(void (__stdcall **)(_DWORD))(**(_DWORD **)v24 + 48))(*(_DWORD *)v24);
          v34 = *(_DWORD *)v26;
          i = 0;
          result = (*(int (__stdcall **)(int, _DWORD, _DWORD, unsigned int *, int))(*(_DWORD *)v34 + 44))(
                     v34,
                     0,
                     0,
                     &i,
                     0x2000);
          if ( result >= 0 )
          {
            v35 = 0;
            for ( j = 0.0; ; v35 = LOWORD(j) )
            {
              v36 = 5 * v35;
              v37 = 0;
              v38 = 2 * (5 * v35 + 5);
              do
              {
                *(_WORD *)i = v38 + v37;
                i += 2;
                *(_WORD *)i = v37;
                i += 2;
                *(_WORD *)i = v37 + 1;
                i += 2;
                *(_WORD *)i = v37 + 1;
                i += 2;
                *(_WORD *)i = v37 + 2 * v36 + 11;
                i += 2;
                *(_WORD *)i = v38 + v37++;
                i += 2;
              }
              while ( v37 < 9 );
              ++LODWORD(j);
              if ( SLODWORD(j) >= 9 )
                break;
            }
            return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)LODWORD(v45) + 48))(*(_DWORD *)LODWORD(v45));
          }
        }
      }
    }
  }
  else
  {
    v15 = (RenderTarget2 *)v1 + 8;
    result = (*(int (__stdcall **)(_DWORD, int, int, int, int, RenderTarget2 *, _DWORD))(**(_DWORD **)&v2[1816] + 104))(
               *(_DWORD *)&v2[1816],
               112,
               8,
               514,
               1,
               v15,
               0);
    if ( result >= 0 )
    {
      v17 = *(_DWORD *)v15;
      i = 0;
      result = (*(int (__stdcall **)(int, _DWORD, _DWORD, unsigned int *, _DWORD))(*(_DWORD *)v17 + 44))(
                 v17,
                 0,
                 0,
                 &i,
                 0);
      if ( result >= 0 )
      {
        v18 = i;
        *(_DWORD *)i = -1082130432;
        *(_DWORD *)(v18 + 4) = -1082130432;
        *(_DWORD *)(v18 + 8) = 0;
        v19 = i + 28;
        v20 = v44;
        *(_DWORD *)(i + 28) = -1082130432;
        *(_DWORD *)(v19 + 4) = 1065353216;
        *(_DWORD *)(v19 + 8) = 0;
        v21 = i + 56;
        *(_DWORD *)(i + 56) = 1065353216;
        *(_DWORD *)(v21 + 4) = -1082130432;
        *(_DWORD *)(v21 + 8) = 0;
        v22 = i;
        *(_DWORD *)(i + 84) = 1065353216;
        *(_DWORD *)(v22 + 88) = 1065353216;
        *(_DWORD *)(v22 + 92) = 0;
        *(_DWORD *)(i + 20) = 0;
        *(_DWORD *)(i + 12) = 0;
        *(_DWORD *)(i + 16) = 1065353216;
        *(float *)(i + 24) = v20;
        v23 = v44;
        *(_DWORD *)(i + 48) = 0;
        *(_DWORD *)(i + 40) = 0;
        *(_DWORD *)(i + 52) = 0;
        *(_DWORD *)(i + 44) = 0;
        *(_DWORD *)(i + 76) = 1065353216;
        *(_DWORD *)(i + 68) = 1065353216;
        *(_DWORD *)(i + 72) = 1065353216;
        *(float *)(i + 80) = v23;
        *(_DWORD *)(i + 104) = 1065353216;
        *(_DWORD *)(i + 96) = 1065353216;
        *(_DWORD *)(i + 108) = 0;
        *(_DWORD *)(i + 100) = 0;
        return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)v15 + 48))(*(_DWORD *)v15);
      }
    }
  }
  return result;
}

// 0x004BFD70
void * RenderTarget2::Begin()
{
  _BYTE *v0; // ecx
  _BYTE *v1; // esi
  _DWORD *Instance; // eax
  int *v3; // eax
  void *result; // eax

  v1 = v0;
  if ( *v0 )
  {
    Instance = (_DWORD *)CRenderTarget::GetInstance();
    Instance->OnDeviceLost(2);
    v3 = (int *)CRenderTarget::GetInstance();
    LOBYTE(result) = v3->OnResetDevice(0);
    if ( (_BYTE)result )
      return (*(void *(__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)&g_pGfxManager[1816]
                                                                                   + 172))(
               *(_DWORD *)&g_pGfxManager[1816],
               0,
               0,
               3,
               -16777216,
               1065353216,
               0);
    else
      *v1 = 0;
  }
  return result;
}

// 0x004BFDD0
void RenderTarget2::Resolve()
{
  int *Instance; // eax
  gbGfxManager *v3; // esi
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // ebp

  if ( *this )
  {
    Instance = (int *)CRenderTarget::GetInstance();
    sub_4BDD90(Instance);
    v3 = g_pGfxManager;
    PushMatrixStacks();
    (*(void (**)(gbGfxManager *))(*(_DWORD *)v3 + 60))(v3);
    v4 = (_DWORD *)CRenderTarget::GetInstance();
    v5 = (_DWORD *)sub_4BDEB0(v4);
    v6 = v5;
    if ( v5 && v5[21] && *((_DWORD *)this + 2) )
    {
      (*(void (__stdcall **)(_DWORD, int, int))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 22, 1);
      (*(void (__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 137, 0);
      (*(void (__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 7, 0);
      (*(void (__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 14, 0);
      (*(void (__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 15, 0);
      (*(void (__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 27, 0);
      (*(void (__stdcall **)(_DWORD, int, int))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 26, 1);
      (*(void (__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 228))(*(_DWORD *)&v3[1816], 29, 0);
      if ( *((_DWORD *)this + 4) )
      {
        (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)&v3[1816] + 260))(*(_DWORD *)&v3[1816], 0, v6[21]);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 268))(
          *(_DWORD *)&v3[1816],
          0,
          11,
          0);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 1, 2);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 2, 2);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 3, 1);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 4, 1);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 276))(*(_DWORD *)&v3[1816], 0, 1, 3);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 276))(*(_DWORD *)&v3[1816], 0, 2, 3);
        (*(void (__stdcall **)(_DWORD, int))(**(_DWORD **)&v3[1816] + 356))(*(_DWORD *)&v3[1816], 514);
        (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int))(**(_DWORD **)&v3[1816] + 400))(
          *(_DWORD *)&v3[1816],
          0,
          *((_DWORD *)this + 2),
          0,
          28);
        (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)&v3[1816] + 416))(
          *(_DWORD *)&v3[1816],
          *((_DWORD *)this + 1));
        (*(void (__stdcall **)(_DWORD, int, _DWORD, _DWORD, int, _DWORD, int))(**(_DWORD **)&v3[1816] + 328))(
          *(_DWORD *)&v3[1816],
          4,
          0,
          0,
          100,
          0,
          200);
      }
      else
      {
        (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)&v3[1816] + 260))(
          *(_DWORD *)&v3[1816],
          0,
          *((_DWORD *)this + 3));
        (*(void (__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 260))(*(_DWORD *)&v3[1816], 1, v6[21]);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, _DWORD))(**(_DWORD **)&v3[1816] + 268))(
          *(_DWORD *)&v3[1816],
          0,
          11,
          0);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 1, 22);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 2, 2);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 3, 1);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 0, 4, 1);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 1, 11, 1);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 1, 1, 2);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 1, 2, 2);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 1, 3, 1);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 1, 4, 1);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 276))(*(_DWORD *)&v3[1816], 1, 1, 3);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 276))(*(_DWORD *)&v3[1816], 1, 2, 3);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 2, 1, 1);
        (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v3[1816] + 268))(*(_DWORD *)&v3[1816], 2, 4, 1);
        (*(void (__stdcall **)(_DWORD, int))(**(_DWORD **)&v3[1816] + 356))(*(_DWORD *)&v3[1816], 514);
        (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int))(**(_DWORD **)&v3[1816] + 400))(
          *(_DWORD *)&v3[1816],
          0,
          *((_DWORD *)this + 2),
          0,
          28);
        (*(void (__stdcall **)(_DWORD, int, _DWORD, int))(**(_DWORD **)&v3[1816] + 324))(*(_DWORD *)&v3[1816], 5, 0, 2);
      }
      *(_DWORD *)&g_pGfxManager[2280] = 0;
      *(_DWORD *)&g_pGfxManager[2284] = 0;
      (gbGfxManager_D3D *->SetTexture()g_pGfxManager, 0);
      gbRenderEffect::Apply(*(gbRenderEffect **)(*(_DWORD *)&g_pGfxManager[200] + 24));
    }
    PopMatrixStacks();
  }
}
