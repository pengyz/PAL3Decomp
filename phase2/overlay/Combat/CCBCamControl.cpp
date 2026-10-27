#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBCamControl.h"
#include "Role/Actor.h"
#include "Misc/CCBDisplayChain.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBStageEffect.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCCTData.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffect.h"
#include "Combat/CUtil.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Role/NPC.h"
#include "Data/PAL_GDB.h"
#include "Render/RenderTarget2.h"
#include "Misc/UIAnimateCtrl.h"
#include "Misc/tag17A7BData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

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
  v4 = (char *)&g_EffTable[4];
  do
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[1] = v3;
    lParam[2] = 0;
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v3);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    v5 = v4[208];
    lParam[2] = 1;
    if ( v5 )
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", v4);
    else
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&unk_5D8B6C);
    result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    v4 += 280;
    ++v3;
  }
  while ( (int)v4 < (int)&g_17A7BData );
  v7 = this->m_CamEntries[1405];
  if ( v7 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[3] = 3;
    lParam[4] = 3;
    lParam[1] = v7;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    SendMessageA(DlgItem, 0x102Bu, v7, (LPARAM)lParam);
    return SendMessageA(DlgItem, 0x1013u, this->m_CamEntries[1405], 0);
  }
  return result;
}

// 0x004EB6F0
void CCBCamControl::sub_4EB6F0(HWND hDlg)
{
  this->CCBCamControl::sub_4EB720(hDlg);
  this->CCBCamControl::sub_4EB8D0(hDlg);
  this->CCBCamControl::ShowCameraDialog(hDlg);
}

// 0x004EB720
LRESULT CCBCamControl::sub_4EB720(HWND hDlg)
{
  HWND DlgItem; // esi
  LPARAM v4; // eax
  int *v5; // edi
  LRESULT result; // eax
  int v7; // edx
  int v8; // eax
  int EffByID; // eax
  int EffSlot; // eax
  WPARAM v11; // edx
  LRESULT v12; // [esp+0x10] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x14] [ebp-0x28] BYREF
  char *hDlga; // [esp+0x40] [ebp+0x4]

  DlgItem = GetDlgItem(hDlg, 1276);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  v4 = 0;
  v5 = (int *)&g_nSaveSlot1;
  for ( hDlga = 0; ; v4 = (LPARAM)hDlga )
  {
    v12 = *(v5 - 1);
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[1] = v4;
    lParam[2] = 0;
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v4);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    lParam[2] = 1;
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v12);
    SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    result = v12;
    if ( v12 )
    {
      v7 = *(_DWORD *)this;
      v8 = (unsigned long)*v5;
      lParam[2] = 2;
      EffByID = (((CEffMgr *)*(CEffMgr **)(v7 + 44)))->CEffMgr::FindEffByID(v8);
      EffSlot = (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)this + 44)))->CEffMgr::FindEffSlot(*(_DWORD *)&g_EffTable[280 * EffByID]);
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", *(_DWORD *)(*(_DWORD *)this + 44) + 72 * EffSlot + 28);
      result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
    v5 += 3985;
    ++hDlga;
    if ( (int)v5 >= (int)&g_EffTable[4] )
      break;
  }
  v11 = this->m_CamEntries[1793];
  if ( v11 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[1] = v11;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
  _BYTE *v5; // edi
  signed int v6; // edi
  int ItemID; // edi
  char v8; // al
  LPARAM v9; // edi
  int v10; // ecx
  int v11; // eax
  LRESULT result; // eax
  WPARAM m_nCurCamIdx; // edx
  signed int index; // [esp+0x14] [ebp-0x38]
  signed int indexa; // [esp+0x14] [ebp-0x38]
  CCBCamControl *SkillID; // [esp+0x18] [ebp-0x34]
  CCBCamControl *v18; // [esp+0x18] [ebp-0x34]
  int RoleNum; // [esp+0x1C] [ebp-0x30]
  int RoleBySlot; // [esp+0x1C] [ebp-0x30]
  int ItemNum; // [esp+0x20] [ebp-0x2C]
  int SkillNum; // [esp+0x20] [ebp-0x2C]
  char *v23; // [esp+0x20] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x24] [ebp-0x28] BYREF
  int *hDlga; // [esp+0x50] [ebp+0x4]
  int *hDlgb; // [esp+0x50] [ebp+0x4]
  int *hDlgc; // [esp+0x50] [ebp+0x4]
  int *hDlgd; // [esp+0x50] [ebp+0x4]

  DlgItem = GetDlgItem(hDlg, 1278);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  RoleNum = GDB_GetRoleNum((PAL_GDB *)&g_pGDB);
  index = GDB_GetItemNum((PAL_GDB *)&g_pGDB);
  v3 = 0;
  SkillID = (CCBCamControl *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillID();
  if ( RoleNum > 0 )
  {
    hDlga = (int *)&this->m_CamEntries[1409];
    do
    {
      PropertyByIndex = (((NPC *)&g_pGDB))->NPC::GetPropertyByIndex(v3);
      *hDlga = PropertyByIndex;
      v5 = (_BYTE *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(PropertyByIndex);
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      lParam[1] = v3;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v3);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      if ( v5[572] || v5[573] || v5[574] || v5[575] || v5[576] )
      {
        lParam[2] = 1;
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", v5 + 28);
      }
      else
      {
        lParam[2] = 1;
        sprintf((char *const)&g_CCBStageCamBuffer, "(敌)%s", v5 + 28);
      }
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v3;
      ++hDlga;
    }
    while ( v3 < RoleNum );
  }
  v6 = 0;
  if ( index > 0 )
  {
    hDlgb = (int *)&this->m_CamEntries[v3 + 1409];
    do
    {
      RoleBySlot = (((UIAnimateCtrl *)&g_pGDB))->UIAnimateCtrl::GetRoleBySlot(v6);
      ItemNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(RoleBySlot);
      *hDlgb = RoleBySlot;
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      lParam[1] = v3;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v3);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", ItemNum);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v3;
      ++v6;
      ++hDlgb;
    }
    while ( v6 < index );
  }
  indexa = 0;
  if ( (int)SkillID > 0 )
  {
    hDlgc = (int *)&this->m_CamEntries[v3 + 1409];
    do
    {
      ItemID = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(indexa);
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(ItemID);
      v8 = *(_BYTE *)(SkillNum + 612);
      if ( v8 == 1 || v8 == 2 )
      {
        *hDlgc = ItemID;
        lParam[0] = 1;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
        lParam[1] = v3;
        lParam[2] = 0;
        sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v3);
        SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
        lParam[2] = 1;
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", SkillNum + 4);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        ++v3;
        ++hDlgc;
      }
      ++indexa;
    }
    while ( indexa < (int)SkillID );
  }
  v9 = 0;
  v18 = (CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(_DWORD *)this + 20) + 76);
  if ( v3 > 0 )
  {
    hDlgd = (int *)&this->m_CamEntries[1409];
    do
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      lParam[1] = v9;
      v10 = (unsigned long)*hDlgd;
      lParam[2] = 2;
      (((CCBCamControl *)v18))->CCBCamControl::KeepCurCam(v10);
      v23 = (char *)v18 + 60 * v11;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], *((_DWORD *)v23 + 612));
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 3;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], *((_DWORD *)v23 + 619));
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
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
    v6 = (CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(_DWORD *)this + 20) + 76);
    (((CCBCamControl *)v6))->CCBCamControl::KeepCurCam(this->m_CamEntries[this->m_nCurCamIdx + 1409]);
    v7 *= 3;
    v8 = v6->m_CamEntries[5 * v7 + 1];
    v9 = (int)&v6->m_CamEntries[5 * v7];
    EditBoxSetInt(DlgItem, v8);
    EditBoxSetInt(hDlga, *(_DWORD *)(v9 + 32));
    EditBoxSetFloat(v18, *(float *)(v9 + 24));
    v10 = EditBoxSetFloat(v19, *(float *)(v9 + 52));
    LOBYTE(v10) = *(_BYTE *)(v9 + 8);
    EditBoxSetReadOnly(hWnd, v10);
    LOBYTE(v11) = *(_BYTE *)(v9 + 36);
    EditBoxSetReadOnly(v21, v11);
    LOBYTE(v12) = *(_BYTE *)(v9 + 9);
    Only = EditBoxSetReadOnly(v22, v12);
    LOBYTE(Only) = *(_BYTE *)(v9 + 37);
    EditBoxSetReadOnly(v23, Only);
    LOBYTE(v14) = *(_BYTE *)(v9 + 10);
    EditBoxSetReadOnly(v24, v14);
    LOBYTE(v15) = *(_BYTE *)(v9 + 38);
    v16 = EditBoxSetReadOnly(v25, v15);
    LOBYTE(v16) = *(_BYTE *)(v9 + 11);
    EditBoxSetReadOnly(v26, v16);
    LOBYTE(v17) = *(_BYTE *)(v9 + 39);
    EditBoxSetReadOnly(v27, v17);
    EditBoxSetFloat(v28, *(float *)(v9 + 12));
    EditBoxSetFloat(v29, *(float *)(v9 + 16));
    EditBoxSetFloat(v30, *(float *)(v9 + 20));
    EditBoxSetFloat(v31, *(float *)(v9 + 40));
    EditBoxSetFloat(v32, *(float *)(v9 + 44));
    EditBoxSetFloat(v33, *(float *)(v9 + 48));
    EditBoxSetFloat(v34, *(float *)(v9 + 28));
    EditBoxSetFloat(v5, *(float *)(v9 + 56));
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
    v6 = (CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(_DWORD *)this + 20) + 76);
    (((CCBCamControl *)v6))->CCBCamControl::KeepCurCam(this->m_CamEntries[this->m_nCurCamIdx + 1409]);
    v8 = (int)&v6->m_CamEntries[15 * v7];
    *(_DWORD *)(v8 + 4) = EditBoxGetInt(DlgItem);
    *(_DWORD *)(v8 + 32) = EditBoxGetInt(hDlga);
    *(float *)(v8 + 24) = EditBoxGetFloat(v9);
    *(float *)(v8 + 52) = EditBoxGetFloat(v10);
    *(_BYTE *)(v8 + 8) = EditBoxIsModified(hWnd);
    *(_BYTE *)(v8 + 36) = EditBoxIsModified(v12);
    *(_BYTE *)(v8 + 9) = EditBoxIsModified(v13);
    *(_BYTE *)(v8 + 37) = EditBoxIsModified(v14);
    *(_BYTE *)(v8 + 10) = EditBoxIsModified(v15);
    *(_BYTE *)(v8 + 38) = EditBoxIsModified(v16);
    *(_BYTE *)(v8 + 11) = EditBoxIsModified(v17);
    *(_BYTE *)(v8 + 39) = EditBoxIsModified(v18);
    *(float *)(v8 + 12) = EditBoxGetFloat(v19);
    *(float *)(v8 + 16) = EditBoxGetFloat(v20);
    *(float *)(v8 + 20) = EditBoxGetFloat(v21);
    *(float *)(v8 + 40) = EditBoxGetFloat(v22);
    *(float *)(v8 + 44) = EditBoxGetFloat(v23);
    *(float *)(v8 + 48) = EditBoxGetFloat(v24);
    *(float *)(v8 + 28) = EditBoxGetFloat(v25);
    *(float *)(v8 + 56) = EditBoxGetFloat(v5);
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
    (((CCBCamControl *)*((CCBCamControl **)&this->m_CamCtrlData + 4)))->CCBCamControl::KeepCurCam(this->m_CamEntries[v3 + 78]);
    *((_DWORD *)v5 + 14) = v6;
    (((CCBCamControl *)*((CCBCamControl **)&this->m_CamCtrlData + 4)))->CCBCamControl::DoLineMove(v6);
    v5[41] = 1;
  }
  *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x005052E0
CCBStageCam * CCBCamControl::SetCamPos(int **pCamParam, int nVal)
{
  CUtil *v4; // eax

  (((CCBStageCam *)this))->CCBStageCam::ResetViewport();
  this->m_vecSpeed.x = 0.0f;
  this->m_vecSpeed.y = 0.0f;
  this->m_vecSpeed.z = 0.0f;
  this->m_vecNextSpeed.x = 0.0f;
  this->m_vecNextSpeed.y = 0.0f;
  this->m_vecNextSpeed.z = 0.0f;
  this->m_StartPos.x = 0.0f;
  this->m_StartPos.y = 0.0f;
  this->m_StartPos.z = 0.0f;
  this->m_StartPos.yaw.p = 0;
  this->m_StartPos.pit = 0.0f;
  this->m_StartPos.rol = 0.0f;
  this->m_CurPos.x = 0.0f;
  this->m_CurPos.y = 0.0f;
  this->m_CurPos.z = 0.0f;
  this->m_CurPos.yaw.p = 0;
  this->m_CurPos.pit = 0.0f;
  this->m_CurPos.rol = 0.0f;
  this->m_vecCurPos.x = 0.0f;
  this->m_vecCurPos.y = 0.0f;
  this->m_vecCurPos.z = 0.0f;
  this->m_vecCircleCenter.x = 0.0f;
  this->m_vecCircleCenter.y = 0.0f;
  this->m_vecCircleCenter.z = 0.0f;
  this->m_vecCircleEnd.x = 0.0f;
  this->m_vecCircleEnd.y = 0.0f;
  this->m_vecCircleEnd.z = 0.0f;
  this->m_pStage = ((CCBStage *)((CCBStage *)pCamParam));
  this->m_pCam = ((CCBStageCam *)((CCBStageCam *)nVal));
  v4 = (CUtil *)**pCamParam;
  this->m_nCurTask = -1;
  this->m_pUtil = ((CUtil *)(v4));
  return (CCBStageCam *)this;
}

// 0x005054B0
bool CCBCamControl::Init()
{
  gbGeomNode *m_pPointer; // ecx

  m_pPointer = (gbGeomNode *)this->m_pPointer;
  if ( m_pPointer )
  {
    (**(void ( ***)(gbGeomNode *, int))((gbChain1DNode *)m_pPointer))((gbGeomNode *)(m_pPointer), (int)(1));
    this->m_pPointer = ((gbGeomNode *)0);
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
  const gbVec3D *ViewTarget; // eax
  float x; // edx
  double v9; // st7
  char m_bCircleCenterSelected; // al
  double v11; // st7
  double v12; // st6
  float z; // eax
  double v14; // st6
  float v15; // edx
  int v16; // [esp+0x8] [ebp-0x58]
  int pPos[3]; // [esp+0xC] [ebp-0x54] BYREF
  struct gbVec3D v18; // [esp+0x18] [ebp-0x48] BYREF
  struct gbVec3D v19; // [esp+0x24] [ebp-0x3C] BYREF
  gbRay v20; // [esp+0x30] [ebp-0x30] BYREF
  _BYTE pTarget[24]; // [esp+0x48] [ebp-0x18] BYREF

  this->m_pCam->m_lastYAW = 0.0;
  if ( this->m_bRunning )
    (((CCCTData *)this))->CCCTData::Init();
  if ( this->m_fQuake <= 0.0f )
  {
    this->m_fQuake = 0.0f;
  }
  else
  {
    m_pStage = (CCBStage *)this->m_pStage;
    pPos[0] = LODWORD(this->m_CurPos.y);
    m_pCam = (CCBStageCam *)this->m_pCam;
    v4 = this->m_fQuake - m_pStage->m_pCBSystem->m_DeltaTime * this->m_fQuakeDec;
    this->m_fQuake = v4;
    this->m_CurPos.y = sin(m_pStage->m_pCBSystem->m_fTimeFund * this->m_fQuakeFre) * v4 + this->m_CurPos.y;
    (((CCCTData *)m_pCam))->CCCTData::UpdateCamera((int)&this->m_CurPos);
    (((CameraCtrl *)this->m_pCam))->CameraCtrl::SetAsCurrent(3);
    LODWORD(this->m_CurPos.y) = pPos[0];
  }
  if ( g_nCombatViewMode == 4 )
  {
    this->CCBCamControl::SwitchEditorCamPos(v16, pPos[0]);
    this->CCBCamControl::ProcCamMove();
    v20.Origin.x = 1.0f;
    v18.x = 0.0;
    v19.z = 0.0;
    memset(&v20.Origin.y, 0, 16);
    pPos[2] = 1065353216;
    v18.y = 1.0;
    v19.x = 0.0;
    v18.z = 1.0;
    v19.y = 1.0;
    ((gbVec3D *)&v20.Direction.z)->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
    v5 = (CCBStage *)this->m_pStage;
    pPos[0] = (int)v5->m_WPXVariance;
    v6 = (CCBStageCam *)this->m_pCam;
    pPos[1] = (int)v5->m_pDisplayChain;
    ViewTarget = (const gbVec3D *)(((CameraCtrl *)v6))->CameraCtrl::GetViewTarget(pTarget, (float *)pPos);
    x = ViewTarget->x;
    ++ViewTarget;
    v20.Origin.x = x;
    v20.Origin.y = ViewTarget[-1].y;
    v20.Origin.z = ViewTarget[-1].z;
    (((gbVec3D *)&v20.Direction))->gbVec3D::operator=(*(ViewTarget));
    v9 = (((gbRay *)&v20))->gbRay::IntersectPlane(v19,  v18);
    m_bCircleCenterSelected = this->m_bCircleCenterSelected;
    v19.x = v20.Direction.x * v9;
    v18.x = v19.x + v20.Origin.x;
    v11 = v9 * v20.Direction.z + v20.Origin.z;
    if ( m_bCircleCenterSelected )
    {
      v12 = (double)*(int *)&g_Input.MouseState[8] * 0.1 + this->m_vecCircleCenter.y;
      this->m_vecCircleCenter.y = v12;
      v19.x = v18.x;
      v19.z = v11;
      z = v19.z;
      this->m_vecCircleCenter.x = v18.x;
      this->m_vecCircleCenter.y = v12;
      this->m_vecCircleCenter.z = z;
    }
    if ( this->m_bCircleEndSelected )
    {
      v14 = (double)*(int *)&g_Input.MouseState[8] * 0.1 + this->m_vecCircleEnd.y;
      this->m_vecCircleEnd.y = v14;
      v19.z = v11;
      v15 = v19.z;
      this->m_vecCircleEnd.x = v18.x;
      this->m_vecCircleEnd.y = v14;
      this->m_vecCircleEnd.z = v15;
    }
  }
}

// 0x00505770
char CCBCamControl::ClearFinishedTask(int nVal)
{
  int v3; // eax

  LOBYTE(v3) = (((CCBStageCam *)this))->CCBStageCam::IsEditorCamValid(nVal);
  if ( !v3 )
    return 0;
  this->m_bRunning = 1;
  (((CCCTData *)this))->CCCTData::Save(nVal);
  this->m_nCurList = nVal;
  this->m_nCurTask = 0;
  return 1;
}

// 0x00505800
int CCBCamControl::AddTask()
{
  int result; // eax

  result = -1;
  this->m_bRunning = 0;
  this->m_nCurList = -1;
  this->m_nCurTask = -1;
  return result;
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

  p_m_vecCircleCenter = (gbVec3D *)&this->m_vecCircleCenter;
  pfVal = this->m_vecCircleCenter.x;
  p_m_vecCircleEnd = (gbVec3D *)&this->m_vecCircleEnd;
  y = p_m_vecCircleCenter->y;
  z = p_m_vecCircleCenter->z;
  x = p_m_vecCircleEnd->x;
  v8 = z;
  v10 = p_m_vecCircleEnd->y;
  result = g_Input.KeyInfo[15].PressTime;
  v11 = p_m_vecCircleEnd->z;
  y = 0.0f;
  v10 = 0.0f;
  if ( g_Input.KeyInfo[15].PressTime == 1 )
  {
    result = (((CCCTData *)this))->CCCTData::Create(&pfVal);
    if ( result )
    {
      this->m_bCircleCenterSelected = 1;
    }
    else
    {
      result = (((CCCTData *)this))->CCCTData::Create(&x);
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
bool CCBCamControl::SwitchEditorCamPos(int nVal1, int nVal2)
{
  return (*(int ( **)(gbGeomNode *, int, int))(*(_DWORD *)((gbChain1DNode *)this->m_pPointer) + 20))(
           this->m_pPointer,
           nVal1,
           nVal2);
}

// 0x005081E0
CCBCamControl::~CCBCamControl()
{
  *((_QWORD *)&g_CCBCamControlData + 184) = 0x13A00000077i64;
  *((_QWORD *)&g_CCBCamControlData + 185) = 0x2C3000001FEi64;
}

// 0x00508220
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBCamControl::Reset()
{
  this->CCBCamControl::Create();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00508230
bool CCBCamControl::Create()
{
  bool result; // al

  *((_QWORD *)&g_CCBCamControlData + 186) = 0x20700000207i64;
  result = 7;
  *((_QWORD *)&g_CCBCamControlData + 187) = 0x20700000207i64;
  return result;
}

// 0x00508270
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
bool CCBCamControl::Destroy()
{
  return CCBCamControl_Init();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005082C0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBCamControl::Update()
{
  this->CCBCamControl::StartList();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005082D0
bool CCBCamControl::StartList()
{
  bool result; // al

  *((_QWORD *)&g_CCBCamControlData + 190) = 0x22100000221i64;
  result = 33;
  *((_QWORD *)&g_CCBCamControlData + 191) = 0x22100000221i64;
  return result;
}

// 0x00508320
void CCBCamControl::StopList()
{
  *((_QWORD *)&g_CCBCamControlData + 192) = 0x13C00000079i64;
  *((_QWORD *)&g_CCBCamControlData + 193) = 0x2C500000200i64;
}

// 0x00508360
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBCamControl::HandleInput()
{
  this->CCBCamControl::UpdateCircleSet();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00508370
void CCBCamControl::UpdateCircleSet()
{
  *((_QWORD *)&g_CCBCamControlData + 194) = 0x23D0000023Di64;
  *((_QWORD *)&g_CCBCamControlData + 195) = 0x23D0000023Di64;
}

// 0x005083B0
CCBCamControl * CCBCamControl::SetCircle(int pvecCenter)
{
  int *v3; // eax
  int v4; // ecx
  void *v6; // [esp+0x0] [ebp-0x1C]

  v3 = (int *)&this->m_CamEntries[5];
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
  NullCallback(v6);
  this->m_nList = ((gbRefObject *)0);
  this->m_nPointerUnderMouse = 0;
  this->m_pvecCenter = ((gbVec3D *)((gbVec3D *)pvecCenter));
  return this;
}

// 0x005084C0
bool CCBCamControl::IsPointerUnderMouse()
{
  char *v2; // esi

  ((CCBStageEffect *)this)->CCBStageEffect::CCBStageEffect();
  v2 = (char *)operator new(0xD8u);
  if ( v2 )
  {
    *((_DWORD *)v2 + 1) = 1;
    *((_DWORD *)v2 + 24) = 0;
    *((_DWORD *)v2 + 25) = 0;
    *((_DWORD *)v2 + 26) = 0;
    (((CCBCamControl *)(v2 + 108)))->CCBCamControl::LoadPointer();
  }
  else
  {
    v2 = 0;
  }
  (((gbLightObj *)v2))->gbLightObj::Init((enum gbLightObj::LIGHT_TYPE)0);
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
  (((gbVolModNode *)&this->m_nTodo_010))->gbVolModNode::SetVolModObj((gbVolumeModifier *)v2);
  (((gbRefObject *)v2))->gbRefObject::Release();
  this->m_nList = ((gbRefObject *)((((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect(aGfxscriptGeomD, 0x401u)));
  this->m_nPointerUnderMouse = (int)(((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect(aGfxscriptGeomD_0, 0x441u);
  return 1;
}

// 0x00508660
int * CCBCamControl::LoadPointer()
{
  int *result; // eax

  result = (int *)this;
  this->m_fCamBlendA = 0.0f;
  this->m_fCamBlendB = 0.0f;
  this->m_CamCtrlData = 0;
  *(&this->m_CamCtrlData + 1) = 0;
  *(&this->m_CamCtrlData + 2) = 0;
  *(&this->m_CamCtrlData + 3) = 0;
  return result;
}

// 0x00508680
void CCBCamControl::DoList()
{
  (((gbRefObject *)this->m_nList))->gbRefObject::Release();
}

// 0x00508690
void CCBCamControl::ResetListFlag()
{
  char *v2; // esi
  _DWORD *v3; // edx
  float *v4; // edx

  v2 = (char *)operator new(0xD8u);
  if ( v2 )
  {
    *((_DWORD *)v2 + 1) = 1;
    ((gbVec3D *)v2 + 8)->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
    (((CCBCamControl *)(v2 + 108)))->CCBCamControl::LoadPointer();
  }
  else
  {
    v2 = 0;
  }
  (((gbLightObj *)v2))->gbLightObj::Init((enum gbLightObj::LIGHT_TYPE)0);
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
  (((gbVolModNode *)&this->m_nTodo_EC))->gbVolModNode::SetVolModObj((gbVolumeModifier *)v2);
  (((gbRefObject *)v2))->gbRefObject::Release();
  v3 = (_DWORD *)(*(&this->m_CamCtrlData + 43) + 28);
  *v3 = -1098907648;
  v3[1] = -1098907648;
  v3[2] = -1098907648;
  v3[3] = 1065353216;
  // [overlay-fix 2026-10-27] C2039: gbVolModNode 无 m_pModObj 成员（类型标注错/垃圾形）——待语义修复
  // v4 = this->m_nTodo_EC.m_pModObj + 7;
  *v4 = -0.25;
  v4[1] = -0.25;
  v4[2] = -0.25;
  v4[3] = 1.0;
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
      (((CEffect *)*(CEffect **)(LODWORD(this->m_pvecCenter->x) + 44)))->CEffect::Render(*((_DWORD *)v3 + 612));
    v4 = *((_DWORD *)v3 + 619);
    if ( v4 != -1 )
      (((CEffect *)*(CEffect **)(LODWORD(this->m_pvecCenter->x) + 44)))->CEffect::Render(v4);
  }
}
