#ifndef PAL3A_MAINPROPUI_H
#define PAL3A_MAINPROPUI_H

#include "pal3a_types.h"

class MainPropUI {
public:
    char _data[248336];

    void DisItemInfo(PlayerItem m_item);
    int NextRole(int * role);
    bool CanUseThis(PlayerItem * pItem, int role);
    void Set3DObjParam(PlayerItem * item);
    void FillList(int type, uchar onlyCheck);
    int UpdateKeyCtrl();
    void Render();
    void CreateAttFrame(int Role, tagRECT * rect);
    void SetPropData();
    void SetParEffect(int Role, gbColorQuad m_color);
    void SetCQ(uchar is);
    int Update(float deltatime, int haveinput);
    ~MainPropUI();
    void SetPropUI();
    int CheckRealRole();
    int PrevRole(int * role);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Create(UIWnd * pWnd);
    void MgrStpCtrl();
    bool CheckUsable(int l_index, uchar bdisinfo);
    void AdjustHeadPos(int Role, tagRECT * rect);
    void SetBtnParEffect(int flag);
    void UsingThis(int useRole);
    void CreatePageControlBtn(tagRECT * rect);
    void SetLK(uchar is);
    bool CheckUsable_Simple(int l_index);
    void ControlPage(int Page);
    void SetRoleVal();
    int GetSkillUseTime(int Role, ulong id);
    void SetZX(uchar is);
    void SetJT(uchar is);
    void EnableList(uchar is);
    void CreateStpCtl();
    void CtrlAttFrameDisplay(int Role);
    MainPropUI();
    void GetRoleState(int role, gbColorQuad color);
    int CheckNeedTo(int l_index);
    void SetXJ(uchar is);
    void ReSetState();
    void CreateHead(int Role, tagRECT * rect);
    int GetSkillLv(int Role, ulong id);
    void IsShow(int Role, uchar flag);
};

#endif // PAL3A_MAINPROPUI_H
