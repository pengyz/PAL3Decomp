#pragma once
// Auto-generated: tagImbibeNimbus

#include "ECBFiveNimbus.h"
#include "gbengine/gbengine_types.h"

class UIStatic;

class tagImbibeNimbus {
public:
    UIStatic * mNimbus; // +0x0
    ECBFiveNimbus mNimbustype; // +0x4
    gbVec3D mVelocity; // +0x8
    char _gap_00C[8]; // +0xC
    tagPOINT mPos; // +0x14
    char _gap_018[4]; // +0x18
    BYTE bAlive; // +0x1C
    char _gap_01D[3]; // +0x1D
    float mAccelerate; // +0x20
    float mFX; // +0x24
    float mFY; // +0x28
    // total size: 0x2C (44)

};
