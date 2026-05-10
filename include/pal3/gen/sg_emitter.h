#pragma once
// Auto-generated: sg_emitter

#include "D3DXVECTOR3.h"
#include "direction_emitter_graph.h"
#include "elelife_emitter_graph.h"
#include "elerandvec_emitter_graph.h"
#include "emissionrate_emitter_graph.h"
#include "rotmulti_emitter_graph.h"
#include "sg_customshape.h"
#include "sg_emitter_sphere.h"
#include "sg_emitter_square.h"
#include "sizemulti_emitter_graph.h"

class sg_emitter {
public:
    char name[64]; // +0x0
    D3DXVECTOR3 relative_position; // +0x40
    D3DXVECTOR3 emission_scope; // +0x4C
    char cs_name[64]; // +0x58
    int emitter_shape; // +0x98
    float cyclelen_start; // +0x9C
    float cyclelen_end; // +0xA0
    int cycle_loop; // +0xA4
    int lighton; // +0xA8
    float m_fSpeedMulti; // +0xAC
    float m_fSizeMulti; // +0xB0
    direction_emitter_graph direction_graph; // +0xB4
    elerandvec_emitter_graph elerandvec_graph; // +0x1568
    emissionrate_emitter_graph emissionrate_graph; // +0x2A1C
    elelife_emitter_graph elelife_graph; // +0x3ED0
    sizemulti_emitter_graph sizemulti_graph; // +0x5384
    rotmulti_emitter_graph rotmulti_graph; // +0x6838
    sg_emitter_square square; // +0x7CEC
    sg_emitter_sphere sphere; // +0x7D04
    sg_customshape m_pCS; // +0x7D0C
    // total size: 0x7D58 (32088)

};
