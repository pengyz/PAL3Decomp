#pragma once
// SceneMgr: forward-declared in PDB (no real layout available)
// Code accesses g_SceneMgr.m_info[N] with N up to ~54112
// [GEN_BROKEN_LAYOUT] - using char array until binary analysis provides real layout

class SceneMgr {
public:
    char m_info[0x400000]; // ~4MB (SceneMgr is very large, contains Scene[3])
};
