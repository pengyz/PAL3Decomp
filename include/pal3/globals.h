#pragma once
// PAL3 global variables
// Addresses are from the original PAL3.exe binary

class CCBSystem;
class CEffMgr;
#include "pal3/gen/CGameData.h"
class CScreenMode;
class Config;
class GRPinput;
class Logger;
class PalScript;
class RoleSystem;
#include "pal3/gen/SceneMgr.h"
class TextureLib;
class UIManager;

// Core engine pointers (0xBFDA60 region)
extern void *g_pGfxManager;        // 0x00BFDA60 - gbGfxManager*
extern void *g_pActorMgr;          // 0x00BFDA64 - gbActorMgr*
extern void *g_pCamera;            // 0x00BFDA68 - gbCamera*
extern int g_nGameState;           // 0x00BFDA6C
extern SceneMgr *g_pSceneMgr;     // 0x00BFDA70
extern CCBSystem *g_pCBSystem;     // 0x00BFDA74
extern CGameData *g_pGameData;     // 0x00BFDA78
extern CScreenMode *g_pScreenMode; // 0x00BFDA7C
extern GRPinput *g_pInput;         // 0x00BFDA80
extern RoleSystem *g_pRoleSystem;  // 0x00BFDA84
extern UIManager *g_pUIManager;    // 0x00BFDA8C
extern CEffMgr *g_pEffMgr;        // 0x00BFDA90
extern Logger *g_pLogger;          // 0x00BFDA94
extern PalScript *g_pPalScript;    // 0x00BFDA98
extern Config *g_pConfig;          // 0x00BFDA9C
extern TextureLib *g_pTextureLib;  // 0x00BFDAA0

// GRPinput global instance
extern GRPinput g_Input;           // 0x00BFAD70

// Scene manager instance
extern SceneMgr g_SceneMgr;       // 0x00C04390

// Game data instance
extern CGameData g_GameData;       // 0x00D8E4C0

// Game state flags
extern int g_nGameFlags;           // from PAL3 static
extern int g_bGameActive;          // from PAL3 static
extern int g_bRenderUI;

// Scene state (0xC04370 cluster)
extern int g_nSceneFlags;          // 0x00C04370
extern int g_nSceneMode;           // 0x00C04374
extern int g_nSceneState;          // 0x00C04384
extern int g_nSceneType;           // 0x00C04388

// Cursor
extern int g_nCursorState;         // 0x01895580
extern unsigned char g_bCursorVisible; // 0x01895560
extern void *g_pCursorNode1;
extern void *g_pCursorNode2;

// UI
extern int g_nUIState;             // 0x01896BE0

// RNG (CRT rand state)
extern int g_RandSeed;             // 0x005DFDEC
extern int g_nRandCallCount;       // 0x017AD310

// Misc
// g_pVFileSys declared in gbengine/gbVFileSystem.h
// g_CurrentTime declared in gbengine/gbengine_types.h
extern void *g_PAL3Data;           // 0x008ACBF8
extern char g_GDB[];               // PAL_GDB global data
