#pragma once
// Auto-generated: SCNHeader

class SCNHeader {
public:
    _BYTE magic[4]; // +0x0
    WORD version; // +0x4
    WORD numnpc; // +0x6
    UINT offsetnpc; // +0x8
    WORD numobj; // +0xC
    char offsetobj[2]; // +0xE
    char _tail_010[2]; // +0x10
    // total size: 0x12 (18)

};
