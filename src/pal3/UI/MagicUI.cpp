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
    this->buf[224] = data;
    ((UIBase *)this)->SetItemData(3, data);
    sub_48A350((char *)this->m_btnPar2[8][0]._element.m_id, data);
    sub_494620((char *)this->m_btnPar2[8][0]._element.m_rect.left, data);
    sub_49E8A0((char *)this->m_btnPar2[8][0]._element.m_rect.top, data);
    return sub_484ED0((char *)this->m_btnPar2[8][0]._element.m_wndcolor.Color, data);
  }
  else
  {
    this->buf[224] = 0;
    ((UIBase *)this)->SetItemData(3, 0);
    sub_48A350((char *)this->m_btnPar2[8][0]._element.m_id, 0);
    sub_494620((char *)this->m_btnPar2[8][0]._element.m_rect.left, 0);
    sub_49E8A0((char *)this->m_btnPar2[8][0]._element.m_rect.top, 0);
    return sub_484ED0((char *)this->m_btnPar2[8][0]._element.m_wndcolor.Color, 0);
  }
}

// 0x004A4B70
void MagicUI::Init()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( ((UIBase *)this)->GetSelected() < 5 )
  {
    this->buf[225] = data;
    ((UIBase *)this)->SetItemData(4, data);
    sub_48A370((char *)this->m_btnPar2[8][0]._element.m_id, data);
    sub_494640((char *)this->m_btnPar2[8][0]._element.m_rect.left, data);
    sub_49E8C0((char *)this->m_btnPar2[8][0]._element.m_rect.top, data);
    sub_484EF0((char *)this->m_btnPar2[8][0]._element.m_wndcolor.Color, data);
  }
  else
  {
    this->buf[225] = 0;
    ((UIBase *)this)->SetItemData(4, 0);
    sub_48A370((char *)this->m_btnPar2[8][0]._element.m_id, 0);
    sub_494640((char *)this->m_btnPar2[8][0]._element.m_rect.left, 0);
    sub_49E8C0((char *)this->m_btnPar2[8][0]._element.m_rect.top, 0);
    sub_484EF0((char *)this->m_btnPar2[8][0]._element.m_wndcolor.Color, 0);
  }
}
