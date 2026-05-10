#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIStatic.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/UIWnd.h"

// Unnamed globals (extern)
extern void *off_56AD88;
extern void *off_5974E0;
extern int unk_D91780;

// 0x00440740
UIStatic::UIStatic()
{
  char *v2; // eax
  int v3; // ecx

  ((UIWnd *)this)->UIWnd();
  *(_DWORD *)this->_data = &off_56AD88;
  this->_data[68] = 0;
  this->_data[69] = 0;
  *(_DWORD *)&this->_data[80] = 0;
  v2 = (char *)&this->_data[92];
  v3 = 2;
  do
  {
    *((_DWORD *)v2 - 2) = 0;
    *(_DWORD *)v2 = 0;
    v2 += 4;
    --v3;
  }
  while ( v3 );
  memset(&this->_data[120], 0, 0x80u);
  *(_DWORD *)&this->_data[76] = 1;
  *(_DWORD *)&this->_data[112] = 0;
  *(_DWORD *)&this->_data[116] = 0;
  *(_DWORD *)&this->_data[104] = 0;
  *(_DWORD *)&this->_data[108] = 0;
}

// 0x00440BA0
int UIStatic::OnMessage()
{
  gbRefObject **v2; // esi
  int v3; // ebx
  int result; // eax

  v2 = (gbRefObject **)(this + 21);
  v3 = 2;
  do
  {
    if ( *v2 )
    {
      ((gbRefObject *)*v2)->Release();
      *v2 = 0;
    }
    ++v2;
    --v3;
  }
  while ( v3 );
  ((UIWnd *)this)->UpdateChildren();
  return result;
}

// 0x00440DD0
BOOL UIStatic::Update(int a2, int a3)
{
  BOOL v5; // eax
  int v6; // ecx
  char *Instance; // eax
  char v8; // dl
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  void *v13; // [esp-8h] [ebp-1Ch]
  POINT pt; // [esp+Ch] [ebp-8h] BYREF

  if ( !*(_DWORD *)&this->_data[56] )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  v5 = PtInRect((const RECT *)&this->_data[16], pt);
  if ( *(_DWORD *)&this->_data[60] )
  {
    if ( a3 )
    {
      if ( v5 )
      {
        if ( g_Input.KeyInfo[0].PressTime == 1 )
        {
          v8 = this->_data[68];
          this->_data[69] = 1;
          this->_data[68] = v8 == 0;
          if ( v8 )
          {
            v10 = *(_DWORD *)&this->_data[32];
            *(_DWORD *)&this->_data[80] = 0;
            if ( v10 )
              (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(1001, *(_DWORD *)&this->_data[12], 0);
          }
          else
          {
            v9 = *(_DWORD *)&this->_data[32];
            *(_DWORD *)&this->_data[80] = 1;
            if ( v9 )
              (*(void (__stdcall **)(int, _DWORD, int))(*(_DWORD *)v9 + 24))(1001, *(_DWORD *)&this->_data[12], 1);
          }
          this->_data[69] = 0;
          this->_data[70] = 0;
        }
        else
        {
          v11 = *(_DWORD *)&this->_data[32];
          this->_data[100] = 1;
          this->_data[70] = 0;
          if ( v11 )
            (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(1002, *(_DWORD *)&this->_data[12], 0);
        }
      }
      else if ( !this->_data[70] )
      {
        v12 = *(_DWORD *)&this->_data[32];
        this->_data[100] = 0;
        this->_data[70] = 1;
        if ( v12 )
          (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(1003, *(_DWORD *)&this->_data[12], 0);
      }
      return ((UIWnd *)this)->HitTest(a2, a3);
    }
    else
    {
      return ((UIWnd *)this)->HitTest(a2, 0);
    }
  }
  else
  {
    if ( v5 && g_Input.KeyInfo[0].PressTime == 1 )
    {
      v6 = *(_DWORD *)&this->_data[32];
      if ( v6 )
        (*(void (**)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(v6, 1021, *(_DWORD *)&this->_data[12], 1);
      v13 = off_5974E0;
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
    }
    return 0;
  }
}

// 0x00440F30
int UIStatic::Render()
{
  int result; // eax
  int v3; // eax
  unsigned int *v4; // eax
  unsigned int *v5; // ebx
  int *v6; // edi
  gbTexture *v7; // ecx
  gbTexture *v8; // eax
  unsigned int *v9; // [esp-10h] [ebp-58h]
  struct gbTextureArray v10; // [esp+4h] [ebp-44h] BYREF

  result = *(_DWORD *)&this->_data[56];
  if ( result )
  {
    v3 = *(_DWORD *)&this->_data[80];
    if ( *(_DWORD *)&this->_data[4 * v3 + 84] )
    {
      if ( this->_data[100] && *(_DWORD *)&this->_data[104] && v3 != 1 )
      {
        v4 = (unsigned int *)*(unsigned int **)&this->_data[108];
        v10.pTexPt[0] = *(gbTexture **)&this->_data[104];
        v10.nTex = 1;
        v5 = (unsigned int *)&this->_data[8];
        v6 = (int *)&this->_data[16];
        ((_TextureLib_Data *)&this->_data[16])->SetLibFolder((unsigned int *)&this->_data[8], &v10, 0x114u, v4, COERCE_FLOAT(1));
      }
      else
      {
        v7 = (gbTexture *)*(gbTexture **)&this->_data[4 * v3 + 84];
        v10.nTex = 1;
        v10.pTexPt[0] = v7;
        v5 = (unsigned int *)&this->_data[8];
        v6 = (int *)&this->_data[16];
        ((_TextureLib_Data *)&this->_data[16])->SetLibFolder((unsigned int *)&this->_data[8], &v10, 0x114u, *(unsigned int **)&this->_data[4 * v3 + 92], COERCE_FLOAT(1));
      }
      if ( !*(_DWORD *)&this->_data[60] )
      {
        v8 = (gbTexture *)*(gbTexture **)&this->_data[112];
        if ( v8 )
        {
          v9 = (unsigned int *)*(unsigned int **)&this->_data[116];
          v10.nTex = 1;
          v10.pTexPt[0] = v8;
          v6->SetLibFolder(v5, &v10, 0x114u, v9, COERCE_FLOAT(1));
        }
      }
    }
    else
    {
      v6 = (int *)&this->_data[16];
      ((_TextureLib_Data *)*(_DWORD *)&this->_data[16])->~_TextureLib_Data(*(_DWORD *)&this->_data[20], *(_DWORD *)&this->_data[24], *(_DWORD *)&this->_data[28], (float *)&unk_D91780);
    }
    if ( this->_data[120] )
      UIRenderPar(&this->_data[120], v6, &this->_data[72], 1, 1);
    return ((UIWnd *)this)->GetID();
  }
  return result;
}
