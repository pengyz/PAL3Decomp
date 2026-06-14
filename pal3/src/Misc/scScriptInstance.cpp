#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/scScriptInstance.h"

// 0x0044E5C0
scScriptInstance * scScriptInstance::_sdtor_25(scScriptInstance *Block, char a2)
{
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x0044E5E0
void scScriptInstance::_scScriptInstance()
{
  ((UIWnd *)this)->_UIWnd();
}
