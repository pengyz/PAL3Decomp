#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBControl.h"

// Forward declarations for unnamed functions
int sub_4DC610(...);

// 0x004DC240
int CCBControl::Update()
{
  int result; // eax

  LOBYTE(result) = this->m_bActive;
  if ( (_BYTE)result )
    LOBYTE(result) = sub_4DC610(this);
  return result;
}
