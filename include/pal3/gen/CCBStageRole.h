#pragma once
// Auto-generated from IDA decomp - CCBStageRole
// 59 methods

class CCBStageRole {
public:
    char IsActive(int index);  // 0x004ED040
    int ~CCBStageRole(int a2, int a3, _DWORD *a4);  // 0x00508930
    static int() Proceed();  // 0x005090F0
    static int() SetAlive();  // 0x00509130
    static int() SetMaxBlend();  // 0x00509140
    static int() SetVisible();  // 0x00509180
    static int() SetPause();  // 0x00509190
    static int() OnChangeAction();  // 0x005091D0
    static int() CheckAction();  // 0x005091E0
    static int() OnPlayAction();  // 0x00509220
    static int() IsUnderMouse();  // 0x00509270
    static int() IsCollideRay();  // 0x00509280
    static int() GetRoleRadius();  // 0x00509290
    static int() GetRoleHeight();  // 0x005092A0
    static char *__thiscall(char *this, int a2) GetOBBox();  // 0x005092B0
    int GetRotAngle();  // 0x00509410
    char IsIdle(unsigned int a2);  // 0x00509540
    char IsAtInitPos();  // 0x00509690
    char IsAtProtectPos(int a2, int a3, int a4);  // 0x005096D0
    static char __usercall@<al>(_DWORD *this@<ecx>, int a2@<edi>) IsTaskFinished();  // 0x005099A0
    void IsDoTask(gbMatrixStack *a2);  // 0x00509B90
    int Grab(int a2);  // 0x0050A180
    char Release(char a2);  // 0x0050A1A0
    int TryRelease();  // 0x0050A1B0
    char ForceRelease(char a2);  // 0x0050A1F0
    char DangerForceRelease(char a2);  // 0x0050A200
    int IsGrabedBy();  // 0x0050A210
    int GetPointerPos();  // 0x0050A260
    void SetBladeTime(int a2);  // 0x0050A2B0
    static bool LoadAction(char a1, int a2, int a3, int a4, int a5, int a6);  // 0x0050A500
    int GetStatus(int index);  // 0x0050A520
    static float *__thiscall(CCBStageRole *this) GetWorldPos();  // 0x0050A560
    double AddTask(float *a2);  // 0x0050A5D0
    bool ForceDelTaskByPFN();  // 0x0050A6F0
    bool ForceEndTaskByPFN();  // 0x0050A700
    bool EndTask(int a2, int a3);  // 0x0050A770
    char DelTask(int a2);  // 0x0050A8E0
    char DelAllTask(int a2, char a3);  // 0x0050A8F0
    char GetCurrentTask(int a2);  // 0x0050A920
    int GetCurrentTaskIndex();  // 0x0050A960
    bool IsReady(int idx);  // 0x0050A980
    static _DWORD *__thiscall(int this, float *a2) DoTask();  // 0x0050A9B0
    void ClearBadPushTask(float a2);  // 0x0050AA60
    double PushBackAllTask();  // 0x0050AAE0
    void ClearAniMsg(char a2, float a3);  // 0x0050AB10
    int SetParam(int a2, char a3);  // 0x0050AC50
    char GetProperCurAction(_DWORD *a2, _DWORD *a3, _DWORD *a4, _DWORD *a5, _DWORD *a6, int *a7, const void *a8, _DWORD *a9);  // 0x0050AD30
    char ProcTransportRun(int a2, int a3, int a4, int a5, int *a6, const void *a7, int a8);  // 0x0050B070
    char SetForceFinishThrowingWeapon(int a2);  // 0x0050B290
    char GetCurrentState();  // 0x0050B330
    int ProcCatchED();  // 0x0050B360
    int GetTaskState();  // 0x0050B530
    char ProcPursueRole(int a2, int a3, char a4);  // 0x0050B580
    int ProcTurn();  // 0x0050BBD0
    int ProcTurnToRole(int a2);  // 0x0050BCD0
    int ProcBlock(int a2);  // 0x0050C320
    int ProcMagic(int a2);  // 0x0050C970
    int ProcUseRecoverItem(float a2);  // 0x0050CDE0
    void PlaySound(char *name, int a3);  // 0x0053E310
};
