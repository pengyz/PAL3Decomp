#include "pal3/gen/UILBColumn.h"

// 0x0043DCA0
int sub_43DCA0()
{
  MEMORY[0xD90064] = 1094713344;
  return 1094713344;
}

// 0x0043DCB0
// attributes: thunk
void UILBColumn::~UILBColumn()
{
  UILBColumn::Destroy();
}

// 0x0043DCC0
void sub_43DCC0()
{
  MEMORY[0xD90060] = 12.0 + 12.0;
}
