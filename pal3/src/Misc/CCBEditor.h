#pragma once
// Auto-generated: CCBEditor

#include "tagNewItem.h"

class CCBRoleState;

class CCBEditor {
public:
    CCBEditor * m_fpThis; // +0x0
    CCBRoleState * m_pRoleState; // +0x4
    tagNewItem m_NewItem[500]; // +0x8
    char _gap_7D8[6000]; // +0x7D8
    int m_dwSelectFighter[11]; // +0x1F48
    int m_nCurCCTList; // +0x1F74
    int m_nCurCCT; // +0x1F78
    int m_nCurEffClass; // +0x1F7C
    int m_nCurEffObjType; // +0x1F80
    int m_nCurEffGroup; // +0x1F84
    int m_nCurEffObjInGroup; // +0x1F88
    int m_nCurEffObjTask; // +0x1F8C
    UINT m_dwTrickID[384]; // +0x1F90
    int m_nCurSelectedEffGroup; // +0x2590
    int m_nCurSelectedTrick; // +0x2594
    // total size: 0x2598 (9624)

    int UpdateItemScript(CHAR *lpString2, int nVal, int nVal2, int nVal3); // 0x0044B630
    int InvokeItemMethod(); // 0x0044B690
};
