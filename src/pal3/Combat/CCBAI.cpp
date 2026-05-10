#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBAI.h"

// 0x004014F0
char CCBAI::Thunk_GetValue(int a1, int a2)
{
  return 0;
}

// 0x0040CFE0
void * CCBAI::GetTargetRole(void *pOut)
{
  _DWORD *v2; // edx
  int v4; // [esp+Ch] [ebp+8h]

  v2 = (_DWORD *)(this->m_bNewRole[1] + 12 * v4);
  *(_DWORD *)pOut = *v2;
  *((_DWORD *)pOut + 1) = v2[1];
  *((_DWORD *)pOut + 2) = v2[2];
  return pOut;
}

// 0x004D7100
int CCBAI::Update()
{
  ((int)this)->DemandThreadTracer();
  return this->FillAllDemandSatisfy();
}
