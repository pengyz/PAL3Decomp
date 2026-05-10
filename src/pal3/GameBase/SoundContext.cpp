#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SoundContext.h"

// Forward declarations for unnamed functions
int sub_53D0B0(...);

// Unnamed globals (extern)
extern unsigned char byte_17B3ED0;
extern int dword_17B3EB0;
extern int unknown_libname_513;

// 0x0053D150
_DWORD *SoundContext::GetInstance()
{
  if ( (byte_17B3ED0 & 1) == 0 )
  {
    byte_17B3ED0 |= 1u;
    sub_53D0B0(dword_17B3EB0);
    atexit(unknown_libname_513);
  }
  return dword_17B3EB0;
}
