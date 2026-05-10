#pragma once
// Auto-generated: HeadMsg

class Role;
class UIStatic;

class HeadMsg {
public:
    unsigned char m_bEnable; // +0x4
    struct allocator<char> > {}; // nested type stub
    allocator<char> > m_szMsg; // +0x8
    float m_fTime; // +0x18
    int m_nType; // +0x1C
    int m_nY; // +0x20
    UIStatic * m_pMsgDlg; // +0x24
    int m_nMsgWidth; // +0x28
    int m_nMsgHeight; // +0x2C
    int m_nShowPointW; // +0x30
    float m_fHeadModeTime; // +0x34
    float m_fAttenSpeed; // +0x38
    unsigned char m_bAtten; // +0x3C
    unsigned char m_ucAlpha; // +0x3D
    Role * m_pRole; // +0x40
    // total size: 0x44 (68)

};
