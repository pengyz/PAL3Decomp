#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIPushButton.h"

// 0x0043A090
void UIPushButton::SetAnimOffset(int thisa, int nVal, float fVal)
{
  double v4; // st7
  double v5; // st6

  v4 = *(float *)&nVal + *((float *)&this->_todo_0EC + 3);
  this->_todo_0EC = thisa;
  *((float *)this + 63) = v4;
  v5 = v4 * 0.0027777778 * 360.0;
  if ( v4 > v5 )
    *((float *)this + 63) = 360.0 - (v4 - v5) + v4;
}

// 0x0043A0E0
int UIPushButton::SetParam(int nVal)
{
  *(&this->_todo_0EC + 3) = nVal;
  return nVal;
}
