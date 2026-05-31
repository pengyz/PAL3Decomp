#include "tagEffTaskParam.h"
#pragma once
// Auto-generated: CEffAction

#include "CEffObj.h"
#include "CTaskTpl.h"

class CTaskTpl_tagEffTaskParam_CEffAction;

class CEffAction : public CEffObj, public CTaskTpl<tagEffTaskParam, unsigned long (__thiscall CEffAction::*)(unsigned long)> {
public:
    int m_nController; // +0x30
    // total size: 0x34 (52)

    void _todo_408BD0(); // 0x00408BD0
    void ResetState(); // 0x004C0640
    char AllocSegments(int nVal); // 0x004C0650
    static void UpdateFrame(float *pfVal, float fVal); // 0x004C0740
};
