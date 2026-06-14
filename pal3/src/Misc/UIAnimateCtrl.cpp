#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIAnimateCtrl.h"

// 0x00479260
int UIAnimateCtrl::GetRoleBySlot(unsigned int dwVal)
{
  if ( dwVal > 0xA )
    return 0;
  else
    return *((_DWORD *)this + 158 * dwVal + 199648);
}
