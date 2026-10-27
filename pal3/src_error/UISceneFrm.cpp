#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UISceneFrm.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Misc/NameSys.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleTask.h"
#include "Misc/RoleTaskLine.h"
#include "Scene/SceneObj.h"
#include "Misc/UIButton.h"
#include "Misc/UIButton_UIBUTTON_STATE.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "UI/UIScene.h"
#include "Misc/UISceneFace.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/graph.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x004590D0
UISceneFrm::UISceneFrm()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->m_map.m_childs.m_needscriptdel = 800;
  this->m_map.m_bcreateok = 64;
  this->m_map.m_bfocus = 360;
  *(_DWORD *)((UIWnd *)&this->m_map.m_probe) = 136;
  LOBYTE(this->m_map.m_probe.m_id) = 0;
  (((UIFrameContainer *)&this->m_map.m_probe.m_rect.right))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_map.m_probe.m_disablepic))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  LOBYTE(this->m_face.m_state[2].m_childs.m_nSize) = 0;
  NameSys::GetSys();
  (((UIFrameContainer *)((char *)&this->m_face + 1868)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_face + 2020)))->UIFrameContainer::ResetContainerState();
  *((_DWORD *)&this->m_face + 543) = 0;
  *((_DWORD *)&this->m_face + 544) = 0;
  *((_DWORD *)&this->m_face + 545) = 0;
  *((_DWORD *)&this->m_face + 546) = 0;
  this->m_map.m_childs.capacity = 88;
  this->m_map.m_childs.m_nSize = 138;
  this->m_map.m_bvisible = 90;
  this->m_map.m_benable = 24;
  LOWORD(this->m_map.m_probe.m_rect.top) = 0;
  *((_DWORD *)&this->m_face + 547) = 0;
  *((_BYTE *)&this->m_face + 2200) = 1;
}

// 0x00459260
UISceneFrm::~UISceneFrm()
{
  this->UISceneFrm::Destroy();
  (((UIFrameContainer *)((char *)&this->m_face + 2020)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_face + 1868)))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->m_face.m_state[2].m_childs.m_needscriptdel))->UICaption::Destroy2();
  (((UICaption *)&this->m_face.m_state[0].m_fontcolor))->UICaption::Destroy2();
  (((UICaption *)&this->m_face.m_face[1].m_ppicInfo))->UICaption::Destroy2();
  (((UICaption *)&this->m_face.m_mp.m_decorateW))->UICaption::Destroy2();
  (((UICaption *)&this->m_face.m_hp.m_decorateRc.top))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_map.m_probe.m_disablepic))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_map.m_probe.m_rect.right))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x00459360
void UISceneFrm::Destroy()
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx

  v2 = *((_DWORD *)&this->m_face + 544);
  if ( v2 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v2 + 20))(v2, 1);
    *((_DWORD *)&this->m_face + 544) = 0;
  }
  v3 = *((_DWORD *)&this->m_face + 545);
  if ( v3 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *((_DWORD *)&this->m_face + 545) = 0;
  }
  v4 = *((_DWORD *)&this->m_face + 546);
  if ( v4 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *((_DWORD *)&this->m_face + 546) = 0;
  }
  Destroy__ovl_03((int)this);
}

// 0x0045A490
void UISceneFrm::Render()
{
  int v2; // [esp+0x0] [ebp-0x4]
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  UIScene_RenderUI(v2);
  switch ( *((_DWORD *)&this->m_face + 543) )
  {
    case 0:
      (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
      break;
    case 1:
      (*(void ( **)(_DWORD))(**((_DWORD **)&this->m_face + 544) + 4))(*((_DWORD *)&this->m_face + 544));
      break;
    case 2:
      (*(void ( **)(_DWORD))(**((_DWORD **)&this->m_face + 545) + 4))(*((_DWORD *)&this->m_face + 545));
      break;
    case 3:
      (*(void ( **)(_DWORD))(**((_DWORD **)&this->m_face + 546) + 4))(*((_DWORD *)&this->m_face + 546));
      break;
    default:
      return;
  }
}

// 0x0045A4F0
void UISceneFrm::fill(RoleTask *a1, RoleTask *a2, RoleTask *a3)
{
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax

  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
  }
  switch ( *((_DWORD *)&this->m_face + 543) )
  {
    case 0:
      StopSceneScripts((const char *)a1);
      (((SceneObj *)this))->SceneObj::Update((int)a1, (int)a2) /* [ROWTABLE] */;
      break;
    case 1:
      (*(void ( **)(_DWORD, RoleTask *, RoleTask *))(**((_DWORD **)&this->m_face + 544) + 8))(
        *((_DWORD *)&this->m_face + 544),
        a1,
        a2);
      break;
    case 2:
      (*(void ( **)(_DWORD, RoleTask *, RoleTask *))(**((_DWORD **)&this->m_face + 545) + 8))(
        *((_DWORD *)&this->m_face + 545),
        a1,
        a2);
      break;
    case 3:
      (*(void ( **)(_DWORD, RoleTask *, RoleTask *))(**((_DWORD **)&this->m_face + 546) + 8))(
        *((_DWORD *)&this->m_face + 546),
        a1,
        a2);
      break;
    case 4:
      (((CGameData *)&g_gamefrm))->CGameData::Load(0);
      break;
    case 5:
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)4);
      break;
    default:
      return;
  }
}

// 0x0045A600
void UISceneFrm::_Construct_2(RoleTaskLine *a1, RoleTaskLine *a2)
{
  CScreenMode *Instance; // eax
  CScreenMode *v4; // eax
  CScreenMode *v5; // eax
  PalScriptMgr *v6; // ecx
  CScreenMode *v7; // eax
  const void *v8; // [esp-0x8] [ebp-0xC]
  const void *v9; // [esp-0x8] [ebp-0xC]
  const void *v10; // [esp-0x8] [ebp-0xC]
  const void *v11; // [esp-0x8] [ebp-0xC]
  int wParam; // [esp+0x10] [ebp+0xC]

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
        UIFrameWnd_OnPaintUpdate(1);
        v8 = (const void *)off_5B203C;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v8, 1);
        break;
      case 5u:
        UIFrameWnd_OnPaintUpdate(2);
        v9 = (const void *)off_5B203C;
        v4 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v4))->CScreenMode::AudioSetPosition(v9, 1);
        break;
      case 6u:
        UIFrameWnd_OnPaintUpdate(3);
        goto LABEL_12;
      case 7u:
        if ( LOWORD(this->m_map.m_probe.m_rect.top) )
        {
          v10 = (const void *)off_5B203C;
          v5 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v5))->CScreenMode::AudioSetPosition(v10, 1);
          UIFrameWnd_OnPaintUpdate(4);
          (((PalScriptMgr *)v6))->PalScriptMgr::Destroy();
        }
        break;
      case 8u:
        UIFrameWnd_OnPaintUpdate(4);
LABEL_12:
        v11 = (const void *)off_5B203C;
        v7 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v7))->CScreenMode::AudioSetPosition(v11, 1);
        break;
      default:
        return;
    }
  }
  else if ( a1 != (RoleTaskLine *)1009 )
  {
    this->UIWnd::OnMessage((int)a1, (int)a2, wParam);
  }
}

// 0x004BB200
void UISceneFrm::ScreenToLocal(float *pOutX, float *pInX, float *pInY)
{
  float v4; // st7

  v4 = (g_fRenderHeight - pOutX[1])
     / g_fRenderWidth
     * (*(float *)&this->m_map.m_probe.m_state - *(float *)&this->m_map.m_probe.m_bfocus)
     + *(float *)&this->m_map.m_probe.m_bfocus;
  *pInX = (*pOutX - *(float *)&g_nTextureDefault)
        / g_fConst400
        * (this->m_map.m_probe.m_ratiow - *(float *)&this->m_map.m_probe.m_benable)
        + *(float *)&this->m_map.m_probe.m_benable;
  pInX[1] = v4;
}

// 0x004BB330
int UISceneFrm::InitGraph_Base()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  strcpy((char *)&this->m_wndcolor, "Size graph: m/t");
  strcpy((char *)&this->m_map, unk_C10D38);
  *(_DWORD *)((UIWnd *)this) = 1;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)0x40000000;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  v2 = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  do
  {
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BB4E0
int UISceneFrm::InitGraph_Rotation()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "Rotation graph: d/t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 1;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1011613696;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1135869952;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  v2 = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  p_m_offsetx = (float *)&this->m_map.m_probe.m_offsetx;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
  *(float *)this->m_map.m_probe.m_texarray.m_ptex = g_fConst400 + *(float *)&g_nTextureDefault;
  *(float *)&this->m_map.m_probe.m_texarray.m_ptex[1] = g_fRenderHeight - g_fRenderWidth * 0.5;
  do
  {
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BB690
int UISceneFrm::InitGraph_VertexAlpha()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "VertexAlpha graph: d/t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 1;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BB830
int UISceneFrm::InitGraph_RGBColor()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "RgbColor graph: d/t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 3;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1132396544;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth;
  this->m_map.m_compass.pDebugTex = ((gbTexture *)((gbTexture *)g_nTextureDefault));
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BBA50
int UISceneFrm::InitGraph_Direction()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "DirectionEmitter graph: x,y,z/t");
  strcpy((char *)&this->m_map, "Red:X,Green:y,Blue:z");
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 3;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1054867456;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1092616192;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
  *((_DWORD *)&this->m_map.m_probe.m_benable_snd + 1) = g_nTextureDefault;
  *((float *)&this->m_map.m_probe.m_benable_snd + 2) = g_fRenderHeight - g_fRenderWidth * 0.5;
  this->m_map.m_compass.pDebugTex = ((gbTexture *)((gbTexture *)g_nTextureDefault));
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BBCA0
int UISceneFrm::InitGraph_RandomVelocity()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "ElementRandomVelocity graph: m/s/t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1092616192;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BBEB0
int UISceneFrm::InitGraph_EmissionRate()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "EmissionRate Graph: rate/t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1120403456;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BC0C0
int UISceneFrm::InitGraph_Lifetime()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "ElementLifeTime Graph: t/t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = 0;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)1101004800;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BC2D0
int UISceneFrm::InitGraph_SizeMultiplier()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "SizeMultiplier Graph: */t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1073741824;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)0x40000000;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x004BC4E0
int UISceneFrm::InitGraph_RotationMultiplier()
{
  int v2; // edi
  float *p_m_offsetx; // esi
  int v4; // edi
  UISceneFace *v5; // esi
  float *v6; // eax
  int v7; // edx
  float *p_bottom; // ecx
  float v9; // st7
  float v10; // st7
  float *v12; // [esp+0x0] [ebp-0x14]
  float *v13; // [esp+0x0] [ebp-0x14]
  int v14; // [esp+0x10] [ebp-0x4]

  strcpy((char *)&this->m_wndcolor, "RotationMultiplier Graph: */t");
  strcpy((char *)&this->m_map, unk_C10D38);
  memset(&this->m_map.m_probe.m_offsetx, 0, 0x2D0u);
  memset(&this->m_map.m_mapbk.m_texs.m_ptex[10], 0, 0x2D0u);
  memset(&this->m_face.m_face[0].m_rect.right, 0, 0x2F4u);
  *(_DWORD *)((UIWnd *)this) = 2;
  this->m_fontcolor.Color = 2;
  this->m_map.m_probe.m_benable = 0;
  this->m_map.m_probe.m_bfocus = -1073741824;
  *(_DWORD *)&this->m_map.m_probe.m_hasDBclk = 0;
  this->m_map.m_probe.m_ratiow = 1.0f;
  this->m_map.m_probe.m_state = (UIButton_UIBUTTON_STATE)0x40000000;
  *(_DWORD *)&this->m_map.m_probe.m_canctrl = 0;
  this->m_map.m_probe.m_offsetx = g_nTextureDefault;
  this->m_map.m_probe.m_offsety = g_fRenderHeight - g_fRenderWidth * 0.5f;
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
    this->UISceneFrm::ScreenToLocal(p_m_offsetx, p_m_offsetx + 180, v12);
    this->UISceneFrm::ScreenToLocal(p_m_offsetx + 3, p_m_offsetx + 183, v13);
    ++v2;
    p_m_offsetx += 60;
  }
  while ( v2 < *(_DWORD *)((UIWnd *)this) );
  v4 = 0;
  if ( *(_DWORD *)((UIWnd *)this) > 0 )
  {
    v5 = (UISceneFace *)(&this->m_face + 1);
    v6 = (float *)&this->m_map.m_mapbk.m_texs.m_ptex[13];
    do
    {
      v7 = 0;
      p_bottom = (float *)&v5[-1].m_face[0].m_rect.bottom;
      v14 = 0;
      do
      {
        v9 = (float)v14;
        ++v7;
        p_bottom += 3;
        v14 = v7;
        v10 = v9 * 0.009999999776482582f;
        *(p_bottom - 4) = (*v6 - *(v6 - 3)) * v10 + *(v6 - 3);
        *(p_bottom - 3) = (v6[1] - *(v6 - 2)) * v10 + *(v6 - 2);
      }
      while ( v7 < 100 );
      ++v4;
      *(float *)((UIWnd *)v5) = *v6;
      v5->m_fontcolor.Color = (unsigned int)v6[1];
      v6 += 60;
      v5 = (UISceneFace *)((char *)v5 + 1212);
    }
    while ( v4 < *(_DWORD *)((UIWnd *)this) );
  }
  return (int)this;
}

// 0x00528CD0
int UISceneFrm::CallFaceMethod(int nVal, unsigned __int8 pData)
{
  int result; // eax

  *(_DWORD *)&this->m_face.m_state[0].m_text[32 * nVal + 4] = (_DWORD)pData;
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_face.m_mp.m_fadespeed))(
    &this->m_face.m_mp.m_fadespeed,
    pData);
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_face.m_face[0].m_ppic))(
    &this->m_face.m_face[0].m_ppic,
    pData);
  result = (**(int ( ***)(char *, _DWORD))&this->m_map.m_probe.m_caption[20])((char *)(&this->m_map.m_probe.m_caption[20]), (_DWORD)(pData));
  *((_BYTE *)&this->m_face + 1808) = pData;
  return result;
}

// 0x00535650
LPSTR UISceneFrm::InitTemplateStrings()
{
  LPSTR result; // eax

  *(_DWORD *)((UIWnd *)this) = 0;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 1;
  lstrcpyA((LPSTR)&this->m_map.m_base.m_childs.capacity, "m04");
  lstrcpyA((LPSTR)&this->m_map.m_compass.m_FVF, a1);
  lstrcpyA((LPSTR)&this->m_map.m_icons.m_ptex[6], "m04");
  lstrcpyA((char *)&this->m_face.m_hp.m_IsGetit, a2);
  lstrcpyA((char *)(LPSTR)&this->m_face.m_mp.m_pbk, "m05");
  lstrcpyA((LPSTR)&this->m_face.m_face[1].m_id, a1);
  lstrcpyA((LPSTR)&this->m_face.m_face[2].m_pbkInfo, "m05");
  lstrcpyA((LPSTR)&this->m_face.m_state[0].m_benable, a2);
  lstrcpyA((LPSTR)&this->m_face.m_state[2].m_id, "m05");
  result = lstrcpyA((LPSTR)&this->m_face.m_state[3].m_pbkInfo, a3);
  *((_DWORD *)&this->m_face + 533) = 0;
  return result;
}
