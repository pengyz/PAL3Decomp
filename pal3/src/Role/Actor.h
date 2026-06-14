#pragma once
// Auto-generated: Actor

#include "gbengine/gbActor.h"
#include "gbengine/gbengine_types.h"

class RoleAtt;

class Actor {
public:
    char m_actarray[16]; // +0x0
    gbActor * m_pact; // +0x10
    char m_name[8]; // +0x14
    float m_fMoveSpeed; // +0x1C
    float m_fMoveRange; // +0x20
    char * m_pAllocBuf; // +0x24
    float m_fTransitionSpeed; // +0x28
    float m_fTransitionPos; // +0x2C
    int m_nRoleParam0; // +0x30
    float m_fRoleParam1; // +0x34
    float m_fRoleParam; // +0x38
    float m_fRoleParam2; // +0x3C
    float m_fRoleParam3; // +0x40
    int m_nRoleParam2; // +0x44
    char * m_pRoleParam3; // +0x48
    int m_nCachedA; // +0x4C
    BYTE m_nCachedB; // +0x50
    char _gap_051[3]; // +0x51
    int m_nTransform; // +0x54
    int m_nRoleState0; // +0x58
    BYTE m_bUIFlagA; // +0x5C
    BYTE m_bUIFlagB; // +0x5D
    char _gap_05E[2]; // +0x5E
    float m_fAnimParam; // +0x60
    float m_szText; // +0x64
    char _gap_068[8]; // +0x68
    void * m_pResource; // +0x70
    int m_nModelId; // +0x74
    char _gap_078[8]; // +0x78
    int m_nAnimParam0; // +0x80
    int m_nAnimParam1; // +0x84
    gbVec3D m_vecBonePos; // +0x88
    char _gap_08C[8]; // +0x8C
    int m_nPathBuffer; // +0x94
    int m_nAnimBuffer; // +0x98
    int m_nParticleBuffer; // +0x9C
    gbVec3D m_vecTargetPos; // +0xA0
    char _gap_0A4[8]; // +0xA4
    float m_fInterpStart; // +0xAC
    float m_fInterpEnd; // +0xB0
    int m_nInterpFrames; // +0xB4
    float m_fActionSpeed; // +0xB8
    int m_nInterpCurrent; // +0xBC
    int m_nInterpState; // +0xC0
    float m_fInterpSpeed; // +0xC4
    int m_nModelLoadState; // +0xC8
    int m_nState; // +0xCC
    char * m_pRoleObj; // +0xD0
    int m_nPathEnabled; // +0xD4
    BYTE m_fScale; // +0xD8
    BYTE m_bParamFlag; // +0xD9
    char _gap_0DA[2]; // +0xDA
    float m_fMatrixA; // +0xDC
    BYTE m_fMatrixB; // +0xE0
    char _gap_0E1[3]; // +0xE1
    float m_fMatrixC; // +0xE4
    int m_nMatrixParam; // +0xE8
    float m_fMatrixParamA; // +0xEC
    float m_fMatrixParamB; // +0xF0
    float m_fMatrixE; // +0xF4
    float m_fMatrixF; // +0xF8
    float m_fMatrixParamC; // +0xFC
    Actor * m_Actor; // +0x100
    char _gap_104[4]; // +0x104
    int m_nCmdParam; // +0x108
    char _gap_10C[4]; // +0x10C
    gbActor * m_pActor; // +0x110
    char _gap_114[4]; // +0x114
    char m_szTexture[28]; // +0x118
    gbVec3D m_vecLocalPos; // +0x134
    char _gap_138[16]; // +0x138
    short m_nAnimState; // +0x148
    char _gap_14A[2]; // +0x14A
    BYTE m_nActionType; // +0x14C
    BYTE m_bActionFlag1; // +0x14D
    char _gap_14E[2]; // +0x14E
    BYTE m_nActionParam; // +0x150
    BYTE m_bActionFlag2; // +0x151
    BYTE m_bActionFlag3; // +0x152
    BYTE m_bActionActive; // +0x153
    int m_nActionState; // +0x154
    BYTE m_nActionResult; // +0x158
    BYTE m_bInitialized; // +0x159
    char _gap_15A[2]; // +0x15A
    int m_nHP; // +0x15C
    int m_nMaxHP; // +0x160
    BYTE m_bHPVisible; // +0x164
    char _gap_165[3]; // +0x165
    int m_nHandleEvent; // +0x168
    gbVec3D m_vecPos; // +0x16C
    char _gap_170[8]; // +0x170
    gbVec3D m_vecRot; // +0x178
    char _gap_17C[8]; // +0x17C
    int m_nCloneParam; // +0x184
    float m_fActionAssignParam; // +0x188
    int m_nCloneParamB; // +0x18C
    int m_nCloneState; // +0x190
    int m_nCloneFlag1; // +0x194
    int m_nCloneFlag2; // +0x198
    float m_fFacingAngle; // +0x19C
    char _gap_1A0[4]; // +0x1A0
    int m_nModelParamA; // +0x1A4
    char _gap_1A8[4]; // +0x1A8
    int m_nModelParamB; // +0x1AC
    int m_nRoleState1; // +0x1B0
    RoleAtt * m_pEquipAtt0; // +0x1B4
    int m_nAnimFrames; // +0x1B8
    int m_nTransitionParam; // +0x1BC
    RoleAtt * m_pEquipAtt1[3]; // +0x1C0
    char _gap_1C4[8]; // +0x1C4
    RoleAtt * m_pEquipAtt2[3]; // +0x1CC
    char _gap_1D0[20]; // +0x1D0
    float m_fBlendWeight; // +0x1E4
    int m_obbox; // +0x1E8
    char _gap_1EC[4]; // +0x1EC
    void * m_pSelfAtt; // +0x1F0
    short m_nAnimFrame; // +0x1F4
    char _gap_1F6[10]; // +0x1F6
    void * m_pParticleData; // +0x200
    char _gap_204[20]; // +0x204
    float m_fAnimDelta; // +0x218
    UINT m_dwMatMsg[11]; // +0x21C
    BYTE m_bChangedMat; // +0x248
    char m_curact[8]; // +0x249
    char _gap_251[39]; // +0x251
    float m_fDirX; // +0x278
    float m_fDirY; // +0x27C
    float m_fDirZ; // +0x280
    float m_fNormX; // +0x284
    float m_fNormY; // +0x288
    float m_fNormZ; // +0x28C
    float m_fDistAccum; // +0x290
    float m_fSpeed; // +0x294
    char _gap_298[12]; // +0x298
    float m_fAngleDeg; // +0x2A4
    char _gap_2A8[4]; // +0x2A8
    BYTE m_bDirFlag; // +0x2AC
    char _gap_2AD[39]; // +0x2AD
    int m_nAnimCounter; // +0x2D4
    char _gap_2D8[45]; // +0x2D8
    BYTE m_bStateFlag; // +0x305
    char _gap_306[2]; // +0x306
    char * m_pRoleState; // +0x308
    char _gap_30C[4]; // +0x30C
    int m_nUpdateMode; // +0x310
    char _tail_314[32]; // +0x314
    // total size: 0x334 (820)

    void UpdatePhysics(float fVal); // 0x00419690
    unsigned int GetInnerAnimDuration(int animId); // 0x0041B9F0
    int SetActionByName(unsigned __int8 *pbyName); // 0x0041BCA0
    int InitParticles(); // 0x0044CB30
    int ApplyStateArray(); // 0x00456EE0
    char * SaveState(); // 0x00456F10
    unsigned int GetAnimDurationByIndex(int nVal); // 0x0050ACF0
    int ResetTransformState(); // 0x005309A0
    bool UpdateAnimState(char pData); // 0x00530C00
    bool GetBoundRadius(); // 0x00530F20
    void BlendAnimation(float fVal); // 0x00530F70
    void UpdateFrame(float arg0); // 0x00531260
    int SetParam(int nVal); // 0x00536160
    int GetDefaultFOV_thunk(); // 0x00536220
    int SetDefaultFOV(); // 0x00536230
    int GetDefaultDist_thunk(); // 0x00536240
    void SetDefaultDist(); // 0x00536250
    void DestroyInternalData(); // 0x00536310
    int ResetDefaultState(); // 0x005363A0
    void SetActorAction(int actionId); // 0x005363E0
    int InitActorComponents(); // 0x005364B0
    char ProcessActorFrame(); // 0x00536560
    int GetDefaultFOV2_thunk(); // 0x00536A40
    int SetDefaultFOV2(); // 0x00536A50
    int GetDefaultDist2_thunk(); // 0x00536A60
    void SetDefaultDist2(); // 0x00536A70
    void FastInit(); // 0x00536A80
    int SetMaterialName(void *name); // 0x00536AC0
    int CompareActionName(int actionIdx, int nVal); // 0x00536C50
    unsigned int GetAnimDuration(int animId); // 0x00536CC0
    void EnableTransition(int nVal, int nVal2); // 0x00536CE0
    void SetTimeScale(float scale); // 0x00536D00
    int QueryState(); // 0x00536FB0
    int DispatchAction(int actionId); // 0x00536FC0
    int PlayAction(int actionId); // 0x00536FD0
    int UpdateAllActions(); // 0x00536FF0
    int ValidateInput(int nVal, int nVal2); // 0x005370E0
    void SetTextureName(const char *pszName); // 0x00537120
    void SetVisible(int bVisible); // 0x005371B0
    int GetArrayCount(); // 0x005372B0
    int * LoadActionSequence(int *p_DWORD, unsigned int dwVal, int *p_DWORD2); // 0x005372D0
    int StoreParam(int nVal, int nVal2); // 0x00537510
    static int ClearArrayEntry(int nVal); // 0x005375B0
    void ClearPathBuffer(); // 0x005375F0
    int LoadSaveData(char *pszSlotIdx); // 0x005376E0
    int LoadActions(FILE *Stream, int *pnVal); // 0x00537770
    void ClearAllocBuffers(); // 0x00537A30
    FILE * DoSceneTransition(double pData, int nVal); // 0x00537A90
    char * InitAnimSequence(); // 0x005381D0
    BOOL EnsureDirectory(); // 0x00538320
    BOOL LoadActorModel(int nVal); // 0x00538500
    int ClearActionFlags(); // 0x00538CE0
    static BOOL CompareModelName(char *String1, char *String2); // 0x00538D20
    void BuildCollisionMesh(int *pOut); // 0x00538FA0
    char * ActionEntry_Assign(int nVal); // 0x005392C0
    int * ClearActionArrays(); // 0x005394D0
    int AddActionByName(const char *pszName, const char *pszName2, int nVal); // 0x00539540
    void GetAnimDataBuffer(void **Buffer, int Stream); // 0x00539700
    void IterateActiveActors(); // 0x005399E0
    char SearchAnimByIndex(char *String1, char *pszBuf); // 0x00539A90
    void RegisterAnim(char *pszName, char *pszBuf); // 0x00539AF0
    int * ClearAllActions(); // 0x00539D60
    char * InsertAnimFrame(float fVal); // 0x00539E70
    char IterateAllocBuffer(int nVal); // 0x0053A020
    int * InitAction(_BYTE *pActionType); // 0x0053A060
    _WORD * GetActionArrayEnd(_WORD *p_WORD, __int16 *pnVal); // 0x0053A080
    int InsertAction(int *p_DWORD, char **nY); // 0x0053A0C0
    int GetActionCount(); // 0x0053A2E0
    void DestroyActionRange(int nVal, int nVal2); // 0x0053A310
    int * CopyActionData(int nVal); // 0x0053A670
    int FindMatchingEntry(int nY, int nVal, int nX); // 0x0053AF30
    void SetVideoRegions(int nX, int nVal, int nY); // 0x0053AF70
    char * CopyBufferBlocks(char *pszDst, char *pszSrc, char *pszBuf3); // 0x0053AFA0
    char * CopyIfValid(char *pszBuf, char *pszBuf2, const void *pData); // 0x0053AFE0
    int GetCount(); // 0x0053B230
    char * CompareBuffers(char *pszBuf, char *pszBuf2, char *pszBuf3); // 0x0053B260
    static int * SelectPointer(int *pnVal, int *pnVal2, int *pnVal3); // 0x0053B2A0
    char * SetCurrentAction(int nVal); // 0x0053B890
    int * ActArray_Assign(int *p_DWORD); // 0x0053BAE0
    int * BoneIndexVec_Assign(int *pnVal); // 0x0053BD30
    int GetActionCountEx(); // 0x0053BEB0
};
