#ifndef PAL3A_PROPUI_H
#define PAL3A_PROPUI_H

#include "pal3a_types.h"

class PropUI {
public:
    char _data[29384];

    int CheckRealRole();
    void Create(UIWnd * pWnd);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void SetEXTMode(int flag);
    void SetCQ(uchar is);
    int Update(float deltatime, int haveinput);
    void Set3DObjParam(FightItem * item);
    void UpdateKeyCtrl();
    bool GetCtrlState(int index);
    void SetPropData(st_Manager * pData);
    void DisItemInfo(int selnum);
    bool IsExitFromHere(int flag);
    void CalPropDeal();
    void SetXJ(uchar is);
    void ReturnParent();
    void ControlReady(uchar isTrue);
    void SetZX(uchar is);
    void SetJT(uchar is);
    void Exit();
    void SetLK(uchar is);
    void EnableDealBTWnd(uchar isTrue);
    void UpdateBtnGroup(float deltatime);
    PropUI();
    ~PropUI();
    void ControlDealBTWnd(uchar isTrue);
};

#endif // PAL3A_PROPUI_H
