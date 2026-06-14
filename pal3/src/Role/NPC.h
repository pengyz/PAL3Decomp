#pragma once
// Auto-generated: NPC

#include "UIWnd.h"

class NPC {
public:
    char _gap_000[4]; // +0x0
    char * m_pBuffer; // +0x4
    int m_nBufStart; // +0x8
    int m_nBufEnd; // +0xC
    char _gap_010[20]; // +0x10
    int _todo_24; // +0x24
    char _gap_028[8]; // +0x28
    int _todo_030; // +0x30
    char _gap_034[4]; // +0x34
    int m_pConditionA; // +0x38
    void * m_pConditionB; // +0x3C
    char _gap_040[4]; // +0x40
    UIWnd m_wndBase; // +0x44
    char _gap_048[152]; // +0x48
    int _todo_0E0; // +0xE0
    char _gap_0E4[64]; // +0xE4
    UIWnd * m_wndHPBar; // +0x124
    char _gap_128[16]; // +0x128
    UIWnd m_WndContainer; // +0x138
    char _gap_13C[220]; // +0x13C
    int m_wndNameLabel; // +0x218
    char _gap_21C[16]; // +0x21C
    UIWnd m_AnimWndA; // +0x22C
    char _gap_230[128]; // +0x230
    NPC * m_wndDialog; // +0x2B0
    char _gap_2B4[16]; // +0x2B4
    UIWnd m_AnimWndB; // +0x2C4
    char _gap_2C8[128]; // +0x2C8
    NPC * m_wndTooltip; // +0x348
    char _gap_34C[16]; // +0x34C
    UIWnd m_AnimWndC; // +0x35C
    char _gap_360[280]; // +0x360
    float m_fAnimTimer; // +0x478
    int m_bAnimActive; // +0x47C
    // total size: 0x480 (1152)

    static unsigned int Create(int index); // 0x0040EB90
    static void * Init(int index); // 0x0040EC20
    int FreeBuffer(); // 0x0040EE00
    char ShiftBufferData(int nVal); // 0x0040EE30
    bool HasBufferData(int nVal); // 0x0040F000
    int GetBufferCount(); // 0x0040F030
    int GetBufferAt(int nIndex); // 0x0040F050
    static int SetRoleMode(int nVal); // 0x0040F060
    static int InitAll(int nMaxCount); // 0x0040F620
    int ReadBufferData(FILE *Stream); // 0x0040F6F0
    int LoadBufferFromStream(FILE *fp); // 0x0040F760
    size_t SaveToStream(FILE *Stream); // 0x0040F950
    size_t LoadFromStream(FILE *Stream); // 0x0040F9E0
    void SetSceneFlag(); // 0x00410580
    int CreateChild(); // 0x0043F560
    void UpdateAnim(); // 0x00446020
    int GetPropertyByIndex(unsigned int dwVal); // 0x00479100
    void DestroyAndRecreateUI(); // 0x00517A50
    char HandleAIMessage(int thisa, int nVal); // 0x00517AC0
    void ShowAIWindow(); // 0x00517BA0
    void ResetLineupWindow(); // 0x00517CF0
};
