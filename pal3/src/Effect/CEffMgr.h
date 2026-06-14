#pragma once
// Auto-generated: CEffMgr

#include "gbengine/gbCamera.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "tagEffClass.h"
#include "tagEffObj.h"

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
    float m_fEffParam; // +0x9C
    float m_fPosX; // +0xA0
    float m_fPosY; // +0xA4
    float m_fPosZ; // +0xA8
    float m_vecRotAxis; // +0xAC
    float _todo_0B0; // +0xB0
    float _todo_0B4; // +0xB4
    int _todo_0BC; // +0xB8
    float m_fScaleX; // +0xBC
    float m_fScaleY; // +0xC0
    float m_fScaleZ; // +0xC4
    char m_szEffectPath[48]; // +0xC8
    char m_szLogPath[216]; // +0xF8
    int _todo_1D8; // +0x1D0
    int _todo_2E4; // +0x1D4
    int _todo_364; // +0x1D8
    int m_nReset; // +0x1DC
    int _todo_404; // +0x1E0
    int _todo_408; // +0x1E4
    int m_pEffectArray; // +0x1E8
    tagEffObj m_EffTable[2048]; // +0x1EC
    char _gap_21EC[32768]; // +0x21EC
    int m_nTargetSlot; // +0xA1EC
    UINT roleIdx; // +0xA1F0
    char m_sz5D8C3C[29028]; // +0xA1F4
    int m_nEff; // +0x11358
    float m_fCurTime; // +0x1135C
    float m_fDeltaTime; // +0x11360
    float m_fTimer; // +0x11364
    float m_fTimeScale; // +0x11368
    // total size: 0x1136C (70508)

    void UpdateTimedTrigger(float fVal); // 0x004B7340
    int SetComponent(int nVal); // 0x004B73D0
    int SetEffectClass(int nVal, int nVal2, int nVal3); // 0x004B73F0
    int ProcessEffectPass(int nVal); // 0x004C2F30
    int UpdateParticlePositions(); // 0x004C5350
    int EmitParticles(); // 0x004C7E60
    int UpdateEffect(float fVal, int nVal); // 0x004CCEF0
    char SetEffectsTimeScale(int nVal); // 0x004CDC50
    int CreateEffect(int nVal, int nVal2, int nVal3, int nVal4, int nVal5); // 0x004CDCA0
    int InitEffClass(); // 0x004CDED0
    int FindEffSlot(int nVal); // 0x004CDFD0
    int FindEffByID(int nVal); // 0x004CE000
    CEffMgr(); // 0x004CE100
    void _CEffMgr(); // 0x004CE2A0
    bool Init(int nVal, int nVal2, int nVal3, int nVal4, int nVal5); // 0x004CE340
    void Render(int nVal); // 0x004CE580
    void SetTimeScale(float fScale); // 0x004CE5F0
    char CreateEff(const char *a2, unsigned int a3, float a4, float a5, int a6); // 0x004CE690
    char ReleaseCompletedEffects(); // 0x004CEA80
    int RunEffGroup(char *nIndex, float a3, char *a4, float a5, int a6); // 0x004CEDA0
    int CreateSParticleEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2); // 0x004CEFE0
    bool IsAllEffGroupStop(char *pszBuf, int nVal, char *pszBuf2); // 0x004CF100
    int CreateModelEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2); // 0x004CF220
    int CreateEffectType3(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2); // 0x004CF460
    int CreateEffectType4(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2); // 0x004CF6A0
    void CopyObjInGroup(char *nGroup, int nObj, char *nObjType); // 0x004CF7C0
    int CreateEffectType5(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2); // 0x004CF8E0
    int CreateShockEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2); // 0x004CFB20
    int UpdateKeyframe(int nVal); // 0x004D22F0
    int * Reset(); // 0x004D58A0
};
