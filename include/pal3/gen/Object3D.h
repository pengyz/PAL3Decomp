#pragma once
// Auto-generated from IDA decomp - Object3D
// 19 methods

class Object3D {
public:
    void Object3D();  // 0x0047CB70
    static struct gbVFileSystem *__thiscall(void *this, const char *a2, int a3) ~Object3D();  // 0x0047CB90
    unsigned __int8 LoadObject(const char *a2, int a3);  // 0x0047CD70
    void LoadSubObject();  // 0x0047CEE0
    char Destroy();  // 0x0047CF40
    static long double IsOverCVD(float a1, float a2, float a3, float a4, float a5, float a6);  // 0x0047CFB0
    void VecAngle(float a2, float a3, float a4);  // 0x0047D030
    void SetObjectPosition(float a2, float a3, float a4);  // 0x0047D130
    long double SetCentrePos();  // 0x0047D230
    void GetScreenDegree();  // 0x0047D320
    static void GetScreenDegree(int a1@<ecx>, int a2, int a3, int a4, gbMatrixStack *a5);  // 0x0047D440
    void CaculateRelative(float a2);  // 0x0047D690
    static void *__thiscall(void *this) SetupCamera();  // 0x0047D9D0
    bool Update();  // 0x0047DA60
    bool GetMouseRay(int a2);  // 0x0047DB40
    static int() CheckMouseLPressed();  // 0x0047DC60
    static int() CheckMousePressed();  // 0x0047DC70
    int Create();  // 0x0047DCA0
    void Init();  // 0x0047DE40
};
