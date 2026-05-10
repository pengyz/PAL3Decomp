#pragma once
// Auto-generated: RoleCameraCtrl

#include "PalScriptWaitObj.h"
#include "RCC_TYPE.h"

class RoleCamera;

class RoleCameraCtrl : public PalScriptWaitObj {
public:
    RoleCamera * m_camera; // +0x8
    RCC_TYPE m_type; // +0xC
    float m_time; // +0x10
    float m_passtime; // +0x14
    int m_itype; // +0x18
    float m_targetdist; // +0x1C
    float m_startdist; // +0x20
    float m_targetyaw; // +0x24
    float m_startyaw; // +0x28
    float m_targetpitch; // +0x2C
    float m_startpitch; // +0x30
    gbVec3D m_targetfrom; // +0x34
    gbVec3D m_startfrom; // +0x40
    // total size: 0x4C (76)

};
