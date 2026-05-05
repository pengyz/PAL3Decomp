#ifndef PAL3A_SCREENFADEOUT_H
#define PAL3A_SCREENFADEOUT_H

#include "pal3a_types.h"

class ScreenFadeOut {
public:
    char _data[24];

    ~ScreenFadeOut();
    ScreenFadeOut();
    void Render();
};

#endif // PAL3A_SCREENFADEOUT_H
