class tagEffObjType;

#pragma once
// Auto-generated: CEffObj
#include "pal3/ida_types.h"

class CEffMgr;
class tagEffObjType;

class CEffObj {
public:
    // vtable (15 methods, order matches binary layout)

    CEffMgr * m_pEM; // +0x4
    _BYTE m_bIdle; // +0x8
    char _tail_009[3]; // +0x9
    // total size: 0xC (12)

    virtual void slot_0(); // slot0 0x004c0620
    virtual char Create(tagEffObjType *); // slot1 0x004c0600
    virtual void ResetState(int, int, int, int); // slot2 0x004c0610
    virtual void DestroyEffect(); // slot3 0x00401800
    virtual void RenderScenePass(); // slot4 0x00401800
    virtual void UpdateFrame(float); // slot5 0x004af760
    virtual void Destroy(); // slot6 0x00401800
    virtual void* AllocEffect(); // slot7 0x0055434f
    virtual char OnTest(); // slot8 0x004c0500
    virtual BOOL Update(int); // slot9 0x004af760
    virtual const char * GetEditorObjDescription(int); // slot10 0x004c0510
    virtual void GetEffect(float); // slot11 0x004af760
    virtual void RenderEffectPass(float); // slot12 0x004af760
    virtual void UpdateParticles(); // slot13 0x00401800
    virtual const char * GetEditorTaskDescription(int); // slot14 0x004c0510

};
