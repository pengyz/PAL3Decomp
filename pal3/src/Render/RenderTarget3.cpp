#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/RenderTarget3.h"

// Forward declarations for unnamed functions
int sub_4B6C80(...);

// Unnamed globals (extern)
extern char byte_DE6A4C;
extern int dword_DE6A30;
extern PalScript stru_C11720;
void __cdecl unknown_libname_413(void);

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
  double v9; // st7
  int v10; // ecx
  double v11; // st6
  long double v12; // st6
  long double v13; // st6
  long double v14; // st5
  long double v15; // st5
  long double v16; // st5
  long double v17; // st4
  double v18; // st6
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
  v19 = 6.2831855 / (double)nVal2;
  fVal3a = 1.0 / fVal3;
  v9 = 0.0;
  if ( nVal2 > 0 )
  {
    v10 = nVal3 + 4;
    do
    {
      v11 = (double)v20;
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
int RenderTarget3::InitStruct(int nVal)
{
  *(_BYTE *)(nVal + 12) = HIBYTE(nVal);
  *(_DWORD *)(nVal + 16) = 0;
  *(_DWORD *)(nVal + 20) = 0;
  *(_DWORD *)(nVal + 24) = 0;
  *(_DWORD *)(nVal + 8) = 12;
  return nVal;
}

// 0x004B65A0
RenderTarget3 * RenderTarget3::GetInstance()
{
  if ( (byte_DE6A4C & 1) == 0 )
  {
    byte_DE6A4C |= 1u;
    ((RenderTarget3 *)dword_DE6A30)->InitStruct();
    atexit(unknown_libname_413);
  }
  return (RenderTarget3 *)dword_DE6A30;
}

// 0x004B65F0
char RenderTarget3::Init()
{
  gbEffectMgr *pEffectMgr; // edi

  pEffectMgr = gfxMgr->pEffectMgr;
// [VFTABLE] this->__vftable = (vtbl_0056F36C *)((gbEffectMgr *)pEffectMgr)->NewRenderEffect(aGfxscriptGlowG, 0);
  this->m_ptr_4 = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\geom_glow.gbf", 1u);
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

  LOBYTE(result) = this->ResetAndRender(v7, v8);
  if ( (_BYTE)result )
  {
    for ( i = 0; ; ++i )
    {
      v4 = *((_DWORD *)&this->m_ptr_4 + 3);
      if ( !v4 || i >= (*((_DWORD *)&this->m_ptr_4 + 4) - v4) >> 2 )
        break;
      ((gbRenderEffect *)this->m_ptr_4)->SetVariant(6, *(_DWORD *)(v4 + 4 * i) + 16);
      v5 = *(_DWORD *)(*((_DWORD *)&this->m_ptr_4 + 3) + 4 * i);
      (*(void ( **)(int, gbRenderEffect *))(*(_DWORD *)v5 + 4))(v5, this->m_ptr_4);
    }

    for ( j = 0; ; ++j )
    {
      result = *((_DWORD *)&this->m_ptr_4 + 3);
      if ( !result || j >= (*((_DWORD *)&this->m_ptr_4 + 4) - result) >> 2 )
        break;
      this->UpdateRender(*(_DWORD *)(result + 4 * j));
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
  PAL3 *v6; // ecx
  PAL3 *v7; // eax
  bool result; // al
  PAL3 *v9; // ecx
  gbGfxManager *v10; // edi
  int v11; // esi
  gbSceneGraph *pSceneGraph; // esi
  gbCamera *p_m_fMinDist; // eax
  float v14; // eax
  gbMatrixStack *v15; // esi
  int v16; // [esp+0x18] [ebp-0x14]
  int v17; // [esp+0x1C] [ebp-0x10]
  __int64 v18; // [esp+0x24] [ebp-0x8] BYREF
  float retaddr; // [esp+0x2C] [ebp+0x0]

  Instance_db10 = ((PAL3 *)this)->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(2);
  v7 = ((PAL3 *)v6)->GetInstance_db10();
  result = ((RenderTarget *)v7)->OnResetDevice(0);
  if ( result )
  {
    v17 = v4;
    v16 = v3;
    v10 = gfxMgr;
    v11 = 1;
    if ( LODWORD(((PAL3 *)v9)->GetInstance_db10()->m_snaph) != 2 )
      v11 = 3;
    (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD, int, int))(*(_DWORD *)LODWORD(v10[1].InvViewMatrix.xy)
                                                                                   + 172))(
      LODWORD(v10[1].InvViewMatrix.xy),
      0,
      0,
      v11,
      -16777216,
      1065353216,
      0,
      v16,
      v17);
    pSceneGraph = gfxMgr->pSceneGraph;
    if ( g_pCameraCtrl )
      p_m_fMinDist = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
    else
      p_m_fMinDist = 0;
    ((gbSceneGraph *)pSceneGraph)->Begin(p_m_fMinDist);
    LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
    v18 = *(_QWORD *)(&g_pCameraCtrl->m_vecLookAt + 1);
    v14 = *((float *)&g_pCameraCtrl->m_vecLookAt + 5);
    *(float *)&v18 = *(float *)&v18 * -1.5;
    *((float *)&v18 + 1) = *((float *)&v18 + 1) * -1.5;
    retaddr = v14 * -1.5;
    v15 = gfxMgr->pMatrixStack[1];
    ((gbMatrixStack *)v15)->Push();
    ((gbMatrixStack *)v15)->Translate((gbVec3D *)&v18);
    return 1;
  }
  return result;
}

// 0x004B67B0
void RenderTarget3::EndSceneGraph()
{
  PAL3 *v1; // ecx
  PAL3 *Instance_db10; // eax

  ((gbSceneGraph *)gfxMgr->pSceneGraph)->End();
  Instance_db10 = ((PAL3 *)v1)->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->RenderToScreen();
  ((gbMatrixStack *)gfxMgr->pMatrixStack[1])->Pop();
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
  double v3; // st7
  double v4; // st7
  double v5; // st6
  double width; // st5
  __int64 v7; // rax
  double v8; // st7
  double v9; // st6
  double v10; // st6
  double v11; // st6
  gbDynVertBuf *DynVertBuf; // eax
  PAL3 *v13; // ecx
  int v14; // esi
  gbDynVertBuf *v15; // ebp
  int result; // eax
  int i; // edi
  PAL3 *Instance_db10; // eax
  float v19; // [esp+0x30] [ebp-C0h]
  int v20; // [esp+0x30] [ebp-C0h]
  float v21; // [esp+0x34] [ebp-BCh]
  float v22; // [esp+0x34] [ebp-BCh]
  float v23; // [esp+0x34] [ebp-BCh]
  int v24; // [esp+0x34] [ebp-BCh]
  float v25; // [esp+0x38] [ebp-B8h]
  float v26; // [esp+0x38] [ebp-B8h]
  float v27; // [esp+0x38] [ebp-B8h]
  int v28; // [esp+0x38] [ebp-B8h]
  float v29; // [esp+0x3C] [ebp-B4h]
  int v30; // [esp+0x3C] [ebp-B4h]
  float height; // [esp+0x40] [ebp-B0h]
  float v32; // [esp+0x40] [ebp-B0h]
  struct gbVec3D v33; // [esp+0x44] [ebp-ACh] BYREF
  float v34; // [esp+0x50] [ebp-A0h] BYREF
  float v35; // [esp+0x54] [ebp-0x9C]
  float v36; // [esp+0x58] [ebp-0x98]
  float v37; // [esp+0x5C] [ebp-0x94]
  float v38; // [esp+0x60] [ebp-0x90]
  float v39; // [esp+0x64] [ebp-0x8C]
  float v40; // [esp+0x68] [ebp-0x88] BYREF
  float v41; // [esp+0x6C] [ebp-0x84] BYREF
  float v42; // [esp+0x70] [ebp-0x80]
  float v43; // [esp+0x74] [ebp-0x7C]
  struct gbUIQuad v44; // [esp+0x78] [ebp-0x78] BYREF
  int v45; // [esp+A0h] [ebp-0x50] BYREF
  int v46; // [esp+A4h] [ebp-0x4C] BYREF
  gbRenderEffect **v47; // [esp+A8h] [ebp-0x48]
  struct gbTextureArray v48; // [esp+ACh] [ebp-0x44] BYREF

  v47 = (gbRenderEffect **)this;
  v2 = *(void ( ***)(int, float *))nVal;
  v34 = 0.0;
  v35 = 0.0;
  v36 = 0.0;
  v37 = 0.0;
  v38 = 0.0;
  v39 = 0.0;
  (*v2)(nVal, &v34);
  v44.color = -1;
  v44.z = 0.0;
  v19 = v37 + v34;
  v21 = v35 + v38;
  v25 = v36 + v39;
  v33.x = v19 * 0.5;
  v33.y = v21 * 0.5;
  v33.z = v25 * 0.5;
  ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->PointWorldToScr(&v33, &v40, &v41);
  v22 = v38 - v35;
  v26 = v39 - v36;
  v33.x = (v37 - v34) * 0.5;
  v33.y = v22 * 0.5;
  v33.z = v26 * 0.5;
  ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->PointWorldToScr(&v33, (float *)&v45, (float *)&v46);
  v3 = v40 - 0.2;
  v45 = 1045220557;
  v46 = 1050253722;
  v23 = v41 - 0.30000001;
  v27 = v40 + 0.2;
  v29 = v41 + 0.30000001;
  if ( v3 >= v27 )
    v44.sx = v40 + 0.2;
  else
    v44.sx = v3;
  if ( v3 <= v27 )
    v44.ex = v40 + 0.2;
  else
    v44.ex = v3;
  if ( v23 >= (double)v29 )
    v4 = v29;
  else
    v4 = v23;
  if ( v23 <= (double)v29 )
    v5 = v29;
  else
    v5 = v23;
  width = (double)g_DrvInfo.width;
  v20 = (__int64)((v44.sx + 1.0) * width * 0.5);
  v28 = (__int64)((v44.ex + 1.0) * width * 0.5);
  height = (float)g_DrvInfo.height;
  v24 = (__int64)((1.0 - v5) * height * 0.5);
  v7 = (__int64)((1.0 - v4) * height * 0.5);
  v8 = (double)v20;
  v30 = v7;
  v44.su = v8 * 0.00125;
  v9 = (double)(int)v7;
  v43 = v9;
  v44.sy = v43;
  v44.sv = v9 * 0.0016666667;
  v10 = (double)v28;
  v42 = v10;
  v44.ex = v42;
  v44.eu = v10 * 0.00125;
  v11 = (double)v24;
  v32 = v11;
  v44.ey = v32;
  v44.color = 1848125480;
  v44.ev = v11 * 0.0016666667;
  v44.sx = v8;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  v14 = *(_DWORD *)(nVal + 8);
  v15 = DynVertBuf;
  result = *(_DWORD *)(nVal + 12);
  for ( i = 0; i < result; v44.sy = (float)v30 )
  {
    Instance_db10 = ((PAL3 *)v13)->GetInstance_db10();
    v48.pTexPt[0] = ((RenderTarget *)Instance_db10)->GetActiveTexture();
    v48.nTex = 1;
    ((gbDynVertBuf *)v15)->RenderUIQuad(&v44, 1, *v47, &v48);
    v20 -= v14;
    HIBYTE(v44.color) -= 10;
    v44.sx = (float)v20;
    v24 -= v14;
    v13 = (PAL3 *)(v14 + v28);
    v28 += v14;
    result = *(_DWORD *)(nVal + 12);
    ++i;
    v44.ey = (float)v24;
    v30 += v14;
    v44.ex = (float)v28;
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
  v2 = &this->m_ptr_4 + 3;
  *v2 = (gbRenderEffect *)1065353216;
  *((_BYTE *)result + 4) = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = (gbRenderEffect *)1065353216;
  return result;
}

// 0x004B6C80
int RenderTarget3::sub_4B6C80(void *Block, char a3)
{
// [VFTABLE] nearby_4b6ca0(&this->__vftable);
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x004B6D20
int * RenderTarget3::Reset()
{
  this->m_ptr_4 = 0;
// [VFTABLE] LOBYTE(this->__vftable) = 0;
  return (int *)this;
}

// 0x004B6DF0
void * RenderTarget3::End()
{
  void *result; // eax

// [VFTABLE] if ( LOBYTE(this->__vftable) )
    return (*(void *( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 228))(
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

// [VFTABLE] if ( LOBYTE(this->__vftable) )
  {
    (*(void ( **)(_DWORD, int, int))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 228))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      168,
      7);
    if ( this->m_ptr_4 )
    {
      if ( *(_DWORD *)&((PalScript *)&stru_C11720)->m_pActorData )
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
        DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
        m_ptr_4 = this->m_ptr_4;
        v6.nTex = 1;
        v6.pTexPt[0] = (gbTexture *)m_ptr_4;
        ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v5, 1, *(gbRenderEffect **)&((PalScript *)&stru_C11720)->m_pActorData, &v6);
        v7 = -1;
        PopMatrixStacks(&v4);
      }
    }
  }
}
