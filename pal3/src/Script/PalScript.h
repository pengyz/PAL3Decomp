#pragma once
// Auto-generated: PalScript

#include "PtrArray.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"

class _PlugInfo;
class scScriptInstance;

class PalScript {
public:
    // vtable (13 methods, order matches binary layout)

    int m_bLoadSceneScript; // +0x0
    scScriptInstance * m_pinst; // +0x4
    PtrArray * m_waitobj; // +0x8
    float m_fBlendFactor; // +0xC
    int m_nState; // +0x10
    int m_nFrameCount; // +0x14
    PtrArray * m_CamObj; // +0x18
    float m_fScriptTimer; // +0x1C
    int m_bEnabled; // +0x20
    BYTE _todo_024; // +0x24
    char _gap_025[3]; // +0x25
    int _todo_028; // +0x28
    int _todo_44; // +0x2C
    int _todo_48; // +0x30
    int _todo_034; // +0x34
    int m_bCreated; // +0x38
    BYTE m_bInitialized; // +0x3C
    char _gap_03D[3]; // +0x3D
    BYTE m_pActorData; // +0x40
    char _gap_041[3]; // +0x41
    float _todo_044; // +0x44
    float _todo_048; // +0x48
    float _todo_04C; // +0x4C
    float _todo_80; // +0x50
    float _todo_054; // +0x54
    int m_RoleArray; // +0x58
    char _gap_05C[36]; // +0x5C
    int m_nTaskIndex; // +0x80
    char _gap_084[4]; // +0x84
    void * m_pTaskData; // +0x88
    void * m_pDialogData; // +0x8C
    void * m_pCurrentTask; // +0x90
    void * m_pTaskPtr; // +0x94
    int m_nTimerCount; // +0x98
    int m_nWaitTimer; // +0x9C
    int m_nAnimState; // +0xA0
    int m_nSnowParticles; // +0xA4
    int m_nItemCheck; // +0xA8
    char _gap_0AC[4]; // +0xAC
    int m_RoleEmoteData; // +0xB0
    char _gap_0B4[16]; // +0xB4
    gbTexture * m_pTexture; // +0xC4
    _PlugInfo * m_pTextureInfo; // +0xC8
    char _gap_0CC[8]; // +0xCC
    int m_RoleEmoteSub; // +0xD4
    int _todo_0D8; // +0xD8
    int m_nRoleCount; // +0xDC
    char _gap_0E0[12]; // +0xE0
    int m_nScriptState; // +0xEC
    BYTE m_bCamActive; // +0xF0
    char _gap_0F1[3]; // +0xF1
    BYTE m_bSoundType; // +0xF4
    char _gap_0F5[3]; // +0xF5
    float m_fCamScale; // +0xF8
    float m_fScaleX; // +0xFC
    int m_nUpdateState; // +0x100
    PtrArray m_WaitObjList; // +0x104
    char _gap_108[12]; // +0x108
    float m_fRenderScaleX; // +0x114
    float m_fScaleY; // +0x118
    float m_fScaleZ; // +0x11C
    char _gap_120[4]; // +0x120
    float m_fInterval; // +0x124
    float m_fElapsed; // +0x128
    char _gap_12C[12]; // +0x12C
    int _todo_138; // +0x138
    char _gap_13C[16]; // +0x13C
    int m_nScriptCount; // +0x14C
    char _gap_150[16]; // +0x150
    int m_EncampConfig; // +0x160
    char _gap_164[12]; // +0x164
    int m_nRepeatCount; // +0x170
    int m_nMaxRepeats; // +0x174
    int m_nCycleCount; // +0x178
    int m_nMaxCycles; // +0x17C
    char _gap_180[12]; // +0x180
    BYTE m_RoleSlotArray; // +0x18C
    BYTE _todo_18D; // +0x18D
    char _gap_18E[34]; // +0x18E
    int _todo_1B0; // +0x1B0
    char _gap_1B4[12]; // +0x1B4
    int m_bRoleAction; // +0x1C0
    char _gap_1C4[16]; // +0x1C4
    BYTE m_RoleActionType; // +0x1D4
    char _gap_1D5[3]; // +0x1D5
    float _todo_1B8; // +0x1D8
    char _gap_1DC[4]; // +0x1DC
    float _todo_01E0; // +0x1E0
    float _todo_1C4; // +0x1E4
    float _todo_1C8; // +0x1E8
    float _todo_1CC; // +0x1EC
    float _todo_1D0; // +0x1F0
    float _todo_1F4; // +0x1F4
    float _todo_1F8; // +0x1F8
    float _todo_1FC; // +0x1FC
    int m_nLoadFromFile; // +0x200
    int m_nLoadState; // +0x204
    int m_nNext; // +0x208
    int m_DialogTemplate; // +0x20C
    int m_nConfigIndex; // +0x210
    int m_SceneConfig; // +0x214
    int m_SceneCfg_flags1; // +0x218
    float m_SceneCfg_fParam0; // +0x21C
    int m_SceneCfg_nParam0; // +0x220
    int m_SceneCfg_nParam1; // +0x224
    int m_SceneCfg_nParam2; // +0x228
    int m_SceneCfg_data; // +0x22C
    float m_fSceneCfg[48]; // +0x230
    char _gap_2F0[28]; // +0x2F0
    short m_nDialogData; // +0x30C
    char _gap_30E[14]; // +0x30E
    int m_nEmoteParam; // +0x31C
    int m_nScreenWidth; // +0x320
    char _gap_324[72]; // +0x324
    int m_EncampSound; // +0x36C
    char _gap_370[92]; // +0x370
    int m_CamFocusData; // +0x3CC
    char _gap_3D0[64]; // +0x3D0
    int m_nDialogResult; // +0x410
    BYTE m_DialogByte; // +0x414
    char _gap_415[83]; // +0x415
    int _todo_468; // +0x468
    char _gap_46C[140]; // +0x46C
    int m_nPathState; // +0x4F8
    int m_nOverlapId; // +0x4FC
    int _todo_500; // +0x500
    char _gap_504[4]; // +0x504
    int _todo_508; // +0x508
    char _gap_50C[4]; // +0x50C
    int _todo_510; // +0x510
    char m_szDialog1[256]; // +0x514
    char m_szDialog2[256]; // +0x614
    BYTE m_DialogSub; // +0x714
    char _tail_715[3]; // +0x715
    // total size: 0x718 (1816)

    virtual ~PalScript() {}

    virtual PalScript * vfunc_0(char a2); // 0x00438190
    virtual void UpdateWaitTimer(float fVal); // 0x00438110
    virtual void * Destroy_28(void *Block, char a2); // 0x00434D50
    virtual void UpdateIdleTimer(float fVal); // 0x004382A0
    virtual int ShowWindow(int nFlags); // 0x00445E70
    virtual int RenderUI(); // 0x0043A270
    virtual BOOL UpdateTimer(int nVal, int nVal2); // 0x0043A3E0
    int MoveAndHide(); // 0x0043A250
    virtual int Create(int id, tagRECT *pRect, int parent); // 0x00445B90
    virtual int OnMessage(int nVal, int nMsg, int wParam); // 0x00445D10
    PalScript * InitParticleSlht(PalScript *pPalScript); // 0x00410840
    int DestroyScript(); // 0x00412680
    void SetAction(int nRoleID); // 0x00421560
    void BindRolesToStage(); // 0x00421CA0
    int * GetCount(int nVal); // 0x00429D10
    void SetIndex(int nVal); // 0x00429D40
    void StopSound3D(); // 0x0042C700
    int LoadScript(int pathAddr); // 0x00430290
    void ReleaseFrame(); // 0x00430500
    char * SetAppName(char *name); // 0x00430570
    int InitScriptObj(int *p_DWORD, unsigned int dwVal, unsigned int dwVal2); // 0x004307D0
    int * EvalExpression(int *p_DWORD, char *pszBuf); // 0x004309D0
    int * GetVarRef(int *pOut, int nIdx); // 0x00431040
    int * EvalExprTree(int *p_DWORD, void *pData, int *p_DWORD2, char *pszBuf); // 0x00431100
    int * ResolveScope(int nVal); // 0x00431390
    int * IteratorNext(); // 0x00431440
    int * IteratorPrev(); // 0x004314A0
    void ConstructStringObj(char *pszBuf); // 0x004314F0
    int SetWaitRange(unsigned int dwVal, unsigned int dwVal2); // 0x00431640
    int CompareBuffer(int nDescriptor); // 0x00431780
    void Cleanup(); // 0x004318A0
    void * LoadFromFile(char *filename); // 0x004318B0
    void FreeLoadBuffer(); // 0x004319C0
    int SetDirectory(char *dir); // 0x004319F0
    int HasNext(); // 0x00431A60
    int LoadNext(); // 0x00431B60
    int SaveLoadState(); // 0x00431C00
    char FindSaveStateString(PalScript *String1, char *String2, char *Destination, int nVal); // 0x00431C10
    void CleanupInstances(); // 0x00431D20
    void PalScript_1d80(); // 0x00431D80
    void AddWaitObj(); // 0x00431F00
    int AddCamObj(); // 0x00431F10
    void ClearAllCamObj(); // 0x00431F40
    void ClearAllWaitObj(); // 0x00431FA0
    void Update(); // 0x00431FB0
    static int ProcessGBKString(); // 0x00433F90
    char * GetString(); // 0x00434C00
    void Op_Idle(); // 0x00434CE0
    void Op_ScriptRunMode(); // 0x00434D70
    void Op_RolePathOut(); // 0x00434D90
    char * Op_RoleScript(); // 0x00434E50
    char * Op_RoleCtrl(); // 0x00434E90
    void Op_RolePathOutToTile(); // 0x00434ED0
    void Op_RolePathTo(); // 0x00434F90
    void Op_TeamCloseA(); // 0x00435010
    void Op_RoleSetPos(); // 0x00435080
    char * Op_RoleOverlap(); // 0x004350F0
    void CmdGetSceneObject(); // 0x00435130
    void Op_GetDislike(); // 0x00435170
    void Op_RoleActive(); // 0x004351A0
    char * Op_RoleScriptInitCam(); // 0x004352D0
    void Op_RoleActiveShort(); // 0x00435320
    void Op_InTeam(); // 0x004353A0
    void Op_RoleSetLayer(); // 0x004353F0
    void Op_RoleOverlapEx(); // 0x00435470
    void Op_RoleCtrlEx(); // 0x004354F0
    void Op_RoleScale(); // 0x00435570
    void Op_CameraPush(); // 0x00435600
    void Op_ShowActAutoStand(); // 0x004356C0
    void Op_RoleMoveBack(); // 0x00435710
    void Op_RoleFaceRole(); // 0x00435720
    void Op_RoleTurnFaceA(); // 0x00435730
    void Op_TeamOpenA(); // 0x00435770
    void Op_CameraPushState(); // 0x004357B0
    void Op_CameraFocusRole(); // 0x004357E0
    void Op_CameraFocusPoint(); // 0x00435830
    void Op_LoseItem(); // 0x00435BF0
    void Op_RoleSpaceWalk(); // 0x004360F0
    void Op_RoleMoveTo(); // 0x00436120
    unsigned int Op_RoleMoveBackEx(); // 0x00436130
    void Op_RoleShowAction(); // 0x00436190
    float * Op_RoleScaleEx(); // 0x00436240
    void Op_RoleEndAction(); // 0x00436280
    void Op_ShowActAutoStandEx(); // 0x004362D0
    void Op_TestGoto(); // 0x00436360
    void Op_Let(); // 0x00436380
    void Op_AddEx(); // 0x004363B0
    void Op_GetSwitch(); // 0x004363E0
    void Op_Call(); // 0x00436410
    void Op_LK_Ghost(); // 0x00436440
    void Op_FavorAdd(); // 0x00436470
    void Op_Team(); // 0x00436490
    void Op_AddRoleAtt(); // 0x004364E0
    void Op_AddItem(); // 0x00436530
    void Op_RoleSetFace(); // 0x004365A0
    void Op_RoleTurnFace(); // 0x004365B0
    char Op_RoleFaceRoleEx(); // 0x004365C0
    char Op_RoleTurnFaceAEx(); // 0x004365D0
    void Op_TeamOpen(); // 0x004365E0
    void Op_TeamClose(); // 0x00436600
    void Op_RoleInput(); // 0x00436680
    void Op_GoTo(); // 0x00436710
    void Op_FCZero(); // 0x00436730
    void Op_Rand(); // 0x00436740
    void Op_FNOT(); // 0x00436760
    void Op_FOP(); // 0x00436780
    void Op_GT(); // 0x004367B0
    void Op_LS(); // 0x004367E0
    void Op_Between(); // 0x00436810
    void Op_EQ(); // 0x00436860
    void Op_NEQ(); // 0x00436890
    void Op_Music(); // 0x004368C0
    void Op_GEQ(); // 0x004368E0
    void Op_LEQ(); // 0x00436910
    void Op_RemoveItem(); // 0x00436940
    void Op_AddMoney(); // 0x004369A0
    void Op_Movie(); // 0x004369C0
    void Op_CEft_Pos(); // 0x00436A10
    void Op_Sub(); // 0x00436A60
    void Op_GetMoney(); // 0x00436AB0
    void Op_TeamCloseAEx(); // 0x00436B40
    void Op_GetHS_Period_type(); // 0x00436BD0
    void Op_HY_Mode(); // 0x00436C00
    void Op_FadeNormal(); // 0x00436C60
    void Op_HY_FLY(); // 0x00436CB0
    void Op_SetRoleTexture(); // 0x00436D30
    void Op_Rotate(); // 0x00436DB0
    void Op_Quake(); // 0x00436E10
    void Op_ShowChatRest(); // 0x00436E70
    void Op_GetHS_UnHock_type(); // 0x00436ED0
    void Op_SetBigMapElement(); // 0x00436F40
    void Op_ObjectMove(); // 0x00436F90
    void Op_KF_Entry(); // 0x00436FB0
    void Op_ENCAMP_Entry(); // 0x00436FE0
    void Op_StopMusic(); // 0x00437010
    void Op_SKEE_Entry(); // 0x00437040
    void Op_Deal(); // 0x00437080
    void Op_APPR_Entry(); // 0x004370C0
    void Op_GetHSLv(); // 0x004370E0
    void Op_SwitchRS(); // 0x00437120
    void Op_GetFavor(); // 0x00437170
    void Op_AddSkill(); // 0x00437190
    void Op_GetFavorite(); // 0x004371B0
    void Op_Note(); // 0x004371D0
    void Op_PlaySound(); // 0x004371F0
    void Op_FullRoleAtt(); // 0x00437210
    void Op_DlgPos(); // 0x00437280
    void Op_FadeOut(); // 0x004373A0
    void Op_FadeIn(); // 0x004373C0
    void Op_DlgFace(); // 0x004373D0
    void Op_DlgFont(); // 0x00437440
    void Op_LoadScene(); // 0x004374A0
    void Op_DlgHead(); // 0x004374E0
    void Op_DlgSel(); // 0x00437500
    void Op_CameraSet(); // 0x00437550
    void Op_CameraWag(); // 0x004375E0
    void Op_CameraMove(); // 0x00437610
    void Op_CameraRotate(); // 0x00437630
    void Op_GetDlgSel(); // 0x00437650
    void Op_CameraTrans(); // 0x004376A0
    void Op_CameraDefault(); // 0x004376F0
    void Op_RoleStop(); // 0x00437740
    void Op_RoleEmote(); // 0x004377F0
    void Op_HaveItem(); // 0x004378E0
    void Op_Climb(); // 0x00437A80
    char * Op_InTeamExecScript(); // 0x00437AC0
    char * Op_RoleSetLayerByObj(); // 0x00437AE0
    void Op_Combat(); // 0x00437B20
    void Op_DlgTime(); // 0x00437B90
    void Op_GetTimeSel(); // 0x00437BB0
    void Op_Get_Appr(); // 0x00437C20
    void Op_Enable_Sword(); // 0x00437C30
    void Op_Enable_JusticeBook(); // 0x00437C40
    void Op_Specify_Compos(); // 0x00437C50
    void Op_Start_Wolf(); // 0x00437FF0
    void Op_Start_HideFight(); // 0x00438030
    void ClearFloatParams(); // 0x004381B0
    void Op_Trigger(); // 0x004381E0
    void Op_JT_Exhibit(); // 0x00438310
    void Op_GetHS_ManageType(); // 0x00438350
    void Op_GetHS_Accrual_type(); // 0x00438390
    void Op_EntryRow(); // 0x00438440
    void Op_RotateInv(); // 0x00438450
    void Op_EntrySkee(); // 0x00438470
    void Op_Dist(); // 0x004384B0
    void Op_CombatNotGameOver(); // 0x004384D0
    static int sub_00438530(); // 0x00438530
    virtual void UpdateFadeOut(float fDelta); // 0x00438540
    void Op_GetCombat(); // 0x004385A0
    virtual void UpdateFadeIn(float fDelta); // 0x00438640
    void Op_RoleFadeOut(); // 0x004386C0
    void Op_RoleFadeIn(); // 0x004387B0
    void Op_TeamOpenAStartMove(); // 0x004387D0
    void Op_ScrEft(); // 0x00438840
    void Op_IfInTeam(); // 0x004388C0
    void ClearIntParams(); // 0x00438910
    void Op_Enable_SwordSkill(); // 0x00438930
    void Op_CEft_Role(); // 0x00438980
    void Op_FogH(); // 0x004389A0
    void Op_Snow(); // 0x004389D0
    void Op_CEft(); // 0x00438A20
    void Op_AverageLv(); // 0x00438A30
    void Op_EntrySmeltSys(); // 0x00438B00
    void Op_Switch2Menu(); // 0x00438B40
    void Op_CEft_Load(); // 0x00438B60
    void Op_GiveCloth(); // 0x00438B80
    void Op_LoadAct(); // 0x00438BA0
    void Op_Rain(); // 0x00438D00
    void Op_WaterMagic(); // 0x00438D20
    void Op_FullTeamAtt(); // 0x00438F10
    void Op_BeeInsertFrame(); // 0x00438F30
    void Op_CameraYaw(); // 0x00438F50
    void PalScript_Init(); // 0x00439130
    void SetReady(); // 0x004391A0
    void ReleaseStateResource(); // 0x004391D0
    gbGeomNode * LoadModel(const char *szFilename, int nActionIdx); // 0x00439230
    char CheckAnimOver(); // 0x004393A0
    void * GetRayToScreen(void *pRay, int *pResult); // 0x00439FE0
    PalScript(); // 0x0043A160
    void ctor(); // 0x0043A1F0
    gbVFileSystem * OpenScript(const char *pszName, char pData); // 0x0043AA00
    int * OffsetRect(int *p_DWORD); // 0x00445E10
    LPSTR SetDialogTemplate(CHAR *String1, CHAR *lpString2); // 0x0044B8A0
    void FreeScriptBuffers(); // 0x004573A0
    int InitMainUIScripts(); // 0x00487B60
    char LoadSceneConfig(char *filename); // 0x00522130
    int LoadResource(char *filename); // 0x00529440
    int LoadEncampConfig(); // 0x0052BE40
    int ResetAll(); // 0x00535010
    struct gbVFileSystem * LoadVisNode(double String2, char *pszBuf, char *pszBuf2); // 0x00535710
    void DestroyInstances(double nActionID, int *p_DWORD); // 0x00538D60
};
