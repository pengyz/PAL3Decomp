#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIFrameWnd.h"

// Forward declarations for unnamed functions
int sub_4431B0(...);
int sub_4433A0(...);
int sub_443530(...);
int sub_443CA0(...);
int sub_444AA0(...);
int sub_445AA0(void); // from annotations
int sub_445FA0(void *a2); // from annotations

int crt_sub_00540DC0(void); // from annotations

// Unnamed globals (extern)
extern TextureLibDataBase stru_1894B78;
extern unsigned int unk_5DFDEC;

// 0x0043BB70
UIFrameWnd::UIFrameWnd()
{
  sub_445AA0();
  this->m_pbktex = 0;
  (int *)this;
}

// 0x0043BBC0
BOOL UIFrameWnd::Update_bbc0(int nVal, int nVal2)
{
  BOOL result; // eax
  BOOL v5; // ebx
  POINT pt; // [esp+0x8] [ebp-0x8]

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( this->m_pbktex )
  {
    ((UIListBox *)this)->Update(nVal, 1);
    return 1;
  }
  result = ((UIListBox *)this)->Update(nVal, nVal2);
  v5 = result;
  if ( nVal2 )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    result = PtInRect(&this->m_rect, pt);
    if ( result || v5 )
      return 1;
  }
  return result;
}

// 0x00442390
void UIFrameWnd::UIFrameWnd::_UIFrameWnd()
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al

  v2 = *((_DWORD *)this + 25);
  if ( v2 )
  {
    v3 = (_BYTE *)(v2 - 1);
    v4 = *(_BYTE *)(v2 - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 26) = 0;
  *((_DWORD *)this + 27) = 0;
// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x00442420
void UIFrameWnd::Destroy()
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *v5; // ecx

  v2 = (gbRefObject *)*((_DWORD *)this + 28);
  if ( v2 )
  {
    ((gbRefObject *)v2)->Release();
    *((_DWORD *)this + 28) = 0;
  }
  v3 = (gbRefObject *)*((_DWORD *)this + 32);
  if ( v3 )
  {
    ((gbRefObject *)v3)->Release();
    *((_DWORD *)this + 32) = 0;
  }
  v4 = (gbRefObject *)*((_DWORD *)this + 34);
  if ( v4 )
  {
    ((gbRefObject *)v4)->Release();
    *((_DWORD *)this + 34) = 0;
  }
  v5 = (gbRefObject *)*((_DWORD *)this + 30);
  if ( v5 )
  {
    ((gbRefObject *)v5)->Release();
    *((_DWORD *)this + 30) = 0;
  }
  *((_DWORD *)this + 37) = -1;
}

// 0x00442540
gbVFileSystem * UIFrameWnd::SetTextureByID(int nTexID)
{
  gbRefObject *v3; // ecx
  gbTexture *v4; // eax
  gbVFileSystem *result; // eax
  OpenBaseFile v6; // [esp+0x8] [ebp-0x10] BYREF
  int v7; // [esp+0x14] [ebp-0x4]

  v3 = (gbRefObject *)*((_DWORD *)this + 34);
  if ( v3 )
    ((gbRefObject *)v3)->Release();
  ((OpenBaseFile *)&v6)->_OpenBaseFile();
  v7 = 0;
  v4 = (gbTexture *)(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr + 8))(gfxMgr, nTexID);
  *((_DWORD *)this + 34) = v4;
  if ( v4 )
    ((gbTexture *)v4)->LoadTexture(1);
  v7 = -1;
  return result;
}

// 0x004425D0
void UIFrameWnd::SetTextureByName(LPCSTR lpTexName, char bCalcUV)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  CHAR *v8; // eax
  gbTexture *v9; // ecx

  v3 = lpTexName;
  if ( lpTexName )
  {
    v5 = (gbRefObject *)*((_DWORD *)this + 32);
    if ( v5 )
      ((gbRefObject *)v5)->Release();
    v6 = bCalcUV == 0;
    *((_DWORD *)this + 33) = 0;
    if ( v6 )
    {
      *((_DWORD *)this + 32) = (*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, v3);
    }
    else
    {
      v7 = *(_DWORD *)gfxMgr;
      v8 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v3);
      *((_DWORD *)this + 32) = (*(int ( **)(gbGfxManager *, CHAR *))(v7 + 8))(gfxMgr, v8);
      *((_DWORD *)this + 33) = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 32);
    if ( v9 )
      ((gbTexture *)v9)->LoadTexture(1);
  }
}

// 0x00442890
int UIFrameWnd::CalculateLayout()
{
  int result; // eax
  LONG left; // ecx
  int v4; // eax
  double v5; // st7
  LONG top; // ecx
  double v7; // st7
  double v8; // st6
  __int64 v9; // rax
  double v10; // st7
  unsigned int v11; // ecx
  int *v12; // eax
  int *v13; // edx
  TextureLibDataBase *v14; // ecx
  int v15; // edx
  int v16; // ecx
  gbTexture *m_pbktex; // edx
  int v18; // edi
  int v19; // eax
  unsigned __int8 *v20; // eax
  TextureLibDataBase *v21; // [esp-0x1C] [ebp-A0h]
  gbColorQuad v22; // [esp-0xC] [ebp-0x90] BYREF
  int *v23; // [esp-0x8] [ebp-0x8C]
  int v24; // [esp-0x4] [ebp-0x88]
  gbTextureArray *v25; // [esp+0x0] [ebp-0x84]
  _PlugInfo *v26; // [esp+0x4] [ebp-0x80]
  int v27; // [esp+0x10] [ebp-0x74]
  LONG right; // [esp+0x14] [ebp-0x70]
  LONG v29; // [esp+0x18] [ebp-0x6C]
  LONG bottom; // [esp+0x1C] [ebp-0x68]
  int nY; // [esp+0x20] [ebp-0x64] BYREF
  int v32; // [esp+0x24] [ebp-0x60]
  int v33; // [esp+0x28] [ebp-0x5C]
  int v34; // [esp+0x2C] [ebp-0x58]
  char pszBuf[4]; // [esp+0x30] [ebp-0x54] BYREF
  int v36; // [esp+0x34] [ebp-0x50]
  int v37; // [esp+0x38] [ebp-0x4C]
  int v38; // [esp+0x3C] [ebp-0x48]
  int v39; // [esp+0x40] [ebp-0x44] BYREF
  _BYTE v40[64]; // [esp+0x44] [ebp-0x40] BYREF

  result = this->m_bvisible;
  if ( result )
  {
    left = this->m_rect.left;
    right = this->m_rect.right;
    v4 = left + right;
    v27 = left;
    v5 = 1.0 - *((float *)this + 19);
    top = this->m_rect.top;
    nY = v4 / 2;
    v7 = v5 * (double)(v4 / 2);
    bottom = this->m_rect.bottom;
    v29 = top;
    v8 = (double)v27 * *((float *)this + 19);
    v32 = (top + bottom) / 2;
    *(_DWORD *)pszBuf = (__int64)(v8 + v7);
    v9 = (__int64)((double)right * *((float *)this + 19) + v7);
    v10 = (1.0 - *((float *)this + 20)) * (double)v32;
    v37 = v9;
    v36 = (__int64)((double)top * *((float *)this + 20) + v10);
    v38 = (__int64)((double)bottom * *((float *)this + 20) + v10);
    if ( *((_DWORD *)this + 28) )
    {
      v11 = *((_DWORD *)this + 36);
      v24 = *((_DWORD *)this + 29);
      v23 = (int *)v11;
      v22.Color = v11;
      ((TextureLibDataBase *)pszBuf)->_CheckItem((char *)&this->m_rect, pszBuf);
    }
    if ( !this->m_benable && *((_DWORD *)this + 32) )
    {
      v12 = (int *)*((_DWORD *)this + 36);
      v24 = *((_DWORD *)this + 33);
      v23 = v12;
      v22.Color = top;
      ((TextureLibDataBase *)pszBuf)->_CheckItem((char *)&this->m_rect, pszBuf);
    }
    if ( *((_DWORD *)this + 34) )
    {
      v39 = *((_DWORD *)this + 34);
      v24 = 0;
      v23 = &v39;
      v22.Color = (unsigned int)&this->m_wndcolor;
      v21 = (TextureLibDataBase *)this->m_rect.left;
      *(_DWORD *)&v40[60] = 1;
      ((TextureLibDataBase *)v21)->GetTextureInfoByIndex((int)v21);
    }
    if ( *((_DWORD *)this + 30) )
    {
      v13 = (int *)*((_DWORD *)this + 36);
      v24 = 0;
      v23 = v13;
      v22.Color = top;
      ((TextureLibDataBase *)v14)->_CheckItem((char *)&this->m_rect, pszBuf);
    }
    if ( *((_DWORD *)this + 26) )
    {
      v15 = *((_DWORD *)this + 22);
      nY = *(_DWORD *)pszBuf;
      v16 = v15 + v36;
      m_pbktex = this->m_pbktex;
      v18 = *((_DWORD *)this + 37);
      v19 = (int)m_pbktex + *(_DWORD *)pszBuf + *((_DWORD *)this + 21);
      nY = v19;
      if ( v18 == -1 )
        v33 = v37 - (_DWORD)m_pbktex;
      else
        v33 = v19 + v18;
      v20 = (unsigned __int8 *)*((_DWORD *)this + 25);
      v32 = (int)m_pbktex + v16;
      v34 = v38 - (_DWORD)m_pbktex;
      if ( !v20 )
        v20 = &g_bActorFlag;
      UIRenderPar(
        (int)v20,
        (int)&nY,
        (int)&this->m_fontcolor,
        *((_DWORD *)this + 23),
        *((gbColorQuad **)this + 18),
        v25,
        v26);
    }
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
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
  POINT pt; // [esp+0x4] [ebp-0x8]

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( !PtInRect(&this->m_rect, pt) )
  {
    if ( !*((_BYTE *)this + 140) )
    {
      m_pfather = this->m_pfather;
      *((_BYTE *)this + 140) = 1;
      if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1003,
// [VFTABLE]   this->m_id,
// [VFTABLE]   0);
    }
    return ((UIListBox *)this)->Update(nVal, nVal2);
  }
  if ( g_Input.KeyInfo[0].PressTime != 1 || (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v6 = this->m_pfather;
      if ( v6 )
      {
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v6->__vftable->OnMessage)(
// [VFTABLE]   v6,
// [VFTABLE]   1010,
// [VFTABLE]   this->m_id,
// [VFTABLE]   LOWORD(pt.x) | (LOWORD(pt.y) << 16));
        *((_BYTE *)this + 140) = 0;
        return ((UIListBox *)this)->Update(nVal, nVal2);
      }
    }
    else if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
    {
      v7 = this->m_pfather;
      if ( v7 )
      {
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v7->__vftable->OnMessage)(v7, 1011, this->m_id, 0);
        *((_BYTE *)this + 140) = 0;
        return ((UIListBox *)this)->Update(nVal, nVal2);
      }
    }
    else
    {
      v8 = this->m_pfather;
      if ( v8 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v8->__vftable->OnMessage)(v8, 1002, this->m_id, 0);
    }
LABEL_20:
    *((_BYTE *)this + 140) = 0;
    return ((UIListBox *)this)->Update(nVal, nVal2);
  }
  v5 = this->m_pfather;
  if ( !v5 )
    goto LABEL_20;
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v5->__vftable->OnMessage)(
// [VFTABLE]   v5,
// [VFTABLE]   1009,
// [VFTABLE]   this->m_id,
// [VFTABLE]   LOWORD(pt.x) | (LOWORD(pt.y) << 16));
  *((_BYTE *)this + 140) = 0;
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00442C60
void UIFrameWnd::SetPosition(int nVal,   int nVal2)
{
  *((_DWORD *)this + 21) = nVal;
  *((_DWORD *)this + 22) = nVal2;
}

// 0x00442C80
int UIFrameWnd::SetFrameParam(int nVal)
{
  *((_DWORD *)this + 37) = nVal;
  return nVal;
}

// 0x00442D20
UIFrameWnd * UIFrameWnd::_sdtor_8(UIFrameWnd *Block, char a2)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00442D40
void UIFrameWnd::_UIFrameWnd_ovl_2d40()
{
}

// 0x00442E80
void UIFrameWnd::ctor()
{
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
  int v11; // [esp+0x34] [ebp-0x6C]
  float v12; // [esp+0x48] [ebp-0x58]
  float v13; // [esp+0x4C] [ebp-0x54]
  struct gbVec3D v14; // [esp+0x50] [ebp-0x50] BYREF
  _BYTE v15[64]; // [esp+0x60] [ebp-0x40] BYREF

  if ( this->m_bvisible )
  {
    v2 = gfxMgr->pMatrixStack[1];
    ((gbMatrixStack *)v2)->Push();
    top = this->m_rect.top;
    v4 = this->m_rect.right - (this->m_rect.right - this->m_rect.left) / 2;
    v11 = 0;
    v13 = *(float *)&v4;
    v5 = this->m_rect.bottom - (this->m_rect.bottom - top) / 2;
    v13 = ((double)SLODWORD(v13) + (double)SLODWORD(v13)) / (double)g_DrvInfo.width - 1.0;
    v12 = 1.0 - ((double)v5 + (double)v5) / (double)g_DrvInfo.height;
    ((gbMatrixStack *)v2)->Translate(v13,   v12,   0.0);
    ((gbMatrixStack *)v2)->Scale(0.125,   0.16666667,   1.0);
    if ( *((_DWORD *)this + 39) <= 2u )
    {
      v6 = *((float *)this + 38);
      v14.x = 0.0;
      v14.y = 0.0;
      v14.z = 1.0;
      ((gbMatrixStack *)v2)->Rotate(v6, v14);
    }
    ((gbMatrixStack *)v2)->Scale(8.0,   6.0,   1.0);
    *(float *)&v10.Color = -v12;
    v9 = -v13;
    ((gbMatrixStack *)v2)->Translate(v9,   *(float *)&v10.Color,   0.0);
    if ( *((_DWORD *)this + 28) )
    {
      v11 = *((_DWORD *)this + 29);
      v10.Color = v7;
      ((TextureLibDataBase *)v8)->_GetItemNum(&this->m_rect);
    }
    ((gbMatrixStack *)v2)->Pop();
  }
}

// 0x00442FF0
BOOL UIFrameWnd::Update_2ff0(int nVal, int nVal2)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  double v6; // st7
  double v8; // st7
  double v9; // st7
  int v10; // eax
  double v11; // st7
  double v12; // st7
  int v13; // eax

  v3 = *((_DWORD *)this + 39);
  if ( v3 )
  {
    v4 = v3 - 1;
    if ( v4 )
    {
      if ( v4 == 1 )
      {
        v5 = *((_DWORD *)this + 42);
        if ( v5 )
        {
          if ( v5 == 1 )
          {
            v6 = *((float *)this + 38) - *((float *)this + 41);
            *((float *)this + 38) = v6;
            if ( v6 < 0.0 )
            {
              *((_DWORD *)this + 38) = 1135837184;
              return this->Update(nVal, nVal2);
            }
          }
        }
        else
        {
          v8 = *((float *)this + 41) + *((float *)this + 38);
          *((float *)this + 38) = v8;
          if ( v8 > 359.0 )
          {
            *((_DWORD *)this + 38) = 0;
            return this->Update(nVal, nVal2);
          }
        }
      }
      return this->Update(nVal, nVal2);
    }
    if ( !*((_BYTE *)this + 172) )
    {
      v9 = *((float *)this + 44) + *((float *)this + 41);
      v10 = *((_DWORD *)this + 42);
      *((float *)this + 41) = v9;
      if ( !v10 )
      {
        v12 = v9 + *((float *)this + 38);
        *((float *)this + 38) = v12;
        if ( v12 < *((float *)this + 40) )
          goto LABEL_14;
        goto LABEL_16;
      }
      if ( v10 == 1 )
      {
        v11 = *((float *)this + 38) - v9;
        *((float *)this + 38) = v11;
        if ( v11 > *((float *)this + 40) )
        {
LABEL_14:
          *((_BYTE *)this + 172) = 0;
          return this->Update(nVal, nVal2);
        }
LABEL_16:
        v13 = *((_DWORD *)this + 40);
        *((_DWORD *)this + 41) = *((_DWORD *)this + 45);
        *((_DWORD *)this + 38) = v13;
        *((_BYTE *)this + 172) = 1;
        return this->Update(nVal, nVal2);
      }
    }
  }
  else if ( !*((_BYTE *)this + 172) )
  {
    *((_DWORD *)this + 38) = *((_DWORD *)this + 40);
    *((_BYTE *)this + 172) = 1;
    return this->Update(nVal, nVal2);
  }
  return this->Update(nVal, nVal2);
}

// 0x004431B0
int UIFrameWnd::sub_4431B0(void *Block, char a3)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x004431D0
void UIFrameWnd::DestroyCallingCtor()
{

}

// 0x00443200
void UIFrameWnd::Render()
{
  gbMatrixStack *v1; // edi
  LONG top; // edx
  int v4; // ecx
  float v5; // ecx
  unsigned int v6; // ecx
  TextureLibDataBase *v7; // ecx
  float v8; // [esp+0x2C] [ebp-0x74]
  gbColorQuad v9; // [esp+0x30] [ebp-0x70] BYREF
  int v10; // [esp+0x34] [ebp-0x6C]
  int v11; // [esp+0x48] [ebp-0x58]
  float v12; // [esp+0x4C] [ebp-0x54]
  struct gbVec3D v13; // [esp+0x50] [ebp-0x50] BYREF
  _BYTE v14[64]; // [esp+0x60] [ebp-0x40] BYREF

  v1 = gfxMgr->pMatrixStack[1];
  ((gbMatrixStack *)v1)->Push();
  top = this->m_rect.top;
  v4 = this->m_rect.right - (this->m_rect.right - this->m_rect.left) / 2;
  v10 = 0;
  v12 = *(float *)&v4;
  v11 = this->m_rect.bottom - (this->m_rect.bottom - top) / 2;
  v12 = ((double)SLODWORD(v12) + (double)SLODWORD(v12)) / (double)g_DrvInfo.width
      - 1.0
      + ((double)*((int *)this + 46) + (double)*((int *)this + 46)) / (double)g_DrvInfo.width
      - 1.0;
  *(float *)&v11 = 1.0
                 - ((double)v11 + (double)v11) / (double)g_DrvInfo.height
                 + 1.0
                 - ((double)*((int *)this + 47) + (double)*((int *)this + 47)) / (double)g_DrvInfo.height;
  ((gbMatrixStack *)v1)->Translate(v12,   *(float *)&v11,   0.0);
  ((gbMatrixStack *)v1)->Scale(0.125,   0.16666667,   1.0);
  if ( *((_DWORD *)this + 39) <= 2u )
  {
    v5 = *((float *)this + 38);
    v13.x = 0.0;
    v13.y = 0.0;
    v13.z = 1.0;
    ((gbMatrixStack *)v1)->Rotate(v5, v13);
  }
  ((gbMatrixStack *)v1)->Scale(8.0,   6.0,   1.0);
  *(float *)&v9.Color = -*(float *)&v11;
  v8 = -v12;
  ((gbMatrixStack *)v1)->Translate(v8,   *(float *)&v9.Color,   0.0);
  if ( *((_DWORD *)this + 28) )
  {
    v10 = *((_DWORD *)this + 29);
    v9.Color = v6;
    ((TextureLibDataBase *)v7)->_GetItemNum(&this->m_rect);
  }
  ((gbMatrixStack *)v1)->Pop();
}

// 0x004433A0
int UIFrameWnd::sub_4433A0(void *Block, char a3)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x004433C0
void UIFrameWnd::_dtor_thunk()
{
}

// 0x004434C0
void * UIFrameWnd::InitSharedPanel()
{
  sub_445AA0();
  *((_DWORD *)this + 29) = 1065353216;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 20) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 26) = 0;
  *((_DWORD *)this + 27) = 0;
  *((_BYTE *)this + 120) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 34) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_BYTE *)this + 140) = 0;
  *((_DWORD *)this + 21) = 792;
  *((_DWORD *)this + 22) = 592;
  *((_DWORD *)this + 23) = 800;
  *((_DWORD *)this + 24) = 600;
  return this;
}

// 0x00443530
int UIFrameWnd::sub_443530(void *Block, char a3)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x00443550
void UIFrameWnd::_UIFrameWnd_ovl()
{

// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x004435A0
gbVFileSystem * UIFrameWnd::LoadFrameResources()
{
  UIFrameWnd *v2; // ebx
  int v3; // edx
  int v4; // edi
  char *v5; // eax
  int v6; // ebp
  _DWORD *v7; // ecx
  int v8; // edx
  int v9; // eax
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
  int v25; // [esp+0x138] [ebp+0x10]
  int v26; // [esp+0x13C] [ebp+0x14]
  int v27; // [esp+0x140] [ebp+0x18]
  int v28; // [esp+0x144] [ebp+0x1C]
  const char *v29; // [esp+0x148] [ebp+0x20]
  int parent; // [esp+0x14C] [ebp+0x24]

  v2 = (UIFrameWnd *)((char *)this + 76);
  this->m_pbktex = v23;
  *((_DWORD *)this + 18) = v24;
  *((_DWORD *)this + 19) = v25;
  *((_DWORD *)this + 20) = v26;
  *((_DWORD *)this + 21) = v27;
  *((_DWORD *)this + 22) = v28;
  v3 = *((_DWORD *)this + 22);
  *((_DWORD *)this + 23) = *((_DWORD *)this + 21) - *((_DWORD *)this + 19);
  *((_DWORD *)this + 24) = v3 - *((_DWORD *)this + 20);
  *((_DWORD *)this + 25) = (int)v23 / 256;
  *((_DWORD *)this + 26) = v24 / 256;
  if ( (int)v23 % 256 > 0 )
    *((_DWORD *)this + 25) = (int)v23 / 256 + 1;
  if ( v24 % 256 > 0 )
    *((_DWORD *)this + 26) = v24 / 256 + 1;
  v4 = *((_DWORD *)this + 25) * *((_DWORD *)this + 26);
  *((_DWORD *)this + 27) = v4;
  v5 = (char *)operator new(80 * v4);
  v6 = 0;
  if ( v5 )
  {
    if ( v4 - 1 >= 0 )
    {
      v7 = v5 + 48;
      v8 = v4;
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
  *((_DWORD *)this + 28) = v5;
  memset(Buffer, 0, sizeof(Buffer));
  v19 = 0;
  v20 = 0;
  v9 = *((_DWORD *)this + 27);
  v21 = 0;
  v16 = 0;
  if ( v9 > 0 )
  {
    do
    {
      v10 = 80 * v6;
      v11 = *(gbRefObject **)(80 * v6 + *((_DWORD *)this + 28) + 44);
      if ( v11 )
        ((gbRefObject *)v11)->Release();
      sprintf(Buffer, "%s%d.tga", v29, v6);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 44) = (*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(
                                                         gfxMgr,
                                                         Buffer);
      v12 = *(gbTexture **)(v10 + *((_DWORD *)this + 28) + 44);
      if ( v12 )
        ((gbTexture *)v12)->LoadTexture(1);
      if ( v6 )
      {
        if ( v6 / *((_DWORD *)this + 25) <= v16 )
        {
          *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 8) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) - 72);
          *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 4) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) - 76) + 256;
        }
        else
        {
          *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 8) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) - 72) + 256;
// [VFTABLE] *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 4) = v2->__vftable;
          ++v16;
        }
      }
      else
      {
        *(_DWORD *)(*((_DWORD *)this + 28) + 8) = *((_DWORD *)this + 20);
// [VFTABLE] *(_DWORD *)(*((_DWORD *)this + 28) + 4) = v2->__vftable;
      }
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 12) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 4) + 256;
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 16) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 8) + 256;
      v13 = (_DWORD *)(v10 + *((_DWORD *)this + 28));
      v14 = v13 + 1;
      v13 += 5;
      *v13 = *v14;
      v13[1] = v14[1];
      v13[2] = v14[2];
      v13[3] = v14[3];
      *(float *)(v10 + *((_DWORD *)this + 28) + 40) = (float)*(int *)(v10 + *((_DWORD *)this + 28) + 8);
      *(float *)(v10 + *((_DWORD *)this + 28) + 36) = (float)*(int *)(v10 + *((_DWORD *)this + 28) + 4);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 48) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 4)
// [VFTABLE] - (unsigned int)v2->__vftable;
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 64) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 48);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 52) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 4)
                                                     - *((_DWORD *)this + 21);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 68) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 52);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 56) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 8)
                                                     - *((_DWORD *)this + 20);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 72) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 56);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 60) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 8)
                                                     - *((_DWORD *)this + 22);
      *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 76) = *(_DWORD *)(v10 + *((_DWORD *)this + 28) + 60);
      ++v6;
      *(_BYTE *)(*((_DWORD *)this + 28) + v10) = 0;
    }
    while ( v6 < *((_DWORD *)this + 27) );
  }
  *((_BYTE *)this + 140) = 1;
  *((_BYTE *)this + 148) = 0;
  *((_DWORD *)this + 36) = 1117782016;
  ((PalScript *)this)->Create(id, (tagRECT *)((char *)this + 76), parent);
  v21 = -1;
  return result;
}

// 0x004438F0
void UIFrameWnd::Destroy_38f0()
{
  int v2; // ebx
  int v3; // edi
  gbRefObject *v4; // ecx

  if ( *((_DWORD *)this + 28) )
  {
    v2 = 0;
    if ( *((int *)this + 27) > 0 )
    {
      v3 = 0;
      do
      {
        v4 = *(gbRefObject **)(v3 + *((_DWORD *)this + 28) + 44);
        if ( v4 )
          ((gbRefObject *)v4)->Release();
        ++v2;
        v3 += 80;
      }
      while ( v2 < *((_DWORD *)this + 27) );
    }
    operator delete(*((void **)this + 28));
    *((_DWORD *)this + 28) = 0;
  }
// [VFTABLE] ((UIWnd *)&this->__vftable)->HideAll();
}

// 0x00443950
void UIFrameWnd::Render()
{
  if ( this->m_bvisible )
  {
    ((TextureLibDataBase *)this)->CountEntries();
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  }
}

// 0x00443970
BOOL UIFrameWnd::UpdateIfVisible(int nVal, int nVal2)
{
  float v3; // edi
  int v6; // eax

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( *((_BYTE *)this + 148) )
    return 0;
  ((UISceneMap *)this)->sub_443CA0(nVal, v3);
  if ( *((_BYTE *)this + 120) )
  {
    v6 = *((_DWORD *)this + 28);
    *((float *)this + 33) = -*(float *)(v6 + 36);
    *((float *)this + 34) = -*(float *)(v6 + 40);
  }
  else
  {
    *((_DWORD *)this + 32) = 0;
    *((_DWORD *)this + 31) = 0;
  }
  ((CCBUIPanel *)this->m_pfather)->UpdateSlotPositions(nVal);
  ((TextureLibDataBase *)this)->SearchByIndex();
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00444AA0
int UIFrameWnd::sub_444AA0(void *Block, char a3)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x00444AC0
void UIFrameWnd::_UIFrameWnd_Full()
{
}

// 0x00444AD0
int UIFrameWnd::RenderAll()
{
  _PlugInfo *v1; // ebx
  gbTextureArray *v2; // edi
  int result; // eax
  int v5; // eax
  int v6; // eax
  char v7; // al
  unsigned int v8; // ebx
  int v9; // ecx
  char v10; // al
  int v11; // eax
  unsigned __int8 *v12; // eax
  LONG top; // edx
  LONG bottom; // ebp
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
  v23 = v1;
  *((_BYTE *)this + 155) = *((_BYTE *)this + 160);
  v5 = *((_DWORD *)this + 44);
  v22 = v2;
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      if ( *((_DWORD *)this + 28) )
      {
        nY[38] = *((_DWORD *)this + 28);
        nY[54] = 1;
        crt_sub_00540DC0();
      }
      if ( *((_DWORD *)this + 30) )
      {
        nY[4] = *((_DWORD *)this + 30);
        nY[20] = 1;
        crt_sub_00540DC0();
      }
    }
  }
  else
  {
    if ( *((_DWORD *)this + 28) )
    {
      nY[21] = *((_DWORD *)this + 28);
      right = (TextureLibDataBase *)this->m_rect.right;
      left = (char *)this->m_rect.left;
      nY[37] = 1;
      ((TextureLibDataBase *)right)->GetLibInfo(left);
    }
    if ( *((_DWORD *)this + 30) )
    {
      nY[55] = *((_DWORD *)this + 30);
      v20 = (TextureLibDataBase *)this->m_rect.left;
      nY[71] = 1;
      ((TextureLibDataBase *)v20)->GetLibInfo((char *)v20);
    }
  }
  v6 = *((_DWORD *)this + 25);
  if ( v6 )
  {
    v7 = *(_BYTE *)(v6 - 1);
    if ( !v7 || v7 == -1 )
      goto LABEL_27;
    v8 = *((_DWORD *)this + 26);
    if ( v8 > 0xFFFFFFFD )
// [IDA_MISID]       std::_Xlen();
    v9 = *((_DWORD *)this + 25);
    if ( v9 && (v10 = *(_BYTE *)(v9 - 1)) != 0 && v10 != -1 )
    {
      if ( !v8 )
      {
        *(_BYTE *)(v9 - 1) = v10 - 1;
        ((std *)0)->string::_Tidy();
        goto LABEL_27;
      }
    }
    else
    {
      if ( !v8 )
      {
        if ( v9 )
          ((std *)*((_DWORD *)this + 26))->string::_Eos();
        goto LABEL_27;
      }
      if ( *((_DWORD *)this + 27) >= v8 )
      {
LABEL_27:
        v11 = *((_DWORD *)this + 25);
        if ( v11 )
          *(_BYTE *)(v11 - 1) = -1;
        v12 = (unsigned __int8 *)*((_DWORD *)this + 25);
        goto LABEL_31;
      }
    }
    ((GRPinput *)((char *)this + 96))->PollInputState(*((_DWORD *)this + 26));
    goto LABEL_27;
  }
  v12 = &g_bActorFlag;
LABEL_31:
  if ( *v12 )
  {
    top = this->m_rect.top;
    bottom = this->m_rect.bottom;
    m_pbktex = this->m_pbktex;
    v16 = (char *)m_pbktex + this->m_rect.left;
    nY[2] = this->m_rect.right - (_DWORD)m_pbktex;
    nY[0] = (int)&v16[*((_DWORD *)this + 21)];
    v17 = (int)m_pbktex + top + *((_DWORD *)this + 22);
    HIBYTE(this->m_fontcolor.Color) = *((_BYTE *)this + 160);
    v18 = (unsigned __int8 *)*((_DWORD *)this + 25);
    nY[1] = v17;
    nY[3] = bottom - (_DWORD)m_pbktex;
    if ( !v18 )
      v18 = &g_bActorFlag;
    UIRenderPar(
      (int)v18,
      (int)nY,
      (int)&this->m_fontcolor,
      *((_DWORD *)this + 23),
      *((gbColorQuad **)this + 18),
      v22,
      v23);
  }
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  return result;
}

// 0x00444D30
BOOL UIFrameWnd::ProcessInput(int nVal, int nVal2)
{
  double v5; // st7
  __int64 v6; // rax
  int v7; // ecx
  char v8; // al
  __int64 v9; // rax
  int v10; // ecx
  UIWnd *m_pfather; // ecx
  UIWnd *v12; // ecx
  UIWnd *v13; // ecx
  POINT pt; // [esp+0x18] [ebp-0x8]

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( *((_BYTE *)this + 173) )
  {
    v5 = (double)*((int *)this + 40);
    if ( *((_BYTE *)this + 172) )
    {
      v6 = (__int64)(v5 + *((float *)this + 42));
      v7 = *((_DWORD *)this + 39);
      *((_DWORD *)this + 40) = v6;
      if ( (int)v6 >= v7 )
      {
        v8 = *((_BYTE *)this + 174);
        *((_DWORD *)this + 40) = v7;
        *((_BYTE *)this + 172) = 0;
        if ( v8 )
        {
          *((_BYTE *)this + 173) = 0;
          *((_DWORD *)this + 40) = v7;
          *((_BYTE *)this + 172) = 0;
          *((_BYTE *)this + 174) = 0;
        }
      }
    }
    else
    {
      v9 = (__int64)(v5 - *((float *)this + 42));
      v10 = *((_DWORD *)this + 41);
      *((_DWORD *)this + 40) = v9;
      if ( (int)v9 <= v10 )
      {
        *((_DWORD *)this + 40) = v10;
        *((_BYTE *)this + 172) = 1;
      }
    }
  }
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( PtInRect(&this->m_rect, pt) )
  {
    if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      m_pfather = this->m_pfather;
      if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1009,
// [VFTABLE]   this->m_id,
// [VFTABLE]   LOWORD(pt.x) | (LOWORD(pt.y) << 16));
    }
    if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v12 = this->m_pfather;
      if ( v12 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v12->__vftable->OnMessage)(
// [VFTABLE]   v12,
// [VFTABLE]   1010,
// [VFTABLE]   this->m_id,
// [VFTABLE]   LOWORD(pt.x) | (LOWORD(pt.y) << 16));
    }
    if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
    {
      v13 = this->m_pfather;
      if ( v13 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v13->__vftable->OnMessage)(v13, 1011, this->m_id, 0);
    }
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00450560
BOOL UIFrameWnd::IsOnScreen(int nVal, int nVal2)
{
  int v5; // eax
  int v6; // edi
  int v7; // ecx
  int v8; // kr00_4
  int v9; // eax
  float v10; // [esp+0xC] [ebp-0x14] BYREF
  float v11; // [esp+0x10] [ebp-0x10] BYREF
  struct gbVec3D v12; // [esp+0x14] [ebp-0xC] BYREF

  if ( !this->m_bvisible )
    return 0;
  v5 = *((_DWORD *)this + 20);
  if ( v5 )
  {
    v12 = *(gbVec3D *)(v5 + 160);
    v12.y = v12.y + 80.0;
    ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->PointWorldToScr(&v12, &v10, &v11);
    v6 = (__int64)((v10 + 1.0) * (double)g_DrvInfo.width * 0.5);
    v7 = (__int64)((1.0 - v11) * (double)g_DrvInfo.height * 0.5);
    v8 = *((_DWORD *)this + 21);
    this->m_rect.right = v6 + v8 / 2;
    v9 = *((_DWORD *)this + 22);
    this->m_rect.left = v6 - v8 / 2;
    v9 /= 2;
    this->m_rect.top = v7 - v9;
    this->m_rect.bottom = v7 + v9;
  }
  return this->Update_bbc0(nVal, nVal2);
}

// 0x0045A220
int UIFrameWnd::OnPaintUpdate()
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v17; // edi
  CScreenMode *v18; // eax
  CScreenMode *v19; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // [esp+0xC] [ebp+0x4]

  switch ( v22 )
  {
    case 0:
      result = this->OnMessage(1000, 1, 0);
      v3 = *((_DWORD *)this + 815);
      if ( v3 )
        result = (*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v3 + 24))(1000, 0, 0);
      goto LABEL_4;
    case 1:
      result = this->OnMessage(1000, 0, 0);
      v5 = *((_DWORD *)this + 815);
      if ( v5 )
        result = (*(int ( **)(int, int, _DWORD))(*(_DWORD *)v5 + 24))(1000, 1, 0);
LABEL_4:
      v4 = *((_DWORD *)this + 816);
      if ( v4 )
        result = (*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(1000, 0, 0);
      goto LABEL_12;
    case 2:
      result = this->OnMessage(1000, 0, 0);
      v6 = *((_DWORD *)this + 815);
      if ( v6 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v6 + 24))(v6, 1000, 0, 0);
      v7 = *((_DWORD *)this + 816);
      if ( v7 )
        result = (*(int ( **)(int, int, _DWORD))(*(_DWORD *)v7 + 24))(1000, 1, 0);
LABEL_12:
      v8 = *((_DWORD *)this + 817);
      if ( v8 )
        goto LABEL_38;
      goto LABEL_39;
    case 3:
      result = this->OnMessage(1000, 0, 0);
      v9 = *((_DWORD *)this + 815);
      if ( v9 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1000, 0, 0);
      v10 = *((_DWORD *)this + 816);
      if ( v10 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1000, 0, 0);
      v11 = *((_DWORD *)this + 817);
      if ( !v11 )
        goto LABEL_39;
      result = (*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 1, 0);
      *((_DWORD *)this + 814) = v22;
      return result;
    case 4:
      result = this->OnMessage(1000, 0, 0);
      v12 = *((_DWORD *)this + 815);
      if ( v12 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 0, 0);
      v13 = *((_DWORD *)this + 816);
      if ( v13 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v13 + 24))(v13, 1000, 0, 0);
      v14 = *((_DWORD *)this + 817);
      if ( v14 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v14 + 24))(v14, 1000, 0, 0);
      if ( (g_dwGameFlags & 4) == 0 )
        goto LABEL_39;
      Instance = CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
      v17 = AudioManager;
      if ( AudioManager )
      {
        ((gbAudioManager *)AudioManager)->StopSoundStream(1);
        ((gbAudioManager *)v17)->StopSoundStream(2);
      }
      if ( CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v18 = CScreenMode::GetInstance();
        ((CScreenMode *)v18)->AudioFadeOut();
      }
      else
      {
        v19 = CScreenMode::GetInstance();
        ((CScreenMode *)v19)->AudioStopAll();
      }
      *((_DWORD *)this + 814) = v22;
      return result;
    case 5:
      result = this->OnMessage(1000, 0, 0);
      v20 = *((_DWORD *)this + 815);
      if ( v20 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v20 + 24))(v20, 1000, 0, 0);
      v21 = *((_DWORD *)this + 816);
      if ( v21 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v21 + 24))(v21, 1000, 0, 0);
      v8 = *((_DWORD *)this + 817);
      if ( v8 )
LABEL_38:
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1000, 0, 0);
      goto LABEL_39;
    default:
LABEL_39:
      *((_DWORD *)this + 814) = v22;
      return result;
  }
}

// 0x00478880
BOOL UIFrameWnd::ProcessTimer(BOOL bEnable, BOOL bReset, int nInterval, int nParam)
{
  BOOL result; // eax
  void *vftable; // ebp
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
  char *v33; // ecx
  char *v34; // ecx
  char *v35; // edx
  char *bottom; // ecx
  char *v37; // edx
  int Color; // ecx
  int v39; // ecx
  int v40; // ecx
  LONG left; // ecx
  LONG v42; // ecx
  LONG v43; // ecx
  int v44; // ecx
  int v45; // ecx
  int v46; // ecx
  char *m_id; // ecx
  char *v48; // ecx
  int v49; // [esp+0x18] [ebp+0x14]
  char *v50; // [esp+0x1C] [ebp+0x18]
  LONG v51; // [esp+0x20] [ebp+0x1C]
  void *a2; // [esp+0x24] [ebp+0x20]

  LOBYTE(result) = bEnable;
  if ( bEnable )
  {
// [VFTABLE] vftable = this->__vftable;
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
    if ( v10 <= (unsigned int)vftable )
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
      m_id = (char *)this->m_id;
      if ( (int)v50 <= (int)m_id )
      {
        if ( v11 )
        {
          v48 = &m_id[-nInterval];
          this->m_id = v48;
          if ( (int)v48 <= (int)v50 )
            this->m_id = (void *)this->m_rect.bottom;
        }
      }
      else if ( v11 )
      {
        this->m_id = &m_id[nInterval];
        if ( (int)&m_id[nInterval] >= (int)v50 )
        {
          this->m_id = (void *)this->m_rect.bottom;
          return sub_445FA0(a2);
        }
      }
      return sub_445FA0(a2);
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
        v33 = (char *)this->m_id;
        if ( (int)v50 <= (int)v33 )
        {
          v34 = &v33[-nInterval];
          this->m_id = v34;
          if ( (int)v34 <= (int)v50 )
            goto LABEL_51;
        }
        else
        {
          this->m_id = &v33[nInterval];
          if ( (int)&v33[nInterval] >= (int)v50 )
          {
LABEL_51:
            this->m_id = v50;
            HIBYTE(this->m_childs.m_pData) = 1;
            return sub_445FA0(a2);
          }
        }
      }
      return sub_445FA0(a2);
    }
    if ( v11 )
    {
      v35 = (char *)this->m_id;
      bottom = (char *)this->m_rect.bottom;
      if ( (int)v35 < (int)bottom )
      {
        this->m_id = &v35[nInterval];
        if ( (int)&v35[nInterval] >= (int)bottom )
          goto LABEL_57;
      }
      else
      {
        v37 = &v35[-nInterval];
        this->m_id = v37;
        if ( (int)v37 <= (int)bottom )
        {
LABEL_57:
          this->m_id = bottom;
          HIBYTE(this->m_childs.m_pData) = 0;
          return sub_445FA0(a2);
        }
      }
    }
    return sub_445FA0(a2);
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
  fProbb = (double)fProba * 10.24;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  return (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)fProbb;
}
