#include "CTaskTpl.h"
#include "tagEffTaskParam.h"
#include "CEffObj.h"
#pragma once
// Auto-generated: CEffModel

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbengine_types.h"

class CEffModel : public CEffObj, public CTaskTpl<tagEffTaskParam,void*> {
public:
    char _gap_000[48]; // +0x0
    gbGeomNode * m_pGeomNode; // +0x30
    char _gap_034[12]; // +0x34
    gbVec3D m_vecOffsetPos; // +0x40
    char _gap_044[8]; // +0x44
    gbVec3D m_vecRot; // +0x4C
    char _gap_050[8]; // +0x50
    BYTE m_bVisible; // +0x58
    BYTE m_bAdditiveBlend; // +0x59
    BYTE m_bNoZTest; // +0x5A
    char _gap_05B[1]; // +0x5B
    float m_fSizeX; // +0x5C
    float m_fSizeY; // +0x60
    float m_fSizeZ; // +0x64
    // total size: 0x68 (104)

    virtual bool LoadFromNode(int nVal); // 0x004CFEB0
    virtual void DestroyEffect(); // 0x004CFFA0
    virtual void RenderScenePass(); // 0x004D01C0
    static int sub_4CFD00(); // 0x004CFD00
    virtual void GetRenderNode(); // 0x004D0390
    virtual void RenderModel(); // 0x004D03B0
    virtual int sub_4D0850(int nVal); // 0x004D0850
    int CreateInstance(CEffModel *pSrc, int nVal, CEffModel *pParam); // 0x004CEC80
    CEffModel(); // 0x004CFC70
    void UpdateDuration(); // 0x004D0BD0
    int * Reset(); // 0x004D0CE0
};
