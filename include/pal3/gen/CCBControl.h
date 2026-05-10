#pragma once
// Auto-generated: CCBControl

#include "tagCmdData.h"
#include "tagControlData.h"
#include "tagControlThread.h"

class CCBAttackSequen;
class CCBRoleState;
class CCBStage;
class CCBSystem;
class CCBUI;

class CCBControl {
public:
    CCBSystem * m_pCBSystem; // +0x0
    CCBAttackSequen * m_pAttackSequen; // +0x4
    CCBStage * m_pStage; // +0x8
    CCBRoleState * m_pRoleState; // +0xC
    CCBUI * m_pUI; // +0x10
    double m_DeltaTime; // +0x18
    int m_nController; // +0x20
    BYTE m_bActive; // +0x24
    BYTE m_bForceRelease; // +0x25
    tagControlData m_InputData; // +0x28
    tagCmdData m_CmdData; // +0x38
    BYTE m_bShowRightPanel; // +0x64
    int m_nCurThread; // +0x68
    int m_nThread; // +0x6C
    tagControlThread m_Thread[20]; // +0x70
    // total size: 0x570 (1392)

    int Update(); // 0x004DC240
};
