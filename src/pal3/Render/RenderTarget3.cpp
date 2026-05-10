#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/RenderTarget3.h"

// Forward declarations for unnamed functions
int sub_4B6550(...);
int sub_4B66B0(...);
int sub_4B67B0(...);
int sub_4B6820(...);

// Unnamed globals (extern)
extern char aGfxscriptGeomG[];
extern char aGfxscriptGlowG[];
extern unsigned char byte_DE6A4C;
extern int unk_DE6A30;

// 0x004B65A0
void *RenderTarget3::GetInstance()
{
  if ( (byte_DE6A4C & 1) == 0 )
  {
    byte_DE6A4C |= 1u;
    sub_4B6550((int)&unk_DE6A30);
    atexit(unknown_libname_413);
  }
  return &unk_DE6A30;
}

// 0x004B65F0
void RenderTarget3::Init()
{
  gbEffectMgr *pEffectMgr; // edi

  pEffectMgr = *(gbEffectMgr **)&g_pGfxManager[200];
  *(_DWORD *)this = pEffectMgr->NewRenderEffect(aGfxscriptGlowG, 0);
  *((_DWORD *)this + 1) = pEffectMgr->NewRenderEffect(aGfxscriptGeomG, 1u);
}

// 0x004B6630
int RenderTarget3::Begin()
{
  int v1; // edi
  int result; // eax
  unsigned int i; // edi
  int v5; // eax
  int v6; // ecx
  unsigned int j; // edi

  LOBYTE(result) = sub_4B66B0(v1, (int)this);
  if ( (_BYTE)result )
  {
    for ( i = 0; ; ++i )
    {
      v5 = *((_DWORD *)this + 4);
      if ( !v5 || i >= (*((_DWORD *)this + 5) - v5) >> 2 )
        break;
      gbRenderEffect::SetVariant(
        *((gbRenderEffect **)this + 1),
        PARAM_HANDLE_SPECULAR,
        (void *)(*(_DWORD *)(v5 + 4 * i) + 16));
      v6 = *(_DWORD *)(*((_DWORD *)this + 4) + 4 * i);
      (*(void (**)(int, _DWORD))(*(_DWORD *)v6 + 4))(v6, *((_DWORD *)this + 1));
    }
    sub_4B67B0();
    for ( j = 0; ; ++j )
    {
      result = *((_DWORD *)this + 4);
      if ( !result || j >= (*((_DWORD *)this + 5) - result) >> 2 )
        break;
      sub_4B6820((struct gbRenderEffect **)this, *(_DWORD *)(result + 4 * j));
    }
  }
  return result;
}

// 0x004B6DF0
void * RenderTarget3::End()
{
  _BYTE *v0; // ecx
  void *result; // eax

  if ( *v0 )
    return (*(void *(__stdcall **)(_DWORD, int, int))(**(_DWORD **)&g_pGfxManager[1816] + 228))(
             *(_DWORD *)&g_pGfxManager[1816],
             168,
             3);
  return result;
}

// 0x004B6E20
void RenderTarget3::Resolve()
{
  gbDynVertBuf *DynVertBuf; // eax
  int v3; // esi
  _DWORD v4[10]; // [esp+24h] [ebp-78h] BYREF
  _DWORD v5[17]; // [esp+4Ch] [ebp-50h] BYREF
  int v6; // [esp+98h] [ebp-4h]

  if ( *this )
  {
    (*(void (__stdcall **)(_DWORD, int, int))(**(_DWORD **)&g_pGfxManager[1816] + 228))(
      *(_DWORD *)&g_pGfxManager[1816],
      168,
      7);
    if ( *((_DWORD *)this + 1) )
    {
      if ( g_SceneMgr.?[5].?.normal[221].x )
      {
        v4[8] = 0;
        v4[9] = -1;
        v4[5] = 0;
        v4[4] = 0;
        v4[6] = 1065353216;
        v4[7] = 1065353216;
        v4[0] = -1082130432;
        v4[3] = 1065353216;
        v4[2] = 1065353216;
        v4[1] = -1082130432;
        PushMatrixStacks();
        v6 = 0;
        DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)&g_pGfxManager[196], 0x15u);
        v3 = *((_DWORD *)this + 1);
        v5[16] = 1;
        v5[0] = v3;
        DynVertBuf->RenderUIQuad((struct gbUIQuad *)v4,
          1,
          (struct gbRenderEffect *)g_SceneMgr.?[5].?.normal[221].x,
          (struct gbTextureArray *)v5);
        v6 = -1;
        PopMatrixStacks();
      }
    }
  }
}
