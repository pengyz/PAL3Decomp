#pragma once
// SceneMgr: forward-declared in PDB (no real layout available)
// [GEN_BROKEN_LAYOUT] Needs binary analysis to determine PAL3 layout
//
// Known members from code access patterns:
//   .m_info[N] - byte array access (898 refs)
//   .m_npc[N] - NPC data access (70+ elements)
//   .s_scene[N] - Scene array (from IDA)
//   .s_curscene - current scene type
//
// TODO: determine offsets from PAL3 binary (stride analysis, memset, ctor)

class SceneMgr {
public:
    char m_info[0x400000]; // placeholder for byte-offset access

    void * Create(int gfxMgr, int cam, int a4);
    char RenderAll();
    char RenderUpdate();
};
