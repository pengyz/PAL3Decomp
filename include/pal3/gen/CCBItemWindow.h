#pragma once
// Auto-generated from IDA decomp - CCBItemWindow
// 8 methods

class CCBItemWindow {
public:
    static stdiobuf *__thiscall(stdiobuf *Block, char a2) CCBItemWindow();  // 0x0051B160
    int Reset();  // 0x0051B1D0
    char Create(_DWORD *a2, int a3);  // 0x0051B210
    int Destroy();  // 0x0051B4B0
    BOOL HandleInput(int a2, int a3);  // 0x0051B570
    int OnMessage(int a2);  // 0x0051B5D0
    static _DWORD *__thiscall(_DWORD *this) Update();  // 0x0051B620
    static stdiobuf *__thiscall(stdiobuf *Block, char a2) CreateButtons();  // 0x0051B670
};
