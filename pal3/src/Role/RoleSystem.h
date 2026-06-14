#pragma once
// Auto-generated: RoleSystem

#include "Actor.h"
#include "UIFrameWnd.h"
#include "UIItem.h"
#include "UIWnd.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"

class Object3D;

class RoleSystem : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    char * m_pVtable; // +0x44
    float m_fStateX; // +0x48
    float m_fStateY; // +0x4C
    BYTE m_nStateMode; // +0x50
    char _gap_051[3]; // +0x51
    int m_nTimerDuration; // +0x54
    float m_fDirX; // +0x58
    float m_fDirY; // +0x5C
    float m_fDirZ; // +0x60
    char * m_pPathPoints; // +0x64
    int m_nPathCount; // +0x68
    char * m_pPathCurrent; // +0x6C
    char * m_pPathNext; // +0x70
    int _todo_074; // +0x74
    int _todo_078; // +0x78
    int m_nPathField7C; // +0x7C
    float m_fMoveX; // +0x80
    int m_nPathState; // +0x84
    float m_fMoveZ; // +0x88
    char * m_pPathListHead; // +0x8C
    int m_nActionResult; // +0x90
    int m_nDispFontColor; // +0x94
    int m_nDispWndColor; // +0x98
    int m_nField9C; // +0x9C
    float m_fPosX; // +0xA0
    float m_fPosY; // +0xA4
    float m_fPosZ; // +0xA8
    char m_nFacing; // +0xAC
    char m_nActionState; // +0xAD
    char m_nAnimState; // +0xAE
    BYTE m_bActionPause; // +0xAF
    int m_szModelName; // +0xB0
    int m_mapData; // +0xB4
    float m_fScale; // +0xB8
    int m_nImageIdx; // +0xBC
    float m_fMoveSpd; // +0xC0
    BYTE m_byStateArray; // +0xC4
    char m_bFlags; // +0xC5
    BYTE m_bActionState; // +0xC6
    char _gap_0C7[1]; // +0xC7
    float m_fAngle; // +0xC8
    float m_fTileHeight; // +0xCC
    int m_nSpawnData; // +0xD0
    int m_nActionType; // +0xD4
    int m_nActionStep; // +0xD8
    float m_fActionParam; // +0xDC
    BYTE m_nSpawnFlags; // +0xE0
    BYTE m_nRoleAction; // +0xE1
    BYTE m_nRoleSlot; // +0xE2
    char _gap_0E3[1]; // +0xE3
    float m_fWaypointX; // +0xE4
    float m_fWaypointZ; // +0xE8
    BYTE m_nActionParam; // +0xEC
    BYTE m_nInitMoveMode; // +0xED
    char _gap_0EE[2]; // +0xEE
    int m_nSpawnExtra; // +0xF0
    int m_nSpawnParam2; // +0xF4
    int m_szModelPath; // +0xF8
    UIWnd * m_pWaypointWnd; // +0xFC
    int m_nParamArray; // +0x100
    BYTE m_bSpawnByteA; // +0x104
    BYTE m_bSpawnByteB; // +0x105
    char _gap_106[2]; // +0x106
    int m_nSpawnParam; // +0x108
    int m_nActionTimer; // +0x10C
    gbVec3D m_vecPosArray; // +0x110
    char _gap_114[8]; // +0x114
    int m_nMoveSrc; // +0x11C
    int m_nMoveDst; // +0x120
    int m_nMoveStep; // +0x124
    int m_nSavedState; // +0x128
    int m_nVisState; // +0x12C
    BYTE m_bVisFlag; // +0x130
    _BYTE _gap_169[3]; // +0x131
    char * m_pWndFrame; // +0x134
    int _todo_170; // +0x138
    int m_nActive; // +0x13C
    float m_fInactiveTime; // +0x140
    void * m_pCmdQueue; // +0x144
    void * m_pCmdQueueEnd; // +0x148
    float m_fCmdInterval; // +0x14C
    float m_fCmdTimer; // +0x150
    char * m_pPathNodeIter; // +0x154
    int m_nCmdQueuePos; // +0x158
    Actor m_partyActor; // +0x15C
    char _gap_160[816]; // +0x160
    float m_fPathTargetY; // +0x490
    float m_fPathTargetZ; // +0x494
    float m_fPathAngle; // +0x498
    float m_fPathSpeed; // +0x49C
    int m_nPrevMoveMode; // +0x4A0
    int m_nMoveMode; // +0x4A4
    int m_nMoveSubMode; // +0x4A8
    int m_nCollisionState; // +0x4AC
    int m_nCollisionParam; // +0x4B0
    BYTE m_bPathActive; // +0x4B4
    char _gap_4B5[3]; // +0x4B5
    int m_nCoreState; // +0x4B8
    int m_nTransformState; // +0x4BC
    float m_fMovement; // +0x4C0
    float m_fRotAxisX; // +0x4C4
    float m_fRotAxisY; // +0x4C8
    float m_fRotAxisZ; // +0x4CC
    int m_nMovement; // +0x4D0
    float m_fSavedRotX; // +0x4D4
    UIFrameWnd m_FrameA; // +0x4D8
    char _gap_4DC[68]; // +0x4DC
    int m_nActiveRole; // +0x520
    int m_nRoleCount; // +0x524
    int m_nAnimation; // +0x528
    int m_nAnimCopy1; // +0x52C
    int m_nAnimCopy2; // +0x530
    int m_nAnimCopy3; // +0x534
    Object3D * m_pLinkedRole; // +0x538
    int m_nTransformMode; // +0x53C
    char * m_pLinkedSystem; // +0x540
    float m_fAnimSpeed; // +0x544
    float m_fMoveRadius; // +0x548
    float m_fMoveSpeed; // +0x54C
    int m_nMoveReset; // +0x550
    gbGeomNode * m_pRenderObj; // +0x554
    int m_bRenderFlag1; // +0x558
    char m_bRenderFlag2; // +0x55C
    char _gap_55D[3]; // +0x55D
    int _todo_5AC; // +0x560
    char * m_pCtrlPoint; // +0x564
    int m_nMoveRole; // +0x568
    int m_nRetryCount; // +0x56C
    float m_fCachePosX; // +0x570
    float m_fCachePosY; // +0x574
    float m_fCachePosZ; // +0x578
    float m_fMoveTargetX; // +0x57C
    int m_fMoveTargetY; // +0x580
    float m_fMoveTargetZ; // +0x584
    float m_fMoveRole; // +0x588
    float m_fMoveParamY; // +0x58C
    float m_fMoveParamZ; // +0x590
    int _todo_61C; // +0x594
    UIWnd _embed_UIWnd_624; // +0x598
    char _gap_59C[64]; // +0x59C
    int m_teamSlots[307]; // +0x5DC
    float m_fCBTimer; // +0xAA8
    float pfVal; // +0xAAC
    BYTE m_CCBStageCamBuffer; // +0xAB0
    char _gap_AB1[3]; // +0xAB1
    int _todo_BA4; // +0xAB4
    int m_wndPanel; // +0xAB8
    UIWnd m_StaticSlotArray; // +0xABC
    char _gap_AC0[64]; // +0xAC0
    int m_teamSlotsB[200]; // +0xB00
    int m_nCombatViewMode; // +0xE20
    HWND dwInitParam; // +0xE24
    HWND g_hCombatDlg1; // +0xE28
    HWND g_hCombatDlg2; // +0xE2C
    int m_nActorRenderCount; // +0xE30
    HWND g_hCBStageCamDlg; // +0xE34
    BYTE m_bWPARAM_17A9926; // +0xE38
    char _gap_E39[3]; // +0xE39
    int m_nCCBUISelectedRole; // +0xE3C
    int m_nCCBUI_17A9940; // +0xE40
    BYTE m_bCommandEdited; // +0xE44
    char _gap_E45[3]; // +0xE45
    int m_pScriptBuf; // +0xE48
    int _field_FE4; // +0xE4C
    void * _todo_FF8; // +0xE50
    int m_configData[96]; // +0xE54
    int _todo_1198; // +0xFD4
    int _todo_119C; // +0xFD8
    int m_nMoveState1; // +0xFDC
    int m_nMoveState2; // +0xFE0
    int m_nMoveState3; // +0xFE4
    BYTE m_bMoveFlag1; // +0xFE8
    char _gap_FE9[3]; // +0xFE9
    int m_nMoveParam1; // +0xFEC
    int m_nMoveParam2; // +0xFF0
    BYTE m_bMoveFlag2; // +0xFF4
    UIItem m_partyUI3; // +0xFF5
    char _gap_FF9[231]; // +0xFF9
    int m_teamData3[29]; // +0x10E0
    // total size: 0x1154 (4436)

    virtual ~RoleSystem() {}

    virtual BOOL UpdateTimer(int nVal, int nVal2); // 0x00532710
    virtual int HandleMsgDLL(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved); // 0x005329A0
    void * AllocSlotData(int nVal); // 0x004202A0
    virtual void ResetState(); // 0x004209E0
    BOOL CheckSceneCollision(int *nFlag, int nVal); // 0x004083E0
    int BindRoleToScene(int index, float *pfVal, float *pfVal2, int nVal, char pData); // 0x00408460
    int * Init(); // 0x0040BE50
    int RecalcAggregatedStats(char pData); // 0x0040BE80
    static int ForceStopRole(int nVal); // 0x0040C9A0
    static void RenderMainRole(void *pMatrixStack); // 0x00410430
    static int CheckVisible(int nVal); // 0x00410E40
    void ApplyMoveStep(double fInput, int nVal, float fVal, char bCollide); // 0x00411E00
    void SetMoveSpeed(float fSpeed, int nRoleIndex, int nFlag); // 0x00412230
    void UpdatePosition(); // 0x004122C0
    void RenderRole(gbMatrixStack *pStack, int nVal); // 0x00412400
    int NotifySceneChange(); // 0x004125B0
    static int GetAnimOffset(int nType, unsigned __int8 nMode); // 0x004126D0
    int UpdateTransform(); // 0x00412710
    int UpdatePath(int nVal); // 0x00412940
    int StartHalfSpeedMovement(); // 0x00412A50
    void MoveToTile(__int64 tileXY, int nMode); // 0x00412A90
    void SetMoveTarget(float *pTargetPos, int nFlags); // 0x00412B60
    int SetPathWaypoint(float fVal); // 0x00412C30
    char BindPartyToScene(float *pfVal, int nVal); // 0x00412D90
    int MoveRole(float *pPos, int nVal, int nVal2, int nVal3); // 0x00412E60
    char UpdateRole(float *pfVal, int nVal, int nVal2); // 0x00413010
    char MoveToTileCheck(int nTileX, int nTileY, int nMode); // 0x004132B0
    void InterpolateMoveFrame(float fVal); // 0x00413390
    int StepAlongPath(double fStepSize, float fVal); // 0x00413420
    double AdvanceToTarget(double fDelta); // 0x00413850
    int PlaceAtRegion(int nSceneIdx, int nRegion); // 0x00413C00
    void PathFollowUpdate(); // 0x00413CD0
    void NormalizeDirection(float *pfDir); // 0x00414250
    int NotifyMoveComplete(); // 0x004142E0
    double UpdateMovement(double result, gbVec3D *pB); // 0x00414350
    float * UpdateMoveInterpolation(float *pfVal, float *pfVal2); // 0x004148C0
    void GetPosition(float *pOut, int nVal); // 0x00414980
    void UpdateMoveTimer(); // 0x00414A10
    int PathFind(float *pTarget); // 0x00414A30
    int GetActionByIndex(int nParam); // 0x00414E30
    int PlayAction(char *pszAction, int nMode); // 0x00414F90
    void UpdateActionState(float fVal); // 0x004150C0
    static void ScaleVector(float *pVec, float fScale); // 0x004161E0
    void CheckMoveCollisionDist(int thisa, float *pfVal); // 0x00416220
    int CalcTileDistance(int nTileX, int nTileY); // 0x004163B0
    void SetTargetRotation(gbVec3D *pTarget); // 0x00416490
    BOOL IsPathMoving(); // 0x004164E0
    int IsActionBlocked(); // 0x00416500
    void IsPathComplete(float *pTargetPos, int nMode); // 0x00416550
    int UpdateMovement(float fDeltaTime, int nMode); // 0x00416620
    void UpdateAnimation(float *pfVal); // 0x00416790
    void ProcessInteraction(); // 0x00416BC0
    int GetActiveRole(); // 0x00416F10
    void InitPathTracking(float *nFlags); // 0x00416FA0
    void RestoreMoveMode(float *nFlags); // 0x00416FE0
    void SetupMoveState(float *pfVal); // 0x00417040
    void UpdateTransform(float arg0); // 0x00417420
    int EnterSubMode6(); // 0x00417850
    BOOL CheckVisibility(); // 0x004178A0
    void SetState(int state); // 0x00417AC0
    void StopAndResetPath(); // 0x00417BC0
    double UpdateMoveSubMode(double result, float result_4); // 0x00417C50
    int CheckWidgetReady(gbRay *pRay); // 0x004180B0
    int GetMoveState(); // 0x00418130
    int Notify(); // 0x004181E0
    void AddVec3ToTarget(int nVal, int nVal2); // 0x00418970
    int StartPathMove(char *pszBuf, int nVal, char *pszBuf2, int nVal2, float fVal, int nVal3); // 0x004189C0
    BOOL IsInBounds(int nVal, int nVal2); // 0x00418D90
    char TryMoveToTarget(__int16 pData, int nVal); // 0x00418DC0
    int ResetPathParams(int nVal); // 0x00419030
    int ProcessMoveCommand(int *p_DWORD); // 0x00419790
    void StartLinearMove(int *pTargetPos, int nMode); // 0x004198C0
    void GetActorState(double thisa, int nVal, int nVal2, int nVal3); // 0x00419A20
    int GetDirection(float *pOut); // 0x00419A80
    int NotifyAndSetMode6(); // 0x00419AE0
    __int64 SetCollisionRadius(); // 0x00419B10
    void UpdateFollowBehavior(float fDelta); // 0x00419B30
    BOOL AdvancePathStep(float *pfVal); // 0x00419EF0
    void SetActorTexture(const char *pszName); // 0x0041A150
    void ScanMoveDirections(float fRadius); // 0x0041A1A0
    void UpdateFollowerMovement(float fVal); // 0x0041A450
    void UpdateFollowVelocity(); // 0x0041ABE0
    void UpdateFollowVelocityEx(); // 0x0041AD40
    void SetBlendMode(float fAlpha); // 0x0041AEA0
    int SetTransform(int *p_DWORD); // 0x0041AEE0
    int AllocPathPage(int nVal, int nVal2); // 0x0041AF50
    int StopPathMovement(int nVal); // 0x0041B120
    int GetCurrentTile(); // 0x0041B300
    void LoadWeaponModel(char *pszRoleName); // 0x0041B420
    char ApproachTarget(int nVal); // 0x0041B6C0
    BOOL InterpolateHeight(float *pfVal); // 0x0041BA10
    int InitDefaultState(); // 0x0041BAD0
    int GetCount(); // 0x0041BBE0
    int ExportRoleData(float *pfVal); // 0x0041BC30
    int * ClearColors(_BYTE *p_BYTE); // 0x0041BD40
    const char * GetRoleName(unsigned int nRoleIndex); // 0x0041BD70
    int FlushCommandQueue(); // 0x0041C090
    int SetInactive(int nVal); // 0x0041C190
    int AddCameraKeyframe(); // 0x0041D220
    RoleSystem(); // 0x00420290
    int GetCurrentID(int *pnVal, char pData); // 0x00420320
    void InitRoleImage(); // 0x004203C0
    unsigned __int8 * LoadRoleImage(int nIndex, const char *pszPath); // 0x004207D0
    virtual RoleSystem * sub_420910(char a2); // 0x00420910
    void InitInternal(); // 0x00420930
    int CopyRoleToSlot(RoleSystem *pRoleSystem, int index); // 0x00420940
    char GetTile(int nX, int nY); // 0x004209F0
    int * IsTileInBounds(int nVal, int nY, int nVal2); // 0x00420A10
    void SetRoleGridPosition(float fVal, int nVal, float fVal2, int nVal2); // 0x00420A90
    int GetRolePtr(int index); // 0x00420F30
    char * GetMapNodePtr(int nIndex); // 0x00420F50
    BOOL IsRoleInRange(int index, int *pnVal, int nVal); // 0x00420F70
    BOOL CheckMoveCollision(int *index, float *pfVal, int nVal); // 0x00420FB0
    BOOL CheckCollision(int *pResult, int nFlag); // 0x00421020
    BOOL IsTilePassable(char nTileType, int nSceneIdx, int nX, int nY); // 0x00421150
    void SetRoleParam(int index, float *pfVal, int *pnVal, int *p_DWORD); // 0x00421440
    BOOL ValidatePathIndex(int index, int nY, int nVal); // 0x004214B0
    int AdvanceOnPath(int *pResult, char *nFlag, int nVal, char *pszBuf, int nVal2); // 0x004215B0
    int ValidatePath(int *pResult, int *nFlag, int *pnVal, int nVal, int nVal2, int **a7); // 0x00421710
    BOOL GetPathTarget(int *pResult, int *nFlag, int *pnVal, char *pszBuf, int nVal, int **a7); // 0x004218B0
    int UpdatePathProgress(char arg0, int index, char *pszBuf, int nVal, char *pszBuf2, int nVal2); // 0x00421A90
    char * NotifyPathEnd(int nVal); // 0x00421BF0
    int * BuildPathSegment(int *pnVal, char pData); // 0x00421D10
    int ClearWaypointBuffer(int nVal, int nVal2, int nVal3, char pData); // 0x00421DD0
    void ResetTransition(); // 0x00421EA0
    size_t GetFontColor(FILE *Stream); // 0x00421F20
    char ClearPathData(FILE *Buffer); // 0x00421F70
    BOOL BuildModelPath(const char *pszName); // 0x00422000
    int * ResetModelPaths(); // 0x00422140
    static char SetAnimBlend(int nVal); // 0x00422430
    void SetAnimFrame(); // 0x00422540
    void ResetGlobalPos(); // 0x00422740
    static int SetCameraMode(int nVal); // 0x004234A0
    void ProcessAction(); // 0x0042A010
    BOOL CheckScriptTrigger(struct gbVec3D *p); // 0x0042A950
    int SetActionState(int nVal, char pData); // 0x0042AD40
    void UpdateStateMode(); // 0x0042B510
    int * SetTileTypeVisible(int nTileType, int bVisible); // 0x0042C0C0
    int ExecScriptDataCmd(int *p_DWORD); // 0x0042D9F0
    int ExecScriptDataA(); // 0x0042DBD0
    int ExecScriptDataB(); // 0x0042DD80
    int ExecScriptDataIdx(int nVal); // 0x0042E870
    int ExecScriptDataC(); // 0x0042EA30
    int ProcessWaypoint(); // 0x0044B470
    int InitUICtrlArray(); // 0x0044CD90
    int InitDefaultPositions(); // 0x0044CEC0
    int InitRandomParticles(); // 0x0044D380
    int ctor_1D20(); // 0x00531D20
    void ctor(); // 0x00531E70
    int InitAllSystems(); // 0x00531F50
    int ApplyRotationAxis(int nVal, char pData); // 0x00532360
    int ShowHideUI(char pData); // 0x00532410
    int StartBlinkUI(); // 0x005326A0
    int StopBlinkUI(); // 0x005326E0
    static int ScaleValue(int nVal, int *pnVal, int *p_DWORD); // 0x00532960
    void AdjustHeight(int nVal); // 0x00532C80
    int GetStateMode(); // 0x00532D30
    void NegateStateMode(); // 0x00532D40
    char ResetPathState(); // 0x00532E10
};
