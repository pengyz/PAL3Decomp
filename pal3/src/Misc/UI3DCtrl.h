#include "UIWnd.h"
#pragma once
// Auto-generated: UI3DCtrl

#include "UI3DObj.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbengine_types.h"

class UI3DCtrl : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    int m_numobj; // +0x44
    UI3DObj m_obj[5]; // +0x48
    char _gap_05C[140]; // +0x5C
    float m_orthosize; // +0xE8
    int m_rotatemode; // +0xEC
    BYTE m_isrotateto; // +0xF0
    char _gap_0F1[3]; // +0xF1
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
    char _tail_12C[8]; // +0x12C
    // total size: 0x134 (308)

    virtual ~UI3DCtrl() {}

    virtual void Render(); // 0x0043D940
    virtual gbVFileSystem * CreateWithTexture(int id, void *pRect, int nVal, unsigned int dwVal, int parent); // 0x0043D890
    int * ctor_D830(); // 0x0043D830
    void ctor(); // 0x0043D880
    char LoadModel(const char *pszModelName); // 0x0052AF20
    char LoadEncampModel(const char *pszModelName, const char *pszName); // 0x0052B050
    double UpdateRotation(); // 0x0052E8C0
    double UpdateOscillation(); // 0x0052E940
    double UpdateOscillationX(); // 0x0052E9C0
    double UpdateOscillationY(); // 0x0052EA40
    char UpdateTransform(int nVal); // 0x0052EAC0
};
