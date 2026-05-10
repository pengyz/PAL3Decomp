#pragma once
// Auto-generated: scScriptInstance

#include "scVARIANT.h"

class scScriptBlock;

class scScriptInstance {
public:
    scScriptBlock * pblock; // +0x0
    BYTE runmode; // +0x4
    BYTE pause; // +0x5
    scScriptInstance * pcaller; // +0x8
    BYTE * codeptr; // +0xC
    scVARIANT reg[8]; // +0x10
    scVARIANT * uservar; // +0x50
    // total size: 0x54 (84)

};
