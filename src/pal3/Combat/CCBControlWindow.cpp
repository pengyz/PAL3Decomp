#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBControlWindow.h"
#include "pal3/gen/CCBItemWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIStatic.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_43F640(...);
int sub_43F670(...);
int sub_43F690(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aCNewFailed_0[];
extern char aCost[];
extern char aDProjectPal3Co_12[];
extern char aName[];
extern char aUiCombatContro_0[];
extern char aUiCombatContro_4[];
extern char aUiCombatContro_5[];
extern char aUiCombatContro_55[];
extern char aUiCombatContro_6[];
extern char aUiCombatContro_7[];
extern char aUiCombatContro_8[];
extern char aUiCombatContro_9[];
extern char aWa001[];
extern char aWa002[];
extern int dword_570134;
extern int dword_570138;
extern void *off_57051C;
extern void *off_570538;

// 0x0051A700
CCBControlWindow::CCBControlWindow()
{
  CCBControlWindow *v2; // edi
  int a4; // [esp+14h] [ebp-10h] BYREF
  int v5; // [esp+18h] [ebp-Ch]
  int v6; // [esp+1Ch] [ebp-8h]
  int v7; // [esp+20h] [ebp-4h]

  v2 = (CCBControlWindow *)((char *)this + 100);
  a4 = 40;
  v6 = 72;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 25, 192, (int)&a4, (int)aUiCombatContro_4);
  (**(void (***)(void *, int))v2->_p000)(v2->_p000, 1);
  a4 = 72;
  v6 = 104;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 26, 193, (int)&a4, (int)aUiCombatContro_5);
  (***((void (****)(_DWORD, int))this + 26))(*((_DWORD *)this + 26), 1);
  a4 = 104;
  v6 = 136;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 27, 194, (int)&a4, (int)aUiCombatContro_6);
  (***((void (****)(_DWORD, int))this + 27))(*((_DWORD *)this + 27), 1);
  a4 = 136;
  v6 = 168;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 28, 195, (int)&a4, (int)aUiCombatContro_7);
  (***((void (****)(_DWORD, int))this + 28))(*((_DWORD *)this + 28), 1);
  a4 = 168;
  v6 = 200;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 29, 196, (int)&a4, (int)aUiCombatContro_8);
  (***((void (****)(_DWORD, int))this + 29))(*((_DWORD *)this + 29), 1);
  a4 = 200;
  v6 = 232;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 30, 197, (int)&a4, (int)aUiCombatContro_9);
  (***((CCBControlWindow *(****)(_DWORD, int))this + 30))(*((_DWORD *)this + 30), 1);
}

// 0x0051A880
CCBControlWindow::~CCBControlWindow()
{
  int result; // eax
  int *p_d04C; // edi
  int v4; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int d048; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  p_d04C = (int *)&this->_d04C;
  v4 = 6;
  do
  {
    if ( *p_d04C )
    {
      result = (*(int (**)(int, int))(*(_DWORD *)*p_d04C + 20))(*p_d04C, 1);
      *p_d04C = 0;
    }
    ++p_d04C;
    --v4;
  }
  while ( v4 );
  v5 = *((_DWORD *)this + 25);
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *((_DWORD *)this + 25) = 0;
  }
  v6 = *((_DWORD *)this + 26);
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *((_DWORD *)this + 26) = 0;
  }
  v7 = *((_DWORD *)this + 27);
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *((_DWORD *)this + 27) = 0;
  }
  v8 = *((_DWORD *)this + 28);
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *((_DWORD *)this + 28) = 0;
  }
  v9 = *((_DWORD *)this + 29);
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *((_DWORD *)this + 29) = 0;
  }
  v10 = *((_DWORD *)this + 30);
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *((_DWORD *)this + 30) = 0;
  }
  d048 = this->_d048;
  if ( d048 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d048 + 20))(d048, 1);
    this->_d048 = 0;
  }
  result;
}

// 0x0051A930
int CCBControlWindow::Reset(int a2, unsigned int a3, int a4)
{
  char *v5; // eax
  char *Instance; // eax
  int Child; // eax

  if ( a2 == 1001 )
  {
    if ( a3 >= 0xC0 && a3 <= 0xC5 )
    {
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(aWa001, 1);
      this->HandleInput(a3 - 192);
      Child = ((UIWnd *)*((UIWnd **)this + a3 - 173))->CreateChild();
      if ( Child != -1 )
        ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(a3 - 48, Child);
    }
  }
  else if ( a2 == 1006 )
  {
    if ( a4 != -1 )
      ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(a3, a4);
  }
  else if ( a2 == 1007 && a4 != -1 )
  {
    v5 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v5)->AudioSetPosition(aWa002, 1);
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(a3, a4);
  }
  return a2->SendMessage(a3, a4);
}

// 0x0051AA20
char CCBControlWindow::Create(_DWORD *a2, int a3, int a4, int a5)
{
  UIStatic *v6; // eax
  int v7; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v11; // [esp+810h] [ebp-4h]

  v6 = (UIStatic *)operator new(0xF8u);
  v11 = 0;
  if ( v6 )
    v6->UIStatic();
  else
    v7 = 0;
  v11 = -1;
  *a2 = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 2875),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (**)(int, int, int, CCBControlWindow *, int, _DWORD))(*(_DWORD *)v7 + 28))(v7, a3, a4, this, a5, 0);
  return 1;
}

// 0x0051AB60
int CCBControlWindow::HandleInput(int a2)
{
  int v3; // ebp
  int *p_d04C; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int result; // eax
  int v11; // eax

  v3 = 6;
  p_d04C = (int *)&this->_d04C;
  do
  {
    (**(void (***)(int, _DWORD))*p_d04C)(*p_d04C, 0);
    ++p_d04C;
    --v3;
  }
  while ( v3 );
  v5 = *((_DWORD *)this + 25);
  *(_DWORD *)(v5 + 80) = 0;
  *(_BYTE *)(v5 + 68) = 0;
  v6 = *((_DWORD *)this + 26);
  *(_DWORD *)(v6 + 80) = 0;
  *(_BYTE *)(v6 + 68) = 0;
  v7 = *((_DWORD *)this + 27);
  *(_DWORD *)(v7 + 80) = 0;
  *(_BYTE *)(v7 + 68) = 0;
  v8 = *((_DWORD *)this + 28);
  *(_DWORD *)(v8 + 80) = 0;
  *(_BYTE *)(v8 + 68) = 0;
  v9 = *((_DWORD *)this + 29);
  *(_DWORD *)(v9 + 80) = 0;
  *(_BYTE *)(v9 + 68) = 0;
  result = *((_DWORD *)this + 30);
  *(_DWORD *)(result + 80) = 0;
  *(_BYTE *)(result + 68) = 0;
  switch ( a2 )
  {
    case 0:
      v11 = *((_DWORD *)this + 25);
      goto LABEL_10;
    case 1:
      v11 = *((_DWORD *)this + 26);
      goto LABEL_10;
    case 2:
      v11 = *((_DWORD *)this + 27);
      goto LABEL_10;
    case 3:
      v11 = *((_DWORD *)this + 28);
      goto LABEL_10;
    case 4:
      v11 = *((_DWORD *)this + 29);
      goto LABEL_10;
    case 5:
      v11 = *((_DWORD *)this + 30);
LABEL_10:
      *(_DWORD *)(v11 + 80) = 1;
      *(_BYTE *)(v11 + 68) = 1;
      ((UIWnd *)this->_d048)->SetEnable(g_SceneMgr.m_szUIString, 0);
      result = (***((int (****)(_DWORD, int))&this->_d04C + a2))(*(&this->_d04C + a2), 1);
      *((_DWORD *)this + 31) = a2;
      break;
    default:
      return result;
  }
  return result;
}

// 0x0051AC30
int CCBControlWindow::KeyPressed()
{
  return *((_DWORD *)this + 31);
}

// 0x0051AC40
_DWORD * CCBControlWindow::DefaultKey()
{
  ((UIListBox *)this)->UIListBox();
  this->_p000 = &off_57051C;
  this->CheckKeyInput();
  return &this->_p000;
}

// 0x0051AC90
UIWnd * CCBControlWindow::HandleEnable(CCBControlWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051AD00
int CCBControlWindow::CheckKeyInput()
{
  this->_d050 = 0;
  this->_d048 = 0;
  this->_d04C = 0;
  return 0;
}

// 0x0051AD10
char CCBControlWindow::OnMessage(_DWORD *pRect, int parent)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  UIFrameWnd *v6; // eax
  int v7; // eax
  UIFrameWnd *v8; // eax
  int v9; // eax
  UIWnd *d048; // ecx
  const int *v11; // ebp
  int *p_d050; // esi
  UIListBox *v13; // eax
  char *updated; // eax
  int id; // [esp+10h] [ebp-1014h] BYREF
  void *v17; // [esp+14h] [ebp-1010h]
  char pExceptionObject[1024]; // [esp+18h] [ebp-100Ch] BYREF
  char ArgList[1024]; // [esp+418h] [ebp-C0Ch] BYREF
  char v20[1024]; // [esp+818h] [ebp-80Ch] BYREF
  char v21[1024]; // [esp+C18h] [ebp-40Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v22; // [esp+1018h] [ebp-Ch]
  void *v23; // [esp+101Ch] [ebp-8h]
  int v24; // [esp+1020h] [ebp-4h]

  v24 = -1;
  ExceptionList = (struct _EXCEPTION_REGISTRATION_RECORD *)NtCurrentTeb()->NtTib.ExceptionList;
  v23 = (void *)&loc_56733A;
  v22 = ExceptionList;
  v4 = (void *)alloca(4104);
  ((UIWnd *)this)->Create(1879048195, pRect, parent);
  v6 = (UIFrameWnd *)operator new(0x98u);
  v17 = v6;
  v24 = 0;
  if ( v6 )
    v6->UIFrameWnd();
  else
    v7 = 0;
  v24 = -1;
  this->_d048 = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 3023),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
  (*(void (**)(int, int, _DWORD *, CCBControlWindow *))(*(_DWORD *)this->_d048 + 16))(
    this->_d048,
    161,
    pRect,
    this);
  ((UIWnd *)this->_d048)->CreateFromTemplate(aUiCombatContro_55, 0);
  (**(void (***)(int, int))this->_d048)(this->_d048, 1);
  v8 = (UIFrameWnd *)operator new(0x98u);
  v17 = v8;
  v24 = 1;
  if ( v8 )
    v8->UIFrameWnd();
  else
    v9 = 0;
  v24 = -1;
  this->_d04C = v9;
  if ( !v9 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 3037),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  d048 = (UIWnd *)this->_d048;
  id = -1879048192;
  d048->SetShow(0);
  ((UIWnd *)this->_d048)->GetChild((int)&id);
  ((UIFrameWnd *)this->_d048)->SetPosition(39, 219);
  v11 = (const int *)&dword_570134;
  p_d050 = (int *)&this->_d050;
  do
  {
    v13 = (UIListBox *)operator new(0x4B8u);
    v17 = v13;
    v24 = 2;
    if ( v13 )
      updated = (char *)v13->UpdateKeyCtrl();
    else
      updated = 0;
    v24 = -1;
    *p_d050 = (int)updated;
    if ( !updated )
    {
      qmemcpy(v20, ((Logger *)v21)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 3067), sizeof(v20));
      _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *pRect = 39;
    pRect[2] = 241;
    pRect[1] = 110;
    pRect[3] = 226;
    (*(void (**)(int, const int, _DWORD *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)*p_d050
                                                                                                 + 28))(
      *p_d050,
      *v11,
      pRect,
      this,
      0,
      0,
      0);
    (**(void (***)(int, int))*p_d050)(*p_d050, 1);
    sub_43F670((_DWORD *)*p_d050, 2, -4);
    ((UIListBox *)*p_d050)->SetFirstShow(aName, 150);
    ((UIListBox *)*p_d050)->SetFirstShow(aCost, 43);
    sub_43F640((_DWORD *)*p_d050, 19);
    ((UIListBox *)*p_d050)->GetSel((int)aUiCombatContro_0, 0);
    sub_43F690((_DWORD *)*p_d050, 1);
    ++v11;
    ++p_d050;
  }
  while ( (int)v11 < (int)dword_570138 );
  return 1;
}

// 0x0051AFE0
int CCBControlWindow::Update()
{
  int result; // eax
  int d050; // ecx
  int d048; // ecx
  int d04C; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  d050 = this->_d050;
  if ( d050 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d050 + 20))(d050, 1);
    this->_d050 = 0;
  }
  d048 = this->_d048;
  if ( d048 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d048 + 20))(d048, 1);
    this->_d048 = 0;
  }
  d04C = this->_d04C;
  if ( d04C )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d04C + 20))(d04C, 1);
    this->_d04C = 0;
  }
  return result;
}

// 0x0051B0B0
BOOL CCBControlWindow::MoveButtons(int a2, int a3)
{
  if ( *(_DWORD *)&this->_pad_024[20] == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(160, -1);
  }
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x0051B110
_DWORD * CCBControlWindow::CreateButton()
{
  ((UIListBox *)this)->UIListBox();
  this->_p000 = &off_570538;
  ((CCBItemWindow *)this)->Reset();
  return &this->_p000;
}
