#pragma once
// Auto-generated: CEffMeteor

#include "CEffObj.h"
#include "CTaskTpl.h"
#include "tagUV.h"

class CMeteorChain;
class gbTextureArray;
class tagMeteor;

class CEffMeteor : public CEffObj, public CTaskTpl {
public:
    gbGeomQuad * m_pGeomQuad; // +0x30
    CMeteorChain * m_pChain; // +0x34
    tagMeteor * m_pMeteor; // +0x38
    gbTexture * m_pTexture; // +0x3C
    gbTextureArray * m_pTextureArray; // +0x40
    unsigned char m_bVisible; // +0x44
    unsigned char m_bAdditiveBlend; // +0x45
    unsigned char m_bNoZTest; // +0x46
    unsigned char m_bHaveHead; // +0x47
    unsigned char m_byMaxFrame; // +0x48
    int m_nRequireLoops; // +0x4C
    int m_nLoops; // +0x50
    float m_fCurFrame; // +0x54
    unsigned long m_dwStartColor; // +0x58
    float m_fAlpha; // +0x5C
    float m_fRed; // +0x60
    float m_fGreen; // +0x64
    float m_fBlue; // +0x68
    float m_fXSize; // +0x6C
    float m_fZSize; // +0x70
    int m_nMaxChain; // +0x74
    float m_fMeteorWidth; // +0x78
    int m_nMaxTrail; // +0x7C
    float m_fLumDecSpeed; // +0x80
    float m_fWidthDecSpeed; // +0x84
    float m_fMaxLum; // +0x88
    float m_fUpdateTimeFund; // +0x8C
    float m_fFramePerSec; // +0x90
    gbVec3D m_vecRot; // +0x94
    gbVec3D m_vecPos; // +0xA0
    gbVec3D m_vecOffsetPos; // +0xAC
    gbVec3D m_vecTarget; // +0xB8
    gbVec3D m_vecStartSpeed; // +0xC4
    tagUV m_DefaultUVSet[256]; // +0xD0
    // total size: 0x10D0 (4304)

    CEffMeteor(); // 0x004CB480
    ~CEffMeteor(); // 0x004CB4C0
    int Init(int a2, float a3, float a4, float a5); // 0x004CB5E0
    char Create(int base); // 0x004CB800
    void CreateTask(int arg0); // 0x004CBFC0
};
