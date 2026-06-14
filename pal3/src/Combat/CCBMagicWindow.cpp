#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBMagicWindow.h"

// Forward declarations for unnamed functions
void sub_43FDB0(float *_this, int a2); // from annotations
int sub_43FEC0(void *a2); // from annotations
int sub_4431B0(...);
void * sub_445FE0(void *a2); // from annotations

// Unnamed globals (extern)
extern int unk_5DF59C;
extern int unk_5DF6AC;
extern int unk_5DF6D0;
extern int unk_5DF6F4;

// 0x0051B860
int CCBMagicWindow::OnMessage(int nVal, int nVal2, int nVal3)
{
  CScreenMode *Instance; // eax

  if ( nVal == 1001 )
  {
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa001", 1);
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(nVal2, nVal3);
  }
  return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
}

// 0x0051B9F0
CCBMagicWindow::CCBMagicWindow(int nVal, int nVal2, int *p_DWORD)
{
  int v4; // eax
  int *v5; // eax
  int v6; // [esp-0x14] [ebp-0x40]
  int v7; // [esp-0x10] [ebp-0x3C]
  int v8; // [esp-0xC] [ebp-0x38]
  int v9; // [esp-0x8] [ebp-0x34]
  int v10[4]; // [esp+0xC] [ebp-0x20] BYREF
  _BYTE a2[16]; // [esp+0x1C] [ebp-0x10] BYREF

  v4 = g_nUnkTable_24C[nVal];
  v6 = v4 + 9;
  v7 = g_nUnkTable_268[nVal] + 232;
  v8 = v4 + 49;
  v9 = g_nUnkTable_268[nVal] + 270;
  v5 = (int *)sub_445FE0(a2);
  if ( ((CCBLineupWindow *)*v5)->SetFaceLineup(v5[1], v5[2], v5[3], v6, v7, v8, v9, v10) )
    *p_DWORD = (v10[3] - v10[1]) * (v10[2] - v10[0]);
  else
    *p_DWORD = 0;
}

// 0x0051BAB0
void CCBMagicWindow::_CCBMagicWindow(int nVal)
{
  int v2; // edi
  int i; // esi
  char v5; // al
  int p_DWORD; // [esp+0x10] [ebp-0x4] BYREF

  v2 = 0;
  p_DWORD = 0;
  for ( i = 1; i < 7; ++i )
  {
    if ( v5 )
    {
      if ( p_DWORD > v2 )
        v2 = p_DWORD;
    }
  }
}

// 0x0051BB00
void CCBMagicWindow::Reset(int nVal, int nVal2)
{
  UIStatic **p_m_pBack; // eax
  int v4; // esi

  p_m_pBack = &this->m_pBack;
  v4 = 5;
  do
  {
    if ( *p_m_pBack == (UIStatic *)nVal2 )
      *p_m_pBack = (UIStatic *)*((_DWORD *)&this->m_pBack + nVal);
    ++p_m_pBack;
    --v4;
  }
  while ( v4 );
  *((_DWORD *)&this->m_pBack + nVal) = nVal2;
  ((RoleCameraCtrl *)this)->InitViewSlots();
}

// 0x0051BB40
bool CCBMagicWindow::Create(int rc)
{
  this->m_pButtonEarth = (UIPushButton *)rc;
  return rc;
}

// 0x0051BB90
UIListBox * CCBMagicWindow::ForbidPage()
{

  return (UIListBox *)this;
}

// 0x0051BC50
int CCBMagicWindow::ClearMagicData()
{
  this->m_pBack = 0;
  this->m_pMagicList[0] = 0;
  this->m_pMagicList[1] = 0;
  this->m_pMagicList[2] = 0;
  this->m_pMagicList[3] = 0;
  this->m_pMagicList[4] = 0;
  this->m_pMagicList[5] = 0;
  this->m_pButtonWater = 0;
  return 0;
}

// 0x0051BC70
bool CCBMagicWindow::CreateButton(int *ppButton, int id)
{
  UIStatic **p_m_pBack; // edi
  CCBLineupWindow *v5; // ecx
  CCBLineupWindow *v6; // ecx
  char v7; // al
  UIScene **v8; // edi
  CCBLineupWindow *v9; // ecx
  void *v10; // eax
  UIScene *v11; // eax
  UIScene **v12; // edi
  CCBLineupWindow *v13; // ecx
  void *v14; // eax
  UIScene *v15; // eax
  UIScene **v16; // edi
  CCBLineupWindow *v17; // ecx
  void *v18; // eax
  UIScene *v19; // eax
  UIListBox **m_pMagicList; // edi
  CCBLineupWindow *v21; // ecx
  UIStatic **v22; // edi
  CCBLineupWindow *v23; // ecx
  UIStatic **v24; // edi
  CCBLineupWindow *v25; // ecx
  UIPushButton **p_m_pButtonWater; // edi
  _BYTE a2[16]; // [esp+0x3C] [ebp-0x10] BYREF

  ((PalScript *)this)->Create(1879048198, (tagRECT *)ppButton, id);
  p_m_pBack = &this->m_pBack;
  ((CCBLineupWindow *)v5)->Destroy();
  if ( v7 == 1 )
  {
    *ppButton = 0;
    ppButton[2] = 230;
    ppButton[1] = 0;
    ppButton[3] = 200;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBMagicWindow *))(*p_m_pBack)->__vftable->Create)(
// [VFTABLE]   *p_m_pBack,
// [VFTABLE]   272,
// [VFTABLE]   ppButton,
// [VFTABLE]   this);
    ((UIStatic *)*p_m_pBack)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))(*p_m_pBack)->__vftable->ShowWindow)(*p_m_pBack, 1);
  }
  v8 = (UIScene **)&this->m_pMagicList[3];
  if ( ((CCBLineupWindow *)v6)->Render((int *)&this->m_pMagicList[3]) == 1 )
  {
    *ppButton = 27;
    ppButton[1] = 57;
    ppButton[2] = 211;
    ppButton[3] = 95;
// [VFTABLE] ((void ( *)(UIScene *, int, int *, CCBMagicWindow *))(*v8)->__vftable->Create)(
// [VFTABLE]   *v8,
// [VFTABLE]   g_nPropIDs_241[8],
// [VFTABLE]   ppButton,
// [VFTABLE]   this);
    v10 = sub_445FE0(a2);
    sub_43FEC0(v10);
    ((UIScene *)*v8)->GetChildCount();
    ((UIScene *)*v8)->GetChildAt();
    sub_43FDB0((float *)*v8, 48);
// [VFTABLE] ((UIWnd *)&(*v8)->__vftable)->GetHeight(23);
// [VFTABLE] ((UIWnd *)&(*v8)->__vftable)->GetWidth(11);
// [VFTABLE] ((UIWnd *)&(*v8)->__vftable)->GetPosition(5);
    ((UIScene *)*v8)->SetTextParam();
    v11 = *v8;
    v11->m_pTexture = (gbTexture *)10;
    *(_DWORD *)&v11->m_bOverlayRender = 9;
    ((UIScrollBar *)*v8)->SetRange(100.0);
    ((UIProgressBar *)*v8)->FindChildByName(100.0);
    (*v8)->m_nRectY = 1077936128;
// [VFTABLE] ((void ( *)(UIScene *, int))(*v8)->__vftable->ShowWindow)(*v8, 1);
  }
  v12 = (UIScene **)&this->m_pMagicList[4];
  if ( ((CCBLineupWindow *)v9)->Render((int *)&this->m_pMagicList[4]) == 1 )
  {
    *ppButton = 27;
    ppButton[1] = 94;
    ppButton[2] = 211;
    ppButton[3] = 132;
// [VFTABLE] ((void ( *)(UIScene *, int, int *, CCBMagicWindow *))(*v12)->__vftable->Create)(
// [VFTABLE]   *v12,
// [VFTABLE]   g_nPropIDs_241[9],
// [VFTABLE]   ppButton,
// [VFTABLE]   this);
    v14 = sub_445FE0(a2);
    sub_43FEC0(v14);
    ((UIScene *)*v12)->GetChildCount();
    ((UIScene *)*v12)->GetChildAt();
    sub_43FDB0((float *)*v12, 48);
// [VFTABLE] ((UIWnd *)&(*v12)->__vftable)->GetHeight(23);
// [VFTABLE] ((UIWnd *)&(*v12)->__vftable)->GetWidth(11);
// [VFTABLE] ((UIWnd *)&(*v12)->__vftable)->GetPosition(5);
    ((UIScene *)*v12)->SetTextParam();
    v15 = *v12;
    v15->m_pTexture = (gbTexture *)10;
    *(_DWORD *)&v15->m_bOverlayRender = 9;
    ((UIScrollBar *)*v12)->SetRange(100.0);
    ((UIProgressBar *)*v12)->FindChildByName(100.0);
    (*v12)->m_nRectY = 1077936128;
// [VFTABLE] ((void ( *)(UIScene *, int))(*v12)->__vftable->ShowWindow)(*v12, 1);
  }
  v16 = (UIScene **)&this->m_pMagicList[5];
  if ( ((CCBLineupWindow *)v13)->Render((int *)&this->m_pMagicList[5]) == 1 )
  {
    *ppButton = 27;
    ppButton[1] = 132;
    ppButton[2] = 211;
    ppButton[3] = 170;
// [VFTABLE] ((void ( *)(UIScene *, int, int *, CCBMagicWindow *))(*v16)->__vftable->Create)(
// [VFTABLE]   *v16,
// [VFTABLE]   g_nPropIDs_241[10],
// [VFTABLE]   ppButton,
// [VFTABLE]   this);
    v18 = sub_445FE0(a2);
    sub_43FEC0(v18);
    ((UIScene *)*v16)->GetChildCount();
    ((UIScene *)*v16)->GetChildAt();
    sub_43FDB0((float *)*v16, 48);
// [VFTABLE] ((UIWnd *)&(*v16)->__vftable)->GetHeight(23);
// [VFTABLE] ((UIWnd *)&(*v16)->__vftable)->GetWidth(11);
// [VFTABLE] ((UIWnd *)&(*v16)->__vftable)->GetPosition(5);
    ((UIScene *)*v16)->SetTextParam();
    v19 = *v16;
    v19->m_pTexture = (gbTexture *)10;
    *(_DWORD *)&v19->m_bOverlayRender = 9;
    ((UIScrollBar *)*v16)->SetRange(100.0);
    ((UIProgressBar *)*v16)->FindChildByName(100.0);
    (*v16)->m_nRectY = 1077936128;
// [VFTABLE] ((void ( *)(UIScene *, int))(*v16)->__vftable->ShowWindow)(*v16, 1);
  }
  m_pMagicList = this->m_pMagicList;
  if ( ((CCBLineupWindow *)v17)->OnMessage((int *)this->m_pMagicList) == 1 )
  {
    *ppButton = 37;
    ppButton[1] = 57;
    ppButton[2] = 69;
    ppButton[3] = 89;
// [VFTABLE] ((void ( *)(UIListBox *, int, int *, CCBMagicWindow *, void *, _DWORD))(*m_pMagicList)->__vftable[1].ShowWindow)(
// [VFTABLE]   *m_pMagicList,
// [VFTABLE]   g_nPropIDs_241[5],
// [VFTABLE]   ppButton,
// [VFTABLE]   this,
// [VFTABLE]   &unk_5DF6F4,
// [VFTABLE]   0);
    ((UIStatic *)*m_pMagicList)->SetText();
// [VFTABLE] ((void ( *)(UIListBox *, int))(*m_pMagicList)->__vftable->ShowWindow)(*m_pMagicList, 1);
  }
  v22 = (UIStatic **)&this->m_pMagicList[1];
  if ( ((CCBLineupWindow *)v21)->OnMessage((int *)&this->m_pMagicList[1]) == 1 )
  {
    *ppButton = 37;
    ppButton[1] = 94;
    ppButton[2] = 69;
    ppButton[3] = 126;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBMagicWindow *, void *, _DWORD))(*v22)->__vftable[1].ShowWindow)(
// [VFTABLE]   *v22,
// [VFTABLE]   g_nPropIDs_241[6],
// [VFTABLE]   ppButton,
// [VFTABLE]   this,
// [VFTABLE]   &unk_5DF6D0,
// [VFTABLE]   0);
    ((UIStatic *)*v22)->SetText();
// [VFTABLE] ((void ( *)(UIStatic *, int))(*v22)->__vftable->ShowWindow)(*v22, 1);
  }
  v24 = (UIStatic **)&this->m_pMagicList[2];
  if ( ((CCBLineupWindow *)v23)->OnMessage((int *)&this->m_pMagicList[2]) == 1 )
  {
    *ppButton = 37;
    ppButton[1] = 132;
    ppButton[2] = 69;
    ppButton[3] = 164;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBMagicWindow *, void *, _DWORD))(*v24)->__vftable[1].ShowWindow)(
// [VFTABLE]   *v24,
// [VFTABLE]   g_nPropIDs_241[7],
// [VFTABLE]   ppButton,
// [VFTABLE]   this,
// [VFTABLE]   &unk_5DF6AC,
// [VFTABLE]   0);
    ((UIStatic *)*v24)->SetText();
// [VFTABLE] ((void ( *)(UIStatic *, int))(*v24)->__vftable->ShowWindow)(*v24, 1);
  }
  p_m_pButtonWater = &this->m_pButtonWater;
  ((CCBLineupWindow *)v25)->Update((int *)&this->m_pButtonWater);
  *ppButton = 68;
  ppButton[2] = 160;
  ppButton[1] = 170;
  ppButton[3] = 196;
// [VFTABLE] ((void ( *)(UIPushButton *, int, int *, CCBMagicWindow *, void *, int, _DWORD))(*p_m_pButtonWater)->__vftable[1].ShowWindow)(
// [VFTABLE]   *p_m_pButtonWater,
// [VFTABLE]   282,
// [VFTABLE]   ppButton,
// [VFTABLE]   this,
// [VFTABLE]   &unk_5DF59C,
// [VFTABLE]   1,
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIPushButton *, int))(*p_m_pButtonWater)->__vftable->ShowWindow)(*p_m_pButtonWater, 1);
  return 1;
}

// 0x0051C110
void CCBMagicWindow::Destroy()
{
  UIStatic *m_pBack; // ecx
  UIListBox *v3; // ecx
  UIListBox *v4; // ecx
  UIListBox *v5; // ecx
  UIListBox *v6; // ecx
  UIListBox *v7; // ecx
  UIListBox *v8; // ecx
  UIPushButton *m_pButtonWater; // ecx
  UIListBox *v10; // [esp+0x0] [ebp-0x8]
  int v11; // [esp+0x4] [ebp-0x4]

  ((CCBRoleState *)this)->Destroy(v10, v11);
  m_pBack = this->m_pBack;
  if ( m_pBack )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pBack->__vftable->sub_4431B0)(m_pBack, 1);
    this->m_pBack = 0;
  }
  v3 = this->m_pMagicList[0];
  if ( v3 )
  {
// [VFTABLE] ((void ( *)(UIListBox *, int))v3->__vftable->sub_4431B0)(v3, 1);
    this->m_pMagicList[0] = 0;
  }
  v4 = this->m_pMagicList[1];
  if ( v4 )
  {
// [VFTABLE] ((void ( *)(UIListBox *, int))v4->__vftable->sub_4431B0)(v4, 1);
    this->m_pMagicList[1] = 0;
  }
  v5 = this->m_pMagicList[2];
  if ( v5 )
  {
// [VFTABLE] ((void ( *)(UIListBox *, int))v5->__vftable->sub_4431B0)(v5, 1);
    this->m_pMagicList[2] = 0;
  }
  v6 = this->m_pMagicList[3];
  if ( v6 )
  {
// [VFTABLE] ((void ( *)(UIListBox *, int))v6->__vftable->sub_4431B0)(v6, 1);
    this->m_pMagicList[3] = 0;
  }
  v7 = this->m_pMagicList[4];
  if ( v7 )
  {
// [VFTABLE] ((void ( *)(UIListBox *, int))v7->__vftable->sub_4431B0)(v7, 1);
    this->m_pMagicList[4] = 0;
  }
  v8 = this->m_pMagicList[5];
  if ( v8 )
  {
// [VFTABLE] ((void ( *)(UIListBox *, int))v8->__vftable->sub_4431B0)(v8, 1);
    this->m_pMagicList[5] = 0;
  }
  m_pButtonWater = this->m_pButtonWater;
  if ( m_pButtonWater )
  {
// [VFTABLE] ((void ( *)(UIPushButton *, int))m_pButtonWater->__vftable->sub_4431B0)(m_pButtonWater, 1);
    this->m_pButtonWater = 0;
  }
}

// 0x0051C1B0
BOOL CCBMagicWindow::SetActivePage(int n, int nVal)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(272, -1);
  }
  return ((UIListBox *)this)->Update(n, nVal);
}

// 0x0051C210
UIListBox * CCBMagicWindow::GetActivePage()
{
  ((CCBSkillWindow *)this)->Reset();
  return (UIListBox *)this;
}
