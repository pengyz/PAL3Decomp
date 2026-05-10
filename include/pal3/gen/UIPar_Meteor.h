#pragma once
// Auto-generated: UIPar_Meteor

#include "UIWnd.h"

class UIPar_Meteor : public UIWnd {
public:
    gbTexture * m_pTex[2]; // +0x44
    gbColorQuad m_color; // +0x4C
    int m_nWidth; // +0x50
    int m_nHeight; // +0x54
    tagRECT m_StartToEnd; // +0x58
    tagPOINT m_tmpPt; // +0x68
    tagPOINT m_TailPt[16]; // +0x70
    int m_nTailNum; // +0xF0
    int m_ntmpTailNum; // +0xF4
    int m_nFrameNumBetweenTail; // +0xF8
    float m_fVelocityX; // +0xFC
    float m_fVelocityY; // +0x100
    float m_passtime; // +0x104
    int m_IsInMeteor; // +0x108
    int m_nNextTime; // +0x10C
    int m_nFrame; // +0x110
    // total size: 0x114 (276)

};
