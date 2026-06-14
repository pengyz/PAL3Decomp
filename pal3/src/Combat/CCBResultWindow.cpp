#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBResultWindow.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations

// 0x0043BE30
void CCBResultWindow::_CCBResultWindow()
{
  ((UIScene *)this)->ReleaseTexture();
// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x00442E10
void CCBResultWindow::ctor()
{
  sub_4422E0(this);
  this->m_pMP = (UIProgressBar *)1056964608;
  this->m_pHGM = 0;
  this->m_pHP = 0;
  this->m_pGP = 0;
  this->m_pUI = 0;
  LOBYTE(this->m_nIndex) = 0;
  *(_DWORD *)&this->m_bClosed = 0;
  this->m_pFace[9] = (UIStatic *)21;
}

// 0x00443190
void CCBResultWindow::Create()
{

}

// 0x00444A20
CCBResultWindow::CCBResultWindow()
{
  UIProgressBar *m_pHGM_high; // eax

  sub_4422E0(this);
  this->m_pUI = (CCBUI *)1065353216;
  LOBYTE(this->m_nIndex) = 0;
  BYTE1(this->m_nIndex) = 0;
  BYTE2(this->m_nIndex) = 0;
  *(_DWORD *)&this->m_bClosed = 0;
  this->m_pMP = (UIProgressBar *)6;
  this->m_pHGM = (UIStatic *)-1;
  m_pHGM_high = (UIProgressBar *)HIBYTE(this->m_pHGM);
  this->m_pGP = m_pHGM_high;
  this->m_pHP = m_pHGM_high;
}

// 0x00444D10
int CCBResultWindow::StartAnim()
{
  int result; // eax

  BYTE1(this->m_nIndex) = 1;
  BYTE2(this->m_nIndex) = 0;
  return result;
}

// 0x00444D20
void CCBResultWindow::SetDirty()
{
  BYTE2(this->m_nIndex) = 1;
}

// 0x00515CE0
int CCBResultWindow::FindChildByID(int nID)
{
  int result; // eax
  int v3; // edx

  result = (int)&this->m_pUI;
  v3 = 0;
  while ( !*(_BYTE *)(result + 20) || *(_DWORD *)result != nID )
  {
    ++v3;
    result += 88;
    if ( v3 >= 1024 )
    {
      LOBYTE(result) = 0;
      return result;
    }
  }
  LOBYTE(result) = 1;
  return result;
}

// 0x00519360
void CCBResultWindow::ShowLineupWindow(BOOL bShow)
{
  ((CCBUI *)this)->Release();
  if ( bShow )
    operator delete(this);
}

// 0x00519660
BOOL CCBResultWindow::IsImbibeNimbusNotFinish(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(g_nSkillItemIDTable[15], -1);
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x0051F0A0
void CCBResultWindow::Reset()
{
  int v2; // eax
  const void *v3; // esi
  int v4; // edx
  int v5; // eax
  PalScriptMgr *v6; // ecx
  int v7; // edx
  char *pszScene; // [esp+0x10] [ebp+0x4]
  int a3; // [esp+0x14] [ebp+0x8]

  v2 = *((_DWORD *)this + 2011);
  v3 = (const void *)*((_DWORD *)this + 2012);
  v4 = *((_DWORD *)this + 82011);
  *((_DWORD *)this + 86393) = *((_DWORD *)this + 82005);
  *((_DWORD *)this + 86395) = v2;
  v5 = *((_DWORD *)this + 82008);
  qmemcpy((char *)this + 345584, v3, 0xDCu);
  v6 = (PalScriptMgr *)*((_DWORD *)this + 82009);
  *((_DWORD *)this + 126858) = v4;
  v7 = *((_DWORD *)this + 82010);
  *((_DWORD *)this + 126855) = v5;
  *((_DWORD *)this + 126856) = v6;
  *((_DWORD *)this + 126857) = v7;
  ((PalScriptMgr *)v6)->RunSceneScript(pszScene);
  ((UIListBox *)this)->Update((int)pszScene, a3);
}
