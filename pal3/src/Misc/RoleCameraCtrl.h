#include "PalScriptWaitObj.h"
#pragma once
// Auto-generated: RoleCameraCtrl

#include "RCC_TYPE.h"
#include "gbengine/gbengine_types.h"

class RoleCameraCtrl : public PalScriptWaitObj {
public:
    char _gap_000[8]; // +0x0
    void * m_pVtable; // +0x8
    RCC_TYPE m_type; // +0xC
    float m_time; // +0x10
    float m_passtime; // +0x14
    float m_itype; // +0x18
    float m_targetdist; // +0x1C
    float m_startdist; // +0x20
    float m_targetyaw; // +0x24
    float m_startyaw; // +0x28
    float m_targetpitch; // +0x2C
    float m_startpitch; // +0x30
    gbVec3D m_targetfrom; // +0x34
    char _gap_038[8]; // +0x38
    gbVec3D m_startfrom; // +0x40
    char _tail_044[8]; // +0x44
    // total size: 0x4C (76)

    virtual void ShowWindow(); // 0x00450D00
    virtual BOOL UpdatePosition(int nVal, int nVal2); // 0x00450C90
    virtual RoleCameraCtrl * _sdtor_26(RoleCameraCtrl *Block, char a2); // 0x00450AB0
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x00450C60
    void SetName(const char *pszName); // 0x00445860
    int SetTargetDistance(int nVal); // 0x00445910
    ~RoleCameraCtrl(); // 0x00450A25
    RoleCameraCtrl * InitFrameUI(); // 0x00450A60
    void InitBaseWidget(); // 0x00450AD0
    int InitViewSlots(); // 0x0051BB50
    int SetViewPosition(int nVal, int nVal2, int nVal3, char pData); // 0x0052DFF0
    int ComputeViewVector(int nVal, int nVal2, int nVal3); // 0x0052E080
};
