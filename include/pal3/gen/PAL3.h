#pragma once
// Auto-generated: PAL3

#include "GAME_STATE.h"
#include "gbGfxDriverInfo.h"

class CCBSystem;
class CEffMgr;
class CEffectSystem;
class HICON__;
class gbDropGroup;

class PAL3 {
public:
    gbImage2D m_screenImg; // +0x0
    unsigned long m_nPrintScreen; // +0x0
    gbDropGroup * g_pSnow; // +0x0
    gbDropGroup * g_pRain; // +0x0
    int s_bCombatGameOver; // +0x0
    int s_bActive; // +0x0
    gbGfxDriverInfo s_drvinfo; // +0x0
    GAME_STATE s_gamestate; // +0x0
    char * m_pCmdLine; // +0x0
    unsigned char m_bTestCombat; // +0x0
    unsigned char m_bCombatWin; // +0x0
    unsigned char m_bLoadMainUI; // +0x0
    unsigned char m_bShowRenderInfo; // +0x0
    unsigned char m_bSoftCursor; // +0x0
    unsigned char m_bNGHVariance; // +0x0
    unsigned char m_bWPXVariance; // +0x0
    double m_gametime; // +0x0
    HICON__ * s_hcur; // +0x0
    int m_snapstate; // +0x0
    unsigned char m_isRenderConsole; // +0x0
    unsigned short s_keymap[54]; // +0x0
    unsigned long s_flag; // +0x0
    CCBSystem * m_pCBSystem; // +0x0
    CEffectSystem * m_pEffectSystem; // +0x0
    CEffMgr * m_pEffMgr; // +0x0
    int m_snapautoindex; // +0x0
    struct allocator<char> > {}; // nested type stub
    allocator<char> > m_snappath; // +0x0
    int m_snapw; // +0x0
    int m_snaph; // +0x0
    // total size: 0x1 (1)

    PAL3(); // 0x00404760
    ~PAL3(); // 0x004047F0
    static struct gbVFileSystem *__usercall@<eax> Create(char *a1, HINSTANCE hInstance); // 0x00404800
    static void InitGFX(); // 0x00404FF0
    static char CreateEffectSystem(); // 0x00405330
    static char DestroyEffectSystem(); // 0x004055A0
    static int Update(float a1); // 0x004055D0
    static int Render(); // 0x00405C00
    static int Destroy(); // 0x00406230
    static void __usercall CheckSystemRequire(char *a1, char *a2, HINSTANCE hInstance); // 0x00406310
    static char CreateGfxWindow(); // 0x004065F0
    static char ParseCmdLine(char *lpKeyName); // 0x004066F0
    static int HasCommandLineParam(char *lpKeyName); // 0x004068C0
    static int GetCommandLineParam(); // 0x00406980
    static int TestCombat(); // 0x00406A10
    static int DefaultKeyMap(const char *a1, int a2, int a3); // 0x00406B80
    static void PrintScreen(); // 0x00406D70
    static int SnapScreen(int a1); // 0x00406FF0
    static char StartWolf(HKEY hKey, CHAR *lpSubKey); // 0x00407180
    static int EndWolf(int a1); // 0x004071C0
    static int StartHideFight(); // 0x004072D0
    static int EndHideFight(); // 0x00407300
    static int StartCombat(int a1, int a2, int a3, char a4); // 0x00407320
    static int StartCombat(const void *a1, int a2, int a3); // 0x00407560
    static char EntryCatchGhost(); // 0x00407640
    static int IfHideFightSucceed(int a1); // 0x00407740
    static int InitSubsystems(); // 0x00408BE0
    static int FullInit(); // 0x00408FD0
    static int UpdateSubsystems(); // 0x004118D0
    static int UIPostProcess(); // 0x0041EE40
};
