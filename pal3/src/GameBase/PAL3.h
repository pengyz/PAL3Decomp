#pragma once
// Auto-generated: PAL3

#include "gbengine/gbParticle.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"

class CCBSystem;
class CEffMgr;
class CEffectSystem;
class NPCInfo;
class RenderTarget3;
class Role;
class RoleSystem;
class ScreenEffectMgr;

class PAL3 {
public:
    float m_snaph; // +0x0
    gbTexture * m_pScnFrameTex; // +0x4
    gbRenderEffect * m_pAdditiveEffect; // +0x8
    gbRenderEffect * m_pAdditiveEffect2; // +0xC
    char _gap_010[20]; // +0x10
    float m_fViewX; // +0x24
    float m_fViewY; // +0x28
    float m_fViewZ; // +0x2C
    char _gap_030[85]; // +0x30
    BYTE _todo_085; // +0x85
    char _gap_086[6]; // +0x86
    RoleSystem * m_pCollisionObj; // +0x8C
    char _gap_090[64]; // +0x90
    int m_nPrintScreen; // +0xD0
    gbDropGroup * g_pSnow; // +0xD4
    gbDropGroup * g_pRain; // +0xD8
    int s_bCombatGameOver; // +0xDC
    int s_bActive; // +0xE0
    gbGfxDriverInfo s_drvinfo; // +0xE4
    char _gap_0E8[180]; // +0xE8
    int s_gamestate; // +0x19C
    char * m_pCmdLine; // +0x1A0
    int m_bTestCombat; // +0x1A4
    int m_bCombatWin; // +0x1A8
    int m_bLoadMainUI; // +0x1AC
    int m_bShowRenderInfo; // +0x1B0
    int m_bSoftCursor; // +0x1B4
    int m_bNGHVariance; // +0x1B8
    int m_bWPXVariance; // +0x1BC
    double m_gametime; // +0x1C0
    HICON__ * s_hcur; // +0x1C8
    int m_snapstate; // +0x1CC
    int m_isRenderConsole; // +0x1D0
    char _gap_1D4[216]; // +0x1D4
    int s_flag; // +0x2AC
    CCBSystem * m_pCBSystem; // +0x2B0
    CEffectSystem * m_pEffectSystem; // +0x2B4
    CEffMgr * m_pEffMgr; // +0x2B8
    int m_snapautoindex; // +0x2BC
    int m_snappath; // +0x2C0
    int m_snapw; // +0x2C4
    int m_snaph_2; // +0x2C8
    char _gap_2CC[980]; // +0x2CC
    int _todo_6A0; // +0x6A0
    char _gap_6A4[4]; // +0x6A4
    int _todo_6A8; // +0x6A8
    int _todo_6AC; // +0x6AC
    int _todo_6B0; // +0x6B0
    char _gap_6B4[20]; // +0x6B4
    int _todo_6C8; // +0x6C8
    char _gap_6CC[4]; // +0x6CC
    int _todo_6D0; // +0x6D0
    int _todo_6D4; // +0x6D4
    int _todo_6D8; // +0x6D8
    char _gap_6DC[392]; // +0x6DC
    int _todo_864; // +0x864
    int _todo_868; // +0x868
    int _todo_86C; // +0x86C
    char _gap_870[28]; // +0x870
    gbTexture * _todo_88C; // +0x88C
    int _todo_890; // +0x890
    int _todo_894; // +0x894
    char _gap_898[1032]; // +0x898
    int _todo_CA0; // +0xCA0
    int _todo_CA4; // +0xCA4
    int _todo_CA8; // +0xCA8
    char _gap_CAC[28]; // +0xCAC
    gbTexture * m_pDeviceTex; // +0xCC8
    int _todo_CCC; // +0xCCC
    int _todo_CD0; // +0xCD0
    char _gap_CD4[664]; // +0xCD4
    int _todo_F6C; // +0xF6C
    int _todo_F70; // +0xF70
    int _todo_F74; // +0xF74
    char _gap_F78[28]; // +0xF78
    gbTexture * _todo_F94; // +0xF94
    int _todo_F98; // +0xF98
    int _todo_F9C; // +0xF9C
    char _gap_FA0[952]; // +0xFA0
    int m_nRenderTarget2_DE8DF8; // +0x1358
    int m_nRenderTarget2_DE8DFC; // +0x135C
    int m_nRenderTarget2_DE8E00; // +0x1360
    char _gap_1364[4]; // +0x1364
    int m_nRenderTarget2_DE8E08; // +0x1368
    int m_nEffObjCount; // +0x136C
    int m_nRenderTarget2_DE8E10; // +0x1370
    char _gap_1374[4]; // +0x1374
    int m_nRenderTarget2_DE8E18; // +0x1378
    int m_nRenderTarget2_DE8E1C; // +0x137C
    int m_nRenderTarget2_DE8E20; // +0x1380
    int m_nRenderTarget2State_DE8E24; // +0x1384
    char _gap_1388[648]; // +0x1388
    int m_nRenderTarget2Count; // +0x1610
    int m_nCombatParam3; // +0x1614
    int m_nCombatParam2; // +0x1618
    int m_nCombatParam1; // +0x161C
    char _gap_1620[648]; // +0x1620
    int m_nCEffExplosiveCount; // +0x18A8
    char _gap_18AC[48]; // +0x18AC
    BYTE m_bCEffCylinderFlag_DE937C; // +0x18DC
    char _gap_18DD[3]; // +0x18DD
    int m_nsub_4C55F0Count_DE9380; // +0x18E0
    char _gap_18E4[1576]; // +0x18E4
    BYTE m_bCEffExplosiveFlag_DE99AC; // +0x1F0C
    char _gap_1F0D[3]; // +0x1F0D
    int m_nCEffCylinderCount; // +0x1F10
    char _gap_1F14[756]; // +0x1F14
    int m_nMeteorChainCount; // +0x2208
    char _tail_220C[82308]; // +0x220C
    // total size: 0x16390 (91024)

    void * InitVFileSystem(); // 0x00401BC0
    void * InitVFileSystem2(); // 0x00401C00
    void InitVolModNode(); // 0x00404530
    PAL3(); // 0x00404760
    void _PAL3(); // 0x004047F0
    void InitGFX(); // 0x00404FF0
    bool CreateEffectSystem(); // 0x00405330
    bool DestroyEffectSystem(); // 0x004055A0
    void Update(float dt); // 0x004055D0
    void Render(); // 0x00405C00
    void Destroy(); // 0x00406230
    void CheckSystemRequire(HINSTANCE hinst); // 0x00406310
    void CreateGfxWindow(); // 0x004065F0
    void ParseCmdLine(const char *lpCmdLine); // 0x004066F0
    static bool HasCommandLineParam(char *lpKeyName); // 0x004068C0
    int GetCommandLineParam(); // 0x00406980
    void TestCombat(); // 0x00406A10
    void DefaultKeyMap(int nVal, int nVal2); // 0x00406B80
    void PrintScreen(); // 0x00406D70
    static void SnapScreen(const char *pszName); // 0x00406FF0
    static bool ReadRegistryValue(CHAR *lpSubKey, DWORD dwDisposition, ...); // 0x004070A0
    static void StartWolf(HKEY hKey, CHAR *lpSubKey); // 0x00407180
    static void EndWolf(int nVal); // 0x004071C0
    void StartHideFight(); // 0x004072D0
    void EndHideFight(); // 0x00407300
    static void StartCombat(unsigned int *const pdwVal, int monsterid, Role *side, char pMonster); // 0x00407320
    static char StartCombatFromNPC(const NPCInfo *pNPCInfo, int tmp, Role *side); // 0x00407560
    void EntryCatchGhost(); // 0x00407640
    static bool IfHideFightSucceed(bool bFlag); // 0x00407740
    int InitSubsystems(); // 0x00408BE0
    int FullInit(); // 0x00408FD0
    int UpdateSubsystems(); // 0x004118D0
    int UIPostProcess(); // 0x0041EE40
    void LoadingTimerCallback(); // 0x0041F9F0
    static bool WriteRegistryValue(CHAR *lpSubKey, DWORD dwDisposition, ...); // 0x00437E60
    static bool WriteRegistryDword(CHAR *lpSubKey, DWORD dwDisposition, ...); // 0x0044E2B0
    static void LoadRoleByIndex(int nVal); // 0x0044E390
    char * LoadUnlockFlags(); // 0x0044E410
    static bool WriteRegistryKey(CHAR *lpSubKey, DWORD dwDisposition, ...); // 0x00456590
    char HandleDeviceReset(); // 0x00459860
    int EnterGameMode(int nVal); // 0x00461BF0
    int SetValue(unsigned __int8 nValue); // 0x00461FD0
    int SetPanelStates(unsigned __int8 pData); // 0x00462030
    int SetRange(unsigned __int8 nMax); // 0x00462080
    int GetValue(unsigned __int8 nIndex); // 0x00462220
    void Render_47c260(); // 0x0047C260
    void DispatchModeCommand(int nVal); // 0x0047C2D0
    static bool WriteRegistry(CHAR *lpSubKey, DWORD dwDisposition, ...); // 0x004B2840
    RenderTarget3 * GetInstance(); // 0x004B6D30
    int * CreateTextures(); // 0x004BDA60
    PAL3 * GetInstance_db10(); // 0x004BDB10
    void InvalidateSnapH(); // 0x004BDED0
    ScreenEffectMgr * GetInstance_fd20(); // 0x004BFD20
    void ClearAdditiveEffects(); // 0x004C0400
    char CreateRenderEffects(); // 0x004C58C0
    int * HandleDeviceLost(); // 0x00527C30
    static bool WriteRegistryDwordEx(CHAR *lpSubKey, DWORD dwDisposition, ...); // 0x0052F570
    char CheckViewCollision(); // 0x00532F60
    static void ResetForNewScene(char bSaveData); // 0x00569110
};
