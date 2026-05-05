#ifndef PAL3A_TRANSPORT_H
#define PAL3A_TRANSPORT_H

#include "pal3a_types.h"

class MXTransport {
public:
    char _data[363968];

    ~MXTransport();
    void Render(gbRenderInfoObj * pobj);
    void AttachSelf(gbRenderEffect * pCustomEffect);
    void Create(ulong param, int addinparam);
    MXTransport();
    void ChangeState(int iTargetState);
    void GetOBB(gbOBBox * box);
    void Update(float deltatime);
    int Attach(gbRenderEffect * pCustomEffect);
    void Destroy();
};

#endif // PAL3A_TRANSPORT_H
