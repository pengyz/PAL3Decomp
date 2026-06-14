#pragma once
// Auto-generated: _Console

#include "_Console__ConCmd.h"
#include "gbengine/gbengine_types.h"

class _Console {
public:
    int m_numcmd; // +0x0
    _Console__ConCmd m_cmd[64]; // +0x4
    char _gap_104[8448]; // +0x104
    tagRECT m_rect; // +0x2204
    char _gap_2208[12]; // +0x2208
    int m_bactive; // +0x2214
    int m_bEnable; // +0x2218
    gbColorQuad m_color; // +0x221C
    char m_inputbuf[100]; // +0x2220
    char m_showbuf[100][17]; // +0x2284
    gbColorQuad m_fontcolor; // +0x2928
    // total size: 0x292C (10540)

};
