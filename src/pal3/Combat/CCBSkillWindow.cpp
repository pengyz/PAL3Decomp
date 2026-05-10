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
  *(_DWORD *)&this->_data[72] = 0;
  *(_DWORD *)&this->_data[76] = 0;
  *(_DWORD *)&this->_data[80] = 0;
  *(_DWORD *)&this->_data[84] = 0;
  *(_DWORD *)&this->_data[88] = 0;
  *(_DWORD *)&this->_data[92] = 0;
  *(_DWORD *)&this->_data[96] = 0;
  *(_DWORD *)&this->_data[100] = 0;
  *(_DWORD *)&this->_data[104] = 0;
  memset(&this->_data[108], 0, 0x2Cu);
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
  char *v5; // ebx
  LPCSTR *v6; // ebp
  char *v7; // ebx
  _DWORD *v8; // ebx
  _DWORD *v9; // eax
  _DWORD *v10; // ebx
  _DWORD *v11; // eax
  _DWORD *v12; // ebx
  _DWORD *v13; // eax
  _DWORD *v14; // ebx
  char *v15; // ebx
  char *v16; // ebx
  char *v17; // ebx
  char *v18; // ebx
  char *v19; // ebx
  char *v20; // ebx
  char *v21; // ebx
  char *v22; // ebx
  _DWORD a2[4]; // [esp+C8h] [ebp-10h] BYREF

  v3 = parent;
  ((UIWnd *)this)->Create(512, pRect, parent);
  *((_DWORD *)this + 42) = v3;
  v5 = (char *)&this->_data[72];
  ((CCBLineupWindow *)&this->_data[72])->Destroy();
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v5 + 16))(
    *(_DWORD *)v5,
    513,
    pRect,
    this);
  ((UIWnd *)*(UIWnd ***)&this->_data[72])->CreateFromTemplate(aUiCombatResult, 0);
  (***(void (****)(_DWORD, int))v5)(*(_DWORD *)v5, 1);
  v6 = (LPCSTR *)off_570310;
  v7 = (char *)&this->_data[108];
  do
  {
    v7->Destroy();
    *pRect = 15;
    pRect[2] = 79;
    pRect[1] = -15;
    pRect[3] = 113;
    (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v7 + 16))(
      *(_DWORD *)v7,
      528,
      pRect,
      this);
    ((UIWnd *)*(UIWnd ***)v7)->CreateFromTemplate(*v6++, 0);
    v7 += 4;
  }
  while ( (int)v6 < (int)dword_570324 );
  (***(void (****)(_DWORD, int))&this->_data[108])(*(_DWORD *)&this->_data[108], 1);
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
  v15 = (char *)&this->_data[76];
  parent = -1;
  ((CCBLineupWindow *)&this->_data[76])->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 134;
  pRect[3] = 166;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v15 + 16))(
    *(_DWORD *)v15,
    514,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v15)(*(_DWORD *)v15, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[76])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[76])->GetChild((int)&parent);
  v16 = (char *)&this->_data[80];
  ((CCBLineupWindow *)&this->_data[80])->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 134;
  pRect[3] = 166;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v16 + 16))(
    *(_DWORD *)v16,
    515,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v16)(*(_DWORD *)v16, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[80])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[80])->GetChild((int)&parent);
  v17 = (char *)&this->_data[84];
  ((CCBLineupWindow *)&this->_data[84])->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 108;
  pRect[3] = 140;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v17 + 16))(
    *(_DWORD *)v17,
    516,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v17)(*(_DWORD *)v17, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[84])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[84])->GetChild((int)&parent);
  v18 = (char *)&this->_data[88];
  ((CCBLineupWindow *)&this->_data[88])->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 108;
  pRect[3] = 140;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v18 + 16))(
    *(_DWORD *)v18,
    517,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v18)(*(_DWORD *)v18, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[88])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[88])->GetChild((int)&parent);
  v19 = (char *)&this->_data[92];
  ((CCBLineupWindow *)&this->_data[92])->Destroy();
  pRect[2] = 115;
  *pRect = 51;
  pRect[1] = 160;
  pRect[3] = 192;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v19 + 16))(
    *(_DWORD *)v19,
    518,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v19)(*(_DWORD *)v19, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[92])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[92])->GetChild((int)&parent);
  v20 = (char *)&this->_data[96];
  ((CCBLineupWindow *)&this->_data[96])->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 160;
  pRect[3] = 192;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v20 + 16))(
    *(_DWORD *)v20,
    519,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v20)(*(_DWORD *)v20, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[96])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[96])->GetChild((int)&parent);
  v21 = (char *)&this->_data[100];
  ((CCBLineupWindow *)&this->_data[100])->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 211;
  pRect[3] = 243;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v21 + 16))(
    *(_DWORD *)v21,
    529,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v21)(*(_DWORD *)v21, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[100])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[100])->GetChild((int)&parent);
  v22 = (char *)&this->_data[104];
  ((CCBLineupWindow *)&this->_data[104])->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 0;
  pRect[3] = 32;
  (*(void (**)(_DWORD, int, _DWORD *, CCBSkillWindow *))(**(_DWORD **)v22 + 16))(
    *(_DWORD *)v22,
    530,
    pRect,
    this);
  (***(void (****)(_DWORD, int))v22)(*(_DWORD *)v22, 1);
  ((UIWnd *)*(UIWnd **)&this->_data[104])->SetShow(0);
  ((UIWnd *)*(UIWnd **)&this->_data[104])->GetChild((int)&parent);
  return 1;
}

// 0x0051C880
int CCBSkillWindow::Destroy()
{
  int result; // eax
  char *v3; // edi
  int v4; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  v3 = (char *)&this->_data[108];
  v4 = 11;
  do
  {
    if ( *(_DWORD *)v3 )
    {
      result = (*(int (**)(_DWORD, int))(**(_DWORD **)v3 + 20))(*(_DWORD *)v3, 1);
      *(_DWORD *)v3 = 0;
    }
    v3 += 4;
    --v4;
  }
  while ( v4 );
  v5 = *(_DWORD *)&this->_data[72];
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)&this->_data[72] = 0;
  }
  v6 = *(_DWORD *)&this->_data[76];
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)&this->_data[76] = 0;
  }
  v7 = *(_DWORD *)&this->_data[80];
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)&this->_data[80] = 0;
  }
  v8 = *(_DWORD *)&this->_data[84];
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)&this->_data[84] = 0;
  }
  v9 = *(_DWORD *)&this->_data[88];
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)&this->_data[88] = 0;
  }
  v10 = *(_DWORD *)&this->_data[92];
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)&this->_data[92] = 0;
  }
  v11 = *(_DWORD *)&this->_data[96];
  if ( v11 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *(_DWORD *)&this->_data[96] = 0;
  }
  v12 = *(_DWORD *)&this->_data[100];
  if ( v12 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
    *(_DWORD *)&this->_data[100] = 0;
  }
  v13 = *(_DWORD *)&this->_data[104];
  if ( v13 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
    *(_DWORD *)&this->_data[104] = 0;
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
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_data[32] + 1160) + 8))->SetParam(a3, a4);
  return a2->SendMessage(a3, a4);
}

// 0x0051C9F0
BOOL CCBSkillWindow::Update(int a2, int a3)
{
  if ( *(_DWORD *)&this->_data[56] == 1 && g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 )
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(*(_DWORD *)&this->_data[32] + 1160) + 8))->SetParam(513, -1);
  return ((UIWnd *)this)->HitTest(a2, a3);
}
