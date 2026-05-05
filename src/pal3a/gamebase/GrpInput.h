#ifndef PAL3A_GRPINPUT_H
#define PAL3A_GRPINPUT_H

#include "pal3a_types.h"

class GRPinput {
public:
    char _data[10584];

    void SetJoystickAbs();
    void SetMouseAbs();
    void SetMouseSensitivity(float factor);
    void AcquireMouse();
    void AcquireJoystick();
    void SetJoystickPos(long x, long y);
    void CheckKeyEvents(ulong key, int isPressed);
    void SetMouseFreePos(long x, long y);
    void GetJoystickPos(long * x, long * y);
    void GetMouseFreePos(long * x, long * y);
    float GetMouseSensitivity();
    void InitShiftedKeys();
    unsigned short GetShiftedKeyState(ushort key);
    void UnacquireKeyboard();
    void UnacquireMouse();
    void RunJoystickControlPanel(void * hWnd);
    int Create(void * hInst, void * hWnd, int ExclusiveMouseAccess);
    void Update();
    void RunMouseControlPanel(void * hWnd);
    void SetActiveDevices(int bMouse, int bKeyboard, int bJoystick);
    void SetJoystickLimits(long x1, long y1, long x2, long y2);
    int GetKey(ulong sKey);
    unsigned long GetKey();
    unsigned short GetKeyRaw(ushort key);
    bool IsAnyKeyPressed();
    void GetJoystickDeltas(long * x, long * y);
    void SetJoystickFreePos(long x, long y);
    void GetMouseDeltas(long * x, long * y);
    void SetMouseLimits(long x1, long y1, long x2, long y2);
    int DecideKeyStatus(ulong thisTime, ulong cKey, int blKey);
    void AcquireKeyboard();
    void GetJoystickFreePos(long * x, long * y);
    void InitDIKToKEY();
    void ClearKeyBuffer();
    void UnacquireJoystick();
    int GetCharKey(ulong cKey);
    void GetMousePos(tagPOINT * tPoint);
    unsigned short GetKeyState(ushort key);
    ~GRPinput();
    void SetMousePos(long x, long y);
    GRPinput();
};

int EnumJoystick(DIDEVICEINSTANCEA * pdinst, void * pvRef);

#endif // PAL3A_GRPINPUT_H
