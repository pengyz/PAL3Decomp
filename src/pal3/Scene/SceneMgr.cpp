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
void * SceneMgr::Create(gbGfxManager *gfxMgr, gbCamera *cam, gbSceneGraph *pRoot)
{
  gbGfxManager *m_pGfxMgr; // eax
  gbRenderEffect *v6; // eax
  gbGfxManager *v7; // ecx
  gbRenderEffect *v8; // eax
  gbGfxManager *v9; // edx

  this->m_pGfxMgr = gfxMgr;
  this->m_pCamera = cam;
  this->m_pAddEffect = 0;
  this->m_pAlphaEffect = 0;
  this->m_pSceneRoot = pRoot;
  memset(this->_preArray, 0, 0x900u);
  memset(&this->m_slot[1]._data[276], 0, 0xA000u);
  m_pGfxMgr = (gbGfxManager *)this->m_pGfxMgr;
  *(_DWORD *)this->m_RoleSystem[4]._gap_054C = 0;
  *(_DWORD *)&this->m_RoleSystem[4]._gap_054C[4] = 0;
  *(_DWORD *)&this->m_RoleSystem[4]._gap_054C[8] = 0;
  *(_DWORD *)&this->m_RoleSystem[4]._gap_054C[12] = 0;
  *(_DWORD *)&this->m_RoleSystem[4]._gap_054C[16] = 1065353216;
  v6 = ((gbEffectMgr *)m_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptAddit, 0);
  v7 = (gbGfxManager *)this->m_pGfxMgr;
  this->m_pAddEffect = v6;
  v8 = ((gbEffectMgr *)v7->pEffectMgr)->NewRenderEffect(aGfxscriptAlpha, 0);
  v9 = (gbGfxManager *)this->m_pGfxMgr;
  this->m_pAlphaEffect = v8;
  this->m_pAddEffect2 = ((gbEffectMgr *)v9->pEffectMgr)->NewRenderEffect(aGfxscriptAddit_0, 0);
  this->m_pAlphaEffect2 = ((gbEffectMgr *)this->m_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptAlpha_0, 0);
  sub_4CDED0((CEffMgr *)this);
  CEffMgr::CEffMgr();
  return this;
}

// 0x004CDBF0
char SceneMgr::RenderAll()
{
  char *v1; // esi
  int v2; // edi
  char result; // al

  v1 = (char *)&this->m_slot[1]._data[292];
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
  char *v1; // esi
  int v2; // edi
  char result; // al

  v1 = (char *)&this->m_slot[1]._data[292];
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
