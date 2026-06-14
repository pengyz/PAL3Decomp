#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UITitle

class PalScript;

class UITitle : public UIFrameWnd {
public:
    char _gap_000[3288]; // +0x0
    int m_hEffect; // +0xCD8
    int m_dwEffectTick; // +0xCDC
    int m_dwTimerTick; // +0xCE0
    BYTE m_bTimerActive; // +0xCE4
    char _gap_CE5[3]; // +0xCE5
    BYTE m_bTimerDone; // +0xCE8
    BYTE m_bTimerProcessed; // +0xCE9
    char _gap_CEA[4106]; // +0xCEA
    int m_nTitleStage; // +0x1CF4
    char _gap_1CF8[1044]; // +0x1CF8
    int m_nTitleScript; // +0x210C
    char _tail_2110[772]; // +0x2110
    // total size: 0x2414 (9236)

    virtual ~UITitle() {}

    virtual int Render(); // 0x0044B460
    virtual int RunFrame(struct PalScript *p, int nVal); // 0x0044B0F0
    virtual int OnCommand(int nVal, char *pszBuf, int nVal2); // 0x0044B710
    UITitle(); // 0x0044AB90
    void _UITitle(); // 0x0044ACE0
};
