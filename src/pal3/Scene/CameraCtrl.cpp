#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CameraCtrl.h"

// 0x0041C1B0
int CameraCtrl::InitParams(void *pParams)
{
  int result; // eax

  *((_DWORD *)this + 95) = 0;
  *((_DWORD *)this + 96) = 0;
  *((_DWORD *)this + 97) = *(_DWORD *)pParams;
  *((_DWORD *)this + 98) = *((_DWORD *)pParams + 1);
  result = *((_DWORD *)pParams + 2);
  *((_DWORD *)this + 99) = result;
  return result;
}

// 0x0041C630
void CameraCtrl::SetAsCurrent(int flags)
{
  if ( (flags & 2) != 0 )
    ((gbCamera *)((char *)this + 4))->SetLookAt((CameraCtrl *)((char *)this + 492), (CameraCtrl *)((char *)this + 480), (CameraCtrl *)((char *)this + 516));
  ((gbCamera *)((char *)this + 4))->SetAsCurrent(flags);
}

// 0x0041CA90
void CameraCtrl::SetDimention(int w, int h)
{
  *((_DWORD *)this + 118) = w;
  *((_DWORD *)this + 119) = h;
  ((gbCamera *)((char *)this + 4))->SetDimention(w, h);
}

// 0x0041CAC0
void * CameraCtrl::GetViewTarget(void *pTarget, float *pPos)
{
  int *v3; // ecx
  double v4; // st7
  double v5; // st6
  float v7; // [esp+8h] [ebp-20h]
  float v8; // [esp+Ch] [ebp-1Ch]
  _DWORD v9[6]; // [esp+10h] [ebp-18h] BYREF

  v3 = (int *)((char *)this + 4);
  v4 = (double)*(int *)pPos;
  v5 = (double)v3[117];
  memset(v9, 0, sizeof(v9));
  v7 = v4 / (v5 * 0.5) - 1.0;
  v8 = 1.0 - (double)*((int *)pPos + 1) / ((double)v3[118] * 0.5);
  ((gbCamera *)v3)->GetRayToScreen(v7, v8, (struct gbRay *)v9);
  qmemcpy(pTarget, v9, 0x18u);
  return pTarget;
}

// 0x0041D5B0
int CameraCtrl::SetCamMode(int mode)
{
  *((_DWORD *)this + 115) = mode;
  return mode;
}
