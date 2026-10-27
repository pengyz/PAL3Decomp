#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBItemWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Misc/CCBPanelSlot.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "GameBase/Logger.h"
#include "Scene/SceneObj.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIButton.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UIStatic.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "Misc/tagEffMgrData.h"
#include "free_functions.h"

// 0x0043DDF0
void CCBControlWindow::Render(CCBMagicWindow *thisa)
{
  if ( this->m_bvisible )
  {
    if ( this->m_pbktex )
      (((TextureLibDataBase *)&this->m_wndcolor))->TextureLibDataBase::SetLibFolder((const char *)&this->m_rect, (int)&this->m_wndcolor);
    (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  }
}

// 0x0051A700
CCBControlWindow::CCBControlWindow()
{
  UIButton **p_m_pButtonAI; // edi
  tagRECT rc; // [esp+0x14] [ebp-0x10] BYREF

  p_m_pButtonAI = (UIButton **)&this->m_pButtonAI;
  rc.left = 40;
  rc.right = 72;
  rc.top = 27;
  rc.bottom = 59;
  this->CCBControlWindow::Create(&this->m_pButtonAI, 192, &rc, g_nUnkDataTable[10]);
  (**(void (***)(UIButton *, int))((UIWnd *)(*p_m_pButtonAI)))((UIButton *)(*p_m_pButtonAI), (int)(1));
  rc.left = 72;
  rc.right = 104;
  rc.top = 27;
  rc.bottom = 59;
  this->CCBControlWindow::Create(&this->m_pButtonFlee, 193, &rc, g_nUnkDataTable[11]);
  (**(void (***)(UIButton *, int))((UIWnd *)this->m_pButtonFlee))((UIButton *)(this->m_pButtonFlee), (int)(1));
  rc.left = 104;
  rc.right = 136;
  rc.top = 27;
  rc.bottom = 59;
  this->CCBControlWindow::Create(&this->m_pButtonProtect, 194, &rc, g_nUnkDataTable[12]);
  (**(void (***)(UIButton *, int))((UIWnd *)this->m_pButtonProtect))((UIButton *)(this->m_pButtonProtect), (int)(1));
  rc.left = 136;
  rc.right = 168;
  rc.top = 27;
  rc.bottom = 59;
  this->CCBControlWindow::Create(&this->m_CurCtrl, 195, &rc, g_nUnkDataTable[13]);
  (**(void (***)(UIWnd *, int))this->m_CurCtrl)((UIWnd *)(this->m_CurCtrl), (int)(1));
  rc.left = 168;
  rc.right = 200;
  rc.top = 27;
  rc.bottom = 59;
  this->CCBControlWindow::Create(&this->m_CurCtrl_1, 196, &rc, g_nUnkDataTable[14]);
  (**(void (***)(UIWnd *, int))this->m_CurCtrl_1)((UIWnd *)(this->m_CurCtrl_1), (int)(1));
  rc.left = 200;
  rc.right = 232;
  rc.top = 27;
  rc.bottom = 59;
  this->CCBControlWindow::Create(&this->m_CurCtrl_2, 197, &rc, g_nUnkDataTable[15]);
  (**(void (***)(UIWnd *, int))this->m_CurCtrl_2)((UIWnd *)(this->m_CurCtrl_2), (int)(1));
}

// 0x0051AA20
bool CCBControlWindow::Create(
        
        UIWnd **ppChild,
        int nCtrlID,
        tagRECT *rc,
        int nDataIdx)
{
  UIPushButton *v6; // eax
  UIWnd *v7; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v11; // [esp+0x810] [ebp-0x4]

  v6 = (UIPushButton *)operator new(0xF8u);
  v11 = 0;
  if ( v6 )
    v6->UIPushButton::UIPushButton();
  else
    v7 = 0;
  v11 = -1;
  *ppChild = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_7, 2875),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void ( **)(UIWnd *, int, tagRECT *, CCBControlWindow *, int, _DWORD))(*(_DWORD *)v7 + 28))(
    v7,
    nCtrlID,
    rc,
    this,
    nDataIdx,
    0);
  return 1;
}

// 0x0051AB60
UIButton * CCBControlWindow::HandleInput(UIButton *pButton)
{
  int v3; // ebp
  UIButton **p_m_pButtonAttack; // edi
  UIButton *m_pButtonAI; // eax
  UIButton *m_pButtonFlee; // eax
  UIButton *m_pButtonProtect; // eax
  UIWnd *m_CurCtrl; // eax
  UIWnd *m_CurCtrl_1; // eax
  UIButton *result; // eax
  UIButton *m_CurCtrl_2; // eax

  v3 = 6;
  p_m_pButtonAttack = (UIButton **)&this->m_pButtonAttack;
  do
  {
    (**(void ( ***)(UIButton *, _DWORD))((UIWnd *)(*p_m_pButtonAttack)))((UIButton *)(*p_m_pButtonAttack), (_DWORD)(0));
    ++p_m_pButtonAttack;
    --v3;
  }
  while ( v3 );
  m_pButtonAI = (UIButton *)this->m_pButtonAI;
  *(_DWORD *)&m_pButtonAI->m_canctrl = 0;
  m_pButtonAI->m_hasDBclk = 0;
  m_pButtonFlee = (UIButton *)this->m_pButtonFlee;
  *(_DWORD *)&m_pButtonFlee->m_canctrl = 0;
  m_pButtonFlee->m_hasDBclk = 0;
  m_pButtonProtect = (UIButton *)this->m_pButtonProtect;
  *(_DWORD *)&m_pButtonProtect->m_canctrl = 0;
  m_pButtonProtect->m_hasDBclk = 0;
  m_CurCtrl = (UIWnd *)this->m_CurCtrl;
  m_CurCtrl[1].m_id = 0;
  *(_BYTE *)&m_CurCtrl[1] = 0;
  m_CurCtrl_1 = (UIWnd *)this->m_CurCtrl_1;
  m_CurCtrl_1[1].m_id = 0;
  *(_BYTE *)&m_CurCtrl_1[1] = 0;
  result = (UIButton *)this->m_CurCtrl_2;
  *(_DWORD *)&result->m_canctrl = 0;
  result->m_hasDBclk = 0;
  switch ( (unsigned int)pButton )
  {
    case 0u:
      m_CurCtrl_2 = (UIButton *)this->m_pButtonAI;
      goto LABEL_10;
    case 1u:
      m_CurCtrl_2 = (UIButton *)this->m_pButtonFlee;
      goto LABEL_10;
    case 2u:
      m_CurCtrl_2 = (UIButton *)this->m_pButtonProtect;
      goto LABEL_10;
    case 3u:
      m_CurCtrl_2 = (UIButton *)this->m_CurCtrl;
      goto LABEL_10;
    case 4u:
      m_CurCtrl_2 = (UIButton *)this->m_CurCtrl_1;
      goto LABEL_10;
    case 5u:
      m_CurCtrl_2 = (UIButton *)this->m_CurCtrl_2;
LABEL_10:
      *(_DWORD *)&m_CurCtrl_2->m_canctrl = 1;
      m_CurCtrl_2->m_hasDBclk = 1;
      SetEnable((UICaption *)this->m_pBack);
      result = (UIButton *)(***((int ( ****)(_DWORD, int))&this->m_pButtonAttack + (_DWORD)pButton))((_DWORD)(*((_DWORD *)&this->m_pButtonAttack + (_DWORD)pButton)), (int)(1));
      *((_DWORD *)&this->m_CurCtrl_2 + 1) = (unsigned long)pButton;
      break;
    default:
      return result;
  }
  return result;
}

// 0x0051AC30
void CCBControlWindow::KeyPressed()
{
  ;
}

// 0x0051AC40
UIListBox * CCBControlWindow::DefaultKey()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->CCBControlWindow::CheckKeyInput();
  return (UIListBox *)this;
}

// 0x0051AC90
UIWnd * CCBControlWindow::HandleEnable(CCBControlWindow *Block, char dir)
{
  this->~CCBControlWindow();
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x0051ACB0
CCBControlWindow::~CCBControlWindow()
{
  this->CCBControlWindow::CheckKeyInput();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0051AD00
void CCBControlWindow::CheckKeyInput()
{
  this->m_pButtonSkill = ((UIButton *)0);
  this->m_pBack = ((UIStatic *)0);
  this->m_pButtonAttack = ((UIButton *)0);
}

// 0x0051AD10
char CCBControlWindow::CreateControls(int *pRect, int parent)
{
  _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  UIFrameContainer *v6; // eax
  UIStatic *v7; // eax
  UIFrameContainer *v8; // eax
  UIButton *v9; // eax
  int *v10; // ebp
  UIButton **p_m_pButtonSkill; // esi
  UIListBox *v12; // eax
  UIListBox *updated; // eax
  char pExceptionObject[1024]; // [esp+0x18] [ebp-0x100C] BYREF
  char ArgList[1024]; // [esp+0x418] [ebp-C0Ch] BYREF
  char v17[1024]; // [esp+0x818] [ebp-0x80C] BYREF
  char v18; // [esp+C18h] [ebp-0x40C] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v19; // [esp+0x1018] [ebp-0xC]
  void *v20; // [esp+0x101C] [ebp-0x8]
  int v21; // [esp+0x1020] [ebp-0x4]

  v21 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v20 = ((void*)0);
  v19 = (_EXCEPTION_REGISTRATION_RECORD *)ExceptionList;
  v4 = alloca(4104);
  this->UIWnd::Create(1879048195, (tagRECT *)pRect, parent);
  v6 = (UIFrameContainer *)operator new(0x98u);
  v21 = 0;
  if ( v6 )
    (((UIFrameContainer *)v6))->UIFrameContainer::ResetContainerState();
  else
    v7 = 0;
  v21 = -1;
  this->m_pBack = ((UIStatic *)(v7));
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 3023),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
  (*(void ( **)(UIStatic *, int, int *, CCBControlWindow *))(*(_DWORD *)((UIWnd *)this->m_pBack) + 16))(
    this->m_pBack,
    161,
    pRect,
    this);
  (((UIPushButton *)this->m_pBack))->UIPushButton::CreateFromTemplate(&unk_5DEF18, 0);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBack))((UIStatic *)(this->m_pBack), (int)(1));
  v8 = (UIFrameContainer *)operator new(0x98u);
  v21 = 1;
  if ( v8 )
    (((UIFrameContainer *)v8))->UIFrameContainer::ResetContainerState();
  else
    v9 = 0;
  v21 = -1;
  this->m_pButtonAttack = ((UIButton *)(v9));
  if ( !v9 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 3037),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((UIScene *)this->m_pBack))->UIScene::SetShow(0);
  AllocObject(this->m_pBack);
  (((UIFrameWnd *)this->m_pBack))->UIFrameWnd::SetPosition(39,   219);
  v10 = (int *)&g_nSkillItemIDTable[24];
  p_m_pButtonSkill = (UIButton **)&this->m_pButtonSkill;
  do
  {
    v12 = (UIListBox *)operator new(0x4B8u);
    v21 = 2;
    if ( v12 )
      updated = (((UIListBox *)v12))->UIListBox::UpdateKeyCtrl();
    else
      updated = 0;
    v21 = -1;
    *p_m_pButtonSkill = (UIButton *)updated;
    if ( !updated )
    {
      qmemcpy(
        v17,
        (((Logger *)&v18))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 3067),
        sizeof(v17));
      _CxxThrowException(v17, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *pRect = 39;
    pRect[2] = 241;
    pRect[1] = 110;
    pRect[3] = 226;
    (*(void ( **)(UIButton *, int, int *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)(*p_m_pButtonSkill))
                                                                                               + 28))(
      *p_m_pButtonSkill,
      *v10,
      pRect,
      this,
      0,
      0,
      0);
    (**(void ( ***)(UIButton *, int))((UIWnd *)(*p_m_pButtonSkill)))((UIButton *)(*p_m_pButtonSkill), (int)(1));
    (((UIListBox *)*p_m_pButtonSkill))->UIListBox::SetItemOffset(2, -4);
    (((UIListBox *)*p_m_pButtonSkill))->UIListBox::SetColumnHead((int)"Name", 150);
    (((UIListBox *)*p_m_pButtonSkill))->UIListBox::SetColumnHead((int)asc_5DFDCC, 43);
    (((UIListBox *)*p_m_pButtonSkill))->UIListBox::SetLockSel(19);
    (((UIListBox *)*p_m_pButtonSkill))->UIListBox::GetSel(g_nUnkDataTable[16], 0);
    UIListBox_SetItemData(1);
    ++v10;
    ++p_m_pButtonSkill;
  }
  while ( (int)v10 < (int)g_nPropIDs_208 );
  return 1;
}

// 0x0051AFE0
int CCBControlWindow::Update(float a2, int a3)
{
  int result; // eax
  UIButton *m_pButtonSkill; // ecx
  UIStatic *m_pBack; // ecx
  UIButton *m_pButtonAttack; // ecx

  result = Destroy__ovl_03((int)this);
  m_pButtonSkill = (UIButton *)this->m_pButtonSkill;
  if ( m_pButtonSkill )
  {
    result = (*(int ( **)(UIButton *, int))(*(_DWORD *)((UIWnd *)m_pButtonSkill) + 20))(m_pButtonSkill, 1);
    this->m_pButtonSkill = ((UIButton *)0);
  }
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    result = (*(int ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pBack) + 20))(m_pBack, 1);
    this->m_pBack = ((UIStatic *)0);
  }
  m_pButtonAttack = (UIButton *)this->m_pButtonAttack;
  if ( m_pButtonAttack )
  {
    result = (*(int ( **)(UIButton *, int))(*(_DWORD *)((UIWnd *)m_pButtonAttack) + 20))(m_pButtonAttack, 1);
    this->m_pButtonAttack = ((UIButton *)0);
  }
  return result;
}

// 0x0051B030
int CCBControlWindow::OnMessage(int nVal, int a2, int a3)
{
  CScreenMode *Instance; // eax

  if ( nVal == 1006 )
  {
    if ( a3 != -1 )
      (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(a2, a3, 1);
  }
  else if ( nVal == 1007 && a3 != -1 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa002", 1);
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(a2, a3, 0);
  }
  return this->UIWnd::OnMessage(nVal, a2, a3);
}

// 0x0051B0B0
BOOL CCBControlWindow::MoveButtons(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(g_nSkillItemIDTable[24], -1, 0);
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x0051B110
UIListBox * CCBControlWindow::CreateButton()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  (((CCBItemWindow *)this))->CCBItemWindow::Reset() /* [ROWTABLE] */;
  return (UIListBox *)this;
}

// 0x0051B5D0
int CCBControlWindow::UpdateDescriptionPage(
        
        unsigned int a2,
        unsigned int a3,
        unsigned int a4)
{
  int v5; // edi
  UIStatic **p_m_pDescription; // esi
  UIStatic *v7; // ecx

  if ( a2 == 1 )
  {
    v5 = 0;
    p_m_pDescription = (UIStatic **)&this->m_pDescription;
    do
    {
      v7 = (UIStatic *)*p_m_pDescription;
      if ( *(&this->m_nActivePage + 5) == v5 )
        (**(void ( ***)(UIStatic *, int))((UIWnd *)v7))((UIStatic *)(v7), (int)(1));
      else
        (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v7))((UIStatic *)(v7), (_DWORD)(0));
      ++v5;
      ++p_m_pDescription;
    }
    while ( v5 < 5 );
  }
  return (((CCBPanelSlot *)this))->CCBPanelSlot::ShowClipped(a2);
}

// 0x0051B940
void CCBControlWindow::ForwardShowClipped(int nFlags)
{
  (((CCBPanelSlot *)this))->CCBPanelSlot::ShowClipped(nFlags);
}
