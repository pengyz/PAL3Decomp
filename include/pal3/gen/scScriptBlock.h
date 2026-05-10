#pragma once
// Auto-generated: scScriptBlock

class scUserVarInfo;

class scScriptBlock {
public:
    unsigned long id; // +0x0
    unsigned char desc[64]; // +0x4
    unsigned long codesize; // +0x44
    unsigned char * pcodedata; // +0x48
    unsigned short uservarnum; // +0x4C
    scUserVarInfo * uservar; // +0x50
    int ref; // +0x54
    // total size: 0x58 (88)

};
