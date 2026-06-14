#pragma once
// Auto-generated: SceneMgrCamBlock

class PalScript;

class SceneMgrCamBlock {
public:
    char _gap_000[84]; // +0x0
    PalScript * m_pScriptArrayEnd; // +0x54
    PalScript * _todo_058; // +0x58
    PalScript * m_pUIScript; // +0x5C
    PalScript * m_pScriptArrayEndSub; // +0x60
    int m_nUnlockDataOffset; // +0x64
    int m_nUnlockDataLen; // +0x68
    int m_RoleUnlockData[100]; // +0x6C
    int m_nUnlockDataEndFlag; // +0x1FC
    int m_nUnlockDataCount; // +0x200
    int m_MonsterUnlockTable[60]; // +0x204
    int m_nMonsterUnlockEndFlag; // +0x2F4
    int m_nCurrentScene; // +0x2F8
    PalScript * m_pCameraScript; // +0x2FC
    // total size: 0x300 (768)

};
