#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBControlWindow.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
void * sub_446010(void *a2); // from annotations

// Unnamed globals (extern)
extern char unk_5DFDCC[];

// 0x0043DDF0
void CCBControlWindow::Render(CCBMagicWindow *thisa)
{
  if ( this->m_bvisible )
  {
    if ( this->m_pbktex )
      ((TextureLibDataBase *)&this->m_wndcolor)->SetLibFolder((char *)&this->m_rect);
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  }
}

// 0x0051A700
CCBControlWindow::CCBControlWindow()
{
  UIButton **p_m_pButtonAI; // edi
  int nVal; // [esp+0x14] [ebp-0x10] BYREF
  int v4; // [esp+0x18] [ebp-0xC]
  int v5; // [esp+0x1C] [ebp-0x8]
  int v6; // [esp+0x20] [ebp-0x4]

  p_m_pButtonAI = &this->m_pButtonAI;
  nVal = 40;
  v5 = 72;
  v4 = 27;
  v6 = 59;
  this->Create((tagRECT *)&this->m_pButtonAI, (UIWnd *)0xC0, (int)&nVal, g_nUnkDataTable[10]);
// [VFTABLE] ((void (*)(UIButton *, int))(*p_m_pButtonAI)->__vftable->ShowWindow)(*p_m_pButtonAI, 1);
  nVal = 72;
  v5 = 104;
  v4 = 27;
  v6 = 59;
  this->Create((tagRECT *)&this->m_pButtonFlee, (UIWnd *)0xC1, (int)&nVal, g_nUnkDataTable[11]);
// [VFTABLE] ((void (*)(UIButton *, int))this->m_pButtonFlee->__vftable->ShowWindow)(this->m_pButtonFlee, 1);
  nVal = 104;
  v5 = 136;
  v4 = 27;
  v6 = 59;
  this->Create((tagRECT *)&this->m_pButtonProtect, (UIWnd *)0xC2, (int)&nVal, g_nUnkDataTable[12]);
// [VFTABLE] ((void (*)(UIButton *, int))this->m_pButtonProtect->__vftable->ShowWindow)(this->m_pButtonProtect, 1);
  nVal = 136;
  v5 = 168;
  v4 = 27;
  v6 = 59;
  this->Create((tagRECT *)&this->m_CurCtrl, (UIWnd *)0xC3, (int)&nVal, g_nUnkDataTable[13]);
  (**(void (***)(int, int))this->m_CurCtrl)(this->m_CurCtrl, 1);
  nVal = 168;
  v5 = 200;
  v4 = 27;
  v6 = 59;
  this->Create((tagRECT *)(&this->m_CurCtrl + 1), (UIWnd *)0xC4, (int)&nVal, g_nUnkDataTable[14]);
  (***((void (****)(_DWORD, int))&this->m_CurCtrl + 1))(*(&this->m_CurCtrl + 1), 1);
  nVal = 200;
  v5 = 232;
  v4 = 27;
  v6 = 59;
  this->Create((tagRECT *)(&this->m_CurCtrl + 2), (UIWnd *)0xC5, (int)&nVal, g_nUnkDataTable[15]);
  (***((void (****)(_DWORD, int))&this->m_CurCtrl + 2))(*(&this->m_CurCtrl + 2), 1);
}

// 0x0051AA20
bool CCBControlWindow::Create(tagRECT *rc, UIWnd *pFather, int nVal, int nVal2)
{
  UIStatic *v6; // eax
  LONG v7; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v11; // [esp+0x810] [ebp-0x4]

  v6 = (UIStatic *)operator new(0xF8u);
  v11 = 0;
  if ( v6 )
  {
  }
  else
    v7 = 0;
  v11 = -1;
  rc->left = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 2875),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void ( **)(LONG, UIWnd *, int, CCBControlWindow *, int, _DWORD))(*(_DWORD *)v7 + 28))(
    v7,
    pFather,
    nVal,
    this,
    nVal2,
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
  int m_CurCtrl; // eax
  int v9; // eax
  UIButton *result; // eax
  int v11; // eax

  v3 = 6;
  p_m_pButtonAttack = &this->m_pButtonAttack;
  do
  {
// [VFTABLE] ((void ( *)(UIButton *, _DWORD))(*p_m_pButtonAttack)->__vftable->ShowWindow)(*p_m_pButtonAttack, 0);
    ++p_m_pButtonAttack;
    --v3;
  }
  while ( v3 );
  m_pButtonAI = this->m_pButtonAI;
  *(_DWORD *)&m_pButtonAI->m_canctrl = 0;
  m_pButtonAI->m_hasDBclk = 0;
  m_pButtonFlee = this->m_pButtonFlee;
  *(_DWORD *)&m_pButtonFlee->m_canctrl = 0;
  m_pButtonFlee->m_hasDBclk = 0;
  m_pButtonProtect = this->m_pButtonProtect;
  *(_DWORD *)&m_pButtonProtect->m_canctrl = 0;
  m_pButtonProtect->m_hasDBclk = 0;
  m_CurCtrl = this->m_CurCtrl;
  *(_DWORD *)(m_CurCtrl + 80) = 0;
  *(_BYTE *)(m_CurCtrl + 68) = 0;
  v9 = *(&this->m_CurCtrl + 1);
  *(_DWORD *)(v9 + 80) = 0;
  *(_BYTE *)(v9 + 68) = 0;
  result = (UIButton *)*(&this->m_CurCtrl + 2);
  *(_DWORD *)&result->m_canctrl = 0;
  result->m_hasDBclk = 0;
  switch ( (unsigned int)pButton )
  {
    case 0u:
      v11 = (int)this->m_pButtonAI;
      goto LABEL_10;
    case 1u:
      v11 = (int)this->m_pButtonFlee;
      goto LABEL_10;
    case 2u:
      v11 = (int)this->m_pButtonProtect;
      goto LABEL_10;
    case 3u:
      v11 = this->m_CurCtrl;
      goto LABEL_10;
    case 4u:
      v11 = *(&this->m_CurCtrl + 1);
      goto LABEL_10;
    case 5u:
      v11 = *(&this->m_CurCtrl + 2);
LABEL_10:
      *(_DWORD *)(v11 + 80) = 1;
      *(_BYTE *)(v11 + 68) = 1;
      ((UICaption *)this->m_pBack)->SetEnable((int)g_szSceneUIText, 0);
      result = (UIButton *)(***((int ( ****)(_DWORD, int))&this->m_pButtonAttack + (_DWORD)pButton))(
                             *((_DWORD *)&this->m_pButtonAttack + (_DWORD)pButton),
                             1);
      *(&this->m_CurCtrl + 3) = (int)pButton;
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

  return (UIListBox *)this;
}

// 0x0051AC90
UIWnd * CCBControlWindow::HandleEnable(CCBControlWindow *Block, char dir)
{
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x0051ACB0
void CCBControlWindow::_CCBControlWindow()
{

  ((UIListBox *)this)->_UIListBox();
}

// 0x0051AD00
void CCBControlWindow::CheckKeyInput()
{
  this->m_pButtonSkill = 0;
  this->m_pBack = 0;
  this->m_pButtonAttack = 0;
}

// 0x0051AD10
char CCBControlWindow::OnMessage(int *pRect, int parent)
{
// [IDA_MISID]   _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  void *v6; // eax
  UIStatic *v7; // eax
  void *v8; // eax
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
// [IDA_MISID]   ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v20 = ((void*)0);
// [IDA_MISID]   v19 = ExceptionList;
  v4 = alloca(4104);
  ((PalScript *)this)->Create(1879048195, (tagRECT *)pRect, parent);
  v6 = operator new(0x98u);
  v21 = 0;
  if ( v6 )
    sub_4422E0(v6);
  else
    v7 = 0;
  v21 = -1;
  this->m_pBack = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 3023),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBControlWindow *))this->m_pBack->__vftable->Create)(
// [VFTABLE]   this->m_pBack,
// [VFTABLE]   161,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
  ((UIStatic *)this->m_pBack)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBack->__vftable->ShowWindow)(this->m_pBack, 1);
  v8 = operator new(0x98u);
  v21 = 1;
  if ( v8 )
    sub_4422E0(v8);
  else
    v9 = 0;
  v21 = -1;
  this->m_pButtonAttack = v9;
  if ( !v9 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 3037),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((UIScene *)this->m_pBack)->SetShow(0);
  sub_446010(this->m_pBack);
  ((UIFrameWnd *)this->m_pBack)->SetPosition(39,   219);
  v10 = &g_nSkillItemIDTable[24];
  p_m_pButtonSkill = &this->m_pButtonSkill;
  do
  {
    v12 = (UIListBox *)operator new(0x4B8u);
    v21 = 2;
    if ( v12 )
      updated = ((UIListBox *)v12)->UpdateKeyCtrl();
    else
      updated = 0;
    v21 = -1;
    *p_m_pButtonSkill = (UIButton *)updated;
    if ( !updated )
    {
      qmemcpy(v17, ((Logger *)&v18)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 3067), sizeof(v17));
      _CxxThrowException(v17, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *pRect = 39;
    pRect[2] = 241;
    pRect[1] = 110;
    pRect[3] = 226;
// [VFTABLE] ((void ( *)(UIButton *, int, int *, CCBControlWindow *, _DWORD, _DWORD, _DWORD))(*p_m_pButtonSkill)->__vftable[1].ShowWindow)(
// [VFTABLE]   *p_m_pButtonSkill,
// [VFTABLE]   *v10,
// [VFTABLE]   pRect,
// [VFTABLE]   this,
// [VFTABLE]   0,
// [VFTABLE]   0,
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIButton *, int))(*p_m_pButtonSkill)->__vftable->ShowWindow)(*p_m_pButtonSkill, 1);
    ((UIListBox *)*p_m_pButtonSkill)->SetItemOffset(2, -4);
    ((UIListBox *)*p_m_pButtonSkill)->SetFirstShow((int)"Name", 150);
    ((UIListBox *)*p_m_pButtonSkill)->SetFirstShow((int)unk_5DFDCC, 43);
    ((UIListBox *)*p_m_pButtonSkill)->SetLockSel();
    ((UIListBox *)*p_m_pButtonSkill)->GetSel(g_nUnkDataTable[16], 0);
    ((UIListBox *)*p_m_pButtonSkill)->SetItemData(1);
    ++v10;
    ++p_m_pButtonSkill;
  }
  while ( (int)v10 < (int)g_nPropIDs_208 );
  return 1;
}

// 0x0051B030
int CCBControlWindow::OnMessage(int nVal, int a2, int a3)
{
  CScreenMode *Instance; // eax

  if ( nVal == 1006 )
  {
    if ( a3 != -1 )
      ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(a2, a3);
  }
  else if ( nVal == 1007 && a3 != -1 )
  {
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa002", 1);
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(a2, a3);
  }
  return ((PalScript *)this)->OnMessage(nVal, a2, a3);
}

// 0x0051B0B0
BOOL CCBControlWindow::MoveButtons(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(g_nSkillItemIDTable[24], -1);
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x0051B110
UIListBox * CCBControlWindow::CreateButton()
{
  ((CCBItemWindow *)this)->Reset();
  return (UIListBox *)this;
}
