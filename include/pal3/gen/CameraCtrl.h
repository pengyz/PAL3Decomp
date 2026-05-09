#pragma once
// Auto-generated from IDA decomp - CameraCtrl
// 5 methods

class CameraCtrl {
public:
    int InitParams(void *pParams);  // 0x0041C1B0
    void SetAsCurrent(int flags);  // 0x0041C630
    void SetDimention(int w, int h);  // 0x0041CA90
    static void *__thiscall(CameraCtrl *this, void *pTarget, float *pPos) GetViewTarget();  // 0x0041CAC0
    int SetCamMode(int mode);  // 0x0041D5B0
};
