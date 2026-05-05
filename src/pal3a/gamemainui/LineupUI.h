#ifndef PAL3A_LINEUPUI_H
#define PAL3A_LINEUPUI_H

#include "pal3a_types.h"

class LineupUI {
public:
    char _data[157492];

    void SelRoleHead(int Role);
    void DispPlank(int Role, uchar disp);
    void SetBtnParEffect(int flag);
    void CtrlBtn(int Role, uchar is);
    void SetCQ(uchar is);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void IsShow(int Role, uchar is);
    void AdjustPlank(int Role, tagPOINT pt);
    void SetLineupUI();
    int CheckRealRole();
    void CreatePlank(int Role);
    LINEUPINFO * GetBehaviorSeting(int Role);
    ~LineupUI();
    void Render();
    void WriteBackMgr();
    void SetLK(uchar is);
    void WriteBackLineup();
    int Update(float deltatime, int haveinput);
    void LoadMgrData();
    void Create(UIWnd * pWnd);
    void SetZX(uchar is);
    void MgrStpCtrl();
    void SetJT(uchar is);
    void CreateStpCtl();
    void CheckLineupPlank();
    LineupUI();
    void SetXJ(uchar is);
    void GetRoleState(int role, gbColorQuad color);
};

class ProtectPanel {
public:
    char _data[1288];

    void ResetProgress();
    void SubmitProtectInfo();
    void Create(uint id, tagRECT * rc, UIWnd * pwnd);
    void SetValue();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
};

#endif // PAL3A_LINEUPUI_H
