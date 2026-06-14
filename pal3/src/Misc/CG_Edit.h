#pragma once
// Auto-generated: CG_Edit

#include "_FLOORPARAM.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbengine_types.h"

class CG_Entry;

class CG_Edit {
public:
    CG_Entry * m_pFather; // +0x0
    tagPOINT m_MousePt; // +0x4
    char _gap_008[4]; // +0x8
    _FLOORPARAM m_Param; // +0xC
    char _gap_010[8]; // +0x10
    float m_fYaw; // +0x18
    float m_fPitch; // +0x1C
    float m_fDist; // +0x20
    float m_fCamX; // +0x24
    float m_fCamY; // +0x28
    float m_fCamZ; // +0x2C
    gbVec3D m_vCamForward; // +0x30
    char _gap_034[8]; // +0x34
    gbRenderEffect * EFT_LINE; // +0x3C
    gbRenderEffect * EFT_GEOM_NOTEX; // +0x40
    gbRenderEffect * EFT_GEOM_NOTEX_LINE; // +0x44
    BYTE m_bWaitForEditArea; // +0x48
    char _gap_049[3]; // +0x49
    tagRECT m_rTouchArea; // +0x4C
    char _gap_050[12]; // +0x50
    tagRECT m_rLastObjArea; // +0x5C
    char _gap_060[12]; // +0x60
    tagPOINT m_pLastGroundPt; // +0x6C
    char _gap_070[4]; // +0x70
    int m_nNoteMoney; // +0x74
    // total size: 0x78 (120)

};
