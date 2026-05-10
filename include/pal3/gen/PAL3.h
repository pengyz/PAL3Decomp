#pragma once
// Auto-generated: PAL3

class CCBSystem;
class CEffMgr;
class CEffectSystem;
class HICON__;
class gbDropGroup;
class gbGfxDriverInfo;

class PAL3 {
public:
    gbImage2D m_screenImg; // +0x0
    int m_nPrintScreen; // +0xDC
    gbDropGroup * g_pSnow; // +0xE0
    gbDropGroup * g_pRain; // +0xE4
    int s_bCombatGameOver; // +0xE8
    int s_bActive; // +0xEC
    gbGfxDriverInfo s_drvinfo; // +0xF0
    int s_gamestate; // +0x1A8
    char * m_pCmdLine; // +0x1AC
    int m_bTestCombat; // +0x1B0
    int m_bCombatWin; // +0x1B4
    int m_bLoadMainUI; // +0x1B8
    int m_bShowRenderInfo; // +0x1BC
    int m_bSoftCursor; // +0x1C0
    int m_bNGHVariance; // +0x1C4
    int m_bWPXVariance; // +0x1C8
    double m_gametime; // +0x1D0
    HICON__ * s_hcur; // +0x1D8
    int m_snapstate; // +0x1DC
    int m_isRenderConsole; // +0x1E0
    int s_keymap[54]; // +0x1E4
    int s_flag; // +0x2BC
    CCBSystem * m_pCBSystem; // +0x2C0
    CEffectSystem * m_pEffectSystem; // +0x2C4
    CEffMgr * m_pEffMgr; // +0x2C8
    int m_snapautoindex; // +0x2CC
    int m_snappath; // +0x2D0
    int m_snapw; // +0x2D4
    int m_snaph; // +0x2D8
    // total size: 0x2E0 (736)

    PAL3(); // 0x00404760
    ~PAL3(); // 0x004047F0
    // [IDA_USERPURGE] Create; // 0x00404800
    static void InitGFX(); // 0x00404FF0
    static char CreateEffectSystem(); // 0x00405330
    static char DestroyEffectSystem(); // 0x004055A0
    // [IDA_USERPURGE] Update; // 0x004055D0
    static void Render(); // 0x00405C00
    static void Destroy(); // 0x00406230
    // [IDA_USERPURGE] CheckSystemRequire; // 0x00406310
    static char CreateGfxWindow(); // 0x004065F0
    static char ParseCmdLine(char *lpKeyName); // 0x004066F0
    static int HasCommandLineParam(char *lpKeyName); // 0x004068C0
    static int GetCommandLineParam(); // 0x00406980
    static int TestCombat(); // 0x00406A10
    static int DefaultKeyMap(const char *a1, int a2, int a3); // 0x00406B80
    static void PrintScreen(); // 0x00406D70
    static int SnapScreen(int a1); // 0x00406FF0
    static char StartWolf(HKEY hKey, CHAR *lpSubKey); // 0x00407180
    static void EndWolf(int a1); // 0x004071C0
    static int StartHideFight(); // 0x004072D0
    static int EndHideFight(); // 0x00407300
    static char StartCombat(int a1, int a2, int a3, char a4); // 0x00407320
    static char StartCombat(const void *a1, int a2, int a3); // 0x00407560
    static char EntryCatchGhost(); // 0x00407640
    static gbGfxManager * IfHideFightSucceed(int a1); // 0x00407740
    static int InitSubsystems(); // 0x00408BE0
    static int FullInit(); // 0x00408FD0
    static int UpdateSubsystems(); // 0x004118D0
    static int UIPostProcess(); // 0x0041EE40
};
