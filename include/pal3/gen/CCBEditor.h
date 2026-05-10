#pragma once
// Auto-generated: CCBEditor

#include "ECBEditorMode.h"
#include "tagNewItem.h"

class CCBRoleState;
class CCBSystem;
class HWND__;

class CCBEditor {
public:
    BYTE m_bAIHandRequre; // +0x0
    BYTE m_bLockCam; // +0x0
    CCBSystem * m_pCBSystem; // +0x0
    CCBRoleState * m_pRoleState; // +0x4
    ECBEditorMode m_eMode; // +0x0
    HWND__ * m_hWndFightSkillCfg; // +0x0
    HWND__ * m_hWndSpecState; // +0x0
    HWND__ * m_hWndNewItem; // +0x0
    HWND__ * m_hWndSelectFighter; // +0x0
    HWND__ * m_hWndEffObjType; // +0x0
    float m_fTimeScale; // +0x0
    char m_sTimeScale[20]; // +0x0
    char m_sTempText[256]; // +0x0
    BYTE m_bAuto; // +0x0
    BYTE m_bRestart; // +0x0
    BYTE m_bShowDebugInfo; // +0x0
    int m_nSystemThread; // +0x0
    int m_nStageTask; // +0x0
    BYTE m_bSaveInitPos; // +0x0
    BYTE m_bEditFiveLineup; // +0x0
    BYTE m_bLoadInitPos; // +0x0
    BYTE m_bSaveCamPos; // +0x0
    int m_nCurRoleData; // +0x0
    BYTE m_bChangeCurRoleData; // +0x0
    BYTE m_bRoleDataActive; // +0x0
    BYTE m_bRoleLevelActive; // +0x0
    BYTE m_bInitFightSkillCfg; // +0x0
    BYTE m_bSaveFightSkillCfg; // +0x0
    int m_nCurFightSkillCfgRole; // +0x0
    int m_nCurFightSkillCfgTab; // +0x0
    int m_nOldFightSkillCfgRole; // +0x0
    int m_nOldFightSkillCfgTab; // +0x0
    BYTE m_bInitSpecStateCfg; // +0x0
    BYTE m_bSaveSpecStateCfg; // +0x0
    BYTE m_bInitNewItemCfg; // +0x0
    BYTE m_bSaveNewItemCfg; // +0x0
    int m_nCurItem; // +0x0
    BYTE m_bSetCurSelectItem; // +0x0
    BYTE m_bChangeItemValue; // +0x0
    int m_nCurAddItem; // +0x0
    BYTE m_bAddItem; // +0x0
    BYTE m_bDefaultItem; // +0x0
    BYTE m_bRemoveItem; // +0x0
    BYTE m_bInitSelectFighterBox; // +0x0
    BYTE m_bRefreshSelectFighterBox; // +0x0
    BYTE m_bInitCamList; // +0x0
    CCBEditor * m_fpThis; // +0x0
    tagNewItem m_NewItem[500]; // +0x8
    int m_dwSelectFighter[11]; // +0x1F48
    int m_nCurCCTList; // +0x1F74
    int m_nCurCCT; // +0x1F78
    int m_nCurEffClass; // +0x1F7C
    int m_nCurEffObjType; // +0x1F80
    int m_nCurEffGroup; // +0x1F84
    int m_nCurEffObjInGroup; // +0x1F88
    int m_nCurEffObjTask; // +0x1F8C
    DWORD m_dwTrickID[384]; // +0x1F90
    int m_nCurSelectedEffGroup; // +0x2590
    int m_nCurSelectedTrick; // +0x2594
    // total size: 0x2598 (9624)

};
