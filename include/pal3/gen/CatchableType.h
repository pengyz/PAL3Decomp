#pragma once
// Auto-generated: CatchableType

#include "PMD.h"

class PMFN;
class TypeDescriptor;

class CatchableType {
public:
    UINT properties; // +0x0
    TypeDescriptor * pType; // +0x4
    PMD thisDisplacement; // +0x8
    int sizeOrOffset; // +0x14
    PMFN copyFunction; // +0x18
    // total size: 0x1C (28)

};
