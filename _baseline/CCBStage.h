#pragma once
// Auto-generated: CCBStage

#include "gbengine/gbengine_types.h"

#include "ECBStageTaskState.h"
class Actor;
class CCBCamControl;
class CCBDisplayChain;
class CCBEditor;
class CCBProtectWindow;
class CCBRoleState;
class CCBStageCam;
class CCBStageEffect;
class CCBStageRole;
class CCBStageScene;
class CCBStageShadow;
class CCBSystem;
class CCBUI;
class PalScriptIdleObj;
class PtrArray;
class ScriptSystem;
class UIWnd;
class gbGfxManager;
class gbVFileSystem;
class tagStageTask;

class CCBStage {
public:
    CCBSystem * m_pCBSystem; // +0x0
    CCBRoleState * m_pRoleState; // +0x4
    CCBEditor * m_pEditor; // +0x8
    CCBStageCam * m_pCam; // +0xC
    CCBCamControl * m_pCamControl; // +0x10
    CCBStageScene * m_pScene; // +0x14
    CCBStageRole * m_pRole[11]; // +0x18
    Actor * m_TempStorageNGH; // +0x44
    Actor * m_NGHVariance; // +0x48
    Actor * m_TempStorageWPX; // +0x4C
    Actor * m_WPXVariance; // +0x50
    CCBDisplayChain * m_pDisplayChain; // +0x54
    CCBStageShadow * m_pShadow; // +0x58
    CCBStageEffect * m_pEffect; // +0x5C
    float m_BFARole; // +0x60
    float m_BFARound; // +0x64
    tagPOINT m_ptMousePos; // +0x68
    int m_nSelectedRole; // +0x70
    unsigned char m_bRoleSelected[11]; // +0x74
    unsigned char m_bHideSceneAndRole; // +0x7F
    float m_fDamageNumPosY[5]; // +0x80
    int _todo_094; // +0x94
    unsigned char m_nStageStatus; // +0x98
    unsigned char m_bFlag99; // +0x99
    unsigned char m_bFlag9A; // +0x9A
    unsigned char m_bFlag9B; // +0x9B
    int m_nTaskCount; // +0x9C
    int m_nClearRoleAllTask; // +0xA0
    int m_nRoleSlot; // +0xA4
    unsigned char m_nForceDelTask; // +0xA8
    float m_fMusicVolume; // +0xAC
    unsigned char m_bPaused; // +0xB0
    int m_nTask; // +0xB4
    int m_nCurTask; // +0xB8
    int m_nCurSubTask; // +0xBC
    tagStageTask * m_Task; // +0xC0
    int m_RoleSlots; // +0xC4
    unsigned char m_bAllDone; // +0x111
    unsigned char m_nActiveRoleIndex; // +0x118
    int m_nActiveIdx; // +0x11C
    int m_CamAngles; // +0x120
    int _todo_124; // +0x124
    gbColorQuad m_CamParams; // +0x128
    int m_nActionIdx; // +0x18C
    int m_TargetPos; // +0x190
    float _todo_1C0; // +0x1C0
    float m_fRotPitch; // +0x1C4
    float m_fRotYaw; // +0x1C8
    float m_fTimeAccum; // +0x1D0
    float m_fTimerRaw; // +0x1D4
    float _todo_1E0; // +0x1E0
    float _todo_1E4; // +0x1E4
    float m_fAllDone; // +0x1E8
    float m_ActionAngles; // +0x1EC
    float _todo_1F0; // +0x1F0
    float _todo_1F4; // +0x1F4
    float m_ActionCmds; // +0x1F8
    float _todo_1FC; // +0x1FC
    float _todo_200; // +0x200
    int _todo_204; // +0x204
    int _todo_208; // +0x208
    int _todo_20C; // +0x20C
    void * m_pController; // +0x220
    float m_fTurnProgress; // +0x224
    float m_fPrevRotX; // +0x228
    float m_fPrevRotY; // +0x22C
    int m_nTurnCount; // +0x230
    int m_nCmdCount; // +0x234
    int m_nTurnPhase; // +0x238
    int m_nLastAction; // +0x23C
    int m_nTurnIndex; // +0x240
    int m_nResetState; // +0x244
    int m_CmdQueue; // +0x248
    short m_TurnFlags; // +0x25E
    int m_TurnData; // +0x270
    int _todo_570; // +0x570
    int _todo_574; // +0x574
    int m_RoleData; // +0x578
    int m_TaskQueue; // +0xAC0
    int m_TaskState; // +0xAC4
    int m_nTaskExist; // +0xAC8
    int m_DamageData; // +0xACC
    unsigned char m_nTaskState; // +0xAEC
    int _todo_1198; // +0x1198
    int _todo_119C; // +0x119C
    int m_TurnBuffer; // +0x11E8
    int m_nAllDone; // +0x19A8
    float m_fCurPosX; // +0x19B8
    float m_fCurPosY; // +0x19BC
    float m_fCurPosZ; // +0x19C0
    float m_fTargetPosX; // +0x19D0
    float m_fTargetPosY; // +0x19D4
    float m_fTargetPosZ; // +0x19D8
    float m_fVelX; // +0x19DC
    float m_fVelY; // +0x19E0
    float m_fVelZ; // +0x19E4
    float m_fAngleDegrees; // +0x19E8
    float _todo_19EC; // +0x19EC
    int m_nBattleResult; // +0x19F4
    int _todo_19F8; // +0x19F8
    int _todo_19FC; // +0x19FC
    int _todo_1A08; // +0x1A08
    int _todo_1A0C; // +0x1A0C
    float m_fTurnTimer; // +0x1F74
    int m_nTurnSlot0; // +0x1F78
    int m_nTurnSlot1; // +0x1F7C
    int m_nTurnSlot2; // +0x1F80
    int m_nTurnSlot3; // +0x1F84
    int m_nTurnSlot4; // +0x1F88
    int m_nTurnSlot5; // +0x1F8C
    int m_nResultSlot0; // +0x2590
    int m_nResultSlot1; // +0x2594
    int _todo_639C0; // +0x639C0
    int _todo_64190; // +0x64190
    int _todo_A48A8; // +0xA48A8
    UINT m_dwAniFlagOver; // +0xA48C0
    // total size: 0xA48C8 (673992)

    void * ReleasePtrArray(); // 0x004019B0
    int CalcScrollPos(); // 0x00442000
    int CalcSplitRect(); // 0x00442100
    gbVFileSystem * LoadScriptTexture(int nTexID, int nParam); // 0x0044A970
    char ProcessScriptEvent(int nVal, int nVal2, int nParam); // 0x004890A0
    int GetReadyCount(); // 0x004C5C20
    int GetActiveTaskCount(); // 0x004D1EF0
    int GetTaskParam(int nVal, int nVal2); // 0x004D4D30
    char SetTaskState(int nVal); // 0x004D4D70
    int * InitStage(int nVal); // 0x004DF6B0
    char IsInitialized(); // 0x004DF700
    void ResetRoundState(); // 0x004DF710
    int CountActiveActions(); // 0x004DFA10
    int InitRound(); // 0x004DFAA0
    int UpdateTurnFlags(const char *pszName, float fVal, float fVal2, float fVal3); // 0x004DFB70
    int InitSlotFlags(const char *pszName, int nVal, int nVal2, int nVal3); // 0x004DFC40
    int AddTextLabel(int nVal, int nVal2); // 0x004DFE00
    int EndTurnAndAdvance(); // 0x004DFED0
    int AssignSlotData(char pData); // 0x004DFF90
    __int64 CalculateTurnOrder(float fVal, int nVal); // 0x004DFFF0
    void SetupCamControl(CCBStage *thisa); // 0x004E0010
    int * ResetAndSetSystem(int nVal); // 0x004E02F0
    int Reset(); // 0x004E0330
    int ResetTurnSlots(); // 0x004E0340
    char SyncTimeScale(); // 0x004E0380
    char DestroyDialog(); // 0x004E03F0
    char CreatePreviewDialog(); // 0x004E0430
    bool ProcessAction(HWND pData); // 0x004E0530
    static void CreatePreview(float fVal); // 0x004E05B0
    BOOL DestroyPreviewWindow(); // 0x004E0650
    char ResetAllSlots(); // 0x004E0690
    bool FindThreadByParam(int nVal, UINT dwVal); // 0x004F06C0
    CCBStageRole * GetRole(int index); // 0x004F4AA0
    char CheckGDBTypeCompat(UINT *pdwVal); // 0x004F6CD0
    CCBStage(int pCBSystem); // 0x004FB9A0
    UINT _CCBStage(); // 0x004FB9F0
    char Create(); // 0x004FBE50
    char Destroy(); // 0x004FBF90
    int Update(); // 0x004FC0A0
    int Update_c150(); // 0x004FC150
    void EditorUpdate(float fVal); // 0x004FC3A0
    void Render(); // 0x004FC6F0
    int GetRoleIndex(int nameCrc, const void *pData, char a4); // 0x004FC700
    int GetRoleName(int nameCrc, int nVal, int nVal2, int nVal3, int nVal4, int *p_DWORD, int nVal5, int nVal6); // 0x004FC7D0
    char Procced(int nVal); // 0x004FC8B0
    char GetStageRole(int idx); // 0x004FC8F0
    char GetStageRoleByIdx(int idx); // 0x004FC940
    int IsDoTask(int eTask); // 0x004FC980
    int EndTask(int nIndex); // 0x004FC9A0
    char * DelTask(int nIndex, _BYTE *p_BYTE, int *p_DWORD); // 0x004FC9C0
    char ForceDelTask(int nIndex); // 0x004FCA00
    void GetTask(); // 0x004FCA80
    char GetTaskID(int nIndex, int nVal); // 0x004FCBD0
    char GetTaskState(int nIndex, bool *bFinished, UINT *dwReturn); // 0x004FCC10
    char GetTaskState(int nIndex, enum ECBStageTaskState *State); // 0x004FCC50
    int IsTaskFinished(int nIndex); // 0x004FCD00
    static _BYTE * IsTaskValidButNotFinish(_BYTE *result, int eTask, int nVal); // 0x004FCD50
    int IsTaskExist(UINT dwTaskID); // 0x004FCDA0
    int DoTask(int nVal); // 0x004FCDE0
    int StartSubTask(int n); // 0x004FCE00
    int IsSubTaskFinished(int n, int nSub); // 0x004FCE70
    int IsAllSubTaskFinished(int n); // 0x004FCFB0
    int IsTaskValid(int n); // 0x004FD0B0
    int IsSubTaskValid(int n, int nSub); // 0x004FD1A0
    int IsIdle(int nVal); // 0x004FD290
    int HasNormalAttackRole(int nRoleIndex); // 0x004FD3D0
    int ClearRoleAllTask(int nRoleIndex); // 0x004FD880
    int EndRoleAllTask(int nRoleIndex); // 0x004FDA10
    int GetRoleTaskNum(int nRoleIndex); // 0x004FDB10
    int SelectRole(int nRoleIndex); // 0x004FDD90
    int ProcWait(int formal); // 0x004FDFC0
    int ProcShowFiveLineup(int formal); // 0x004FE290
    int ProcShowEnemyFiveLineup(); // 0x004FE540
    int ProcFiveLienupFadeIn(int formal); // 0x004FE550
    int ProcFiveLienupFadeOut(int formal); // 0x004FE600
    int ProcShowSneakAttackState(UINT  a_74); // 0x004FE660
    int HandleKeyCtrl(int n); // 0x004FECE0
    int HandleKeyFriend(int Selected); // 0x004FEE60
    int ProcShowName(UINT formal); // 0x004FEFB0
    int ProcShowItemName(int formal); // 0x004FF1B0
    int ProcShowDamage(UINT formal); // 0x004FF3D0
    int ProcTaskSlot(int nVal); // 0x004FF560
    int ProcShowCost(int formal); // 0x004FF5C0
    int ProcShowCombatDialog(int formal); // 0x004FF740
    int ProcGrabStageRole(UINT formal); // 0x004FF840
    int ExecuteRoleTask(int nVal); // 0x00500840
    int Method_5009C0(int nVal); // 0x005009C0
    int Method_500AD0(int nVal); // 0x00500AD0
    int ProcessRoleEffect(int nVal); // 0x005024D0
    int ResetAll(); // 0x00503020
    int CalcSneakAttackVariance(); // 0x00503680
    int UpdatePhysics(); // 0x00503CF0
    int ResetTurnData(int **a2, struct gbGfxManager *p); // 0x00503FA0
    int ResetTurnSystem(); // 0x005040D0
    int ClearTurnSlot(int nVal); // 0x00504420
    bool GetTurnSlotData(int nVal); // 0x00504440
    bool HasTurnChanged(float *pfVal); // 0x00504460
    char ProcessTurn(); // 0x005045B0
    int * GetNextActiveTask(); // 0x005049F0
    char ScanTurnSlots(); // 0x00504A80
    char ClearActionSlot(int nVal); // 0x00504AB0
    char EnqueueCommand(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, float fVal, const void *pData, const void *pData2); // 0x00504B50
    int ProcessQueuedCommand(int nVal); // 0x00504C50
    int ClearAll(); // 0x00504E30
    int CheckAllDone(); // 0x0050D440
    int UpdateSlotTimer(int nVal); // 0x0050DA90
    int ProcessCommand(); // 0x0050E0D0
    int Method_50E160(int nVal); // 0x0050E160
    int CalcFacingAngle(int nVal); // 0x0050E360
    int ResolveActionEffect(int nVal); // 0x0050E550
    int ProcessSlotAction(int nVal); // 0x0050EB00
    int UpdateActionTimers(float fVal); // 0x0050EF60
    int AnimCallback_Attack(int nVal); // 0x0050F080
    int AnimCallback_UseItem(int nVal); // 0x0050F150
    int AnimCallback_Throw(int nVal, int nVal2); // 0x0050F310
    int AnimCallback_CastMagic(int nVal); // 0x0050F410
    int AnimCallback_WaitCmd(int nVal); // 0x0050F4C0
    int AnimCallback_MoveTo(int nVal); // 0x0050F590
    CCBProtectWindow * Create_d710(); // 0x0051D710
    void ShowWindow(); // 0x0051DDA0
    CCBStage() {} // auto-generated default ctor

};
