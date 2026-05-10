#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBResultWindow.h"

// 0x0051F080
CCBResultWindow::CCBResultWindow(int a2)
{
  *((_DWORD *)this + 2004) = a2;
  return a2;
}

// 0x0051F090
CCBResultWindow::~CCBResultWindow(int a2)
{
  *((_DWORD *)this + 2005) = a2;
  return a2;
}

// 0x0051F0A0
int CCBResultWindow::Reset(int a2, int a3)
{
  int v4; // eax
  const void *v5; // esi
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx

  v4 = *((_DWORD *)this + 2011);
  v5 = (const void *)*((_DWORD *)this + 2012);
  v6 = *((_DWORD *)this + 82011);
  *((_DWORD *)this + 86393) = *((_DWORD *)this + 82005);
  *((_DWORD *)this + 86395) = v4;
  v7 = *((_DWORD *)this + 82008);
  qmemcpy(this + 86396, v5, 0xDCu);
  v8 = *((_DWORD *)this + 82009);
  *((_DWORD *)this + 126858) = v6;
  v9 = *((_DWORD *)this + 82010);
  *((_DWORD *)this + 126855) = v7;
  *((_DWORD *)this + 126856) = v8;
  *((_DWORD *)this + 126857) = v9;
  a2->RunSceneScript();
  this->HitTest(a2, a3);
  return 1;
}
