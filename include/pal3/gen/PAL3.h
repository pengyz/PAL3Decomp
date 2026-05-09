#pragma once
// Auto-generated from IDA decomp - PAL3
// 30 methods

class PAL3 {
public:
    static void *() PAL3();  // 0x00404760
    static int() ~PAL3();  // 0x004047F0
    static struct gbVFileSystem *__cdecl(HINSTANCE hInstance) Create();  // 0x00404800
    static void() InitGFX();  // 0x00404FF0
    static char() CreateEffectSystem();  // 0x00405330
    static char() DestroyEffectSystem();  // 0x004055A0
    static int Update(float a1);  // 0x004055D0
    static int() Render();  // 0x00405C00
    static int() Destroy();  // 0x00406230
    static void CheckSystemRequire(char *a1@<edi>, char *a2@<esi>, HINSTANCE hInstance);  // 0x00406310
    static char() CreateGfxWindow();  // 0x004065F0
    static char ParseCmdLine(char *lpKeyName);  // 0x004066F0
    static int HasCommandLineParam(char *lpKeyName);  // 0x004068C0
    static int() GetCommandLineParam();  // 0x00406980
    static int() TestCombat();  // 0x00406A10
    static int DefaultKeyMap(const char *a1, int a2, int a3);  // 0x00406B80
    static void() PrintScreen();  // 0x00406D70
    static int SnapScreen(int a1);  // 0x00406FF0
    static char StartWolf(HKEY hKey, CHAR *lpSubKey);  // 0x00407180
    static int EndWolf(int a1);  // 0x004071C0
    static int() StartHideFight();  // 0x004072D0
    static int() EndHideFight();  // 0x00407300
    static int StartCombat(int a1, int a2, int a3, char a4);  // 0x00407320
    static int StartCombat(const void *a1, int a2, int a3);  // 0x00407560
    static char() EntryCatchGhost();  // 0x00407640
    static int IfHideFightSucceed(int a1);  // 0x00407740
    static int() InitSubsystems();  // 0x00408BE0
    static int __cdecl() FullInit();  // 0x00408FD0
    static int __cdecl() UpdateSubsystems();  // 0x004118D0
    static int __cdecl() UIPostProcess();  // 0x0041EE40
};
