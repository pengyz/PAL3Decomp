#pragma once
// Auto-generated from IDA decomp - Camera
// 4 methods

class Camera {
public:
    void SetParams(int a2);  // 0x004125D0
    static int CheckCollision1(void *pPos, void *pBounds, float *pDist);  // 0x0041E7D0
    static int CheckCollision2(void *pPos, int rolePtr, void *pBounds);  // 0x0041EA00
    static char __cdecl() IsTransitioning();  // 0x0041EE60
};
