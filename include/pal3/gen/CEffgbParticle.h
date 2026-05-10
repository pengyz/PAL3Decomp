#pragma once
// Auto-generated: CEffgbParticle

#include "CEffObj.h"
#include "CTaskTpl.h"

class ParticleEffect;

class CEffgbParticle : public CEffObj, public CTaskTpl {
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

    ~CEffgbParticle(); // 0x004C8650
    void * Create(CEffgbParticle *Block, char a2); // 0x004C87A0
    int Init(int a2); // 0x004C8830
    char * Attach(char a2); // 0x004C88C0
    _DWORD * Render(); // 0x004C88D0
    static _DWORD * SetTimeScale(); // 0x004C8930
    static void Destroy(_DWORD *a1); // 0x004C8970
    char CreateTask(int a2); // 0x004C8A40
    void ProcCommonTask(float a2); // 0x004C8BF0
    void GetEditorTaskDescription(); // 0x004C8E10
};
