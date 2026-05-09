#pragma once
// Auto-generated from IDA decomp - CCBCamControl
// 19 methods

class CCBCamControl {
public:
    static int() CCBCamControl();  // 0x005081D0
    static int() ~CCBCamControl();  // 0x005081E0
    static int() Reset();  // 0x00508220
    static int() Create();  // 0x00508230
    static int() Destroy();  // 0x00508270
    static int() Init();  // 0x00508280
    static int() Update();  // 0x005082C0
    static int() StartList();  // 0x005082D0
    static int() StartList();  // 0x00508310
    static int() StopList();  // 0x00508320
    static int() HandleInput();  // 0x00508360
    static int() UpdateCircleSet();  // 0x00508370
    static char *__thiscall(char *this, int a2) SetCircle();  // 0x005083B0
    char IsPointerUnderMouse();  // 0x005084C0
    static _DWORD *__thiscall(_DWORD *this) LoadPointer();  // 0x00508660
    char DoList();  // 0x00508680
    int ResetListFlag();  // 0x00508690
    int KeepCurCam(int a2);  // 0x00508880
    int DoLineMove(unsigned int a2);  // 0x005088D0
};
