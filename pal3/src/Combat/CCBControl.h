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
    char _gap_014[4]; // +0x14
    double m_DeltaTime; // +0x18
    int m_nController; // +0x20
    BYTE m_bActive; // +0x24
    BYTE m_bForceRelease; // +0x25
    char _gap_026[2]; // +0x26
    tagControlData m_InputData; // +0x28
    char _gap_02C[12]; // +0x2C
    tagCmdData m_CmdData; // +0x38
    char _gap_03C[40]; // +0x3C
    BYTE m_bShowRightPanel; // +0x64
    char _gap_065[3]; // +0x65
    int m_nCurThread; // +0x68
    int m_nThread; // +0x6C
    tagControlThread m_Thread[4]; // +0x70
    char _tail_080[240]; // +0x80
    // total size: 0x170 (368)

    int GetActiveAttackCount(); // 0x004DC240
    int GetState(); // 0x004DC560
    int GetControl(); // 0x004DC5B0
    int SetParam(int nVal, int nVal2); // 0x004DC5C0
};
