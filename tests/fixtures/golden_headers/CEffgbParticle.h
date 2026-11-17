class tagEffObjType;

#pragma once
// Auto-generated: CEffgbParticle
#include "pal3/ida_types.h"

#include "Misc/CEffObj.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffgbParticle.h"

class ParticleEffect;
class tagEffObjType;

class CEffgbParticle : public CEffObj, public CTaskTpl_tagEffTaskParam_CEffgbParticle {
public:
    ParticleEffect * m_pEffect; // +0x30
    float m_fSize; // +0x34
    float m_fX; // +0x38
    float m_fY; // +0x3C
    float m_fZ; // +0x40
    float m_fPX; // +0x44
    float m_fPY; // +0x48
    float m_fPZ; // +0x4C
    // total size: 0x50 (80)

    virtual ~CEffgbParticle() {}

    virtual char Create(tagEffObjType *); // slot1 0x004c8a40
    virtual void ResetState(int, int, int, int); // slot2 0x004c8b80
    virtual void DestroyEffect(); // slot3 0x004d0a60
    virtual void RenderScenePass(); // slot4 0x00408bd0
    virtual void UpdateFrame(float); // slot5 0x004c8bf0
    virtual void Destroy(); // slot6 0x004c8e10
    virtual void* AllocEffect(); // slot7 0x004c8930
    virtual char OnTest(); // slot8 0x004c0500
    virtual BOOL Update(int); // slot9 0x004af760
    virtual const char * GetEditorObjDescription(int); // slot10 0x004c0510
    virtual void GetEffect(float); // slot11 0x004c8e80
    virtual void RenderEffectPass(float); // slot12 0x004c8e90
    virtual void UpdateParticles(); // slot13 0x004c15d0
    virtual const char * GetEditorTaskDescription(int); // slot14 0x004c9260

    virtual char CreateTask(tagEffObjType *p); // 0x004c8a40
    virtual void slot_2(int nVal, int a3, int a4, int a5); // 0x004c8b80
    virtual void ProcCommonTask(float dwParam); // 0x004c8bf0
    virtual void RenderEffectTexture(); // 0x004c8e10
    virtual void * SetTimeScale(); // 0x004c8930
    virtual const char * GetParticleType(int a2); // 0x004c9260
    virtual char * _sdtor_call_dtor(char pData); // 0x004c9540
    void ReleaseEffect(); // 0x004c6980
    void SetData(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004c8650
    void * _scalar_deleting_destructor_(CEffgbParticle *Block, char pType); // 0x004c87a0
    int Init(int pType); // 0x004c8830
    void _todo_88B0(); // 0x004c88b0
    virtual char * Attach(char pData); // 0x004c88c0
    int * Render(); // 0x004c88d0
    void Destroy__fastcall(); // 0x004c8970
    int CreateInstance(CEffgbParticle *pSrc, int nVal, CEffgbParticle *pParam); // 0x004ceb60
    static int DestroyEffect_FD40(CEffgbParticle *a1); // 0x004cfd40
};
