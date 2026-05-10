#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CRenderTarget.h"

// Forward declarations for unnamed functions
int sub_4BDA60(...);

// Unnamed globals (extern)
extern unsigned char byte_DE7B68;
extern int dword_DE7AA0;
extern int unknown_libname_427;

// 0x004BDB10
_DWORD *CRenderTarget::GetInstance()
{
  if ( (byte_DE7B68 & 1) == 0 )
  {
    byte_DE7B68 |= 1u;
    sub_4BDA60(dword_DE7AA0);
    atexit(unknown_libname_427);
  }
  return dword_DE7AA0;
}

// 0x004BDED0
void CRenderTarget::Destroy()
{
  *(_DWORD *)this = -1;
}
