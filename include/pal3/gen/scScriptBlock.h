#pragma once
// Auto-generated: scScriptBlock

class scUserVarInfo;

class scScriptBlock {
public:
    DWORD id; // +0x0
    BYTE desc[64]; // +0x4
    DWORD codesize; // +0x44
    BYTE * pcodedata; // +0x48
    WORD uservarnum; // +0x4C
    scUserVarInfo * uservar; // +0x50
    int ref; // +0x54
    // total size: 0x58 (88)

};
