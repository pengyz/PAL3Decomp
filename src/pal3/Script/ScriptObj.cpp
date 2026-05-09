#include "pal3/gen/ScriptObj.h"

// 0x00412680
int ScriptObj::Destroy()
{
  int (__thiscall ***v2)(_DWORD, int); // ecx
  int result; // eax

  v2 = (int (__thiscall ***)(_DWORD, int))*((_DWORD *)this + 360);
  *((_DWORD *)this + 157) = 0;
  if ( v2 )
  {
    result = (**v2)(v2, 1);
    *((_DWORD *)this + 360) = 0;
  }
  *((_DWORD *)this + 363) = 0;
  *((_DWORD *)this + 362) = 0;
  *((_DWORD *)this + 317) = 0;
  *((_DWORD *)this + 365) = 0;
  *((_DWORD *)this + 318) = 0;
  return result;
}
