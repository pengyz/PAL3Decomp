#pragma once
// Auto-generated: sg_emission_control

#include "sg_emitter_data.h"
#include "sg_particle_data.h"

class sg_emitter;
class sg_particle;
class sg_particle_scene;

class sg_emission_control {
public:
    char name[64]; // +0x0
    int particle_pointer; // +0x40
    int emitter_pointer; // +0x44
    float elapsetime; // +0x48
    float total_elatime; // +0x4C
    int maxparticle; // +0x50
    int first_time; // +0x54
    float cyclelength; // +0x58
    int replacestyle; // +0x5C
    sg_particle_data particle_array[400]; // +0x60
    sg_emitter_data emitter; // +0x9020
    sg_particle * pparticle; // +0x904C
    sg_emitter * pemitter; // +0x9050
    sg_particle_scene * scene_pointer; // +0x9054
    // total size: 0x9058 (36952)

};
