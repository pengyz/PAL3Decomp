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
  int *p_d048; // eax
  int v4; // esi

  p_d048 = (int *)&this->_d048;
  v4 = 5;
  do
  {
    if ( *p_d048 == a3 )
      * p_d048 = (*)*(_DWORD *)&this->_pad_03C[4 * a2 + 12];
    ++p_d048;
    --v4;
  }
  while ( v4 );
  *(_DWORD *)&this->_pad_03C[4 * a2 + 12] = a3;
  sub_51BB50((char *)this);
  return -1;
}

// 0x0051BB40
int CCBMagicWindow::Create(int a2)
{
  this->_d074 = a2;
  return a2;
}

// 0x0051BB90
_DWORD * CCBMagicWindow::ForbidPage()
{
  ((UIListBox *)this)->UIListBox();
  this->_p000 = &off_570570;
  this->OnMessage();
  return &this->_p000;
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
  this->_d048 = 0;
  this->_d04C = 0;
  this->_d050 = 0;
  this->_d054 = 0;
  this->_d058 = 0;
  this->_d05C = 0;
  this->_d060 = 0;
  this->_d064 = 0;
  return 0;
}

// 0x0051BC70
char CCBMagicWindow::CreateButton(_DWORD *a2, int a3)
{
  int *p_d048; // edi
  int *p_d058; // edi
  _DWORD *v6; // eax
  UIWnd *v7; // eax
  int *p_d05C; // edi
  _DWORD *v9; // eax
  UIWnd *v10; // eax
  int *p_d060; // edi
  _DWORD *v12; // eax
  UIWnd *v13; // eax
  int *p_d04C; // edi
  int *p_d050; // edi
  int *p_d054; // edi
  int *p_d064; // edi
  _DWORD a2a[4]; // [esp+3Ch] [ebp-10h] BYREF

  ((UIWnd *)this)->Create(1879048198, a2, a3);
  p_d048 = (int *)&this->_d048;
  if ( ((CCBLineupWindow *)&this->_d048)->Destroy() == 1 )
  {
    *a2 = 0;
    a2[2] = 230;
    a2[1] = 0;
    a2[3] = 200;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)*p_d048 + 16))(*p_d048, 272, a2, this);
    ((UIWnd *)*p_d048)->CreateFromTemplate(aUiCombatContro_22, 0);
    (**(void (***)(int, int))*p_d048)(*p_d048, 1);
  }
  p_d058 = (int *)&this->_d058;
  if ( ((CCBLineupWindow *)&this->_d058)->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 57;
    a2[2] = 211;
    a2[3] = 95;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)*p_d058 + 16))(*p_d058, 276, a2, this);
    v6 = ((UIWnd *)*p_d058)->SetRect(a2a);
    ((UIWnd *)*p_d058)->AddChild(v6);
    ((UIWnd *)*p_d058)->GetChildCount(aUiCombatContro_29, 0);
    ((UIWnd *)*p_d058)->GetChildAt(aUiCombatContro_30, 0);
    ((UIWnd *)*p_d058)->SetFrameRate(48);
    ((UIWnd *)*p_d058)->GetHeight(23);
    ((UIWnd *)*p_d058)->GetWidth(11);
    ((UIWnd *)*p_d058)->GetPosition(5);
    sub_43FBC0((gbRefObject **)*p_d058, aUiCombatContro_31, 0);
    v7 = (UIWnd *)*p_d058;
    v7[2].m_id = 10;
    v7[2].m_rect.left = 9;
    ((UIWnd *)*p_d058)->FindChild(100.0);
    ((UIWnd *)*p_d058)->FindChildByName(100.0);
    *(_DWORD *)(*p_d058 + 112) = 1077936128;
    (**(void (***)(int, int))*p_d058)(*p_d058, 1);
  }
  p_d05C = (int *)&this->_d05C;
  if ( ((CCBLineupWindow *)&this->_d05C)->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 94;
    a2[2] = 211;
    a2[3] = 132;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)*p_d05C + 16))(*p_d05C, 277, a2, this);
    v9 = ((UIWnd *)*p_d05C)->SetRect(a2a);
    ((UIWnd *)*p_d05C)->AddChild(v9);
    ((UIWnd *)*p_d05C)->GetChildCount(aUiCombatContro_29, 0);
    ((UIWnd *)*p_d05C)->GetChildAt(aUiCombatContro_30, 0);
    ((UIWnd *)*p_d05C)->SetFrameRate(48);
    ((UIWnd *)*p_d05C)->GetHeight(23);
    ((UIWnd *)*p_d05C)->GetWidth(11);
    ((UIWnd *)*p_d05C)->GetPosition(5);
    sub_43FBC0((gbRefObject **)*p_d05C, aUiCombatContro_31, 0);
    v10 = (UIWnd *)*p_d05C;
    v10[2].m_id = 10;
    v10[2].m_rect.left = 9;
    ((UIWnd *)*p_d05C)->FindChild(100.0);
    ((UIWnd *)*p_d05C)->FindChildByName(100.0);
    *(_DWORD *)(*p_d05C + 112) = 1077936128;
    (**(void (***)(int, int))*p_d05C)(*p_d05C, 1);
  }
  p_d060 = (int *)&this->_d060;
  if ( ((CCBLineupWindow *)&this->_d060)->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 132;
    a2[2] = 211;
    a2[3] = 170;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)*p_d060 + 16))(*p_d060, 278, a2, this);
    v12 = ((UIWnd *)*p_d060)->SetRect(a2a);
    ((UIWnd *)*p_d060)->AddChild(v12);
    ((UIWnd *)*p_d060)->GetChildCount(aUiCombatContro_29, 0);
    ((UIWnd *)*p_d060)->GetChildAt(aUiCombatContro_30, 0);
    ((UIWnd *)*p_d060)->SetFrameRate(48);
    ((UIWnd *)*p_d060)->GetHeight(23);
    ((UIWnd *)*p_d060)->GetWidth(11);
    ((UIWnd *)*p_d060)->GetPosition(5);
    sub_43FBC0((gbRefObject **)*p_d060, aUiCombatContro_31, 0);
    v13 = (UIWnd *)*p_d060;
    v13[2].m_id = 10;
    v13[2].m_rect.left = 9;
    ((UIWnd *)*p_d060)->FindChild(100.0);
    ((UIWnd *)*p_d060)->FindChildByName(100.0);
    *(_DWORD *)(*p_d060 + 112) = 1077936128;
    (**(void (***)(int, int))*p_d060)(*p_d060, 1);
  }
  p_d04C = (int *)&this->_d04C;
  if ( ((CCBLineupWindow *)&this->_d04C)->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 57;
    a2[2] = 69;
    a2[3] = 89;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(*(_DWORD *)*p_d04C + 28))(
      *p_d04C,
      273,
      a2,
      this,
      aUiCombatContro_23,
      0);
    sub_440CE0((gbRefObject **)*p_d04C, aUiCombatContro_26, 0);
    (**(void (***)(int, int))*p_d04C)(*p_d04C, 1);
  }
  p_d050 = (int *)&this->_d050;
  if ( ((CCBLineupWindow *)&this->_d050)->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 94;
    a2[2] = 69;
    a2[3] = 126;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(*(_DWORD *)*p_d050 + 28))(
      *p_d050,
      274,
      a2,
      this,
      aUiCombatContro_24,
      0);
    sub_440CE0((gbRefObject **)*p_d050, aUiCombatContro_27, 0);
    (**(void (***)(int, int))*p_d050)(*p_d050, 1);
  }
  p_d054 = (int *)&this->_d054;
  if ( ((CCBLineupWindow *)&this->_d054)->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 132;
    a2[2] = 69;
    a2[3] = 164;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(*(_DWORD *)*p_d054 + 28))(
      *p_d054,
      275,
      a2,
      this,
      aUiCombatContro_25,
      0);
    sub_440CE0((gbRefObject **)*p_d054, aUiCombatContro_28, 0);
    (**(void (***)(int, int))*p_d054)(*p_d054, 1);
  }
  p_d064 = (int *)&this->_d064;
  ((CCBLineupWindow *)&this->_d064)->Update();
  *a2 = 68;
  a2[2] = 160;
  a2[1] = 170;
  a2[3] = 196;
  (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, int, _DWORD))(*(_DWORD *)*p_d064 + 28))(
    *p_d064,
    282,
    a2,
    this,
    aUiCombatContro_32,
    1,
    0);
  (**(void (***)(int, int))*p_d064)(*p_d064, 1);
  return 1;
}

// 0x0051C110
int CCBMagicWindow::Update()
{
  int result; // eax
  int d048; // ecx
  int d04C; // ecx
  int d050; // ecx
  int d054; // ecx
  int d058; // ecx
  int d05C; // ecx
  int d060; // ecx
  int d064; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  d048 = this->_d048;
  if ( d048 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d048 + 20))(d048, 1);
    this->_d048 = 0;
  }
  d04C = this->_d04C;
  if ( d04C )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d04C + 20))(d04C, 1);
    this->_d04C = 0;
  }
  d050 = this->_d050;
  if ( d050 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d050 + 20))(d050, 1);
    this->_d050 = 0;
  }
  d054 = this->_d054;
  if ( d054 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d054 + 20))(d054, 1);
    this->_d054 = 0;
  }
  d058 = this->_d058;
  if ( d058 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d058 + 20))(d058, 1);
    this->_d058 = 0;
  }
  d05C = this->_d05C;
  if ( d05C )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d05C + 20))(d05C, 1);
    this->_d05C = 0;
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
  return result;
}

// 0x0051C1B0
BOOL CCBMagicWindow::SetActivePage(int a2, int a3)
{
  if ( this->_d038 == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(272, -1);
  }
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x0051C210
_DWORD * CCBMagicWindow::GetActivePage()
{
  ((UIListBox *)this)->UIListBox();
  this->_p000 = &off_57058C;
  ((CCBSkillWindow *)this)->Reset();
  return &this->_p000;
}
