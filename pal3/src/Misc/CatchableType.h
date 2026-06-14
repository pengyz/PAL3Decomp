#pragma once
// Auto-generated: CatchableType

#include "PMD.h"
#include "PMFN.h"

class TypeDescriptor;

class CatchableType {
public:
    UINT properties; // +0x0
    TypeDescriptor * pType; // +0x4
    PMD thisDisplacement; // +0x8
    char _gap_00C[8]; // +0xC
    int sizeOrOffset; // +0x14
    PMFN copyFunction; // +0x18
    // total size: 0x1C (28)

};
