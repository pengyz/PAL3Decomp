#pragma once
// Auto-generated: HeadMsg

class Role;
class UIStatic;

class HeadMsg {
public:
    BYTE m_bEnable; // +0x4
    char m_szMsg[16]; // +0x8 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    float m_fTime; // +0x18
    int m_nType; // +0x1C
    int m_nY; // +0x20
    UIStatic * m_pMsgDlg; // +0x24
    int m_nMsgWidth; // +0x28
    int m_nMsgHeight; // +0x2C
    int m_nShowPointW; // +0x30
    float m_fHeadModeTime; // +0x34
    float m_fAttenSpeed; // +0x38
    BYTE m_bAtten; // +0x3C
    BYTE m_ucAlpha; // +0x3D
    Role * m_pRole; // +0x40
    // total size: 0x44 (68)

};
