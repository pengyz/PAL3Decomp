#pragma once
// Auto-generated from IDA decomp - CCBStageShadow
// 8 methods

class CCBStageShadow {
public:
    char CCBStageShadow();  // 0x00511EE0
    char ~CCBStageShadow();  // 0x00511F90
    char Reset();  // 0x00511FC0
    void Create();  // 0x00512080
    static float *__thiscall(float *this) Destroy();  // 0x00512240
    static int() Update();  // 0x005122E0
    static int() Render();  // 0x005122F0
    static void() FillShadowQuad();  // 0x00512300
};
