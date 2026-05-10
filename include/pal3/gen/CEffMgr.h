#pragma once
// Auto-generated: CEffMgr

#include "tagEffClass.h"
#include "tagEffGroup.h"
#include "tagEffObj.h"
#include "tagEffObjType.h"

class CCBSystem;

class CEffMgr {
public:
    gbGfxManager * m_pDisplay; // +0x0
    CCBSystem * m_pCBSystem; // +0x4
    gbRenderEffect * m_pAdditiveBlendNoZ; // +0x8
    gbRenderEffect * m_pAlphaBlendNoZ; // +0xC
    gbRenderEffect * m_pAdditiveBlend; // +0x10
    gbRenderEffect * m_pAlphaBlend; // +0x14
    gbCamera * m_pCam; // +0x18
    tagEffClass m_EffClass[32]; // +0x1C
    tagEffObjType m_EffObjType[2048]; // +0x0
    tagEffGroup m_EffGroup[1024]; // +0x0
    tagEffObj m_EffTable[2048]; // +0x91C
    int m_nEff; // +0xA91C
    float m_fCurTime; // +0xA920
    float m_fDeltaTime; // +0xA924
    float m_fTimer; // +0xA928
    float m_fTimeScale; // +0xA92C
    // total size: 0xA930 (43312)

    int Init(int a2, int a3, int a4, int a5, int a6); // 0x004CE340
    char Render(int a2); // 0x004CE580
    static int SetTimeScale(int a1); // 0x004CE5F0
    static char CreateEff(int a1); // 0x004CE690
    int RunEffGroup(const char *a2, int a3, const char *a4); // 0x004CEDA0
    int IsAllEffGroupStop(const char *a2, int a3, const char *a4); // 0x004CF100
    int CopyObjInGroup(const char *a2, int a3, const char *a4); // 0x004CF7C0
    _DWORD * Reset(); // 0x004D58A0
};
