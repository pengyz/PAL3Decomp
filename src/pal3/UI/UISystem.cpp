#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UISystem.h"

// Forward declarations for unnamed functions
int sub_41F8C0(...);
int sub_4208A0(...);

// Unnamed globals (extern)
extern unsigned char byte_D8B314;
extern unsigned char byte_D8B938;
extern int unk_D8B318;

// 0x00422DF0
int UISystem::Destroy()
{
  float *p_z; // esi
  char *v1; // esi
  int result; // eax

  UISceneUpdate();
  GetGfxManager_3();
  p_z = (float *)&g_SceneMgr.m_npc[13].m_path.normal[157].z;
  do
  {
    sub_41F8C0((int)p_z);
    p_z += 123289;
  }
  while ( (int)p_z < (int)&byte_D8B314 );
  v1 = (char *)&unk_D8B318;
  do
  {
    result = sub_4208A0((int)v1);
    v1 += 392;
  }
  while ( (int)v1 < (int)byte_D8B938 );
  return result;
}
