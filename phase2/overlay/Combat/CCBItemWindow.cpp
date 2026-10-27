#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBItemWindow.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBLineupWindow.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "Scene/SceneObj.h"
#include "Misc/UIButton.h"
#include "UI/UIListBox.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_51A400(...);
int sub_51B6E0(...);

// 0x004461B0
CCBItemWindow::CCBItemWindow()
{
  int v2; // [esp+0x0] [ebp-0x4]

  *(_BYTE *)((UIWnd *)this) = 0;
  UIScenePanel__UIScenePanel(v2);
  LOBYTE(this[2].m_pButtonAttack) = 0;
}

// 0x00450650
char * CCBItemWindow::SetItemName(char *pszName)
{
  return strncpy((char *)&this->m_pButtonAttack, pszName, 0xFFu);
}

// 0x0051A390
void CCBItemWindow::DoTask(int a2)
{
  this->~CCBItemWindow();
  if ( (a2 & 1) != 0 )
    operator delete(this);
}

// 0x0051A3B0
CCBItemWindow::~CCBItemWindow()
{
  sub_51A400(this);
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0051A880
void CCBItemWindow::CCBItemWindow_Destroy()
{
  UIStatic **p_m_pDescription; // edi
  int v3; // ebx
  UIPushButton *m_pButtonTreasure; // ecx
  int m_nActivePage; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  UIStatic *m_pBack; // ecx

  // [overlay-fix 2026-10-27] C2065: Destroy__ovl_03 无定义/声明（IDA overlay 合成名）——待归属定谳
  // Destroy__ovl_03((int)this);
  p_m_pDescription = (UIStatic **)&this->m_pDescription;
  v3 = 6;
  do
  {
    if ( *p_m_pDescription )
    {
      (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)(*p_m_pDescription)) + 20))(*p_m_pDescription, 1);
      *p_m_pDescription = 0;
    }
    ++p_m_pDescription;
    --v3;
  }
  while ( v3 );
  m_pButtonTreasure = (UIPushButton *)this->m_pButtonTreasure;
  if ( m_pButtonTreasure )
  {
    (*(void ( **)(UIPushButton *, int))(*(_DWORD *)((UIWnd *)m_pButtonTreasure) + 20))(m_pButtonTreasure, 1);
    this->m_pButtonTreasure = ((UIPushButton *)0);
  }
  m_nActivePage = this->m_nActivePage;
  if ( m_nActivePage )
  {
    (*(void ( **)(int, int))(*(_DWORD *)m_nActivePage + 20))(m_nActivePage, 1);
    this->m_nActivePage = 0;
  }
  v6 = *(&this->m_nActivePage + 1);
  if ( v6 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(&this->m_nActivePage + 1) = 0;
  }
  v7 = *(&this->m_nActivePage + 2);
  if ( v7 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(&this->m_nActivePage + 2) = 0;
  }
  v8 = *(&this->m_nActivePage + 3);
  if ( v8 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(&this->m_nActivePage + 3) = 0;
  }
  v9 = *(&this->m_nActivePage + 4);
  if ( v9 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(&this->m_nActivePage + 4) = 0;
  }
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pBack) + 20))(m_pBack, 1);
    this->m_pBack = ((UIStatic *)0);
  }
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
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa001", 1);
      (((CCBControlWindow *)this))->CCBControlWindow::HandleInput((UIButton *)(nMsg - 192)) /* [ROWTABLE] */;
      Child = (((UIListBox *)*((UIListBox **)&this[-3] + nMsg - 32)))->UIListBox::CreateChild();
      if ( Child != -1 )
        (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(g_nSkillItemIDTable[18] + nMsg - 192, Child, 1);
    }
  }
  else if ( nVal == 1006 )
  {
    if ( wParam != -1 )
      (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(nMsg, wParam, 1);
  }
  else if ( nVal == 1007 && wParam != -1 )
  {
    v5 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v5))->CScreenMode::AudioSetPosition("wa002", 1);
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(nMsg, wParam, 0);
  }
  return this->UIWnd::OnMessage(nVal, nMsg, wParam);
}

// 0x0051B1D0
void CCBItemWindow::Reset()
{
  this->m_pBack = ((UIStatic *)0);
  this->m_pDescription = ((UIStatic *)0);
  this->m_pItemList[0] = 0;
  this->m_pItemList[1] = 0;
  this->m_pItemList[2] = 0;
  this->m_pButtonRecover = ((UIPushButton *)0);
  this->m_pButtonAttack = ((UIPushButton *)0);
  this->m_pButtonTreasure = ((UIPushButton *)0);
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
  UIPushButton **p_m_pDescription; // ebx
  int i; // ebp
  int *v21; // ebx

  this->UIWnd::Create(1879048196, (tagRECT *)pRect, (UIWnd *)parent);
  p_m_pBack = (UIStatic **)&this->m_pBack;
  (((CCBLineupWindow *)v5))->CCBLineupWindow::Destroy();
  *pRect = 0;
  pRect[2] = 158;
  pRect[1] = 0;
  pRect[3] = 158;
  (*(void ( **)(UIStatic *, int, int *, CCBItemWindow *))(*(_DWORD *)((UIWnd *)(*p_m_pBack)) + 16))(
    *p_m_pBack,
    232,
    pRect,
    this);
  (((UIPushButton *)this->m_pBack))->UIPushButton::CreateFromTemplate((void *)g_nUnkDataTable[29], 0);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)(*p_m_pBack)))((UIStatic *)(*p_m_pBack), (int)(1));
  p_m_pButtonAttack = (UIPushButton **)&this->m_pButtonAttack;
  (((CCBLineupWindow *)v7))->CCBLineupWindow::OnMessage((int *)&this->m_pButtonAttack);
  *pRect = 7;
  pRect[2] = 80;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void ( **)(UIPushButton *, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)((UIWnd *)(*p_m_pButtonAttack))
                                                                                   + 28))(
    *p_m_pButtonAttack,
    214,
    pRect,
    this,
    g_nUnkDataTable[22],
    0);
  (**(void ( ***)(UIPushButton *, int))((UIWnd *)(*p_m_pButtonAttack)))((UIPushButton *)(*p_m_pButtonAttack), (int)(1));
  p_m_pButtonTreasure = (UIPushButton **)&this->m_pButtonTreasure;
  (((CCBLineupWindow *)v9))->CCBLineupWindow::OnMessage((int *)&this->m_pButtonTreasure);
  *pRect = 78;
  pRect[2] = 151;
  pRect[1] = 48;
  pRect[3] = 73;
  (*(void ( **)(UIPushButton *, int, int *, CCBItemWindow *, int, _DWORD))(*(_DWORD *)((UIWnd *)(*p_m_pButtonTreasure))
                                                                                   + 28))(
    *p_m_pButtonTreasure,
    215,
    pRect,
    this,
    g_nUnkDataTable[23],
    0);
  (**(void ( ***)(UIPushButton *, int))((UIWnd *)(*p_m_pButtonTreasure)))((UIPushButton *)(*p_m_pButtonTreasure), (int)(1));
  p_m_nActivePage = (int *)&this->m_nActivePage;
  (((CCBLineupWindow *)v11))->CCBLineupWindow::OnMessage(&this->m_nActivePage);
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
  (**(void ( ***)(int, int))*p_m_nActivePage)((int)(*p_m_nActivePage), (int)(1));
  v12 = (int *)(&this->m_nActivePage + 1);
  (((CCBLineupWindow *)v13))->CCBLineupWindow::OnMessage(&this->m_nActivePage + 1);
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
  (**(void ( ***)(int, int))*v12)((int)(*v12), (int)(1));
  v14 = (int *)(&this->m_nActivePage + 2);
  (((CCBLineupWindow *)v15))->CCBLineupWindow::OnMessage(&this->m_nActivePage + 2);
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
  (**(void ( ***)(int, int))*v14)((int)(*v14), (int)(1));
  v16 = (int *)(&this->m_nActivePage + 3);
  (((CCBLineupWindow *)v17))->CCBLineupWindow::OnMessage(&this->m_nActivePage + 3);
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
  (**(void ( ***)(int, int))*v16)((int)(*v16), (int)(1));
  p_m_pDescription = (UIPushButton **)&this->m_pDescription;
  for ( i = 0; i < 5; ++i )
  {
    (((CCBLineupWindow *)v18))->CCBLineupWindow::Destroy();
    *pRect = 57;
    pRect[2] = 95;
    pRect[1] = 31;
    pRect[3] = 47;
    (*(void ( **)(UIPushButton *, int, int *, CCBItemWindow *))(*(_DWORD *)((UIWnd *)(*p_m_pDescription)) + 16))(
      *p_m_pDescription,
      g_nPropIDs_208[i],
      pRect,
      this);
    (((UIPushButton *)*p_m_pDescription))->UIPushButton::CreateFromTemplate((void *)g_nUnkDataTable[i + 17], 0);
    (**(void ( ***)(UIPushButton *, int))((UIWnd *)(*p_m_pDescription)))((UIPushButton *)(*p_m_pDescription), (int)(1));
    ++p_m_pDescription;
  }
  v21 = (int *)(&this->m_nActivePage + 4);
  (((CCBLineupWindow *)v18))->CCBLineupWindow::Update(&this->m_nActivePage + 4);
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
  (**(void ( ***)(int, int))*v21)((int)(*v21), (int)(1));
  return 1;
}

// 0x0051B4B0
void CCBItemWindow::Destroy()
{
  UIStatic *m_pBack; // ecx
  UIPushButton *m_pButtonAttack; // ecx
  UIPushButton *m_pButtonTreasure; // ecx
  int m_nActivePage; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  UIStatic **p_m_pDescription; // esi
  int v11; // edi

  // [overlay-fix 2026-10-27] C2065: Destroy__ovl_03 无定义/声明（IDA overlay 合成名）——待归属定谳
  // Destroy__ovl_03((int)this);
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pBack) + 20))(m_pBack, 1);
    this->m_pBack = ((UIStatic *)0);
  }
  m_pButtonAttack = (UIPushButton *)this->m_pButtonAttack;
  if ( m_pButtonAttack )
  {
    (*(void ( **)(UIPushButton *, int))(*(_DWORD *)((UIWnd *)m_pButtonAttack) + 20))(m_pButtonAttack, 1);
    this->m_pButtonAttack = ((UIPushButton *)0);
  }
  m_pButtonTreasure = (UIPushButton *)this->m_pButtonTreasure;
  if ( m_pButtonTreasure )
  {
    (*(void ( **)(UIPushButton *, int))(*(_DWORD *)((UIWnd *)m_pButtonTreasure) + 20))(m_pButtonTreasure, 1);
    this->m_pButtonTreasure = ((UIPushButton *)0);
  }
  m_nActivePage = this->m_nActivePage;
  if ( m_nActivePage )
  {
    (*(void ( **)(int, int))(*(_DWORD *)m_nActivePage + 20))(m_nActivePage, 1);
    this->m_nActivePage = 0;
  }
  v6 = *(&this->m_nActivePage + 1);
  if ( v6 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(&this->m_nActivePage + 1) = 0;
  }
  v7 = *(&this->m_nActivePage + 2);
  if ( v7 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(&this->m_nActivePage + 2) = 0;
  }
  v8 = *(&this->m_nActivePage + 3);
  if ( v8 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(&this->m_nActivePage + 3) = 0;
  }
  v9 = *(&this->m_nActivePage + 4);
  if ( v9 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(&this->m_nActivePage + 4) = 0;
  }
  p_m_pDescription = (UIStatic **)&this->m_pDescription;
  v11 = 5;
  do
  {
    if ( *p_m_pDescription )
    {
      (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)(*p_m_pDescription)) + 20))(*p_m_pDescription, 1);
      *p_m_pDescription = 0;
    }
    ++p_m_pDescription;
    --v11;
  }
  while ( v11 );
}

// 0x0051B570
BOOL CCBItemWindow::HandleInput(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(214, -1, 0);
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x0051B620
UIListBox * CCBItemWindow::Update()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  sub_51B6E0(this);
  return (UIListBox *)this;
}

// 0x0051B670
UIWnd * CCBItemWindow::CreateButtons(CCBItemWindow *Block, char pData)
{
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}
