#pragma once
// Auto-generated: RenderTarget3

#include "gbengine/gbRenderEffect.h"

class CPolicy;
class vtbl_0056F36C;

class RenderTarget3 {
public:
    // vtable (3 methods, order matches binary layout)

    char _gap_000[4]; // +0x0
    gbRenderEffect * m_ptr_4; // +0x4
    char _tail_008[16]; // +0x8
    // total size: 0x18 (24)

    virtual int sub_4B6C80(void *Block, char a3); // 0x004B6C80
    static int GenerateRingMesh(float fVal, float fVal2, int nVal, int nVal2, int nVal3, int nVal4, float fVal3); // 0x004B63C0
    static int InitStruct(int nVal); // 0x004B6550
    RenderTarget3 * GetInstance(); // 0x004B65A0
    char Init(); // 0x004B65F0
    int Begin(); // 0x004B6630
    bool ResetAndRender(int nVal, int nVal2); // 0x004B66B0
    void EndSceneGraph(); // 0x004B67B0
    int SwapBuffers(); // 0x004B67E0
    int UpdateRender(int nVal); // 0x004B6820
    CPolicy ** ClearEffects(); // 0x004B6C20
    // [IDA_VTABLE] _nearby_4b6ca0; // 0x004B6CA0
    int * Reset(); // 0x004B6D20
    void * End(); // 0x004B6DF0
    void Resolve(); // 0x004B6E20
};
