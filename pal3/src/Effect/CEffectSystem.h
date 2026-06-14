#pragma once
// Auto-generated: CEffectSystem

#include "gbengine/gbMesh.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "tagUVSet.h"

class CCBUI;
class CEffect;

class CEffectSystem {
public:
    // vtable (9 methods, order matches binary layout)

    gbGfxManager * m_pDisplay; // +0x0
    gbDynVertBuf * m_pVertexBuffer; // +0x4
    gbRenderEffect * m_pAdditiveBlend; // +0x8
    gbRenderEffect * m_pAlphaBlend; // +0xC
    tagUVSet m_DefaultUVSet[16]; // +0x10
    char _gap_050[192]; // +0x50
    BYTE m_bInitialized; // +0x110
    char _gap_111[3]; // +0x111
    int m_nEffect; // +0x114
    CEffect * m_pEffect[8]; // +0x118
    char _gap_11C[28]; // +0x11C
    double m_dDeltaTime; // +0x138
    double m_dTimeFund; // +0x140
    float m_fTimeFund; // +0x148
    int m_fTimeScale; // +0x14C
    int m_fWindDirection; // +0x150
    int m_fWindSpeed; // +0x154
    // total size: 0x158 (344)

    virtual int slot_0(void *Block, char a3); // 0x004C5D50
    static int slot_1(); // 0x004C5D80
    virtual int GetThreadHandle(); // 0x004C5DB0
    virtual void ReleaseParticle(); // 0x004C5DE0
    virtual int nullsub_79(int a2, int a3); // 0x004C5E70
    virtual int ProcessEffects(double time); // 0x004C5E80
    static int slot_6(); // 0x004C5E20
    virtual int UpdateEffectState(int nVal); // 0x004C6030
    virtual int * Reset(CEffectSystem *Block, char pData); // 0x004C6260
    CEffectSystem * Create(int pGfxMgr); // 0x004C5820
    CEffectSystem(int pDisplay); // 0x004C61A0
    int * _CEffectSystem(int nVal); // 0x004C6240
    bool Init(); // 0x004C6280
    void Destroy(); // 0x004C6290
    CEffect * GetEffectIndex(); // 0x004C6330
    int CreateEffect(); // 0x004C6340
    void GetEffect(); // 0x004C6350
    void DestroyEffect(); // 0x004C6360
    int * DestroyAllEffect(); // 0x004C6410
    bool IsVisible(); // 0x004C6460
    void SetVisible(float effect); // 0x004C65C0
    void HandleViewMove(gbRenderEffect *a2, int a3); // 0x004C65F0
    void Update(); // 0x004C6670
    int * FillDefaultUVSet(); // 0x004C6870
    int CreateEffect(CEffectSystem *pSrc, int nVal, CEffectSystem *pParam); // 0x004CF580
    int CreateEffectChain(CCBUI *pCBUI, HWND hDlg, unsigned int dwVal, int bReadOnly, int nVal); // 0x004E1190
};
