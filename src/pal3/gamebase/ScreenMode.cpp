// PAL3.exe gamebase/ScreenMode.cpp — CScreenMode 类实现
// 地址范围: 0x0053CF80-0x0053E950
// PDB suggested_source: gamebase/ScreenMode.cpp (推断)

#include "pal3/CScreenMode.h"

static CScreenMode g_ScreenModeInstance;

// 0x0053DF70 - CScreenMode::GetInstance (6B, matched)
CScreenMode *CScreenMode::GetInstance(void) { return &g_ScreenModeInstance; }

// extern "C" wrapper — 其他 TU 通过 C linkage 调用
extern "C" int __cdecl sub_53DF70(void) { return (int)&g_ScreenModeInstance; }

// 0x0053CDD0 - CScreenMode::SetState (13B)
void CScreenMode::SetState(int state) { *(int *)((char *)this + 0x1224) = state; }

// 0x0053E500 - CScreenMode::GetAudioManager (7B)
gbAudioManager *CScreenMode::GetAudioManager(void) { return *(gbAudioManager **)((char *)this + 0x328); }

// 0x0053DEF0 - CScreenMode::Restore (stub, needs analysis)
void CScreenMode::Restore(void) {}

// C linkage wrappers for PAL3::Update
extern "C" int __cdecl sub_53CDD0(int a) { g_ScreenModeInstance.SetState(a); return 0; }
extern "C" int __cdecl sub_53E500(int a) { return (int)((CScreenMode *)a)->GetAudioManager(); }

// === STUB: 0x0053DD70 - CScreenMode::SetMode ===
extern "C" void __cdecl sub_53DD70(int) {}

// === STUB: 0x0053E490 - AudioUpdate ===
extern "C" void __cdecl sub_53E490(int) {}

// === STUB: 0x0053E950 - AudioStopAll ===
extern "C" void __cdecl sub_53E950(int) {}

// === STUB: 0x0053EA60 - AudioFadeOut ===
extern "C" void __cdecl sub_53EA60(int) {}
