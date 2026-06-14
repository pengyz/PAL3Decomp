#include "CEffObj.h"
#pragma once
// Auto-generated: CEffQuad

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "tagQuad.h"
#include "tagUV.h"

class CEffQuad : public CEffObj {
public:
    char _gap_000[48]; // +0x0
    BYTE m_bActive; // +0x30
    BYTE m_bVisible; // +0x31
    BYTE m_bAniFrame; // +0x32
    BYTE m_bBillBoard; // +0x33
    BYTE m_bAdditiveBlend; // +0x34
    BYTE m_bNoZTest; // +0x35
    BYTE m_byMaxFrame; // +0x36
    char _gap_037[1]; // +0x37
    int m_nRequireLoops; // +0x38
    int m_nQuadNum; // +0x3C
    int m_nGeomQuadNum; // +0x40
    int m_nMaxQuad; // +0x44
    int m_nLastCreatedQuad; // +0x48
    tagQuad m_StartQuad; // +0x4C
    char _gap_050[76]; // +0x50
    tagQuad * m_pQuad; // +0x9C
    gbGeomQuad * m_pGeomQuad; // +0xA0
    int * m_pnG2Q; // +0xA4
    tagUV m_DefaultUVSet[256]; // +0xA8
    char _gap_4A8[3072]; // +0x4A8
    gbTexture * m_pTexture; // +0x10A8
    gbTextureArray * m_pTextureArray; // +0x10AC
    // total size: 0x10B0 (4272)

    void DestroyOneQuad(const void *n); // 0x004D1BE0
    bool SetQuad(int n); // 0x004D1CA0
    int * DestroyAllQuad(int nVal); // 0x004D1E50
    int * ToNextFrame(int nQuad); // 0x004D1F30
    int ProcessDestroyPass(int nVal); // 0x004D2E10
};
