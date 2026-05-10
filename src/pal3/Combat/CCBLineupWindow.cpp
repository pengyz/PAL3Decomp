#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBControlWindow.h"
#include "pal3/gen/CCBItemWindow.h"
#include "pal3/gen/CCBMagicWindow.h"
#include "pal3/gen/CCBProtectWindow.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIStatic.h"
#include "pal3/gen/UIWnd.h"

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Co_12[];
extern unsigned char byte_17ACF80;

// 0x0051CFB0
CCBLineupWindow::CCBLineupWindow(_DWORD *a1)
{
  CCBControlWindow *v1; // eax
  _DWORD *Button; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (CCBControlWindow *)((operator *)0x80u)->new();
  v6 = 0;
  if ( v1 )
    Button = (_DWORD *)v1->CreateButton();
  else
    Button = 0;
  v6 = -1;
  *a1 = Button;
  if ( !Button )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D070
CCBLineupWindow::~CCBLineupWindow(_DWORD *a1)
{
  CCBItemWindow *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (CCBItemWindow *)((operator *)0x7Cu)->new();
  v6 = 0;
  if ( v1 )
    v2 = (_DWORD *)v1->Update();
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

// 0x0051D120
char CCBLineupWindow::Reset(_DWORD *a1)
{
  CCBMagicWindow *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (CCBMagicWindow *)((operator *)0x68u)->new();
  v6 = 0;
  if ( v1 )
    v2 = (_DWORD *)v1->ForbidPage();
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

// 0x0051D1D0
char CCBLineupWindow::Create(_DWORD *a1)
{
  CCBMagicWindow *v1; // eax
  _DWORD *ActivePage; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (CCBMagicWindow *)((operator *)0xB4u)->new();
  v6 = 0;
  if ( v1 )
    ActivePage = (_DWORD *)v1->GetActivePage();
  else
    ActivePage = 0;
  v6 = -1;
  *a1 = ActivePage;
  if ( !ActivePage )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D290
char CCBLineupWindow::Destroy(_DWORD *a1)
{
  UIFrameWnd *v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (UIFrameWnd *)((operator *)0x98u)->new();
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
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D340
char CCBLineupWindow::OnMessage(_DWORD *a1)
{
  UIStatic *v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (UIStatic *)((operator *)0xF8u)->new();
  v6 = 0;
  if ( v1 )
    v1->UIStatic();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D3F0
char CCBLineupWindow::Update(_DWORD *a1)
{
  UIScene *v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (UIScene *)((operator *)0x158u)->new();
  v6 = 0;
  if ( v1 )
    v1->_UIScene();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D4A0
char CCBLineupWindow::Render(_DWORD *a1)
{
  UIWnd *v1; // eax
  _DWORD *v2; // eax
  char pExceptionObject[1024]; // [esp+4h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+404h] [ebp-40Ch] BYREF
  int v6; // [esp+80Ch] [ebp-4h]

  v1 = (UIWnd *)((operator *)0xF4u)->new();
  v6 = 0;
  if ( v1 )
    v2 = (_DWORD *)v1->ctor_F7F0();
  else
    v2 = 0;
  v6 = -1;
  *a1 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D580
// attributes: thunk
int CCBLineupWindow::IsPtOnFace()
{
  return ?IsPtOnFace@CCBLineupWindow@@QAEHUtagPOINT@@@Z();
}

// 0x0051D590
int CCBLineupWindow::IsPtOnFace()
{
  *(_DWORD *)&byte_17ACF80[908] = 1094713344;
  return 1094713344;
}

// 0x0051D5A0
// attributes: thunk
void CCBLineupWindow::IsPtOnInitPos()
{
  ?IsPtOnInitPos@CCBLineupWindow@@QAEHUtagPOINT@@@Z();
}

// 0x0051D5B0
void CCBLineupWindow::IsPtOnInitPos()
{
  *(float *)&byte_17ACF80[904] = 12.0 + 12.0;
}

// 0x0051D5F0
char CCBLineupWindow::IsFaceOnInitPos()
{
  g_RandSeed = timeGetTime();
  g_nRandCallCount = 0;
  return 1;
}

// 0x0051D610
char CCBLineupWindow::SetFaceLineup(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, _DWORD *a9)
{
  if ( a1 > a7 || a5 > a3 || a2 > a8 || a6 > a4 )
    return 0;
  if ( a1 <= a5 )
    *a9 = a5;
  else
    *a9 = a1;
  if ( a3 >= a7 )
    a9[2] = a7;
  else
    a9[2] = a3;
  if ( a2 <= a6 )
    a9[1] = a6;
  else
    a9[1] = a2;
  if ( a4 >= a8 )
    a9[3] = a8;
  else
    a9[3] = a4;
  return 1;
}

// 0x0051D6D0
// attributes: thunk
int CCBLineupWindow::RefreshFacePos()
{
  return CCBProtectWindow::CCBProtectWindow();
}
