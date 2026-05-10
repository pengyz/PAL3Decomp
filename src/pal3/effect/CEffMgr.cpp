#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffMgr.h"

// Forward declarations for unnamed functions
int sub_4D5A00(...);

// 0x004D58A0
_DWORD * CEffMgr::Reset()
{
  sub_4D5A00((int *)this);
  *(_DWORD *)&this->m_EffClass[13].szName[8] = 1;
  *(_DWORD *)&this->m_EffClass[13].szName[12] = timeGetTime();
  *(_DWORD *)&this->m_EffClass[13].szName[16] = 0;
  return &this->m_pDisplay;
}
