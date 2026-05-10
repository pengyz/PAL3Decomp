#pragma once
// Auto-generated: scScriptInstance

#include "scVARIANT.h"

class scScriptBlock;

class scScriptInstance {
public:
    scScriptBlock * pblock; // +0x0
    unsigned char runmode; // +0x4
    unsigned char pause; // +0x5
    scScriptInstance * pcaller; // +0x8
    unsigned char * codeptr; // +0xC
    scVARIANT reg[8]; // +0x10
    scVARIANT * uservar; // +0x50
    // total size: 0x54 (84)

};
