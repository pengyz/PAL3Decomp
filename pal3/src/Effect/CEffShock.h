#include "CEffObj.h"
#pragma once
// Auto-generated: CEffShock

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#include "tagUV.h"

class tagShockUnit;

class CEffShock : public CEffObj {
public:
    char _gap_000[48]; // +0x0
    tagUV m_DefaultUVSet[256]; // +0x30
    char _gap_430[3072]; // +0x430
    gbTexture * m_pTexture; // +0x1030
    gbTextureArray * m_pTextureArray; // +0x1034
    int m_nMaxGeomQuad; // +0x1038
    gbGeomQuad * m_pGeomQuad; // +0x103C
    tagShockUnit * m_pShock; // +0x1040
    BYTE m_bVisible; // +0x1044
    BYTE m_bAdditiveBlend; // +0x1045
    BYTE m_bNoZTest; // +0x1046
    char _gap_1047[1]; // +0x1047
    float m_fFramePerSec; // +0x1048
    BYTE m_byMaxFrame; // +0x104C
    char _gap_104D[3]; // +0x104D
    int m_nRequireLoops; // +0x1050
    int m_nLoops; // +0x1054
    float m_fCurFrame; // +0x1058
    UINT m_dwStartColor; // +0x105C
    float m_fAlpha; // +0x1060
    float m_fRed; // +0x1064
    float m_fGreen; // +0x1068
    float m_fBlue; // +0x106C
    float m_fSize; // +0x1070
    gbVec3D m_vecRot; // +0x1074
    char _gap_1078[8]; // +0x1078
    gbVec3D m_vecPos; // +0x1080
    char _gap_1084[8]; // +0x1084
    gbVec3D m_vecOffsetPos; // +0x108C
    char _gap_1090[8]; // +0x1090
    int m_nNodeOfShock; // +0x1098
    int m_nCascade; // +0x109C
    float m_fWidthOfNode; // +0x10A0
    float m_fHeightOfNode; // +0x10A4
    float m_fSpeedOfDisappear; // +0x10A8
    float m_fInterleaving; // +0x10AC
    // total size: 0x10B0 (4272)

    const char * GetEditorTaskDescription(int nIndex); // 0x004D3280
    CEffShock(CEffShock *thisa); // 0x004D3910
    int UpdateSegment(int nVal); // 0x004D4570
    void StartShock(int nRequireLoops); // 0x004D45D0
    void CreateGeom(int nVal, int nVal2); // 0x004D49F0
    void LoadTexture(int pFileName, int nVal, int nVal2, int *p_DWORD, int nVal3, int nVal4); // 0x004D4B50
};
