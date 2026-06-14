#include "UIWnd.h"
#pragma once
// Auto-generated: UIPushButton

#include "gbengine/gbTexture.h"

class _PlugInfo;

class UIPushButton : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    BYTE m_isDown; // +0x44
    char _gap_045[3]; // +0x45
    _PlugInfo * m_texarrayInfo[2]; // +0x48
    char _gap_04C[4]; // +0x4C
    BYTE m_bOn; // +0x50
    char _gap_051[3]; // +0x51
    gbTexture * m_onpic; // +0x54
    _PlugInfo * m_onpicInfo; // +0x58
    gbTexture * m_disablepic; // +0x5C
    _PlugInfo * m_disablepicInfo; // +0x60
    char m_caption[128]; // +0x64
    int m_TextTopOffset; // +0xE4
    char _gap_0E8[4]; // +0xE8
    int _todo_0EC; // +0xEC
    char _tail_0F0[12]; // +0xF0
    // total size: 0xFC (252)

    void SetAnimOffset(int thisa, int nVal, float fVal); // 0x0043A090
    int SetParam(int nVal); // 0x0043A0E0
};
