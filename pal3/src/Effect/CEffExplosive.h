#include "CEffObj.h"
#pragma once
// Auto-generated: CEffExplosive

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#include "tagUV.h"

class tagExplosive;

class CEffExplosive : public CEffObj {
public:
    char _gap_000[48]; // +0x0
    gbGeomQuad * m_pGeomQuad; // +0x30
    tagExplosive * m_pExplosive; // +0x34
    gbTexture * m_pTexture; // +0x38
    gbTextureArray * m_pTextureArray; // +0x3C
    BYTE m_bVisible; // +0x40
    BYTE m_bAdditiveBlend; // +0x41
    BYTE m_bNoZTest; // +0x42
    BYTE m_byMaxFrame; // +0x43
    int m_nRequireLoops; // +0x44
    int m_nLoops; // +0x48
    float m_fCurFrame; // +0x4C
    UINT m_dwStartColor; // +0x50
    float m_fAlpha; // +0x54
    float m_fRed; // +0x58
    float m_fGreen; // +0x5C
    float m_fBlue; // +0x60
    float m_fXSize; // +0x64
    float m_fZSize; // +0x68
    int m_nXDivision; // +0x6C
    int m_nZDivision; // +0x70
    float m_fGridSize; // +0x74
    int m_nQuad; // +0x78
    float m_fMaxExplosivePower; // +0x7C
    float m_fMinExplosivePower; // +0x80
    gbVec3D m_vecExplosiveDir; // +0x84
    char _gap_088[8]; // +0x88
    float m_fPowerDec; // +0x90
    float m_fFramePerSec; // +0x94
    gbVec3D m_vecRot; // +0x98
    char _gap_09C[8]; // +0x9C
    gbVec3D m_vecPos; // +0xA4
    char _gap_0A8[8]; // +0xA8
    gbVec3D m_vecOffsetPos; // +0xB0
    char _gap_0B4[8]; // +0xB4
    float m_fResistance; // +0xBC
    tagUV m_DefaultUVSet[256]; // +0xC0
    char _tail_4C0[3072]; // +0x4C0
    // total size: 0x10C0 (4288)

    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol); // 0x004C7C00
    int * LoadTexture(char *pFileName); // 0x004C7CB0
    void CreateGeom(); // 0x004C7D40
    void UpdateExplosive(float fDeltaTime, int fTime); // 0x004C8370
};
