#ifndef PAL3A_MESHFX_H
#define PAL3A_MESHFX_H

#include "pal3a_types.h"

class MeshFx {
public:
    char _data[92];

    void GetOBB(gbOBBox * box);
    ~MeshFx();
    MeshFx();
    int GetCurrentState();
};

#endif // PAL3A_MESHFX_H
