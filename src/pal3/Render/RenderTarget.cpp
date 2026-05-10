#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/RenderTarget.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/Logger.h"

// Unnamed globals (extern)
extern char aDProjectPal3Ef[];
extern char aLockBackBuffer[];
extern void *off_56F4F0;

// 0x004BDAC0
RenderTarget::RenderTarget()
{
  ((gbTexture_D3D *)&this->m_Texture.InFmt.a_shift)->~gbTexture_D3D();
  ((gbTexture_D3D *)&this->m_Texture)->~gbTexture_D3D();
}

// 0x004BDB60
int RenderTarget::Create()
{
  int result; // eax
  int v3; // [esp+Ch] [ebp-814h] BYREF
  int v4; // [esp+14h] [ebp-80Ch]
  char pExceptionObject[1024]; // [esp+20h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+420h] [ebp-400h] BYREF

  if ( !(*(int (**)(int, int *, int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 84))(
          g_Input.KeyInfo[177].Data,
          &v3,
          1) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aLockBackBuffer, aDProjectPal3Ef, 39),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 88))(g_Input.KeyInfo[177].Data);
  (*(void (**)(__int32 *, int, int, int))(this->m_Texture.InFmt.a_shift + 12))(
    &this->m_Texture.InFmt.a_shift,
    g_Input.KeyInfo[120].Data,
    g_Input.KeyInfo[120].HoldTime,
    v4);
  result = (*(int (**)(gbTexture_D3D *, int, int, int))(*(_DWORD *)this->m_Texture._pad_0000 + 12))(
             &this->m_Texture,
             512,
             512,
             v4);
  this->m_iMode = 0;
  this->m_ScreenPlane.InFmt.g_mask = 0;
  return result;
}

// 0x004BDC10
void RenderTarget::OnDeviceLost(int a2)
{
  int v2; // eax

  if ( this->m_ScreenPlane.InFmt.g_mask != 1 )
  {
    v2 = a2;
    if ( (a2 == 1 || a2 == 2) && !this->m_ScreenPlane.InFmt.Bpp )
      v2 = 0;
    this->m_iMode = v2;
  }
}

// 0x004BDC40
bool RenderTarget::OnResetDevice(int a2)
{
  BOOL v3; // eax
  int m_iMode; // ecx
  int v5; // esi

  if ( this->m_ScreenPlane.InFmt.g_mask != 1 )
  {
    this->m_ScreenPlane.InFmt.g_mask = 1;
    m_iMode = this->m_iMode;
    v5 = 0;
    if ( this->m_iMode )
    {
      if ( m_iMode <= 0 || m_iMode > 2 )
        return v5 != 0;
      v5 = (*(int (**)(int, __int32 *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 92))(
             g_Input.KeyInfo[177].Data,
             &this->m_Texture.InFmt.a_shift);
    }
    else
    {
      v5 = (*(int (**)(int, gbTexture_D3D *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 92))(
             g_Input.KeyInfo[177].Data,
             &this->m_Texture);
      ((gbCamera *)(g_Input.KeyInfo[177].CountMode + 4))->SetDimention(512, 384);
      ((CameraCtrl *)g_Input.KeyInfo[177].CountMode)->SetAsCurrent(3);
    }
    if ( v5 && (_BYTE)a2 )
    {
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)(g_Input.KeyInfo[177].Data
                                                                                         + 1816)
                                                                           + 172))(
        *(_DWORD *)(g_Input.KeyInfo[177].Data + 1816),
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 48))(g_Input.KeyInfo[177].Data);
      PushMatrixStacks();
      a2 = -16777216;
      ((_TextureLib_Data *)0)->~_TextureLib_Data(0, 512, 512, (float *)&a2);
      (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 52))(g_Input.KeyInfo[177].Data);
      PopMatrixStacks();
    }
    return v5 != 0;
  }
  LOBYTE(v3) = 0;
  return v3;
}

// 0x004BDF10
_DWORD * RenderTarget::Destroy()
{
  *(_DWORD *)this->m_Texture._pad_0000 = 0;
  this->m_iMode = (int)&off_56F4F0;
  this->m_Texture.RefCount = 1;
  this->m_Texture.NameCrc32 = 0;
  this->m_Texture.pName = 0;
  LOBYTE(this->m_Texture.IsLoaded) = 0;
  return &this->m_iMode;
}
