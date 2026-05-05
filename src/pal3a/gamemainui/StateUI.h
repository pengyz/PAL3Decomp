#ifndef PAL3A_STATEUI_H
#define PAL3A_STATEUI_H

#include "pal3a_types.h"

class StateUI {
public:
    char _data[162296];

    void SetJT(uchar is);
    void Create();
    void AdjustHeadPos(int Role, tagRECT * rect);
    void InterceptScene();
    void MgrStpCtrl();
    void GetRoleVal();
    int GetPropUIUsedID();
    void CreateHead(int Role, tagRECT * rect);
    void SetSpecialPropUsed(ulong ItemId, uchar CanUse);
    void AdjustPortrait(int Role, tagRECT * rect);
    ~StateUI();
    void SwitchUIRender(_MU_R_STATE flag);
    void SetTestData();
    StateUI();
    void SetCQ(uchar is);
    void SortArrowHead(int Role);
    void IsShow(int Role, uchar flag);
    int Update(float deltatime, int haveinput);
    void CreateStpCtl();
    void SetSwordSkill(uchar is);
    void SetParEffect(int flag);
    void Destroy();
    void SetRoleVal();
    void SetStateUI();
    void ClearAllSpecialProp();
    void CreatePortrait(int Role, tagRECT * rect);
    void SeekToSaveLoad();
    void SetFinishSaveFlag(int bFlag);
    void GetRoleState(int role);
    void Render();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    int CheckRealRole();
    void RenderIntercept();
    void ReSetState();
    void SetTeamState();
    void SetZX(uchar is);
    void SetRoleState(int Role);
    void SetLK(uchar is);
    void UpdateStpCtrl();
    void SetXJ(uchar is);
};

#endif // PAL3A_STATEUI_H
