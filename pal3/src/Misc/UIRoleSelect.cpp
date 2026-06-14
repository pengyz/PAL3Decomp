#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIRoleSelect.h"

// 0x004A1530
int UIRoleSelect::SetByte(char value)
{
  BYTE1(this->m_bk.m_currect.left) = value;
  if ( this->m_bk.m_rect.bottom )
  {
    if ( this->m_bk.m_rect.bottom == 2 )
    {
      (*(void ( **)(int *, int))this->m_list.m_scrollbar.m_bk.m_bfocus)(
        &this->m_list.m_scrollbar.m_bk.m_bfocus,
        1);
      ((void ( *)(_PlugInfo **, int))this->m_list.m_scrollbar.m_texarrayInfo[7]->filepos)(
        &this->m_list.m_scrollbar.m_texarrayInfo[7],
        1);
      (**(void ( ***)(char *, int))&this->m_list.m_column[1].head[24])(&this->m_list.m_column[1].head[24], 1);
      (**(void ( ***)(char *, int))&this->m_list.m_column[5].head[32])(&this->m_list.m_column[5].head[32], 1);
      this->m_list.m_column[2].head[40] = 0;
      this->m_list.m_column[6].head[48] = 0;
    }
    else if ( this->m_bk.m_rect.bottom == 3 )
    {
      (*(void ( **)(LONG *, int))this->m_list.m_rect.right)(&this->m_list.m_rect.right, 1);
    }
  }
  else
  {
    (*(void ( **)(int *, int))this->m_list.m_scrollbar.m_bk.m_bfocus)(
      &this->m_list.m_scrollbar.m_bk.m_bfocus,
      1);
    ((void ( *)(_PlugInfo **, int))this->m_list.m_scrollbar.m_texarrayInfo[7]->filepos)(
      &this->m_list.m_scrollbar.m_texarrayInfo[7],
      1);
    (**(void ( ***)(char *, int))&this->m_list.m_column[1].head[24])(&this->m_list.m_column[1].head[24], 1);
    this->m_list.m_column[2].head[40] = 0;
  }
  ++g_nUILayoutFlags;
  this->m_bmodal = 1;
  LOBYTE(this->m_bk.m_currect.left) = 0;
  BYTE1(this->m_bk.m_childs.m_nSize) = 1;
  LOBYTE(this->m_bk.m_childs.m_nSize) = 1;
  return ((PalScript *)this)->ShowWindow(1);
}

// 0x00524960
int UIRoleSelect::SetFieldLeft(int nVal)
{
  *((_DWORD *)this + 1313) = nVal;
  return nVal;
}
