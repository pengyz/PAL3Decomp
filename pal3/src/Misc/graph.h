#pragma once
// Auto-generated: graph

class D3DXVECTOR3;

class graph {
public:
    int curve_num; // +0x0
    int cp_num; // +0x4
    char graphname[64]; // +0x8
    char describe[128]; // +0x48
    D3DXVECTOR3 min; // +0xC8
    char _gap_0CC[8]; // +0xCC
    D3DXVECTOR3 max; // +0xD4
    char _gap_0D8[8]; // +0xD8
    D3DXVECTOR3 disdata[20][3]; // +0xE0
    char _gap_1D0[480]; // +0x1D0
    D3DXVECTOR3 realdata[20][3]; // +0x3B0
    char _gap_4A0[480]; // +0x4A0
    char interpolate[256]; // +0x680
    // total size: 0x780 (1920)

};
