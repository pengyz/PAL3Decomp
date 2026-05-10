#pragma once
// Auto-generated: CGameData

class CGameData {
public:
    char _data[14544]; // +0x0
    // total size: 0x38D0 (14544)

    int InitRoles(int a2); // 0x0044ADE0
    int InitItems(int a2); // 0x0044E660
    void * Init(); // 0x0044F130
    void Destroy(); // 0x0044F430
    int Render(); // 0x0044F5B0
    int SetMode(int mode); // 0x0044F8A0
    int GetMode(); // 0x0044FF60
};
