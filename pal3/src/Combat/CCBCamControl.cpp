#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBCamControl.h"

// Forward declarations for unnamed functions
int sub_445E50(int a2); // from annotations
int sub_4E9750(...);
int sub_4EB6F0(...);
int sub_4EB720(...);
int sub_4EB8D0(...);
int todo_408BD0(...);

double EditBox_GetFloat(HWND hWnd); // from annotations
int EditBox_GetInt(HWND hWnd); // from annotations
BOOL EditBox_IsModified(HWND hWnd); // from annotations
LRESULT EditBox_SetFloat(HWND hWnd, float fValue); // from annotations
LRESULT EditBox_SetInt(HWND hWnd, int nValue); // from annotations
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations

// Unnamed globals (extern)
extern const char asc_5D8C3C[];
extern char byte_5967B0[3];
extern int dword_17A7B54;
extern char unk_5D8B6C;

// 0x00449C20
void CCBCamControl::Render()
{
  char *v2; // esi
  int v3; // edi
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0xC]

  v2 = (char *)&this->_embed_gbVolModNode_EC + 372;
  v3 = 38;
  do
  {
    (*(void ( **)(char *))(*(_DWORD *)v2 + 4))(v2);
    v2 += 476;
    --v3;
  }
  while ( v3 );
  ((CCBControlWindow *)this)->Render(v4);
}

// 0x0048E600
int CCBCamControl::ProcessRenderQueue()
{
  int v1; // esi
  int v2; // edi
  int v3; // eax
  RenderTarget *v4; // esi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int result; // eax
  int nScaleY; // [esp+0x0] [ebp-0x24]
  int nScaleYa; // [esp+0x0] [ebp-0x24]
  int v12; // [esp+0x4] [ebp-0x20]
  int v13; // [esp+0x18] [ebp-0xC]
  int fXa; // [esp+0x1C] [ebp-0x8]
  float fX; // [esp+0x1C] [ebp-0x8]
  float fY; // [esp+0x20] [ebp-0x4]

  v1 = *(&this->m_nCurCamIdx + 74349);
  v2 = *(&this->m_nCurCamIdx + 74351) - v1;
  v3 = v1 + v2 / 2;
  v4 = (RenderTarget *)(&this->m_nCurCamIdx + 60041);
  fXa = v3;
  v5 = *(&this->m_nCurCamIdx + 74350);
  v6 = *(&this->m_nCurCamIdx + 74352) - v5;
  v13 = 98;
  fY = (float)v5;
  fX = (float)fXa;
  do
  {
    ((RenderTarget *)v4)->LoadTexture(szFilename);
    ((RenderTarget *)v4)->SetSize(32);
    v12 = rand() % 10 + 252;
    nScaleY = rand() % 10 + 36;
    v7 = rand();
    ((RenderTarget *)v4)->SetColor(v7 % 10 - 37, nScaleY, v12);
    v8 = rand();
    ((RenderTarget *)v4)->SetAlpha(v8 % 135 + 120);
    ((RenderTarget *)v4)->SetField084();
    ((RenderTarget *)v4)->SetState();
    ((RenderTarget *)v4)->UpdateTransform(fX, fY);
    ((RenderTarget *)v4)->CalcRenderDimensions(v2, v6);
    ((RenderTarget *)v4)->SetOffset(1092616192);
    rand();
    *(float *)&nScaleYa = (float)(rand() % 8 + 2);
    ((RenderTarget *)v4)->SetScale(nScaleYa);
    ((RenderTarget *)v4)->SetVisible(1);
    v4 = (RenderTarget *)((char *)v4 + 584);
    result = --v13;
  }
  while ( v13 );
  return result;
}

// 0x004A9ED0
int CCBCamControl::ShowAllSlots(int nVal)
{
  int v3; // ebx
  int *v4; // edi
  int result; // eax

  v3 = 5;
  v4 = &this->m_nCurCamIdx + 93462;
  do
  {
    sub_445E50((int)v4);
    v4 += 86;
    --v3;
  }
  while ( v3 );
  result = sub_445E50((int)&this->m_CamEntries[86 * nVal + 95256]);
  switch ( nVal )
  {
    case 0:
      ((UIListBox *)this)->_todo_4A9870();
      (**((void ( ***)(int *, int))&this->m_nCurCamIdx + 95091))(&this->m_nCurCamIdx + 95091, 1);
      ((UIListBox *)(&this->m_nCurCamIdx + 95091))->GetItem();
      ((UIListBox *)(&this->m_nCurCamIdx + 95091))->GetItem();
      ((UIListBox *)(&this->m_nCurCamIdx + 95393))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95393))(&this->m_nCurCamIdx + 95393, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95695))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95695))(&this->m_nCurCamIdx + 95695, 0);
      goto LABEL_7;
    case 1:
      ((UIListBox *)(&this->m_nCurCamIdx + 95091))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95091))(&this->m_nCurCamIdx + 95091, 0);
      ((UIListBox *)this)->_todo_4A9870();
      (**((void ( ***)(int *, int))&this->m_nCurCamIdx + 95393))(&this->m_nCurCamIdx + 95393, 1);
      ((UIListBox *)(&this->m_nCurCamIdx + 95393))->GetItem();
      ((UIListBox *)(&this->m_nCurCamIdx + 95393))->GetItem();
      ((UIListBox *)(&this->m_nCurCamIdx + 95695))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95695))(&this->m_nCurCamIdx + 95695, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95997))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95997))(&this->m_nCurCamIdx + 95997, 0);
      goto LABEL_9;
    case 2:
      ((UIListBox *)(&this->m_nCurCamIdx + 95091))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95091))(&this->m_nCurCamIdx + 95091, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95393))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95393))(&this->m_nCurCamIdx + 95393, 0);
      ((UIListBox *)this)->_todo_4A9870();
      (**((void ( ***)(int *, int))&this->m_nCurCamIdx + 95695))(&this->m_nCurCamIdx + 95695, 1);
      ((UIListBox *)(&this->m_nCurCamIdx + 95695))->GetItem();
      ((UIListBox *)(&this->m_nCurCamIdx + 95695))->GetItem();
LABEL_7:
      ((UIListBox *)(&this->m_nCurCamIdx + 95997))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95997))(&this->m_nCurCamIdx + 95997, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 96299))->ClearAll();
      result = (**((int ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 96299))(
                 &this->m_nCurCamIdx + 96299,
                 0);
      *(&this->m_nCurCamIdx + 3057) = nVal;
      return result;
    case 3:
      ((UIListBox *)(&this->m_nCurCamIdx + 95091))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95091))(&this->m_nCurCamIdx + 95091, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95393))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95393))(&this->m_nCurCamIdx + 95393, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95695))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95695))(&this->m_nCurCamIdx + 95695, 0);
      ((UIListBox *)this)->_todo_4A9870();
      (**((void ( ***)(int *, int))&this->m_nCurCamIdx + 95997))(&this->m_nCurCamIdx + 95997, 1);
      ((UIListBox *)(&this->m_nCurCamIdx + 95997))->GetItem();
      ((UIListBox *)(&this->m_nCurCamIdx + 95997))->GetItem();
LABEL_9:
      ((UIListBox *)(&this->m_nCurCamIdx + 96299))->ClearAll();
      result = (**((int ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 96299))(
                 &this->m_nCurCamIdx + 96299,
                 0);
      *(&this->m_nCurCamIdx + 3057) = nVal;
      return result;
    case 4:
      ((UIListBox *)(&this->m_nCurCamIdx + 95091))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95091))(&this->m_nCurCamIdx + 95091, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95393))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95393))(&this->m_nCurCamIdx + 95393, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95695))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95695))(&this->m_nCurCamIdx + 95695, 0);
      ((UIListBox *)(&this->m_nCurCamIdx + 95997))->ClearAll();
      (**((void ( ***)(int *, _DWORD))&this->m_nCurCamIdx + 95997))(&this->m_nCurCamIdx + 95997, 0);
      ((UIListBox *)this)->_todo_4A9870();
      (**((void ( ***)(int *, int))&this->m_nCurCamIdx + 96299))(&this->m_nCurCamIdx + 96299, 1);
      ((UIListBox *)(&this->m_nCurCamIdx + 96299))->GetItem();
      result = ((UIListBox *)(&this->m_nCurCamIdx + 96299))->GetItem();
      goto LABEL_11;
    default:
LABEL_11:
      *(&this->m_nCurCamIdx + 3057) = nVal;
      return result;
  }
}

// 0x004E9750
int CCBCamControl::sub_4E9750(HWND hDlg)
{
  HWND DlgItem; // ebp
  LPARAM v3; // edi
  char *v4; // esi
  char v5; // al
  int result; // eax
  WPARAM v7; // edx
  LPARAM lParam[10]; // [esp+0x14] [ebp-0x28] BYREF

  DlgItem = GetDlgItem(hDlg, 1153);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  v3 = 0;
  v4 = &g_EffTable[4];
  do
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[1] = v3;
    lParam[2] = 0;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v3);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    v5 = v4[208];
    lParam[2] = 1;
    if ( v5 )
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, v4);
    else
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &unk_5D8B6C);
    result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    v4 += 280;
    ++v3;
  }
  while ( (int)v4 < (int)&dword_17A7B54 );
  v7 = this->m_CamEntries[1405];
  if ( v7 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[3] = 3;
    lParam[4] = 3;
    lParam[1] = v7;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    SendMessageA(DlgItem, 0x102Bu, v7, (LPARAM)lParam);
    return SendMessageA(DlgItem, 0x1013u, this->m_CamEntries[1405], 0);
  }
  return result;
}

// 0x004EB6F0
void CCBCamControl::sub_4EB6F0(HWND hDlg)
{
  this->sub_4EB720(hDlg);
  this->sub_4EB8D0(hDlg);
  this->ShowCameraDialog(hDlg);
}

// 0x004EB720
LRESULT CCBCamControl::sub_4EB720(HWND hDlg)
{
  HWND DlgItem; // esi
  LPARAM v4; // eax
  int *v5; // edi
  LRESULT result; // eax
  CCCTData *m_CCT; // edx
  int v8; // eax
  int EffByID; // eax
  int EffSlot; // eax
  WPARAM v11; // edx
  LRESULT v12; // [esp+0x10] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x14] [ebp-0x28] BYREF
  HWND hDlga; // [esp+0x40] [ebp+0x4]

  DlgItem = GetDlgItem(hDlg, 1276);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  v4 = 0;
  v5 = &g_nSaveSlot1;
  for ( hDlga = 0; ; v4 = (LPARAM)hDlga )
  {
    v12 = *(v5 - 1);
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[1] = v4;
    lParam[2] = 0;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v4);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    lParam[2] = 1;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v12);
    SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    result = v12;
    if ( v12 )
    {
      m_CCT = this->m_CCT;
      v8 = *v5;
      lParam[2] = 2;
      EffByID = ((CEffMgr *)LODWORD(m_CCT->m_Pool[0].StartPos.yaw))->FindEffByID(v8);
      EffSlot = ((CEffMgr *)LODWORD(this->m_CCT->m_Pool[0].StartPos.yaw))->FindEffSlot(*(_DWORD *)&g_EffTable[280 * EffByID]);
      sprintf(
        (char *const)&g_RoleSystemCombat.m_teamSlots[264],
        byte_5967B0,
        LODWORD(this->m_CCT->m_Pool[0].StartPos.yaw) + 72 * EffSlot + 28);
      result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
    v5 += 3985;
    hDlga = (HWND)((char *)hDlga + 1);
    if ( (int)v5 >= (int)&g_EffTable[4] )
      break;
  }
  v11 = this->m_CamEntries[1793];
  if ( v11 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[1] = v11;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[3] = 3;
    lParam[4] = 3;
    SendMessageA(DlgItem, 0x102Bu, v11, (LPARAM)lParam);
    return SendMessageA(DlgItem, 0x1013u, this->m_CamEntries[1793], 0);
  }
  return result;
}

// 0x004EB8D0
LRESULT CCBCamControl::sub_4EB8D0(HWND hDlg)
{
  HWND DlgItem; // ebp
  signed int v3; // esi
  int PropertyByIndex; // eax
  _BYTE *RoleNum; // edi
  signed int v6; // edi
  int ItemID; // edi
  char v8; // al
  LPARAM v9; // edi
  int v10; // ecx
  int v11; // eax
  LRESULT result; // eax
  WPARAM m_nCurCamIdx; // edx
// [IDA_MISID]   Concurrency::IThreadProxy *index; // [esp+0x14] [ebp-0x38]
  signed int indexa; // [esp+0x14] [ebp-0x38]
  CCBCamControl *SkillID; // [esp+0x18] [ebp-0x34]
  CCBCamControl *v18; // [esp+0x18] [ebp-0x34]
  int ExecutionResourceId; // [esp+0x1C] [ebp-0x30]
  int RoleBySlot; // [esp+0x1C] [ebp-0x30]
  int ItemNum; // [esp+0x20] [ebp-0x2C]
  int SkillNum; // [esp+0x20] [ebp-0x2C]
  char *v23; // [esp+0x20] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x24] [ebp-0x28] BYREF
  HWND hDlga; // [esp+0x50] [ebp+0x4]
  HWND hDlgb; // [esp+0x50] [ebp+0x4]
  HWND hDlgc; // [esp+0x50] [ebp+0x4]
  HWND hDlgd; // [esp+0x50] [ebp+0x4]

  DlgItem = GetDlgItem(hDlg, 1278);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
// [IDA_MISID]   ExecutionResourceId = ((Concurrency *)&g_pGDB)->details::VirtualProcessor::GetExecutionResourceId();
// [IDA_MISID]   index = ((Concurrency *)&g_pGDB)->details::InternalContextBase::GetProxy();
  v3 = 0;
  SkillID = (CCBCamControl *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillID();
  if ( ExecutionResourceId > 0 )
  {
    hDlga = (HWND)&this->m_CamEntries[1409];
    do
    {
      PropertyByIndex = ((NPC *)&g_pGDB)->GetPropertyByIndex(v3);
      *(_DWORD *)hDlga = PropertyByIndex;
      RoleNum = (_BYTE *)((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(PropertyByIndex);
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      lParam[1] = v3;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v3);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      if ( RoleNum[572] || RoleNum[573] || RoleNum[574] || RoleNum[575] || RoleNum[576] )
      {
        lParam[2] = 1;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, RoleNum + 28);
      }
      else
      {
        lParam[2] = 1;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], asc_5D8C3C, RoleNum + 28);
      }
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v3;
      ++hDlga;
    }
    while ( v3 < ExecutionResourceId );
  }
  v6 = 0;
  if ( (int)index > 0 )
  {
    hDlgb = (HWND)&this->m_CamEntries[v3 + 1409];
    do
    {
      RoleBySlot = ((UIAnimateCtrl *)&g_pGDB)->GetRoleBySlot(v6);
      ItemNum = ((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(RoleBySlot);
      *(_DWORD *)hDlgb = RoleBySlot;
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      lParam[1] = v3;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v3);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, ItemNum);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v3;
      ++v6;
      ++hDlgb;
    }
    while ( v6 < (int)index );
  }
  indexa = 0;
  if ( (int)SkillID > 0 )
  {
    hDlgc = (HWND)&this->m_CamEntries[v3 + 1409];
    do
    {
      ItemID = ((PAL_GDB *)&g_pGDB)->GetItemID(indexa);
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(ItemID);
      v8 = *(_BYTE *)(SkillNum + 612);
      if ( v8 == 1 || v8 == 2 )
      {
        *(_DWORD *)hDlgc = ItemID;
        lParam[0] = 1;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[1] = v3;
        lParam[2] = 0;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v3);
        SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
        lParam[2] = 1;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, SkillNum + 4);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        ++v3;
        ++hDlgc;
      }
      ++indexa;
    }
    while ( indexa < (int)SkillID );
  }
  v9 = 0;
  v18 = *(CCBCamControl **)(*(_DWORD *)&this->m_CCT->m_Pool[0].bValid + 76);
  if ( v3 > 0 )
  {
    hDlgd = (HWND)&this->m_CamEntries[1409];
    do
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      lParam[1] = v9;
      v10 = *(_DWORD *)hDlgd;
      lParam[2] = 2;
      ((CCBCamControl *)v18)->KeepCurCam(v10);
      v23 = (char *)v18 + 60 * v11;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], *((_DWORD *)v23 + 612));
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 3;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], *((_DWORD *)v23 + 619));
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v9;
      ++hDlgd;
    }
    while ( v9 < v3 );
  }
  result = (LRESULT)this;
  m_nCurCamIdx = this->m_nCurCamIdx;
  if ( m_nCurCamIdx != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[1] = m_nCurCamIdx;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[3] = 3;
    lParam[4] = 3;
    SendMessageA(DlgItem, 0x102Bu, m_nCurCamIdx, (LPARAM)lParam);
    return SendMessageA(DlgItem, 0x1013u, this->m_nCurCamIdx, 0);
  }
  return result;
}

// 0x004EBD30
void CCBCamControl::ShowCameraDialog(HWND hDlg)
{
  HWND DlgItem; // ebp
  HWND v5; // edi
  CCBCamControl *v6; // esi
  int v7; // eax
  int v8; // edx
  int v9; // esi
  LRESULT v10; // eax
  BOOL v11; // edx
  BOOL v12; // ecx
  LRESULT Only; // eax
  BOOL v14; // edx
  BOOL v15; // ecx
  LRESULT v16; // eax
  BOOL v17; // edx
  HWND v18; // [esp+0x4] [ebp-0x44]
  HWND v19; // [esp+0x8] [ebp-0x40]
  HWND hWnd; // [esp+0xC] [ebp-0x3C]
  HWND v21; // [esp+0x10] [ebp-0x38]
  HWND v22; // [esp+0x14] [ebp-0x34]
  HWND v23; // [esp+0x18] [ebp-0x30]
  HWND v24; // [esp+0x1C] [ebp-0x2C]
  HWND v25; // [esp+0x20] [ebp-0x28]
  HWND v26; // [esp+0x24] [ebp-0x24]
  HWND v27; // [esp+0x28] [ebp-0x20]
  HWND v28; // [esp+0x2C] [ebp-0x1C]
  HWND v29; // [esp+0x30] [ebp-0x18]
  HWND v30; // [esp+0x34] [ebp-0x14]
  HWND v31; // [esp+0x38] [ebp-0x10]
  HWND v32; // [esp+0x3C] [ebp-0xC]
  HWND v33; // [esp+0x40] [ebp-0x8]
  HWND v34; // [esp+0x44] [ebp-0x4]
  HWND hDlga; // [esp+0x4C] [ebp+0x4]

  if ( this->m_nCurCamIdx != -1 )
  {
    DlgItem = GetDlgItem(hDlg, 1208);
    v18 = GetDlgItem(hDlg, 1279);
    hWnd = GetDlgItem(hDlg, 1281);
    v22 = GetDlgItem(hDlg, 1280);
    v24 = GetDlgItem(hDlg, 1283);
    v26 = GetDlgItem(hDlg, 1282);
    v28 = GetDlgItem(hDlg, 1209);
    v29 = GetDlgItem(hDlg, 1214);
    v30 = GetDlgItem(hDlg, 1215);
    v34 = GetDlgItem(hDlg, 1216);
    hDlga = GetDlgItem(hDlg, 1218);
    v19 = GetDlgItem(hDlg, 1217);
    v21 = GetDlgItem(hDlg, 1285);
    v23 = GetDlgItem(hDlg, 1284);
    v25 = GetDlgItem(hDlg, 1287);
    v27 = GetDlgItem(hDlg, 1286);
    v31 = GetDlgItem(hDlg, 1219);
    v32 = GetDlgItem(hDlg, 1220);
    v33 = GetDlgItem(hDlg, 1221);
    v5 = GetDlgItem(hDlg, 1222);
    v6 = *(CCBCamControl **)(*(_DWORD *)&this->m_CCT->m_Pool[0].bValid + 76);
    ((CCBCamControl *)v6)->KeepCurCam(this->m_CamEntries[this->m_nCurCamIdx + 1409]);
    v7 *= 3;
    v8 = v6->m_CamEntries[5 * v7 + 1];
    v9 = (int)&v6->m_CamEntries[5 * v7];
    EditBox_SetInt(DlgItem, v8);
    EditBox_SetInt(hDlga, *(_DWORD *)(v9 + 32));
    EditBox_SetFloat(v18, *(float *)(v9 + 24));
    v10 = EditBox_SetFloat(v19, *(float *)(v9 + 52));
    LOBYTE(v10) = *(_BYTE *)(v9 + 8);
    EditBox_SetReadOnly(hWnd, v10);
    LOBYTE(v11) = *(_BYTE *)(v9 + 36);
    EditBox_SetReadOnly(v21, v11);
    LOBYTE(v12) = *(_BYTE *)(v9 + 9);
    Only = EditBox_SetReadOnly(v22, v12);
    LOBYTE(Only) = *(_BYTE *)(v9 + 37);
    EditBox_SetReadOnly(v23, Only);
    LOBYTE(v14) = *(_BYTE *)(v9 + 10);
    EditBox_SetReadOnly(v24, v14);
    LOBYTE(v15) = *(_BYTE *)(v9 + 38);
    v16 = EditBox_SetReadOnly(v25, v15);
    LOBYTE(v16) = *(_BYTE *)(v9 + 11);
    EditBox_SetReadOnly(v26, v16);
    LOBYTE(v17) = *(_BYTE *)(v9 + 39);
    EditBox_SetReadOnly(v27, v17);
    EditBox_SetFloat(v28, *(float *)(v9 + 12));
    EditBox_SetFloat(v29, *(float *)(v9 + 16));
    EditBox_SetFloat(v30, *(float *)(v9 + 20));
    EditBox_SetFloat(v31, *(float *)(v9 + 40));
    EditBox_SetFloat(v32, *(float *)(v9 + 44));
    EditBox_SetFloat(v33, *(float *)(v9 + 48));
    EditBox_SetFloat(v34, *(float *)(v9 + 28));
    EditBox_SetFloat(v5, *(float *)(v9 + 56));
  }
}

// 0x004EBF90
void CCBCamControl::ReadCameraDialog(HWND hDlg)
{
  HWND DlgItem; // ebp
  HWND v5; // edi
  CCBCamControl *v6; // esi
  int v7; // eax
  int v8; // esi
  HWND v9; // [esp+0x4] [ebp-0x44]
  HWND v10; // [esp+0x8] [ebp-0x40]
  HWND hWnd; // [esp+0xC] [ebp-0x3C]
  HWND v12; // [esp+0x10] [ebp-0x38]
  HWND v13; // [esp+0x14] [ebp-0x34]
  HWND v14; // [esp+0x18] [ebp-0x30]
  HWND v15; // [esp+0x1C] [ebp-0x2C]
  HWND v16; // [esp+0x20] [ebp-0x28]
  HWND v17; // [esp+0x24] [ebp-0x24]
  HWND v18; // [esp+0x28] [ebp-0x20]
  HWND v19; // [esp+0x2C] [ebp-0x1C]
  HWND v20; // [esp+0x30] [ebp-0x18]
  HWND v21; // [esp+0x34] [ebp-0x14]
  HWND v22; // [esp+0x38] [ebp-0x10]
  HWND v23; // [esp+0x3C] [ebp-0xC]
  HWND v24; // [esp+0x40] [ebp-0x8]
  HWND v25; // [esp+0x44] [ebp-0x4]
  HWND hDlga; // [esp+0x4C] [ebp+0x4]

  if ( this->m_nCurCamIdx != -1 )
  {
    DlgItem = GetDlgItem(hDlg, 1208);
    v9 = GetDlgItem(hDlg, 1279);
    hWnd = GetDlgItem(hDlg, 1281);
    v13 = GetDlgItem(hDlg, 1280);
    v15 = GetDlgItem(hDlg, 1283);
    v17 = GetDlgItem(hDlg, 1282);
    v19 = GetDlgItem(hDlg, 1209);
    v20 = GetDlgItem(hDlg, 1214);
    v21 = GetDlgItem(hDlg, 1215);
    v25 = GetDlgItem(hDlg, 1216);
    hDlga = GetDlgItem(hDlg, 1218);
    v10 = GetDlgItem(hDlg, 1217);
    v12 = GetDlgItem(hDlg, 1285);
    v14 = GetDlgItem(hDlg, 1284);
    v16 = GetDlgItem(hDlg, 1287);
    v18 = GetDlgItem(hDlg, 1286);
    v22 = GetDlgItem(hDlg, 1219);
    v23 = GetDlgItem(hDlg, 1220);
    v24 = GetDlgItem(hDlg, 1221);
    v5 = GetDlgItem(hDlg, 1222);
    v6 = *(CCBCamControl **)(*(_DWORD *)&this->m_CCT->m_Pool[0].bValid + 76);
    ((CCBCamControl *)v6)->KeepCurCam(this->m_CamEntries[this->m_nCurCamIdx + 1409]);
    v8 = (int)&v6->m_CamEntries[15 * v7];
    *(_DWORD *)(v8 + 4) = EditBox_GetInt(DlgItem);
    *(_DWORD *)(v8 + 32) = EditBox_GetInt(hDlga);
    *(float *)(v8 + 24) = EditBox_GetFloat(v9);
    *(float *)(v8 + 52) = EditBox_GetFloat(v10);
    *(_BYTE *)(v8 + 8) = EditBox_IsModified(hWnd);
    *(_BYTE *)(v8 + 36) = EditBox_IsModified(v12);
    *(_BYTE *)(v8 + 9) = EditBox_IsModified(v13);
    *(_BYTE *)(v8 + 37) = EditBox_IsModified(v14);
    *(_BYTE *)(v8 + 10) = EditBox_IsModified(v15);
    *(_BYTE *)(v8 + 38) = EditBox_IsModified(v16);
    *(_BYTE *)(v8 + 11) = EditBox_IsModified(v17);
    *(_BYTE *)(v8 + 39) = EditBox_IsModified(v18);
    *(float *)(v8 + 12) = EditBox_GetFloat(v19);
    *(float *)(v8 + 16) = EditBox_GetFloat(v20);
    *(float *)(v8 + 20) = EditBox_GetFloat(v21);
    *(float *)(v8 + 40) = EditBox_GetFloat(v22);
    *(float *)(v8 + 44) = EditBox_GetFloat(v23);
    *(float *)(v8 + 48) = EditBox_GetFloat(v24);
    *(float *)(v8 + 28) = EditBox_GetFloat(v25);
    *(float *)(v8 + 56) = EditBox_GetFloat(v5);
    *(_DWORD *)v8 = this->m_CamEntries[this->m_nCurCamIdx + 1409];
  }
}

// 0x004FF360
int CCBCamControl::ProcessCamMove(int nVal)
{
  int v3; // eax
  int v4; // ecx
  char *v5; // edi
  unsigned int v6; // eax

  v3 = 658 * *(&this->m_CamCtrlData + 25);
  v4 = v3 * 4 + 80 * *(&this->m_CamCtrlData + 26);
  v5 = (char *)&this->m_CamCtrlData + v4 + 124;
  if ( !*((_BYTE *)&this->m_CamCtrlData + v4 + 165) )
  {
    ((CCBCamControl *)*((CCBCamControl **)&this->m_CamCtrlData + 4))->KeepCurCam(this->m_CamEntries[v3 + 78]);
    *((_DWORD *)v5 + 14) = v6;
    ((CCBCamControl *)*((CCBCamControl **)&this->m_CamCtrlData + 4))->DoLineMove(v6);
    v5[41] = 1;
  }
  *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x005052E0
CCBStageCam * CCBCamControl::SetCamPos(int **pCamParam, int nVal)
{
  CUtil *v4; // eax

  ((CCBStageCam *)this)->ResetViewport();
  this->m_vecSpeed.x = 0.0;
  this->m_vecSpeed.y = 0.0;
  this->m_vecSpeed.z = 0.0;
  this->m_vecNextSpeed.x = 0.0;
  this->m_vecNextSpeed.y = 0.0;
  this->m_vecNextSpeed.z = 0.0;
  this->m_StartPos.x = 0.0;
  this->m_StartPos.y = 0.0;
  this->m_StartPos.z = 0.0;
  this->m_StartPos.yaw = 0.0;
  this->m_StartPos.pit = 0.0;
  this->m_StartPos.rol = 0.0;
  this->m_CurPos.x = 0.0;
  this->m_CurPos.y = 0.0;
  this->m_CurPos.z = 0.0;
  this->m_CurPos.yaw = 0.0;
  this->m_CurPos.pit = 0.0;
  this->m_CurPos.rol = 0.0;
  this->m_vecCurPos.x = 0.0;
  this->m_vecCurPos.y = 0.0;
  this->m_vecCurPos.z = 0.0;
  this->m_vecCircleCenter.x = 0.0;
  this->m_vecCircleCenter.y = 0.0;
  this->m_vecCircleCenter.z = 0.0;
  this->m_vecCircleEnd.x = 0.0;
  this->m_vecCircleEnd.y = 0.0;
  this->m_vecCircleEnd.z = 0.0;
  this->m_pStage = (CCBStage *)pCamParam;
  this->m_pCam = (CCBStageCam *)nVal;
  v4 = (CUtil *)**pCamParam;
  this->m_nCurTask = -1;
  this->m_pUtil = v4;
  return (CCBStageCam *)this;
}

// 0x005054B0
bool CCBCamControl::Init()
{
  gbGeomNode *m_pPointer; // ecx

  m_pPointer = this->m_pPointer;
  if ( m_pPointer )
  {
    (**(void ( ***)(gbGeomNode *, int))m_pPointer)(m_pPointer, 1);
    this->m_pPointer = 0;
  }
  return 1;
}

// 0x005054F0
void CCBCamControl::DoTask()
{
  CCBStage *m_pStage; // eax
  CCBStageCam *m_pCam; // ecx
  double v4; // st7
  CCBStage *v5; // eax
  CCBStageCam *v6; // ecx
  float *ViewTarget; // eax
  float v8; // edx
  double v9; // st7
  char m_bCircleCenterSelected; // al
  double v11; // st7
  double v12; // st6
  float z; // eax
  double v14; // st6
  float v15; // edx
  float pPos; // [esp+0xC] [ebp-0x54] BYREF
  CCBDisplayChain *m_pDisplayChain; // [esp+0x10] [ebp-0x50]
  int v18; // [esp+0x14] [ebp-0x4C]
  struct gbVec3D v19; // [esp+0x18] [ebp-0x48] BYREF
  struct gbVec3D v20; // [esp+0x24] [ebp-0x3C] BYREF
  gbRay v21; // [esp+0x30] [ebp-0x30] BYREF
  _BYTE pTarget[24]; // [esp+0x48] [ebp-0x18] BYREF

  this->m_pCam->m_lastYAW = 0.0;
  if ( this->m_bRunning )
    ((CCCTData *)this)->Init();
  if ( this->m_fQuake <= 0.0 )
  {
    this->m_fQuake = 0.0;
  }
  else
  {
    m_pStage = this->m_pStage;
    pPos = this->m_CurPos.y;
    m_pCam = this->m_pCam;
    v4 = this->m_fQuake - m_pStage->m_pCBSystem->m_DeltaTime * this->m_fQuakeDec;
    this->m_fQuake = v4;
    this->m_CurPos.y = sin(m_pStage->m_pCBSystem->m_fTimeFund * this->m_fQuakeFre) * v4 + this->m_CurPos.y;
    ((CCCTData *)m_pCam)->CCCTData::UpdateCamera((int)&this->m_CurPos);
    ((CameraCtrl *)this->m_pCam)->SetAsCurrent(3);
    this->m_CurPos.y = pPos;
  }
  if ( g_RoleSystemCombat.dwInitParam == (HWND)4 )
  {


    v20.y = 1.0;
    m_pDisplayChain = 0;
    v20.x = 0.0;
    v20.z = 0.0;
    pPos = 1.0;
    v18 = 1065353216;
    v19.y = 0.0;
    v19.x = 1.0;
    v19.z = 1.0;
    memset(&v21, 0, 12);
    v5 = this->m_pStage;
    pPos = *(float *)&v5->m_WPXVariance;
    v6 = this->m_pCam;
    m_pDisplayChain = v5->m_pDisplayChain;
    ViewTarget = (float *)((CameraCtrl *)v6)->GetViewTarget(pTarget, &pPos);
    v8 = *ViewTarget;
    ViewTarget += 3;
    v21.Origin.x = v8;
    v21.Origin.y = *(ViewTarget - 2);
    v21.Origin.z = *(ViewTarget - 1);
    ((gbVec3D *)&v21.Direction)->operator=(ViewTarget);
    v9 = ((gbRay *)&v21)->IntersectPlane(v20, v19);
    m_bCircleCenterSelected = this->m_bCircleCenterSelected;
    v20.x = v21.Direction.x * v9;
    v19.x = v20.x + v21.Origin.x;
    v11 = v9 * v21.Direction.z + v21.Origin.z;
    if ( m_bCircleCenterSelected )
    {
      v12 = (double)*(int *)&g_Input.MouseState[8] * 0.1 + this->m_vecCircleCenter.y;
      this->m_vecCircleCenter.y = v12;
      v20.x = v19.x;
      v20.z = v11;
      z = v20.z;
      this->m_vecCircleCenter.x = v19.x;
      this->m_vecCircleCenter.y = v12;
      this->m_vecCircleCenter.z = z;
    }
    if ( this->m_bCircleEndSelected )
    {
      v14 = (double)*(int *)&g_Input.MouseState[8] * 0.1 + this->m_vecCircleEnd.y;
      this->m_vecCircleEnd.y = v14;
      v20.z = v11;
      v15 = v20.z;
      this->m_vecCircleEnd.x = v19.x;
      this->m_vecCircleEnd.y = v14;
      this->m_vecCircleEnd.z = v15;
    }
  }
}

// 0x00505770
char CCBCamControl::ClearFinishedTask(int nVal)
{
  int v3; // eax

  LOBYTE(v3) = ((CCBStageCam *)this)->IsEditorCamValid(nVal);
  if ( !v3 )
    return 0;
  this->m_bRunning = 1;
  ((CCCTData *)this)->Save(nVal);
  this->m_nCurList = nVal;
  this->m_nCurTask = 0;
  return 1;
}

// 0x00505800
int CCBCamControl::AddTask()
{
  this->m_bRunning = 0;
  this->m_nCurList = -1;
  this->m_nCurTask = -1;
  return -1;
}

// 0x00505820
char CCBCamControl::ProcCamMove()
{
  gbVec3D *p_m_vecCircleCenter; // eax
  gbVec3D *p_m_vecCircleEnd; // ecx
  float z; // eax
  char result; // al
  float pfVal; // [esp+0x4] [ebp-0x18] BYREF
  float y; // [esp+0x8] [ebp-0x14]
  float v8; // [esp+0xC] [ebp-0x10]
  float x; // [esp+0x10] [ebp-0xC] BYREF
  float v10; // [esp+0x14] [ebp-0x8]
  float v11; // [esp+0x18] [ebp-0x4]

  p_m_vecCircleCenter = &this->m_vecCircleCenter;
  pfVal = this->m_vecCircleCenter.x;
  p_m_vecCircleEnd = &this->m_vecCircleEnd;
  y = p_m_vecCircleCenter->y;
  z = p_m_vecCircleCenter->z;
  x = p_m_vecCircleEnd->x;
  v8 = z;
  v10 = p_m_vecCircleEnd->y;
  result = g_Input.KeyInfo[15].PressTime;
  v11 = p_m_vecCircleEnd->z;
  y = 0.0;
  v10 = 0.0;
  if ( g_Input.KeyInfo[15].PressTime == 1 )
  {
    result = ((CCCTData *)this)->Create(&pfVal);
    if ( result )
    {
      this->m_bCircleCenterSelected = 1;
    }
    else
    {
      result = ((CCCTData *)this)->Create(&x);
      if ( result )
      {
        this->m_bCircleEndSelected = 1;
      }
      else
      {
        this->m_bCircleCenterSelected = 0;
        this->m_bCircleEndSelected = 0;
      }
    }
  }
  if ( (g_Input.KeyInfo[15].Data & 0xF) != 1 )
  {
    this->m_bCircleCenterSelected = 0;
    this->m_bCircleEndSelected = 0;
  }
  return result;
}

// 0x005058E0
bool CCBCamControl::SwitchEditorCamPos()
{
  return (*(bool ( **)(gbGeomNode *))(*(_DWORD *)this->m_pPointer + 20))(this->m_pPointer);
}

// 0x005081D0
// attributes: thunk
CCBCamControl::CCBCamControl()
{
}

// 0x005081E0
void CCBCamControl::_CCBCamControl()
{
  *((_QWORD *)&g_CCBCamControlData + 184) = 0x13A00000077LL;
  *((_QWORD *)&g_CCBCamControlData + 185) = 0x2C3000001FELL;
}

// 0x00508220
// attributes: thunk
void CCBCamControl::Reset()
{

}

// 0x00508230
bool CCBCamControl::Create()
{
  *((_QWORD *)&g_CCBCamControlData + 186) = 0x20700000207LL;
  *((_QWORD *)&g_CCBCamControlData + 187) = 0x20700000207LL;
  return 7;
}

// 0x00508270
// attributes: thunk
bool CCBCamControl::Destroy()
{
  return this->Init();
}

// 0x00508280
int CCBCamControl::Init()
{
  *((_QWORD *)&g_CCBCamControlData + 188) = 0x14300000080LL;
  *((_QWORD *)&g_CCBCamControlData + 189) = 0x2CC00000207LL;
  return 716;
}

// 0x005082C0
// attributes: thunk
void CCBCamControl::Update()
{

}

// 0x005082D0
bool CCBCamControl::StartList()
{
  *((_QWORD *)&g_CCBCamControlData + 190) = 0x22100000221LL;
  *((_QWORD *)&g_CCBCamControlData + 191) = 0x22100000221LL;
  return 33;
}

// 0x00508320
void CCBCamControl::StopList()
{
  *((_QWORD *)&g_CCBCamControlData + 192) = 0x13C00000079LL;
  *((_QWORD *)&g_CCBCamControlData + 193) = 0x2C500000200LL;
}

// 0x00508360
// attributes: thunk
void CCBCamControl::HandleInput()
{

}

// 0x00508370
void CCBCamControl::UpdateCircleSet()
{
  *((_QWORD *)&g_CCBCamControlData + 194) = 0x23D0000023DLL;
  *((_QWORD *)&g_CCBCamControlData + 195) = 0x23D0000023DLL;
}

// 0x005083B0
CCBCamControl * CCBCamControl::SetCircle(int pvecCenter)
{
  int *v3; // eax
  int v4; // ecx
  void *v6; // [esp+0x0] [ebp-0x1C]

  v3 = &this->m_CamEntries[5];
  v4 = 384;
  do
  {
    *(v3 - 2) = 0;
    *(v3 - 1) = 0;
    *v3 = 0;
    v3[5] = 0;
    v3[6] = 0;
    v3[7] = 0;
    v3 += 15;
    --v4;
  }
  while ( v4 );
  todo_408BD0(v6);
  this->m_nList = 0;
  this->m_nPointerUnderMouse = 0;
  this->m_pvecCenter = (gbVec3D *)pvecCenter;
  return this;
}

// 0x005084C0
bool CCBCamControl::IsPointerUnderMouse()
{
  char *v2; // esi

  v2 = (char *)operator new(0xD8u);
  if ( v2 )
  {
    *((_DWORD *)v2 + 1) = 1;
    *((_DWORD *)v2 + 24) = 0;
    *((_DWORD *)v2 + 25) = 0;
    *((_DWORD *)v2 + 26) = 0;
    ((CCBCamControl *)(v2 + 108))->LoadPointer();
  }
  else
  {
    v2 = 0;
  }
  ((gbLightObj *)v2)->Init(0);
  *((_DWORD *)v2 + 7) = 1008981770;
  *((_DWORD *)v2 + 8) = 1008981770;
  *((_DWORD *)v2 + 9) = 1008981770;
  *((_DWORD *)v2 + 10) = 1065353216;
  *((_DWORD *)v2 + 17) = 1;
  *((_DWORD *)v2 + 18) = 1133903872;
  *((_DWORD *)v2 + 21) = 1056964608;
  *((_DWORD *)v2 + 3) = 1008981770;
  *((_DWORD *)v2 + 11) = 1;
  *((_DWORD *)v2 + 12) = 1;
  *((_DWORD *)v2 + 4) = 1008981770;
  *((_DWORD *)v2 + 13) = 0;
  *((_DWORD *)v2 + 14) = 0;
  *((_DWORD *)v2 + 5) = 1008981770;
  *((_DWORD *)v2 + 15) = 0x40000000;
  *((_DWORD *)v2 + 16) = 1133903872;
  *((_DWORD *)v2 + 6) = 1065353216;
  ((gbVolModNode *)&this->_todo_010)->SetVolModObj((gbVolumeModifier *)v2);
  ((gbRefObject *)v2)->Release();
  this->m_nList = (gbRefObject *)((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\geom_diffuse.gbf", 0x401u);
  this->m_nPointerUnderMouse = (int)((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\geom_diffuse_t.gbf", 0x441u);
  return 1;
}

// 0x00508660
int * CCBCamControl::LoadPointer()
{
  this->m_fCamBlendA = 0.0;
  this->m_fCamBlendB = 0.0;
  this->m_CamCtrlData = 0;
  *(&this->m_CamCtrlData + 1) = 0;
  *(&this->m_CamCtrlData + 2) = 0;
  *(&this->m_CamCtrlData + 3) = 0;
  return (int *)this;
}

// 0x00508680
void CCBCamControl::DoList()
{
  ((gbRefObject *)this->m_nList)->Release();
}

// 0x00508690
void CCBCamControl::ResetListFlag()
{
  char *v2; // esi
  _DWORD *v3; // edx
  gbVolumeModifier *v4; // edx

  v2 = (char *)operator new(0xD8u);
  if ( v2 )
  {
    *((_DWORD *)v2 + 1) = 1;
    ((CCBCamControl *)(v2 + 108))->LoadPointer();
  }
  else
  {
    v2 = 0;
  }
  ((gbLightObj *)v2)->Init(0);
  *((_DWORD *)v2 + 7) = 0;
  *((_DWORD *)v2 + 8) = 0;
  *((_DWORD *)v2 + 9) = 0;
  *((_DWORD *)v2 + 10) = 1065353216;
  *((_DWORD *)v2 + 17) = 1;
  *((_DWORD *)v2 + 18) = 1133903872;
  *((_DWORD *)v2 + 21) = 1056964608;
  *((_DWORD *)v2 + 3) = 0;
  *((_DWORD *)v2 + 11) = 1;
  *((_DWORD *)v2 + 12) = 1;
  *((_DWORD *)v2 + 4) = 0;
  *((_DWORD *)v2 + 13) = 0;
  *((_DWORD *)v2 + 14) = 0;
  *((_DWORD *)v2 + 5) = 0;
  *((_DWORD *)v2 + 15) = 0x40000000;
  *((_DWORD *)v2 + 16) = 1133903872;
  *((_DWORD *)v2 + 6) = 1065353216;
  ((gbVolModNode *)&this->_embed_gbVolModNode_EC)->SetVolModObj((gbVolumeModifier *)v2);
  ((gbRefObject *)v2)->Release();
  v3 = (_DWORD *)(*(&this->m_CamCtrlData + 43) + 28);
  *v3 = -1098907648;
  v3[1] = -1098907648;
  v3[2] = -1098907648;
  v3[3] = 1065353216;
  v4 = this->_embed_gbVolModNode_EC.m_pModObj + 7;
// [VFTABLE] v4->__vftable = (void *)-1098907648;
// [VFTABLE] v4[1].__vftable = (void *)-1098907648;
// [VFTABLE] v4[2].__vftable = (void *)-1098907648;
// [VFTABLE] v4[3].__vftable = (void *)1065353216;
}

// 0x00508880
void CCBCamControl::KeepCurCam(int pCam)
{
  int *m_CamEntries; // edx
  int v3; // eax
  int *i; // esi
  int v5; // eax

  m_CamEntries = this->m_CamEntries;
  v3 = 0;
  for ( i = this->m_CamEntries; *i != pCam; i += 15 )
  {
    if ( ++v3 >= 384 )
    {
      v5 = 0;
      while ( *m_CamEntries )
      {
        ++v5;
        m_CamEntries += 15;
        if ( v5 >= 384 )
          return;
      }
      this->m_CamEntries[15 * v5] = pCam;
      return;
    }
  }
}

// 0x005088D0
void CCBCamControl::DoLineMove(unsigned int dwVal)
{
  char *v3; // esi
  int v4; // esi

  if ( dwVal < 0x180 )
  {
    v3 = (char *)this + 60 * dwVal;
    if ( *((_DWORD *)v3 + 612) != -1 )
      ((CEffect *)*(CEffect **)(LODWORD(this->m_pvecCenter->x) + 44))->Render(*((_DWORD *)v3 + 612));
    v4 = *((_DWORD *)v3 + 619);
    if ( v4 != -1 )
      ((CEffect *)*(CEffect **)(LODWORD(this->m_pvecCenter->x) + 44))->Render(v4);
  }
}
