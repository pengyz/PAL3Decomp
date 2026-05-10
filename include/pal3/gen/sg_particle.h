#pragma once
// Auto-generated: sg_particle

class rgbcolor_particle_graph;
class rotation_particle_graph;
class size_particle_graph;
class vertexalpha_particle_graph;

class sg_particle {
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
    int framenums; // +0x13C
    int framesets; // +0x140
    int animation_type; // +0x144
    int animation_fps; // +0x148
    int random_1stframe; // +0x14C
    int random_rotstart; // +0x150
    int random_rotend; // +0x154
    int random_rotdir; // +0x158
    int random_mirroringx; // +0x15C
    int random_mirroringy; // +0x160
    float m_fSizeMulti; // +0x164
    int chainnum; // +0x168
    int framenum; // +0x16C
    int blendmode; // +0x170
    size_particle_graph size_graph; // +0x174
    rotation_particle_graph rotation_graph; // +0x1628
    vertexalpha_particle_graph vertexalpha_graph; // +0x2ADC
    rgbcolor_particle_graph rgbcolor_graph; // +0x3F90
    // total size: 0x5444 (21572)

};
