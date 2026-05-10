#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PtrArray.h"

// Forward declarations for unnamed functions
int sub_432660(...);
int sub_4326A0(...);
int sub_432770(...);
int sub_4327B0(...);
int sub_433F90(...);
int sub_434130(...);
int sub_4341E0(...);
int sub_434240(...);
int sub_4343B0(...);
int sub_4343F0(...);
int sub_434490(...);
int sub_4344F0(...);
int sub_434670(...);
int sub_4348E0(...);
int sub_5372D0(...);

// Unnamed globals (extern)
extern int dword_D8C348;
extern int dword_D8C34C;
extern int dword_D8C360;
extern int dword_D8C364;
extern int dword_D8E468;
extern int dword_D8E46C;

// 0x00432660
_DWORD * sub_432660()
{
  *this = 0;
  *((_DWORD *)this + 2) = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 3) = 32;
  return this;
}

// 0x00432770
void sub_432770(int a2, int a3)
{
  if ( a2 >= *((_DWORD *)this + 1) )
    sub_4326A0((int)this, a2 + 1, -1);
  *(_DWORD *)(*this + 4 * a2) = a3;
}

// 0x004327B0
int sub_4327B0(int a2, int a3)
{
  int v4; // eax
  int result; // eax

  v4 = *((_DWORD *)this + 1) - a2 - a3;
  if ( v4 )
    memcpy((void *)(*this + 4 * a2), (const void *)(*this + 4 * (a2 + a3)), 4 * v4);
  result = *((_DWORD *)this + 1) - a3;
  *((_DWORD *)this + 1) = result;
  return result;
}

// 0x00434130
int sub_434130(int a1, int a2, char a3)
{
  int result; // eax
  int v4; // edx

  result = a1;
  *(_BYTE *)a1 = a3;
  switch ( a3 )
  {
    case 1:
    case 2:
    case 4:
      *(_WORD *)(a1 + 2) = 4;
      *(_DWORD *)(a1 + 4) = **(_DWORD **)(a2 + 8);
      result = *(_DWORD *)(a2 + 8) + 4;
      *(_DWORD *)(a2 + 8) = result;
      break;
    case 3:
      *(_WORD *)(a1 + 2) = **(_WORD **)(a2 + 8);
      v4 = *(_DWORD *)(a2 + 8) + 2;
      *(_DWORD *)(a2 + 8) = v4;
      *(_DWORD *)(a1 + 4) = v4;
      result = *(unsigned __int16 *)(a1 + 2) + *(_DWORD *)(a2 + 8);
      *(_DWORD *)(a2 + 8) = result;
      break;
    case 5:
      *(_WORD *)(a1 + 2) = 2;
      *(_DWORD *)(a1 + 4) = **(unsigned __int16 **)(a2 + 8);
      result = *(_DWORD *)(a2 + 8) + 2;
      *(_DWORD *)(a2 + 8) = result;
      break;
    default:
      *(_BYTE *)a1 = -1;
      *(_WORD *)(a1 + 2) = 0;
      *(_DWORD *)(a1 + 4) = 0;
      break;
  }
  return result;
}

// 0x004341E0
int sub_4341E0(int a1)
{
  unsigned int v2; // edi

  if ( !a1 )
    return 0;
  v2 = *(_DWORD *)(*(_DWORD *)a1 + 68) + *(_DWORD *)(*(_DWORD *)a1 + 72);
  if ( *(_DWORD *)(a1 + 8) >= v2 )
    return 2;
  dword_D8E468 = a1;
  if ( *(_DWORD *)(a1 + 8) < v2 )
  {
    do
      sub_433F90();
    while ( *(_BYTE *)(a1 + 4) != 1 && *(_DWORD *)(a1 + 8) < v2 );
  }
  dword_D8E468 = 0;
  return 1;
}

// 0x00434240
void sub_434240()
{
  int v0; // esi
  int v1; // edi
  void **v2; // ebx
  int v3; // esi
  int v4; // eax
  unsigned __int16 *v5; // esi
  int v6; // edi
  int v7; // eax
  int i; // [esp+Ch] [ebp-8h]
  int v9; // [esp+10h] [ebp-4h]

  v0 = dword_D8C34C;
  v1 = 0;
  v9 = dword_D8C34C;
  for ( i = 0; v1 < v0; i = v1 )
  {
    if ( v1 < 0 || v1 >= dword_D8C34C )
      v2 = 0;
    else
      v2 = *(void ***)(dword_D8C348 + 4 * v1);
    if ( *v2 )
    {
      if ( *((_WORD *)*v2 + 38) )
      {
        v3 = 0;
        do
        {
          v4 = (int)v2[19] + 8 * v3;
          if ( *(_BYTE *)v4 == 3 )
          {
            free(*(void **)(v4 + 4));
            *((_DWORD *)v2[19] + 2 * v3 + 1) = 0;
          }
          ++v3;
        }
        while ( v3 < *((unsigned __int16 *)*v2 + 38) );
        free(v2[19]);
        v2[19] = 0;
      }
      v5 = (unsigned __int16 *)*v2;
      if ( *((_DWORD *)*v2 + 18) )
      {
        free(*((void **)*v2 + 18));
        *((_DWORD *)v5 + 18) = 0;
      }
      if ( v5[38] )
      {
        v6 = 0;
        do
        {
          v7 = *((_DWORD *)v5 + 20) + 8 * v6;
          if ( *(_WORD *)(v7 + 2) )
          {
            free(*(void **)(v7 + 4));
            *(_DWORD *)(*((_DWORD *)v5 + 20) + 8 * v6 + 4) = 0;
          }
          ++v6;
        }
        while ( v6 < v5[38] );
        free(*((void **)v5 + 20));
        v1 = i;
        *((_DWORD *)v5 + 20) = 0;
      }
      operator delete(*v2);
      v0 = v9;
      *v2 = 0;
    }
    free(v2);
    ++v1;
  }
  sub_4326A0((int)&dword_D8C348, 0, -1);
  dword_D8C360 = -1;
  memset(dword_D8C364, 0, 0x100u);
  dword_D8E468 = 0;
  if ( Block )
  {
    free(Block);
    Block = 0;
  }
  dword_D8E46C = 0;
}

// 0x004343B0
char * sub_4343B0(unsigned __int16 a1, int a2)
{
  int v2; // ecx

  v2 = a2;
  if ( !a2 )
    v2 = dword_D8E468;
  if ( (a1 & 0x8000u) == 0 )
    return (char *)(*(_DWORD *)(v2 + 76) + 8 * a1);
  else
    return (char *)Block + 24 * (a1 & 0x7FFF);
}

// 0x004343F0
char * sub_4343F0(const char *a1)
{
  int v1; // edi
  const char *i; // ebp

  v1 = 0;
  if ( dword_D8E46C <= 0 )
    return 0;
  for ( i = (char *)Block + 8; strcmp(a1, i); i += 24 )
  {
    if ( ++v1 >= dword_D8E46C )
      return 0;
  }
  return (char *)Block + 24 * v1;
}

// 0x00434490
void sub_434490(int _this)
{
  sub_434670(this);
  operator delete(*(void **)(this + 8));
  *(_DWORD *)(this + 8) = 0;
  *(_DWORD *)(this + 12) = 0;
  *(_DWORD *)(this + 16) = 0;
}

// 0x004344F0
struct gbVFile * sub_4344F0(int _this, const char *a2)
{
  struct gbVFile *result; // eax
  int v4; // edi
  bool v5; // zf
  int v6; // ebx
  int v7; // [esp+20h] [ebp-10h] BYREF
  char v8[5]; // [esp+24h] [ebp-Ch] BYREF
  int v9; // [esp+29h] [ebp-7h]

  sub_434670(this);
  result = g_pVFileSys->OpenFile(a2, 0x201u);
  *(_DWORD *)this = result;
  if ( result )
  {
    g_pVFileSys->Read(v8, 7u, result);
    if ( !strcmp(v8, "SCE") )
    {
      if ( v8[4] == 1 )
      {
        result = (struct gbVFile *)malloc(72 * (unsigned __int16)v9);
        *(_DWORD *)(this + 24) = result;
        if ( result )
        {
          memset(result, 0, 72 * (unsigned __int16)v9);
          g_pVFileSys->Read(*(void **)(this + 24), 72 * (unsigned __int16)v9, *(struct gbVFile **)this);
          v4 = 0;
          v5 = (_WORD)v9 == 0;
          *(_WORD *)(this + 20) = v9;
          if ( !v5 )
          {
            v6 = 0;
            do
            {
              v7 = sub_4348E0(v6 + *(_DWORD *)(this + 24));
              sub_5372D0(*(_DWORD *)(this + 12), 1, &v7);
              ++v4;
              v6 += 72;
            }
            while ( v4 < (unsigned __int16)v9 );
          }
          g_pVFileSys->CloseFile(*(struct gbVFile **)this);
          *(_DWORD *)this = 0;
          return (struct gbVFile *)1;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}
