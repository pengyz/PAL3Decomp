#pragma once
// Auto-generated from IDA decomp - CCBControlWindow
// 13 methods

class CCBControlWindow {
public:
    int CCBControlWindow();  // 0x0051A700
    int ~CCBControlWindow();  // 0x0051A880
    int Reset(int a2, unsigned int a3, int a4);  // 0x0051A930
    char Create(_DWORD *a2, int a3, int a4, int a5);  // 0x0051AA20
    int HandleInput(int a2);  // 0x0051AB60
    int KeyPressed();  // 0x0051AC30
    static _DWORD *__thiscall(_DWORD *this) DefaultKey();  // 0x0051AC40
    static stdiobuf *__thiscall(stdiobuf *Block, char a2) HandleEnable();  // 0x0051AC90
    int CheckKeyInput();  // 0x0051AD00
    char OnMessage(_DWORD *a2, int a3);  // 0x0051AD10
    int Update();  // 0x0051AFE0
    BOOL MoveButtons(int a2, int a3);  // 0x0051B0B0
    static _DWORD *__thiscall(_DWORD *this) CreateButton();  // 0x0051B110
};
