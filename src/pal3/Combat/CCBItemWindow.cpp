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
  *(_DWORD *)&this->_data[72] = 0;
  *(_DWORD *)&this->_data[76] = 0;
  *(_DWORD *)&this->_data[80] = 0;
  *(_DWORD *)&this->_data[84] = 0;
  *(_DWORD *)&this->_data[88] = 0;
  *(_DWORD *)&this->_data[92] = 0;
  *(_DWORD *)&this->_data[96] = 0;
  *(_DWORD *)&this->_data[100] = 0;
  *(_DWORD *)&this->_data[104] = 0;
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
  char *v4; // ebx
  char *v5; // ebx
  char *v6; // ebx
  char *v7; // ebx
  CCBItemWindow *v8; // ebx
  _DWORD *v9; // ebx
  _DWORD *v10; // ebx
  char *v11; // ebx
  int i; // ebp
  _DWORD *v13; // ebx

  ((UIWnd *)this)->Create(1879048196, pRect, parent);
  v4 = (char *)&this->_data[72];
  ((CCBLineupWindow *)&this->_data[72])->Destroy();
  *pRect = 0;
  pRect[2] = 158;
  pRect[1] = 0;
  pRect[3] = 158;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *))(**(_DWORD **)v4 + 16))(
    *(_DWORD *)v4,
    232,
    pRect,
    this);
  ((UIWnd *)*(UIWnd ***)&this->_data[72])->CreateFromTemplate(aUiCombatContro_18, 0);
  (***(void (****)(_DWORD, int))v4)(*(_DWORD *)v4, 1);
  v5 = (char *)&this->_data[96];
  ((CCBLineupWindow *)&this->_data[96])->OnMessage();
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(**(_DWORD **)v5 + 28))(
    *(_DWORD *)v5,
    214,
    pRect,
    this,
    aUiCombatContro_11,
    0);
  (***(void (****)(_DWORD, int))v5)(*(_DWORD *)v5, 1);
  v6 = (char *)&this->_data[100];
  ((CCBLineupWindow *)&this->_data[100])->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(**(_DWORD **)v6 + 28))(
    *(_DWORD *)v6,
    215,
    pRect,
    this,
    aUiCombatContro_12,
    0);
  (***(void (****)(_DWORD, int))v6)(*(_DWORD *)v6, 1);
  v7 = (char *)&this->_data[104];
  ((CCBLineupWindow *)&this->_data[104])->OnMessage();
  pRect[1] = 73;
  *pRect = 7;
  pRect[2] = 80;
  pRect[3] = 98;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(**(_DWORD **)v7 + 28))(
    *(_DWORD *)v7,
    216,
    pRect,
    this,
    aUiCombatContro_13,
    0);
  (***(void (****)(_DWORD, int))v7)(*(_DWORD *)v7, 1);
  v8 = (CCBItemWindow *)this + 1;
  ((CCBLineupWindow *)(_DWORD *)this + 27)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 73;
  pRect[3] = 98;
  (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(**(_DWORD **)v8->_data + 28))(
    *(_DWORD *)v8->_data,
    217,
    pRect,
    this,
    aUiCombatContro_14,
    0);
  (***(void (****)(_DWORD, int))v8->_data)(*(_DWORD *)v8->_data, 1);
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
  v11 = (char *)&this->_data[76];
  for ( i = 0; i < 5; ++i )
  {
    v11->Destroy();
    *pRect = 57;
    pRect[2] = 95;
    pRect[1] = 31;
    pRect[3] = 47;
    (*(void (**)(_DWORD, int, _DWORD *, CCBItemWindow *))(**(_DWORD **)v11 + 16))(
      *(_DWORD *)v11,
      dword_570138[i],
      pRect,
      this);
    ((UIWnd *)*(UIWnd ***)v11)->CreateFromTemplate(off_570218[i], 0);
    (***(void (****)(_DWORD, int))v11)(*(_DWORD *)v11, 1);
    v11 += 4;
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
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  char *v11; // esi
  int v12; // edi

  result = ((UIListBox *)this)->SetScrollPos();
  v3 = *(_DWORD *)&this->_data[72];
  if ( v3 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)&this->_data[72] = 0;
  }
  v4 = *(_DWORD *)&this->_data[96];
  if ( v4 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *(_DWORD *)&this->_data[96] = 0;
  }
  v5 = *(_DWORD *)&this->_data[100];
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)&this->_data[100] = 0;
  }
  v6 = *(_DWORD *)&this->_data[104];
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)&this->_data[104] = 0;
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
  v11 = (char *)&this->_data[76];
  v12 = 5;
  do
  {
    if ( *(_DWORD *)v11 )
    {
      result = (*(int (**)(_DWORD, int))(**(_DWORD **)v11 + 20))(*(_DWORD *)v11, 1);
      *(_DWORD *)v11 = 0;
    }
    v11 += 4;
    --v12;
  }
  while ( v12 );
  return result;
}

// 0x0051B570
BOOL CCBItemWindow::HandleInput(int a2, int a3)
{
  if ( *(_DWORD *)&this->_data[56] == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_data[32] + 1160) + 8))->SetParam(214, -1);
  }
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x0051B5D0
int CCBItemWindow::OnMessage(int a2)
{
  int v3; // edi
  char *v4; // esi
  void (***v5)(_DWORD, int); // ecx

  if ( a2 == 1 )
  {
    v3 = 0;
    v4 = (char *)&this->_data[76];
    do
    {
      v5 = *(void (****)(_DWORD, int))v4;
      if ( *((_DWORD *)this + 31) == v3 )
        (**v5)(v5, 1);
      else
        (**v5)(v5, 0);
      ++v3;
      v4 += 4;
    }
    while ( v3 < 5 );
  }
  return ((UIWnd *)this)->Destroy(a2);
}

// 0x0051B620
_DWORD * CCBItemWindow::Update()
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)this->_data = &off_570554;
  sub_51B6E0(this);
  return this->_data;
}

// 0x0051B670
UIWnd * CCBItemWindow::CreateButtons(CCBItemWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}
