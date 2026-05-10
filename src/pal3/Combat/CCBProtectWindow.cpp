#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBProtectWindow.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIItem.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIStatic.h"
#include "pal3/gen/UIWnd.h"

// Unnamed globals (extern)
extern int dword_17AD59C;
extern float flt_17AD598;
extern void *off_5705D0;

// 0x0051D6E0
CCBProtectWindow::CCBProtectWindow()
{
  dword_17AD59C = 1094713344;
  1094713344;
}

// 0x0051D6F0
// attributes: thunk
CCBProtectWindow::~CCBProtectWindow()
{
  CCBProtectWindow::Reset();
}

// 0x0051D700
void CCBProtectWindow::Reset()
{
  flt_17AD598 = 12.0 + 12.0;
}

// 0x0051D710
int CCBProtectWindow::Create()
{
  CCBProtectWindow *v2; // eax
  CHAR *v3; // ebp
  CCBProtectWindow *v4; // ecx
  char *v5; // eax
  char *v6; // ebp
  char *v7; // ebp
  _DWORD *v8; // ebp
  CCBProtectWindow *v9; // eax
  CHAR *v10; // ebp
  CCBProtectWindow *v11; // ecx
  char *v12; // eax
  char *v13; // ebp
  char *v14; // ebp
  _DWORD *v15; // ebp
  CCBProtectWindow *v16; // eax
  CHAR *v17; // ebp
  CCBProtectWindow *v18; // eax
  int v19; // ecx
  CCBProtectWindow *v21; // [esp+10h] [ebp-18h]
  CCBProtectWindow *v22; // [esp+10h] [ebp-18h]
  CCBProtectWindow *v23; // [esp+10h] [ebp-18h]
  int v24; // [esp+14h] [ebp-14h]
  int v25; // [esp+14h] [ebp-14h]
  int v26; // [esp+14h] [ebp-14h]
  int v27; // [esp+14h] [ebp-14h]
  int v28; // [esp+14h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  this->m_pWPXLove = (UIProgressBar *)128;
  this->m_pOk = (UIButton *)512;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 25) = 0;
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 512))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 664))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 816,
    0x98u,
    6,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)((char *)this + 1744))->_UIScene();
  ((UIScene *)((char *)this + 2088))->_UIScene();
  ((UIStatic *)((char *)this + 2432))->UIStatic();
  ((UIScene *)((char *)this + 2680))->_UIScene();
  ((UIScene *)((char *)this + 3024))->_UIScene();
  ((UIScene *)((char *)this + 3368))->_UIScene();
  ((UIStatic *)((char *)this + 3728))->UIStatic();
  ((UIStatic *)((char *)this + 3976))->UIStatic();
  ((UIStatic *)(this + 44))->UIStatic();
  ((UIStatic *)((char *)this + 4472))->UIStatic();
  ((UIStatic *)((char *)this + 4736))->UIStatic();
  ((UIStatic *)((char *)this + 4984))->UIStatic();
  ((UIStatic *)((char *)this + 5232))->UIStatic();
  ((UIStatic *)((char *)this + 5496))->UIStatic();
  ((UIStatic *)((char *)this + 5744))->UIStatic();
  ((UIStatic *)((char *)this + 5992))->UIStatic();
  ((UIStatic *)((char *)this + 6256))->UIStatic();
  ((UIStatic *)((char *)this + 6504))->UIStatic();
  ((UIStatic *)((char *)this + 6752))->UIStatic();
  ((UIStatic *)((char *)this + 7016))->UIStatic();
  ((UIStatic *)((char *)this + 7264))->UIStatic();
  ((UIStatic *)((char *)this + 7512))->UIStatic();
  ((UIStatic *)((char *)this + 7760))->UIStatic();
  v2 = (CCBProtectWindow *)((char *)this + 8052);
  *((_DWORD *)this + 2002) = 0;
  *((_DWORD *)this + 2003) = 0;
  *((_DWORD *)this + 2004) = 0;
  *((_DWORD *)this + 2005) = 0;
  *((_BYTE *)this + 8025) = 1;
  *((_BYTE *)this + 8026) = 0;
  *((_DWORD *)this + 2012) = 0;
  v21 = (CCBProtectWindow *)((char *)this + 8052);
  v3 = (char *)this + 8088;
  v24 = 396;
  while ( 1 )
  {
    *(_DWORD *)v2->_base._base._pad_000 = 0;
    lstrcpyA(v3 - 32, g_SceneMgr.m_szUIString);
    lstrcpyA(v3, g_SceneMgr.m_szUIString);
    lstrcpyA(v3 + 30, g_SceneMgr.m_szUIString);
    lstrcpyA(v3 + 60, g_SceneMgr.m_szUIString);
    v3[576] = 0;
    memset(v3 + 608, 0, 0x18u);
    v3[764] = 0;
    v3[765] = 0;
    *((_DWORD *)v3 + 192) = -1;
    v3 += 808;
    v21 = (CCBProtectWindow *)((char *)v21 + 808);
    if ( !--v24 )
      break;
    v2 = v21;
  }
  *((_DWORD *)this + 82005) = 0;
  *((_DWORD *)this + 82006) = 0;
  *((_DWORD *)this + 82007) = 0;
  *((_DWORD *)this + 82008) = 1;
  *((_DWORD *)this + 82009) = 1;
  *((_DWORD *)this + 82010) = 1;
  *((_DWORD *)this + 82011) = 0;
  *((_DWORD *)this + 82012) = 0;
  *((_WORD *)this + 164027) = 0;
  *((_DWORD *)this + 85487) = 0;
  v25 = 4;
  *((_DWORD *)this + 85488) = 0;
  memset((char *)this + 341956, 0, 0x640u);
  memset((char *)this + 345156, 0, 0x190u);
  memset((char *)this + 343556, 0, 0x640u);
  *((_DWORD *)this + 82013) = 0;
  v4 = (CCBProtectWindow *)((char *)this + 345608);
  *((_DWORD *)this + 86393) = 0;
  *((_DWORD *)this + 86394) = 0;
  *((_DWORD *)this + 86395) = 0;
  v5 = (char *)this + 345644;
  do
  {
    v6 = (char *)v5 - 24;
    *(_DWORD *)v4->_base._base._pad_000 = 0;
    *((_DWORD *)v5 - 8) = 0;
    *((_DWORD *)v5 - 7) = 0;
    *(_DWORD *)v6 = 0;
    v4 = (CCBProtectWindow *)((char *)v4 + 48);
    *((_DWORD *)v6 + 1) = 0;
    *((_DWORD *)v6 + 2) = 0;
    v7 = (char *)v5 - 12;
    *((_DWORD *)v5 - 3) = 0;
    *((_DWORD *)v7 + 1) = 0;
    *((_DWORD *)v7 + 2) = 0;
    v8 = v5;
    v5 += 48;
    *v8 = 0;
    v8[1] = 0;
    v8[2] = 0;
    --v25;
  }
  while ( v25 );
  *((_BYTE *)this + 345584) = 0;
  *((_BYTE *)this + 345585) = 0;
  *((_BYTE *)this + 345586) = 0;
  *((_BYTE *)this + 345587) = 0;
  *((_BYTE *)this + 345588) = 0;
  *((_BYTE *)this + 345589) = 0;
  *((_BYTE *)this + 345590) = 0;
  *((_DWORD *)this + 86398) = 1065353216;
  *((_DWORD *)this + 86399) = 0;
  *((_DWORD *)this + 86400) = 0;
  *((_DWORD *)this + 86401) = 0;
  *((_DWORD *)this + 86450) = 0;
  memset((char *)this + 345608, 0, 0xC0u);
  v9 = (CCBProtectWindow *)((char *)this + 345804);
  v26 = 200;
  v22 = (CCBProtectWindow *)((char *)this + 345804);
  v10 = (char *)this + 345840;
  while ( 1 )
  {
    *(_DWORD *)v9->_base._base._pad_000 = 0;
    lstrcpyA(v10 - 32, g_SceneMgr.m_szUIString);
    lstrcpyA(v10, g_SceneMgr.m_szUIString);
    lstrcpyA(v10 + 30, g_SceneMgr.m_szUIString);
    lstrcpyA(v10 + 60, g_SceneMgr.m_szUIString);
    v10[576] = 0;
    memset(v10 + 608, 0, 0x18u);
    v10[764] = 0;
    v10[765] = 0;
    *((_DWORD *)v10 + 192) = -1;
    v10 += 808;
    v22 = (CCBProtectWindow *)((char *)v22 + 808);
    if ( !--v26 )
      break;
    v9 = v22;
  }
  v11 = (CCBProtectWindow *)((char *)this + 507472);
  *((_DWORD *)this + 126855) = 1;
  *((_DWORD *)this + 126856) = 1;
  *((_DWORD *)this + 126857) = 1;
  *((_DWORD *)this + 126858) = 0;
  *((_DWORD *)this + 126859) = 0;
  *((_DWORD *)this + 126860) = 0;
  *((_DWORD *)this + 126861) = 0;
  v12 = (char *)this + 507508;
  v27 = 4;
  do
  {
    v13 = (char *)v12 - 24;
    *(_DWORD *)v11->_base._base._pad_000 = 0;
    *((_DWORD *)v12 - 8) = 0;
    *((_DWORD *)v12 - 7) = 0;
    *(_DWORD *)v13 = 0;
    v11 = (CCBProtectWindow *)((char *)v11 + 48);
    *((_DWORD *)v13 + 1) = 0;
    *((_DWORD *)v13 + 2) = 0;
    v14 = (char *)v12 - 12;
    *((_DWORD *)v12 - 3) = 0;
    *((_DWORD *)v14 + 1) = 0;
    *((_DWORD *)v14 + 2) = 0;
    v15 = v12;
    v12 += 48;
    *v15 = 0;
    v15[1] = 0;
    v15[2] = 0;
    --v27;
  }
  while ( v27 );
  *((_BYTE *)this + 507448) = 0;
  *((_BYTE *)this + 507449) = 0;
  *((_BYTE *)this + 507450) = 0;
  *((_BYTE *)this + 507451) = 0;
  *((_BYTE *)this + 507452) = 0;
  *((_BYTE *)this + 507453) = 0;
  *((_BYTE *)this + 507454) = 0;
  *((_DWORD *)this + 126864) = 1065353216;
  *((_DWORD *)this + 126865) = 0;
  *((_DWORD *)this + 126866) = 0;
  *((_DWORD *)this + 126867) = 0;
  *((_DWORD *)this + 126916) = 0;
  memset((char *)this + 507472, 0, 0xC0u);
  v16 = (CCBProtectWindow *)((char *)this + 507668);
  v28 = 200;
  v23 = (CCBProtectWindow *)((char *)this + 507668);
  v17 = (char *)this + 507704;
  while ( 1 )
  {
    *(_DWORD *)v16->_base._base._pad_000 = 0;
    lstrcpyA(v17 - 32, g_SceneMgr.m_szUIString);
    lstrcpyA(v17, g_SceneMgr.m_szUIString);
    lstrcpyA(v17 + 30, g_SceneMgr.m_szUIString);
    lstrcpyA(v17 + 60, g_SceneMgr.m_szUIString);
    v17[576] = 0;
    memset(v17 + 608, 0, 0x18u);
    v17[764] = 0;
    v17[765] = 0;
    *((_DWORD *)v17 + 192) = -1;
    v17 += 808;
    v23 = (CCBProtectWindow *)((char *)v23 + 808);
    if ( !--v28 )
      break;
    v16 = v23;
  }
  *((_DWORD *)this + 167324) = 0;
  *((_DWORD *)this + 167321) = 1;
  *((_DWORD *)this + 167322) = 1;
  *((_DWORD *)this + 167323) = 1;
  *((_BYTE *)this + 669300) = 0;
  ((UIItem *)(UIItem *)this + 669304)->Refresh();
  ((UIItem *)(UIItem *)this + 670672)->Refresh();
  *(_DWORD *)this->_base._base._pad_000 = &off_5705D0;
  v18 = (CCBProtectWindow *)((char *)this + 8028);
  v19 = 4;
  do
  {
    v18[3515].m_pWPXLove = 0;
    *(_DWORD *)v18->_base._base._pad_000 = 0;
    v18 = (CCBProtectWindow *)((char *)v18 + 4);
    --v19;
  }
  while ( v19 );
  return (int)this;
}

// 0x0051DD80
UIWnd * CCBProtectWindow::Destroy(CCBProtectWindow *Block, char a2)
{
  Block->ShowWindow();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051DDA0
void CCBProtectWindow::ShowWindow()
{
  *(_DWORD *)this->_base._base._pad_000 = &off_5705D0;
  *((_BYTE *)this + 8025) = 1;
  ((UIItem *)(UIItem *)this + 670672)->UIItem();
  ((UIItem *)(UIItem *)this + 669304)->UIItem();
  ((UIWnd *)((char *)this + 7760))->~UIWnd();
  ((UIWnd *)((char *)this + 7512))->~UIWnd();
  ((UIWnd *)((char *)this + 7264))->~UIWnd();
  ((UIWnd *)((char *)this + 7016))->~UIWnd();
  ((UIWnd *)((char *)this + 6752))->~UIWnd();
  ((UIWnd *)((char *)this + 6504))->~UIWnd();
  ((UIWnd *)(UIWnd *)this + 92)->~UIWnd();
  ((UIWnd *)((char *)this + 5992))->~UIWnd();
  ((UIWnd *)((char *)this + 5744))->~UIWnd();
  ((UIWnd *)((char *)this + 5496))->~UIWnd();
  ((UIWnd *)((char *)this + 5232))->~UIWnd();
  ((UIWnd *)((char *)this + 4984))->~UIWnd();
  ((UIWnd *)((char *)this + 4736))->~UIWnd();
  ((UIWnd *)((char *)this + 4472))->~UIWnd();
  ((UIWnd *)(this + 44))->~UIWnd();
  ((UIWnd *)((char *)this + 3976))->~UIWnd();
  ((UIWnd *)((char *)this + 3728))->~UIWnd();
  ((UIScene *)((char *)this + 3368))->Destroy2();
  ((UIScene *)((char *)this + 3024))->Destroy2();
  ((UIScene *)((char *)this + 2680))->Destroy2();
  ((UIWnd *)((char *)this + 2432))->~UIWnd();
  ((UIScene *)((char *)this + 2088))->Destroy2();
  ((UIScene *)((char *)this + 1744))->Destroy2();
  `eh vector destructor iterator'((char *)this + 816, 0x98u, 6, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 664))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 512))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->_UIFrameWnd();
  ((UIWnd *)&this->_base._base)->~UIWnd();
}

// 0x0051F070
int CCBProtectWindow::Update(int a2)
{
  *((_DWORD *)this + 2003) = a2;
  return a2;
}
