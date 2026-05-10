#pragma once
// Auto-generated: TaskMgr (template class, simplified for PAL3 compilation)
// Original: TaskMgr<SceneObjParam, unsigned long (__thiscall SceneObj::*)(unsigned long)>
// Size: 0x24 (36 bytes) from PAL3A PDB

class TaskMgr {
public:
    float m_fCurTime; // +0x4
    float m_fDeltaTime; // +0x8
    void * m_pTask; // +0xC (MainTask*)
    int m_nCurTask; // +0x10
    int m_nCurSubTask; // +0x14
    int m_nTask; // +0x18
    int m_nMaxTask; // +0x1C
    int m_nMaxSubTask; // +0x20
    // total size: 0x24 (36)
};
