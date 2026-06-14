#pragma once
// Auto-generated: ScriptVM

#include "gbengine/gbVFileSystem.h"

class ScriptVM {
public:
    char _gap_000[4]; // +0x0
    int m_bufHead; // +0x4
    int m_bufTail; // +0x8
    int m_bufCapacity; // +0xC
    int m_bufReadPtr; // +0x10
    int m_bufWritePtr; // +0x14
    char _gap_018[8]; // +0x18
    int * m_ptr_20; // +0x20
    char _gap_024[124]; // +0x24
    int _todo_0A0; // +0xA0
    int _todo_0A4; // +0xA4
    int _todo_0A8; // +0xA8
    char _gap_0AC[48]; // +0xAC
    int _todo_0DC; // +0xDC
    void * _todo_0E0; // +0xE0
    char _gap_0E4[16]; // +0xE4
    BYTE _todo_0F4; // +0xF4
    char _gap_0F5[11]; // +0xF5
    int m_nPauseState; // +0x100
    char _gap_104[536]; // +0x104
    void * m_pCmdList; // +0x31C
    char _gap_320[28]; // +0x320
    int m_nPathMode; // +0x33C
    float m_fPathStartX; // +0x340
    float m_fPathStartY; // +0x344
    float m_fPathStartZ; // +0x348
    int m_nPathParam; // +0x34C
    float m_fPathEndX; // +0x350
    float m_fPathEndY; // +0x354
    char * m_ptr_358; // +0x358
    char * m_pPathCurrent; // +0x35C
    char * m_pPathKeys; // +0x360
    int m_nPathKeyCount; // +0x364
    int m_nPathStep; // +0x368
    // total size: 0x36C (876)

    void ProcessFrame(); // 0x00423880
    BOOL IsRunning(); // 0x0042C1A0
    struct gbVFileSystem * OpenSceneScript(); // 0x0042C730
    char UpdatePauseState(); // 0x0042C810
    int ExecuteOpcode(void *pData, unsigned __int8 nType, int nCount); // 0x0042C950
    int CallFunction(unsigned __int8 nFuncID, int nArgCount); // 0x0042CD90
    int SetRolePosition(unsigned __int8 pData); // 0x0042D4B0
    int GetRolePosition(unsigned __int8 pData); // 0x0042D670
    char * GetString(); // 0x0042FB60
    static int GetObjectByID(int nObjID); // 0x004366C0
};
