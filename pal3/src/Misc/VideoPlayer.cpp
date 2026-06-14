#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/VideoPlayer.h"

// 0x0053B720
void VideoPlayer::SetRegion(int nX, int nY)
{
  int v2; // edx
  int v3; // eax
  int v4; // eax
  char *v5; // eax
  char *v6; // ebp
  char *i; // edx
  int v8; // ecx
  int v9; // eax
  _WORD *v10; // eax
  _WORD *v11; // ecx
  _WORD *j; // ebx

  v2 = 0;
  if ( nX )
  {
    qmemcpy((void *)nX, (const void *)nY, 0x85u);
    v3 = *(_DWORD *)(nY + 136);
    if ( v3 )
      v2 = (*(_DWORD *)(nY + 140) - v3) / 656;
    v4 = v2;
    if ( v2 < 0 )
      v4 = 0;
    v5 = (char *)operator new(656 * v4);
    *(_DWORD *)(nX + 136) = v5;
    v6 = *(char **)(nY + 140);
    for ( i = *(char **)(nY + 136); i != v6; v5 += 656 )
    {
      if ( v5 )
        qmemcpy(v5, i, 0x290u);
      i += 656;
    }
    *(_DWORD *)(nX + 140) = v5;
    *(_DWORD *)(nX + 144) = v5;
    *(_BYTE *)(nX + 148) = *(_BYTE *)(nY + 148);
    v8 = *(_DWORD *)(nY + 152);
    if ( v8 )
      v9 = (*(_DWORD *)(nY + 156) - v8) >> 1;
    else
      v9 = 0;
    if ( v9 < 0 )
      v9 = 0;
    v10 = operator new(2 * v9);
    *(_DWORD *)(nX + 152) = v10;
    v11 = *(_WORD **)(nY + 156);
    for ( j = *(_WORD **)(nY + 152); j != v11; ++v10 )
    {
      if ( v10 )
        *v10 = *j;
      ++j;
    }
    *(_DWORD *)(nX + 156) = v10;
    *(_DWORD *)(nX + 160) = v10;
  }
}
