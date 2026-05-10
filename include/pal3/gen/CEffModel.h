#pragma once
// Auto-generated: CEffModel

#include "CEffObj.h"

class CEffModel : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffModel::*)(unsigned long)> {
public:
    gbGeomNode * m_pGeomNode; // +0x30
    gbVec3D m_vecCurPos; // +0x34
    gbVec3D m_vecOffsetPos; // +0x40
    gbVec3D m_vecRot; // +0x4C
    unsigned char m_bVisible; // +0x58
    unsigned char m_bAdditiveBlend; // +0x59
    unsigned char m_bNoZTest; // +0x5A
    float m_fSizeX; // +0x5C
    float m_fSizeY; // +0x60
    float m_fSizeZ; // +0x64
    // total size: 0x68 (104)

    _DWORD * Render(); // 0x004D0CE0
    static _DWORD * SetTimeScale(); // 0x004D0D70
    int ProcInitTask(int a2, float a3, float a4, float a5); // 0x004D0EC0
};
