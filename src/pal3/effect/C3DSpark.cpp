#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/C3DSpark.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co_11[];
extern char aEffectFlare2Bm[];
extern char aEffectFlare3Bm[];
extern char aEffectFlareblu[];
extern char aEffectFlarebri[];
extern char aEffectFlaregre[];
extern char aGfxscriptAddit[];
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
  char pExceptionObject[1024]; // [esp+30h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+430h] [ebp-400h] BYREF

  v2 = 128;
  m_GeomQuad = (gbGeomQuad *)this->m_GeomQuad;
  do
  {
    ArraySort((int)m_GeomQuad, 12, 4, gbVec3D::`default constructor closure');
    m_GeomQuad = (gbGeomQuad *)((char *)m_GeomQuad + 68);
    --v2;
  }
  while ( v2 );
  memset(this, 0, 0x3E30u);
  this->m_pAdditiveBlend = ((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptAddit, 0);
  v4 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 8))(
                      g_pGfxMgr,
                      aEffectFlare3Bm);
  this->m_pRedBig = v4;
  v4->LoadTexture(1);
  v5 = (gbTextureArray *)operator new(0x44u);
  if ( v5 )
  {
    m_pRedBig = (gbTexture *)this->m_pRedBig;
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
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 37),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 8))(
                      g_pGfxMgr,
                      aEffectFlare2Bm);
  this->m_pRed16 = v7;
  v7->LoadTexture(1);
  v8 = (gbTextureArray *)operator new(0x44u);
  if ( v8 )
  {
    m_pRed16 = (gbTexture *)this->m_pRed16;
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
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 42),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 8))(
                       g_pGfxMgr,
                       aEffectFlaregre);
  this->m_pGreen16 = v10;
  v10->LoadTexture(1);
  v11 = (gbTextureArray *)operator new(0x44u);
  if ( v11 )
  {
    m_pGreen16 = (gbTexture *)this->m_pGreen16;
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
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 47),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 8))(
                       g_pGfxMgr,
                       aEffectFlareblu);
  this->m_pBlue16 = v13;
  v13->LoadTexture(1);
  v14 = (gbTextureArray *)operator new(0x44u);
  if ( v14 )
  {
    m_pBlue16 = (gbTexture *)this->m_pBlue16;
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
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 52),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 8))(
                       g_pGfxMgr,
                       aEffectFlarebri);
  this->m_pYellow16 = v16;
  v16->LoadTexture(1);
  v17 = (gbTextureArray *)operator new(0x44u);
  if ( v17 )
  {
    m_pYellow16 = (gbTexture *)this->m_pYellow16;
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
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 57),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  p_sv = (float *)&this->m_GeomQuad[0].sv;
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
  this->m_Spark;
}

// 0x004D6960
C3DSpark::~C3DSpark()
{
  gbRenderEffect *m_pAdditiveBlend; // ecx
  gbTexture *m_pRedBig; // ecx
  gbTexture *m_pGreen16; // ecx
  gbTexture *m_pBlue16; // ecx
  gbTexture *m_pRed16; // ecx
  gbTexture *m_pYellow16; // ecx

  m_pAdditiveBlend = (gbRenderEffect *)this->m_pAdditiveBlend;
  if ( m_pAdditiveBlend )
  {
    ((gbRefObject *)m_pAdditiveBlend)->Release();
    this->m_pAdditiveBlend = 0;
  }
  m_pRedBig = (gbTexture *)this->m_pRedBig;
  if ( m_pRedBig )
  {
    ((gbRefObject *)m_pRedBig)->Release();
    this->m_pRedBig = 0;
  }
  m_pGreen16 = (gbTexture *)this->m_pGreen16;
  if ( m_pGreen16 )
  {
    ((gbRefObject *)m_pGreen16)->Release();
    this->m_pGreen16 = 0;
  }
  m_pBlue16 = (gbTexture *)this->m_pBlue16;
  if ( m_pBlue16 )
  {
    ((gbRefObject *)m_pBlue16)->Release();
    this->m_pBlue16 = 0;
  }
  m_pRed16 = (gbTexture *)this->m_pRed16;
  if ( m_pRed16 )
  {
    ((gbRefObject *)m_pRed16)->Release();
    this->m_pRed16 = 0;
  }
  m_pYellow16 = (gbTexture *)this->m_pYellow16;
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
char C3DSpark::CreateSingle(const void *a2)
{
  int v3; // eax
  char *i; // ecx

  v3 = 0;
  for ( i = &this->m_Spark[53]; *i; i += 56 )
  {
    if ( ++v3 >= 128 )
      return 0;
  }
  qmemcpy((char *)this + 56 * v3, a2, 0x38u);
  this->m_Spark[56 * v3 + 53] = 1;
  if ( v3 >= this->m_nCurrentSpark )
    this->m_nCurrentSpark = v3 + 1;
  return 1;
}

// 0x004D6AC0
char C3DSpark::CreateOne(int a2, int a3, int a4)
{
  int v5; // eax
  long double v6; // st7
  float a2a; // [esp+8h] [ebp+4h]

  dword_17A846C = 1090519040;
  dword_17A8464 = 1128792064;
  dword_17A8440 = a2;
  dword_17A8444 = a3;
  dword_17A8448 = a4;
  dword_17A8458 = 0;
  dword_17A845C = -1046478848;
  dword_17A8460 = 0;
  dword_17A8468 = -1015414784;
  dword_17A8470 = 0;
  a2a = (float)(rand() % 10);
  v5 = rand();
  dword_17A8450 = -1054867456;
  v6 = (double)(v5 % 5760 / 16) * 0.017453292;
  flt_17A844C = sin(v6) * a2a;
  flt_17A8454 = cos(v6) * a2a;
  return this->CreateSingle(&dword_17A8440);
}

// 0x004D6BA0
_BYTE * C3DSpark::DestroyAll()
{
  _BYTE *result; // eax
  int v2; // edx

  result = (_BYTE *)&this->m_Spark[53];
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
void C3DSpark::Render(int a1@<ecx>, struct gbVec3D *a2@<edi>)
{
  gbMatrixStack *v2; // ebx
  int v3; // esi
  int v4; // edi
  gbMatrix4 *Top; // eax
  double v6; // st7
  double v7; // st6
  struct gbVec3D *v8; // [esp-4h] [ebp-34h]
  int v9; // [esp+0h] [ebp-30h]
  float v10; // [esp+8h] [ebp-28h]
  float v11; // [esp+Ch] [ebp-24h]
  int v12; // [esp+10h] [ebp-20h]
  float v13; // [esp+1Ch] [ebp-14h]
  float v14; // [esp+1Ch] [ebp-14h]
  int v15; // [esp+20h] [ebp-10h]
  int v16; // [esp+24h] [ebp-Ch]
  int v17; // [esp+28h] [ebp-8h]
  float v18; // [esp+2Ch] [ebp-4h]

  v2 = (gbMatrixStack *)g_pGfxMgr->pMatrixStack[1];
  v15 = a1;
  v17 = 0;
  v16 = 0;
  if ( *(int *)(a1 + 7168) > 0 )
  {
    v8 = a2;
    v3 = a1 + 7220;
    v4 = a1 + 4;
    do
    {
      if ( *(_BYTE *)(v4 + 49) )
      {
        v10 = *(float *)(v4 - 4);
        v11 = *(float *)v4;
        v12 = *(_DWORD *)(v4 + 4);
        Top = (gbMatrix4 *)v2->GetTop();
        Top->Transform(v8, v9);
        v18 = *(float *)(v4 + 40) * 0.5;
        v6 = v10 - v18;
        *(float *)(v3 - 4) = v6;
        v7 = v11 + v18;
        *(float *)v3 = v7;
        *(_DWORD *)(v3 + 4) = v12;
        v13 = v10 + v18;
        *(float *)(v3 + 8) = v13;
        *(float *)(v3 + 12) = v7;
        *(_DWORD *)(v3 + 16) = v12;
        *(float *)(v3 + 20) = v13;
        v14 = v11 - v18;
        *(float *)(v3 + 24) = v14;
        *(_DWORD *)(v3 + 28) = v12;
        *(float *)(v3 + 32) = v6;
        *(float *)(v3 + 36) = v14;
        *(_DWORD *)(v3 + 40) = v12;
        *(_BYTE *)(v3 + 63) = (int)*(float *)(v4 + 32);
        ++v17;
        a1 = v15;
        v3 += 68;
      }
      v4 += 56;
      ++v16;
    }
    while ( v16 < *(_DWORD *)(a1 + 7168) );
    if ( v17 > 0 )
    {
      ((gbVertPoolMgr *)g_pGfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
      v2->Push();
      v2->LoadIdentity();
      ((gbDynVertBuf *)(v15 + 7216))->RenderGeomQuad(v17, *(struct gbRenderEffect **)(v15 + 7172), *(struct gbTextureArray **)(v15 + 7204));
      v2->Pop();
    }
  }
}

// 0x004D6D30
int C3DSpark::Update(float a2)
{
  int result; // eax
  int v3; // esi
  char *v4; // edx
  int v5; // eax
  float v6; // [esp+4h] [ebp-4h]

  result = this->m_nCurrentSpark;
  v3 = 0;
  if ( result > 0 )
  {
    v4 = (char *)&this->m_Spark[12];
    do
    {
      if ( v4[41] )
      {
        *(float *)v4 = a2 * *((float *)v4 + 3) + *(float *)v4;
        *((float *)v4 + 1) = a2 * *((float *)v4 + 4) + *((float *)v4 + 1);
        *((float *)v4 + 2) = a2 * *((float *)v4 + 5) + *((float *)v4 + 2);
        *((float *)v4 - 3) = a2 * *(float *)v4 + *((float *)v4 - 3);
        *((float *)v4 - 2) = a2 * *((float *)v4 + 1) + *((float *)v4 - 2);
        *((float *)v4 - 1) = a2 * *((float *)v4 + 2) + *((float *)v4 - 1);
        *((float *)v4 + 6) = a2 * *((float *)v4 + 7) + *((float *)v4 + 6);
        v6 = a2 * *((float *)v4 + 9) + *((float *)v4 + 8);
        *((float *)v4 + 8) = v6;
        if ( -v6 >= *((float *)v4 - 2) || *((float *)v4 + 6) <= 1.0 || *((float *)v4 + 6) > 255.0 || v6 < 0.0099999998 )
        {
          v4[41] = 0;
          v5 = this->m_nCurrentSpark - 1;
          if ( v3 == v5 )
            this->m_nCurrentSpark = v5;
        }
      }
      result = this->m_nCurrentSpark;
      ++v3;
      v4 += 56;
    }
    while ( v3 < result );
  }
  return result;
}
