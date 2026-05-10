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
  int *p_m_bfocus; // edi
  int a4; // [esp+14h] [ebp-10h] BYREF
  int v5; // [esp+18h] [ebp-Ch]
  int v6; // [esp+1Ch] [ebp-8h]
  int v7; // [esp+20h] [ebp-4h]

  p_m_bfocus = (int *)&this->m_bfocus;
  a4 = 40;
  v6 = 72;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_bfocus, 192, (int)&a4, (int)aUiCombatContro_4);
  (**(void (***)(int, int))*p_m_bfocus)(*p_m_bfocus, 1);
  a4 = 72;
  v6 = 104;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pbktex, 193, (int)&a4, (int)aUiCombatContro_5);
  (**(void (***)(gbTexture *, int))this->m_pbktex)(this->m_pbktex, 1);
  a4 = 104;
  v6 = 136;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pBack, 194, (int)&a4, (int)aUiCombatContro_6);
  (*(void (**)(UIStatic *, int))this->m_pBack->m_fontcolor.ColorQuadFmt)(this->m_pBack, 1);
  a4 = 136;
  v6 = 168;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pButtonAttack, 195, (int)&a4, (int)aUiCombatContro_7);
  (*(void (**)(UIButton *, int))this->m_pButtonAttack->m_fontcolor.ColorQuadFmt)(this->m_pButtonAttack, 1);
  a4 = 168;
  v6 = 200;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pButtonSkill, 196, (int)&a4, (int)aUiCombatContro_8);
  (*(void (**)(UIButton *, int))this->m_pButtonSkill->m_fontcolor.ColorQuadFmt)(this->m_pButtonSkill, 1);
  a4 = 200;
  v6 = 232;
  v5 = 27;
  v7 = 59;
  this->Create(&this->m_pButtonMagic, 197, (int)&a4, (int)aUiCombatContro_9);
  return (*(CCBControlWindow *(**)(UIButton *, int))this->m_pButtonMagic->m_fontcolor.ColorQuadFmt)(
           this->m_pButtonMagic,
           1);
}

// 0x0051A880
CCBControlWindow::~CCBControlWindow()
{
  int result; // eax
  int *p_m_nSize; // edi
  int v4; // ebx
  int m_bfocus; // ecx
  gbTexture *m_pbktex; // ecx
  UIStatic *m_pBack; // ecx
  UIButton *m_pButtonAttack; // ecx
  UIButton *m_pButtonSkill; // ecx
  UIButton *m_pButtonMagic; // ecx
  void *m_pData; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  p_m_nSize = (int *)&this->m_childs.m_nSize;
  v4 = 6;
  do
  {
    if ( *p_m_nSize )
    {
      result = (*(int (**)(int, int))(*(_DWORD *)*p_m_nSize + 20))(*p_m_nSize, 1);
      *p_m_nSize = 0;
    }
    ++p_m_nSize;
    --v4;
  }
  while ( v4 );
  m_bfocus = this->m_bfocus;
  if ( m_bfocus )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bfocus + 20))(m_bfocus, 1);
    this->m_bfocus = 0;
  }
  m_pbktex = (gbTexture *)this->m_pbktex;
  if ( m_pbktex )
  {
    result = (*(int (**)(gbTexture *, int))(*(_DWORD *)m_pbktex->_pad_0000 + 20))(m_pbktex, 1);
    this->m_pbktex = 0;
  }
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    result = (*(int (**)(UIStatic *, int))(m_pBack->m_fontcolor.ColorQuadFmt + 20))(m_pBack, 1);
    this->m_pBack = 0;
  }
  m_pButtonAttack = (UIButton *)this->m_pButtonAttack;
  if ( m_pButtonAttack )
  {
    result = (*(int (**)(UIButton *, int))(m_pButtonAttack->m_fontcolor.ColorQuadFmt + 20))(
               m_pButtonAttack,
               1);
    this->m_pButtonAttack = 0;
  }
  m_pButtonSkill = (UIButton *)this->m_pButtonSkill;
  if ( m_pButtonSkill )
  {
    result = (*(int (**)(UIButton *, int))(m_pButtonSkill->m_fontcolor.ColorQuadFmt + 20))(m_pButtonSkill, 1);
    this->m_pButtonSkill = 0;
  }
  m_pButtonMagic = (UIButton *)this->m_pButtonMagic;
  if ( m_pButtonMagic )
  {
    result = (*(int (**)(UIButton *, int))(m_pButtonMagic->m_fontcolor.ColorQuadFmt + 20))(m_pButtonMagic, 1);
    this->m_pButtonMagic = 0;
  }
  m_pData = (void *)this->m_childs.m_pData;
  if ( m_pData )
  {
    result = (*(int (**)(void *, int))(*(_DWORD *)m_pData + 20))(m_pData, 1);
    this->m_childs.m_pData = 0;
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
        ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3 - 48, Child);
    }
  }
  else if ( a2 == 1006 )
  {
    if ( a4 != -1 )
      ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
  }
  else if ( a2 == 1007 && a4 != -1 )
  {
    v5 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v5)->AudioSetPosition(aWa002, 1);
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
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
  int *p_m_nSize; // edi
  int m_bfocus; // eax
  gbTexture *m_pbktex; // eax
  UIStatic *m_pBack; // eax
  UIButton *m_pButtonAttack; // eax
  UIButton *m_pButtonSkill; // eax
  int result; // eax
  _DWORD *pad_0000; // eax

  v3 = 6;
  p_m_nSize = (int *)&this->m_childs.m_nSize;
  do
  {
    (**(void (***)(int, _DWORD))*p_m_nSize)(*p_m_nSize, 0);
    ++p_m_nSize;
    --v3;
  }
  while ( v3 );
  m_bfocus = this->m_bfocus;
  *(_DWORD *)(m_bfocus + 80) = 0;
  *(_BYTE *)(m_bfocus + 68) = 0;
  m_pbktex = (gbTexture *)this->m_pbktex;
  m_pbktex->InFmt.a_mask = 0;
  LOBYTE(m_pbktex->InFmt.r_mask) = 0;
  m_pBack = (UIStatic *)this->m_pBack;
  m_pBack->m_childs.m_nMaxSize = 0;
  LOBYTE(m_pBack->m_pfather) = 0;
  m_pButtonAttack = (UIButton *)this->m_pButtonAttack;
  m_pButtonAttack->m_childs.m_nMaxSize = 0;
  LOBYTE(m_pButtonAttack->m_pfather) = 0;
  m_pButtonSkill = (UIButton *)this->m_pButtonSkill;
  m_pButtonSkill->m_childs.m_nMaxSize = 0;
  LOBYTE(m_pButtonSkill->m_pfather) = 0;
  result = (int)this->m_pButtonMagic;
  *(_DWORD *)(result + 80) = 0;
  *(_BYTE *)(result + 68) = 0;
  switch ( a2 )
  {
    case 0:
      pad_0000 = (_DWORD *)this->m_bfocus;
      goto LABEL_10;
    case 1:
      pad_0000 = (_DWORD *)this->m_pbktex->_pad_0000;
      goto LABEL_10;
    case 2:
      pad_0000 = (_DWORD *)&this->m_pBack->m_fontcolor.ColorQuadFmt;
      goto LABEL_10;
    case 3:
      pad_0000 = (_DWORD *)&this->m_pButtonAttack->m_fontcolor.ColorQuadFmt;
      goto LABEL_10;
    case 4:
      pad_0000 = (_DWORD *)&this->m_pButtonSkill->m_fontcolor.ColorQuadFmt;
      goto LABEL_10;
    case 5:
      pad_0000 = (_DWORD *)&this->m_pButtonMagic->m_fontcolor.ColorQuadFmt;
LABEL_10:
      pad_0000[20] = 1;
      *((_BYTE *)pad_0000 + 68) = 1;
      ((UIWnd *)this->m_childs.m_pData)->SetEnable(g_SceneMgr.m_szUIString, 0);
      result = (***((int (****)(_DWORD, int))&this->m_childs.m_nSize + a2))(
                 *(&this->m_childs.m_nSize + a2),
                 1);
      this->m_pButtonItem = (UIButton *)a2;
      break;
    default:
      return result;
  }
  return result;
}

// 0x0051AC30
int CCBControlWindow::KeyPressed()
{
  return (int)this->m_pButtonItem;
}

// 0x0051AC40
_DWORD * CCBControlWindow::DefaultKey()
{
  ((UIListBox *)this)->UIListBox();
  this->m_fontcolor.ColorQuadFmt = (int)&off_57051C;
  this->CheckKeyInput();
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0051AC90
UIWnd * CCBControlWindow::HandleEnable(CCBControlWindow *Block, char a2)
{
  Block->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051AD00
int CCBControlWindow::CheckKeyInput()
{
  this->m_childs.m_nMaxSize = 0;
  this->m_childs.m_pData = 0;
  this->m_childs.m_nSize = 0;
  return 0;
}

// 0x0051AD10
char CCBControlWindow::OnMessage(_DWORD *pRect, int parent)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  UIFrameWnd *v6; // eax
  void *v7; // eax
  UIFrameWnd *v8; // eax
  int v9; // eax
  UIWnd *m_pData; // ecx
  const int *v11; // ebp
  int *p_m_nMaxSize; // esi
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
  this->Create(1879048195, pRect, parent);
  v6 = (UIFrameWnd *)operator new(0x98u);
  v17 = v6;
  v24 = 0;
  if ( v6 )
    v6->UIFrameWnd();
  else
    v7 = 0;
  v24 = -1;
  this->m_childs.m_pData = v7;
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
  (*(void (**)(void *, int, _DWORD *, CCBControlWindow *))(*(_DWORD *)this->m_childs.m_pData + 16))(
    this->m_childs.m_pData,
    161,
    pRect,
    this);
  ((UIWnd *)this->m_childs.m_pData)->CreateFromTemplate(aUiCombatContro_55, 0);
  (**(void (***)(void *, int))this->m_childs.m_pData)(this->m_childs.m_pData, 1);
  v8 = (UIFrameWnd *)operator new(0x98u);
  v17 = v8;
  v24 = 1;
  if ( v8 )
    v8->UIFrameWnd();
  else
    v9 = 0;
  v24 = -1;
  this->m_childs.m_nSize = v9;
  if ( !v9 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 3037),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  m_pData = (UIWnd *)this->m_childs.m_pData;
  id = -1879048192;
  m_pData->SetShow(0);
  ((UIWnd *)this->m_childs.m_pData)->GetChild((int)&id);
  ((UIFrameWnd *)this->m_childs.m_pData)->SetPosition(39, 219);
  v11 = (const int *)&dword_570134;
  p_m_nMaxSize = (int *)&this->m_childs.m_nMaxSize;
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
    *p_m_nMaxSize = (int)updated;
    if ( !updated )
    {
      qmemcpy(v20, ((Logger *)v21)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 3067), sizeof(v20));
      _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *pRect = 39;
    pRect[2] = 241;
    pRect[1] = 110;
    pRect[3] = 226;
    (*(void (**)(int, const int, _DWORD *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)*p_m_nMaxSize
                                                                                                 + 28))(
      *p_m_nMaxSize,
      *v11,
      pRect,
      this,
      0,
      0,
      0);
    (**(void (***)(int, int))*p_m_nMaxSize)(*p_m_nMaxSize, 1);
    sub_43F670((_DWORD *)*p_m_nMaxSize, 2, -4);
    ((UIListBox *)*p_m_nMaxSize)->SetFirstShow(aName, 150);
    ((UIListBox *)*p_m_nMaxSize)->SetFirstShow(aCost, 43);
    sub_43F640((_DWORD *)*p_m_nMaxSize, 19);
    ((UIListBox *)*p_m_nMaxSize)->GetSel((int)aUiCombatContro_0, 0);
    sub_43F690((_DWORD *)*p_m_nMaxSize, 1);
    ++v11;
    ++p_m_nMaxSize;
  }
  while ( (int)v11 < (int)dword_570138 );
  return 1;
}

// 0x0051AFE0
int CCBControlWindow::Update()
{
  int result; // eax
  int m_nMaxSize; // ecx
  void *m_pData; // ecx
  int m_nSize; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  m_nMaxSize = this->m_childs.m_nMaxSize;
  if ( m_nMaxSize )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nMaxSize + 20))(m_nMaxSize, 1);
    this->m_childs.m_nMaxSize = 0;
  }
  m_pData = (void *)this->m_childs.m_pData;
  if ( m_pData )
  {
    result = (*(int (**)(void *, int))(*(_DWORD *)m_pData + 20))(m_pData, 1);
    this->m_childs.m_pData = 0;
  }
  m_nSize = this->m_childs.m_nSize;
  if ( m_nSize )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nSize + 20))(m_nSize, 1);
    this->m_childs.m_nSize = 0;
  }
  return result;
}

// 0x0051B0B0
BOOL CCBControlWindow::MoveButtons(int a2, int a3)
{
  if ( this->m_rect.top == 1
    && (g_Input.m_DIKToKEY[1] == 1 && (g_Input.m_shiftedKeyStates[268] & 0xF) == 1 || g_Input.m_DIKToKEY[5] == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(160, -1);
  }
  return this->HitTest(a2, a3);
}

// 0x0051B110
_DWORD * CCBControlWindow::CreateButton()
{
  ((UIListBox *)this)->UIListBox();
  this->m_fontcolor.ColorQuadFmt = (int)&off_570538;
  ((CCBItemWindow *)this)->Reset();
  return &this->m_fontcolor.ColorQuadFmt;
}
