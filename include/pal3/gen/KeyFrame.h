#pragma once
// Auto-generated: KeyFrame

class CPolicy;

class KeyFrame {
public:
    char emitterAttr[220]; // +0x0 (CParticleSystem::EmitterAttribute)
    CPolicy * pPositionPolicy; // +0xDC
    CPolicy * pDirectionPolicy; // +0xE0
    CPolicy * pColorPolicy; // +0xE4
    CPolicy * pAlphaPolicy; // +0xE8
    CPolicy * pFramePolicy; // +0xEC
    CPolicy * pEmitterPolicy; // +0xF0
    float fTime; // +0xF4
    unsigned long dwReserved[4]; // +0xF8
    // total size: 0x108 (264)

};
