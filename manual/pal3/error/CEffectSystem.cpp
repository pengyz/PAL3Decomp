#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffectSystem.h"
#include "Combat/CCBUI.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffSParticle.h"
#include "Effect/CEffect.h"
#include "Effect/CEffgbParticle.h"
#include "UI/UIWnd.h"
#include "Misc/tagEffMgrData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4C5850(...);
int sub_4C5910(...);
int sub_4C5D00(...);
int sub_4C5D70(...);
int sub_4C60E0(...);

// Unnamed globals (extern)
extern unsigned char byte_DE93A8;
extern unsigned char byte_DE93A9;
extern unsigned char byte_DE96F4;
extern int dword_DE9384;
extern int dword_DE93B0;
extern int dword_DE997C;
extern float flt_DE9978;
void __cdecl nullsub_16(void);
void __cdecl nullsub_79(...);
extern gbColorQuad stru_DE9388;

// 0x004C5820
CEffectSystem * CEffectSystem::Create(int pGfxMgr)
{
    CEffectSystem *_this = this;
  *(_DWORD *)_this = 0;
  sub_4C5850();
  *(_DWORD *)_this = pGfxMgr;
  return _this;
}

// 0x004C5840
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CEffectSystem::DestroyEffects()
{
  sub_4C5910(this);
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004C5D80
int CEffectSystem::slot_1()
{
  int v0; // ecx
  int result; // eax

  result = 0;
  dword_DE9384 = 0;
  *(_BYTE *)(v0 + 12) = 0;
  *(_BYTE *)(v0 + 13) = 0;
  *(_DWORD *)(v0 + 24) = 0;
  *(_DWORD *)(v0 + 98332) = 0;
  memset((void *)(v0 + 28), 0, 0x18000u);
  return result;
}

// 0x004C5E20
int CEffectSystem::slot_6()
{
  int v0; // ecx
  int v1; // esi
  int result; // eax

  v1 = v0;
  *(_DWORD *)(dword_DE9384 + 4) = (unsigned long)(((gbVertPoolMgr *)*(gbVertPoolMgr **)(*(_DWORD *)dword_DE9384 + 196)))->gbVertPoolMgr::GetDynVertBuf(0x15u);
  result = *(_DWORD *)(v1 + 98332);
  if ( result > 0 )
    (((gbDynVertBuf *)*(gbDynVertBuf **)(dword_DE9384 + 4)))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)(v1 + 98336), result, *(gbRenderEffect **)(dword_DE9384 + 8), *(gbTextureArray **)(v1 + 245796));
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
  char *p_eu; // [esp+0xC] [ebp-0x8]
  float v8; // [esp+0x10] [ebp-0x4]

  v3 = 0;
  result = LODWORD(this->m_DefaultUVSet[0].sv);
  if ( result > 0 )
  {
    result = (int)&this[273].m_DefaultUVSet[5].eu;
    p_eu = (char *)&this[273].m_DefaultUVSet[5].eu;
    v5 = (char *)&this->m_DefaultUVSet[1].sv + 2;
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
          *(_DWORD *)(result - 4) = *(_DWORD *)(16 * ((unsigned __int8)*(v5 - 1) + 1) + dword_DE9384);
          *(_DWORD *)result = *(_DWORD *)(16 * (unsigned __int8)*(v5 - 1) + dword_DE9384 + 20);
          *(_DWORD *)(result + 4) = *(_DWORD *)(16 * (unsigned __int8)*(v5 - 1) + dword_DE9384 + 24);
          *(_DWORD *)(result + 8) = *(_DWORD *)(16 * (unsigned __int8)*(v5 - 1) + dword_DE9384 + 28);
          goto LABEL_12;
        }
        *v5 = 0;
        sub_4C60E0(v3);
        result = (int)p_eu;
      }
LABEL_12:
      ++v3;
      result += 68;
      v5 += 48;
      p_eu = (char *)result;
    }
    while ( v3 < SLODWORD(this->m_DefaultUVSet[0].sv) );
  }
  return result;
}

// 0x004C6030
int CEffectSystem::UpdateEffectState(int nVal)
{
  int result; // eax
  float su; // edx
  float *v4; // ecx

  result = (int)&this->m_DefaultUVSet[3 * nVal].eu;
  su = this->m_DefaultUVSet[3 * nVal + 2].su;
  v4 = (float *)((char *)this + 68 * LODWORD(this->m_DefaultUVSet[3 * nVal].ev));
  v4[24600] = su;
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

// 0x004C6240
int * CEffectSystem::_todo_004C6240(int nVal)
{
  sub_4C5D00(nVal);
  this->m_pVertexBuffer = ((gbDynVertBuf *)((gbDynVertBuf *)1));
  return (int *)this;
}

// 0x004C6280
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
bool CEffectSystem::Init()
{
  return sub_4C5D70(this);
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004C6330
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
CEffect * CEffectSystem::GetEffectIndex()
{
  return (CEffect *)this->CEffectSystem::CreateEffect();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004C6340
int CEffectSystem::CreateEffect()
{
  int result; // eax

  result = 1094713344;
  dword_DE997C = 1094713344;
  return result;
}

// 0x004C6350
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CEffectSystem::GetEffect()
{
  this->CEffectSystem::DestroyEffect();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004C6360
void CEffectSystem::DestroyEffect()
{
  flt_DE9978 = 12.0 + 12.0;
}

// 0x004C6410
int * CEffectSystem::DestroyAllEffect()
{
  if ( (byte_DE96F4 & 1) == 0 )
  {
    byte_DE96F4 |= 1u;
    CEffectSystem_DestroyEffect();
    atexit(PostDestroyAllEffects);
  }
  return dword_DE93B0;
}

// 0x004C6460
bool CEffectSystem::IsVisible()
{
  gbRenderEffect *v3; // eax
  int v4; // esi
  float *p_eu; // edi
  _DWORD v6[2]; // [esp+0x14] [ebp-0x14] BYREF
  int v7; // [esp+0x1C] [ebp-0xC]
  int v8; // [esp+0x20] [ebp-0x8]
  int v9; // [esp+0x24] [ebp-0x4]

  if ( !LODWORD(this[2].m_DefaultUVSet[5].eu) )
  {
    if ( (g_dwGameFlags & 8) == 0 )
      return 0;
    v6[0] = 0;
    v6[1] = 0;
    v7 = 0;
    v8 = 0;
    v9 = 0;
    if ( !(*(int ( **)(gbGfxManager *, _DWORD *, int))(*(_DWORD *)*(void**)(gfxMgr) + 84))(gfxMgr, (_DWORD *)(v6), 1) )
      return 0;
    (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 88))(gfxMgr);
    v3 = (((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect(&g_EffMgrData._tail_000[920], 0);
    LODWORD(this[2].m_DefaultUVSet[5].eu) = (unsigned long)v3;
    if ( !v3 )
      return 0;
    if ( (*(int ( **)(_DWORD, _DWORD, float *))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 152))(
           LODWORD(gfxMgr[1].InvViewMatrix.xy),
           0,
           &this[2].m_DefaultUVSet[5].ev) < 0 )
      return 0;
    v4 = 0;
    p_eu = (float *)&this->m_DefaultUVSet[2].eu;
    do
    {
      if ( !(*(int ( **)(float *, int, int, int))(*(_DWORD *)p_eu + 12))(p_eu, 256, 256, v7)
        || !(*(int ( **)(gbGfxManager *, float *))(*(_DWORD *)*(void**)(gfxMgr) + 92))(gfxMgr, p_eu) )
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
      p_eu += 24;
    }
    while ( v4 < 8 );
    if ( (*(int ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 148))(
           LODWORD(gfxMgr[1].InvViewMatrix.xy),
           0,
           LODWORD(this[2].m_DefaultUVSet[5].ev)) < 0 )
      return 0;
    LOBYTE(this->m_pDisplay) = 1;
  }
  return 1;
}

// 0x004C65C0
void CEffectSystem::SetVisible(float effect)
{
    CEffectSystem *_this = this;
  float v2; // st7
  char v4; // c0

  v2 = effect + *(float *)_this;
  *(float *)_this = v2;
  if ( !v4 )
  {
    ++LODWORD(_this->m_DefaultUVSet[2].su);
    *(float *)_this = v2 - 0.02;
  }
}

// 0x004C65F0
void CEffectSystem::HandleViewMove(float x, float y)
{
  int v2; // ecx
  int v3; // esi
  int v4; // eax
  gbCamera *v5; // ecx

  v3 = v2;
  if ( *(_BYTE *)(v2 + 5) && *(_BYTE *)(v2 + 4) )
  {
    if ( x != 0.0f )
      *(float *)(v2 + 8) = x;
    v4 = *(_DWORD *)(v2 + 52) & 7;
    *(_DWORD *)(v2 + 56) = v4;
    (*(void ( **)(gbGfxManager *, int))(*(_DWORD *)*(void**)(gfxMgr) + 92))(gfxMgr, 96 * v4 + v2 + 60);
    (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                         + 172))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      0,
      0,
      3,
      -16777216,
      1065353216,
      0);
    v5 = (gbCamera *)*(gbCamera **)(v3 + 8);
    if ( v5 )
      (((gbCamera *)v5))->gbCamera::SetDimention(256, 192);
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
  float sv; // eax
  int v8; // eax
  float *v9; // edi
  float *p_eu; // ebx
  float eu; // eax
  unsigned int v12; // ebp
  float *v13; // edi
  float *v14; // ebx
  float v15; // eax
  gbDynVertBuf *DynVertBuf; // [esp+0x44] [ebp-0x48]
  struct gbTextureArray v17; // [esp+0x48] [ebp-0x44] BYREF

  if ( BYTE1(this->m_pDisplay) && LOBYTE(this->m_pDisplay) )
  {
    (*(void ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy) + 148))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      0,
      LODWORD(this[2].m_DefaultUVSet[5].ev));
    (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                         + 172))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      0,
      0,
      3,
      -16777216,
      1065353216,
      0);
    (((gbCamera *)this->m_pVertexBuffer))->gbCamera::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
    DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
    if ( (byte_DE93A8 & 1) == 0 )
    {
      v2 = (gbColorQuad *)&stru_DE9388;
      byte_DE93A8 |= 1u;
      v3 = 8;
      do
      {
        v2++->gbColorQuad::gbColorQuad();
        --v3;
      }
      while ( v3 );
      atexit(nullsub_16);
    }
    v4 = 158 - 8 * LODWORD(this->m_DefaultUVSet[2].sv);
    v5 = 0;
    v6 = (char *)&((gbColorQuad *)&stru_DE9388)->Color + 1;
    do
    {
      *(v6 - 1) = v4 / 2;
      *v6 = v4 / 2;
      v6[1] = v4 / 2;
      v6[2] = v4;
      v4 += 8;
      if ( v5 == LODWORD(this->m_DefaultUVSet[2].sv) )
        v4 = 102;
      v6 += 4;
      ++v5;
    }
    while ( (int)v6 < (int)byte_DE93A9 );
    sv = this->m_DefaultUVSet[2].sv;
    v17.nTex = 0;
    if ( LODWORD(sv) < 7 )
    {
      v8 = LODWORD(sv) + 1;
      if ( v8 < 8 )
      {
        v9 = (float *)(4 * v8 + 14586760);
        p_eu = (float *)&this->m_DefaultUVSet[6 * v8 + 2].eu;
        do
        {
          eu = this[2].m_DefaultUVSet[5].eu;
          this->m_DefaultUVSet[1].ev = *v9;
          v17.nTex = 1;
          v17.pTexPt[0] = (gbTexture *)p_eu;
          (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad((gbUIQuad *)&this->m_pAdditiveBlend, 1, (gbRenderEffect *)LODWORD(eu), &v17);
          ++v9;
          p_eu += 24;
        }
        while ( (int)v9 < (int)&byte_DE93A8 );
      }
    }
    v12 = 0;
    v13 = (float *)&stru_DE9388;
    v14 = (float *)&this->m_DefaultUVSet[2].eu;
    do
    {
      if ( (int)v13 < (int)&byte_DE93A8 )
      {
        v15 = this[2].m_DefaultUVSet[5].eu;
        this->m_DefaultUVSet[1].ev = *v13;
        v17.nTex = 1;
        v17.pTexPt[0] = (gbTexture *)v14;
        (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad((gbUIQuad *)&this->m_pAdditiveBlend, 1, (gbRenderEffect *)LODWORD(v15), &v17);
      }
      ++v12;
      ++v13;
      v14 += 24;
    }
    while ( v12 <= LODWORD(this->m_DefaultUVSet[2].sv) );
  }
}

// 0x004C6870
int * CEffectSystem::FillDefaultUVSet()
{
  int *result; // eax

  result = (int *)this;
  this->m_pDisplay = ((gbGfxManager *)0);
  LOBYTE(this->m_pVertexBuffer) = 0;
  this->m_pAlphaBlend = ((gbRenderEffect *)0);
  this->m_DefaultUVSet[0].su = 0.0f;
  this->m_DefaultUVSet[0].sv = 0.0f;
  this->m_DefaultUVSet[0].eu = NAN;
  this->m_DefaultUVSet[0].ev = NAN;
  this->m_DefaultUVSet[1].su = 0.0f;
  this->m_DefaultUVSet[1].sv = 0.0f;
  this->m_DefaultUVSet[1].eu = 0.0f;
  this->m_DefaultUVSet[7].su = 0.0f;
  this->m_DefaultUVSet[7].sv = 0.0f;
  this->m_DefaultUVSet[7].eu = 0.0f;
  this->m_DefaultUVSet[8].sv = 0.0f;
  this->m_DefaultUVSet[8].eu = 0.0f;
  this->m_DefaultUVSet[8].ev = 0.0f;
  this->m_DefaultUVSet[9].su = 0.0f;
  this->m_DefaultUVSet[9].sv = 0.0f;
  this->m_DefaultUVSet[9].eu = 0.0f;
  this->m_DefaultUVSet[9].ev = 0.0f;
  this->m_DefaultUVSet[10].su = 0.0f;
  this->m_DefaultUVSet[10].sv = 0.0f;
  this->m_DefaultUVSet[9].eu = 0.0f;
  this->m_DefaultUVSet[9].sv = 0.0f;
  this->m_DefaultUVSet[9].su = 0.0f;
  this->m_DefaultUVSet[10].sv = 0.0f;
  this->m_DefaultUVSet[10].su = 0.0f;
  this->m_DefaultUVSet[9].ev = 0.0f;
  this->m_DefaultUVSet[8].ev = 0.0f;
  this->m_DefaultUVSet[8].eu = 0.0f;
  this->m_DefaultUVSet[8].sv = 0.0f;
  this->m_DefaultUVSet[6].sv = 0.0f;
  this->m_DefaultUVSet[1].ev = 0.0f;
  this->m_DefaultUVSet[2].su = 0.0f;
  BYTE1(this->m_DefaultUVSet[2].ev) = 0;
  BYTE2(this->m_DefaultUVSet[2].ev) = 0;
  this->m_DefaultUVSet[2].sv = 0.0f;
  this->m_DefaultUVSet[2].eu = 0.0f;
  return result;
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
  for ( i = &this->m_DefaultUVSet[4].sv; *(_BYTE *)i; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pSrc);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = unk_C10D38;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffectSystem *)operator new(0x10C0u);
  if ( v9 )
    v10 = (((CEffectSystem *)v9))->CEffectSystem::FillDefaultUVSet();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = (unsigned long)v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pSrc);
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
            v16 = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)pCBUI) + 20) + 76) + 232) + 28);
            *v16 = -1092196762;
            v16[1] = -1092196762;
            v16[2] = -1092196762;
            v16[3] = 1065353216;
            v17 = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)pCBUI) + 20) + 76) + 452) + 28);
            *v17 = -1092196762;
            v17[1] = -1092196762;
            v17[2] = -1092196762;
            v17[3] = 1065353216;
            break;
          case 1027:
            v18 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)pCBUI) + 20) + 76) + 452) + 12;
            strcpy((char *)v18, "333?333?333?");
            *(_BYTE *)(v18 + 13) = 0;
            *(_WORD *)(v18 + 14) = 16256;
            break;
          case 1028:
            gfxMgr->fSelfIllum = 1.0;
            break;
          case 1208:
            IsModified = EditBoxIsModified(v8);
            *((_BYTE *)this->CEffectSystem::DestroyAllEffect() + 5) = IsModified;
            break;
          case 1209:
            *((_BYTE *)(((CEffectSystem *)((unsigned __int16)bReadOnly - 1026)))->CEffectSystem::DestroyAllEffect() + 5) = 0;
            break;
          default:
            break;
        }
      }
      else if ( (unsigned __int16)bReadOnly == 1023 )
      {
        v14 = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)pCBUI) + 20) + 76) + 232) + 28);
        *v14 = 1041865114;
        v14[1] = 1041865114;
        v14[2] = 1041865114;
        v14[3] = 1065353216;
        v15 = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)pCBUI) + 20) + 76) + 452) + 28);
        *v15 = 1041865114;
        v15[1] = 1041865114;
        v15[2] = 1041865114;
        v15[3] = 1065353216;
      }
      else if ( (unsigned __int16)bReadOnly > 0x3FCu )
      {
        if ( (unsigned __int16)bReadOnly == 1021 )
        {
          (((CCBUI *)pCBUI))->CCBUI::PopulateSceneList(hDlg);
        }
        else if ( (unsigned __int16)bReadOnly == 1022 )
        {
          v12 = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)pCBUI) + 20) + 76) + 232) + 28);
          *v12 = 0;
          v12[1] = 0;
          v12[2] = 0;
          v12[3] = 1065353216;
          v13 = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)pCBUI) + 20) + 76) + 452) + 28);
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
            byte_17A9933 = 1;
            break;
          case 1u:
            EndDialog(hDlg, 1);
            break;
          case 0x3F8u:
            byte_17A9930 = 1;
            break;
          case 0x3F9u:
            byte_17A9932 = 1;
            break;
        }
      }
LABEL_32:
      if ( bReadOnly == 1203 && *(_DWORD *)(nVal + 8) == -3 )
      {
        v21 = *(_DWORD *)(nVal + 12);
        if ( v21 != -1 )
          (((CCBUI *)pCBUI))->CCBUI::LoadSceneByIndex(v21);
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
    lParam[3] = (LPARAM)&unk_5D88F4;
    SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 100;
    lParam[3] = (LPARAM)&unk_5D88EC;
    SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParam);
    (((CCBUI *)pCBUI))->CCBUI::PopulateSceneList(hDlg);
    if ( hDlga )
    {
      LOBYTE(bReadOnly) = *((_BYTE *)this->CEffectSystem::DestroyAllEffect() + 5);
      EditBoxSetReadOnly(hDlga, bReadOnly);
      return 0;
    }
  }
  return 0;
}
