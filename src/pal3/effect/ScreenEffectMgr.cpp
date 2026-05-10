#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ScreenEffectMgr.h"
#include "pal3/gen/ScreenEffect.h"

// Unnamed globals (extern)
extern unsigned char byte_DE7E90;
extern int stru_DE7DF8;
extern int unknown_libname_430;

// 0x004BE4A0
void ScreenEffectMgr::Render()
{
  int v2; // edi
  int v3; // edx
  int v4; // ecx
  void **v5; // eax
  int *v6; // eax
  int *v7; // esi
  int v8; // ecx
  void *v9; // [esp-8h] [ebp-20h]

  if ( *((_DWORD *)this + 37) )
  {
    v2 = **((_DWORD **)this + 29);
    (*(void (**)(int))(*(_DWORD *)v2 + 16))(v2);
    if ( !*(_DWORD *)(v2 + 8) && !*(_BYTE *)(v2 + 20) )
    {
      v3 = *((_DWORD *)this + 29) + 4;
      v4 = *((_DWORD *)this + 37) - 1;
      *((_DWORD *)this + 29) = v3;
      *((_DWORD *)this + 37) = v4;
      if ( !v4 || v3 == *((_DWORD *)this + 28) )
      {
        v5 = (void **)*((_DWORD *)this + 30);
        *((_DWORD *)this + 30) = v5 + 1;
        operator delete(*v5);
        if ( *((_DWORD *)this + 37) )
        {
          v6 = (int *)*((_DWORD *)this + 30);
          v7 = (int *)this + 27;
          v8 = *v6;
          * v7 = (*)*v6;
          v7[1] = v8 + 4096;
          v7[2] = v8;
          v7[3] = (int)v6;
        }
        else
        {
          *((_DWORD *)this + 27) = 0;
          *((_DWORD *)this + 28) = 0;
          *((_DWORD *)this + 29) = 0;
          *((_DWORD *)this + 30) = 0;
          *((_DWORD *)this + 31) = 0;
          v9 = (void *)*((_DWORD *)this + 35);
          *((_DWORD *)this + 32) = 0;
          *((_DWORD *)this + 33) = 0;
          *((_DWORD *)this + 34) = 0;
          operator delete(v9);
        }
      }
    }
  }
}

// 0x004BE590
ScreenEffect * ScreenEffectMgr::GetInstance()
{
  if ( (byte_DE7E90 & 1) == 0 )
  {
    byte_DE7E90 |= 1u;
    ((ScreenEffect *)&stru_DE7DF8)->ScreenEffect();
    atexit(unknown_libname_430);
  }
  return &stru_DE7DF8;
}
