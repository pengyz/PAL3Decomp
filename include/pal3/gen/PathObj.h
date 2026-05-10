#pragma once
// Auto-generated: PathObj

class PathObj {
public:
    gbVec3D points[256]; // +0x0
    int numpoint; // +0xC00
    float totallength; // +0xC04
    float length[256]; // +0xC08
    gbVec3D normal[256]; // +0x1008
    float segmentprojection; // +0x1C08
    float segmentlength; // +0x1C0C
    gbVec3D segmentnormal; // +0x1C10
    gbVec3D chosen; // +0x1C1C
    // total size: 0x1C28 (7208)

};
