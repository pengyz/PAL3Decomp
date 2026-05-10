#pragma once
// Auto-generated: CEffGrid

#include "CEffObj.h"
#include "tagUV.h"

class gbTextureArray;

class CEffGrid : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffGrid::*)(unsigned long)> {
public:
    gbGeomQuad * m_pGeomQuad; // +0x30
    gbVec3D * m_pMesh; // +0x34
    gbVec3D * m_pMesh2; // +0x38
    gbTexture * m_pTexture; // +0x3C
    gbTextureArray * m_pTextureArray; // +0x40
    unsigned char m_bVisible; // +0x44
    unsigned char m_bAdditiveBlend; // +0x45
    unsigned char m_bNoZTest; // +0x46
    unsigned char m_byMaxFrame; // +0x47
    int m_nRequireLoops; // +0x48
    int m_nLoops; // +0x4C
    float m_fCurFrame; // +0x50
    unsigned long m_dwStartColor; // +0x54
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
    gbVec3D m_vecPos; // +0xA0
    gbVec3D m_vecOffsetPos; // +0xAC
    tagUV m_DefaultUVSet[256]; // +0xB8
    // total size: 0x10B8 (4280)

    CEffGrid(); // 0x004C9610
    ~CEffGrid(); // 0x004C9650
    char Create(int a2); // 0x004C98F0
    static void * GetEditorObjDescription(int a1); // 0x004CA9A0
};
