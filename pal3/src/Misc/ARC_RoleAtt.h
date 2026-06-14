#pragma once
// Auto-generated: ARC_RoleAtt

class ARC_RoleAtt {
public:
    UINT id; // +0x0
    WORD type; // +0x4
    char Remark[512]; // +0x6
    char ModelID[30]; // +0x206
    char ImageID[30]; // +0x224
    char _gap_242[2]; // +0x242
    int att[5]; // +0x244
    char name[32]; // +0x258
    int lv; // +0x278
    int rolevalue[12]; // +0x27C
    _BYTE fightstate[31]; // +0x2AC
    char _gap_2CB[1]; // +0x2CB
    int RoundNum; // +0x2CC
    int SAID; // +0x2D0
    int Escape; // +0x2D4
    WORD haogan[5]; // +0x2D8
    char _gap_2E2[2]; // +0x2E2
    int exp; // +0x2E4
    WORD gold; // +0x2E8
    char _gap_2EA[2]; // +0x2EA
    UINT NormalAtkID; // +0x2EC
    BYTE height; // +0x2F0
    BYTE move; // +0x2F1
    BYTE attackrange; // +0x2F2
    BYTE speed1; // +0x2F3
    BYTE speed2; // +0x2F4
    char _gap_2F5[3]; // +0x2F5
    UINT skill[4]; // +0x2F8
    _BYTE skill_lv[3]; // +0x308
    char _gap_30B[1]; // +0x30B
    int RoleQiAdd; // +0x30C
    float append[10]; // +0x310
    UINT normalplunder; // +0x338
    short normalplundernum; // +0x33C
    char _gap_33E[2]; // +0x33E
    UINT shikuai; // +0x340
    UINT shikuaiskill; // +0x344
    short shikuaisucc; // +0x348
    short stealmoney; // +0x34A
    UINT steal; // +0x34C
    short stealnum; // +0x350
    short getmoney; // +0x352
    // total size: 0x354 (852)

};
