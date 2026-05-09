#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffQuake.h"

// 0x004D32C0
_DWORD *sub_4D32C0()
{
  _DWORD *v0; // eax

  v0 = operator new(0x30u);
  if ( v0 )
    return sub_4D3280(v0);
  else
    return 0;
}

// 0x004D3300
int sub_4D3300(_DWORD *this)
{
  int v2; // esi
  int v3; // eax
  int result; // eax
  int v5; // ebx
  int v6; // edi

  *this = &off_56FA88;
  v2 = this != 0 ? (unsigned int)(this + 3) : 0;
  *(this + 3) = &off_56FA7C;
  v3 = *(_DWORD *)(v2 + 0x1C);
  *(_DWORD *)v2 = &off_56FAC4;
  if ( v3 || (result = *(this != 0 ? this + 11 : (_DWORD *)32)) != 0 )
  {
    v5 = 0;
    if ( *(this != 0 ? this + 10 : (int *)28) > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(v6 + *(_DWORD *)(v2 + 12)));
        ++v5;
        *(_DWORD *)(v6 + *(_DWORD *)(v2 + 12)) = 0;
        v6 += 152;
      }
      while ( v5 < *(_DWORD *)(v2 + 28) );
    }
    operator delete(*(void **)(v2 + 12));
    *(_DWORD *)(v2 + 12) = 0;
    *(_DWORD *)(v2 + 28) = 0;
    *(_DWORD *)(v2 + 32) = 0;
    *this = &off_56F62C;
    return 0;
  }
  else
  {
    *this = &off_56F62C;
  }
  return result;
}
