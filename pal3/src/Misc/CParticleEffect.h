#pragma once
// Auto-generated: CParticleEffect

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"

class CParticleEffect {
public:
    int _bPlay; // +0x0
    float _fTimeScale; // +0x4
    int _tBlendType; // +0x8
    float _fTime; // +0xC
    char _ParticleSystems[16]; // +0x10
    gbRenderEffect * _pRenderEffect; // +0x20
    gbGfxManager * _pGfxMgr; // +0x24
    UINT _dwReserved[4]; // +0x28
    // total size: 0x38 (56)

};
