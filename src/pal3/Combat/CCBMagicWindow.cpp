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
CCBMagicWindow::CCBMagicWindow(CCBMagicWindow **this, int a2, int a3, _DWORD *a4)
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
  v5 = (int *)UIWnd::SetRect(*(this + a3 + 24), v12);
  if ( CCBLineupWindow::SetFaceLineup(*v5, v5[1], v5[2], v5[3], v7, v8, v9, v10, v11) )
  {
    *a4 = (v11[3] - v11[1]) * (v11[2] - v11[0]);
    return 1;
  }
  else
  {
    *a4 = 0;
    return 0;
  }
}

// 0x0051BAB0
CCBMagicWindow::~CCBMagicWindow(CCBMagicWindow **this, int a2)
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
  return v4;
}

// 0x0051BB00
int CCBMagicWindow::Reset(int a2, int a3)
{
  PtrArray *p_m_childs; // eax
  int v4; // esi

  p_m_childs = (PtrArray *)&this->m_childs;
  v4 = 5;
  do
  {
    if ( p_m_childs->m_pData == (void *)a3 )
      p_m_childs->m_pData = (void *)*((_DWORD *)&this->m_childs.m_pData + a2);
    p_m_childs = (PtrArray *)((char *)p_m_childs + 4);
    --v4;
  }
  while ( v4 );
  *((_DWORD *)&this->m_childs.m_pData + a2) = a3;
  sub_51BB50((char *)this);
  return -1;
}

// 0x0051BB40
int CCBMagicWindow::Create(int a2)
{
  this->m_pMagicList[1] = (UIListBox *)a2;
  return a2;
}

// 0x0051BB90
_DWORD * CCBMagicWindow::ForbidPage()
{
  (UIListBox *->UIListBox()this);
  this->m_fontcolor.ColorQuadFmt = (int)&off_570570;
  this->OnMessage();
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0051BBE0
UIWnd * CCBMagicWindow::Destroy(CCBMagicWindow *Block, char a2)
{
  UIWnd::~UIWnd((UIWnd *)Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051BC50
int CCBMagicWindow::OnMessage()
{
  this->m_childs.m_pData = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_nMaxSize = 0;
  this->m_childs.m_nGrowBy = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_benable = 0;
  this->m_bfocus = 0;
  return 0;
}

// 0x0051BC70
char CCBMagicWindow::CreateButton(_DWORD *a2, int a3)
{
  UIWnd ***p_m_childs; // edi
  int *p_m_bcreateok; // edi
  _DWORD *v6; // eax
  UIWnd *v7; // eax
  int *p_m_bvisible; // edi
  _DWORD *v9; // eax
  UIWnd *v10; // eax
  int *p_m_benable; // edi
  _DWORD *v12; // eax
  UIWnd *v13; // eax
  int *p_m_nSize; // edi
  int *p_m_nMaxSize; // edi
  int *p_m_nGrowBy; // edi
  int *p_m_bfocus; // edi
  _DWORD a2a[4]; // [esp+3Ch] [ebp-10h] BYREF

  this->Create(1879048198, a2, a3);
  p_m_childs = (UIWnd ***)&this->m_childs;
  if ( &this->m_childs.m_pData->Destroy() == 1 )
  {
    *a2 = 0;
    a2[2] = 230;
    a2[1] = 0;
    a2[3] = 200;
    ((void (*)(UIWnd **, int, _DWORD *, CCBMagicWindow *))(**p_m_childs)->m_fontcolor.Alpha)(
      *p_m_childs,
      272,
      a2,
      this);
    UIWnd::CreateFromTemplate(*p_m_childs, aUiCombatContro_22, 0);
    ((void (*)(UIWnd **, int))(**p_m_childs)->m_fontcolor.ColorQuadFmt)(*p_m_childs, 1);
  }
  p_m_bcreateok = (int *)&this->m_bcreateok;
  if ( &this->m_bcreateok->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 57;
    a2[2] = 211;
    a2[3] = 95;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)*p_m_bcreateok + 16))(
      *p_m_bcreateok,
      276,
      a2,
      this);
    v6 = (UIWnd *->SetRect()*p_m_bcreateok, a2a);
    (UIWnd *->AddChild()*p_m_bcreateok, v6);
    (UIWnd **->GetChildCount()*p_m_bcreateok, aUiCombatContro_29, 0);
    (UIWnd **->GetChildAt()*p_m_bcreateok, aUiCombatContro_30, 0);
    (UIWnd *->SetFrameRate()*p_m_bcreateok, 48);
    (UIWnd *->GetHeight()*p_m_bcreateok, 23);
    (UIWnd *->GetWidth()*p_m_bcreateok, 11);
    (UIWnd *->GetPosition()*p_m_bcreateok, 5);
    sub_43FBC0((gbRefObject **)*p_m_bcreateok, aUiCombatContro_31, 0);
    v7 = (UIWnd *)*p_m_bcreateok;
    v7[1].m_bvisible = 10;
    v7[1].m_benable = 9;
    UIWnd::FindChild(*p_m_bcreateok, 100.0);
    UIWnd::FindChildByName(*p_m_bcreateok, 100.0);
    *(_DWORD *)(*p_m_bcreateok + 112) = 1077936128;
    (**(void (***)(int, int))*p_m_bcreateok)(*p_m_bcreateok, 1);
  }
  p_m_bvisible = (int *)&this->m_bvisible;
  if ( &this->m_bvisible->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 94;
    a2[2] = 211;
    a2[3] = 132;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)*p_m_bvisible + 16))(
      *p_m_bvisible,
      277,
      a2,
      this);
    v9 = (UIWnd *->SetRect()*p_m_bvisible, a2a);
    (UIWnd *->AddChild()*p_m_bvisible, v9);
    (UIWnd **->GetChildCount()*p_m_bvisible, aUiCombatContro_29, 0);
    (UIWnd **->GetChildAt()*p_m_bvisible, aUiCombatContro_30, 0);
    (UIWnd *->SetFrameRate()*p_m_bvisible, 48);
    (UIWnd *->GetHeight()*p_m_bvisible, 23);
    (UIWnd *->GetWidth()*p_m_bvisible, 11);
    (UIWnd *->GetPosition()*p_m_bvisible, 5);
    sub_43FBC0((gbRefObject **)*p_m_bvisible, aUiCombatContro_31, 0);
    v10 = (UIWnd *)*p_m_bvisible;
    v10[1].m_bvisible = 10;
    v10[1].m_benable = 9;
    UIWnd::FindChild(*p_m_bvisible, 100.0);
    UIWnd::FindChildByName(*p_m_bvisible, 100.0);
    *(_DWORD *)(*p_m_bvisible + 112) = 1077936128;
    (**(void (***)(int, int))*p_m_bvisible)(*p_m_bvisible, 1);
  }
  p_m_benable = (int *)&this->m_benable;
  if ( &this->m_benable->Render() == 1 )
  {
    *a2 = 27;
    a2[1] = 132;
    a2[2] = 211;
    a2[3] = 170;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *))(*(_DWORD *)*p_m_benable + 16))(
      *p_m_benable,
      278,
      a2,
      this);
    v12 = (UIWnd *->SetRect()*p_m_benable, a2a);
    (UIWnd *->AddChild()*p_m_benable, v12);
    (UIWnd **->GetChildCount()*p_m_benable, aUiCombatContro_29, 0);
    (UIWnd **->GetChildAt()*p_m_benable, aUiCombatContro_30, 0);
    (UIWnd *->SetFrameRate()*p_m_benable, 48);
    (UIWnd *->GetHeight()*p_m_benable, 23);
    (UIWnd *->GetWidth()*p_m_benable, 11);
    (UIWnd *->GetPosition()*p_m_benable, 5);
    sub_43FBC0((gbRefObject **)*p_m_benable, aUiCombatContro_31, 0);
    v13 = (UIWnd *)*p_m_benable;
    v13[1].m_bvisible = 10;
    v13[1].m_benable = 9;
    UIWnd::FindChild(*p_m_benable, 100.0);
    UIWnd::FindChildByName(*p_m_benable, 100.0);
    *(_DWORD *)(*p_m_benable + 112) = 1077936128;
    (**(void (***)(int, int))*p_m_benable)(*p_m_benable, 1);
  }
  p_m_nSize = (int *)&this->m_childs.m_nSize;
  if ( &this->m_childs.m_nSize->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 57;
    a2[2] = 69;
    a2[3] = 89;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(*(_DWORD *)*p_m_nSize + 28))(
      *p_m_nSize,
      273,
      a2,
      this,
      aUiCombatContro_23,
      0);
    sub_440CE0((gbRefObject **)*p_m_nSize, aUiCombatContro_26, 0);
    (**(void (***)(int, int))*p_m_nSize)(*p_m_nSize, 1);
  }
  p_m_nMaxSize = (int *)&this->m_childs.m_nMaxSize;
  if ( &this->m_childs.m_nMaxSize->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 94;
    a2[2] = 69;
    a2[3] = 126;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(*(_DWORD *)*p_m_nMaxSize + 28))(
      *p_m_nMaxSize,
      274,
      a2,
      this,
      aUiCombatContro_24,
      0);
    sub_440CE0((gbRefObject **)*p_m_nMaxSize, aUiCombatContro_27, 0);
    (**(void (***)(int, int))*p_m_nMaxSize)(*p_m_nMaxSize, 1);
  }
  p_m_nGrowBy = (int *)&this->m_childs.m_nGrowBy;
  if ( &this->m_childs.m_nGrowBy->OnMessage() == 1 )
  {
    *a2 = 37;
    a2[1] = 132;
    a2[2] = 69;
    a2[3] = 164;
    (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, _DWORD))(*(_DWORD *)*p_m_nGrowBy + 28))(
      *p_m_nGrowBy,
      275,
      a2,
      this,
      aUiCombatContro_25,
      0);
    sub_440CE0((gbRefObject **)*p_m_nGrowBy, aUiCombatContro_28, 0);
    (**(void (***)(int, int))*p_m_nGrowBy)(*p_m_nGrowBy, 1);
  }
  p_m_bfocus = (int *)&this->m_bfocus;
  &this->m_bfocus->Update();
  *a2 = 68;
  a2[2] = 160;
  a2[1] = 170;
  a2[3] = 196;
  (*(void (**)(int, int, _DWORD *, CCBMagicWindow *, char *, int, _DWORD))(*(_DWORD *)*p_m_bfocus + 28))(
    *p_m_bfocus,
    282,
    a2,
    this,
    aUiCombatContro_32,
    1,
    0);
  (**(void (***)(int, int))*p_m_bfocus)(*p_m_bfocus, 1);
  return 1;
}

// 0x0051C110
int CCBMagicWindow::Update(int _this)
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

  result = (gbRefObject **->SetScrollPos()this);
  v3 = *(_DWORD *)(this + 72);
  if ( v3 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v4 = *(_DWORD *)(this + 76);
  if ( v4 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *(_DWORD *)(this + 76) = 0;
  }
  v5 = *(_DWORD *)(this + 80);
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 80) = 0;
  }
  v6 = *(_DWORD *)(this + 84);
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 84) = 0;
  }
  v7 = *(_DWORD *)(this + 88);
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 88) = 0;
  }
  v8 = *(_DWORD *)(this + 92);
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v9 = *(_DWORD *)(this + 96);
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v10 = *(_DWORD *)(this + 100);
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  return result;
}

// 0x0051C1B0
BOOL CCBMagicWindow::SetActivePage(int a2, int a3)
{
  if ( this->m_rect.top == 1
    && (g_Input.m_DIKToKEY[1] == 1 && (g_Input.m_shiftedKeyStates[268] & 0xF) == 1 || g_Input.m_DIKToKEY[5] == 1) )
  {
    CCBUI::SetParam(*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8), 272, -1);
  }
  return this->HitTest(a2, a3);
}

// 0x0051C210
_DWORD * CCBMagicWindow::GetActivePage()
{
  (UIListBox *->UIListBox()this);
  this->m_fontcolor.ColorQuadFmt = (int)&off_57058C;
  (CCBSkillWindow *->Reset()this);
  return &this->m_fontcolor.ColorQuadFmt;
}
