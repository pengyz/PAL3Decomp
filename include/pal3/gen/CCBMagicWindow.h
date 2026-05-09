#pragma once
// Auto-generated from IDA decomp - CCBMagicWindow
// 11 methods

class CCBMagicWindow {
public:
    char CCBMagicWindow(int a2, int a3, _DWORD *a4);  // 0x0051B9F0
    int ~CCBMagicWindow(int a2);  // 0x0051BAB0
    int Reset(int a2, int a3);  // 0x0051BB00
    int Create(int a2);  // 0x0051BB40
    static _DWORD *__thiscall(_DWORD *this) ForbidPage();  // 0x0051BB90
    static stdiobuf *__thiscall(stdiobuf *Block, char a2) Destroy();  // 0x0051BBE0
    int OnMessage();  // 0x0051BC50
    char CreateButton(_DWORD *a2, int a3);  // 0x0051BC70
    int Update();  // 0x0051C110
    BOOL SetActivePage(int a2, int a3);  // 0x0051C1B0
    static _DWORD *__thiscall(_DWORD *this) GetActivePage();  // 0x0051C210
};
