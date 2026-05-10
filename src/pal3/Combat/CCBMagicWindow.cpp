#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBMagicWindow.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBSkillWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_43FBC0(...);
int sub_440CE0(...);
int sub_51BB50(...);

// Unnamed globals (extern)
extern char aUiCombatContro_22[];
extern char aUiCombatContro_23[];
extern char aUiCombatContro_24[];
extern char aUiCombatContro_25[];
extern char aUiCombatContro_26[];
extern char aUiCombatContro_27[];
extern char aUiCombatContro_28[];
extern char aUiCombatContro_29[];
extern char aUiCombatContro_30[];
extern char aUiCombatContro_31[];
extern char aUiCombatContro_32[];
extern int dword_57024C;
extern int dword_570268;
extern void *off_570570;
extern void *off_57058C;

// 0x0051B9F0
CCBMagicWindow::CCBMagicWindow(int a2, int a3, _DWORD *a4)
{
  int v4; // eax
  int *v5; // eax
  int v7; // [esp-14h] [ebp-40h]
  int v8; // [esp-10h] [ebp-3Ch]
  int v9; // [esp-Ch] [ebp-38h]
  int v10; // [esp-8h] [ebp-34h]
  _DWORD v11[4]; // [esp+Ch] [ebp-20h] BYREF
  _DWORD v12[4]; // [esp+1Ch] [ebp-10h] BYREF

  v4 = dword_57024C[a2];
  v7 = v4 + 9;
  v8 = dword_570268[a2] + 232;
  v9 = v4 + 49;
  v10 = dword_570268[a2] + 270;
  v5 = ((UIWnd *)*(this + a3 + 24))->SetRect(v12);
  if ( ((CCBLineupWindow *)*v5)->SetFaceLineup(v5[1], v5[2], v5[3], v7, v8, v9, v10, v11) )
  {
    *a4 = (v11[3] - v11[1]) * (v11[2] - v11[0]);
  1;
  }
  else
  {
    *a4 = 0;
  0;
  }
}

// 0x0051BAB0
CCBMagicWindow::~CCBMagicWindow()
{
  int v2; // edi
  int v4; // ebx
  int i; // esi
  int a4; // [esp+10h] [ebp-4h] BYREF

  v2 = 0;
  a4 = 0;
  v4 = -1;
  for ( i = 1; i < 7; ++i )
  {
    if ( this->CCBMagicWindow(i, a2, &a4) && a4 > v2 )
    {
      v4 = i;
      v2 = a4;
    }
  }
  v4;
}

// 0x0051BB00
int CCBMagicWindow::Reset(int a2, int a3)
{
  char *v3; // eax
  int v4; // esi

  v3 = (char *)&this->_data[72];
  v4 = 5;
  do
  {
    if ( *(_DWORD *)v3 == a3 )
      *(_DWORD *)v3 = *(_DWORD *)&this->_data[4 * a2 + 72];
    v3 += 4;
    --v4;
  }
  while ( v4 );
  *(_DWORD *)&this->_data[4 * a2 + 72] = a3;
  sub_51BB50(this->_data);
  return -1;
}

// 0x0051BB40
int CCBMagicWindow::Create(int a2)
{
  *(_DWORD *)&this->_data[116] = a2;
  return a2;
}

// 0x0051BB90
_DWORD * CCBMagicWindow::ForbidPage()
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)this->_data = &off_570570;
  this->OnMessage();
  return this->_data;
}

// 0x0051BBE0
UIWnd * CCBMagicWindow::Destroy(CCBMagicWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051BC50
int CCBMagicWindow::OnMessage()
{
  *(_DWORD *)&this->_data[72] = 0;
  *(_DWORD *)&this->_data[76] = 0;
  *(_DWORD *)&this->_data[80] = 0;
  *(_DWORD *)&this->_data[84] = 0;
  *(_DWORD *)&this->_data[88] = 0;
  *(_DWORD *)&this->_data[92] = 0;
  *(_DWORD *)&this->_data[96] = 0;
  *(_DWORD *)&this->_data[100] = 0;
  return 0;
}

// 0x0051BC70
char CCBMagicWindow::CreateButton(_DWORD *a2, int a3)
{
  UIWnd ***v4; // edi
  UIWnd **v5; // edi
  _DWORD *v6; // eax
  UIWnd *v7; // eax
  UIWnd **v8; // edi
  _DWORD *v9; // eax
  UIWnd *v10; // eax
  UIWnd **v11; // edi
  _DWORD *v12; // eax
  UIWnd *v13; // eax
  gbRefObject ***v14; // edi
  gbRefObject ***v15; // edi
  gbRefObject ***v16; // edi
  char *v17; // edi
  _DWORD a2a[4]; // [esp+3Ch] [ebp-10h] BYREF

  ((UIWnd *)this)->Create(1879048198, a2, a3);
  v4 = (UIWnd ***)&this->_data[72];
  if ( ((CCBLineupWindow *)&this->_data[72])->Destroy() == 1 )
  {
    *a2 = 0;
    a2[2] = 230;
    a2[1] = 0;
    a2[3] = 200;
    ((void (*)(UIWnd **, int, _DWORD *, CCBMagicWindow *))(**v4)->m_wndcolor.ColorQuadFmt)(
      *v4,
      272,
      a2,
      this);
    ((UIWnd *)*v4)->CreateFromTemplate(aUiCombatContro_22, 0);
    (*(void (**)(UIWnd **, int))(**v4)->_pad_0000)(*v4, 1);
  }
  v5 = (UIWnd **)&this->_data[88];
  if ( ((CCBLineupWindow *)&this->_data[88])->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 57;
    a2[2] = 211;
    a2[3] = 95;
    (*(void (**)(UIWnd *, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)(*v5)->_pad_0000 + 16))(
      *v5,
      276,
      a2,
      this);
    v6 = ((UIWnd *)*v5)->SetRect(a2a);
    ((UIWnd *)*v5)->AddChild(v6);
    ((UIWnd *)*v5)->GetChildCount(aUiCombatContro_29, 0);
    ((UIWnd *)*v5)->GetChildAt(aUiCombatContro_30, 0);
    ((UIWnd *)*v5)->SetFrameRate(48);
    ((UIWnd *)*v5)->GetHeight(23);
    ((UIWnd *)*v5)->GetWidth(11);
    ((UIWnd *)*v5)->GetPosition(5);
    sub_43FBC0((gbRefObject **)*v5, aUiCombatContro_31, 0);
    v7 = (UIWnd *)*v5;
    v7[2].m_id = 10;
    v7[2].m_rect.left = 9;
    ((UIWnd *)*v5)->FindChild(100.0);
    ((UIWnd *)*v5)->FindChildByName(100.0);
    (*v5)[1].m_id = 1077936128;
    (**(void (***)(UIWnd *, int))(*v5)->_pad_0000)(*v5, 1);
  }
  v8 = (UIWnd **)&this->_data[92];
  if ( ((CCBLineupWindow *)&this->_data[92])->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 94;
    a2[2] = 211;
    a2[3] = 132;
    (*(void (**)(UIWnd *, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)(*v8)->_pad_0000 + 16))(
      *v8,
      277,
      a2,
      this);
    v9 = ((UIWnd *)*v8)->SetRect(a2a);
    ((UIWnd *)*v8)->AddChild(v9);
    ((UIWnd *)*v8)->GetChildCount(aUiCombatContro_29, 0);
    ((UIWnd *)*v8)->GetChildAt(aUiCombatContro_30, 0);
    ((UIWnd *)*v8)->SetFrameRate(48);
    ((UIWnd *)*v8)->GetHeight(23);
    ((UIWnd *)*v8)->GetWidth(11);
    ((UIWnd *)*v8)->GetPosition(5);
    sub_43FBC0((gbRefObject **)*v8, aUiCombatContro_31, 0);
    v10 = (UIWnd *)*v8;
    v10[2].m_id = 10;
    v10[2].m_rect.left = 9;
    ((UIWnd *)*v8)->FindChild(100.0);
    ((UIWnd *)*v8)->FindChildByName(100.0);
    (*v8)[1].m_id = 1077936128;
    (**(void (***)(UIWnd *, int))(*v8)->_pad_0000)(*v8, 1);
  }
  v11 = (UIWnd **)&this->_data[96];
  if ( ((CCBLineupWindow *)&this->_data[96])->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 132;
    a2[2] = 211;
    a2[3] = 170;
    (*(void (**)(UIWnd *, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)(*v11)->_pad_0000 + 16))(
      *v11,
      278,
      a2,
      this);
    v12 = ((UIWnd *)*v11)->SetRect(a2a);
    ((UIWnd *)*v11)->AddChild(v12);
    ((UIWnd *)*v11)->GetChildCount(aUiCombatContro_29, 0);
    ((UIWnd *)*v11)->GetChildAt(aUiCombatContro_30, 0);
    ((UIWnd *)*v11)->SetFrameRate(48);
    ((UIWnd *)*v11)->GetHeight(23);
    ((UIWnd *)*v11)->GetWidth(11);
    ((UIWnd *)*v11)->GetPosition(5);
    sub_43FBC0((gbRefObject **)*v11, aUiCombatContro_31, 0);
    v13 = (UIWnd *)*v11;
    v13[2].m_id = 10;
    v13[2].m_rect.left = 9;
    ((UIWnd *)*v11)->FindChild(100.0);
    ((UIWnd *)*v11)->FindChildByName(100.0);
    (*v11)[1].m_id = 1077936128;
    (**(void (***)(UIWnd *, int))(*v11)->_pad_0000)(*v11, 1);
  }
  v14 = (gbRefObject ***)&this->_data[76];
  if ( ((CCBLineupWindow *)&this->_data[76])->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 57;
    a2[2] = 69;
    a2[3] = 89;
    ((void (*)(gbRefObject **, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(**v14)[3].RefCount)(
      *v14,
      273,
      a2,
      this,
      aUiCombatContro_23,
      0);
    sub_440CE0(*v14, aUiCombatContro_26, 0);
    (*(void (**)(gbRefObject **, int))(**v14)->_pad_0000)(*v14, 1);
  }
  v15 = (gbRefObject ***)&this->_data[80];
  if ( ((CCBLineupWindow *)&this->_data[80])->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 94;
    a2[2] = 69;
    a2[3] = 126;
    ((void (*)(gbRefObject **, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(**v15)[3].RefCount)(
      *v15,
      274,
      a2,
      this,
      aUiCombatContro_24,
      0);
    sub_440CE0(*v15, aUiCombatContro_27, 0);
    (*(void (**)(gbRefObject **, int))(**v15)->_pad_0000)(*v15, 1);
  }
  v16 = (gbRefObject ***)&this->_data[84];
  if ( ((CCBLineupWindow *)&this->_data[84])->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 132;
    a2[2] = 69;
    a2[3] = 164;
    ((void (*)(gbRefObject **, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(**v16)[3].RefCount)(
      *v16,
      275,
      a2,
      this,
      aUiCombatContro_25,
      0);
    sub_440CE0(*v16, aUiCombatContro_28, 0);
    (*(void (**)(gbRefObject **, int))(**v16)->_pad_0000)(*v16, 1);
  }
  v17 = (char *)&this->_data[100];
  ((CCBLineupWindow *)&this->_data[100])->Update();
  *a2 = 68;
  a2[2] = 160;
  a2[1] = 170;
  a2[3] = 196;
  (*(void (**)(_DWORD, int, _DWORD *, CCBMagicWindow *, char *, int, _DWORD))(**(_DWORD **)v17 + 28))(
    *(_DWORD *)v17,
    282,
    a2,
    this,
    aUiCombatContro_32,
    1,
    0);
  (***(void (****)(_DWORD, int))v17)(*(_DWORD *)v17, 1);
  return 1;
}

// 0x0051C110
int CCBMagicWindow::Update()
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

  result = ((UIListBox *)this)->SetScrollPos();
  v3 = *(_DWORD *)&this->_data[72];
  if ( v3 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)&this->_data[72] = 0;
  }
  v4 = *(_DWORD *)&this->_data[76];
  if ( v4 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *(_DWORD *)&this->_data[76] = 0;
  }
  v5 = *(_DWORD *)&this->_data[80];
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)&this->_data[80] = 0;
  }
  v6 = *(_DWORD *)&this->_data[84];
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)&this->_data[84] = 0;
  }
  v7 = *(_DWORD *)&this->_data[88];
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)&this->_data[88] = 0;
  }
  v8 = *(_DWORD *)&this->_data[92];
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)&this->_data[92] = 0;
  }
  v9 = *(_DWORD *)&this->_data[96];
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)&this->_data[96] = 0;
  }
  v10 = *(_DWORD *)&this->_data[100];
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)&this->_data[100] = 0;
  }
  return result;
}

// 0x0051C1B0
BOOL CCBMagicWindow::SetActivePage(int a2, int a3)
{
  if ( *(_DWORD *)&this->_data[56] == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_data[32] + 1160) + 8))->SetParam(272, -1);
  }
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x0051C210
_DWORD * CCBMagicWindow::GetActivePage()
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)this->_data = &off_57058C;
  ((CCBSkillWindow *)this)->Reset();
  return this->_data;
}
