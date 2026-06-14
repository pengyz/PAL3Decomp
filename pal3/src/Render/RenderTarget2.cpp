#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/RenderTarget2.h"

// Forward declarations for unnamed functions
int sub_004C2040(...);
int sub_004C27C0(...);
int sub_004C3400(...);
int sub_4C3C70(...);
int sub_4C5800(...);
void __cdecl todo_401800(void);

// Unnamed globals (extern)
extern int dword_5D4E5C;
extern int dword_5D4E68;
extern int dword_5D4E74;
extern int dword_5D4E80;
extern int dword_5D4E8C;
extern int dword_5D4E98;
extern int dword_5D4EA4;
extern int dword_5D4EB0;
extern int dword_5D4EC8;
extern int dword_5D4ED4;
extern int dword_5D4EE0;
extern int dword_5D4EE8;
extern int dword_5D4EF0;
extern int dword_5D4EF8;
extern int dword_5D4F00;
extern int dword_5D4F08;
extern int dword_5D4F10;
extern int dword_5D4F18;
extern int dword_5D4F20;
extern int dword_5D4F28;
extern int dword_5D4F30;
extern int dword_5D4F38;
extern int dword_5D4F40;
extern int dword_5D4F48;
extern int dword_5D4F50;
extern int dword_5D4F58;
extern int dword_5D4F78;
void __cdecl nullsub_12(void);
void __cdecl nullsub_13(void);
void __cdecl nullsub_14(void);
void __cdecl nullsub_15(void);

// 0x004BF780
int RenderTarget2::Init()
{
  RenderTarget2 *v1; // esi
  gbGfxManager *v2; // ebp
  float xy; // eax
  gbVertPoolMgr *pVertPoolMgr; // eax
  PAL3 *v5; // ecx
  PAL3 *Instance_db10; // eax
  PAL3 *v7; // ecx
  DWORD Time; // eax
  _BYTE *v9; // edi
  unsigned int v10; // esi
  long double v11; // st7
  long double v12; // st6
  float v13; // eax
  float v14; // eax
  float v15; // eax
  float v16; // eax
  _DWORD *v17; // esi
  int result; // eax
  int v19; // eax
  unsigned int v20; // eax
  unsigned int v21; // eax
  double v22; // st7
  unsigned int v23; // eax
  unsigned int v24; // edx
  double v25; // st7
  _DWORD *p_m_bActive; // edi
  float v27; // ebp
  char **p_m_pSurface; // esi
  int v29; // edx
  int v30; // eax
  double v31; // st7
  double v32; // st6
  int v33; // eax
  int v34; // edx
  float *v35; // ecx
  char *v36; // eax
  __int16 v37; // di
  __int16 v38; // bp
  int v39; // eax
  __int16 v40; // di
  unsigned int i; // [esp+D4h] [ebp-0x168] BYREF
  float v42; // [esp+D8h] [ebp-0x164]
  float j; // [esp+DCh] [ebp-0x160]
  float v44; // [esp+E0h] [ebp-0x15C]
  _BYTE *v45; // [esp+E4h] [ebp-0x158] BYREF
  float v46; // [esp+E8h] [ebp-0x154]
  float v47; // [esp+ECh] [ebp-0x150]
  RenderTarget2 *v48; // [esp+F0h] [ebp-0x14C]
  __int64 v49; // [esp+F4h] [ebp-0x148]
  _DWORD v50[2]; // [esp+FCh] [ebp-0x140] BYREF
  __int64 v51; // [esp+0x104] [ebp-0x138]
  _DWORD v52[76]; // [esp+0x10C] [ebp-0x130] BYREF
this->m_nFallbackMode = 0;
  v2 = gfxMgr;
  xy = gfxMgr[1].InvViewMatrix.xy;
  v48 = this;
  (*(void ( **)(float, _DWORD *))(*(_DWORD *)LODWORD(xy) + 28))(COERCE_FLOAT(LODWORD(xy)), v52);
  if ( (v52[36] & 0x200000) == 0 )
    this->m_nFallbackMode = 1;
  if ( v2[1].DrvInfo.winname[76] )
    pVertPoolMgr = *(gbVertPoolMgr **)&v2[1].DrvInfo.winname[88];
  else
    pVertPoolMgr = v2[1].pVertPoolMgr;
  if ( (*(int ( **)(_DWORD, _DWORD, _DWORD, int, _DWORD, int, int))(**(_DWORD **)&v2[1].InvViewMatrix
                                                                                      + 40))(
         *(_DWORD *)&v2[1].InvViewMatrix,
         v52[1],
         v52[0],
         pVertPoolMgr->StaticPool[0].m_numNode,
         0,
         3,
         60) < 0 )
    this->m_nFallbackMode = 1;
  v46 = 1.0;
  Instance_db10 = ((PAL3 *)v5)->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(1);
  if ( !LODWORD(((PAL3 *)v7)->GetInstance_db10()->m_snaph) )
    v46 = 0.75;
  if ( this->m_nFallbackMode )
    goto LABEL_22;
  if ( (*(int ( **)(_DWORD, int, int, int, _DWORD, int, int, int *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy)
                                                                                               + 92))(
         LODWORD(v2[1].InvViewMatrix.xy),
         256,
         256,
         1,
         0,
         60,
         1,
         &this->m_SubObj,
         0) >= 0 )
  {
    (*(void ( **)(int, _DWORD, _DWORD *, _DWORD, _DWORD))(*(_DWORD *)this->m_SubObj + 76))(
      this->m_SubObj,
      0,
      v50,
      0,
      0);
    v45 = (_BYTE *)v50[1];
    Time = timeGetTime();
    CRT_set_new_handler(Time);
    for ( i = 0; i < 0x100; ++i )
    {
      v51 = i;
      v9 = v45;
      v10 = 0;
      v47 = (double)i * 0.00390625 - 0.5;
      do
      {
        v49 = v10;
        j = (v47 + (double)v10 * 0.00390625 - 0.5) * 12.566371;
        v44 = (double)(rand() % 16) + cos(j) * 48.0;
        LODWORD(v42) = rand() % 16;
        v11 = (double)SLODWORD(v42) + sin(j) * 48.0;
        v12 = v44 - v11;
        *v9 = (__int64)((v11 + v44) * 0.5);
        v9[1] = (__int64)v12;
        ++v10;
        v9 += 2;
      }
      while ( v10 < 0x100 );
      v45 += v50[0];
    }
    (*(void ( **)(int, _DWORD))(*(_DWORD *)v48->m_SubObj + 80))(v48->m_SubObj, 0);
    v13 = v2[1].InvViewMatrix.xy;
    v42 = 0.0099999998;
    (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(v13) + 268))(
      COERCE_FLOAT(LODWORD(v13)),
      0,
      7,
      1008981770);
    v14 = v2[1].InvViewMatrix.xy;
    v42 = 0.0;
    (*(void ( **)(float, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v14) + 268))(
      COERCE_FLOAT(LODWORD(v14)),
      0,
      8,
      0);
    v15 = v2[1].InvViewMatrix.xy;
    v42 = 0.0;
    (*(void ( **)(float, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v15) + 268))(
      COERCE_FLOAT(LODWORD(v15)),
      0,
      9,
      0);
    v16 = v2[1].InvViewMatrix.xy;
    v42 = 0.0099999998;
    (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(v16) + 268))(
      COERCE_FLOAT(LODWORD(v16)),
      0,
      10,
      1008981770);
    v1 = v48;
  }
  else
  {
    this->m_nFallbackMode = 1;
  }
  if ( this->m_nFallbackMode )
  {
LABEL_22:
    p_m_bActive = &this->m_bActive;
    result = (*(int ( **)(_DWORD, int, int, int, int, _BYTE *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy)
                                                                               + 104))(
               LODWORD(v2[1].InvViewMatrix.xy),
               2800,
               8,
               514,
               1,
               &this->m_bActive,
               0);
    if ( result >= 0 )
    {
      v27 = v2[1].InvViewMatrix.xy;
      p_m_pSurface = &this->m_pSurface;
      v29 = *(_DWORD *)LODWORD(v27);
      v47 = *(float *)&p_m_pSurface;
      result = (*(int ( **)(float, int, int, int, _DWORD, char **, _DWORD))(v29 + 108))(
                 COERCE_FLOAT(LODWORD(v27)),
                 1200,
                 512,
                 101,
                 0,
                 p_m_pSurface,
                 0);
      if ( result >= 0 )
      {
        v30 = *p_m_bActive;
        v45 = 0;
        result = (*(int ( **)(int, _DWORD, _DWORD, _BYTE **, _DWORD))(*(_DWORD *)v30 + 44))(v30, 0, 0, &v45, 0);
        if ( result >= 0 )
        {
          v31 = -1.0;
          v32 = 0.0;
          v44 = -1.0;
          j = v46;
          v33 = 0;
          v42 = v46 * 0.1;
          do
          {
            v34 = 10;
            do
            {
              v35 = (float *)&v45[v33];
              v33 += 28;
              v35[1] = v44;
              v35[2] = 0.0;
              *v35 = v31;
              v31 = v31 + 0.22222222;
              v32 = v32 + 0.1;
              --v34;
              *(float *)&v45[v33 - 16] = v32;
              *(float *)&v45[v33 - 12] = j;
            }
            while ( v34 );
            v44 = v44 + 0.22222222;
            v31 = -1.0;
            v32 = 0.0;
            j = j - v42;
          }
          while ( v33 < 2800 );
          (*(void ( **)(_DWORD))(*(_DWORD *)*p_m_bActive + 48))(*p_m_bActive);
          v36 = *p_m_pSurface;
          i = 0;
          result = (*(int ( **)(char *, _DWORD, _DWORD, unsigned int *, int))(*(_DWORD *)v36 + 44))(
                     v36,
                     0,
                     0,
                     &i,
                     0x2000);
          if ( result >= 0 )
          {
            v37 = 0;
            for ( j = 0.0; ; v37 = LOWORD(j) )
            {
              v38 = 5 * v37;
              v39 = 0;
              v40 = 2 * (5 * v37 + 5);
              do
              {
                *(_WORD *)i = v40 + v39;
                i += 2;
                *(_WORD *)i = v39;
                i += 2;
                *(_WORD *)i = v39 + 1;
                i += 2;
                *(_WORD *)i = v39 + 1;
                i += 2;
                *(_WORD *)i = v39 + 2 * v38 + 11;
                i += 2;
                *(_WORD *)i = v40 + v39++;
                i += 2;
              }
              while ( v39 < 9 );
              ++LODWORD(j);
              if ( SLODWORD(j) >= 9 )
                break;
            }
            return (*(int ( **)(_DWORD))(**(_DWORD **)LODWORD(v47) + 48))(*(_DWORD *)LODWORD(v47));
          }
        }
      }
    }
  }
  else
  {
    v17 = &this->m_bActive;
    result = (*(int ( **)(_DWORD, int, int, int, int, _DWORD *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy)
                                                                                + 104))(
               LODWORD(v2[1].InvViewMatrix.xy),
               112,
               8,
               514,
               1,
               v17,
               0);
    if ( result >= 0 )
    {
      v19 = *v17;
      i = 0;
      result = (*(int ( **)(int, _DWORD, _DWORD, unsigned int *, _DWORD))(*(_DWORD *)v19 + 44))(
                 v19,
                 0,
                 0,
                 &i,
                 0);
      if ( result >= 0 )
      {
        v20 = i;
        *(_DWORD *)i = -1082130432;
        *(_DWORD *)(v20 + 4) = -1082130432;
        *(_DWORD *)(v20 + 8) = 0;
        v21 = i + 28;
        v22 = v46;
        *(_DWORD *)(i + 28) = -1082130432;
        *(_DWORD *)(v21 + 4) = 1065353216;
        *(_DWORD *)(v21 + 8) = 0;
        v23 = i + 56;
        *(_DWORD *)(i + 56) = 1065353216;
        *(_DWORD *)(v23 + 4) = -1082130432;
        *(_DWORD *)(v23 + 8) = 0;
        v24 = i;
        *(_DWORD *)(i + 84) = 1065353216;
        *(_DWORD *)(v24 + 88) = 1065353216;
        *(_DWORD *)(v24 + 92) = 0;
        *(_DWORD *)(i + 20) = 0;
        *(_DWORD *)(i + 12) = 0;
        *(_DWORD *)(i + 16) = 1065353216;
        *(float *)(i + 24) = v22;
        v25 = v46;
        *(_DWORD *)(i + 48) = 0;
        *(_DWORD *)(i + 40) = 0;
        *(_DWORD *)(i + 52) = 0;
        *(_DWORD *)(i + 44) = 0;
        *(_DWORD *)(i + 76) = 1065353216;
        *(_DWORD *)(i + 68) = 1065353216;
        *(_DWORD *)(i + 72) = 1065353216;
        *(float *)(i + 80) = v25;
        *(_DWORD *)(i + 104) = 1065353216;
        *(_DWORD *)(i + 96) = 1065353216;
        *(_DWORD *)(i + 108) = 0;
        *(_DWORD *)(i + 100) = 0;
        return (*(int ( **)(_DWORD))(*(_DWORD *)*v17 + 48))(*v17);
      }
    }
  }
  return result;
}

// 0x004BFD70
void * RenderTarget2::Begin()
{
  PAL3 *Instance_db10; // eax
  PAL3 *v3; // ecx
  PAL3 *v4; // eax
  void *result; // eax

  if ( LOBYTE(this->m_pVtable) )
  {
    Instance_db10 = ((PAL3 *)this)->GetInstance_db10();
    ((RenderTarget *)Instance_db10)->OnDeviceLost(2);
    v4 = ((PAL3 *)v3)->GetInstance_db10();
    LOBYTE(result) = ((RenderTarget *)v4)->OnResetDevice(0);
    if ( (_BYTE)result )
      return (*(void *( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                                   + 172))(
               LODWORD(gfxMgr[1].InvViewMatrix.xy),
               0,
               0,
               3,
               -16777216,
               1065353216,
               0);
    else
      LOBYTE(this->m_pVtable) = 0;
  }
  return result;
}

// 0x004BFDD0
void RenderTarget2::Resolve()
{
  PAL3 *Instance_db10; // eax
  gbGfxManager *v3; // esi
  int v4; // eax
  PAL3 *v5; // ecx
  PAL3 *v6; // eax
  gbTexture *ActiveTexture; // eax
  gbTexture *v8; // ebp
  char v9[4]; // [esp+0x120] [ebp-0x10] BYREF
  int v10; // [esp+0x12C] [ebp-0x4]

  if ( LOBYTE(this->m_pVtable) )
  {
    Instance_db10 = ((PAL3 *)this)->GetInstance_db10();
    ((RenderTarget *)Instance_db10)->RenderToScreen();
    v3 = gfxMgr;
    PushMatrixStacks(v9);
    v4 = *(_DWORD *)v3;
    v10 = 0;
    (*(void ( **)(gbGfxManager *))(v4 + 60))(v3);
    v6 = ((PAL3 *)v5)->GetInstance_db10();
    ActiveTexture = ((RenderTarget *)v6)->GetActiveTexture();
    v8 = ActiveTexture;
    if ( ActiveTexture && ActiveTexture[1] && *(_DWORD *)&this->m_bActive )
    {
      (*(void ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        22,
        1);
      (*(void ( **)(_DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        137,
        0);
      (*(void ( **)(_DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        7,
        0);
      (*(void ( **)(_DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        14,
        0);
      (*(void ( **)(_DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        15,
        0);
      (*(void ( **)(_DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        27,
        0);
      (*(void ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        26,
        1);
      (*(void ( **)(_DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 228))(
        LODWORD(v3[1].InvViewMatrix.xy),
        29,
        0);
      if ( this->m_nFallbackMode )
      {
        (*(void ( **)(_DWORD, _DWORD, void *))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 260))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          v8[1]);
        (*(void ( **)(_DWORD, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          11,
          0);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          1,
          2);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          2,
          2);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          3,
          1);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          4,
          1);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 276))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          1,
          3);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 276))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          2,
          3);
        (*(void ( **)(_DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 356))(
          LODWORD(v3[1].InvViewMatrix.xy),
          514);
        (*(void ( **)(_DWORD, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 400))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          *(_DWORD *)&this->m_bActive,
          0,
          28);
        (*(void ( **)(_DWORD, char *))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 416))(
          LODWORD(v3[1].InvViewMatrix.xy),
          this->m_pSurface);
        (*(void ( **)(_DWORD, int, _DWORD, _DWORD, int, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy)
                                                                             + 328))(
          LODWORD(v3[1].InvViewMatrix.xy),
          4,
          0,
          0,
          100,
          0,
          200);
      }
      else
      {
        (*(void ( **)(_DWORD, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 260))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          this->m_SubObj);
        (*(void ( **)(_DWORD, int, void *))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 260))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          v8[1]);
        (*(void ( **)(_DWORD, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          11,
          0);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          1,
          22);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          2,
          2);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          3,
          1);
        (*(void ( **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          4,
          1);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          11,
          1);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          1,
          2);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          2,
          2);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          3,
          1);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          4,
          1);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 276))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          1,
          3);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 276))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          2,
          3);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          2,
          1,
          1);
        (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 268))(
          LODWORD(v3[1].InvViewMatrix.xy),
          2,
          4,
          1);
        (*(void ( **)(_DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 356))(
          LODWORD(v3[1].InvViewMatrix.xy),
          514);
        (*(void ( **)(_DWORD, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 400))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          *(_DWORD *)&this->m_bActive,
          0,
          28);
        (*(void ( **)(_DWORD, int, _DWORD, int))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 324))(
          LODWORD(v3[1].InvViewMatrix.xy),
          5,
          0,
          2);
      }
      gfxMgr[1].AllLight[1].attenuation1 = 0.0;
      gfxMgr[1].AllLight[1].attenuation2 = 0.0;
      ((gbGfxManager_D3D *)gfxMgr)->SetTexture(0);
      ((gbRenderEffect *)gfxMgr->pEffectMgr->m_pDefEffect)->Apply();
    }
    v10 = -1;
    PopMatrixStacks(v9);
  }
}

// 0x004C0200
void RenderTarget2::Update(float fVal)
{
  int v3; // eax
  double v4; // st7
  PAL3 *v5; // ecx
  int m_nFallbackMode; // eax
  double v7; // st7
  double v8; // st6
  float v9; // eax
  int v10; // eax
  int v11; // ecx
  long double v12; // st5
  long double v13; // st5
  double v14; // st4
  float v15; // [esp+0x14] [ebp-0x10]
  int v16; // [esp+0x14] [ebp-0x10]
  float v17; // [esp+0x18] [ebp-0xC]
  int v18; // [esp+0x1C] [ebp-0x8]
  float v19; // [esp+0x1C] [ebp-0x8]
  float v20; // [esp+0x20] [ebp-0x4]

  if ( LOBYTE(this->m_pVtable) )
  {
    v3 = *(_DWORD *)&this->m_bActive;
    if ( v3 )
    {
      v4 = fVal * 0.40000001;
      fVal = 0.0;
      this->m_fBlendParam = v4 + this->m_fBlendParam;
      if ( (*(int ( **)(int, _DWORD, _DWORD, float *, _DWORD))(*(_DWORD *)v3 + 44))(v3, 0, 0, &fVal, 0) >= 0 )
      {
        m_nFallbackMode = this->m_nFallbackMode;
        if ( m_nFallbackMode )
        {
          if ( m_nFallbackMode == 1 )
          {
            v15 = 1.0;
            if ( !LODWORD(((PAL3 *)v5)->GetInstance_db10()->m_snaph) )
              v15 = 0.75;
            v7 = 0.0;
            v8 = v15 * 0.1;
            v9 = v15;
            v16 = 0;
            v17 = v9;
            v10 = 0;
            do
            {
              v11 = 0;
              v18 = 0;
              do
              {
                ++v11;
                v10 += 28;
                v7 = v7 + 0.1;
                v12 = ((double)v18 * 0.1 - 0.5 + (double)v16 * 0.1 - 0.5) * 12.566371 + this->m_fBlendParam * 4.0;
                v19 = cos(v12) * 0.0099999998;
                v13 = sin(v12) * 0.0099999998;
                *(float *)(v10 + LODWORD(fVal) - 16) = (v13 + v19) * 0.5 + v7;
                v14 = v19 + v17;
                v18 = v11;
                *(float *)(v10 + LODWORD(fVal) - 12) = v14 - v13;
              }
              while ( v11 < 10 );
              v7 = 0.0;
              ++v16;
              v20 = v8;
              v17 = v17 - v20;
            }
            while ( v10 < 2800 );
          }
          (*(void ( **)(_DWORD))(**(_DWORD **)&this->m_bActive + 48))(*(_DWORD *)&this->m_bActive);
        }
        else
        {
          if ( this->m_fBlendParam > 2.0 )
            this->m_fBlendParam = this->m_fBlendParam - 2.0;
          *(_DWORD *)(LODWORD(fVal) + 12) = 0;
          *(float *)(LODWORD(fVal) + 16) = this->m_fBlendParam * 0.5 + 1.0;
          *(_DWORD *)(LODWORD(fVal) + 40) = 0;
          *(float *)(LODWORD(fVal) + 44) = this->m_fBlendParam * 0.5;
          *(_DWORD *)(LODWORD(fVal) + 68) = 1065353216;
          *(float *)(LODWORD(fVal) + 72) = this->m_fBlendParam * 0.5;
          *(_DWORD *)(LODWORD(fVal) + 96) = 1065353216;
          *(float *)(LODWORD(fVal) + 100) = this->m_fBlendParam * 0.5 + 1.0;
          (*(void ( **)(_DWORD))(**(_DWORD **)&this->m_bActive + 48))(*(_DWORD *)&this->m_bActive);
        }
      }
    }
  }
}

// 0x004C04C0
CEffBase ** RenderTarget2::ClearTarget()
{
  this->m_pSurface = 0;
  this->m_bActive = 0;
  this->m_nFallbackMode = 0;
  this->m_fBlendParam = 0.0;
  this->m_pTargetArray = 0;
  this->m_nCurTarget = -1;
  this->m_nCurPass = -1;
  this->m_fTime = 0.0;
  this->m_nMaxTargets = 0;
  this->m_nMaxPasses = 0;
  return (CEffBase **)this;
}

// 0x004C0560
int RenderTarget2::ExecutePasses()
{
  int *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->m_SubObj : 0;
  if ( v1[7] || (result = *(this != 0 ? &this->m_nMaxPasses : (int *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? &this->m_nMaxTargets : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + v1[3]));
        ++v3;
        *(_DWORD *)(v4 + v1[3]) = 0;
        v4 += 152;
      }
      while ( v3 < v1[7] );
    }
    operator delete((void *)v1[3]);
    v1[3] = 0;
    v1[7] = 0;
    v1[8] = 0;
    return 0;
  }
  return result;
}

// 0x004C0600
char RenderTarget2::StubReturn0(int nVal)
{
  return 0;
}

// 0x004C0C10
int RenderTarget2::SceneRoleCallback(int nParam)
{
  char *v2; // ebx
  int v3; // edi
  int v4; // ecx
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int *v8; // eax
  double v9; // st7
  double v10; // st7
  int v11; // edx
  double v12; // st7
  double v13; // st6
  int v14; // eax
  double v15; // st7
  double v16; // st7
  int v17; // eax
  int v18; // edx
  float v20; // [esp+0x10] [ebp-0x34]
  int v21; // [esp+0x10] [ebp-0x34]
  int v22; // [esp+0x10] [ebp-0x34]
  float v23; // [esp+0x14] [ebp-0x30]
  int v24; // [esp+0x14] [ebp-0x30]
  int v25; // [esp+0x14] [ebp-0x30]
  float v26; // [esp+0x18] [ebp-0x2C]
  float v27; // [esp+0x1C] [ebp-0x28]
  float v28; // [esp+0x1C] [ebp-0x28]
  float v29; // [esp+0x20] [ebp-0x24]
  float v30; // [esp+0x24] [ebp-0x20]
  float v31; // [esp+0x28] [ebp-0x1C]
  float v32; // [esp+0x2C] [ebp-0x18]
  int pParam; // [esp+0x30] [ebp-0x14]
  unsigned int v34; // [esp+0x34] [ebp-0x10]
  float fVal; // [esp+0x3C] [ebp-0x8]
  float fVala; // [esp+0x3C] [ebp-0x8]
  int v38; // [esp+0x40] [ebp-0x4]

  v2 = &this->m_pTargetArray[152 * this->m_nCurTarget];
  v38 = *(_DWORD *)v2 + 72 * this->m_nCurPass;
  v3 = *(_DWORD *)(*((_DWORD *)this->m_pSurface + 1) + 20);
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  v34 = (int)*((float *)v2 + 27);
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  pParam = (int)*((float *)v2 + 6);
  v4 = v38;
  v5 = *(float *)&this->m_nFallbackMode;
  this->m_szPrefix = v34;
  v6 = v5 - *(float *)(v38 + 16);
  fVal = this->m_fBlendParam;
  if ( v6 > *(float *)(v38 + 24) )
    fVal = fVal - (v6 - *(float *)(v38 + 24));
  if ( (g_PAL3.m_nRenderTarget2State_DE8E24 & 1) == 0 )
  {
    g_PAL3.m_nRenderTarget2_DE8E18 = 0;
    LOBYTE(g_PAL3.m_nRenderTarget2State_DE8E24) |= 1u;
    g_PAL3.m_nRenderTarget2_DE8E1C = 0;
    g_PAL3.m_nRenderTarget2_DE8E20 = 0;
    atexit(nullsub_15);
    v4 = v38;
  }
  if ( (g_PAL3.m_nRenderTarget2State_DE8E24 & 2) == 0 )
  {
    LOBYTE(g_PAL3.m_nRenderTarget2State_DE8E24) |= 2u;
    g_PAL3.m_nRenderTarget2_DE8E08 = 0;
    g_PAL3.m_nEffObjCount = 0;
    g_PAL3.m_nRenderTarget2_DE8E10 = 0;
    atexit(nullsub_14);
    v4 = v38;
  }
  v7 = (int *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6584);
  g_PAL3.m_nRenderTarget2_DE8E18 = *v7;
  g_PAL3.m_nRenderTarget2_DE8E1C = v7[1];
  g_PAL3.m_nRenderTarget2_DE8E20 = v7[2];
  v8 = (int *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6584);
  g_PAL3.m_nRenderTarget2_DE8E08 = *v8;
  g_PAL3.m_nEffObjCount = v8[1];
  g_PAL3.m_nRenderTarget2_DE8E10 = v8[2];
  if ( !*(_BYTE *)(v4 + 65) )
  {
    if ( v34 <= 0xA )
    {
      *(_BYTE *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 380) = 1;
      ((CCBStageRole *)*(CCBStageRole **)(v3 + 4 * v34 + 24))->SetParam(pParam, 1);
      if ( *((int *)v2 + 26) <= 0 )
        ((CCBStageRole *)*(CCBStageRole **)(v3 + 4 * v34 + 24))->ClearBadPushTask(0.0099999998);
      else
        ((CCBStageRole *)*(CCBStageRole **)(v3 + 4 * v34 + 24))->ClearBadPushTask(0.25);
      if ( *((float *)v2 + 23) > 0.0 )
      {
        *(_DWORD *)(v38 + 44) = g_PAL3.m_nRenderTarget2_DE8E08;
        *(_DWORD *)(v38 + 48) = g_PAL3.m_nEffObjCount;
        *(_DWORD *)(v38 + 52) = g_PAL3.m_nRenderTarget2_DE8E10;
      }
      v4 = v38;
    }
    *(_BYTE *)(v4 + 65) = 1;
  }
  if ( v34 <= 0xA )
  {
    if ( *((float *)v2 + 23) > 0.0 )
    {
      v10 = *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16);
      if ( *(float *)(v4 + 24) - v10 > 0.0 )
      {
        v12 = v10 / *(float *)(v4 + 24);
        v30 = *(float *)(v4 + 44);
        v31 = *(float *)(v4 + 48);
        v32 = *(float *)(v4 + 52);
        v20 = *((float *)v2 + 17) - v31;
        v23 = *((float *)v2 + 18) - v32;
        v26 = (*((float *)v2 + 16) - v30) * v12;
        v28 = v20 * v12;
        *(float *)&v21 = v28 + v31;
        v13 = v12 * v23;
        v9 = v26 + v30;
        g_PAL3.m_nEffObjCount = v21;
        *(float *)&v24 = v13 + v32;
        v11 = v24;
        *(float *)&g_PAL3.m_nRenderTarget2_DE8E08 = v9;
      }
      else
      {
        v9 = *((float *)v2 + 16);
        g_PAL3.m_nRenderTarget2_DE8E08 = *((int *)v2 + 16);
        g_PAL3.m_nEffObjCount = *((_DWORD *)v2 + 17);
        v11 = *((_DWORD *)v2 + 18);
      }
      g_PAL3.m_nRenderTarget2_DE8E10 = v11;
    }
    else
    {
      v27 = *((float *)v2 + 8) * fVal;
      v29 = *((float *)v2 + 9) * fVal;
      v9 = *((float *)v2 + 7) * fVal + *(float *)&g_PAL3.m_nRenderTarget2_DE8E08;
      *(float *)&g_PAL3.m_nRenderTarget2_DE8E08 = v9;
      *(float *)&g_PAL3.m_nEffObjCount = v27 + *(float *)&g_PAL3.m_nEffObjCount;
      *(float *)&g_PAL3.m_nRenderTarget2_DE8E10 = v29 + *(float *)&g_PAL3.m_nRenderTarget2_DE8E10;
    }
    v14 = *(_DWORD *)(v3 + 4 * v34 + 24);
    *(float *)(v14 + 6584) = v9;
    v14 += 6584;
    *(_DWORD *)(v14 + 4) = g_PAL3.m_nEffObjCount;
    *(_DWORD *)(v14 + 8) = g_PAL3.m_nRenderTarget2_DE8E10;
    if ( v2[113] )
    {
      if ( (g_PAL3.m_nRenderTarget2State_DE8E24 & 4) == 0 )
      {
        g_PAL3.m_nRenderTarget2_DE8DF8 = 0;
        LOBYTE(g_PAL3.m_nRenderTarget2State_DE8E24) |= 4u;
        g_PAL3.m_nRenderTarget2_DE8DFC = 0;
        g_PAL3.m_nRenderTarget2_DE8E00 = 0;
        atexit(nullsub_13);
        v4 = v38;
      }
      if ( *(float *)&g_PAL3.m_nRenderTarget2_DE8E18 != *(float *)&g_PAL3.m_nRenderTarget2_DE8E08
        || *(float *)&g_PAL3.m_nRenderTarget2_DE8E1C != *(float *)&g_PAL3.m_nEffObjCount
        || *(float *)&g_PAL3.m_nRenderTarget2_DE8E20 != *(float *)&g_PAL3.m_nRenderTarget2_DE8E10 )
      {
        *(float *)&v22 = *(float *)&g_PAL3.m_nEffObjCount - *(float *)&g_PAL3.m_nRenderTarget2_DE8E1C;
        g_PAL3.m_nRenderTarget2_DE8DFC = v22;
        *(float *)&v25 = *(float *)&g_PAL3.m_nRenderTarget2_DE8E10 - *(float *)&g_PAL3.m_nRenderTarget2_DE8E20;
        *(float *)&g_PAL3.m_nRenderTarget2_DE8DF8 = *(float *)&g_PAL3.m_nRenderTarget2_DE8E08
                                                  - *(float *)&g_PAL3.m_nRenderTarget2_DE8E18;
        g_PAL3.m_nRenderTarget2_DE8E00 = v25;
        ((gbVec3D *)&g_PAL3.m_nRenderTarget2_DE8DF8)->Normalize();
        if ( (g_PAL3.m_nRenderTarget2State_DE8E24 & 8) == 0 )
        {
          LOBYTE(g_PAL3.m_nRenderTarget2State_DE8E24) |= 8u;
          *(&g_PAL3._todo_F9C + 235) = 0;
          *(&g_PAL3._todo_F9C + 236) = 0;
          *(&g_PAL3._todo_F9C + 237) = 1065353216;
          atexit(nullsub_12);
        }
        v15 = acos(
                *((float *)&g_PAL3._todo_F9C + 237) * *(float *)&g_PAL3.m_nRenderTarget2_DE8E00
              + *((float *)&g_PAL3._todo_F9C + 236) * *(float *)&g_PAL3.m_nRenderTarget2_DE8DFC
              + *((float *)&g_PAL3._todo_F9C + 235) * *(float *)&g_PAL3.m_nRenderTarget2_DE8DF8);
        if ( *(float *)&g_PAL3.m_nRenderTarget2_DE8DF8 < 0.0 )
          v15 = 6.2831855 - v15;
        v4 = v38;
        *(float *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6632) = v15 * 57.29578;
      }
    }
    if ( *((float *)v2 + 20) != 0.0 )
    {
      fVala = fVal * *((float *)v2 + 20) + ((CCBStageRole *)*(_DWORD *)(v3 + 4 * v34 + 24))->PushBackAllTask();
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      if ( fVala <= 1.0 )
      {
        if ( fVala < 0.0 )
          fVala = 0.0;
        ((CCBStageRole *)*(CCBStageRole **)(v3 + 4 * v34 + 24))->ClearAniMsg(1, fVala);
      }
      else
      {
        ((CCBStageRole *)*(CCBStageRole **)(v3 + 4 * v34 + 24))->ClearAniMsg(1, 1.0);
      }
      v4 = v38;
    }
    v16 = *((float *)v2 + 22);
    v17 = *(_DWORD *)(v3 + 4 * v34 + 24);
    *(float *)(v17 + 384) = *((float *)v2 + 21);
    *(float *)(v17 + 388) = v16;
    if ( v2[114] )
    {
      v18 = *(_DWORD *)(v3 + 4 * v34 + 24);
      if ( *(_DWORD *)(v18 + 6640) == *(_DWORD *)(v18 + 6644) )
      {
        if ( *((float *)v2 + 29) > 0.0 )
          *(float *)(v18 + 6632) = *((float *)v2 + 29);
        goto LABEL_56;
      }
    }
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
  {
    if ( v34 > 0xA )
    {
LABEL_57:
      *(_DWORD *)(v4 + 8) = 4;
      return 0;
    }
    if ( *((float *)v2 + 29) > 0.0 )
      *(float *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6632) = *((float *)v2 + 29);
LABEL_56:
    ((CCBStageRole *)*(CCBStageRole **)(v3 + 4 * v34 + 24))->ClearBadPushTask(0.0099999998);
    v4 = v38;
    goto LABEL_57;
  }
  return 0;
}

// 0x004C13B0
int RenderTarget2::RenderScene(
        
        int nVal,
        int nVal2,
        int nVal3,
        int *p_DWORD,
        int nVal4,
        int nVal5)
{
  int m_nCurPass; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  m_nCurPass = this->m_nCurPass;
  v9 = 0;
  if ( m_nCurPass <= 0 )
    return -1;
  v10 = *(_DWORD *)(this->m_SubObj + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= m_nCurPass )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_PAL3.m_nRenderTarget2Count;
  if ( !g_PAL3.m_nRenderTarget2Count || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_PAL3.m_nRenderTarget2Count = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = v13 + 7;
    *v15 = *p_DWORD;
    v15[1] = p_DWORD[1];
    v15[2] = p_DWORD[2];
    v15[3] = p_DWORD[3];
  }
  ++*(_DWORD *)(this->m_SubObj + 152 * nVal + 4);
  return v9;
}

// 0x004C1490
RenderTarget2 * RenderTarget2::BeginRenderPass(void *Block, char pData)
{
  int m_nCurTarget; // eax
  int v5; // ebx
  int v6; // edi

  m_nCurTarget = this->m_nCurTarget;
  if ( m_nCurTarget || this->m_nCurPass )
  {
    v5 = 0;
    if ( m_nCurTarget > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(this->m_SubObj + v6));
        ++v5;
        *(_DWORD *)(this->m_SubObj + v6) = 0;
        v6 += 152;
      }
      while ( v5 < this->m_nCurTarget );
    }
    operator delete((void *)this->m_SubObj);
    this->m_SubObj = 0;
    this->m_nCurTarget = 0;
    this->m_nCurPass = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C1550
void RenderTarget2::UpdateFrame(float a2)
{
  ((CEffAction *)((char *)this - 12))->UpdateFrame(a2);
}

// 0x004C1560
char * RenderTarget2::vfunc_2(char a2)
{
  return ((CEffAction *)((char *)this - 12))->ExecutePasses(a2);
}

// 0x004C1570
CEffAudio ** RenderTarget2::Reset()
{
  this->m_pSurface = 0;
  this->m_bActive = 0;
  this->m_nFallbackMode = 0;
  this->m_fBlendParam = 0.0;
  this->m_pTargetArray = 0;
  this->m_nCurTarget = -1;
  this->m_nCurPass = -1;
  this->m_fTime = 0.0;
  this->m_nMaxTargets = 0;
  this->m_nMaxPasses = 0;
  return (CEffAudio **)this;
}

// 0x004C15B0
CEffAudio ** RenderTarget2::CreateEffAudio()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x130u);
  if ( v1 )
    return ((RenderTarget2 *)v1)->Reset();
  else
    return 0;
}

// 0x004C1640
char * RenderTarget2::DestroyEffBase(char a2)
{

  if ( (a2 & 1) != 0 )
    operator delete(this);
  return (char *)this;
}

// 0x004C1660
int RenderTarget2::DestroyEffBase()
{
  int *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->m_SubObj : 0;
  if ( v1[7] || (result = *(this != 0 ? &this->m_nMaxPasses : (int *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? &this->m_nMaxTargets : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + v1[3]));
        ++v3;
        *(_DWORD *)(v4 + v1[3]) = 0;
        v4 += 152;
      }
      while ( v3 < v1[7] );
    }
    operator delete((void *)v1[3]);
    v1[3] = 0;
    v1[7] = 0;
    v1[8] = 0;
    return 0;
  }
  return result;
}

// 0x004C1700
void RenderTarget2::LoadResourcesByIndex(float *pfVal)
{
  CScreenMode *Instance; // eax
  CScreenMode *v4; // eax
  CScreenMode *v5; // eax
  CScreenMode *v6; // eax

  if ( *pfVal != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)*pfVal);
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->PlaySoundStream(&this->m_szFmtBuf);
  }
  if ( pfVal[2] != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)pfVal[2]);
    v4 = CScreenMode::GetInstance();
    ((CScreenMode *)v4)->PlaySoundStream(&this->m_szFmtBuf);
  }
  if ( pfVal[8] != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)pfVal[8]);
    v5 = CScreenMode::GetInstance();
    ((CScreenMode *)v5)->PlaySoundStream(&this->m_szFmtBuf);
  }
  if ( pfVal[11] != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)pfVal[11]);
    v6 = CScreenMode::GetInstance();
    ((CScreenMode *)v6)->PlaySoundStream(&this->m_szFmtBuf);
  }
}

// 0x004C18D0
void RenderTarget2::CreateSoundTarget(int *p_DWORD)
{
  RenderTarget2 *p_m_SubObj; // ebx
  int m_nMaxTargets; // ecx
  int v4; // edx
  int m_SubObj; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int m_nCurPass; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  p_m_SubObj = (RenderTarget2 *)&this->m_SubObj;
  m_nMaxTargets = this->m_nMaxTargets;
  v4 = 0;
  if ( m_nMaxTargets > 0 )
  {
    m_SubObj = p_m_SubObj->m_SubObj;
    for ( i = (_BYTE *)(m_SubObj + 148); *i; i += 152 )
    {
      if ( ++v4 >= m_nMaxTargets )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(m_SubObj + v7 + 12) = 2;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 148) = 1;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 149) = 1;
    v8 = ++g_PAL3.m_nCombatParam3;
    if ( !g_PAL3.m_nCombatParam3 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_PAL3.m_nCombatParam3 = 1;
    }
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 16) = v8;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 8) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(p_m_SubObj->m_SubObj + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(p_m_SubObj->m_SubObj + v7 + 24), 0, 0x7Cu);
    ++p_m_SubObj->m_pTargetArray;
    if ( v4 != -1 )
    {
      m_nCurPass = p_m_SubObj->m_nCurPass;
      v10 = 0;
      if ( m_nCurPass > 0 )
      {
        v11 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= m_nCurPass )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_PAL3.m_nCombatParam3;
        if ( !g_PAL3.m_nCombatParam3 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_PAL3.m_nCombatParam3 = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_22:
      v15 = p_m_SubObj->m_nCurPass;
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_PAL3.m_nCombatParam3;
        if ( !g_PAL3.m_nCombatParam3 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_PAL3.m_nCombatParam3 = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_31:
      ((RenderTarget2 *)p_m_SubObj)->RenderOverlay(v4, 0 /* TODO: (int)RenderTarget2::ProcessSoundPass */, 0, 0, p_DWORD[18], p_DWORD[19]);
      *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 16) = p_m_SubObj->m_pSurface;
    }
  }
}

// 0x004C1B00
int RenderTarget2::ProcessSoundPass(int nVal)
{
  char *v3; // ebx
  int v4; // edi
  CScreenMode *Instance; // eax
  CScreenMode *v6; // eax
  CScreenMode *v7; // eax
  CScreenMode *v8; // eax

  v3 = &this->m_pTargetArray[152 * this->m_nCurTarget];
  v4 = *(_DWORD *)v3 + 72 * this->m_nCurPass;
  if ( !*(_BYTE *)(v4 + 65) )
  {
    *(_BYTE *)(v4 + 65) = 1;
    *(_DWORD *)(v4 + 44) = 0;
    *(_DWORD *)(v4 + 48) = 0;
    *(_DWORD *)(v4 + 52) = 0;
    *(_DWORD *)(v4 + 56) = 0;
  }
  if ( *((float *)v3 + 6) != 0.0
    && !*(_DWORD *)(v4 + 44)
    && *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *((float *)v3 + 7) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)*((float *)v3 + 6));
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(&this->m_szFmtBuf, 1);
    *(_DWORD *)(v4 + 44) = 1;
  }
  if ( *((float *)v3 + 8) != 0.0
    && !*(_DWORD *)(v4 + 48)
    && *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *((float *)v3 + 9) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)*((float *)v3 + 8));
    v6 = CScreenMode::GetInstance();
    ((CScreenMode *)v6)->AudioSetPosition(&this->m_szFmtBuf, 1);
    *(_DWORD *)(v4 + 48) = 1;
  }
  if ( *((float *)v3 + 14) != 0.0
    && !*(_DWORD *)(v4 + 52)
    && *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *((float *)v3 + 16) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)*((float *)v3 + 14));
    v7 = CScreenMode::GetInstance();
    ((CScreenMode *)v7)->AudioSetPosition(&this->m_szFmtBuf, 1);
    *(_DWORD *)(v4 + 52) = 1;
  }
  if ( *((float *)v3 + 17) != 0.0
    && !*(_DWORD *)(v4 + 56)
    && *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *((float *)v3 + 18) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d", (const char *)&this->m_szPrefix, (int)*((float *)v3 + 17));
    v8 = CScreenMode::GetInstance();
    ((CScreenMode *)v8)->AudioSetPosition(&this->m_szFmtBuf, 1);
    *(_DWORD *)(v4 + 56) = 1;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004C1DD0
int * RenderTarget2::GetEffAudioTemplate(int nType)
{
  int *result; // eax

  switch ( nType )
  {
    case 0:
      result = dword_5D4EB0;
      break;
    case 1:
      result = dword_5D4EA4;
      break;
    case 2:
      result = dword_5D4E98;
      break;
    case 3:
      result = dword_5D4E8C;
      break;
    case 4:
      result = dword_5D4E80;
      break;
    case 5:
      result = dword_5D4E74;
      break;
    case 6:
      result = dword_5D4E68;
      break;
    case 7:
      result = dword_5D4E5C;
      break;
    case 9:
      result = &g_EffEditorState;
      break;
    case 20:
      result = (int *)&g_pszEditorDesc;
      break;
    default:
      result = &g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C1E90
int RenderTarget2::RenderOverlay(
        
        int nVal,
        int nVal2,
        int nVal3,
        int *p_DWORD,
        int nVal4,
        int nVal5)
{
  int m_nCurPass; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  m_nCurPass = this->m_nCurPass;
  v9 = 0;
  if ( m_nCurPass <= 0 )
    return -1;
  v10 = *(_DWORD *)(this->m_SubObj + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= m_nCurPass )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_PAL3.m_nCombatParam3;
  if ( !g_PAL3.m_nCombatParam3 || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_PAL3.m_nCombatParam3 = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = v13 + 7;
    *v15 = *p_DWORD;
    v15[1] = p_DWORD[1];
    v15[2] = p_DWORD[2];
    v15[3] = p_DWORD[3];
  }
  ++*(_DWORD *)(this->m_SubObj + 152 * nVal + 4);
  return v9;
}

// 0x004C1F70
RenderTarget2 * RenderTarget2::DestroyEffAudio(void *Block, char pData)
{
  int m_nCurTarget; // eax
  int v5; // ebx
  int v6; // edi

  m_nCurTarget = this->m_nCurTarget;
  if ( m_nCurTarget || this->m_nCurPass )
  {
    v5 = 0;
    if ( m_nCurTarget > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(this->m_SubObj + v6));
        ++v5;
        *(_DWORD *)(this->m_SubObj + v6) = 0;
        v6 += 152;
      }
      while ( v5 < this->m_nCurTarget );
    }
    operator delete((void *)this->m_SubObj);
    this->m_SubObj = 0;
    this->m_nCurTarget = 0;
    this->m_nCurPass = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C2040
char * RenderTarget2::sub_004C2040(char a2)
{
  return ((RenderTarget2 *)((char *)this - 12))->DestroyEffBase(a2);
}

// 0x004C2050
CEffBink ** RenderTarget2::ResetSurface()
{
  this->m_pSurface = 0;
  this->m_bActive = 0;
  this->m_nFallbackMode = 0;
  this->m_fBlendParam = 0.0;
  this->m_pTargetArray = 0;
  this->m_nCurTarget = -1;
  this->m_nCurPass = -1;
  this->m_fTime = 0.0;
  this->m_nMaxTargets = 0;
  this->m_nMaxPasses = 0;
  return (CEffBink **)this;
}

// 0x004C2090
CEffBink ** RenderTarget2::CreateEffBink()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x130u);
  if ( v1 )
    return ((RenderTarget2 *)v1)->ResetSurface();
  else
    return 0;
}

// 0x004C20B0
char * RenderTarget2::DestroyEffBink(char a2)
{

  if ( (a2 & 1) != 0 )
    operator delete(this);
  return (char *)this;
}

// 0x004C20D0
int RenderTarget2::DestroyEffBink()
{
  int *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->m_SubObj : 0;
  if ( v1[7] || (result = *(this != 0 ? &this->m_nMaxPasses : (int *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? &this->m_nMaxTargets : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + v1[3]));
        ++v3;
        *(_DWORD *)(v4 + v1[3]) = 0;
        v4 += 152;
      }
      while ( v3 < v1[7] );
    }
    operator delete((void *)v1[3]);
    v1[3] = 0;
    v1[7] = 0;
    v1[8] = 0;
    return 0;
  }
  return result;
}

// 0x004C2170
char RenderTarget2::AllocTargets(int nVal)
{
  char *v3; // eax
  int v4; // ebp
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v11; // ebx
  int v12; // edi

  v3 = (char *)operator new(0x4C0u);
  this->m_pTargetArray = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)&this->m_pTargetArray[v5] = operator new(0x2D0u);
      if ( !*(_DWORD *)&this->m_pTargetArray[v5] )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        this->m_nMaxTargets = 8;
        this->m_nMaxPasses = 10;
        v7 = 0;
        do
        {
          this->m_pTargetArray[v7 + 148] = 0;
          v8 = 0;
          if ( this->m_nMaxPasses > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(v9 + *(_DWORD *)&this->m_pTargetArray[v7] - 8) = 0;
            }
            while ( v8 < this->m_nMaxPasses );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < this->m_nMaxTargets );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v11 = v4;
      v12 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)&this->m_pTargetArray[v12]);
        v12 -= 152;
        --v11;
      }
      while ( v11 );
    }
    operator delete(this->m_pTargetArray);
  }
LABEL_10:
  strcpy((char *)&this->m_szPrefix, (const char *)(nVal + 40));
  return 1;
}

// 0x004C2280
void RenderTarget2::CreateVideoTarget(int *p_DWORD)
{
  RenderTarget2 *p_m_SubObj; // ebx
  int m_nMaxTargets; // ecx
  int v4; // edx
  int m_SubObj; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int m_nCurPass; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  p_m_SubObj = (RenderTarget2 *)&this->m_SubObj;
  m_nMaxTargets = this->m_nMaxTargets;
  v4 = 0;
  if ( m_nMaxTargets > 0 )
  {
    m_SubObj = p_m_SubObj->m_SubObj;
    for ( i = (_BYTE *)(m_SubObj + 148); *i; i += 152 )
    {
      if ( ++v4 >= m_nMaxTargets )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(m_SubObj + v7 + 12) = 2;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 148) = 1;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 149) = 1;
    v8 = ++g_PAL3.m_nCombatParam2;
    if ( !g_PAL3.m_nCombatParam2 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_PAL3.m_nCombatParam2 = 1;
    }
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 16) = v8;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 8) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(p_m_SubObj->m_SubObj + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(p_m_SubObj->m_SubObj + v7 + 24), 0, 0x7Cu);
    ++p_m_SubObj->m_pTargetArray;
    if ( v4 != -1 )
    {
      m_nCurPass = p_m_SubObj->m_nCurPass;
      v10 = 0;
      if ( m_nCurPass > 0 )
      {
        v11 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= m_nCurPass )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_PAL3.m_nCombatParam2;
        if ( !g_PAL3.m_nCombatParam2 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_PAL3.m_nCombatParam2 = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_22:
      v15 = p_m_SubObj->m_nCurPass;
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_PAL3.m_nCombatParam2;
        if ( !g_PAL3.m_nCombatParam2 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_PAL3.m_nCombatParam2 = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_31:
      ((RenderTarget2 *)p_m_SubObj)->RenderEffect(v4, 0 /* TODO: (int)RenderTarget2::ProcessVideoPass */, 0, 0, p_DWORD[18], p_DWORD[19]);
      *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 16) = p_m_SubObj->m_pSurface;
    }
  }
}

// 0x004C24B0
int RenderTarget2::ProcessVideoPass(int nVal)
{
  char *v3; // ebx
  int v4; // edi

  v3 = &this->m_pTargetArray[152 * this->m_nCurTarget];
  v4 = *(_DWORD *)v3 + 72 * this->m_nCurPass;
  if ( !*(_BYTE *)(v4 + 65) )
    *(_BYTE *)(v4 + 65) = 1;
  if ( *((float *)v3 + 6) != 0.0 && *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *((float *)v3 + 7) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    sprintf((char *const)&this->m_szFmtBuf, "%s%03d.bik", (const char *)&this->m_szPrefix, (int)*((float *)v3 + 6));
    ((CScreenMode *)&g_ScreenMode)->SetViewport(0, 0);
    ((CScreenMode *)&g_ScreenMode)->CreateDevice((int)&this->m_szFmtBuf, (int)hWnd, 0, 0);
    ((CScreenMode *)&g_ScreenMode)->PlayVideo(1);
    *(_DWORD *)(v4 + 8) = 4;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004C25C0
int * RenderTarget2::GetTargetAddress(int nVal)
{
  switch ( nVal )
  {
    case 0:
      return dword_5D4EC8;
    case 1:
      return dword_5D4ED4;
    case 9:
      return &g_EffEditorState;
  }
  return &g_EffCylinderEditorData;
}

// 0x004C2600
int RenderTarget2::CalcDeltaTime(float fTime)
{
  double v2; // st7

  v2 = fTime - *(float *)&this->m_pSurface;
  *(float *)&this->m_pSurface = fTime;
  *(float *)&this->m_bActive = v2;
  return LODWORD(fTime);
}

// 0x004C2620
void RenderTarget2::RenderEffect(
        
        int nVal,
        int nVal2,
        int nVal3,
        int *p_DWORD,
        int nVal4,
        int nVal5)
{
  int m_nCurPass; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v12; // edx
  unsigned int v13; // eax
  int *v14; // edx

  m_nCurPass = this->m_nCurPass;
  v9 = 0;
  if ( m_nCurPass > 0 )
  {
    v10 = *(_DWORD *)(this->m_SubObj + 152 * nVal);
    for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
    {
      if ( ++v9 >= m_nCurPass )
        return;
    }
    v12 = (int *)(v10 + 72 * v9);
    memset(v12, 0, 0x48u);
    *((_BYTE *)v12 + 65) = 0;
    *((_BYTE *)v12 + 64) = 1;
    *v12 = nVal2;
    v12[1] = nVal3;
    v12[2] = 2;
    v13 = ++g_PAL3.m_nCombatParam2;
    if ( !g_PAL3.m_nCombatParam2 || v13 >= 0x7FFFFFFF )
    {
      v13 = 1;
      g_PAL3.m_nCombatParam2 = 1;
    }
    v12[3] = v13;
    v12[4] = 0;
    v12[5] = nVal4;
    v12[6] = nVal5;
    if ( p_DWORD )
    {
      v14 = v12 + 7;
      *v14 = *p_DWORD;
      v14[1] = p_DWORD[1];
      v14[2] = p_DWORD[2];
      v14[3] = p_DWORD[3];
    }
    ++*(_DWORD *)(this->m_SubObj + 152 * nVal + 4);
  }
}

// 0x004C2700
RenderTarget2 * RenderTarget2::BeginNextPass(void *Block, char pData)
{
  int m_nCurTarget; // eax
  int v5; // ebx
  int v6; // edi

  m_nCurTarget = this->m_nCurTarget;
  if ( m_nCurTarget || this->m_nCurPass )
  {
    v5 = 0;
    if ( m_nCurTarget > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(this->m_SubObj + v6));
        ++v5;
        *(_DWORD *)(this->m_SubObj + v6) = 0;
        v6 += 152;
      }
      while ( v5 < this->m_nCurTarget );
    }
    operator delete((void *)this->m_SubObj);
    this->m_SubObj = 0;
    this->m_nCurTarget = 0;
    this->m_nCurPass = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C27C0
char * RenderTarget2::sub_004C27C0(char a2)
{
  return ((RenderTarget2 *)((char *)this - 12))->DestroyEffBink(a2);
}

// 0x004C27D0
void ** RenderTarget2::Deactivate()
{
  this->m_pSurface = 0;
  this->m_bActive = 0;
  this->m_nFallbackMode = 0;
  this->m_fBlendParam = 0.0;
  this->m_pTargetArray = 0;
  this->m_nCurTarget = -1;
  this->m_nCurPass = -1;
  this->m_fTime = 0.0;
  this->m_nMaxTargets = 0;
  this->m_nMaxPasses = 0;
  this->m_szPrefix = 0;
  this->m_fSpeed = 0.0;
  this->m_fParam = 0.0;
  this->m_fBlend = 0.0;
  return (void **)&this->m_pVtable;
}

// 0x004C2820
void ** RenderTarget2::CreateDeactivated()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x40u);
  if ( v1 )
    return ((RenderTarget2 *)v1)->Deactivate();
  else
    return 0;
}

// 0x004C2840
char RenderTarget2::do_always_noconv()
{
  return 1;
}

// 0x004C2850
int RenderTarget2::AdjustThisCall(int ( *a2)(char *, int), int a3, int a4)
{
  return a2((char *)this + a3 - 12, a4);
}

// 0x004C2870
char * RenderTarget2::BeginMultiPass(char a2)
{

  if ( (a2 & 1) != 0 )
    operator delete(this);
  return (char *)this;
}

// 0x004C2890
int RenderTarget2::BeginMultiPass()
{
  int *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->m_SubObj : 0;
  if ( v1[7] || (result = *(this != 0 ? &this->m_nMaxPasses : (int *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? &this->m_nMaxTargets : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + v1[3]));
        ++v3;
        *(_DWORD *)(v4 + v1[3]) = 0;
        v4 += 152;
      }
      while ( v3 < v1[7] );
    }
    operator delete((void *)v1[3]);
    v1[3] = 0;
    v1[7] = 0;
    v1[8] = 0;
    return 0;
  }
  return result;
}

// 0x004C2930
int RenderTarget2::InitTargetPos(float *pfVal, float fVal, float fVal2, float fVal3)
{
  char *m_pSurface; // esi
  RenderTarget2 **v6; // edx
  int v7; // eax
  int result; // eax

  this->m_bActive = 0;
  m_pSurface = this->m_pSurface;
  *(float *)&this->m_szPrefix = fVal + pfVal[46];
  v6 = (RenderTarget2 **)(m_pSurface + 2348);
  this->m_fSpeed = fVal2 + pfVal[47];
  v7 = 0;
  this->m_fParam = fVal3 + pfVal[48];
  while ( !*((_BYTE *)v6 - 4) || *v6 != this )
  {
    ++v7;
    v6 += 5;
    if ( v7 >= 2048 )
    {
      this->m_fBlend = 0.0;
      return 0;
    }
  }
  result = *(_DWORD *)&m_pSurface[20 * v7 + 2340];
  LODWORD(this->m_fBlend) = result;
  return result;
}

// 0x004C29A0
void RenderTarget2::UpdateInternal(float fVal)
{
  int *p_m_SubObj; // esi
  int v3; // ebx
  int *v4; // ebp
  int v5; // edx
  int v6; // edi
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // edx
  _DWORD *v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // [esp+0xC] [ebp-0x8]
  RenderTarget2 *v17; // [esp+0x10] [ebp-0x4]
  int fVala; // [esp+0x18] [ebp+0x4]

  p_m_SubObj = &this->m_SubObj;
this->m_fBlendParam = fVal - *(float *)&this->m_nFallbackMode;
  *(float *)&this->m_nFallbackMode = fVal;
  if ( this->m_fBlendParam > 0.0 )
  {
    v3 = 0;
    fVala = 0;
    if ( this->m_nMaxTargets > 0 )
    {
      while ( 1 )
      {
        v4 = (int *)(v3 + p_m_SubObj[3]);
        if ( *((_BYTE *)v4 + 148) )
        {
          if ( v4[3] == 3 )
          {
            v5 = 0;
            v16 = 0;
            if ( p_m_SubObj[8] > 0 )
              break;
          }
        }
LABEL_33:
        v3 += 152;
        if ( ++fVala >= p_m_SubObj[7] )
        {
          this = v17;
          goto LABEL_35;
        }
      }
      v6 = 0;
      while ( 1 )
      {
        v7 = *v4;
        if ( !*(_BYTE *)(v6 + *v4 + 64) || v6 > 0 && *(_DWORD *)(v6 + v7 - 64) == 2 )
          goto LABEL_33;
        switch ( *(_DWORD *)(v6 + v7 + 8) )
        {
          case 2:
            if ( v6 > 0 )
            {
              if ( *(float *)(v6 + v7 + 20) >= 0.0 )
              {
                if ( *((float *)p_m_SubObj + 1) - *(float *)(v6 + v7 - 56) > *(float *)(v6 + v7 + 20) )
                {
LABEL_25:
                  *(_DWORD *)(*(_DWORD *)(v3 + p_m_SubObj[3]) + v6 + 8) = 3;
                  *(_DWORD *)(*(_DWORD *)(v3 + p_m_SubObj[3]) + v6 + 16) = p_m_SubObj[1];
                  p_m_SubObj[4] = fVala;
                  p_m_SubObj[5] = v16;
                  goto LABEL_26;
                }
              }
              else if ( *(_DWORD *)(v6 + v7 - 64) == 4 )
              {
                goto LABEL_25;
              }
            }
            break;
          case 3:
            p_m_SubObj[5] = v5;
            p_m_SubObj[4] = fVala;
LABEL_26:
            (*(void ( **)(int *, _DWORD, _DWORD, _DWORD))(*p_m_SubObj + 4))(
              p_m_SubObj,
              *(_DWORD *)(*v4 + v6),
              *(_DWORD *)(*v4 + v6 + 4),
              0);
            break;
          case 4:
            v8 = 0;
            v9 = (_DWORD *)(v3 + p_m_SubObj[3]);
            v10 = v9[1];
            if ( v10 <= 0 )
            {
LABEL_17:
              v12 = v4[1];
              v4[3] = 4;
              v13 = 9 * v12;
              LOBYTE(v12) = *((_BYTE *)v4 + 149);
              v4[5] = *(_DWORD *)(*v4 + 8 * v13 - 12);
              if ( (_BYTE)v12 == 1 )
              {
                v14 = 0;
                *(_BYTE *)(v3 + p_m_SubObj[3] + 148) = 0;
                if ( p_m_SubObj[8] > 0 )
                {
                  v15 = 0;
                  do
                  {
                    ++v14;
                    v15 += 72;
                    *(_BYTE *)(*(_DWORD *)(v3 + p_m_SubObj[3]) + v15 - 8) = 0;
                  }
                  while ( v14 < p_m_SubObj[8] );
                }
                *(_DWORD *)(v3 + p_m_SubObj[3] + 4) = 0;
                --p_m_SubObj[6];
                goto LABEL_33;
              }
            }
            else
            {
              v11 = (_DWORD *)(*v9 + 8);
              while ( *v11 == 4 )
              {
                ++v8;
                v11 += 18;
                if ( v8 >= v10 )
                  goto LABEL_17;
              }
            }
            break;
        }
        v5 = v16 + 1;
        v6 += 72;
        if ( ++v16 >= p_m_SubObj[8] )
          goto LABEL_33;
      }
    }
LABEL_35:
    if ( SLODWORD(this->m_fTime) <= 0 )
      this->m_bActive = 1;
  }
}

// 0x004C2BA0
void RenderTarget2::RenderFromParams(float *pfVal)
{
  if ( *pfVal != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    ((CEffect *)this->m_pSurface)->Render((int)*pfVal);
  }
  if ( pfVal[8] != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    ((CEffect *)this->m_pSurface)->Render((int)pfVal[8]);
  }
  if ( pfVal[5] != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    ((CEffect *)this->m_pSurface)->Render((int)pfVal[5]);
  }
  if ( pfVal[14] != 0.0 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    ((CEffect *)this->m_pSurface)->Render((int)pfVal[14]);
  }
}

// 0x004C2D00
void RenderTarget2::CreateEffectTarget(int *p_DWORD)
{
  RenderTarget2 *p_m_SubObj; // ebx
  int m_nMaxTargets; // ecx
  int v4; // edx
  int m_SubObj; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int m_nCurPass; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  p_m_SubObj = (RenderTarget2 *)&this->m_SubObj;
  m_nMaxTargets = this->m_nMaxTargets;
  v4 = 0;
  if ( m_nMaxTargets > 0 )
  {
    m_SubObj = p_m_SubObj->m_SubObj;
    for ( i = (_BYTE *)(m_SubObj + 148); *i; i += 152 )
    {
      if ( ++v4 >= m_nMaxTargets )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(m_SubObj + v7 + 12) = 2;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 148) = 1;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 149) = 1;
    v8 = ++g_PAL3.m_nCombatParam1;
    if ( !g_PAL3.m_nCombatParam1 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_PAL3.m_nCombatParam1 = 1;
    }
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 16) = v8;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 8) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(p_m_SubObj->m_SubObj + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(p_m_SubObj->m_SubObj + v7 + 24), 0, 0x7Cu);
    ++p_m_SubObj->m_pTargetArray;
    if ( v4 != -1 )
    {
      m_nCurPass = p_m_SubObj->m_nCurPass;
      v10 = 0;
      if ( m_nCurPass > 0 )
      {
        v11 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= m_nCurPass )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_PAL3.m_nCombatParam1;
        if ( !g_PAL3.m_nCombatParam1 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_PAL3.m_nCombatParam1 = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_22:
      v15 = p_m_SubObj->m_nCurPass;
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_PAL3.m_nCombatParam1;
        if ( !g_PAL3.m_nCombatParam1 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_PAL3.m_nCombatParam1 = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_31:
      ((RenderTarget2 *)p_m_SubObj)->RenderPostProcess(v4, 0 /* TODO: (int)CEffMgr::ProcessEffectPass */, 0, 0, p_DWORD[18], p_DWORD[19]);
      *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 16) = p_m_SubObj->m_pSurface;
    }
  }
}

// 0x004C3160
int * RenderTarget2::GetCallbackTable(int nVal)
{
  int *result; // eax

  switch ( nVal )
  {
    case 0:
      result = dword_5D4F58;
      break;
    case 1:
      result = dword_5D4F50;
      break;
    case 2:
      result = dword_5D4F48;
      break;
    case 3:
      result = dword_5D4F40;
      break;
    case 4:
      result = dword_5D4F38;
      break;
    case 5:
      result = dword_5D4F30;
      break;
    case 6:
      result = dword_5D4F28;
      break;
    case 7:
      result = dword_5D4F20;
      break;
    case 9:
      result = &g_EffEditorState;
      break;
    case 12:
      result = dword_5D4F18;
      break;
    case 13:
      result = dword_5D4F10;
      break;
    case 14:
      result = dword_5D4F08;
      break;
    case 15:
      result = dword_5D4F00;
      break;
    case 16:
      result = dword_5D4EF8;
      break;
    case 17:
      result = dword_5D4EF0;
      break;
    case 18:
      result = dword_5D4EE8;
      break;
    case 19:
      result = dword_5D4EE0;
      break;
    case 20:
      result = (int *)&g_pszEditorDesc;
      break;
    default:
      result = &g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C3260
int RenderTarget2::RenderPostProcess(
        
        int nVal,
        int nVal2,
        int nVal3,
        int *p_DWORD,
        int nVal4,
        int nVal5)
{
  int m_nCurPass; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  m_nCurPass = this->m_nCurPass;
  v9 = 0;
  if ( m_nCurPass <= 0 )
    return -1;
  v10 = *(_DWORD *)(this->m_SubObj + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= m_nCurPass )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_PAL3.m_nCombatParam1;
  if ( !g_PAL3.m_nCombatParam1 || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_PAL3.m_nCombatParam1 = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = v13 + 7;
    *v15 = *p_DWORD;
    v15[1] = p_DWORD[1];
    v15[2] = p_DWORD[2];
    v15[3] = p_DWORD[3];
  }
  ++*(_DWORD *)(this->m_SubObj + 152 * nVal + 4);
  return v9;
}

// 0x004C3400
char * RenderTarget2::sub_004C3400(char a2)
{
  return ((RenderTarget2 *)((char *)this - 12))->BeginMultiPass(a2);
}

// 0x004C3450
CEffCallBack ** RenderTarget2::ResetTargetSlot()
{
  this->m_pSurface = 0;
  this->m_bActive = 0;
  this->m_nFallbackMode = 0;
  this->m_fBlendParam = 0.0;
  this->m_pTargetArray = 0;
  this->m_nCurTarget = -1;
  this->m_nCurPass = -1;
  this->m_fTime = 0.0;
  this->m_nMaxTargets = 0;
  this->m_nMaxPasses = 0;
  return (CEffCallBack **)this;
}

// 0x004C3490
CEffCallBack ** RenderTarget2::CreateEffCallBack()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x30u);
  if ( v1 )
    return ((RenderTarget2 *)v1)->ResetTargetSlot();
  else
    return 0;
}

// 0x004C34D0
int RenderTarget2::DestroyEffCallBack()
{
  int *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->m_SubObj : 0;
  if ( v1[7] || (result = *(this != 0 ? &this->m_nMaxPasses : (int *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? &this->m_nMaxTargets : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + v1[3]));
        ++v3;
        *(_DWORD *)(v4 + v1[3]) = 0;
        v4 += 152;
      }
      while ( v3 < v1[7] );
    }
    operator delete((void *)v1[3]);
    v1[3] = 0;
    v1[7] = 0;
    v1[8] = 0;
    return 0;
  }
  return result;
}

// 0x004C3570
void RenderTarget2::UpdatePost(float fVal)
{
  int *p_m_SubObj; // esi
  int v3; // ebx
  int *v4; // ebp
  int v5; // edx
  int v6; // edi
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // edx
  _DWORD *v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // [esp+0xC] [ebp-0x8]
  RenderTarget2 *v17; // [esp+0x10] [ebp-0x4]
  int fVala; // [esp+0x18] [ebp+0x4]

  p_m_SubObj = &this->m_SubObj;
this->m_fBlendParam = fVal - *(float *)&this->m_nFallbackMode;
  *(float *)&this->m_nFallbackMode = fVal;
  if ( this->m_fBlendParam > 0.0 )
  {
    v3 = 0;
    fVala = 0;
    if ( this->m_nMaxTargets > 0 )
    {
      while ( 1 )
      {
        v4 = (int *)(v3 + p_m_SubObj[3]);
        if ( *((_BYTE *)v4 + 148) )
        {
          if ( v4[3] == 3 )
          {
            v5 = 0;
            v16 = 0;
            if ( p_m_SubObj[8] > 0 )
              break;
          }
        }
LABEL_33:
        v3 += 152;
        if ( ++fVala >= p_m_SubObj[7] )
        {
          this = v17;
          goto LABEL_35;
        }
      }
      v6 = 0;
      while ( 1 )
      {
        v7 = *v4;
        if ( !*(_BYTE *)(v6 + *v4 + 64) || v6 > 0 && *(_DWORD *)(v6 + v7 - 64) == 2 )
          goto LABEL_33;
        switch ( *(_DWORD *)(v6 + v7 + 8) )
        {
          case 2:
            if ( v6 > 0 )
            {
              if ( *(float *)(v6 + v7 + 20) >= 0.0 )
              {
                if ( *((float *)p_m_SubObj + 1) - *(float *)(v6 + v7 - 56) > *(float *)(v6 + v7 + 20) )
                {
LABEL_25:
                  *(_DWORD *)(*(_DWORD *)(v3 + p_m_SubObj[3]) + v6 + 8) = 3;
                  *(_DWORD *)(*(_DWORD *)(v3 + p_m_SubObj[3]) + v6 + 16) = p_m_SubObj[1];
                  p_m_SubObj[4] = fVala;
                  p_m_SubObj[5] = v16;
                  goto LABEL_26;
                }
              }
              else if ( *(_DWORD *)(v6 + v7 - 64) == 4 )
              {
                goto LABEL_25;
              }
            }
            break;
          case 3:
            p_m_SubObj[5] = v5;
            p_m_SubObj[4] = fVala;
LABEL_26:
            (*(void ( **)(int *, _DWORD, _DWORD, _DWORD))(*p_m_SubObj + 4))(
              p_m_SubObj,
              *(_DWORD *)(*v4 + v6),
              *(_DWORD *)(*v4 + v6 + 4),
              0);
            break;
          case 4:
            v8 = 0;
            v9 = (_DWORD *)(v3 + p_m_SubObj[3]);
            v10 = v9[1];
            if ( v10 <= 0 )
            {
LABEL_17:
              v12 = v4[1];
              v4[3] = 4;
              v13 = 9 * v12;
              LOBYTE(v12) = *((_BYTE *)v4 + 149);
              v4[5] = *(_DWORD *)(*v4 + 8 * v13 - 12);
              if ( (_BYTE)v12 == 1 )
              {
                v14 = 0;
                *(_BYTE *)(v3 + p_m_SubObj[3] + 148) = 0;
                if ( p_m_SubObj[8] > 0 )
                {
                  v15 = 0;
                  do
                  {
                    ++v14;
                    v15 += 72;
                    *(_BYTE *)(*(_DWORD *)(v3 + p_m_SubObj[3]) + v15 - 8) = 0;
                  }
                  while ( v14 < p_m_SubObj[8] );
                }
                *(_DWORD *)(v3 + p_m_SubObj[3] + 4) = 0;
                --p_m_SubObj[6];
                goto LABEL_33;
              }
            }
            else
            {
              v11 = (_DWORD *)(*v9 + 8);
              while ( *v11 == 4 )
              {
                ++v8;
                v11 += 18;
                if ( v8 >= v10 )
                  goto LABEL_17;
              }
            }
            break;
        }
        v5 = v16 + 1;
        v6 += 72;
        if ( ++v16 >= p_m_SubObj[8] )
          goto LABEL_33;
      }
    }
LABEL_35:
    if ( SLODWORD(this->m_fTime) <= 0 )
      this->m_bActive = 1;
  }
}

// 0x004C3770
void RenderTarget2::CreateCameraTarget(int *p_DWORD)
{
  RenderTarget2 *p_m_SubObj; // ebx
  int m_nMaxTargets; // ecx
  int v4; // edx
  int m_SubObj; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int m_nCurPass; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  p_m_SubObj = (RenderTarget2 *)&this->m_SubObj;
  m_nMaxTargets = this->m_nMaxTargets;
  v4 = 0;
  if ( m_nMaxTargets > 0 )
  {
    m_SubObj = p_m_SubObj->m_SubObj;
    for ( i = (_BYTE *)(m_SubObj + 148); *i; i += 152 )
    {
      if ( ++v4 >= m_nMaxTargets )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(m_SubObj + v7 + 12) = 2;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 148) = 1;
    *(_BYTE *)(p_m_SubObj->m_SubObj + v7 + 149) = 1;
    v8 = ++g_PAL3.m_nCEffExplosiveCount;
    if ( !g_PAL3.m_nCEffExplosiveCount || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_PAL3.m_nCEffExplosiveCount = 1;
    }
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 16) = v8;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 8) = 0;
    *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(p_m_SubObj->m_SubObj + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(p_m_SubObj->m_SubObj + v7 + 24), 0, 0x7Cu);
    ++p_m_SubObj->m_pTargetArray;
    if ( v4 != -1 )
    {
      m_nCurPass = p_m_SubObj->m_nCurPass;
      v10 = 0;
      if ( m_nCurPass > 0 )
      {
        v11 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= m_nCurPass )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_PAL3.m_nCEffExplosiveCount;
        if ( !g_PAL3.m_nCEffExplosiveCount || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_PAL3.m_nCEffExplosiveCount = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_22:
      v15 = p_m_SubObj->m_nCurPass;
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(p_m_SubObj->m_SubObj + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_PAL3.m_nCEffExplosiveCount;
        if ( !g_PAL3.m_nCEffExplosiveCount || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_PAL3.m_nCEffExplosiveCount = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 4);
      }
LABEL_31:
      ((RenderTarget2 *)p_m_SubObj)->RenderFinal(v4, 0 /* TODO: (int)RenderTarget2::ProcessCameraPass */, 0, 0, p_DWORD[18], p_DWORD[19]);
      *(_DWORD *)(p_m_SubObj->m_SubObj + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_SubObj->m_SubObj + v7) + 16) = p_m_SubObj->m_pSurface;
    }
  }
}

// 0x004C39A0
int RenderTarget2::ProcessCameraPass(int nVal)
{
  char *v3; // ebx
  int v4; // edi

  v3 = &this->m_pTargetArray[152 * this->m_nCurTarget];
  v4 = *(_DWORD *)v3 + 72 * this->m_nCurPass;
  if ( !*(_BYTE *)(v4 + 65) )
  {
    ((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*((_DWORD *)this->m_pSurface + 1) + 20) + 16))->AddTask();
    if ( *((float *)v3 + 6) > 0.0 )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      ((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*((_DWORD *)this->m_pSurface + 1) + 20) + 16))->ClearFinishedTask((int)*((float *)v3 + 6));
    }
    *(_BYTE *)(v4 + 65) = 1;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 )
  {
    if ( *((float *)v3 + 6) > 0.0 )
      ((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*((_DWORD *)this->m_pSurface + 1) + 20) + 16))->AddTask();
    *(_DWORD *)(v4 + 8) = 4;
  }
  if ( *(float *)&this->m_nFallbackMode - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004C3A90
int * RenderTarget2::GetTargetByType(int nVal)
{
  switch ( nVal )
  {
    case 0:
      return dword_5D4F78;
    case 9:
      return &g_EffEditorState;
    case 20:
      return (int *)&g_pszEditorDesc;
  }
  return &g_EffCylinderEditorData;
}

// 0x004C3AD0
int RenderTarget2::RenderFinal(
        
        int nVal,
        int nVal2,
        int nVal3,
        int *p_DWORD,
        int nVal4,
        int nVal5)
{
  int m_nCurPass; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  m_nCurPass = this->m_nCurPass;
  v9 = 0;
  if ( m_nCurPass <= 0 )
    return -1;
  v10 = *(_DWORD *)(this->m_SubObj + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= m_nCurPass )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_PAL3.m_nCEffExplosiveCount;
  if ( !g_PAL3.m_nCEffExplosiveCount || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_PAL3.m_nCEffExplosiveCount = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = v13 + 7;
    *v15 = *p_DWORD;
    v15[1] = p_DWORD[1];
    v15[2] = p_DWORD[2];
    v15[3] = p_DWORD[3];
  }
  ++*(_DWORD *)(this->m_SubObj + 152 * nVal + 4);
  return v9;
}

// 0x004C3BB0
RenderTarget2 * RenderTarget2::AdvancePass(void *Block, char pData)
{
  int m_nCurTarget; // eax
  int v5; // ebx
  int v6; // edi

  m_nCurTarget = this->m_nCurTarget;
  if ( m_nCurTarget || this->m_nCurPass )
  {
    v5 = 0;
    if ( m_nCurTarget > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(this->m_SubObj + v6));
        ++v5;
        *(_DWORD *)(this->m_SubObj + v6) = 0;
        v6 += 152;
      }
      while ( v5 < this->m_nCurTarget );
    }
    operator delete((void *)this->m_SubObj);
    this->m_SubObj = 0;
    this->m_nCurTarget = 0;
    this->m_nCurPass = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C3C70
void RenderTarget2::sub_4C3C70(float a2)
{
  ((RenderTarget2 *)(this - 12))->UpdatePost(a2);
}

// 0x004C3C80
char * RenderTarget2::_sdtor_35(char a2)
{
  char *v2; // esi

  v2 = this - 12;
  ((RenderTarget2 *)(this - 12))->DestroyEffCallBack();
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004C5800
void RenderTarget2::sub_4C5800(float a2)
{
  ((CEffCylinder *)(this - 12))->CreateTask(a2);
}

// 0x004CEEC0
int RenderTarget2::AddCallbackEffect(
        
        RenderTarget2 *pTarget,
        int nVal,
        RenderTarget2 *pParam)
{
  int v4; // ebp
  int *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  RenderTarget2 *v9; // eax
  CEffCallBack **v10; // eax

  v4 = 0;
  for ( i = &this->m_EffectSlots; *(_BYTE *)i; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pTarget);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (RenderTarget2 *)operator new(0x30u);
  if ( v9 )
    v10 = ((RenderTarget2 *)v9)->ResetTargetSlot();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pTarget);
  return v4;
}

// 0x004CF340
int RenderTarget2::AddGenericEffect(
        
        RenderTarget2 *pTarget,
        int nVal,
        RenderTarget2 *pParam)
{
  int v4; // ebp
  int *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  RenderTarget2 *v9; // eax
  void **v10; // eax

  v4 = 0;
  for ( i = &this->m_EffectSlots; *(_BYTE *)i; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pTarget);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (RenderTarget2 *)operator new(0x40u);
  if ( v9 )
    v10 = ((RenderTarget2 *)v9)->Deactivate();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pTarget);
  return v4;
}

// 0x004CFA00
int RenderTarget2::AddBinkEffect(
        
        RenderTarget2 *pTarget,
        int nVal,
        RenderTarget2 *pParam)
{
  int v4; // ebp
  int *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  RenderTarget2 *v9; // eax
  CEffBink **v10; // eax

  v4 = 0;
  for ( i = &this->m_EffectSlots; *(_BYTE *)i; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pTarget);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (RenderTarget2 *)operator new(0x130u);
  if ( v9 )
    v10 = ((RenderTarget2 *)v9)->ResetSurface();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pTarget);
  return v4;
}

// 0x004D05E0
int RenderTarget2::CameraInterpCallback(int nVal)
{
  double v3; // st7
  char *v4; // edi
  int v5; // ecx
  double v6; // st7
  int v7; // ebp
  int m_szPrefix; // ecx
  double v9; // st7
  int v10; // ecx
  double v11; // st7
  float v13; // [esp+0x4] [ebp-0x8C]
  float v14; // [esp+0x18] [ebp-0x78] BYREF
  float m_fBlendParam; // [esp+0x1C] [ebp-0x74]
  gbVec3D v16; // [esp+0x20] [ebp-0x70] BYREF
  struct gbVec3D v17; // [esp+0x2C] [ebp-0x64] BYREF
  float v18; // [esp+0x3C] [ebp-0x54]
  float v19; // [esp+0x40] [ebp-0x50]
  float v20; // [esp+0x48] [ebp-0x48]
  float v21; // [esp+0x4C] [ebp-0x44]
  gbMatrix4 v22; // [esp+0x50] [ebp-0x40] BYREF

  v3 = *(float *)&this->m_nFallbackMode;
  v4 = &this->m_pTargetArray[152 * this->m_nCurTarget];
  v5 = 9 * this->m_nCurPass;
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  m_fBlendParam = this->m_fBlendParam;
  if ( v6 > *(float *)(v7 + 24) )
    m_fBlendParam = m_fBlendParam - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    m_szPrefix = this->m_szPrefix;
    LOBYTE(this->m_EffectSlots) = 1;
    if ( m_szPrefix )
      (*(void ( **)(int, _DWORD))(*(_DWORD *)m_szPrefix + 24))(m_szPrefix, 0);
    *(_BYTE *)(v7 + 65) = 1;
  }
  v9 = *((float *)v4 + 7);
  v18 = *((float *)v4 + 8);
  v19 = *((float *)v4 + 9);
  v20 = v18 * m_fBlendParam;
  v21 = v19 * m_fBlendParam;
  this->m_fSpeed = v9 * m_fBlendParam + this->m_fSpeed;
  this->m_fParam = v20 + this->m_fParam;
  this->m_fBlend = v21 + this->m_fBlend;
  *((float *)&this->m_EffectSlots + 1) = *((float *)v4 + 6) + *((float *)&this->m_EffectSlots + 1);
  *((float *)&this->m_EffectSlots + 2) = *((float *)v4 + 29) + *((float *)&this->m_EffectSlots + 2);
  *((float *)&this->m_EffectSlots + 3) = *((float *)v4 + 27) + *((float *)&this->m_EffectSlots + 3);
  *(&this->m_fBlend + 4) = *((float *)v4 + 16) + *(&this->m_fBlend + 4);
  *(&this->m_fBlend + 5) = *((float *)v4 + 17) + *(&this->m_fBlend + 5);
  *(&this->m_fBlend + 6) = *((float *)v4 + 18) + *(&this->m_fBlend + 6);
  memset(&v16, 0, sizeof(v16));
  memset(&v17, 0, sizeof(v17));
  ((gbMatrix4 *)&v22)->LoadIdentity();
  v16 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v16)->Normalize();
  v13 = (*(float *)&this->m_nFallbackMode - *(float *)(v7 + 16)) * *((float *)v4 + 15);
  ((gbMatrix4 *)&v22)->SetAxisAngle(&v16, v13);
  v17.z = *((float *)v4 + 14);
  v17.x = 0.0;
  v17.y = 0.0;
  ((gbMatrix4 *)&v22)->Rotate(&v17, (gbVec3D *)(&this->m_fBlend + 1));
  if ( *((float *)v4 + 20) != 0.0 )
  {
    v10 = this->m_szPrefix;
    v14 = 0.0;
    if ( ((int ( *)(int, float *))gbVisNode::GetBlend)(v10, &v14) )
      v11 = m_fBlendParam;
    else
      v11 = 1.0;
    m_fBlendParam = v16.x * *((float *)v4 + 20) + v11;
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( m_fBlendParam <= 1.0 )
    {
      if ( m_fBlendParam < 0.0 )
        m_fBlendParam = 0.0;
    }
    else
    {
      m_fBlendParam = 1.0;
    }
    ((gbVisNode *)this->m_szPrefix)->SetBlend(1, LODWORD(m_fBlendParam));
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *(float *)&this->m_nFallbackMode - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
    *(_DWORD *)(v7 + 8) = 4;
  return 0;
}

// 0x0055434F
void __noreturn RenderTarget2::FatalExit()
{
  _amsg_exit(0x19u);
}
