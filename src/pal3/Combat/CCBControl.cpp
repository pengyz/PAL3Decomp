#include "pal3/gen/CCBControl.h"

// 0x004DC240
int CCBControl::Update()
{
  int result; // eax

  LOBYTE(result) = this->m_pCBSystem[36];
  if ( (_BYTE)result )
    LOBYTE(result) = sub_4DC610(this);
  return result;
}
