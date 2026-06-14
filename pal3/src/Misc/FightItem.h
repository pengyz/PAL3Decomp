#pragma once
// Auto-generated: FightItem

class FightItem {
public:
    UINT id; // +0x0
    char name[32]; // +0x4
    char ModelID[30]; // +0x24
    char ImageID[30]; // +0x42
    char desc[512]; // +0x60
    int price; // +0x260
    BYTE type; // +0x264
    BYTE weapontype; // +0x265
    _BYTE user[5]; // +0x266
    _BYTE att[5]; // +0x26B
    int gu; // +0x270
    BYTE special; // +0x274
    BYTE fanwei; // +0x275
    BYTE space; // +0x276
    _BYTE rvtype[12]; // +0x277
    char _gap_283[1]; // +0x283
    short rolevalue[12]; // +0x284
    _BYTE fstype[31]; // +0x29C
    char _gap_2BB[1]; // +0x2BB
    short fightstate[31]; // +0x2BC
    char _gap_2FA[2]; // +0x2FA
    int tosshurt; // +0x2FC
    int lian; // +0x300
    short saveqi; // +0x304
    short saveshen; // +0x306
    short addbaoji; // +0x308
    short addteji; // +0x30A
    int embracer; // +0x30C
    UINT compose_material; // +0x310
    int compose_type; // +0x314
    UINT compose_final; // +0x318
    UINT compose_intimacy; // +0x31C
    // total size: 0x320 (800)

};
