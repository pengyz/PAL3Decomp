#include "pal3/gen/ScreenEffect.h"

// 0x004BDFB0
_BYTE * sub_4BDFB0(_BYTE *this)
{
  char v3; // [esp+Bh] [ebp-11h]

  sub_4BE8D0(this + 4);
  sub_4BEA60(this + 32);
  sub_4BEBB0(this + 56);
  sub_4BED00(this + 80);
  *(this + 104) = v3;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 30) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 34) = 0;
  *((_DWORD *)this + 35) = 0;
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 37) = 0;
  *(_DWORD *)this = &off_56F508;
  return this;
}
