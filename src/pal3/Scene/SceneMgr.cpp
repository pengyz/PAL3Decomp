#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SceneMgr.h"
#include "pal3/gen/CEffMgr.h"

// Forward declarations for unnamed functions
int sub_4CDED0(...);

// Unnamed globals (extern)
extern char aGfxscriptAddit[];
extern char aGfxscriptAddit_0[];
extern char aGfxscriptAlpha[];
extern char aGfxscriptAlpha_0[];

// 0x004CDA10
void * SceneMgr::Create(int gfxMgr, int cam, int a4)
{
  __int32 m_pGfxMgr; // eax
  struct gbRenderEffect *v6; // eax
  __int32 v7; // ecx
  struct gbRenderEffect *v8; // eax
  __int32 v9; // edx

  this->m_pGfxMgr = gfxMgr;
  this->m_pCamera = cam;
  this->m_pAddEffect = 0;
  this->m_pAlphaEffect = 0;
  this->m_pSceneRoot = a4;
  memset(this->_preArray, 0, 0x900u);
  memset(&this->m_slot1[276], 0, 0xA000u);
  m_pGfxMgr = this->m_pGfxMgr;
  this->m_lightDirX = 0.0;
  this->m_lightDirY = 0.0;
  this->m_lightDirZ = 0.0;
  this->m_upX = 0.0;
  this->m_upY = 1.0;
  v6 = ((gbEffectMgr *)*(gbEffectMgr **)(m_pGfxMgr + 200))->NewRenderEffect(aGfxscriptAddit, 0);
  v7 = this->m_pGfxMgr;
  this->m_pAddEffect = (__int32)v6;
  v8 = ((gbEffectMgr *)*(gbEffectMgr **)(v7 + 200))->NewRenderEffect(aGfxscriptAlpha, 0);
  v9 = this->m_pGfxMgr;
  this->m_pAlphaEffect = (__int32)v8;
  this->m_pAddEffect2 = (__int32)((gbEffectMgr *)*(gbEffectMgr **)(v9 + 200))->NewRenderEffect(aGfxscriptAddit_0, 0);
  this->m_pAlphaEffect2 = (__int32)((gbEffectMgr *)*(gbEffectMgr **)(this->m_pGfxMgr + 200))->NewRenderEffect(aGfxscriptAlpha_0, 0);
  sub_4CDED0((CEffMgr *)this);
  CEffMgr::CEffMgr();
  return this;
}

// 0x004CDBF0
char SceneMgr::RenderAll()
{
  __int8 *v1; // esi
  int v2; // edi
  char result; // al

  v1 = (__int8 *)&this->m_slot1[292];
  v2 = 2048;
  do
  {
    result = *(v1 - 4);
    if ( result )
      result = (*(int (**)(_DWORD))(**(_DWORD **)v1 + 24))(*(_DWORD *)v1);
    v1 += 20;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004CDC20
char SceneMgr::RenderUpdate()
{
  __int8 *v1; // esi
  int v2; // edi
  char result; // al

  v1 = (__int8 *)&this->m_slot1[292];
  v2 = 2048;
  do
  {
    result = *(v1 - 4);
    if ( result )
      result = (*(int (**)(_DWORD))(**(_DWORD **)v1 + 16))(*(_DWORD *)v1);
    v1 += 20;
    --v2;
  }
  while ( v2 );
  return result;
}
