#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/j_UIFrameWnd.h"
#include "pal3/gen/UIFrameWnd.h"

// 0x0044BE70
// attributes: thunk
void j_UIFrameWnd::_UIFrameWnd(UIWnd *this)
{
  ((UIFrameWnd *)this)->_UIFrameWnd();
}
