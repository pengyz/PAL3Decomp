#ifndef PAL3A_GLOW_H
#define PAL3A_GLOW_H

#include "pal3a_types.h"

class Glow {
public:
    char _data[28];

    void RemoveGlowObj(GlowObj * obj);
    void ClearGlowObj();
    bool Create();
    void AddGlowObj(GlowObj * obj);
    void Render();
    void EndRenderGlowObject();
    Glow();
    bool BeginRenderGlowObject();
    ~Glow();
    Glow * Inst();
    void RenderSingle(GlowObj * obj);
};

#endif // PAL3A_GLOW_H
