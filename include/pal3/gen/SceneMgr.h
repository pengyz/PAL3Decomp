#pragma once
// SceneMgr: forward-declared in PDB (no real layout available)
// [GEN_BROKEN_LAYOUT] - using char array until binary analysis provides real layout

class SceneMgr {
public:
    union {
        char m_info[0x400000];
        char m_npc[0x400000];
    };
    void * Create(int gfxMgr, int cam, int a4);
    char RenderAll();
    char RenderUpdate();
};
