#include "CEffObj.h"
#pragma once
// Auto-generated: CEffGrid

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#include "tagUV.h"

class tagEffObjType;

class CEffGrid : public CEffObj {
public:
    char _gap_000[48]; // +0x0
    gbGeomQuad * m_pGeomQuad; // +0x30
    gbVec3D * m_pMesh; // +0x34
    gbVec3D * m_pMesh2; // +0x38
    gbTexture * m_pTexture; // +0x3C
    gbTextureArray * m_pTextureArray; // +0x40
    BYTE m_bVisible; // +0x44
    BYTE m_bAdditiveBlend; // +0x45
    BYTE m_bNoZTest; // +0x46
    BYTE m_byMaxFrame; // +0x47
    int m_nRequireLoops; // +0x48
    int m_nLoops; // +0x4C
    float m_fCurFrame; // +0x50
    UINT m_dwStartColor; // +0x54
    float m_fAlpha; // +0x58
    float m_fRed; // +0x5C
    float m_fGreen; // +0x60
    float m_fBlue; // +0x64
    float m_fXSize; // +0x68
    float m_fZSize; // +0x6C
    int m_nXDivision; // +0x70
    int m_nZDivision; // +0x74
    float m_fGridSize; // +0x78
    int m_nQuad; // +0x7C
    float m_fWavePower; // +0x80
    float m_fWaveSpeed; // +0x84
    float m_fFlapPower; // +0x88
    float m_fFlapSpeed; // +0x8C
    float m_fFramePerSec; // +0x90
    gbVec3D m_vecRot; // +0x94
    char _gap_098[8]; // +0x98
    gbVec3D m_vecPos; // +0xA0
    char _gap_0A4[8]; // +0xA4
    gbVec3D m_vecOffsetPos; // +0xAC
    char _gap_0B0[8]; // +0xB0
    tagUV m_DefaultUVSet[256]; // +0xB8
    char _tail_4B8[3072]; // +0x4B8
    // total size: 0x10B8 (4280)

    virtual char Create(tagEffObjType *pType); // 0x004C98F0
    virtual int Init(float *pfVal, float fVal, float fVal2, float fVal3); // 0x004C9750
    virtual int slot_5(int a2); // 0x004C9ED0
    virtual int slot_6(int a2, int a3); // 0x004C9CA0
    CEffGrid(); // 0x004C9610
    virtual int DispatchByType(int a2); // 0x004CAAB0
    virtual int RenderEffectPass(int a2); // 0x004CA1D0
    virtual const char * GetEditorObjDescription(int nIndex); // 0x004CA9A0
    void _CEffGrid(); // 0x004C9650
};
