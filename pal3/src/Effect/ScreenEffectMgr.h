#pragma once
// Auto-generated: ScreenEffectMgr

#include "ScreenFadeIn.h"
#include "ScreenFadeOut.h"
#include "ScreenFadeWhite.h"
#include "ScreenFadeWhite2.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbVisNode.h"

class ScreenEffect;

class ScreenEffectMgr {
public:
    // vtable (11 methods, order matches binary layout)

    void * m_pVtable; // +0x0
    ScreenFadeIn m_fadeIn; // +0x4
    char _gap_008[24]; // +0x8
    ScreenFadeOut m_fadeOut; // +0x20
    char _gap_024[20]; // +0x24
    ScreenFadeWhite m_fadeWhite; // +0x38
    char _gap_03C[20]; // +0x3C
    ScreenFadeWhite2 m_fadeWhite2; // +0x50
    char _gap_054[20]; // +0x54
    char m_activeQueue[4]; // +0x68
    int m_pAllocBlock; // +0x6C
    int m_pAllocBlockEnd; // +0x70
    int m_pAllocPos; // +0x74
    int m_pAllocSlot; // +0x78
    int m_pAllocRest; // +0x7C
    int m_nAllocFlag1; // +0x80
    int m_nAllocFlag2; // +0x84
    int m_fAllocFactor; // +0x88
    char * m_pEffect; // +0x8C
    char _gap_090[4]; // +0x90
    int m_nEffectCount; // +0x94
    // total size: 0x98 (152)

    virtual void sub_54210E(struct gbSphere *a2); // 0x0054210E
    virtual int sub_5420DE(struct gbAABBox *a2); // 0x005420DE
    virtual void sub_5420D8(int a2); // 0x005420D8
    virtual gbVFileSystem * LoadResources(int nVal); // 0x004BEFB0
    virtual void CleanupTextures(); // 0x004BF170
    virtual void UpdateAnimation(float fVal); // 0x004BF4F0
    virtual int GetPageIndex(int nVal); // 0x004BF680
    virtual int SetFadeParams(int nVal); // 0x004BF6C0
    int IsScriptDelNeeded(); // 0x004BDF60
    void StartFade(); // 0x004BDF70
    void ClearAllEffects(); // 0x004BE080
    int ProcessEffect(); // 0x004BE1A0
    void UpdateFrontEffect(); // 0x004BE4A0
    ScreenEffect * GetInstance(); // 0x004BE590
    bool IsFadeWhiteHolding(); // 0x004BE5E0
    int DrainQueue(); // 0x004BE5F0
    char * AllocEffectBlock(); // 0x004BE6B0
    int * GetFadeFlags(); // 0x004BE810
    void RenderFadeOut(); // 0x004BE920
    void ToggleFade(float fVal); // 0x004BE9C0
    void StartFadeIn(); // 0x004BE9E0
    void RenderFadeIn(); // 0x004BEAB0
    void RenderFadeWhiteOut(); // 0x004BEC00
    void RenderFadeWhiteIn(); // 0x004BED50
    ScreenEffectMgr(); // 0x004BEE60
    int * ResetFadeState(); // 0x004BF760
    int ProcessInstance(); // 0x0052F310
    BOOL IsFadeActive(); // 0x0052F330
};
