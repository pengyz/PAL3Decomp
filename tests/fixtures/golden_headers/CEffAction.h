class tagEffObjType;

#pragma once
// Auto-generated: CEffAction
#include "pal3/ida_types.h"

#include "Misc/CEffObj.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffAction.h"

class tagEffObjType;

class CEffAction : public CEffObj, public CTaskTpl_tagEffTaskParam_CEffAction {
public:
    int m_nController; // +0x30
    // total size: 0x34 (52)

    virtual ~CEffAction();
    virtual char Create(tagEffObjType *); // slot1 0x004c0650
    virtual void ResetState(int, int, int, int); // slot2 0x004c0640
    virtual void DestroyEffect(); // slot3 0x00408bd0
    virtual void RenderScenePass(); // slot4 0x00408bd0
    virtual void UpdateFrame(float); // slot5 0x004c0740
    virtual void Destroy(); // slot6 0x00408bd0
    virtual void* AllocEffect(); // slot7 0x004c0520
    virtual char OnTest(); // slot8 0x004c0500
    virtual BOOL Update(int); // slot9 0x004c0920
    virtual const char * GetEditorObjDescription(int); // slot10 0x004c0510
    virtual void GetEffect(float); // slot11 0x004af760
    virtual void RenderEffectPass(float); // slot12 0x004c09e0
    virtual void UpdateParticles(); // slot13 0x004c15d0
    virtual const char * GetEditorTaskDescription(int); // slot14 0x004c1270

    virtual char * _sdtor_call_dtor(char a2); // 0x004c0540
    virtual char slot_1(tagEffObjType *nVal); // 0x004c0650
    virtual void NullCallback(); // 0x00408bd0
    virtual const char * slot_14(int a2); // 0x004c1270
};
