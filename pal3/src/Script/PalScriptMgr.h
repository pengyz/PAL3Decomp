#pragma once
// Auto-generated: PalScriptMgr

#include "PtrArray.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbengine_types.h"

class RoleSystem;
class UIWnd;
class scSCEFile;

class PalScriptMgr {
public:
    // vtable (6 methods, order matches binary layout)

    BYTE m_bGetSceneScript; // +0x0
    char _gap_001[3]; // +0x1
    PtrArray m_script; // +0x4
    char _gap_008[12]; // +0x8
    scSCEFile * m_scefile; // +0x14
    float _todo_018; // +0x18
    float _todo_01C; // +0x1C
    float _todo_020; // +0x20
    int _todo_024; // +0x24
    float m_fCamX; // +0x28
    float m_fCamY; // +0x2C
    float m_fCamZ; // +0x30
    int m_Sub_0034; // +0x34
    int m_nFrameCounter; // +0x38
    float m_fField3C; // +0x3C
    scSCEFile * m_pBigMapSce; // +0x40
    float m_fField44; // +0x44
    float m_fPosZ; // +0x48
    scSCEFile * m_scepath; // +0x4C
    BYTE m_bBigMapState; // +0x50
    char _gap_051[3]; // +0x51
    int _todo_054; // +0x54
    int _todo_058; // +0x58
    char * m_pExecSystem; // +0x5C
    int _todo_060; // +0x60
    int _todo_1F8; // +0x64
    short _todo_1FC; // +0x68
    char _gap_06A[2]; // +0x6A
    short _todo_200; // +0x6C
    char _gap_06E[2]; // +0x6E
    int _todo_204; // +0x70
    float _todo_208; // +0x74
    int _todo_20C; // +0x78
    float _todo_210; // +0x7C
    int m_nExecParam; // +0x80
    int m_vRolePos; // +0x84
    float m_fDefaultFOV; // +0x88
    char _gap_08C[8]; // +0x8C
    int m_nScriptIdx; // +0x94
    void * m_pCurScriptBlock; // +0x98
    int m_nBlockEndAddr; // +0x9C
    void * m_pExecState; // +0xA0
    int m_pVarContext; // +0xA4
    char m_szScriptFile[6]; // +0xA8
    BYTE m_bExecuteBlock; // +0xAE
    BYTE m_bScriptPause; // +0xAF
    int m_RoleAnimData; // +0xB0
    char _gap_0B4[4]; // +0xB4
    int m_bRunning; // +0xB8
    int m_bBlockActive; // +0xBC
    int m_bBlockFlag; // +0xC0
    char _gap_0C4[4]; // +0xC4
    int _todo_C8; // +0xC8
    int m_nSavedBlockNum; // +0xCC
    BYTE m_pSavedIndex; // +0xD0
    BYTE m_bOpcodeFlag; // +0xD1
    char _gap_0D2[2]; // +0xD2
    int m_nExecuteBlock; // +0xD4
    int m_nSavedDataA; // +0xD8
    int m_nSavedDataB; // +0xDC
    float m_fAngle; // +0xE0
    int m_nExecRangeA; // +0xE4
    int m_nExecRangeB; // +0xE8
    int m_nExecRangeC; // +0xEC
    int m_nExecRangeD; // +0xF0
    BYTE m_nCmdType; // +0xF4
    BYTE _todo_0F5; // +0xF5
    BYTE m_bExecuteOpcode; // +0xF6
    BYTE _todo_0F7; // +0xF7
    int m_nCmdValue; // +0xF8
    short m_nCmdParam0; // +0xFC
    char _gap_0FE[2]; // +0xFE
    short m_nCmdParam1; // +0x100
    char _gap_102[2]; // +0x102
    int m_nCmdParam2; // +0x104
    int m_nExecCounter; // +0x108
    RoleSystem * m_pRoleSystemCache; // +0x10C
    BYTE _todo_110; // +0x110
    char _gap_111[1]; // +0x111
    short _todo_112; // +0x112
    short m_Actor; // +0x114
    short _todo_116; // +0x116
    short m_nField_0118; // +0x118
    BYTE _todo_11A; // +0x11A
    char _gap_11B[1]; // +0x11B
    int _todo_2B0; // +0x11C
    char _gap_120[4]; // +0x120
    char * m_pSubScript; // +0x124
    int m_nScriptCount; // +0x128
    PalScriptMgr * m_pScriptObj; // +0x12C
    int m_nScriptDepth; // +0x130
    float m_fPrevPosX; // +0x134
    float m_fPrevPosY; // +0x138
    int m_nExecuteOpcode; // +0x13C
    float m_fExecuteBlock; // +0x140
    float m_fCurPosY; // +0x144
    float m_fAnimSpeed; // +0x148
    char _gap_14C[28]; // +0x14C
    int m_nField_0168; // +0x168
    int m_RolePos; // +0x16C
    char _gap_170[8]; // +0x170
    int m_RoleDir; // +0x178
    char _gap_17C[8]; // +0x17C
    int m_nRoleState; // +0x184
    int m_RoleSubData; // +0x188
    char _gap_18C[4]; // +0x18C
    int m_nRoleParam1; // +0x190
    int m_nRoleParam2; // +0x194
    int m_nRoleParam3; // +0x198
    void * m_pRoleScript; // +0x19C
    char _gap_1A0[4]; // +0x1A0
    int m_nField_01A4; // +0x1A4
    char _gap_1A8[24]; // +0x1A8
    void * m_pOpResult; // +0x1C0
    char _gap_1C4[16]; // +0x1C4
    BYTE m_bTileType; // +0x1D4
    char _gap_1D5[23]; // +0x1D5
    float m_fSpeed1; // +0x1EC
    float m_fSpeed2; // +0x1F0
    short m_nScriptID; // +0x1F4
    char _gap_1F6[24]; // +0x1F6
    short m_nRoleIndex; // +0x20E
    float m_fPosAYTarget; // +0x210
    char _gap_214[2]; // +0x214
    BYTE m_bScriptByte; // +0x216
    char _gap_217[1]; // +0x217
    float m_fPosAX; // +0x218
    float m_fPosAY; // +0x21C
    float m_fPosAZ; // +0x220
    float m_fPosBX; // +0x224
    float m_fPosBY; // +0x228
    float m_fPosBZ; // +0x22C
    int m_nMatrixData; // +0x230
    BYTE m_bRunCommand; // +0x234
    char _gap_235[3]; // +0x235
    int _todo_238; // +0x238
    int _todo_23C; // +0x23C
    int m_bInputBlock; // +0x240
    int m_bRoleLock; // +0x244
    char _gap_248[44]; // +0x248
    void * m_pCaseTable; // +0x274
    int _todo_278; // +0x278
    char _gap_27C[152]; // +0x27C
    char * m_pRoleSystem; // +0x314
    int m_nBlockHandle; // +0x318
    RoleSystem * m_pSceneMgr; // +0x31C
    BYTE m_bRoleCmd_42ac80; // +0x320
    char _gap_321[3]; // +0x321
    int m_nExecState; // +0x324
    char * m_pCmdBuffer; // +0x328
    int m_nLoopCountA; // +0x32C
    int m_nLoopCountB; // +0x330
    int m_nLoopCountC; // +0x334
    int m_nSavedPosX; // +0x338
    PalScriptMgr * m_pSubScriptB; // +0x33C
    int m_nScriptCamX; // +0x340
    int m_nScriptCamY; // +0x344
    char * m_pScriptBlock; // +0x348
    char * m_pExecObj; // +0x34C
    float m_fExecParam; // +0x350
    float m_fExecPosY; // +0x354
    float m_fExecPosZ; // +0x358
    int m_nExecState2; // +0x35C
    char * m_pWaitObj; // +0x360
    char _gap_364[4]; // +0x364
    int m_nWaitCount; // +0x368
    char * m_pScriptInst; // +0x36C
    float m_fDirNeg; // +0x370
    char * m_pClearResult; // +0x374
    int m_nExecHandle; // +0x378
    char _gap_37C[60]; // +0x37C
    int m_nState; // +0x3B8
    char _gap_3BC[96]; // +0x3BC
    int m_bDirty; // +0x41C
    char _gap_420[88]; // +0x420
    int m_nFrameState; // +0x478
    char _gap_47C[120]; // +0x47C
    int m_nOpType; // +0x4F4
    char _gap_4F8[12]; // +0x4F8
    int m_nCmdData; // +0x504
    char _gap_508[8]; // +0x508
    int m_fFramePosX; // +0x510
    int m_fFramePosY; // +0x514
    int m_fFramePosZ; // +0x518
    int m_fFrameScale; // +0x51C
    int m_fFrameRot; // +0x520
    int m_nFrameParam; // +0x524
    char _gap_528[160]; // +0x528
    int m_OpSubObj; // +0x5C8
    int m_OpParam; // +0x5CC
    int m_OpData; // +0x5D0
    char _gap_5D4[8]; // +0x5D4
    int m_OpBuffer; // +0x5DC
    char _gap_5E0[404]; // +0x5E0
    int _todo_774; // +0x774
    char _gap_778[4]; // +0x778
    int m_ctrlParabola; // +0x77C
    char _gap_780[80]; // +0x780
    int m_nField_07D0; // +0x7D0
    char _gap_7D4[360]; // +0x7D4
    int _todo_93C; // +0x93C
    char _gap_940[4]; // +0x940
    UIWnd * m_wndTextDisplay; // +0x944
    char _gap_948[36]; // +0x948
    int m_nField_096C; // +0x96C
    char _gap_970[460]; // +0x970
    int m_nField_0B3C; // +0xB3C
    char _gap_B40[52]; // +0xB40
    int m_nField_0B74; // +0xB74
    char _gap_B78[140]; // +0xB78
    int m_nField_0C04; // +0xC04
    char _gap_C08[92]; // +0xC08
    int m_nField_0C64; // +0xC64
    char _gap_C68[8]; // +0xC68
    int m_nField_0C70; // +0xC70
    char _gap_C74[88]; // +0xC74
    int _todo_CCC; // +0xCCC
    char * m_pScreenEffect; // +0xCD0
    BYTE _field_CD4; // +0xCD4
    char _gap_CD5[3]; // +0xCD5
    int m_nScreenEffect; // +0xCD8
    int m_nEffectTick; // +0xCDC
    int m_nTickStamp; // +0xCE0
    BYTE m_bEffectInit; // +0xCE4
    char _gap_CE5[3]; // +0xCE5
    BYTE m_bEffectActive; // +0xCE8
    BYTE _todo_CE9; // +0xCE9
    char _gap_CEA[390]; // +0xCEA
    int m_nField_0E70; // +0xE70
    char _gap_E74[328]; // +0xE74
    int m_RoleCmdCtx; // +0xFBC
    char _gap_FC0[520]; // +0xFC0
    int m_nTileFlags; // +0x11C8
    float m_fTileHeight; // +0x11CC
    char _gap_11D0[476]; // +0x11D0
    int m_nField_13AC; // +0x13AC
    char _gap_13B0[184]; // +0x13B0
    int m_nField_1468; // +0x1468
    char _gap_146C[36]; // +0x146C
    int m_nField_1490; // +0x1490
    char _gap_1494[208]; // +0x1494
    int m_nField_1564; // +0x1564
    char _gap_1568[148]; // +0x1568
    int m_nField_15FC; // +0x15FC
    char _gap_1600[40]; // +0x1600
    int m_nField_1628; // +0x1628
    char _gap_162C[1252]; // +0x162C
    int m_nField_1B10; // +0x1B10
    char _gap_1B14[76]; // +0x1B14
    int m_nField_1B60; // +0x1B60
    char _gap_1B64[168]; // +0x1B64
    int m_nField_1C0C; // +0x1C0C
    char _gap_1C10[388]; // +0x1C10
    int m_nField_1D94; // +0x1D94
    char _gap_1D98[876]; // +0x1D98
    int m_nCost; // +0x2104
    char _gap_2108[4]; // +0x2108
    int m_nCapacity; // +0x210C
    char _gap_2110[228]; // +0x2110
    float m_fFrameTime; // +0x21F4
    float m_fFrameDelta; // +0x21F8
    float m_fFrameTotal; // +0x21FC
    char _gap_2200[776]; // +0x2200
    char * m_pScriptInstB; // +0x2508
    char * m_pScriptInstC; // +0x250C
    char * m_pScriptInstA; // +0x2510
    PalScriptMgr * m_pScriptInstD; // +0x2514
    char * m_pScriptInstE; // +0x2518
    int m_nScriptResultA; // +0x251C
    int m_nScriptResultB; // +0x2520
    int m_nScriptResultC; // +0x2524
    // total size: 0x2528 (9512)

    virtual BOOL IsWaitComplete(); // 0x00434CC0
    virtual BOOL IsBlendComplete(); // 0x00434D20
    virtual void AccumulateTime(float fDelta); // 0x00434D40
    static int RunScript(int nVal, int nVal2, int nVal3); // 0x004100A0
    int * LoadYlfScript(); // 0x00410920
    int * Get_result(); // 0x0041BDE0
    void CheckTileScript(RoleSystem *pRole, float fVal, char bExecute); // 0x00420B40
    void ExecuteBlock(); // 0x00424C20
    int InitControlBlock(); // 0x00429D80
    void BuildCmdTransform(gbMatrix4 *pMatrix); // 0x00429DB0
    void BuildFullTransform(gbMatrix4 *pMatrix, struct gbVec3D *pPos); // 0x00429F90
    BOOL CheckTileCollision(int *pnVal, int nVal, struct gbVec3D *p); // 0x0042AAE0
    int CmdUpdateRolePath(float *pfVal, float *pfVal2); // 0x0042AC80
    char GetScriptState(); // 0x0042AF80
    int SaveExecutionState(); // 0x0042AFA0
    void ProcessRoleLoading(); // 0x0042B350
    BOOL IsPosInBounds(float *pfPos); // 0x0042B450
    double UpdateScriptRoles(double thisa, int nVal, int nVal2); // 0x0042B5B0
    void OnAnimFinish(); // 0x0042BEA0
    static void HandleGetItem(int nSkillGDBID); // 0x0042BEF0
    PalScriptMgr * ExecuteScriptByID(); // 0x0042BF90
    bool IsScriptReady(); // 0x0042BFE0
    void SetPauseState(int bPause); // 0x0042C030
    struct gbVFileSystem * LoadSceneGeometry(char bNoPol); // 0x0042C280
    bool IsInputBlocked(); // 0x0042C3A0
    void RunCommand(); // 0x0042C440
    int CmdPushCmd04(int nVal, unsigned __int8 pData); // 0x0042CF60
    int CmdPushCmd05(unsigned __int8 pData); // 0x0042D130
    int CmdPushCmd07(unsigned __int8 pData); // 0x0042D2F0
    int CmdPushCmd10(unsigned __int8 pData); // 0x0042D830
    int CmdPushCmd14(int nVal, unsigned __int8 pData); // 0x0042DF30
    int CmdPushCmd15(unsigned __int8 pData); // 0x0042E100
    char * CmdCameraOrbitPos(int nVal, float fVal, float fVal2, unsigned __int8 pData); // 0x0042E2C0
    int CmdRoleMoveSmooth(int nVal, unsigned __int8 pData); // 0x0042E4D0
    int CmdRoleMoveDirect(unsigned __int8 pData); // 0x0042E6C0
    int ExecuteOpcode(); // 0x0042EBE0
    void ExecuteFrame(float fVal); // 0x0042F460
    char SetBigMapState(char nState); // 0x0042FB40
    void PopScript(); // 0x0042FCC0
    PalScriptMgr(); // 0x00431E60
    void OpenSCE(); // 0x00431EB0
    void FindScript(); // 0x00431EE0
    static void Update(const char *pszName); // 0x004320A0
    void Destroy(); // 0x00432170
    static const char ** _CON_State(const char *pszName); // 0x00432260
    bool IfAnyScriptRunning(int nVal); // 0x004322A0
    int IsScriptRuning(int pal); // 0x004322C0
    void RunSceneScript(const char *pszScene); // 0x004323C0
    void _CON_ReLoadScript(); // 0x00432480
    BOOL _CON_CloseScript(); // 0x004324A0
    static void ClearAllScript(void *pData); // 0x004324B0
    static int * FindScriptByDesc(const char *pszName, const char *desc); // 0x00432500
    void IfHaveScript(); // 0x00432550
    static void NotifyEvent(int nEventID); // 0x00434C40
    static void * UpdateLoadProgress(); // 0x00434C80
    void InitVtable(); // 0x00434CA0
    int ShowTextBox(const char *pszText); // 0x00450BC0
};
