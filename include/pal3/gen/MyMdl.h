#pragma once
// Auto-generated: MyMdl

#include "gbOBBox.h"

class MeshFx;
class gbActor;
class gbGeomNode;

class MyMdl {
public:
    int m_mdltype; // +0x0
    gbActor * m_actor; // +0x4
    gbGeomNode * m_geom; // +0x4
    MeshFx * m_fx; // +0x4
    gbOBBox box; // +0x8
    // total size: 0x54 (84)

};
