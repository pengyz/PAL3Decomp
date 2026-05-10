#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_442390(...);

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
void sub_442390(UIWnd *this)
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al

  *(_DWORD *)this->_data = &off_56ADD0;
  UIFrameWnd::OnMessage();
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
int UIFrameWnd::Render(int _this)
{
  int result; // eax
  int v3; // ecx
  int v4; // eax
  double v5; // st7
  int v6; // ecx
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
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // edi
  int v23; // eax
  _BYTE *v24; // eax
  int v25; // [esp-1Ch] [ebp-A0h]
  int v26; // [esp-18h] [ebp-9Ch]
  gbColorQuad v27; // [esp-Ch] [ebp-90h] BYREF
  int v28; // [esp+10h] [ebp-74h]
  int v29; // [esp+14h] [ebp-70h]
  int v30; // [esp+18h] [ebp-6Ch]
  int v31; // [esp+1Ch] [ebp-68h]
  int v32; // [esp+20h] [ebp-64h] BYREF
  int v33; // [esp+24h] [ebp-60h]
  int v34; // [esp+28h] [ebp-5Ch]
  int v35; // [esp+2Ch] [ebp-58h]
  int v36; // [esp+30h] [ebp-54h] BYREF
  int v37; // [esp+34h] [ebp-50h]
  int v38; // [esp+38h] [ebp-4Ch]
  int v39; // [esp+3Ch] [ebp-48h]
  struct gbTextureArray v40; // [esp+40h] [ebp-44h] BYREF

  result = *(_DWORD *)(this + 56);
  if ( result )
  {
    v3 = *(_DWORD *)(this + 16);
    v29 = *(_DWORD *)(this + 24);
    v4 = v3 + v29;
    v28 = v3;
    v5 = 1.0 - *(float *)(this + 76);
    v6 = *(_DWORD *)(this + 20);
    v32 = v4 / 2;
    v7 = v5 * (double)(v4 / 2);
    v31 = *(_DWORD *)(this + 28);
    v30 = v6;
    v8 = (double)v28 * *(float *)(this + 76);
    v33 = (v6 + v31) / 2;
    v36 = (__int64)(v8 + v7);
    v9 = (__int64)((double)v29 * *(float *)(this + 76) + v7);
    v10 = (1.0 - *(float *)(this + 80)) * (double)v33;
    v38 = v9;
    v37 = (__int64)((double)v6 * *(float *)(this + 80) + v10);
    v39 = (__int64)((double)v31 * *(float *)(this + 80) + v10);
    if ( *(_DWORD *)(this + 112) )
    {
      v11 = *(_DWORD *)(this + 144);
      v27.Green = *(_DWORD *)(this + 116);
      v27.Blue = v11;
      v27.ColorQuadFmt = v11;
      ((gbColorQuad *)&v27)->gbColorQuad((struct gbColorQuad *)(this + 8));
      v12 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*(struct gbTexture **)(this + 112));
      ((_DWORD *)(this + 16))->_CheckItem(&v36, v12, v27.ColorQuadFmt, v27.Blue, (float *)v27.Green);
    }
    if ( !*(_DWORD *)(this + 60) && *(_DWORD *)(this + 128) )
    {
      v13 = *(_DWORD *)(this + 144);
      v27.Green = *(_DWORD *)(this + 132);
      v27.Blue = v13;
      v27.ColorQuadFmt = v6;
      ((gbColorQuad *)&v27)->gbColorQuad((struct gbColorQuad *)(this + 8));
      v14 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*(struct gbTexture **)(this + 128));
      ((_DWORD *)(this + 16))->_CheckItem(&v36, v14, v27.ColorQuadFmt, v27.Blue, (float *)v27.Green);
    }
    if ( *(_DWORD *)(this + 136) )
    {
      v15 = *(_DWORD *)(this + 28);
      v40.pTexPt[0] = *(gbTexture **)(this + 136);
      v27.Green = 0;
      v27.Blue = (__int32)&v40;
      v16 = *(_DWORD *)(this + 24);
      v27.ColorQuadFmt = this + 8;
      v26 = *(_DWORD *)(this + 20);
      v25 = *(_DWORD *)(this + 16);
      v40.nTex = 1;
      v25->GetTextureInfo(v26, v16, v15, (int *)(this + 8), &v40, 0);
    }
    if ( *(_DWORD *)(this + 120) )
    {
      v17 = *(_DWORD *)(this + 144);
      v27.Green = 0;
      v27.Blue = v17;
      v27.ColorQuadFmt = v6;
      ((gbColorQuad *)&v27)->gbColorQuad((struct gbColorQuad *)(this + 8));
      v18 = ((gbTextureArray *)&v40.pTexPt[1])->gbTextureArray(*(struct gbTexture **)(this + 120));
      ((_DWORD *)(this + 16))->_CheckItem(&v36, v18, v27.ColorQuadFmt, v27.Blue, (float *)v27.Green);
    }
    if ( *(_DWORD *)(this + 104) )
    {
      v19 = *(_DWORD *)(this + 88);
      v32 = v36;
      v20 = v19 + v37;
      v21 = *(_DWORD *)(this + 68);
      v22 = *(_DWORD *)(this + 148);
      v23 = v21 + v36 + *(_DWORD *)(this + 84);
      v32 = v23;
      if ( v22 == -1 )
        v34 = v38 - v21;
      else
        v34 = v23 + v22;
      v24 = (_BYTE *)*(_BYTE **)(this + 100);
      v33 = v21 + v20;
      v35 = v39 - v21;
      if ( !v24 )
        v24 = byte_56A634;
      UIRenderPar((int)v24, (int)&v32, (_BYTE *)(this + 4), *(_DWORD *)(this + 92), *(_DWORD *)(this + 72));
    }
    return ((UIWnd *)this)->GetID();
  }
  return result;
}

// 0x00442AD0
BOOL UIFrameWnd::Update(int _this, int a2, int a3)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  POINT pt; // [esp+4h] [ebp-8h] BYREF

  if ( !*(_DWORD *)(this + 56) )
    return 0;
  if ( !*(_DWORD *)(this + 60) )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  if ( !PtInRect((const RECT *)(this + 16), pt) )
  {
    if ( !*(_BYTE *)(this + 140) )
    {
      v9 = *(_DWORD *)(this + 32);
      *(_BYTE *)(this + 140) = 1;
      if ( v9 )
        (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1003, *(_DWORD *)(this + 12), 0);
    }
    return ((UIWnd *)this)->HitTest(a2, a3);
  }
  if ( g_Input.m_shiftedKeyStates[207] != 1 || (g_Input.m_shiftedKeyStates[204] & 0xF) != 1 )
  {
    if ( g_Input.m_shiftedKeyStates[211] == 1 && (g_Input.m_shiftedKeyStates[208] & 0xF) == 1 )
    {
      v6 = *(_DWORD *)(this + 32);
      if ( v6 )
      {
        (*(void (**)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(
          v6,
          1010,
          *(_DWORD *)(this + 12),
          LOWORD(pt.x) | (LOWORD(pt.y) << 16));
        *(_BYTE *)(this + 140) = 0;
        return ((UIWnd *)this)->HitTest(a2, a3);
      }
    }
    else if ( g_Input.m_shiftedKeyStates[207] == 1 && (g_Input.m_shiftedKeyStates[204] & 0xF) == 2 )
    {
      v7 = *(_DWORD *)(this + 32);
      if ( v7 )
      {
        (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1011, *(_DWORD *)(this + 12), 0);
        *(_BYTE *)(this + 140) = 0;
        return ((UIWnd *)this)->HitTest(a2, a3);
      }
    }
    else
    {
      v8 = *(_DWORD *)(this + 32);
      if ( v8 )
        (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1002, *(_DWORD *)(this + 12), 0);
    }
LABEL_20:
    *(_BYTE *)(this + 140) = 0;
    return ((UIWnd *)this)->HitTest(a2, a3);
  }
  v5 = *(_DWORD *)(this + 32);
  if ( !v5 )
    goto LABEL_20;
  (*(void (**)(int, int, _DWORD, int))(*(_DWORD *)v5 + 24))(
    v5,
    1009,
    *(_DWORD *)(this + 12),
    LOWORD(pt.x) | (LOWORD(pt.y) << 16));
  *(_BYTE *)(this + 140) = 0;
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x00442C60
int UIFrameWnd::SetPosition(int a2, int a3)
{
  this->m_childs.m_nGrowBy = a2;
  this->m_bcreateok = a3;
  return a2;
}
