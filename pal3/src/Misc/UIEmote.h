#include "PalScriptWaitObj.h"
#include "UIWnd.h"
#pragma once
// Auto-generated: UIEmote

#include "UIAnimateCtrl.h"

class Role;

class UIEmote : public UIWnd, public PalScriptWaitObj {
public:
    char _gap_000[76]; // +0x0
    int m_cur; // +0x4C
    UIAnimateCtrl m_ani[13]; // +0x50
    char _gap_084[2080]; // +0x84
    Role * m_role; // +0x8A4
    int m_loopcount; // +0x8A8
    int m_nLoop[13]; // +0x8AC
    // total size: 0x8E0 (2272)

    int InitParticleSlots(); // 0x0044D0B0
    UIEmote(); // 0x0044E530
    void Render(); // 0x00529870
};
