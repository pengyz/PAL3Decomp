#pragma once
// Auto-generated: ARC_RoleAtt

class ARC_RoleAtt {
public:
    DWORD id; // +0x0
    WORD type; // +0x4
    char Remark[512]; // +0x6
    char ModelID[30]; // +0x206
    char ImageID[30]; // +0x224
    int att[5]; // +0x244
    char name[32]; // +0x258
    int lv; // +0x278
    int rolevalue[12]; // +0x27C
    BYTE fightstate[31]; // +0x2AC
    int RoundNum; // +0x2CC
    int SAID; // +0x2D0
    float Escape; // +0x2D4
    WORD haogan[5]; // +0x2D8
    int exp; // +0x2E4
    WORD gold; // +0x2E8
    DWORD NormalAtkID; // +0x2EC
    BYTE height; // +0x2F0
    BYTE move; // +0x2F1
    BYTE attackrange; // +0x2F2
    BYTE speed1; // +0x2F3
    BYTE speed2; // +0x2F4
    DWORD skill[4]; // +0x2F8
    BYTE skill_lv[3]; // +0x308
    int RoleQiAdd; // +0x30C
    float append[10]; // +0x310
    DWORD normalplunder; // +0x338
    short normalplundernum; // +0x33C
    DWORD shikuai; // +0x340
    DWORD shikuaiskill; // +0x344
    short shikuaisucc; // +0x348
    short stealmoney; // +0x34A
    DWORD steal; // +0x34C
    short stealnum; // +0x350
    short getmoney; // +0x352
    // total size: 0x354 (852)

};
