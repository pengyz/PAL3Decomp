#pragma once
// Auto-generated: CEffShock

#include "CEffObj.h"
#include "tagUV.h"

class gbTextureArray;
class tagShockUnit;

class CEffShock : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffShock::*)(unsigned long)> {
public:
    tagUV m_DefaultUVSet[256]; // +0x30
    gbTexture * m_pTexture; // +0x1030
    gbTextureArray * m_pTextureArray; // +0x1034
    int m_nMaxGeomQuad; // +0x1038
    gbGeomQuad * m_pGeomQuad; // +0x103C
    tagShockUnit * m_pShock; // +0x1040
    unsigned char m_bVisible; // +0x1044
    unsigned char m_bAdditiveBlend; // +0x1045
    unsigned char m_bNoZTest; // +0x1046
    float m_fFramePerSec; // +0x1048
    unsigned char m_byMaxFrame; // +0x104C
    int m_nRequireLoops; // +0x1050
    int m_nLoops; // +0x1054
    float m_fCurFrame; // +0x1058
    unsigned long m_dwStartColor; // +0x105C
    float m_fAlpha; // +0x1060
    float m_fRed; // +0x1064
    float m_fGreen; // +0x1068
    float m_fBlue; // +0x106C
    float m_fSize; // +0x1070
    gbVec3D m_vecRot; // +0x1074
    gbVec3D m_vecPos; // +0x1080
    gbVec3D m_vecOffsetPos; // +0x108C
    int m_nNodeOfShock; // +0x1098
    int m_nCascade; // +0x109C
    float m_fWidthOfNode; // +0x10A0
    float m_fHeightOfNode; // +0x10A4
    float m_fSpeedOfDisappear; // +0x10A8
    float m_fInterleaving; // +0x10AC
    // total size: 0x10B0 (4272)

    CEffShock(); // 0x004D3910
    int Init(int a2, float a3, float a4, float a5); // 0x004D3A50
    char Create(int a2); // 0x004D3AD0
    int StartShock(int a2); // 0x004D45D0
    int CreateGeom(int a2, int a3); // 0x004D49F0
    int LoadTexture(int a2, int a3, int a4, _DWORD *a5, int a6, int a7); // 0x004D4B50
};
