#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/GRPinput.h"

// Forward declarations for unnamed functions
int sub_402220(...);
int sub_402640(...);
int sub_403B80(...);

// Unnamed globals (extern)
extern unsigned char byte_56A634;
extern unsigned char byte_8AC5D8;
extern int dword_C116EC;
extern float flt_8ACBEC;
extern void *off_56A620;
extern void *off_580CFC;
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
    if ( !this->m_bMouse )
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
    if ( !this->m_bKeyboard )
      return 0;
    sub_402640(this);
    this->Create();
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
  return this->m_keyStates[key];
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
    this->m_bMouse = 1;
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
          this->m_bMouse = 0;
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
    this->m_bKeyboard = 1;
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
          this->m_bKeyboard = 0;
          return result;
        }
      }
    }
    return sub_402220(this);
  }
  return result;
}

// 0x00402400
GRPinput::GRPinput()
{
  unsigned __int8 *m_keyRaw; // edi
  int m_bMouse; // eax
  int *m_DIKToKEY; // ebx
  int v5; // ebp
  int y; // edi
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // edi
  char *v11; // ebx
  int v12; // ebp
  struct tagPOINT Point; // [esp+18h] [ebp-8h] BYREF

  if ( this->m_bKeyboard )
  {
    m_keyRaw = (unsigned __int8 *)this->m_keyRaw;
    if ( (*(int (__stdcall **)(IDirectInputDevice8A *, int, unsigned __int8 *))(*(_DWORD *)this->m_lpDIDKeyboard + 36))(
           this->m_lpDIDKeyboard,
           256,
           this->m_keyRaw) )
    {
      LOBYTE(m_bMouse) = this->ReleaseDevices();
  (GRPinput *)(char)m_bMouse;
    }
    m_DIKToKEY = (int *)this->m_DIKToKEY;
    v5 = 256;
    do
    {
      if ( *m_DIKToKEY )
        this->~GRPinput(*m_DIKToKEY, *m_keyRaw >> 7);
      ++m_DIKToKEY;
      ++m_keyRaw;
      --v5;
    }
    while ( v5 );
  }
  m_bMouse = this->m_bMouse;
  if ( m_bMouse )
  {
    if ( (*(int (__stdcall **)(IDirectInputDevice8A *, int, char *))(*(_DWORD *)this->m_lpDIDMouse + 36))(
           this->m_lpDIDMouse,
           20,
           this->MouseState) )
    {
      LOBYTE(m_bMouse) = this->AcquireDevices();
    }
    else
    {
      GetCursorPos(&Point);
      y = this->m_mousept.y;
      v7 = Point.x - this->m_mousept.x;
      this->m_mousept.x = Point.x;
      this->m_mouseDeltaX = v7;
      v8 = Point.y;
      this->m_mousept.y = Point.y;
      v9 = v8 - y;
      v10 = 256;
      this->m_mouseDeltaY = v9;
      v11 = (char *)&this->MouseState[12];
      v12 = 3;
      do
      {
        LOBYTE(m_bMouse) = this->~GRPinput(v10++, (unsigned __int8)*v11++ >> 7);
        --v12;
      }
      while ( v12 );
    }
  }
  (GRPinput *)(char)m_bMouse;
}

// 0x004024F0
GRPinput::~GRPinput()
{
  int m_mouseFreeX; // eax

  if ( a3 )
  {
    LOBYTE(m_mouseFreeX) = this->m_keyStates[a2];
    if ( (unsigned __int8)m_mouseFreeX < 2u )
    {
      this->m_keyStates[a2] = 2;
      this->m_keyPressTimes[a2] = timeGetTime();
      m_mouseFreeX = this->m_mouseFreeX;
      this->m_keyDragStartPositions[0][2 * a2] = m_mouseFreeX;
      this->m_keyDragStartPositions[0][2 * a2 + 1] = this->m_mouseFreeY;
    }
    else if ( (_BYTE)m_mouseFreeX == 2 )
    {
      this->m_keyStates[a2] = 3;
    }
  }
  else
  {
    m_mouseFreeX = this->m_keyStates[a2];
    if ( (_BYTE)m_mouseFreeX == 3 || (_BYTE)m_mouseFreeX == 2 )
    {
      this->m_keyStates[a2] = 1;
    }
    else if ( (_BYTE)m_mouseFreeX == 1 )
    {
      this->m_keyStates[a2] = 0;
    }
  }
  m_mouseFreeX;
}

// 0x00402570
int GRPinput::Create()
{
  int result; // eax
  unsigned __int8 *v3; // esi
  unsigned __int8 v4; // cl

  memset(this->m_shiftedKeyStates, 0, 0x10Cu);
  *(_WORD *)&this->m_shiftedKeyStates[268] = 0;
  result = 0;
  v3 = (unsigned __int8 *)&this->m_shiftedKeyStates[97];
  do
  {
    v4 = result++ + 65;
    *v3++ = v4;
  }
  while ( (unsigned __int16)result < 0x1Au );
  this->m_shiftedKeyStates[61] = 43;
  this->m_shiftedKeyStates[91] = 123;
  this->m_shiftedKeyStates[93] = 125;
  this->m_shiftedKeyStates[92] = 124;
  this->m_shiftedKeyStates[59] = 58;
  this->m_shiftedKeyStates[39] = 34;
  qmemcpy(&this->m_shiftedKeyStates[44], "<_>?)!@#$%^&*(", 14);
  this->m_shiftedKeyStates[96] = 126;
  return result;
}

// 0x00402A90
int GRPinput::SetMouseAbs(int a2, int a3, int a4)
{
  GRP_KEYREG *v4; // eax
  int HoldTime; // ecx
  int v7; // ecx
  int PressTime; // ecx

  v4 = (GRP_KEYREG *)&this->KeyInfo[a3];
  if ( a4 )
  {
    if ( this->KeyInfo[a3].HoldTime )
    {
      v7 = this->KeyTransformation[this->KeyInfo[a3].CountMode];
      v4->PressTime = 0;
      v4->Data = v7;
      v4->CountMode = v7;
    }
    PressTime = v4->PressTime;
    v4->HoldTime = 0;
    v4->PressTime = PressTime + 1;
  }
  else
  {
    HoldTime = this->KeyInfo[a3].HoldTime;
    v4->PressTime = 0;
    if ( !HoldTime )
    {
      v4->HoldTime = a2;
      return 0;
    }
    v4->Data = 0;
    if ( (unsigned int)(a2 - HoldTime) > 0x64 )
    {
      v4->CountMode = 0;
      return v4->PressTime;
    }
  }
  return v4->PressTime;
}

// 0x00402B00
char GRPinput::SetJoystickAbs()
{
  int v1; // edx
  GRP_KEYREG *KeyInfo; // ecx
  char result; // al

  v1 = 0;
  KeyInfo = (GRP_KEYREG *)this->KeyInfo;
  result = 1;
  while ( KeyInfo->PressTime != 1 || (KeyInfo->Data & 3) == 0 )
  {
    ++v1;
    ++KeyInfo;
    if ( v1 >= 270 )
      return 0;
  }
  return result;
}

// 0x00402B60
// attributes: thunk
int GRPinput::RunJoystickControlPanel()
{
  return GRPinput::ClearKeyBuffer();
}

// 0x00402B70
int GRPinput::ClearKeyBuffer()
{
  *(_DWORD *)&byte_8AC5D8[908] = 1094713344;
  return 1094713344;
}

// 0x00402B80
// attributes: thunk
void GRPinput::SetMouseLimits()
{
  GRPinput::SetJoystickLimits();
}

// 0x00402B90
void GRPinput::SetJoystickLimits()
{
  *(float *)&byte_8AC5D8[904] = 12.0 + 12.0;
}

// 0x00402BA0
int GRPinput::SetMousePos(int a1)
{
  *(_BYTE *)(a1 + 8) = HIBYTE(a1);
  *(_DWORD *)(a1 + 12) = 0;
  *(_DWORD *)(a1 + 16) = 0;
  *(_DWORD *)(a1 + 20) = 0;
  *(_DWORD *)a1 = &off_56A620;
  *(_BYTE *)(a1 + 4) = 0;
  *(_DWORD *)(a1 + 24) = 0;
  *(_DWORD *)(a1 + 28) = 0;
  *(_DWORD *)(a1 + 32) = 10;
  return a1;
}

// 0x00402BF0
void GRPinput::SetMouseFreePos()
{
  float m_mouseSensitivity; // eax
  _BYTE *v3; // ecx
  char v4; // al

  this->m_lpDI = (IDirectInput8A *)&off_56A620;
  m_mouseSensitivity = this->m_mouseSensitivity;
  if ( m_mouseSensitivity != 0.0 )
  {
    v3 = (_BYTE *)(LODWORD(m_mouseSensitivity) - 1);
    v4 = *(_BYTE *)(LODWORD(m_mouseSensitivity) - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      * v3 = (*)v4 - 1;
  }
  this->m_mouseSensitivity = 0.0;
  this->m_mouseMinX = 0;
  this->m_mouseMinY = 0;
}

// 0x00402C40
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char GRPinput::SetJoystickPos(const char *a2, int a3)
{
  GRPinput *v3; // esi
  unsigned int v4; // kr04_4
  IDirectInputDevice8A **p_m_lpDIDMouse; // ebp
  unsigned int v6; // ebx
  float m_mouseSensitivity; // ecx
  char v8; // al
  char result; // al
  unsigned int m_mouseMinY; // eax
  float v11; // ecx
  int v12; // [esp+0h] [ebp-14h]

  v3 = this;
  LOBYTE(this->m_lpDIDKeyboard) = 1;
  v4 = strlen(a2) + 1;
  p_m_lpDIDMouse = &v3->m_lpDIDMouse;
  v6 = v4 - 1;
  if ( v4 - 1 > 0xFFFFFFFD )
    v12->_Xlen();
  m_mouseSensitivity = v3->m_mouseSensitivity;
  if ( m_mouseSensitivity == 0.0 || (v8 = *(_BYTE *)(LODWORD(m_mouseSensitivity) - 1)) == 0 || v8 == -1 )
  {
    if ( v4 == 1 )
    {
      ((std *)&v3->m_lpDIDMouse)->string::_Tidy(1);
      goto LABEL_15;
    }
    m_mouseMinY = v3->m_mouseMinY;
    if ( m_mouseMinY <= 0x1F && m_mouseMinY >= v6 )
    {
LABEL_14:
      result = v4 - 1;
      qmemcpy((void *)LODWORD(v3->m_mouseSensitivity), a2, v6);
      v11 = v3->m_mouseSensitivity;
      v3 = this;
      p_m_lpDIDMouse[2] = (IDirectInputDevice8A *)v6;
      *(_BYTE *)(LODWORD(v11) + v6) = 0;
      goto LABEL_15;
    }
    ((std *)&v3->m_lpDIDMouse)->string::_Tidy(1);
LABEL_13:
    ((GRPinput *)&v3->m_lpDIDMouse)->GetKeyState(v6);
    goto LABEL_14;
  }
  if ( v4 != 1 )
    goto LABEL_13;
  result = v8 - 1;
  *(_BYTE *)(LODWORD(m_mouseSensitivity) - 1) = result;
  v3->m_mouseSensitivity = 0.0;
  v3->m_mouseMinX = 0;
  v3->m_mouseMinY = 0;
LABEL_15:
  v3->m_mouseMaxX = 0;
  v3->m_mouseMaxY = a3;
  v3->m_joystickMinX = 40;
  return result;
}

// 0x00402D00
char GRPinput::SetJoystickFreePos(float a2)
{
  char result; // al

  result = (char)this->m_lpDIDKeyboard;
  if ( result )
    *(float *)&this->m_mouseMaxX = a2 + *(float *)&this->m_mouseMaxX;
  return result;
}

// 0x00402D20
char GRPinput::SetMouseSensitivity()
{
  int v2; // eax
  int m_mouseMaxY; // eax
  double v4; // st7
  gbPrintFont *v5; // edi
  double v6; // st7
  double v7; // st7
  float m_mouseSensitivity; // esi
  double v9; // st7
  __int64 v10; // rax
  double v11; // st7
  gbPrintFont *v12; // edi
  float v13; // esi
  float v15; // [esp+10h] [ebp-38h]
  float v16; // [esp+10h] [ebp-38h]
  float v17; // [esp+14h] [ebp-34h]
  float v18; // [esp+28h] [ebp-20h]
  int v19; // [esp+28h] [ebp-20h]
  signed int v20; // [esp+2Ch] [ebp-1Ch] BYREF
  int m_joystickMinX; // [esp+30h] [ebp-18h]
  gbColorQuad v22; // [esp+34h] [ebp-14h] BYREF
  float v23; // [esp+40h] [ebp-8h]
  int v24; // [esp+44h] [ebp-4h]

  LOBYTE(v2) = this->m_lpDIDKeyboard;
  if ( (_BYTE)v2 )
  {
    m_mouseMaxY = this->m_mouseMaxY;
    if ( m_mouseMaxY )
    {
      v2 = m_mouseMaxY - 1;
      if ( !v2 )
      {
        m_joystickMinX = this->m_joystickMinX;
        v4 = 40.0 / (double)(int)g_pAbsTime;
        v5 = (gbPrintFont *)g_pGfxMgr->pFontMgr->pAllFont[2];
        v20 = ((unsigned int)g_pGameTime - 10 * this->m_mouseMinX) >> 1;
        *(float *)&v5->curColor.Blue = 40.0 / (double)(int)g_pGameTime;
        *(float *)&v5->curColor.Color = v4;
        v6 = *(float *)&this->m_mouseMaxX - 1.5;
        if ( v6 < 0.0 )
          v6 = 0.0;
        v7 = 1.0 - v6 * 0.40000001;
        if ( v7 < 0.0 )
          v7 = 0.0;
        HIBYTE(v22.ColorQuadFmt) = (__int64)(v7 * 255.0);
        if ( !HIBYTE(v22.ColorQuadFmt) )
          LOBYTE(this->m_lpDIDKeyboard) = 0;
        v5->curColor.ColorQuadFmt = ((gbColorQuad *)&v22)->gbColorQuad(0xFFu, 0xFFu, 0xFFu, HIBYTE(v22.ColorQuadFmt))->ColorQuadFmt;
        m_mouseSensitivity = this->m_mouseSensitivity;
        if ( m_mouseSensitivity == 0.0 )
          m_mouseSensitivity = COERCE_FLOAT(byte_56A634);
        v17 = 1.0 - ((double)m_joystickMinX + (double)m_joystickMinX) / (double)(int)g_pAbsTime;
        v15 = ((double)v20 + (double)v20) / (double)(int)g_pGameTime - 1.0;
        (*(void (**)(gbPrintFont *, float, _DWORD, _DWORD, int, int))(*(_DWORD *)v5->_pad_0000 + 16))(
          v5,
          COERCE_FLOAT(LODWORD(m_mouseSensitivity)),
          LODWORD(v15),
          LODWORD(v17),
          1176256512,
          1176256512);
        LOBYTE(v2) = (*(char (**)(gbPrintFont *))(*(_DWORD *)v5->_pad_0000 + 8))(v5);
      }
    }
    else
    {
      LOBYTE(v2) = (_BYTE)dword_C116EC;
      v18 = *(float *)&this->m_mouseMaxX * 0.40000001;
      if ( dword_C116EC )
      {
        v22.Color = *((_DWORD *)dword_C116EC + 40);
        v23 = *((float *)dword_C116EC + 41);
        v24 = *((_DWORD *)dword_C116EC + 42);
        v23 = v18 * 20.0 + v23 + 64.0;
        ((gbCamera *)((char *)g_pCameraCtrl + 4))->PointWorldToScr((struct gbVec3D *)&v22.Color, (float *)&v22.ColorQuadFmt, (float *)&v20);
        v9 = 1.0 - v18;
        if ( v9 < 0.0 )
          v9 = 0.0;
        v10 = (__int64)(v9 * 255.0);
        if ( !(_BYTE)v10 )
          LOBYTE(this->m_lpDIDKeyboard) = 0;
        v11 = 32.0 / (double)(int)g_pAbsTime;
        v12 = (gbPrintFont *)g_pGfxMgr->pFontMgr->pAllFont[3];
        *(float *)&v12->curColor.Blue = 32.0 / (double)(int)g_pGameTime;
        *(float *)&v12->curColor.Color = v11;
        if ( gbColorQuad::ColorQuadFmt )
        {
          *(_WORD *)((char *)&v19 + 1) = -6636;
          LOBYTE(v19) = 20;
        }
        else
        {
          LOBYTE(v19) = -26;
          *(_WORD *)((char *)&v19 + 1) = 5140;
        }
        HIBYTE(v19) = v10;
        v12->curColor.ColorQuadFmt = v19;
        v13 = this->m_mouseSensitivity;
        if ( v13 == 0.0 )
          v13 = COERCE_FLOAT(byte_56A634);
        v16 = *(float *)&v22.ColorQuadFmt - 0.1;
        (*(void (**)(gbPrintFont *, float, _DWORD, signed int, int, int))(*(_DWORD *)v12->_pad_0000 + 16))(
          v12,
          COERCE_FLOAT(LODWORD(v13)),
          LODWORD(v16),
          v20,
          1176256512,
          1176256512);
        LOBYTE(v2) = (*(char (**)(gbPrintFont *))(*(_DWORD *)v12->_pad_0000 + 8))(v12);
      }
    }
  }
  return v2;
}

// 0x00402FA0
int GRPinput::GetMouseSensitivity(int a2)
{
  this->m_joystickMinX = a2;
  return a2;
}

// 0x00403000
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_BYTE * GRPinput::GetKeyState(unsigned int a2)
{
  IDirectInputDevice8A *v2; // esi
  size_t v4; // eax
  IDirectInputDevice8A *m_lpDIDMouse; // eax
  IDirectInputDevice8A *m_lpDIDKeyboard; // eax
  IDirectInputDevice8A *v7; // edi
  IDirectInputDevice8A *v8; // ecx
  IDirectInputDevice8A v9; // al
  _BYTE *result; // eax
  IDirectInputDevice8A *v11; // ecx
  _DWORD v12[4]; // [esp+0h] [ebp-24h] BYREF
  unsigned int v13; // [esp+10h] [ebp-14h]
  _DWORD *v14; // [esp+14h] [ebp-10h]
  int v15; // [esp+20h] [ebp-4h]
  _DWORD *v16; // [esp+2Ch] [ebp+8h]

  v2 = (IDirectInputDevice8A *)(a2 | 0x1F);
  v14 = v12;
  v12[3] = this;
  v13 = a2 | 0x1F;
  if ( (a2 | 0x1F) > 0xFFFFFFFD )
  {
    v13 = a2;
    v2 = (IDirectInputDevice8A *)a2;
  }
  v4 = (size_t)&v2[2];
  v15 = 0;
  if ( (int)&v2[2] < 0 )
    v4 = 0;
  v16 = (_DWORD *)operator new(v4);
  m_lpDIDMouse = (IDirectInputDevice8A *)this->m_lpDIDMouse;
  if ( m_lpDIDMouse )
  {
    if ( m_lpDIDMouse > v2 )
      m_lpDIDMouse = v2;
    qmemcpy((char *)v16 + 1, this->m_lpDIDKeyboard, (unsigned int)m_lpDIDMouse);
    v2 = (IDirectInputDevice8A *)v13;
  }
  m_lpDIDKeyboard = (IDirectInputDevice8A *)this->m_lpDIDKeyboard;
  v7 = (IDirectInputDevice8A *)this->m_lpDIDMouse;
  if ( m_lpDIDKeyboard )
  {
    v8 = (IDirectInputDevice8A *)m_lpDIDKeyboard - 1;
    v9 = m_lpDIDKeyboard[-1];
    if ( !*(_BYTE *)&v9 || v9 == 0xFF )
      operator delete(v8);
    else
      *v8 = (IDirectInputDevice8A)(*(_BYTE *)&v9 - 1);
  }
  this->m_lpDIDMouse = 0;
  result = (char *)v16 + 1;
  this->m_lpDIDKeyboard = (IDirectInputDevice8A *)v16 + 1;
  *(_BYTE *)v16 = 0;
  LODWORD(this->m_mouseSensitivity) = v2;
  if ( v7 <= v2 )
    v2 = v7;
  v11 = (IDirectInputDevice8A *)this->m_lpDIDKeyboard;
  this->m_lpDIDMouse = v2;
  v2[(_DWORD)v11] = 0;
  return result;
}

// 0x00403140
// attributes: thunk
int GRPinput::GetMousePos()
{
  return GRPinput::GetMouseFreePos();
}

// 0x00403150
int GRPinput::GetMouseFreePos()
{
  flt_8ACBEC = 12.0;
  return 1094713344;
}

// 0x00403160
// attributes: thunk
void GRPinput::GetMouseDeltas()
{
  GRPinput::GetJoystickPos();
}

// 0x00403170
void GRPinput::GetJoystickPos()
{
  *(float *)&byte_8AC5D8[1552] = 12.0 + 12.0;
}

// 0x00403180
BOOL GRPinput::GetJoystickFreePos(int a2, int a3)
{
  int v3; // eax

  if ( a2 >= 0 && (v3 = *(_DWORD *)&this->m_keyStates[48], a2 < v3) && a3 >= 0 && a3 < *(_DWORD *)&this->m_keyStates[52] )
    return *(_BYTE *)(*(_DWORD *)&this->m_keyStates[56] + 8 * (a2 + a3 * v3) + 4) > 1u;
  else
    return 0;
}

// 0x00403370
char * GRPinput::AcquireMouse()
{
  `eh vector constructor iterator'(
    (char *)&this->m_lpDIDKeyboard,
    0xA4u,
    2,
    (void (*)(void *))GRPinput::UnacquireJoystick,
    (void (*)(void *))GRPinput::AcquireKeyboard);
  `eh vector constructor iterator'(
    (char *)&this->m_keyStates[228],
    0x10u,
    2,
    (void (*)(void *))GRPinput::UnacquireMouse,
    (void (*)(void *))GRPinput::AcquireJoystick);
  memset(this, 0, 0x16Cu);
  return (char *)this;
}

// 0x004033F0
void GRPinput::UnacquireMouse()
{
  this->m_lpDI = 0;
  this->m_lpDIDKeyboard = 0;
  this->m_lpDIDMouse = 0;
  this->m_mouseSensitivity = 0.0;
}

// 0x00403410
void GRPinput::AcquireJoystick()
{
  void *v2; // edi

  if ( *((_DWORD *)this + 1) )
  {
    free(*((_DWORD *)this + 1));
    *((_DWORD *)this + 1) = 0;
  }
  if ( *((_DWORD *)this + 2) )
  {
    free(*((_DWORD *)this + 2));
    *((_DWORD *)this + 2) = 0;
  }
  v2 = (void *)*((_DWORD *)this + 3);
  if ( v2 )
  {
    ((GRPinput *)*((_DWORD *)this + 3))->GetCharKey();
    operator delete(v2);
    *((_DWORD *)this + 3) = 0;
  }
  *this = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 0;
  *((_DWORD *)this + 3) = 0;
}

// 0x00403470
void GRPinput::UnacquireJoystick()
{
  *(_DWORD *)&this->m_keyStates[24] = 0;
  *(_DWORD *)&this->m_keyStates[28] = 0;
  *(_DWORD *)&this->m_keyStates[32] = 0;
  *(_DWORD *)&this->m_keyStates[36] = 0;
  *(_DWORD *)&this->m_keyStates[40] = 0;
  *(_DWORD *)&this->m_keyStates[44] = 0;
  memset(this, 0, 0xA4u);
}

// 0x004034B0
void GRPinput::AcquireKeyboard()
{
  if ( *((_DWORD *)this + 40) )
    free(*((_DWORD *)this + 40));
  memset(this, 0, 0xA4u);
}

// 0x004034E0
void GRPinput::UnacquireKeyboard()
{
  this->Update();
  `eh vector destructor iterator'(
    (char *)&this->m_keyStates[228],
    0x10u,
    2,
    (void (*)(void *))GRPinput::AcquireJoystick);
  `eh vector destructor iterator'(
    (char *)&this->m_lpDIDKeyboard,
    0xA4u,
    2,
    (void (*)(void *))GRPinput::AcquireKeyboard);
}

// 0x00403560
int GRPinput::Update()
{
  unsigned __int8 *v2; // esi
  void **v3; // ebx
  void *v4; // edi
  unsigned __int8 *v5; // ecx
  int result; // eax
  int v7; // [esp+4h] [ebp-4h]

  v7 = 0;
  if ( (int)this->m_lpDI <= 0 )
  {
    this->m_lpDI = 0;
  }
  else
  {
    v2 = (unsigned __int8 *)&this->m_keyStates[236];
    v3 = (void **)&this->m_keyStates[60];
    do
    {
      if ( *v3 )
        free(*v3);
      memset(v3 - 40, 0, 0xA4u);
      if ( *((_DWORD *)v2 - 1) )
      {
        free(*((void **)v2 - 1));
        *((_DWORD *)v2 - 1) = 0;
      }
      if ( *(_DWORD *)v2 )
      {
        free(*(void **)v2);
        *(_DWORD *)v2 = 0;
      }
      v4 = (void *)*((_DWORD *)v2 + 1);
      if ( v4 )
      {
        ((GRPinput *)*((GRPinput **)v2 + 1))->GetCharKey();
        operator delete(v4);
        *((_DWORD *)v2 + 1) = 0;
      }
      v5 = (unsigned __int8 *)v2 - 8;
      v3 += 41;
      v2 += 16;
      *(_DWORD *)v5 = 0;
      *((_DWORD *)v5 + 1) = 0;
      *((_DWORD *)v5 + 2) = 0;
      *((_DWORD *)v5 + 3) = 0;
      result = ++v7;
    }
    while ( v7 < (int)this->m_lpDI );
    this->m_lpDI = 0;
  }
  return result;
}

// 0x00403640
void GRPinput::CheckKeyEvents(const char *a2)
{
  GRPinput *v2; // ebx
  struct gbVFile *v3; // edi
  int v4; // ecx
  unsigned __int8 *v5; // ebx
  size_t v6; // esi
  void *v7; // eax
  unsigned __int8 *v8; // esi
  size_t v9; // ebx
  void *v10; // eax
  size_t v11; // ebx
  void *v12; // eax
  _DWORD *v13; // eax
  GRPinput *Key; // eax
  int v16; // [esp+ACh] [ebp-1Ch] BYREF
  char v17; // [esp+B0h] [ebp-18h]
  _BYTE v18[5]; // [esp+B1h] [ebp-17h]
  int v19; // [esp+B6h] [ebp-12h]
  int v20; // [esp+C4h] [ebp-4h]
  const char *a2a; // [esp+CCh] [ebp+4h]
  const char *a2b; // [esp+CCh] [ebp+4h]

  v2 = this;
  this->Update();
  v3 = (struct gbVFile *)g_pVFileSys->OpenFile(a2, 0x201u);
  if ( v3 )
  {
    g_pVFileSys->Read(&v16, 0xEu, v3);
    if ( !strcmp((const char *)&v16, (const char *)&off_580CFC) && (v17 == 1 || v17 == 2) )
    {
      v4 = *(_DWORD *)&v18[1];
      v2->m_lpDI = (IDirectInput8A *)v18[0];
      g_pVFileSys->Seek(v3, v4, 1);
      a2a = 0;
      if ( (int)v2->m_lpDI > 0 )
      {
        v5 = (unsigned __int8 *)&v2->m_keyStates[40];
        do
        {
          if ( v17 == 2 )
            g_pVFileSys->Read(v5 - 140, 0x80u, v3);
          g_pVFileSys->Read(v5, 0xCu, v3);
          g_pVFileSys->Read(v5 - 12, 0xCu, v3);
          g_pVFileSys->Read(v5 + 12, 4u, v3);
          g_pVFileSys->Read(v5 + 16, 4u, v3);
          v6 = 8 * *((_DWORD *)v5 + 3) * *((_DWORD *)v5 + 4);
          v7 = (void *)malloc(v6);
          *((_DWORD *)v5 + 5) = v7;
          if ( v7 )
            g_pVFileSys->Read(v7, v6, v3);
          v5 += 164;
          ++a2a;
        }
        while ( (int)a2a < (int)this->m_lpDI );
        v2 = this;
      }
      g_pVFileSys->Seek(v3, v19, 1);
      a2b = 0;
      if ( (int)v2->m_lpDI > 0 )
      {
        v8 = (unsigned __int8 *)&v2->m_keyStates[228];
        do
        {
          g_pVFileSys->Read(v8, 2u, v3);
          g_pVFileSys->Read(v8 + 2, 2u, v3);
          v9 = 12 * *(unsigned __int16 *)v8;
          v10 = (void *)malloc(v9);
          *((_DWORD *)v8 + 1) = v10;
          g_pVFileSys->Read(v10, v9, v3);
          v11 = 6 * *((unsigned __int16 *)v8 + 1);
          v12 = (void *)malloc(v11);
          *((_DWORD *)v8 + 2) = v12;
          g_pVFileSys->Read(v12, v11, v3);
          v13 = (_DWORD *)operator new(0x3Cu);
          v20 = 0;
          if ( v13 )
            Key = (GRPinput *)((GRPinput *)v13)->GetKey();
          else
            Key = 0;
          v20 = -1;
          *((_DWORD *)v8 + 3) = Key;
          Key->InitDIKToKEY((unsigned __int16 *)v8);
          free(*((void **)v8 + 1));
          free(*((void **)v8 + 2));
          *((_DWORD *)v8 + 2) = 0;
          *((_DWORD *)v8 + 1) = 0;
          v8 += 16;
          ++a2b;
        }
        while ( (int)a2b < (int)this->m_lpDI );
      }
      g_pVFileSys->CloseFile(v3);
    }
  }
}

// 0x004038F0
float * GRPinput::InitShiftedKeys(float *a1, int a2)
{
  double v2; // st7
  float *v3; // ecx
  int v4; // edx
  float v6[6]; // [esp+0h] [ebp-18h] BYREF

  v2 = -3.4028235e38;
  v6[0] = 3.4028235e38;
  v6[5] = -3.4028235e38;
  v6[1] = 3.4028235e38;
  v6[2] = 3.4028235e38;
  v6[3] = -3.4028235e38;
  v6[4] = -3.4028235e38;
  v3 = (float *)(a2 + 8);
  v4 = 3;
  do
  {
    if ( *(v3 - 2) < (double)v6[0] )
      v6[0] = *(v3 - 2);
    if ( *(v3 - 1) < (double)v6[1] )
      v6[1] = *(v3 - 1);
    if ( *v3 < (double)v6[2] )
      v6[2] = *v3;
    if ( *(v3 - 2) > (double)v6[3] )
      v6[3] = *(v3 - 2);
    if ( *(v3 - 1) > (double)v6[4] )
      v6[4] = *(v3 - 1);
    if ( v2 < *v3 )
      v2 = *v3;
    v3 += 3;
    --v4;
  }
  while ( v4 );
  v6[5] = v2;
  qmemcpy(a1, v6, 0x18u);
  return a1;
}

// 0x004039D0
void GRPinput::InitDIKToKEY(unsigned __int16 *a2)
{
  char *v3; // edi
  int v4; // ebx
  int v6; // ebx
  int v7; // ecx
  IDirectInput8A **v8; // edx
  int v9; // edx
  double v10; // st7
  IDirectInputDevice8A **v11; // edx
  int v12; // edx
  double v13; // st7
  IDirectInputDevice8A **v14; // edx
  float *v15; // edx
  int v16; // edx
  double v17; // st7
  int *v18; // edx
  int v19; // edx
  double v20; // st7
  int *v21; // edx
  int v22; // edx
  char *v23; // ecx
  unsigned __int16 *v24; // edx
  int v25; // ebx
  unsigned __int16 v26; // ax
  _DWORD *v27; // eax
  bool v28; // cc
  int v29; // [esp+Ch] [ebp-2Ch]
  int v30; // [esp+10h] [ebp-28h]
  char v31[8]; // [esp+14h] [ebp-24h] BYREF
  char v32; // [esp+1Ch] [ebp-1Ch] BYREF
  unsigned __int16 *a2a; // [esp+3Ch] [ebp+4h]

  v3 = v31;
  v4 = 3;
  do
  {
    ((void (*)(char *))gbVec3D::`default constructor closure')(v3);
    v3 += 12;
    --v4;
  }
  while ( v4 );
  v6 = 0;
  v30 = *((_DWORD *)a2 + 1);
  this->m_lpDI = (IDirectInput8A *)2139095039;
  this->m_lpDIDKeyboard = (IDirectInputDevice8A *)2139095039;
  this->m_lpDIDMouse = (IDirectInputDevice8A *)2139095039;
  this->m_mouseSensitivity = -3.4028235e38;
  this->m_mouseMinX = -8388609;
  this->m_mouseMinY = -8388609;
  if ( *a2 )
  {
    v7 = 0;
    do
    {
      v8 = (IDirectInput8A **)(v7 + *((_DWORD *)a2 + 1));
      if ( *(float *)v8 < (double)*(float *)&this->m_lpDI )
        this->m_lpDI = *v8;
      v9 = *((_DWORD *)a2 + 1);
      v10 = *(float *)(v7 + v9 + 4);
      v11 = (IDirectInputDevice8A **)(v7 + v9 + 4);
      if ( v10 < *(float *)&this->m_lpDIDKeyboard )
        this->m_lpDIDKeyboard = *v11;
      v12 = *((_DWORD *)a2 + 1);
      v13 = *(float *)(v7 + v12 + 8);
      v14 = (IDirectInputDevice8A **)(v7 + v12 + 8);
      if ( v13 < *(float *)&this->m_lpDIDMouse )
        this->m_lpDIDMouse = *v14;
      v15 = (float *)(v7 + *((_DWORD *)a2 + 1));
      if ( *v15 > (double)this->m_mouseSensitivity )
        this->m_mouseSensitivity = *v15;
      v16 = *((_DWORD *)a2 + 1);
      v17 = *(float *)(v7 + v16 + 4);
      v18 = (int *)(v7 + v16 + 4);
      if ( v17 > *(float *)&this->m_mouseMinX )
        this->m_mouseMinX = *v18;
      v19 = *((_DWORD *)a2 + 1);
      v20 = *(float *)(v7 + v19 + 8);
      v21 = (int *)(v7 + v19 + 8);
      if ( v20 > *(float *)&this->m_mouseMinY )
        this->m_mouseMinY = *v21;
      ++v6;
      v7 += 12;
    }
    while ( v6 < *a2 );
  }
  a2a = 0;
  *(float *)&this->m_lpDI = *(float *)&this->m_lpDI - flt_8ACBEC;
  *(float *)&this->m_lpDIDMouse = *(float *)&this->m_lpDIDMouse - flt_8ACBEC;
  this->m_mouseSensitivity = flt_8ACBEC + this->m_mouseSensitivity;
  *(float *)&this->m_mouseMinY = flt_8ACBEC + *(float *)&this->m_mouseMinY;
  if ( a2[1] )
  {
    v22 = 0;
    v29 = 0;
    do
    {
      v23 = (char *)&v32;
      v24 = (unsigned __int16 *)(*((_DWORD *)a2 + 2) + v22);
      v25 = 3;
      do
      {
        v26 = *v24++;
        v23 += 12;
        --v25;
        v27 = (_DWORD *)(v30 + 12 * v26);
        *((_DWORD *)v23 - 5) = *v27;
        *((_DWORD *)v23 - 4) = v27[1];
        *((_DWORD *)v23 - 3) = v27[2];
      }
      while ( v25 );
      sub_403B80((char *)this, v31);
      v22 = v29 + 6;
      v28 = (int)a2a + 1 < a2[1];
      a2a = (unsigned __int16 *)((char *)a2a + 1);
      v29 += 6;
    }
    while ( v28 );
  }
}

// 0x00404020
int GRPinput::GetKey(int a1)
{
  *(_DWORD *)a1 = 0;
  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 12) = 0;
  *(_DWORD *)(a1 + 16) = 0;
  *(_DWORD *)(a1 + 20) = 0;
  *(_BYTE *)(a1 + 24) = HIBYTE(a1);
  *(_DWORD *)(a1 + 28) = 0;
  *(_DWORD *)(a1 + 32) = 0;
  *(_DWORD *)(a1 + 36) = 0;
  *(_DWORD *)(a1 + 44) = 0;
  *(_DWORD *)(a1 + 48) = 0;
  *(_DWORD *)(a1 + 52) = 0;
  *(_DWORD *)(a1 + 56) = 0;
  *(_DWORD *)(a1 + 40) = 0;
  return a1;
}

// 0x00404060
int GRPinput::GetCharKey()
{
  int *p_m_joystickMaxY; // ebx
  GRPinput **v3; // edi
  GRPinput *v4; // ebp
  int v6; // [esp+10h] [ebp-18h]

  p_m_joystickMaxY = (int *)&this->m_joystickMaxY;
  v3 = (GRPinput **)&this->m_joystickMaxY;
  v6 = 4;
  do
  {
    v4 = (GRPinput *)*v3;
    if ( *v3 )
    {
      ((GRPinput *)*v3)->GetCharKey();
      operator delete(v4);
    }
    ++v3;
    --v6;
  }
  while ( v6 );
  *p_m_joystickMaxY = 0;
  p_m_joystickMaxY[1] = 0;
  p_m_joystickMaxY[2] = 0;
  p_m_joystickMaxY[3] = 0;
  this->m_joystickMaxX = 0;
  this->m_joystickMinX = this->m_mouseMaxY;
  operator delete((void *)this->m_mouseMaxY);
  this->m_mouseMaxY = 0;
  this->m_joystickMinX = 0;
  this->m_joystickMinY = 0;
  return 0;
}

// 0x00404150
unsigned int GRPinput::DecideKeyStatus(gbRay *a2, int a3)
{
  gbRay *v3; // ebx
  unsigned int result; // eax
  unsigned int v6; // edx
  struct gbVec3D *v7; // edi
  double v8; // st7
  double v9; // st7
  double v10; // st7
  float y; // edx
  float x; // ecx
  float z; // eax
  int *v14; // ecx
  _DWORD *v15; // eax
  char *v16; // edi
  int v17; // edx
  int v18; // ebx
  int *p_m_joystickMaxY; // edi
  int v20; // ebp
  unsigned int v21; // [esp+14h] [ebp-2Ch]
  int i; // [esp+18h] [ebp-28h]
  struct gbVec3D v23; // [esp+1Ch] [ebp-24h] BYREF
  float v24; // [esp+28h] [ebp-18h]
  float v25; // [esp+2Ch] [ebp-14h]
  float v26; // [esp+30h] [ebp-10h]
  gbVec3D v27; // [esp+34h] [ebp-Ch] BYREF

  v3 = a2;
  result = a2->IsColAABB((struct gbAABBox *)this);
  if ( result )
  {
    memset(&v23, 0, sizeof(v23));
    v21 = 0;
    for ( i = 0; ; i += 36 )
    {
      result = this->m_mouseMaxY;
      if ( !result )
        break;
      v6 = (int)(this->m_joystickMinX - result) / 36;
      result = v21;
      if ( v21 >= v6 )
        break;
      v7 = (struct gbVec3D *)(i + this->m_mouseMaxY);
      ++*(_DWORD *)(a3 + 20);
      if ( v3->IsColTriangle(v7, v7 + 1, v7 + 2, &v23) )
      {
        v24 = v23.x - v3->Origin.x;
        v8 = v23.y - v3->Origin.y;
        v27.x = v24;
        v25 = v8;
        v9 = v23.z - v3->Origin.z;
        v27.y = v25;
        v26 = v9;
        v27.z = v26;
        v10 = ((gbVec3D *)&v27)->Length();
        if ( v10 < *(float *)a3 )
        {
          y = v23.y;
          x = v23.x;
          *(float *)a3 = v10;
          z = v23.z;
          *(_BYTE *)(a3 + 16) = 1;
          *(float *)(a3 + 8) = y;
          *(float *)(a3 + 4) = x;
          *(float *)(a3 + 12) = z;
          v14 = (int *)v7;
          v15 = (_DWORD *)(a3 + 28);
          v16 = (char *)&v7[-2] - a3;
          v17 = 3;
          do
          {
            v18 = *v14;
            v14 += 3;
            *(v15 - 1) = v18;
            * v15 = (*)*(_DWORD *)((char *)v15 + (_DWORD)v16);
            v15[1] = *(v14 - 1);
            v15 += 3;
            --v17;
          }
          while ( v17 );
          v3 = a2;
        }
      }
      ++v21;
    }
    p_m_joystickMaxY = (int *)&this->m_joystickMaxY;
    v20 = 4;
    do
    {
      if ( *p_m_joystickMaxY )
        result = ((GRPinput *)*p_m_joystickMaxY)->DecideKeyStatus(v3, a3);
      ++p_m_joystickMaxY;
      --v20;
    }
    while ( v20 );
  }
  return result;
}

// 0x004042D0
int GRPinput::IsAnyKeyPressed()
{
  int result; // eax

  result = (int)this->m_lpDIDKeyboard;
  if ( result )
    return (int)&this->m_lpDIDMouse[-result] / 36;
  return result;
}
