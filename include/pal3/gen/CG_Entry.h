#pragma once
// Auto-generated: CG_Entry

#include "LEVELPARAM.h"
#include "PAL3_FRAME.h"

class CG_Edit;
class CG_Scene;
class CG_UI;

class CG_Entry {
public:
    BYTE m_bActive; // +0x0
    BYTE m_bUIActive; // +0x1
    CG_Scene * m_pScene; // +0x4
    CG_UI * m_pUI; // +0x8
    CG_Edit * m_pEdit; // +0xC
    LEVELPARAM m_LEVELPARAM[5]; // +0x10
    PAL3_FRAME m_EntryFrame; // +0x38
    gbVec3D m_EntryRolePos; // +0x3C
    char m_EntryCityName[64]; // +0x48
    char m_EntryName[64]; // +0x88
    BYTE bOpt; // +0x0
    BYTE b_NoteJumpFree; // +0xC8
    // total size: 0xCC (204)

};
