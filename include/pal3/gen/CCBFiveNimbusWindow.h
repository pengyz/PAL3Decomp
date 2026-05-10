#pragma once
// Auto-generated: CCBFiveNimbusWindow

#include "OpenFNWindow.h"
#include "UIFrameWnd.h"

class UIButtonEX;

class CCBFiveNimbusWindow : public UIFrameWnd {
public:
    UIButtonEX * pCtrlButton[5]; // +0x48
    UIButtonEX * pMiddle; // +0x5C
    OpenFNWindow m_OpenWindow; // +0x60
    int m_nimbus[5]; // +0x6C
    int m_state[5]; // +0x80
    int m_nimbusStep; // +0x94
    unsigned char m_bShow; // +0x98
    unsigned char m_bLock; // +0x99
    int m_counter; // +0x9C
    // total size: 0xA0 (160)

};
