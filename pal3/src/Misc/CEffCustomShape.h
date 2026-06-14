#include "CTaskTpl.h"
#include "tagEffTaskParam.h"
#include "CEffObj.h"
#pragma once
// Auto-generated: CEffCustomShape

#include "gbengine/gbMesh.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"

class t3DModel;

class CEffCustomShape : public CEffObj, public CTaskTpl<tagEffTaskParam,void*> {
public:
    char _gap_000[48]; // +0x0
    BYTE m_bVisible; // +0x30
    char _gap_031[3]; // +0x31
    gbVec3D m_vecPos; // +0x34
    char _gap_038[8]; // +0x38
    gbVec3D m_vecOffsetPos; // +0x40
    char _gap_044[8]; // +0x44
    gbVec3D m_vecRot; // +0x4C
    char _gap_050[8]; // +0x50
    float m_fAlpha; // +0x58
    float m_fRed; // +0x5C
    float m_fGreen; // +0x60
    float m_fBlue; // +0x64
    float m_fScaleX; // +0x68
    float m_fScaleY; // +0x6C
    float m_fScaleZ; // +0x70
    t3DModel * m_pModel; // +0x74
    gbTexture * m_pTexture; // +0x78
    gbRenderEffect * m_pRenderEffect; // +0x7C
    gbIndexBubble * m_pIndexBubble; // +0x80
    int m_nCurrFrame; // +0x84
    int m_nFrameNum; // +0x88
    float m_fFrameU; // +0x8C
    float m_fFrameV; // +0x90
    float m_fSpeed; // +0x94
    float m_fTimeCount; // +0x98
    char m_UVData[16]; // +0x9C
    // total size: 0xAC (172)

};
