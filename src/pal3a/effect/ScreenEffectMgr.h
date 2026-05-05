#ifndef PAL3A_SCREENEFFECTMGR_H
#define PAL3A_SCREENEFFECTMGR_H

#include "pal3a_types.h"

class ScreenEffectMgr {
public:
    char _data[152];

    bool IsFadingOut();
    ~ScreenEffectMgr();
    ScreenEffectMgr * Inst();
    void Render();
    void Update(float delta);
    ScreenEffect * QueueEffect(SCR_EFT_KIND kind);
    void Clear();
    ScreenEffectMgr();
};

#endif // PAL3A_SCREENEFFECTMGR_H
