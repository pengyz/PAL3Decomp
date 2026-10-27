#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/RenderTarget3.h"
#include "Misc/CPolicy.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/PAL3.h"
#include "Script/PalScript.h"
#include "Render/RenderTarget.h"
#include "free_functions.h"

// 0x004B63C0
int RenderTarget3::GenerateRingMesh(
        float fVal,
        float fVal2,
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        float fVal3)
{
  int result; // eax
  float v9; // st7
  int v10; // ecx
  float v11; // st6
  long double v12; // st6
  long double v13; // st6
  long double v14; // st5
  long double v15; // st5
  long double v16; // st5
  long double v17; // st4
  float v18; // st6
  float v19; // [esp+0x0] [ebp-0x8]
  int v20; // [esp+0x4] [ebp-0x4]
  float v21; // [esp+0x4] [ebp-0x4]
  float nVal2a; // [esp+0x18] [ebp+0x10]
  float nVal2b; // [esp+0x18] [ebp+0x10]
  float nVal2c; // [esp+0x18] [ebp+0x10]
  float nVal3a; // [esp+0x1C] [ebp+0x14]
  float fVal3a; // [esp+0x24] [ebp+0x1C]

  result = 0;
  v20 = 0;
  v19 = 6.2831854820251465f / (float)nVal2;
  fVal3a = 1.0f / fVal3;
  v9 = 0.0f;
  if ( nVal2 > 0 )
  {
    v10 = nVal3 + 4;
    do
    {
      v11 = (float)v20;
      ++result;
      v10 += 68;
      nVal3a = v11;
      v12 = v11 * v19;
      nVal2a = v12;
      v13 = cos(v12);
      *(float *)(v10 - 72) = fVal2 * v13;
      v14 = sin(nVal2a);
      v21 = v14;
      *(float *)(v10 - 64) = v14 * fVal2;
      *(_DWORD *)(v10 - 68) = 0;
      v15 = (nVal3a + 1.0) * v19;
      nVal2b = v15;
      v16 = cos(v15);
      *(float *)(v10 - 60) = fVal2 * v16;
      v17 = sin(nVal2b);
      nVal2c = v17;
      *(float *)(v10 - 52) = v17 * fVal2;
      *(_DWORD *)(v10 - 56) = 0;
      *(float *)(v10 - 48) = fVal * v16;
      *(float *)(v10 - 40) = nVal2c * fVal;
      *(_DWORD *)(v10 - 44) = nVal;
      *(float *)(v10 - 36) = fVal * v13;
      v18 = v21 * fVal;
      v20 = result;
      *(float *)(v10 - 28) = v18;
      *(_DWORD *)(v10 - 32) = nVal;
      *(float *)(v10 - 24) = v9;
      v9 = v9 + fVal3a;
      *(float *)(v10 - 16) = v9;
      *(_DWORD *)(v10 - 20) = 0;
      *(_DWORD *)(v10 - 12) = 1065353216;
      *(_DWORD *)(v10 - 8) = -1;
    }
    while ( result < nVal2 );
  }
  return result;
}

// 0x004B6550
int RenderTarget3::InitStruct()
{
  int result; // eax

  result = (int)this;
  *((_BYTE *)&this->m_ptr_4 + 8) = HIBYTE(this);
  *((_DWORD *)&this->m_ptr_4 + 3) = 0;
  *((_DWORD *)&this->m_ptr_4 + 4) = 0;
  *(_DWORD *)&this[1] = 0;
  *((_DWORD *)&this->m_ptr_4 + 1) = 12;
  return result;
}

// 0x004B65A0
RenderTarget3 * RenderTarget3::GetInstance()
{
  if ( (byte_DE6A4C & 1) == 0 )
  {
    LOBYTE(byte_DE6A4C) = byte_DE6A4C | 1;
    (((RenderTarget3 *)&dword_DE6A30))->RenderTarget3::InitStruct();
    atexit(InitRenderTarget3Singleton);
  }
  return (RenderTarget3 *)&dword_DE6A30;
}

// 0x004B65F0
char RenderTarget3::Init()
{
    RenderTarget3 *_this = this;
  gbEffectMgr *pEffectMgr; // edi

  pEffectMgr = gfxMgr->pEffectMgr;
  *(_DWORD *)_this = (((gbEffectMgr *)pEffectMgr))->gbEffectMgr::NewRenderEffect("gfxscript\\glow.gbf", 0);
  _this->m_ptr_4 = ((gbRenderEffect *)((((gbEffectMgr *)pEffectMgr))->gbEffectMgr::NewRenderEffect("gfxscript\\geom_glow.gbf", 1u)));
  return 1;
}

// 0x004B6630
int RenderTarget3::Begin()
{
  int result; // eax
  unsigned int i; // edi
  int v4; // eax
  int v5; // ecx
  unsigned int j; // edi
  int v7; // [esp+0x0] [ebp-0x8]
  int v8; // [esp+0x4] [ebp-0x4]

  LOBYTE(result) = this->RenderTarget3::ResetAndRender(v7, v8);
  if ( (_BYTE)result )
  {
    for ( i = 0; ; ++i )
    {
      v4 = *((_DWORD *)&this->m_ptr_4 + 3);
      if ( !v4 || i >= (*((_DWORD *)&this->m_ptr_4 + 4) - v4) >> 2 )
        break;
      (((gbRenderEffect *)this->m_ptr_4))->gbRenderEffect::SetVariant((GBPARAMHANDLE)(GBPARAM_TEXTURE1|GBPARAM_PROJMATRIX), (void *)(*(_DWORD *)(v4 + 4 * i) + 16));
      v5 = *(_DWORD *)(*((_DWORD *)&this->m_ptr_4 + 3) + 4 * i);
      (*(void ( **)(int, gbRenderEffect *))(*(_DWORD *)v5 + 4))(v5, this->m_ptr_4);
    }
    this->RenderTarget3::EndSceneGraph();
    for ( j = 0; ; ++j )
    {
      result = *((_DWORD *)&this->m_ptr_4 + 3);
      if ( !result || j >= (*((_DWORD *)&this->m_ptr_4 + 4) - result) >> 2 )
        break;
      this->RenderTarget3::UpdateRender(*(_DWORD *)(result + 4 * j));
    }
  }
  return result;
}

// 0x004B66B0
bool RenderTarget3::ResetAndRender(int nVal, int nVal2)
{
  int v3; // edi
  int v4; // esi
  PAL3 *Instance_db10; // eax
  PAL3 *v6; // eax
  bool result; // al
  gbGfxManager *v8; // edi
  int v9; // esi
  gbSceneGraph *pSceneGraph; // esi
  gbCamera *p_m_fMinDist; // eax
  float v12; // eax
  gbMatrixStack *v13; // esi
  int v14; // [esp+0x18] [ebp-0x14]
  int v15; // [esp+0x1C] [ebp-0x10]
  __int64 v16; // [esp+0x24] [ebp-0x8] BYREF
  float retaddr; // [esp+0x2C] [ebp+0x0]

  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(2);
  v6 = (PAL3 *)PAL3::GetInstance_db10();
  result = (((RenderTarget *)v6))->RenderTarget::OnResetDevice(0);
  if ( result )
  {
    v15 = v4;
    v14 = v3;
    v8 = gfxMgr;
    v9 = 1;
    if ( LODWORD(PAL3::GetInstance_db10()->m_snaph) != 2 )
      v9 = 3;
    (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD, int, int))(*(_DWORD *)LODWORD(v8[1].InvViewMatrix.xy)
                                                                                   + 172))(
      LODWORD(v8[1].InvViewMatrix.xy),
      0,
      0,
      v9,
      -16777216,
      1065353216,
      0,
      v14,
      v15);
    pSceneGraph = gfxMgr->pSceneGraph;
    if ( g_pCameraCtrl )
      p_m_fMinDist = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
    else
      p_m_fMinDist = 0;
    (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(p_m_fMinDist);
    LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
    v16 = *(_QWORD *)(&g_pCameraCtrl->m_vecLookAt + 1);
    v12 = *((float *)&g_pCameraCtrl->m_vecLookAt + 5);
    *(float *)&v16 = *(float *)&v16 * -1.5;
    *((float *)&v16 + 1) = *((float *)&v16 + 1) * -1.5;
    retaddr = v12 * -1.5f;
    v13 = gfxMgr->pMatrixStack[1];
    (((gbMatrixStack *)v13))->gbMatrixStack::Push();
    (((gbMatrixStack *)v13))->gbMatrixStack::Translate(*(gbVec3D *)&v16);
    return 1;
  }
  return result;
}

// 0x004B67B0
void RenderTarget3::EndSceneGraph()
{
  PAL3 *Instance_db10; // eax

  (((gbSceneGraph *)gfxMgr->pSceneGraph))->gbSceneGraph::End();
  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)Instance_db10))->RenderTarget::RenderToScreen();
  (((gbMatrixStack *)gfxMgr->pMatrixStack[1]))->gbMatrixStack::Pop();
}

// 0x004B67E0
int RenderTarget3::SwapBuffers()
{
  int result; // eax

  result = *((_DWORD *)&this->m_ptr_4 + 4);
  *((_DWORD *)&this->m_ptr_4 + 4) = *((_DWORD *)&this->m_ptr_4 + 3);
  return result;
}

// 0x004B6820
int RenderTarget3::UpdateRender(int nVal)
{
  void ( **v2)(int, float *); // eax
  float v3; // st7
  float v4; // st7
  float v5; // st6
  float width; // st5
  __int64 v7; // rax
  float v8; // st7
  float v9; // st6
  float v10; // st6
  float v11; // st6
  gbDynVertBuf *DynVertBuf; // eax
  int v13; // esi
  gbDynVertBuf *v14; // ebp
  int result; // eax
  int i; // edi
  PAL3 *Instance_db10; // eax
  float v18; // [esp+0x30] [ebp-C0h]
  int v19; // [esp+0x30] [ebp-C0h]
  float v20; // [esp+0x34] [ebp-BCh]
  float v21; // [esp+0x34] [ebp-BCh]
  float v22; // [esp+0x34] [ebp-BCh]
  int v23; // [esp+0x34] [ebp-BCh]
  float v24; // [esp+0x38] [ebp-B8h]
  float v25; // [esp+0x38] [ebp-B8h]
  float v26; // [esp+0x38] [ebp-B8h]
  int v27; // [esp+0x38] [ebp-B8h]
  float v28; // [esp+0x3C] [ebp-B4h]
  int v29; // [esp+0x3C] [ebp-B4h]
  float height; // [esp+0x40] [ebp-B0h]
  float v31; // [esp+0x40] [ebp-B0h]
  struct gbVec3D v32; // [esp+0x44] [ebp-ACh] BYREF
  float v33; // [esp+0x50] [ebp-A0h] BYREF
  float v34; // [esp+0x54] [ebp-0x9C]
  float v35; // [esp+0x58] [ebp-0x98]
  float v36; // [esp+0x5C] [ebp-0x94]
  float v37; // [esp+0x60] [ebp-0x90]
  float v38; // [esp+0x64] [ebp-0x8C]
  float v39; // [esp+0x68] [ebp-0x88] BYREF
  float v40; // [esp+0x6C] [ebp-0x84] BYREF
  float v41; // [esp+0x70] [ebp-0x80]
  float v42; // [esp+0x74] [ebp-0x7C]
  struct gbUIQuad v43; // [esp+0x78] [ebp-0x78] BYREF
  float v44; // [esp+A0h] [ebp-0x50] BYREF
  float v45; // [esp+A4h] [ebp-0x4C] BYREF
  RenderTarget3 *v46; // [esp+A8h] [ebp-0x48]
  struct gbTextureArray v47; // [esp+ACh] [ebp-0x44] BYREF
v2 = *(void ( ***)(int, float *))nVal;
  v33 = 0.0f;
  v34 = 0.0f;
  v35 = 0.0f;
  v36 = 0.0f;
  v37 = 0.0f;
  v38 = 0.0f;
  (*v2)(nVal, &v33);
  v43.color = -1;
  v43.z = 0.0;
  v18 = v36 + v33;
  v20 = v34 + v37;
  v24 = v35 + v38;
  v32.x = v18 * 0.5;
  v32.y = v20 * 0.5;
  v32.z = v24 * 0.5;
  (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::PointWorldToScr(&v32, &v39, &v40);
  v21 = v37 - v34;
  v25 = v38 - v35;
  v32.x = (v36 - v33) * 0.5;
  v32.y = v21 * 0.5;
  v32.z = v25 * 0.5;
  (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::PointWorldToScr(&v32, &v44, &v45);
  v3 = v39 - 0.20000000298023224f;
  v44 = 0.20000000298023224f;
  v45 = 0.30000001192092896f;
  v22 = v40 - 0.30000001192092896f;
  v26 = v39 + 0.20000000298023224f;
  v28 = v40 + 0.30000001192092896f;
  if ( v3 >= v26 )
    v43.sx = v39 + 0.2;
  else
    v43.sx = v3;
  if ( v3 <= v26 )
    v43.ex = v39 + 0.2;
  else
    v43.ex = v3;
  if ( v22 >= (double)v28 )
    v4 = v28;
  else
    v4 = v22;
  if ( v22 <= (double)v28 )
    v5 = v28;
  else
    v5 = v22;
  width = (float)g_DrvInfo.width;
  v19 = (__int64)((v43.sx + 1.0) * width * 0.5);
  v27 = (__int64)((v43.ex + 1.0) * width * 0.5);
  height = (float)g_DrvInfo.height;
  v23 = (__int64)((1.0 - v5) * height * 0.5);
  v7 = (__int64)((1.0 - v4) * height * 0.5);
  v8 = (float)v19;
  v29 = v7;
  v43.su = v8 * 0.00125;
  v9 = (float)(int)v7;
  v42 = v9;
  v43.sy = v42;
  v43.sv = v9 * 0.0016666667;
  v10 = (float)v27;
  v41 = v10;
  v43.ex = v41;
  v43.eu = v10 * 0.00125;
  v11 = (float)v23;
  v31 = v11;
  v43.ey = v31;
  v43.color = 1848125480;
  v43.ev = v11 * 0.0016666667;
  v43.sx = v8;
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
  v13 = *(_DWORD *)(nVal + 8);
  v14 = (gbDynVertBuf *)DynVertBuf;
  result = *(_DWORD *)(nVal + 12);
  for ( i = 0; i < result; v43.sy = (float)v29 )
  {
    Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
    v47.pTexPt[0] = (((RenderTarget *)Instance_db10))->RenderTarget::GetActiveTexture();
    v47.nTex = 1;
    (((gbDynVertBuf *)v14))->gbDynVertBuf::RenderUIQuad(&v43, 1, *(gbRenderEffect * *)this, &v47);
    v19 -= v13;
    HIBYTE(v43.color) -= 10;
    v43.sx = (float)v19;
    v23 -= v13;
    v27 += v13;
    result = *(_DWORD *)(nVal + 12);
    ++i;
    v43.ey = (float)v23;
    v29 += v13;
    v43.ex = (float)v27;
  }
  return result;
}

// 0x004B6C20
CPolicy ** RenderTarget3::ClearEffects()
{
  CPolicy **result; // eax
  gbRenderEffect **v2; // ecx

  result = (CPolicy **)this;
  *((_DWORD *)&this->m_ptr_4 + 1) = 6;
  *((_DWORD *)&this->m_ptr_4 + 2) = 6;
  v2 = (gbRenderEffect **)(&this->m_ptr_4 + 3);
  *v2 = (gbRenderEffect *)1065353216;
  *((_BYTE *)result + 4) = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = (gbRenderEffect *)1065353216;
  return result;
}

// 0x004B6CA0
void RenderTarget3::_nearby_4b6ca0(void **a2)
{
  ;
}

// 0x004B6D20
int * RenderTarget3::Reset()
{
    RenderTarget3 *_this = this;
  int *result; // eax

  result = (int *)_this;
  _this->m_ptr_4 = ((gbRenderEffect *)0);
  *(_BYTE *)_this = 0;
  return result;
}

// 0x004B6DF0
void * RenderTarget3::End()
{
  void *result; // eax

  if ( *(_BYTE *)this )
    return (void *)(*(int ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 228))(
                     LODWORD(gfxMgr[1].InvViewMatrix.xy),
                     168,
                     3);
  return result;
}

// 0x004B6E20
void RenderTarget3::Resolve()
{
  gbDynVertBuf *DynVertBuf; // eax
  gbRenderEffect *m_ptr_4; // esi
  int v4; // [esp+0x20] [ebp-0x7C] BYREF
  struct gbUIQuad v5; // [esp+0x24] [ebp-0x78] BYREF
  struct gbTextureArray v6; // [esp+0x4C] [ebp-0x50] BYREF
  int v7; // [esp+0x98] [ebp-0x4]

  if ( *(_BYTE *)this )
  {
    (*(void ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 228))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      168,
      7);
    if ( this->m_ptr_4 )
    {
      if ( unk_C11720.m_pActorData )
      {
        v5.z = 0.0;
        v5.color = -1;
        v5.sv = 0.0;
        v5.su = 0.0;
        v5.eu = 1.0;
        v5.ev = 1.0;
        v5.sx = -1.0;
        v5.ey = 1.0;
        v5.ex = 1.0;
        v5.sy = -1.0;
        PushMatrixStacks(&v4);
        v7 = 0;
        DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
        m_ptr_4 = (gbRenderEffect *)this->m_ptr_4;
        v6.nTex = 1;
        v6.pTexPt[0] = (gbTexture *)m_ptr_4;
        (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad(&v5, 1, unk_C11720.m_pActorData, &v6);
        v7 = -1;
        PopMatrixStacks(&v4);
      }
    }
  }
}
