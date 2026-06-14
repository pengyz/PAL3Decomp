#pragma once
// Auto-generated: FightSkill

class FightSkill {
public:
    UINT id; // +0x0
    BYTE type; // +0x4
    char _gap_005[3]; // +0x5
    int att[5]; // +0x8
    char name[32]; // +0x1C
    char desc[512]; // +0x3C
    _BYTE user[5]; // +0x23C
    BYTE fanwei; // +0x241
    BYTE special; // +0x242
    _BYTE rvtype[12]; // +0x243
    char _gap_24F[1]; // +0x24F
    short rolevalue[12]; // +0x250
    BYTE succ; // +0x268
    char _gap_269[1]; // +0x269
    short fs[31]; // +0x26A
    int consumervtype[2]; // +0x2A8
    int consumetype[3]; // +0x2B0
    BYTE tutype; // +0x2BC
    char _gap_2BD[3]; // +0x2BD
    int tusuval; // +0x2C0
    BYTE lv; // +0x2C4
    _BYTE lvup[4]; // +0x2C5
    BYTE rolelv; // +0x2C9
    BYTE magiclv; // +0x2CA
    char _gap_2CB[1]; // +0x2CB
    UINT nextid; // +0x2CC
    BYTE isuseall; // +0x2D0
    char _gap_2D1[3]; // +0x2D1
    UINT hecheng[3]; // +0x2D4
    UINT heskill[3]; // +0x2E0
    _BYTE helv[3]; // +0x2EC
    _BYTE helvself[3]; // +0x2EF
    _BYTE manlv[3]; // +0x2F2
    BYTE heji; // +0x2F5
    char _tail_2F6[2]; // +0x2F6
    // total size: 0x2F8 (760)

};
