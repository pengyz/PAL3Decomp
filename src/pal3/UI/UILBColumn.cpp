#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UILBColumn.h"

// 0x0043DCA0
UILBColumn::UILBColumn()
{
  *(_DWORD *)&g_GameData_0._data[7076] = 1094713344;
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
  *(float *)&g_GameData_0._data[7072] = 12.0 + 12.0;
}
