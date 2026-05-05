#ifndef PAL3A_SALEUI_H
#define PAL3A_SALEUI_H

#include "pal3a_types.h"

class SaleUI {
public:
    char _data[111856];

    void DisItemInfo(int Page, int selnum);
    void CancelSale(int SalePage);
    void GetSaleData();
    void SetSaleData();
    void Set3DObjParam(FightItem * item);
    void UpdateKeyCtrl();
    void AdjustSelNum(int Page);
    void SetEXTMode(int flag);
    void SetCQ(uchar is);
    int Update(float deltatime, int haveinput);
    int CheckRealRole();
    void AddNum(int SaleType);
    void CalSaleData(int SalePage);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Create(UIWnd * pWnd);
    void SubNum(int SaleType);
    void SetLK(uchar is);
    void CalAllSaleData();
    void ControlPage(int Page);
    void UpdateBtnGroup(float deltatime);
    ~SaleUI();
    void SetZX(uchar is);
    void SetJT(uchar is);
    void Exit();
    void CancelAllSale();
    SaleUI();
    void SetXJ(uchar is);
    void ResetSuface();
    void SortList(int Page, int sortstate);
};

#endif // PAL3A_SALEUI_H
