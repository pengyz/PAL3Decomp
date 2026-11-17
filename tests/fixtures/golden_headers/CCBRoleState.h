class UIWnd;

class tagRECT;

class CCBUI;

#pragma once
// Auto-generated: CCBRoleState
#include "pal3/ida_types.h"

#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/tagRoleState.h"

class CCBStage;
class CCBSystem;
class CCBUI;
class CUtil;
class SceneObj;
class UIScene;
class tagCmdData;

class CCBRoleState : public UIListBox {
public:
    char _gap_048[4]; // +0x48
    int m_nState_04C; // +0x4C
    char _gap_050[16]; // +0x50
    int m_nState_060; // +0x60
    int m_nCombatResult; // +0x64
    char _gap_068[28]; // +0x68
    int m_nState[4]; // +0x84
    int m_nTargetRoleIdx; // +0x94
    char _gap_098[4]; // +0x98
    int m_nSelectedAction; // +0x9C
    int m_nSelectedTarget; // +0xA0
    int m_nSelectedItem; // +0xA4
    int m_nState2[26]; // +0xA8
    char _gap_110[8]; // +0x110
    int m_nDamageThisRound; // +0x118
    char _gap_11C[4]; // +0x11C
    int m_nState3[18]; // +0x120
    UIFrameWnd m_nTodo_168; // +0x168
    char _gap_1B0[80]; // +0x1B0
    float m_fLastDialogTime; // +0x200
    BYTE m_bCombatDialog; // +0x204
    char _gap_205[3]; // +0x205
    CCBSystem * m_pCBSystem; // +0x208
    CCBStage * m_pStage; // +0x20C
    CCBUI * m_pUI; // +0x210
    CUtil * m_pUtil; // +0x214
    BYTE m_bWeSneakAttackEnemy; // +0x218
    BYTE m_bEnemySneakAttackUs; // +0x219
    char _gap_21A[2]; // +0x21A
    int m_nMaxRound; // +0x21C
    int m_nBossRound; // +0x220
    BYTE m_bMustFail; // +0x224
    BYTE m_bFleeAlwaysSuccess; // +0x225
    BYTE m_bCreatedNewRole; // +0x226
    char _gap_227[1]; // +0x227
    tagRoleState m_Role[11]; // +0x228
    char _gap_1BF0[524]; // +0x1BF0
    BYTE m_byteFlags; // +0x1DFC
    char _gap_1DFD[2675]; // +0x1DFD
    BYTE m_nTodo_2870; // +0x2870
    char _gap_2871[11]; // +0x2871
    char m_BufferData[1628]; // +0x287C
    tagRoleState m_RoleXor[11]; // +0x2ED8
    char _gap_48A0[24]; // +0x48A0
    UIWnd m_SlotUIWnd; // +0x48B8
    char _gap_48FC[16]; // +0x48FC
    float m_fLerpCurX; // +0x490C
    float m_fLerpCurY; // +0x4910
    int m_nLerpTargetX; // +0x4914
    int m_nLerpTargetY; // +0x4918
    int m_nLerpDestX; // +0x491C
    int m_nLerpDestY; // +0x4920
    char _gap_4924[8]; // +0x4924
    int m_nLerpDir; // +0x492C
    char _gap_4930[9]; // +0x4930
    BYTE m_bLerpDone; // +0x4939
    char _gap_493A[2]; // +0x493A
    float m_fLerpSpeed; // +0x493C
    char _gap_4940[28]; // +0x4940
    float m_fSpringPosX; // +0x495C
    float m_fSpringPosY; // +0x4960
    float m_fSpringTargX; // +0x4964
    float m_fSpringTargY; // +0x4968
    float m_fSpringPrevX; // +0x496C
    float m_fSpringPrevY; // +0x4970
    int m_nSpringTargetX; // +0x4974
    int m_nSpringTargetY; // +0x4978
    int m_nSpringDir; // +0x497C
    float m_fSpringAccelX; // +0x4980
    float m_fSpringAccelY; // +0x4984
    BYTE m_bSpringDoneX; // +0x4988
    BYTE m_bSpringDoneY; // +0x4989
    char _gap_498A[2]; // +0x498A
    float m_fSpringSpeed; // +0x498C
    char _gap_4990[224]; // +0x4990
    UIWnd m_SlotWidgets; // +0x4A70
    char _gap_4AB4[540]; // +0x4AB4
    int m_SlotRects; // +0x4CD0
    char _gap_4CD4[160]; // +0x4CD4
    int m_SlotRightEdge; // +0x4D74
    char _gap_4D78[64]; // +0x4D78
    int m_nSlotStartY; // +0x4DB8
    int m_nSlotSpacing; // +0x4DBC
    int m_nSlotHeight; // +0x4DC0
    int m_nSlotWidth; // +0x4DC4
    BYTE m_bySlotVisible; // +0x4DC8
    char _gap_4DC9[151]; // +0x4DC9
    UIScene * m_pScene; // +0x4E60
    char _gap_4E64[340]; // +0x4E64
    UIStatic m_Static_20408; // +0x4FB8
    BYTE m_bVideoPlayed; // +0x5050
    char _gap_5051[3]; // +0x5051
    int m_nVideoState; // +0x5054
    char _gap_5058[8]; // +0x5058
    int m_nCurrentTaskID; // +0x5060
    int m_nEffCurA; // +0x5064
    int m_nEffCurB; // +0x5068
    char _gap_506C[4]; // +0x506C
    int m_nEffTarget1; // +0x5070
    int m_nEffTarget2; // +0x5074
    int m_nEffTransFrames; // +0x5078
    int m_nEffSwapA; // +0x507C
    int m_nEffSwapB; // +0x5080
    char _gap_5084[4]; // +0x5084
    int m_nEffCurC; // +0x5088
    int m_nEffSwapC; // +0x508C
    int m_nEffCurD; // +0x5090
    int m_nEffTransFrames2; // +0x5094
    int m_nEffCurE; // +0x5098
    int m_nEffSwapE; // +0x509C
    float m_fTimeFund; // +0x50A0
    char _gap_50A4[1316]; // +0x50A4
    BYTE m_bScrollEnableA; // +0x55C8
    BYTE m_bScrollEnableB; // +0x55C9
    char _gap_55CA[2]; // +0x55CA
    int m_nScrollOffset; // +0x55CC
    int m_nScrollTarget; // +0x55D0
    char _gap_55D4[128]; // +0x55D4
    int m_nFadeFlags; // +0x5654
    int m_nFadeAlpha; // +0x5658
    int m_nFadeTimer; // +0x565C
    char _gap_5660[108]; // +0x5660
    int m_BattleFlags; // +0x56CC
    // total size: 0x56D0 (22224)

    virtual ~CCBRoleState() {}

    virtual void ShowClipped(int nVal); // slot0 0x00445e70
    virtual void Render(); // slot1 0x00524970
    virtual BOOL Update(CCBUI **deltatime); // slot2 0x00457020
    virtual void HideAll(); // slot3 0x0043de40
    virtual int Create(int id, tagRECT *, UIWnd * parent); // slot4 0x00445b90
    virtual int OnMessage(int a2, unsigned int nVal, int nVal2); // slot6 0x00457070

    virtual void * _sdtor_call_dtor(UIWnd *Block, char pData); // 0x00456b60
    char HandleInput(void *thisa, unsigned int a2, int a3); // 0x004499a0
    __int64 CalcSpringForce(int nVal, int nVal2); // 0x00449f00
    int UpdateSpringAnim(float fDelta); // 0x00449fe0
    void UpdateFadeAlpha(); // 0x0044a2e0
    int InitFadeAndSpring(); // 0x0044a3d0
    CCBRoleState(); // 0x00456ab0
    int LayoutSlotPanelA(unsigned __int8 pData); // 0x0046d770
    int LayoutSlotPanelB(unsigned __int8 pData); // 0x0046d890
    int LayoutSlotPanelC(unsigned __int8 pData); // 0x0046d9b0
    int LayoutSlotPanelD(unsigned __int8 pData); // 0x0046dad0
    int LayoutSlotPanelE(unsigned __int8 pData); // 0x0046dbf0
    int NotifyStateChange(unsigned __int8 nState); // 0x0046f390
    int Init_3360(CHAR *thisa, int a2, int *a3); // 0x004a3360
    int UpdatePanel(BOOL bRefresh); // 0x004dc250
    BOOL IsRoleShelved(int nVal1); // 0x004dc720
    char GetCombatDialogPos(int *p_DWORD, int *p_DWORD2, int *p_DWORD3); // 0x004dc760
    void InitCombatDialog(); // 0x004dc7a0
    int HandleItemMenu(int nState); // 0x004dcd00
    int HandleMagicMenu(int nState); // 0x004dcf80
    int HandleTargetMenu(int nState); // 0x004dd300
    int StartLineupPhase(int nVal); // 0x004dd650
    int EndRoundTasks(int B4); // 0x004ddc90
    int InitSelectionUI(int nVal); // 0x004de8c0
    int DispatchCombatAction(int nVal); // 0x004dee80
    int ExecuteCombatCommand(int nVal); // 0x004df2f0
    int GetActionPriority(int nVal); // 0x004df370
    char CheckSelfMP(); // 0x004df3d0
    int ResetDialogSlots(); // 0x004df6d0
    int CombatDialogProc(int nVal, HWND hDlg, unsigned int uMsg, int wParam, int lParam); // 0x004e1a40
    LRESULT UpdateDebugTreeView(); // 0x004e28f0
    LRESULT HandleDlgMessage(); // 0x004e2c10
    unsigned __int8 SyncRoleUIData(); // 0x004e30e0
    LRESULT UpdateDebugDialog(); // 0x004e40b0
    char ApplyDebugEdits(); // 0x004e4570
    static int GetTargetCommand(); // 0x004e5110
    CCBRoleState * ClearAndSetGP(int nVal); // 0x004ec680
    int ClearRoleMemory(); // 0x004ec6b0
    char IterateMagicSlots(); // 0x004ec7d0
    char DestroyAndReinit(); // 0x004ec830
    int SetupCombatLayout(); // 0x004ec910
    int ProcessState(); // 0x004ecb00
    char ProcessCombatAction(int roleIdx); // 0x004ecb20
    char IsRoleAlive(int roleIdx); // 0x004ed010
    char IsActive(int index); // 0x004ed040
    char GetRoleType(int roleIdx); // 0x004ed060
    char ApplyHitEffect(char pData); // 0x004ed0a0
    int GetForce(int roleIdx); // 0x004ed100
    char ShuffleSlots(); // 0x004ed170
    static int LoadPartyData(); // 0x004ed250
    char SavePartyData(); // 0x004ed680
    char * UpdateDefenceStats(); // 0x004ed800
    char SyncSkillCent(); // 0x004ed870
    int RollInitiative(); // 0x004edc60
    void InitSelfAtt(); // 0x004edd60
    char UpdateRolePositions(); // 0x004edf10
    char * Reset(int nVal, char *pszBuf); // 0x004ee430
    bool Destroy(); // 0x004ee760
    bool Init(int nVal, char pData); // 0x004ee7c0
    tagRoleState * InitUI(int nVal); // 0x004ee870
    int UpdateRoleMP(int roleIdx); // 0x004ee890
    int CheckRoleMP(int roleIdx); // 0x004ee910
    bool VarianceRoundCounter(int *nRoleIndex); // 0x004ee990
    void CheckVarianceRound(int nRoleIndex, int nVal, int *pnVal); // 0x004eea70
    void CancelVariance(int *nRoleIndex, unsigned int dwVal); // 0x004eecb0
    char ForceRoleTaskByCond(int roleIdx); // 0x004eed60
    char IsAlive(int nIndex, int nVal); // 0x004eee60
    int CalcCombatDamage(const void *pData, unsigned int roleIdx); // 0x004eef20
    void IsBoss(int *arg0, unsigned int nRoleIndex); // 0x004ef4a0
    bool IsAllWeDead(int bCheckHP); // 0x004ef6a0
    int * IsAllEnemyDead(int bCheckHP, int *pnVal, int *pnVal2); // 0x004ef6c0
    bool CanAction(int nIndex, int nVal, int nVal2); // 0x004ef710
    void SetCanAction(unsigned int dmg, int roleIdx, int nVal); // 0x004ef7e0
    void RandSetEnemyPos(const void *arg0); // 0x004ef8b0
    int CalcHealAmount(int roleIdx); // 0x004ef980
    void WriteBackRoleData(int nVal, int *p_DWORD, int *pnVal); // 0x004efaf0
    bool WriteBackConfig(int roleIdx, int nVal); // 0x004efd70
    bool ReviveAllFriendAtEnd(int roleIdx, int nVal); // 0x004efe90
    bool IsRoleReady(int roleIdx); // 0x004effc0
    void SetEnemyBeImbibeNimbus(char pData, char pData2); // 0x004f0020
    bool CalSneakAttack(int nVal, unsigned int dwVal); // 0x004f0210
    unsigned int InitRoleFiveMagic(int nVal); // 0x004f0360
    char IsAllyTargetCmd(int *p_DWORD); // 0x004f05a0
    void InitRoleSpecEquipAttrib(int nRoleIndex); // 0x004f0640
    void UnloadWeaponModel(int nVal); // 0x004f0700
    bool SetVisible(); // 0x004f0750
    char IsRoleIndexEqual(int nIndex, int nVal); // 0x004f07d0
    unsigned __int8 GetRoleNum(int *pnVal); // 0x004f0830
    char CalcCombatDamage_0a10(int nVal); // 0x004f0a10
    char GetAliveRoleNumInForce(struct tagCmdData *force); // 0x004f1070
    char GetDeadRoleNumInForce(int *force); // 0x004f1420
    char GetFirstAliveRoleInForce(int roleIdx, int arg4); // 0x004f17c0
    bool GetCastFightSkillSuccess(int pCmd); // 0x004f1a30
    void SetCoAttack(unsigned int dwCoAttackID); // 0x004f1b20
    bool CanBeImbibeNimbus(int dmg, unsigned int nRoleIndex); // 0x004f1cc0
    bool CheckRoleValid(int nRoleIndex, unsigned int roleIdx, int nVal); // 0x004f1fa0
    char CheckRoleNimbus(int nRoleIndex, unsigned int dwVal); // 0x004f2310
    bool CanBeSelect(tagCmdData *pCmd, unsigned int nDestRole); // 0x004f2350
    char CheckRoundComplete(); // 0x004f2390
    char ValidateSlotIndex(unsigned int arg0, unsigned int dwVal); // 0x004f2560
    int CheckTargetCombo(struct tagCmdData *p, unsigned int roleIdx); // 0x004f2660
    int CheckBoss(int *arg0, int roleIdx); // 0x004f2690
    int GetV4(int *arg0, unsigned int roleIdx); // 0x004f27b0
    int CalcComboDirect(const void *pData, unsigned int roleIdx); // 0x004f27e0
    int ApplyItemEffect(int nCmdData, int nParam); // 0x004f2800
    int SetRoleHP(int roleIdx, int value); // 0x004f2910
    int SetRoleField(int roleIdx, int value); // 0x004f2bb0
    int GetRoleGPBak(int nVal, char pData); // 0x004f2bf0
    void * GetRole(int index); // 0x004f2c30
    int AddCommand(int nCmdType, BOOL bImmediate, int nParam); // 0x004f2c70
    int CalcAttackPower(int roleIdx); // 0x004f3020
    int CalcDefensePower(int roleIdx); // 0x004f31c0
    int GetMaxHP(int roleIdx); // 0x004f3380
    int GetMaxMP(int roleIdx); // 0x004f33d0
    int GetTotalRounds(); // 0x004f3420
    char CheckBuff(int roleIdx); // 0x004f3430
    char CanUseSkill(int roleIdx); // 0x004f34e0
    int CalcMagicAttack(int roleIdx); // 0x004f3570
    int CalcMPRegen(int roleIdx); // 0x004f3620
    int CalcMagicDefense(int roleIdx); // 0x004f36d0
    int GetAttackBonus(int roleIdx); // 0x004f37a0
    int GetDefenseBonus(int roleIdx); // 0x004f3820
    int GetRoleState(int roleIdx); // 0x004f38a0
    int GetSpeedBonus(int roleIdx); // 0x004f3920
    int GetRoleLevel(int roleIdx); // 0x004f39a0
    int GetRoleExp(int roleIdx); // 0x004f39f0
    char SetRoleFlag(int roleIdx, char flag); // 0x004f3a30
    int GetRoleAttr(int roleIdx); // 0x004f3a50
    int CalcMPCost(int roleIdx); // 0x004f3ad0
    int GetRoleMP(int roleIdx); // 0x004f3b90
    int GetRoleHP(int roleIdx); // 0x004f3bc0
    int IsForce1(int force); // 0x004f3c00
    char IsPlayerTeam(int force); // 0x004f3c20
    char GetRoleForce(int roleIdx); // 0x004f3c70
    bool IsRoleInForce(int roleIdx); // 0x004f3cc0
    char CanRoleAct(int roleIdx); // 0x004f3d10
    char GetRoleField(int roleIdx, int fieldOff); // 0x004f3d90
    int FindFirstEnemySlot(int roleIdx); // 0x004f3dc0
    char * ProcessRound(unsigned int dwVal, int force, int a4, int a5); // 0x004f3e20
    void TickDebuffs(int roleIdx); // 0x004f48c0
    unsigned int CalcSpellDamage(int roleIdx, int nMagicID); // 0x004f4b90
    unsigned int CalcSkillDamage(int roleIdx, int nSkillID); // 0x004f4c80
    int ProcessAttackResult(int roleIdx); // 0x004f4da0
    int ProcessMagicResult(int roleIdx); // 0x004f5070
    int AISelectItem(int roleIdx, char pData); // 0x004f5330
    int CalcPhysicalDamage(int roleIdx); // 0x004f55d0
    int CalcMagicDamage(int roleIdx); // 0x004f57a0
    int ProcessSkillEffect(int roleIdx); // 0x004f5970
    int ProcessItemEffect(int roleIdx); // 0x004f5b70
    int AISelectMagic(unsigned int roleIdx, char pData, int nVal); // 0x004f5d00
    int AISelectHealItem(unsigned int roleIdx, char pData, int nVal); // 0x004f6000
    int AISelectTarget(unsigned int roleIdx, char pData, int nVal); // 0x004f61d0
    int AISelectSkill(unsigned int roleIdx, int nVal, char pData); // 0x004f6370
    int AISelectItemForSkill(unsigned int roleIdx, int nSkillID, char pData); // 0x004f6690
    int AISelectSkillTarget(unsigned int roleIdx, int nSkillID, char pData); // 0x004f6860
    char ValidateCommandTarget(int *pCmd); // 0x004f6da0
    char CheckEventCondition(int pEvent); // 0x004f7200
    char CheckMagicCost(int *p_DWORD); // 0x004f7480
    char GetRoleAI(void *pOut); // 0x004f7500
    int GetSkillCostLevel(unsigned int dwSlot, int nSkillID); // 0x004f76c0
    char SumGPCost(int nVal); // 0x004f7820
    unsigned int CheckStatus(); // 0x004f7880
    void * ProcessActions(); // 0x004f7910
    void ProcessCombatDialog(unsigned int dwVal); // 0x004f7fc0
    int UpdateEffects(); // 0x004f8480
    void ProcessControlInput(); // 0x004f8af0
    int InitSlot(int idx, int nRoleID); // 0x004f8bb0
    char LoadRoleModel(int nVal); // 0x004f8fa0
    char SpawnRandomEnemies(int nVal, int nVal2); // 0x004f8fd0
    char * CheckRoleCanAct(int roleIdx); // 0x004f90f0
    char * PopulateItemList(int nSlot); // 0x004f91b0
    int GetDialogSlot(int nVal, int nVal2); // 0x004f9340
    unsigned int PopulateMagicList(int nSlot); // 0x004f9390
    int GetMagicSlotData(int nVal, int nVal2, int nVal3); // 0x004f9590
    int PopulateTargetList(int nSlot, int nType); // 0x004f95f0
    int UpdateCommandButtons(int nSlot); // 0x004f9790
    int ApplyDamage(int roleIdx, int dmg); // 0x004f98b0
    int GetSlotState(int nVal, int nVal2); // 0x004fa210
    int CalcSpeedByLevel(int nRole, int nLevel); // 0x004fa280
    int GetActionTypeBySlot(int nVal, int nVal2); // 0x004fa330
    int CalcDefenseByLevel(int nRole, int nLevel); // 0x004fa3a0
    int CalcDamage(int nVal, int nVal2); // 0x004fa440
    int FindSlotByHP(unsigned int nVal, unsigned int dwVal); // 0x004fa4e0
    int GetRoleCount(int nVal); // 0x004fa510
    int CheckRoleStatus(int roleIdx); // 0x004fa540
    int GetSlotActionType(int nVal, char *Buffer); // 0x004fa560
    int FindRoleByID(int nVal); // 0x004fa5f0
    int CountValidSlots(int nVal, int nVal2, int *p_DWORD, int *pnVal); // 0x004fa620
    int CheckDeath(int roleIdx); // 0x004fa6a0
    int GetSlotType(int nVal); // 0x004fa700
    int SwapEffectParams(int nVal); // 0x004fa760
    int Revive(int roleIdx); // 0x004fa8b0
    char UpdateRoleMP_a930(char arg0, int nVal); // 0x004fa930
    int CheckMPRequirement(int nVal); // 0x004fb370
    int RandomizeSpecialSkill(int nSkillId); // 0x004fb6b0
    int CCBRoleState_Func(int nVal); // 0x00502000
    int CalcTurnDelay(int nVal); // 0x005020d0
    int FadeMusicIn(int nVal); // 0x005021c0
    int FadeMusicOut(int nVal); // 0x00502300
    int GetCombatDialogEntry(int nVal); // 0x00502430
    int FormatSkillResultText(int nVal); // 0x005025c0
    int FormatAttackResultText(int nVal); // 0x005027e0
    int FormatItemResultText(int nVal); // 0x00502950
    int FormatMagicResultText(int nVal); // 0x00502cc0
    int GetRoleMPValue(int nVal, int nVal2, int nVal3); // 0x00503ae0
    SceneObj * Destructor(int nVal1); // 0x005362f0
    int CleanupInternal(); // 0x005363c0
    BOOL HandleEvent(int nVal, int nVal2); // 0x005368a0
};
