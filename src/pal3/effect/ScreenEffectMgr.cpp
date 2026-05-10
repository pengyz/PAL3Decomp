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
  char *v7; // esi
  int v8; // ecx
  void *v9; // [esp-8h] [ebp-20h]

  if ( *(_DWORD *)&this->m_fadeIn[148] )
  {
    v2 = **(_DWORD **)&this->m_fadeIn[116];
    (*(void (**)(int))(*(_DWORD *)v2 + 16))(v2);
    if ( !*(_DWORD *)(v2 + 8) && !*(_BYTE *)(v2 + 20) )
    {
      v3 = *(_DWORD *)&this->m_fadeIn[116] + 4;
      v4 = *(_DWORD *)&this->m_fadeIn[148] - 1;
      *(_DWORD *)&this->m_fadeIn[116] = v3;
      *(_DWORD *)&this->m_fadeIn[148] = v4;
      if ( !v4 || v3 == *(_DWORD *)&this->m_fadeIn[112] )
      {
        v5 = *(void ***)&this->m_fadeIn[120];
        *(_DWORD *)&this->m_fadeIn[120] = v5 + 1;
        operator delete(*v5);
        if ( *(_DWORD *)&this->m_fadeIn[148] )
        {
          v6 = (int *)*(int **)&this->m_fadeIn[120];
          v7 = (char *)&this->m_fadeIn[108];
          v8 = *v6;
          *(_DWORD *)v7 = *v6;
          *((_DWORD *)v7 + 1) = v8 + 4096;
          *((_DWORD *)v7 + 2) = v8;
          *((_DWORD *)v7 + 3) = v6;
        }
        else
        {
          *(_DWORD *)&this->m_fadeIn[108] = 0;
          *(_DWORD *)&this->m_fadeIn[112] = 0;
          *(_DWORD *)&this->m_fadeIn[116] = 0;
          *(_DWORD *)&this->m_fadeIn[120] = 0;
          *(_DWORD *)&this->m_fadeIn[124] = 0;
          v9 = (void *)*(void **)&this->m_fadeIn[140];
          *(_DWORD *)&this->m_fadeIn[128] = 0;
          *(_DWORD *)&this->m_fadeIn[132] = 0;
          *(_DWORD *)&this->m_fadeIn[136] = 0;
          operator delete(v9);
        }
      }
    }
  }
}

// 0x004BE590
_BYTE * ScreenEffectMgr::GetInstance()
{
  if ( (byte_DE7E90 & 1) == 0 )
  {
    byte_DE7E90 |= 1u;
    stru_DE7DF8->ScreenEffect();
    atexit(unknown_libname_430);
  }
  return stru_DE7DF8;
}
