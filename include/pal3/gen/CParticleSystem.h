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
    char _strParticleName[16]; // +0x10 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    DWORD _dwParticleId; // +0x20
    CPolicy * _pPositionPolicy; // +0x24
    CPolicy * _pDirectionPolicy; // +0x28
    CPolicy * _pColorPolicy; // +0x2C
    CPolicy * _pAlphaPolicy; // +0x30
    CPolicy * _pFramePolicy; // +0x34
    CPolicy * _pEmitterPolicy; // +0x38
    char _pParticles[4]; // +0x3C (CParticleSystem::ParticleUnit *)
    CEmitter * _pEmitter; // +0x40
    char _KeyFrames[16]; // +0x44 (std::vector<KeyFrame *,std::allocator<KeyFrame *> >)
    int _nNumOfParticles; // +0x54
    int _nMaxNum; // +0x58
    DWORD _dwNumOfKeyFrames; // +0x5C
    DWORD _dwNumOfUnitFrames; // +0x60
    int _nCurrFrame; // +0x64
    int _nLastFrame; // +0x68
    float _fTimeCounter; // +0x6C
    float _fEmitDecPart; // +0x70
    DWORD _dwVBFlush; // +0x74
    gbMatrix4 _matTransform; // +0x78
    float _fWidthScale; // +0xB8
    float _fHeightScale; // +0xBC
    char _TexCoordData[16]; // +0xC0 (std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >)
    gbTexture * _pTexture; // +0xD0
    gbRenderEffect * _pRenderEffect; // +0xD4
    gbGfxManager * _pGfxMgr; // +0xD8
    // total size: 0xDC (220)

};
