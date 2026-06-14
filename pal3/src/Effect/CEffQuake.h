#include "CEffObj.h"
#pragma once
// Auto-generated: CEffQuake

class CEffQuake : public CEffObj {
public:
    char _tail_000[4272]; // +0x0
    // total size: 0x10B0 (4272)

    virtual ~CEffQuake() {}

    virtual void _sub_4D33A0(int a2, int a3, int a4, int a5); // 0x004D33A0
    virtual int * Destroy(); // 0x004D32C0
    virtual int RenderEffectPass(int a2); // 0x004D33B0
    virtual int sub_4D3660(int a2); // 0x004D3660
    int Update(); // 0x004D3300
};
