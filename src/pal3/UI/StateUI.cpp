#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/StateUI.h"
#include "pal3/gen/UIBase.h"

// Forward declarations for unnamed functions
int sub_484E90(...);
int sub_484EB0(...);
int sub_48A310(...);
int sub_48A330(...);
int sub_4945E0(...);
int sub_494600(...);
int sub_49E860(...);
int sub_49E880(...);

// 0x004A4960
int StateUI::Create()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( ((UIBase *)this)->GetSelected() < 5 )
  {
    this->m_Is[1] = data;
    ((UIBase *)this)->SetItemData(1, data);
    sub_48A310(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[24], data);
    sub_4945E0(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[28], data);
    sub_49E860(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[32], data);
    return sub_484E90(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[20], data);
  }
  else
  {
    this->m_Is[1] = 0;
    ((UIBase *)this)->SetItemData(1, 0);
    sub_48A310(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[24], 0);
    sub_4945E0(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[28], 0);
    sub_49E860(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[32], 0);
    return sub_484E90(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[20], 0);
  }
}

// 0x004A4A10
void StateUI::Init()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( ((UIBase *)this)->GetSelected() < 5 )
  {
    this->m_Is[2] = data;
    ((UIBase *)this)->SetItemData(2, data);
    sub_48A330(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[24], data);
    sub_494600(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[28], data);
    sub_49E880(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[32], data);
    sub_484EB0(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[20], data);
  }
  else
  {
    this->m_Is[2] = 0;
    ((UIBase *)this)->SetItemData(2, 0);
    sub_48A330(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[24], 0);
    sub_494600(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[28], 0);
    sub_49E880(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[32], 0);
    sub_484EB0(*(char **)&this->m_RoleState[2].m_WuLing[3]._pad_0000[20], 0);
  }
}
