#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UICaption.h"

// Forward declarations for unnamed functions
int sub_44BDA0(...);

// 0x0043B4B0
UICaption * UICaption::_sdtor_5(UICaption *Block, char a2)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x0043B4D0
void UICaption::Destroy2()
{
  if ( *((_DWORD *)this + 86) )
  {
    operator delete(*((void **)this + 86));
    *((_DWORD *)this + 86) = 0;
  }

}

// 0x004427C0
void UICaption::SetEnable(int szName, int bEnable)
{
  UICaption *v3; // ebp
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  unsigned int Color; // ecx
  char v7; // al
  unsigned int m_id; // eax
  unsigned int v9; // ecx

  if ( szName )
  {
    v3 = this + 1;
    v4 = strlen((const char *)szName) + 1;
    v5 = v4 - 1;
    if ( v4 - 1 > 0xFFFFFFFD )
// [IDA_MISID]       std::_Xlen();
    Color = v3->m_fontcolor.Color;
    if ( Color && (v7 = *(_BYTE *)(Color - 1)) != 0 && v7 != -1 )
    {
      if ( v4 == 1 )
      {
        *(_BYTE *)(Color - 1) = v7 - 1;
        v3->m_fontcolor.Color = 0;
        v3->m_wndcolor.Color = 0;
        v3->m_id = 0;
        goto LABEL_16;
      }
    }
    else
    {
      if ( v4 == 1 )
      {
        ((std *)1)->string::_Tidy();
        goto LABEL_16;
      }
      m_id = (unsigned int)v3->m_id;
      if ( m_id <= 0x1F && m_id >= v5 )
      {
LABEL_15:
        qmemcpy((void *)v3->m_fontcolor.Color, (const void *)szName, v5);
        v9 = v3->m_fontcolor.Color;
        v3->m_wndcolor.Color = v5;
        *(_BYTE *)(v9 + v5) = 0;
LABEL_16:
        if ( bEnable )
          this->m_needscriptdel = (gbImage2D *)1;
        else
          this->m_needscriptdel = 0;
        return;
      }
      ((std *)1)->string::_Tidy();
    }
    ((GRPinput *)v3)->PollInputState(v5);
    goto LABEL_15;
  }
}

// 0x004461F0
void UICaption::DestroyPanel()
{
  ((UICaption *)this + 1)->Destroy2();
}

// 0x0044BDA0
void UICaption::sub_44BDA0()
{

}

// 0x0044BE00
UICaption * UICaption::_sdtor_24(UICaption *Block, char a2)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00450320
void UICaption::LayoutDefault()
{
  this->m_tex = 0;
  this->m_curline = 0;
  this->m_lineheight = 0;
// [VFTABLE] this->__vftable = (void *)1;
  this->m_linetime = 0.0;
  this->m_numline = 0;
  memset(this + 1, 0, 0x100u);
}

// 0x00450670
void UICaption::Destroy()
{
  float m_linetime; // ecx

  m_linetime = this->m_linetime;
  if ( m_linetime != 0.0 )
  {
    ((gbRefObject *)LODWORD(m_linetime))->Release();
    this->m_linetime = 0.0;
  }
// [VFTABLE] ((UIWnd *)&this->__vftable)->HideAll();
}
