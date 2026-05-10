#pragma once
// Auto-generated: FightItem

class FightItem {
public:
    DWORD id; // +0x0
    char name[32]; // +0x4
    char ModelID[30]; // +0x24
    char ImageID[30]; // +0x42
    char desc[512]; // +0x60
    int price; // +0x260
    BYTE type; // +0x264
    BYTE weapontype; // +0x265
    BYTE user[5]; // +0x266
    BYTE att[5]; // +0x26B
    int gu; // +0x270
    BYTE special; // +0x274
    BYTE fanwei; // +0x275
    BYTE space; // +0x276
    BYTE rvtype[12]; // +0x277
    short rolevalue[12]; // +0x284
    BYTE fstype[31]; // +0x29C
    short fightstate[31]; // +0x2BC
    int tosshurt; // +0x2FC
    int lian; // +0x300
    short saveqi; // +0x304
    short saveshen; // +0x306
    short addbaoji; // +0x308
    short addteji; // +0x30A
    int embracer; // +0x30C
    DWORD compose_material; // +0x310
    int compose_type; // +0x314
    DWORD compose_final; // +0x318
    DWORD compose_intimacy; // +0x31C
    // total size: 0x320 (800)

};
