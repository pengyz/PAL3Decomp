#pragma once
// Auto-generated: CameraCtrl

class CameraCtrl {
public:
    int InitParams(void *pParams); // 0x0041C1B0
    void SetAsCurrent(int flags); // 0x0041C630
    void SetDimention(int w, int h); // 0x0041CA90
    void * GetViewTarget(void *pTarget, float *pPos); // 0x0041CAC0
    int SetCamMode(int mode); // 0x0041D5B0
};
