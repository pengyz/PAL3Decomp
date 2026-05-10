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
  ((gbTexture_D3D *)this->m_ScreenPlane)->~gbTexture_D3D();
  ((gbTexture_D3D *)this->m_Texture)->~gbTexture_D3D();
}

// 0x004BDB60
int RenderTarget::Create()
{
  int result; // eax
  int v3; // [esp+Ch] [ebp-814h] BYREF
  int v4; // [esp+14h] [ebp-80Ch]
  char pExceptionObject[1024]; // [esp+20h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+420h] [ebp-400h] BYREF

  if ( !(*(int (**)(gbGfxManager *, int *, int))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 84))(g_pGfxMgr, &v3, 1) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aLockBackBuffer, aDProjectPal3Ef, 39),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (**)(gbGfxManager *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 88))(g_pGfxMgr);
  (*(void (**)(char *, double *, double *, int))(*(_DWORD *)this->m_ScreenPlane + 12))(
    this->m_ScreenPlane,
    g_pGameTime,
    g_pAbsTime,
    v4);
  result = (*(int (**)(char *, int, int, int))(*(_DWORD *)this->m_Texture + 12))(
             this->m_Texture,
             512,
             512,
             v4);
  this->m_iMode = 0;
  this->m_nState = 0;
  return result;
}

// 0x004BDC10
void RenderTarget::OnDeviceLost(int a2)
{
  int v2; // eax

  if ( this->m_nState != 1 )
  {
    v2 = a2;
    if ( (a2 == 1 || a2 == 2) && !*(_DWORD *)&this->m_ScreenPlane[84] )
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

  if ( this->m_nState != 1 )
  {
    this->m_nState = 1;
    m_iMode = this->m_iMode;
    v5 = 0;
    if ( this->m_iMode )
    {
      if ( m_iMode <= 0 || m_iMode > 2 )
        return v5 != 0;
      v5 = (*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 92))(
             g_pGfxMgr,
             this->m_ScreenPlane);
    }
    else
    {
      v5 = (*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 92))(
             g_pGfxMgr,
             this->m_Texture);
      ((gbCamera *)((char *)g_pCameraCtrl + 4))->SetDimention(512, 384);
      g_pCameraCtrl->SetAsCurrent(3);
    }
    if ( v5 && (_BYTE)a2 )
    {
      (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)&g_pGfxMgr[1].DrvInfo.winname[44]
                                                                           + 172))(
        *(_DWORD *)&g_pGfxMgr[1].DrvInfo.winname[44],
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      (*(void (**)(gbGfxManager *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 48))(g_pGfxMgr);
      PushMatrixStacks();
      a2 = -16777216;
      ((_TextureLib_Data *)0)->~_TextureLib_Data(0, 512, 512, (float *)&a2);
      (*(void (**)(gbGfxManager *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 52))(g_pGfxMgr);
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
  *(_DWORD *)this->m_Texture = 0;
  this->m_iMode = (int)&off_56F4F0;
  *(_DWORD *)&this->m_Texture[4] = 1;
  *(_DWORD *)&this->m_Texture[12] = 0;
  *(_DWORD *)&this->m_Texture[8] = 0;
  this->m_Texture[16] = 0;
  return &this->m_iMode;
}
