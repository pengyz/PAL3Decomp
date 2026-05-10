#pragma once
// Auto-generated: Object3D

#include "ACTION_KIND.h"

class Actor;
class ObjectCamera;

class Object3D {
public:
    BYTE m_isLoadObj; // +0x0
    UINT m_type; // +0x4
    gbGeomNode * m_pol; // +0x8
    Actor * m_actor; // +0x8
    gbGeomNode * m_subObj; // +0xC
    UINT m_subType; // +0x10
    BYTE m_isLoadSubObj; // +0x14
    BYTE m_showSubObj; // +0x15
    float m_subObjHeight; // +0x18
    float m_height; // +0x1C
    gbVec3D m_position; // +0x20
    gbVec3D RelativePos; // +0x2C
    float m_roty; // +0x38
    float m_rotx; // +0x3C
    float m_rotz; // +0x40
    float m_dropx; // +0x44
    float m_dropy; // +0x48
    float m_dropz; // +0x4C
    BYTE m_visible; // +0x50
    ObjectCamera * m_pCamera; // +0x54
    float m_yaw; // +0x58
    float m_pitch; // +0x5C
    float m_roll; // +0x60
    float m_dist; // +0x64
    gbVec3D m_forward; // +0x68
    float m_degreeToScreen; // +0x74
    BYTE m_isActionRelativeRot; // +0x78
    BYTE m_bRotDstDegree; // +0x79
    float m_rotRelative; // +0x7C
    float m_rotDegree; // +0x80
    float m_rotDstDegree; // +0x84
    float m_rotDstSpeed; // +0x88
    int m_rotDstDir; // +0x8C
    int m_rotDstMode; // +0x90
    ACTION_KIND m_action; // +0x94
    // total size: 0x98 (152)

    Object3D(); // 0x0047CB70
    struct gbVFileSystem * _Object3D(const char *a2, int a3); // 0x0047CB90
    unsigned __int8 LoadObject(const char *a2, int a3); // 0x0047CD70
    void LoadSubObject(); // 0x0047CEE0
    char Destroy(); // 0x0047CF40
    static long double IsOverCVD(float a1, float a2, float a3, float a4, float a5, float a6); // 0x0047CFB0
    void VecAngle(float a2, float a3, float a4); // 0x0047D030
    void SetObjectPosition(float a2, float a3, float a4); // 0x0047D130
    long double SetCentrePos(); // 0x0047D230
    void GetScreenDegree(); // 0x0047D320
    // [IDA_USERPURGE] GetScreenDegree; // 0x0047D440
    void CaculateRelative(float a2); // 0x0047D690
    void * SetupCamera(); // 0x0047D9D0
    bool Update(); // 0x0047DA60
    bool GetMouseRay(int a2); // 0x0047DB40
    static int CheckMouseLPressed(); // 0x0047DC60
    static int CheckMousePressed(); // 0x0047DC70
    int Create(); // 0x0047DCA0
    void Init(); // 0x0047DE40
};
