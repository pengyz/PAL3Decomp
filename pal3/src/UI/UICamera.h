#pragma once
// Auto-generated: UICamera

class UICamera {
public:
    char _gap_000[128]; // +0x0
    int m_nCamState; // +0x80
    char _gap_084[20]; // +0x84
    int m_nViewMode; // +0x98
    char _gap_09C[4]; // +0x9C
    float m_fCamAngle; // +0xA0
    float m_fCoordU; // +0xA4
    float m_fCoordV; // +0xA8
    char _gap_0AC[48]; // +0xAC
    int m_nBuffer; // +0xDC
    int m_hTarget; // +0xE0
    char _gap_0E4[44]; // +0xE4
    int m_pCameraData; // +0x110
    char _gap_114[184]; // +0x114
    int m_nStateFlags; // +0x1CC
    int m_nParam; // +0x1D0
    char _gap_1D4[24]; // +0x1D4
    float m_fVecX; // +0x1EC
    float m_fVecY; // +0x1F0
    float m_fVecZ; // +0x1F4
    char _gap_1F8[124]; // +0x1F8
    int m_hCameraHandle; // +0x274
    int _todo_278; // +0x278
    // total size: 0x27C (636)

    BOOL IsPointVisible(float *pfTargetPos, char bNearVisible); // 0x0041A070
    static int GetViewMode(int nVal); // 0x00420CD0
    static float * CalcPosition(float *pMat); // 0x00420E50
    int GetState(); // 0x004230D0
    static int GetTarget(float *pMat); // 0x004232D0
};
