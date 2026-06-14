#include "CTaskTpl.h"
#include "tagEffTaskParam.h"
#include "CEffObj.h"
#pragma once
// Auto-generated: CEffAudio

class CEffAudio : public CEffObj, public CTaskTpl<tagEffTaskParam,void*> {
public:
    char _gap_000[48]; // +0x0
    char m_szSoundNamePrefix[128]; // +0x30
    char m_szSoundName[128][4]; // +0xB0
    // total size: 0x2B0 (688)

};
