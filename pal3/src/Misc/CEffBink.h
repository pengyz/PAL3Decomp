#include "CTaskTpl.h"
#include "tagEffTaskParam.h"
#include "CEffObj.h"
#pragma once
// Auto-generated: CEffBink

class CEffBink : public CEffObj, public CTaskTpl<tagEffTaskParam,void*> {
public:
    char _gap_000[48]; // +0x0
    char m_szBinkNamePrefix[128]; // +0x30
    char m_szBinkName[128]; // +0xB0
    // total size: 0x130 (304)

};
