#pragma once

#include <windows.h>

class gbGfxManager;
class GRPinput;
extern GRPinput g_Input;

// ============================================================
// ============================================================

extern DWORD g_bGameActive;             // 0x005833B8
extern HINSTANCE hInstance;             // 0x00BFDA48
extern char WindowName[32];            // 0x005839C4
extern HWND hWnd;                      // 0x00BFDA4C
extern HWND hWndParent;                // 0x00BFDA50
extern int xRight;                     // 0x00BFDA54
extern int yBottom;                    // 0x00BFDA58
extern int g_hCursor;                  // 0x00BFDA94

// ============================================================
// ============================================================

extern gbGfxManager *g_pGfxManager;    // 0x00BFDA60
extern void *g_pActorMgr;              // 0x00BFDA64 (gbActorMgr*)
extern void *g_pCamera;                // 0x00BFDA68 (CameraCtrl*)
extern void *g_pCBSystem;              // 0x00BFDA74 (CCBSystem*)
extern int g_pSceneMgr;                // 0x00BFDA78
extern int g_UIManager;                // 0x00C11758
extern int g_GDB;                      // 0x00975ED8

// ============================================================
// ============================================================

extern char Data[260];                 // 0x01894970
extern char Filename[260];             // 0x01894A74
extern double dbl_1895070;             // 0x01895070
extern char byte_BFDA90;               // 0x00BFDA90
extern char byte_5833C0;               // 0x005833C0
extern char g_Logger;                  // 0x017B1EC0
extern int g_pCursorNode1;             // 0x00A3A6EC
extern int g_pCursorNode2;             // 0x00A3A6F0
extern void *unk_A3A7D8;              // 0x00A3A7D8
extern void *off_56A66C;              // 0x0056A66C
class CGameData { public: void Destroy(); int GetMode(); char _pad[0x38D0]; };
extern CGameData g_GameData;                 // 0x00DB9FD0

// ============================================================
// ============================================================

extern const char aSoftwareSoftst_1[];
extern const char aCdriver[];
extern const char asc_5D41EC[];
extern const char aPal3[];
extern const char aPercentSMovie[];
extern const char aPlsInsertDisc[];
extern const char aDatascriptComb[];
extern const char aDatascriptLang[];
extern const char aAppname[];
extern const char aInputDeviceCre[];
extern const char aDProjectPal3Ga_0[];
extern const char aFightDatabaseL[];
extern const char aCouldNotAlloca[];
extern const char aCouldNotAlloca_0[];
extern const char aAssislangLang[];
extern const char aSBulidSS[];
extern const char aV104[];
extern const char aGameCreateOk[];
extern const char aObjectG02Cvd[];
extern const char aObjectG03Cvd[];
extern const char aMovieLogoBik[];
extern const char aCreateGfxManag[];
extern const char aCreateActorman[];
extern const char aCNewFailed[];
extern const char aGfxscriptGlowG[];
extern const char aGfxscriptGeomG[];
extern const char aWt[];
extern const char aEnginelogTxt[];
extern const char aExceptionS[];
extern const char aConsoleErrorCo[];
extern const char aXuejian[];
extern const char aLongkui[];
extern const char aZixuan[];
extern const char aChangqing[];
extern const char aHuaying[];

extern int g_nGameState;
extern float g_fEventTimer;
extern float g_fSceneTime;
extern float g_fTotalTime;
extern int dword_BFDA98;
extern int dword_BFDA84;
extern int dword_BFDA7C;
extern char byte_BFDA91;

extern int dword_BFD6C8;
extern void *off_56A694;
extern char unk_A3A6F8;
extern const char aPal3Exception[];
extern int dword_BFD774;

// PAL3 subsystem variables
extern int g_nGameFlags;
extern int g_pRoleSystem;
extern int dword_BFDA34;
extern int dword_BFDA38;
extern int dword_BFDA3C;
extern int dword_BFDA80;
extern int dword_BFD6C8;
extern int dword_C1171C;
extern int dword_C11754;
extern int dword_D8E488;
extern char byte_BFDA40;
extern char byte_BFDA41;
extern char byte_5833D0;
extern char byte_C11748;
extern char byte_C11750;
extern char byte_C11751;
extern char byte_D8C339;
extern char byte_D924E8;
extern char g_bRenderUI;
extern float flt_C1096C;
extern short word_8ACCD8;
extern void *off_56A66C;
extern void *off_56A694;
extern void *unk_A3A7D8;
extern char unk_A3A6F8;
extern char Data[260];
extern char Filename[260];
extern double dbl_1895070;

