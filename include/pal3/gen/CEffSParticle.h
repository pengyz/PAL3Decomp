#pragma once
// Auto-generated: CEffSParticle

#include "CEffObj.h"
#include "CTaskTpl.h"

class CParticleEffect;

class CEffSParticle : public CEffObj, public CTaskTpl {
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

    int Create(float a2); // 0x004D4FC0
    void Init(_DWORD *a2); // 0x004D51B0
    int Attach(int a2); // 0x004D53E0
    static void * Update(int a1); // 0x004D5620
    int Render(int a2, int a3, int a4, _DWORD *a5, int a6, int a7); // 0x004D56B0
    void * SetTimeScale(CEffSParticle *Block, char a2); // 0x004D5790
    char * CreateTask(char a2); // 0x004D5860
    int GetEditorTaskDescription(unsigned __int8 *a2); // 0x004D58D0
};
