class CCBAIWindow;

#include "Misc/Object.h"
#pragma once
// Auto-generated: GameObject
#include "pal3/ida_types.h"

class GameObject : public Object {
public:
    _BYTE _tail_000[4]; // +0x0
    // total size: 0x4 (4)

    virtual ~GameObject() {}

    virtual void * slot_1(); // slot1 0x0055434f
    virtual void UpdateFrame(float); // slot2 0x004af760

    // Scalar-wrapper: ctors for IDA (Cls)int casts (no init code)
    GameObject() {}

};
