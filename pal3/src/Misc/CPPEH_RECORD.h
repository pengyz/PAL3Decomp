#pragma once
// Auto-generated: CPPEH_RECORD

#include "_EH3_EXCEPTION_REGISTRATION.h"

class EXCEPTION_POINTERS;

class CPPEH_RECORD {
public:
    UINT old_esp; // +0x0
    EXCEPTION_POINTERS * exc_ptr; // +0x4
    _EH3_EXCEPTION_REGISTRATION registration; // +0x8
    char _tail_00C[12]; // +0xC
    // total size: 0x18 (24)

};
