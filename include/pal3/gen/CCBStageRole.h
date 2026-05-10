#pragma once
// Auto-generated: CCBStageRole

#include "ACTION_KIND.h"
#include "ERoleActState.h"
#include "tagCmdData.h"
#include "tagRoleTask.h"

class Actor;
class CCBRoleState;
class CCBStage;

class CCBStageRole {
public:
    CCBStage * m_pStage; // +0x0
    CCBRoleState * m_pRoleState; // +0x4
    char m_sLastRole[256]; // +0x8
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
    float m_fBlend; // +0x11C
    BYTE m_bBeSelected; // +0x120
    int m_nIndex; // +0x124
    DWORD m_dwID; // +0x128
    Actor * m_pActor; // +0x12C
    Actor * m_pRawActor; // +0x130
    gbGeomNode * m_pWeaponModel; // +0x134
    gbVec3D m_vecWeapon; // +0x138
    gbVec3D m_rotWeapon; // +0x144
    gbVec3D m_vNoteThrowPos; // +0x150
    gbVec3D m_vThrowVec; // +0x15C
    gbVec3D m_vecLen; // +0x168
    BYTE m_bShowWeaponModel; // +0x174
    BYTE m_bCatching; // +0x175
    int m_iState; // +0x178
    BYTE m_bForceFinishThrowingWeapon; // +0x17C
    float m_fMaxThrowSpeed; // +0x180
    float m_fThrowSpeed; // +0x184
    float m_fThrowLen; // +0x188
    tagCmdData m_ThrowCmdData; // +0x18C
    gbOBBox m_OBBox; // +0x1B8
    BYTE m_bTransMtl; // +0x204
    BYTE m_bSpecTransport; // +0x205
    BYTE m_bGrabed; // +0x206
    BYTE m_bNormalGrab; // +0x207
    DWORD m_dwStageTaskID; // +0x208
    BYTE m_bExternalTask; // +0x20C
    float m_fLeftWeapon; // +0x210
    float m_fRightWeapon; // +0x214
    int m_nTask; // +0x218
    int m_nCurTask; // +0x21C
    void * * m_fp; // +0x220
    tagRoleTask m_Task[64]; // +0x230
    DWORD m_dwCurWeaponIndex; // +0x1A30
    ERoleActState m_eRoleActState; // +0x1A34
    ACTION_KIND m_eCurAction; // +0x1A38
    gbVec3D m_vecSunDir; // +0x1A3C
    gbVec3D m_vecPos; // +0x1A48
    gbVec3D m_vecInitPos; // +0x1A54
    gbVec3D m_vecRunTarget; // +0x1A60
    gbVec3D m_vecRunVelocity; // +0x1A6C
    float m_fFaceDir; // +0x1A78
    float m_fInitFaceDir; // +0x1A7C
    DWORD m_dwCurAniFlag; // +0x1A80
    DWORD m_dwAniFlagOver; // +0x1A84
    DWORD m_dwAniFlagWork; // +0x1A88
    DWORD m_dwAniFlagWork1; // +0x1A8C
    DWORD m_dwAniFlagWork2; // +0x1A90
    DWORD m_dwAniFlagWork3; // +0x1A94
    DWORD m_dwAniFlagPause; // +0x1A98
    DWORD m_dwAniFlagStore; // +0x1A9C
    DWORD m_dwAniFlagFlyup; // +0x1AA0
    DWORD m_dwAniFlagFlydown; // +0x1AA4
    DWORD m_dwAniFlagThrowED; // +0x1AA8
    DWORD m_dwAniFlagCatchED; // +0x1AAC
    DWORD m_dwAniFlagSJump; // +0x1AB0
    DWORD m_dwAniFlagEJump; // +0x1AB4
    DWORD m_dwLastExternalActionCRC; // +0x1AB8
    // total size: 0x1AC0 (6848)

    char IsActive(int index); // 0x004ED040
    ~CCBStageRole(); // 0x00508930
    static int Proceed(); // 0x005090F0
    static int SetAlive(); // 0x00509130
    static int SetMaxBlend(); // 0x00509140
    static int SetVisible(); // 0x00509180
    static int SetPause(); // 0x00509190
    static int OnChangeAction(); // 0x005091D0
    static int CheckAction(); // 0x005091E0
    static int OnPlayAction(); // 0x00509220
    static int IsUnderMouse(); // 0x00509270
    static int IsCollideRay(); // 0x00509280
    static int GetRoleRadius(); // 0x00509290
    static int GetRoleHeight(); // 0x005092A0
    char * GetOBBox(int a2); // 0x005092B0
    int GetRotAngle(); // 0x00509410
    char IsIdle(unsigned int a2); // 0x00509540
    char IsAtInitPos(); // 0x00509690
    char IsAtProtectPos(int a2, int a3, int a4); // 0x005096D0
    // [IDA_USERPURGE] IsTaskFinished; // 0x005099A0
    void IsDoTask(gbMatrixStack *a2); // 0x00509B90
    int Grab(int a2); // 0x0050A180
    char Release(char a2); // 0x0050A1A0
    void TryRelease(); // 0x0050A1B0
    char ForceRelease(char a2); // 0x0050A1F0
    char DangerForceRelease(char a2); // 0x0050A200
    int IsGrabedBy(); // 0x0050A210
    void GetPointerPos(); // 0x0050A260
    void SetBladeTime(int a2); // 0x0050A2B0
    bool LoadAction(gbRay a2); // 0x0050A500
    int GetStatus(int index); // 0x0050A520
    float * GetWorldPos(); // 0x0050A560
    double AddTask(float *a2); // 0x0050A5D0
    bool ForceDelTaskByPFN(); // 0x0050A6F0
    bool ForceEndTaskByPFN(); // 0x0050A700
    bool EndTask(int a2, int a3); // 0x0050A770
    char DelTask(int a2); // 0x0050A8E0
    char DelAllTask(int a2, char a3); // 0x0050A8F0
    char GetCurrentTask(int a2); // 0x0050A920
    int GetCurrentTaskIndex(); // 0x0050A960
    bool IsReady(int idx); // 0x0050A980
    _DWORD * DoTask(float *a2); // 0x0050A9B0
    void ClearBadPushTask(float a2); // 0x0050AA60
    double PushBackAllTask(); // 0x0050AAE0
    void ClearAniMsg(char a2, float a3); // 0x0050AB10
    int SetParam(int a2, char a3); // 0x0050AC50
    char GetProperCurAction(_DWORD *a2, _DWORD *a3, _DWORD *a4, _DWORD *a5, _DWORD *a6, int *a7, const void *a8, _DWORD *a9); // 0x0050AD30
    char ProcTransportRun(float a2, float a3, int a4, int a5, int *a6, const void *a7, float a8); // 0x0050B070
    char SetForceFinishThrowingWeapon(int a2); // 0x0050B290
    char GetState(); // 0x0050B330
    int ProcCatchED(); // 0x0050B360
    int GetTaskState(); // 0x0050B530
    char ProcPursueRole(int a2, int a3, char a4); // 0x0050B580
    int ProcTurn(); // 0x0050BBD0
    int ProcTurnToRole(int a2); // 0x0050BCD0
    int ProcBlock(int a2); // 0x0050C320
    int ProcMagic(int a2); // 0x0050C970
    int ProcUseRecoverItem(float a2); // 0x0050CDE0
    void PlaySound(char *name, int a3); // 0x0053E310
};
