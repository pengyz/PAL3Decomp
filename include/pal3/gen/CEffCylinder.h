#pragma once
// Auto-generated: CEffCylinder

#include "CEffObj.h"
#include "tagUV.h"

class gbTextureArray;

class CEffCylinder : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCylinder::*)(unsigned long)> {
public:
    gbGeomQuad * m_pGeomQuad; // +0x30
    gbTexture * m_pTexture; // +0x34
    gbTextureArray * m_pTextureArray; // +0x38
    unsigned char m_bVisible; // +0x3C
    unsigned char m_bAdditiveBlend; // +0x3D
    unsigned char m_bNoZTest; // +0x3E
    unsigned char m_byMaxFrame; // +0x3F
    int m_nRequireLoops; // +0x40
    int m_nLoops; // +0x44
    float m_fCurFrame; // +0x48
    unsigned long m_dwStartColor; // +0x4C
    float m_fAlpha; // +0x50
    float m_fRed; // +0x54
    float m_fGreen; // +0x58
    float m_fBlue; // +0x5C
    float m_fSize; // +0x60
    float m_fHeight; // +0x64
    float m_fRotAngle; // +0x68
    float m_fWide; // +0x6C
    int m_nDivision; // +0x70
    float m_fTopShrink; // +0x74
    float m_fBottomShrink; // +0x78
    float m_fTopRadius; // +0x7C
    float m_fBottomRadius; // +0x80
    float m_fTopRadiusIncSpeed; // +0x84
    float m_fBottomRadiusIncSpeed; // +0x88
    float m_fTopRiseSpeed; // +0x8C
    float m_fBottomRiseSpeed; // +0x90
    float m_fTextureRepeat; // +0x94
    float m_fFramePerSec; // +0x98
    float m_fCurTextureV; // +0x9C
    gbVec3D m_vecRot; // +0xA0
    gbVec3D m_vecPos; // +0xAC
    gbVec3D m_vecOffsetPos; // +0xB8
    tagUV m_DefaultUVSet[256]; // +0xC4
    // total size: 0x10C4 (4292)

    CEffCylinder(int a1); // 0x004C3DD0
    ~CEffCylinder(); // 0x004C3EB0
    int Init(int a2, float a3, float a4, float a5); // 0x004C3EC0
    char Create(int a2); // 0x004C4060
    void Destroy(); // 0x004C4370
    void CreateTask(float a2); // 0x004C45A0
    void ProcInitTask(_DWORD *a2); // 0x004C48D0
    int ProcCommonTask(int a2); // 0x004C4B00
    static void * GetEditorTaskDescription(int a1); // 0x004C5010
    static void * GetEditorObjDescription(int a1); // 0x004C5150
    void InitDefaultUVSet(int a2, int a3); // 0x004C5210
    _DWORD * LoadTexture(int a2); // 0x004C52C0
};
