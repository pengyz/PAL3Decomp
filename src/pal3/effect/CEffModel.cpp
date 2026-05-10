#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffModel.h"

// Forward declarations for unnamed functions
int sub_4D0CE0(...);
int sub_4D0D70(...);
int sub_4D0EC0(...);
int sub_4D1EF0(...);

// Unnamed globals (extern)
extern void *off_56FA24;
extern void *off_56FA30;
extern void *off_56FA6C;

// 0x004D0CE0
_DWORD * sub_4D0CE0()
{
  *((_DWORD *)this + 1) = 0;
  *((_BYTE *)this + 8) = 0;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 7) = -1;
  *((_DWORD *)this + 8) = -1;
  *((_DWORD *)this + 9) = 0;
  *((_DWORD *)this + 10) = 0;
  *((_DWORD *)this + 11) = 0;
  *((_DWORD *)this + 3) = &off_56FA6C;
  *((_DWORD *)this + 18) = -1;
  *this = &off_56FA30;
  *((_DWORD *)this + 3) = &off_56FA24;
  *((_BYTE *)this + 48) = 0;
  *((_BYTE *)this + 49) = 0;
  *((_BYTE *)this + 50) = 0;
  *((_BYTE *)this + 51) = 0;
  *((_BYTE *)this + 54) = 0;
  *((_BYTE *)this + 52) = 0;
  *((_BYTE *)this + 53) = 0;
  *((_DWORD *)this + 14) = 0;
  *((_DWORD *)this + 15) = 0;
  *((_DWORD *)this + 16) = 0;
  *((_DWORD *)this + 17) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 1066) = 0;
  *((_DWORD *)this + 1067) = 0;
  memset(this + 42, 0, 0x1000u);
  return this;
}

// 0x004D0D70
_DWORD *sub_4D0D70()
{
  _DWORD *v0; // eax

  v0 = operator new(0x10B0u);
  if ( v0 )
    return v0->Render();
  else
    return 0;
}

// 0x004D0EC0
int sub_4D0EC0(int _this, int a2, float a3, float a4, float a5)
{
  int v7; // edx
  double v8; // st7

  *(_BYTE *)(this + 48) = 1;
  *(_BYTE *)(this + 49) = 1;
  *(_BYTE *)(this + 8) = 0;
  *(_BYTE *)(this + 51) = *(_BYTE *)(a2 + 214);
  sub_4D1EF0();
  *(_BYTE *)(this + 80) = 1;
  *(_BYTE *)(this + 81) = 1;
  *(_BYTE *)(this + 82) = 0;
  *(_BYTE *)(this + 83) = 0;
  *(_DWORD *)(this + 152) = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *(float *)(this + 136) = (float)HIBYTE(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *(float *)(this + 140) = (float)(unsigned __int8)BYTE2(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *(float *)(this + 144) = (float)(unsigned __int8)BYTE1(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  v7 = *(unsigned __int8 *)(a2 + 204);
  *(_DWORD *)(this + 88) = 0;
  *(float *)(this + 148) = (float)v7;
  *(_DWORD *)(this + 84) = *(_DWORD *)(a2 + 180);
  *(_DWORD *)(this + 124) = *(_DWORD *)(a2 + 196);
  *(_DWORD *)(this + 128) = *(_DWORD *)(a2 + 216);
  *(_DWORD *)(this + 132) = *(_DWORD *)(a2 + 220);
  *(_DWORD *)(this + 104) = *(_DWORD *)(a2 + 200);
  *(_DWORD *)(this + 108) = *(_DWORD *)(a2 + 200);
  *(float *)(this + 92) = a3 + *(float *)(a2 + 184);
  *(float *)(this + 96) = a4 + *(float *)(a2 + 188);
  v8 = a5 + *(float *)(a2 + 192);
  *(_DWORD *)(this + 112) = 0;
  *(_DWORD *)(this + 116) = 0;
  *(_DWORD *)(this + 120) = 0;
  *(_DWORD *)(this + 76) = 0;
  *(float *)(this + 100) = v8;
  return 0;
}
