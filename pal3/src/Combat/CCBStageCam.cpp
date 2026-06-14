#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStageCam.h"

// Forward declarations for unnamed functions
int sub_4CE5C0(...);
int sub_4CE7F0(...);
int sub_4CE8A0(...);
int sub_4CE970(...);
int sub_4CEA40(...);
int sub_4E95A0(...);
int sub_4E9750(...);
char sub_504F40(void); // from annotations
int sub_5057B0(...);
void __cdecl todo_401800(void);

double EditBox_GetFloat(HWND hWnd); // from annotations
int EditBox_GetInt(HWND hWnd); // from annotations
BOOL EditBox_IsModified(HWND hWnd); // from annotations
LRESULT EditBox_SetFloat(HWND hWnd, float fValue); // from annotations
LRESULT EditBox_SetInt(HWND hWnd, int nValue); // from annotations
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations

// Unnamed globals (extern)
extern char byte_1895559;
extern char byte_5967B0[3];
extern char byte_EC9F0C[];
extern int dword_EC9F00[];
extern char unk_5D8A38[];
extern const char * unk_5D8A3C;
extern CHAR unk_5D8A6C;
extern CHAR unk_5D8A90;
extern char unk_5D8AB4;
extern char unk_5D8ABC;
extern char unk_5D8AC4;
extern CHAR unk_5D8AD4;
extern CHAR unk_5D8AF4;
extern CHAR unk_5D8B14;
extern CHAR unk_5D8B3C;
extern CHAR unk_5D8B44;
extern CHAR unk_5D8B88;

// 0x004E6020
int CCBStageCam::UpdateEditorState()
{
  int v1; // eax
  HWND DlgItem; // ebx
  HWND v3; // ebp
  int FullConfig; // esi
  int result; // eax
  HWND v6; // ebx
  int v7; // ecx
  int v8; // eax
  WPARAM v9; // ecx
  int v10; // ecx
  HWND v11; // ebx
  int v12; // eax
  int v13; // eax
  WPARAM v14; // ecx
  LRESULT v15; // eax
  WPARAM v16; // esi
  int v17; // esi
  float fov; // ecx
  LRESULT v19; // eax
  int v20; // esi
  int i; // esi
  int v22; // ebx
  int v23; // edx
  HWND v24; // ebx
  int v25; // eax
  HWND v26; // ebx
  char *v27; // eax
  char *v28; // esi
  char *v29; // eax
  char *v30; // esi
  int v31; // ecx
  float *v32; // eax
  CCBStage *v33; // edi
  int v34; // esi
  char *v35; // eax
  char *v36; // esi
  int v37; // ecx
  float *v38; // eax
  LRESULT v39; // eax
  LRESULT v40; // eax
  LRESULT v41; // eax
  HWND v42; // ebx
  HWND v43; // ebx
  int v44; // eax
  char *v45; // eax
  int v46; // eax
  char *v47; // eax
  int v48; // eax
  WPARAM v49; // [esp-0x8] [ebp-0x158]
  WPARAM v50; // [esp-0x8] [ebp-0x158]
  WPARAM v51; // [esp-0x8] [ebp-0x158]
  WPARAM v52; // [esp-0x8] [ebp-0x158]
  WPARAM v53; // [esp-0x8] [ebp-0x158]
  CCBStageCam *v54; // [esp+0x0] [ebp-0x150]
  CCBStageCam *Buffer; // [esp+0x10] [ebp-0x140]
  LPARAM lParam[10]; // [esp+0x14] [ebp-0x13C] BYREF
  CCBStage *v57; // [esp+0x3C] [ebp-0x114]
  HWND hWnd; // [esp+0x40] [ebp-0x110]
  LPARAM v59[8]; // [esp+0x44] [ebp-0x10C] BYREF
  HWND v60; // [esp+0x64] [ebp-ECh]
  HWND v61; // [esp+0x68] [ebp-E8h]
  int p_DWORD[3]; // [esp+0x6C] [ebp-E4h] BYREF
  int p_DWORD2[3]; // [esp+0x78] [ebp-D8h] BYREF
  _DWORD pData[51]; // [esp+0x84] [ebp-CCh] BYREF
  CCBStageCam *v65; // [esp+0x154] [ebp+0x4]
  HWND hDlg; // [esp+0x158] [ebp+0x8]
  int v67; // [esp+0x15C] [ebp+0xC]
  int v68; // [esp+0x160] [ebp+0x10]
  int v69; // [esp+0x164] [ebp+0x14]

  v1 = *(_DWORD *)(LODWORD(v65->fov) + 20);
  Buffer = *(CCBStageCam **)(v1 + 16);
  v57 = *(CCBStage **)(v1 + 12);
  DlgItem = GetDlgItem(hDlg, 1150);
  v61 = GetDlgItem(hDlg, 1163);
  hWnd = GetDlgItem(hDlg, 1151);
  v3 = GetDlgItem(hDlg, 1152);
  v60 = v3;
  if ( v67 == 78 )
  {
    switch ( v68 )
    {
      case 1150:
        v48 = *(_DWORD *)(v69 + 8);
        if ( (v48 == -3 || v48 == -2 && EditBox_IsModified(v61))
          && *(_DWORD *)(v69 + 12) != -1
          && ((CCBStage *)v57)->GetTurnSlotData(*(_DWORD *)(v69 + 12)) )
        {
          ((j_CCCTData *)*(_DWORD *)(v69 + 12))->CCCTData::UpdateCamera();
        }
        return 0;
      case 1151:
        v46 = *(_DWORD *)(v69 + 8);
        if ( v46 != -3 && v46 != -2 )
          return 0;
        v47 = *(char **)(v69 + 12);
        if ( v47 == (char *)-1 )
          return 0;
        v65[1].m_Task[13].fp[1] = v47;
        v65[1].m_Task[13].fp[2] = (char *)-1;
        ((CCBStageCam *)v65)->PopulateCameraListView();
        break;
      case 1152:
        v44 = *(_DWORD *)(v69 + 8);
        if ( v44 != -3 && v44 != -2 )
          return 0;
        v45 = *(char **)(v69 + 12);
        if ( v45 == (char *)-1 )
          return 0;
        v65[1].m_Task[13].fp[2] = v45;
        break;
      default:
        return 0;
    }
LABEL_26:
    ((CCCTData *)v65)->UpdateDebugDialog();
    return 0;
  }
  if ( v67 == 272 )
  {
    SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
    v39 = SendMessageA(DlgItem, 0x1037u, 0, 0);
    LOBYTE(v39) = v39 | 0x21;
    SendMessageA(DlgItem, 0x1036u, 0, v39);
    v40 = SendMessageA(hWnd, 0x1037u, 0, 0);
    LOBYTE(v40) = v40 | 0x21;
    SendMessageA(hWnd, 0x1036u, 0, v40);
    v41 = SendMessageA(v60, 0x1037u, 0, 0);
    LOBYTE(v41) = v41 | 0x21;
    SendMessageA(v60, 0x1036u, 0, v41);
    memset(v59, 0, sizeof(v59));
    memset(lParam, 0, sizeof(lParam));
    v59[0] = 7;
    v59[1] = 0;
    v59[2] = 40;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 38;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 49;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)v59);
    v42 = hWnd;
    v59[0] = 7;
    v59[1] = 0;
    v59[2] = 25;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(hWnd, 0x101Bu, 0, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 38;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(v42, 0x101Bu, 1u, (LPARAM)v59);
    v59[0] = 7;
    v43 = v60;
    v59[1] = 0;
    v59[2] = 25;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(v60, 0x101Bu, 0, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 48;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(v43, 0x101Bu, 1u, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 40;
    v59[3] = (LPARAM)&g_EffMgr;
    SendMessageA(v43, 0x101Bu, 2u, (LPARAM)v59);
    ((CCBStageCam *)v65)->ApplyShake(hDlg);
    return 0;
  }
  if ( v67 != 273 )
    return 0;
  if ( (unsigned __int16)v68 > 0x417u )
  {
    switch ( (__int16)v68 )
    {
      case 1048:
        if ( v65[1].m_Task[13].fp[1] == (char *)-1
          || v65[1].m_Task[13].fp[2] == (char *)-1
          || !((CCBStageCam *)v65)->LerpToTarget() )
        {
          return 0;
        }
        ((CCBStageCam *)v65)->ClampViewAngle();
        ((CCBStageCam *)v65)->PopulateCameraListView();
        memset(lParam, 0, sizeof(lParam));
        v53 = (WPARAM)v65[1].m_Task[13].fp[2];
        lParam[0] = 1;
        lParam[1] = v53;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(v3, 0x102Bu, v53, (LPARAM)lParam);
        SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
        return 0;
      case 1049:
        if ( MessageBoxA(::hWnd, &unk_5D8A6C, "Warning", 4u) != 6 )
          return 0;
        v65[1].m_Task[13].fp[1] = (char *)-1;
        v65[1].m_Task[13].fp[2] = (char *)-1;
        sub_504F40();
        ((CCBStageCam *)v65)->UpdateSmooth();
        ((CCBStageCam *)v65)->PopulateCameraListView();
        goto LABEL_26;
      case 1050:
        if ( v65[1].m_Task[13].fp[1] == (char *)-1 )
          return 0;
        LOBYTE(v25) = ((CCBStageCam *)Buffer)->IsEditorCamValid((int)v65[1].m_Task[13].fp[1]);
        if ( v25 <= 0 || MessageBoxA(::hWnd, &unk_5D8A90, "Warning", 4u) != 6 )
          return 0;
        ((CCBStageCam *)Buffer)->DelEditorCam((int)v65[1].m_Task[13].fp[1]);
        ((CCBStageCam *)v65)->UpdateSmooth();
        ((CCBStageCam *)v65)->PopulateCameraListView();
        v26 = hWnd;
        memset(lParam, 0, sizeof(lParam));
        v52 = (WPARAM)v65[1].m_Task[13].fp[1];
        lParam[0] = 1;
        lParam[1] = v52;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(hWnd, 0x102Bu, v52, (LPARAM)lParam);
        SendMessageA(v26, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[1], 0);
        goto LABEL_25;
      case 1051:
        v22 = (int)v65[1].m_Task[13].fp[1];
        if ( v22 == -1 )
          return 0;
        v23 = (int)v65[1].m_Task[13].fp[2];
        if ( v23 == -1 )
          return 0;
        memset(pData, 0, sizeof(pData));
        pData[35] = 0;
        pData[37] = 0;
        LOBYTE(pData[5]) = 1;
        LOBYTE(pData[23]) = 1;
        LOWORD(pData[22]) = 257;
        pData[7] = 1065353216;
        pData[36] = 1112014848;
        pData[38] = 1120403456;
        pData[39] = 1120403456;
        pData[40] = 1120403456;
        ((CCBStageCam *)Buffer)->LoadEditorCam(v22, v23, pData);
        ((CCBStageCam *)v65)->UpdateSmooth();
        ((CCBStageCam *)v65)->PopulateCameraListView();
        ((CCCTData *)v65)->UpdateDebugDialog();
        v24 = hWnd;
        memset(lParam, 0, sizeof(lParam));
        v51 = (WPARAM)v65[1].m_Task[13].fp[1];
        lParam[0] = 1;
        lParam[1] = v51;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(hWnd, 0x102Bu, v51, (LPARAM)lParam);
        SendMessageA(v24, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[1], 0);
        lParam[1] = (LPARAM)v65[1].m_Task[13].fp[2];
        SendMessageA(v3, 0x102Bu, lParam[1], (LPARAM)lParam);
        SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
        return 0;
      case 1052:
        v27 = v65[1].m_Task[13].fp[1];
        if ( v27 == (char *)-1 )
          return 0;
        v28 = v65[1].m_Task[13].fp[2];
        if ( v28 == (char *)-1 )
          return 0;
        sub_5057B0((CCCTData *)Buffer, v27, v28);
        return 0;
      case 1086:
        v19 = SendMessageA(DlgItem, 0x1042u, 0, 0);
        v20 = v19;
        if ( v19 == -1 )
          return 0;
        ((CCBStage *)v57)->ClearTurnSlot(v19);
        memset(lParam, 0, sizeof(lParam));
        lParam[0] = 1;
        lParam[1] = v20;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[2] = 1;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, unk_5D8A38);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        lParam[2] = 2;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], g_szSceneUIText);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        if ( v20 > 0 )
          --v20;
        lParam[1] = v20;
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(DlgItem, 0x102Bu, v20, (LPARAM)lParam);
        SendMessageA(DlgItem, 0x1043u, v20, v20);
        SendMessageA(DlgItem, 0x1013u, v20, 0);
        return 0;
      case 1088:
        for ( i = 0; i < 63; ++i )
        {
          if ( ((CCBStage *)v57)->GetTurnSlotData(i) && ((CCBStage *)v57)->GetTurnSlotData(i + 1) )
            ((CCBSystem *)v57)->CastProtect(i, i + 1, 1.0);
        }
        return 0;
      case 1194:
        v29 = v65[1].m_Task[13].fp[1];
        if ( v29 == (char *)-1 )
          return 0;
        v30 = v65[1].m_Task[13].fp[2];
        if ( v30 == (char *)-1 )
          return 0;
        v31 = *((_DWORD *)&Buffer->fov + (_DWORD)&v30[50 * (_DWORD)v29 + 102500]);
        if ( v31 == -1 )
          return 0;
        v32 = &Buffer->fov + 51 * v31;
        if ( !v32 )
          return 0;
        if ( !*((_BYTE *)v32 + 88) )
          return 0;
        v33 = v57;
        v34 = (int)(v32 + 8);
        if ( !((CCBStage *)v57)->HasTurnChanged(v32 + 8) )
          return 0;
        goto LABEL_70;
      case 1195:
        v35 = v65[1].m_Task[13].fp[1];
        if ( v35 == (char *)-1 )
          return 0;
        v36 = v65[1].m_Task[13].fp[2];
        if ( v36 == (char *)-1 )
          return 0;
        v37 = *((_DWORD *)&Buffer->fov + (_DWORD)&v36[50 * (_DWORD)v35 + 102500]);
        if ( v37 == -1 )
          return 0;
        v38 = &Buffer->fov + 51 * v37;
        if ( !v38 )
          return 0;
        if ( !*((_BYTE *)v38 + 89) )
          return 0;
        v33 = v57;
        v34 = (int)(v38 + 14);
        if ( !((CCBStage *)v57)->HasTurnChanged(v38 + 14) )
          return 0;
LABEL_70:
        ((CCCTData *)v33)->CCCTData::UpdateCamera(v34);
        result = 0;
        break;
      default:
        return 0;
    }
  }
  else
  {
    if ( (unsigned __int16)v68 == 1047 )
    {
      return 0;
    }
    if ( (unsigned __int16)v68 <= 0x411u )
    {
      if ( (unsigned __int16)v68 == 1041 )
      {
        if ( v65[1].m_Task[13].fp[1] != (char *)-1 && v65[1].m_Task[13].fp[2] != (char *)-1 )
        {
          LOBYTE(v13) = ((CCBStageCam *)Buffer)->IsEditorCamValid((int)v65[1].m_Task[13].fp[1]);
          if ( v13 != 1 )
          {
            ((CCBStageCam *)Buffer)->SaveEditorCam((int)v65[1].m_Task[13].fp[1], (int)v65[1].m_Task[13].fp[2], (int)(v65[1].m_Task[13].fp[2] + 1));
            ++v65[1].m_Task[13].fp[2];
            ((CCBStageCam *)v65)->PopulateCameraListView();
            memset(lParam, 0, sizeof(lParam));
            v14 = (WPARAM)v65[1].m_Task[13].fp[2];
            lParam[3] = 3;
            lParam[4] = 3;
            lParam[0] = 1;
            lParam[1] = v14;
            lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
            SendMessageA(v3, 0x102Bu, v14, (LPARAM)lParam);
            SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
            return 0;
          }
        }
        return 0;
      }
      if ( (unsigned __int16)v68 <= 0x40Eu )
      {
        switch ( (unsigned __int16)v68 )
        {
          case 0x40Eu:
            if ( v65[1].m_Task[13].fp[1] != (char *)-1 )
            {
              ((CCBStageCam *)v65)->UpdateOrbit();
              ((CCBStageCam *)v65)->UpdateSmooth();
              ((CCBStageCam *)v65)->PopulateCameraListView();
              ((CCCTData *)v65)->UpdateDebugDialog();
              v6 = hWnd;
              memset(lParam, 0, sizeof(lParam));
              v49 = (WPARAM)v65[1].m_Task[13].fp[1];
              lParam[0] = 1;
              lParam[1] = v49;
              lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
              lParam[3] = 3;
              lParam[4] = 3;
              SendMessageA(hWnd, 0x102Bu, v49, (LPARAM)lParam);
              SendMessageA(v6, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[1], 0);
              return 0;
            }
            break;
          case 1u:
            EndDialog(hDlg, 1);
            return 0;
          case 0x40Du:
            FullConfig = ((CIniFile *)*(CIniFile **)(*(_DWORD *)(LODWORD(v65->fov) + 20) + 12))->LoadFullConfig();
            memset(lParam, 0, sizeof(lParam));
            lParam[0] = 1;
            lParam[1] = FullConfig;
            lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
            lParam[3] = 3;
            lParam[4] = 3;
            SendMessageA(DlgItem, 0x102Bu, FullConfig, (LPARAM)lParam);
            SendMessageA(DlgItem, 0x1043u, FullConfig, FullConfig);
            SendMessageA(DlgItem, 0x1013u, FullConfig, 0);
            SendMessageA(DlgItem, 7u, 0, 0);
            memset(lParam, 0, sizeof(lParam));
            lParam[0] = 1;
            lParam[1] = FullConfig;
            lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
            lParam[2] = 1;
            sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &unk_5D8A3C);
            SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
            lParam[2] = 2;
            sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], g_szSceneUIText);
            SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
            return 0;
        }
        return 0;
      }
      if ( (unsigned __int16)v68 != 1039 )
      {
        if ( (unsigned __int16)v68 == 1040 )
        {
          v7 = (int)v65[1].m_Task[13].fp[1];
          if ( v7 != -1 )
          {
            v8 = (int)v65[1].m_Task[13].fp[2];
            if ( v8 > 0 )
            {
              ((CCBStageCam *)Buffer)->SaveEditorCam(v7, v8, v8 - 1);
              --v65[1].m_Task[13].fp[2];
              ((CCBStageCam *)v65)->PopulateCameraListView();
              memset(lParam, 0, sizeof(lParam));
              v9 = (WPARAM)v65[1].m_Task[13].fp[2];
              lParam[3] = 3;
              lParam[4] = 3;
              lParam[0] = 1;
              lParam[1] = v9;
              lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
              SendMessageA(v3, 0x102Bu, v9, (LPARAM)lParam);
              SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
              return 0;
            }
          }
        }
        return 0;
      }
      v10 = (int)v65[1].m_Task[13].fp[1];
      if ( v10 != -1
        && v65[1].m_Task[13].fp[2] != (char *)-1
        && ((CCBStageCam *)Buffer)->AddCurCamToEditor(v10, (int)v65[1].m_Task[13].fp[2]) )
      {
        ((CCBStageCam *)v65)->UpdateSmooth();
        ((CCBStageCam *)v65)->PopulateCameraListView();
        v11 = hWnd;
        memset(lParam, 0, sizeof(lParam));
        v50 = (WPARAM)v65[1].m_Task[13].fp[1];
        lParam[0] = 1;
        lParam[1] = v50;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(hWnd, 0x102Bu, v50, (LPARAM)lParam);
        SendMessageA(v11, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[1], 0);
        lParam[1] = (LPARAM)v65[1].m_Task[13].fp[2];
        SendMessageA(v3, 0x102Bu, lParam[1], (LPARAM)lParam);
        SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
        LOBYTE(v12) = ((CCBStageCam *)Buffer)->IsEditorCamValid((int)v65[1].m_Task[13].fp[1]);
        if ( v12 )
LABEL_25:
          v65[1].m_Task[13].fp[2] = (char *)-1;
        goto LABEL_26;
      }
      return 0;
    }
    switch ( (__int16)v68 )
    {
      case 1042:
        v17 = (int)v65[1].m_Task[13].fp[1];
        if ( v17 == -1 )
          return 0;
        ((CCBCamControl *)&Buffer)->ClearFinishedTask(v17);
        result = 0;
        break;
      case 1044:
        v15 = SendMessageA(DlgItem, 0x1042u, 0, 0);
        v16 = v15;
        if ( v15 == -1 )
          return 0;
        ((CCBStage *)v57)->ClearTurnSlot(v15);
        memset(lParam, 0, sizeof(lParam));
        lParam[0] = 1;
        lParam[1] = v16;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[2] = 1;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, unk_5D8A38);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        lParam[2] = 2;
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], g_szSceneUIText);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(DlgItem, 0x102Bu, v16, (LPARAM)lParam);
        SendMessageA(DlgItem, 0x1013u, v16, 0);
        result = 0;
        break;
      case 1045:
        ((CCBCamControl *)&Buffer)->AddTask();
        result = 0;
        break;
      case 1046:
        fov = v65->fov;
        p_DWORD[0] = 0;
        p_DWORD[1] = 1112014848;
        p_DWORD[2] = 0;
        p_DWORD2[0] = 1120403456;
        p_DWORD2[1] = 1120403456;
        p_DWORD2[2] = 1120403456;
        result = 0;
        break;
      default:
        return 0;
    }
  }
  return result;
}

// 0x004E7060
LRESULT CCBStageCam::ApplyShake(HWND hDlg)
{
  HWND DlgItem; // ebx
  int i; // edi
  float fov; // eax
  int j; // edi
  float v8; // edx
  int v9; // eax
  WPARAM v10; // edx
  LRESULT result; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x14] [ebp-0x28] BYREF
  HWND hDlga; // [esp+0x40] [ebp+0x4]

  memset(lParam, 0, sizeof(lParam));
  hDlga = GetDlgItem(hDlg, 1150);
  DlgItem = GetDlgItem(hDlg, 1151);
  hWnd = GetDlgItem(hDlg, 1152);
  SendMessageA(hDlga, 0x1009u, 0, 0);
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  SendMessageA(hWnd, 0x1009u, 0, 0);
  for ( i = 0; i < 64; ++i )
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[1] = i;
    lParam[2] = 0;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], i);
    SendMessageA(hDlga, 0x1007u, 0, (LPARAM)lParam);
    fov = this->fov;
    lParam[2] = 1;
    if ( ((CCBStage *)*(CCBStage **)(*(_DWORD *)(LODWORD(fov) + 20) + 12))->GetTurnSlotData(i) )
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &unk_5D8A3C);
    else
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, unk_5D8A38);
    SendMessageA(hDlga, 0x1006u, 0, (LPARAM)lParam);
  }
  for ( j = 0; j < 100; ++j )
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[1] = j;
    lParam[2] = 0;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%03d", j);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    v8 = this->fov;
    lParam[2] = 1;
    LOBYTE(v9) = ((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(v8) + 20) + 16))->IsEditorCamValid(j);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v9);
    SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
  }
  v10 = *((_DWORD *)this + 2013);
  if ( v10 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[3] = 3;
    lParam[4] = 3;
    lParam[1] = v10;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    SendMessageA(DlgItem, 0x102Bu, v10, (LPARAM)lParam);
    SendMessageA(DlgItem, 0x1013u, *((_DWORD *)this + 2013), 0);
  }
  result = *((_DWORD *)this + 2014);
  if ( result != -1 )
  {
    lParam[1] = *((_DWORD *)this + 2014);
    SendMessageA(hWnd, 0x102Bu, result, (LPARAM)lParam);
    return SendMessageA(hWnd, 0x1013u, *((_DWORD *)this + 2014), 0);
  }
  return result;
}

// 0x004E7280
LRESULT CCBStageCam::UpdateSmooth()
{
  HWND DlgItem; // edi
  int i; // esi
  float fov; // edx
  int v5; // eax
  LRESULT result; // eax
  LPARAM lParam[10]; // [esp+0x10] [ebp-0x28] BYREF

  memset(lParam, 0, sizeof(lParam));
  DlgItem = GetDlgItem(g_hMainWnd, 1151);
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  for ( i = 0; i < 100; ++i )
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[1] = i;
    lParam[2] = 0;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%03d", i);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    fov = this->fov;
    lParam[2] = 1;
    LOBYTE(v5) = ((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(fov) + 20) + 16))->IsEditorCamValid(i);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v5);
    result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
  }
  return result;
}

// 0x004E7350
int CCBStageCam::PopulateCameraListView()
{
  HWND DlgItem; // ebp
  int result; // eax
  LPARAM v4; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // edi
  int i; // [esp+0x1C] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x20] [ebp-0x28] BYREF

  memset(lParam, 0, sizeof(lParam));
  DlgItem = GetDlgItem(g_hMainWnd, 1152);
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  result = *((_DWORD *)this + 2013);
  if ( result != -1 )
  {
    LOBYTE(result) = ((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16))->IsEditorCamValid(*((_DWORD *)this + 2013));
    v4 = 0;
    for ( i = result; v4 < i; ++v4 )
    {
      v5 = *(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16);
      v6 = *(_DWORD *)(v5 + 4 * (v4 + 10 * (5 * *((_DWORD *)this + 2013) + 10250)));
      if ( v6 == -1 )
        v7 = 0;
      else
        v7 = v5 + 204 * v6;
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      lParam[1] = v4;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v4);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%1.2f", *(float *)(v7 + 28));
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 2;
      if ( *(_BYTE *)(v7 + 92) )
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &unk_5D8AC4);
      if ( *(_BYTE *)(v7 + 93) )
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &unk_5D8ABC);
      if ( *(_BYTE *)(v7 + 94) )
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &unk_5D8AB4);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      result = i;
    }
  }
  return result;
}

// 0x004E74E0
void CCBStageCam::UpdateOrbit()
{
  int v1; // eax
  _DWORD pData[51]; // [esp+0x4] [ebp-CCh] BYREF

  memset(pData, 0, sizeof(pData));
  pData[7] = 1065353216;
  LOBYTE(pData[5]) = 1;
  LOBYTE(pData[23]) = 1;
  LOWORD(pData[22]) = 257;
  BYTE2(pData[22]) = 1;
  HIBYTE(pData[23]) = 1;
  v1 = *((_DWORD *)this + 2013);
  pData[35] = 0;
  pData[36] = 1112014848;
  pData[37] = 0;
  pData[38] = 1120403456;
  pData[39] = 1120403456;
  pData[40] = 1120403456;
  if ( v1 != -1 )
    ((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16))->Reset(v1, pData);
}

// 0x004E75E0
char CCBStageCam::ClampViewAngle()
{
  HWND v2; // edi
  HWND v3; // esi
  int v4; // ebp
  int v5; // eax
  int v6; // ebp
  CCBStage *v7; // esi
  int Int; // eax
  CCBStage *v9; // esi
  int v10; // eax
  int v11; // esi
  HWND v13; // [esp+0x10] [ebp-0x74]
  HWND hWnd; // [esp+0x14] [ebp-0x70]
  HWND DlgItem; // [esp+0x18] [ebp-0x6C]
  HWND v16; // [esp+0x1C] [ebp-0x68]
  HWND v17; // [esp+0x20] [ebp-0x64]
  HWND v18; // [esp+0x24] [ebp-0x60]
  HWND v19; // [esp+0x28] [ebp-0x5C]
  HWND v20; // [esp+0x2C] [ebp-0x58]
  HWND v21; // [esp+0x30] [ebp-0x54]
  HWND v22; // [esp+0x34] [ebp-0x50]
  HWND v23; // [esp+0x38] [ebp-0x4C]
  HWND v24; // [esp+0x3C] [ebp-0x48]
  HWND v25; // [esp+0x40] [ebp-0x44]
  HWND v26; // [esp+0x44] [ebp-0x40]
  HWND v27; // [esp+0x48] [ebp-0x3C]
  HWND v28; // [esp+0x4C] [ebp-0x38]
  HWND v29; // [esp+0x50] [ebp-0x34]
  HWND v30; // [esp+0x54] [ebp-0x30]
  HWND v31; // [esp+0x58] [ebp-0x2C]
  HWND v32; // [esp+0x5C] [ebp-0x28]
  HWND v33; // [esp+0x60] [ebp-0x24]
  HWND v34; // [esp+0x64] [ebp-0x20]
  HWND v35; // [esp+0x68] [ebp-0x1C]
  HWND v36; // [esp+0x6C] [ebp-0x18]
  HWND v37; // [esp+0x70] [ebp-0x14]
  HWND v38; // [esp+0x74] [ebp-0x10]
  HWND v39; // [esp+0x78] [ebp-0xC]
  HWND v40; // [esp+0x7C] [ebp-0x8]
  HWND v41; // [esp+0x80] [ebp-0x4]

  DlgItem = GetDlgItem(g_hMainWnd, 1185);
  hWnd = GetDlgItem(g_hMainWnd, 1187);
  v16 = GetDlgItem(g_hMainWnd, 1186);
  v17 = GetDlgItem(g_hMainWnd, 1174);
  v18 = GetDlgItem(g_hMainWnd, 1175);
  v2 = GetDlgItem(g_hMainWnd, 1164);
  v13 = GetDlgItem(g_hMainWnd, 1165);
  v19 = GetDlgItem(g_hMainWnd, 1199);
  v20 = GetDlgItem(g_hMainWnd, 1200);
  v21 = GetDlgItem(g_hMainWnd, 1178);
  v22 = GetDlgItem(g_hMainWnd, 1181);
  v23 = GetDlgItem(g_hMainWnd, 1166);
  v24 = GetDlgItem(g_hMainWnd, 1162);
  v25 = GetDlgItem(g_hMainWnd, 1177);
  v26 = GetDlgItem(g_hMainWnd, 1183);
  v27 = GetDlgItem(g_hMainWnd, 1182);
  v28 = GetDlgItem(g_hMainWnd, 1167);
  v29 = GetDlgItem(g_hMainWnd, 1184);
  v30 = GetDlgItem(g_hMainWnd, 1192);
  v31 = GetDlgItem(g_hMainWnd, 1193);
  v32 = GetDlgItem(g_hMainWnd, 1196);
  v33 = GetDlgItem(g_hMainWnd, 1171);
  v34 = GetDlgItem(g_hMainWnd, 1172);
  v35 = GetDlgItem(g_hMainWnd, 1173);
  v36 = GetDlgItem(g_hMainWnd, 1176);
  v37 = GetDlgItem(g_hMainWnd, 1179);
  v38 = GetDlgItem(g_hMainWnd, 1180);
  v39 = GetDlgItem(g_hMainWnd, 1191);
  v40 = GetDlgItem(g_hMainWnd, 1190);
  v41 = GetDlgItem(g_hMainWnd, 1202);
  v3 = GetDlgItem(g_hMainWnd, 1168);
  v4 = *(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16);
  v5 = *(_DWORD *)(v4 + 4 * (*((_DWORD *)this + 2014) + 10 * (5 * *((_DWORD *)this + 2013) + 10250)));
  if ( v5 != -1 )
  {
    v6 = v4 + 204 * v5;
    if ( v6 )
    {
      *(_BYTE *)(v6 + 93) = EditBox_IsModified(hWnd);
      *(_BYTE *)(v6 + 92) = EditBox_IsModified(DlgItem);
      *(_BYTE *)(v6 + 94) = EditBox_IsModified(v16);
      *(_BYTE *)(v6 + 88) = !EditBox_IsModified(v17);
      *(_BYTE *)(v6 + 89) = !EditBox_IsModified(v18);
      *(_DWORD *)(v6 + 80) = EditBox_GetInt(v2);
      *(_DWORD *)(v6 + 84) = EditBox_GetInt(v13);
      *(_BYTE *)(v6 + 91) = EditBox_IsModified(v19);
      *(_BYTE *)(v6 + 90) = EditBox_IsModified(v20);
      *(float *)(v6 + 132) = EditBox_GetFloat(v21);
      *(float *)(v6 + 136) = EditBox_GetFloat(v22);
      *(float *)(v6 + 108) = EditBox_GetFloat(v23);
      *(float *)(v6 + 28) = EditBox_GetFloat(v24);
      *(_BYTE *)(v6 + 97) = EditBox_IsModified(v25);
      *(_BYTE *)(v6 + 98) = EditBox_IsModified(v26);
      *(_BYTE *)(v6 + 99) = EditBox_IsModified(v27);
      *(float *)(v6 + 112) = EditBox_GetFloat(v28);
      *(_BYTE *)(v6 + 23) = EditBox_IsModified(v29);
      *(_BYTE *)(v6 + 101) = EditBox_IsModified(v30);
      *(_BYTE *)(v6 + 102) = EditBox_IsModified(v31);
      *(_DWORD *)(v6 + 104) = EditBox_GetInt(v32);
      *(float *)(v6 + 116) = EditBox_GetFloat(v33);
      *(float *)(v6 + 120) = EditBox_GetFloat(v34);
      *(float *)(v6 + 124) = EditBox_GetFloat(v35);
      *(float *)(v6 + 128) = EditBox_GetFloat(v36);
      *(float *)(v6 + 164) = EditBox_GetFloat(v37);
      *(float *)(v6 + 168) = EditBox_GetFloat(v38);
      *(_BYTE *)(v6 + 100) = EditBox_IsModified(v39);
      *(_BYTE *)(v6 + 96) = EditBox_IsModified(v40);
      *(_BYTE *)(v6 + 95) = EditBox_IsModified(v41);
      *(float *)(v6 + 172) = EditBox_GetFloat(v3);
      *(_DWORD *)(v6 + 140) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430228);
      *(_DWORD *)(v6 + 144) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430232);
      *(_DWORD *)(v6 + 148) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430236);
      *(_DWORD *)(v6 + 152) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430240);
      *(_DWORD *)(v6 + 156) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430244);
      *(_DWORD *)(v6 + 160) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430248);
      if ( *(_BYTE *)(v6 + 88) )
      {
        v7 = *(CCBStage **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12);
        Int = EditBox_GetInt(v2);
        if ( ((CCBStage *)v7)->GetTurnSlotData(Int) )
          qmemcpy(
            (void *)(v6 + 32),
            (const void *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12) + 24 * (EditBox_GetInt(v2) + 191)),
            0x18u);
        else
          *(_BYTE *)(v6 + 88) = 0;
      }
      v9 = *(CCBStage **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12);
      v10 = EditBox_GetInt(v13);
      LOBYTE(v5) = ((CCBStage *)v9)->GetTurnSlotData(v10);
      if ( (_BYTE)v5 )
      {
        v11 = *(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12);
        v5 = EditBox_GetInt(v13) + 191;
        qmemcpy((void *)(v6 + 56), (const void *)(v11 + 24 * v5), 0x18u);
      }
      else
      {
        *(_BYTE *)(v6 + 89) = 0;
      }
    }
  }
  return v5;
}

// 0x004E7B50
char CCBStageCam::LerpToTarget()
{
  HWND DlgItem; // edi
  HWND v2; // ebp
  HWND v3; // ebx

  if ( *((_DWORD *)this + 2013) == -1 || *((_DWORD *)this + 2014) == -1 )
    return 0;
  GetDlgItem(g_hMainWnd, 1185);
  GetDlgItem(g_hMainWnd, 1187);
  GetDlgItem(g_hMainWnd, 1186);
  GetDlgItem(g_hMainWnd, 1174);
  DlgItem = GetDlgItem(g_hMainWnd, 1175);
  GetDlgItem(g_hMainWnd, 1164);
  GetDlgItem(g_hMainWnd, 1165);
  v2 = GetDlgItem(g_hMainWnd, 1199);
  v3 = GetDlgItem(g_hMainWnd, 1200);
  GetDlgItem(g_hMainWnd, 1178);
  GetDlgItem(g_hMainWnd, 1181);
  GetDlgItem(g_hMainWnd, 1166);
  GetDlgItem(g_hMainWnd, 1162);
  GetDlgItem(g_hMainWnd, 1177);
  GetDlgItem(g_hMainWnd, 1183);
  GetDlgItem(g_hMainWnd, 1182);
  GetDlgItem(g_hMainWnd, 1167);
  GetDlgItem(g_hMainWnd, 1184);
  GetDlgItem(g_hMainWnd, 1192);
  GetDlgItem(g_hMainWnd, 1193);
  GetDlgItem(g_hMainWnd, 1196);
  GetDlgItem(g_hMainWnd, 1171);
  GetDlgItem(g_hMainWnd, 1172);
  GetDlgItem(g_hMainWnd, 1173);
  GetDlgItem(g_hMainWnd, 1176);
  GetDlgItem(g_hMainWnd, 1179);
  GetDlgItem(g_hMainWnd, 1180);
  GetDlgItem(g_hMainWnd, 1191);
  GetDlgItem(g_hMainWnd, 1190);
  GetDlgItem(g_hMainWnd, 1202);
  if ( !EditBox_IsModified(DlgItem) && EditBox_IsModified(v3) && EditBox_IsModified(v2) )
  {
    MessageBoxA(hWnd, &unk_5D8AD4, &unk_5D8AF4, 0);
    return 0;
  }
  return 1;
}

// 0x004E8450
int CCBStageCam::StoreCurrentView(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return ((CCBStageCam *)g_RoleSystemCombat.m_teamSlots[263])->UpdateStageCamera((float *)g_RoleSystemCombat.m_teamSlots[263], hDlg, uMsg, wParam, lParam);
}

// 0x004E8480
int CCBStageCam::UpdateStageCamera(
        
        float *pfVal,
        HWND hDlg,
        int nVal,
        int nVal2,
        int nVal3)
{
  HWND v7; // ebp
  WPARAM v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  WPARAM EffByID; // edx
  int v14; // esi
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  float *v18; // esi
  WPARAM v19; // eax
  WPARAM v20; // eax
  int v21; // eax
  WPARAM v22; // eax
  int v23; // ecx
  int v24; // eax
  int v25; // edi
  int v26; // esi
  int v27; // edx
  int v28; // eax
  char *i; // esi
  int v30; // edx
  int v31; // ecx
  int v32; // eax
  int v33; // ecx
  int v34; // ecx
  int v35; // eax
  CScreenMode *Instance; // eax
  int v37; // edx
  int v38; // eax
  int *v39; // ecx
  WPARAM v40; // eax
  int v41; // edx
  WPARAM v42; // eax
  LRESULT v43; // eax
  LRESULT v44; // eax
  LRESULT v45; // eax
  LRESULT v46; // eax
  LRESULT v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // eax
  WPARAM v58; // [esp-0x8] [ebp-0x6C]
  WPARAM v59; // [esp-0x8] [ebp-0x6C]
  WPARAM v60; // [esp-0x8] [ebp-0x6C]
  unsigned int v61; // [esp+0x0] [ebp-0x64]
  float v62; // [esp+0x4] [ebp-0x60]
  float v63; // [esp+0x8] [ebp-0x5C]
  int v64; // [esp+0xC] [ebp-0x58]
  HWND hWnd; // [esp+0x10] [ebp-0x54]
  HWND DlgItem; // [esp+0x14] [ebp-0x50]
  HWND v67; // [esp+0x18] [ebp-0x4C]
  LPARAM v68[8]; // [esp+0x1C] [ebp-0x48] BYREF
  LPARAM lParam[10]; // [esp+0x3C] [ebp-0x28] BYREF
  HWND hDlga; // [esp+0x6C] [ebp+0x8]

  DlgItem = GetDlgItem(hDlg, 1212);
  hWnd = GetDlgItem(hDlg, 1153);
  hDlga = GetDlgItem(hDlg, 1213);
  v7 = GetDlgItem(hDlg, 1214);
  v67 = GetDlgItem(hDlg, 1154);
  switch ( nVal )
  {
    case 78:
      switch ( nVal2 )
      {
        case 1153:
          v50 = *(_DWORD *)(nVal3 + 8);
          if ( v50 != -3 && v50 != -2 )
            return 0;
          v51 = *(_DWORD *)(nVal3 + 12);
          if ( v51 == -1 )
            pfVal[2016] = NAN;
          else
            *((_DWORD *)pfVal + 2016) = v51;
          return 0;
        case 1154:
          v56 = *(_DWORD *)(nVal3 + 8);
          if ( v56 != -3 && v56 != -2 )
            return 0;
          v57 = *(_DWORD *)(nVal3 + 12);
          if ( v57 != -1 )
          {
            *((_DWORD *)pfVal + 2019) = v57;
            ((CCBStageCam *)pfVal)->SetViewDistance(hDlg);
            return 0;
          }
          pfVal[2019] = NAN;
          ((CCBStageCam *)pfVal)->SetViewDistance(hDlg);
          break;
        case 1212:
          v48 = *(_DWORD *)(nVal3 + 8);
          if ( v48 != -3 && v48 != -2 )
            return 0;
          v49 = *(_DWORD *)(nVal3 + 12);
          if ( v49 == -1 )
            pfVal[2015] = NAN;
          else
            *((_DWORD *)pfVal + 2015) = v49;
          return 0;
        case 1213:
          v52 = *(_DWORD *)(nVal3 + 8);
          if ( v52 != -3 && v52 != -2 )
            return 0;
          v53 = *(_DWORD *)(nVal3 + 12);
          if ( v53 == -1 )
            pfVal[2017] = NAN;
          else
            *((_DWORD *)pfVal + 2017) = v53;
          ((CCBStageCam *)pfVal)->InterpolateAngle(hDlg);
          pfVal[2018] = NAN;
          pfVal[2019] = NAN;
          ((CCBStageCam *)pfVal)->UpdateFollowTarget(hDlg);
          ((CCBStageCam *)pfVal)->SetViewDistance(hDlg);
          return 0;
        case 1214:
          v54 = *(_DWORD *)(nVal3 + 8);
          if ( v54 != -3 && v54 != -2 )
            return 0;
          v55 = *(_DWORD *)(nVal3 + 12);
          if ( v55 == -1 )
            pfVal[2018] = NAN;
          else
            *((_DWORD *)pfVal + 2018) = v55;
          pfVal[2019] = NAN;
          ((CCBStageCam *)pfVal)->UpdateFollowTarget(hDlg);
          ((CCBStageCam *)pfVal)->SetViewDistance(hDlg);
          return 0;
        default:
          return 0;
      }
      break;
    case 272:
      SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
      v43 = SendMessageA(DlgItem, 0x1037u, 0, 0);
      LOBYTE(v43) = v43 | 0x21;
      SendMessageA(DlgItem, 0x1036u, 0, v43);
      memset(v68, 0, sizeof(v68));
      memset(lParam, 0, sizeof(lParam));
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 55;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)v68);
      v44 = SendMessageA(hWnd, 0x1037u, 0, 0);
      LOBYTE(v44) = v44 | 0x21;
      SendMessageA(hWnd, 0x1036u, 0, v44);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 24;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(hWnd, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 48;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(hWnd, 0x101Bu, 1u, (LPARAM)v68);
      v45 = SendMessageA(hDlga, 0x1037u, 0, 0);
      LOBYTE(v45) = v45 | 0x21;
      SendMessageA(hDlga, 0x1036u, 0, v45);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 25;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(hDlga, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 38;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(hDlga, 0x101Bu, 1u, (LPARAM)v68);
      v46 = SendMessageA(v7, 0x1037u, 0, 0);
      LOBYTE(v46) = v46 | 0x21;
      SendMessageA(v7, 0x1036u, 0, v46);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 25;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v7, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 48;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v7, 0x101Bu, 1u, (LPARAM)v68);
      v47 = SendMessageA(v67, 0x1037u, 0, 0);
      LOBYTE(v47) = v47 | 0x21;
      SendMessageA(v67, 0x1036u, 0, v47);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 25;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v67, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 0;
      v68[0] = 7;
      v68[2] = 25;
      v68[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v67, 0x101Bu, 1u, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 60;
      v68[3] = (LPARAM)&g_EffEditorState;
      SendMessageA(v67, 0x101Bu, 2u, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 60;
      v68[3] = (LPARAM)&g_pszEditorDesc;
      SendMessageA(v67, 0x101Bu, 3u, (LPARAM)v68);
      return 0;
    case 273:
      switch ( (__int16)nVal2 )
      {
        case 1042:
          if ( *((_DWORD *)pfVal + 2015) == -1 )
            return 0;
          pfVal[2016] = NAN;
          if ( *(_DWORD *)&g_RoleSystemCombat.m_bWPARAM_17A9926 )
            DestroyWindow(*(HWND *)&g_RoleSystemCombat.m_bWPARAM_17A9926);
          goto LABEL_8;
        case 1043:
          if ( *((_DWORD *)pfVal + 2016) == -1 )
            return 0;
          ((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44))->SetTimeScale(pfVal[2016]);
          ((CCBCamControl *)pfVal)->sub_4E9750(hDlg);
          return 0;
        case 1044:
          if ( *((_DWORD *)pfVal + 2016) == -1 )
            return 0;
          ((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44))->CreateEff(*((const char **)pfVal + 2016), v61, v62, v63, v64);
          ((CCBCamControl *)pfVal)->sub_4E9750(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v9 = *((_DWORD *)pfVal + 2016);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v9;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          SendMessageA(hWnd, 0x102Bu, v9, (LPARAM)lParam);
          SendMessageA(hWnd, 0x1013u, *((_DWORD *)pfVal + 2016), 0);
          return 0;
        case 1045:
          v14 = *((_DWORD *)pfVal + 2016);
          if ( v14 == -1 )
            return 0;
          v15 = *((_DWORD *)pfVal + 2017);
          if ( v15 == -1 )
            return 0;
          v16 = *(&g_nSaveSlot0 + 3985 * v15);
          if ( v16 >= 16 )
            return 0;
          v17 = 7 * v14;
          v18 = pfVal;
          *(&g_nSaveSlot1 + 3984 * v15 + v16 + v15) = *(_DWORD *)&g_EffTable[40 * v17 + 36];
          ++*(&g_nSaveSlot0 + 3985 * *((_DWORD *)pfVal + 2017));
          goto LABEL_25;
        case 1046:
          if ( *((_DWORD *)pfVal + 2018) == -1 )
            return 0;
          v21 = *((_DWORD *)pfVal + 2017);
          if ( v21 == -1 )
            return 0;
          sub_4CE7F0(v21, *((_DWORD *)pfVal + 2018));
          pfVal[2018] = NAN;
          ((CCBStageCam *)pfVal)->UpdateFollowTarget(hDlg);
          ((CCBStageCam *)pfVal)->InterpolateAngle(hDlg);
          ((CCBStageCam *)pfVal)->SetBlendWeight(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v22 = *((_DWORD *)pfVal + 2017);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v22;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          SendMessageA(hDlga, 0x102Bu, v22, (LPARAM)lParam);
          SendMessageA(hDlga, 0x1013u, *((_DWORD *)pfVal + 2017), 0);
          return 0;
        case 1052:
          v23 = *((_DWORD *)pfVal + 2018);
          if ( v23 == -1 )
            return 0;
          v24 = *((_DWORD *)pfVal + 2017);
          if ( v24 == -1 || *(&g_nSaveSlot0 + 3985 * v24) >= 16 )
            return 0;
          v18 = pfVal;
          sub_4CE8A0(v24, v23, *((_DWORD *)pfVal + 2016));
LABEL_25:
          ((CCBStageCam *)v18)->InterpolateAngle(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v19 = *((_DWORD *)v18 + 2018);
          lParam[0] = 1;
          lParam[1] = v19;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          lParam[3] = 3;
          lParam[4] = 3;
          SendMessageA(v7, 0x102Bu, v19, (LPARAM)lParam);
          SendMessageA(v7, 0x1013u, *((_DWORD *)pfVal + 2018), 0);
          ((CCBStageCam *)pfVal)->SetBlendWeight(hDlg);
          memset(lParam, 0, sizeof(lParam));
          lParam[3] = 3;
          v20 = *((_DWORD *)pfVal + 2017);
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v20;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          SendMessageA(hDlga, 0x102Bu, v20, (LPARAM)lParam);
          SendMessageA(hDlga, 0x1013u, *((_DWORD *)pfVal + 2017), 0);
          return 0;
        case 1053:
          if ( *((_DWORD *)pfVal + 2016) == -1 )
            return 0;
          if ( *(_DWORD *)&g_RoleSystemCombat.m_bWPARAM_17A9926 )
            DestroyWindow(*(HWND *)&g_RoleSystemCombat.m_bWPARAM_17A9926);
LABEL_8:
          *(_DWORD *)&g_RoleSystemCombat.m_bWPARAM_17A9926 = CreateDialogParamA(
                                                               hInstance,
                                                               (LPCSTR)0x70,
                                                               ::hWnd,
                                                               CCBStageCam_DlgProc,
                                                               0);
          ShowWindow(*(HWND *)&g_RoleSystemCombat.m_bWPARAM_17A9926, 5);
          return 0;
        case 1054:
          v10 = *((_DWORD *)pfVal + 2018);
          if ( v10 == -1 )
            return 0;
          v11 = *((_DWORD *)pfVal + 2017);
          if ( v11 == -1 )
            return 0;
          v12 = *(&g_nSaveSlot1 + 3984 * v11 + v10 + v11);
          if ( !v12 )
            return 0;
          EffByID = ((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44))->FindEffByID(v12);
          memset(lParam, 0, sizeof(lParam));
          lParam[3] = 3;
          lParam[4] = 3;
          *((_DWORD *)pfVal + 2016) = EffByID;
          lParam[0] = 1;
          lParam[1] = EffByID;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          SendMessageA(hWnd, 0x102Bu, EffByID, (LPARAM)lParam);
          SendMessageA(hWnd, 0x1013u, *((_DWORD *)pfVal + 2016), 0);
          return 0;
        case 1055:
          sub_4CE5C0(*(_DWORD *)(*(_DWORD *)pfVal + 44));
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->ApplyColorFilter();
          return 0;
        case 1057:
          if ( *((_DWORD *)pfVal + 2017) == -1 )
            return 0;
          ((CEffect *)*(CEffect **)(*(_DWORD *)pfVal + 44))->Render(*((_DWORD *)pfVal + 2017));
          ((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44))->Init(*((_DWORD *)pfVal + 2017), 0, 0, 0, 0);
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)pfVal + 44) + 43304) = 0;
          return 0;
        case 1059:
          v32 = *((_DWORD *)pfVal + 2018);
          if ( v32 == -1 )
            return 0;
          v33 = *((_DWORD *)pfVal + 2017);
          if ( v33 == -1 || v32 <= 0 )
            return 0;
          sub_4CE970(v33, v32, v32 - 1);
          --*((_DWORD *)pfVal + 2018);
          ((CCBStageCam *)pfVal)->InterpolateAngle(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v58 = *((_DWORD *)pfVal + 2018);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v58;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          SendMessageA(v7, 0x102Bu, v58, (LPARAM)lParam);
          SendMessageA(v7, 0x1013u, *((_DWORD *)pfVal + 2018), 0);
          return 0;
        case 1060:
          v34 = *((_DWORD *)pfVal + 2018);
          if ( v34 == -1 )
            return 0;
          v35 = *((_DWORD *)pfVal + 2017);
          if ( v35 == -1 || v34 < 0 || v34 + 1 >= *(&g_nSaveSlot0 + 3985 * v35) )
            return 0;
          sub_4CE970(v35, v34, v34 + 1);
          ++*((_DWORD *)pfVal + 2018);
          ((CCBStageCam *)pfVal)->InterpolateAngle(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v59 = *((_DWORD *)pfVal + 2018);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v59;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          SendMessageA(v7, 0x102Bu, v59, (LPARAM)lParam);
          SendMessageA(v7, 0x1013u, *((_DWORD *)pfVal + 2018), 0);
          return 0;
        case 1210:
          ((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44))->_CEffMgr();
          return 0;
        case 1211:
          if ( MessageBoxA(::hWnd, &unk_5D8B14, &unk_5D8B3C, 1u) != 1 )
            return 0;
          ((CCBStageCam *)pfVal)->sub_4E95A0(hDlg);
          return 0;
        case 1230:
          v25 = *((_DWORD *)pfVal + 2018);
          if ( v25 == -1 )
            return 0;
          v26 = *((_DWORD *)pfVal + 2017);
          if ( v26 == -1 )
            return 0;
          v27 = 0;
          v28 = 15940 * v26;
          for ( i = &byte_EC9F0C[15940 * v26 + 992 * v25]; *i; i += 124 )
          {
            if ( ++v27 >= 8 )
              return 0;
          }
          byte_EC9F0C[992 * v25 + 124 * v27 + v28] = 1;
          dword_EC9F00[3985 * *((_DWORD *)pfVal + 2017) + 248 * *((_DWORD *)pfVal + 2018) + 31 * v27] = 1065353216;
          ((CCBStageCam *)pfVal)->UpdateFollowTarget(hDlg);
          return 0;
        case 1231:
          v30 = *((_DWORD *)pfVal + 2018);
          if ( v30 == -1 )
            return 0;
          v31 = *((_DWORD *)pfVal + 2017);
          if ( v31 == -1 || *((_DWORD *)pfVal + 2019) == -1 )
            return 0;
          sub_4CEA40(v31, v30, *((_DWORD *)pfVal + 2019));
          pfVal[2019] = NAN;
          ((CCBStageCam *)pfVal)->UpdateFollowTarget(hDlg);
          return 0;
        case 1232:
          if ( *((_DWORD *)pfVal + 2017) == -1 || *((_DWORD *)pfVal + 2018) == -1 || *((_DWORD *)pfVal + 2019) == -1 )
          {
            MessageBoxA(::hWnd, &unk_5D8B44, "Warning", 0);
            return 0;
          }
          else
          {
            ((CCBStageCam *)pfVal)->CalculateFOV(hDlg);
            ((CCBStageCam *)pfVal)->UpdateFollowTarget(hDlg);
            return 0;
          }
        case 1237:
          ((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44))->ReleaseCompletedEffects();
          return 0;
        case 1238:
          v37 = *((_DWORD *)pfVal + 2017);
          if ( v37 == -1 )
            return 0;
          v38 = 0;
          v39 = &g_nSaveSlot0;
          break;
        case 1261:
          v41 = *((_DWORD *)pfVal + 2017);
          if ( v41 == -1 )
            return 0;
          memset((void *)(15940 * v41 + 15507056), 0, 0x3E44u);
          ((CCBStageCam *)pfVal)->SetBlendWeight(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v42 = *((_DWORD *)pfVal + 2017);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v42;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          SendMessageA(hDlga, 0x102Bu, v42, (LPARAM)lParam);
          SendMessageA(hDlga, 0x1013u, *((_DWORD *)pfVal + 2017), 0);
          ((CCBStageCam *)pfVal)->InterpolateAngle(hDlg);
          ((CCBStageCam *)pfVal)->UpdateFollowTarget(hDlg);
          return 0;
        default:
          return 0;
      }
      while ( *v39 )
      {
        v39 += 3985;
        ++v38;
        if ( (int)v39 >= (int)g_EffTable )
          return 0;
      }
      if ( v38 < 560 )
      {
        qmemcpy((void *)(15940 * v38 + 15507056), (const void *)(15940 * v37 + 15507056), 0x3E44u);
        *((_DWORD *)pfVal + 2017) = v38;
        ((CCBStageCam *)pfVal)->SetBlendWeight(hDlg);
        memset(lParam, 0, sizeof(lParam));
        v40 = *((_DWORD *)pfVal + 2017);
        lParam[0] = 1;
        lParam[1] = v40;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(hDlga, 0x102Bu, v40, (LPARAM)lParam);
        SendMessageA(hDlga, 0x1013u, *((_DWORD *)pfVal + 2017), 0);
        ((CCBStageCam *)pfVal)->InterpolateAngle(hDlg);
        memset(lParam, 0, sizeof(lParam));
        lParam[3] = 3;
        lParam[4] = 3;
        v60 = *((_DWORD *)pfVal + 2018);
        lParam[0] = 1;
        lParam[1] = v60;
        lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
        SendMessageA(v7, 0x102Bu, v60, (LPARAM)lParam);
        SendMessageA(v7, 0x1013u, *((_DWORD *)pfVal + 2018), 0);
        return 0;
      }
      break;
  }
  return 0;
}

// 0x004E95A0
int CCBStageCam::sub_4E95A0(HWND hDlg)
{
  int v4; // edi
  float fov; // eax
  int result; // eax
  WPARAM v7; // edx
  WPARAM v8; // edx
  HWND hWnd; // [esp+0x10] [ebp-0x34]
  HWND DlgItem; // [esp+0x14] [ebp-0x30]
  HWND v11; // [esp+0x18] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x1C] [ebp-0x28] BYREF
  HWND hDlga; // [esp+0x48] [ebp+0x4]

  hWnd = GetDlgItem(hDlg, 1212);
  DlgItem = GetDlgItem(hDlg, 1214);
  v11 = GetDlgItem(hDlg, 1213);
  memset(lParam, 0, sizeof(lParam));
  v4 = 0;
  SendMessageA(hWnd, 0x1009u, 0, 0);
  hDlga = 0;
  do
  {
    fov = this->fov;
    if ( *(_BYTE *)(*(_DWORD *)(LODWORD(this->fov) + 44) + v4 + 88) )
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      lParam[1] = (LPARAM)hDlga;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, *(_DWORD *)(LODWORD(fov) + 44) + v4 + 28);
      SendMessageA(hWnd, 0x1007u, 0, (LPARAM)lParam);
    }
    v4 += 72;
    hDlga = (HWND)((char *)hDlga + 1);
  }
  while ( v4 < 2304 );
  ((CCBCamControl *)this)->sub_4E9750(hDlg);
  this->SetBlendWeight(hDlg);
  this->InterpolateAngle(hDlg);
  result = this->UpdateFollowTarget(hDlg);
  v7 = *((_DWORD *)this + 2018);
  if ( v7 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[1] = v7;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[3] = 3;
    lParam[4] = 3;
    SendMessageA(DlgItem, 0x102Bu, v7, (LPARAM)lParam);
    result = SendMessageA(DlgItem, 0x1013u, *((_DWORD *)this + 2018), 0);
  }
  v8 = *((_DWORD *)this + 2017);
  if ( v8 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[1] = v8;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[3] = 3;
    lParam[4] = 3;
    SendMessageA(v11, 0x102Bu, v8, (LPARAM)lParam);
    return SendMessageA(v11, 0x1013u, *((_DWORD *)this + 2017), 0);
  }
  return result;
}

// 0x004E9890
LRESULT CCBStageCam::SetBlendWeight(HWND hDlg)
{
  HWND DlgItem; // ebx
  LPARAM v3; // esi
  int *v4; // edi
  int v5; // edx
  LRESULT result; // eax
  LPARAM lParam[10]; // [esp+0x10] [ebp-0x28] BYREF

  DlgItem = GetDlgItem(hDlg, 1213);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  v3 = 0;
  v4 = &g_nSaveSlot0;
  do
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[1] = v3;
    lParam[2] = 0;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%03d", v3);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    v5 = *v4;
    lParam[2] = 1;
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v5);
    result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    v4 += 3985;
    ++v3;
  }
  while ( (int)v4 < (int)g_EffTable );
  return result;
}

// 0x004E9950
LRESULT CCBStageCam::InterpolateAngle(HWND hDlg)
{
  HWND DlgItem; // esi
  LRESULT result; // eax
  int i; // edi
  int v6; // eax
  int v7; // eax
  int EffByID; // eax
  LPARAM lParam[10]; // [esp+0x10] [ebp-0x28] BYREF

  DlgItem = GetDlgItem(hDlg, 1214);
  memset(lParam, 0, sizeof(lParam));
  result = SendMessageA(DlgItem, 0x1009u, 0, 0);
  if ( *((_DWORD *)this + 2017) != -1 )
  {
    for ( i = 0; i < 16; ++i )
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      lParam[1] = i;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], i);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      v6 = *((_DWORD *)this + 2017);
      lParam[2] = 1;
      v7 = *(&g_nSaveSlot1 + 3984 * v6 + i + v6);
      if ( v7 )
      {
        EffByID = ((CEffMgr *)*(CEffMgr **)(LODWORD(this->fov) + 44))->FindEffByID(v7);
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, 280 * EffByID + 24433460);
      }
      else
      {
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "empty");
      }
      result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
  }
  return result;
}

// 0x004E9A70
LRESULT CCBStageCam::UpdateFollowTarget(HWND hDlg)
{
  LRESULT result; // eax
  int i; // esi
  int v5; // eax
  int v6; // edx
  int v7; // edx
  HWND hWnd; // [esp+0x14] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x18] [ebp-0x28] BYREF

  memset(lParam, 0, sizeof(lParam));
  hWnd = GetDlgItem(hDlg, 1154);
  SendMessageA(hWnd, 0x1009u, 0, 0);
  result = -1;
  if ( *((_DWORD *)this + 2017) != -1 && *((_DWORD *)this + 2018) != -1 )
  {
    for ( i = 0; i < 8; ++i )
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      lParam[1] = i;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], i);
      SendMessageA(hWnd, 0x1007u, 0, (LPARAM)lParam);
      v5 = *((_DWORD *)this + 2018);
      lParam[2] = 1;
      if ( byte_EC9F0C[15940 * *((_DWORD *)this + 2017) + 992 * v5 + 124 * i] )
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "o");
      else
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "x");
      SendMessageA(hWnd, 0x1006u, 0, (LPARAM)lParam);
      v6 = *((_DWORD *)this + 2018);
      lParam[2] = 2;
      sprintf(
        (char *const)&g_RoleSystemCombat.m_teamSlots[264],
        "%0.2f",
        *(float *)&g_nSaveSlotBase[3985 * *((_DWORD *)this + 2017) + 18 + 248 * v6 + 31 * i]);
      SendMessageA(hWnd, 0x1006u, 0, (LPARAM)lParam);
      v7 = *((_DWORD *)this + 2018);
      lParam[2] = 3;
      sprintf(
        (char *const)&g_RoleSystemCombat.m_teamSlots[264],
        "%0.2f",
        *(float *)&dword_EC9F00[3985 * *((_DWORD *)this + 2017) + 248 * v7 + 31 * i]);
      result = SendMessageA(hWnd, 0x1006u, 0, (LPARAM)lParam);
    }
  }
  return result;
}

// 0x004E9C50
char CCBStageCam::SetViewDistance(HWND hDlg)
{
  char result; // al
  HWND v5; // ebp
  HWND v6; // edi
  int v7; // ecx
  int *v8; // esi
  BOOL v9; // edx
  BOOL v10; // ecx
  HWND DlgItem; // [esp+0x10] [ebp-0x54]
  HWND v12; // [esp+0x14] [ebp-0x50]
  HWND v13; // [esp+0x18] [ebp-0x4C]
  HWND v14; // [esp+0x1C] [ebp-0x48]
  HWND v15; // [esp+0x20] [ebp-0x44]
  HWND v16; // [esp+0x24] [ebp-0x40]
  HWND v17; // [esp+0x28] [ebp-0x3C]
  HWND v18; // [esp+0x2C] [ebp-0x38]
  HWND v19; // [esp+0x30] [ebp-0x34]
  HWND v20; // [esp+0x34] [ebp-0x30]
  HWND v21; // [esp+0x38] [ebp-0x2C]
  HWND v22; // [esp+0x3C] [ebp-0x28]
  HWND v23; // [esp+0x40] [ebp-0x24]
  HWND v24; // [esp+0x44] [ebp-0x20]
  HWND v25; // [esp+0x48] [ebp-0x1C]
  HWND v26; // [esp+0x4C] [ebp-0x18]
  HWND v27; // [esp+0x50] [ebp-0x14]
  HWND v28; // [esp+0x54] [ebp-0x10]
  HWND v29; // [esp+0x58] [ebp-0xC]
  HWND hWnd; // [esp+0x5C] [ebp-0x8]
  HWND v31; // [esp+0x60] [ebp-0x4]
  HWND hDlga; // [esp+0x68] [ebp+0x4]

  result = -1;
  if ( *((_DWORD *)this + 2017) != -1 && *((_DWORD *)this + 2018) != -1 && *((_DWORD *)this + 2019) != -1 )
  {
    this->UpdateTransition(hDlg);
    hDlga = GetDlgItem(hDlg, 1207);
    DlgItem = GetDlgItem(hDlg, 1209);
    v12 = GetDlgItem(hDlg, 1215);
    v13 = GetDlgItem(hDlg, 1216);
    v14 = GetDlgItem(hDlg, 1218);
    v15 = GetDlgItem(hDlg, 1226);
    v16 = GetDlgItem(hDlg, 1227);
    v17 = GetDlgItem(hDlg, 1225);
    v18 = GetDlgItem(hDlg, 1236);
    v19 = GetDlgItem(hDlg, 1228);
    v20 = GetDlgItem(hDlg, 1234);
    v21 = GetDlgItem(hDlg, 1235);
    v5 = GetDlgItem(hDlg, 1208);
    v22 = GetDlgItem(hDlg, 1217);
    v23 = GetDlgItem(hDlg, 1219);
    v24 = GetDlgItem(hDlg, 1220);
    v25 = GetDlgItem(hDlg, 1221);
    v26 = GetDlgItem(hDlg, 1224);
    v27 = GetDlgItem(hDlg, 1162);
    v28 = GetDlgItem(hDlg, 1222);
    v29 = GetDlgItem(hDlg, 1223);
    hWnd = GetDlgItem(hDlg, 1229);
    v31 = GetDlgItem(hDlg, 1233);
    v6 = GetDlgItem(hDlg, 1163);
    v7 = 3985 * *((_DWORD *)this + 2017);
    result = byte_EC9F0C[992 * *((_DWORD *)this + 2018) + 124 * *((_DWORD *)this + 2019) + v7 * 4];
    v8 = &g_nSaveSlotBase[248 * *((_DWORD *)this + 2018) + 31 * *((_DWORD *)this + 2019) + v7];
    if ( result )
    {
      EditBox_SetFloat(hDlga, *(float *)v8);
      EditBox_SetFloat(v5, *((float *)v8 + 4));
      EditBox_SetFloat(DlgItem, *((float *)v8 + 1));
      EditBox_SetFloat(v12, *((float *)v8 + 2));
      EditBox_SetFloat(v13, *((float *)v8 + 3));
      EditBox_SetFloat(v14, *((float *)v8 + 5));
      EditBox_SetFloat(v15, *((float *)v8 + 6));
      EditBox_SetFloat(v16, *((float *)v8 + 7));
      EditBox_SetFloat(v17, *((float *)v8 + 8));
      EditBox_SetFloat(v18, *((float *)v8 + 9));
      EditBox_SetFloat(v19, *((float *)v8 + 10));
      EditBox_SetFloat(v20, *((float *)v8 + 11));
      EditBox_SetFloat(v21, *((float *)v8 + 12));
      EditBox_SetFloat(v5, *((float *)v8 + 13));
      EditBox_SetFloat(v22, *((float *)v8 + 14));
      EditBox_SetFloat(v23, *((float *)v8 + 15));
      EditBox_SetFloat(v24, *((float *)v8 + 16));
      EditBox_SetFloat(v25, *((float *)v8 + 17));
      EditBox_SetFloat(v26, *((float *)v8 + 18));
      EditBox_SetFloat(v27, *((float *)v8 + 19));
      EditBox_SetFloat(v28, *((float *)v8 + 21));
      EditBox_SetInt(v29, v8[20]);
      LOBYTE(v9) = *((_BYTE *)v8 + 89);
      EditBox_SetReadOnly(hWnd, v9);
      LOBYTE(v10) = *((_BYTE *)v8 + 90);
      EditBox_SetReadOnly(v31, v10);
      return EditBox_SetFloat(v6, *((float *)v8 + 23));
    }
  }
  return result;
}

// 0x004E9F70
void CCBStageCam::CalculateFOV(HWND hDlg)
{
  HWND v4; // ebp
  HWND v5; // eax
  int v6; // ecx
  HWND v7; // edi
  int *v8; // esi
  const char *v9; // ebx
  HWND DlgItem; // [esp+0x10] [ebp-0x54]
  HWND v11; // [esp+0x14] [ebp-0x50]
  HWND v12; // [esp+0x18] [ebp-0x4C]
  HWND v13; // [esp+0x1C] [ebp-0x48]
  HWND v14; // [esp+0x20] [ebp-0x44]
  HWND v15; // [esp+0x24] [ebp-0x40]
  HWND v16; // [esp+0x28] [ebp-0x3C]
  HWND v17; // [esp+0x2C] [ebp-0x38]
  HWND v18; // [esp+0x30] [ebp-0x34]
  HWND v19; // [esp+0x34] [ebp-0x30]
  HWND v20; // [esp+0x38] [ebp-0x2C]
  HWND v21; // [esp+0x3C] [ebp-0x28]
  HWND v22; // [esp+0x40] [ebp-0x24]
  HWND v23; // [esp+0x44] [ebp-0x20]
  HWND v24; // [esp+0x48] [ebp-0x1C]
  HWND v25; // [esp+0x4C] [ebp-0x18]
  HWND v26; // [esp+0x50] [ebp-0x14]
  HWND v27; // [esp+0x54] [ebp-0x10]
  HWND v28; // [esp+0x58] [ebp-0xC]
  HWND hWnd; // [esp+0x5C] [ebp-0x8]
  HWND v30; // [esp+0x60] [ebp-0x4]
  HWND hDlga; // [esp+0x68] [ebp+0x4]

  if ( *((_DWORD *)this + 2017) != -1 && *((_DWORD *)this + 2018) != -1 && *((_DWORD *)this + 2019) != -1 )
  {
    hDlga = GetDlgItem(hDlg, 1207);
    DlgItem = GetDlgItem(hDlg, 1209);
    v11 = GetDlgItem(hDlg, 1215);
    v12 = GetDlgItem(hDlg, 1216);
    v13 = GetDlgItem(hDlg, 1218);
    v14 = GetDlgItem(hDlg, 1226);
    v15 = GetDlgItem(hDlg, 1227);
    v16 = GetDlgItem(hDlg, 1225);
    v17 = GetDlgItem(hDlg, 1236);
    v18 = GetDlgItem(hDlg, 1228);
    v19 = GetDlgItem(hDlg, 1234);
    v20 = GetDlgItem(hDlg, 1235);
    v4 = GetDlgItem(hDlg, 1208);
    v21 = GetDlgItem(hDlg, 1217);
    v22 = GetDlgItem(hDlg, 1219);
    v23 = GetDlgItem(hDlg, 1220);
    v24 = GetDlgItem(hDlg, 1221);
    v25 = GetDlgItem(hDlg, 1224);
    v26 = GetDlgItem(hDlg, 1162);
    v27 = GetDlgItem(hDlg, 1222);
    v28 = GetDlgItem(hDlg, 1223);
    hWnd = GetDlgItem(hDlg, 1229);
    v30 = GetDlgItem(hDlg, 1233);
    v5 = GetDlgItem(hDlg, 1163);
    v6 = *((_DWORD *)this + 2018);
    v7 = v5;
    v8 = &g_nSaveSlotBase[3985 * *((_DWORD *)this + 2017) + 248 * v6 + 31 * *((_DWORD *)this + 2019)];
    if ( *((_BYTE *)v8 + 88) )
    {
      v9 = (const char *)*(&g_nSaveSlot1 + 3984 * *((_DWORD *)this + 2017) + v6 + *((_DWORD *)this + 2017));
      *(float *)v8 = EditBox_GetFloat(hDlga);
      *((float *)v8 + 4) = EditBox_GetFloat(v4);
      *((float *)v8 + 1) = EditBox_GetFloat(DlgItem);
      *((float *)v8 + 2) = EditBox_GetFloat(v11);
      *((float *)v8 + 3) = EditBox_GetFloat(v12);
      *((float *)v8 + 5) = EditBox_GetFloat(v13);
      *((float *)v8 + 6) = EditBox_GetFloat(v14);
      *((float *)v8 + 7) = EditBox_GetFloat(v15);
      *((float *)v8 + 8) = EditBox_GetFloat(v16);
      *((float *)v8 + 9) = EditBox_GetFloat(v17);
      *((float *)v8 + 10) = EditBox_GetFloat(v18);
      *((float *)v8 + 11) = EditBox_GetFloat(v19);
      *((float *)v8 + 12) = EditBox_GetFloat(v20);
      *((float *)v8 + 13) = EditBox_GetFloat(v4);
      *((float *)v8 + 14) = EditBox_GetFloat(v21);
      *((float *)v8 + 15) = EditBox_GetFloat(v22);
      *((float *)v8 + 16) = EditBox_GetFloat(v23);
      *((float *)v8 + 17) = EditBox_GetFloat(v24);
      *((float *)v8 + 18) = EditBox_GetFloat(v25);
      *((float *)v8 + 19) = EditBox_GetFloat(v26);
      *((float *)v8 + 21) = EditBox_GetFloat(v27);
      v8[20] = EditBox_GetInt(v28);
      *((_BYTE *)v8 + 89) = EditBox_IsModified(hWnd);
      *((_BYTE *)v8 + 90) = EditBox_IsModified(v30);
      *((float *)v8 + 23) = EditBox_GetFloat(v7);
      if ( (byte_1895559 & 1) == 0 )
      {
        byte_1895559 |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      if ( v9 == ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)&pTarget._todo_06C)
        && *((_BYTE *)v8 + 89)
        && *((float *)v8 + 21) < 0.029999999 )
      {
        MessageBoxA(::hWnd, &unk_5D8B88, "Warning", 0);
      }
    }
  }
}

// 0x004EA2E0
LRESULT CCBStageCam::UpdateTransition(HWND hDlg)
{
  LRESULT result; // eax
  int EffByID; // eax
  int v5; // esi
  int v6; // edi
  HWND *v7; // ebp
  int v8; // ecx
  LPARAM v9; // eax
  _DWORD v10[24]; // [esp+0xC] [ebp-0x60] BYREF

  v10[0] = GetDlgItem(hDlg, 1239);
  v10[1] = GetDlgItem(hDlg, 1240);
  v10[2] = GetDlgItem(hDlg, 1241);
  v10[3] = GetDlgItem(hDlg, 1242);
  v10[4] = GetDlgItem(hDlg, 1243);
  v10[5] = GetDlgItem(hDlg, 1244);
  v10[6] = GetDlgItem(hDlg, 1245);
  v10[7] = GetDlgItem(hDlg, 1246);
  v10[8] = GetDlgItem(hDlg, 1247);
  v10[9] = GetDlgItem(hDlg, 1248);
  v10[10] = GetDlgItem(hDlg, 1249);
  v10[11] = GetDlgItem(hDlg, 1250);
  v10[12] = GetDlgItem(hDlg, 1251);
  v10[13] = GetDlgItem(hDlg, 1252);
  v10[14] = GetDlgItem(hDlg, 1253);
  v10[15] = GetDlgItem(hDlg, 1254);
  v10[16] = GetDlgItem(hDlg, 1255);
  v10[17] = GetDlgItem(hDlg, 1256);
  v10[18] = GetDlgItem(hDlg, 1257);
  v10[19] = GetDlgItem(hDlg, 1258);
  v10[20] = GetDlgItem(hDlg, 1259);
  v10[21] = GetDlgItem(hDlg, 1260);
  v10[22] = GetDlgItem(hDlg, 1233);
  v10[23] = GetDlgItem(hDlg, 1229);
  result = *(&g_nSaveSlot1 + 3985 * *((_DWORD *)this + 2017) + *((_DWORD *)this + 2018));
  if ( result )
  {
    EffByID = ((CEffMgr *)*(CEffMgr **)(LODWORD(this->fov) + 44))->FindEffByID(result);
    v5 = 0;
    v6 = 72 * ((CEffMgr *)*(CEffMgr **)(LODWORD(this->fov) + 44))->FindEffSlot(*(_DWORD *)&g_EffTable[280 * EffByID]);
    v7 = (HWND *)v10;
    do
    {
      v8 = *(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 44) + v6 + 96);
      v9 = (*(int ( **)(int, int))(*(_DWORD *)v8 + 56))(v8, v5);
      result = ((CCBUI *)*v7)->SendWindowMessage(v9);
      ++v5;
      ++v7;
    }
    while ( v5 < 24 );
  }
  return result;
}

// 0x00504DD0
CCBStage * CCBStageCam::ResetViewport()
{
  int v2; // edx
  float *p_minz; // eax

  v2 = 2000;
  p_minz = &this->Viewport.minz;
  do
  {
    *(p_minz - 2) = 0.0;
    *(p_minz - 1) = 0.0;
    *p_minz = 0.0;
    p_minz[1] = 0.0;
    p_minz[2] = 0.0;
    p_minz[3] = 0.0;
    p_minz[4] = 0.0;
    p_minz[5] = 0.0;
    p_minz[6] = 0.0;
    p_minz[7] = 0.0;
    p_minz[8] = 0.0;
    p_minz[9] = 0.0;
    p_minz += 51;
    --v2;
  }
  while ( v2 );
  ((CCBStage *)this)->ClearAll();
  return (CCBStage *)this;
}

// 0x00504E60
char CCBStageCam::_CCBStageCam()
{
  sub_504F40();
  return 1;
}

// 0x00504E70
CCBStageCam::CCBStageCam(CCBStageCam *Buffer)
{
  FILE *v3; // esi
  float *p_yw; // eax
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x800] BYREF
  char ArgList; // [esp+0x408] [ebp-0x400] BYREF

  v3 = fopen("basedata\\cbdata\\flexcam.dat", Mode);
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(aCouldnTOpenCbC, aDProjectPal3Co_3, 702),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  p_yw = &this->ViewMatrix.yw;
  v5 = 2000;
  do
  {
    p_yw[1] = 50.0;
    *p_yw = 50.0;
    p_yw += 51;
    --v5;
  }
  while ( v5 );
  fseek(v3, 0, 0);
  fwrite(this, 0x639C0u, 1u, v3);
  fwrite((char *)this + 408000, 0x7D0u, 1u, v3);
  fwrite((char *)this + 410000, 0x4E20u, 1u, v3);
  fclose(v3);
}

// 0x00505060
void CCBStageCam::Reset(int nVal, const void *pData)
{
  int v4; // eax
  int v5; // esi
  int v6; // eax

  LOBYTE(v4) = this->IsCamValid();
  v5 = v4;
  LOBYTE(v6) = this->IsEditorCamValid(nVal);
  if ( v5 != -1 && v6 < 50 )
  {
    *((_DWORD *)this + 50 * nVal + v6 + 102500) = v5;
    *((_BYTE *)this + v5 + 408000) = 1;
    qmemcpy((char *)this + 204 * v5, pData, 0xCCu);
  }
}

// 0x005050D0
void CCBStageCam::LoadEditorCam(int nVal, int nVal2, const void *pData)
{
  int v5; // eax
  int v6; // eax
  _DWORD *v7; // edx
  int v8; // ecx

  LOBYTE(v5) = this->IsEditorCamValid(nVal);
  if ( nVal2 < v5 )
  {
    if ( v5 < 50 )
    {
      LOBYTE(v6) = this->IsCamValid();
      if ( v6 != -1 )
      {
        if ( nVal2 < 49 )
        {
          v7 = (_DWORD *)((char *)this + 200 * nVal + 410196);
          v8 = 49 - nVal2;
          do
          {
            *v7 = *(v7 - 1);
            --v7;
            --v8;
          }
          while ( v8 );
        }
        *((_DWORD *)this + 50 * nVal + nVal2 + 102500) = v6;
        *((_BYTE *)this + v6 + 408000) = 1;
        qmemcpy((char *)this + 204 * v6, pData, 0xCCu);
      }
    }
  }
  else
  {
    this->Reset(nVal, pData);
  }
}

// 0x00505180
void CCBStageCam::SaveEditorCam(int nVal, int nVal2, int nVal3)
{
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  _DWORD *v9; // eax

  LOBYTE(v5) = this->IsEditorCamValid(nVal);
  if ( nVal2 < v5 && nVal3 < v5 && nVal2 != nVal3 )
  {
    v6 = 10 * (5 * nVal + 10250);
    v7 = v6 + nVal2;
    v8 = *((_DWORD *)&this->fov + v6 + nVal2);
    v9 = (_DWORD *)(&this->fov + nVal3 + v6);
    *((_DWORD *)&this->fov + v7) = *v9;
    *v9 = v8;
  }
}

// 0x005051E0
char CCBStageCam::AddCurCamToEditor(int nVal, int nVal2)
{
  int v4; // eax
  int v6; // eax
  _DWORD *v7; // eax
  int v8; // edx

  LOBYTE(v4) = this->IsEditorCamValid(nVal);
  if ( nVal2 >= v4 )
    return 0;
  v6 = 10 * (5 * nVal + 10250);
  *((_BYTE *)this + *((_DWORD *)&this->fov + v6 + nVal2) + 408000) = 0;
  if ( nVal2 == 49 )
  {
    *((_DWORD *)this + 50 * nVal + 102549) = -1;
    return 1;
  }
  else
  {
    if ( nVal2 < 49 )
    {
      v7 = (_DWORD *)(&this->fov + v6 + nVal2);
      v8 = 49 - nVal2;
      do
      {
        *v7 = v7[1];
        ++v7;
        --v8;
      }
      while ( v8 );
    }
    return 1;
  }
}

// 0x00505250
void CCBStageCam::DelEditorCam(int nCamIndex)
{
  int v2; // edx
  int *v3; // eax
  int v4; // esi

  v2 = 50;
  v3 = (int *)((char *)this + 200 * nCamIndex + 410000);
  do
  {
    v4 = *v3++;
    --v2;
    *((_BYTE *)this + v4 + 408000) = 0;
    *(v3 - 1) = -1;
  }
  while ( v2 );
}

// 0x00505290
bool CCBStageCam::IsEditorCamValid(int nCamIndex)
{
  bool result; // al
  int v3; // edx
  _DWORD *v4; // ecx

  result = 0;
  v3 = 0;
  v4 = (_DWORD *)((char *)this + 200 * nCamIndex + 410000);
  do
  {
    if ( *v4 == -1 )
      break;
    ++result;
    ++v3;
    ++v4;
  }
  while ( v3 < 50 );
  return result;
}

// 0x005052C0
bool CCBStageCam::IsCamValid()
{
  int v1; // eax

  v1 = 0;
  while ( *((_BYTE *)this + v1 + 408000) )
  {
    if ( ++v1 >= 2000 )
    {
      LOBYTE(v1) = -1;
      return v1;
    }
  }
  return v1;
}

// 0x00505410
bool CCBStageCam::Create()
{
  *((_DWORD *)this + 107504) = 0;
  *((_DWORD *)this + 107505) = 0;
  *((_BYTE *)this + 430012) = 0;
  *((_DWORD *)this + 107519) = 0;
  *((_DWORD *)this + 107506) = 0;
  *((_DWORD *)this + 107557) = 0;
  *((_DWORD *)this + 107559) = 0;
  *((_DWORD *)this + 107507) = -1;
  *((_DWORD *)this + 107508) = -1;
  *((_DWORD *)this + 107509) = -1;
  *((_DWORD *)this + 107520) = 1065353216;
  *((_DWORD *)this + 107521) = 1117782016;
  *((_DWORD *)this + 107558) = 1112014848;
  *((_DWORD *)this + 107560) = 1120403456;
  *((_DWORD *)this + 107561) = 1120403456;
  *((_DWORD *)this + 107562) = 1120403456;
  return 0;
}

// 0x00505490
bool CCBStageCam::Destroy()
{

  sub_504F40();
  ((CCCTData *)this)->Destroy();
  return 1;
}

// 0x005054E0
void CCBStageCam::Update()
{

}
