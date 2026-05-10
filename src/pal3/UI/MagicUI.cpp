#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MagicUI.h"

// Forward declarations for unnamed functions
int sub_484ED0(...);
int sub_484EF0(...);
int sub_48A350(...);
int sub_48A370(...);
int sub_494620(...);
int sub_494640(...);
int sub_49E8A0(...);
int sub_49E8C0(...);

// 0x004A4AC0
int MagicUI::Create()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( (UIBase *->GetSelected()this) < 5 )
  {
    this->UIFrameWnd[364] = data;
    (UIBase *->SetItemData()this, 3, data);
    sub_48A350(*(char **)&this->UIFrameWnd[176060], data);
    sub_494620(*(char **)&this->UIFrameWnd[176064], data);
    sub_49E8A0(*(char **)&this->UIFrameWnd[176068], data);
    return sub_484ED0(*(char **)&this->UIFrameWnd[176056], data);
  }
  else
  {
    this->UIFrameWnd[364] = 0;
    (UIBase *->SetItemData()this, 3, 0);
    sub_48A350(*(char **)&this->UIFrameWnd[176060], 0);
    sub_494620(*(char **)&this->UIFrameWnd[176064], 0);
    sub_49E8A0(*(char **)&this->UIFrameWnd[176068], 0);
    return sub_484ED0(*(char **)&this->UIFrameWnd[176056], 0);
  }
}

// 0x004A4B70
void MagicUI::Init()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( (UIBase *->GetSelected()this) < 5 )
  {
    this->UIFrameWnd[365] = data;
    (UIBase *->SetItemData()this, 4, data);
    sub_48A370(*(char **)&this->UIFrameWnd[176060], data);
    sub_494640(*(char **)&this->UIFrameWnd[176064], data);
    sub_49E8C0(*(char **)&this->UIFrameWnd[176068], data);
    sub_484EF0(*(char **)&this->UIFrameWnd[176056], data);
  }
  else
  {
    this->UIFrameWnd[365] = 0;
    (UIBase *->SetItemData()this, 4, 0);
    sub_48A370(*(char **)&this->UIFrameWnd[176060], 0);
    sub_494640(*(char **)&this->UIFrameWnd[176064], 0);
    sub_49E8C0(*(char **)&this->UIFrameWnd[176068], 0);
    sub_484EF0(*(char **)&this->UIFrameWnd[176056], 0);
  }
}
