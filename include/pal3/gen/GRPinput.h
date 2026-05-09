#pragma once
// Auto-generated from IDA decomp - GRPinput
// 43 methods

class GRPinput {
public:
    int Create(void *hInst, int hwnd, int flag);  // 0x004020E0
    int SetMouseLimits(int a, int b, int c, int d);  // 0x00402270
    int SetMode(int mode);  // 0x004022B0
    __int16 GetKeyState(unsigned __int16 key);  // 0x004022C0
    static BOOL GetCursorPos(void *pPoint);  // 0x004022E0
    int GetMousePos(void *pOut, void *pOut2);  // 0x004022F0
    int AcquireDevices();  // 0x00402310
    int ReleaseDevices();  // 0x00402380
    static GRPinput *__thiscall(GRPinput *this) GRPinput();  // 0x00402400
    char ~GRPinput(int a2, int a3);  // 0x004024F0
    int Create();  // 0x00402570
    int SetMouseAbs(int a2, int a3, int a4);  // 0x00402A90
    char SetJoystickAbs();  // 0x00402B00
    static int() RunJoystickControlPanel();  // 0x00402B60
    static int() ClearKeyBuffer();  // 0x00402B70
    static void() SetMouseLimits();  // 0x00402B80
    static void() SetJoystickLimits();  // 0x00402B90
    static int SetMousePos(int a1);  // 0x00402BA0
    void SetMouseFreePos();  // 0x00402BF0
    char SetJoystickPos(const char *a2, int a3);  // 0x00402C40
    char SetJoystickFreePos(float a2);  // 0x00402D00
    char SetMouseSensitivity();  // 0x00402D20
    int GetMouseSensitivity(int a2);  // 0x00402FA0
    static _BYTE *__thiscall(int this, unsigned int a2) GetKeyState();  // 0x00403000
    static int() GetMousePos();  // 0x00403140
    static int() GetMouseFreePos();  // 0x00403150
    static void() GetMouseDeltas();  // 0x00403160
    static void() GetJoystickPos();  // 0x00403170
    BOOL GetJoystickFreePos(int a2, int a3);  // 0x00403180
    int AcquireMouse();  // 0x00403370
    void UnacquireMouse();  // 0x004033F0
    void AcquireJoystick();  // 0x00403410
    void UnacquireJoystick();  // 0x00403470
    void AcquireKeyboard();  // 0x004034B0
    void UnacquireKeyboard();  // 0x004034E0
    int Update();  // 0x00403560
    void CheckKeyEvents(const char *a2);  // 0x00403640
    static float *__cdecl(float *a1, int a2) InitShiftedKeys();  // 0x004038F0
    void InitDIKToKEY(unsigned __int16 *a2);  // 0x004039D0
    static int GetKey(int a1);  // 0x00404020
    int GetCharKey();  // 0x00404060
    unsigned int DecideKeyStatus(gbRay *a2, int a3);  // 0x00404150
    int IsAnyKeyPressed();  // 0x004042D0
};
