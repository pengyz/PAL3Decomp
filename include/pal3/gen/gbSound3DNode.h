#pragma once
// Auto-generated: gbSound3DNode

class h3DPOBJECT;

class gbSound3DNode {
public:
    gbSoundData * pData; // +0x0
    h3DPOBJECT * hSample; // +0x4
    gbVec3D Position; // +0x8
    gbVec3D Velocity; // +0x14
    gbVec3D Orientation; // +0x20
    int EffectType; // +0x2C
    float Volume; // +0x30
    int nLoop; // +0x34
    float MinDist; // +0x38
    float MaxDist; // +0x3C
    gbAudioManager * pAudioMgr; // +0x0
    // total size: 0x40 (64)

};
