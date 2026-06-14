#include "CTaskTpl.h"
#include "tagEffTaskParam.h"
#include "CEffObj.h"
#pragma once
// Auto-generated: CEffAction

class CEffAction : public CEffObj, public CTaskTpl<tagEffTaskParam,void*> {
public:
    char _gap_000[48]; // +0x0
    int m_nController; // +0x30
    // total size: 0x34 (52)

    virtual char * ExecutePasses(char a2); // 0x004C0540
    virtual char AllocSegments(int nVal); // 0x004C0650
    virtual void ResetState(); // 0x004C0640
    void NullCallback(void *pData); // 0x00408BD0
    virtual void UpdateFrame(float fVal); // 0x004C0740
    virtual void AllocRenderTarget(); // 0x004C0520
    static int OnTest(); // 0x004C0500
    virtual void PrepareEffect(); // 0x004C0920
    virtual void RenderScene(); // 0x004C09E0
};
