#pragma once
// Auto-generated: CCBStageRole

#include "ACTION_KIND.h"
#include "Array.h"
#include "ERoleActState.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"
#include "tagRoleTask.h"

class Actor;
class CCBRoleState;
class CCBStage;
class tagCmdData;
class tagRoleState;

class CCBStageRole {
public:
    CCBStage * m_pStage; // +0x0
    CCBRoleState * m_pRoleState; // +0x4
    char m_sLastRole[12]; // +0x8
    Array m_sRoleArray; // +0x14
    char _gap_018[12]; // +0x18
    char m_sRoleData[228]; // +0x24
    BYTE m_bValid; // +0x108
    BYTE m_bVisible; // +0x109
    BYTE m_bPaused; // +0x10A
    BYTE m_bAbsTime; // +0x10B
    float m_fTimeScale; // +0x10C
    BYTE m_bAlive; // +0x110
    BYTE m_bRun; // +0x111
    BYTE m_bFlash; // +0x112
    BYTE m_bFlashCounter; // +0x113
    float m_fFlashTimeKey; // +0x114
    BYTE m_bShowWeapon; // +0x118
    char _gap_119[3]; // +0x119
    float m_fBlend; // +0x11C
    BYTE m_bBeSelected; // +0x120
    char _gap_121[3]; // +0x121
    int m_nIndex; // +0x124
    UINT m_dwID; // +0x128
    Actor * m_pActor; // +0x12C
    Actor * m_pRawActor; // +0x130
    gbGeomNode * m_pWeaponModel; // +0x134
    gbVec3D m_vecWeapon; // +0x138
    char _gap_13C[8]; // +0x13C
    gbVec3D m_rotWeapon; // +0x144
    char _gap_148[8]; // +0x148
    gbVec3D m_vNoteThrowPos; // +0x150
    char _gap_154[8]; // +0x154
    gbVec3D m_vThrowVec; // +0x15C
    char _gap_160[8]; // +0x160
    float m_vecLen; // +0x168
    float m_fTask; // +0x16C
    float m_fStatus; // +0x170
    BYTE m_bShowWeaponModel; // +0x174
    BYTE m_bCatching; // +0x175
    BYTE m_bDelAllTask; // +0x176
    char _gap_177[1]; // +0x177
    int m_iState; // +0x178
    BYTE m_bForceFinishThrowingWeapon; // +0x17C
    char _gap_17D[3]; // +0x17D
    float m_fMaxThrowSpeed; // +0x180
    float m_fThrowSpeed; // +0x184
    float m_fThrowLen; // +0x188
    tagCmdData * m_ThrowCmdData; // +0x18C
    int m_nRotAngle; // +0x190
    int m_nCurActionOff; // +0x194
    int m_nCurActionParam; // +0x198
    int _todo_19C; // +0x19C
    int m_nTransportRun; // +0x1A0
    int m_ActionSlot0; // +0x1A4
    int m_ActionSlot1; // +0x1A8
    int m_ActionSlot2; // +0x1AC
    int m_nUseRecoverItem; // +0x1B0
    int m_nProperAction; // +0x1B4
    gbOBBox * m_OBBox; // +0x1B8
    int m_nOBBox; // +0x1BC
    int m_fActionSpeed0; // +0x1C0
    int _todo_1C4; // +0x1C4
    char _gap_1C8[16]; // +0x1C8
    int _todo_1D8; // +0x1D8
    char _gap_1DC[8]; // +0x1DC
    int m_apSlotData; // +0x1E4
    float _todo_1E8; // +0x1E8
    char _gap_1EC[4]; // +0x1EC
    int m_nCurState; // +0x1F0
    int m_nActionType0; // +0x1F4
    BYTE m_bProperCurAction; // +0x1F8
    BYTE m_bSlotActive0; // +0x1F9
    BYTE m_bSlotBlocked0; // +0x1FA
    char _gap_1FB[9]; // +0x1FB
    BYTE m_bTransMtl; // +0x204
    BYTE m_bSpecTransport; // +0x205
    BYTE m_bGrabed; // +0x206
    BYTE m_bNormalGrab; // +0x207
    UINT m_dwStageTaskID; // +0x208
    BYTE m_bExternalTask; // +0x20C
    char _gap_20D[3]; // +0x20D
    float m_fLeftWeapon; // +0x210
    float m_fRightWeapon; // +0x214
    int m_nTask; // +0x218
    int m_nCurTask; // +0x21C
    char * m_fp; // +0x220
    char _gap_224[12]; // +0x224
    tagRoleTask m_Task[64]; // +0x230
    char _gap_330[5888]; // +0x330
    UINT m_dwCurWeaponIndex; // +0x1A30
    ERoleActState m_eRoleActState; // +0x1A34
    ACTION_KIND m_eCurAction; // +0x1A38
    gbVec3D m_vecSunDir; // +0x1A3C
    char _gap_1A40[8]; // +0x1A40
    gbVec3D m_vecPos; // +0x1A48
    char _gap_1A4C[8]; // +0x1A4C
    gbVec3D m_vecInitPos; // +0x1A54
    char _gap_1A58[8]; // +0x1A58
    gbVec3D m_vecRunTarget; // +0x1A60
    char _gap_1A64[8]; // +0x1A64
    gbVec3D m_vecRunVelocity; // +0x1A6C
    char _gap_1A70[8]; // +0x1A70
    float m_fFaceDir; // +0x1A78
    float m_fInitFaceDir; // +0x1A7C
    UINT m_dwCurAniFlag; // +0x1A80
    UINT m_dwAniFlagOver; // +0x1A84
    UINT m_dwAniFlagWork; // +0x1A88
    UINT m_dwAniFlagWork1; // +0x1A8C
    UINT m_dwAniFlagWork2; // +0x1A90
    UINT m_dwAniFlagWork3; // +0x1A94
    UINT m_dwAniFlagPause; // +0x1A98
    UINT m_dwAniFlagStore; // +0x1A9C
    UINT m_dwAniFlagFlyup; // +0x1AA0
    UINT m_dwAniFlagFlydown; // +0x1AA4
    UINT m_dwAniFlagThrowED; // +0x1AA8
    UINT m_dwAniFlagCatchED; // +0x1AAC
    UINT m_dwAniFlagSJump; // +0x1AB0
    UINT m_dwAniFlagEJump; // +0x1AB4
    UINT m_dwLastExternalActionCRC; // +0x1AB8
    char _tail_1ABC[4]; // +0x1ABC
    // total size: 0x1AC0 (6848)

    void Init(int thisa); // 0x0040CC90
    char * GetAlive(int thisa, int *pConfig); // 0x0040CCF0
    int PassCmd(void *p_DWORD); // 0x0040CF60
    int CheckValid(int nVal); // 0x0040D010
    int * GetByIndex(int *p_DWORD); // 0x0040DCF0
    int Find(char *String1); // 0x0040DD30
    void Reset(); // 0x0040DD80
    int RandomizePositions(); // 0x0044CFF0
    void InitUIByName(); // 0x004E2C50
    int TaskExecAttack(int nVal); // 0x004FFA90
    int TaskExecCommand(int nVal); // 0x004FFCB0
    int TaskResetToIdle(int nVal); // 0x004FFED0
    int TaskExecMagicEffect(int nVal); // 0x004FFF60
    int TaskExecSkill(int nVal); // 0x00500220
    int TaskWaitIdle(int nVal); // 0x005004B0
    int TaskExecItem(int nVal); // 0x00500550
    int TaskForceEnd(int nVal); // 0x005007A0
    int TaskExecAction(int nVal); // 0x00500C20
    int TaskResolveAction(int nState); // 0x00500D50
    int TaskMoveToStart(int nVal); // 0x005011B0
    int TaskBlendToReady(int nVal); // 0x00501330
    int TaskBlendToEnd(int nVal); // 0x00501410
    int TaskEnterGuard(int nVal); // 0x005014E0
    int SetupCombatAction(int nVal); // 0x005015C0
    int TaskReturnToIdle(int nVal); // 0x00501CF0
    int TaskShowLevelUp(int nVal); // 0x00501E60
    int TaskShowSkillLearned(int nVal); // 0x00501F30
    void _CCBStageRole(int nVal, int nVal2, int *p_DWORD); // 0x00508930
    void Proceed(); // 0x005090F0
    void SetAlive(bool bAlive); // 0x00509130
    void SetMaxBlend(); // 0x00509140
    void SetVisible(); // 0x00509180
    void SetPause(); // 0x00509190
    void OnChangeAction(); // 0x005091D0
    int CheckAction(); // 0x005091E0
    void OnPlayAction(); // 0x00509220
    bool IsUnderMouse(); // 0x00509270
    bool IsCollideRay(); // 0x00509280
    void GetRoleRadius(); // 0x00509290
    int GetRoleHeight(); // 0x005092A0
    CCBStageRole * GetOBBox(int nVal); // 0x005092B0
    int GetRotAngle(); // 0x00509410
    bool IsIdle(unsigned int dwVal); // 0x00509540
    bool IsAtInitPos(); // 0x00509690
    bool IsAtProtectPos(int index, int nAttacker, int nVal); // 0x005096D0
    bool IsTaskFinished(int nVal, BOOL fpTask); // 0x005099A0
    void IsDoTask(gbMatrixStack *fpTask); // 0x00509B90
    int Grab(int a2); // 0x0050A180
    void Release(char dwStageTaskID); // 0x0050A1A0
    void TryRelease(); // 0x0050A1B0
    void ForceRelease(char pData); // 0x0050A1F0
    void DangerForceRelease(char pData); // 0x0050A200
    bool IsGrabedBy(); // 0x0050A210
    void GetPointerPos(); // 0x0050A260
    void SetBladeTime(int fBladeTime); // 0x0050A2B0
    bool CheckViewTarget(); // 0x0050A4B0
    bool LoadAction(gbRay nActIndex); // 0x0050A500
    int GetStatus(int index); // 0x0050A520
    float * GetWorldPos(); // 0x0050A560
    double AddTask(float *fp); // 0x0050A5D0
    bool ForceDelTaskByPFN(); // 0x0050A6F0
    bool ForceEndTaskByPFN(); // 0x0050A700
    bool EndTask(int fp, int dwTaskID); // 0x0050A770
    bool DelTask(int nIndex); // 0x0050A8E0
    bool DelAllTask(int nVal, char pData); // 0x0050A8F0
    char GetCurrentTask(int nVal); // 0x0050A920
    int GetCurrentTaskIndex(); // 0x0050A960
    bool IsReady(int idx); // 0x0050A980
    tagRoleState * DoTask(gbVec3D *dwMsg); // 0x0050A9B0
    void ClearBadPushTask(float fVal); // 0x0050AA60
    double PushBackAllTask(); // 0x0050AAE0
    void ClearAniMsg(char pData, float fVal); // 0x0050AB10
    void SetParam(int pParam, char dw1); // 0x0050AC50
    char GetProperCurAction(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int *pnVal, const void *pData, int nVal6); // 0x0050AD30
    char ProcTransportRun(unsigned int dwMsg, int nVal, int nVal2, int nVal3, int *pnVal, const void *pData, int nVal4); // 0x0050B070
    void SetForceFinishThrowingWeapon(int bForce); // 0x0050B290
    char GetCurrentState(); // 0x0050B330
    unsigned int ProcCatchED(); // 0x0050B360
    char FindFreeSlot(int a2); // 0x0050B430
    char CountValidTasks(); // 0x0050B4C0
    int FindNextTask(); // 0x0050B4F0
    void GetTaskState(); // 0x0050B530
    char ProcPursueRole(int formal, int nVal, char pData); // 0x0050B580
    unsigned int ProcTurn(); // 0x0050BBD0
    unsigned int ProcTurnToRole(int formal); // 0x0050BCD0
    unsigned int ProcBlock(int dwMsg); // 0x0050C320
    unsigned int ProcMagic(unsigned int dwMsg); // 0x0050C970
    unsigned int ProcUseRecoverItem(float dwMsg); // 0x0050CDE0
    int CheckPushState(int nVal); // 0x0050EDA0
    int OnPhysicalHit(int nVal); // 0x0050EE70
    int OnMagicHit(int nVal); // 0x0050F200
    int ClearTaskIfMatch(int nVal); // 0x0050FA20
    int SetActionVisible(char nActIndex); // 0x00518E10
    static bool CheckActionValid(int nVal); // 0x00521A80
    CCBStageRole * LoadSaveData(int *a2); // 0x00521B00
    int DispatchUpdate(unsigned __int8 nFlag); // 0x00521E60
    int DispatchUpdateAll(unsigned __int8 nFlag); // 0x00521F30
    CCBStageRole(); // 0x00522030
    int * ClearRoleState(); // 0x005220E0
    void CleanupScript(); // 0x00522120
    int GetWeaponSlotPtr(int nVal); // 0x00523090
    void PlaySound(char *name, int nVal); // 0x0053E310
    unsigned int PauseSound(); // 0x0053E9C0
    unsigned int ResumeSound(); // 0x0053EA10
};
