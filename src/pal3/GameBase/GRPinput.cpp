#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/GRPinput.h"

// Forward declarations for unnamed functions
int sub_402220(...);
int sub_402640(...);

// Unnamed globals (extern)
extern int unk_573800;
extern int unk_573810;
extern int unk_573A5C;
extern int unk_573C64;

// 0x004020E0
int GRPinput::Create(void *hInst, int hwnd, int flag)
{
  IDirectInputDevice8A **p_m_lpDIDMouse; // edi
  IDirectInputDevice8A *v7; // edi
  IDirectInputDevice8A **p_m_lpDIDKeyboard; // edi

  if ( DirectInput8Create((HINSTANCE)hInst, 0x800u, &riidltf, (LPVOID *)&this->m_lpDI, 0) )
    return 0;
  p_m_lpDIDMouse = &this->m_lpDIDMouse;
  if ( !(*(int (__stdcall **)(IDirectInput8A *, void *, IDirectInputDevice8A **, _DWORD))(*(_DWORD *)this->m_lpDI + 12))(
          this->m_lpDI,
          &unk_573810,
          &this->m_lpDIDMouse,
          0) )
  {
    (*(void (__stdcall **)(IDirectInputDevice8A *, void *))(*(_DWORD *)*p_m_lpDIDMouse + 44))(
      *p_m_lpDIDMouse,
      &unk_573C64);
    v7 = (IDirectInputDevice8A *)*p_m_lpDIDMouse;
    if ( flag )
      (*(void (__stdcall **)(IDirectInputDevice8A *, int, int))(*(_DWORD *)v7 + 52))(v7, hwnd, 5);
    else
      (*(void (__stdcall **)(IDirectInputDevice8A *, int, int))(*(_DWORD *)v7 + 52))(v7, hwnd, 6);
    this->AcquireDevices();
    if ( !this->m_shiftedKeyStates[201] )
      return 0;
  }
  p_m_lpDIDKeyboard = &this->m_lpDIDKeyboard;
  if ( !(*(int (__stdcall **)(IDirectInput8A *, void *, IDirectInputDevice8A **, _DWORD))(*(_DWORD *)this->m_lpDI + 12))(
          this->m_lpDI,
          &unk_573800,
          &this->m_lpDIDKeyboard,
          0) )
  {
    (*(void (__stdcall **)(IDirectInputDevice8A *, void *))(*(_DWORD *)*p_m_lpDIDKeyboard + 44))(
      *p_m_lpDIDKeyboard,
      &unk_573A5C);
    (*(void (__stdcall **)(IDirectInputDevice8A *, int, int))(*(_DWORD *)*p_m_lpDIDKeyboard + 52))(
      *p_m_lpDIDKeyboard,
      hwnd,
      6);
    this->ReleaseDevices();
    if ( !this->m_shiftedKeyStates[202] )
      return 0;
    sub_402640(this);
    ((int)this)->Create();
  }
  GetCursorPos(&this->m_mousept);
  return 1;
}

// 0x00402270
int GRPinput::SetMouseLimits(int a, int b, int c, int d)
{
  this->m_mouseMinX = a;
  this->m_mouseMinY = b;
  this->m_mouseMaxX = c;
  this->m_mouseMaxY = d;
  return c;
}

// 0x004022B0
int GRPinput::SetMode(int mode)
{
  LODWORD(this->m_mouseSensitivity) = mode;
  return mode;
}

// 0x004022C0
__int16 GRPinput::GetKeyState(unsigned __int16 key)
{
  return *((unsigned __int8 *)this->m_keyStates + key);
}

// 0x004022E0
BOOL GRPinput::GetCursorPos(void *pPoint)
{
  return GetCursorPos((LPPOINT)pPoint);
}

// 0x004022F0
int GRPinput::GetMousePos(void *pOut, void *pOut2)
{
  int result; // eax

  *(_DWORD *)pOut = this->m_mouseDeltaX;
  result = this->m_mouseDeltaY;
  *(_DWORD *)pOut2 = result;
  return result;
}

// 0x00402310
int GRPinput::AcquireDevices()
{
  int result; // eax
  int v3; // edi

  result = (int)this->m_lpDIDMouse;
  if ( result )
  {
    this->m_shiftedKeyStates[201] = 1;
    result = (*(int (__stdcall **)(int))(*(_DWORD *)result + 28))(result);
    if ( result )
    {
      v3 = 0;
      while ( 1 )
      {
        result = (*(int (__stdcall **)(IDirectInputDevice8A *))(*(_DWORD *)this->m_lpDIDMouse + 28))(this->m_lpDIDMouse);
        if ( !result )
          break;
        if ( ++v3 >= 50 )
        {
          this->m_shiftedKeyStates[201] = 0;
          return result;
        }
      }
    }
  }
  return result;
}

// 0x00402380
int GRPinput::ReleaseDevices()
{
  int result; // eax
  int v3; // edi

  result = (int)this->m_lpDIDKeyboard;
  if ( result )
  {
    this->m_shiftedKeyStates[202] = 1;
    if ( (*(int (__stdcall **)(int))(*(_DWORD *)result + 28))(result) )
    {
      v3 = 0;
      while ( 1 )
      {
        result = (*(int (__stdcall **)(IDirectInputDevice8A *))(*(_DWORD *)this->m_lpDIDKeyboard + 28))(this->m_lpDIDKeyboard);
        if ( !result )
          break;
        if ( ++v3 >= 50 )
        {
          this->m_shiftedKeyStates[202] = 0;
          return result;
        }
      }
    }
    return sub_402220(this);
  }
  return result;
}

// 0x00402B00
char GRPinput::SetJoystickAbs()
{
  int v1; // edx
  __int32 *v2; // ecx
  char result; // al

  v1 = 0;
  v2 = (__int32 *)&this->m_shiftedKeyStates[204];
  result = 1;
  while ( v2[3] != 1 || (*(_BYTE *)v2 & 3) == 0 )
  {
    ++v1;
    v2 += 4;
    if ( v1 >= 270 )
      return 0;
  }
  return result;
}
