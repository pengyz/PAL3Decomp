#pragma once
// Auto-generated: CEffect

#include "EEffect.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "tagPartical.h"

class CEffectSystem;
class tagEffObjType;

class CEffect {
public:
    // vtable (21 methods, order matches binary layout)

    CEffectSystem * m_pES[2]; // +0x0
    char _gap_004[4]; // +0x4
    EEffect m_eKind; // +0x8
    BYTE m_bActive; // +0xC
    BYTE m_bVisible; // +0xD
    char _gap_00E[2]; // +0xE
    double m_DeltaTime; // +0x10
    int m_nPartical; // +0x18
    tagPartical m_Partical[2048]; // +0x1C
    char _gap_201C[90112]; // +0x201C
    int m_nQuad; // +0x1801C
    gbGeomQuad m_QuadBuffer[2048]; // +0x18020
    char _gap_1A020[131072]; // +0x1A020
    int m_nQ2PIndex[2048]; // +0x3A020
    gbTexture * m_pTexture; // +0x3C020
    gbTextureArray * m_pTextureArray; // +0x3C024
    // total size: 0x3C028 (245800)

    virtual char Create(tagEffObjType *pEffObjType); // 0x004D1090
    virtual int ProcInitTask(float *dwParam, float fVal, float fVal2, float fVal3); // 0x004D0EC0
    virtual CEffect * SetTimeScale(); // 0x004D0D70
    virtual int Update(int a2); // 0x004AF760
    virtual int CreateTask(int *p); // 0x004D2080
    virtual int sub_4D2ED0(int a2); // 0x004D2ED0
    virtual char Create_3ad0(tagEffObjType *pEffObjType); // 0x004D3AD0
    virtual int Init(float *pType, float fx, float fy, float fz); // 0x004D3A50
    virtual void CreateTarget(int *pnVal); // 0x004D4340
    int CreateFromTemplate(int f); // 0x0048E780
    char UpdateState(int nVal); // 0x0048E950
    int SetRenderParam(int nVal); // 0x004BB190
    int * SetQuadParam(int nVal); // 0x004BD7A0
    CEffect(); // 0x004C6940
    void Reset(float *pfVal, float fVal, float fVal2, float fVal3); // 0x004C6A70
    void CreateOnePartical(float pPartical); // 0x004C7150
    void FillQuadByPartical(int *nParticalIndex); // 0x004C7450
    int SetParam(int nVal); // 0x004CA400
    int Render(int nVal); // 0x004CE460
    virtual int _nearby_4cfe20(int thisa, int a2, float a3, float a4, float a5); // 0x004CFE20
    virtual void _nearby_4cffb0(int thisa, float a2); // 0x004CFFB0
    void UpdateCallback(); // 0x004D0DB0
    void DestroyCallback(); // 0x004D3950
    void ReleaseResources(); // 0x0053D580
};
