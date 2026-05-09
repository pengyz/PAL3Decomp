// PAL3.exe effect/RenderTarget2.cpp — CRenderTarget2 单例管理
// PDB source: 无直接对应 (PAL3 特有, PAL3A 只有 RenderTarget)
// Address range: 0x004BF760-0x004C0620

#include <stdlib.h>
#include <string.h>

struct IUnknown;

// CRenderTarget2: PAL3 特有的渲染目标管理器
// 从 Destroy 逆推布局: this+1,+2,+3 是 COM 接口指针 (D3D surfaces/textures)
class CRenderTarget2 {
public:
    int       m_iMode;          // +0x00
    IUnknown *m_pSurface1;      // +0x04 (this+1 in DWORD)
    IUnknown *m_pSurface2;      // +0x08 (this+2 in DWORD)
    IUnknown *m_pSurface3;      // +0x0C (this+3 in DWORD)

    void Destroy(void);
};

static CRenderTarget2 g_RenderTarget2_inst;
static unsigned char g_RenderTarget2_guard;

static void __cdecl RenderTarget2_Dtor_atexit(void) {}

// 0x004BFD20 - CRenderTarget2::GetInstance (51B)
extern "C" CRenderTarget2 *__cdecl RenderTarget2_GetInstance(void)
{
    if ((g_RenderTarget2_guard & 1) == 0)
    {
        g_RenderTarget2_guard |= 1;
        memset(&g_RenderTarget2_inst, 0, sizeof(g_RenderTarget2_inst));
        atexit(RenderTarget2_Dtor_atexit);
    }
    return &g_RenderTarget2_inst;
}

// 0x004C0400 - CRenderTarget2::Destroy (65B)
// Releases 3 COM interfaces via IUnknown::Release (vtable slot 2 = offset 8)
void CRenderTarget2::Destroy(void)
{
    if (m_pSurface2)
    {
        (*(void (__stdcall **)(IUnknown *))(*(int *)m_pSurface2 + 8))(m_pSurface2);
        m_pSurface2 = 0;
    }
    if (m_pSurface1)
    {
        (*(void (__stdcall **)(IUnknown *))(*(int *)m_pSurface1 + 8))(m_pSurface1);
        m_pSurface1 = 0;
    }
    if (m_pSurface3)
    {
        (*(void (__stdcall **)(IUnknown *))(*(int *)m_pSurface3 + 8))(m_pSurface3);
        m_pSurface3 = 0;
    }
}
