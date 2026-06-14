#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/_Console.h"

// 0x0041C170
void _Console::SetActive(int nVal)
{
  *(_DWORD *)&this->m_cmd[2]._tail_000[108] = 0;
  *(_DWORD *)&this->m_cmd[2]._tail_000[104] = nVal;
  if ( !nVal )
    old_sbh_page_alloc((__old_sbh_page_struct *)this);
}
