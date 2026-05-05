#ifndef PAL3A_MESHFXCREATOR_H
#define PAL3A_MESHFXCREATOR_H

#include "pal3a_types.h"

class MeshFxCreator {
public:
    char _data[4];

    MeshFx * NewMeshFx(MeshFxClass classid);
    ~MeshFxCreator();
    MeshFxCreator * Inst();
    MeshFxCreator();
};

#endif // PAL3A_MESHFXCREATOR_H
