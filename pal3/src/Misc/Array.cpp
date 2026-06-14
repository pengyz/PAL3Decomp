#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/Array.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations

char FindScriptEventByID(int nEventId); // from annotations
int RefreshPartyRoleData(void); // from annotations

// Unnamed globals (extern)
extern int dword_DC9F3C;
extern int dword_DD443C;
extern int dword_DD453C;
extern int dword_DD463C;
extern int dword_DD473C;
extern int dword_DD483C;
extern int dword_DD493C;
extern int dword_DD4B3C;
void __cdecl nullsub_2(...);
extern void * off_5CADD0;
extern RoleSystem stru_C059A0;

// 0x00410960
void Array::Free()
{
  operator delete((void *)this->m_nSize);
  this->m_nSize = 0;
  this->m_pData = 0;
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
  char *v11; // ebx
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

  v3 = pPos;
  m_nSize = this->m_nSize;
  m_pData = this->m_pData;
  v22 = (int)&pPos[-m_nSize] / 12;
  if ( (this->m_nCapacity - (int)m_pData) / 12 )
  {
    if ( (m_pData - pPos) / 12 )
    {
      this->Insert(m_pData - 12, m_pData);
      v17 = this->m_pData;
      for ( i = v17 - 12; i != pPos; *((_DWORD *)v17 + 2) = *((_DWORD *)i + 2) )
      {
        i -= 12;
        v17 -= 12;
        *(_DWORD *)v17 = *(_DWORD *)i;
        *((_DWORD *)v17 + 1) = *((_DWORD *)i + 1);
      }
      do
      {
        v19 = v3;
        v3 += 12;
        *v19 = *pSrc;
        v19[1] = pSrc[1];
        v19[2] = pSrc[2];
      }
      while ( v3 != pPos + 12 );
    }
    else
    {
      this->Insert(pPos, m_pData);
      this->Erase((int)this->m_pData, 1 - (this->m_pData - pPos) / 12);
      v14 = this->m_pData;
      for ( j = pPos; j != v14; v16[2] = pSrc[2] )
      {
        v16 = j;
        j += 12;
        *v16 = *pSrc;
        v16[1] = pSrc[1];
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
    v11 = (char *)this->m_nSize;
    v21 = (int)v10;
    for ( k = v10; v11 != v3; k += 12 )
    {
      ((Array *)k)->Copy(v11);
      v11 += 12;
    }
    ((Array *)k)->Copy(pSrc);
    this->Insert(v3, this->m_pData);
    nullsub_2(this->m_nSize, this->m_pData);
    operator delete((void *)this->m_nSize);
    this->m_nCapacity = v21 + 12 * (_DWORD)pPosa;
    v13 = this->Size();
    this->m_nSize = v21;
    this->m_pData = (char *)(v21 + 12 * (v13 + 1));
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

  v3 = p_DWORD2;
  v4 = p_DWORD;
  m_pData = (int *)this->m_pData;
  if ( p_DWORD2 != m_pData )
  {
    do
    {
      v6 = v3;
      v7 = v4;
      v3 += 3;
      v4 += 3;
      *v7 = *v6;
      v7[1] = v6[1];
      v7[2] = v6[2];
    }
    while ( v3 != m_pData );
  }
  this->m_pData = (char *)v4;
  return p_DWORD;
}

// 0x00411170
void * Array::Insert(void *pElem, void *pEnd)
{
  _DWORD *v3; // ecx
  void *result; // eax
  void *v5; // [esp+0xC] [ebp+0xC]

  v3 = pElem;
  if ( pElem == g_SceneMgr.m_pAddEffect2 )
    return v5;
  result = v5;
  do
  {
    if ( result )
    {
      *(_DWORD *)result = *v3;
      *((_DWORD *)result + 1) = v3[1];
      *((_DWORD *)result + 2) = v3[2];
    }
    v3 += 3;
    result = (char *)result + 12;
  }
  while ( v3 != g_SceneMgr.m_pAddEffect2 );
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
        *(_DWORD *)result = *v5;
        *((_DWORD *)result + 1) = v5[1];
        *((_DWORD *)result + 2) = v5[2];
      }
      result = (char *)result + 12;
      --v4;
    }
    while ( v4 );
  }
  return result;
}

// 0x00411240
void * Array::Copy(void *src)
{
  void *result; // eax

  result = dst;
  if ( dst )
  {
    *(_DWORD *)dst = *(_DWORD *)g_SceneMgr.m_pSceneRoot;
    *((_DWORD *)dst + 1) = *((_DWORD *)g_SceneMgr.m_pSceneRoot + 1);
    *((_DWORD *)dst + 2) = *((_DWORD *)g_SceneMgr.m_pSceneRoot + 2);
  }
  return result;
}

// 0x004115C0
unsigned int * Array::PartialSort(
        
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

  result = pdwVal;
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
          v16 = *result;
          v19 = result[1];
          v17 = result;
          v18 = result[2];
          result += 3;
          *v17 = *pdwVal2;
          v17[1] = pdwVal2[1];
          v8 = nVal;
          v17[2] = pdwVal2[2];
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
double Array::HandleItemPage(int nVal, int elem)
{
  void *v3; // esi
  int v4; // edi
  void *v5; // eax
  void *v6; // eax
  bool IsValidItem; // al
  NPC *v9; // ecx
  CScreenMode *Instance; // eax
  char v11; // al
  __int16 v12; // ax
  int v13; // eax
  double result; // st7
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
  ScriptSystem *v26; // esi
  int v27; // eax
  char *v28; // ecx
  char *i; // eax
  char *v30; // edx
  EquipUI *v31; // esi
  char *v32; // edi
  Array *v33; // edi
  char *v34; // ecx
  int v35; // eax
  int v36; // eax
  EquipUI *v37; // eax
  void *v38; // eax
  void *v39; // ecx
  int v40; // ecx
  unsigned int v41; // eax
  char *v42; // eax
  char *v43; // ecx
  int v44; // edi
  Array *v45; // edi
  char *v46; // ecx
  int v47; // eax
  int v48; // edx
  unsigned int v49; // eax
  int v50; // edx
  unsigned int v51; // eax
  char *v52; // eax
  char *v53; // ecx
  int v54; // edi
  int v55; // eax
  int v56; // eax
  int v57; // edx
  float v58; // ecx
  RoleSystem *v59; // esi
  int *v60; // eax
  int v61; // esi
  int v62; // edx
  EquipUI *v63; // esi
  EquipUI *v64; // ecx
  int v65; // edx
  int v66; // edi
  char v67; // al
  int v68; // eax
  _DWORD *v69; // eax
  bool v70; // zf
  int v71; // eax
  _BYTE *v72; // edi
  char *v73; // eax
  int v74; // edi
  int v75; // edx
  char *v76; // eax
  __int16 *v77; // eax
  int v78; // edi
  int j; // esi
  char v80; // cl
  int v81; // ecx
  ScriptSystem *v82; // ecx
  int v83; // esi
  _BYTE *v84; // edi
  ScriptSystem *v85; // esi
  int *v86; // eax
  int v87; // esi
  int v88; // edx
  bool v89; // cc
  void (***v90)(_DWORD, _DWORD); // edi
  int v91; // ebx
  void (***v92)(_DWORD, _DWORD); // edi
  int v93; // ebx
  int v94; // ebx
  int k; // edi
  void (***v96)(_DWORD, _DWORD); // edi
  int v97; // ebx
  int v98; // [esp-0x10] [ebp-0x150]
  const void *v99; // [esp-0x4] [ebp-0x144]
  unsigned int fValue; // [esp+0x0] [ebp-0x140]
  float fValuea; // [esp+0x0] [ebp-0x140]
  float fValueb; // [esp+0x0] [ebp-0x140]
  int v103; // [esp+0x4] [ebp-0x13C]
  char Buffer; // [esp+0x10] [ebp-0x130] BYREF
  _BYTE v105[252]; // [esp+0x11] [ebp-0x12F] BYREF
  __int16 v106; // [esp+0x10D] [ebp-0x33]
  char v107; // [esp+0x10F] [ebp-0x31]
  int v108; // [esp+0x110] [ebp-0x30]
  float v109; // [esp+0x114] [ebp-0x2C]
  int nItemID; // [esp+0x118] [ebp-0x28] BYREF
  int v111; // [esp+0x11C] [ebp-0x24]
  NPC *v112; // [esp+0x120] [ebp-0x20]
  EquipUI *v113; // [esp+0x124] [ebp-0x1C]
  ScriptSystem *p_m_bActionFlag3; // [esp+0x128] [ebp-0x18]
  int pOut; // [esp+0x12C] [ebp-0x14] BYREF
  int v116; // [esp+0x130] [ebp-0x10]
  int RoleNum; // [esp+0x134] [ebp-0xC]
  int v118; // [esp+0x138] [ebp-0x8]
  unsigned int v119; // [esp+0x13C] [ebp-0x4]
  int elema; // [esp+0x148] [ebp+0x8]
  void *elemg; // [esp+0x148] [ebp+0x8]
  char *elemb; // [esp+0x148] [ebp+0x8]
  char *elemc; // [esp+0x148] [ebp+0x8]
  int elemd; // [esp+0x148] [ebp+0x8]
  int eleme; // [esp+0x148] [ebp+0x8]
  float elemh; // [esp+0x148] [ebp+0x8]
  ScriptSystem *elemf; // [esp+0x148] [ebp+0x8]
  char elem_3; // [esp+0x14B] [ebp+0xB]

  v3 = pnVal;
  v4 = 0;
  v113 = (EquipUI *)pnVal;
  if ( pnVal[161] < 0 )
    return result;
  switch ( pnVal[160] )
  {
    case 0:
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(0);
      v5 = (void *)*((_DWORD *)v3 + 48947);
      if ( (int)v5 < 0 )
        goto LABEL_7;
      goto LABEL_6;
    case 1:
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(1);
      v5 = (void *)*((_DWORD *)v3 + 48947);
      if ( (int)v5 >= 0 )
LABEL_6:
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(v5);
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
      v111 = 0;
      v112 = 0;
      v6 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(&pOut, fValue);
      nItemID = *(_DWORD *)v6;
      v111 = *((_DWORD *)v6 + 1);
      v112 = (NPC *)*((_DWORD *)v6 + 2);
      if ( !v112 )
        return result;
      IsValidItem = ((PAL_GDB *)v3)->IsValidItem((int)&nItemID);
      v9 = v112;
      if ( !IsValidItem && *((_BYTE *)&v112->m_AnimWndA + 73) == 1 )
      {
        sprintf((char *const)v3 + 108, "\\n      %s", (const char *)dword_DC9F3C);
        ((UICaption *)((char *)v3 + 155240))->SetEnable((int)v3 + 108, 0);
        ((UIRoleSelect *)((char *)v3 + 154784))->SetByte(1);
        v99 = off_5CADD0;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v99, 1);
        return result;
      }
      v11 = *((_BYTE *)&v112->m_AnimWndA + 73);
      elem_3 = v11;
      if ( v11 != 1 && v11 != 2 || !*((_BYTE *)v3 + 654) || !*((_BYTE *)v3 + 653) )
        return result;
      v12 = *((_WORD *)&v112->m_AnimWndA + 44);
      *(_WORD *)((char *)&v118 + 1) = -30124;
      LOBYTE(v118) = -32;
      if ( v12 )
      {
        *(_WORD *)((char *)&v118 + 1) = -22360;
        goto LABEL_21;
      }
      if ( *((_WORD *)&v112->m_AnimWndA + 45) )
      {
        *(_WORD *)((char *)&v118 + 1) = 22696;
LABEL_21:
        LOBYTE(v118) = 28;
        goto LABEL_22;
      }
      if ( *((_WORD *)&v112->m_AnimWndA + 46) )
      {
        BYTE2(v118) = 28;
        LOWORD(v118) = 22696;
      }
LABEL_22:
      if ( nItemID == 6402 )
        goto LABEL_23;
      if ( nItemID == 6405 )
      {
LABEL_26:
        ((NPC *)v112)->SetSceneFlag();
        ((EquipUI *)v3)->UpdateDisplay(elem, v118);
        goto LABEL_207;
      }
      if ( nItemID != 6404 )
      {
        if ( nItemID == 6403 )
          goto LABEL_26;
        if ( nItemID != 6406 )
        {
          if ( nItemID == 6230 )
          {
            if ( *((_WORD *)&v112->m_wndDialog + 8) )
              v4 = *(&::Buffer.m_partyActor.m_bActionFlag3 + 1408 * elem);
            if ( *((_WORD *)&v112->m_wndDialog + 9) )
              v4 += *(&::Buffer.m_partyActor.m_bActionActive + 1408 * elem);
            if ( *((_WORD *)&v112->m_wndDialog + 6) )
              v4 += *(&::Buffer.m_partyActor.m_nActionParam + 1408 * elem);
            if ( *((_WORD *)&v112->m_wndDialog + 7) )
              v4 += *(&::Buffer.m_partyActor.m_bActionFlag2 + 1408 * elem);
// [VFTABLE] if ( LOWORD(v112->m_AnimWndB.__vftable) )
              v4 += *((unsigned __int8 *)&::Buffer.m_partyActor.m_nActionState + 1408 * elem);
            if ( v4 <= 0 )
            {
              *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * elem + 39] = 1;
              fValuea = (float)(int)::Buffer.m_partyActor.m_dwMatMsg[352 * elem + 9];
              ((UIScrollBar *)((char *)v3 + 4892 * elem + 156952))->SetRange(fValuea);
              result = (double)*(int *)&::Buffer.m_partyActor.m_curact[1408 * elem + 39];
              fValueb = result;
              ((UIProgressBar *)((char *)v3 + 4892 * elem + 156952))->FindChildByName(fValueb);
            }
            else
            {
              v13 = 1408 * elem;
              *(&::Buffer.m_partyActor.m_bActionFlag3 + v13) = 0;
              *(&::Buffer.m_partyActor.m_bActionActive + v13) = 0;
              *(&::Buffer.m_partyActor.m_nActionParam + v13) = 0;
              *(&::Buffer.m_partyActor.m_bActionFlag2 + v13) = 0;
              *((_BYTE *)&::Buffer.m_partyActor.m_nActionState + v13) = 0;
              if ( elem == g_nCurrentRoleSlot )
                ((ScriptSystem *)(5 * elem))->RunEvent(31, 1);
              ((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164))->ProcessInput();
            }
            goto LABEL_24;
          }
// [VFTABLE] if ( v112->__vftable == (void *)6401 )
          {
            ((EquipUI *)v3)->UpdateDisplay(elem, v118);
            ((PalScriptMgr *)v15)->LoadYlfScript();
            ((MainEquipUI *)*((MainEquipUI **)v3 + 164))->HandleMessage();
            goto LABEL_207;
          }
// [VFTABLE] if ( v112->__vftable == (void *)6427 )
          {
            if ( !FindScriptEventByID(2101) )
              goto LABEL_207;
            ((PalScriptMgr *)v16)->Destroy();
            ((MainEquipUI *)*((MainEquipUI **)v3 + 164))->HandleMessage();
            goto LABEL_24;
          }
          v17 = *((_BYTE *)&v112->m_AnimWndA + 72);
          if ( v17 == 5 )
          {
            v18 = (RoleSystem *)UISceneUpdate();
            ((RoleSystem *)v18)->ResetTransition();
            ((MainEquipUI *)*((MainEquipUI **)v3 + 164))->HandleMessage();
            ((EquipUI *)v3)->UpdateDisplay(elem, v118);
            goto LABEL_207;
          }
          if ( v17 == 7 )
          {
            v116 = 0;
            RoleNum = 0;
            pOut = 306;
            LOWORD(v116) = ((MUIDialog *)v3)->GetPlayerAttField(elem, 306);
            HIWORD(v116) = ((UIListBox *)v3)->GetSkillSlotLevel(elem, pOut);
            Buffer = 0;
            RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pOut);
            memset(v105, 0, sizeof(v105));
            v106 = 0;
            v107 = 0;
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              ((RoleSystem *)*((_DWORD *)&g_SceneMgrPrefix.m_pData + 4 * elem))->CheckVisible();
              ((NPC *)v103)->InitAll();
              sprintf(
                &Buffer,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)dword_DD443C,
                (const char *)dword_DD463C,
                (const char *)(RoleNum + 28));
              ((EquipUI *)v3)->UpdateDisplay(elem, v118);
              *((_BYTE *)v3 + 652) = 0;
              *((_BYTE *)v3 + 654) = 0;
              *((_BYTE *)v3 + 653) = 0;
              ((EquipUI *)v3)->SetGroupVisible(1u);
            }
            else
            {
              sprintf(
                &Buffer,
                "\\n   %s%s",
                (const char *)&::Buffer.m_partyActor.m_fMatrixParamC + 1408 * elem,
                (const char *)dword_DD4B3C);
            }
            ((UICaption *)((char *)v3 + 155240))->SetEnable((int)&Buffer, 0);
            goto LABEL_58;
          }
          if ( v17 == 8 )
          {
            v116 = 0;
            RoleNum = 0;
            pOut = 311;
            LOWORD(v116) = ((MUIDialog *)v3)->GetPlayerAttField(elem, 311);
            HIWORD(v116) = ((UIListBox *)v3)->GetSkillSlotLevel(elem, pOut);
            Buffer = 0;
            RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pOut);
            memset(v105, 0, sizeof(v105));
            v106 = 0;
            v107 = 0;
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              ((RoleSystem *)*((_DWORD *)&g_SceneMgrPrefix.m_pData + 4 * elem))->CheckVisible();
              ((NPC *)v103)->InitAll();
              sprintf(
                &Buffer,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)dword_DD443C,
                (const char *)dword_DD473C,
                (const char *)(RoleNum + 28));
              ((EquipUI *)v3)->UpdateDisplay(elem, v118);
              *((_BYTE *)v3 + 652) = 0;
              *((_BYTE *)v3 + 654) = 0;
              *((_BYTE *)v3 + 653) = 0;
              ((EquipUI *)v3)->SetGroupVisible(1u);
            }
            else
            {
              sprintf(
                &Buffer,
                "\\n   %s%s",
                (const char *)&::Buffer.m_partyActor.m_fMatrixParamC + 1408 * elem,
                (const char *)dword_DD4B3C);
            }
            ((UICaption *)((char *)v3 + 155240))->SetEnable((int)&Buffer, 0);
            ((UIRoleSelect *)((char *)v3 + 154784))->SetByte(1);
            goto LABEL_207;
          }
          if ( v17 == 9 )
          {
            v116 = 0;
            RoleNum = 0;
            pOut = 301;
            LOWORD(v116) = ((MUIDialog *)v3)->GetPlayerAttField(elem, 301);
            HIWORD(v116) = ((UIListBox *)v3)->GetSkillSlotLevel(elem, pOut);
            RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pOut);
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              v19 = &g_SceneMgrPrefix + elem;
              m_pData = v19->m_pData;
              if ( (v19->m_nCapacity - (int)m_pData) / 12 )
              {
                ((Array *)&g_SceneMgrPrefix + elem)->Insert(m_pData, m_pData);
                ((Array *)&g_SceneMgrPrefix + elem)->Erase((int)v19->m_pData, 1 - (v19->m_pData - m_pData) / 12);
                v28 = v19->m_pData;
                for ( i = m_pData; i != v28; *((_DWORD *)v30 + 2) = RoleNum )
                {
                  v30 = i;
                  i += 12;
                  *(_DWORD *)v30 = pOut;
                  *((_DWORD *)v30 + 1) = v116;
                }
                v19->m_pData += 12;
              }
              else
              {
                if ( (unsigned int)((Array *)v19)->Size() <= 1 )
                  elema = 1;
                else
                  elema = ((Array *)v19)->Size();
                v21 = ((Array *)v19)->Size();
                v22 = elema + v21 < 0;
                v23 = elema + v21;
                v119 = v23;
                if ( v22 )
                  v23 = 0;
                v24 = (ScriptSystem *)operator new(12 * v23);
                m_nSize = (void *)v19->m_nSize;
                p_m_bActionFlag3 = v24;
                elemg = ((Array *)&g_SceneMgrPrefix + elem)->Insert(m_nSize, m_pData);
                ((Array *)v19)->Erase((int)elemg, 1);
                ((Array *)&g_SceneMgrPrefix + elem)->Insert(m_pData, v19->m_pData);
                nullsub_2(v19->m_nSize, v19->m_pData);
                operator delete((void *)v19->m_nSize);
                v26 = p_m_bActionFlag3;
                v19->m_nCapacity = (int)p_m_bActionFlag3 + 12 * v119;
                v27 = ((Array *)&g_SceneMgrPrefix + elem)->Size();
                v19->m_nSize = (int)v26;
                v19->m_pData = (char *)(&v26->m_vPos_z + 3 * v27);
              }
              ((NPC *)v103)->InitAll();
              v31 = v113;
              v32 = &v113->buf[28];
              sprintf(
                &v113->buf[28],
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)dword_DD443C,
                (const char *)dword_DD483C,
                (const char *)(RoleNum + 28));
              *((_BYTE *)&v31->m_EquipData + 276) = 0;
              *((_BYTE *)&v31->m_EquipData + 278) = 0;
              *((_BYTE *)&v31->m_EquipData + 277) = 0;
              ((EquipUI *)v31)->SetGroupVisible(1u);
              ((EquipUI *)v31)->UpdateDisplay(elem, v118);
            }
            else
            {
              v32 = (char *)v3 + 108;
              sprintf(
                (char *const)v3 + 108,
                "\\n   %s%s",
                (const char *)&::Buffer.m_partyActor.m_fMatrixParamC + 1408 * elem,
                (const char *)dword_DD4B3C);
              v31 = v113;
            }
            ((UICaption *)&v31[1].m_Arrow[1][3][4].m_childs.m_nSize)->SetEnable((int)v32, 0);
            ((UIRoleSelect *)&v31[1].m_Arrow[1][3][1].m_childs.m_nSize)->SetByte(1);
            goto LABEL_206;
          }
          if ( v17 == 10 )
          {
            v116 = 0;
            RoleNum = 0;
            pOut = 316;
            LOWORD(v116) = ((MUIDialog *)v3)->GetPlayerAttField(elem, 316);
            HIWORD(v116) = ((UIListBox *)v3)->GetSkillSlotLevel(elem, pOut);
            RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pOut);
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              v33 = &g_SceneMgrPrefix + elem;
              v34 = v33->m_pData;
              elemb = v34;
              if ( (v33->m_nCapacity - (int)v34) / 12 )
              {
                ((Array *)&g_SceneMgrPrefix + elem)->Insert(v34, v34);
                ((Array *)&g_SceneMgrPrefix + elem)->Erase((int)v33->m_pData, 1 - (v33->m_pData - elemb) / 12);
                v42 = elemb;
                v119 = (unsigned int)v33->m_pData;
                if ( elemb != (char *)v119 )
                {
                  do
                  {
                    v43 = v42;
                    v42 += 12;
                    *(_DWORD *)v43 = pOut;
                    *((_DWORD *)v43 + 1) = v116;
                    *((_DWORD *)v43 + 2) = RoleNum;
                  }
                  while ( v42 != (char *)v119 );
                }
                v33->m_pData += 12;
              }
              else
              {
                v35 = v33->m_nSize;
                if ( v35 && (unsigned int)((int)&v34[-v35] / 12) > 1 )
                  v119 = ((Array *)&g_SceneMgrPrefix + elem)->Size();
                else
                  v119 = 1;
                v36 = ((Array *)&g_SceneMgrPrefix + elem)->Size();
                v22 = (int)(v119 + v36) < 0;
                v37 = (EquipUI *)(v119 + v36);
                v113 = v37;
                if ( v22 )
                  v37 = 0;
                v38 = operator new(12 * (_DWORD)v37);
                v39 = (void *)v33->m_nSize;
                v119 = (unsigned int)v38;
                p_m_bActionFlag3 = (ScriptSystem *)((Array *)&g_SceneMgrPrefix + elem)->Insert(v39, elemb);
                ((Array *)&g_SceneMgrPrefix + elem)->Erase((int)p_m_bActionFlag3, 1);
                ((Array *)&g_SceneMgrPrefix + elem)->Insert(elemb, v33->m_pData);
                nullsub_2(v33->m_nSize, v33->m_pData);
                operator delete((void *)v33->m_nSize);
                v33->m_nCapacity = v119 + 12 * (_DWORD)v113;
                v40 = 3 * (((Array *)&g_SceneMgrPrefix + elem)->Size() + 1);
                v41 = v119;
                v33->m_nSize = v119;
                v33->m_pData = (char *)(v41 + 4 * v40);
              }
              ((NPC *)v103)->InitAll();
              v44 = (int)v3 + 108;
              sprintf(
                (char *const)v3 + 108,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)dword_DD443C,
                (const char *)dword_DD453C,
                (const char *)(RoleNum + 28));
LABEL_109:
              *((_BYTE *)v3 + 652) = 0;
              *((_BYTE *)v3 + 654) = 0;
              *((_BYTE *)v3 + 653) = 0;
              ((EquipUI *)v3)->SetGroupVisible(1u);
              ((EquipUI *)v3)->UpdateDisplay(elem, v118);
              ((UICaption *)((char *)v3 + 155240))->SetEnable(v44, 0);
LABEL_58:
              ((UIRoleSelect *)((char *)v3 + 154784))->SetByte(1);
              goto LABEL_207;
            }
          }
          else
          {
            if ( v17 != 11 )
            {
              if ( v17 == 15 )
              {
                v54 = *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 8]
                    - ((Role *)elem)->CalcXueJianInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                v55 = ((Role *)elem)->CalcZiXuanInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                v98 = *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4];
                v119 = *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 16] - v55;
                elemd = *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 12]
                      - ((Role *)elem)->CalcLongKuiInit(v98);
                p_m_bActionFlag3 = (ScriptSystem *)(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 20]
                                                  - ((Role *)elem)->CalcChangQingInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]));
                v56 = ((Role *)elem)->CalcHuaYingInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                v57 = *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4] + 1;
                LODWORD(v109) = *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 24] - v56;
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4] = v57;
                if ( v57 >= 99 )
                  *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4] = 99;
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 8] = ((Role *)elem)->CalcXueJianInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 12] = ((Role *)elem)->CalcLongKuiInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 16] = ((Role *)elem)->CalcZiXuanInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 20] = ((Role *)elem)->CalcChangQingInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 24] = ((Role *)elem)->CalcHuaYingInit(*(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 4]);
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 8] += v54;
                v58 = v109;
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 12] += elemd;
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 16] += v119;
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 20] += p_m_bActionFlag3;
                *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * elem + 24] += LODWORD(v58);
                v59 = (RoleSystem *)((char *)&::Buffer + 1408 * elem);
                ((RoleSystem *)v59)->RecalcAggregatedStats(0);
                v60 = (int *)&v59->m_partyActor.m_curact[39];
                v61 = 12;
                do
                {
                  v62 = *(v60 - 12);
                  if ( *v60 < v62 )
                  {
                    if ( *v60 <= 0 )
                      *v60 = 0;
                  }
                  else
                  {
                    *v60 = v62;
                  }
                  ++v60;
                  --v61;
                }
                while ( v61 );
                v63 = v113;
                v64 = v113;
                *((_BYTE *)&v113->m_EquipData + 276) = 0;
                *((_BYTE *)&v64->m_EquipData + 278) = 0;
                *((_BYTE *)&v64->m_EquipData + 277) = 0;
                ((EquipUI *)v64)->SetGroupVisible(1u);
                ((EquipUI *)v63)->UpdateDisplay(elem, v118);
                ((StateUI *)v63)->UpdateScrollValues();
              }
              else
              {
                if ( elem_3 == 1 )
                {
                  v65 = 644;
                  v66 = 0;
                  eleme = 644;
                  do
                  {
                    v67 = *((_BYTE *)&v9->m_AnimWndA + v66 + 75);
                    if ( v67 == 1 )
                    {
                      v68 = v66 + 352 * elem;
// [VFTABLE] elemh = (double)*(__int16 *)((char *)&v9->__vftable + v65)
                            * 0.0099999998
                            * (double)(int)::Buffer.m_partyActor.m_dwMatMsg[v68 + 9];
                      result = elemh;
                      LODWORD(v109) = (int)elemh;
                      *(_DWORD *)&::Buffer.m_partyActor.m_curact[v68 * 4 + 39] += LODWORD(v109);
                      v9 = v112;
                    }
                    else
                    {
                      if ( v67 == 3 )
                        v69 = (_DWORD *)(4 * (v66 + 352 * elem) + 12600860);
                      else
                        v69 = (_DWORD *)(4 * (v66 + 352 * elem) + 12601196);
// [VFTABLE] *v69 += *(__int16 *)((char *)&v9->__vftable + v65);
                      v65 = eleme;
                    }
                    v65 += 2;
                    ++v66;
                    eleme = v65;
                  }
                  while ( v65 < 668 );
                  if ( *((__int16 *)&v9->m_wndDialog + 8) >= 2 )
                  {
                    v70 = elem == g_nCurrentRoleSlot;
                    *(&::Buffer.m_partyActor.m_bActionFlag3 + 1408 * elem) = 0;
                    if ( v70 )
                      ((ScriptSystem *)(1408 * elem))->RunEvent(31, 1);
                    ((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164))->ProcessInput();
                    v9 = v112;
                  }
                  if ( *((__int16 *)&v9->m_wndDialog + 9) >= 2 )
                  {
                    *(&::Buffer.m_partyActor.m_bActionActive + 1408 * elem) = 0;
                    if ( elem == g_nCurrentRoleSlot )
                      ((ScriptSystem *)v9)->RunEvent(31, 1);
                    ((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164))->ProcessInput();
                    v9 = v112;
                  }
                  if ( *((__int16 *)&v9->m_wndDialog + 6) >= 2 )
                  {
                    v70 = elem == g_nCurrentRoleSlot;
                    *(&::Buffer.m_partyActor.m_nActionParam + 1408 * elem) = 0;
                    if ( v70 )
                      ((ScriptSystem *)(5 * elem))->RunEvent(31, 1);
                    ((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164))->ProcessInput();
                    v9 = v112;
                  }
                  if ( *((__int16 *)&v9->m_wndDialog + 7) >= 2 )
                  {
                    v70 = elem == g_nCurrentRoleSlot;
                    *(&::Buffer.m_partyActor.m_bActionFlag2 + 1408 * elem) = 0;
                    if ( v70 )
                      ((ScriptSystem *)(1408 * elem))->RunEvent(31, 1);
                    ((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164))->ProcessInput();
                    v9 = v112;
                  }
// [VFTABLE] if ( SLOWORD(v9->m_AnimWndB.__vftable) >= 2 )
                  {
                    *((_BYTE *)&::Buffer.m_partyActor.m_nActionState + 1408 * elem) = 0;
                    if ( elem == g_nCurrentRoleSlot )
                      ((ScriptSystem *)v9)->RunEvent(31, 1);
                    ((Comp_DonateUI *)*((Comp_DonateUI **)v3 + 164))->ProcessInput();
                    v9 = v112;
                  }
                  v71 = 0;
                  v72 = &v9->m_wndDialog + 3;
                  do
                  {
                    if ( (unsigned int)v71 > 0xC )
                      *(&::Buffer.m_partyActor.m_nActionParam + 1408 * elem + v71) = *v72;
                    ++v71;
                    v72 += 2;
                  }
                  while ( v71 < 31 );
                  ((RoleSystem *)((char *)&::Buffer + 1408 * elem))->RecalcAggregatedStats(0);
                  v73 = &::Buffer.m_partyActor.m_curact[1408 * elem + 39];
                  v74 = 12;
                  do
                  {
                    v75 = *((_DWORD *)v73 - 12);
                    if ( *(_DWORD *)v73 < v75 )
                    {
                      if ( *(int *)v73 <= 0 )
                        *(_DWORD *)v73 = 0;
                    }
                    else
                    {
                      *(_DWORD *)v73 = v75;
                    }
                    v73 += 4;
                    --v74;
                  }
                  while ( v74 );
                  goto LABEL_24;
                }
                if ( elem_3 != 2 )
                  goto LABEL_207;
                v76 = 0;
                p_m_bActionFlag3 = (ScriptSystem *)&::Buffer.m_partyActor.m_bActionFlag3;
                elemf = 0;
                v119 = 0;
                while ( 1 )
                {
                  if ( v76[(_DWORD)v3 + 621] && ((PAL_GDB *)v3)->IsValidItem((int)&nItemID) )
                  {
                    v77 = (__int16 *)v112;
                    v78 = 0;
                    for ( j = 322; j < 334; ++j )
                    {
                      v80 = *((_BYTE *)v77 + v78 + 631);
                      if ( v80 == 1 )
                      {
                        v81 = v78 + v119;
                        v109 = (float)(::Buffer.m_partyActor.m_dwMatMsg[v81 + 9] * (v77[j] / 100));
                        result = v109;
                        v108 = (int)v109;
                        *(_DWORD *)&::Buffer.m_partyActor.m_curact[v81 * 4 + 39] += v108;
                        v77 = (__int16 *)v112;
                      }
                      else if ( v80 == 3 )
                      {
                        *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[4 * v78 + 8 + 4 * v119] += v77[j];
                      }
                      else
                      {
                        *(_DWORD *)&::Buffer.m_partyActor.m_curact[4 * v78 + 39 + 4 * v119] += v77[j];
                      }
                      ++v78;
                    }
                    v82 = p_m_bActionFlag3;
                    v83 = 0;
                    v84 = v77 + 350;
                    do
                    {
                      if ( (unsigned int)v83 > 0xC )
                        *((_BYTE *)v82 + v83 - 2) = *v84;
                      ++v83;
                      v84 += 2;
                    }
                    while ( v83 < 31 );
                    if ( v77[352] >= 2 )
                    {
                      LOBYTE(v82->m_nSlotID) = 0;
                      if ( elemf == (ScriptSystem *)g_nCurrentRoleSlot )
                        ((ScriptSystem *)v82)->RunEvent(31, 1);
                      ((Comp_DonateUI *)*((Comp_DonateUI **)&v113->m_EquipData + 70))->ProcessInput();
                      v77 = (__int16 *)v112;
                      v82 = p_m_bActionFlag3;
                    }
                    if ( v77[353] >= 2 )
                    {
                      BYTE1(v82->m_nSlotID) = 0;
                      if ( elemf == (ScriptSystem *)g_nCurrentRoleSlot )
                        ((ScriptSystem *)v82)->RunEvent(31, 1);
                      ((Comp_DonateUI *)*((Comp_DonateUI **)&v113->m_EquipData + 70))->ProcessInput();
                      v77 = (__int16 *)v112;
                      v82 = p_m_bActionFlag3;
                    }
                    if ( v77[350] >= 2 )
                    {
                      BYTE2(v82[-1].m_nSaveDir) = 0;
                      if ( elemf == (ScriptSystem *)g_nCurrentRoleSlot )
                        ((ScriptSystem *)v82)->RunEvent(31, 1);
                      ((Comp_DonateUI *)*((Comp_DonateUI **)&v113->m_EquipData + 70))->ProcessInput();
                      v77 = (__int16 *)v112;
                      v82 = p_m_bActionFlag3;
                    }
                    if ( v77[351] >= 2 )
                    {
                      HIBYTE(v82[-1].m_nSaveDir) = 0;
                      if ( elemf == (ScriptSystem *)g_nCurrentRoleSlot )
                        ((ScriptSystem *)v82)->RunEvent(31, 1);
                      ((Comp_DonateUI *)*((Comp_DonateUI **)&v113->m_EquipData + 70))->ProcessInput();
                      v77 = (__int16 *)v112;
                    }
                    if ( v77[354] >= 2 )
                    {
                      BYTE2(p_m_bActionFlag3->m_nSlotID) = 0;
                      if ( elemf == (ScriptSystem *)g_nCurrentRoleSlot )
                        ((ScriptSystem *)elemf)->RunEvent(31, 1);
                      ((Comp_DonateUI *)*((Comp_DonateUI **)&v113->m_EquipData + 70))->ProcessInput();
                    }
                    v85 = p_m_bActionFlag3;
                    ((RoleSystem *)((char *)&p_m_bActionFlag3[-1]._todo_5C8 + 6538))->RecalcAggregatedStats(0);
                    v86 = (int *)((char *)&v85->_todo_10C + 18);
                    v87 = 12;
                    do
                    {
                      v88 = *(v86 - 12);
                      if ( *v86 < v88 )
                      {
                        if ( *v86 <= 0 )
                          *v86 = 0;
                      }
                      else
                      {
                        *v86 = v88;
                      }
                      ++v86;
                      --v87;
                    }
                    while ( v87 );
                    if ( ((PAL_GDB *)v113)->IsValidItem((int)&nItemID) )
                      ((EquipUI *)v113)->UpdateDisplay((int)elemf, v118);
                  }
                  v76 = (char *)&elemf->m_nSlotID + 1;
                  v89 = (int)(&p_m_bActionFlag3->_todo_56C + 5) < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[148] + 2;
                  elemf = (ScriptSystem *)((char *)elemf + 1);
                  v119 += 352;
                  p_m_bActionFlag3 = (ScriptSystem *)((char *)p_m_bActionFlag3 + 1408);
                  if ( !v89 )
                    break;
                  v3 = v113;
                }
              }
LABEL_206:
              v3 = v113;
              goto LABEL_207;
            }
            v116 = 0;
            RoleNum = 0;
            pOut = 321;
            LOWORD(v116) = ((MUIDialog *)v3)->GetPlayerAttField(elem, 321);
            HIWORD(v116) = ((UIListBox *)v3)->GetSkillSlotLevel(elem, pOut);
            RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pOut);
            if ( *(_BYTE *)(RoleNum + elem + 572) )
            {
              RefreshPartyRoleData();
              v45 = &g_SceneMgrPrefix + elem;
              v46 = v45->m_pData;
              elemc = v46;
              if ( (v45->m_nCapacity - (int)v46) / 12 )
              {
                ((Array *)&g_SceneMgrPrefix + elem)->Insert(v46, v46);
                ((Array *)&g_SceneMgrPrefix + elem)->Erase((int)v45->m_pData, 1 - (v45->m_pData - elemc) / 12);
                v52 = elemc;
                v119 = (unsigned int)v45->m_pData;
                if ( elemc != (char *)v119 )
                {
                  do
                  {
                    v53 = v52;
                    v52 += 12;
                    *(_DWORD *)v53 = pOut;
                    *((_DWORD *)v53 + 1) = v116;
                    *((_DWORD *)v53 + 2) = RoleNum;
                  }
                  while ( v52 != (char *)v119 );
                }
                v45->m_pData += 12;
              }
              else
              {
                v47 = v45->m_nSize;
                if ( !v47 || (v119 = (int)&v46[-v47] / 12, v119 <= 1) )
                  v119 = 1;
                if ( v45->m_nSize )
                  v48 = (int)&v46[-v45->m_nSize] / 12;
                else
                  v48 = 0;
                v49 = v48 + v119;
                v113 = (EquipUI *)(v48 + v119);
                if ( (int)(v48 + v119) < 0 )
                  v49 = 0;
                v119 = (unsigned int)operator new(12 * v49);
                p_m_bActionFlag3 = (ScriptSystem *)((Array *)&g_SceneMgrPrefix + elem)->Insert((void *)v45->m_nSize, elemc);
                ((Array *)&g_SceneMgrPrefix + elem)->Erase((int)p_m_bActionFlag3, 1);
                ((Array *)&g_SceneMgrPrefix + elem)->Insert(elemc, v45->m_pData);
                operator delete((void *)v45->m_nSize);
                v45->m_nCapacity = v119 + 12 * (_DWORD)v113;
                v50 = 3 * (((Array *)&g_SceneMgrPrefix + elem)->Size() + 1);
                v51 = v119;
                v45->m_nSize = v119;
                v45->m_pData = (char *)(v51 + 4 * v50);
              }
              ((NPC *)v103)->InitAll();
              v44 = (int)v3 + 108;
              sprintf(
                (char *const)v3 + 108,
                "\\n %s%s%s\\n\\n        %s",
                &g_szRoleNameTable[256 * elem],
                (const char *)dword_DD443C,
                (const char *)dword_DD493C,
                (const char *)(RoleNum + 28));
              goto LABEL_109;
            }
          }
          sprintf(
            (char *const)v3 + 108,
            "\\n   %s%s",
            (const char *)&::Buffer.m_partyActor.m_fMatrixParamC + 1408 * elem,
            (const char *)dword_DD4B3C);
          ((UICaption *)((char *)v3 + 155240))->SetEnable((int)v3 + 108, 0);
          goto LABEL_58;
        }
      }
LABEL_23:
      ((NPC *)v112)->SetSceneFlag();
LABEL_24:
      ((EquipUI *)v3)->UpdateDisplay(elem, v118);
LABEL_207:
      if ( *((_BYTE *)v3 + 652) )
      {
        if ( v111 - 1 > 0 )
        {
          if ( ((PAL_GDB *)v3)->IsValidItem((int)&nItemID) )
            goto LABEL_225;
          v94 = 0;
          for ( k = 0; k < 5; ++k )
          {
            if ( *((_BYTE *)v3 + k + 621) && ((PAL_GDB *)v3)->IsValidItem((int)&nItemID) )
              ++v94;
          }
          if ( v94 )
          {
LABEL_225:
            ((PAL_GDB *)v3)->SelectBestTarget(*((_DWORD *)v3 + 161));
          }
          else
          {
            *((_BYTE *)v3 + 652) = 0;
            v96 = (void ( ***)(_DWORD, _DWORD))((char *)v3 + 160876);
            v97 = 5;
            do
            {
              (**v96)(v96, 0);
              v96 += 1223;
              --v97;
            }
            while ( v97 );
          }
        }
        else
        {
          *((_BYTE *)v3 + 652) = 0;
          v92 = (void ( ***)(_DWORD, _DWORD))((char *)v3 + 160876);
          v93 = 5;
          do
          {
            (**v92)(v92, 0);
            v92 += 1223;
            --v93;
          }
          while ( v93 );
        }
      }
      else
      {
        v90 = (void ( ***)(_DWORD, _DWORD))((char *)v3 + 160876);
        v91 = 5;
        do
        {
          (**v90)(v90, 0);
          v90 += 1223;
          --v91;
        }
        while ( v91 );
      }
      if ( nItemID != 6427 )
      {
        v111 = 1;
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&nItemID);
      }
      ((MainEquipUI *)v3)->SetupRoleList(*((_DWORD *)v3 + 160), 0);
      if ( !*((_BYTE *)v3 + 652) )
      {
        *((_BYTE *)v3 + 654) = 0;
        *((_BYTE *)v3 + 653) = 0;
        ((EquipUI *)v3)->SetGroupVisible(1u);
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
result = this->m_pData;
  v6 = dwVal;
  if ( (this->m_nCapacity - (int)result) >> 4 >= dwVal )
  {
    if ( (result - pszBuf) >> 4 >= dwVal )
    {
      if ( dwVal )
      {
        v29 = 16 * dwVal;
        m_pData = this->m_pData;
        v31 = &result[-16 * dwVal];
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
        v32 = this->m_pData;
        for ( i = &v32[-v29]; i != pszBuf; *((_DWORD *)v32 + 3) = *((_DWORD *)i + 3) )
        {
          i -= 16;
          v32 -= 16;
          *(_DWORD *)v32 = *(_DWORD *)i;
          *((_DWORD *)v32 + 1) = *((_DWORD *)i + 1);
          *((_DWORD *)v32 + 2) = *((_DWORD *)i + 2);
        }
        for ( j = pszBuf; j != &pszBuf[v29]; v35[3] = p_DWORD[3] )
        {
          v35 = j;
          j += 16;
          *v35 = *p_DWORD;
          v35[1] = p_DWORD[1];
          v35[2] = p_DWORD[2];
        }
        this->m_pData += v29;
        return (char *)this;
      }
    }
    else
    {
      v20 = 16 * dwVal;
      v21 = &pszBuf[16 * dwVal];
      if ( pszBuf != result )
      {
        v22 = &v21[-v20];
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
      v23 = this->m_pData;
      v24 = p_DWORD;
      v25 = v6 - ((v23 - pszBuf) >> 4);
      if ( v25 )
      {
        do
        {
          if ( v23 )
          {
            *(_DWORD *)v23 = *v24;
            *((_DWORD *)v23 + 1) = v24[1];
            *((_DWORD *)v23 + 2) = v24[2];
            *((_DWORD *)v23 + 3) = v24[3];
            v24 = p_DWORD;
          }
          v23 += 16;
          --v25;
        }
        while ( v25 );
}
      v26 = this->m_pData;
      for ( k = pszBuf; k != v26; v28[3] = v24[3] )
      {
        v28 = k;
        k += 16;
        *v28 = *v24;
        v28[1] = v24[1];
        v28[2] = v24[2];
      }
      this->m_pData += v20;
      return (char *)this;
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
    v12 = v37;
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
    v14 = v12;
    if ( v6 )
    {
      pszBufa = (char *)v6;
      do
      {
        if ( v14 )
        {
          *v14 = *p_DWORD;
          v14[1] = p_DWORD[1];
          v14[2] = p_DWORD[2];
          v14[3] = p_DWORD[3];
        }
        v14 += 4;
        --pszBufa;
      }
      while ( pszBufa );
}
    v15 = this->m_pData;
    v16 = &v12[4 * v6];
    if ( pszBuf != v15 )
    {
      v17 = pszBuf;
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
      v19 = this->m_pData;
      this->m_nSize = (int)v37;
      result = (char *)&v37[4 * v6 + 4 * ((int)&v19[-v18] >> 4)];
    }
    else
    {
      this->m_nSize = (int)v37;
      result = (char *)&v37[4 * v6];
    }
    this->m_pData = result;
  }
  return result;
}
