#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/UIWnd.h"

// Unnamed globals (extern)
extern unsigned char byte_56A634;
extern void *off_56ADD0;

// 0x004422E0
UIFrameWnd::UIFrameWnd()
{
  char v2; // [esp+7h] [ebp-1h]

  ((UIWnd *)&this->_base)->UIWnd();
  *((_BYTE *)this + 96) = v2;
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 26) = 0;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 30) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 34) = 0;
  *((_DWORD *)this + 21) = 0;
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 19) = 1065353216;
  *((_DWORD *)this + 20) = 1065353216;
  this->_base._vftable = (void **)&off_56ADD0;
  this->m_pbktex = (gbTexture *)8;
  *((_DWORD *)this + 23) = 1;
  *((_BYTE *)this + 140) = 1;
  *((_DWORD *)this + 36) = 276;
  *((_DWORD *)this + 37) = -1;
}

// 0x00442390
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIFrameWnd::_UIFrameWnd()
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al

  this->_base._vftable = (void **)&off_56ADD0;
  ((UIFrameWnd *)this)->OnMessage();
  v2 = *((_DWORD *)this + 25);
  if ( v2 )
  {
    v3 = (_BYTE *)(v2 - 1);
    v4 = *(_BYTE *)(v2 - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      * v3 = (*)v4 - 1;
  }
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 26) = 0;
  *((_DWORD *)this + 27) = 0;
  ((UIWnd *)&this->_base)->_UIWnd();
}

// 0x00442420
void UIFrameWnd::OnMessage()
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *v5; // ecx

  v2 = (gbRefObject *)*((_DWORD *)this + 28);
  if ( v2 )
  {
    v2->Release();
    *((_DWORD *)this + 28) = 0;
  }
  v3 = (gbRefObject *)*((_DWORD *)this + 32);
  if ( v3 )
  {
    v3->Release();
    *((_DWORD *)this + 32) = 0;
  }
  v4 = (gbRefObject *)*((_DWORD *)this + 34);
  if ( v4 )
  {
    v4->Release();
    *((_DWORD *)this + 34) = 0;
  }
  v5 = (gbRefObject *)*((_DWORD *)this + 30);
  if ( v5 )
  {
    v5->Release();
    *((_DWORD *)this + 30) = 0;
  }
  *((_DWORD *)this + 37) = (UIFrameWnd *)-1;
}

// 0x00442890
int UIFrameWnd::Render()
{
  int result; // eax
  int m_rect_left; // ecx
  int v4; // eax
  double v5; // st7
  int m_rect_top; // ecx
  double v7; // st7
  double v8; // st6
  __int64 v9; // rax
  double v10; // st7
  int v11; // ecx
  struct gbTextureArray *v12; // eax
  int v13; // eax
  struct gbTextureArray *v14; // eax
  int v15; // ecx
  int v16; // edx
  int v17; // edx
  struct gbTextureArray *v18; // eax
  int v19; // edx
  int v20; // ecx
  gbTexture *m_pbktex; // edx
  int v22; // edi
  int v23; // eax
  const char *v24; // eax
  int v25; // [esp-1Ch] [ebp-A0h]
  int v26; // [esp-18h] [ebp-9Ch]
  gbColorQuad v27[2]; // [esp-Ch] [ebp-90h] BYREF
  int v28; // [esp+10h] [ebp-74h]
  int m_rect_right; // [esp+14h] [ebp-70h]
  int v30; // [esp+18h] [ebp-6Ch]
  int m_rect_bottom; // [esp+1Ch] [ebp-68h]
  int v32; // [esp+20h] [ebp-64h] BYREF
  int v33; // [esp+24h] [ebp-60h]
  int v34; // [esp+28h] [ebp-5Ch]
  int v35; // [esp+2Ch] [ebp-58h]
  int v36; // [esp+30h] [ebp-54h] BYREF
  int v37; // [esp+34h] [ebp-50h]
  int v38; // [esp+38h] [ebp-4Ch]
  int v39; // [esp+3Ch] [ebp-48h]
  struct gbTextureArray v40; // [esp+40h] [ebp-44h] BYREF

  result = this->_base.m_bvisible;
  if ( result )
  {
    m_rect_left = this->_base.m_rect_left;
    m_rect_right = this->_base.m_rect_right;
    v4 = m_rect_left + m_rect_right;
    v28 = m_rect_left;
    v5 = 1.0 - *((float *)this + 19);
    m_rect_top = this->_base.m_rect_top;
    v32 = v4 / 2;
    v7 = v5 * (double)(v4 / 2);
    m_rect_bottom = this->_base.m_rect_bottom;
    v30 = m_rect_top;
    v8 = (double)v28 * *((float *)this + 19);
    v33 = (m_rect_top + m_rect_bottom) / 2;
    v36 = (__int64)(v8 + v7);
    v9 = (__int64)((double)m_rect_right * *((float *)this + 19) + v7);
    v10 = (1.0 - *((float *)this + 20)) * (double)v33;
    v38 = v9;
    v37 = (__int64)((double)m_rect_top * *((float *)this + 20) + v10);
    v39 = (__int64)((double)m_rect_bottom * *((float *)this + 20) + v10);
    if ( *((_DWORD *)this + 28) )
    {
      v11 = *((_DWORD *)this + 36);
      v27[0].Color = *((_DWORD *)this + 29);
      *(_DWORD *)&v27[0].Blue = v11;
      v27[0].ColorQuadFmt = v11;
      v27->gbColorQuad((struct gbColorQuad *)&this->_base.m_wndcolor);
      v12 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*((struct gbTexture **)this + 28));
      ((_TextureLib_Data *)&this->_base.m_rect_left)->_CheckItem(&v36, v12, v27[0].ColorQuadFmt, *(unsigned int *)&v27[0].Blue, (float *)v27[0].Color);
    }
    if ( !this->_base.m_benable && *((_DWORD *)this + 32) )
    {
      v13 = *((_DWORD *)this + 36);
      v27[0].Color = *((_DWORD *)this + 33);
      *(_DWORD *)&v27[0].Blue = v13;
      v27[0].ColorQuadFmt = m_rect_top;
      v27->gbColorQuad((struct gbColorQuad *)&this->_base.m_wndcolor);
      v14 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*((struct gbTexture **)this + 32));
      ((_TextureLib_Data *)&this->_base.m_rect_left)->_CheckItem(&v36, v14, v27[0].ColorQuadFmt, *(unsigned int *)&v27[0].Blue, (float *)v27[0].Color);
    }
    if ( *((_DWORD *)this + 34) )
    {
      v15 = this->_base.m_rect_bottom;
      v40.pTexPt[0] = (gbTexture *)*((_DWORD *)this + 34);
      v27[0].Color = 0;
      *(_DWORD *)&v27[0].Blue = &v40;
      v16 = this->_base.m_rect_right;
      v27[0].ColorQuadFmt = (int)&this->_base.m_wndcolor;
      v26 = this->_base.m_rect_top;
      v25 = this->_base.m_rect_left;
      v40.nTex = 1;
      v25->GetTextureInfo(v26, v16, v15, (int *)&this->_base.m_wndcolor, &v40, 0);
    }
    if ( *((_DWORD *)this + 30) )
    {
      v17 = *((_DWORD *)this + 36);
      v27[0].Color = 0;
      *(_DWORD *)&v27[0].Blue = v17;
      v27[0].ColorQuadFmt = m_rect_top;
      v27->gbColorQuad((struct gbColorQuad *)&this->_base.m_wndcolor);
      v18 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*((struct gbTexture **)this + 30));
      ((_TextureLib_Data *)&this->_base.m_rect_left)->_CheckItem(&v36, v18, v27[0].ColorQuadFmt, *(unsigned int *)&v27[0].Blue, (float *)v27[0].Color);
    }
    if ( *((_DWORD *)this + 26) )
    {
      v19 = *((_DWORD *)this + 22);
      v32 = v36;
      v20 = v19 + v37;
      m_pbktex = (gbTexture *)this->m_pbktex;
      v22 = *((_DWORD *)this + 37);
      v23 = (int)&m_pbktex->_base[v36 + *((_DWORD *)this + 21)];
      v32 = v23;
      if ( v22 == -1 )
        v34 = v38 - (_DWORD)m_pbktex;
      else
        v34 = v23 + v22;
      v24 = (const char *)*((_DWORD *)this + 25);
      v33 = (int)&m_pbktex->_base[v20];
      v35 = v39 - (_DWORD)m_pbktex;
      if ( !v24 )
        v24 = byte_56A634;
      UIRenderPar(v24, &v32, &this->_base.m_fontcolor, *((_DWORD *)this + 23), *((_DWORD *)this + 18));
    }
    return ((UIWnd *)&this->_base)->GetID();
  }
  return result;
}

// 0x00442AD0
BOOL UIFrameWnd::Update(int a2, int a3)
{
  UIWnd *v5; // ecx
  UIWnd *v6; // ecx
  UIWnd *v7; // ecx
  UIWnd *v8; // ecx
  UIWnd *m_pfather; // ecx
  POINT pt; // [esp+4h] [ebp-8h] BYREF

  if ( !this->_base.m_bvisible )
    return 0;
  if ( !this->_base.m_benable )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  if ( !PtInRect((const RECT *)&this->_base.m_rect_left, pt) )
  {
    if ( !*((_BYTE *)this + 140) )
    {
      m_pfather = (UIWnd *)this->_base.m_pfather;
      *((_BYTE *)this + 140) = 1;
      if ( m_pfather )
        (*((void (**)(UIWnd *, int, unsigned int, _DWORD))m_pfather->_vftable + 6))(
          m_pfather,
          1003,
          this->_base.m_id,
          0);
    }
    return ((UIWnd *)&this->_base)->HitTest(a2, a3);
  }
  if ( g_Input.KeyInfo[0].PressTime != 1 || (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v6 = (UIWnd *)this->_base.m_pfather;
      if ( v6 )
      {
        (*((void (**)(UIWnd *, int, unsigned int, int))v6->_vftable + 6))(
          v6,
          1010,
          this->_base.m_id,
          LOWORD(pt.x) | (LOWORD(pt.y) << 16));
        *((_BYTE *)this + 140) = 0;
        return ((UIWnd *)&this->_base)->HitTest(a2, a3);
      }
    }
    else if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
    {
      v7 = (UIWnd *)this->_base.m_pfather;
      if ( v7 )
      {
        (*((void (**)(UIWnd *, int, unsigned int, _DWORD))v7->_vftable + 6))(v7, 1011, this->_base.m_id, 0);
        *((_BYTE *)this + 140) = 0;
        return ((UIWnd *)&this->_base)->HitTest(a2, a3);
      }
    }
    else
    {
      v8 = (UIWnd *)this->_base.m_pfather;
      if ( v8 )
        (*((void (**)(UIWnd *, int, unsigned int, _DWORD))v8->_vftable + 6))(v8, 1002, this->_base.m_id, 0);
    }
LABEL_20:
    *((_BYTE *)this + 140) = 0;
    return ((UIWnd *)&this->_base)->HitTest(a2, a3);
  }
  v5 = (UIWnd *)this->_base.m_pfather;
  if ( !v5 )
    goto LABEL_20;
  (*((void (**)(UIWnd *, int, unsigned int, int))v5->_vftable + 6))(
    v5,
    1009,
    this->_base.m_id,
    LOWORD(pt.x) | (LOWORD(pt.y) << 16));
  *((_BYTE *)this + 140) = 0;
  return ((UIWnd *)&this->_base)->HitTest(a2, a3);
}

// 0x00442C60
int UIFrameWnd::SetPosition(int a2, int a3)
{
  *((_DWORD *)this + 21) = a2;
  *((_DWORD *)this + 22) = a3;
  return a2;
}
