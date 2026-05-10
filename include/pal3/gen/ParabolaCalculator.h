#pragma once
// Auto-generated: ParabolaCalculator

class ParabolaCalculator {
public:
    gbVec3D velocity; // +0x0
    gbVec3D A; // +0xC
    gbVec3D B; // +0x18
    float H; // +0x24
    float G; // +0x28
    char m_state[4]; // +0x2C (ParabolaCalculator::PRBL_STATE)
    // total size: 0x30 (48)

    int CalulateParabola(); // 0x00523600
    int UpdateParabola(); // 0x00523670
    int UpdateParabolaY(int a2, int a3); // 0x005236E0
};
