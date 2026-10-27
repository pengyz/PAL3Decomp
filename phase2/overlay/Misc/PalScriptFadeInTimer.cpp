#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PalScriptFadeInTimer.h"

// 0x00438530
BOOL PalScriptFadeInTimer::IsFadeDone()
{
  // [overlay-fix 2026-10-27] C2678: this[16] 得类引用无 == 运算（Hex-Rays 垃圾形）——待语义修复
  // return this[16] == 0;
  return 0;
}
