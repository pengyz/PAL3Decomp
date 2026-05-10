#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffModel.h"
#include "pal3/gen/CEffMgr.h"

// Forward declarations for unnamed functions
int sub_4D1EF0(...);

// Unnamed globals (extern)
extern int nullsub_1;
extern void *off_56FA24;
extern void *off_56FA30;
extern void *off_56FA6C;

// 0x004D0CE0
_DWORD * CEffModel::Render()
{
  this->_d004 = 0;
  this->_b008 = 0;
  this->_d010 = 0;
  this->_d014 = 0;
  this->_d018 = 0;
  this->_d01C = -1;
  this->_d020 = -1;
  this->_d024 = 0;
  this->_d028 = 0;
  this->_d02C = 0;
  this->_d00C = (int)&off_56FA6C;
  this->_d048 = -1;
  this->_p000 = &off_56FA30;
  this->_d00C = (int)&off_56FA24;
  this->_b030 = 0;
  this->_b031 = 0;
  this->_b032 = 0;
  this->_b033 = 0;
  this->_b036 = 0;
  this->_b034 = 0;
  this->_b035 = 0;
  this->_d038 = 0;
  this->_d03C = 0;
  this->_d040 = 0;
  this->_d044 = 0;
  this->_d09C = 0;
  this->_d0A0 = 0;
  this->_d0A4 = 0;
  *((_DWORD *)this + 1066) = 0;
  *((_DWORD *)this + 1067) = 0;
  memset(this->_tail, 0, 0x1000u);
  return &this->_p000;
}

// 0x004D0D70
_DWORD *CEffModel::SetTimeScale()
{
  CEffModel *v0; // eax

  v0 = (CEffModel *)operator new(0x10B0u);
  if ( v0 )
    return v0->Render();
  else
    return 0;
}

// 0x004D0EC0
int CEffModel::ProcInitTask(int a2, float a3, float a4, float a5)
{
  int v7; // edx
  double v8; // st7

  this->_b030 = 1;
  this->_b031 = 1;
  this->_b008 = 0;
  this->_b033 = *(_BYTE *)(a2 + 214);
  sub_4D1EF0(this);
  this->_b050 = 1;
  this->_b051 = 1;
  this->_b052 = 0;
  this->_b053 = 0;
  this->_d098 = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->_f088 = (float)HIBYTE(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->_f08C = (float)(unsigned __int8)BYTE2(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->_f090 = (float)(unsigned __int8)BYTE1(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  v7 = *(unsigned __int8 *)(a2 + 204);
  this->_d058 = 0;
  this->_f094 = (float)v7;
  this->_d054 = *(_DWORD *)(a2 + 180);
  this->_d07C = *(_DWORD *)(a2 + 196);
  this->_d080 = *(_DWORD *)(a2 + 216);
  this->_d084 = *(_DWORD *)(a2 + 220);
  this->_d068 = *(_DWORD *)(a2 + 200);
  this->_d06C = *(_DWORD *)(a2 + 200);
  this->_f05C = a3 + *(float *)(a2 + 184);
  this->_f060 = a4 + *(float *)(a2 + 188);
  v8 = a5 + *(float *)(a2 + 192);
  this->_d070 = 0;
  this->_d074 = 0;
  this->_d078 = 0;
  this->_d04C = 0;
  this->_f064 = v8;
  return 0;
}
