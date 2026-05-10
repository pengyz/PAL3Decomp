#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UILBColumn.h"

// 0x0043DCA0
UILBColumn::UILBColumn()
{
  MEMORY[0xD90064] = 1094713344;
  return 1094713344;
}

// 0x0043DCB0
// attributes: thunk
UILBColumn::~UILBColumn()
{
  UILBColumn::Destroy();
}

// 0x0043DCC0
void UILBColumn::Destroy()
{
  MEMORY[0xD90060] = 12.0 + 12.0;
}
