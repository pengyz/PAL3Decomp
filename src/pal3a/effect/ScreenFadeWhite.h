#ifndef PAL3A_SCREENFADEWHITE_H
#define PAL3A_SCREENFADEWHITE_H

#include "pal3a_types.h"

class ScreenFadeWhite {
public:
    char _data[24];

    ScreenFadeWhite();
    ~ScreenFadeWhite();
    void Render();
};

#endif // PAL3A_SCREENFADEWHITE_H
