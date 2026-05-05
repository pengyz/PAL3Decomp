#ifndef PAL3A_EQUIPUI_H
#define PAL3A_EQUIPUI_H

#include "pal3a_types.h"

class EquipUI {
public:
    char _data[120484];

    void CompareAllItem(int selnum);
    void ControlEquip(uchar isTrue);
    ~EquipUI();
    void ReturnParent();
    void ControlDealBTWnd(uchar isTrue);
    void RemindUserEquip(int selnum);
    void AdjustControl();
    void UnRemindUserEquip();
    void SetLK(uchar is);
    void UpdateBtnGroup(float deltatime);
    void SetXJ(uchar is);
    void UpdateKeyCtrl();
    void SetEquipData(st_Manager * pData);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void DisItemInfo(int selnum);
    void UnEquipThis(int Role, int type);
    void SetZX(uchar is);
    int CheckRealRole();
    void Set3DObjParam(FightItem * item);
    void Create(UIWnd * pWnd);
    void CalEquipDeal(int Flag, uchar IsDK);
    void UnEquipAll();
    EquipUI();
    void ControlReady(uchar isTrue);
    bool EquipThis(int Role, int type, int selnum);
    void SetJT(uchar is);
    void SetRole();
    void ExitSys(int flag);
    void SetEquip(int selnum);
    void SetCQ(uchar is);
    int Update(float deltatime, int haveinput);
};

#endif // PAL3A_EQUIPUI_H
