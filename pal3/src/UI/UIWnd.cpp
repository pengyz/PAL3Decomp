#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIWnd.h"

// Forward declarations for unnamed functions
int sub_525080(...);
int todo_408BD0(...);

int crt_sub_00541210(void); // from annotations

// 0x0043BBB0
void UIWnd::Destroy()
{
}

// 0x0043FDC0
void UIWnd::GetWidth(int nWidth)
{
  *((float *)this + 35) = (float)nWidth;
}

// 0x0043FDD0
void UIWnd::GetHeight(int nHeight)
{
  *((float *)this + 36) = (float)nHeight;
}

// 0x0043FDE0
void UIWnd::GetPosition(int pPos)
{
  *((float *)this + 37) = (float)pPos;
}

// 0x004433D0
int UIWnd::LayoutAndRender()
{
  int result; // eax

  result = this->m_bvisible;
  if ( result )
  {
    if ( *((_DWORD *)this + 28) && *((_DWORD *)this + 38) <= 1u )
      UIInitSystem();
    if ( !this->m_benable && *((_DWORD *)this + 32) && *((_DWORD *)this + 38) <= 1u )
      UIInitSystem();

  }
  return result;
}

// 0x00445B40
void UIWnd::_UIWnd()
{

  ((UIListBox *)&this->m_childs)->ReleaseVtable();
}

// 0x00445C10
void UIWnd::HideAll()
{
  int v2; // edi
  int v3; // ecx

  v2 = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  for ( this->m_benable = 0; v2 < this->m_childs.capacity; ++v2 )
  {
    v3 = *(_DWORD *)&this->m_childs.m_pData[4 * v2];
    (*(void ( **)(int))(*(_DWORD *)v3 + 12))(v3);
  }
  ((String *)&this->m_childs)->Assign(0, -1);
}

// 0x00445CD0
void UIWnd::Render()
{
  int i; // esi
  _DWORD *v3; // ecx

  if ( this->m_bvisible )
  {
    for ( i = 0; i < this->m_childs.capacity; ++i )
    {
      v3 = *(_DWORD **)&this->m_childs.m_pData[4 * i];
      if ( v3[14] )
        (*(void ( **)(_DWORD *))(*v3 + 4))(v3);
    }
  }
}

// 0x0044A7F0
void UIWnd::RenderText()
{
}

// 0x00450390
void UIWnd::DelegateRender()
{

}

// 0x00450440
void UIWnd::RenderContent()
{
  unsigned int v2; // [esp+0x4] [ebp-0x5C]

  if ( this->m_bvisible )
  {
    if ( *((_DWORD *)this + 23) )
      ((TextureLibDataBase *)&this->m_wndcolor)->SetLibFolder((char *)&this->m_rect);
    strlen((const char *)this + 96);
    if ( gbColorQuad::ColorQuadFmt )
    {
      BYTE2(v2) = this->m_fontcolor.Color;
      BYTE1(v2) = BYTE1(this->m_fontcolor.Color);
      LOBYTE(v2) = BYTE2(this->m_fontcolor.Color);
    }
    else
    {
      BYTE2(v2) = BYTE2(this->m_fontcolor.Color);
      LOWORD(v2) = this->m_fontcolor.Color;
    }
    HIBYTE(v2) = -1;
    gfxMgr->pFontMgr->pAllFont[1]->curColor.Color = v2;
    crt_sub_00541210();

  }
}

// 0x00450E90
UIWnd * UIWnd::_sdtor_27(UIWnd *Block, char a2)
{
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004518E0
UIWnd * UIWnd::_sdtor_28(UIWnd *Block, char a2)
{
  ((UIListBox *)this)->DestroyContent();
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00457340
void UIWnd::CleanupScript()
{
  void *v2; // [esp+0x0] [ebp-0x14]

  ((PalScript *)((char *)this + 805416))->Cleanup();
  todo_408BD0(v2);
  ((PalScript *)&this->m_fontcolor)->Cleanup();
}

// 0x00525080
int UIWnd::sub_525080()
{
  return *((_DWORD *)this + 1316);
}
