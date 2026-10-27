#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"

// 0x004B6FB0
int gbChain1DNode::Process()
{
  int result; // eax

  operator delete(this[3].next);
  (((gbChain1D *)&this[1].next))->gbChain1D::~gbChain1D();
  this->~gbChain1DNode();
  return result;
}
