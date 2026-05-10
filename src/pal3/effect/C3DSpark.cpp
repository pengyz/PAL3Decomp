#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/C3DSpark.h"

// 0x004D6670
_DWORD * sub_4D6670()
{
  int v2; // ebx
  int v3; // edi
  gbTexture *v4; // eax
  _DWORD *v5; // eax
  int v6; // ecx
  gbTexture *v7; // eax
  _DWORD *v8; // eax
  int v9; // ecx
  gbTexture *v10; // eax
  _DWORD *v11; // eax
  int v12; // ecx
  gbTexture *v13; // eax
  _DWORD *v14; // eax
  int v15; // ecx
  gbTexture *v16; // eax
  _DWORD *v17; // eax
  int v18; // ecx
  _DWORD *v19; // eax
  int v20; // ecx
  char pExceptionObject[1024]; // [esp+30h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+430h] [ebp-400h] BYREF

  v2 = 128;
  v3 = (int)(this + 1804);
  do
  {
    ArraySort(v3, 12, 4, (int (__thiscall *)(int))gbVec3D::`default constructor closure');
    v3 += 68;
    --v2;
  }
  while ( v2 );
  memset(this, 0, 0x3E30u);
  *(this + 1793) = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(g_pGfxManager + 200), aGfxscriptAddit, 0);
  v4 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aEffectFlare3Bm);
  *(this + 1794) = v4;
  v4->LoadTexture(1);
  v5 = operator new(0x44u);
  if ( v5 )
  {
    v6 = *(this + 1794);
    v5[16] = 1;
    *v5 = v6;
  }
  else
  {
    v5 = 0;
  }
  *(this + 1795) = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_11, 37),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aEffectFlare2Bm);
  *(this + 1800) = v7;
  v7->LoadTexture(1);
  v8 = operator new(0x44u);
  if ( v8 )
  {
    v9 = *(this + 1800);
    v8[16] = 1;
    *v8 = v9;
  }
  else
  {
    v8 = 0;
  }
  *(this + 1801) = v8;
  if ( !v8 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_11, 42),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                       g_pGfxManager,
                       aEffectFlaregre);
  *(this + 1798) = v10;
  v10->LoadTexture(1);
  v11 = operator new(0x44u);
  if ( v11 )
  {
    v12 = *(this + 1798);
    v11[16] = 1;
    *v11 = v12;
  }
  else
  {
    v11 = 0;
  }
  *(this + 1799) = v11;
  if ( !*(this + 1801) )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_11, 47),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                       g_pGfxManager,
                       aEffectFlareblu);
  *(this + 1796) = v13;
  v13->LoadTexture(1);
  v14 = operator new(0x44u);
  if ( v14 )
  {
    v15 = *(this + 1796);
    v14[16] = 1;
    *v14 = v15;
  }
  else
  {
    v14 = 0;
  }
  *(this + 1797) = v14;
  if ( !v14 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_11, 52),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                       g_pGfxManager,
                       aEffectFlarebri);
  *(this + 1802) = v16;
  v16->LoadTexture(1);
  v17 = operator new(0x44u);
  if ( v17 )
  {
    v18 = *(this + 1802);
    v17[16] = 1;
    *v17 = v18;
  }
  else
  {
    v17 = 0;
  }
  *(this + 1803) = v17;
  if ( !v17 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_11, 57),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v19 = this + 1817;
  v20 = 128;
  do
  {
    v19[3] = -1;
    *v19 = 0;
    *(v19 - 1) = 0;
    v19[2] = 1065353216;
    v19[1] = 1065353216;
    v19 += 17;
    --v20;
  }
  while ( v20 );
  return this;
}

// 0x004D6960
void sub_4D6960(int this)
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *v5; // ecx
  gbRefObject *v6; // ecx
  gbRefObject *v7; // ecx

  v2 = *(gbRefObject **)(this + 7172);
  if ( v2 )
  {
    v2->Release();
    *(_DWORD *)(this + 7172) = 0;
  }
  v3 = *(gbRefObject **)(this + 7176);
  if ( v3 )
  {
    v3->Release();
    *(_DWORD *)(this + 7176) = 0;
  }
  v4 = *(gbRefObject **)(this + 7192);
  if ( v4 )
  {
    v4->Release();
    *(_DWORD *)(this + 7192) = 0;
  }
  v5 = *(gbRefObject **)(this + 7184);
  if ( v5 )
  {
    v5->Release();
    *(_DWORD *)(this + 7184) = 0;
  }
  v6 = *(gbRefObject **)(this + 7200);
  if ( v6 )
  {
    v6->Release();
    *(_DWORD *)(this + 7200) = 0;
  }
  v7 = *(gbRefObject **)(this + 7208);
  if ( v7 )
  {
    v7->Release();
    *(_DWORD *)(this + 7208) = 0;
  }
  if ( *(_DWORD *)(this + 7180) )
  {
    operator delete(*(void **)(this + 7180));
    *(_DWORD *)(this + 7180) = 0;
  }
  if ( *(_DWORD *)(this + 7196) )
  {
    operator delete(*(void **)(this + 7196));
    *(_DWORD *)(this + 7196) = 0;
  }
  if ( *(_DWORD *)(this + 7188) )
  {
    operator delete(*(void **)(this + 7188));
    *(_DWORD *)(this + 7188) = 0;
  }
  if ( *(_DWORD *)(this + 7204) )
  {
    operator delete(*(void **)(this + 7204));
    *(_DWORD *)(this + 7204) = 0;
  }
  if ( *(_DWORD *)(this + 7212) )
  {
    operator delete(*(void **)(this + 7212));
    *(_DWORD *)(this + 7212) = 0;
  }
}

// 0x004D6A60
char sub_4D6A60(const void *a2)
{
  int v3; // eax
  _BYTE *i; // ecx

  v3 = 0;
  for ( i = (char *)this + 53; *i; i += 56 )
  {
    if ( ++v3 >= 128 )
      return 0;
  }
  qmemcpy(this + 14 * v3, a2, 0x38u);
  *((_BYTE *)this + 56 * v3 + 53) = 1;
  if ( v3 >= *(this + 1792) )
    *(this + 1792) = v3 + 1;
  return 1;
}

// 0x004D6AC0
char sub_4D6AC0(int a2, int a3, int a4)
{
  int v5; // eax
  long double v6; // st7
  float v8; // [esp+8h] [ebp+4h]

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
  v8 = (float)(rand() % 10);
  v5 = rand();
  dword_17A8450 = -1054867456;
  v6 = (double)(v5 % 5760 / 16) * 0.017453292;
  flt_17A844C = sin(v6) * v8;
  flt_17A8454 = cos(v6) * v8;
  return this->CreateSingle(&dword_17A8440);
}

// 0x004D6BA0
_BYTE * sub_4D6BA0()
{
  _BYTE *result; // eax
  int v2; // edx

  result = (char *)this + 53;
  v2 = 128;
  do
  {
    *result = 0;
    result += 56;
    --v2;
  }
  while ( v2 );
  *(this + 1792) = 0;
  return result;
}

// 0x004D6BC0
void __usercall sub_4D6BC0(int a1@<ecx>, struct gbVec3D *a2@<edi>)
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

  v2 = *(gbMatrixStack **)(g_pGfxManager + 216);
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
        Top = v2->GetTop();
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
      gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x15u);
      v2->Push();
      v2->LoadIdentity();
      (struct gbGeomQuad *->RenderGeomQuad()(v15 + 7216),
        v17,
        *(struct gbRenderEffect **)(v15 + 7172),
        *(struct gbTextureArray **)(v15 + 7204));
      v2->Pop();
    }
  }
}

// 0x004D6D30
int sub_4D6D30(float a2)
{
  int result; // eax
  int v3; // esi
  float *v4; // edx
  int v5; // eax
  float v6; // [esp+4h] [ebp-4h]

  result = *((_DWORD *)this + 1792);
  v3 = 0;
  if ( result > 0 )
  {
    v4 = this + 3;
    do
    {
      if ( *((_BYTE *)v4 + 41) )
      {
        *v4 = a2 * v4[3] + *v4;
        v4[1] = a2 * v4[4] + v4[1];
        v4[2] = a2 * v4[5] + v4[2];
        *(v4 - 3) = a2 * *v4 + *(v4 - 3);
        *(v4 - 2) = a2 * v4[1] + *(v4 - 2);
        *(v4 - 1) = a2 * v4[2] + *(v4 - 1);
        v4[6] = a2 * v4[7] + v4[6];
        v6 = a2 * v4[9] + v4[8];
        v4[8] = v6;
        if ( -v6 >= *(v4 - 2) || v4[6] <= 1.0 || v4[6] > 255.0 || v6 < 0.0099999998 )
        {
          *((_BYTE *)v4 + 41) = 0;
          v5 = *((_DWORD *)this + 1792) - 1;
          if ( v3 == v5 )
            *((_DWORD *)this + 1792) = v5;
        }
      }
      result = *((_DWORD *)this + 1792);
      ++v3;
      v4 += 14;
    }
    while ( v3 < result );
  }
  return result;
}
