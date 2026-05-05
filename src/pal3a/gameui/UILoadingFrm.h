#ifndef PAL3A_UILOADINGFRM_H
#define PAL3A_UILOADINGFRM_H

#include "pal3a_types.h"

class UILoadingFrm {
public:
    char _data[332];

    void Render();
    void Create();
    int Update(float deltatime, int haveinput);
    ~UILoadingFrm();
    UILoadingFrm();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
};

#endif // PAL3A_UILOADINGFRM_H
