#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ScreenEffect.h"

// Forward declarations for unnamed functions
int sub_4BE8D0(...);
int sub_4BEA60(...);
int sub_4BEBB0(...);
int sub_4BED00(...);

// Unnamed globals (extern)
extern void *off_56F508;

// 0x004BDFB0
ScreenEffect::ScreenEffect()
{
  char v3; // [esp+Bh] [ebp-11h]

  sub_4BE8D0((RenderTarget *)&this->m_needscriptdel);
  sub_4BEA60((int)this + 32);
  sub_4BEBB0((int)this + 56);
  sub_4BED00((RenderTarget *)((char *)this + 80));
  *((_BYTE *)this + 104) = v3;
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
  *(_DWORD *)this->_pad_0000 = &off_56F508;
  this->_pad_0000;
}
