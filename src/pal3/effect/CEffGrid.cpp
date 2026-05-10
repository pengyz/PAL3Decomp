#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffGrid.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4C9550(...);
int sub_4CAB30(...);
int sub_4CABE0(...);
int sub_4CAC70(...);

// Unnamed globals (extern)
extern char aDProjectPal3Co_14[];
extern char aNewFailInCeffg[];
extern void *off_56F62C;
extern void *off_56F914;
extern void *off_56F920;
extern void *off_56F95C;
extern int unk_5D4D3C;
extern int unk_5D4D7C;
extern int unk_5D4DAC;
extern int unk_5D4DB8;
extern int unk_5D4DC4;
extern int unk_5D4DCC;
extern int unk_5D4DD4;
extern int unk_5D4DF4;
extern int unk_5D4E00;
extern int unk_5D4E24;
extern int unk_5D4E30;
extern int unk_5D4E38;
extern int unk_5D4E40;
extern int unk_5D4FFC;
extern int unk_5D5008;
extern int unk_5D5014;
extern int unk_5D5038;
extern int unk_5D5040;
extern int unk_5D5048;
extern int unk_5D5050;
extern int unk_5D51B0;
extern int unk_FFFFFF;

// 0x004C9610
CEffGrid::CEffGrid()
{
  _DWORD *v0; // eax

  v0 = (_DWORD *)operator new(0x10B8u);
  if ( v0 )
  sub_4C9550(v0);
  else
  0;
}

// 0x004C9650
CEffGrid::~CEffGrid()
{
  int v2; // edi
  void *v3; // eax
  int v4; // ebp
  gbRefObject *v5; // ecx
  int v6; // esi
  int v7; // eax
  bool v8; // cc
  int v9; // edi

  v2 = a1 + 12;
  *(_DWORD *)a1 = &off_56F920;
  *(_DWORD *)(a1 + 12) = &off_56F914;
  v3 = (void *)*(void **)(a1 + 48);
  v4 = 0;
  if ( v3 )
    operator delete(v3);
  if ( *(_DWORD *)(a1 + 52) )
    operator delete(*(void **)(a1 + 52));
  if ( *(_DWORD *)(a1 + 56) )
    operator delete(*(void **)(a1 + 56));
  v5 = (gbRefObject *)*(gbRefObject **)(a1 + 60);
  if ( v5 )
    v5->Release();
  if ( *(_DWORD *)(a1 + 64) )
    operator delete(*(void **)(a1 + 64));
  v6 = a1 != 0 ? v2 : 0;
  *(_DWORD *)v6 = &off_56F95C;
  v7 = *(_DWORD *)(v6 + 0x1C);
  v8 = v7 <= 0;
  if ( !v7 )
  {
    if ( !*(_DWORD *)(a1 != 0 ? v2 + 0x20 : 32) )
      goto LABEL_18;
    v8 = 1;
  }
  if ( !v8 )
  {
    v9 = 0;
    do
    {
      operator delete(*(void **)(*(_DWORD *)(v6 + 12) + v9));
      ++v4;
      *(_DWORD *)(*(_DWORD *)(v6 + 12) + v9) = 0;
      v9 += 152;
    }
    while ( v4 < *(_DWORD *)(v6 + 28) );
  }
  operator delete(*(void **)(v6 + 12));
  *(_DWORD *)(v6 + 12) = 0;
  *(_DWORD *)(v6 + 28) = 0;
  *(_DWORD *)(v6 + 32) = 0;
LABEL_18:
  *(_DWORD *)a1 = &off_56F62C;
}

// 0x004C98F0
char CEffGrid::Create(int a2)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v3; // esp
  _DWORD *v5; // eax
  int v6; // ebx
  int v7; // edi
  int v8; // edi
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  __int64 v12; // rax
  int v13; // ecx
  int d07C; // ebx
  _DWORD *v15; // eax
  int v16; // ebx
  int v17; // ebp
  int v18; // ebx
  int v19; // edi
  int v20; // ebp
  _DWORD *v21; // eax
  int v22; // ebp
  _DWORD *v23; // ebx
  int v24; // ebp
  int v25; // ebp
  _DWORD *v26; // eax
  int v27; // ebp
  _DWORD *v28; // ebx
  int v29; // ebp
  int d034; // ecx
  _DWORD *v32; // [esp+0h] [ebp-1010h]
  _DWORD *v33; // [esp+0h] [ebp-1010h]
  _DWORD *v34; // [esp+0h] [ebp-1010h]
  _BYTE v35[1024]; // [esp+4h] [ebp-100Ch] BYREF
  char pExceptionObject[1024]; // [esp+404h] [ebp-C0Ch] BYREF
  char ArgList[1024]; // [esp+804h] [ebp-80Ch] BYREF
  char v38[1024]; // [esp+C04h] [ebp-40Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v39; // [esp+1004h] [ebp-Ch]
  void *v40; // [esp+1008h] [ebp-8h]
  int v41; // [esp+100Ch] [ebp-4h]

  v41 = -1;
  ExceptionList = (struct _EXCEPTION_REGISTRATION_RECORD *)NtCurrentTeb()->NtTib.ExceptionList;
  v40 = (void *)&loc_5667EA;
  v39 = ExceptionList;
  v3 = (void *)alloca(4100);
  v5 = (_DWORD *)operator new(0x4C0u);
  this->_d018 = (int)v5;
  if ( v5 )
  {
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v7 + this->_d018) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v7 + this->_d018) )
        break;
      v7 += 152;
      ++v6;
      if ( v7 >= 1216 )
      {
        v8 = 0;
        this->_d028 = 8;
        this->_d02C = 10;
        v9 = 0;
        do
        {
          *(_BYTE *)(v9 + this->_d018 + 148) = 0;
          v10 = 0;
          if ( this->_d02C > 0 )
          {
            v11 = 0;
            do
            {
              ++v10;
              v11 += 72;
              *(_BYTE *)(*(_DWORD *)(v9 + this->_d018) + v11 - 8) = 0;
            }
            while ( v10 < this->_d02C );
          }
          ++v8;
          v9 += 152;
        }
        while ( v8 < this->_d028 );
        goto LABEL_10;
      }
    }
    if ( v6 > 0 && v6 - 1 >= 0 )
    {
      v19 = 152 * (v6 - 1);
      do
      {
        operator delete(*(void **)(v19 + this->_d018));
        v19 -= 152;
        --v6;
      }
      while ( v6 );
    }
    operator delete((void *)this->_d018);
  }
LABEL_10:
  this->_d070 = (__int64)*(float *)(a2 + 224);
  v12 = (__int64)*(float *)(a2 + 232);
  this->_d074 = v12;
  v13 = *(_DWORD *)(a2 + 228);
  this->_d07C = this->_d070 * v12;
  this->_d078 = v13;
  this->_d090 = *(_DWORD *)(a2 + 180);
  this->_d0A0 = *(_DWORD *)(a2 + 184);
  this->_d0A4 = *(_DWORD *)(a2 + 188);
  this->_d0A8 = *(_DWORD *)(a2 + 192);
  this->_d094 = *(_DWORD *)(a2 + 216);
  this->_d098 = *(_DWORD *)(a2 + 196);
  this->_d09C = *(_DWORD *)(a2 + 220);
  this->_b045 = *(_BYTE *)(a2 + 213);
  this->_b046 = *(_BYTE *)(a2 + 215);
  this->_b047 = *(_BYTE *)(a2 + 176);
  this->_d048 = (int)&unk_FFFFFF;
  this->_d054 = *(_DWORD *)(a2 + 204);
  this->_d080 = *(_DWORD *)(a2 + 244);
  this->_d084 = *(_DWORD *)(a2 + 248);
  this->_d088 = *(_DWORD *)(a2 + 268);
  this->_d08C = *(_DWORD *)(a2 + 252);
  sub_4CAB30(this->_pad_000, *(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  d07C = this->_d07C;
  v15 = (_DWORD *)operator new(68 * d07C);
  v32 = v15;
  v41 = 0;
  if ( v15 )
  {
    v16 = d07C - 1;
    v17 = (int)v15;
    if ( v16 >= 0 )
    {
      v18 = v16 + 1;
      do
      {
        ArraySort(v17, 12, 4, gbVec3D::`default constructor closure');
        v17 += 68;
        --v18;
      }
      while ( v18 );
      v15 = v32;
    }
  }
  else
  {
    v15 = 0;
  }
  v41 = -1;
  this->_d030 = (int)v15;
  if ( !v15 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffg, aDProjectPal3Co_14, 115),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v20 = (this->_d070 + 1) * (this->_d074 + 1);
  v21 = (_DWORD *)operator new(12 * v20);
  v33 = v21;
  v41 = 1;
  if ( v21 )
  {
    v22 = v20 - 1;
    v23 = v21;
    if ( v22 >= 0 )
    {
      v24 = v22 + 1;
      do
      {
        ((void (*)(_DWORD *))gbVec3D::`default constructor closure')(v23);
        v23 += 3;
        --v24;
      }
      while ( v24 );
      v21 = v33;
    }
  }
  else
  {
    v21 = 0;
  }
  v25 = (this->_d070 + 1) * (this->_d074 + 1);
  this->_d034 = (int)v21;
  v26 = (_DWORD *)operator new(12 * v25);
  v34 = v26;
  v41 = 2;
  if ( v26 )
  {
    v27 = v25 - 1;
    v28 = v26;
    if ( v27 >= 0 )
    {
      v29 = v27 + 1;
      do
      {
        ((void (*)(_DWORD *))gbVec3D::`default constructor closure')(v28);
        v28 += 3;
        --v29;
      }
      while ( v29 );
      v26 = v34;
    }
  }
  else
  {
    v26 = 0;
  }
  d034 = this->_d034;
  v41 = -1;
  this->_d038 = (int)v26;
  if ( !d034 || !v26 )
  {
    qmemcpy(v35, ((Logger *)v38)->FormatException(aNewFailInCeffg, aDProjectPal3Co_14, 124), sizeof(v35));
    _CxxThrowException(v35, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  sub_4CABE0((int)this, a2 + 40);
  sub_4CAC70((int)this);
  return 1;
}

// 0x004CA9A0
void * CEffGrid::GetEditorObjDescription(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = (void *)&unk_5D5050;
      break;
    case 1:
      result = (void *)&unk_5D4E40;
      break;
    case 2:
      result = (void *)&unk_5D4E38;
      break;
    case 3:
      result = (void *)&unk_5D4E30;
      break;
    case 4:
      result = (void *)&unk_5D4E24;
      break;
    case 5:
      result = (void *)&unk_5D5048;
      break;
    case 6:
      result = (void *)&unk_5D5040;
      break;
    case 7:
      result = (void *)&unk_5D5038;
      break;
    case 8:
      result = (void *)&unk_5D4E00;
      break;
    case 9:
      result = (void *)&unk_5D4DF4;
      break;
    case 10:
      result = (void *)&unk_5D51B0;
      break;
    case 12:
      result = (void *)&unk_5D4DD4;
      break;
    case 13:
      result = (void *)&unk_5D4DCC;
      break;
    case 14:
      result = (void *)&unk_5D4DC4;
      break;
    case 15:
      result = (void *)&unk_5D4DB8;
      break;
    case 16:
      result = (void *)&unk_5D4DAC;
      break;
    case 17:
      result = (void *)&unk_5D5014;
      break;
    case 18:
      result = (void *)&unk_5D5008;
      break;
    case 19:
      result = (void *)&unk_5D4FFC;
      break;
    case 20:
      result = (void *)&unk_5D4D7C;
      break;
    default:
      result = (void *)&unk_5D4D3C;
      break;
  }
  return result;
}
