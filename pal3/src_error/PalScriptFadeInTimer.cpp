#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PalScriptFadeInTimer.h"

// 0x00438530
BOOL PalScriptFadeInTimer::IsFadeDone()
{
  return this[16] == 0;
}
