#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Array.h"

// 0x00411170
void * Array::Insert(void *arr, void *elem, void *end)
{
  _DWORD *v3; // ecx
  void *result; // eax

  v3 = arr;
  if ( arr == elem )
    return end;
  result = end;
  do
  {
    if ( result )
    {
      *(_DWORD *)result = *v3;
      *((_DWORD *)result + 1) = v3[1];
      *((_DWORD *)result + 2) = v3[2];
    }
    v3 += 3;
    result = (char *)result + 12;
  }
  while ( v3 != elem );
  return result;
}

// 0x004111C0
int Array::Size()
{
  int result; // eax

  result = *((_DWORD *)this + 1);
  if ( result )
    return (*((_DWORD *)this + 2) - result) / 12;
  return result;
}

// 0x004111E0
void * Array::Erase(void *arr, int index, void *pConfig)
{
  void *result; // eax
  int v4; // ecx

  result = (void *)index;
  if ( index )
  {
    v4 = index;
    result = arr;
    do
    {
      if ( result )
      {
        *(_DWORD *)result = *(_DWORD *)pConfig;
        *((_DWORD *)result + 1) = *((_DWORD *)pConfig + 1);
        *((_DWORD *)result + 2) = *((_DWORD *)pConfig + 2);
      }
      result = (char *)result + 12;
      --v4;
    }
    while ( v4 );
  }
  return result;
}

// 0x00411240
void * Array::Copy(void *dst, void *src)
{
  void *result; // eax

  result = dst;
  if ( dst )
  {
    *(_DWORD *)dst = *(_DWORD *)src;
    *((_DWORD *)dst + 1) = *((_DWORD *)src + 1);
    *((_DWORD *)dst + 2) = *((_DWORD *)src + 2);
  }
  return result;
}
