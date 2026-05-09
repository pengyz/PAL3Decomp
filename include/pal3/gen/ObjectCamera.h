#pragma once
// Auto-generated from IDA decomp - ObjectCamera
// 12 methods

class ObjectCamera {
public:
    static void() ObjectCamera();  // 0x0047C570
    static void() ~ObjectCamera();  // 0x0047C580
    static float *__thiscall(float *this) Create();  // 0x0047C590
    void GetCameraDirect();  // 0x0047C630
    void SetCameraEyePosition(struct gbGfxManager *a2);  // 0x0047C640
    int SetCameraAtPosition(int a2, int a3, int a4, char a5);  // 0x0047C6E0
    int SetCameraRotate(int a2, int a3, int a4);  // 0x0047C770
    int SetCameraDist(int a2, int a3, int a4);  // 0x0047C7E0
    void Destroy();  // 0x0047C810
    int ComputeInfo(int a2);  // 0x0047C830
    void SetStepRotate();  // 0x0047C9B0
    void Update();  // 0x0047CAD0
};
