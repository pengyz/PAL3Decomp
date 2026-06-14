#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PAL3VisNode.h"

// 0x004B6F70
PAL3VisNode::PAL3VisNode()
{
  *((_DWORD *)this + 22) = 0;
}
