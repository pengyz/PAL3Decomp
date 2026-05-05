#ifndef PAL3A_ROLESHADOW_H
#define PAL3A_ROLESHADOW_H

#include "pal3a_types.h"

class RoleShadow {
public:
    char _data[5344];

    void Create();
    void DisableFrameShadow();
    void Render();
    void DestroyFrameShadow();
    void SetFrameShadow(int nFrame, int nFPS);
    void UpdateFrameShadow(float deltatime);
    RoleShadow();
    ~RoleShadow();
};

#endif // PAL3A_ROLESHADOW_H
