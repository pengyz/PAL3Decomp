#pragma once
// Auto-generated: ARC_RoleAtt

class ARC_RoleAtt {
public:
    unsigned long id; // +0x0
    unsigned short type; // +0x4
    char Remark[512]; // +0x6
    char ModelID[30]; // +0x206
    char ImageID[30]; // +0x224
    int att[5]; // +0x244
    char name[32]; // +0x258
    int lv; // +0x278
    int rolevalue[12]; // +0x27C
    unsigned char fightstate[31]; // +0x2AC
    int RoundNum; // +0x2CC
    int SAID; // +0x2D0
    float Escape; // +0x2D4
    unsigned short haogan[5]; // +0x2D8
    int exp; // +0x2E4
    unsigned short gold; // +0x2E8
    unsigned long NormalAtkID; // +0x2EC
    unsigned char height; // +0x2F0
    unsigned char move; // +0x2F1
    unsigned char attackrange; // +0x2F2
    unsigned char speed1; // +0x2F3
    unsigned char speed2; // +0x2F4
    unsigned long skill[4]; // +0x2F8
    unsigned char skill_lv[3]; // +0x308
    int RoleQiAdd; // +0x30C
    float append[10]; // +0x310
    unsigned long normalplunder; // +0x338
    short normalplundernum; // +0x33C
    unsigned long shikuai; // +0x340
    unsigned long shikuaiskill; // +0x344
    short shikuaisucc; // +0x348
    short stealmoney; // +0x34A
    unsigned long steal; // +0x34C
    short stealnum; // +0x350
    short getmoney; // +0x352
    // total size: 0x354 (852)

};
