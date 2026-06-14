#pragma once
// Auto-generated: scScriptBlock

class scUserVarInfo;

class scScriptBlock {
public:
    UINT id; // +0x0
    _BYTE desc[64]; // +0x4
    UINT codesize; // +0x44
    _BYTE * pcodedata; // +0x48
    WORD uservarnum; // +0x4C
    char _gap_04E[2]; // +0x4E
    scUserVarInfo * uservar; // +0x50
    int ref; // +0x54
    // total size: 0x58 (88)

};
