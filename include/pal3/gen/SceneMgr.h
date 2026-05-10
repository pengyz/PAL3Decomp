#pragma once
// SceneMgr: forward-declared in PDB (no real layout available)
// Code accesses g_SceneMgr.m_info[N] with N up to ~54112
// [GEN_BROKEN_LAYOUT] - using char array until binary analysis provides real layout

class SceneMgr {
public:
    union {
        char m_info[0x400000]; // byte access: g_SceneMgr.m_info[N]
        char m_npc[0x400000];  // also accessed as g_SceneMgr.m_npc[N]
    };
};
