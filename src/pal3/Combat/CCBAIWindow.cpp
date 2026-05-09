#include "pal3/gen/CCBAIWindow.h"

// 0x004DFE00
int CCBAIWindow::SetText(int a2, int a3)
{
  int result; // eax
  int v5; // [esp+10h] [ebp+Ch]
  int v6; // [esp+14h] [ebp+10h]

  sprintf(&this->UIFrameWnd[280 * *(_DWORD *)&this->UIFrameWnd[16] + 24], "%d", v5);
  *((float *)this + 70 * *(_DWORD *)&this->UIFrameWnd[16] + 71) = ((double)a2 + (double)a2) / (double)MEMORY[0xBFD6D0]
                                                                - 1.0;
  *((float *)this + 70 * *(_DWORD *)&this->UIFrameWnd[16] + 72) = 1.0
                                                                - ((double)a3 + (double)a3) / (double)MEMORY[0xBFD6D4];
  *(_DWORD *)&this->UIFrameWnd[280 * *(_DWORD *)&this->UIFrameWnd[16] + 20] = 2;
  *((_DWORD *)this + 70 * *(_DWORD *)&this->UIFrameWnd[16] + 74) = 1094713344;
  *((_DWORD *)this + 70 * *(_DWORD *)&this->UIFrameWnd[16] + 70) = v6;
  result = *(_DWORD *)&this->UIFrameWnd[16] + 1;
  *(_DWORD *)&this->UIFrameWnd[16] = result;
  return result;
}

// 0x0051CA50
int sub_51CA50(int this, int a2)
{
  int v3; // edi
  void (__thiscall ****v4)(_DWORD, int); // esi
  void (__thiscall ***v5)(_DWORD, int); // ecx

  if ( a2 == 1 )
  {
    *(_BYTE *)(this + 176) = 0;
    v3 = 0;
    v4 = (void (__thiscall ****)(_DWORD, int))(this + 108);
    do
    {
      v5 = *v4;
      if ( *(_DWORD *)(this + 172) == v3 )
        (**v5)(v5, 1);
      else
        (**v5)(v5, 0);
      ++v3;
      ++v4;
    }
    while ( v3 < 5 );
  }
  return (int *->Destroy()this, a2);
}

// 0x0051CAA0
int sub_51CAA0(int *this)
{
  int v2; // ebx
  char *v3; // edi
  int v5; // [esp+Ch] [ebp-Ch]

  this->SetScroll();
  v2 = *(this + 4);
  v5 = *(this + 5);
  v3 = *(char **)(*(_DWORD *)(*(_DWORD *)(*(this + 42) + 1160) + 20) + 68);
  v3->SetText(v2 + 105, v5 + 51, (int)*(float *)(*(this + 39) + 156), -6243078);
  v3->SetText(v2 + 117, v5 + 76, (int)*(float *)(*(this + 40) + 156), -270174);
  return v3->SetText(v2 + 107, v5 + 102, (int)*(float *)(*(this + 41) + 156), -349995);
}

// 0x0051CB60
char sub_51CB60(_DWORD *a1)
{
  _BYTE *v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = operator new(0x98u);
  v6 = 0;
  if ( v1 )
    v1->UIFrameWnd();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CCE0
char sub_51CCE0(_DWORD *a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = operator new(0x74u);
  v6 = 0;
  if ( v1 )
    v2 = sub_519310(v1);
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CD90
char sub_51CD90(_DWORD *a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = operator new(0x6Cu);
  v6 = 0;
  if ( v1 )
    v2 = sub_519AF0(v1);
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CE40
char sub_51CE40(_DWORD *a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = operator new(0x80u);
  v6 = 0;
  if ( v1 )
    v2 = v1->ChangeNumTxt();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CF00
char sub_51CF00(_DWORD *a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = operator new(0x54u);
  v6 = 0;
  if ( v1 )
    v2 = v1->DefaultKey();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}
