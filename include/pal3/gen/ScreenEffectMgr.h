#pragma once
// Auto-generated: ScreenEffectMgr

#include "ScreenFadeIn.h"
#include "ScreenFadeOut.h"
#include "ScreenFadeWhite.h"
#include "ScreenFadeWhite2.h"

class ScreenEffectMgr {
public:
    ScreenFadeIn m_fadeIn; // +0x4
    ScreenFadeOut m_fadeOut; // +0x20
    ScreenFadeWhite m_fadeWhite; // +0x38
    ScreenFadeWhite2 m_fadeWhite2; // +0x50
    struct allocator<ScreenEffect *> > > {}; // nested type stub
    allocator<ScreenEffect *> > > m_activeQueue; // +0x68
    // total size: 0x98 (152)

    void Render(); // 0x004BE4A0
    static _BYTE * GetInstance(); // 0x004BE590
};
