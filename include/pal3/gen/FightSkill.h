#pragma once
// Auto-generated: FightSkill

class FightSkill {
public:
    unsigned long id; // +0x0
    unsigned char type; // +0x4
    int att[5]; // +0x8
    char name[32]; // +0x1C
    char desc[512]; // +0x3C
    unsigned char user[5]; // +0x23C
    unsigned char fanwei; // +0x241
    unsigned char special; // +0x242
    unsigned char rvtype[12]; // +0x243
    short rolevalue[12]; // +0x250
    unsigned char succ; // +0x268
    short fs[31]; // +0x26A
    int consumervtype[2]; // +0x2A8
    int consumetype[3]; // +0x2B0
    unsigned char tutype; // +0x2BC
    int tusuval; // +0x2C0
    unsigned char lv; // +0x2C4
    unsigned char lvup[4]; // +0x2C5
    unsigned char rolelv; // +0x2C9
    unsigned char magiclv; // +0x2CA
    unsigned long nextid; // +0x2CC
    unsigned char isuseall; // +0x2D0
    unsigned long hecheng[3]; // +0x2D4
    unsigned long heskill[3]; // +0x2E0
    unsigned char helv[3]; // +0x2EC
    unsigned char helvself[3]; // +0x2EF
    unsigned char manlv[3]; // +0x2F2
    unsigned char heji; // +0x2F5
    // total size: 0x2F8 (760)

};
