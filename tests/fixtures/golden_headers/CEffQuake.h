class tagEffObjType;

#pragma once
// Auto-generated: CEffQuake
#include "pal3/ida_types.h"

#include "Misc/CEffObj.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffQuake.h"

class CEffQuake : public CEffObj, public CTaskTpl_tagEffTaskParam_CEffQuake {
public:
    // total size: 0x30 (48)

    virtual ~CEffQuake() {}

    virtual char Create(tagEffObjType *); // slot1 0x004c0650
    virtual void ResetState(int, int, int, int); // slot2 0x004d33a0
    virtual void DestroyEffect(); // slot3 0x00408bd0
    virtual void RenderScenePass(); // slot4 0x00408bd0
    virtual void UpdateFrame(float); // slot5 0x004c29a0
    virtual void Destroy(); // slot6 0x00408bd0
    virtual void* AllocEffect(); // slot7 0x004d32c0
    virtual char OnTest(); // slot8 0x004c0500
    virtual BOOL Update(int); // slot9 0x004af760
    virtual const char * GetEditorObjDescription(int); // slot10 0x004c0510
    virtual void GetEffect(float); // slot11 0x004af760
    virtual void RenderEffectPass(float); // slot12 0x004d33b0
    virtual void UpdateParticles(); // slot13 0x004c15d0
    virtual const char * GetEditorTaskDescription(int); // slot14 0x004d3660

    virtual void _sdtor_call_dtor(int nVal1); // 0x004d32e0
    virtual const char * slot_14(int a2); // 0x004d3660
};
