#include "pal3/ida_defs.h"
#include "pal3/globals.h"

// 0x0055353B
_DWORD * operator new(size_t Size)
{
  return _nh_malloc(Size, 1);
}
