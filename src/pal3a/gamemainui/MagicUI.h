#ifndef PAL3A_MAGICUI_H
#define PAL3A_MAGICUI_H

#include "pal3a_types.h"

class MagicUI {
public:
    char _data[267620];

    MagicUI();
    ~MagicUI();
    void CtlList(uchar flag);
    void CreateAttFrame(int Role, tagRECT * rect);
    void SetRoleSkill();
    bool CanUseThis(PlayerSkill * pSkill, int role);
    bool CheckUsable(int l_index, int l_type, uchar bdisinfo);
    bool CheckCom(int l_index, int l_type);
    void CtrlAttFrameDisplay(int Role);
    void GetRoleState(int role, gbColorQuad color);
    void Render();
    void UpdateMagicLV(PlayerSkill * pMagic, int Role);
    void DisSkillInfo(PlayerSkill m_skill);
    void UpdateMagicVal(int Role, int l_type, int magic);
    bool UsingMagicRole(int usingrole, int acceptrole, int selnum);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void GetRoleSkill();
    void SetBtnParEffect(int flag);
    void ReSetState();
    void SetZX(uchar is);
    int CheckRealRole();
    void SetLK(uchar is);
    int UpdateKeyCtrl();
    void SetXJ(uchar is);
    void ChangeGrid(uchar isLarge);
    void SetMagicUI();
    void CheckComQuantum();
    void SetJT(uchar is);
    void AdjustHeadPos(int Role, tagRECT * rect);
    void MgrStpCtrl();
    int PrevRole(int * role);
    bool CheckUsable_Simple(int l_index, int l_type);
    void ComboFinal(int role, int selnum);
    void Create(UIWnd * pWnd);
    void CreateHead(int Role, tagRECT * rect);
    int NextRole(int * role);
    int CheckNeedTo(int l_index, int l_type);
    void SetCQ(uchar is);
    void InitComItem();
    void CreateStpCtl();
    void ControlPage(int Page);
    int Update(float deltatime, int haveinput);
    void IsShow(int Role, uchar flag);
    void SetComParEffect();
    void SetParEffect(int Role);
    void RealCom();
    void GetListVal(int Role, Magic_ListType listType);
    bool CalProbability(float quantum);
    void SetRoleVal();
    int Warp(int n, float warp);
};

#endif // PAL3A_MAGICUI_H
