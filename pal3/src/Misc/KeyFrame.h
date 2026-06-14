#pragma once
// Auto-generated: KeyFrame

class CPolicy;

class KeyFrame {
public:
    CParticleSystem::EmitterAttribute emitterAttr; // +0x0
    char _gap_004[216]; // +0x4
    CPolicy * pPositionPolicy; // +0xDC
    CPolicy * pDirectionPolicy; // +0xE0
    CPolicy * pColorPolicy; // +0xE4
    CPolicy * pAlphaPolicy; // +0xE8
    CPolicy * pFramePolicy; // +0xEC
    CPolicy * pEmitterPolicy; // +0xF0
    float fTime; // +0xF4
    UINT dwReserved[4]; // +0xF8
    // total size: 0x108 (264)

};
