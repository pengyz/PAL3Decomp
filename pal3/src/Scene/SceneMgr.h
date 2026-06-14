#pragma once
// Auto-generated: SceneMgr

#include "PlayerAtts.h"
#include "RoleSystem.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbAudio.h"

class CCBStageRole;
class CEffMgr;
class CGameData;
class CameraCtrl;
class PalScript;
class PalScriptMgr;
class Role;

class SceneMgr {
public:
    gbGfxManager * m_pGfxMgr; // +0x0
    gbSceneGraph * m_pSceneRoot; // +0x4
    gbRenderEffect * m_pAddEffect2; // +0x8
    gbRenderEffect * m_pAlphaEffect2; // +0xC
    gbRenderEffect * m_pAddEffect; // +0x10
    gbRenderEffect * m_pAlphaEffect; // +0x14
    gbCamera * m_pCamera; // +0x18
    float m_aSceneSlots; // +0x1C
    float _todo_020[12]; // +0x20
    PlayerAtts m_PlayerAtts; // +0x50
    char _gap_054[204]; // +0x54
    int m_aRoleSlotStat[11]; // +0x120
    int m_nSlotCount[1]; // +0x14C
    int m_nSlotMemberCount[1]; // +0x150
    int m_aEquipGDB_ArmorData[1]; // +0x154
    int m_aEquipWField_01[1]; // +0x158
    int m_aEquipGDB_ArmorFlag[1]; // +0x15C
    int m_aEquipGDB_WeaponData[1]; // +0x160
    int m_aEquipWField_04[1]; // +0x164
    int m_aEquipGDB_ItemData[1]; // +0x168
    int m_aEquipGDB_WeaponFlag[1]; // +0x16C
    int m_aEquipWField_07[1]; // +0x170
    int m_aEquipGDB_ItemFlag[1]; // +0x174
    int m_aEquipGDB_Acc1Data[1]; // +0x178
    int m_aEquipWField_0A[1]; // +0x17C
    int m_aEquipGDB_Acc2Data[1]; // +0x180
    int m_aEquipGDB_Acc1Flag[1]; // +0x184
    int m_aEquipWField_0D[1]; // +0x188
    int m_aEquipGDB_Acc2Flag[1]; // +0x18C
    int m_aSkillGDB_0F[1]; // +0x190
    int m_apSkillData[1]; // +0x194
    int m_aScriptDelay[1]; // +0x198
    int m_aViewModeParamA[1]; // +0x19C
    int m_aViewModeParamB[1]; // +0x1A0
    int m_aEquipVal_0[1]; // +0x1A4
    int m_aEquipVal_1[1]; // +0x1A8
    int m_aEquipVal_2[1]; // +0x1AC
    int m_aEquipVal_3[1]; // +0x1B0
    int m_aEquipVal_4[1]; // +0x1B4
    int m_aEquipVal_5[1]; // +0x1B8
    int m_aEquipVal_6[1]; // +0x1BC
    int m_aEquipVal_7[1]; // +0x1C0
    int m_aEquipVal_8[1]; // +0x1C4
    int m_aScriptTransition[1]; // +0x1C8
    int m_aScreenModeParam[1]; // +0x1CC
    int m_aScreenModeParam2[1]; // +0x1D0
    int _todo_3F0[1]; // +0x1D4
    int _todo_3F4[1]; // +0x1D8
    int m_aStatMaxVal_Exp[1]; // +0x1DC
    int m_aStatMaxVal_NextLv[1]; // +0x1E0
    int m_aStatMaxVal_WuLing0[1]; // +0x1E4
    int m_aStatMaxVal_WuLing1[1]; // +0x1E8
    int m_aStatMaxVal_WuLing2[1]; // +0x1EC
    int m_nGDBItemCount[1]; // +0x1F0
    int m_nUIDisplayCount[1]; // +0x1F4
    int m_nGDBRoleCount[1]; // +0x1F8
    int m_aNPCData[1]; // +0x1FC
    int m_aNPCFieldData[1]; // +0x200
    int m_aNPCPropByType[1]; // +0x204
    int m_aNPCPropByType2[1]; // +0x208
    int m_aNPCPropBySlot[1]; // +0x20C
    int m_RenderBuffer[12]; // +0x210
    RoleSystem stru_C059A0; // +0x240
    char _gap_244[4432]; // +0x244
    CCBStageRole * m_pCCBStageRoleFind; // +0x1394
    _BYTE m_bRoleSlotValid[8]; // +0x1398
    int m_nUnk61D8; // +0x13A0
    UINT m_nScriptObjectCount; // +0x13A4
    CGameData * m_pGameData; // +0x13A8
    int _unkC5D4; // +0x13AC
    CameraCtrl * m_pCameraCtrl; // +0x13B0
    PalScriptMgr * m_pScriptCtrl; // +0x13B4
    RoleSystem * m_pRoleSystemArrayEnd; // +0x13B8
    int m_partyInitData[100]; // +0x13BC
    PalScript * m_pCurrentScript; // +0x154C
    BYTE m_bFormationReady; // +0x1550
    BYTE m_nSceneTransitionParam2; // +0x1551
    char _gap_1552[2]; // +0x1552
    int m_nCurrentRoleSlot; // +0x1554
    float m_fFadeTimer; // +0x1558
    float m_fMoveParam; // +0x155C
    float _field_CCB4; // +0x1560
    float _field_CCB8; // +0x1564
    int _field_CCE8; // +0x1568
    int _field_CCEC; // +0x156C
    float m_fTileSize; // +0x1570
    float m_fCamFOV; // +0x1574
    int _field_CF78; // +0x1578
    int _field_CF7C; // +0x157C
    float m_vCameraTarget[3]; // +0x1580
    float m_vCameraPos[3]; // +0x158C
    float m_vCamLookAt[3]; // +0x1598
    float m_CamMatrix[4]; // +0x15A4
    float m_fCamDist; // +0x15B4
    int _field_D04C; // +0x15B8
    int _field_D054; // +0x15BC
    int m_nCollisionFlags; // +0x15C0
    int m_ScriptResult; // +0x15C4
    RoleSystem * m_pControlledRole; // +0x15C8
    int m_bCameraActive; // +0x15CC
    float _field_D2DC; // +0x15D0
    float _field_D2E0; // +0x15D4
    BYTE m_bPathEnabled; // +0x15D8
    char _gap_15D9[3]; // +0x15D9
    RoleSystem * m_pRoleSystem; // +0x15DC
    int m_nCameraFlags; // +0x15E0
    float m_fTileSizeSub; // +0x15E4
    BYTE m_bPathBlockEnabled; // +0x15E8
    char _gap_15E9[3]; // +0x15E9
    RoleSystem * m_pRoleSystemPtr; // +0x15EC
    gbSound2DNode * m_pCurrentBGM; // +0x15F0
    float m_fCameraBlendWeight; // +0x15F4
    int m_nPartyRoles[6]; // +0x15F8
    int m_nPartyCount; // +0x1610
    int m_nMonsterType; // +0x1614
    Role * m_pCombatRole; // +0x1618
    int m_nRoleCount; // +0x161C
    // total size: 0x1620 (5664)

    virtual ~SceneMgr() {}

    static int ResetPlayerAtts(); // 0x00408850
    static int InitSceneRoles(); // 0x0040CA40
    static int GetValidPartyCount(); // 0x0040FC70
    int RenderActiveRoles(); // 0x00421C00
    int * FindRoleByState(char nState); // 0x00422050
    static int ClearInactiveRoles(); // 0x00423500
    static int ResetSceneFlags(); // 0x004236B0
    void FormatStatusCaption(int a2); // 0x00493E40
    CEffMgr * Create(int gfxMgr, int cam, int nVal); // 0x004CDA10
    char RenderAll(); // 0x004CDBF0
    char RenderUpdate(); // 0x004CDC20
    SceneMgr * LoadMainUITexture(); // 0x00528D50
    int * GetCurrentNode(); // 0x0052EC90
};
