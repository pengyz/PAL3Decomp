#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/RenderTargetNode.h"

// 0x004BD830
RenderTargetNode::RenderTargetNode()
{
  *(_DWORD *)&this->_tail_000[92] = 0;
}
