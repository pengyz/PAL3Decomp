#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/NavFaceLayer.h"
#include "Misc/NavFace.h"
#include "Misc/UITitle_BBTY.h"
#include "free_functions.h"

// 0x00452540
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
int NavFaceLayer::GetVertexNum()
{
  return accessor_00452550();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00452560
// attributes: thunk
gbVec3D *NavFaceLayer::GetVertexBuf()
{
  gbVec3D *result; // eax

  // [overlay-fix 2026-10-27] C2352: _nearby_452570 非静态成员非法调用（thunk 形待解）——待归属定谳
  // UITitle_BBTY::_nearby_452570();
  return result;
}
