#pragma once
// Auto-generated: CEffQuake

#include "CEffObj.h"

class CEffQuake : public CEffObj, public CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuake::*)(unsigned long)> {
public:
    static _DWORD * Destroy(); // 0x004D32C0
    int Update(); // 0x004D3300
};
