#pragma once
// Auto-generated from IDA decomp - gbLightObj
// 4 methods

class gbLightObj {
public:
    void Compute(struct gbVolModNode *a2);  // 0x005420A8
    float GetEffectOnPoint(const struct gbVec3D *a2, int a3);  // 0x005420AE
    static const struct gbSphere *__thiscall(gbLightObj *this) GetBoundSphere();  // 0x005420B4
    int GetType();  // 0x005420BA
};
