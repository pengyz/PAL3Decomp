#pragma once
// Auto-generated: ScreenEffectMgr

#include "ScreenFadeIn.h"

class ScreenFadeOut;
class ScreenFadeWhite;
class ScreenFadeWhite2;

class ScreenEffectMgr {
public:
    ScreenFadeIn m_fadeIn; // +0x4
    ScreenFadeOut m_fadeOut; // +0x20
    ScreenFadeWhite m_fadeWhite; // +0x38
    ScreenFadeWhite2 m_fadeWhite2; // +0x50
    char m_activeQueue[48]; // +0x68 (std::queue<ScreenEffect *,std::deque<ScreenEffect *,std::allocator<ScreenEffect *> > >)
    // total size: 0x98 (152)

    void Render(); // 0x004BE4A0
    static ScreenEffect * GetInstance(); // 0x004BE590
};
