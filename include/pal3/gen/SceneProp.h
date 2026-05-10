#pragma once
// Auto-generated: SceneProp

#include "ParabolaCalculator.h"

class SceneProp {
public:
    gbGeomNode * pGeom; // +0x0
    tagRECT rect; // +0x4
    float fCurTime; // +0x14
    float fValidTime; // +0x18
    unsigned char bCountTime; // +0x1C
    unsigned char bPopFling; // +0x1D
    gbVec3D vecFling; // +0x20
    gbVec3D lastFling; // +0x2C
    gbVec3D rotFling; // +0x38
    unsigned char bCollide; // +0x44
    unsigned long ID; // +0x48
    unsigned char bNeedParabola; // +0x4C
    int nFlag; // +0x50
    unsigned char bValid; // +0x54
    ParabolaCalculator parabola; // +0x58
    // total size: 0x88 (136)

};
