#pragma once
// Auto-generated: sg_particle_scene

#include "sg_emission_control.h"
#include "sg_emitter.h"
#include "sg_particle.h"

class D3DXVECTOR3;

class sg_particle_scene {
public:
    char name[256]; // +0x0
    int emission_controlnum; // +0x100
    int particle_num; // +0x104
    int emitter_num; // +0x108
    int active_particle; // +0x10C
    int active_emitter; // +0x110
    int active_emissioncontrol; // +0x114
    sg_emission_control econtrol[4]; // +0x118
    int ecenable[4]; // +0x24278
    int cur_sel; // +0x24288
    sg_particle particle[4]; // +0x2428C
    sg_emitter emitter[4]; // +0x3939C
    int maxparticle; // +0x588FC
    int emittedto; // +0x58900
    int npwmr; // +0x58904
    float gravity; // +0x58908
    float timescale; // +0x5890C
    int maxfps; // +0x58910
    int camerafollow; // +0x58914
    float camerafollowdis; // +0x58918
    int gravityeffect; // +0x5891C
    float frontplane; // +0x58920
    float backplane; // +0x58924
    D3DXVECTOR3 objectoffset; // +0x58928
    D3DXVECTOR3 systemoffset; // +0x58934
    D3DXVECTOR3 systemvelocity; // +0x58940
    float m_fMultisize; // +0x5894C
    // total size: 0x58950 (362832)

};
