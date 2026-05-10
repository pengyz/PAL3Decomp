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
  *(_DWORD *)this->_pad_0000 = &off_56AD88;
  LOBYTE(this->m_bordersize) = 0;
  BYTE1(this->m_bordersize) = 0;
  *(_DWORD *)this->_pad_0004 = 0;
  v2 = (char *)&this->_pad_0004[12];
  v3 = 2;
  do
  {
    *((_DWORD *)v2 - 2) = 0;
    *(_DWORD *)v2 = 0;
    v2 += 4;
    --v3;
  }
  while ( v3 );
  memset(&this->_pad_0004[40], 0, 0x80u);
  this->pDebugTex = (gbTexture *)1;
  *(_DWORD *)&this->_pad_0004[32] = 0;
  *(_DWORD *)&this->_pad_0004[36] = 0;
  *(_DWORD *)&this->_pad_0004[24] = 0;
  *(_DWORD *)&this->_pad_0004[28] = 0;
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
  char m_bordersize; // dl
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  void *v13; // [esp-8h] [ebp-1Ch]
  POINT pt; // [esp+Ch] [ebp-8h] BYREF

  if ( !*(_DWORD *)&this->_pad_0000[56] )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  v5 = PtInRect((const RECT *)&this->_pad_0000[16], pt);
  if ( *(_DWORD *)&this->_pad_0000[60] )
  {
    if ( a3 )
    {
      if ( v5 )
      {
        if ( g_Input.KeyInfo[0].PressTime == 1 )
        {
          m_bordersize = this->m_bordersize;
          BYTE1(this->m_bordersize) = 1;
          LOBYTE(this->m_bordersize) = m_bordersize == 0;
          if ( m_bordersize )
          {
            v10 = *(_DWORD *)&this->_pad_0000[32];
            *(_DWORD *)this->_pad_0004 = 0;
            if ( v10 )
              (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(
                1001,
                *(_DWORD *)&this->_pad_0000[12],
                0);
          }
          else
          {
            v9 = *(_DWORD *)&this->_pad_0000[32];
            *(_DWORD *)this->_pad_0004 = 1;
            if ( v9 )
              (*(void (__stdcall **)(int, _DWORD, int))(*(_DWORD *)v9 + 24))(1001, *(_DWORD *)&this->_pad_0000[12], 1);
          }
          BYTE1(this->m_bordersize) = 0;
          BYTE2(this->m_bordersize) = 0;
        }
        else
        {
          v11 = *(_DWORD *)&this->_pad_0000[32];
          this->_pad_0004[20] = 1;
          BYTE2(this->m_bordersize) = 0;
          if ( v11 )
            (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(1002, *(_DWORD *)&this->_pad_0000[12], 0);
        }
      }
      else if ( !BYTE2(this->m_bordersize) )
      {
        v12 = *(_DWORD *)&this->_pad_0000[32];
        this->_pad_0004[20] = 0;
        BYTE2(this->m_bordersize) = 1;
        if ( v12 )
          (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(1003, *(_DWORD *)&this->_pad_0000[12], 0);
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
      v6 = *(_DWORD *)&this->_pad_0000[32];
      if ( v6 )
        (*(void (**)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(
          v6,
          1021,
          *(_DWORD *)&this->_pad_0000[12],
          1);
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

  result = *(_DWORD *)&this->_pad_0000[56];
  if ( result )
  {
    v3 = *(_DWORD *)this->_pad_0004;
    if ( *(_DWORD *)&this->_pad_0004[4 * v3 + 4] )
    {
      if ( this->_pad_0004[20] && *(_DWORD *)&this->_pad_0004[24] && v3 != 1 )
      {
        v4 = (unsigned int *)*(unsigned int **)&this->_pad_0004[28];
        v10.pTexPt[0] = *(gbTexture **)&this->_pad_0004[24];
        v10.nTex = 1;
        v5 = (unsigned int *)&this->_pad_0000[8];
        v6 = (int *)&this->_pad_0000[16];
        ((_TextureLib_Data *)&this->_pad_0000[16])->SetLibFolder((unsigned int *)&this->_pad_0000[8], &v10, 0x114u, v4, COERCE_FLOAT(1));
      }
      else
      {
        v7 = (gbTexture *)*(gbTexture **)&this->_pad_0004[4 * v3 + 4];
        v10.nTex = 1;
        v10.pTexPt[0] = v7;
        v5 = (unsigned int *)&this->_pad_0000[8];
        v6 = (int *)&this->_pad_0000[16];
        ((_TextureLib_Data *)&this->_pad_0000[16])->SetLibFolder((unsigned int *)&this->_pad_0000[8], &v10, 0x114u, *(unsigned int **)&this->_pad_0004[4 * v3 + 12], COERCE_FLOAT(1));
      }
      if ( !*(_DWORD *)&this->_pad_0000[60] )
      {
        v8 = (gbTexture *)*(gbTexture **)&this->_pad_0004[32];
        if ( v8 )
        {
          v9 = (unsigned int *)*(unsigned int **)&this->_pad_0004[36];
          v10.nTex = 1;
          v10.pTexPt[0] = v8;
          v6->SetLibFolder(v5, &v10, 0x114u, v9, COERCE_FLOAT(1));
        }
      }
    }
    else
    {
      v6 = (int *)&this->_pad_0000[16];
      ((_TextureLib_Data *)*(_DWORD *)&this->_pad_0000[16])->~_TextureLib_Data(*(_DWORD *)&this->_pad_0000[20], *(_DWORD *)&this->_pad_0000[24], *(_DWORD *)&this->_pad_0000[28], (float *)&unk_D91780);
    }
    if ( this->_pad_0004[40] )
      UIRenderPar(&this->_pad_0004[40], v6, &this->m_align, 1, 1);
    return ((UIWnd *)this)->GetID();
  }
  return result;
}
