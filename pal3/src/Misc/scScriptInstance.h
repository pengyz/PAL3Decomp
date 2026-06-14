#pragma once
// Auto-generated: scScriptInstance

#include "scVARIANT.h"

class scScriptBlock;

class scScriptInstance {
public:
    // vtable (6 methods, order matches binary layout)

    scScriptBlock * pblock; // +0x0
    BYTE runmode; // +0x4
    BYTE pause; // +0x5
    char _gap_006[2]; // +0x6
    scScriptInstance * pcaller; // +0x8
    _BYTE * codeptr; // +0xC
    scVARIANT reg[8]; // +0x10
    char _gap_030[32]; // +0x30
    scVARIANT * uservar; // +0x50
    // total size: 0x54 (84)

    virtual scScriptInstance * _sdtor_25(scScriptInstance *Block, char a2); // 0x0044E5C0
    void _scScriptInstance(); // 0x0044E5E0
};
