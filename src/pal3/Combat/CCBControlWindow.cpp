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
  UIButton **p_m_pButtonAI; // edi
  int a4; // [esp+14h] [ebp-10h] BYREF
  int v5; // [esp+18h] [ebp-Ch]
  int v6; // [esp+1Ch] [ebp-8h]
  int v7; // [esp+20h] [ebp-4h]

  p_m_pButtonAI = &this->m_pButtonAI;
  a4 = 40;
  v6 = 72;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pButtonAI, 192, (int)&a4, (int)aUiCombatContro_4);
  (**(void (***)(UIButton *, int))(*p_m_pButtonAI)->_base)(*p_m_pButtonAI, 1);
  a4 = 72;
  v6 = 104;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pButtonFlee, 193, (int)&a4, (int)aUiCombatContro_5);
  (**(void (***)(UIButton *, int))this->m_pButtonFlee)(this->m_pButtonFlee, 1);
  a4 = 104;
  v6 = 136;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pButtonProtect, 194, (int)&a4, (int)aUiCombatContro_6);
  (**(void (***)(UIButton *, int))this->m_pButtonProtect)(this->m_pButtonProtect, 1);
  a4 = 136;
  v6 = 168;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_CurCtrl, 195, (int)&a4, (int)aUiCombatContro_7);
  (**(void (***)(int, int))this->m_CurCtrl)(this->m_CurCtrl, 1);
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
  UIButton **p_m_pButtonAttack; // edi
  int v4; // ebx
  UIButton *m_pButtonAI; // ecx
  UIButton *m_pButtonFlee; // ecx
  UIButton *m_pButtonProtect; // ecx
  int m_CurCtrl; // ecx
  int v9; // ecx
  int v10; // ecx
  UIStatic *m_pBack; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  p_m_pButtonAttack = &this->m_pButtonAttack;
  v4 = 6;
  do
  {
    if ( *p_m_pButtonAttack )
    {
      result = (*(int (**)(UIButton *, int))(*(_DWORD *)(*p_m_pButtonAttack)->_base + 20))(
                 *p_m_pButtonAttack,
                 1);
      *p_m_pButtonAttack = 0;
    }
    ++p_m_pButtonAttack;
    --v4;
  }
  while ( v4 );
  m_pButtonAI = (UIButton *)this->m_pButtonAI;
  if ( m_pButtonAI )
  {
    result = (*(int (**)(UIButton *, int))(*(_DWORD *)m_pButtonAI->_base + 20))(m_pButtonAI, 1);
    this->m_pButtonAI = 0;
  }
  m_pButtonFlee = (UIButton *)this->m_pButtonFlee;
  if ( m_pButtonFlee )
  {
    result = (*(int (**)(UIButton *, int))(*(_DWORD *)m_pButtonFlee->_base + 20))(m_pButtonFlee, 1);
    this->m_pButtonFlee = 0;
  }
  m_pButtonProtect = (UIButton *)this->m_pButtonProtect;
  if ( m_pButtonProtect )
  {
    result = (*(int (**)(UIButton *, int))(*(_DWORD *)m_pButtonProtect->_base + 20))(m_pButtonProtect, 1);
    this->m_pButtonProtect = 0;
  }
  m_CurCtrl = this->m_CurCtrl;
  if ( m_CurCtrl )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_CurCtrl + 20))(m_CurCtrl, 1);
    this->m_CurCtrl = 0;
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
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    result = (*(int (**)(UIStatic *, int))(*(_DWORD *)m_pBack->_base + 20))(m_pBack, 1);
    this->m_pBack = 0;
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
      Child = ((UIWnd *)*(UIWnd **)&this->_base[4 * a3 - 692])->CreateChild();
      if ( Child != -1 )
        ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_base[32] + 1160) + 8))->SetParam(a3 - 48, Child);
    }
  }
  else if ( a2 == 1006 )
  {
    if ( a4 != -1 )
      ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_base[32] + 1160) + 8))->SetParam(a3, a4);
  }
  else if ( a2 == 1007 && a4 != -1 )
  {
    v5 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v5)->AudioSetPosition(aWa002, 1);
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_base[32] + 1160) + 8))->SetParam(a3, a4);
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
  UIButton **p_m_pButtonAttack; // edi
  UIButton *m_pButtonAI; // eax
  UIButton *m_pButtonFlee; // eax
  UIButton *m_pButtonProtect; // eax
  int m_CurCtrl; // eax
  int v9; // eax
  int result; // eax
  UIButton *v11; // eax

  v3 = 6;
  p_m_pButtonAttack = &this->m_pButtonAttack;
  do
  {
    (**(void (***)(UIButton *, _DWORD))(*p_m_pButtonAttack)->_base)(*p_m_pButtonAttack, 0);
    ++p_m_pButtonAttack;
    --v3;
  }
  while ( v3 );
  m_pButtonAI = (UIButton *)this->m_pButtonAI;
  *(_DWORD *)m_pButtonAI->m_drawrc = 0;
  m_pButtonAI->m_hasDBclk = 0;
  m_pButtonFlee = (UIButton *)this->m_pButtonFlee;
  *(_DWORD *)m_pButtonFlee->m_drawrc = 0;
  m_pButtonFlee->m_hasDBclk = 0;
  m_pButtonProtect = (UIButton *)this->m_pButtonProtect;
  *(_DWORD *)m_pButtonProtect->m_drawrc = 0;
  m_pButtonProtect->m_hasDBclk = 0;
  m_CurCtrl = this->m_CurCtrl;
  *(_DWORD *)(m_CurCtrl + 80) = 0;
  *(_BYTE *)(m_CurCtrl + 68) = 0;
  v9 = *((_DWORD *)this + 29);
  *(_DWORD *)(v9 + 80) = 0;
  *(_BYTE *)(v9 + 68) = 0;
  result = *((_DWORD *)this + 30);
  *(_DWORD *)(result + 80) = 0;
  *(_BYTE *)(result + 68) = 0;
  switch ( a2 )
  {
    case 0:
      v11 = (UIButton *)this->m_pButtonAI;
      goto LABEL_10;
    case 1:
      v11 = (UIButton *)this->m_pButtonFlee;
      goto LABEL_10;
    case 2:
      v11 = (UIButton *)this->m_pButtonProtect;
      goto LABEL_10;
    case 3:
      v11 = (UIButton *)this->m_CurCtrl;
      goto LABEL_10;
    case 4:
      v11 = (UIButton *)*((_DWORD *)this + 29);
      goto LABEL_10;
    case 5:
      v11 = (UIButton *)*((_DWORD *)this + 30);
LABEL_10:
      *(_DWORD *)v11->m_drawrc = 1;
      v11->m_hasDBclk = 1;
      ((UIWnd *)this->m_pBack)->SetEnable(g_SceneMgr.m_szUIString, 0);
      result = (***((int (****)(_DWORD, int))&this->m_pButtonAttack + a2))(
                 *((_DWORD *)&this->m_pButtonAttack + a2),
                 1);
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
  *(_DWORD *)this->_base = &off_57051C;
  this->CheckKeyInput();
  return this->_base;
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
  this->m_pButtonSkill = 0;
  this->m_pBack = 0;
  this->m_pButtonAttack = 0;
  return 0;
}

// 0x0051AD10
char CCBControlWindow::OnMessage(_DWORD *pRect, int parent)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  UIFrameWnd *v6; // eax
  UIStatic *v7; // eax
  UIFrameWnd *v8; // eax
  UIButton *v9; // eax
  UIStatic *m_pBack; // ecx
  const int *v11; // ebp
  UIButton **p_m_pButtonSkill; // esi
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
  this->m_pBack = v7;
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
  (*(void (**)(UIStatic *, int, _DWORD *, CCBControlWindow *))(*(_DWORD *)this->m_pBack + 16))(
    this->m_pBack,
    161,
    pRect,
    this);
  ((UIWnd *)this->m_pBack)->CreateFromTemplate(aUiCombatContro_55, 0);
  (**(void (***)(UIStatic *, int))this->m_pBack)(this->m_pBack, 1);
  v8 = (UIFrameWnd *)operator new(0x98u);
  v17 = v8;
  v24 = 1;
  if ( v8 )
    v8->UIFrameWnd();
  else
    v9 = 0;
  v24 = -1;
  this->m_pButtonAttack = v9;
  if ( !v9 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 3037),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  m_pBack = (UIStatic *)this->m_pBack;
  id = -1879048192;
  ((UIWnd *)m_pBack)->SetShow(0);
  ((UIWnd *)this->m_pBack)->GetChild((int)&id);
  ((UIFrameWnd *)this->m_pBack)->SetPosition(39, 219);
  v11 = (const int *)&dword_570134;
  p_m_pButtonSkill = &this->m_pButtonSkill;
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
    *p_m_pButtonSkill = (UIButton *)updated;
    if ( !updated )
    {
      qmemcpy(v20, ((Logger *)v21)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 3067), sizeof(v20));
      _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *pRect = 39;
    pRect[2] = 241;
    pRect[1] = 110;
    pRect[3] = 226;
    (*(void (**)(UIButton *, const int, _DWORD *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)(*p_m_pButtonSkill)->_base + 28))(
      *p_m_pButtonSkill,
      *v11,
      pRect,
      this,
      0,
      0,
      0);
    (**(void (***)(UIButton *, int))(*p_m_pButtonSkill)->_base)(*p_m_pButtonSkill, 1);
    sub_43F670(*p_m_pButtonSkill, 2, -4);
    ((UIListBox *)*p_m_pButtonSkill)->SetFirstShow(aName, 150);
    ((UIListBox *)*p_m_pButtonSkill)->SetFirstShow(aCost, 43);
    sub_43F640(*p_m_pButtonSkill, 19);
    ((UIListBox *)*p_m_pButtonSkill)->GetSel((int)aUiCombatContro_0, 0);
    sub_43F690(*p_m_pButtonSkill, 1);
    ++v11;
    ++p_m_pButtonSkill;
  }
  while ( (int)v11 < (int)dword_570138 );
  return 1;
}

// 0x0051AFE0
int CCBControlWindow::Update()
{
  int result; // eax
  UIButton *m_pButtonSkill; // ecx
  UIStatic *m_pBack; // ecx
  UIButton *m_pButtonAttack; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  m_pButtonSkill = (UIButton *)this->m_pButtonSkill;
  if ( m_pButtonSkill )
  {
    result = (*(int (**)(UIButton *, int))(*(_DWORD *)m_pButtonSkill->_base + 20))(m_pButtonSkill, 1);
    this->m_pButtonSkill = 0;
  }
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    result = (*(int (**)(UIStatic *, int))(*(_DWORD *)m_pBack->_base + 20))(m_pBack, 1);
    this->m_pBack = 0;
  }
  m_pButtonAttack = (UIButton *)this->m_pButtonAttack;
  if ( m_pButtonAttack )
  {
    result = (*(int (**)(UIButton *, int))(*(_DWORD *)m_pButtonAttack->_base + 20))(m_pButtonAttack, 1);
    this->m_pButtonAttack = 0;
  }
  return result;
}

// 0x0051B0B0
BOOL CCBControlWindow::MoveButtons(int a2, int a3)
{
  if ( *(_DWORD *)&this->_base[56] == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_base[32] + 1160) + 8))->SetParam(160, -1);
  }
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x0051B110
_DWORD * CCBControlWindow::CreateButton()
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)this->_base = &off_570538;
  ((CCBItemWindow *)this)->Reset();
  return this->_base;
}
