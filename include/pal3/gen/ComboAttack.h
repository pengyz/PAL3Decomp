#pragma once
// Auto-generated: ComboAttack

#include "FightState.h"

class ComboAttack {
public:
    char name[32]; // +0x0
    unsigned long id; // +0x20
    unsigned long man[4]; // +0x24
    unsigned char pos[4]; // +0x34
    unsigned long skill; // +0x38
    unsigned char WeaponType[4]; // +0x3C
    unsigned char Range; // +0x40
    FightState state[3]; // +0x44
    char Remark[512]; // +0x50
    unsigned char fanwei; // +0x250
    unsigned char rvtype[12]; // +0x251
    short rolevalue[12]; // +0x25E
    int hj_EffectRate; // +0x278
    // total size: 0x27C (636)

};
