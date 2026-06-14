#pragma once
// Auto-generated: CG_Entry

#include "LEVELPARAM.h"
#include "PAL3_FRAME.h"
#include "gbengine/gbengine_types.h"

class CG_Edit;
class CG_Scene;
class CG_UI;

class CG_Entry {
public:
    BYTE bOpt; // +0x0
    BYTE m_bUIActive; // +0x1
    char _gap_002[2]; // +0x2
    CG_Scene * m_pScene; // +0x4
    CG_UI * m_pUI; // +0x8
    CG_Edit * m_pEdit; // +0xC
    LEVELPARAM m_LEVELPARAM[5]; // +0x10
    char _gap_024[20]; // +0x24
    PAL3_FRAME m_EntryFrame; // +0x38
    gbVec3D m_EntryRolePos; // +0x3C
    char _gap_040[8]; // +0x40
    char m_EntryCityName[64]; // +0x48
    char m_EntryName[64]; // +0x88
    BYTE b_NoteJumpFree; // +0xC8
    char _tail_0C9[3]; // +0xC9
    // total size: 0xCC (204)

};
