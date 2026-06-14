#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UISceneFace.h"

// Unnamed globals (extern)
extern RoleSystem stru_C059A0;

// 0x0052D010
int UISceneFace::SetFaceVisible(int nVal, unsigned int dwVal)
{
  char *v4; // edi
  int result; // eax

  v4 = (char *)this + 1552 * nVal;
  (**((void ( ***)(int, _DWORD))v4 + 606))((int)(v4 + 2424), (unsigned __int8)dwVal);
  (**((void ( ***)(int, _DWORD))v4 + 644))((int)(v4 + 2576), (unsigned __int8)dwVal);
  (**((void ( ***)(int, _DWORD))v4 + 682))((int)(v4 + 2728), (unsigned __int8)dwVal);
  (**((void ( ***)(int, _DWORD))v4 + 720))((int)(v4 + 2880), (unsigned __int8)dwVal);
  (**((void ( ***)(int, _DWORD))v4 + 758))((int)(v4 + 3032), (unsigned __int8)dwVal);
  (**((void ( ***)(int, _DWORD))v4 + 819))((int)(v4 + 3276), (unsigned __int8)dwVal);
  (**((void ( ***)(int, _DWORD))v4 + 857))((int)(v4 + 3428), (unsigned __int8)dwVal);
  (**((void ( ***)(int, _DWORD))v4 + 895))((int)(v4 + 3580), (unsigned __int8)dwVal);
  result = (**((int ( ***)(int, _DWORD))v4 + 956))((int)(v4 + 3824), (unsigned __int8)dwVal);
  LOBYTE(result) = dwVal;
  *((_BYTE *)this + nVal + 10201) = dwVal;
  return result;
}

// 0x0052D0D0
int UISceneFace::ResetAllSlots()
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 5; ++i )
    result = this->SetFaceVisible(i, 0);
  return result;
}

// 0x0052D0F0
int UISceneFace::UpdateFacePosition()
{
  UISceneFace *v1; // ebx
  int result; // eax
  int v3; // ebp
  int *p_m_bChangedMat; // edi
  char *p_m_ratioh; // esi
  float fValue; // [esp+0x0] [ebp-0x28]
  float fValuea; // [esp+0x0] [ebp-0x28]
  float fValueb; // [esp+0x0] [ebp-0x28]
  float fValuec; // [esp+0x0] [ebp-0x28]
  int v11; // [esp+0x18] [ebp-0x10]
  int v12; // [esp+0x20] [ebp-0x8]
result = 0;
  v12 = 192;
  v3 = 0;
  p_m_bChangedMat = (int *)&Buffer.m_partyActor.m_bChangedMat;
  p_m_ratioh = (char *)&v1[1].m_state[0].m_ratioh;
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v3) )
    {
      ((UIScenePanel *)v1)->LayoutSlot(v3, result, 0, v12, 256);
      ((UISceneFace *)v1)->SetFaceVisible(v3, 1u);
      v11 = v12 + 10;
      v12 += 202;
      ((UIListBox *)p_m_ratioh)->GetCurSel();
      fValue = (float)*(p_m_bChangedMat - 2);
      ((UIScrollBar *)p_m_ratioh)->SetRange(fValue);
      *((_DWORD *)p_m_ratioh + 28) = 1065353216;
      ((UIListBox *)(p_m_ratioh + 548))->GetCurSel();
      fValuea = (float)*p_m_bChangedMat;
      ((UIScrollBar *)(p_m_ratioh + 548))->SetRange(fValuea);
      *((_DWORD *)p_m_ratioh + 165) = 1065353216;
      fValueb = (float)p_m_bChangedMat[10];
      ((UIProgressBar *)p_m_ratioh)->FindChildByName(fValueb);
      fValuec = (float)p_m_bChangedMat[12];
      ((UIProgressBar *)(p_m_ratioh + 548))->FindChildByName(fValuec);
      result = v11;
}
    p_m_bChangedMat += 352;
    ++v3;
    p_m_ratioh += 1552;
  }
  while ( (int)p_m_bChangedMat < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[210] );
  BYTE1(this->m_bk.m_FVF) = 1;
  return result;
}
