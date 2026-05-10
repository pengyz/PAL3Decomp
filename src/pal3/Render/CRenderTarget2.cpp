#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CRenderTarget2.h"

// Forward declarations for unnamed functions
int sub_4BF760(...);

// Unnamed globals (extern)
extern unsigned char byte_DE8B58;
extern int dword_DE8B40;
extern int unknown_libname_437;

// 0x004BFD20
_DWORD *CRenderTarget2::GetInstance()
{
  if ( (byte_DE8B58 & 1) == 0 )
  {
    byte_DE8B58 |= 1u;
    sub_4BF760(dword_DE8B40);
    atexit(unknown_libname_437);
  }
  return dword_DE8B40;
}

// 0x004C0400
void CRenderTarget2::Destroy()
{
  int v2; // eax
  int v3; // eax
  int v4; // eax

  v2 = *((_DWORD *)this + 2);
  if ( v2 )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)v2 + 8))(v2);
    *((_DWORD *)this + 2) = 0;
  }
  v3 = *((_DWORD *)this + 1);
  if ( v3 )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)v3 + 8))(*((_DWORD *)this + 1));
    *((_DWORD *)this + 1) = 0;
  }
  v4 = *((_DWORD *)this + 3);
  if ( v4 )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)v4 + 8))(*((_DWORD *)this + 3));
    *((_DWORD *)this + 3) = 0;
  }
}
