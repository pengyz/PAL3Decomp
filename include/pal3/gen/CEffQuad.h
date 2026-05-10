#pragma once
// Auto-generated: CEffQuad

#include "CEffObj.h"
#include "tagQuad.h"
#include "tagUV.h"

class gbTextureArray;

class CEffQuad : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuad::*)(unsigned long)> {
public:
    unsigned char m_bActive; // +0x30
    unsigned char m_bVisible; // +0x31
    unsigned char m_bAniFrame; // +0x32
    unsigned char m_bBillBoard; // +0x33
    unsigned char m_bAdditiveBlend; // +0x34
    unsigned char m_bNoZTest; // +0x35
    unsigned char m_byMaxFrame; // +0x36
    int m_nRequireLoops; // +0x38
    int m_nQuadNum; // +0x3C
    int m_nGeomQuadNum; // +0x40
    int m_nMaxQuad; // +0x44
    int m_nLastCreatedQuad; // +0x48
    tagQuad m_StartQuad; // +0x4C
    tagQuad * m_pQuad; // +0x9C
    gbGeomQuad * m_pGeomQuad; // +0xA0
    int * m_pnG2Q; // +0xA4
    tagUV m_DefaultUVSet[256]; // +0xA8
    gbTexture * m_pTexture; // +0x10A8
    gbTextureArray * m_pTextureArray; // +0x10AC
    // total size: 0x10B0 (4272)

    char Create(int a2); // 0x004D1090
    char DestroyOneQuad(const void *a2); // 0x004D1BE0
    int SetQuad(int a2); // 0x004D1CA0
    _DWORD * DestroyAllQuad(int a2); // 0x004D1E50
    _DWORD * ToNextFrame(int a2); // 0x004D1F30
    int CreateTask(_DWORD *a2); // 0x004D2080
};
