#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CG_Entry.h"

// 0x0042C920
char * CG_Entry::GetCGEntry()
{
  char *v2; // esi
  int v3; // edi

  v2 = this + 12;
  v3 = 4;
  do
  {
    v2 += 12;
    --v3;
  }
  while ( v3 );
  memset(this, 0, 0x4Cu);
  return this;
}
