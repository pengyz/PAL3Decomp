#ifndef PAL3A_CBATTACKSEQUEN_H
#define PAL3A_CBATTACKSEQUEN_H

#include "pal3a_types.h"

class CCBAttackSequen {
public:
    char _data[500];

    bool Destroy();
    ~CCBAttackSequen();
    void Reset();
    void UnLockFlag(int nIndex);
    void SetToStart(int nIndex);
    void SetDefaultSpeed(int nIndex);
    void SetAllFaceToStart();
    void Update();
    bool IsStart(int nIndex);
    void Set(int nIndex, int nSlot1, int nSlot2, uchar bSlot2Running);
    void SetEnable(uchar bEnable);
    void UpdateFacePos();
    void SetVisible(uchar bVisible);
    bool Init();
    void InitOneRole(int nRoleIndex);
    bool Create();
    int GetTheFirstReachCom2Enemy();
    int GetTheFirstReachCom1Enemy();
    void PauseRole(int nRoleIndex, uchar bPause);
    int CallDefaultSpeed(int nIndex, uchar bSlot2);
    void SetSlot2Run(int nIndex);
    bool IsRunInSlut1(int nIndex);
    bool IsFaceVisible(int nRoleIndex);
    void SetFaceVisible(int nRoleIndex, uchar bVisible);
    bool IsValid(int nIndex);
    ECBStageLockFlag GetLockFlag(int nIndex);
    bool IsReachCom2(int nIndex);
    void SetPause(uchar bPause);
    void HitBack(int nIndex, int nBackValue);
    void HitBackMagic(int nIndex);
    bool IsReachCom1(int nIndex);
    void SetSlot2Speed(int nIndex, uchar bySpeed);
    void InitSequen();
    void RunOneStep();
    CCBAttackSequen(CCBSystem * pCBSystem);
    void InitSpeed();
    int GetRound(int nIndex);
    void SetHalfSlot1(int nIndex);
    void SetLockFlag(int nIndex, ECBStageLockFlag eSLF);
    void SetFaceToStart(int n);
    int GetSlot2Speed(int nIndex);
    void HandleFaceFlash();
    void SetZeroSpeed(int nIndex);
    void InitSmallFace();
};

#endif // PAL3A_CBATTACKSEQUEN_H
