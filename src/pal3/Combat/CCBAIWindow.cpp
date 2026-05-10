#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBAIWindow.h"
#include "pal3/gen/CCBControlWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_519AF0(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Co_12[];
extern int dword_BFD6D0;
extern int dword_BFD6D4;

// 0x004DFE00
int CCBAIWindow::SetText(int a2, int a3)
{
  int result; // eax
  int v5; // [esp+10h] [ebp+Ch]
  int v6; // [esp+14h] [ebp+10h]

  sprintf(&this->_data[280 * *(_DWORD *)&this->_data[16] + 24], "%d", v5);
  *((float *)this + 70 * *(_DWORD *)&this->_data[16] + 71) = ((double)a2 + (double)a2) / (double)dword_BFD6D0 - 1.0;
  *((float *)this + 70 * *(_DWORD *)&this->_data[16] + 72) = 1.0 - ((double)a3 + (double)a3) / (double)dword_BFD6D4;
  *(_DWORD *)&this->_data[280 * *(_DWORD *)&this->_data[16] + 20] = 2;
  *((_DWORD *)this + 70 * *(_DWORD *)&this->_data[16] + 74) = 1094713344;
  *((_DWORD *)this + 70 * *(_DWORD *)&this->_data[16] + 70) = v6;
  result = *(_DWORD *)&this->_data[16] + 1;
  *(_DWORD *)&this->_data[16] = result;
  return result;
}

// 0x0051CA50
CCBAIWindow::CCBAIWindow(int a2)
{
  int v3; // edi
  char *v4; // esi
  void (***v5)(_DWORD, int); // ecx

  if ( a2 == 1 )
  {
    this->_data[176] = 0;
    v3 = 0;
    v4 = (char *)&this->_data[108];
    do
    {
      v5 = *(void (****)(_DWORD, int))v4;
      if ( *(_DWORD *)&this->_data[172] == v3 )
        (**v5)(v5, 1);
      else
        (**v5)(v5, 0);
      ++v3;
      v4 += 4;
    }
    while ( v3 < 5 );
  }
  (CCBAIWindow *)((UIWnd *)this)->Destroy(a2);
}

// 0x0051CAA0
CCBAIWindow::~CCBAIWindow()
{
  int v2; // ebx
  CCBAIWindow *v3; // edi
  int v5; // [esp+Ch] [ebp-Ch]

  ((UIListBox *)this)->SetScroll();
  v2 = *(_DWORD *)&this->_data[16];
  v5 = *(_DWORD *)&this->_data[20];
  v3 = (CCBAIWindow *)*(CCBAIWindow **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->_data[168] + 1160) + 20) + 68);
  v3->SetText(v2 + 105, v5 + 51);
  v3->SetText(v2 + 117, v5 + 76);
  v3->SetText(v2 + 107, v5 + 102);
}

// 0x0051CB60
char CCBAIWindow::Reset(_DWORD *a1)
{
  UIFrameWnd *v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (UIFrameWnd *)operator new(0x98u);
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
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CCE0
char CCBAIWindow::Destroy(_DWORD *a1)
{
  UIWnd *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (UIWnd *)operator new(0x74u);
  v6 = 0;
  if ( v1 )
    v2 = (_DWORD *)v1->ctor_9310();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CD90
char CCBAIWindow::OnMessage(UIListBox **a1)
{
  UIListBox *v1; // eax
  UIListBox *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (UIListBox *)operator new(0x6Cu);
  v6 = 0;
  if ( v1 )
    v2 = (UIListBox *)sub_519AF0(v1);
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CE40
char CCBAIWindow::Update(_DWORD *a1)
{
  CCBUI *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (CCBUI *)operator new(0x80u);
  v6 = 0;
  if ( v1 )
    v2 = (_DWORD *)v1->ChangeNumTxt();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CF00
char CCBAIWindow::ShowWindow(_DWORD *a1)
{
  CCBControlWindow *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (CCBControlWindow *)operator new(0x54u);
  v6 = 0;
  if ( v1 )
    v2 = (_DWORD *)v1->DefaultKey();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}
