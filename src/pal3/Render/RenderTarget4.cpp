#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/RenderTarget4.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"

// Forward declarations for unnamed functions
int sub_4B6D20(...);

// Unnamed globals (extern)
extern char aEffectscnFrame[];
extern unsigned char byte_DE6CE0;
extern int dword_DE6CD8;
extern int unknown_libname_416;

// 0x004B6D30
_DWORD *RenderTarget4::GetInstance()
{
  if ( (byte_DE6CE0 & 1) == 0 )
  {
    byte_DE6CE0 |= 1u;
    sub_4B6D20(dword_DE6CD8);
    atexit(unknown_libname_416);
  }
  return dword_DE6CD8;
}

// 0x004B6D80
void * RenderTarget4::Init()
{
  gbTexture *v2; // eax
  OpenBaseFile v4; // [esp+8h] [ebp-10h] BYREF
  int v5; // [esp+14h] [ebp-4h]

  ((OpenBaseFile *)&v4)->OpenBaseFile();
  v5 = 0;
  v2 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                      g_Input.KeyInfo[177].Data,
                      aEffectscnFrame);
  *((_DWORD *)this + 1) = v2;
  v2->LoadTexture(1);
  *this = 0;
  v5 = -1;
  return ((OpenNULLFile **)&v4)->OpenNULLFile();
}
