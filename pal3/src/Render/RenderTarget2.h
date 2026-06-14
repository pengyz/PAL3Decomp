#pragma once
// Auto-generated: RenderTarget2

class CEffAudio;
class CEffBase;
class CEffBink;
class CEffCallBack;
class codecvt_base;

class RenderTarget2 {
public:
    // vtable (125 methods, order matches binary layout)

    char * m_pVtable; // +0x0
    char * m_pSurface; // +0x4
    BYTE m_bActive; // +0x8
    char _gap_009[3]; // +0x9
    int m_SubObj; // +0xC
    int m_nFallbackMode; // +0x10
    float m_fBlendParam; // +0x14
    char * m_pTargetArray; // +0x18
    int m_nCurTarget; // +0x1C
    int m_nCurPass; // +0x20
    float m_fTime; // +0x24
    int m_nMaxTargets; // +0x28
    int m_nMaxPasses; // +0x2C
    int m_szPrefix; // +0x30
    float m_fSpeed; // +0x34
    float m_fParam; // +0x38
    float m_fBlend; // +0x3C
    char _gap_040[24]; // +0x40
    int m_EffectSlots; // +0x58
    char _gap_05C[12]; // +0x5C
    float _todo_068; // +0x68
    float _todo_06C; // +0x6C
    int _todo_70; // +0x70
    float _todo_074; // +0x74
    int _todo_078; // +0x78
    float _todo_07C; // +0x7C
    float m_fSoundTimeout; // +0x80
    int m_nSoundState; // +0x84
    int m_nSoundParam; // +0x88
    float m_fSoundVol; // +0x8C
    float m_fSoundPan; // +0x90
    int m_pTargetObj; // +0x94
    char _gap_098[8]; // +0x98
    int m_nFlags0; // +0xA0
    int m_nFlags1; // +0xA4
    int m_nTargetId; // +0xA8
    float m_pfnBegin; // +0xAC
    int m_szFmtBuf; // +0xB0
    float m_fTargetScale; // +0xB4
    float m_fTargetPosX; // +0xB8
    float m_fTargetPosY; // +0xBC
    float m_fTargetPosZ; // +0xC0
    char _gap_0C4[4]; // +0xC4
    int m_nTargetSize; // +0xC8
    char _gap_0CC[24]; // +0xCC
    int m_pfnStageSetup; // +0xE4
    char _gap_0E8[28]; // +0xE8
    int m_pfnStageGeometry; // +0x104
    char _gap_108[4]; // +0x108
    int m_pfnStageProcess; // +0x10C
    int m_nTaskState; // +0x110
    int m_pfnStagePostFx; // +0x114
    char _gap_118[44]; // +0x118
    int m_pfnStageOutput; // +0x144
    int m_pfnStageComposite; // +0x148
    char _gap_14C[24]; // +0x14C
    int m_pfnUpdatePost; // +0x164
    char _gap_168[20]; // +0x168
    BYTE m_bFlag; // +0x17C
    char _gap_17D[3]; // +0x17D
    float _todo_180; // +0x180
    float _todo_184; // +0x184
    char _gap_188[8]; // +0x188
    int m_pfnStagePresent; // +0x190
    char _gap_194[12]; // +0x194
    int m_pfnStageCleanup; // +0x1A0
    char _gap_1A4[104]; // +0x1A4
    int m_nTargetType; // +0x20C
    char _gap_210[1120]; // +0x210
    int m_nSoundChannels; // +0x670
    char _gap_674[8]; // +0x674
    int m_nSampleRate; // +0x67C
    char _gap_680[52]; // +0x680
    int m_nBufferSamples; // +0x6B4
    char _gap_6B8[92]; // +0x6B8
    int m_nRenderFlags; // +0x714
    int m_pRenderData; // +0x718
    char _gap_71C[460]; // +0x71C
    int m_nClearFlags; // +0x8E8
    int m_nClearColor; // +0x8EC
    char _gap_8F0[60]; // +0x8F0
    int m_vTargetPos; // +0x92C
    char _tail_930[1940]; // +0x930
    // total size: 0x10C4 (4292)

    virtual ~RenderTarget2() {}

    virtual void UpdateFrame(float a2); // 0x004C1550
    virtual int AdjustThisCall(int (__thiscall *a2)(char *, int), int a3, int a4); // 0x004C2850
    virtual char * vfunc_2(char a2); // 0x004C1560
    virtual int CalcDeltaTime(float fTime); // 0x004C2600
    virtual void FatalExit(); // 0x0055434F
    virtual RenderTarget2 * BeginRenderPass(void *Block, char pData); // 0x004C1490
    virtual char StubReturn0(int nVal); // 0x004C0600
    void NullCallback(); // 0x00401800
    void UpdateInternalAdj(float a2); // 0x004C2030
    virtual char * sub_004C2040(char a2); // 0x004C2040
    virtual char * DestroyEffBase(char a2); // 0x004C1640
    virtual char AllocTargets(int nVal); // 0x004C2170
    virtual void UpdateInternal(float fVal); // 0x004C29A0
    virtual CEffAudio ** CreateEffAudio(); // 0x004C15B0
    virtual void LoadResourcesByIndex(float *pfVal); // 0x004C1700
    virtual void CreateSoundTarget(int *p_DWORD); // 0x004C18D0
    virtual int * GetEffAudioTemplate(int nType); // 0x004C1DD0
    virtual RenderTarget2 * DestroyEffAudio(void *Block, char pData); // 0x004C1F70
    virtual char * sub_004C27C0(char a2); // 0x004C27C0
    virtual char * DestroyEffBink(char a2); // 0x004C20B0
    virtual CEffBink ** CreateEffBink(); // 0x004C2090
    virtual void CreateVideoTarget(int *p_DWORD); // 0x004C2280
    virtual int * GetTargetAddress(int nVal); // 0x004C25C0
    virtual RenderTarget2 * BeginNextPass(void *Block, char pData); // 0x004C2700
    virtual char * sub_004C3400(char a2); // 0x004C3400
    virtual char * BeginMultiPass(char a2); // 0x004C2870
    virtual int InitTargetPos(float *pfVal, float fVal, float fVal2, float fVal3); // 0x004C2930
    virtual void ** CreateDeactivated(); // 0x004C2820
    virtual char do_always_noconv(); // 0x004C2840
    virtual void RenderFromParams(float *pfVal); // 0x004C2BA0
    virtual void CreateEffectTarget(int *p_DWORD); // 0x004C2D00
    virtual int * GetCallbackTable(int nVal); // 0x004C3160
    virtual void UpdatePost(float fVal); // 0x004C3570
    virtual CEffCallBack ** CreateEffCallBack(); // 0x004C3490
    virtual void CreateCameraTarget(int *p_DWORD); // 0x004C3770
    virtual int * GetTargetByType(int nVal); // 0x004C3A90
    virtual RenderTarget2 * AdvancePass(void *Block, char pData); // 0x004C3BB0
    int Init(); // 0x004BF780
    void * Begin(); // 0x004BFD70
    void Resolve(); // 0x004BFDD0
    void Update(float fVal); // 0x004C0200
    CEffBase ** ClearTarget(); // 0x004C04C0
    int ExecutePasses(); // 0x004C0560
    int SceneRoleCallback(int nParam); // 0x004C0C10
    int RenderScene(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004C13B0
    CEffAudio ** Reset(); // 0x004C1570
    int DestroyEffBase(); // 0x004C1660
    int ProcessSoundPass(int nVal); // 0x004C1B00
    int RenderOverlay(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004C1E90
    CEffBink ** ResetSurface(); // 0x004C2050
    int DestroyEffBink(); // 0x004C20D0
    int ProcessVideoPass(int nVal); // 0x004C24B0
    void RenderEffect(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004C2620
    void ** Deactivate(); // 0x004C27D0
    int BeginMultiPass(); // 0x004C2890
    int RenderPostProcess(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004C3260
    CEffCallBack ** ResetTargetSlot(); // 0x004C3450
    int DestroyEffCallBack(); // 0x004C34D0
    int ProcessCameraPass(int nVal); // 0x004C39A0
    int RenderFinal(int nVal, int nVal2, int nVal3, int *p_DWORD, int nVal4, int nVal5); // 0x004C3AD0
    virtual void sub_4C3C70(float a2); // 0x004C3C70
    virtual char * _sdtor_35(char a2); // 0x004C3C80
    virtual void sub_4C5800(float a2); // 0x004C5800
    int AddCallbackEffect(RenderTarget2 *pTarget, int nVal, RenderTarget2 *pParam); // 0x004CEEC0
    int AddGenericEffect(RenderTarget2 *pTarget, int nVal, RenderTarget2 *pParam); // 0x004CF340
    int AddBinkEffect(RenderTarget2 *pTarget, int nVal, RenderTarget2 *pParam); // 0x004CFA00
    int CameraInterpCallback(int nVal); // 0x004D05E0
};
