#pragma once
// Auto-generated: GRPinput

#include "GRP_KEYREG.h"

class GRPinput {
public:
    IDirectInput8A * m_lpDI; // +0x0
    IDirectInputDevice8A * m_lpDIDKeyboard; // +0x4
    IDirectInputDevice8A * m_lpDIDMouse; // +0x8
    float m_mouseSensitivity; // +0xC
    long m_mouseMinX; // +0x10
    long m_mouseMinY; // +0x14
    long m_mouseMaxX; // +0x18
    long m_mouseMaxY; // +0x1C
    long m_joystickMinX; // +0x20
    long m_joystickMinY; // +0x24
    long m_joystickMaxX; // +0x28
    long m_joystickMaxY; // +0x2C
    tagPOINT m_mousept; // +0x30
    long m_mouseX; // +0x38
    long m_mouseY; // +0x3C
    long m_mouseFreeX; // +0x40
    long m_mouseFreeY; // +0x44
    long m_mouseDeltaX; // +0x48
    long m_mouseDeltaY; // +0x4C
    long m_joystickX; // +0x50
    long m_joystickY; // +0x54
    long m_joystickFreeX; // +0x58
    long m_joystickFreeY; // +0x5C
    long m_joystickDeltaX; // +0x60
    long m_joystickDeltaY; // +0x64
    unsigned char m_keyStates[270]; // +0x68
    unsigned char m_keyRaw[256]; // +0x176
    unsigned long m_keyPressTimes[270]; // +0x278
    unsigned long m_keyDragStartPositions[2][270]; // +0x6B0
    unsigned char m_shiftedKeyStates[270]; // +0xF20
    unsigned long m_DIKToKEY[256]; // +0x1030
    _DIMOUSESTATE2 MouseState; // +0x1430
    unsigned long charTOscan[256]; // +0x1444
    int KeyTransformation[10]; // +0x1844
    int m_bMouse; // +0x186C
    int m_bKeyboard; // +0x1870
    int m_bJoystick; // +0x1874
    GRP_KEYREG KeyInfo[270]; // +0x1878
    // total size: 0x2958 (10584)

    int Create(void *hInst, int hwnd, int flag); // 0x004020E0
    int SetMouseLimits(int a, int b, int c, int d); // 0x00402270
    int SetMode(int mode); // 0x004022B0
    __int16 GetKeyState(unsigned __int16 key); // 0x004022C0
    static BOOL GetCursorPos(void *pPoint); // 0x004022E0
    int GetMousePos(void *pOut, void *pOut2); // 0x004022F0
    int AcquireDevices(); // 0x00402310
    int ReleaseDevices(); // 0x00402380
    GRPinput(); // 0x00402400
    ~GRPinput(); // 0x004024F0
    int Create(); // 0x00402570
    int SetMouseAbs(int a2, int a3, int a4); // 0x00402A90
    char SetJoystickAbs(); // 0x00402B00
    static int RunJoystickControlPanel(); // 0x00402B60
    static int ClearKeyBuffer(); // 0x00402B70
    static void SetMouseLimits(); // 0x00402B80
    static void SetJoystickLimits(); // 0x00402B90
    static int SetMousePos(int a1); // 0x00402BA0
    void SetMouseFreePos(); // 0x00402BF0
    char SetJoystickPos(const char *a2, int a3); // 0x00402C40
    char SetJoystickFreePos(float a2); // 0x00402D00
    char SetMouseSensitivity(); // 0x00402D20
    int GetMouseSensitivity(int a2); // 0x00402FA0
    _BYTE * GetKeyState(unsigned int a2); // 0x00403000
    static int GetMousePos(); // 0x00403140
    static int GetMouseFreePos(); // 0x00403150
    static void GetMouseDeltas(); // 0x00403160
    static void GetJoystickPos(); // 0x00403170
    BOOL GetJoystickFreePos(int a2, int a3); // 0x00403180
    char * AcquireMouse(); // 0x00403370
    void UnacquireMouse(); // 0x004033F0
    void AcquireJoystick(); // 0x00403410
    void UnacquireJoystick(); // 0x00403470
    void AcquireKeyboard(); // 0x004034B0
    void UnacquireKeyboard(); // 0x004034E0
    int Update(); // 0x00403560
    void CheckKeyEvents(const char *a2); // 0x00403640
    static float * InitShiftedKeys(float *a1, int a2); // 0x004038F0
    void InitDIKToKEY(unsigned __int16 *a2); // 0x004039D0
    static int GetKey(int a1); // 0x00404020
    int GetCharKey(); // 0x00404060
    unsigned int DecideKeyStatus(gbRay *a2, int a3); // 0x00404150
    int IsAnyKeyPressed(); // 0x004042D0
};
