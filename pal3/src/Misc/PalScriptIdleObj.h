#include "PalScriptWaitObj.h"
#pragma once
// Auto-generated: PalScriptIdleObj

#include "gbengine/gbVFileSystem.h"

class UISceneFrm;

class PalScriptIdleObj : public PalScriptWaitObj {
public:
    char _gap_000[8]; // +0x0
    int _todo_0; // +0x8
    float m_passedtime; // +0xC
    // total size: 0x10 (16)

    gbVFileSystem * LoadScriptTexture(int nTexID, int nParam); // 0x0044A970
    int UpdateWait(const void *pData, unsigned int dwVal); // 0x00453C00
    UISceneFrm * ResetTimers(); // 0x00535600
};
