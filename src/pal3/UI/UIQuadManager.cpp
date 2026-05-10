#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIQuadManager.h"

// 0x005415C0
void UIQuadManager::Destroy()
{
  gbRefObject **v1; // esi
  int v2; // ebx

  v1 = (gbRefObject **)(this + 16);
  v2 = 3;
  do
  {
    if ( *v1 )
    {
      gbRefObject::Release(*v1);
      *v1 = 0;
    }
    ++v1;
    --v2;
  }
  while ( v2 );
}

// 0x005415F0
void *sub_5415F0()
{
  if ( (byte_1894DB0 & 1) == 0 )
  {
    byte_1894DB0 |= 1u;
    sub_541470((int)&unk_1894D90);
    atexit(unknown_libname_522);
  }
  return &unk_1894D90;
}
