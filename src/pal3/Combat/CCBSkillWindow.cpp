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
  Block->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  (UIWnd *)Block;
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
char CCBSkillWindow::Create(_DWORD *pRect, int parent)
{
  int v3; // ebx
  PtrArray *p_m_childs; // ebx
  LPCSTR *v6; // ebp
  UIStatic **p_m_pBack; // ebx
  CCBSkillWindow *v8; // ebx
  _DWORD *v9; // eax
  CCBSkillWindow *v10; // ebx
  _DWORD *v11; // eax
  CCBSkillWindow *v12; // ebx
  _DWORD *v13; // eax
  CCBSkillWindow *v14; // ebx
  int *p_m_nSize; // ebx
  int *p_m_nMaxSize; // ebx
  int *p_m_nGrowBy; // ebx
  int *p_m_bcreateok; // ebx
  int *p_m_bvisible; // ebx
  int *p_m_benable; // ebx
  int *p_m_bfocus; // ebx
  gbTexture **p_m_pbktex; // ebx
  _DWORD a2[4]; // [esp+C8h] [ebp-10h] BYREF

  v3 = parent;
  this->Create(512, pRect, parent);
  *((_DWORD *)this + 42) = v3;
  p_m_childs = (PtrArray *)&this->m_childs;
  ((CCBLineupWindow *)&this->m_childs.m_pData)->Destroy();
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
  (*(void (**)(void *, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)p_m_childs->m_pData + 16))(
    p_m_childs->m_pData,
    513,
    pRect,
    this);
  ((UIWnd *)this->m_childs.m_pData)->CreateFromTemplate(aUiCombatResult, 0);
  (**(void (***)(void *, int))p_m_childs->m_pData)(p_m_childs->m_pData, 1);
  v6 = (LPCSTR *)off_570310;
  p_m_pBack = &this->m_pBack;
  do
  {
    p_m_pBack->Destroy();
    *pRect = 15;
    pRect[2] = 79;
    pRect[1] = -15;
    pRect[3] = 113;
    (*(void (**)(UIStatic *, int, _DWORD *, CCBSkillWindow *))((*p_m_pBack)->m_fontcolor.ColorQuadFmt + 16))(
      *p_m_pBack,
      528,
      pRect,
      this);
    ((UIWnd *)*p_m_pBack++)->CreateFromTemplate(*v6++, 0);
  }
  while ( (int)v6 < (int)dword_570324 );
  (*(void (**)(UIStatic *, int))this->m_pBack->m_fontcolor.ColorQuadFmt)(this->m_pBack, 1);
  v8 = (CCBSkillWindow *)((char *)this + 156);
  ((CCBLineupWindow *)(_DWORD *)this + 39)->Render();
  *pRect = 83;
  pRect[2] = 168;
  pRect[1] = 46;
  pRect[3] = 58;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)v8->m_fontcolor.ColorQuadFmt + 16))(
    v8->m_fontcolor.ColorQuadFmt,
    545,
    pRect,
    this);
  v9 = ((UIWnd *)*((UIWnd **)this + 39))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 39))->AddChild(v9);
  ((UIWnd *)*((UIWnd ***)this + 39))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 39))->GetChildAt(aUiCombatResult_1, 0);
  sub_43FD90(*((float **)this + 39), 3);
  ((UIWnd *)*((UIWnd **)this + 39))->SetFrameRate(-2);
  (**(void (***)(int, int))v8->m_fontcolor.ColorQuadFmt)(v8->m_fontcolor.ColorQuadFmt, 1);
  v10 = (CCBSkillWindow *)((char *)this + 160);
  ((CCBLineupWindow *)(_DWORD *)this + 40)->Render();
  *pRect = 86;
  pRect[2] = 171;
  pRect[1] = 71;
  pRect[3] = 83;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)v10->m_fontcolor.ColorQuadFmt + 16))(
    v10->m_fontcolor.ColorQuadFmt,
    546,
    pRect,
    this);
  v11 = ((UIWnd *)*((UIWnd **)this + 40))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 40))->AddChild(v11);
  ((UIWnd *)*((UIWnd ***)this + 40))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 40))->GetChildAt(aUiCombatResult_2, 0);
  sub_43FD90(*((float **)this + 40), 3);
  ((UIWnd *)*((UIWnd **)this + 40))->SetFrameRate(-2);
  (**(void (***)(int, int))v10->m_fontcolor.ColorQuadFmt)(v10->m_fontcolor.ColorQuadFmt, 1);
  v12 = (CCBSkillWindow *)((char *)this + 164);
  ((CCBLineupWindow *)(_DWORD *)this + 41)->Render();
  *pRect = 84;
  pRect[2] = 169;
  pRect[1] = 97;
  pRect[3] = 109;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)v12->m_fontcolor.ColorQuadFmt + 16))(
    v12->m_fontcolor.ColorQuadFmt,
    547,
    pRect,
    this);
  v13 = ((UIWnd *)*((UIWnd **)this + 41))->SetRect(a2);
  ((UIWnd *)*((UIWnd **)this + 41))->AddChild(v13);
  ((UIWnd *)*((UIWnd ***)this + 41))->GetChildCount(aUiCombatResult_4, 0);
  ((UIWnd *)*((UIWnd ***)this + 41))->GetChildAt(aUiCombatResult_3, 0);
  sub_43FD90(*((float **)this + 41), 3);
  ((UIWnd *)*((UIWnd **)this + 41))->SetFrameRate(-2);
  (**(void (***)(int, int))v12->m_fontcolor.ColorQuadFmt)(v12->m_fontcolor.ColorQuadFmt, 1);
  v14 = (CCBSkillWindow *)((char *)this + 152);
  ((CCBLineupWindow *)(_DWORD *)this + 38)->Destroy();
  *pRect = 66;
  pRect[2] = 130;
  pRect[1] = 42;
  pRect[3] = 109;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)v14->m_fontcolor.ColorQuadFmt + 16))(
    v14->m_fontcolor.ColorQuadFmt,
    544,
    pRect,
    this);
  ((UIWnd *)*((UIWnd ***)this + 38))->CreateFromTemplate(aUiCombatResult_5, 0);
  (**(void (***)(int, int))v14->m_fontcolor.ColorQuadFmt)(v14->m_fontcolor.ColorQuadFmt, 1);
  p_m_nSize = (int *)&this->m_childs.m_nSize;
  parent = -1;
  ((CCBLineupWindow *)&this->m_childs.m_nSize)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 134;
  pRect[3] = 166;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_m_nSize + 16))(
    *p_m_nSize,
    514,
    pRect,
    this);
  (**(void (***)(int, int))*p_m_nSize)(*p_m_nSize, 1);
  ((UIWnd *)this->m_childs.m_nSize)->SetShow(0);
  ((UIWnd *)this->m_childs.m_nSize)->GetChild((int)&parent);
  p_m_nMaxSize = (int *)&this->m_childs.m_nMaxSize;
  ((CCBLineupWindow *)&this->m_childs.m_nMaxSize)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 134;
  pRect[3] = 166;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_m_nMaxSize + 16))(
    *p_m_nMaxSize,
    515,
    pRect,
    this);
  (**(void (***)(int, int))*p_m_nMaxSize)(*p_m_nMaxSize, 1);
  ((UIWnd *)this->m_childs.m_nMaxSize)->SetShow(0);
  ((UIWnd *)this->m_childs.m_nMaxSize)->GetChild((int)&parent);
  p_m_nGrowBy = (int *)&this->m_childs.m_nGrowBy;
  ((CCBLineupWindow *)&this->m_childs.m_nGrowBy)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 108;
  pRect[3] = 140;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_m_nGrowBy + 16))(
    *p_m_nGrowBy,
    516,
    pRect,
    this);
  (**(void (***)(int, int))*p_m_nGrowBy)(*p_m_nGrowBy, 1);
  ((UIWnd *)this->m_childs.m_nGrowBy)->SetShow(0);
  ((UIWnd *)this->m_childs.m_nGrowBy)->GetChild((int)&parent);
  p_m_bcreateok = (int *)&this->m_bcreateok;
  ((CCBLineupWindow *)&this->m_bcreateok)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 108;
  pRect[3] = 140;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_m_bcreateok + 16))(
    *p_m_bcreateok,
    517,
    pRect,
    this);
  (**(void (***)(int, int))*p_m_bcreateok)(*p_m_bcreateok, 1);
  ((UIWnd *)this->m_bcreateok)->SetShow(0);
  ((UIWnd *)this->m_bcreateok)->GetChild((int)&parent);
  p_m_bvisible = (int *)&this->m_bvisible;
  ((CCBLineupWindow *)&this->m_bvisible)->Destroy();
  pRect[2] = 115;
  *pRect = 51;
  pRect[1] = 160;
  pRect[3] = 192;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_m_bvisible + 16))(
    *p_m_bvisible,
    518,
    pRect,
    this);
  (**(void (***)(int, int))*p_m_bvisible)(*p_m_bvisible, 1);
  ((UIWnd *)this->m_bvisible)->SetShow(0);
  ((UIWnd *)this->m_bvisible)->GetChild((int)&parent);
  p_m_benable = (int *)&this->m_benable;
  ((CCBLineupWindow *)&this->m_benable)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 160;
  pRect[3] = 192;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_m_benable + 16))(
    *p_m_benable,
    519,
    pRect,
    this);
  (**(void (***)(int, int))*p_m_benable)(*p_m_benable, 1);
  ((UIWnd *)this->m_benable)->SetShow(0);
  ((UIWnd *)this->m_benable)->GetChild((int)&parent);
  p_m_bfocus = (int *)&this->m_bfocus;
  ((CCBLineupWindow *)&this->m_bfocus)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 211;
  pRect[3] = 243;
  (*(void (**)(int, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)*p_m_bfocus + 16))(
    *p_m_bfocus,
    529,
    pRect,
    this);
  (**(void (***)(int, int))*p_m_bfocus)(*p_m_bfocus, 1);
  ((UIWnd *)this->m_bfocus)->SetShow(0);
  ((UIWnd *)this->m_bfocus)->GetChild((int)&parent);
  p_m_pbktex = &this->m_pbktex;
  ((CCBLineupWindow *)&this->m_pbktex)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 0;
  pRect[3] = 32;
  (*(void (**)(gbTexture *, int, _DWORD *, CCBSkillWindow *))(*(_DWORD *)(*p_m_pbktex)->_pad_0000 + 16))(
    *p_m_pbktex,
    530,
    pRect,
    this);
  (**(void (***)(gbTexture *, int))(*p_m_pbktex)->_pad_0000)(*p_m_pbktex, 1);
  ((UIWnd *)this->m_pbktex)->SetShow(0);
  ((UIWnd *)this->m_pbktex)->GetChild((int)&parent);
  return 1;
}

// 0x0051C880
int CCBSkillWindow::Destroy()
{
  int result; // eax
  UIStatic **p_m_pBack; // edi
  int v4; // ebx
  void *m_pData; // ecx
  int m_nSize; // ecx
  int m_nMaxSize; // ecx
  int m_nGrowBy; // ecx
  int m_bcreateok; // ecx
  int m_bvisible; // ecx
  int m_benable; // ecx
  int m_bfocus; // ecx
  gbTexture *m_pbktex; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  p_m_pBack = &this->m_pBack;
  v4 = 11;
  do
  {
    if ( *p_m_pBack )
    {
      result = (*(int (**)(UIStatic *, int))((*p_m_pBack)->m_fontcolor.ColorQuadFmt + 20))(*p_m_pBack, 1);
      *p_m_pBack = 0;
    }
    ++p_m_pBack;
    --v4;
  }
  while ( v4 );
  m_pData = (void *)this->m_childs.m_pData;
  if ( m_pData )
  {
    result = (*(int (**)(void *, int))(*(_DWORD *)m_pData + 20))(m_pData, 1);
    this->m_childs.m_pData = 0;
  }
  m_nSize = this->m_childs.m_nSize;
  if ( m_nSize )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nSize + 20))(m_nSize, 1);
    this->m_childs.m_nSize = 0;
  }
  m_nMaxSize = this->m_childs.m_nMaxSize;
  if ( m_nMaxSize )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nMaxSize + 20))(m_nMaxSize, 1);
    this->m_childs.m_nMaxSize = 0;
  }
  m_nGrowBy = this->m_childs.m_nGrowBy;
  if ( m_nGrowBy )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nGrowBy + 20))(m_nGrowBy, 1);
    this->m_childs.m_nGrowBy = 0;
  }
  m_bcreateok = this->m_bcreateok;
  if ( m_bcreateok )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bcreateok + 20))(m_bcreateok, 1);
    this->m_bcreateok = 0;
  }
  m_bvisible = this->m_bvisible;
  if ( m_bvisible )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bvisible + 20))(m_bvisible, 1);
    this->m_bvisible = 0;
  }
  m_benable = this->m_benable;
  if ( m_benable )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_benable + 20))(m_benable, 1);
    this->m_benable = 0;
  }
  m_bfocus = this->m_bfocus;
  if ( m_bfocus )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bfocus + 20))(m_bfocus, 1);
    this->m_bfocus = 0;
  }
  m_pbktex = (gbTexture *)this->m_pbktex;
  if ( m_pbktex )
  {
    result = (*(int (**)(gbTexture *, int))(*(_DWORD *)m_pbktex->_pad_0000 + 20))(m_pbktex, 1);
    this->m_pbktex = 0;
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
