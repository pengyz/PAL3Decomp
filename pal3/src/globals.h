#pragma once
// PAL3 global variables with known types
// Auto-generated from pipeline/data/annotations/globals.json

#include <windows.h>
#ifndef _PVFV
typedef void (__cdecl *_PVFV)(void);
#endif
class ARC_PlayerAtt;
class Actor;
class Array;
class CCBEditor;
class CCBSystem;
class CCBUI;
class CEffMgr;
class CScreenMode;
class CameraCtrl;
class ComposeUI;
class GRPinput;
class Iostream_init;
class PAL3;
class PAL_GDB;
class PalScript;
class PalScriptMgr;
class RenderTarget2;
class RenderTarget3;
class RoleSystem;
class SceneMgr;
class ScriptCounter;
class ScriptSystemData;
class UIListBox;
class UISceneMap;
class gbActorMgr;
class gbDropGroup;
class gbGfxDriverInfo;
class gbGfxManager;
class gbRenderEffect;
class gbSound2DNode;
class gbVFileSystem;
class gbVolModNode;


// 1972 typed globals

extern float g_fHeuristicScale[8]; // 0x56a5e0
extern unsigned __int8 g_bActorFlag; // 0x56a634
extern const char ArgList[]; // 0x56a660
extern char *const pszAction; // 0x56a7ac
extern const unsigned int dwVal2; // 0x56ab90
extern const LPCSTR nData; // 0x56b460
extern int g_MonsterEntryTable[]; // 0x56c568
extern void * g_ArcSceneMonsterTable; // 0x56c57c
extern void * g_pfnCallback; // 0x56d604
extern void * g_ArcSceneMonsterTable2; // 0x56e15c
extern const CHAR aUiGamemainuiSt[]; // 0x56e718
extern int g_ComposeUIChildIDs[]; // 0x56f02c
extern const int nVal5; // 0x56fbec
extern const LPCSTR lpFileName; // 0x56fc8c
extern int g_nStatePanelL[4]; // 0x56fcc8
extern int g_nStatePanelT[4]; // 0x56fcd8
extern const float formal; // 0x56fd04
extern const float fVal; // 0x56fd0c
extern const int bVisible; // 0x56fdac
extern const int animId; // 0x56fe20
extern int g_nItemTypeBase[4]; // 0x570080
extern int g_nSkillTabIDs[4]; // 0x570090
extern int g_nMagicTabIDs[4]; // 0x5700a0
extern int g_nItemTabIDs[4]; // 0x5700b0
extern int g_nItemIDs_69[5]; // 0x5700c0
extern int g_nSkillItemIDTable[25]; // 0x5700d4
extern int g_nPropIDs_208[5]; // 0x570138
extern int g_nPropIDs_241[11]; // 0x57014c
extern int g_nStatePanelL_dup[4]; // 0x570178
extern int g_nStatePanelT_dup[4]; // 0x570188
extern int g_nSpriteSize_64[5]; // 0x570198
extern int g_nSpriteSize_82[5]; // 0x5701ac
extern int g_nSpriteSize_20[5]; // 0x5701c0
extern int g_nUnkDataTable[30]; // 0x5701d4
extern int g_nUnkTable_24C[7]; // 0x57024c
extern int g_nUnkTable_268[7]; // 0x570268
extern const LPCSTR lpString; // 0x570618
extern const char aPal3logTxt[]; // 0x570a10
extern const char aStringTooLong[]; // 0x570a84
extern const char aInvalidStringP[]; // 0x570ab4
extern const CHAR SubKey[]; // 0x572b3c
extern const CHAR aDisabled3dxpsg[]; // 0x572b68
extern const CHAR aDisablepsgp[]; // 0x572b78
extern const CHAR aD3dxWarnD3dxRe[]; // 0x572cc8
extern const CHAR aD3dxWarnLeastZ[]; // 0x572cf8
extern const CHAR aD3dxWarnAnAllo[]; // 0x572d50
extern const CHAR OutputString[]; // 0x572db0
extern const CHAR ProcName[]; // 0x573268
extern const CHAR ModuleName[]; // 0x573284
extern const char aE000[]; // 0x573290
extern const WCHAR SrcStr; // 0x573388
extern const char aRuntimeErrorPr[]; // 0x5736ac
extern const char aProgramNameUnk[]; // 0x5736cc
extern const CHAR aGetlastactivep[]; // 0x5737a4
extern const CHAR aGetactivewindo[]; // 0x5737b8
extern const CHAR aMessageboxa[]; // 0x5737c8
extern const CHAR LibFileName[]; // 0x5737d4
extern const char a1Qnan[]; // 0x5737e0
extern const char a1Inf[]; // 0x5737e8
extern char a1Ind[]; // 0x5737f0
extern char a1Snan[]; // 0x5737f8
extern const IID riidltf; // 0x573860
extern char ValueName_0[256]; // 0x575098
extern _PVFV First; // 0x5809ec
extern _PVFV Last; // 0x580a00
extern char Format[256]; // 0x580a88
extern char msg[]; // 0x580afc
extern char file[]; // 0x580b1c
extern char aSS[]; // 0x580b54
extern char Mode[3]; // 0x580d00
extern int g_nPAL3_5833B8; // 0x5833b8
extern unsigned int g_dwGameFlags; // 0x5833bc
extern unsigned __int8 g_bFullScreen; // 0x5833c0
extern unsigned __int8 g_bGameFlag2; // 0x5833c2
extern int g_nKeyMap1; // 0x5833c4
extern int g_nKeyMap2; // 0x5833c8
extern int g_nKeyMap3; // 0x5833cc
extern char g_szGamePath[256]; // 0x5833d0
extern char aCouldNotAlloca_0[]; // 0x58378c
extern char aCouldNotAlloca[]; // 0x5837b4
extern char aGameCreateOk[]; // 0x5837e4
extern char aSBulidSS[]; // 0x5837f8
extern char a163941[]; // 0x583814
extern char path[256]; // 0x583820
extern char a03d[]; // 0x583948
extern char aWindowCreateFa[]; // 0x583950
extern CHAR aRate[]; // 0x583968
extern CHAR aDepthbits[]; // 0x583970
extern CHAR aColorbits[]; // 0x58397c
extern CHAR aHeight[]; // 0x583988
extern CHAR aDisplay[]; // 0x583990
extern CHAR section[]; // 0x583998
extern char filename[]; // 0x5839a0
extern char aRegisterclassF[]; // 0x5839ac
extern CHAR WindowName[]; // 0x5839c4
extern CHAR aScursor[]; // 0x5839d8
extern CHAR aMotionblur[]; // 0x5839e0
extern CHAR KeyName[]; // 0x5839ec
extern CHAR aXmusic[]; // 0x5839f4
extern CHAR aXsnd[]; // 0x5839fc
extern CHAR aSoftcursor[]; // 0x583a04
extern CHAR CmdLine[]; // 0x583a10
extern CHAR aMisc[]; // 0x583a14
extern char aS[]; // 0x583a20
extern CHAR aSoftwareSoftst[]; // 0x583a28
extern CHAR aSGameA[]; // 0x583a48
extern CHAR aWriteRegError[]; // 0x583a54
extern CHAR szCaption[]; // 0x583a64
extern char aExceptionInitC[]; // 0x583a78
extern char dir[256]; // 0x583a9c
extern int g_nPtrArray_586154; // 0x586154
extern int g_nFrameRate; // 0x586158
extern int g_nUpdateInterval; // 0x58615c
extern char aUiFlexNote_0[]; // 0x586160
extern char * g_pszDefaultScene; // 0x586180
extern char * g_pszScene1; // 0x586184
extern char * g_pszScene2; // 0x586188
extern void * g_pfnUpdateFuncs[5]; // 0x58618c
extern char aGetmoney[]; // 0x5861a8
extern char aLossmoney[]; // 0x5861b4
extern char name[]; // 0x5861c0
extern char aYlfSS[]; // 0x586218
extern char aHold[]; // 0x588994
extern char aOver[]; // 0x5889bc
extern char pszMsgName[]; // 0x5889c4
extern char aOutdist[]; // 0x5889cc
extern char aRoleSSTga[]; // 0x5889d4
extern char aS4[]; // 0x5889e4
extern char aGetitem[]; // 0x5889ec
extern char aGetexp[]; // 0x5889fc
extern char aS3[]; // 0x588a04
extern char aWeaponSSSTga[]; // 0x588a14
extern char aWeaponSSPol[]; // 0x588a28
extern int g_nCameraUpdateCount; // 0x58b230
extern int g_nRoleSystem_58B234; // 0x58b234
extern float g_fCameraDefaultDist; // 0x58b238
extern char aSndWe022CWav[]; // 0x58b23c
extern char aSndWe021CWav[]; // 0x58b24c
extern char aFreeranges[]; // 0x58b264
extern char aTalkrange[]; // 0x58b37c
extern int g_nRoleSystem_58B38C; // 0x58b38c
extern char aRole[]; // 0x58b44c
extern char aDatascriptScen_0[]; // 0x58b454
extern char nIndex[]; // 0x58b770
extern char aN05[]; // 0x58b77c
extern char aQ02[4]; // 0x58b780
extern char a1n07a[]; // 0x58b784
extern char aM26[]; // 0x58b78c
extern char aSSLgt[]; // 0x58b790
extern char aSSCvd[]; // 0x58b7a8
extern char aSSPol_0[]; // 0x58b7b4
extern char aS1SPol[]; // 0x58b7c0
extern char aSSNav[]; // 0x58b7cc
extern char aXmouse[]; // 0x58b7d8
extern char aSScn[]; // 0x58b7e4
extern float g_fEffectTimer; // 0x58de64
extern char aM02[4]; // 0x58de68
extern char aSSce[]; // 0x58de6c
extern char aQ08p[]; // 0x58de74
extern char aQ08f[]; // 0x58de7c
extern char pszBuf[]; // 0x58de84
extern char aM25[]; // 0x58de88
extern char aM20_0[]; // 0x58de8c
extern char aM19_0[]; // 0x58de90
extern char a4_0[3]; // 0x590538
extern char aObjectS[]; // 0x59053c
extern char aItemSSPol_0[]; // 0x590548
extern char aSS_1[]; // 0x590560
extern char aSndSWav[]; // 0x590568
extern char aLessweight[]; // 0x590574
extern char aM09[]; // 0x59058c
extern char aNothing[]; // 0x590590
extern char aAddluck[]; // 0x590598
extern char aAddspeed[]; // 0x5905a0
extern char pszSceneName[]; // 0x5905ac
extern char aNotmoney[]; // 0x5905b0
extern char aThrow0[]; // 0x5905c4
extern char aThrow100[]; // 0x5905cc
extern char aThrow10[]; // 0x5905d8
extern char aThrow1[]; // 0x5905e0
extern char aChestNotopen[]; // 0x5905e8
extern char aChestFailed[]; // 0x5905f8
extern char aObjectWz20DCvd[]; // 0x590608
extern char aPol[]; // 0x59061c
extern char aCvd[]; // 0x590624
extern char aM22[]; // 0x59062c
extern CHAR a3[]; // 0x590630
extern char aM15[]; // 0x590634
extern CHAR a2[]; // 0x590638
extern char aG01Cvd[]; // 0x59063c
extern char a3_0[]; // 0x590644
extern char aM22_0[]; // 0x590650
extern char pszName2[]; // 0x590654
extern LPCSTR lpDefault; // 0x592d80
extern char aPal3lang[]; // 0x592d84
extern char aBegin[]; // 0x592d9c
extern char aBigmapScriptLo[]; // 0x592da8
extern char aUiBigmapBigmap[]; // 0x592dc4
extern char aSystemScriptLo[]; // 0x592ddc
extern char aInitSce[]; // 0x592df8
extern char aScriptSysInitF[]; // 0x592e04
extern char aDProjectPal3Sc[]; // 0x592e1c
extern char pszFileName[]; // 0x592e44
extern char aSS_5[]; // 0x592e50
extern char aChangqing[]; // 0x592e60
extern char aZixuan[]; // 0x592e6c
extern char aLongkui[]; // 0x592e74
extern char aXuejian[]; // 0x592e7c
extern char aJingtian[]; // 0x592e84
extern char aPal3op[]; // 0x5955dc
extern char a13i2[]; // 0x595960
extern char a14i1[]; // 0x5959d8
extern char a15b1[]; // 0x595a50
extern char a15c1[]; // 0x595a8c
extern char a15h1[]; // 0x595b04
extern char aRemoveteam[]; // 0x5961e0
extern char aAddteam[]; // 0x5961ec
extern char aLoseitem[]; // 0x5961f4
extern char a106[]; // 0x596200
extern char aAddskill[]; // 0x596204
extern char aM08[]; // 0x596210
extern char aD1[]; // 0x596214
extern char aC1[]; // 0x596218
extern char aB1[]; // 0x59621c
extern char aA1[]; // 0x596220
extern char aD_5[]; // 0x596224
extern char aC_0[]; // 0x596228
extern char aB[]; // 0x59622c
extern char aA[]; // 0x596230
extern char aCaptionSTga[]; // 0x596234
extern char aMovieSBik[]; // 0x596244
extern CHAR aEnd[]; // 0x596254
extern CHAR aMovieB[]; // 0x59625c
extern CHAR szSubKey[]; // 0x596264
extern CHAR szValueName[]; // 0x596284
extern CHAR aEffectscn104sT[]; // 0x59628c
extern char pszName[]; // 0x5962a0
extern char aSDTga[]; // 0x5965a4
extern void * pData; // 0x59693c
extern char aDProjectPal3Ui[]; // 0x5971b8
extern CHAR String2[]; // 0x597864
extern const char * g_szDataPath; // 0x5995ac
extern char aDatascriptScen[]; // 0x59b08c
extern char aSSS_0[]; // 0x59b2e8
extern const char * g_pCScreenMode; // 0x59b5e8
extern CHAR aMId[]; // 0x59ba98
extern char aGStory[]; // 0x59dae4
extern char aNSDS_0[]; // 0x59daec
extern char aSec1[]; // 0x59db00
extern char a13i2_0[]; // 0x5a06b0
extern char a14i1_0[]; // 0x5a0728
extern char a15b1_0[]; // 0x5a07a0
extern char a15c1_0[]; // 0x5a07dc
extern char a15h1_0[]; // 0x5a0854
extern unsigned __int8 g_bSceneLoaded; // 0x5a0998
extern float g_fDefaultFOV; // 0x5a099c
extern CHAR aSGameC[]; // 0x5a0d68
extern CHAR aSGameB[]; // 0x5a0d74
extern char aUiEmoteEm02dTg[]; // 0x5a0f80
extern int g_nMiniGameParam; // 0x5a3748
extern char aUiDlgSelbkTga[]; // 0x5a374c
extern char aUiDlgHeadbkTga[]; // 0x5a3760
extern char tex[256]; // 0x5a3774
extern CHAR aUiGameoverDiTg[]; // 0x5a5e20
extern CHAR aUiSceneTimepTg[]; // 0x5a6648
extern CHAR aUiSceneTimebkT[]; // 0x5a665c
extern CHAR aUiSceneTimeclo[]; // 0x5a6670
extern char aUiFlexDlg[]; // 0x5a6698
extern char aSeldlg[]; // 0x5a68b8
extern CHAR aUiSceneFaceHpT[]; // 0x5a8f98
extern CHAR aUiSceneFaceMpT[]; // 0x5a8fb0
extern CHAR aUiSceneFaceBkT[]; // 0x5a8fc8
extern char aUiSceneFaceFac[]; // 0x5a8fe0
extern CHAR aUiSceneMapComp[]; // 0x5ab890
extern CHAR aUiSceneMapBase[]; // 0x5ab8ac
extern char aUiFlexMap[]; // 0x5ab8c4
extern char aP[]; // 0x5aba60
extern unsigned __int8 g_bAudioEnabled; // 0x5ae1e4
extern char aSNSNS[]; // 0x5ae1e8
extern char aSNSNSNS[]; // 0x5ae1f4
extern unsigned __int8 g_bEffectEnabled; // 0x5b0958
extern CHAR aUiGamemainuiSy_3[]; // 0x5b0a88
extern CHAR aUiGamemainuiSy_0[]; // 0x5b0b08
extern CHAR aUiGamemainuiSy[]; // 0x5b0b2c
extern char aUiGamemainuiSy_5[]; // 0x5b0b4c
extern CHAR aUiGamemainuiSy_16[]; // 0x5b0b88
extern char aNS_3[]; // 0x5b0ba4
extern char aNS_0[]; // 0x5b0bac
extern char aSavePal304dJpg[]; // 0x5b0bb8
extern char aSS_4[]; // 0x5b0bcc
extern char aSD[]; // 0x5b0bd4
extern char aS02d02d02d[]; // 0x5b0bdc
extern CHAR aSoftwareSoftst_0[]; // 0x5b0c04
extern CHAR aSeek[]; // 0x5b0c20
extern char a13i2_1[]; // 0x5b1280
extern char a14i1_1[]; // 0x5b12f8
extern char a15b1_1[]; // 0x5b1370
extern char a15c1_1[]; // 0x5b13ac
extern char a15h1_1[]; // 0x5b1424
extern char aMovieSBik_0[]; // 0x5b1a28
extern CHAR aSt_0[]; // 0x5b1a50
extern CHAR aAcptquantum[]; // 0x5b1ce4
extern CHAR aItemId[]; // 0x5b1e6c
extern char aS10[]; // 0x5b1e78
extern char aSD_4[]; // 0x5b1e84
extern char aSD_3[]; // 0x5b1e90
extern char aSD_2[]; // 0x5b1e98
extern char aSD_1[]; // 0x5b1ea0
extern char aSD_0[]; // 0x5b1ea8
extern char aS_1[]; // 0x5b1eb4
extern char aSS_8[]; // 0x5b1eb8
extern const char * g_pCScreenMode_5B46B4; // 0x5b46b4
extern char aItemSSPol[]; // 0x5b7458
extern char aNone[]; // 0x5b7468
extern char aNum1[]; // 0x5b7474
extern char aPrice[]; // 0x5b747c
extern char aName[]; // 0x5b7484
extern char aSSS[]; // 0x5b748c
extern char aNS_4[]; // 0x5b74a8
extern char aSD_10[]; // 0x5b74bc
extern char aItemSSTga[]; // 0x5b74c4
extern void * g_pCombatUIData; // 0x5bc4a8
extern char aSSSS[]; // 0x5bc4ac
extern char aCombatDataCoul[]; // 0x5bc6e0
extern char aDProjectPal3Fi[]; // 0x5bc6fc
extern const char * g_pCScreenMode_5BC918; // 0x5bc918
extern char aSmelt[]; // 0x5bee2c
extern char aBone[]; // 0x5bee34
extern char szFilename[260]; // 0x5bee3c
extern char aSubgameHocksho_1[]; // 0x5c3cf0
extern char aUiFlexNote[]; // 0x5c3d18
extern char aNS_5[]; // 0x5c3d28
extern char aUiGamemainuiJu[]; // 0x5c5414
extern char aUiGamemainuiJu_23[]; // 0x5c5514
extern char aUiGamemainuiJu_22[]; // 0x5c5614
extern char aUiGamemainuiJu_9[]; // 0x5c59d4
extern char aUiGamemainuiJu_4[]; // 0x5c5a78
extern char aUiGamemainuiJu_3[]; // 0x5c5a98
extern char aUiGamemainuiJu_1[]; // 0x5c5adc
extern char a02d02d02d[]; // 0x5c5b20
extern CHAR aUiGamemainuiJu_21[]; // 0x5c5b40
extern CHAR aUiGamemainuiJu_20[]; // 0x5c5b68
extern CHAR aUiGamemainuiJu_19[]; // 0x5c5b94
extern CHAR aUiGamemainuiJu_18[]; // 0x5c5bbc
extern CHAR aUiGamemainuiJu_17[]; // 0x5c5be8
extern CHAR aUiGamemainuiJu_16[]; // 0x5c5c10
extern CHAR aUiGamemainuiJu_15[]; // 0x5c5c3c
extern CHAR aUiGamemainuiJu_14[]; // 0x5c5c64
extern CHAR aUiGamemainuiJu_13[]; // 0x5c5c90
extern CHAR aUiGamemainuiJu_12[]; // 0x5c5cb8
extern CHAR aUiGamemainuiJu_11[]; // 0x5c5ce4
extern CHAR aUiGamemainuiJu_10[]; // 0x5c5d08
extern char aD_4[]; // 0x5c5d30
extern char aSD_8[]; // 0x5c5d38
extern void * fVal2; // 0x5c5ef8
extern char aUiGamemainuiLi_2[]; // 0x5c749c
extern char aUiGamemainuiLi_1[]; // 0x5c74c0
extern CHAR aUiGamemainuiLi_4[]; // 0x5c74dc
extern CHAR aUiGamemainuiLi_3[]; // 0x5c7500
extern char aNS_6[]; // 0x5c7524
extern const char * g_pCScreenMode_5C7768; // 0x5c7768
extern char aDD[]; // 0x5c9114
extern char aNS[]; // 0x5c911c
extern char aSSSN[]; // 0x5c912c
extern char aNNSSSDSN[]; // 0x5c913c
extern char aD_0[]; // 0x5c9154
extern char aNNNS[]; // 0x5c9170
extern char aSDN[]; // 0x5c9184
extern char aPercent[]; // 0x5c9198
extern char aCom3[]; // 0x5c91a0
extern char aCom2[]; // 0x5c91a8
extern char aCom1[]; // 0x5c91b0
extern char aUsetimes[]; // 0x5c91b8
extern char aLv[]; // 0x5c91c4
extern char aNSNS[]; // 0x5c91cc
extern char aNS_2[]; // 0x5c91dc
extern char aD_3[]; // 0x5cac04
extern char aD_2[]; // 0x5cac10
extern char aD_1[]; // 0x5cac20
extern char aSS_6[]; // 0x5cac2c
extern char aNSS[]; // 0x5cc3bc
extern char aNSSSNNS[]; // 0x5cc3c8
extern char aSS_7[]; // 0x5cc3e0
extern unsigned __int8 g_bDebugMode; // 0x5cefa8
extern unsigned __int8 g_bRoleSystem_5CEFA9; // 0x5cefa9
extern char aSNS_0[]; // 0x5cf03c
extern char aSND[]; // 0x5cf048
extern char aSDSDSDSD[]; // 0x5cf054
extern const char * g_pCScreenMode_5CF1E8; // 0x5cf1e8
extern const char * g_pCScreenMode_5CF1F4; // 0x5cf1f4
extern int g_nFiveNimbusCount; // 0x5d0750
extern char aGu[]; // 0x5d0ee8
extern char aSSSS_0[]; // 0x5d0eec
extern char aNNS[]; // 0x5d0f08
extern char aNSNS_0[]; // 0x5d0f18
extern char aSS_3[]; // 0x5d0f28
extern char aSD_5[]; // 0x5d0f34
extern CHAR aN[]; // 0x5d0f44
extern char aSS_2[]; // 0x5d0f48
extern char pszPath[]; // 0x5d0f58
extern char aUiGamemainuiSw[]; // 0x5d0f80
extern CHAR aUiGamemainuiPa_0[]; // 0x5d0fa8
extern CHAR aUiGamemainuiPa_1[]; // 0x5d0fcc
extern char aNNSDNSS[]; // 0x5d0ff0
extern char aQ14[]; // 0x5d1008
extern char aNNS_1[]; // 0x5d100c
extern char aNNS_0[]; // 0x5d1018
extern char aNSNS_1[]; // 0x5d1028
extern CHAR aUiGamemainuiSy_14[]; // 0x5d3700
extern CHAR aUiGamemainuiSy_13[]; // 0x5d3728
extern CHAR aUiGamemainuiSy_12[]; // 0x5d374c
extern CHAR aUiGamemainuiSy_11[]; // 0x5d3778
extern CHAR aUiGamemainuiSy_9[]; // 0x5d37bc
extern CHAR aUiGamemainuiSy_7[]; // 0x5d37f8
extern CHAR aUiGamemainuiSy_19[]; // 0x5d3834
extern CHAR aM05[4]; // 0x5d3850
extern CHAR aM04[4]; // 0x5d3854
extern char aDS_1[]; // 0x5d3858
extern int g_nTextureDefault; // 0x5d41b0
extern float g_fConst400; // 0x5d41b4
extern float g_fRenderHeight; // 0x5d41b8
extern float g_fRenderWidth; // 0x5d41bc
extern CHAR aNotSupportedFi[]; // 0x5d4214
extern CHAR aInfo[]; // 0x5d4230
extern CHAR Text[]; // 0x5d4238
extern CHAR Caption[]; // 0x5d4254
extern char aLockBackBuffer[]; // 0x5d4530
extern char aDProjectPal3Ef[]; // 0x5d454c
extern int g_EffCylinderEditorData; // 0x5d4d3c
extern const char * g_pszEditorDesc; // 0x5d4d7c
extern int g_EffEditorState; // 0x5d4df4
extern char aS03d[]; // 0x5d4e54
extern char aS03dBik[]; // 0x5d4ebc
extern char aNewFailInCeffc[]; // 0x5d4f84
extern char aDProjectPal3Co[]; // 0x5d4fa8
extern char aCNewFailed_0[]; // 0x5d50f4
extern char aDProjectPal3Ef_0[]; // 0x5d5104
extern char aNewFailInCeffe[]; // 0x5d5158
extern char aDProjectPal3Co_13[]; // 0x5d517c
extern char aNewFailInCeffg[]; // 0x5d5234
extern char aDProjectPal3Co_14[]; // 0x5d5254
extern char aNewFailInCeffm[]; // 0x5d52d0
extern char aDProjectPal3Co_0[]; // 0x5d52f0
extern char aCouldNotMalloc_1[]; // 0x5d5394
extern char aCouldNotMalloc_0[]; // 0x5d53c0
extern char aCouldNotMalloc[]; // 0x5d53e8
extern char aFewOfNodeInMet[]; // 0x5d5410
extern int g_TargetData; // 0x5d542c
extern CEffMgr g_EffMgr; // 0x5d5484
extern RenderTarget2 pTarget; // 0x5d548c
extern unsigned int dwVal; // 0x5d87f4
extern unsigned int index; // 0x5d8804
extern const CHAR aDatascriptComb[]; // 0x5d880c
extern const char aPal3CombatSyst[]; // 0x5d8824
extern const char aSpeed12f[]; // 0x5d883c
extern CCBUI * ppUI; // 0x5d8864
extern const char aStopped[]; // 0x5d8890
extern const char a03d03d[]; // 0x5d8898
extern const char aSBuildSSReleas[]; // 0x5d88a4
extern const char a164229[]; // 0x5d88bc
extern const CHAR aBasedataCbscen[]; // 0x5d8924
extern const char a03dS[]; // 0x5d8968
extern const char aY[]; // 0x5d8970
extern const char a15f[]; // 0x5d89b4
extern const char aLu[]; // 0x5d89bc
extern const char aSmp[]; // 0x5d89c0
extern const char aSgp[]; // 0x5d89c8
extern const char aShp[]; // 0x5d89d0
extern const char aSid[]; // 0x5d89d8
extern const CHAR aItem[]; // 0x5d89e0
extern const CHAR aNewitem[]; // 0x5d89e8
extern const char aDS[]; // 0x5d8a10
extern const CHAR aWarning[]; // 0x5d8aac
extern const char a12f[]; // 0x5d8acc
extern const char aEmpty[]; // 0x5d8b70
extern const char a02f[]; // 0x5d8b78
extern const char aO[]; // 0x5d8b84
extern const char aDatascriptComb_0[]; // 0x5d8e00
extern char aLevel[6]; // 0x5d8e18
extern char aFailToCreateWe[29]; // 0x5d8e50
extern char aDProjectPal3Co_1[39]; // 0x5d8e70
extern const char aGpfullD[]; // 0x5d8fa0
extern const char aSsleepD[]; // 0x5d8fac
extern const char aPoisonD[]; // 0x5d8fb8
extern const char aShplowD[]; // 0x5d8fc4
extern const char aDyingD[]; // 0x5d8fd0
extern const char aSCombatdialog[]; // 0x5d8fd8
extern char aZ39[4]; // 0x5d8fe8
extern const char a2d[]; // 0x5d8fec
extern const char aD02d[]; // 0x5d8ff0
extern char aNewFailedAtCre[39]; // 0x5db678
extern char aDProjectPal3Co_2[35]; // 0x5db6a0
extern char aEnemysneakatta[19]; // 0x5db708
extern char aWesneakattacke[19]; // 0x5db71c
extern const char aSD_6[]; // 0x5db730
extern char aWitch[6]; // 0x5db738
extern char aMoney[6]; // 0x5db740
extern char aFleefail[9]; // 0x5db758
extern const char aSSDS[]; // 0x5db778
extern char aLevelup[8]; // 0x5db784
extern const char aSSD[]; // 0x5db78c
extern const char aSDS_0[]; // 0x5db798
extern char aGetitem_0[8]; // 0x5db7a4
extern const char aSSS_1[]; // 0x5db7b4
extern char aMastered[9]; // 0x5db7bc
extern const char aSSSDS[]; // 0x5db7c8
extern const char aUiCombatPointe[]; // 0x5db7d8
extern const char aCbdataFlexcamD[]; // 0x5db7f8
extern const char aDatascriptCbca[]; // 0x5db80c
extern const char aRoll[]; // 0x5db9a0
extern const char aPitch[]; // 0x5db9a8
extern const char aYaw[]; // 0x5db9b0
extern const char aZ[]; // 0x5db9b4
extern const char aY_0[]; // 0x5db9b8
extern const char aEditorcamD[]; // 0x5db9bc
extern char aCamFovF[]; // 0x5db9c8
extern char aCamYawFPitchFR[]; // 0x5db9d4
extern char aCamXFYFZF[]; // 0x5db9f4
extern char aCouldnTOpenCbC[35]; // 0x5dba0c
extern char aDProjectPal3Co_3[38]; // 0x5dba30
extern const char aBasedataCbdata[]; // 0x5dba58
extern const char aGfxscriptGeomD_0[]; // 0x5dbbf0
extern const char aGfxscriptGeomD[]; // 0x5dbc10
extern char aCouldnTOpenEff[38]; // 0x5dbc2c
extern char aDProjectPal3Co_4[41]; // 0x5dbc54
extern const char aCbdataEfflinke[]; // 0x5dbc80
extern char aCouldnTOpenCbE[33]; // 0x5dbc98
extern const char aFlydown[]; // 0x5dbe48
extern const char aFlyup[]; // 0x5dbe50
extern const char aStore[]; // 0x5dbe58
extern const char aPause[]; // 0x5dbe60
extern const char aWork1[]; // 0x5dbe68
extern const char aWork[]; // 0x5dbe70
extern char aDProjectPal3Co_5[39]; // 0x5dbe78
extern const char a203[]; // 0x5dbea0
extern const char aRoleSSIni[]; // 0x5dbea4
extern char aWe011b[7]; // 0x5dbeb4
extern char aWe011[6]; // 0x5dbebc
extern const char aZ02d[]; // 0x5dbec4
extern char aWe014[6]; // 0x5dbecc
extern char aWe013[6]; // 0x5dbed4
extern char aWe012[6]; // 0x5dbedc
extern const char aWd[]; // 0x5dbee4
extern const char aWe[]; // 0x5dbf30
extern char aCouldnTCreateT[52]; // 0x5dbf54
extern char aDProjectPal3Co_6[40]; // 0x5dbf88
extern const char aGfxscriptAddit_1[]; // 0x5dbfe8
extern const char aItemSSSTga[]; // 0x5dc004
extern const char aDS_0[]; // 0x5dc018
extern const char aCbsceneSSLgt[]; // 0x5dc020
extern const char aCbsceneSSCvd[]; // 0x5dc034
extern const char aCbsceneSSPol[]; // 0x5dc048
extern const char aCbscene[]; // 0x5dc05c
extern const char aRoleDZ[]; // 0x5dc068
extern const char aRoleDX[]; // 0x5dc074
extern const char aRolepos[]; // 0x5dc080
extern const char aRadius[]; // 0x5dc0a4
extern char aDProjectPal3Co_7[41]; // 0x5dc228
extern int nVal3; // 0x5dc3dc
extern char aDProjectPal3Co_8[36]; // 0x5de8fc
extern char aRoleDXFZFRotF[]; // 0x5de920
extern char aEffectTimerF[]; // 0x5de93c
extern char aEffectObjectsD[]; // 0x5de94c
extern char aDeltatimeF[]; // 0x5de960
extern char aTimefundF[]; // 0x5de970
extern char aTimesOfCombatD[]; // 0x5de97c
extern char aThreadDStageta[]; // 0x5de990
extern const char aS_2[]; // 0x5de9a8
extern const char aTooManyCharact[]; // 0x5de9bc
extern const char aUiCombatContro_6[]; // 0x5deff0
extern const char aUiCombatContro_5[]; // 0x5df02c
extern const char aUiCombatContro_4[]; // 0x5df060
extern const char aUiCombatContro_7[]; // 0x5df094
extern const char aUiCombatContro_3[]; // 0x5df0d0
extern const char aUiCombatContro_2[]; // 0x5df124
extern const char aUiCombatContro_1[]; // 0x5df158
extern const char aUiCombatContro_0[]; // 0x5df190
extern const char aUiCombatContro[]; // 0x5df1c8
extern char aDProjectPal3Co_9[32]; // 0x5dfd6c
extern const char aWt[]; // 0x5dfe04
extern const char aRb[]; // 0x5dfe08
extern const char aNSSS[]; // 0x5e24d4
extern const char aNSS_0[]; // 0x5e24e4
extern const char aNSS_1[]; // 0x5e24f8
extern const char aNSDS[]; // 0x5e2510
extern char aHockshopGut[13]; // 0x5e50c0
extern char aSubgameHocksho[]; // 0x5e6d84
extern char aSubgameApprais_17[]; // 0x5e9018
extern CHAR aUiGamemainuiPa_2[]; // 0x5e9040
extern char pszTexBase[]; // 0x5e9068
extern char aSSPol[]; // 0x5e9084
extern char aNNSNN[]; // 0x5e909c
extern char aNNSS[]; // 0x5e90b4
extern char aNNSDNSDNSDN[]; // 0x5e90cc
extern char aNS_7[]; // 0x5eb794
extern char aSubgameApprais[]; // 0x5ecf20
extern char aSNSN[]; // 0x5ecf48
extern char aSD_7[]; // 0x5ef66c
extern char aNNSDSNSD[]; // 0x5ef674
extern char aDProjectPal3Su[]; // 0x5ef88c
extern char aSubgameEncampm[]; // 0x5ef8c4
extern char aSubgameEncampm_3[]; // 0x5efb20
extern char pszModelName[]; // 0x5efbd0
extern char aSubgameEncampm_5[]; // 0x5f2424
extern char aSSSD[]; // 0x5f2444
extern char aNSS10[]; // 0x5f245c
extern char aNSS_2[]; // 0x5f2474
extern char aFFF[]; // 0x5f248c
extern char aSUd[]; // 0x5f24b8
extern char aR[]; // 0x5f24cc
extern char aSSDPol[]; // 0x5f4d28
extern char aBasedataSkeePa[]; // 0x5f4d34
extern char aObstruct[]; // 0x5f4d80
extern char pszFilename[]; // 0x5f4f08
extern LPCSTR lpString2; // 0x5f50b8
extern char aSubgameApprais_0[]; // 0x5f9cb4
extern CHAR aN_0[]; // 0x5f9cd4
extern char aNSSNNS[]; // 0x5f9ce0
extern char aNSD[]; // 0x5f9cf8
extern char aNSSNNSN[]; // 0x5f9d0c
extern char pszModel1[]; // 0x5feab4
extern CHAR a1[2]; // 0x601138
extern char PathName_0[256]; // 0x601528
extern char aSNS[]; // 0x6039cc
extern char aRoleS02dIni[]; // 0x6039fc
extern char aSavePal02dArc[]; // 0x606088
extern CHAR PathName[]; // 0x60609c
extern char aConsoleErrorCo[]; // 0x6088dc
extern char aBadCommandOrFi[]; // 0x608900
extern char aSD_9[]; // 0x60891c
extern char aFv[]; // 0x60892c
extern char desc[]; // 0x608944
extern char aExceptionS[]; // 0x60895c
extern char aSDS[]; // 0x608970
extern char aSDSS[]; // 0x60897c
extern char aLogAtS[]; // 0x60898c
extern char aS_0[]; // 0x608998
extern char aSLogAt[]; // 0x6089a4
extern char aEnginelogTxt[]; // 0x6089b0
extern char aAt[]; // 0x6089c0
extern char aDatascriptMusi[]; // 0x608af4
extern char aMusicSMp3[]; // 0x608b0c
extern char aScene[]; // 0x608b1c
extern char aCombat[]; // 0x608b24
extern char aLuLuMp3[]; // 0x608b2c
extern LPCSTR lpString1; // 0x608b3c
extern CHAR aTName[]; // 0x608b40
extern CHAR aEndKey[]; // 0x608ca0
extern CHAR aEndfile[]; // 0x608ca8
extern char Delimiter[256]; // 0x608cb4
extern char aC[]; // 0x608fc0
extern CHAR aPal3Exception[]; // 0x608fc8
extern CHAR aPal3[]; // 0x608fdc
extern char aPleaseInsertDi[]; // 0x608fe4
extern char aSmovie[]; // 0x609008
extern CHAR aSoftwareSoftst_1[]; // 0x609010
extern CHAR ValueName[]; // 0x609028
extern int g_TileData[]; // 0x60ad00
extern unsigned __int16 __ctype[]; // 0x60ad08
extern size_t cbMultiByte; // 0x60af0c
extern void * jpt_55C6DD; // 0x60b76e
extern gbVFileSystem * g_VFileSystem; // 0x6ebfa0
extern gbVFileSystem * g_BaseVFileSystem; // 0x7cc178
extern int g_nSaveDataSize; // 0x8834c0
extern float g_fPAL3Timer; // 0x8acbec
extern PAL3 g_PAL3_Instance; // 0x8acbf0
extern int g_nLoadBufferSize; // 0x8ddce0
extern _WORD p_WORD; // 0x971a74
extern PAL_GDB * g_pGDB; // 0x975ed8
extern unsigned __int8 g_UITemplateData[]; // 0xa00000
extern int g_nRenderFlags; // 0xa3a6ec
extern int g_nRenderMode; // 0xa3a6f0
extern gbVolModNode * g_pVolModNode; // 0xa3a6f8
extern CScreenMode g_ScreenMode; // 0xa3a7d8
extern ARC_PlayerAtt g_PlayerAttBuffer; // 0xaa0b00
extern unsigned __int8 g_PalScriptTemplate[]; // 0xaabef6
extern ARC_PlayerAtt g_PlayerAttBuffer2; // 0xabcd00
extern int g_ScriptSlots[132]; // 0xbfab60
extern GRPinput g_Input; // 0xbfad70
extern gbGfxDriverInfo g_DrvInfo; // 0xbfd6c8
extern int g_nGameTime; // 0xbfda04
extern int g_nTickCount; // 0xbfda2c
extern float g_fDeltaTime; // 0xbfda30
extern float g_fGameSpeed; // 0xbfda34
extern gbDropGroup * g_pDropGroup; // 0xbfda38
extern int g_nPAL3_BFDA3C; // 0xbfda3c
extern int g_nWolfIndex; // 0xbfda44
extern HINSTANCE hInstance; // 0xbfda48
extern HWND hWnd; // 0xbfda4c
extern HWND hDlg; // 0xbfda50
extern HWND g_hMainWnd; // 0xbfda54
extern float g_fFadeAngle; // 0xbfda58
extern float g_fTimeScale; // 0xbfda5c
extern gbGfxManager * gfxMgr; // 0xbfda60
extern gbActorMgr * g_pActorMgr; // 0xbfda64
extern CameraCtrl * g_pCameraCtrl; // 0xbfda68
extern int g_nSceneState; // 0xbfda6c
extern void * g_pEffectSystem; // 0xbfda70
extern CCBSystem * g_pCBSystem; // 0xbfda74
extern void * g_pSceneManager; // 0xbfda78
extern void * g_pMiniGame2; // 0xbfda7c
extern void * g_pMiniGame1; // 0xbfda80
extern void * g_pMiniGame3; // 0xbfda84
extern unsigned __int8 g_bSceneLoaded_0; // 0xbfda88
extern int g_nCombatMode; // 0xbfda8c
extern unsigned __int8 g_bTestCombat; // 0xbfda90
extern unsigned __int8 g_bPAL3_BFDA91; // 0xbfda91
extern HCURSOR g_hCursor; // 0xbfda94
extern int g_bEditorMode; // 0xbfda98
extern float g_fGameTimer; // 0xbfdaa0
extern CHAR Default[8]; // 0xbfdaa4
extern int g_nMagicSlotCountA; // 0xbfdb70
extern int g_nMagicSlotCountB; // 0xbfdb74
extern void ** g_pScriptObjArray; // 0xbfdb80
extern void * g_pScriptEventObj; // 0xbfdb84
extern int g_nScriptEventParam; // 0xbfdb90
extern float g_fScriptEventParam2; // 0xbfdb94
extern int g_nScriptRolePosX; // 0xbfdb98
extern int g_nScriptRolePosY; // 0xbfdb9c
extern int g_nScriptRolePosZ; // 0xbfdba0
extern unsigned int g_nCurrentEventId; // 0xbfdba4
extern int g_nActor_BFDBA8; // 0xbfdba8
extern int g_nActor_BFDBAC; // 0xbfdbac
extern RoleSystem g_RoleSystemExtra0; // 0xbfdbb0
extern RoleSystem g_RoleSystemExtra1; // 0xbffdb0
extern float g_fCamRoleParams[40]; // 0xc01fb0
extern ScriptCounter g_ScriptCounters[10]; // 0xc02050
extern unsigned __int8 g_ScriptCountersEnd; // 0xc020f0
extern RoleSystem g_RoleSystemMain; // 0xc020f8
extern float g_fScriptTimeAccum; // 0xc042e8
extern int g_nPtrArray_C04300; // 0xc04300
extern int g_nRoleInitLevel[6]; // 0xc04334
extern Array g_SceneMgrPrefix; // 0xc04350
extern Array g_RoleTeamArray; // 0xc04360
extern Array g_nSceneFlags; // 0xc04370
extern Array g_SceneArray; // 0xc04380
extern SceneMgr g_SceneMgr; // 0xc04390
extern RoleSystem Buffer; // 0xc043a0
extern int nVal2; // 0xc05698
extern float fDeltaTime; // 0xc0a350
extern Iostream_init g_pScriptArrayEnd; // 0xc10960
extern PalScript * g_pScriptArrayEnd2; // 0xc1096c
extern RoleSystem * g_pRoleSystemArrayEnd; // 0xc10a0e
extern PalScript * g_pCurrentScript; // 0xc10cbc
extern unsigned __int8 g_bFormationReady; // 0xc10cc0
extern unsigned __int8 g_nSceneTransitionParam2; // 0xc10cc1
extern int g_nCurrentRoleSlot; // 0xc10cc8
extern int nVal; // 0xc10ccc
extern float g_fFadeTimer; // 0xc10cd0
extern char g_szSceneUIText[256]; // 0xc10d38
extern float g_fSceneTileSize; // 0xc1109c
extern gbSound2DNode * g_pBGMTable[24]; // 0xc11360
extern gbSound2DNode * g_pAmbientTable[24]; // 0xc113c0
extern struct tagPOINT pPos; // 0xc11430
extern float g_fTileSize; // 0xc116c4
extern unsigned __int8 m_bPathEnabled; // 0xc116ea
extern RoleSystem * g_pRoleSystem; // 0xc116ec
extern gbSound2DNode * g_pCurrentBGM; // 0xc116f4
extern float g_fCameraBlendWeight; // 0xc116f8
extern int g_nPartyRoles[6]; // 0xc11700
extern int g_nPartyCount; // 0xc11718
extern float g_fTileScale; // 0xc12b14
extern int g_nLastUpdateTime; // 0xc12b1c
extern unsigned int g_lastupdateloading; // 0xc12b20
extern float g_fPalScript_C12B28; // 0xc12b28
extern float g_fPalScript_C12B2C; // 0xc12b2c
extern float g_fPalScript_C12B30; // 0xc12b30
extern int g_nunknown_libname_331_C12B38; // 0xc12b38
extern int g_nunknown_libname_331_C12B3C; // 0xc12b3c
extern int g_nunknown_libname_331_C12B40; // 0xc12b40
extern RoleSystem g_RoleSystemInstance; // 0xc12b48
extern PalScriptMgr pOut; // 0xc21fe8
extern ScriptSystemData g_ScriptSystemData; // 0xd8b318
extern double thisa; // 0xd92780
extern _BYTE p_BYTE; // 0xd92784
extern unsigned __int8 pCmd[]; // 0xd92788
extern int g_gamefrm; // 0xdb9fd0
extern unsigned __int8 * g_pSceneTransitionBegin; // 0xdba014
extern unsigned __int8 * g_pSceneTransitionEnd; // 0xdba0ac
extern unsigned int g_dwUISettings; // 0xdba250
extern UIListBox g_UIListBoxDlg; // 0xdba260
extern UISceneMap g_UISceneMapDlg; // 0xdbaf10
extern CCBEditor g_CCBEditorInst; // 0xdbb364
extern ComposeUI * g_pComposeUI; // 0xdc0de8
extern int g_nsub_41FA90_DC10FC; // 0xdc10fc
extern int g_nMiniGameState; // 0xdc1100
extern unsigned __int8 g_bStateFlags[]; // 0xdc3304
extern unsigned __int8 g_bListNeedsRefresh; // 0xdc3338
extern CHAR Destination[256]; // 0xdc333c
extern unsigned __int8 g_bSlotFlag[768]; // 0xdc3c3c
extern const char * g_szRoleName0; // 0xdc443c
extern const char * g_szRoleName1; // 0xdc453c
extern const char * g_szRoleName2; // 0xdc463c
extern const char * g_szRoleName3; // 0xdc473c
extern unsigned __int8 g_bSaveFlag; // 0xdc5f3c
extern const char * g_szSceneName; // 0xdc6c3c
extern char g_szRoleNameTable[256]; // 0xdc733c
extern char g_szCombatFieldName[]; // 0xdcae3c
extern char szText[]; // 0xdcd43c
extern unsigned __int8 g_ComposeRecipeTable[]; // 0xdd003c
extern CHAR String1; // 0xde333c
extern unsigned __int8 g_SaveSlotFlags[40]; // 0xde5220
extern unsigned __int8 g_ArcSceneObjBuffer; // 0xde54ef
extern int g_nUILayoutFlags; // 0xde5ce4
extern unsigned __int8 g_bRoleFlag1; // 0xde5f92
extern unsigned __int8 g_bRoleFlag2; // 0xde5f93
extern int g_nActorState; // 0xde5f98
extern int g_nActor_DE5F9C; // 0xde5f9c
extern int g_nRoleParam; // 0xde5fa0
extern int g_nRoleState; // 0xde5fa4
extern int g_nActor_DE5FA8; // 0xde5fa8
extern unsigned __int8 g_bUIWnd_DE625A; // 0xde625a
extern RenderTarget3 g_RenderTarget3; // 0xde6cd8
extern unsigned int g_nFileVersion; // 0xde7710
extern char g_szParticleTexName[256]; // 0xde7714
extern PAL3 g_PAL3; // 0xde7aa0
extern int g_nSaveSlot0; // 0xec9e70
extern int g_nSaveSlot1; // 0xec9e74
extern int g_nSaveSlotBase[]; // 0xec9eb4
extern char g_EffTable[370720]; // 0x174d330
extern int g_nCEffMgr_17A7B50; // 0x17a7b50
extern int g_EffTableEnd; // 0x17a7b74
extern unsigned __int8 g_bgbMatrixStackFlag_17A7B84; // 0x17a7b84
extern int g_nEffectUID; // 0x17a7b88
extern int g_nSceneObjCount; // 0x17a7bc0
extern int g_EffTaskEnd; // 0x17a7c24
extern int g_nEffShockCount; // 0x17a7e88
extern int g_nEffSParticleCount; // 0x17a8118
extern RoleSystem g_RoleSystemCombat; // 0x17a8ae8
extern unsigned __int8 g_CCBStageState; // 0x17aa870
extern int g_nCBStageFlags[8]; // 0x17aa880
extern int g_nCBRoleAnimData[24]; // 0x17aa8a0
extern int pnVal; // 0x17aa910
extern int fBladeTime; // 0x17aad3c
extern float g_fCBAnimTime; // 0x17aad48
extern float g_fCombatHalfParam; // 0x17aad54
extern unsigned __int8 g_CCBCamControlData; // 0x17aaf64
extern int g_nCBFormation1[12]; // 0x17ab588
extern int g_nCBFormation2[16]; // 0x17ab5e8
extern int g_nCBFormation3[12]; // 0x17ab658
extern int g_nCBFormation4[12]; // 0x17ab6b8
extern int g_nCBRoleAttackTable[44]; // 0x17ab6e8
extern int g_nCBRoleMoveTable[24]; // 0x17ab7a8
extern int g_nCBRoleHitTable[18]; // 0x17ab874
extern float g_fCombatTimer; // 0x17abcdc
extern unsigned __int8 g_CCBStageSceneData; // 0x17abf00
extern UINT uType; // 0x17ac5d8
extern unsigned __int8 g_bCBFlag; // 0x17ac5dc
extern float g_fCBDeltaTime; // 0x17ac7dc
extern int g_nCBRoundCount[3]; // 0x17ac7e0
extern float g_fCBSpeed; // 0x17ac7ec
extern unsigned __int8 g_bCBActive; // 0x17ac7f0
extern float g_fCBTimeScale; // 0x17aca78
extern int g_nCBRolePos[32]; // 0x17aca80
extern int g_nAIWindowBase; // 0x17acb88
extern int g_nCCBAIWindow_17ACB8C; // 0x17acb8c
extern float g_fCBCamParam; // 0x17ace10
extern int g_nCBCamState[24]; // 0x17ace14
extern unsigned __int8 g_TempBuffer1024[1024]; // 0x17acf80
extern unsigned __int8 g_CCBProtectData[]; // 0x17ad5c4
extern unsigned __int8 g_bgbGeomNodeFlag_17AF5C4; // 0x17af5c4
extern float g_fSceneScale; // 0x17b02ec
extern Actor g_ActorSaveData; // 0x17b1550
extern char Source[99]; // 0x17b1cc0
extern int g_InputState; // 0x17b1ec0
extern int g_nCBResultState; // 0x17b30e4
extern CScreenMode g_CScreenMode; // 0x17b41e8
extern BYTE Data; // 0x1894970
extern CHAR Filename[260]; // 0x1894a74
extern gbRenderEffect * g_pRenderEffect_1895048; // 0x1895048
extern gbRenderEffect * g_pRenderEffect_189504C; // 0x189504c
extern gbRenderEffect * g_pRenderEffect_1895050; // 0x1895050
extern gbRenderEffect * g_pRenderEffect_1895054; // 0x1895054
extern int g_pTexColorEffect; // 0x1895058
extern gbRenderEffect * g_pRenderEffect_189505C; // 0x189505c
extern gbRenderEffect * g_pRenderEffect_1895060; // 0x1895060
extern gbRenderEffect * g_pRenderEffect_1895064; // 0x1895064
extern gbRenderEffect * g_pRenderEffect_1895068; // 0x1895068
extern int g_nParent_Data_189506C; // 0x189506c
extern double dbl_1895070; // 0x1895070
extern char * Str; // 0x1895318
extern int g_nScriptState; // 0x189533c
extern void * lp; // 0x1895388
extern LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter; // 0x1895398
extern unsigned __int8 g_bEffSystemFlags; // 0x1895560
extern unsigned __int8 g_bScriptFlag; // 0x1895561
extern int g_pCEffMgrBackup; // 0x1895580
extern int g_nCEffect_1895980; // 0x1895980
extern unsigned int g_nRandSeed; // 0x1895984
extern int g_nRandCount; // 0x1895988
extern unsigned __int8 g_bSceneChangeFlags; // 0x189598d
extern unsigned __int8 g_bStaticInitFlags; // 0x189598e
extern size_t Count; // 0x18969a0
extern UINT CodePage; // 0x18969a4
extern LCID Locale; // 0x1896bc4
extern int g_nUIState; // 0x1896be0
extern UINT uNumber; // 0x1896ce0
extern void * Block; // 0x1896cf0
extern int g_nScriptCounter; // 0x1896d00
extern LPVOID lpMem; // 0x1896d08
extern HANDLE hHeap; // 0x1896d0c
