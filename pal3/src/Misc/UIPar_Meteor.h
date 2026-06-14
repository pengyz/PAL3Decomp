#include "UIWnd.h"
#pragma once
// Auto-generated: UIPar_Meteor

class UIPar_Meteor : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    tagRECT m_StartToEnd; // +0x44
    char _gap_048[12]; // +0x48
    tagPOINT m_tmpPt; // +0x54
    char _gap_058[4]; // +0x58
    tagPOINT m_TailPt[16]; // +0x5C
    char _gap_09C[64]; // +0x9C
    int m_nTailNum; // +0xDC
    int m_ntmpTailNum; // +0xE0
    int m_nFrameNumBetweenTail; // +0xE4
    float m_fVelocityX; // +0xE8
    float m_fVelocityY; // +0xEC
    float m_passtime; // +0xF0
    int m_IsInMeteor; // +0xF4
    int m_nNextTime; // +0xF8
    int m_nFrame; // +0xFC
    char _tail_100[20]; // +0x100
    // total size: 0x114 (276)

};
