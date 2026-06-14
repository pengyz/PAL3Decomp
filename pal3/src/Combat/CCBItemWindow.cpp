#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBItemWindow.h"

// Forward declarations for unnamed functions
int sub_4431B0(...);
int sub_51A400(...);
int sub_51B6E0(...);

// 0x004461B0
CCBItemWindow::CCBItemWindow()
{
// [VFTABLE] LOBYTE(this->__vftable) = 0;
  ((UIScenePanel *)&this->m_pButtonAttack)->_UIScenePanel();
  *((_BYTE *)this + 472) = 0;
}

// 0x00450650
char * CCBItemWindow::SetItemName(char *pszName)
{
  return strncpy((char *)&this->m_pButtonAttack, pszName, 0xFFu);
}

// 0x0051A3B0
void CCBItemWindow::_CCBItemWindow()
{
  sub_51A400(this);
  ((UIListBox *)this)->_UIListBox();
}

// 0x0051A930
int CCBItemWindow::HandleMessage(int nVal, unsigned int nMsg, int wParam)
{
  CScreenMode *v5; // eax
  CScreenMode *Instance; // eax
  int Child; // eax

  if ( nVal == 1001 )
  {
    if ( nMsg >= 0xC0 && nMsg <= 0xC5 )
    {
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition("wa001", 1);
      ((CCBControlWindow *)this)->HandleInput((UIButton *)(nMsg - 192));
      Child = ((NPC *)*((NPC **)this + nMsg - 173))->CreateChild();
      if ( Child != -1 )
        ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(g_nSkillItemIDTable[18] + nMsg - 192, Child);
    }
  }
  else if ( nVal == 1006 )
  {
    if ( wParam != -1 )
      ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(nMsg, wParam);
  }
  else if ( nVal == 1007 && wParam != -1 )
  {
    v5 = CScreenMode::GetInstance();
    ((CScreenMode *)v5)->AudioSetPosition("wa002", 1);
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(nMsg, wParam);
  }
  return ((PalScript *)this)->OnMessage(nVal, nMsg, wParam);
}

// 0x0051B1D0
void CCBItemWindow::Reset()
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
  *(&this->m_nActivePage + 1) = 0;
  *(&this->m_nActivePage + 2) = 0;
  *(&this->m_nActivePage + 3) = 0;
  *(&this->m_nActivePage + 4) = 0;
  *(&this->m_nActivePage + 5) = -1;
}

// 0x0051B210
bool CCBItemWindow::Create(int *pRect, int parent)
{
  UIStatic **p_m_pBack; // ebx
  CCBLineupWindow *v5; // ecx
  UIPushButton **p_m_pButtonAttack; // ebx
  CCBLineupWindow *v7; // ecx
  UIPushButton **p_m_pButtonTreasure; // ebx
  CCBLineupWindow *v9; // ecx
  int *p_m_nActivePage; // ebx
  CCBLineupWindow *v11; // ecx
  int *v12; // ebx
  CCBLineupWindow *v13; // ecx
  int *v14; // ebx
  CCBLineupWindow *v15; // ecx
  int *v16; // ebx
  CCBLineupWindow *v17; // ecx
  CCBLineupWindow *v18; // ecx
  UIStatic **p_m_pDescription; // ebx
  int i; // ebp
  int *v21; // ebx

  ((PalScript *)this)->Create(1879048196, (tagRECT *)pRect, parent);
  p_m_pBack = &this->m_pBack;
  ((CCBLineupWindow *)v5)->Destroy();
  *pRect = 0;
  pRect[2] = 158;
  pRect[1] = 0;
  pRect[3] = 158;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBItemWindow *))(*p_m_pBack)->__vftable->Create)(
// [VFTABLE]   *p_m_pBack,
// [VFTABLE]   232,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
  ((UIStatic *)this->m_pBack)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))(*p_m_pBack)->__vftable->ShowWindow)(*p_m_pBack, 1);
  p_m_pButtonAttack = &this->m_pButtonAttack;
  ((CCBLineupWindow *)v7)->OnMessage((int *)&this->m_pButtonAttack);
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 48;
  pRect[3] = 73;
// [VFTABLE] ((void ( *)(UIPushButton *, int, int *, CCBItemWindow *, int, _DWORD))(*p_m_pButtonAttack)->__vftable[1].ShowWindow)(
// [VFTABLE]   *p_m_pButtonAttack,
// [VFTABLE]   214,
// [VFTABLE]   pRect,
// [VFTABLE]   this,
// [VFTABLE]   g_nUnkDataTable[22],
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIPushButton *, int))(*p_m_pButtonAttack)->__vftable->ShowWindow)(*p_m_pButtonAttack, 1);
  p_m_pButtonTreasure = &this->m_pButtonTreasure;
  ((CCBLineupWindow *)v9)->OnMessage((int *)&this->m_pButtonTreasure);
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 48;
  pRect[3] = 73;
// [VFTABLE] ((void ( *)(UIPushButton *, int, int *, CCBItemWindow *, int, _DWORD))(*p_m_pButtonTreasure)->__vftable[1].ShowWindow)(
// [VFTABLE]   *p_m_pButtonTreasure,
// [VFTABLE]   215,
// [VFTABLE]   pRect,
// [VFTABLE]   this,
// [VFTABLE]   g_nUnkDataTable[23],
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIPushButton *, int))(*p_m_pButtonTreasure)->__vftable->ShowWindow)(*p_m_pButtonTreasure, 1);
  p_m_nActivePage = &this->m_nActivePage;
  ((CCBLineupWindow *)v11)->OnMessage(&this->m_nActivePage);
  pRect[1] = 73;
  *pRect = 7;
  pRect[2] = 80;
  pRect[3] = 98;
  (*(void ( **)(int, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)*p_m_nActivePage + 28))(
    *p_m_nActivePage,
    216,
    pRect,
    this,
    g_nUnkDataTable[24],
    0);
  (**(void ( ***)(int, int))*p_m_nActivePage)(*p_m_nActivePage, 1);
  v12 = &this->m_nActivePage + 1;
  ((CCBLineupWindow *)v13)->OnMessage(&this->m_nActivePage + 1);
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 73;
  pRect[3] = 98;
  (*(void ( **)(int, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)*v12 + 28))(
    *v12,
    217,
    pRect,
    this,
    g_nUnkDataTable[25],
    0);
  (**(void ( ***)(int, int))*v12)(*v12, 1);
  v14 = &this->m_nActivePage + 2;
  ((CCBLineupWindow *)v15)->OnMessage(&this->m_nActivePage + 2);
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void ( **)(int, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)*v14 + 28))(
    *v14,
    218,
    pRect,
    this,
    g_nUnkDataTable[26],
    0);
  (**(void ( ***)(int, int))*v14)(*v14, 1);
  v16 = &this->m_nActivePage + 3;
  ((CCBLineupWindow *)v17)->OnMessage(&this->m_nActivePage + 3);
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 98;
  pRect[3] = 123;
  (*(void ( **)(int, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)*v16 + 28))(
    *v16,
    219,
    pRect,
    this,
    g_nUnkDataTable[27],
    0);
  (**(void ( ***)(int, int))*v16)(*v16, 1);
  p_m_pDescription = &this->m_pDescription;
  for ( i = 0; i < 5; ++i )
  {
    ((CCBLineupWindow *)v18)->Destroy();
    *pRect = 57;
    pRect[2] = 95;
    pRect[1] = 31;
    pRect[3] = 47;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBItemWindow *))(*p_m_pDescription)->__vftable->Create)(
// [VFTABLE]   *p_m_pDescription,
// [VFTABLE]   g_nPropIDs_208[i],
// [VFTABLE]   pRect,
// [VFTABLE]   this);
    ((UIStatic *)*p_m_pDescription)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))(*p_m_pDescription)->__vftable->ShowWindow)(*p_m_pDescription, 1);
    ++p_m_pDescription;
  }
  v21 = &this->m_nActivePage + 4;
  ((CCBLineupWindow *)v18)->Update(&this->m_nActivePage + 4);
  *pRect = 35;
  pRect[2] = 127;
  pRect[1] = 127;
  pRect[3] = 153;
  (*(void ( **)(int, int, int *, CCBItemWindow *, int, int, _DWORD))(*(_DWORD *)*v21 + 28))(
    *v21,
    220,
    pRect,
    this,
    g_nUnkDataTable[28],
    1,
    0);
  (**(void ( ***)(int, int))*v21)(*v21, 1);
  return 1;
}

// 0x0051B4B0
void CCBItemWindow::Destroy(CCBItemWindow *thisa)
{
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
  UIListBox *v13; // [esp+0x0] [ebp-0xC]
  int v14; // [esp+0x4] [ebp-0x8]

  ((CCBRoleState *)this)->Destroy(v13, v14);
  m_pBack = this->m_pBack;
  if ( m_pBack )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pBack->__vftable->sub_4431B0)(m_pBack, 1);
    this->m_pBack = 0;
  }
  m_pButtonAttack = this->m_pButtonAttack;
  if ( m_pButtonAttack )
  {
// [VFTABLE] ((void ( *)(UIPushButton *, int))m_pButtonAttack->__vftable->sub_4431B0)(m_pButtonAttack, 1);
    this->m_pButtonAttack = 0;
  }
  m_pButtonTreasure = this->m_pButtonTreasure;
  if ( m_pButtonTreasure )
  {
// [VFTABLE] ((void ( *)(UIPushButton *, int))m_pButtonTreasure->__vftable->sub_4431B0)(m_pButtonTreasure, 1);
    this->m_pButtonTreasure = 0;
  }
  m_nActivePage = this->m_nActivePage;
  if ( m_nActivePage )
  {
    (*(void ( **)(int, int))(*(_DWORD *)m_nActivePage + 20))(m_nActivePage, 1);
    this->m_nActivePage = 0;
  }
  v7 = *(&this->m_nActivePage + 1);
  if ( v7 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(&this->m_nActivePage + 1) = 0;
  }
  v8 = *(&this->m_nActivePage + 2);
  if ( v8 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(&this->m_nActivePage + 2) = 0;
  }
  v9 = *(&this->m_nActivePage + 3);
  if ( v9 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(&this->m_nActivePage + 3) = 0;
  }
  v10 = *(&this->m_nActivePage + 4);
  if ( v10 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(&this->m_nActivePage + 4) = 0;
  }
  p_m_pDescription = &this->m_pDescription;
  v12 = 5;
  do
  {
    if ( *p_m_pDescription )
    {
// [VFTABLE] ((void ( *)(UIStatic *, int))(*p_m_pDescription)->__vftable->sub_4431B0)(*p_m_pDescription, 1);
      *p_m_pDescription = 0;
    }
    ++p_m_pDescription;
    --v12;
  }
  while ( v12 );
}

// 0x0051B5D0
int CCBItemWindow::OnMessage(
        
        CCBItemWindow *thisa,
        unsigned int a2,
        unsigned int a4,
        unsigned int a5)
{
  int v6; // edi
  UIStatic **p_m_pDescription; // esi
  UIStatic *v8; // ecx

  if ( thisa == (CCBItemWindow *)1 )
  {
    v6 = 0;
    p_m_pDescription = &this->m_pDescription;
    do
    {
      v8 = *p_m_pDescription;
      if ( *(&this->m_nActivePage + 5) == v6 )
// [VFTABLE] ((void ( *)(UIStatic *, int))v8->__vftable->ShowWindow)(v8, 1);
      else
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v8->__vftable->ShowWindow)(v8, 0);
      ++v6;
      ++p_m_pDescription;
    }
    while ( v6 < 5 );
  }
  return ((PalScript *)this)->ShowWindow((int)thisa);
}

// 0x0051B620
UIListBox * CCBItemWindow::Update()
{
  sub_51B6E0(this);
  return (UIListBox *)this;
}

// 0x0051B670
UIWnd * CCBItemWindow::CreateButtons(CCBItemWindow *Block, char pData)
{
  ((CCBMagicWindow *)this)->_scalar_dtor();
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}
