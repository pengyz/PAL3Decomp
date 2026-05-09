// PAL3.exe effect/RenderTarget.cpp — RenderTarget 单例管理
// PDB source: D:\PAL3A\PAL3\effect\RenderTarget.cpp
// Address range: 0x004BDA60-0x004BDED0

#include <stdlib.h>
#include <string.h>

// PDB: RenderTarget (size=200)
//   +0x0000 int           m_iMode
//   +0x0004 gbTexture_D3D m_Texture     (size=0x60)
//   +0x0064 gbTexture_D3D m_ScreenPlane (size=0x60)
//   +0x00C4 int           m_nState

class CRenderTarget {
public:
    int  m_iMode;
    char m_Texture[0x60];
    char m_ScreenPlane[0x60];
    int  m_nState;

    void Destroy(void);
};

static CRenderTarget g_RenderTarget_inst;
static unsigned char g_RenderTarget_guard;

static void __cdecl RenderTarget_Dtor_atexit(void) {}

// 0x004BDB10 - RenderTarget::Inst (51B)
extern "C" CRenderTarget *__cdecl RenderTarget_GetInstance(void)
{
    if ((g_RenderTarget_guard & 1) == 0)
    {
        g_RenderTarget_guard |= 1;
        memset(&g_RenderTarget_inst, 0, sizeof(g_RenderTarget_inst));
        atexit(RenderTarget_Dtor_atexit);
    }
    return &g_RenderTarget_inst;
}

// 0x004BDED0 - CRenderTarget::Destroy (7B)
void CRenderTarget::Destroy(void)
{
    m_iMode = -1;
}
