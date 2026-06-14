#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UISystem.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations
int sub_41F8C0(...);
void sub_421870(struct gbVisNode **_this); // from annotations

// Unnamed globals (extern)
extern char byte_D8B314;
extern UISystem stru_D8B938;

// 0x00422DF0
void UISystem::Destroy()
{
  gbVisNode **v1; // eax
  PalScriptMgr *v2; // esi
  ScriptSystemData *v3; // esi

  v1 = (gbVisNode **)UISceneUpdate();
  sub_421870(v1);
  v2 = &pOut;
  do
  {
    sub_41F8C0(v2);
    v2 = (PalScriptMgr *)((char *)v2 + 493156);
  }
  while ( (int)v2 < (int)&byte_D8B314 );
  v3 = &g_ScriptSystemData;
  do
  {
    ((SceneMapPlayer *)v3->m_mapPlayer)->Reset();
    v3 = (ScriptSystemData *)((char *)v3 + 392);
  }
  while ( (int)v3 < (int)&stru_D8B938 );
}
