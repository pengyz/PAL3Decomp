#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/Combat.h"

// 0x0040CCD0
int Combat::GetSlotCount()
{
  int result; // eax

  result = *((_DWORD *)this + 1);
  if ( result )
    return (*((_DWORD *)this + 2) - result) / 12;
  return result;
}

// 0x004CDB60
char Combat::Func_4CDB60()
{
  ((CEffMgr *)this)->ReleaseCompletedEffects();
  return 1;
}

// 0x004DFD20
char Combat::LogMessage(char *a2, int a3, char *format, ...)
{
  int v4; // eax
  va_list ArgList; // [esp+0x14] [ebp+0x14] BYREF

  va_start(ArgList, format);
  LOBYTE(v4) = HIBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole);
  if ( HIBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) )
  {
    vsprintf((char *const)this + 280 * *((_DWORD *)this + 4) + 24, format, ArgList);
    *((float *)this + 70 * *((_DWORD *)this + 4) + 71) = ((double)(int)a2 + (double)(int)a2) / (double)g_DrvInfo.width
                                                       - 1.0;
    *((float *)this + 70 * *((_DWORD *)this + 4) + 72) = 1.0 - ((double)a3 + (double)a3) / (double)g_DrvInfo.height;
    *((_DWORD *)this + 70 * *((_DWORD *)this + 4) + 5) = 3;
    *((_DWORD *)this + 70 * *((_DWORD *)this + 4) + 74) = 1098907648;
    *(this + 70 * *((_DWORD *)this + 4) + 70) = *(this + 2);
    v4 = *((_DWORD *)this + 4) + 1;
    *((_DWORD *)this + 4) = v4;
  }
  return v4;
}

// 0x004F4820
unsigned __int8 Combat::HandleControlCmd(int idx)
{
  CCBControl *v3; // ecx
  int v4; // eax
  _BYTE *v5; // ecx
  unsigned __int8 result; // al

  v3 = *(CCBControl **)(*((_DWORD *)this + 130) + 8);
  if ( v3->m_bActive && ((CCBControl *)v3)->GetControl() == idx )
  {
    ((CCBControl *)*(CCBControl **)(*((_DWORD *)this + 130) + 8))->GetState();
    v4 = 24;
    v5 = (char *)this + 577;
    do
    {
      if ( *v5 )
      {
        *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this + 131) + v4) + 280) = 0;
        *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this + 131) + v4) + 274) = 0;
      }
      v4 += 4;
      v5 += 892;
    }
    while ( v4 < 68 );
  }
  result = ((CCBSystem *)*(CCBSystem **)(*((_DWORD *)this + 130) + 12))->IsCmdEmpty(idx);
  if ( !result && !*((_BYTE *)this + 549) )
    return (unsigned __int8)((CCBSystem *)*(CCBSystem **)(*((_DWORD *)this + 130) + 12))->GetCmdPtr(idx);
  return result;
}
