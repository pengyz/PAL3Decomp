#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStageRole.h"

// Forward declarations for unnamed functions
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc); // from annotations
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations
int sub_4DB940(_BYTE *_this, char a2); // from annotations
void sub_536D20(Actor *_this, const char *a2, int a3); // from annotations
void __cdecl todo_401800(void);
int todo_408BD0(...);

int * ctor_0x431870(int *_this); // from annotations

// Unnamed globals (extern)
extern char byte_17AB818[16];
extern char byte_17AB9C4;
extern char byte_1895558;
extern char byte_5967B0[3];
extern int dword_17AB9B8;
extern int dword_17AB9BC;
extern int dword_17AB9C0;
extern int dword_17AB9C8;
extern int dword_17AB9CC;
extern int dword_17AB9D8;
extern int dword_17AB9DC;
extern int dword_17ABC7C;
extern int dword_17ABC80;
extern int dword_17ABC84;
extern int dword_17ABC88;
extern int dword_17ABC8C;
extern int dword_17ABC90;
extern int dword_17ABC94;
extern int dword_17ABC98;
extern int dword_17ABC9C;
extern int dword_17ABCA0;
extern int dword_17ABCA4;
extern int dword_17ABCA8;
extern int dword_17ABCAC;
extern int dword_17ABCB0;
extern int dword_17ABCB4;
extern int dword_17ABCB8;
extern int dword_56FE98[];
extern int dword_5888BC;
extern int dword_5888C4;
extern int dword_5888C8;
extern int dword_5888D0;
extern float flt_17ABCCC;
extern float flt_17ABCD0;
extern float flt_17ABCD4;
extern float flt_17ABCD8;
void __cdecl nullsub_2(...);
void __cdecl nullsub_22(void);
void __cdecl nullsub_23(void);
void __cdecl nullsub_24(void);
void __cdecl nullsub_25(void);
void __cdecl nullsub_26(void);
void __cdecl nullsub_27(void);
void __cdecl nullsub_32(void);
void __cdecl nullsub_33(void);
void __cdecl nullsub_34(void);
void __cdecl nullsub_35(void);
void __cdecl nullsub_36(void);
void __cdecl nullsub_37(void);
void __cdecl nullsub_38(void);
void __cdecl nullsub_39(void);
void __cdecl nullsub_40(void);
void __cdecl nullsub_41(void);
void __cdecl nullsub_42(void);
void __cdecl nullsub_43(void);
void __cdecl nullsub_44(void);
void __cdecl nullsub_45(void);
void __cdecl nullsub_46(void);
void __cdecl nullsub_47(void);
void __cdecl nullsub_48(void);
void __cdecl nullsub_49(void);
void __cdecl nullsub_50(void);
void __cdecl nullsub_51(void);
void __cdecl nullsub_52(void);
void __cdecl nullsub_53(void);
void __cdecl nullsub_54(void);
extern char unk_5D89A4;
extern unsigned int unk_5DFDEC;

// 0x0040CC90
void CCBStageRole::Init(int thisa)
{
  operator delete((void *)this->m_sRoleArray.m_nSize);
  this->m_sRoleArray.m_nSize = 0;
  this->m_sRoleArray.m_pData = 0;
  this->m_sRoleArray.m_nCapacity = 0;
  operator delete(this->m_pRoleState);
  this->m_pRoleState = 0;
  *(_DWORD *)this->m_sLastRole = 0;
  *(_DWORD *)&this->m_sLastRole[4] = 0;
}

// 0x0040CCF0
char * CCBStageRole::GetAlive(int thisa, int *pConfig)
{
  char *result; // eax
  CCBRoleState *v5; // ecx
  CCBRoleState *v6; // edi
  CCBRoleState *m_pRoleState; // ebx
  unsigned int v8; // ebp
  int v9; // edx
  unsigned int v10; // eax
  char *v11; // eax
  CCBRoleState *v12; // ebp
  char *j; // ebx
  CCBRoleState *v14; // eax
  int v15; // ecx
  CCBRoleState *v16; // ecx
  CCBRoleState *i; // eax
  CCBRoleState *v18; // edi
  int v19; // ecx
  unsigned int v20; // [esp+0x10] [ebp-0x8]
  char *v21; // [esp+0x14] [ebp-0x4]

  result = (char *)this->GetByIndex((int *)thisa);
  if ( result )
  {
    v19 = *(_DWORD *)(thisa + 4) + *((_DWORD *)result + 1);
    if ( v19 > 99 )
      v19 = 99;
    *((_DWORD *)result + 1) = v19;
  }
  else
  {
    v5 = *(CCBRoleState **)this->m_sLastRole;
    v6 = v5;
    if ( (*(_DWORD *)&this->m_sLastRole[4] - (int)v5) / 12 )
    {
      ((Array *)this)->Insert(v5, v5);
      ((Array *)this)->Erase(*(_DWORD *)this->m_sLastRole, 1 - (*(_DWORD *)this->m_sLastRole - (int)v6) / 12);
      v16 = *(CCBRoleState **)this->m_sLastRole;
      for ( i = v6; i != v16; v18->_embed_UIFrameWnd_168.m_fontcolor.Color = *(_DWORD *)(thisa + 8) )
      {
        v18 = i;
        i = (CCBRoleState *)((char *)i + 12);
        *(_DWORD *)v18->m_sCombatDialog = *(_DWORD *)thisa;
// [VFTABLE] v18->_embed_UIFrameWnd_168.__vftable = *(vtbl_0056AE2C **)(thisa + 4);
      }
      result = (char *)(*(_DWORD *)this->m_sLastRole + 12);
      *(_DWORD *)this->m_sLastRole = result;
    }
    else
    {
      m_pRoleState = this->m_pRoleState;
      if ( !m_pRoleState || (v8 = ((char *)v5 - (char *)m_pRoleState) / 12, v8 <= 1) )
        v8 = 1;
      if ( m_pRoleState )
        v9 = ((char *)v5 - (char *)m_pRoleState) / 12;
      else
        v9 = 0;
      v10 = v9 + v8;
      v20 = v9 + v8;
      if ( (int)(v9 + v8) < 0 )
        v10 = 0;
      v11 = (char *)operator new(12 * v10);
      v12 = this->m_pRoleState;
      v21 = v11;
      for ( j = v11; v12 != v6; j += 12 )
      {
        ((Array *)j)->Copy(v12);
        v12 = (CCBRoleState *)((char *)v12 + 12);
      }
      ((Array *)this)->Erase((int)j, 1);
      ((Array *)this)->Insert(v6, *(void **)this->m_sLastRole);
      nullsub_2(this->m_pRoleState, *(_DWORD *)this->m_sLastRole);
      operator delete(this->m_pRoleState);
      *(_DWORD *)&this->m_sLastRole[4] = &v21[12 * v20];
      v14 = this->m_pRoleState;
      if ( v14 )
      {
        v15 = *(_DWORD *)this->m_sLastRole;
        this->m_pRoleState = (CCBRoleState *)v21;
        result = &v21[12 * ((v15 - (int)v14) / 12) + 12];
        *(_DWORD *)this->m_sLastRole = result;
      }
      else
      {
        this->m_pRoleState = (CCBRoleState *)v21;
        *(_DWORD *)this->m_sLastRole = v21 + 12;
        return v21 + 12;
      }
    }
  }
  return result;
}

// 0x0040CF60
int CCBStageRole::PassCmd(void *p_DWORD)
{
  int *v3; // eax
  int v4; // ecx
  int *v5; // edx
  int *v6; // eax
  int *v7; // ecx
  int *v8; // edi
  int *v9; // ebx

  v3 = this->GetByIndex((int *)p_DWORD);
  if ( !v3 )
    return 0;
  v4 = v3[1] - *((_DWORD *)p_DWORD + 1);
  v3[1] = v4;
  if ( v4 > 0 )
    return 1;
  v5 = *(int **)this->m_sLastRole;
  v6 = v3 + 3;
  if ( v6 != v5 )
  {
    v7 = v6 - 3;
    do
    {
      v8 = v6;
      v9 = v7;
      v6 += 3;
      v7 += 3;
      *v9 = *v8;
      v9[1] = v8[1];
      v9[2] = v8[2];
    }
    while ( v6 != v5 );
  }
  *(_DWORD *)this->m_sLastRole -= 12;
  return 2;
}

// 0x0040D010
int CCBStageRole::CheckValid(int nVal)
{
  Combat *v2; // ebp
  Array *p_m_sRoleArray; // esi
  int v4; // ebx
  Combat v5; // eax
  int v6; // ecx
  int *v7; // eax
  bool v8; // zf
  Combat v9; // ecx
  Combat v10; // edx
  char v11; // al
  Combat v12; // eax
  int v13; // ecx
  char v14; // al
  char v15; // al
  int v16; // eax
  Combat v17; // eax
  int v18; // ecx
  char v19; // dl
  int v20; // eax
  _WORD *v21; // edi
  char *m_pData; // ecx
  char *v23; // edi
  int m_nSize; // ebx
  unsigned int v25; // ebp
  int v26; // edx
  unsigned int v27; // eax
  char *v28; // eax
  char *v29; // ebx
  char *j; // ebp
  char *v31; // ebx
  char *k; // ebp
  int v33; // eax
  char *i; // eax
  char *v35; // edx
  int result; // eax
  _DWORD *src; // [esp+0xC] [ebp-0x18]
  int v39; // [esp+0x14] [ebp-0x10]
  unsigned int v40; // [esp+0x18] [ebp-0xC]
  char *v41; // [esp+0x1C] [ebp-0x8]
  int SlotCount; // [esp+0x20] [ebp-0x4]

  v2 = (Combat *)this;
  p_m_sRoleArray = &this->m_sRoleArray;
  ((Array *)&this->m_sRoleArray)->CopyRange((int *)this->m_sRoleArray.m_nSize, (int *)this->m_sRoleArray.m_pData);
  v4 = 0;
  SlotCount = ((Combat *)v2)->GetSlotCount();
  v39 = 0;
  if ( SlotCount > 0 )
  {
    do
    {
      switch ( nVal )
      {
        case 0:
          v5 = v2[1];
          v6 = *(_DWORD *)(*(_DWORD *)&v5 + 12 * v4 + 8);
          v7 = (int *)(*(_DWORD *)&v5 + 12 * v4);
          v8 = *(_BYTE *)(v6 + 612) == 1;
          goto LABEL_13;
        case 1:
          v7 = (int *)(*(_DWORD *)&v2[1] + 12 * v4);
          v8 = *(_BYTE *)(v7[2] + 612) == 3;
          goto LABEL_13;
        case 2:
          v9 = v2[1];
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v9 + 12 * v4 + 8) + 612) == 2 )
            goto LABEL_5;
          break;
        case 3:
          v10 = v2[1];
          v11 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v10 + 12 * v4 + 8) + 612);
          if ( v11 == 5 || v11 == 12 )
            ((Array *)p_m_sRoleArray)->InsertAt(p_m_sRoleArray->m_pData, (int *)(*(_DWORD *)&v10 + 12 * v4));
          break;
        case 4:
          v9 = v2[1];
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v9 + 12 * v4 + 8) + 612) == 4 )
LABEL_5:
            ((Array *)p_m_sRoleArray)->InsertAt(p_m_sRoleArray->m_pData, (int *)(*(_DWORD *)&v9 + 12 * v4));
          break;
        case 5:
          v12 = v2[1];
          v13 = *(_DWORD *)(*(_DWORD *)&v12 + 12 * v4 + 8);
          v7 = (int *)(*(_DWORD *)&v12 + 12 * v4);
          v8 = *(_BYTE *)(v13 + 612) == 6;
LABEL_13:
          if ( v8 )
            ((Array *)p_m_sRoleArray)->InsertAt(p_m_sRoleArray->m_pData, v7);
          break;
        case 6:
          v14 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612);
          if ( v14 == 7 || v14 == 8 || v14 == 9 || v14 == 10 || v14 == 11 )
            goto LABEL_45;
          break;
        case 7:
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612) == 11 )
            goto LABEL_45;
          break;
        case 8:
          v15 = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612);
          if ( v15 == 7 || v15 == 8 || v15 == 9 )
            goto LABEL_45;
          break;
        case 9:
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612) == 10 )
            goto LABEL_45;
          break;
        case 10:
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612) == 12 )
            goto LABEL_45;
          break;
        case 11:
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612) == 7 )
            goto LABEL_45;
          break;
        case 12:
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612) == 8 )
            goto LABEL_45;
          break;
        case 13:
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8) + 612) == 9 )
            goto LABEL_45;
          break;
        case 14:
          v16 = *(_DWORD *)(*(_DWORD *)&v2[1] + 12 * v4 + 8);
          if ( *(_BYTE *)(v16 + 612) == 1
            && (*(_WORD *)(v16 + 748) == 2
             || *(_BYTE *)(v16 + 631) == 2
             || *(__int16 *)(v16 + 644) > 0
             || *(_BYTE *)(v16 + 632) == 2
             || *(__int16 *)(v16 + 646) > 0
             || *(_BYTE *)(v16 + 633) == 2
             || *(__int16 *)(v16 + 648) > 0) )
          {
LABEL_45:
            ((RoleSystem *)p_m_sRoleArray->m_pData)->CheckVisible();
          }
          break;
        case 15:
          v17 = v2[1];
          v18 = *(_DWORD *)(*(_DWORD *)&v17 + 12 * v4 + 8);
          g_SceneMgr.m_pSceneRoot = (_DWORD *)(*(_DWORD *)&v17 + 12 * v4);
          if ( *(_BYTE *)(v18 + 612) == 1 )
          {
            v19 = 0;
            v20 = 0;
            v21 = (_WORD *)(v18 + 700);
            do
            {
              if ( v20 != 24 && v20 != 23 && (*v21 == 1 || *v21 == 2) )
                v19 = 1;
              ++v20;
              ++v21;
            }
            while ( v20 < 26 );
            if ( v19 )
            {
              m_pData = p_m_sRoleArray->m_pData;
              v23 = m_pData;
              if ( (p_m_sRoleArray->m_nCapacity - (int)m_pData) / 12 )
              {
                ((Array *)p_m_sRoleArray)->Insert(m_pData, m_pData);
                ((Array *)p_m_sRoleArray)->Erase((int)p_m_sRoleArray->m_pData, 1 - (p_m_sRoleArray->m_pData - v23) / 12);
                for ( i = p_m_sRoleArray->m_pData; v23 != i; *((_DWORD *)v35 + 2) = g_SceneMgr.m_pSceneRoot[2] )
                {
                  v35 = v23;
                  v23 += 12;
                  *(_DWORD *)v35 = *g_SceneMgr.m_pSceneRoot;
                  *((_DWORD *)v35 + 1) = g_SceneMgr.m_pSceneRoot[1];
                }
                v2 = (Combat *)this;
                p_m_sRoleArray->m_pData += 12;
              }
              else
              {
                m_nSize = p_m_sRoleArray->m_nSize;
                if ( !m_nSize || (v25 = (int)&m_pData[-m_nSize] / 12, v25 <= 1) )
                  v25 = 1;
                if ( m_nSize )
                  v26 = (int)&m_pData[-m_nSize] / 12;
                else
                  v26 = 0;
                v27 = v26 + v25;
                v40 = v26 + v25;
                if ( (int)(v26 + v25) < 0 )
                  v27 = 0;
                v28 = (char *)operator new(12 * v27);
                v29 = (char *)p_m_sRoleArray->m_nSize;
                v41 = v28;
                for ( j = v28; v29 != v23; j += 12 )
                {
                  ((Array *)j)->Copy(v29);
                  v29 += 12;
                }
                ((Array *)j)->Copy(g_SceneMgr.m_pSceneRoot);
                v31 = p_m_sRoleArray->m_pData;
                for ( k = j + 12; v23 != v31; k += 12 )
                {
                  ((Array *)k)->Copy(v23);
                  v23 += 12;
                }
                nullsub_2(p_m_sRoleArray->m_nSize, p_m_sRoleArray->m_pData);
                operator delete((void *)p_m_sRoleArray->m_nSize);
                p_m_sRoleArray->m_nCapacity = (int)&v41[12 * v40];
                v33 = ((Array *)p_m_sRoleArray)->Size();
                v4 = v39;
                v2 = (Combat *)this;
                p_m_sRoleArray->m_nSize = (int)v41;
                p_m_sRoleArray->m_pData = &v41[12 * v33 + 12];
              }
            }
          }
          break;
        default:
          break;
      }
      v39 = ++v4;
    }
    while ( v4 < SlotCount );
  }
  result = p_m_sRoleArray->m_nSize;
  if ( result )
    return (int)&p_m_sRoleArray->m_pData[-result] / 12;
  return result;
}

// 0x0040DCF0
int * CCBStageRole::GetByIndex(int *p_DWORD)
{
  int *v3; // edi
  int *i; // esi

  v3 = *(int **)this->m_sLastRole;
  for ( i = (int *)this->m_pRoleState->m_sCombatDialog; i != v3; i += 3 )
  {
    if ( ((PtrArray *)i)->CompareValues(p_DWORD) )
      break;
  }
  return *(_DWORD *)this->m_sLastRole != (_DWORD)i ? i : 0;
}

// 0x0040DD30
int CCBStageRole::Find(char *String1)
{
  CCBRoleState *m_pRoleState; // esi

  m_pRoleState = this->m_pRoleState;
  if ( m_pRoleState == *(CCBRoleState **)this->m_sLastRole )
    return 0;
  while ( _strcmpi(String1, (const char *)(m_pRoleState->_embed_UIFrameWnd_168.m_fontcolor.Color + 36)) )
  {
    m_pRoleState = (CCBRoleState *)((char *)m_pRoleState + 12);
    if ( m_pRoleState == *(CCBRoleState **)this->m_sLastRole )
      return 0;
  }
  return 1;
}

// 0x0040DD80
void CCBStageRole::Reset()
{
  CCBRoleState *m_pRoleState; // edx

  m_pRoleState = this->m_pRoleState;
  *(_DWORD *)&this->m_sLastRole[8] = -1;
  *(_DWORD *)this->m_sRoleData = 0;
  *(_DWORD *)this->m_sLastRole = m_pRoleState;
  this->m_sRoleArray.m_pData = (char *)this->m_sRoleArray.m_nSize;
}

// 0x0044CFF0
int CCBStageRole::RandomizePositions()
{
  int v2; // ebx
  float *p_fTemp; // esi

  v2 = 16;
  p_fTemp = &this->m_Task[48].fTemp;
  do
  {
    p_fTemp += 52;
    --v2;
    *((_DWORD *)p_fTemp - 51) = rand() % 50 + 298;
    *((_DWORD *)p_fTemp - 52) = 758;
    *(p_fTemp - 48) = 758.0;
  }
  while ( v2 );
  *(_DWORD *)(&this->m_Task[48].bExecuted + 2) = 256;
  this->m_Task[49].fp[0] = (char *)64;
  this->m_Task[51].fp[3] = (char *)512;
  LODWORD(this->m_Task[51].vec1.x) = 128;
  this->m_Task[53].cmd.dwCmdKind = 128;
  this->m_Task[53].cmd.dwItemID = 64;
  *(_DWORD *)&this->m_Task[55].cmd.bMultiSrcRole = 128;
  *(_DWORD *)&this->m_Task[55].cmd.bSrcRole[2] = 64;
  *(_DWORD *)&this->m_Task[57].cmd.bDestRole[3] = 128;
  *(_DWORD *)&this->m_Task[57].cmd.bDestRole[7] = 64;
  LODWORD(this->m_Task[59].fTemp2) = 128;
  this->m_Task[59].dwID = 64;
  *(_DWORD *)(&this->m_Task[61].bExecuted + 2) = 64;
  this->m_Task[62].fp[0] = (char *)32;
  LODWORD(this->m_vecSunDir.x) = 128;
  LODWORD(this->m_vecSunDir.y) = 128;
  return 128;
}

// 0x004E2C50
void CCBStageRole::InitUIByName()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  HWND v4; // edi
  tagRoleState *inited; // eax
  int v6; // eax
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int RoleGPBak; // eax
  int v11; // eax
  void *Role; // eax
  void *v13; // eax
  tagRoleState *v14; // eax
  tagRoleState *v15; // eax
  tagRoleState *v16; // eax
  tagRoleState *v17; // eax
  tagRoleState *v18; // eax
  tagRoleState *v19; // eax
  unsigned int v20; // [esp-0x4] [ebp-0x40]
  HWND hWnd; // [esp+0x10] [ebp-0x2C]
  HWND v22; // [esp+0x14] [ebp-0x28]
  HWND v23; // [esp+0x18] [ebp-0x24]
  HWND v24; // [esp+0x1C] [ebp-0x20]
  HWND v25; // [esp+0x20] [ebp-0x1C]
  HWND v26; // [esp+0x24] [ebp-0x18]
  HWND v27; // [esp+0x28] [ebp-0x14]
  HWND v28; // [esp+0x2C] [ebp-0x10]
  HWND v29; // [esp+0x30] [ebp-0xC]
  HWND v30; // [esp+0x34] [ebp-0x8]
  HWND v31; // [esp+0x38] [ebp-0x4]

  DlgItem = GetDlgItem(g_hMainWnd, 1024);
  v3 = GetDlgItem(g_hMainWnd, 1026);
  hWnd = GetDlgItem(g_hMainWnd, 1032);
  v22 = GetDlgItem(g_hMainWnd, 1025);
  v23 = GetDlgItem(g_hMainWnd, 1033);
  v24 = GetDlgItem(g_hMainWnd, 1027);
  v25 = GetDlgItem(g_hMainWnd, 1034);
  v26 = GetDlgItem(g_hMainWnd, 1028);
  v27 = GetDlgItem(g_hMainWnd, 1029);
  v28 = GetDlgItem(g_hMainWnd, 1030);
  v29 = GetDlgItem(g_hMainWnd, 1031);
  v30 = GetDlgItem(g_hMainWnd, 1035);
  v31 = GetDlgItem(g_hMainWnd, 1036);
  v4 = GetDlgItem(g_hMainWnd, 1042);
  if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][892 * dwVal + 4] )
  {
    EnableWindow(v4, 1);
    if ( (int)dwVal < 5 )
    {
      switch ( dwVal )
      {
        case 0u:
          v20 = dwVal;
          v7 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Jingtian");
          goto LABEL_11;
        case 1u:
          v20 = dwVal;
          v7 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Xuejian");
          goto LABEL_11;
        case 2u:
          v20 = dwVal;
          v7 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Longkui");
          goto LABEL_11;
        case 3u:
          v20 = dwVal;
          v7 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Zixuan");
          goto LABEL_11;
        case 4u:
          v20 = dwVal;
          v7 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Changqing");
LABEL_11:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%s%d", v7, v20);
          break;
        default:
          break;
      }
    }
    else
    {
      inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(dwVal);
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(inited->dwID);
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, v6 + 600);
    }
    SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v8 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(dwVal, 0);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v8);
    SendMessageA(v3, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v9 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(dwVal, 1);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v9);
    SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    RoleGPBak = ((CCBRoleState *)this->m_pRoleState)->GetRoleGPBak(dwVal, 0);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], RoleGPBak);
    SendMessageA(v22, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v11 = ((CCBRoleState *)this->m_pRoleState)->GetRoleGPBak(dwVal, 1);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v11);
    SendMessageA(v23, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    Role = ((CCBRoleState *)this->m_pRoleState)->GetRole(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], Role);
    SendMessageA(v24, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v13 = ((CCBRoleState *)this->m_pRoleState)->GetRole(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v13);
    SendMessageA(v25, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v14 = ((CCBRoleState *)this->m_pRoleState)->InitUI(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v14->nLevel);
    SendMessageA(v26, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v15 = ((CCBRoleState *)this->m_pRoleState)->InitUI(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v15->nSpeed);
    SendMessageA(v27, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v16 = ((CCBRoleState *)this->m_pRoleState)->InitUI(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v16->nAttack);
    SendMessageA(v28, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v17 = ((CCBRoleState *)this->m_pRoleState)->InitUI(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v17->nDefence);
    SendMessageA(v29, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v18 = ((CCBRoleState *)this->m_pRoleState)->InitUI(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v18->nLuck);
    SendMessageA(v30, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    v19 = ((CCBRoleState *)this->m_pRoleState)->InitUI(dwVal);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], *(_DWORD *)&v19->bLostMoneyGetLife);
    SendMessageA(v31, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  }
  else
  {
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &unk_5D89A4);
    SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    EnableWindow(v4, 0);
  }
}

// 0x004FFA90
int CCBStageRole::TaskExecAttack(int nVal)
{
  int v3; // eax
  int *v4; // ebp
  char *v5; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  CCBStageRole *v10; // ecx
  int v11; // ebx

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = (int *)((char *)&this->m_Task[22].dwID + v3);
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *(_DWORD *)(&this->m_Task[22].bValid + v3)))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
    goto LABEL_6;
  if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->ForceDelTaskByPFN() )
  {
    v7 = *(&this->m_sRoleArray.m_nSize + v4[2]);
    *(_DWORD *)(v7 + 6632) = *(_DWORD *)(v7 + 6636);
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->GetProperCurAction(0 /* TODO: (int)CCBStage::AnimCallback_Attack */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), 0, v4, 1);
    v5[41] = 1;
    ((CCBCamControl *)*(CCBCamControl **)&this->m_sRoleData[40])->KeepCurCam(v4[1]);
    *((_DWORD *)v5 + 14) = v8;
    v5[62] = 0;
    v5[61] = 0;
    v5[60] = 0;
LABEL_6:
    v9 = *((_DWORD *)v5 + 14);
    v10 = *(CCBStageRole **)&this->m_sRoleData[40];
    v11 = (int)&v10->m_Task[19].cmd.bDestRole[60 * v9 + 3];
    if ( !v5[60]
      && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *((float *)&v10->m_Task[19].eMode + 15 * v9) )
    {
      ((CCBStageRole *)v10)->_CCBStageRole(v9, 1, v4);
      v5[60] = 1;
    }
    if ( !v5[61] && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *(float *)(v11 + 52) )
    {
      ((CCBStageRole *)*(CCBStageRole **)&this->m_sRoleData[40])->_CCBStageRole(*((_DWORD *)v5 + 14), 2, v4);
      v5[61] = 1;
    }
    if ( !v5[62]
      && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *(float *)(*(_DWORD *)&this->m_sRoleData[40]
                                                                                   + 60 * *((_DWORD *)v5 + 14)
                                                                                   + 2472) )
    {
      if ( v4[1] != 4101 && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v4[2]) )
        ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[22].dwID + 658 * *(_DWORD *)&this->m_sRoleData[124]);
      v5[62] = 1;
    }
    if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->ForceDelTaskByPFN() && v5[62] )
    {
      if ( v4[1] == 4101 && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v4[2]) )
        ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[22].dwID + 658 * *(_DWORD *)&this->m_sRoleData[124]);
      *((_DWORD *)v5 + 4) = 4;
    }
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x004FFCB0
int CCBStageRole::TaskExecCommand(int nVal)
{
  int v3; // eax
  int *v4; // ebx
  char *v5; // edi
  int v6; // eax
  int v7; // ecx
  double v8; // st7
  int v9; // eax
  int pnVal[3]; // [esp+0x18] [ebp-0xC] BYREF

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = (int *)(&this->m_Task[22].bValid + v3);
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
    goto LABEL_15;
  if ( v5[41] || !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
    goto LABEL_13;
  ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->GetCurrentState();
  v6 = *v4;
  if ( *v4 >= 0 && v6 < 5 )
  {
    switch ( v6 )
    {
      case 1:
        goto LABEL_11;
      case 2:
        ((CCBStageRole *)this->m_sRoleArray.m_nCapacity)->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcMagic */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), (int *)(this->m_sRoleArray.m_nCapacity + 6596), 0, 1);
        goto LABEL_12;
      case 3:
LABEL_11:
        ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v6))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcUseRecoverItem */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), (int *)(*(&this->m_sRoleArray.m_nSize + v6) + 6596), 0, 1);
        goto LABEL_12;
    }
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v6))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcTurnToRole */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), (int *)(*(&this->m_sRoleArray.m_nSize + v6) + 6596), 0, 1);
  }
LABEL_12:
  v7 = *v4;
  v8 = *(float *)(*(&this->m_sRoleArray.m_nSize + *v4) + 6636);
  pnVal[1] = 0;
  v9 = *(_DWORD *)&this->m_sRoleData[124];
  *(float *)pnVal = v8;
  pnVal[2] = 0;
  ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v7))->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * v9), pnVal, 0, 1);
  v5[41] = 1;
LABEL_13:
  if ( v5[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
LABEL_15:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FFED0
int CCBStageRole::TaskResetToIdle(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // edi
  int v6; // eax

  v3 = 329 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = 80 * *(_DWORD *)&this->m_sRoleData[128];
  v5 = &this->m_sRoleData[8 * v3 + 148 + v4];
  if ( !this->m_sRoleData[8 * v3 + 189 + v4]
    && ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize
                                       + *(_DWORD *)&this->m_sRoleData[8 * v3 + 196 + v4]))->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v5 + 12)))->GetCurrentState();
    v6 = *(&this->m_sRoleArray.m_nSize + *((_DWORD *)v5 + 12));
    *(_DWORD *)(v6 + 6632) = *(_DWORD *)(v6 + 6636);
    v5[41] = 1;
  }
  if ( v5[43] == 1
    || ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v5 + 12)))->ForceDelTaskByPFN() )
  {
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x004FFF60
int CCBStageRole::TaskExecMagicEffect(int nVal)
{
  int v3; // eax
  int v4; // ecx
  int *v5; // ebp
  char *v6; // esi
  int v7; // eax
  int v8; // edx
  CCBStageRole *v9; // ecx
  int v10; // eax
  CCBStageRole *Instance; // eax
  char v12; // al
  CCBStageRole *v13; // eax
  CCBStageRole *v14; // eax
  int v16; // [esp+0x10] [ebp-0x4]

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = v3 + 80 * *(_DWORD *)&this->m_sRoleData[128];
  v5 = (int *)((char *)&this->m_Task[22].dwID + v3);
  v6 = &this->m_sRoleData[v4 + 148];
  if ( !this->m_sRoleData[v4 + 189] )
  {
    if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize
                                          + *(_DWORD *)&this->m_sRoleData[v4 + 196]))->ForceDelTaskByPFN() )
      return 0;
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v6 + 12)))->GetCurrentState();
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v6 + 12)))->GetProperCurAction(0 /* TODO: (int)CCBStage::AnimCallback_CastMagic */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), 0, 0, 1);
    v6[41] = 1;
    ((CCBCamControl *)*(CCBCamControl **)&this->m_sRoleData[40])->KeepCurCam(v5[1]);
    *((_DWORD *)v6 + 14) = v7;
    v6[62] = 0;
    v6[61] = 0;
    v6[60] = 0;
    *((_DWORD *)v6 + 16) = 0;
  }
  v8 = *((_DWORD *)v6 + 14);
  v9 = *(CCBStageRole **)&this->m_sRoleData[40];
  v16 = (int)&v9->m_Task[19].cmd.bDestRole[60 * v8 + 3];
  if ( !v6[60]
    && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v6 + 6) >= *((float *)&v9->m_Task[19].eMode + 15 * v8) )
  {
    ((CCBStageRole *)v9)->_CCBStageRole(v8, 1, v5);
    *((_DWORD *)v6 + 16) = v10;
    ((CCBSystem *)this->m_pStage)->ProcAI(0.0);
    *(_BYTE *)(*(&this->m_sRoleArray.m_nSize + *((_DWORD *)v6 + 12)) + 267) = 1;
    Instance = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)Instance)->PauseSound();
    v6[60] = 1;
  }
  if ( !v6[61] && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v6 + 6) >= *(float *)(v16 + 52) )
  {
    ((CCBStageRole *)*(CCBStageRole **)&this->m_sRoleData[40])->_CCBStageRole(*((_DWORD *)v6 + 14), 2, v5);
    v6[61] = 1;
  }
  if ( v6[60] )
  {
    ((CEffMgr *)this->m_pStage->m_pRole[6])->Render(*((_DWORD *)v6 + 16));
    if ( !v12 )
    {
      ((CCBSystem *)this->m_pStage)->ProcAI(1.0);
      v13 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v13)->ResumeSound();
      *(_BYTE *)(*(&this->m_sRoleArray.m_nSize + *((_DWORD *)v6 + 12)) + 267) = 0;
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v5[2]) )
        ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[22].dwID + 658 * *(_DWORD *)&this->m_sRoleData[124]);
      v6[62] = 1;
      *((_DWORD *)v6 + 4) = 4;
    }
  }
  if ( v6[43] == 1 )
  {
    ((CCBSystem *)this->m_pStage)->ProcAI(1.0);
    v14 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v14)->ResumeSound();
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x00500220
int CCBStageRole::TaskExecSkill(int nVal)
{
  int v3; // eax
  int *v4; // ebp
  char *v5; // edi
  int v7; // eax
  tagRoleState *inited; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  CCBStageRole *v13; // ecx
  int v14; // ebx
  int pnVal[3]; // [esp+0x10] [ebp-0xC] BYREF

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = (int *)((char *)&this->m_Task[22].dwID + v3);
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *(_DWORD *)(&this->m_Task[22].bValid + v3)))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
    goto LABEL_15;
  if ( ((CCBRoleState *)this->m_pRoleState)->CheckMagicCost(v4)
    && ((CCBRoleState *)this->m_pRoleState)->CheckEventCondition((int)v4) )
  {
    if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->ForceDelTaskByPFN() )
      return 0;
    v7 = v4[2];
    memset(pnVal, 0, sizeof(pnVal));
    if ( v7 >= 5 && v7 < 11 )
    {
      inited = ((CCBRoleState *)this->m_pStage->m_pCamControl)->InitUI(v7);
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(inited->dwID);
      if ( v9 )
      {
        v10 = v4[1];
        if ( v10 == *(_DWORD *)(v9 + 764) )
        {
          pnVal[0] = 1065353216;
        }
        else if ( v10 == *(_DWORD *)(v9 + 768) )
        {
          pnVal[0] = 0x40000000;
        }
      }
    }
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->GetCurrentState();
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->GetProperCurAction(0 /* TODO: (int)CCBStage::UpdateActionTimers */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), pnVal, 0, 1);
    v5[41] = 1;
    ((CCBCamControl *)*(CCBCamControl **)&this->m_sRoleData[40])->KeepCurCam(v4[1]);
    *((_DWORD *)v5 + 14) = v11;
    v5[62] = 0;
    v5[61] = 0;
    v5[60] = 0;
LABEL_15:
    v12 = *((_DWORD *)v5 + 14);
    v13 = *(CCBStageRole **)&this->m_sRoleData[40];
    v14 = (int)&v13->m_Task[19].cmd.bDestRole[60 * v12 + 3];
    if ( !v5[60]
      && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *((float *)&v13->m_Task[19].eMode + 15 * v12) )
    {
      ((CCBStageRole *)v13)->_CCBStageRole(v12, 1, v4);
      v5[60] = 1;
    }
    if ( !v5[61] && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *(float *)(v14 + 52) )
    {
      ((CCBStageRole *)*(CCBStageRole **)&this->m_sRoleData[40])->_CCBStageRole(*((_DWORD *)v5 + 14), 2, v4);
      v5[61] = 1;
    }
    if ( !v5[62]
      && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *(float *)(*(_DWORD *)&this->m_sRoleData[40]
                                                                                   + 60 * *((_DWORD *)v5 + 14)
                                                                                   + 2472) )
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v4[2]) )
        ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[22].dwID + 658 * *(_DWORD *)&this->m_sRoleData[124]);
      v5[62] = 1;
    }
    if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->ForceDelTaskByPFN() && v5[62] )
      *((_DWORD *)v5 + 4) = 4;
    if ( v5[43] == 1 )
    {
      v5[41] = 1;
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  v5[41] = 1;
  *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x005004B0
int CCBStageRole::TaskWaitIdle(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  char *v5; // ebp

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = &this->m_Task[22].bValid + v3;
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
    goto LABEL_7;
  if ( !v5[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->GetCurrentState();
    v5[41] = 1;
  }
  if ( v5[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00500550
int CCBStageRole::TaskExecItem(int nVal)
{
  int v3; // eax
  int *v4; // ebp
  char *v5; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  CCBStageRole *v10; // ecx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  char v14; // al

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = (int *)((char *)&this->m_Task[22].dwID + v3);
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *(_DWORD *)(&this->m_Task[22].bValid + v3)))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
  {
LABEL_9:
    v9 = *((_DWORD *)v5 + 14);
    v10 = *(CCBStageRole **)&this->m_sRoleData[40];
    v11 = (int)&v10->m_Task[19].cmd.bDestRole[60 * v9 + 3];
    if ( !v5[60]
      && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *((float *)&v10->m_Task[19].eMode + 15 * v9) )
    {
      ((CCBStageRole *)v10)->_CCBStageRole(v9, 1, v4);
      *((_DWORD *)v5 + 16) = v12;
      v5[60] = 1;
    }
    if ( !v5[61] && *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) >= *(float *)(v11 + 52) )
    {
      ((CCBStageRole *)*(CCBStageRole **)&this->m_sRoleData[40])->_CCBStageRole(*((_DWORD *)v5 + 14), 2, v4);
      *((_DWORD *)v5 + 17) = v13;
      v5[61] = 1;
    }
    if ( v5[62]
      || *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) < *(float *)(*(_DWORD *)&this->m_sRoleData[40]
                                                                                  + 60 * *((_DWORD *)v5 + 14)
                                                                                  + 2472)
      || !v5[60] )
    {
      goto LABEL_25;
    }
    if ( ((CCBSystem *)this->m_pStage->m_pCamControl)->IsMagicSlotMsg((int)v4) )
    {
      ((CEffMgr *)this->m_pStage->m_pRole[5])->Render(*((_DWORD *)v5 + 16));
      if ( v14 )
        goto LABEL_25;
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v4[2]) )
        goto LABEL_23;
    }
    else if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v4[2]) )
    {
LABEL_23:
      ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[22].dwID + 658 * *(_DWORD *)&this->m_sRoleData[124]);
    }
    v5[62] = 1;
LABEL_25:
    if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->ForceDelTaskByPFN() && v5[62] )
      *((_DWORD *)v5 + 4) = 4;
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->ForceDelTaskByPFN() )
  {
    v7 = *(&this->m_sRoleArray.m_nSize + v4[2]);
    *(_DWORD *)(v7 + 6632) = *(_DWORD *)(v7 + 6636);
    if ( ((PAL_GDB *)this->m_pRoleState)->GetSkillLevel(v4[1]) )
      ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->GetProperCurAction(0 /* TODO: (int)CCBStage::AnimCallback_UseItem */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), 0, 0, 1);
    else
      ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v4[2]))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::OnMagicHit */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), 0, v4, 1);
    v5[41] = 1;
    ((CCBCamControl *)*(CCBCamControl **)&this->m_sRoleData[40])->KeepCurCam(v4[1]);
    *((_DWORD *)v5 + 14) = v8;
    v5[62] = 0;
    v5[61] = 0;
    v5[60] = 0;
    *((_DWORD *)v5 + 17) = 0;
    *((_DWORD *)v5 + 16) = 0;
    goto LABEL_9;
  }
  return 0;
}

// 0x005007A0
int CCBStageRole::TaskForceEnd(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  char *v5; // ebp

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = &this->m_Task[22].bValid + v3;
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
    goto LABEL_6;
  if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
  {
    v5[41] = 1;
LABEL_6:
    if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
      *((_DWORD *)v5 + 4) = 4;
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00500C20
int CCBStageRole::TaskExecAction(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  char *v5; // ebx

  if ( (g_nCBRoleAnimData[23] & 1) == 0 )
  {
    g_nCBRoleAnimData[20] = 0;
    LOBYTE(g_nCBRoleAnimData[23]) |= 1u;
    g_nCBRoleAnimData[21] = 0;
    g_nCBRoleAnimData[22] = 0;
    atexit(nullsub_22);
  }
  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = &this->m_Task[22].bValid + v3;
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
    goto LABEL_9;
  if ( !v5[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->GetProperCurAction(0 /* TODO: (int)CCBStage::AnimCallback_WaitCmd */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), &g_nCBRoleAnimData[20], 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
LABEL_9:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00500D50
int CCBStageRole::TaskResolveAction(int nState)
{
  int v3; // eax
  int *v4; // esi
  int v5; // ecx
  int v6; // eax
  char *v7; // edi
  CCBStageRole *v8; // ecx
  CCBStage *m_pStage; // edx
  int RoleIndex; // edi
  char *v11; // eax
  int v13; // esi
  int v14; // eax
  int *p_m_nSize; // edi
  CCBRoleState *m_pRoleState; // ecx
  int v17; // eax
  CCBStage *v18; // edx
  _BYTE *v19; // eax
  bool v20; // cc
  CCBControl *m_pEditor; // ecx
  int Control; // eax
  int v23; // esi
  int v24; // [esp-0x4] [ebp-0x11C]
  _DWORD v25[22]; // [esp+0xC] [ebp-0x10C] BYREF
  _BYTE v26[88]; // [esp+0x64] [ebp-B4h] BYREF
  _DWORD pData[11]; // [esp+BCh] [ebp-0x5C] BYREF
  int p_DWORD[3]; // [esp+E8h] [ebp-0x30] BYREF
  int RoleHP; // [esp+F4h] [ebp-0x24]
  int *v30; // [esp+F8h] [ebp-0x20]
  int idx; // [esp+FCh] [ebp-0x1C]
  int v32; // [esp+0x100] [ebp-0x18]
  char *v33; // [esp+0x104] [ebp-0x14]
  int nIndex; // [esp+0x108] [ebp-0x10]
  int *v35; // [esp+0x10C] [ebp-0xC]
  float v36; // [esp+0x110] [ebp-0x8]
  bool v37; // [esp+0x117] [ebp-0x1]

  if ( (g_nCBRoleAnimData[19] & 1) == 0 )
  {
    g_nCBRoleAnimData[16] = 0;
    LOBYTE(g_nCBRoleAnimData[19]) |= 1u;
    g_nCBRoleAnimData[17] = 0;
    g_nCBRoleAnimData[18] = 0;
    atexit(nullsub_23);
  }
  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = (int *)(&this->m_Task[22].bValid + v3);
  v5 = v3 + 80 * *(_DWORD *)&this->m_sRoleData[128];
  v24 = *(_DWORD *)((char *)&this->m_Task[22].fTemp + v3);
  v6 = *v4;
  v30 = v4;
  v7 = &this->m_sRoleData[v5 + 148];
  v8 = (CCBStageRole *)*(&this->m_sRoleArray.m_nSize + v6);
  v33 = v7;
  if ( !((CCBStageRole *)v8)->IsReady(v24) )
  {
LABEL_42:
    *((_DWORD *)v7 + 4) = 4;
    return 0;
  }
  if ( v7[41] )
  {
LABEL_39:
    if ( v7[43] != 1 && !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
      return 0;
    *((_DWORD *)v7 + 9) = 1;
    goto LABEL_42;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->CheckMP(2) != -1 )
  {
    ((CCBRoleState *)this->m_pRoleState)->CheckMP(2);
    v36 = COERCE_FLOAT(((CCBRoleState *)this->m_pRoleState)->ApplyDamage(3, *v4));
    if ( SLODWORD(v36) > 0 )
    {
      __asm
      {
        fild    [ebp+var_8]
        fmul    dword ptr [flt_56B5E8]
        fstp    [ebp+var_8]
        fld     [ebp+var_8]
        fistp   [ebp+var_C]
      }
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      v37 = (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)v35;
    }
    else
    {
      v37 = 0;
    }
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[1][0] )
      v37 = 1;
    m_pStage = this->m_pStage;
    if ( *(_BYTE *)(this->m_pStage->m_nSelectedRole + 80) )
      v37 = 0;
    memset(pData, 0, sizeof(pData));
    LOBYTE(pData[10]) = 1;
    pData[0] = 267;
    pData[1] = ((CCBSystem *)m_pStage)->ProcProtect();
    pData[2] = -1;
    pData[3] = -1;
    if ( !v37 )
      pData[2] = *v4;
    RoleIndex = ((CCBStage *)this)->GetRoleIndex(26, pData, 1);
    if ( RoleIndex != -1 )
    {
      p_DWORD[1] = 0;
      p_DWORD[2] = 0;
      p_DWORD[0] = v37;
      ((CCBStage *)this)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcessRoleEffect */, 0, 0, 0, p_DWORD, 0, 1077936128);
      ((CCBStage *)this)->GetStageRoleByIdx(RoleIndex);
    }
    if ( !v37 )
    {
      v11 = v33;
      v33[41] = 1;
      *((_DWORD *)v11 + 4) = 4;
      *((_DWORD *)v11 + 9) = 0;
      return 0;
    }
    if ( ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
    {
      ((CCBAttackSequen *)this->m_pStage->m_pCam)->SetPause();
      g_nCBRoleAnimData[16] = -1001914368;
      g_nCBRoleAnimData[17] = 0;
      g_nCBRoleAnimData[18] = -1001914368;
      RoleHP = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(*v4);
      v13 = 0;
      v14 = 0;
      p_m_nSize = &this->m_sRoleArray.m_nSize;
      nIndex = 0;
      v36 = 0.0;
      v35 = &this->m_sRoleArray.m_nSize;
      do
      {
        m_pRoleState = this->m_pRoleState;
        if ( m_pRoleState->m_Role[0].bMagicMastered[5][v14 + 4] )
        {
          if ( ((CCBRoleState *)m_pRoleState)->IsRoleAlive(v13) )
          {
            v17 = ((CCBRoleState *)this->m_pRoleState)->GetRoleHP(v13);
            if ( v17 == RoleHP )
            {
              *(_BYTE *)(*p_m_nSize + 280) = 0;
              *(_BYTE *)(*p_m_nSize + 274) = 0;
              ((CCBStageRole *)*p_m_nSize)->ClearAniMsg(0, 1.0);
              if ( v13 != *v30 )
              {
                idx = 0;
                v32 = 0;
                do
                {
                  v18 = this->m_pStage;
                  v19 = &this->m_pStage->m_nStageStatus + v32;
                  qmemcpy(v26, v19, sizeof(v26));
                  if ( v26[36] )
                  {
                    qmemcpy(v25, v19, sizeof(v25));
                    if ( v25[12] == nIndex )
                      ((CCBSystem *)v18)->ClearEffect(idx);
                  }
                  v20 = v32 + 88 < 90112;
                  ++idx;
                  v32 += 88;
                }
                while ( v20 );
                m_pEditor = (CCBControl *)this->m_pStage->m_pEditor;
                if ( m_pEditor->m_bActive )
                {
                  Control = ((CCBControl *)m_pEditor)->GetControl();
                  v23 = nIndex;
                  if ( Control == nIndex )
                    ((CCBControl *)this->m_pStage->m_pEditor)->GetState();
                }
                else
                {
                  v23 = nIndex;
                }
                ((CCBStage *)this)->IsTaskFinished(v23);
                p_m_nSize = v35;
                ((CCBStageRole *)*v35)->GetCurrentTaskIndex();
                ((CCBStageRole *)*p_m_nSize)->DelAllTask(*((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), 1);
                ((CCBSystem *)this->m_pStage->m_pCam)->SetCmdParam(v23, 1);
                ((CCBSystem *)this->m_pStage->m_pCam)->GetCmdPtr(v23);
              }
              ((CCBStageRole *)*p_m_nSize)->ProcTransportRun((unsigned int)CCBStageRole::ProcTurnToRole, 0, 0, 0, &g_nCBRoleAnimData[16], 0, 2);
              v13 = nIndex;
            }
          }
        }
        ++v13;
        v14 = LODWORD(v36) + 892;
        ++p_m_nSize;
        v20 = LODWORD(v36) + 892 < 9812;
        nIndex = v13;
        v35 = p_m_nSize;
        LODWORD(v36) += 892;
      }
      while ( v20 );
      v4 = v30;
      v33[41] = 1;
    }
    v7 = v33;
    goto LABEL_39;
  }
  return 0;
}

// 0x005011B0
int CCBStageRole::TaskMoveToStart(int nVal)
{
  int v3; // eax
  int *v4; // edi
  char *v5; // ebp

  if ( (g_nCBRoleAnimData[15] & 1) == 0 )
  {
    g_nCBRoleAnimData[12] = 0;
    LOBYTE(g_nCBRoleAnimData[15]) |= 1u;
    g_nCBRoleAnimData[13] = 0;
    g_nCBRoleAnimData[14] = 0;
    atexit(nullsub_24);
  }
  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = (int *)(&this->m_Task[22].bValid + v3);
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
    goto LABEL_10;
  if ( !v5[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
  {
    g_nCBRoleAnimData[12] = 1145569280;
    g_nCBRoleAnimData[13] = 0;
    g_nCBRoleAnimData[14] = 1145569280;
    *(_BYTE *)(*(&this->m_sRoleArray.m_nSize + *v4) + 280) = 0;
    *(_BYTE *)(*(&this->m_sRoleArray.m_nSize + *v4) + 274) = 0;
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ClearAniMsg(0, 1.0);
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->GetProperCurAction(0 /* TODO: (int)CCBStage::AnimCallback_MoveTo */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), &g_nCBRoleAnimData[12], 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(*v4)[1].dwMagicID[2][5]) == 1 )
  {
    *((_DWORD *)v5 + 9) = 1;
LABEL_10:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00501330
int CCBStageRole::TaskBlendToReady(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  double v6; // st7
  double v7; // st7
  float fVal; // [esp+0x0] [ebp-0xC]

  v3 = 329 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = 80 * *(_DWORD *)&this->m_sRoleData[128];
  v5 = &this->m_sRoleData[8 * v3 + 148 + v4];
  if ( !this->m_sRoleData[8 * v3 + 189 + v4] )
  {
    v6 = ((CCBStageRole *)*(&this->m_sRoleArray.m_nSize
                                                       + *(_DWORD *)&this->m_sRoleData[8 * v3 + 196 + v4]))->PushBackAllTask();
    *((float *)v5 + 16) = v6;
    v5[41] = 1;
    if ( v6 < 0.44 )
      goto LABEL_7;
  }
  v7 = (*(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6)) / *((float *)v5 + 8);
  if ( v7 > 1.0 )
    v7 = 1.0;
  fVal = (*((float *)v5 + 16) - 0.44) * (1.0 - v7) + 0.44;
  ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v5 + 12)))->ClearAniMsg(1, fVal);
  if ( *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) > *((float *)v5 + 8) )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v5 + 12)))->ClearAniMsg(1, 0.44);
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00501410
int CCBStageRole::TaskBlendToEnd(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  double v6; // st7
  double v7; // st7
  float fVal; // [esp+0x0] [ebp-0xC]

  v3 = 329 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = 80 * *(_DWORD *)&this->m_sRoleData[128];
  v5 = &this->m_sRoleData[8 * v3 + 148 + v4];
  if ( !this->m_sRoleData[8 * v3 + 189 + v4] )
  {
    v6 = ((CCBStageRole *)*(&this->m_sRoleArray.m_nSize
                                                       + *(_DWORD *)&this->m_sRoleData[8 * v3 + 196 + v4]))->PushBackAllTask();
    *((float *)v5 + 16) = v6;
    v5[41] = 1;
    if ( v6 >= 0.99000001 )
      goto LABEL_7;
  }
  v7 = (*(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6)) / *((float *)v5 + 8);
  if ( v7 > 1.0 )
    v7 = 1.0;
  fVal = (1.0 - *((float *)v5 + 16)) * v7 + *((float *)v5 + 16);
  ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v5 + 12)))->ClearAniMsg(1, fVal);
  if ( *(float *)&this->m_pStage->m_WPXVariance - *((float *)v5 + 6) > *((float *)v5 + 8) )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *((_DWORD *)v5 + 12)))->ClearAniMsg(0, 1.0);
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x005014E0
int CCBStageRole::TaskEnterGuard(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  char *v5; // ebp

  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = &this->m_Task[22].bValid + v3;
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
    goto LABEL_7;
  if ( !v5[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::CheckPushState */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), 0, 0, 1);
    v5[41] = 1;
  }
  ((CCBStage *)this)->ForceDelTask(12);
  ((CCBStage *)this)->ForceDelTask(15);
  if ( v5[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x005015C0
int CCBStageRole::SetupCombatAction(int nVal)
{
  int v3; // eax
  int v4; // ecx
  _DWORD *v5; // esi
  char *m_pDataStart; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  _DWORD *v11; // eax
  int *v12; // eax
  int *v13; // eax
  int v14; // eax
  int v15; // ecx
  float v16; // edx
  int v17; // eax
  int v18; // edx
  int v19; // eax
  void *v20; // ecx
  unsigned int ( *v21)(CCBStageRole *, int); // ecx
  _DWORD *v22; // eax
  _DWORD *v23; // eax
  int v24; // eax
  double v25; // st7
  double v26; // st7
  CCBStageRole **v28; // edi
  double v29; // st7
  unsigned int ( *v30)(CCBStageRole *, int); // [esp-0x20] [ebp-0x70]
  const void *v31; // [esp-0x8] [ebp-0x58]
  char *v32; // [esp+0x10] [ebp-0x40]
  struct gbVec3D v33; // [esp+0x14] [ebp-0x3C] BYREF
  int pnVal; // [esp+0x20] [ebp-0x30] BYREF
  float v35; // [esp+0x24] [ebp-0x2C]
  float z; // [esp+0x28] [ebp-0x28]
  float v37; // [esp+0x2C] [ebp-0x24]
  float v38; // [esp+0x30] [ebp-0x20]
  float v39; // [esp+0x34] [ebp-0x1C]
  struct gbVec3D v40; // [esp+0x38] [ebp-0x18] BYREF
  gbVec3D v41; // [esp+0x44] [ebp-0xC] BYREF

  if ( (g_nCBRoleAnimData[11] & 1) == 0 )
  {
    g_nCBRoleAnimData[8] = 0;
    LOBYTE(g_nCBRoleAnimData[11]) |= 1u;
    g_nCBRoleAnimData[9] = 0;
    g_nCBRoleAnimData[10] = 0;
    atexit(nullsub_26);
  }
  if ( (g_nCBRoleAnimData[11] & 2) == 0 )
  {
    g_nCBRoleAnimData[4] = 0;
    LOBYTE(g_nCBRoleAnimData[11]) |= 2u;
    g_nCBRoleAnimData[5] = 0;
    g_nCBRoleAnimData[6] = 0;
    atexit(nullsub_25);
  }
  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = v3 + 80 * *(_DWORD *)&this->m_sRoleData[128];
  v5 = (unsigned int *)((char *)&this->m_Task[22].dwID + v3);
  v32 = &this->m_sRoleData[v4 + 148];
  if ( !this->m_sRoleData[v4 + 189] )
  {
    if ( *(_DWORD *)(&this->m_Task[22].bExecuted + v3 + 2) == -1 )
    {
      m_pDataStart = this->m_sRoleArray.m_pDataStart;
      v7 = *(_DWORD *)&m_pDataStart[12 * v5[1] + 8];
      v8 = (int)&m_pDataStart[12 * v5[1] + 8];
      g_nCBRoleAnimData[4] = v7;
      g_nCBRoleAnimData[5] = *(_DWORD *)(v8 + 4);
      g_nCBRoleAnimData[6] = *(_DWORD *)(v8 + 8);
      v9 = v5[2];
      if ( v9 == 1 )
        goto LABEL_12;
      if ( v5[2] == 2 )
      {
        ((CCBStageRole *)this->m_sRoleArray.m_nCapacity)->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcMagic */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
LABEL_14:
        v11 = (_DWORD *)*(&this->m_sRoleArray.m_nSize + v5[2]);
        v11[1649] = g_nCBRoleAnimData[4];
        v11 += 1649;
        v11[1] = g_nCBRoleAnimData[5];
        v11[2] = g_nCBRoleAnimData[6];
        v32[41] = 1;
        goto LABEL_36;
      }
      if ( v5[2] == 3 )
LABEL_12:
        v10 = CCBStageRole::ProcUseRecoverItem;
      else
        v10 = CCBStageRole::ProcTurnToRole;
      ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v9))->GetProperCurAction((int)v10, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
      goto LABEL_14;
    }
    v12 = (int *)(*(&this->m_sRoleArray.m_nSize + *(_DWORD *)(&this->m_Task[22].bValid + v3)) + 6596);
    g_nCBRoleAnimData[8] = *v12;
    g_nCBRoleAnimData[9] = v12[1];
    g_nCBRoleAnimData[10] = v12[2];
    v13 = (int *)(*(&this->m_sRoleArray.m_nSize + v5[3]) + 6596);
    g_nCBRoleAnimData[4] = *v13;
    g_nCBRoleAnimData[5] = v13[1];
    g_nCBRoleAnimData[6] = v13[2];
    v14 = v5[2];
    if ( !v14 && v5[3] == 4 || v14 == 4 && !v5[3] )
    {
      memset(&v33, 0, sizeof(v33));
      *(float *)&pnVal = *(float *)&g_nCBRoleAnimData[4] + *(float *)&g_nCBRoleAnimData[8];
      v35 = *(float *)&g_nCBRoleAnimData[9] + *(float *)&g_nCBRoleAnimData[5];
      z = *(float *)&g_nCBRoleAnimData[10] + *(float *)&g_nCBRoleAnimData[6];
      v37 = *(float *)&pnVal * 0.5;
      v38 = v35 * 0.5;
      v39 = z * 0.5;
      *(float *)&pnVal = *(float *)&g_nCBRoleAnimData[8] - *(float *)&g_nCBRoleAnimData[4];
      v15 = pnVal;
      *(float *)&pnVal = 0.0;
      LODWORD(v40.x) = v15;
      v35 = *(float *)&g_nCBRoleAnimData[9] - *(float *)&g_nCBRoleAnimData[5];
      v16 = v35;
      v35 = 1.0;
      v40.y = v16;
      z = *(float *)&g_nCBRoleAnimData[10] - *(float *)&g_nCBRoleAnimData[6];
      v41.x = 0.0;
      v41.y = 1.0;
      v40.z = z;
      z = 0.0;
      v41.z = 0.0;
      ((gbVec3D *)&v41)->CrossProduct(&v40, &v33);
      ((gbVec3D *)&v33)->Normalize();
      v33.x = v33.x * 30.0;
      v33.y = v33.y * 30.0;
      v33.z = v33.z * 30.0;
      z = v33.z;
      *(float *)&pnVal = v33.x + v37;
      v35 = v33.y + v38;
      v17 = v5[2];
      z = v33.z + v39;
      ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v17))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcTurnToRole */, 0, 0, 0, 0x7FFFFFFF, &pnVal, v5, 1);
      ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v5[2]))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcTurnToRole */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
      v35 = v33.y * -1.0;
      z = v33.z * -1.0;
      *(float *)&pnVal = v37 + v33.x * -1.0;
      v18 = v5[3];
      v35 = v35 + v38;
      z = z + v39;
      ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v18))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcTurnToRole */, 0, 0, 0, 0x7FFFFFFF, &pnVal, v5, 1);
      v31 = v5;
      v30 = CCBStageRole::ProcTurnToRole;
      v19 = v5[3];
      goto LABEL_34;
    }
    switch ( v14 )
    {
      case 1:
        goto LABEL_25;
      case 2:
        ((CCBStageRole *)this->m_sRoleArray.m_nCapacity)->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcMagic */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
        goto LABEL_27;
      case 3:
LABEL_25:
        v20 = CCBStageRole::ProcUseRecoverItem;
        break;
      default:
        v20 = CCBStageRole::ProcTurnToRole;
        break;
    }
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v14))->GetProperCurAction((int)v20, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
LABEL_27:
    v19 = v5[3];
    if ( v19 == 1 )
      goto LABEL_32;
    if ( v5[3] == 2 )
    {
      ((CCBStageRole *)this->m_sRoleArray.m_nCapacity)->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcMagic */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[8], v5, 1);
LABEL_35:
      v22 = (_DWORD *)*(&this->m_sRoleArray.m_nSize + v5[2]);
      v22[1649] = g_nCBRoleAnimData[4];
      v22 += 1649;
      v22[1] = g_nCBRoleAnimData[5];
      v22[2] = g_nCBRoleAnimData[6];
      v23 = (_DWORD *)*(&this->m_sRoleArray.m_nSize + v5[3]);
      v23[1649] = g_nCBRoleAnimData[8];
      v23 += 1649;
      v23[1] = g_nCBRoleAnimData[9];
      v23[2] = g_nCBRoleAnimData[10];
      v32[41] = 1;
      goto LABEL_36;
    }
    if ( v5[3] == 3 )
LABEL_32:
      v21 = (unsigned int ( *)(CCBStageRole *, int))CCBStageRole::ProcUseRecoverItem;
    else
      v21 = CCBStageRole::ProcTurnToRole;
    v31 = v5;
    v30 = v21;
LABEL_34:
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v19))->GetProperCurAction((int)v30, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[8], v31, 1);
    goto LABEL_35;
  }
LABEL_36:
  if ( v5[3] == -1 )
  {
    v28 = (CCBStageRole **)(&this->m_sRoleArray.m_nSize + v5[2]);
    v29 = *(float *)&(*v28)->m_Task[63].cmd.dwCmdKind;
    v41.y = 0.0;
    v41.x = v29;
    v41.z = 0.0;
    ((CCBStageRole *)*v28)->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, 0x7FFFFFFF, (int *)&v41, v5, 1);
  }
  else
  {
    v24 = v5[2];
    v25 = *(float *)(*(&this->m_sRoleArray.m_nSize + v24) + 6636);
    v41.y = 0.0;
    v41.z = 0.0;
    v41.x = v25;
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v24))->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, 0x7FFFFFFF, (int *)&v41, v5, 1);
    v26 = *(float *)(*(&this->m_sRoleArray.m_nSize + v5[2]) + 6636);
    v41.y = 0.0;
    v41.z = 0.0;
    v41.x = v26;
    ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + v5[3]))->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, 0x7FFFFFFF, (int *)&v41, v5, 1);
  }
  *((_DWORD *)v32 + 4) = 4;
  return 0;
}

// 0x00501CF0
int CCBStageRole::TaskReturnToIdle(int nVal)
{
  int v3; // eax
  int *v4; // edi
  char *v5; // ebx

  if ( (g_nCBRoleAnimData[3] & 1) == 0 )
  {
    g_nCBRoleAnimData[0] = 0;
    LOBYTE(g_nCBRoleAnimData[3]) |= 1u;
    g_nCBRoleAnimData[1] = 0;
    g_nCBRoleAnimData[2] = 0;
    atexit(nullsub_27);
  }
  v3 = 2632 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = (int *)(&this->m_Task[22].bValid + v3);
  v5 = &this->m_sRoleData[80 * *(_DWORD *)&this->m_sRoleData[128] + 148 + v3];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->IsReady(*(_DWORD *)((char *)&this->m_Task[22].fTemp + v3)) )
    goto LABEL_12;
  if ( !v5[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
  {
    *(_DWORD *)(*(&this->m_sRoleArray.m_nSize + *v4) + 6632) = *(_DWORD *)(*(&this->m_sRoleArray.m_nSize + *v4) + 6636);
    if ( !((CCBRoleState *)this->m_pRoleState)->GetRoleField(*v4, 17)
      && !((CCBRoleState *)this->m_pRoleState)->GetRoleField(*v4, 14) )
    {
      ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ClearTaskIfMatch */, 0, 0, 0, *((_DWORD *)&this->m_Task[22].fTemp + 658 * *(_DWORD *)&this->m_sRoleData[124]), g_nCBRoleAnimData, 0, 1);
    }
    v5[41] = 1;
  }
  if ( v5[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_sRoleArray.m_nSize + *v4))->ForceDelTaskByPFN() )
LABEL_12:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00501E60
int CCBStageRole::TaskShowLevelUp(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // edi
  void ( ***v6)(_DWORD, int); // ecx
  CScreenMode *Instance; // eax
  char v9; // al
  void (***v10)(_DWORD, _DWORD); // ecx

  v3 = 329 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = 80 * *(_DWORD *)&this->m_sRoleData[128];
  v5 = &this->m_sRoleData[8 * v3 + 148 + v4];
  if ( this->m_sRoleData[8 * v3 + 189 + v4] )
  {
    if ( this->m_sRoleData[8 * v3 + 191 + v4] == 1
      || *(float *)&this->m_pStage->m_WPXVariance - *(float *)&this->m_sRoleData[8 * v3 + 172 + v4] > *(float *)&this->m_sRoleData[8 * v3 + 180 + v4]
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v9) )
    {
      v10 = *(void ( ****)(_DWORD, _DWORD))((char *)&this->m_pStage->m_pRoleState->m_Role[1].dwMagicID[3][3]
                                                    + 1);
      (**v10)(v10, 0);
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    v6 = *(void ( ****)(_DWORD, int))((char *)&this->m_pStage->m_pRoleState->m_Role[1].dwMagicID[3][3] + 1);
    (**v6)(v6, 1);
    ((CCBUI *)this->m_pStage->m_pRoleState)->CreateResultWindow(0);
    sub_4DB940(this->m_pStage->m_pCam, 0);
    ((C2DSpark *)this->m_pStage->m_pRole[7])->CreateStars();
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(&g_EffMgr, 1);
    v5[41] = 1;
    return 0;
  }
}

// 0x00501F30
int CCBStageRole::TaskShowSkillLearned(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // edi
  void ( ***v6)(_DWORD, int); // ecx
  CScreenMode *Instance; // eax
  char v9; // al
  void (***v10)(_DWORD, _DWORD); // ecx

  v3 = 329 * *(_DWORD *)&this->m_sRoleData[124];
  v4 = 80 * *(_DWORD *)&this->m_sRoleData[128];
  v5 = &this->m_sRoleData[8 * v3 + 148 + v4];
  if ( this->m_sRoleData[8 * v3 + 189 + v4] )
  {
    if ( this->m_sRoleData[8 * v3 + 191 + v4] == 1
      || *(float *)&this->m_pStage->m_WPXVariance - *(float *)&this->m_sRoleData[8 * v3 + 172 + v4] > *(float *)&this->m_sRoleData[8 * v3 + 180 + v4]
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v9) )
    {
      v10 = *(void ( ****)(_DWORD, _DWORD))((char *)&this->m_pStage->m_pRoleState->m_Role[1].dwMagicID[3][4]
                                                    + 1);
      (**v10)(v10, 0);
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    v6 = *(void ( ****)(_DWORD, int))((char *)&this->m_pStage->m_pRoleState->m_Role[1].dwMagicID[3][4] + 1);
    (**v6)(v6, 1);
    ((CCBUI *)this->m_pStage->m_pRoleState)->CreateResultWindow(0);
    sub_4DB940(this->m_pStage->m_pCam, 0);
    ((C2DSpark *)this->m_pStage->m_pRole[7])->CreateStars();
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(&g_EffMgr, 1);
    v5[41] = 1;
    return 0;
  }
}

// 0x00508930
void CCBStageRole::_CCBStageRole(int nVal, int nVal2, int *p_DWORD)
{
  int v5; // edx
  char *v6; // esi
  _DWORD *v7; // ecx
  int v8; // eax
  int v9; // edi
  int v10; // edi
  bool IsRoleAlive2; // al
  bool v12; // cc
  int v13; // edx
  double v14; // st7
  char v15; // dl
  float *v16; // eax
  float v17; // ecx
  char v18; // cl
  int v19; // eax
  float *v20; // eax
  float v21; // edi
  char v22; // dl
  float *v23; // eax
  float v24; // ecx
  char v25; // cl
  int v26; // eax
  float *v27; // eax
  float v28; // edi
  float v29; // [esp+0x10] [ebp-0x3C]
  int nVal3; // [esp+0x14] [ebp-0x38]
  int nVal4; // [esp+0x18] [ebp-0x34]
  int v32; // [esp+0x20] [ebp-0x2C]
  int v33; // [esp+0x24] [ebp-0x28]
  float v34; // [esp+0x28] [ebp-0x24]
  int v35; // [esp+0x2C] [ebp-0x20]
  int v36; // [esp+0x30] [ebp-0x1C]
  float v37; // [esp+0x34] [ebp-0x18]
  int v38; // [esp+0x38] [ebp-0x14]
  int v39; // [esp+0x3C] [ebp-0x10]
  float v40; // [esp+0x40] [ebp-0xC]
  int v41; // [esp+0x44] [ebp-0x8]
  int v42; // [esp+0x48] [ebp-0x4]

  v5 = *(_DWORD *)&this->m_Task[19].cmd.bDestRole[60 * nVal + 3];
  v6 = (char *)this + 60 * nVal;
  if ( v5 != p_DWORD[1] )
    v5 = p_DWORD[1];
  v7 = *(_DWORD **)this->m_sLastRole;
  v29 = 0.0;
  nVal3 = 0;
  nVal4 = 0;
  v34 = *(float *)(v7[5] + 900);
  v35 = *(_DWORD *)(v7[5] + 904);
  v36 = *(_DWORD *)(v7[5] + 908);
  v37 = *(float *)(v7[16] + 6596);
  v38 = *(_DWORD *)(v7[16] + 6600);
  v39 = *(_DWORD *)(v7[16] + 6604);
  v8 = p_DWORD[2];
  if ( (unsigned int)v8 > 4 )
  {
    v40 = *(float *)(v7[16] + 6596);
    v41 = *(_DWORD *)(v7[16] + 6600);
    v9 = *(_DWORD *)(v7[16] + 6604);
  }
  else
  {
    v40 = *(float *)(v7[5] + 900);
    v41 = *(_DWORD *)(v7[5] + 904);
    v9 = *(_DWORD *)(v7[5] + 908);
  }
  v42 = v9;
  v10 = p_DWORD[3];
  if ( v10 == -1 )
  {
    switch ( *p_DWORD )
    {
      case 260:
      case 269:
        IsRoleAlive2 = ((PAL_GDB *)*(PAL_GDB **)(*v7 + 16))->IsRoleAlive2(v5);
        goto LABEL_12;
      case 261:
        IsRoleAlive2 = ((PAL_GDB *)*(PAL_GDB **)(*v7 + 16))->IsItemEquipment(v5);
        goto LABEL_12;
      case 262:
        IsRoleAlive2 = ((PAL_GDB *)*(PAL_GDB **)(*v7 + 16))->IsSkillEmpty(v5);
        goto LABEL_12;
      case 270:
        IsRoleAlive2 = ((PAL_GDB *)*(PAL_GDB **)(*v7 + 16))->IsItemConsumed(v5);
LABEL_12:
        if ( IsRoleAlive2 )
          goto LABEL_13;
        v8 = p_DWORD[2];
        if ( v8 < 0 )
          goto LABEL_21;
        v12 = v8 < 5;
        break;
      default:
LABEL_13:
        v8 = p_DWORD[2];
        if ( (unsigned int)v8 > 4 )
          goto LABEL_20;
        goto LABEL_21;
    }
  }
  else
  {
    if ( v10 < 0 )
      goto LABEL_21;
    v12 = v10 < 5;
  }
  if ( v12 )
  {
LABEL_20:
    v13 = v36;
    v14 = v34;
    v32 = v35;
    goto LABEL_22;
  }
LABEL_21:
  v13 = v39;
  v14 = v37;
  v32 = v38;
LABEL_22:
  v33 = v13;
  if ( nVal2 == 1 )
  {
    if ( *((_DWORD *)v6 + 612) != -1 )
    {
      if ( v6[2452] )
      {
        v29 = v40;
        nVal3 = v41;
        nVal4 = v42;
      }
      if ( v6[2453] )
      {
        v29 = v14;
        nVal3 = v32;
        nVal4 = v13;
      }
      v15 = v6[2454];
      if ( v15 )
      {
        v16 = *(float **)(*(_DWORD *)this->m_sLastRole + 4 * v8 + 24);
        v17 = v16[1649];
        v16 += 1649;
        v29 = v17;
        nVal3 = *((_DWORD *)v16 + 1);
        nVal4 = *((_DWORD *)v16 + 2);
      }
      v18 = v6[2455];
      if ( v18 )
      {
        v19 = p_DWORD[3];
        if ( v19 == -1 )
        {
          v29 = v14;
          nVal3 = v32;
          nVal4 = v33;
        }
        else
        {
          v20 = *(float **)(*(_DWORD *)this->m_sLastRole + 4 * v19 + 24);
          v21 = v20[1649];
          v20 += 1649;
          v29 = v21;
          nVal3 = *((_DWORD *)v20 + 1);
          nVal4 = *((_DWORD *)v20 + 2);
        }
      }
      if ( !v6[2452] && !v6[2453] && !v15 && !v18 )
      {
        v29 = *((float *)v6 + 614);
        nVal3 = *((_DWORD *)v6 + 615);
        nVal4 = *((_DWORD *)v6 + 616);
      }
      if ( *p_DWORD == 269 )
        ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 48))->Render(*((_DWORD *)v6 + 612));
      if ( *p_DWORD == 270 )
        ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 44))->Render(*((_DWORD *)v6 + 612));
      if ( *p_DWORD == 269 )
        ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 48))->Init(*((_DWORD *)v6 + 612), SLODWORD(v29), nVal3, nVal4, 0);
      else
        ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 44))->Init(*((_DWORD *)v6 + 612), SLODWORD(v29), nVal3, nVal4, 0);
    }
  }
  else if ( *((_DWORD *)v6 + 619) != -1 )
  {
    if ( v6[2480] )
    {
      v29 = v40;
      nVal3 = v41;
      nVal4 = v42;
    }
    if ( v6[2481] )
    {
      v29 = v14;
      nVal3 = v32;
      nVal4 = v13;
    }
    v22 = v6[2482];
    if ( v22 )
    {
      v23 = *(float **)(*(_DWORD *)this->m_sLastRole + 4 * v8 + 24);
      v24 = v23[1649];
      v23 += 1649;
      v29 = v24;
      nVal3 = *((_DWORD *)v23 + 1);
      nVal4 = *((_DWORD *)v23 + 2);
    }
    v25 = v6[2483];
    if ( v25 )
    {
      v26 = p_DWORD[3];
      if ( v26 == -1 )
      {
        v29 = v14;
        nVal3 = v32;
        nVal4 = v33;
      }
      else
      {
        v27 = *(float **)(*(_DWORD *)this->m_sLastRole + 4 * v26 + 24);
        v28 = v27[1649];
        v27 += 1649;
        v29 = v28;
        nVal3 = *((_DWORD *)v27 + 1);
        nVal4 = *((_DWORD *)v27 + 2);
      }
    }
    if ( !v6[2480] && !v6[2481] && !v22 && !v25 )
    {
      v29 = *((float *)v6 + 621);
      nVal3 = *((_DWORD *)v6 + 622);
      nVal4 = *((_DWORD *)v6 + 623);
    }
    if ( *p_DWORD == 269 )
      ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 48))->Render(*((_DWORD *)v6 + 619));
    if ( *p_DWORD == 270 )
      ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 44))->Render(*((_DWORD *)v6 + 619));
    if ( *p_DWORD == 269 )
      ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 48))->Init(*((_DWORD *)v6 + 619), SLODWORD(v29), nVal3, nVal4, 0);
    else
      ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 44))->Init(*((_DWORD *)v6 + 619), SLODWORD(v29), nVal3, nVal4, 0);
  }
}

// 0x005090F0
void CCBStageRole::Proceed()
{
  dword_17ABC7C = 519;
  dword_17ABC80 = 519;
  dword_17ABC84 = 519;
  dword_17ABC88 = 519;
}

// 0x00509130
// attributes: thunk
void CCBStageRole::SetAlive(bool bAlive)
{

}

// 0x00509140
void CCBStageRole::SetMaxBlend()
{
  dword_17ABC8C = 128;
  dword_17ABC90 = 323;
  dword_17ABC94 = 519;
  dword_17ABC98 = 716;
}

// 0x00509180
// attributes: thunk
void CCBStageRole::SetVisible()
{

}

// 0x00509190
void CCBStageRole::SetPause()
{
  dword_17ABC9C = 545;
  dword_17ABCA0 = 545;
  dword_17ABCA4 = 545;
  dword_17ABCA8 = 545;
}

// 0x005091D0
// attributes: thunk
void CCBStageRole::OnChangeAction()
{

}

// 0x005091E0
int CCBStageRole::CheckAction()
{
  dword_17ABCAC = 121;
  dword_17ABCB0 = 316;
  dword_17ABCB4 = 512;
  dword_17ABCB8 = 709;
  return 709;
}

// 0x00509220
// attributes: thunk
void CCBStageRole::OnPlayAction()
{
  compiler_init_00509230(this);
}

// 0x00509270
// attributes: thunk
bool CCBStageRole::IsUnderMouse()
{
  return this->IsCollideRay();
}

// 0x00509280
bool CCBStageRole::IsCollideRay()
{
  dword_17AB9DC = 12;
  return 12;
}

// 0x00509290
// attributes: thunk
void CCBStageRole::GetRoleRadius()
{

}

// 0x005092A0
int CCBStageRole::GetRoleHeight()
{
  dword_17AB9D8 = 508;
  return 508;
}

// 0x005092B0
CCBStageRole * CCBStageRole::GetOBBox(int nVal)
{
  int *p_m_nOBBox; // ebp
  int *v4; // edi
  CCBRoleState *v5; // ecx
  int v7; // [esp+0x10] [ebp-0x4]

  p_m_nOBBox = &this->m_nOBBox;
  v7 = 64;
  do
  {
    v4 = p_m_nOBBox;
    p_m_nOBBox += 24;
    memset(v4, 0, 0x2Cu);
    --v7;
  }
  while ( v7 );
  *(_DWORD *)&this->m_Task[62].cmd.bDestRole[3] = 0;
  *(_DWORD *)&this->m_Task[62].cmd.bDestRole[7] = 0;
  *(_DWORD *)&this->m_Task[62].cmd.bValid = 0;
  this->m_Task[62].fTemp = 0.0;
  this->m_Task[62].fTemp2 = 0.0;
  this->m_Task[62].dwID = 0;
  *(_DWORD *)&this->m_Task[62].eMode = 0;
  *(_DWORD *)&this->m_Task[62].bValid = 0;
  *(_DWORD *)(&this->m_Task[62].bExecuted + 2) = 0;
  this->m_Task[63].fp[0] = 0;
  this->m_Task[63].fp[1] = 0;
  this->m_Task[63].fp[2] = 0;
  this->m_Task[63].fp[3] = 0;
  this->m_Task[63].vec1.x = 0.0;
  this->m_Task[63].vec1.y = 0.0;
  memset(this, 0, 0x1A18u);
  this->m_pStage = (CCBStage *)nVal;
  v5 = *(CCBRoleState **)(*(_DWORD *)nVal + 16);
  this->m_Task[63].cmd.dwItemID = 0;
  this->m_pRoleState = v5;
  this->m_Task[63].cmd.nSrcRole = gbCrc32Compute("over");
  this->m_Task[63].cmd.nDestRole = gbCrc32Compute("work");
  *(_DWORD *)&this->m_Task[63].cmd.bMultiSrcRole = gbCrc32Compute("work1");
  *(_DWORD *)&this->m_Task[63].cmd.bSrcRole[2] = gbCrc32Compute("pause");
  *(_DWORD *)&this->m_Task[63].cmd.bSrcRole[6] = gbCrc32Compute("store");
  *(_DWORD *)&this->m_Task[63].cmd.bSrcRole[10] = gbCrc32Compute("flyup");
  *(_DWORD *)&this->m_Task[63].cmd.bDestRole[3] = gbCrc32Compute("flydown");
  *(_DWORD *)&this->m_Task[63].cmd.bDestRole[7] = 0;
  strcpy(this->m_sLastRole, "???");
  return this;
}

// 0x00509410
int CCBStageRole::GetRotAngle()
{
  int *p_m_nRotAngle; // ebp
  _DWORD *v4; // ecx

  p_m_nRotAngle = &this->m_nRotAngle;
  this->m_nRotAngle = 0;
  this->m_nCurActionOff = 0;
  v4 = &this->m_Task[62].cmd.bDestRole[3];
  this->m_bValid = 0;
  this->m_bVisible = 0;
  p_m_nRotAngle[2] = 0;
  this->m_bPaused = 0;
  this->m_bAbsTime = 0;
  this->m_fTimeScale = 1.0;
  this->m_bAlive = 0;
  this->m_bRun = 0;
  this->m_bShowWeapon = 0;
  this->m_bFlash = 0;
  this->m_bForceFinishThrowingWeapon = 0;
  this->m_fMaxThrowSpeed = 0.0;
  this->m_fThrowSpeed = 0.0;
  this->m_fBlend = 0.0;
  this->m_Task[63].vec1.z = 0.0;
  this->m_Task[63].cmd.dwCmdKind = 0;
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[6] = 2;
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 32;
  this->m_fThrowLen = 0.0;
  this->m_ThrowCmdData = (tagCmdData *)-1;
  p_m_nRotAngle[3] = -1;
  this->m_bCatching = 0;
  this->m_bDelAllTask = 0;
  this->m_iState = 0;
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[2] = 1;
  *v4 = 0;
  v4[1] = 0;
  v4[2] = 0;
  this->m_Task[62].fTemp = 0.0;
  this->m_Task[62].fTemp2 = 0.0;
  this->m_Task[62].dwID = 0;
  *(_DWORD *)&this->m_Task[62].eMode = 0;
  *(_DWORD *)&this->m_Task[62].bValid = 0;
  *(_DWORD *)(&this->m_Task[62].bExecuted + 2) = 0;
  this->m_Task[63].fp[0] = 0;
  this->m_Task[63].fp[1] = 0;
  this->m_Task[63].fp[2] = 0;
  this->m_Task[63].fp[3] = 0;
  this->m_Task[63].vec1.x = 0.0;
  this->m_Task[63].vec1.y = 0.0;
  memset(&this->m_nTransportRun, 0, 0x1800u);
  this->m_Task[63].cmd.dwItemID = 0;
  return 0;
}

// 0x00509540
bool CCBStageRole::IsIdle(unsigned int dwVal)
{
  Actor *v3; // eax
  int v4; // eax
  char Buffer[260]; // [esp+0x8] [ebp-0x910] BYREF
  char pExceptionObject[1024]; // [esp+0x10C] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x50C] [ebp-0x40C] BYREF
  int v9; // [esp+0x914] [ebp-0x4]

  v3 = (Actor *)operator new(0x224u);
  v9 = 0;
  if ( v3 )
    ((Actor *)v3)->FastInit();
  else
    v4 = 0;
  v9 = -1;
  this->m_nIndex = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("C++ new failed!", aDProjectPal3Co_5, 120),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( dwVal <= 4 )
  {
    switch ( dwVal )
    {
      case 0u:
        sprintf(Buffer, (const char *const)&g_pfnUpdateFuncs[4]);
        break;
      case 1u:
        sprintf(Buffer, (const char *const)&g_pfnUpdateFuncs[3]);
        break;
      case 2u:
        sprintf(Buffer, a106);
        break;
      case 3u:
        sprintf(Buffer, (const char *const)&g_pfnUpdateFuncs[1]);
        break;
      case 4u:
        sprintf(Buffer, (const char *const)g_pfnUpdateFuncs);
        break;
    }
    sub_536D20((Actor *)this->m_nIndex, Buffer, 0);

  }
  this->m_bFlash = 0;
  return 1;
}

// 0x00509690
bool CCBStageRole::IsAtInitPos()
{
  Actor *m_nIndex; // ecx
  void *v3; // edi

  m_nIndex = (Actor *)this->m_nIndex;
  if ( !m_nIndex )
    return 1;
  ((Actor *)m_nIndex)->UpdateAllActions();
  v3 = (void *)this->m_nIndex;
  if ( v3 )
  {
    ((NPC *)this->m_nIndex)->FreeBuffer();
    operator delete(v3);
  }
  this->m_nIndex = 0;
  return 1;
}

// 0x005096D0
bool CCBStageRole::IsAtProtectPos(int index, int nAttacker, int nVal)
{
  tagRoleState *inited; // eax
  float m_fBlend; // eax
  unsigned int v7; // eax
  char *v8; // edi
  const char *v9; // esi
  char v10; // cl
  tagRoleState *v11; // eax
  char *v12; // edi
  unsigned int v13; // edx
  char *v14; // edi
  CCBStage *m_pStage; // eax
  CCBRoleState *m_pRoleState; // ecx
  CCBStageScene *m_pScene; // esi
  int v18; // eax
  gbVec3D *v19; // eax
  CCBStage *v20; // eax
  CCBRoleState *v21; // ecx
  CCBStageScene *v22; // esi
  int v23; // eax
  int m_fBlend_low; // eax
  char v25; // dl
  float v26; // eax
  char *sModel; // [esp-0x8] [ebp-0x11C]
  float v29; // [esp+0xC] [ebp-0x108]
  char Buffer[260]; // [esp+0x10] [ebp-0x104] BYREF

  LODWORD(this->m_fBlend) = index;
  *(_DWORD *)&this->m_bBeSelected = nAttacker;
  this->m_bValid = 1;
  this->m_bVisible = 1;
  this->m_bAlive = 1;
  this->m_Task[63].vec1.z = 0.0;
  if ( index >= 5 && index < 11 )
  {
    if ( strcmp(((CCBRoleState *)this->m_pRoleState)->InitUI(index)->sModel, this->m_sLastRole) )
    {
      sModel = ((CCBRoleState *)this->m_pRoleState)->InitUI(index)->sModel;
      inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(index);
      sprintf(Buffer, "role\\%s\\%s.ini", inited->sModel, sModel);
      m_fBlend = this->m_fBlend;
      if ( SLODWORD(m_fBlend) < 5
        || SLODWORD(m_fBlend) >= 11
        || (int)((gbVFileSystem *)g_pVFileSys)->FileExistNum(Buffer) > 0 )
      {
        v11 = ((CCBRoleState *)this->m_pRoleState)->InitUI(index);
        sub_536D20((Actor *)this->m_nIndex, v11->sModel, 0);
        v12 = ((CCBRoleState *)this->m_pRoleState)->InitUI(index)->sModel;
        v13 = strlen(v12) + 1;
        v14 = &v12[v13];
        qmemcpy(this->m_sLastRole, &v14[-v13], 4 * (v13 >> 2));
        v9 = &v14[4 * (v13 >> 2) - v13];
        v8 = &this->m_sLastRole[4 * (v13 >> 2)];
        v10 = v13;
      }
      else
      {
        sub_536D20((Actor *)this->m_nIndex, "203", 0);
        v7 = strlen("203") + 1;
        qmemcpy(this->m_sLastRole, "203", 4 * (v7 >> 2));
        v9 = &a203[4 * (v7 >> 2)];
        v8 = &this->m_sLastRole[4 * (v7 >> 2)];
        v10 = v7;
      }
      qmemcpy(v8, v9, v10 & 3);
    }

  }
  if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(index) )
    *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 32;
  else
    *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 50;

  if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(index) == 1 )
  {
    m_pStage = this->m_pStage;
    m_pRoleState = this->m_pRoleState;
    this->m_Task[63].cmd.dwCmdKind = 1110704128;
    m_pScene = m_pStage->m_pScene;
    LOBYTE(v18) = ((CCBRoleState *)m_pRoleState)->IsAllWeDead(index);
    v19 = &m_pScene->m_vecFiveLineup[v18];
  }
  else
  {
    v20 = this->m_pStage;
    v21 = this->m_pRoleState;
    this->m_Task[63].cmd.dwCmdKind = -1022951424;
    v22 = v20->m_pScene;
    LOBYTE(v23) = ((CCBRoleState *)v21)->IsAllWeDead(index);
    v19 = &v22->m_vecEnemyLineup[v23];
  }
  *(float *)&this->m_Task[62].eMode = v19->x;
  *(float *)&this->m_Task[62].bValid = v19->y;
  *(float *)(&this->m_Task[62].bExecuted + 2) = v19->z;
  this->m_Task[62].fTemp = *(float *)&this->m_Task[62].eMode;
  this->m_Task[62].fTemp2 = *(float *)&this->m_Task[62].bValid;
  this->m_Task[62].dwID = *(_DWORD *)(&this->m_Task[62].bExecuted + 2);
  v29 = *(float *)&this->m_Task[63].cmd.dwCmdKind;
  m_fBlend_low = LODWORD(this->m_fBlend);
  this->m_Task[63].vec1.z = v29;
  if ( m_fBlend_low >= 5 && m_fBlend_low < 11 )
  {
    if ( !BYTE1(this->m_pRoleState->m_Role[0].dwMagicID[8][4]) )
      goto LABEL_24;
    goto LABEL_23;
  }
  if ( (unsigned int)m_fBlend_low <= 4 && BYTE2(this->m_pRoleState->m_Role[0].dwMagicID[8][4]) )
LABEL_23:
    this->m_Task[63].vec1.z = v29 + 180.0;
LABEL_24:
  this->ClearAniMsg(0, 1.0);
  v25 = BYTE2(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[2][4]);
  v26 = this->m_fBlend;
  this->m_bShowWeaponModel = v25;
  if ( LODWORD(v26) <= 4 )
    this->m_bShowWeaponModel = 0;
  return 1;
}

// 0x005099A0
bool CCBStageRole::IsTaskFinished(int nVal, BOOL fpTask)
{
  int v3; // edi
  bool result; // al
  Actor *m_nIndex; // ecx
  int v7; // eax
  tagRoleState *inited; // eax
  tagRoleState *v9; // eax
  int v10; // ecx
  CCBStageRole *Instance; // eax
  CCBStageRole *v12; // eax
  int v13; // [esp-0x8] [ebp-0x14]
  float scale; // [esp+0x4] [ebp-0x8]
  float v15; // [esp+0x8] [ebp-0x4]

  result = this->m_bValid;
  if ( result )
  {
    m_nIndex = (Actor *)this->m_nIndex;
    if ( m_nIndex )
    {
      scale = 1.3;
      if ( !this->m_bForceFinishThrowingWeapon )
      {
        v7 = *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10];
        if ( v7 == 32 || v7 == 50 )
          scale = 0.64999998;
      }
      v15 = scale;
      if ( this->m_bAbsTime )
      {
        ((Actor *)m_nIndex)->SetTimeScale(scale);
      }
      else if ( this->m_bPaused )
      {
        v15 = 0.0;
      }
      else
      {
        v15 = scale * this->m_fTimeScale;
      }
      v13 = v3;
      ((Actor *)this->m_nIndex)->SetTimeScale(v15);
      if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[1][3] )
      {
        inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
        ((gbGeomNode *)inited[1].dwMagicID[1][3])->SetBladeTimeScale(v15);
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[2][0] )
      {
        v9 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
        ((gbGeomNode *)v9[1].dwMagicID[2][0])->SetBladeTimeScale(v15);
      }
      if ( this->ForceDelTaskByPFN() && !this->m_bForceFinishThrowingWeapon )
      {
        this->ClearBadPushTask(0.0099999998);
        if ( !((CCBRoleState *)this->m_pStage->m_pCBSystem->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
          this->m_bAlive = 0;
      }
      v10 = this->m_nIndex;
      this->m_Task[63].cmd.dwItemID = 0;
      if ( ((gbVisNode *)*(gbVisNode **)(v10 + 16))->PopMessage((gbNodeMsgObj *)&dword_17AB9C8) == 1
        && dword_17AB9C8 == 1 )
      {
        this->m_Task[63].cmd.dwItemID = dword_17AB9CC;
      }
      if ( !this->m_bForceFinishThrowingWeapon )
        this->Grab(this->m_Task[63].cmd.dwItemID);
      if ( !LODWORD(this->m_fBlend) && *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] != 31 )
      {
        Instance = (CCBStageRole *)CScreenMode::GetInstance();
        ((CCBStageRole *)Instance)->PlaySound(aWe011, v3);
      }
      if ( LODWORD(this->m_fBlend) == 4 && *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] != 31 )
      {
        v12 = (CCBStageRole *)CScreenMode::GetInstance();
        ((CCBStageRole *)v12)->PlaySound(aWe011b, v13);
      }
      return ((Actor *)this->m_nIndex)->QueryState();
    }
  }
  return result;
}

// 0x00509B90
void CCBStageRole::IsDoTask(gbMatrixStack *fpTask)
{
  float m_fBlend; // eax
  int m_fBlend_low; // eax
  int v5; // esi
  int v6; // edi
  char RoleType; // al
  unsigned int v8; // edi
  int v9; // esi
  int height; // ebx
  int v11; // edx
  int v12; // ecx
  tagRoleState *v13; // eax
  tagRoleState *v14; // eax
  int *LastBladePos; // ecx
  double v16; // st7
  tagRoleState *inited; // eax
  CCBStage *m_pStage; // eax
  char m_bShowWeaponModel; // cl
  __int16 v20; // [esp+0x2C] [ebp-0x6A]
  float v21; // [esp+0x32] [ebp-0x64] BYREF
  float v22; // [esp+0x36] [ebp-0x60] BYREF
  gbVec3D dwMsg; // [esp+0x3A] [ebp-0x5C] BYREF
  float v24[4]; // [esp+0x46] [ebp-0x50] BYREF
  gbMatrix4 v25; // [esp+0x56] [ebp-0x40] BYREF

  if ( (byte_17AB9C4 & 1) == 0 )
  {
    dword_17AB9B8 = 0;
    byte_17AB9C4 |= 1u;
    dword_17AB9BC = 1065353216;
    dword_17AB9C0 = 0;
    atexit(nullsub_32);
  }
  m_fBlend = this->m_fBlend;
  memset(&dwMsg, 0, sizeof(dwMsg));
  v20 = 0;
  if ( SLODWORD(m_fBlend) >= 5 && SLODWORD(m_fBlend) < 11 )
    this->ProcPursueRole(0, 0, 0);
  if ( this->m_bShowWeapon )
  {
    this->DoTask(&dwMsg);
    m_fBlend_low = LODWORD(this->m_fBlend);
    dwMsg.y = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 10.0 + (double)m_fBlend_low) * 5.0 + dwMsg.y + 6.0;
    if ( (unsigned int)m_fBlend_low <= 4
      || m_fBlend_low >= 5 && m_fBlend_low < 11 && this->ForceEndTaskByPFN() )
    {
      ((gbCamera *)&this->m_pStage->m_pCam->OrthoSize)->PointWorldToScr(&dwMsg, &v21, &v22);
      v5 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(LODWORD(this->m_fBlend), 0);
      v6 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(LODWORD(this->m_fBlend), 1);
      RoleType = ((CCBRoleState *)this->m_pRoleState)->GetRoleType(LODWORD(this->m_fBlend));
      if ( LODWORD(this->m_fBlend) == 10 && this->m_pRoleState->m_Role[0].bMagicMastered[0][5]
        || RoleType && v5 > v6 / 4 )
      {
        strcpy(
          (char *)&g_nCBRoleHitTable[17],
          (const char *)((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[3][1]);
      }
      else
      {
        sprintf((char *const)&g_nCBRoleHitTable[17], "%d/%d", v5, v6);
      }
      v8 = 10 * strlen((const char *)&g_nCBRoleHitTable[17]);
      v9 = (__int64)((v21 + 1.0) * (double)g_DrvInfo.width * 0.5);
      height = (__int64)((1.0 - v22) * (double)g_DrvInfo.height * 0.5);
      if ( v9 >= 0 )
      {
        if ( v9 > (int)(g_DrvInfo.width - v8) )
          v9 = g_DrvInfo.width - v8;
      }
      else
      {
        v9 = 0;
      }
      if ( height >= 20 )
      {
        if ( height > g_DrvInfo.height )
          height = g_DrvInfo.height;
      }
      else
      {
        height = 20;
      }
      ((CCBStage *)this->m_pStage->m_TempStorageNGH)->InitSlotFlags((const char *)&g_nCBRoleHitTable[17], v9, height, -1);
      if ( LODWORD(this->m_fBlend) > 4 )
        this->ProcPursueRole(v9, height, 1);
    }
  }
  if ( BYTE1(this->m_pStage->m_pCBSystem->m_nTimesOfCombat) && g_RoleSystemCombat.dwInitParam == (HWND)1
    || this->m_bVisible && (this->m_bAlive || SLODWORD(this->m_fBlend) < 5) )
  {
    ((gbMatrixStack *)fpTask)->Push();
    ((gbMatrixStack *)fpTask)->Translate((gbVec3D *)&this->m_Task[62].fTemp);
    ((gbMatrixStack *)fpTask)->Rotate(this->m_Task[63].vec1.z, (gbVec3D *)&dword_17AB9B8);
    v11 = *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10];
    switch ( dword_56FE98[v11] )
    {
      case 1:
        v20 = 1;
        break;
      case 2:
        v20 = 256;
        break;
      case 3:
        v20 = 0;
        break;
    }
    v12 = LODWORD(this->m_fBlend);
    if ( !v12 && (v11 == 39 || v11 == 49) )
      v20 = 0;
    if ( v12 == 3 )
      v20 = 257;
    if ( v12 == 1 )
      v20 = 257;
    if ( (v12 == 2 || v12 == 4) && v11 == 46 )
      v20 = 256;
    if ( this->m_bForceFinishThrowingWeapon )
    {
      if ( this->m_fMaxThrowSpeed > 0.0 || (LOBYTE(v20) = 0, this->m_fMaxThrowSpeed >= 0.0) )
        LOBYTE(v20) = 1;
      if ( this->m_fThrowSpeed <= 0.0 && this->m_fThrowSpeed < 0.0 )
        goto LABEL_64;
    }
    else if ( !HIBYTE(v20) )
    {
LABEL_64:
      if ( (_BYTE)v20 && ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[1][3] )
      {
        ((gbMatrixStack *)fpTask)->Push();
        ((gbActor *)*(gbActor **)(this->m_nIndex + 16))->GetTagNodeTM(&v25, "tag_weapon2");
        ((gbMatrixStack *)fpTask)->MultMatrix(&v25);
        inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
        (*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)inited[1].dwMagicID[1][3] + 16))(
          inited[1].dwMagicID[1][3],
          0);
        ((gbMatrixStack *)fpTask)->Pop();
      }
      if ( this->m_bFlash )
      {
        m_pStage = this->m_pStage;
        m_bShowWeaponModel = this->m_bShowWeaponModel;
        v24[0] = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 7.8000002) * 0.34999999 + 0.64999998;
        v24[1] = v24[0];
        v24[2] = v24[0];
        if ( m_bShowWeaponModel )
        {
          ((gbRenderEffect *)*(&m_pStage->m_TempStorageWPX[2].m_nUpdateMode + 4))->SetVariant(6, v24);
          ((Actor *)this->m_nIndex)->DispatchAction(*(&this->m_pStage->m_TempStorageWPX[2].m_nUpdateMode + 4));
        }
        else
        {
          ((gbRenderEffect *)*(&m_pStage->m_TempStorageWPX[2].m_nUpdateMode + 3))->SetVariant(6, v24);
          ((Actor *)this->m_nIndex)->DispatchAction(*(&this->m_pStage->m_TempStorageWPX[2].m_nUpdateMode + 3));
        }
      }
      else
      {
        ((Actor *)this->m_nIndex)->DispatchAction(0);
      }
      ((gbMatrixStack *)fpTask)->Pop();
      return;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(v12)[1].dwMagicID[2][0] )
    {
      ((gbMatrixStack *)fpTask)->Push();
      ((gbActor *)*(gbActor **)(this->m_nIndex + 16))->GetTagNodeTM(&v25, "tag_weapon1");
      ((gbMatrixStack *)fpTask)->MultMatrix(&v25);
      v13 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      (*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)v13[1].dwMagicID[2][0] + 16))(
        v13[1].dwMagicID[2][0],
        0);
      ((gbMatrixStack *)fpTask)->Pop();
      if ( LODWORD(this->m_fBlend) == 3 && *(_BYTE *)(g_SceneMgr.m_partyInitData[27] + 613) == 3 )
      {
        v14 = ((CCBRoleState *)this->m_pRoleState)->InitUI(3);
        LastBladePos = (int *)((gbGeomNode *)v14[1].dwMagicID[2][0])->GetLastBladePos(0);
        if ( LastBladePos )
        {
          v16 = this->m_pStage->m_pCBSystem->m_DeltaTime + flt_17ABCCC;
          flt_17ABCCC = v16;
          if ( v16 >= 0.050000001 )
          {
            ((C3DSpark *)this->m_pStage->m_pCBSystem->m_p3DSpark)->CreateOne(*LastBladePos, LastBladePos[1], LastBladePos[2]);
            flt_17ABCCC = flt_17ABCCC - 0.050000001;
          }
        }
      }
    }
    goto LABEL_64;
  }
}

// 0x0050A180
int CCBStageRole::Grab(int a2)
{
  this->FindFreeSlot(a2);

  return this->FindNextTask();
}

// 0x0050A1A0
void CCBStageRole::Release(char dwStageTaskID)
{
  this->m_bAlive = dwStageTaskID;
}

// 0x0050A1B0
void CCBStageRole::TryRelease()
{
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 23) )
    this->ClearAniMsg(1, 0.44);
  else
    this->ClearAniMsg(0, 1.0);
}

// 0x0050A1F0
void CCBStageRole::ForceRelease(char pData)
{
  this->m_bVisible = pData;
}

// 0x0050A200
void CCBStageRole::DangerForceRelease(char pData)
{
  this->m_bPaused = pData;
}

// 0x0050A210
bool CCBStageRole::IsGrabedBy()
{
  Actor *m_nIndex; // ecx
  bool result; // al

  m_nIndex = (Actor *)this->m_nIndex;
  if ( m_nIndex )
  {
    ((Actor *)m_nIndex)->EnableTransition(*(&bVisible + *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10]), this->m_bShowWeaponModel != 0);
    return ((Actor *)this->m_nIndex)->CompareActionName(*(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10], 0);
  }
  return result;
}

// 0x0050A260
void CCBStageRole::GetPointerPos()
{
  Actor *m_nIndex; // ecx

  m_nIndex = (Actor *)this->m_nIndex;
  if ( m_nIndex )
  {
    ((Actor *)m_nIndex)->EnableTransition(*(&bVisible + *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10]), this->m_bShowWeaponModel != 0);
    ((Actor *)this->m_nIndex)->SetVisible(*(&bVisible + *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10]));
  }
}

// 0x0050A2B0
void CCBStageRole::SetBladeTime(int fBladeTime)
{
  int *p_fTemp; // eax
  double v4; // st7
  double v5; // st6
  long double v6; // st7
  int v7; // [esp+0x8] [ebp-0x8]
  int v8; // [esp+0xC] [ebp-0x4]

  if ( (g_nCBRoleHitTable[16] & 1) == 0 )
  {
    g_nCBRoleHitTable[13] = 0;
    LOBYTE(g_nCBRoleHitTable[16]) |= 1u;
    g_nCBRoleHitTable[14] = 0;
    g_nCBRoleHitTable[15] = 0;
    atexit(nullsub_35);
  }
  if ( (g_nCBRoleHitTable[16] & 2) == 0 )
  {
    g_nCBRoleHitTable[9] = 0;
    LOBYTE(g_nCBRoleHitTable[16]) |= 2u;
    g_nCBRoleHitTable[10] = 0;
    g_nCBRoleHitTable[11] = 0;
    atexit(nullsub_34);
  }
  if ( (g_nCBRoleHitTable[16] & 4) == 0 )
  {
    LOBYTE(g_nCBRoleHitTable[16]) |= 4u;
    g_nCBRoleHitTable[5] = 0;
    g_nCBRoleHitTable[6] = 0;
    g_nCBRoleHitTable[7] = 1065353216;
    atexit(nullsub_33);
  }
  p_fTemp = (int *)&this->m_pStage->m_pRole[fBladeTime]->m_Task[62].fTemp;
  g_nCBRoleHitTable[9] = *p_fTemp;
  g_nCBRoleHitTable[10] = p_fTemp[1];
  g_nCBRoleHitTable[11] = p_fTemp[2];
  v4 = *(float *)&g_nCBRoleHitTable[9] - this->m_Task[62].fTemp;
  *(float *)&v7 = *(float *)&g_nCBRoleHitTable[10] - this->m_Task[62].fTemp2;
  v5 = *(float *)&g_nCBRoleHitTable[11] - *(float *)&this->m_Task[62].dwID;
  g_nCBRoleHitTable[14] = v7;
  *(float *)&v8 = v5;
  *(float *)&g_nCBRoleHitTable[13] = v4;
  g_nCBRoleHitTable[15] = v8;
  ((gbVec3D *)&g_nCBRoleHitTable[13])->Normalize();
  v6 = acos(
         *(float *)&g_nCBRoleHitTable[7] * *(float *)&g_nCBRoleHitTable[15]
       + *(float *)&g_nCBRoleHitTable[6] * *(float *)&g_nCBRoleHitTable[14]
       + *(float *)&g_nCBRoleHitTable[5] * *(float *)&g_nCBRoleHitTable[13]);
  this->m_Task[63].vec1.z = v6;
  if ( *(float *)&g_nCBRoleHitTable[13] < 0.0 )
    this->m_Task[63].vec1.z = 6.2831855 - v6;
  this->m_Task[63].vec1.z = this->m_Task[63].vec1.z * 57.29578;
}

// 0x0050A4B0
bool CCBStageRole::CheckViewTarget()
{
  CCBStage *m_pStage; // eax
  gbRay v4; // [esp-0x18] [ebp-0x44] BYREF
  float pPos[2]; // [esp+0xC] [ebp-0x20] BYREF
  _BYTE pTarget[24]; // [esp+0x14] [ebp-0x18] BYREF

  m_pStage = this->m_pStage;
  pPos[0] = *(float *)&this->m_pStage->m_WPXVariance;
  pPos[1] = *(float *)&m_pStage->m_pDisplayChain;
  qmemcpy(&v4, ((CameraCtrl *)m_pStage->m_pCam)->GetViewTarget(pTarget, pPos), sizeof(v4));
  return this->LoadAction(v4);
}

// 0x0050A500
bool CCBStageRole::LoadAction(gbRay nActIndex)
{
  gbOBBox *WorldPos; // eax

  WorldPos = (gbOBBox *)this->GetWorldPos();
  return ((gbRay *)&nActIndex)->IsColOBB(WorldPos) == 1;
}

// 0x0050A520
int CCBStageRole::GetStatus(int index)
{
  ((Actor *)this->m_nIndex)->PlayAction((int)&this->m_dwID);
  return LODWORD(this->m_fBlend);
}

// 0x0050A560
float * CCBStageRole::GetWorldPos()
{
  gbMatrix4 v3; // [esp+0x8] [ebp-0x40] BYREF

  ((Actor *)this->m_nIndex)->PlayAction((int)&this->m_dwID);
  ((gbMatrix4 *)&v3)->LoadIdentity();
  ((gbMatrix4 *)&v3)->SetAxisAngle(1, LODWORD(this->m_Task[63].vec1.z));
  ((gbMatrix4 *)&this->m_dwID)->RightMultiply(&v3);
  ((gbMatrix4 *)&this->m_dwID)->RightTranslate((gbVec3D *)&this->m_Task[62].fTemp);
  return (float *)&this->m_dwID;
}

// 0x0050A5D0
double CCBStageRole::AddTask(float *fp)
{
  double v3; // st7
  double v4; // st6
  double v6; // st7
  gbVec3D v7; // [esp+0x4] [ebp-0x18] BYREF
  float v8; // [esp+0x14] [ebp-0x8]
  float v9; // [esp+0x18] [ebp-0x4]

  if ( (g_nCBRoleHitTable[4] & 1) == 0 )
  {
    v7.x = 0.0;
    LOBYTE(g_nCBRoleHitTable[4]) |= 1u;
    v7.y = 0.0;
    v7.z = 1.0;
    g_nCBRoleHitTable[1] = 0;
    g_nCBRoleHitTable[2] = 0;
    g_nCBRoleHitTable[3] = 1065353216;
    atexit(nullsub_36);
  }
  v3 = *fp - this->m_Task[62].fTemp;
  v8 = fp[1] - this->m_Task[62].fTemp2;
  v4 = fp[2] - *(float *)&this->m_Task[62].dwID;
  v7.y = v8;
  v9 = v4;
  v7.x = v3;
  v7.z = v9;
  if ( ((gbVec3D *)&v7)->Length() <= 0.0 )
    return 0.0;
  ((gbVec3D *)&v7)->Normalize();
  v6 = acos(
         v7.y * *(float *)&g_nCBRoleHitTable[2]
       + v7.z * *(float *)&g_nCBRoleHitTable[3]
       + *(float *)&g_nCBRoleHitTable[1] * v7.x);
  if ( v7.x < 0.0 )
    v6 = 6.2831855 - v6;
  return v6 * 57.29578;
}

// 0x0050A6F0
bool CCBStageRole::ForceDelTaskByPFN()
{
  return LODWORD(this->m_fThrowLen) == 0;
}

// 0x0050A700
bool CCBStageRole::ForceEndTaskByPFN()
{
  double v1; // st7
  double v2; // st6
  float v4; // [esp+0x4] [ebp-0x14]
  float v5; // [esp+0x8] [ebp-0x10]
  gbVec3D v6; // [esp+0xC] [ebp-0xC] BYREF

  v1 = this->m_Task[62].fTemp - *(float *)&this->m_Task[62].eMode;
  v4 = this->m_Task[62].fTemp2 - *(float *)&this->m_Task[62].bValid;
  v2 = *(float *)&this->m_Task[62].dwID - *(float *)(&this->m_Task[62].bExecuted + 2);
  v6.y = v4;
  v5 = v2;
  v6.x = v1;
  v6.z = v5;
  return ((gbVec3D *)&v6)->Length() <= 13.0;
}

// 0x0050A770
bool CCBStageRole::EndTask(int fp, int dwTaskID)
{
  float m_fBlend; // eax
  CCBStage *m_pStage; // ecx
  float *v6; // eax
  float *p_eMode; // ecx
  double v8; // st7
  double v9; // st6
  CCBStage *v10; // edx
  float *v11; // eax
  double v12; // st7
  double v13; // st7
  double v14; // st6
  gbVec3D v16; // [esp+0x4] [ebp-0x30] BYREF
  gbVec3D v17; // [esp+0x10] [ebp-0x24] BYREF
  float v18; // [esp+0x20] [ebp-0x14]
  float v19; // [esp+0x24] [ebp-0x10]
  float v20; // [esp+0x2C] [ebp-0x8]
  float v21; // [esp+0x30] [ebp-0x4]

  memset(&v16, 0, sizeof(v16));
  m_fBlend = this->m_fBlend;
  memset(&v17, 0, sizeof(v17));
  if ( m_fBlend != 0.0 )
    return 0;
  m_pStage = this->m_pStage;
  v6 = (float *)m_pStage->m_pRole[fp];
  p_eMode = (float *)&m_pStage->m_pRole[dwTaskID]->m_Task[62].eMode;
  v6 += 1649;
  v8 = *p_eMode - *v6;
  v18 = p_eMode[1] - v6[1];
  v9 = p_eMode[2] - v6[2];
  v16.y = v18;
  v19 = v9;
  v16.x = v8;
  v16.z = v19;
  ((gbVec3D *)&v16)->Normalize();
  v10 = this->m_pStage;
  v16.x = v16.x * 40.0;
  v16.y = v16.y * 40.0;
  v16.z = v16.z * 40.0;
  v11 = (float *)v10->m_pRole[fp];
  v12 = v16.x + v11[1649];
  v18 = v16.y + v11[1650];
  v19 = v16.z + v11[1651];
  v16.x = v12;
  v16.z = v19;
  v16.y = v18;
  v13 = this->m_Task[62].fTemp - v12;
  v20 = this->m_Task[62].fTemp2 - v18;
  v14 = *(float *)&this->m_Task[62].dwID - v19;
  v17.y = v20;
  v21 = v14;
  v17.x = v13;
  v17.z = v21;
  return ((gbVec3D *)&v17)->Length() <= 20.0;
}

// 0x0050A8E0
bool CCBStageRole::DelTask(int nIndex)
{
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[6] = nIndex;
  return 1;
}

// 0x0050A8F0
bool CCBStageRole::DelAllTask(int nVal, char pData)
{
  bool result; // al

  result = 1;
  if ( this->m_bCatching == 1 )
    return 0;
  this->m_bCatching = 1;
  this->m_bDelAllTask = pData;
  this->m_iState = nVal;
  return result;
}

// 0x0050A920
char CCBStageRole::GetCurrentTask(int nVal)
{
  char result; // al

  if ( nVal != 0x7FFFFFFF || (result = this->m_bCatching) != 0 )
  {
    result = this->GetCurrentState();
    this->m_bCatching = 0;
    this->m_bDelAllTask = 0;
    this->m_iState = 0;
  }
  return result;
}

// 0x0050A960
int CCBStageRole::GetCurrentTaskIndex()
{

  this->m_bCatching = 0;
  this->m_bDelAllTask = 0;
  this->m_iState = 0;
  return 0;
}

// 0x0050A980
bool CCBStageRole::IsReady(int idx)
{
  return this->m_bCatching && this->m_iState == idx;
}

// 0x0050A9B0
tagRoleState * CCBStageRole::DoTask(gbVec3D *dwMsg)
{
  gbOBBox *WorldPos; // eax
  tagRoleState *result; // eax
  struct gbVec3D v5; // [esp+0x8] [ebp-0xC] BYREF

  if ( (g_nCBRoleHitTable[0] & 1) == 0 )
  {
    LOBYTE(g_nCBRoleHitTable[0]) |= 1u;
    atexit(nullsub_37);
  }
  WorldPos = (gbOBBox *)this->GetWorldPos();
  *dwMsg = *((gbOBBox *)WorldPos)->GetCenter(&v5);
  dwMsg->y = this->m_fTask * 0.5 + dwMsg->y + 10.0;
  result = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
  if ( result->dwID == 707 )
    dwMsg->y = dwMsg->y - 80.0;
  return result;
}

// 0x0050AA60
void CCBStageRole::ClearBadPushTask(float fVal)
{
  unsigned int m_fBlend_low; // eax
  tagRoleState *inited; // eax
  tagRoleState *v5; // eax

  m_fBlend_low = LODWORD(this->m_fBlend);
  if ( m_fBlend_low <= 4 )
  {
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(m_fBlend_low)[1].dwMagicID[1][3] )
    {
      inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbGeomNode *)inited[1].dwMagicID[1][3])->SetBladeTime(fVal);
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[2][0] )
    {
      v5 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbGeomNode *)v5[1].dwMagicID[2][0])->SetBladeTime(fVal);
    }
  }
}

// 0x0050AAE0
double CCBStageRole::PushBackAllTask()
{
  int m_nIndex; // eax
  float v3; // [esp+0x4] [ebp-0x4] BYREF

  m_nIndex = this->m_nIndex;
  v3 = 0.0;
  if ( ((int ( *)(_DWORD, float *))gbVisNode::GetBlend)(*(_DWORD *)(m_nIndex + 16), &v3) )
    return v3;
  else
    return 1.0;
}

// 0x0050AB10
void CCBStageRole::ClearAniMsg(char pData, float fVal)
{
  tagRoleState *inited; // eax
  tagRoleState *v5; // eax
  tagRoleState *v6; // eax
  tagRoleState *v7; // eax

  if ( fVal <= 0.98000002 && pData )
  {
    ((gbVisNode *)*(_DWORD *)(this->m_nIndex + 16))->SetBlend(1, LODWORD(fVal));
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[2][0] )
    {
      inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)inited[1].dwMagicID[2][0])->SetBlend(1, LODWORD(fVal));
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[1][3] )
    {
      v5 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)v5[1].dwMagicID[1][3])->SetBlend(1, LODWORD(fVal));
    }
  }
  else
  {
    ((gbVisNode *)*(_DWORD *)(this->m_nIndex + 16))->SetBlend(0, 1065353216);
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[2][0] )
    {
      v6 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)v6[1].dwMagicID[2][0])->SetBlend(0, 1065353216);
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))[1].dwMagicID[1][3] )
    {
      v7 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)v7[1].dwMagicID[1][3])->SetBlend(0, 1065353216);
    }
  }
}

// 0x0050AC50
void CCBStageRole::SetParam(int pParam, char dw1)
{
  const char *EditorTaskDescription; // eax
  Actor *m_nIndex; // ecx

  if ( pParam > 0 )
  {
    sprintf(byte_17AB818, "z%02d", pParam);
    if ( (byte_1895558 & 1) == 0 )
    {
      byte_1895558 |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    EditorTaskDescription = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)byte_17AB818);
    if ( dw1 || EditorTaskDescription != *(const char **)&this->m_Task[63].cmd.bDestRole[7] )
    {
      m_nIndex = (Actor *)this->m_nIndex;
      *(_DWORD *)&this->m_Task[63].cmd.bDestRole[7] = EditorTaskDescription;
      ((Actor *)m_nIndex)->SetVisible((int)byte_17AB818);
      (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(this->m_nIndex + 16) + 24))(
        *(_DWORD *)(this->m_nIndex + 16),
        0);
    }
  }
}

// 0x0050AD30
char CCBStageRole::GetProperCurAction(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        int *pnVal,
        const void *pData,
        int nVal6)
{
  int *v11; // eax
  int *v12; // eax
  int *v13; // eax
  _DWORD v14[3]; // [esp+0x4] [ebp-0xC] BYREF

  if ( (g_nCBRoleMoveTable[23] & 1) == 0 )
  {
    g_nCBRoleMoveTable[20] = 0;
    LOBYTE(g_nCBRoleMoveTable[23]) |= 1u;
    g_nCBRoleMoveTable[21] = 0;
    g_nCBRoleMoveTable[22] = 0;
    atexit(nullsub_40);
  }
  if ( (g_nCBRoleMoveTable[23] & 2) == 0 )
  {
    g_nCBRoleMoveTable[16] = 0;
    LOBYTE(g_nCBRoleMoveTable[23]) |= 2u;
    g_nCBRoleMoveTable[17] = 0;
    g_nCBRoleMoveTable[18] = 0;
    atexit(nullsub_39);
  }
  if ( (g_nCBRoleMoveTable[23] & 4) == 0 )
  {
    g_nCBRoleMoveTable[12] = 0;
    LOBYTE(g_nCBRoleMoveTable[23]) |= 4u;
    g_nCBRoleMoveTable[13] = 0;
    g_nCBRoleMoveTable[14] = 0;
    atexit(nullsub_38);
  }
  if ( this->m_iState != nVal5 )
    return 0;
  v11 = pnVal;
  if ( !pnVal )
  {
    memset(v14, 0, sizeof(v14));
    v11 = v14;
  }
  g_nCBRoleMoveTable[20] = *v11;
  g_nCBRoleMoveTable[21] = v11[1];
  g_nCBRoleMoveTable[22] = v11[2];
  if ( nVal6 == 2 )
  {

    goto LABEL_15;
  }
  if ( nVal6 != 3 )
  {
LABEL_15:
    v12 = &this->m_nTransportRun + 24 * LODWORD(this->m_fThrowLen);
    *v12 = nVal;
    v12[1] = nVal2;
    v12[2] = nVal3;
    v12[3] = nVal4;
    *(&this->m_bProperCurAction + 96 * LODWORD(this->m_fThrowLen)) = 1;
    *(&this->m_bSlotBlocked0 + 96 * LODWORD(this->m_fThrowLen)) = 0;
    *(&this->m_bSlotActive0 + 96 * LODWORD(this->m_fThrowLen)) = 0;
    *(&this->m_nCurState + 24 * LODWORD(this->m_fThrowLen)) = ((CCBSystem *)this->m_pStage->m_pCBSystem)->ProcProtect();
    v13 = &this->m_nUseRecoverItem + 24 * LODWORD(this->m_fThrowLen);
    *v13 = g_nCBRoleMoveTable[20];
    v13[1] = g_nCBRoleMoveTable[21];
    v13[2] = g_nCBRoleMoveTable[22];
    *(&this->m_nActionType0 + 24 * LODWORD(this->m_fThrowLen)) = nVal6;
    if ( pData )
      qmemcpy(&this->m_nOBBox + 24 * LODWORD(this->m_fThrowLen), pData, 0x2Cu);
    else
      memset(&this->m_nOBBox + 24 * LODWORD(this->m_fThrowLen), 0, 0x2Cu);
    goto LABEL_23;
  }

  this->m_bProperCurAction = 1;
  this->m_bSlotBlocked0 = 0;
  this->m_bSlotActive0 = 0;
  this->m_nTransportRun = nVal;
  this->m_ActionSlot0 = nVal2;
  this->m_ActionSlot1 = nVal3;
  this->m_ActionSlot2 = nVal4;
  this->m_nCurState = ((CCBSystem *)this->m_pStage->m_pCBSystem)->ProcProtect();
  this->m_nUseRecoverItem = g_nCBRoleMoveTable[20];
  this->m_nProperAction = g_nCBRoleMoveTable[21];
  this->m_OBBox = (gbOBBox *)g_nCBRoleMoveTable[22];
  this->m_nActionType0 = 3;
  if ( pData )
    qmemcpy(&this->m_nOBBox, pData, 0x2Cu);
  else
    memset(&this->m_nOBBox, 0, 0x2Cu);
  BYTE2(this->m_Task[0].cmd.nDestRole) = 0;
LABEL_23:
  ++LODWORD(this->m_fThrowLen);
  return 1;
}

// 0x0050B070
char CCBStageRole::ProcTransportRun(
        
        unsigned int dwMsg,
        int nVal,
        int nVal2,
        int nVal3,
        int *pnVal,
        const void *pData,
        int nVal4)
{
  int *v9; // eax
  float v11; // eax
  _DWORD v12[3]; // [esp+0x8] [ebp-0xC] BYREF

  if ( (g_nCBRoleMoveTable[11] & 1) == 0 )
  {
    g_nCBRoleMoveTable[8] = 0;
    LOBYTE(g_nCBRoleMoveTable[11]) |= 1u;
    g_nCBRoleMoveTable[9] = 0;
    g_nCBRoleMoveTable[10] = 0;
    atexit(nullsub_43);
  }
  if ( (g_nCBRoleMoveTable[11] & 2) == 0 )
  {
    g_nCBRoleMoveTable[4] = 0;
    LOBYTE(g_nCBRoleMoveTable[11]) |= 2u;
    g_nCBRoleMoveTable[5] = 0;
    g_nCBRoleMoveTable[6] = 0;
    atexit(nullsub_42);
  }
  if ( (g_nCBRoleMoveTable[11] & 4) == 0 )
  {
    g_nCBRoleMoveTable[0] = 0;
    LOBYTE(g_nCBRoleMoveTable[11]) |= 4u;
    g_nCBRoleMoveTable[1] = 0;
    g_nCBRoleMoveTable[2] = 0;
    atexit(nullsub_41);
  }
  v9 = pnVal;
  if ( !pnVal )
  {
    memset(v12, 0, sizeof(v12));
    v9 = v12;
  }
  g_nCBRoleMoveTable[8] = *v9;
  g_nCBRoleMoveTable[9] = v9[1];
  g_nCBRoleMoveTable[10] = v9[2];
  switch ( nVal4 )
  {
    case 2:

      break;
    case 3:

      break;
    case 4:
      if ( SLODWORD(this->m_fThrowLen) > 0 )
        return 0;
      break;
    default:
      return 0;
  }
  this->m_bProperCurAction = 1;
  this->m_bSlotBlocked0 = 0;
  this->m_bSlotActive0 = 0;
  this->m_nTransportRun = dwMsg;
  this->m_ActionSlot0 = nVal;
  this->m_ActionSlot1 = nVal2;
  this->m_ActionSlot2 = nVal3;
  this->m_nCurState = ((CCBSystem *)this->m_pStage->m_pCBSystem)->ProcProtect();
  this->m_nUseRecoverItem = g_nCBRoleMoveTable[8];
  this->m_nProperAction = g_nCBRoleMoveTable[9];
  this->m_OBBox = (gbOBBox *)g_nCBRoleMoveTable[10];
  this->m_nActionType0 = nVal4;
  if ( pData )
    qmemcpy(&this->m_nOBBox, pData, 0x2Cu);
  else
    memset(&this->m_nOBBox, 0, 0x2Cu);
  LODWORD(v11) = LODWORD(this->m_fThrowLen) + 1;
  BYTE2(this->m_Task[0].cmd.nDestRole) = 0;
  this->m_fThrowLen = v11;
  return 1;
}

// 0x0050B290
void CCBStageRole::SetForceFinishThrowingWeapon(int bForce)
{
  int v2; // ebx
  int *v3; // eax

  v2 = bForce;
  if ( bForce == 63 )
  {
    memset(&this->m_Task[61].cmd.bSrcRole[2], 0, 0x60u);
    --LODWORD(this->m_fThrowLen);
  }
  else
  {
    if ( bForce < SLODWORD(this->m_fThrowLen) )
    {
      v3 = &this->m_nTransportRun + 24 * bForce;
      do
      {
        ++v2;
        qmemcpy(v3, v3 + 24, 0x60u);
        v3 += 24;
      }
      while ( v2 < SLODWORD(this->m_fThrowLen) );
    }
    memset(&this->m_nTransportRun + 24 * LODWORD(this->m_fThrowLen)--, 0, 0x60u);
  }
}

// 0x0050B330
char CCBStageRole::GetCurrentState()
{
  int *p_m_nCurState; // eax
  int v2; // edx

  p_m_nCurState = &this->m_nCurState;
  v2 = 64;
  do
  {
    *((_BYTE *)p_m_nCurState + 8) = 0;
    *p_m_nCurState = 0;
    p_m_nCurState += 24;
    --v2;
  }
  while ( v2 );
  this->m_fThrowLen = 0.0;
  return 1;
}

// 0x0050B360
unsigned int CCBStageRole::ProcCatchED()
{
  unsigned int result; // eax

  if ( SLODWORD(this->m_fBlend) < 5 )
  {
    ((Actor *)this->m_nIndex)->GetAnimDuration(animId);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)"z09");
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)"z06");
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)"z03");
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)"z04");
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)"z05");
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)&dword_5888D0);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)&dword_5888C8);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)&dword_5888C4);
    return ((Actor *)this->m_nIndex)->GetAnimDuration((int)&dword_5888BC);
  }
  return result;
}

// 0x0050B430
char CCBStageRole::FindFreeSlot(int a2)
{
  int v3; // eax
  _BYTE *i; // ecx
  int ( *m_nRotAngle)(char *, int); // eax

  v3 = 0;
  for ( i = &this->m_bSlotActive0; !*(i - 1) || *i; i += 96 )
  {
    if ( ++v3 >= 64 )
    {
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = this->ProcTurn();
      LOBYTE(m_nRotAngle) = this->IsGrabedBy();
      this->m_ThrowCmdData = (tagCmdData *)-1;
      return (char)m_nRotAngle;
    }
  }
  this->m_ThrowCmdData = (tagCmdData *)v3;
  this->m_nRotAngle = *(&this->m_nTransportRun + 24 * v3);
  this->m_nCurActionOff = *(&this->m_ActionSlot0 + 24 * v3);
  this->m_nCurActionParam = *(&this->m_ActionSlot1 + 24 * v3);
  this->_todo_19C = *(&this->m_ActionSlot2 + 24 * v3);
  m_nRotAngle = (int ( *)(char *, int))this->m_nRotAngle;
  if ( m_nRotAngle )
    LOBYTE(m_nRotAngle) = m_nRotAngle((char *)this + this->m_nCurActionOff, a2);
  return (char)m_nRotAngle;
}

// 0x0050B4C0
char CCBStageRole::CountValidTasks()
{
  int v1; // edx
  _BYTE *p_m_bSlotActive0; // eax

  v1 = 0;
  p_m_bSlotActive0 = &this->m_bSlotActive0;
  while ( *(p_m_bSlotActive0 - 1) != 1 || *p_m_bSlotActive0 != 1 )
  {
    ++v1;
    p_m_bSlotActive0 += 96;
    if ( v1 >= 64 )
      return (char)p_m_bSlotActive0;
  }
  this->SetForceFinishThrowingWeapon(v1);
  return (char)p_m_bSlotActive0;
}

// 0x0050B4F0
int CCBStageRole::FindNextTask()
{
  int result; // eax
  int v3; // esi
  int *p_nSrcRole; // ebx

  result = LODWORD(this->m_fThrowLen);
  if ( result > 1 )
  {
    v3 = 1;
    p_nSrcRole = &this->m_Task[0].cmd.nSrcRole;
    do
    {
      if ( *p_nSrcRole == 3 )
        this->SetForceFinishThrowingWeapon(v3);
      result = LODWORD(this->m_fThrowLen);
      ++v3;
      p_nSrcRole += 24;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x0050B530
void CCBStageRole::GetTaskState()
{
  float m_fThrowLen; // eax
  float v2; // edx
  int *v3; // edi

  m_fThrowLen = this->m_fThrowLen;
  if ( m_fThrowLen != 0.0 )
  {
    if ( SLODWORD(m_fThrowLen) > 0 )
    {
      v2 = this->m_fThrowLen;
      v3 = &this->m_nTransportRun + 24 * LODWORD(m_fThrowLen);
      do
      {
        --LODWORD(v2);
        qmemcpy(v3, v3 - 24, 0x60u);
        v3 -= 24;
      }
      while ( v2 != 0.0 );
    }
    memset(&this->m_nTransportRun, 0, 0x60u);
  }
}

// 0x0050B580
char CCBStageRole::ProcPursueRole(int formal, int nVal, char pData)
{
  CCBUI *m_pUI; // edi
  UIStatic *v6; // ecx
  int v7; // ebx
  UIStatic *v8; // ecx
  UIStatic *v9; // ecx
  UIStatic *v10; // ecx
  UIStatic *v11; // ecx
  UIStatic *v12; // ecx
  UIStatic *v13; // ecx
  UIStatic *v14; // ecx
  UIStatic *v15; // ecx
  UIStatic *v16; // ecx
  UIStatic *v17; // ecx
  UIStatic *v18; // ecx
  UIStatic *v19; // ecx
  UIStatic *v20; // ecx
  UIStatic *v21; // ecx
  UIStatic *v22; // ecx
  UIStatic *v23; // ecx
  UIStatic *v24; // ecx
  char result; // al
  UIStatic *v26; // ecx
  UIStatic *v27; // ecx
  UIStatic *v28; // ecx
  UIStatic *v29; // ecx
  UIStatic *v30; // ecx
  UIStatic *v31; // ecx
  UIStatic *v32; // ecx
  UIStatic *v33; // ecx
  UIStatic *v34; // ecx
  UIStatic *v35; // ecx
  UIStatic *v36; // ecx
  UIStatic *v37; // ecx
  UIStatic *v38; // ecx
  UIStatic *v39; // ecx
  UIStatic *v40; // ecx
  UIStatic *v41; // ecx
  UIStatic *v42; // ecx
  UIStatic *v43; // ecx
  UIStatic *v44; // ecx
  UIStatic *v45; // ecx

  m_pUI = this->m_pStage->m_pCBSystem->m_pUI;
  if ( pData )
  {
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 6) )
    {
      v6 = m_pUI->m_pRoleStateFace[LODWORD(this->m_fBlend) + 3];
// [VFTABLE] ((void ( *)(UIStatic *, int))v6->__vftable->ShowWindow)(v6, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateFace[LODWORD(this->m_fBlend) + 3]->__vftable, formal, nVal);
      v7 = formal + 24;
    }
    else
    {
      v7 = formal;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 7) )
    {
      v8 = m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v8->__vftable->ShowWindow)(v8, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 8) )
    {
      v9 = m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v9->__vftable->ShowWindow)(v9, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 9) )
    {
      v10 = m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v10->__vftable->ShowWindow)(v10, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 12) )
    {
      v11 = m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v11->__vftable->ShowWindow)(v11, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 13) )
    {
      v12 = m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v12->__vftable->ShowWindow)(v12, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 10) )
    {
      v13 = m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v13->__vftable->ShowWindow)(v13, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 11) )
    {
      v14 = m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v14->__vftable->ShowWindow)(v14, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 14) )
    {
      v15 = m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v15->__vftable->ShowWindow)(v15, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 15) )
    {
      v16 = m_pUI->m_pRoleStateStable[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v16->__vftable->ShowWindow)(v16, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateStable[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 16) )
    {
      v17 = m_pUI->m_pRoleStateBlank[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v17->__vftable->ShowWindow)(v17, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateBlank[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 17) )
    {
      v18 = m_pUI->m_pRoleStateForbid[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v18->__vftable->ShowWindow)(v18, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateForbid[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 18) )
    {
      v19 = m_pUI->m_pRoleStateSleep[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v19->__vftable->ShowWindow)(v19, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateSleep[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 19) )
    {
      v20 = m_pUI->m_pRoleStateChaos[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v20->__vftable->ShowWindow)(v20, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateChaos[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 20) )
    {
      v21 = m_pUI->m_pRoleStateMad[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v21->__vftable->ShowWindow)(v21, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateMad[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 21) )
    {
      v22 = m_pUI->m_pRoleStateMirror[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v22->__vftable->ShowWindow)(v22, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateMirror[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 22) )
    {
      v23 = m_pUI->m_pRoleStateWall[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v23->__vftable->ShowWindow)(v23, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateWall[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 23) )
    {
      v24 = m_pUI->m_pRoleStateBound[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v24->__vftable->ShowWindow)(v24, 1);
// [VFTABLE] sub_445D20(&m_pUI->m_pRoleStateBound[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
      v7 += 20;
    }
    result = ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 26);
    if ( result )
    {
      v26 = m_pUI->m_pRoleStateHermit[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, int))v26->__vftable->ShowWindow)(v26, 1);
// [VFTABLE] return sub_445D20(&m_pUI->m_pRoleStateHermit[LODWORD(this->m_fBlend) + 4]->__vftable, v7, nVal);
    }
  }
  else
  {
    v27 = m_pUI->m_pRoleStateFace[LODWORD(this->m_fBlend) + 3];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v27->__vftable->ShowWindow)(v27, 0);
    v28 = m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v28->__vftable->ShowWindow)(v28, 0);
    v29 = m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v29->__vftable->ShowWindow)(v29, 0);
    v30 = m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v30->__vftable->ShowWindow)(v30, 0);
    v31 = m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v31->__vftable->ShowWindow)(v31, 0);
    v32 = m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v32->__vftable->ShowWindow)(v32, 0);
    v33 = m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v33->__vftable->ShowWindow)(v33, 0);
    v34 = m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v34->__vftable->ShowWindow)(v34, 0);
    v35 = m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v35->__vftable->ShowWindow)(v35, 0);
    v36 = m_pUI->m_pRoleStateStable[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v36->__vftable->ShowWindow)(v36, 0);
    v37 = m_pUI->m_pRoleStateBlank[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v37->__vftable->ShowWindow)(v37, 0);
    v38 = m_pUI->m_pRoleStateForbid[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v38->__vftable->ShowWindow)(v38, 0);
    v39 = m_pUI->m_pRoleStateSleep[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v39->__vftable->ShowWindow)(v39, 0);
    v40 = m_pUI->m_pRoleStateChaos[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v40->__vftable->ShowWindow)(v40, 0);
    v41 = m_pUI->m_pRoleStateMad[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v41->__vftable->ShowWindow)(v41, 0);
    v42 = m_pUI->m_pRoleStateMirror[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v42->__vftable->ShowWindow)(v42, 0);
    v43 = m_pUI->m_pRoleStateWall[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v43->__vftable->ShowWindow)(v43, 0);
    v44 = m_pUI->m_pRoleStateBound[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v44->__vftable->ShowWindow)(v44, 0);
    v45 = m_pUI->m_pRoleStateHermit[LODWORD(this->m_fBlend) + 4];
// [VFTABLE] return ((char ( *)(UIStatic *, _DWORD))v45->__vftable->ShowWindow)(v45, 0);
  }
  return result;
}

// 0x0050BBD0
unsigned int CCBStageRole::ProcTurn()
{
  unsigned int m_fBlend_low; // eax
  CCBRoleState *m_pRoleState; // ecx
  int v5; // eax

  m_fBlend_low = LODWORD(this->m_fBlend);
  m_pRoleState = this->m_pRoleState;
  if ( !m_pRoleState->m_Role[0].bMagicMastered[5][892 * m_fBlend_low + 4] )
  {
    if ( m_fBlend_low <= 4 )
      return 32;
    return 50;
  }
  if ( !((CCBRoleState *)m_pRoleState)->IsActive(m_fBlend_low) )
    return 50;
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(LODWORD(this->m_fBlend)) == 5 )
    return 47;
  if ( *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[6] == 4 )
    return 34;
  if ( LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend))->byMagicUseTime[8][5]) )
  {
    this->ClearBadPushTask(0.25);
    return 42;
  }
  else if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 17)
         || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 14) )
  {
    return 45;
  }
  else
  {
    v5 = ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(LODWORD(this->m_fBlend)) - 4;
    if ( v5 )
    {
      if ( v5 == 1 )
        return 47;
      return 32;
    }
    else
    {
      return 46;
    }
  }
}

// 0x0050BCD0
unsigned int CCBStageRole::ProcTurnToRole(int formal)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  tagCmdData *m_ThrowCmdData; // eax
  float *v9; // ecx
  CScreenMode *v10; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v12; // eax
  float *p_fTemp; // edi
  double m_DeltaTime; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  CCBStageRole *v19; // eax
  CCBStageRole *v20; // eax
  double v21; // st7
  double v22; // st7
  CCBStageRole *v23; // eax
  CCBStageRole *v24; // eax
  CCBStageRole *v25; // eax
  int v26; // [esp-0x4] [ebp-0x28]
  int v27; // [esp+0x0] [ebp-0x24]
  int v28; // [esp+0x10] [ebp-0x14]
  float v29; // [esp+0x10] [ebp-0x14]
  int v30; // [esp+0x14] [ebp-0x10]
  unsigned int v31; // [esp+0x14] [ebp-0x10]
  float v32; // [esp+0x18] [ebp-0xC]
  float v33; // [esp+0x1C] [ebp-0x8]
  int v34; // [esp+0x1C] [ebp-0x8]
  int v35; // [esp+0x20] [ebp-0x4]

  if ( (g_nCBRoleAttackTable[43] & 1) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[43]) |= 1u;
    g_nCBRoleAttackTable[40] = 0;
    g_nCBRoleAttackTable[41] = 0;
    g_nCBRoleAttackTable[42] = 0;
    atexit(nullsub_46);
  }
  if ( (g_nCBRoleAttackTable[43] & 2) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[43]) |= 2u;
    g_nCBRoleAttackTable[36] = 0;
    g_nCBRoleAttackTable[37] = 0;
    g_nCBRoleAttackTable[38] = 1065353216;
    atexit(nullsub_45);
  }
  if ( (g_nCBRoleAttackTable[43] & 4) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[43]) |= 4u;
    g_nCBRoleAttackTable[32] = 0;
    g_nCBRoleAttackTable[33] = 0;
    g_nCBRoleAttackTable[34] = 0;
    atexit(nullsub_44);
  }
  v3 = (char *)this + 96 * (int)this->m_ThrowCmdData;
  if ( !v3[506] )
  {
    this->m_Task[63].fp[0] = (char *)*((_DWORD *)v3 + 108);
    this->m_Task[63].fp[1] = (char *)*((_DWORD *)v3 + 109);
    this->m_Task[63].fp[2] = (char *)*((_DWORD *)v3 + 110);
    v4 = *(float *)this->m_Task[63].fp - this->m_Task[62].fTemp;
    *(float *)&v28 = *(float *)&this->m_Task[63].fp[1] - this->m_Task[62].fTemp2;
    v5 = *(float *)&this->m_Task[63].fp[2] - *(float *)&this->m_Task[62].dwID;
    g_nCBRoleAttackTable[41] = v28;
    *(float *)&v30 = v5;
    *(float *)&g_nCBRoleAttackTable[40] = v4;
    g_nCBRoleAttackTable[42] = v30;
    if ( ((gbVec3D *)&g_nCBRoleAttackTable[40])->Length() < 2.0 )
    {
      LODWORD(this->m_Task[62].fTemp) = this->m_Task[63].fp[0];
      LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
      this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      return 0;
    }
    ((gbVec3D *)&g_nCBRoleAttackTable[40])->Normalize();
    v7 = acos(
           *(float *)&g_nCBRoleAttackTable[38] * *(float *)&g_nCBRoleAttackTable[42]
         + *(float *)&g_nCBRoleAttackTable[37] * *(float *)&g_nCBRoleAttackTable[41]
         + *(float *)&g_nCBRoleAttackTable[36] * *(float *)&g_nCBRoleAttackTable[40]);
    this->m_Task[63].vec1.z = v7;
    if ( *(float *)&g_nCBRoleAttackTable[40] < 0.0 )
      this->m_Task[63].vec1.z = 6.2831855 - v7;
    this->m_Task[63].vec1.z = this->m_Task[63].vec1.z * 57.29578;
    this->m_Task[63].fp[3] = (char *)g_nCBRoleAttackTable[40];
    LODWORD(this->m_Task[63].vec1.x) = g_nCBRoleAttackTable[41];
    LODWORD(this->m_Task[63].vec1.y) = g_nCBRoleAttackTable[42];
    *(float *)&this->m_Task[63].fp[3] = *(float *)&this->m_Task[63].fp[3] * 380.0;
    this->m_Task[63].vec1.x = this->m_Task[63].vec1.x * 380.0;
    this->m_Task[63].vec1.y = this->m_Task[63].vec1.y * 380.0;
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 31;
    else
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 52;

    *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) = 1;
    this->ClearBadPushTask(0.0099999998);
    m_ThrowCmdData = this->m_ThrowCmdData;
    this->m_bRun = 1;
    v9 = (float *)((char *)this + 96 * (_DWORD)m_ThrowCmdData);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(aWe011, 0);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        v10 = CScreenMode::GetInstance();
        ((CScreenMode *)v10)->AudioSetPosition(aWe011, 1);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = CScreenMode::GetInstance();
        ((CScreenMode *)v12)->AudioSetPosition(aWe011b, v26);
      }
    }
  }
  p_fTemp = &this->m_Task[62].fTemp;
  m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
  v32 = *(float *)&this->m_Task[63].fp[3] * m_DeltaTime;
  v33 = this->m_Task[63].vec1.x * m_DeltaTime;
  v15 = v32 + this->m_Task[62].fTemp;
  v29 = this->m_Task[62].fTemp2 + v33;
  v16 = *(float *)&this->m_Task[62].dwID + m_DeltaTime * this->m_Task[63].vec1.y;
  this->m_Task[62].fTemp2 = v29;
  *(float *)&v31 = v16;
  this->m_Task[62].fTemp = v15;
  this->m_Task[62].dwID = v31;
  v17 = *(float *)this->m_Task[63].fp - this->m_Task[62].fTemp;
  *(float *)&v34 = *(float *)&this->m_Task[63].fp[1] - this->m_Task[62].fTemp2;
  v18 = *(float *)&this->m_Task[63].fp[2] - *(float *)&this->m_Task[62].dwID;
  g_nCBRoleAttackTable[41] = v34;
  *(float *)&v35 = v18;
  *(float *)&g_nCBRoleAttackTable[40] = v17;
  g_nCBRoleAttackTable[42] = v35;
  if ( ((gbVec3D *)&g_nCBRoleAttackTable[40])->Length() >= 2.0 )
  {
    ((gbVec3D *)&g_nCBRoleAttackTable[40])->Normalize();
    v21 = acos(
            *(float *)&g_nCBRoleAttackTable[38] * *(float *)&g_nCBRoleAttackTable[42]
          + *(float *)&g_nCBRoleAttackTable[37] * *(float *)&g_nCBRoleAttackTable[41]
          + *(float *)&g_nCBRoleAttackTable[36] * *(float *)&g_nCBRoleAttackTable[40]);
    if ( *(float *)&g_nCBRoleAttackTable[40] < 0.0 )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    flt_17ABCD0 = v22;
    if ( fabs(v22 - this->m_Task[63].vec1.z) < 1.570796370506287 )
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
        return 0;
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v24 = (CCBStageRole *)CScreenMode::GetInstance();
        ((CCBStageRole *)v24)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
      {
LABEL_43:
        this->m_bRun = 0;
        return 0;
      }
    }
    else
    {
      *p_fTemp = *(float *)this->m_Task[63].fp;
      LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
      this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v23 = (CCBStageRole *)CScreenMode::GetInstance();
        ((CCBStageRole *)v23)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
        goto LABEL_43;
    }
    v25 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v25)->PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *p_fTemp = *(float *)this->m_Task[63].fp;
  LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
  this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
  *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
  if ( !LODWORD(this->m_fBlend) )
  {
    v19 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v19)->PlaySound(aWe011, v27);
  }
  if ( LODWORD(this->m_fBlend) == 4 )
  {
    v20 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v20)->PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C320
unsigned int CCBStageRole::ProcBlock(int dwMsg)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  tagCmdData *m_ThrowCmdData; // eax
  float *v9; // ecx
  CScreenMode *v10; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v12; // eax
  float *p_fTemp; // edi
  double m_DeltaTime; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  CCBStageRole *v19; // eax
  CCBStageRole *v20; // eax
  double v21; // st7
  double v22; // st7
  CCBStageRole *v23; // eax
  CCBStageRole *v24; // eax
  CCBStageRole *v25; // eax
  int v26; // [esp-0x4] [ebp-0x28]
  int v27; // [esp+0x0] [ebp-0x24]
  int v28; // [esp+0x10] [ebp-0x14]
  float v29; // [esp+0x10] [ebp-0x14]
  int v30; // [esp+0x14] [ebp-0x10]
  unsigned int v31; // [esp+0x14] [ebp-0x10]
  float v32; // [esp+0x18] [ebp-0xC]
  float v33; // [esp+0x1C] [ebp-0x8]
  int v34; // [esp+0x1C] [ebp-0x8]
  int v35; // [esp+0x20] [ebp-0x4]

  if ( (g_nCBRoleAttackTable[31] & 1) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[31]) |= 1u;
    g_nCBRoleAttackTable[28] = 0;
    g_nCBRoleAttackTable[29] = 0;
    g_nCBRoleAttackTable[30] = 0;
    atexit(nullsub_49);
  }
  if ( (g_nCBRoleAttackTable[31] & 2) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[31]) |= 2u;
    g_nCBRoleAttackTable[24] = 0;
    g_nCBRoleAttackTable[25] = 0;
    g_nCBRoleAttackTable[26] = 1065353216;
    atexit(nullsub_48);
  }
  if ( (g_nCBRoleAttackTable[31] & 4) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[31]) |= 4u;
    g_nCBRoleAttackTable[20] = 0;
    g_nCBRoleAttackTable[21] = 0;
    g_nCBRoleAttackTable[22] = 0;
    atexit(nullsub_47);
  }
  v3 = (char *)this + 96 * (int)this->m_ThrowCmdData;
  if ( !v3[506] )
  {
    this->m_Task[63].fp[0] = (char *)*((_DWORD *)v3 + 108);
    this->m_Task[63].fp[1] = (char *)*((_DWORD *)v3 + 109);
    this->m_Task[63].fp[2] = (char *)*((_DWORD *)v3 + 110);
    v4 = *(float *)this->m_Task[63].fp - this->m_Task[62].fTemp;
    *(float *)&v28 = *(float *)&this->m_Task[63].fp[1] - this->m_Task[62].fTemp2;
    v5 = *(float *)&this->m_Task[63].fp[2] - *(float *)&this->m_Task[62].dwID;
    g_nCBRoleAttackTable[29] = v28;
    *(float *)&v30 = v5;
    *(float *)&g_nCBRoleAttackTable[28] = v4;
    g_nCBRoleAttackTable[30] = v30;
    if ( ((gbVec3D *)&g_nCBRoleAttackTable[28])->Length() < 2.0 )
    {
      LODWORD(this->m_Task[62].fTemp) = this->m_Task[63].fp[0];
      LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
      this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      return 0;
    }
    ((gbVec3D *)&g_nCBRoleAttackTable[28])->Normalize();
    v7 = acos(
           *(float *)&g_nCBRoleAttackTable[26] * *(float *)&g_nCBRoleAttackTable[30]
         + *(float *)&g_nCBRoleAttackTable[25] * *(float *)&g_nCBRoleAttackTable[29]
         + *(float *)&g_nCBRoleAttackTable[24] * *(float *)&g_nCBRoleAttackTable[28]);
    this->m_Task[63].vec1.z = v7;
    if ( *(float *)&g_nCBRoleAttackTable[28] < 0.0 )
      this->m_Task[63].vec1.z = 6.2831855 - v7;
    this->m_Task[63].vec1.z = this->m_Task[63].vec1.z * 57.29578;
    this->m_Task[63].fp[3] = (char *)g_nCBRoleAttackTable[28];
    LODWORD(this->m_Task[63].vec1.x) = g_nCBRoleAttackTable[29];
    LODWORD(this->m_Task[63].vec1.y) = g_nCBRoleAttackTable[30];
    *(float *)&this->m_Task[63].fp[3] = *(float *)&this->m_Task[63].fp[3] * 570.0;
    this->m_Task[63].vec1.x = this->m_Task[63].vec1.x * 570.0;
    this->m_Task[63].vec1.y = this->m_Task[63].vec1.y * 570.0;
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 31;
    else
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 52;

    *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) = 1;
    this->ClearBadPushTask(0.0099999998);
    m_ThrowCmdData = this->m_ThrowCmdData;
    this->m_bRun = 1;
    v9 = (float *)((char *)this + 96 * (_DWORD)m_ThrowCmdData);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(aWe011, 0);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        v10 = CScreenMode::GetInstance();
        ((CScreenMode *)v10)->AudioSetPosition(aWe011, 1);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = CScreenMode::GetInstance();
        ((CScreenMode *)v12)->AudioSetPosition(aWe011b, v26);
      }
    }
  }
  p_fTemp = &this->m_Task[62].fTemp;
  m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
  v32 = *(float *)&this->m_Task[63].fp[3] * m_DeltaTime;
  v33 = this->m_Task[63].vec1.x * m_DeltaTime;
  v15 = v32 + this->m_Task[62].fTemp;
  v29 = this->m_Task[62].fTemp2 + v33;
  v16 = *(float *)&this->m_Task[62].dwID + m_DeltaTime * this->m_Task[63].vec1.y;
  this->m_Task[62].fTemp2 = v29;
  *(float *)&v31 = v16;
  this->m_Task[62].fTemp = v15;
  this->m_Task[62].dwID = v31;
  v17 = *(float *)this->m_Task[63].fp - this->m_Task[62].fTemp;
  *(float *)&v34 = *(float *)&this->m_Task[63].fp[1] - this->m_Task[62].fTemp2;
  v18 = *(float *)&this->m_Task[63].fp[2] - *(float *)&this->m_Task[62].dwID;
  g_nCBRoleAttackTable[29] = v34;
  *(float *)&v35 = v18;
  *(float *)&g_nCBRoleAttackTable[28] = v17;
  g_nCBRoleAttackTable[30] = v35;
  if ( ((gbVec3D *)&g_nCBRoleAttackTable[28])->Length() >= 2.0 )
  {
    ((gbVec3D *)&g_nCBRoleAttackTable[28])->Normalize();
    v21 = acos(
            *(float *)&g_nCBRoleAttackTable[26] * *(float *)&g_nCBRoleAttackTable[30]
          + *(float *)&g_nCBRoleAttackTable[25] * *(float *)&g_nCBRoleAttackTable[29]
          + *(float *)&g_nCBRoleAttackTable[24] * *(float *)&g_nCBRoleAttackTable[28]);
    if ( *(float *)&g_nCBRoleAttackTable[28] < 0.0 )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    flt_17ABCD4 = v22;
    if ( fabs(v22 - this->m_Task[63].vec1.z) < 1.570796370506287 )
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
        return 0;
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v24 = (CCBStageRole *)CScreenMode::GetInstance();
        ((CCBStageRole *)v24)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
      {
LABEL_43:
        this->m_bRun = 0;
        return 0;
      }
    }
    else
    {
      *p_fTemp = *(float *)this->m_Task[63].fp;
      LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
      this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v23 = (CCBStageRole *)CScreenMode::GetInstance();
        ((CCBStageRole *)v23)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
        goto LABEL_43;
    }
    v25 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v25)->PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *p_fTemp = *(float *)this->m_Task[63].fp;
  LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
  this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
  *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
  if ( !LODWORD(this->m_fBlend) )
  {
    v19 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v19)->PlaySound(aWe011, v27);
  }
  if ( LODWORD(this->m_fBlend) == 4 )
  {
    v20 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v20)->PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C970
unsigned int CCBStageRole::ProcMagic(unsigned int dwMsg)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  int v8; // ecx
  CScreenMode *Instance; // eax
  double v10; // st7
  char *v11; // ecx
  double v12; // st7
  double v13; // st7
  CCBStageRole *v14; // eax
  CCBStageRole *v15; // eax
  int nVal3; // [esp+0x0] [ebp-0x28]
  int v17; // [esp+0xC] [ebp-0x1C]
  float fVal; // [esp+0x14] [ebp-0x14]
  float v19; // [esp+0x18] [ebp-0x10]
  int v20; // [esp+0x20] [ebp-0x8]
  int v21; // [esp+0x24] [ebp-0x4]

  if ( (g_nCBRoleAttackTable[19] & 1) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[19]) |= 1u;
    g_nCBRoleAttackTable[16] = 0;
    g_nCBRoleAttackTable[17] = 0;
    g_nCBRoleAttackTable[18] = 0;
    atexit(nullsub_51);
  }
  if ( (g_nCBRoleAttackTable[19] & 2) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[19]) |= 2u;
    g_nCBRoleAttackTable[12] = 0;
    g_nCBRoleAttackTable[13] = 0;
    g_nCBRoleAttackTable[14] = 1065353216;
    atexit(nullsub_50);
  }
  v19 = 1.0;
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 23) )
    v19 = 0.44;
  v3 = (char *)this + 96 * (int)this->m_ThrowCmdData;
  if ( !v3[506] )
  {
    this->m_Task[63].fp[0] = (char *)*((_DWORD *)v3 + 108);
    this->m_Task[63].fp[1] = (char *)*((_DWORD *)v3 + 109);
    this->m_Task[63].fp[2] = (char *)*((_DWORD *)v3 + 110);
    v4 = *(float *)this->m_Task[63].fp - this->m_Task[62].fTemp;
    *(float *)&v20 = *(float *)&this->m_Task[63].fp[1] - this->m_Task[62].fTemp2;
    v5 = *(float *)&this->m_Task[63].fp[2] - *(float *)&this->m_Task[62].dwID;
    g_nCBRoleAttackTable[17] = v20;
    *(float *)&v21 = v5;
    *(float *)&g_nCBRoleAttackTable[16] = v4;
    g_nCBRoleAttackTable[18] = v21;
    if ( ((gbVec3D *)&g_nCBRoleAttackTable[16])->Length() < 2.0 )
    {
      this->ClearAniMsg(0, 1.0);
      LODWORD(this->m_Task[62].fTemp) = this->m_Task[63].fp[0];
      LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
      this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      return 0;
    }
    ((gbVec3D *)&g_nCBRoleAttackTable[16])->Normalize();
    v7 = acos(
           *(float *)&g_nCBRoleAttackTable[14] * *(float *)&g_nCBRoleAttackTable[18]
         + *(float *)&g_nCBRoleAttackTable[13] * *(float *)&g_nCBRoleAttackTable[17]
         + *(float *)&g_nCBRoleAttackTable[12] * *(float *)&g_nCBRoleAttackTable[16]);
    this->m_Task[63].vec1.z = v7;
    if ( *(float *)&g_nCBRoleAttackTable[16] < 0.0 )
      this->m_Task[63].vec1.z = 6.2831855 - v7;
    v8 = 96 * (int)this->m_ThrowCmdData;
    this->m_Task[63].vec1.z = this->m_Task[63].vec1.z * 57.29578;
    *(&this->m_bSlotBlocked0 + v8) = 1;
    *((_DWORD *)&this->_todo_1E8 + 24 * (int)this->m_ThrowCmdData) = 1065353216;
    *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 32;

    *(float *)&nVal3 = this->m_Task[62].fTemp2 - 20.0;
    if ( LODWORD(this->m_fBlend) )
      ((CEffMgr *)this->m_pStage->m_pCBSystem->m_pEffMgr)->Init(221, LODWORD(this->m_Task[62].fTemp), nVal3, this->m_Task[62].dwID, 0);
    else
      ((CEffMgr *)this->m_pStage->m_pCBSystem->m_pEffMgr)->Init(222, LODWORD(this->m_Task[62].fTemp), nVal3, this->m_Task[62].dwID, 0);
    this->ClearBadPushTask(0.0099999998);
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(aWe014, 1);
  }
  v10 = this->PushBackAllTask();
  v11 = (char *)this + 96 * (int)this->m_ThrowCmdData;
  if ( *((float *)v11 + 122) <= 0.0 )
  {
    v13 = this->m_pStage->m_pCBSystem->m_DeltaTime * 2.5 + v10;
    fVal = v13;
    if ( v13 >= v19 )
    {
      fVal = v19;
      v11[505] = 1;
      v14 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v14)->PlaySound(aWe014, v17);
    }
  }
  else
  {
    v12 = v10 - this->m_pStage->m_pCBSystem->m_DeltaTime * 2.5;
    fVal = v12;
    if ( v12 < 0.0 )
    {
      *((_DWORD *)v11 + 122) = -1054867456;
      LODWORD(this->m_Task[62].fTemp) = this->m_Task[63].fp[0];
      LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
      this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
      LODWORD(this->m_Task[63].vec1.z) = this->m_Task[63].cmd.dwCmdKind;
    }
  }
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
  {
    fVal = v19;
    *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
    v15 = (CCBStageRole *)CScreenMode::GetInstance();
    ((CCBStageRole *)v15)->PlaySound(aWe014, v17);
  }
  if ( fVal < 1.0 )
    this->ClearAniMsg(1, fVal);
  else
    this->ClearAniMsg(0, 1.0);
  return 0;
}

// 0x0050CDE0
unsigned int CCBStageRole::ProcUseRecoverItem(float dwMsg)
{
  char *v3; // eax
  int v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  long double v9; // st7
  double v10; // st7
  float v11; // edi
  float m_fBlend; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v14; // eax
  double v15; // st7
  double v16; // st6
  double m_DeltaTime; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  float v21; // eax
  CCBStageRole *v22; // eax
  CCBStageRole *v23; // eax
  float v24; // eax
  CCBStageRole *v25; // eax
  CCBStageRole *v26; // eax
  int v27; // [esp+0x0] [ebp-0x18]
  float v28; // [esp+0xC] [ebp-0xC]
  int v29; // [esp+0x10] [ebp-0x8]
  int v30; // [esp+0x10] [ebp-0x8]
  float v31; // [esp+0x10] [ebp-0x8]
  int v32; // [esp+0x14] [ebp-0x4]
  int v33; // [esp+0x14] [ebp-0x4]
  float dwMsga; // [esp+0x1C] [ebp+0x4]

  if ( (g_nCBRoleAttackTable[11] & 1) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[11]) |= 1u;
    g_nCBRoleAttackTable[8] = 0;
    g_nCBRoleAttackTable[9] = 0;
    g_nCBRoleAttackTable[10] = 0;
    atexit(nullsub_54);
  }
  if ( (g_nCBRoleAttackTable[11] & 2) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[11]) |= 2u;
    g_nCBRoleAttackTable[4] = 0;
    g_nCBRoleAttackTable[5] = 0;
    g_nCBRoleAttackTable[6] = 1065353216;
    atexit(nullsub_53);
  }
  if ( (g_nCBRoleAttackTable[11] & 4) == 0 )
  {
    LOBYTE(g_nCBRoleAttackTable[11]) |= 4u;
    g_nCBRoleAttackTable[0] = 0;
    g_nCBRoleAttackTable[1] = 0;
    g_nCBRoleAttackTable[2] = 0;
    atexit(nullsub_52);
  }
  v3 = (char *)this + 96 * (int)this->m_ThrowCmdData;
  if ( v3[506] )
  {
    v11 = dwMsg;
  }
  else
  {
    *((_DWORD *)v3 + 122) = -1054867456;
    v4 = 96 * (int)this->m_ThrowCmdData;
    this->m_Task[63].fp[0] = *(char **)((char *)&this->m_nUseRecoverItem + v4);
    this->m_Task[63].fp[1] = *(char **)((char *)&this->m_nProperAction + v4);
    this->m_Task[63].fp[2] = *(char **)((char *)&this->m_OBBox + v4);
    v5 = *(float *)this->m_Task[63].fp - this->m_Task[62].fTemp;
    *(float *)&v29 = *(float *)&this->m_Task[63].fp[1] - this->m_Task[62].fTemp2;
    v6 = *(float *)&this->m_Task[63].fp[2] - *(float *)&this->m_Task[62].dwID;
    g_nCBRoleAttackTable[9] = v29;
    *(float *)&v32 = v6;
    *(float *)&g_nCBRoleAttackTable[8] = v5;
    g_nCBRoleAttackTable[10] = v32;
    v7 = ((gbVec3D *)&g_nCBRoleAttackTable[8])->Length();
    dwMsga = v7;
    if ( v7 < 2.0 )
    {
      LODWORD(this->m_Task[62].fTemp) = this->m_Task[63].fp[0];
      LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
      this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      return 0;
    }
    ((gbVec3D *)&g_nCBRoleAttackTable[8])->Normalize();
    v9 = acos(
           *(float *)&g_nCBRoleAttackTable[6] * *(float *)&g_nCBRoleAttackTable[10]
         + *(float *)&g_nCBRoleAttackTable[5] * *(float *)&g_nCBRoleAttackTable[9]
         + *(float *)&g_nCBRoleAttackTable[4] * *(float *)&g_nCBRoleAttackTable[8]);
    this->m_Task[63].vec1.z = v9;
    if ( *(float *)&g_nCBRoleAttackTable[8] < 0.0 )
      this->m_Task[63].vec1.z = 6.2831855 - v9;
    this->m_Task[63].vec1.z = this->m_Task[63].vec1.z * 57.29578;
    this->m_Task[63].fp[3] = (char *)g_nCBRoleAttackTable[8];
    v10 = dwMsga + dwMsga;
    LODWORD(this->m_Task[63].vec1.x) = g_nCBRoleAttackTable[9];
    LODWORD(this->m_Task[63].vec1.y) = g_nCBRoleAttackTable[10];
    *(float *)&this->m_Task[63].fp[3] = v10 * *(float *)&this->m_Task[63].fp[3];
    this->m_Task[63].vec1.x = v10 * this->m_Task[63].vec1.x;
    this->m_Task[63].vec1.y = v10 * this->m_Task[63].vec1.y;
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 31;
    else
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 52;

    v11 = 0.0;
    *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) = 1;
    this->ClearBadPushTask(0.0099999998);
    m_fBlend = this->m_fBlend;
    this->m_bRun = 1;
    if ( LODWORD(m_fBlend) == 1 )
    {
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(aWe012, 1);
    }
    if ( LODWORD(this->m_fBlend) == 3 )
    {
      v14 = CScreenMode::GetInstance();
      ((CScreenMode *)v14)->AudioSetPosition(aWe013, 1);
    }
  }
  v15 = *(float *)this->m_Task[63].fp - this->m_Task[62].fTemp;
  *(float *)&v30 = *(float *)&this->m_Task[63].fp[1] - this->m_Task[62].fTemp2;
  v16 = *(float *)&this->m_Task[63].fp[2] - *(float *)&this->m_Task[62].dwID;
  g_nCBRoleAttackTable[9] = v30;
  *(float *)&v33 = v16;
  *(float *)&g_nCBRoleAttackTable[8] = v15;
  g_nCBRoleAttackTable[10] = v33;
  if ( LODWORD(v11) == *(_DWORD *)&this->m_Task[63].cmd.bSrcRole[10] )
    *((_DWORD *)&this->_todo_1E8 + 24 * (int)this->m_ThrowCmdData) = 1120403456;
  if ( *(&this->_todo_1E8 + 24 * (int)this->m_ThrowCmdData) > 0.0
    && ((gbVec3D *)&g_nCBRoleAttackTable[8])->Length() > 2.0 )
  {
    m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
    v28 = *(float *)&this->m_Task[63].fp[3] * m_DeltaTime;
    v31 = this->m_Task[63].vec1.x * m_DeltaTime;
    v18 = m_DeltaTime * this->m_Task[63].vec1.y;
    this->m_Task[62].fTemp = v28 + this->m_Task[62].fTemp;
    this->m_Task[62].fTemp2 = v31 + this->m_Task[62].fTemp2;
    *(float *)&this->m_Task[62].dwID = v18 + *(float *)&this->m_Task[62].dwID;
  }
  if ( LODWORD(v11) == *(_DWORD *)&this->m_Task[63].cmd.bDestRole[3]
    && ((gbVec3D *)&g_nCBRoleAttackTable[8])->Length() <= 2.0 )
  {
    *((_DWORD *)&this->_todo_1E8 + 24 * (int)this->m_ThrowCmdData) = -1054867456;
  }
  ((gbVec3D *)&g_nCBRoleAttackTable[8])->Normalize();
  v19 = acos(
          *(float *)&g_nCBRoleAttackTable[6] * *(float *)&g_nCBRoleAttackTable[10]
        + *(float *)&g_nCBRoleAttackTable[5] * *(float *)&g_nCBRoleAttackTable[9]
        + *(float *)&g_nCBRoleAttackTable[4] * *(float *)&g_nCBRoleAttackTable[8]);
  if ( *(float *)&g_nCBRoleAttackTable[8] < 0.0 )
    v19 = 6.2831855 - v19;
  v20 = v19 * 57.29578;
  flt_17ABCD8 = v20;
  if ( fabs(v20 - this->m_Task[63].vec1.z) >= 1.570796370506287 )
  {
    LODWORD(this->m_Task[62].fTemp) = this->m_Task[63].fp[0];
    LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
    this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
    *((_DWORD *)&this->_todo_1E8 + 24 * (int)this->m_ThrowCmdData) = -1054867456;
  }
  if ( LODWORD(v11) == this->m_Task[63].cmd.nSrcRole )
  {
    LODWORD(this->m_Task[62].fTemp) = this->m_Task[63].fp[0];
    LODWORD(this->m_Task[62].fTemp2) = this->m_Task[63].fp[1];
    this->m_Task[62].dwID = (unsigned int)this->m_Task[63].fp[2];
    *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
    v21 = this->m_fBlend;
    this->m_bRun = 0;
    if ( LODWORD(v21) == 1 )
    {
      v22 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v22)->PlaySound(aWe012, v27);
    }
    if ( LODWORD(this->m_fBlend) == 3 )
    {
      v23 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v23)->PlaySound(aWe013, v27);
    }
  }
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
  {
    *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
    v24 = this->m_fBlend;
    this->m_bRun = 0;
    if ( LODWORD(v24) == 1 )
    {
      v25 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v25)->PlaySound(aWe012, v27);
    }
    if ( LODWORD(this->m_fBlend) == 3 )
    {
      v26 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v26)->PlaySound(aWe013, v27);
    }
  }
  return 0;
}

// 0x0050EDA0
int CCBStageRole::CheckPushState(int nVal)
{
  tagCmdData *m_ThrowCmdData; // eax
  void *v5; // [esp+0x0] [ebp-0x4]

  if ( *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend))
      || nVal == this->m_Task[63].cmd.nSrcRole )
    {
      this->ClearBadPushTask(0.0099999998);
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      ((CCBRoleState *)this->m_pRoleState)->SetRoleFlag(LODWORD(this->m_fBlend), 1);
    }
    return 0;
  }
  else
  {
    this->ClearBadPushTask(0.0099999998);
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
    {
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 41;

    }
    m_ThrowCmdData = this->m_ThrowCmdData;
    LODWORD(this->m_Task[63].vec1.z) = this->m_Task[63].cmd.dwCmdKind;
    *(&this->m_bSlotBlocked0 + 96 * (_DWORD)m_ThrowCmdData) = 1;
    todo_408BD0(v5);
    return 0;
  }
}

// 0x0050EE70
int CCBStageRole::OnPhysicalHit(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend))
      || nVal == this->m_Task[63].cmd.nSrcRole )
    {
      this->ClearBadPushTask(0.0099999998);
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
      if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
        this->m_bAlive = 0;
    }
    return 0;
  }
  else
  {
    this->ClearBadPushTask(0.25);
    if ( *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] == 44 )
    {
      (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(this->m_nIndex + 16) + 24))(
        *(_DWORD *)(this->m_nIndex + 16),
        0);
    }
    else if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
    {
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 44;

    }
    *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) = 1;
    todo_408BD0(v4);
    return 0;
  }
}

// 0x0050F200
int CCBStageRole::OnMagicHit(int nVal)
{
  char *v3; // eax
  float v4; // eax
  CScreenMode *Instance; // eax
  void *v7; // [esp+0x0] [ebp-0x4]

  v3 = (char *)this + 96 * (int)this->m_ThrowCmdData;
  if ( v3[506] )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend))
      || nVal == this->m_Task[63].cmd.nSrcRole )
    {
      this->ClearBadPushTask(0.0099999998);
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
    }
    return 0;
  }
  else
  {
    if ( ((CCBSystem *)this->m_pStage->m_pCBSystem->m_pRoleState)->IsMagicSlotMsg((int)(v3 + 444)) )
    {
      *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) = 1;
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
    }
    else
    {
      this->ClearBadPushTask(0.25);
      v4 = *(float *)&this->m_Task[63].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 39;
      this->m_Task[63].vec1.z = v4;

      todo_408BD0(v7);
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(&g_EffMgr, 1);
    }
    *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) = 1;
    return 0;
  }
}

// 0x0050FA20
int CCBStageRole::ClearTaskIfMatch(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) )
  {
    if ( nVal == this->m_Task[63].cmd.nSrcRole )
    {
      this->ClearBadPushTask(0.0099999998);
      *(&this->m_bSlotActive0 + 96 * (int)this->m_ThrowCmdData) = 1;
    }
    return 0;
  }
  else
  {
    this->ClearBadPushTask(0.25);
    *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 49;

    *(&this->m_bSlotBlocked0 + 96 * (int)this->m_ThrowCmdData) = 1;
    todo_408BD0(v4);
    return 0;
  }
}

// 0x00518E10
int CCBStageRole::SetActionVisible(char nActIndex)
{
  char *v2; // ecx

  v2 = this->m_Task[6].fp[1];
  if ( nActIndex )
    return (**(int ( ***)(char *, int))v2)(v2, 1);
  else
    return (**(int ( ***)(char *, _DWORD))v2)(v2, 0);
}

// 0x00521A80
bool CCBStageRole::CheckActionValid(int nVal)
{
  float nVala; // [esp+0xC] [ebp+0x8]

  if ( nVal <= 0 )
    return 0;
  nVala = (double)nVal * 10.24;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  return (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)nVala;
}

// 0x00521B00
CCBStageRole * CCBStageRole::LoadSaveData(int *a2)
{
  CCBStageRole *result; // eax
  int *v4; // ebp
  int *v5; // esi
  bool v6; // cc
  bool v7; // zf
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  char *v14; // [esp+0x10] [ebp-0x18]
  int v15; // [esp+0x14] [ebp-0x14]
  int *v16; // [esp+0x18] [ebp-0x10]
  CCBStageRole *v17; // [esp+0x1C] [ebp-0xC]
  int *v18; // [esp+0x20] [ebp-0x8]
  int v19; // [esp+0x24] [ebp-0x4]
  char *v20; // [esp+0x2C] [ebp+0x4]
v4 = a2 + 58;
  *((_DWORD *)this + 82008) = a2[40462];
  *((_DWORD *)this + 82009) = a2[40463];
  *((_DWORD *)this + 82010) = a2[40464];
  *((_DWORD *)this + 82011) = a2[40465];
  *((_DWORD *)this + 82007) = a2[1];
  v17 = (CCBStageRole *)((char *)this + 8028);
  v16 = a2 + 40458;
  v18 = a2 + 58;
  v14 = (char *)this + 8052;
  v19 = 4;
  do
  {
    v15 = 0;
    if ( a2[6] > 0 )
    {
      v20 = v14;
      do
      {
        v5 = v4;
        v4 += 202;
        qmemcpy(v20, v5, 0x328u);
        v6 = ++v15 < a2[6];
        v20 += 808;
      }
      while ( v6 );
    }
    v17->m_pStage = (CCBStage *)*v16++;
    v4 = v18 + 10100;
    v7 = v19 == 1;
    v17 = (CCBStageRole *)((char *)v17 + 4);
    v14 += 79992;
    v18 += 10100;
    --v19;
  }
  while ( !v7 );
  v8 = *((_DWORD *)this + 82008);
  if ( !v8 )
  {
    this->m_Task[44].cmd.dwItemID = 1;
    LOBYTE(this->m_Task[44].vec1.y) = 1;
    *(_DWORD *)&this->m_Task[46].bValid = 0;
    LOBYTE(this->m_Task[46].fTemp2) = 0;
    goto LABEL_12;
  }
  v9 = v8 - 1;
  if ( !v9 )
  {
    this->m_Task[44].cmd.dwItemID = 0;
    LOBYTE(this->m_Task[44].vec1.y) = 0;
    *(_DWORD *)&this->m_Task[46].bValid = 1;
    LOBYTE(this->m_Task[46].fTemp2) = 1;
LABEL_12:
    *(_DWORD *)&this->m_Task[49].cmd.bSrcRole[2] = 0;
    LOBYTE(this->m_Task[49].cmd.nSrcRole) = 0;
    goto LABEL_13;
  }
  if ( v9 == 1 )
  {
    this->m_Task[44].cmd.dwItemID = 0;
    LOBYTE(this->m_Task[44].vec1.y) = 0;
    *(_DWORD *)&this->m_Task[46].bValid = 0;
    LOBYTE(this->m_Task[46].fTemp2) = 0;
    *(_DWORD *)&this->m_Task[49].cmd.bSrcRole[2] = 1;
    LOBYTE(this->m_Task[49].cmd.nSrcRole) = 1;
  }
LABEL_13:
  v10 = *((_DWORD *)this + 82009);
  if ( !v10 )
  {
    LODWORD(this->m_Task[52].vec1.z) = 1;
    LOBYTE(this->m_Task[52].fp[3]) = 1;
    this->m_Task[54].dwID = 0;
    this->m_Task[54].cmd.bValid = 0;
    goto LABEL_19;
  }
  v11 = v10 - 1;
  if ( !v11 )
  {
    this->m_Task[52].vec1.z = 0.0;
    LOBYTE(this->m_Task[52].fp[3]) = 0;
    this->m_Task[54].dwID = 1;
    this->m_Task[54].cmd.bValid = 1;
LABEL_19:
    this->m_Task[57].cmd.nDestRole = 0;
    LOBYTE(this->m_Task[57].cmd.dwCmdKind) = 0;
    goto LABEL_20;
  }
  if ( v11 == 1 )
  {
    this->m_Task[52].vec1.z = 0.0;
    LOBYTE(this->m_Task[52].fp[3]) = 0;
    this->m_Task[54].dwID = 0;
    this->m_Task[54].cmd.bValid = 0;
    this->m_Task[57].cmd.nDestRole = 1;
    LOBYTE(this->m_Task[57].cmd.dwCmdKind) = 1;
  }
LABEL_20:
  v12 = *((_DWORD *)this + 82010);
  if ( !v12 )
  {
    LODWORD(this->m_Task[60].vec1.x) = 1;
    LOBYTE(this->m_Task[60].fp[1]) = 1;
    this->m_Task[62].fTemp = 0.0;
    this->m_Task[62].cmd.bDestRole[3] = 0;
    goto LABEL_26;
  }
  v13 = v12 - 1;
  if ( !v13 )
  {
    this->m_Task[60].vec1.x = 0.0;
    LOBYTE(this->m_Task[60].fp[1]) = 0;
    LODWORD(this->m_Task[62].fTemp) = 1;
    this->m_Task[62].cmd.bDestRole[3] = 1;
LABEL_26:
    this->m_dwAniFlagSJump = 0;
    LOBYTE(this->m_dwAniFlagFlydown) = 0;
    goto LABEL_27;
  }
  if ( v13 == 1 )
  {
    this->m_Task[60].vec1.x = 0.0;
    LOBYTE(this->m_Task[60].fp[1]) = 0;
    this->m_Task[62].fTemp = 0.0;
    this->m_Task[62].cmd.bDestRole[3] = 0;
    this->m_dwAniFlagSJump = 1;
    LOBYTE(this->m_dwAniFlagFlydown) = 1;
  }
LABEL_27:
  switch ( *((_DWORD *)this + 82011) )
  {
    case 0:
      *((_DWORD *)this + 1774) = 0;
      *((_BYTE *)this + 7084) = 0;
      *((_DWORD *)this + 1836) = 0;
      *((_BYTE *)this + 7332) = 0;
      *((_DWORD *)this + 1898) = 0;
      *((_BYTE *)this + 7580) = 0;
      *((_DWORD *)this + 1960) = 1;
      *((_BYTE *)this + 7828) = 1;
      break;
    case 1:
      *((_DWORD *)this + 1774) = 1;
      *((_BYTE *)this + 7084) = 1;
      *((_DWORD *)this + 1836) = 0;
      *((_BYTE *)this + 7332) = 0;
      goto LABEL_30;
    case 2:
      *((_DWORD *)this + 1774) = 0;
      *((_BYTE *)this + 7084) = 0;
      *((_DWORD *)this + 1836) = 1;
      *((_BYTE *)this + 7332) = 1;
LABEL_30:
      *((_DWORD *)this + 1898) = 0;
      *((_BYTE *)this + 7580) = 0;
      *((_DWORD *)this + 1960) = 0;
      *((_BYTE *)this + 7828) = 0;
      break;
    case 3:
      *((_DWORD *)this + 1774) = 0;
      *((_BYTE *)this + 7084) = 0;
      *((_DWORD *)this + 1836) = 0;
      *((_BYTE *)this + 7332) = 0;
      *((_DWORD *)this + 1898) = 1;
      *((_BYTE *)this + 7580) = 1;
      *((_DWORD *)this + 1960) = 0;
      *((_BYTE *)this + 7828) = 0;
      break;
    default:
      return result;
  }
  return result;
}

// 0x00521E60
int CCBStageRole::DispatchUpdate(unsigned __int8 nFlag)
{
  (*(void ( **)(tagRoleTask *, _DWORD))this->m_Task[33].fp[0])(&this->m_Task[33], nFlag);
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_Task[35].cmd.bSrcRole[10])(
    &this->m_Task[35].cmd.bSrcRole[10],
    nFlag);
  (*(void ( **)(gbVec3D *, _DWORD))LODWORD(this->m_Task[38].vec1.x))(&this->m_Task[38].vec1, nFlag);
  return (*(int ( **)(float *, _DWORD))LODWORD(this->m_Task[40].fTemp))(&this->m_Task[40].fTemp, nFlag);
}

// 0x00521EB0
int CCBStageRole::DispatchUpdate(unsigned __int8 nFlag)
{
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_Task[43].cmd.bSrcRole[2])(
    &this->m_Task[43].cmd.bSrcRole[2],
    nFlag);
  (*(void ( **)(char **, _DWORD))this->m_Task[46].fp[2])(&this->m_Task[46].fp[2], nFlag);
  return (**(int ( ***)(_BYTE *, _DWORD))&this->m_Task[48].cmd.bDestRole[7])(
           &this->m_Task[48].cmd.bDestRole[7],
           nFlag);
}

// 0x00521EF0
int CCBStageRole::DispatchUpdate(unsigned __int8 nFlag)
{
  (*(void ( **)(int *, _DWORD))this->m_Task[51].cmd.nDestRole)(
    &this->m_Task[51].cmd.nDestRole,
    nFlag);
  (*(void ( **)(tagRoleTask *, _DWORD))this->m_Task[54].fp[0])(&this->m_Task[54], nFlag);
  return (**(int ( ***)(_BYTE *, _DWORD))&this->m_Task[56].cmd.bSrcRole[10])(
           &this->m_Task[56].cmd.bSrcRole[10],
           nFlag);
}

// 0x00521F30
int CCBStageRole::DispatchUpdateAll(unsigned __int8 nFlag)
{
  (*(void ( **)(unsigned int *, _DWORD))this->m_Task[59].cmd.dwItemID)(
    &this->m_Task[59].cmd.dwItemID,
    nFlag);
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_Task[61].bValid)(&this->m_Task[61].bValid, nFlag);
  return (*(int ( **)(gbVec3D *, _DWORD))LODWORD(this->m_vecRunTarget.x))(&this->m_vecRunTarget, nFlag);
}

// 0x00521F70
int CCBStageRole::DispatchUpdate(unsigned __int8 nFlag)
{
  (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, nFlag);
  (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, nFlag);
  (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, nFlag);
  return (**((int ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, nFlag);
}

// 0x00522030
CCBStageRole::CCBStageRole()
{
  float *p_m_fRightWeapon; // esi
  int v3; // ebp
  void *v4; // edi

  LOBYTE(this->m_pStage) = 0;
  ctor_0x431870((int *)&this->m_pRoleState);
  this->m_fLeftWeapon = 0.0;
  p_m_fRightWeapon = &this->m_fRightWeapon;
  v3 = 5;
  do
  {
    v4 = p_m_fRightWeapon + 6;
    ArraySort((int)(p_m_fRightWeapon + 6), 48, 4, 0 /* TODO: (int)CCBStageRole::ClearRoleState */);
    *(_BYTE *)p_m_fRightWeapon = 0;
    *((_BYTE *)p_m_fRightWeapon + 1) = 0;
    *((_BYTE *)p_m_fRightWeapon + 2) = 0;
    *((_BYTE *)p_m_fRightWeapon + 3) = 0;
    *((_BYTE *)p_m_fRightWeapon + 4) = 0;
    *((_BYTE *)p_m_fRightWeapon + 5) = 0;
    *((_BYTE *)p_m_fRightWeapon + 6) = 0;
    p_m_fRightWeapon[2] = 1.0;
    p_m_fRightWeapon[3] = 0.0;
    p_m_fRightWeapon[4] = 0.0;
    p_m_fRightWeapon[5] = 0.0;
    p_m_fRightWeapon[54] = 0.0;
    p_m_fRightWeapon += 55;
    --v3;
    memset(v4, 0, 0xC0u);
  }
  while ( v3 );
  this;
}

// 0x005220E0
int * CCBStageRole::ClearRoleState()
{
  int *result; // eax
  char *v2; // ecx
  _DWORD *v3; // esi

  result = (int *)this;
  this->m_pStage = 0;
  this->m_pRoleState = 0;
  *(_DWORD *)this->m_sLastRole = 0;
  v2 = &this->m_sLastRole[4];
  *(_DWORD *)v2 = 0;
  *((_DWORD *)v2 + 1) = 0;
  *((_DWORD *)v2 + 2) = 0;
  v3 = v2 + 12;
  v2 += 24;
  *v3 = 0;
  v3[1] = 0;
  v3[2] = 0;
  *(_DWORD *)v2 = 0;
  *((_DWORD *)v2 + 1) = 0;
  *((_DWORD *)v2 + 2) = 0;
  return result;
}

// 0x00522120
void CCBStageRole::CleanupScript()
{
  ((PalScript *)&this->m_pRoleState)->Cleanup();
}

// 0x00523090
int CCBStageRole::GetWeaponSlotPtr(int nVal)
{
  if ( nVal < 5 )
    return (int)(&this->m_fRightWeapon + 55 * nVal);
  else
    return 0;
}

// 0x0053E310
void CCBStageRole::PlaySound(char *name, int nVal)
{
  unsigned int v4; // ebp
  unsigned int v5; // kr08_4
  unsigned int v6; // ebp
  int i; // esi
  int j; // edi
  char v9; // al
  int nVal2; // [esp+0x4] [ebp-0x20] BYREF
  char *v11; // [esp+0x8] [ebp-0x1C]
  unsigned int v12; // [esp+0xC] [ebp-0x18]
  int v13; // [esp+0x14] [ebp-0x10]
  int v14; // [esp+0x20] [ebp-0x4]

  if ( (g_dwGameFlags & 1) != 0 )
  {
    LOBYTE(nVal2) = (_BYTE)name;
    ((std *)0)->string::_Tidy();
    v14 = 0;
    v4 = strlen(g_szSceneUIText);
    if ( ((SceneObj *)&nVal2)->UpdateAutoDelete(v4) )
    {
      qmemcpy(v11, g_szSceneUIText, v4);
      ((std *)v4)->string::_Eos();
    }
    v13 = 0;
    v5 = strlen(name) + 1;
    v6 = v5 - 1;
    v14 = 1;
    if ( ((SceneObj *)&nVal2)->UpdateAutoDelete(v5 - 1) )
    {
      qmemcpy(v11, name, v6);
      v12 = v5 - 1;
      v11[v6] = 0;
    }
    for ( i = *(_DWORD *)&this->m_Task[2].cmd.bDestRole[7]; i != *(_DWORD *)&this->m_Task[2].cmd.bValid; i += 20 )
    {
      for ( j = *(_DWORD *)&this->m_Task[2].cmd.bValid; i != j; i += 20 )
      {
        if ( ((CScreenMode *)i)->GetByteParam((int)&nVal2) )
          break;
      }
      if ( i == *(_DWORD *)&this->m_Task[2].cmd.bValid )
        break;
      if ( ((gbSound2DNode *)*(gbSound2DNode **)(i + 16))->IsPlaying() )
      {
        ((gbSound2DNode *)*(gbSound2DNode **)(i + 16))->Stop();
        break;
      }
    }
    if ( v11 )
    {
      v9 = *(v11 - 1);
      if ( !v9 || v9 == -1 )
        operator delete(v11 - 1);
      else
        *(v11 - 1) = v9 - 1;
    }
  }
}

// 0x0053E9C0
unsigned int CCBStageRole::PauseSound()
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  int v5; // ecx

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = *(_DWORD *)&this->m_Task[2].cmd.bDestRole[7];
    if ( !result )
      break;
    v5 = *(_DWORD *)&this->m_Task[2].cmd.bValid - result;
    result = (unsigned int)((unsigned __int64)(1717986919LL * v5) >> 32) >> 31;
    if ( v1 >= v5 / 20 )
      break;
    ((gbSound2DNode *)*(gbSound2DNode **)(*(_DWORD *)&this->m_Task[2].cmd.bDestRole[7] + i + 16))->Pause();
    ++v1;
  }
  return result;
}

// 0x0053EA10
unsigned int CCBStageRole::ResumeSound()
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  int v5; // ecx

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = *(_DWORD *)&this->m_Task[2].cmd.bDestRole[7];
    if ( !result )
      break;
    v5 = *(_DWORD *)&this->m_Task[2].cmd.bValid - result;
    result = (unsigned int)((unsigned __int64)(1717986919LL * v5) >> 32) >> 31;
    if ( v1 >= v5 / 20 )
      break;
    ((gbSound2DNode *)*(gbSound2DNode **)(*(_DWORD *)&this->m_Task[2].cmd.bDestRole[7] + i + 16))->Resume();
    ++v1;
  }
  return result;
}
