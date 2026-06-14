#pragma once
// Auto-generated: CameraCtrl

#include "gbengine/gbCamera.h"
#include "gbengine/gbengine_types.h"

class CameraCtrl {
public:
    // vtable (3 methods, order matches binary layout)

    gbCamera * m_pCamera; // +0x0
    float m_fMinDist; // +0x4
    void * m_pTarget; // +0x8
    int m_nFlags; // +0xC
    float m_fTargetAngle; // +0x10
    float m_fCurAngle; // +0x14
    int m_nCamState; // +0x18
    float m_fAngleDest; // +0x1C
    float m_fAngleSrc; // +0x20
    float m_fFOV; // +0x24
    float m_fFOVLerp; // +0x28
    int m_bCamFlag; // +0x2C
    float m_fParamF; // +0x30
    float m_fLerpPosX; // +0x34
    float m_fLerpPosY; // +0x38
    float m_fLerpPosZ; // +0x3C
    float m_fLerpTargetX; // +0x40
    float m_fLerpTargetY; // +0x44
    float m_fLerpTargetZ; // +0x48
    int m_nUIPosX; // +0x4C
    int m_nUIWidgetW; // +0x50
    int m_nUIWidgetH; // +0x54
    int m_nUIWidgetSavedW; // +0x58
    float m_fUIWidgetSavedH; // +0x5C
    int m_nViewMode; // +0x60
    int m_nViewFlags; // +0x64
    char m_szCamPath[260]; // +0x68
    int m_nBlendWeightIdx; // +0x16C
    char _gap_170[12]; // +0x170
    int m_nInitParams; // +0x17C
    int m_nParamState; // +0x180
    int m_nParamA; // +0x184
    int m_nParamB; // +0x188
    int m_nParamC; // +0x18C
    gbVec3D m_lastFrom; // +0x190
    char _gap_194[8]; // +0x194
    gbVec3D m_fromVec; // +0x19C
    char _gap_1A0[8]; // +0x1A0
    float m_yaw; // +0x1A8
    float m_fCtrlYaw; // +0x1AC
    int m_dist; // +0x1B0
    char _gap_1B4[8]; // +0x1B4
    float m_nextYAW; // +0x1BC
    char _gap_1C0[4]; // +0x1C0
    float m_fAngle; // +0x1C4
    float m_fOrbitAngle; // +0x1C8
    float m_mode; // +0x1CC
    char m_argstack[4]; // +0x1D0
    float m_fCamDist; // +0x1D4
    int m_nWidth; // +0x1D8
    int m_nHeight; // +0x1DC
    int m_nAsCurrent; // +0x1E0
    char _gap_1E4[8]; // +0x1E4
    gbVec3D m_vecLookAt; // +0x1EC
    char _gap_1F0[20]; // +0x1F0
    gbVec3D m_vecUpDir; // +0x204
    char _gap_208[36]; // +0x208
    float m_fViewDistance; // +0x22C
    char _gap_230[4]; // +0x230
    float m_fViewPitch; // +0x234
    float m_fViewYaw; // +0x238
    float m_fDefaultPosX; // +0x23C
    float m_fDefaultPosY; // +0x240
    float m_fDefaultPosZ; // +0x244
    float m_fDefaultOffset; // +0x248
    char _gap_24C[4]; // +0x24C
    int m_pCameraEvent; // +0x250
    char _gap_254[20]; // +0x254
    float m_szText; // +0x268
    WORD m_wParamA; // +0x26C
    char _gap_26E[2]; // +0x26E
    WORD m_wParamB; // +0x270
    char _gap_272[62]; // +0x272
    int m_nEventViewX; // +0x2B0
    int m_nEventViewY; // +0x2B4
    int m_nEventHandle; // +0x2B8
    int _todo_2BC; // +0x2BC
    char _gap_2C0[173]; // +0x2C0
    BYTE m_bCamEventFlag; // +0x36D
    char _gap_36E[10]; // +0x36E
    BYTE m_bPageMode; // +0x378
    BYTE m_bCamDirty; // +0x379
    char _gap_37A[2]; // +0x37A
    int m_nPageParam; // +0x37C
    BYTE m_bBlendUpdate; // +0x380
    char _gap_381[3]; // +0x381
    int m_nBlendWeight; // +0x384
    char _gap_388[6]; // +0x388
    BYTE m_bBlendWeight; // +0x38E
    BYTE m_bHandleEvent; // +0x38F
    BYTE m_bAutoRotate; // +0x390
    char _gap_391[3]; // +0x391
    int m_nBlendTimer; // +0x394
    char _gap_398[4]; // +0x398
    int m_nBlendState; // +0x39C
    int m_nSlotParam; // +0x3A0
    char _gap_3A4[256]; // +0x3A4
    int m_nBlendWeightA; // +0x4A4
    int m_nBlendWeightB; // +0x4A8
    int m_nBlendWeightC; // +0x4AC
    float m_roleParams; // +0x4B0
    char _gap_4B4[60]; // +0x4B4
    int m_nViewState; // +0x4F0
    char _gap_4F4[776]; // +0x4F4
    void * _todo_7FC; // +0x7FC
    char _gap_800[1288]; // +0x800
    BYTE m_bBlendActive; // +0xD08
    BYTE m_bBlendPause; // +0xD09
    char _gap_D0A[2]; // +0xD0A
    int m_nTickCount; // +0xD0C
    int m_nTickStamp; // +0xD10
    BYTE m_bTickInit; // +0xD14
    char _gap_D15[3]; // +0xD15
    int m_CamBlocks; // +0xD18
    char _tail_D1C[732]; // +0xD1C
    // total size: 0xFF8 (4088)

    virtual ~CameraCtrl() {}

    virtual BOOL IsAngleBelowTarget(); // 0x0041CBD0
    virtual int UpdateTransition(float fDelta); // 0x0041CC50
    int InitParams(void *pParams); // 0x0041C1B0
    void SetAsCurrent(int flags); // 0x0041C630
    float * CalcOrbitalPos(float *pfOut, float fTargetX, float fTargetY, float fTargetZ); // 0x0041C670
    void SetDimention(int w, int h); // 0x0041CA90
    void * GetViewTarget(void *pTarget, float *pPos); // 0x0041CAC0
    float * GetLerpPos(float *pResult, float fCurrent, float fTarget, float fFactor); // 0x0041CBF0
    int SetupFollow(int nVal, int nVal2, int nVal3, int nVal4); // 0x0041CEE0
    int SetupOrbit(int nVal, int nVal2, int nVal3, int nVal4, int nVal5); // 0x0041CF20
    int SetupTrack(int nVal, int nVal2, int nVal3, int nVal4, int nVal5); // 0x0041CF70
    int SetupDirect(int *p_DWORD, int nVal, int nVal2); // 0x0041CFC0
    int SetupLerp(int nVal, int *p_DWORD, int nVal2, int nVal3); // 0x0041D010
    int SmoothTransition(int nVal, int nVal2, int nVal3, int nVal4, int *p_DWORD, int nVal5); // 0x0041D070
    int SetCamMode(int mode); // 0x0041D5B0
    int SetCamDist(int nVal); // 0x0041D5C0
    char * UpdateFOVLerp(); // 0x0041D5D0
    void PopState(); // 0x0041D730
    int * SetCameraSource(int nVal, int *p_DWORD); // 0x0041D7C0
    unsigned int SetupCameraArray(int a2); // 0x0041D7F0
    void ResetSceneMgrParams(); // 0x0041D960
    void UpdateInternal(float fDelta); // 0x0041D9A0
    static void AttachToRole(int nVal); // 0x0041E720
    static int GetModeByIndex(int nVal); // 0x0041EB50
    static int InitPathState(); // 0x0041EF30
    int ResetToDefaults(); // 0x00487480
    int * LoadRoleParams(); // 0x00487610
    int BuildRenderLists(); // 0x0048B370
    void CalcStatPower(int nVal); // 0x0048C520
    BOOL HandleCameraEvent(int nParam, BOOL bFlag); // 0x0048C610
    int ProcessCameraTask(int a2, int a3); // 0x0048C9A0
    char InitBlendState(int a2, int a3); // 0x0048CCE0
    void UpdateBlendWeight(int arg0, int nVal); // 0x0048D040
    void * CreateCameraUI(int nVal); // 0x0048D5D0
    int FindNextValidSlot(int *pCounter); // 0x0048EE00
    int FindPrevValidSlot(int *pCounter); // 0x0048EE30
    char ProcessSaveSlotNav(); // 0x0048EE60
    virtual int ValidateDevice(int a2, int a3); // 0x0048EF80
    CameraCtrl * _sdtor_17(CameraCtrl *Block, char a2); // 0x004BE8F0
    void OnIdle(); // 0x004BE910
    void OnIdleB(); // 0x004BEAA0
    void RenderFadeEffect(); // 0x004BEBF0
    void RenderFadeEffectB(); // 0x004BED40
    char InitFromConfig(); // 0x00504510
    char InitFromScreen(); // 0x00504540
    void SetViewport(int nFlags); // 0x0052EBE0
    char InitDefaultView(); // 0x00533EA0
    int SetFOVIfValid(int nVal); // 0x00534DC0
};
