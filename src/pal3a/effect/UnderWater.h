#ifndef PAL3A_UNDERWATER_H
#define PAL3A_UNDERWATER_H

#include "pal3a_types.h"

class UnderWater {
public:
    char _data[24];

    bool OnResetDevice();
    void OnDeviceLost();
    void Begin();
    ~UnderWater();
    void Destroy();
    UnderWater * Inst();
    void Create();
    void End();
    void Update(float deltatime);
    UnderWater();
};

unsigned long F2DW(float f);

#endif // PAL3A_UNDERWATER_H
