#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/Comp_DonateUI.h"

// Unnamed globals (extern)
extern RoleSystem stru_C059A0;

// 0x004A6030
BOOL Comp_DonateUI::ProcessInput()
{
  BOOL result; // eax
  int v3; // edi
  int nVal; // [esp+0x10] [ebp+0x4]

  LOBYTE(result) = *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + nVal);
  if ( result )
  {
    if ( *(&Buffer.m_partyActor.m_nActionParam + 1408 * nVal) )
    {
      v3 = -11356565;
    }
    else if ( *(&Buffer.m_partyActor.m_bActionFlag2 + 1408 * nVal) )
    {
      v3 = -2198083;
    }
    else if ( *(&Buffer.m_partyActor.m_bActionFlag3 + 1408 * nVal) )
    {
      v3 = -13002067;
    }
    else if ( *(&Buffer.m_partyActor.m_bActionActive + 1408 * nVal) )
    {
      v3 = -2198223;
    }
    else
    {
      v3 = *((_BYTE *)&Buffer.m_partyActor.m_nActionState + 1408 * nVal) != 0 ? -2707878 : -1;
    }
    ((NPC *)((char *)this + 3788 * nVal + 155292))->NPC::UpdateAnim();
    ((j_NPC *)nVal)->NPC::UpdateAnim(v3);
    ((UITitle_XJTM *)*((UITitle_XJTM **)this + 44015))->UpdateNPCAnims2(nVal, v3);
    ((UIBigMap *)*((UIBigMap **)this + 44016))->UpdateNPCAnimations(nVal, v3);
    return ((UITitle_XJTM *)*((UITitle_XJTM **)this + 44017))->UpdateNPCAnims(nVal, v3);
  }
  return result;
}
