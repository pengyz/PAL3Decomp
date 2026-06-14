#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBAIWindow.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations

// 0x0051CB60
void CCBAIWindow::Reset(int *p_DWORD)
{
  void *v2; // eax
  int v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v6; // [esp+0x80C] [ebp-0x4]

  v2 = operator new(0x98u);
  v6 = 0;
  if ( v2 )
    sub_4422E0(v2);
  else
    v3 = 0;
  v6 = -1;
  *p_DWORD = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x0051CCE0
void CCBAIWindow::Destroy()
{
  CCBUI *v1; // eax
  int *v2; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v5; // [esp+0x80C] [ebp-0x4]
  int **v6; // [esp+0x814] [ebp+0x4]

  v1 = (CCBUI *)operator new(0x74u);
  v5 = 0;
  if ( v1 )
    v2 = ((CCBUI *)v1)->ctor();
  else
    v2 = 0;
  v5 = -1;
  *v6 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x0051CD90
char CCBAIWindow::OnMessage(UIListBox **msg)
{
  UIListBox *v2; // eax
  CCBUI *v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v7; // [esp+0x80C] [ebp-0x4]

  v2 = (UIListBox *)operator new(0x6Cu);
  v7 = 0;
  if ( v2 )
    v3 = ((UIListBox *)v2)->InitAndRender();
  else
    v3 = 0;
  v7 = -1;
  *msg = (UIListBox *)v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CE40
char CCBAIWindow::Update(CCBUI **deltatime)
{
  CCBUI *v2; // eax
  CCBUI *v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v7; // [esp+0x80C] [ebp-0x4]

  v2 = (CCBUI *)operator new(0x80u);
  v7 = 0;
  if ( v2 )
    v3 = (CCBUI *)((CCBUI *)v2)->ChangeNumTxt();
  else
    v3 = 0;
  v7 = -1;
  *deltatime = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051CF00
char CCBAIWindow::ShowWindow(CCBControlWindow **show)
{
  CCBControlWindow *v2; // eax
  CCBControlWindow *v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v7; // [esp+0x80C] [ebp-0x4]

  v2 = (CCBControlWindow *)operator new(0x54u);
  v7 = 0;
  if ( v2 )
    v3 = (CCBControlWindow *)((CCBControlWindow *)v2)->DefaultKey();
  else
    v3 = 0;
  v7 = -1;
  *show = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}
