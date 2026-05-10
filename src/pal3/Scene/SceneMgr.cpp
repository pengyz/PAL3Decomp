#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SceneMgr.h"

// 0x004CDA10
void * SceneMgr::Create(int gfxMgr, int cam, int a4)
{
  int v5; // eax
  struct gbRenderEffect *v6; // eax
  int v7; // ecx
  struct gbRenderEffect *v8; // eax
  int v9; // edx

  *(_DWORD *)this = gfxMgr;
  *((_DWORD *)this + 6) = cam;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 1) = a4;
  memset(this + 28, 0, 0x900u);
  memset(this + 2332, 0, 0xA000u);
  v5 = *(_DWORD *)this;
  *((_DWORD *)this + 10823) = 0;
  *((_DWORD *)this + 10824) = 0;
  *((_DWORD *)this + 10825) = 0;
  *((_DWORD *)this + 10826) = 0;
  *((_DWORD *)this + 10827) = 1065353216;
  v6 = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(v5 + 200), aGfxscriptAddit, 0);
  v7 = *(_DWORD *)this;
  *((_DWORD *)this + 4) = v6;
  v8 = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(v7 + 200), aGfxscriptAlpha, 0);
  v9 = *(_DWORD *)this;
  *((_DWORD *)this + 5) = v8;
  *((_DWORD *)this + 2) = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(v9 + 200), aGfxscriptAddit_0, 0);
  *((_DWORD *)this + 3) = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(*(_DWORD *)this + 200), aGfxscriptAlpha_0, 0);
  ((void (__stdcall *)())sub_4CDED0)();
  CEffMgr::CEffMgr();
  return this;
}

// 0x004CDBF0
char SceneMgr::RenderAll()
{
  SceneMgr *v1; // esi
  int v2; // edi
  char result; // al

  v1 = this + 2348;
  v2 = 2048;
  do
  {
    result = (char)v1[-4];
    if ( result )
      result = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)v1 + 24))(*(_DWORD *)v1);
    v1 += 20;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004CDC20
char SceneMgr::RenderUpdate()
{
  SceneMgr *v1; // esi
  int v2; // edi
  char result; // al

  v1 = this + 2348;
  v2 = 2048;
  do
  {
    result = (char)v1[-4];
    if ( result )
      result = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)v1 + 16))(*(_DWORD *)v1);
    v1 += 20;
    --v2;
  }
  while ( v2 );
  return result;
}
