#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UILoadingFrm

#include "UIProgressBar.h"

class UILoadingFrm : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIProgressBar m_LoadProgress; // +0x48
    char _gap_04C[240]; // +0x4C
    float m_anitime; // +0x13C
    int m_aniFlag; // +0x140
    float m_MaxValue; // +0x144
    BYTE m_isOverProgress; // +0x148
    char _tail_149[3]; // +0x149
    // total size: 0x14C (332)

    virtual ~UILoadingFrm() {}

    virtual BOOL UpdateAnimation(int nVal, int nVal2); // 0x00450900
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x00450990
    int * ctor(); // 0x00450710
    void ctor_790(); // 0x00450790
    void InitFullScreen(); // 0x004507F0
    void DestroyStatics(); // 0x00483280
    void DestroyFrames(); // 0x00483300
    int ResetState(); // 0x0052DD60
    int ResetAllState(); // 0x0052DE00
    char CheckProgress(int nVal); // 0x0052E820
};
