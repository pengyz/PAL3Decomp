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
  *(_DWORD *)&this->_pad_0000[4] = 0;
  this->_pad_0000[8] = 0;
  *(_DWORD *)&this->_pad_0000[16] = 0;
  *(_DWORD *)&this->_pad_0000[20] = 0;
  *(_DWORD *)&this->_pad_0000[24] = 0;
  *(_DWORD *)&this->_pad_0000[28] = -1;
  *(_DWORD *)&this->_pad_0000[32] = -1;
  *(_DWORD *)&this->_pad_0000[36] = 0;
  *(_DWORD *)&this->_pad_0000[40] = 0;
  *(_DWORD *)&this->_pad_0000[44] = 0;
  *(_DWORD *)&this->_pad_0000[12] = &off_56FA6C;
  this->m_vecOffsetPos.x = NAN;
  *(_DWORD *)this->_pad_0000 = &off_56FA30;
  *(_DWORD *)&this->_pad_0000[12] = &off_56FA24;
  LOBYTE(this->m_pGeomNode) = 0;
  BYTE1(this->m_pGeomNode) = 0;
  BYTE2(this->m_pGeomNode) = 0;
  HIBYTE(this->m_pGeomNode) = 0;
  BYTE2(this->m_vecCurPos.x) = 0;
  LOBYTE(this->m_vecCurPos.x) = 0;
  BYTE1(this->m_vecCurPos.x) = 0;
  this->m_vecCurPos.y = 0.0;
  this->m_vecCurPos.z = 0.0;
  *(_DWORD *)this->_pad_0038 = 0;
  *(_DWORD *)&this->_pad_0038[4] = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 1066) = 0;
  *((_DWORD *)this + 1067) = 0;
  memset((char *)this + 168, 0, 0x1000u);
  return this->_pad_0000;
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

  LOBYTE(this->m_pGeomNode) = 1;
  BYTE1(this->m_pGeomNode) = 1;
  this->_pad_0000[8] = 0;
  HIBYTE(this->m_pGeomNode) = *(_BYTE *)(a2 + 214);
  sub_4D1EF0(this);
  this->m_vecOffsetPos.z = 257;
  *((_DWORD *)this + 38) = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *((float *)this + 34) = (float)HIBYTE(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *((float *)this + 35) = (float)(unsigned __int8)BYTE2(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *((float *)this + 36) = (float)(unsigned __int8)BYTE1(*(_DWORD *)(a2 + 204));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  v7 = *(unsigned __int8 *)(a2 + 204);
  *(_DWORD *)&this->_pad_0044[4] = 0;
  *((float *)this + 37) = (float)v7;
  *(_DWORD *)this->_pad_0044 = *(_DWORD *)(a2 + 180);
  this->m_fSizeZ = *(float *)(a2 + 196);
  *((_DWORD *)this + 32) = *(_DWORD *)(a2 + 216);
  *((_DWORD *)this + 33) = *(_DWORD *)(a2 + 220);
  *(_DWORD *)this->_pad_0050 = *(_DWORD *)(a2 + 200);
  *(_DWORD *)&this->_pad_0050[4] = *(_DWORD *)(a2 + 200);
  this->m_vecRot.x = a3 + *(float *)(a2 + 184);
  this->m_vecRot.y = a4 + *(float *)(a2 + 188);
  v8 = a5 + *(float *)(a2 + 192);
  *(_DWORD *)&this->m_bVisible = 0;
  this->m_fSizeX = 0.0;
  this->m_fSizeY = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  this->m_vecRot.z = v8;
  return 0;
}
