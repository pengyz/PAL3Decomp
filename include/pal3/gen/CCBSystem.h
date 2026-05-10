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
    double m_DeltaTime; // +0x40
    double m_dTimeFund; // +0x48
    float m_fTimeFund; // +0x50
    double m_AbsDeltaTime; // +0x58
    double m_dAbsTimeFund; // +0x60
    float m_fAbsTimeFund; // +0x68
    float m_fTimeScale; // +0x6C
    FightInfo * m_pFightInfo; // +0x70
    unsigned char m_bQuitFlag; // +0x74
    unsigned char m_bPause; // +0x75
    ECBCombatState m_eState; // +0x78
    ECBCombatResult m_eResult; // +0x7C
    unsigned char m_bFiveNimbus; // +0x80
    unsigned char m_bPXVariance; // +0x81
    int m_nTimesOfCombat; // +0x84
    unsigned char m_bAuto; // +0x88
    unsigned char m_bEditor; // +0x89
    unsigned char m_bLockCam; // +0x8A
    unsigned char m_bFirstRender; // +0x8B
    unsigned long m_dwIDHolder; // +0x8C
    int m_nThread; // +0x90
    int m_nCurThread; // +0x94
    tagThread m_Thread[1024]; // +0x98
    tagPlayerSet m_Player[11]; // +0x16098
    // total size: 0x162D8 (90840)

    static int InitCmdTable1_thunk(); // 0x004DB3A0
    static int InitCmdTable1(); // 0x004DB3B0
    static int InitCmdTable2_thunk(); // 0x004DB3F0
    static int InitCmdTable2(); // 0x004DB400
    static int InitCmdTable3_thunk(); // 0x004DB440
    static int InitCmdTable3(); // 0x004DB450
    void * InitCmd(int a2); // 0x004DB490
    int ResetFlags(); // 0x004DB4C0
    char DestroySubsystems(); // 0x004DB4F0
    static int CalcSpeed(int roleIdx, int a2); // 0x004DB640
    int GetCmdSlot(int idx); // 0x004DB660
    char GetCmdType(int idx); // 0x004DB690
    bool IsBusy(); // 0x004DB6A0
    bool IsCmdReady(int idx); // 0x004DB6C0
    bool IsCmdEmpty(int idx); // 0x004DB6E0
    int GetCmdValue(int idx); // 0x004DB700
    char * GetCmdPtr(int idx); // 0x004DB710
    char * sub_4DB730(int a2); // 0x004DB730
    char * GetCmdData(int idx); // 0x004DB750
    int GetCmdCount(int idx); // 0x004DB780
    int ProcessAllCmds(); // 0x004DB7A0
    char * GetCmdString(int idx); // 0x004DB8B0
    double GetDeltaTime(); // 0x004DB910
    int SetCmdParam(int idx, int value); // 0x004DB920
    int GetControl(); // 0x004DC5B0
    char GetStageRole(int idx); // 0x004FC8F0
    char GetStageRoleByIdx(int idx); // 0x004FC940
    int EndBattle(); // 0x00500170
    static void HandleInput(); // 0x00512310
    static int SetQuitFlag(); // 0x00512320
    static int IsEditorWindow(); // 0x00512330
    static int SetAuto(); // 0x00512370
    static int SetAutoOnly(); // 0x00512380
    static int ShowInfo(); // 0x005123C0
    static int SetTimeScale(); // 0x005123D0
    static int GetFreeID(); // 0x00512410
    static int DelAllTaskAndThread(); // 0x00512460
    static int Proceed(); // 0x00512470
    static int CanBeHandleWPX_R(); // 0x005124B0
    static int CanBeHandleNGH_R(); // 0x005124C0
    CCBSystem(); // 0x00512500
    int ProcDialog(); // 0x00512580
    char ProcNormalAttack(); // 0x005125E0
    char ProcFling(); // 0x00512BA0
    void * ProcCoAttack(CCBSystem *Block, char a2); // 0x00512D40
    char ProcWeaponSkill(); // 0x00512D60
    char ProcMagicWait(int a2, char a3); // 0x00512F40
    int CombatUpdate(double dt); // 0x00513060
    char RenderCheck(); // 0x00513120
    char ProcMagic(); // 0x00513150
    static int GetRenderFlag(); // 0x00513330
    static bool ProcUseItem(HWND a1); // 0x00513380
    int SetRenderFlag(char flag); // 0x00513390
    char ProcFlee(char a2); // 0x00513420
    char ProcDefence(); // 0x00513430
    void ProcAI(float a2); // 0x00513600
    int ProcProtect(); // 0x005136A0
    char ProcMessage(int a2); // 0x005136D0
    int IsFriendDoSkill(); // 0x005137F0
    int CheckBattleEnd(); // 0x00513840
    int Message(int a2); // 0x00513EB0
    int IsRoleWaitForFlee(int a2); // 0x00513FD0
    int AddThread(int a2); // 0x00514220
    int DelThread(int a2); // 0x00514610
    int GetSameThreadNum(int a2); // 0x00514870
    int IsThreadExist(int a2); // 0x00514AE0
    int GetThreadIndex(int a2); // 0x00514D60
    int PassCmdToThread(int a2); // 0x00514FE0
    int PassCmdToTask(int a2); // 0x005155D0
    int PassCmdViaThread(int a2); // 0x00515760
    int CreateObj(int a2); // 0x00515940
    int CreateObj(const char *a2, const char *a3, UINT a4); // 0x005159A0
    // [IDA_COMPLEX_RET] original: int __thiscall(CCBSystem *this, int (__thiscall *a2)(int this, int a2), int a3, 
    int CreateObj(int (__thiscall *a2)(int this, int a2), int a3, int a4, int a5, const void *a6); // 0x00515B20
    char ClearEffect(int idx); // 0x00515C50
    bool CreateObj2(_DWORD *a2); // 0x00515D10
    void * DestroyObj(CCBSystem *Block, char a2); // 0x00515DD0
    static int DestroyObj(); // 0x00515E40
    static int InitObj(); // 0x00515E90
};
