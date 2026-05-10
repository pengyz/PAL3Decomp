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
char CCBItemWindow::Create(_DWORD *pRect, int parent)
{
  PtrArray *p_m_childs; // ebx
  int *p_m_benable; // ebx
  int *p_m_bfocus; // ebx
  gbTexture **p_m_pbktex; // ebx
  UIStatic **p_m_pBack; // ebx
  UIStatic **p_m_pDescription; // ebx
  UIListBox **m_pItemList; // ebx
  int *p_m_nSize; // ebx
  int i; // ebp
  UIListBox **v13; // ebx

  this->Create(1879048196, pRect, parent);
  p_m_childs = (PtrArray *)&this->m_childs;
  ((CCBLineupWindow *)&this->m_childs.m_pData)->Destroy();
  *pRect = 0;
  pRect[2] = 158;
  pRect[1] = 0;
  pRect[3] = 158;
  (*(void (**)(void *, int, _DWORD *, CCBItemWindow *))(*(_DWORD *)p_m_childs->m_pData + 16))(
    p_m_childs->m_pData,
    232,
    pRect,
    this);
  ((UIWnd **)this->m_childs.m_pData)->CreateFromTemplate(aUiCombatContro_18, 0);
  (**(void (***)(void *, int))p_m_childs->m_pData)(p_m_childs->m_pData, 1);
  p_m_benable = (int *)&this->m_benable;
  ((CCBLineupWindow *)&this->m_benable)->OnMessage();
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(int, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*p_m_benable + 28))(
    *p_m_benable,
    214,
    pRect,
    this,
    aUiCombatContro_11,
    0);
  (**(void (***)(int, int))*p_m_benable)(*p_m_benable, 1);
  p_m_bfocus = (int *)&this->m_bfocus;
  ((CCBLineupWindow *)&this->m_bfocus)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void (**)(int, int, _DWORD *, CCBItemWindow *, char *, _DWORD))(*(_DWORD *)*p_m_bfocus + 28))(
    *p_m_bfocus,
    215,
    pRect,
    this,
    aUiCombatContro_12,
    0);
  (**(void (***)(int, int))*p_m_bfocus)(*p_m_bfocus, 1);
  p_m_pbktex = &this->m_pbktex;
  ((CCBLineupWindow *)&this->m_pbktex)->OnMessage();
  pRect[1] = 73;
  *pRect = 7;
  pRect[2] = 80;
  pRect[3] = 98;
  (*(void (**)(gbTexture *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))((*p_m_pbktex)->RefCount + 28))(
    *p_m_pbktex,
    216,
    pRect,
    this,
    aUiCombatContro_13,
    0);
  (*(void (**)(gbTexture *, int))(*p_m_pbktex)->RefCount)(*p_m_pbktex, 1);
  p_m_pBack = &this->m_pBack;
  ((CCBLineupWindow *)&this->m_pBack)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 73;
  pRect[3] = 98;
  (*(void (**)(UIStatic *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))((*p_m_pBack)->m_fontcolor.ColorQuadFmt
                                                                                     + 28))(
    *p_m_pBack,
    217,
    pRect,
    this,
    aUiCombatContro_14,
    0);
  (*(void (**)(UIStatic *, int))(*p_m_pBack)->m_fontcolor.ColorQuadFmt)(*p_m_pBack, 1);
  p_m_pDescription = &this->m_pDescription;
  ((CCBLineupWindow *)&this->m_pDescription)->OnMessage();
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void (**)(UIStatic *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))((*p_m_pDescription)->m_fontcolor.ColorQuadFmt
                                                                                     + 28))(
    *p_m_pDescription,
    218,
    pRect,
    this,
    aUiCombatContro_15,
    0);
  (*(void (**)(UIStatic *, int))(*p_m_pDescription)->m_fontcolor.ColorQuadFmt)(*p_m_pDescription, 1);
  m_pItemList = this->m_pItemList;
  ((CCBLineupWindow *)this->m_pItemList)->OnMessage();
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void (**)(UIListBox *, int, _DWORD *, CCBItemWindow *, char *, _DWORD))((*m_pItemList)->m_fontcolor.ColorQuadFmt
                                                                                      + 28))(
    *m_pItemList,
    219,
    pRect,
    this,
    aUiCombatContro_16,
    0);
  (*(void (**)(UIListBox *, int))(*m_pItemList)->m_fontcolor.ColorQuadFmt)(*m_pItemList, 1);
  p_m_nSize = (int *)&this->m_childs.m_nSize;
  for ( i = 0; i < 5; ++i )
  {
    p_m_nSize->Destroy();
    *pRect = 57;
    pRect[2] = 95;
    pRect[1] = 31;
    pRect[3] = 47;
    (*(void (**)(int, int, _DWORD *, CCBItemWindow *))(*(_DWORD *)*p_m_nSize + 16))(
      *p_m_nSize,
      dword_570138[i],
      pRect,
      this);
    ((UIWnd **)*p_m_nSize)->CreateFromTemplate(off_570218[i], 0);
    (**(void (***)(int, int))*p_m_nSize)(*p_m_nSize, 1);
    ++p_m_nSize;
  }
  v13 = &this->m_pItemList[1];
  ((CCBLineupWindow *)&this->m_pItemList[1])->Update();
  *pRect = 35;
  pRect[2] = 127;
  pRect[1] = 127;
  pRect[3] = 153;
  (*(void (**)(UIListBox *, int, _DWORD *, CCBItemWindow *, char *, int, _DWORD))((*v13)->m_fontcolor.ColorQuadFmt
                                                                                           + 28))(
    *v13,
    220,
    pRect,
    this,
    aUiCombatContro_17,
    1,
    0);
  (*(void (**)(UIListBox *, int))(*v13)->m_fontcolor.ColorQuadFmt)(*v13, 1);
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

  result = ((UIListBox **)this)->SetScrollPos();
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
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(214, -1);
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
  ((UIListBox *)this)->UIListBox();
  this->m_fontcolor.ColorQuadFmt = (int)&off_570554;
  sub_51B6E0(this);
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0051B670
UIWnd * CCBItemWindow::CreateButtons(CCBItemWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}
