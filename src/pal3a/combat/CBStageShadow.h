#ifndef PAL3A_CBSTAGESHADOW_H
#define PAL3A_CBSTAGESHADOW_H

#include "pal3a_types.h"

class CCBStageShadow {
public:
    char _data[1556];

    void Render();
    void Reset();
    bool Create();
    void Update();
    bool Init();
    ~CCBStageShadow();
    CCBStageShadow(CCBStage * pStage);
    void FillShadowQuad();
    bool Destroy();
};

#endif // PAL3A_CBSTAGESHADOW_H
