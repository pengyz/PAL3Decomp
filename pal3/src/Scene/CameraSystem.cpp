#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/CameraSystem.h"

// 0x0041D980
int CameraSystem::BindToRoleSlot(int nVal)
{
  int result; // eax

  result = nVal;
  if ( nVal )
  {
    g_pRoleSystem = (RoleSystem *)nVal;
    *(_DWORD *)(nVal + 1264) = 2;
  }
  return result;
}
