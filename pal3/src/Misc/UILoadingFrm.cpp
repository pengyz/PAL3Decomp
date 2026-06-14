#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UILoadingFrm.h"

// Forward declarations for unnamed functions
void sub_43FDB0(float *_this, int a2); // from annotations
void sub_4422E0(void *_this); // from annotations

// 0x00450710
int * UILoadingFrm::ctor()
{
  ((UIButton *)&this->m_LoadProgress)->ctor_17();
  this->m_MaxValue = 100.0;
  return (int *)this;
}

// 0x00450790
void UILoadingFrm::ctor_790()
{
  ((UIButton *)&this->m_LoadProgress)->_UIButton();
  ((UIListBox *)this)->_UIListBox();
}

// 0x004507F0
void UILoadingFrm::InitFullScreen()
{
  void *vftable; // eax
  _DWORD v3[4]; // [esp+0xC] [ebp-0x10] BYREF

  ((UIListBox *)this)->SetSelTexture(0, 0, 0, g_DrvInfo.width, g_DrvInfo.height, 0);
// [VFTABLE] vftable = this->m_LoadProgress.__vftable;
  v3[1] = 520;
  v3[0] = 206;
  v3[2] = 570;
  v3[3] = 548;
  ((void ( *)(UIProgressBar *, _DWORD, _DWORD *, UILoadingFrm *))vftable->Create)(
    &this->m_LoadProgress,
    0,
    v3,
    this);
  ((UIScene *)&this->m_LoadProgress)->GetChildCount();
  ((UIScene *)&this->m_LoadProgress)->GetChildAt();
  ((UIScene *)&this->m_LoadProgress)->SetTextParam();
  this->m_LoadProgress.m_color.Color = 88;
  this->m_LoadProgress.m_dstAlpha = 64;
  this->m_LoadProgress.m_alpha = 0;
  this->m_LoadProgress.m_minAlpha = -20;
  sub_43FDB0((float *)&this->m_LoadProgress, 4);
// [VFTABLE] ((UIWnd *)&this->m_LoadProgress.__vftable)->GetHeight(10);
// [VFTABLE] ((UIWnd *)&this->m_LoadProgress.__vftable)->GetPosition(6);
// [VFTABLE] ((UIWnd *)&this->m_LoadProgress.__vftable)->GetWidth(6);
  this->m_LoadProgress.m_radius = 1086324736;
  this->m_isOverProgress = 0;
  this->m_anitime = 0.0;
  this->m_aniFlag = 1;
}

// 0x00450900
BOOL UILoadingFrm::UpdateAnimation(int nVal, int nVal2)
{
  int m_aniFlag; // edx

  if ( this->m_anitime >= 0.30000001 )
  {
    m_aniFlag = this->m_aniFlag;
    this->m_anitime = 0.0;
    this->m_aniFlag = m_aniFlag == 0;
    ((UIScene *)&this->m_LoadProgress)->SetTextParam();
  }
  this->m_anitime = *(float *)&nVal + this->m_anitime;
  this->m_isOverProgress = this->m_LoadProgress.m_ppic;
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00450990
int UILoadingFrm::OnMessage(int nVal, int nVal2, int nVal3)
{
  UIProgressBar *p_m_LoadProgress; // esi

  if ( nVal != 1000 )
    return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
  if ( nVal2 )
  {
    p_m_LoadProgress = &this->m_LoadProgress;
    ((UIScrollBar *)&this->m_LoadProgress)->SetRange(100.0);
    ((UIProgressBar *)p_m_LoadProgress)->FindChildByName(100.0);
  }
  else
  {
    ((UIListBox *)&this->m_LoadProgress)->GetCurSel();
  }
  return 1;
}

// 0x00483280
void UILoadingFrm::DestroyStatics()
{
  sub_4422E0(this);
  sub_4422E0(&this->m_LoadProgress.m_decorateRc.right);
  sub_4422E0(&this->m_LoadProgress.m_warningval + 3);
}

// 0x00483300
void UILoadingFrm::DestroyFrames()
{
  ((UIFrameWnd *)(&this->m_LoadProgress.m_warningval + 3))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_LoadProgress.m_decorateRc.right)->UIFrameWnd::_UIFrameWnd();
// [VFTABLE] ((UIFrameWnd *)&this->__vftable)->_UIFrameWnd();
}

// 0x0052DD60
int UILoadingFrm::ResetState()
{
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 0;
  this->m_id = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = 0;
  this->m_childs.m_pData = 0;
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_needscriptdel = 0;
  this->m_LoadProgress.m_wndcolor.Color = 0;
  this->m_LoadProgress.m_id = 0;
  this->m_LoadProgress.m_rect.left = 0;
  this->m_LoadProgress.m_rect.top = 0;
  this->m_LoadProgress.m_rect.right = 0;
  this->m_LoadProgress.m_rect.bottom = 0;
  LOBYTE(this->m_LoadProgress.m_speed) = 0;
  this->m_LoadProgress.m_progress = 0;
  this->m_LoadProgress.m_decorateRc.bottom = 0;
  LOBYTE(this->m_LoadProgress.m_ppicInfo) = 0;
  this->m_LoadProgress.m_ppic = 0;
  this->m_LoadProgress.m_pbkInfo = 0;

  return (int)this;
}

// 0x0052DE00
int UILoadingFrm::ResetAllState()
{
  double v2; // st7
  LONG Color; // edx
  void *m_id; // esi

  this->m_id = (void *)1145569280;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 0;
  v2 = *(float *)&this->m_fontcolor.Color;
  Color = this->m_wndcolor.Color;
  this->m_rect.right = 0;
  *(float *)&this->m_rect.left = v2;
  this->m_rect.top = Color;
  this->m_rect.bottom = 0;
  this->m_pfather = (UIWnd *)1065353216;
  this->m_childs.m_pData = 0;
  this->m_benable = 0;
  this->m_bvisible = 0;
  this->m_bcreateok = 0;
  this->m_LoadProgress.m_fontcolor.Color = 0;
// [VFTABLE] this->m_LoadProgress.__vftable = 0;
  this->m_pbktex = 0;
  m_id = this->m_id;
  this->m_LoadProgress.m_childs.m_needscriptdel = 0;
  this->m_bfocus = (int)m_id;
  this->m_LoadProgress.m_bfocus = 1065353216;
  this->m_LoadProgress.m_mode = 1065353216;
  this->m_LoadProgress.m_decorateRc.left = 1065353216;
  this->m_LoadProgress.m_decorateRc.top = 1065353216;
  this->m_LoadProgress.m_benable = 0;
  this->m_LoadProgress.m_bvisible = 0;
  this->m_LoadProgress.m_bcreateok = 0;
  LOBYTE(this->m_LoadProgress.m_bkColor.Color) = 0;
  this->m_LoadProgress.m_tradius = 0.0;
  this->m_LoadProgress.m_rradius = 0;
  this->m_LoadProgress.m_lradius = 0;
  this->m_LoadProgress.m_radius = 0;
  *(_DWORD *)&this->m_LoadProgress.m_IsGetit = 1065353216;
  this->m_LoadProgress.m_Val = 1.0;
  this->m_LoadProgress.m_step = 1065353216;
  this->m_LoadProgress.m_bradius = 1.0;
  LOBYTE(this->m_LoadProgress.m_decorateRc.right) = 0;
  BYTE1(this->m_LoadProgress.m_decorateRc.right) = 0;
  LOBYTE(this->m_LoadProgress.m_pdecorate) = 0;
  this->m_LoadProgress.m_decorateOffsetX = 0;
  this->m_LoadProgress.m_decorateH = 0;
  this->m_LoadProgress.m_decorateW = 0;
  this->m_LoadProgress.m_pdecorateInfo = 0;
  this->m_LoadProgress.m_decorateOffsetY = 0;
  *(_DWORD *)&this->m_LoadProgress.m_pgrmode = 1065353216;
  this->m_LoadProgress.m_minAlpha = 0;
  this->m_LoadProgress.m_alpha = 0;
  this->m_LoadProgress.m_dstAlpha = 0;
  this->m_LoadProgress.m_color.Color = 0;
  LODWORD(this->m_LoadProgress.m_fadespeed) = 500;
  this->m_LoadProgress.m_isAdd = 0;
  *(&this->m_LoadProgress.m_warningval + 1) = 0;
  *(&this->m_LoadProgress.m_warningval + 3) = 1065353216;
  *((_BYTE *)&this->m_LoadProgress.m_warningval + 16) = 0;
  return 0;
}

// 0x0052E820
char UILoadingFrm::CheckProgress(int nVal)
{
  char result; // al
  double v3; // st7
  double v4; // st7
  int v5; // eax

  result = *((_BYTE *)&this->m_LoadProgress.m_warningval + 16);
  if ( result )
  {
    if ( *((float *)&this->m_LoadProgress.m_warningval + 1) >= (double)*((float *)&this->m_LoadProgress.m_warningval + 2) )
    {
      if ( *((float *)&this->m_LoadProgress.m_warningval + 1) <= (double)*((float *)&this->m_LoadProgress.m_warningval
                                                                         + 2) )
        goto LABEL_8;
      v4 = *((float *)&this->m_LoadProgress.m_warningval + 1) - *((float *)&this->m_LoadProgress.m_warningval + 3);
      *((float *)&this->m_LoadProgress.m_warningval + 1) = v4;
      if ( v4 > *((float *)&this->m_LoadProgress.m_warningval + 2) )
        goto LABEL_8;
    }
    else
    {
      v3 = *((float *)&this->m_LoadProgress.m_warningval + 3) + *((float *)&this->m_LoadProgress.m_warningval + 1);
      *((float *)&this->m_LoadProgress.m_warningval + 1) = v3;
      if ( v3 < *((float *)&this->m_LoadProgress.m_warningval + 2) )
      {
LABEL_8:
        *(float *)&this->m_bcreateok = *(float *)&this->m_bcreateok + *((float *)&this->m_LoadProgress.m_warningval + 1);
        return ((UIScene *)this)->CalcViewTransform(1);
      }
    }
    v5 = *(&this->m_LoadProgress.m_warningval + 2);
    *((_BYTE *)&this->m_LoadProgress.m_warningval + 16) = 0;
    *(&this->m_LoadProgress.m_warningval + 1) = v5;
    goto LABEL_8;
  }
  return result;
}
