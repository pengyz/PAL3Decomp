#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/Math.h"

// 0x004B8200
double Math::RandomLerp(float fFrom, float fTo)
{
  if ( fFrom == fTo )
    return fFrom;
  else
    return (double)(rand() % 10000 + 1) * (fTo - fFrom) * 0.000099999997 + fFrom;
}
