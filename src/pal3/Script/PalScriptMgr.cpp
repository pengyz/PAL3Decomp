#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PalScriptMgr.h"

// Forward declarations for unnamed functions
int sub_431CB0(...);
int sub_431CD0(...);
int sub_431E60(...);
int sub_431E90(...);
int sub_431EB0(...);
int sub_431EE0(...);
int sub_4320A0(...);
int sub_432170(...);
int sub_432260(...);
int sub_4322A0(...);
int sub_4322C0(...);
int sub_4323C0(...);
int sub_432480(...);
int sub_4324A0(...);
int sub_4324B0(...);
int sub_432500(...);
int sub_432550(...);
int sub_4325A0(...);
int sub_4326A0(...);
int sub_433CD0(...);
int sub_433DC0(...);
int sub_434670(...);

// Unnamed globals (extern)
extern unsigned char byte_D8C2B8;
extern unsigned char byte_D8C324;
extern unsigned char byte_D8C339;
extern int dword_D8C2BC;
extern int dword_D8C2C0;
extern int dword_D8C2C4;
extern int dword_D8C2C8;
extern int dword_D8C2E8;
extern int dword_D8C308;
extern int dword_D8C328;
extern int dword_D8C32C;

// 0x00431E60
int sub_431E60()
{
  unknown_libname_343();
  return atexit(sub_431E90);
}

// 0x00431EB0
int sub_431EB0()
{
  unknown_libname_344();
  return atexit(PalScriptMgr::FindScript);
}

// 0x00431EE0
void sub_431EE0()
{
  if ( (byte_D8C324 & 8) == 0 )
  {
    byte_D8C324 |= 8u;
    dword_D8C2C8->Remove();
  }
}

// 0x004320A0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __cdecl sub_4320A0(const char *a1)
{
  unsigned int v1; // kr04_4
  unsigned int v2; // ebp
  char *v3; // edi
  char v4; // al

  if ( a1->InsertAt() )
  {
    v1 = strlen(a1) + 1;
    v2 = v1 - 1;
    if ( v1 - 1 > 0xFFFFFFFD )
      std::_Xlen();
    v3 = (char *)dword_D8C2BC;
    if ( dword_D8C2BC && (v4 = *(_BYTE *)(dword_D8C2BC - 1)) != 0 && v4 != -1 )
    {
      if ( v1 == 1 )
      {
        *(_BYTE *)(dword_D8C2BC - 1) = v4 - 1;
        dword_D8C2BC = 0;
        dword_D8C2C0 = 0;
        dword_D8C2C4 = 0;
        return;
      }
    }
    else
    {
      if ( v1 == 1 )
      {
        std::string::_Tidy(&byte_D8C2B8, 1);
        return;
      }
      if ( (unsigned int)dword_D8C2C4 <= 0x1F && dword_D8C2C4 >= v1 - 1 )
        goto LABEL_15;
      std::string::_Tidy(&byte_D8C2B8, 1);
    }
    GRPinput::GetKeyState((int)&byte_D8C2B8, v2);
    v3 = (char *)dword_D8C2BC;
LABEL_15:
    qmemcpy(v3, a1, v2);
    dword_D8C2C0 = v1 - 1;
    *(_BYTE *)(dword_D8C2BC + v2) = 0;
  }
}

// 0x00432170
_DWORD * sub_432170(unsigned int a1, char a2)
{
  _DWORD *result; // eax
  void *v3; // edi
  _DWORD *v4; // eax
  _DWORD *v5; // esi

  result = (_DWORD *)a1;
  if ( a1 )
  {
    if ( a2 )
      result = (_DWORD *)sub_433DC0(dword_D8C2C8, a1, 0);
    else
      result = (_DWORD *)(a1 >= 0x64 ? sub_433DC0(dword_D8C308, a1, 0) : sub_433DC0(dword_D8C2E8, a1, 0));
    v3 = result;
    if ( result )
    {
      v4 = operator new(0x18u);
      if ( v4 )
        v5 = sub_431CB0(v4);
      else
        v5 = 0;
      if ( v5 )
      {
        v5[1] = v3;
        dword_D8C32C->SetAt(v5);
        return v5;
      }
      else
      {
        sub_433CD0(v3);
        return 0;
      }
    }
  }
  return result;
}

// 0x00432260
int sub_432260(int a1)
{
  int v1; // ecx
  int *i; // edx
  int result; // eax

  v1 = 0;
  if ( dword_D8C32C <= 0 )
    return 0;
  for ( i = (int *)dword_D8C328; ; ++i )
  {
    if ( v1 >= 0 && v1 < dword_D8C32C )
    {
      result = *i;
      if ( *i )
      {
        if ( *(_DWORD *)(result + 4) == a1 )
          break;
      }
    }
    if ( ++v1 >= dword_D8C32C )
      return 0;
  }
  return result;
}

// 0x004322A0
int sub_4322A0(int a2)
{
  return PtrArray::SetAt(*((_DWORD *)this + 3), a2);
}

// 0x004322C0
int sub_4322C0(int a2)
{
  int v3; // eax
  int v5; // ebp
  int v6; // edi
  _DWORD *v7; // ebx
  _DWORD *v8; // esi
  int v9; // esi

  v3 = *((_DWORD *)this + 3);
  if ( v3 )
  {
    v5 = 0;
    v6 = 0;
    if ( v3 > 0 )
    {
      v7 = this + 2;
      do
      {
        if ( v6 < 0 || v6 >= v7[1] )
          v8 = 0;
        else
          v8 = *(_DWORD **)(*v7 + 4 * v6);
        if ( (*(int (**)(_DWORD *))(*v8 + 4))(v8) )
        {
          (*(void (**)(_DWORD *, int))(*v8 + 8))(v8, a2);
        }
        else
        {
          if ( v8[1] && v8 )
            (*(void (**)(_DWORD *, int))*v8)(v8, 1);
          if ( v6 >= 0 && v6 < v7[1] )
            *(_DWORD *)(*v7 + 4 * v6) = 0;
          v5 = 1;
        }
        ++v6;
      }
      while ( v6 < *((_DWORD *)this + 3) );
      if ( v5 )
      {
        v9 = 0;
        while ( v9 < *((_DWORD *)this + 3) )
        {
          if ( v9 >= 0 && v9 < v7[1] && *(_DWORD *)(*v7 + 4 * v9) )
            ++v9;
          else
            v9->InsertAt(1);
        }
      }
    }
  }
  else
  {
    while ( PtrArray::~PtrArray(*((_DWORD *)this + 1)) != 2 )
    {
      if ( (int)*((_DWORD *)this + 3) > 0 )
        return 0;
    }
    if ( !*((_DWORD *)this + 3) )
      return 1;
  }
  return 0;
}

// 0x004323C0
void sub_4323C0(int a1)
{
  int v1; // ebp
  int v2; // ebx
  int v3; // esi
  char *v4; // edi
  int v5; // eax
  int i; // esi

  v1 = dword_D8C32C;
  v2 = 0;
  v3 = 0;
  if ( dword_D8C32C > 0 )
  {
    do
    {
      if ( v3 < 0 || v3 >= dword_D8C32C )
        v4 = 0;
      else
        v4 = *(char **)(dword_D8C328 + 4 * v3);
      if ( v4->IsScriptRuning(a1) )
      {
        if ( v4 )
        {
          sub_431CD0(v4);
          operator delete(v4);
        }
        if ( v3 >= 0 && v3 < dword_D8C32C )
          *(_DWORD *)(dword_D8C328 + 4 * v3) = 0;
        v2 = 1;
      }
      ++v3;
    }
    while ( v3 < v1 );
    if ( v2 )
    {
      v5 = dword_D8C32C;
      for ( i = 0; i < dword_D8C32C; v5 = dword_D8C32C )
      {
        if ( i >= 0 && i < v5 && *(_DWORD *)(dword_D8C328 + 4 * i) )
          ++i;
        else
          i->InsertAt(1);
      }
    }
  }
}

// 0x00432480
int sub_432480()
{
  PalScriptMgr::IfHaveScript();
  PtrArray::SetSize();
  return sub_434670(dword_D8C308);
}

// 0x004324A0
BOOL sub_4324A0()
{
  return dword_D8C32C > 0;
}

// 0x004324B0
int sub_4324B0(int a1)
{
  int v1; // eax
  _DWORD *i; // esi
  int v3; // ecx

  if ( !a1 )
    return 0;
  v1 = 0;
  if ( dword_D8C32C <= 0 )
    return 0;
  for ( i = (_DWORD *)dword_D8C328; ; ++i )
  {
    v3 = v1 < 0 || v1 >= dword_D8C32C ? 0 : *i;
    if ( v3 == a1 )
      break;
    if ( ++v1 >= dword_D8C32C )
      return 0;
  }
  return 1;
}

// 0x00432500
_DWORD * sub_432500(const char *a1, const char *a2)
{
  unsigned int v2; // eax
  _DWORD *result; // eax
  char Buffer[64]; // [esp+0h] [ebp-40h] BYREF

  _snprintf(Buffer, 0x3Fu, "_%s_%s", a1, a2);
  v2 = sub_4325A0(Buffer);
  result = v2->Destroy(0);
  if ( result )
    byte_D8C339 = 1;
  return result;
}

// 0x00432550
int sub_432550()
{
  int v0; // eax
  int i; // edi
  void *v2; // esi

  v0 = dword_D8C32C;
  for ( i = 0; i < v0; ++i )
  {
    if ( i >= 0 && i < v0 )
    {
      v2 = *(void **)(dword_D8C328 + 4 * i);
      if ( v2 )
      {
        sub_431CD0(*(char **)(dword_D8C328 + 4 * i));
        operator delete(v2);
        v0 = dword_D8C32C;
      }
    }
  }
  return sub_4326A0(0, -1);
}
