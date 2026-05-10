#pragma once
// Auto-generated: gbPartGroupParam

#include "gbPartParamControl.h"
#include "gbTextureArray.h"

class gbPartGroupParam {
public:
    char particle_name[32]; // +0x0
    int particle_lighting; // +0x20
    float gravity; // +0x24
    float noresis; // +0x28
    int aresis_velocity; // +0x2C
    int aresis_size; // +0x30
    float aresis_constant; // +0x34
    char filename[256]; // +0x38
    int particlesize; // +0x138
    int animation_type; // +0x13C
    int animation_fps; // +0x140
    int random_1stframe; // +0x144
    int random_rotstart; // +0x148
    int random_rotend; // +0x14C
    int random_rotdir; // +0x150
    int random_mirroringx; // +0x154
    int random_mirroringy; // +0x158
    int chainnum; // +0x15C
    int framenum; // +0x160
    int blendmode; // +0x164
    gbPartParamControl SizeCtrl; // +0x168
    gbPartParamControl RotCtrl; // +0x134C
    gbPartParamControl AlphaCtrl; // +0x2530
    gbPartParamControl RGBCtrl; // +0x3714
    gbTextureArray TexArray; // +0x48F8
    gbRenderEffect * pREffect; // +0x493C
    // total size: 0x4940 (18752)

};
