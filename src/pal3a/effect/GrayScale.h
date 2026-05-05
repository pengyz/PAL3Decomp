#ifndef PAL3A_GRAYSCALE_H
#define PAL3A_GRAYSCALE_H

#include "pal3a_types.h"

class GrayScale {
public:
    char _data[8];

    GrayScale * Inst();
    ~GrayScale();
    void Create();
    void End();
    GrayScale();
    void Begin();
};

#endif // PAL3A_GRAYSCALE_H
