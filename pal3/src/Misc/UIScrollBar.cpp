#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIScrollBar.h"

// 0x0043FCA0
void UIScrollBar::SetRange(float fValue)
{
  int v2; // eax
  double v3; // st7
  double v4; // st6

  *(float *)&this->m_bk.m_bcreateok = fValue;
  if ( fValue >= 0.0 )
  {
    v2 = *(_DWORD *)&this->m_bPress;
    if ( v2 )
    {
      if ( v2 != 1 )
      {
LABEL_7:
        *(float *)&this->m_bk.m_bvisible = *(float *)&this->m_bk.m_childs.m_needscriptdel / fValue;
        *(float *)&this->m_bk.m_style = fValue / *(float *)&this->m_bk.m_childs.m_needscriptdel;
        return;
      }
      v3 = (double)this->m_rect.bottom - *(float *)&this->m_bk.m_tex - *(float *)&this->m_bk.m_benable;
      v4 = (double)this->m_rect.top + *(float *)&this->m_bk.m_tileheight;
    }
    else
    {
      v3 = (double)this->m_rect.right - *(float *)&this->m_bk.m_tilewidth - *(float *)&this->m_bk.m_benable;
      v4 = (double)this->m_rect.left + *(float *)&this->m_bk.m_bfocus;
    }
    *(float *)&this->m_bk.m_childs.m_needscriptdel = v3 - (v4 + *(float *)&this->m_bk.m_benable);
    goto LABEL_7;
  }
}
