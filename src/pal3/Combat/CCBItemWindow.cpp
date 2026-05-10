#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBItemWindow.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_51B6E0(...);

// Unnamed globals (extern)
extern char aUiCombatContro_11[];
extern char aUiCombatContro_12[];
extern char aUiCombatContro_13[];
extern char aUiCombatContro_14[];
extern char aUiCombatContro_15[];
extern char aUiCombatContro_16[];
extern char aUiCombatContro_17[];
extern char aUiCombatContro_18[];
extern int dword_570138;
extern void *off_570218;
extern void *off_570554;

// 0x0051B160
CCBItemWindow::CCBItemWindow(CCBItemWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  (UIWnd *)Block;
}

// 0x0051B1D0
int CCBItemWindow::Reset()
{
  this->m_pBack = 0;
  this->m_pDescription = 0;
  this->m_pItemList[0] = 0;
  this->m_pItemList[1] = 0;
  this->m_pItemList[2] = 0;
  this->m_pButtonRecover = 0;
  this->m_pButtonAttack = 0;
  this->m_pButtonTreasure = 0;
  this->m_nActivePage = 0;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 30) = 0;
  *((_DWORD *)this + 31) = -1;
  return 0;
}

// 0x0051B210
char CCBItemWindow::Create(_DWORD *pRect, int parent)
{
  UIStatic **p_m_pBack; // ebx
  UIPushButton **p_m_pButtonAttack; // ebx
  UIPushButton **p_m_pButtonTreasure; // ebx
  int *p_m_nActivePage; // ebx
  CCBItemWindow *v8; // ebx
  _DWORD *v9; // ebx
  _DWORD *v10; // ebx
  UIStatic **p_m_pDescription; // ebx
  int i; // ebp
  _DWORD *v13; // ebx

  ((UIWnd *)this)->Create(1879048196, pRect, parent);
  p_m_pBack = &this->m_pBack;
  ((CCBLineupWindow *)&this->m_pBack)->Destroy();
  *pRect = 0;
  pRect[2] = 158;
  pRect[1] = 0;
  pRect[3] = 158;
  (*(void (**)(UIStatic *, int, _DWORD *, CCBItemWindow *))(*(_DWORD *)(*p_m_pBack)->_pad_0000 + 16))(
    *p_m_pBack,
    232,
    pRect,
    this);
  ((UIWnd *)this->m_pBack)->CreateFromTemplate(aUiCombatContro_18, 0);
  (**(void (***)(UIStatic *, int))(*p_m_pBack)->_pad_0000)(*p_m_pBack, 1);
  p_m_pButtonAttack = &this->m_pButtonAttack;
  ((CCBLineupWindow *)&this->m_pButtonAttack)->OnMessage();
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(UIPushButton *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)(*p_m_pButtonAttack)->_pad_0000
                                                                                         + 28))(
    *p_m_pButtonAttack,
    214,
    pRect,
    this,
    aUiCombatContro_11,
    0);
  (**(void (***)(UIPushButton *, int))(*p_m_pButtonAttack)->_pad_0000)(*p_m_pButtonAttack, 1);
  p_m_pButtonTreasure = &this->m_pButtonTreasure;
  ((CCBLineupWindow *)&this->m_pButtonTreasure)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(UIPushButton *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)(*p_m_pButtonTreasure)->_pad_0000
                                                                                         + 28))(
    *p_m_pButtonTreasure,
    215,
    pRect,
    this,
    aUiCombatContro_12,
    0);
  (**(void (***)(UIPushButton *, int))(*p_m_pButtonTreasure)->_pad_0000)(*p_m_pButtonTreasure, 1);
  p_m_nActivePage = (int *)&this->m_nActivePage;
  ((CCBLineupWindow *)&this->m_nActivePage)->OnMessage();
  pRect[1] = 73;
  *pRect = 7;
  pRect[2] = 80;
  pRect[3] = 98;
  (*(void (**)(int, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*p_m_nActivePage + 28))(
    *p_m_nActivePage,
    216,
    pRect,
    this,
    aUiCombatContro_13,
    0);
  (**(void (***)(int, int))*p_m_nActivePage)(*p_m_nActivePage, 1);
  v8 = (CCBItemWindow *)this + 1;
  ((CCBLineupWindow *)(_DWORD *)this + 27)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 73;
  pRect[3] = 98;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(**(_DWORD **)v8->_pad_0000 + 28))(
    *(_DWORD *)v8->_pad_0000,
    217,
    pRect,
    this,
    aUiCombatContro_14,
    0);
  (***(void (****)(_DWORD, int))v8->_pad_0000)(*(_DWORD *)v8->_pad_0000, 1);
  v9 = (_DWORD *)((char *)this + 112);
  ((CCBLineupWindow *)(_DWORD *)this + 28)->OnMessage();
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*v9 + 28))(
    *v9,
    218,
    pRect,
    this,
    aUiCombatContro_15,
    0);
  (**(void (***)(_DWORD, int))*v9)(*v9, 1);
  v10 = (_DWORD *)((char *)this + 116);
  ((CCBLineupWindow *)(_DWORD *)this + 29)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*v10 + 28))(
    *v10,
    219,
    pRect,
    this,
    aUiCombatContro_16,
    0);
  (**(void (***)(_DWORD, int))*v10)(*v10, 1);
  p_m_pDescription = &this->m_pDescription;
  for ( i = 0; i < 5; ++i )
  {
    p_m_pDescription->Destroy();
    *pRect = 57;
    pRect[2] = 95;
    pRect[1] = 31;
    pRect[3] = 47;
    (*(void (**)(UIStatic *, int, _DWORD *, CCBItemWindow *))(*(_DWORD *)(*p_m_pDescription)->_pad_0000 + 16))(
      *p_m_pDescription,
      dword_570138[i],
      pRect,
      this);
    ((UIWnd *)*p_m_pDescription)->CreateFromTemplate(off_570218[i], 0);
    (**(void (***)(UIStatic *, int))(*p_m_pDescription)->_pad_0000)(*p_m_pDescription, 1);
    ++p_m_pDescription;
  }
  v13 = (_DWORD *)((char *)this + 120);
  ((CCBLineupWindow *)(_DWORD *)this + 30)->Update();
  *pRect = 35;
  pRect[2] = 127;
  pRect[1] = 127;
  pRect[3] = 153;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, int, _DWORD))(*(_DWORD *)*v13 + 28))(
    *v13,
    220,
    pRect,
    this,
    aUiCombatContro_17,
    1,
    0);
  (**(void (***)(_DWORD, int))*v13)(*v13, 1);
  return 1;
}

// 0x0051B4B0
int CCBItemWindow::Destroy()
{
  int result; // eax
  UIStatic *m_pBack; // ecx
  UIPushButton *m_pButtonAttack; // ecx
  UIPushButton *m_pButtonTreasure; // ecx
  int m_nActivePage; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  UIStatic **p_m_pDescription; // esi
  int v12; // edi

  result = ((UIListBox *)this)->SetScrollPos();
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    result = (*(int (**)(UIStatic *, int))(*(_DWORD *)m_pBack->_pad_0000 + 20))(m_pBack, 1);
    this->m_pBack = 0;
  }
  m_pButtonAttack = (UIPushButton *)this->m_pButtonAttack;
  if ( m_pButtonAttack )
  {
    result = (*(int (**)(UIPushButton *, int))(*(_DWORD *)m_pButtonAttack->_pad_0000 + 20))(
               m_pButtonAttack,
               1);
    this->m_pButtonAttack = 0;
  }
  m_pButtonTreasure = (UIPushButton *)this->m_pButtonTreasure;
  if ( m_pButtonTreasure )
  {
    result = (*(int (**)(UIPushButton *, int))(*(_DWORD *)m_pButtonTreasure->_pad_0000 + 20))(
               m_pButtonTreasure,
               1);
    this->m_pButtonTreasure = 0;
  }
  m_nActivePage = this->m_nActivePage;
  if ( m_nActivePage )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nActivePage + 20))(m_nActivePage, 1);
    this->m_nActivePage = 0;
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
  p_m_pDescription = &this->m_pDescription;
  v12 = 5;
  do
  {
    if ( *p_m_pDescription )
    {
      result = (*(int (**)(UIStatic *, int))(*(_DWORD *)(*p_m_pDescription)->_pad_0000 + 20))(
                 *p_m_pDescription,
                 1);
      *p_m_pDescription = 0;
    }
    ++p_m_pDescription;
    --v12;
  }
  while ( v12 );
  return result;
}

// 0x0051B570
BOOL CCBItemWindow::HandleInput(int a2, int a3)
{
  if ( *(_DWORD *)&this->_pad_0000[56] == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_pad_0000[32] + 1160) + 8))->SetParam(214, -1);
  }
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x0051B5D0
int CCBItemWindow::OnMessage(int a2)
{
  int v3; // edi
  UIStatic **p_m_pDescription; // esi
  UIStatic *v5; // ecx

  if ( a2 == 1 )
  {
    v3 = 0;
    p_m_pDescription = &this->m_pDescription;
    do
    {
      v5 = (UIStatic *)*p_m_pDescription;
      if ( *((_DWORD *)this + 31) == v3 )
        (**(void (***)(UIStatic *, int))v5->_pad_0000)(v5, 1);
      else
        (**(void (***)(UIStatic *, _DWORD))v5->_pad_0000)(v5, 0);
      ++v3;
      ++p_m_pDescription;
    }
    while ( v3 < 5 );
  }
  return ((UIWnd *)this)->Destroy(a2);
}

// 0x0051B620
_DWORD * CCBItemWindow::Update()
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)this->_pad_0000 = &off_570554;
  sub_51B6E0(this);
  return this->_pad_0000;
}

// 0x0051B670
UIWnd * CCBItemWindow::CreateButtons(CCBItemWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}
