// PAL3.exe gamebase/GRPinput.cpp — GRPinput 类实现
// 地址范围: 0x004020E0-0x004042D0
// PDB source: gamebase/GRPinput.cpp
// Compiler: MSVC 6.0 SP0

#include <windows.h>

// DirectInput 前向声明 (避免依赖 DirectX SDK 头文件)
struct IDirectInput8A;
struct IDirectInputDevice8A;

struct GRPinput {
    IDirectInput8A       *m_lpDI;             // +0x0000
    IDirectInputDevice8A *m_lpDIDKeyboard;    // +0x0004
    IDirectInputDevice8A *m_lpDIDMouse;       // +0x0008
    float                 m_mouseSensitivity; // +0x000C
    long                  m_mouseMinX;        // +0x0010
    long                  m_mouseMinY;        // +0x0014
    long                  m_mouseMaxX;        // +0x0018
    long                  m_mouseMaxY;        // +0x001C
    long                  m_joystickMinX;     // +0x0020
    long                  m_joystickMinY;     // +0x0024
    long                  m_joystickMaxX;     // +0x0028
    long                  m_joystickMaxY;     // +0x002C
    POINT                 m_mousept;          // +0x0030
    long                  m_mouseX;           // +0x0038
    long                  m_mouseY;           // +0x003C
    long                  m_mouseFreeX;       // +0x0040
    long                  m_mouseFreeY;       // +0x0044
    long                  m_mouseDeltaX;      // +0x0048
    long                  m_mouseDeltaY;      // +0x004C
    long                  m_joystickX;        // +0x0050
    long                  m_joystickY;        // +0x0054
    long                  m_joystickFreeX;    // +0x0058
    long                  m_joystickFreeY;    // +0x005C
    long                  m_joystickDeltaX;   // +0x0060
    long                  m_joystickDeltaY;   // +0x0064
    unsigned char         m_keyStates[270];   // +0x0068

    int  SetMode(int mode);
    short GetKeyState(unsigned short key);
    int  SetMouseLimits(long minX, long minY, long maxX, long maxY);
    void Poll(void);
    void SetMouseAbs(unsigned int time, int btn, int state);
};

// 0x004022B0 - GRPinput::SetMode (10B)
// IDA: *(this+3) = a2; return a2;
// this+3 in DWORD units = offset 0x0C = m_mouseSensitivity (reinterpreted as int)
int GRPinput::SetMode(int mode)
{
    *(int *)&m_mouseSensitivity = mode;
    return mode;
}

// 0x004022C0 - GRPinput::GetKeyState (18B)
// IDA: return *(this + a2 + 104);
// offset 104 = 0x68 = m_keyStates
short GRPinput::GetKeyState(unsigned short key)
{
    return m_keyStates[key];
}

// 0x00402270 - GRPinput::SetMouseLimits (31B)
// IDA: *(this+4)=a2; *(this+5)=a3; *(this+6)=a4; *(this+7)=a5; return a4;
// DWORD offsets 4-7 = byte offsets 0x10-0x1C
int GRPinput::SetMouseLimits(long minX, long minY, long maxX, long maxY)
{
    m_mouseMinX = minX;
    m_mouseMinY = minY;
    m_mouseMaxX = maxX;
    m_mouseMaxY = maxY;
    return maxX;
}

// C linkage wrappers (PAL3.cpp calls these via extern "C")
extern "C" void __cdecl sub_402270(void *pThis, int a, int b, int c, int d)
{
    ((GRPinput *)pThis)->SetMouseLimits(a, b, c, d);
}

extern "C" void __cdecl sub_4022B0(void *pThis, int mode)
{
    ((GRPinput *)pThis)->SetMode(mode);
}

extern "C" short __cdecl sub_4022C0(void *pThis, unsigned short key)
{
    return ((GRPinput *)pThis)->GetKeyState(key);
}

// === STUB: GRPinput::Poll ===
void GRPinput::Poll(void) {}

// === STUB: GRPinput::SetMouseAbs ===
void GRPinput::SetMouseAbs(unsigned int, int, int) {}

// === STUB: 0x004020E0 - GRPinput::Create ===
extern "C" int __cdecl sub_4020E0(void *ppv, HINSTANCE hInst, HWND hwnd, int flag) { return 1; }
