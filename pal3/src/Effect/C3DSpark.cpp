#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/C3DSpark.h"

// Unnamed globals (extern)
extern int dword_17A8440;
extern int dword_17A8444;
extern int dword_17A8448;
extern int dword_17A8450;
extern int dword_17A8458;
extern int dword_17A845C;
extern int dword_17A8460;
extern int dword_17A8464;
extern int dword_17A8468;
extern int dword_17A846C;
extern int dword_17A8470;
extern float flt_17A844C;
extern float flt_17A8454;

// 0x004D6670
C3DSpark::C3DSpark()
{
  int v2; // ebx
  gbGeomQuad *m_GeomQuad; // edi
  gbTexture *v4; // eax
  gbTextureArray *v5; // eax
  gbTexture *m_pRedBig; // ecx
  gbTexture *v7; // eax
  gbTextureArray *v8; // eax
  gbTexture *m_pRed16; // ecx
  gbTexture *v10; // eax
  gbTextureArray *v11; // eax
  gbTexture *m_pGreen16; // ecx
  gbTexture *v13; // eax
  gbTextureArray *v14; // eax
  gbTexture *m_pBlue16; // ecx
  gbTexture *v16; // eax
  gbTextureArray *v17; // eax
  gbTexture *m_pYellow16; // ecx
  float *p_sv; // eax
  int v20; // ecx
  char pExceptionObject[1024]; // [esp+0x30] [ebp-0x800] BYREF
  char ArgList[1024]; // [esp+0x430] [ebp-0x400] BYREF

  v2 = 128;
  m_GeomQuad = this->m_GeomQuad;
  do
  {
    --v2;
  }
  while ( v2 );
  memset(this, 0, sizeof(C3DSpark));
  this->m_pAdditiveBlend = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0);
  v4 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                      gfxMgr,
                      &pTarget.m_nTargetType + 98);
  this->m_pRedBig = v4;
  ((gbTexture *)v4)->LoadTexture(1);
  v5 = (gbTextureArray *)operator new(0x44u);
  if ( v5 )
  {
    m_pRedBig = this->m_pRedBig;
    v5->nTex = 1;
    v5->pTexPt[0] = m_pRedBig;
  }
  else
  {
    v5 = 0;
  }
  this->m_pRedBigArray = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 472, 37),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                      gfxMgr,
                      &pTarget.m_nTargetType + 83);
  this->m_pRed16 = v7;
  ((gbTexture *)v7)->LoadTexture(1);
  v8 = (gbTextureArray *)operator new(0x44u);
  if ( v8 )
  {
    m_pRed16 = this->m_pRed16;
    v8->nTex = 1;
    v8->pTexPt[0] = m_pRed16;
  }
  else
  {
    v8 = 0;
  }
  this->m_pRed16Array = v8;
  if ( !v8 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 472, 42),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                       gfxMgr,
                       &pTarget.m_nTargetType + 77);
  this->m_pGreen16 = v10;
  ((gbTexture *)v10)->LoadTexture(1);
  v11 = (gbTextureArray *)operator new(0x44u);
  if ( v11 )
  {
    m_pGreen16 = this->m_pGreen16;
    v11->nTex = 1;
    v11->pTexPt[0] = m_pGreen16;
  }
  else
  {
    v11 = 0;
  }
  this->m_pGreen16Array = v11;
  if ( !this->m_pRed16Array )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 472, 47),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                       gfxMgr,
                       &pTarget.m_nTargetType + 71);
  this->m_pBlue16 = v13;
  ((gbTexture *)v13)->LoadTexture(1);
  v14 = (gbTextureArray *)operator new(0x44u);
  if ( v14 )
  {
    m_pBlue16 = this->m_pBlue16;
    v14->nTex = 1;
    v14->pTexPt[0] = m_pBlue16;
  }
  else
  {
    v14 = 0;
  }
  this->m_pBlue16Array = v14;
  if ( !v14 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 472, 52),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                       gfxMgr,
                       &pTarget.m_nTargetType + 63);
  this->m_pYellow16 = v16;
  ((gbTexture *)v16)->LoadTexture(1);
  v17 = (gbTextureArray *)operator new(0x44u);
  if ( v17 )
  {
    m_pYellow16 = this->m_pYellow16;
    v17->nTex = 1;
    v17->pTexPt[0] = m_pYellow16;
  }
  else
  {
    v17 = 0;
  }
  this->m_pYellow16Array = v17;
  if ( !v17 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 472, 57),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  p_sv = &this->m_GeomQuad[0].sv;
  v20 = 128;
  do
  {
    p_sv[3] = NAN;
    *p_sv = 0.0;
    *(p_sv - 1) = 0.0;
    p_sv[2] = 1.0;
    p_sv[1] = 1.0;
    p_sv += 17;
    --v20;
  }
  while ( v20 );
  this;
}

// 0x004D6960
void C3DSpark::_C3DSpark()
{
  gbRenderEffect *m_pAdditiveBlend; // ecx
  gbRefObject *m_pRedBig; // ecx
  gbRefObject *m_pGreen16; // ecx
  gbRefObject *m_pBlue16; // ecx
  gbRefObject *m_pRed16; // ecx
  gbRefObject *m_pYellow16; // ecx

  m_pAdditiveBlend = this->m_pAdditiveBlend;
  if ( m_pAdditiveBlend )
  {
// [VFTABLE] ((gbRefObject *)&m_pAdditiveBlend->__vftable)->Release();
    this->m_pAdditiveBlend = 0;
  }
  m_pRedBig = (gbRefObject *)this->m_pRedBig;
  if ( m_pRedBig )
  {
    ((gbRefObject *)m_pRedBig)->Release();
    this->m_pRedBig = 0;
  }
  m_pGreen16 = (gbRefObject *)this->m_pGreen16;
  if ( m_pGreen16 )
  {
    ((gbRefObject *)m_pGreen16)->Release();
    this->m_pGreen16 = 0;
  }
  m_pBlue16 = (gbRefObject *)this->m_pBlue16;
  if ( m_pBlue16 )
  {
    ((gbRefObject *)m_pBlue16)->Release();
    this->m_pBlue16 = 0;
  }
  m_pRed16 = (gbRefObject *)this->m_pRed16;
  if ( m_pRed16 )
  {
    ((gbRefObject *)m_pRed16)->Release();
    this->m_pRed16 = 0;
  }
  m_pYellow16 = (gbRefObject *)this->m_pYellow16;
  if ( m_pYellow16 )
  {
    ((gbRefObject *)m_pYellow16)->Release();
    this->m_pYellow16 = 0;
  }
  if ( this->m_pRedBigArray )
  {
    operator delete(this->m_pRedBigArray);
    this->m_pRedBigArray = 0;
  }
  if ( this->m_pGreen16Array )
  {
    operator delete(this->m_pGreen16Array);
    this->m_pGreen16Array = 0;
  }
  if ( this->m_pBlue16Array )
  {
    operator delete(this->m_pBlue16Array);
    this->m_pBlue16Array = 0;
  }
  if ( this->m_pRed16Array )
  {
    operator delete(this->m_pRed16Array);
    this->m_pRed16Array = 0;
  }
  if ( this->m_pYellow16Array )
  {
    operator delete(this->m_pYellow16Array);
    this->m_pYellow16Array = 0;
  }
}

// 0x004D6A60
bool C3DSpark::CreateSingle(const void *pSpark)
{
  int v3; // eax
  _BYTE *i; // ecx

  v3 = 0;
  for ( i = &this->m_Spark[0]._tail_000[53]; *i; i += 56 )
  {
    if ( ++v3 >= 128 )
      return 0;
  }
  qmemcpy(&this->m_Spark[v3], pSpark, sizeof(this->m_Spark[v3]));
  this->m_Spark[v3]._tail_000[53] = 1;
  if ( v3 >= this->m_nCurrentSpark )
    this->m_nCurrentSpark = v3 + 1;
  return 1;
}

// 0x004D6AC0
void C3DSpark::CreateOne(int x, int y, int z)
{
  int v5; // eax
  long double v6; // st7
  float xa; // [esp+0x8] [ebp+0x4]

  dword_17A846C = 1090519040;
  dword_17A8464 = 1128792064;
  dword_17A8440 = x;
  dword_17A8444 = y;
  dword_17A8448 = z;
  dword_17A8458 = 0;
  dword_17A845C = -1046478848;
  dword_17A8460 = 0;
  dword_17A8468 = -1015414784;
  dword_17A8470 = 0;
  xa = (float)(rand() % 10);
  v5 = rand();
  dword_17A8450 = -1054867456;
  v6 = (double)(v5 % 5760 / 16) * 0.017453292;
  flt_17A844C = sin(v6) * xa;
  flt_17A8454 = cos(v6) * xa;
  this->CreateSingle(&dword_17A8440);
}

// 0x004D6BA0
_BYTE * C3DSpark::DestroyAll()
{
  _BYTE *result; // eax
  int v2; // edx

  result = &this->m_Spark[0]._tail_000[53];
  v2 = 128;
  do
  {
    *result = 0;
    result += 56;
    --v2;
  }
  while ( v2 );
  this->m_nCurrentSpark = 0;
  return result;
}

// 0x004D6BC0
void C3DSpark::Render(C3DSpark *this@<ecx>, )
{
  gbMatrixStack *v2; // ebx
  float *p_y; // esi
  float *v4; // edi
  gbMatrix4 *Top; // eax
  double v6; // st7
  double v7; // st6
  gbVec3D *v8; // [esp-0x4] [ebp-0x34]
  int v9; // [esp+0x0] [ebp-0x30]
  float v10; // [esp+0x8] [ebp-0x28]
  float v11; // [esp+0xC] [ebp-0x24]
  int v12; // [esp+0x10] [ebp-0x20]
  float v13; // [esp+0x1C] [ebp-0x14]
  float v14; // [esp+0x1C] [ebp-0x14]
  C3DSpark *v15; // [esp+0x20] [ebp-0x10]
  int v16; // [esp+0x24] [ebp-0xC]
  int v17; // [esp+0x28] [ebp-0x8]
  float v18; // [esp+0x2C] [ebp-0x4]

  v2 = gfxMgr->pMatrixStack[1];
v17 = 0;
  v16 = 0;
  if ( this->m_nCurrentSpark > 0 )
  {
    v8 = a2;
    p_y = &this->m_GeomQuad[0].vec[0].y;
    v4 = (float *)&this->m_Spark[0]._tail_000[4];
    do
    {
      if ( *((_BYTE *)v4 + 49) )
      {
        v10 = *(v4 - 1);
        v11 = *v4;
        v12 = *((_DWORD *)v4 + 1);
        Top = ((gbMatrixStack *)v2)->GetTop();
        ((gbMatrix4 *)Top)->Transform(v8, v9);
        v18 = v4[10] * 0.5;
        v6 = v10 - v18;
        *(p_y - 1) = v6;
        v7 = v11 + v18;
        *p_y = v7;
        *((_DWORD *)p_y + 1) = v12;
        v13 = v10 + v18;
        p_y[2] = v13;
        p_y[3] = v7;
        *((_DWORD *)p_y + 4) = v12;
        p_y[5] = v13;
        v14 = v11 - v18;
        p_y[6] = v14;
        *((_DWORD *)p_y + 7) = v12;
        p_y[8] = v6;
        p_y[9] = v14;
        *((_DWORD *)p_y + 10) = v12;
        *((_BYTE *)p_y + 63) = (int)v4[8];
        ++v17;
        this = v15;
        p_y += 17;
      }
      v4 += 14;
      ++v16;
    }
    while ( v16 < this->m_nCurrentSpark );
    if ( v17 > 0 )
    {
      ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
      ((gbMatrixStack *)v2)->Push();
      ((gbMatrixStack *)v2)->LoadIdentity();
      ((gbDynVertBuf *)this->m_GeomQuad)->RenderGeomQuad(v17, this->m_pAdditiveBlend, this->m_pRed16Array);
      ((gbMatrixStack *)v2)->Pop();
    }
  }
}

// 0x004D6D30
void C3DSpark::Update(float fDeltaTime)
{
  int v2; // esi
  float *v3; // edx
  int v4; // eax
  float v5; // [esp+0x4] [ebp-0x4]

  v2 = 0;
  if ( this->m_nCurrentSpark > 0 )
  {
    v3 = (float *)&this->m_Spark[0]._tail_000[12];
    do
    {
      if ( *((_BYTE *)v3 + 41) )
      {
        *v3 = fDeltaTime * v3[3] + *v3;
        v3[1] = fDeltaTime * v3[4] + v3[1];
        v3[2] = fDeltaTime * v3[5] + v3[2];
        *(v3 - 3) = fDeltaTime * *v3 + *(v3 - 3);
        *(v3 - 2) = fDeltaTime * v3[1] + *(v3 - 2);
        *(v3 - 1) = fDeltaTime * v3[2] + *(v3 - 1);
        v3[6] = fDeltaTime * v3[7] + v3[6];
        v5 = fDeltaTime * v3[9] + v3[8];
        v3[8] = v5;
        if ( -v5 >= *(v3 - 2) || v3[6] <= 1.0 || v3[6] > 255.0 || v5 < 0.0099999998 )
        {
          *((_BYTE *)v3 + 41) = 0;
          v4 = this->m_nCurrentSpark - 1;
          if ( v2 == v4 )
            this->m_nCurrentSpark = v4;
        }
      }
      ++v2;
      v3 += 14;
    }
    while ( v2 < this->m_nCurrentSpark );
  }
}
