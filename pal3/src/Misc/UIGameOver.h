#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UIGameOver

#include "UIStatic.h"
#include "gbengine/gbTexture.h"

class UIGameOver : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    gbTexture * m_pbktex; // +0x48
    UIStatic m_Blood; // +0x4C
    char _gap_050[148]; // +0x50
    float m_fTime; // +0xE4
    // total size: 0xE8 (232)

    int InitParticle(int nIndex); // 0x0044D470
    int RandomizeEffects(int nVal); // 0x0044D580
    int InitParticle2(int nIndex); // 0x0044D680
    void Create(); // 0x004500F0
    void SetupDisplay(int nVal); // 0x0052E500
    int ClearState(); // 0x00530570
    int ResetState(); // 0x005305A0
};
