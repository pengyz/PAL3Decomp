#pragma once
// Auto-generated: gbPartEmitter

#include "gbEmitterShape.h"
#include "gbEmitterSphere.h"
#include "gbEmitterSquare.h"
#include "gbPartParamControl.h"

class gbPartEmitter {
public:
    char name[64]; // +0x0
    gbVec3D relative_position; // +0x40
    gbVec3D emission_scope; // +0x4C
    char cs_name[64]; // +0x58
    int emitter_shape; // +0x98
    float cyclelen_start; // +0x9C
    float cyclelen_end; // +0xA0
    int cycle_loop; // +0xA4
    int lighton; // +0xA8
    gbEmitterSquare square; // +0xAC
    gbEmitterSphere sphere; // +0xC4
    gbEmitterShape shape; // +0xCC
    float m_fSpeedMulti; // +0x118
    float m_fSizeMulti; // +0x11C
    gbPartParamControl DirectionCtrl; // +0x120
    gbPartParamControl RandomVelCtrl; // +0x1304
    gbPartParamControl EmitRateCtrl; // +0x24E8
    gbPartParamControl UnitLifeCtrl; // +0x36CC
    gbPartParamControl UnitScaleCtrl; // +0x48B0
    gbPartParamControl UnitRotCtrl; // +0x5A94
    // total size: 0x6C78 (27768)

};
