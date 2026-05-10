#pragma once
// Auto-generated: gbDropGroup

class gbDropUnit;

class gbDropGroup {
public:
    int m_MaxUnit; // +0x8
    int m_nAliveUnit; // +0xC
    float m_UnitSize; // +0x10
    float m_Range; // +0x14
    int m_EmitRate; // +0x18
    float m_MinLife; // +0x1C
    float m_MaxLife; // +0x20
    float m_MinEmitVel; // +0x24
    float m_MaxEmitVel; // +0x28
    float m_MinHeight; // +0x2C
    float m_MaxHeight; // +0x30
    double m_LastFrameTime; // +0x38
    float m_LeftTimeAccum; // +0x40
    gbDropUnit * m_pUnits; // +0x44
    gbTexture * m_pTex; // +0x48
    gbRenderEffect * m_pEffect; // +0x4C
    // total size: 0x50 (80)

};
