#ifndef PAL3A_MAINEQUIPUI_H
#define PAL3A_MAINEQUIPUI_H

#include "pal3a_types.h"

class MainEquipUI {
public:
    char _data[205068];

    void SetRoleEquipData();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void DisItemInfo(PlayerItem m_item);
    void SetZX(uchar is);
    void ReSetState();
    void SetBtnParEffect(int flag);
    void Set3DObjParam(PlayerItem * item);
    ~MainEquipUI();
    int CheckRealRole();
    void SetLK(uchar is);
    void SetXJ(uchar is);
    MainEquipUI();
    void UpdateKeyCtrl();
    void CreateAttFrame(int Role, tagRECT * rect);
    void DispRawVal(int Role);
    bool CheckUsable(int selNum, int role, uchar bdisinfo);
    void GetRoleState(int role, gbColorQuad color);
    void CtrlAttFrameDisplay(int Role);
    void CtrlEquip(int Role, int type);
    void Render();
    void PutOnThis(int Role);
    void SetCQ(uchar is);
    void CreateStpCtl();
    void IsShow(int Role, int flag);
    int Update(float deltatime, int haveinput);
    void FillEquipList(int Role, int type);
    void SetRoleVal();
    void CreatePageControlBtn(tagRECT * rect);
    void SetJT(uchar is);
    void MgrStpCtrl();
    int PrevRole(int * role);
    void AdjustHeadPos(int Role, tagRECT * rect);
    void CompareVal(int Role, FightItem * pItem, int type);
    void CompareVal(int Role);
    void Create(UIWnd * pWnd);
    void SetEquipUI();
    void CreateHead(int Role, tagRECT * rect);
    void DisRoleAtt(int Role);
    void GetRoleVal(int Role);
    int NextRole(int * role);
};

#endif // PAL3A_MAINEQUIPUI_H
