#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIBase.h"

// 0x004A3900
int UIBase::SetItemData(int id, unsigned int data)
{
  UIBase *v4; // edi
  int result; // eax

  if ( id <= 5 )
  {
    v4 = this + 947 * id;
    (**(void ( ***)(int, _DWORD))&v4[38785])((int)&v4[38785], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[38823])((int)&v4[38823], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[38861])((int)&v4[38861], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[38937])((int)&v4[38937], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[38998])((int)&v4[38998], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39211])((int)&v4[39211], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39272])((int)&v4[39272], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39074])((int)&v4[39074], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39135])((int)&v4[39135], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39310])((int)&v4[39310], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39348])((int)&v4[39348], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39386])((int)&v4[39386], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39424])((int)&v4[39424], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39462])((int)&v4[39462], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39500])((int)&v4[39500], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39538])((int)&v4[39538], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39576])((int)&v4[39576], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39652])((int)&v4[39652], (unsigned __int8)data);
    (**(void ( ***)(int, _DWORD))&v4[39614])((int)&v4[39614], (unsigned __int8)data);
    ((UITitle_XJTM *)*((UITitle_XJTM **)this + 44015))->SetMonsterState(id, data);
    ((UIBigMap *)*((UIBigMap **)this + 44016))->SetEntryVisible(id, data);
    ((UITitle_XJTM *)*((UITitle_XJTM **)this + 44017))->SetMonsterState2(id, data);
    return ((LineupComp *)*((LineupComp **)this + 44014))->DispatchSlotMethod(id, data);
  }
  return result;
}
