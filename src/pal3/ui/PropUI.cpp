#include "pal3/gen/PropUI.h"

// 0x00452580
int PropUI::Create()
{
  this->UIListBox();
  sub_452790((int)&this->UIFrameWnd[72]);
  sub_451CC0((int)&this->UIFrameWnd[1084]);
  *(_DWORD *)this->UIFrameWnd = &off_56B1BC;
  return (int)this->UIFrameWnd;
}

// 0x00452670
void PropUI::Init()
{
  (UIWnd *->SetSelTexture()this, -1, 0, 0, 800, 600, 0);
  sub_4528F0((gbRefObject **)&this->UIFrameWnd[72], 100, (int)this);
  sub_451E50((int)&this->UIFrameWnd[1084], (int)this);
}
