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

  ((UIWnd *)&this->_base)->UIWnd();
  *(_DWORD *)this->_base._pad_000 = &off_56AD88;
  LOBYTE(this->m_bordersize) = 0;
  BYTE1(this->m_bordersize) = 0;
  *(_DWORD *)this->_pad_004 = 0;
  v2 = (char *)&this->_pad_004[12];
  v3 = 2;
  do
  {
    *((_DWORD *)v2 - 2) = 0;
    *(_DWORD *)v2 = 0;
    v2 += 4;
    --v3;
  }
  while ( v3 );
  memset(&this->_pad_004[40], 0, 0x80u);
  this->pDebugTex = (gbTexture *)1;
  *(_DWORD *)&this->_pad_004[32] = 0;
  *(_DWORD *)&this->_pad_004[36] = 0;
  *(_DWORD *)&this->_pad_004[24] = 0;
  *(_DWORD *)&this->_pad_004[28] = 0;
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
  UIWnd *v6; // ecx
  char *Instance; // eax
  char m_bordersize; // dl
  UIWnd *v9; // ecx
  UIWnd *m_pfather; // ecx
  UIWnd *v11; // ecx
  UIWnd *v12; // ecx
  void *v13; // [esp-8h] [ebp-1Ch]
  POINT pt; // [esp+Ch] [ebp-8h] BYREF

  if ( !this->_base.m_bvisible )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  v5 = PtInRect((const RECT *)this->_base.m_rect, pt);
  if ( this->_base.m_benable )
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
            m_pfather = (UIWnd *)this->_base.m_pfather;
            *(_DWORD *)this->_pad_004 = 0;
            if ( m_pfather )
              (*(void (__stdcall **)(int, unsigned int, _DWORD))(*(_DWORD *)m_pfather->_pad_000 + 24))(
                1001,
                this->_base.m_id,
                0);
          }
          else
          {
            v9 = (UIWnd *)this->_base.m_pfather;
            *(_DWORD *)this->_pad_004 = 1;
            if ( v9 )
              (*(void (__stdcall **)(int, unsigned int, int))(*(_DWORD *)v9->_pad_000 + 24))(1001, this->_base.m_id, 1);
          }
          BYTE1(this->m_bordersize) = 0;
          BYTE2(this->m_bordersize) = 0;
        }
        else
        {
          v11 = (UIWnd *)this->_base.m_pfather;
          this->_pad_004[20] = 1;
          BYTE2(this->m_bordersize) = 0;
          if ( v11 )
            (*(void (__stdcall **)(int, unsigned int, _DWORD))(*(_DWORD *)v11->_pad_000 + 24))(
              1002,
              this->_base.m_id,
              0);
        }
      }
      else if ( !BYTE2(this->m_bordersize) )
      {
        v12 = (UIWnd *)this->_base.m_pfather;
        this->_pad_004[20] = 0;
        BYTE2(this->m_bordersize) = 1;
        if ( v12 )
          (*(void (__stdcall **)(int, unsigned int, _DWORD))(*(_DWORD *)v12->_pad_000 + 24))(1003, this->_base.m_id, 0);
      }
      return ((UIWnd *)&this->_base)->HitTest(a2, a3);
    }
    else
    {
      return ((UIWnd *)&this->_base)->HitTest(a2, 0);
    }
  }
  else
  {
    if ( v5 && g_Input.KeyInfo[0].PressTime == 1 )
    {
      v6 = (UIWnd *)this->_base.m_pfather;
      if ( v6 )
        (*(void (**)(UIWnd *, int, unsigned int, int))(*(_DWORD *)v6->_pad_000 + 24))(
          v6,
          1021,
          this->_base.m_id,
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
  unsigned int *m_wndcolor; // ebx
  int *m_rect; // edi
  gbTexture *v7; // ecx
  gbTexture *v8; // eax
  unsigned int *v9; // [esp-10h] [ebp-58h]
  struct gbTextureArray v10; // [esp+4h] [ebp-44h] BYREF

  result = this->_base.m_bvisible;
  if ( result )
  {
    v3 = *(_DWORD *)this->_pad_004;
    if ( *(_DWORD *)&this->_pad_004[4 * v3 + 4] )
    {
      if ( this->_pad_004[20] && *(_DWORD *)&this->_pad_004[24] && v3 != 1 )
      {
        v4 = (unsigned int *)*(unsigned int **)&this->_pad_004[28];
        v10.pTexPt[0] = *(gbTexture **)&this->_pad_004[24];
        v10.nTex = 1;
        m_wndcolor = (unsigned int *)this->_base.m_wndcolor;
        m_rect = (int *)this->_base.m_rect;
        ((_TextureLib_Data *)this->_base.m_rect)->SetLibFolder((unsigned int *)this->_base.m_wndcolor, &v10, 0x114u, v4, COERCE_FLOAT(1));
      }
      else
      {
        v7 = (gbTexture *)*(gbTexture **)&this->_pad_004[4 * v3 + 4];
        v10.nTex = 1;
        v10.pTexPt[0] = v7;
        m_wndcolor = (unsigned int *)this->_base.m_wndcolor;
        m_rect = (int *)this->_base.m_rect;
        ((_TextureLib_Data *)this->_base.m_rect)->SetLibFolder((unsigned int *)this->_base.m_wndcolor, &v10, 0x114u, *(unsigned int **)&this->_pad_004[4 * v3 + 12], COERCE_FLOAT(1));
      }
      if ( !this->_base.m_benable )
      {
        v8 = (gbTexture *)*(gbTexture **)&this->_pad_004[32];
        if ( v8 )
        {
          v9 = (unsigned int *)*(unsigned int **)&this->_pad_004[36];
          v10.nTex = 1;
          v10.pTexPt[0] = v8;
          m_rect->SetLibFolder(m_wndcolor, &v10, 0x114u, v9, COERCE_FLOAT(1));
        }
      }
    }
    else
    {
      m_rect = (int *)this->_base.m_rect;
      ((_TextureLib_Data *)*(_DWORD *)this->_base.m_rect)->~_TextureLib_Data(*(_DWORD *)&this->_base.m_rect[4], *(_DWORD *)&this->_base.m_rect[8], *(_DWORD *)&this->_base.m_rect[12], (float *)&unk_D91780);
    }
    if ( this->_pad_004[40] )
      UIRenderPar(&this->_pad_004[40], m_rect, &this->m_align, 1, 1);
    return ((UIWnd *)&this->_base)->GetID();
  }
  return result;
}
