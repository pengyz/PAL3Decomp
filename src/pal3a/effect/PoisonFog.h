#ifndef PAL3A_POISONFOG_H
#define PAL3A_POISONFOG_H

#include "pal3a_types.h"

class MXPoisonFog {
public:
    char _data[96];

    void Render(gbRenderInfoObj * pobj);
    MXPoisonFog();
    ~MXPoisonFog();
    void Create(ulong param, int addinparam);
    void ChangeState(int iTargetState);
    void GetOBB(gbOBBox * box);
    void AttachSelf(gbRenderEffect * pCustomEffect);
    int Attach(gbRenderEffect * pCustomEffect);
    void Destroy();
    void Update(float deltatime);
};

#endif // PAL3A_POISONFOG_H
