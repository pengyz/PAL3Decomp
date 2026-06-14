#pragma once
// Auto-generated: GRPinput

#include "GRP_KEYREG.h"

class IDirectInput8;
class IDirectInputDevice8;

class GRPinput {
public:
    IDirectInput8 * m_lpDI; // +0x0
    IDirectInputDevice8 * m_lpDIDKeyboard; // +0x4
    IDirectInputDevice8 * m_lpDIDMouse; // +0x8
    float m_mouseSensitivity; // +0xC
    int m_mouseMinX; // +0x10
    int m_mouseMinY; // +0x14
    int m_mouseMaxX; // +0x18
    int m_mouseMaxY; // +0x1C
    int m_joystickMinX; // +0x20
    int m_joystickMinY; // +0x24
    int m_joystickMaxX; // +0x28
    int m_joystickMaxY; // +0x2C
    POINT m_mousept; // +0x30
    char _gap_034[4]; // +0x34
    int m_mouseX; // +0x38
    int m_mouseY; // +0x3C
    int m_mouseFreeX; // +0x40
    int m_mouseFreeY; // +0x44
    int m_mouseDeltaX; // +0x48
    int m_mouseDeltaY; // +0x4C
    int m_joystickX; // +0x50
    int m_joystickY; // +0x54
    int m_joystickFreeX; // +0x58
    int m_joystickFreeY; // +0x5C
    int m_joystickDeltaX; // +0x60
    int m_joystickDeltaY; // +0x64
    _BYTE m_keyStates[270]; // +0x68
    char _gap_176[2]; // +0x176
    _BYTE m_keyRaw[256]; // +0x178
    ULONG m_keyPressTimes[270]; // +0x278
    ULONG m_keyDragStartPositions[270][2]; // +0x6B0
    _BYTE m_shiftedKeyStates[270]; // +0xF20
    char _gap_102E[2]; // +0x102E
    ULONG m_DIKToKEY[256]; // +0x1030
    char MouseState[20]; // +0x1430
    ULONG charTOscan[256]; // +0x1444
    int KeyTransformation[10]; // +0x1844
    int m_bMouse; // +0x186C
    int m_bKeyboard; // +0x1870
    int m_bJoystick; // +0x1874
    GRP_KEYREG KeyInfo[270]; // +0x1878
    char _tail_1CB0[3240]; // +0x1CB0
    // total size: 0x2958 (10584)

    int Create(HINSTANCE *hInst, int hwnd, int flag); // 0x004020E0
    int HandleDeviceInput(int nMouse, int nKeyboard, int nVal3); // 0x004021E0
    void Reset(); // 0x00402220
    void SetMouseLimits(int a, int b, int c, int d); // 0x00402270
    BOOL SetCursorPos(int X, int Y); // 0x00402290
    int SetMode(int mode); // 0x004022B0
    __int16 GetKeyState(unsigned __int16 key); // 0x004022C0
    BOOL GetCursorPos(); // 0x004022E0
    void GetMousePos(void *pOut, void *pOut2); // 0x004022F0
    int AcquireDevices(); // 0x00402310
    int _thunk_vtbl8(); // 0x00402360
    int ReleaseDevices(); // 0x00402380
    GRPinput(); // 0x00402400
    void _GRPinput(int nVal, int nVal2); // 0x004024F0
    int InitKeyMappings(); // 0x00402570
    int BuildKeyMap(); // 0x00402640
    void SetMouseAbs(int nVal, int nVal2, int nVal3); // 0x00402A90
    void SetJoystickAbs(); // 0x00402B00
    void RunJoystickControlPanel(void *hWnd); // 0x00402B60
    void ClearKeyBuffer(); // 0x00402B70
    void SetJoystickLimits(); // 0x00402B90
    GRPinput * SetMousePos(); // 0x00402BA0
    void SetMouseFreePos(); // 0x00402BF0
    void SetJoystickPos(const char *x, int y); // 0x00402C40
    void SetJoystickFreePos(float x); // 0x00402D00
    void SetMouseSensitivity(); // 0x00402D20
    int GetMouseSensitivity(int nVal); // 0x00402FA0
    _BYTE * PollInputState(unsigned int key); // 0x00403000
    void GetMouseFreePos(); // 0x00403150
    void GetMouseDeltas(); // 0x00403160
    void GetJoystickPos(); // 0x00403170
    BOOL GetJoystickFreePos(int x, int y); // 0x00403180
    int GetState(); // 0x004031D0
    GRPinput * AcquireMouse(); // 0x00403370
    void UnacquireMouse(); // 0x004033F0
    void AcquireJoystick(); // 0x00403410
    void UnacquireJoystick(); // 0x00403470
    void AcquireKeyboard(); // 0x004034B0
    void UnacquireKeyboard(); // 0x004034E0
    void Update(); // 0x00403560
    void CheckKeyEvents(const char *key); // 0x00403640
    static float * InitShiftedKeys(float *pfVal, int nVal); // 0x004038F0
    void InitDIKToKEY(unsigned __int16 *pwVal); // 0x004039D0
    int ProcessInputFrame(char *pszBuf); // 0x00403B80
    GRPinput * GetKey(); // 0x00404020
    int GetCharKey(); // 0x00404060
    int DecideKeyStatus(gbRay *a2, unsigned int a3); // 0x00404150
    bool IsAnyKeyPressed(); // 0x004042D0
    void ProcessButtonHold(float fDelta); // 0x0046AEA0
    void ProcessMouseInput(float fVal); // 0x0046F480
};
