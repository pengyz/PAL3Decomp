#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIParticle.h"

// 0x00529400
int * UIParticle::CountActiveParticles()
{
  int *result; // eax
  int v2; // esi
  int *v3; // edx

  result = (int *)p_DWORD[495];
  v2 = 0;
  if ( (int)result > 0 )
  {
    v3 = p_DWORD + 503;
    result = p_DWORD + 557;
    do
    {
      ++v2;
      *(v3 - 2) = *(result - 2);
      *(v3 - 1) = *(result - 1);
      *v3 = *result;
      result += 3;
      v3 += 8;
    }
    while ( v2 < p_DWORD[495] );
  }
  return result;
}
