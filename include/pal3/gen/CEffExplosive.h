#pragma once
// Auto-generated: CEffExplosive

#include "CEffObj.h"
#include "gbVec3D.h"
#include "tagUV.h"

class gbGeomQuad;
class gbTexture;
class gbTextureArray;
class tagExplosive;

class CEffExplosive : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffExplosive::*)(unsigned long)> {
public:
    gbGeomQuad * m_pGeomQuad; // +0x30
    tagExplosive * m_pExplosive; // +0x34
    gbTexture * m_pTexture; // +0x38
    gbTextureArray * m_pTextureArray; // +0x3C
    unsigned char m_bVisible; // +0x40
    unsigned char m_bAdditiveBlend; // +0x41
    unsigned char m_bNoZTest; // +0x42
    unsigned char m_byMaxFrame; // +0x43
    int m_nRequireLoops; // +0x44
    int m_nLoops; // +0x48
    float m_fCurFrame; // +0x4C
    unsigned long m_dwStartColor; // +0x50
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
    float m_fPowerDec; // +0x90
    float m_fFramePerSec; // +0x94
    gbVec3D m_vecRot; // +0x98
    gbVec3D m_vecPos; // +0xA4
    gbVec3D m_vecOffsetPos; // +0xB0
    float m_fResistance; // +0xBC
    tagUV m_DefaultUVSet[256]; // +0xC0
    // total size: 0x10C0 (4288)

    char Create(int a2); // 0x004C6C10
    void Destroy(); // 0x004C6F20
    int ProcCommonTask(int a2); // 0x004C7680
    static void * GetEditorTaskDescription(int a1); // 0x004C7A70
    static void * GetEditorObjDescription(int a1); // 0x004C7B70
    void InitDefaultUVSet(int a2, int a3); // 0x004C7C00
    _DWORD * LoadTexture(int a2); // 0x004C7CB0
    int CreateGeom(); // 0x004C7D40
    int UpdateExplosive(float a2, int a3); // 0x004C8370
};
