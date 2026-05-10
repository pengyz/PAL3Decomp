#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Combat.h"

// Unnamed globals (extern)
extern unsigned char byte_17A9927;

// 0x004DFD20
char Combat::LogMessage(int a1, int a2, int a3, char *format)
{
  int v4; // eax
  char ArgList; // [esp+14h] [ebp+14h] BYREF

  LOBYTE(v4) = byte_17A9927;
  if ( byte_17A9927 )
  {
    vsprintf((char *const)(a1 + 280 * *(_DWORD *)(a1 + 16) + 24), format, &ArgList);
    *(float *)(a1 + 280 * *(_DWORD *)(a1 + 16) + 284) = ((double)a2 + (double)a2) / (double)(int)g_pGameTime - 1.0;
    *(float *)(a1 + 280 * *(_DWORD *)(a1 + 16) + 288) = 1.0 - ((double)a3 + (double)a3) / (double)(int)g_pAbsTime;
    *(_DWORD *)(a1 + 280 * *(_DWORD *)(a1 + 16) + 20) = 3;
    *(_DWORD *)(a1 + 280 * *(_DWORD *)(a1 + 16) + 296) = 1098907648;
    *(_DWORD *)(a1 + 280 * (*(_DWORD *)(a1 + 16) + 1)) = *(_DWORD *)(a1 + 8);
    v4 = *(_DWORD *)(a1 + 16) + 1;
    *(_DWORD *)(a1 + 16) = v4;
  }
  return v4;
}
