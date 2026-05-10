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
  int *p_m_bvisible; // eax
  int v3; // ecx

  this->UIWnd();
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AD88;
  LOBYTE(this->m_pfather) = 0;
  BYTE1(this->m_pfather) = 0;
  this->m_childs.m_nMaxSize = 0;
  p_m_bvisible = (int *)&this->m_bvisible;
  v3 = 2;
  do
  {
    *(p_m_bvisible - 2) = 0;
    *p_m_bvisible++ = 0;
    --v3;
  }
  while ( v3 );
  memset(&this->m_ratioh, 0, 0x80u);
  this->m_childs.m_nSize = 1;
  this->pDebugTex = 0;
  this->m_ratiow = 0.0;
  this->m_bordersize = 0;
  this->m_align = 0;
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
  __int32 v6; // ecx
  char *Instance; // eax
  char m_pfather; // dl
  __int32 v9; // ecx
  __int32 Green; // ecx
  __int32 v11; // ecx
  __int32 v12; // ecx
  void *v13; // [esp-8h] [ebp-1Ch]
  POINT pt; // [esp+Ch] [ebp-8h] BYREF

  if ( !this->m_rect.top )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  v5 = PtInRect((const RECT *)&this->m_fontcolor.Alpha, pt);
  if ( this->m_rect.right )
  {
    if ( a3 )
    {
      if ( v5 )
      {
        if ( g_Input.m_shiftedKeyStates[207] == 1 )
        {
          m_pfather = (char)this->m_pfather;
          BYTE1(this->m_pfather) = 1;
          LOBYTE(this->m_pfather) = m_pfather == 0;
          if ( m_pfather )
          {
            Green = this->m_wndcolor.Green;
            this->m_childs.m_nMaxSize = 0;
            if ( Green )
              (*(void (__stdcall **)(int, __int32, _DWORD))(*(_DWORD *)Green + 24))(1001, this->m_fontcolor.Red, 0);
          }
          else
          {
            v9 = this->m_wndcolor.Green;
            this->m_childs.m_nMaxSize = 1;
            if ( v9 )
              (*(void (__stdcall **)(int, __int32, int))(*(_DWORD *)v9 + 24))(1001, this->m_fontcolor.Red, 1);
          }
          BYTE1(this->m_pfather) = 0;
          BYTE2(this->m_pfather) = 0;
        }
        else
        {
          v11 = this->m_wndcolor.Green;
          LOBYTE(this->m_bfocus) = 1;
          BYTE2(this->m_pfather) = 0;
          if ( v11 )
            (*(void (__stdcall **)(int, __int32, _DWORD))(*(_DWORD *)v11 + 24))(1002, this->m_fontcolor.Red, 0);
        }
      }
      else if ( !BYTE2(this->m_pfather) )
      {
        v12 = this->m_wndcolor.Green;
        LOBYTE(this->m_bfocus) = 0;
        BYTE2(this->m_pfather) = 1;
        if ( v12 )
          (*(void (__stdcall **)(int, __int32, _DWORD))(*(_DWORD *)v12 + 24))(1003, this->m_fontcolor.Red, 0);
      }
      return this->HitTest(a2, a3);
    }
    else
    {
      return this->HitTest(a2, 0);
    }
  }
  else
  {
    if ( v5 && g_Input.m_shiftedKeyStates[207] == 1 )
    {
      v6 = this->m_wndcolor.Green;
      if ( v6 )
        (*(void (**)(__int32, int, __int32, int))(*(_DWORD *)v6 + 24))(v6, 1021, this->m_fontcolor.Red, 1);
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
  int m_nMaxSize; // eax
  unsigned int *m_align; // eax
  __int32 *p_Green; // ebx
  __int32 *p_Alpha; // edi
  gbTexture *v7; // ecx
  gbTexture *pDebugTex; // eax
  float m_ratiow; // [esp-10h] [ebp-58h]
  struct gbTextureArray v10; // [esp+4h] [ebp-44h] BYREF

  result = this->m_rect.top;
  if ( result )
  {
    m_nMaxSize = this->m_childs.m_nMaxSize;
    if ( *(&this->m_childs.m_nGrowBy + m_nMaxSize) )
    {
      if ( LOBYTE(this->m_bfocus) && this->m_bordersize && m_nMaxSize != 1 )
      {
        m_align = (unsigned int *)this->m_align;
        v10.pTexPt[0] = (gbTexture *)this->m_bordersize;
        v10.nTex = 1;
        p_Green = (__int32 *)&this->m_fontcolor.Green;
        p_Alpha = (__int32 *)&this->m_fontcolor.Alpha;
        ((_TextureLib_Data *)&this->m_fontcolor.Alpha)->SetLibFolder((unsigned int *)&this->m_fontcolor.Green, &v10, 0x114u, m_align, COERCE_FLOAT(1));
      }
      else
      {
        v7 = (gbTexture *)*(&this->m_childs.m_nGrowBy + m_nMaxSize);
        v10.nTex = 1;
        v10.pTexPt[0] = v7;
        p_Green = (__int32 *)&this->m_fontcolor.Green;
        p_Alpha = (__int32 *)&this->m_fontcolor.Alpha;
        ((_TextureLib_Data *)&this->m_fontcolor.Alpha)->SetLibFolder((unsigned int *)&this->m_fontcolor.Green, &v10, 0x114u, *((unsigned int **)&this->m_bvisible + m_nMaxSize), COERCE_FLOAT(1));
      }
      if ( !this->m_rect.right )
      {
        pDebugTex = (gbTexture *)this->pDebugTex;
        if ( pDebugTex )
        {
          m_ratiow = this->m_ratiow;
          v10.nTex = 1;
          v10.pTexPt[0] = pDebugTex;
          p_Alpha->SetLibFolder((unsigned int *)p_Green, &v10, 0x114u, (unsigned int *)LODWORD(m_ratiow), COERCE_FLOAT(1));
        }
      }
    }
    else
    {
      p_Alpha = (__int32 *)&this->m_fontcolor.Alpha;
      ((_TextureLib_Data *)this->m_fontcolor.Alpha)->~_TextureLib_Data(this->m_fontcolor.Color, this->m_wndcolor.ColorQuadFmt, this->m_wndcolor.Blue, (float *)&unk_D91780);
    }
    if ( LOBYTE(this->m_ratioh) )
      UIRenderPar((const char *)&this->m_ratioh, p_Alpha, &this->m_childs, 1, 1);
    return this->GetID();
  }
  return result;
}
