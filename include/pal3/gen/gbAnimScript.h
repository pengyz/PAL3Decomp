#pragma once
// Auto-generated: gbAnimScript

class gbAnimScript {
public:
    unsigned int AnimCmdBuf[1024]; // +0x0
    char AnimCmdDesBuf[1024]; // +0x0
    int CurCmdBufPt; // +0x0
    int BeginPos; // +0x0
    int EndPos; // +0x4
    int CurPos; // +0x8
    float Var_Flt[8]; // +0xC
    int Var_Int[8]; // +0x2C
    float AnimSpeed; // +0x4C
    gbVec3D Vel; // +0x50
    gbVec3D Accel; // +0x5C
    gbVec3D Offset; // +0x68
    int IsHide; // +0x74
    double CurTime; // +0x78
    double NextTime; // +0x80
    // total size: 0x88 (136)

};
