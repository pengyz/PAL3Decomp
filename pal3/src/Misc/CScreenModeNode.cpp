#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CScreenModeNode.h"

// 0x0053D3A0
CScreenModeNode::CScreenModeNode()
{
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 30) = 0;
  *((_DWORD *)this + 31) = 0;
  memset(this + 1, 0, 0x18u);
}
