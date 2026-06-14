#pragma once
// Auto-generated: ThrowInfo

#include "PMFN.h"

class CatchableTypeArray;

class ThrowInfo {
public:
    UINT attributes; // +0x0
    PMFN pmfnUnwind; // +0x4
    char _gap_008[4]; // +0x8
    CatchableTypeArray * pCatchableTypeArray; // +0xC
    // total size: 0x10 (16)

};
