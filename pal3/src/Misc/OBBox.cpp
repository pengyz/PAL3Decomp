#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/OBBox.h"

// Unnamed globals (extern)
extern int unknown_libname_491;

// 0x0052F6C0
OBBox * OBBox::GetBBox()
{
  char *v2; // edi
  int v3; // ebx
  gbOBBox *v4; // edi
  int v5; // ebx
  char *v6; // edi
  int v7; // ebx
  gbOBBox *v8; // edi
  int v9; // ebx

  v2 = (char *)this + 1680;
  v3 = 6;
  do
  {
    v2 += 12;
    --v3;
  }
  while ( v3 );
  v4 = (gbOBBox *)((char *)this + 1752);
  v5 = 6;
  do
  {
    --v5;
  }
  while ( v5 );
  v6 = (char *)this + 3064;
  v7 = 3;
  do
  {
    v6 += 12;
    --v7;
  }
  while ( v7 );
  v8 = (gbOBBox *)((char *)this + 3100);
  v9 = 3;
  do
  {
    --v9;
  }
  while ( v9 );
  *((_DWORD *)this + 833) = 0;
  *((_DWORD *)this + 904) = 0;
  *((_DWORD *)this + 905) = 0;
  *((_DWORD *)this + 906) = 0;
  *((_DWORD *)this + 907) = 0;
  *((_DWORD *)this + 908) = 0;
  *((_DWORD *)this + 909) = 0;
  *((_DWORD *)this + 910) = 0;
  *((_DWORD *)this + 911) = 0;
  *((_DWORD *)this + 912) = 0;
  unknown_libname_491((char *)this + 3748);
  return this;
}
