#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBCamControl.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Combat/CCCTData.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffSParticle.h"
#include "Effect/CEffect.h"
#include "Render/CScreenMode.h"
#include "GameBase/Logger.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Misc/tagEffMgrData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4CE5C0(...);
int sub_4CE7F0(...);
int sub_4CE8A0(...);
int sub_4CE970(...);
int sub_4CEA40(...);
int sub_5057B0(...);

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
  Buffer = (CCBStageCam *)*(CCBStageCam **)(v1 + 16);
  v57 = (CCBStage *)*(CCBStage **)(v1 + 12);
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
        if ( (v48 == -3 || v48 == -2 && EditBoxIsModified(v61))
          && *(_DWORD *)(v69 + 12) != -1
          && (((CCBStage *)v57))->CCBStage::GetTurnSlotData(*(_DWORD *)(v69 + 12)) )
        {
          (((CCCTData *)*(_DWORD *)(v69 + 12)))->UpdateCamera();
        }
        return 0;
      case 1151:
        v46 = *(_DWORD *)(v69 + 8);
        if ( v46 != -3 && v46 != -2 )
          return 0;
        v47 = (char *)*(char **)(v69 + 12);
        if ( v47 == (char *)-1 )
          return 0;
        v65[1].m_Task[13].fp[1] = v47;
        v65[1].m_Task[13].fp[2] = (char *)-1;
        (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
        break;
      case 1152:
        v44 = *(_DWORD *)(v69 + 8);
        if ( v44 != -3 && v44 != -2 )
          return 0;
        v45 = (char *)*(char **)(v69 + 12);
        if ( v45 == (char *)-1 )
          return 0;
        v65[1].m_Task[13].fp[2] = v45;
        break;
      default:
        return 0;
    }
LABEL_26:
    (((CCCTData *)v65))->CCCTData::UpdateDebugDialog();
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
    v59[3] = (LPARAM)&unk_5D88F4;
    SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 38;
    v59[3] = (LPARAM)&unk_5D8A64;
    SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 49;
    v59[3] = (LPARAM)&unk_5D8A5C;
    SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)v59);
    v42 = hWnd;
    v59[0] = 7;
    v59[1] = 0;
    v59[2] = 25;
    v59[3] = (LPARAM)&unk_5D8A58;
    SendMessageA(hWnd, 0x101Bu, 0, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 38;
    v59[3] = (LPARAM)&unk_5D8A50;
    SendMessageA(v42, 0x101Bu, 1u, (LPARAM)v59);
    v59[0] = 7;
    v43 = v60;
    v59[1] = 0;
    v59[2] = 25;
    v59[3] = (LPARAM)&unk_5D8A58;
    SendMessageA(v60, 0x101Bu, 0, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 48;
    v59[3] = (LPARAM)&unk_5D8A48;
    SendMessageA(v43, 0x101Bu, 1u, (LPARAM)v59);
    v59[1] = 1;
    v59[2] = 40;
    v59[3] = (LPARAM)&unk_5D8A40;
    SendMessageA(v43, 0x101Bu, 2u, (LPARAM)v59);
    (((CCBStageCam *)v65))->CCBStageCam::ApplyShake(hDlg);
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
          || !(((CCBStageCam *)v65))->CCBStageCam::LerpToTarget() )
        {
          return 0;
        }
        (((CCBStageCam *)v65))->CCBStageCam::ClampViewAngle();
        (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
        memset(lParam, 0, sizeof(lParam));
        v53 = (WPARAM)v65[1].m_Task[13].fp[2];
        lParam[0] = 1;
        lParam[1] = v53;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(v3, 0x102Bu, v53, (LPARAM)lParam);
        SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
        return 0;
      case 1049:
        if ( MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8A6C, aWarning, 4u) != 6 )
          return 0;
        v65[1].m_Task[13].fp[1] = (char *)-1;
        v65[1].m_Task[13].fp[2] = (char *)-1;
        ReadStageCamConfig();
        (((CCBStageCam *)v65))->CCBStageCam::UpdateSmooth();
        (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
        goto LABEL_26;
      case 1050:
        if ( v65[1].m_Task[13].fp[1] == (char *)-1 )
          return 0;
        LOBYTE(v25) = (((CCBStageCam *)Buffer))->CCBStageCam::IsEditorCamValid((int)v65[1].m_Task[13].fp[1]);
        if ( v25 <= 0 || MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8A90, aWarning, 4u) != 6 )
          return 0;
        (((CCBStageCam *)Buffer))->CCBStageCam::DelEditorCam((int)v65[1].m_Task[13].fp[1]);
        (((CCBStageCam *)v65))->CCBStageCam::UpdateSmooth();
        (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
        v26 = hWnd;
        memset(lParam, 0, sizeof(lParam));
        v52 = (WPARAM)v65[1].m_Task[13].fp[1];
        lParam[0] = 1;
        lParam[1] = v52;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
        (((CCBStageCam *)Buffer))->CCBStageCam::LoadEditorCam(v22, v23, pData);
        (((CCBStageCam *)v65))->CCBStageCam::UpdateSmooth();
        (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
        (((CCCTData *)v65))->CCCTData::UpdateDebugDialog();
        v24 = hWnd;
        memset(lParam, 0, sizeof(lParam));
        v51 = (WPARAM)v65[1].m_Task[13].fp[1];
        lParam[0] = 1;
        lParam[1] = v51;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(hWnd, 0x102Bu, v51, (LPARAM)lParam);
        SendMessageA(v24, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[1], 0);
        lParam[1] = (LPARAM)v65[1].m_Task[13].fp[2];
        SendMessageA(v3, 0x102Bu, lParam[1], (LPARAM)lParam);
        SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
        return 0;
      case 1052:
        v27 = (char *)v65[1].m_Task[13].fp[1];
        if ( v27 == (char *)-1 )
          return 0;
        v28 = (char *)v65[1].m_Task[13].fp[2];
        if ( v28 == (char *)-1 )
          return 0;
        sub_5057B0((CCCTData *)Buffer, v27, v28);
        return 0;
      case 1086:
        v19 = SendMessageA(DlgItem, 0x1042u, 0, 0);
        v20 = v19;
        if ( v19 == -1 )
          return 0;
        (((CCBStage *)v57))->CCBStage::ClearTurnSlot(v19);
        memset(lParam, 0, sizeof(lParam));
        lParam[0] = 1;
        lParam[1] = v20;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
        lParam[2] = 1;
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", g_szCCBStageCamName);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        lParam[2] = 2;
        sprintf((char *const)&g_CCBStageCamBuffer, unk_C10D38);
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
          if ( (((CCBStage *)v57))->CCBStage::GetTurnSlotData(i) && (((CCBStage *)v57))->CCBStage::GetTurnSlotData(i + 1) )
            (((CCBSystem *)v57))->CCBSystem::CastProtect(i, i + 1, 1.0);
        }
        return 0;
      case 1194:
        v29 = (char *)v65[1].m_Task[13].fp[1];
        if ( v29 == (char *)-1 )
          return 0;
        v30 = (char *)v65[1].m_Task[13].fp[2];
        if ( v30 == (char *)-1 )
          return 0;
        v31 = *((_DWORD *)&Buffer->fov + (_DWORD)&v30[50 * (_DWORD)v29 + 102500]);
        if ( v31 == -1 )
          return 0;
        v32 = (float *)(&Buffer->fov + 51 * v31);
        if ( !v32 )
          return 0;
        if ( !*((_BYTE *)v32 + 88) )
          return 0;
        v33 = (CCBStage *)v57;
        v34 = (int)(v32 + 8);
        if ( !(((CCBStage *)v57))->CCBStage::HasTurnChanged(v32 + 8) )
          return 0;
        goto LABEL_70;
      case 1195:
        v35 = (char *)v65[1].m_Task[13].fp[1];
        if ( v35 == (char *)-1 )
          return 0;
        v36 = (char *)v65[1].m_Task[13].fp[2];
        if ( v36 == (char *)-1 )
          return 0;
        v37 = *((_DWORD *)&Buffer->fov + (_DWORD)&v36[50 * (_DWORD)v35 + 102500]);
        if ( v37 == -1 )
          return 0;
        v38 = (float *)(&Buffer->fov + 51 * v37);
        if ( !v38 )
          return 0;
        if ( !*((_BYTE *)v38 + 89) )
          return 0;
        v33 = (CCBStage *)v57;
        v34 = (int)(v38 + 14);
        if ( !(((CCBStage *)v57))->CCBStage::HasTurnChanged(v38 + 14) )
          return 0;
LABEL_70:
        (((CCCTData *)v33))->CCCTData::UpdateCamera(v34);
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
      Buffer->CCBStageCam::CCBStageCam(v54);
      return 0;
    }
    if ( (unsigned __int16)v68 <= 0x411u )
    {
      if ( (unsigned __int16)v68 == 1041 )
      {
        if ( v65[1].m_Task[13].fp[1] != (char *)-1 && v65[1].m_Task[13].fp[2] != (char *)-1 )
        {
          LOBYTE(v13) = (((CCBStageCam *)Buffer))->CCBStageCam::IsEditorCamValid((int)v65[1].m_Task[13].fp[1]);
          if ( v13 != 1 )
          {
            (((CCBStageCam *)Buffer))->CCBStageCam::SaveEditorCam((int)v65[1].m_Task[13].fp[1], (int)v65[1].m_Task[13].fp[2], (int)(v65[1].m_Task[13].fp[2] + 1));
            ++v65[1].m_Task[13].fp[2];
            (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
            memset(lParam, 0, sizeof(lParam));
            v14 = (WPARAM)v65[1].m_Task[13].fp[2];
            lParam[3] = 3;
            lParam[4] = 3;
            lParam[0] = 1;
            lParam[1] = v14;
            lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
              (((CCBStageCam *)v65))->CCBStageCam::UpdateOrbit();
              (((CCBStageCam *)v65))->CCBStageCam::UpdateSmooth();
              (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
              (((CCCTData *)v65))->CCCTData::UpdateDebugDialog();
              v6 = hWnd;
              memset(lParam, 0, sizeof(lParam));
              v49 = (WPARAM)v65[1].m_Task[13].fp[1];
              lParam[0] = 1;
              lParam[1] = v49;
              lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
            FullConfig = (((CCBStage *)*(CCBStage **)(*(_DWORD *)(LODWORD(v65->fov) + 20) + 12)))->CCBStage::LoadFullConfig();
            memset(lParam, 0, sizeof(lParam));
            lParam[0] = 1;
            lParam[1] = FullConfig;
            lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
            lParam[3] = 3;
            lParam[4] = 3;
            SendMessageA(DlgItem, 0x102Bu, FullConfig, (LPARAM)lParam);
            SendMessageA(DlgItem, 0x1043u, FullConfig, FullConfig);
            SendMessageA(DlgItem, 0x1013u, FullConfig, 0);
            SendMessageA(DlgItem, 7u, 0, 0);
            memset(lParam, 0, sizeof(lParam));
            lParam[0] = 1;
            lParam[1] = FullConfig;
            lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
            lParam[2] = 1;
            sprintf((char *const)&g_CCBStageCamBuffer, "%s", &off_5D8A3C);
            SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
            lParam[2] = 2;
            sprintf((char *const)&g_CCBStageCamBuffer, unk_C10D38);
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
              (((CCBStageCam *)Buffer))->CCBStageCam::SaveEditorCam(v7, v8, v8 - 1);
              --v65[1].m_Task[13].fp[2];
              (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
              memset(lParam, 0, sizeof(lParam));
              v9 = (WPARAM)v65[1].m_Task[13].fp[2];
              lParam[3] = 3;
              lParam[4] = 3;
              lParam[0] = 1;
              lParam[1] = v9;
              lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
        && (((CCBStageCam *)Buffer))->CCBStageCam::AddCurCamToEditor(v10, (int)v65[1].m_Task[13].fp[2]) )
      {
        (((CCBStageCam *)v65))->CCBStageCam::UpdateSmooth();
        (((CCBStageCam *)v65))->CCBStageCam::PopulateCameraListView();
        v11 = hWnd;
        memset(lParam, 0, sizeof(lParam));
        v50 = (WPARAM)v65[1].m_Task[13].fp[1];
        lParam[0] = 1;
        lParam[1] = v50;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(hWnd, 0x102Bu, v50, (LPARAM)lParam);
        SendMessageA(v11, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[1], 0);
        lParam[1] = (LPARAM)v65[1].m_Task[13].fp[2];
        SendMessageA(v3, 0x102Bu, lParam[1], (LPARAM)lParam);
        SendMessageA(v3, 0x1013u, (WPARAM)v65[1].m_Task[13].fp[2], 0);
        LOBYTE(v12) = (((CCBStageCam *)Buffer))->CCBStageCam::IsEditorCamValid((int)v65[1].m_Task[13].fp[1]);
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
        (((CCBCamControl *)Buffer))->CCBCamControl::ClearFinishedTask(v17);
        result = 0;
        break;
      case 1044:
        v15 = SendMessageA(DlgItem, 0x1042u, 0, 0);
        v16 = v15;
        if ( v15 == -1 )
          return 0;
        (((CCBStage *)v57))->CCBStage::ClearTurnSlot(v15);
        memset(lParam, 0, sizeof(lParam));
        lParam[0] = 1;
        lParam[1] = v16;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
        lParam[2] = 1;
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", g_szCCBStageCamName);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        lParam[2] = 2;
        sprintf((char *const)&g_CCBStageCamBuffer, unk_C10D38);
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(DlgItem, 0x102Bu, v16, (LPARAM)lParam);
        SendMessageA(DlgItem, 0x1013u, v16, 0);
        result = 0;
        break;
      case 1045:
        (((CCBCamControl *)Buffer))->CCBCamControl::AddTask();
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
        *(CCCTData **)(*(_DWORD *)(LODWORD(fov) + 20) + 16)->CCCTData::CCCTData(p_DWORD, p_DWORD2);
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
  char *v10; // edx
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
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[1] = i;
    lParam[2] = 0;
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], i);
    SendMessageA(hDlga, 0x1007u, 0, (LPARAM)lParam);
    fov = this->fov;
    lParam[2] = 1;
    if ( (((CCBStage *)*(CCBStage **)(*(_DWORD *)(LODWORD(fov) + 20) + 12)))->CCBStage::GetTurnSlotData(i) )
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", &off_5D8A3C);
    else
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", g_szCCBStageCamName);
    SendMessageA(hDlga, 0x1006u, 0, (LPARAM)lParam);
  }
  for ( j = 0; j < 100; ++j )
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[1] = j;
    lParam[2] = 0;
    sprintf((char *const)&g_CCBStageCamBuffer, "%03d", j);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    v8 = this->fov;
    lParam[2] = 1;
    LOBYTE(v9) = (((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(v8) + 20) + 16)))->CCBStageCam::IsEditorCamValid(j);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v9);
    SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
  }
  v10 = (char *)this[1].m_Task[13].fp[1];
  if ( v10 != (char *)-1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[3] = 3;
    lParam[4] = 3;
    lParam[1] = (LPARAM)v10;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    SendMessageA(DlgItem, 0x102Bu, (WPARAM)v10, (LPARAM)lParam);
    SendMessageA(DlgItem, 0x1013u, (WPARAM)this[1].m_Task[13].fp[1], 0);
  }
  result = (LRESULT)this[1].m_Task[13].fp[2];
  if ( result != -1 )
  {
    lParam[1] = (LPARAM)this[1].m_Task[13].fp[2];
    SendMessageA(hWnd, 0x102Bu, result, (LPARAM)lParam);
    return SendMessageA(hWnd, 0x1013u, (WPARAM)this[1].m_Task[13].fp[2], 0);
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
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[1] = i;
    lParam[2] = 0;
    sprintf((char *const)&g_CCBStageCamBuffer, "%03d", i);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    fov = this->fov;
    lParam[2] = 1;
    LOBYTE(v5) = (((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(fov) + 20) + 16)))->CCBStageCam::IsEditorCamValid(i);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v5);
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
  result = (int)this[1].m_Task[13].fp[1];
  if ( result != -1 )
  {
    LOBYTE(result) = (((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16)))->CCBStageCam::IsEditorCamValid((int)this[1].m_Task[13].fp[1]);
    v4 = 0;
    for ( i = result; v4 < i; ++v4 )
    {
      v5 = *(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16);
      v6 = *(_DWORD *)(v5 + 4 * (v4 + 10 * (5 * (int)this[1].m_Task[13].fp[1] + 10250)));
      if ( v6 == -1 )
        v7 = 0;
      else
        v7 = v5 + 204 * v6;
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      lParam[1] = v4;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v4);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_CCBStageCamBuffer, "%1.2f", *(float *)(v7 + 28));
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 2;
      if ( *(_BYTE *)(v7 + 92) )
        sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&unk_5D8AC4);
      if ( *(_BYTE *)(v7 + 93) )
        sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&unk_5D8ABC);
      if ( *(_BYTE *)(v7 + 94) )
        sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&unk_5D8AB4);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      result = i;
    }
  }
  return result;
}

// 0x004E74E0
void CCBStageCam::UpdateOrbit()
{
  char *v1; // eax
  _DWORD pData[51]; // [esp+0x4] [ebp-CCh] BYREF

  memset(pData, 0, sizeof(pData));
  pData[7] = 1065353216;
  LOBYTE(pData[5]) = 1;
  LOBYTE(pData[23]) = 1;
  LOWORD(pData[22]) = 257;
  BYTE2(pData[22]) = 1;
  HIBYTE(pData[23]) = 1;
  v1 = (char *)this[1].m_Task[13].fp[1];
  pData[35] = 0;
  pData[36] = 1112014848;
  pData[37] = 0;
  pData[38] = 1120403456;
  pData[39] = 1120403456;
  pData[40] = 1120403456;
  if ( v1 != (char *)-1 )
    (((CCBStageCam *)*(CCBStageCam **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16)))->CCBStageCam::Reset((int)v1, pData);
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
  v5 = *(_DWORD *)(v4 + 4 * (int)&this[1].m_Task[13].fp[2][50 * (int)this[1].m_Task[13].fp[1] + 102500]);
  if ( v5 != -1 )
  {
    v6 = v4 + 204 * v5;
    if ( v6 )
    {
      *(_BYTE *)(v6 + 93) = EditBoxIsModified(hWnd);
      *(_BYTE *)(v6 + 92) = EditBoxIsModified(DlgItem);
      *(_BYTE *)(v6 + 94) = EditBoxIsModified(v16);
      *(_BYTE *)(v6 + 88) = !EditBoxIsModified(v17);
      *(_BYTE *)(v6 + 89) = !EditBoxIsModified(v18);
      *(_DWORD *)(v6 + 80) = EditBoxGetInt(v2);
      *(_DWORD *)(v6 + 84) = EditBoxGetInt(v13);
      *(_BYTE *)(v6 + 91) = EditBoxIsModified(v19);
      *(_BYTE *)(v6 + 90) = EditBoxIsModified(v20);
      *(float *)(v6 + 132) = EditBoxGetFloat(v21);
      *(float *)(v6 + 136) = EditBoxGetFloat(v22);
      *(float *)(v6 + 108) = EditBoxGetFloat(v23);
      *(float *)(v6 + 28) = EditBoxGetFloat(v24);
      *(_BYTE *)(v6 + 97) = EditBoxIsModified(v25);
      *(_BYTE *)(v6 + 98) = EditBoxIsModified(v26);
      *(_BYTE *)(v6 + 99) = EditBoxIsModified(v27);
      *(float *)(v6 + 112) = EditBoxGetFloat(v28);
      *(_BYTE *)(v6 + 23) = EditBoxIsModified(v29);
      *(_BYTE *)(v6 + 101) = EditBoxIsModified(v30);
      *(_BYTE *)(v6 + 102) = EditBoxIsModified(v31);
      *(_DWORD *)(v6 + 104) = EditBoxGetInt(v32);
      *(float *)(v6 + 116) = EditBoxGetFloat(v33);
      *(float *)(v6 + 120) = EditBoxGetFloat(v34);
      *(float *)(v6 + 124) = EditBoxGetFloat(v35);
      *(float *)(v6 + 128) = EditBoxGetFloat(v36);
      *(float *)(v6 + 164) = EditBoxGetFloat(v37);
      *(float *)(v6 + 168) = EditBoxGetFloat(v38);
      *(_BYTE *)(v6 + 100) = EditBoxIsModified(v39);
      *(_BYTE *)(v6 + 96) = EditBoxIsModified(v40);
      *(_BYTE *)(v6 + 95) = EditBoxIsModified(v41);
      *(float *)(v6 + 172) = EditBoxGetFloat(v3);
      *(_DWORD *)(v6 + 140) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430228);
      *(_DWORD *)(v6 + 144) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430232);
      *(_DWORD *)(v6 + 148) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430236);
      *(_DWORD *)(v6 + 152) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430240);
      *(_DWORD *)(v6 + 156) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430244);
      *(_DWORD *)(v6 + 160) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 16) + 430248);
      if ( *(_BYTE *)(v6 + 88) )
      {
        v7 = (CCBStage *)*(CCBStage **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12);
        Int = EditBoxGetInt(v2);
        if ( (((CCBStage *)v7))->CCBStage::GetTurnSlotData(Int) )
          qmemcpy(
            (void *)(v6 + 32),
            (const void *)(*(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12) + 24 * (EditBoxGetInt(v2) + 191)),
            0x18u);
        else
          *(_BYTE *)(v6 + 88) = 0;
      }
      v9 = (CCBStage *)*(CCBStage **)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12);
      v10 = EditBoxGetInt(v13);
      LOBYTE(v5) = (((CCBStage *)v9))->CCBStage::GetTurnSlotData(v10);
      if ( (_BYTE)v5 )
      {
        v11 = *(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 20) + 12);
        v5 = EditBoxGetInt(v13) + 191;
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

  if ( this[1].m_Task[13].fp[1] == (char *)-1 || this[1].m_Task[13].fp[2] == (char *)-1 )
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
  if ( !EditBoxIsModified(DlgItem) && EditBoxIsModified(v3) && EditBoxIsModified(v2) )
  {
    MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8AD4, &unk_5D8AF4, 0);
    return 0;
  }
  return 1;
}

// 0x004E8450
int CCBStageCam::StoreCurrentView(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return (((CCBStageCam *)pfVal))->CCBStageCam::UpdateStageCamera((float *)pfVal, hDlg, uMsg, wParam, lParam);
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
  int result; // eax
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
  float v64; // [esp+0xC] [ebp-0x58]
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
            (((CCBStageCam *)pfVal))->CCBStageCam::SetViewDistance(hDlg);
            return 0;
          }
          pfVal[2019] = NAN;
          (((CCBStageCam *)pfVal))->CCBStageCam::SetViewDistance(hDlg);
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
          (((CCBStageCam *)pfVal))->CCBStageCam::InterpolateAngle(hDlg);
          pfVal[2018] = NAN;
          pfVal[2019] = NAN;
          (((CCBStageCam *)pfVal))->CCBStageCam::UpdateFollowTarget(hDlg);
          (((CCBStageCam *)pfVal))->CCBStageCam::SetViewDistance(hDlg);
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
          (((CCBStageCam *)pfVal))->CCBStageCam::UpdateFollowTarget(hDlg);
          (((CCBStageCam *)pfVal))->CCBStageCam::SetViewDistance(hDlg);
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
      v68[3] = (LPARAM)&unk_5D8B0C;
      SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)v68);
      v44 = SendMessageA(hWnd, 0x1037u, 0, 0);
      LOBYTE(v44) = v44 | 0x21;
      SendMessageA(hWnd, 0x1036u, 0, v44);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 24;
      v68[3] = (LPARAM)&unk_5D8A58;
      SendMessageA(hWnd, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 48;
      v68[3] = (LPARAM)&unk_5D8B0C;
      SendMessageA(hWnd, 0x101Bu, 1u, (LPARAM)v68);
      v45 = SendMessageA(hDlga, 0x1037u, 0, 0);
      LOBYTE(v45) = v45 | 0x21;
      SendMessageA(hDlga, 0x1036u, 0, v45);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 25;
      v68[3] = (LPARAM)&unk_5D8A58;
      SendMessageA(hDlga, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 38;
      v68[3] = (LPARAM)&unk_5D8B04;
      SendMessageA(hDlga, 0x101Bu, 1u, (LPARAM)v68);
      v46 = SendMessageA(v7, 0x1037u, 0, 0);
      LOBYTE(v46) = v46 | 0x21;
      SendMessageA(v7, 0x1036u, 0, v46);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 25;
      v68[3] = (LPARAM)&unk_5D8A58;
      SendMessageA(v7, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 48;
      v68[3] = (LPARAM)&unk_5D8B0C;
      SendMessageA(v7, 0x101Bu, 1u, (LPARAM)v68);
      v47 = SendMessageA(v67, 0x1037u, 0, 0);
      LOBYTE(v47) = v47 | 0x21;
      SendMessageA(v67, 0x1036u, 0, v47);
      v68[0] = 7;
      v68[1] = 0;
      v68[2] = 25;
      v68[3] = (LPARAM)&unk_5D8A58;
      SendMessageA(v67, 0x101Bu, 0, (LPARAM)v68);
      v68[1] = 0;
      v68[0] = 7;
      v68[2] = 25;
      v68[3] = (LPARAM)&unk_5D8B00;
      SendMessageA(v67, 0x101Bu, 1u, (LPARAM)v68);
      v68[1] = 1;
      v68[2] = 60;
      v68[3] = (LPARAM)&g_EffMgrData._tail_000[72];
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
          if ( g_hCBStageCamDlg )
            DestroyWindow((HWND)g_hCBStageCamDlg);
          goto LABEL_8;
        case 1043:
          if ( *((_DWORD *)pfVal + 2016) == -1 )
            return 0;
          (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44)))->CEffMgr::SetTimeScale(pfVal[2016]);
          (((CCBCamControl *)pfVal))->CCBCamControl::sub_4E9750(hDlg);
          return 0;
        case 1044:
          if ( *((_DWORD *)pfVal + 2016) == -1 )
            return 0;
          (((CEffMgr *)*((const char **)pfVal + 2016)))->CEffMgr::CreateEff(v61, v62, v63, v64);
          (((CCBCamControl *)pfVal))->CCBCamControl::sub_4E9750(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v9 = *((_DWORD *)pfVal + 2016);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v9;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
          v18 = (float *)pfVal;
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
          (((CCBStageCam *)pfVal))->CCBStageCam::UpdateFollowTarget(hDlg);
          (((CCBStageCam *)pfVal))->CCBStageCam::InterpolateAngle(hDlg);
          (((CCBStageCam *)pfVal))->CCBStageCam::SetBlendWeight(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v22 = *((_DWORD *)pfVal + 2017);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v22;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
          v18 = (float *)pfVal;
          sub_4CE8A0(v24, v23, *((_DWORD *)pfVal + 2016));
LABEL_25:
          (((CCBStageCam *)v18))->CCBStageCam::InterpolateAngle(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v19 = *((_DWORD *)v18 + 2018);
          lParam[0] = 1;
          lParam[1] = v19;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
          lParam[3] = 3;
          lParam[4] = 3;
          SendMessageA(v7, 0x102Bu, v19, (LPARAM)lParam);
          SendMessageA(v7, 0x1013u, *((_DWORD *)pfVal + 2018), 0);
          (((CCBStageCam *)pfVal))->CCBStageCam::SetBlendWeight(hDlg);
          memset(lParam, 0, sizeof(lParam));
          lParam[3] = 3;
          v20 = *((_DWORD *)pfVal + 2017);
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v20;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
          SendMessageA(hDlga, 0x102Bu, v20, (LPARAM)lParam);
          SendMessageA(hDlga, 0x1013u, *((_DWORD *)pfVal + 2017), 0);
          return 0;
        case 1053:
          if ( *((_DWORD *)pfVal + 2016) == -1 )
            return 0;
          if ( g_hCBStageCamDlg )
            DestroyWindow((HWND)g_hCBStageCamDlg);
LABEL_8:
          g_hCBStageCamDlg = (int)CreateDialogParamA(
                                    hInstance,
                                    (LPCSTR)0x70,
                                    (HWND)g_todo_BFDA4C,
                                    CCBStageCam::DlgProc,
                                    0);
          ::ShowWindow((HWND)g_hCBStageCamDlg, 5);
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
          EffByID = (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44)))->CEffMgr::FindEffByID(v12);
          memset(lParam, 0, sizeof(lParam));
          lParam[3] = 3;
          lParam[4] = 3;
          *((_DWORD *)pfVal + 2016) = EffByID;
          lParam[0] = 1;
          lParam[1] = EffByID;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
          SendMessageA(hWnd, 0x102Bu, EffByID, (LPARAM)lParam);
          SendMessageA(hWnd, 0x1013u, *((_DWORD *)pfVal + 2016), 0);
          return 0;
        case 1055:
          sub_4CE5C0(*(_DWORD *)(*(_DWORD *)pfVal + 44));
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::ApplyColorFilter();
          return 0;
        case 1057:
          if ( *((_DWORD *)pfVal + 2017) == -1 )
            return 0;
          (((CEffect *)*(CEffect **)(*(_DWORD *)pfVal + 44)))->CEffect::Render(*((_DWORD *)pfVal + 2017));
          (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44)))->CEffMgr::Init(*((_DWORD *)pfVal + 2017), 0, 0, 0, 0);
          result = 0;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)pfVal + 44) + 43304) = 0;
          return result;
        case 1059:
          v32 = *((_DWORD *)pfVal + 2018);
          if ( v32 == -1 )
            return 0;
          v33 = *((_DWORD *)pfVal + 2017);
          if ( v33 == -1 || v32 <= 0 )
            return 0;
          sub_4CE970(v33, v32, v32 - 1);
          --*((_DWORD *)pfVal + 2018);
          (((CCBStageCam *)pfVal))->CCBStageCam::InterpolateAngle(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v58 = *((_DWORD *)pfVal + 2018);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v58;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
          (((CCBStageCam *)pfVal))->CCBStageCam::InterpolateAngle(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v59 = *((_DWORD *)pfVal + 2018);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v59;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
          SendMessageA(v7, 0x102Bu, v59, (LPARAM)lParam);
          SendMessageA(v7, 0x1013u, *((_DWORD *)pfVal + 2018), 0);
          return 0;
        case 1210:
          (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44)))->CEffMgr::~CEffMgr();
          return 0;
        case 1211:
          if ( MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8B14, &unk_5D8B3C, 1u) != 1 )
            return 0;
          *(CEffMgr **)(*(_DWORD *)pfVal + 44)->CEffMgr::CEffMgr();
          (((CCBStageCam *)pfVal))->CCBStageCam::sub_4E95A0(hDlg);
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
          *(&dword_EC9F00 + 3985 * *((_DWORD *)pfVal + 2017) + 248 * *((_DWORD *)pfVal + 2018) + 31 * v27) = 1065353216;
          (((CCBStageCam *)pfVal))->CCBStageCam::UpdateFollowTarget(hDlg);
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
          (((CCBStageCam *)pfVal))->CCBStageCam::UpdateFollowTarget(hDlg);
          return 0;
        case 1232:
          if ( *((_DWORD *)pfVal + 2017) == -1 || *((_DWORD *)pfVal + 2018) == -1 || *((_DWORD *)pfVal + 2019) == -1 )
          {
            MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8B44, aWarning, 0);
            return 0;
          }
          else
          {
            (((CCBStageCam *)pfVal))->CCBStageCam::CalculateFOV(hDlg);
            (((CCBStageCam *)pfVal))->CCBStageCam::UpdateFollowTarget(hDlg);
            return 0;
          }
        case 1237:
          (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)pfVal + 44)))->CEffMgr::ReleaseCompletedEffects();
          return 0;
        case 1238:
          v37 = *((_DWORD *)pfVal + 2017);
          if ( v37 == -1 )
            return 0;
          v38 = 0;
          v39 = (int *)&g_nSaveSlot0;
          break;
        case 1261:
          v41 = *((_DWORD *)pfVal + 2017);
          if ( v41 == -1 )
            return 0;
          memset((void *)(15940 * v41 + 15507056), 0, 0x3E44u);
          (((CCBStageCam *)pfVal))->CCBStageCam::SetBlendWeight(hDlg);
          memset(lParam, 0, sizeof(lParam));
          v42 = *((_DWORD *)pfVal + 2017);
          lParam[3] = 3;
          lParam[4] = 3;
          lParam[0] = 1;
          lParam[1] = v42;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
          SendMessageA(hDlga, 0x102Bu, v42, (LPARAM)lParam);
          SendMessageA(hDlga, 0x1013u, *((_DWORD *)pfVal + 2017), 0);
          (((CCBStageCam *)pfVal))->CCBStageCam::InterpolateAngle(hDlg);
          (((CCBStageCam *)pfVal))->CCBStageCam::UpdateFollowTarget(hDlg);
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
        (((CCBStageCam *)pfVal))->CCBStageCam::SetBlendWeight(hDlg);
        memset(lParam, 0, sizeof(lParam));
        v40 = *((_DWORD *)pfVal + 2017);
        lParam[0] = 1;
        lParam[1] = v40;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
        lParam[3] = 3;
        lParam[4] = 3;
        SendMessageA(hDlga, 0x102Bu, v40, (LPARAM)lParam);
        SendMessageA(hDlga, 0x1013u, *((_DWORD *)pfVal + 2017), 0);
        (((CCBStageCam *)pfVal))->CCBStageCam::InterpolateAngle(hDlg);
        memset(lParam, 0, sizeof(lParam));
        lParam[3] = 3;
        lParam[4] = 3;
        v60 = *((_DWORD *)pfVal + 2018);
        lParam[0] = 1;
        lParam[1] = v60;
        lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
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
  WPARAM fStartTime_low; // edx
  WPARAM v8; // edx
  HWND hWnd; // [esp+0x10] [ebp-0x34]
  HWND DlgItem; // [esp+0x14] [ebp-0x30]
  HWND v11; // [esp+0x18] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x1C] [ebp-0x28] BYREF
  char *hDlga; // [esp+0x48] [ebp+0x4]

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
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      lParam[1] = (LPARAM)hDlga;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", *(_DWORD *)(LODWORD(fov) + 44) + v4 + 28);
      SendMessageA(hWnd, 0x1007u, 0, (LPARAM)lParam);
    }
    v4 += 72;
    ++hDlga;
  }
  while ( v4 < 2304 );
  (((CCBCamControl *)this))->CCBCamControl::sub_4E9750(hDlg);
  this->CCBStageCam::SetBlendWeight(hDlg);
  this->CCBStageCam::InterpolateAngle(hDlg);
  result = this->CCBStageCam::UpdateFollowTarget(hDlg);
  fStartTime_low = LODWORD(this[1].m_Task[13].fStartTime);
  if ( fStartTime_low != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[1] = fStartTime_low;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[3] = 3;
    lParam[4] = 3;
    SendMessageA(DlgItem, 0x102Bu, fStartTime_low, (LPARAM)lParam);
    result = SendMessageA(DlgItem, 0x1013u, LODWORD(this[1].m_Task[13].fStartTime), 0);
  }
  v8 = *(_DWORD *)&this[1].m_Task[13].bValid;
  if ( v8 != -1 )
  {
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 1;
    lParam[1] = v8;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[3] = 3;
    lParam[4] = 3;
    SendMessageA(v11, 0x102Bu, v8, (LPARAM)lParam);
    return SendMessageA(v11, 0x1013u, *(_DWORD *)&this[1].m_Task[13].bValid, 0);
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
  v4 = (int *)&g_nSaveSlot0;
  do
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[1] = v3;
    lParam[2] = 0;
    sprintf((char *const)&g_CCBStageCamBuffer, "%03d", v3);
    SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
    v5 = (unsigned long)*v4;
    lParam[2] = 1;
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v5);
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
  if ( *(_DWORD *)&this[1].m_Task[13].bValid != -1 )
  {
    for ( i = 0; i < 16; ++i )
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      lParam[1] = i;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], i);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      v6 = *(_DWORD *)&this[1].m_Task[13].bValid;
      lParam[2] = 1;
      v7 = *(&g_nSaveSlot1 + 3984 * v6 + i + v6);
      if ( v7 )
      {
        EffByID = (((CEffMgr *)*(CEffMgr **)(LODWORD(this->fov) + 44)))->CEffMgr::FindEffByID(v7);
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", 280 * EffByID + 24433460);
      }
      else
      {
        sprintf((char *const)&g_CCBStageCamBuffer, aEmpty);
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
  float fStartTime; // eax
  float v6; // edx
  float v7; // edx
  HWND hWnd; // [esp+0x14] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x18] [ebp-0x28] BYREF

  memset(lParam, 0, sizeof(lParam));
  hWnd = GetDlgItem(hDlg, 1154);
  SendMessageA(hWnd, 0x1009u, 0, 0);
  result = -1;
  if ( *(_DWORD *)&this[1].m_Task[13].bValid != -1 && LODWORD(this[1].m_Task[13].fStartTime) != -1 )
  {
    for ( i = 0; i < 8; ++i )
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      lParam[1] = i;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], i);
      SendMessageA(hWnd, 0x1007u, 0, (LPARAM)lParam);
      fStartTime = this[1].m_Task[13].fStartTime;
      lParam[2] = 1;
      if ( byte_EC9F0C[15940 * *(_DWORD *)&this[1].m_Task[13].bValid + 992 * LODWORD(fStartTime) + 124 * i] )
        sprintf((char *const)&g_CCBStageCamBuffer, aO);
      else
        sprintf((char *const)&g_CCBStageCamBuffer, "x");
      SendMessageA(hWnd, 0x1006u, 0, (LPARAM)lParam);
      v6 = this[1].m_Task[13].fStartTime;
      lParam[2] = 2;
      sprintf(
        (char *const)&g_CCBStageCamBuffer,
        "%0.2f",
        *(float *)&g_nSaveSlotBase[3985 * *(_DWORD *)&this[1].m_Task[13].bValid + 18 + 248 * LODWORD(v6) + 31 * i]);
      SendMessageA(hWnd, 0x1006u, 0, (LPARAM)lParam);
      v7 = this[1].m_Task[13].fStartTime;
      lParam[2] = 3;
      sprintf(
        (char *const)&g_CCBStageCamBuffer,
        "%0.2f",
        *((float *)&dword_EC9F00 + 3985 * *(_DWORD *)&this[1].m_Task[13].bValid + 248 * LODWORD(v7) + 31 * i));
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
  if ( *(_DWORD *)&this[1].m_Task[13].bValid != -1
    && LODWORD(this[1].m_Task[13].fStartTime) != -1
    && LODWORD(this[1].m_Task[13].fExpectTime) != -1 )
  {
    this->CCBStageCam::UpdateTransition(hDlg);
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
    v7 = 3985 * *(_DWORD *)&this[1].m_Task[13].bValid;
    result = byte_EC9F0C[992 * LODWORD(this[1].m_Task[13].fStartTime)
                       + 124 * LODWORD(this[1].m_Task[13].fExpectTime)
                       + v7 * 4];
    v8 = (int *)&g_nSaveSlotBase[248 * LODWORD(this[1].m_Task[13].fStartTime)
                        + 31 * LODWORD(this[1].m_Task[13].fExpectTime)
                        + v7];
    if ( result )
    {
      EditBoxSetFloat(hDlga, *(float *)v8);
      EditBoxSetFloat(v5, *((float *)v8 + 4));
      EditBoxSetFloat(DlgItem, *((float *)v8 + 1));
      EditBoxSetFloat(v12, *((float *)v8 + 2));
      EditBoxSetFloat(v13, *((float *)v8 + 3));
      EditBoxSetFloat(v14, *((float *)v8 + 5));
      EditBoxSetFloat(v15, *((float *)v8 + 6));
      EditBoxSetFloat(v16, *((float *)v8 + 7));
      EditBoxSetFloat(v17, *((float *)v8 + 8));
      EditBoxSetFloat(v18, *((float *)v8 + 9));
      EditBoxSetFloat(v19, *((float *)v8 + 10));
      EditBoxSetFloat(v20, *((float *)v8 + 11));
      EditBoxSetFloat(v21, *((float *)v8 + 12));
      EditBoxSetFloat(v5, *((float *)v8 + 13));
      EditBoxSetFloat(v22, *((float *)v8 + 14));
      EditBoxSetFloat(v23, *((float *)v8 + 15));
      EditBoxSetFloat(v24, *((float *)v8 + 16));
      EditBoxSetFloat(v25, *((float *)v8 + 17));
      EditBoxSetFloat(v26, *((float *)v8 + 18));
      EditBoxSetFloat(v27, *((float *)v8 + 19));
      EditBoxSetFloat(v28, *((float *)v8 + 21));
      EditBoxSetInt(v29, v8[20]);
      LOBYTE(v9) = *((_BYTE *)v8 + 89);
      EditBoxSetReadOnly(hWnd, v9);
      LOBYTE(v10) = *((_BYTE *)v8 + 90);
      EditBoxSetReadOnly(v31, v10);
      return EditBoxSetFloat(v6, *((float *)v8 + 23));
    }
  }
  return result;
}

// 0x004E9F70
void CCBStageCam::CalculateFOV(HWND hDlg)
{
  HWND v4; // ebp
  HWND v5; // eax
  float fStartTime; // ecx
  void *v7; // edi
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

  if ( *(_DWORD *)&this[1].m_Task[13].bValid != -1
    && LODWORD(this[1].m_Task[13].fStartTime) != -1
    && LODWORD(this[1].m_Task[13].fExpectTime) != -1 )
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
    fStartTime = this[1].m_Task[13].fStartTime;
    v7 = v5;
    v8 = (int *)&g_nSaveSlotBase[3985 * *(_DWORD *)&this[1].m_Task[13].bValid
                        + 248 * LODWORD(fStartTime)
                        + 31 * LODWORD(this[1].m_Task[13].fExpectTime)];
    if ( *((_BYTE *)v8 + 88) )
    {
      v9 = (const char *)*(&g_nSaveSlot1
                         + 3984 * *(_DWORD *)&this[1].m_Task[13].bValid
                         + LODWORD(fStartTime)
                         + *(_DWORD *)&this[1].m_Task[13].bValid);
      *(float *)v8 = EditBoxGetFloat(hDlga);
      *((float *)v8 + 4) = EditBoxGetFloat(v4);
      *((float *)v8 + 1) = EditBoxGetFloat(DlgItem);
      *((float *)v8 + 2) = EditBoxGetFloat(v11);
      *((float *)v8 + 3) = EditBoxGetFloat(v12);
      *((float *)v8 + 5) = EditBoxGetFloat(v13);
      *((float *)v8 + 6) = EditBoxGetFloat(v14);
      *((float *)v8 + 7) = EditBoxGetFloat(v15);
      *((float *)v8 + 8) = EditBoxGetFloat(v16);
      *((float *)v8 + 9) = EditBoxGetFloat(v17);
      *((float *)v8 + 10) = EditBoxGetFloat(v18);
      *((float *)v8 + 11) = EditBoxGetFloat(v19);
      *((float *)v8 + 12) = EditBoxGetFloat(v20);
      *((float *)v8 + 13) = EditBoxGetFloat(v4);
      *((float *)v8 + 14) = EditBoxGetFloat(v21);
      *((float *)v8 + 15) = EditBoxGetFloat(v22);
      *((float *)v8 + 16) = EditBoxGetFloat(v23);
      *((float *)v8 + 17) = EditBoxGetFloat(v24);
      *((float *)v8 + 18) = EditBoxGetFloat(v25);
      *((float *)v8 + 19) = EditBoxGetFloat(v26);
      *((float *)v8 + 21) = EditBoxGetFloat(v27);
      v8[20] = EditBoxGetInt(v28);
      *((_BYTE *)v8 + 89) = EditBoxIsModified(hWnd);
      *((_BYTE *)v8 + 90) = EditBoxIsModified(v30);
      *((float *)v8 + 23) = EditBoxGetFloat(v7);
      if ( (byte_1895559 & 1) == 0 )
      {
        LOBYTE(byte_1895559) = byte_1895559 | 1;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      if ( v9 == (((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)aQuad)
        && *((_BYTE *)v8 + 89)
        && *((float *)v8 + 21) < 0.029999999 )
      {
        MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8B88, aWarning, 0);
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

  v10[0] = (unsigned long)GetDlgItem(hDlg, 1239);
  v10[1] = (unsigned long)GetDlgItem(hDlg, 1240);
  v10[2] = (unsigned long)GetDlgItem(hDlg, 1241);
  v10[3] = (unsigned long)GetDlgItem(hDlg, 1242);
  v10[4] = (unsigned long)GetDlgItem(hDlg, 1243);
  v10[5] = (unsigned long)GetDlgItem(hDlg, 1244);
  v10[6] = (unsigned long)GetDlgItem(hDlg, 1245);
  v10[7] = (unsigned long)GetDlgItem(hDlg, 1246);
  v10[8] = (unsigned long)GetDlgItem(hDlg, 1247);
  v10[9] = (unsigned long)GetDlgItem(hDlg, 1248);
  v10[10] = (unsigned long)GetDlgItem(hDlg, 1249);
  v10[11] = (unsigned long)GetDlgItem(hDlg, 1250);
  v10[12] = (unsigned long)GetDlgItem(hDlg, 1251);
  v10[13] = (unsigned long)GetDlgItem(hDlg, 1252);
  v10[14] = (unsigned long)GetDlgItem(hDlg, 1253);
  v10[15] = (unsigned long)GetDlgItem(hDlg, 1254);
  v10[16] = (unsigned long)GetDlgItem(hDlg, 1255);
  v10[17] = (unsigned long)GetDlgItem(hDlg, 1256);
  v10[18] = (unsigned long)GetDlgItem(hDlg, 1257);
  v10[19] = (unsigned long)GetDlgItem(hDlg, 1258);
  v10[20] = (unsigned long)GetDlgItem(hDlg, 1259);
  v10[21] = (unsigned long)GetDlgItem(hDlg, 1260);
  v10[22] = (unsigned long)GetDlgItem(hDlg, 1233);
  v10[23] = (unsigned long)GetDlgItem(hDlg, 1229);
  result = *(&g_nSaveSlot1 + 3985 * *(_DWORD *)&this[1].m_Task[13].bValid + LODWORD(this[1].m_Task[13].fStartTime));
  if ( result )
  {
    EffByID = (((CEffMgr *)*(CEffMgr **)(LODWORD(this->fov) + 44)))->CEffMgr::FindEffByID(result);
    v5 = 0;
    v6 = 72 * (((CEffMgr *)*(CEffMgr **)(LODWORD(this->fov) + 44)))->CEffMgr::FindEffSlot(*(_DWORD *)&g_EffTable[280 * EffByID]);
    v7 = (HWND *)v10;
    do
    {
      v8 = *(_DWORD *)(*(_DWORD *)(LODWORD(this->fov) + 44) + v6 + 96);
      v9 = (*(int ( **)(int, int))(*(_DWORD *)v8 + 56))(v8, v5);
      result = CCBUI::SendWindowMessage(*v7, v9);
      ++v5;
      ++v7;
    }
    while ( v5 < 24 );
  }
  return result;
}

// 0x004EA590
BOOL CCBStageCam::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return (((CCBUI *)pfVal))->CCBUI::DlgProcCameraEdit(hDlg, uMsg, wParam, lParam);
}

// 0x00504060
CCBStageCam::~CCBStageCam()
{
  char v1; // [esp+0x8] [ebp+0x4]

  if ( (v1 & 1) != 0 )
    operator delete(this);
}

// 0x00504DD0
CCBStage * CCBStageCam::ResetViewport()
{
  int v2; // edx
  float *p_minz; // eax

  v2 = 2000;
  p_minz = (float *)&this->Viewport.minz;
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
  (((CCBStage *)this))->CCBStage::ResetAllData() /* [ROWTABLE] */;
  this->CCBStageCam::_todo_00504E60();
  return (CCBStage *)this;
}

// 0x00504E60
char CCBStageCam::_todo_00504E60()
{
  ReadStageCamConfig();
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

  v3 = fopen(aBasedataCbdata, Mode);
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(aCouldnTOpenCbC, aDProjectPal3Co_9, 702),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  p_yw = (float *)&this->ViewMatrix.yw;
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
  fwrite(&this[65].pControl[11], 0x7D0u, 1u, v3);
  fwrite(&this[65].m_Task[19].EndPos.z, 0x4E20u, 1u, v3);
  fclose(v3);
}

// 0x00505060
void CCBStageCam::Reset(int nVal, const void *pData)
{
  int v4; // eax
  int v5; // esi
  int v6; // eax

  LOBYTE(v4) = this->CCBStageCam::IsCamValid();
  v5 = v4;
  LOBYTE(v6) = this->CCBStageCam::IsEditorCamValid(nVal);
  if ( v5 != -1 && v6 < 50 )
  {
    *((_DWORD *)&this[65].m_Task[19].EndPos.z + 50 * nVal + v6) = v5;
    *((_BYTE *)&this[65].pControl[11] + v5) = 1;
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

  LOBYTE(v5) = this->CCBStageCam::IsEditorCamValid(nVal);
  if ( nVal2 < v5 )
  {
    if ( v5 < 50 )
    {
      LOBYTE(v6) = this->CCBStageCam::IsCamValid();
      if ( v6 != -1 )
      {
        if ( nVal2 < 49 )
        {
          v7 = (_DWORD *)(&this[65].m_Task[22].bValid + 200 * nVal);
          v8 = 49 - nVal2;
          do
          {
            *v7 = *(v7 - 1);
            --v7;
            --v8;
          }
          while ( v8 );
        }
        *((_DWORD *)&this[65].m_Task[19].EndPos.z + 50 * nVal + nVal2) = v6;
        *((_BYTE *)&this[65].pControl[11] + v6) = 1;
        qmemcpy((char *)this + 204 * v6, pData, 0xCCu);
      }
    }
  }
  else
  {
    this->CCBStageCam::Reset(nVal, pData);
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

  LOBYTE(v5) = this->CCBStageCam::IsEditorCamValid(nVal);
  if ( nVal2 < v5 && nVal3 < v5 && nVal2 != nVal3 )
  {
    v6 = 10 * (5 * nVal + 10250);
    v7 = v6 + nVal2;
    v8 = *((_DWORD *)&this->fov + v6 + nVal2);
    v9 = (_DWORD *)(&this->fov + nVal3 + v6);
    *((_DWORD *)&this->fov + v7) = (unsigned long)*v9;
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

  LOBYTE(v4) = this->CCBStageCam::IsEditorCamValid(nVal);
  if ( nVal2 >= v4 )
    return 0;
  v6 = 10 * (5 * nVal + 10250);
  *((_BYTE *)&this[65].pControl[11] + *((_DWORD *)&this->fov + v6 + nVal2)) = 0;
  if ( nVal2 == 49 )
  {
    *((_DWORD *)&this[65].m_Task[22].bValid + 50 * nVal) = -1;
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
  v3 = (int *)(&this[65].m_Task[19].EndPos.z + 50 * nCamIndex);
  do
  {
    v4 = (unsigned long)(*v3++);
    --v2;
    *((_BYTE *)&this[65].pControl[11] + v4) = 0;
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
  v4 = (_DWORD *)(&this[65].m_Task[19].EndPos.z + 50 * nCamIndex);
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
  while ( *((_BYTE *)&this[65].pControl[11] + v1) )
  {
    if ( ++v1 >= 2000 )
    {
      return -1;
    }
  }
  return v1;
}

// 0x00505410
bool CCBStageCam::Create()
{
  bool result; // al

  this[68].m_Task[34].EndPos.z = 0.0f;
  this[68].m_Task[34].EndPos.yaw.p = 0;
  LOBYTE(this[68].m_Task[34].EndPos.y) = 0;
  this[68].m_Task[35].StartPos.yaw.p = 0;
  this[68].m_Task[34].EndPos.pit = 0.0f;
  this[68].m_Task[37].StartPos.y = 0.0f;
  this[68].m_Task[37].StartPos.yaw.p = 0;
  this[68].m_Task[34].EndPos.rol = NAN;
  result = 0;
  this[68].m_Task[35].fp[0] = (char *)-1;
  this[68].m_Task[35].fp[1] = (char *)-1;
  this[68].m_Task[35].StartPos.pit = 1.0f;
  this[68].m_Task[35].StartPos.rol = 80.0f;
  this[68].m_Task[37].StartPos.z = 50.0f;
  this[68].m_Task[37].StartPos.pit = 100.0f;
  this[68].m_Task[37].StartPos.rol = 100.0f;
  this[68].m_Task[37].EndPos.x = 100.0f;
  return result;
}

// 0x00505490
bool CCBStageCam::Destroy()
{
  this->CCBStageCam::Create();
  ReadStageCamConfig();
  (((CCCTData *)this))->CCCTData::Destroy();
  return 1;
}

// 0x005054E0
void CCBStageCam::Update()
{
  this->CCBStageCam::Create();
}
