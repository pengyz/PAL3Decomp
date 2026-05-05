#ifndef PAL3A_UISTATICCB_H
#define PAL3A_UISTATICCB_H

#include "pal3a_types.h"

class UIStaticCB {
public:
    char _data[164];

    void ShowWindow(int show);
    ~UIStaticCB();
    UIStaticCB();
};

#endif // PAL3A_UISTATICCB_H
