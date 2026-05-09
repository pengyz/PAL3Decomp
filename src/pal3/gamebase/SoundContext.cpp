#include "pal3/gen/SoundContext.h"

// 0x0053D150
_DWORD *sub_53D150()
{
  if ( (byte_17B3ED0 & 1) == 0 )
  {
    byte_17B3ED0 |= 1u;
    sub_53D0B0(dword_17B3EB0);
    atexit(unknown_libname_513);
  }
  return dword_17B3EB0;
}
