#ifndef PAL3A_CBSYSTEM_H
#define PAL3A_CBSYSTEM_H

#include "pal3a_types.h"

class CCBSystem {
public:
    char _data[90840];

    void ShowInfo();
    unsigned long ProcSkill(ulong __formal);
    bool PassCmdToThread(int nThreadIndex, tagCmdData * pCmd);
    bool PassCmdToThread(int nThreadIndex);
    unsigned long ProcCoAttack(ulong __formal);
    void HandleRoleDead(int nRoleIndex);
    unsigned long ProcLineup(ulong __formal);
    bool CanBeHandleNGH_R();
    unsigned long ProcVariance(ulong __formal);
    void SetAutoOnly(uchar bAuto);
    bool PassCmdToTask(int nTaskIndex, int nThreadIndex);
    unsigned long ProcWeaponSkill(ulong __formal);
    int GetThreadIndex(ulong dwThreadID);
    unsigned long ProcMagicWait(ulong __formal);
    ~CCBSystem();
    bool Create();
    bool IsThreadExist(ulong dwThreadID);
    void Reset();
    unsigned long ProcEnemyAIWaitFriendSkill(ulong __formal);
    void Update(double gbTime);
    bool DestroyObj();
    void DelAllTaskAndThread();
    bool CanBeHandleWPX_R();
    bool InitAllObj();
    bool InitObj();
    void SetQuitFlag(uchar b);
    unsigned long ProcNormalAttack(ulong __formal);
    unsigned long AddThread(void * fp, tagCmdData * pCmd);
    unsigned long ProcControl(ulong __formal);
    unsigned long ProcSetBFA(ulong __formal);
    void Render();
    bool IsFriendDoSkill();
    unsigned long GetFreeID();
    bool Init(FightInfo * pFightInfo, uchar bEdit);
    int Message(char * pMsg, char * pTitle, uint uType);
    int GetSameThreadNum(void * fp);
    CCBSystem();
    unsigned long ProcProtect(ulong __formal);
    bool DelThread(int nIndex);
    bool PassCmdViaThread(int nDestThread, int nSrcThread);
    unsigned long ProcFleeWait(ulong __formal);
    void SetAuto(uchar bAuto);
    void SetTimeScale(float f);
    bool IsRoleWaitForFlee(int nRoleIndex);
    unsigned long ProcDialog(ulong __formal);
    unsigned long ProcFlee(ulong __formal);
    unsigned long ProcMagic(ulong __formal);
    unsigned long ProcMessage(ulong __formal);
    bool CreateObj();
    unsigned long ProcUseItem(ulong __formal);
    bool Destroy();
    unsigned long ProcDefence(ulong __formal);
    unsigned long ProcFling(ulong __formal);
    void HandleInput();
    bool IsEditorWindow(HWND * hWnd);
    unsigned long ProcAI(ulong __formal);
    void Proceed();
};

void DataCheck();

#endif // PAL3A_CBSYSTEM_H
