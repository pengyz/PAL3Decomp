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
  float *p_eu; // edi
  gbTexture *v4; // eax
  float *v5; // eax
  float y; // ecx
  gbTexture *v7; // eax
  float *v8; // eax
  float v9; // ecx
  gbTexture *v10; // eax
  float *v11; // eax
  float z; // ecx
  gbTexture *v13; // eax
  float *v14; // eax
  float x; // ecx
  gbTexture *v16; // eax
  float *v17; // eax
  float su; // ecx
  float *p_z; // eax
  int v20; // ecx
  char pExceptionObject[1024]; // [esp+30h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+430h] [ebp-400h] BYREF

  v2 = 128;
  p_eu = (float *)&this->m_GeomQuad[75].eu;
  do
  {
    ArraySort((int)p_eu, 12, 4, gbVec3D::`default constructor closure');
    p_eu += 17;
    --v2;
  }
  while ( v2 );
  memset(this, 0, 0x3E30u);
  LODWORD(this->m_GeomQuad[75].vec[1].x) = ((gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200))->NewRenderEffect(aGfxscriptAddit, 0);
  v4 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                      g_Input.KeyInfo[177].Data,
                      aEffectFlare3Bm);
  LODWORD(this->m_GeomQuad[75].vec[1].y) = v4;
  v4->LoadTexture(1);
  v5 = (float *)operator new(0x44u);
  if ( v5 )
  {
    y = this->m_GeomQuad[75].vec[1].y;
    *((_DWORD *)v5 + 16) = 1;
    *v5 = y;
  }
  else
  {
    v5 = 0;
  }
  LODWORD(this->m_GeomQuad[75].vec[1].z) = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 37),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                      g_Input.KeyInfo[177].Data,
                      aEffectFlare2Bm);
  LODWORD(this->m_GeomQuad[75].vec[3].y) = v7;
  v7->LoadTexture(1);
  v8 = (float *)operator new(0x44u);
  if ( v8 )
  {
    v9 = this->m_GeomQuad[75].vec[3].y;
    *((_DWORD *)v8 + 16) = 1;
    *v8 = v9;
  }
  else
  {
    v8 = 0;
  }
  LODWORD(this->m_GeomQuad[75].vec[3].z) = v8;
  if ( !v8 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 42),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                       g_Input.KeyInfo[177].Data,
                       aEffectFlaregre);
  LODWORD(this->m_GeomQuad[75].vec[2].z) = v10;
  v10->LoadTexture(1);
  v11 = (float *)operator new(0x44u);
  if ( v11 )
  {
    z = this->m_GeomQuad[75].vec[2].z;
    *((_DWORD *)v11 + 16) = 1;
    *v11 = z;
  }
  else
  {
    v11 = 0;
  }
  LODWORD(this->m_GeomQuad[75].vec[3].x) = v11;
  if ( !LODWORD(this->m_GeomQuad[75].vec[3].z) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 47),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                       g_Input.KeyInfo[177].Data,
                       aEffectFlareblu);
  LODWORD(this->m_GeomQuad[75].vec[2].x) = v13;
  v13->LoadTexture(1);
  v14 = (float *)operator new(0x44u);
  if ( v14 )
  {
    x = this->m_GeomQuad[75].vec[2].x;
    *((_DWORD *)v14 + 16) = 1;
    *v14 = x;
  }
  else
  {
    v14 = 0;
  }
  LODWORD(this->m_GeomQuad[75].vec[2].y) = v14;
  if ( !v14 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 52),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                       g_Input.KeyInfo[177].Data,
                       aEffectFlarebri);
  LODWORD(this->m_GeomQuad[75].su) = v16;
  v16->LoadTexture(1);
  v17 = (float *)operator new(0x44u);
  if ( v17 )
  {
    su = this->m_GeomQuad[75].su;
    *((_DWORD *)v17 + 16) = 1;
    *v17 = su;
  }
  else
  {
    v17 = 0;
  }
  LODWORD(this->m_GeomQuad[75].sv) = v17;
  if ( !v17 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_11, 57),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  p_z = (float *)&this->m_GeomQuad[76].vec[1].z;
  v20 = 128;
  do
  {
    p_z[3] = NAN;
    *p_z = 0.0;
    *(p_z - 1) = 0.0;
    p_z[2] = 1.0;
    p_z[1] = 1.0;
    p_z += 17;
    --v20;
  }
  while ( v20 );
  this->m_Spark;
}

// 0x004D6960
C3DSpark::~C3DSpark()
{
  float x; // ecx
  float y; // ecx
  float z; // ecx
  float v5; // ecx
  float v6; // ecx
  float su; // ecx

  x = this->m_GeomQuad[75].vec[1].x;
  if ( x != 0.0 )
  {
    ((gbRefObject *)LODWORD(x))->Release();
    this->m_GeomQuad[75].vec[1].x = 0.0;
  }
  y = this->m_GeomQuad[75].vec[1].y;
  if ( y != 0.0 )
  {
    ((gbRefObject *)LODWORD(y))->Release();
    this->m_GeomQuad[75].vec[1].y = 0.0;
  }
  z = this->m_GeomQuad[75].vec[2].z;
  if ( z != 0.0 )
  {
    ((gbRefObject *)LODWORD(z))->Release();
    this->m_GeomQuad[75].vec[2].z = 0.0;
  }
  v5 = this->m_GeomQuad[75].vec[2].x;
  if ( v5 != 0.0 )
  {
    ((gbRefObject *)LODWORD(v5))->Release();
    this->m_GeomQuad[75].vec[2].x = 0.0;
  }
  v6 = this->m_GeomQuad[75].vec[3].y;
  if ( v6 != 0.0 )
  {
    ((gbRefObject *)LODWORD(v6))->Release();
    this->m_GeomQuad[75].vec[3].y = 0.0;
  }
  su = this->m_GeomQuad[75].su;
  if ( su != 0.0 )
  {
    ((gbRefObject *)LODWORD(su))->Release();
    this->m_GeomQuad[75].su = 0.0;
  }
  if ( LODWORD(this->m_GeomQuad[75].vec[1].z) )
  {
    operator delete((void *)LODWORD(this->m_GeomQuad[75].vec[1].z));
    this->m_GeomQuad[75].vec[1].z = 0.0;
  }
  if ( LODWORD(this->m_GeomQuad[75].vec[3].x) )
  {
    operator delete((void *)LODWORD(this->m_GeomQuad[75].vec[3].x));
    this->m_GeomQuad[75].vec[3].x = 0.0;
  }
  if ( LODWORD(this->m_GeomQuad[75].vec[2].y) )
  {
    operator delete((void *)LODWORD(this->m_GeomQuad[75].vec[2].y));
    this->m_GeomQuad[75].vec[2].y = 0.0;
  }
  if ( LODWORD(this->m_GeomQuad[75].vec[3].z) )
  {
    operator delete((void *)LODWORD(this->m_GeomQuad[75].vec[3].z));
    this->m_GeomQuad[75].vec[3].z = 0.0;
  }
  if ( LODWORD(this->m_GeomQuad[75].sv) )
  {
    operator delete((void *)LODWORD(this->m_GeomQuad[75].sv));
    this->m_GeomQuad[75].sv = 0.0;
  }
}

// 0x004D6A60
char C3DSpark::CreateSingle(const void *a2)
{
  int v3; // eax
  _BYTE *i; // ecx

  v3 = 0;
  for ( i = (char *)&this->m_Spark[13] + 1; *i; i += 56 )
  {
    if ( ++v3 >= 128 )
      return 0;
  }
  qmemcpy((char *)this + 56 * v3, a2, 0x38u);
  BYTE1(this->m_Spark[14 * v3 + 13]) = 1;
  if ( v3 >= SLODWORD(this->m_GeomQuad[75].vec[0].z) )
    LODWORD(this->m_GeomQuad[75].vec[0].z) = v3 + 1;
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

  result = (char *)&this->m_Spark[13] + 1;
  v2 = 128;
  do
  {
    *result = 0;
    result += 56;
    --v2;
  }
  while ( v2 );
  this->m_GeomQuad[75].vec[0].z = 0.0;
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

  v2 = (gbMatrixStack *)*(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 216);
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
      ((gbVertPoolMgr *)*(gbVertPoolMgr **)(g_Input.KeyInfo[177].Data + 196))->GetDynVertBuf(0x15u);
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
  __int32 *v4; // edx
  float v5; // eax
  float v6; // [esp+4h] [ebp-4h]

  result = LODWORD(this->m_GeomQuad[75].vec[0].z);
  v3 = 0;
  if ( result > 0 )
  {
    v4 = (__int32 *)&this->m_Spark[3];
    do
    {
      if ( *((_BYTE *)v4 + 41) )
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
          *((_BYTE *)v4 + 41) = 0;
          LODWORD(v5) = LODWORD(this->m_GeomQuad[75].vec[0].z) - 1;
          if ( v3 == LODWORD(v5) )
            this->m_GeomQuad[75].vec[0].z = v5;
        }
      }
      result = LODWORD(this->m_GeomQuad[75].vec[0].z);
      ++v3;
      v4 += 14;
    }
    while ( v3 < result );
  }
  return result;
}
