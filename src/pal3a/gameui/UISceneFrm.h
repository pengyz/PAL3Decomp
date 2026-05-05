#ifndef PAL3A_UISCENEFRM_H
#define PAL3A_UISCENEFRM_H

#include "pal3a_types.h"

class UISceneFrm {
public:
    char _data[3124];

    ~UISceneFrm();
    void Render();
    int Update(float deltatime, int haveinput);
    UISceneFrm();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Create();
};

#endif // PAL3A_UISCENEFRM_H
