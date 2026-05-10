#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBSkillWindow.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

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
  ((UIWnd *)&Block->_base._base)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  (UIWnd *)Block;
}

// 0x0051C2D0
int CCBSkillWindow::Reset()
{
  *((_DWORD *)this + 42) = 0;
  *((_DWORD *)this + 43) = -1;
  this->m_pBack = 0;
  this->m_pDescription = 0;
  this->m_pSkillList[0] = 0;
  *((_DWORD *)this + 21) = 0;
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 23) = 0;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 26) = 0;
  memset((char *)this + 108, 0, 0x2Cu);
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
  UIStatic **p_m_pBack; // ebx
  LPCSTR *v6; // ebp
  UIWnd ***v7; // ebx
  CCBSkillWindow *v8; // ebx
  _DWORD *v9; // eax
  CCBSkillWindow *v10; // ebx
  _DWORD *v11; // eax
  CCBSkillWindow *v12; // ebx
  _DWORD *v13; // eax
  CCBSkillWindow *v14; // ebx
  UIStatic **p_m_pDescription; // ebx
  void **m_pSkillList; // ebx
  CCBSkillWindow *v17; // ebx
  CCBSkillWindow *v18; // ebx
  CCBSkillWindow *v19; // ebx
  CCBSkillWindow *v20; // ebx
  CCBSkillWindow *v21; // ebx
  CCBSkillWindow *v22; // ebx
  _DWORD a2[4]; // [esp+C8h] [ebp-10h] BYREF

  v3 = parent;
  ((UIWnd *)&this->_base._base)->Create(512, pRect, parent);
  *((_DWORD *)this + 42) = v3;
  p_m_pBack = &this->m_pBack;
  ((CCBLineupWindow *)&this->m_pBack)->Destroy();
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
  (*((void (**)(UIStatic *, int, _DWORD *, CCBSkillWindow *))(*p_m_pBack)->_base._vftable + 4))(
    *p_m_pBack,
    513,
    pRect,
    this);
  ((UIWnd *)this->m_pBack)->CreateFromTemplate(aUiCombatResult, 0);
  ((void (*)(UIStatic *, int))*(*p_m_pBack)->_base._vftable)(*p_m_pBack, 1);
  v6 = (LPCSTR *)off_570310;
  v7 = (UIWnd ***)((char *)this + 108);
  do
  {
    v7->Destroy();
    *pRect = 15;
    pRect[2] = 79;
    pRect[1] = -15;
    pRect[3] = 113;
    ((void (*)(UIWnd **, int, _DWORD *, CCBSkillWindow *))(**v7)->m_rect_left)(*v7, 528, pRect, this);
    ((UIWnd *)*v7++)->CreateFromTemplate(*v6++, 0);
  }
  while ( (int)v6 < (int)dword_570324 );
  (***((void (****)(_DWORD, int))this + 27))(*((_DWORD *)this + 27), 1);
  v8 = (CCBSkillWindow *)((char *)this + 156);
  ((CCBLineupWindow *)(_DWORD *)this + 39)->Render();
  *pRect = 83;
  pRect[2] = 168;
  pRect[1] = 46;
  pRect[3] = 58;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v8->_base._base._vftable + 4))(
    v8->_base._base._vftable,
    545,
    pRect,
    this);
  v9 = ((UIWnd *)*((UIWnd **)this + 39))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 39))->AddChild(v9);
  ((UIWnd *)*((UIWnd ***)this + 39))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 39))->GetChildAt(aUiCombatResult_1, 0);
  SetIntParam(*((void **)this + 39), 3);
  ((UIWnd *)*((UIWnd **)this + 39))->SetFrameRate(-2);
  (**(void (***)(void **, int))v8->_base._base._vftable)(v8->_base._base._vftable, 1);
  v10 = (CCBSkillWindow *)((char *)this + 160);
  ((CCBLineupWindow *)(_DWORD *)this + 40)->Render();
  *pRect = 86;
  pRect[2] = 171;
  pRect[1] = 71;
  pRect[3] = 83;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v10->_base._base._vftable + 4))(
    v10->_base._base._vftable,
    546,
    pRect,
    this);
  v11 = ((UIWnd *)*((UIWnd **)this + 40))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 40))->AddChild(v11);
  ((UIWnd *)*((UIWnd ***)this + 40))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 40))->GetChildAt(aUiCombatResult_2, 0);
  SetIntParam(*((void **)this + 40), 3);
  ((UIWnd *)*((UIWnd **)this + 40))->SetFrameRate(-2);
  (**(void (***)(void **, int))v10->_base._base._vftable)(v10->_base._base._vftable, 1);
  v12 = (CCBSkillWindow *)((char *)this + 164);
  ((CCBLineupWindow *)(_DWORD *)this + 41)->Render();
  *pRect = 84;
  pRect[2] = 169;
  pRect[1] = 97;
  pRect[3] = 109;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v12->_base._base._vftable + 4))(
    v12->_base._base._vftable,
    547,
    pRect,
    this);
  v13 = ((UIWnd *)*((UIWnd **)this + 41))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 41))->AddChild(v13);
  ((UIWnd *)*((UIWnd ***)this + 41))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 41))->GetChildAt(aUiCombatResult_3, 0);
  SetIntParam(*((void **)this + 41), 3);
  ((UIWnd *)*((UIWnd **)this + 41))->SetFrameRate(-2);
  (**(void (***)(void **, int))v12->_base._base._vftable)(v12->_base._base._vftable, 1);
  v14 = (CCBSkillWindow *)((char *)this + 152);
  ((CCBLineupWindow *)(_DWORD *)this + 38)->Destroy();
  *pRect = 66;
  pRect[2] = 130;
  pRect[1] = 42;
  pRect[3] = 109;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v14->_base._base._vftable + 4))(
    v14->_base._base._vftable,
    544,
    pRect,
    this);
  ((UIWnd *)*((UIWnd ***)this + 38))->CreateFromTemplate(aUiCombatResult_5, 0);
  (**(void (***)(void **, int))v14->_base._base._vftable)(v14->_base._base._vftable, 1);
  p_m_pDescription = &this->m_pDescription;
  parent = -1;
  ((CCBLineupWindow *)&this->m_pDescription)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 134;
  pRect[3] = 166;
  (*((void (**)(UIStatic *, int, _DWORD *, CCBSkillWindow *))(*p_m_pDescription)->_base._vftable + 4))(
    *p_m_pDescription,
    514,
    pRect,
    this);
  ((void (*)(UIStatic *, int))*(*p_m_pDescription)->_base._vftable)(*p_m_pDescription, 1);
  ((UIWnd *)&this->m_pDescription->_base)->SetShow(0);
  ((UIWnd *)&this->m_pDescription->_base)->GetChild((int)&parent);
  m_pSkillList = this->m_pSkillList;
  ((CCBLineupWindow *)this->m_pSkillList)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 134;
  pRect[3] = 166;
  (*(void (**)(void *, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*m_pSkillList + 16))(
    *m_pSkillList,
    515,
    pRect,
    this);
  (**(void (***)(void *, int))*m_pSkillList)(*m_pSkillList, 1);
  ((UIWnd *)this->m_pSkillList[0])->SetShow(0);
  ((UIWnd *)this->m_pSkillList[0])->GetChild((int)&parent);
  v17 = (CCBSkillWindow *)this + 1;
  ((CCBLineupWindow *)(_DWORD *)this + 21)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 108;
  pRect[3] = 140;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v17->_base._base._vftable + 4))(
    v17->_base._base._vftable,
    516,
    pRect,
    this);
  (**(void (***)(void **, int))v17->_base._base._vftable)(v17->_base._base._vftable, 1);
  ((UIWnd *)*((UIWnd **)this + 21))->SetShow(0);
  ((UIWnd *)*((UIWnd **)this + 21))->GetChild((int)&parent);
  v18 = (CCBSkillWindow *)((char *)this + 88);
  ((CCBLineupWindow *)(_DWORD *)this + 22)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 108;
  pRect[3] = 140;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v18->_base._base._vftable + 4))(
    v18->_base._base._vftable,
    517,
    pRect,
    this);
  (**(void (***)(void **, int))v18->_base._base._vftable)(v18->_base._base._vftable, 1);
  ((UIWnd *)*((UIWnd **)this + 22))->SetShow(0);
  ((UIWnd *)*((UIWnd **)this + 22))->GetChild((int)&parent);
  v19 = (CCBSkillWindow *)((char *)this + 92);
  ((CCBLineupWindow *)(_DWORD *)this + 23)->Destroy();
  pRect[2] = 115;
  *pRect = 51;
  pRect[1] = 160;
  pRect[3] = 192;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v19->_base._base._vftable + 4))(
    v19->_base._base._vftable,
    518,
    pRect,
    this);
  (**(void (***)(void **, int))v19->_base._base._vftable)(v19->_base._base._vftable, 1);
  ((UIWnd *)*((UIWnd **)this + 23))->SetShow(0);
  ((UIWnd *)*((UIWnd **)this + 23))->GetChild((int)&parent);
  v20 = (CCBSkillWindow *)((char *)this + 96);
  ((CCBLineupWindow *)(_DWORD *)this + 24)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 160;
  pRect[3] = 192;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v20->_base._base._vftable + 4))(
    v20->_base._base._vftable,
    519,
    pRect,
    this);
  (**(void (***)(void **, int))v20->_base._base._vftable)(v20->_base._base._vftable, 1);
  ((UIWnd *)*((UIWnd **)this + 24))->SetShow(0);
  ((UIWnd *)*((UIWnd **)this + 24))->GetChild((int)&parent);
  v21 = (CCBSkillWindow *)((char *)this + 100);
  ((CCBLineupWindow *)(_DWORD *)this + 25)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 211;
  pRect[3] = 243;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v21->_base._base._vftable + 4))(
    v21->_base._base._vftable,
    529,
    pRect,
    this);
  (**(void (***)(void **, int))v21->_base._base._vftable)(v21->_base._base._vftable, 1);
  ((UIWnd *)*((UIWnd **)this + 25))->SetShow(0);
  ((UIWnd *)*((UIWnd **)this + 25))->GetChild((int)&parent);
  v22 = (CCBSkillWindow *)((char *)this + 104);
  ((CCBLineupWindow *)(_DWORD *)this + 26)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 0;
  pRect[3] = 32;
  (*((void (**)(void **, int, _DWORD *, CCBSkillWindow *))*v22->_base._base._vftable + 4))(
    v22->_base._base._vftable,
    530,
    pRect,
    this);
  (**(void (***)(void **, int))v22->_base._base._vftable)(v22->_base._base._vftable, 1);
  ((UIWnd *)*((UIWnd **)this + 26))->SetShow(0);
  ((UIWnd *)*((UIWnd **)this + 26))->GetChild((int)&parent);
  return 1;
}

// 0x0051C880
int CCBSkillWindow::Destroy()
{
  int result; // eax
  CCBSkillWindow *v3; // edi
  int v4; // ebx
  UIStatic *m_pBack; // ecx
  UIStatic *m_pDescription; // ecx
  void *v7; // ecx
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
  v3 = (CCBSkillWindow *)((char *)this + 108);
  v4 = 11;
  do
  {
    if ( v3->_base._base._vftable )
    {
      result = (*((int (**)(void **, int))*v3->_base._base._vftable + 5))(v3->_base._base._vftable, 1);
      v3->_base._base._vftable = 0;
    }
    v3 = (CCBSkillWindow *)((char *)v3 + 4);
    --v4;
  }
  while ( v4 );
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    result = (*((int (**)(UIStatic *, int))m_pBack->_base._vftable + 5))(m_pBack, 1);
    this->m_pBack = 0;
  }
  m_pDescription = (UIStatic *)this->m_pDescription;
  if ( m_pDescription )
  {
    result = (*((int (**)(UIStatic *, int))m_pDescription->_base._vftable + 5))(m_pDescription, 1);
    this->m_pDescription = 0;
  }
  v7 = (void *)this->m_pSkillList[0];
  if ( v7 )
  {
    result = (*(int (**)(void *, int))(*(_DWORD *)v7 + 20))(v7, 1);
    this->m_pSkillList[0] = 0;
  }
  v8 = *((_DWORD *)this + 21);
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *((_DWORD *)this + 21) = 0;
  }
  v9 = *((_DWORD *)this + 22);
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *((_DWORD *)this + 22) = 0;
  }
  v10 = *((_DWORD *)this + 23);
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *((_DWORD *)this + 23) = 0;
  }
  v11 = *((_DWORD *)this + 24);
  if ( v11 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *((_DWORD *)this + 24) = 0;
  }
  v12 = *((_DWORD *)this + 25);
  if ( v12 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
    *((_DWORD *)this + 25) = 0;
  }
  v13 = *((_DWORD *)this + 26);
  if ( v13 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
    *((_DWORD *)this + 26) = 0;
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
    ((CCBUI *)*(CCBUI **)(this->_base._base.m_pfather[17].m_fontcolor + 8))->SetParam(a3, a4);
  return a2->SendMessage(a3, a4);
}

// 0x0051C9F0
BOOL CCBSkillWindow::Update(int a2, int a3)
{
  if ( this->_base._base.m_bvisible == 1 && g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 )
    ((CCBUI *)*(CCBUI **)(this->_base._base.m_pfather[17].m_fontcolor + 8))->SetParam(513, -1);
  return ((UIWnd *)&this->_base._base)->HitTest(a2, a3);
}
