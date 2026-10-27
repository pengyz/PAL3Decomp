#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/MagicUI.h"
#include "Misc/LineupComp.h"
#include "Misc/UIBigMap.h"
#include "Misc/UITitle_XJTM.h"

// 0x00484ED0
int MagicUI::SelectTab3(unsigned __int8 nTab)
{
  this->remarkbuf[84] = nTab;
  return (((LineupComp *)this))->LineupComp::DispatchSlotMethod(3, nTab);
}

// 0x00484EF0
int MagicUI::SelectTab4(unsigned __int8 nTab)
{
  this->remarkbuf[85] = nTab;
  return (((LineupComp *)this))->LineupComp::DispatchSlotMethod(4, nTab);
}

// 0x0048A350
int MagicUI::SelectSubTab3(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][1].m_Data[28] = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState(3, nTab);
}

// 0x0048A370
int MagicUI::SelectSubTab4(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][1].m_Data[29] = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState(4, nTab);
}

// 0x00494620
int MagicUI::SelectBigMapTab3(char nTab)
{
  this->remarkbuf[84] = nTab;
  return (((UIBigMap *)this))->UIBigMap::SetEntryVisible(3, nTab);
}

// 0x00494640
int MagicUI::SelectBigMapTab4(char nTab)
{
  this->remarkbuf[85] = nTab;
  return (((UIBigMap *)this))->UIBigMap::SetEntryVisible(4, nTab);
}

// 0x0049E8A0
int MagicUI::SelectXJTMTab3(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][0].m_Data[32] = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState2(3, nTab);
}

// 0x0049E8C0
int MagicUI::SelectXJTMTab4(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][0].m_Data[33] = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState2(4, nTab);
}

// 0x00551C66
void MagicUI::InitComItem(int nVal1)
{
  __m64 v1; // mm1
  __m64 v2; // mm2
  __m64 v3; // mm2
  __m64 *v4; // [esp+0x8] [ebp+0x8]
  __m64 *v5; // [esp+0xC] [ebp+0xC]

  _m_femms();
  v1 = _mm_cvtsi32_si64(v5[1].m64_i64);
  v2 = _m_pfmul((__m64)v4->m64_i64, (__m64)v5->m64_i64);
  v3 = _m_pfadd(_m_pfacc(v2, v2), _m_pfmul(_mm_cvtsi32_si64(v4[1].m64_i64), v1));
  *(__m64 *)nVal1 = (__m64)v5->m64_i64;
  *(_DWORD *)(nVal1 + 8) = _mm_cvtsi64_si32(v1);
  *(_DWORD *)(nVal1 + 12) = _mm_cvtsi64_si32(_m_pxor(v3, (__m64)0x80000000i64));
  _m_femms();
}
