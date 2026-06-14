#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UILBColumn.h"

// Unnamed globals (extern)
extern int dword_D90064;
extern int unk_D90060;

// 0x0043DCA0
UILBColumn::UILBColumn()
{
  dword_D90064 = 1094713344;
}

// 0x0043DCB0
// attributes: thunk
void UILBColumn::_UILBColumn()
{

}

// 0x0043DCC0
void UILBColumn::Destroy()
{
  unk_D90060 = 12.0 + 12.0;
}
