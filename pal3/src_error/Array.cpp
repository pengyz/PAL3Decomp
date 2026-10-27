#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/Array.h"
#include "Role/Actor.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Effect/CEffgbParticle.h"
#include "Render/CScreenMode.h"
#include "Misc/Comp_DonateUI.h"
#include "UI/EquipUI.h"
#include "Misc/MUIDialog.h"
#include "Misc/MainEquipUI.h"
#include "Role/NPC.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneMgr.h"
#include "Script/ScriptSystem.h"
#include "UI/StateUI.h"
#include "Misc/UICaption.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIRoleSelect.h"
#include "Misc/UIScrollBar.h"
#include "UI/UIWnd.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/scVarStack.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
void __cdecl nullsub_2(...);

// 0x00410960
void Array::Free()
{
  operator delete((void *)this->m_nSize);
  this->m_nSize = 0;
  this->m_pData = ((char *)0);
  this->m_nCapacity = 0;
}

// 0x00410BD0
int Array::InsertAt(char *pPos, int *pSrc)
{
  char *v3; // edi
  int m_nSize; // ebx
  char *m_pData; // ecx
  unsigned int v7; // ebp
  int v8; // edx
  unsigned int v9; // eax
  char *v10; // eax
  int v11; // ebx
  char *k; // ebp
  int v13; // eax
  char *v14; // ecx
  char *j; // eax
  _DWORD *v16; // edi
  char *v17; // ecx
  char *i; // eax
  _DWORD *v19; // ebx
  int v21; // [esp+0x10] [ebp-0x8]
  int v22; // [esp+0x14] [ebp-0x4]
  char *pPosa; // [esp+0x1C] [ebp+0x4]

  v3 = (char *)pPos;
  m_nSize = this->m_nSize;
  m_pData = (char *)this->m_pData;
  v22 = (int)&pPos[-m_nSize] / 12;
  if ( (this->m_nCapacity - (int)m_pData) / 12 )
  {
    if ( (m_pData - pPos) / 12 )
    {
      this->Array::Insert(m_pData - 12, m_pData);
      v17 = (char *)this->m_pData;
      for ( i = v17 - 12; i != pPos; *((_DWORD *)v17 + 2) = *((_DWORD *)i + 2) )
      {
        i -= 12;
        v17 -= 12;
        *(_DWORD *)v17 = *(_DWORD *)i;
        *((_DWORD *)v17 + 1) = *((_DWORD *)i + 1);
      }
      do
      {
        v19 = (_DWORD *)v3;
        v3 += 12;
        *v19 = *pSrc;
        v19[1] = (unsigned long)pSrc[1];
        v19[2] = (unsigned long)pSrc[2];
      }
      while ( v3 != pPos + 12 );
    }
    else
    {
      this->Array::Insert(pPos, m_pData);
      this->Array::Erase((int)this->m_pData, 1 - (this->m_pData - pPos) / 12);
      v14 = (char *)this->m_pData;
      for ( j = pPos; j != v14; v16[2] = (unsigned long)pSrc[2] )
      {
        v16 = (_DWORD *)j;
        j += 12;
        *v16 = *pSrc;
        v16[1] = (unsigned long)pSrc[1];
      }
    }
    this->m_pData += 12;
  }
  else
  {
    if ( !m_nSize || (v7 = (int)&m_pData[-m_nSize] / 12, v7 <= 1) )
      v7 = 1;
    if ( m_nSize )
      v8 = (int)&m_pData[-m_nSize] / 12;
    else
      v8 = 0;
    v9 = v8 + v7;
    pPosa = (char *)(v8 + v7);
    if ( (int)(v8 + v7) < 0 )
      v9 = 0;
    v10 = (char *)operator new(12 * v9);
    v11 = this->m_nSize;
    v21 = (int)v10;
    for ( k = v10; (char *)v11 != v3; k += 12 )
    {
      Array::Copy(k);
      v11 += 12;
    }
    Array::Copy(k);
    this->Array::Insert(v3, this->m_pData);
    nullsub_2(this->m_nSize, this->m_pData);
    operator delete((void *)this->m_nSize);
    this->m_nCapacity = v21 + 12 * (_DWORD)pPosa;
    v13 = this->Array::Size();
    this->m_nSize = v21;
    this->m_pData = ((char *)((char *)(v21 + 12 * (v13 + 1))));
  }
  return this->m_nSize + 12 * v22;
}

// 0x00410DF0
int * Array::CopyRange(int *p_DWORD, int *p_DWORD2)
{
  int *v3; // edx
  int *v4; // esi
  int *m_pData; // edi
  int *v6; // eax
  int *v7; // ebx
  int *result; // eax

  v3 = (int *)p_DWORD2;
  v4 = (int *)p_DWORD;
  m_pData = (int *)this->m_pData;
  if ( p_DWORD2 != m_pData )
  {
    do
    {
      v6 = (int *)v3;
      v7 = (int *)v4;
      v3 += 3;
      v4 += 3;
      *v7 = *v6;
      v7[1] = (unsigned long)v6[1];
      v7[2] = (unsigned long)v6[2];
    }
    while ( v3 != m_pData );
  }
  result = (int *)p_DWORD;
  this->m_pData = ((char *)((char *)v4));
  return result;
}

// 0x00411170
void * Array::Insert(void *pElem, void *pEnd)
{
  _DWORD *v3; // ecx
  void *result; // eax
  void *v5; // [esp+0xC] [ebp+0xC]

  v3 = (_DWORD *)pElem;
  if ( pElem == pEnd )
    return v5;
  result = (void *)v5;
  do
  {
    if ( result )
    {
      *(_DWORD *)result = (unsigned long)*v3;
      *((_DWORD *)result + 1) = (unsigned long)v3[1];
      *((_DWORD *)result + 2) = (unsigned long)v3[2];
    }
    v3 += 3;
    result = (char *)result + 12;
  }
  while ( v3 != pEnd );
  return result;
}

// 0x004111C0
int Array::Size()
{
  int result; // eax

  result = this->m_nSize;
  if ( result )
    return (int)&this->m_pData[-result] / 12;
  return result;
}

// 0x004111E0
void * Array::Erase(int nIndex, int nCount)
{
  void *result; // eax
  int v4; // ecx
  _DWORD *v5; // [esp+0xC] [ebp+0xC]

  result = (void *)nCount;
  if ( nCount )
  {
    v4 = nCount;
    result = (void *)nIndex;
    do
    {
      if ( result )
      {
        *(_DWORD *)result = (unsigned long)*v5;
        *((_DWORD *)result + 1) = (unsigned long)v5[1];
        *((_DWORD *)result + 2) = (unsigned long)v5[2];
      }
      result = (char *)result + 12;
      --v4;
    }
    while ( v4 );
  }
  return result;
}

// 0x00411240
void * Array::Copy(void *dst)
{
  void *result; // eax
  gbVec3D *pSrc; // [esp+0x8] [ebp+0x8]

  result = (void *)dst;
  if ( dst )
  {
    *(float *)dst = pSrc->x;
    *((_DWORD *)dst + 1) = LODWORD(pSrc->y);
    *((_DWORD *)dst + 2) = LODWORD(pSrc->z);
  }
  return result;
}

// 0x004115C0
unsigned int * Array::PartialSort(
        unsigned int *pdwVal,
        unsigned int *pdwVal2,
        unsigned int dwVal,
        int nVal,
        int nVal2,
        int nVal3)
{
  unsigned int *result; // eax
  int v8; // ebp
  int v9; // edi
  bool v10; // dl
  bool v11; // cf
  unsigned __int8 v12; // bl
  unsigned __int8 v13; // dl
  bool v14; // dl
  bool v15; // cf
  unsigned int v16; // edx
  unsigned int *v17; // ebx
  unsigned int v18; // edi
  unsigned int v19; // [esp+0x14] [ebp-0x8]

  result = (unsigned int *)pdwVal;
  v8 = nVal;
  v9 = nVal3;
LABEL_2:
  while ( 2 )
  {
    switch ( v9 )
    {
      case 0:
        v10 = *(_DWORD *)(result[2] + 608) < *(_DWORD *)(nVal2 + 608);
        goto LABEL_11;
      case 1:
        v10 = *(_DWORD *)(result[2] + 624) < *(_DWORD *)(nVal2 + 624);
        goto LABEL_11;
      case 2:
        v10 = (int)result[1] < v8;
        goto LABEL_11;
      case 3:
        v11 = *result < dwVal;
        goto LABEL_10;
      case 4:
        v12 = *(_BYTE *)(nVal2 + 612);
        v13 = *(_BYTE *)(result[2] + 612);
        goto LABEL_9;
      case 5:
        v12 = *(_BYTE *)(nVal2 + 613);
        v13 = *(_BYTE *)(result[2] + 613);
LABEL_9:
        v11 = v13 < v12;
LABEL_10:
        v10 = v11;
LABEL_11:
        if ( !v10 )
          break;
        result += 3;
        continue;
      default:
        goto LABEL_13;
    }
    break;
  }
LABEL_13:
  while ( 2 )
  {
    pdwVal2 -= 3;
    switch ( v9 )
    {
      case 0:
        v14 = *(_DWORD *)(nVal2 + 608) < *(_DWORD *)(pdwVal2[2] + 608);
        goto LABEL_21;
      case 1:
        v14 = *(_DWORD *)(nVal2 + 624) < *(_DWORD *)(pdwVal2[2] + 624);
        goto LABEL_21;
      case 2:
        v14 = v8 < (int)pdwVal2[1];
        goto LABEL_21;
      case 3:
        v15 = dwVal < *pdwVal2;
        goto LABEL_20;
      case 4:
        v15 = *(_BYTE *)(nVal2 + 612) < *(_BYTE *)(pdwVal2[2] + 612);
        goto LABEL_20;
      case 5:
        v15 = *(_BYTE *)(nVal2 + 613) < *(_BYTE *)(pdwVal2[2] + 613);
LABEL_20:
        v14 = v15;
LABEL_21:
        if ( !v14 )
          goto LABEL_22;
        continue;
      default:
LABEL_22:
        if ( pdwVal2 > result )
        {
          v16 = (unsigned long)*result;
          v19 = (unsigned long)result[1];
          v17 = (unsigned int *)result;
          v18 = (unsigned long)result[2];
          result += 3;
          *v17 = *pdwVal2;
          v17[1] = (unsigned long)pdwVal2[1];
          v8 = nVal;
          v17[2] = (unsigned long)pdwVal2[2];
          *pdwVal2 = v16;
          pdwVal2[1] = v19;
          pdwVal2[2] = v18;
          v9 = nVal3;
          goto LABEL_2;
        }
        return result;
    }
  }
}

// 0x0049CF80
double Array::HandleItemPage(int *pnVal, int nVal, int elem)
{
  char *v3; // esi
  int v4; // edi
  void *v5; // eax
  void *v6; // eax
  bool IsValidItem; // al
  NPC *v9; // ecx
  CScreenMode *Instance; // eax
  char v11; // al
  __int16 v12; // ax
  int v13; // eax
  float result; // st7
  PalScriptMgr *v15; // ecx
  PalScriptMgr *v16; // ecx
  char v17; // al
  RoleSystem *v18; // eax
  Array *v19; // edi
  char *m_pData; // esi
  int v21; // eax
  bool v22; // sf
  unsigned int v23; // eax
  ScriptSystem *v24; // eax
  void *m_nSize; // edx
  int v26; // esi
  int v27; // eax
  char *v28; // ecx
  char *i; // eax
  char *v30; // edx
  EquipUI *v31; // esi
  Array *v32; // edi
  char *v33; // ecx
  int v34; // eax
  int v35; // eax
  EquipUI *v36; // eax
  void *v37; // eax
  void *v38; // ecx
  int v39; // ecx
  unsigned int v40; // eax
  char *v41; // eax
  char *v42; // ecx
  Array *v43; // edi
  char *v44; // ecx
  int v45; // eax
  int v46; // edx
  unsigned int v47; // eax
  int v48; // edx
  unsigned int v49; // eax
  char *v50; // eax
  char *v51; // ecx
  int v52; // edi
  int v53; // eax
  int v54; // eax
  int v55; // edx
  int v56; // ecx
  RoleSystem *v57; // esi
  int *v58; // eax
  int v59; // esi
  int v60; // edx
  EquipUI *v61; // esi
  EquipUI *v62; // ecx
  int v63; // edx
  int v64; // edi
  char v65; // al
  int v66; // eax
  _DWORD *v67; // eax
  bool v68; // zf
  int v69; // eax
  _BYTE *v70; // edi
  unsigned int *v71; // eax
  int v72; // edi
  int v73; // edx
  int v74; // eax
  __int16 *v75; // eax
  int v76; // edi
  int j; // esi
  char v78; // cl
  int v79; // ecx
  int v80; // ecx
  int v81; // esi
  _BYTE *v82; // edi
  ScriptSystem *v83; // esi
  int *v84; // eax
  int v85; // esi
  int v86; // edx
  bool v87; // cc
  void (***v88)(_DWORD, _DWORD); // edi
  int v89; // ebx
  void (***v90)(_DWORD, _DWORD); // edi
  int v91; // ebx
  int v92; // ebx
  int k; // edi
  void (***v94)(_DWORD, _DWORD); // edi
  int v95; // ebx
  int v96; // [esp-0x10] [ebp-0x150]
  const void *v97; // [esp-0x4] [ebp-0x144]
  unsigned int fValue; // [esp+0x0] [ebp-0x140]
  float fValuea; // [esp+0x0] [ebp-0x140]
  float fValueb; // [esp+0x0] [ebp-0x140]
  char Buffer; // [esp+0x10] [ebp-0x130] BYREF
  _BYTE v102[252]; // [esp+0x11] [ebp-0x12F] BYREF
  __int16 v103; // [esp+0x10D] [ebp-0x33]
  char v104; // [esp+0x10F] [ebp-0x31]
  int v105; // [esp+0x110] [ebp-0x30]
  float v106; // [esp+0x114] [ebp-0x2C]
  int nItemID; // [esp+0x118] [ebp-0x28] BYREF
  int v108; // [esp+0x11C] [ebp-0x24]
  NPC *v109; // [esp+0x120] [ebp-0x20]
  EquipUI *v110; // [esp+0x124] [ebp-0x1C]
  int v111; // [esp+0x128] [ebp-0x18]
  int pOut; // [esp+0x12C] [ebp-0x14] BYREF
  int v113; // [esp+0x130] [ebp-0x10]
  int RoleNum; // [esp+0x134] [ebp-0xC]
  int v115; // [esp+0x138] [ebp-0x8]
  int v116; // [esp+0x13C] [ebp-0x4]
  int elema; // [esp+0x148] [ebp+0x8]
  void *elemg; // [esp+0x148] [ebp+0x8]
  char *elemb; // [esp+0x148] [ebp+0x8]
  char *elemc; // [esp+0x148] [ebp+0x8]
  int elemd; // [esp+0x148] [ebp+0x8]
  int eleme; // [esp+0x148] [ebp+0x8]
  float elemh; // [esp+0x148] [ebp+0x8]
  scAsmDecoder *elemf; // [esp+0x148] [ebp+0x8]
  char elem_3; // [esp+0x14B] [ebp+0xB]

  v3 = (char *)pnVal;
  v4 = 0;
  v110 = (EquipUI *)pnVal;
  if ( pnVal[161] < 0 )
    return result;
  switch ( pnVal[160] )
  {
    case 0:
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(0);
      v5 = (void *)*((_DWORD *)v3 + 48947);
      if ( (int)v5 < 0 )
        goto LABEL_7;
      goto LABEL_6;
    case 1:
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(1);
      v5 = (void *)*((_DWORD *)v3 + 48947);
      if ( (int)v5 >= 0 )
LABEL_6:
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(v5);
      goto LABEL_7;
    case 2:
    case 3:
    case 4:
    case 5:
      return result;
    default:
LABEL_7:
      fValue = *((_DWORD *)v3 + 161);
      nItemID = 0xFFFF;
      v108 = 0;
      v109 = 0;
      v6 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(&pOut, fValue);
      nItemID = *(_DWORD *)v6;
      v108 = *((_DWORD *)v6 + 1);
      v109 = (NPC *)*((_DWORD *)v6 + 2);
      if ( !v109 )
        return result;
      IsValidItem = (((PAL_GDB *)v3))->PAL_GDB::IsValidItem((int)&nItemID, elem);
      v9 = (NPC *)v109;
      if ( !IsValidItem && *((_BYTE *)&v109->m_AnimWndA + 73) == 1 )
      {
        sprintf(v3 + 108, "\\n      %s", (const char *)&dword_DC9F3C);
        SetEnable((UICaption *)(v3 + 155240));
        (((UIRoleSelect *)(v3 + 154784)))->UIRoleSelect::SetByte(1);
        v97 = (const void *)off_5CADD0;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v97, 1);
        return result;
      }
      v11 = *((_BYTE *)&v109->m_AnimWndA + 73);
      elem_3 = v11;
      if ( v11 != 1 && v11 != 2 || !v3[654] || !v3[653] )
        return result;
      v12 = *((_WORD *)&v109->m_AnimWndA + 44);
      *(_WORD *)((char *)&v115 + 1) = -30124;
      LOBYTE(v115) = -32;
      if ( v12 )
      {
        *(_WORD *)((char *)&v115 + 1) = -22360;
        goto LABEL_21;
      }
      if ( *((_WORD *)&v109->m_AnimWndA + 45) )
      {
        *(_WORD *)((char *)&v115 + 1) = 22696;
LABEL_21:
        LOBYTE(v115) = 28;
        goto LABEL_22;
      }
      if ( *((_WORD *)&v109->m_AnimWndA + 46) )
      {
        BYTE2(v115) = 28;
        LOWORD(v115) = 22696;
      }
LABEL_22:
      if ( nItemID == 6402 )
        goto LABEL_23;
      if ( nItemID == 6405 )
      {
LABEL_26:
        (((NPC *)v109))->NPC::SetSceneFlag();
        (((EquipUI *)v3))->EquipUI::UpdateDisplay(elem, v115);
        goto LABEL_205;
      }
      if ( nItemID != 6404 )
      {
        if ( nItemID == 6403 )
          goto LABEL_26;
        if ( nItemID != 6406 )
        {
          if ( nItemID == 6230 )
          {
            if ( *((_WORD *)&v109->m_wndDialog + 8) )
              v4 = *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 6);
            if ( *((_WORD *)&v109->m_wndDialog + 9) )
              v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 7);
            if ( *((_WORD *)&v109->m_wndDialog + 6) )
              v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 4);
            if ( *((_WORD *)&v109->m_wndDialog + 7) )
              v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 5);
            if ( *(_WORD *)&v109->m_AnimWndB )
              v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_nCmdParam + 1408 * elem);
            if ( v4 <= 0 )
            {
              g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * elem + 2] = 1;
              fValuea = (float)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * elem);
              (((UIScrollBar *)&v3[4892 * elem + 156952]))->UIScrollBar::SetRange(fValuea);
              result = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * elem + 2];
              fValueb = result;
              (((UIProgressBar *)&v3[4892 * elem + 156952]))->UIProgressBar::FindChildByName(fValueb);
            }
            else
            {
              v13 = 1408 * elem;
              *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v13 + 6) = 0;
              *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v13 + 7) = 0;
              *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v13 + 4) = 0;
              *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v13 + 5) = 0;
              *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_nCmdParam + v13) = 0;
              if ( (scAsmDecoder *)elem == dword_C10CC8 )
                (((ScriptSystem *)(5 * elem)))->ScriptSystem::RunEvent(31, 1);
              (((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164)))->Comp_DonateUI::ProcessInput(elem);
            }
            goto LABEL_24;
          }
          if ( *(_DWORD *)v109 == 6401 )
          {
            (((EquipUI *)v3))->EquipUI::UpdateDisplay(elem, v115);
            (((PalScriptMgr *)v15))->PalScriptMgr::LoadYlfScript();
            (((MainEquipUI *)*((MainEquipUI **)v3 + 164)))->MainEquipUI::HandleMessage(9);
            goto LABEL_205;
          }
          if ( *(_DWORD *)v109 == 6427 )
          {
            if ( !FindScriptEventByID(2101) )
              goto LABEL_205;
            (((PalScriptMgr *)v16))->PalScriptMgr::Destroy();
            (((MainEquipUI *)*((MainEquipUI **)v3 + 164)))->MainEquipUI::HandleMessage(9);
            goto LABEL_24;
          }
          v17 = *((_BYTE *)&v109->m_AnimWndA + 72);
          if ( v17 == 5 )
          {
            v18 = (RoleSystem *)UISceneUpdate();
            (((RoleSystem *)v18))->RoleSystem::ResetTransition();
            (((MainEquipUI *)*((MainEquipUI **)v3 + 164)))->MainEquipUI::HandleMessage(9);
            (((EquipUI *)v3))->EquipUI::UpdateDisplay(elem, v115);
            goto LABEL_205;
          }
          if ( v17 == 7 )
          {
            v113 = 0;
            RoleNum = 0;
            pOut = 306;
            LOWORD(v113) = (((MUIDialog *)v3))->MUIDialog::GetPlayerAttField(elem, 306);
            HIWORD(v113) = (((UIListBox *)v3))->UIListBox::GetSkillSlotLevel(elem, pOut);
            Buffer = 0;
            RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pOut);
            memset(v102, 0, sizeof(v102));
            v103 = 0;
            v104 = 0;
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              RoleSystem::CheckVisible();
              NPC::InitAll();
              sprintf(
                &Buffer,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)&dword_DD443C,
                (const char *)&dword_DD463C,
                (const char *)(RoleNum + 28));
              (((EquipUI *)v3))->EquipUI::UpdateDisplay(elem, v115);
              v3[652] = 0;
              v3[654] = 0;
              v3[653] = 0;
              (((EquipUI *)v3))->EquipUI::SetGroupVisible(1u);
LABEL_61:
              SetEnable((UICaption *)(v3 + 155240));
              (((UIRoleSelect *)(v3 + 154784)))->UIRoleSelect::SetByte(1);
              goto LABEL_205;
            }
            goto LABEL_60;
          }
          if ( v17 == 8 )
          {
            v113 = 0;
            RoleNum = 0;
            pOut = 311;
            LOWORD(v113) = (((MUIDialog *)v3))->MUIDialog::GetPlayerAttField(elem, 311);
            HIWORD(v113) = (((UIListBox *)v3))->UIListBox::GetSkillSlotLevel(elem, pOut);
            Buffer = 0;
            RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pOut);
            memset(v102, 0, sizeof(v102));
            v103 = 0;
            v104 = 0;
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              RoleSystem::CheckVisible();
              NPC::InitAll();
              sprintf(
                &Buffer,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)&dword_DD443C,
                (const char *)&dword_DD473C,
                (const char *)(RoleNum + 28));
              (((EquipUI *)v3))->EquipUI::UpdateDisplay(elem, v115);
              v3[652] = 0;
              v3[654] = 0;
              v3[653] = 0;
              (((EquipUI *)v3))->EquipUI::SetGroupVisible(1u);
              goto LABEL_61;
            }
LABEL_60:
            sprintf(
              &Buffer,
              "\\n   %s%s",
              (const char *)&g_RoleSlotBuf.m_partyActor.m_fInterpEnd + 1408 * elem,
              (const char *)&dword_DD4B3C);
            goto LABEL_61;
          }
          if ( v17 == 9 )
          {
            v113 = 0;
            RoleNum = 0;
            pOut = 301;
            LOWORD(v113) = (((MUIDialog *)v3))->MUIDialog::GetPlayerAttField(elem, 301);
            HIWORD(v113) = (((UIListBox *)v3))->UIListBox::GetSkillSlotLevel(elem, pOut);
            RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pOut);
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              v19 = (Array *)(&g_SceneMgrPrefix + elem);
              m_pData = (char *)v19->m_pData;
              if ( (v19->m_nCapacity - (int)m_pData) / 12 )
              {
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(m_pData, m_pData);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Erase((int)v19->m_pData, 1 - (v19->m_pData - m_pData) / 12);
                v28 = (char *)v19->m_pData;
                for ( i = m_pData; i != v28; *((_DWORD *)v30 + 2) = RoleNum )
                {
                  v30 = (char *)i;
                  i += 12;
                  *(_DWORD *)v30 = pOut;
                  *((_DWORD *)v30 + 1) = v113;
                }
                v19->m_pData += 12;
              }
              else
              {
                if ( (unsigned int)(((Array *)v19))->Array::Size() <= 1 )
                  elema = 1;
                else
                  elema = (((Array *)v19))->Array::Size();
                v21 = (((Array *)v19))->Array::Size();
                v22 = elema + v21 < 0;
                v23 = elema + v21;
                v116 = v23;
                if ( v22 )
                  v23 = 0;
                v24 = (ScriptSystem *)operator new(12 * v23);
                m_nSize = (void *)v19->m_nSize;
                v111 = (int)v24;
                elemg = ((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(m_nSize, m_pData);
                (((Array *)v19))->Array::Erase((int)elemg, 1);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(m_pData, v19->m_pData);
                nullsub_2(v19->m_nSize, v19->m_pData);
                operator delete((void *)v19->m_nSize);
                v26 = v111;
                v19->m_nCapacity = (int)v111 + 12 * v116;
                v27 = ((Array *)(&g_SceneMgrPrefix + elem))->Array::Size();
                v19->m_nSize = (int)v26;
                v19->m_pData = (char *)(&v26->m_vPos_z + 3 * v27);
              }
              NPC::InitAll();
              v31 = (EquipUI *)v110;
              sprintf(
                &v110->buf[28],
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)&dword_DD443C,
                (const char *)&dword_DD483C,
                (const char *)(RoleNum + 28));
              *((_BYTE *)&v31->m_EquipData + 276) = 0;
              *((_BYTE *)&v31->m_EquipData + 278) = 0;
              *((_BYTE *)&v31->m_EquipData + 277) = 0;
              (((EquipUI *)v31))->EquipUI::SetGroupVisible(1u);
              (((EquipUI *)v31))->EquipUI::UpdateDisplay(elem, v115);
            }
            else
            {
              sprintf(
                v3 + 108,
                "\\n   %s%s",
                (const char *)&g_RoleSlotBuf.m_partyActor.m_fInterpEnd + 1408 * elem,
                (const char *)&dword_DD4B3C);
              v31 = (EquipUI *)v110;
            }
            SetEnable((UICaption *)&v31[1].m_Arrow[1][3][4].m_childs.m_nSize);
            (((UIRoleSelect *)&v31[1].m_Arrow[1][3][1].m_childs.m_nSize))->UIRoleSelect::SetByte(1);
            goto LABEL_204;
          }
          if ( v17 == 10 )
          {
            v113 = 0;
            RoleNum = 0;
            pOut = 316;
            LOWORD(v113) = (((MUIDialog *)v3))->MUIDialog::GetPlayerAttField(elem, 316);
            HIWORD(v113) = (((UIListBox *)v3))->UIListBox::GetSkillSlotLevel(elem, pOut);
            RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pOut);
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              v32 = (Array *)(&g_SceneMgrPrefix + elem);
              v33 = (char *)v32->m_pData;
              elemb = (char *)v33;
              if ( (v32->m_nCapacity - (int)v33) / 12 )
              {
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(v33, v33);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Erase((int)v32->m_pData, 1 - (v32->m_pData - elemb) / 12);
                v41 = (char *)elemb;
                v116 = (unsigned int)v32->m_pData;
                if ( elemb != (char *)v116 )
                {
                  do
                  {
                    v42 = (char *)v41;
                    v41 += 12;
                    *(_DWORD *)v42 = pOut;
                    *((_DWORD *)v42 + 1) = v113;
                    *((_DWORD *)v42 + 2) = RoleNum;
                  }
                  while ( v41 != (char *)v116 );
                }
                v32->m_pData += 12;
              }
              else
              {
                v34 = v32->m_nSize;
                if ( v34 && (unsigned int)((int)&v33[-v34] / 12) > 1 )
                  v116 = ((Array *)(&g_SceneMgrPrefix + elem))->Array::Size();
                else
                  v116 = 1;
                v35 = ((Array *)(&g_SceneMgrPrefix + elem))->Array::Size();
                v22 = (int)(v116 + v35) < 0;
                v36 = (EquipUI *)(v116 + v35);
                v110 = (EquipUI *)v36;
                if ( v22 )
                  v36 = 0;
                v37 = (void *)operator new(12 * (_DWORD)v36);
                v38 = (void *)v32->m_nSize;
                v116 = (unsigned int)v37;
                v111 = (int)(ScriptSystem *)((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(v38, elemb);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Erase((int)v111, 1);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(elemb, v32->m_pData);
                nullsub_2(v32->m_nSize, v32->m_pData);
                operator delete((void *)v32->m_nSize);
                v32->m_nCapacity = v116 + 12 * (_DWORD)v110;
                v39 = 3 * (((Array *)(&g_SceneMgrPrefix + elem))->Array::Size() + 1);
                v40 = v116;
                v32->m_nSize = v116;
                v32->m_pData = (char *)(v40 + 4 * v39);
              }
              NPC::InitAll();
              sprintf(
                v3 + 108,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)&dword_DD443C,
                (const char *)&dword_DD453C,
                (const char *)(RoleNum + 28));
LABEL_107:
              v3[652] = 0;
              v3[654] = 0;
              v3[653] = 0;
              (((EquipUI *)v3))->EquipUI::SetGroupVisible(1u);
              (((EquipUI *)v3))->EquipUI::UpdateDisplay(elem, v115);
              goto LABEL_61;
            }
          }
          else
          {
            if ( v17 != 11 )
            {
              if ( v17 == 15 )
              {
                v52 = *(&g_RoleSlotBuf.m_partyActor.m_nPathEnabled + 352 * elem)
                    - Role::CalcXueJianInit(elem, *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem));
                v53 = Role::CalcZiXuanInit(elem, *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem));
                v96 = *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem);
                v116 = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixA + 352 * elem) - v53;
                elemd = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fScale + 352 * elem)
                      - Role::CalcLongKuiInit(elem, v96);
                v111 = (int)(ScriptSystem *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixB + 352 * elem)
                                      - Role::CalcChangQingInit(
                                          elem,
                                          *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem)));
                v54 = Role::CalcHuaYingInit(elem, *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem));
                v55 = *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem) + 1;
                LODWORD(v106) = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * elem) - v54;
                *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem) = v55;
                if ( v55 >= 99 )
                  *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * elem) = 99;
                *(&g_RoleSlotBuf.m_partyActor.m_nPathEnabled + 352 * elem) = Role::CalcXueJianInit(
                                                                               elem,
                                                                               *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj
                                                                               + 352 * elem));
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fScale + 352 * elem) = Role::CalcLongKuiInit(
                                                                                   elem,
                                                                                   *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj
                                                                                   + 352 * elem));
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixA + 352 * elem) = Role::CalcZiXuanInit(
                                                                                     elem,
                                                                                     *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj
                                                                                     + 352 * elem));
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixB + 352 * elem) = Role::CalcChangQingInit(
                                                                                     elem,
                                                                                     *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj
                                                                                     + 352 * elem));
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * elem) = Role::CalcHuaYingInit(
                                                                                     elem,
                                                                                     *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj
                                                                                     + 352 * elem));
                *(&g_RoleSlotBuf.m_partyActor.m_nPathEnabled + 352 * elem) += v52;
                v56 = v106;
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fScale + 352 * elem) += elemd;
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixA + 352 * elem) += v116;
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixB + 352 * elem) += v111;
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * elem) += LODWORD(v56);
                v57 = (RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * elem);
                (((RoleSystem *)v57))->RoleSystem::RecalcAggregatedStats(0);
                v58 = (int *)&v57->m_partyActor.m_dwMatMsg[2];
                v59 = 12;
                do
                {
                  v60 = *(v58 - 12);
                  if ( *v58 < v60 )
                  {
                    if ( *v58 <= 0 )
                      *v58 = 0;
                  }
                  else
                  {
                    *v58 = v60;
                  }
                  ++v58;
                  --v59;
                }
                while ( v59 );
                v61 = (EquipUI *)v110;
                v62 = (EquipUI *)v110;
                *((_BYTE *)&v110->m_EquipData + 276) = 0;
                *((_BYTE *)&v62->m_EquipData + 278) = 0;
                *((_BYTE *)&v62->m_EquipData + 277) = 0;
                (((EquipUI *)v62))->EquipUI::SetGroupVisible(1u);
                (((EquipUI *)v61))->EquipUI::UpdateDisplay(elem, v115);
                (((StateUI *)v61))->StateUI::UpdateScrollValues();
              }
              else
              {
                if ( elem_3 == 1 )
                {
                  v63 = 644;
                  v64 = 0;
                  eleme = 644;
                  do
                  {
                    v65 = *((_BYTE *)&v9->m_AnimWndA + v64 + 75);
                    if ( v65 == 1 )
                    {
                      v66 = v64 + 352 * elem;
                      elemh = (float)*(__int16 *)((char *)v9 + v63)
                            * 0.0099999998
                            * (double)*(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v66 * 4);
                      result = elemh;
                      LODWORD(v106) = (int)elemh;
                      g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v66 + 2] += LODWORD(v106);
                      v9 = (NPC *)v109;
                    }
                    else
                    {
                      if ( v65 == 3 )
                        v67 = (_DWORD *)(4 * (v64 + 352 * elem) + 12600860);
                      else
                        v67 = (_DWORD *)(4 * (v64 + 352 * elem) + 12601196);
                      *v67 += *(__int16 *)((char *)v9 + v63);
                      v63 = eleme;
                    }
                    v63 += 2;
                    ++v64;
                    eleme = v63;
                  }
                  while ( v63 < 668 );
                  if ( *((__int16 *)&v9->m_wndDialog + 8) >= 2 )
                  {
                    v68 = elem == (_DWORD)dword_C10CC8;
                    *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 6) = 0;
                    if ( v68 )
                      (((ScriptSystem *)(1408 * elem)))->ScriptSystem::RunEvent(31, 1);
                    (((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164)))->Comp_DonateUI::ProcessInput(elem);
                    v9 = (NPC *)v109;
                  }
                  if ( *((__int16 *)&v9->m_wndDialog + 9) >= 2 )
                  {
                    *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 7) = 0;
                    if ( (scAsmDecoder *)elem == dword_C10CC8 )
                      (((ScriptSystem *)v9))->ScriptSystem::RunEvent(31, 1);
                    (((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164)))->Comp_DonateUI::ProcessInput(elem);
                    v9 = (NPC *)v109;
                  }
                  if ( *((__int16 *)&v9->m_wndDialog + 6) >= 2 )
                  {
                    v68 = elem == (_DWORD)dword_C10CC8;
                    *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 4) = 0;
                    if ( v68 )
                      (((ScriptSystem *)(5 * elem)))->ScriptSystem::RunEvent(31, 1);
                    (((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164)))->Comp_DonateUI::ProcessInput(elem);
                    v9 = (NPC *)v109;
                  }
                  if ( *((__int16 *)&v9->m_wndDialog + 7) >= 2 )
                  {
                    v68 = elem == (_DWORD)dword_C10CC8;
                    *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + 5) = 0;
                    if ( v68 )
                      (((ScriptSystem *)(1408 * elem)))->ScriptSystem::RunEvent(31, 1);
                    (((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164)))->Comp_DonateUI::ProcessInput(elem);
                    v9 = (NPC *)v109;
                  }
                  if ( *(_WORD *)&v9->m_AnimWndB >= 2 )
                  {
                    *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_nCmdParam + 1408 * elem) = 0;
                    if ( (scAsmDecoder *)elem == dword_C10CC8 )
                      (((ScriptSystem *)v9))->ScriptSystem::RunEvent(31, 1);
                    (((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164)))->Comp_DonateUI::ProcessInput(elem);
                    v9 = (NPC *)v109;
                  }
                  v69 = 0;
                  v70 = (_BYTE *)(&v9->m_wndDialog + 3);
                  do
                  {
                    if ( (unsigned int)v69 > 0xC )
                      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * elem + v69 + 4) = *v70;
                    ++v69;
                    v70 += 2;
                  }
                  while ( v69 < 31 );
                  (((RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * elem)))->RoleSystem::RecalcAggregatedStats(0);
                  v71 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * elem + 2];
                  v72 = 12;
                  do
                  {
                    v73 = *(v71 - 12);
                    if ( (int)*v71 < v73 )
                    {
                      if ( (int)*v71 <= 0 )
                        *v71 = 0;
                    }
                    else
                    {
                      *v71 = v73;
                    }
                    ++v71;
                    --v72;
                  }
                  while ( v72 );
                  goto LABEL_24;
                }
                if ( elem_3 != 2 )
                  goto LABEL_205;
                v74 = 0;
                v111 = (int)(ScriptSystem *)((char *)&g_RoleSlotBuf.m_partyActor.m_Actor + 6);
                elemf = 0;
                v116 = 0;
                while ( 1 )
                {
                  if ( v3[v74 + 621] && (((PAL_GDB *)v3))->PAL_GDB::IsValidItem((int)&nItemID, v74) )
                  {
                    v75 = (__int16 *)v109;
                    v76 = 0;
                    for ( j = 322; j < 334; ++j )
                    {
                      v78 = *((_BYTE *)v75 + v76 + 631);
                      if ( v78 == 1 )
                      {
                        v79 = v76 + v116;
                        v106 = (float)(*(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v79 * 4)
                                     * (v75[j]
                                      / 100));
                        result = v106;
                        v105 = (int)v106;
                        g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v79 + 2] += v105;
                        v75 = (__int16 *)v109;
                      }
                      else if ( v78 == 3 )
                      {
                        *(&g_RoleSlotBuf.m_partyActor.m_nPathEnabled + v76 + v116) += v75[j];
                      }
                      else
                      {
                        g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v76 + 2 + v116] += v75[j];
                      }
                      ++v76;
                    }
                    v80 = v111;
                    v81 = 0;
                    v82 = (_BYTE *)(v75 + 350);
                    do
                    {
                      if ( (unsigned int)v81 > 0xC )
                        *((_BYTE *)v80 + v81 - 2) = *v82;
                      ++v81;
                      v82 += 2;
                    }
                    while ( v81 < 31 );
                    if ( v75[352] >= 2 )
                    {
                      LOBYTE(v80->m_nSlotID) = 0;
                      if ( elemf == dword_C10CC8 )
                        (((ScriptSystem *)v80))->ScriptSystem::RunEvent(31, 1);
                      (((Comp_DonateUI *)*((Comp_DonateUI **)&v110->m_EquipData + 70)))->Comp_DonateUI::ProcessInput((int)elemf);
                      v75 = (__int16 *)v109;
                      v80 = v111;
                    }
                    if ( v75[353] >= 2 )
                    {
                      BYTE1(v80->m_nSlotID) = 0;
                      if ( elemf == dword_C10CC8 )
                        (((ScriptSystem *)v80))->ScriptSystem::RunEvent(31, 1);
                      (((Comp_DonateUI *)*((Comp_DonateUI **)&v110->m_EquipData + 70)))->Comp_DonateUI::ProcessInput((int)elemf);
                      v75 = (__int16 *)v109;
                      v80 = v111;
                    }
                    if ( v75[350] >= 2 )
                    {
                      BYTE2(v80[-1].m_nSaveDir) = 0;
                      if ( elemf == dword_C10CC8 )
                        (((ScriptSystem *)v80))->ScriptSystem::RunEvent(31, 1);
                      (((Comp_DonateUI *)*((Comp_DonateUI **)&v110->m_EquipData + 70)))->Comp_DonateUI::ProcessInput((int)elemf);
                      v75 = (__int16 *)v109;
                      v80 = v111;
                    }
                    if ( v75[351] >= 2 )
                    {
                      HIBYTE(v80[-1].m_nSaveDir) = 0;
                      if ( elemf == dword_C10CC8 )
                        (((ScriptSystem *)v80))->ScriptSystem::RunEvent(31, 1);
                      (((Comp_DonateUI *)*((Comp_DonateUI **)&v110->m_EquipData + 70)))->Comp_DonateUI::ProcessInput((int)elemf);
                      v75 = (__int16 *)v109;
                    }
                    if ( v75[354] >= 2 )
                    {
                      BYTE2(v111->m_nSlotID) = 0;
                      if ( elemf == dword_C10CC8 )
                        (((ScriptSystem *)elemf))->ScriptSystem::RunEvent(31, 1);
                      (((Comp_DonateUI *)*((Comp_DonateUI **)&v110->m_EquipData + 70)))->Comp_DonateUI::ProcessInput((int)elemf);
                    }
                    v83 = v111;
                    (((RoleSystem *)((char *)&v111[-1].m_nSubObjBase + 6538)))->RoleSystem::RecalcAggregatedStats(0);
                    v84 = (int *)((char *)&v83->m_nTodo_10C + 18);
                    v85 = 12;
                    do
                    {
                      v86 = *(v84 - 12);
                      if ( *v84 < v86 )
                      {
                        if ( *v84 <= 0 )
                          *v84 = 0;
                      }
                      else
                      {
                        *v84 = v86;
                      }
                      ++v84;
                      --v85;
                    }
                    while ( v85 );
                    if ( (((PAL_GDB *)v110))->PAL_GDB::IsValidItem((int)&nItemID, (int)elemf) )
                      (((EquipUI *)v110))->EquipUI::UpdateDisplay((int)elemf, v115);
                  }
                  v74 = (int)&elemf->m_stack + 1;
                  v87 = (int)(&v111->m_nTodo_56C + 5) < (int)&unk_C061CE;
                  elemf = (scAsmDecoder *)((char *)elemf + 1);
                  v116 += 352;
                  v111 = (int)(ScriptSystem *)((char *)v111 + 1408);
                  if ( !v87 )
                    break;
                  v3 = (char *)v110;
                }
              }
LABEL_204:
              v3 = (char *)v110;
              goto LABEL_205;
            }
            v113 = 0;
            RoleNum = 0;
            pOut = 321;
            LOWORD(v113) = (((MUIDialog *)v3))->MUIDialog::GetPlayerAttField(elem, 321);
            HIWORD(v113) = (((UIListBox *)v3))->UIListBox::GetSkillSlotLevel(elem, pOut);
            RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pOut);
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              v43 = (Array *)(&g_SceneMgrPrefix + elem);
              v44 = (char *)v43->m_pData;
              elemc = (char *)v44;
              if ( (v43->m_nCapacity - (int)v44) / 12 )
              {
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(v44, v44);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Erase((int)v43->m_pData, 1 - (v43->m_pData - elemc) / 12);
                v50 = (char *)elemc;
                v116 = (unsigned int)v43->m_pData;
                if ( elemc != (char *)v116 )
                {
                  do
                  {
                    v51 = (char *)v50;
                    v50 += 12;
                    *(_DWORD *)v51 = pOut;
                    *((_DWORD *)v51 + 1) = v113;
                    *((_DWORD *)v51 + 2) = RoleNum;
                  }
                  while ( v50 != (char *)v116 );
                }
                v43->m_pData += 12;
              }
              else
              {
                v45 = v43->m_nSize;
                if ( !v45 || (v116 = (int)&v44[-v45] / 12, v116 <= 1) )
                  v116 = 1;
                if ( v43->m_nSize )
                  v46 = (int)&v44[-v43->m_nSize] / 12;
                else
                  v46 = 0;
                v47 = v46 + v116;
                v110 = (EquipUI *)(v46 + v116);
                if ( (int)(v46 + v116) < 0 )
                  v47 = 0;
                v116 = (unsigned int)operator new(12 * v47);
                v111 = (int)(ScriptSystem *)((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert((void *)v43->m_nSize, elemc);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Erase((int)v111, 1);
                ((Array *)(&g_SceneMgrPrefix + elem))->Array::Insert(elemc, v43->m_pData);
                operator delete((void *)v43->m_nSize);
                v43->m_nCapacity = v116 + 12 * (_DWORD)v110;
                v48 = 3 * (((Array *)(&g_SceneMgrPrefix + elem))->Array::Size() + 1);
                v49 = v116;
                v43->m_nSize = v116;
                v43->m_pData = (char *)(v49 + 4 * v48);
              }
              NPC::InitAll();
              sprintf(
                v3 + 108,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)&dword_DD443C,
                (const char *)&dword_DD493C,
                (const char *)(RoleNum + 28));
              goto LABEL_107;
            }
          }
          sprintf(
            v3 + 108,
            "\\n   %s%s",
            (const char *)&g_RoleSlotBuf.m_partyActor.m_fInterpEnd + 1408 * elem,
            (const char *)&dword_DD4B3C);
          goto LABEL_61;
        }
      }
LABEL_23:
      (((NPC *)v109))->NPC::SetSceneFlag();
LABEL_24:
      (((EquipUI *)v3))->EquipUI::UpdateDisplay(elem, v115);
LABEL_205:
      if ( v3[652] )
      {
        if ( v108 - 1 > 0 )
        {
          if ( (((PAL_GDB *)v3))->PAL_GDB::IsValidItem((int)&nItemID, elem) )
            goto LABEL_223;
          v92 = 0;
          for ( k = 0; k < 5; ++k )
          {
            if ( v3[k + 621] && (((PAL_GDB *)v3))->PAL_GDB::IsValidItem((int)&nItemID, k) )
              ++v92;
          }
          if ( v92 )
          {
LABEL_223:
            (((PAL_GDB *)v3))->PAL_GDB::SelectBestTarget(*((_DWORD *)v3 + 161));
          }
          else
          {
            v3[652] = 0;
            v94 = (void ( ***)(_DWORD, _DWORD))(v3 + 160876);
            v95 = 5;
            do
            {
              (**v94)((_DWORD)(v94), (_DWORD)(0));
              v94 += 1223;
              --v95;
            }
            while ( v95 );
          }
        }
        else
        {
          v3[652] = 0;
          v90 = (void ( ***)(_DWORD, _DWORD))(v3 + 160876);
          v91 = 5;
          do
          {
            (**v90)((_DWORD)(v90), (_DWORD)(0));
            v90 += 1223;
            --v91;
          }
          while ( v91 );
        }
      }
      else
      {
        v88 = (void ( ***)(_DWORD, _DWORD))(v3 + 160876);
        v89 = 5;
        do
        {
          (**v88)((_DWORD)(v88), (_DWORD)(0));
          v88 += 1223;
          --v89;
        }
        while ( v89 );
      }
      if ( nItemID != 6427 )
      {
        v108 = 1;
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&nItemID);
      }
      (((MainEquipUI *)v3))->MainEquipUI::SetupRoleList(*((_DWORD *)v3 + 160), 0);
      if ( !v3[652] )
      {
        v3[654] = 0;
        v3[653] = 0;
        (((EquipUI *)v3))->EquipUI::SetGroupVisible(1u);
      }
      return result;
  }
}

// 0x004AF450
char * Array::InsertBlocks(char *pszBuf, unsigned int dwVal, int *p_DWORD)
{
  Array *v4; // ebx
  char *result; // eax
  unsigned int v6; // edi
  int m_nSize; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  int *v12; // edx
  int v13; // eax
  int *v14; // eax
  char *v15; // ebx
  int *v16; // esi
  char *v17; // eax
  int v18; // ecx
  char *v19; // eax
  unsigned int v20; // ebp
  char *v21; // esi
  char *v22; // ecx
  char *v23; // eax
  int *v24; // esi
  unsigned int v25; // edi
  char *v26; // ecx
  char *k; // eax
  _DWORD *v28; // edi
  unsigned int v29; // edi
  char *m_pData; // esi
  char *v31; // ecx
  char *v32; // ecx
  char *i; // eax
  char *j; // eax
  _DWORD *v35; // ebx
  int *v37; // [esp+0x14] [ebp-0x4]
  char *pszBufa; // [esp+0x1C] [ebp+0x4]
  unsigned int dwVala; // [esp+0x20] [ebp+0x8]
result = (char *)this->m_pData;
  v6 = dwVal;
  if ( (this->m_nCapacity - (int)result) >> 4 >= dwVal )
  {
    if ( (result - pszBuf) >> 4 >= dwVal )
    {
      if ( dwVal )
      {
        v29 = 16 * dwVal;
        m_pData = (char *)this->m_pData;
        v31 = (char *)&result[-16 * dwVal];
        if ( v31 != result )
        {
          do
          {
            if ( m_pData )
            {
              *(_DWORD *)m_pData = *(_DWORD *)v31;
              *((_DWORD *)m_pData + 1) = *((_DWORD *)v31 + 1);
              *((_DWORD *)m_pData + 2) = *((_DWORD *)v31 + 2);
              *((_DWORD *)m_pData + 3) = *((_DWORD *)v31 + 3);
              v29 = 16 * dwVal;
            }
            v31 += 16;
            m_pData += 16;
          }
          while ( v31 != result );
}
        v32 = (char *)this->m_pData;
        for ( i = &v32[-v29]; i != pszBuf; *((_DWORD *)v32 + 3) = *((_DWORD *)i + 3) )
        {
          i -= 16;
          v32 -= 16;
          *(_DWORD *)v32 = *(_DWORD *)i;
          *((_DWORD *)v32 + 1) = *((_DWORD *)i + 1);
          *((_DWORD *)v32 + 2) = *((_DWORD *)i + 2);
        }
        for ( j = pszBuf; j != &pszBuf[v29]; v35[3] = (unsigned long)p_DWORD[3] )
        {
          v35 = (_DWORD *)j;
          j += 16;
          *v35 = *p_DWORD;
          v35[1] = (unsigned long)p_DWORD[1];
          v35[2] = (unsigned long)p_DWORD[2];
        }
        result = (char *)this;
        this->m_pData += v29;
      }
    }
    else
    {
      v20 = 16 * dwVal;
      v21 = (char *)&pszBuf[16 * dwVal];
      if ( pszBuf != result )
      {
        v22 = (char *)&v21[-v20];
        do
        {
          if ( v21 )
          {
            *(_DWORD *)v21 = *(_DWORD *)v22;
            *((_DWORD *)v21 + 1) = *((_DWORD *)v22 + 1);
            *((_DWORD *)v21 + 2) = *((_DWORD *)v22 + 2);
            v20 = 16 * dwVal;
            *((_DWORD *)v21 + 3) = *((_DWORD *)v22 + 3);
            v6 = dwVal;
          }
          v22 += 16;
          v21 += 16;
        }
        while ( v22 != result );
}
      v23 = (char *)this->m_pData;
      v24 = (int *)p_DWORD;
      v25 = v6 - ((v23 - pszBuf) >> 4);
      if ( v25 )
      {
        do
        {
          if ( v23 )
          {
            *(_DWORD *)v23 = (unsigned long)*v24;
            *((_DWORD *)v23 + 1) = (unsigned long)v24[1];
            *((_DWORD *)v23 + 2) = (unsigned long)v24[2];
            *((_DWORD *)v23 + 3) = (unsigned long)v24[3];
            v24 = (int *)p_DWORD;
          }
          v23 += 16;
          --v25;
        }
        while ( v25 );
}
      v26 = (char *)this->m_pData;
      for ( k = pszBuf; k != v26; v28[3] = (unsigned long)v24[3] )
      {
        v28 = (_DWORD *)k;
        k += 16;
        *v28 = *v24;
        v28[1] = (unsigned long)v24[1];
        v28[2] = (unsigned long)v24[2];
      }
      result = (char *)this;
      this->m_pData += v20;
    }
  }
  else
  {
    m_nSize = this->m_nSize;
    if ( !m_nSize || (v8 = (int)&result[-m_nSize] >> 4, dwVal >= v8) )
      v8 = dwVal;
    if ( m_nSize )
      v9 = (int)&result[-m_nSize] >> 4;
    else
      v9 = 0;
    v10 = v8 + v9;
    dwVala = v10;
    if ( v10 < 0 )
      v10 = 0;
    v37 = (int *)operator new(16 * v10);
    v12 = (int *)v37;
    v13 = this->m_nSize;
    if ( (char *)v13 != pszBuf )
    {
      do
      {
        if ( v12 )
        {
          *v12 = *(_DWORD *)v13;
          v12[1] = *(_DWORD *)(v13 + 4);
          v12[2] = *(_DWORD *)(v13 + 8);
          v12[3] = *(_DWORD *)(v13 + 12);
        }
        v13 += 16;
        v12 += 4;
      }
      while ( (char *)v13 != pszBuf );
}
    v14 = (int *)v12;
    if ( v6 )
    {
      pszBufa = (char *)v6;
      do
      {
        if ( v14 )
        {
          *v14 = *p_DWORD;
          v14[1] = (unsigned long)p_DWORD[1];
          v14[2] = (unsigned long)p_DWORD[2];
          v14[3] = (unsigned long)p_DWORD[3];
        }
        v14 += 4;
        --pszBufa;
      }
      while ( pszBufa );
}
    v15 = (char *)this->m_pData;
    v16 = (int *)&v12[4 * v6];
    if ( pszBuf != v15 )
    {
      v17 = (char *)pszBuf;
      do
      {
        if ( v16 )
        {
          *v16 = *(_DWORD *)v17;
          v16[1] = *((_DWORD *)v17 + 1);
          v16[2] = *((_DWORD *)v17 + 2);
          v16[3] = *((_DWORD *)v17 + 3);
        }
        v17 += 16;
        v16 += 4;
      }
      while ( v17 != v15 );
    }
    operator delete((void *)this->m_nSize);
    v18 = this->m_nSize;
    this->m_nCapacity = (int)&v37[4 * dwVala];
    if ( v18 )
    {
      v19 = (char *)this->m_pData;
      this->m_nSize = (int)v37;
      result = (char *)&v37[4 * v6 + 4 * ((int)&v19[-v18] >> 4)];
    }
    else
    {
      this->m_nSize = (int)v37;
      result = (char *)&v37[4 * v6];
    }
    this->m_pData = ((char *)(result));
  }
  return result;
}
