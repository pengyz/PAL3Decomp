#pragma once
// Auto-generated: sg_emitter

#include "direction_emitter_graph.h"
#include "elelife_emitter_graph.h"
#include "elerandvec_emitter_graph.h"
#include "emissionrate_emitter_graph.h"
#include "rotmulti_emitter_graph.h"
#include "sg_customshape.h"
#include "sg_emitter_sphere.h"
#include "sg_emitter_square.h"
#include "sizemulti_emitter_graph.h"

class D3DXVECTOR3;

class sg_emitter {
public:
    char name[64]; // +0x0
    D3DXVECTOR3 relative_position; // +0x40
    char _gap_044[8]; // +0x44
    D3DXVECTOR3 emission_scope; // +0x4C
    char _gap_050[8]; // +0x50
    char cs_name[64]; // +0x58
    int emitter_shape; // +0x98
    float cyclelen_start; // +0x9C
    float cyclelen_end; // +0xA0
    int cycle_loop; // +0xA4
    int lighton; // +0xA8
    float m_fSpeedMulti; // +0xAC
    float m_fSizeMulti; // +0xB0
    direction_emitter_graph direction_graph; // +0xB4
    char _gap_0B8[5296]; // +0xB8
    elerandvec_emitter_graph elerandvec_graph; // +0x1568
    char _gap_156C[5296]; // +0x156C
    emissionrate_emitter_graph emissionrate_graph; // +0x2A1C
    char _gap_2A20[5296]; // +0x2A20
    elelife_emitter_graph elelife_graph; // +0x3ED0
    char _gap_3ED4[5296]; // +0x3ED4
    sizemulti_emitter_graph sizemulti_graph; // +0x5384
    char _gap_5388[5296]; // +0x5388
    rotmulti_emitter_graph rotmulti_graph; // +0x6838
    char _gap_683C[5296]; // +0x683C
    sg_emitter_square square; // +0x7CEC
    char _gap_7CF0[20]; // +0x7CF0
    sg_emitter_sphere sphere; // +0x7D04
    char _gap_7D08[4]; // +0x7D08
    sg_customshape m_pCS; // +0x7D0C
    char _tail_7D10[72]; // +0x7D10
    // total size: 0x7D58 (32088)

};
