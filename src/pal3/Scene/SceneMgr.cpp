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
  __int32 s_curscene; // eax
  struct gbRenderEffect *v6; // eax
  __int32 v7; // ecx
  struct gbRenderEffect *v8; // eax
  __int32 v9; // edx

  this->m_pGfxMgr = gfxMgr;
  *(_DWORD *)&this->m_pSceneRoot[0].m_info.cityname[20] = cam;
  *(_DWORD *)&this->m_pSceneRoot[0].m_info.cityname[12] = 0;
  *(_DWORD *)&this->m_pSceneRoot[0].m_info.cityname[16] = 0;
  *(_DWORD *)this->m_pSceneRoot[0].m_info.cityname = a4;
  memset(&this->m_pSceneRoot[0].m_info.cityname[24], 0, 0x900u);
  memset(&this->m_pSceneRoot[0].m_npc[0].m_path.points[26], 0, 0xA000u);
  s_curscene = this->m_pGfxMgr;
  this->m_pSceneRoot[0].m_npc[4].m_path.normal[176].x = 0.0;
  this->m_pSceneRoot[0].m_npc[4].m_path.normal[176].y = 0.0;
  this->m_pSceneRoot[0].m_npc[4].m_path.normal[176].z = 0.0;
  this->m_pSceneRoot[0].m_npc[4].m_path.normal[177].x = 0.0;
  this->m_pSceneRoot[0].m_npc[4].m_path.normal[177].y = 1.0;
  v6 = ((gbEffectMgr *)*(gbEffectMgr **)(s_curscene + 200))->NewRenderEffect(aGfxscriptAddit, 0);
  v7 = this->m_pGfxMgr;
  *(_DWORD *)&this->m_pSceneRoot[0].m_info.cityname[12] = v6;
  v8 = ((gbEffectMgr *)*(gbEffectMgr **)(v7 + 200))->NewRenderEffect(aGfxscriptAlpha, 0);
  v9 = this->m_pGfxMgr;
  *(_DWORD *)&this->m_pSceneRoot[0].m_info.cityname[16] = v8;
  *(_DWORD *)&this->m_pSceneRoot[0].m_info.cityname[4] = ((gbEffectMgr *)*(gbEffectMgr **)(v9 + 200))->NewRenderEffect(aGfxscriptAddit_0, 0);
  *(_DWORD *)&this->m_pSceneRoot[0].m_info.cityname[8] = ((gbEffectMgr *)*(gbEffectMgr **)(this->m_pGfxMgr + 200))->NewRenderEffect(aGfxscriptAlpha_0, 0);
  sub_4CDED0((CEffMgr *)this);
  CEffMgr::CEffMgr();
  return this;
}

// 0x004CDBF0
char SceneMgr::RenderAll()
{
  float *p_y; // esi
  int v2; // edi
  char result; // al

  p_y = (float *)&this->m_pSceneRoot[0].m_npc[0].m_path.points[27].y;
  v2 = 2048;
  do
  {
    result = *((_BYTE *)p_y - 4);
    if ( result )
      result = (*(int (**)(_DWORD))(**(_DWORD **)p_y + 24))(*(_DWORD *)p_y);
    p_y += 5;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004CDC20
char SceneMgr::RenderUpdate()
{
  float *p_y; // esi
  int v2; // edi
  char result; // al

  p_y = (float *)&this->m_pSceneRoot[0].m_npc[0].m_path.points[27].y;
  v2 = 2048;
  do
  {
    result = *((_BYTE *)p_y - 4);
    if ( result )
      result = (*(int (**)(_DWORD))(**(_DWORD **)p_y + 16))(*(_DWORD *)p_y);
    p_y += 5;
    --v2;
  }
  while ( v2 );
  return result;
}
