#include "CEffObj.h"
#pragma once
// Auto-generated: CEffgbParticle

class ParticleEffect;
class tagEffObjType;
class tagEffTaskParam;

class CEffgbParticle : public CEffObj {
public:
    char _gap_000[48]; // +0x0
    ParticleEffect * m_pEffect; // +0x30
    float m_fSize; // +0x34
    float m_fX; // +0x38
    float m_fY; // +0x3C
    float m_fZ; // +0x40
    float m_fPX; // +0x44
    float m_fPY; // +0x48
    float m_fPZ; // +0x4C
    // total size: 0x50 (80)

    virtual char CreateTask(tagEffTaskParam *p); // 0x004C8A40
    virtual int slot_2(int nVal, float a3, float a4, float a5); // 0x004C8B80
    virtual void DestroyEffect(); // 0x004D0A60
    virtual void ProcCommonTask(float dwParam); // 0x004C8BF0
    virtual void GetEditorTaskDescription(); // 0x004C8E10
    virtual CEffgbParticle * SetTimeScale(); // 0x004C8930
    virtual int sub_4C8E80(int a2); // 0x004C8E80
    virtual int RenderEffectPass(int a2); // 0x004C8E90
    virtual int sub_4C9260(int a2); // 0x004C9260
    void ReleaseEffect(); // 0x004C6980
    char Create(tagEffObjType *pType); // 0x004C6C10
    void Destroy(); // 0x004C6F20
    const char * GetEditorTaskDescription(int nIndex); // 0x004C7A70
    const char * GetEditorObjDescription(int nIndex); // 0x004C7B70
    void _CEffgbParticle(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004C8650
    void * Create(CEffgbParticle *Block, char pType); // 0x004C87A0
    int Init(int pType); // 0x004C8830
    char * Attach(char pData); // 0x004C88C0
    int * Render(); // 0x004C88D0
    void Destroy__fastcall(); // 0x004C8970
    char * DestroyEffect(char pData); // 0x004C9540
    int CreateInstance(CEffgbParticle *pSrc, int nVal, CEffgbParticle *pParam); // 0x004CEB60
    static int _nearby_4cfd40(CEffgbParticle *a1); // 0x004CFD40
};
