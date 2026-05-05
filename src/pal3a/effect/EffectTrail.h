#ifndef PAL3A_EFFECTTRAIL_H
#define PAL3A_EFFECTTRAIL_H

#include "pal3a_types.h"

class CTrail {
public:
    char _data[840];

    void End();
    bool Create();
    void SetEnable(uchar bEnable);
    void Update(float fDeltaTime);
    void Begin(gbCamera * pCam);
    ~CTrail();
    void ReleaseRTS();
    CTrail();
    CTrail * Inst();
    bool CreateRTS();
};

#endif // PAL3A_EFFECTTRAIL_H
