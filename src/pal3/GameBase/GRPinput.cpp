#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/GRPinput.h"

// Forward declarations for unnamed functions
int sub_402220(...);
int sub_4024F0(...);
int sub_402570(...);
int sub_402640(...);
int sub_402A90(...);
int sub_402B70(...);
int sub_402B90(...);
int sub_402BA0(...);
int sub_402BF0(...);
int sub_402C40(...);
int sub_402D00(...);
int sub_402D20(...);
int sub_402FA0(...);
int sub_403000(...);
int sub_403150(...);
int sub_403170(...);
int sub_403180(...);
int sub_403370(...);
int sub_4033F0(...);
int sub_403410(...);
int sub_403470(...);
int sub_4034B0(...);
int sub_4034E0(...);
int sub_403560(...);
int sub_403640(...);
int sub_4038F0(...);
int sub_4039D0(...);
int sub_403B80(...);
int sub_404020(...);
int sub_404060(...);
int sub_404150(...);
int sub_4042D0(...);

// Unnamed globals (extern)
extern unsigned char byte_56A634;
extern unsigned char byte_8AC5D8;
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
  void **p_m_lpDIDMouse; // edi
  void *v7; // edi
  void **p_m_lpDIDKeyboard; // edi

  if ( DirectInput8Create((HINSTANCE)hInst, 0x800u, &riidltf, &this->m_lpDI, 0) )
    return 0;
  p_m_lpDIDMouse = &this->m_lpDIDMouse;
  if ( !(*(int (__stdcall **)(void *, void *, void **, _DWORD))(*(_DWORD *)this->m_lpDI + 12))(
          this->m_lpDI,
          &unk_573810,
          &this->m_lpDIDMouse,
          0) )
  {
    (*(void (__stdcall **)(void *, void *))(*(_DWORD *)*p_m_lpDIDMouse + 44))(*p_m_lpDIDMouse, &unk_573C64);
    v7 = *p_m_lpDIDMouse;
    if ( flag )
      (*(void (__stdcall **)(void *, int, int))(*(_DWORD *)v7 + 52))(v7, hwnd, 5);
    else
      (*(void (__stdcall **)(void *, int, int))(*(_DWORD *)v7 + 52))(v7, hwnd, 6);
    this->AcquireDevices();
    if ( !*(_DWORD *)&this->m_mousept[6204] )
      return 0;
  }
  p_m_lpDIDKeyboard = &this->m_lpDIDKeyboard;
  if ( !(*(int (__stdcall **)(void *, void *, void **, _DWORD))(*(_DWORD *)this->m_lpDI + 12))(
          this->m_lpDI,
          &unk_573800,
          &this->m_lpDIDKeyboard,
          0) )
  {
    (*(void (__stdcall **)(void *, void *))(*(_DWORD *)*p_m_lpDIDKeyboard + 44))(*p_m_lpDIDKeyboard, &unk_573A5C);
    (*(void (__stdcall **)(void *, int, int))(*(_DWORD *)*p_m_lpDIDKeyboard + 52))(*p_m_lpDIDKeyboard, hwnd, 6);
    this->ReleaseDevices();
    if ( !*(_DWORD *)&this->m_mousept[6208] )
      return 0;
    sub_402640(this);
    GRPinput::Create((int)this);
  }
  GetCursorPos((LPPOINT)this->m_mousept);
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
  return (unsigned __int8)this->m_mousept[key + 56];
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

  *(_DWORD *)pOut = *(_DWORD *)&this->m_mousept[24];
  result = *(_DWORD *)&this->m_mousept[28];
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
    *(_DWORD *)&this->m_mousept[6204] = 1;
    result = (*(int (__stdcall **)(int))(*(_DWORD *)result + 28))(result);
    if ( result )
    {
      v3 = 0;
      while ( 1 )
      {
        result = (*(int (__stdcall **)(void *))(*(_DWORD *)this->m_lpDIDMouse + 28))(this->m_lpDIDMouse);
        if ( !result )
          break;
        if ( ++v3 >= 50 )
        {
          *(_DWORD *)&this->m_mousept[6204] = 0;
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
    *(_DWORD *)&this->m_mousept[6208] = 1;
    if ( (*(int (__stdcall **)(int))(*(_DWORD *)result + 28))(result) )
    {
      v3 = 0;
      while ( 1 )
      {
        result = (*(int (__stdcall **)(void *))(*(_DWORD *)this->m_lpDIDKeyboard + 28))(this->m_lpDIDKeyboard);
        if ( !result )
          break;
        if ( ++v3 >= 50 )
        {
          *(_DWORD *)&this->m_mousept[6208] = 0;
          return result;
        }
      }
    }
    return sub_402220(this);
  }
  return result;
}

// 0x00402400
GRPinput * GRPinput::GRPinput()
{
  char *v2; // edi
  int v3; // eax
  int *v4; // ebx
  int v5; // ebp
  int v6; // edi
  int v7; // ecx
  LONG y; // edx
  int v9; // edx
  int v10; // edi
  char *v11; // ebx
  int v12; // ebp
  struct tagPOINT Point; // [esp+18h] [ebp-8h] BYREF

  if ( *(_DWORD *)&this->m_mousept[6208] )
  {
    v2 = &this->m_mousept[326];
    if ( (*(int (__stdcall **)(void *, int, char *))(*(_DWORD *)this->m_lpDIDKeyboard + 36))(
           this->m_lpDIDKeyboard,
           256,
           &this->m_mousept[326]) )
    {
      LOBYTE(v3) = this->ReleaseDevices();
      return (GRPinput *)(char)v3;
    }
    v4 = (int *)&this->m_mousept[4096];
    v5 = 256;
    do
    {
      if ( *v4 )
        GRPinput::~GRPinput(this, *v4, (unsigned __int8)*v2 >> 7);
      ++v4;
      ++v2;
      --v5;
    }
    while ( v5 );
  }
  v3 = *(_DWORD *)&this->m_mousept[6204];
  if ( v3 )
  {
    if ( (*(int (__stdcall **)(void *, int, char *))(*(_DWORD *)this->m_lpDIDMouse + 36))(
           this->m_lpDIDMouse,
           20,
           &this->m_mousept[5120]) )
    {
      LOBYTE(v3) = this->AcquireDevices();
    }
    else
    {
      GetCursorPos(&Point);
      v6 = *(_DWORD *)&this->m_mousept[4];
      v7 = Point.x - *(_DWORD *)this->m_mousept;
      *(_DWORD *)this->m_mousept = Point.x;
      *(_DWORD *)&this->m_mousept[24] = v7;
      y = Point.y;
      *(_DWORD *)&this->m_mousept[4] = Point.y;
      v9 = y - v6;
      v10 = 256;
      *(_DWORD *)&this->m_mousept[28] = v9;
      v11 = &this->m_mousept[5132];
      v12 = 3;
      do
      {
        LOBYTE(v3) = GRPinput::~GRPinput(this, v10++, (unsigned __int8)*v11++ >> 7);
        --v12;
      }
      while ( v12 );
    }
  }
  return (GRPinput *)(char)v3;
}

// 0x004024F0
char sub_4024F0(int a2, int a3)
{
  int v4; // eax

  if ( a3 )
  {
    LOBYTE(v4) = *((_BYTE *)this + a2 + 104);
    if ( (unsigned __int8)v4 < 2u )
    {
      *((_BYTE *)this + a2 + 104) = 2;
      *(this + a2 + 158) = timeGetTime();
      v4 = *((_DWORD *)this + 16);
      *(this + 2 * a2 + 428) = v4;
      *(this + 2 * a2 + 429) = *((_DWORD *)this + 17);
    }
    else if ( (_BYTE)v4 == 2 )
    {
      *((_BYTE *)this + a2 + 104) = 3;
    }
  }
  else
  {
    LOBYTE(v4) = *((_BYTE *)this + a2 + 104);
    if ( (_BYTE)v4 == 3 || (_BYTE)v4 == 2 )
    {
      *((_BYTE *)this + a2 + 104) = 1;
    }
    else if ( (_BYTE)v4 == 1 )
    {
      *((_BYTE *)this + a2 + 104) = 0;
    }
  }
  return v4;
}

// 0x00402570
int sub_402570(int _this)
{
  int result; // eax
  _BYTE *v3; // esi
  char v4; // cl

  memset((void *)(this + 3872), 0, 0x10Cu);
  *(_WORD *)(this + 4140) = 0;
  result = 0;
  v3 = (_BYTE *)(this + 3969);
  do
  {
    v4 = result++ + 65;
    *v3++ = v4;
  }
  while ( (unsigned __int16)result < 0x1Au );
  *(_BYTE *)(this + 3933) = 43;
  *(_BYTE *)(this + 3963) = 123;
  *(_BYTE *)(this + 3965) = 125;
  *(_BYTE *)(this + 3964) = 124;
  *(_BYTE *)(this + 3931) = 58;
  *(_BYTE *)(this + 3911) = 34;
  qmemcpy((void *)(this + 3916), "<_>?)!@#$%^&*(", 14);
  *(_BYTE *)(this + 3968) = 126;
  return result;
}

// 0x00402A90
int sub_402A90(int a2, int a3, int a4)
{
  _DWORD *v4; // eax
  int v5; // ecx
  int v7; // ecx
  int v8; // ecx

  v4 = this + 4 * a3 + 1566;
  if ( a4 )
  {
    if ( *(this + 4 * a3 + 1567) )
    {
      v7 = *(this + *(this + 4 * a3 + 1568) + 1553);
      v4[3] = 0;
      *v4 = v7;
      v4[2] = v7;
    }
    v8 = v4[3];
    v4[1] = 0;
    v4[3] = v8 + 1;
  }
  else
  {
    v5 = *(this + 4 * a3 + 1567);
    v4[3] = 0;
    if ( !v5 )
    {
      v4[1] = a2;
      return 0;
    }
    *v4 = 0;
    if ( (unsigned int)(a2 - v5) > 0x64 )
    {
      v4[2] = 0;
      return v4[3];
    }
  }
  return v4[3];
}

// 0x00402B00
char GRPinput::SetJoystickAbs()
{
  int v1; // edx
  char *v2; // ecx
  char result; // al

  v1 = 0;
  v2 = &this->m_mousept[6216];
  result = 1;
  while ( *((_DWORD *)v2 + 3) != 1 || (*v2 & 3) == 0 )
  {
    ++v1;
    v2 += 16;
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
int sub_402B70()
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
void sub_402B90()
{
  *(float *)&byte_8AC5D8[904] = 12.0 + 12.0;
}

// 0x00402BA0
int sub_402BA0(int a1)
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
void sub_402BF0()
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al

  *this = &off_56A620;
  v2 = *((_DWORD *)this + 3);
  if ( v2 )
  {
    v3 = (_BYTE *)(v2 - 1);
    v4 = *(_BYTE *)(v2 - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  *((_DWORD *)this + 3) = 0;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
}

// 0x00402C40
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char sub_402C40(_BYTE *this, const char *a2, int a3)
{
  _BYTE *v3; // esi
  unsigned int v4; // kr04_4
  _BYTE *v5; // ebp
  unsigned int v6; // ebx
  int v7; // ecx
  char v8; // al
  char result; // al
  unsigned int v10; // eax
  int v11; // ecx

  v3 = this;
  *((_DWORD *)this + 4) = 1;
  v4 = strlen(a2) + 1;
  v5 = v3 + 8;
  v6 = v4 - 1;
  if ( v4 - 1 > 0xFFFFFFFD )
    std::_Xlen();
  v7 = *((_DWORD *)v3 + 3);
  if ( !v7 || (v8 = *(_BYTE *)(v7 - 1)) == 0 || v8 == -1 )
  {
    if ( v4 == 1 )
    {
      result = std::string::_Tidy(1);
      goto LABEL_15;
    }
    v10 = *((_DWORD *)v3 + 5);
    if ( v10 <= 0x1F && v10 >= v6 )
    {
LABEL_14:
      result = v4 - 1;
      qmemcpy(*((void **)v3 + 3), a2, v6);
      v11 = *((_DWORD *)v3 + 3);
      v3 = this;
      *((_DWORD *)v5 + 2) = v6;
      *(_BYTE *)(v11 + v6) = 0;
      goto LABEL_15;
    }
    std::string::_Tidy(1);
LABEL_13:
    v6->GetKeyState();
    goto LABEL_14;
  }
  if ( v4 != 1 )
    goto LABEL_13;
  result = v8 - 1;
  *(_BYTE *)(v7 - 1) = result;
  *((_DWORD *)v3 + 3) = 0;
  *((_DWORD *)v3 + 4) = 0;
  *((_DWORD *)v3 + 5) = 0;
LABEL_15:
  *((_DWORD *)v3 + 6) = 0;
  *((_DWORD *)v3 + 7) = a3;
  *((_DWORD *)v3 + 8) = 40;
  return result;
}

// 0x00402D00
char sub_402D00(int _this, float a2)
{
  char result; // al

  result = *(_BYTE *)(this + 4);
  if ( result )
    *(float *)(this + 24) = a2 + *(float *)(this + 24);
  return result;
}

// 0x00402D20
char sub_402D20(int _this)
{
  int v2; // eax
  int v3; // eax
  double v4; // st7
  int v5; // edi
  double v6; // st7
  double v7; // st7
  void *v8; // esi
  double v9; // st7
  __int64 v10; // rax
  double v11; // st7
  int v12; // edi
  void *v13; // esi
  float v15; // [esp+10h] [ebp-38h]
  float v16; // [esp+10h] [ebp-38h]
  float v17; // [esp+14h] [ebp-34h]
  float v18; // [esp+28h] [ebp-20h]
  int v19; // [esp+28h] [ebp-20h]
  signed int v20; // [esp+2Ch] [ebp-1Ch] BYREF
  int v21; // [esp+30h] [ebp-18h]
  float v22[2]; // [esp+34h] [ebp-14h] BYREF
  int v23; // [esp+3Ch] [ebp-Ch] BYREF
  float v24; // [esp+40h] [ebp-8h]
  int v25; // [esp+44h] [ebp-4h]

  LOBYTE(v2) = *(_BYTE *)(this + 4);
  if ( (_BYTE)v2 )
  {
    v3 = *(_DWORD *)(this + 28);
    if ( v3 )
    {
      v2 = v3 - 1;
      if ( !v2 )
      {
        v21 = *(_DWORD *)(this + 32);
        v4 = 40.0 / (double)MEMORY[0xBFD6D4];
        v5 = *(_DWORD *)(*(_DWORD *)(g_pGfxManager + 208) + 8);
        v20 = (unsigned int)(MEMORY[0xBFD6D0] - 10 * *(_DWORD *)(this + 16)) >> 1;
        *(float *)(v5 + 48) = 40.0 / (double)MEMORY[0xBFD6D0];
        *(float *)(v5 + 52) = v4;
        v6 = *(float *)(this + 24) - 1.5;
        if ( v6 < 0.0 )
          v6 = 0.0;
        v7 = 1.0 - v6 * 0.40000001;
        if ( v7 < 0.0 )
          v7 = 0.0;
        HIBYTE(v22[0]) = (__int64)(v7 * 255.0);
        if ( !HIBYTE(v22[0]) )
          *(_BYTE *)(this + 4) = 0;
        *(_DWORD *)(v5 + 44) = *(_DWORD *)(gbColorQuad *->gbColorQuad()v22,
                                            0xFFu,
                                            0xFFu,
                                            0xFFu,
                                            HIBYTE(v22[0]));
        v8 = *(void **)(this + 12);
        if ( !v8 )
          v8 = &byte_56A634;
        v17 = 1.0 - ((double)v21 + (double)v21) / (double)MEMORY[0xBFD6D4];
        v15 = ((double)v20 + (double)v20) / (double)MEMORY[0xBFD6D0] - 1.0;
        (*(void (**)(int, void *, _DWORD, _DWORD, int, int))(*(_DWORD *)v5 + 16))(
          v5,
          v8,
          LODWORD(v15),
          LODWORD(v17),
          1176256512,
          1176256512);
        LOBYTE(v2) = (*(int (**)(int))(*(_DWORD *)v5 + 8))(v5);
      }
    }
    else
    {
      LOBYTE(v2) = MEMORY[0xC116EC];
      v18 = *(float *)(this + 24) * 0.40000001;
      if ( MEMORY[0xC116EC] )
      {
        v23 = *(_DWORD *)(MEMORY[0xC116EC] + 160);
        v24 = *(float *)(MEMORY[0xC116EC] + 164);
        v25 = *(_DWORD *)(MEMORY[0xC116EC] + 168);
        v24 = v18 * 20.0 + v24 + 64.0;
        (gbCamera *->PointWorldToScr()(g_pCamera + 4), (struct gbVec3D *)&v23, v22, (float *)&v20);
        v9 = 1.0 - v18;
        if ( v9 < 0.0 )
          v9 = 0.0;
        v10 = (__int64)(v9 * 255.0);
        if ( !(_BYTE)v10 )
          *(_BYTE *)(this + 4) = 0;
        v11 = 32.0 / (double)MEMORY[0xBFD6D4];
        v12 = *(_DWORD *)(*(_DWORD *)(g_pGfxManager + 208) + 12);
        *(float *)(v12 + 48) = 32.0 / (double)MEMORY[0xBFD6D0];
        *(float *)(v12 + 52) = v11;
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
        *(_DWORD *)(v12 + 44) = v19;
        v13 = *(void **)(this + 12);
        if ( !v13 )
          v13 = &byte_56A634;
        v16 = v22[0] - 0.1;
        (*(void (**)(int, void *, _DWORD, signed int, int, int))(*(_DWORD *)v12 + 16))(
          v12,
          v13,
          LODWORD(v16),
          v20,
          1176256512,
          1176256512);
        LOBYTE(v2) = (*(int (**)(int))(*(_DWORD *)v12 + 8))(v12);
      }
    }
  }
  return v2;
}

// 0x00402FA0
int sub_402FA0(int a2)
{
  *((_DWORD *)this + 8) = a2;
  return a2;
}

// 0x00403000
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_BYTE *sub_403000(int _this, unsigned int a2)
{
  unsigned int v2; // esi
  size_t v4; // eax
  unsigned int v5; // eax
  int v6; // eax
  unsigned int v7; // edi
  _BYTE *v8; // ecx
  char v9; // al
  _BYTE *result; // eax
  int v11; // ecx
  _DWORD v12[4]; // [esp+0h] [ebp-24h] BYREF
  int v13; // [esp+10h] [ebp-14h]
  _DWORD *v14; // [esp+14h] [ebp-10h]
  int v15; // [esp+20h] [ebp-4h]
  _BYTE *v16; // [esp+2Ch] [ebp+8h]

  v2 = a2 | 0x1F;
  v14 = v12;
  v12[3] = this;
  v13 = a2 | 0x1F;
  if ( (a2 | 0x1F) > 0xFFFFFFFD )
  {
    v13 = a2;
    v2 = a2;
  }
  v4 = v2 + 2;
  v15 = 0;
  if ( (int)(v2 + 2) < 0 )
    v4 = 0;
  v16 = operator new(v4);
  v5 = *(_DWORD *)(this + 8);
  if ( v5 )
  {
    if ( v5 > v2 )
      v5 = v2;
    qmemcpy(v16 + 1, *(const void **)(this + 4), v5);
    v2 = v13;
  }
  v6 = *(_DWORD *)(this + 4);
  v7 = *(_DWORD *)(this + 8);
  if ( v6 )
  {
    v8 = (_BYTE *)(v6 - 1);
    v9 = *(_BYTE *)(v6 - 1);
    if ( !v9 || v9 == -1 )
      operator delete(v8);
    else
      *v8 = v9 - 1;
  }
  *(_DWORD *)(this + 8) = 0;
  result = v16 + 1;
  *(_DWORD *)(this + 4) = v16 + 1;
  *v16 = 0;
  *(_DWORD *)(this + 12) = v2;
  if ( v7 <= v2 )
    v2 = v7;
  v11 = *(_DWORD *)(this + 4);
  *(_DWORD *)(this + 8) = v2;
  *(_BYTE *)(v11 + v2) = 0;
  return result;
}

// 0x00403140
// attributes: thunk
int GRPinput::GetMousePos()
{
  return GRPinput::GetMouseFreePos();
}

// 0x00403150
int sub_403150()
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
void sub_403170()
{
  *(float *)&byte_8AC5D8[1552] = 12.0 + 12.0;
}

// 0x00403180
BOOL sub_403180(int a2, int a3)
{
  int v3; // eax

  if ( a2 >= 0 && (v3 = *((_DWORD *)this + 38), a2 < v3) && a3 >= 0 && a3 < *((_DWORD *)this + 39) )
    return *(_BYTE *)(*((_DWORD *)this + 40) + 8 * (a2 + a3 * v3) + 4) > 1u;
  else
    return 0;
}

// 0x00403370
int sub_403370(int _this)
{
  `eh vector constructor iterator'((void *)(this + 4), 0xA4u, 2, GRPinput::UnacquireJoystick, GRPinput::AcquireKeyboard);
  `eh vector constructor iterator'((void *)(this + 332), 0x10u, 2, GRPinput::UnacquireMouse, GRPinput::AcquireJoystick);
  memset((void *)this, 0, 0x16Cu);
  return this;
}

// 0x004033F0
void sub_4033F0()
{
  *this = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 0;
  *((_DWORD *)this + 3) = 0;
}

// 0x00403410
void sub_403410(void **this)
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
  v2 = *((_DWORD *)this + 3);
  if ( v2 )
  {
    GRPinput::GetCharKey(*((_DWORD *)this + 3));
    operator delete(v2);
    *((_DWORD *)this + 3) = 0;
  }
  *this = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 0;
  *((_DWORD *)this + 3) = 0;
}

// 0x00403470
void sub_403470()
{
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 34) = 0;
  *((_DWORD *)this + 35) = 0;
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 37) = 0;
  memset(this, 0, 0xA4u);
}

// 0x004034B0
void sub_4034B0(void **this)
{
  if ( *((_DWORD *)this + 40) )
    free(*((_DWORD *)this + 40));
  memset(this, 0, 0xA4u);
}

// 0x004034E0
void sub_4034E0(int _this)
{
  GRPinput::Update();
  `eh vector destructor iterator'(
    (void *)(this + 332),
    0x10u,
    2,
    (void (*)(void *))GRPinput::AcquireJoystick);
  `eh vector destructor iterator'((void *)(this + 4), 0xA4u, 2, (void (*)(void *))GRPinput::AcquireKeyboard);
}

// 0x00403560
int sub_403560()
{
  void **v2; // esi
  void **v3; // ebx
  void *v4; // edi
  void **v5; // ecx
  int result; // eax
  int v7; // [esp+4h] [ebp-4h]

  v7 = 0;
  if ( (int)*this <= 0 )
  {
    *this = 0;
  }
  else
  {
    v2 = (void **)(this + 85);
    v3 = (void **)(this + 41);
    do
    {
      if ( *v3 )
        free(*v3);
      memset(v3 - 40, 0, 0xA4u);
      if ( *(v2 - 1) )
      {
        free(*(v2 - 1));
        *(v2 - 1) = 0;
      }
      if ( *v2 )
      {
        free(*v2);
        *v2 = 0;
      }
      v4 = v2[1];
      if ( v4 )
      {
        GRPinput::GetCharKey(v2[1]);
        operator delete(v4);
        v2[1] = 0;
      }
      v5 = v2 - 2;
      v3 += 41;
      v2 += 4;
      *v5 = 0;
      v5[1] = 0;
      v5[2] = 0;
      v5[3] = 0;
      result = ++v7;
    }
    while ( v7 < *this );
    *this = 0;
  }
  return result;
}

// 0x00403640
void sub_403640(const char *a2)
{
  _DWORD *v2; // ebx
  struct gbVFile *v3; // edi
  int v4; // ecx
  _DWORD *v5; // ebx
  size_t v6; // esi
  void *v7; // eax
  unsigned __int16 *v8; // esi
  size_t v9; // ebx
  void *v10; // eax
  size_t v11; // ebx
  void *v12; // eax
  void *v13; // eax
  int v14; // eax
  int v16; // [esp+ACh] [ebp-1Ch] BYREF
  char v17; // [esp+B0h] [ebp-18h]
  _BYTE v18[5]; // [esp+B1h] [ebp-17h]
  int v19; // [esp+B6h] [ebp-12h]
  int v20; // [esp+C4h] [ebp-4h]
  int v21; // [esp+CCh] [ebp+4h]
  int v22; // [esp+CCh] [ebp+4h]

  v2 = this;
  this->Update();
  v3 = g_pVFileSys->OpenFile(a2, 0x201u);
  if ( v3 )
  {
    g_pVFileSys->Read(&v16, 0xEu, v3);
    if ( !strcmp((const char *)&v16, (const char *)&off_580CFC) && (v17 == 1 || v17 == 2) )
    {
      v4 = *(_DWORD *)&v18[1];
      *v2 = v18[0];
      g_pVFileSys->Seek(v3, v4, 1);
      v21 = 0;
      if ( (int)*v2 > 0 )
      {
        v5 = v2 + 36;
        do
        {
          if ( v17 == 2 )
            g_pVFileSys->Read(v5 - 35, 0x80u, v3);
          g_pVFileSys->Read(v5, 0xCu, v3);
          g_pVFileSys->Read(v5 - 3, 0xCu, v3);
          g_pVFileSys->Read(v5 + 3, 4u, v3);
          g_pVFileSys->Read(v5 + 4, 4u, v3);
          v6 = 8 * v5[3] * v5[4];
          v7 = malloc(v6);
          v5[5] = v7;
          if ( v7 )
            g_pVFileSys->Read(v7, v6, v3);
          v5 += 41;
          ++v21;
        }
        while ( v21 < *this );
        v2 = this;
      }
      g_pVFileSys->Seek(v3, v19, 1);
      v22 = 0;
      if ( (int)*v2 > 0 )
      {
        v8 = (unsigned __int16 *)(v2 + 83);
        do
        {
          g_pVFileSys->Read(v8, 2u, v3);
          g_pVFileSys->Read(v8 + 1, 2u, v3);
          v9 = 12 * *v8;
          v10 = malloc(v9);
          *((_DWORD *)v8 + 1) = v10;
          g_pVFileSys->Read(v10, v9, v3);
          v11 = 6 * v8[1];
          v12 = malloc(v11);
          *((_DWORD *)v8 + 2) = v12;
          g_pVFileSys->Read(v12, v11, v3);
          v13 = operator new(0x3Cu);
          v20 = 0;
          if ( v13 )
            v14 = v13->GetKey();
          else
            v14 = 0;
          v20 = -1;
          *((_DWORD *)v8 + 3) = v14;
          v8->InitDIKToKEY();
          free(*((void **)v8 + 1));
          free(*((void **)v8 + 2));
          *((_DWORD *)v8 + 2) = 0;
          *((_DWORD *)v8 + 1) = 0;
          v8 += 8;
          ++v22;
        }
        while ( v22 < *this );
      }
      g_pVFileSys->CloseFile(v3);
    }
  }
}

// 0x004038F0
float * sub_4038F0(float *a1, int a2)
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
void sub_4039D0(unsigned __int16 *a2)
{
  gbVec3D *v3; // edi
  int v4; // ebx
  int v6; // ebx
  int v7; // ecx
  float *v8; // edx
  int v9; // edx
  double v10; // st7
  float *v11; // edx
  int v12; // edx
  double v13; // st7
  float *v14; // edx
  float *v15; // edx
  int v16; // edx
  double v17; // st7
  float *v18; // edx
  int v19; // edx
  double v20; // st7
  float *v21; // edx
  int v22; // edx
  char *v23; // ecx
  unsigned __int16 *v24; // edx
  int v25; // ebx
  unsigned __int16 v26; // ax
  _DWORD *v27; // eax
  bool v28; // cc
  int v29; // [esp+Ch] [ebp-2Ch]
  int v30; // [esp+10h] [ebp-28h]
  _BYTE v31[8]; // [esp+14h] [ebp-24h] BYREF
  char v32; // [esp+1Ch] [ebp-1Ch] BYREF
  int v33; // [esp+3Ch] [ebp+4h]

  v3 = (gbVec3D *)v31;
  v4 = 3;
  do
  {
    gbVec3D::`default constructor closure'(v3);
    v3 = (gbVec3D *)((char *)v3 + 12);
    --v4;
  }
  while ( v4 );
  v6 = 0;
  v30 = *((_DWORD *)a2 + 1);
  *this = 3.4028235e38;
  *((_DWORD *)this + 1) = 3.4028235e38;
  *((_DWORD *)this + 2) = 3.4028235e38;
  *((_DWORD *)this + 3) = -3.4028235e38;
  *((_DWORD *)this + 4) = -3.4028235e38;
  *((_DWORD *)this + 5) = -3.4028235e38;
  if ( *a2 )
  {
    v7 = 0;
    do
    {
      v8 = (float *)(v7 + *((_DWORD *)a2 + 1));
      if ( *v8 < (double)*this )
        *this = *v8;
      v9 = *((_DWORD *)a2 + 1);
      v10 = *(float *)(v7 + v9 + 4);
      v11 = (float *)(v7 + v9 + 4);
      if ( v10 < *((_DWORD *)this + 1) )
        *((_DWORD *)this + 1) = *v11;
      v12 = *((_DWORD *)a2 + 1);
      v13 = *(float *)(v7 + v12 + 8);
      v14 = (float *)(v7 + v12 + 8);
      if ( v13 < *((_DWORD *)this + 2) )
        *((_DWORD *)this + 2) = *v14;
      v15 = (float *)(v7 + *((_DWORD *)a2 + 1));
      if ( *v15 > (double)*((_DWORD *)this + 3) )
        *((_DWORD *)this + 3) = *v15;
      v16 = *((_DWORD *)a2 + 1);
      v17 = *(float *)(v7 + v16 + 4);
      v18 = (float *)(v7 + v16 + 4);
      if ( v17 > *((_DWORD *)this + 4) )
        *((_DWORD *)this + 4) = *v18;
      v19 = *((_DWORD *)a2 + 1);
      v20 = *(float *)(v7 + v19 + 8);
      v21 = (float *)(v7 + v19 + 8);
      if ( v20 > *((_DWORD *)this + 5) )
        *((_DWORD *)this + 5) = *v21;
      ++v6;
      v7 += 12;
    }
    while ( v6 < *a2 );
  }
  v33 = 0;
  *this = *this - flt_8ACBEC;
  *((_DWORD *)this + 2) = *((_DWORD *)this + 2) - flt_8ACBEC;
  *((_DWORD *)this + 3) = flt_8ACBEC + *((_DWORD *)this + 3);
  *((_DWORD *)this + 5) = flt_8ACBEC + *((_DWORD *)this + 5);
  if ( a2[1] )
  {
    v22 = 0;
    v29 = 0;
    do
    {
      v23 = &v32;
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
      sub_403B80(v31);
      v22 = v29 + 6;
      v28 = ++v33 < a2[1];
      v29 += 6;
    }
    while ( v28 );
  }
}

// 0x00404020
int sub_404020(int a1)
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
int sub_404060(int _this)
{
  _DWORD *v2; // ebx
  _DWORD *v3; // edi
  void *v4; // ebp
  int v6; // [esp+10h] [ebp-18h]

  v2 = (_DWORD *)(this + 44);
  v3 = (_DWORD *)(this + 44);
  v6 = 4;
  do
  {
    v4 = (void *)*v3;
    if ( *v3 )
    {
      GRPinput::GetCharKey(*v3);
      operator delete(v4);
    }
    ++v3;
    --v6;
  }
  while ( v6 );
  *v2 = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
  *(_DWORD *)(this + 40) = 0;
  *(_DWORD *)(this + 32) = *(_DWORD *)(this + 28);
  operator delete(*(void **)(this + 28));
  *(_DWORD *)(this + 28) = 0;
  *(_DWORD *)(this + 32) = 0;
  *(_DWORD *)(this + 36) = 0;
  return 0;
}

// 0x00404150
unsigned int sub_404150(int _this, gbRay *a2, int a3)
{
  float *v3; // ebx
  unsigned int result; // eax
  unsigned int v6; // edx
  int *v7; // edi
  double v8; // st7
  double v9; // st7
  double v10; // st7
  float v11; // edx
  float v12; // ecx
  float v13; // eax
  int *v14; // ecx
  _DWORD *v15; // eax
  char *v16; // edi
  int v17; // edx
  int v18; // ebx
  _DWORD *v19; // edi
  int v20; // ebp
  unsigned int v21; // [esp+14h] [ebp-2Ch]
  int i; // [esp+18h] [ebp-28h]
  float v23; // [esp+1Ch] [ebp-24h] BYREF
  float v24; // [esp+20h] [ebp-20h]
  float v25; // [esp+24h] [ebp-1Ch]
  float v26; // [esp+28h] [ebp-18h]
  float v27; // [esp+2Ch] [ebp-14h]
  float v28; // [esp+30h] [ebp-10h]
  _DWORD v29[3]; // [esp+34h] [ebp-Ch] BYREF

  v3 = (float *)a2;
  result = a2->IsColAABB((struct gbAABBox *)this);
  if ( result )
  {
    v23 = 0.0;
    v24 = 0.0;
    v25 = 0.0;
    v21 = 0;
    for ( i = 0; ; i += 36 )
    {
      result = *(_DWORD *)(this + 28);
      if ( !result )
        break;
      v6 = (int)(*(_DWORD *)(this + 32) - result) / 36;
      result = v21;
      if ( v21 >= v6 )
        break;
      v7 = (int *)(i + *(_DWORD *)(this + 28));
      ++*(_DWORD *)(a3 + 20);
      if ( (gbRay *->IsColTriangle()v3,
             (struct gbVec3D *)v7,
             (struct gbVec3D *)(v7 + 3),
             (struct gbVec3D *)(v7 + 6),
             (struct gbVec3D *)&v23) )
      {
        v26 = v23 - *v3;
        v8 = v24 - v3[1];
        *(float *)v29 = v26;
        v27 = v8;
        v9 = v25 - v3[2];
        *(float *)&v29[1] = v27;
        v28 = v9;
        *(float *)&v29[2] = v28;
        v10 = (gbVec3D *->Length()v29);
        if ( v10 < *(float *)a3 )
        {
          v11 = v24;
          v12 = v23;
          *(float *)a3 = v10;
          v13 = v25;
          *(_BYTE *)(a3 + 16) = 1;
          *(float *)(a3 + 8) = v11;
          *(float *)(a3 + 4) = v12;
          *(float *)(a3 + 12) = v13;
          v14 = v7;
          v15 = (_DWORD *)(a3 + 28);
          v16 = (char *)v7 - a3 - 24;
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
          v3 = (float *)a2;
        }
      }
      ++v21;
    }
    v19 = (_DWORD *)(this + 44);
    v20 = 4;
    do
    {
      if ( *v19 )
        result = v3->DecideKeyStatus(a3);
      ++v19;
      --v20;
    }
    while ( v20 );
  }
  return result;
}

// 0x004042D0
int sub_4042D0()
{
  int result; // eax

  result = *((_DWORD *)this + 1);
  if ( result )
    return (*((_DWORD *)this + 2) - result) / 36;
  return result;
}
