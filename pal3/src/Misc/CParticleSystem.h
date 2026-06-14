#pragma once
// Auto-generated: CParticleSystem

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"

class CEmitter;
class CParticleSystem_ParticleUnit;
class CPolicy;

class CParticleSystem {
public:
    struct EmitterAttribute;


    struct EmitterAttribute {
        _BYTE _tail_000[220];
    };
    int _bVisible; // +0x0
    int _bPlay; // +0x4
    int _bCycle; // +0x8
    int _bManual; // +0xC
    char _strParticleName[16]; // +0x10
    UINT _dwParticleId; // +0x20
    CPolicy * _pPositionPolicy; // +0x24
    CPolicy * _pDirectionPolicy; // +0x28
    CPolicy * _pColorPolicy; // +0x2C
    CPolicy * _pAlphaPolicy; // +0x30
    CPolicy * _pFramePolicy; // +0x34
    CPolicy * _pEmitterPolicy; // +0x38
    CParticleSystem_ParticleUnit * _pParticles; // +0x3C
    CEmitter * _pEmitter; // +0x40
    char _KeyFrames[16]; // +0x44
    int _nNumOfParticles; // +0x54
    int _nMaxNum; // +0x58
    UINT _dwNumOfKeyFrames; // +0x5C
    UINT _dwNumOfUnitFrames; // +0x60
    int _nCurrFrame; // +0x64
    int _nLastFrame; // +0x68
    float _fTimeCounter; // +0x6C
    float _fEmitDecPart; // +0x70
    UINT _dwVBFlush; // +0x74
    gbMatrix4 _matTransform; // +0x78
    char _gap_07C[60]; // +0x7C
    float _fWidthScale; // +0xB8
    float _fHeightScale; // +0xBC
    char _TexCoordData[16]; // +0xC0
    gbTexture * _pTexture; // +0xD0
    gbRenderEffect * _pRenderEffect; // +0xD4
    gbGfxManager * _pGfxMgr; // +0xD8
    // total size: 0xDC (220)

};
