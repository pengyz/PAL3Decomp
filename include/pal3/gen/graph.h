#pragma once
// Auto-generated: graph

#include "D3DXVECTOR3.h"

class graph {
public:
    int curve_num; // +0x0
    int cp_num; // +0x4
    char graphname[64]; // +0x8
    char describe[128]; // +0x48
    D3DXVECTOR3 min; // +0xC8
    D3DXVECTOR3 max; // +0xD4
    D3DXVECTOR3 disdata[20][3]; // +0xE0
    D3DXVECTOR3 realdata[20][3]; // +0x3B0
    D3DXVECTOR3 interpolate[101][3]; // +0x680
    // total size: 0x14B4 (5300)

};
