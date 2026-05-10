#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBSkillWindow.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_43FD90(...);

// Unnamed globals (extern)
extern char aUiCombatResult[];
extern char aUiCombatResult_1[];
extern char aUiCombatResult_2[];
extern char aUiCombatResult_3[];
extern char aUiCombatResult_4[];
extern char aUiCombatResult_5[];
extern int dword_570324;
extern void *off_570310;

// 0x0051C260
CCBSkillWindow::CCBSkillWindow(CCBSkillWindow *Block, char a2)
{
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  (UIWnd *)Block;
}

// 0x0051C2D0
int CCBSkillWindow::Reset()
{
  *((_DWORD *)this + 42) = 0;
  *((_DWORD *)this + 43) = -1;
  this->_d048 = 0;
  this->_d04C = 0;
  this->_d050 = 0;
  this->_d054 = 0;
  this->_d058 = 0;
  this->_d05C = 0;
  this->_d060 = 0;
  this->_d064 = 0;
  this->_d068 = 0;
  memset(&this->_d06C, 0, 0x2Cu);
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 41) = 0;
  return 0;
}

// 0x0051C330
char CCBSkillWindow::Create(_DWORD *pRect, int parent)
{
  int v3; // ebx
  int *p_d048; // ebx
  LPCSTR *v6; // ebp
  int *p_d06C; // ebx
  _DWORD *v8; // ebx
  _DWORD *v9; // eax
  _DWORD *v10; // ebx
  _DWORD *v11; // eax
  _DWORD *v12; // ebx
  _DWORD *v13; // eax
  _DWORD *v14; // ebx
  int *p_d04C; // ebx
  int *p_d050; // ebx
  int *p_d054; // ebx
  int *p_d058; // ebx
  int *p_d05C; // ebx
  int *p_d060; // ebx
  int *p_d064; // ebx
  int *p_d068; // ebx
  _DWORD a2[4]; // [esp+C8h] [ebp-10h] BYREF

  v3 = parent;
  ((UIWnd *)this)->Create(512, pRect, parent);
  *((_DWORD *)this + 42) = v3;
  p_d048 = (int *)&this->_d048;
  ((CCBLineupWindow *)&this->_d048)->Destroy();
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d048 + 16))(*p_d048, 513, pRect, this);
  ((UIWnd *)this->_d048)->CreateFromTemplate(aUiCombatResult, 0);
  (**(void (***)(int, int))*p_d048)(*p_d048, 1);
  v6 = (LPCSTR *)off_570310;
  p_d06C = (int *)&this->_d06C;
  do
  {
    p_d06C->Destroy();
    *pRect = 15;
    pRect[2] = 79;
    pRect[1] = -15;
    pRect[3] = 113;
    (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d06C + 16))(*p_d06C, 528, pRect, this);
    ((UIWnd *)*p_d06C++)->CreateFromTemplate(*v6++, 0);
  }
  while ( (int)v6 < (int)dword_570324 );
  (**(void (***)(int, int))this->_d06C)(this->_d06C, 1);
  v8 = (_DWORD *)this + 39;
  ((CCBLineupWindow *)(_DWORD *)this + 39)->Render();
  *pRect = 83;
  pRect[2] = 168;
  pRect[1] = 46;
  pRect[3] = 58;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*v8 + 16))(*v8, 545, pRect, this);
  v9 = ((UIWnd *)*((UIWnd **)this + 39))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 39))->AddChild(v9);
  ((UIWnd *)*((UIWnd ***)this + 39))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 39))->GetChildAt(aUiCombatResult_1, 0);
  sub_43FD90(*((float **)this + 39), 3);
  ((UIWnd *)*((UIWnd **)this + 39))->SetFrameRate(-2);
  (**(void (***)(_DWORD, int))*v8)(*v8, 1);
  v10 = (_DWORD *)this + 40;
  ((CCBLineupWindow *)(_DWORD *)this + 40)->Render();
  *pRect = 86;
  pRect[2] = 171;
  pRect[1] = 71;
  pRect[3] = 83;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*v10 + 16))(*v10, 546, pRect, this);
  v11 = ((UIWnd *)*((UIWnd **)this + 40))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 40))->AddChild(v11);
  ((UIWnd *)*((UIWnd ***)this + 40))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 40))->GetChildAt(aUiCombatResult_2, 0);
  sub_43FD90(*((float **)this + 40), 3);
  ((UIWnd *)*((UIWnd **)this + 40))->SetFrameRate(-2);
  (**(void (***)(_DWORD, int))*v10)(*v10, 1);
  v12 = (_DWORD *)this + 41;
  ((CCBLineupWindow *)(_DWORD *)this + 41)->Render();
  *pRect = 84;
  pRect[2] = 169;
  pRect[1] = 97;
  pRect[3] = 109;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*v12 + 16))(*v12, 547, pRect, this);
  v13 = ((UIWnd *)*((UIWnd **)this + 41))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 41))->AddChild(v13);
  ((UIWnd *)*((UIWnd ***)this + 41))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 41))->GetChildAt(aUiCombatResult_3, 0);
  sub_43FD90(*((float **)this + 41), 3);
  ((UIWnd *)*((UIWnd **)this + 41))->SetFrameRate(-2);
  (**(void (***)(_DWORD, int))*v12)(*v12, 1);
  v14 = (_DWORD *)this + 38;
  ((CCBLineupWindow *)(_DWORD *)this + 38)->Destroy();
  *pRect = 66;
  pRect[2] = 130;
  pRect[1] = 42;
  pRect[3] = 109;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*v14 + 16))(*v14, 544, pRect, this);
  ((UIWnd *)*((UIWnd ***)this + 38))->CreateFromTemplate(aUiCombatResult_5, 0);
  (**(void (***)(_DWORD, int))*v14)(*v14, 1);
  p_d04C = (int *)&this->_d04C;
  parent = -1;
  ((CCBLineupWindow *)&this->_d04C)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 134;
  pRect[3] = 166;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d04C + 16))(*p_d04C, 514, pRect, this);
  (**(void (***)(int, int))*p_d04C)(*p_d04C, 1);
  ((UIWnd *)this->_d04C)->SetShow(0);
  ((UIWnd *)this->_d04C)->GetChild((int)&parent);
  p_d050 = (int *)&this->_d050;
  ((CCBLineupWindow *)&this->_d050)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 134;
  pRect[3] = 166;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d050 + 16))(*p_d050, 515, pRect, this);
  (**(void (***)(int, int))*p_d050)(*p_d050, 1);
  ((UIWnd *)this->_d050)->SetShow(0);
  ((UIWnd *)this->_d050)->GetChild((int)&parent);
  p_d054 = (int *)&this->_d054;
  ((CCBLineupWindow *)&this->_d054)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 108;
  pRect[3] = 140;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d054 + 16))(*p_d054, 516, pRect, this);
  (**(void (***)(int, int))*p_d054)(*p_d054, 1);
  ((UIWnd *)this->_d054)->SetShow(0);
  ((UIWnd *)this->_d054)->GetChild((int)&parent);
  p_d058 = (int *)&this->_d058;
  ((CCBLineupWindow *)&this->_d058)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 108;
  pRect[3] = 140;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d058 + 16))(*p_d058, 517, pRect, this);
  (**(void (***)(int, int))*p_d058)(*p_d058, 1);
  ((UIWnd *)this->_d058)->SetShow(0);
  ((UIWnd *)this->_d058)->GetChild((int)&parent);
  p_d05C = (int *)&this->_d05C;
  ((CCBLineupWindow *)&this->_d05C)->Destroy();
  pRect[2] = 115;
  *pRect = 51;
  pRect[1] = 160;
  pRect[3] = 192;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d05C + 16))(*p_d05C, 518, pRect, this);
  (**(void (***)(int, int))*p_d05C)(*p_d05C, 1);
  ((UIWnd *)this->_d05C)->SetShow(0);
  ((UIWnd *)this->_d05C)->GetChild((int)&parent);
  p_d060 = (int *)&this->_d060;
  ((CCBLineupWindow *)&this->_d060)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 160;
  pRect[3] = 192;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d060 + 16))(*p_d060, 519, pRect, this);
  (**(void (***)(int, int))*p_d060)(*p_d060, 1);
  ((UIWnd *)this->_d060)->SetShow(0);
  ((UIWnd *)this->_d060)->GetChild((int)&parent);
  p_d064 = (int *)&this->_d064;
  ((CCBLineupWindow *)&this->_d064)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 211;
  pRect[3] = 243;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d064 + 16))(*p_d064, 529, pRect, this);
  (**(void (***)(int, int))*p_d064)(*p_d064, 1);
  ((UIWnd *)this->_d064)->SetShow(0);
  ((UIWnd *)this->_d064)->GetChild((int)&parent);
  p_d068 = (int *)&this->_d068;
  ((CCBLineupWindow *)&this->_d068)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 0;
  pRect[3] = 32;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_d068 + 16))(*p_d068, 530, pRect, this);
  (**(void (***)(int, int))*p_d068)(*p_d068, 1);
  ((UIWnd *)this->_d068)->SetShow(0);
  ((UIWnd *)this->_d068)->GetChild((int)&parent);
  return 1;
}

// 0x0051C880
int CCBSkillWindow::Destroy()
{
  int result; // eax
  int *p_d06C; // edi
  int v4; // ebx
  int d048; // ecx
  int d04C; // ecx
  int d050; // ecx
  int d054; // ecx
  int d058; // ecx
  int d05C; // ecx
  int d060; // ecx
  int d064; // ecx
  int d068; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  p_d06C = (int *)&this->_d06C;
  v4 = 11;
  do
  {
    if ( *p_d06C )
    {
      result = (*(int (**)(int, int))(*(_DWORD *)*p_d06C + 20))(*p_d06C, 1);
      *p_d06C = 0;
    }
    ++p_d06C;
    --v4;
  }
  while ( v4 );
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
  d068 = this->_d068;
  if ( d068 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)d068 + 20))(d068, 1);
    this->_d068 = 0;
  }
  v14 = *((_DWORD *)this + 38);
  if ( v14 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v14 + 20))(v14, 1);
    *((_DWORD *)this + 38) = 0;
  }
  v15 = *((_DWORD *)this + 39);
  if ( v15 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v15 + 20))(v15, 1);
    *((_DWORD *)this + 39) = 0;
  }
  v16 = *((_DWORD *)this + 40);
  if ( v16 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v16 + 20))(v16, 1);
    *((_DWORD *)this + 40) = 0;
  }
  v17 = *((_DWORD *)this + 41);
  if ( v17 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v17 + 20))(v17, 1);
    *((_DWORD *)this + 41) = 0;
  }
  return result;
}

// 0x0051C9B0
int CCBSkillWindow::OnMessage(int a2, int a3, int a4)
{
  if ( a2 == 1001 )
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(a3, a4);
  return a2->SendMessage(a3, a4);
}

// 0x0051C9F0
BOOL CCBSkillWindow::Update(int a2, int a3)
{
  if ( this->_d038 == 1 && g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 )
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->_d020 + 1160) + 8))->SetParam(513, -1);
  return ((UIWnd *)this)->HitTest(a2, a3);
}
