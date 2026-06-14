#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBLineupWindow.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations

// Unnamed globals (extern)
extern unsigned int unk_5DFDEC;

// 0x0051CFB0
CCBLineupWindow::CCBLineupWindow(CCBControlWindow **a2)
{
  CCBControlWindow *v2; // eax
  CCBControlWindow *Button; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v6; // [esp+0x80C] [ebp-0x4]

  v2 = (CCBControlWindow *)operator new(0x80u);
  v6 = 0;
  if ( v2 )
    Button = (CCBControlWindow *)((CCBControlWindow *)v2)->CreateButton();
  else
    Button = 0;
  v6 = -1;
  *a2 = Button;
  if ( !Button )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x0051D070
void CCBLineupWindow::_CCBLineupWindow(CCBItemWindow **a2)
{
  CCBItemWindow *v2; // eax
  CCBItemWindow *v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v6; // [esp+0x80C] [ebp-0x4]

  v2 = (CCBItemWindow *)operator new(0x7Cu);
  v6 = 0;
  if ( v2 )
    v3 = (CCBItemWindow *)((CCBItemWindow *)v2)->Update();
  else
    v3 = 0;
  v6 = -1;
  *a2 = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x0051D120
void CCBLineupWindow::Reset(CCBMagicWindow **a2)
{
  CCBMagicWindow *v2; // eax
  CCBMagicWindow *v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v6; // [esp+0x80C] [ebp-0x4]

  v2 = (CCBMagicWindow *)operator new(0x68u);
  v6 = 0;
  if ( v2 )
    v3 = (CCBMagicWindow *)((CCBMagicWindow *)v2)->ForbidPage();
  else
    v3 = 0;
  v6 = -1;
  *a2 = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x0051D1D0
char CCBLineupWindow::Create@<al>(CCBLineupWindow *this@<ecx>, int a3)
{
  CCBMagicWindow *v3; // eax
  UIListBox *ActivePage; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v8; // [esp+0x80C] [ebp-0x4]

  v3 = (CCBMagicWindow *)operator new(0xB4u);
  v8 = 0;
  if ( v3 )
    ActivePage = ((CCBMagicWindow *)v3)->GetActivePage();
  else
    ActivePage = 0;
  v8 = -1;
  a2->left = (LONG)ActivePage;
  if ( !ActivePage )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 1660),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D290
void CCBLineupWindow::Destroy()
{
  void *v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v5; // [esp+0x80C] [ebp-0x4]
  _DWORD *v6; // [esp+0x814] [ebp+0x4]

  v1 = operator new(0x98u);
  v5 = 0;
  if ( v1 )
    sub_4422E0(v1);
  else
    v2 = 0;
  v5 = -1;
  *v6 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x0051D340
char CCBLineupWindow::OnMessage(int *msg)
{
  UIStatic *v2; // eax
  int v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v7; // [esp+0x80C] [ebp-0x4]

  v2 = (UIStatic *)operator new(0xF8u);
  v7 = 0;
  if ( v2 )
  {
  }
  else
    v3 = 0;
  v7 = -1;
  *msg = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D3F0
char CCBLineupWindow::Update(int *deltatime)
{
  NameSys *Sys; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v6; // [esp+0x80C] [ebp-0x4]

  v6 = 0;
  if ( operator new(0x158u) )
    Sys = UIScene::GetSys();
  else
    Sys = 0;
  v6 = -1;
  *deltatime = (int)Sys;
  if ( !Sys )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D4A0
char CCBLineupWindow::Render(int *p_DWORD)
{
  UIButton *v2; // eax
  int *v3; // eax
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x404] [ebp-0x40C] BYREF
  int v7; // [esp+0x80C] [ebp-0x4]

  v2 = (UIButton *)operator new(0xF4u);
  v7 = 0;
  if ( v2 )
    v3 = ((UIButton *)v2)->ctor_17();
  else
    v3 = 0;
  v7 = -1;
  *p_DWORD = (int)v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 4346),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x0051D580
// attributes: thunk
int CCBLineupWindow::IsPtOnFace()
{
  return this->IsPtOnFace_d590();
}

// 0x0051D590
int CCBLineupWindow::IsPtOnFace_d590()
{
  *(_DWORD *)&g_TempBuffer1024[908] = 1094713344;
  return 1094713344;
}

// 0x0051D5A0
// attributes: thunk
void CCBLineupWindow::IsPtOnInitPos()
{

}

// 0x0051D5B0
void CCBLineupWindow::IsPtOnInitPos_d5b0()
{
  *(float *)&g_TempBuffer1024[904] = 12.0 + 12.0;
}

// 0x0051D5F0
char CCBLineupWindow::IsFaceOnInitPos()
{
  unk_5DFDEC = timeGetTime();
  *(_DWORD *)&g_TempBuffer1024[912] = 0;
  return 1;
}

// 0x0051D610
char CCBLineupWindow::SetFaceLineup(
        int nVal,
        int nFaceIndex,
        int nPosIndex,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        int nVal6,
        int *p_DWORD)
{
  if ( nVal > nVal5 || nVal3 > nPosIndex || nFaceIndex > nVal6 || nVal4 > nVal2 )
    return 0;
  if ( nVal <= nVal3 )
    *p_DWORD = nVal3;
  else
    *p_DWORD = nVal;
  if ( nPosIndex >= nVal5 )
    p_DWORD[2] = nVal5;
  else
    p_DWORD[2] = nPosIndex;
  if ( nFaceIndex <= nVal4 )
    p_DWORD[1] = nVal4;
  else
    p_DWORD[1] = nFaceIndex;
  if ( nVal2 >= nVal6 )
    p_DWORD[3] = nVal6;
  else
    p_DWORD[3] = nVal2;
  return 1;
}

// 0x0051D6D0
// attributes: thunk
CCBProtectWindow * CCBLineupWindow::RefreshFacePos()
{
  CCBProtectWindow *result; // eax

  return result;
}
