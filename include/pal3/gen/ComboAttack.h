#pragma once
// Auto-generated: ComboAttack

#include "FightState.h"

class ComboAttack {
public:
    char name[32]; // +0x0
    DWORD id; // +0x20
    DWORD man[4]; // +0x24
    BYTE pos[4]; // +0x34
    DWORD skill; // +0x38
    BYTE WeaponType[4]; // +0x3C
    BYTE Range; // +0x40
    FightState state[3]; // +0x44
    char Remark[512]; // +0x50
    BYTE fanwei; // +0x250
    BYTE rvtype[12]; // +0x251
    short rolevalue[12]; // +0x25E
    int hj_EffectRate; // +0x278
    // total size: 0x27C (636)

};
