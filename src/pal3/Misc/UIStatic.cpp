#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIStatic.h"

// Forward declarations for unnamed functions
int sub_440740(...);
int sub_440BA0(...);
int sub_440DD0(...);
int sub_440F30(...);

// Unnamed globals (extern)
extern void *off_56AD88;
extern void *off_5974E0;

// 0x00440740
void sub_440740()
{
  _DWORD *v2; // eax
  int v3; // ecx

  UIWnd::UIWnd();
  *(_DWORD *)this = &off_56AD88;
  *((_DWORD *)this + 68) = 0;
  *((_DWORD *)this + 69) = 0;
  *((_DWORD *)this + 20) = 0;
  v2 = this + 92;
  v3 = 2;
  do
  {
    *(v2 - 2) = 0;
    *v2++ = 0;
    --v3;
  }
  while ( v3 );
  memset(this + 120, 0, 0x80u);
  *((_DWORD *)this + 19) = 1;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 26) = 0;
  *((_DWORD *)this + 27) = 0;
}

// 0x00440BA0
int sub_440BA0(gbRefObject **this)
{
  gbRefObject **v2; // esi
  int v3; // ebx

  v2 = this + 21;
  v3 = 2;
  do
  {
    if ( *v2 )
    {
      gbRefObject::Release(*v2);
      *v2 = 0;
    }
    ++v2;
    --v3;
  }
  while ( v3 );
  return this->UpdateChildren();
}

// 0x00440DD0
int sub_440DD0(int this, int a2, int a3)
{
  BOOL v5; // eax
  int v6; // ecx
  char v7; // dl
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  char *v12; // [esp-8h] [ebp-1Ch]
  POINT pt; // [esp+Ch] [ebp-8h] BYREF

  if ( !*(_DWORD *)(this + 56) )
    return 0;
  GRPinput::GetCursorPos(&pt);
  v5 = PtInRect((const RECT *)(this + 16), pt);
  if ( *(_DWORD *)(this + 60) )
  {
    if ( a3 )
    {
      if ( v5 )
      {
        if ( MEMORY[0xBFC5F4] == 1 )
        {
          v7 = *(_BYTE *)(this + 68);
          *(_BYTE *)(this + 69) = 1;
          *(_BYTE *)(this + 68) = v7 == 0;
          if ( v7 )
          {
            v9 = *(_DWORD *)(this + 32);
            *(_DWORD *)(this + 80) = 0;
            if ( v9 )
              (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(1001, *(_DWORD *)(this + 12), 0);
          }
          else
          {
            v8 = *(_DWORD *)(this + 32);
            *(_DWORD *)(this + 80) = 1;
            if ( v8 )
              (*(void (__stdcall **)(int, _DWORD, int))(*(_DWORD *)v8 + 24))(1001, *(_DWORD *)(this + 12), 1);
          }
          *(_BYTE *)(this + 69) = 0;
          *(_BYTE *)(this + 70) = 0;
        }
        else
        {
          v10 = *(_DWORD *)(this + 32);
          *(_BYTE *)(this + 100) = 1;
          *(_BYTE *)(this + 70) = 0;
          if ( v10 )
            (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(1002, *(_DWORD *)(this + 12), 0);
        }
      }
      else if ( !*(_BYTE *)(this + 70) )
      {
        v11 = *(_DWORD *)(this + 32);
        *(_BYTE *)(this + 100) = 0;
        *(_BYTE *)(this + 70) = 1;
        if ( v11 )
          (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(1003, *(_DWORD *)(this + 12), 0);
      }
      return a2->HitTest(a3);
    }
    else
    {
      return a2->HitTest(0);
    }
  }
  else
  {
    if ( v5 && MEMORY[0xBFC5F4] == 1 )
    {
      v6 = *(_DWORD *)(this + 32);
      if ( v6 )
        (*(void (__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(v6, 1021, *(_DWORD *)(this + 12), 1);
      v12 = off_5974E0[0];
      CScreenMode::GetInstance();
      v12->AudioSetPosition(1);
    }
    return 0;
  }
}

// 0x00440F30
int sub_440F30(int this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // ecx
  int v8; // eax
  int v9; // [esp-10h] [ebp-58h]
  int v10[16]; // [esp+4h] [ebp-44h] BYREF
  int v11; // [esp+44h] [ebp-4h]

  result = *(_DWORD *)(this + 56);
  if ( result )
  {
    v3 = *(_DWORD *)(this + 80);
    if ( *(_DWORD *)(this + 4 * v3 + 84) )
    {
      if ( *(_BYTE *)(this + 100) && *(_DWORD *)(this + 104) && v3 != 1 )
      {
        v4 = *(_DWORD *)(this + 108);
        v10[0] = *(_DWORD *)(this + 104);
        v11 = 1;
        v5 = this + 8;
        v6 = this + 16;
        _TextureLib_Data::SetLibFolder(this + 16, this + 8, (int)v10, 276, v4, COERCE_FLOAT(1));
      }
      else
      {
        v7 = *(_DWORD *)(this + 4 * v3 + 84);
        v11 = 1;
        v10[0] = v7;
        v5 = this + 8;
        v6 = this + 16;
        _TextureLib_Data::SetLibFolder(
          this + 16,
          this + 8,
          (int)v10,
          276,
          *(_DWORD *)(this + 4 * v3 + 92),
          COERCE_FLOAT(1));
      }
      if ( !*(_DWORD *)(this + 60) )
      {
        v8 = *(_DWORD *)(this + 112);
        if ( v8 )
        {
          v9 = *(_DWORD *)(this + 116);
          v11 = 1;
          v10[0] = v8;
          v6->SetLibFolder(v5, (int)v10, 276, v9, COERCE_FLOAT(1));
        }
      }
    }
    else
    {
      v6 = this + 16;
      _TextureLib_Data::~_TextureLib_Data(
        *(_DWORD *)(this + 16),
        *(_DWORD *)(this + 20),
        *(_DWORD *)(this + 24),
        *(_DWORD *)(this + 28),
        &MEMORY[0xD91780]);
    }
    if ( *(_BYTE *)(this + 120) )
      UIRenderPar(this + 120, v6, this + 72, 1, 1);
    return this->GetID();
  }
  return result;
}
