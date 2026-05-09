// PAL3.exe gamebase/GRPinput.cpp — GRPinput 类实现
// 地址范围: 0x004020E0-0x00402400
// PDB suggested_source: gamebase/GRPinput.cpp (推断)

#include <windows.h>

class GRPinput {
public:
    void Poll(void);
    void SetMouseAbs(unsigned int time, int btn, int state);
};

// === STUB: GRPinput::Poll ===
void GRPinput::Poll(void) {}

// === STUB: GRPinput::SetMouseAbs ===
void GRPinput::SetMouseAbs(unsigned int, int, int) {}

// === STUB: 0x004020E0 - DirectInput 初始化 ===
extern "C" int __cdecl sub_4020E0(void *ppv, HINSTANCE hInst, HWND hwnd, int flag) { return 1; }

// === STUB: 0x00402270 - 设置输入范围 ===
extern "C" void __cdecl sub_402270(void *ppv, int a, int b, int c, int d) {}

// === STUB: 0x004022B0 - GRPinput::SetMode ===
extern "C" void __cdecl sub_4022B0(void *ppv, int mode) {}

// === STUB: 0x004022C0 ===
extern "C" short __cdecl sub_4022C0(void *, unsigned short) { return 0; }
