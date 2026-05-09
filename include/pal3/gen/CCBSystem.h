#pragma once
// Auto-generated from IDA decomp - CCBSystem
// 93 methods

class CCBSystem {
public:
    static int __cdecl() InitCmdTable1_thunk();  // 0x004DB3A0
    static int __cdecl() InitCmdTable1();  // 0x004DB3B0
    static int __cdecl() InitCmdTable2_thunk();  // 0x004DB3F0
    static int __cdecl() InitCmdTable2();  // 0x004DB400
    static int __cdecl() InitCmdTable3_thunk();  // 0x004DB440
    static int __cdecl() InitCmdTable3();  // 0x004DB450
    static void *__thiscall(CCBSystem *this, int a2) InitCmd();  // 0x004DB490
    int ResetFlags();  // 0x004DB4C0
    char DestroySubsystems();  // 0x004DB4F0
    static int CalcSpeed(int roleIdx, int a2);  // 0x004DB640
    int GetCmdSlot(int idx);  // 0x004DB660
    char GetCmdType(int idx);  // 0x004DB690
    bool IsBusy();  // 0x004DB6A0
    bool IsCmdReady(int idx);  // 0x004DB6C0
    bool IsCmdEmpty(int idx);  // 0x004DB6E0
    int GetCmdValue(int idx);  // 0x004DB700
    static char *__thiscall(CCBSystem *this, int idx) GetCmdPtr();  // 0x004DB710
    static char *__thiscall(char *this, int a2) sub_4DB730();  // 0x004DB730
    static char *__thiscall(CCBSystem *this, int idx) GetCmdData();  // 0x004DB750
    int GetCmdCount(int idx);  // 0x004DB780
    int ProcessAllCmds();  // 0x004DB7A0
    static char *__thiscall(CCBSystem *this, int idx) GetCmdString();  // 0x004DB8B0
    double GetDeltaTime();  // 0x004DB910
    int SetCmdParam(int idx, int value);  // 0x004DB920
    int GetControl();  // 0x004DC5B0
    char GetStageRole(int idx);  // 0x004FC8F0
    char GetStageRoleByIdx(int idx);  // 0x004FC940
    int EndBattle();  // 0x00500170
    static void() HandleInput();  // 0x00512310
    static int() SetQuitFlag();  // 0x00512320
    static int() IsEditorWindow();  // 0x00512330
    static int() SetAuto();  // 0x00512370
    static int() SetAutoOnly();  // 0x00512380
    static int() ShowInfo();  // 0x005123C0
    static int() SetTimeScale();  // 0x005123D0
    static int() GetFreeID();  // 0x00512410
    static int() DelAllTaskAndThread();  // 0x00512460
    static int() Proceed();  // 0x00512470
    static int() CanBeHandleWPX_R();  // 0x005124B0
    static int() CanBeHandleNGH_R();  // 0x005124C0
    int CCBSystem();  // 0x00512500
    int ProcDialog();  // 0x00512580
    char ProcNormalAttack();  // 0x005125E0
    char ProcFling();  // 0x00512BA0
    static void *__thiscall(void *Block, char a2) ProcCoAttack();  // 0x00512D40
    char ProcWeaponSkill();  // 0x00512D60
    char ProcMagicWait(int a2, char a3);  // 0x00512F40
    int CombatUpdate(double dt);  // 0x00513060
    char RenderCheck();  // 0x00513120
    char ProcMagic();  // 0x00513150
    static int __cdecl() GetRenderFlag();  // 0x00513330
    static bool ProcUseItem(HWND a1);  // 0x00513380
    int SetRenderFlag(char flag);  // 0x00513390
    char ProcFlee(char a2);  // 0x00513420
    char ProcDefence();  // 0x00513430
    void ProcAI(float a2);  // 0x00513600
    int ProcProtect();  // 0x005136A0
    char ProcMessage(int a2);  // 0x005136D0
    int IsFriendDoSkill();  // 0x005137F0
    int CheckBattleEnd();  // 0x00513840
    int Message(int a2);  // 0x00513EB0
    int IsRoleWaitForFlee(int a2);  // 0x00513FD0
    int AddThread(int a2);  // 0x00514220
    int DelThread(int a2);  // 0x00514610
    int GetSameThreadNum(int a2);  // 0x00514870
    int IsThreadExist(int a2);  // 0x00514AE0
    int GetThreadIndex(int a2);  // 0x00514D60
    int PassCmdToThread(int a2);  // 0x00514FE0
    int PassCmdToThread(int a2);  // 0x00515200
    int PassCmdToTask(int a2);  // 0x005155D0
    int PassCmdViaThread(int a2);  // 0x00515760
    int CreateObj(int a2);  // 0x00515940
    static int CreateObj(const char *a1, const char *a2, UINT a3);  // 0x005159A0
    char CreateObj(int a2);  // 0x00515AC0
    int CreateObj(int (__thiscall *a2)(int this, int a2), int a3, int a4, int a5, const void *a6);  // 0x00515B20
    char ClearEffect(int idx);  // 0x00515C50
    bool CreateObj(_DWORD *a2);  // 0x00515D10
    static void *__thiscall(void *Block, char a2) DestroyObj();  // 0x00515DD0
    static void *__thiscall(void *Block, char a2) DestroyObj();  // 0x00515DF0
    static int() DestroyObj();  // 0x00515E40
    static int() DestroyObj();  // 0x00515E50
    static void() DestroyObj();  // 0x00515E60
    static void() DestroyObj();  // 0x00515E70
    static int() DestroyObj();  // 0x00515E80
    static int() InitObj();  // 0x00515E90
    static int() InitObj();  // 0x00515ED0
    static int() InitObj();  // 0x00515EE0
    static int() InitObj();  // 0x00515F20
    static int() InitObj();  // 0x00515F30
    static int() InitObj();  // 0x00515F70
    static int() InitObj();  // 0x00515F80
    static int() InitObj();  // 0x00515FC0
    static int() InitObj();  // 0x00515FD0
};
