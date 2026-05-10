#pragma once
// Auto-generated: tagCCT

#include "tagCam.h"

class tagCCT {
public:
    void * * fp; // +0x0
    DWORD dwID; // +0x10
    BYTE bValid; // +0x14
    BYTE bExecuted; // +0x15
    BYTE bFinished; // +0x16
    BYTE bSplice; // +0x17
    float fStartTime; // +0x18
    float fExpectTime; // +0x1C
    tagCam StartPos; // +0x20
    tagCam EndPos; // +0x38
    int nStartCam; // +0x50
    int nEndCam; // +0x54
    BYTE bStartCamValid; // +0x58
    BYTE bEndCamValid; // +0x59
    BYTE bTimeValid; // +0x5A
    BYTE bSpeedValid; // +0x5B
    BYTE bLineMove; // +0x5C
    BYTE bCircleMove; // +0x5D
    BYTE bMechanicsMove; // +0x5E
    BYTE bTimeRevise; // +0x5F
    BYTE bAbsoluteTime; // +0x60
    BYTE bCounterYaw; // +0x61
    BYTE bCounterPitch; // +0x62
    BYTE bCounterRoll; // +0x63
    BYTE bRandSwing; // +0x64
    BYTE bSightTrace; // +0x65
    BYTE bPosTrace; // +0x66
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
    DWORD dwReserved[2]; // +0xC4
    // total size: 0xCC (204)

};
