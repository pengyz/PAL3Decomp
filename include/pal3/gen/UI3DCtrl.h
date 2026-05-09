#pragma once
// Auto-generated: UI3DCtrl

#include "UI3DObj.h"
#include "UIWnd.h"
#include "gbVec3D.h"

class gbCamera;
class gbLightObj;

class UI3DCtrl : public UIWnd {
public:
    int m_numobj; // +0x44
    UI3DObj m_obj[5]; // +0x48
    float m_orthosize; // +0xE8
    int m_rotatemode; // +0xEC
    unsigned char m_isrotateto; // +0xF0
    int m_speed; // +0xF4
    float m_rotate; // +0xF8
    float m_rotatetarget; // +0xFC
    float m_rotx; // +0x100
    float m_rotz; // +0x104
    float m_dropx; // +0x108
    float m_dropy; // +0x10C
    float m_dropz; // +0x110
    float m_scalex; // +0x114
    float m_scaley; // +0x118
    float m_scalez; // +0x11C
    gbLightObj * m_lightobj; // +0x120
    gbCamera * m_camera; // +0x124
    gbVec3D m_raydir; // +0x128
    // total size: 0x134 (308)

};
