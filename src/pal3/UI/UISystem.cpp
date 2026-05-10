#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UISystem.h"

// Forward declarations for unnamed functions
int UISceneUpdate(...);
int sub_41F8C0(...);
int sub_4208A0(...);

// Unnamed globals (extern)
extern unsigned char byte_D8B314;
extern unsigned char byte_D8B938;
extern int unk_C21FE8;
extern int unk_D8B318;

// 0x00422DF0
int UISystem::Destroy()
{
  char *v0; // esi
  char *v1; // esi
  int result; // eax

  UISceneUpdate();
  GetGfxManager_3();
  v0 = unk_C21FE8;
  do
  {
    sub_41F8C0((int)v0);
    v0 += 493156;
  }
  while ( (int)v0 < (int)&byte_D8B314 );
  v1 = (char *)&unk_D8B318;
  do
  {
    result = sub_4208A0((int)v1);
    v1 += 392;
  }
  while ( (int)v1 < (int)byte_D8B938 );
  return result;
}
