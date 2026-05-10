#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffectSystem.h"

// Forward declarations for unnamed functions
int sub_4C5D00(...);
int sub_4C5D70(...);
int sub_4C5FA0(...);
int sub_4C61A0(...);
int sub_4C6240(...);
int sub_4C6260(...);
int sub_4C6290(...);
int sub_4C6340(...);
int sub_4C6360(...);
int sub_4C6370(...);
int sub_4C6410(...);
int sub_4C6460(...);
int sub_4C65C0(...);
int sub_4C65F0(...);
int sub_4C6670(...);
int sub_4C6870(...);

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
extern void *off_56F844;
extern void *off_56F86C;
extern void *off_56F878;
extern void *off_56F8B4;
extern int unk_DE9388;
extern int unk_DE9389;
extern int unk_DE93B0;

// 0x004C61A0
_DWORD * sub_4C61A0(int a2)
{
  gbTexture *v3; // eax
  _DWORD *result; // eax
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(**(_DWORD **)dword_DE9384 + 8))(*(_DWORD *)dword_DE9384, a2);
  *((_DWORD *)this + 61448) = v3;
  v3->LoadTexture(1);
  result = operator new(0x44u);
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
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Ef_0, 761),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004C6240
_DWORD * sub_4C6240(int a2)
{
  sub_4C5D00(this, a2);
  *this = &off_56F844;
  *((_DWORD *)this + 2) = 1;
  return this;
}

// 0x004C6260
_DWORD * sub_4C6260(_DWORD *Block, char a2)
{
  Block->Init();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x004C6280
// attributes: thunk
int CEffectSystem::Init(_DWORD *this)
{
  return sub_4C5D70(this);
}

// 0x004C6290
char sub_4C6290(int a2, int a3, int a4, int a5, int a6)
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
int sub_4C6340()
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
void sub_4C6360()
{
  flt_DE9978 = 12.0 + 12.0;
}

// 0x004C6370
int sub_4C6370(int _this)
{
  *(_DWORD *)(this + 48) = -1;
  *(_DWORD *)(this + 44) = 0;
  `eh vector constructor iterator'(
    (void *)(this + 60),
    0x60u,
    8,
    gbTexture_D3D::gbTexture_D3D,
    gbTexture_D3D::~gbTexture_D3D);
  *(_DWORD *)(this + 832) = 0;
  *(_DWORD *)(this + 52) = 0;
  *(_DWORD *)(this + 56) = 0;
  *(_BYTE *)(this + 4) = 0;
  *(_BYTE *)(this + 5) = 0;
  *(_DWORD *)(this + 8) = 0;
  *(_DWORD *)(this + 828) = 0;
  *(_DWORD *)(this + 28) = 0;
  *(_DWORD *)(this + 32) = 1061158912;
  *(_DWORD *)(this + 36) = 1065353216;
  *(_DWORD *)(this + 40) = 0;
  *(_DWORD *)(this + 12) = 0;
  *(_DWORD *)(this + 24) = 0;
  *(_DWORD *)(this + 20) = 1145569280;
  *(_DWORD *)(this + 16) = 1142292480;
  return this;
}

// 0x004C6410
void *sub_4C6410()
{
  if ( (byte_DE96F4 & 1) == 0 )
  {
    byte_DE96F4 |= 1u;
    CEffectSystem::DestroyEffect((int)&unk_DE93B0);
    atexit(unknown_libname_446);
  }
  return &unk_DE93B0;
}

// 0x004C6460
char sub_4C6460(int _this)
{
  struct gbRenderEffect *v3; // eax
  int v4; // esi
  int v5; // edi
  _DWORD v6[2]; // [esp+14h] [ebp-14h] BYREF
  int v7; // [esp+1Ch] [ebp-Ch]
  int v8; // [esp+20h] [ebp-8h]
  int v9; // [esp+24h] [ebp-4h]

  if ( !*(_DWORD *)(this + 828) )
  {
    if ( (g_nGameFlags & 8) == 0 )
      return 0;
    v6[0] = 0;
    v6[1] = 0;
    v7 = 0;
    v8 = 0;
    v9 = 0;
    if ( !(*(int (**)(int, _DWORD *, int))(*(_DWORD *)g_pGfxManager + 84))(g_pGfxManager, v6, 1) )
      return 0;
    (*(void (**)(int))(*(_DWORD *)g_pGfxManager + 88))(g_pGfxManager);
    v3 = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(g_pGfxManager + 200), aGfxscriptTrail, 0);
    *(_DWORD *)(this + 828) = v3;
    if ( !v3 )
      return 0;
    if ( (*(int (__stdcall **)(_DWORD, _DWORD, int))(**(_DWORD **)(g_pGfxManager + 1816) + 152))(
           *(_DWORD *)(g_pGfxManager + 1816),
           0,
           this + 832) < 0 )
      return 0;
    v4 = 0;
    v5 = this + 60;
    do
    {
      if ( !(*(int (**)(int, int, int, int))(*(_DWORD *)v5 + 12))(v5, 256, 256, v7)
        || !(*(int (**)(int, int))(*(_DWORD *)g_pGfxManager + 92))(g_pGfxManager, v5) )
      {
        return 0;
      }
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)(g_pGfxManager + 1816) + 172))(
        *(_DWORD *)(g_pGfxManager + 1816),
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      ++v4;
      v5 += 96;
    }
    while ( v4 < 8 );
    if ( (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)(g_pGfxManager + 1816) + 148))(
           *(_DWORD *)(g_pGfxManager + 1816),
           0,
           *(_DWORD *)(this + 832)) < 0 )
      return 0;
    *(_BYTE *)(this + 4) = 1;
  }
  return 1;
}

// 0x004C65C0
void sub_4C65C0(float a2)
{
  double v2; // st7
  char v4; // c0

  v2 = a2 + *this;
  *this = v2;
  if ( !v4 )
  {
    ++*((_DWORD *)this + 13);
    *this = v2 - 0.02;
  }
}

// 0x004C65F0
void sub_4C65F0(int _this, int a2)
{
  int v3; // eax
  gbCamera *v4; // ecx

  if ( *(_BYTE *)(this + 5) && *(_BYTE *)(this + 4) )
  {
    if ( a2 )
      *(_DWORD *)(this + 8) = a2;
    v3 = *(_DWORD *)(this + 52) & 7;
    *(_DWORD *)(this + 56) = v3;
    (*(void (**)(int, int))(*(_DWORD *)g_pGfxManager + 92))(g_pGfxManager, 96 * v3 + this + 60);
    (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)(g_pGfxManager + 1816) + 172))(
      *(_DWORD *)(g_pGfxManager + 1816),
      0,
      0,
      3,
      -16777216,
      1065353216,
      0);
    v4 = *(gbCamera **)(this + 8);
    if ( v4 )
      v4->SetDimention(256, 192);
  }
}

// 0x004C6670
char sub_4C6670(int _this)
{
  unsigned int v2; // eax
  gbColorQuad *v3; // edi
  int v4; // ebx
  int v5; // ebx
  int v6; // edi
  _BYTE *v7; // ecx
  unsigned int v8; // eax
  int v9; // eax
  _DWORD *v10; // edi
  int v11; // ebx
  struct gbRenderEffect *v12; // eax
  unsigned int v13; // ebp
  _DWORD *v14; // edi
  int v15; // ebx
  struct gbRenderEffect *v16; // eax
  gbDynVertBuf *DynVertBuf; // [esp+44h] [ebp-48h]
  _DWORD v19[16]; // [esp+48h] [ebp-44h] BYREF
  int v20; // [esp+88h] [ebp-4h]

  LOBYTE(v2) = *(_BYTE *)(this + 5);
  if ( (_BYTE)v2 )
  {
    LOBYTE(v2) = *(_BYTE *)(this + 4);
    if ( (_BYTE)v2 )
    {
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)(g_pGfxManager + 1816) + 148))(
        *(_DWORD *)(g_pGfxManager + 1816),
        0,
        *(_DWORD *)(this + 832));
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)(g_pGfxManager + 1816) + 172))(
        *(_DWORD *)(g_pGfxManager + 1816),
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      gbCamera::SetDimention(*(gbCamera **)(this + 8), MEMORY[0xBFD6D0], MEMORY[0xBFD6D4]);
      DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x114u);
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
      v5 = 158 - 8 * *(_DWORD *)(this + 56);
      v6 = 0;
      v7 = &unk_DE9389;
      do
      {
        *(v7 - 1) = v5 / 2;
        *v7 = v5 / 2;
        v7[1] = v5 / 2;
        v7[2] = v5;
        v5 += 8;
        if ( v6 == *(_DWORD *)(this + 56) )
          v5 = 102;
        v7 += 4;
        ++v6;
      }
      while ( (int)v7 < (int)byte_DE93A9 );
      v8 = *(_DWORD *)(this + 56);
      v20 = 0;
      if ( v8 < 7 )
      {
        v9 = v8 + 1;
        if ( v9 < 8 )
        {
          v10 = (_DWORD *)(4 * v9 + 14586760);
          v11 = 96 * v9 + this + 60;
          do
          {
            v12 = *(struct gbRenderEffect **)(this + 828);
            *(_DWORD *)(this + 48) = *v10;
            v20 = 1;
            v19[0] = v11;
            DynVertBuf->RenderUIQuad((struct gbUIQuad *)(this + 12), 1, v12, (struct gbTextureArray *)v19);
            ++v10;
            v11 += 96;
          }
          while ( (int)v10 < (int)&byte_DE93A8 );
        }
      }
      v13 = 0;
      v14 = &unk_DE9388;
      v15 = this + 60;
      do
      {
        if ( (int)v14 < (int)&byte_DE93A8 )
        {
          v16 = *(struct gbRenderEffect **)(this + 828);
          *(_DWORD *)(this + 48) = *v14;
          v20 = 1;
          v19[0] = v15;
          DynVertBuf->RenderUIQuad((struct gbUIQuad *)(this + 12), 1, v16, (struct gbTextureArray *)v19);
        }
        v2 = *(_DWORD *)(this + 56);
        ++v13;
        ++v14;
        v15 += 96;
      }
      while ( v13 <= v2 );
    }
  }
  return v2;
}

// 0x004C6870
_DWORD * sub_4C6870()
{
  *((_DWORD *)this + 1) = 0;
  *((_BYTE *)this + 8) = 0;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 7) = -1;
  *((_DWORD *)this + 8) = -1;
  *((_DWORD *)this + 9) = 0;
  *((_DWORD *)this + 10) = 0;
  *((_DWORD *)this + 11) = 0;
  *((_DWORD *)this + 3) = &off_56F8B4;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 34) = 0;
  *((_DWORD *)this + 35) = 0;
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 42) = 0;
  *((_DWORD *)this + 43) = 0;
  *((_DWORD *)this + 44) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 46) = 0;
  *this = &off_56F878;
  *((_DWORD *)this + 3) = &off_56F86C;
  *((_DWORD *)this + 43) = 0;
  *((_DWORD *)this + 42) = 0;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 44) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 30) = 0;
  *((_DWORD *)this + 12) = 0;
  *((_DWORD *)this + 13) = 0;
  *((_BYTE *)this + 65) = 0;
  *((_BYTE *)this + 66) = 0;
  *((_DWORD *)this + 14) = 0;
  *((_DWORD *)this + 15) = 0;
  return this;
}
