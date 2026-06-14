#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITextArea.h"

// Forward declarations for unnamed functions
int sub_445AA0(void); // from annotations
void * sub_445EA0(void); // from annotations
int sub_445F60(unsigned int a2); // from annotations

BOOL __stdcall MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint); // from annotations

// 0x00444F60
int UITextArea::InitAfterClear()
{
  char v3; // [esp+0xB] [ebp-0x11]

  sub_445AA0();
  this->m_buf[4] = v3;
  *(_DWORD *)&this->m_buf[8] = 0;
  *(_DWORD *)&this->m_bInvalidate = 0;
  *((_DWORD *)&this->m_bInvalidate + 1) = 0;
  sub_445EA0();
  *((_DWORD *)this + 44) = 0;
  BYTE2(this->m_fontcolor.Color) = -1;
  BYTE1(this->m_fontcolor.Color) = -1;
  *((_DWORD *)this + 47) = 0;
  *((_DWORD *)this + 43) = 2;
  LOBYTE(this->m_fontcolor.Color) = -6;
  *(_DWORD *)this->m_buf = 1056964608;
  return (int)this;
}

// 0x00444FF0
UITextArea * UITextArea::_sdtor_13(UITextArea *Block, char a2)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00445170
int UITextArea::ProcessInput()
{
  int v3; // eax
  double v4; // st7
  LONG v5; // edi
  int v6; // ecx
  long double v7; // st7
  long double v8; // st6
  double top; // st5
  double v10; // st7
  int v11; // ecx
  LONG v12; // [esp+0x4] [ebp-0x24]
  LONG v13; // [esp+0x4] [ebp-0x24]
  LONG v14; // [esp+0x4] [ebp-0x24]
  LONG left; // [esp+0x4] [ebp-0x24]
  LONG v16; // [esp+0x8] [ebp-0x20]
  LONG v17; // [esp+0x8] [ebp-0x20]
  LONG v18; // [esp+0x8] [ebp-0x20]
  LONG bottom; // [esp+0x8] [ebp-0x20]
  LONG v20; // [esp+0xC] [ebp-0x1C]
  LONG right; // [esp+0xC] [ebp-0x1C]
  LONG v22; // [esp+0x10] [ebp-0x18]
  LONG v23; // [esp+0x10] [ebp-0x18]
  float v24; // [esp+0x14] [ebp-0x14]
  float v25; // [esp+0x14] [ebp-0x14]
  int a2; // [esp+0x2C] [ebp+0x4]
  int a3; // [esp+0x30] [ebp+0x8]

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  v3 = *((_DWORD *)this + 43);
  if ( !v3 )
  {
    v10 = *(float *)&a2 + *((float *)this + 44);
    *((float *)this + 44) = v10;
    v25 = v10 / *(float *)this->m_buf;
    if ( v10 >= *(float *)this->m_buf )
    {
      *((_DWORD *)this + 43) = 2;
      *((_DWORD *)this + 44) = 0;
      *((_DWORD *)&this->m_bInvalidate + 2) = this->m_rect.left;
      *((_DWORD *)&this->m_bInvalidate + 3) = this->m_rect.top;
      *((_DWORD *)&this->m_bInvalidate + 4) = this->m_rect.right;
      *((_DWORD *)&this->m_bInvalidate + 5) = this->m_rect.bottom;
      return ((UIListBox *)this)->Update(a2, a3);
    }
    if ( *((_DWORD *)this + 47) )
    {
      left = this->m_rect.left;
      *((_DWORD *)&this->m_bInvalidate + 2) = left;
      bottom = this->m_rect.bottom;
      *((_DWORD *)&this->m_bInvalidate + 5) = bottom;
      v7 = (1.0 - cos(v25 * 3.1415927)) * 0.5;
      v8 = (1.0 - v7) * (double)bottom;
      *((_DWORD *)&this->m_bInvalidate + 4) = (__int64)((1.0 - v7) * (double)left + (double)this->m_rect.right * v7);
      top = (double)this->m_rect.top;
    }
    else
    {
      right = this->m_rect.right;
      v14 = this->m_rect.left;
      v23 = this->m_rect.top;
      v18 = this->m_rect.bottom;
      v11 = (v14 + right) / 2;
      v7 = (1.0 - cos(v25 * 3.1415927)) * 0.5;
      *((_DWORD *)&this->m_bInvalidate + 2) = (__int64)((1.0 - v7) * (double)(v11 - 16) + (double)v14 * v7);
      *((_DWORD *)&this->m_bInvalidate + 5) = (__int64)((1.0 - v7) * (double)((v23 + v18) / 2 + 16) + (double)v18 * v7);
      v8 = (1.0 - v7) * (double)((v23 + v18) / 2 - 16);
      *((_DWORD *)&this->m_bInvalidate + 4) = (__int64)((1.0 - v7) * (double)(v11 + 16) + (double)right * v7);
      top = (double)v23;
    }
    goto LABEL_17;
  }
  if ( v3 == 1 )
  {
    v4 = *(float *)&a2 + *((float *)this + 44);
    *((float *)this + 44) = v4;
    v24 = v4 / *(float *)this->m_buf;
    if ( v4 >= *(float *)this->m_buf )
    {
      *((_DWORD *)this + 43) = 2;
      this->m_bvisible = 0;
      v5 = this->m_rect.left;
      *((_DWORD *)this + 44) = 0;
      *((_DWORD *)&this->m_bInvalidate + 2) = v5;
      *((_DWORD *)&this->m_bInvalidate + 3) = this->m_rect.top;
      *((_DWORD *)&this->m_bInvalidate + 4) = this->m_rect.right;
      *((_DWORD *)&this->m_bInvalidate + 5) = this->m_rect.bottom;
      return ((UIListBox *)this)->Update(a2, a3);
    }
    if ( *((_DWORD *)this + 47) )
    {
      v13 = this->m_rect.left;
      *((_DWORD *)&this->m_bInvalidate + 2) = v13;
      v17 = this->m_rect.bottom;
      *((_DWORD *)&this->m_bInvalidate + 5) = v17;
      v7 = (1.0 - cos(v24 * 3.1415927)) * 0.5;
      v8 = (1.0 - v7) * (double)this->m_rect.top;
      *((_DWORD *)&this->m_bInvalidate + 4) = (__int64)((1.0 - v7) * (double)this->m_rect.right + (double)v13 * v7);
      top = (double)v17;
    }
    else
    {
      v20 = this->m_rect.right;
      v12 = this->m_rect.left;
      v22 = this->m_rect.top;
      v16 = this->m_rect.bottom;
      v6 = (v12 + v20) / 2;
      v7 = (1.0 - cos(v24 * 3.1415927)) * 0.5;
      *((_DWORD *)&this->m_bInvalidate + 2) = (__int64)((1.0 - v7) * (double)v12 + (double)(v6 - 16) * v7);
      *((_DWORD *)&this->m_bInvalidate + 5) = (__int64)((1.0 - v7) * (double)v16 + (double)((v22 + v16) / 2 + 16) * v7);
      v8 = (1.0 - v7) * (double)v22;
      *((_DWORD *)&this->m_bInvalidate + 4) = (__int64)((1.0 - v7) * (double)v20 + (double)(v6 + 16) * v7);
      top = (double)((v22 + v16) / 2 - 16);
    }
LABEL_17:
    *((_DWORD *)&this->m_bInvalidate + 3) = (__int64)(v8 + top * v7);
  }
  return ((UIListBox *)this)->Update(a2, a3);
}

// 0x00445500
void UITextArea::Render()
{
  LONG v2; // ebp
  int v3; // ebx
  int v4; // edi
  int v5; // ecx
  int v6; // kr04_4
  LONG v7; // eax
  LONG v8; // ecx
  LONG v9; // eax
  int v10; // edx
  LONG v11; // eax
  LONG v12; // eax
  LONG v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // ecx
  LONG v17; // eax
  LONG v18; // ecx
  LONG v19; // edx
  LONG v20; // ebp
  unsigned __int8 *v21; // eax
  gbTextureArray *v22; // [esp+0x0] [ebp-0x14]
  RECT pRect; // [esp+0x4] [ebp-0x10] BYREF

  if ( this->m_bvisible )
  {
    v2 = *((_DWORD *)&this->m_bInvalidate + 2);
    v3 = *((_DWORD *)this + 46);
    v4 = v3;
    if ( v3 >= (*((_DWORD *)&this->m_bInvalidate + 4) - v2) / 2 )
      v4 = (*((_DWORD *)&this->m_bInvalidate + 4) - v2) / 2;
    v5 = *((_DWORD *)&this->m_bInvalidate + 3);
    v6 = *((_DWORD *)&this->m_bInvalidate + 5) - v5;
    if ( v3 >= v6 / 2 )
      v3 = v6 / 2;
    pRect.top = *((_DWORD *)&this->m_bInvalidate + 3);
    pRect.left = v2;
    pRect.right = v4 + v2;
    pRect.bottom = v3 + v5;
    this->UpdateChildLayout(&pRect, 0);
    v7 = *((_DWORD *)&this->m_bInvalidate + 5);
    pRect.left = *((_DWORD *)&this->m_bInvalidate + 2);
    pRect.right = v4 + pRect.left;
    pRect.top = v7 - v3;
    pRect.bottom = v7;
    this->UpdateChildLayout(&pRect, 1u);
    v8 = *((_DWORD *)&this->m_bInvalidate + 5);
    pRect.left = *((_DWORD *)&this->m_bInvalidate + 4) - v4;
    pRect.right = v4 + pRect.left;
    pRect.bottom = v8;
    pRect.top = v8 - v3;
    this->UpdateChildLayout(&pRect, 2u);
    v9 = *((_DWORD *)&this->m_bInvalidate + 4);
    pRect.top = *((_DWORD *)&this->m_bInvalidate + 3);
    pRect.bottom = v3 + pRect.top;
    pRect.left = v9 - v4;
    pRect.right = v9;
    this->UpdateChildLayout(&pRect, 3u);
    v10 = *((_DWORD *)&this->m_bInvalidate + 3);
    pRect.left = *((_DWORD *)&this->m_bInvalidate + 2);
    pRect.right = v4 + pRect.left;
    v11 = *((_DWORD *)&this->m_bInvalidate + 5) - v3;
    pRect.top = v3 + v10;
    pRect.bottom = v11;
    this->UpdateChildLayout(&pRect, 4u);
    v12 = *((_DWORD *)&this->m_bInvalidate + 5);
    pRect.left = v4 + *((_DWORD *)&this->m_bInvalidate + 2);
    v13 = *((_DWORD *)&this->m_bInvalidate + 4) - v4;
    pRect.top = v12 - v3;
    pRect.right = v13;
    pRect.bottom = v12;
    this->UpdateChildLayout(&pRect, 5u);
    v14 = *((_DWORD *)&this->m_bInvalidate + 3);
    pRect.right = *((_DWORD *)&this->m_bInvalidate + 4);
    v15 = *((_DWORD *)&this->m_bInvalidate + 5);
    pRect.left = pRect.right - v4;
    pRect.top = v3 + v14;
    pRect.bottom = v15 - v3;
    this->UpdateChildLayout(&pRect, 6u);
    v16 = *((_DWORD *)&this->m_bInvalidate + 4);
    v17 = *((_DWORD *)&this->m_bInvalidate + 3);
    pRect.left = v4 + *((_DWORD *)&this->m_bInvalidate + 2);
    pRect.top = v17;
    pRect.right = v16 - v4;
    pRect.bottom = v3 + v17;
    this->UpdateChildLayout(&pRect, 7u);
    v18 = *((_DWORD *)&this->m_bInvalidate + 4) - v4;
    v19 = v3 + *((_DWORD *)&this->m_bInvalidate + 3);
    v20 = *((_DWORD *)&this->m_bInvalidate + 5) - v3;
    pRect.left = v4 + *((_DWORD *)&this->m_bInvalidate + 2);
    pRect.top = v19;
    pRect.right = v18;
    pRect.bottom = v20;
    if ( v18 > pRect.left && v20 > v19 )
      this->UpdateChildLayout(&pRect, 8u);
    if ( *((_DWORD *)this + 43) == 2 && *(_DWORD *)&this->m_bInvalidate )
    {
      v21 = *(unsigned __int8 **)&this->m_buf[8];
      if ( !v21 )
        v21 = &g_bActorFlag;
      UIRenderPar(
        (int)v21,
        (int)&this->m_rect,
        (int)&this->m_fontcolor,
        *((_DWORD *)this + 45),
        (gbColorQuad *)1,
        v22,
        (_PlugInfo *)pRect.left);
    }
  }
}

// 0x00445720
void UITextArea::ShowWindow()
{
  int v1; // eax
  int nFlags; // [esp+0x4] [ebp+0x4]

  if ( nFlags )
  {
    *((_DWORD *)this + 43) = 0;
    *((_DWORD *)this + 44) = 0;
    ((PalScript *)this)->ShowWindow(nFlags);
  }
  else
  {
    v1 = *((_DWORD *)this + 47);
    *((_DWORD *)this + 43) = 1;
    if ( v1 )
      this->m_bvisible = 0;
  }
}

// 0x00445760
void UITextArea::UpdateChildLayout(RECT *pRect, unsigned int nFlags)
{
  int v4; // eax
  unsigned int Color; // edx
  gbDynVertBuf *DynVertBuf; // edi
  int v7; // [esp+0xC] [ebp-0x74]
  int v8; // [esp+0x10] [ebp-0x70]
  struct gbUIQuad v9; // [esp+0x14] [ebp-0x6C] BYREF
  struct gbTextureArray v10; // [esp+0x3C] [ebp-0x44] BYREF

  v9.color = -1;
  v9.z = 0.0;
  v7 = *(_DWORD *)(sub_445F60(nFlags) + 24);
  v4 = sub_445F60(nFlags);
  Color = this->m_wndcolor.Color;
  v8 = *(_DWORD *)(v4 + 28);
  v9.su = 0.0;
  v9.sv = 0.0;
  v9.color = Color;
  v9.eu = 1.0 - 0.5 / (double)v7;
  v9.ev = 1.0 - 0.5 / (double)v8;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  v9.sx = (float)pRect->left;
  v9.ey = (float)pRect->top;
  v9.ex = (float)pRect->right;
  v9.sy = (float)pRect->bottom;
  v10.pTexPt[0] = (gbTexture *)sub_445F60(nFlags);
  v10.nTex = 1;
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v9, 1, g_pRenderEffect_189504C, &v10);
}

// 0x00445920
int UITextArea::Destroy()
{
  HWND v2; // [esp+0x4] [ebp+0x4]
  int v3; // [esp+0x8] [ebp+0x8]
  int v4; // [esp+0xC] [ebp+0xC]
  int v5; // [esp+0x10] [ebp+0x10]
  int v6; // [esp+0x14] [ebp+0x14]
  BOOL v7; // [esp+0x18] [ebp+0x18]

  return MoveWindow(v2, v3, v4, v5, v6, v7);
}

// 0x004B7AF0
void UITextArea::ReleaseAllTextures()
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject **v4; // esi
  int v5; // ebp
  void ( ***v6)(_DWORD, int); // ecx

  v2 = (gbRefObject *)*((_DWORD *)&this->m_bInvalidate + 5);
  if ( v2 )
  {
    ((gbRefObject *)v2)->Release();
    *((_DWORD *)&this->m_bInvalidate + 5) = 0;
  }
  v3 = (gbRefObject *)*((_DWORD *)this + 59);
  if ( v3 )
  {
    ((gbRefObject *)v3)->Release();
    *((_DWORD *)this + 59) = 0;
  }
  v4 = (gbRefObject **)(this + 1);
  v5 = 16;
  do
  {
    if ( *v4 )
    {
      ((gbRefObject *)*v4)->Release();
      *v4 = 0;
    }
    ++v4;
    --v5;
  }
  while ( v5 );
  v6 = (void ( ***)(_DWORD, int))*((_DWORD *)this + 60);
  if ( v6 )
  {
    (**v6)(v6, 1);
    *((_DWORD *)this + 60) = 0;
  }
}
