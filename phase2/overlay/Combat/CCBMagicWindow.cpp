#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBLineupWindow.h"
#include "Combat/CCBSkillWindow.h"
#include "Render/CScreenMode.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleCameraCtrl.h"
#include "Scene/SceneObj.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x004B0520
void * CCBMagicWindow::_scalar_deleting_destructor_(UIWnd *Block, char pData)
{
  int v5; // [esp+0x0] [ebp-0x4]

  UITitle_JDHY__UITitle_JDHY(v5);
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x0051B860
int CCBMagicWindow::OnMessage(int nVal, int nVal2, int nVal3)
{
  CScreenMode *Instance; // eax

  if ( nVal == 1001 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa001", 1);
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(nVal2, nVal3, 0);
  }
  return this->UIWnd::OnMessage(nVal, nVal2, nVal3);
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
  if ( CCBLineupWindow::SetFaceLineup(*v5, v5[1], v5[2], v5[3], v6, v7, v8, v9, v10) )
    *p_DWORD = (v10[3] - v10[1]) * (v10[2] - v10[0]);
  else
    *p_DWORD = 0;
}

// 0x0051BAB0
void CCBMagicWindow::_todo_0051BAB0(int nVal)
{
  int v2; // edi
  int i; // esi
  char v5; // al
  int p_DWORD; // [esp+0x10] [ebp-0x4] BYREF

  v2 = 0;
  p_DWORD = 0;
  for ( i = 1; i < 7; ++i )
  {
    this->CCBMagicWindow::CCBMagicWindow(i, nVal, &p_DWORD);
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

  p_m_pBack = (UIStatic **)&this->m_pBack;
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
  (((RoleCameraCtrl *)this))->RoleCameraCtrl::InitViewSlots() /* [ROWTABLE] */;
}

// 0x0051BB40
int CCBMagicWindow::Create(int rc)
{
  int result; // eax

  result = rc;
  this->m_pButtonEarth = ((UIPushButton *)((UIPushButton *)rc));
  return result;
}

// 0x0051BB90
UIListBox * CCBMagicWindow::ForbidPage()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->CCBMagicWindow::ClearMagicData();
  return (UIListBox *)this;
}

// 0x0051BC50
int CCBMagicWindow::ClearMagicData()
{
  int result; // eax

  result = 0;
  this->m_pBack = ((UIStatic *)0);
  this->m_pMagicList[0] = 0;
  this->m_pMagicList[1] = 0;
  this->m_pMagicList[2] = 0;
  this->m_pMagicList[3] = 0;
  this->m_pMagicList[4] = 0;
  this->m_pMagicList[5] = 0;
  this->m_pButtonWater = ((UIPushButton *)0);
  return result;
}

// 0x0051BC70
bool CCBMagicWindow::CreateButton(int *ppButton, int id)
{
  UIPushButton **p_m_pBack; // edi
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
  UIPushButton **v22; // edi
  CCBLineupWindow *v23; // ecx
  UIPushButton **v24; // edi
  CCBLineupWindow *v25; // ecx
  UIPushButton **p_m_pButtonWater; // edi
  _BYTE a2[16]; // [esp+0x3C] [ebp-0x10] BYREF

  this->UIWnd::Create(1879048198, (tagRECT *)ppButton, (UIWnd *)id);
  p_m_pBack = (UIPushButton **)&this->m_pBack;
  (((CCBLineupWindow *)v5))->CCBLineupWindow::Destroy();
  if ( v7 == 1 )
  {
    *ppButton = 0;
    ppButton[2] = 230;
    ppButton[1] = 0;
    ppButton[3] = 200;
    (*(void ( **)(UIPushButton *, int, int *, CCBMagicWindow *))(*(_DWORD *)((UIWnd *)(*p_m_pBack)) + 16))(
      *p_m_pBack,
      272,
      ppButton,
      this);
    (((UIPushButton *)*p_m_pBack))->UIPushButton::CreateFromTemplate(&unk_5DF718, 0);
    (**(void ( ***)(UIPushButton *, int))((UIWnd *)(*p_m_pBack)))((UIPushButton *)(*p_m_pBack), (int)(1));
  }
  v8 = (UIScene **)&this->m_pMagicList[3];
  if ( (((CCBLineupWindow *)v6))->CCBLineupWindow::Render((int *)&this->m_pMagicList[3]) == 1 )
  {
    *ppButton = 27;
    ppButton[1] = 57;
    ppButton[2] = 211;
    ppButton[3] = 95;
    (*(void ( **)(UIScene *, int, int *, CCBMagicWindow *))(*(_DWORD *)((UIWnd *)(*v8)) + 16))(
      *v8,
      g_nPropIDs_241[8],
      ppButton,
      this);
    v10 = (void *)sub_445FE0(a2);
    sub_43FEC0(v10);
    (((UIScene *)*v8))->UIScene::GetChildCount();
    (((UIScene *)*v8))->UIScene::GetChildAt();
    sub_43FDB0((float *)*v8, 48);
    (((UIProgressBar *)*v8))->UIProgressBar::GetHeight(23);
    (((UIProgressBar *)*v8))->UIProgressBar::GetWidth(11);
    (((UIProgressBar *)*v8))->UIProgressBar::GetPosition(5);
    (((UIScene *)*v8))->UIScene::SetTextParam();
    v11 = (UIScene *)*v8;
    v11->m_pTexture = (gbTexture *)10;
    *(_DWORD *)&v11->m_bOverlayRender = 9;
    (((UIScrollBar *)*v8))->UIScrollBar::SetRange(100.0);
    (((UIProgressBar *)*v8))->UIProgressBar::FindChildByName(100.0);
    (*v8)->m_nRectY = 1077936128;
    (**(void ( ***)(UIScene *, int))((UIWnd *)(*v8)))((UIScene *)(*v8), (int)(1));
  }
  v12 = (UIScene **)&this->m_pMagicList[4];
  if ( (((CCBLineupWindow *)v9))->CCBLineupWindow::Render((int *)&this->m_pMagicList[4]) == 1 )
  {
    *ppButton = 27;
    ppButton[1] = 94;
    ppButton[2] = 211;
    ppButton[3] = 132;
    (*(void ( **)(UIScene *, int, int *, CCBMagicWindow *))(*(_DWORD *)((UIWnd *)(*v12)) + 16))(
      *v12,
      g_nPropIDs_241[9],
      ppButton,
      this);
    v14 = (void *)sub_445FE0(a2);
    sub_43FEC0(v14);
    (((UIScene *)*v12))->UIScene::GetChildCount();
    (((UIScene *)*v12))->UIScene::GetChildAt();
    sub_43FDB0((float *)*v12, 48);
    (((UIProgressBar *)*v12))->UIProgressBar::GetHeight(23);
    (((UIProgressBar *)*v12))->UIProgressBar::GetWidth(11);
    (((UIProgressBar *)*v12))->UIProgressBar::GetPosition(5);
    (((UIScene *)*v12))->UIScene::SetTextParam();
    v15 = (UIScene *)*v12;
    v15->m_pTexture = (gbTexture *)10;
    *(_DWORD *)&v15->m_bOverlayRender = 9;
    (((UIScrollBar *)*v12))->UIScrollBar::SetRange(100.0);
    (((UIProgressBar *)*v12))->UIProgressBar::FindChildByName(100.0);
    (*v12)->m_nRectY = 1077936128;
    (**(void ( ***)(UIScene *, int))((UIWnd *)(*v12)))((UIScene *)(*v12), (int)(1));
  }
  v16 = (UIScene **)&this->m_pMagicList[5];
  if ( (((CCBLineupWindow *)v13))->CCBLineupWindow::Render((int *)&this->m_pMagicList[5]) == 1 )
  {
    *ppButton = 27;
    ppButton[1] = 132;
    ppButton[2] = 211;
    ppButton[3] = 170;
    (*(void ( **)(UIScene *, int, int *, CCBMagicWindow *))(*(_DWORD *)((UIWnd *)(*v16)) + 16))(
      *v16,
      g_nPropIDs_241[10],
      ppButton,
      this);
    v18 = (void *)sub_445FE0(a2);
    sub_43FEC0(v18);
    (((UIScene *)*v16))->UIScene::GetChildCount();
    (((UIScene *)*v16))->UIScene::GetChildAt();
    sub_43FDB0((float *)*v16, 48);
    (((UIProgressBar *)*v16))->UIProgressBar::GetHeight(23);
    (((UIProgressBar *)*v16))->UIProgressBar::GetWidth(11);
    (((UIProgressBar *)*v16))->UIProgressBar::GetPosition(5);
    (((UIScene *)*v16))->UIScene::SetTextParam();
    v19 = (UIScene *)*v16;
    v19->m_pTexture = (gbTexture *)10;
    *(_DWORD *)&v19->m_bOverlayRender = 9;
    (((UIScrollBar *)*v16))->UIScrollBar::SetRange(100.0);
    (((UIProgressBar *)*v16))->UIProgressBar::FindChildByName(100.0);
    (*v16)->m_nRectY = 1077936128;
    (**(void ( ***)(UIScene *, int))((UIWnd *)(*v16)))((UIScene *)(*v16), (int)(1));
  }
  m_pMagicList = (UIListBox **)this->m_pMagicList;
  if ( (((CCBLineupWindow *)v17))->CCBLineupWindow::OnMessage((int *)this->m_pMagicList) == 1 )
  {
    *ppButton = 37;
    ppButton[1] = 57;
    ppButton[2] = 69;
    ppButton[3] = 89;
    (*(void ( **)(UIListBox *, int, int *, CCBMagicWindow *, void *, _DWORD))(*(_DWORD *)((UIWnd *)(*m_pMagicList))
                                                                                      + 28))(
      *m_pMagicList,
      g_nPropIDs_241[5],
      ppButton,
      this,
      &unk_5DF6F4,
      0);
    (((UIPushButton *)*m_pMagicList))->UIPushButton::SetText();
    (**(void ( ***)(UIListBox *, int))((UIWnd *)(*m_pMagicList)))((UIListBox *)(*m_pMagicList), (int)(1));
  }
  v22 = (UIPushButton **)&this->m_pMagicList[1];
  if ( (((CCBLineupWindow *)v21))->CCBLineupWindow::OnMessage((int *)&this->m_pMagicList[1]) == 1 )
  {
    *ppButton = 37;
    ppButton[1] = 94;
    ppButton[2] = 69;
    ppButton[3] = 126;
    (*(void ( **)(UIPushButton *, int, int *, CCBMagicWindow *, void *, _DWORD))(*(_DWORD *)((UIWnd *)(*v22)) + 28))(
      *v22,
      g_nPropIDs_241[6],
      ppButton,
      this,
      &unk_5DF6D0,
      0);
    (((UIPushButton *)*v22))->UIPushButton::SetText();
    (**(void ( ***)(UIPushButton *, int))((UIWnd *)(*v22)))((UIPushButton *)(*v22), (int)(1));
  }
  v24 = (UIPushButton **)&this->m_pMagicList[2];
  if ( (((CCBLineupWindow *)v23))->CCBLineupWindow::OnMessage((int *)&this->m_pMagicList[2]) == 1 )
  {
    *ppButton = 37;
    ppButton[1] = 132;
    ppButton[2] = 69;
    ppButton[3] = 164;
    (*(void ( **)(UIPushButton *, int, int *, CCBMagicWindow *, void *, _DWORD))(*(_DWORD *)((UIWnd *)(*v24)) + 28))(
      *v24,
      g_nPropIDs_241[7],
      ppButton,
      this,
      &unk_5DF6AC,
      0);
    (((UIPushButton *)*v24))->UIPushButton::SetText();
    (**(void ( ***)(UIPushButton *, int))((UIWnd *)(*v24)))((UIPushButton *)(*v24), (int)(1));
  }
  p_m_pButtonWater = (UIPushButton **)&this->m_pButtonWater;
  (((CCBLineupWindow *)v25))->CCBLineupWindow::Update((int *)&this->m_pButtonWater);
  *ppButton = 68;
  ppButton[2] = 160;
  ppButton[1] = 170;
  ppButton[3] = 196;
  (*(void ( **)(UIPushButton *, int, int *, CCBMagicWindow *, void *, int, _DWORD))(*(_DWORD *)((UIWnd *)(*p_m_pButtonWater))
                                                                                            + 28))(
    *p_m_pButtonWater,
    282,
    ppButton,
    this,
    &unk_5DF59C,
    1,
    0);
  (**(void ( ***)(UIPushButton *, int))((UIWnd *)(*p_m_pButtonWater)))((UIPushButton *)(*p_m_pButtonWater), (int)(1));
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

  // [overlay-fix 2026-10-27] C2065: Destroy__ovl_03 无定义/声明（IDA overlay 合成名）——待归属定谳
  // Destroy__ovl_03((int)this);
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pBack) + 20))(m_pBack, 1);
    this->m_pBack = ((UIStatic *)0);
  }
  v3 = (UIListBox *)this->m_pMagicList[0];
  if ( v3 )
  {
    (*(void ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)v3) + 20))(v3, 1);
    this->m_pMagicList[0] = 0;
  }
  v4 = (UIListBox *)this->m_pMagicList[1];
  if ( v4 )
  {
    (*(void ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)v4) + 20))(v4, 1);
    this->m_pMagicList[1] = 0;
  }
  v5 = (UIListBox *)this->m_pMagicList[2];
  if ( v5 )
  {
    (*(void ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)v5) + 20))(v5, 1);
    this->m_pMagicList[2] = 0;
  }
  v6 = (UIListBox *)this->m_pMagicList[3];
  if ( v6 )
  {
    (*(void ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)v6) + 20))(v6, 1);
    this->m_pMagicList[3] = 0;
  }
  v7 = (UIListBox *)this->m_pMagicList[4];
  if ( v7 )
  {
    (*(void ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)v7) + 20))(v7, 1);
    this->m_pMagicList[4] = 0;
  }
  v8 = (UIListBox *)this->m_pMagicList[5];
  if ( v8 )
  {
    (*(void ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)v8) + 20))(v8, 1);
    this->m_pMagicList[5] = 0;
  }
  m_pButtonWater = (UIPushButton *)this->m_pButtonWater;
  if ( m_pButtonWater )
  {
    (*(void ( **)(UIPushButton *, int))(*(_DWORD *)((UIWnd *)m_pButtonWater) + 20))(m_pButtonWater, 1);
    this->m_pButtonWater = ((UIPushButton *)0);
  }
}

// 0x0051C1B0
BOOL CCBMagicWindow::SetActivePage(int n, int nVal)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(272, -1, 0);
  }
  return (((SceneObj *)this))->SceneObj::Update(n, nVal) /* [ROWTABLE] */;
}

// 0x0051C210
UIListBox * CCBMagicWindow::GetActivePage()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  (((CCBSkillWindow *)this))->CCBSkillWindow::Reset() /* [ROWTABLE] */;
  return (UIListBox *)this;
}
