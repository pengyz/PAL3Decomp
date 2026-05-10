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
  *(_DWORD *)&this->_data[4] = 0;
  this->_data[8] = 0;
  *(_DWORD *)&this->_data[16] = 0;
  *(_DWORD *)&this->_data[20] = 0;
  *(_DWORD *)&this->_data[24] = 0;
  *(_DWORD *)&this->_data[28] = -1;
  *(_DWORD *)&this->_data[32] = -1;
  *(_DWORD *)&this->_data[36] = 0;
  *(_DWORD *)&this->_data[40] = 0;
  *(_DWORD *)&this->_data[44] = 0;
  *(_DWORD *)&this->_data[12] = &off_56FA6C;
  *(_DWORD *)&this->_data[72] = -1;
  *(_DWORD *)this->_data = &off_56FA30;
  *(_DWORD *)&this->_data[12] = &off_56FA24;
  this->_data[48] = 0;
  this->_data[49] = 0;
  this->_data[50] = 0;
  this->_data[51] = 0;
  this->_data[54] = 0;
  this->_data[52] = 0;
  this->_data[53] = 0;
  *(_DWORD *)&this->_data[56] = 0;
  *(_DWORD *)&this->_data[60] = 0;
  *(_DWORD *)&this->_data[64] = 0;
  *(_DWORD *)&this->_data[68] = 0;
  *(_DWORD *)&this->_data[156] = 0;
  *(_DWORD *)&this->_data[160] = 0;
  *(_DWORD *)&this->_data[164] = 0;
  *((_DWORD *)this + 1066) = 0;
  *((_DWORD *)this + 1067) = 0;
  memset(&this->_data[168], 0, 0x1000u);
  return this->_data;
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

  this->_data[48] = 1;
  this->_data[49] = 1;
  this->_data[8] = 0;
  this->_data[51] = *(_BYTE *)(a2 + 214);
  sub_4D1EF0(this);
  this->_data[80] = 1;
  this->_data[81] = 1;
  this->_data[82] = 0;
  this->_data[83] = 0;
  *(_DWORD *)&this->_data[152] = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->_data[136] = (float)HIBYTE(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->_data[140] = (float)(unsigned __int8)BYTE2(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->_data[144] = (float)(unsigned __int8)BYTE1(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  v7 = *(unsigned __int8 *)(a2 + 204);
  *(_DWORD *)&this->_data[88] = 0;
  *(float *)&this->_data[148] = (float)v7;
  *(_DWORD *)&this->_data[84] = *(_DWORD *)(a2 + 180);
  *(_DWORD *)&this->_data[124] = *(_DWORD *)(a2 + 196);
  *(_DWORD *)&this->_data[128] = *(_DWORD *)(a2 + 216);
  *(_DWORD *)&this->_data[132] = *(_DWORD *)(a2 + 220);
  *(_DWORD *)&this->_data[104] = *(_DWORD *)(a2 + 200);
  *(_DWORD *)&this->_data[108] = *(_DWORD *)(a2 + 200);
  *(float *)&this->_data[92] = a3 + *(float *)(a2 + 184);
  *(float *)&this->_data[96] = a4 + *(float *)(a2 + 188);
  v8 = a5 + *(float *)(a2 + 192);
  *(_DWORD *)&this->_data[112] = 0;
  *(_DWORD *)&this->_data[116] = 0;
  *(_DWORD *)&this->_data[120] = 0;
  *(_DWORD *)&this->_data[76] = 0;
  *(float *)&this->_data[100] = v8;
  return 0;
}
