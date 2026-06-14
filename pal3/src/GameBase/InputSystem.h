#pragma once
// Auto-generated: InputSystem

class InputSystem {
public:
    _BYTE _tail_000[36]; // +0x0
    // total size: 0x24 (36)

    static void ProcessFrame(char *pInputState); // 0x00410360
    static void ProcessMouse(int nVal); // 0x0041C540
    void ProcessKeyboard(); // 0x0041C710
    int SetCameraTransition(int nMode, int nStart, int nTarget, int nPosX, int nPosY, int nPosZ, int bTargetCoord); // 0x0041C9A0
};
