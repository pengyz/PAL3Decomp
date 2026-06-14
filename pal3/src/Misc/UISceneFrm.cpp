#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UISceneFrm.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations

// Unnamed globals (extern)
extern void * off_5B203C;

// 0x004590D0
int UISceneFrm::ctor()
{
  this->m_map.m_childs.m_needscriptdel = 800;
  this->m_map.m_bcreateok = 64;
  this->m_map.m_bfocus = 360;
// [VFTABLE] this->m_map.m_probe.__vftable = (vtbl_0056AE2C *)136;
  LOBYTE(this->m_map.m_probe.m_id) = 0;
  sub_4422E0(&this->m_map.m_probe.m_rect.right);
  sub_4422E0(&this->m_map.m_probe.m_disablepic);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  LOBYTE(this->m_face.m_state[2].m_childs.m_nSize) = 0;
  UIScene::GetSys();
  sub_4422E0((char *)this + 2952);
  sub_4422E0((char *)this + 3104);
  *((_DWORD *)this + 814) = 0;
  *((_DWORD *)this + 815) = 0;
  *((_DWORD *)this + 816) = 0;
  *((_DWORD *)this + 817) = 0;
  this->m_map.m_childs.capacity = 88;
  this->m_map.m_childs.m_nSize = 138;
  this->m_map.m_bvisible = 90;
  this->m_map.m_benable = 24;
  LOWORD(this->m_map.m_probe.m_rect.top) = 0;
  *((_DWORD *)this + 818) = 0;
  *((_BYTE *)this + 3284) = 1;
  return (int)this;
}

// 0x00459260
void UISceneFrm::ctor_9260()
{

  ((UIFrameWnd *)((char *)this + 3104))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 41)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_face.m_state[2].m_childs.m_needscriptdel)->Destroy2();
  ((UICaption *)&this->m_face.m_state[0].m_fontcolor)->Destroy2();
  ((UICaption *)&this->m_face.m_face[1].m_ppicInfo)->Destroy2();
  ((UICaption *)&this->m_face.m_mp.m_decorateW)->Destroy2();
  ((UICaption *)&this->m_face.m_hp.m_decorateRc.top)->Destroy2();
  ((UIFrameWnd *)&this->m_map.m_probe.m_disablepic)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_map.m_probe.m_rect.right)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0045A490
void UISceneFrm::Render()
{
  CCBMagicWindow *v2; // [esp+0x0] [ebp-0x4]

  ((UIScene *)this)->RenderUI();
  switch ( *((_DWORD *)this + 814) )
  {
    case 0:
      ((CCBControlWindow *)this)->Render(v2);
      break;
    case 1:
      (*(void ( **)(_DWORD))(**((_DWORD **)this + 815) + 4))(*((_DWORD *)this + 815));
      break;
    case 2:
      (*(void ( **)(_DWORD))(**((_DWORD **)this + 816) + 4))(*((_DWORD *)this + 816));
      break;
    case 3:
      (*(void ( **)(_DWORD))(**((_DWORD **)this + 817) + 4))(*((_DWORD *)this + 817));
      break;
    default:
      return;
  }
}

// 0x0045A4F0
void UISceneFrm::fill(RoleTask *a2, RoleTask *a3)
{
  PalScriptMgr *v3; // ecx
  PalScriptMgr *v4; // esi
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax

  v4 = v3;
  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    ((gbAudioManager *)AudioManager)->DetachAll3D();
  }
  switch ( *(&v4->m_nField_0C70 + 18) )
  {
    case 0:
      ((PalScriptMgr *)v3)->RunSceneScript((const char *)a1);
      ((UIListBox *)v4)->Update((int)a1, (int)a2);
      break;
    case 1:
      (*(void ( **)(_DWORD, RoleTask *, RoleTask *))(**((_DWORD **)&v4->m_nField_0C70 + 19) + 8))(
        *(&v4->m_nField_0C70 + 19),
        a1,
        a2);
      break;
    case 2:
      (*(void ( **)(_DWORD, RoleTask *, RoleTask *))(**((_DWORD **)&v4->m_nField_0C70 + 20) + 8))(
        *(&v4->m_nField_0C70 + 20),
        a1,
        a2);
      break;
    case 3:
      (*(void ( **)(_DWORD, RoleTask *, RoleTask *))(**((_DWORD **)&v4->m_nField_0C70 + 21) + 8))(
        *(&v4->m_nField_0C70 + 21),
        a1,
        a2);
      break;
    case 4:
      ((CGameData *)&g_gamefrm)->Load(0);
      break;
    case 5:
      ((CGameData *)&g_gamefrm)->Load((CUtil *)4);
      break;
    default:
      return;
  }
}

// 0x0045A600
void UISceneFrm::_Construct_2(RoleTaskLine *a2)
{
  int v2; // ecx
  UIFrameWnd *v3; // esi
  CScreenMode *Instance; // eax
  CScreenMode *v5; // eax
  PalScriptMgr *v6; // ecx
  const void *v7; // [esp-0x8] [ebp-0xC]
  const void *v8; // [esp-0x8] [ebp-0xC]
  int wParam; // [esp+0x10] [ebp+0xC]

  v3 = (UIFrameWnd *)v2;
  if ( a1 == (RoleTaskLine *)1000 )
  {
    if ( a2 )
      g_nSceneState = 1;
  }
  else if ( a1 == (RoleTaskLine *)1001 )
  {
    switch ( (unsigned int)a2 )
    {
      case 4u:
      case 5u:
      case 6u:
      case 8u:
        ((UIFrameWnd *)v2)->OnPaintUpdate();
        v7 = off_5B203C;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v7, 1);
        break;
      case 7u:
        if ( *(_WORD *)(v2 + 160) )
        {
          v8 = off_5B203C;
          v5 = CScreenMode::GetInstance();
          ((CScreenMode *)v5)->AudioSetPosition(v8, 1);
          ((UIFrameWnd *)v3)->OnPaintUpdate();
          ((PalScriptMgr *)v6)->Destroy();
        }
        break;
      default:
        return;
    }
  }
  else if ( a1 != (RoleTaskLine *)1009 )
  {
    ((PalScript *)v2)->OnMessage((int)a1, (int)a2, wParam);
  }
}

// 0x004BB330
int UISceneFrm::InitGraph_Base()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  strcpy((char *)&this->m_wndcolor, "Size graph: m/t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)1;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)0x40000000;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  v2 = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BB4E0
int UISceneFrm::InitGraph_Rotation()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "Rotation graph: d/t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)1;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1011613696;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1135869952;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  v2 = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BB690
int UISceneFrm::InitGraph_VertexAlpha()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "VertexAlpha graph: d/t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)1;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1065353216;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BB830
int UISceneFrm::InitGraph_RGBColor()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "RgbColor graph: d/t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)3;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1132396544;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth;
  this->m_map.m_compass.pDebugTex = (gbTexture *)g_nTextureDefault;
  *(float *)&this->m_map.m_compass.m_align = g_fRenderHeight - g_fRenderWidth;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth;
  *((float *)&this->m_map.m_probe.m_benable_snd + 4) = g_fConst400 + *(float *)&g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 5) = g_fRenderHeight - g_fRenderWidth;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  this->m_map.m_compass.m_ratioh = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_compass.m_textx = g_fRenderHeight - g_fRenderWidth;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BBA50
int UISceneFrm::InitGraph_Direction()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "DirectionEmitter graph: x,y,z/t");
  strcpy((char *)&this->m_map, "Red:X,Green:y,Blue:z");
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)3;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1054867456;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1092616192;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth * 0.5;
  this->m_map.m_compass.pDebugTex = (gbTexture *)g_nTextureDefault;
  *(float *)&this->m_map.m_compass.m_align = g_fRenderHeight - g_fRenderWidth * 0.5;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  *((float *)&this->m_map.m_probe.m_benable_snd + 4) = g_fConst400 + *(float *)&g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 5) = g_fRenderHeight - g_fRenderWidth * 0.5;
  this->m_map.m_compass.m_ratioh = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_compass.m_textx = g_fRenderHeight - g_fRenderWidth * 0.5;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BBCA0
int UISceneFrm::InitGraph_RandomVelocity()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "ElementRandomVelocity graph: m/s/t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1092616192;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((float *)&this->m_map.m_probe.m_benable_snd + 4) = g_fConst400 + *(float *)&g_nTextureDefault;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  *((float *)&this->m_map.m_probe.m_benable_snd + 5) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BBEB0
int UISceneFrm::InitGraph_EmissionRate()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "EmissionRate Graph: rate/t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1120403456;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((float *)&this->m_map.m_probe.m_benable_snd + 4) = g_fConst400 + *(float *)&g_nTextureDefault;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  *((float *)&this->m_map.m_probe.m_benable_snd + 5) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BC0C0
int UISceneFrm::InitGraph_Lifetime()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "ElementLifeTime Graph: t/t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1101004800;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((float *)&this->m_map.m_probe.m_benable_snd + 4) = g_fConst400 + *(float *)&g_nTextureDefault;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  *((float *)&this->m_map.m_probe.m_benable_snd + 5) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BC2D0
int UISceneFrm::InitGraph_SizeMultiplier()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "SizeMultiplier Graph: */t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1073741824;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)0x40000000;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((float *)&this->m_map.m_probe.m_benable_snd + 4) = g_fConst400 + *(float *)&g_nTextureDefault;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  *((float *)&this->m_map.m_probe.m_benable_snd + 5) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x004BC4E0
int UISceneFrm::InitGraph_RotationMultiplier()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFrm *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  double v9; // st7
  double v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "RotationMultiplier Graph: */t");
  strcpy((char *)&this->m_map, g_szSceneUIText);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1073741824;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)0x40000000;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  *((float *)&this->m_map.m_probe.m_benable_snd + 4) = g_fConst400 + *(float *)&g_nTextureDefault;
  v2 = 0;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  *((float *)&this->m_map.m_probe.m_benable_snd + 5) = g_fRenderHeight - g_fRenderWidth * 0.5 + 30.0;
  do
  {
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    ((RenderTarget *)this)->ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
// [VFTABLE] while ( v2 < (int)this->__vftable );
  v4 = 0;
// [VFTABLE] if ( (int)this->__vftable > 0 )
  {
    v5 = this + 1;
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face.m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (double)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.0099999998;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
// [VFTABLE] v5->__vftable = *(vtbl_0056AE2C **)v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFrm *)((char *)v5 + 1212);
    }
// [VFTABLE] while ( v4 < (int)this->__vftable );
  }
  return (int)this;
}

// 0x00528CD0
int UISceneFrm::CallFaceMethod(int nVal, unsigned __int8 pData)
{
  int result; // eax

  *(_DWORD *)&this->m_face.m_state[0].m_text[32 * nVal + 4] = pData;
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_face.m_mp.m_fadespeed))(
    &this->m_face.m_mp.m_fadespeed,
    pData);
  ((void ( *)(gbTexture **, _DWORD))this->m_face.m_face[0].*((_DWORD *)m_ppic))(&this->m_face.m_face[0].m_ppic, pData);
  result = (**(int ( ***)(char *, _DWORD))&this->m_map.m_probe.m_caption[20])(
             &this->m_map.m_probe.m_caption[20],
             pData);
  *((_BYTE *)this + 2892) = pData;
  return result;
}

// 0x00535630
int UISceneFrm::ShowAndRelease()
{
  int ( ***v2)(_DWORD, int); // ecx
  int result; // eax

  v2 = (int ( ***)(_DWORD, int))*((_DWORD *)this + 804);
  if ( v2 )
  {
    result = (**v2)(v2, 1);
    *((_DWORD *)this + 804) = 0;
  }
  return result;
}

// 0x00535650
LPSTR UISceneFrm::InitTemplateStrings()
{
  LPSTR result; // eax

// [VFTABLE] this->__vftable = 0;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 1;
  lstrcpyA((LPSTR)&this->m_map.m_base.m_childs.capacity, "m04");
  lstrcpyA((LPSTR)&this->m_map.m_compass.m_FVF, a1);
  lstrcpyA((LPSTR)&this->m_map.m_icons.m_ptex[6], "m04");
  lstrcpyA(&this->m_face.m_hp.m_IsGetit, a2);
  lstrcpyA((LPSTR)&this->m_face.m_mp.m_pbk, "m05");
  lstrcpyA((LPSTR)&this->m_face.m_face[1].m_id, a1);
  lstrcpyA((LPSTR)&this->m_face.m_face[2].m_pbkInfo, "m05");
  lstrcpyA((LPSTR)&this->m_face.m_state[0].m_benable, a2);
  lstrcpyA((LPSTR)&this->m_face.m_state[2].m_id, "m05");
  result = lstrcpyA((LPSTR)&this->m_face.m_state[3].m_pbkInfo, a3);
  *((_DWORD *)this + 804) = 0;
  return result;
}
