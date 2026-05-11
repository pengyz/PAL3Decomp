#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CameraSystem.h"

// Unnamed globals (extern)
extern int dword_C116EC;

// 0x0041D980
int CameraSystem::Init(int a1)
{
  int result; // eax

  result = a1;
  if ( a1 )
  {
    dword_C116EC = (void *)a1;
    *(_DWORD *)(a1 + 1264) = 2;
  }
  return result;
}
