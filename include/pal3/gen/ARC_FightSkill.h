#pragma once
// Auto-generated: ARC_FightSkill

class ARC_FightSkill {
public:
    DWORD id; // +0x0
    BYTE type; // +0x4
    int att[5]; // +0x8
    char name[32]; // +0x1C
    char desc[512]; // +0x3C
    BYTE user[5]; // +0x23C
    BYTE fanwei; // +0x241
    BYTE special; // +0x242
    BYTE rvtype[12]; // +0x243
    short rolevalue[12]; // +0x250
    BYTE succ; // +0x268
    short fs[31]; // +0x26A
    int consumervtype[2]; // +0x2A8
    int consumetype[3]; // +0x2B0
    BYTE tutype; // +0x2BC
    int tusuval; // +0x2C0
    BYTE lv; // +0x2C4
    BYTE lvup[4]; // +0x2C5
    BYTE rolelv; // +0x2C9
    BYTE magiclv; // +0x2CA
    DWORD nextid; // +0x2CC
    BYTE isuseall; // +0x2D0
    DWORD hecheng[3]; // +0x2D4
    DWORD heskill[3]; // +0x2E0
    BYTE helv[3]; // +0x2EC
    BYTE helvself[3]; // +0x2EF
    BYTE manlv[3]; // +0x2F2
    BYTE heji; // +0x2F5
    // total size: 0x2F8 (760)

};
