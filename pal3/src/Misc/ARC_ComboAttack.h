#pragma once
// Auto-generated: ARC_ComboAttack

#include "FightState.h"

class ARC_ComboAttack {
public:
    char name[32]; // +0x0
    UINT id; // +0x20
    UINT man[4]; // +0x24
    _BYTE pos[4]; // +0x34
    UINT skill; // +0x38
    _BYTE WeaponType[4]; // +0x3C
    BYTE Range; // +0x40
    char _gap_041[3]; // +0x41
    FightState state[3]; // +0x44
    char Remark[512]; // +0x50
    BYTE fanwei; // +0x250
    _BYTE rvtype[12]; // +0x251
    char _gap_25D[1]; // +0x25D
    short rolevalue[12]; // +0x25E
    char _tail_276[2]; // +0x276
    // total size: 0x278 (632)

};
