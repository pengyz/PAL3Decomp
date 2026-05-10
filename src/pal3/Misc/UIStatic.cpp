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
  this->_p000 = &off_56AD88;
  this->_b044 = 0;
  this->_b045 = 0;
  this->_d050 = 0;
  v2 = (char *)&this->_pad_054[8];
  v3 = 2;
  do
  {
    *((_DWORD *)v2 - 2) = 0;
    *(_DWORD *)v2 = 0;
    v2 += 4;
    --v3;
  }
  while ( v3 );
  memset(this->_tail, 0, sizeof(this->_tail));
  this->_d04C = 1;
  this->_d070 = 0;
  this->_d074 = 0;
  this->_d068 = 0;
  this->_d06C = 0;
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
  char b044; // dl
  int v9; // ecx
  int d020; // ecx
  int v11; // ecx
  int v12; // ecx
  void *v13; // [esp-8h] [ebp-1Ch]
  POINT pt; // [esp+Ch] [ebp-8h] BYREF

  if ( !this->_d038 )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  v5 = PtInRect((const RECT *)&this->_d010, pt);
  if ( this->_d03C )
  {
    if ( a3 )
    {
      if ( v5 )
      {
        if ( g_Input.KeyInfo[0].PressTime == 1 )
        {
          b044 = this->_b044;
          this->_b045 = 1;
          this->_b044 = b044 == 0;
          if ( b044 )
          {
            d020 = this->_d020;
            this->_d050 = 0;
            if ( d020 )
              (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)d020 + 24))(1001, this->_d00C, 0);
          }
          else
          {
            v9 = this->_d020;
            this->_d050 = 1;
            if ( v9 )
              (*(void (__stdcall **)(int, int, int))(*(_DWORD *)v9 + 24))(1001, this->_d00C, 1);
          }
          this->_b045 = 0;
          this->_b046 = 0;
        }
        else
        {
          v11 = this->_d020;
          this->_b064 = 1;
          this->_b046 = 0;
          if ( v11 )
            (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)v11 + 24))(1002, this->_d00C, 0);
        }
      }
      else if ( !this->_b046 )
      {
        v12 = this->_d020;
        this->_b064 = 0;
        this->_b046 = 1;
        if ( v12 )
          (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)v12 + 24))(1003, this->_d00C, 0);
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
      v6 = this->_d020;
      if ( v6 )
        (*(void (**)(int, int, int, int))(*(_DWORD *)v6 + 24))(v6, 1021, this->_d00C, 1);
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
  int d050; // eax
  unsigned int *d06C; // eax
  unsigned int *v5; // ebx
  int *p_d010; // edi
  gbTexture *v7; // ecx
  gbTexture *d070; // eax
  unsigned int *d074; // [esp-10h] [ebp-58h]
  struct gbTextureArray v10; // [esp+4h] [ebp-44h] BYREF

  result = this->_d038;
  if ( result )
  {
    d050 = this->_d050;
    if ( *(_DWORD *)&this->_pad_054[4 * d050] )
    {
      if ( this->_b064 && this->_d068 && d050 != 1 )
      {
        d06C = (unsigned int *)this->_d06C;
        v10.pTexPt[0] = (gbTexture *)this->_d068;
        v10.nTex = 1;
        v5 = (unsigned int *)&this->_pad_004[4];
        p_d010 = (int *)&this->_d010;
        ((_TextureLib_Data *)&this->_d010)->SetLibFolder((unsigned int *)&this->_pad_004[4], &v10, 0x114u, d06C, COERCE_FLOAT(1));
      }
      else
      {
        v7 = (gbTexture *)*(gbTexture **)&this->_pad_054[4 * d050];
        v10.nTex = 1;
        v10.pTexPt[0] = v7;
        v5 = (unsigned int *)&this->_pad_004[4];
        p_d010 = (int *)&this->_d010;
        ((_TextureLib_Data *)&this->_d010)->SetLibFolder((unsigned int *)&this->_pad_004[4], &v10, 0x114u, *(unsigned int **)&this->_pad_054[4 * d050 + 8], COERCE_FLOAT(1));
      }
      if ( !this->_d03C )
      {
        d070 = (gbTexture *)this->_d070;
        if ( d070 )
        {
          d074 = (unsigned int *)this->_d074;
          v10.nTex = 1;
          v10.pTexPt[0] = d070;
          p_d010->SetLibFolder(v5, &v10, 0x114u, d074, COERCE_FLOAT(1));
        }
      }
    }
    else
    {
      p_d010 = (int *)&this->_d010;
      ((_TextureLib_Data *)this->_d010)->~_TextureLib_Data(this->_d014, this->_d018, this->_d01C, (float *)&unk_D91780);
    }
    if ( this->_tail[0] )
      UIRenderPar(this->_tail, p_d010, &this->_pad_047[1], 1, 1);
    return ((UIWnd *)this)->GetID();
  }
  return result;
}
