#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/GRPinput.h"

// Forward declarations for unnamed functions
int DirectInput8Create(...);
int sub_404350(...);
int sub_404380(...);

char * __stdcall StrCopyRange(char *pStart, char *pEnd, char *pDest); // from annotations

// Unnamed globals (extern)
extern char byte_8AC5D8[1556];
extern int dword_573800;
extern int dword_573810;
extern int dword_573A5C;
extern int dword_573C64;
void __cdecl nullsub_2(...);
extern const char * off_580CFC;

// 0x004020E0
int GRPinput::Create(HINSTANCE *hInst, int hwnd, int flag)
{
  IDirectInputDevice8 **p_m_lpDIDMouse; // edi
  IDirectInputDevice8 *v7; // edi
  IDirectInputDevice8 **p_m_lpDIDKeyboard; // edi

  if ( DirectInput8Create((HINSTANCE)hInst, 0x800u, &riidltf, (LPVOID *)&this->m_lpDI, 0) )
    return 0;
  p_m_lpDIDMouse = &this->m_lpDIDMouse;
  if ( !(*(int ( **)(IDirectInput8 *, int *, IDirectInputDevice8 **, _DWORD))(*(_DWORD *)this->m_lpDI + 12))(
          this->m_lpDI,
          dword_573810,
          &this->m_lpDIDMouse,
          0) )
  {
    (*(void ( **)(IDirectInputDevice8 *, int *))(*(_DWORD *)*p_m_lpDIDMouse + 44))(
      *p_m_lpDIDMouse,
      dword_573C64);
    v7 = *p_m_lpDIDMouse;
    if ( flag )
      (*(void ( **)(IDirectInputDevice8 *, int, int))(*(_DWORD *)v7 + 52))(v7, hwnd, 5);
    else
      (*(void ( **)(IDirectInputDevice8 *, int, int))(*(_DWORD *)v7 + 52))(v7, hwnd, 6);

    if ( !this->m_bMouse )
      return 0;
  }
  p_m_lpDIDKeyboard = &this->m_lpDIDKeyboard;
  if ( !(*(int ( **)(IDirectInput8 *, int *, IDirectInputDevice8 **, _DWORD))(*(_DWORD *)this->m_lpDI + 12))(
          this->m_lpDI,
          dword_573800,
          &this->m_lpDIDKeyboard,
          0) )
  {
    (*(void ( **)(IDirectInputDevice8 *, int *))(*(_DWORD *)*p_m_lpDIDKeyboard + 44))(
      *p_m_lpDIDKeyboard,
      dword_573A5C);
    (*(void ( **)(IDirectInputDevice8 *, int, int))(*(_DWORD *)*p_m_lpDIDKeyboard + 52))(
      *p_m_lpDIDKeyboard,
      hwnd,
      6);

    if ( !this->m_bKeyboard )
      return 0;


  }
  GetCursorPos(&this->m_mousept);
  return 1;
}

// 0x004021E0
int GRPinput::HandleDeviceInput(int nMouse, int nKeyboard, int nVal3)
{
  this->m_bMouse = nMouse;
  if ( nMouse )
  {
  }
  else

  this->m_bKeyboard = nKeyboard;
  if ( nKeyboard )
    return this->ReleaseDevices();
  else
    return EnumJoystick();
}

// 0x00402220
void GRPinput::Reset()
{
  memset(this->m_keyStates, 0, 0x10Cu);
  *(_WORD *)&this->m_keyStates[268] = 0;
  memset(&this->m_keyStates[270], 0, 0x10Cu);
  HIWORD(this->m_keyPressTimes[2]) = 0;
  memset(this->m_keyPressTimes, 0, sizeof(this->m_keyPressTimes));
  memset(this->m_keyDragStartPositions, 0, sizeof(this->m_keyDragStartPositions));
  memset(this->KeyInfo, 0, sizeof(this->KeyInfo));
}

// 0x00402270
void GRPinput::SetMouseLimits(int a, int b, int c, int d)
{
  this->m_mouseMinX = a;
  this->m_mouseMinY = b;
  this->m_mouseMaxX = c;
  this->m_mouseMaxY = d;
}

// 0x00402290
BOOL GRPinput::SetCursorPos(int X, int Y)
{
  return SetCursorPos(X, Y);
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
  return (unsigned __int8)this->m_keyStates[key];
}

// 0x004022E0
BOOL GRPinput::GetCursorPos()
{
  tagPOINT *lpPoint; // [esp+0x4] [ebp+0x4]

  return GetCursorPos(lpPoint);
}

// 0x004022F0
void GRPinput::GetMousePos(void *pOut, void *pOut2)
{
  *(_DWORD *)pOut = this->m_mouseDeltaX;
  *(_DWORD *)pOut2 = this->m_mouseDeltaY;
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
    result = (*(int ( **)(int))(*(_DWORD *)result + 28))(result);
    if ( result )
    {
      v3 = 0;
      while ( 1 )
      {
        result = (*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)this->m_lpDIDMouse + 28))(this->m_lpDIDMouse);
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

// 0x00402360
int GRPinput::_thunk_vtbl8()
{
  IDirectInputDevice8 *m_lpDIDMouse; // ecx
  int result; // eax

  this->m_bMouse = 0;
  m_lpDIDMouse = this->m_lpDIDMouse;
  if ( m_lpDIDMouse )
    return (*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)m_lpDIDMouse + 32))(m_lpDIDMouse);
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
    if ( (*(int ( **)(int))(*(_DWORD *)result + 28))(result) )
    {
      v3 = 0;
      while ( 1 )
      {
        result = (*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)this->m_lpDIDKeyboard + 28))(this->m_lpDIDKeyboard);
        if ( !result )
          break;
        if ( ++v3 >= 50 )
        {
          this->m_bKeyboard = 0;
          return result;
        }
      }
    }

  }
  return result;
}

// 0x00402400
GRPinput::GRPinput()
{
  unsigned __int8 *v2; // edi
  int *m_DIKToKEY; // ebx
  int v4; // ebp
  LONG y; // edi
  int v6; // ecx
  LONG v7; // edx
  int v8; // edx
  int v9; // edi
  char *v10; // ebx
  int v11; // ebp
  struct tagPOINT Point; // [esp+0x18] [ebp-0x8] BYREF

  if ( this->m_bKeyboard )
  {
    v2 = &this->m_keyStates[270];
    if ( (*(int (__stdcall **)(IDirectInputDevice8 *, int, _BYTE *))(*(_DWORD *)this->m_lpDIDKeyboard + 36))(
           this->m_lpDIDKeyboard,
           256,
           &this->m_keyStates[270]) )
    {

      return;
    }
    m_DIKToKEY = (int *)this->m_DIKToKEY;
    v4 = 256;
    do
    {
      if ( *m_DIKToKEY )
      ++m_DIKToKEY;
      ++v2;
      --v4;
    }
    while ( v4 );
  }
  if ( this->m_bMouse )
  {
    if ( (*(int (__stdcall **)(IDirectInputDevice8 *, int, char *))(*(_DWORD *)this->m_lpDIDMouse + 36))(
           this->m_lpDIDMouse,
           20,
           this->MouseState) )
    {

    }
    else
    {
      GetCursorPos(&Point);
      y = this->m_mousept.y;
      v6 = Point.x - this->m_mousept.x;
      this->m_mousept.x = Point.x;
      this->m_mouseDeltaX = v6;
      v7 = Point.y;
      this->m_mousept.y = Point.y;
      v8 = v7 - y;
      v9 = 256;
      this->m_mouseDeltaY = v8;
      v10 = &this->MouseState[12];
      v11 = 3;
      do
      {
        --v11;
      }
      while ( v11 );
    }
  }
}

// 0x004024F0
void GRPinput::_GRPinput(int nVal, int nVal2)
{
  unsigned __int8 v4; // al
  int v5; // eax

  if ( nVal2 )
  {
    v4 = this->m_keyStates[nVal];
    if ( v4 < 2u )
    {
      this->m_keyStates[nVal] = 2;
      this->m_keyPressTimes[nVal] = timeGetTime();
      this->m_keyDragStartPositions[nVal][0] = this->m_mouseFreeX;
      this->m_keyDragStartPositions[nVal][1] = this->m_mouseFreeY;
    }
    else if ( v4 == 2 )
    {
      this->m_keyStates[nVal] = 3;
    }
  }
  else
  {
    v5 = (unsigned __int8)this->m_keyStates[nVal];
    if ( (_BYTE)v5 == 3 || (_BYTE)v5 == 2 )
    {
      this->m_keyStates[nVal] = 1;
    }
    else if ( (_BYTE)v5 == 1 )
    {
      this->m_keyStates[nVal] = 0;
    }
  }
}

// 0x00402570
int GRPinput::InitKeyMappings()
{
  int result; // eax
  _BYTE *v3; // esi
  char v4; // cl

  memset(this->m_shiftedKeyStates, 0, 0x10Cu);
  *(_WORD *)&this->m_shiftedKeyStates[268] = 0;
  result = 0;
  v3 = &this->m_shiftedKeyStates[97];
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

// 0x00402640
int GRPinput::BuildKeyMap()
{
  int v2; // eax
  ULONG *m_DIKToKEY; // ecx
  int v4; // esi

  v2 = 0;
  memset(this->m_DIKToKEY, 0, sizeof(this->m_DIKToKEY));
  this->m_DIKToKEY[1] = 27;
  this->m_DIKToKEY[2] = 49;
  this->m_DIKToKEY[3] = 50;
  this->m_DIKToKEY[4] = 51;
  this->m_DIKToKEY[5] = 52;
  this->m_DIKToKEY[6] = 53;
  this->m_DIKToKEY[7] = 54;
  this->m_DIKToKEY[8] = 55;
  this->m_DIKToKEY[9] = 56;
  this->m_DIKToKEY[10] = 57;
  this->m_DIKToKEY[11] = 48;
  this->m_DIKToKEY[12] = 45;
  this->m_DIKToKEY[13] = 61;
  this->m_DIKToKEY[14] = 8;
  this->m_DIKToKEY[15] = 9;
  this->m_DIKToKEY[16] = 113;
  this->m_DIKToKEY[17] = 119;
  this->m_DIKToKEY[18] = 101;
  this->m_DIKToKEY[19] = 114;
  this->m_DIKToKEY[20] = 116;
  this->m_DIKToKEY[21] = 121;
  this->m_DIKToKEY[22] = 117;
  this->m_DIKToKEY[23] = 105;
  this->m_DIKToKEY[24] = 111;
  this->m_DIKToKEY[25] = 112;
  this->m_DIKToKEY[26] = 91;
  this->m_DIKToKEY[27] = 93;
  this->m_DIKToKEY[28] = 13;
  this->m_DIKToKEY[29] = 130;
  this->m_DIKToKEY[30] = 97;
  this->m_DIKToKEY[31] = 115;
  this->m_DIKToKEY[32] = 100;
  this->m_DIKToKEY[33] = 102;
  this->m_DIKToKEY[34] = 103;
  this->m_DIKToKEY[35] = 104;
  this->m_DIKToKEY[36] = 106;
  this->m_DIKToKEY[37] = 107;
  this->m_DIKToKEY[38] = 108;
  this->m_DIKToKEY[39] = 59;
  this->m_DIKToKEY[40] = 39;
  this->m_DIKToKEY[41] = 96;
  this->m_DIKToKEY[42] = 128;
  this->m_DIKToKEY[43] = 92;
  this->m_DIKToKEY[44] = 122;
  this->m_DIKToKEY[45] = 120;
  this->m_DIKToKEY[46] = 99;
  this->m_DIKToKEY[47] = 118;
  this->m_DIKToKEY[48] = 98;
  this->m_DIKToKEY[49] = 110;
  this->m_DIKToKEY[50] = 109;
  this->m_DIKToKEY[51] = 44;
  this->m_DIKToKEY[52] = 46;
  this->m_DIKToKEY[53] = 47;
  this->m_DIKToKEY[54] = 129;
  this->m_DIKToKEY[55] = 157;
  this->m_DIKToKEY[56] = 132;
  this->m_DIKToKEY[57] = 32;
  this->m_DIKToKEY[58] = 173;
  this->m_DIKToKEY[59] = 138;
  this->m_DIKToKEY[60] = 139;
  this->m_DIKToKEY[61] = 140;
  this->m_DIKToKEY[62] = 141;
  this->m_DIKToKEY[63] = 142;
  this->m_DIKToKEY[64] = 143;
  this->m_DIKToKEY[65] = 144;
  this->m_DIKToKEY[66] = 145;
  this->m_DIKToKEY[67] = 146;
  this->m_DIKToKEY[68] = 147;
  this->m_DIKToKEY[69] = 172;
  this->m_DIKToKEY[70] = 174;
  this->m_DIKToKEY[71] = 169;
  this->m_DIKToKEY[72] = 170;
  this->m_DIKToKEY[73] = 171;
  this->m_DIKToKEY[74] = 158;
  this->m_DIKToKEY[75] = 166;
  this->m_DIKToKEY[76] = 167;
  this->m_DIKToKEY[77] = 168;
  this->m_DIKToKEY[78] = 159;
  this->m_DIKToKEY[79] = 163;
  this->m_DIKToKEY[80] = 164;
  this->m_DIKToKEY[81] = 165;
  this->m_DIKToKEY[82] = 162;
  this->m_DIKToKEY[83] = 161;
  this->m_DIKToKEY[87] = 148;
  this->m_DIKToKEY[88] = 149;
  this->m_DIKToKEY[156] = 160;
  this->m_DIKToKEY[157] = 131;
  this->m_DIKToKEY[181] = 156;
  this->m_DIKToKEY[183] = 175;
  this->m_DIKToKEY[184] = 133;
  this->m_DIKToKEY[199] = 152;
  this->m_DIKToKEY[200] = 136;
  this->m_DIKToKEY[201] = 154;
  this->m_DIKToKEY[203] = 134;
  this->m_DIKToKEY[205] = 135;
  this->m_DIKToKEY[207] = 153;
  this->m_DIKToKEY[208] = 137;
  this->m_DIKToKEY[209] = 155;
  this->m_DIKToKEY[210] = 150;
  this->m_DIKToKEY[211] = 151;
  this->m_DIKToKEY[219] = 0;
  this->m_DIKToKEY[220] = 0;
  this->m_DIKToKEY[221] = 0;
  m_DIKToKEY = this->m_DIKToKEY;
  do
  {
    v4 = *m_DIKToKEY++;
    this->charTOscan[v4] = v2++;
  }
  while ( v2 < 256 );
  this->KeyTransformation[0] = 1;
  this->KeyTransformation[1] = 2;
  this->KeyTransformation[2] = 2;
  this->KeyTransformation[3] = 2;
  return 2;
}

// 0x00402A90
void GRPinput::SetMouseAbs(int nVal, int nVal2, int nVal3)
{
  GRP_KEYREG *v4; // eax
  int HoldTime; // ecx
  int v6; // ecx
  int PressTime; // ecx

  v4 = &this->KeyInfo[nVal2];
  if ( nVal3 )
  {
    if ( this->KeyInfo[nVal2].HoldTime )
    {
      v6 = this->KeyTransformation[this->KeyInfo[nVal2].CountMode];
      v4->PressTime = 0;
      v4->Data = v6;
      v4->CountMode = v6;
    }
    PressTime = v4->PressTime;
    v4->HoldTime = 0;
    v4->PressTime = PressTime + 1;
  }
  else
  {
    HoldTime = this->KeyInfo[nVal2].HoldTime;
    v4->PressTime = 0;
    if ( HoldTime )
    {
      v4->Data = 0;
      if ( (unsigned int)(nVal - HoldTime) > 0x64 )
        v4->CountMode = 0;
    }
    else
    {
      v4->HoldTime = nVal;
    }
  }
}

// 0x00402B00
void GRPinput::SetJoystickAbs()
{
  int v1; // edx
  GRP_KEYREG *KeyInfo; // ecx

  v1 = 0;
  KeyInfo = this->KeyInfo;
  do
  {
    if ( KeyInfo->PressTime == 1 && (KeyInfo->Data & 3) != 0 )
      break;
    ++v1;
    ++KeyInfo;
  }
  while ( v1 < 270 );
}

// 0x00402B60
// attributes: thunk
void GRPinput::RunJoystickControlPanel(void *hWnd)
{

}

// 0x00402B70
void GRPinput::ClearKeyBuffer()
{
  *(_DWORD *)&byte_8AC5D8[908] = 1094713344;
}

// 0x00402B90
void GRPinput::SetJoystickLimits()
{
  *(float *)&byte_8AC5D8[904] = 12.0 + 12.0;
}

// 0x00402BA0
GRPinput * GRPinput::SetMousePos()
{
  LOBYTE(this->m_lpDIDMouse) = HIBYTE(this);
  this->m_mouseSensitivity = 0.0;
  this->m_mouseMinX = 0;
  this->m_mouseMinY = 0;
  LOBYTE(this->m_lpDIDKeyboard) = 0;
  this->m_mouseMaxX = 0;
  this->m_mouseMaxY = 0;
  this->m_joystickMinX = 10;
  return this;
}

// 0x00402BF0
void GRPinput::SetMouseFreePos()
{
  float m_mouseSensitivity; // eax
  _BYTE *v3; // ecx
  char v4; // al

  m_mouseSensitivity = this->m_mouseSensitivity;
  if ( m_mouseSensitivity != 0.0 )
  {
    v3 = (_BYTE *)(LODWORD(m_mouseSensitivity) - 1);
    v4 = *(_BYTE *)(LODWORD(m_mouseSensitivity) - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  this->m_mouseSensitivity = 0.0;
  this->m_mouseMinX = 0;
  this->m_mouseMinY = 0;
}

// 0x00402C40
void GRPinput::SetJoystickPos(const char *x, int y)
{
  GRPinput *v3; // esi
  unsigned int v4; // kr04_4
  IDirectInputDevice8 **p_m_lpDIDMouse; // ebp
  unsigned int v6; // ebx
  float m_mouseSensitivity; // ecx
  char v8; // al
  unsigned int m_mouseMinY; // eax
  float v10; // ecx
LOBYTE(this->m_lpDIDKeyboard) = 1;
  v4 = strlen(x) + 1;
  p_m_lpDIDMouse = &this->m_lpDIDMouse;
  v6 = v4 - 1;
  if ( v4 - 1 > 0xFFFFFFFD )
// [IDA_MISID]     std::_Xlen();
  m_mouseSensitivity = this->m_mouseSensitivity;
  if ( m_mouseSensitivity == 0.0 || (v8 = *(_BYTE *)(LODWORD(m_mouseSensitivity) - 1)) == 0 || v8 == -1 )
  {
    if ( v4 == 1 )
    {
      ((std *)1)->string::_Tidy();
      goto LABEL_15;
    }
    m_mouseMinY = this->m_mouseMinY;
    if ( m_mouseMinY <= 0x1F && m_mouseMinY >= v6 )
    {
LABEL_14:
      qmemcpy((void *)LODWORD(this->m_mouseSensitivity), x, v6);
      v10 = this->m_mouseSensitivity;
p_m_lpDIDMouse[2] = (IDirectInputDevice8 *)v6;
      *(_BYTE *)(LODWORD(v10) + v6) = 0;
      goto LABEL_15;
    }
    ((std *)1)->string::_Tidy();
LABEL_13:
    ((GRPinput *)&this->m_lpDIDMouse)->PollInputState(v6);
    goto LABEL_14;
  }
  if ( v4 != 1 )
    goto LABEL_13;
  *(_BYTE *)(LODWORD(m_mouseSensitivity) - 1) = v8 - 1;
  this->m_mouseSensitivity = 0.0;
  this->m_mouseMinX = 0;
  this->m_mouseMinY = 0;
LABEL_15:
  this->m_mouseMaxX = 0;
  this->m_mouseMaxY = y;
  this->m_joystickMinX = 40;
}

// 0x00402D00
void GRPinput::SetJoystickFreePos(float x)
{
  if ( LOBYTE(this->m_lpDIDKeyboard) )
    *(float *)&this->m_mouseMaxX = x + *(float *)&this->m_mouseMaxX;
}

// 0x00402D20
void GRPinput::SetMouseSensitivity()
{
  int m_mouseMaxY; // eax
  double v3; // st7
  gbPrintFont *v4; // edi
  double v5; // st7
  double v6; // st7
  float m_mouseSensitivity; // esi
  double v8; // st7
  __int64 v9; // rax
  double v10; // st7
  gbPrintFont *v11; // edi
  float v12; // esi
  float v13; // [esp+0x10] [ebp-0x38]
  float v14; // [esp+0x10] [ebp-0x38]
  float v15; // [esp+0x14] [ebp-0x34]
  float v16; // [esp+0x28] [ebp-0x20]
  unsigned int v17; // [esp+0x28] [ebp-0x20]
  signed int v18; // [esp+0x2C] [ebp-0x1C] BYREF
  int m_joystickMinX; // [esp+0x30] [ebp-0x18]
  gbColorQuad v20[2]; // [esp+0x34] [ebp-0x14] BYREF
  struct gbVec3D v21; // [esp+0x3C] [ebp-0xC] BYREF

  if ( LOBYTE(this->m_lpDIDKeyboard) )
  {
    m_mouseMaxY = this->m_mouseMaxY;
    if ( m_mouseMaxY )
    {
      if ( m_mouseMaxY == 1 )
      {
        m_joystickMinX = this->m_joystickMinX;
        v3 = 40.0 / (double)g_DrvInfo.height;
        v4 = gfxMgr->pFontMgr->pAllFont[2];
        v18 = (unsigned int)(g_DrvInfo.width - 10 * this->m_mouseMinX) >> 1;
        v4->ScaleX = 40.0 / (double)g_DrvInfo.width;
        v4->ScaleY = v3;
        v5 = *(float *)&this->m_mouseMaxX - 1.5;
        if ( v5 < 0.0 )
          v5 = 0.0;
        v6 = 1.0 - v5 * 0.40000001;
        if ( v6 < 0.0 )
          v6 = 0.0;
        HIBYTE(v20[0].Color) = (__int64)(v6 * 255.0);
        if ( !HIBYTE(v20[0].Color) )
          LOBYTE(this->m_lpDIDKeyboard) = 0;
        // [AUTO-COMMENTED] v4->curColor = (gbColorQuad)((gbColorQuad *)v20)->gbColorQuad(0xFFu, 0xFFu, 0xFFu, HIBYTE(v20[0].Color))->Color;
        m_mouseSensitivity = this->m_mouseSensitivity;
        if ( m_mouseSensitivity == 0.0 )
          m_mouseSensitivity = COERCE_FLOAT(&g_bActorFlag);
        v15 = 1.0 - ((double)m_joystickMinX + (double)m_joystickMinX) / (double)g_DrvInfo.height;
        v13 = ((double)v18 + (double)v18) / (double)g_DrvInfo.width - 1.0;
        ((void ( *)(gbPrintFont *, float, _DWORD, _DWORD, int, int))v4->pGfxMgr->DrvInfo.subtype)(
          v4,
          COERCE_FLOAT(LODWORD(m_mouseSensitivity)),
          LODWORD(v13),
          LODWORD(v15),
          1176256512,
          1176256512);
        ((void ( *)(gbPrintFont *))v4->pGfxMgr->hGfxWnd)(v4);
      }
    }
    else
    {
      v16 = *(float *)&this->m_mouseMaxX * 0.40000001;
      if ( g_pRoleSystem )
      {
        v21 = *(gbVec3D *)&g_pRoleSystem->m_fPosX;
        v21.y = v16 * 20.0 + v21.y + 64.0;
        ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->PointWorldToScr(&v21, (float *)&v20[0].Color, (float *)&v18);
        v8 = 1.0 - v16;
        if ( v8 < 0.0 )
          v8 = 0.0;
        v9 = (__int64)(v8 * 255.0);
        if ( !(_BYTE)v9 )
          LOBYTE(this->m_lpDIDKeyboard) = 0;
        v10 = 32.0 / (double)g_DrvInfo.height;
        v11 = gfxMgr->pFontMgr->pAllFont[3];
        v11->ScaleX = 32.0 / (double)g_DrvInfo.width;
        v11->ScaleY = v10;
        if ( gbColorQuad::ColorQuadFmt )
        {
          *(_WORD *)((char *)&v17 + 1) = -6636;
          LOBYTE(v17) = 20;
        }
        else
        {
          LOBYTE(v17) = -26;
          *(_WORD *)((char *)&v17 + 1) = 5140;
        }
        HIBYTE(v17) = v9;
        v11->curColor.Color = v17;
        v12 = this->m_mouseSensitivity;
        if ( v12 == 0.0 )
          v12 = COERCE_FLOAT(&g_bActorFlag);
        v14 = *(float *)&v20[0].Color - 0.1;
        ((void ( *)(gbPrintFont *, float, _DWORD, signed int, int, int))v11->pGfxMgr->DrvInfo.subtype)(
          v11,
          COERCE_FLOAT(LODWORD(v12)),
          LODWORD(v14),
          v18,
          1176256512,
          1176256512);
        ((void ( *)(gbPrintFont *))v11->pGfxMgr->hGfxWnd)(v11);
      }
    }
  }
}

// 0x00402FA0
int GRPinput::GetMouseSensitivity(int nVal)
{
  this->m_joystickMinX = nVal;
  return nVal;
}

// 0x00403000
_BYTE * GRPinput::PollInputState(unsigned int key)
{
  IDirectInputDevice8 *v2; // esi
  size_t v4; // eax
  IDirectInputDevice8 *m_lpDIDMouse; // eax
  IDirectInputDevice8 *m_lpDIDKeyboard; // eax
  IDirectInputDevice8 *v7; // edi
  IDirectInputDevice8 *v8; // ecx
  IDirectInputDevice8 v9; // al
  _BYTE *result; // eax
  IDirectInputDevice8 *v11; // ecx
  _DWORD v12[4]; // [esp+0x0] [ebp-0x24] BYREF
  unsigned int v13; // [esp+0x10] [ebp-0x14]
  _DWORD *v14; // [esp+0x14] [ebp-0x10]
  int v15; // [esp+0x20] [ebp-0x4]
  IDirectInputDevice8 *keya; // [esp+0x2C] [ebp+0x8]

  v2 = (IDirectInputDevice8 *)(key | 0x1F);
  v14 = v12;
  v12[3] = this;
  v13 = key | 0x1F;
  if ( (key | 0x1F) > 0xFFFFFFFD )
  {
    v13 = key;
    v2 = (IDirectInputDevice8 *)key;
  }
  v4 = (size_t)&v2[2];
  v15 = 0;
  if ( (int)&v2[2] < 0 )
    v4 = 0;
  keya = (IDirectInputDevice8 *)operator new(v4);
  m_lpDIDMouse = this->m_lpDIDMouse;
  if ( m_lpDIDMouse )
  {
    if ( m_lpDIDMouse > v2 )
      m_lpDIDMouse = v2;
    qmemcpy(&keya[1], this->m_lpDIDKeyboard, (unsigned int)m_lpDIDMouse);
    v2 = (IDirectInputDevice8 *)v13;
  }
  m_lpDIDKeyboard = this->m_lpDIDKeyboard;
  v7 = this->m_lpDIDMouse;
  if ( m_lpDIDKeyboard )
  {
    v8 = m_lpDIDKeyboard - 1;
    v9 = m_lpDIDKeyboard[-1];
    if ( !*(_BYTE *)&v9 || v9 == 0xFF )
      operator delete(v8);
    else
      *v8 = (IDirectInputDevice8)(*(_BYTE *)&v9 - 1);
  }
  this->m_lpDIDMouse = 0;
  result = &keya[1];
  this->m_lpDIDKeyboard = keya + 1;
  *keya = 0;
  LODWORD(this->m_mouseSensitivity) = v2;
  if ( v7 <= v2 )
    v2 = v7;
  v11 = this->m_lpDIDKeyboard;
  this->m_lpDIDMouse = v2;
  v2[(_DWORD)v11] = 0;
  return result;
}

// 0x00403150
void GRPinput::GetMouseFreePos()
{
  g_fPAL3Timer = 12.0;
}

// 0x00403160
// attributes: thunk
void GRPinput::GetMouseDeltas()
{

}

// 0x00403170
void GRPinput::GetJoystickPos()
{
  *(float *)&byte_8AC5D8[1552] = 12.0 + 12.0;
}

// 0x00403180
BOOL GRPinput::GetJoystickFreePos(int x, int y)
{
  int v3; // eax

  if ( x >= 0 && (v3 = *(_DWORD *)&this->m_keyStates[48], x < v3) && y >= 0 && y < *(_DWORD *)&this->m_keyStates[52] )
    return *(_BYTE *)(*(_DWORD *)&this->m_keyStates[56] + 8 * (x + y * v3) + 4) > 1u;
  else
    return 0;
}

// 0x004031D0
int GRPinput::GetState()
{
  float m_mouseSensitivity; // ecx
  int v3; // ecx
  int v4; // edx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st7
  double v13; // st6
  double v14; // st5
  float v16; // [esp+0x10] [ebp-0x44]
  float v17; // [esp+0x10] [ebp-0x44]
  float v18; // [esp+0x10] [ebp-0x44]
  float v19; // [esp+0x10] [ebp-0x44]
  float v20; // [esp+0x14] [ebp-0x40]
  float v21; // [esp+0x14] [ebp-0x40]
  float v22; // [esp+0x14] [ebp-0x40]
  float v23; // [esp+0x14] [ebp-0x40]
  int v24; // [esp+0x18] [ebp-0x3C] BYREF
  float v25; // [esp+0x1C] [ebp-0x38]
  int v26; // [esp+0x20] [ebp-0x34]
  int v27; // [esp+0x24] [ebp-0x30]
  int v28; // [esp+0x28] [ebp-0x2C]
  int v29; // [esp+0x2C] [ebp-0x28]
  int base; // [esp+0x30] [ebp-0x24] BYREF
  float v31; // [esp+0x34] [ebp-0x20]
  float v32; // [esp+0x38] [ebp-0x1C]
  float v33; // [esp+0x3C] [ebp-0x18]
  float v34; // [esp+0x40] [ebp-0x14]
  float v35; // [esp+0x44] [ebp-0x10]
  float v36; // [esp+0x48] [ebp-0xC]
  float v37; // [esp+0x4C] [ebp-0x8]
  float v38; // [esp+0x50] [ebp-0x4]
  int v39; // [esp+0x58] [ebp+0x4]
  int v40; // [esp+0x5C] [ebp+0x8]
  gbVec3D *v41; // [esp+0x60] [ebp+0xC]

  v25 = 0.0;
  v26 = 0;
  v27 = 0;
  m_mouseSensitivity = this->m_mouseSensitivity;
  v24 = 2139095039;
  LOBYTE(v28) = 0;
  v29 = 0;
  ((GRPinput *)LODWORD(m_mouseSensitivity))->DecideKeyStatus(v39, (unsigned int)&v24);
  v3 = v26;
  v4 = v27;
  *(float *)v40 = v25;
  *(_DWORD *)(v40 + 4) = v3;
  *(_DWORD *)(v40 + 8) = v4;
  if ( (_BYTE)v28 && v41 )
  {
    v5 = v33 - *(float *)&base;
    v16 = v34 - v31;
    v6 = v35 - v32;
    v41[1].y = v16;
    v20 = v6;
    v41[1].x = v5;
    v41[1].z = v20;
    ((gbVec3D *)v41 + 1)->Normalize();
    v7 = v36 - *(float *)&base;
    v17 = v37 - v31;
    v8 = v38 - v32;
    v41[2].y = v17;
    v21 = v8;
    v41[2].x = v7;
    v41[2].z = v21;
    ((gbVec3D *)v41 + 2)->Normalize();
    v9 = v41[1].y * v41[2].z - v41[1].z * v41[2].y;
    v18 = v41[1].z * v41[2].x - v41[1].x * v41[2].z;
    v10 = v41[1].x * v41[2].y;
    v11 = v41[1].y * v41[2].x;
    v41->y = v18;
    v22 = v10 - v11;
    v41->x = v9;
    v41->z = v22;
    ((gbVec3D *)v41)->Normalize();
    v12 = v41->z * v41[1].y - v41[1].z * v41->y;
    v19 = v41[1].z * v41->x - v41->z * v41[1].x;
    v13 = v41->y * v41[1].x;
    v14 = v41->x * v41[1].y;
    v41[2].y = v19;
    v23 = v13 - v14;
    v41[2].x = v12;
    v41[2].z = v23;
    ((gbVec3D *)v41 + 2)->Normalize();
  }
  return (unsigned __int8)v28;
}

// 0x00403370
GRPinput * GRPinput::AcquireMouse()
{
  memset(this, 0, 0x16Cu);
  return this;
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
  float m_mouseSensitivity; // edi

  if ( this->m_lpDIDKeyboard )
  {
    free(this->m_lpDIDKeyboard);
    this->m_lpDIDKeyboard = 0;
  }
  if ( this->m_lpDIDMouse )
  {
    free(this->m_lpDIDMouse);
    this->m_lpDIDMouse = 0;
  }
  m_mouseSensitivity = this->m_mouseSensitivity;
  if ( m_mouseSensitivity != 0.0 )
  {
    ((GRPinput *)LODWORD(this->m_mouseSensitivity))->GetCharKey();
    operator delete((void *)LODWORD(m_mouseSensitivity));
    this->m_mouseSensitivity = 0.0;
  }
  this->m_lpDI = 0;
  this->m_lpDIDKeyboard = 0;
  this->m_lpDIDMouse = 0;
  this->m_mouseSensitivity = 0.0;
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
  if ( *(_DWORD *)&this->m_keyStates[56] )
    free(*(void **)&this->m_keyStates[56]);
  memset(this, 0, 0xA4u);
}

// 0x004034E0
void GRPinput::UnacquireKeyboard()
{

}

// 0x00403560
void GRPinput::Update()
{
  _BYTE *v2; // esi
  void **v3; // ebx
  void *v4; // edi
  _DWORD *v5; // ecx
  int v6; // [esp+0x4] [ebp-0x4]

  v6 = 0;
  if ( (int)this->m_lpDI <= 0 )
  {
    this->m_lpDI = 0;
  }
  else
  {
    v2 = &this->m_keyStates[236];
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
      v5 = v2 - 8;
      v3 += 41;
      v2 += 16;
      *v5 = 0;
      v5[1] = 0;
      v5[2] = 0;
      v5[3] = 0;
      ++v6;
    }
    while ( v6 < (int)this->m_lpDI );
    this->m_lpDI = 0;
  }
}

// 0x00403640
void GRPinput::CheckKeyEvents(const char *key)
{
  GRPinput *v2; // ebx
  gbVFile *v3; // edi
  int v4; // ecx
  _DWORD *v5; // ebx
  size_t v6; // esi
  void *v7; // eax
  unsigned __int16 *v8; // esi
  size_t v9; // ebx
  void *v10; // eax
  size_t v11; // ebx
  void *v12; // eax
  GRPinput *v13; // eax
  GRPinput *v14; // eax
  int v16; // [esp+ACh] [ebp-0x1C] BYREF
  char v17; // [esp+B0h] [ebp-0x18]
  _BYTE v18[5]; // [esp+B1h] [ebp-0x17]
  int v19; // [esp+B6h] [ebp-0x12]
  int v20; // [esp+C4h] [ebp-0x4]
  const char *keya; // [esp+CCh] [ebp+0x4]
  const char *keyb; // [esp+CCh] [ebp+0x4]
v3 = ((gbVFileSystem *)g_pVFileSys)->OpenFile(key, 0x201u);
  if ( v3 )
  {
    ((gbVFileSystem *)g_pVFileSys)->Read(&v16, 0xEu, v3);
    if ( !strcmp((const char *)&v16, (const char *)&off_580CFC) && (v17 == 1 || v17 == 2) )
    {
      v4 = *(_DWORD *)&v18[1];
      this->m_lpDI = (IDirectInput8 *)v18[0];
      ((gbVFileSystem *)g_pVFileSys)->Seek(v3, v4, 1);
      keya = 0;
      if ( (int)this->m_lpDI > 0 )
      {
        v5 = &this->m_keyStates[40];
        do
        {
          if ( v17 == 2 )
            ((gbVFileSystem *)g_pVFileSys)->Read(v5 - 35, 0x80u, v3);
          ((gbVFileSystem *)g_pVFileSys)->Read(v5, 0xCu, v3);
          ((gbVFileSystem *)g_pVFileSys)->Read(v5 - 3, 0xCu, v3);
          ((gbVFileSystem *)g_pVFileSys)->Read(v5 + 3, 4u, v3);
          ((gbVFileSystem *)g_pVFileSys)->Read(v5 + 4, 4u, v3);
          v6 = 8 * v5[3] * v5[4];
          v7 = malloc(v6);
          v5[5] = v7;
          if ( v7 )
            ((gbVFileSystem *)g_pVFileSys)->Read(v7, v6, v3);
          v5 += 41;
          ++keya;
        }
        while ( (int)keya < (int)this->m_lpDI );
}
      ((gbVFileSystem *)g_pVFileSys)->Seek(v3, v19, 1);
      keyb = 0;
      if ( (int)this->m_lpDI > 0 )
      {
        v8 = (unsigned __int16 *)&this->m_keyStates[228];
        do
        {
          ((gbVFileSystem *)g_pVFileSys)->Read(v8, 2u, v3);
          ((gbVFileSystem *)g_pVFileSys)->Read(v8 + 1, 2u, v3);
          v9 = 12 * *v8;
          v10 = malloc(v9);
          *((_DWORD *)v8 + 1) = v10;
          ((gbVFileSystem *)g_pVFileSys)->Read(v10, v9, v3);
          v11 = 6 * v8[1];
          v12 = malloc(v11);
          *((_DWORD *)v8 + 2) = v12;
          ((gbVFileSystem *)g_pVFileSys)->Read(v12, v11, v3);
          v13 = (GRPinput *)operator new(0x3Cu);
          v20 = 0;
          if ( v13 )
            v14 = ((GRPinput *)v13)->GetKey();
          else
            v14 = 0;
          v20 = -1;
          *((_DWORD *)v8 + 3) = v14;
          ((GRPinput *)v14)->InitDIKToKEY(v8);
          free(*((void **)v8 + 1));
          free(*((void **)v8 + 2));
          *((_DWORD *)v8 + 2) = 0;
          *((_DWORD *)v8 + 1) = 0;
          v8 += 8;
          ++keyb;
        }
        while ( (int)keyb < (int)this->m_lpDI );
      }
      ((gbVFileSystem *)g_pVFileSys)->CloseFile(v3);
    }
  }
}

// 0x004038F0
float * GRPinput::InitShiftedKeys(int nVal)
{
  double v2; // st7
  float *v3; // ecx
  int v4; // edx
  float v6[6]; // [esp+0x0] [ebp-0x18] BYREF

  v2 = -3.4028235e38;
  v6[0] = 3.4028235e38;
  v6[5] = -3.4028235e38;
  v6[1] = 3.4028235e38;
  v6[2] = 3.4028235e38;
  v6[3] = -3.4028235e38;
  v6[4] = -3.4028235e38;
  v3 = (float *)(nVal + 8);
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
  qmemcpy(pfVal, v6, 0x18u);
  return pfVal;
}

// 0x004039D0
void GRPinput::InitDIKToKEY(unsigned __int16 *pwVal)
{
  char *v3; // edi
  int v4; // ebx
  int v6; // ebx
  int v7; // ecx
  IDirectInput8 **v8; // edx
  int v9; // edx
  double v10; // st7
  IDirectInputDevice8 **v11; // edx
  int v12; // edx
  double v13; // st7
  IDirectInputDevice8 **v14; // edx
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
  int v29; // [esp+0xC] [ebp-0x2C]
  int v30; // [esp+0x10] [ebp-0x28]
  char pszBuf[8]; // [esp+0x14] [ebp-0x24] BYREF
  char v32; // [esp+0x1C] [ebp-0x1C] BYREF
  unsigned __int16 *pwVala; // [esp+0x3C] [ebp+0x4]

  v3 = pszBuf;
  v4 = 3;
  do
  {
    v3 += 12;
    --v4;
  }
  while ( v4 );
  v6 = 0;
  v30 = *((_DWORD *)pwVal + 1);
  this->m_lpDI = (IDirectInput8 *)2139095039;
  this->m_lpDIDKeyboard = (IDirectInputDevice8 *)2139095039;
  this->m_lpDIDMouse = (IDirectInputDevice8 *)2139095039;
  this->m_mouseSensitivity = -3.4028235e38;
  this->m_mouseMinX = -8388609;
  this->m_mouseMinY = -8388609;
  if ( *pwVal )
  {
    v7 = 0;
    do
    {
      v8 = (IDirectInput8 **)(v7 + *((_DWORD *)pwVal + 1));
      if ( *(float *)v8 < (double)*(float *)&this->m_lpDI )
        this->m_lpDI = *v8;
      v9 = *((_DWORD *)pwVal + 1);
      v10 = *(float *)(v7 + v9 + 4);
      v11 = (IDirectInputDevice8 **)(v7 + v9 + 4);
      if ( v10 < *(float *)&this->m_lpDIDKeyboard )
        this->m_lpDIDKeyboard = *v11;
      v12 = *((_DWORD *)pwVal + 1);
      v13 = *(float *)(v7 + v12 + 8);
      v14 = (IDirectInputDevice8 **)(v7 + v12 + 8);
      if ( v13 < *(float *)&this->m_lpDIDMouse )
        this->m_lpDIDMouse = *v14;
      v15 = (float *)(v7 + *((_DWORD *)pwVal + 1));
      if ( *v15 > (double)this->m_mouseSensitivity )
        this->m_mouseSensitivity = *v15;
      v16 = *((_DWORD *)pwVal + 1);
      v17 = *(float *)(v7 + v16 + 4);
      v18 = (int *)(v7 + v16 + 4);
      if ( v17 > *(float *)&this->m_mouseMinX )
        this->m_mouseMinX = *v18;
      v19 = *((_DWORD *)pwVal + 1);
      v20 = *(float *)(v7 + v19 + 8);
      v21 = (int *)(v7 + v19 + 8);
      if ( v20 > *(float *)&this->m_mouseMinY )
        this->m_mouseMinY = *v21;
      ++v6;
      v7 += 12;
    }
    while ( v6 < *pwVal );
  }
  pwVala = 0;
  *(float *)&this->m_lpDI = *(float *)&this->m_lpDI - g_fPAL3Timer;
  *(float *)&this->m_lpDIDMouse = *(float *)&this->m_lpDIDMouse - g_fPAL3Timer;
  this->m_mouseSensitivity = g_fPAL3Timer + this->m_mouseSensitivity;
  *(float *)&this->m_mouseMinY = g_fPAL3Timer + *(float *)&this->m_mouseMinY;
  if ( pwVal[1] )
  {
    v22 = 0;
    v29 = 0;
    do
    {
      v23 = &v32;
      v24 = (unsigned __int16 *)(*((_DWORD *)pwVal + 2) + v22);
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
      this->ProcessInputFrame(pszBuf);
      v22 = v29 + 6;
      v28 = (int)pwVala + 1 < pwVal[1];
      pwVala = (unsigned __int16 *)((char *)pwVala + 1);
      v29 += 6;
    }
    while ( v28 );
  }
}

// 0x00403B80
int GRPinput::ProcessInputFrame(char *pszBuf)
{
  char *v2; // ebp
  float *inited; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st6
  double v8; // st6
  double v10; // st5
  unsigned __int8 v11; // c0
  unsigned __int8 v12; // c3
  int v13; // esi
  double v14; // st7
  double v15; // st6
  int v16; // eax
  GRPinput *v17; // eax
  GRPinput *Key; // eax
  int v19; // ecx
  int v20; // eax
  int result; // eax
  char *m_joystickMinX; // ecx
  char *v23; // edi
  int m_mouseMaxY; // eax
  int v25; // eax
  int v26; // ebp
  int v27; // eax
  bool v28; // sf
  int v29; // eax
  char *v30; // ebp
  int v31; // eax
  int v32; // ecx
  IDirectInputDevice8 **v33; // ecx
  int v34; // edx
  __int16 v35; // fps
  double v36; // st7
  bool v37; // c0
  char v38; // c2
  bool v39; // c3
  float v40; // [esp+0x10] [ebp-0x54]
  float v41; // [esp+0x10] [ebp-0x54]
  float v42; // [esp+0x14] [ebp-0x50]
  float v43; // [esp+0x14] [ebp-0x50]
  float v44; // [esp+0x18] [ebp-0x4C]
  float v45; // [esp+0x18] [ebp-0x4C]
  float v46; // [esp+0x18] [ebp-0x4C]
  float v47; // [esp+0x1C] [ebp-0x48]
  int v48; // [esp+0x1C] [ebp-0x48]
  float v49; // [esp+0x20] [ebp-0x44]
  char *v50; // [esp+0x20] [ebp-0x44]
  float v51[6]; // [esp+0x28] [ebp-0x3C] BYREF
  float pfVal; // [esp+0x40] [ebp-0x24] BYREF
  float v53; // [esp+0x44] [ebp-0x20]
  float v54; // [esp+0x48] [ebp-0x1C]
  int v55; // [esp+0x60] [ebp-0x4]
  float pszBufc; // [esp+0x68] [ebp+0x4]
  float pszBufa; // [esp+0x68] [ebp+0x4]
  float pszBufb; // [esp+0x68] [ebp+0x4]

  v2 = pszBuf;
  inited = ((GRPinput *)&pfVal)->InitShiftedKeys((int)pszBuf);
  v42 = this->m_mouseSensitivity - *(float *)&this->m_lpDI;
  v5 = *(float *)&this->m_mouseMinY - *(float *)&this->m_lpDIDMouse;
  qmemcpy(v51, inited, sizeof(v51));
  v40 = v5;
  if ( v42 * 0.5 > v51[3] - v51[0] && v40 * 0.5 > v51[5] - v51[2] && this->m_joystickMaxX < 10 )
  {
    pszBufc = *(float *)&this->m_mouseMinX + *(float *)&this->m_lpDIDKeyboard;
    v44 = this->m_mouseSensitivity + *(float *)&this->m_lpDI;
    v6 = (*(float *)&this->m_mouseMinY + *(float *)&this->m_lpDIDMouse) * 0.5;
    v45 = v44 * 0.5;
    pfVal = v45;
    v53 = pszBufc * 0.5;
    v54 = v6;
    v7 = v51[2] + v51[5];
    v51[0] = v45;
    v51[2] = v54;
    v51[1] = v53;
    v8 = v7 * 0.5;
    v10 = v42 * 0.25;
    if ( v11 | v12 )
    {
      pszBufa = v10;
      v51[0] = v45 - pszBufa;
      if ( v8 > v6 )
      {
        v13 = 2;
        goto LABEL_10;
      }
      v13 = 1;
    }
    else
    {
      pszBufa = v10;
      v51[0] = v10 + v45;
      if ( v8 > v6 )
      {
        v13 = 3;
LABEL_10:
        v14 = v40 * 0.25;
        v15 = v14 + v51[2];
        goto LABEL_13;
      }
      v13 = 0;
    }
    v14 = v40 * 0.25;
    v15 = v51[2] - v14;
LABEL_13:
    v16 = *(&this->m_joystickMaxY + v13);
    v51[2] = v15;
    if ( v16 )
    {
      result = ((GRPinput *)*((GRPinput **)&this->m_joystickMaxY + v13))->ProcessInputFrame(v2);
    }
    else
    {
      pfVal = pszBufa;
      v47 = v51[1];
      v46 = v51[1];
      v49 = v14 + v51[2];
      v41 = pszBufa + v51[0];
      v43 = v51[2] - v14;
      pszBufb = v51[0] - pszBufa;
      v17 = (GRPinput *)operator new(0x3Cu);
      v55 = 0;
      if ( v17 )
        Key = ((GRPinput *)v17)->GetKey();
      else
        Key = 0;
      *(&this->m_joystickMaxY + v13) = (int)Key;
      *(float *)&Key->m_lpDI = pszBufb;
      *(float *)&Key->m_lpDIDKeyboard = v46;
      *(float *)&Key->m_lpDIDMouse = v43;
      Key->m_mouseSensitivity = v41;
      *(float *)&Key->m_mouseMinX = v47;
      *(float *)&Key->m_mouseMinY = v49;
      v19 = *(&this->m_joystickMaxY + v13);
      v20 = this->m_joystickMaxX + 1;
      v55 = -1;
      *(_DWORD *)(v19 + 40) = v20;
      result = ((GRPinput *)*((GRPinput **)&this->m_joystickMaxY + v13))->ProcessInputFrame(v2);
    }
    goto LABEL_28;
  }
  m_joystickMinX = (char *)this->m_joystickMinX;
  v23 = m_joystickMinX;
  if ( (this->m_joystickMinY - (int)m_joystickMinX) / 36 )
  {
    StrCopyRange(m_joystickMinX, m_joystickMinX, m_joystickMinX + 36);
    sub_404350(this->m_joystickMinX, 1 - (this->m_joystickMinX - (int)v23) / 36, pszBuf);
    sub_404380(v23, this->m_joystickMinX, pszBuf);
    v2 = pszBuf;
    result = this->m_joystickMinX + 36;
    this->m_joystickMinX = result;
  }
  else
  {
    m_mouseMaxY = this->m_mouseMaxY;
    if ( m_mouseMaxY && (unsigned int)((int)&m_joystickMinX[-m_mouseMaxY] / 36) > 1 )
    {
      LOBYTE(v25) = ((GRPinput *)&this->m_mouseMaxX)->IsAnyKeyPressed();
      v26 = v25;
    }
    else
    {
      v26 = 1;
    }
    LOBYTE(v27) = ((GRPinput *)&this->m_mouseMaxX)->IsAnyKeyPressed();
    v28 = v26 + v27 < 0;
    v29 = v26 + v27;
    v48 = v29;
    if ( v28 )
      v29 = 0;
    v30 = (char *)operator new(36 * v29);
    v50 = StrCopyRange((char *)this->m_mouseMaxY, v23, v30);
    sub_404350(v50, 1, pszBuf);
    StrCopyRange(v23, (char *)this->m_joystickMinX, v50 + 36);
    nullsub_2(this->m_mouseMaxY, this->m_joystickMinX);
    operator delete((void *)this->m_mouseMaxY);
    this->m_joystickMinY = (int)&v30[36 * v48];
    LOBYTE(v31) = ((GRPinput *)&this->m_mouseMaxX)->IsAnyKeyPressed();
    this->m_mouseMaxY = (int)v30;
    result = 9 * (v31 + 1);
    v32 = (int)&v30[4 * result];
    v2 = pszBuf;
    this->m_joystickMinX = v32;
  }
LABEL_28:
  v33 = (IDirectInputDevice8 **)(v2 + 8);
  v34 = 3;
  do
  {
    if ( *((float *)v33 - 2) < (double)*(float *)&this->m_lpDI )
    {
      result = (int)*(v33 - 2);
      this->m_lpDI = (IDirectInput8 *)result;
    }
    if ( *((float *)v33 - 1) < (double)*(float *)&this->m_lpDIDKeyboard )
    {
      result = (int)*(v33 - 1);
      this->m_lpDIDKeyboard = (IDirectInputDevice8 *)result;
    }
    if ( *(float *)v33 < (double)*(float *)&this->m_lpDIDMouse )
    {
      result = (int)*v33;
      this->m_lpDIDMouse = *v33;
    }
    if ( *((float *)v33 - 2) > (double)this->m_mouseSensitivity )
    {
      result = (int)*(v33 - 2);
      LODWORD(this->m_mouseSensitivity) = result;
    }
    if ( *((float *)v33 - 1) > (double)*(float *)&this->m_mouseMinX )
    {
      result = (int)*(v33 - 1);
      this->m_mouseMinX = result;
    }
    v36 = *(float *)v33;
    v37 = v36 < *(float *)&this->m_mouseMinY;
    v38 = 0;
    v39 = v36 == *(float *)&this->m_mouseMinY;
    LOWORD(result) = v35;
    if ( v36 > *(float *)&this->m_mouseMinY )
    {
      result = (int)*v33;
      this->m_mouseMinY = (int)*v33;
    }
    v33 += 3;
    --v34;
  }
  while ( v34 );
  return result;
}

// 0x00404020
GRPinput * GRPinput::GetKey()
{
  this->m_lpDI = 0;
  this->m_lpDIDKeyboard = 0;
  this->m_lpDIDMouse = 0;
  this->m_mouseSensitivity = 0.0;
  this->m_mouseMinX = 0;
  this->m_mouseMinY = 0;
  LOBYTE(this->m_mouseMaxX) = HIBYTE(this);
  this->m_mouseMaxY = 0;
  this->m_joystickMinX = 0;
  this->m_joystickMinY = 0;
  this->m_joystickMaxY = 0;
  this->m_mousept.x = 0;
  this->m_mousept.y = 0;
  this->m_mouseX = 0;
  this->m_joystickMaxX = 0;
  return this;
}

// 0x00404060
int GRPinput::GetCharKey()
{
  int *p_m_joystickMaxY; // ebx
  GRPinput **v3; // edi
  GRPinput *v4; // ebp
  int v6; // [esp+0x10] [ebp-0x18]

  p_m_joystickMaxY = &this->m_joystickMaxY;
  v3 = (GRPinput **)&this->m_joystickMaxY;
  v6 = 4;
  do
  {
    v4 = *v3;
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
int GRPinput::DecideKeyStatus(gbRay *a2, unsigned int a3)
{
  gbRay *v3; // ebx
  int result; // eax
  unsigned int v6; // edx
  gbVec3D *v7; // edi
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
  unsigned int v21; // [esp+0x14] [ebp-0x2C]
  int i; // [esp+0x18] [ebp-0x28]
  struct gbVec3D v23; // [esp+0x1C] [ebp-0x24] BYREF
  float v24; // [esp+0x28] [ebp-0x18]
  float v25; // [esp+0x2C] [ebp-0x14]
  float v26; // [esp+0x30] [ebp-0x10]
  gbVec3D v27; // [esp+0x34] [ebp-0xC] BYREF

  v3 = a2;
  result = ((gbRay *)a2)->IsColAABB((gbAABBox *)this);
  if ( result )
  {
    memset(&v23, 0, sizeof(v23));
    v21 = 0;
    for ( i = 0; ; i += 36 )
    {
      result = this->m_mouseMaxY;
      if ( !result )
        break;
      v6 = (this->m_joystickMinX - result) / 36;
      result = v21;
      if ( v21 >= v6 )
        break;
      v7 = (gbVec3D *)(i + this->m_mouseMaxY);
      ++*(_DWORD *)(a3 + 20);
      if ( ((gbRay *)v3)->IsColTriangle(v7, v7 + 1, v7 + 2, v23) )
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
            *v15 = *(_DWORD *)((char *)v15 + (_DWORD)v16);
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
    p_m_joystickMaxY = &this->m_joystickMaxY;
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
bool GRPinput::IsAnyKeyPressed()
{
  IDirectInputDevice8 *m_lpDIDKeyboard; // eax

  m_lpDIDKeyboard = this->m_lpDIDKeyboard;
  if ( m_lpDIDKeyboard )
    return (this->m_lpDIDMouse - m_lpDIDKeyboard) / 36;
  return (char)m_lpDIDKeyboard;
}

// 0x0046AEA0
void GRPinput::ProcessButtonHold(float fDelta)
{
  double v3; // st7
  double v4; // st7
  POINT pt; // [esp+0x10] [ebp-0x8]

  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( PtInRect((const RECT *)((char *)this + 100444), pt) && (g_Input.KeyInfo[0].Data & 0xF) != 1
    || (((GRPinput *)&g_Input)->GetCursorPos(), PtInRect((const RECT *)((char *)this + 100428), pt))
    && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    *((_BYTE *)this + 101172) = 0;
    *((_BYTE *)this + 101173) = 0;
  }
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( PtInRect((const RECT *)((char *)this + 100444), pt) && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
  {
    if ( !*((_BYTE *)this + 101173) )
    {
      v3 = fDelta + *((float *)this + 25292);
      *((_BYTE *)this + 101172) = 1;
      *((_BYTE *)this + 101173) = 0;
      *((float *)this + 25292) = v3;
      if ( v3 > 0.5 )
        ((void ( *)(GRPinput *, int, int, _DWORD))this->m_lpDI[24])(this, 1001, 406, 0);
    }
  }
  else
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    if ( PtInRect((const RECT *)((char *)this + 100428), pt) && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      if ( !*((_BYTE *)this + 101172) )
      {
        v4 = fDelta + *((float *)this + 25292);
        *((_BYTE *)this + 101172) = 0;
        *((_BYTE *)this + 101173) = 1;
        *((float *)this + 25292) = v4;
        if ( v4 > 0.5 )
          ((void ( *)(GRPinput *, int, int, _DWORD))this->m_lpDI[24])(this, 1001, 405, 0);
      }
    }
    else
    {
      *((_DWORD *)this + 25292) = 0;
    }
  }
}

// 0x0046F480
void GRPinput::ProcessMouseInput(float fVal)
{
  double v3; // st7
  double v4; // st7
  POINT pt; // [esp+0x10] [ebp-0x8]

  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( PtInRect((const RECT *)((char *)this + 26076), pt) && (g_Input.KeyInfo[0].Data & 0xF) != 1
    || (((GRPinput *)&g_Input)->GetCursorPos(), PtInRect((const RECT *)((char *)this + 26060), pt))
    && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    *((_BYTE *)this + 26804) = 0;
    *((_BYTE *)this + 26805) = 0;
  }
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( PtInRect((const RECT *)((char *)this + 26076), pt) && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
  {
    if ( !*((_BYTE *)this + 26805) )
    {
      v3 = fVal + *((float *)this + 6700);
      *((_BYTE *)this + 26804) = 1;
      *((_BYTE *)this + 26805) = 0;
      *((float *)this + 6700) = v3;
      if ( v3 > 0.5 )
        ((void ( *)(GRPinput *, int, int, _DWORD))this->m_lpDI[24])(this, 1001, 547, 0);
    }
  }
  else
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    if ( PtInRect((const RECT *)((char *)this + 26060), pt) && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      if ( !*((_BYTE *)this + 26804) )
      {
        v4 = fVal + *((float *)this + 6700);
        *((_BYTE *)this + 26804) = 0;
        *((_BYTE *)this + 26805) = 1;
        *((float *)this + 6700) = v4;
        if ( v4 > 0.5 )
          ((void ( *)(GRPinput *, int, int, _DWORD))this->m_lpDI[24])(this, 1001, 546, 0);
      }
    }
    else
    {
      *((_DWORD *)this + 6700) = 0;
    }
  }
}
