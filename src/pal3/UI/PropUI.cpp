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
  ((UIWnd *)&this->_data[72])->ctor_2790();
  ((UIWnd *)&this->_data[1084])->ctor_1CC0();
  *(_DWORD *)this->_data = &off_56B1BC;
  return (int)this->_data;
}

// 0x00452670
void PropUI::Init()
{
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, 800, 600, 0);
  sub_4528F0((gbRefObject **)&this->_data[72], 100, (int)this);
  sub_451E50((int)&this->_data[1084], (int)this);
}
