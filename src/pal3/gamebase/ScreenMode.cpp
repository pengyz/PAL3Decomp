// PAL3.exe gamebase/ScreenMode.cpp — CScreenMode 类实现
// 地址范围: 0x0053C2D0-0x0053EA60
// PDB: 无此类定义 (PAL3 特有, PAL3A 中不存在)

#include <windows.h>
#include <string.h>
#include <stdlib.h>

struct gbAudioManager;

class CScreenMode {
public:
    void Restore(void);
};

// === STUB: CScreenMode::Restore — 0x0053DEF0 ===
void CScreenMode::Restore(void) {}

// DisplayConfig: 显示配置对象 (全局 g_DisplayConfig 位于 0x00A3A7D8)
struct DisplayConfig {
    int   m_nFlags;          // +0x00
    int   m_nSettingWidth;   // +0x04
    int   m_nSettingHeight;  // +0x08
    int  *m_pDisplayMode;    // +0x0C — 指向 {width, height, ...} 结构
};

// 0x0053C710 - DisplayConfig::GetWidth (11B)
extern "C" int __cdecl DisplayConfig_GetWidth(DisplayConfig *pThis)
{
    int *pMode = pThis->m_pDisplayMode;
    if (pMode)
        return pMode[0];
    return 0;
}

// 0x0053C720 - DisplayConfig::GetHeight (12B)
extern "C" int __cdecl DisplayConfig_GetHeight(DisplayConfig *pThis)
{
    int *pMode = pThis->m_pDisplayMode;
    if (pMode)
        return pMode[1];
    return 0;
}

// 0x0053C6F0 - CScreenMode::SetViewport (17B)
// 设置视口位置 (this+1 = x, this+2 = y in DWORD offsets)
extern "C" int __cdecl CScreenMode_SetViewport(int *pThis, int nX, int nY)
{
    pThis[1] = nX;
    pThis[2] = nY;
    return nX;
}
// 0x0053C440 - gbGfxManager_D3D::CreateDevice thunk (32B)
// 纯转发到 sub_5694F0 (gbGfxManager_D3D 的方法)
extern "C" int __cdecl sub_5694F0(void *, int, int, int, int);
extern "C" int __cdecl CScreenMode_CreateDevice(void *pThis, int nAdapter, int nDevType, int nBehavior, int nFormat)
{
    return sub_5694F0(pThis, nAdapter, nDevType, nBehavior, nFormat);
}
// === STUB: 0x0053CDD0 ===
extern "C" void __cdecl sub_53CDD0(int) {}
// === STUB: 0x0053DD70 ===
extern "C" void __cdecl sub_53DD70(int) {}
// === STUB: 0x0053DF70 - CScreenMode::GetInstance ===
extern "C" int __cdecl sub_53DF70(void) { return 0; }
// === STUB: 0x0053E490 - AudioUpdate ===
extern "C" void __cdecl sub_53E490(int) {}
// === STUB: 0x0053E500 ===
extern "C" int __cdecl sub_53E500(int) { return 0; }
// === STUB: 0x0053E950 - AudioStopAll ===
extern "C" void __cdecl sub_53E950(int) {}

// CScreenMode 音频子系统部分布局 (从 AudioFadeOut/AudioUpdate 逆推)
struct CScreenMode_Audio {
    int   m_nUnk00;              // +0x00
    int   m_nUnk04;              // +0x04
    int   m_nUnk08;              // +0x08
    char *m_pCurrentSoundName;   // +0x0C (byte offset 12)
    int   m_bSoundPlaying;       // +0x10 (byte offset 16)
    int   m_nUnk14;              // +0x14
    int  *m_pFadeTarget;         // +0x18 (byte offset 24)
};

extern "C" void __cdecl sub_53E740(CScreenMode_Audio *, const char *, int *);
char byte_56A634[];

// 0x0053EA60 - AudioFadeOut (30B)
extern "C" void __cdecl AudioFadeOut(CScreenMode_Audio *pAudio)
{
    if (pAudio->m_bSoundPlaying)
    {
        char *pName = pAudio->m_pCurrentSoundName;
        if (!pName)
            pName = byte_56A634;
        sub_53E740(pAudio, pName, pAudio->m_pFadeTarget);
    }
}
// 0x0053D150 - SoundContext::GetInstance (51B)
// 单例模式: guard check → ctor → atexit → return instance
static char g_SoundContext_inst[32];
static unsigned char g_SoundContext_guard;
extern "C" void __cdecl SoundContext_Ctor(void *pThis);
static void __cdecl SoundContext_Dtor_atexit(void) {}

extern "C" void *__cdecl SoundContext_GetInstance(void)
{
    if ((g_SoundContext_guard & 1) == 0)
    {
        g_SoundContext_guard |= 1;
        SoundContext_Ctor(g_SoundContext_inst);
        atexit(SoundContext_Dtor_atexit);
    }
    return g_SoundContext_inst;
}

// === STUB: SoundContext 构造函数 (0x0053D0B0) ===
void __cdecl SoundContext_Ctor(void *pThis) { memset(pThis, 0, 32); }
// 0x0053D1A0 - SoundContext::SetResolution (46B)
struct SoundResContext {
    int m_nFlags;
    int m_nCurrent;
};

struct SoundContext_Resolution {
    SoundResContext m_width;   // [0],[1]
    int _pad[2];               // [2],[3]
    SoundResContext m_height;  // [4],[5]
};

extern "C" void __cdecl sub_432770(SoundResContext *, int, int);

extern "C" void __cdecl SoundContext_SetResolution(int nWidth, int nHeight)
{
    SoundContext_Resolution *pRes = (SoundContext_Resolution *)SoundContext_GetInstance();
    if (nWidth)
        sub_432770(&pRes->m_width, pRes->m_width.m_nCurrent, nWidth);
    if (nHeight)
        sub_432770(&pRes->m_height, pRes->m_height.m_nCurrent, nHeight);
}
