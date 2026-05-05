#ifndef PAL3A_MXSAVEPOINT_H
#define PAL3A_MXSAVEPOINT_H

#include "pal3a_types.h"

class MXSavePoint {
public:
    char _data[1060];

    void GetOBB(gbOBBox * box);
    void ChangeState(int iTargetState);
    ~MXSavePoint();
    void Create(ulong param, int addinparam);
    void AttachSelf(gbRenderEffect * pCustomEffect);
    void Destroy();
    int Attach(gbRenderEffect * pCustomEffect);
    void Update(float deltatime);
    MXSavePoint();
    void Render(gbRenderInfoObj * pobj);
};

#endif // PAL3A_MXSAVEPOINT_H
