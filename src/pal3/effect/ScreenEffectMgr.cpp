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
  char *tail; // esi
  int v8; // ecx
  void *v9; // [esp-8h] [ebp-20h]

  if ( *(_DWORD *)&this->_tail[40] )
  {
    v2 = **(_DWORD **)&this->_tail[8];
    (*(void (**)(int))(*(_DWORD *)v2 + 16))(v2);
    if ( !*(_DWORD *)(v2 + 8) && !*(_BYTE *)(v2 + 20) )
    {
      v3 = *(_DWORD *)&this->_tail[8] + 4;
      v4 = *(_DWORD *)&this->_tail[40] - 1;
      *(_DWORD *)&this->_tail[8] = v3;
      *(_DWORD *)&this->_tail[40] = v4;
      if ( !v4 || v3 == *(_DWORD *)&this->_tail[4] )
      {
        v5 = *(void ***)&this->_tail[12];
        *(_DWORD *)&this->_tail[12] = v5 + 1;
        operator delete(*v5);
        if ( *(_DWORD *)&this->_tail[40] )
        {
          v6 = (int *)*(int **)&this->_tail[12];
          tail = (char *)this->_tail;
          v8 = *v6;
          *(_DWORD *)tail = *v6;
          *((_DWORD *)tail + 1) = v8 + 4096;
          *((_DWORD *)tail + 2) = v8;
          *((_DWORD *)tail + 3) = v6;
        }
        else
        {
          *(_DWORD *)this->_tail = 0;
          *(_DWORD *)&this->_tail[4] = 0;
          *(_DWORD *)&this->_tail[8] = 0;
          *(_DWORD *)&this->_tail[12] = 0;
          *(_DWORD *)&this->_tail[16] = 0;
          v9 = (void *)*(void **)&this->_tail[32];
          *(_DWORD *)&this->_tail[20] = 0;
          *(_DWORD *)&this->_tail[24] = 0;
          *(_DWORD *)&this->_tail[28] = 0;
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
