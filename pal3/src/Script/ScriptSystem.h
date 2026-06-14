#pragma once
// Auto-generated: ScriptSystem

#include "gbengine/gbengine_internal.h"

class RoleSystem;

class ScriptSystem {
public:
    int m_nSlotID; // +0x0
    float m_vPos_x; // +0x4
    float m_vPos_y; // +0x8
    float m_vPos_z; // +0xC
    char _gap_010[4]; // +0x10
    float _todo_14; // +0x14
    float _todo_18; // +0x18
    int _todo_1C; // +0x1C
    int _todo_20; // +0x20
    int _todo_24; // +0x24
    int _todo_28; // +0x28
    char _gap_02C[60]; // +0x2C
    char m_szFmtBuf[40]; // +0x68
    int m_nMoveState; // +0x90
    float m_vRot_x; // +0x94
    float m_vRot_y; // +0x98
    float m_vRot_z; // +0x9C
    float m_vDir_x; // +0xA0
    float m_vDir_y; // +0xA4
    float m_vDir_z; // +0xA8
    char _gap_0AC[4]; // +0xAC
    int _todo_0B0; // +0xB0
    char _gap_0B4[20]; // +0xB4
    int _todo_0C8; // +0xC8
    char _gap_0CC[4]; // +0xCC
    int _todo_0D0; // +0xD0
    char _gap_0D4[56]; // +0xD4
    int _todo_10C; // +0x10C
    char _gap_110[176]; // +0x110
    int _todo_1C0; // +0x1C0
    char _gap_1C4[176]; // +0x1C4
    int m_nActionID; // +0x274
    int m_bActive; // +0x278
    int _todo_27C; // +0x27C
    char _gap_280[40]; // +0x280
    int m_Object3D; // +0x2A8
    char _gap_2AC[193]; // +0x2AC
    BYTE _todo_36D; // +0x36D
    char _gap_36E[22]; // +0x36E
    int m_pScriptEvent; // +0x384
    int m_nEventParam; // +0x388
    char _gap_38C[1]; // +0x38C
    BYTE m_bOpcodeFlag; // +0x38D
    BYTE m_bExecFlag; // +0x38E
    BYTE m_bBlockFlag; // +0x38F
    char _gap_390[172]; // +0x390
    int _todo_43C; // +0x43C
    char _gap_440[176]; // +0x440
    int m_nActionState; // +0x4F0
    int m_nMoveMode; // +0x4F4
    char _gap_4F8[12]; // +0x4F8
    int m_nSceneState; // +0x504
    char _gap_508[8]; // +0x508
    float m_vSavePos1_x; // +0x510
    float m_vSavePos1_y; // +0x514
    float m_vSavePos1_z; // +0x518
    float m_vSrcPos_x; // +0x51C
    float m_vSrcPos_y; // +0x520
    float m_vSrcPos_z; // +0x524
    float m_vMoveDir_x; // +0x528
    float m_vMoveDir_y; // +0x52C
    float m_vMoveDir_z; // +0x530
    char _gap_534[12]; // +0x534
    float m_vTargetPos; // +0x540
    float m_fObjects; // +0x544
    float m_fTargetDir; // +0x548
    char _gap_54C[32]; // +0x54C
    int _todo_56C; // +0x56C
    char _gap_570[76]; // +0x570
    int _todo_5BC; // +0x5BC
    int _todo_5C0; // +0x5C0
    int _todo_5C4; // +0x5C4
    int _todo_5C8; // +0x5C8
    char _gap_5CC[7204]; // +0x5CC
    float m_nSaveRot_x; // +0x21F0
    float m_nSaveRot_y; // +0x21F4
    float m_nSaveRot_z; // +0x21F8
    int m_nSaveDir; // +0x21FC
    // total size: 0x2200 (8704)

    void Render(gbMatrixStack *pMatrixStack); // 0x0040C630
    int Cleanup(); // 0x0040C790
    void Destroy(); // 0x0040C960
    static RoleSystem * GetMainRoleSystem(unsigned __int16 pData); // 0x0040CB80
    static int GetScriptContext(unsigned __int16 pData, int nVal); // 0x0040CBB0
    static int PassThrough(unsigned __int16 pData, int nVal, int nVal2); // 0x0040CBD0
    static int CheckEventType(unsigned __int16 pData, int nVal); // 0x0040CC00
    static int ClearTimerSlot(int nVal); // 0x0040CC60
    static int RunWithDelay(float delay, int nVal, int nVal2); // 0x004101F0
    int RunEvent(int eventId, int nVal); // 0x00410470
    static int UpdateTimers(float dt); // 0x00411F60
    void UpdatePositions(); // 0x00419090
    int SmoothTrackTarget(float fDeltaTime, float fMaxAccel, float fVal3, float fVal4); // 0x00419200
    static int UpdateObjects(float dt); // 0x004194C0
    void Init(); // 0x0041EFA0
    char ProcessScriptEvent(int nVal, int nVal2, int nParam); // 0x004890A0
};
