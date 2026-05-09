#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIFrameWnd.h"

// 0x004422E0
void sub_4422E0(_BYTE *this)
{
  char v2; // [esp+7h] [ebp-1h]

  UIWnd::UIWnd();
  *(this + 96) = v2;
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
  *(_DWORD *)this = &off_56ADD0;
  *((_DWORD *)this + 17) = 8;
  *((_DWORD *)this + 23) = 1;
  *(this + 140) = 1;
  *((_DWORD *)this + 36) = 276;
  *((_DWORD *)this + 37) = -1;
}

// 0x00442390
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall sub_442390(std::ios_base *this)
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
      *v3 = v4 - 1;
  }
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 26) = 0;
  *((_DWORD *)this + 27) = 0;
  this->_UIWnd();
}

// 0x00442420
void sub_442420(gbRefObject **this)
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *v5; // ecx

  v2 = *(this + 28);
  if ( v2 )
  {
    v2->Release();
    *(this + 28) = 0;
  }
  v3 = *(this + 32);
  if ( v3 )
  {
    v3->Release();
    *(this + 32) = 0;
  }
  v4 = *(this + 34);
  if ( v4 )
  {
    v4->Release();
    *(this + 34) = 0;
  }
  v5 = *(this + 30);
  if ( v5 )
  {
    v5->Release();
    *(this + 30) = 0;
  }
  *(this + 37) = (gbRefObject *)-1;
}

// 0x00442890
int sub_442890(int this)
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
  int *v11; // ecx
  gbTextureArray *v12; // eax
  int *v13; // eax
  gbTextureArray *v14; // eax
  int v15; // ecx
  int v16; // edx
  int *v17; // edx
  gbTextureArray *v18; // eax
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // edi
  int v23; // eax
  void *v24; // eax
  int v25; // [esp-1Ch] [ebp-A0h]
  int v26; // [esp-18h] [ebp-9Ch]
  int v27; // [esp-Ch] [ebp-90h] BYREF
  int *v28; // [esp-8h] [ebp-8Ch]
  int v29; // [esp-4h] [ebp-88h]
  int v30; // [esp+10h] [ebp-74h]
  int v31; // [esp+14h] [ebp-70h]
  int v32; // [esp+18h] [ebp-6Ch]
  int v33; // [esp+1Ch] [ebp-68h]
  int v34; // [esp+20h] [ebp-64h] BYREF
  int v35; // [esp+24h] [ebp-60h]
  int v36; // [esp+28h] [ebp-5Ch]
  int v37; // [esp+2Ch] [ebp-58h]
  int v38; // [esp+30h] [ebp-54h] BYREF
  int v39; // [esp+34h] [ebp-50h]
  int v40; // [esp+38h] [ebp-4Ch]
  int v41; // [esp+3Ch] [ebp-48h]
  int v42; // [esp+40h] [ebp-44h] BYREF
  _BYTE v43[60]; // [esp+44h] [ebp-40h] BYREF
  int v44; // [esp+80h] [ebp-4h]

  result = *(_DWORD *)(this + 56);
  if ( result )
  {
    v3 = *(_DWORD *)(this + 16);
    v31 = *(_DWORD *)(this + 24);
    v4 = v3 + v31;
    v30 = v3;
    v5 = 1.0 - *(float *)(this + 76);
    v6 = *(_DWORD *)(this + 20);
    v34 = v4 / 2;
    v7 = v5 * (double)(v4 / 2);
    v33 = *(_DWORD *)(this + 28);
    v32 = v6;
    v8 = (double)v30 * *(float *)(this + 76);
    v35 = (v6 + v33) / 2;
    v38 = (__int64)(v8 + v7);
    v9 = (__int64)((double)v31 * *(float *)(this + 76) + v7);
    v10 = (1.0 - *(float *)(this + 80)) * (double)v35;
    v40 = v9;
    v39 = (__int64)((double)v6 * *(float *)(this + 80) + v10);
    v41 = (__int64)((double)v33 * *(float *)(this + 80) + v10);
    if ( *(_DWORD *)(this + 112) )
    {
      v11 = *(int **)(this + 144);
      v29 = *(_DWORD *)(this + 116);
      v28 = v11;
      v27 = (int)v11;
      (gbColorQuad *->gbColorQuad()&v27, (struct gbColorQuad *)(this + 8));
      v12 = (gbTextureArray *->gbTextureArray()v43, *(struct gbTexture **)(this + 112));
      _TextureLib_Data::_CheckItem(this + 16, &v38, v12, v27, v28, v29);
    }
    if ( !*(_DWORD *)(this + 60) && *(_DWORD *)(this + 128) )
    {
      v13 = *(int **)(this + 144);
      v29 = *(_DWORD *)(this + 132);
      v28 = v13;
      v27 = v6;
      (gbColorQuad *->gbColorQuad()&v27, (struct gbColorQuad *)(this + 8));
      v14 = (gbTextureArray *->gbTextureArray()v43, *(struct gbTexture **)(this + 128));
      _TextureLib_Data::_CheckItem(this + 16, &v38, v14, v27, v28, v29);
    }
    if ( *(_DWORD *)(this + 136) )
    {
      v15 = *(_DWORD *)(this + 28);
      v42 = *(_DWORD *)(this + 136);
      v29 = 0;
      v28 = &v42;
      v16 = *(_DWORD *)(this + 24);
      v27 = this + 8;
      v26 = *(_DWORD *)(this + 20);
      v25 = *(_DWORD *)(this + 16);
      v44 = 1;
      v25->GetTextureInfo(v26, v16, v15, this + 8, &v42, 0);
    }
    if ( *(_DWORD *)(this + 120) )
    {
      v17 = *(int **)(this + 144);
      v29 = 0;
      v28 = v17;
      v27 = v6;
      (gbColorQuad *->gbColorQuad()&v27, (struct gbColorQuad *)(this + 8));
      v18 = (gbTextureArray *->gbTextureArray()v43, *(struct gbTexture **)(this + 120));
      _TextureLib_Data::_CheckItem(this + 16, &v38, v18, v27, v28, v29);
    }
    if ( *(_DWORD *)(this + 104) )
    {
      v19 = *(_DWORD *)(this + 88);
      v34 = v38;
      v20 = v19 + v39;
      v21 = *(_DWORD *)(this + 68);
      v22 = *(_DWORD *)(this + 148);
      v23 = v21 + v38 + *(_DWORD *)(this + 84);
      v34 = v23;
      if ( v22 == -1 )
        v36 = v40 - v21;
      else
        v36 = v23 + v22;
      v24 = *(void **)(this + 100);
      v35 = v21 + v20;
      v37 = v41 - v21;
      if ( !v24 )
        v24 = &byte_56A634;
      UIRenderPar(v24, &v34, this + 4, *(_DWORD *)(this + 92), *(_DWORD *)(this + 72));
    }
    return this->GetID();
  }
  return result;
}

// 0x00442AD0
int sub_442AD0(int this, int a2, int a3)
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
  GRPinput::GetCursorPos(&pt);
  if ( !PtInRect((const RECT *)(this + 16), pt) )
  {
    if ( !*(_BYTE *)(this + 140) )
    {
      v9 = *(_DWORD *)(this + 32);
      *(_BYTE *)(this + 140) = 1;
      if ( v9 )
        (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1003, *(_DWORD *)(this + 12), 0);
    }
    return a2->HitTest(a3);
  }
  if ( MEMORY[0xBFC5F4] != 1 || (MEMORY[0xBFC5E8] & 0xF) != 1 )
  {
    if ( MEMORY[0xBFC604] == 1 && (MEMORY[0xBFC5F8] & 0xF) == 1 )
    {
      v6 = *(_DWORD *)(this + 32);
      if ( v6 )
      {
        (*(void (__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(
          v6,
          1010,
          *(_DWORD *)(this + 12),
          LOWORD(pt.x) | (LOWORD(pt.y) << 16));
        *(_BYTE *)(this + 140) = 0;
        return a2->HitTest(a3);
      }
    }
    else if ( MEMORY[0xBFC5F4] == 1 && (MEMORY[0xBFC5E8] & 0xF) == 2 )
    {
      v7 = *(_DWORD *)(this + 32);
      if ( v7 )
      {
        (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1011, *(_DWORD *)(this + 12), 0);
        *(_BYTE *)(this + 140) = 0;
        return a2->HitTest(a3);
      }
    }
    else
    {
      v8 = *(_DWORD *)(this + 32);
      if ( v8 )
        (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1002, *(_DWORD *)(this + 12), 0);
    }
LABEL_20:
    *(_BYTE *)(this + 140) = 0;
    return a2->HitTest(a3);
  }
  v5 = *(_DWORD *)(this + 32);
  if ( !v5 )
    goto LABEL_20;
  (*(void (__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v5 + 24))(
    v5,
    1009,
    *(_DWORD *)(this + 12),
    LOWORD(pt.x) | (LOWORD(pt.y) << 16));
  *(_BYTE *)(this + 140) = 0;
  return a2->HitTest(a3);
}

// 0x00442C60
int sub_442C60(_DWORD *this, int a2, int a3)
{
  *(this + 21) = a2;
  *(this + 22) = a3;
  return a2;
}
