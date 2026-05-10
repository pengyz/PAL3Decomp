#pragma once
// Auto-generated: LineupComp

#include "Object3D.h"
#include "UIWnd.h"

class ObjectCamera;

class LineupComp : public UIWnd {
public:
    gbVec3D m_ObjPos[6]; // +0x44
    Object3D m_LineupObj; // +0x8C
    Object3D m_3DRole[5]; // +0x124
    unsigned char m_isRoleIn[5]; // +0x41C
    Object3D m_3DNone[6]; // +0x424
    unsigned char m_is3DNoneIn[6]; // +0x7B4
    ObjectCamera * m_pCamera; // +0x7BC
    float m_objCamPitch; // +0x7C0
    float m_objRotSpeed; // +0x7C4
    float m_pointerHeight; // +0x7C8
    unsigned char m_isRotLineup; // +0x7CC
    int m_RoleId; // +0x7D0
    int m_nRole; // +0x7D4
    unsigned char m_bClickRole; // +0x7D8
    // total size: 0x7DC (2012)

};
