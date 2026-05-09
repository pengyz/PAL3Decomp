// PAL3.exe gamebase/GRPinput.cpp — GRPinput 类实现
// 地址范围: 0x004020E0-0x004022C0+
// PDB suggested_source: gamebase/GRPinput.cpp

#include <windows.h>

class GRPinput {
public:
    int m_nUnk0;        // +0x00
    int m_nUnk4;        // +0x04
    int m_nUnk8;        // +0x08
    int m_nMode;        // +0x0C (offset 3 dwords = 12 bytes)
    char m_pad[92];     // padding to reach offset 104
    short m_keyState[256]; // +0x68 (offset 104)

    int SetMode(int mode);
    short GetKeyState(unsigned short key);
};

// 0x004022B0 - GRPinput::SetMode (10B, matched)
int GRPinput::SetMode(int mode)
{
    m_nMode = mode;
    return mode;
}

// 0x004022C0 - GRPinput::GetKeyState (18B)
short GRPinput::GetKeyState(unsigned short key)
{
    return *((unsigned char *)this + key + 104);
}

// === STUB: 0x004020E0 - DirectInput 初始化 ===
extern "C" int __cdecl sub_4020E0(void *ppv, HINSTANCE hInst, HWND hwnd, int flag) { return 1; }

// === STUB: 0x00402270 - 设置输入范围 ===
extern "C" void __cdecl sub_402270(void *ppv, int a, int b, int c, int d) {}
