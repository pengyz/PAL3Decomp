#pragma once
// Auto-generated: CEffect

#include "EEffect.h"
#include "tagPartical.h"

class CEffectSystem;
class gbTextureArray;

class CEffect {
public:
    CEffectSystem * m_pES; // +0x0
    EEffect m_eKind; // +0x8
    unsigned char m_bActive; // +0xC
    unsigned char m_bVisible; // +0xD
    double m_DeltaTime; // +0x10
    int m_nPartical; // +0x18
    tagPartical m_Partical[2048]; // +0x1C
    int m_nQuad; // +0x1801C
    gbGeomQuad m_QuadBuffer[2048]; // +0x18020
    int m_nQ2PIndex[2048]; // +0x3A020
    gbTexture * m_pTexture; // +0x3C020
    gbTextureArray * m_pTextureArray; // +0x3C024
    // total size: 0x3C028 (245800)

    CEffect(); // 0x004C6940
    int Reset(int a2, float a3, float a4, float a5); // 0x004C6A70
    void CreateOnePartical(float a2); // 0x004C7150
    void FillQuadByPartical(_DWORD *a2); // 0x004C7450
    int SetParam(int a2); // 0x004CA400
    int Render(int a2); // 0x004CE460
};
