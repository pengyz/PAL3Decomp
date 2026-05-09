#pragma once
// Auto-generated: FightItem

class FightItem {
public:
    unsigned long id; // +0x0
    char name[32]; // +0x4
    char ModelID[30]; // +0x24
    char ImageID[30]; // +0x42
    char desc[512]; // +0x60
    int price; // +0x260
    unsigned char type; // +0x264
    unsigned char weapontype; // +0x265
    unsigned char user[5]; // +0x266
    unsigned char att[5]; // +0x26B
    int gu; // +0x270
    unsigned char special; // +0x274
    unsigned char fanwei; // +0x275
    unsigned char space; // +0x276
    unsigned char rvtype[12]; // +0x277
    short rolevalue[12]; // +0x284
    unsigned char fstype[31]; // +0x29C
    short fightstate[31]; // +0x2BC
    int tosshurt; // +0x2FC
    int lian; // +0x300
    short saveqi; // +0x304
    short saveshen; // +0x306
    short addbaoji; // +0x308
    short addteji; // +0x30A
    int embracer; // +0x30C
    unsigned long compose_material; // +0x310
    int compose_type; // +0x314
    unsigned long compose_final; // +0x318
    unsigned long compose_intimacy; // +0x31C
    // total size: 0x320 (800)

};
