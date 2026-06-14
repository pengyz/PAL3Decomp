#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIParabolaCtrl.h"

// 0x004A1CF0
int UIParabolaCtrl::GetState()
{
  int result; // eax

  result = *((_DWORD *)this + 332);
  *((_DWORD *)this + 332) = -1;
  return result;
}
