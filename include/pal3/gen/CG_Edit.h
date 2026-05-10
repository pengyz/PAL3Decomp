#pragma once
// Auto-generated: CG_Edit

#include "_FLOORPARAM.h"

class CG_Entry;

class CG_Edit {
public:
    CG_Entry * m_pFather; // +0x0
    tagPOINT m_MousePt; // +0x4
    _FLOORPARAM m_Param; // +0xC
    float m_fYaw; // +0x18
    float m_fPitch; // +0x1C
    float m_fDist; // +0x20
    float m_fCamX; // +0x24
    float m_fCamY; // +0x28
    float m_fCamZ; // +0x2C
    gbVec3D m_vCamForward; // +0x30
    gbRenderEffect * EFT_LINE; // +0x3C
    gbRenderEffect * EFT_GEOM_NOTEX; // +0x40
    gbRenderEffect * EFT_GEOM_NOTEX_LINE; // +0x44
    BYTE m_bWaitForEditArea; // +0x48
    tagRECT m_rTouchArea; // +0x4C
    tagRECT m_rLastObjArea; // +0x5C
    tagPOINT m_pLastGroundPt; // +0x6C
    int m_nNoteMoney; // +0x74
    // total size: 0x78 (120)

};
