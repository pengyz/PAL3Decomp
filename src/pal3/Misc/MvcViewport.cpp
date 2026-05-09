#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MvcViewport.h"

// 0x0043A4B0
int MvcViewport::SetController(_DWORD *this, int a2)
{
  *(this + 17) = a2;
  return a2;
}
