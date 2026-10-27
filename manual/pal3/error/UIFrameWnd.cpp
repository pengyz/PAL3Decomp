// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIFrameWnd.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/Parent_Data.h"
#include "Scene/SceneObj.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/_Texture_Info.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

class TextureLibDataBase;

// Unnamed globals (extern)
extern TextureLibDataBase stru_1894B78;

// 0x0043BB70
UIFrameWnd::UIFrameWnd()
{
  ClearSubArraySlot();
  this->m_pbktex = ((gbTexture *)0);
  (int *)this;
}

// 0x0043BBC0
BOOL UIFrameWnd::Update_bbc0(int nVal, int nVal2)
{
  BOOL result; // eax
  BOOL v5; // ebx
  POINT pt; // [esp+0x8] [ebp-0x8] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( this->m_pbktex )
  {
    (((SceneObj *)this))->SceneObj::Update(nVal, 1) /* [ROWTABLE] */;
    return 1;
  }
  result = (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  v5 = result;
  if ( nVal2 )
  {
    (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
    result = PtInRect(&this->m_rect, pt);
    if ( result || v5 )
      return 1;
  }
  return result;
}

// 0x00442420
void UIFrameWnd::Destroy()
{
  gbRefObject *capacity; // ecx
  gbRefObject *m_bvisible; // ecx
  gbRefObject *m_bfocus; // ecx
  gbRefObject *m_needscriptdel; // ecx

  capacity = (gbRefObject *)this[1].m_childs.capacity;
  if ( capacity )
  {
    (((gbRefObject *)capacity))->gbRefObject::Release();
    this[1].m_childs.capacity = 0;
  }
  m_bvisible = (gbRefObject *)this[1].m_bvisible;
  if ( m_bvisible )
  {
    (((gbRefObject *)m_bvisible))->gbRefObject::Release();
    this[1].m_bvisible = 0;
  }
  m_bfocus = (gbRefObject *)this[1].m_bfocus;
  if ( m_bfocus )
  {
    (((gbRefObject *)m_bfocus))->gbRefObject::Release();
    this[1].m_bfocus = 0;
  }
  m_needscriptdel = (gbRefObject *)this[1].m_childs.m_needscriptdel;
  if ( m_needscriptdel )
  {
    (((gbRefObject *)m_needscriptdel))->gbRefObject::Release();
    this[1].m_childs.m_needscriptdel = 0;
  }
  this[2].m_fontcolor.Color = -1;
}

// 0x00442540
gbVFileSystem * UIFrameWnd::SetTextureByID(int nTexID)
{
  gbRefObject *m_bfocus; // ecx
  gbTexture *v4; // eax
  gbVFileSystem *result; // eax
  OpenBaseFile v6; // [esp+0x8] [ebp-0x10] BYREF
  int v7; // [esp+0x14] [ebp-0x4]

  m_bfocus = (gbRefObject *)this[1].m_bfocus;
  if ( m_bfocus )
    (((gbRefObject *)m_bfocus))->gbRefObject::Release();
  (((OpenBaseFile *)&v6))->OpenBaseFile::~OpenBaseFile();
  v7 = 0;
  v4 = (gbTexture *)gfxMgr->NewTexture((const char *)nTexID);
  this[1].m_bfocus = (int)v4;
  if ( v4 )
    (((gbTexture *)v4))->gbTexture::LoadTexture(1);
  v7 = -1;
  ((OpenNULLFile *)&v6)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x004425D0
void UIFrameWnd::SetTextureByName(LPCSTR lpTexName, char bCalcUV)
{
  const CHAR *v3; // edi
  gbRefObject *m_bvisible; // ecx
  bool v6; // zf
  int v7; // ebp
  CHAR *v8; // eax
  gbTexture *v9; // ecx

  v3 = lpTexName;
  if ( lpTexName )
  {
    m_bvisible = (gbRefObject *)this[1].m_bvisible;
    if ( m_bvisible )
      (((gbRefObject *)m_bvisible))->gbRefObject::Release();
    ((OpenBaseFile *)&lpTexName)->OpenBaseFile::OpenBaseFile();
    v6 = bCalcUV == 0;
    this[1].m_benable = 0;
    if ( v6 )
    {
      this[1].m_bvisible = gfxMgr->NewTexture((const char *)v3);
    }
    else
    {
      v7 = *(_DWORD *)*(void**)(gfxMgr);
      v8 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(v3);
      this[1].m_bvisible = gfxMgr->NewTexture((const char *)v8);
      this[1].m_benable = (int)(((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(v3);
    }
    v9 = (gbTexture *)this[1].m_bvisible;
    if ( v9 )
      (((gbTexture *)v9))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&lpTexName)->OpenNULLFile::OpenNULLFile();
  }
}

// 0x00442890
int UIFrameWnd::CalculateLayout()
{
  int result; // eax
  LONG left; // ecx
  int v4; // eax
  float v5; // st7
  LONG top; // ecx
  float v7; // st7
  float v8; // st6
  __int64 v9; // rax
  float v10; // st7
  unsigned int v11; // ecx
  int *v12; // eax
  int *v13; // edx
  TextureLibDataBase *v14; // ecx
  LONG v15; // edx
  int v16; // ecx
  gbTexture *m_pbktex; // edx
  unsigned int Color; // edi
  int v19; // eax
  unsigned __int8 *v20; // eax
  TextureLibDataBase *v21; // [esp-0x1C] [ebp-A0h]
  gbColorQuad v22; // [esp-0xC] [ebp-0x90] BYREF
  int *p_m_bfocus; // [esp-0x8] [ebp-0x8C]
  int m_nSize; // [esp-0x4] [ebp-0x88]
  gbTextureArray *v25; // [esp+0x0] [ebp-0x84]
  _PlugInfo *v26; // [esp+0x4] [ebp-0x80]
  int v27; // [esp+0x10] [ebp-0x74]
  LONG right; // [esp+0x14] [ebp-0x70]
  LONG v29; // [esp+0x18] [ebp-0x6C]
  LONG bottom; // [esp+0x1C] [ebp-0x68]
  int nY; // [esp+0x20] [ebp-0x64] BYREF
  int v32; // [esp+0x24] [ebp-0x60]
  unsigned int v33; // [esp+0x28] [ebp-0x5C]
  int v34; // [esp+0x2C] [ebp-0x58]
  char pszBuf[4]; // [esp+0x30] [ebp-0x54] BYREF
  int v36; // [esp+0x34] [ebp-0x50]
  int v37; // [esp+0x38] [ebp-0x4C]
  int v38; // [esp+0x3C] [ebp-0x48]
  int m_bfocus; // [esp+0x40] [ebp-0x44] BYREF
  _BYTE v40[64]; // [esp+0x44] [ebp-0x40] BYREF

  result = this->m_bvisible;
  if ( result )
  {
    left = this->m_rect.left;
    right = this->m_rect.right;
    v4 = left + right;
    v27 = left;
    v5 = 1.0f - *(float *)&this[1].m_fontcolor.Color;
    top = this->m_rect.top;
    nY = v4 / 2;
    v7 = v5 * (float)(v4 / 2);
    bottom = this->m_rect.bottom;
    v29 = top;
    v8 = (float)v27 * *(float *)&this[1].m_fontcolor.Color;
    v32 = (top + bottom) / 2;
    *(_DWORD *)pszBuf = (__int64)(v8 + v7);
    v9 = (__int64)((double)right * *(float *)&this[1].m_fontcolor.Color + v7);
    v10 = (1.0f - *(float *)&this[1].m_wndcolor.Color) * (float)v32;
    v37 = v9;
    v36 = (__int64)((double)top * *(float *)&this[1].m_wndcolor.Color + v10);
    v38 = (__int64)((double)bottom * *(float *)&this[1].m_wndcolor.Color + v10);
    if ( this[1].m_childs.capacity )
    {
      v11 = (unsigned int)((UIWnd *)&this[2]);
      m_nSize = this[1].m_childs.m_nSize;
      p_m_bfocus = (int *)v11;
      v22.Color = v11;
      ((gbTextureArray *)v40)->gbTextureArray::gbTextureArray((gbTexture *)this[1].m_childs.capacity);
      (((TextureLibDataBase *)pszBuf))->TextureLibDataBase::_CheckItem((char *)&this->m_rect, pszBuf);
    }
    if ( !this->m_benable && this[1].m_bvisible )
    {
      v12 = (int *)((UIWnd *)&this[2]);
      m_nSize = this[1].m_benable;
      p_m_bfocus = (int *)v12;
      v22.Color = top;
      ((gbTextureArray *)v40)->gbTextureArray::gbTextureArray((gbTexture *)this[1].m_bvisible);
      (((TextureLibDataBase *)pszBuf))->TextureLibDataBase::_CheckItem((char *)&this->m_rect, pszBuf);
    }
    if ( this[1].m_bfocus )
    {
      m_bfocus = this[1].m_bfocus;
      m_nSize = 0;
      p_m_bfocus = (int *)&m_bfocus;
      v22.Color = (unsigned int)&this->m_wndcolor;
      v21 = *((TextureLibDataBase **)this + 4);
      *(_DWORD *)&v40[60] = 1;
      (((TextureLibDataBase *)v21))->TextureLibDataBase::GetTextureInfoByIndex((int)v21);
    }
    if ( this[1].m_childs.m_needscriptdel )
    {
      v13 = (int *)((UIWnd *)&this[2]);
      m_nSize = 0;
      p_m_bfocus = (int *)v13;
      v22.Color = top;
      ((gbTextureArray *)v40)->gbTextureArray::gbTextureArray((gbTexture *)this[1].m_childs.m_needscriptdel);
      (((TextureLibDataBase *)v14))->TextureLibDataBase::_CheckItem((char *)&this->m_rect, pszBuf);
    }
    if ( this[1].m_pfather )
    {
      v15 = this[1].m_rect.left;
      nY = *(_DWORD *)pszBuf;
      v16 = v15 + v36;
      m_pbktex = (gbTexture *)this->m_pbktex;
      Color = this[2].m_fontcolor.Color;
      v19 = (int)m_pbktex + *(_DWORD *)pszBuf + this[1].m_id;
      nY = v19;
      if ( Color == -1 )
        v33 = v37 - (_DWORD)m_pbktex;
      else
        v33 = v19 + Color;
      v20 = (unsigned __int8 *)this[1].m_rect.bottom;
      v32 = (int)m_pbktex + v16;
      v34 = v38 - (_DWORD)m_pbktex;
      if ( !v20 )
        v20 = (unsigned __int8 *)&g_bActorFlag;
      UIRenderPar(
        (int)v20,
        (int)&nY,
        (int)&this->m_fontcolor,
        this[1].m_rect.top,
        *(gbColorQuad **)((UIWnd *)&this[1]),
        v25,
        v26);
    }
    (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  }
  return result;
}

// 0x00442AD0
BOOL UIFrameWnd::Update(int nVal, int nVal2)
{
  UIWnd *v5; // ecx
  UIWnd *v6; // ecx
  UIWnd *v7; // ecx
  UIWnd *v8; // ecx
  UIWnd *m_pfather; // ecx
  POINT pt; // [esp+0x4] [ebp-0x8] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
  if ( !PtInRect(&this->m_rect, pt) )
  {
    if ( !LOBYTE(this[1].m_pbktex) )
    {
      m_pfather = this->m_pfather;
      LOBYTE(this[1].m_pbktex) = 1;
      if ( m_pfather )
        m_pfather->OnMessage(1003, this->m_id, 0);
    }
    return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  }
  if ( g_Input.KeyInfo[0].PressTime != 1 || (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v6 = this->m_pfather;
      if ( v6 )
      {
        v6->OnMessage(1010, this->m_id, LOWORD(pt.x) | (LOWORD(pt.y) << 16));
        LOBYTE(this[1].m_pbktex) = 0;
        return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
      }
    }
    else if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
    {
      v7 = this->m_pfather;
      if ( v7 )
      {
        v7->OnMessage(1011, this->m_id, 0);
        LOBYTE(this[1].m_pbktex) = 0;
        return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
      }
    }
    else
    {
      v8 = this->m_pfather;
      if ( v8 )
        v8->OnMessage(1002, this->m_id, 0);
    }
LABEL_20:
    LOBYTE(this[1].m_pbktex) = 0;
    return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  }
  v5 = this->m_pfather;
  if ( !v5 )
    goto LABEL_20;
  v5->OnMessage(1009, this->m_id, LOWORD(pt.x) | (LOWORD(pt.y) << 16));
  LOBYTE(this[1].m_pbktex) = 0;
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x00442C60
void UIFrameWnd::SetPosition(int nVal,   int nVal2)
{
  this[1].m_id = nVal;
  this[1].m_rect.left = nVal2;
}

// 0x00442C80
int UIFrameWnd::SetFrameParam(int nVal)
{
  int result; // eax

  result = nVal;
  this[2].m_fontcolor.Color = nVal;
  return result;
}

// 0x00442D40
void UIFrameWnd::_UIFrameWnd_ovl_00442d40(int nVal1)
{
  (((UIFrameContainer *)this))->UIFrameContainer::~UIFrameContainer();
}

// 0x00442E80
UIFrameWnd::~UIFrameWnd()
{
  (((UIFrameContainer *)this))->UIFrameContainer::~UIFrameContainer();
}

// 0x00442E90
void UIFrameWnd::RenderWithTexture()
{
  gbMatrixStack *v2; // edi
  LONG top; // edx
  int v4; // ecx
  int v5; // ecx
  float v6; // ecx
  unsigned int v7; // ecx
  TextureLibDataBase *v8; // ecx
  float v9; // [esp+0x2C] [ebp-0x74]
  gbColorQuad v10; // [esp+0x30] [ebp-0x70] BYREF
  int m_nSize; // [esp+0x34] [ebp-0x6C]
  float v12; // [esp+0x48] [ebp-0x58]
  int v13; // [esp+0x4C] [ebp-0x54]
  struct gbVec3D v14; // [esp+0x50] [ebp-0x50] BYREF
  _BYTE v15[64]; // [esp+0x60] [ebp-0x40] BYREF

  if ( this->m_bvisible )
  {
    v2 = gfxMgr->pMatrixStack[1];
    (((gbMatrixStack *)v2))->gbMatrixStack::Push();
    top = this->m_rect.top;
    v4 = this->m_rect.right - (this->m_rect.right - this->m_rect.left) / 2;
    m_nSize = 0;
    v13 = v4;
    v5 = this->m_rect.bottom - (this->m_rect.bottom - top) / 2;
    *(float *)&v13 = ((double)v13 + (double)v13) / (double)g_DrvInfo.width - 1.0;
    v12 = 1.0f - ((float)v5 + (float)v5) / (float)g_DrvInfo.height;
    (((gbMatrixStack *)v2))->gbMatrixStack::Translate(*(float *)&v13,   v12,   0.0);
    (((gbMatrixStack *)v2))->gbMatrixStack::Scale(0.125,   0.16666667,   1.0);
    if ( this[2].m_id <= 2 )
    {
      v6 = *(float *)&this[2].m_wndcolor.Color;
      v14.x = 0.0;
      v14.y = 0.0;
      v14.z = 1.0;
      (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(v6,  v14);
    }
    (((gbMatrixStack *)v2))->gbMatrixStack::Scale(8.0,   6.0,   1.0);
    *(float *)&v10.Color = -v12;
    v9 = -*(float *)&v13;
    (((gbMatrixStack *)v2))->gbMatrixStack::Translate(v9,   *(float *)&v10.Color,   0.0);
    if ( this[1].m_childs.capacity )
    {
      m_nSize = this[1].m_childs.m_nSize;
      v10.Color = v7;
      ((gbTextureArray *)v15)->gbTextureArray::gbTextureArray((gbTexture *)this[1].m_childs.capacity);
      (((TextureLibDataBase *)v8))->TextureLibDataBase::_GetItemNum(&this->m_rect);
    }
    (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
  }
}

// 0x004431D0
void UIFrameWnd::DestroyCallingCtor(int nVal1)
{
}

// 0x004433C0
void UIFrameWnd::_dtor_thunk()
{
  (((UIFrameContainer *)this))->UIFrameContainer::~UIFrameContainer();
}

// 0x004433D0
int UIFrameWnd::LayoutAndRender()
{
  int result; // eax
  gbTexture *capacity; // eax
  unsigned int Color; // ecx
  int v5; // ecx
  unsigned int v6; // ecx
  int m_benable; // edx
  int m_nSize; // [esp-0x8] [ebp-0x94]
  int v9; // [esp-0x8] [ebp-0x94]
  struct gbTextureArray v10; // [esp+0x4] [ebp-0x88] BYREF
  struct gbTextureArray v11; // [esp+0x48] [ebp-0x44] BYREF

  result = this->m_bvisible;
  if ( result )
  {
    capacity = (gbTexture *)this[1].m_childs.capacity;
    if ( capacity )
    {
      Color = this[2].m_wndcolor.Color;
      if ( Color )
      {
        if ( Color == 1 )
        {
          v10.pTexPt[0] = capacity;
          m_nSize = this[1].m_childs.m_nSize;
          v10.nTex = 1;
          UIInitSystem(&this->m_rect, &this->m_wndcolor, &v10, 1, m_nSize);
        }
      }
      else
      {
        v5 = this[1].m_childs.m_nSize;
        v11.pTexPt[0] = capacity;
        v11.nTex = 1;
        UIInitSystem(&this->m_rect, &this->m_wndcolor, &v11, 0, v5);
      }
    }
    if ( !this->m_benable && this[1].m_bvisible )
    {
      v6 = this[2].m_wndcolor.Color;
      if ( v6 )
      {
        if ( v6 == 1 )
        {
          m_benable = this[1].m_benable;
          v11.pTexPt[0] = (gbTexture *)this[1].m_bvisible;
          v11.nTex = 1;
          UIInitSystem(&this->m_rect, &this->m_wndcolor, &v11, 1, m_benable);
        }
      }
      else
      {
        v10.pTexPt[0] = (gbTexture *)this[1].m_bvisible;
        v9 = this[1].m_benable;
        v10.nTex = 1;
        UIInitSystem(&this->m_rect, &this->m_wndcolor, &v10, 0, v9);
      }
    }
    (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  }
  return result;
}

// 0x004434C0
void * UIFrameWnd::InitSharedPanel()
{
  ClearSubArraySlot();
  this[1].m_childs.m_nSize = 1065353216;
  this[1].m_childs.capacity = 0;
  this[1].m_wndcolor.Color = 0;
  this[1].m_fontcolor.Color = 0;
  this[1].m_rect.bottom = 0;
  this[1].m_pfather = ((UIWnd *)0);
  this[1].m_childs.m_pData = ((char *)0);
  LOBYTE(this[1].m_childs.m_needscriptdel) = 0;
  this[1].m_bvisible = 0;
  this[1].m_bcreateok = 0;
  this[1].m_bfocus = 0;
  this[1].m_benable = 0;
  LOBYTE(this[1].m_pbktex) = 0;
  this[1].m_id = 792;
  this[1].m_rect.left = 592;
  this[1].m_rect.top = 800;
  this[1].m_rect.right = 600;
  return this;
}

// 0x00443550
void UIFrameWnd::_UIFrameWnd_ovl_00443550()
{
  (((CCBFiveNimbusWindow *)this))->CCBFiveNimbusWindow::Destroy_38f0() /* [ROWTABLE] */;
  this->UIWnd::~UIWnd();
}

// 0x004435A0
gbVFileSystem * UIFrameWnd::LoadFrameResources()
{
  gbColorQuad *p_m_fontcolor; // ebx
  LONG left; // edx
  char *v4; // edi
  char *v5; // eax
  int v6; // ebp
  _DWORD *v7; // ecx
  char *v8; // edx
  char *m_pData; // eax
  int v10; // edi
  gbRefObject *v11; // ecx
  gbTexture *v12; // ecx
  _DWORD *v13; // eax
  _DWORD *v14; // ecx
  gbVFileSystem *result; // eax
  int v16; // [esp+0x10] [ebp-0x118]
  OpenBaseFile v17; // [esp+0x14] [ebp-0x114] BYREF
  char Buffer[257]; // [esp+0x18] [ebp-0x110] BYREF
  __int16 v19; // [esp+0x119] [ebp-0xF]
  char v20; // [esp+0x11B] [ebp-0xD]
  int v21; // [esp+0x124] [ebp-0x4]
  int id; // [esp+0x12C] [ebp+0x4]
  gbTexture *v23; // [esp+0x130] [ebp+0x8]
  int v24; // [esp+0x134] [ebp+0xC]
  unsigned int v25; // [esp+0x138] [ebp+0x10]
  unsigned int v26; // [esp+0x13C] [ebp+0x14]
  unsigned int v27; // [esp+0x140] [ebp+0x18]
  LONG v28; // [esp+0x144] [ebp+0x1C]
  const char *v29; // [esp+0x148] [ebp+0x20]
  int parent; // [esp+0x14C] [ebp+0x24]

  p_m_fontcolor = (gbColorQuad *)&this[1].m_fontcolor;
  this->m_pbktex = ((gbTexture *)(v23));
  *(_DWORD *)((UIWnd *)&this[1]) = v24;
  this[1].m_fontcolor.Color = v25;
  this[1].m_wndcolor.Color = v26;
  this[1].m_id = v27;
  this[1].m_rect.left = v28;
  left = this[1].m_rect.left;
  this[1].m_rect.top = this[1].m_id - this[1].m_fontcolor.Color;
  this[1].m_rect.right = left - this[1].m_wndcolor.Color;
  this[1].m_rect.bottom = (int)v23 / 256;
  this[1].m_pfather = (UIWnd *)(v24 / 256);
  if ( (int)v23 % 256 > 0 )
    this[1].m_rect.bottom = (int)v23 / 256 + 1;
  if ( v24 % 256 > 0 )
    this[1].m_pfather = (UIWnd *)(v24 / 256 + 1);
  v4 = (char *)(this[1].m_rect.bottom * (int)this[1].m_pfather);
  this[1].m_childs.m_pData = v4;
  v5 = (char *)operator new(80 * (_DWORD)v4);
  v6 = 0;
  if ( v5 )
  {
    if ( (int)(v4 - 1) >= 0 )
    {
      v7 = (_DWORD *)v5 + 48;
      v8 = (char *)v4;
      do
      {
        *((_BYTE *)v7 - 48) = 0;
        *(v7 - 1) = 0;
        *v7 = 0;
        v7[1] = 0;
        v7[2] = 0;
        v7[3] = 0;
        v7 += 20;
        --v8;
      }
      while ( v8 );
    }
  }
  else
  {
    v5 = 0;
  }
  this[1].m_childs.capacity = (int)v5;
  memset(Buffer, 0, sizeof(Buffer));
  v19 = 0;
  v20 = 0;
  m_pData = this[1].m_childs.m_pData;
  v21 = 0;
  v16 = 0;
  if ( (int)m_pData > 0 )
  {
    do
    {
      v10 = 80 * v6;
      v11 = (gbRefObject *)*(gbRefObject **)(80 * v6 + this[1].m_childs.capacity + 44);
      if ( v11 )
        (((gbRefObject *)v11))->gbRefObject::Release();
      sprintf(Buffer, "%s%d.tga", v29, v6);
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 44)  = (unsigned long)(gfxMgr->NewTexture((const char *)Buffer));
      v12 = (gbTexture *)*(gbTexture **)(v10 + this[1].m_childs.capacity + 44);
      if ( v12 )
        (((gbTexture *)v12))->gbTexture::LoadTexture(1);
      if ( v6 )
      {
        if ( v6 / this[1].m_rect.bottom <= v16 )
        {
          *(_DWORD *)(v10 + this[1].m_childs.capacity + 8) = *(_DWORD *)(v10 + this[1].m_childs.capacity - 72);
          *(_DWORD *)(v10 + this[1].m_childs.capacity + 4) = *(_DWORD *)(v10 + this[1].m_childs.capacity - 76) + 256;
        }
        else
        {
          *(_DWORD *)(v10 + this[1].m_childs.capacity + 8) = *(_DWORD *)(v10 + this[1].m_childs.capacity - 72) + 256;
          *(gbColorQuad *)(v10 + this[1].m_childs.capacity + 4) = (gbColorQuad)p_m_fontcolor->Color;
          ++v16;
        }
      }
      else
      {
        *(_DWORD *)(this[1].m_childs.capacity + 8) = this[1].m_wndcolor.Color;
        *(gbColorQuad *)(this[1].m_childs.capacity + 4) = (gbColorQuad)p_m_fontcolor->Color;
      }
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 12) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 4) + 256;
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 16) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 8) + 256;
      v13 = (_DWORD *)(v10 + this[1].m_childs.capacity);
      v14 = (_DWORD *)(v13 + 1);
      v13 += 5;
      *v13 = *v14;
      v13[1] = (unsigned long)v14[1];
      v13[2] = (unsigned long)v14[2];
      v13[3] = (unsigned long)v14[3];
      *(float *)(v10 + this[1].m_childs.capacity + 40) = (float)*(int *)(v10 + this[1].m_childs.capacity + 8);
      *(float *)(v10 + this[1].m_childs.capacity + 36) = (float)*(int *)(v10 + this[1].m_childs.capacity + 4);
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 48) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 4)
                                                        - p_m_fontcolor->Color;
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 64) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 48);
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 52) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 4)
                                                        - this[1].m_id;
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 68) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 52);
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 56) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 8)
                                                        - this[1].m_wndcolor.Color;
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 72) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 56);
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 60) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 8)
                                                        - this[1].m_rect.left;
      *(_DWORD *)(v10 + this[1].m_childs.capacity + 76) = *(_DWORD *)(v10 + this[1].m_childs.capacity + 60);
      ++v6;
      *(_BYTE *)(this[1].m_childs.capacity + v10) = 0;
    }
    while ( v6 < (int)this[1].m_childs.m_pData );
  }
  LOBYTE(this[1].m_pbktex) = 1;
  LOBYTE(this[2].m_fontcolor.Color) = 0;
  *(_DWORD *)((UIWnd *)&this[2]) = 1117782016;
  this->UIWnd::Create(id, (tagRECT *)&this[1].m_fontcolor, parent);
  v21 = -1;
  ((OpenNULLFile *)&v17)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x00444AC0
void UIFrameWnd::_UIFrameWnd_Full()
{
  (((UIFrameContainer *)this))->UIFrameContainer::~UIFrameContainer();
}

// 0x00444AD0
int UIFrameWnd::RenderAll()
{
  _PlugInfo *v1; // ebx
  gbTextureArray *v2; // edi
  int result; // eax
  UIWnd *m_pfather; // eax
  LONG bottom; // eax
  char v7; // al
  char *v8; // ebx
  LONG v9; // ecx
  char v10; // al
  LONG v11; // eax
  unsigned __int8 *v12; // eax
  LONG top; // edx
  LONG v14; // ebp
  gbTexture *m_pbktex; // eax
  char *v16; // ecx
  int v17; // edx
  unsigned __int8 *v18; // edi
  char *left; // [esp-0x28] [ebp-0x14C]
  TextureLibDataBase *v20; // [esp-0x28] [ebp-0x14C]
  TextureLibDataBase *right; // [esp-0x20] [ebp-0x144]
  gbTextureArray *v22; // [esp-0x8] [ebp-0x12C]
  _PlugInfo *v23; // [esp-0x4] [ebp-0x128]
  int nY[72]; // [esp+0x4] [ebp-0x120] BYREF

  result = this->m_bvisible;
  if ( !result )
    return result;
  v23 = (_PlugInfo *)v1;
  HIBYTE(this[2].m_wndcolor.Color) = this[2].m_rect.left;
  m_pfather = this[2].m_pfather;
  v22 = (gbTextureArray *)v2;
  if ( m_pfather )
  {
    if ( m_pfather == (UIWnd *)1 )
    {
      if ( this[1].m_childs.capacity )
      {
        nY[38] = this[1].m_childs.capacity;
        nY[54] = 1;
        crt_sub_00540DC0();
      }
      if ( this[1].m_childs.m_needscriptdel )
      {
        nY[4] = this[1].m_childs.m_needscriptdel;
        nY[20] = 1;
        crt_sub_00540DC0();
      }
    }
  }
  else
  {
    if ( this[1].m_childs.capacity )
    {
      nY[21] = this[1].m_childs.capacity;
      right = *((TextureLibDataBase **)this + 6);
      left = *((char **)this + 4);
      nY[37] = 1;
      (((TextureLibDataBase *)right))->TextureLibDataBase::GetLibInfo(left);
    }
    if ( this[1].m_childs.m_needscriptdel )
    {
      nY[55] = this[1].m_childs.m_needscriptdel;
      v20 = *((TextureLibDataBase **)this + 4);
      nY[71] = 1;
      (((TextureLibDataBase *)v20))->TextureLibDataBase::GetLibInfo((char *)((Parent_Data *)v20));
    }
  }
  bottom = this[1].m_rect.bottom;
  if ( bottom )
  {
    v7 = *(_BYTE *)(bottom - 1);
    if ( !v7 || v7 == -1 )
      goto LABEL_27;
    v8 = (char *)this[1].m_pfather;
    if ( (unsigned int)v8 > 0xFFFFFFFD )
      std::_Xlen();
    v9 = this[1].m_rect.bottom;
    if ( v9 && (v10 = *(_BYTE *)(v9 - 1)) != 0 && v10 != -1 )
    {
      if ( !v8 )
      {
        *(_BYTE *)(v9 - 1) = v10 - 1;
        (((std::string *)0))->_Tidy();
        goto LABEL_27;
      }
    }
    else
    {
      if ( !v8 )
      {
        if ( v9 )
          (((std::string *)this[1].m_pfather))->_Eos();
        goto LABEL_27;
      }
      if ( this[1].m_childs.m_pData >= v8 )
      {
LABEL_27:
        v11 = this[1].m_rect.bottom;
        if ( v11 )
          *(_BYTE *)(v11 - 1) = -1;
        v12 = (unsigned __int8 *)this[1].m_rect.bottom;
        goto LABEL_31;
      }
    }
    (((GRPinput *)&this[1].m_rect.right))->GRPinput::PollInputState((unsigned int)this[1].m_pfather);
    goto LABEL_27;
  }
  v12 = (unsigned __int8 *)&g_bActorFlag;
LABEL_31:
  if ( *v12 )
  {
    top = this->m_rect.top;
    v14 = this->m_rect.bottom;
    m_pbktex = (gbTexture *)this->m_pbktex;
    v16 = (char *)m_pbktex + this->m_rect.left;
    nY[2] = this->m_rect.right - (_DWORD)m_pbktex;
    nY[0] = (int)&v16[this[1].m_id];
    v17 = (int)m_pbktex + top + this[1].m_rect.left;
    HIBYTE(this->m_fontcolor.Color) = this[2].m_rect.left;
    v18 = (unsigned __int8 *)this[1].m_rect.bottom;
    nY[1] = v17;
    nY[3] = v14 - (_DWORD)m_pbktex;
    if ( !v18 )
      v18 = (unsigned __int8 *)&g_bActorFlag;
    UIRenderPar(
      (int)v18,
      (int)nY,
      (int)&this->m_fontcolor,
      this[1].m_rect.top,
      *(gbColorQuad **)((UIWnd *)&this[1]),
      v22,
      v23);
  }
  (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  return result;
}

// 0x00444D30
BOOL UIFrameWnd::ProcessInput(int nVal, int nVal2)
{
  double left; // st7
  __int64 v6; // rax
  LONG m_id; // ecx
  char v8; // al
  __int64 v9; // rax
  int top; // ecx
  UIWnd *m_pfather; // ecx
  UIWnd *v12; // ecx
  UIWnd *v13; // ecx
  POINT pt; // [esp+0x18] [ebp-0x8] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( BYTE1(this[2].m_rect.bottom) )
  {
    left = (double)this[2].m_rect.left;
    if ( LOBYTE(this[2].m_rect.bottom) )
    {
      v6 = (__int64)(left + *(float *)&this[2].m_rect.right);
      m_id = this[2].m_id;
      this[2].m_rect.left = v6;
      if ( (int)v6 >= m_id )
      {
        v8 = BYTE2(this[2].m_rect.bottom);
        this[2].m_rect.left = m_id;
        LOBYTE(this[2].m_rect.bottom) = 0;
        if ( v8 )
        {
          BYTE1(this[2].m_rect.bottom) = 0;
          this[2].m_rect.left = m_id;
          LOBYTE(this[2].m_rect.bottom) = 0;
          BYTE2(this[2].m_rect.bottom) = 0;
        }
      }
    }
    else
    {
      v9 = (__int64)(left - *(float *)&this[2].m_rect.right);
      top = this[2].m_rect.top;
      this[2].m_rect.left = v9;
      if ( (int)v9 <= top )
      {
        this[2].m_rect.left = top;
        LOBYTE(this[2].m_rect.bottom) = 1;
      }
    }
  }
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
  if ( PtInRect(&this->m_rect, pt) )
  {
    if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      m_pfather = this->m_pfather;
      if ( m_pfather )
        m_pfather->OnMessage(1009, this->m_id, LOWORD(pt.x) | (LOWORD(pt.y) << 16));
    }
    if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v12 = this->m_pfather;
      if ( v12 )
        v12->OnMessage(1010, this->m_id, LOWORD(pt.x) | (LOWORD(pt.y) << 16));
    }
    if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
    {
      v13 = this->m_pfather;
      if ( v13 )
        v13->OnMessage(1011, this->m_id, 0);
    }
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x00450560
BOOL UIFrameWnd::IsOnScreen(int nVal, int nVal2)
{
  unsigned int Color; // eax
  int v6; // edi
  int v7; // ecx
  int m_id; // kr00_4
  LONG left; // eax
  float v10; // [esp+0xC] [ebp-0x14] BYREF
  float v11; // [esp+0x10] [ebp-0x10] BYREF
  struct gbVec3D v12; // [esp+0x14] [ebp-0xC] BYREF

  if ( !this->m_bvisible )
    return 0;
  Color = this[1].m_wndcolor.Color;
  if ( Color )
  {
    v12 = *(gbVec3D *)(Color + 160);
    v12.y = v12.y + 80.0;
    (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::PointWorldToScr(&v12, &v10, &v11);
    v6 = (__int64)((v10 + 1.0) * (double)g_DrvInfo.width * 0.5);
    v7 = (__int64)((1.0 - v11) * (double)g_DrvInfo.height * 0.5);
    m_id = this[1].m_id;
    this->m_rect.right = v6 + m_id / 2;
    left = this[1].m_rect.left;
    this->m_rect.left = v6 - m_id / 2;
    left /= 2;
    this->m_rect.top = v7 - left;
    this->m_rect.bottom = v7 + left;
  }
  return this->UIFrameWnd::Update_bbc0(nVal, nVal2);
}

// 0x00478880
BOOL UIFrameWnd::ProcessTimer(BOOL bEnable, BOOL bReset, int nInterval, int nParam)
{
  BOOL result; // eax
  unsigned int v7; // ebp
  DWORD TickCount; // eax
  DWORD v9; // eax
  unsigned int v10; // ecx
  char v11; // bl
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  LONG right; // ecx
  int v17; // edx
  int v18; // edx
  LONG v19; // ecx
  LONG v20; // ecx
  LONG v21; // ecx
  LONG v22; // edx
  UIWnd *m_pfather; // ecx
  LONG v24; // edx
  LONG v25; // edx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  LONG top; // edx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  int v34; // ecx
  int v35; // edx
  LONG bottom; // ecx
  int v37; // edx
  int Color; // ecx
  int v39; // ecx
  int v40; // ecx
  LONG left; // ecx
  LONG v42; // ecx
  LONG v43; // ecx
  int v44; // ecx
  int v45; // ecx
  int v46; // ecx
  int m_id; // ecx
  int v48; // ecx
  int v49; // [esp+0x18] [ebp+0x14]
  int v50; // [esp+0x1C] [ebp+0x18]
  LONG v51; // [esp+0x20] [ebp+0x1C]
  UIWnd *v52; // [esp+0x24] [ebp+0x20]

  LOBYTE(result) = bEnable;
  if ( bEnable )
  {
    v7 = (unsigned int)((UIWnd *)this);
    if ( !LOBYTE(this->m_childs.m_needscriptdel) )
    {
      TickCount = GetTickCount();
      this->m_childs.capacity = TickCount;
      this->m_childs.m_nSize = TickCount;
      LOBYTE(this->m_childs.m_needscriptdel) = 1;
    }
    v9 = GetTickCount();
    v10 = v9 - this->m_childs.m_nSize;
    this->m_childs.capacity = v9;
    if ( v10 <= v7 )
    {
      v11 = 0;
    }
    else
    {
      this->m_childs.m_nSize = v9;
      LOBYTE(this->m_childs.m_needscriptdel) = 0;
      v11 = 1;
    }
    if ( !bReset )
    {
      Color = this->m_wndcolor.Color;
      if ( v49 <= Color )
      {
        if ( v11 )
        {
          v40 = Color - nInterval;
          this->m_wndcolor.Color = v40;
          if ( v40 <= v49 )
            this->m_wndcolor.Color = this->m_rect.right;
        }
      }
      else if ( v11 )
      {
        v39 = nInterval + Color;
        this->m_wndcolor.Color = v39;
        if ( v39 >= v49 )
          this->m_wndcolor.Color = this->m_rect.right;
      }
      left = this->m_rect.left;
      if ( v51 <= left )
      {
        if ( v11 )
        {
          v43 = left - nInterval;
          this->m_rect.left = v43;
          if ( v43 <= v51 )
            this->m_rect.left = (LONG)this->m_pfather;
        }
      }
      else if ( v11 )
      {
        v42 = nInterval + left;
        this->m_rect.left = v42;
        if ( v42 >= v51 )
          this->m_rect.left = (LONG)this->m_pfather;
      }
      v44 = this->m_fontcolor.Color;
      if ( nParam <= v44 )
      {
        if ( v11 )
        {
          v46 = v44 - nInterval;
          this->m_fontcolor.Color = v46;
          if ( v46 <= nParam )
            this->m_fontcolor.Color = this->m_rect.top;
        }
      }
      else if ( v11 )
      {
        v45 = nInterval + v44;
        this->m_fontcolor.Color = v45;
        if ( v45 >= nParam )
          this->m_fontcolor.Color = this->m_rect.top;
      }
      m_id = this->m_id;
      if ( v50 <= m_id )
      {
        if ( v11 )
        {
          v48 = m_id - nInterval;
          this->m_id = v48;
          if ( v48 <= v50 )
            this->m_id = this->m_rect.bottom;
        }
      }
      else if ( v11 )
      {
        this->m_id = m_id + nInterval;
        if ( m_id + nInterval >= v50 )
        {
          this->m_id = this->m_rect.bottom;
          return (((UIWnd *)v52))->UIWnd::sub_445FA0(&this->m_fontcolor);
        }
      }
      return (((UIWnd *)v52))->UIWnd::sub_445FA0(&this->m_fontcolor);
    }
    if ( LOBYTE(this->m_childs.m_pData) )
    {
      if ( !v11 )
        goto LABEL_21;
      v15 = this->m_wndcolor.Color;
      right = this->m_rect.right;
      if ( v15 < right )
      {
        v18 = nInterval + v15;
        this->m_wndcolor.Color = v18;
        if ( v18 < right )
          goto LABEL_21;
      }
      else
      {
        v17 = v15 - nInterval;
        this->m_wndcolor.Color = v17;
        if ( v17 > right )
          goto LABEL_21;
      }
      this->m_wndcolor.Color = right;
      LOBYTE(this->m_childs.m_pData) = 0;
    }
    else if ( v11 )
    {
      v12 = this->m_wndcolor.Color;
      if ( v49 <= v12 )
      {
        v14 = v12 - nInterval;
        this->m_wndcolor.Color = v14;
        if ( v14 <= v49 )
        {
          this->m_wndcolor.Color = v49;
          LOBYTE(this->m_childs.m_pData) = 1;
        }
      }
      else
      {
        v13 = nInterval + v12;
        this->m_wndcolor.Color = v13;
        if ( v13 >= v49 )
        {
          this->m_wndcolor.Color = v49;
          LOBYTE(this->m_childs.m_pData) = 1;
        }
      }
    }
LABEL_21:
    if ( BYTE1(this->m_childs.m_pData) )
    {
      if ( !v11 )
        goto LABEL_34;
      v22 = this->m_rect.left;
      m_pfather = this->m_pfather;
      if ( v22 < (int)m_pfather )
      {
        v25 = nInterval + v22;
        this->m_rect.left = v25;
        if ( v25 < (int)m_pfather )
          goto LABEL_34;
      }
      else
      {
        v24 = v22 - nInterval;
        this->m_rect.left = v24;
        if ( v24 > (int)m_pfather )
          goto LABEL_34;
      }
      this->m_rect.left = (LONG)m_pfather;
      BYTE1(this->m_childs.m_pData) = 0;
    }
    else if ( v11 )
    {
      v19 = this->m_rect.left;
      if ( v51 <= v19 )
      {
        v21 = v19 - nInterval;
        this->m_rect.left = v21;
        if ( v21 <= v51 )
        {
          this->m_rect.left = v51;
          BYTE1(this->m_childs.m_pData) = 1;
        }
      }
      else
      {
        v20 = nInterval + v19;
        this->m_rect.left = v20;
        if ( v20 >= v51 )
        {
          this->m_rect.left = v51;
          BYTE1(this->m_childs.m_pData) = 1;
        }
      }
    }
LABEL_34:
    if ( BYTE2(this->m_childs.m_pData) )
    {
      if ( !v11 )
        goto LABEL_47;
      v29 = this->m_fontcolor.Color;
      top = this->m_rect.top;
      if ( v29 < top )
      {
        top = nParam;
        v32 = nInterval + v29;
        this->m_fontcolor.Color = v32;
        if ( v32 < nParam )
          goto LABEL_47;
      }
      else
      {
        v31 = v29 - nInterval;
        this->m_fontcolor.Color = v31;
        if ( v31 > top )
          goto LABEL_47;
      }
      this->m_fontcolor.Color = top;
      BYTE2(this->m_childs.m_pData) = 0;
    }
    else if ( v11 )
    {
      v26 = this->m_fontcolor.Color;
      if ( nParam <= v26 )
      {
        v28 = v26 - nInterval;
        this->m_fontcolor.Color = v28;
        if ( v28 <= nParam )
        {
          this->m_fontcolor.Color = nParam;
          BYTE2(this->m_childs.m_pData) = 1;
        }
      }
      else
      {
        v27 = nInterval + v26;
        this->m_fontcolor.Color = v27;
        if ( v27 >= nParam )
        {
          this->m_fontcolor.Color = nParam;
          BYTE2(this->m_childs.m_pData) = 1;
        }
      }
    }
LABEL_47:
    if ( !HIBYTE(this->m_childs.m_pData) )
    {
      if ( v11 )
      {
        v33 = this->m_id;
        if ( v50 <= v33 )
        {
          v34 = v33 - nInterval;
          this->m_id = v34;
          if ( v34 <= v50 )
            goto LABEL_51;
        }
        else
        {
          this->m_id = v33 + nInterval;
          if ( v33 + nInterval >= v50 )
          {
LABEL_51:
            this->m_id = v50;
            HIBYTE(this->m_childs.m_pData) = 1;
            return (((UIWnd *)v52))->UIWnd::sub_445FA0(&this->m_fontcolor);
          }
        }
      }
      return (((UIWnd *)v52))->UIWnd::sub_445FA0(&this->m_fontcolor);
    }
    if ( v11 )
    {
      v35 = this->m_id;
      bottom = this->m_rect.bottom;
      if ( v35 < bottom )
      {
        this->m_id = v35 + nInterval;
        if ( v35 + nInterval >= bottom )
          goto LABEL_57;
      }
      else
      {
        v37 = v35 - nInterval;
        this->m_id = v37;
        if ( v37 <= bottom )
        {
LABEL_57:
          this->m_id = bottom;
          HIBYTE(this->m_childs.m_pData) = 0;
          return (((UIWnd *)v52))->UIWnd::sub_445FA0(&this->m_fontcolor);
        }
      }
    }
    return (((UIWnd *)v52))->UIWnd::sub_445FA0(&this->m_fontcolor);
  }
  return result;
}

// 0x0048CFB0
bool UIFrameWnd::RollProbability(float fProb)
{
  int fProba; // [esp+0xC] [ebp+0x8]
  float fProbb; // [esp+0xC] [ebp+0x8]

  fProba = (__int64)(fProb * 100.0);
  if ( fProba <= 0 )
    return 0;
  fProbb = (float)fProba * 10.239999771118164f;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
  return (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)fProbb;
}
