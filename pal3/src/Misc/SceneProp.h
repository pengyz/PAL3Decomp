#pragma once
// Auto-generated: SceneProp

#include "ParabolaCalculator.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbengine_types.h"

class SceneProp {
public:
    gbGeomNode * pGeom; // +0x0
    tagRECT rect; // +0x4
    char _gap_008[12]; // +0x8
    float fCurTime; // +0x14
    float fValidTime; // +0x18
    BYTE bCountTime; // +0x1C
    BYTE bPopFling; // +0x1D
    char _gap_01E[2]; // +0x1E
    gbVec3D vecFling; // +0x20
    char _gap_024[8]; // +0x24
    gbVec3D lastFling; // +0x2C
    char _gap_030[8]; // +0x30
    gbVec3D rotFling; // +0x38
    char _gap_03C[8]; // +0x3C
    BYTE bCollide; // +0x44
    char _gap_045[3]; // +0x45
    UINT ID; // +0x48
    BYTE bNeedParabola; // +0x4C
    char _gap_04D[3]; // +0x4D
    int nFlag; // +0x50
    BYTE bValid; // +0x54
    char _gap_055[3]; // +0x55
    ParabolaCalculator parabola; // +0x58
    char _tail_05C[44]; // +0x5C
    // total size: 0x88 (136)

    char CalculateWorldPos(float fVal); // 0x005330F0
    char CalcScreenPosition(); // 0x00533BC0
};
