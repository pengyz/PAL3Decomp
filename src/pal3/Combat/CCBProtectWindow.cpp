#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBProtectWindow.h"

// Forward declarations for unnamed functions
int sub_51D6E0(...);
int sub_51D700(...);
int sub_51D710(...);
int sub_51DD80(...);
int sub_51DDA0(...);
int sub_51F070(...);

// Unnamed globals (extern)
extern int dword_17AD59C;
extern float flt_17AD598;
extern void *off_5705D0;

// 0x0051D6E0
int sub_51D6E0()
{
  dword_17AD59C = 1094713344;
  return 1094713344;
}

// 0x0051D6F0
// attributes: thunk
void CCBProtectWindow::~CCBProtectWindow()
{
  CCBProtectWindow::Reset();
}

// 0x0051D700
void sub_51D700()
{
  flt_17AD598 = 12.0 + 12.0;
}

// 0x0051D710
int sub_51D710(int _this)
{
  _DWORD *v2; // eax
  int v3; // ebp
  _DWORD *v4; // ecx
  _DWORD *v5; // eax
  _DWORD *v6; // ebp
  _DWORD *v7; // ebp
  _DWORD *v8; // ebp
  _DWORD *v9; // eax
  int v10; // ebp
  _DWORD *v11; // ecx
  _DWORD *v12; // eax
  _DWORD *v13; // ebp
  _DWORD *v14; // ebp
  _DWORD *v15; // ebp
  _DWORD *v16; // eax
  int v17; // ebp
  _DWORD *v18; // eax
  int v19; // ecx
  _DWORD *v21; // [esp+10h] [ebp-18h]
  _DWORD *v22; // [esp+10h] [ebp-18h]
  _DWORD *v23; // [esp+10h] [ebp-18h]
  int v24; // [esp+14h] [ebp-14h]
  int v25; // [esp+14h] [ebp-14h]
  int v26; // [esp+14h] [ebp-14h]
  int v27; // [esp+14h] [ebp-14h]
  int v28; // [esp+14h] [ebp-14h]

  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 128;
  *(_DWORD *)(this + 92) = 512;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 100) = 0;
  (_BYTE *->UIFrameWnd()(this + 360));
  (_BYTE *->UIFrameWnd()(this + 512));
  (_BYTE *->UIFrameWnd()(this + 664));
  `eh vector constructor iterator'(
    (void *)(this + 816),
    0x98u,
    6,
    (void (__thiscall *)(void *))UIFrameWnd::UIFrameWnd,
    (void (__thiscall *)(void *))UIFrameWnd::_UIFrameWnd);
  (_DWORD *->_UIScene()(this + 1744));
  (_DWORD *->_UIScene()(this + 2088));
  (char *->UIStatic()(this + 2432));
  (_DWORD *->_UIScene()(this + 2680));
  (_DWORD *->_UIScene()(this + 3024));
  (_DWORD *->_UIScene()(this + 3368));
  (char *->UIStatic()(this + 3728));
  (char *->UIStatic()(this + 3976));
  (char *->UIStatic()(this + 4224));
  (char *->UIStatic()(this + 4472));
  (char *->UIStatic()(this + 4736));
  (char *->UIStatic()(this + 4984));
  (char *->UIStatic()(this + 5232));
  (char *->UIStatic()(this + 5496));
  (char *->UIStatic()(this + 5744));
  (char *->UIStatic()(this + 5992));
  (char *->UIStatic()(this + 6256));
  (char *->UIStatic()(this + 6504));
  (char *->UIStatic()(this + 6752));
  (char *->UIStatic()(this + 7016));
  (char *->UIStatic()(this + 7264));
  (char *->UIStatic()(this + 7512));
  (char *->UIStatic()(this + 7760));
  v2 = (_DWORD *)(this + 8052);
  *(_DWORD *)(this + 8008) = 0;
  *(_DWORD *)(this + 8012) = 0;
  *(_DWORD *)(this + 8016) = 0;
  *(_DWORD *)(this + 8020) = 0;
  *(_BYTE *)(this + 8025) = 1;
  *(_BYTE *)(this + 8026) = 0;
  *(_DWORD *)(this + 8048) = 0;
  v21 = (_DWORD *)(this + 8052);
  v3 = this + 8088;
  v24 = 396;
  while ( 1 )
  {
    *v2 = 0;
    lstrcpyA((LPSTR)(v3 - 32), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)v3, MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v3 + 30), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v3 + 60), MEMORY[0xC10D38]);
    *(_BYTE *)(v3 + 576) = 0;
    memset((void *)(v3 + 608), 0, 0x18u);
    *(_BYTE *)(v3 + 764) = 0;
    *(_BYTE *)(v3 + 765) = 0;
    *(_DWORD *)(v3 + 768) = -1;
    v3 += 808;
    v21 += 202;
    if ( !--v24 )
      break;
    v2 = v21;
  }
  *(_DWORD *)(this + 328020) = 0;
  *(_DWORD *)(this + 328024) = 0;
  *(_DWORD *)(this + 328028) = 0;
  *(_DWORD *)(this + 328032) = 1;
  *(_DWORD *)(this + 328036) = 1;
  *(_DWORD *)(this + 328040) = 1;
  *(_DWORD *)(this + 328044) = 0;
  *(_DWORD *)(this + 328048) = 0;
  *(_WORD *)(this + 328054) = 0;
  *(_DWORD *)(this + 341948) = 0;
  v25 = 4;
  *(_DWORD *)(this + 341952) = 0;
  memset((void *)(this + 341956), 0, 0x640u);
  memset((void *)(this + 345156), 0, 0x190u);
  memset((void *)(this + 343556), 0, 0x640u);
  *(_DWORD *)(this + 328052) = 0;
  v4 = (_DWORD *)(this + 345608);
  *(_DWORD *)(this + 345572) = 0;
  *(_DWORD *)(this + 345576) = 0;
  *(_DWORD *)(this + 345580) = 0;
  v5 = (_DWORD *)(this + 345644);
  do
  {
    v6 = v5 - 6;
    *v4 = 0;
    *(v5 - 8) = 0;
    *(v5 - 7) = 0;
    *v6 = 0;
    v4 += 12;
    v6[1] = 0;
    v6[2] = 0;
    v7 = v5 - 3;
    *(v5 - 3) = 0;
    v7[1] = 0;
    v7[2] = 0;
    v8 = v5;
    v5 += 12;
    *v8 = 0;
    v8[1] = 0;
    v8[2] = 0;
    --v25;
  }
  while ( v25 );
  *(_BYTE *)(this + 345584) = 0;
  *(_BYTE *)(this + 345585) = 0;
  *(_BYTE *)(this + 345586) = 0;
  *(_BYTE *)(this + 345587) = 0;
  *(_BYTE *)(this + 345588) = 0;
  *(_BYTE *)(this + 345589) = 0;
  *(_BYTE *)(this + 345590) = 0;
  *(_DWORD *)(this + 345592) = 1065353216;
  *(_DWORD *)(this + 345596) = 0;
  *(_DWORD *)(this + 345600) = 0;
  *(_DWORD *)(this + 345604) = 0;
  *(_DWORD *)(this + 345800) = 0;
  memset((void *)(this + 345608), 0, 0xC0u);
  v9 = (_DWORD *)(this + 345804);
  v26 = 200;
  v22 = (_DWORD *)(this + 345804);
  v10 = this + 345840;
  while ( 1 )
  {
    *v9 = 0;
    lstrcpyA((LPSTR)(v10 - 32), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)v10, MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v10 + 30), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v10 + 60), MEMORY[0xC10D38]);
    *(_BYTE *)(v10 + 576) = 0;
    memset((void *)(v10 + 608), 0, 0x18u);
    *(_BYTE *)(v10 + 764) = 0;
    *(_BYTE *)(v10 + 765) = 0;
    *(_DWORD *)(v10 + 768) = -1;
    v10 += 808;
    v22 += 202;
    if ( !--v26 )
      break;
    v9 = v22;
  }
  v11 = (_DWORD *)(this + 507472);
  *(_DWORD *)(this + 507420) = 1;
  *(_DWORD *)(this + 507424) = 1;
  *(_DWORD *)(this + 507428) = 1;
  *(_DWORD *)(this + 507432) = 0;
  *(_DWORD *)(this + 507436) = 0;
  *(_DWORD *)(this + 507440) = 0;
  *(_DWORD *)(this + 507444) = 0;
  v12 = (_DWORD *)(this + 507508);
  v27 = 4;
  do
  {
    v13 = v12 - 6;
    *v11 = 0;
    *(v12 - 8) = 0;
    *(v12 - 7) = 0;
    *v13 = 0;
    v11 += 12;
    v13[1] = 0;
    v13[2] = 0;
    v14 = v12 - 3;
    *(v12 - 3) = 0;
    v14[1] = 0;
    v14[2] = 0;
    v15 = v12;
    v12 += 12;
    *v15 = 0;
    v15[1] = 0;
    v15[2] = 0;
    --v27;
  }
  while ( v27 );
  *(_BYTE *)(this + 507448) = 0;
  *(_BYTE *)(this + 507449) = 0;
  *(_BYTE *)(this + 507450) = 0;
  *(_BYTE *)(this + 507451) = 0;
  *(_BYTE *)(this + 507452) = 0;
  *(_BYTE *)(this + 507453) = 0;
  *(_BYTE *)(this + 507454) = 0;
  *(_DWORD *)(this + 507456) = 1065353216;
  *(_DWORD *)(this + 507460) = 0;
  *(_DWORD *)(this + 507464) = 0;
  *(_DWORD *)(this + 507468) = 0;
  *(_DWORD *)(this + 507664) = 0;
  memset((void *)(this + 507472), 0, 0xC0u);
  v16 = (_DWORD *)(this + 507668);
  v28 = 200;
  v23 = (_DWORD *)(this + 507668);
  v17 = this + 507704;
  while ( 1 )
  {
    *v16 = 0;
    lstrcpyA((LPSTR)(v17 - 32), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)v17, MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v17 + 30), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v17 + 60), MEMORY[0xC10D38]);
    *(_BYTE *)(v17 + 576) = 0;
    memset((void *)(v17 + 608), 0, 0x18u);
    *(_BYTE *)(v17 + 764) = 0;
    *(_BYTE *)(v17 + 765) = 0;
    *(_DWORD *)(v17 + 768) = -1;
    v17 += 808;
    v23 += 202;
    if ( !--v28 )
      break;
    v16 = v23;
  }
  *(_DWORD *)(this + 669296) = 0;
  *(_DWORD *)(this + 669284) = 1;
  *(_DWORD *)(this + 669288) = 1;
  *(_DWORD *)(this + 669292) = 1;
  *(_BYTE *)(this + 669300) = 0;
  UIItem::Refresh(this + 669304);
  UIItem::Refresh(this + 670672);
  *(_DWORD *)this = &off_5705D0;
  v18 = (_DWORD *)(this + 8028);
  v19 = 4;
  do
  {
    v18[84382] = 0;
    *v18++ = 0;
    --v19;
  }
  while ( v19 );
  return this;
}

// 0x0051DD80
UIWnd * sub_51DD80(UIWnd *Block, char a2)
{
  Block->ShowWindow();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0051DDA0
void sub_51DDA0()
{
  *(_DWORD *)this = &off_5705D0;
  *((_BYTE *)this + 8025) = 1;
  UIItem::UIItem((int)this + 670672);
  UIItem::UIItem((int)this + 669304);
  UIWnd::~UIWnd((UIWnd *)this + 194);
  UIWnd::~UIWnd((UIWnd *)((char *)this + 7512));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 7264));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 7016));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 6752));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 6504));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 6256));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 5992));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 5744));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 5496));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 5232));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 4984));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 4736));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 4472));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 4224));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 3976));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 3728));
  (UIWnd *->Destroy2()((char *)this + 3368));
  (UIWnd *->Destroy2()((char *)this + 3024));
  (UIWnd *->Destroy2()this + 67);
  UIWnd::~UIWnd((UIWnd *)((char *)this + 2432));
  (UIWnd *->Destroy2()((char *)this + 2088));
  (UIWnd *->Destroy2()((char *)this + 1744));
  `eh vector destructor iterator'((char *)this + 816, 0x98u, 6, (void (__thiscall *)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 664));
  (UIWnd *->_UIFrameWnd()((char *)this + 512));
  (UIWnd *->_UIFrameWnd()this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x0051F070
int sub_51F070(int a2)
{
  *((_DWORD *)this + 2003) = a2;
  return a2;
}
