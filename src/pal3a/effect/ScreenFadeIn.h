#ifndef PAL3A_SCREENFADEIN_H
#define PAL3A_SCREENFADEIN_H

#include "pal3a_types.h"

class ScreenFadeIn {
public:
    char _data[28];

    ~ScreenFadeIn();
    void Update(float delta);
    void Init();
    void Render();
    ScreenFadeIn();
};

#endif // PAL3A_SCREENFADEIN_H
