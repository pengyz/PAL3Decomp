#ifndef PAL3A_UISCENEFACE_H
#define PAL3A_UISCENEFACE_H

#include "pal3a_types.h"

class UISceneFace {
public:
    char _data[1844];

    ~UISceneFace();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    int Update(float deltatime, int haveinput);
    void Create(UIWnd * pfather);
    UISceneFace();
    void SetFacePic(int nRoleID);
};

#endif // PAL3A_UISCENEFACE_H
