#pragma once
// Auto-generated: CGameData

class CGameData {
public:
    char _pad_000[76]; // +0x0
    int _d04C; // +0x4C
    int _d050; // +0x50
    int _d054; // +0x54
    int _d058; // +0x58
    int _d05C; // +0x5C
    int _d060; // +0x60
    int _d064; // +0x64
    int _d068; // +0x68
    int _d06C; // +0x6C
    int _d070; // +0x70
    char _pad_074[8]; // +0x74
    int _d07C; // +0x7C
    char _pad_080[132]; // +0x80
    int _d104; // +0x104
    char _pad_108[12]; // +0x108
    int _d114; // +0x114
    char _pad_118[604]; // +0x118
    int _d374; // +0x374
    char _pad_378[100]; // +0x378
    int _d3DC; // +0x3DC
    int _d3E0; // +0x3E0
    char _pad_3E4[232]; // +0x3E4
    int _d4CC; // +0x4CC
    char _pad_4D0[100]; // +0x4D0
    int _d534; // +0x534
    int _d538; // +0x538
    char _pad_53C[232]; // +0x53C
    int _d624; // +0x624
    char _pad_628[100]; // +0x628
    int _d68C; // +0x68C
    int _d690; // +0x690
    char _pad_694[544]; // +0x694
    int _d8B4; // +0x8B4
    int _d8B8; // +0x8B8
    char _pad_8BC[12]; // +0x8BC
    int _d8C8; // +0x8C8
    char _pad_8CC[8]; // +0x8CC
    int _d8D4; // +0x8D4
    char _pad_8D8[1024]; // +0x8D8
    int _dCD8; // +0xCD8
    char _pad_CDC[612]; // +0xCDC
    int _dF40; // +0xF40
    char _tail[188]; // +0xF44
    // total size: 0x1000 (4096)

    int InitRoles(int a2); // 0x0044ADE0
    int InitItems(int a2); // 0x0044E660
    void * Init(); // 0x0044F130
    void Destroy(); // 0x0044F430
    int Render(); // 0x0044F5B0
    int SetMode(int mode); // 0x0044F8A0
    int GetMode(); // 0x0044FF60
};
