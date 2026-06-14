#pragma once
// Auto-generated: CCBSystem

#include "ECBCombatResult.h"
#include "ECBCombatState.h"
#include "tagPlayerSet.h"
#include "tagThread.h"

class C2DSpark;
class C3DSpark;
class CCBAI;
class CCBAttackSequen;
class CCBControl;
class CCBEditor;
class CCBRoleState;
class CCBStage;
class CCBUI;
class CEffMgr;
class CEffectSimple;
class CEffectSystem;
class FightInfo;
class TxtFile;
class tagCmdData;

class CCBSystem {
public:
    CCBSystem * m_pUtil; // +0x0
    CCBUI * m_pUI; // +0x4
    CCBControl * m_pControl; // +0x8
    CCBAttackSequen * m_pAttackSequen; // +0xC
    CCBRoleState * m_pRoleState; // +0x10
    CCBStage * m_pStage; // +0x14
    CCBAI * m_pAI; // +0x18
    CCBEditor * m_pEditor; // +0x1C
    CEffectSystem * m_pES; // +0x20
    CEffectSimple * m_pEffectSimple; // +0x24
    TxtFile * m_pConfig; // +0x28
    CEffMgr * m_pEffMgr; // +0x2C
    CEffMgr * m_pATSEffMgr; // +0x30
    C2DSpark * m_p2DSpark; // +0x34
    C3DSpark * m_p3DSpark; // +0x38
    char _gap_03C[4]; // +0x3C
    double m_DeltaTime; // +0x40
    double m_dTimeFund; // +0x48
    float m_fTimeFund; // +0x50
    char _gap_054[4]; // +0x54
    double m_AbsDeltaTime; // +0x58
    double m_dAbsTimeFund; // +0x60
    float m_fAbsTimeFund; // +0x68
    float m_fTimeScale; // +0x6C
    FightInfo * m_pFightInfo; // +0x70
    BYTE m_bQuitFlag; // +0x74
    BYTE m_bPause; // +0x75
    char _gap_076[2]; // +0x76
    ECBCombatState m_eState; // +0x78
    ECBCombatResult m_eResult; // +0x7C
    BYTE m_bFiveNimbus; // +0x80
    BYTE m_bPXVariance; // +0x81
    char _gap_082[2]; // +0x82
    int m_nTimesOfCombat; // +0x84
    BYTE m_bAuto; // +0x88
    BYTE m_bEditor; // +0x89
    BYTE m_bLockCam; // +0x8A
    BYTE m_bFirstRender; // +0x8B
    UINT m_dwIDHolder; // +0x8C
    int m_nThread; // +0x90
    int m_nCurThread; // +0x94
    tagThread m_Thread[1024]; // +0x98
    char _gap_1098[86016]; // +0x1098
    tagPlayerSet m_Player[11]; // +0x16098
    char _tail_160C4[532]; // +0x160C4
    // total size: 0x162D8 (90840)

    void ProcessSlotResults(int nVal); // 0x00462280
    void InitResultWindow(); // 0x00462340
    _BYTE * GetThreadBase(); // 0x004C6170
    int InitCmdTable1_thunk(); // 0x004DB3A0
    int InitCmdTable1(); // 0x004DB3B0
    int InitCmdTable2_thunk(); // 0x004DB3F0
    int InitCmdTable2(); // 0x004DB400
    int InitCmdTable3_thunk(); // 0x004DB440
    int InitCmdTable3(); // 0x004DB450
    CCBSystem * InitCmd(int nVal); // 0x004DB490
    int ResetFlags(); // 0x004DB4C0
    char DestroySubsystems(); // 0x004DB4F0
    int CalcSpeed(int roleIdx, int nVal); // 0x004DB640
    int GetCmdSlot(int idx); // 0x004DB660
    char GetCmdType(int idx); // 0x004DB690
    bool IsBusy(); // 0x004DB6A0
    bool IsCmdReady(int idx); // 0x004DB6C0
    bool IsCmdEmpty(int idx); // 0x004DB6E0
    int GetCmdValue(int idx); // 0x004DB700
    char * GetCmdPtr(int idx); // 0x004DB710
    char * ClearCmdSlot(int nVal); // 0x004DB730
    char * GetCmdData(int idx); // 0x004DB750
    int GetCmdCount(int idx); // 0x004DB780
    int ProcessAllCmds(); // 0x004DB7A0
    char * GetCmdString(int idx); // 0x004DB8B0
    int SetThreadFlag(char pData); // 0x004DB8E0
    int SetCmdParam(int idx, int value); // 0x004DB920
    int InvokeThreadMethod(int nVal, char pData); // 0x004DB9C0
    void InitRoleStateUI(); // 0x004DB9F0
    void InitCombatSlot(int roleIdx); // 0x004DBE60
    CCBSystem * CopyCmdData(int *p_DWORD); // 0x004DC160
    int GetState(); // 0x004DC1B0
    int ClearAllPointers(); // 0x004DC1C0
    char StartRoleThread(int arg0); // 0x004DC3F0
    double ResetConfig(int nVal); // 0x004DC510
    int FindFreeThread(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int nVal6, int nVal7, int nVal8, int nVal9); // 0x004DC650
    char ValidateThreadAction(int nVal); // 0x004F1C40
    int AddCommand(int nCmdType, BOOL bImmediate, int nParam); // 0x004F2C70
    bool IsMagicSlotMsg(int nVal); // 0x004F7050
    char HandleMagicCommand(int nVal); // 0x004F70A0
    char HandleMagicSlotInput(int nVal); // 0x004F7140
    int FindThreadByID(int nID); // 0x004FCA40
    int EndBattle(); // 0x00500170
    char CastProtect(int nCaster, int nTarget, float fVal); // 0x00504D60
    void HandleInput(); // 0x00512310
    void SetQuitFlag(); // 0x00512320
    bool IsEditorWindow(); // 0x00512330
    void SetAuto(); // 0x00512370
    void SetAutoOnly(); // 0x00512380
    void ShowInfo(); // 0x005123C0
    void SetTimeScale(); // 0x005123D0
    unsigned int GetFreeID(); // 0x00512410
    void DelAllTaskAndThread(); // 0x00512460
    void Proceed(); // 0x00512470
    bool CanBeHandleWPX_R(); // 0x005124B0
    bool CanBeHandleNGH_R(); // 0x005124C0
    CCBSystem(); // 0x00512500
    unsigned int ProcDialog(); // 0x00512580
    char ProcNormalAttack(); // 0x005125E0
    char ProcFling(); // 0x00512BA0
    void * ProcCoAttack(CCBSystem *Block, char formal); // 0x00512D40
    char ProcWeaponSkill(); // 0x00512D60
    char ProcMagicWait(unsigned int formal, char pData); // 0x00512F40
    int CombatUpdate(double dt); // 0x00513060
    char RenderCheck(); // 0x00513120
    char ProcMagic(); // 0x00513150
    int GetRenderFlag(); // 0x00513330
    bool ProcUseItem(HWND formal); // 0x00513380
    int SetRenderFlag(char flag); // 0x00513390
    char ProcFlee(char formal); // 0x00513420
    char ProcDefence(); // 0x00513430
    void ProcAI(float formal); // 0x00513600
    unsigned int ProcProtect(); // 0x005136A0
    char ProcMessage(int idx); // 0x005136D0
    bool IsFriendDoSkill(); // 0x005137F0
    int CheckBattleEnd(); // 0x00513840
    int Message(char *a2, char *a3, int a4); // 0x00513EB0
    bool IsRoleWaitForFlee(int nRoleIndex); // 0x00513FD0
    unsigned int AddThread(int fp); // 0x00514220
    bool DelThread(int nIndex); // 0x00514610
    int GetSameThreadNum(int fp); // 0x00514870
    bool IsThreadExist(unsigned int dwThreadID); // 0x00514AE0
    int GetThreadIndex(unsigned int dwThreadID); // 0x00514D60
    int PassCmdToThread(int  a_34); // 0x00514FE0
    int PassCmdToThread(int a2, int a3); // 0x00515200
    int PassCmdToTask(int a2, int a3); // 0x005155D0
    int PassCmdViaThread(int a2, int a3); // 0x00515760
    int AllocThread(int nVal); // 0x005158F0
    int CreateObj(int nVal); // 0x00515940
    BOOL CreateObj(CCBUI **ppUI, const char *szName, UINT nFlags); // 0x005159A0
    char CreateObj(CCBRoleState **a2); // 0x00515AC0
    int CreateObj(int (__thiscall *a2)(int _this, int a2), int nVal, int nVal2, int nVal3, const void *pData); // 0x00515B20
    char ClearEffect(int idx); // 0x00515C50
    bool CreateObj(struct CCBEditor **a2); // 0x00515D10
    void * DestroyObj(CCBSystem *Block, char pData); // 0x00515DD0
    void * DestroyObj_5df0(CCBSystem *Block, char pData); // 0x00515DF0
    BOOL DestroyObj(); // 0x00515E50
    void DestroyObj_5e70(); // 0x00515E70
    bool InitObj(); // 0x00515E90
    int InitObj_5ee0(); // 0x00515EE0
    int InitObj_5f30(); // 0x00515F30
    int InitObj_5f80(); // 0x00515F80
    int InitObj_5fd0(); // 0x00515FD0
};
