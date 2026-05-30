#pragma once
// Template override: CTaskTpl<T, Callback>
// Auto-generated from PDB: CTaskTpl<tagEffTaskParam, unsigned long (__thiscall CEffAction::*)(unsigned long)>
// Size: 0x24 (36)

template<typename T, typename Callback>
class MainTask;

template<typename T, typename Callback>
class CTaskTpl {
public:
    float m_fCurTime; // +0x4
    float m_fDeltaTime; // +0x8
    MainTask<T, Callback> * m_pTask; // +0xC
    int m_nCurTask; // +0x10
    int m_nCurSubTask; // +0x14
    int m_nTask; // +0x18
    int m_nMaxTask; // +0x1C
    int m_nMaxSubTask; // +0x20
    // total size: 0x24 (36)
};
