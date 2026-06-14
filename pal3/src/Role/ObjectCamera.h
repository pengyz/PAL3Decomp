#pragma once
// Auto-generated: ObjectCamera

#include "gbengine/gbCamera.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"

class ObjectCamera {
public:
    gbCamera * m_pCamera; // +0x0
    gbVec3D m_camFrom; // +0x4
    char _gap_008[8]; // +0x8
    gbVec3D m_camTo; // +0x10
    char _gap_014[8]; // +0x14
    gbVec3D m_camUp; // +0x1C
    char _gap_020[8]; // +0x20
    gbVec3D m_camDirect; // +0x28
    char _gap_02C[8]; // +0x2C
    float m_yaw; // +0x34
    float m_pitch; // +0x38
    float m_roll; // +0x3C
    float m_dist; // +0x40
    float m_nyaw; // +0x44
    float m_npitch; // +0x48
    float m_nroll; // +0x4C
    gbVec3D m_forward; // +0x50
    char _gap_054[8]; // +0x54
    gbVec3D m_side; // +0x5C
    char _gap_060[8]; // +0x60
    float m_stepRotSpeed; // +0x68
    int m_stepRot; // +0x6C
    int m_stepRotMode; // +0x70
    short m_stepRotAxis; // +0x74
    char _gap_076[2]; // +0x76
    BYTE m_bStepRot; // +0x78
    char _tail_079[3]; // +0x79
    // total size: 0x7C (124)

    ObjectCamera(); // 0x0047C570
    void _ObjectCamera(); // 0x0047C580
    float * Create(); // 0x0047C590
    void GetCameraDirect(); // 0x0047C630
    void SetCameraEyePosition(gbGfxManager *position); // 0x0047C640
    void SetCameraAtPosition(gbVec3D position, char pData); // 0x0047C6E0
    void SetCameraRotate(float yaw, float pitch, float roll); // 0x0047C770
    void SetCameraDist(int dist, int nVal, int nVal2); // 0x0047C7E0
    void Destroy(); // 0x0047C810
    void ComputeInfo(int from); // 0x0047C830
    void SetStepRotate(); // 0x0047C9B0
    void Update(); // 0x0047CAD0
};
