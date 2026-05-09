#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MvcController.h"

// 0x004B73D0
int MvcController::SetComponent(_DWORD *this, int a2)
{
  *(this + 23) = a2;
  return a2;
}
