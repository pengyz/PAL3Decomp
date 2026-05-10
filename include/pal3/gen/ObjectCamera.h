#pragma once
// Auto-generated: ObjectCamera

class ObjectCamera {
public:
    gbCamera * m_pCamera; // +0x0
    gbVec3D m_camFrom; // +0x4
    gbVec3D m_camTo; // +0x10
    gbVec3D m_camUp; // +0x1C
    gbVec3D m_camDirect; // +0x28
    float m_yaw; // +0x34
    float m_pitch; // +0x38
    float m_roll; // +0x3C
    float m_dist; // +0x40
    float m_nyaw; // +0x44
    float m_npitch; // +0x48
    float m_nroll; // +0x4C
    gbVec3D m_forward; // +0x50
    gbVec3D m_side; // +0x5C
    float m_stepRotSpeed; // +0x68
    float m_stepRot; // +0x6C
    int m_stepRotMode; // +0x70
    int m_stepRotAxis; // +0x74
    BYTE m_bStepRot; // +0x78
    // total size: 0x7C (124)

    ObjectCamera(); // 0x0047C570
    ~ObjectCamera(); // 0x0047C580
    float * Create(); // 0x0047C590
    void GetCameraDirect(); // 0x0047C630
    void SetCameraEyePosition(struct gbGfxManager *a2); // 0x0047C640
    int SetCameraAtPosition(int a2, int a3, int a4, char a5); // 0x0047C6E0
    int SetCameraRotate(int a2, int a3, int a4); // 0x0047C770
    int SetCameraDist(int a2, int a3, int a4); // 0x0047C7E0
    void Destroy(); // 0x0047C810
    int ComputeInfo(int a2); // 0x0047C830
    void SetStepRotate(); // 0x0047C9B0
    void Update(); // 0x0047CAD0
};
