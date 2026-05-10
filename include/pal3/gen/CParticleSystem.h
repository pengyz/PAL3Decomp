#pragma once
// Auto-generated: CParticleSystem

class CEmitter;
class CPolicy;

class CParticleSystem {
public:
    int _bVisible; // +0x0
    int _bPlay; // +0x4
    int _bCycle; // +0x8
    int _bManual; // +0xC
    struct allocator<char> > {}; // nested type stub
    allocator<char> > _strParticleName; // +0x10
    unsigned long _dwParticleId; // +0x20
    CPolicy * _pPositionPolicy; // +0x24
    CPolicy * _pDirectionPolicy; // +0x28
    CPolicy * _pColorPolicy; // +0x2C
    CPolicy * _pAlphaPolicy; // +0x30
    CPolicy * _pFramePolicy; // +0x34
    CPolicy * _pEmitterPolicy; // +0x38
    struct ParticleUnit * {}; // nested type stub
    ParticleUnit * _pParticles; // +0x3C
    CEmitter * _pEmitter; // +0x40
    struct allocator<KeyFrame *> > {}; // nested type stub
    allocator<KeyFrame *> > _KeyFrames; // +0x44
    int _nNumOfParticles; // +0x54
    int _nMaxNum; // +0x58
    unsigned long _dwNumOfKeyFrames; // +0x5C
    unsigned long _dwNumOfUnitFrames; // +0x60
    int _nCurrFrame; // +0x64
    int _nLastFrame; // +0x68
    float _fTimeCounter; // +0x6C
    float _fEmitDecPart; // +0x70
    unsigned long _dwVBFlush; // +0x74
    gbMatrix4 _matTransform; // +0x78
    float _fWidthScale; // +0xB8
    float _fHeightScale; // +0xBC
    struct TexCoordQuad> > {}; // nested type stub
    TexCoordQuad> > _TexCoordData; // +0xC0
    gbTexture * _pTexture; // +0xD0
    gbRenderEffect * _pRenderEffect; // +0xD4
    gbGfxManager * _pGfxMgr; // +0xD8
    // total size: 0xDC (220)

};
