#pragma once
// Auto-generated: SceneProp

#include "ParabolaCalculator.h"

class SceneProp {
public:
    gbGeomNode * pGeom; // +0x0
    tagRECT rect; // +0x4
    float fCurTime; // +0x14
    float fValidTime; // +0x18
    BYTE bCountTime; // +0x1C
    BYTE bPopFling; // +0x1D
    gbVec3D vecFling; // +0x20
    gbVec3D lastFling; // +0x2C
    gbVec3D rotFling; // +0x38
    BYTE bCollide; // +0x44
    DWORD ID; // +0x48
    BYTE bNeedParabola; // +0x4C
    int nFlag; // +0x50
    BYTE bValid; // +0x54
    ParabolaCalculator parabola; // +0x58
    // total size: 0x88 (136)

};
