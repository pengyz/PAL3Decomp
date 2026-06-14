#pragma once
// Auto-generated: CScreenMode

#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIRoleDialog.h"
#include "UIScene.h"
#include "UIStatic.h"
#include "gbengine/gbAudio.h"
#include "gbengine/gbGfxManager.h"

class PtrArray;

class CScreenMode {
public:
    // vtable (7 methods, order matches binary layout)

    char * m_pEnumeration; // +0x0
    BYTE m_bRenderAlt; // +0x4
    char _gap_005[3]; // +0x5
    int m_nScreenFlags; // +0x8
    int m_nField0C; // +0xC
    float m_fFadeStart; // +0x10
    float m_fFadeTarget; // +0x14
    int m_nFadeState; // +0x18
    float m_fFadeAlpha; // +0x1C
    int m_nFadeCounter; // +0x20
    float m_fFadeSpeed; // +0x24
    float m_fCountdown; // +0x28
    float m_fFadeParam; // +0x2C
    float m_fFadeProgress; // +0x30
    int m_VolMod; // +0x34
    float m_fFadeMaxAlpha; // +0x38
    BYTE m_bFadeActive; // +0x3C
    char _gap_03D[3]; // +0x3D
    float m_fScreenTimer; // +0x40
    int m_nPosX; // +0x44
    int m_nPosY; // +0x48
    int m_nLayoutParam; // +0x4C
    int m_nUIState; // +0x50
    int m_nUIMode; // +0x54
    int m_nScreenWidth; // +0x58
    int m_nScreenHeight; // +0x5C
    int m_nProgressBase; // +0x60
    int m_nLayoutState; // +0x64
    int m_nLayoutOffX; // +0x68
    int m_nLayoutOffY; // +0x6C
    char _gap_070[1]; // +0x70
    BYTE m_bLoadFlag; // +0x71
    char _gap_072[6]; // +0x72
    int m_nProgressValA; // +0x78
    int m_nProgressValB; // +0x7C
    int m_nProgressPos; // +0x80
    int m_nProgress; // +0x84
    int m_nBarWidth; // +0x88
    int m_nBarHeight; // +0x8C
    int m_nBarPosX; // +0x90
    int m_nBarPosY; // +0x94
    int m_bCameraInit; // +0x98
    char _gap_09C[4]; // +0x9C
    float m_fVolume; // +0xA0
    float m_wndAssistA; // +0xA4
    int m_nAudioHandle; // +0xA8
    int m_pfnPlayVideo; // +0xAC
    int m_nAudioState; // +0xB0
    float m_fAudioVolume; // +0xB4
    int m_nAudioFileId; // +0xB8
    char _gap_0BC[4]; // +0xBC
    int m_nVideoState; // +0xC0
    float m_fSceneVolume; // +0xC4
    char _gap_0C8[4]; // +0xC8
    float m_fPan; // +0xCC
    float m_fProgressD; // +0xD0
    char m_szTooltip[8]; // +0xD4
    float m_fProgressRatio; // +0xDC
    float m_fProgressMax; // +0xE0
    float m_fProgressCur; // +0xE4
    float m_fProgress; // +0xE8
    float m_fProgressParam; // +0xEC
    float m_fProgressNorm; // +0xF0
    int m_nBarTotalSize; // +0xF4
    float m_fBarOffsetX; // +0xF8
    float m_fBarOffsetY; // +0xFC
    float m_fBarOffsetW; // +0x100
    float m_fAccum; // +0x104
    int m_nProgressTimer; // +0x108
    int m_nBarParam; // +0x10C
    int m_nArrayCapacity; // +0x110
    char * m_pArrayData; // +0x114
    UIStatic m_FrameB; // +0x118
    char _gap_11C[148]; // +0x11C
    UIStatic m_StaticArray; // +0x1B0
    char _gap_1B4[180]; // +0x1B4
    int m_nVolNode0; // +0x268
    int m_nVolNode1; // +0x26C
    int m_nVolNode2; // +0x270
    int m_nVolNode3; // +0x274
    int m_nVolNode4; // +0x278
    UIFrameWnd _embed_UIFrameWnd_816; // +0x27C
    char _gap_280[88]; // +0x280
    UIFrameWnd _embed_UIFrameWnd_968; // +0x2D8
    char _gap_2DC[76]; // +0x2DC
    gbAudioManager * m_pAudioMgr; // +0x328
    void * m_pSoundStream; // +0x32C
    UIStatic m_Static_816; // +0x330
    char _gap_334[424]; // +0x334
    UIScene m_nPageCounter; // +0x4DC
    char _gap_4E0[1012]; // +0x4E0
    UIButton m_BtnTooltipC; // +0x8D4
    char _gap_8D8[344]; // +0x8D8
    void * m_pGameUI; // +0xA30
    char _gap_A34[8]; // +0xA34
    UIScene m_ScenePanel; // +0xA3C
    char _gap_A40[340]; // +0xA40
    UIScene m_ScenePanelB; // +0xB94
    char _gap_B98[340]; // +0xB98
    UIScene m_ScenePanelC; // +0xCEC
    char _gap_CF0[348]; // +0xCF0
    int m_nAssistMode; // +0xE4C
    char _gap_E50[24]; // +0xE50
    int m_SceneBlock; // +0xE68
    char _gap_E6C[176]; // +0xE6C
    BYTE m_bActive; // +0xF1C
    char _gap_F1D[3]; // +0xF1D
    int m_nScreenActive; // +0xF20
    UIRoleDialog m_RoleDialog; // +0xF24
    char _tail_F28[1104]; // +0xF28
    // total size: 0x1378 (4984)

    virtual ~CScreenMode() {}

    virtual int ForwardMessage(int nVal, int nVal2); // 0x00524980
    virtual int OnRenderAlt(); // 0x005249A0
    static void ProcessGameMode(int nVal, int nVal2); // 0x0040EB10
    void SetTooltipText(); // 0x0043AFA0
    void SetProgress(float fProgress); // 0x0043C550
    void SetPosition(int nX, int nY); // 0x0043DC40
    void HideUIBars(int nVal, unsigned int dwVal); // 0x0044E8B0
    char GetMouseScroll(); // 0x00456280
    void PauseAllStreams(void (__thiscall ***thisa)(_DWORD, _DWORD), unsigned __int8 a2); // 0x00456E20
    void InitGameUI(); // 0x004593C0
    void InitEquipScreen(); // 0x0047BE20
    void GetPlayerAttByIndex(int nIndex); // 0x00493290
    int ResetProgressList(); // 0x00494250
    char GetMouseDelta(); // 0x004B30C0
    CScreenMode(); // 0x00523F30
    void _CScreenMode(); // 0x00524130
    int InitSceneAudio(int nVal); // 0x00527F50
    char InitPlayerData(); // 0x0052D230
    void InitCamera(struct gbGfxManager *pGfx); // 0x0052DF40
    void InitEndScreen(); // 0x0052ED30
    int CreateVolModNode(); // 0x00530440
    void FreeNPCBuffer(); // 0x00530660
    double LoadScreenScene(double result, float result_4); // 0x00533250
    int CloseBinkVideo(); // 0x0053C420
    int CreateDevice(int a, int b, int c, int d); // 0x0053C440
    int WaitBinkFrame(); // 0x0053C460
    int IsSceneReady(); // 0x0053C470
    int CheckFieldReady(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int nVal6); // 0x0053C530
    int PlayVideo(int nVal); // 0x0053C5A0
    int SetViewport(int x, int y); // 0x0053C6F0
    int GetWidth(); // 0x0053C710
    int GetHeight(); // 0x0053C720
    int InitDisplayState(); // 0x0053C8C0
    int SetState(int state); // 0x0053CDD0
    PtrArray * GetSoundList(); // 0x0053D150
    void SetAudioParam(); // 0x0053D1E0
    char IsAudioReady(); // 0x0053D2D0
    void CleanupSoundList(); // 0x0053DC50
    void SetMode(int mode); // 0x0053DD70
    void Restore(); // 0x0053DEF0
    static CScreenMode * GetInstance(); // 0x0053DF70
    static BOOL GetByteParam(int nVal, int nVal2); // 0x0053DF80
    int PlaySoundStream(const void *pData); // 0x0053DFB0
    void AudioSetPosition(const void *pData, int nVal); // 0x0053E2E0
    void AudioUpdate(); // 0x0053E490
    void PlaySoundIfEnabled(void *pSound, int nMode); // 0x0053E4E0
    int GetAudioManager(); // 0x0053E500
    void PlaySceneMusic(char *pszScene, const char *pszArea, int nVal); // 0x0053E510
    void PlayCombatMusic(char *pszSceneName); // 0x0053E680
    unsigned int StopAllAudio(); // 0x0053E720
    void PlayAmbientSound(char *pszName, gbAudioManager *pAudioMgr); // 0x0053E740
    void ApplyColorFilter(); // 0x0053E890
    void AudioStopAll(); // 0x0053E950
    unsigned int StopAll(); // 0x0053E970
    void AudioFadeOut(); // 0x0053EA60
    int IterateChildList(); // 0x0053EB50
    int AddSoundEntry(char *pszBuf, char *pszBuf2); // 0x0053EB90
    int GetSoundCount(); // 0x0053ED70
    void DestroyString(int *p_DWORD, int *p_DWORD2); // 0x0053EDA0
    static int _nearby_53edd0(int); // 0x0053EDD0
    void FreeSoundBuffer(void *Block, int nVal); // 0x0053EDE0
    int * ComparePointers(int *p_DWORD, int *p_DWORD2, int *p_DWORD3); // 0x0053EDF0
    void InitSceneObjects(int *p_DWORD, int nVal, int *p_DWORD2); // 0x0053EE30
    char UpdateRenderState(int *lpString); // 0x0053F220
    _DWORD * _nearby_53f4c0(_DWORD *); // 0x0053F4C0
    static int LoadAudioFromFile(int *p_DWORD, FILE *Stream, int *p_DWORD2); // 0x00569320
    static int OpenBinkVideo(CScreenMode *pScreen, const char *szFilename, int nVal, int nVal2, int nFlags); // 0x005694F0
};
