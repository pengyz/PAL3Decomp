#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBResultWindow.h"

// 0x0051F080
int sub_51F080(_DWORD *this, int a2)
{
  *(this + 2004) = a2;
  return a2;
}

// 0x0051F090
int sub_51F090(_DWORD *this, int a2)
{
  *(this + 2005) = a2;
  return a2;
}

// 0x0051F0A0
int sub_51F0A0(_DWORD *this, int a2, int a3)
{
  int v4; // eax
  const void *v5; // esi
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx

  v4 = *(this + 2011);
  v5 = (const void *)*(this + 2012);
  v6 = *(this + 82011);
  *(this + 86393) = *(this + 82005);
  *(this + 86395) = v4;
  v7 = *(this + 82008);
  qmemcpy(this + 86396, v5, 0xDCu);
  v8 = *(this + 82009);
  *(this + 126858) = v6;
  v9 = *(this + 82010);
  *(this + 126855) = v7;
  *(this + 126856) = v8;
  *(this + 126857) = v9;
  a2->RunSceneScript();
  this->HitTest(a2, a3);
  return 1;
}
