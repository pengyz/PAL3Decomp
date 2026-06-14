#pragma once
// Auto-generated: ArcSceneMonster

class ArcSceneMonster {
public:
    BYTE id; // +0x0
    BYTE active; // +0x1
    char _gap_002[2]; // +0x2
    void * m_pMonsterData; // +0x4
    char _gap_008[156]; // +0x8
    int m_nMonsterHP; // +0xA4
    int m_nMonsterMP; // +0xA8
    char _gap_0AC[8]; // +0xAC
    int m_nMonsterLevel; // +0xB4
    char _gap_0B8[52]; // +0xB8
    int m_nMonsterExp; // +0xEC
    char _gap_0F0[64]; // +0xF0
    void * m_pSkillList; // +0x130
    char _gap_134[8]; // +0x134
    int m_nSkillCount; // +0x13C
    void * m_pDropItems; // +0x140
    int m_nDropRate; // +0x144
    char _gap_148[20]; // +0x148
    int m_nMonsterGold; // +0x15C
    // total size: 0x160 (352)

    int HitTest(unsigned int *pPoint); // 0x00441E30
    int * CreateInfoPanel(int nVal, int nVal2, int id, int *pnVal, int nVal3); // 0x00487F80
    int * CreateMonsterUI(int nVal, int nVal2, int id, int *pnVal, int nVal3); // 0x00491F20
    int * CreateStatusPanel(int nVal, int nVal2, int id, int *pnVal, int nVal3); // 0x00499CC0
    int CheckDistance(float fVal); // 0x0052DC40
    int ValidateRange(float fVal); // 0x0052DCA0
};
