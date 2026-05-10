#pragma once
// CTaskTpl: base class for effect task management
// Original is template CTaskTpl<TParam, TFunc>, simplified for compilation.
// Layout from DIA/PDB: 36 bytes (0x24)

struct tagEffTaskParam;

class CTaskTpl {
public:
    unsigned long m_dwTaskIDHolder; // +0x0
    float m_fCurTime;              // +0x4
    float m_fDeltaTime;            // +0x8
    tagEffTaskParam *m_pTask;      // +0xC
    int m_nCurTask;                // +0x10
    int m_nCurSubTask;             // +0x14
    int m_nTask;                   // +0x18
    int m_nMaxTask;                // +0x1C
    int m_nMaxSubTask;             // +0x20
    // total size: 0x24 (36)
};
