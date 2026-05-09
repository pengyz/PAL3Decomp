// PAL3.exe gamebase/ScreenMode.cpp — CScreenMode 类实现
// 地址范围: 0x0053C2D0-0x0053EA60
// PDB: 无此类定义 (PAL3 特有, PAL3A 中不存在)

#include <windows.h>

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
// === STUB: 0x0053C440 ===
extern "C" int __cdecl sub_53C440(void) { return 0; }
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
// === STUB: 0x0053EA60 - AudioFadeOut ===
extern "C" void __cdecl sub_53EA60(int) {}
// === STUB: 0x0053D150 ===
extern "C" int __cdecl sub_53D150(void) { return 0; }
// === STUB: 0x0053D1A0 ===
extern "C" void __cdecl sub_53D1A0(void) {}
