#ifndef PAL3A_MXFIRE_H
#define PAL3A_MXFIRE_H

#include "pal3a_types.h"

class MXFire {
public:
    char _data[248];

    void ChangeState(int iTargetState);
    void GetOBB(gbOBBox * box);
    ~MXFire();
    void Destroy();
    int Attach(gbRenderEffect * pCustomEffect);
    void Render(gbRenderInfoObj * pobj);
    void Update(float deltatime);
    MXFire();
    void Create(ulong param, int addinparam);
    void AttachSelf(gbRenderEffect * pCustomEffect);
};

#endif // PAL3A_MXFIRE_H
