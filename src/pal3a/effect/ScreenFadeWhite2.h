#ifndef PAL3A_SCREENFADEWHITE2_H
#define PAL3A_SCREENFADEWHITE2_H

#include "pal3a_types.h"

class ScreenFadeWhite2 {
public:
    char _data[24];

    ~ScreenFadeWhite2();
    void Render();
    ScreenFadeWhite2();
};

#endif // PAL3A_SCREENFADEWHITE2_H
