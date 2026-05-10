#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MagicUI.h"
#include "pal3/gen/UIBase.h"

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

  if ( ((UIBase *)this)->GetSelected() < 5 )
  {
    this->_rest[264] = data;
    ((UIBase *)this)->SetItemData(3, data);
    sub_48A350(*(char **)&this->_rest[175960], data);
    sub_494620(*(char **)&this->_rest[175964], data);
    sub_49E8A0(*(char **)&this->_rest[175968], data);
    return sub_484ED0(*(char **)&this->_rest[175956], data);
  }
  else
  {
    this->_rest[264] = 0;
    ((UIBase *)this)->SetItemData(3, 0);
    sub_48A350(*(char **)&this->_rest[175960], 0);
    sub_494620(*(char **)&this->_rest[175964], 0);
    sub_49E8A0(*(char **)&this->_rest[175968], 0);
    return sub_484ED0(*(char **)&this->_rest[175956], 0);
  }
}

// 0x004A4B70
void MagicUI::Init()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( ((UIBase *)this)->GetSelected() < 5 )
  {
    this->_rest[265] = data;
    ((UIBase *)this)->SetItemData(4, data);
    sub_48A370(*(char **)&this->_rest[175960], data);
    sub_494640(*(char **)&this->_rest[175964], data);
    sub_49E8C0(*(char **)&this->_rest[175968], data);
    sub_484EF0(*(char **)&this->_rest[175956], data);
  }
  else
  {
    this->_rest[265] = 0;
    ((UIBase *)this)->SetItemData(4, 0);
    sub_48A370(*(char **)&this->_rest[175960], 0);
    sub_494640(*(char **)&this->_rest[175964], 0);
    sub_49E8C0(*(char **)&this->_rest[175968], 0);
    sub_484EF0(*(char **)&this->_rest[175956], 0);
  }
}
