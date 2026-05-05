#ifndef PAL3A_SCREENEFFECT_H
#define PAL3A_SCREENEFFECT_H

#include "pal3a_types.h"

class ScreenEffect {
public:
    char _data[24];

    int IsWaiting();
    ~ScreenEffect();
    void Init();
    ScreenEffect();
    void Update(float delta);
};

#endif // PAL3A_SCREENEFFECT_H
