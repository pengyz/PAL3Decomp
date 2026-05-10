#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UILBColumn.h"

// Unnamed globals (extern)
extern int unk_D90060;
extern int unk_D90064;

// 0x0043DCA0
UILBColumn::UILBColumn()
{
  unk_D90064 = 1094713344;
  1094713344;
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
  unk_D90060 = 12.0 + 12.0;
}
