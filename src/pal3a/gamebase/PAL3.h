#ifndef PAL3A_PAL3_H
#define PAL3A_PAL3_H

#include "pal3a_types.h"

class PAL3 {
public:
    char _data[1];

    void Create(HINSTANCE * hinst);
    void EndWolf(int roleid);
    void Update(double deltaTime);
    ~PAL3();
    void CreateGfxWindow(HINSTANCE * hinst);
    void StartCombat(NPCInfo * tmp, int side, Role * pMonster);
    void StartCombat(ulong * monsterid, int side, Role * pMonster, uchar bBossMusic);
    void Render();
    void DefaultKeyMap();
    bool IfHideFightSucceed(uchar daybreak);
    bool DestroyEffectSystem();
    void WriteSnapScreen();
    void PrintScreen(int width, int height);
    void Init();
    void TestCombat();
    void ParseCmdLine();
    void StartWolf(int flag);
    void InitGFX(HINSTANCE * hinst);
    bool HasCommandLineParam(char * s);
    void Destroy();
    void EndHideFight();
    void OnSwitchState(GAME_STATE old, GAME_STATE now);
    void SnapScreen(char * savefile, int savewidth, int saveheight);
    void StartHideFight();
    bool CreateEffectSystem();
    int GetCommandLineParam(char * s);
    PAL3();
    int CheckSystemRequire();
    void EntryCatchGhost();
};

void SFINIT0_Pal3Init();
long WinProc(HWND * hwnd, uint uMsg, uint wParam, long lParam);

#endif // PAL3A_PAL3_H
