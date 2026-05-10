#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBControl.h"
#include "pal3/gen/CCBSystem.h"

int sub_4DC610(void *);  // forward decl

// 0x004DC240
int CCBControl::Update()
{
  int result; // eax

  LOBYTE(result) = this->m_pCBSystem[36];
  if ( (_BYTE)result )
    LOBYTE(result) = sub_4DC610(this);
  return result;
}
