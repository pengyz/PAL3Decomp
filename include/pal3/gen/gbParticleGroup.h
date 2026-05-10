#pragma once
// Auto-generated: gbParticleGroup

#include "gbEmitterData.h"

class gbPartEmitter;
class gbPartGroupParam;
class gbParticleEffect;
class gbParticleUnit;

class gbParticleGroup {
public:
    char Name[64]; // +0x0
    double Life; // +0x40
    gbEmitterData EmitterData; // +0x48
    gbPartGroupParam * pGroupParam; // +0x78
    gbPartEmitter * pEmitter; // +0x7C
    gbParticleUnit * pAllUnits; // +0x80
    int MaxUnits; // +0x84
    int nAlivePart; // +0x88
    gbParticleEffect * pParticleEffect; // +0x8C
    // total size: 0x90 (144)

};
