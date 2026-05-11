#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int sub_4C5D00(...);
int sub_4C5D70(...);
int sub_4C5FA0(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Ef_0[];
extern char aGfxscriptTrail[];
extern unsigned char byte_DE93A8;
extern unsigned char byte_DE93A9;
extern unsigned char byte_DE96F4;
extern int dword_DE9384;
extern int dword_DE997C;
extern float flt_DE9978;
extern int nullsub_16;
extern void *off_56F844;
extern void *off_56F86C;
extern void *off_56F878;
extern void *off_56F8B4;
extern int stru_DE93B0;
extern int unk_DE9388;
extern int unk_DE9389;
extern int unknown_libname_446;

// 0x004C61A0
CEffectSystem::CEffectSystem(int a2)
{
  gbTexture *v3; // eax
  _DWORD *result; // eax
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(**(_DWORD **)dword_DE9384 + 8))(*(_DWORD *)dword_DE9384, a2);
  *((_DWORD *)this + 61448) = v3;
  v3->LoadTexture(1);
  result = (_DWORD *)operator new(0x44u);
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
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Ef_0, 761),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result;
}

// 0x004C6240
CEffectSystem::~CEffectSystem()
{
  sub_4C5D00(this, a2);
  this->m_pDisplay = (gbGfxManager *)&off_56F844;
  this->m_pAdditiveBlend = (gbRenderEffect *)1;
  &this->m_pDisplay;
}

// 0x004C6260
_DWORD * CEffectSystem::Reset(CEffectSystem *Block, char a2)
{
  Block->Init();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return &Block->m_pDisplay;
}

// 0x004C6280
// attributes: thunk
int CEffectSystem::Init()
{
  int result; // eax

  sub_4C5D70((int)this);
  return result;
}

// 0x004C6290
char CEffectSystem::Destroy(int a2, int a3, int a4, int a5, int a6)
{
  _BYTE v7[16]; // [esp+4h] [ebp-30h] BYREF
  int v8; // [esp+14h] [ebp-20h]
  int v9; // [esp+18h] [ebp-1Ch]
  int v10; // [esp+1Ch] [ebp-18h]
  int v11; // [esp+20h] [ebp-14h]
  int v12; // [esp+24h] [ebp-10h]
  int v13; // [esp+28h] [ebp-Ch]
  int v14; // [esp+2Ch] [ebp-8h]

  v7[13] = 0;
  v7[14] = 0;
  v11 = a2;
  v14 = a5;
  v13 = a4;
  v12 = a3;
  v7[10] = 1;
  v7[8] = 1;
  v7[9] = 1;
  v7[12] = 16;
  v7[15] = 1;
  v10 = -1;
  v8 = a6;
  v9 = 0;
  sub_4C5FA0(this, v7);
  return 1;
}

// 0x004C6330
// attributes: thunk
int CEffectSystem::GetEffectIndex()
{
  return CEffectSystem::CreateEffect();
}

// 0x004C6340
int CEffectSystem::CreateEffect()
{
  dword_DE997C = 1094713344;
  return 1094713344;
}

// 0x004C6350
// attributes: thunk
void CEffectSystem::GetEffect()
{
  CEffectSystem::DestroyEffect();
}

// 0x004C6360
void CEffectSystem::DestroyEffect()
{
  flt_DE9978 = 12.0 + 12.0;
}

// 0x004C6370
int CEffectSystem::DestroyEffect()
{
  this->m_DefaultUVSet[2].su = NAN;
  this->m_DefaultUVSet[1].ev = 0.0;
  `eh vector constructor iterator'(
    (char *)&this->m_DefaultUVSet[2].ev,
    0x60u,
    8,
    gbTexture_D3D::gbTexture_D3D,
    gbTexture_D3D::~gbTexture_D3D);
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
  return (int)this;
}

// 0x004C6410
CEffectSystem *CEffectSystem::DestroyAllEffect()
{
  if ( (byte_DE96F4 & 1) == 0 )
  {
    byte_DE96F4 |= 1u;
    ((CEffectSystem *)&stru_DE93B0)->DestroyEffect();
    atexit(unknown_libname_446);
  }
  return &stru_DE93B0;
}

// 0x004C6460
char CEffectSystem::IsVisible()
{
  struct gbRenderEffect *v3; // eax
  int v4; // esi
  float *p_ev; // edi
  _DWORD v6[2]; // [esp+14h] [ebp-14h] BYREF
  int v7; // [esp+1Ch] [ebp-Ch]
  int v8; // [esp+20h] [ebp-8h]
  int v9; // [esp+24h] [ebp-4h]

  if ( !*((_DWORD *)this + 207) )
  {
    if ( (g_nGameFlags & 8) == 0 )
      return 0;
    v6[0] = 0;
    v6[1] = 0;
    v7 = 0;
    v8 = 0;
    v9 = 0;
    if ( !(*(int (**)(gbGfxManager *, _DWORD *, int))(*(_DWORD *)g_pGfxMgr->_vftable + 84))(g_pGfxMgr, v6, 1) )
      return 0;
    (*(void (**)(gbGfxManager *))(*(_DWORD *)g_pGfxMgr->_vftable + 88))(g_pGfxMgr);
    v3 = ((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptTrail, 0);
    *((_DWORD *)this + 207) = v3;
    if ( !v3 )
      return 0;
    if ( (*(int (__stdcall **)(_DWORD, _DWORD, char *))(**(_DWORD **)&g_pGfxMgr[1].InvViewMatrix[4] + 152))(
           *(_DWORD *)&g_pGfxMgr[1].InvViewMatrix[4],
           0,
           (char *)this + 832) < 0 )
      return 0;
    v4 = 0;
    p_ev = (float *)&this->m_DefaultUVSet[2].ev;
    do
    {
      if ( !(*(int (**)(float *, int, int, int))(*(_DWORD *)p_ev + 12))(p_ev, 256, 256, v7)
        || !(*(int (**)(gbGfxManager *, float *))(*(_DWORD *)g_pGfxMgr->_vftable + 92))(g_pGfxMgr, p_ev) )
      {
        return 0;
      }
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)&g_pGfxMgr[1].InvViewMatrix[4]
                                                                           + 172))(
        *(_DWORD *)&g_pGfxMgr[1].InvViewMatrix[4],
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
    if ( (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)&g_pGfxMgr[1].InvViewMatrix[4] + 148))(
           *(_DWORD *)&g_pGfxMgr[1].InvViewMatrix[4],
           0,
           *((_DWORD *)this + 208)) < 0 )
      return 0;
    LOBYTE(this->m_pVertexBuffer) = 1;
  }
  return 1;
}

// 0x004C65C0
void CEffectSystem::SetVisible(float a2)
{
  double v2; // st7
  char v4; // c0

  v2 = a2 + *(float *)&this->m_pDisplay;
  *(float *)&this->m_pDisplay = v2;
  if ( !v4 )
  {
    ++LODWORD(this->m_DefaultUVSet[2].sv);
    *(float *)&this->m_pDisplay = v2 - 0.02;
  }
}

// 0x004C65F0
void CEffectSystem::HandleViewMove(int a2)
{
  int v3; // eax
  gbRenderEffect *m_pAdditiveBlend; // ecx

  if ( BYTE1(this->m_pVertexBuffer) && LOBYTE(this->m_pVertexBuffer) )
  {
    if ( a2 )
      this->m_pAdditiveBlend = (gbRenderEffect *)a2;
    v3 = LODWORD(this->m_DefaultUVSet[2].sv) & 7;
    LODWORD(this->m_DefaultUVSet[2].eu) = v3;
    (*(void (**)(gbGfxManager *, float *))(*(_DWORD *)g_pGfxMgr->_vftable + 92))(
      g_pGfxMgr,
      &this->m_DefaultUVSet[6 * v3 + 2].ev);
    (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)&g_pGfxMgr[1].InvViewMatrix[4]
                                                                         + 172))(
      *(_DWORD *)&g_pGfxMgr[1].InvViewMatrix[4],
      0,
      0,
      3,
      -16777216,
      1065353216,
      0);
    m_pAdditiveBlend = (gbRenderEffect *)this->m_pAdditiveBlend;
    if ( m_pAdditiveBlend )
      ((gbCamera *)m_pAdditiveBlend)->SetDimention(256, 192);
  }
}

// 0x004C6670
char CEffectSystem::Update()
{
  float v2; // eax
  gbColorQuad *v3; // edi
  int v4; // ebx
  int v5; // ebx
  int v6; // edi
  _BYTE *v7; // ecx
  float eu; // eax
  int v9; // eax
  float *v10; // edi
  float *p_ev; // ebx
  struct gbRenderEffect *v12; // eax
  unsigned int v13; // ebp
  float *v14; // edi
  float *v15; // ebx
  struct gbRenderEffect *v16; // eax
  gbDynVertBuf *DynVertBuf; // [esp+44h] [ebp-48h]
  struct gbTextureArray v19; // [esp+48h] [ebp-44h] BYREF

  LOBYTE(v2) = BYTE1(this->m_pVertexBuffer);
  if ( LOBYTE(v2) )
  {
    LOBYTE(v2) = this->m_pVertexBuffer;
    if ( LOBYTE(v2) )
    {
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)&g_pGfxMgr[1].InvViewMatrix[4] + 148))(
        *(_DWORD *)&g_pGfxMgr[1].InvViewMatrix[4],
        0,
        *((_DWORD *)this + 208));
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)&g_pGfxMgr[1].InvViewMatrix[4]
                                                                           + 172))(
        *(_DWORD *)&g_pGfxMgr[1].InvViewMatrix[4],
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      ((gbCamera *)this->m_pAdditiveBlend)->SetDimention(g_pGameTime, g_pAbsTime);
      DynVertBuf = ((gbVertPoolMgr *)g_pGfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
      if ( (byte_DE93A8 & 1) == 0 )
      {
        v3 = (gbColorQuad *)&unk_DE9388;
        byte_DE93A8 |= 1u;
        v4 = 8;
        do
        {
          v3->gbColorQuad();
          v3 = (gbColorQuad *)((char *)v3 + 4);
          --v4;
        }
        while ( v4 );
        atexit(nullsub_16);
      }
      v5 = 158 - 8 * LODWORD(this->m_DefaultUVSet[2].eu);
      v6 = 0;
      v7 = (_BYTE *)&unk_DE9389;
      do
      {
        *(v7 - 1) = v5 / 2;
        * v7 = (*)v5 / 2;
        v7[1] = v5 / 2;
        v7[2] = v5;
        v5 += 8;
        if ( v6 == LODWORD(this->m_DefaultUVSet[2].eu) )
          v5 = 102;
        v7 += 4;
        ++v6;
      }
      while ( (int)v7 < (int)byte_DE93A9 );
      eu = this->m_DefaultUVSet[2].eu;
      v19.nTex = 0;
      if ( LODWORD(eu) < 7 )
      {
        v9 = LODWORD(eu) + 1;
        if ( v9 < 8 )
        {
          v10 = (float *)(4 * v9 + 14586760);
          p_ev = (float *)&this->m_DefaultUVSet[6 * v9 + 2].ev;
          do
          {
            v12 = (struct gbRenderEffect *)*((_DWORD *)this + 207);
            this->m_DefaultUVSet[2].su = *v10;
            v19.nTex = 1;
            v19.pTexPt[0] = (gbTexture *)p_ev;
            DynVertBuf->RenderUIQuad((struct gbUIQuad *)&this->m_pAlphaBlend, 1, v12, &v19);
            ++v10;
            p_ev += 24;
          }
          while ( (int)v10 < (int)&byte_DE93A8 );
        }
      }
      v13 = 0;
      v14 = (float *)&unk_DE9388;
      v15 = (float *)&this->m_DefaultUVSet[2].ev;
      do
      {
        if ( (int)v14 < (int)&byte_DE93A8 )
        {
          v16 = (struct gbRenderEffect *)*((_DWORD *)this + 207);
          this->m_DefaultUVSet[2].su = *v14;
          v19.nTex = 1;
          v19.pTexPt[0] = (gbTexture *)v15;
          DynVertBuf->RenderUIQuad((struct gbUIQuad *)&this->m_pAlphaBlend, 1, v16, &v19);
        }
        v2 = this->m_DefaultUVSet[2].eu;
        ++v13;
        ++v14;
        v15 += 24;
      }
      while ( v13 <= LODWORD(v2) );
    }
  }
  return LOBYTE(v2);
}

// 0x004C6870
_DWORD * CEffectSystem::FillDefaultUVSet()
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
  this->m_pAlphaBlend = (gbRenderEffect *)&off_56F8B4;
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
  this->m_pDisplay = (gbGfxManager *)&off_56F878;
  this->m_pAlphaBlend = (gbRenderEffect *)&off_56F86C;
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
  return &this->m_pDisplay;
}
