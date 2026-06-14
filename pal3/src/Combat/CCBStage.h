#pragma once
// Auto-generated: CCBStage

#include "gbengine/gbengine_types.h"
#include "gbengine/gbGfxManager.h"
#include "tagStageTask.h"

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
class ECBStageTaskState;

class CCBStage {
public:
    // vtable (7 methods, order matches binary layout)

    CCBSystem * m_pCBSystem; // +0x0
    CCBRoleState * m_pRoleState; // +0x4
    CCBEditor * m_pEditor; // +0x8
    CCBStageCam * m_pCam; // +0xC
    CCBCamControl * m_pCamControl; // +0x10
    CCBStageScene * m_pScene; // +0x14
    CCBStageRole * m_pRole[11]; // +0x18
    char _gap_01C[40]; // +0x1C
    Actor * m_TempStorageNGH; // +0x44
    Actor * m_NGHVariance; // +0x48
    Actor * m_TempStorageWPX; // +0x4C
    Actor * m_WPXVariance; // +0x50
    CCBDisplayChain * m_pDisplayChain; // +0x54
    CCBStageShadow * m_pShadow; // +0x58
    CCBStageEffect * m_pEffect; // +0x5C
    int m_BFARole; // +0x60
    int m_BFARound; // +0x64
    tagPOINT m_ptMousePos; // +0x68
    char _gap_06C[4]; // +0x6C
    int m_nSelectedRole; // +0x70
    _BYTE m_bRoleSelected[11]; // +0x74
    BYTE m_bHideSceneAndRole; // +0x7F
    float m_fDamageNumPosY[5]; // +0x80
    int _todo_094; // +0x94
    BYTE m_nStageStatus; // +0x98
    BYTE m_bFlag99; // +0x99
    BYTE m_bFlag9A; // +0x9A
    BYTE m_bFlag9B; // +0x9B
    int m_nTaskCount; // +0x9C
    int m_nClearRoleAllTask; // +0xA0
    int m_nRoleSlot; // +0xA4
    BYTE m_nForceDelTask; // +0xA8
    char _gap_0A9[3]; // +0xA9
    float m_fMusicVolume; // +0xAC
    BYTE m_bPaused; // +0xB0
    char _gap_0B1[3]; // +0xB1
    int m_nTask; // +0xB4
    int m_nCurTask; // +0xB8
    int m_nCurSubTask; // +0xBC
    tagStageTask m_Task[256]; // +0xC0
    char _gap_4C0[672768]; // +0x4C0
    int m_RoleSlots; // +0xA48C0
    BYTE m_bAllDone; // +0xA48C4
    BYTE m_nActiveRoleIndex; // +0xA48C5
    char _gap_A48C6[2]; // +0xA48C6
    int m_nActiveIdx; // +0xA48C8
    int m_CamAngles; // +0xA48CC
    int _todo_124; // +0xA48D0
    gbColorQuad m_CamParams; // +0xA48D4
    int m_nActionIdx; // +0xA48D8
    int m_TargetPos; // +0xA48DC
    int m_nTurnCounter; // +0xA48E0
    float m_fRotPitch; // +0xA48E4
    float m_fRotYaw; // +0xA48E8
    float m_fTimeAccum; // +0xA48EC
    float m_fTimerRaw; // +0xA48F0
    float m_fAccumX; // +0xA48F4
    float m_fAccumY; // +0xA48F8
    float m_fAllDone; // +0xA48FC
    float m_ActionAngles; // +0xA4900
    float m_fTurnDelay; // +0xA4904
    int m_nActionTimer; // +0xA4908
    float m_ActionCmds; // +0xA490C
    float _todo_1FC; // +0xA4910
    float m_pSubStage; // +0xA4914
    int m_nSubStageState; // +0xA4918
    int _todo_208; // +0xA491C
    int _todo_20C; // +0xA4920
    char * m_pController; // +0xA4924
    float m_fTurnProgress; // +0xA4928
    float m_fPrevRotX; // +0xA492C
    float m_fPrevRotY; // +0xA4930
    int m_nTurnCount; // +0xA4934
    int m_nCmdCount; // +0xA4938
    int m_nTurnPhase; // +0xA493C
    int m_nLastAction; // +0xA4940
    int m_nTurnIndex; // +0xA4944
    int m_nResetState; // +0xA4948
    int m_CmdQueue; // +0xA494C
    short m_TurnFlags; // +0xA4950
    char _gap_A4952[2]; // +0xA4952
    int m_TurnData; // +0xA4954
    char _todo_36D; // +0xA4958
    char _gap_A4959[3]; // +0xA4959
    int m_hTask; // +0xA495C
    int m_hTaskParam; // +0xA4960
    int _todo_570; // +0xA4964
    int _todo_574; // +0xA4968
    int m_RoleData; // +0xA496C
    int _todo_5C8; // +0xA4970
    int m_TaskQueue; // +0xA4974
    int m_TaskState; // +0xA4978
    int m_nTaskExist; // +0xA497C
    int m_DamageData; // +0xA4980
    BYTE m_nTaskState; // +0xA4984
    char _gap_A4985[3]; // +0xA4985
    void * _todo_1198; // +0xA4988
    int _todo_119C; // +0xA498C
    int m_TurnBuffer; // +0xA4990
    int m_nAllDone; // +0xA4994
    float m_fCurPosX; // +0xA4998
    float m_fCurPosY; // +0xA499C
    float m_fCurPosZ; // +0xA49A0
    float m_fTargetPosX; // +0xA49A4
    float m_fTargetPosY; // +0xA49A8
    float m_fTargetPosZ; // +0xA49AC
    float m_fVelX; // +0xA49B0
    float m_fVelY; // +0xA49B4
    float m_fVelZ; // +0xA49B8
    float m_fAngleDegrees; // +0xA49BC
    float m_fCombatAnimY; // +0xA49C0
    int m_nBattleResult; // +0xA49C4
    int m_nActionFilterA; // +0xA49C8
    int m_nActionFilterB; // +0xA49CC
    int m_nDoneCount; // +0xA49D0
    int m_nTotalCount; // +0xA49D4
    float m_fTurnTimer; // +0xA49D8
    int m_nTurnSlot0; // +0xA49DC
    int m_nTurnSlot1; // +0xA49E0
    int m_nTurnSlot2; // +0xA49E4
    int m_nTurnSlot3; // +0xA49E8
    int m_nTurnSlot4; // +0xA49EC
    int m_nTurnSlot5; // +0xA49F0
    int m_nResultSlot0; // +0xA49F4
    int m_nResultSlot1; // +0xA49F8
    char _todo_639C0[2000]; // +0xA49FC
    void * _todo_64190; // +0xA51CC
    int _todo_A48A8; // +0xA51D0
    UINT m_dwAniFlagOver; // +0xA51D4
    // total size: 0xA51D8 (676312)

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
    void SetupCamControl(); // 0x004E0010
    int * ResetAndSetSystem(int nVal); // 0x004E02F0
    int Reset(); // 0x004E0330
    int ResetTurnSlots(); // 0x004E0340
    char SyncTimeScale(); // 0x004E0380
    char DestroyDialog(); // 0x004E03F0
    char CreatePreviewDialog(); // 0x004E0430
    bool ProcessAction(HWND pData); // 0x004E0530
    static void CreatePreview(float fVal); // 0x004E05B0
    BOOL DestroyPreviewWindow(); // 0x004E0650
    bool FindThreadByParam(int nVal, unsigned int dwVal); // 0x004F06C0
    CCBStageRole * GetRole(int index); // 0x004F4AA0
    char CheckGDBTypeCompat(unsigned int *pdwVal); // 0x004F6CD0
    CCBStage(int pCBSystem); // 0x004FB9A0
    unsigned int _CCBStage(); // 0x004FB9F0
    bool Create(); // 0x004FBE50
    bool Destroy(); // 0x004FBF90
    void Update(); // 0x004FC0A0
    int Update_c150(); // 0x004FC150
    int EditorUpdate(int a2); // 0x004FC3A0
    void Render(); // 0x004FC6F0
    int GetRoleIndex(int nameCrc, const void *pData, char a4); // 0x004FC700
    int GetRoleName(int nameCrc, int nVal, int nVal2, int nVal3, int nVal4, int *p_DWORD, int nVal5, int nVal6); // 0x004FC7D0
    void Procced(int nVal); // 0x004FC8B0
    char GetStageRole(int idx); // 0x004FC8F0
    char GetStageRoleByIdx(int idx); // 0x004FC940
    bool IsDoTask(int eTask); // 0x004FC980
    bool EndTask(int nIndex); // 0x004FC9A0
    char * DelTask(int nIndex, _BYTE *p_BYTE, int *p_DWORD); // 0x004FC9C0
    bool ForceDelTask(int nIndex); // 0x004FCA00
    void GetTask(); // 0x004FCA80
    char GetTaskID(int nIndex, int nVal); // 0x004FCBD0
    char GetTaskState(int a2, bool *a3, int a4); // 0x004FCC10
    char GetTaskState(int a2, int a3); // 0x004FCC50
    bool IsTaskFinished(int nIndex); // 0x004FCD00
    static unsigned __int8 * IsTaskValidButNotFinish(unsigned __int8 *result, int eTask, int nVal); // 0x004FCD50
    bool IsTaskExist(unsigned int dwTaskID); // 0x004FCDA0
    void DoTask(int nVal); // 0x004FCDE0
    bool StartSubTask(int n); // 0x004FCE00
    int IsSubTaskFinished(int a2, int a3); // 0x004FCE70
    bool IsAllSubTaskFinished(int n); // 0x004FCFB0
    bool IsTaskValid(int n); // 0x004FD0B0
    int IsSubTaskValid(int a2, int a3); // 0x004FD1A0
    bool IsIdle(int nVal); // 0x004FD290
    bool HasNormalAttackRole(int nRoleIndex); // 0x004FD3D0
    void ClearRoleAllTask(int nRoleIndex); // 0x004FD880
    void EndRoleAllTask(int nRoleIndex); // 0x004FDA10
    int GetRoleTaskNum(int nRoleIndex); // 0x004FDB10
    void SelectRole(int nRoleIndex); // 0x004FDD90
    unsigned int ProcWait(int formal); // 0x004FDFC0
    unsigned int ProcShowFiveLineup(int formal); // 0x004FE290
    unsigned int ProcShowEnemyFiveLineup(); // 0x004FE540
    unsigned int ProcFiveLienupFadeIn(int formal); // 0x004FE550
    unsigned int ProcFiveLienupFadeOut(int formal); // 0x004FE600
    unsigned int ProcShowSneakAttackState(unsigned int  a_74); // 0x004FE660
    void HandleKeyCtrl(int n); // 0x004FECE0
    bool HandleKeyFriend(int Selected); // 0x004FEE60
    unsigned int ProcShowName(unsigned int formal); // 0x004FEFB0
    unsigned int ProcShowItemName(int formal); // 0x004FF1B0
    unsigned int ProcShowDamage(unsigned int formal); // 0x004FF3D0
    int ProcTaskSlot(int nVal); // 0x004FF560
    unsigned int ProcShowCost(int formal); // 0x004FF5C0
    unsigned int ProcShowCombatDialog(int formal); // 0x004FF740
    unsigned int ProcGrabStageRole(unsigned int formal); // 0x004FF840
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
};
