// PAL3.exe effect/ScreenEffectMgr.cpp — ScreenEffectMgr 单例
// PDB: ScreenEffectMgr (size=152)
// Address: 0x004BE590

#include <stdlib.h>
#include <string.h>

// PDB: ScreenEffectMgr (size=152)
//   +0x0004 ScreenFadeIn    m_fadeIn      (size=28)
//   +0x0020 ScreenFadeOut   m_fadeOut     (size=24)
//   +0x0038 ScreenFadeWhite m_fadeWhite   (size=24)
//   +0x0050 ScreenFadeWhite2 m_fadeWhite2 (size=24)
//   +0x0068 std::queue<...> m_activeQueue (size=48)
struct ScreenEffectMgr {
    char m_data[152];
};

static ScreenEffectMgr g_ScreenEffectMgr_inst;
static unsigned char g_ScreenEffectMgr_guard;

static void __cdecl ScreenEffectMgr_Dtor_atexit(void) {}

// === STUB: ScreenEffectMgr 构造函数 ===
static void ScreenEffectMgr_Ctor(ScreenEffectMgr *pThis)
{
    memset(pThis, 0, sizeof(ScreenEffectMgr));
}

// 0x004BE590 - ScreenEffectMgr::GetInstance (51B)
// call_graph 中名为 RenderPrepare，实际是 ScreenEffectMgr 单例
extern "C" ScreenEffectMgr *__cdecl ScreenEffectMgr_GetInstance(void)
{
    if ((g_ScreenEffectMgr_guard & 1) == 0)
    {
        g_ScreenEffectMgr_guard |= 1;
        ScreenEffectMgr_Ctor(&g_ScreenEffectMgr_inst);
        atexit(ScreenEffectMgr_Dtor_atexit);
    }
    return &g_ScreenEffectMgr_inst;
}
