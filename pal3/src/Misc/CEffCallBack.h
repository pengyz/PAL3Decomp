#include "CTaskTpl.h"
#include "tagEffTaskParam.h"
#include "CEffObj.h"
#pragma once
// Auto-generated: CEffCallBack

class CEffCallBack : public CEffObj, public CTaskTpl<tagEffTaskParam,void*> {
public:
    char _gap_000[48]; // +0x0
    float m_fStartX; // +0x30
    float m_fStartY; // +0x34
    float m_fStartZ; // +0x38
    UINT m_dwRunningID; // +0x3C
    // total size: 0x40 (64)

};
