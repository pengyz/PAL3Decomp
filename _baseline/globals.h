#pragma once
// PAL3 global variables with known types
// Auto-generated from pipeline/data/annotations/globals.json

#include <windows.h>

// 702 typed globals

#include "pal3/gen/ARC_PlayerAtt.h"
#include "pal3/gen/Array.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/PAL3.h"
#include "pal3/gen/RenderTarget3.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/SceneMgr.h"
#include "pal3/gen/ScriptCounter.h"
#include "pal3/gen/ScriptSystemData.h"

class CCBRoleState;
class CCBSystem;
class CameraCtrl;
class ComposeUI;
class PAL_GDB;
class PalScript;
class Role;
class gbActorMgr;
class gbGfxDriverInfo;
class gbVec3D;
class gbVolModNode;

extern unsigned char g_bActorFlag; // 0x0056A634
extern const char ArgList[]; // 0x0056A660
extern void * g_vtbl_UITitle_YXXX; // 0x0056A9C0
extern int g_MonsterEntryTable[]; // 0x0056C568
extern void * g_ArcSceneMonsterTable; // 0x0056C57C
extern void * g_pfnCallback; // 0x0056D604
extern void * g_ArcSceneMonsterTable2; // 0x0056E15C
extern int g_ComposeUIChildIDs[]; // 0x0056F02C
extern void * g_vtbl_CEffSParticle; // 0x0056F62C
extern const LPCSTR lpFileName; // 0x0056FC8C
extern int g_nStatePanelL[4]; // 0x0056FCC8
extern int g_nStatePanelT[4]; // 0x0056FCD8
extern const int bVisible; // 0x0056FDAC
extern const int animId; // 0x0056FE20
extern int g_nItemTypeBase[4]; // 0x00570080
extern int g_nSkillTabIDs[4]; // 0x00570090
extern int g_nMagicTabIDs[4]; // 0x005700A0
extern int g_nItemTabIDs[4]; // 0x005700B0
extern int g_nItemIDs_69[5]; // 0x005700C0
extern int g_nSkillItemIDTable[25]; // 0x005700D4
extern int g_nPropIDs_208[5]; // 0x00570138
extern int g_nPropIDs_241[11]; // 0x0057014C
extern int g_nStatePanelL_dup[4]; // 0x00570178
extern int g_nStatePanelT_dup[4]; // 0x00570188
extern int g_nSpriteSize_64[5]; // 0x00570198
extern int g_nSpriteSize_82[5]; // 0x005701AC
extern int g_nSpriteSize_20[5]; // 0x005701C0
extern int g_nUnkDataTable[30]; // 0x005701D4
extern int g_nUnkTable_24C[7]; // 0x0057024C
extern int g_nUnkTable_268[7]; // 0x00570268
extern const LPCSTR lpString; // 0x00570618
extern const CHAR SubKey[]; // 0x00572B3C
extern const CHAR OutputString[]; // 0x00572DB0
extern const CHAR ProcName[]; // 0x00573268
extern const CHAR ModuleName[]; // 0x00573284
extern const WCHAR SrcStr; // 0x00573388
extern const CHAR LibFileName[]; // 0x005737D4
extern const char a1Qnan[]; // 0x005737E0
extern const char a1Inf[]; // 0x005737E8
extern char a1Ind[]; // 0x005737F0
extern char a1Snan[]; // 0x005737F8
extern char ValueName_0[256]; // 0x00575098
extern char Format[256]; // 0x00580A88
extern char Mode[3]; // 0x00580D00
extern int g_nPAL3_5833B8; // 0x005833B8
extern unsigned long g_dwGameFlags; // 0x005833BC
extern unsigned char g_bFullScreen; // 0x005833C0
extern unsigned char g_bGameFlag2; // 0x005833C2
extern int g_nKeyMap1; // 0x005833C4
extern int g_nKeyMap2; // 0x005833C8
extern int g_nKeyMap3; // 0x005833CC
extern char g_szGamePath[256]; // 0x005833D0
extern char a101h[]; // 0x005834CC
extern char a163941[]; // 0x00583814
extern char path[256]; // 0x00583820
extern char name[256]; // 0x0058388C
extern char filename[256]; // 0x005838A8
extern CHAR section[]; // 0x00583998
extern char dir[256]; // 0x00583A9C
extern int g_nPtrArray_586154; // 0x00586154
extern int g_nFrameRate; // 0x00586158
extern int g_nUpdateInterval; // 0x0058615C
extern char * g_pszDefaultScene; // 0x00586180
extern char * g_pszScene1; // 0x00586184
extern char * g_pszScene2; // 0x00586188
extern void * g_pfnUpdateFuncs[5]; // 0x0058618C
extern char * g_pszSceneSlot3; // 0x00586190
extern char * g_pszSceneSlot2; // 0x00586194
extern char * g_pszSceneSlot1; // 0x00586198
extern char * g_pszSceneSlot0; // 0x0058619C
extern int g_nCameraUpdateCount; // 0x0058B230
extern int g_nRoleSystem_58B234; // 0x0058B234
extern float g_fCameraDefaultDist; // 0x0058B238
extern int g_nRoleSystem_58B38C; // 0x0058B38C
extern char a1n07a[]; // 0x0058B784
extern float g_fEffectTimer; // 0x0058DE64
extern char a368[]; // 0x005905AC
extern char a13i2[]; // 0x00595960
extern char a14i1[]; // 0x005959D8
extern char a15b1[]; // 0x00595A50
extern char a15c1[]; // 0x00595A8C
extern char a15h1[]; // 0x00595B04
extern char a106[]; // 0x00596200
extern char aA[]; // 0x00596230
extern char aS_2[3]; // 0x005967B0
extern char aQ07[4]; // 0x00598C14
extern const char * g_szDataPath; // 0x005995AC
extern const char * g_pCScreenMode; // 0x0059B5E8
extern char a13i2_0[]; // 0x005A06B0
extern char a14i1_0[]; // 0x005A0728
extern char a15b1_0[]; // 0x005A07A0
extern char a15c1_0[]; // 0x005A07DC
extern char a15h1_0[]; // 0x005A0854
extern unsigned char g_bSceneLoaded; // 0x005A0998
extern float g_fDefaultFOV; // 0x005A099C
extern int g_nMiniGameParam; // 0x005A3748
extern char tex[256]; // 0x005A3774
extern char aP[]; // 0x005ABA60
extern unsigned char g_bAudioEnabled; // 0x005AE1E4
extern unsigned char g_bEffectEnabled; // 0x005B0958
extern char a13i2_1[]; // 0x005B1280
extern char a14i1_1[]; // 0x005B12F8
extern char a15b1_1[]; // 0x005B1370
extern char a15c1_1[]; // 0x005B13AC
extern char a15h1_1[]; // 0x005B1424
extern const char * g_pCScreenMode_5B46B4; // 0x005B46B4
extern void * g_pCombatUIData; // 0x005BC4A8
extern const char * g_pCScreenMode_5BC918; // 0x005BC918
extern char szFilename[260]; // 0x005BEE3C
extern const char * g_pCScreenMode_5C7768; // 0x005C7768
extern unsigned char g_bDebugMode; // 0x005CEFA8
extern unsigned char g_bRoleSystem_5CEFA9; // 0x005CEFA9
extern const char * g_pCScreenMode_5CF1E8; // 0x005CF1E8
extern const char * g_pCScreenMode_5CF1F4; // 0x005CF1F4
extern int g_nFiveNimbusCount; // 0x005D0750
extern CHAR aN[]; // 0x005D0F44
extern int g_nTextureDefault; // 0x005D41B0
extern float g_fConst400; // 0x005D41B4
extern float g_fRenderHeight; // 0x005D41B8
extern float g_fRenderWidth; // 0x005D41BC
extern int g_EffCylinderEditorData; // 0x005D4D3C
extern const char * g_pszEditorDesc; // 0x005D4D7C
extern int g_EffEditorState; // 0x005D4DF4
extern CEffMgr g_EffMgr; // 0x005D5484
extern char FileName[256]; // 0x005D558C
extern unsigned int roleIdx; // 0x005D87F4
extern char a164229[]; // 0x005D88BC
extern char a03dS[]; // 0x005D8968
extern char aY[]; // 0x005D8970
extern char a15f[]; // 0x005D89B4
extern CHAR AppName[]; // 0x005D89E0
extern CHAR KeyName[]; // 0x005D89E8
extern char g_szCCBStageCamName[]; // 0x005D8A38
extern char a12f[]; // 0x005D8ACC
extern char a02f[]; // 0x005D8B78
extern char aO[]; // 0x005D8B84
extern char a203[]; // 0x005DBEA0
extern unsigned char g_bCombatDebugMode; // 0x005DFDEB
extern unsigned long g_nCombatRandSeed; // 0x005DFDEC
extern char aRb[3]; // 0x005DFE08
extern char aR[]; // 0x005F24CC
extern LPCSTR lpString2; // 0x005F50B8
extern char PathName_0[256]; // 0x00601528
extern LPCSTR aPal3Timenotefi_96_0; // 0x00601548
extern LPCSTR lpString1; // 0x00608B3C
extern char Delimiter[256]; // 0x00608CB4
extern const char * pszName3; // 0x00608CD8
extern int g_TileData[]; // 0x0060AD00
extern void * jpt_55C6DD; // 0x0060B76E
extern gbVFileSystem * g_VFileSystem; // 0x006EBFA0
extern gbVFileSystem * g_BaseVFileSystem; // 0x007CC178
extern int g_nSaveDataSize; // 0x008834C0
extern float g_fPAL3Timer; // 0x008ACBEC
extern PAL3 g_PAL3_Instance; // 0x008ACBF0
extern int g_nLoadBufferSize; // 0x008DDCE0
extern PAL_GDB * g_pGDB; // 0x00975ED8
extern unsigned char g_UITemplateData[]; // 0x00A00000
extern int g_nRenderFlags; // 0x00A3A6EC
extern int g_nRenderMode; // 0x00A3A6F0
extern gbVolModNode * g_pVolModNode; // 0x00A3A6F8
extern CScreenMode g_ScreenMode; // 0x00A3A7D8
extern ARC_PlayerAtt g_PlayerAttBuffer; // 0x00AA0B00
extern unsigned char g_PalScriptTemplate[]; // 0x00AABEF6
extern ARC_PlayerAtt g_PlayerAttBuffer2; // 0x00ABCD00
extern unsigned char g_PlayerAttTemplate[]; // 0x00ABD000
extern int g_ScriptSlots[132]; // 0x00BFAB60
extern GRPinput g_Input; // 0x00BFAD70
extern gbGfxDriverInfo g_DrvInfo; // 0x00BFD6C8
extern int g_nDisplayMode; // 0x00BFD6CC
extern int g_nDisplayWidth; // 0x00BFD6D0
extern int g_nDisplayHeight; // 0x00BFD6D4
extern int g_nColorBits; // 0x00BFD6E0
extern int g_nDepthBits; // 0x00BFD6E4
extern int g_nSyncMode; // 0x00BFD6E8
extern unsigned char g_bSoftCursor; // 0x00BFD6F0
extern HINSTANCE g_hInstance; // 0x00BFD770
extern HWND hWnd; // 0x00BFD774
extern int g_nScreenWidth; // 0x00BFD778
extern int g_nScreenHeight; // 0x00BFD77C
extern int g_nGameTime; // 0x00BFDA04
extern int g_nTickCount; // 0x00BFDA2C
extern float g_fDeltaTime; // 0x00BFDA30
extern float g_fGameSpeed; // 0x00BFDA34
extern gbDropGroup * g_pDropGroup; // 0x00BFDA38
extern int g_nPAL3_BFDA3C; // 0x00BFDA3C
extern int g_nWolfIndex; // 0x00BFDA44
extern HINSTANCE hInstance; // 0x00BFDA48
extern HWND hWndParent; // 0x00BFDA4C
extern HWND hDlg; // 0x00BFDA50
extern HWND g_hMainWnd; // 0x00BFDA54
extern float g_fFadeAngle; // 0x00BFDA58
extern float g_fTimeScale; // 0x00BFDA5C
extern gbGfxManager * gfxMgr; // 0x00BFDA60
extern gbActorMgr * g_pActorMgr; // 0x00BFDA64
extern CameraCtrl * g_pCameraCtrl; // 0x00BFDA68
extern int g_nSceneState; // 0x00BFDA6C
extern void * g_pEffectSystem; // 0x00BFDA70
extern CCBSystem * g_pCBSystem; // 0x00BFDA74
extern void * g_pSceneManager; // 0x00BFDA78
extern void * g_pMiniGame2; // 0x00BFDA7C
extern void * g_pMiniGame1; // 0x00BFDA80
extern void * g_pMiniGame3; // 0x00BFDA84
extern unsigned char g_bSceneLoaded; // 0x00BFDA88
extern int g_nCombatMode; // 0x00BFDA8C
extern unsigned char g_bTestCombat; // 0x00BFDA90
extern unsigned char g_bPAL3_BFDA91; // 0x00BFDA91
extern HCURSOR g_hCursor; // 0x00BFDA94
extern int g_bEditorMode; // 0x00BFDA98
extern float g_fGameTimer; // 0x00BFDAA0
extern CHAR Default[8]; // 0x00BFDAA4
extern float g_fPathScale; // 0x00BFDAAC
extern std::ios_base g_UIScene; // 0x00BFDAB0
extern int g_nMagicSlotCountA; // 0x00BFDB70
extern int g_nMagicSlotCountB; // 0x00BFDB74
extern void ** g_pScriptObjArray; // 0x00BFDB80
extern void * g_pScriptEventObj; // 0x00BFDB84
extern int g_nScriptEventParam; // 0x00BFDB90
extern float g_fScriptEventParam2; // 0x00BFDB94
extern int g_nScriptRolePosX; // 0x00BFDB98
extern int g_nScriptRolePosY; // 0x00BFDB9C
extern int g_nScriptRolePosZ; // 0x00BFDBA0
extern unsigned int g_nCurrentEventId; // 0x00BFDBA4
extern int g_nActor_BFDBA8; // 0x00BFDBA8
extern int g_nActor_BFDBAC; // 0x00BFDBAC
extern RoleSystem g_RoleSystemExtra0; // 0x00BFDBB0
extern RoleSystem g_RoleSystemExtra1; // 0x00BFFDB0
extern float g_fCamRoleParams[40]; // 0x00C01FB0
extern ScriptCounter g_ScriptCounters[10]; // 0x00C02050
extern unsigned char g_ScriptCountersEnd; // 0x00C020F0
extern RoleSystem g_RoleSystemMain; // 0x00C020F8
extern int g_nRoleMoveParam; // 0x00C02370
extern float g_fScriptTimeAccum; // 0x00C042E8
extern int g_nPtrArray_C04300; // 0x00C04300
extern int g_nRoleInitLevel[6]; // 0x00C04334
extern Array g_SceneMgrPrefix; // 0x00C04350
extern void * g_RoleTeam1; // 0x00C04354
extern int g_RoleTeam2[]; // 0x00C04358
extern int g_pRoleTeam0_Capacity; // 0x00C0435C
extern Array g_RoleTeamArray; // 0x00C04360
extern void * arr; // 0x00C04364
extern void * end; // 0x00C04368
extern int g_pRoleTeam1_Capacity; // 0x00C0436C
extern Array g_nSceneFlags; // 0x00C04370
extern int g_nSceneMode; // 0x00C04374
extern void * elem; // 0x00C04378
extern int g_nPAL3_C0437C; // 0x00C0437C
extern Array g_SceneArray; // 0x00C04380
extern int g_nSceneState; // 0x00C04384
extern int g_nSceneType; // 0x00C04388
extern int * g_pSceneArrayEnd; // 0x00C0438C
extern SceneMgr g_SceneMgr; // 0x00C04390
extern int * g_pSceneArrayEnd2; // 0x00C0439C
extern RoleSystem g_ScriptRoleBuf; // 0x00C04920
extern RoleSystem * g_pRoleSystems; // 0x00C05F60
extern int g_nUnk61D8; // 0x00C061D8
extern unsigned int g_nScriptObjectCount; // 0x00C08664
extern PalScript * g_pScriptArrayEnd2; // 0x00C1096C
extern RoleSystem * g_pRoleSystemArrayEnd; // 0x00C10A0E
extern PalScript * g_pCurrentScript; // 0x00C10CBC
extern unsigned char g_bFormationReady; // 0x00C10CC0
extern unsigned char g_nSceneTransitionParam2; // 0x00C10CC1
extern int g_nCurrentRoleSlot; // 0x00C10CC8
extern float g_fFadeTimer; // 0x00C10CD0
extern char g_szSceneUIText[256]; // 0x00C10D38
extern double g_fCollisionRadius; // 0x00C10D40
extern float g_fSceneTileSize; // 0x00C1109C
extern gbSound2DNode * g_pBGMTable[]; // 0x00C11360
extern gbSound2DNode * g_pAmbientTable[]; // 0x00C113C0
extern float g_fTileSize; // 0x00C116C4
extern unsigned char m_bPathEnabled; // 0x00C116EA
extern RoleSystem * g_pRoleSystem; // 0x00C116EC
extern gbSound2DNode * g_pCurrentBGM; // 0x00C116F4
extern float g_fCameraBlendWeight; // 0x00C116F8
extern int g_nPartyRoles[6]; // 0x00C11700
extern int g_nPartyCount; // 0x00C11718
extern int g_nMonsterType; // 0x00C11744
extern Role * g_pCombatRole; // 0x00C11754
extern float g_fTileScale; // 0x00C12B14
extern int g_nLastUpdateTime; // 0x00C12B1C
extern unsigned long g_lastupdateloading; // 0x00C12B20
extern float g_fPalScript_C12B28; // 0x00C12B28
extern float g_fPalScript_C12B2C; // 0x00C12B2C
extern float g_fPalScript_C12B30; // 0x00C12B30
extern int g_nunknown_libname_331_C12B38; // 0x00C12B38
extern int g_nunknown_libname_331_C12B3C; // 0x00C12B3C
extern int g_nunknown_libname_331_C12B40; // 0x00C12B40
extern RoleSystem g_RoleSystemInstance; // 0x00C12B48
extern ScriptSystemData g_ScriptSystemData; // 0x00D8B318
extern int g_nGameMode; // 0x00D8BBEC
extern gbVec3D g_vRotateAxis; // 0x00D8BC20
extern unsigned char g_bMapRenderFlags; // 0x00D8BC2C
extern int g_nScriptCounter0; // 0x00D8BC30
extern int g_nScriptCounter1; // 0x00D8BC34
extern int g_nScriptFlag; // 0x00D8BC38
extern float g_fScriptTileSize; // 0x00D8BEC4
extern float g_fScriptTileSize2; // 0x00D8C17C
extern CHAR String[260]; // 0x00D8C1AC
extern void * g_pScriptCurrentBlock; // 0x00D8C2B0
extern void * g_pLoadBuffer; // 0x00D8E468
extern int g_nPtrArray_D8E46C; // 0x00D8E46C
extern void * Block; // 0x00D8E470
extern int g_nPalScript_D8E478; // 0x00D8E478
extern int g_nPalScript_D8E47C; // 0x00D8E47C
extern int g_nPAL3_D8E488; // 0x00D8E488
extern CGameData g_GameData; // 0x00D8E4C0
extern float g_fUIColorParam; // 0x00D91780
extern unsigned char g_bRoleLoadFlags[]; // 0x00D924B4
extern unsigned char g_bGameUpdating; // 0x00D924E8
extern unsigned char g_SceneTransitionBuffer[]; // 0x00D92788
extern int g_gamefrm; // 0x00DB9FD0
extern unsigned char * g_pSceneTransitionBegin; // 0x00DBA014
extern unsigned char * g_pSceneTransitionEnd; // 0x00DBA0AC
extern unsigned int g_dwUISettings; // 0x00DBA250
extern ComposeUI * g_pComposeUI; // 0x00DC0DE8
extern int g_nsub_41FA90_DC10FC; // 0x00DC10FC
extern int g_nMiniGameState; // 0x00DC1100
extern unsigned char g_bStateFlags[]; // 0x00DC3304
extern unsigned char g_bListNeedsRefresh; // 0x00DC3338
extern unsigned char g_bSlotFlag[768]; // 0x00DC3C3C
extern const char * g_szRoleName0; // 0x00DC443C
extern const char * g_szRoleName1; // 0x00DC453C
extern const char * g_szRoleName2; // 0x00DC463C
extern const char * g_szRoleName3; // 0x00DC473C
extern unsigned char g_bSaveFlag; // 0x00DC5F3C
extern const char * g_szSceneName; // 0x00DC6C3C
extern char g_szRoleNameTable[256]; // 0x00DC733C
extern char g_szCombatFieldName; // 0x00DCAE3C
extern unsigned char g_ComposeRecipeTable[]; // 0x00DD003C
extern unsigned char g_SaveSlotFlags[40]; // 0x00DE5220
extern unsigned char g_ArcSceneObjBuffer; // 0x00DE54EF
extern int g_nUILayoutFlags; // 0x00DE5CE4
extern unsigned char g_bRoleFlag1; // 0x00DE5F92
extern unsigned char g_bRoleFlag2; // 0x00DE5F93
extern int g_nActorState; // 0x00DE5F98
extern int g_nActor_DE5F9C; // 0x00DE5F9C
extern int g_nRoleParam; // 0x00DE5FA0
extern int g_nRoleState; // 0x00DE5FA4
extern int g_nActor_DE5FA8; // 0x00DE5FA8
extern unsigned char g_bUIWnd_DE625A; // 0x00DE625A
extern RenderTarget3 g_RenderTarget3; // 0x00DE6CD8
extern unsigned int g_nFileVersion; // 0x00DE7710
extern char g_szParticleTexName[256]; // 0x00DE7714
extern PAL3 g_PAL3; // 0x00DE7AA0
extern int g_nRenderTarget2_DE8DF8; // 0x00DE8DF8
extern int g_nRenderTarget2_DE8DFC; // 0x00DE8DFC
extern int g_nRenderTarget2_DE8E00; // 0x00DE8E00
extern int g_nRenderTarget2_DE8E08; // 0x00DE8E08
extern int g_nRenderTarget2_DE8E10; // 0x00DE8E10
extern int g_nRenderTarget2_DE8E18; // 0x00DE8E18
extern int g_nRenderTarget2_DE8E1C; // 0x00DE8E1C
extern int g_nRenderTarget2_DE8E20; // 0x00DE8E20
extern int g_nRenderTarget2State_DE8E24; // 0x00DE8E24
extern unsigned char g_bCEffCylinderFlag_DE937C; // 0x00DE937C
extern int g_nsub_4C55F0Count_DE9380; // 0x00DE9380
extern unsigned char g_bCEffExplosiveFlag_DE99AC; // 0x00DE99AC
extern int g_nSaveSlot0; // 0x00EC9E70
extern int g_nSaveSlot1; // 0x00EC9E74
extern int g_nSaveSlotBase[]; // 0x00EC9EB4
extern char g_EffTable[370720]; // 0x0174D330
extern int g_nEffTableCount; // 0x0174D334
extern int g_EffTableBase[]; // 0x0174D354
extern int g_nCEffMgr_17A7B50; // 0x017A7B50
extern int g_EffTableEnd; // 0x017A7B74
extern unsigned char g_bgbMatrixStackFlag_17A7B84; // 0x017A7B84
extern int g_nEffectUID; // 0x017A7B88
extern int g_nSceneObjCount; // 0x017A7BC0
extern int g_EffTaskEnd; // 0x017A7C24
extern int g_nScriptCounter; // 0x0017A7E88
extern int g_nEffShockCount; // 0x017A7E88
extern int g_nEffSParticleCount; // 0x017A8118
extern RoleSystem g_RoleSystemCombat; // 0x017A8AE8
extern CCBRoleState * g_pCCBRoleStateArrayEnd; // 0x017A8EF4
extern float g_fCBTimer; // 0x017A9180
extern float pfVal; // 0x017A94E0
extern unsigned char g_CCBStageCamBuffer; // 0x017A94E4
extern int g_nCombatViewMode; // 0x17A990C
extern HWND dwInitParam; // 0x017A9910
extern HWND g_hCombatDlg1; // 0x17A9914
extern HWND g_hCombatDlg2; // 0x17A9918
extern int g_nActorRenderCount; // 0x017A991C
extern HWND g_hCBStageCamDlg; // 0x017A9920
extern unsigned char g_bWPARAM_17A9926; // 0x017A9926
extern int g_nCCBUISelectedRole; // 0x017A993C
extern int g_nCCBUI_17A9940; // 0x017A9940
extern unsigned char g_bCommandEdited; // 0x017A9946
extern unsigned char g_CCBStageState; // 0x017AA870
extern int g_nCBStageFlags[8]; // 0x017AA880
extern int g_nCEffQuadX; // 0x017AA884
extern int g_nCEffQuadY; // 0x017AA888
extern int g_nCEffQuadZ; // 0x017AA890
extern float g_fCEffParam1; // 0x017AA894
extern float g_fCEffParam2; // 0x017AA898
extern int g_nCBRoleAnimData[24]; // 0x017AA8A0
extern int g_nCBQueueHead; // 0x017AA8B0
extern int g_nCombatActionParam; // 0x017AA8B4
extern float g_fCBAnimTime; // 0x017AAD48
extern float g_fCombatHalfParam; // 0x017AAD54
extern unsigned char g_CCBCamControlData; // 0x017AAF64
extern int g_nCBFormation1[12]; // 0x017AB588
extern float g_fCCBStageMoveParam; // 0x017AB598
extern int g_nCEffGridCount; // 0x017AB5A8
extern int g_nCBFormation2[16]; // 0x017AB5E8
extern int g_nCBFormation3[12]; // 0x017AB658
extern int g_nCBRoleIndex; // 0x017AB678
extern int g_nCEffModelX; // 0x017AB67C
extern int g_nCEffModelY; // 0x017AB680
extern int g_nCBFormation4[12]; // 0x017AB6B8
extern int g_nCBTargetIndex; // 0x017AB6D8
extern int g_nCBRoleAttackTable[44]; // 0x017AB6E8
extern int g_nCBActionType; // 0x017AB708
extern int g_nCBDamageValue; // 0x017AB758
extern int g_nCBHealValue; // 0x017AB788
extern int g_nCBRoleMoveTable[24]; // 0x017AB7A8
extern int g_nCBRoleHitTable[18]; // 0x017AB874
extern unsigned char g_bBladeFlags; // 0x017AB8B4
extern float g_fCombatTimer; // 0x017ABCDC
extern unsigned char g_CCBStageSceneData; // 0x017ABF00
extern UINT uType; // 0x017AC5D8
extern unsigned char g_bCBFlag; // 0x017AC5DC
extern float g_fCBDeltaTime; // 0x017AC7DC
extern int g_nCBRoundCount[3]; // 0x017AC7E0
extern float g_fCBSpeed; // 0x017AC7EC
extern unsigned char g_bCBActive; // 0x017AC7F0
extern float g_fCBTimeScale; // 0x017ACA78
extern int g_nCBRolePos[32]; // 0x017ACA80
extern int g_nAIWindowBase; // 0x017ACB88
extern int g_nCCBAIWindow_17ACB8C; // 0x017ACB8C
extern float g_fCBCamParam; // 0x017ACE10
extern int g_nCBCamState[24]; // 0x017ACE14
extern unsigned char g_TempBuffer1024[1024]; // 0x017ACF80
extern int g_nRandCallCount; // 0x017AD310
extern unsigned char g_CCBProtectData[]; // 0x017AD5C4
extern unsigned char g_bgbGeomNodeFlag_17AF5C4; // 0x017AF5C4
extern float g_fSceneScale; // 0x017B02EC
extern char Source[99]; // 0x017B1CC0
extern int g_InputState; // 0x0017B1EC0
extern int g_nCBResultState; // 0x017B30E4
extern CScreenMode g_CScreenMode; // 0x17B41E8
extern BYTE Data; // 0x01894970
extern CHAR Filename[260]; // 0x01894A74
extern int g_nScriptVar; // 0x01894B78
extern gbRenderEffect * g_pRenderEffect_1895048; // 0x01895048
extern gbRenderEffect * g_pRenderEffect_189504C; // 0x0189504C
extern gbRenderEffect * g_pRenderEffect_1895050; // 0x01895050
extern gbRenderEffect * g_pRenderEffect_1895054; // 0x01895054
extern int g_pTexColorEffect; // 0x01895058
extern gbRenderEffect * g_pRenderEffect_189505C; // 0x0189505C
extern gbRenderEffect * g_pRenderEffect_1895060; // 0x01895060
extern gbRenderEffect * g_pRenderEffect_1895064; // 0x01895064
extern gbRenderEffect * g_pRenderEffect_1895068; // 0x01895068
extern int g_nParent_Data_189506C; // 0x0189506C
extern double dbl_1895070; // 0x01895070
extern char * Str; // 0x01895318
extern int g_nScriptState; // 0x0189533C
extern void * lp; // 0x01895388
extern unsigned char g_bEffSystemFlags; // 0x01895560
extern unsigned char g_bScriptFlag; // 0x01895561
extern int g_pCEffMgrBackup; // 0x01895580
extern int g_nCEffect_1895980; // 0x01895980
extern unsigned long g_nRandSeed; // 0x01895984
extern int g_nRandCount; // 0x01895988
extern unsigned char g_bSceneChangeFlags; // 0x0189598D
extern unsigned char g_bStaticInitFlags; // 0x0189598E
extern UINT CodePage; // 0x018969A4
extern int g_nUIState; // 0x01896BE0
extern UINT uNumber; // 0x01896CE0
extern int g_nScriptCounter; // 0x01896D00
extern HANDLE hHeap; // 0x01896D0C
