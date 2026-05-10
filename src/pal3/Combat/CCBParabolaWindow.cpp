#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBParabolaWindow.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_4425D0(...);

// Unnamed globals (extern)
extern char aUiCombatContro_21[];
extern char aWa001[];
extern int dword_57014C;
extern int dword_570250;
extern int dword_57026C;
extern void *off_570284;
extern void *off_570298;

// 0x0051B710
CCBParabolaWindow::CCBParabolaWindow(int *a2, int a3)
{
  UIWnd ***v4; // edi
  UIWnd ***v5; // ebx
  int i; // edi
  int v7; // eax
  int v8; // ecx

  ((UIWnd *)this)->Create(1879048197, a2, a3);
  *((_DWORD *)this + 30) = (CCBParabolaWindow **)a3;
  v4 = this + 23;
  if ( ((CCBLineupWindow *)this + 23)->Destroy() == 1 )
  {
    *a2 = 0;
    a2[2] = 230;
    a2[1] = 0;
    a2[3] = 250;
    ((void (*)(UIWnd **, int, int *, CCBParabolaWindow ***))(**v4)->m_fontcolor.Alpha)(*v4, 240, a2, this);
    ((UIWnd *)*v4)->CreateFromTemplate(aUiCombatContro_21, 0);
    ((void (*)(UIWnd **, int))(**v4)->m_fontcolor.ColorQuadFmt)(*v4, 1);
  }
  v5 = this + 24;
  for ( i = 0; i < 5; ++i )
  {
    if ( v5->Destroy() )
    {
      v7 = dword_57026C[i];
      v8 = dword_570250[i];
      *a2 = v8;
      a2[1] = v7;
      a2[2] = v8 + 40;
      a2[3] = v7 + 38;
      ((void (*)(UIWnd **, int, int *, CCBParabolaWindow ***))(**v5)->m_fontcolor.Alpha)(
        *v5,
        dword_57014C[i],
        a2,
        this);
      ((UIWnd *)*v5)->CreateFromTemplate(off_570284[i], 0);
      sub_4425D0((gbRefObject **)*v5, off_570298[i], 0);
      ((void (*)(UIWnd **, int))(**v5)->m_fontcolor.ColorQuadFmt)(*v5, 1);
    }
    ++v5;
  }
  1;
}

// 0x0051B810
CCBParabolaWindow::~CCBParabolaWindow()
{
  int result; // eax
  int m_bvisible; // ecx
  int *p_m_benable; // esi
  int v5; // edi

  result = ((UIListBox *)this)->SetScrollPos();
  m_bvisible = this->m_bvisible;
  if ( m_bvisible )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bvisible + 20))(m_bvisible, 1);
    this->m_bvisible = 0;
  }
  p_m_benable = (int *)&this->m_benable;
  v5 = 5;
  do
  {
    if ( *p_m_benable )
    {
      result = (*(int (**)(int, int))(*(_DWORD *)*p_m_benable + 20))(*p_m_benable, 1);
      *p_m_benable = 0;
    }
    ++p_m_benable;
    --v5;
  }
  while ( v5 );
  result;
}

// 0x0051B860
int CCBParabolaWindow::Reset(int a2, int a3, int a4)
{
  char *Instance; // eax

  if ( a2 == 1001 )
  {
    Instance = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(aWa001, 1);
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
  }
  return a2->SendMessage(a3, a4);
}

// 0x0051B920
int CCBParabolaWindow::Destroy()
{
  int v2; // ecx

  ((UIListBox *)this)->SetScroll();
  v2 = *(&this->m_benable + (int)this->m_pItemList);
  return (*(int (**)(int))(*(_DWORD *)v2 + 4))(v2);
}

// 0x0051B950
bool CCBParabolaWindow::OnMessage(int a2, int a3, int a4)
{
  int *v4; // eax
  _DWORD v6[4]; // [esp+8h] [ebp-10h] BYREF

  v4 = ((UIWnd *)*(this + a2 + 24))->SetRect(v6);
  return a3 >= *v4 && a3 < v4[2] && a4 >= v4[1] && a4 < v4[3];
}

// 0x0051B9A0
int CCBParabolaWindow::Update(int a2, int a3)
{
  int v4; // esi
  CCBParabolaWindow **i; // edi

  v4 = 0;
  for ( i = this + 24; (*i)->m_rect.top != 1 || !this->OnMessage(v4, a2, a3); ++i )
  {
    if ( ++v4 >= 5 )
      return -1;
  }
  return v4;
}
