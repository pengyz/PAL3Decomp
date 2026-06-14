#pragma once
// Auto-generated: CCBRoleState

#include "UIFrameWnd.h"
#include "UIScene.h"
#include "UIStatic.h"
#include "UIWnd.h"
#include "tagRoleState.h"

class CCBStage;
class CCBSystem;
class CCBUI;
class CUtil;
class UIListBox;
class tagCmdData;

class CCBRoleState {
public:
    // vtable (7 methods, order matches binary layout)

    char m_sCombatDialog[4]; // +0x0
    UIFrameWnd _embed_UIFrameWnd_168; // +0x4
    char _gap_008[68]; // +0x8
    float m_fLastDialogTime; // +0x4C
    BYTE m_bCombatDialog; // +0x50
    char _gap_051[3]; // +0x51
    CCBSystem * m_pCBSystem; // +0x54
    CCBStage * m_pStage; // +0x58
    CCBUI * m_pUI; // +0x5C
    CUtil * m_pUtil; // +0x60
    BYTE m_bWeSneakAttackEnemy; // +0x64
    BYTE m_bEnemySneakAttackUs; // +0x65
    char _gap_066[2]; // +0x66
    int m_nMaxRound; // +0x68
    int m_nBossRound; // +0x6C
    BYTE m_bMustFail; // +0x70
    BYTE m_bFleeAlwaysSuccess; // +0x71
    BYTE m_bCreatedNewRole; // +0x72
    tagRoleState m_Role[11]; // +0x73
    char _gap_09F[6556]; // +0x9F
    BYTE m_byteFlags; // +0x1A3B
    BYTE m_bFlag2870; // +0x1A3C
    char m_BufferData[9812]; // +0x1A3D
    tagRoleState m_RoleXor[11]; // +0x4091
    char _gap_40BD[6556]; // +0x40BD
    UIWnd m_SlotUIWnd; // +0x5A59
    char _gap_5A5D[67]; // +0x5A5D
    float m_fLerpCurX; // +0x5AA0
    float m_fLerpCurY; // +0x5AA4
    int m_nLerpTargetX; // +0x5AA8
    int m_nLerpTargetY; // +0x5AAC
    int m_nLerpDestX; // +0x5AB0
    int m_nLerpDestY; // +0x5AB4
    int m_nLerpDir; // +0x5AB8
    BYTE m_bLerpDone; // +0x5ABC
    char _gap_5ABD[3]; // +0x5ABD
    float m_fLerpSpeed; // +0x5AC0
    float m_fSpringPosX; // +0x5AC4
    float m_fSpringPosY; // +0x5AC8
    float m_fSpringTargX; // +0x5ACC
    float m_fSpringTargY; // +0x5AD0
    float m_fSpringPrevX; // +0x5AD4
    float m_fSpringPrevY; // +0x5AD8
    int m_nSpringDir; // +0x5ADC
    float m_fSpringAccelX; // +0x5AE0
    float m_fSpringAccelY; // +0x5AE4
    BYTE m_bSpringDoneX; // +0x5AE8
    BYTE m_bSpringDoneY; // +0x5AE9
    char _gap_5AEA[2]; // +0x5AEA
    float m_fSpringSpeed; // +0x5AEC
    UIWnd m_SlotWidgets; // +0x5AF0
    char _gap_5AF4[64]; // +0x5AF4
    int m_SlotRects; // +0x5B34
    int m_SlotRightEdge; // +0x5B38
    int m_nSlotStartY; // +0x5B3C
    int m_nSlotSpacing; // +0x5B40
    int m_nSlotHeight; // +0x5B44
    int m_nSlotWidth; // +0x5B48
    BYTE m_bySlotVisible; // +0x5B4C
    UIScene m_Scene_20064; // +0x5B4D
    char _gap_5B51[340]; // +0x5B51
    UIStatic m_Static_20408; // +0x5CA5
    char _gap_5CA9[148]; // +0x5CA9
    BYTE m_bVideoPlayed; // +0x5D3D
    char _gap_5D3E[2]; // +0x5D3E
    int m_nVideoState; // +0x5D40
    int m_nCurrentTaskID; // +0x5D44
    int m_nEffCurA; // +0x5D48
    int m_nEffCurB; // +0x5D4C
    int m_nEffTarget1; // +0x5D50
    int m_nEffTarget2; // +0x5D54
    int m_nEffTransFrames; // +0x5D58
    int m_nEffSwapA; // +0x5D5C
    int m_nEffSwapB; // +0x5D60
    int m_nEffCurC; // +0x5D64
    int m_nEffSwapC; // +0x5D68
    int m_nEffCurD; // +0x5D6C
    int m_nEffTransFrames2; // +0x5D70
    int m_nEffCurE; // +0x5D74
    int m_nEffSwapE; // +0x5D78
    float m_fTimeFund; // +0x5D7C
    BYTE m_bScrollEnableA; // +0x5D80
    BYTE m_bScrollEnableB; // +0x5D81
    char _gap_5D82[2]; // +0x5D82
    int m_nScrollOffset; // +0x5D84
    int m_nScrollTarget; // +0x5D88
    int m_nFadeFlags; // +0x5D8C
    int m_nFadeAlpha; // +0x5D90
    int m_nFadeTimer; // +0x5D94
    int m_BattleFlags; // +0x5D98
    // total size: 0x5D9C (23964)

    virtual ~CCBRoleState() {}

    virtual void Render(UIListBox *thisa, const char *a3, struct tagRECT *a4, int a5, int a6, bool a7); // 0x00524970
    virtual BOOL PlayVideoIfReady(int nVal, int nVal2); // 0x00457020
    virtual void Destroy(UIListBox *thisa, int a2); // 0x0043DE40
    virtual int ctor(int nVal, int nVal2, int nVal3); // 0x00457070
    __int64 CalcSpringForce(int nVal, int nVal2); // 0x00449F00
    int UpdateSpringAnim(float fDelta); // 0x00449FE0
    void UpdateFadeAlpha(); // 0x0044A2E0
    int InitFadeAndSpring(); // 0x0044A3D0
    int ctor(); // 0x00456AB0
    void ctor_6B80(); // 0x00456B80
    void _CCBRoleState(); // 0x00456C20
    int LayoutSlotPanelA(unsigned __int8 pData); // 0x0046D770
    int LayoutSlotPanelB(unsigned __int8 pData); // 0x0046D890
    int LayoutSlotPanelC(unsigned __int8 pData); // 0x0046D9B0
    int LayoutSlotPanelD(unsigned __int8 pData); // 0x0046DAD0
    int LayoutSlotPanelE(unsigned __int8 pData); // 0x0046DBF0
    int NotifyStateChange(unsigned __int8 nState); // 0x0046F390
    BOOL IsAlive(); // 0x004DC720
    char GetCombatDialogPos(int *p_DWORD, int *p_DWORD2, int *p_DWORD3); // 0x004DC760
    void InitCombatDialog(); // 0x004DC7A0
    int HandleItemMenu(int nState); // 0x004DCD00
    int HandleMagicMenu(int nState); // 0x004DCF80
    int HandleTargetMenu(int nState); // 0x004DD300
    int StartLineupPhase(int nVal); // 0x004DD650
    int EndRoundTasks(int B4); // 0x004DDC90
    int InitSelectionUI(int nVal); // 0x004DE8C0
    int DispatchCombatAction(int nVal); // 0x004DEE80
    int ExecuteCombatCommand(int nVal); // 0x004DF2F0
    int GetActionPriority(int nVal); // 0x004DF370
    char CheckMP(); // 0x004DF3D0
    int ResetDialogSlots(); // 0x004DF6D0
    int CombatDialogProc(int nVal, HWND hDlg, unsigned int uMsg, int wParam, int lParam); // 0x004E1A40
    LRESULT UpdateDebugTreeView(); // 0x004E28F0
    LRESULT HandleDlgMessage(); // 0x004E2C10
    unsigned __int8 SyncRoleUIData(); // 0x004E30E0
    LRESULT UpdateDebugDialog(); // 0x004E40B0
    char ApplyDebugEdits(); // 0x004E4570
    static int GetTargetCommand(); // 0x004E5110
    CCBRoleState * ClearAndSetGP(int nVal); // 0x004EC680
    int ClearRoleMemory(); // 0x004EC6B0
    char IterateMagicSlots(); // 0x004EC7D0
    char DestroyAndReinit(); // 0x004EC830
    int SetupCombatLayout(); // 0x004EC910
    int Update(); // 0x004ECB00
    char ProcessCombatAction(int roleIdx); // 0x004ECB20
    char IsRoleAlive(int roleIdx); // 0x004ED010
    char IsActive(int index); // 0x004ED040
    char GetRoleType(int roleIdx); // 0x004ED060
    char ApplyHitEffect(char pData); // 0x004ED0A0
    int GetForce(int roleIdx); // 0x004ED100
    char ShuffleSlots(); // 0x004ED170
    int LoadPartyData(); // 0x004ED250
    char SavePartyData(); // 0x004ED680
    char * UpdateDefenceStats(); // 0x004ED800
    char SyncSkillCent(); // 0x004ED870
    int RollInitiative(); // 0x004EDC60
    CCBRoleState(); // 0x004EDD60
    char UpdateRolePositions(); // 0x004EDF10
    char * Reset(int nVal, char *pszBuf); // 0x004EE430
    bool Create(); // 0x004EE540
    bool Destroy(); // 0x004EE760
    bool Init(int nVal, char pData); // 0x004EE7C0
    tagRoleState * InitUI(int nVal); // 0x004EE870
    int Update(int roleIdx); // 0x004EE890
    int CheckMP(int roleIdx); // 0x004EE910
    bool VarianceRoundCounter(int *nRoleIndex); // 0x004EE990
    void CheckVarianceRound(int nRoleIndex, int nVal, int *pnVal); // 0x004EEA70
    void CancelVariance(int *nRoleIndex, unsigned int dwVal); // 0x004EECB0
    char ForceRoleTaskByCond(int roleIdx); // 0x004EED60
    char IsAlive(int nIndex, int nVal); // 0x004EEE60
    int CalcCombatDamage(const void *pData, unsigned int roleIdx); // 0x004EEF20
    void IsBoss(int *arg0, unsigned int nRoleIndex); // 0x004EF4A0
    bool IsAllWeDead(int bCheckHP); // 0x004EF6A0
    int * IsAllEnemyDead(int bCheckHP, int *pnVal, int *pnVal2); // 0x004EF6C0
    bool CanAction(int nIndex, int nVal, int nVal2); // 0x004EF710
    void SetCanAction(unsigned int dmg, int roleIdx, int nVal); // 0x004EF7E0
    void RandSetEnemyPos(const void *arg0); // 0x004EF8B0
    int CalcHealAmount(int roleIdx); // 0x004EF980
    void WriteBackRoleData(int nVal, int *p_DWORD, int *pnVal); // 0x004EFAF0
    bool WriteBackConfig(int roleIdx, int nVal); // 0x004EFD70
    bool ReviveAllFriendAtEnd(int roleIdx, int nVal); // 0x004EFE90
    bool IsRoleReady(int roleIdx); // 0x004EFFC0
    void SetEnemyBeImbibeNimbus(char pData, char pData2); // 0x004F0020
    bool CalSneakAttack(int nVal, unsigned int dwVal); // 0x004F0210
    unsigned int InitRoleFiveMagic(int nVal); // 0x004F0360
    char IsAllyTargetCmd(int *p_DWORD); // 0x004F05A0
    void InitRoleSpecEquipAttrib(int nRoleIndex); // 0x004F0640
    void UnloadWeaponModel(int nVal); // 0x004F0700
    bool SetVisible(int roleIdx, int a3); // 0x004F0750
    char GetRole(int nIndex, int nVal); // 0x004F07D0
    unsigned __int8 GetRoleNum(int *pnVal); // 0x004F0830
    char CalcCombatDamage(int nVal); // 0x004F0A10
    char GetAliveRoleNumInForce(struct tagCmdData *force); // 0x004F1070
    char GetDeadRoleNumInForce(int *force); // 0x004F1420
    char GetFirstAliveRoleInForce(int roleIdx, int arg4); // 0x004F17C0
    bool GetCastFightSkillSuccess(int pCmd); // 0x004F1A30
    void SetCoAttack(unsigned int dwCoAttackID); // 0x004F1B20
    bool CanBeImbibeNimbus(int dmg, unsigned int nRoleIndex); // 0x004F1CC0
    bool CheckRoleValid(int nRoleIndex, unsigned int roleIdx, int nVal); // 0x004F1FA0
    char CheckRoleNimbus(int nRoleIndex, unsigned int dwVal); // 0x004F2310
    bool CanBeSelect(tagCmdData *pCmd, unsigned int nDestRole); // 0x004F2350
    char CheckRoundComplete(); // 0x004F2390
    char ValidateSlotIndex(unsigned int arg0, unsigned int dwVal); // 0x004F2560
    int CheckTargetCombo(struct tagCmdData *p, unsigned int roleIdx); // 0x004F2660
    int CheckBoss(int *arg0, int roleIdx); // 0x004F2690
    int GetV4(int *arg0, unsigned int roleIdx); // 0x004F27B0
    int CalcComboDirect(const void *pData, unsigned int roleIdx); // 0x004F27E0
    int ApplyItemEffect(int nCmdData, int nParam); // 0x004F2800
    int SetRoleHP(int roleIdx, int value); // 0x004F2910
    int SetRoleField(int roleIdx, int value); // 0x004F2BB0
    int GetRoleGPBak(int nVal, char pData); // 0x004F2BF0
    void * GetRole(int index); // 0x004F2C30
    int CalcAttackPower(int roleIdx); // 0x004F3020
    int CalcDefensePower(int roleIdx); // 0x004F31C0
    int GetMaxHP(int roleIdx); // 0x004F3380
    int GetMaxMP(int roleIdx); // 0x004F33D0
    int GetTotalRounds(); // 0x004F3420
    char CheckBuff(int roleIdx); // 0x004F3430
    char CanUseSkill(int roleIdx); // 0x004F34E0
    int CalcMagicAttack(int roleIdx); // 0x004F3570
    int CalcMPRegen(int roleIdx); // 0x004F3620
    int CalcMagicDefense(int roleIdx); // 0x004F36D0
    int GetAttackBonus(int roleIdx); // 0x004F37A0
    int GetDefenseBonus(int roleIdx); // 0x004F3820
    int GetRoleState(int roleIdx); // 0x004F38A0
    int GetSpeedBonus(int roleIdx); // 0x004F3920
    int GetRoleLevel(int roleIdx); // 0x004F39A0
    int GetRoleExp(int roleIdx); // 0x004F39F0
    char SetRoleFlag(int roleIdx, char flag); // 0x004F3A30
    int GetRoleAttr(int roleIdx); // 0x004F3A50
    int CalcMPCost(int roleIdx); // 0x004F3AD0
    int GetRoleMP(int roleIdx); // 0x004F3B90
    int GetRoleHP(int roleIdx); // 0x004F3BC0
    int IsForce1(int force); // 0x004F3C00
    char IsPlayerTeam(int force); // 0x004F3C20
    char GetRoleForce(int roleIdx); // 0x004F3C70
    bool IsRoleInForce(int roleIdx); // 0x004F3CC0
    char CanRoleAct(int roleIdx); // 0x004F3D10
    char GetRoleField(int roleIdx, int fieldOff); // 0x004F3D90
    int FindFirstEnemySlot(int roleIdx); // 0x004F3DC0
    char ProcessRound(unsigned int dwVal); // 0x004F3E20
    void TickDebuffs(int roleIdx); // 0x004F48C0
    unsigned int CalcMagicDamage(int roleIdx, int nMagicID); // 0x004F4B90
    unsigned int CalcSkillDamage(int roleIdx, int nSkillID); // 0x004F4C80
    int ProcessAttackResult(int roleIdx); // 0x004F4DA0
    int ProcessMagicResult(int roleIdx); // 0x004F5070
    int AISelectItem(int roleIdx, char pData); // 0x004F5330
    int CalcPhysicalDamage(int roleIdx); // 0x004F55D0
    int CalcMagicDamage(int roleIdx); // 0x004F57A0
    int ProcessSkillEffect(int roleIdx); // 0x004F5970
    int ProcessItemEffect(int roleIdx); // 0x004F5B70
    int AISelectMagic(unsigned int roleIdx, char pData, int nVal); // 0x004F5D00
    int AISelectHealItem(unsigned int roleIdx, char pData, int nVal); // 0x004F6000
    int AISelectTarget(unsigned int roleIdx, char pData, int nVal); // 0x004F61D0
    int AISelectSkill(unsigned int roleIdx, int nVal, char pData); // 0x004F6370
    int AISelectItemForSkill(unsigned int roleIdx, int nSkillID, char pData); // 0x004F6690
    int AISelectSkillTarget(unsigned int roleIdx, int nSkillID, char pData); // 0x004F6860
    char ValidateCommandTarget(int *pCmd); // 0x004F6DA0
    char CheckEventCondition(int pEvent); // 0x004F7200
    char CheckMagicCost(int *p_DWORD); // 0x004F7480
    char GetRoleAI(void *pOut); // 0x004F7500
    int GetSkillCostLevel(unsigned int dwSlot, int nSkillID); // 0x004F76C0
    char SumGPCost(int nVal); // 0x004F7820
    unsigned int CheckStatus(); // 0x004F7880
    void * ProcessActions(); // 0x004F7910
    void ProcessCombatDialog(unsigned int dwVal); // 0x004F7FC0
    int UpdateEffects(); // 0x004F8480
    void ProcessControlInput(); // 0x004F8AF0
    int InitSlot(int idx, int nRoleID); // 0x004F8BB0
    char LoadRoleModel(int nVal); // 0x004F8FA0
    char SpawnRandomEnemies(int nVal, int nVal2); // 0x004F8FD0
    char * CheckRoleCanAct(int roleIdx); // 0x004F90F0
    char * PopulateItemList(int nSlot); // 0x004F91B0
    int GetDialogSlot(int nVal, int nVal2); // 0x004F9340
    unsigned int PopulateMagicList(int nSlot); // 0x004F9390
    int GetMagicSlotData(int nVal, int nVal2, int nVal3); // 0x004F9590
    int PopulateTargetList(int nSlot, int nType); // 0x004F95F0
    int UpdateCommandButtons(int nSlot); // 0x004F9790
    int ApplyDamage(int roleIdx, int dmg); // 0x004F98B0
    int GetSlotState(int nVal, int nVal2); // 0x004FA210
    int CalcSpeedByLevel(int nRole, int nLevel); // 0x004FA280
    int GetActionTypeBySlot(int nVal, int nVal2); // 0x004FA330
    int CalcDefenseByLevel(int nRole, int nLevel); // 0x004FA3A0
    int CalcDamage(int nVal, int nVal2); // 0x004FA440
    int FindSlotByHP(unsigned int a2, unsigned int a3); // 0x004FA4E0
    int GetRoleCount(int nVal); // 0x004FA510
    int CheckRoleStatus(int roleIdx); // 0x004FA540
    int GetSlotActionType(int nVal, char *Buffer); // 0x004FA560
    int FindRoleByID(int nVal); // 0x004FA5F0
    int CountValidSlots(int nVal, int nVal2, int *p_DWORD, int *pnVal); // 0x004FA620
    int CheckDeath(int roleIdx); // 0x004FA6A0
    int GetSlotType(int nVal); // 0x004FA700
    int SwapEffectParams(int nVal); // 0x004FA760
    int Revive(int roleIdx); // 0x004FA8B0
    char UpdateRoleMP(char arg0, int nVal); // 0x004FA930
    int CheckMPRequirement(int nVal); // 0x004FB370
    int RandomizeSpecialSkill(int nSkillId); // 0x004FB6B0
    int Func(int nVal); // 0x00502000
    int CalcTurnDelay(int nVal); // 0x005020D0
    int FadeMusicIn(int nVal); // 0x005021C0
    int FadeMusicOut(int nVal); // 0x00502300
    int GetCombatDialogEntry(int nVal); // 0x00502430
    int FormatSkillResultText(int nVal); // 0x005025C0
    int FormatAttackResultText(int nVal); // 0x005027E0
    int FormatItemResultText(int nVal); // 0x00502950
    int FormatMagicResultText(int nVal); // 0x00502CC0
    int GetRoleMPValue(int nVal, int nVal2, int nVal3); // 0x00503AE0
};
