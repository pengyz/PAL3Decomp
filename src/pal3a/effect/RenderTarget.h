#ifndef PAL3A_RENDERTARGET_H
#define PAL3A_RENDERTARGET_H

#include "pal3a_types.h"

class RenderTarget {
public:
    char _data[200];

    void Create();
    bool OnResetDevice();
    bool Begin(uchar bClear);
    void OnDeviceLost();
    void End();
    gbTexture * GetContent();
    ~RenderTarget();
    RenderTarget * Inst();
    void Destroy();
    void SetMode(int mode);
    RenderTarget();
};

#endif // PAL3A_RENDERTARGET_H
