#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/EquipUI.h"
#include "Role/Actor.h"
#include "Misc/ArcSceneObject.h"
#include "Misc/Array.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCCTData.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Misc/LineupComp.h"
#include "Misc/LineupUI.h"
#include "Misc/MainEquipUI.h"
#include "Misc/MainPropUI.h"
#include "Misc/NameSys.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "UI/StateUI.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIBigMap.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIParticle.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIScene.h"
#include "Misc/UITitle_XJTM.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/st_Manager.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern char asc_5B74B8[];

// 0x00484D20
int EquipUI::ShowPage()
{
  char *v2; // ecx

  if ( g_bRoleFlag1 )
  {
    v2 = (char *)&this->m_EquipData + 2280;
  }
  else
  {
    (((PalScript *)((char *)&this->m_EquipData + 2280)))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    v2 = (char *)&this->m_EquipData + 2280;
  }
  sub_445E50((int)v2);
  if ( !g_bRoleFlag2 )
    (((PalScript *)((char *)&this->m_EquipData + 2624)))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->m_EquipData + 2624);
  (((PalScript *)((char *)&this->m_EquipData + 2968)))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnBattle_Array.tga", g_bDebugMode);
  sub_445E50((int)&this->m_EquipData + 2968);
  sub_445E50((int)&this->m_EquipData + 904);
  sub_445E50((int)&this->m_EquipData + 1248);
  sub_445E50((int)&this->m_EquipData + 1592);
  sub_445E50((int)&this->m_EquipData + 1936);
  sub_445E50((int)&this->m_EquipData + 3312);
  return sub_445E50((int)&this->m_EquipData + 3656);
}

// 0x00484E70
int EquipUI::SelectTab0(unsigned __int8 nTab)
{
  BYTE1(this->j) = nTab;
  return (((LineupComp *)this))->LineupComp::DispatchSlotMethod(0, nTab);
}

// 0x0048A2F0
int EquipUI::SetSubTab(unsigned __int8 nTab)
{
  *((_BYTE *)&this->m_EquipData + 501) = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState(0, nTab);
}

// 0x00494040
void EquipUI::UpdateSlot(int nSlotIdx, int nItemID, int nCount)
{
  CHAR *v5; // esi
  CHAR *v6; // edi
  RoleAtt *v7; // ecx
  LPCSTR v8; // eax
  CHAR String1[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v10; // [esp+0x10D] [ebp-0x3]
  char v11; // [esp+0x10F] [ebp-0x1]

  v5 = (CHAR *)&this->buf[24];
  sprintf(&this->buf[24], unk_C10D38);
  memset(String1, 0, sizeof(String1));
  v10 = 0;
  v11 = 0;
  v6 = (CHAR *)sub_458F70((LPCSTR)(nCount + 96), (int)asc_5B74B8, String1);
  if ( lstrlenA((const char *)v6) <= 0 )
  {
    (((RoleAtt *)v7))->RoleAtt::FormatAttributeText();
    lstrcatA((char *)v5, v8);
  }
  else
  {
    lstrcpyA((char *)v5, v6);
  }
  SetEnable((UICaption *)&this[1].m_AnimateRc[3][2][0].right);
  SetEnable((UICaption *)&this[1].m_AnimateRc[3][0][1]);
}

// 0x004945C0
int EquipUI::SelectBigMapTab0(char nTab)
{
  BYTE1(this->j) = nTab;
  return (((UIBigMap *)this))->UIBigMap::SetEntryVisible(0, nTab);
}

// 0x00494D70
void EquipUI::HandleInput(int nInputID, int nParam)
{
  char *v4; // edi
  int v5; // edi
  const char *v6; // ebp
  const char *v7; // edx
  char *v8; // edi
  RoleAtt *v9; // edi
  char *v10; // edi
  const char *v11; // edx
  const char *v12; // ebx
  char *v13; // edi
  RoleAtt *v14; // edi
  char *v15; // edi
  RoleAtt *v16; // edi
  char *v17; // edi
  RoleAtt *v18; // edi
  const char *v19; // edi
  int oldtick; // ebp
  signed int Child; // edi
  _DWORD *v22; // eax
  int v23; // ebx
  int ListItems; // ebp
  int v25; // ebp
  int ItemData; // eax
  int *v27; // eax
  int v28; // ebx
  const char *v29; // ebp
  UICursor *v30; // ecx
  const char *v31; // [esp-0x18] [ebp-0x150]
  int v32; // [esp+0x10] [ebp-0x128]
  int nIndex; // [esp+0x14] [ebp-0x124]
  int v34; // [esp+0x1C] [ebp-0x11C]
  int v35; // [esp+0x20] [ebp-0x118]
  gbColorQuad v36; // [esp+0x28] [ebp-0x110] BYREF
  char pOut[12]; // [esp+0x2C] [ebp-0x10C] BYREF
  char Buffer; // [esp+0x38] [ebp-0x100] BYREF
  _BYTE v39[252]; // [esp+0x39] [ebp-FFh] BYREF
  __int16 v40; // [esp+0x135] [ebp-0x3]
  char v41; // [esp+0x137] [ebp-0x1]

  if ( nInputID <= 5 )
  {
    switch ( nParam )
    {
      case 0:
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(7);
        *(_DWORD *)&this->m_EquipData.m_Type = 7;
        v4 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v4 + 162424));
        sub_445E50((int)(v4 + 163112));
        sub_445E50((int)(v4 + 162768));
        sub_445E50((int)(v4 + 163456));
        sub_445E50((int)(v4 + 163800));
        sub_445E50((int)(v4 + 164144));
        if ( !*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID) )
          goto LABEL_42;
        this->EquipUI::UpdateSlot(*(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * nInputID), *(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * nInputID + 1), *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID));
        (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(228.0);
        (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 262, 600);
        if ( !strcmp(
                (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID) + 36),
                unk_C10D38) )
          sprintf(&this->buf[24], "%s", "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID) + 36),
            (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID) + 36));
        (((PalScript *)&this[1].m_Icon[0][0].m_dstAlpha))->PalScript::LoadModel(&this->buf[24], 0);
        v5 = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID);
        v6 = (const char *)(v5 + 36);
        v7 = (const char *)(v5 + 66);
        if ( !strcmp((const char *)(v5 + 36), unk_C10D38) )
          goto LABEL_38;
        goto LABEL_39;
      case 1:
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(11);
        *(_DWORD *)&this->m_EquipData.m_Type = 11;
        v8 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v8 + 162424));
        sub_445E50((int)(v8 + 163112));
        sub_445E50((int)(v8 + 162768));
        sub_445E50((int)(v8 + 163456));
        sub_445E50((int)(v8 + 163800));
        sub_445E50((int)(v8 + 164144));
        if ( !g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID] )
          goto LABEL_42;
        this->EquipUI::UpdateSlot(*(&g_RoleSlotBuf.m_partyActor.m_nAnimFrames + 352 * nInputID), *(&g_RoleSlotBuf.m_partyActor.m_nTransitionParam + 352 * nInputID), (int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID]);
        (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(180.0);
        (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp(
                (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID]->Remark.skillCount + 30,
                unk_C10D38) )
          sprintf(&this->buf[24], "%s", "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID]->Remark.skillCount + 30,
            (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID]->Remark.skillCount + 30);
        (((PalScript *)&this[1].m_Icon[0][0].m_dstAlpha))->PalScript::LoadModel(&this->buf[24], 0);
        v9 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID];
        v6 = (char *)&v9->Remark.skillCount + 30;
        v7 = (char *)&v9->Remark.skillCount + 60;
        if ( strcmp((const char *)&v9->Remark.skillCount + 30, unk_C10D38) )
          goto LABEL_39;
        goto LABEL_38;
      case 2:
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(12);
        *(_DWORD *)&this->m_EquipData.m_Type = 12;
        v10 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v10 + 162424));
        sub_445E50((int)(v10 + 163112));
        sub_445E50((int)(v10 + 162768));
        sub_445E50((int)(v10 + 163456));
        sub_445E50((int)(v10 + 163800));
        sub_445E50((int)(v10 + 164144));
        if ( !*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID) )
          goto LABEL_42;
        this->EquipUI::UpdateSlot(*(&g_RoleSlotBuf.m_partyActor.m_nModelParamB + 352 * nInputID), *(&g_RoleSlotBuf.m_partyActor.m_nRoleState1 + 352 * nInputID), *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID));
        (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(180.0);
        (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp(
                (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID) + 36),
                unk_C10D38) )
          sprintf(&this->buf[24], "%s", "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID) + 36),
            (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID) + 36));
        (((PalScript *)&this[1].m_Icon[0][0].m_dstAlpha))->PalScript::LoadModel(&this->buf[24], 0);
        v11 = (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0
                             + 352 * this[1].m_ArrowMove[5][1][0].m_Rc2.top)
                           + 66);
        v12 = (const char *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID) + 36);
        if ( !strcmp(v12, unk_C10D38) )
          goto LABEL_38;
        Buffer = 0;
        memset(v39, 0, sizeof(v39));
        v40 = 0;
        v41 = 0;
        sprintf(&Buffer, "%s%s", v12, v11);
        v31 = (const char *)v12;
        goto LABEL_40;
      case 3:
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(13);
        *(_DWORD *)&this->m_EquipData.m_Type = 13;
        v13 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v13 + 162424));
        sub_445E50((int)(v13 + 163112));
        sub_445E50((int)(v13 + 162768));
        sub_445E50((int)(v13 + 163456));
        sub_445E50((int)(v13 + 163800));
        sub_445E50((int)(v13 + 164144));
        if ( !g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID] )
          goto LABEL_42;
        this->EquipUI::UpdateSlot((int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID + 1], (int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID + 2], (int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID]);
        (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(180.0);
        (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp(
                (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID]->Remark.skillCount + 30,
                unk_C10D38) )
          sprintf(&this->buf[24], "%s", "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID]->Remark.skillCount + 30,
            (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID]->Remark.skillCount + 30);
        (((PalScript *)&this[1].m_Icon[0][0].m_dstAlpha))->PalScript::LoadModel(&this->buf[24], 0);
        v14 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID];
        v6 = (char *)&v14->Remark.skillCount + 30;
        v7 = (char *)&v14->Remark.skillCount + 60;
        if ( strcmp((const char *)&v14->Remark.skillCount + 30, unk_C10D38) )
          goto LABEL_39;
        goto LABEL_38;
      case 4:
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(9);
        *(_DWORD *)&this->m_EquipData.m_Type = 9;
        v15 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v15 + 162424));
        sub_445E50((int)(v15 + 163112));
        sub_445E50((int)(v15 + 162768));
        sub_445E50((int)(v15 + 163456));
        sub_445E50((int)(v15 + 163800));
        sub_445E50((int)(v15 + 164144));
        if ( !g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3] )
          goto LABEL_42;
        this->EquipUI::UpdateSlot((int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 1], (int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 2], (int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3]);
        (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(180.0);
        (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp(
                (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3]->Remark.skillCount + 30,
                unk_C10D38) )
          sprintf(&this->buf[24], "%s", "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3]->Remark.skillCount + 30,
            (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3]->Remark.skillCount + 30);
        (((PalScript *)&this[1].m_Icon[0][0].m_dstAlpha))->PalScript::LoadModel(&this->buf[24], 0);
        v16 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3];
        v6 = (char *)&v16->Remark.skillCount + 30;
        v7 = (char *)&v16->Remark.skillCount + 60;
        if ( strcmp((const char *)&v16->Remark.skillCount + 30, unk_C10D38) )
          goto LABEL_39;
        goto LABEL_38;
      case 5:
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(9);
        *(_DWORD *)&this->m_EquipData.m_Type = 9;
        v17 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v17 + 162424));
        sub_445E50((int)(v17 + 163112));
        sub_445E50((int)(v17 + 162768));
        sub_445E50((int)(v17 + 163456));
        sub_445E50((int)(v17 + 163800));
        sub_445E50((int)(v17 + 164144));
        if ( g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6] )
        {
          this->EquipUI::UpdateSlot((int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 4], (int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 5], (int)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6]);
          (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(180.0);
          (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 258, 600);
          if ( !strcmp(
                  (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6]->Remark.skillCount + 30,
                  unk_C10D38) )
            sprintf(&this->buf[24], "%s", "NONE");
          else
            sprintf(
              &this->buf[24],
              "Item\\%s\\%s.pol",
              (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6]->Remark.skillCount + 30,
              (const char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6]->Remark.skillCount + 30);
          (((PalScript *)&this[1].m_Icon[0][0].m_dstAlpha))->PalScript::LoadModel(&this->buf[24], 0);
          v18 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6];
          v6 = (char *)&v18->Remark.skillCount + 30;
          v7 = (char *)&v18->Remark.skillCount + 60;
          if ( !strcmp((const char *)&v18->Remark.skillCount + 30, unk_C10D38) )
          {
LABEL_38:
            v19 = (const char *)&this->buf[24];
            sprintf(&this->buf[24], "%s", "NONE");
          }
          else
          {
LABEL_39:
            Buffer = 0;
            memset(v39, 0, sizeof(v39));
            v40 = 0;
            v41 = 0;
            sprintf(&Buffer, "%s%s", v6, v7);
            v31 = (const char *)v6;
LABEL_40:
            v19 = (const char *)&this->buf[24];
            sprintf(&this->buf[24], "Item\\%s\\%s.tga", v31, &Buffer);
          }
          (((gbGeomNode *)*(gbGeomNode **)&this[1].m_Icon[0][0].m_isAdd))->gbGeomNode::ReplaceTexture(v19);
          this[1].m_Icon[0][0].m_alpha = 1;
        }
        else
        {
LABEL_42:
          SetEnable((UICaption *)&this[1].m_AnimateRc[3][0][1]);
          SetEnable((UICaption *)&this[1].m_AnimateRc[3][2][0].right);
          this[1].m_Icon[0][0].m_alpha = 0;
        }
LABEL_43:
        oldtick = *(_DWORD *)&this[1].m_ArrowMove[6][4][2].m_Time.bNote;
        v32 = oldtick;
        Child = (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::CreateChild();
        if ( Child < 0 )
        {
          oldtick = 0;
          v32 = 0;
        }
        if ( this[1].m_Icon[0][0].m_ratioh >= 0.0 )
          (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert((void *)LODWORD(this[1].m_Icon[0][0].m_ratioh));
        (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::ClearAll();
        nIndex = 0;
        if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
        {
          do
          {
            v22 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, nIndex);
            v34 = (unsigned long)v22[1];
            v23 = (unsigned long)v22[2];
            sprintf(&this->buf[24], "%s", v23 + 4);
            ListItems = (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::LoadListItems(&this->buf[24], 0);
            sprintf(&this->buf[24], (const char *)&dir[20], v34);
            (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::SetMouseMoveSel(1, ListItems, &this->buf[24], 0);
            if ( *(_BYTE *)(nInputID + v23 + 614) )
            {
              if ( ListItems < 0 || ListItems >= (int)this[1].m_ArrowMove[6][5][2].m_Time.newtick )
                v25 = 0;
              else
                v25 = *(_DWORD *)(*(_DWORD *)this[1].m_ArrowMove[6][5][2].m_IsLoop + 4 * ListItems);
              *(_DWORD *)(v25 + 68) = this[1].m_ArrowMove[6][3][3].m_Rc.top;
            }
            else
            {
              UITabCtrl_SetItemParam(ListItems);
            }
            ++nIndex;
          }
          while ( nIndex < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
          oldtick = v32;
        }
        (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::SetSel(oldtick);
        ItemData = (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::GetItemData();
        if ( ItemData <= Child )
          Child = ItemData - 1;
        (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::GetItem();
        if ( Child >= 0 )
        {
          v27 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, Child);
          v28 = (unsigned long)v27[2];
          this->EquipUI::UpdateSlot(*v27, v27[1], v28);
          if ( *(_BYTE *)(v28 + 612) == 11 )
          {
            (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(228.0);
            (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 262, 600);
          }
          else
          {
            (((CCBFiveNimbusWindow *)&this[1].m_Icon[0][0].m_textx))->CCBFiveNimbusWindow::SetFloatParam(180.0);
            (((Camera *)&this[1].m_Icon[0][0].m_textx))->Camera::UpdateCameraLookAt(128, 258, 600);
          }
          v35 = *((_DWORD *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, Child) + 2);
          v29 = (const char *)(v35 + 36);
          if ( !strcmp((const char *)(v35 + 36), unk_C10D38) )
            sprintf(&this->buf[24], "%s", "NONE");
          else
            sprintf(&this->buf[24], "Item\\%s\\%s.pol", (const char *)(v35 + 36), (const char *)(v35 + 36));
          (((PalScript *)&this[1].m_Icon[0][0].m_dstAlpha))->PalScript::LoadModel(&this->buf[24], 0);
          if ( !strcmp((const char *)(v35 + 36), unk_C10D38) )
          {
            sprintf(&this->buf[24], "%s", "NONE");
          }
          else
          {
            Buffer = 0;
            memset(v39, 0, sizeof(v39));
            v40 = 0;
            v41 = 0;
            sprintf(&Buffer, "%s%s", v29, (const char *)(v35 + 66));
            sprintf(&this->buf[24], "Item\\%s\\%s.tga", v29, &Buffer);
          }
          (((gbGeomNode *)*(gbGeomNode **)&this[1].m_Icon[0][0].m_isAdd))->gbGeomNode::ReplaceTexture(&this->buf[24]);
          oldtick = v32;
          this[1].m_Icon[0][0].m_alpha = 1;
        }
        if ( oldtick >= (int)this[1].m_ArrowMove[6][4][2].m_Time.oldtick )
          oldtick = this[1].m_ArrowMove[6][4][2].m_Time.oldtick;
        (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::SetSel(oldtick);
        if ( *(_DWORD *)&this->_isCreatable >= (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::GetItemData() )
          *(_DWORD *)&this->_isCreatable = (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::GetItemData() - 1;
        if ( *(int *)&this->_isCreatable < 0 )
          *(_DWORD *)&this->_isCreatable = -1;
        (((UIListBox *)&this[1].m_ArrowMove[6][3][3].m_Rc))->UIListBox::GetItem();
        LODWORD(this->_flashSpeed) = nParam;
        MainPropUI_ShowSubPanels(nInputID);
        UIScene_LoadRoleSkillData(nInputID);
        (((MainEquipUI *)this))->MainEquipUI::UpdateTooltip(nInputID) /* [ROWTABLE] */;
        (((UICursor *)v30))->UICursor::_todo_541CC0();
        break;
      default:
        goto LABEL_43;
    }
  }
}

// 0x00498820
EquipUI::EquipUI()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  *(_DWORD *)&this->buf[8] = 800;
  *(_DWORD *)&this->buf[12] = 600;
  *(_DWORD *)&this->buf[24] = 0;
  *((_BYTE *)&this->m_EquipData + 244) = 0;
  *((_DWORD *)&this->m_EquipData + 63) = 0;
  *((_BYTE *)&this->m_EquipData + 257) = 0;
  *((_DWORD *)&this->m_EquipData + 65) = 0;
  *((_DWORD *)&this->m_EquipData + 66) = 0;
  *((_DWORD *)&this->m_EquipData + 67) = 0;
  *((_DWORD *)&this->m_EquipData + 68) = 0;
  *((_BYTE *)&this->m_EquipData + 277) = 0;
  *((_BYTE *)&this->m_EquipData + 278) = 0;
  *((_BYTE *)&this->m_EquipData + 279) = 0;
  *((_DWORD *)&this->m_EquipData + 70) = 0;
  (((UIFrameContainer *)((char *)&this->m_EquipData + 284)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 436)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 588)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 740)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 892)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 1044)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 4292)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 4460)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 4612)))->UIFrameContainer::ResetContainerState();
  ((UIRoleDialog *)&this[1].m_Arrow[1][3][1].m_childs.m_nSize)->UIRoleDialog::UIRoleDialog();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][1].m_pfather))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][2].m_pfather))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][3].m_pfather))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][4].m_childs.m_needscriptdel))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1].m_Arrow[7][2][0].m_childs.m_needscriptdel))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1].m_Arrow[8][0][4].m_text[8]))->UIFrameContainer::ResetContainerState();
  ((UI3DCtrl *)&this[1].m_Arrow[8][1][0].m_text[8])->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)&this[1].m_Arrow[8][1][1].m_childs))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)&this[1].m_ArrowNum[0][1][1].m_fonttype))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1].m_ArrowNum[1][0][4].m_textx))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1].m_ArrowNum[2][0][2].m_ratiow))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1].m_ArrowNum[3][0][0].pDebugTex))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1].m_ArrowNum[3][1][3].m_benable))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1].m_ArrowNum[4][1][1].m_bcreateok))->UIListBox::UpdateKeyCtrl();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  this[1].m_ArrowNum[6][0][3].m_bfocus = -1;
  (((UIProgressBar *)&this[1].m_ArrowNum[6][0][3].pDebugTex))->UIProgressBar::ctor();
  *((_BYTE *)&this->m_EquipData + 249) = 0;
  *((_BYTE *)&this->m_EquipData + 248) = 0;
  *((_BYTE *)&this->m_EquipData + 246) = 0;
  *((_BYTE *)&this->m_EquipData + 245) = 0;
  *((_BYTE *)&this->m_EquipData + 247) = 0;
  this[1].m_Arrow[1][3][1].m_pfather = ((UIWnd *)0);
  this[1].m_Arrow[1][3][1].m_childs.m_pData = ((char *)0);
  this[1].m_Arrow[1][3][1].m_childs.capacity = 0;
}

// 0x00499030
EquipUI::~EquipUI()
{
  (((PalScript *)&this[1].m_ArrowNum[6][0][3].pDebugTex))->PalScript::Reset();
  (((UICaption *)&this[1].m_ArrowNum[6][0][1].m_rect.right))->UICaption::Destroy2();
  (((UICaption *)&this[1].m_ArrowNum[5][1][3].m_pbk2))->UICaption::Destroy2();
  (((UICaption *)this[1].m_ArrowNum[5][1][1].m_text))->UICaption::Destroy2();
  (((UIListBox *)&this[1].m_ArrowNum[4][1][1].m_bcreateok))->UIListBox::DeleteRow();
  (((UIListBox *)&this[1].m_ArrowNum[3][1][3].m_benable))->UIListBox::DeleteRow();
  (((UIListBox *)&this[1].m_ArrowNum[3][0][0].pDebugTex))->UIListBox::DeleteRow();
  (((UIListBox *)&this[1].m_ArrowNum[2][0][2].m_ratiow))->UIListBox::DeleteRow();
  (((UIListBox *)&this[1].m_ArrowNum[1][0][4].m_textx))->UIListBox::DeleteRow();
  (((UIListBox *)&this[1].m_ArrowNum[0][1][1].m_fonttype))->UIListBox::DeleteRow();
  (((UIFrameContainer *)&this[1].m_Arrow[8][1][1].m_childs))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((EquipUI *)((char *)this + 185092));
  (((UIFrameContainer *)&this[1].m_Arrow[8][0][4].m_text[8]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].m_Arrow[7][2][0].m_childs.m_needscriptdel))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][4].m_childs.m_needscriptdel))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][3].m_pfather))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][2].m_pfather))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].m_Arrow[7][1][1].m_pfather))->UIFrameContainer::~UIFrameContainer();
  (((UIRoleDialog *)&this[1].m_Arrow[1][3][1].m_childs.m_nSize))->UIRoleDialog::~UIRoleDialog();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 4612)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 4460)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 4292)))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)((char *)&this->m_EquipData + 3948)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 3604)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 3260)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 2916)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 2572)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 2228)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 1884)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 1540)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_EquipData + 1196)))->UICaption::Destroy2();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 1044)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 892)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 740)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 588)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 436)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)((char *)&this->m_EquipData + 284)))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0049E840
int EquipUI::SetSubTab2(unsigned __int8 nTab)
{
  *((_BYTE *)&this->m_EquipData + 245) = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState2(0, nTab);
}

// 0x0049F9B0
int EquipUI::SetGroupVisible(unsigned __int8 bVisible)
{
  sub_445E50((int)&this[1].m_ArrowNum[0][1][1].m_fonttype);
  sub_445E50((int)&this[1].m_ArrowNum[1][0][4].m_textx);
  sub_445E50((int)&this[1].m_ArrowNum[2][0][2].m_ratiow);
  sub_445E50((int)&this[1].m_ArrowNum[3][0][0].pDebugTex);
  sub_445E50((int)&this[1].m_ArrowNum[3][1][3].m_benable);
  return sub_445E50((int)&this[1].m_ArrowNum[4][1][1].m_bcreateok);
}

// 0x0049FA10
int EquipUI::InitParticleEffects(int nVal)
{
  _DWORD *v4; // esi
  int *v5; // ebx
  int v6; // edi
  RenderTarget *v7; // ebp
  int v8; // eax
  int v9; // eax
  int *p_m_nScaleX; // edi
  RenderTarget *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  float fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  float fYb; // [esp+0x4] [ebp-0x20]
  _DWORD *v20; // [esp+0x18] [ebp-0xC]
  int v21; // [esp+0x1C] [ebp-0x8]
  int nVala; // [esp+0x28] [ebp+0x4]

  this[1].m_Arrow[1][3][1].m_pfather = ((UIWnd *)0);
  this[1].m_Arrow[1][3][1].m_childs.m_pData = ((char *)0);
  nVala = 16;
  *((_BYTE *)&this[1].m_Arrow[1][3][1].m_pfather + nVal) = 1;
  v4 = (_DWORD *)((char *)this + 16 * nVal);
  v20 = (_DWORD *)v4;
  v5 = (int *)v4 + 38661;
  v6 = (unsigned long)(v4[38663] - v4[38661]);
  v21 = v6;
  v7 = (RenderTarget *)((char *)&this->m_EquipData + 9344 * nVal + 4764);
  while ( 1 )
  {
    (((RenderTarget *)v7))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v7))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 98;
    fX = rand() % 10 + 168;
    v8 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetColor(v8 % 10 + 68, fX, fY);
    v9 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetAlpha(v9 % 55 - 56);
    *((_BYTE *)&v7->m_ScreenPlane + 4) = 1;
    (((RenderTarget *)v7))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v7))->RenderTarget::SetState(1067030938);
    fYa = (float)(int)v4[38662];
    fXa = (float)(*v5 + rand() % v6);
    (((RenderTarget *)v7))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v7))->RenderTarget::Render(*v5, v5[1], v5[2]);
    fYb = (float)(rand() % 2 + 1);
    fXb = (float)(rand() % 2 + 1);
    (((RenderTarget *)v7))->RenderTarget::SetOffset(fXb, fYb);
    (((RenderTarget *)v7))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v7))->RenderTarget::SetVisible(1);
    p_m_nScaleX = (int *)&v7[373].m_nScaleX;
    v11 = (RenderTarget *)v7;
    v7 = (RenderTarget *)((char *)v7 + 584);
    result = nVala - 1;
    v12 = nVala == 1;
    qmemcpy(p_m_nScaleX, v11, 0x248u);
    --nVala;
    if ( v12 )
      break;
    v4 = (_DWORD *)v20;
    v6 = v21;
  }
  return result;
}

// 0x0049FBE0
BOOL EquipUI::UpdateDisplay(int nPage, int nSlot)
{
  BOOL result; // eax
  int v5; // ebx
  int v6; // ebp
  int v7; // edi
  int v8; // edi
  float v9; // st7
  RenderTarget *v10; // ebx
  int v11; // eax
  int v12; // eax
  _BYTE *p_m_nTodo_028; // edi
  RenderTarget *v14; // esi
  bool v15; // zf
  int fVal1; // [esp+0x0] [ebp-0x30]
  float fVal1a; // [esp+0x0] [ebp-0x30]
  int fVal1b; // [esp+0x0] [ebp-0x30]
  int fVal2; // [esp+0x4] [ebp-0x2C]
  float fVal2a; // [esp+0x4] [ebp-0x2C]
  int fVal2b; // [esp+0x4] [ebp-0x2C]
  float fX; // [esp+0x18] [ebp-0x18]
  int v23; // [esp+0x1C] [ebp-0x14]
  float fY; // [esp+0x28] [ebp-0x8]
  int nPageb; // [esp+0x34] [ebp+0x4]
  int nPagea; // [esp+0x34] [ebp+0x4]

  LOBYTE(result) = *((_BYTE *)&this->m_EquipData + nPage + 245);
  if ( result )
  {
    v5 = *(&this[2].m_OutFrameT.m_rect.right + 4 * nPage);
    v6 = *((_DWORD *)&this[2].m_OutFrameT.m_pfather + 4 * nPage) - v5;
    v7 = *((_DWORD *)&this[2].m_OutFrameT.m_childs.m_pData + 4 * nPage);
    nPageb = *(&this[2].m_OutFrameT.m_rect.bottom + 4 * nPage);
    v8 = v7 - nPageb;
    v23 = v8;
    v9 = (float)nPageb;
    nPagea = 12;
    fX = (float)(v5 + v6 / 2);
    v10 = (RenderTarget *)(&this[1].m_ArrowNum[6][1][0].m_align + 1752 * nPage);
    while ( 1 )
    {
      (((RenderTarget *)v10))->RenderTarget::LoadTexture(szFilename);
      (((RenderTarget *)v10))->RenderTarget::SetSize(32);
      fVal2 = (unsigned __int8)nSlot + rand() % 10;
      fVal1 = BYTE1(nSlot) + rand() % 10;
      v11 = rand();
      (((RenderTarget *)v10))->RenderTarget::SetColor(BYTE2(nSlot) + v11 % 10, fVal1, fVal2);
      v12 = rand();
      (((RenderTarget *)v10))->RenderTarget::SetAlpha(v12 % 135 + 120);
      (((RenderTarget *)v10))->RenderTarget::SetField084(1065353216);
      (((RenderTarget *)v10))->RenderTarget::SetState(1061997773);
      fY = v9;
      (((RenderTarget *)v10))->RenderTarget::UpdateTransform(fX, fY);
      (((RenderTarget *)v10))->RenderTarget::CalcRenderDimensions(v6, v8);
      fVal2a = (float)(rand() % 2 + 1);
      fVal1a = (float)(rand() % 2 + 1);
      (((RenderTarget *)v10))->RenderTarget::SetOffset(fVal1a, fVal2a);
      *(float *)&fVal2b = (float)(rand() % 2 + 2);
      *(float *)&fVal1b = (float)(rand() % 2 + 2);
      (((RenderTarget *)v10))->RenderTarget::SetScale(fVal1b, fVal2b);
      (((RenderTarget *)v10))->RenderTarget::SetVisible(1);
      p_m_nTodo_028 = (_BYTE *)&v10[175].m_nTodo_028;
      v14 = (RenderTarget *)v10;
      v10 = (RenderTarget *)((char *)v10 + 584);
      result = nPagea - 1;
      v15 = nPagea == 1;
      qmemcpy(p_m_nTodo_028, v14, 0x248u);
      --nPagea;
      if ( v15 )
        break;
      v8 = v23;
    }
  }
  return result;
}

// 0x0049FE00
int EquipUI::EquipUI_RenderEffects(int nVal)
{
  CCBControlWindow *v1; // ecx
  CCBControlWindow *v2; // esi
  int v3; // eax
  UIParticle *p_m_bvisible; // edi
  int v5; // ebp
  int result; // eax
  int i; // edi
  CCBMagicWindow *v8; // [esp+0x0] [ebp-0x18]
  int v9; // [esp+0x10] [ebp-0x8]
  UIParticle *v10; // [esp+0x14] [ebp-0x4]

  v2 = (CCBControlWindow *)v1;
  (((CCBControlWindow *)v1))->CCBControlWindow::Render(v8);
  v3 = 0;
  p_m_bvisible = (UIParticle *)&v2[1179].m_bvisible;
  v9 = 0;
  v10 = (UIParticle *)&v2[1179].m_bvisible;
  do
  {
    if ( *((_BYTE *)&v2[3].m_pfather + v3 + 1) )
    {
      v5 = 12;
      do
      {
        if ( IsVisible((RenderTarget *)&p_m_bvisible[-60]) )
          ((UIParticle *)(p_m_bvisible - 60))->UIParticle::Apply(8);
        if ( IsVisible((RenderTarget *)p_m_bvisible) )
          (((UIParticle *)p_m_bvisible))->UIParticle::Apply(7);
        ++p_m_bvisible;
        --v5;
      }
      while ( v5 );
      v3 = v9;
    }
    ++v3;
    p_m_bvisible = (UIParticle *)(v10 + 12);
    v9 = v3;
    v10 += 12;
  }
  while ( v3 < 5 );
  result = *((_DWORD *)&v2[789].m_CurCtrl_2 + 4);
  if ( *((_BYTE *)&v2[789].m_CurCtrl_2 + result + 8) )
  {
    for ( i = 0; i < 16; ++i )
    {
      if ( IsVisible((RenderTarget *)(&v2[26].m_childs.m_nSize + 2336 * *((_DWORD *)&v2[789].m_CurCtrl_2 + 4) + 146 * i)) )
        ((UIParticle *)((UIParticle *)&v2[26].m_childs.m_nSize + 16 * *((_DWORD *)&v2[789].m_CurCtrl_2 + 4) + i))->UIParticle::Apply(11);
      LOBYTE(result) = IsVisible((RenderTarget *)(&v2[407].m_CurCtrl_2
                                                + 2336 * *((_DWORD *)&v2[789].m_CurCtrl_2 + 4)
                                                + 146 * i));
      if ( (_BYTE)result )
        ((UIParticle *)((UIParticle *)&v2[407].m_CurCtrl_2 + 16 * *((_DWORD *)&v2[789].m_CurCtrl_2 + 4) + i))->UIParticle::Apply(10);
    }
  }
  return result;
}

// 0x0049FF30
int EquipUI::FindNextSlot(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  ++*pCounter;
  while ( 1 )
  {
    v2 = (unsigned long)*pCounter;
    if ( *((_BYTE *)&this->m_EquipData + *pCounter + 245) )
    {
      if ( v2 <= 4 )
        break;
    }
    v3 = v2 + 1;
    *pCounter = v3;
    if ( v3 > 4 )
      *pCounter = 0;
  }
  return *pCounter;
}

// 0x0049FF60
int EquipUI::FindPrevSlot(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  --*pCounter;
  while ( 1 )
  {
    v2 = (unsigned long)*pCounter;
    if ( *((_BYTE *)&this->m_EquipData + *pCounter + 245) )
    {
      if ( v2 >= 0 )
        break;
    }
    v3 = v2 - 1;
    *pCounter = v3;
    if ( v3 < 0 )
      *pCounter = 4;
  }
  return *pCounter;
}

// 0x0049FF90
char EquipUI::NavigateSlots()
{
  char result; // al
  int *v3; // edi
  int PrevSlot; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax

  result = BYTE1(this[1].m_Arrow[1][5][0].m_rect.left);
  if ( !result )
  {
    result = 1;
    if ( *((_BYTE *)&this->m_EquipData + 277) )
    {
      if ( g_Input.KeyInfo[10].PressTime == 1 )
      {
        v3 = (int *)((char *)&this->m_EquipData + 252);
        PrevSlot = this->EquipUI::FindPrevSlot((int *)&this->m_EquipData + 63);
LABEL_7:
        v5 = (int)((UIWnd *)this);
        *v3 = PrevSlot;
        return (*(int ( **)(EquipUI *, int, _DWORD, _DWORD))(v5 + 24))(
                 this,
                 1001,
                 *(&dword_56E148 + PrevSlot),
                 0);
      }
      if ( g_Input.KeyInfo[9].PressTime == 1 )
      {
        v3 = (int *)((char *)&this->m_EquipData + 252);
        PrevSlot = this->EquipUI::FindNextSlot((int *)&this->m_EquipData + 63);
        goto LABEL_7;
      }
      if ( g_Input.KeyInfo[8].PressTime == 1 )
      {
        return (*(int ( **)(EquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(this, 1010, 0, 0);
      }
      else if ( g_Input.KeyInfo[6].PressTime == 1 )
      {
        return (*(int ( **)(EquipUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
                 this,
                 1020,
                 *(&dword_56E148 + *((_DWORD *)&this->m_EquipData + 63)),
                 0);
      }
    }
    else
    {
      if ( g_Input.KeyInfo[2].PressTime == 1 )
      {
        v6 = *((_DWORD *)&this->m_EquipData + 65) - 1;
        *((_DWORD *)&this->m_EquipData + 65) = v6;
        if ( v6 < 0 )
          *((_DWORD *)&this->m_EquipData + 65) = 0;
      }
      else
      {
        if ( g_Input.KeyInfo[3].PressTime != 1 )
          return result;
        v7 = *((_DWORD *)&this->m_EquipData + 65) + 1;
        *((_DWORD *)&this->m_EquipData + 65) = v7;
        if ( v7 >= 5 )
          *((_DWORD *)&this->m_EquipData + 65) = 5;
      }
      return (*(int ( **)(EquipUI *, int, const char *, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
               this,
               1001,
               (&off_56E130)[*((_DWORD *)&this->m_EquipData + 65)],
               0);
    }
  }
  return result;
}

// 0x004A00B0
BOOL EquipUI::Update(int nVal, int nVal2)
{
  __int64 v4; // rax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  char v8; // cl
  float *v9; // eax
  int v10; // eax
  char v11; // cl
  float *v12; // eax
  float *v13; // eax
  int v14; // eax
  int v16; // [esp-0x4] [ebp-0x28]
  int v17; // [esp+0x20] [ebp-0x4]

  v4 = (__int64)g_fGameTimer;
  v5 = (int)v4 / 3600;
  v17 = (int)v4 / 60 % 60;
  v16 = (int)v4 % 60;
  if ( (int)v4 / 3600 < 100 )
    sprintf(&this->buf[28], "%02d:%02d:%02d", v5, v17, v16);
  else
    sprintf(&this->buf[28], "%03d:%02d:%02d", v5, v17, v16);
  SetEnable((UICaption *)((char *)&this->m_EquipData + 4460));
  sprintf(&this->buf[28], (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)((char *)&this->m_EquipData + 4612));
  if ( *((_BYTE *)&this->m_EquipData + 256) )
  {
    this->EquipUI::NavigateSlots();
    *(_DWORD *)&this->buf[16] = 0;
    do
    {
      v6 = *(_DWORD *)&this->buf[16];
      if ( *((_BYTE *)&this->m_EquipData + v6 + 245) )
      {
        v7 = 1223 * v6;
        v8 = (char)(&this[1].m_Arrow[2][0][1].m_fonttype)[v7];
        v9 = (float *)((char *)this + v7 * 4);
        if ( !v8 )
        {
          sprintf(
            &this->buf[28],
            "%d/%d",
            (int)v9[39277],
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)&this->buf[16]));
          SetEnable((UICaption *)(&this[1].m_Arrow[2][0][2].m_rect.right + 1223 * *(_DWORD *)&this->buf[16]));
        }
        v10 = 4892 * *(_DWORD *)&this->buf[16];
        v11 = *((_BYTE *)&this[1].m_Arrow[2][1][3].m_ppicInfo + v10);
        v12 = (float *)((char *)this + v10);
        if ( !v11 )
        {
          sprintf(
            &this->buf[28],
            "%d/%d",
            (int)v12[39551],
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)&this->buf[16] + 1));
          SetEnable((UICaption *)(&this[1].m_Arrow[2][1][4].m_bvisible + 1223 * *(_DWORD *)&this->buf[16]));
        }
        v13 = (float *)((char *)this + 4892 * *(_DWORD *)&this->buf[16]);
        if ( !*((_BYTE *)v13 + 157660) )
        {
          sprintf(
            &this->buf[28],
            "%d/%d",
            (int)v13[39414],
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)&this->buf[16] + 2));
          SetEnable((UICaption *)(&this[1].m_Arrow[2][1][0].m_pbkInfo + 1223 * *(_DWORD *)&this->buf[16]));
        }
        (((UIFrameWnd *)((char *)this + 52 * *(_DWORD *)&this->buf[16] + 194400)))->UIFrameWnd::ProcessTimer(1, 1, 2, *((_DWORD *)((UIWnd *)&this[1].m_ArrowNum[5][1][1]) + 4 * *(_DWORD *)&this->buf[16]));
      }
      v14 = *(_DWORD *)&this->buf[16] + 1;
      *(_DWORD *)&this->buf[16] = v14;
    }
    while ( v14 < 5 );
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x004A0370
void EquipUI::HandleEquipEvent(int nVal, char *pszBuf, int nVal2)
{
  int i; // edi
  UICursor *v6; // ecx
  int v7; // edx
  int *v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ebp
  char *p_m_bvisible; // edi
  int *v13; // eax
  int v14; // ecx
  int v15; // eax
  char v16; // al
  int v17; // edi
  int v18; // ebp
  char *v19; // edi
  char *v20; // edi
  int v21; // ebp
  char v22; // al
  CScreenMode *v23; // eax
  CScreenMode *v24; // eax
  CScreenMode *v25; // eax
  CScreenMode *v26; // eax
  CScreenMode *v27; // eax
  CScreenMode *v28; // eax
  CScreenMode *v29; // eax
  CScreenMode *Instance; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  signed int v34; // eax
  int v35; // eax
  int v36; // eax
  int *v37; // eax
  int v38; // ecx
  int v39; // eax
  int v40; // edi
  char *v41; // ebp
  int v42; // edi
  char *v43; // ebp
  char *v44; // esi
  int v45; // edi
  char *v46; // edi
  int v47; // ebp
  int *v48; // eax
  int v49; // ecx
  char v50; // al
  CCBFiveNimbusWindow *p_pDebugTex; // edi
  const char *v52; // ebp
  CScreenMode *v53; // eax
  UIListBox *p_m_fonttype; // edi
  int *v55; // eax
  int v56; // edi
  char *v57; // ebp
  CScreenMode *v58; // eax
  const void *v59; // [esp-0x8] [ebp-0x158]
  const void *v60; // [esp-0x8] [ebp-0x158]
  const void *v61; // [esp-0x8] [ebp-0x158]
  const void *v62; // [esp-0x8] [ebp-0x158]
  const void *v63; // [esp-0x8] [ebp-0x158]
  const void *v64; // [esp-0x8] [ebp-0x158]
  const void *v65; // [esp-0x8] [ebp-0x158]
  const void *v66; // [esp-0x8] [ebp-0x158]
  const void *v67; // [esp-0x8] [ebp-0x158]
  const void *v68; // [esp-0x8] [ebp-0x158]
  float v69; // [esp-0x4] [ebp-0x154]
  int a2; // [esp+0x10] [ebp-0x140]
  int nItemID; // [esp+0x14] [ebp-0x13C] BYREF
  int v72; // [esp+0x18] [ebp-0x138]
  int v73; // [esp+0x1C] [ebp-0x134]
  _BYTE v74[12]; // [esp+0x20] [ebp-0x130] BYREF
  int v75[3]; // [esp+0x2C] [ebp-0x124] BYREF
  _BYTE v76[12]; // [esp+0x38] [ebp-0x118] BYREF
  _BYTE pOut[12]; // [esp+0x44] [ebp-0x10C] BYREF
  char Buffer[253]; // [esp+0x50] [ebp-0x100] BYREF
  __int16 v79; // [esp+0x14D] [ebp-0x3]
  char v80; // [esp+0x14F] [ebp-0x1]

  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        for ( i = 0; i < 8; ++i )
          this->EquipUI::InitParticleEffects(i);
        (((ArcSceneObject *)this))->ArcSceneObject::ResetEquipControls();
        (((StateUI *)this))->StateUI::ShowPage() /* [ROWTABLE] */;
        g_nSceneState = 1;
        *((_BYTE *)&this->m_EquipData + 256) = 1;
        this[1].m_Arrow[1][3][1].m_pfather = ((UIWnd *)0);
        this[1].m_Arrow[1][3][1].m_childs.m_pData = ((char *)0);
        *((_BYTE *)&this->m_EquipData + 276) = 0;
        (((UICursor *)v6))->UICursor::_todo_541CC0();
      }
      else
      {
        *((_BYTE *)&this->m_EquipData + 256) = 0;
      }
      return;
    case 1001:
      v7 = 0;
      v8 = (int *)&dword_56E148;
      while ( pszBuf != (char *)*v8 )
      {
        ++v8;
        ++v7;
        if ( (int)v8 >= (int)&g_ArcSceneMonsterTable2 )
        {
          *(_DWORD *)&this->buf[16] = 0;
          do
          {
            v9 = *(_DWORD *)&this->buf[16];
            if ( (&off_56E130)[v9] == pszBuf )
            {
              (((MainEquipUI *)this))->MainEquipUI::ShowWithCursor(*(_DWORD *)&this->buf[16]) /* [ROWTABLE] */;
              v59 = (const void *)off_5CADC4;
              goto LABEL_176;
            }
            v10 = v9 + 1;
            *(_DWORD *)&this->buf[16] = v10;
          }
          while ( v10 < 6 );
          if ( pszBuf <= (char *)&byte_A00110 )
          {
            if ( pszBuf == (char *)&byte_A00110 )
            {
              v67 = (const void *)off_5CADC4;
              Instance = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v67, 1);
              (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(9);
            }
            else
            {
              switch ( (unsigned int)pszBuf )
              {
                case 0xA00102u:
                  v60 = (const void *)off_5CADC4;
                  v23 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v23))->CScreenMode::AudioSetPosition(v60, 1);
                  (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(0);
                  break;
                case 0xA00103u:
                  v61 = (const void *)off_5CADC4;
                  v24 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v24))->CScreenMode::AudioSetPosition(v61, 1);
                  (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(3);
                  break;
                case 0xA00104u:
                  v62 = (const void *)off_5CADC4;
                  v25 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v25))->CScreenMode::AudioSetPosition(v62, 1);
                  (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(2);
                  break;
                case 0xA00106u:
                  v63 = (const void *)off_5CADC4;
                  v26 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v26))->CScreenMode::AudioSetPosition(v63, 1);
                  (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(5);
                  break;
                case 0xA00107u:
                  v64 = (const void *)off_5CADC4;
                  v27 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v27))->CScreenMode::AudioSetPosition(v64, 1);
                  (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(6);
                  break;
                case 0xA00108u:
                  v65 = (const void *)off_5CADC4;
                  v28 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v28))->CScreenMode::AudioSetPosition(v65, 1);
                  (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(4);
                  break;
                case 0xA00109u:
                  v66 = (const void *)off_5CADC4;
                  v29 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v29))->CScreenMode::AudioSetPosition(v66, 1);
                  (((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70)))->MainEquipUI::HandleMessage(7);
                  break;
                default:
                  return;
              }
            }
            return;
          }
          if ( pszBuf == (char *)&byte_A00427 )
          {
            if ( *((_BYTE *)&this->m_EquipData + 278) )
            {
              v59 = (const void *)off_5CADD0;
              goto LABEL_176;
            }
            this[1].m_ArrowNum[6][0][3].m_bfocus = -1;
          }
          else if ( pszBuf - (char *)&byte_A00427 == 1 )
          {
            if ( *((_BYTE *)&this->m_EquipData + 278) )
            {
              v59 = (const void *)off_5CADD0;
              goto LABEL_176;
            }
            this[1].m_ArrowNum[6][0][3].m_bfocus = 0;
          }
          else
          {
            if ( pszBuf - (char *)&byte_A00427 != 2 )
              return;
            if ( *((_BYTE *)&this->m_EquipData + 278) )
            {
              v59 = (const void *)off_5CADD0;
              goto LABEL_176;
            }
            this[1].m_ArrowNum[6][0][3].m_bfocus = 3;
          }
          (((MainEquipUI *)this))->MainEquipUI::SetupRoleList(*((_DWORD *)&this->m_EquipData + 65), 0) /* [ROWTABLE] */;
          v31 = (unsigned long)off_5CADC4;
          goto LABEL_175;
        }
      }
      a2 = v7;
      if ( *((int *)&this->m_EquipData + 67) >= 0 && *((_BYTE *)&this->m_EquipData + 277) )
      {
        v11 = 0;
        p_m_bvisible = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
        do
        {
          if ( *((_BYTE *)&this->m_EquipData + v11 + 245) )
            (**(void ( ***)(char *, _DWORD))p_m_bvisible)((char *)(p_m_bvisible), (_DWORD)(0));
          ++v11;
          p_m_bvisible += 4892;
        }
        while ( v11 < 5 );
        v13 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, *((_DWORD *)&this->m_EquipData + 67));
        nItemID = (unsigned long)*v13;
        v14 = (unsigned long)v13[1];
        v72 = v14;
        v15 = (unsigned long)v13[2];
        v73 = v15;
        if ( !v15 || v14 <= 0 )
        {
          *((_BYTE *)&this->m_EquipData + 276) = 0;
          v20 = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
          v21 = 5;
          do
          {
            (**(void ( ***)(char *, _DWORD))v20)((char *)(v20), (_DWORD)(0));
            v20 += 4892;
            --v21;
          }
          while ( v21 );
          *((_BYTE *)&this->m_EquipData + 278) = 0;
          *((_BYTE *)&this->m_EquipData + 277) = 0;
          this->EquipUI::SetGroupVisible(1u);
          return;
        }
        if ( *((_DWORD *)&this->m_EquipData + 65) )
        {
          v17 = a2;
          if ( (((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)&nItemID, a2) )
            goto LABEL_25;
          goto LABEL_40;
        }
        v16 = *(_BYTE *)(v15 + 629);
        if ( v16 == 1 )
        {
          v17 = a2;
          if ( (((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)&nItemID, a2) )
          {
LABEL_25:
            (**((void ( ***)(int *, int))&this[1].m_Arrow[2][5][1].m_bvisible + 1223 * v17))((int *)(&this[1].m_Arrow[2][5][1].m_bvisible + 1223 * v17), (int)(1));
            goto LABEL_40;
          }
          (((PAL_GDB *)this))->PAL_GDB::SelectBestTarget(*((_DWORD *)&this->m_EquipData + 67));
LABEL_40:
          v22 = *((_BYTE *)&this->m_EquipData + 276);
          *((_DWORD *)&this->m_EquipData + 63) = v17;
          if ( !v22 )
          {
            (((StateUI *)this))->StateUI::DisplayCaption(v17) /* [ROWTABLE] */;
            if ( !*((_BYTE *)&this->m_EquipData + 277) )
              (((MainEquipUI *)this))->MainEquipUI::SetupRoleList(*((_DWORD *)&this->m_EquipData + 65), 1) /* [ROWTABLE] */;
          }
          v59 = (const void *)off_5CADC4;
          goto LABEL_176;
        }
        if ( v16 == 2 )
        {
          v18 = 0;
          v19 = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
          do
          {
            if ( (((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)&nItemID, v18) )
              (**(void ( ***)(char *, int))v19)((char *)(v19), (int)(1));
            ++v18;
            v19 += 4892;
          }
          while ( v18 < 5 );
        }
      }
      else
      {
        *((_BYTE *)&this->m_EquipData + 276) = 0;
      }
      v17 = a2;
      goto LABEL_40;
    case 1002:
      *(_DWORD *)&this->buf[16] = 0;
      while ( 1 )
      {
        v35 = *(_DWORD *)&this->buf[16];
        if ( *((_BYTE *)&this->m_EquipData + v35 + 245) )
        {
          if ( pszBuf == (char *)*(&dword_56E148 + v35) )
            break;
        }
        v36 = v35 + 1;
        *(_DWORD *)&this->buf[16] = v36;
        if ( v36 >= 5 )
        {
          switch ( (unsigned int)pszBuf )
          {
            case 0xA00102u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 0;
              if ( !LOBYTE(this[1].m_Arrow[1][3][1].m_pfather) )
                this->EquipUI::InitParticleEffects(0);
              break;
            case 0xA00103u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 1;
              if ( !BYTE1(this[1].m_Arrow[1][3][1].m_pfather) )
                this->EquipUI::InitParticleEffects(1);
              break;
            case 0xA00104u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 2;
              if ( !BYTE2(this[1].m_Arrow[1][3][1].m_pfather) )
                this->EquipUI::InitParticleEffects(2);
              break;
            case 0xA00105u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 3;
              if ( !HIBYTE(this[1].m_Arrow[1][3][1].m_pfather) )
                this->EquipUI::InitParticleEffects(3);
              break;
            case 0xA00106u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 5;
              if ( !BYTE1(this[1].m_Arrow[1][3][1].m_childs.m_pData) )
                this->EquipUI::InitParticleEffects(5);
              break;
            case 0xA00107u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 6;
              if ( !BYTE2(this[1].m_Arrow[1][3][1].m_childs.m_pData) )
                this->EquipUI::InitParticleEffects(6);
              break;
            case 0xA00108u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 4;
              if ( !LOBYTE(this[1].m_Arrow[1][3][1].m_childs.m_pData) )
                this->EquipUI::InitParticleEffects(4);
              break;
            case 0xA00109u:
              this[1].m_Arrow[1][3][1].m_childs.capacity = 7;
              if ( !HIBYTE(this[1].m_Arrow[1][3][1].m_childs.m_pData) )
                this->EquipUI::InitParticleEffects(7);
              break;
            default:
              return;
          }
          return;
        }
      }
      if ( *((int *)&this->m_EquipData + 67) < 0 || !*((_BYTE *)&this->m_EquipData + 277) )
        return;
      v37 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v74, *((_DWORD *)&this->m_EquipData + 67));
      nItemID = (unsigned long)*v37;
      v72 = (unsigned long)v37[1];
      v38 = *((_DWORD *)&this->m_EquipData + 65);
      v39 = (unsigned long)v37[2];
      v73 = v39;
      if ( !v38 )
      {
        if ( *(_BYTE *)(v39 + 629) != 1 )
          return;
        v40 = 0;
        v41 = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
        do
        {
          if ( *((_BYTE *)&this->m_EquipData + v40 + 245) )
            (**(void ( ***)(char *, _DWORD))v41)((char *)(v41), (_DWORD)(0));
          ++v40;
          v41 += 4892;
        }
        while ( v40 < 5 );
        if ( !(((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)&nItemID, *(_DWORD *)&this->buf[16]) )
        {
          (((PAL_GDB *)this))->PAL_GDB::SelectBestTarget(*((_DWORD *)&this->m_EquipData + 67));
          return;
        }
        goto LABEL_103;
      }
      v42 = 0;
      v43 = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
      do
      {
        if ( *((_BYTE *)&this->m_EquipData + v42 + 245) )
          (**(void ( ***)(char *, _DWORD))v43)((char *)(v43), (_DWORD)(0));
        ++v42;
        v43 += 4892;
      }
      while ( v42 < 5 );
      if ( (((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)&nItemID, *(_DWORD *)&this->buf[16]) )
      {
LABEL_103:
        (**((void ( ***)(int *, int))&this[1].m_Arrow[2][5][1].m_bvisible
          + 1223 * *(_DWORD *)&this->buf[16]))((int *)(&this[1].m_Arrow[2][5][1].m_bvisible + 1223 * *(_DWORD *)&this->buf[16]), (int)(1));
        return;
      }
      return;
    case 1003:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00102u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 0;
          LOBYTE(this[1].m_Arrow[1][3][1].m_pfather) = 0;
          break;
        case 0xA00103u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 1;
          BYTE1(this[1].m_Arrow[1][3][1].m_pfather) = 0;
          break;
        case 0xA00104u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 2;
          BYTE2(this[1].m_Arrow[1][3][1].m_pfather) = 0;
          break;
        case 0xA00105u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 3;
          HIBYTE(this[1].m_Arrow[1][3][1].m_pfather) = 0;
          break;
        case 0xA00106u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 5;
          BYTE1(this[1].m_Arrow[1][3][1].m_childs.m_pData) = 0;
          break;
        case 0xA00107u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 6;
          BYTE2(this[1].m_Arrow[1][3][1].m_childs.m_pData) = 0;
          break;
        case 0xA00108u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 4;
          LOBYTE(this[1].m_Arrow[1][3][1].m_childs.m_pData) = 0;
          break;
        case 0xA00109u:
          this[1].m_Arrow[1][3][1].m_childs.capacity = 7;
          HIBYTE(this[1].m_Arrow[1][3][1].m_childs.m_pData) = 0;
          break;
        default:
          return;
      }
      return;
    case 1007:
      *((_DWORD *)&this->m_EquipData + 67) = nVal2;
      if ( nVal2 < 0 )
      {
        SetEnable((UICaption *)&this[1].m_Arrow[7][1][2].m_pfather);
        SetEnable((UICaption *)&this[1].m_Arrow[7][1][3].m_pfather);
        this[1].m_ArrowNum[6][0][3].m_FVF = 0;
        v46 = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
        v47 = 5;
        do
        {
          (**(void ( ***)(char *, _DWORD))v46)((char *)(v46), (_DWORD)(0));
          v46 += 4892;
          --v47;
        }
        while ( v47 );
        goto LABEL_135;
      }
      v48 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v75, nVal2);
      nItemID = (unsigned long)*v48;
      v72 = (unsigned long)v48[1];
      v49 = (unsigned long)*v48;
      v73 = (unsigned long)v48[2];
      (((MainEquipUI *)this))->MainEquipUI::SetSlotLabel(v49, v48[1], v48[2]) /* [ROWTABLE] */;
      v50 = *(_BYTE *)(v73 + 612);
      if ( v50 == 11 )
      {
        (((CCBFiveNimbusWindow *)&this[1].m_ArrowNum[6][0][3].pDebugTex))->CCBFiveNimbusWindow::SetFloatParam(228.0);
        (((Camera *)&this[1].m_ArrowNum[6][0][3].pDebugTex))->Camera::UpdateCameraLookAt(128, 262, 600);
        goto LABEL_141;
      }
      if ( v50 == 6 )
      {
        p_pDebugTex = (CCBFiveNimbusWindow *)&this[1].m_ArrowNum[6][0][3].pDebugTex;
        v69 = 200.0f;
LABEL_140:
        (((CCBFiveNimbusWindow *)p_pDebugTex))->CCBFiveNimbusWindow::SetFloatParam(v69);
        (((Camera *)p_pDebugTex))->Camera::UpdateCameraLookAt(128, 258, 600);
        goto LABEL_141;
      }
      p_pDebugTex = (CCBFiveNimbusWindow *)&this[1].m_ArrowNum[6][0][3].pDebugTex;
      v69 = 160.0f;
      if ( *(_DWORD *)v73 != 6421 )
        goto LABEL_140;
      (((CCBFiveNimbusWindow *)&this[1].m_ArrowNum[6][0][3].pDebugTex))->CCBFiveNimbusWindow::SetFloatParam(160.0);
      (((Camera *)p_pDebugTex))->Camera::UpdateCameraLookAt(128, 276, 600);
LABEL_141:
      v52 = (const char *)(v73 + 36);
      if ( !strcmp((const char *)(v73 + 36), unk_C10D38) )
        sprintf(&this->buf[28], "%s", "NONE");
      else
        sprintf(&this->buf[28], "Item\\%s\\%s.pol", (const char *)(v73 + 36), (const char *)(v73 + 36));
      (((PalScript *)&this[1].m_ArrowNum[6][0][3].m_mouseoff))->PalScript::LoadModel(&this->buf[28], 0);
      if ( !strcmp((const char *)(v73 + 36), unk_C10D38) )
      {
        sprintf(&this->buf[28], "%s", "NONE");
      }
      else
      {
        memset(Buffer, 0, sizeof(Buffer));
        v79 = 0;
        v80 = 0;
        sprintf(Buffer, "%s%s", v52, (const char *)(v73 + 66));
        sprintf(&this->buf[28], "Item\\%s\\%s.tga", v52, Buffer);
      }
      (((gbGeomNode *)this[1].m_ArrowNum[6][0][4].m_fontcolor.Color))->gbGeomNode::ReplaceTexture(&this->buf[28]);
      this[1].m_ArrowNum[6][0][3].m_FVF = 1;
      return;
    case 1008:
      if ( *((int *)&this->m_EquipData + 67) >= 0 )
      {
        switch ( *((_DWORD *)&this->m_EquipData + 65) )
        {
          case 0:
            p_m_fonttype = (UIListBox *)&this[1].m_ArrowNum[0][1][1].m_fonttype;
            goto LABEL_159;
          case 1:
            p_m_fonttype = (UIListBox *)&this[1].m_ArrowNum[1][0][4].m_textx;
            goto LABEL_159;
          case 2:
            p_m_fonttype = (UIListBox *)&this[1].m_ArrowNum[2][0][2].m_ratiow;
            goto LABEL_159;
          case 3:
            p_m_fonttype = (UIListBox *)&this[1].m_ArrowNum[3][0][0].pDebugTex;
            goto LABEL_159;
          case 4:
            p_m_fonttype = (UIListBox *)&this[1].m_ArrowNum[3][1][3].m_benable;
LABEL_159:
            if ( *((_DWORD *)&this->m_EquipData + 67) >= (((UIListBox *)p_m_fonttype))->UIListBox::GetItemData() )
              return;
            goto LABEL_162;
          case 5:
            p_m_fonttype = (UIListBox *)&this[1].m_ArrowNum[4][1][1].m_bcreateok;
            if ( *((_DWORD *)&this->m_EquipData + 67) >= (((UIListBox *)&this[1].m_ArrowNum[4][1][1].m_bcreateok))->UIListBox::GetItemData() )
              return;
LABEL_162:
            *((_DWORD *)&this->m_EquipData + 67) = (((UIListBox *)p_m_fonttype))->UIListBox::CreateChild();
LABEL_163:
            if ( (((PAL_GDB *)this))->PAL_GDB::LoadByType(*((_DWORD *)&this->m_EquipData + 67), 1) )
            {
              if ( *((_DWORD *)&this->m_EquipData + 65) == 1 )
              {
                v55 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v76, *((_DWORD *)&this->m_EquipData + 67));
                v56 = 0;
                nItemID = (unsigned long)*v55;
                v57 = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
                v72 = (unsigned long)v55[1];
                v73 = (unsigned long)v55[2];
                while ( 1 )
                {
                  if ( *((_BYTE *)&this->m_EquipData + v56 + 245) )
                  {
                    if ( (((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)&nItemID, v56) )
                    {
                      (**((void ( ***)(int *, int))&this[1].m_Arrow[2][5][1].m_bvisible + 1223 * v56))((int *)(&this[1].m_Arrow[2][5][1].m_bvisible + 1223 * v56), (int)(1));
LABEL_173:
                      this->EquipUI::SetGroupVisible(0);
                      *((_BYTE *)&this->m_EquipData + 277) = 1;
                      *((_BYTE *)&this->m_EquipData + 276) = 1;
                      v59 = (const void *)off_5CADC8;
                      goto LABEL_176;
                    }
                    (**(void ( ***)(char *, _DWORD))v57)((char *)(v57), (_DWORD)(0));
                  }
                  ++v56;
                  v57 += 4892;
                  if ( v56 >= 5 )
                    goto LABEL_173;
                }
              }
              (((PAL_GDB *)this))->PAL_GDB::SelectBestTarget(*((_DWORD *)&this->m_EquipData + 67));
              goto LABEL_173;
            }
            *((_BYTE *)&this->m_EquipData + 277) = 0;
            v31 = (unsigned long)off_5CADD0;
LABEL_175:
            v59 = (const void *)v31;
LABEL_176:
            v58 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v58))->CScreenMode::AudioSetPosition(v59, 1);
            break;
          default:
            goto LABEL_163;
        }
      }
      else
      {
        v68 = (const void *)off_5CADD0;
        v53 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v53))->CScreenMode::AudioSetPosition(v68, 1);
LABEL_135:
        this->UIWnd::OnMessage(nVal, (int)pszBuf, nVal2);
      }
      return;
    case 1009:
      return;
    case 1010:
      *((_BYTE *)&this->m_EquipData + 276) = 0;
      *((_BYTE *)&this->m_EquipData + 278) = 0;
      *((_BYTE *)&this->m_EquipData + 277) = 0;
      this->EquipUI::SetGroupVisible(1u);
      v44 = (char *)&this[1].m_Arrow[2][5][1].m_bvisible;
      v45 = 5;
      do
      {
        (**(void ( ***)(char *, _DWORD))v44)((char *)(v44), (_DWORD)(0));
        v44 += 4892;
        --v45;
      }
      while ( v45 );
      return;
    case 1020:
      *(_DWORD *)&this->buf[16] = 0;
      while ( 1 )
      {
        v32 = *(_DWORD *)&this->buf[16];
        if ( *((_BYTE *)&this->m_EquipData + v32 + 245) )
        {
          if ( pszBuf == (char *)*(&dword_56E148 + v32) )
            break;
        }
        v33 = v32 + 1;
        *(_DWORD *)&this->buf[16] = v33;
        if ( v33 >= 5 )
          return;
      }
      v34 = *((_DWORD *)&this->m_EquipData + 67);
      *((_DWORD *)&this->m_EquipData + 63) = *(_DWORD *)&this->buf[16];
      if ( v34 < 0 || !(((PAL_GDB *)this))->PAL_GDB::LoadByType(v34, 1) )
        goto LABEL_78;
      (((int *)this))->Array::HandleItemPage(*(_DWORD *)&this->buf[16], *(_DWORD *)&this->buf[16]);
      (((StateUI *)this))->StateUI::UpdateScrollValues() /* [ROWTABLE] */;
      if ( !*((_BYTE *)&this->m_EquipData + 276) )
      {
        this->EquipUI::SetGroupVisible(1u);
LABEL_78:
        if ( !*((_BYTE *)&this->m_EquipData + 276) )
          (((StateUI *)this))->StateUI::DisplayCaption(*((_DWORD *)&this->m_EquipData + 63)) /* [ROWTABLE] */;
      }
      *((_BYTE *)&this->m_EquipData + 244) = 1;
      return;
    default:
      goto LABEL_135;
  }
}

// 0x004A4220
void EquipUI::Init()
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  CHAR *v8; // ebp
  UIPushButton *p_m_childs; // edi
  int v10; // edx
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  LineupUI *v15; // eax
  char *v16; // eax
  RenderTarget *v17; // eax
  int inited; // eax
  int v19; // eax
  EquipUI *v20; // eax
  int v21; // eax
  CCCTData *v22; // eax
  int v23; // eax
  LineupUI *v24; // eax
  int v25; // eax
  int v26; // eax
  char *m_pData; // ecx
  int v28; // [esp+0x3C] [ebp-0x64]
  void *v29; // [esp+0x4C] [ebp-0x54]
  void *v30; // [esp+0x4C] [ebp-0x54]
  int v31; // [esp+0x54] [ebp-0x4C] BYREF
  int v32; // [esp+0x58] [ebp-0x48]
  int v33; // [esp+0x5C] [ebp-0x44]
  int v34; // [esp+0x60] [ebp-0x40]
  int v35; // [esp+0x64] [ebp-0x3C]
  int v36; // [esp+0x68] [ebp-0x38]
  int v37; // [esp+0x6C] [ebp-0x34]
  int v38; // [esp+0x70] [ebp-0x30]
  int v39; // [esp+0x74] [ebp-0x2C] BYREF
  int v40; // [esp+0x78] [ebp-0x28]
  int v41; // [esp+0x7C] [ebp-0x24]
  int v42; // [esp+0x80] [ebp-0x20]
  _DWORD v43[4]; // [esp+0x84] [ebp-0x1C] BYREF
  int v44; // [esp+0x9C] [ebp-0x4]

  v2 = *(_DWORD *)&this->buf[8];
  v3 = *(_DWORD *)&this->buf[12];
  *(_DWORD *)this->buf = v2;
  this->bkWndY = 0;
  this->bkWndX = 0;
  *(_DWORD *)&this->buf[4] = v3;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, this->bkWndX, this->bkWndY, *(_DWORD *)this->buf, *(_DWORD *)&this->buf[4]) /* [ROWTABLE] */;
  v4 = this->bkWndY + 18;
  v39 = this->bkWndX + 592;
  v40 = v4;
  v41 = v39 + 192;
  v42 = v4 + 526;
  (*(void ( **)(st_Manager *, int, int *, EquipUI *))(*(_DWORD *)&this->m_EquipData.m_Type + 16))(
    &this->m_EquipData,
    161,
    &v39,
    this);
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)&this->m_EquipData))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\State\\Frame.tga", v5);
  v6 = *(_DWORD *)(&this->m_EquipData.m_Dicker + 151);
  v40 += 26;
  v39 = v41;
  v42 = v40 + 526;
  v41 += 17;
  (*(void ( **)(_BYTE *, int, int *, EquipUI *))(v6 + 16))(
    &this->m_EquipData.m_Dicker + 151,
    161,
    &v39,
    this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)(&this->m_EquipData.m_Dicker + 151)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Frame_Line.tga", v7);
  v43[1] = 14;
  v43[0] = 626;
  v43[2] = 674;
  v43[3] = 68;
  v8 = (CHAR *)"UI\\GameMainUI\\State\\State0.tga";
  p_m_childs = (UIPushButton *)&this[1].m_Arrow[5][4][3].m_childs;
  do
  {
    (*(void ( **)(UIPushButton *, int, _DWORD *, EquipUI *))(*(_DWORD *)((UIWnd *)p_m_childs) + 16))(
      p_m_childs,
      161,
      (_DWORD *)(v43),
      this);
    LOBYTE(v10) = g_bDebugMode;
    (((UIPushButton *)p_m_childs))->UIPushButton::CreateFromTemplate(v8, v10);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)p_m_childs))((UIPushButton *)(p_m_childs), (_DWORD)(0));
    v8 += 256;
    p_m_childs = (UIPushButton *)((char *)p_m_childs + 152);
  }
  while ( (int)v8 < (int)"UI\\GameMainUI\\State\\Portrait0.tga" );
  v11 = *((_DWORD *)&this->m_EquipData + 76);
  v31 = v41 - 205;
  v33 = v41 - 205 + 203;
  v32 = 0;
  v34 = 64;
  (*(void ( **)(char *, int, int *, EquipUI *))(v11 + 16))((char *)&this->m_EquipData + 304, 161, &v31, this);
  LOBYTE(v12) = g_bDebugMode;
  (((UIPushButton *)((char *)&this->m_EquipData + 304)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\TimeMoney.tga", v12);
  v13 = *((_DWORD *)&this->m_EquipData + 1082);
  v32 = -4;
  v31 = 618;
  v33 = 738;
  v34 = 28;
  (*(void ( **)(char *, int, int *, EquipUI *))(v13 + 16))((char *)&this->m_EquipData + 4328, 161, &v31, this);
  (((UIScene *)((char *)&this->m_EquipData + 4328)))->UIScene::SetShow(0);
  AllocObject((char *)&this->m_EquipData + 4328);
  v14 = *((_DWORD *)&this->m_EquipData + 1044);
  v32 = 16;
  v31 = 668;
  v33 = 748;
  v34 = 48;
  (*(void ( **)(char *, int, int *, EquipUI *))(v14 + 16))((char *)&this->m_EquipData + 4176, 161, &v31, this);
  (((UIScene *)((char *)&this->m_EquipData + 4176)))->UIScene::SetShow(0);
  AllocObject((char *)&this->m_EquipData + 4176);
  (((LineupUI *)this))->LineupUI::RebuildFontPage() /* [ROWTABLE] */;
  v36 = 0;
  v35 = 0;
  v37 = 0;
  v38 = 32;
  (((StateUI *)this))->StateUI::GetChildPtr(0) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::GetChildPtr(1) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::GetChildPtr(2) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::GetChildPtr(3) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::GetChildPtr(4) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::FindChild(0) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::FindChild(1) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::FindChild(2) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::FindChild(3) /* [ROWTABLE] */;
  (((StateUI *)this))->StateUI::FindChild(4) /* [ROWTABLE] */;
  BYTE1(this[1].m_Arrow[6][1][1].pDebugTex) = 0;
  LOBYTE(this[1].m_Arrow[6][1][1].pDebugTex) = g_bRoleSystem_5CEFA9;
  v15 = (LineupUI *)operator new(0x29CECu);
  v44 = 0;
  if ( v15 )
    v16 = (char *)(((LineupUI *)v15))->LineupUI::Save();
  else
    v16 = 0;
  v44 = -1;
  this[1].m_Arrow[6][1][1].m_childs.m_pData = v16;
  v17 = (RenderTarget *)operator new(0x56630u);
  v44 = 1;
  if ( v17 )
    inited = (((RenderTarget *)v17))->RenderTarget::InitChildPanels();
  else
    inited = 0;
  v44 = -1;
  this[1].m_Arrow[6][1][1].m_childs.capacity = inited;
  v29 = (void *)operator new(0x35B50u);
  v44 = 2;
  if ( v29 )
    v19 = MainPropUI__MainPropUI(v28);
  else
    v19 = 0;
  v44 = -1;
  this[1].m_Arrow[6][1][1].m_childs.m_nSize = v19;
  v20 = (EquipUI *)operator new(0x41014u);
  v44 = 3;
  if ( v20 )
    v20->EquipUI::EquipUI();
  else
    v21 = 0;
  v44 = -1;
  this[1].m_Arrow[6][1][1].m_childs.m_needscriptdel = v21;
  v22 = (CCCTData *)operator new(0x62588u);
  v44 = 4;
  if ( v22 )
    v22->CCCTData::CCCTData();
  else
    v23 = 0;
  v44 = -1;
  this[1].m_Arrow[6][1][1].m_bcreateok = v23;
  v24 = (LineupUI *)operator new(0x27BD4u);
  v44 = 5;
  if ( v24 )
    v24->LineupUI::LineupUI();
  else
    v25 = 0;
  v44 = -1;
  this[1].m_Arrow[6][1][1].m_bvisible = v25;
  v30 = (void *)operator new(0x46EB8u);
  v44 = 6;
  if ( v30 )
    v26 = UITitle_JDHY_DestroyPages(v28);
  else
    v26 = 0;
  m_pData = this[1].m_Arrow[6][1][1].m_childs.m_pData;
  v44 = -1;
  this[1].m_Arrow[6][1][1].m_benable = v26;
  (((LineupUI *)m_pData))->LineupUI::CreatePreviewScene((int)this);
  CameraCtrl_CreateCameraUI((int)this);
  CreateSceneEntities((Actor *)this[1].m_Arrow[6][1][1].m_childs.m_nSize, (int)this);
  (((MainEquipUI *)this[1].m_Arrow[6][1][1].m_childs.m_needscriptdel))->MainEquipUI::CreateListPanel((int)this);
  EquipUI_InitEquipUI((int)this);
  sub_47F590(this[1].m_Arrow[6][1][1].m_bvisible, (int)this);
  UITitle_JDHY_PopulateContent((int)this);
  g_bRoleFlag1 = 0;
  g_bRoleFlag2 = 0;
  BYTE1(this->_flashSpeed) = 1;
}
