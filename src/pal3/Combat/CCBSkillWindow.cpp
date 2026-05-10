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
  return (UIWnd *)Block;
}

// 0x0051C2D0
int CCBSkillWindow::Reset()
{
  *((_DWORD *)this + 42) = 0;
  *((_DWORD *)this + 43) = -1;
  this->m_childs.m_pData = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_nMaxSize = 0;
  this->m_childs.m_nGrowBy = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_benable = 0;
  this->m_bfocus = 0;
  this->m_pbktex = 0;
  memset(&this->m_pBack, 0, 0x2Cu);
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 41) = 0;
  return 0;
}

// 0x0051C330
char CCBSkillWindow::Create(int _this, _DWORD *a2, int a3)
{
  int v3; // ebx
  _DWORD *v5; // ebx
  LPCSTR *v6; // ebp
  gbRefObject ***v7; // ebx
  _DWORD *v8; // ebx
  _DWORD *v9; // eax
  _DWORD *v10; // ebx
  _DWORD *v11; // eax
  _DWORD *v12; // ebx
  _DWORD *v13; // eax
  _DWORD *v14; // ebx
  _DWORD *v15; // ebx
  _DWORD *v16; // ebx
  _DWORD *v17; // ebx
  _DWORD *v18; // ebx
  _DWORD *v19; // ebx
  _DWORD *v20; // ebx
  _DWORD *v21; // ebx
  _DWORD *v22; // ebx
  _DWORD v24[4]; // [esp+C8h] [ebp-10h] BYREF

  v3 = a3;
  ((_DWORD *)this)->Create(512, a2, a3);
  *(_DWORD *)(this + 168) = v3;
  v5 = (_DWORD *)(this + 72);
  ((CCBLineupWindow *)this + 72)->Destroy();
  *a2 = 0;
  a2[2] = 256;
  a2[1] = 0;
  a2[3] = 256;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v5 + 16))(*v5, 513, a2, this);
  ((UIWnd *)*(gbRefObject ***)(this + 72))->CreateFromTemplate(aUiCombatResult, 0);
  (**(void (***)(_DWORD, int))*v5)(*v5, 1);
  v6 = (LPCSTR *)off_570310;
  v7 = (gbRefObject ***)(this + 108);
  do
  {
    v7->Destroy();
    *a2 = 15;
    a2[2] = 79;
    a2[1] = -15;
    a2[3] = 113;
    ((void (*)(gbRefObject **, int, _DWORD *, int))(**v7)[4].RefCount)(*v7, 528, a2, this);
    ((UIWnd *)*v7++)->CreateFromTemplate(*v6++, 0);
  }
  while ( (int)v6 < (int)dword_570324 );
  (***(void (****)(_DWORD, int))(this + 108))(*(_DWORD *)(this + 108), 1);
  v8 = (_DWORD *)(this + 156);
  ((CCBLineupWindow *)this + 156)->Render();
  *a2 = 83;
  a2[2] = 168;
  a2[1] = 46;
  a2[3] = 58;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v8 + 16))(*v8, 545, a2, this);
  v9 = ((UIWnd *)*(_DWORD **)(this + 156))->SetRect(v24);
  ((UIWnd *)*(_DWORD **)(this + 156))->AddChild(v9);
  ((UIWnd *)*(gbRefObject ***)(this + 156))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*(gbRefObject ***)(this + 156))->GetChildAt(aUiCombatResult_1, 0);
  sub_43FD90(*(float **)(this + 156), 3);
  ((UIWnd *)*(float **)(this + 156))->SetFrameRate(-2);
  (**(void (***)(_DWORD, int))*v8)(*v8, 1);
  v10 = (_DWORD *)(this + 160);
  ((CCBLineupWindow *)this + 160)->Render();
  *a2 = 86;
  a2[2] = 171;
  a2[1] = 71;
  a2[3] = 83;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v10 + 16))(*v10, 546, a2, this);
  v11 = ((UIWnd *)*(_DWORD **)(this + 160))->SetRect(v24);
  ((UIWnd *)*(_DWORD **)(this + 160))->AddChild(v11);
  ((UIWnd *)*(gbRefObject ***)(this + 160))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*(gbRefObject ***)(this + 160))->GetChildAt(aUiCombatResult_2, 0);
  sub_43FD90(*(float **)(this + 160), 3);
  ((UIWnd *)*(float **)(this + 160))->SetFrameRate(-2);
  (**(void (***)(_DWORD, int))*v10)(*v10, 1);
  v12 = (_DWORD *)(this + 164);
  ((CCBLineupWindow *)this + 164)->Render();
  *a2 = 84;
  a2[2] = 169;
  a2[1] = 97;
  a2[3] = 109;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v12 + 16))(*v12, 547, a2, this);
  v13 = ((UIWnd *)*(_DWORD **)(this + 164))->SetRect(v24);
  ((UIWnd *)*(_DWORD **)(this + 164))->AddChild(v13);
  ((UIWnd *)*(gbRefObject ***)(this + 164))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*(gbRefObject ***)(this + 164))->GetChildAt(aUiCombatResult_3, 0);
  sub_43FD90(*(float **)(this + 164), 3);
  ((UIWnd *)*(float **)(this + 164))->SetFrameRate(-2);
  (**(void (***)(_DWORD, int))*v12)(*v12, 1);
  v14 = (_DWORD *)(this + 152);
  ((CCBLineupWindow *)this + 152)->Destroy();
  *a2 = 66;
  a2[2] = 130;
  a2[1] = 42;
  a2[3] = 109;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v14 + 16))(*v14, 544, a2, this);
  ((UIWnd *)*(gbRefObject ***)(this + 152))->CreateFromTemplate(aUiCombatResult_5, 0);
  (**(void (***)(_DWORD, int))*v14)(*v14, 1);
  v15 = (_DWORD *)(this + 76);
  a3 = -1;
  ((CCBLineupWindow *)this + 76)->Destroy();
  *a2 = 136;
  a2[2] = 200;
  a2[1] = 134;
  a2[3] = 166;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v15 + 16))(*v15, 514, a2, this);
  (**(void (***)(_DWORD, int))*v15)(*v15, 1);
  ((UIWnd *)*(_DWORD **)(this + 76))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 76))->GetChild(&a3);
  v16 = (_DWORD *)(this + 80);
  ((CCBLineupWindow *)this + 80)->Destroy();
  *a2 = 51;
  a2[2] = 115;
  a2[1] = 134;
  a2[3] = 166;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v16 + 16))(*v16, 515, a2, this);
  (**(void (***)(_DWORD, int))*v16)(*v16, 1);
  ((UIWnd *)*(_DWORD **)(this + 80))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 80))->GetChild(&a3);
  v17 = (_DWORD *)(this + 84);
  ((CCBLineupWindow *)this + 84)->Destroy();
  *a2 = 51;
  a2[2] = 115;
  a2[1] = 108;
  a2[3] = 140;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v17 + 16))(*v17, 516, a2, this);
  (**(void (***)(_DWORD, int))*v17)(*v17, 1);
  ((UIWnd *)*(_DWORD **)(this + 84))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 84))->GetChild(&a3);
  v18 = (_DWORD *)(this + 88);
  ((CCBLineupWindow *)this + 88)->Destroy();
  *a2 = 136;
  a2[2] = 200;
  a2[1] = 108;
  a2[3] = 140;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v18 + 16))(*v18, 517, a2, this);
  (**(void (***)(_DWORD, int))*v18)(*v18, 1);
  ((UIWnd *)*(_DWORD **)(this + 88))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 88))->GetChild(&a3);
  v19 = (_DWORD *)(this + 92);
  ((CCBLineupWindow *)this + 92)->Destroy();
  a2[2] = 115;
  *a2 = 51;
  a2[1] = 160;
  a2[3] = 192;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v19 + 16))(*v19, 518, a2, this);
  (**(void (***)(_DWORD, int))*v19)(*v19, 1);
  ((UIWnd *)*(_DWORD **)(this + 92))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 92))->GetChild(&a3);
  v20 = (_DWORD *)(this + 96);
  ((CCBLineupWindow *)this + 96)->Destroy();
  *a2 = 136;
  a2[2] = 200;
  a2[1] = 160;
  a2[3] = 192;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v20 + 16))(*v20, 519, a2, this);
  (**(void (***)(_DWORD, int))*v20)(*v20, 1);
  ((UIWnd *)*(_DWORD **)(this + 96))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 96))->GetChild(&a3);
  v21 = (_DWORD *)(this + 100);
  ((CCBLineupWindow *)this + 100)->Destroy();
  *a2 = 0;
  a2[2] = 187;
  a2[1] = 211;
  a2[3] = 243;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v21 + 16))(*v21, 529, a2, this);
  (**(void (***)(_DWORD, int))*v21)(*v21, 1);
  ((UIWnd *)*(_DWORD **)(this + 100))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 100))->GetChild(&a3);
  v22 = (_DWORD *)(this + 104);
  ((CCBLineupWindow *)this + 104)->Destroy();
  *a2 = 0;
  a2[2] = 187;
  a2[1] = 0;
  a2[3] = 32;
  (*(void (**)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v22 + 16))(*v22, 530, a2, this);
  (**(void (***)(_DWORD, int))*v22)(*v22, 1);
  ((UIWnd *)*(_DWORD **)(this + 104))->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 104))->GetChild(&a3);
  return 1;
}

// 0x0051C880
int CCBSkillWindow::Destroy(int _this)
{
  int result; // eax
  _DWORD *v3; // edi
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

  result = ((gbRefObject **)this)->SetScrollPos();
  v3 = (_DWORD *)(this + 108);
  v4 = 11;
  do
  {
    if ( *v3 )
    {
      result = (*(int (**)(_DWORD, int))(*(_DWORD *)*v3 + 20))(*v3, 1);
      *v3 = 0;
    }
    ++v3;
    --v4;
  }
  while ( v4 );
  v5 = *(_DWORD *)(this + 72);
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v6 = *(_DWORD *)(this + 76);
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 76) = 0;
  }
  v7 = *(_DWORD *)(this + 80);
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 80) = 0;
  }
  v8 = *(_DWORD *)(this + 84);
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 84) = 0;
  }
  v9 = *(_DWORD *)(this + 88);
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 88) = 0;
  }
  v10 = *(_DWORD *)(this + 92);
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v11 = *(_DWORD *)(this + 96);
  if ( v11 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v12 = *(_DWORD *)(this + 100);
  if ( v12 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  v13 = *(_DWORD *)(this + 104);
  if ( v13 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
    *(_DWORD *)(this + 104) = 0;
  }
  v14 = *(_DWORD *)(this + 152);
  if ( v14 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v14 + 20))(v14, 1);
    *(_DWORD *)(this + 152) = 0;
  }
  v15 = *(_DWORD *)(this + 156);
  if ( v15 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v15 + 20))(v15, 1);
    *(_DWORD *)(this + 156) = 0;
  }
  v16 = *(_DWORD *)(this + 160);
  if ( v16 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v16 + 20))(v16, 1);
    *(_DWORD *)(this + 160) = 0;
  }
  v17 = *(_DWORD *)(this + 164);
  if ( v17 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v17 + 20))(v17, 1);
    *(_DWORD *)(this + 164) = 0;
  }
  return result;
}

// 0x0051C9B0
int CCBSkillWindow::OnMessage(int a2, int a3, int a4)
{
  if ( a2 == 1001 )
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
  return a2->SendMessage(a3, a4);
}

// 0x0051C9F0
BOOL CCBSkillWindow::Update(int a2, int a3)
{
  if ( this->m_rect.top == 1 && g_Input.m_DIKToKEY[1] == 1 && (g_Input.m_shiftedKeyStates[268] & 0xF) == 1 )
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(513, -1);
  return this->HitTest(a2, a3);
}
