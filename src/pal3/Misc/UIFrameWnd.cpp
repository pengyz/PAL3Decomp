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

  ((UIWnd *)this)->UIWnd();
  this->_b060 = v2;
  this->_d064 = 0;
  this->_d068 = 0;
  this->_d06C = 0;
  this->_d070 = 0;
  this->_d078 = 0;
  this->_d080 = 0;
  this->_d088 = 0;
  this->_d054 = 0;
  this->_d058 = 0;
  this->_d048 = 0;
  this->_d074 = 0;
  this->_d07C = 0;
  this->_d084 = 0;
  this->_f04C = 1.0;
  this->_f050 = 1.0;
  this->_p000 = &off_56ADD0;
  this->_d044 = 8;
  this->_d05C = 1;
  this->_b08C = 1;
  this->_d090 = 276;
  this->_d094 = -1;
}

// 0x00442390
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIFrameWnd::_UIFrameWnd()
{
  int d064; // eax
  _BYTE *v3; // ecx
  char v4; // al

  this->_p000 = &off_56ADD0;
  ((UIFrameWnd *)this)->OnMessage();
  d064 = this->_d064;
  if ( d064 )
  {
    v3 = (_BYTE *)(d064 - 1);
    v4 = *(_BYTE *)(d064 - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      * v3 = (*)v4 - 1;
  }
  this->_d064 = 0;
  this->_d068 = 0;
  this->_d06C = 0;
  ((UIWnd *)this)->_UIWnd();
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
  int d010; // ecx
  int v4; // eax
  double v5; // st7
  int d014; // ecx
  double v7; // st7
  double v8; // st6
  __int64 v9; // rax
  double v10; // st7
  int d090; // ecx
  struct gbTextureArray *v12; // eax
  int v13; // eax
  struct gbTextureArray *v14; // eax
  int v15; // ecx
  int v16; // edx
  int v17; // edx
  struct gbTextureArray *v18; // eax
  int d058; // edx
  int v20; // ecx
  int d044; // edx
  int d094; // edi
  int v23; // eax
  const char *d064; // eax
  int v25; // [esp-1Ch] [ebp-A0h]
  int v26; // [esp-18h] [ebp-9Ch]
  gbColorQuad v27[2]; // [esp-Ch] [ebp-90h] BYREF
  int v28; // [esp+10h] [ebp-74h]
  int d018; // [esp+14h] [ebp-70h]
  int v30; // [esp+18h] [ebp-6Ch]
  int d01C; // [esp+1Ch] [ebp-68h]
  int v32; // [esp+20h] [ebp-64h] BYREF
  int v33; // [esp+24h] [ebp-60h]
  int v34; // [esp+28h] [ebp-5Ch]
  int v35; // [esp+2Ch] [ebp-58h]
  int v36; // [esp+30h] [ebp-54h] BYREF
  int v37; // [esp+34h] [ebp-50h]
  int v38; // [esp+38h] [ebp-4Ch]
  int v39; // [esp+3Ch] [ebp-48h]
  struct gbTextureArray v40; // [esp+40h] [ebp-44h] BYREF

  result = this->_d038;
  if ( result )
  {
    d010 = this->_d010;
    d018 = this->_d018;
    v4 = d010 + d018;
    v28 = d010;
    v5 = 1.0 - this->_f04C;
    d014 = this->_d014;
    v32 = v4 / 2;
    v7 = v5 * (double)(v4 / 2);
    d01C = this->_d01C;
    v30 = d014;
    v8 = (double)v28 * this->_f04C;
    v33 = (d014 + d01C) / 2;
    v36 = (__int64)(v8 + v7);
    v9 = (__int64)((double)d018 * this->_f04C + v7);
    v10 = (1.0 - this->_f050) * (double)v33;
    v38 = v9;
    v37 = (__int64)((double)d014 * this->_f050 + v10);
    v39 = (__int64)((double)d01C * this->_f050 + v10);
    if ( this->_d070 )
    {
      d090 = this->_d090;
      v27[0].Color = this->_d074;
      *(_DWORD *)&v27[0].Blue = d090;
      v27[0].ColorQuadFmt = d090;
      v27->gbColorQuad((struct gbColorQuad *)&this->_pad_004[4]);
      v12 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray((struct gbTexture *)this->_d070);
      ((_TextureLib_Data *)&this->_d010)->_CheckItem(&v36, v12, v27[0].ColorQuadFmt, *(unsigned int *)&v27[0].Blue, (float *)v27[0].Color);
    }
    if ( !this->_d03C && this->_d080 )
    {
      v13 = this->_d090;
      v27[0].Color = this->_d084;
      *(_DWORD *)&v27[0].Blue = v13;
      v27[0].ColorQuadFmt = d014;
      v27->gbColorQuad((struct gbColorQuad *)&this->_pad_004[4]);
      v14 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray((struct gbTexture *)this->_d080);
      ((_TextureLib_Data *)&this->_d010)->_CheckItem(&v36, v14, v27[0].ColorQuadFmt, *(unsigned int *)&v27[0].Blue, (float *)v27[0].Color);
    }
    if ( this->_d088 )
    {
      v15 = this->_d01C;
      v40.pTexPt[0] = (gbTexture *)this->_d088;
      v27[0].Color = 0;
      *(_DWORD *)&v27[0].Blue = &v40;
      v16 = this->_d018;
      v27[0].ColorQuadFmt = (int)&this->_pad_004[4];
      v26 = this->_d014;
      v25 = this->_d010;
      v40.nTex = 1;
      v25->GetTextureInfo(v26, v16, v15, (int *)&this->_pad_004[4], &v40, 0);
    }
    if ( this->_d078 )
    {
      v17 = this->_d090;
      v27[0].Color = 0;
      *(_DWORD *)&v27[0].Blue = v17;
      v27[0].ColorQuadFmt = d014;
      v27->gbColorQuad((struct gbColorQuad *)&this->_pad_004[4]);
      v18 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray((struct gbTexture *)this->_d078);
      ((_TextureLib_Data *)&this->_d010)->_CheckItem(&v36, v18, v27[0].ColorQuadFmt, *(unsigned int *)&v27[0].Blue, (float *)v27[0].Color);
    }
    if ( this->_d068 )
    {
      d058 = this->_d058;
      v32 = v36;
      v20 = d058 + v37;
      d044 = this->_d044;
      d094 = this->_d094;
      v23 = d044 + v36 + this->_d054;
      v32 = v23;
      if ( d094 == -1 )
        v34 = v38 - d044;
      else
        v34 = v23 + d094;
      d064 = (const char *)this->_d064;
      v33 = d044 + v20;
      v35 = v39 - d044;
      if ( !d064 )
        d064 = byte_56A634;
      UIRenderPar(d064, &v32, this->_pad_004, this->_d05C, this->_d048);
    }
    return ((UIWnd *)this)->GetID();
  }
  return result;
}

// 0x00442AD0
BOOL UIFrameWnd::Update(int a2, int a3)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int d020; // ecx
  POINT pt; // [esp+4h] [ebp-8h] BYREF

  if ( !this->_d038 )
    return 0;
  if ( !this->_d03C )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  if ( !PtInRect((const RECT *)&this->_d010, pt) )
  {
    if ( !this->_b08C )
    {
      d020 = this->_d020;
      this->_b08C = 1;
      if ( d020 )
        (*(void (**)(int, int, int, _DWORD))(*(_DWORD *)d020 + 24))(d020, 1003, this->_d00C, 0);
    }
    return ((UIWnd *)this)->HitTest(a2, a3);
  }
  if ( g_Input.KeyInfo[0].PressTime != 1 || (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v6 = this->_d020;
      if ( v6 )
      {
        (*(void (**)(int, int, int, int))(*(_DWORD *)v6 + 24))(
          v6,
          1010,
          this->_d00C,
          LOWORD(pt.x) | (LOWORD(pt.y) << 16));
        this->_b08C = 0;
        return ((UIWnd *)this)->HitTest(a2, a3);
      }
    }
    else if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
    {
      v7 = this->_d020;
      if ( v7 )
      {
        (*(void (**)(int, int, int, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1011, this->_d00C, 0);
        this->_b08C = 0;
        return ((UIWnd *)this)->HitTest(a2, a3);
      }
    }
    else
    {
      v8 = this->_d020;
      if ( v8 )
        (*(void (**)(int, int, int, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1002, this->_d00C, 0);
    }
LABEL_20:
    this->_b08C = 0;
    return ((UIWnd *)this)->HitTest(a2, a3);
  }
  v5 = this->_d020;
  if ( !v5 )
    goto LABEL_20;
  (*(void (**)(int, int, int, int))(*(_DWORD *)v5 + 24))(
    v5,
    1009,
    this->_d00C,
    LOWORD(pt.x) | (LOWORD(pt.y) << 16));
  this->_b08C = 0;
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x00442C60
int UIFrameWnd::SetPosition(int a2, int a3)
{
  this->_d054 = a2;
  this->_d058 = a3;
  return a2;
}
