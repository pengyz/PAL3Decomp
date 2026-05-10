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
  this->UIListBox();
  UIWnd::ctor_2790((int)&this->UIFrameWnd[72]);
  UIWnd::ctor_1CC0((int)&this->UIFrameWnd[1084]);
  *(_DWORD *)this->UIFrameWnd = &off_56B1BC;
  return (int)this->UIFrameWnd;
}

// 0x00452670
void PropUI::Init()
{
  UIListBox::SetSelTexture((UIListBox *)this, -1, 0, 0, 800, 600, 0);
  sub_4528F0((gbRefObject **)&this->m_childs, 100, (int)this);
  sub_451E50((int)&this->m_PropData.m_EntrySale[172], (int)this);
}
