// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStage.h"
#include "Role/Actor.h"
#include "Misc/Array.h"
#include "Effect/C2DSpark.h"
#include "Effect/C3DSpark.h"
#include "Combat/CCBAI.h"
#include "Combat/CCBAttackSequen.h"
#include "Combat/CCBCamControl.h"
#include "Combat/CCBControl.h"
#include "Misc/CCBDisplayChain.h"
#include "Misc/CCBEditor.h"
#include "Combat/CCBProtectWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBStageEffect.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBStageScene.h"
#include "Combat/CCBStageShadow.h"
#include "Combat/CCBSystem.h"
#include "Misc/CCBTaskSlot280.h"
#include "Combat/CCBUI.h"
#include "Combat/CCCTData.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffSParticle.h"
#include "Effect/CEffect.h"
#include "Misc/CEffectSimple.h"
#include "Effect/CEffectSystem.h"
#include "Effect/CEffgbParticle.h"
#include "Data/CGameData.h"
#include "Misc/CParticleEffect.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/Camera.h"
#include "Scene/CameraCtrl.h"
#include "Combat/Combat.h"
#include "Misc/ECBRoleTaskMode.h"
#include "Misc/ECBStageTaskState.h"
#include "Misc/FightInfo.h"
#include "GameBase/GRPinput.h"
#include "GameBase/InputSystem.h"
#include "GameBase/Logger.h"
#include "Role/NPC.h"
#include "Misc/NameSys.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/ParticleEffect.h"
#include "Misc/PlayerItem.h"
#include "UI/PropUI.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget2.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Misc/SaleUI.h"
#include "Scene/SceneMgr.h"
#include "Scene/SceneObj.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIScene.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/tagCCBStageData.h"
#include "Misc/tagCmdData.h"
#include "Misc/tagEffMgrData.h"
#include "Misc/tagRoleState.h"
#include "Misc/tagStageRoleData.h"
#include "Misc/tagThread.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_508460(...);

// Unnamed globals (extern)
extern char aFleesuccess[];
extern char aFlydown[];
extern char aFlyup[];
extern char aPause[];
extern char aStore[];
extern char aWa012[];
extern char aWa013[];
extern char aWd023[];
extern char aWd024[];
extern char aWd025[];
extern char aWd026[];
extern char aWd027[];
extern char aWd028[];
extern char aWd029[];
extern char aWd030[];
extern char aWe020[];
extern char aWe033[];
extern char aWork[];
extern char aWork1[];
extern char byte_17AAEE4[61];
void __cdecl nullsub_2(...);
void __cdecl nullsub_20(void);
void __cdecl nullsub_21(void);
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
void __cdecl nullsub_55(void);
void __cdecl nullsub_56(void);
void __cdecl nullsub_57(void);
void __cdecl nullsub_58(void);
void __cdecl nullsub_59(void);
void __cdecl nullsub_60(void);
void __cdecl nullsub_61(void);
void __cdecl nullsub_62(void);
void __cdecl nullsub_63(void);
void __cdecl nullsub_64(void);
void __cdecl nullsub_65(void);
void __cdecl nullsub_66(void);
void __cdecl nullsub_67(void);

// 0x0040CC90
void CCBStage::Init(int thisa)
{
  operator delete(this->m_pRole[0]);
  this->m_pRole[0] = 0;
  this->m_pRole[1] = 0;
  this->m_pRole[2] = 0;
  operator delete(this->m_pRoleState);
  this->m_pRoleState = ((CCBRoleState *)0);
  this->m_pEditor = ((CCBEditor *)0);
  this->m_pCam = ((CCBStageCam *)0);
}

// 0x0040CCF0
char * CCBStage::GetAlive(int *pConfig)
{
  char *result; // eax
  CCBEditor *m_pEditor; // ecx
  CCBEditor *v5; // edi
  CCBRoleState *m_pRoleState; // ebx
  unsigned int v7; // ebp
  int v8; // edx
  unsigned int v9; // eax
  char *v10; // eax
  CCBRoleState *v11; // ebp
  char *j; // ebx
  CCBRoleState *v13; // eax
  CCBEditor *v14; // ecx
  CCBEditor *v15; // ecx
  CCBEditor *i; // eax
  int *v17; // edi
  int v18; // ecx
  unsigned int v19; // [esp+0x10] [ebp-0x8]
  char *v20; // [esp+0x14] [ebp-0x4]

  result = (char *)this->CCBStage::GetByIndex(pConfig);
  if ( result )
  {
    v18 = (unsigned long)(pConfig[1] + *((_DWORD *)result + 1));
    if ( v18 > 99 )
      v18 = 99;
    *((_DWORD *)result + 1) = v18;
  }
  else
  {
    m_pEditor = (CCBEditor *)this->m_pEditor;
    v5 = (CCBEditor *)m_pEditor;
    if ( ((char *)this->m_pCam - (char *)m_pEditor) / 12 )
    {
      (((Array *)this))->Array::Insert(m_pEditor, m_pEditor);
      (((Array *)this))->Array::Erase((int)this->m_pEditor, 1 - ((char *)this->m_pEditor - (char *)v5) / 12);
      v15 = (CCBEditor *)this->m_pEditor;
      for ( i = v5; i != v15; v17[2] = (unsigned long)pConfig[2] )
      {
        v17 = (int *)i;
        i = (CCBEditor *)((char *)i + 12);
        *v17 = *pConfig;
        v17[1] = (unsigned long)pConfig[1];
      }
      result = (char *)&this->m_pEditor->m_NewItem[0].fnHP;
      this->m_pEditor = ((CCBEditor *)((CCBEditor *)result));
    }
    else
    {
      m_pRoleState = (CCBRoleState *)this->m_pRoleState;
      if ( !m_pRoleState || (v7 = ((char *)m_pEditor - (char *)m_pRoleState) / 12, v7 <= 1) )
        v7 = 1;
      if ( m_pRoleState )
        v8 = ((char *)m_pEditor - (char *)m_pRoleState) / 12;
      else
        v8 = 0;
      v9 = v8 + v7;
      v19 = v8 + v7;
      if ( (int)(v8 + v7) < 0 )
        v9 = 0;
      v10 = (char *)operator new(12 * v9);
      v11 = (CCBRoleState *)this->m_pRoleState;
      v20 = (char *)v10;
      for ( j = v10; v11 != (CCBRoleState *)v5; j += 12 )
      {
        Array::Copy(j);
        v11 = (CCBRoleState *)((char *)v11 + 12);
      }
      (((Array *)this))->Array::Erase((int)j, 1);
      (((Array *)this))->Array::Insert(v5, this->m_pEditor);
      nullsub_2(this->m_pRoleState, this->m_pEditor);
      operator delete(this->m_pRoleState);
      this->m_pCam = ((CCBStageCam *)((CCBStageCam *)&v20[12 * v19]));
      v13 = (CCBRoleState *)this->m_pRoleState;
      if ( v13 )
      {
        v14 = (CCBEditor *)this->m_pEditor;
        this->m_pRoleState = ((CCBRoleState *)((CCBRoleState *)v20));
        result = (char *)&v20[12 * (((char *)v14 - (char *)v13) / 12) + 12];
        this->m_pEditor = ((CCBEditor *)((CCBEditor *)result));
      }
      else
      {
        this->m_pRoleState = ((CCBRoleState *)((CCBRoleState *)v20));
        result = (char *)(v20 + 12);
        this->m_pEditor = ((CCBEditor *)((CCBEditor *)(v20 + 12)));
      }
    }
  }
  return result;
}

// 0x0040CF60
int CCBStage::PassCmd(void *p_DWORD)
{
  int *v3; // eax
  int v4; // ecx
  CCBEditor *m_pEditor; // edx
  CCBEditor *v6; // eax
  unsigned int *v7; // ecx
  CCBEditor *v8; // edi
  _DWORD *v9; // ebx

  v3 = (int *)this->CCBStage::GetByIndex((int *)p_DWORD);
  if ( !v3 )
    return 0;
  v4 = (unsigned long)(v3[1] - *((_DWORD *)p_DWORD + 1));
  v3[1] = v4;
  if ( v4 > 0 )
    return 1;
  m_pEditor = (CCBEditor *)this->m_pEditor;
  v6 = (CCBEditor *)(v3 + 3);
  if ( v6 != m_pEditor )
  {
    v7 = (unsigned int *)&v6[-1].m_dwTrickID[383];
    do
    {
      v8 = (CCBEditor *)v6;
      v9 = (_DWORD *)v7;
      v6 = (CCBEditor *)((char *)v6 + 12);
      v7 += 3;
      *v9 = (_DWORD)v8->m_fpThis;
      v9[1] = (_DWORD)v8->m_pRoleState;
      v9[2] = v8->m_NewItem[0].dwItemID;
    }
    while ( v6 != m_pEditor );
  }
  this->m_pEditor = ((CCBEditor *)((CCBEditor *)((char *)this->m_pEditor - 12)));
  return 2;
}

// 0x0040D010
int CCBStage::CheckValid(int nVal)
{
  Combat *v2; // ebp
  CCBStageScene **p_m_pScene; // esi
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
  CCBStageScene *v22; // ecx
  CCBStageScene *v23; // edi
  CCBStageScene *v24; // ebx
  unsigned int v25; // ebp
  int v26; // edx
  unsigned int v27; // eax
  CCBStageScene *v28; // eax
  CCBStageScene *v29; // ebx
  char *j; // ebp
  CCBStageScene *v31; // ebx
  char *k; // ebp
  int v33; // eax
  CCBStageScene *i; // eax
  CCBStageScene *v35; // edx
  int result; // eax
  gbVec3D *pSrc; // [esp+0xC] [ebp-0x18]
  int v39; // [esp+0x14] [ebp-0x10]
  unsigned int v40; // [esp+0x18] [ebp-0xC]
  CCBStageScene *v41; // [esp+0x1C] [ebp-0x8]
  int SlotCount; // [esp+0x20] [ebp-0x4]

  v2 = (Combat *)this;
  p_m_pScene = (CCBStageScene **)&this->m_pScene;
  (((Array *)&this->m_pScene))->Array::CopyRange((int *)this->m_pRole[0], (int *)this->m_pRole[1]);
  v4 = 0;
  SlotCount = (((Combat *)v2))->Combat::GetSlotCount();
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
            (((Array *)p_m_pScene))->Array::InsertAt((char *)p_m_pScene[2], (int *)(*(_DWORD *)&v10 + 12 * v4));
          break;
        case 4:
          v9 = v2[1];
          if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&v9 + 12 * v4 + 8) + 612) == 4 )
LABEL_5:
            (((Array *)p_m_pScene))->Array::InsertAt((char *)p_m_pScene[2], (int *)(*(_DWORD *)&v9 + 12 * v4));
          break;
        case 5:
          v12 = v2[1];
          v13 = *(_DWORD *)(*(_DWORD *)&v12 + 12 * v4 + 8);
          v7 = (int *)(*(_DWORD *)&v12 + 12 * v4);
          v8 = *(_BYTE *)(v13 + 612) == 6;
LABEL_13:
          if ( v8 )
            (((Array *)p_m_pScene))->Array::InsertAt((char *)p_m_pScene[2], v7);
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
            RoleSystem::CheckVisible();
          }
          break;
        case 15:
          v17 = v2[1];
          v18 = *(_DWORD *)(*(_DWORD *)&v17 + 12 * v4 + 8);
          pSrc = (gbVec3D *)(*(_DWORD *)&v17 + 12 * v4);
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
              v22 = (CCBStageScene *)p_m_pScene[2];
              v23 = (CCBStageScene *)v22;
              if ( ((char *)p_m_pScene[3] - (char *)v22) / 12 )
              {
                (((Array *)p_m_pScene))->Array::Insert(v22, v22);
                (((Array *)p_m_pScene))->Array::Erase((int)p_m_pScene[2], 1 - ((char *)p_m_pScene[2] - (char *)v23) / 12);
                for ( i = p_m_pScene[2]; v23 != i; v35->m_vecFiveLineup[0].x = pSrc->z )
                {
                  v35 = (CCBStageScene *)v23;
                  v23 = (CCBStageScene *)((char *)v23 + 12);
                  v35->m_pStage = (CCBStage *)LODWORD(pSrc->x);
                  v35->m_pUtil = (CUtil *)LODWORD(pSrc->y);
                }
                v2 = (Combat *)this;
                p_m_pScene[2] = (CCBStageScene *)((char *)p_m_pScene[2] + 12);
              }
              else
              {
                v24 = (CCBStageScene *)p_m_pScene[1];
                if ( !v24 || (v25 = ((char *)v22 - (char *)v24) / 12, v25 <= 1) )
                  v25 = 1;
                if ( v24 )
                  v26 = ((char *)v22 - (char *)v24) / 12;
                else
                  v26 = 0;
                v27 = v26 + v25;
                v40 = v26 + v25;
                if ( (int)(v26 + v25) < 0 )
                  v27 = 0;
                v28 = (CCBStageScene *)operator new(12 * v27);
                v29 = (CCBStageScene *)p_m_pScene[1];
                v41 = (CCBStageScene *)v28;
                for ( j = (char *)v28; v29 != v23; j += 12 )
                {
                  Array::Copy(j);
                  v29 = (CCBStageScene *)((char *)v29 + 12);
                }
                Array::Copy(j);
                v31 = (CCBStageScene *)p_m_pScene[2];
                for ( k = j + 12; v23 != v31; k += 12 )
                {
                  Array::Copy(k);
                  v23 = (CCBStageScene *)((char *)v23 + 12);
                }
                nullsub_2(p_m_pScene[1], p_m_pScene[2]);
                operator delete(p_m_pScene[1]);
                p_m_pScene[3] = (CCBStageScene *)((char *)v41 + 12 * v40);
                v33 = (((Array *)p_m_pScene))->Array::Size();
                v4 = v39;
                v2 = (Combat *)this;
                p_m_pScene[1] = v41;
                p_m_pScene[2] = (CCBStageScene *)&v41->m_vecFiveLineup[v33].y;
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
  result = (int)p_m_pScene[1];
  if ( result )
    return ((int)p_m_pScene[2] - result) / 12;
  return result;
}

// 0x0040DCF0
int * CCBStage::GetByIndex(int *p_DWORD)
{
  CCBEditor *m_pEditor; // edi
  int *i; // esi

  m_pEditor = (CCBEditor *)this->m_pEditor;
  for ( i = (int *)this->m_pRoleState; i != (int *)m_pEditor; i += 3 )
  {
    if ( PtrArray::CompareValues(i, p_DWORD) )
      break;
  }
  return this->m_pEditor != (CCBEditor *)i ? i : 0;
}

// 0x0040DD30
int CCBStage::Find(char *String1)
{
  CCBEditor *m_pRoleState; // esi

  m_pRoleState = (CCBEditor *)this->m_pRoleState;
  if ( m_pRoleState == this->m_pEditor )
    return 0;
  while ( _strcmpi(String1, (const char *)(m_pRoleState->m_NewItem[0].dwItemID + 36)) )
  {
    m_pRoleState = (CCBEditor *)((char *)m_pRoleState + 12);
    if ( m_pRoleState == this->m_pEditor )
      return 0;
  }
  return 1;
}

// 0x0040DD80
void CCBStage::Reset()
{
  CCBEditor *m_pRoleState; // edx

  m_pRoleState = (CCBEditor *)this->m_pRoleState;
  this->m_pCamControl = ((CCBCamControl *)((CCBCamControl *)-1));
  this->m_pRole[3] = 0;
  this->m_pEditor = ((CCBEditor *)(m_pRoleState));
  this->m_pRole[1] = this->m_pRole[0];
}

// 0x0044CFF0
int CCBStage::RandomizePositions()
{
  int v2; // ebx
  _BYTE *m_TaskArrA; // esi
  int result; // eax

  v2 = 16;
  m_TaskArrA = this->m_TaskArrA;
  do
  {
    m_TaskArrA += 208;
    --v2;
    *((_DWORD *)m_TaskArrA - 51) = rand() % 50 + 298;
    *((_DWORD *)m_TaskArrA - 52) = 758;
    *((_DWORD *)m_TaskArrA - 48) = 1144881152;
  }
  while ( v2 );
  result = 128;
  *(_DWORD *)&this->m_TaskArrA[20] = 256;
  *(_DWORD *)&this->m_TaskArrA[24] = 64;
  *(_DWORD *)&this->m_TaskArrA[228] = 512;
  *(_DWORD *)&this->m_TaskArrA[232] = 128;
  *(_DWORD *)&this->m_TaskArrA[436] = 128;
  *(_DWORD *)&this->m_TaskArrA[440] = 64;
  *(_DWORD *)&this->m_TaskArrA[644] = 128;
  *(_DWORD *)&this->m_TaskArrA[648] = 64;
  *(_DWORD *)&this->m_TaskArrA[852] = 128;
  *(_DWORD *)&this->m_TaskArrA[856] = 64;
  *(_DWORD *)&this->m_TaskArrA[1060] = 128;
  *(_DWORD *)&this->m_TaskArrA[1064] = 64;
  *(_DWORD *)&this->m_TaskArrA[1268] = 64;
  *(_DWORD *)&this->m_TaskArrA[1272] = 32;
  *(&this->m_nTotalCount + 12) = 128;
  *(&this->m_nTotalCount + 13) = 128;
  return result;
}

// 0x00459FA0
char CCBStage::sub_00459fa0(int thisa, unsigned __int8 pData)
{
  char result; // al

  if ( IsStateFlagSet(this) < 5 )
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory0(thisa);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelA(thisa);
    result = (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot0(thisa);
  }
  else
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory0(0);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelA(0);
    (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot0(0);
    result = thisa;
  }
  this->m_nTodo_99 = thisa;
  return result;
}

// 0x0045A020
char CCBStage::sub_0045a020(int thisa, unsigned __int8 pData)
{
  char result; // al

  if ( IsStateFlagSet(this) < 5 )
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory1(thisa);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelB(thisa);
    result = (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot1(thisa);
  }
  else
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory1(0);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelB(0);
    (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot1(0);
    result = thisa;
  }
  this->m_nTodo_9A = thisa;
  return result;
}

// 0x0045A0A0
char CCBStage::sub_0045a0a0(int thisa, unsigned __int8 pData)
{
  char result; // al

  if ( IsStateFlagSet(this) < 5 )
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory2(thisa);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelC(thisa);
    result = (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot2(thisa);
  }
  else
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory2(0);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelC(0);
    (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot2(0);
    result = thisa;
  }
  this->m_nTodo_9B = thisa;
  return result;
}

// 0x0045A120
char CCBStage::sub_0045a120(int thisa, unsigned __int8 pData)
{
  char result; // al

  if ( IsStateFlagSet(this) < 5 )
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory3(thisa);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelD(thisa);
    result = (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot3(thisa);
  }
  else
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory3(0);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelD(0);
    (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot3(0);
    result = thisa;
  }
  LOBYTE(this->m_nTaskCount) = thisa;
  return result;
}

// 0x0045A1A0
char CCBStage::sub_0045a1a0(int thisa, unsigned __int8 pData)
{
  char result; // al

  if ( IsStateFlagSet(this) < 5 )
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory4(thisa);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelE(thisa);
    result = (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot4(thisa);
  }
  else
  {
    (((PropUI *)*((PropUI **)&this->m_nTaskState + 116)))->PropUI::ShowCategory4(0);
    (((CCBRoleState *)*((CCBRoleState **)&this->m_nTaskState + 117)))->CCBRoleState::LayoutSlotPanelE(0);
    (((SaleUI *)*((SaleUI **)&this->m_nTaskState + 118)))->SaleUI::ToggleSlot4(0);
    result = thisa;
  }
  BYTE1(this->m_nTaskCount) = thisa;
  return result;
}

// 0x004C5C20
int CCBStage::GetReadyCount()
{
  int v2; // edi
  int result; // eax
  CCBTaskSlot280 *m_TaskArrC; // esi

  v2 = 0;
  result = *(_DWORD *)&this->m_TaskSlots[92];
  if ( result > 0 )
  {
    m_TaskArrC = this->m_TaskArrC;
    do
    {
      if ( *(_BYTE *)(*(_DWORD *)m_TaskArrC->m_pHead + 13) )
        (*(void ( **)(_DWORD))(**(_DWORD **)m_TaskArrC->m_pHead + 24))(*(_DWORD *)m_TaskArrC->m_pHead);
      result = *(_DWORD *)&this->m_TaskSlots[92];
      ++v2;
      m_TaskArrC = (CCBTaskSlot280 *)((char *)m_TaskArrC + 4);
    }
    while ( v2 < result );
  }
  return result;
}

// 0x004D1EF0
int CCBStage::GetActiveTaskCount()
{
  int result; // eax
  int v2; // edx

  result = 0;
  if ( (int)this->m_TempStorageNGH > 0 )
  {
    v2 = 0;
    do
    {
      ++result;
      *(_BYTE *)(v2 + this->m_nTaskCount + 4) = 0;
      v2 += 80;
    }
    while ( result < (int)this->m_TempStorageNGH );
  }
  this->m_pRole[9] = 0;
  this->m_pRole[10] = 0;
  this->m_NGHVariance = ((Actor *)((Actor *)-1));
  return result;
}

// 0x004D4D30
int CCBStage::GetTaskParam(int nVal, int nVal2)
{
  int v3; // edx
  int result; // eax

  v3 = 72 * nVal2;
  *(_DWORD *)(*((_DWORD *)&this->m_pCam->fov + 38 * nVal) + v3 + 8) = 3;
  result = *((_DWORD *)&this->m_pCam->fov + 38 * nVal);
  *(_DWORD *)(result + v3 + 16) = (_DWORD)this->m_pRoleState;
  return result;
}

// 0x004D4D70
char CCBStage::SetTaskState(int nVal)
{
  int v2; // edx
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *i; // eax

  v2 = 0;
  v3 = (_DWORD *)(&this->m_pCam->fov + 38 * nVal);
  v4 = (unsigned long)v3[1];
  if ( v4 <= 0 )
    return 1;
  for ( i = (_DWORD *)(*v3 + 8); *i == 4; i += 18 )
  {
    if ( ++v2 >= v4 )
      return 1;
  }
  return 0;
}

// 0x004DF6B0
int * CCBStage::InitStage(int nVal)
{
  memset(this, 0, 0x4618u);
  this->m_pCBSystem = ((CCBSystem *)((CCBSystem *)nVal));
  this->m_pRoleState = ((CCBRoleState *)(*(CCBRoleState **)(nVal + 20)));
  return (int *)this;
}

// 0x004DF700
char CCBStage::IsInitialized()
{
  (((CCBRoleState *)this))->CCBRoleState::ResetDialogSlots();
  return 1;
}

// 0x004DF710
void CCBStage::ResetRoundState()
{
  float *p_m_fSlot3; // esi
  gbPrintFont *v3; // edi
  unsigned int *v4; // eax
  gbGfxManager *pGfxMgr; // edx
  float v6; // st7
  gbPrintFont *v7; // edi
  float v8; // st7
  unsigned int *v9; // eax
  unsigned int v10; // edx
  gbGfxManager *v11; // eax
  float v12; // st7
  float v13; // st6
  gbPrintFont *v14; // ecx
  unsigned int v15; // eax
  float v16; // st7
  float v17; // st6
  unsigned __int8 m_pCam_high; // al
  unsigned int v19; // [esp+0xC] [ebp-0x34]
  unsigned int v20; // [esp+0x10] [ebp-0x30]
  int v21; // [esp+0x14] [ebp-0x2C]
  gbColorQuad v22; // [esp+0x38] [ebp-0x8] BYREF
  gbColorQuad v23; // [esp+0x3C] [ebp-0x4] BYREF

  v21 = 0;
  if ( (int)this->m_pCamControl > 0 )
  {
    p_m_fSlot3 = (float *)&this->m_TaskArrC[0].m_fSlot3;
    do
    {
      switch ( *((_DWORD *)p_m_fSlot3 - 69) )
      {
        case 1:
          v3 = gfxMgr->pFontMgr->pAllFont[2];
          pGfxMgr = (gbGfxManager *)v3->pGfxMgr;
          v3->curColor.Color = *v4;
          v6 = 40.0f / (float)g_DrvInfo.height;
          v3->ScaleX = 40.0f / (float)g_DrvInfo.width;
          v3->ScaleY = v6;
          ((void ( *)(float *, _DWORD, _DWORD, int, int))pGfxMgr->DrvInfo.subtype)(
            p_m_fSlot3 - 68,
            *((_DWORD *)p_m_fSlot3 - 3),
            *((_DWORD *)p_m_fSlot3 - 2),
            1176256512,
            1176256512);
          break;
        case 2:
          v7 = gfxMgr->pFontMgr->pAllFont[3];
          v8 = *p_m_fSlot3 / (float)g_DrvInfo.height * 2.5999999046325684f;
          v7->ScaleX = *p_m_fSlot3 / (float)g_DrvInfo.width + *p_m_fSlot3 / (float)g_DrvInfo.width;
          v7->ScaleY = v8;
          v10 = (unsigned long)*v9;
          v11 = (gbGfxManager *)v7->pGfxMgr;
          v7->curColor.Color = v10;
          ((void ( *)(gbPrintFont *, float *, _DWORD, _DWORD, int, int))v11->DrvInfo.subtype)(
            v7,
            p_m_fSlot3 - 68,
            *((_DWORD *)p_m_fSlot3 - 3),
            *((_DWORD *)p_m_fSlot3 - 2),
            1176256512,
            1176256512);
          break;
        case 3:
          v12 = *p_m_fSlot3 + *p_m_fSlot3;
          v13 = v12 / (float)g_DrvInfo.height;
          v14 = gfxMgr->pFontMgr->pAllFont[1];
          v14->ScaleX = v12 / (float)g_DrvInfo.width;
          v14->ScaleY = v13;
          if ( gbColorQuad::ColorQuadFmt )
          {
            BYTE2(v19) = *((_BYTE *)p_m_fSlot3 - 16);
            BYTE1(v19) = *((_BYTE *)p_m_fSlot3 - 15);
            LOBYTE(v19) = *((_BYTE *)p_m_fSlot3 - 14);
          }
          else
          {
            BYTE2(v19) = *((_BYTE *)p_m_fSlot3 - 14);
            LOWORD(v19) = *((_WORD *)p_m_fSlot3 - 8);
          }
          HIBYTE(v19) = *((_BYTE *)p_m_fSlot3 - 13);
          v15 = v19;
          goto LABEL_14;
        case 7:
          v16 = *p_m_fSlot3 * 3.0f;
          v17 = v16 / (float)g_DrvInfo.height;
          v14 = gfxMgr->pFontMgr->pAllFont[1];
          v14->ScaleX = v16 / (float)g_DrvInfo.width;
          v14->ScaleY = v17;
          if ( gbColorQuad::ColorQuadFmt )
          {
            BYTE2(v20) = *((_BYTE *)p_m_fSlot3 - 16);
            BYTE1(v20) = *((_BYTE *)p_m_fSlot3 - 15);
            LOBYTE(v20) = *((_BYTE *)p_m_fSlot3 - 14);
          }
          else
          {
            BYTE2(v20) = *((_BYTE *)p_m_fSlot3 - 14);
            LOWORD(v20) = *((_WORD *)p_m_fSlot3 - 8);
          }
          HIBYTE(v20) = *((_BYTE *)p_m_fSlot3 - 13);
          v15 = v20;
LABEL_14:
          v14->curColor.Color = v15;
          ((void ( *)(float *, _DWORD, _DWORD, int, int))v14->pGfxMgr->DrvInfo.subtype)(
            p_m_fSlot3 - 68,
            *((_DWORD *)p_m_fSlot3 - 3),
            *((_DWORD *)p_m_fSlot3 - 2),
            1176256512,
            1176256512);
          break;
        default:
          break;
      }
      p_m_fSlot3 += 70;
      ++v21;
    }
    while ( v21 < (int)this->m_pCamControl );
  }
  ((void ( *)(gbPrintFont *))gfxMgr->pFontMgr->pAllFont[1]->pGfxMgr->hGfxWnd)(gfxMgr->pFontMgr->pAllFont[1]);
  ((void ( *)(gbPrintFont *))gfxMgr->pFontMgr->pAllFont[2]->pGfxMgr->hGfxWnd)(gfxMgr->pFontMgr->pAllFont[2]);
  ((void ( *)(gbPrintFont *))gfxMgr->pFontMgr->pAllFont[3]->pGfxMgr->hGfxWnd)(gfxMgr->pFontMgr->pAllFont[3]);
  m_pCam_high = HIBYTE(this->m_pCam);
  this->m_pCamControl = ((CCBCamControl *)0);
  if ( m_pCam_high > 1u )
    this->CCBStage::SetupCamControl();
}

// 0x004DFA10
int CCBStage::CountActiveActions()
{
  int v2; // ebx
  int result; // eax
  float *p_m_fSlot0; // esi
  unsigned int v5; // edx
  CCBRoleState *m_pRoleState; // eax
  unsigned int v7; // [esp+0x10] [ebp-0x4]

  v2 = 0;
  result = (int)this->m_pCamControl;
  if ( result > 0 )
  {
    p_m_fSlot0 = (float *)&this->m_TaskArrC[0].m_fSlot0;
    do
    {
      if ( *((_DWORD *)p_m_fSlot0 - 66) == 5 )
      {
        *(float *)&this->m_pRoleState->m_pObjMsgBuffer2[232] = p_m_fSlot0[3];
        v5 = *((_DWORD *)p_m_fSlot0 + 1);
        v7 = *((_DWORD *)p_m_fSlot0 + 2);
        m_pRoleState = (CCBRoleState *)this->m_pRoleState;
        *(float *)&m_pRoleState->m_pObjMsgBuffer2[208] = *p_m_fSlot0;
        m_pRoleState = (CCBRoleState *)((char *)m_pRoleState + 888);
        m_pRoleState->m_fontcolor.Color = v5;
        m_pRoleState->m_wndcolor.Color = v7;
        (((CCBStageScene *)this->m_pRoleState))->CCBStageScene::LoadPointer(*((_BYTE *)p_m_fSlot0 - 1));
      }
      else if ( *((_DWORD *)p_m_fSlot0 - 66) == 6 )
      {
        (((RoleSystem *)this->m_pRoleState))->RoleSystem::SetColor(*((unsigned __int8 *)p_m_fSlot0 - 1));
      }
      result = (int)this->m_pCamControl;
      ++v2;
      p_m_fSlot0 += 70;
    }
    while ( v2 < result );
  }
  return result;
}

// 0x004DFB70
int CCBStage::UpdateTurnFlags(const char *pszName, float fVal, float fVal2, float fVal3)
{
  int result; // eax

  strcpy((char *)&this->m_pRole[70 * (int)this->m_pCamControl], pszName);
  this->m_TaskArrC[(int)this->m_pCamControl].m_fSlot0 = fVal;
  this->m_TaskArrC[(int)this->m_pCamControl].m_fSlot1 = fVal2;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 1;
  this->m_TaskArrC[(int)this->m_pCamControl].m_fSlot3 = fVal3;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)this->m_pCamControl + 1)) = (unsigned long)this->m_pEditor;
  result = (int)this->m_pCamControl + 1;
  this->m_pCamControl = ((CCBCamControl *)((CCBCamControl *)result));
  return result;
}

// 0x004DFC40
int CCBStage::InitSlotFlags(const char *pszName, int nVal, int nVal2, int nVal3)
{
  int result; // eax

  strcpy((char *)&this->m_pRole[70 * (int)this->m_pCamControl], pszName);
  this->m_TaskArrC[(int)this->m_pCamControl].m_fSlot0 = ((double)nVal + (double)nVal) / (double)g_DrvInfo.width - 1.0;
  this->m_TaskArrC[(int)this->m_pCamControl].m_fSlot1 = 1.0 - ((double)nVal2 + (double)nVal2) / (double)g_DrvInfo.height;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 1;
  this->m_TaskArrC[(int)this->m_pCamControl].m_fSlot3 = 16.0;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)this->m_pCamControl + 1)) = nVal3;
  result = (int)this->m_pCamControl + 1;
  this->m_pCamControl = ((CCBCamControl *)((CCBCamControl *)result));
  return result;
}

// 0x004DFF90
int CCBStage::AssignSlotData(char pData)
{
  int result; // eax

  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 6;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)this->m_pCamControl + 1)) = (unsigned long)this->m_pEditor;
  this->m_TaskArrC[(int)this->m_pCamControl].m_bFlag = pData;
  result = (int)this->m_pCamControl + 1;
  this->m_pCamControl = ((CCBCamControl *)((CCBCamControl *)result));
  return result;
}

// 0x004DFFF0
__int64 CCBStage::CalculateTurnOrder(float fVal, int nVal)
{
  __int64 result; // rax

  this->m_pCam = ((CCBStageCam *)((CCBStageCam *)nVal));
  result = (__int64)fVal;
  HIBYTE(this->m_pCam) = result;
  return result;
}

// 0x004E0010
void CCBStage::SetupCamControl()
{
  _BYTE v1[4]; // [esp+0x4] [ebp-0x10] BYREF
  int v2; // [esp+0x10] [ebp-0x4]

  PushMatrixStacks(v1);
  v2 = 0;
  crt_sub_00540070();
  v2 = -1;
  PopMatrixStacks(v1);
}

// 0x004E02F0
int * CCBStage::ResetAndSetSystem(int nVal)
{
  memset(this, 0, 0x2598u);
  this->CCBStage::ResetTurnSlots();
  this->m_pCBSystem = ((CCBSystem *)((CCBSystem *)nVal));
  this->m_pRoleState = ((CCBRoleState *)0);
  g_nCombatViewMode = 0;
  g_todo_BFDA50 = 0;
  g_hMainWnd = 0;
  pfVal = (int)this;
  return (int *)this;
}

// 0x004E0330
int CCBStage::ClearAll()
{
  int result; // eax

  result = 0;
  memset(this, 0, 0x2598u);
  return result;
}

// 0x004E0340
int CCBStage::ResetTurnSlots()
{
  int result; // eax

  result = -1;
  this->m_fTurnTimer = NAN;
  this->m_nTurnSlot0 = -1;
  this->m_nTurnSlot1 = -1;
  this->m_nTurnSlot2 = -1;
  this->m_nTurnSlot3 = -1;
  this->m_nTurnSlot4 = -1;
  this->m_nTurnSlot5 = -1;
  this->m_nResultSlot0 = -1;
  this->m_nResultSlot1 = -1;
  return result;
}

// 0x004E0380
char CCBStage::SyncTimeScale()
{
  this->CCBStage::ResetTurnSlots();
  formal = this->m_pCBSystem->m_fTimeScale;
  if ( g_bTestCombat )
  {
    g_todo_BFDA50 = CreateDialogParamA(hInstance, (LPCSTR)0x66, (HWND)g_todo_BFDA4C, DialogFunc, 0);
    g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x6A, (HWND)g_todo_BFDA4C, (DLGPROC)CCBUI::CloseDialog, 0);
  }
  return 1;
}

// 0x004E03F0
char CCBStage::DestroyDialog()
{
  if ( g_todo_BFDA50 )
  {
    DestroyWindow(g_todo_BFDA50);
    g_todo_BFDA50 = 0;
  }
  if ( g_hMainWnd )
  {
    DestroyWindow(g_hMainWnd);
    g_hMainWnd = 0;
  }
  return 1;
}

// 0x004E0430
char CCBStage::CreatePreviewDialog()
{
  CCBSystem *m_pCBSystem; // eax
  HWND DlgItem; // eax

  m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
  this->m_pRoleState = ((CCBRoleState *)(this->m_pCBSystem->m_pRoleState));
  if ( BYTE1(m_pCBSystem->m_nTimesOfCombat) )
  {
    ::ShowWindow(g_todo_BFDA50, 4);
    ::ShowWindow(g_hMainWnd, 4);
  }
  LOBYTE(g_bWPARAM_17A9926) = 0;
  (((PAL_GDB *)this))->PAL_GDB::LoadConfigFromINI();
  DlgItem = GetDlgItem(g_todo_BFDA50, 1006);
  SendMessageA(DlgItem, 0xF5u, 0, 0);
  (((CCBRoleState *)this))->CCBRoleState::UpdateDebugTreeView();
  (((CCBRoleState *)this))->CCBRoleState::HandleDlgMessage();
  SetActiveWindow((HWND)g_todo_BFDA4C);
  return 1;
}

// 0x004E0530
bool CCBStage::ProcessAction(HWND pData)
{
  if ( !pData )
    return 0;
  if ( pData == (HWND)g_todo_BFDA4C )
    return 1;
  if ( pData == g_todo_BFDA50 )
    return 1;
  if ( pData == g_hMainWnd )
    return 1;
  if ( pData == (HWND)dwInitParam )
    return 1;
  if ( pData == (HWND)g_hCombatDlg1 )
    return 1;
  if ( pData == (HWND)g_hCombatDlg2 )
    return 1;
  if ( pData == (HWND)g_nActorRenderCount )
    return 1;
  return pData == (HWND)g_hCBStageCamDlg;
}

// 0x004E05B0
void CCBStage::CreatePreview(float fVal)
{
  HWND DlgItem; // edi
  HWND v2; // esi

  if ( formal != fVal )
  {
    formal = fVal;
    DlgItem = GetDlgItem(g_todo_BFDA50, 1001);
    v2 = GetDlgItem(g_todo_BFDA50, 1003);
    SendMessageA(DlgItem, 0x405u, 1u, (__int64)(100.0 * formal));
    sprintf(unk_17A95E4, "Speed%1.2f", formal);
    SendMessageA(v2, 0xCu, 0, (LPARAM)unk_17A95E4);
  }
}

// 0x004E0650
BOOL CCBStage::DestroyPreviewWindow()
{
  if ( g_nActorRenderCount )
    DestroyWindow((HWND)g_nActorRenderCount);
  g_nActorRenderCount = (int)CreateDialogParamA(
                               hInstance,
                               (LPCSTR)0x6F,
                               (HWND)g_todo_BFDA4C,
                               (DLGPROC)PAL_GDB::PartySetupDialogProc,
                               0);
  return ::ShowWindow((HWND)g_nActorRenderCount, 5);
}

// 0x004E2C50
void CCBStage::InitUIByName()
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
  if ( this->m_pRoleState->m_pObjMsgBuffer[892 * roleIdx + 153] )
  {
    EnableWindow(v4, 1);
    if ( (int)roleIdx < 5 )
    {
      switch ( roleIdx )
      {
        case 0u:
          v20 = roleIdx;
          v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Jingtian");
          goto LABEL_11;
        case 1u:
          v20 = roleIdx;
          v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Xuejian");
          goto LABEL_11;
        case 2u:
          v20 = roleIdx;
          v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Longkui");
          goto LABEL_11;
        case 3u:
          v20 = roleIdx;
          v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Zixuan");
          goto LABEL_11;
        case 4u:
          v20 = roleIdx;
          v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Changqing");
LABEL_11:
          sprintf((char *const)&g_CCBStageCamBuffer, "%s%d", v7, v20);
          break;
        default:
          break;
      }
    }
    else
    {
      inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(roleIdx);
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(inited->dwID);
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", v6 + 600);
    }
    SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v8 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(roleIdx, 0);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v8);
    SendMessageA(v3, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v9 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(roleIdx, 1);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v9);
    SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    RoleGPBak = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleGPBak(roleIdx, 0);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], RoleGPBak);
    SendMessageA(v22, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v11 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleGPBak(roleIdx, 1);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v11);
    SendMessageA(v23, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    Role = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRole(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], Role);
    SendMessageA(v24, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v13 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRole(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v13);
    SendMessageA(v25, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v14 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v14->nLevel);
    SendMessageA(v26, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v15 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v15->nSpeed);
    SendMessageA(v27, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v16 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v16->nAttack);
    SendMessageA(v28, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v17 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v17->nDefence);
    SendMessageA(v29, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v18 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v18->nLuck);
    SendMessageA(v30, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    v19 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(roleIdx);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], *(_DWORD *)&v19->bLostMoneyGetLife);
    SendMessageA(v31, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
  }
  else
  {
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&unk_5D89A4);
    SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    EnableWindow(v4, 0);
  }
}

// 0x004F06C0
bool CCBStage::FindThreadByParam(int nVal, unsigned int dwVal)
{
  if ( !nVal )
    return 0;
  if ( *(_DWORD *)(nVal + 12) == dwVal )
    return 1;
  return dwVal <= 0xA && *(_BYTE *)(nVal + dwVal + 29);
}

// 0x004F4AA0
CCBStageRole * CCBStage::GetRole(int index)
{
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int *i; // eax
  int RoleNum; // eax
  int pCmd[11]; // [esp+0xC] [ebp-0x2C] BYREF
  int nVal; // [esp+0x40] [ebp+0x8]

  memset(pCmd, 0, sizeof(pCmd));
  v3 = (((CCBRoleState *)this))->CCBRoleState::GetRoleHP(index) - 1;
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)&this->m_TaskArrC[0]._todo_018[892 * index + 248]);
      v4 = 0;
      for ( i = (int *)(v5 + 760); nVal != *i; ++i )
      {
        if ( ++v4 >= 4 )
          return 0;
      }
      RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*i);
      return (CCBStageRole *)*(__int16 *)(RoleNum + 592);
    }
    return 0;
  }
  pCmd[2] = index;
  pCmd[0] = 261;
  pCmd[1] = nVal;
  LOBYTE(pCmd[10]) = 1;
  if ( !(((CCBRoleState *)this))->CCBRoleState::ValidateCommandTarget(pCmd) )
  {
    pCmd[0] = 260;
    if ( !(((CCBRoleState *)this))->CCBRoleState::ValidateCommandTarget(pCmd) )
      return 0;
  }
  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nVal);
  return (CCBStageRole *)*(__int16 *)(RoleNum + 592);
}

// 0x004F6CD0
char CCBStage::CheckGDBTypeCompat(unsigned int *pdwVal)
{
  unsigned int v2; // eax

  v2 = (unsigned long)*pdwVal;
  if ( *pdwVal >= 0x104 )
  {
    if ( v2 <= 0x105 )
    {
      if ( *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pdwVal[1]) + 666) == 2 )
        return 1;
    }
    else if ( v2 == 262 && *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(pdwVal[1]) + 748) == 2 )
    {
      return 1;
    }
  }
  return 0;
}

// 0x004FB9A0
CCBStage::CCBStage(int pCBSystem)
{
  int *p_m_TaskQueue; // edx
  int v3; // esi
  int *v4; // edi

  p_m_TaskQueue = (int *)&this->m_TaskQueue;
  v3 = 256;
  do
  {
    v4 = (int *)p_m_TaskQueue;
    p_m_TaskQueue += 658;
    --v3;
    memset(v4, 0, 0x2Cu);
  }
  while ( v3 );
  memset(this, 0, 0xA48B0u);
  this->m_pCBSystem = ((CCBSystem *)((CCBSystem *)pCBSystem));
  this->m_pRoleState = ((CCBRoleState *)(*(CCBRoleState **)(pCBSystem + 16)));
  this;
}

// 0x004FB9F0
unsigned int CCBStage::_todo_004FB9F0()
{
  Actor **p_m_WPXVariance; // ecx
  unsigned int result; // eax

  p_m_WPXVariance = (Actor **)&this->m_WPXVariance;
  *p_m_WPXVariance = 0;
  p_m_WPXVariance[1] = 0;
  this->m_nStageStatus = 0;
  this->m_nTaskCount = 0;
  memset(&this->m_nForceDelTask, 0, 0xA4800u);
  this->m_nClearRoleAllTask = -1;
  this->m_nRoleSlot = -1;
  this->m_pShadow = ((CCBStageShadow *)((CCBStageShadow *)-1));
  this->m_pEffect = ((CCBStageEffect *)0);
  this->m_BFARole = 0;
  LOWORD(this->m_BFARound) = 0;
  BYTE2(this->m_BFARound) = 0;
  memset(&this->m_ptMousePos, 0, 0x2Cu);
  this->m_nTodo_094 = 0;
  result = gbCrc32Compute("over");
  this->m_nTodo_A48A8 = result;
  return result;
}

// 0x004FBE50
bool CCBStage::Create()
{
  int v2; // ebp
  CCBStageScene *m_pScene; // ecx
  CCBStageScene *v4; // edi
  CCBStage **i; // edi
  CCBStage *v6; // ebx
  std::codecvt_base *m_pCam; // ecx
  CCBStageCam *v8; // ecx
  CCBCamControl *m_pCamControl; // ecx
  CCBCamControl *v10; // edi
  std::codecvt_base *m_TempStorageNGH; // ecx
  Actor *v12; // edi
  Actor *m_NGHVariance; // ecx
  Actor *v14; // edi
  Actor *m_TempStorageWPX; // ecx
  Actor *v16; // edi
  void *v18; // [esp+0x0] [ebp-0x10]

  v2 = 0;
  m_pScene = (CCBStageScene *)this->m_pScene;
  if ( m_pScene )
  {
    (((CCBStageScene *)m_pScene))->CCBStageScene::~CCBStageScene();
    v4 = (CCBStageScene *)this->m_pScene;
    if ( v4 )
    {
      NullCallback(v18);
      operator delete(v4);
    }
    this->m_pScene = ((CCBStageScene *)0);
    for ( i = (CCBStage **)this->m_pRole; *i; ++i )
    {
      (((CCBStage *)*i))->CCBStage::IsAtInitPos();
      v6 = (CCBStage *)*i;
      if ( *i )
      {
        NullCallback(v18);
        operator delete(v6);
      }
      *i = 0;
      if ( ++v2 >= 11 )
      {
        m_pCam = (std::codecvt_base *)this->m_pCam;
        if ( m_pCam )
        {
          (((std::codecvt_base *)m_pCam))->do_always_noconv();
          v8 = (CCBStageCam *)this->m_pCam;
          if ( v8 )
            (*(void ( **)(CCBStageCam *, int))LODWORD(v8->fov))(v8, 1);
          this->m_pCam = ((CCBStageCam *)0);
          m_pCamControl = (CCBCamControl *)this->m_pCamControl;
          if ( m_pCamControl )
          {
            (((CCBCamControl *)m_pCamControl))->CCBCamControl::Init();
            v10 = (CCBCamControl *)this->m_pCamControl;
            if ( v10 )
            {
              (((j_j_codecvt_base *)this->m_pCamControl))->j_j_codecvt_base::do_always_noconv();
              operator delete(v10);
            }
            this->m_pCamControl = ((CCBCamControl *)0);
            m_TempStorageNGH = (std::codecvt_base *)this->m_TempStorageNGH;
            if ( m_TempStorageNGH )
            {
              (((std::codecvt_base *)m_TempStorageNGH))->do_always_noconv();
              v12 = (Actor *)this->m_TempStorageNGH;
              if ( v12 )
              {
                NullCallback(v18);
                operator delete(v12);
              }
              this->m_TempStorageNGH = ((Actor *)0);
              m_NGHVariance = (Actor *)this->m_NGHVariance;
              if ( m_NGHVariance )
              {
                (((CCBStageShadow *)m_NGHVariance))->CCBStageShadow::~CCBStageShadow();
                v14 = (Actor *)this->m_NGHVariance;
                if ( v14 )
                {
                  NullCallback(v18);
                  operator delete(v14);
                }
                this->m_NGHVariance = ((Actor *)0);
                m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
                if ( m_TempStorageWPX )
                {
                  (((CCBCamControl *)m_TempStorageWPX))->CCBCamControl::DoList();
                  v16 = (Actor *)this->m_TempStorageWPX;
                  if ( v16 )
                  {
                    sub_508460(this->m_TempStorageWPX);
                    operator delete(v16);
                  }
                  this->m_TempStorageWPX = ((Actor *)0);
                  return 1;
                }
              }
            }
          }
        }
        return 0;
      }
    }
  }
  return 0;
}

// 0x004FBF90
bool CCBStage::Destroy()
{
  CCBStageScene *m_pScene; // ecx
  char v3; // al
  int v5; // ebx
  int v6; // edi
  CCBStage **m_pRole; // esi
  CCBStage *v8; // ecx
  CCBStageCam *m_pCam; // ecx
  CCBCamControl *m_pCamControl; // ecx
  char v11; // al
  Actor *m_NGHVariance; // ecx
  char v13; // al
  Actor *m_TempStorageWPX; // ecx
  char v15; // al
  Actor *m_TempStorageNGH; // ecx

  this->CCBStage::_todo_004FB9F0();
  this->m_pEditor = ((CCBEditor *)(this->m_pCBSystem->m_pEditor));
  m_pScene = (CCBStageScene *)this->m_pScene;
  if ( !m_pScene )
    return 0;
  (((CCBStageScene *)m_pScene))->CCBStageScene::Reset();
  if ( !v3 )
    return 0;
  v5 = 0;
  v6 = 0;
  m_pRole = (CCBStage **)this->m_pRole;
  do
  {
    if ( !*m_pRole )
      return 0;
    (((CCBStage *)*m_pRole))->CCBStage::GetRotAngle();
    v8 = (CCBStage *)*m_pRole;
    if ( this->m_pRoleState->m_pObjMsgBuffer[v6 + 153] )
    {
      if ( !(((CCBStage *)v8))->CCBStage::IsAtProtectPos(v5, 0, 0) )
        return 0;
    }
    else if ( !(((CCBStage *)v8))->CCBStage::IsAtProtectPos(v5, 0, 0) )
    {
      return 0;
    }
    v6 += 892;
    ++v5;
    ++m_pRole;
  }
  while ( v6 < 9812 );
  m_pCam = (CCBStageCam *)this->m_pCam;
  if ( !m_pCam || !(((CameraCtrl *)m_pCam))->CameraCtrl::InitFromScreen() )
    return 0;
  m_pCamControl = (CCBCamControl *)this->m_pCamControl;
  if ( !m_pCamControl )
    return 0;
  (((CCBStageCam *)m_pCamControl))->CCBStageCam::Update();
  if ( !v11 )
    return 0;
  m_NGHVariance = (Actor *)this->m_NGHVariance;
  if ( !m_NGHVariance )
    return 0;
  (((CCBStageShadow *)m_NGHVariance))->CCBStageShadow::Reset();
  if ( !v13 )
    return 0;
  m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
  if ( !m_TempStorageWPX )
    return 0;
  (((CCBCamControl *)m_TempStorageWPX))->CCBCamControl::ResetListFlag();
  if ( !v15 )
    return 0;
  m_TempStorageNGH = (Actor *)this->m_TempStorageNGH;
  if ( !m_TempStorageNGH || !(((CCBStage *)m_TempStorageNGH))->CCBStage::IsInitialized() )
    return 0;
  (((CCBStage *)this->m_TempStorageNGH))->CCBStage::CalculateTurnOrder(0.0, 0);
  return 1;
}

// 0x004FC0A0
void CCBStage::Update()
{
  void *v1; // esi
  CCBStage **m_pRole; // esi
  int v4; // ebx
  int *v5; // eax
  float effect; // [esp+0x0] [ebp-0x10]
  void *v7; // [esp+0x4] [ebp-0xC]
  void *v8; // [esp+0x4] [ebp-0xC]
  BOOL v9; // [esp+0x8] [ebp-0x8]

  if ( this->m_nStageStatus != 1 )
  {
    (((GRPinput *)&g_Input))->GRPinput::GetCursorPos((LPPOINT)&this->m_WPXVariance);
    (((CCBStageScene *)this->m_pScene))->CCBStageScene::SetBattleFieldAttr();
    if ( g_nCombatViewMode == 1 )
      this->CCBStage::Update_c150();
    else
      this->CCBStage::Render();
    v7 = (void *)v1;
    m_pRole = (CCBStage **)this->m_pRole;
    v4 = 11;
    do
    {
      if ( (*m_pRole)->m_TaskSlots[80] )
        (((CCBStage *)*m_pRole))->CCBStage::ApplyTaskTimeScale((int)v7, v9);
      ++m_pRole;
      --v4;
    }
    while ( v4 );
    (((CCBStage *)this->m_pCam))->CCBStage::ProcessTurn();
    (((CCBCamControl *)this->m_pCamControl))->CCBCamControl::DoTask();
    NullCallback(v7);
    NullCallback(v8);
    this->CCBStage::UpdatePhysics();
    effect = this->m_pCBSystem->m_DeltaTime;
    v5 = (((CEffectSystem *)this->m_pCBSystem))->CEffectSystem::DestroyAllEffect();
    (((CEffectSystem *)v5))->CEffectSystem::SetVisible(effect);
  }
}

// 0x004FC150
int CCBStage::Update_c150()
{
  CCBDisplayChain *m_pDisplayChain; // ecx
  CCBStageCam *m_pCam; // ecx
  const gbVec3D *ViewTarget; // edi
  float v5; // st7
  float *v6; // eax
  float v7; // eax
  CCBStageShadow *m_pShadow; // eax
  float *v9; // eax
  int result; // eax
  float y; // ecx
  float z; // edx
  float v13; // [esp+0x1C] [ebp-0x7C]
  float v14; // [esp+0x20] [ebp-0x78]
  float v15; // [esp+0x24] [ebp-0x74]
  int pOut; // [esp+0x30] [ebp-0x68] BYREF
  int pOut2; // [esp+0x34] [ebp-0x64] BYREF
  struct gbVec3D pPos; // [esp+0x38] [ebp-0x60] BYREF
  struct gbVec3D v19; // [esp+0x44] [ebp-0x54] BYREF
  struct gbVec3D v20; // [esp+0x50] [ebp-0x48] BYREF
  struct gbVec3D v21; // [esp+0x5C] [ebp-0x3C] BYREF
  gbVec3D pTarget[2]; // [esp+0x68] [ebp-0x30] BYREF
  gbRay v23; // [esp+0x80] [ebp-0x18] BYREF

  v21.y = 1.0;
  pPos.y = 0.0;
  v21.x = 0.0;
  v21.z = 0.0;
  pPos.x = 1.0;
  pPos.z = 1.0;
  v20.y = 0.0;
  memset(&v19, 0, sizeof(v19));
  v20.x = 1.0;
  v20.z = 1.0;
  memset(&v23, 0, 12);
  m_pDisplayChain = (CCBDisplayChain *)this->m_pDisplayChain;
  LODWORD(pPos.x) = (unsigned long)this->m_WPXVariance;
  LODWORD(pPos.y) = (unsigned long)m_pDisplayChain;
  m_pCam = (CCBStageCam *)this->m_pCam;
  pOut = 0;
  pOut2 = 0;
  ViewTarget = (const gbVec3D *)(((CameraCtrl *)m_pCam))->CameraCtrl::GetViewTarget(pTarget, &pPos.x);
  (((gbVec3D *)&v23.Origin))->gbVec3D::operator=(*(ViewTarget));
  (((gbVec3D *)&v23.Direction))->gbVec3D::operator=(*(ViewTarget + 1));
  v5 = (((gbRay *)&v23))->gbRay::IntersectPlane(v21,  v20);
  pPos.x = v23.Direction.x * v5;
  pPos.y = v23.Direction.y * v5;
  v15 = v23.Origin.z + v5 * v23.Direction.z;
  v14 = v23.Origin.y + pPos.y;
  v13 = pPos.x + v23.Origin.x;
  pTarget->gbVec3D::gbVec3D(v13, v14, v15);
  pPos.x = *v6;
  pPos.y = v6[1];
  v7 = v6[2];
  v19.x = pPos.x;
  pPos.z = v7;
  v19.z = v7;
  m_pShadow = (CCBStageShadow *)this->m_pShadow;
  v19.y = pPos.y;
  if ( m_pShadow != (CCBStageShadow *)-1 )
  {
    (((gbVec3D *)&this->m_pRole[(_DWORD)m_pShadow]->m_Task[62].eMode))->gbVec3D::operator=(*(&v19));
    v9 = (float *)this->m_pRole[(int)this->m_pShadow];
    v9[1646] = v19.x;
    v9 += 1646;
    v9[1] = v19.y;
    v9[2] = v19.z;
  }
  result = (int)this->m_pScene;
  if ( *(_BYTE *)(result + 964) )
  {
    if ( (g_Input.KeyInfo[15].Data & 0xF) == 1 )
    {
      pPos = v19;
      y = v19.y;
      *(float *)(result + 888) = v19.x;
      z = pPos.z;
      *(float *)(result + 892) = y;
      *(float *)(result + 896) = z;
    }
    else
    {
      (((GRPinput *)&g_Input))->GRPinput::GetMousePos(&pOut, &pOut2);
      result = (int)this->m_pScene;
      *(float *)(result + 912) = (double)pOut + *(float *)(result + 912);
      this->m_pScene->m_vecFiveLineupPos.x = (double)pOut2 * 0.016666668 + this->m_pScene->m_vecFiveLineupPos.x;
    }
  }
  return result;
}

// 0x004FC3A0
void CCBStage::EditorUpdate(float fVal)
{
  CEffectSystem *v1; // ecx
  float v2; // edi
  CEffectSystem *v3; // esi
  int v4; // ebp
  gbRenderEffect *m_pAdditiveBlend; // eax
  float v6; // eax
  gbRenderEffect *v7; // eax
  gbSceneGraph *pSceneGraph; // ebx
  gbCamera *p_RefCount; // eax
  gbMatrixStack *v10; // edi
  int v11; // eax
  CCBStage **v12; // eax
  CCBStage *v13; // ecx
  long double v14; // st7
  bool v15; // cc
  gbRenderEffect *v16; // eax
  gbCamera *v17; // eax
  float su; // ecx
  float v19; // ecx
  CEffectSystem *v20; // ecx
  int *v21; // eax
  float v22; // [esp+0x18] [ebp-0x3C]
  float v23; // [esp+0x20] [ebp-0x34]
  CCBStage **p_sv; // [esp+0x38] [ebp-0x1C] BYREF
  float v25; // [esp+0x3C] [ebp-0x18]
  float *v26; // [esp+0x40] [ebp-0x14]
  gbVec3D dwMsg; // [esp+0x48] [ebp-0xC] BYREF

  v3 = (CEffectSystem *)v1;
  v4 = 0;
  gfxMgr->fSelfIllum = 0.0;
  m_pAdditiveBlend = (gbRenderEffect *)v1->m_pAdditiveBlend;
  if ( m_pAdditiveBlend )
    LODWORD(v6) = (unsigned long)&m_pAdditiveBlend->RefCount;
  else
    v6 = 0.0f;
  v22 = v6;
  (((CEffectSystem *)v1))->CEffectSystem::DestroyAllEffect();
  (((CEffectSystem *)v22))->CEffectSystem::HandleViewMove(v2);
  v7 = (gbRenderEffect *)v3->m_pAdditiveBlend;
  pSceneGraph = gfxMgr->pSceneGraph;
  if ( v7 )
    p_RefCount = (gbCamera *)&v7->RefCount;
  else
    p_RefCount = 0;
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(p_RefCount);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v10 = gfxMgr->pMatrixStack[1];
  (((CameraCtrl *)v3->m_pAdditiveBlend))->CameraCtrl::SetAsCurrent(3);
  (((gbMatrixStack *)v10))->gbMatrixStack::Push();
  (*(void ( **)(int, _DWORD))(*(_DWORD *)(LODWORD(v3->m_DefaultUVSet[3].eu) + 16) + 16))(
    LODWORD(v3->m_DefaultUVSet[3].eu) + 16,
    0);
  if ( !HIBYTE(v3->m_DefaultUVSet[5].su) )
  {
    (((CCBStageScene *)LODWORD(v3->m_DefaultUVSet[0].su)))->CCBStageScene::GetBattleFieldSubdueAttr(v10);
    p_sv = (CCBStage **)&v3->m_DefaultUVSet[0].sv;
    do
    {
      if ( g_nCombatViewMode == 1 || (v11 = (int)v3->m_pDisplay + v4, *(_BYTE *)(v11 + 577)) && !*(_BYTE *)(v11 + 1432) )
        (((CCBStage *)*p_sv))->CCBStage::RunActiveTask(v10);
      v4 += 892;
      ++p_sv;
    }
    while ( v4 < 9812 );
    v12 = (CCBStage **)&v3->m_DefaultUVSet[0].sv;
    p_sv = 0;
    v26 = (float *)&v3->m_DefaultUVSet[0].sv;
    do
    {
      v13 = (CCBStage *)*v12;
      if ( (*v12)->m_TaskArrC[0].m_pHead[0] )
      {
        memset(&dwMsg, 0, sizeof(dwMsg));
        (((CCBStage *)v13))->CCBStage::CalcTaskWorldMatrix(&dwMsg);
        v14 = sin(*(float *)(*(_DWORD *)v3 + 80) * 10.0 + (double)(int)p_sv);
        v25 = v14;
        dwMsg.y = v14 * 5.0f + dwMsg.y + 6.0f;
        (((gbMatrixStack *)v10))->gbMatrixStack::Push();
        (((gbMatrixStack *)v10))->gbMatrixStack::Translate(dwMsg.x,   dwMsg.y,   dwMsg.z);
        v23 = v25 * 0.20000000298023224f + 1.0f;
        (((gbMatrixStack *)v10))->gbMatrixStack::Scale(1.0,   v23,   1.0);
        (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(LODWORD(v3->m_DefaultUVSet[0].su) + 616) + 16))(
          *(_DWORD *)(LODWORD(v3->m_DefaultUVSet[0].su) + 616),
          0);
        (((gbMatrixStack *)v10))->gbMatrixStack::Pop();
      }
      v12 = (CCBStage **)(v26 + 1);
      v15 = (int)p_sv + 1 < 5;
      p_sv = (CCBStage **)((char *)p_sv + 1);
      ++v26;
    }
    while ( v15 );
  }
  (((SceneMgr *)*(SceneMgr **)(*(_DWORD *)v3 + 44)))->SceneMgr::RenderUpdate();
  (((SceneMgr *)*(SceneMgr **)(*(_DWORD *)v3 + 48)))->SceneMgr::RenderUpdate();
  (((gbMatrixStack *)v10))->gbMatrixStack::Pop();
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
  (((CCBStageShadow *)LODWORD(v3->m_DefaultUVSet[3].sv)))->CCBStageShadow::Create();
  v16 = (gbRenderEffect *)v3->m_pAdditiveBlend;
  if ( v16 )
    v17 = (gbCamera *)&v16->RefCount;
  else
    v17 = 0;
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(v17);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  (*(void ( **)(int, _DWORD))(*(_DWORD *)(LODWORD(v3->m_DefaultUVSet[3].eu) + 16) + 16))(
    LODWORD(v3->m_DefaultUVSet[3].eu) + 16,
    0);
  (*(void ( **)(_DWORD))(**(_DWORD **)(LODWORD(v3->m_DefaultUVSet[0].su) + 612) + 16))(*(_DWORD *)(LODWORD(v3->m_DefaultUVSet[0].su) + 612));
  (((SceneMgr *)*(SceneMgr **)(*(_DWORD *)v3 + 44)))->SceneMgr::RenderAll();
  (((SceneMgr *)*(SceneMgr **)(*(_DWORD *)v3 + 48)))->SceneMgr::RenderAll();
  (((C3DSpark *)0))->C3DSpark::Render();
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
  if ( byte_17A9927 )
  {
    (((CCBStageScene *)LODWORD(v3->m_DefaultUVSet[0].su)))->CCBStageScene::IsSameBattleFieldAttr();
    (((CCBStageScene *)LODWORD(v3->m_DefaultUVSet[0].su)))->CCBStageScene::GetBFASubdueFM();
  }
  if ( *(_BYTE *)(*(_DWORD *)v3 + 133) )
  {
    if ( g_nCombatViewMode == 1 )
    {
      su = v3->m_DefaultUVSet[0].su;
      if ( !*(_BYTE *)(LODWORD(su) + 963) )
        goto LABEL_31;
      (((CCBStageScene *)LODWORD(su)))->CCBStageScene::LoadPointer(60);
    }
    if ( g_nCombatViewMode == 4 )
    {
      v19 = v3->m_DefaultUVSet[0].su;
      if ( *(_BYTE *)(LODWORD(v19) + 963) )
        (((CCBStageScene *)LODWORD(v19)))->CCBStageScene::LoadPointer(60);
      (((CCCTData *)v3->m_pAlphaBlend))->CCCTData::~CCCTData();
    }
  }
LABEL_31:
  (((CCBStage *)LODWORD(v3->m_DefaultUVSet[3].su)))->CCBStage::CountActiveActions();
  v21 = (((CEffectSystem *)v20))->CEffectSystem::DestroyAllEffect();
  (((CEffectSystem *)v21))->CEffectSystem::Update();
  (((CCBStage *)g_pEffectSystem))->CCBStage::GetReadyCount();
  PushMatrixStacks(&p_sv);
  dwMsg.z = 0.0f;
  (((CGameData *)&g_gamefrm))->CGameData::ProcessDialog();
  (((CCBStage *)LODWORD(v3->m_DefaultUVSet[3].su)))->CCBStage::ResetRoundState();
  if ( !g_bEditorMode )
    (((Logger *)&g_InputState))->Logger::Render();
  dwMsg.z = NAN;
  PopMatrixStacks(&p_sv);
}

// 0x004FC6F0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBStage::Render()
{
  this->CCBStage::GetTask();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004FC700
int CCBStage::GetRoleIndex(int nameCrc, const void *pData, char a4)
{
  int v5; // ebp
  _BYTE *i; // eax
  char *v8; // edi

  if ( this->m_nTaskCount >= 246 )
    (((CCBSystem *)this->m_pCBSystem))->CCBSystem::CreateUIObj(&dword_5DB6C4, 0, 0x30u);
  v5 = 0;
  for ( i = (_BYTE *)&this->m_nTaskState; *i; i += 2632 )
  {
    if ( ++v5 >= 256 )
      return -1;
  }
  v8 = (char *)this + 2632 * v5;
  *((_DWORD *)v8 + 43) = 2;
  v8[2796] = 1;
  v8[2797] = a4;
  *((_DWORD *)v8 + 686) = (((CCBSystem *)this->m_pCBSystem))->CCBSystem::ProcProtect();
  *((_DWORD *)v8 + 44) = 0;
  *((_DWORD *)v8 + 42) = nameCrc;
  *((_DWORD *)v8 + 687) = 0;
  if ( pData )
    qmemcpy(v8 + 2752, pData, 0x2Cu);
  else
    *((_DWORD *)v8 + 690) = -1;
  ++this->m_nTaskCount;
  return v5;
}

// 0x004FC7D0
int CCBStage::GetRoleName(
        
        int nameCrc,
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int *p_DWORD,
        int nVal5,
        int nVal6)
{
  int v9; // ebp
  int v10; // ebx
  _BYTE *i; // eax
  int *v13; // esi
  int *v14; // esi

  v9 = 0;
  v10 = 2632 * nameCrc;
  for ( i = &this->m_TaskSlots[2632 * nameCrc + 40]; *i; i += 80 )
  {
    if ( ++v9 >= 32 )
      return -1;
  }
  v13 = (int *)&this->m_TaskSlots[80 * v9 + v10];
  memset(v13, 0, 0x50u);
  this->m_TaskSlots[80 * v9 + 41 + v10] = 0;
  this->m_TaskSlots[80 * v9 + 40 + v10] = 1;
  *(_DWORD *)&this->m_TaskSlots[80 * v9 + 16 + v10] = 2;
  *v13 = nVal;
  *(_DWORD *)&this->m_TaskSlots[80 * v9 + 4 + v10] = nVal2;
  *(_DWORD *)&this->m_TaskSlots[80 * v9 + 8 + v10] = nVal3;
  *(_DWORD *)&this->m_TaskSlots[80 * v9 + 12 + v10] = nVal4;
  v13[5] = (((CCBSystem *)this->m_pCBSystem))->CCBSystem::ProcProtect();
  v13[7] = nVal5;
  v13[6] = 0;
  v13[8] = nVal6;
  if ( p_DWORD )
  {
    v14 = (int *)(v13 + 11);
    *v14 = *p_DWORD;
    v14[1] = (unsigned long)p_DWORD[1];
    v14[2] = (unsigned long)p_DWORD[2];
  }
  ++*(_DWORD *)(&this->m_bPaused + v10);
  return v9;
}

// 0x004FC8B0
void CCBStage::Procced(int nVal)
{
  char *v2; // edx
  int v3; // ecx
  _BYTE *v4; // eax

  v2 = (char *)this + 2632 * nVal;
  v3 = 32;
  v4 = (_BYTE *)v2 + 227;
  do
  {
    if ( *(v4 - 3) )
      *v4 = 1;
    v4 += 80;
    --v3;
  }
  while ( v3 );
  v2[2797] = 1;
}

// 0x004FC8F0
char CCBStage::GetStageRole(int idx)
{
  char *v2; // esi

  v2 = (char *)this + 2632 * idx;
  v2[2796] = 0;
  memset(v2 + 184, 0, 0xA00u);
  *((_DWORD *)v2 + 44) = 0;
  --this->m_nTaskCount;
  return 1;
}

// 0x004FC940
char CCBStage::GetStageRoleByIdx(int idx)
{
  char *v2; // eax

  v2 = (char *)this + 2632 * idx;
  *((_DWORD *)v2 + 43) = 3;
  *((_DWORD *)v2 + 50) = 3;
  *((float *)v2 + 52) = this->m_pCBSystem->m_fTimeFund;
  return 1;
}

// 0x004FC980
bool CCBStage::IsDoTask(int eTask)
{
  return (_BYTE)this + 72 * eTask - 88;
}

// 0x004FC9A0
bool CCBStage::EndTask(int nIndex)
{
  return *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * nIndex + 200];
}

// 0x004FC9C0
char * CCBStage::DelTask(int nIndex, _BYTE *p_BYTE, int *p_DWORD)
{
  char *result; // eax

  *p_BYTE = 0;
  *p_DWORD = 0;
  result = (char *)this + 2632 * nIndex;
  if ( *((_DWORD *)result + 43) == 4 )
  {
    *p_BYTE = 1;
    *p_DWORD = *((_DWORD *)result + 687);
  }
  return result;
}

// 0x004FCA00
bool CCBStage::ForceDelTask(int nIndex)
{
  _BYTE *p_m_nForceDelTask; // eax
  int v3; // edx

  p_m_nForceDelTask = (_BYTE *)&this->m_nForceDelTask;
  v3 = 0;
  while ( !p_m_nForceDelTask[2628] || nIndex != *(_DWORD *)p_m_nForceDelTask || *((_DWORD *)p_m_nForceDelTask + 1) == 4 )
  {
    ++v3;
    p_m_nForceDelTask += 2632;
    if ( v3 >= 256 )
      return 0;
  }
  return 1;
}

// 0x004FCA80
void CCBStage::GetTask()
{
  int v2; // ebx
  _BYTE *p_m_nTaskState; // edi
  int v4; // ebp
  _BYTE *v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  unsigned int ( *v9)(CCBStage *, int); // ecx
  bool *v10; // [esp+0x0] [ebp-0x14]
  unsigned int *v11; // [esp+0x4] [ebp-0x10]
  _BYTE *v12; // [esp+0x10] [ebp-0x4]

  v2 = 0;
  p_m_nTaskState = (_BYTE *)&this->m_nTaskState;
  v12 = (_BYTE *)&this->m_nTaskState;
  do
  {
    if ( *p_m_nTaskState == 1 && *((_DWORD *)p_m_nTaskState - 656) == 3 )
    {
      v4 = 0;
      v5 = (_BYTE *)(p_m_nTaskState - 2676);
      do
      {
        if ( !v5[104] || v4 > 0 && *(_DWORD *)v5 == 2 )
          break;
        if ( *((_DWORD *)v5 + 20) == 2 )
        {
          if ( v4 > 0 )
          {
            if ( *((float *)v5 + 23) >= 0.0 )
            {
              if ( this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 2) > *((float *)v5 + 23) )
              {
LABEL_25:
                this->CCBStage::GetTaskID(v2, v4);
LABEL_26:
                this->m_nClearRoleAllTask = v2;
                this->m_nRoleSlot = v4;
                (*((void ( **)(char *, _DWORD))v5 + 16))((char *)this + *((_DWORD *)v5 + 17), 0);
              }
            }
            else if ( *(_DWORD *)v5 == 4 )
            {
              goto LABEL_25;
            }
          }
        }
        else
        {
          if ( *((_DWORD *)v5 + 20) == 3 )
            goto LABEL_26;
          if ( *((_DWORD *)v5 + 20) == 4 && (((CCBStage *)v2))->CCBStage::GetTaskState(v10, v11) == 1 )
          {
            v6 = *((_DWORD *)v12 - 655);
            *((_DWORD *)v12 - 656) = 4;
            v6 *= 80;
            v7 = *(_DWORD *)&v12[v6 - 2656];
            v8 = (int)&v12[v6 - 2628];
            *((_DWORD *)v12 - 12) = v7;
            v9 = *(unsigned int ( **)(CCBStage *, int))(v8 - 64);
            if ( v9 == CCBStage::ProcFiveLienupFadeOut
              && (!v9 || !*(_DWORD *)(v8 - 60) && !*(_DWORD *)(v8 - 56) && !*(_DWORD *)(v8 - 52)) )
            {
              *((_DWORD *)v12 - 12) = *(_DWORD *)(v8 - 108);
            }
            if ( v12[1] == 1 )
            {
              this->CCBStage::GetStageRole(v2);
              break;
            }
          }
        }
        ++v4;
        v5 += 80;
      }
      while ( v4 < 32 );
    }
    ++v2;
    p_m_nTaskState = (_BYTE *)(v12 + 2632);
    v12 += 2632;
  }
  while ( v2 < 256 );
}

// 0x004FCBD0
char CCBStage::GetTaskID(int nIndex, int nVal)
{
  char *v3; // eax

  v3 = (char *)this + 2632 * nIndex + 80 * nVal;
  *((_DWORD *)v3 + 50) = 3;
  *((float *)v3 + 52) = this->m_pCBSystem->m_fTimeFund;
  return 1;
}

// 0x004FCC10
char CCBStage::GetTaskState(int nIndex, bool *bFinished, unsigned int *dwReturn)
{
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // eax
  _DWORD *i; // ecx

  v4 = 0;
  v5 = v3 + 2632 * nIndex;
  v6 = *(_DWORD *)(v5 + 176);
  if ( v6 <= 0 )
    return 1;
  for ( i = (_DWORD *)(v5 + 200); *i == 4; i += 20 )
  {
    if ( ++v4 >= v6 )
      return 1;
  }
  return 0;
}

// 0x004FCC50
char CCBStage::GetTaskState(int nIndex, ECBStageTaskState *State)
{
  int v2; // ecx
  int v3; // ebx
  _BYTE *i; // edx
  int v5; // eax
  int v6; // esi
  _BYTE *v7; // eax
  int v8; // ecx

  v3 = 0;
  for ( i = (_BYTE *)(v2 + 2796); ; i += 2632 )
  {
    if ( *i )
    {
      if ( *((_DWORD *)i - 656) != 4 && *((_DWORD *)i - 657) == 11 )
      {
        v5 = *((_DWORD *)i - 9);
        if ( v5 >= 5 && v5 < 11 )
          break;
      }
    }
LABEL_18:
    if ( ++v3 >= 256 )
      return 0;
  }
  v6 = 0;
  v7 = (_BYTE *)(i - 2612);
  while ( 1 )
  {
    if ( *(void ( **)(CCBStage *, int))v7 == CCBStage::HandleKeyCtrl
      && (!*(_DWORD *)v7 || !*((_DWORD *)v7 + 1) && !*((_DWORD *)v7 + 2) && !*((_DWORD *)v7 + 3)) )
    {
      if ( *((_DWORD *)v7 + 4) == 4 )
        goto LABEL_18;
      v8 = *((_DWORD *)i - 8);
      if ( v8 == nIndex || v8 == -1 && i[nIndex - 15] )
        return 1;
    }
    ++v6;
    v7 += 80;
    if ( v6 >= 32 )
      goto LABEL_18;
  }
}

// 0x004FCD00
bool CCBStage::IsTaskFinished(int nIndex)
{
  int *p_m_nTaskExist; // edx
  int v4; // ebx
  bool result; // al

  (((CCBStage *)this->m_pRole[nIndex]))->CCBStage::GetCurrentState();
  p_m_nTaskExist = (int *)&this->m_nTaskExist;
  v4 = 256;
  do
  {
    result = *((_BYTE *)p_m_nTaskExist + 36);
    if ( result && *p_m_nTaskExist == nIndex )
    {
      result = 0;
      memset(p_m_nTaskExist - 648, 0, 0xA48u);
      --this->m_nTaskCount;
    }
    p_m_nTaskExist += 658;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCD50
unsigned __int8 * CCBStage::IsTaskValidButNotFinish(unsigned __int8 *result, int eTask, int nVal)
{
  unsigned __int8 *v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // esi
  int v7; // ecx

  v5 = v4 + 2760;
  v6 = 256;
  do
  {
    LOBYTE(v3) = *(_BYTE *)(v5 + 36);
    if ( (_BYTE)v3 && *(unsigned __int8 **)v5 == result )
    {
      v3 = (unsigned __int8 *)(v5 - 2533);
      v7 = 32;
      do
      {
        if ( *(v3 - 3) )
          *v3 = 1;
        v3 += 80;
        --v7;
      }
      while ( v7 );
    }
    v5 += 2632;
    --v6;
  }
  while ( v6 );
  return v3;
}

// 0x004FCDA0
bool CCBStage::IsTaskExist(unsigned int dwTaskID)
{
  bool result; // al
  int *p_m_nTaskExist; // ecx
  int v4; // edx

  result = 0;
  p_m_nTaskExist = (int *)&this->m_nTaskExist;
  v4 = 256;
  do
  {
    if ( *((_BYTE *)p_m_nTaskExist + 36) && *p_m_nTaskExist == dwTaskID && *(p_m_nTaskExist - 648) != 29 )
      ++result;
    p_m_nTaskExist += 658;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCDE0
void CCBStage::DoTask(int nVal)
{
  if ( nVal == -1 )
    this->m_pShadow = ((CCBStageShadow *)((CCBStageShadow *)-1));
  else
    this->m_pShadow = ((CCBStageShadow *)((CCBStageShadow *)nVal));
}

// 0x004FCE00
bool CCBStage::StartSubTask(int n)
{
  int v2; // eax
  _BYTE *v3; // esi
  char v5; // al

  v2 = 80 * this->m_nRoleSlot;
  v3 = (_BYTE *)&this->m_TaskSlots[2632 * this->m_nClearRoleAllTask + v2];
  if ( this->m_TaskSlots[2632 * this->m_nClearRoleAllTask + 41 + v2] )
  {
    if ( this->m_TaskSlots[2632 * this->m_nClearRoleAllTask + 43 + v2] == 1
      || this->m_pCBSystem->m_fTimeFund - *((float *)v3 + 6) >= *((float *)v3 + 8)
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v5) )
    {
      *((_DWORD *)v3 + 4) = 4;
    }
    return 0;
  }
  else
  {
    this->m_TaskSlots[2632 * this->m_nClearRoleAllTask + 41 + v2] = 1;
    return 0;
  }
}

// 0x004FCE70
bool CCBStage::IsSubTaskFinished(int n, int nSub)
{
  _DWORD *v2; // ecx
  _DWORD *v3; // edi
  int v4; // ecx
  _DWORD *v5; // eax
  float v6; // st7
  int v7; // esi
  float v8; // st7
  unsigned int v9; // eax
  unsigned int v10; // ecx
  float v12; // [esp+0x1C] [ebp-0x8]
  float v13; // [esp+0x1C] [ebp-0x8]
  float v14; // [esp+0x20] [ebp-0x4]
  float v15; // [esp+0x20] [ebp-0x4]

  v3 = (_DWORD *)v2;
  v4 = 329 * v2[40];
  v5 = (_DWORD *)&v3[20 * v3[41]];
  v6 = *(float *)&v5[2 * v4 + 54] * 0.25f;
  v7 = (int)&v5[2 * v4 + 46];
  v12 = v6;
  v14 = v6 * 3.0f;
  if ( !BYTE1(v5[2 * v4 + 56]) )
  {
    v5[2 * v4 + 62] = 0;
    BYTE1(v5[2 * v4 + 56]) = 1;
  }
  ::EndTurnAndAdvance(
    v3[17],
    *(_DWORD *)(v3[5] + 900),
    *(_DWORD *)(v3[5] + 904),
    *(_DWORD *)(v3[5] + 908),
    COERCE_INT(*(float *)(v3[5] + 916)));
  v8 = *(float *)(*v3 + 80) - *(float *)(v7 + 24);
  if ( v8 >= v14 )
  {
    v13 = (1.0f - (v8 - v14) / v12) * 255.0f;
    v10 = (int)v13;
    *(_DWORD *)(v7 + 64) = v10;
    v9 = v10 <= 0xFF ? v10 : 0;
  }
  else
  {
    v15 = v8 / v14 * 255.0f;
    v9 = (int)v15;
    *(_DWORD *)(v7 + 64) = v9;
    if ( v9 > 0xFF )
      v9 = 255;
  }
  *(_DWORD *)(v7 + 64) = v9;
  if ( *(_BYTE *)(v7 + 43) == 1 || *(float *)(*v3 + 80) - *(float *)(v7 + 24) >= *(float *)(v7 + 32) )
    *(_DWORD *)(v7 + 16) = 4;
  return 0;
}

// 0x004FCFB0
bool CCBStage::IsAllSubTaskFinished(int n)
{
  int v3; // ecx
  int v4; // edx
  float v5; // st7
  float *v6; // esi
  float v7; // st7
  unsigned int v8; // eax
  unsigned int v9; // ecx
  float v11; // [esp+0x8] [ebp-0x8]
  float v12; // [esp+0x8] [ebp-0x8]
  float v13; // [esp+0xC] [ebp-0x4]
  float v14; // [esp+0xC] [ebp-0x4]

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = *(float *)&this->m_TaskSlots[8 * v3 + 32 + v4] * 0.25f;
  v6 = (float *)&this->m_TaskSlots[8 * v3 + v4];
  v11 = v5;
  v13 = v5 * 3.0f;
  if ( !this->m_TaskSlots[8 * v3 + 41 + v4] )
  {
    *(_DWORD *)&this->m_TaskSlots[8 * v3 + 64 + v4] = 0;
    this->m_TaskSlots[8 * v3 + 41 + v4] = 1;
  }
  (((CCBStage *)this->m_TempStorageNGH))->CCBStage::AssignSlotData(this->m_TaskSlots[8 * v3 + 64 + v4]);
  v7 = this->m_pCBSystem->m_fTimeFund - v6[6];
  if ( v7 >= v13 )
  {
    v12 = (1.0f - (v7 - v13) / v11) * 255.0f;
    v9 = (int)v12;
    *((_DWORD *)v6 + 16) = v9;
    v8 = v9 <= 0xFF ? v9 : 0;
  }
  else
  {
    v14 = v7 / v13 * 255.0f;
    v8 = (int)v14;
    *((_DWORD *)v6 + 16) = v8;
    if ( v8 > 0xFF )
      v8 = 255;
  }
  *((_DWORD *)v6 + 16) = v8;
  if ( *((_BYTE *)v6 + 43) == 1 || this->m_pCBSystem->m_fTimeFund - v6[6] >= v6[8] )
    *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FD0B0
bool CCBStage::IsTaskValid(int n)
{
  int v3; // ecx
  int v4; // edx
  float *v5; // esi
  float v6; // st7
  unsigned int v7; // eax
  float v9; // [esp+0x20] [ebp-0x4]
  float v10; // [esp+0x20] [ebp-0x4]

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = (float *)&this->m_TaskSlots[8 * v3 + v4];
  v9 = *(float *)&this->m_TaskSlots[8 * v3 + 32 + v4];
  if ( !this->m_TaskSlots[8 * v3 + 41 + v4] )
  {
    *(_DWORD *)&this->m_TaskSlots[8 * v3 + 64 + v4] = 0;
    this->m_TaskSlots[8 * v3 + 41 + v4] = 1;
  }
  ::EndTurnAndAdvance(
    (int)this->m_TempStorageNGH,
    LODWORD(this->m_pScene->m_fInitAxisX),
    LODWORD(this->m_pScene->m_fInitAxisY),
    LODWORD(this->m_pScene->m_fInitAxisZ),
    COERCE_INT(this->m_pScene->m_fInitRotParam));
  v6 = this->m_pCBSystem->m_fTimeFund - v5[6];
  if ( v6 >= v9 )
  {
    *((_DWORD *)v5 + 16) = 255;
    *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    v10 = v6 / v9 * 255.0f;
    v7 = (int)v10;
    *((_DWORD *)v5 + 16) = v7;
    if ( v7 > 0xFF )
      v7 = 255;
    *((_DWORD *)v5 + 16) = v7;
  }
  if ( *((_BYTE *)v5 + 43) == 1 )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FD1A0
bool CCBStage::IsSubTaskValid(int n, int nSub)
{
  _DWORD *v2; // ecx
  _DWORD *v3; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // esi
  float v7; // st7
  unsigned int v8; // ecx
  float v10; // [esp+0x20] [ebp-0x4]
  float v11; // [esp+0x20] [ebp-0x4]

  v3 = (_DWORD *)v2;
  v4 = 329 * v2[40];
  v5 = 20 * v3[41];
  v6 = (int)&v3[2 * v4 + 46 + v5];
  v10 = *(float *)&v3[2 * v4 + 54 + v5];
  if ( !BYTE1(v3[2 * v4 + 56 + v5]) )
  {
    v3[2 * v4 + 62 + v5] = 255;
    BYTE1(v3[2 * v4 + 56 + v5]) = 1;
  }
  ::EndTurnAndAdvance(
    v3[17],
    *(_DWORD *)(v3[5] + 900),
    *(_DWORD *)(v3[5] + 904),
    *(_DWORD *)(v3[5] + 908),
    COERCE_INT(*(float *)(v3[5] + 916)));
  v7 = *(float *)(*v3 + 80) - *(float *)(v6 + 24);
  if ( v7 >= v10 )
  {
    *(_DWORD *)(v6 + 64) = 0;
    *(_DWORD *)(v6 + 16) = 4;
  }
  else
  {
    v11 = (1.0f - v7 / v10) * 255.0f;
    v8 = (int)v11;
    *(_DWORD *)(v6 + 64) = v8;
    *(_DWORD *)(v6 + 64) = v8 <= 0xFF ? v8 : 0;
  }
  if ( *(_BYTE *)(v6 + 43) == 1 )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FD290
bool CCBStage::IsIdle(int nVal)
{
  CEffectSystem *v3; // ecx
  char *v4; // eax
  int v5; // edi
  CCBUI *m_pUI; // ebp
  UIProgressBar *v8; // ecx
  CCBUI *v9; // ecx

  v3 = (CEffectSystem *)(329 * this->m_nClearRoleAllTask);
  v4 = (char *)this + 80 * this->m_nRoleSlot;
  v5 = (int)&v4[8 * (_DWORD)v3 + 184];
  if ( !v4[8 * (_DWORD)v3 + 225] )
  {
    if ( *((_BYTE *)(((CEffectSystem *)v3))->CEffectSystem::DestroyAllEffect() + 5) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    m_pUI = (CCBUI *)this->m_pCBSystem->m_pUI;
    if ( this->m_pRoleState->m_pObjMsgBuffer[112] )
    {
      (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aWesneakattacke);
      SetEnable((UICaption *)m_pUI->m_pRoleStateGP[2]);
      v8 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    }
    else
    {
      (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aEnemysneakatta);
      SetEnable((UICaption *)m_pUI->m_pRoleStateGP[3]);
      v8 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    }
    (**(void ( ***)(UIProgressBar *, int))((UIWnd *)v8))((UIProgressBar *)(v8), (int)(1));
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || this->m_pCBSystem->m_fTimeFund - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || *((_BYTE *)(((CEffectSystem *)this->m_pCBSystem))->CEffectSystem::DestroyAllEffect() + 5) )
  {
    v9 = (CCBUI *)this->m_pCBSystem->m_pUI;
    if ( this->m_pRoleState->m_pObjMsgBuffer[112] )
    {
      (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v9->m_pRoleStateGP[2]))((UIProgressBar *)(v9->m_pRoleStateGP[2]), (_DWORD)(0));
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v9->m_pRoleStateGP[3]))((UIProgressBar *)(v9->m_pRoleStateGP[3]), (_DWORD)(0));
    *(_DWORD *)(v5 + 16) = 4;
  }
  return 0;
}

// 0x004FD3D0
bool CCBStage::HasNormalAttackRole(int nRoleIndex)
{
  int v3; // ebp
  int v4; // ecx
  _BYTE *v5; // ebx
  int v6; // eax
  int v8; // edi
  char v9; // al
  signed int i; // edi
  char v11; // al
  int v12; // edi
  int v13; // ebx
  CCBRoleState *m_pRoleState; // ecx
  int j; // edi
  int v16; // ecx
  int v17; // edx
  CCBStageRole **v18; // eax
  int v19; // eax
  char *v20; // eax
  char v21; // dl
  int k; // eax
  int v23; // ebp
  int v24; // eax
  CCBStageRole **v25; // ecx
  int v26; // eax
  CCBStageRole **v27; // ecx
  int *v28; // [esp+0x10] [ebp-0x10]
  CCBStage **m_pRole; // [esp+0x14] [ebp-0xC]
  CCBStage **v30; // [esp+0x14] [ebp-0xC]
  _BYTE *v31; // [esp+0x18] [ebp-0x8]
  int v32; // [esp+0x18] [ebp-0x8]
  int roleIdx; // [esp+0x1C] [ebp-0x4]

  if ( (byte_17AAA2C & 1) == 0 )
  {
    dword_17AAA20 = 0;
    LOBYTE(byte_17AAA2C) = byte_17AAA2C | 1;
    dword_17AAA24 = 0;
    dword_17AAA28 = 0;
    atexit(nullsub_20);
  }
  v3 = 2632 * this->m_nClearRoleAllTask;
  roleIdx = *(int *)((char *)&this->m_nTaskExist + v3);
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[v4];
  v31 = (_BYTE *)v5;
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    this->m_pEffect = ((CCBStageEffect *)0);
    this->m_BFARole = 0;
    LOWORD(this->m_BFARound) = 0;
    BYTE2(this->m_BFARound) = 0;
    v6 = this->CCBStage::CalcSneakAttackVariance();
    LODWORD(fBladeTime) = v6;
    if ( v6 == -1 )
    {
      v5[41] = 1;
      *((_DWORD *)v5 + 9) = -1;
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
    (((CCBRoleState *)this))->CCBRoleState::GetRoleMPValue(v6, *((_DWORD *)v5 + 11), *(int *)((char *)&this->m_TaskState + v3));
    v5[41] = 1;
  }
  if ( (v5[44] & 1) != 0 )
  {
    v8 = 0;
    v28 = (int *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
    m_pRole = (CCBStage **)this->m_pRole;
    do
    {
      (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CancelVariance(v28, v8);
      if ( v9 && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(v8) && (((CCBStage *)*m_pRole))->CCBStage::CheckViewTarget() )
      {
        LODWORD(fBladeTime) = v8;
        (((CCBRoleState *)this))->CCBRoleState::GetRoleMPValue(v8, *((_DWORD *)v5 + 11), *(int *)((char *)&this->m_TaskState + v3));
      }
      ++v8;
      ++m_pRole;
    }
    while ( v8 < 11 );
    (((CCBRoleState *)this))->CCBRoleState::GetRoleMPValue(SLODWORD(fBladeTime), *((_DWORD *)v5 + 11), *(int *)((char *)&this->m_TaskState + v3));
    for ( i = 0; i < 11; ++i )
    {
      if ( *((_BYTE *)&this->m_pEffect + i) )
      {
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CancelVariance(v28, i);
        if ( !v11 )
          *((_BYTE *)&this->m_pEffect + i) = 0;
      }
    }
    if ( LODWORD(fBladeTime) <= 0xA && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleAttr(roleIdx) < 4 )
      (((CCBStage *)this->m_pRole[roleIdx]))->CCBStage::SetBladeTime(SLODWORD(fBladeTime));
  }
  else
  {
    v12 = 0;
    v13 = 0;
    v30 = (CCBStage **)this->m_pRole;
    do
    {
      m_pRoleState = (CCBRoleState *)this->m_pRoleState;
      if ( m_pRoleState->m_pObjMsgBuffer[v13 + 153]
        && (((CCBRoleState *)m_pRoleState))->CCBRoleState::IsActive(v12) == 1
        && (((CCBStage *)*v30))->CCBStage::CheckViewTarget() )
      {
        LODWORD(fBladeTime) = v12;
        (((CCBRoleState *)this))->CCBRoleState::GetRoleMPValue(v12, *((_DWORD *)v31 + 11), *(int *)((char *)&this->m_TaskState + v3));
      }
      v13 += 892;
      ++v12;
      ++v30;
    }
    while ( v13 < 9812 );
    v28 = (int *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
    if ( !(((CCBStage *)this->m_pRoleState))->CCBStage::CheckGDBTypeCompat((unsigned int *)v28) )
    {
      for ( j = 0; j < 11; ++j )
      {
        if ( *((_BYTE *)&this->m_pEffect + j) && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(j) )
          *((_BYTE *)&this->m_pEffect + j) = 0;
      }
    }
    v5 = (_BYTE *)v31;
  }
  v16 = 0;
  v17 = 0;
  v32 = 0;
  v18 = (CCBStageRole **)this->m_pRole;
  do
  {
    if ( this->m_pRoleState->m_pObjMsgBuffer[v16 + 153] )
    {
      if ( *((_BYTE *)&this->m_pEffect + v17) )
      {
        ++v32;
        (*v18)->m_bShowWeapon = 1;
        (*v18)->m_bFlash = 1;
      }
      else
      {
        (*v18)->m_bShowWeapon = 0;
        (*v18)->m_bFlash = 0;
      }
    }
    v16 += 892;
    ++v17;
    ++v18;
  }
  while ( v16 < 9812 );
  if ( v32 <= 0 )
    v5[41] = 0;
  if ( g_Input.KeyInfo[0].PressTime == 1 && ((v19 = g_Input.KeyInfo[0].Data & 0xF, v19 == 1) || v19 == 2) )
  {
    if ( (v5[44] & 0x10) != 0 )
    {
      *((_BYTE *)&this->m_DamageData + v3 + 5) = 0;
      *((_BYTE *)&this->m_DamageData + v3 + 4) = 0;
      *(float *)((char *)&this->m_DamageData + v3) = fBladeTime;
      if ( LODWORD(fBladeTime) == -1 )
        return 0;
    }
    else
    {
      *((_BYTE *)&this->m_DamageData + v3 + 4) = 0;
      *((_BYTE *)&this->m_DamageData + v3 + 5) = 1;
      v20 = (char *)&this->m_DamageData + v3 + 17;
      *(_DWORD *)v20 = (_DWORD)this->m_pEffect;
      *((_DWORD *)v20 + 1) = this->m_BFARole;
      *((_WORD *)v20 + 4) = this->m_BFARound;
      v20[10] = BYTE2(this->m_BFARound);
      v21 = 0;
      for ( k = 0; k < 11; ++k )
      {
        if ( *((_BYTE *)&this->m_pEffect + k) )
          v21 = 1;
      }
      if ( !v21 )
        return 0;
    }
    v23 = roleIdx;
    *((float *)v5 + 9) = fBladeTime;
    *((_DWORD *)v5 + 4) = 4;
    v24 = 0;
    this->m_pRole[roleIdx]->m_bFlash = 0;
    v25 = (CCBStageRole **)this->m_pRole;
    do
    {
      if ( this->m_pRoleState->m_pObjMsgBuffer[v24 + 153] )
      {
        (*v25)->m_bShowWeapon = 0;
        (*v25)->m_bFlash = 0;
      }
      v24 += 892;
      ++v25;
    }
    while ( v24 < 9812 );
  }
  else
  {
    v23 = roleIdx;
  }
  if ( v5[43] == 1
    || g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1
    || g_Input.KeyInfo[17].PressTime == 1
    || *v28 == 262 && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v23, 16)
    || *v28 == 261 && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v23, 15) )
  {
    *((_DWORD *)v5 + 9) = -1;
    *((_DWORD *)v5 + 4) = 4;
    v26 = 0;
    v27 = (CCBStageRole **)this->m_pRole;
    do
    {
      if ( this->m_pRoleState->m_pObjMsgBuffer[v26 + 153] )
      {
        (*v27)->m_bShowWeapon = 0;
        (*v27)->m_bFlash = 0;
      }
      v26 += 892;
      ++v27;
    }
    while ( v26 < 9812 );
  }
  return 0;
}

// 0x004FD880
void CCBStage::ClearRoleAllTask(int nRoleIndex)
{
  int m_nClearRoleAllTask; // eax
  CEffectSystem *v4; // ecx
  int v5; // edi
  int v6; // eax
  _BYTE *v7; // ebp
  UIProgressBar *v8; // ecx
  UIProgressBar *v9; // ecx
  UIProgressBar *v10; // ecx
  int v11; // [esp-0x4] [ebp-0x10]

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = (CEffectSystem *)(5 * m_nClearRoleAllTask);
  v5 = 2632 * m_nClearRoleAllTask;
  v6 = 2632 * m_nClearRoleAllTask + 80 * this->m_nRoleSlot;
  v7 = (_BYTE *)&this->m_TaskSlots[v6];
  if ( !this->m_TaskSlots[v6 + 41] )
  {
    if ( *((_BYTE *)(((CEffectSystem *)v4))->CEffectSystem::DestroyAllEffect() + 5) )
    {
      v7[41] = 1;
      *((_DWORD *)v7 + 4) = 4;
      return;
    }
    if ( *(int *)((char *)&this->m_TaskState + v5) )
    {
      v11 = *(int *)((char *)&this->m_TaskState + v5);
      if ( *(_DWORD *)&this->m_TaskArrC[8]._todo_018[v5 + 208] == 270 )
      {
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(v11);
        if ( *(int *)((char *)&this->m_nTaskExist + v5) > 4u )
          v8 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
        else
          v8 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
      }
      else
      {
        (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v11);
        if ( *(int *)((char *)&this->m_nTaskExist + v5) > 4u )
          v8 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
        else
          v8 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
      }
      SetEnable((UICaption *)v8);
    }
    if ( *(int *)((char *)&this->m_nTaskExist + v5) > 4u )
      v9 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    else
      v9 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    (**(void ( ***)(UIProgressBar *, int))((UIWnd *)v9))((UIProgressBar *)(v9), (int)(1));
    v7[41] = 1;
  }
  if ( v7[43] == 1
    || this->m_pCBSystem->m_fTimeFund - *((float *)v7 + 6) > *((float *)v7 + 8)
    || *((_BYTE *)(((CEffectSystem *)v4))->CEffectSystem::DestroyAllEffect() + 5) )
  {
    if ( *(int *)((char *)&this->m_nTaskExist + v5) > 4u )
      v10 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    else
      v10 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v10))((UIProgressBar *)(v10), (_DWORD)(0));
    *((_DWORD *)v7 + 4) = 4;
  }
}

// 0x004FDA10
void CCBStage::EndRoleAllTask(int nRoleIndex)
{
  int v3; // edi
  int v4; // eax
  _BYTE *v5; // ebp
  UIProgressBar *v6; // ecx
  UIProgressBar *v7; // ecx

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(_DWORD *)&this->m_TaskSlots[v4 + 44]);
    if ( *(int *)((char *)&this->m_nTaskExist + v3) > 4u )
    {
      SetEnable((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3]);
      v6 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    }
    else
    {
      SetEnable((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2]);
      v6 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    }
    (**(void ( ***)(UIProgressBar *, int))((UIWnd *)v6))((UIProgressBar *)(v6), (int)(1));
    v5[41] = 1;
  }
  if ( v5[43] == 1 || this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) > *((float *)v5 + 8) )
  {
    if ( *(int *)((char *)&this->m_nTaskExist + v3) > 4u )
      v7 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    else
      v7 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v7))((UIProgressBar *)(v7), (_DWORD)(0));
    *((_DWORD *)v5 + 4) = 4;
  }
}

// 0x004FDB10
int CCBStage::GetRoleTaskNum(int nRoleIndex)
{
  int v3; // eax
  int v4; // ecx
  _BYTE *v5; // esi
  _DWORD *v6; // ecx
  CCBStageCam *m_pCam; // ecx
  float v8; // st7
  float height; // st7
  float width; // st7
  int v11; // eax
  char v12; // dl
  struct gbVec3D v14; // [esp+0x8] [ebp-0x20] BYREF
  int v15; // [esp+0x14] [ebp-0x14]
  int v16; // [esp+0x18] [ebp-0x10]
  int nVal4; // [esp+0x1C] [ebp-0xC]
  int nVal2; // [esp+0x20] [ebp-0x8] BYREF
  float fVal3; // [esp+0x24] [ebp-0x4] BYREF

  *(float *)&nVal2 = 0.0;
  fVal3 = 0.0f;
  memset(&v14, 0, sizeof(v14));
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    v6 = (_DWORD *)(int *)((char *)&this->m_nTaskExist + v3);
    *((float *)&this->m_ptMousePos.x + *v6) = *((float *)&this->m_ptMousePos.x + *v6) + 10.0;
    v14 = *(gbVec3D *)&this->m_pRole[*v6]->m_Task[62].fTemp;
    *((_DWORD *)v5 + 16) = LODWORD(v14.x);
    *((_DWORD *)v5 + 17) = LODWORD(v14.z);
    v16 = *(&this->m_ptMousePos.x + *v6);
    nVal4 = (int)*(float *)&v16;
    *((float *)v5 + 18) = *(float *)&nVal4;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    *((_DWORD *)v5 + 19) = ((int)g_nCombatRandSeed >> 16) & 0x1F;
    v5[41] = 1;
  }
  v14.x = *((float *)v5 + 16);
  v14.z = *((float *)v5 + 17);
  m_pCam = (CCBStageCam *)this->m_pCam;
  v14.y = 50.0;
  (((gbCamera *)&m_pCam->OrthoSize))->gbCamera::PointWorldToScr(&v14, (float *)&nVal2, &fVal3);
  sprintf(byte_17AA920, (const char *)&dir[20], *((_DWORD *)v5 + 11));
  v8 = (this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6)) / *((float *)v5 + 8);
  if ( v8 > 1.0f )
    v8 = 1.0f;
  *(float *)&nVal4 = (1.0 - v8) * 255.0;
  v16 = (int)*(float *)&nVal4;
  *(float *)&nVal4 = (this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6)) * 30.0;
  v15 = (int)*(float *)&nVal4;
  height = (float)g_DrvInfo.height;
  v15 = *((_DWORD *)v5 + 18) - (__int64)((1.0 - fVal3) * height * -0.5) - v15;
  fVal3 = 1.0f - ((float)v15 + (float)v15) / height;
  width = (float)g_DrvInfo.width;
  v15 = *((_DWORD *)v5 + 19) - (__int64)((*(float *)&nVal2 + 1.0) * width * -0.5) - 16;
  *(float *)&nVal2 = ((double)v15 + (double)v15) / width - 1.0;
  v11 = *((_DWORD *)v5 + 13);
  if ( v11 )
  {
    v12 = v5[52];
    BYTE1(nVal4) = BYTE1(*((_DWORD *)v5 + 13));
    BYTE2(nVal4) = BYTE2(v11);
    LOBYTE(nVal4) = v12;
  }
  else
  {
    *(_WORD *)((char *)&nVal4 + 1) = 12850;
    LOBYTE(nVal4) = -1;
  }
  HIBYTE(nVal4) = v16;
  ::InitRound((CCBStage *)this->m_TempStorageNGH, COERCE_FLOAT(byte_17AA920), nVal2, fVal3, nVal4);
  if ( this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) > *((float *)v5 + 8) )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FDD90
void CCBStage::SelectRole(int nRoleIndex)
{
  int v3; // eax
  int v4; // ecx
  float *v5; // esi
  float v6; // st7
  float height; // st7
  float width; // st7
  float v9; // edx
  struct gbVec3D v10; // [esp+0x8] [ebp-0x20] BYREF
  int v11; // [esp+0x14] [ebp-0x14]
  int v12; // [esp+0x18] [ebp-0x10]
  int nVal4; // [esp+0x1C] [ebp-0xC]
  int nVal2; // [esp+0x20] [ebp-0x8] BYREF
  float fVal3; // [esp+0x24] [ebp-0x4] BYREF

  *(float *)&nVal2 = 0.0;
  fVal3 = 0.0f;
  memset(&v10, 0, sizeof(v10));
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (float *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    v10 = *(gbVec3D *)&this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)]->m_Task[62].eMode;
    v10.y = v10.y + 80.0;
    *(gbVec3D *)&this->m_TaskSlots[v4 + 64] = v10;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    *(_DWORD *)&this->m_TaskSlots[v4 + 76] = ((int)g_nCombatRandSeed >> 16) & 0x1F;
    this->m_TaskSlots[v4 + 41] = 1;
  }
  v10 = *(gbVec3D *)&this->m_TaskSlots[v4 + 64];
  (((gbCamera *)&this->m_pCam->OrthoSize))->gbCamera::PointWorldToScr(&v10, (float *)&nVal2, &fVal3);
  v6 = (this->m_pCBSystem->m_fTimeFund - v5[6]) / v5[8];
  *(float *)&nVal4 = v6;
  if ( v6 > 1.0f )
    *(float *)&nVal4 = 1.0;
  *(float *)&v12 = (1.0 - *(float *)&nVal4) * 255.0;
  v11 = (int)*(float *)&v12;
  *(float *)&v12 = *(float *)&nVal4 * 32.0;
  nVal4 = (int)*(float *)&v12;
  height = (float)g_DrvInfo.height;
  v12 = 16 - (__int64)((1.0 - fVal3) * height * -0.5) - nVal4;
  fVal3 = 1.0f - ((float)v12 + (float)v12) / height;
  width = (float)g_DrvInfo.width;
  LODWORD(v9) = *((_DWORD *)v5 + 19) - (__int64)((*(float *)&nVal2 + 1.0) * width * -0.5) - 16;
  *(_WORD *)((char *)&nVal4 + 1) = 13055;
  *(float *)&v12 = v9;
  LOBYTE(nVal4) = -1;
  HIBYTE(nVal4) = v11;
  *(float *)&nVal2 = ((double)v12 + (double)v12) / width - 1.0;
  ::InitRound((CCBStage *)this->m_TempStorageNGH, _pal3_coerce_f32(6141552), nVal2, fVal3, nVal4);
  if ( this->m_pCBSystem->m_fTimeFund - v5[6] > v5[8] )
    *((_DWORD *)v5 + 4) = 4;
}

// 0x004FDFC0
unsigned int CCBStage::ProcWait(int formal)
{
  CCBStage *v2; // esi
  int m_nClearRoleAllTask; // eax
  int v4; // ecx
  char *v5; // eax
  int v6; // ebx
  int v7; // eax
  gbCamera *p_OrthoSize; // ecx
  float v9; // st7
  float height; // st7
  float width; // st7
  int v12; // edx
  char *v14; // [esp-0x8] [ebp-B8h]
  char *v15; // [esp-0x4] [ebp-B4h]
  int v16; // [esp-0x4] [ebp-B4h]
  char Buffer[128]; // [esp+0xC] [ebp-A4h] BYREF
  int v18; // [esp+0x8C] [ebp-0x24]
  CCBStage *v19; // [esp+0x90] [ebp-0x20]
  struct gbVec3D v20; // [esp+0x94] [ebp-0x1C] BYREF
  int nVal4; // [esp+A0h] [ebp-0x10]
  float v22; // [esp+A4h] [ebp-0xC]
  int nVal2; // [esp+A8h] [ebp-0x8] BYREF
  float fVal3; // [esp+ACh] [ebp-0x4] BYREF
*(float *)&nVal2 = 0.0;
  fVal3 = 0.0f;
  memset(&v20, 0, sizeof(v20));
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
v4 = 329 * m_nClearRoleAllTask;
  v5 = (char *)this + 80 * this->m_nRoleSlot;
  v6 = (int)&v5[8 * v4 + 184];
  if ( !v5[8 * v4 + 225] )
  {
    *((float *)&this->m_ptMousePos.x + *(_DWORD *)&v5[8 * v4 + 232]) = *((float *)&this->m_ptMousePos.x
                                                                     + *(_DWORD *)&v5[8 * v4 + 232])
                                                                   + 10.0;
    v20 = *(gbVec3D *)&this->m_pRole[*(_DWORD *)&v5[8 * v4 + 232]]->m_Task[62].eMode;
    v7 = *(_DWORD *)&v5[8 * v4 + 232];
    *(float *)(v6 + 64) = v20.x;
    *(float *)(v6 + 68) = v20.z;
    nVal4 = *(&this->m_ptMousePos.x + v7);
    LODWORD(v22) = (int)*(float *)&nVal4;
    *(float *)(v6 + 72) = v22;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    *(_DWORD *)(v6 + 76) = ((int)g_nCombatRandSeed >> 16) & 0x1F;
    *(_BYTE *)(v6 + 41) = 1;
  }
  v20.x = *(float *)(v6 + 64);
  v20.z = *(float *)(v6 + 68);
  p_OrthoSize = (CCBStageCam *)&this->m_pCam->OrthoSize;
  v20.y = 50.0;
  (((gbCamera *)p_OrthoSize))->gbCamera::PointWorldToScr(&v20, (float *)&nVal2, &fVal3);
  v9 = (this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24)) / *(float *)(v6 + 32);
  if ( v9 > 1.0f )
    v9 = 1.0f;
  v22 = (1.0f - v9) * 255.0f;
  v18 = (int)v22;
  v22 = (this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24)) * 30.0f;
  nVal4 = (int)v22;
  height = (float)g_DrvInfo.height;
  LODWORD(v22) = *(_DWORD *)(v6 + 72) - (__int64)((1.0 - fVal3) * height * -0.5) - nVal4;
  fVal3 = 1.0f - ((float)SLODWORD(v22) + (float)SLODWORD(v22)) / height;
  width = (float)g_DrvInfo.width;
  v12 = *(_DWORD *)(v6 + 76) - (__int64)((*(float *)&nVal2 + 1.0) * width * -0.5);
  *(_WORD *)((char *)&nVal4 + 1) = 13055;
  LODWORD(v22) = v12 - 32;
  LOBYTE(nVal4) = -1;
  HIBYTE(nVal4) = v18;
  *(float *)&nVal2 = ((double)SLODWORD(v22) + (double)SLODWORD(v22)) / width - 1.0;
  if ( *(_DWORD *)(v6 + 44) == 1 )
  {
    v16 = *(_DWORD *)(v6 + 52);
    v14 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aWitch);
    sprintf(Buffer, "%s -%d", v14, v16);
  }
  else if ( *(_DWORD *)(v6 + 44) == 2 )
  {
    v15 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aMoney);
    sprintf(Buffer, "%d%s", *(_DWORD *)(v6 + 52), v15);
  }
  else
  {
    strcpy((char *)Buffer, unk_C10D38);
    v2 = (CCBStage *)v19;
  }
  ::InitRound((CCBStage *)this->m_TempStorageNGH, COERCE_FLOAT(Buffer), nVal2, fVal3, nVal4);
  if ( this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24) > *(float *)(v6 + 32) )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FE290
unsigned int CCBStage::ProcShowFiveLineup(int formal)
{
  int m_nClearRoleAllTask; // eax
  int v4; // eax
  int v5; // ecx
  float *v6; // edi
  float v7; // st7
  float height; // st7
  float width; // st7
  __int64 v10; // rax
  float v11; // ebx
  unsigned int v12; // eax
  UIProgressBar *v13; // ecx
  int v15; // [esp-0x4] [ebp-0x34]
  struct gbVec3D v16; // [esp+0xC] [ebp-0x24] BYREF
  int v17; // [esp+0x18] [ebp-0x18]
  float v18; // [esp+0x1C] [ebp-0x14]
  int v19; // [esp+0x20] [ebp-0x10]
  float v20; // [esp+0x24] [ebp-0xC] BYREF
  float v21; // [esp+0x28] [ebp-0x8] BYREF
  int v22; // [esp+0x2C] [ebp-0x4]

  v20 = 0.0f;
  v21 = 0.0f;
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  memset(&v16, 0, sizeof(v16));
  v4 = 2632 * m_nClearRoleAllTask;
  v5 = v4 + 80 * this->m_nRoleSlot;
  v6 = (float *)&this->m_TaskSlots[v5];
  if ( !this->m_TaskSlots[v5 + 41] )
  {
    v16 = *(gbVec3D *)&this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v4)]->m_Task[62].fTemp;
    v16.y = v16.y + 80.0;
    *(gbVec3D *)&this->m_TaskSlots[v5 + 64] = v16;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    *(_DWORD *)&this->m_TaskSlots[v5 + 76] = ((int)g_nCombatRandSeed >> 16) & 0x1F;
    this->m_TaskSlots[v5 + 41] = 1;
  }
  v16 = *(gbVec3D *)&this->m_TaskSlots[v5 + 64];
  (((gbCamera *)&this->m_pCam->OrthoSize))->gbCamera::PointWorldToScr(&v16, &v20, &v21);
  v7 = (this->m_pCBSystem->m_fTimeFund - v6[6]) / v6[8];
  *(float *)&v19 = v7;
  if ( v7 > 1.0f )
    *(float *)&v19 = 1.0;
  v18 = (1.0f - *(float *)&v19) * 255.0f;
  v17 = (int)v18;
  v18 = *(float *)&v19 * 32.0f;
  height = (float)g_DrvInfo.height;
  v19 = 16 - (__int64)((1.0 - v21) * height * -0.5);
  v21 = 1.0f - ((float)v19 + (float)v19) / height;
  width = (float)g_DrvInfo.width;
  v10 = (__int64)((v20 + 1.0) * width * -0.5);
  HIDWORD(v10) = (unsigned long)(this->m_pCBSystem);
  LODWORD(v11) = *((_DWORD *)v6 + 19) - v10 - 16;
  v18 = v11;
  HIBYTE(v22) = v17;
  *(_WORD *)((char *)&v22 + 1) = 13055;
  LOBYTE(v22) = -1;
  v20 = ((float)SLODWORD(v11) + (float)SLODWORD(v11)) / width - 1.0f;
  (***(void ( ****)(_DWORD, int))(*(_DWORD *)(HIDWORD(v10) + 4) + 1080))((_DWORD)(*(_DWORD *)(*(_DWORD *)(HIDWORD(v10) + 4) + 1080)), (int)(1));
  SetEnable((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateMP[0]);
  v15 = v22;
  v12 = (((CCBStage *)this->m_pCBSystem))->CCBStage::ProcShowEnemyFiveLineup();
  (((NPC *)*(NPC **)(v12 + 1080)))->NPC::UpdateAnim(v15);
  AllocObject(this->m_pCBSystem->m_pUI->m_pRoleStateMP[0]);
  ::MoveToAbsolute(this->m_pCBSystem->m_pUI->m_pRoleStateMP[0], LODWORD(v11) - 168, v19 - 128);
  (((UIScene *)this->m_pCBSystem->m_pUI->m_pRoleStateMP[0]))->UIScene::SetShow(0);
  if ( *((_BYTE *)v6 + 43) == 1 || this->m_pCBSystem->m_fTimeFund - v6[6] > v6[8] )
  {
    v13 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateMP[0];
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v13))((UIProgressBar *)(v13), (_DWORD)(0));
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x004FE540
unsigned int CCBStage::ProcShowEnemyFiveLineup()
{
  return (unsigned int)this->m_pRoleState;
}

// 0x004FE550
unsigned int CCBStage::ProcFiveLienupFadeIn(int formal)
{
  int v3; // eax
  int v4; // ecx
  _BYTE *v5; // edi
  _DWORD *v6; // ebp
  CCBStageRole *v7; // ecx

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    v6 = (_DWORD *)(int *)((char *)&this->m_nTaskExist + v3);
    v7 = (CCBStageRole *)this->m_pRole[*v6];
    if ( !v7->m_bCatching || !v7->m_bDelAllTask )
    {
      if ( v7->m_bCatching == 1 )
        (((CCBStage *)v7))->CCBStage::GetCurrentTaskIndex();
      (((CCBStage *)this->m_pRole[*v6]))->CCBStage::DelAllTask(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], 1);
      v5[41] = 1;
      *((_DWORD *)v5 + 4) = 4;
    }
  }
  return 0;
}

// 0x004FE600
unsigned int CCBStage::ProcFiveLienupFadeOut(int formal)
{
  int v2; // eax
  int v3; // edx
  _BYTE *v4; // esi

  v2 = 2632 * this->m_nClearRoleAllTask;
  v3 = v2 + 80 * this->m_nRoleSlot;
  v4 = (_BYTE *)&this->m_TaskSlots[v3];
  if ( !this->m_TaskSlots[v3 + 41] )
  {
    (((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v2)]))->CCBStage::GetCurrentTask(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v2 + 200]);
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  return 0;
}

// 0x004FE660
unsigned int CCBStage::ProcShowSneakAttackState(unsigned int a_74)
{
  int v3; // eax
  _BYTE *v4; // ebp
  _BYTE *v5; // edi
  unsigned int v7; // eax
  void *v8; // ecx
  CCBRoleState *m_pRoleState; // ecx
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  unsigned int v13; // eax
  float v14; // st7
  int m_nClearRoleAllTask; // eax
  tagRoleState *inited; // eax
  int i; // ebx
  int v18; // eax
  CCBRoleState *v19; // ecx
  tagRoleState *v20; // eax
  int nProtectRole; // ebx
  float *p_fTemp; // ecx
  float *v23; // eax
  float v24; // st7
  float v25; // st7
  int RoleIndex; // edi
  char v27; // [esp+0x13] [ebp-0x5D]
  _BYTE *v28; // [esp+0x14] [ebp-0x5C]
  int pnVal; // [esp+0x18] [ebp-0x58] BYREF
  int p_DWORD; // [esp+0x1C] [ebp-0x54] BYREF
  float fp[3]; // [esp+0x20] [ebp-0x50] BYREF
  gbVec3D v32; // [esp+0x2C] [ebp-0x44] BYREF
  gbVec3D v33; // [esp+0x38] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x44] [ebp-0x2C] BYREF

  memset(fp, 0, sizeof(fp));
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (_BYTE *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  v28 = (_BYTE *)v5;
  if ( !(((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*((_DWORD *)v4 + 2)]))->CCBStage::ForceDelTaskByPFN() )
  {
    this->CCBStage::ResetAll();
    v7 = *((_DWORD *)v4 + 2);
    if ( v7 <= 4 && *(_BYTE *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * v7) + 613) == 5
      || (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*((_DWORD *)v4 + 2))->dwID == 7366 )
    {
      pnVal = *((_DWORD *)v4 + 3);
      if ( (unsigned int)pnVal <= 0xA )
      {
        *(int (CCBStage::**)(int))&(v8) = CCBStage::UpdateTaskNormals;
        fp[0] = (float)pnVal;
LABEL_25:
        (((CCBStage *)this->m_pRole[*((_DWORD *)v4 + 2)]))->CCBStage::GetProperCurAction((int)v8, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)fp, v4, 1);
        goto LABEL_26;
      }
      m_pRoleState = (CCBRoleState *)this->m_pRoleState;
      *(float *)&p_DWORD = NAN;
      pnVal = -1;
      (((CCBRoleState *)m_pRoleState))->CCBRoleState::WriteBackRoleData((int)v4, &p_DWORD, &pnVal);
      if ( v10 <= 0xA )
      {
        *(int (CCBStage::**)(int))&(v8) = CCBStage::UpdateTaskNormals;
        fp[0] = (float)*((int *)v4 + 3);
        goto LABEL_25;
      }
    }
    else
    {
      v11 = *((_DWORD *)v4 + 2);
      if ( v11 > 4 )
      {
        if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*((_DWORD *)v4 + 2))->dwID == 720 )
        {
          *(unsigned int (CCBStage::**)(unsigned int))&(v8) = CCBStage::ProcMagic;
        }
        else if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*((_DWORD *)v4 + 2))->dwID == 738
               || (inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*((_DWORD *)v4 + 2)),
                   *(unsigned int (CCBStage::**)(int))&(v8) = CCBStage::ProcTurnToRole,
                   inited->dwID == 739) )
        {
          *(unsigned int (CCBStage::**)(int))&(v8) = CCBStage::ProcBlock;
        }
        goto LABEL_25;
      }
      v12 = v11 - 1;
      if ( v12 )
      {
        v13 = v12 - 1;
        if ( v13 )
        {
          if ( v13 == 1 )
          {
            v14 = (((CCBStage *)this->m_pRole[3]))->CCBStage::AddTask(fp);
            m_nClearRoleAllTask = this->m_nClearRoleAllTask;
            *(float *)&p_DWORD = v14;
            (((CCBStage *)this->m_pRole[*((_DWORD *)v4 + 2)]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::CalcFacingAngle) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * m_nClearRoleAllTask + 200], (int *)fp, v4, 1);
            (((CCBStage *)this->m_pRole[*((_DWORD *)v4 + 2)]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)())CCBStage::CheckAllDone) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)fp, v4, 1);
            *(int (CCBStage::**)(int))&(v8) = CCBStage::ProcessCommand;
            LODWORD(fp[0]) = p_DWORD;
            goto LABEL_25;
          }
        }
        else
        {
          (((CCBStage *)this->m_pRole[2]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcMagic) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)fp, v4, 1);
        }
        *(unsigned int (CCBStage::**)(int))&(v8) = CCBStage::ProcTurnToRole;
        goto LABEL_25;
      }
      (((CCBStage *)this->m_pRole[1]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(float))CCBStage::ProcUseRecoverItem) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)fp, v4, 1);
    }
LABEL_26:
    *((_DWORD *)v5 + 16) = 1;
    v5[41] = 1;
  }
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(*((_DWORD *)v4 + 2)) )
  {
    v27 = 1;
    if ( v4[17] )
    {
      for ( i = 0; i < 11; ++i )
      {
        if ( v4[i + 29] && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(i) )
          v27 = 0;
      }
      if ( v27 )
        goto LABEL_35;
    }
    else if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(*((_DWORD *)v4 + 3)) )
    {
LABEL_35:
      v5[41] = 1;
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
  }
  if ( *((_DWORD *)v5 + 16) == 1 )
  {
    v18 = *((_DWORD *)v4 + 2);
    if ( v18 >= 5 && v18 < 11 )
    {
      v19 = (CCBRoleState *)this->m_pRoleState;
      if ( v19->m_pObjMsgBuffer[153] )
      {
        if ( (((CCBRoleState *)v19))->CCBRoleState::InitUI(0)->nProtectRole >= 0
          && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->nProtectRole < 11 )
        {
          v20 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0);
          if ( (((CCBStage *)this->m_pRoleState))->CCBStage::FindThreadByParam((int)v4, v20->nProtectRole) )
          {
            nProtectRole = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->nProtectRole;
            p_fTemp = (float *)&this->m_pRole[nProtectRole]->m_Task[62].fTemp;
            v23 = (float *)&this->m_pRole[*((_DWORD *)v4 + 2)]->m_Task[62].fTemp;
            v32.x = *p_fTemp - *v23;
            v32.y = p_fTemp[1] - v23[1];
            v24 = p_fTemp[2] - v23[2];
            v33 = v32;
            v32.z = v24;
            v25 = (((gbVec3D *)&v33))->gbVec3D::Length();
            if ( v25 < 120.0f && v25 > 50.0f )
            {
              if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::ForceRoleTaskByCond(nProtectRole) )
              {
                memset(pData, 0, sizeof(pData));
                pData[2] = 0;
                pData[1] = 0;
                pData[3] = nProtectRole;
                RoleIndex = this->CCBStage::GetRoleIndex(18, pData, 1);
                if ( RoleIndex != -1 )
                {
                  v32.x = *((float *)v4 + 2);
                  LODWORD(v32.y) = pData[2];
                  LODWORD(v32.z) = pData[3];
                  this->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ExecuteRoleTask) */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ClearTaskForRole) */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ClearTaskForRoleAll) */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  *((_DWORD *)v28 + 16) = 0;
                  this->CCBStage::GetStageRoleByIdx(RoleIndex);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (((CCBStage *)this->m_pRole[*((_DWORD *)v4 + 2)]))->CCBStage::ForceDelTaskByPFN() || v28[43] == 1 )
    *((_DWORD *)v28 + 4) = 4;
  return 0;
}

// 0x004FECE0
void CCBStage::HandleKeyCtrl(int n)
{
  int v3; // edi
  int *v4; // ebp
  _BYTE *v5; // ebx

  if ( (byte_17AA91C & 1) == 0 )
  {
    pnVal = 0;
    LOBYTE(byte_17AA91C) = byte_17AA91C | 1;
    dword_17AA914 = 0;
    dword_17AA918 = 0;
    atexit(nullsub_21);
  }
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( (((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
  {
    if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
    {
      *(float *)&pnVal = (float)*v4;
      *(float *)&dword_17AA914 = (float)*(int *)((char *)&this->m_DamageData + v3);
      (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ResolveActionEffect) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], &pnVal, &this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 208], 1);
      v5[41] = 1;
    }
    if ( (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
      *((_DWORD *)v5 + 4) = 4;
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    *((_DWORD *)v5 + 4) = 4;
  }
}

// 0x004FEE60
bool CCBStage::HandleKeyFriend(int Selected)
{
  int v2; // eax
  int v3; // edx
  _BYTE *v4; // esi

  v2 = 2632 * this->m_nClearRoleAllTask;
  v3 = v2 + 80 * this->m_nRoleSlot;
  v4 = (_BYTE *)&this->m_TaskSlots[v3];
  if ( !this->m_TaskSlots[v3 + 41] )
  {
    (((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v2)]))->CCBStage::ProcTransportRun(pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessSlotAction), 0, 0, 0, 0, 0, 3);
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  if ( v4[43] == 1 )
    *((_DWORD *)v4 + 4) = 4;
  return 0;
}

// 0x004FEEF0
int CCBStage::sub_4FEEF0(void *thisa)
{
  int v3; // eax
  int v4; // ecx
  _BYTE *v5; // edi
  int *v6; // ebp

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    v6 = (int *)((char *)&this->m_nTaskExist + v3);
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(*v6, 17)
      && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(*v6, 14) )
    {
      (((CCBStage *)this->m_pRole[*v6]))->CCBStage::ProcTransportRun(pmf_to_u32((int (CCBStage::*)(int))CCBStage::OnPhysicalHit), 0, 0, 0, 0, 0, 3);
    }
    v5[41] = 1;
    *((_DWORD *)v5 + 4) = 4;
  }
  if ( v5[43] == 1 )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FEFB0
unsigned int CCBStage::ProcShowName(unsigned int formal)
{
  int v3; // eax
  int *v4; // edi
  _BYTE *v5; // ebx
  int v7; // eax
  CCBStageRole *v8; // ecx
  void *v9; // edx
  int v10; // ecx
  float v11; // st7
  int m_nClearRoleAllTask; // eax
  int pnVal[3]; // [esp+0x14] [ebp-0xC] BYREF

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    v7 = (unsigned long)*v4;
    if ( *v4 >= 0 && v7 < 5 )
    {
      switch ( v7 )
      {
        case 1:
          v8 = (CCBStageRole *)this->m_pRole[1];
          *(unsigned int (CCBStage::**)(float))&(v9) = CCBStage::ProcUseRecoverItem;
          break;
        case 2:
          v8 = (CCBStageRole *)this->m_pRole[2];
          *(unsigned int (CCBStage::**)(unsigned int))&(v9) = CCBStage::ProcMagic;
          break;
        case 3:
          v8 = (CCBStageRole *)this->m_pRole[3];
          *(int (CCBStage::**)())&(v9) = CCBStage::CheckAllDone;
          break;
        default:
          v8 = (CCBStageRole *)this->m_pRole[v7];
          *(unsigned int (CCBStage::**)(int))&(v9) = CCBStage::ProcTurnToRole;
          break;
      }
      goto LABEL_22;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*v4)->dwID == 720 )
    {
      *(unsigned int (CCBStage::**)(unsigned int))&(v9) = CCBStage::ProcMagic;
    }
    else
    {
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*v4)->dwID != 738
        && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*v4)->dwID != 739 )
      {
        *(unsigned int (CCBStage::**)(int))&(v9) = CCBStage::ProcTurnToRole;
        v8 = (CCBStageRole *)this->m_pRole[*v4];
LABEL_22:
        (((CCBStage *)v8))->CCBStage::GetProperCurAction((int)v9, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)&v8->m_Task[62].eMode, 0, 1);
        v10 = (unsigned long)*v4;
        v11 = *(float *)&this->m_pRole[*v4]->m_Task[63].cmd.dwCmdKind;
        pnVal[1] = 0;
        m_nClearRoleAllTask = this->m_nClearRoleAllTask;
        *(float *)pnVal = v11;
        pnVal[2] = 0;
        (((CCBStage *)this->m_pRole[v10]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * m_nClearRoleAllTask + 200], pnVal, 0, 1);
        v5[41] = 1;
        goto LABEL_23;
      }
      *(unsigned int (CCBStage::**)(int))&(v9) = CCBStage::ProcBlock;
    }
    v8 = (CCBStageRole *)this->m_pRole[*v4];
    goto LABEL_22;
  }
LABEL_23:
  if ( (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
    *((_DWORD *)v5 + 4) = 4;
  if ( v5[43] == 1 && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*v4)->nHP )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF1B0
unsigned int CCBStage::ProcShowItemName(int formal)
{
  int v3; // eax
  int *v4; // ebp
  _BYTE *v5; // edi
  void *v6; // edx
  CCBStageRole *v7; // ecx
  int v8; // ecx
  float v9; // st7
  int m_nClearRoleAllTask; // eax
  int pnVal[3]; // [esp+0x18] [ebp-0xC] BYREF

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_13;
  if ( v5[41] || !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
    goto LABEL_12;
  if ( *v4 == 1 )
    goto LABEL_9;
  if ( *v4 != 2 )
  {
    if ( *v4 != 3 )
    {
      *(unsigned int (CCBStage::**)(int))&(v6) = CCBStage::ProcTurnToRole;
LABEL_10:
      v7 = (CCBStageRole *)this->m_pRole[*v4];
      (((CCBStage *)v7))->CCBStage::GetProperCurAction((int)v6, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)&v7->m_Task[62].eMode, 0, 1);
      goto LABEL_11;
    }
LABEL_9:
    *(unsigned int (CCBStage::**)(float))&(v6) = CCBStage::ProcUseRecoverItem;
    goto LABEL_10;
  }
  (((CCBStage *)this->m_pRole[2]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcMagic) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)&this->m_pRole[2]->m_Task[62].eMode, 0, 1);
LABEL_11:
  v8 = (unsigned long)*v4;
  v9 = *(float *)&this->m_pRole[*v4]->m_Task[63].cmd.dwCmdKind;
  pnVal[1] = 0;
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  *(float *)pnVal = v9;
  pnVal[2] = 0;
  (((CCBStage *)this->m_pRole[v8]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * m_nClearRoleAllTask + 200], pnVal, 0, 1);
  v5[41] = 1;
LABEL_12:
  if ( (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_13:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF3D0
unsigned int CCBStage::ProcShowDamage(unsigned int formal)
{
  int v3; // ebp
  int v4; // eax
  char v5; // cl
  _BYTE *v6; // eax
  int v7; // edi
  CCBStageRole **m_pRole; // ebx
  int v9; // ecx
  CCBStageRole *p_fTemp; // eax
  gbVec3D *v11; // ecx
  int ItemNum; // eax
  int v13; // eax
  _DWORD *v14; // ebp
  CCBRoleState *m_pRoleState; // ecx
  CCBStageRole *v16; // eax
  ECBRoleTaskMode *p_eMode; // eax
  float *v18; // esi
  _BYTE *v20; // [esp+0x8] [ebp-0x4]

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = this->m_TaskSlots[v4 + 41];
  v6 = (_BYTE *)&this->m_TaskSlots[v4];
  v20 = (_BYTE *)v6;
  if ( !v5 )
  {
    v7 = 0;
    m_pRole = (CCBStageRole **)this->m_pRole;
    do
    {
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v7)->bValid && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v7)->bAlive )
      {
        v9 = *(_DWORD *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v7)->byMagicUseTime[8][3];
        p_fTemp = (CCBStageRole *)&(*m_pRole)->m_Task[62].fTemp;
        v11 = (gbVec3D *)&this->m_pScene->m_vecInitFiveLineup[v9];
        p_fTemp->m_pStage = (CCBStage *)LODWORD(v11->x);
        p_fTemp->m_pRoleState = (CCBRoleState *)LODWORD(v11->y);
        *(float *)p_fTemp->m_sLastRole = v11->z;
        LODWORD((*m_pRole)->m_Task[63].vec1.v.z) = (*m_pRole)->m_Task[63].cmd.dwCmdKind;
      }
      ++v7;
      ++m_pRole;
    }
    while ( v7 < 5 );
    ItemNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(*(int *)((char *)&this->m_TaskState + v3));
    if ( ItemNum )
    {
      if ( *(_BYTE *)(ItemNum + 592) == 2 )
      {
        v13 = *(int *)((char *)&this->m_DamageData + v3);
        v14 = (_DWORD *)(int *)((char *)&this->m_DamageData + v3);
        if ( v13 != -1 && v13 != 10 )
        {
          m_pRoleState = (CCBRoleState *)this->m_pRoleState;
          if ( *(&m_pRoleState->m_byteFlags + 1821) )
          {
            if ( !LOBYTE((((CCBRoleState *)m_pRoleState))->CCBRoleState::InitUI(10)[1].dwMagicID[2][5]) )
            {
              v16 = (CCBStageRole *)this->m_pRole[10];
              if ( v16->m_bAlive )
              {
                v16->m_Task[62].fTemp = *(float *)&v16->m_Task[62].eMode;
                v16->m_Task[62].fTemp2 = *(float *)&v16->m_Task[62].bValid;
                v16->m_Task[62].dwID = *(_DWORD *)(&v16->m_Task[62].bExecuted + 2);
                (((CCBStage *)this->m_pRole[10]))->CCBStage::ForceRelease(0);
              }
            }
          }
          p_eMode = (ECBRoleTaskMode *)&this->m_pRole[10]->m_Task[62].eMode;
          v18 = (float *)&this->m_pRole[*v14]->m_Task[62].fTemp;
          *v18 = *(float *)p_eMode;
          v18[1] = *(float *)&p_eMode[4];
          v18[2] = *(float *)&p_eMode[8];
        }
      }
    }
    v6 = (_BYTE *)v20;
    v20[41] = 1;
  }
  *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FF560
int CCBStage::ProcTaskSlot(int nVal)
{
  int v2; // eax
  int v3; // edx
  _BYTE *v4; // esi

  v2 = 2632 * this->m_nClearRoleAllTask;
  v3 = v2 + 80 * this->m_nRoleSlot;
  v4 = (_BYTE *)&this->m_TaskSlots[v3];
  if ( !this->m_TaskSlots[v3 + 41] )
    this->m_TaskSlots[v3 + 41] = 1;
  if ( this->m_TaskSlots[v3 + 43] == 1
    || (((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v2)]))->CCBStage::ForceDelTaskByPFN() )
  {
    *((_DWORD *)v4 + 4) = 4;
  }
  return 0;
}

// 0x004FF5C0
unsigned int CCBStage::ProcShowCost(int formal)
{
  int v3; // eax
  int v4; // ecx
  int *v5; // ebp
  _BYTE *v6; // esi
  CCBStageRole *v7; // eax
  int v8; // eax
  int v9; // edx
  Actor *m_TempStorageWPX; // ecx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  char v14; // al
  char v15; // al

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (int *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v6 = (_BYTE *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    v7 = (CCBStageRole *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)];
    LODWORD(v7->m_Task[63].vec1.v.z) = v7->m_Task[63].cmd.dwCmdKind;
    this->m_TaskSlots[v4 + 41] = 1;
    (((CCBCamControl *)this->m_TempStorageWPX))->CCBCamControl::KeepCurCam(v5[1]);
    *((_DWORD *)v6 + 14) = v8;
    v6[62] = 0;
    v6[61] = 0;
    v6[60] = 0;
    *((_DWORD *)v6 + 17) = 0;
    *((_DWORD *)v6 + 16) = 0;
  }
  v9 = *((_DWORD *)v6 + 14);
  m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
  v11 = (int)(&m_TempStorageWPX[2].m_nUpdateMode + 15 * v9 + 5);
  if ( !v6[60]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *((float *)&m_TempStorageWPX[3].m_actarray_end + 15 * v9) )
  {
    (((CCBStage *)m_TempStorageWPX))->CCBStage::_CCBStageRole(v9, 1, v5);
    *((_DWORD *)v6 + 16) = v12;
    v6[60] = 1;
  }
  if ( !v6[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)(v11 + 52) )
  {
    (((CCBStage *)this->m_TempStorageWPX))->CCBStage::_CCBStageRole(*((_DWORD *)v6 + 14), 2, v5);
    *((_DWORD *)v6 + 17) = v13;
    v6[61] = 1;
  }
  if ( !v6[62]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *((float *)&this->m_TempStorageWPX[3].m_actarray_capacity_end
                                                              + 15 * *((_DWORD *)v6 + 14)) )
  {
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 208]);
    v6[62] = 1;
  }
  if ( (((CCBStage *)this->m_pRole[v5[2]]))->CCBStage::ForceDelTaskByPFN() )
  {
    if ( v6[62] )
    {
      (((CEffMgr *)this->m_pCBSystem->m_pEffMgr))->CEffMgr::Render(*((_DWORD *)v6 + 16));
      if ( !v14 )
      {
        (((CEffMgr *)this->m_pCBSystem->m_pEffMgr))->CEffMgr::Render(*((_DWORD *)v6 + 17));
        if ( !v15 )
          *((_DWORD *)v6 + 4) = 4;
      }
    }
  }
  return 0;
}

// 0x004FF740
unsigned int CCBStage::ProcShowCombatDialog(int formal)
{
  int v3; // ecx
  int v4; // edx
  _BYTE *v5; // eax
  int v6; // ebp
  int v7; // esi
  CCBStageRole **m_pRole; // ebx
  CCBRoleState *m_pRoleState; // ecx
  CCBStageRole *v10; // eax
  CCBRoleState *v11; // ecx
  CCBStage *v12; // ecx
  _BYTE *v14; // [esp+0x4] [ebp-0x4]

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[8 * v3 + v4];
  v14 = (_BYTE *)v5;
  if ( !this->m_TaskSlots[8 * v3 + 41 + v4] )
  {
    v6 = 0;
    v7 = 0;
    m_pRole = (CCBStageRole **)this->m_pRole;
    do
    {
      m_pRoleState = (CCBRoleState *)this->m_pRoleState;
      if ( m_pRoleState->m_pObjMsgBuffer[v7 + 153] && !LOBYTE((((CCBRoleState *)m_pRoleState))->CCBRoleState::InitUI(v6)[1].dwMagicID[2][5]) )
      {
        v10 = (CCBStageRole *)*m_pRole;
        v10->m_Task[62].fTemp = *(float *)&(*m_pRole)->m_Task[62].eMode;
        v10->m_Task[62].fTemp2 = *(float *)&v10->m_Task[62].bValid;
        v10->m_Task[62].dwID = *(_DWORD *)(&v10->m_Task[62].bExecuted + 2);
        LODWORD((*m_pRole)->m_Task[63].vec1.v.z) = (*m_pRole)->m_Task[63].cmd.dwCmdKind;
      }
      v7 += 892;
      ++v6;
      ++m_pRole;
    }
    while ( v7 < 9812 );
    v11 = (CCBRoleState *)this->m_pRoleState;
    if ( *(&v11->m_byteFlags + 1821) )
    {
      if ( !LOBYTE((((CCBRoleState *)v11))->CCBRoleState::InitUI(10)[1].dwMagicID[2][5]) )
      {
        v12 = (CCBStage *)this->m_pRole[10];
        if ( v12->m_TaskSlots[88] )
          (((CCBStage *)v12))->CCBStage::ForceRelease(1);
      }
    }
    v5 = (_BYTE *)v14;
    v14[41] = 1;
  }
  *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF840
unsigned int CCBStage::ProcGrabStageRole(unsigned int formal)
{
  int v3; // eax
  _DWORD *v4; // edi
  _BYTE *v5; // ebp
  CCBStageRole *v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  int v9; // eax
  int v10; // eax
  int m_nClearRoleAllTask; // eax
  int pnVal[6]; // [esp+0x14] [ebp-0x1C] BYREF
  int v14; // [esp+0x2C] [ebp-0x4]

  memset(pnVal, 0, 12);
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_17;
  if ( !v5[41] )
  {
    if ( !(((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() )
      return 0;
    (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetCurrentState();
    v6 = this->m_pRole[v4[2]];
    LODWORD(v6->m_Task[63].vec1.v.z) = v6->m_Task[63].cmd.dwCmdKind;
    v7 = (unsigned long)v4[1];
    if ( v7 > 0x10D0 )
    {
      if ( v7 == 4505 )
      {
        this->CCBStage::ResetAll();
        m_nClearRoleAllTask = this->m_nClearRoleAllTask;
        v14 = 0;
        (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcTurnToRole) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * m_nClearRoleAllTask + 200], pnVal, v4, 1);
      }
    }
    else if ( v7 == 4304 || (v8 = v7 - 4101) == 0 )
    {
      this->CCBStage::ResetAll();
      v10 = this->m_nClearRoleAllTask;
      v14 = 0;
      (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcMagic) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * v10 + 200], pnVal, v4, 1);
    }
    else if ( v8 == 104 )
    {
      this->CCBStage::ResetAll();
      v9 = this->m_nClearRoleAllTask;
      v14 = 0;
      (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(float))CCBStage::ProcUseRecoverItem) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * v9 + 200], pnVal, v4, 1);
    }
    v5[41] = 1;
  }
  if ( (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() || v5[43] == 1 )
  {
    (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::TryRelease();
LABEL_17:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x004FFA90
int CCBStage::TaskExecAttack(int nVal)
{
  int v3; // eax
  int *v4; // ebp
  _BYTE *v5; // edi
  CCBStageRole *v7; // eax
  int v8; // eax
  int v9; // edx
  Actor *m_TempStorageWPX; // ecx
  int v11; // ebx

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
    goto LABEL_6;
  if ( (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() )
  {
    v7 = this->m_pRole[v4[2]];
    LODWORD(v7->m_Task[63].vec1.v.z) = v7->m_Task[63].cmd.dwCmdKind;
    (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::AnimCallback_Attack) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], 0, v4, 1);
    v5[41] = 1;
    (((CCBCamControl *)this->m_TempStorageWPX))->CCBCamControl::KeepCurCam(v4[1]);
    *((_DWORD *)v5 + 14) = v8;
    v5[62] = 0;
    v5[61] = 0;
    v5[60] = 0;
LABEL_6:
    v9 = *((_DWORD *)v5 + 14);
    m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
    v11 = (int)(&m_TempStorageWPX[2].m_nUpdateMode + 15 * v9 + 5);
    if ( !v5[60]
      && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *((float *)&m_TempStorageWPX[3].m_actarray_end + 15 * v9) )
    {
      (((CCBStage *)m_TempStorageWPX))->CCBStage::_CCBStageRole(v9, 1, v4);
      v5[60] = 1;
    }
    if ( !v5[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *(float *)(v11 + 52) )
    {
      (((CCBStage *)this->m_TempStorageWPX))->CCBStage::_CCBStageRole(*((_DWORD *)v5 + 14), 2, v4);
      v5[61] = 1;
    }
    if ( !v5[62]
      && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *((float *)&this->m_TempStorageWPX[3].m_actarray_capacity_end
                                                                + 15 * *((_DWORD *)v5 + 14)) )
    {
      if ( v4[1] != 4101 && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v4[2]) )
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 208]);
      v5[62] = 1;
    }
    if ( (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() && v5[62] )
    {
      if ( v4[1] == 4101 && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v4[2]) )
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 208]);
      *((_DWORD *)v5 + 4) = 4;
    }
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x004FFCB0
int CCBStage::TaskExecCommand(int nVal)
{
  int v3; // eax
  int *v4; // ebx
  _BYTE *v5; // edi
  int v6; // eax
  int v7; // ecx
  float v8; // st7
  int m_nClearRoleAllTask; // eax
  int pnVal[3]; // [esp+0x18] [ebp-0xC] BYREF

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_15;
  if ( v5[41] || !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
    goto LABEL_13;
  (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetCurrentState();
  v6 = (unsigned long)*v4;
  if ( *v4 >= 0 && v6 < 5 )
  {
    switch ( v6 )
    {
      case 1:
        goto LABEL_11;
      case 2:
        (((CCBStage *)this->m_pRole[2]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcMagic) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)&this->m_pRole[2]->m_Task[62].eMode, 0, 1);
        goto LABEL_12;
      case 3:
LABEL_11:
        (((CCBStage *)this->m_pRole[v6]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(float))CCBStage::ProcUseRecoverItem) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)&this->m_pRole[v6]->m_Task[62].eMode, 0, 1);
        goto LABEL_12;
    }
    (((CCBStage *)this->m_pRole[v6]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcTurnToRole) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)&this->m_pRole[v6]->m_Task[62].eMode, 0, 1);
  }
LABEL_12:
  v7 = (unsigned long)*v4;
  v8 = *(float *)&this->m_pRole[*v4]->m_Task[63].cmd.dwCmdKind;
  pnVal[1] = 0;
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  *(float *)pnVal = v8;
  pnVal[2] = 0;
  (((CCBStage *)this->m_pRole[v7]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * m_nClearRoleAllTask + 200], pnVal, 0, 1);
  v5[41] = 1;
LABEL_13:
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_15:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FFED0
int CCBStage::TaskResetToIdle(int nVal)
{
  int v3; // ecx
  int v4; // edx
  _BYTE *v5; // edi
  CCBStageRole *v6; // eax

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[8 * v3 + v4];
  if ( !this->m_TaskSlots[8 * v3 + 41 + v4]
    && (((CCBStage *)this->m_pRole[*(_DWORD *)&this->m_TaskSlots[8 * v3 + 48 + v4]]))->CCBStage::ForceDelTaskByPFN() )
  {
    (((CCBStage *)this->m_pRole[*((_DWORD *)v5 + 12)]))->CCBStage::GetCurrentState();
    v6 = (CCBStageRole *)this->m_pRole[*((_DWORD *)v5 + 12)];
    LODWORD(v6->m_Task[63].vec1.v.z) = v6->m_Task[63].cmd.dwCmdKind;
    v5[41] = 1;
  }
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*((_DWORD *)v5 + 12)]))->CCBStage::ForceDelTaskByPFN() )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FFF60
int CCBStage::TaskExecMagicEffect(int nVal)
{
  int v3; // eax
  int v4; // ecx
  int *v5; // ebp
  _BYTE *v6; // esi
  int v7; // eax
  int v8; // edx
  Actor *m_TempStorageWPX; // ecx
  int v10; // eax
  CCBStage *Instance; // eax
  char v12; // al
  CCBStage *v13; // eax
  CCBStage *v14; // eax
  int v16; // [esp+0x10] [ebp-0x4]

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (int *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v6 = (_BYTE *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    if ( !(((CCBStage *)this->m_pRole[*(_DWORD *)&this->m_TaskSlots[v4 + 48]]))->CCBStage::ForceDelTaskByPFN() )
      return 0;
    (((CCBStage *)this->m_pRole[*((_DWORD *)v6 + 12)]))->CCBStage::GetCurrentState();
    (((CCBStage *)this->m_pRole[*((_DWORD *)v6 + 12)]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::AnimCallback_CastMagic) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], 0, 0, 1);
    v6[41] = 1;
    (((CCBCamControl *)this->m_TempStorageWPX))->CCBCamControl::KeepCurCam(v5[1]);
    *((_DWORD *)v6 + 14) = v7;
    v6[62] = 0;
    v6[61] = 0;
    v6[60] = 0;
    *((_DWORD *)v6 + 16) = 0;
  }
  v8 = *((_DWORD *)v6 + 14);
  m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
  v16 = (int)(&m_TempStorageWPX[2].m_nUpdateMode + 15 * v8 + 5);
  if ( !v6[60]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *((float *)&m_TempStorageWPX[3].m_actarray_end + 15 * v8) )
  {
    (((CCBStage *)m_TempStorageWPX))->CCBStage::_CCBStageRole(v8, 1, v5);
    *((_DWORD *)v6 + 16) = v10;
    (((CCBSystem *)this->m_pCBSystem))->CCBSystem::ProcAI(0.0);
    this->m_pRole[*((_DWORD *)v6 + 12)]->m_bAbsTime = 1;
    Instance = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)Instance))->CCBStage::PauseSound();
    v6[60] = 1;
  }
  if ( !v6[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)(v16 + 52) )
  {
    (((CCBStage *)this->m_TempStorageWPX))->CCBStage::_CCBStageRole(*((_DWORD *)v6 + 14), 2, v5);
    v6[61] = 1;
  }
  if ( v6[60] )
  {
    (((CEffMgr *)this->m_pCBSystem->m_pATSEffMgr))->CEffMgr::Render(*((_DWORD *)v6 + 16));
    if ( !v12 )
    {
      (((CCBSystem *)this->m_pCBSystem))->CCBSystem::ProcAI(1.0);
      v13 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v13))->CCBStage::ResumeSound();
      this->m_pRole[*((_DWORD *)v6 + 12)]->m_bAbsTime = 0;
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v5[2]) )
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 208]);
      v6[62] = 1;
      *((_DWORD *)v6 + 4) = 4;
    }
  }
  if ( v6[43] == 1 )
  {
    (((CCBSystem *)this->m_pCBSystem))->CCBSystem::ProcAI(1.0);
    v14 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v14))->CCBStage::ResumeSound();
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x00500220
int CCBStage::TaskExecSkill(int nVal)
{
  int v3; // eax
  int *v4; // ebp
  _BYTE *v5; // edi
  int v7; // eax
  tagRoleState *inited; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  Actor *m_TempStorageWPX; // ecx
  int v14; // ebx
  int pnVal[3]; // [esp+0x10] [ebp-0xC] BYREF

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
    goto LABEL_15;
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CheckMagicCost(v4)
    && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CheckEventCondition((int)v4) )
  {
    if ( !(((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() )
      return 0;
    v7 = (unsigned long)v4[2];
    memset(pnVal, 0, sizeof(pnVal));
    if ( v7 >= 5 && v7 < 11 )
    {
      inited = (((CCBRoleState *)this->m_pCBSystem->m_pRoleState))->CCBRoleState::InitUI(v7);
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(inited->dwID);
      if ( v9 )
      {
        v10 = (unsigned long)v4[1];
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
    (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetCurrentState();
    (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(float))CCBStage::UpdateActionTimers) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], pnVal, 0, 1);
    v5[41] = 1;
    (((CCBCamControl *)this->m_TempStorageWPX))->CCBCamControl::KeepCurCam(v4[1]);
    *((_DWORD *)v5 + 14) = v11;
    v5[62] = 0;
    v5[61] = 0;
    v5[60] = 0;
LABEL_15:
    v12 = *((_DWORD *)v5 + 14);
    m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
    v14 = (int)(&m_TempStorageWPX[2].m_nUpdateMode + 15 * v12 + 5);
    if ( !v5[60]
      && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *((float *)&m_TempStorageWPX[3].m_actarray_end + 15 * v12) )
    {
      (((CCBStage *)m_TempStorageWPX))->CCBStage::_CCBStageRole(v12, 1, v4);
      v5[60] = 1;
    }
    if ( !v5[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *(float *)(v14 + 52) )
    {
      (((CCBStage *)this->m_TempStorageWPX))->CCBStage::_CCBStageRole(*((_DWORD *)v5 + 14), 2, v4);
      v5[61] = 1;
    }
    if ( !v5[62]
      && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *((float *)&this->m_TempStorageWPX[3].m_actarray_capacity_end
                                                                + 15 * *((_DWORD *)v5 + 14)) )
    {
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v4[2]) )
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 208]);
      v5[62] = 1;
    }
    if ( (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() && v5[62] )
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
int CCBStage::TaskWaitIdle(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  _BYTE *v5; // ebp

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (_DWORD *)(int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_7;
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetCurrentState();
    v5[41] = 1;
  }
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00500550
int CCBStage::TaskExecItem(int nVal)
{
  int v3; // eax
  int *v4; // ebp
  _BYTE *v5; // edi
  CCBStageRole *v7; // eax
  int v8; // eax
  int v9; // edx
  Actor *m_TempStorageWPX; // ecx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  char v14; // al

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
  {
LABEL_9:
    v9 = *((_DWORD *)v5 + 14);
    m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
    v11 = (int)(&m_TempStorageWPX[2].m_nUpdateMode + 15 * v9 + 5);
    if ( !v5[60]
      && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *((float *)&m_TempStorageWPX[3].m_actarray_end + 15 * v9) )
    {
      (((CCBStage *)m_TempStorageWPX))->CCBStage::_CCBStageRole(v9, 1, v4);
      *((_DWORD *)v5 + 16) = v12;
      v5[60] = 1;
    }
    if ( !v5[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) >= *(float *)(v11 + 52) )
    {
      (((CCBStage *)this->m_TempStorageWPX))->CCBStage::_CCBStageRole(*((_DWORD *)v5 + 14), 2, v4);
      *((_DWORD *)v5 + 17) = v13;
      v5[61] = 1;
    }
    if ( v5[62]
      || this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) < *((float *)&this->m_TempStorageWPX[3].m_actarray_capacity_end
                                                               + 15 * *((_DWORD *)v5 + 14))
      || !v5[60] )
    {
      goto LABEL_25;
    }
    if ( (((CCBSystem *)this->m_pCBSystem->m_pRoleState))->CCBSystem::IsMagicSlotMsg((int)v4) )
    {
      (((CEffMgr *)this->m_pCBSystem->m_pEffMgr))->CEffMgr::Render(*((_DWORD *)v5 + 16));
      if ( v14 )
        goto LABEL_25;
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v4[2]) )
        goto LABEL_23;
    }
    else if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v4[2]) )
    {
LABEL_23:
      (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 208]);
    }
    v5[62] = 1;
LABEL_25:
    if ( (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() && v5[62] )
      *((_DWORD *)v5 + 4) = 4;
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::ForceDelTaskByPFN() )
  {
    v7 = this->m_pRole[v4[2]];
    LODWORD(v7->m_Task[63].vec1.v.z) = v7->m_Task[63].cmd.dwCmdKind;
    if ( (((PAL_GDB *)this->m_pRoleState))->PAL_GDB::GetSkillLevel(v4[1]) )
      (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::AnimCallback_UseItem) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], 0, 0, 1);
    else
      (((CCBStage *)this->m_pRole[v4[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::OnMagicHit) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], 0, v4, 1);
    v5[41] = 1;
    (((CCBCamControl *)this->m_TempStorageWPX))->CCBCamControl::KeepCurCam(v4[1]);
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
int CCBStage::TaskForceEnd(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  _BYTE *v5; // ebp

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (_DWORD *)(int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( v5[41] )
    goto LABEL_6;
  if ( (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    v5[41] = 1;
LABEL_6:
    if ( (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
      *((_DWORD *)v5 + 4) = 4;
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00500840
int CCBStage::ExecuteRoleTask(int nVal)
{
  int m_nClearRoleAllTask; // eax
  int v4; // ebp
  int *v5; // ebx
  int *v6; // edi
  int v7; // eax
  CCBStage **v8; // ecx
  float m_fCombatAnimY; // st7
  int v10; // eax
  int pnVal; // [esp+0x10] [ebp-0x18] BYREF
  float v13; // [esp+0x14] [ebp-0x14]
  int v14; // [esp+0x18] [ebp-0x10]
  int v15[3]; // [esp+0x1C] [ebp-0xC] BYREF

  *(float *)&pnVal = 0.0;
  v13 = 0.0f;
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v14 = 0;
  v4 = 2632 * m_nClearRoleAllTask;
  v5 = (int *)(&this->m_nTaskExist + 658 * m_nClearRoleAllTask);
  v6 = (int *)&this->m_TaskSlots[2632 * m_nClearRoleAllTask + 80 * this->m_nRoleSlot];
  if ( !(((CCBStage *)this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v4)]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v4 + 200]) )
    goto LABEL_8;
  if ( !*((_BYTE *)v6 + 41) )
  {
    if ( (((CCBStage *)this->m_pRole[*v5]))->CCBStage::ForceDelTaskByPFN() )
    {
      *(float *)&pnVal = (float)*(int *)((char *)&this->m_DamageData + v4);
      v7 = this->m_nClearRoleAllTask;
      v13 = (float)v6[11];
      (((CCBStage *)this->m_pRole[*v5]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::UpdateSlotTimer) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * v7 + 200], &pnVal, 0, 1);
      v8 = (CCBStage **)&this->m_pRole[*v5];
      m_fCombatAnimY = (*v8)->m_fCombatAnimY;
      v15[1] = 0;
      v10 = this->m_nClearRoleAllTask;
      *(float *)v15 = m_fCombatAnimY;
      v15[2] = 0;
      (((CCBStage *)*v8))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * v10 + 200], v15, 0, 1);
      *((_BYTE *)v6 + 41) = 1;
    }
    else
    {
      *((_BYTE *)v6 + 41) = 1;
      v6[4] = 4;
    }
  }
  if ( *((_BYTE *)v6 + 43) == 1 || (((CCBStage *)this->m_pRole[*v5]))->CCBStage::ForceDelTaskByPFN() )
LABEL_8:
    v6[4] = 4;
  return 0;
}

// 0x005009C0
int CCBStage::ClearTaskForRole(int nVal)
{
  int v3; // edi
  _DWORD *v4; // ebp
  _BYTE *v5; // ebx
  int m_nClearRoleAllTask; // eax
  int pnVal[3]; // [esp+0x14] [ebp-0xC] BYREF

  memset(pnVal, 0, sizeof(pnVal));
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (_DWORD *)(int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_7;
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    m_nClearRoleAllTask = this->m_nClearRoleAllTask;
    *(float *)pnVal = (float)*(int *)((char *)&this->m_DamageData + v3);
    (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int, int))CCBStage::AnimCallback_Throw) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * m_nClearRoleAllTask + 200], pnVal, 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00500AD0
int CCBStage::ClearTaskForRoleAll(int nVal)
{
  int v3; // eax
  int *v4; // edi
  _BYTE *v5; // ebx
  int v6; // ecx
  float v7; // st7
  int m_nClearRoleAllTask; // eax
  int pnVal[3]; // [esp+0x14] [ebp-0xC] BYREF

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_7;
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcTurnToRole) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], (int *)&this->m_pRole[*v4]->m_Task[62].eMode, 0, 1);
    v6 = (unsigned long)*v4;
    v7 = *(float *)&this->m_pRole[*v4]->m_Task[63].cmd.dwCmdKind;
    pnVal[1] = 0;
    m_nClearRoleAllTask = this->m_nClearRoleAllTask;
    *(float *)pnVal = v7;
    pnVal[2] = 0;
    (((CCBStage *)this->m_pRole[v6]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * m_nClearRoleAllTask + 200], pnVal, 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00500C20
int CCBStage::TaskExecAction(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  _BYTE *v5; // ebx

  if ( (g_nCBRoleAnimData[23] & 1) == 0 )
  {
    g_nCBRoleAnimData[20] = 0;
    LOBYTE(g_nCBRoleAnimData[23]) |= 1u;
    g_nCBRoleAnimData[21] = 0;
    g_nCBRoleAnimData[22] = 0;
    atexit(nullsub_22);
  }
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (_DWORD *)(int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_9;
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::AnimCallback_WaitCmd) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], &g_nCBRoleAnimData[20], 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_9:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00500D50
int CCBStage::TaskResolveAction(int nState)
{
  int v3; // eax
  int *v4; // esi
  int v5; // ecx
  int v6; // eax
  _BYTE *v7; // edi
  CCBStage *v8; // ecx
  CCBSystem *m_pCBSystem; // edx
  int RoleIndex; // edi
  _BYTE *v11; // eax
  int v13; // esi
  int v14; // eax
  CCBStage **m_pRole; // edi
  CCBRoleState *m_pRoleState; // ecx
  int v17; // eax
  CCBSystem *v18; // edx
  tagThread *v19; // eax
  bool v20; // cc
  CCBControl *m_pControl; // ecx
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
  unsigned int v32; // [esp+0x100] [ebp-0x18]
  _BYTE *v33; // [esp+0x104] [ebp-0x14]
  int nIndex; // [esp+0x108] [ebp-0x10]
  CCBStage **v35; // [esp+0x10C] [ebp-0xC]
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
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = v3 + 80 * this->m_nRoleSlot;
  v24 = *(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200];
  v6 = (unsigned long)*v4;
  v30 = (int *)v4;
  v7 = (_BYTE *)&this->m_TaskSlots[v5];
  v8 = (CCBStage *)this->m_pRole[v6];
  v33 = (_BYTE *)v7;
  if ( !(((CCBStage *)v8))->CCBStage::IsReady(v24) )
  {
LABEL_42:
    *((_DWORD *)v7 + 4) = 4;
    return 0;
  }
  if ( v7[41] )
  {
LABEL_39:
    if ( v7[43] != 1 && !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
      return 0;
    *((_DWORD *)v7 + 9) = 1;
    goto LABEL_42;
  }
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CheckRoleMP(2) != -1 )
  {
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CheckRoleMP(2);
    v36 = _pal3_coerce_f32((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::ApplyDamage(3, *v4));
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
      g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
      v37 = (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)v35;
    }
    else
    {
      v37 = 0;
    }
    if ( this->m_pRoleState->m_pObjMsgBuffer[125] )
      v37 = 1;
    m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
    if ( LOBYTE(this->m_pCBSystem->m_pFightInfo->nRoleWillNotBeAttack) )
      v37 = 0;
    memset(pData, 0, sizeof(pData));
    LOBYTE(pData[10]) = 1;
    pData[0] = 267;
    pData[1] = (((CCBSystem *)m_pCBSystem))->CCBSystem::ProcProtect();
    pData[2] = -1;
    pData[3] = -1;
    if ( !v37 )
      pData[2] = (unsigned long)*v4;
    RoleIndex = this->CCBStage::GetRoleIndex(26, pData, 1);
    if ( RoleIndex != -1 )
    {
      p_DWORD[1] = 0;
      p_DWORD[2] = 0;
      p_DWORD[0] = v37;
      this->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessRoleEffect) */, 0, 0, 0, p_DWORD, 0, 1077936128);
      this->CCBStage::GetStageRoleByIdx(RoleIndex);
    }
    if ( !v37 )
    {
      v11 = (_BYTE *)v33;
      v33[41] = 1;
      *((_DWORD *)v11 + 4) = 4;
      *((_DWORD *)v11 + 9) = 0;
      return 0;
    }
    if ( (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
    {
      (((CCBAttackSequen *)this->m_pCBSystem->m_pAttackSequen))->CCBAttackSequen::SetPause(1);
      g_nCBRoleAnimData[16] = -1001914368;
      g_nCBRoleAnimData[17] = 0;
      g_nCBRoleAnimData[18] = -1001914368;
      RoleHP = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleHP(*v4);
      v13 = 0;
      v14 = 0;
      m_pRole = (CCBStage **)this->m_pRole;
      nIndex = 0;
      v36 = 0.0f;
      v35 = (CCBStage **)this->m_pRole;
      do
      {
        m_pRoleState = (CCBRoleState *)this->m_pRoleState;
        if ( m_pRoleState->m_pObjMsgBuffer[v14 + 153] )
        {
          if ( (((CCBRoleState *)m_pRoleState))->CCBRoleState::IsRoleAlive(v13) )
          {
            v17 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleHP(v13);
            if ( v17 == RoleHP )
            {
              (*m_pRole)->m_TaskArrC[0].m_pHead[0] = 0;
              (*m_pRole)->m_TaskSlots[90] = 0;
              (((CCBStage *)*m_pRole))->CCBStage::ClearAniMsg(0, 1.0);
              if ( v13 != *v30 )
              {
                idx = 0;
                v32 = 0;
                do
                {
                  v18 = (CCBSystem *)this->m_pCBSystem;
                  v19 = (tagThread *)&this->m_pCBSystem->m_Thread[v32 / 0x58];
                  qmemcpy(v26, v19, sizeof(v26));
                  if ( v26[36] )
                  {
                    qmemcpy(v25, v19, sizeof(v25));
                    if ( v25[12] == nIndex )
                      (((CCBSystem *)v18))->CCBSystem::ClearEffect(idx);
                  }
                  v20 = (int)(v32 + 88) < 90112;
                  ++idx;
                  v32 += 88;
                }
                while ( v20 );
                m_pControl = (CCBControl *)this->m_pCBSystem->m_pControl;
                if ( m_pControl->m_bActive )
                {
                  Control = (((CCBControl *)m_pControl))->CCBControl::GetControl();
                  v23 = nIndex;
                  if ( Control == nIndex )
                    (((CCBControl *)this->m_pCBSystem->m_pControl))->CCBControl::GetState();
                }
                else
                {
                  v23 = nIndex;
                }
                this->CCBStage::IsTaskFinished(v23);
                m_pRole = (CCBStage **)v35;
                (((CCBStage *)*v35))->CCBStage::GetCurrentTaskIndex();
                (((CCBStage *)*m_pRole))->CCBStage::DelAllTask(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], 1);
                (((CCBSystem *)this->m_pCBSystem->m_pAttackSequen))->CCBSystem::SetCmdParam(v23, 1);
                (((CCBSystem *)this->m_pCBSystem->m_pAttackSequen))->CCBSystem::GetCmdPtr(v23);
              }
              (((CCBStage *)*m_pRole))->CCBStage::ProcTransportRun(pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcTurnToRole), 0, 0, 0, &g_nCBRoleAnimData[16], 0, 2);
              v13 = nIndex;
            }
          }
        }
        ++v13;
        v14 = LODWORD(v36) + 892;
        ++m_pRole;
        v20 = LODWORD(v36) + 892 < 9812;
        nIndex = v13;
        v35 = (CCBStage **)m_pRole;
        LODWORD(v36) += 892;
      }
      while ( v20 );
      v4 = (int *)v30;
      v33[41] = 1;
    }
    v7 = (_BYTE *)v33;
    goto LABEL_39;
  }
  return 0;
}

// 0x005011B0
int CCBStage::TaskMoveToStart(int nVal)
{
  int v3; // eax
  int *v4; // edi
  _BYTE *v5; // ebp

  if ( (g_nCBRoleAnimData[15] & 1) == 0 )
  {
    g_nCBRoleAnimData[12] = 0;
    LOBYTE(g_nCBRoleAnimData[15]) |= 1u;
    g_nCBRoleAnimData[13] = 0;
    g_nCBRoleAnimData[14] = 0;
    atexit(nullsub_24);
  }
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_10;
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    g_nCBRoleAnimData[12] = 1145569280;
    g_nCBRoleAnimData[13] = 0;
    g_nCBRoleAnimData[14] = 1145569280;
    this->m_pRole[*v4]->m_bShowWeapon = 0;
    this->m_pRole[*v4]->m_bFlash = 0;
    (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ClearAniMsg(0, 1.0);
    (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::AnimCallback_MoveTo) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], &g_nCBRoleAnimData[12], 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(*v4)[1].dwMagicID[2][5]) == 1 )
  {
    *((_DWORD *)v5 + 9) = 1;
LABEL_10:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00501330
int CCBStage::TaskBlendToReady(int nVal)
{
  int v3; // ecx
  int v4; // edx
  float *v5; // esi
  float v6; // st7
  float v7; // st7
  float fVal; // [esp+0x0] [ebp-0xC]

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = (float *)&this->m_TaskSlots[8 * v3 + v4];
  if ( !this->m_TaskSlots[8 * v3 + 41 + v4] )
  {
    v6 = (((CCBStage *)this->m_pRole[*(_DWORD *)&this->m_TaskSlots[8 * v3 + 48 + v4]]))->CCBStage::PushBackAllTask();
    v5[16] = v6;
    *((_BYTE *)v5 + 41) = 1;
    if ( v6 < 0.44f )
      goto LABEL_7;
  }
  v7 = (this->m_pCBSystem->m_fTimeFund - v5[6]) / v5[8];
  if ( v7 > 1.0f )
    v7 = 1.0f;
  fVal = (v5[16] - 0.4399999976158142f) * (1.0f - v7) + 0.4399999976158142f;
  (((CCBStage *)this->m_pRole[*((_DWORD *)v5 + 12)]))->CCBStage::ClearAniMsg(1, fVal);
  if ( this->m_pCBSystem->m_fTimeFund - v5[6] > v5[8] )
  {
    (((CCBStage *)this->m_pRole[*((_DWORD *)v5 + 12)]))->CCBStage::ClearAniMsg(1, 0.44);
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00501410
int CCBStage::TaskBlendToEnd(int nVal)
{
  int v3; // ecx
  int v4; // edx
  float *v5; // esi
  double v6; // st7
  double v7; // st7
  float fVal; // [esp+0x0] [ebp-0xC]

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = (float *)&this->m_TaskSlots[8 * v3 + v4];
  if ( !this->m_TaskSlots[8 * v3 + 41 + v4] )
  {
    v6 = (((CCBStage *)this->m_pRole[*(_DWORD *)&this->m_TaskSlots[8 * v3 + 48 + v4]]))->CCBStage::PushBackAllTask();
    v5[16] = v6;
    *((_BYTE *)v5 + 41) = 1;
    if ( v6 >= 0.99000001 )
      goto LABEL_7;
  }
  v7 = (this->m_pCBSystem->m_fTimeFund - v5[6]) / v5[8];
  if ( v7 > 1.0 )
    v7 = 1.0;
  fVal = (1.0f - v5[16]) * v7 + v5[16];
  (((CCBStage *)this->m_pRole[*((_DWORD *)v5 + 12)]))->CCBStage::ClearAniMsg(1, fVal);
  if ( this->m_pCBSystem->m_fTimeFund - v5[6] > v5[8] )
  {
    (((CCBStage *)this->m_pRole[*((_DWORD *)v5 + 12)]))->CCBStage::ClearAniMsg(0, 1.0);
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x005014E0
int CCBStage::TaskEnterGuard(int nVal)
{
  int v3; // eax
  _DWORD *v4; // edi
  _BYTE *v5; // ebp

  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (_DWORD *)(int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_7;
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::CheckPushState) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], 0, 0, 1);
    v5[41] = 1;
  }
  this->CCBStage::ForceDelTask(12);
  this->CCBStage::ForceDelTask(15);
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x005015C0
int CCBStage::SetupCombatAction(int nVal)
{
  int v3; // eax
  int v4; // ecx
  _DWORD *v5; // esi
  CCBStageScene *m_pScene; // eax
  int x_low; // ecx
  int v8; // eax
  int v9; // eax
  void *v10; // ecx
  CCBStageRole *v11; // eax
  int *p_eMode; // eax
  int *v13; // eax
  int v14; // eax
  int v15; // ecx
  float v16; // edx
  int v17; // eax
  int v18; // edx
  int v19; // eax
  void *v20; // ecx
  unsigned int ( *v21)(CCBStage *, int); // ecx
  CCBStageRole *v22; // eax
  CCBStageRole *v23; // eax
  int v24; // eax
  float v25; // st7
  float v26; // st7
  int result; // eax
  CCBStage **v28; // edi
  float m_fCombatAnimY; // st7
  unsigned int ( *v30)(CCBStage *, int); // [esp-0x20] [ebp-0x70]
  const void *v31; // [esp-0x8] [ebp-0x58]
  _BYTE *v32; // [esp+0x10] [ebp-0x40]
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
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = v3 + 80 * this->m_nRoleSlot;
  v5 = (_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 208];
  v32 = (_BYTE *)&this->m_TaskSlots[v4];
  if ( !this->m_TaskSlots[v4 + 41] )
  {
    if ( *(int *)((char *)&this->m_DamageData + v3) == -1 )
    {
      m_pScene = (CCBStageScene *)this->m_pScene;
      x_low = LODWORD(m_pScene->m_vecFiveLineup[v5[1]].x);
      v8 = (int)&m_pScene->m_vecFiveLineup[v5[1]];
      g_nCBRoleAnimData[4] = x_low;
      g_nCBRoleAnimData[5] = *(_DWORD *)(v8 + 4);
      g_nCBRoleAnimData[6] = *(_DWORD *)(v8 + 8);
      v9 = (unsigned long)v5[2];
      if ( v9 == 1 )
        goto LABEL_12;
      if ( v5[2] == 2 )
      {
        (((CCBStage *)this->m_pRole[2]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcMagic) */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
LABEL_14:
        v11 = this->m_pRole[v5[2]];
        *(_DWORD *)&v11->m_Task[62].eMode = g_nCBRoleAnimData[4];
        v11 = (CCBStageRole *)((char *)v11 + 6596);
        v11->m_pRoleState = (CCBRoleState *)g_nCBRoleAnimData[5];
        *(_DWORD *)v11->m_sLastRole = g_nCBRoleAnimData[6];
        v32[41] = 1;
        goto LABEL_36;
      }
      if ( v5[2] == 3 )
LABEL_12:
        *(unsigned int (CCBStage::**)(float))&(v10) = CCBStage::ProcUseRecoverItem;
      else
        *(unsigned int (CCBStage::**)(int))&(v10) = CCBStage::ProcTurnToRole;
      (((CCBStage *)this->m_pRole[v9]))->CCBStage::GetProperCurAction((int)v10, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
      goto LABEL_14;
    }
    p_eMode = (int *)&this->m_pRole[*(int *)((char *)&this->m_nTaskExist + v3)]->m_Task[62].eMode;
    g_nCBRoleAnimData[8] = *p_eMode;
    g_nCBRoleAnimData[9] = p_eMode[1];
    g_nCBRoleAnimData[10] = p_eMode[2];
    v13 = (int *)&this->m_pRole[v5[3]]->m_Task[62].eMode;
    g_nCBRoleAnimData[4] = *v13;
    g_nCBRoleAnimData[5] = v13[1];
    g_nCBRoleAnimData[6] = v13[2];
    v14 = (unsigned long)v5[2];
    if ( !v14 && v5[3] == 4 || v14 == 4 && !v5[3] )
    {
      memset(&v33, 0, sizeof(v33));
      *(float *)&pnVal = *(float *)&g_nCBRoleAnimData[4] + *(float *)&g_nCBRoleAnimData[8];
      v35 = *(float *)&g_nCBRoleAnimData[9] + *(float *)&g_nCBRoleAnimData[5];
      z = *(float *)&g_nCBRoleAnimData[10] + *(float *)&g_nCBRoleAnimData[6];
      v37 = *(float *)&pnVal * 0.5f;
      v38 = v35 * 0.5f;
      v39 = z * 0.5f;
      *(float *)&pnVal = *(float *)&g_nCBRoleAnimData[8] - *(float *)&g_nCBRoleAnimData[4];
      v15 = pnVal;
      *(float *)&pnVal = 0.0;
      LODWORD(v40.x) = v15;
      v35 = *(float *)&g_nCBRoleAnimData[9] - *(float *)&g_nCBRoleAnimData[5];
      v16 = v35;
      v35 = 1.0f;
      v40.y = v16;
      z = *(float *)&g_nCBRoleAnimData[10] - *(float *)&g_nCBRoleAnimData[6];
      v41.x = 0.0f;
      v41.y = 1.0f;
      v40.z = z;
      z = 0.0f;
      v41.z = 0.0f;
      (((gbVec3D *)&v41))->gbVec3D::CrossProduct(&v40, &v33);
      (((gbVec3D *)&v33))->gbVec3D::Normalize();
      v33.x = v33.x * 30.0;
      v33.y = v33.y * 30.0;
      v33.z = v33.z * 30.0;
      z = v33.z;
      *(float *)&pnVal = v33.x + v37;
      v35 = v33.y + v38;
      v17 = (unsigned long)v5[2];
      z = v33.z + v39;
      (((CCBStage *)this->m_pRole[v17]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcTurnToRole) */, 0, 0, 0, 0x7FFFFFFF, &pnVal, v5, 1);
      (((CCBStage *)this->m_pRole[v5[2]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcTurnToRole) */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
      v35 = v33.y * -1.0f;
      z = v33.z * -1.0f;
      *(float *)&pnVal = v37 + v33.x * -1.0;
      v18 = (unsigned long)v5[3];
      v35 = v35 + v38;
      z = z + v39;
      (((CCBStage *)this->m_pRole[v18]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcTurnToRole) */, 0, 0, 0, 0x7FFFFFFF, &pnVal, v5, 1);
      v31 = (void *)v5;
      *(unsigned int (CCBStage::**)(int))&(v30) = CCBStage::ProcTurnToRole;
      v19 = (unsigned long)v5[3];
      goto LABEL_34;
    }
    switch ( v14 )
    {
      case 1:
        goto LABEL_25;
      case 2:
        (((CCBStage *)this->m_pRole[2]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcMagic) */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
        goto LABEL_27;
      case 3:
LABEL_25:
        *(unsigned int (CCBStage::**)(float))&(v20) = CCBStage::ProcUseRecoverItem;
        break;
      default:
        *(unsigned int (CCBStage::**)(int))&(v20) = CCBStage::ProcTurnToRole;
        break;
    }
    (((CCBStage *)this->m_pRole[v14]))->CCBStage::GetProperCurAction((int)v20, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[4], v5, 1);
LABEL_27:
    v19 = (unsigned long)v5[3];
    if ( v19 == 1 )
      goto LABEL_32;
    if ( v5[3] == 2 )
    {
      (((CCBStage *)this->m_pRole[2]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcMagic) */, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[8], v5, 1);
LABEL_35:
      v22 = this->m_pRole[v5[2]];
      *(_DWORD *)&v22->m_Task[62].eMode = g_nCBRoleAnimData[4];
      v22 = (CCBStageRole *)((char *)v22 + 6596);
      v22->m_pRoleState = (CCBRoleState *)g_nCBRoleAnimData[5];
      *(_DWORD *)v22->m_sLastRole = g_nCBRoleAnimData[6];
      v23 = this->m_pRole[v5[3]];
      *(_DWORD *)&v23->m_Task[62].eMode = g_nCBRoleAnimData[8];
      v23 = (CCBStageRole *)((char *)v23 + 6596);
      v23->m_pRoleState = (CCBRoleState *)g_nCBRoleAnimData[9];
      *(_DWORD *)v23->m_sLastRole = g_nCBRoleAnimData[10];
      v32[41] = 1;
      goto LABEL_36;
    }
    if ( v5[3] == 3 )
LABEL_32:
      v21 = (unsigned int ( *)(CCBStage *, int))CCBStage::ProcUseRecoverItem;
    else
      *(unsigned int (CCBStage::**)(int))&(v21) = CCBStage::ProcTurnToRole;
    v31 = (void *)v5;
    v30 = v21;
LABEL_34:
    (((CCBStage *)this->m_pRole[v19]))->CCBStage::GetProperCurAction((int)v30, 0, 0, 0, 0x7FFFFFFF, &g_nCBRoleAnimData[8], v31, 1);
    goto LABEL_35;
  }
LABEL_36:
  if ( v5[3] == -1 )
  {
    v28 = (CCBStage **)&this->m_pRole[v5[2]];
    m_fCombatAnimY = (*v28)->m_fCombatAnimY;
    v41.y = 0.0f;
    v41.x = m_fCombatAnimY;
    v41.z = 0.0f;
    (((CCBStage *)*v28))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, 0x7FFFFFFF, (int *)&v41, v5, 1);
    *((_DWORD *)v32 + 4) = 4;
    return 0;
  }
  else
  {
    v24 = (unsigned long)v5[2];
    v25 = *(float *)&this->m_pRole[v24]->m_Task[63].cmd.dwCmdKind;
    v41.y = 0.0f;
    v41.z = 0.0f;
    v41.x = v25;
    (((CCBStage *)this->m_pRole[v24]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, 0x7FFFFFFF, (int *)&v41, v5, 1);
    v26 = *(float *)&this->m_pRole[v5[2]]->m_Task[63].cmd.dwCmdKind;
    v41.y = 0.0f;
    v41.z = 0.0f;
    v41.x = v26;
    (((CCBStage *)this->m_pRole[v5[3]]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessCommand) */, 0, 0, 0, 0x7FFFFFFF, (int *)&v41, v5, 1);
    result = 0;
    *((_DWORD *)v32 + 4) = 4;
  }
  return result;
}

// 0x00501CF0
int CCBStage::TaskReturnToIdle(int nVal)
{
  int v3; // eax
  int *v4; // edi
  _BYTE *v5; // ebx

  if ( (g_nCBRoleAnimData[3] & 1) == 0 )
  {
    g_nCBRoleAnimData[0] = 0;
    LOBYTE(g_nCBRoleAnimData[3]) |= 1u;
    g_nCBRoleAnimData[1] = 0;
    g_nCBRoleAnimData[2] = 0;
    atexit(nullsub_27);
  }
  v3 = 2632 * this->m_nClearRoleAllTask;
  v4 = (int *)((char *)&this->m_nTaskExist + v3);
  v5 = (_BYTE *)&this->m_TaskSlots[80 * this->m_nRoleSlot + v3];
  if ( !(((CCBStage *)this->m_pRole[*v4]))->CCBStage::IsReady(*(_DWORD *)&this->m_TaskArrC[8]._todo_018[v3 + 200]) )
    goto LABEL_12;
  if ( !v5[41] && (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
  {
    LODWORD(this->m_pRole[*v4]->m_Task[63].vec1.v.z) = (unsigned long)this->m_pRole[*v4]->m_Task[63].cmd.dwCmdKind;
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(*v4, 17)
      && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(*v4, 14) )
    {
      (((CCBStage *)this->m_pRole[*v4]))->CCBStage::GetProperCurAction(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ClearTaskIfMatch) */, 0, 0, 0, *(_DWORD *)&this->m_TaskArrC[8]._todo_018[2632 * this->m_nClearRoleAllTask + 200], g_nCBRoleAnimData, 0, 1);
    }
    v5[41] = 1;
  }
  if ( v5[43] == 1 || (((CCBStage *)this->m_pRole[*v4]))->CCBStage::ForceDelTaskByPFN() )
LABEL_12:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00501E60
int CCBStage::TaskShowLevelUp(int nVal)
{
  int v3; // ecx
  int v4; // edx
  _BYTE *v5; // edi
  UIStatic *v6; // ecx
  CScreenMode *Instance; // eax
  char v9; // al
  UIStatic *v10; // ecx

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[8 * v3 + v4];
  if ( this->m_TaskSlots[8 * v3 + 41 + v4] )
  {
    if ( this->m_TaskSlots[8 * v3 + 43 + v4] == 1
      || this->m_pCBSystem->m_fTimeFund - *(float *)&this->m_TaskSlots[8 * v3 + 24 + v4] > *(float *)&this->m_TaskSlots[8 * v3 + 32 + v4]
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v9) )
    {
      v10 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[4];
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10))((UIStatic *)(v10), (_DWORD)(0));
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    v6 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[4];
    (**(void ( ***)(UIStatic *, int))((UIWnd *)v6))((UIStatic *)(v6), (int)(1));
    (((CCBUI *)this->m_pCBSystem->m_pUI))->CCBUI::CreateResultWindow(0);
    StoreThreadFlag(this->m_pCBSystem->m_pAttackSequen, 0);
    (((C2DSpark *)this->m_pCBSystem->m_p2DSpark))->C2DSpark::CreateStars();
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWa012, 1);
    v5[41] = 1;
    return 0;
  }
}

// 0x00501F30
int CCBStage::TaskShowSkillLearned(int nVal)
{
  int v3; // ecx
  int v4; // edx
  _BYTE *v5; // edi
  UIStatic *v6; // ecx
  CScreenMode *Instance; // eax
  char v9; // al
  UIStatic *v10; // ecx

  v3 = 329 * this->m_nClearRoleAllTask;
  v4 = 80 * this->m_nRoleSlot;
  v5 = (_BYTE *)&this->m_TaskSlots[8 * v3 + v4];
  if ( this->m_TaskSlots[8 * v3 + 41 + v4] )
  {
    if ( this->m_TaskSlots[8 * v3 + 43 + v4] == 1
      || this->m_pCBSystem->m_fTimeFund - *(float *)&this->m_TaskSlots[8 * v3 + 24 + v4] > *(float *)&this->m_TaskSlots[8 * v3 + 32 + v4]
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v9) )
    {
      v10 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[5];
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10))((UIStatic *)(v10), (_DWORD)(0));
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    v6 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[5];
    (**(void ( ***)(UIStatic *, int))((UIWnd *)v6))((UIStatic *)(v6), (int)(1));
    (((CCBUI *)this->m_pCBSystem->m_pUI))->CCBUI::CreateResultWindow(0);
    StoreThreadFlag(this->m_pCBSystem->m_pAttackSequen, 0);
    (((C2DSpark *)this->m_pCBSystem->m_p2DSpark))->C2DSpark::CreateStars();
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWa013, 1);
    v5[41] = 1;
    return 0;
  }
}

// 0x005024D0
int CCBStage::ProcessRoleEffect(int nVal)
{
  CEffectSystem *v3; // ecx
  char *v4; // eax
  int v5; // edi
  CCBUI *m_pUI; // ebp
  UIProgressBar *v8; // ecx
  UIProgressBar *v9; // ecx

  v3 = (CEffectSystem *)(329 * this->m_nClearRoleAllTask);
  v4 = (char *)this + 80 * this->m_nRoleSlot;
  v5 = (int)&v4[8 * (_DWORD)v3 + 184];
  if ( !v4[8 * (_DWORD)v3 + 225] )
  {
    if ( *((_BYTE *)(((CEffectSystem *)v3))->CEffectSystem::DestroyAllEffect() + 5) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    m_pUI = (CCBUI *)this->m_pCBSystem->m_pUI;
    if ( *(_DWORD *)(v5 + 44) == 1 )
      (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aFleesuccess);
    else
      (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aFleefail);
    SetEnable((UICaption *)m_pUI->m_pRoleStateGP[2]);
    v8 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    (**(void ( ***)(UIProgressBar *, int))((UIWnd *)v8))((UIProgressBar *)(v8), (int)(1));
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || this->m_pCBSystem->m_fTimeFund - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || *((_BYTE *)(((CEffectSystem *)v3))->CEffectSystem::DestroyAllEffect() + 5) )
  {
    v9 = (UIProgressBar *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v9))((UIProgressBar *)(v9), (_DWORD)(0));
    *(_DWORD *)(v5 + 16) = 4;
  }
  return 0;
}

// 0x00503680
int CCBStage::CalcSneakAttackVariance()
{
  char v2; // bl
  CCBStageEffect **p_m_pEffect; // ecx
  int *v4; // ebp
  unsigned int v5; // edi
  char v6; // al
  unsigned int v7; // eax
  int v8; // edi
  int i; // ebp
  CCBRoleState *m_pRoleState; // ecx
  int result; // eax
  int *v12; // ecx
  int v13; // eax
  int v14; // ebp
  int v15; // ebx
  int v16; // edi
  int v17; // edi
  int j; // ebp
  CCBRoleState *v19; // ecx
  int v20; // edi
  int k; // ebp
  CCBRoleState *v22; // ecx
  unsigned int v23; // [esp+0x10] [ebp-0xC]
  float v24; // [esp+0x14] [ebp-0x8]
  float v25; // [esp+0x18] [ebp-0x4]
  float v26; // [esp+0x18] [ebp-0x4]
  float v27; // [esp+0x18] [ebp-0x4]
  char v28; // [esp+0x20] [ebp+0x4]
  int v29; // [esp+0x20] [ebp+0x4]
  float Role; // [esp+0x20] [ebp+0x4]
  float v31; // [esp+0x20] [ebp+0x4]
  float v32; // [esp+0x20] [ebp+0x4]
  float v33; // [esp+0x20] [ebp+0x4]
  int *nRoleIndex; // [esp+0x24] [ebp+0x8]
  char nRoleIndexa; // [esp+0x24] [ebp+0x8]

  v2 = v28;
  p_m_pEffect = (CCBStageEffect **)&this->m_pEffect;
  *p_m_pEffect = 0;
  v23 = -1;
  v24 = 1.0f;
  v25 = 1.0f;
  p_m_pEffect[1] = 0;
  *((_WORD *)p_m_pEffect + 4) = 0;
  *((_BYTE *)p_m_pEffect + 10) = 0;
  if ( (v28 & 1) != 0 )
  {
    v4 = (int *)nRoleIndex;
    v29 = v28 & 0x10;
    if ( (v2 & 0x10) != 0 )
    {
      v5 = (((CCBAttackSequen *)this->m_pCBSystem->m_pAttackSequen))->CCBAttackSequen::ProcessAllCmds();
      v23 = v5;
      (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CancelVariance(nRoleIndex, v5);
      if ( !v6 )
      {
        v23 = -1;
        goto LABEL_18;
      }
      if ( v5 != 6 )
      {
        if ( v5 == -1 )
          goto LABEL_18;
        goto LABEL_63;
      }
      if ( *nRoleIndex != 259 )
        goto LABEL_63;
    }
    else
    {
      if ( (v2 & 4) == 0 && (v2 & 8) == 0 )
      {
LABEL_18:
        nRoleIndexa = 1;
        if ( *v4 == 259 && (v29 || (v2 & 4) != 0) && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CalSneakAttack(v4[2], 6u) )
          nRoleIndexa = 0;
        v8 = 0;
        for ( i = 0; i < 9812; i += 892 )
        {
          m_pRoleState = (CCBRoleState *)this->m_pRoleState;
          if ( m_pRoleState->m_pObjMsgBuffer[i + 153]
            && !m_pRoleState->m_info.depend_scenename[i + 26]
            && !HIBYTE((((CCBRoleState *)m_pRoleState))->CCBRoleState::InitUI(v8)[1].dwMagicID[2][4])
            && i >= 4460
            && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v8)
            && (nRoleIndexa || i != 5352) )
          {
            v26 = (float)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v8, 0);
            if ( v26 / (double)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v8, 1) <= v24 )
            {
              v27 = (float)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v8, 0);
              v23 = v8;
              v24 = v27 / (float)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v8, 1);
            }
          }
          ++v8;
        }
        result = v23;
        *((_BYTE *)&this->m_pEffect + v23) = 1;
        return result;
      }
      (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetEnemyBeImbibeNimbus((v2 & 4) != 0, 1);
      v23 = v7;
      if ( (v2 & 4) == 0 || v7 != 6 )
      {
        if ( v7 == -1 )
          goto LABEL_18;
        goto LABEL_63;
      }
      if ( *nRoleIndex != 259 )
        goto LABEL_63;
    }
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CalSneakAttack(nRoleIndex[2], 6u) )
    {
      v23 = -1;
      goto LABEL_18;
    }
LABEL_63:
    result = v23;
    *((_BYTE *)&this->m_pEffect + v23) = 1;
    return result;
  }
  v12 = (int *)nRoleIndex;
  v13 = (unsigned long)*nRoleIndex;
  if ( *nRoleIndex != 262 && v13 != 260 && v13 != 261 )
  {
LABEL_47:
    if ( *v12 != 262
      || !(((PAL_GDB *)this->m_pRoleState))->PAL_GDB::GetSkillType(v12[1])
      || (((PAL_GDB *)this->m_pRoleState))->PAL_GDB::GetSkillLevel(nRoleIndex[1]) )
    {
      goto LABEL_57;
    }
    v17 = 0;
    for ( j = 0; j < 4460; j += 892 )
    {
      v19 = (CCBRoleState *)this->m_pRoleState;
      if ( v19->m_pObjMsgBuffer[j + 153] )
      {
        if ( (((CCBRoleState *)v19))->CCBRoleState::IsRoleAlive(v17) )
        {
          Role = (float)(int)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRole(v17);
          if ( Role / (double)(int)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRole(v17) < v25 )
          {
            v31 = (float)(int)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRole(v17);
            v23 = v17;
            v25 = v31 / (float)(int)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRole(v17);
          }
        }
      }
      ++v17;
    }
    if ( v23 > 0xA )
    {
LABEL_57:
      v20 = 0;
      for ( k = 0; k < 4460; k += 892 )
      {
        v22 = (CCBRoleState *)this->m_pRoleState;
        if ( v22->m_pObjMsgBuffer[k + 153] )
        {
          if ( (((CCBRoleState *)v22))->CCBRoleState::IsRoleAlive(v20) )
          {
            v32 = (float)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v20, 0);
            if ( v32 / (double)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v20, 1) <= v24 )
            {
              v33 = (float)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v20, 0);
              v23 = v20;
              v24 = v33 / (float)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(v20, 1);
            }
          }
        }
        ++v20;
      }
    }
    goto LABEL_63;
  }
  v14 = 0;
  v15 = 0;
  while ( !this->m_pRoleState->m_pObjMsgBuffer[v15 + 153] )
  {
LABEL_45:
    v15 += 892;
    ++v14;
    if ( v15 >= 4460 )
    {
      v12 = (int *)nRoleIndex;
      goto LABEL_47;
    }
  }
  v16 = 1;
  while ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v14, v16)
       || (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsPlayerTeam(v16)
       || !(((PAL_GDB *)this->m_pRoleState))->PAL_GDB::IsRoleSkillValid((unsigned int *)nRoleIndex, v16) )
  {
    if ( ++v16 >= 27 )
      goto LABEL_45;
  }
  result = v14;
  *((_BYTE *)&this->m_pEffect + v14) = 1;
  return result;
}

// 0x00503CF0
int CCBStage::UpdatePhysics()
{
  int result; // eax
  tagPOINT *p_m_ptMousePos; // ecx
  int v3; // edx
  double v4; // st7
  __int16 v5; // fps
  double v6; // st6
  bool v7; // c0
  char v8; // c2
  bool v9; // c3

  result = (int)this->m_pCBSystem;
  p_m_ptMousePos = (tagPOINT *)&this->m_ptMousePos;
  v3 = 11;
  v4 = *(double *)(result + 64) * 30.0;
  do
  {
    if ( *(float *)&p_m_ptMousePos->x > 0.0f )
    {
      if ( *(float *)&p_m_ptMousePos->x <= 160.0f )
        *(float *)&p_m_ptMousePos->x = *(float *)&p_m_ptMousePos->x - v4;
      else
        p_m_ptMousePos->x = 1126170624;
    }
    v6 = *(float *)&p_m_ptMousePos->x;
    v7 = v6 < 0.0;
    v8 = 0;
    v9 = v6 == 0.0;
    LOWORD(result) = v5;
    if ( v6 < 0.0 )
      p_m_ptMousePos->x = 0;
    p_m_ptMousePos = (tagPOINT *)((char *)p_m_ptMousePos + 4);
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x00503FA0
int CCBStage::ResetTurnData(int **a2, gbGfxManager *p)
{
  _DWORD *v4; // eax
  int v5; // edx
  int *p_m_TurnBuffer; // eax
  int v7; // edx
  int result; // eax

  ((Camera *)this)->Camera::Camera(p);
  v4 = (_DWORD *)&this->m_TaskArrC[1]._todo_018[40];
  v5 = 50;
  do
  {
    *(v4 - 2) = 0;
    *(v4 - 1) = 0;
    *v4 = 0;
    v4[1] = 0;
    v4[2] = 0;
    v4[3] = 0;
    v4[4] = 0;
    v4[5] = 0;
    v4[6] = 0;
    v4[7] = 0;
    v4[8] = 0;
    v4[9] = 0;
    v4 += 20;
    --v5;
  }
  while ( v5 );
  p_m_TurnBuffer = (int *)&this->m_TurnBuffer;
  v7 = 64;
  do
  {
    *p_m_TurnBuffer = 0;
    p_m_TurnBuffer[1] = 0;
    p_m_TurnBuffer[2] = 0;
    p_m_TurnBuffer[3] = 0;
    p_m_TurnBuffer[4] = 0;
    p_m_TurnBuffer[5] = 0;
    p_m_TurnBuffer += 6;
    --v7;
  }
  while ( v7 );
  this->CCBStage::ResetTurnSystem();
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[240] = (unsigned long)a2;
  result = (int)this;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[244] = **a2;
  return result;
}

// 0x005040D0
int CCBStage::ResetTurnSystem()
{
  int result; // eax

  result = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[240] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[244] = 0;
  memset(&this->m_TurnBuffer, 0, 0x600u);
  *(_DWORD *)this->m_TaskArrC[1].m_pHead = 0;
  this->m_TaskArrC[1].m_nState = -1;
  this->m_TaskArrC[1].m_fSlot0 = 0.0f;
  this->m_TaskArrC[1].m_fSlot3 = 0.0f;
  this->m_TaskArrC[1].m_fSlot1 = 0.0f;
  this->m_TaskArrC[1].m_fSlot2 = NAN;
  memset(this->m_TaskArrC[1]._todo_018, 0, 0xFA0u);
  return result;
}

// 0x00504240
int CCBStage::LoadFullConfig()
{
  int v2; // edi
  float *i; // ebx
  float *v5; // ebx
  float *v6; // esi
  int v7; // [esp+0x20] [ebp-0x2C]
  int v8; // [esp+0x24] [ebp-0x28]
  int v9; // [esp+0x28] [ebp-0x24]
  int v10; // [esp+0x2C] [ebp-0x20]
  int v11; // [esp+0x30] [ebp-0x1C]
  int v12; // [esp+0x34] [ebp-0x18]
  CIniFile v13; // [esp+0x38] [ebp-0x14] BYREF
  int v14; // [esp+0x48] [ebp-0x4]

  v2 = 0;
  v14 = 0;
  if ( (g_dwGameFlags & 2) == 0 )
    (((CIniFile *)&v13))->CIniFile::OpenFileWrite("datascript\\cbCam.ini");
  v7 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[188];
  v8 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[192];
  v9 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[196];
  v10 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[152];
  v11 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[148];
  v12 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[160];
  for ( i = (float *)&this->m_TurnBuffer; this->CCBStage::HasTurnChanged(i); i += 6 )
  {
    if ( ++v2 >= 64 )
    {
      v14 = -1;
      (((CIniFile *)&v13))->CIniFile::~CIniFile();
      return -1;
    }
  }
  v5 = (float *)(&this->m_TurnBuffer + 6 * v2);
  v6 = (float *)((char *)this + 24 * v2);
  *(_DWORD *)v5 = v7;
  *((_DWORD *)v6 + 1147) = v8;
  *((_DWORD *)v6 + 1148) = v9;
  *((_DWORD *)v6 + 1149) = v10;
  *((_DWORD *)v6 + 1150) = v11;
  *((_DWORD *)v6 + 1151) = v12;
  if ( (g_dwGameFlags & 2) == 0 )
  {
    sprintf(byte_17AAEE4, "EditorCam%d", v2);
    (((CIniFile *)&v13))->CIniFile::WriteSection(byte_17AAEE4);
    (((CIniFile *)&v13))->CIniFile::WriteLine("x", *v5);
    (((CIniFile *)&v13))->CIniFile::WriteLine(aY_0, v6[1147]);
    (((CIniFile *)&v13))->CIniFile::WriteLine(aZ, v6[1148]);
    (((CIniFile *)&v13))->CIniFile::WriteLine(off_5DB9B0, v6[1149]);
    (((CIniFile *)&v13))->CIniFile::WriteLine(aPitch, v6[1150]);
    (((CIniFile *)&v13))->CIniFile::WriteLine(aRoll, v6[1151]);
  }
  v14 = -1;
  (((CIniFile *)&v13))->CIniFile::~CIniFile();
  return v2;
}

// 0x00504420
int CCBStage::ClearTurnSlot(int nVal)
{
  int result; // eax

  result = 0;
  memset(&this->m_TurnBuffer + 6 * nVal, 0, 0x18u);
  return result;
}

// 0x00504440
bool CCBStage::GetTurnSlotData(int nVal)
{
  return this->CCBStage::HasTurnChanged((float *)&this->m_TurnBuffer + 6 * nVal);
}

// 0x00504460
bool CCBStage::HasTurnChanged(float *pfVal)
{
  return *pfVal != pfVal[1]
      || *pfVal != pfVal[2]
      || *pfVal != pfVal[3]
      || *pfVal != pfVal[4]
      || *pfVal != pfVal[5]
      || *pfVal != 0.0f;
}

// 0x005045B0
char CCBStage::ProcessTurn()
{
  double x; // st7
  double y; // st6
  double v4; // st6
  int v5; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st6
  double v9; // st6
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  float v15; // [esp+0x2C] [ebp-0x44]
  float v16; // [esp+0x2C] [ebp-0x44]
  float v17; // [esp+0x30] [ebp-0x40]
  float v18; // [esp+0x30] [ebp-0x40]
  float v19; // [esp+0x34] [ebp-0x3C]
  float v20; // [esp+0x34] [ebp-0x3C]
  struct tagPOINT Point; // [esp+0x38] [ebp-0x38] BYREF
  struct gbVec3D v22; // [esp+0x40] [ebp-0x30] BYREF
  gbVec3D v23; // [esp+0x4C] [ebp-0x24] BYREF
  float v24; // [esp+0x58] [ebp-0x18]
  float v25; // [esp+0x60] [ebp-0x10]
  gbVec3D v26; // [esp+0x64] [ebp-0xC] BYREF

  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[144] = 0;
  this->CCBStage::GetNextActiveTask();
  this->CCBStage::ScanTurnSlots();
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&Point);
  if ( (((GRPinput *)&g_Input))->GRPinput::GetKeyState(0x100u) || (((GRPinput *)&g_Input))->GRPinput::GetKeyState(0x101u) )
  {
    x = (double)Point.x;
    v15 = x - *(float *)&this->m_TaskArrC[0]._todo_018[248];
    y = (double)Point.y;
    v19 = y;
    v4 = y - *(float *)&this->m_TaskArrC[0]._todo_018[252];
    *(float *)&this->m_TaskArrC[0]._todo_018[252] = v19;
    v17 = v4;
    *(float *)&this->m_TaskArrC[0]._todo_018[248] = x;
  }
  else
  {
    v17 = 0.0f;
    v15 = 0.0f;
    *(float *)&this->m_TaskArrC[0]._todo_018[248] = (float)Point.x;
    *(float *)&this->m_TaskArrC[0]._todo_018[252] = (float)Point.y;
  }
  if ( !*(_BYTE *)(**(_DWORD **)&this->m_TaskArrC[0]._todo_018[240] + 134) )
  {
    if ( (((GRPinput *)&g_Input))->GRPinput::GetKeyState(0x100u) )
    {
      v5 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[240];
      if ( *(_DWORD *)(v5 + 88) == -1 && !*(_BYTE *)(*(_DWORD *)(v5 + 20) + 964) )
      {
        v23 = *(gbVec3D *)&this->m_TaskArrC[0]._todo_018[200];
        (((gbVec3D *)&v23))->gbVec3D::Normalize();
        v26 = *(gbVec3D *)&this->m_TaskArrC[0]._todo_018[212];
        (((gbVec3D *)&v26))->gbVec3D::Normalize();
        memset(&v22, 0, sizeof(v22));
        (((gbVec3D *)&v26))->gbVec3D::CrossProduct(&v23, &v22);
        (((gbVec3D *)&v22))->gbVec3D::Normalize();
        v6 = v17 + v17;
        if ( (g_Input.KeyInfo[31].Data & 0xF) == 1 )
        {
          v23.x = 0.0f;
          v23.y = v6;
          v7 = (float)0.0;
          v23.z = 0.0f;
          v8 = v15 + v15;
          v22.x = v22.x * v8;
        }
        else
        {
          v23.y = 0.0f;
          v23.x = v6 * v23.x;
          v7 = v6 * v23.z;
          v23.z = v7;
          v8 = v15 + v15;
          v22.x = v8 * v22.x;
        }
        v22.z = v22.z * v8;
        v9 = v7;
        v10 = v23.y;
        v25 = v9;
        v22.y = 0.0;
        v24 = v22.x + v23.x;
        v25 = v25 + v22.z;
        *(float *)&this->m_TaskArrC[0]._todo_018[176] = v24 + *(float *)&this->m_TaskArrC[0]._todo_018[176];
        *(float *)&this->m_TaskArrC[0]._todo_018[180] = v10 + *(float *)&this->m_TaskArrC[0]._todo_018[180];
        *(float *)&this->m_TaskArrC[0]._todo_018[184] = v25 + *(float *)&this->m_TaskArrC[0]._todo_018[184];
        (((InputSystem *)this))->InputSystem::ProcessKeyboard(1);
        (((InputSystem *)this))->InputSystem::ProcessKeyboard(0);
      }
    }
    v11 = (double)*(int *)&g_Input.MouseState[8] * 0.25;
    if ( (g_Input.KeyInfo[31].Data & 0xF) == 1 )
    {
      *(float *)&this->m_TaskArrC[0]._todo_018[160] = v11 * 0.001 + *(float *)&this->m_TaskArrC[0]._todo_018[160];
      (((InputSystem *)this))->InputSystem::ProcessKeyboard(0);
    }
    else if ( (g_Input.KeyInfo[32].Data & 0xF) == 1 )
    {
      v12 = v11 * 0.001 + *(float *)&this->m_pRoleState;
      this->m_pEditor = ((CCBEditor *)0);
      *(float *)&this->m_pRoleState = v12;
    }
    else
    {
      *(float *)&this->m_TaskArrC[0]._todo_018[164] = v11 + *(float *)&this->m_TaskArrC[0]._todo_018[164];
      (((InputSystem *)this))->InputSystem::ProcessKeyboard(1);
    }
    if ( (((GRPinput *)&g_Input))->GRPinput::GetKeyState(0x101u)
      && !*(_BYTE *)(*(_DWORD *)(*(_DWORD *)&this->m_TaskArrC[0]._todo_018[240] + 20) + 964) )
    {
      v13 = v15 * 0.0043633231 + *(float *)&this->m_TaskArrC[0]._todo_018[152];
      *(float *)&this->m_TaskArrC[0]._todo_018[152] = v13;
      *(float *)&this->m_TaskArrC[0]._todo_018[148] = *(float *)&this->m_TaskArrC[0]._todo_018[148] - v17 * 0.0043633231;
      if ( v13 <= 3.1415927 )
      {
        if ( v13 <= -3.1415927 )
          v13 = v13 + 6.2831855;
      }
      else
      {
        v13 = v13 - 6.2831855;
      }
      *(float *)&this->m_TaskArrC[0]._todo_018[152] = v13;
      (((InputSystem *)this))->InputSystem::ProcessKeyboard(0);
    }
  }
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[164] = 1120403456;
  (((InputSystem *)this))->InputSystem::ProcessKeyboard(0);
  (((CameraCtrl *)this))->CameraCtrl::SetAsCurrent(3);
  v16 = *(float *)&this->m_TaskArrC[0]._todo_018[152];
  v18 = *(float *)&this->m_TaskArrC[0]._todo_018[148];
  v20 = *(float *)&this->m_TaskArrC[0]._todo_018[160];
  (((Combat *)*(Combat **)(*(_DWORD *)&this->m_TaskArrC[0]._todo_018[240] + 68)))->Combat::LogMessage((char *)5, 135, "Cam x=%f, y=%f, z=%f", *(float *)&this->m_TaskArrC[0]._todo_018[188], *(float *)&this->m_TaskArrC[0]._todo_018[192], *(float *)&this->m_TaskArrC[0]._todo_018[196]);
  (((Combat *)*(Combat **)(*(_DWORD *)&this->m_TaskArrC[0]._todo_018[240] + 68)))->Combat::LogMessage((char *)5, 150, "Cam yaw=%f, pitch=%f, roll=%f", v16, v18, v20);
  return (((Combat *)*(Combat **)(*(_DWORD *)&this->m_TaskArrC[0]._todo_018[240] + 68)))->Combat::LogMessage((char *)5, 165, "Cam fov=%f", *(float *)&this->m_pRoleState);
}

// 0x005049F0
int * CCBStage::GetNextActiveTask()
{
  int *result; // eax
  int v2; // ecx
  int *v3; // ebx
  _BYTE *v4; // edx

  result = (int *)this;
  v2 = 0;
  v3 = (int *)(result + 140);
  result[140] = 0;
  result[145] = -1;
  result[141] = 0;
  v4 = (char *)result + 606;
  result[142] = 0;
  result[143] = -1;
  while ( *(v4 - 2) )
  {
    if ( !*v4 )
    {
      result[145] = v2;
      *v3 = result[20 * v2 + 146];
      result[141] = (unsigned long)result[20 * v2 + 147];
      result[142] = (unsigned long)result[20 * v2 + 148];
      result[143] = (unsigned long)result[20 * v2 + 149];
      return (int *)((int ( *)(char *, _DWORD))*v3)((char *)result + result[141], 0);
    }
    ++v2;
    v4 += 80;
    if ( v2 >= 50 )
      return result;
  }
  return result;
}

// 0x00504A80
char CCBStage::ScanTurnSlots()
{
  int v1; // edx
  _BYTE *v2; // eax

  v1 = 0;
  v2 = (_BYTE *)&this->m_TaskArrC[1]._todo_018[22];
  while ( *(v2 - 2) != 1 || *v2 != 1 )
  {
    ++v1;
    v2 += 80;
    if ( v1 >= 50 )
      return (char)v2;
  }
  LOBYTE(v2) = this->CCBStage::ClearActionSlot(v1);
  return (char)v2;
}

// 0x00504AB0
char CCBStage::ClearActionSlot(int nVal)
{
  int v2; // ebx
  _BYTE *v4; // eax

  v2 = nVal;
  if ( nVal == 49 )
  {
    memset(&this->m_nTodo_1198, 0, 0x50u);
    --LODWORD(this->m_TaskArrC[1].m_fSlot3);
    return 1;
  }
  else
  {
    if ( nVal < SLODWORD(this->m_TaskArrC[1].m_fSlot3) )
    {
      v4 = (_BYTE *)&this->m_TaskArrC[1]._todo_018[80 * nVal];
      do
      {
        ++v2;
        qmemcpy(v4, v4 + 80, 0x50u);
        v4 += 80;
      }
      while ( v2 < SLODWORD(this->m_TaskArrC[1].m_fSlot3) );
    }
    memset(&this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3)--], 0, 0x50u);
    return 1;
  }
}

// 0x00504B50
char CCBStage::EnqueueCommand(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        float fVal,
        const void *pData,
        const void *pData2)
{
  float m_fSlot3; // ecx
  int *v12; // edx

  m_fSlot3 = this->m_TaskArrC[1].m_fSlot3;
  if ( SLODWORD(m_fSlot3) >= 49 )
    return 0;
  this->m_TaskArrC[1]._todo_018[80 * LODWORD(m_fSlot3) + 21] = 0;
  this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3) + 22] = 0;
  this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3) + 20] = 1;
  *(float *)&this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3) + 28] = fVal;
  *(_DWORD *)&this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3) + 16] = nVal5;
  qmemcpy(&this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3) + 32], pData, 0x18u);
  qmemcpy(&this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3) + 56], pData2, 0x18u);
  v12 = (int *)&this->m_TaskArrC[1]._todo_018[80 * LODWORD(this->m_TaskArrC[1].m_fSlot3)];
  *v12 = nVal;
  v12[1] = nVal2;
  v12[2] = nVal3;
  v12[3] = nVal4;
  ++LODWORD(this->m_TaskArrC[1].m_fSlot3);
  return 1;
}

// 0x00504C50
int CCBStage::ProcessQueuedCommand(int nVal)
{
  int v3; // eax
  _BYTE *v4; // esi
  float v6; // [esp+0x0] [ebp-0x28]
  float v7; // [esp+0x4] [ebp-0x24]
  float v8; // [esp+0x8] [ebp-0x20]
  float v9; // [esp+0xC] [ebp-0x1C]
  float v10; // [esp+0x10] [ebp-0x18]
  float v11; // [esp+0x14] [ebp-0x14]
  float v12; // [esp+0x24] [ebp-0x4]

  v3 = 80 * this->m_TaskArrC[1].m_nState;
  v4 = (_BYTE *)&this->m_TaskArrC[1]._todo_018[v3];
  if ( !this->m_TaskArrC[1]._todo_018[v3 + 21] )
  {
    *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 24] = *(float *)(**(_DWORD **)&this->m_TaskArrC[0]._todo_018[240] + 80);
    this->m_TaskArrC[1]._todo_018[v3 + 21] = 1;
  }
  if ( *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 28] == 0.0f )
    v12 = 1.0f;
  else
    v12 = (*(float *)(**(_DWORD **)&this->m_TaskArrC[0]._todo_018[240] + 80)
         - *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 24])
        / *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 28];
  v11 = (*(float *)&this->m_TaskArrC[1]._todo_018[v3 + 64] - *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 40]) * v12
      + *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 40];
  v10 = (*(float *)&this->m_TaskArrC[1]._todo_018[v3 + 60] - *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 36]) * v12
      + *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 36];
  v9 = (*(float *)&this->m_TaskArrC[1]._todo_018[v3 + 56] - *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 32]) * v12
     + *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 32];
  v8 = (*(float *)&this->m_TaskArrC[1]._todo_018[v3 + 76] - *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 52]) * v12
     + *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 52];
  v7 = (*(float *)&this->m_TaskArrC[1]._todo_018[v3 + 72] - *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 48]) * v12
     + *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 48];
  v6 = (*(float *)&this->m_TaskArrC[1]._todo_018[v3 + 68] - *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 44]) * v12
     + *(float *)&this->m_TaskArrC[1]._todo_018[v3 + 44];
  ProcessKeyboard(LODWORD(v6), LODWORD(v7), LODWORD(v8), LODWORD(v9), LODWORD(v10), LODWORD(v11));
  (((CameraCtrl *)this))->CameraCtrl::SetAsCurrent(3);
  if ( v12 >= 1.0f )
  {
    (((CCCTData *)this))->CCCTData::UpdateCamera((int)(v4 + 56));
    v4[22] = 1;
  }
  return 0;
}

// 0x00504E30
int CCBStage::ResetAllData()
{
  int result; // eax

  memset(this, 0, 0x639C0u);
  memset(this->m_EditDescBuf, 0, sizeof(this->m_EditDescBuf));
  result = -1;
  memset(&this->m_nTodo_64190, 0xFFu, 0x4E20u);
  return result;
}

// 0x00508930
void CCBStage::_CCBStageRole(int nVal, int nVal2, int *p_DWORD)
{
  int v5; // edx
  char *v6; // esi
  CCBEditor *m_pEditor; // ecx
  int v8; // eax
  int v9; // edi
  int v10; // edi
  bool IsRoleAlive2; // al
  bool v12; // cc
  int v13; // edx
  float v14; // st7
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

  v5 = *(_DWORD *)&this->m_TaskArrC[7]._todo_018[60 * nVal + 180];
  v6 = (char *)this + 60 * nVal;
  if ( v5 != p_DWORD[1] )
    v5 = (unsigned long)p_DWORD[1];
  m_pEditor = (CCBEditor *)this->m_pEditor;
  v29 = 0.0f;
  nVal3 = 0;
  nVal4 = 0;
  v34 = *(float *)(LODWORD(m_pEditor->m_NewItem[0].fMP) + 900);
  v35 = *(_DWORD *)(LODWORD(m_pEditor->m_NewItem[0].fMP) + 904);
  v36 = *(_DWORD *)(LODWORD(m_pEditor->m_NewItem[0].fMP) + 908);
  v37 = *((float *)m_pEditor->m_NewItem[3].fnGP + 1649);
  v38 = *((_DWORD *)m_pEditor->m_NewItem[3].fnGP + 1650);
  v39 = *((_DWORD *)m_pEditor->m_NewItem[3].fnGP + 1651);
  v8 = (unsigned long)p_DWORD[2];
  if ( (unsigned int)v8 > 4 )
  {
    v40 = *((float *)m_pEditor->m_NewItem[3].fnGP + 1649);
    v41 = *((_DWORD *)m_pEditor->m_NewItem[3].fnGP + 1650);
    v9 = *((_DWORD *)m_pEditor->m_NewItem[3].fnGP + 1651);
  }
  else
  {
    v40 = *(float *)(LODWORD(m_pEditor->m_NewItem[0].fMP) + 900);
    v41 = *(_DWORD *)(LODWORD(m_pEditor->m_NewItem[0].fMP) + 904);
    v9 = *(_DWORD *)(LODWORD(m_pEditor->m_NewItem[0].fMP) + 908);
  }
  v42 = v9;
  v10 = (unsigned long)p_DWORD[3];
  if ( v10 == -1 )
  {
    switch ( *p_DWORD )
    {
      case 260:
      case 269:
        IsRoleAlive2 = (((PAL_GDB *)m_pEditor->m_fpThis->m_NewItem[0].fnGP))->PAL_GDB::IsRoleAlive2(v5);
        goto LABEL_12;
      case 261:
        IsRoleAlive2 = (((PAL_GDB *)m_pEditor->m_fpThis->m_NewItem[0].fnGP))->PAL_GDB::IsItemEquipment(v5);
        goto LABEL_12;
      case 262:
        IsRoleAlive2 = (((PAL_GDB *)m_pEditor->m_fpThis->m_NewItem[0].fnGP))->PAL_GDB::IsSkillEmpty(v5);
        goto LABEL_12;
      case 270:
        IsRoleAlive2 = (((PAL_GDB *)m_pEditor->m_fpThis->m_NewItem[0].fnGP))->PAL_GDB::IsItemConsumed(v5);
LABEL_12:
        if ( IsRoleAlive2 )
          goto LABEL_13;
        v8 = (unsigned long)p_DWORD[2];
        if ( v8 < 0 )
          goto LABEL_21;
        v12 = v8 < 5;
        break;
      default:
LABEL_13:
        v8 = (unsigned long)p_DWORD[2];
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
        v16 = (float *)*(&this->m_pEditor->m_NewItem[1].dwItemID + v8);
        v17 = v16[1649];
        v16 += 1649;
        v29 = v17;
        nVal3 = *((_DWORD *)v16 + 1);
        nVal4 = *((_DWORD *)v16 + 2);
      }
      v18 = v6[2455];
      if ( v18 )
      {
        v19 = (unsigned long)p_DWORD[3];
        if ( v19 == -1 )
        {
          v29 = v14;
          nVal3 = v32;
          nVal4 = v33;
        }
        else
        {
          v20 = (float *)*(&this->m_pEditor->m_NewItem[1].dwItemID + v19);
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
        (((CEffect *)this->m_pEditor->m_fpThis->m_NewItem[2].fnGP))->CEffect::Render(*((_DWORD *)v6 + 612));
      if ( *p_DWORD == 270 )
        (((CEffect *)this->m_pEditor->m_fpThis->m_NewItem[2].fnHP))->CEffect::Render(*((_DWORD *)v6 + 612));
      if ( *p_DWORD == 269 )
        (((CEffMgr *)this->m_pEditor->m_fpThis->m_NewItem[2].fnGP))->CEffMgr::Init(*((_DWORD *)v6 + 612), SLODWORD(v29), nVal3, nVal4, 0);
      else
        (((CEffMgr *)this->m_pEditor->m_fpThis->m_NewItem[2].fnHP))->CEffMgr::Init(*((_DWORD *)v6 + 612), SLODWORD(v29), nVal3, nVal4, 0);
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
      v23 = (float *)*(&this->m_pEditor->m_NewItem[1].dwItemID + v8);
      v24 = v23[1649];
      v23 += 1649;
      v29 = v24;
      nVal3 = *((_DWORD *)v23 + 1);
      nVal4 = *((_DWORD *)v23 + 2);
    }
    v25 = v6[2483];
    if ( v25 )
    {
      v26 = (unsigned long)p_DWORD[3];
      if ( v26 == -1 )
      {
        v29 = v14;
        nVal3 = v32;
        nVal4 = v33;
      }
      else
      {
        v27 = (float *)*(&this->m_pEditor->m_NewItem[1].dwItemID + v26);
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
      (((CEffect *)this->m_pEditor->m_fpThis->m_NewItem[2].fnGP))->CEffect::Render(*((_DWORD *)v6 + 619));
    if ( *p_DWORD == 270 )
      (((CEffect *)this->m_pEditor->m_fpThis->m_NewItem[2].fnHP))->CEffect::Render(*((_DWORD *)v6 + 619));
    if ( *p_DWORD == 269 )
      (((CEffMgr *)this->m_pEditor->m_fpThis->m_NewItem[2].fnGP))->CEffMgr::Init(*((_DWORD *)v6 + 619), SLODWORD(v29), nVal3, nVal4, 0);
    else
      (((CEffMgr *)this->m_pEditor->m_fpThis->m_NewItem[2].fnHP))->CEffMgr::Init(*((_DWORD *)v6 + 619), SLODWORD(v29), nVal3, nVal4, 0);
  }
}

// 0x005090F0
void CCBStage::Proceed()
{
  g_StageRoleData.m_nEffParam1C = 519;
  g_StageRoleData.m_nEffTypeID = 519;
  g_StageRoleData.m_nEffParam24 = 519;
  g_StageRoleData.m_nEffTypeCode = 519;
}

// 0x00509130
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBStage::SetAlive(bool bAlive)
{
  this->CCBStage::SetMaxBlend();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00509140
void CCBStage::SetMaxBlend()
{
  g_StageRoleData.m_nEffParam2C = 128;
  g_StageRoleData.m_nEffParam30 = 323;
  g_StageRoleData.m_nEffParam34 = 519;
  g_StageRoleData.m_nEffParam38 = 716;
}

// 0x00509180
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBStage::SetVisible()
{
  this->CCBStage::SetPause();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00509190
void CCBStage::SetPause()
{
  g_StageRoleData.m_nEffParam3C = 545;
  g_StageRoleData.m_nEffParam40 = 545;
  g_StageRoleData.m_nEffParam44 = 545;
  g_StageRoleData.m_nEffParam48 = 545;
}

// 0x005091D0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBStage::OnChangeAction()
{
  this->CCBStage::CheckAction();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005091E0
int CCBStage::CheckAction()
{
  int result; // eax

  g_StageRoleData.m_nEffParam4C = 121;
  result = 709;
  g_StageRoleData.m_nEffParam50 = 316;
  g_StageRoleData.m_nEffParam2 = 512;
  g_StageRoleData.m_nEffParam58 = 709;
  return result;
}

// 0x00509220
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBStage::OnPlayAction()
{
  compiler_init_00509230();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00509270
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
bool CCBStage::IsUnderMouse()
{
  return this->CCBStage::IsCollideRay();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00509280
bool CCBStage::IsCollideRay()
{
  bool result; // al

  result = 12;
  dword_17AB9DC = 12;
  return result;
}

// 0x00509290
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBStage::GetRoleRadius()
{
  this->CCBStage::GetRoleHeight();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005092A0
int CCBStage::GetRoleHeight()
{
  int result; // eax

  result = 508;
  dword_17AB9D8 = 508;
  return result;
}

// 0x005092B0
CCBStage * CCBStage::GetOBBox(int nVal)
{
  gbVec3D *v3; // ebp
  gbVec3D *v4; // edi
  CCBRoleState *v5; // ecx
  int v7; // [esp+0x10] [ebp-0x4]

  ((gbMatrix4 *)&this->m_TaskArrC[0].m_fSlot3)->gbMatrix4::gbMatrix4();
  v3 = (gbVec3D *)&this->m_TaskArrC[0]._todo_018[140];
  v7 = 64;
  do
  {
    v3 - 1->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
    v4 = (gbVec3D *)v3;
    v3 += 8;
    memset(v4, 0, 0x2Cu);
    --v7;
  }
  while ( v7 );
  *(&this->m_nAllDone + 1) = 0;
  *(&this->m_nAllDone + 2) = 0;
  *(&this->m_nAllDone + 3) = 0;
  this->m_fCurPosX = 0.0f;
  this->m_fCurPosY = 0.0f;
  this->m_fCurPosZ = 0.0f;
  *((_DWORD *)&this->m_fCurPosZ + 1) = 0;
  *((_DWORD *)&this->m_fCurPosZ + 2) = 0;
  *((_DWORD *)&this->m_fCurPosZ + 3) = 0;
  this->m_fTargetPosX = 0.0f;
  this->m_fTargetPosY = 0.0f;
  this->m_fTargetPosZ = 0.0f;
  this->m_fVelX = 0.0f;
  this->m_fVelY = 0.0f;
  this->m_fVelZ = 0.0f;
  memset(this, 0, 0x1A18u);
  this->m_pCBSystem = ((CCBSystem *)((CCBSystem *)nVal));
  v5 = (CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)nVal + 16);
  *((_DWORD *)&this->m_fCombatAnimY + 1) = 0;
  this->m_pRoleState = ((CCBRoleState *)(v5));
  this->m_nBattleResult = gbCrc32Compute("over");
  this->m_nActionFilterA = gbCrc32Compute(aWork);
  this->m_nActionFilterB = gbCrc32Compute(aWork1);
  *(&this->m_nActionFilterB + 1) = gbCrc32Compute(aPause);
  *(&this->m_nActionFilterB + 2) = gbCrc32Compute(aStore);
  this->m_nDoneCount = gbCrc32Compute(aFlyup);
  this->m_nTotalCount = gbCrc32Compute(aFlydown);
  *(&this->m_nTotalCount + 1) = 0;
  strcpy((char *)&this->m_pEditor, "???");
  return this;
}

// 0x00509410
int CCBStage::GetRotAngle()
{
  int result; // eax
  _BYTE *v3; // ebp
  int *v4; // ecx

  result = 0;
  v3 = (_BYTE *)&this->m_TaskArrC[0]._todo_018[96];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[100] = 0;
  v4 = (int *)(&this->m_nAllDone + 1);
  this->m_TaskSlots[80] = 0;
  this->m_TaskSlots[81] = 0;
  *((_DWORD *)v3 + 2) = 0;
  this->m_TaskSlots[82] = 0;
  this->m_TaskSlots[83] = 0;
  *(_DWORD *)&this->m_TaskSlots[84] = 1065353216;
  this->m_TaskSlots[88] = 0;
  this->m_TaskSlots[89] = 0;
  this->m_TaskArrC[0].m_pHead[0] = 0;
  this->m_TaskSlots[90] = 0;
  this->m_TaskArrC[0]._todo_018[76] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[80] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[84] = 0;
  this->m_TaskArrC[0].m_fSlot0 = 0.0f;
  this->m_fAngleDegrees = 0.0f;
  this->m_fCombatAnimY = 0.0f;
  *(_DWORD *)&this->m_TaskArrA[1324] = 2;
  this->m_nAllDone = 32;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] = -1;
  *((_DWORD *)v3 + 3) = -1;
  this->m_TaskArrC[0]._todo_018[69] = 0;
  this->m_TaskArrC[0]._todo_018[70] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[72] = 0;
  *(_DWORD *)&this->m_TaskArrA[1320] = 1;
  *v4 = 0;
  v4[1] = 0;
  v4[2] = 0;
  this->m_fCurPosX = 0.0f;
  this->m_fCurPosY = 0.0f;
  this->m_fCurPosZ = 0.0f;
  *((_DWORD *)&this->m_fCurPosZ + 1) = 0;
  *((_DWORD *)&this->m_fCurPosZ + 2) = 0;
  *((_DWORD *)&this->m_fCurPosZ + 3) = 0;
  this->m_fTargetPosX = 0.0f;
  this->m_fTargetPosY = 0.0f;
  this->m_fTargetPosZ = 0.0f;
  this->m_fVelX = 0.0f;
  this->m_fVelY = 0.0f;
  this->m_fVelZ = 0.0f;
  memset(&this->m_TaskArrC[0]._todo_018[112], 0, 0x1800u);
  *((_DWORD *)&this->m_fCombatAnimY + 1) = 0;
  return result;
}

// 0x00509540
bool CCBStage::IsIdle(unsigned int dwVal)
{
  Actor *v3; // eax
  float v4; // eax
  char Buffer[260]; // [esp+0x8] [ebp-0x910] BYREF
  char pExceptionObject[1024]; // [esp+0x10C] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x50C] [ebp-0x40C] BYREF
  int v9; // [esp+0x914] [ebp-0x4]

  v3 = (Actor *)operator new(0x224u);
  v9 = 0;
  if ( v3 )
    FastInit(v3);
  else
    v4 = 0.0f;
  v9 = -1;
  this->m_TaskArrC[0].m_fSlot2 = v4;
  if ( v4 == 0.0f )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_11, 120),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( dwVal <= 4 )
  {
    switch ( dwVal )
    {
      case 0u:
        sprintf(Buffer, dword_58619C);
        break;
      case 1u:
        sprintf(Buffer, (const char *const)&g_pszSceneSlot1);
        break;
      case 2u:
        sprintf(Buffer, a106);
        break;
      case 3u:
        sprintf(Buffer, g_szFormat105);
        break;
      case 4u:
        sprintf(Buffer, (const char *const)g_pfnUpdateFuncs);
        break;
      default:
        break;
    }
    LoadActionSequences((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2), Buffer, 0);
    this->CCBStage::ProcCatchED();
  }
  this->m_TaskSlots[90] = 0;
  return 1;
}

// 0x00509690
bool CCBStage::IsAtInitPos()
{
  float m_fSlot2; // ecx
  float v3; // edi

  m_fSlot2 = this->m_TaskArrC[0].m_fSlot2;
  if ( m_fSlot2 == 0.0f )
    return 1;
  UpdateAllActions((Actor *)LODWORD(m_fSlot2));
  v3 = this->m_TaskArrC[0].m_fSlot2;
  if ( v3 != 0.0f )
  {
    (((NPC *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->NPC::FreeBuffer();
    operator delete((void *)LODWORD(v3));
  }
  this->m_TaskArrC[0].m_fSlot2 = 0.0f;
  return 1;
}

// 0x005096D0
bool CCBStage::IsAtProtectPos(int index, int nAttacker, int nVal)
{
  tagRoleState *inited; // eax
  float m_fSlot0; // eax
  unsigned int v7; // eax
  CCBEditor **v8; // edi
  char *v9; // esi
  char v10; // cl
  tagRoleState *v11; // eax
  char *v12; // edi
  unsigned int v13; // edx
  char *v14; // edi
  CCBSystem *m_pCBSystem; // eax
  CCBRoleState *m_pRoleState; // ecx
  CCBStage *m_pStage; // esi
  int v18; // eax
  CCBEditor **v19; // eax
  CCBSystem *v20; // eax
  CCBRoleState *v21; // ecx
  CCBStage *v22; // esi
  int v23; // eax
  int m_fSlot0_low; // eax
  char v25; // dl
  float v26; // eax
  char *sModel; // [esp-0x8] [ebp-0x11C]
  float m_fCombatAnimY; // [esp+0xC] [ebp-0x108]
  char Buffer[260]; // [esp+0x10] [ebp-0x104] BYREF

  this->CCBStage::GetRotAngle();
  LODWORD(this->m_TaskArrC[0].m_fSlot0) = index;
  LODWORD(this->m_TaskArrC[0].m_fSlot1) = nAttacker;
  this->m_TaskSlots[80] = 1;
  this->m_TaskSlots[81] = 1;
  this->m_TaskSlots[88] = 1;
  this->m_fAngleDegrees = 0.0f;
  if ( index >= 5 && index < 11 )
  {
    if ( strcmp((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(index)->sModel, (const char *)&this->m_pEditor) )
    {
      sModel = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(index)->sModel;
      inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(index);
      sprintf(Buffer, "role\\%s\\%s.ini", inited->sModel, sModel);
      m_fSlot0 = this->m_TaskArrC[0].m_fSlot0;
      if ( SLODWORD(m_fSlot0) < 5 || SLODWORD(m_fSlot0) >= 11 || (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) > 0 )
      {
        v11 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(index);
        LoadActionSequences((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2), v11->sModel, 0);
        v12 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(index)->sModel;
        v13 = strlen(v12) + 1;
        v14 = (char *)&v12[v13];
        qmemcpy(&this->m_pEditor, &v14[-v13], 4 * (v13 >> 2));
        v9 = (char *)&v14[4 * (v13 >> 2) - v13];
        v8 = (CCBEditor **)(&this->m_pEditor + (v13 >> 2));
        v10 = v13;
      }
      else
      {
        LoadActionSequences((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2), a203, 0);
        v7 = strlen(a203) + 1;
        qmemcpy(&this->m_pEditor, a203, 4 * (v7 >> 2));
        v9 = (char *)&a203[4 * (v7 >> 2)];
        v8 = (CCBEditor **)(&this->m_pEditor + (v7 >> 2));
        v10 = v7;
      }
      qmemcpy(v8, v9, v10 & 3);
    }
    this->CCBStage::ProcCatchED();
  }
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(index) )
    this->m_nAllDone = 32;
  else
    this->m_nAllDone = 50;
  this->CCBStage::IsGrabedBy();
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(index) == 1 )
  {
    m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
    m_pRoleState = (CCBRoleState *)this->m_pRoleState;
    this->m_fCombatAnimY = 45.0f;
    m_pStage = (CCBStage *)m_pCBSystem->m_pStage;
    LOBYTE(v18) = (((CCBRoleState *)m_pRoleState))->CCBRoleState::IsAllWeDead(index);
    v19 = (CCBEditor **)(&m_pStage->m_pEditor + 3 * v18);
  }
  else
  {
    v20 = (CCBSystem *)this->m_pCBSystem;
    v21 = (CCBRoleState *)this->m_pRoleState;
    this->m_fCombatAnimY = -135.0f;
    v22 = (CCBStage *)v20->m_pStage;
    LOBYTE(v23) = (((CCBRoleState *)v21))->CCBRoleState::IsAllWeDead(index);
    v19 = (CCBEditor **)(&v22->m_bPaused + 12 * v23);
  }
  *((_DWORD *)&this->m_fCurPosZ + 1) = (unsigned long)*v19;
  *((_DWORD *)&this->m_fCurPosZ + 2) = (unsigned long)v19[1];
  *((_DWORD *)&this->m_fCurPosZ + 3) = (unsigned long)v19[2];
  this->m_fCurPosX = *(&this->m_fCurPosZ + 1);
  this->m_fCurPosY = *(&this->m_fCurPosZ + 2);
  this->m_fCurPosZ = *(&this->m_fCurPosZ + 3);
  m_fCombatAnimY = this->m_fCombatAnimY;
  m_fSlot0_low = LODWORD(this->m_TaskArrC[0].m_fSlot0);
  this->m_fAngleDegrees = m_fCombatAnimY;
  if ( m_fSlot0_low >= 5 && m_fSlot0_low < 11 )
  {
    if ( !this->m_pRoleState->m_pObjMsgBuffer[112] )
      goto LABEL_24;
    goto LABEL_23;
  }
  if ( (unsigned int)m_fSlot0_low <= 4 && this->m_pRoleState->m_pObjMsgBuffer[113] )
LABEL_23:
    this->m_fAngleDegrees = m_fCombatAnimY + 180.0f;
LABEL_24:
  this->CCBStage::ClearAniMsg(0, 1.0);
  v25 = BYTE2((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[2][4]);
  v26 = this->m_TaskArrC[0].m_fSlot0;
  this->m_TaskArrC[0]._todo_018[68] = v25;
  if ( LODWORD(v26) <= 4 )
    this->m_TaskArrC[0]._todo_018[68] = 0;
  return 1;
}

// 0x005099A0
bool CCBStage::ApplyTaskTimeScale(int nVal, BOOL fpTask)
{
  bool result; // al
  float m_fSlot2; // ecx
  int m_nAllDone; // eax
  tagRoleState *inited; // eax
  tagRoleState *v8; // eax
  float v9; // ecx
  CCBStage *Instance; // eax
  CCBStage *v11; // eax
  int v12; // [esp-0xC] [ebp-0x18]
  float scale; // [esp+0x4] [ebp-0x8]
  float v14; // [esp+0x8] [ebp-0x4]

  result = this->m_TaskSlots[80];
  if ( result )
  {
    m_fSlot2 = this->m_TaskArrC[0].m_fSlot2;
    if ( m_fSlot2 != 0.0f )
    {
      scale = 1.2999999523162842f;
      if ( !this->m_TaskArrC[0]._todo_018[76] )
      {
        m_nAllDone = this->m_nAllDone;
        if ( m_nAllDone == 32 || m_nAllDone == 50 )
          scale = 0.6499999761581421f;
      }
      v14 = scale;
      if ( this->m_TaskSlots[83] )
      {
        (((Actor *)LODWORD(m_fSlot2)))->Actor::SetTimeScale(scale);
      }
      else if ( this->m_TaskSlots[82] )
      {
        v14 = 0.0f;
      }
      else
      {
        v14 = scale * *(float *)&this->m_TaskSlots[84];
      }
      (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::SetTimeScale(v14);
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[1][3] )
      {
        inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
        (((gbGeomNode *)inited[1].dwMagicID[1][3]))->gbGeomNode::SetBladeTimeScale(v14);
      }
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[2][0] )
      {
        v8 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
        (((gbGeomNode *)v8[1].dwMagicID[2][0]))->gbGeomNode::SetBladeTimeScale(v14);
      }
      if ( this->CCBStage::ForceDelTaskByPFN() && !this->m_TaskArrC[0]._todo_018[76] )
      {
        this->CCBStage::ClearBadPushTask(0.0099999998);
        if ( !(((CCBRoleState *)this->m_pCBSystem->m_pUtil->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
          this->m_TaskSlots[88] = 0;
      }
      v9 = this->m_TaskArrC[0].m_fSlot2;
      *((_DWORD *)&this->m_fCombatAnimY + 1) = 0;
      if ( (((gbVisNode *)*(gbVisNode **)(LODWORD(v9) + 16)))->gbVisNode::PopMessage(*(gbNodeMsgObj *)&dword_17AB9C8) == 1
        && dword_17AB9C8 == 1 )
      {
        *((_DWORD *)&this->m_fCombatAnimY + 1) = dword_17AB9CC;
      }
      if ( !this->m_TaskArrC[0]._todo_018[76] )
        (((CCBStage *)*((_DWORD *)&this->m_fCombatAnimY + 1)))->CCBStage::Grab(v12);
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) && this->m_nAllDone != 31 )
      {
        Instance = (CCBStage *)CScreenMode::GetInstance();
        (((CCBStage *)Instance))->CCBStage::PlaySound(aWe011, v12);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 && this->m_nAllDone != 31 )
      {
        v11 = (CCBStage *)CScreenMode::GetInstance();
        (((CCBStage *)v11))->CCBStage::PlaySound(aWe011b, v12);
      }
      return (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::QueryState(v12);
    }
  }
  return result;
}

// 0x00509B90
void CCBStage::RunActiveTask(gbMatrixStack *fpTask)
{
  float m_fSlot0; // eax
  int m_fSlot0_low; // eax
  int v5; // esi
  int v6; // edi
  char RoleType; // al
  unsigned int v8; // edi
  int v9; // esi
  int height; // ebx
  int m_nAllDone; // edx
  int v12; // ecx
  tagRoleState *v13; // eax
  tagRoleState *v14; // eax
  int *LastBladePos; // ecx
  double v16; // st7
  tagRoleState *inited; // eax
  CCBSystem *m_pCBSystem; // eax
  char v19; // cl
  __int16 v20; // [esp+0x2C] [ebp-0x6A]
  float v21; // [esp+0x32] [ebp-0x64] BYREF
  float v22; // [esp+0x36] [ebp-0x60] BYREF
  gbVec3D dwMsg; // [esp+0x3A] [ebp-0x5C] BYREF
  float v24[4]; // [esp+0x46] [ebp-0x50] BYREF
  gbMatrix4 v25; // [esp+0x56] [ebp-0x40] BYREF

  if ( (byte_17AB9C4 & 1) == 0 )
  {
    dword_17AB9B8 = 0;
    LOBYTE(byte_17AB9C4) = byte_17AB9C4 | 1;
    dword_17AB9BC = 1065353216;
    dword_17AB9C0 = 0;
    atexit(nullsub_32);
  }
  m_fSlot0 = this->m_TaskArrC[0].m_fSlot0;
  memset(&dwMsg, 0, sizeof(dwMsg));
  v20 = 0;
  if ( SLODWORD(m_fSlot0) >= 5 && SLODWORD(m_fSlot0) < 11 )
    this->CCBStage::ProcPursueRole(0, 0, 0);
  if ( this->m_TaskArrC[0].m_pHead[0] )
  {
    this->CCBStage::CalcTaskWorldMatrix(&dwMsg);
    m_fSlot0_low = LODWORD(this->m_TaskArrC[0].m_fSlot0);
    dwMsg.y = sin(this->m_pCBSystem->m_pUtil->m_fTimeFund * 10.0f + (float)m_fSlot0_low) * 5.0f + dwMsg.y + 6.0f;
    if ( (unsigned int)m_fSlot0_low <= 4 || m_fSlot0_low >= 5 && m_fSlot0_low < 11 && this->CCBStage::ForceEndTaskByPFN() )
    {
      (((gbCamera *)&this->m_pCBSystem->m_pAttackSequen->m_pUI))->gbCamera::PointWorldToScr(&dwMsg, &v21, &v22);
      v5 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 0);
      v6 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 1);
      RoleType = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleType(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 10 && this->m_pRoleState->m_pObjMsgBuffer[124]
        || RoleType && v5 > v6 / 4 )
      {
        strcpy(
          (char *)&g_nCBRoleHitTable[17],
          (const char *)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[3][1]);
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
      (((CCBStage *)HIDWORD(this->m_pCBSystem->m_DeltaTime)))->CCBStage::InitSlotFlags((const char *)&g_nCBRoleHitTable[17], v9, height, -1);
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) > 4 )
        this->CCBStage::ProcPursueRole(v9, height, 1);
    }
  }
  if ( BYTE1(this->m_pCBSystem->m_pUtil->m_nTimesOfCombat) && g_nCombatViewMode == 1
    || this->m_TaskSlots[81] && (this->m_TaskSlots[88] || SLODWORD(this->m_TaskArrC[0].m_fSlot0) < 5) )
  {
    (((gbMatrixStack *)fpTask))->gbMatrixStack::Push();
    (((gbMatrixStack *)fpTask))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_fCurPosX);
    (((gbMatrixStack *)fpTask))->gbMatrixStack::Rotate(this->m_fAngleDegrees, * (gbVec3D *)&dword_17AB9B8);
    m_nAllDone = this->m_nAllDone;
    switch ( *(&dword_56FE98 + m_nAllDone) )
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
    v12 = LODWORD(this->m_TaskArrC[0].m_fSlot0);
    if ( !v12 && (m_nAllDone == 39 || m_nAllDone == 49) )
      v20 = 0;
    if ( v12 == 3 )
      v20 = 257;
    if ( v12 == 1 )
      v20 = 257;
    if ( (v12 == 2 || v12 == 4) && m_nAllDone == 46 )
      v20 = 256;
    if ( this->m_TaskArrC[0]._todo_018[76] )
    {
      if ( *(float *)&this->m_TaskArrC[0]._todo_018[80] > 0.0f
        || (LOBYTE(v20) = 0, *(float *)&this->m_TaskArrC[0]._todo_018[80] >= 0.0) )
      {
        LOBYTE(v20) = 1;
      }
      if ( *(float *)&this->m_TaskArrC[0]._todo_018[84] <= 0.0f && *(float *)&this->m_TaskArrC[0]._todo_018[84] < 0.0f )
        goto LABEL_64;
    }
    else if ( !HIBYTE(v20) )
    {
LABEL_64:
      if ( (_BYTE)v20
        && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[1][3] )
      {
        (((gbMatrixStack *)fpTask))->gbMatrixStack::Push();
        (((gbActor *)*(gbActor **)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16)))->gbActor::GetTagNodeTM(&v25, "tag_weapon2");
        (((gbMatrixStack *)fpTask))->gbMatrixStack::MultMatrix(&v25);
        inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
        (*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)inited[1].dwMagicID[1][3] + 16))(
          inited[1].dwMagicID[1][3],
          0);
        (((gbMatrixStack *)fpTask))->gbMatrixStack::Pop();
      }
      if ( this->m_TaskSlots[90] )
      {
        m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
        v19 = this->m_TaskArrC[0]._todo_018[68];
        v24[0] = sin(this->m_pCBSystem->m_pUtil->m_fTimeFund * 7.8000002) * 0.34999999 + 0.64999998;
        v24[1] = v24[0];
        v24[2] = v24[0];
        if ( v19 )
        {
          (((gbRenderEffect *)*(gbRenderEffect **)(HIDWORD(m_pCBSystem->m_dTimeFund) + 2440)))->gbRenderEffect::SetVariant((GBPARAMHANDLE)(GBPARAM_TEXTURE1|GBPARAM_PROJMATRIX), v24);
          (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::DispatchAction(*(_DWORD *)(HIDWORD(this->m_pCBSystem->m_dTimeFund) + 2440));
        }
        else
        {
          (((gbRenderEffect *)*(gbRenderEffect **)(HIDWORD(m_pCBSystem->m_dTimeFund) + 2436)))->gbRenderEffect::SetVariant((GBPARAMHANDLE)(GBPARAM_TEXTURE1|GBPARAM_PROJMATRIX), v24);
          (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::DispatchAction(*(_DWORD *)(HIDWORD(this->m_pCBSystem->m_dTimeFund) + 2436));
        }
      }
      else
      {
        (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::DispatchAction(0);
      }
      (((gbMatrixStack *)fpTask))->gbMatrixStack::Pop();
      return;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v12)[1].dwMagicID[2][0] )
    {
      (((gbMatrixStack *)fpTask))->gbMatrixStack::Push();
      (((gbActor *)*(gbActor **)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16)))->gbActor::GetTagNodeTM(&v25, "tag_weapon1");
      (((gbMatrixStack *)fpTask))->gbMatrixStack::MultMatrix(&v25);
      v13 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)v13[1].dwMagicID[2][0] + 16))(
        v13[1].dwMagicID[2][0],
        0);
      (((gbMatrixStack *)fpTask))->gbMatrixStack::Pop();
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 3 && *(_BYTE *)(g_RoleSlotBuf.m_teamData3[98] + 613) == 3 )
      {
        v14 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(3);
        LastBladePos = (int *)(((gbGeomNode *)v14[1].dwMagicID[2][0]))->gbGeomNode::GetLastBladePos(0);
        if ( LastBladePos )
        {
          v16 = this->m_pCBSystem->m_pUtil->m_DeltaTime + g_StageRoleData._todo_06C;
          g_StageRoleData._todo_06C = v16;
          if ( v16 >= 0.050000001 )
          {
            (((C3DSpark *)this->m_pCBSystem->m_pUtil->m_p3DSpark))->C3DSpark::CreateOne(*LastBladePos, LastBladePos[1], LastBladePos[2]);
            g_StageRoleData._todo_06C = g_StageRoleData._todo_06C - 0.050000001;
          }
        }
      }
    }
    goto LABEL_64;
  }
}

// 0x0050A180
int CCBStage::Grab(int dwStageTaskID, bool bNormal)
{
  CCBStage *v2; // ecx
  CCBStage *v3; // esi

  v3 = (CCBStage *)v2;
  (((CCBStage *)v2))->CCBStage::FindFreeSlot(dwStageTaskID);
  (((CCBStage *)v3))->CCBStage::CountValidTasks();
  return (((CCBStage *)v3))->CCBStage::FindNextTask();
}

// 0x0050A1A0
void CCBStage::Release(char dwStageTaskID)
{
  this->m_TaskSlots[88] = dwStageTaskID;
}

// 0x0050A1B0
void CCBStage::TryRelease()
{
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 23) )
    this->CCBStage::ClearAniMsg(1, 0.44);
  else
    this->CCBStage::ClearAniMsg(0, 1.0);
}

// 0x0050A1F0
void CCBStage::ForceRelease(char pData)
{
  this->m_TaskSlots[81] = pData;
}

// 0x0050A200
void CCBStage::DangerForceRelease(char pData)
{
  this->m_TaskSlots[82] = pData;
}

// 0x0050A210
bool CCBStage::IsGrabedBy()
{
  float m_fSlot2; // ecx
  bool result; // al

  m_fSlot2 = this->m_TaskArrC[0].m_fSlot2;
  if ( m_fSlot2 != 0.0f )
  {
    (((Actor *)LODWORD(m_fSlot2)))->Actor::EnableTransition(*(&bVisible + this->m_nAllDone), this->m_TaskArrC[0]._todo_018[68] != 0);
    return (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::CompareActionName(this->m_nAllDone, 0);
  }
  return result;
}

// 0x0050A260
void CCBStage::GetPointerPos()
{
  float m_fSlot2; // ecx

  m_fSlot2 = this->m_TaskArrC[0].m_fSlot2;
  if ( m_fSlot2 != 0.0f )
  {
    (((Actor *)LODWORD(m_fSlot2)))->Actor::EnableTransition(*(&bVisible + this->m_nAllDone), this->m_TaskArrC[0]._todo_018[68] != 0);
    SetActionByName(
      (Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2),
      *((const char **)&bVisible + this->m_nAllDone),
      0,
      0);
  }
}

// 0x0050A2B0
void CCBStage::SetBladeTime(int fBladeTime)
{
  int *v3; // eax
  float v4; // st7
  float v5; // st6
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
  v3 = (int *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + fBladeTime) + 6584);
  g_nCBRoleHitTable[9] = *v3;
  g_nCBRoleHitTable[10] = v3[1];
  g_nCBRoleHitTable[11] = v3[2];
  v4 = *(float *)&g_nCBRoleHitTable[9] - this->m_fCurPosX;
  *(float *)&v7 = *(float *)&g_nCBRoleHitTable[10] - this->m_fCurPosY;
  v5 = *(float *)&g_nCBRoleHitTable[11] - this->m_fCurPosZ;
  g_nCBRoleHitTable[14] = v7;
  *(float *)&v8 = v5;
  *(float *)&g_nCBRoleHitTable[13] = v4;
  g_nCBRoleHitTable[15] = v8;
  (((gbVec3D *)&g_nCBRoleHitTable[13]))->gbVec3D::Normalize();
  v6 = acos(
         *(float *)&g_nCBRoleHitTable[7] * *(float *)&g_nCBRoleHitTable[15]
       + *(float *)&g_nCBRoleHitTable[6] * *(float *)&g_nCBRoleHitTable[14]
       + *(float *)&g_nCBRoleHitTable[5] * *(float *)&g_nCBRoleHitTable[13]);
  this->m_fAngleDegrees = v6;
  if ( *(float *)&g_nCBRoleHitTable[13] < 0.0f )
    this->m_fAngleDegrees = 6.2831854820251465f - v6;
  this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
}

// 0x0050A4B0
bool CCBStage::CheckViewTarget()
{
  CCBSystem *m_pCBSystem; // eax
  gbRay v4; // [esp-0x18] [ebp-0x44] BYREF
  float pPos[2]; // [esp+0xC] [ebp-0x20] BYREF
  _BYTE pTarget[24]; // [esp+0x14] [ebp-0x18] BYREF

  m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
  pPos[0] = this->m_pCBSystem->m_fTimeFund;
  pPos[1] = *(&m_pCBSystem->m_fTimeFund + 1);
  qmemcpy(&v4, (((CameraCtrl *)m_pCBSystem->m_pAttackSequen))->CameraCtrl::GetViewTarget(pTarget, pPos), sizeof(v4));
  return this->CCBStage::LoadAction(v4);
}

// 0x0050A500
bool CCBStage::LoadAction(gbRay nActIndex)
{
  gbOBBox *WorldPos; // eax

  WorldPos = (gbOBBox *)this->CCBStage::GetWorldPos();
  return (((gbRay *)&nActIndex))->gbRay::IsColOBB(*WorldPos) == 1;
}

// 0x0050A520
int CCBStage::GetStatus(int index)
{
  (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::PlayAction((int)&this->m_TaskArrC[0].m_fSlot3);
  return LODWORD(this->m_TaskArrC[0].m_fSlot0);
}

// 0x0050A560
float * CCBStage::GetWorldPos()
{
  gbMatrix4 v3; // [esp+0x8] [ebp-0x40] BYREF

  (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::PlayAction((int)&this->m_TaskArrC[0].m_fSlot3);
  (((gbMatrix4 *)&v3))->gbMatrix4::LoadIdentity();
  (((gbMatrix4 *)&v3))->gbMatrix4::SetAxisAngle(GB_AXIS_Y, this->m_fAngleDegrees);
  (((gbMatrix4 *)&this->m_TaskArrC[0].m_fSlot3))->gbMatrix4::RightMultiply(&v3);
  (((gbMatrix4 *)&this->m_TaskArrC[0].m_fSlot3))->gbMatrix4::RightTranslate(*(gbVec3D *)&this->m_fCurPosX);
  return &this->m_TaskArrC[0].m_fSlot3;
}

// 0x0050A5D0
double CCBStage::AddTask(float *fp)
{
  float v3; // st7
  float v4; // st6
  float v6; // st7
  gbVec3D v7; // [esp+0x4] [ebp-0x18] BYREF
  float v8; // [esp+0x14] [ebp-0x8]
  float v9; // [esp+0x18] [ebp-0x4]

  if ( (g_nCBRoleHitTable[4] & 1) == 0 )
  {
    v7.x = 0.0f;
    LOBYTE(g_nCBRoleHitTable[4]) |= 1u;
    v7.y = 0.0f;
    v7.z = 1.0f;
    g_nCBRoleHitTable[1] = 0;
    g_nCBRoleHitTable[2] = 0;
    g_nCBRoleHitTable[3] = 1065353216;
    atexit(nullsub_36);
  }
  v3 = *fp - this->m_fCurPosX;
  v8 = fp[1] - this->m_fCurPosY;
  v4 = fp[2] - this->m_fCurPosZ;
  v7.y = v8;
  v9 = v4;
  v7.x = v3;
  v7.z = v9;
  if ( (((gbVec3D *)&v7))->gbVec3D::Length() <= 0.0 )
    return 0.0;
  (((gbVec3D *)&v7))->gbVec3D::Normalize();
  v6 = acos(
         v7.y * *(float *)&g_nCBRoleHitTable[2]
       + v7.z * *(float *)&g_nCBRoleHitTable[3]
       + *(float *)&g_nCBRoleHitTable[1] * v7.x);
  if ( v7.x < 0.0f )
    v6 = 6.2831854820251465f - v6;
  return v6 * 57.29578;
}

// 0x0050A6F0
bool CCBStage::ForceDelTaskByPFN()
{
  return *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] == 0;
}

// 0x0050A700
bool CCBStage::ForceEndTaskByPFN()
{
  float v1; // st7
  float v2; // st6
  float v4; // [esp+0x4] [ebp-0x14]
  float v5; // [esp+0x8] [ebp-0x10]
  gbVec3D v6; // [esp+0xC] [ebp-0xC] BYREF

  v1 = this->m_fCurPosX - *(&this->m_fCurPosZ + 1);
  v4 = this->m_fCurPosY - *(&this->m_fCurPosZ + 2);
  v2 = this->m_fCurPosZ - *(&this->m_fCurPosZ + 3);
  v6.y = v4;
  v5 = v2;
  v6.x = v1;
  v6.z = v5;
  return (((gbVec3D *)&v6))->gbVec3D::Length() <= 13.0;
}

// 0x0050A770
bool CCBStage::MoveToAbsolute(int fp, int dwTaskID)
{
  float m_fSlot0; // eax
  CCBSystem *m_pCBSystem; // ecx
  float *v6; // eax
  float *v7; // ecx
  float v8; // st7
  float v9; // st6
  CCBSystem *v10; // edx
  float *v11; // eax
  float v12; // st7
  float v13; // st7
  float v14; // st6
  gbVec3D v16; // [esp+0x4] [ebp-0x30] BYREF
  gbVec3D v17; // [esp+0x10] [ebp-0x24] BYREF
  float v18; // [esp+0x20] [ebp-0x14]
  float v19; // [esp+0x24] [ebp-0x10]
  float v20; // [esp+0x2C] [ebp-0x8]
  float v21; // [esp+0x30] [ebp-0x4]

  memset(&v16, 0, sizeof(v16));
  m_fSlot0 = this->m_TaskArrC[0].m_fSlot0;
  memset(&v17, 0, sizeof(v17));
  if ( m_fSlot0 != 0.0f )
    return 0;
  m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
  v6 = (float *)*((_DWORD *)&m_pCBSystem->m_pAI + fp);
  v7 = (float *)(*((_DWORD *)&m_pCBSystem->m_pAI + dwTaskID) + 6596);
  v6 += 1649;
  v8 = *v7 - *v6;
  v18 = v7[1] - v6[1];
  v9 = v7[2] - v6[2];
  v16.y = v18;
  v19 = v9;
  v16.x = v8;
  v16.z = v19;
  (((gbVec3D *)&v16))->gbVec3D::Normalize();
  v10 = (CCBSystem *)this->m_pCBSystem;
  v16.x = v16.x * 40.0f;
  v16.y = v16.y * 40.0f;
  v16.z = v16.z * 40.0f;
  v11 = (float *)*((_DWORD *)&v10->m_pAI + fp);
  v12 = v16.x + v11[1649];
  v18 = v16.y + v11[1650];
  v19 = v16.z + v11[1651];
  v16.x = v12;
  v16.z = v19;
  v16.y = v18;
  v13 = this->m_fCurPosX - v12;
  v20 = this->m_fCurPosY - v18;
  v14 = this->m_fCurPosZ - v19;
  v17.y = v20;
  v21 = v14;
  v17.x = v13;
  v17.z = v21;
  return (((gbVec3D *)&v17))->gbVec3D::Length() <= 20.0;
}

// 0x0050A8E0
bool CCBStage::DelTask(int nIndex)
{
  *(_DWORD *)&this->m_TaskArrA[1324] = nIndex;
  return 1;
}

// 0x0050A8F0
bool CCBStage::DelAllTask(int nVal, char pData)
{
  bool result; // al

  result = 1;
  if ( this->m_TaskArrC[0]._todo_018[69] == 1 )
    return 0;
  this->m_TaskArrC[0]._todo_018[69] = 1;
  this->m_TaskArrC[0]._todo_018[70] = pData;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[72] = nVal;
  return result;
}

// 0x0050A920
char CCBStage::GetCurrentTask(int nVal)
{
  char result; // al

  if ( nVal != 0x7FFFFFFF || (result = this->m_TaskArrC[0]._todo_018[69]) != 0 )
  {
    result = this->CCBStage::GetCurrentState();
    this->m_TaskArrC[0]._todo_018[69] = 0;
    this->m_TaskArrC[0]._todo_018[70] = 0;
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[72] = 0;
  }
  return result;
}

// 0x0050A960
int CCBStage::GetCurrentTaskIndex()
{
  int result; // eax

  this->CCBStage::GetCurrentState();
  result = 0;
  this->m_TaskArrC[0]._todo_018[69] = 0;
  this->m_TaskArrC[0]._todo_018[70] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[72] = 0;
  return result;
}

// 0x0050A980
bool CCBStage::IsReady(int idx)
{
  return this->m_TaskArrC[0]._todo_018[69] && *(_DWORD *)&this->m_TaskArrC[0]._todo_018[72] == idx;
}

// 0x0050A9B0
tagRoleState * CCBStage::CalcTaskWorldMatrix(gbVec3D *dwMsg)
{
  gbVec3D *WorldPos; // eax
  tagRoleState *result; // eax
  char v5; // [esp+0x8] [ebp-0xC] BYREF

  if ( (g_nCBRoleHitTable[0] & 1) == 0 )
  {
    LOBYTE(g_nCBRoleHitTable[0]) |= 1u;
    atexit(nullsub_37);
  }
  WorldPos = (gbVec3D *)this->CCBStage::GetWorldPos();
  *dwMsg = *((gbVec3D *( *)(gbVec3D *__return_ptr __struct_ptr, gbOBBox *))gbOBBox::GetCenter)(
              WorldPos,
              (gbOBBox *)&v5);
  dwMsg->y = *(float *)&this->m_TaskArrC[0]._todo_018[60] * 0.5 + dwMsg->y + 10.0;
  result = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
  if ( result->dwID == 707 )
    dwMsg->y = dwMsg->y - 80.0;
  return result;
}

// 0x0050AA60
void CCBStage::ClearBadPushTask(float fVal)
{
  unsigned int m_fSlot0_low; // eax
  tagRoleState *inited; // eax
  tagRoleState *v5; // eax

  m_fSlot0_low = LODWORD(this->m_TaskArrC[0].m_fSlot0);
  if ( m_fSlot0_low <= 4 )
  {
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(m_fSlot0_low)[1].dwMagicID[1][3] )
    {
      inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (((gbGeomNode *)inited[1].dwMagicID[1][3]))->gbGeomNode::SetBladeTime(fVal);
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[2][0] )
    {
      v5 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (((gbGeomNode *)v5[1].dwMagicID[2][0]))->gbGeomNode::SetBladeTime(fVal);
    }
  }
}

// 0x0050AAE0
double CCBStage::PushBackAllTask()
{
  float m_fSlot2; // eax
  float v3; // [esp+0x4] [ebp-0x4] BYREF

  m_fSlot2 = this->m_TaskArrC[0].m_fSlot2;
  v3 = 0.0f;
  if ( (((gbVisNode *)*(gbVisNode **)(LODWORD(m_fSlot2) + 16)))->gbVisNode::GetBlend(&v3) )
    return v3;
  else
    return 1.0;
}

// 0x0050AB10
void CCBStage::ClearAniMsg(char pData, float fVal)
{
  tagRoleState *inited; // eax
  tagRoleState *v5; // eax
  tagRoleState *v6; // eax
  tagRoleState *v7; // eax

  if ( fVal <= 0.98000002f && pData )
  {
    (((gbVisNode *)*(gbVisNode **)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16)))->gbVisNode::SetBlend(BLEND_ALPHA, fVal);
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[2][0] )
    {
      inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (((gbVisNode *)inited[1].dwMagicID[2][0]))->gbVisNode::SetBlend(BLEND_ALPHA, fVal);
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[1][3] )
    {
      v5 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (((gbVisNode *)v5[1].dwMagicID[1][3]))->gbVisNode::SetBlend(BLEND_ALPHA, fVal);
    }
  }
  else
  {
    (((gbVisNode *)*(gbVisNode **)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16)))->gbVisNode::SetBlend(BLEND_NONE, 1.0);
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[2][0] )
    {
      v6 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (((gbVisNode *)v6[1].dwMagicID[2][0]))->gbVisNode::SetBlend(BLEND_NONE, 1.0);
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[1][3] )
    {
      v7 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (((gbVisNode *)v7[1].dwMagicID[1][3]))->gbVisNode::SetBlend(BLEND_NONE, 1.0);
    }
  }
}

// 0x0050AC50
void CCBStage::SetParam(int pParam, char dw1)
{
  const char *EditorTaskDescription; // eax
  float m_fSlot2; // ecx

  if ( pParam > 0 )
  {
    sprintf(byte_17AB818, "z%02d", pParam);
    if ( (byte_1895558 & 1) == 0 )
    {
      LOBYTE(byte_1895558) = byte_1895558 | 1;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    EditorTaskDescription = (((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)byte_17AB818);
    if ( dw1 || EditorTaskDescription != *((const char **)&this->m_nTotalCount + 1) )
    {
      m_fSlot2 = this->m_TaskArrC[0].m_fSlot2;
      *(&this->m_nTotalCount + 1) = (int)EditorTaskDescription;
      SetActionByName((Actor *)LODWORD(m_fSlot2), byte_17AB818, 0, 0);
      (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16) + 24))(
        *(_DWORD *)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16),
        0);
    }
  }
}

// 0x0050AD30
char CCBStage::GetProperCurAction(
        
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
  _DWORD *v13; // eax
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
  if ( *(_DWORD *)&this->m_TaskArrC[0]._todo_018[72] != nVal5 )
    return 0;
  v11 = (int *)pnVal;
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
    this->CCBStage::GetCurrentState();
    goto LABEL_15;
  }
  if ( nVal6 != 3 )
  {
LABEL_15:
    v12 = (int *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 112];
    *v12 = nVal;
    v12[1] = nVal2;
    v12[2] = nVal3;
    v12[3] = nVal4;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 200] = 1;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 202] = 0;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 201] = 0;
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 192] = (((CCBSystem *)this->m_pCBSystem->m_pUtil))->CCBSystem::ProcProtect();
    v13 = (_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 128];
    *v13 = g_nCBRoleMoveTable[20];
    v13[1] = g_nCBRoleMoveTable[21];
    v13[2] = g_nCBRoleMoveTable[22];
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 196] = nVal6;
    if ( pData )
      qmemcpy(&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 140], pData, 0x2Cu);
    else
      memset(&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 140], 0, 0x2Cu);
    goto LABEL_23;
  }
  this->CCBStage::RefreshTaskTargetPos();
  this->m_TaskArrC[0]._todo_018[200] = 1;
  this->m_TaskArrC[0]._todo_018[202] = 0;
  this->m_TaskArrC[0]._todo_018[201] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[112] = nVal;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[116] = nVal2;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[120] = nVal3;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[124] = nVal4;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[192] = (((CCBSystem *)this->m_pCBSystem->m_pUtil))->CCBSystem::ProcProtect();
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[128] = g_nCBRoleMoveTable[20];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[132] = g_nCBRoleMoveTable[21];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[136] = g_nCBRoleMoveTable[22];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[196] = 3;
  if ( pData )
    qmemcpy(&this->m_TaskArrC[0]._todo_018[140], pData, 0x2Cu);
  else
    memset(&this->m_TaskArrC[0]._todo_018[140], 0, 0x2Cu);
  this->m_TaskArrC[1]._todo_018[18] = 0;
LABEL_23:
  ++*(_DWORD *)&this->m_TaskArrC[0]._todo_018[88];
  return 1;
}

// 0x0050B070
char CCBStage::ProcTransportRun(
        
        unsigned int dwMsg,
        int nVal,
        int nVal2,
        int nVal3,
        int *pnVal,
        const void *pData,
        int nVal4)
{
  int *v9; // eax
  int v11; // eax
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
  v9 = (int *)pnVal;
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
      this->CCBStage::GetCurrentState();
      break;
    case 3:
      this->CCBStage::RefreshTaskTargetPos();
      break;
    case 4:
      if ( *(int *)&this->m_TaskArrC[0]._todo_018[88] > 0 )
        return 0;
      break;
    default:
      return 0;
  }
  this->m_TaskArrC[0]._todo_018[200] = 1;
  this->m_TaskArrC[0]._todo_018[202] = 0;
  this->m_TaskArrC[0]._todo_018[201] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[112] = dwMsg;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[116] = nVal;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[120] = nVal2;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[124] = nVal3;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[192] = (((CCBSystem *)this->m_pCBSystem->m_pUtil))->CCBSystem::ProcProtect();
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[128] = g_nCBRoleMoveTable[8];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[132] = g_nCBRoleMoveTable[9];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[136] = g_nCBRoleMoveTable[10];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[196] = nVal4;
  if ( pData )
    qmemcpy(&this->m_TaskArrC[0]._todo_018[140], pData, 0x2Cu);
  else
    memset(&this->m_TaskArrC[0]._todo_018[140], 0, 0x2Cu);
  v11 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] + 1;
  this->m_TaskArrC[1]._todo_018[18] = 0;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] = v11;
  return 1;
}

// 0x0050B290
void CCBStage::SetForceFinishThrowingWeapon(int bForce)
{
  int v2; // ebx
  _BYTE *v3; // eax

  v2 = bForce;
  if ( bForce == 63 )
  {
    memset(&this->m_TaskArrA[1224], 0, 0x60u);
    --*(_DWORD *)&this->m_TaskArrC[0]._todo_018[88];
  }
  else
  {
    if ( bForce < *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] )
    {
      v3 = (_BYTE *)&this->m_TaskArrC[0]._todo_018[96 * bForce + 112];
      do
      {
        ++v2;
        qmemcpy(v3, v3 + 96, 0x60u);
        v3 += 96;
      }
      while ( v2 < *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] );
    }
    memset(&this->m_TaskArrC[0]._todo_018[96 * (*(_DWORD *)&this->m_TaskArrC[0]._todo_018[88])-- + 112], 0, 0x60u);
  }
}

// 0x0050B330
char CCBStage::GetCurrentState()
{
  _BYTE *v1; // eax
  int v2; // edx

  v1 = (_BYTE *)&this->m_TaskArrC[0]._todo_018[192];
  v2 = 64;
  do
  {
    v1[8] = 0;
    *(_DWORD *)v1 = 0;
    v1 += 96;
    --v2;
  }
  while ( v2 );
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88] = 0;
  return 1;
}

// 0x0050B360
unsigned int CCBStage::ProcCatchED()
{
  unsigned int result; // eax

  if ( SLODWORD(this->m_TaskArrC[0].m_fSlot0) < 5 )
  {
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration(animId);
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)"z09");
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)"z06");
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)"z03");
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)"z04");
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)"z05");
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)&g_CCBStageData.m_nEffTypeCode);
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)&g_CCBStageData.m_nEffTypeID);
    (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)&g_CCBStageData.m_nEffParam1C);
    return (((Actor *)LODWORD(this->m_TaskArrC[0].m_fSlot2)))->Actor::GetAnimDuration((int)&g_CCBStageData.m_nEffParam14);
  }
  return result;
}

// 0x0050B430
char CCBStage::FindFreeSlot(int a2)
{
  int v3; // eax
  _BYTE *i; // ecx
  int ( *v5)(char *, int); // eax

  v3 = 0;
  for ( i = &this->m_TaskArrC[0]._todo_018[201]; !*(i - 1) || *i; i += 96 )
  {
    if ( ++v3 >= 64 )
    {
      this->m_nAllDone = this->CCBStage::ProcTurn();
      LOBYTE(v5) = this->CCBStage::IsGrabedBy();
      *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] = -1;
      return (char)v5;
    }
  }
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] = v3;
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96] = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * v3 + 112];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[100] = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * v3 + 116];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[104] = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * v3 + 120];
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[108] = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * v3 + 124];
  v5 = *(int ( **)(char *, int))&this->m_TaskArrC[0]._todo_018[96];
  if ( v5 )
    LOBYTE(v5) = v5((char *)this + *(_DWORD *)&this->m_TaskArrC[0]._todo_018[100], a2);
  return (char)v5;
}

// 0x0050B4C0
char CCBStage::CountValidTasks()
{
  int v1; // edx
  _BYTE *v2; // eax

  v1 = 0;
  v2 = (_BYTE *)&this->m_TaskArrC[0]._todo_018[201];
  while ( *(v2 - 1) != 1 || *v2 != 1 )
  {
    ++v1;
    v2 += 96;
    if ( v1 >= 64 )
      return (char)v2;
  }
  this->CCBStage::SetForceFinishThrowingWeapon(v1);
  return (char)v2;
}

// 0x0050B4F0
int CCBStage::FindNextTask()
{
  int result; // eax
  int v3; // esi
  _DWORD *v4; // ebx

  result = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88];
  if ( result > 1 )
  {
    v3 = 1;
    v4 = (_DWORD *)&this->m_TaskArrC[1]._todo_018[12];
    do
    {
      if ( *v4 == 3 )
        this->CCBStage::SetForceFinishThrowingWeapon(v3);
      result = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88];
      ++v3;
      v4 += 24;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x0050B530
void CCBStage::RefreshTaskTargetPos()
{
  int v1; // eax
  int v2; // edx
  _BYTE *v3; // edi

  v1 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88];
  if ( v1 )
  {
    if ( v1 > 0 )
    {
      v2 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[88];
      v3 = (_BYTE *)&this->m_TaskArrC[0]._todo_018[96 * v1 + 112];
      do
      {
        --v2;
        qmemcpy(v3, v3 - 96, 0x60u);
        v3 -= 96;
      }
      while ( v2 );
    }
    memset(&this->m_TaskArrC[0]._todo_018[112], 0, 0x60u);
  }
}

// 0x0050B580
char CCBStage::ProcPursueRole(int formal, int nVal, char pData)
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

  m_pUI = (CCBUI *)this->m_pCBSystem->m_pUtil->m_pUI;
  if ( pData )
  {
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 6) )
    {
      v6 = (UIStatic *)m_pUI->m_pRoleStateFace[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 3];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v6))((UIStatic *)(v6), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateFace[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 3], formal, nVal);
      v7 = formal + 24;
    }
    else
    {
      v7 = formal;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 7) )
    {
      v8 = (UIStatic *)m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v8))((UIStatic *)(v8), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 24;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 8) )
    {
      v9 = (UIStatic *)m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v9))((UIStatic *)(v9), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 24;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 9) )
    {
      v10 = (UIStatic *)m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v10))((UIStatic *)(v10), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 24;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 12) )
    {
      v11 = (UIStatic *)m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v11))((UIStatic *)(v11), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 24;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 13) )
    {
      v12 = (UIStatic *)m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v12))((UIStatic *)(v12), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 24;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 10) )
    {
      v13 = (UIStatic *)m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v13))((UIStatic *)(v13), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 24;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 11) )
    {
      v14 = (UIStatic *)m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v14))((UIStatic *)(v14), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 24;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 14) )
    {
      v15 = (UIStatic *)m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v15))((UIStatic *)(v15), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 15) )
    {
      v16 = (UIStatic *)m_pUI->m_pRoleStateStable[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v16))((UIStatic *)(v16), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateStable[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 16) )
    {
      v17 = (UIStatic *)m_pUI->m_pRoleStateBlank[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v17))((UIStatic *)(v17), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateBlank[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 17) )
    {
      v18 = (UIStatic *)m_pUI->m_pRoleStateForbid[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v18))((UIStatic *)(v18), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateForbid[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 18) )
    {
      v19 = (UIStatic *)m_pUI->m_pRoleStateSleep[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v19))((UIStatic *)(v19), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateSleep[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 19) )
    {
      v20 = (UIStatic *)m_pUI->m_pRoleStateChaos[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v20))((UIStatic *)(v20), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateChaos[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 20) )
    {
      v21 = (UIStatic *)m_pUI->m_pRoleStateMad[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v21))((UIStatic *)(v21), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateMad[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 21) )
    {
      v22 = (UIStatic *)m_pUI->m_pRoleStateMirror[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v22))((UIStatic *)(v22), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateMirror[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 22) )
    {
      v23 = (UIStatic *)m_pUI->m_pRoleStateWall[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v23))((UIStatic *)(v23), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateWall[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 23) )
    {
      v24 = (UIStatic *)m_pUI->m_pRoleStateBound[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v24))((UIStatic *)(v24), (int)(1));
      ::MoveToAbsolute(m_pUI->m_pRoleStateBound[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
      v7 += 20;
    }
    result = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 26);
    if ( result )
    {
      v26 = (UIStatic *)m_pUI->m_pRoleStateHermit[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
      (**(void ( ***)(UIStatic *, int))((UIWnd *)v26))((UIStatic *)(v26), (int)(1));
      return MoveToAbsolute(m_pUI->m_pRoleStateHermit[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4], v7, nVal);
    }
  }
  else
  {
    v27 = (UIStatic *)m_pUI->m_pRoleStateFace[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 3];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v27))((UIStatic *)(v27), (_DWORD)(0));
    v28 = (UIStatic *)m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v28))((UIStatic *)(v28), (_DWORD)(0));
    v29 = (UIStatic *)m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v29))((UIStatic *)(v29), (_DWORD)(0));
    v30 = (UIStatic *)m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v30))((UIStatic *)(v30), (_DWORD)(0));
    v31 = (UIStatic *)m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v31))((UIStatic *)(v31), (_DWORD)(0));
    v32 = (UIStatic *)m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v32))((UIStatic *)(v32), (_DWORD)(0));
    v33 = (UIStatic *)m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v33))((UIStatic *)(v33), (_DWORD)(0));
    v34 = (UIStatic *)m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v34))((UIStatic *)(v34), (_DWORD)(0));
    v35 = (UIStatic *)m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v35))((UIStatic *)(v35), (_DWORD)(0));
    v36 = (UIStatic *)m_pUI->m_pRoleStateStable[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v36))((UIStatic *)(v36), (_DWORD)(0));
    v37 = (UIStatic *)m_pUI->m_pRoleStateBlank[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v37))((UIStatic *)(v37), (_DWORD)(0));
    v38 = (UIStatic *)m_pUI->m_pRoleStateForbid[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v38))((UIStatic *)(v38), (_DWORD)(0));
    v39 = (UIStatic *)m_pUI->m_pRoleStateSleep[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v39))((UIStatic *)(v39), (_DWORD)(0));
    v40 = (UIStatic *)m_pUI->m_pRoleStateChaos[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v40))((UIStatic *)(v40), (_DWORD)(0));
    v41 = (UIStatic *)m_pUI->m_pRoleStateMad[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v41))((UIStatic *)(v41), (_DWORD)(0));
    v42 = (UIStatic *)m_pUI->m_pRoleStateMirror[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v42))((UIStatic *)(v42), (_DWORD)(0));
    v43 = (UIStatic *)m_pUI->m_pRoleStateWall[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v43))((UIStatic *)(v43), (_DWORD)(0));
    v44 = (UIStatic *)m_pUI->m_pRoleStateBound[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v44))((UIStatic *)(v44), (_DWORD)(0));
    v45 = (UIStatic *)m_pUI->m_pRoleStateHermit[LODWORD(this->m_TaskArrC[0].m_fSlot0) + 4];
    return (**(int ( ***)(UIStatic *, _DWORD))((UIWnd *)v45))((UIStatic *)(v45), (_DWORD)(0));
  }
  return result;
}

// 0x0050BBD0
unsigned int CCBStage::ProcTurn()
{
  unsigned int m_fSlot0_low; // eax
  CCBRoleState *m_pRoleState; // ecx
  int v5; // eax

  m_fSlot0_low = LODWORD(this->m_TaskArrC[0].m_fSlot0);
  m_pRoleState = (CCBRoleState *)this->m_pRoleState;
  if ( !m_pRoleState->m_pObjMsgBuffer[892 * m_fSlot0_low + 153] )
  {
    if ( m_fSlot0_low <= 4 )
      return 32;
    return 50;
  }
  if ( !(((CCBRoleState *)m_pRoleState))->CCBRoleState::IsActive(m_fSlot0_low) )
    return 50;
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleAttr(LODWORD(this->m_TaskArrC[0].m_fSlot0)) == 5 )
    return 47;
  if ( *(_DWORD *)&this->m_TaskArrA[1324] == 4 )
    return 34;
  if ( LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))->byMagicUseTime[8][5]) )
  {
    this->CCBStage::ClearBadPushTask(0.25);
    return 42;
  }
  else if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 17)
         || (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 14) )
  {
    return 45;
  }
  else
  {
    v5 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleAttr(LODWORD(this->m_TaskArrC[0].m_fSlot0)) - 4;
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
unsigned int CCBStage::ProcTurnToRole(int formal)
{
  float *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  int v8; // eax
  float *v9; // ecx
  CScreenMode *v10; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v12; // eax
  float *p_m_fCurPosX; // edi
  double m_DeltaTime; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  CCBStage *v19; // eax
  CCBStage *v20; // eax
  double v21; // st7
  double v22; // st7
  CCBStage *v23; // eax
  CCBStage *v24; // eax
  CCBStage *v25; // eax
  int v26; // [esp-0x4] [ebp-0x28]
  int v27; // [esp+0x0] [ebp-0x24]
  int v28; // [esp+0x10] [ebp-0x14]
  float v29; // [esp+0x10] [ebp-0x14]
  int v30; // [esp+0x14] [ebp-0x10]
  float v31; // [esp+0x14] [ebp-0x10]
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
  v3 = (float *)((char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]);
  if ( !*((_BYTE *)v3 + 506) )
  {
    this->m_fTargetPosX = v3[108];
    this->m_fTargetPosY = v3[109];
    this->m_fTargetPosZ = v3[110];
    v4 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v28 = this->m_fTargetPosY - this->m_fCurPosY;
    v5 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBRoleAttackTable[41] = v28;
    *(float *)&v30 = v5;
    *(float *)&g_nCBRoleAttackTable[40] = v4;
    g_nCBRoleAttackTable[42] = v30;
    if ( (((gbVec3D *)&g_nCBRoleAttackTable[40]))->gbVec3D::Length() < 2.0 )
    {
      this->m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      return 0;
    }
    (((gbVec3D *)&g_nCBRoleAttackTable[40]))->gbVec3D::Normalize();
    v7 = acos(
           *(float *)&g_nCBRoleAttackTable[38] * *(float *)&g_nCBRoleAttackTable[42]
         + *(float *)&g_nCBRoleAttackTable[37] * *(float *)&g_nCBRoleAttackTable[41]
         + *(float *)&g_nCBRoleAttackTable[36] * *(float *)&g_nCBRoleAttackTable[40]);
    this->m_fAngleDegrees = v7;
    if ( *(float *)&g_nCBRoleAttackTable[40] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v7;
    this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
    LODWORD(this->m_fVelX) = g_nCBRoleAttackTable[40];
    LODWORD(this->m_fVelY) = g_nCBRoleAttackTable[41];
    LODWORD(this->m_fVelZ) = g_nCBRoleAttackTable[42];
    this->m_fVelX = this->m_fVelX * 380.0f;
    this->m_fVelY = this->m_fVelY * 380.0f;
    this->m_fVelZ = this->m_fVelZ * 380.0f;
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
      this->m_nAllDone = 31;
    else
      this->m_nAllDone = 52;
    this->CCBStage::IsGrabedBy();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    this->CCBStage::ClearBadPushTask(0.0099999998);
    v8 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
    this->m_TaskSlots[89] = 1;
    v9 = (float *)((char *)this + 96 * v8);
    if ( v9[108] >= -700.0f || v9[110] >= -700.0f )
    {
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWe011, 0);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        v10 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v10))->CScreenMode::AudioSetPosition(aWe011, 1);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(aWe011b, v26);
      }
    }
  }
  p_m_fCurPosX = (float *)&this->m_fCurPosX;
  m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
  v32 = this->m_fVelX * m_DeltaTime;
  v33 = this->m_fVelY * m_DeltaTime;
  v15 = v32 + this->m_fCurPosX;
  v29 = this->m_fCurPosY + v33;
  v16 = this->m_fCurPosZ + m_DeltaTime * this->m_fVelZ;
  this->m_fCurPosY = v29;
  v31 = v16;
  this->m_fCurPosX = v15;
  this->m_fCurPosZ = v31;
  v17 = this->m_fTargetPosX - this->m_fCurPosX;
  *(float *)&v34 = this->m_fTargetPosY - this->m_fCurPosY;
  v18 = this->m_fTargetPosZ - this->m_fCurPosZ;
  g_nCBRoleAttackTable[41] = v34;
  *(float *)&v35 = v18;
  *(float *)&g_nCBRoleAttackTable[40] = v17;
  g_nCBRoleAttackTable[42] = v35;
  if ( (((gbVec3D *)&g_nCBRoleAttackTable[40]))->gbVec3D::Length() >= 2.0 )
  {
    (((gbVec3D *)&g_nCBRoleAttackTable[40]))->gbVec3D::Normalize();
    v21 = acos(
            *(float *)&g_nCBRoleAttackTable[38] * *(float *)&g_nCBRoleAttackTable[42]
          + *(float *)&g_nCBRoleAttackTable[37] * *(float *)&g_nCBRoleAttackTable[41]
          + *(float *)&g_nCBRoleAttackTable[36] * *(float *)&g_nCBRoleAttackTable[40]);
    if ( *(float *)&g_nCBRoleAttackTable[40] < 0.0f )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    g_StageRoleData.m_nEffParam5 = v22;
    if ( fabs(v22 - this->m_fAngleDegrees) < 1.570796370506287 )
    {
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
        return 0;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        v24 = (CCBStage *)CScreenMode::GetInstance();
        (((CCBStage *)v24))->CCBStage::PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) != 4 )
      {
LABEL_43:
        this->m_TaskSlots[89] = 0;
        return 0;
      }
    }
    else
    {
      *p_m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        v23 = (CCBStage *)CScreenMode::GetInstance();
        (((CCBStage *)v23))->CCBStage::PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) != 4 )
        goto LABEL_43;
    }
    v25 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v25))->CCBStage::PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *p_m_fCurPosX = this->m_fTargetPosX;
  this->m_fCurPosY = this->m_fTargetPosY;
  this->m_fCurPosZ = this->m_fTargetPosZ;
  this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
  if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
  {
    v19 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v19))->CCBStage::PlaySound(aWe011, v27);
  }
  if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 )
  {
    v20 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v20))->CCBStage::PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C320
unsigned int CCBStage::ProcBlock(int dwMsg)
{
  float *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  int v8; // eax
  float *v9; // ecx
  CScreenMode *v10; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v12; // eax
  float *p_m_fCurPosX; // edi
  double m_DeltaTime; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  CCBStage *v19; // eax
  CCBStage *v20; // eax
  double v21; // st7
  double v22; // st7
  CCBStage *v23; // eax
  CCBStage *v24; // eax
  CCBStage *v25; // eax
  int v26; // [esp-0x4] [ebp-0x28]
  int v27; // [esp+0x0] [ebp-0x24]
  int v28; // [esp+0x10] [ebp-0x14]
  float v29; // [esp+0x10] [ebp-0x14]
  int v30; // [esp+0x14] [ebp-0x10]
  float v31; // [esp+0x14] [ebp-0x10]
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
  v3 = (float *)((char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]);
  if ( !*((_BYTE *)v3 + 506) )
  {
    this->m_fTargetPosX = v3[108];
    this->m_fTargetPosY = v3[109];
    this->m_fTargetPosZ = v3[110];
    v4 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v28 = this->m_fTargetPosY - this->m_fCurPosY;
    v5 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBRoleAttackTable[29] = v28;
    *(float *)&v30 = v5;
    *(float *)&g_nCBRoleAttackTable[28] = v4;
    g_nCBRoleAttackTable[30] = v30;
    if ( (((gbVec3D *)&g_nCBRoleAttackTable[28]))->gbVec3D::Length() < 2.0 )
    {
      this->m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      return 0;
    }
    (((gbVec3D *)&g_nCBRoleAttackTable[28]))->gbVec3D::Normalize();
    v7 = acos(
           *(float *)&g_nCBRoleAttackTable[26] * *(float *)&g_nCBRoleAttackTable[30]
         + *(float *)&g_nCBRoleAttackTable[25] * *(float *)&g_nCBRoleAttackTable[29]
         + *(float *)&g_nCBRoleAttackTable[24] * *(float *)&g_nCBRoleAttackTable[28]);
    this->m_fAngleDegrees = v7;
    if ( *(float *)&g_nCBRoleAttackTable[28] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v7;
    this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
    LODWORD(this->m_fVelX) = g_nCBRoleAttackTable[28];
    LODWORD(this->m_fVelY) = g_nCBRoleAttackTable[29];
    LODWORD(this->m_fVelZ) = g_nCBRoleAttackTable[30];
    this->m_fVelX = this->m_fVelX * 570.0f;
    this->m_fVelY = this->m_fVelY * 570.0f;
    this->m_fVelZ = this->m_fVelZ * 570.0f;
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
      this->m_nAllDone = 31;
    else
      this->m_nAllDone = 52;
    this->CCBStage::IsGrabedBy();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    this->CCBStage::ClearBadPushTask(0.0099999998);
    v8 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
    this->m_TaskSlots[89] = 1;
    v9 = (float *)((char *)this + 96 * v8);
    if ( v9[108] >= -700.0f || v9[110] >= -700.0f )
    {
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWe011, 0);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        v10 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v10))->CScreenMode::AudioSetPosition(aWe011, 1);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(aWe011b, v26);
      }
    }
  }
  p_m_fCurPosX = (float *)&this->m_fCurPosX;
  m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
  v32 = this->m_fVelX * m_DeltaTime;
  v33 = this->m_fVelY * m_DeltaTime;
  v15 = v32 + this->m_fCurPosX;
  v29 = this->m_fCurPosY + v33;
  v16 = this->m_fCurPosZ + m_DeltaTime * this->m_fVelZ;
  this->m_fCurPosY = v29;
  v31 = v16;
  this->m_fCurPosX = v15;
  this->m_fCurPosZ = v31;
  v17 = this->m_fTargetPosX - this->m_fCurPosX;
  *(float *)&v34 = this->m_fTargetPosY - this->m_fCurPosY;
  v18 = this->m_fTargetPosZ - this->m_fCurPosZ;
  g_nCBRoleAttackTable[29] = v34;
  *(float *)&v35 = v18;
  *(float *)&g_nCBRoleAttackTable[28] = v17;
  g_nCBRoleAttackTable[30] = v35;
  if ( (((gbVec3D *)&g_nCBRoleAttackTable[28]))->gbVec3D::Length() >= 2.0 )
  {
    (((gbVec3D *)&g_nCBRoleAttackTable[28]))->gbVec3D::Normalize();
    v21 = acos(
            *(float *)&g_nCBRoleAttackTable[26] * *(float *)&g_nCBRoleAttackTable[30]
          + *(float *)&g_nCBRoleAttackTable[25] * *(float *)&g_nCBRoleAttackTable[29]
          + *(float *)&g_nCBRoleAttackTable[24] * *(float *)&g_nCBRoleAttackTable[28]);
    if ( *(float *)&g_nCBRoleAttackTable[28] < 0.0f )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    g_StageRoleData._todo_074 = v22;
    if ( fabs(v22 - this->m_fAngleDegrees) < 1.570796370506287 )
    {
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
        return 0;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        v24 = (CCBStage *)CScreenMode::GetInstance();
        (((CCBStage *)v24))->CCBStage::PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) != 4 )
      {
LABEL_43:
        this->m_TaskSlots[89] = 0;
        return 0;
      }
    }
    else
    {
      *p_m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      {
        v23 = (CCBStage *)CScreenMode::GetInstance();
        (((CCBStage *)v23))->CCBStage::PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) != 4 )
        goto LABEL_43;
    }
    v25 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v25))->CCBStage::PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *p_m_fCurPosX = this->m_fTargetPosX;
  this->m_fCurPosY = this->m_fTargetPosY;
  this->m_fCurPosZ = this->m_fTargetPosZ;
  this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
  if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
  {
    v19 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v19))->CCBStage::PlaySound(aWe011, v27);
  }
  if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 )
  {
    v20 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v20))->CCBStage::PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C970
unsigned int CCBStage::ProcMagic(unsigned int dwMsg)
{
  float *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  int v8; // ecx
  CScreenMode *Instance; // eax
  double v10; // st7
  char *v11; // ecx
  double v12; // st7
  double v13; // st7
  CCBStage *v14; // eax
  CCBStage *v15; // eax
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
  v19 = 1.0f;
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 23) )
    v19 = 0.4399999976158142f;
  v3 = (float *)((char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]);
  if ( !*((_BYTE *)v3 + 506) )
  {
    this->m_fTargetPosX = v3[108];
    this->m_fTargetPosY = v3[109];
    this->m_fTargetPosZ = v3[110];
    v4 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v20 = this->m_fTargetPosY - this->m_fCurPosY;
    v5 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBRoleAttackTable[17] = v20;
    *(float *)&v21 = v5;
    *(float *)&g_nCBRoleAttackTable[16] = v4;
    g_nCBRoleAttackTable[18] = v21;
    if ( (((gbVec3D *)&g_nCBRoleAttackTable[16]))->gbVec3D::Length() < 2.0 )
    {
      this->CCBStage::ClearAniMsg(0, 1.0);
      this->m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      return 0;
    }
    (((gbVec3D *)&g_nCBRoleAttackTable[16]))->gbVec3D::Normalize();
    v7 = acos(
           *(float *)&g_nCBRoleAttackTable[14] * *(float *)&g_nCBRoleAttackTable[18]
         + *(float *)&g_nCBRoleAttackTable[13] * *(float *)&g_nCBRoleAttackTable[17]
         + *(float *)&g_nCBRoleAttackTable[12] * *(float *)&g_nCBRoleAttackTable[16]);
    this->m_fAngleDegrees = v7;
    if ( *(float *)&g_nCBRoleAttackTable[16] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v7;
    v8 = 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
    this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
    this->m_TaskArrC[0]._todo_018[v8 + 202] = 1;
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] = 1065353216;
    this->m_nAllDone = 32;
    this->CCBStage::IsGrabedBy();
    *(float *)&nVal3 = this->m_fCurPosY - 20.0;
    if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) )
      (((CEffMgr *)this->m_pCBSystem->m_pUtil->m_pEffMgr))->CEffMgr::Init(221, LODWORD(this->m_fCurPosX), nVal3, LODWORD(this->m_fCurPosZ), 0);
    else
      (((CEffMgr *)this->m_pCBSystem->m_pUtil->m_pEffMgr))->CEffMgr::Init(222, LODWORD(this->m_fCurPosX), nVal3, LODWORD(this->m_fCurPosZ), 0);
    this->CCBStage::ClearBadPushTask(0.0099999998);
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWe014, 1);
  }
  v10 = this->CCBStage::PushBackAllTask();
  v11 = (char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
  if ( *((float *)v11 + 122) <= 0.0 )
  {
    v13 = this->m_pCBSystem->m_pUtil->m_DeltaTime * 2.5 + v10;
    fVal = v13;
    if ( v13 >= v19 )
    {
      fVal = v19;
      v11[505] = 1;
      v14 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v14))->CCBStage::PlaySound(aWe014, v17);
    }
  }
  else
  {
    v12 = v10 - this->m_pCBSystem->m_pUtil->m_DeltaTime * 2.5;
    fVal = v12;
    if ( v12 < 0.0 )
    {
      *((_DWORD *)v11 + 122) = -1054867456;
      this->m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      this->m_fAngleDegrees = this->m_fCombatAnimY;
    }
  }
  if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
  {
    fVal = v19;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    v15 = (CCBStage *)CScreenMode::GetInstance();
    (((CCBStage *)v15))->CCBStage::PlaySound(aWe014, v17);
  }
  if ( fVal < 1.0f )
    this->CCBStage::ClearAniMsg(1, fVal);
  else
    this->CCBStage::ClearAniMsg(0, 1.0);
  return 0;
}

// 0x0050CDE0
unsigned int CCBStage::ProcUseRecoverItem(float dwMsg)
{
  char *v3; // eax
  int v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  unsigned int result; // eax
  long double v9; // st7
  double v10; // st7
  float v11; // edi
  float m_fSlot0; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v14; // eax
  double v15; // st7
  double v16; // st6
  double m_DeltaTime; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  float v21; // eax
  CCBStage *v22; // eax
  CCBStage *v23; // eax
  float v24; // eax
  CCBStage *v25; // eax
  CCBStage *v26; // eax
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
  v3 = (char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
  if ( v3[506] )
  {
    v11 = dwMsg;
  }
  else
  {
    *((_DWORD *)v3 + 122) = -1054867456;
    v4 = 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
    this->m_fTargetPosX = *(float *)&this->m_TaskArrC[0]._todo_018[v4 + 128];
    this->m_fTargetPosY = *(float *)&this->m_TaskArrC[0]._todo_018[v4 + 132];
    this->m_fTargetPosZ = *(float *)&this->m_TaskArrC[0]._todo_018[v4 + 136];
    v5 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v29 = this->m_fTargetPosY - this->m_fCurPosY;
    v6 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBRoleAttackTable[9] = v29;
    *(float *)&v32 = v6;
    *(float *)&g_nCBRoleAttackTable[8] = v5;
    g_nCBRoleAttackTable[10] = v32;
    v7 = (((gbVec3D *)&g_nCBRoleAttackTable[8]))->gbVec3D::Length();
    dwMsga = v7;
    if ( v7 < 2.0 )
    {
      this->m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      result = 0;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      return result;
    }
    (((gbVec3D *)&g_nCBRoleAttackTable[8]))->gbVec3D::Normalize();
    v9 = acos(
           *(float *)&g_nCBRoleAttackTable[6] * *(float *)&g_nCBRoleAttackTable[10]
         + *(float *)&g_nCBRoleAttackTable[5] * *(float *)&g_nCBRoleAttackTable[9]
         + *(float *)&g_nCBRoleAttackTable[4] * *(float *)&g_nCBRoleAttackTable[8]);
    this->m_fAngleDegrees = v9;
    if ( *(float *)&g_nCBRoleAttackTable[8] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v9;
    this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
    LODWORD(this->m_fVelX) = g_nCBRoleAttackTable[8];
    v10 = dwMsga + dwMsga;
    LODWORD(this->m_fVelY) = g_nCBRoleAttackTable[9];
    LODWORD(this->m_fVelZ) = g_nCBRoleAttackTable[10];
    this->m_fVelX = v10 * this->m_fVelX;
    this->m_fVelY = v10 * this->m_fVelY;
    this->m_fVelZ = v10 * this->m_fVelZ;
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
      this->m_nAllDone = 31;
    else
      this->m_nAllDone = 52;
    this->CCBStage::IsGrabedBy();
    v11 = 0.0f;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    this->CCBStage::ClearBadPushTask(0.0099999998);
    m_fSlot0 = this->m_TaskArrC[0].m_fSlot0;
    this->m_TaskSlots[89] = 1;
    if ( LODWORD(m_fSlot0) == 1 )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWe012, 1);
    }
    if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 3 )
    {
      v14 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(aWe013, 1);
    }
  }
  v15 = this->m_fTargetPosX - this->m_fCurPosX;
  *(float *)&v30 = this->m_fTargetPosY - this->m_fCurPosY;
  v16 = this->m_fTargetPosZ - this->m_fCurPosZ;
  g_nCBRoleAttackTable[9] = v30;
  *(float *)&v33 = v16;
  *(float *)&g_nCBRoleAttackTable[8] = v15;
  g_nCBRoleAttackTable[10] = v33;
  if ( LODWORD(v11) == this->m_nDoneCount )
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] = 1120403456;
  if ( *(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] > 0.0f
    && (((gbVec3D *)&g_nCBRoleAttackTable[8]))->gbVec3D::Length() > 2.0 )
  {
    m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
    v28 = this->m_fVelX * m_DeltaTime;
    v31 = this->m_fVelY * m_DeltaTime;
    v18 = m_DeltaTime * this->m_fVelZ;
    this->m_fCurPosX = v28 + this->m_fCurPosX;
    this->m_fCurPosY = v31 + this->m_fCurPosY;
    this->m_fCurPosZ = v18 + this->m_fCurPosZ;
  }
  if ( LODWORD(v11) == this->m_nTotalCount && (((gbVec3D *)&g_nCBRoleAttackTable[8]))->gbVec3D::Length() <= 2.0 )
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] = -1054867456;
  (((gbVec3D *)&g_nCBRoleAttackTable[8]))->gbVec3D::Normalize();
  v19 = acos(
          *(float *)&g_nCBRoleAttackTable[6] * *(float *)&g_nCBRoleAttackTable[10]
        + *(float *)&g_nCBRoleAttackTable[5] * *(float *)&g_nCBRoleAttackTable[9]
        + *(float *)&g_nCBRoleAttackTable[4] * *(float *)&g_nCBRoleAttackTable[8]);
  if ( *(float *)&g_nCBRoleAttackTable[8] < 0.0f )
    v19 = 6.2831855 - v19;
  v20 = v19 * 57.29578;
  g_StageRoleData.m_nEffParam6 = v20;
  if ( fabs(v20 - this->m_fAngleDegrees) >= 1.570796370506287 )
  {
    this->m_fCurPosX = this->m_fTargetPosX;
    this->m_fCurPosY = this->m_fTargetPosY;
    this->m_fCurPosZ = this->m_fTargetPosZ;
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] = -1054867456;
  }
  if ( LODWORD(v11) == this->m_nBattleResult )
  {
    this->m_fCurPosX = this->m_fTargetPosX;
    this->m_fCurPosY = this->m_fTargetPosY;
    this->m_fCurPosZ = this->m_fTargetPosZ;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    v21 = this->m_TaskArrC[0].m_fSlot0;
    this->m_TaskSlots[89] = 0;
    if ( LODWORD(v21) == 1 )
    {
      v22 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v22))->CCBStage::PlaySound(aWe012, v27);
    }
    if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 3 )
    {
      v23 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v23))->CCBStage::PlaySound(aWe013, v27);
    }
  }
  if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
  {
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    v24 = this->m_TaskArrC[0].m_fSlot0;
    this->m_TaskSlots[89] = 0;
    if ( LODWORD(v24) == 1 )
    {
      v25 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v25))->CCBStage::PlaySound(aWe012, v27);
    }
    if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 3 )
    {
      v26 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v26))->CCBStage::PlaySound(aWe013, v27);
    }
  }
  return 0;
}

// 0x0050D440
int CCBStage::CheckAllDone()
{
  char *v2; // eax
  int v3; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st7
  int result; // eax
  double v8; // st7
  int v9; // edi
  float m_fSlot0; // eax
  CScreenMode *Instance; // eax
  double v12; // st7
  double v13; // st6
  double m_DeltaTime; // st7
  double v15; // st7
  float v16; // eax
  CCBStage *v17; // eax
  float v18; // eax
  CCBStage *v19; // eax
  int v20; // [esp+0x0] [ebp-0x14]
  float v21; // [esp+0x8] [ebp-0xC]
  int v22; // [esp+0xC] [ebp-0x8]
  int v23; // [esp+0xC] [ebp-0x8]
  float v24; // [esp+0xC] [ebp-0x8]
  int v25; // [esp+0x10] [ebp-0x4]
  int v26; // [esp+0x10] [ebp-0x4]
  int v27; // [esp+0x18] [ebp+0x4]
  float v28; // [esp+0x18] [ebp+0x4]

  if ( (g_nCBFormation4[11] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation4[11]) |= 1u;
    g_nCBFormation4[8] = 0;
    g_nCBFormation4[9] = 0;
    g_nCBFormation4[10] = 0;
    atexit(nullsub_57);
  }
  if ( (g_nCBFormation4[11] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation4[11]) |= 2u;
    g_nCBFormation4[4] = 0;
    g_nCBFormation4[5] = 0;
    g_nCBFormation4[6] = 1065353216;
    atexit(nullsub_56);
  }
  if ( (g_nCBFormation4[11] & 4) == 0 )
  {
    LOBYTE(g_nCBFormation4[11]) |= 4u;
    g_nCBFormation4[0] = 0;
    g_nCBFormation4[1] = 0;
    g_nCBFormation4[2] = 0;
    atexit(nullsub_55);
  }
  v2 = (char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
  if ( v2[506] )
  {
    v9 = v27;
  }
  else
  {
    *((_DWORD *)v2 + 122) = -1054867456;
    v3 = 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
    this->m_fTargetPosX = *(float *)&this->m_TaskArrC[0]._todo_018[v3 + 128];
    this->m_fTargetPosY = *(float *)&this->m_TaskArrC[0]._todo_018[v3 + 132];
    this->m_fTargetPosZ = *(float *)&this->m_TaskArrC[0]._todo_018[v3 + 136];
    v4 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v22 = this->m_fTargetPosY - this->m_fCurPosY;
    v5 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBFormation4[9] = v22;
    *(float *)&v25 = v5;
    *(float *)&g_nCBFormation4[8] = v4;
    g_nCBFormation4[10] = v25;
    v6 = (((gbVec3D *)&g_nCBFormation4[8]))->gbVec3D::Length();
    if ( v6 < 2.0 )
    {
      this->m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      result = 0;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      return result;
    }
    (((gbVec3D *)&g_nCBFormation4[8]))->gbVec3D::Normalize();
    *(&g_StageRoleData.m_nEffParam6 + 1) = acos(
                                             *(float *)&g_nCBFormation4[6] * *(float *)&g_nCBFormation4[10]
                                           + *(float *)&g_nCBFormation4[5] * *(float *)&g_nCBFormation4[9]
                                           + *(float *)&g_nCBFormation4[4] * *(float *)&g_nCBFormation4[8]);
    if ( *(float *)&g_nCBFormation4[8] < 0.0f )
      *(&g_StageRoleData.m_nEffParam6 + 1) = 6.2831855 - *(&g_StageRoleData.m_nEffParam6 + 1);
    *(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 188] = *(&g_StageRoleData.m_nEffParam6 + 1) * 57.29578;
    LODWORD(this->m_fVelX) = g_nCBFormation4[8];
    v28 = v6;
    v8 = v28 + v28;
    LODWORD(this->m_fVelY) = g_nCBFormation4[9];
    LODWORD(this->m_fVelZ) = g_nCBFormation4[10];
    this->m_fVelX = v8 * this->m_fVelX;
    this->m_fVelY = v8 * this->m_fVelY;
    this->m_fVelZ = v8 * this->m_fVelZ;
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
      this->m_nAllDone = 31;
    else
      this->m_nAllDone = 52;
    this->CCBStage::IsGrabedBy();
    v9 = 0;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    this->CCBStage::ClearBadPushTask(0.40000001);
    m_fSlot0 = this->m_TaskArrC[0].m_fSlot0;
    this->m_TaskSlots[89] = 1;
    if ( LODWORD(m_fSlot0) == 3 )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWe013, 1);
    }
  }
  v12 = this->m_fTargetPosX - this->m_fCurPosX;
  *(float *)&v23 = this->m_fTargetPosY - this->m_fCurPosY;
  v13 = this->m_fTargetPosZ - this->m_fCurPosZ;
  g_nCBFormation4[9] = v23;
  *(float *)&v26 = v13;
  *(float *)&g_nCBFormation4[8] = v12;
  g_nCBFormation4[10] = v26;
  if ( v9 == this->m_nDoneCount )
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] = 1120403456;
  if ( *(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] > 0.0f
    && (((gbVec3D *)&g_nCBFormation4[8]))->gbVec3D::Length() > 2.0 )
  {
    m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
    v21 = this->m_fVelX * m_DeltaTime;
    v24 = this->m_fVelY * m_DeltaTime;
    v15 = m_DeltaTime * this->m_fVelZ;
    this->m_fCurPosX = v21 + this->m_fCurPosX;
    this->m_fCurPosY = v24 + this->m_fCurPosY;
    this->m_fCurPosZ = v15 + this->m_fCurPosZ;
    this->m_fAngleDegrees = this->m_pCBSystem->m_pUtil->m_DeltaTime * 720.0f + this->m_fAngleDegrees;
  }
  if ( v9 == this->m_nTotalCount && (((gbVec3D *)&g_nCBFormation4[8]))->gbVec3D::Length() <= 2.0 )
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] = -1054867456;
  (((gbVec3D *)&g_nCBFormation4[8]))->gbVec3D::Normalize();
  *(&g_StageRoleData.m_nEffParam6 + 1) = acos(
                                           *(float *)&g_nCBFormation4[6] * *(float *)&g_nCBFormation4[10]
                                         + *(float *)&g_nCBFormation4[5] * *(float *)&g_nCBFormation4[9]
                                         + *(float *)&g_nCBFormation4[4] * *(float *)&g_nCBFormation4[8]);
  if ( *(float *)&g_nCBFormation4[8] < 0.0f )
    *(&g_StageRoleData.m_nEffParam6 + 1) = 6.2831855 - *(&g_StageRoleData.m_nEffParam6 + 1);
  if ( fabs(
         *(&g_StageRoleData.m_nEffParam6 + 1) * 57.29578
       - *(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 188]) >= 1.570796370506287 )
  {
    this->m_fCurPosX = this->m_fTargetPosX;
    this->m_fCurPosY = this->m_fTargetPosY;
    this->m_fCurPosZ = this->m_fTargetPosZ;
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 184] = -1054867456;
  }
  if ( v9 == this->m_nBattleResult )
  {
    this->m_fCurPosX = this->m_fTargetPosX;
    this->m_fCurPosY = this->m_fTargetPosY;
    this->m_fCurPosZ = this->m_fTargetPosZ;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    v16 = this->m_TaskArrC[0].m_fSlot0;
    this->m_TaskSlots[89] = 0;
    if ( LODWORD(v16) == 3 )
    {
      v17 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v17))->CCBStage::PlaySound(aWe013, v20);
    }
  }
  if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
  {
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    v18 = this->m_TaskArrC[0].m_fSlot0;
    this->m_TaskSlots[89] = 0;
    if ( LODWORD(v18) == 3 )
    {
      v19 = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)v19))->CCBStage::PlaySound(aWe013, v20);
    }
  }
  return 0;
}

// 0x0050DA90
int CCBStage::UpdateSlotTimer(int nVal)
{
  double v3; // st7
  float *p_m_fTargetPosX; // edi
  double v5; // st6
  double v6; // st7
  double v7; // st6
  double v8; // st7
  double v9; // st6
  int result; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st6
  long double v15; // st7
  float *p_m_fCurPosX; // edi
  double m_DeltaTime; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st7
  float v24; // [esp+0xC] [ebp-0x2C]
  float v25; // [esp+0x10] [ebp-0x28]
  float v26; // [esp+0x10] [ebp-0x28]
  int v27; // [esp+0x10] [ebp-0x28]
  float v28; // [esp+0x10] [ebp-0x28]
  int v29; // [esp+0x10] [ebp-0x28]
  float v30; // [esp+0x10] [ebp-0x28]
  int v31; // [esp+0x10] [ebp-0x28]
  float v32; // [esp+0x14] [ebp-0x24]
  float v33; // [esp+0x14] [ebp-0x24]
  int v34; // [esp+0x14] [ebp-0x24]
  float v35; // [esp+0x14] [ebp-0x24]
  int v36; // [esp+0x14] [ebp-0x24]
  int v37; // [esp+0x14] [ebp-0x24]
  float v38; // [esp+0x24] [ebp-0x14]
  float v39; // [esp+0x28] [ebp-0x10]
  float v40; // [esp+0x28] [ebp-0x10]
  float v41; // [esp+0x2C] [ebp-0xC]
  float v42; // [esp+0x2C] [ebp-0xC]
  float v43; // [esp+0x30] [ebp-0x8]

  if ( (g_nCBFormation3[11] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation3[11]) |= 1u;
    g_nCBFormation3[8] = 0;
    g_nCBFormation3[9] = 0;
    g_nCBFormation3[10] = 0;
    atexit(nullsub_60);
  }
  if ( (g_nCBFormation3[11] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation3[11]) |= 2u;
    g_nCBFormation3[4] = 0;
    g_nCBFormation3[5] = 0;
    g_nCBFormation3[6] = 1065353216;
    atexit(nullsub_59);
  }
  if ( (g_nCBFormation3[11] & 4) == 0 )
  {
    LOBYTE(g_nCBFormation3[11]) |= 4u;
    g_nCBFormation3[0] = 0;
    g_nCBFormation3[1] = 0;
    g_nCBFormation3[2] = 0;
    atexit(nullsub_58);
  }
  LODWORD(g_StageRoleData.m_fRoleTargetParam) = (int)*(float *)&this->m_TaskArrC[0]._todo_018[96
                                                                                            * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]
                                                                                            + 128];
  v43 = *(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 132];
  g_StageRoleData.m_nEffParam8 = (int)v43;
  if ( !this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    v38 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + LODWORD(g_StageRoleData.m_fRoleTargetParam)) + 6596);
    v39 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + LODWORD(g_StageRoleData.m_fRoleTargetParam)) + 6600);
    v3 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + (int)v43) + 6596) - v38;
    v41 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + LODWORD(g_StageRoleData.m_fRoleTargetParam)) + 6604);
    p_m_fTargetPosX = (float *)&this->m_fTargetPosX;
    v25 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + (int)v43) + 6600) - v39;
    v5 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + (int)v43) + 6604) - v41;
    this->m_fTargetPosY = v25;
    v32 = v5;
    this->m_fTargetPosX = v3;
    this->m_fTargetPosZ = v32;
    (((gbVec3D *)&this->m_fTargetPosX))->gbVec3D::Normalize();
    this->m_fTargetPosX = this->m_fTargetPosX * 32.0f;
    this->m_fTargetPosY = this->m_fTargetPosY * 32.0f;
    this->m_fTargetPosZ = this->m_fTargetPosZ * 32.0f;
    v6 = v38 + this->m_fTargetPosX;
    v26 = v39 + this->m_fTargetPosY;
    v7 = v41 + this->m_fTargetPosZ;
    this->m_fTargetPosY = v26;
    v33 = v7;
    this->m_fTargetPosX = v6;
    this->m_fTargetPosZ = v33;
    v8 = this->m_fCurPosX - this->m_fTargetPosX;
    *(float *)&v27 = this->m_fCurPosY - this->m_fTargetPosY;
    v9 = this->m_fCurPosZ - this->m_fTargetPosZ;
    g_nCBFormation3[9] = v27;
    *(float *)&v34 = v9;
    *(float *)&g_nCBFormation3[8] = v8;
    g_nCBFormation3[10] = v34;
    if ( (((gbVec3D *)&g_nCBFormation3[8]))->gbVec3D::Length() < 4.0 )
    {
      this->m_fCurPosX = *p_m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      result = 0;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      return result;
    }
    (((gbVec3D *)&g_nCBFormation3[8]))->gbVec3D::Normalize();
    *(float *)&g_nCBFormation3[8] = *(float *)&g_nCBFormation3[8] * 10.0;
    *(float *)&g_nCBFormation3[9] = *(float *)&g_nCBFormation3[9] * 10.0;
    *(float *)&g_nCBFormation3[10] = *(float *)&g_nCBFormation3[10] * 10.0;
    v11 = *(float *)&g_nCBFormation3[8] + *p_m_fTargetPosX;
    v28 = *(float *)&g_nCBFormation3[9] + this->m_fTargetPosY;
    v12 = *(float *)&g_nCBFormation3[10] + this->m_fTargetPosZ;
    this->m_fTargetPosY = v28;
    v35 = v12;
    *p_m_fTargetPosX = v11;
    this->m_fTargetPosZ = v35;
    v13 = *p_m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v29 = this->m_fTargetPosY - this->m_fCurPosY;
    v14 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBFormation3[9] = v29;
    *(float *)&v36 = v14;
    *(float *)&g_nCBFormation3[8] = v13;
    g_nCBFormation3[10] = v36;
    (((gbVec3D *)&g_nCBFormation3[8]))->gbVec3D::Normalize();
    v15 = acos(
            *(float *)&g_nCBFormation3[5] * *(float *)&g_nCBFormation3[9]
          + *(float *)&g_nCBFormation3[6] * *(float *)&g_nCBFormation3[10]
          + *(float *)&g_nCBFormation3[4] * *(float *)&g_nCBFormation3[8]);
    this->m_fAngleDegrees = v15;
    if ( *(float *)&g_nCBFormation3[8] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v15;
    this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
    LODWORD(this->m_fVelX) = g_nCBFormation3[8];
    LODWORD(this->m_fVelY) = g_nCBFormation3[9];
    LODWORD(this->m_fVelZ) = g_nCBFormation3[10];
    this->m_fVelX = this->m_fVelX * 480.0f;
    this->m_fVelY = this->m_fVelY * 480.0f;
    this->m_fVelZ = this->m_fVelZ * 480.0f;
    this->m_nAllDone = 31;
    this->CCBStage::IsGrabedBy();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    this->m_TaskSlots[89] = 1;
  }
  p_m_fCurPosX = (float *)&this->m_fCurPosX;
  m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
  v24 = this->m_fVelX * m_DeltaTime;
  v30 = this->m_fVelY * m_DeltaTime;
  v18 = v24 + this->m_fCurPosX;
  v40 = this->m_fCurPosY + v30;
  v19 = this->m_fCurPosZ + m_DeltaTime * this->m_fVelZ;
  this->m_fCurPosY = v40;
  v42 = v19;
  this->m_fCurPosX = v18;
  this->m_fCurPosZ = v42;
  v20 = this->m_fTargetPosX - this->m_fCurPosX;
  *(float *)&v31 = this->m_fTargetPosY - this->m_fCurPosY;
  v21 = this->m_fTargetPosZ - this->m_fCurPosZ;
  g_nCBFormation3[9] = v31;
  *(float *)&v37 = v21;
  *(float *)&g_nCBFormation3[8] = v20;
  g_nCBFormation3[10] = v37;
  if ( (((gbVec3D *)&g_nCBFormation3[8]))->gbVec3D::Length() >= 4.0 )
  {
    (((gbVec3D *)&g_nCBFormation3[8]))->gbVec3D::Normalize();
    v22 = acos(
            *(float *)&g_nCBFormation3[5] * *(float *)&g_nCBFormation3[9]
          + *(float *)&g_nCBFormation3[6] * *(float *)&g_nCBFormation3[10]
          + *(float *)&g_nCBFormation3[4] * *(float *)&g_nCBFormation3[8]);
    if ( *(float *)&g_nCBFormation3[8] < 0.0f )
      v22 = 6.2831855 - v22;
    v23 = v22 * 57.29578;
    g_StageRoleData.m_nEffParam7 = v23;
    if ( fabs(v23 - this->m_fAngleDegrees) >= 1.570796370506287 )
    {
      *p_m_fCurPosX = this->m_fTargetPosX;
      this->m_fCurPosY = this->m_fTargetPosY;
      this->m_fCurPosZ = this->m_fTargetPosZ;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      this->m_TaskSlots[89] = 0;
    }
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
    {
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      this->m_TaskSlots[89] = 0;
    }
    return 0;
  }
  else
  {
    *p_m_fCurPosX = this->m_fTargetPosX;
    this->m_fCurPosY = this->m_fTargetPosY;
    this->m_fCurPosZ = this->m_fTargetPosZ;
    result = 0;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
  }
  return result;
}

// 0x0050E0D0
int CCBStage::ProcessCommand(int nVal1)
{
  float *v3; // eax
  int m_fSlot0_low; // edx

  v3 = (float *)((char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]);
  if ( !*((_BYTE *)v3 + 506) )
  {
    m_fSlot0_low = LODWORD(this->m_TaskArrC[0].m_fSlot0);
    this->m_fAngleDegrees = v3[108];
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(m_fSlot0_low) )
      this->m_nAllDone = 32;
    else
      this->m_nAllDone = 50;
    this->CCBStage::IsGrabedBy();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
  }
  return 0;
}

// 0x0050E160
int CCBStage::UpdateTaskNormals(int nVal)
{
  float *v3; // eax
  float *v4; // eax
  float v5; // st7
  float v6; // st6
  long double v7; // st7
  int v8; // edx
  int result; // eax
  int v10; // [esp+0x8] [ebp-0x8]
  int v11; // [esp+0xC] [ebp-0x4]

  if ( (g_nCBFormation2[15] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation2[15]) |= 1u;
    g_nCBFormation2[12] = 0;
    g_nCBFormation2[13] = 0;
    g_nCBFormation2[14] = 0;
    atexit(nullsub_62);
  }
  if ( (g_nCBFormation2[15] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation2[15]) |= 2u;
    g_nCBFormation2[8] = 0;
    g_nCBFormation2[9] = 0;
    g_nCBFormation2[10] = 1065353216;
    atexit(nullsub_61);
  }
  v3 = (float *)((char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]);
  if ( !*((_BYTE *)v3 + 506) )
  {
    v4 = (float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + (__int64)v3[108]) + 6584);
    this->m_fTargetPosX = *v4;
    this->m_fTargetPosY = v4[1];
    this->m_fTargetPosZ = v4[2];
    v5 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v10 = this->m_fTargetPosY - this->m_fCurPosY;
    v6 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBFormation2[13] = v10;
    *(float *)&v11 = v6;
    *(float *)&g_nCBFormation2[12] = v5;
    g_nCBFormation2[14] = v11;
    (((gbVec3D *)&g_nCBFormation2[12]))->gbVec3D::Normalize();
    v7 = acos(
           *(float *)&g_nCBFormation2[10] * *(float *)&g_nCBFormation2[14]
         + *(float *)&g_nCBFormation2[9] * *(float *)&g_nCBFormation2[13]
         + *(float *)&g_nCBFormation2[8] * *(float *)&g_nCBFormation2[12]);
    this->m_fAngleDegrees = v7;
    if ( *(float *)&g_nCBFormation2[12] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v7;
  }
  v8 = 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
  result = 0;
  this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
  this->m_TaskArrC[0]._todo_018[v8 + 201] = 1;
  return result;
}

// 0x0050E360
int CCBStage::CalcFacingAngle(int nVal)
{
  float *v3; // eax
  float v4; // st7
  float v5; // st6
  long double v6; // st7
  int v7; // eax
  int v9; // [esp+0x8] [ebp-0x8]
  int v10; // [esp+0xC] [ebp-0x4]

  if ( (g_nCBFormation2[7] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation2[7]) |= 1u;
    g_nCBFormation2[4] = 0;
    g_nCBFormation2[5] = 0;
    g_nCBFormation2[6] = 0;
    atexit(nullsub_64);
  }
  if ( (g_nCBFormation2[7] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation2[7]) |= 2u;
    g_nCBFormation2[0] = 0;
    g_nCBFormation2[1] = 0;
    g_nCBFormation2[2] = 1065353216;
    atexit(nullsub_63);
  }
  v3 = (float *)((char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]);
  if ( !*((_BYTE *)v3 + 506) )
  {
    this->m_fTargetPosX = v3[108];
    this->m_fTargetPosY = v3[109];
    this->m_fTargetPosZ = v3[110];
    v4 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v9 = this->m_fTargetPosY - this->m_fCurPosY;
    v5 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBFormation2[5] = v9;
    *(float *)&v10 = v5;
    *(float *)&g_nCBFormation2[4] = v4;
    g_nCBFormation2[6] = v10;
    (((gbVec3D *)&g_nCBFormation2[4]))->gbVec3D::Normalize();
    v6 = acos(
           *(float *)&g_nCBFormation2[2] * *(float *)&g_nCBFormation2[6]
         + *(float *)&g_nCBFormation2[1] * *(float *)&g_nCBFormation2[5]
         + *(float *)g_nCBFormation2 * *(float *)&g_nCBFormation2[4]);
    this->m_fAngleDegrees = v6;
    if ( *(float *)&g_nCBFormation2[4] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v6;
  }
  v7 = 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
  this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
  this->m_TaskArrC[0]._todo_018[v7 + 201] = 1;
  return 0;
}

// 0x0050E550
int CCBStage::ResolveActionEffect(int nVal)
{
  char v3; // bl
  char *v4; // ebp
  int i; // edi
  float m_fSlot0; // eax
  unsigned int v7; // ebp
  float v8; // eax
  int v10; // edi
  CScreenMode *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  tagRoleState *inited; // eax
  int v18; // eax
  int v19; // edi
  unsigned int v20; // ecx
  int *v21; // ecx
  int v22; // eax
  CScreenMode *Instance; // eax
  int m_nActionFilterA; // ecx
  float v25; // eax
  int v26; // edi
  float *v27; // edi
  char *v28; // [esp-0x8] [ebp-0x44]
  char *v29; // [esp-0x8] [ebp-0x44]
  char *v30; // [esp-0x8] [ebp-0x44]
  void *v31; // [esp+0x0] [ebp-0x3C]
  char Buffer[32]; // [esp+0x1C] [ebp-0x20] BYREF

  v3 = 1;
  v4 = (char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
  if ( !v4[506] )
  {
    this->CCBStage::ClearBadPushTask(0.25);
    if ( v4[461] )
    {
      for ( i = 0; i < 11; ++i )
      {
        if ( v4[i + 473] && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(i) )
          v3 = 0;
      }
      if ( !v3 )
        goto LABEL_10;
    }
    else if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(*((_DWORD *)v4 + 114)) )
    {
      goto LABEL_10;
    }
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
LABEL_10:
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
    {
      m_fSlot0 = this->m_TaskArrC[0].m_fSlot0;
      this->m_nAllDone = 29;
      if ( LODWORD(m_fSlot0) == 2 )
      {
        if ( *(_BYTE *)(*(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 58) + 613) == 7 )
        {
          this->m_nAllDone = 30;
        }
        else
        {
          v7 = *((_DWORD *)v4 + 114);
          if ( v7 <= 0xA )
            this->CCBStage::SetBladeTime(v7);
        }
      }
      v8 = this->m_TaskArrC[0].m_fSlot0;
      if ( LODWORD(v8) == 3 && *(_BYTE *)(g_RoleSlotBuf.m_teamData3[98] + 613) == 4 )
        this->m_nAllDone = 30;
      if ( LODWORD(v8) == 4 && *(_BYTE *)(*(&g_RoleSlotBuf.dword_17AA450 + 12) + 613) == 2 )
        this->m_nAllDone = 30;
    }
    else
    {
      this->m_nAllDone = 53;
    }
    this->CCBStage::GetPointerPos();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v31);
    return 0;
  }
  v10 = nVal;
  if ( nVal != this->m_nActionFilterA && nVal != this->m_nActionFilterB )
    goto LABEL_68;
  if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
  {
    inited = (((CCBRoleState *)this->m_pCBSystem->m_pUtil->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(inited->dwID);
    v19 = (__int64)*(float *)(v18 + 784);
    if ( v19 )
    {
      v20 = *((_DWORD *)v4 + 114);
      if ( v20 <= 0xA )
      {
        v21 = (int *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + v20) + 6596);
        switch ( v19 )
        {
          case 121:
            v22 = 324;
            goto LABEL_66;
          case 123:
            v22 = 325;
            goto LABEL_66;
          case 124:
            v22 = 326;
            goto LABEL_66;
          case 125:
            v22 = 327;
            goto LABEL_66;
          case 127:
            v22 = 328;
            goto LABEL_66;
          case 128:
            v22 = 329;
            goto LABEL_66;
          case 129:
            v22 = 330;
            goto LABEL_66;
          case 130:
            v22 = 331;
            goto LABEL_66;
          case 131:
            v22 = 332;
            goto LABEL_66;
          case 132:
            v22 = 333;
            goto LABEL_66;
          case 133:
            v22 = 334;
            goto LABEL_66;
          case 134:
            v22 = 335;
LABEL_66:
            (((CEffMgr *)this->m_pCBSystem->m_pUtil->m_pEffMgr))->CEffMgr::Init(v22, *v21, 0, v21[2], 0);
            break;
          default:
            break;
        }
      }
      sprintf(Buffer, (const char *)&g_EffMgrData._tail_000[168], aWd, v19);
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(Buffer, 1);
    }
LABEL_68:
    v10 = nVal;
    goto LABEL_69;
  }
  if ( !LODWORD(this->m_TaskArrC[0].m_fSlot0) )
  {
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->bMagicSword )
      v28 = aWd023;
    else
      v28 = aWd025;
    v11 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v11))->CScreenMode::AudioSetPosition(v28, 1);
  }
  if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 1 )
  {
    v12 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(aWd028, 1);
  }
  if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) != 2 )
    goto LABEL_42;
  if ( *(_BYTE *)(*(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 58) + 613) == 7 )
  {
    v29 = aWd030;
LABEL_41:
    v13 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v13))->CScreenMode::AudioSetPosition(v29, 1);
    goto LABEL_42;
  }
  if ( nVal == this->m_nActionFilterB )
  {
    v29 = aWd024;
    goto LABEL_41;
  }
LABEL_42:
  if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 3 )
  {
    if ( *(_BYTE *)(g_RoleSlotBuf.m_teamData3[98] + 613) == 4 )
      v30 = aWd027;
    else
      v30 = aWd026;
    v14 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(v30, 1);
  }
  if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) == 4 )
  {
    if ( *(_BYTE *)(*(&g_RoleSlotBuf.dword_17AA450 + 12) + 613) == 2 )
    {
      v15 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(aWd025, 1);
    }
    else
    {
      v16 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v16))->CScreenMode::AudioSetPosition(aWd029, 1);
    }
  }
LABEL_69:
  m_nActionFilterA = this->m_nActionFilterA;
  if ( v10 != m_nActionFilterA && v10 != this->m_nActionFilterB )
    goto LABEL_92;
  v25 = this->m_TaskArrC[0].m_fSlot0;
  if ( SLODWORD(v25) < 5 || SLODWORD(v25) >= 11 )
  {
    if ( LODWORD(v25) == 2 )
    {
      if ( v10 == m_nActionFilterA
        && *(_BYTE *)(*(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 58) + 613) == 5 )
      {
        goto LABEL_91;
      }
      if ( *(int *)(*(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 58) + 764) <= 1 )
        goto LABEL_74;
      v26 = *(_DWORD *)(*(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 58) + 764);
      do
      {
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 140]);
        --v26;
      }
      while ( v26 );
    }
    else
    {
      if ( v25 == 0.0f
        && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->bMagicSword
        && *(_DWORD *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[3][5] )
      {
        if ( !*(_DWORD *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[4][1] )
          *(_DWORD *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[4][1] = 1;
        v27 = (float *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[4][3];
        *v27 = (double)*(unsigned int *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[4][1] + *v27;
        if ( *(float *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[4][3] > 200.0f )
          *(_DWORD *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[4][3] = 1128792064;
      }
      (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 140]);
    }
    v10 = nVal;
    goto LABEL_91;
  }
  if ( v10 == m_nActionFilterA )
LABEL_74:
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::RandSetEnemyPos(&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 140]);
LABEL_91:
  *(_DWORD *)&this->m_TaskArrC[0]._todo_018[196] = 3;
LABEL_92:
  if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
    || v10 == this->m_nBattleResult )
  {
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
  }
  return 0;
}

// 0x0050EB00
int CCBStage::ProcessSlotAction(int nVal)
{
  int m_nAllDone; // eax
  tagRoleState *inited; // eax
  int v5; // eax
  float v6; // st7
  CScreenMode *Instance; // eax
  char *v9; // [esp-0x8] [ebp-0x38]
  void *v10; // [esp+0x0] [ebp-0x30]
  char Buffer[32]; // [esp+0x10] [ebp-0x20] BYREF

  if ( !this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    this->CCBStage::ClearBadPushTask(0.25);
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 14) )
    {
      m_nAllDone = this->m_nAllDone;
      if ( m_nAllDone == 33 || m_nAllDone == 43 || m_nAllDone == 54 )
      {
        (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16) + 24))(
          *(_DWORD *)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16),
          0);
      }
      else
      {
        if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
          this->m_nAllDone = LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))->byMagicUseTime[8][5]) != 0
                           ? 43
                           : 33;
        else
          this->m_nAllDone = 54;
        this->CCBStage::GetPointerPos();
      }
    }
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
    {
      if ( !LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))->byMagicUseTime[8][5]) )
      {
        switch ( LODWORD(this->m_TaskArrC[0].m_fSlot0) )
        {
          case 0:
            v9 = (char *)"we015";
            goto LABEL_22;
          case 1:
            v9 = (char *)"we016";
            goto LABEL_22;
          case 2:
            v9 = (char *)"we017";
            goto LABEL_22;
          case 3:
            v9 = (char *)"we018";
            goto LABEL_22;
          case 4:
            v9 = (char *)"we019";
            goto LABEL_22;
          default:
            goto LABEL_23;
        }
        goto LABEL_23;
      }
      v9 = aWe020;
    }
    else
    {
      Destroy__ovl_02((int)this->m_pCBSystem->m_pUtil->m_pEffectSimple);
      inited = (((CCBRoleState *)this->m_pCBSystem->m_pUtil->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0));
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(inited->dwID);
      v6 = *(float *)(v5 + 788);
      if ( !(unsigned int)(__int64)v6 )
      {
LABEL_23:
        this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
        NullCallback(v10);
        return 0;
      }
      sprintf(Buffer, (const char *)&g_EffMgrData._tail_000[168], aWe, (unsigned int)(__int64)v6);
      v9 = Buffer;
    }
LABEL_22:
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v9, 1);
    goto LABEL_23;
  }
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(LODWORD(this->m_TaskArrC[0].m_fSlot0), 14) )
  {
    this->CCBStage::ClearBadPushTask(0.0099999998);
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
      this->m_TaskSlots[88] = 0;
  }
  if ( nVal == this->m_nBattleResult )
  {
    this->CCBStage::ClearBadPushTask(0.0099999998);
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
      this->m_TaskSlots[88] = 0;
  }
  return 0;
}

// 0x0050EDA0
int CCBStage::CheckPushState(int nVal)
{
  int v3; // eax
  void *v5; // [esp+0x0] [ebp-0x4]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || nVal == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleFlag(LODWORD(this->m_TaskArrC[0].m_fSlot0), 1);
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.0099999998);
    if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
    {
      this->m_nAllDone = 41;
      this->CCBStage::GetPointerPos();
    }
    v3 = *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
    this->m_fAngleDegrees = this->m_fCombatAnimY;
    this->m_TaskArrC[0]._todo_018[96 * v3 + 202] = 1;
    NullCallback(v5);
    return 0;
  }
}

// 0x0050EE70
int CCBStage::OnPhysicalHit(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || nVal == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
        this->m_TaskSlots[88] = 0;
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.25);
    if ( this->m_nAllDone == 44 )
    {
      (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16) + 24))(
        *(_DWORD *)(LODWORD(this->m_TaskArrC[0].m_fSlot2) + 16),
        0);
    }
    else if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
    {
      this->m_nAllDone = 44;
      this->CCBStage::GetPointerPos();
    }
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v4);
    return 0;
  }
}

// 0x0050EF60
int CCBStage::UpdateActionTimers(float fVal)
{
  void *v4; // [esp+0x0] [ebp-0x8]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || LODWORD(fVal) == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.0099999998);
    if ( LODWORD(this->m_TaskArrC[0].m_fSlot0) > 4 )
    {
      if ( (int)*(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 128] == 1 )
      {
        this->m_nAllDone = 56;
      }
      else if ( (int)*(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 128] == 2 )
      {
        this->m_nAllDone = 57;
      }
      else
      {
        this->m_nAllDone = 55;
      }
    }
    else
    {
      this->m_nAllDone = 35;
    }
    this->CCBStage::GetPointerPos();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v4);
    *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 196] = 3;
    return 0;
  }
}

// 0x0050F080
int CCBStage::AnimCallback_Attack(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || nVal == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.25);
    if ( *(_DWORD *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 144] == 4101 )
      this->m_nAllDone = 37;
    else
      this->m_nAllDone = 36;
    this->m_fAngleDegrees = this->m_fCombatAnimY;
    this->CCBStage::GetPointerPos();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v4);
    return 0;
  }
}

// 0x0050F150
int CCBStage::AnimCallback_UseItem(int nVal)
{
  float m_fCombatAnimY; // ecx
  void *v5; // [esp+0x0] [ebp-0x4]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || nVal == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.25);
    m_fCombatAnimY = this->m_fCombatAnimY;
    this->m_nAllDone = 38;
    this->m_fAngleDegrees = m_fCombatAnimY;
    this->CCBStage::GetPointerPos();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v5);
    return 0;
  }
}

// 0x0050F200
int CCBStage::OnMagicHit(int nVal)
{
  char *v3; // eax
  float m_fCombatAnimY; // eax
  CScreenMode *Instance; // eax
  void *v7; // [esp+0x0] [ebp-0x4]

  v3 = (char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92];
  if ( v3[506] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || nVal == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    return 0;
  }
  else
  {
    if ( (((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pRoleState))->CCBSystem::IsMagicSlotMsg((int)(v3 + 444)) )
    {
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    else
    {
      this->CCBStage::ClearBadPushTask(0.25);
      m_fCombatAnimY = this->m_fCombatAnimY;
      this->m_nAllDone = 39;
      this->m_fAngleDegrees = m_fCombatAnimY;
      this->CCBStage::GetPointerPos();
      NullCallback(v7);
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(aWe033, 1);
    }
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    return 0;
  }
}

// 0x0050F310
int CCBStage::AnimCallback_Throw(int nVal, int nVal2)
{
  ECBStageTaskState *v3; // edi
  int v6; // edi
  bool v7; // bl
  ECBStageTaskState *v8; // [esp-0x8] [ebp-0x10]
  void *v9; // [esp+0x0] [ebp-0x8]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    v8 = (ECBStageTaskState *)v3;
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || nVal == this->m_nBattleResult )
    {
      v6 = (int)*(float *)&this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 128];
      v7 = (((CCBStage *)*((CCBStage **)&this->m_pCBSystem->m_pAI + v6)))->CCBStage::ForceEndTaskByPFN();
      if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v6) || !v7 || !(((CCBStage *)v6))->CCBStage::GetTaskState(v8) )
      {
        this->CCBStage::ClearBadPushTask(0.0099999998);
        this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
      }
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.25);
    this->m_nAllDone = 42;
    this->CCBStage::IsGrabedBy();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v9);
    return 0;
  }
}

// 0x0050F410
int CCBStage::AnimCallback_CastMagic(int nVal)
{
  float m_fCombatAnimY; // ecx
  void *v5; // [esp+0x0] [ebp-0x4]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || nVal == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.25);
    m_fCombatAnimY = this->m_fCombatAnimY;
    this->m_nAllDone = 40;
    this->m_fAngleDegrees = m_fCombatAnimY;
    this->CCBStage::GetPointerPos();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v5);
    return 0;
  }
}

// 0x0050F4C0
int CCBStage::AnimCallback_WaitCmd(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || (((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen))->CCBSystem::IsCmdReady(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || (((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen))->CCBSystem::IsCmdEmpty(LODWORD(this->m_TaskArrC[0].m_fSlot0))
      || (unsigned __int8)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetForce(0) )
    {
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.0099999998);
    this->m_nAllDone = 48;
    this->CCBStage::IsGrabedBy();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v4);
    return 0;
  }
}

// 0x0050F590
int CCBStage::AnimCallback_MoveTo(int nVal)
{
  float *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v6; // st7
  double m_DeltaTime; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st7
  double v11; // st6
  double v12; // st7
  double v13; // st7
  int v15; // [esp+0xC] [ebp-0x14]
  float v16; // [esp+0xC] [ebp-0x14]
  int v17; // [esp+0x10] [ebp-0x10]
  float v18; // [esp+0x10] [ebp-0x10]
  float v19; // [esp+0x14] [ebp-0xC]
  float v20; // [esp+0x18] [ebp-0x8]
  int v21; // [esp+0x18] [ebp-0x8]
  int v22; // [esp+0x1C] [ebp-0x4]

  if ( (g_nCBFormation1[11] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation1[11]) |= 1u;
    g_nCBFormation1[8] = 0;
    g_nCBFormation1[9] = 0;
    g_nCBFormation1[10] = 0;
    atexit(nullsub_67);
  }
  if ( (g_nCBFormation1[11] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation1[11]) |= 2u;
    g_nCBFormation1[4] = 0;
    g_nCBFormation1[5] = 0;
    g_nCBFormation1[6] = 1065353216;
    atexit(nullsub_66);
  }
  if ( (g_nCBFormation1[11] & 4) == 0 )
  {
    LOBYTE(g_nCBFormation1[11]) |= 4u;
    g_nCBFormation1[0] = 0;
    g_nCBFormation1[1] = 0;
    g_nCBFormation1[2] = 0;
    atexit(nullsub_65);
  }
  v3 = (float *)((char *)this + 96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92]);
  if ( !*((_BYTE *)v3 + 506) )
  {
    this->m_fTargetPosX = v3[108];
    this->m_fTargetPosY = v3[109];
    this->m_fTargetPosZ = v3[110];
    v4 = this->m_fTargetPosX - this->m_fCurPosX;
    *(float *)&v15 = this->m_fTargetPosY - this->m_fCurPosY;
    v5 = this->m_fTargetPosZ - this->m_fCurPosZ;
    g_nCBFormation1[9] = v15;
    *(float *)&v17 = v5;
    *(float *)&g_nCBFormation1[8] = v4;
    g_nCBFormation1[10] = v17;
    (((gbVec3D *)&g_nCBFormation1[8]))->gbVec3D::Normalize();
    v6 = acos(
           *(float *)&g_nCBFormation1[6] * *(float *)&g_nCBFormation1[10]
         + *(float *)&g_nCBFormation1[5] * *(float *)&g_nCBFormation1[9]
         + *(float *)&g_nCBFormation1[4] * *(float *)&g_nCBFormation1[8]);
    this->m_fAngleDegrees = v6;
    if ( *(float *)&g_nCBFormation1[8] < 0.0f )
      this->m_fAngleDegrees = 6.2831854820251465f - v6;
    this->m_fAngleDegrees = this->m_fAngleDegrees * 57.295780181884766f;
    LODWORD(this->m_fVelX) = g_nCBFormation1[8];
    LODWORD(this->m_fVelY) = g_nCBFormation1[9];
    LODWORD(this->m_fVelZ) = g_nCBFormation1[10];
    this->m_fVelX = this->m_fVelX * 380.0f;
    this->m_fVelY = this->m_fVelY * 380.0f;
    this->m_fVelZ = this->m_fVelZ * 380.0f;
    this->m_nAllDone = 52;
    this->CCBStage::IsGrabedBy();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
  }
  m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
  v19 = this->m_fVelX * m_DeltaTime;
  v20 = this->m_fVelY * m_DeltaTime;
  v8 = v19 + this->m_fCurPosX;
  v16 = this->m_fCurPosY + v20;
  v9 = this->m_fCurPosZ + m_DeltaTime * this->m_fVelZ;
  this->m_fCurPosY = v16;
  v18 = v9;
  this->m_fCurPosX = v8;
  this->m_fCurPosZ = v18;
  v10 = this->m_fTargetPosX - this->m_fCurPosX;
  *(float *)&v21 = this->m_fTargetPosY - this->m_fCurPosY;
  v11 = this->m_fTargetPosZ - this->m_fCurPosZ;
  g_nCBFormation1[9] = v21;
  *(float *)&v22 = v11;
  *(float *)&g_nCBFormation1[8] = v10;
  g_nCBFormation1[10] = v22;
  (((gbVec3D *)&g_nCBFormation1[8]))->gbVec3D::Normalize();
  v12 = acos(
          *(float *)&g_nCBFormation1[6] * *(float *)&g_nCBFormation1[10]
        + *(float *)&g_nCBFormation1[5] * *(float *)&g_nCBFormation1[9]
        + *(float *)&g_nCBFormation1[4] * *(float *)&g_nCBFormation1[8]);
  if ( *(float *)&g_nCBFormation1[8] < 0.0f )
    v12 = 6.2831855 - v12;
  v13 = v12 * 57.29578;
  g_StageRoleData.m_nEffParam9C = v13;
  if ( fabs(v13 - this->m_fAngleDegrees) >= 1.570796370506287 )
  {
    LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(LODWORD(this->m_TaskArrC[0].m_fSlot0))[1].dwMagicID[2][5]) = 1;
    (((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen))->CCBSystem::GetCmdPtr(LODWORD(this->m_TaskArrC[0].m_fSlot0));
    (((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen))->CCBSystem::InvokeThreadMethod(LODWORD(this->m_TaskArrC[0].m_fSlot0), 0);
    (((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen))->CCBSystem::SetCmdParam(LODWORD(this->m_TaskArrC[0].m_fSlot0), 1);
    this->m_fCurPosX = this->m_fTargetPosX;
    this->m_fCurPosY = this->m_fTargetPosY;
    this->m_fCurPosZ = this->m_fTargetPosZ;
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
  }
  if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(LODWORD(this->m_TaskArrC[0].m_fSlot0)) )
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
  return 0;
}

// 0x0050FA20
int CCBStage::ClearTaskIfMatch(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] )
  {
    if ( nVal == this->m_nBattleResult )
    {
      this->CCBStage::ClearBadPushTask(0.0099999998);
      this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 201] = 1;
    }
    return 0;
  }
  else
  {
    this->CCBStage::ClearBadPushTask(0.25);
    this->m_nAllDone = 49;
    this->CCBStage::GetPointerPos();
    this->m_TaskArrC[0]._todo_018[96 * *(_DWORD *)&this->m_TaskArrC[0]._todo_018[92] + 202] = 1;
    NullCallback(v4);
    return 0;
  }
}

// 0x00518E10
int CCBStage::SetActionVisible(char nActIndex)
{
  int ( ***m_nState)(_DWORD, int); // ecx

  m_nState = (int ( ***)(_DWORD, int))this->m_TaskArrC[3].m_nState;
  if ( nActIndex )
    return (**m_nState)((_DWORD)((_DWORD)(m_nState)), (int)(1));
  else
    return (**m_nState)((_DWORD)((_DWORD)(m_nState)), (int)(0));
}

// 0x0051D710
CCBProtectWindow * CCBStage::Create_d710()
{
  float *p_m_fTurnTimer; // eax
  int *v3; // ebp
  int *v4; // ecx
  int *v5; // eax
  int *v6; // ebp
  int *v7; // ebp
  int *v8; // ebp
  int *v9; // eax
  int *v10; // ebp
  void **v11; // ecx
  void **v12; // eax
  void **v13; // ebp
  void **v14; // ebp
  void **v15; // ebp
  void **v16; // eax
  void **v17; // ebp
  int *v18; // eax
  int v19; // ecx
  float *v21; // [esp+0x10] [ebp-0x18]
  int *v22; // [esp+0x10] [ebp-0x18]
  void **v23; // [esp+0x10] [ebp-0x18]
  int v24; // [esp+0x14] [ebp-0x14]
  int v25; // [esp+0x14] [ebp-0x14]
  int v26; // [esp+0x14] [ebp-0x14]
  int v27; // [esp+0x14] [ebp-0x14]
  int v28; // [esp+0x14] [ebp-0x14]

  ((UIListBox *)this)->UIListBox::UIListBox();
  this->m_pShadow = ((CCBStageShadow *)((CCBStageShadow *)128));
  this->m_pEffect = ((CCBStageEffect *)((CCBStageEffect *)512));
  this->m_BFARole = 0;
  this->m_BFARound = 0;
  (((UIFrameContainer *)&this->m_TaskArrC[0]._todo_018[56]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_TaskArrC[0]._todo_018[208]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_TaskArrC[1]._todo_018[80]))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  ((UIPushButton *)&this->m_TaskArrC[7]._todo_018[168])->UIPushButton::UIPushButton();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  ((UIPushButton *)(&this->m_nTaskState + 932))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTaskState + 1180))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTaskState + 1428))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTaskState + 1676))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_TurnBuffer + 38))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_TurnBuffer + 100))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_TurnBuffer + 162))->UIPushButton::UIPushButton();
  ((UIPushButton *)&this->m_TaskArrA[256])->UIPushButton::UIPushButton();
  ((UIPushButton *)&this->m_TaskArrA[504])->UIPushButton::UIPushButton();
  ((UIPushButton *)&this->m_TaskArrA[752])->UIPushButton::UIPushButton();
  ((UIPushButton *)&this->m_TaskArrA[1016])->UIPushButton::UIPushButton();
  ((UIPushButton *)&this->m_TaskArrA[1264])->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTotalCount + 21))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTotalCount + 87))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTotalCount + 149))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTotalCount + 211))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->m_nTotalCount + 273))->UIPushButton::UIPushButton();
  p_m_fTurnTimer = (float *)&this->m_fTurnTimer;
  *(&this->m_nTotalCount + 335) = 0;
  *(&this->m_nTotalCount + 336) = 0;
  *(&this->m_nTotalCount + 337) = 0;
  *(&this->m_nTotalCount + 338) = 0;
  *((_BYTE *)&this->m_nTotalCount + 1357) = 1;
  *((_BYTE *)&this->m_nTotalCount + 1358) = 0;
  *(&this->m_nTotalCount + 345) = 0;
  v21 = (float *)&this->m_fTurnTimer;
  v3 = (int *)(&this->m_nTurnSlot5 + 3);
  v24 = 396;
  while ( 1 )
  {
    *p_m_fTurnTimer = 0.0;
    lstrcpyA((LPSTR)v3 - 32, unk_C10D38);
    lstrcpyA((LPSTR)v3, unk_C10D38);
    lstrcpyA((LPSTR)v3 + 30, unk_C10D38);
    lstrcpyA((LPSTR)v3 + 60, unk_C10D38);
    *((_BYTE *)v3 + 576) = 0;
    memset(v3 + 152, 0, 0x18u);
    *((_BYTE *)v3 + 764) = 0;
    *((_BYTE *)v3 + 765) = 0;
    v3[192] = -1;
    v3 += 202;
    v21 += 202;
    if ( !--v24 )
      break;
    p_m_fTurnTimer = (float *)v21;
  }
  *(&this->m_nResultSlot1 + 79600) = 0;
  *(&this->m_nResultSlot1 + 79601) = 0;
  *(&this->m_nResultSlot1 + 79602) = 0;
  *(&this->m_nResultSlot1 + 79603) = 1;
  *(&this->m_nResultSlot1 + 79604) = 1;
  *(&this->m_nResultSlot1 + 79605) = 1;
  *(&this->m_nResultSlot1 + 79606) = 0;
  *(&this->m_nResultSlot1 + 79607) = 0;
  *((_WORD *)&this->m_nResultSlot1 + 159217) = 0;
  *(&this->m_nResultSlot1 + 83082) = 0;
  v25 = 4;
  *(&this->m_nResultSlot1 + 83083) = 0;
  memset(&this->m_nResultSlot1 + 83084, 0, 0x640u);
  memset(&this->m_nResultSlot1 + 83884, 0, 0x190u);
  memset(&this->m_nResultSlot1 + 83484, 0, 0x640u);
  *(&this->m_nResultSlot1 + 79608) = 0;
  v4 = (int *)(&this->m_nResultSlot1 + 83997);
  *(&this->m_nResultSlot1 + 83988) = 0;
  *(&this->m_nResultSlot1 + 83989) = 0;
  *(&this->m_nResultSlot1 + 83990) = 0;
  v5 = (int *)(&this->m_nResultSlot1 + 84006);
  do
  {
    v6 = (int *)(v5 - 6);
    *v4 = 0;
    *(v5 - 8) = 0;
    *(v5 - 7) = 0;
    *v6 = 0;
    v4 += 12;
    v6[1] = 0;
    v6[2] = 0;
    v7 = (int *)(v5 - 3);
    *(v5 - 3) = 0;
    v7[1] = 0;
    v7[2] = 0;
    v8 = (int *)v5;
    v5 += 12;
    *v8 = 0;
    v8[1] = 0;
    v8[2] = 0;
    --v25;
  }
  while ( v25 );
  *((_BYTE *)&this->m_nResultSlot1 + 335964) = 0;
  *((_BYTE *)&this->m_nResultSlot1 + 335965) = 0;
  *((_BYTE *)&this->m_nResultSlot1 + 335966) = 0;
  *((_BYTE *)&this->m_nResultSlot1 + 335967) = 0;
  *((_BYTE *)&this->m_nResultSlot1 + 335968) = 0;
  *((_BYTE *)&this->m_nResultSlot1 + 335969) = 0;
  *((_BYTE *)&this->m_nResultSlot1 + 335970) = 0;
  *(&this->m_nResultSlot1 + 83993) = 1065353216;
  *(&this->m_nResultSlot1 + 83994) = 0;
  *(&this->m_nResultSlot1 + 83995) = 0;
  *(&this->m_nResultSlot1 + 83996) = 0;
  *(&this->m_nResultSlot1 + 84045) = 0;
  memset(&this->m_nResultSlot1 + 83997, 0, 0xC0u);
  v9 = (int *)(&this->m_nResultSlot1 + 84046);
  v26 = 200;
  v22 = (int *)(&this->m_nResultSlot1 + 84046);
  v10 = (int *)(&this->m_nResultSlot1 + 84055);
  while ( 1 )
  {
    *v9 = 0;
    lstrcpyA((LPSTR)v10 - 32, unk_C10D38);
    lstrcpyA((LPSTR)v10, unk_C10D38);
    lstrcpyA((LPSTR)v10 + 30, unk_C10D38);
    lstrcpyA((LPSTR)v10 + 60, unk_C10D38);
    *((_BYTE *)v10 + 576) = 0;
    memset(v10 + 152, 0, 0x18u);
    *((_BYTE *)v10 + 764) = 0;
    *((_BYTE *)v10 + 765) = 0;
    v10[192] = -1;
    v10 += 202;
    v22 += 202;
    if ( !--v26 )
      break;
    v9 = (int *)v22;
  }
  v11 = (void **)(&this->m_nTodo_64190 + 24368);
  *((_DWORD *)&this->m_nTodo_64190 + 24355) = 1;
  *((_DWORD *)&this->m_nTodo_64190 + 24356) = 1;
  *((_DWORD *)&this->m_nTodo_64190 + 24357) = 1;
  *((_DWORD *)&this->m_nTodo_64190 + 24358) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 24359) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 24360) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 24361) = 0;
  v12 = (void **)(&this->m_nTodo_64190 + 24377);
  v27 = 4;
  do
  {
    v13 = (void **)(v12 - 6);
    *v11 = 0;
    *(v12 - 8) = 0;
    *(v12 - 7) = 0;
    *v13 = 0;
    v11 += 12;
    v13[1] = 0;
    v13[2] = 0;
    v14 = (void **)(v12 - 3);
    *(v12 - 3) = 0;
    v14[1] = 0;
    v14[2] = 0;
    v15 = (void **)v12;
    v12 += 12;
    *v15 = 0;
    v15[1] = 0;
    v15[2] = 0;
    --v27;
  }
  while ( v27 );
  *((_BYTE *)&this->m_nTodo_64190 + 97448) = 0;
  *((_BYTE *)&this->m_nTodo_64190 + 97449) = 0;
  *((_BYTE *)&this->m_nTodo_64190 + 97450) = 0;
  *((_BYTE *)&this->m_nTodo_64190 + 97451) = 0;
  *((_BYTE *)&this->m_nTodo_64190 + 97452) = 0;
  *((_BYTE *)&this->m_nTodo_64190 + 97453) = 0;
  *((_BYTE *)&this->m_nTodo_64190 + 97454) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 24364) = 1065353216;
  *((_DWORD *)&this->m_nTodo_64190 + 24365) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 24366) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 24367) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 24416) = 0;
  memset(&this->m_nTodo_64190 + 24368, 0, 0xC0u);
  v16 = (void **)(&this->m_nTodo_64190 + 24417);
  v28 = 200;
  v23 = (void **)(&this->m_nTodo_64190 + 24417);
  v17 = (void **)(&this->m_nTodo_64190 + 24426);
  while ( 1 )
  {
    *v16 = 0;
    lstrcpyA((LPSTR)v17 - 32, unk_C10D38);
    lstrcpyA((LPSTR)v17, unk_C10D38);
    lstrcpyA((LPSTR)v17 + 30, unk_C10D38);
    lstrcpyA((LPSTR)v17 + 60, unk_C10D38);
    *((_BYTE *)v17 + 576) = 0;
    memset(v17 + 152, 0, 0x18u);
    *((_BYTE *)v17 + 764) = 0;
    *((_BYTE *)v17 + 765) = 0;
    v17[192] = (void *)-1;
    v17 += 202;
    v23 += 202;
    if ( !--v28 )
      break;
    v16 = (void **)v23;
  }
  *((_DWORD *)&this->m_nTodo_64190 + 64824) = 0;
  *((_DWORD *)&this->m_nTodo_64190 + 64821) = 1;
  *((_DWORD *)&this->m_nTodo_64190 + 64822) = 1;
  *((_DWORD *)&this->m_nTodo_64190 + 64823) = 1;
  *((_BYTE *)&this->m_nTodo_64190 + 259300) = 0;
  ((UIRoleDialog *)(&this->m_nTodo_64190 + 64826))->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)(&this->m_nTodo_64190 + 65168))->UIRoleDialog::UIRoleDialog();
  v18 = (int *)(&this->m_nTotalCount + 340);
  v19 = 4;
  do
  {
    v18[84382] = 0;
    *v18++ = 0;
    --v19;
  }
  while ( v19 );
  return (CCBProtectWindow *)this;
}

// 0x0051DD80
void CCBStage::_sdtor_call_dtor(int a2)
{
  this->CCBStage::ShowWindow();
  if ( (a2 & 1) != 0 )
    operator delete(this);
}

// 0x0051DDA0
void CCBStage::ShowWindow()
{
  *((_BYTE *)&this->m_nTotalCount + 1357) = 1;
  (((UIRoleDialog *)(&this->m_nTodo_64190 + 65168)))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)(&this->m_nTodo_64190 + 64826)))->UIRoleDialog::~UIRoleDialog();
  (((UIPushButton *)(&this->m_nTotalCount + 273)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTotalCount + 211)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTotalCount + 149)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTotalCount + 87)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTotalCount + 21)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)&this->m_TaskArrA[1264]))->UIPushButton::~UIPushButton();
  (((UIPushButton *)&this->m_TaskArrA[1016]))->UIPushButton::~UIPushButton();
  (((UIPushButton *)&this->m_TaskArrA[752]))->UIPushButton::~UIPushButton();
  (((UIPushButton *)&this->m_TaskArrA[504]))->UIPushButton::~UIPushButton();
  (((UIPushButton *)&this->m_TaskArrA[256]))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_TurnBuffer + 162)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_TurnBuffer + 100)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_TurnBuffer + 38)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTaskState + 1676)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTaskState + 1428)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTaskState + 1180)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(&this->m_nTaskState + 932)))->UIPushButton::~UIPushButton();
  (((UICaption *)(&this->m_nTaskState + 572)))->UICaption::Destroy2();
  (((UICaption *)(&this->m_nTaskState + 228)))->UICaption::Destroy2();
  (((UICaption *)&this->m_TaskArrC[8]._todo_018[136]))->UICaption::Destroy2();
  (((UIPushButton *)&this->m_TaskArrC[7]._todo_018[168]))->UIPushButton::~UIPushButton();
  (((UICaption *)&this->m_TaskArrC[6]._todo_018[104]))->UICaption::Destroy2();
  (((UICaption *)&this->m_TaskArrC[5]._todo_018[40]))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_TaskArrC[1]._todo_018[80]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_TaskArrC[0]._todo_018[208]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_TaskArrC[0]._todo_018[56]))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0051F070
int CCBStage::UpdateWeaponSlots()
{
  int result; // eax
  int v2; // [esp+0x4] [ebp+0x4]

  result = v2;
  *(&this->m_nTotalCount + 336) = v2;
  return result;
}

// 0x0051F080
int CCBStage::SetWeaponSlotA()
{
  int result; // eax
  int v2; // [esp+0x4] [ebp+0x4]

  result = v2;
  *(&this->m_nTotalCount + 337) = v2;
  return result;
}

// 0x0051F090
int CCBStage::SetWeaponSlotB()
{
  int result; // eax
  int v2; // [esp+0x4] [ebp+0x4]

  result = v2;
  *(&this->m_nTotalCount + 338) = v2;
  return result;
}

// 0x00521A80
bool CCBStage::CheckActionValid(int nVal)
{
  float nVala; // [esp+0xC] [ebp+0x8]

  if ( nVal <= 0 )
    return 0;
  nVala = (float)nVal * 10.239999771118164f;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
  return (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)nVala;
}

// 0x00521E60
int CCBStage::DispatchUpdate(unsigned __int8 nFlag)
{
  (**((void ( ***)(_BYTE *, _DWORD))&this->m_nTaskState + 233))((_BYTE *)(&this->m_nTaskState + 932), (_DWORD)(nFlag));
  (**((void ( ***)(_BYTE *, _DWORD))&this->m_nTaskState + 295))((_BYTE *)(&this->m_nTaskState + 1180), (_DWORD)(nFlag));
  (**((void ( ***)(_BYTE *, _DWORD))&this->m_nTaskState + 357))((_BYTE *)(&this->m_nTaskState + 1428), (_DWORD)(nFlag));
  return (**((int ( ***)(_BYTE *, _DWORD))&this->m_nTaskState + 419))((_BYTE *)(&this->m_nTaskState + 1676), (_DWORD)(nFlag));
}

// 0x00521F30
int CCBStage::DispatchUpdateAll(unsigned __int8 nFlag)
{
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_TaskArrA[1016])((_BYTE *)(&this->m_TaskArrA[1016]), (_DWORD)(nFlag));
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_TaskArrA[1264])((_BYTE *)(&this->m_TaskArrA[1264]), (_DWORD)(nFlag));
  return (**((int ( ***)(int *, _DWORD))&this->m_nTotalCount + 21))((int *)(&this->m_nTotalCount + 21), (_DWORD)(nFlag));
}

// 0x005220E0
int * CCBStage::ClearRoleState()
{
  int *result; // eax
  CCBStageCam **p_m_pCam; // ecx
  _DWORD *v3; // esi

  result = (int *)this;
  this->m_pCBSystem = ((CCBSystem *)0);
  this->m_pRoleState = ((CCBRoleState *)0);
  this->m_pEditor = ((CCBEditor *)0);
  p_m_pCam = (CCBStageCam **)&this->m_pCam;
  *p_m_pCam = 0;
  p_m_pCam[1] = 0;
  p_m_pCam[2] = 0;
  v3 = (_DWORD *)(p_m_pCam + 3);
  p_m_pCam += 6;
  *v3 = 0;
  v3[1] = 0;
  v3[2] = 0;
  *p_m_pCam = 0;
  p_m_pCam[1] = 0;
  p_m_pCam[2] = 0;
  return result;
}

// 0x00522120
void CCBStage::CleanupScript()
{
  (((PalScript *)&this->m_pRoleState))->PalScript::Cleanup();
}

// 0x00523090
int CCBStage::GetWeaponSlotPtr(int nVal)
{
  if ( nVal < 5 )
    return (int)&this->m_TaskArrC[0]._todo_018[220 * nVal + 228];
  else
    return 0;
}

// 0x00525090
int CCBStage::sub_525090(void *thisa)
{
  return (((CCBStage *)&this->m_TaskArrC[6]._todo_018[252]))->CCBStage::GetWeaponSlotPtr(*(_DWORD *)&this->m_TaskArrA[24]);
}

// 0x0053E310
void CCBStage::PlaySound(char *name, int nVal)
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
    (((std::string *)0))->_Tidy();
    v14 = 0;
    v4 = strlen(unk_C10D38);
    if ( (((SceneObj *)&nVal2))->SceneObj::UpdateAutoDelete(v4) )
    {
      qmemcpy(v11, unk_C10D38, v4);
      (((std::string *)v4))->_Eos();
    }
    v13 = 0;
    v5 = strlen(name) + 1;
    v6 = v5 - 1;
    v14 = 1;
    if ( (((SceneObj *)&nVal2))->SceneObj::UpdateAutoDelete(v5 - 1) )
    {
      qmemcpy(v11, name, v6);
      v12 = v5 - 1;
      v11[v6] = 0;
    }
    for ( i = *(_DWORD *)&this->m_TaskArrC[1]._todo_018[232]; i != *(_DWORD *)&this->m_TaskArrC[1]._todo_018[236]; i += 20 )
    {
      for ( j = *(_DWORD *)&this->m_TaskArrC[1]._todo_018[236]; i != j; i += 20 )
      {
        if ( CScreenMode::GetByteParam(i, (int)&nVal2) )
          break;
      }
      if ( i == *(_DWORD *)&this->m_TaskArrC[1]._todo_018[236] )
        break;
      if ( (((gbSound2DNode *)*(gbSound2DNode **)(i + 16)))->gbSound2DNode::IsPlaying() )
      {
        (((gbSound2DNode *)*(gbSound2DNode **)(i + 16)))->gbSound2DNode::Stop();
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
unsigned int CCBStage::PauseSound()
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  signed int v5; // ecx

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = *(_DWORD *)&this->m_TaskArrC[1]._todo_018[232];
    if ( !result )
      break;
    v5 = *(_DWORD *)&this->m_TaskArrC[1]._todo_018[236] - result;
    result = (unsigned int)((unsigned __int64)(1717986919i64 * v5) >> 32) >> 31;
    if ( v1 >= v5 / 20 )
      break;
    (((gbSound2DNode *)*(gbSound2DNode **)(*(_DWORD *)&this->m_TaskArrC[1]._todo_018[232] + i + 16)))->gbSound2DNode::Pause();
    ++v1;
  }
  return result;
}

// 0x0053EA10
unsigned int CCBStage::ResumeSound()
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  signed int v5; // ecx

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
    result = *(_DWORD *)&this->m_TaskArrC[1]._todo_018[232];
    if ( !result )
      break;
    v5 = *(_DWORD *)&this->m_TaskArrC[1]._todo_018[236] - result;
    result = (unsigned int)((unsigned __int64)(1717986919i64 * v5) >> 32) >> 31;
    if ( v1 >= v5 / 20 )
      break;
    (((gbSound2DNode *)*(gbSound2DNode **)(*(_DWORD *)&this->m_TaskArrC[1]._todo_018[232] + i + 16)))->gbSound2DNode::Resume();
    ++v1;
  }
  return result;
}
