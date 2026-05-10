#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIStatic.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/UIWnd.h"

// Unnamed globals (extern)
extern void *off_56AD88;
extern void *off_5974E0;

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
BOOL UIStatic::Update(int _this, int a2, int a3)
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

  if ( !*(_DWORD *)(this + 56) )
    return 0;
  ((GRPinput *)&pt)->GetCursorPos();
  v5 = PtInRect((const RECT *)(this + 16), pt);
  if ( *(_DWORD *)(this + 60) )
  {
    if ( a3 )
    {
      if ( v5 )
      {
        if ( g_Input.m_shiftedKeyStates[207] == 1 )
        {
          v8 = *(_BYTE *)(this + 68);
          *(_BYTE *)(this + 69) = 1;
          *(_BYTE *)(this + 68) = v8 == 0;
          if ( v8 )
          {
            v10 = *(_DWORD *)(this + 32);
            *(_DWORD *)(this + 80) = 0;
            if ( v10 )
              (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(1001, *(_DWORD *)(this + 12), 0);
          }
          else
          {
            v9 = *(_DWORD *)(this + 32);
            *(_DWORD *)(this + 80) = 1;
            if ( v9 )
              (*(void (__stdcall **)(int, _DWORD, int))(*(_DWORD *)v9 + 24))(1001, *(_DWORD *)(this + 12), 1);
          }
          *(_BYTE *)(this + 69) = 0;
          *(_BYTE *)(this + 70) = 0;
        }
        else
        {
          v11 = *(_DWORD *)(this + 32);
          *(_BYTE *)(this + 100) = 1;
          *(_BYTE *)(this + 70) = 0;
          if ( v11 )
            (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(1002, *(_DWORD *)(this + 12), 0);
        }
      }
      else if ( !*(_BYTE *)(this + 70) )
      {
        v12 = *(_DWORD *)(this + 32);
        *(_BYTE *)(this + 100) = 0;
        *(_BYTE *)(this + 70) = 1;
        if ( v12 )
          (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(1003, *(_DWORD *)(this + 12), 0);
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
    if ( v5 && g_Input.m_shiftedKeyStates[207] == 1 )
    {
      v6 = *(_DWORD *)(this + 32);
      if ( v6 )
        (*(void (**)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(v6, 1021, *(_DWORD *)(this + 12), 1);
      v13 = off_5974E0;
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
    }
    return 0;
  }
}

// 0x00440F30
int UIStatic::Render(int _this)
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

  result = *(_DWORD *)(this + 56);
  if ( result )
  {
    v3 = *(_DWORD *)(this + 80);
    if ( *(_DWORD *)(this + 4 * v3 + 84) )
    {
      if ( *(_BYTE *)(this + 100) && *(_DWORD *)(this + 104) && v3 != 1 )
      {
        v4 = (unsigned int *)*(unsigned int **)(this + 108);
        v10.pTexPt[0] = *(gbTexture **)(this + 104);
        v10.nTex = 1;
        v5 = (unsigned int *)(this + 8);
        v6 = (int *)(this + 16);
        ((int *)(this + 16))->SetLibFolder((unsigned int *)(this + 8), &v10, 0x114u, v4, COERCE_FLOAT(1));
      }
      else
      {
        v7 = (gbTexture *)*(gbTexture **)(this + 4 * v3 + 84);
        v10.nTex = 1;
        v10.pTexPt[0] = v7;
        v5 = (unsigned int *)(this + 8);
        v6 = (int *)(this + 16);
        ((int *)(this + 16))->SetLibFolder((unsigned int *)(this + 8), &v10, 0x114u, *(unsigned int **)(this + 4 * v3 + 92), COERCE_FLOAT(1));
      }
      if ( !*(_DWORD *)(this + 60) )
      {
        v8 = (gbTexture *)*(gbTexture **)(this + 112);
        if ( v8 )
        {
          v9 = (unsigned int *)*(unsigned int **)(this + 116);
          v10.nTex = 1;
          v10.pTexPt[0] = v8;
          v6->SetLibFolder(v5, &v10, 0x114u, v9, COERCE_FLOAT(1));
        }
      }
    }
    else
    {
      v6 = (int *)(this + 16);
      ((_TextureLib_Data *)*(_DWORD *)(this + 16))->~_TextureLib_Data(*(_DWORD *)(this + 20), *(_DWORD *)(this + 24), *(_DWORD *)(this + 28), (float *)&g_GameData_0._data[12992]);
    }
    if ( *(_BYTE *)(this + 120) )
      UIRenderPar(this + 120, (int)v6, (_BYTE *)(this + 72), 1, 1);
    return ((UIWnd *)this)->GetID();
  }
  return result;
}
