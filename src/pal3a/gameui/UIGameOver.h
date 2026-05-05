#ifndef PAL3A_UIGAMEOVER_H
#define PAL3A_UIGAMEOVER_H

#include "pal3a_types.h"

class UIGameOver {
public:
    char _data[240];

    void Destroy();
    ~UIGameOver();
    int Update(float deltatime, int haveinput);
    void Create();
    UIGameOver();
    void Render();
};

#endif // PAL3A_UIGAMEOVER_H
