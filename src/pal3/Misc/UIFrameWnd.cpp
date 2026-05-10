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

  this->UIWnd();
  LOBYTE(this->m_benable) = v2;
  this->m_bfocus = 0;
  this->m_pbktex = 0;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 30) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 34) = 0;
  this->m_childs.m_nGrowBy = 0;
  this->m_bcreateok = 0;
  this->m_childs.m_pData = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 33) = 0;
  this->m_childs.m_nSize = 1065353216;
  this->m_childs.m_nMaxSize = 1065353216;
  this->m_fontcolor.ColorQuadFmt = (int)&off_56ADD0;
  this->m_pfather = (UIWnd *)8;
  this->m_bvisible = 1;
  *((_BYTE *)this + 140) = 1;
  *((_DWORD *)this + 36) = 276;
  *((_DWORD *)this + 37) = -1;
}

// 0x00442390
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIFrameWnd::_UIFrameWnd()
{
  int m_bfocus; // eax
  _BYTE *v3; // ecx
  char v4; // al

  this->m_fontcolor.ColorQuadFmt = (int)&off_56ADD0;
  ((UIFrameWnd *)this)->OnMessage();
  m_bfocus = this->m_bfocus;
  if ( m_bfocus )
  {
    v3 = (_BYTE *)(m_bfocus - 1);
    v4 = *(_BYTE *)(m_bfocus - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      * v3 = (*)v4 - 1;
  }
  this->m_bfocus = 0;
  this->m_pbktex = 0;
  *((_DWORD *)this + 27) = 0;
  this->_UIWnd();
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
  __int32 Alpha; // ecx
  __int32 v4; // eax
  double v5; // st7
  int Color; // ecx
  double v7; // st7
  double v8; // st6
  __int64 v9; // rax
  double v10; // st7
  __int32 v11; // ecx
  struct gbTextureArray *v12; // eax
  __int32 v13; // eax
  struct gbTextureArray *v14; // eax
  int v15; // ecx
  int v16; // edx
  __int32 v17; // edx
  struct gbTextureArray *v18; // eax
  int m_bcreateok; // edx
  int v20; // ecx
  UIWnd *m_pfather; // edx
  int v22; // edi
  int v23; // eax
  const char *m_bfocus; // eax
  int v25; // [esp-1Ch] [ebp-A0h]
  int v26; // [esp-18h] [ebp-9Ch]
  gbColorQuad v27; // [esp-Ch] [ebp-90h] BYREF
  int v28; // [esp+10h] [ebp-74h]
  int ColorQuadFmt; // [esp+14h] [ebp-70h]
  int v30; // [esp+18h] [ebp-6Ch]
  __int32 Blue; // [esp+1Ch] [ebp-68h]
  int v32; // [esp+20h] [ebp-64h] BYREF
  int v33; // [esp+24h] [ebp-60h]
  int v34; // [esp+28h] [ebp-5Ch]
  int v35; // [esp+2Ch] [ebp-58h]
  int v36; // [esp+30h] [ebp-54h] BYREF
  int v37; // [esp+34h] [ebp-50h]
  int v38; // [esp+38h] [ebp-4Ch]
  int v39; // [esp+3Ch] [ebp-48h]
  struct gbTextureArray v40; // [esp+40h] [ebp-44h] BYREF

  result = this->m_rect.top;
  if ( result )
  {
    Alpha = this->m_fontcolor.Alpha;
    ColorQuadFmt = this->m_wndcolor.ColorQuadFmt;
    v4 = Alpha + ColorQuadFmt;
    v28 = Alpha;
    v5 = 1.0 - *(float *)&this->m_childs.m_nSize;
    Color = this->m_fontcolor.Color;
    v32 = v4 / 2;
    v7 = v5 * (double)(v4 / 2);
    Blue = this->m_wndcolor.Blue;
    v30 = Color;
    v8 = (double)v28 * *(float *)&this->m_childs.m_nSize;
    v33 = (Color + Blue) / 2;
    v36 = (__int64)(v8 + v7);
    v9 = (__int64)((double)ColorQuadFmt * *(float *)&this->m_childs.m_nSize + v7);
    v10 = (1.0 - *(float *)&this->m_childs.m_nMaxSize) * (double)v33;
    v38 = v9;
    v37 = (__int64)((double)Color * *(float *)&this->m_childs.m_nMaxSize + v10);
    v39 = (__int64)((double)Blue * *(float *)&this->m_childs.m_nMaxSize + v10);
    if ( *((_DWORD *)this + 28) )
    {
      v11 = *((_DWORD *)this + 36);
      v27.Green = *((_DWORD *)this + 29);
      v27.Blue = v11;
      v27.ColorQuadFmt = v11;
      ((gbColorQuad *)&v27)->gbColorQuad((struct gbColorQuad *)&this->m_fontcolor.Green);
      v12 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*((struct gbTexture **)this + 28));
      ((_TextureLib_Data *)&this->m_fontcolor.Alpha)->_CheckItem(&v36, v12, v27.ColorQuadFmt, v27.Blue, (float *)v27.Green);
    }
    if ( !this->m_rect.right && *((_DWORD *)this + 32) )
    {
      v13 = *((_DWORD *)this + 36);
      v27.Green = *((_DWORD *)this + 33);
      v27.Blue = v13;
      v27.ColorQuadFmt = Color;
      ((gbColorQuad *)&v27)->gbColorQuad((struct gbColorQuad *)&this->m_fontcolor.Green);
      v14 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*((struct gbTexture **)this + 32));
      ((_TextureLib_Data *)&this->m_fontcolor.Alpha)->_CheckItem(&v36, v14, v27.ColorQuadFmt, v27.Blue, (float *)v27.Green);
    }
    if ( *((_DWORD *)this + 34) )
    {
      v15 = this->m_wndcolor.Blue;
      v40.pTexPt[0] = (gbTexture *)*((_DWORD *)this + 34);
      v27.Green = 0;
      v27.Blue = (__int32)&v40;
      v16 = this->m_wndcolor.ColorQuadFmt;
      v27.ColorQuadFmt = (int)&this->m_fontcolor.Green;
      v26 = this->m_fontcolor.Color;
      v25 = this->m_fontcolor.Alpha;
      v40.nTex = 1;
      v25->GetTextureInfo(v26, v16, v15, &this->m_fontcolor.Green, &v40, 0);
    }
    if ( *((_DWORD *)this + 30) )
    {
      v17 = *((_DWORD *)this + 36);
      v27.Green = 0;
      v27.Blue = v17;
      v27.ColorQuadFmt = Color;
      ((gbColorQuad *)&v27)->gbColorQuad((struct gbColorQuad *)&this->m_fontcolor.Green);
      v18 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*((struct gbTexture **)this + 30));
      ((_TextureLib_Data *)&this->m_fontcolor.Alpha)->_CheckItem(&v36, v18, v27.ColorQuadFmt, v27.Blue, (float *)v27.Green);
    }
    if ( this->m_pbktex )
    {
      m_bcreateok = this->m_bcreateok;
      v32 = v36;
      v20 = m_bcreateok + v37;
      m_pfather = (UIWnd *)this->m_pfather;
      v22 = *((_DWORD *)this + 37);
      v23 = (int)m_pfather + v36 + this->m_childs.m_nGrowBy;
      v32 = v23;
      if ( v22 == -1 )
        v34 = v38 - (_DWORD)m_pfather;
      else
        v34 = v23 + v22;
      m_bfocus = (const char *)this->m_bfocus;
      v33 = (int)m_pfather + v20;
      v35 = v39 - (_DWORD)m_pfather;
      if ( !m_bfocus )
        m_bfocus = byte_56A634;
      UIRenderPar(m_bfocus, &v32, &this->m_fontcolor.Blue, this->m_bvisible, (int)this->m_childs.m_pData);
    }
    return this->GetID();
  }
  return result;
}

// 0x00442AD0
BOOL UIFrameWnd::Update(int a2, int a3)
{
  __int32 v5; // ecx
  __int32 v6; // ecx
  __int32 v7; // ecx
  __int32 v8; // ecx
  __int32 Green; // ecx
  POINT pt; // [esp+4h] [ebp-8h] BYREF

  if ( !this->m_rect.top )
    return 0;
  if ( !this->m_rect.right )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  if ( !PtInRect((const RECT *)&this->m_fontcolor.Alpha, pt) )
  {
    if ( !*((_BYTE *)this + 140) )
    {
      Green = this->m_wndcolor.Green;
      *((_BYTE *)this + 140) = 1;
      if ( Green )
        (*(void (**)(__int32, int, __int32, _DWORD))(*(_DWORD *)Green + 24))(
          Green,
          1003,
          this->m_fontcolor.Red,
          0);
    }
    return this->HitTest(a2, a3);
  }
  if ( g_Input.m_shiftedKeyStates[207] != 1 || (g_Input.m_shiftedKeyStates[204] & 0xF) != 1 )
  {
    if ( g_Input.m_shiftedKeyStates[211] == 1 && (g_Input.m_shiftedKeyStates[208] & 0xF) == 1 )
    {
      v6 = this->m_wndcolor.Green;
      if ( v6 )
      {
        (*(void (**)(__int32, int, __int32, int))(*(_DWORD *)v6 + 24))(
          v6,
          1010,
          this->m_fontcolor.Red,
          LOWORD(pt.x) | (LOWORD(pt.y) << 16));
        *((_BYTE *)this + 140) = 0;
        return this->HitTest(a2, a3);
      }
    }
    else if ( g_Input.m_shiftedKeyStates[207] == 1 && (g_Input.m_shiftedKeyStates[204] & 0xF) == 2 )
    {
      v7 = this->m_wndcolor.Green;
      if ( v7 )
      {
        (*(void (**)(__int32, int, __int32, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1011, this->m_fontcolor.Red, 0);
        *((_BYTE *)this + 140) = 0;
        return this->HitTest(a2, a3);
      }
    }
    else
    {
      v8 = this->m_wndcolor.Green;
      if ( v8 )
        (*(void (**)(__int32, int, __int32, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1002, this->m_fontcolor.Red, 0);
    }
LABEL_20:
    *((_BYTE *)this + 140) = 0;
    return this->HitTest(a2, a3);
  }
  v5 = this->m_wndcolor.Green;
  if ( !v5 )
    goto LABEL_20;
  (*(void (**)(__int32, int, __int32, int))(*(_DWORD *)v5 + 24))(
    v5,
    1009,
    this->m_fontcolor.Red,
    LOWORD(pt.x) | (LOWORD(pt.y) << 16));
  *((_BYTE *)this + 140) = 0;
  return this->HitTest(a2, a3);
}

// 0x00442C60
int UIFrameWnd::SetPosition(int a2, int a3)
{
  this->m_childs.m_nGrowBy = a2;
  this->m_bcreateok = a3;
  return a2;
}
