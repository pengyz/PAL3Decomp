#include "CEffObj.h"
#pragma once
// Auto-generated: CEffCylinder

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#include "tagUV.h"

class CEffExplosive;
class tagEffObjType;

class CEffCylinder : public CEffObj {
public:
    char _gap_000[48]; // +0x0
    gbGeomQuad * m_pGeomQuad; // +0x30
    gbTexture * m_pTexture; // +0x34
    gbTextureArray * m_pTextureArray; // +0x38
    BYTE m_bVisible; // +0x3C
    BYTE m_bAdditiveBlend; // +0x3D
    BYTE m_bNoZTest; // +0x3E
    BYTE m_byMaxFrame; // +0x3F
    int m_nRequireLoops; // +0x40
    int m_nLoops; // +0x44
    float m_fCurFrame; // +0x48
    UINT m_dwStartColor; // +0x4C
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
    char _gap_0A4[8]; // +0xA4
    gbVec3D m_vecPos; // +0xAC
    char _gap_0B0[8]; // +0xB0
    gbVec3D m_vecOffsetPos; // +0xB8
    char _gap_0BC[8]; // +0xBC
    tagUV m_DefaultUVSet[256]; // +0xC4
    char _tail_4C4[3072]; // +0x4C4
    // total size: 0x10C4 (4292)

    virtual char Create(tagEffObjType *pType); // 0x004C4060
    virtual int Init(float *pType, float fx, float fy, float fz); // 0x004C3EC0
    virtual void CreateTask(float p); // 0x004C45A0
    virtual void Destroy(); // 0x004C4370
    virtual void AllocEffect(); // 0x004C3D90
    virtual const char * GetEditorObjDescription(int nIndex); // 0x004C5150
    virtual void ProcInitTask(int *dwParam); // 0x004C48D0
    virtual const char * GetEditorTaskDescription(int nIndex); // 0x004C5010
    CEffCylinder ** Init(); // 0x004C3C90
    CEffCylinder(); // 0x004C3DD0
    void _CEffCylinder(); // 0x004C3EB0
    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol); // 0x004C5210
    int * LoadTexture(char *pFileName); // 0x004C52C0
    int ProcCommonTask__ovl(int a2); // 0x004C7680
    int UpdateGeometry(int nVal); // 0x004CA450
    int Update(int nVal); // 0x004CC4C0
};
