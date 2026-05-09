#pragma once
// Auto-generated: tagCCT

#include "tagCam.h"

class tagCCT {
public:
    void * * fp; // +0x0
    unsigned long dwID; // +0x10
    unsigned char bValid; // +0x14
    unsigned char bExecuted; // +0x15
    unsigned char bFinished; // +0x16
    unsigned char bSplice; // +0x17
    float fStartTime; // +0x18
    float fExpectTime; // +0x1C
    tagCam StartPos; // +0x20
    tagCam EndPos; // +0x38
    int nStartCam; // +0x50
    int nEndCam; // +0x54
    unsigned char bStartCamValid; // +0x58
    unsigned char bEndCamValid; // +0x59
    unsigned char bTimeValid; // +0x5A
    unsigned char bSpeedValid; // +0x5B
    unsigned char bLineMove; // +0x5C
    unsigned char bCircleMove; // +0x5D
    unsigned char bMechanicsMove; // +0x5E
    unsigned char bTimeRevise; // +0x5F
    unsigned char bAbsoluteTime; // +0x60
    unsigned char bCounterYaw; // +0x61
    unsigned char bCounterPitch; // +0x62
    unsigned char bCounterRoll; // +0x63
    unsigned char bRandSwing; // +0x64
    unsigned char bSightTrace; // +0x65
    unsigned char bPosTrace; // +0x66
    int nTraceRole; // +0x68
    float fStartSpeed; // +0x6C
    float fInertia; // +0x70
    float fAccelerationTime1; // +0x74
    float fAccelerationTime2; // +0x78
    float fAcceleration1; // +0x7C
    float fAcceleration2; // +0x80
    float fCircleAngle; // +0x84
    float fAngleSpeed; // +0x88
    float fCircleCentreX; // +0x8C
    float fCircleCentreY; // +0x90
    float fCircleCentreZ; // +0x94
    float fCircleEndX; // +0x98
    float fCircleEndY; // +0x9C
    float fCircleEndZ; // +0xA0
    float fSwingFre; // +0xA4
    float fSwing; // +0xA8
    float fTimeExpiate; // +0xAC
    float fStartFOV; // +0xB0
    float fEndFOV; // +0xB4
    float fStartTracePosX; // +0xB8
    float fStartTracePosY; // +0xBC
    float fStartTracePosZ; // +0xC0
    unsigned long dwReserved[2]; // +0xC4
    // total size: 0xCC (204)

};
