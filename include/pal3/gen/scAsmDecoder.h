#pragma once
// Auto-generated: scAsmDecoder

#include "PtrArray.h"
#include "scVarStack.h"

class scGlobalUserVar;
class scScriptInstance;

class scAsmDecoder {
public:
    scScriptInstance * m_pRunningInst; // +0x0
    int m_globalvarnum; // +0x0
    scGlobalUserVar * m_globalvar; // +0x0
    PtrArray m_instptrarray; // +0x0
    scVarStack m_stack; // +0x0
    // total size: 0x4 (4)

};
