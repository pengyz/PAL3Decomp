#pragma once
// Auto-generated: gbLightObj

#include "gbVolumeModifier.h"

class gbLightObj : public gbVolumeModifier {
public:
    struct LIGHT_TYPE {}; // nested type stub
    LIGHT_TYPE m_LightType; // +0x8
    gbColorFlt m_Color; // +0xC
    gbColorFlt m_Ambient; // +0x1C
    int m_UseDiffuse; // +0x2C
    int m_UseSpecular; // +0x30
    float m_NearStart; // +0x34
    float m_NearEnd; // +0x38
    float m_FarStart; // +0x3C
    float m_FarEnd; // +0x40
    struct DECAY_TYPE {}; // nested type stub
    DECAY_TYPE m_DecayType; // +0x44
    float m_DecayRadius; // +0x48
    struct LIGHT_SHAPE {}; // nested type stub
    LIGHT_SHAPE m_LightShape; // +0x4C
    float m_HotSize; // +0x50
    float m_Falloff; // +0x54
    float m_Aspect; // +0x58
    gbSphere m_BoundSphere; // +0x5C
    gbLight m_SysLight; // +0x6C
    int m_BakedLight; // +0xD4
    // total size: 0xD8 (216)

    void Compute(struct gbVolModNode *a2); // 0x005420A8
    float GetEffectOnPoint(const struct gbVec3D *a2, int a3); // 0x005420AE
    const struct gbSphere * GetBoundSphere(); // 0x005420B4
    int GetType(); // 0x005420BA
};
