#pragma once

struct IDirectInput8A;
struct IDirectInputDevice8A;

class GRPinput {
public:
    IDirectInput8A       *m_lpDI;
    IDirectInputDevice8A *m_lpDIDKeyboard;
    IDirectInputDevice8A *m_lpDIDMouse;
    float                 m_mouseSensitivity;
    long                  m_mouseMinX;
    long                  m_mouseMinY;
    long                  m_mouseMaxX;
    long                  m_mouseMaxY;

    int  SetMode(int mode);
    short GetKeyState(unsigned short key);
    int  SetMouseLimits(long minX, long minY, long maxX, long maxY);
    void Poll(void);
    void SetMouseAbs(unsigned int time, int btn, int state);
};
