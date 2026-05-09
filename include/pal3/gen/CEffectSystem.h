#pragma once
// Auto-generated: CEffectSystem

#include "tagUVSet.h"

class CEffect;
class gbDynVertBuf;
class gbGfxManager;
class gbRenderEffect;

class CEffectSystem {
public:
    gbGfxManager * m_pDisplay; // +0x0
    gbDynVertBuf * m_pVertexBuffer; // +0x4
    gbRenderEffect * m_pAdditiveBlend; // +0x8
    gbRenderEffect * m_pAlphaBlend; // +0xC
    tagUVSet m_DefaultUVSet[16]; // +0x10
    unsigned char m_bInitialized; // +0x110
    int m_nEffect; // +0x114
    CEffect * m_pEffect[8]; // +0x118
    double m_dDeltaTime; // +0x138
    double m_dTimeFund; // +0x140
    float m_fTimeFund; // +0x148
    float m_fTimeScale; // +0x14C
    float m_fWindDirection; // +0x150
    float m_fWindSpeed; // +0x154
    // total size: 0x158 (344)

    CEffectSystem(int a2); // 0x004C61A0
    ~CEffectSystem(); // 0x004C6240
    _DWORD * Reset(_DWORD *Block, char a2); // 0x004C6260
    int Init(); // 0x004C6280
    char Destroy(int a2, int a3, int a4, int a5, int a6); // 0x004C6290
    static int GetEffectIndex(); // 0x004C6330
    static int CreateEffect(); // 0x004C6340
    static void GetEffect(); // 0x004C6350
    static void DestroyEffect(); // 0x004C6360
    int DestroyEffect(); // 0x004C6370
    static void * DestroyAllEffect(); // 0x004C6410
    char IsVisible(); // 0x004C6460
    void SetVisible(float a2); // 0x004C65C0
    void HandleViewMove(int a2); // 0x004C65F0
    char Update(); // 0x004C6670
    _DWORD * FillDefaultUVSet(); // 0x004C6870
};
