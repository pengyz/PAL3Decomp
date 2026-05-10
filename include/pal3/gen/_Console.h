#pragma once
// Auto-generated: _Console

class _Console {
public:
    int m_numcmd; // +0x0
    struct _ConCmd {}; // nested type stub
    _ConCmd m_cmd[64]; // +0x4
    tagRECT m_rect; // +0x2204
    int m_bactive; // +0x2214
    int m_bEnable; // +0x2218
    gbColorQuad m_color; // +0x221C
    char m_inputbuf[100]; // +0x2220
    char m_showbuf[100][17]; // +0x2284
    gbColorQuad m_fontcolor; // +0x2928
    // total size: 0x292C (10540)

};
