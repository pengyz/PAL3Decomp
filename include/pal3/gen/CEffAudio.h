#pragma once
// Auto-generated: CEffAudio

#include "CEffObj.h"

class CEffAudio : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAudio::*)(unsigned long)> {
public:
    char m_szSoundNamePrefix[128]; // +0x30
    char m_szSoundName[128][4]; // +0xB0
    // total size: 0x2B0 (688)

};
