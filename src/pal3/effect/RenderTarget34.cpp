// PAL3.exe effect/RenderTarget34.cpp — RenderTarget3/4 单例
// 两个额外的渲染目标管理器 (PAL3 特有，与 RenderTarget/RenderTarget2 同模式)
// Addresses: 0x004B65A0, 0x004B6D30

#include <stdlib.h>
#include <string.h>

// RenderTarget3 实例 (大小未确定，预留足够空间)
static char g_RenderTarget3_inst[256];
static unsigned char g_RenderTarget3_guard;
static void __cdecl RenderTarget3_Dtor_atexit(void) {}

// === STUB: RenderTarget3 构造函数 (0x004B6550) ===
static void RenderTarget3_Ctor(void *pThis)
{
    memset(pThis, 0, 256);
}

// 0x004B65A0 - RenderTarget3::GetInstance (51B)
extern "C" void *__cdecl RenderTarget3_GetInstance(void)
{
    if ((g_RenderTarget3_guard & 1) == 0)
    {
        g_RenderTarget3_guard |= 1;
        RenderTarget3_Ctor(g_RenderTarget3_inst);
        atexit(RenderTarget3_Dtor_atexit);
    }
    return g_RenderTarget3_inst;
}

// RenderTarget4 实例
static char g_RenderTarget4_inst[8];
static unsigned char g_RenderTarget4_guard;
static void __cdecl RenderTarget4_Dtor_atexit(void) {}

// === STUB: RenderTarget4 构造函数 (0x004B6D20) ===
static void RenderTarget4_Ctor(void *pThis)
{
    memset(pThis, 0, 8);
}

// 0x004B6D30 - RenderTarget4::GetInstance (51B)
extern "C" void *__cdecl RenderTarget4_GetInstance(void)
{
    if ((g_RenderTarget4_guard & 1) == 0)
    {
        g_RenderTarget4_guard |= 1;
        RenderTarget4_Ctor(g_RenderTarget4_inst);
        atexit(RenderTarget4_Dtor_atexit);
    }
    return g_RenderTarget4_inst;
}
