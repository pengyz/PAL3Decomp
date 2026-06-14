#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffectSystem.h"

// Forward declarations for unnamed functions
int sub_4431B0(...);
int sub_4C5850(...);
int sub_4C5D00(...);
int sub_4C5D70(...);
int sub_4C5FA0(...);
int sub_4C60E0(...);
void __cdecl todo_401800(void);

BOOL EditBox_IsModified(HWND hWnd); // from annotations
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations

// Unnamed globals (extern)
extern int dword_189555C;
void __cdecl nullsub_16(void);
void __cdecl nullsub_79(...);
void __cdecl unknown_libname_446(void);

// 0x004C5820
CEffectSystem * CEffectSystem::Create(int pGfxMgr)
{
  this->m_pDisplay = 0;
  sub_4C5850();
  this->m_pDisplay = (gbGfxManager *)pGfxMgr;
  return this;
}

// 0x004C5D50
int CEffectSystem::slot_0(void *Block, char a3)
{
  sub_4C5D70();
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x004C5D80
int CEffectSystem::slot_1()
{
  int v0; // ecx

  *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1) = 0;
  *(_BYTE *)(v0 + 12) = 0;
  *(_BYTE *)(v0 + 13) = 0;
  *(_DWORD *)(v0 + 24) = 0;
  *(_DWORD *)(v0 + 98332) = 0;
  memset((void *)(v0 + 28), 0, 0x18000u);
  return 0;
}

// 0x004C5DB0
int CEffectSystem::GetThreadHandle()
{
  CEffectSystem *v2; // ecx
  int result; // eax

  LOBYTE(this->m_pAlphaBlend) = 1;
  BYTE1(this->m_pAlphaBlend) = 1;
  ((CCBSystem *)this)->GetThreadBase();
  v2 = (CEffectSystem *)((char *)this + 237600);
  for ( result = 0; result < 2048; ++result )
  {
    v2->m_pDisplay = (gbGfxManager *)result;
    v2 = (CEffectSystem *)((char *)v2 + 4);
  }
  LOBYTE(result) = 1;
  return result;
}

// 0x004C5DE0
void CEffectSystem::ReleaseParticle()
{
  gbRefObject *v2; // ecx

  v2 = (gbRefObject *)*((_DWORD *)this + 61448);
  if ( v2 )
  {
    ((gbRefObject *)v2)->Release();
    *((_DWORD *)this + 61448) = 0;
  }
  if ( *((_DWORD *)this + 61449) )
  {
    operator delete(*((void **)this + 61449));
    *((_DWORD *)this + 61449) = 0;
  }
}

// 0x004C5E20
int CEffectSystem::slot_6()
{
  int v0; // ecx
  int v1; // esi
  int result; // eax

  v1 = v0;
  *(_DWORD *)(*(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1) + 4) = ((gbVertPoolMgr *)*(gbVertPoolMgr **)(**((_DWORD **)&g_PAL3.m_nsub_4C55F0Count_DE9380
                                                                                     + 1)
                                                                                  + 196))->GetDynVertBuf(0x15u);
  result = *(_DWORD *)(v1 + 98332);
  if ( result > 0 )
    ((gbDynVertBuf *)*(gbDynVertBuf **)(*(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1) + 4))->RenderGeomQuad((gbGeomQuad *)(v1 + 98336), result, *(gbRenderEffect **)(*(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1) + 8), *(gbTextureArray **)(v1 + 245796));
  return result;
}

// 0x004C5E70
int CEffectSystem::nullsub_79(int a2, int a3)
{
  int result; // eax

  return result;
}

// 0x004C5E80
int CEffectSystem::ProcessEffects(double time)
{
  int v3; // edi
  int result; // eax
  char *v5; // esi
  int v6; // [esp+0x8] [ebp-0xC]
  char *v7; // [esp+0xC] [ebp-0x8]
  float v8; // [esp+0x10] [ebp-0x4]

  v3 = 0;
  result = LODWORD(this->m_DefaultUVSet[0].eu);
  if ( result > 0 )
  {
    result = (int)this + 98388;
    v7 = (char *)this + 98388;
    v5 = (char *)&this->m_DefaultUVSet[1].eu + 2;
    do
    {
      if ( *(v5 - 6) )
      {
        v8 = *(float *)(v5 + 2) * time + *(float *)(v5 + 6);
        dword_189555C = (int)v8;
        v6 = (int)v8;
        if ( v6 < (unsigned __int8)*(v5 - 2) )
        {
          *(float *)(v5 + 6) = v8;
          *(v5 - 1) = v6;
          goto LABEL_9;
        }
        ++*v5;
        *(v5 - 1) = 0;
        if ( (unsigned __int8)*v5 < (unsigned __int8)v5[1] )
        {
          *(float *)(v5 + 6) = v8 - (double)(unsigned __int8)*(v5 - 2);
LABEL_9:
          if ( (unsigned __int8)*(v5 - 1) >= (unsigned __int8)*(v5 - 2) )
            *(v5 - 1) = 0;
          *(_DWORD *)(result - 4) = *(_DWORD *)(16 * ((unsigned __int8)*(v5 - 1) + 1)
                                              + *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1));
          *(_DWORD *)result = *(_DWORD *)(16 * (unsigned __int8)*(v5 - 1) + *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1) + 20);
          *(_DWORD *)(result + 4) = *(_DWORD *)(16 * (unsigned __int8)*(v5 - 1)
                                              + *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1)
                                              + 24);
          *(_DWORD *)(result + 8) = *(_DWORD *)(16 * (unsigned __int8)*(v5 - 1)
                                              + *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1)
                                              + 28);
          goto LABEL_12;
        }
        *v5 = 0;
        sub_4C60E0(v3);
        result = (int)v7;
      }
LABEL_12:
      ++v3;
      result += 68;
      v5 += 48;
      v7 = (char *)result;
    }
    while ( v3 < SLODWORD(this->m_DefaultUVSet[0].eu) );
  }
  return result;
}

// 0x004C6030
int CEffectSystem::UpdateEffectState(int nVal)
{
  int result; // eax
  float sv; // edx
  float *v4; // ecx

  result = (int)&this->m_DefaultUVSet[3 * nVal].ev;
  sv = this->m_DefaultUVSet[3 * nVal + 2].sv;
  v4 = (float *)((char *)this + 68 * LODWORD(this->m_DefaultUVSet[3 * nVal + 1].su));
  v4[24600] = sv;
  v4[24584] = *(float *)(result + 28) - *(float *)(result + 40);
  v4[24587] = *(float *)(result + 40) + *(float *)(result + 28);
  v4[24590] = *(float *)(result + 40) + *(float *)(result + 28);
  v4[24593] = *(float *)(result + 28) - *(float *)(result + 40);
  v4[24585] = *(float *)(result + 32);
  v4[24588] = *(float *)(result + 32);
  v4[24591] = *(float *)(result + 32);
  v4[24594] = *(float *)(result + 32);
  v4[24586] = *(float *)(result + 40) + *(float *)(result + 36);
  v4[24589] = *(float *)(result + 40) + *(float *)(result + 36);
  v4[24592] = *(float *)(result + 36) - *(float *)(result + 40);
  v4[24595] = *(float *)(result + 36) - *(float *)(result + 40);
  return result;
}

// 0x004C61A0
CEffectSystem::CEffectSystem(int pDisplay)
{
  gbTexture *v3; // eax
  int *result; // eax
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x800] BYREF
  char ArgList; // [esp+0x408] [ebp-0x400] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(***((_DWORD ***)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1) + 8))(
                      **((_DWORD **)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 1),
                      pDisplay);
  *((_DWORD *)this + 61448) = v3;
  ((gbTexture *)v3)->LoadTexture(1);
  result = (int *)operator new(0x44u);
  if ( result )
  {
    v5 = *((_DWORD *)this + 61448);
    result[16] = 1;
    *result = v5;
  }
  else
  {
    result = 0;
  }
  *((_DWORD *)this + 61449) = result;
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("C++ new failed!", "D:\\Project\\PAL3\\effect\\EffectSystem.cpp", 761),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result;
}

// 0x004C6240
int * CEffectSystem::_CEffectSystem(int nVal)
{
  sub_4C5D00(nVal);
  this->m_pAdditiveBlend = (gbRenderEffect *)1;
  return (int *)this;
}

// 0x004C6260
int * CEffectSystem::Reset(CEffectSystem *Block, char pData)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int *)this;
}

// 0x004C6280
// attributes: thunk
bool CEffectSystem::Init()
{
  return sub_4C5D70(this);
}

// 0x004C6290
void CEffectSystem::Destroy()
{
  _BYTE v1[16]; // [esp+0x4] [ebp-0x30] BYREF
  int v2; // [esp+0x14] [ebp-0x20]
  int v3; // [esp+0x18] [ebp-0x1C]
  int v4; // [esp+0x1C] [ebp-0x18]
  int v5; // [esp+0x20] [ebp-0x14]
  int v6; // [esp+0x24] [ebp-0x10]
  int v7; // [esp+0x28] [ebp-0xC]
  int v8; // [esp+0x2C] [ebp-0x8]
  int v9; // [esp+0x38] [ebp+0x4]
  int v10; // [esp+0x3C] [ebp+0x8]
  int v11; // [esp+0x40] [ebp+0xC]
  int v12; // [esp+0x44] [ebp+0x10]
  int v13; // [esp+0x48] [ebp+0x14]

  v1[13] = 0;
  v1[14] = 0;
  v5 = v9;
  v8 = v12;
  v7 = v11;
  v6 = v10;
  v1[10] = 1;
  v1[8] = 1;
  v1[9] = 1;
  v1[12] = 16;
  v1[15] = 1;
  v4 = -1;
  v2 = v13;
  v3 = 0;
  sub_4C5FA0(v1);
}

// 0x004C6330
// attributes: thunk
CEffect * CEffectSystem::GetEffectIndex()
{
  return (CEffect *)this->CreateEffect();
}

// 0x004C6340
int CEffectSystem::CreateEffect()
{
  *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 383) = 1094713344;
  return 1094713344;
}

// 0x004C6350
// attributes: thunk
void CEffectSystem::GetEffect()
{

}

// 0x004C6360
void CEffectSystem::DestroyEffect()
{
  *((float *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 382) = 12.0 + 12.0;
}

// 0x004C6370
CEffectSystem * CEffectSystem::DestroyEffect()
{
  this->m_DefaultUVSet[2].su = NAN;
  this->m_DefaultUVSet[1].ev = 0.0;
  *((_DWORD *)this + 208) = 0;
  this->m_DefaultUVSet[2].sv = 0.0;
  this->m_DefaultUVSet[2].eu = 0.0;
  LOBYTE(this->m_pVertexBuffer) = 0;
  BYTE1(this->m_pVertexBuffer) = 0;
  this->m_pAdditiveBlend = 0;
  *((_DWORD *)this + 207) = 0;
  this->m_DefaultUVSet[0].ev = 0.0;
  this->m_DefaultUVSet[1].su = 0.75;
  this->m_DefaultUVSet[1].sv = 1.0;
  this->m_DefaultUVSet[1].eu = 0.0;
  this->m_pAlphaBlend = 0;
  this->m_DefaultUVSet[0].eu = 0.0;
  this->m_DefaultUVSet[0].sv = 800.0;
  this->m_DefaultUVSet[0].su = 600.0;
  return this;
}

// 0x004C6410
int * CEffectSystem::DestroyAllEffect()
{
  if ( (*(_BYTE *)(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 221) & 1) == 0 )
  {
    *((_BYTE *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 884) |= 1u;
    ((CEffectSystem *)(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 12))->DestroyEffect();
    atexit(unknown_libname_446);
  }
  return &g_PAL3.m_nsub_4C55F0Count_DE9380 + 12;
}

// 0x004C6460
bool CEffectSystem::IsVisible()
{
  gbRenderEffect *v3; // eax
  int v4; // esi
  float *p_ev; // edi
  _DWORD v6[2]; // [esp+0x14] [ebp-0x14] BYREF
  int v7; // [esp+0x1C] [ebp-0xC]
  int v8; // [esp+0x20] [ebp-0x8]
  int v9; // [esp+0x24] [ebp-0x4]

  if ( !*((_DWORD *)this + 207) )
  {
    if ( (g_dwGameFlags & 8) == 0 )
      return 0;
    v6[0] = 0;
    v6[1] = 0;
    v7 = 0;
    v8 = 0;
    v9 = 0;
    if ( !(*(int ( **)(gbGfxManager *, _DWORD *, int))(*(_DWORD *)gfxMgr + 84))(gfxMgr, v6, 1) )
      return 0;
    (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 88))(gfxMgr);
    v3 = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\trail.gbf", 0);
    *((_DWORD *)this + 207) = v3;
    if ( !v3 )
      return 0;
    if ( (*(int ( **)(_DWORD, _DWORD, char *))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 152))(
           LODWORD(gfxMgr[1].InvViewMatrix.xy),
           0,
           (char *)this + 832) < 0 )
      return 0;
    v4 = 0;
    p_ev = &this->m_DefaultUVSet[2].ev;
    do
    {
      if ( !(*(int ( **)(float *, int, int, int))(*(_DWORD *)p_ev + 12))(p_ev, 256, 256, v7)
        || !(*(int ( **)(gbGfxManager *, float *))(*(_DWORD *)gfxMgr + 92))(gfxMgr, p_ev) )
      {
        return 0;
      }
      (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                           + 172))(
        LODWORD(gfxMgr[1].InvViewMatrix.xy),
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      ++v4;
      p_ev += 24;
    }
    while ( v4 < 8 );
    if ( (*(int ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 148))(
           LODWORD(gfxMgr[1].InvViewMatrix.xy),
           0,
           *((_DWORD *)this + 208)) < 0 )
      return 0;
    LOBYTE(this->m_pVertexBuffer) = 1;
  }
  return 1;
}

// 0x004C65C0
void CEffectSystem::SetVisible(float effect)
{
  double v2; // st7
  char v4; // c0

  v2 = effect + *(float *)&this->m_pDisplay;
  *(float *)&this->m_pDisplay = v2;
  if ( !v4 )
  {
    ++LODWORD(this->m_DefaultUVSet[2].sv);
    *(float *)&this->m_pDisplay = v2 - 0.02;
  }
}

// 0x004C65F0
void CEffectSystem::HandleViewMove(gbRenderEffect *a2, int a3)
{
  int v4; // eax
  gbCamera *m_pAdditiveBlend; // ecx

  if ( BYTE1(this->m_pVertexBuffer) && LOBYTE(this->m_pVertexBuffer) )
  {
    if ( *(float *)&a2 != 0.0 )
      this->m_pAdditiveBlend = a2;
    v4 = LODWORD(this->m_DefaultUVSet[2].sv) & 7;
    LODWORD(this->m_DefaultUVSet[2].eu) = v4;
    (*(void (**)(gbGfxManager *, float *))(*(_DWORD *)gfxMgr + 92))(
      gfxMgr,
      &this->m_DefaultUVSet[6 * v4 + 2].ev);
    (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                         + 172))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      0,
      0,
      3,
      -16777216,
      1065353216,
      0);
    m_pAdditiveBlend = (gbCamera *)this->m_pAdditiveBlend;
    if ( m_pAdditiveBlend )
      ((gbCamera *)m_pAdditiveBlend)->SetDimention(256, 192);
  }
}

// 0x004C6670
void CEffectSystem::Update()
{
  gbColorQuad *v2; // edi
  int v3; // ebx
  int v4; // ebx
  int v5; // edi
  char *v6; // ecx
  float eu; // eax
  int v8; // eax
  float *v9; // edi
  float *p_ev; // ebx
  gbRenderEffect *v11; // eax
  unsigned int v12; // ebp
  float *v13; // edi
  float *v14; // ebx
  gbRenderEffect *v15; // eax
  gbDynVertBuf *DynVertBuf; // [esp+0x44] [ebp-0x48]
  struct gbTextureArray v17; // [esp+0x48] [ebp-0x44] BYREF

  if ( BYTE1(this->m_pVertexBuffer) && LOBYTE(this->m_pVertexBuffer) )
  {
    (*(void ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 148))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      0,
      *((_DWORD *)this + 208));
    (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                         + 172))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      0,
      0,
      3,
      -16777216,
      1065353216,
      0);
    ((gbCamera *)this->m_pAdditiveBlend)->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
    DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
    if ( (*(_BYTE *)(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 10) & 1) == 0 )
    {
      v2 = (gbColorQuad *)(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 2);
      *((_BYTE *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 40) |= 1u;
      v3 = 8;
      do
      {
        --v3;
      }
      while ( v3 );
      atexit(nullsub_16);
    }
    v4 = 158 - 8 * LODWORD(this->m_DefaultUVSet[2].eu);
    v5 = 0;
    v6 = (char *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 9;
    do
    {
      *(v6 - 1) = v4 / 2;
      *v6 = v4 / 2;
      v6[1] = v4 / 2;
      v6[2] = v4;
      v4 += 8;
      if ( v5 == LODWORD(this->m_DefaultUVSet[2].eu) )
        v4 = 102;
      v6 += 4;
      ++v5;
    }
    while ( (int)v6 < (int)((char *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 41) );
    eu = this->m_DefaultUVSet[2].eu;
    v17.nTex = 0;
    if ( LODWORD(eu) < 7 )
    {
      v8 = LODWORD(eu) + 1;
      if ( v8 < 8 )
      {
        v9 = (float *)(4 * v8 + 14586760);
        p_ev = &this->m_DefaultUVSet[6 * v8 + 2].ev;
        do
        {
          v11 = (gbRenderEffect *)*((_DWORD *)this + 207);
          this->m_DefaultUVSet[2].su = *v9;
          v17.nTex = 1;
          v17.pTexPt[0] = (gbTexture *)p_ev;
          ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad((gbUIQuad *)&this->m_pAlphaBlend, 1, v11, &v17);
          ++v9;
          p_ev += 24;
        }
        while ( (int)v9 < (int)((float *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 10) );
      }
    }
    v12 = 0;
    v13 = (float *)(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 2);
    v14 = &this->m_DefaultUVSet[2].ev;
    do
    {
      if ( (int)v13 < (int)((float *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 10) )
      {
        v15 = (gbRenderEffect *)*((_DWORD *)this + 207);
        this->m_DefaultUVSet[2].su = *v13;
        v17.nTex = 1;
        v17.pTexPt[0] = (gbTexture *)v14;
        ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad((gbUIQuad *)&this->m_pAlphaBlend, 1, v15, &v17);
      }
      ++v12;
      ++v13;
      v14 += 24;
    }
    while ( v12 <= LODWORD(this->m_DefaultUVSet[2].eu) );
  }
}

// 0x004C6870
int * CEffectSystem::FillDefaultUVSet()
{
  this->m_pVertexBuffer = 0;
  LOBYTE(this->m_pAdditiveBlend) = 0;
  this->m_DefaultUVSet[0].su = 0.0;
  this->m_DefaultUVSet[0].sv = 0.0;
  this->m_DefaultUVSet[0].eu = 0.0;
  this->m_DefaultUVSet[0].ev = NAN;
  this->m_DefaultUVSet[1].su = NAN;
  this->m_DefaultUVSet[1].sv = 0.0;
  this->m_DefaultUVSet[1].eu = 0.0;
  this->m_DefaultUVSet[1].ev = 0.0;
  this->m_DefaultUVSet[7].sv = 0.0;
  this->m_DefaultUVSet[7].eu = 0.0;
  this->m_DefaultUVSet[7].ev = 0.0;
  this->m_DefaultUVSet[8].eu = 0.0;
  this->m_DefaultUVSet[8].ev = 0.0;
  this->m_DefaultUVSet[9].su = 0.0;
  this->m_DefaultUVSet[9].sv = 0.0;
  this->m_DefaultUVSet[9].eu = 0.0;
  this->m_DefaultUVSet[9].ev = 0.0;
  this->m_DefaultUVSet[10].su = 0.0;
  this->m_DefaultUVSet[10].sv = 0.0;
  this->m_DefaultUVSet[10].eu = 0.0;
  this->m_DefaultUVSet[9].ev = 0.0;
  this->m_DefaultUVSet[9].eu = 0.0;
  this->m_DefaultUVSet[9].sv = 0.0;
  this->m_DefaultUVSet[10].eu = 0.0;
  this->m_DefaultUVSet[10].sv = 0.0;
  this->m_DefaultUVSet[10].su = 0.0;
  this->m_DefaultUVSet[9].su = 0.0;
  this->m_DefaultUVSet[8].ev = 0.0;
  this->m_DefaultUVSet[8].eu = 0.0;
  this->m_DefaultUVSet[6].eu = 0.0;
  this->m_DefaultUVSet[2].su = 0.0;
  this->m_DefaultUVSet[2].sv = 0.0;
  BYTE1(this->m_DefaultUVSet[3].su) = 0;
  BYTE2(this->m_DefaultUVSet[3].su) = 0;
  this->m_DefaultUVSet[2].eu = 0.0;
  this->m_DefaultUVSet[2].ev = 0.0;
  return (int *)this;
}

// 0x004CF580
int CEffectSystem::CreateEffect(CEffectSystem *pSrc, int nVal, CEffectSystem *pParam)
{
  int v4; // ebp
  float *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  CEffectSystem *v9; // eax
  int *v10; // eax

  v4 = 0;
  for ( i = &this->m_DefaultUVSet[4].eu; *(_BYTE *)i; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pSrc);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffectSystem *)operator new(0x10C0u);
  if ( v9 )
    v10 = ((CEffectSystem *)v9)->FillDefaultUVSet();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pSrc);
  return v4;
}

// 0x004E1190
int CEffectSystem::CreateEffectChain(
        
        CCBUI *pCBUI,
        HWND hDlg,
        unsigned int dwVal,
        int bReadOnly,
        int nVal)
{
  HWND DlgItem; // esi
  HWND v8; // eax
  LRESULT v10; // eax

  _DWORD *v12; // edx
  _DWORD *v13; // edx
  _DWORD *v14; // edx
  _DWORD *v15; // edx
  _DWORD *v16; // eax
  _DWORD *v17; // eax
  int v18; // eax
  bool IsModified; // bl

  int v21; // eax
  LPARAM lParam[8]; // [esp+0x20] [ebp-0x20] BYREF
  HWND hDlga; // [esp+0x48] [ebp+0x8]

  DlgItem = GetDlgItem(hDlg, 1203);
  v8 = GetDlgItem(hDlg, 1208);
  hDlga = v8;
  if ( dwVal > 0x110 )
  {
    if ( dwVal == 273 )
    {
      if ( (unsigned __int16)bReadOnly > 0x3FFu )
      {
        switch ( (__int16)bReadOnly )
        {
          case 1026:
// [VFTABLE] v16 = (_DWORD *)(*(_DWORD *)(*((_DWORD *)pCBUI->__vftable->sub_4431B0 + 19) + 232) + 28);
            *v16 = -1092196762;
            v16[1] = -1092196762;
            v16[2] = -1092196762;
            v16[3] = 1065353216;
// [VFTABLE] v17 = (_DWORD *)(*(_DWORD *)(*((_DWORD *)pCBUI->__vftable->sub_4431B0 + 19) + 452) + 28);
            *v17 = -1092196762;
            v17[1] = -1092196762;
            v17[2] = -1092196762;
            v17[3] = 1065353216;
            break;
          case 1027:
// [VFTABLE] v18 = *(_DWORD *)(*((_DWORD *)pCBUI->__vftable->sub_4431B0 + 19) + 452) + 12;
            strcpy((char *)v18, "333?333?333?");
            *(_BYTE *)(v18 + 13) = 0;
            *(_WORD *)(v18 + 14) = 16256;
            break;
          case 1028:
            gfxMgr->fSelfIllum = 1.0;
            break;
          case 1208:
            IsModified = EditBox_IsModified(v8);
            *((_BYTE *)this->DestroyAllEffect() + 5) = IsModified;
            break;
          case 1209:
            *((_BYTE *)((CEffectSystem *)((unsigned __int16)bReadOnly - 1026))->DestroyAllEffect() + 5) = 0;
            break;
          default:
            break;
        }
      }
      else if ( (unsigned __int16)bReadOnly == 1023 )
      {
// [VFTABLE] v14 = (_DWORD *)(*(_DWORD *)(*((_DWORD *)pCBUI->__vftable->sub_4431B0 + 19) + 232) + 28);
        *v14 = 1041865114;
        v14[1] = 1041865114;
        v14[2] = 1041865114;
        v14[3] = 1065353216;
// [VFTABLE] v15 = (_DWORD *)(*(_DWORD *)(*((_DWORD *)pCBUI->__vftable->sub_4431B0 + 19) + 452) + 28);
        *v15 = 1041865114;
        v15[1] = 1041865114;
        v15[2] = 1041865114;
        v15[3] = 1065353216;
      }
      else if ( (unsigned __int16)bReadOnly > 0x3FCu )
      {
        if ( (unsigned __int16)bReadOnly == 1021 )
        {
          ((CCBUI *)pCBUI)->PopulateSceneList(hDlg);
        }
        else if ( (unsigned __int16)bReadOnly == 1022 )
        {
// [VFTABLE] v12 = (_DWORD *)(*(_DWORD *)(*((_DWORD *)pCBUI->__vftable->sub_4431B0 + 19) + 232) + 28);
          *v12 = 0;
          v12[1] = 0;
          v12[2] = 0;
          v12[3] = 1065353216;
// [VFTABLE] v13 = (_DWORD *)(*(_DWORD *)(*((_DWORD *)pCBUI->__vftable->sub_4431B0 + 19) + 452) + 28);
          *v13 = 0;
          v13[1] = 0;
          v13[2] = 0;
          v13[3] = 1065353216;
        }
      }
      else
      {
        switch ( (unsigned __int16)bReadOnly )
        {
          case 0x3FCu:
            HIBYTE(g_RoleSystemCombat.m_pScriptBuf) = 1;
            break;
          case 1u:
            EndDialog(hDlg, 1);
            break;
          case 0x3F8u:
            LOBYTE(g_RoleSystemCombat.m_pScriptBuf) = 1;
            break;
          case 0x3F9u:
            BYTE2(g_RoleSystemCombat.m_pScriptBuf) = 1;
            break;
        }
      }
LABEL_32:
      if ( bReadOnly == 1203 && *(_DWORD *)(nVal + 8) == -3 )
      {
        v21 = *(_DWORD *)(nVal + 12);
        if ( v21 != -1 )
          ((CCBUI *)pCBUI)->LoadSceneByIndex(v21);
      }
    }
  }
  else
  {
    if ( dwVal != 272 )
    {
      if ( dwVal == 16 )
      {
        EndDialog(hDlg, (unsigned __int16)bReadOnly);
        return 1;
      }
      if ( dwVal != 78 )
        return 0;
      goto LABEL_32;
    }
    SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
    v10 = SendMessageA(DlgItem, 0x1037u, 0, 0);
    LOBYTE(v10) = v10 | 0x21;
    SendMessageA(DlgItem, 0x1036u, 0, v10);
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 7;
    lParam[1] = 0;
    lParam[2] = 50;
    lParam[3] = (LPARAM)&g_EffMgr;
    SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 100;
    lParam[3] = (LPARAM)&g_EffMgr;
    SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParam);
    ((CCBUI *)pCBUI)->PopulateSceneList(hDlg);
    if ( hDlga )
    {
      LOBYTE(bReadOnly) = *((_BYTE *)this->DestroyAllEffect() + 5);
      EditBox_SetReadOnly(hDlga, bReadOnly);
      return 0;
    }
  }
  return 0;
}
