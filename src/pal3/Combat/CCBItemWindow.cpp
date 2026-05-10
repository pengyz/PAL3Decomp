#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBItemWindow.h"

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
  UIWnd::~UIWnd((UIWnd *)Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051B1D0
int CCBItemWindow::Reset()
{
  this->m_childs.m_pData = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_nMaxSize = 0;
  this->m_childs.m_nGrowBy = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_benable = 0;
  this->m_bfocus = 0;
  this->m_pbktex = 0;
  this->m_pBack = 0;
  this->m_pDescription = 0;
  this->m_pItemList[0] = 0;
  this->m_pItemList[1] = 0;
  this->m_pItemList[2] = (UIListBox *)-1;
  return 0;
}

// 0x0051B210
char CCBItemWindow::Create(int _this, _DWORD *a2, int a3)
{
  _DWORD *v4; // ebx
  _DWORD *v5; // ebx
  _DWORD *v6; // ebx
  _DWORD *v7; // ebx
  _DWORD *v8; // ebx
  _DWORD *v9; // ebx
  _DWORD *v10; // ebx
  gbRefObject ***v11; // ebx
  int i; // ebp
  _DWORD *v13; // ebx

  (_DWORD *->Create()this, 1879048196, a2, a3);
  v4 = (_DWORD *)(this + 72);
  CCBLineupWindow::Destroy(this + 72);
  *a2 = 0;
  a2[2] = 158;
  a2[1] = 0;
  a2[3] = 158;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v4 + 16))(*v4, 232, a2, this);
  UIWnd::CreateFromTemplate(*(gbRefObject ***)(this + 72), aUiCombatContro_18, 0);
  (**(void (***)(_DWORD, int))*v4)(*v4, 1);
  v5 = (_DWORD *)(this + 96);
  CCBLineupWindow::OnMessage(this + 96);
  *a2 = 7;
  a2[2] = 80;
  a2[1] = 48;
  a2[3] = 73;
  (*(void (**)(_DWORD, int, _DWORD *, int, char *, _DWORD))(*(_DWORD *)*v5 + 28))(
    *v5,
    214,
    a2,
    this,
    aUiCombatContro_11,
    0);
  (**(void (***)(_DWORD, int))*v5)(*v5, 1);
  v6 = (_DWORD *)(this + 100);
  CCBLineupWindow::OnMessage(this + 100);
  *a2 = 78;
  a2[2] = 151;
  a2[1] = 48;
  a2[3] = 73;
  (*(void (**)(_DWORD, int, _DWORD *, int, char *, _DWORD))(*(_DWORD *)*v6 + 28))(
    *v6,
    215,
    a2,
    this,
    aUiCombatContro_12,
    0);
  (**(void (***)(_DWORD, int))*v6)(*v6, 1);
  v7 = (_DWORD *)(this + 104);
  CCBLineupWindow::OnMessage(this + 104);
  a2[1] = 73;
  *a2 = 7;
  a2[2] = 80;
  a2[3] = 98;
  (*(void (**)(_DWORD, int, _DWORD *, int, char *, _DWORD))(*(_DWORD *)*v7 + 28))(
    *v7,
    216,
    a2,
    this,
    aUiCombatContro_13,
    0);
  (**(void (***)(_DWORD, int))*v7)(*v7, 1);
  v8 = (_DWORD *)(this + 108);
  CCBLineupWindow::OnMessage(this + 108);
  *a2 = 78;
  a2[2] = 151;
  a2[1] = 73;
  a2[3] = 98;
  (*(void (**)(_DWORD, int, _DWORD *, int, char *, _DWORD))(*(_DWORD *)*v8 + 28))(
    *v8,
    217,
    a2,
    this,
    aUiCombatContro_14,
    0);
  (**(void (***)(_DWORD, int))*v8)(*v8, 1);
  v9 = (_DWORD *)(this + 112);
  CCBLineupWindow::OnMessage(this + 112);
  *a2 = 7;
  a2[2] = 80;
  a2[1] = 98;
  a2[3] = 123;
  (*(void (**)(_DWORD, int, _DWORD *, int, char *, _DWORD))(*(_DWORD *)*v9 + 28))(
    *v9,
    218,
    a2,
    this,
    aUiCombatContro_15,
    0);
  (**(void (***)(_DWORD, int))*v9)(*v9, 1);
  v10 = (_DWORD *)(this + 116);
  CCBLineupWindow::OnMessage(this + 116);
  *a2 = 78;
  a2[2] = 151;
  a2[1] = 98;
  a2[3] = 123;
  (*(void (**)(_DWORD, int, _DWORD *, int, char *, _DWORD))(*(_DWORD *)*v10 + 28))(
    *v10,
    219,
    a2,
    this,
    aUiCombatContro_16,
    0);
  (**(void (***)(_DWORD, int))*v10)(*v10, 1);
  v11 = (gbRefObject ***)(this + 76);
  for ( i = 0; i < 5; ++i )
  {
    v11->Destroy();
    *a2 = 57;
    a2[2] = 95;
    a2[1] = 31;
    a2[3] = 47;
    ((void (*)(gbRefObject **, int, _DWORD *, int))(**v11)[4].RefCount)(*v11, dword_570138[i], a2, this);
    UIWnd::CreateFromTemplate(*v11, off_570218[i], 0);
    ((void (*)(gbRefObject **, int))(**v11)->RefCount)(*v11, 1);
    ++v11;
  }
  v13 = (_DWORD *)(this + 120);
  CCBLineupWindow::Update(this + 120);
  *a2 = 35;
  a2[2] = 127;
  a2[1] = 127;
  a2[3] = 153;
  (*(void (**)(_DWORD, int, _DWORD *, int, char *, int, _DWORD))(*(_DWORD *)*v13 + 28))(
    *v13,
    220,
    a2,
    this,
    aUiCombatContro_17,
    1,
    0);
  (**(void (***)(_DWORD, int))*v13)(*v13, 1);
  return 1;
}

// 0x0051B4B0
int CCBItemWindow::Destroy(int _this)
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
  _DWORD *v11; // esi
  int v12; // edi

  result = (gbRefObject **->SetScrollPos()this);
  v3 = *(_DWORD *)(this + 72);
  if ( v3 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v4 = *(_DWORD *)(this + 96);
  if ( v4 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v5 = *(_DWORD *)(this + 100);
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  v6 = *(_DWORD *)(this + 104);
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 104) = 0;
  }
  v7 = *(_DWORD *)(this + 108);
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 108) = 0;
  }
  v8 = *(_DWORD *)(this + 112);
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 112) = 0;
  }
  v9 = *(_DWORD *)(this + 116);
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 116) = 0;
  }
  v10 = *(_DWORD *)(this + 120);
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)(this + 120) = 0;
  }
  v11 = (_DWORD *)(this + 76);
  v12 = 5;
  do
  {
    if ( *v11 )
    {
      result = (*(int (**)(_DWORD, int))(*(_DWORD *)*v11 + 20))(*v11, 1);
      *v11 = 0;
    }
    ++v11;
    --v12;
  }
  while ( v12 );
  return result;
}

// 0x0051B570
BOOL CCBItemWindow::HandleInput(int a2, int a3)
{
  if ( this->m_rect.top == 1
    && (g_Input.m_DIKToKEY[1] == 1 && (g_Input.m_shiftedKeyStates[268] & 0xF) == 1 || g_Input.m_DIKToKEY[5] == 1) )
  {
    CCBUI::SetParam(*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8), 214, -1);
  }
  return this->HitTest(a2, a3);
}

// 0x0051B5D0
int CCBItemWindow::OnMessage(int a2)
{
  int v3; // edi
  int *p_m_nSize; // esi
  void (***v5)(_DWORD, int); // ecx

  if ( a2 == 1 )
  {
    v3 = 0;
    p_m_nSize = (int *)&this->m_childs.m_nSize;
    do
    {
      v5 = (void (***)(_DWORD, int))*p_m_nSize;
      if ( this->m_pItemList[2] == (UIListBox *)v3 )
        (**v5)(v5, 1);
      else
        (**v5)(v5, 0);
      ++v3;
      ++p_m_nSize;
    }
    while ( v3 < 5 );
  }
  return this->Destroy(a2);
}

// 0x0051B620
_DWORD * CCBItemWindow::Update()
{
  (UIListBox *->UIListBox()this);
  this->m_fontcolor.ColorQuadFmt = (int)&off_570554;
  sub_51B6E0(this);
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0051B670
UIWnd * CCBItemWindow::CreateButtons(CCBItemWindow *Block, char a2)
{
  UIWnd::~UIWnd((UIWnd *)Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}
