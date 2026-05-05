#ifndef PAL3A_DEALUI_H
#define PAL3A_DEALUI_H

#include "pal3a_types.h"

class DealUI {
public:
    char _data[3224];

    void SetJT(uchar is);
    void SetZX(uchar is);
    void Destroy();
    void SetXJ(uchar is);
    void InterceptScene();
    void RenderIntercept();
    void SetLK(uchar is);
    int Update(float deltatime, int haveinput);
    void SetST(ushort ShopType);
    void SetCQ(uchar is);
    int CheckRealRole();
    void Create();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void SetShopData(st_Manager * pData);
    DealUI();
    ~DealUI();
    void UpdateKeyCtrl();
    void SwitchUIRender(int flag);
    void Render();
};

#endif // PAL3A_DEALUI_H
