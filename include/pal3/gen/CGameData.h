#pragma once
// Auto-generated: CGameData
// [GEN_BROKEN_LAYOUT] No PDB layout available, using IDA-derived size

class CGameData {
public:
    char _data[14544]; // IDA size, no member names available

    int InitRoles(int a2); // 0x0044ADE0
    int InitItems(int a2); // 0x0044E660
    void * Init(); // 0x0044F130
    void Destroy(); // 0x0044F430
    int Render(); // 0x0044F5B0
    int SetMode(int mode); // 0x0044F8A0
    int GetMode(); // 0x0044FF60
};
