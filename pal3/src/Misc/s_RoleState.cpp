#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/s_RoleState.h"

void CopyRoleData(int pDst, int pSrc); // from annotations

// 0x004A3A90
int s_RoleState::LoadAndSetupRole()
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int result; // eax
  float fValue; // [esp+0x0] [ebp-0x1C]
  float fValuea; // [esp+0x0] [ebp-0x1C]
  float fValueb; // [esp+0x0] [ebp-0x1C]
  float fValuec; // [esp+0x0] [ebp-0x1C]
  float fValued; // [esp+0x0] [ebp-0x1C]
  float fValuee; // [esp+0x0] [ebp-0x1C]

  *(_DWORD *)this->m_Headbk.m_text = 0;
  do
  {
    v2 = *(_DWORD *)this->m_Headbk.m_text;
    if ( *((_BYTE *)&this->m_Name.m_bvisible + v2 + 1) )
    {
      ((RoleSystem *)((char *)&Buffer + 1408 * v2))->RecalcAggregatedStats(0);
      fValue = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)this->m_Headbk.m_text + 9];
      ((UIScrollBar *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 155748))->SetRange(fValue);
      v3 = *(_DWORD *)this->m_Headbk.m_text;
      fValuea = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v3 + 10];
      ((UIScrollBar *)((char *)this + 3788 * v3 + 156844))->SetRange(fValuea);
      v4 = *(_DWORD *)this->m_Headbk.m_text;
      fValueb = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v4 + 11];
      ((UIScrollBar *)((char *)this + 3788 * v4 + 156296))->SetRange(fValueb);
      v5 = *(_DWORD *)this->m_Headbk.m_text;
      fValuec = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v5 + 39];
      ((UIProgressBar *)((char *)this + 3788 * v5 + 155748))->FindChildByName(fValuec);
      v6 = *(_DWORD *)this->m_Headbk.m_text;
      fValued = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v6 + 43];
      ((UIProgressBar *)((char *)this + 3788 * v6 + 156844))->FindChildByName(fValued);
      v7 = *(_DWORD *)this->m_Headbk.m_text;
      fValuee = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v7 + 47];
      ((UIProgressBar *)((char *)this + 3788 * v7 + 156296))->FindChildByName(fValuee);
      sprintf(
        &this->m_Headbk.m_text[8],
        "%d/%d",
        (int)*((float *)this + 947 * *(_DWORD *)this->m_Headbk.m_text + 38976),
        Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)this->m_Headbk.m_text + 9]);
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 155992))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
      sprintf(
        &this->m_Headbk.m_text[8],
        "%d/%d",
        (int)*((float *)this + 947 * *(_DWORD *)this->m_Headbk.m_text + 39250),
        Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)this->m_Headbk.m_text + 10]);
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 157088))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
      sprintf(
        &this->m_Headbk.m_text[8],
        "%d/%d",
        (int)*((float *)this + 947 * *(_DWORD *)this->m_Headbk.m_text + 39113),
        Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)this->m_Headbk.m_text + 11]);
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 156540))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
      sprintf(
        &this->m_Headbk.m_text[8],
        &dir[20],
        *((_DWORD *)&Buffer.m_partyActor.m_fNormZ + 352 * *(_DWORD *)this->m_Headbk.m_text));
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 158000))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
      sprintf(
        &this->m_Headbk.m_text[8],
        &dir[20],
        *((_DWORD *)&Buffer.m_partyActor.m_fDistAccum + 352 * *(_DWORD *)this->m_Headbk.m_text));
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 158152))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
      sprintf(
        &this->m_Headbk.m_text[8],
        &dir[20],
        *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 352 * *(_DWORD *)this->m_Headbk.m_text + 1));
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 158456))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
      sprintf(
        &this->m_Headbk.m_text[8],
        &dir[20],
        *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 352 * *(_DWORD *)this->m_Headbk.m_text));
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 158304))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
      sprintf(
        &this->m_Headbk.m_text[8],
        &dir[20],
        *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 352 * *(_DWORD *)this->m_Headbk.m_text + 2));
      ((UICaption *)((char *)this + 3788 * *(_DWORD *)this->m_Headbk.m_text + 158608))->SetEnable((int)&this->m_Headbk.m_text[8], 0);
    }
    result = *(_DWORD *)this->m_Headbk.m_text + 1;
    *(_DWORD *)this->m_Headbk.m_text = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0052FA50
gbVFileSystem * s_RoleState::LoadSkeletonModel()
{
  gbVFileSystem *result; // eax
  OpenBaseFile v3; // [esp+0x10] [ebp-0x10] BYREF
  int v4; // [esp+0x1C] [ebp-0x4]

  v4 = 0;
  ((gbGeomNode *)&this->m_WuLing[3].m_rect.top)->LoadFromFile("SubGame\\Skee\\SkeeScene\\Ball\\Ball.pol", 0, 0);
  ((gbGeomNode *)&this->m_WuLing[3].m_rect.top)->GetOBBox((gbOBBox *)&this->m_FWSY.m_pfather);
  ((UICoverFrm *)&this->m_FWSY.m_disablepic)->LoadFromFile(aBasedataSkeePa);
  *(_DWORD *)&this->m_FWSY.m_text[12] = 0;
  this->m_FWSY.m_pbkInfo = 0;
  this->m_FWSY.m_ppic = 0;
  this->m_FWSY.m_pbk = (gbTexture *)1093517967;
  *(_DWORD *)&this->m_FWSY.m_mouseoff = 0;
  LOBYTE(this->m_FWSY.m_ppicInfo) = 0;
  v4 = -1;
  return result;
}

// 0x0052FB00
char s_RoleState::CopyRoleData(int nVal, char pData)
{
  char *v3; // eax

  v3 = (char *)this->m_FWSY.m_disablepicInfo + 32 * nVal;
  *(_DWORD *)&this->m_FWSY.m_text[12] = *((_DWORD *)v3 + 3);
  this->m_FWSY.m_wndcolor.Color = *(_DWORD *)v3;
  this->m_FWSY.m_id = (void *)*((_DWORD *)v3 + 1);
  this->m_FWSY.m_rect.left = *((_DWORD *)v3 + 2);
  this->m_WuLing[4].m_nTextW = this->m_FWSY.m_wndcolor.Color;
// [VFTABLE] this->m_FWSY.__vftable = (vtbl_0056AE2C *)this->m_FWSY.m_id;
  this->m_FWSY.m_fontcolor.Color = this->m_FWSY.m_rect.left;
  LOBYTE(this->m_FWSY.m_ppicInfo) = pData;
  return pData;
}
