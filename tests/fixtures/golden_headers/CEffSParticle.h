class tagEffObjType;

#pragma once
// Auto-generated: CEffSParticle
#include "pal3/ida_types.h"

#include "Misc/CEffObj.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffSParticle.h"
#include "gbengine/gbengine_types.h"

class CEffCylinder;
class CParticleEffect;

class CEffSParticle : public CEffObj, public CTaskTpl_tagEffTaskParam_CEffSParticle {
public:
    CParticleEffect * m_pEffect; // +0x30
    gbVec3D m_vecPos; // +0x34
    float m_fX; // +0x40
    float m_fY; // +0x44
    float m_fZ; // +0x48
    float m_fPX; // +0x4C
    float m_fPY; // +0x50
    float m_fPZ; // +0x54
    float m_fRotX; // +0x58
    float m_fRotY; // +0x5C
    float m_fRotZ; // +0x60
    // total size: 0x64 (100)

    virtual ~CEffSParticle();
    virtual char Create(tagEffObjType *); // slot1 0x004c0650
    virtual void ResetState(int, int, int, int); // slot2 0x004d33a0
    virtual void DestroyEffect(); // slot3 0x00408bd0
    virtual void RenderScenePass(); // slot4 0x00408bd0
    virtual void UpdateFrame(float); // slot5 0x004d4fc0
    virtual void Destroy(); // slot6 0x00408bd0
    virtual void* AllocEffect(); // slot7 0x004d4ee0
    virtual char OnTest(); // slot8 0x004c0500
    virtual BOOL Update(int); // slot9 0x004af760
    virtual const char * GetEditorObjDescription(int); // slot10 0x004c0510
    virtual void GetEffect(float); // slot11 0x004af760
    virtual void RenderEffectPass(float); // slot12 0x004d51b0
    virtual void UpdateParticles(); // slot13 0x004c15d0
    virtual const char * GetEditorTaskDescription(int); // slot14 0x004d5620

    CEffSParticle(); // 0x004d4ee0
    virtual void Init(int pType); // 0x004d51b0
    virtual const char * GetEffTypeData(int fCurTime); // 0x004d5620
    int Attach(int nVal); // 0x004d53e0
    int Render(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004d56b0
    const char GetEditorTaskDescription_58d0(int); // [G1b] 0x004d58d0

};
