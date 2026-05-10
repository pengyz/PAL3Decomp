#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MvcViewport.h"

// 0x0043A4B0
int MvcViewport::SetController(int a2)
{
  *((_DWORD *)this + 17) = a2;
  return a2;
}
