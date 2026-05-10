#pragma once
// Auto-generated: UICursor

#include "CURSOR_TYPE.h"

class UICursor {
public:
    unsigned long m_dwID[3]; // +0x0
    CURSOR_TYPE m_active; // +0xC
    gbTexture * m_tex[3]; // +0x10
    unsigned char m_bShow; // +0x1C
    unsigned char m_bSoftMode; // +0x1D
    // total size: 0x20 (32)

    static UINT Init(); // 0x00541860
    static char Inst(CHAR *lpSubKey, LPCSTR lpValueName, LPBYTE lpData); // 0x00541C40
    static int IRender(); // 0x00541CC0
};
