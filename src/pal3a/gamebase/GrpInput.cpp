#include "GrpInput.h"

void GRPinput::SetJoystickAbs()
{
    /* stub */
}

void GRPinput::SetMouseAbs()
{
    /* stub */
}

void GRPinput::SetMouseSensitivity(float factor)
{
    /* stub */
}

void GRPinput::AcquireMouse()
{
    /* stub */
}

void GRPinput::AcquireJoystick()
{
    /* stub */
}

void GRPinput::SetJoystickPos(long x, long y)
{
    /* stub */
}

void GRPinput::CheckKeyEvents(ulong key, int isPressed)
{
    /* stub */
}

void GRPinput::SetMouseFreePos(long x, long y)
{
    /* stub */
}

void GRPinput::GetJoystickPos(long * x, long * y)
{
    /* stub */
}

void GRPinput::GetMouseFreePos(long * x, long * y)
{
    /* stub */
}

float GRPinput::GetMouseSensitivity()
{
    /* stub */
    return 0.0f;
}

void GRPinput::InitShiftedKeys()
{
    /* stub */
}

unsigned short GRPinput::GetShiftedKeyState(ushort key)
{
    /* stub */
    return 0;
}

void GRPinput::UnacquireKeyboard()
{
    /* stub */
}

void GRPinput::UnacquireMouse()
{
    /* stub */
}

void GRPinput::RunJoystickControlPanel(void * hWnd)
{
    /* stub */
}

int GRPinput::Create(void * hInst, void * hWnd, int ExclusiveMouseAccess)
{
    /* stub */
    return 0;
}

void GRPinput::Update()
{
    /* stub */
}

void GRPinput::RunMouseControlPanel(void * hWnd)
{
    /* stub */
}

void GRPinput::SetActiveDevices(int bMouse, int bKeyboard, int bJoystick)
{
    /* stub */
}

void GRPinput::SetJoystickLimits(long x1, long y1, long x2, long y2)
{
    /* stub */
}

int GRPinput::GetKey(ulong sKey)
{
    /* stub */
    return 0;
}

unsigned long GRPinput::GetKey()
{
    /* stub */
    return 0;
}

unsigned short GRPinput::GetKeyRaw(ushort key)
{
    /* stub */
    return 0;
}

bool GRPinput::IsAnyKeyPressed()
{
    /* stub */
    return FALSE;
}

void GRPinput::GetJoystickDeltas(long * x, long * y)
{
    /* stub */
}

void GRPinput::SetJoystickFreePos(long x, long y)
{
    /* stub */
}

void GRPinput::GetMouseDeltas(long * x, long * y)
{
    /* stub */
}

void GRPinput::SetMouseLimits(long x1, long y1, long x2, long y2)
{
    /* stub */
}

int GRPinput::DecideKeyStatus(ulong thisTime, ulong cKey, int blKey)
{
    /* stub */
    return 0;
}

void GRPinput::AcquireKeyboard()
{
    /* stub */
}

void GRPinput::GetJoystickFreePos(long * x, long * y)
{
    /* stub */
}

void GRPinput::InitDIKToKEY()
{
    /* stub */
}

void GRPinput::ClearKeyBuffer()
{
    /* stub */
}

void GRPinput::UnacquireJoystick()
{
    /* stub */
}

int GRPinput::GetCharKey(ulong cKey)
{
    /* stub */
    return 0;
}

void GRPinput::GetMousePos(tagPOINT * tPoint)
{
    /* stub */
}

unsigned short GRPinput::GetKeyState(ushort key)
{
    /* stub */
    return 0;
}

GRPinput::~GRPinput()
{
    /* stub */
}

void GRPinput::SetMousePos(long x, long y)
{
    /* stub */
}

GRPinput::GRPinput()
{
    /* stub */
}

int EnumJoystick(DIDEVICEINSTANCEA * pdinst, void * pvRef)
{
    /* stub */
    return 0;
}

