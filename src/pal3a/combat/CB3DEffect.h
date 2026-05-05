#ifndef PAL3A_CB3DEFFECT_H
#define PAL3A_CB3DEFFECT_H

#include "pal3a_types.h"

class C3DSpark {
public:
    char _data[15920];

    bool CreateSingle(void* pSpark);
    ~C3DSpark();
    void Update(float fDeltaTime);
    void Render();
    void CreateOne(float x, float y, float z);
    C3DSpark();
    void DestroyAll();
};

#endif // PAL3A_CB3DEFFECT_H
