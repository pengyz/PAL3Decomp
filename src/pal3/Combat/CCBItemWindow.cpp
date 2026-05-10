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
  this->_d048 = 0;
  this->_d04C = 0;
  this->_d050 = 0;
  this->_d054 = 0;
  this->_d058 = 0;
  this->_d05C = 0;
  this->_d060 = 0;
  this->_d064 = 0;
  this->_d068 = 0;
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
  int *p_d048; // ebx
  int *p_d060; // ebx
  int *p_d064; // ebx
  int *p_d068; // ebx
  CCBItemWindow *v8; // ebx
  CCBItemWindow *v9; // ebx
  CCBItemWindow *v10; // ebx
  int *p_d04C; // ebx
  int i; // ebp
  CCBItemWindow *v13; // ebx

  ((UIWnd *)this)->Create(1879048196, pRect, parent);
  p_d048 = (int *)&this->_d048;
  ((CCBLineupWindow *)&this->_d048)->Destroy();
  *pRect = 0;
  pRect[2] = 158;
  pRect[1] = 0;
  pRect[3] = 158;
  (*(void (**)(int, int, _DWORD *, CCBItemWindow *))(*(_DWORD *)*p_d048 + 16))(*p_d048, 232, pRect, this);
  ((UIWnd *)this->_d048)->CreateFromTemplate(aUiCombatContro_18, 0);
  (**(void (***)(int, int))*p_d048)(*p_d048, 1);
  p_d060 = (int *)&this->_d060;
  ((CCBLineupWindow *)&this->_d060)->OnMessage();
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(int, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*p_d060 + 28))(
    *p_d060,
    214,
    pRect,
    this,
    aUiCombatContro_11,
    0);
  (**(void (***)(int, int))*p_d060)(*p_d060, 1);
  p_d064 = (int *)&this->_d064;
  ((CCBLineupWindow *)&this->_d064)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(int, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*p_d064 + 28))(
    *p_d064,
    215,
    pRect,
    this,
    aUiCombatContro_12,
    0);
  (**(void (***)(int, int))*p_d064)(*p_d064, 1);
  p_d068 = (int *)&this->_d068;
  ((CCBLineupWindow *)&this->_d068)->OnMessage();
  pRect[1] = 73;
  *pRect = 7;
  pRect[2] = 80;
  pRect[3] = 98;
  (*(void (**)(int, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*p_d068 + 28))(
    *p_d068,
    216,
    pRect,
    this,
    aUiCombatContro_13,
    0);
  (**(void (***)(int, int))*p_d068)(*p_d068, 1);
  v8 = (CCBItemWindow *)this + 1;
  ((CCBLineupWindow *)(_DWORD *)this + 27)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 73;
  pRect[3] = 98;
  (*(void (**)(void *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)v8->_p000 + 28))(
    v8->_p000,
    217,
    pRect,
    this,
    aUiCombatContro_14,
    0);
  (**(void (***)(void *, int))v8->_p000)(v8->_p000, 1);
  v9 = (CCBItemWindow *)((char *)this + 112);
  ((CCBLineupWindow *)(_DWORD *)this + 28)->OnMessage();
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void (**)(void *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)v9->_p000 + 28))(
    v9->_p000,
    218,
    pRect,
    this,
    aUiCombatContro_15,
    0);
  (**(void (***)(void *, int))v9->_p000)(v9->_p000, 1);
  v10 = (CCBItemWindow *)((char *)this + 116);
  ((CCBLineupWindow *)(_DWORD *)this + 29)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void (**)(void *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)v10->_p000 + 28))(
    v10->_p000,
    219,
    pRect,
    this,
    aUiCombatContro_16,
    0);
  (**(void (***)(void *, int))v10->_p000)(v10->_p000, 1);
  p_d04C = (int *)&this->_d04C;
  for ( i = 0; i < 5; ++i )
  {
    p_d04C->Destroy();
    *pRect = 57;
    pRect[2] = 95;
    pRect[1] = 31;
    pRect[3] = 47;
    (*(void (**)(int, int, _DWORD *, CCBItemWindow *))(*(_DWORD *)*p_d04C + 16))(
      *p_d04C,
      dword_570138[i],
      pRect,
      this);
    ((UIWnd *)*p_d04C)->CreateFromTemplate(off_570218[i], 0);
    (**(void (***)(int, int))*p_d04C)(*p_d04C, 1);
    ++p_d04C;
  }
  v13 = (CCBItemWindow *)((char *)this + 120);
  ((CCBLineupWindow *)(_DWORD *)this + 30)->Update();
  *pRect = 35;
  pRect[2] = 127;
  pRect[1] = 127;
  pRect[3] = 153;
  (*(void (**)(void *, int, _DWORD *, CCBItemWindow *, char *, int, _DWORD))(*(_DWORD *)v13->_p000 + 28))(
    v13->_p000,
    220,
    pRect,
    this,
    aUiCombatContro_17,
    1,
    0);
  (**(void (***)(void *, int))v13->_p000)(v13->_p000, 1);
  return 1;
}

// 0x0051B4B0
int CCBItemWindow::Destroy()
{
  int result; // eax
  int d048; // ecx
  int d060; // ecx
  int d064; // ecx
  int d068; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int *p_d04C; // esi
  int v12; // edi

  result = ((UIListBox *)this)->SetScrollPos();
  d048 = this->_d048;
  if ( d048 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d048 + 20))(d048, 1);
    this->_d048 = 0;
  }
  d060 = this->_d060;
  if ( d060 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d060 + 20))(d060, 1);
    this->_d060 = 0;
  }
  d064 = this->_d064;
  if ( d064 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d064 + 20))(d064, 1);
    this->_d064 = 0;
  }
  d068 = this->_d068;
  if ( d068 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d068 + 20))(d068, 1);
    this->_d068 = 0;
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
  p_d04C = (int *)&this->_d04C;
  v12 = 5;
  do
  {
    if ( *p_d04C )
    {
      result = (*(int (**)(int, int))(*(_DWORD *)*p_d04C + 20))(*p_d04C, 1);
      *p_d04C = 0;
    }
    ++p_d04C;
    --v12;
  }
  while ( v12 );
  return result;
}

// 0x0051B570
BOOL CCBItemWindow::HandleInput(int a2, int a3)
{
  if ( this->_d038 == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(214, -1);
  }
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x0051B5D0
int CCBItemWindow::OnMessage(int a2)
{
  int v3; // edi
  int *p_d04C; // esi
  void (***v5)(_DWORD, int); // ecx

  if ( a2 == 1 )
  {
    v3 = 0;
    p_d04C = (int *)&this->_d04C;
    do
    {
      v5 = (void (***)(_DWORD, int))*p_d04C;
      if ( *((_DWORD *)this + 31) == v3 )
        (**v5)(v5, 1);
      else
        (**v5)(v5, 0);
      ++v3;
      ++p_d04C;
    }
    while ( v3 < 5 );
  }
  return ((UIWnd *)this)->Destroy(a2);
}

// 0x0051B620
_DWORD * CCBItemWindow::Update()
{
  ((UIListBox *)this)->UIListBox();
  this->_p000 = &off_570554;
  sub_51B6E0(this);
  return &this->_p000;
}

// 0x0051B670
UIWnd * CCBItemWindow::CreateButtons(CCBItemWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}
