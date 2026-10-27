#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CG_Entry.h"

// 0x0042C920
char * CG_Entry::GetCGEntry()
{
  char *v2; // esi
  int v3; // edi

  // [overlay-fix 2026-10-27] C2440: this+12 得 CG_Entry* 赋 char*（垃圾形）——待语义修复
  // v2 = this + 12;
  v2 = 0;
  v3 = 4;
  do
  {
    v2 += 12;
    --v3;
  }
  while ( v3 );
  memset(this, 0, 0x4Cu);
  // [overlay-fix 2026-10-27] C2440: return this 得 CG_Entry* 但函数返 char*（签名标注错）——待语义修复
  // return this;
  return 0;
}
