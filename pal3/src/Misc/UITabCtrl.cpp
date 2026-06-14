#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITabCtrl.h"

// 0x0046D0A0
int UITabCtrl::SetItemParam(int nIndex)
{
  int result; // eax
  int v3; // [esp+0x8] [ebp+0x8]

  if ( nIndex < 0 || nIndex >= *((_DWORD *)this + 126) )
  {
    MEMORY[0x44] = v3;
    return 0;
  }
  else
  {
    result = *(_DWORD *)(*((_DWORD *)this + 125) + 4 * nIndex);
    *(_DWORD *)(result + 68) = v3;
  }
  return result;
}

// 0x00532A80
int UITabCtrl::InitAnimParams()
{
  gbTexture *v2; // esi
  double v3; // st7

  BYTE1(this->m_texarray.m_ptex[15]) = 1;
// [VFTABLE] this->__vftable = 0;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 0;
  this->m_texarray.m_ptex[5] = (gbTexture *)1074832343;
  this->m_id = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 1074832343;
  v2 = this->m_texarray.m_ptex[5];
  this->m_texarray.m_ptex[7] = (gbTexture *)1016296636;
  this->m_texarray.m_ptex[6] = v2;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = (UIWnd *)1065353216;
  this->m_childs.m_pData = (char *)-1027567780;
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = -982398730;
  this->m_childs.m_pData = (char *)1125908480;
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = 1141112832;
  this->m_childs.m_needscriptdel = (int)this->m_childs.m_pData;
  this->m_bcreateok = this->m_childs.capacity;
  this->m_bvisible = this->m_childs.m_nSize;
  LOBYTE(this->m_benable) = 0;
  v3 = *(float *)&this->m_childs.capacity;
  HIBYTE(this->m_texarray.m_ptex[15]) = 0;
  this->m_texarray.m_ptex[2] = (gbTexture *)1030590824;
  *(float *)&this->m_texarray.m_ptex[1] = v3;
  *(float *)&this->m_texarray.m_ptex[9] = v3;
  this->m_texarray.m_ptex[0] = (gbTexture *)1114112000;
  this->m_bfocus = 1078774989;
  this->m_itemwidth = 1020591604;
  LOBYTE(this->m_texarray.m_ptex[8]) = 1;
  BYTE1(this->m_texarray.m_ptex[8]) = 1;
  this->m_texarray.m_ptex[14] = 0;
  this->m_texarray.m_num = 0;
  LOBYTE(this->m_texarray.m_ptex[10]) = 0;
  BYTE1(this->m_texarray.m_ptex[10]) = 0;
  BYTE2(this->m_texarray.m_ptex[15]) = 0;
  return 0;
}

// 0x00532B40
void UITabCtrl::Render()
{
  UIScene *vftable; // ecx
  unsigned int RolePtr; // edi
  double v4; // st7

  ((UICursor *)this)->IRender();
  if ( BYTE1(this->m_texarray.m_ptex[15]) )
  {
    BYTE1(this->m_texarray.m_ptex[15]) = 1;
    this->m_texarray.m_ptex[5] = (gbTexture *)1074832343;
    this->m_id = 0;
    this->m_rect.left = 0;
    this->m_rect.top = 1074832343;
    this->m_texarray.m_ptex[6] = this->m_texarray.m_ptex[5];
    this->m_texarray.m_ptex[7] = (gbTexture *)1016296636;
    this->m_rect.right = 0;
    this->m_rect.bottom = 0;
    this->m_pfather = (UIWnd *)1065353216;
    this->m_childs.m_pData = (char *)-1027567780;
    this->m_childs.capacity = 0;
    this->m_childs.m_nSize = -982398730;
    this->m_childs.m_pData = (char *)1117782016;
    this->m_childs.capacity = 0;
    this->m_childs.m_nSize = 1141112832;
    this->m_childs.m_needscriptdel = (int)this->m_childs.m_pData;
    this->m_bcreateok = this->m_childs.capacity;
    this->m_bvisible = this->m_childs.m_nSize;
// [VFTABLE] vftable = (UIScene *)this->__vftable;
    LOBYTE(this->m_benable) = 0;
    this->m_texarray.m_ptex[2] = (gbTexture *)1030590824;
    this->m_texarray.m_ptex[0] = (gbTexture *)1114112000;
    this->m_bfocus = 1078774989;
    this->m_itemwidth = 1020591604;
    LOBYTE(this->m_texarray.m_ptex[8]) = 1;
    BYTE1(this->m_texarray.m_ptex[8]) = 1;
    LOBYTE(this->m_texarray.m_ptex[10]) = 0;
    BYTE1(this->m_texarray.m_ptex[10]) = 0;
    this->m_texarray.m_ptex[14] = 0;
    this->m_texarray.m_num = 0;
    ((UIScene *)vftable)->ResetCameraOffset();
// [VFTABLE] ((UIScene *)this->__vftable)->ResetCameraOffset();
    RolePtr = ((RoleSystem *)*(RoleSystem **)this->m_fontcolor.Color)->GetRolePtr(0);
    this->m_wndcolor.Color = RolePtr;
    v4 = ((Scene *)*(_DWORD *)this->m_fontcolor.Color)->GetTileHeight(0, (__int64)((*(float *)&this->m_childs.m_pData - *(float *)(RolePtr + 128)) / g_fSceneScale), (__int64)((*(float *)&this->m_childs.m_nSize - *(float *)(RolePtr + 136)) / g_fSceneScale), 0)
       + *(float *)this->m_texarray.m_ptex;
    BYTE2(this->m_texarray.m_ptex[15]) = 0;
    HIBYTE(this->m_texarray.m_ptex[15]) = 0;
    this->m_numpage = 0;
    *(float *)&this->m_childs.capacity = v4;
    *(float *)&this->m_texarray.m_ptex[1] = v4;
    *(float *)&this->m_texarray.m_ptex[9] = v4;
  }
}
