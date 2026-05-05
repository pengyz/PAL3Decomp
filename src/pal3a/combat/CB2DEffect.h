#ifndef PAL3A_CB2DEFFECT_H
#define PAL3A_CB2DEFFECT_H

#include "pal3a_types.h"

class C2DSpark {
public:
    char _data[24688];

    bool CreateSingle(void* pSpark);
    void CreateMore(int x, int y, gbColorQuad color);
    ~C2DSpark();
    void Update(float fDeltaTime);
    void Render();
    void CreateTrack(int nx, int ny, gbColorQuad color);
    void CreateStars(int x, int y, int nWidth, float fStarSize);
    C2DSpark(int nClientWidth, int nClientHeight);
    void SetEnableMouseTrack(uchar bEnable);
    void DestroyAll();
};

#endif // PAL3A_CB2DEFFECT_H
