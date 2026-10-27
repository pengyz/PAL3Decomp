#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/RenderTarget2.h"
#include "Combat/CCBCamControl.h"
#include "Combat/CCBStage.h"
#include "Misc/CEffAction.h"
#include "Misc/CEffAudio.h"
#include "Misc/CEffBase.h"
#include "Misc/CEffBink.h"
#include "Misc/CEffCallBack.h"
#include "Effect/CEffCylinder.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffSParticle.h"
#include "Effect/CEffect.h"
#include "Render/CScreenMode.h"
#include "Misc/EffObjectPool.h"
#include "GameBase/PAL3.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/Role.h"
#include "UI/UIWnd.h"
#include "Misc/tagEffMgrData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern int dword_DE8DE8;
extern int dword_DE8DEC;
extern int dword_DE8DF0;
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
  PAL3 *Instance_db10; // eax
  DWORD Time; // eax
  _BYTE *v7; // edi
  unsigned int v8; // esi
  long double v9; // st7
  long double v10; // st6
  float v11; // eax
  float v12; // eax
  float v13; // eax
  float v14; // eax
  _DWORD *v15; // esi
  int result; // eax
  int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // eax
  double v20; // st7
  unsigned int v21; // eax
  unsigned int v22; // edx
  double v23; // st7
  _DWORD *v24; // edi
  float v25; // ebp
  int *v26; // esi
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
  unsigned int i; // [esp+D4h] [ebp-0x168] BYREF
  float v40; // [esp+D8h] [ebp-0x164]
  float j; // [esp+DCh] [ebp-0x160]
  float v42; // [esp+E0h] [ebp-0x15C]
  _BYTE *v43; // [esp+E4h] [ebp-0x158] BYREF
  float v44; // [esp+E8h] [ebp-0x154]
  float v45; // [esp+ECh] [ebp-0x150]
  RenderTarget2 *v46; // [esp+F0h] [ebp-0x14C]
  __int64 v47; // [esp+F4h] [ebp-0x148]
  _DWORD v48[2]; // [esp+FCh] [ebp-0x140] BYREF
  __int64 v49; // [esp+0x104] [ebp-0x138]
  _DWORD v50[76]; // [esp+0x10C] [ebp-0x130] BYREF
*(_DWORD *)&this->_tail_000[16] = 0;
  v2 = gfxMgr;
  xy = gfxMgr[1].InvViewMatrix.xy;
(*(void ( **)(float, _DWORD *))(*(_DWORD *)LODWORD(xy) + 28))(_pal3_coerce_f32(LODWORD(xy)), (_DWORD *)(v50));
  if ( (v50[36] & 0x200000) == 0 )
    *(_DWORD *)&this->_tail_000[16] = 1;
  if ( v2[1].DrvInfo.winname[76] )
    pVertPoolMgr = (gbVertPoolMgr *)(*(gbVertPoolMgr **)&v2[1].DrvInfo.winname[88]);
  else
    pVertPoolMgr = (gbVertPoolMgr *)v2[1].pVertPoolMgr;
  if ( (*(int ( **)(_DWORD, _DWORD, _DWORD, int, _DWORD, int, int))(**(_DWORD **)&v2[1].InvViewMatrix
                                                                                      + 40))(
         *(_DWORD *)&v2[1].InvViewMatrix,
         v50[1],
         v50[0],
         pVertPoolMgr->StaticPool[0].m_numNode,
         0,
         3,
         60) < 0 )
    *(_DWORD *)&this->_tail_000[16] = 1;
  v44 = 1.0f;
  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(1);
  if ( !LODWORD(PAL3::GetInstance_db10()->m_snaph) )
    v44 = 0.75f;
  if ( *(_DWORD *)&this->_tail_000[16] )
    goto LABEL_22;
  if ( (*(int ( **)(_DWORD, int, int, int, _DWORD, int, int, _BYTE *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy)
                                                                                      + 92))(
         LODWORD(v2[1].InvViewMatrix.xy),
         256,
         256,
         1,
         0,
         60,
         1,
         &this->_tail_000[12],
         0) >= 0 )
  {
    (*(void ( **)(_DWORD, _DWORD, _DWORD *, _DWORD, _DWORD))(**(_DWORD **)&this->_tail_000[12] + 76))(
      *(_DWORD *)&this->_tail_000[12],
      0,
      (_DWORD *)(v48),
      0,
      0);
    v43 = (_BYTE *)v48[1];
    Time = timeGetTime();
    CRT_set_new_handler(Time);
    for ( i = 0; i < 0x100; ++i )
    {
      v49 = i;
      v7 = (_BYTE *)v43;
      v8 = 0;
      v45 = (float)i * 0.00390625f - 0.5f;
      do
      {
        v47 = v8;
        j = (v45 + (float)v8 * 0.00390625f - 0.5f) * 12.566370964050293f;
        v42 = (float)(rand() % 16) + cos(j) * 48.0f;
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
    (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)&this->_tail_000[12] + 80))(*(_DWORD *)&this->_tail_000[12], 0);
    v11 = v2[1].InvViewMatrix.xy;
    v40 = 0.009999999776482582f;
    (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(v11) + 268))(
      _pal3_coerce_f32(LODWORD(v11)),
      0,
      7,
      1008981770);
    v12 = v2[1].InvViewMatrix.xy;
    v40 = 0.0f;
    (*(void ( **)(float, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v12) + 268))(
      _pal3_coerce_f32(LODWORD(v12)),
      0,
      8,
      0);
    v13 = v2[1].InvViewMatrix.xy;
    v40 = 0.0f;
    (*(void ( **)(float, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v13) + 268))(
      _pal3_coerce_f32(LODWORD(v13)),
      0,
      9,
      0);
    v14 = v2[1].InvViewMatrix.xy;
    v40 = 0.009999999776482582f;
    (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(v14) + 268))(
      _pal3_coerce_f32(LODWORD(v14)),
      0,
      10,
      1008981770);
    v1 = (RenderTarget2 *)v46;
  }
  else
  {
    *(_DWORD *)&this->_tail_000[16] = 1;
  }
  if ( *(_DWORD *)&this->_tail_000[16] )
  {
LABEL_22:
    v24 = (_DWORD *)&this->_tail_000[8];
    result = (*(int ( **)(_DWORD, int, int, int, int, _BYTE *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy)
                                                                               + 104))(
               LODWORD(v2[1].InvViewMatrix.xy),
               2800,
               8,
               514,
               1,
               &this->_tail_000[8],
               0);
    if ( result >= 0 )
    {
      v25 = v2[1].InvViewMatrix.xy;
      v26 = (int *)&this->_tail_000[4];
      v27 = *(_DWORD *)LODWORD(v25);
      v45 = *(float *)&v26;
      result = (*(int ( **)(float, int, int, int, _DWORD, int *, _DWORD))(v27 + 108))(
                 _pal3_coerce_f32(LODWORD(v25)),
                 1200,
                 512,
                 101,
                 0,
                 v26,
                 0);
      if ( result >= 0 )
      {
        v28 = (unsigned long)*v24;
        v43 = 0;
        result = (*(int ( **)(int, _DWORD, _DWORD, _BYTE **, _DWORD))(*(_DWORD *)v28 + 44))(v28, 0, 0, &v43, 0);
        if ( result >= 0 )
        {
          v29 = -1.0;
          v30 = 0.0;
          v42 = -1.0f;
          j = v44;
          v31 = 0;
          v40 = v44 * 0.10000000149011612f;
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
            v42 = v42 + 0.2222222238779068f;
            v29 = -1.0;
            v30 = 0.0;
            j = j - v40;
          }
          while ( v31 < 2800 );
          (*(void ( **)(_DWORD))(*(_DWORD *)*v24 + 48))(*v24);
          v34 = (unsigned long)*v26;
          i = 0;
          result = (*(int ( **)(int, _DWORD, _DWORD, unsigned int *, int))(*(_DWORD *)v34 + 44))(
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
            return (*(int ( **)(_DWORD))(**(_DWORD **)LODWORD(v45) + 48))(*(_DWORD *)LODWORD(v45));
          }
        }
      }
    }
  }
  else
  {
    v15 = (_DWORD *)&this->_tail_000[8];
    result = (*(int ( **)(_DWORD, int, int, int, int, _DWORD *, _DWORD))(*(_DWORD *)LODWORD(v2[1].InvViewMatrix.xy)
                                                                                + 104))(
               LODWORD(v2[1].InvViewMatrix.xy),
               112,
               8,
               514,
               1,
               v15,
               0);
    if ( result >= 0 )
    {
      v17 = (unsigned long)*v15;
      i = 0;
      result = (*(int ( **)(int, _DWORD, _DWORD, unsigned int *, _DWORD))(*(_DWORD *)v17 + 44))(
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
        return (*(int ( **)(_DWORD))(*(_DWORD *)*v15 + 48))(*v15);
      }
    }
  }
  return result;
}

// 0x004BFD70
void * RenderTarget2::Begin()
{
  PAL3 *Instance_db10; // eax
  PAL3 *v3; // eax
  void *result; // eax

  if ( this->_tail_000[0] )
  {
    Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
    (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(2);
    v3 = (PAL3 *)PAL3::GetInstance_db10();
    LOBYTE(result) = (((RenderTarget *)v3))->RenderTarget::OnResetDevice(0);
    if ( (_BYTE)result )
      return (void *)(*(int ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                                         + 172))(
                       LODWORD(gfxMgr[1].InvViewMatrix.xy),
                       0,
                       0,
                       3,
                       -16777216,
                       1065353216,
                       0);
    else
      this->_tail_000[0] = 0;
  }
  return result;
}

// 0x004BFDD0
void RenderTarget2::Resolve()
{
  PAL3 *Instance_db10; // eax
  gbGfxManager *v3; // esi
  int v4; // eax
  PAL3 *v5; // eax
  gbTexture *ActiveTexture; // eax
  gbTexture *v7; // ebp
  _BYTE v8[4]; // [esp+0x120] [ebp-0x10] BYREF
  int v9; // [esp+0x12C] [ebp-0x4]

  if ( this->_tail_000[0] )
  {
    Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
    (((RenderTarget *)Instance_db10))->RenderTarget::RenderToScreen();
    v3 = gfxMgr;
    PushMatrixStacks(v8);
    v4 = *(_DWORD *)*(void**)(v3);
    v9 = 0;
    (*(void ( **)(gbGfxManager *))(v4 + 60))(v3);
    v5 = (PAL3 *)PAL3::GetInstance_db10();
    ActiveTexture = (((RenderTarget *)v5))->RenderTarget::GetActiveTexture();
    v7 = (gbTexture *)ActiveTexture;
    if ( ActiveTexture && *(_DWORD *)((gbRefObject *)&ActiveTexture[1]) && *(_DWORD *)&this->_tail_000[8] )
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
      if ( *(_DWORD *)&this->_tail_000[16] )
      {
        (*(void ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 260))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          *(_DWORD *)((gbRefObject *)&v7[1]));
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
          *(_DWORD *)&this->_tail_000[8],
          0,
          28);
        (*(void ( **)(_DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 416))(
          LODWORD(v3[1].InvViewMatrix.xy),
          *(_DWORD *)&this->_tail_000[4]);
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
        (*(void ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 260))(
          LODWORD(v3[1].InvViewMatrix.xy),
          0,
          *(_DWORD *)&this->_tail_000[12]);
        (*(void ( **)(_DWORD, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 260))(
          LODWORD(v3[1].InvViewMatrix.xy),
          1,
          *(_DWORD *)((gbRefObject *)&v7[1]));
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
          *(_DWORD *)&this->_tail_000[8],
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
      (((gbGfxManager_D3D *)gfxMgr))->gbGfxManager_D3D::SetTexture(0);
      (((gbRenderEffect *)gfxMgr->pEffectMgr->m_pDefEffect))->gbRenderEffect::Apply();
    }
    v9 = -1;
    PopMatrixStacks(v8);
  }
}

// 0x004C0200
void RenderTarget2::Update(float fVal)
{
  int v3; // eax
  float v4; // st7
  int v5; // eax
  double v6; // st7
  float v7; // st6
  float v8; // eax
  int v9; // eax
  int v10; // ecx
  long double v11; // st5
  long double v12; // st5
  double v13; // st4
  float v14; // [esp+0x14] [ebp-0x10]
  int v15; // [esp+0x14] [ebp-0x10]
  float v16; // [esp+0x18] [ebp-0xC]
  int v17; // [esp+0x1C] [ebp-0x8]
  float v18; // [esp+0x1C] [ebp-0x8]
  float v19; // [esp+0x20] [ebp-0x4]

  if ( this->_tail_000[0] )
  {
    v3 = *(_DWORD *)&this->_tail_000[8];
    if ( v3 )
    {
      v4 = fVal * 0.4000000059604645f;
      fVal = 0.0f;
      *(float *)&this->_tail_000[20] = v4 + *(float *)&this->_tail_000[20];
      if ( (*(int ( **)(int, _DWORD, _DWORD, float *, _DWORD))(*(_DWORD *)v3 + 44))(v3, 0, 0, &fVal, 0) >= 0 )
      {
        v5 = *(_DWORD *)&this->_tail_000[16];
        if ( v5 )
        {
          if ( v5 == 1 )
          {
            v14 = 1.0f;
            if ( !LODWORD(PAL3::GetInstance_db10()->m_snaph) )
              v14 = 0.75f;
            v6 = 0.0;
            v7 = v14 * 0.10000000149011612f;
            v8 = v14;
            v15 = 0;
            v16 = v8;
            v9 = 0;
            do
            {
              v10 = 0;
              v17 = 0;
              do
              {
                ++v10;
                v9 += 28;
                v6 = v6 + 0.1;
                v11 = ((double)v17 * 0.1 - 0.5 + (double)v15 * 0.1 - 0.5) * 12.566371
                    + *(float *)&this->_tail_000[20] * 4.0;
                v18 = cos(v11) * 0.009999999776482582f;
                v12 = sin(v11) * 0.0099999998;
                *(float *)(v9 + LODWORD(fVal) - 16) = (v12 + v18) * 0.5 + v6;
                v13 = v18 + v16;
                v17 = v10;
                *(float *)(v9 + LODWORD(fVal) - 12) = v13 - v12;
              }
              while ( v10 < 10 );
              v6 = 0.0;
              ++v15;
              v19 = v7;
              v16 = v16 - v19;
            }
            while ( v9 < 2800 );
          }
          (*(void ( **)(_DWORD))(**(_DWORD **)&this->_tail_000[8] + 48))(*(_DWORD *)&this->_tail_000[8]);
        }
        else
        {
          if ( *(float *)&this->_tail_000[20] > 2.0f )
            *(float *)&this->_tail_000[20] = *(float *)&this->_tail_000[20] - 2.0;
          *(_DWORD *)(LODWORD(fVal) + 12) = 0;
          *(float *)(LODWORD(fVal) + 16) = *(float *)&this->_tail_000[20] * 0.5 + 1.0;
          *(_DWORD *)(LODWORD(fVal) + 40) = 0;
          *(float *)(LODWORD(fVal) + 44) = *(float *)&this->_tail_000[20] * 0.5;
          *(_DWORD *)(LODWORD(fVal) + 68) = 1065353216;
          *(float *)(LODWORD(fVal) + 72) = *(float *)&this->_tail_000[20] * 0.5;
          *(_DWORD *)(LODWORD(fVal) + 96) = 1065353216;
          *(float *)(LODWORD(fVal) + 100) = *(float *)&this->_tail_000[20] * 0.5 + 1.0;
          (*(void ( **)(_DWORD))(**(_DWORD **)&this->_tail_000[8] + 48))(*(_DWORD *)&this->_tail_000[8]);
        }
      }
    }
  }
}

// 0x004C04C0
CEffBase ** RenderTarget2::ClearTarget()
{
  CEffBase **result; // eax

  result = (CEffBase **)this;
  *(_DWORD *)&this->_tail_000[4] = 0;
  this->_tail_000[8] = 0;
  *(_DWORD *)&this->_tail_000[16] = 0;
  *(_DWORD *)&this->_tail_000[20] = 0;
  *(_DWORD *)&this->_tail_000[24] = 0;
  *(_DWORD *)&this->_tail_000[28] = -1;
  *(_DWORD *)&this->_tail_000[32] = -1;
  *(_DWORD *)&this->_tail_000[36] = 0;
  *(_DWORD *)&this->_tail_000[40] = 0;
  *(_DWORD *)&this->_tail_000[44] = 0;
  return result;
}

// 0x004C0560
int RenderTarget2::ExecutePasses()
{
  _BYTE *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->_tail_000[12] : 0;
  if ( *((_DWORD *)v1 + 7) || (result = *(this != 0 ? (_DWORD *)&this->_tail_000[44] : (_DWORD *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? (int *)&this->_tail_000[40] : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + *((_DWORD *)v1 + 3)));
        ++v3;
        *(_DWORD *)(v4 + *((_DWORD *)v1 + 3)) = 0;
        v4 += 152;
      }
      while ( v3 < *((_DWORD *)v1 + 7) );
    }
    operator delete(*((void **)v1 + 3));
    result = 0;
    *((_DWORD *)v1 + 3) = 0;
    *((_DWORD *)v1 + 7) = 0;
    *((_DWORD *)v1 + 8) = 0;
  }
  return result;
}

// 0x004C0C10
int RenderTarget2::SceneRoleCallback(int nParam)
{
  int v2; // ebx
  int v3; // edi
  float *v4; // ecx
  float v5; // st7
  float v6; // st7
  float *v7; // eax
  float *v8; // eax
  float v9; // st7
  float v10; // st7
  float v11; // edx
  float v12; // st7
  float v13; // st6
  float *v14; // eax
  float v15; // st7
  float v16; // st7
  int v17; // eax
  int v18; // edx
  float v20; // [esp+0x10] [ebp-0x34]
  float v21; // [esp+0x10] [ebp-0x34]
  float v22; // [esp+0x10] [ebp-0x34]
  float v23; // [esp+0x14] [ebp-0x30]
  float v24; // [esp+0x14] [ebp-0x30]
  float v25; // [esp+0x14] [ebp-0x30]
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
  float *v38; // [esp+0x40] [ebp-0x4]

  v2 = *(_DWORD *)&this->_tail_000[24] + 152 * *(_DWORD *)&this->_tail_000[28];
  v38 = (float *)(*(_DWORD *)v2 + 72 * *(_DWORD *)&this->_tail_000[32]);
  v3 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->_tail_000[4] + 4) + 20);
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  v34 = (int)*(float *)(v2 + 108);
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  pParam = (int)*(float *)(v2 + 24);
  v4 = (float *)v38;
  v5 = *(float *)&this->_tail_000[16];
  *(_DWORD *)&this->_tail_000[48] = v34;
  v6 = v5 - v38[4];
  fVal = *(float *)&this->_tail_000[20];
  if ( v6 > v38[6] )
    fVal = fVal - (v6 - v38[6]);
  if ( (g_nRenderTarget2State_DE8E24 & 1) == 0 )
  {
    g_nRenderTarget2_DE8E18 = 0.0;
    LOBYTE(g_nRenderTarget2State_DE8E24) = g_nRenderTarget2State_DE8E24 | 1;
    g_nRenderTarget2_DE8E1C = 0.0;
    g_nRenderTarget2_DE8E20 = 0.0;
    atexit(nullsub_15);
    v4 = (float *)v38;
  }
  if ( (g_nRenderTarget2State_DE8E24 & 2) == 0 )
  {
    LOBYTE(g_nRenderTarget2State_DE8E24) = g_nRenderTarget2State_DE8E24 | 2;
    g_nRenderTarget2_DE8E08 = 0.0;
    g_nRenderTarget2_DE8E0C = 0.0;
    g_nRenderTarget2_DE8E10 = 0.0;
    atexit(nullsub_14);
    v4 = (float *)v38;
  }
  v7 = (float *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6584);
  g_nRenderTarget2_DE8E18 = *v7;
  g_nRenderTarget2_DE8E1C = v7[1];
  g_nRenderTarget2_DE8E20 = v7[2];
  v8 = (float *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6584);
  g_nRenderTarget2_DE8E08 = *v8;
  g_nRenderTarget2_DE8E0C = v8[1];
  g_nRenderTarget2_DE8E10 = v8[2];
  if ( !*((_BYTE *)v4 + 65) )
  {
    if ( v34 <= 0xA )
    {
      *(_BYTE *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 380) = 1;
      (((CCBStage *)*(CCBStage **)(v3 + 4 * v34 + 24)))->CCBStage::SetParam(pParam, 1);
      if ( *(int *)(v2 + 104) <= 0 )
        (((CCBStage *)*(CCBStage **)(v3 + 4 * v34 + 24)))->CCBStage::ClearBadPushTask(0.0099999998);
      else
        (((CCBStage *)*(CCBStage **)(v3 + 4 * v34 + 24)))->CCBStage::ClearBadPushTask(0.25);
      if ( *(float *)(v2 + 92) > 0.0f )
      {
        v38[11] = g_nRenderTarget2_DE8E08;
        v38[12] = g_nRenderTarget2_DE8E0C;
        v38[13] = g_nRenderTarget2_DE8E10;
      }
      v4 = (float *)v38;
    }
    *((_BYTE *)v4 + 65) = 1;
  }
  if ( v34 <= 0xA )
  {
    if ( *(float *)(v2 + 92) > 0.0f )
    {
      v10 = *(float *)&this->_tail_000[16] - v4[4];
      if ( v4[6] - v10 > 0.0 )
      {
        v12 = v10 / v4[6];
        v30 = v4[11];
        v31 = v4[12];
        v32 = v4[13];
        v20 = *(float *)(v2 + 68) - v31;
        v23 = *(float *)(v2 + 72) - v32;
        v26 = (*(float *)(v2 + 64) - v30) * v12;
        v28 = v20 * v12;
        v21 = v28 + v31;
        v13 = v12 * v23;
        v9 = v26 + v30;
        g_nRenderTarget2_DE8E0C = v21;
        v24 = v13 + v32;
        v11 = v24;
        g_nRenderTarget2_DE8E08 = v9;
      }
      else
      {
        v9 = *(float *)(v2 + 64);
        g_nRenderTarget2_DE8E08 = *(float *)(v2 + 64);
        g_nRenderTarget2_DE8E0C = *(float *)(v2 + 68);
        v11 = *(float *)(v2 + 72);
      }
      g_nRenderTarget2_DE8E10 = v11;
    }
    else
    {
      v27 = *(float *)(v2 + 32) * fVal;
      v29 = *(float *)(v2 + 36) * fVal;
      v9 = *(float *)(v2 + 28) * fVal + g_nRenderTarget2_DE8E08;
      g_nRenderTarget2_DE8E08 = v9;
      g_nRenderTarget2_DE8E0C = v27 + g_nRenderTarget2_DE8E0C;
      g_nRenderTarget2_DE8E10 = v29 + g_nRenderTarget2_DE8E10;
    }
    v14 = (float *)*(float **)(v3 + 4 * v34 + 24);
    v14[1646] = v9;
    v14 += 1646;
    v14[1] = g_nRenderTarget2_DE8E0C;
    v14[2] = g_nRenderTarget2_DE8E10;
    if ( *(_BYTE *)(v2 + 113) )
    {
      if ( (g_nRenderTarget2State_DE8E24 & 4) == 0 )
      {
        g_nRenderTarget2_DE8DF8 = 0.0;
        LOBYTE(g_nRenderTarget2State_DE8E24) = g_nRenderTarget2State_DE8E24 | 4;
        g_nRenderTarget2_DE8DFC = 0.0;
        g_nRenderTarget2_DE8E00 = 0.0;
        atexit(nullsub_13);
        v4 = (float *)v38;
      }
      if ( g_nRenderTarget2_DE8E18 != g_nRenderTarget2_DE8E08
        || g_nRenderTarget2_DE8E1C != g_nRenderTarget2_DE8E0C
        || g_nRenderTarget2_DE8E20 != g_nRenderTarget2_DE8E10 )
      {
        v22 = g_nRenderTarget2_DE8E0C - g_nRenderTarget2_DE8E1C;
        g_nRenderTarget2_DE8DFC = v22;
        v25 = g_nRenderTarget2_DE8E10 - g_nRenderTarget2_DE8E20;
        g_nRenderTarget2_DE8DF8 = g_nRenderTarget2_DE8E08 - g_nRenderTarget2_DE8E18;
        g_nRenderTarget2_DE8E00 = v25;
        (((gbVec3D *)&g_nRenderTarget2_DE8DF8))->gbVec3D::Normalize();
        if ( (g_nRenderTarget2State_DE8E24 & 8) == 0 )
        {
          LOBYTE(g_nRenderTarget2State_DE8E24) = g_nRenderTarget2State_DE8E24 | 8;
          dword_DE8DE8 = 0;
          dword_DE8DEC = 0;
          dword_DE8DF0 = 1065353216;
          atexit(nullsub_12);
        }
        v15 = acos(
                *(float *)&dword_DE8DF0 * g_nRenderTarget2_DE8E00
              + *(float *)&dword_DE8DEC * g_nRenderTarget2_DE8DFC
              + *(float *)&dword_DE8DE8 * g_nRenderTarget2_DE8DF8);
        if ( g_nRenderTarget2_DE8DF8 < 0.0f )
          v15 = 6.2831854820251465f - v15;
        v4 = (float *)v38;
        *(float *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6632) = v15 * 57.29578;
      }
    }
    if ( *(float *)(v2 + 80) != 0.0f )
    {
      fVala = fVal * *(float *)(v2 + 80) + (((CCBStage *)*(_DWORD *)(v3 + 4 * v34 + 24)))->CCBStage::PushBackAllTask();
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      if ( fVala <= 1.0f )
      {
        if ( fVala < 0.0f )
          fVala = 0.0f;
        (((CCBStage *)*(CCBStage **)(v3 + 4 * v34 + 24)))->CCBStage::ClearAniMsg(1, fVala);
      }
      else
      {
        (((CCBStage *)*(CCBStage **)(v3 + 4 * v34 + 24)))->CCBStage::ClearAniMsg(1, 1.0);
      }
      v4 = (float *)v38;
    }
    v16 = *(float *)(v2 + 88);
    v17 = *(_DWORD *)(v3 + 4 * v34 + 24);
    *(float *)(v17 + 384) = *(float *)(v2 + 84);
    *(float *)(v17 + 388) = v16;
    if ( *(_BYTE *)(v2 + 114) )
    {
      v18 = *(_DWORD *)(v3 + 4 * v34 + 24);
      if ( *(_DWORD *)(v18 + 6640) == *(_DWORD *)(v18 + 6644) )
      {
        if ( *(float *)(v2 + 116) > 0.0f )
          *(float *)(v18 + 6632) = *(float *)(v2 + 116);
        goto LABEL_56;
      }
    }
  }
  if ( *((_BYTE *)v4 + 66) == 1 || *(float *)&this->_tail_000[16] - v4[4] >= v4[6] )
  {
    if ( v34 > 0xA )
    {
LABEL_57:
      *((_DWORD *)v4 + 2) = 4;
      return 0;
    }
    if ( *(float *)(v2 + 116) > 0.0f )
      *(float *)(*(_DWORD *)(v3 + 4 * v34 + 24) + 6632) = *(float *)(v2 + 116);
LABEL_56:
    (((CCBStage *)*(CCBStage **)(v3 + 4 * v34 + 24)))->CCBStage::ClearBadPushTask(0.0099999998);
    v4 = (float *)v38;
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
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  v8 = *(_DWORD *)&this->_tail_000[32];
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_nRenderSceneSeq;
  if ( !g_nRenderSceneSeq || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_nRenderSceneSeq = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = (int *)(v13 + 7);
    *v15 = *p_DWORD;
    v15[1] = (unsigned long)p_DWORD[1];
    v15[2] = (unsigned long)p_DWORD[2];
    v15[3] = (unsigned long)p_DWORD[3];
  }
  ++*(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal + 4);
  return v9;
}

// 0x004C1550
void RenderTarget2::UpdateFrame(float a2)
{
  (((CEffAction *)&this[-1]._tail_000[4280]))->CEffAction::UpdateFrame(a2);
}

// 0x004C1560
char * RenderTarget2::vfunc_2(char a2)
{
  return (((CEffAction *)&this[-1]._tail_000[4280]))->CEffAction::_sdtor_call_dtor(a2);
}

// 0x004C1570
CEffAudio ** RenderTarget2::Reset()
{
  CEffAudio **result; // eax

  result = (CEffAudio **)this;
  *(_DWORD *)&this->_tail_000[4] = 0;
  this->_tail_000[8] = 0;
  *(_DWORD *)&this->_tail_000[16] = 0;
  *(_DWORD *)&this->_tail_000[20] = 0;
  *(_DWORD *)&this->_tail_000[24] = 0;
  *(_DWORD *)&this->_tail_000[28] = -1;
  *(_DWORD *)&this->_tail_000[32] = -1;
  *(_DWORD *)&this->_tail_000[36] = 0;
  *(_DWORD *)&this->_tail_000[40] = 0;
  *(_DWORD *)&this->_tail_000[44] = 0;
  return result;
}

// 0x004C15B0
CEffAudio ** RenderTarget2::CreateEffAudio()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x130u);
  if ( v1 )
    return (((RenderTarget2 *)v1))->RenderTarget2::Reset();
  else
    return 0;
}

// 0x004C1660
int RenderTarget2::DestroyEffBase()
{
  _BYTE *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->_tail_000[12] : 0;
  if ( *((_DWORD *)v1 + 7) || (result = *(this != 0 ? (_DWORD *)&this->_tail_000[44] : (_DWORD *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? (int *)&this->_tail_000[40] : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + *((_DWORD *)v1 + 3)));
        ++v3;
        *(_DWORD *)(v4 + *((_DWORD *)v1 + 3)) = 0;
        v4 += 152;
      }
      while ( v3 < *((_DWORD *)v1 + 7) );
    }
    operator delete(*((void **)v1 + 3));
    result = 0;
    *((_DWORD *)v1 + 3) = 0;
    *((_DWORD *)v1 + 7) = 0;
    *((_DWORD *)v1 + 8) = 0;
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

  if ( *pfVal != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)*pfVal);
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::PlaySoundStream(&this->_tail_000[176]);
  }
  if ( pfVal[2] != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)pfVal[2]);
    v4 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v4))->CScreenMode::PlaySoundStream(&this->_tail_000[176]);
  }
  if ( pfVal[8] != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)pfVal[8]);
    v5 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v5))->CScreenMode::PlaySoundStream(&this->_tail_000[176]);
  }
  if ( pfVal[11] != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)pfVal[11]);
    v6 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v6))->CScreenMode::PlaySoundStream(&this->_tail_000[176]);
  }
}

// 0x004C18D0
void RenderTarget2::CreateSoundTarget(int *p_DWORD)
{
  _BYTE *v2; // ebx
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
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v2 = (_BYTE *)&this->_tail_000[12];
  v3 = *(_DWORD *)&this->_tail_000[40];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)v2 + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 149) = 1;
    v8 = ++g_nSoundTargetSeq;
    if ( !g_nSoundTargetSeq || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nSoundTargetSeq = 1;
    }
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(*((_DWORD *)v2 + 3) + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)v2 + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)v2 + 6);
    if ( v4 != -1 )
    {
      v9 = *((_DWORD *)v2 + 8);
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *(int (CEffect::**)(int))v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nSoundTargetSeq;
        if ( !g_nSoundTargetSeq || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nSoundTargetSeq = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_22:
      v15 = *((_DWORD *)v2 + 8);
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
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
        *(int (CEffect::**)(int))v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nSoundTargetSeq;
        if ( !g_nSoundTargetSeq || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nSoundTargetSeq = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_31:
      (((RenderTarget2 *)v2))->RenderTarget2::RenderOverlay(v4, 0 /* TODO: pmf_to_u32((int (RenderTarget2::*)(int))RenderTarget2::ProcessSoundPass) */, 0, 0, p_DWORD[18], p_DWORD[19]);
      *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 16) = *((_DWORD *)v2 + 1);
    }
  }
}

// 0x004C1B00
int RenderTarget2::ProcessSoundPass(int nVal)
{
  int v3; // ebx
  int v4; // edi
  CScreenMode *Instance; // eax
  CScreenMode *v6; // eax
  CScreenMode *v7; // eax
  CScreenMode *v8; // eax

  v3 = *(_DWORD *)&this->_tail_000[24] + 152 * *(_DWORD *)&this->_tail_000[28];
  v4 = *(_DWORD *)v3 + 72 * *(_DWORD *)&this->_tail_000[32];
  if ( !*(_BYTE *)(v4 + 65) )
  {
    *(_BYTE *)(v4 + 65) = 1;
    *(_DWORD *)(v4 + 44) = 0;
    *(_DWORD *)(v4 + 48) = 0;
    *(_DWORD *)(v4 + 52) = 0;
    *(_DWORD *)(v4 + 56) = 0;
  }
  if ( *(float *)(v3 + 24) != 0.0f
    && !*(_DWORD *)(v4 + 44)
    && *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v3 + 28) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)*(float *)(v3 + 24));
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(&this->_tail_000[176], 1);
    *(_DWORD *)(v4 + 44) = 1;
  }
  if ( *(float *)(v3 + 32) != 0.0f
    && !*(_DWORD *)(v4 + 48)
    && *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v3 + 36) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)*(float *)(v3 + 32));
    v6 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v6))->CScreenMode::AudioSetPosition(&this->_tail_000[176], 1);
    *(_DWORD *)(v4 + 48) = 1;
  }
  if ( *(float *)(v3 + 56) != 0.0f
    && !*(_DWORD *)(v4 + 52)
    && *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v3 + 64) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)*(float *)(v3 + 56));
    v7 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v7))->CScreenMode::AudioSetPosition(&this->_tail_000[176], 1);
    *(_DWORD *)(v4 + 52) = 1;
  }
  if ( *(float *)(v3 + 68) != 0.0f
    && !*(_DWORD *)(v4 + 56)
    && *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v3 + 72) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[168], &this->_tail_000[48], (int)*(float *)(v3 + 68));
    v8 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v8))->CScreenMode::AudioSetPosition(&this->_tail_000[176], 1);
    *(_DWORD *)(v4 + 56) = 1;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004C1DD0
int * RenderTarget2::GetEffAudioTemplate(int nVal)
{
  int *result; // eax

  switch ( nVal )
  {
    case 0:
      result = (int *)&g_EffMgrData._tail_000[260];
      break;
    case 1:
      result = (int *)&g_EffMgrData._tail_000[248];
      break;
    case 2:
      result = (int *)&g_EffMgrData._tail_000[236];
      break;
    case 3:
      result = (int *)&g_EffMgrData._tail_000[224];
      break;
    case 4:
      result = (int *)&g_EffMgrData._tail_000[212];
      break;
    case 5:
      result = (int *)&g_EffMgrData._tail_000[200];
      break;
    case 6:
      result = (int *)&g_EffMgrData._tail_000[188];
      break;
    case 7:
      result = (int *)&g_EffMgrData._tail_000[176];
      break;
    case 9:
      result = (int *)&g_EffMgrData._tail_000[72];
      break;
    case 20:
      result = (int *)&g_pszEditorDesc;
      break;
    default:
      result = (int *)g_EffCylinderEditorData;
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
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  v8 = *(_DWORD *)&this->_tail_000[32];
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_nSoundTargetSeq;
  if ( !g_nSoundTargetSeq || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_nSoundTargetSeq = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = (int *)(v13 + 7);
    *v15 = *p_DWORD;
    v15[1] = (unsigned long)p_DWORD[1];
    v15[2] = (unsigned long)p_DWORD[2];
    v15[3] = (unsigned long)p_DWORD[3];
  }
  ++*(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal + 4);
  return v9;
}

// 0x004C1F70
RenderTarget2 * RenderTarget2::DestroyEffAudio(void *Block, char pData)
{
  int v4; // eax
  int v5; // ebx
  int v6; // edi

  v4 = *(_DWORD *)&this->_tail_000[28];
  if ( v4 || *(_DWORD *)&this->_tail_000[32] )
  {
    v5 = 0;
    if ( v4 > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(*(_DWORD *)&this->_tail_000[12] + v6));
        ++v5;
        *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + v6) = 0;
        v6 += 152;
      }
      while ( v5 < *(_DWORD *)&this->_tail_000[28] );
    }
    operator delete(*(void **)&this->_tail_000[12]);
    *(_DWORD *)&this->_tail_000[12] = 0;
    *(_DWORD *)&this->_tail_000[28] = 0;
    *(_DWORD *)&this->_tail_000[32] = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C2050
CEffBink ** RenderTarget2::ResetSurface()
{
  CEffBink **result; // eax

  result = (CEffBink **)this;
  *(_DWORD *)&this->_tail_000[4] = 0;
  this->_tail_000[8] = 0;
  *(_DWORD *)&this->_tail_000[16] = 0;
  *(_DWORD *)&this->_tail_000[20] = 0;
  *(_DWORD *)&this->_tail_000[24] = 0;
  *(_DWORD *)&this->_tail_000[28] = -1;
  *(_DWORD *)&this->_tail_000[32] = -1;
  *(_DWORD *)&this->_tail_000[36] = 0;
  *(_DWORD *)&this->_tail_000[40] = 0;
  *(_DWORD *)&this->_tail_000[44] = 0;
  return result;
}

// 0x004C2090
CEffBink ** RenderTarget2::CreateEffBink()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x130u);
  if ( v1 )
    return (((RenderTarget2 *)v1))->RenderTarget2::ResetSurface();
  else
    return 0;
}

// 0x004C20D0
int RenderTarget2::DestroyEffBink()
{
  _BYTE *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->_tail_000[12] : 0;
  if ( *((_DWORD *)v1 + 7) || (result = *(this != 0 ? (_DWORD *)&this->_tail_000[44] : (_DWORD *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? (int *)&this->_tail_000[40] : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + *((_DWORD *)v1 + 3)));
        ++v3;
        *(_DWORD *)(v4 + *((_DWORD *)v1 + 3)) = 0;
        v4 += 152;
      }
      while ( v3 < *((_DWORD *)v1 + 7) );
    }
    operator delete(*((void **)v1 + 3));
    result = 0;
    *((_DWORD *)v1 + 3) = 0;
    *((_DWORD *)v1 + 7) = 0;
    *((_DWORD *)v1 + 8) = 0;
  }
  return result;
}

// 0x004C2280
void RenderTarget2::CreateVideoTarget(int *p_DWORD)
{
  _BYTE *v2; // ebx
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
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v2 = (_BYTE *)&this->_tail_000[12];
  v3 = *(_DWORD *)&this->_tail_000[40];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)v2 + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 149) = 1;
    v8 = ++g_nVideoTargetSeq;
    if ( !g_nVideoTargetSeq || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nVideoTargetSeq = 1;
    }
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(*((_DWORD *)v2 + 3) + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)v2 + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)v2 + 6);
    if ( v4 != -1 )
    {
      v9 = *((_DWORD *)v2 + 8);
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *(int (CEffect::**)(int))v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nVideoTargetSeq;
        if ( !g_nVideoTargetSeq || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nVideoTargetSeq = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_22:
      v15 = *((_DWORD *)v2 + 8);
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
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
        *(int (CEffect::**)(int))v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nVideoTargetSeq;
        if ( !g_nVideoTargetSeq || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nVideoTargetSeq = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_31:
      (((CEffCylinder *)v2))->CEffCylinder::_todo_4C2620();
      *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 16) = *((_DWORD *)v2 + 1);
    }
  }
}

// 0x004C24B0
int RenderTarget2::ProcessVideoPass(int nVal)
{
  int v3; // ebx
  int v4; // edi

  v3 = *(_DWORD *)&this->_tail_000[24] + 152 * *(_DWORD *)&this->_tail_000[28];
  v4 = *(_DWORD *)v3 + 72 * *(_DWORD *)&this->_tail_000[32];
  if ( !*(_BYTE *)(v4 + 65) )
    *(_BYTE *)(v4 + 65) = 1;
  if ( *(float *)(v3 + 24) != 0.0f && *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v3 + 28) )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    sprintf(&this->_tail_000[176], (const char *)&g_EffMgrData._tail_000[272], &this->_tail_000[48], (int)*(float *)(v3 + 24));
    (((CScreenMode *)&g_ScreenMode))->CScreenMode::SetViewport(0, 0);
    (((CScreenMode *)&g_ScreenMode))->CScreenMode::CreateDevice((int)&this->_tail_000[176], g_todo_BFDA4C, 0, 0);
    (((CScreenMode *)&g_ScreenMode))->CScreenMode::PlayVideo(1);
    *(_DWORD *)(v4 + 8) = 4;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004C25C0
int * RenderTarget2::GetTargetAddress(int nVal)
{
  switch ( nVal )
  {
    case 0:
      return (int *)&g_EffMgrData._tail_000[284];
    case 1:
      return (int *)&g_EffMgrData._tail_000[296];
    case 9:
      return (int *)&g_EffMgrData._tail_000[72];
  }
  return (int *)g_EffCylinderEditorData;
}

// 0x004C2700
RenderTarget2 * RenderTarget2::BeginNextPass(void *Block, char pData)
{
  int v4; // eax
  int v5; // ebx
  int v6; // edi

  v4 = *(_DWORD *)&this->_tail_000[28];
  if ( v4 || *(_DWORD *)&this->_tail_000[32] )
  {
    v5 = 0;
    if ( v4 > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(*(_DWORD *)&this->_tail_000[12] + v6));
        ++v5;
        *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + v6) = 0;
        v6 += 152;
      }
      while ( v5 < *(_DWORD *)&this->_tail_000[28] );
    }
    operator delete(*(void **)&this->_tail_000[12]);
    *(_DWORD *)&this->_tail_000[12] = 0;
    *(_DWORD *)&this->_tail_000[28] = 0;
    *(_DWORD *)&this->_tail_000[32] = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C27C0
char * RenderTarget2::DestroyEffWithBink(char a2)
{
  char *result; // eax

  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // (((EffObjectPool *)&this[-1]._tail_000[4280]))->EffObjectPool::_scalar_dtor_20B0();
  return result;
}

// 0x004C27D0
void ** RenderTarget2::Deactivate()
{
  void **result; // eax

  result = (void **)this;
  *(_DWORD *)&this->_tail_000[4] = 0;
  this->_tail_000[8] = 0;
  *(_DWORD *)&this->_tail_000[16] = 0;
  *(_DWORD *)&this->_tail_000[20] = 0;
  *(_DWORD *)&this->_tail_000[24] = 0;
  *(_DWORD *)&this->_tail_000[28] = -1;
  *(_DWORD *)&this->_tail_000[32] = -1;
  *(_DWORD *)&this->_tail_000[36] = 0;
  *(_DWORD *)&this->_tail_000[40] = 0;
  *(_DWORD *)&this->_tail_000[44] = 0;
  *(_DWORD *)&this->_tail_000[48] = 0;
  *(_DWORD *)&this->_tail_000[52] = 0;
  *(_DWORD *)&this->_tail_000[56] = 0;
  *(_DWORD *)&this->_tail_000[60] = 0;
  return result;
}

// 0x004C2820
void ** RenderTarget2::CreateDeactivated()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x40u);
  if ( v1 )
    return (((RenderTarget2 *)v1))->RenderTarget2::Deactivate();
  else
    return 0;
}

// 0x004C2840
char RenderTarget2::do_always_noconv()
{
  return 1;
}

// 0x004C2890
int RenderTarget2::BeginMultiPass()
{
  _BYTE *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->_tail_000[12] : 0;
  if ( *((_DWORD *)v1 + 7) || (result = *(this != 0 ? (_DWORD *)&this->_tail_000[44] : (_DWORD *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? (int *)&this->_tail_000[40] : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + *((_DWORD *)v1 + 3)));
        ++v3;
        *(_DWORD *)(v4 + *((_DWORD *)v1 + 3)) = 0;
        v4 += 152;
      }
      while ( v3 < *((_DWORD *)v1 + 7) );
    }
    operator delete(*((void **)v1 + 3));
    result = 0;
    *((_DWORD *)v1 + 3) = 0;
    *((_DWORD *)v1 + 7) = 0;
    *((_DWORD *)v1 + 8) = 0;
  }
  return result;
}

// 0x004C2930
int RenderTarget2::InitTargetPos(float *pfVal, float fVal, float fVal2, float fVal3)
{
  int v5; // esi
  RenderTarget2 **v6; // edx
  int v7; // eax
  int result; // eax

  this->_tail_000[8] = 0;
  v5 = *(_DWORD *)&this->_tail_000[4];
  *(float *)&this->_tail_000[48] = fVal + pfVal[46];
  v6 = (RenderTarget2 **)(v5 + 2348);
  *(float *)&this->_tail_000[52] = fVal2 + pfVal[47];
  v7 = 0;
  *(float *)&this->_tail_000[56] = fVal3 + pfVal[48];
  while ( !*((_BYTE *)v6 - 4) || *v6 != this )
  {
    ++v7;
    v6 += 5;
    if ( v7 >= 2048 )
    {
      result = 0;
      *(_DWORD *)&this->_tail_000[60] = 0;
      return result;
    }
  }
  result = *(_DWORD *)(v5 + 4 * (5 * v7 + 585));
  *(_DWORD *)&this->_tail_000[60] = result;
  return result;
}

// 0x004C2BA0
void RenderTarget2::RenderFromParams(float *pfVal)
{
  if ( *pfVal != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    (((CEffect *)*(CEffect **)&this->_tail_000[4]))->CEffect::Render((int)*pfVal);
  }
  if ( pfVal[8] != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    (((CEffect *)*(CEffect **)&this->_tail_000[4]))->CEffect::Render((int)pfVal[8]);
  }
  if ( pfVal[5] != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    (((CEffect *)*(CEffect **)&this->_tail_000[4]))->CEffect::Render((int)pfVal[5]);
  }
  if ( pfVal[14] != 0.0f )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    (((CEffect *)*(CEffect **)&this->_tail_000[4]))->CEffect::Render((int)pfVal[14]);
  }
}

// 0x004C2D00
void RenderTarget2::CreateEffectTarget(int *p_DWORD)
{
  _BYTE *v2; // ebx
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
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v2 = (_BYTE *)&this->_tail_000[12];
  v3 = *(_DWORD *)&this->_tail_000[40];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)v2 + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 149) = 1;
    v8 = ++g_nEffectTargetSeq;
    if ( !g_nEffectTargetSeq || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nEffectTargetSeq = 1;
    }
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(*((_DWORD *)v2 + 3) + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)v2 + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)v2 + 6);
    if ( v4 != -1 )
    {
      v9 = *((_DWORD *)v2 + 8);
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *(int (CEffect::**)(int))v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nEffectTargetSeq;
        if ( !g_nEffectTargetSeq || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nEffectTargetSeq = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_22:
      v15 = *((_DWORD *)v2 + 8);
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
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
        *(int (CEffect::**)(int))v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nEffectTargetSeq;
        if ( !g_nEffectTargetSeq || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nEffectTargetSeq = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_31:
      (((RenderTarget2 *)v2))->RenderTarget2::RenderPostProcess(v4, 0 /* TODO: pmf_to_u32((int (CEffMgr::*)(int))CEffMgr::ProcessEffectPass) */, 0, 0, p_DWORD[18], p_DWORD[19]);
      *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 16) = *((_DWORD *)v2 + 1);
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
      result = (int *)&g_EffMgrData._tail_000[428];
      break;
    case 1:
      result = (int *)&g_EffMgrData._tail_000[420];
      break;
    case 2:
      result = (int *)&g_EffMgrData._tail_000[412];
      break;
    case 3:
      result = (int *)&g_EffMgrData._tail_000[404];
      break;
    case 4:
      result = (int *)&g_EffMgrData._tail_000[396];
      break;
    case 5:
      result = (int *)&g_EffMgrData._tail_000[388];
      break;
    case 6:
      result = (int *)&g_EffMgrData._tail_000[380];
      break;
    case 7:
      result = (int *)&g_EffMgrData._tail_000[372];
      break;
    case 9:
      result = (int *)&g_EffMgrData._tail_000[72];
      break;
    case 12:
      result = (int *)&g_EffMgrData._tail_000[364];
      break;
    case 13:
      result = (int *)&g_EffMgrData._tail_000[356];
      break;
    case 14:
      result = (int *)&g_EffMgrData._tail_000[348];
      break;
    case 15:
      result = (int *)&g_EffMgrData._tail_000[340];
      break;
    case 16:
      result = (int *)&g_EffMgrData._tail_000[332];
      break;
    case 17:
      result = (int *)&g_EffMgrData._tail_000[324];
      break;
    case 18:
      result = (int *)&g_EffMgrData._tail_000[316];
      break;
    case 19:
      result = (int *)&g_EffMgrData._tail_000[308];
      break;
    case 20:
      result = (int *)&g_pszEditorDesc;
      break;
    default:
      result = (int *)g_EffCylinderEditorData;
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
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  v8 = *(_DWORD *)&this->_tail_000[32];
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_nEffectTargetSeq;
  if ( !g_nEffectTargetSeq || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_nEffectTargetSeq = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = (int *)(v13 + 7);
    *v15 = *p_DWORD;
    v15[1] = (unsigned long)p_DWORD[1];
    v15[2] = (unsigned long)p_DWORD[2];
    v15[3] = (unsigned long)p_DWORD[3];
  }
  ++*(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal + 4);
  return v9;
}

// 0x004C3400
char * RenderTarget2::BeginMultiPassRender(char a2)
{
  char *result; // eax

  return result;
}

// 0x004C3450
CEffCallBack ** RenderTarget2::ResetTargetSlot()
{
  CEffCallBack **result; // eax

  result = (CEffCallBack **)this;
  *(_DWORD *)&this->_tail_000[4] = 0;
  this->_tail_000[8] = 0;
  *(_DWORD *)&this->_tail_000[16] = 0;
  *(_DWORD *)&this->_tail_000[20] = 0;
  *(_DWORD *)&this->_tail_000[24] = 0;
  *(_DWORD *)&this->_tail_000[28] = -1;
  *(_DWORD *)&this->_tail_000[32] = -1;
  *(_DWORD *)&this->_tail_000[36] = 0;
  *(_DWORD *)&this->_tail_000[40] = 0;
  *(_DWORD *)&this->_tail_000[44] = 0;
  return result;
}

// 0x004C3490
CEffCallBack ** RenderTarget2::CreateEffCallBack()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x30u);
  if ( v1 )
    return (((RenderTarget2 *)v1))->RenderTarget2::ResetTargetSlot();
  else
    return 0;
}

// 0x004C34D0
int RenderTarget2::DestroyEffCallBack()
{
  _BYTE *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? &this->_tail_000[12] : 0;
  if ( *((_DWORD *)v1 + 7) || (result = *(this != 0 ? (_DWORD *)&this->_tail_000[44] : (_DWORD *)32)) != 0 )
  {
    v3 = 0;
    if ( *(this != 0 ? (int *)&this->_tail_000[40] : (int *)28) > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(v4 + *((_DWORD *)v1 + 3)));
        ++v3;
        *(_DWORD *)(v4 + *((_DWORD *)v1 + 3)) = 0;
        v4 += 152;
      }
      while ( v3 < *((_DWORD *)v1 + 7) );
    }
    operator delete(*((void **)v1 + 3));
    result = 0;
    *((_DWORD *)v1 + 3) = 0;
    *((_DWORD *)v1 + 7) = 0;
    *((_DWORD *)v1 + 8) = 0;
  }
  return result;
}

// 0x004C3570
void RenderTarget2::UpdatePost(float fVal)
{
    RenderTarget2 *_this = this;
  float *v2; // esi
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

  v2 = (float *)&_this->_tail_000[12];
  v17 = _this;
  *(float *)&_this->_tail_000[20] = fVal - *(float *)&_this->_tail_000[16];
  *(float *)&_this->_tail_000[16] = fVal;
  if ( *(float *)&_this->_tail_000[20] > 0.0f )
  {
    v3 = 0;
    fVala = 0;
    if ( *(int *)&_this->_tail_000[40] > 0 )
    {
      while ( 1 )
      {
        v4 = (int *)(v3 + *((_DWORD *)v2 + 3));
        if ( *((_BYTE *)v4 + 148) )
        {
          if ( v4[3] == 3 )
          {
            v5 = 0;
            v16 = 0;
            if ( *((int *)v2 + 8) > 0 )
              break;
          }
        }
LABEL_33:
        v3 += 152;
        if ( ++fVala >= *((_DWORD *)v2 + 7) )
        {
          _this = v17;
          goto LABEL_35;
        }
      }
      v6 = 0;
      while ( 1 )
      {
        v7 = (unsigned long)*v4;
        if ( !*(_BYTE *)(v6 + *v4 + 64) || v6 > 0 && *(_DWORD *)(v6 + v7 - 64) == 2 )
          goto LABEL_33;
        switch ( *(_DWORD *)(v6 + v7 + 8) )
        {
          case 2:
            if ( v6 > 0 )
            {
              if ( *(float *)(v6 + v7 + 20) >= 0.0f )
              {
                if ( v2[1] - *(float *)(v6 + v7 - 56) > *(float *)(v6 + v7 + 20) )
                {
LABEL_25:
                  *(_DWORD *)(*(_DWORD *)(v3 + *((_DWORD *)v2 + 3)) + v6 + 8) = 3;
                  *(float *)(*(_DWORD *)(v3 + *((_DWORD *)v2 + 3)) + v6 + 16) = (unsigned long)v2[1];
                  *((_DWORD *)v2 + 4) = fVala;
                  *((_DWORD *)v2 + 5) = v16;
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
            *((_DWORD *)v2 + 5) = v5;
            *((_DWORD *)v2 + 4) = fVala;
LABEL_26:
            (*(void ( **)(float *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2 + 4))(
              v2,
              *(_DWORD *)(*v4 + v6),
              *(_DWORD *)(*v4 + v6 + 4),
              0);
            break;
          case 4:
            v8 = 0;
            v9 = (_DWORD *)(v3 + *((_DWORD *)v2 + 3));
            v10 = (unsigned long)v9[1];
            if ( v10 <= 0 )
            {
LABEL_17:
              v12 = (unsigned long)v4[1];
              v4[3] = 4;
              v13 = 9 * v12;
              LOBYTE(v12) = *((_BYTE *)v4 + 149);
              v4[5] = *(_DWORD *)(*v4 + 8 * v13 - 12);
              if ( (_BYTE)v12 == 1 )
              {
                v14 = 0;
                *(_BYTE *)(v3 + *((_DWORD *)v2 + 3) + 148) = 0;
                if ( *((int *)v2 + 8) > 0 )
                {
                  v15 = 0;
                  do
                  {
                    ++v14;
                    v15 += 72;
                    *(_BYTE *)(*(_DWORD *)(v3 + *((_DWORD *)v2 + 3)) + v15 - 8) = 0;
                  }
                  while ( v14 < *((_DWORD *)v2 + 8) );
                }
                *(_DWORD *)(v3 + *((_DWORD *)v2 + 3) + 4) = 0;
                --*((_DWORD *)v2 + 6);
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
        if ( ++v16 >= *((_DWORD *)v2 + 8) )
          goto LABEL_33;
      }
    }
LABEL_35:
    if ( *(int *)&_this->_tail_000[36] <= 0 )
      _this->_tail_000[8] = 1;
  }
}

// 0x004C3770
void RenderTarget2::CreateCameraTarget(int *p_DWORD)
{
  _BYTE *v2; // ebx
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
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v2 = (_BYTE *)&this->_tail_000[12];
  v3 = *(_DWORD *)&this->_tail_000[40];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)v2 + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 149) = 1;
    v8 = ++g_nCameraTargetSeq;
    if ( !g_nCameraTargetSeq || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nCameraTargetSeq = 1;
    }
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 20) = 0;
    if ( p_DWORD )
      qmemcpy((void *)(*((_DWORD *)v2 + 3) + v7 + 24), p_DWORD, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)v2 + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)v2 + 6);
    if ( v4 != -1 )
    {
      v9 = *((_DWORD *)v2 + 8);
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *(int (CEffect::**)(int))v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nCameraTargetSeq;
        if ( !g_nCameraTargetSeq || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nCameraTargetSeq = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_22:
      v15 = *((_DWORD *)v2 + 8);
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
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
        *(int (CEffect::**)(int))v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nCameraTargetSeq;
        if ( !g_nCameraTargetSeq || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nCameraTargetSeq = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_31:
      (((RenderTarget2 *)v2))->RenderTarget2::RenderFinal(v4, 0 /* TODO: pmf_to_u32((int (RenderTarget2::*)(int))RenderTarget2::ProcessCameraPass) */, 0, 0, p_DWORD[18], p_DWORD[19]);
      *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 16) = *((_DWORD *)v2 + 1);
    }
  }
}

// 0x004C39A0
int RenderTarget2::ProcessCameraPass(int nVal)
{
  int v3; // ebx
  int v4; // edi

  v3 = *(_DWORD *)&this->_tail_000[24] + 152 * *(_DWORD *)&this->_tail_000[28];
  v4 = *(_DWORD *)v3 + 72 * *(_DWORD *)&this->_tail_000[32];
  if ( !*(_BYTE *)(v4 + 65) )
  {
    (((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->_tail_000[4] + 4) + 20) + 16)))->CCBCamControl::AddTask();
    if ( *(float *)(v3 + 24) > 0.0f )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      (((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->_tail_000[4] + 4) + 20) + 16)))->CCBCamControl::ClearFinishedTask((int)*(float *)(v3 + 24));
    }
    *(_BYTE *)(v4 + 65) = 1;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 )
  {
    if ( *(float *)(v3 + 24) > 0.0f )
      (((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->_tail_000[4] + 4) + 20) + 16)))->CCBCamControl::AddTask();
    *(_DWORD *)(v4 + 8) = 4;
  }
  if ( *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004C3A90
int * RenderTarget2::GetTargetByType(int nVal)
{
  switch ( nVal )
  {
    case 0:
      return (int *)&g_EffMgrData._tail_000[460];
    case 9:
      return (int *)&g_EffMgrData._tail_000[72];
    case 20:
      return (int *)&g_pszEditorDesc;
  }
  return (int *)g_EffCylinderEditorData;
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
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  v8 = *(_DWORD *)&this->_tail_000[32];
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_nCameraTargetSeq;
  if ( !g_nCameraTargetSeq || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_nCameraTargetSeq = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = (int *)(v13 + 7);
    *v15 = *p_DWORD;
    v15[1] = (unsigned long)p_DWORD[1];
    v15[2] = (unsigned long)p_DWORD[2];
    v15[3] = (unsigned long)p_DWORD[3];
  }
  ++*(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + 152 * nVal + 4);
  return v9;
}

// 0x004C3C70
void RenderTarget2::sub_4C3C70()
{
  float v1; // [esp+0x4] [ebp+0x4]

  (((RenderTarget2 *)((char *)this - 12)))->RenderTarget2::UpdatePost(v1);
}

// 0x004C5740
int RenderTarget2::sub_4C5740(int a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi

  v3 = *(_DWORD *)&this->_tail_000[28];
  if ( v3 || *(_DWORD *)&this->_tail_000[32] )
  {
    v4 = 0;
    if ( v3 > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(*(_DWORD *)&this->_tail_000[12] + v5));
        ++v4;
        *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + v5) = 0;
        v5 += 152;
      }
      while ( v4 < *(_DWORD *)&this->_tail_000[28] );
    }
    operator delete(*(void **)&this->_tail_000[12]);
    *(_DWORD *)&this->_tail_000[12] = 0;
    *(_DWORD *)&this->_tail_000[28] = 0;
    *(_DWORD *)&this->_tail_000[32] = 0;
  }
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x004CEEC0
int RenderTarget2::AddCallbackEffect(
        
        RenderTarget2 *pTarget,
        int nVal,
        RenderTarget2 *pParam)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  RenderTarget2 *v8; // edi
  RenderTarget2 *v9; // eax
  CEffCallBack **v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // strcpy(v7 + 28, *(void**)(pTarget));
  v8 = (RenderTarget2 *)pParam;
  if ( !pParam )
    v8 = (RenderTarget2 *)unk_C10D38;
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (RenderTarget2 *)operator new(0x30u);
  if ( v9 )
    v10 = (((RenderTarget2 *)v9))->RenderTarget2::ResetTargetSlot();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = (unsigned long)v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pTarget);
  return v4;
}

// 0x004CF340
int RenderTarget2::AddGenericEffect(
        
        RenderTarget2 *pTarget,
        int nVal,
        RenderTarget2 *pParam)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  RenderTarget2 *v8; // edi
  RenderTarget2 *v9; // eax
  void **v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // strcpy(v7 + 28, *(void**)(pTarget));
  v8 = (RenderTarget2 *)pParam;
  if ( !pParam )
    v8 = (RenderTarget2 *)unk_C10D38;
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (RenderTarget2 *)operator new(0x40u);
  if ( v9 )
    v10 = (((RenderTarget2 *)v9))->RenderTarget2::Deactivate();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = (unsigned long)v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pTarget);
  return v4;
}

// 0x004CFA00
int RenderTarget2::AddBinkEffect(
        
        RenderTarget2 *pTarget,
        int nVal,
        RenderTarget2 *pParam)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  RenderTarget2 *v8; // edi
  RenderTarget2 *v9; // eax
  CEffBink **v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // strcpy(v7 + 28, *(void**)(pTarget));
  v8 = (RenderTarget2 *)pParam;
  if ( !pParam )
    v8 = (RenderTarget2 *)unk_C10D38;
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (RenderTarget2 *)operator new(0x130u);
  if ( v9 )
    v10 = (((RenderTarget2 *)v9))->RenderTarget2::ResetSurface();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = (unsigned long)v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pTarget);
  return v4;
}

// 0x004D05E0
int RenderTarget2::CameraInterpCallback(int nVal)
{
  float v3; // st7
  int v4; // edi
  int v5; // ecx
  float v6; // st7
  int v7; // ebp
  int v8; // ecx
  float v9; // st7
  gbVisNode *v10; // ecx
  float v11; // st7
  float v13; // [esp+0x4] [ebp-0x8C]
  float v14; // [esp+0x18] [ebp-0x78] BYREF
  float v15; // [esp+0x1C] [ebp-0x74]
  gbVec3D v16; // [esp+0x20] [ebp-0x70] BYREF
  struct gbVec3D v17; // [esp+0x2C] [ebp-0x64] BYREF
  float v18; // [esp+0x3C] [ebp-0x54]
  float v19; // [esp+0x40] [ebp-0x50]
  float v20; // [esp+0x48] [ebp-0x48]
  float v21; // [esp+0x4C] [ebp-0x44]
  gbMatrix4 v22; // [esp+0x50] [ebp-0x40] BYREF

  v3 = *(float *)&this->_tail_000[16];
  v4 = *(_DWORD *)&this->_tail_000[24] + 152 * *(_DWORD *)&this->_tail_000[28];
  v5 = 9 * *(_DWORD *)&this->_tail_000[32];
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  v15 = *(float *)&this->_tail_000[20];
  if ( v6 > *(float *)(v7 + 24) )
    v15 = v15 - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    v8 = *(_DWORD *)&this->_tail_000[48];
    this->_tail_000[88] = 1;
    if ( v8 )
      (*(void ( **)(int, _DWORD))(*(_DWORD *)v8 + 24))(v8, 0);
    *(_BYTE *)(v7 + 65) = 1;
  }
  v9 = *(float *)(v4 + 28);
  v18 = *(float *)(v4 + 32);
  v19 = *(float *)(v4 + 36);
  v20 = v18 * v15;
  v21 = v19 * v15;
  *(float *)&this->_tail_000[52] = v9 * v15 + *(float *)&this->_tail_000[52];
  *(float *)&this->_tail_000[56] = v20 + *(float *)&this->_tail_000[56];
  *(float *)&this->_tail_000[60] = v21 + *(float *)&this->_tail_000[60];
  *(float *)&this->_tail_000[92] = *(float *)(v4 + 24) + *(float *)&this->_tail_000[92];
  *(float *)&this->_tail_000[96] = *(float *)(v4 + 116) + *(float *)&this->_tail_000[96];
  *(float *)&this->_tail_000[100] = *(float *)(v4 + 108) + *(float *)&this->_tail_000[100];
  *(float *)&this->_tail_000[76] = *(float *)(v4 + 64) + *(float *)&this->_tail_000[76];
  *(float *)&this->_tail_000[80] = *(float *)(v4 + 68) + *(float *)&this->_tail_000[80];
  *(float *)&this->_tail_000[84] = *(float *)(v4 + 72) + *(float *)&this->_tail_000[84];
  memset(&v16, 0, sizeof(v16));
  memset(&v17, 0, sizeof(v17));
  (((gbMatrix4 *)&v22))->gbMatrix4::LoadIdentity();
  v16 = *(gbVec3D *)(v4 + 44);
  (((gbVec3D *)&v16))->gbVec3D::Normalize();
  v13 = (*(float *)&this->_tail_000[16] - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  (((gbMatrix4 *)&v22))->gbMatrix4::SetAxisAngle(&v16, v13);
  v17.z = *(float *)(v4 + 56);
  v17.x = 0.0;
  v17.y = 0.0;
  (((gbMatrix4 *)&v22))->gbMatrix4::Rotate(&v17, (gbVec3D *)&this->_tail_000[64]);
  if ( *(float *)(v4 + 80) != 0.0f )
  {
    v10 = (gbVisNode *)(*(gbVisNode **)&this->_tail_000[48]);
    v14 = 0.0f;
    // [overlay-fix 2026-10-27] 垃圾形条件——待语义修复
    // if ( (((gbVisNode *)v10))->gbVisNode::GetBlend(&v14) )
    if ( 0 )
      v11 = v15;
    else
      v11 = 1.0f;
    v15 = v16.x * *(float *)(v4 + 80) + v11;
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( v15 <= 1.0f )
    {
      if ( v15 < 0.0f )
        v15 = 0.0f;
    }
    else
    {
      v15 = 1.0f;
    }
    (((gbVisNode *)*(gbVisNode **)&this->_tail_000[48]))->gbVisNode::SetBlend(BLEND_ALPHA, v15);
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *(float *)&this->_tail_000[16] - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
    *(_DWORD *)(v7 + 8) = 4;
  return 0;
}
