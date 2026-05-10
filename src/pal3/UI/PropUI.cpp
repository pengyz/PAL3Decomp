#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PropUI.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_451E50(...);
int sub_4528F0(...);

// Unnamed globals (extern)
extern void *off_56B1BC;

// 0x00452580
int PropUI::Create()
{
  ((UIListBox *)this)->UIListBox();
  ((UIWnd *)&this->bkWndX)->ctor_2790();
  ((UIWnd *)&this->m_PropData.m_EntrySale[216])->ctor_1CC0();
  *(_DWORD *)this->_pad_0000 = &off_56B1BC;
  return (int)this->_pad_0000;
}

// 0x00452670
void PropUI::Init()
{
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, 800, 600, 0);
  sub_4528F0((gbRefObject **)&this->bkWndX, 100, (int)this);
  sub_451E50((int)&this->m_PropData.m_EntrySale[216], (int)this);
}
