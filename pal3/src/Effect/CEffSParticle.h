#include "CEffObj.h"
#pragma once
// Auto-generated: CEffSParticle

#include "gbengine/gbengine_types.h"

class CParticleEffect;

class CEffSParticle : public CEffObj {
public:
    char _gap_000[48]; // +0x0
    CParticleEffect * m_pEffect; // +0x30
    gbVec3D m_vecPos; // +0x34
    char _gap_038[8]; // +0x38
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

    virtual int Create(float pType); // 0x004D4FC0
    CEffSParticle(); // 0x004D4EE0
    virtual void Init(int *pType); // 0x004D51B0
    virtual void UpdateParticles(); // 0x004C15D0
    virtual int * Update(float fCurTime); // 0x004D5620
    void _CEffSParticle(); // 0x004D4F20
    int Attach(int nVal); // 0x004D53E0
    int Render(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004D56B0
    void * SetTimeScale(CEffSParticle *Block, char fTimeScale); // 0x004D5790
    char * CreateTask(char p); // 0x004D5860
    const char * GetEditorTaskDescription(int nIndex); // 0x004D58D0
};
