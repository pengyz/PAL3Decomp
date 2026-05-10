#pragma once
// Auto-generated: gbPartParamControl

class gbPartParamControl {
public:
    int nCurve; // +0x0
    int nCtrlPt; // +0x4
    char Name[64]; // +0x8
    char Descript[128]; // +0x48
    gbVec3D MinPt; // +0xC8
    gbVec3D MaxPt; // +0xD4
    gbVec3D CtrlPt[20][3]; // +0xE0
    gbVec3D Segment[101][3]; // +0x3B0
    // total size: 0x11E4 (4580)

};
