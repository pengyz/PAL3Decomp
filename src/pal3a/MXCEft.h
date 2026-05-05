#ifndef PAL3A_MXCEFT_H
#define PAL3A_MXCEFT_H

#include "pal3a_types.h"

class MXCEft {
public:
    char _data[116];

    void Update(float deltatime);
    void Stop();
    void Start(gbVec3D pos);
    void Create(ulong param, int addinparam);
    void AttachSelf(gbRenderEffect * pCustomEffect);
    void Render(gbRenderInfoObj * pobj);
    void Destroy();
    int Attach(gbRenderEffect * pCustomEffect);
    void ChangeState(int iTargetState);
    MXCEft();
    void GetOBB(gbOBBox * box);
    ~MXCEft();
};

#endif // PAL3A_MXCEFT_H
