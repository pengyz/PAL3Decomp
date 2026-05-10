#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PAL3.h"
#include "pal3/gen/Array.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/CRenderTarget.h"
#include "pal3/gen/CRenderTarget2.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/Camera.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/CameraSystem.h"
#include "pal3/gen/Config.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/MiniGame1.h"
#include "pal3/gen/MiniGame3.h"
#include "pal3/gen/MvcViewport.h"
#include "pal3/gen/NPC.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/Parent_Data.h"
#include "pal3/gen/RenderTarget.h"
#include "pal3/gen/RenderTarget2.h"
#include "pal3/gen/RenderTarget3.h"
#include "pal3/gen/RenderTarget4.h"
#include "pal3/gen/Role.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/Scene.h"
#include "pal3/gen/SceneMgr.h"
#include "pal3/gen/SceneObj.h"
#include "pal3/gen/ScreenEffectMgr.h"
#include "pal3/gen/ScriptSystem.h"
#include "pal3/gen/SoundContext.h"
#include "pal3/gen/SoundSystem.h"
#include "pal3/gen/UIManager.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/UIQuadManager.h"
#include "pal3/gen/UIRenderObj.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UISystem.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_4070A0(...);
int sub_410430(...);
int sub_419AE0(...);
int sub_41BE80(...);
int sub_41D100(...);
int sub_426E80(...);
int sub_42BEF0(...);
int sub_431C10(...);
int sub_4C5820(...);
int sub_4C5840(...);
int sub_4C58C0(...);
int sub_52F2E0(...);
int sub_53E680(...);
int sub_569020(...);

// Unnamed globals (extern)
extern char aAppname[];
extern char aCNewFailed[];
extern char aColorbits[];
extern char aConfigIni[];
extern char aCouldNotAlloca[];
extern char aCouldNotAlloca_0[];
extern char aCouldnTMallocM[];
extern char aCreateActorman[];
extern char aCreateGfxManag[];
extern char aDProjectPal3Ga_0[];
extern char aDatascriptLang[];
extern char aDefault[];
extern char aDepthbits[];
extern char aDisplay[];
extern char aEffectSnowTga[];
extern char aFightDatabaseL[];
extern char aGameCreateOk[];
extern char aHeight[];
extern char aInputDeviceCre[];
extern char aJan52004[];
extern char aMisc[];
extern char aMotionblur[];
extern char aMovieLogoBik[];
extern char aObjectG02Cvd[];
extern char aObjectG03Cvd[];
extern char aRate[];
extern char aRegisterclassF[];
extern char aSGameA[];
extern char aScursor[];
extern char aSoftcursor[];
extern char aSoftwareSoftst[];
extern char aSync[];
extern char aUiFlexNote_0[];
extern char aUiSceneTiao[];
extern char aV104[];
extern char aWindowCreateFa[];
extern char aXmusic[];
extern char aXsnd[];
extern unsigned char byte_5833C0;
extern unsigned char byte_5833D0;
extern unsigned char byte_BFFE5E;
extern unsigned char byte_C020F0;
extern unsigned char byte_C021A4;
extern unsigned char byte_C021A5;
extern unsigned char byte_C021A6;
extern unsigned char byte_D8C339;
extern unsigned char byte_D924E8;
extern unsigned char byte_DE5220;
extern int dword_5833C4;
extern int dword_5833C8;
extern int dword_5833CC;
extern int dword_586158;
extern int dword_58618C;
extern int dword_586190;
extern int dword_586194;
extern int dword_586198;
extern int dword_58619C;
extern int dword_BFE0A0;
extern int dword_BFFDB0;
extern int dword_C00028;
extern int dword_C002A0;
extern int dword_C01FB0;
extern int dword_C01FB4;
extern int dword_C01FB8;
extern int dword_C01FBC;
extern int dword_C01FC0;
extern int dword_C01FC4;
extern int dword_C01FC8;
extern int dword_C01FCC;
extern int dword_C01FD0;
extern int dword_C01FD4;
extern int dword_C01FD8;
extern int dword_C01FDC;
extern int dword_C01FE0;
extern int dword_C01FE4;
extern int dword_C01FE8;
extern int dword_C01FEC;
extern int dword_C01FF0;
extern int dword_C01FF4;
extern int dword_C01FF8;
extern int dword_C01FFC;
extern int dword_C02000;
extern int dword_C02004;
extern int dword_C02008;
extern int dword_C0200C;
extern int dword_C02010;
extern int dword_C02014;
extern int dword_C02018;
extern int dword_C0201C;
extern int dword_C02028;
extern int dword_C0202C;
extern int dword_C02030;
extern int dword_C02034;
extern int dword_C02038;
extern int dword_C0203C;
extern int dword_C02040;
extern int dword_C02044;
extern int dword_C02048;
extern int dword_C0204C;
extern int dword_C02050;
extern int dword_C02060;
extern int dword_C02070;
extern int dword_C02080;
extern int dword_C0209C;
extern int dword_C020AC;
extern int dword_C020BC;
extern int dword_C020CC;
extern int dword_C020DC;
extern int dword_C020EC;
extern int dword_C020F8;
extern int dword_C02370;
extern int dword_C02374;
extern int dword_C025E8;
extern int dword_C042F8;
extern int dword_C042FC;
extern int dword_C04300;
extern int dword_C04304;
extern int dword_C04308;
extern int dword_C0430C;
extern int dword_C04310;
extern int dword_C04314;
extern int dword_C04318;
extern int dword_C0431C;
extern int dword_C04320;
extern int dword_C04324;
extern int dword_C04328;
extern int dword_C0432C;
extern int dword_C04330;
extern int dword_C04334;
extern int dword_C04350;
extern int dword_C0435C;
extern int dword_C04360;
extern int dword_C0436C;
extern int dword_C0437C;
extern int dword_C04380;
extern int dword_C0438C;
extern int dword_D8E488;
extern int nullsub_2;
extern int nullsub_3;
extern void *off_56A66C;
extern void *off_56A694;
extern void *off_56A6A8;
extern void *off_56A6B4;
extern void *off_583A1C;
extern void *off_586180;
extern int stru_BFAB60;
extern int unk_8ACBF0;

// 0x00404760
PAL3::PAL3()
{
  int v0; // eax

  memset(&g_Input.KeyInfo[119].CountMode, 0, 0xB8u);
  g_bGameActive = 1;
  PAL3::TestCombat();
  g_Input.KeyInfo[178].HoldTime = 0;
  g_Input.KeyInfo[179].PressTime = 0;
  LOBYTE(g_Input.KeyInfo[180].Data) = 0;
  v0 = g_nGameFlags;
  *(_DWORD *)g_GDB.m_ItemData[360].name = 0;
  LOBYTE(v0) = g_nGameFlags & 0xF4 | 3;
  g_nGameFlags = v0;
  *(_DWORD *)&g_GDB.m_ItemData[360].name[4] = 0;
  return &unk_8ACBF0;
}

// 0x004047F0
// attributes: thunk
PAL3::~PAL3()
{
  return PAL3::Destroy();
}

// 0x00404800
struct gbVFileSystem * PAL3::Create@<eax>(char *a1@<edi>, HINSTANCE hInstance)
{
  PalScript *v2; // ecx
  char *Instance; // eax
  HCURSOR CursorA; // eax
  HWND HoldTime; // edi
  _BYTE *v6; // eax
  CCBSystem *v7; // eax
  CCBSystem *v8; // eax
  SceneMgr *v9; // eax
  int v10; // ecx
  void *v11; // eax
  RenderTarget *v12; // eax
  RenderTarget3 *v13; // eax
  RenderTarget2 *v14; // eax
  RenderTarget4 *v15; // eax
  void *v16; // eax
  RenderTarget *v17; // eax
  RenderTarget3 *v18; // eax
  RenderTarget2 *v19; // eax
  RenderTarget4 *v20; // eax
  void *v21; // eax
  gbGeomNode *v22; // eax
  gbGeomNode *v23; // esi
  gbGeomNode *v24; // ecx
  gbVFileSystem *v25; // eax
  gbVFileSystem *v26; // esi
  gbGeomNode *v27; // ecx
  int Width; // eax
  int v30; // [esp+Ch] [ebp-960h]
  int v31; // [esp+14h] [ebp-958h]
  OpenBaseFile v32; // [esp+20h] [ebp-94Ch] BYREF
  _DWORD pParams[3]; // [esp+24h] [ebp-948h] BYREF
  char pExceptionObject[1024]; // [esp+30h] [ebp-93Ch] BYREF
  char v35[24]; // [esp+430h] [ebp-53Ch] BYREF
  int v36; // [esp+448h] [ebp-524h]
  char ArgList[1024]; // [esp+560h] [ebp-40Ch] BYREF
  int v38; // [esp+968h] [ebp-4h]
  _UNKNOWN *retaddr; // [esp+96Ch] [ebp+0h]

  PAL3::CreateGfxWindow();
  InitLogFiles();
  FileSysInit();
  gbTimeCounterInit();
  a1->CheckSystemRequire((char *)hInstance, hInstance);
  PAL3::InitGFX();
  PAL3::CreateEffectSystem();
  Parent_Data::spstr();
  v2->Update();
  ScriptSystem::Init();
  ((PalScript *)&stru_BFAB60)->LoadFromFile(filename);
  ((PalScript *)(&g_PAL3Data + 312))->LoadScript((int)aDatascriptLang);
  ((PalScript *)(&g_PAL3Data + 312))->SetAppName(aAppname);
  Instance = (char *)CScreenMode::GetInstance();
  ((CScreenMode *)Instance)->SetMode(v31);
  CursorA = LoadCursorA(hInstance, (LPCSTR)0x73);
  HoldTime = (HWND)g_Input.KeyInfo[130].HoldTime;
  g_Input.KeyInfo[180].HoldTime = (int)CursorA;
  ShowWindow((HWND)g_Input.KeyInfo[130].HoldTime, 5);
  UpdateWindow(HoldTime);
  if ( !((GRPinput *)&g_Input)->Create(hInstance, (int)HoldTime, 0) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aInputDeviceCre, aDProjectPal3Ga_0, 180),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((GRPinput *)&g_Input)->SetMouseLimits(0, 0, g_Input.KeyInfo[120].Data, g_Input.KeyInfo[120].HoldTime);
  ((GRPinput *)&g_Input)->SetMode(0x40000000);
  ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->InitCPK(0, 1);
  memset(pParams, 0, sizeof(pParams));
  ((CameraCtrl *)g_Input.KeyInfo[177].CountMode)->InitParams(pParams);
  if ( !((PAL_GDB *)&g_GDB)->PAL_GDB() )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aFightDatabaseL, aDProjectPal3Ga_0, 191),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((PAL_GDB *)(&g_PAL3Data + 328))->LoadLanguage(path);
  PAL3::InitSubsystems();
  v6 = (_BYTE *)UIQuadManager::GetInstance();
  UIRenderQuadList(v6);
  ((UIManager *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[240])->LoadShadowTexture();
  ((Logger *)g_Logger)->RegisterCallbacks();
  ((Logger *)g_Logger)->Write("%s Bulid %s %s", aV104, aJan52004, a163941);
  ((Logger *)g_Logger)->Write(aGameCreateOk);
  v7 = (CCBSystem *)((operator *)0x162D8u)->new();
  v38 = 0;
  if ( v7 )
    v8 = (CCBSystem *)v7->CCBSystem();
  else
    v8 = 0;
  g_Input.KeyInfo[178].HoldTime = (int)v8;
  v38 = -1;
  if ( !v8 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldNotAlloca, aDProjectPal3Ga_0, 214),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v8->ProcNormalAttack();
  v9 = (SceneMgr *)((operator *)0xA930u)->new();
  v38 = 1;
  if ( v9 )
  {
    if ( g_Input.KeyInfo[177].CountMode )
      v10 = g_Input.KeyInfo[177].CountMode + 4;
    else
      v10 = 0;
    v11 = (void *)v9->Create(g_Input.KeyInfo[177].Data, v10, 0);
  }
  else
  {
    v11 = 0;
  }
  v38 = -1;
  g_Input.KeyInfo[178].CountMode = (int)v11;
  if ( !v11 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldNotAlloca_0, aDProjectPal3Ga_0, 222),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( LOBYTE(g_Input.KeyInfo[180].Data) )
  {
    if ( byte_5833C0 )
      ((CGameData *)&g_GameData)->Init();
    v17 = (RenderTarget *)CRenderTarget::GetInstance();
    v17->Create();
    v18 = (RenderTarget3 *)RenderTarget3::GetInstance();
    v18->Init();
    v19 = (RenderTarget2 *)CRenderTarget2::GetInstance();
    v19->Init();
    v20 = (RenderTarget4 *)RenderTarget4::GetInstance();
    v20->Init();
    v21 = (void *)CEffectSystem::DestroyAllEffect();
    ((int)v21)->IsVisible();
    PAL3::GetCommandLineParam();
  }
  else
  {
    ((CGameData *)&g_GameData)->Init();
    CGameData_Load((int)&g_GameData, 4);
    v12 = (RenderTarget *)CRenderTarget::GetInstance();
    v12->Create();
    v13 = (RenderTarget3 *)RenderTarget3::GetInstance();
    v13->Init();
    v14 = (RenderTarget2 *)CRenderTarget2::GetInstance();
    v14->Init();
    v15 = (RenderTarget4 *)RenderTarget4::GetInstance();
    v15->Init();
    v16 = (void *)CEffectSystem::DestroyAllEffect();
    ((int)v16)->IsVisible();
  }
  (*(void (__stdcall **)(_DWORD, char *))(**(_DWORD **)(g_Input.KeyInfo[177].Data + 1816) + 28))(
    *(_DWORD *)(g_Input.KeyInfo[177].Data + 1816),
    v35);
  if ( !v36 )
    BYTE1(g_Input.KeyInfo[180].Data) = 1;
  SoundSystem::Init();
  ((OpenBaseFile *)&v32)->OpenBaseFile();
  v38 = 2;
  v22 = (gbGeomNode *)((operator *)0x118u)->new();
  v23 = v22;
  LOBYTE(v38) = 3;
  if ( v22 )
  {
    v22->gbGeomNode();
    v23->next = (gbChain1DNode *)&off_56A66C;
    v24 = v23;
  }
  else
  {
    v24 = 0;
  }
  LOBYTE(v38) = 2;
  *(_DWORD *)g_GDB.m_ItemData[360].name = v24;
  v24->LoadFromFile(aObjectG02Cvd, 0, 0);
  v25 = (gbVFileSystem *)((operator *)0x118u)->new();
  v26 = v25;
  v32.m_plastsys = v25;
  LOBYTE(retaddr) = 4;
  if ( v25 )
  {
    v25->gbGeomNode();
    v26->IsInit = (int)&off_56A66C;
    v27 = (gbGeomNode *)v26;
  }
  else
  {
    v27 = 0;
  }
  LOBYTE(retaddr) = 2;
  *(_DWORD *)&g_GDB.m_ItemData[360].name[4] = v27;
  v27->LoadFromFile(aObjectG03Cvd, 0, 0);
  ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->CreateDevice((int)aMovieLogoBik, g_Input.KeyInfo[175].PressTime, 0, 0);
  v30 = (600 - ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->GetHeight()) / 2;
  Width = ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->GetWidth();
  ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->SetViewport((800 - Width) / 2, v30);
  ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->PlayVideo(1);
  v38 = -1;
  return ((OpenNULLFile **)&v32)->OpenNULLFile();
}

// 0x00404FF0
void PAL3::InitGFX()
{
  gbActorMgr *v0; // eax
  gbActorMgr *v1; // eax
  char *v2; // eax
  char *v3; // eax
  int v4; // esi
  _BYTE v5[1040]; // [esp+20h] [ebp-81Ch] BYREF
  char ArgList[1024]; // [esp+430h] [ebp-40Ch] BYREF
  int v7; // [esp+838h] [ebp-4h]

  g_Input.KeyInfo[177].Data = (int)gbCreateGraphManager((struct gbGfxDriverInfo *)&g_Input.KeyInfo[119].CountMode);
  if ( !g_Input.KeyInfo[177].Data )
  {
    qmemcpy(&v5[16], ((Logger *)ArgList)->FormatException(aCreateGfxManag, aDProjectPal3Ga_0, 401), 0x400u);
    _CxxThrowException(&v5[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v0 = (gbActorMgr *)((operator *)0xCu)->new();
  v7 = 0;
  if ( v0 )
    v1 = (gbActorMgr *)v0->gbActorMgr((struct gbGfxManager *)g_Input.KeyInfo[177].Data);
  else
    v1 = 0;
  v7 = -1;
  g_Input.KeyInfo[177].HoldTime = (int)v1;
  if ( !v1 )
  {
    qmemcpy(&v5[16], ((Logger *)ArgList)->FormatException(aCreateActorman, aDProjectPal3Ga_0, 405), 0x400u);
    _CxxThrowException(&v5[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v2 = (char *)((operator *)0x220u)->new();
  v7 = 1;
  if ( v2 )
    v3 = (char *)sub_41BE80(v2, (struct gbGfxManager *)g_Input.KeyInfo[177].Data);
  else
    v3 = 0;
  v7 = -1;
  g_Input.KeyInfo[177].CountMode = (int)v3;
  if ( !v3 )
  {
    qmemcpy(&v5[16], ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Ga_0, 409), 0x400u);
    _CxxThrowException(&v5[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((CameraCtrl *)v3)->SetDimention(g_Input.KeyInfo[120].Data, g_Input.KeyInfo[120].HoldTime);
  sub_41D100(g_Input.KeyInfo[177].CountMode, 0);
  ((CameraCtrl *)g_Input.KeyInfo[177].CountMode)->SetAsCurrent(3);
  *(_DWORD *)&v5[12] = 3;
  *(_DWORD *)v5 = -16777216;
  *(_DWORD *)&v5[4] = 1065353216;
  ((gbGfxManager *)g_Input.KeyInfo[177].Data)->SetClearParam((struct gbClearParam *)v5);
  v4 = ((operator *)0xD8u)->new();
  v7 = 2;
  if ( v4 )
  {
    *(_DWORD *)(v4 + 4) = 1;
    *(_DWORD *)v4 = gbRefObject::`vftable';
    *(_DWORD *)v4 = gbVolumeModifier::`vftable';
    *(_DWORD *)(v4 + 96) = 0;
    *(_DWORD *)(v4 + 100) = 0;
    *(_DWORD *)(v4 + 104) = 0;
    LOBYTE(v7) = 3;
    *(_DWORD *)(v4 + 160) = 0;
    *(_DWORD *)(v4 + 164) = 0;
    *(_DWORD *)(v4 + 168) = 0;
    ((gbVec3D *)(v4 + 172))->gbVec3D(0.0, 0.0, 0.0);
    *(_DWORD *)v4 = &off_56A694;
  }
  else
  {
    v4 = 0;
  }
  v7 = -1;
  v4->Init(2);
  *(_DWORD *)(v4 + 28) = 1065353216;
  *(_DWORD *)(v4 + 32) = 1065353216;
  *(_DWORD *)(v4 + 36) = 1065353216;
  *(_DWORD *)(v4 + 40) = 1065353216;
  *(_DWORD *)(v4 + 48) = 1;
  *(_DWORD *)(v4 + 44) = 1;
  *(_DWORD *)(v4 + 12) = 1049582633;
  *(_DWORD *)(v4 + 16) = 1049582633;
  *(_DWORD *)(v4 + 20) = 1049582633;
  *(_DWORD *)(v4 + 64) = 1092616192;
  *(_DWORD *)(v4 + 60) = 1092616192;
  *(_DWORD *)(v4 + 24) = 1065353216;
  ((gbVolModNode *)&g_GDB.m_ItemData[360].name[12])->SetVolModObj((struct gbVolumeModifier *)v4);
  ((gbRefObject *)v4)->Release();
}

// 0x00405330
char PAL3::CreateEffectSystem()
{
  gbSnow *v0; // esi
  gbRain *v1; // eax
  gbRain *v2; // esi
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  char v5; // al
  OpenBaseFile v7; // [esp+8h] [ebp-85Ch] BYREF
  _DWORD *p_m_MaxUnit; // [esp+Ch] [ebp-858h]
  struct gbDropDesc v9; // [esp+10h] [ebp-854h] BYREF
  struct gbDropDesc v10; // [esp+34h] [ebp-830h] BYREF
  char pExceptionObject[1024]; // [esp+58h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+458h] [ebp-40Ch] BYREF
  int v13; // [esp+860h] [ebp-4h]

  v10.emitrate = 500;
  v10.minheight = -10.0;
  v10.maxheight = 50.0;
  v10.maxlife = 2.0;
  v10.minlife = 0.40000001;
  v10.maxvelocity = 40.0;
  v10.minvelocity = 20.0;
  v10.range = 100.0;
  v10.unitsize = 0.079999998;
  v9.emitrate = 200;
  v9.minheight = -10.0;
  v9.maxheight = 50.0;
  v9.maxlife = 3.0;
  v9.minlife = 1.0;
  v9.maxvelocity = 10.0;
  v9.minvelocity = 6.0;
  v9.range = 100.0;
  v9.unitsize = 0.5;
  ((OpenBaseFile *)&v7)->OpenBaseFile();
  v13 = 0;
  v0 = (gbSnow *)((operator *)0x58u)->new();
  p_m_MaxUnit = (_DWORD *)&v0->m_MaxUnit;
  LOBYTE(v13) = 1;
  if ( v0 )
  {
    v0->gbSnow(500, &v9, aEffectSnowTga, 2.0);
    v0->m_MaxUnit = (int)&off_56A6B4;
  }
  else
  {
    v0 = 0;
  }
  LOBYTE(v13) = 0;
  g_Input.KeyInfo[174].CountMode = (int)v0;
  v1 = (gbRain *)((operator *)0x50u)->new();
  v2 = v1;
  p_m_MaxUnit = v1;
  LOBYTE(v13) = 2;
  if ( v1 )
  {
    v1->gbRain(500, &v10, 0);
    *(_DWORD *)v2 = &off_56A6A8;
  }
  else
  {
    v2 = 0;
  }
  LOBYTE(v13) = 0;
  g_Input.KeyInfo[174].PressTime = (int)v2;
  v3 = (_DWORD *)((operator *)0x158u)->new();
  p_m_MaxUnit = v3;
  LOBYTE(v13) = 3;
  if ( v3 )
    v4 = (_DWORD *)sub_4C5820(v3, g_Input.KeyInfo[177].Data);
  else
    v4 = 0;
  LOBYTE(v13) = 0;
  g_Input.KeyInfo[178].Data = (int)v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldnTMallocM, aDProjectPal3Ga_0, 483),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v5 = sub_4C58C0(v4);
  v13 = -1;
  if ( v5 )
  {
    ((OpenNULLFile **)&v7)->OpenNULLFile();
    return 1;
  }
  else
  {
    ((OpenNULLFile **)&v7)->OpenNULLFile();
    return 0;
  }
}

// 0x004055A0
char PAL3::DestroyEffectSystem()
{
  void *Data; // esi

  Data = (void *)g_Input.KeyInfo[178].Data;
  if ( g_Input.KeyInfo[178].Data )
  {
    sub_4C5840(g_Input.KeyInfo[178].Data);
    operator delete(Data);
  }
  g_Input.KeyInfo[178].Data = 0;
  return 1;
}

// 0x004055D0
int PAL3::Update(int a1)
{
  int v1; // edi
  unsigned __int16 *v2; // esi
  __int16 KeyState; // ax
  BOOL v4; // eax
  DWORD Time; // eax
  int PressTime; // esi
  int v7; // ebx
  int v8; // eax
  _DWORD *v9; // eax
  float *v10; // ebp
  int v11; // ebx
  float *p_y; // esi
  double v13; // st7
  double v14; // st7
  _DWORD *v15; // eax
  double v16; // st7
  _DWORD *v17; // eax
  void *v18; // ecx
  int *v19; // eax
  int *v20; // eax
  float *Instance; // eax
  _DWORD *v22; // eax
  void *v23; // ecx
  char *v24; // eax
  char *v25; // eax
  int Mode; // eax
  char *v27; // eax
  gbAudioManager *AudioManager; // esi
  char *v29; // eax
  char *v30; // eax
  _BYTE *v31; // eax
  int result; // eax
  int v33; // [esp+4h] [ebp-2Ch]
  int v34; // [esp+4h] [ebp-2Ch]
  float dt; // [esp+18h] [ebp-18h]
  float dt_4; // [esp+1Ch] [ebp-14h]
  float v37; // [esp+20h] [ebp-10h]
  gbVec3D v38; // [esp+24h] [ebp-Ch] BYREF

  *(float *)&g_Input.KeyInfo[181].Data = *(float *)&g_Input.KeyInfo[181].Data + *(float *)&a1;
  ((GRPinput *)&g_Input)->GRPinput();
  v1 = 0;
  v2 = (unsigned __int16 *)(&g_PAL3Data + 224);
  do
  {
    KeyState = ((GRPinput *)&g_Input)->GetKeyState(*v2);
    v4 = KeyState == 1 || KeyState == 3;
    v33 = v4;
    Time = timeGetTime();
    ((GRPinput *)&g_Input)->SetMouseAbs(Time, v1, v33);
    ++v2;
    ++v1;
  }
  while ( (int)v2 < (int)((unsigned __int16 *)&g_PAL3Data + 153) );
  PressTime = g_Input.KeyInfo[177].PressTime;
  v7 = SceneUpdate((int)&g_GameData, a1, 1);
  v8 = g_Input.KeyInfo[177].PressTime;
  if ( g_Input.KeyInfo[177].PressTime != PressTime )
  {
    PressTime->IfHideFightSucceed();
    v8 = g_Input.KeyInfo[177].PressTime;
  }
  switch ( v8 )
  {
    case 0:
    case 1:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset();
      goto LABEL_64;
    case 2:
    case 9:
      *(float *)&g_Input.KeyInfo[176].PressTime = *(float *)&g_Input.KeyInfo[176].PressTime + *(float *)&a1;
      (*(void (**)(_DWORD))(**(_DWORD **)g_GDB.m_ItemData[360].name + 20))(*(_DWORD *)g_GDB.m_ItemData[360].name);
      (*(void (**)(_DWORD))(**(_DWORD **)&g_GDB.m_ItemData[360].name[4] + 20))(*(_DWORD *)&g_GDB.m_ItemData[360].name[4]);
      Instance = (float *)CRenderTarget2::GetInstance();
      CRenderTarget2_Update(Instance, *(float *)&a1);
      a1->RunSceneScript();
      if ( byte_D8C339 )
      {
        byte_D8C339 = 0;
        a1->RunSceneScript();
      }
      InputUpdate(g_Input.KeyInfo[177].CountMode, *(float *)&a1);
      if ( g_Input.KeyInfo[177].PressTime != 9 )
      {
        if ( v7 )
        {
          UIQuadManager::GetInstance();
          UIQuadManager_Reset();
        }
        else
        {
          CameraUpdate_Internal(*(float *)&a1);
        }
        ScriptUpdate(*(float *)&a1);
      }
      v22 = (_DWORD *)UISceneUpdate();
      UIUpdate(v22, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      SceneMgrUpdate((float *)g_Input.KeyInfo[178].CountMode, *(float *)&g_Input.KeyInfo[176].PressTime);
      UIPostUpdate(v23);
      v24 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v24)->AudioUpdate();
      if ( g_Input.KeyInfo[177].PressTime != 2 && g_Input.KeyInfo[177].PressTime != 9 )
        PressTime->IfHideFightSucceed();
      goto LABEL_64;
    case 3:
      ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->CombatUpdate(*(float *)&a1);
      CombatEffectUpdate(g_Input.KeyInfo[178].Data, *(float *)&a1);
      v25 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v25)->AudioUpdate();
      if ( !*(_BYTE *)(g_Input.KeyInfo[178].HoldTime + 116) )
        goto LABEL_64;
      if ( LOBYTE(g_Input.KeyInfo[180].Data) )
      {
        PAL3::GetCommandLineParam();
        ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->CombatUpdate(0.0);
        CombatEffectUpdate(g_Input.KeyInfo[178].Data, 0.0);
        goto LABEL_59;
      }
      byte_5833D0 = *(_DWORD *)(g_Input.KeyInfo[178].HoldTime + 124) == 2;
      Mode = ((CGameData *)&g_GameData)->GetMode();
      CGameData_Load((int)&g_GameData, Mode);
      CombatEnter();
      if ( (g_nGameFlags & 4) == 0 )
        goto LABEL_54;
      v27 = (char *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)v27)->GetAudioManager();
      if ( !AudioManager )
        goto LABEL_54;
      if ( g_SceneMgr.m_npc[6].m_actor.m_szTexture[233] )
      {
        if ( CScreenMode::GetInstance()[4] )
          goto LABEL_54;
        goto LABEL_51;
      }
      AudioManager->StopSoundStream(1);
      AudioManager->StopSoundStream(0);
      if ( !CScreenMode::GetInstance()[4] )
      {
LABEL_51:
        AudioManager->StopSoundStream(2);
        AudioManager->StopSoundStream(1);
        v29 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v29)->AudioStopAll();
        goto LABEL_54;
      }
      v30 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v30)->AudioFadeOut();
LABEL_54:
      if ( byte_5833D0 || !dword_5833CC )
      {
        if ( *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[236] )
          *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[236] + 632) = 0;
      }
      else
      {
        CGameData_Load((int)&g_GameData, 15);
        PalScriptMgr::IfHaveScript();
      }
LABEL_59:
      g_SceneMgr.m_npc[6].m_actor.m_szTexture[224] = 0;
      g_SceneMgr.m_npc[6].m_actor.m_szTexture[232] = 0;
      *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[180] = 0x7FFFFFFF;
      dword_5833CC = 1;
      goto LABEL_64;
    case 4:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset();
      MiniGame1Update((_DWORD ***)g_Input.KeyInfo[179].Data, *(float *)&a1);
      goto LABEL_64;
    case 5:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset();
      MiniGame2Update(g_Input.KeyInfo[178].PressTime, a1);
      goto LABEL_63;
    case 6:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset();
      MiniGame3Update((int *)g_Input.KeyInfo[179].HoldTime, *(float *)&a1);
LABEL_63:
      NPCAnimUpdate(*(float *)&a1);
      goto LABEL_64;
    case 7:
      *(float *)&g_Input.KeyInfo[176].CountMode = *(float *)&g_Input.KeyInfo[176].CountMode + *(float *)&a1;
      if ( g_Input.KeyInfo[174].Data )
      {
        if ( !PalScriptMgr::_CON_CloseScript() )
        {
          byte_D924E8 = 1;
          CGameData_Load((int)&g_GameData, 4);
        }
      }
      else if ( *(float *)&g_Input.KeyInfo[176].CountMode >= 60.0 )
      {
        ((PAL3 *)-1)->EndWolf();
        goto LABEL_64;
      }
      a1->RunSceneScript();
      InputUpdate(g_Input.KeyInfo[177].CountMode, *(float *)&a1);
      ScriptUpdate(*(float *)&a1);
      v9 = (_DWORD *)UISceneUpdate();
      UIUpdate(v9, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      if ( g_Input.KeyInfo[174].Data )
        goto LABEL_64;
      if ( !v7 )
        CameraUpdate_Internal(*(float *)&a1);
      v10 = (float *)*(float **)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132];
      v11 = 1;
      p_y = (float *)&g_SceneMgr.m_npc[1].m_path.normal[79].y;
      while ( 1 )
      {
        if ( *((_DWORD *)p_y + 155) )
        {
          dt = v10[1] - *(p_y - 2);
          v13 = v10[2] - *(p_y - 1);
          v38.x = dt;
          dt_4 = v13;
          v14 = v10[3] - *p_y;
          v38.y = dt_4;
          v37 = v14;
          v38.z = v37;
          if ( 12.0 + 12.0 > ((gbVec3D *)&v38)->Length() )
            break;
        }
        p_y += 2176;
        ++v11;
        if ( (int)p_y >= (int)&g_SceneMgr.m_npc[5].m_path.normal[59].y )
          goto LABEL_64;
      }
      v11->EndWolf();
      goto LABEL_64;
    case 8:
      if ( PAL3::EntryCatchGhost() )
      {
        PAL3::EndHideFight();
        RoleSystemNotify(*(int *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132]);
        v15 = ((PalScriptMgr *)0x6A5u)->Destroy(0);
LABEL_33:
        v34 = (int)v15;
        v20 = (int *)SoundContext::GetInstance();
        CScreenMode_SetResolution(v20, 0, v34);
        a1->RunSceneScript();
        goto LABEL_64;
      }
      v16 = *(float *)&g_Input.KeyInfo[176].CountMode + *(float *)&a1;
      *(float *)&g_Input.KeyInfo[176].CountMode = v16;
      if ( v16 >= 180.0 )
        goto LABEL_32;
      a1->RunSceneScript();
      InputUpdate(g_Input.KeyInfo[177].CountMode, *(float *)&a1);
      ScriptUpdate(*(float *)&a1);
      v17 = (_DWORD *)UISceneUpdate();
      UIUpdate(v17, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      if ( !v7 )
        CameraUpdate_Internal(*(float *)&a1);
      UIPostUpdate(v18);
      if ( *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132] + 1264) != 4 )
      {
        v19 = (int *)UISceneUpdate();
        if ( UINotifyUpdate(v19) )
        {
LABEL_32:
          RoleSystemNotify(*(int *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132]);
          PAL3::EndHideFight();
          v15 = ((PalScriptMgr *)0x6A6u)->Destroy(0);
          goto LABEL_33;
        }
      }
LABEL_64:
      v31 = (_BYTE *)ScreenEffectMgr::GetInstance();
      RenderPost((int)v31, a1);
      result = g_Input.KeyInfo[177].PressTime;
      if ( !g_Input.KeyInfo[177].PressTime )
        return ((CScreenMode *)g_Logger)->SetState(1);
      return result;
    default:
      goto LABEL_64;
  }
}

// 0x00405C00
void PAL3::Render()
{
  int v0; // edi
  struct gbCamera *v1; // eax
  int v2; // ebx
  gbMatrixStack *v3; // esi
  gbMatrix4 *Top; // eax
  UIScene *v5; // eax
  struct gbCamera *v6; // eax
  struct gbCamera *v7; // eax
  UIScene *v8; // eax
  struct gbCamera *v9; // eax
  UIScene *v10; // eax
  UIScene *v11; // eax
  struct gbCamera *v12; // eax
  UIScene *v13; // eax
  RenderTarget3 *Instance; // eax
  RenderTarget2 *v15; // eax
  RenderTarget3 *v16; // eax
  int v17; // edi
  __int64 v18; // rax
  int v19; // esi
  double v20; // st7
  ScreenEffectMgr *v21; // eax
  void *v22; // eax
  float v23; // [esp+0h] [ebp-94h]
  float v24; // [esp+4h] [ebp-90h]
  int v25; // [esp+18h] [ebp-7Ch]
  int v26; // [esp+18h] [ebp-7Ch]
  struct gbVec3D v27; // [esp+24h] [ebp-70h] BYREF
  struct gbVec3D v28; // [esp+30h] [ebp-64h] BYREF
  struct gbVec3D v29; // [esp+3Ch] [ebp-58h] BYREF
  struct gbVec3D v30; // [esp+48h] [ebp-4Ch] BYREF
  struct gbVec3D v31; // [esp+54h] [ebp-40h] BYREF
  gbQuaternion v32; // [esp+60h] [ebp-34h] BYREF
  gbQuaternion v33; // [esp+70h] [ebp-24h] BYREF
  struct gbQuaternion v34; // [esp+80h] [ebp-14h] BYREF
  int v35; // [esp+90h] [ebp-4h]

  (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 48))(g_Input.KeyInfo[177].Data);
  switch ( g_Input.KeyInfo[177].PressTime )
  {
    case 0:
      (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 52))(g_Input.KeyInfo[177].Data);
      return;
    case 2:
    case 7:
    case 8:
    case 9:
      RenderTarget4::GetInstance();
      RenderTarget3::End();
      CRenderTarget2::GetInstance();
      RenderTarget2::Begin();
      v0 = *(_DWORD *)(g_Input.KeyInfo[177].Data + 448);
      if ( g_Input.KeyInfo[177].CountMode )
        v1 = (struct gbCamera *)(g_Input.KeyInfo[177].CountMode + 4);
      else
        v1 = 0;
      ((gbSceneGraph *)v0)->Begin(v1);
      v2 = UIScene::CombatCheck();
      v3 = (gbMatrixStack *)*(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 216);
      ((CameraCtrl *)g_Input.KeyInfo[177].CountMode)->SetAsCurrent(3);
      v27.x = 1.0;
      v27.y = 0.0;
      v27.z = 0.0;
      v3->Rotate(g_SceneMgr.m_npc[6].m_path.normal[48].z, &v27);
      v28.x = 0.0;
      v28.y = 1.0;
      v28.z = 0.0;
      v3->Rotate(g_SceneMgr.m_npc[6].m_path.normal[49].x, &v28);
      v29.x = 0.0;
      v29.y = 0.0;
      v29.z = 1.0;
      v3->Rotate(g_SceneMgr.m_npc[6].m_path.normal[49].y, &v29);
      if ( !v2 && *(_DWORD *)(UISceneUpdate() + 100) != 1 )
      {
        memset(&v32, 0, 12);
        memset(&v33, 0, 12);
        memset(&v34, 0, 12);
        v30.y = 0.0;
        v30.z = 0.0;
        v32.w = 1.0;
        v33.w = 1.0;
        v34.w = 1.0;
        v30.x = 1.0;
        ((gbQuaternion *)&v32)->SetAxisAngle(&v30, 45.0);
        v31.x = 0.0;
        v31.y = 1.0;
        v31.z = 0.0;
        ((gbQuaternion *)&v33)->SetAxisAngle(&v31, 90.0);
        ((gbQuaternion *)&v33)->MultiplyBy(&v32, &v34);
        ((gbQuaternion *)&v34)->GetMatrix((struct gbMatrix4 *)&g_GDB.m_ItemData[360].desc[8]);
        ((gbVolModNode *)&g_GDB.m_ItemData[360].name[12])->Attach(0);
      }
      if ( dword_D8E488 == 2 )
      {
        Top = (gbMatrix4 *)v3->GetTop();
        Top->TransformPlane();
        (*(void (**)(int, int *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 112))(
          g_Input.KeyInfo[177].Data,
          &dword_D8E488);
      }
      else
      {
        (*(void (**)(int, _DWORD))(*(_DWORD *)g_Input.KeyInfo[177].Data + 112))(g_Input.KeyInfo[177].Data, 0);
      }
      v5 = (UIScene *)UISceneUpdate();
      v5->RenderWithStack(v3);
      if ( g_Input.KeyInfo[177].PressTime != 9 )
        v3->Render();
      ((gbSceneGraph *)v0)->End();
      if ( g_Input.KeyInfo[174].CountMode && LOBYTE(g_Input.KeyInfo[175].Data) )
      {
        if ( g_Input.KeyInfo[177].CountMode )
          v6 = (struct gbCamera *)(g_Input.KeyInfo[177].CountMode + 4);
        else
          v6 = 0;
        ((gbDropGroup *)g_Input.KeyInfo[174].CountMode)->Render(v6);
      }
      if ( g_Input.KeyInfo[174].PressTime && BYTE1(g_Input.KeyInfo[175].Data) )
      {
        if ( g_Input.KeyInfo[177].CountMode )
          v7 = (struct gbCamera *)(g_Input.KeyInfo[177].CountMode + 4);
        else
          v7 = 0;
        ((gbDropGroup *)g_Input.KeyInfo[174].PressTime)->Render(v7);
      }
      v8 = (UIScene *)UISceneUpdate();
      v8->NotifyRender();
      if ( g_Input.KeyInfo[177].CountMode )
        v9 = (struct gbCamera *)(g_Input.KeyInfo[177].CountMode + 4);
      else
        v9 = 0;
      ((gbSceneGraph *)v0)->Begin(v9);
      *(_BYTE *)(v0 + 19244) = 0;
      if ( *(_DWORD *)(UISceneUpdate() + 100) != 1 )
        UIScene::CombatCheck();
      v10 = (UIScene *)UISceneUpdate();
      v10->Render((int)v3);
      ((SceneMgr *)g_Input.KeyInfo[178].CountMode)->RenderUpdate();
      ((gbSceneGraph *)v0)->End();
      if ( g_Input.KeyInfo[177].PressTime == 8 )
      {
        v11 = (UIScene *)UISceneUpdate();
        v11->EffectRender();
      }
      ((UIManager *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[240])->Render();
      ((SceneMgr *)g_Input.KeyInfo[178].CountMode)->RenderAll();
      if ( g_Input.KeyInfo[177].CountMode )
        v12 = (struct gbCamera *)(g_Input.KeyInfo[177].CountMode + 4);
      else
        v12 = 0;
      ((gbSceneGraph *)v0)->Begin(v12);
      *(_BYTE *)(v0 + 19244) = 0;
      UIScene::CombatCheck();
      sub_410430((int)v3);
      v13 = (UIScene *)UISceneUpdate();
      v13->OverlayRender((int)v3);
      ((gbSceneGraph *)v0)->End();
      Instance = (RenderTarget3 *)RenderTarget4::GetInstance();
      Instance->Resolve();
      v15 = (RenderTarget2 *)CRenderTarget2::GetInstance();
      v15->Resolve();
      v16 = (RenderTarget3 *)RenderTarget3::GetInstance();
      v16->Begin();
      if ( !g_bRenderUI )
        break;
      goto LABEL_42;
    case 3:
      ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->RenderCheck();
      break;
    case 4:
      ((MiniGame1 *)g_Input.KeyInfo[179].Data)->Render();
      break;
    case 5:
      sub_52F2E0((_DWORD *)g_Input.KeyInfo[178].PressTime);
      goto LABEL_42;
    case 6:
      ((MiniGame3 *)g_Input.KeyInfo[179].HoldTime)->Render();
LABEL_42:
      ScriptSystem::Render2();
      break;
    default:
      break;
  }
  if ( g_Input.KeyInfo[177].PressTime == 8 )
  {
    v17 = (__int64)(180.0 - *(float *)&g_Input.KeyInfo[176].CountMode);
    goto LABEL_46;
  }
  if ( g_Input.KeyInfo[177].PressTime == 7 )
  {
    v17 = (int)(__int64)(60.0 - *(float *)&g_Input.KeyInfo[176].CountMode) < 0
        ? 0
        : (__int64)(60.0 - *(float *)&g_Input.KeyInfo[176].CountMode);
LABEL_46:
    sprintf((char *const)&v33.z, "%03d", v17);
    LOBYTE(v18) = 0;
    v19 = *(_DWORD *)(*(_DWORD *)(g_Input.KeyInfo[177].Data + 208) + 12);
    if ( v17 < 30 )
      v18 = (__int64)(sin(*(float *)&g_Input.KeyInfo[176].CountMode * 4.0) * 255.0);
    v20 = 60.0 / (double)g_Input.KeyInfo[120].HoldTime;
    *(float *)(v19 + 48) = 60.0 / (double)g_Input.KeyInfo[120].Data;
    *(float *)(v19 + 52) = v20;
    if ( (_BYTE)v18 )
    {
      if ( gbColorQuad::ColorQuadFmt )
      {
        BYTE2(v25) = v18;
        LOWORD(v25) = 29338;
      }
      else
      {
        *(_WORD *)((char *)&v25 + 1) = -25998;
        LOBYTE(v25) = v18;
      }
      HIBYTE(v25) = -56;
      *(_DWORD *)(v19 + 44) = v25;
    }
    else
    {
      if ( gbColorQuad::ColorQuadFmt )
      {
        *(_WORD *)((char *)&v26 + 1) = 214;
        LOBYTE(v26) = -2;
      }
      else
      {
        *(_WORD *)((char *)&v26 + 1) = -298;
        LOBYTE(v26) = 0;
      }
      HIBYTE(v26) = -56;
      *(_DWORD *)(v19 + 44) = v26;
    }
    v24 = 1.0 - 64.0 / (double)g_Input.KeyInfo[120].HoldTime;
    v23 = 1380.0 / (double)g_Input.KeyInfo[120].Data - 1.0;
    (*(void (**)(int, float *, _DWORD, _DWORD, int, int))(*(_DWORD *)v19 + 16))(
      v19,
      &v33.z,
      LODWORD(v23),
      LODWORD(v24),
      1176256512,
      1176256512);
    (*(void (**)(int))(*(_DWORD *)v19 + 8))(v19);
  }
  if ( g_Input.KeyInfo[177].PressTime && g_Input.KeyInfo[177].PressTime != 3 && g_bRenderUI )
  {
    PushMatrixStacks();
    v35 = 0;
    v21 = (ScreenEffectMgr *)ScreenEffectMgr::GetInstance();
    v21->Render();
    ((CGameData *)&g_GameData)->Render();
    if ( g_Input.KeyInfo[174].HoldTime )
      (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[174].HoldTime + 4))(g_Input.KeyInfo[174].HoldTime);
    if ( !g_Input.KeyInfo[180].CountMode )
      ((Logger *)g_Logger)->Render();
    v35 = -1;
    PopMatrixStacks();
  }
  v22 = (void *)UIQuadManager::GetInstance();
  ((int)v22)->UIRenderObj();
  (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 52))(g_Input.KeyInfo[177].Data);
  if ( g_Input.KeyInfo[180].CountMode )
  {
    PAL3::PrintScreen();
    g_Input.KeyInfo[180].CountMode = 0;
  }
}

// 0x00406230
void PAL3::Destroy()
{
  CRenderTarget *Instance; // eax
  CRenderTarget2 *v1; // eax
  UIQuadManager *v2; // eax
  void *HoldTime; // esi
  void *v4; // esi
  char *v5; // eax

  Instance = (CRenderTarget *)CRenderTarget::GetInstance();
  Instance->Destroy();
  v1 = (CRenderTarget2 *)CRenderTarget2::GetInstance();
  v1->Destroy();
  v2 = (UIQuadManager *)UIQuadManager::GetInstance();
  v2->Destroy();
  ScriptSystem::Destroy();
  UISystem::Destroy();
  _TextureLib_Data::_TextureLib_Data();
  PalScriptMgr::_CON_ReLoadScript();
  if ( g_Input.KeyInfo[178].HoldTime )
  {
    ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->ProcFling();
    HoldTime = (void *)g_Input.KeyInfo[178].HoldTime;
    if ( g_Input.KeyInfo[178].HoldTime )
    {
      nullsub_3((void *)g_Input.KeyInfo[178].HoldTime);
      operator delete(HoldTime);
    }
    g_Input.KeyInfo[178].HoldTime = 0;
  }
  ((CGameData *)&g_GameData)->Destroy();
  PAL3::DestroyEffectSystem();
  if ( g_Input.KeyInfo[177].CountMode )
  {
    (**(void (***)(int, int))g_Input.KeyInfo[177].CountMode)(g_Input.KeyInfo[177].CountMode, 1);
    g_Input.KeyInfo[177].CountMode = 0;
  }
  v4 = (void *)g_Input.KeyInfo[177].HoldTime;
  if ( g_Input.KeyInfo[177].HoldTime )
  {
    ((gbActorMgr *)g_Input.KeyInfo[177].HoldTime)->~gbActorMgr();
    operator delete(v4);
    g_Input.KeyInfo[177].HoldTime = 0;
  }
  if ( g_Input.KeyInfo[177].Data )
  {
    (**(void (***)(int, int))g_Input.KeyInfo[177].Data)(g_Input.KeyInfo[177].Data, 1);
    g_Input.KeyInfo[177].Data = 0;
  }
  FileSysDestory();
  v5 = (char *)CScreenMode::GetInstance();
  ((CScreenMode *)v5)->Restore();
}

// 0x00406310
void PAL3::CheckSystemRequire(char *a1@<edi>, char *a2@<esi>, HINSTANCE hInstance)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  DWORD v5; // esi
  HWND Window; // eax
  char *v7; // [esp-10h] [ebp-116Ch]
  CHAR ClassName[20]; // [esp+0h] [ebp-115Ch] BYREF
  struct tagRECT rc; // [esp+14h] [ebp-1148h] BYREF
  WNDCLASSA WndClass; // [esp+24h] [ebp-1138h] BYREF
  char Buffer[260]; // [esp+4Ch] [ebp-1110h] BYREF
  _BYTE v12[1024]; // [esp+150h] [ebp-100Ch] BYREF
  char pExceptionObject[1024]; // [esp+550h] [ebp-C0Ch] BYREF
  char ArgList[1024]; // [esp+950h] [ebp-80Ch] BYREF
  char v15[1024]; // [esp+D50h] [ebp-40Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v16; // [esp+1150h] [ebp-Ch]
  void *v17; // [esp+1154h] [ebp-8h]
  int v18; // [esp+1158h] [ebp-4h]

  v18 = -1;
  ExceptionList = (struct _EXCEPTION_REGISTRATION_RECORD *)NtCurrentTeb()->NtTib.ExceptionList;
  v17 = (void *)&loc_55F21B;
  v16 = ExceptionList;
  v4 = (void *)alloca(4432);
  strcpy(ClassName, "PAL3--SOFTSTAR.sh");
  WndClass.style = 32;
  WndClass.lpfnWndProc = WinProc;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hInstance = hInstance;
  memset(&WndClass.hIcon, 0, 16);
  WndClass.lpszClassName = ClassName;
  if ( !RegisterClassA(&WndClass) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aRegisterclassF, aDProjectPal3Ga_0, 1094),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((Config *)Buffer)->ReadINIInt(a1, a2);
  v18 = 0;
  ((Config *)Buffer)->ReadINIString(aConfigIni, v7);
  g_Input.KeyInfo[119].CountMode = 2;
  g_Input.KeyInfo[119].PressTime = 0;
  ((Config *)Buffer)->ReadINI(aDisplay, section);
  ((Config *)Buffer)->ReadINI(aDisplay, aHeight);
  ((Config *)Buffer)->ReadINI(aDisplay, aColorbits);
  ((Config *)Buffer)->ReadINI(aDisplay, aDepthbits);
  ((Config *)Buffer)->ReadINI(aDisplay, aRate);
  g_Input.KeyInfo[121].HoldTime = 2;
  g_Input.KeyInfo[130].PressTime = (unsigned __int8)(g_nGameFlags & 0x10) >> 4;
  g_Input.KeyInfo[121].CountMode = 1;
  g_Input.KeyInfo[121].Data = 0;
  strcpy((char *)&g_Input.KeyInfo[122], ClassName);
  g_Input.KeyInfo[130].Data = (int)hInstance;
  g_Input.KeyInfo[130].CountMode = 0;
  v5 = g_Input.KeyInfo[121].CountMode != 0 ? 8 : 0;
  SetRect(&rc, 0, 0, g_Input.KeyInfo[120].Data, g_Input.KeyInfo[120].HoldTime);
  AdjustWindowRect(&rc, 0x96080000, 0);
  Window = CreateWindowExA(
             v5,
             ClassName,
             ClassName,
             0x96080000,
             0,
             0,
             rc.right - rc.left,
             rc.bottom - rc.top,
             0,
             0,
             hInstance,
             0);
  if ( !Window )
  {
    qmemcpy(v12, ((Logger *)v15)->FormatException(aWindowCreateFa, aDProjectPal3Ga_0, 1152), sizeof(v12));
    _CxxThrowException(v12, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_Input.KeyInfo[130].HoldTime = (int)Window;
  g_Input.KeyInfo[175].PressTime = (int)Window;
  v18 = -1;
  nullsub_3(Buffer);
}

// 0x004065F0
char PAL3::CreateGfxWindow()
{
  LPSTR CommandLineA; // eax
  int v1; // eax
  int v2; // eax
  bool v3; // cc
  int v4; // eax
  bool v5; // zf
  int v6; // eax

  CommandLineA = GetCommandLineA();
  g_Input.KeyInfo[179].PressTime = (int)CommandLineA;
  if ( CommandLineA )
  {
    if ( aSc->ParseCmdLine() || aSoftcursor->ParseCmdLine() )
      BYTE1(g_Input.KeyInfo[180].Data) = 1;
    if ( aXsnd->ParseCmdLine() )
    {
      v1 = g_nGameFlags;
      LOBYTE(v1) = g_nGameFlags & 0xFE;
      g_nGameFlags = v1;
    }
    if ( aXmusic->ParseCmdLine() )
    {
      v2 = g_nGameFlags;
      LOBYTE(v2) = g_nGameFlags & 0xFB;
      g_nGameFlags = v2;
    }
    v3 = aSync->HasCommandLineParam() <= 0;
    v4 = g_nGameFlags;
    if ( v3 )
      LOBYTE(v4) = g_nGameFlags & 0xEF;
    else
      LOBYTE(v4) = g_nGameFlags | 0x10;
    g_nGameFlags = v4;
    v5 = aMotionblur->ParseCmdLine() == 0;
    v6 = g_nGameFlags;
    if ( v5 )
      LOBYTE(v6) = g_nGameFlags & 0xF7;
    else
      LOBYTE(v6) = g_nGameFlags | 8;
    g_nGameFlags = v6;
    if ( aScursor->ParseCmdLine() )
      *((_BYTE *)UIQuadManager::GetInstance() + 29) = 1;
    v3 = aRate->HasCommandLineParam() <= 60;
    CommandLineA = (LPSTR)g_nGameFlags;
    if ( v3 )
      LOBYTE(CommandLineA) = g_nGameFlags & 0xDF;
    else
      LOBYTE(CommandLineA) = g_nGameFlags | 0x20;
    g_nGameFlags = (int)CommandLineA;
  }
  return (char)CommandLineA;
}

// 0x004066F0
char PAL3::ParseCmdLine(char *lpKeyName)
{
  char *v2; // [esp+0h] [ebp-340h]
  char *v3; // [esp+0h] [ebp-340h]
  char *v4; // [esp+4h] [ebp-33Ch]
  char Buffer[32]; // [esp+10h] [ebp-330h] BYREF
  CHAR FileName[260]; // [esp+30h] [ebp-310h] BYREF
  char Str[512]; // [esp+134h] [ebp-20Ch] BYREF
  int v8; // [esp+33Ch] [ebp-4h]

  if ( strlen(lpKeyName) < 0x14 && strlen(GetCommandLineA()) < 0x200 && strlen(GetCommandLineA()) )
  {
    strcpy(Str, GetCommandLineA());
    sprintf(Buffer, aS, lpKeyName);
    _strlwr(Str);
    _strlwr(Buffer);
    if ( strstr(Str, Buffer) )
      return 1;
    sprintf(Buffer, off_583A1C, lpKeyName);
    if ( strstr(Str, Buffer) && strlen(Str) == strstr(Str, Buffer) - Str + strlen(Buffer) )
      return 1;
    ((Config *)FileName)->ReadINIInt(v2, v4);
    v8 = 0;
    ((Config *)FileName)->ReadINIString(aConfigIni, v3);
    ((Config *)FileName)->ReadINI(aMisc, lpKeyName);
    v8 = -1;
    nullsub_3(FileName);
  }
  return 0;
}

// 0x004068C0
int PAL3::HasCommandLineParam(char *lpKeyName)
{
  int result; // eax
  char *v2; // [esp+0h] [ebp-11Ch]
  char *v3; // [esp+0h] [ebp-11Ch]
  char *v4; // [esp+4h] [ebp-118h]
  char Buffer[260]; // [esp+Ch] [ebp-110h] BYREF
  int v6; // [esp+118h] [ebp-4h]

  result = 0;
  if ( strlen(lpKeyName) < 0x14 )
  {
    ((Config *)Buffer)->ReadINIInt(v2, v4);
    v6 = 0;
    ((Config *)Buffer)->ReadINIString(aConfigIni, v3);
    ((Config *)Buffer)->ReadINI(aDisplay, lpKeyName);
    v6 = -1;
    nullsub_3(Buffer);
    return 0;
  }
  return result;
}

// 0x00406980
int PAL3::GetCommandLineParam()
{
  if ( !LOBYTE(g_SceneMgr.m_npc[0].m_path.normal[82].z)
    && __PAIR16__(BYTE1(g_SceneMgr.m_npc[0].m_path.normal[82].z), 0) == BYTE2(g_SceneMgr.m_npc[0].m_path.normal[82].z)
    && __PAIR16__(HIBYTE(g_SceneMgr.m_npc[0].m_path.normal[82].z), 0) == LOBYTE(g_SceneMgr.m_npc[0].m_path.normal[83].x) )
  {
    g_SceneMgr.m_npc[0].m_path.normal[82].z = 2.3510607e-38;
    LOBYTE(g_SceneMgr.m_npc[0].m_path.normal[83].x) = 0;
  }
  if ( !*(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[176] )
    PAL3::UpdateSubsystems();
  ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->ProcMagicWait((int)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[152], 1);
  return CGameData_Load((int)&g_GameData, 6);
}

// 0x00406A10
int PAL3::TestCombat()
{
  *((_WORD *)&g_PAL3Data + 120) = 27;
  *((_WORD *)&g_PAL3Data + 123) = 9;
  *((_WORD *)&g_PAL3Data + 124) = 9;
  *((_WORD *)&g_PAL3Data + 129) = 27;
  *((_WORD *)&g_PAL3Data + 136) = 9;
  *((_WORD *)&g_PAL3Data + 112) = 256;
  *((_WORD *)&g_PAL3Data + 113) = 257;
  *((_WORD *)&g_PAL3Data + 114) = 134;
  *((_WORD *)&g_PAL3Data + 115) = 135;
  *((_WORD *)&g_PAL3Data + 116) = 136;
  *((_WORD *)&g_PAL3Data + 117) = 137;
  *((_WORD *)&g_PAL3Data + 118) = 32;
  *((_WORD *)&g_PAL3Data + 119) = 13;
  *((_WORD *)&g_PAL3Data + 122) = 154;
  *((_WORD *)&g_PAL3Data + 121) = 155;
  *((_WORD *)&g_PAL3Data + 125) = 97;
  *((_WORD *)&g_PAL3Data + 126) = 100;
  *((_WORD *)&g_PAL3Data + 127) = 256;
  *((_WORD *)&g_PAL3Data + 128) = 257;
  *((_WORD *)&g_PAL3Data + 130) = 13;
  *((_WORD *)&g_PAL3Data + 131) = 32;
  *((_WORD *)&g_PAL3Data + 132) = 134;
  *((_WORD *)&g_PAL3Data + 133) = 135;
  *((_WORD *)&g_PAL3Data + 134) = 136;
  *((_WORD *)&g_PAL3Data + 135) = 137;
  *((_WORD *)&g_PAL3Data + 137) = 119;
  *((_WORD *)&g_PAL3Data + 138) = 138;
  *((_WORD *)&g_PAL3Data + 139) = 139;
  *((_WORD *)&g_PAL3Data + 140) = 140;
  *((_WORD *)&g_PAL3Data + 141) = 141;
  *((_WORD *)&g_PAL3Data + 142) = 142;
  *((_WORD *)&g_PAL3Data + 143) = 130;
  *((_WORD *)&g_PAL3Data + 144) = 132;
  *((_WORD *)&g_PAL3Data + 145) = 112;
  *((_WORD *)&g_PAL3Data + 146) = 114;
  *((_WORD *)&g_PAL3Data + 147) = 102;
  *((_WORD *)&g_PAL3Data + 148) = 107;
  *((_WORD *)&g_PAL3Data + 149) = 101;
  *((_WORD *)&g_PAL3Data + 150) = 130;
  *((_WORD *)&g_PAL3Data + 151) = 132;
  *((_WORD *)&g_PAL3Data + 152) = 128;
  return 132;
}

// 0x00406B80
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int PAL3::DefaultKeyMap(const char *a1, int a2, int a3)
{
  int v3; // eax
  bool v4; // zf
  char v5; // cl
  unsigned int v6; // esi
  char v7; // cl
  int v8; // ebx
  unsigned int v9; // edi
  int result; // eax
  unsigned int v11; // edi
  unsigned int v12; // kr04_4
  unsigned int v13; // ebx
  char *v14; // edi
  char v15; // al
  int v16; // [esp+0h] [ebp-Ch]

  g_Input.KeyInfo[180].CountMode = 1;
  if ( a1 )
  {
    v12 = strlen(a1) + 1;
    v13 = v12 - 1;
    if ( std::string::max_size() < v12 - 1 )
      v16->_Xlen();
    v14 = (char *)*((_DWORD *)&g_PAL3Data + 1);
    if ( *((_DWORD *)&g_PAL3Data + 1) && (v15 = *(_BYTE *)(*((_DWORD *)&g_PAL3Data + 1) - 1)) != 0 && v15 != -1 )
    {
      if ( v12 == 1 )
      {
        *(_BYTE *)(*((_DWORD *)&g_PAL3Data + 1) - 1) = v15 - 1;
        ((std *)&g_PAL3Data)->string::_Tidy(0);
        goto LABEL_43;
      }
    }
    else
    {
      if ( v12 == 1 )
      {
        ((std *)&g_PAL3Data)->string::_Tidy(1);
        goto LABEL_43;
      }
      if ( *((_DWORD *)&g_PAL3Data + 3) <= 0x1Fu && *((_DWORD *)&g_PAL3Data + 3) >= v13 )
      {
LABEL_42:
        qmemcpy(v14, a1, v13);
        result = *((_DWORD *)&g_PAL3Data + 1);
        *((_DWORD *)&g_PAL3Data + 2) = v12 - 1;
        *(_BYTE *)(*((_DWORD *)&g_PAL3Data + 1) + v13) = 0;
        goto LABEL_43;
      }
      ((std *)&g_PAL3Data)->string::_Tidy(1);
    }
    ((int)&g_PAL3Data)->GetKeyState(v13);
    v14 = (char *)*((_DWORD *)&g_PAL3Data + 1);
    goto LABEL_42;
  }
  v3 = *((_DWORD *)&g_PAL3Data + 1);
  v4 = *((_DWORD *)&g_PAL3Data + 1) == 0;
  if ( *((_DWORD *)&g_PAL3Data + 1) )
  {
    v5 = *(_BYTE *)(*((_DWORD *)&g_PAL3Data + 1) - 1);
    if ( v5 && v5 != -1 )
    {
      ((SceneObj *)&g_PAL3Data)->Update(*((unsigned int *)&g_PAL3Data + 2));
      v3 = *((_DWORD *)&g_PAL3Data + 1);
    }
    v4 = v3 == 0;
    if ( v3 )
    {
      *(_BYTE *)(v3 - 1) = -1;
      v3 = *((_DWORD *)&g_PAL3Data + 1);
      v4 = *((_DWORD *)&g_PAL3Data + 1) == 0;
    }
  }
  if ( v4 )
    v6 = 0;
  else
    v6 = *((_DWORD *)&g_PAL3Data + 2) + v3;
  if ( v3 )
  {
    v7 = *(_BYTE *)(v3 - 1);
    if ( v7 && v7 != -1 )
    {
      ((SceneObj *)&g_PAL3Data)->Update(*((unsigned int *)&g_PAL3Data + 2));
      v3 = *((_DWORD *)&g_PAL3Data + 1);
    }
    if ( v3 )
    {
      *(_BYTE *)(v3 - 1) = -1;
      v3 = *((_DWORD *)&g_PAL3Data + 1);
    }
  }
  v8 = v3;
  ((unsigned int *)&g_PAL3Data)->string::_Freeze();
  if ( v8 )
    v9 = v8 - *((_DWORD *)&g_PAL3Data + 1);
  else
    v9 = 0;
  if ( v6 )
    v6 -= v8;
  if ( *((_DWORD *)&g_PAL3Data + 2) < v9 )
    std::_Xran();
  ((int)&g_PAL3Data)->string::_Split();
  result = *((_DWORD *)&g_PAL3Data + 2);
  if ( *((_DWORD *)&g_PAL3Data + 2) - v9 < v6 )
    v6 = *((_DWORD *)&g_PAL3Data + 2) - v9;
  if ( v6 )
  {
    memcpy(
      (void *)(v9 + *((_DWORD *)&g_PAL3Data + 1)),
      (const void *)(v9 + *((_DWORD *)&g_PAL3Data + 1) + v6),
      *((_DWORD *)&g_PAL3Data + 2) - v6 - v9);
    v11 = *((_DWORD *)&g_PAL3Data + 2) - v6;
    LOBYTE(result) = ((SceneObj *)&g_PAL3Data)->Update(*((_DWORD *)&g_PAL3Data + 2) - v6);
    if ( (_BYTE)result )
    {
      result = *((_DWORD *)&g_PAL3Data + 1);
      *((_DWORD *)&g_PAL3Data + 2) = v11;
      *(_BYTE *)(*((_DWORD *)&g_PAL3Data + 1) + v11) = 0;
    }
  }
LABEL_43:
  dword_5833C4 = a2;
  dword_5833C8 = a3;
  return result;
}

// 0x00406D70
void PAL3::PrintScreen()
{
  int v0; // edi
  unsigned __int8 *Image; // ebx
  unsigned int v2; // eax
  unsigned __int8 *v3; // ebx
  char *v4; // edx
  unsigned __int8 *v5; // edi
  unsigned __int8 *v6; // eax
  _BYTE *v7; // ecx
  _BYTE *v8; // esi
  int v9; // edi
  int v10; // edx
  int v11; // ecx
  _BYTE *v12; // edx
  unsigned __int8 *v13; // ebx
  int v14; // edi
  int v15; // edx
  int v16; // esi
  unsigned int v17; // edx
  _BYTE *v18; // eax
  int v19; // edi
  int v20; // edx
  int v21; // esi
  _BYTE *v22; // eax
  int v23; // [esp+20h] [ebp-F0h] BYREF
  int v24; // [esp+24h] [ebp-ECh]
  int v25; // [esp+28h] [ebp-E8h]
  int v26; // [esp+2Ch] [ebp-E4h]
  int v27; // [esp+30h] [ebp-E0h]
  int v28; // [esp+34h] [ebp-DCh]
  char *v29; // [esp+38h] [ebp-D8h]
  int v30; // [esp+3Ch] [ebp-D4h] BYREF
  int v31; // [esp+40h] [ebp-D0h]
  _BYTE *v32; // [esp+F4h] [ebp-1Ch]
  int v33; // [esp+10Ch] [ebp-4h]

  if ( (*(int (**)(int, int *, int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 84))(
         g_Input.KeyInfo[177].Data,
         &v23,
         1) )
  {
    ((gbImage2D *)&v30)->gbImage2D();
    v33 = 0;
    if ( v25 != 3 )
    {
      if ( v25 == 8 )
      {
        v0 = 32;
LABEL_8:
        v28 = v0;
        Image = ((gbImage2D *)&v30)->CreateImage(v23, v24, v0);
        v31 = 0;
        v2 = v0 * v25 / 8;
        v3 = (unsigned __int8 *)&Image[v2 * (v26 - 1)];
        v4 = v29;
        if ( v26 > 0 )
        {
          do
          {
            qmemcpy(v3, v4, 4 * (v2 >> 2));
            v5 = (unsigned __int8 *)&v3[4 * (v2 >> 2)];
            v3 -= v2;
            qmemcpy(v5, &v4[4 * (v2 >> 2)], v2 & 3);
            v4 += v28;
            ++v31;
          }
          while ( v31 < v26 );
          v0 = v30;
        }
        (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 88))(g_Input.KeyInfo[177].Data);
        ((gbImage2D *)(&g_PAL3Data + 24))->Release();
        v6 = ((gbImage2D *)(&g_PAL3Data + 24))->CreateImage(v26, v27, 24);
        v7 = v32;
        v8 = v32;
        if ( v0 == 32 )
        {
          v9 = 0;
          if ( v24 > 0 )
          {
            v10 = v23;
            do
            {
              v11 = 0;
              if ( v10 > 0 )
              {
                do
                {
                  v12 = v8;
                  v13 = v6;
                  v8 += 4;
                  v6 += 3;
                  ++v11;
                  *(_WORD *)v13 = *(_WORD *)v12;
                  v13[2] = v12[2];
                  v10 = v23;
                }
                while ( v11 < v23 );
              }
              ++v9;
            }
            while ( v9 < v24 );
          }
        }
        else if ( v25 == 9 )
        {
          v14 = 0;
          if ( v24 > 0 )
          {
            v15 = v23;
            do
            {
              v16 = 0;
              if ( v15 > 0 )
              {
                do
                {
                  LOBYTE(v15) = *v7;
                  v7 += 2;
                  * v6 = (*)8 * v15;
                  LOWORD(v15) = *((_WORD *)v7 - 1);
                  v17 = (unsigned int)v15 >> 2;
                  v18 = (_BYTE *)v6 + 1;
                  * v18 = (*)v17 & 0xF8;
                  LOWORD(v17) = *((_WORD *)v7 - 1);
                  *++v18 = (v17 >> 7) & 0xF8;
                  v15 = v23;
                  v6 = (unsigned __int8 *)v18 + 1;
                  ++v16;
                }
                while ( v16 < v23 );
              }
              ++v14;
            }
            while ( v14 < v24 );
          }
        }
        else
        {
          v19 = 0;
          if ( v24 > 0 )
          {
            v20 = v23;
            do
            {
              v21 = 0;
              if ( v20 > 0 )
              {
                do
                {
                  LOBYTE(v20) = *v7;
                  v7 += 2;
                  * v6 = (*)8 * v20;
                  LOWORD(v20) = *((_WORD *)v7 - 1);
                  v22 = (_BYTE *)v6 + 1;
                  *v22++ = ((unsigned int)v20 >> 3) & 0xFC;
                  * v22 = (*)*(v7 - 1) & 0xF8;
                  v20 = v23;
                  v6 = (unsigned __int8 *)v22 + 1;
                  ++v21;
                }
                while ( v21 < v23 );
              }
              ++v19;
            }
            while ( v19 < v24 );
          }
        }
        if ( dword_5833C4 != -1 && dword_5833C8 != -1 )
          ((gbImage2D *)(&g_PAL3Data + 24))->ScaleTo(dword_5833C4, dword_5833C8);
        ((gbImage2D *)&v30)->Release();
        goto LABEL_34;
      }
      if ( v25 != 9 )
      {
        (*(void (**)(int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 88))(g_Input.KeyInfo[177].Data);
LABEL_34:
        v33 = -1;
        ((gbImage2D *)&v30)->~gbImage2D();
        return;
      }
    }
    v0 = 16;
    goto LABEL_8;
  }
}

// 0x00406FF0
int PAL3::SnapScreen(int a1)
{
  float *p_y; // esi
  int (***v2)(_DWORD, _DWORD); // eax
  int result; // eax

  g_Input.KeyInfo[174].Data = 0;
  g_Input.KeyInfo[173].PressTime = a1;
  if ( a1 )
  {
    *(_DWORD *)(g_Input.KeyInfo[177].CountMode + 448) = 1;
    ((RoleSystem *)g_Input.KeyInfo[177].CountMode)->SetActive((int)&g_SceneMgr.m_npc[0].m_path.normal[83].y);
  }
  sub_4070A0(aSoftwareSoftst, (DWORD)aSGameA, 1);
  ((PalScriptMgr *)0x63u)->Destroy(0);
  p_y = (float *)&g_SceneMgr.m_npc[1].m_path.normal[78].y;
  do
  {
    sub_419AE0(p_y);
    p_y += 2176;
  }
  while ( (int)p_y < (int)&g_SceneMgr.m_npc[5].m_path.normal[58].y );
  ((ScriptSystem *)0)->Execute(1);
  g_Input.KeyInfo[177].PressTime = 7;
  v2 = (int (***)(_DWORD, _DWORD))((CGameData *)&g_GameData)->SetMode(0);
  result = (**v2)(v2, 0);
  g_Input.KeyInfo[176].CountMode = 0;
  return result;
}

// 0x00407180
char PAL3::StartWolf(HKEY hKey, CHAR *lpSubKey)
{
  if ( RegOpenKeyExA(hKey, lpSubKey, 0, 0x20019u, (PHKEY)&lpSubKey) )
  {
    RegCloseKey((HKEY)lpSubKey);
    return 0;
  }
  else
  {
    RegCloseKey((HKEY)lpSubKey);
    return 1;
  }
}

// 0x004071C0
void PAL3::EndWolf(int a1)
{
  float *p_z; // esi
  void (***v2)(_DWORD, int); // eax
  int *v3; // eax
  int *Instance; // eax
  _DWORD *v5; // [esp-4h] [ebp-18h]
  _DWORD *v6; // [esp-4h] [ebp-18h]
  _DWORD v7[5]; // [esp+0h] [ebp-14h]
  void *retaddr; // [esp+14h] [ebp+0h]

  p_z = (float *)&g_SceneMgr.m_npc[1].m_path.normal[183].z;
  do
  {
    RoleSystemNotify((int)(p_z - 316));
    *(_DWORD *)p_z = 2;
    p_z += 2176;
  }
  while ( (int)p_z < (int)&g_SceneMgr.m_npc[5].m_path.normal[163].z );
  if ( g_Input.KeyInfo[173].PressTime )
  {
    v7[0] = 0;
    if ( a1 == -1 )
      g_Input.KeyInfo[174].Data = (int)((PalScriptMgr *)0x5Fu)->Destroy(v7[0]);
    else
      g_Input.KeyInfo[174].Data = (int)((PalScriptMgr *)0x60u)->Destroy(v7[0]);
  }
  else
  {
    g_Input.KeyInfo[177].PressTime = 2;
    v2 = (void (***)(_DWORD, int))((CGameData *)&g_GameData)->SetMode(0);
    (**v2)(v2, 1);
    if ( retaddr == (void *)-1 )
    {
      v6 = ((PalScriptMgr *)0x61u)->Destroy(0);
      Instance = (int *)SoundContext::GetInstance();
      CScreenMode_SetResolution(Instance, 0, (int)v6);
    }
    else
    {
      v5 = ((PalScriptMgr *)0x62u)->Destroy(0);
      v3 = (int *)SoundContext::GetInstance();
      CScreenMode_SetResolution(v3, 0, (int)v5);
      if ( g_Input.KeyInfo[175].HoldTime < 4u )
      {
        v7[0] = 80015;
        v7[1] = 83012;
        v7[2] = 8153;
        v7[3] = 8154;
        sub_42BEF0(v7[g_Input.KeyInfo[175].HoldTime]);
      }
      ++g_Input.KeyInfo[175].HoldTime;
    }
  }
}

// 0x004072D0
int PAL3::StartHideFight()
{
  int (***v0)(_DWORD, _DWORD); // eax

  g_Input.KeyInfo[177].PressTime = 8;
  g_Input.KeyInfo[176].CountMode = 0;
  v0 = (int (***)(_DWORD, _DWORD))((CGameData *)&g_GameData)->SetMode(0);
  return (**v0)(v0, 0);
}

// 0x00407300
int PAL3::EndHideFight()
{
  int (***v0)(_DWORD, int); // eax

  g_Input.KeyInfo[177].PressTime = 2;
  v0 = (int (***)(_DWORD, int))((CGameData *)&g_GameData)->SetMode(0);
  return (**v0)(v0, 1);
}

// 0x00407320
char PAL3::StartCombat(int a1, int a2, int a3, char a4)
{
  char result; // al
  int v5; // ebx
  RoleSystem *v6; // eax
  int RolePtr; // esi
  int v8; // edi
  __int64 v9; // rax
  int v10; // ecx
  int v11; // esi
  int i; // eax
  int v13; // edi
  const char *v14; // eax
  char *v15; // esi
  char *Instance; // eax
  int v17; // [esp+0h] [ebp-11Ch] BYREF
  char Buffer[256]; // [esp+Ch] [ebp-110h] BYREF
  int *v19; // [esp+10Ch] [ebp-10h]
  int v20; // [esp+118h] [ebp-4h]

  v20 = 0;
  v19 = (int *)&v17;
  result = PAL3::UIPostProcess();
  v5 = *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132];
  if ( *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132] )
  {
    v6 = (RoleSystem *)UISceneUpdate();
    RolePtr = v6->GetRolePtr(*(_DWORD *)(v5 + 628));
    v8 = (__int64)((*(float *)(v5 + 4) - *(float *)(RolePtr + 128)) / *(float *)&g_Input.KeyInfo[171].HoldTime);
    v9 = (__int64)((*(float *)(v5 + 12) - *(float *)(RolePtr + 136)) / *(float *)&g_Input.KeyInfo[171].HoldTime);
    if ( v8 < 0 || (v10 = *(_DWORD *)(RolePtr + 152), v8 >= v10) || (int)v9 < 0 || (int)v9 >= *(_DWORD *)(RolePtr + 156) )
      v11 = 2;
    else
      v11 = *(unsigned __int8 *)(*(_DWORD *)(RolePtr + 160) + 8 * (v8 + v9 * v10) + 5);
    for ( i = 0; i < 6; ++i )
      *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[4 * i + 152] = *(_DWORD *)(a1 + 4 * i);
    v13 = UISceneUpdate();
    v14 = (const char *)UISceneUpdate();
    sprintf(Buffer, "%s_%s", v14, (const char *)(v13 + 32));
    ((PalScript *)&stru_BFAB60)->SetDirectory(Buffer);
    sprintf(Buffer, "%d", v11);
    if ( !sub_431C10(&stru_BFAB60, Buffer, &g_SceneMgr.m_npc[6].m_actor.m_szTexture[184], 32) )
      sub_431C10(&stru_BFAB60, aDefault, &g_SceneMgr.m_npc[6].m_actor.m_szTexture[184], 32);
    ((PalScript *)&stru_BFAB60)->SetDirectory(dir);
    if ( sub_431C10(&stru_BFAB60, &g_SceneMgr.m_npc[6].m_actor.m_szTexture[184], Buffer, 256) )
      *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[216] = atoi(Buffer);
    else
      *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[216] = 1;
    if ( a2 == 1 )
      *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[220] = 2;
    else
      *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[220] = a2 == 2;
    *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[236] = a3;
    g_SceneMgr.m_npc[6].m_actor.m_szTexture[233] = a4;
    result = ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->ProcMagicWait((int)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[152], 0);
    if ( result )
    {
      if ( !a4 || !CScreenMode::GetInstance()[4] )
      {
        v15 = (char *)UISceneUpdate();
        Instance = (char *)CScreenMode::GetInstance();
        sub_53E680((int)Instance, v15);
      }
      return CGameData_Load((int)&g_GameData, 6);
    }
  }
  return result;
}

// 0x00407560
char PAL3::StartCombat(const void *a1, int a2, int a3)
{
  _BYTE v4[28]; // [esp+Ch] [ebp-220h] BYREF
  int v5; // [esp+28h] [ebp-204h]
  char v6[4]; // [esp+2Ch] [ebp-200h] BYREF
  int v7; // [esp+4Ch] [ebp-1E0h]
  int v8; // [esp+50h] [ebp-1DCh]
  char v9; // [esp+54h] [ebp-1D8h]
  int v10; // [esp+58h] [ebp-1D4h]
  char v11; // [esp+5Ch] [ebp-1D0h]
  char v12; // [esp+5Eh] [ebp-1CEh]
  int v13; // [esp+60h] [ebp-1CCh]
  _DWORD v14[114]; // [esp+64h] [ebp-1C8h] BYREF

  v9 = 0;
  v5 = 0x7FFFFFFF;
  strcpy(v6, aZ27);
  v7 = 1;
  v12 = 1;
  v10 = -1;
  v8 = 0;
  v13 = 0;
  v11 = 0;
  qmemcpy(v14, a1, sizeof(v14));
  if ( BYTE1(g_SceneMgr.m_npc[5].m_path.normal[130].y) )
    LOBYTE(v14[32]) = 6;
  PAL3::UpdateSubsystems();
  return ((int)v4)->StartCombat(a2, a3, 0);
}

// 0x00407640
char PAL3::EntryCatchGhost()
{
  int v0; // esi
  int *i; // edi
  int v3; // esi
  RoleSystem *v4; // eax
  int RolePtr; // edi
  int v6; // ebx
  int v7; // [esp-8h] [ebp-2Ch]
  int v8; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+Ch] [ebp-18h]
  int v10; // [esp+10h] [ebp-14h]
  int v11; // [esp+14h] [ebp-10h] BYREF
  int v12; // [esp+18h] [ebp-Ch]
  int v13; // [esp+1Ch] [ebp-8h]
  int v14; // [esp+20h] [ebp-4h]

  v0 = 0;
  if ( aQ01->ProcessInput(0) )
  {
    v8 = 6308;
    v9 = 6309;
    v10 = 6310;
    v12 = 0;
    v13 = 0;
    for ( i = &v8; ; ++i )
    {
      v11 = *i;
      if ( CCBStageRole_GetByIndex(&g_SceneMgr.m_npc[0].m_path.normal[79].y, &v11) )
        break;
      if ( ++v0 >= 3 )
        return 0;
    }
  }
  else
  {
    v3 = *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132];
    v7 = *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132] + 628);
    v4 = (RoleSystem *)UISceneUpdate();
    RolePtr = v4->GetRolePtr(v7);
    v6 = (__int64)((*(float *)(v3 + 4) - *(float *)(RolePtr + 128)) / *(float *)&g_Input.KeyInfo[171].HoldTime);
    v9 = (__int64)((*(float *)(v3 + 12) - *(float *)(RolePtr + 136)) / *(float *)&g_Input.KeyInfo[171].HoldTime);
    v8 = v6;
    v11 = 23;
    v12 = 93;
    v13 = 30;
    v14 = 96;
    if ( !sub_426E80(&v11, &v8) )
      return 0;
  }
  return 1;
}

// 0x00407740
gbGfxManager * PAL3::IfHideFightSucceed(int a1)
{
  gbGfxManager *result; // eax
  char *Instance; // eax
  gbAudioManager *AudioManager; // eax

  result = (gbGfxManager *)(a1 - 2);
  if ( a1 == 2 )
  {
    if ( (g_nGameFlags & 1) != 0 )
    {
      Instance = (char *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
      AudioManager->DetachAll3D();
    }
    PAL3::UIPostProcess();
    RoleSystemNotify(*(int *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132]);
    UIQuadManager::GetInstance();
    return UIQuadManager_Reset();
  }
  return result;
}

// 0x00408BE0
int PAL3::InitSubsystems()
{
  _DWORD pRect[4]; // [esp+0h] [ebp-10h] BYREF

  pRect[0] = 0;
  pRect[1] = 0;
  pRect[2] = 40;
  pRect[3] = 32;
  ((UIWnd *)&g_SceneMgr.m_npc[5].m_path.normal[59])->Create(0, pRect, 0);
  ((UIScene *)&g_SceneMgr.m_npc[5].m_path.normal[59])->LoadResource(aUiSceneTiao);
  ((MvcViewport *)&g_SceneMgr.m_npc[5].m_path.normal[59].x)->SetController(1082130432);
  ((UIWnd *)&g_SceneMgr.m_npc[5].m_path.normal[59])->Destroy(0);
  ((UINote *)&g_Input.KeyInfo[182])->Create(1, (int)pRect, 0, aUiFlexNote_0);
  ((UIWnd *)&g_Input.KeyInfo[182])->SetState(1);
  dword_C042F8 = 1101838418;
  dword_C042FC = 0;
  dword_C04300 = -1038795408;
  dword_C04304 = -1037468958;
  dword_C04308 = 0;
  dword_C0430C = -1040166416;
  dword_C04310 = -1043495648;
  dword_C04314 = 0;
  dword_C04318 = -1030531316;
  dword_C0431C = 1105702418;
  dword_C04320 = 0;
  dword_C04324 = -1029309724;
  dword_C04328 = 1105702418;
  dword_C0432C = 0;
  dword_C04330 = -1024066844;
  return PAL3::FullInit();
}

// 0x00408FD0
int PAL3::FullInit()
{
  int *v0; // eax
  int *v1; // edx
  char *v2; // esi
  int *v3; // ebp
  const char *v4; // edi
  int y_low; // eax
  int i; // esi
  int RoleNum; // eax
  int *v8; // esi
  int v9; // edi
  int v10; // eax
  bool v11; // sf
  int v12; // ebp
  int v13; // eax
  void *v14; // edi
  int v15; // eax
  int j; // eax
  int *v17; // ecx
  int k; // eax
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int *v22; // esi
  int v23; // edi
  int v24; // eax
  int v25; // ebp
  int v26; // eax
  char *v27; // edi
  int v28; // eax
  char *v29; // eax
  int *v30; // ecx
  int HuaYing; // eax
  int m; // eax
  int v33; // ecx
  int v34; // edx
  int *v35; // esi
  int v36; // edi
  int v37; // eax
  int v38; // ebp
  int v39; // eax
  char *v40; // edi
  int v41; // eax
  char *v42; // eax
  int *v43; // edx
  int *v44; // esi
  int v45; // edi
  int v46; // eax
  int v47; // ebp
  int v48; // eax
  char *v49; // edi
  int v50; // eax
  char *v51; // eax
  int *v52; // ecx
  int *v53; // esi
  int v54; // edi
  int v55; // eax
  int v56; // ebp
  int v57; // eax
  char *v58; // edi
  int v59; // eax
  char *v60; // eax
  int *v61; // ecx
  int *v62; // esi
  int v63; // edi
  int v64; // eax
  int v65; // ebp
  int v66; // eax
  char *v67; // edi
  int v68; // eax
  char *v69; // eax
  int *v70; // ecx
  int v71; // eax
  int n; // eax
  int v73; // ecx
  int v74; // edx
  int *v75; // esi
  int v76; // edi
  int v77; // eax
  int v78; // ebp
  int v79; // eax
  void *v80; // edi
  int v81; // eax
  int ii; // eax
  int *v83; // ecx
  int *v84; // esi
  int v85; // edi
  int v86; // eax
  int v87; // ebp
  int v88; // eax
  void *v89; // edi
  int v90; // eax
  int jj; // eax
  int *v92; // ecx
  int *v93; // esi
  int v94; // edi
  int v95; // eax
  int v96; // ebp
  int v97; // eax
  void *v98; // edi
  int v99; // eax
  int kk; // eax
  int *v101; // ecx
  int *v102; // esi
  int v103; // edi
  int v104; // eax
  int v105; // ebp
  int v106; // eax
  void *v107; // edi
  int v108; // eax
  int mm; // eax
  int *v110; // ecx
  int v111; // ebp
  int nn; // eax
  int v113; // ecx
  int v114; // edx
  int *v115; // esi
  int v116; // edx
  int v117; // edi
  int v118; // eax
  char *v119; // ebp
  int v120; // edx
  int *i1; // eax
  int *v122; // edx
  int *v123; // esi
  int v124; // ebp
  int v125; // edx
  int v126; // eax
  int v127; // eax
  char *v128; // ebp
  int i3; // edi
  int v130; // eax
  int *i2; // eax
  int *v132; // ecx
  int *v133; // esi
  int v134; // ebp
  int v135; // edx
  int v136; // eax
  int v137; // eax
  char *v138; // ebp
  int i5; // edi
  int v140; // eax
  int *i4; // eax
  int *v142; // ecx
  int i6; // ecx
  int result; // eax
  int v145; // [esp+10h] [ebp-28h]
  char *v146; // [esp+10h] [ebp-28h]
  char *v147; // [esp+10h] [ebp-28h]
  char *v148; // [esp+10h] [ebp-28h]
  char *v149; // [esp+10h] [ebp-28h]
  char *v150; // [esp+10h] [ebp-28h]
  char *v151; // [esp+10h] [ebp-28h]
  char *v152; // [esp+10h] [ebp-28h]
  char *v153; // [esp+10h] [ebp-28h]
  char *v154; // [esp+10h] [ebp-28h]
  char *v155; // [esp+10h] [ebp-28h]
  char *v156; // [esp+10h] [ebp-28h]
  int v157; // [esp+10h] [ebp-28h]
  int v158; // [esp+10h] [ebp-28h]
  int v159; // [esp+14h] [ebp-24h]
  int v160; // [esp+14h] [ebp-24h]
  int pConfig; // [esp+18h] [ebp-20h] BYREF
  int v162; // [esp+1Ch] [ebp-1Ch]
  int v163; // [esp+20h] [ebp-18h]
  _DWORD v164[5]; // [esp+24h] [ebp-14h] BYREF

  memset(byte_DE5220, 0, 0x28u);
  if ( LODWORD(g_SceneMgr.m_npc[5].m_path.normal[130].x) )
  {
    (**(void (***)(_DWORD, int))LODWORD(g_SceneMgr.m_npc[5].m_path.normal[130].x))(
      LODWORD(g_SceneMgr.m_npc[5].m_path.normal[130].x),
      1);
    g_SceneMgr.m_npc[5].m_path.normal[130].x = 0.0;
  }
  memset(dword_C02050, 0, 0xA0u);
  v0 = dword_C02050;
  do
  {
    v0[1] = 1;
    *v0 = 10;
    v0[3] = 0;
    v0 += 4;
  }
  while ( (int)v0 < (int)&byte_C020F0 );
  dword_C02050[0] = 30;
  dword_C02060 = 30;
  dword_C0209C = 6701;
  dword_C02070 = 20;
  dword_C02080 = 20;
  dword_C020AC = 6702;
  dword_C020BC = 6703;
  dword_C020CC = 6704;
  dword_C020DC = 6705;
  dword_C020EC = 84018;
  g_SceneMgr.m_npc[5].m_path.normal[132].x = 0.0;
  g_SceneMgr.m_npc[5].m_path.normal[131].y = 0.0;
  CCBStageRole_Reset(&g_SceneMgr.m_npc[0].m_path.normal[79].y);
  g_SceneMgr.m_npc[0].m_path.normal[78].z = g_SceneMgr.m_npc[0].m_path.normal[78].y;
  dword_586158 = 35;
  v1 = g_RoleTeam2;
  do
  {
    * v1 = (*)*(v1 - 1);
    v1 += 4;
  }
  while ( (int)v1 < (int)&g_SceneMgr.m_info.cityname[24] );
  BYTE1(g_SceneMgr.m_npc[5].m_path.normal[130].y) = 0;
  memset(&g_Input.KeyInfo[196], 0, 0x20u);
  g_Input.KeyInfo[197].HoldTime = 31;
  g_SceneMgr.m_npc[5].m_path.normal[131].z = 0.0;
  memset(&g_SceneMgr.m_info.cityname[16], 0, 0x1B80u);
  v164[0] = dword_58619C;
  v164[1] = dword_586198;
  v164[2] = dword_586194;
  v164[3] = &dword_586190;
  v164[4] = dword_58618C;
  v145 = 0;
  v2 = (char *)&g_SceneMgr.m_npc[0].m_path.normal[97].z + 2;
  v3 = v164;
  do
  {
    v4 = (const char *)*v3;
    ((Camera *)(v2 - 174))->SetParams(*v3);
    strncpy(v2, v4, 0x1Fu);
    *(_DWORD *)(v2 + 1090) = 1;
    *(_DWORD *)(v2 + 1086) = 1;
    *(_DWORD *)(v2 + 458) = 0;
    *(v2 - 1) = -1;
    *(v2 - 2) = v145;
    v2 += 8704;
    ++v3;
    ++v145;
  }
  while ( (int)v2 < (int)((char *)&g_SceneMgr.m_npc[5].m_path.normal[72].z + 2) );
  ((Camera *)dword_C020F8)->SetParams((int)"109");
  byte_C021A4 = 5;
  y_low = LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].y);
  strcpy(byte_C021A6, "109");
  dword_C025E8 = 0;
  dword_C02370 = 0;
  dword_C02374 = 1;
  byte_C021A5 = -1;
  y_low->SetParams();
  ((Camera *)dword_BFFDB0)->SetParams((int)"DXD");
  strcpy(byte_BFFE5E, "DXD");
  dword_C002A0 = 1;
  dword_C00028 = 0;
  ((Camera *)&g_Input.KeyInfo[198])->SetParams((int)&off_586180);
  strcpy((char *)&g_Input.KeyInfo[208].PressTime + 2, (const char *)&off_586180);
  dword_BFE0A0 = 1;
  g_Input.KeyInfo[237].CountMode = 0;
  ((int)&g_SceneMgr.m_npc[0].m_path.normal[83].y)->Init();
  g_SceneMgr.m_npc[5].m_path.normal[131].x = 0.0;
  ((RoleSystem *)g_Input.KeyInfo[177].CountMode)->SetActive((int)&g_SceneMgr.m_npc[0].m_path.normal[83].y);
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[82].z) = 1;
  LOBYTE(g_SceneMgr.m_npc[0].m_path.normal[83].x) = 0;
  g_SceneMgr.m_npc[0].m_actor.m_szTexture[30] = 3;
  BYTE2(g_SceneMgr.m_npc[0].m_path.points[67].z) = 5;
  BYTE2(g_SceneMgr.m_npc[0].m_path.points[185].x) = 1;
  BYTE2(g_SceneMgr.m_npc[0].m_path.length[137]) = 2;
  BYTE2(g_SceneMgr.m_npc[0].m_path.normal[77].z) = 4;
  dword_C01FB0[0] = 1058642330;
  dword_C01FB4 = 1061997773;
  dword_C01FB8 = 1053609165;
  dword_C01FBC = 1053609165;
  dword_C01FC0 = 1053609165;
  dword_C01FC4 = 1053609165;
  dword_C01FC8 = 1045220557;
  dword_C01FCC = 1045220557;
  dword_C01FD0 = 1053609165;
  dword_C01FD4 = 1053609165;
  dword_C01FD8 = 1028443341;
  dword_C01FDC = 1045220557;
  dword_C01FE0 = 1028443341;
  dword_C01FE4 = 1036831949;
  dword_C01FE8 = 1028443341;
  dword_C01FEC = 1053609165;
  dword_C01FF0 = 1053609165;
  dword_C01FF4 = 1061997773;
  dword_C01FF8 = 1058642330;
  dword_C01FFC = 1053609165;
  dword_C02000 = 1045220557;
  dword_C02004 = 1036831949;
  dword_C02008 = 1036831949;
  dword_C0200C = 1053609165;
  dword_C02010 = 1045220557;
  dword_C02014 = 1063675494;
  dword_C02018 = 1065353216;
  qmemcpy(&dword_C0201C, "fff?fff?fff?", 12);
  dword_C02028 = 1045220557;
  dword_C0202C = 1036831949;
  dword_C02030 = 1036831949;
  dword_C02034 = 1045220557;
  dword_C02038 = 1053609165;
  dword_C0203C = 1028443341;
  dword_C02040 = 1028443341;
  dword_C02044 = 1045220557;
  dword_C02048 = 1036831949;
  dword_C0204C = 1028443341;
  for ( i = 0; i < 5; ++i )
  {
    i->Create();
    i->Init();
  }
  memset32(dword_C04334, 20, 6u);
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[24] = 2224;
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[25] = 10;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[11].x = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[11].y = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[11].z = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[12].x = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[12].y = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[12].z = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[13].x = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[13].y = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[13].z = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[14].x = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[14].y = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[14].z = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[15].x = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[15].y = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[15].z = 0.0;
  g_SceneMgr.m_npc[0].m_npcinfo.noturn = 0;
  g_SceneMgr.m_npc[0].m_npcinfo.loopact = 0;
  g_SceneMgr.m_npc[0].m_npcinfo.speed = 0;
  pConfig = 301;
  v162 = 0;
  RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(301);
  v8 = (int *)g_RoleTeam2[0];
  v163 = RoleNum;
  if ( (dword_C0435C - g_RoleTeam2[0]) / 12 )
  {
    ((void *)g_RoleTeam2[0])->Insert((void *)g_RoleTeam2[0], (void *)(g_RoleTeam2[0] + 12));
    ((void *)g_RoleTeam2[0])->Erase(1 - (g_RoleTeam2[0] - (int)v8) / 12, &pConfig);
    for ( j = g_RoleTeam2[0]; v8 != (int *)j; v17[2] = v163 )
    {
      v17 = v8;
      v8 += 3;
      *v17 = pConfig;
      v17[1] = v162;
    }
    g_RoleTeam2[0] += 12;
  }
  else
  {
    if ( (unsigned int)((Array *)&dword_C04350)->Size() <= 1 )
      v9 = 1;
    else
      v9 = ((Array *)&dword_C04350)->Size();
    v10 = ((Array *)&dword_C04350)->Size();
    v11 = v9 + v10 < 0;
    v12 = v9 + v10;
    v13 = v9 + v10;
    if ( v11 )
      v13 = 0;
    v14 = (void *)((operator *)12 * v13)->new();
    v146 = (char *)g_RoleTeam1->Insert(v8, v14);
    v146->Erase(1, &pConfig);
    v8->Insert((void *)g_RoleTeam2[0], v146 + 12);
    nullsub_2(g_RoleTeam1, g_RoleTeam2[0]);
    operator delete(g_RoleTeam1);
    dword_C0435C = (int)v14 + 12 * v12;
    v15 = ((Array *)&dword_C04350)->Size();
    g_RoleTeam1 = v14;
    g_RoleTeam2[0] = (int)v14 + 12 * v15 + 12;
  }
  g_SceneMgr.m_npc[0].m_npcinfo.path.pt[1].z = 0.0;
  *(_DWORD *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[16] = 1;
  *(_DWORD *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[20] = ((Role *)0)->CreateXueJian(1);
  *(_DWORD *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[24] = ((Role *)0)->CreateLongKui(*(int *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[16]);
  *(_DWORD *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[28] = ((Role *)0)->CreateZiXuan(*(int *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[16]);
  LODWORD(g_SceneMgr.m_npc[0].m_npcinfo.face) = ((Role *)0)->CreateChangQing(*(int *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[16]);
  g_SceneMgr.m_npc[0].m_npcinfo.onlayer = ((Role *)0)->CreateHuaYing(*(int *)&g_SceneMgr.m_npc[0].m_npcinfo.mtl[16]);
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[17] = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_npcinfo.x) = 3;
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[19] = 3;
  g_SceneMgr.m_npc[0].m_npcinfo.initactive = 3;
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[20] = 3;
  g_SceneMgr.m_npc[0].m_npcinfo.initbeh = 3;
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[18] = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_npcinfo.z) = 2;
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[23] = 2;
  *(_DWORD *)g_SceneMgr.m_npc[0].m_npcinfo.initact = 2;
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[21] = 6;
  g_SceneMgr.m_npc[0].m_npcinfo.scriptid = 6;
  g_SceneMgr.m_npc[0].m_npcinfo.reserve[22] = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_npcinfo.y) = 1;
  ((RoleSystem *)&g_SceneMgr.m_info.cityname[16])->LoadData(1);
  for ( k = 972; k < 1020; k += 4 )
  {
    v19 = *(_DWORD *)&g_SceneMgr.m_info.cityname[k + 16];
    v20 = *(int *)((char *)&g_nSceneFlags + k);
    if ( v19 < v20 )
    {
      if ( v19 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_info.cityname[k + 16] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_info.cityname[k + 16] = v20;
    }
  }
  g_SceneMgr.m_npc[0].m_path.points[21].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[22].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[22].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[22].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[23].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[23].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[23].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[24].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[24].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[24].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[25].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[25].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[25].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[26].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[26].y = 0.0;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[26].z) = 82201;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[27].x) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[27].y) = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82201);
  pConfig = 321;
  v162 = 0;
  v21 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(321);
  v22 = (int *)end;
  v163 = v21;
  if ( (dword_C0436C - (int)end) / 12 )
  {
    end->Insert(end, (char *)end + 12);
    end->Erase(1 - ((_BYTE *)end - (_BYTE *)v22) / 12, &pConfig);
    v29 = (char *)end;
    if ( v22 != end )
    {
      do
      {
        v30 = v22;
        v22 += 3;
        *v30 = pConfig;
        v30[1] = v162;
        v30[2] = v163;
      }
      while ( v22 != (int *)v29 );
    }
    end = (char *)end + 12;
  }
  else
  {
    if ( (unsigned int)((Array *)&dword_C04360)->Size() <= 1 )
      v23 = 1;
    else
      v23 = ((Array *)&dword_C04360)->Size();
    v24 = ((Array *)&dword_C04360)->Size();
    v11 = v23 + v24 < 0;
    v25 = v23 + v24;
    v26 = v23 + v24;
    if ( v11 )
      v26 = 0;
    v27 = (char *)((operator *)12 * v26)->new();
    v147 = (char *)arr->Insert(v22, v27);
    v147->Erase(1, &pConfig);
    v22->Insert(end, v147 + 12);
    nullsub_2(arr, end);
    operator delete(arr);
    dword_C0436C = (int)&v27[12 * v25];
    v28 = ((Array *)&dword_C04360)->Size();
    arr = v27;
    end = &v27[12 * v28 + 12];
  }
  g_SceneMgr.m_npc[0].m_path.points[12].y = 0.0;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[3].y) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[3].z) = ((Role *)1)->CreateXueJian(1);
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[4].x) = ((Role *)1)->CreateLongKui(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[3].y));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[4].y) = ((Role *)1)->CreateZiXuan(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[3].y));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[4].z) = ((Role *)1)->CreateChangQing(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[3].y));
  HuaYing = ((Role *)1)->CreateHuaYing(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[3].y));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[34].x) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[6].x) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[34].z) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[6].z) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[5].x) = HuaYing;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[35].x) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[7].x) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[33].y) = 5;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[5].y) = 5;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[33].z) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[5].z) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[34].y) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[6].y) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[35].y) = 5;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[7].y) = 5;
  ((RoleSystem *)&g_SceneMgr.m_npc[0].m_actor.m_szTexture[32])->LoadData(1);
  for ( m = 972; m < 1020; m += 4 )
  {
    v33 = *(_DWORD *)&g_SceneMgr.m_npc[0].m_actor.m_szTexture[m + 32];
    v34 = *(_DWORD *)&g_SceneMgr.m_npc[0].m_actor.m_name[m + 244];
    if ( v33 < v34 )
    {
      if ( v33 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_npc[0].m_actor.m_szTexture[m + 32] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_npc[0].m_actor.m_szTexture[m + 32] = v34;
    }
  }
  g_SceneMgr.m_npc[0].m_path.points[139].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[139].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[139].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[140].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[140].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[140].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[141].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[141].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[141].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[142].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[142].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[142].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[143].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[143].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.points[143].z = 0.0;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[144].x) = 82101;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[144].y) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[144].z) = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82101);
  pConfig = 4301;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(4301);
  v35 = (int *)elem;
  if ( (dword_C0437C - (int)elem) / 12 )
  {
    elem->Insert(elem, (char *)elem + 12);
    elem->Erase(1 - ((_BYTE *)elem - (_BYTE *)v35) / 12, &pConfig);
    v42 = (char *)elem;
    if ( v35 != elem )
    {
      do
      {
        v43 = v35;
        v35 += 3;
        *v43 = pConfig;
        v43[1] = v162;
        v43[2] = v163;
      }
      while ( v35 != (int *)v42 );
    }
    elem = (char *)elem + 12;
  }
  else
  {
    if ( g_nSceneMode && (unsigned int)(((int)elem - g_nSceneMode) / 12) > 1 )
      v36 = ((Array *)&g_nSceneFlags)->Size();
    else
      v36 = 1;
    v37 = ((Array *)&g_nSceneFlags)->Size();
    v11 = v36 + v37 < 0;
    v38 = v36 + v37;
    v39 = v36 + v37;
    if ( v11 )
      v39 = 0;
    v40 = (char *)((operator *)12 * v39)->new();
    v148 = (char *)((void *)g_nSceneMode)->Insert(v35, v40);
    v148->Erase(1, &pConfig);
    v35->Insert(elem, v148 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v40[12 * v38];
    v41 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v40;
    elem = &v40[12 * v41 + 12];
  }
  pConfig = 4302;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(4302);
  v44 = (int *)elem;
  if ( (dword_C0437C - (int)elem) / 12 )
  {
    elem->Insert(elem, (char *)elem + 12);
    elem->Erase(1 - ((_BYTE *)elem - (_BYTE *)v44) / 12, &pConfig);
    v51 = (char *)elem;
    if ( v44 != elem )
    {
      do
      {
        v52 = v44;
        v44 += 3;
        *v52 = pConfig;
        v52[1] = v162;
        v52[2] = v163;
      }
      while ( v44 != (int *)v51 );
    }
    elem = (char *)elem + 12;
  }
  else
  {
    if ( g_nSceneMode && (unsigned int)(((int)elem - g_nSceneMode) / 12) > 1 )
      v45 = ((Array *)&g_nSceneFlags)->Size();
    else
      v45 = 1;
    v46 = ((Array *)&g_nSceneFlags)->Size();
    v11 = v45 + v46 < 0;
    v47 = v45 + v46;
    v48 = v45 + v46;
    if ( v11 )
      v48 = 0;
    v49 = (char *)((operator *)12 * v48)->new();
    v149 = (char *)((void *)g_nSceneMode)->Insert(v44, v49);
    v149->Erase(1, &pConfig);
    v44->Insert(elem, v149 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v49[12 * v47];
    v50 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v49;
    elem = &v49[12 * v50 + 12];
  }
  pConfig = 311;
  v162 = 2949123;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(311);
  v53 = (int *)elem;
  if ( (dword_C0437C - (int)elem) / 12 )
  {
    elem->Insert(elem, (char *)elem + 12);
    elem->Erase(1 - ((_BYTE *)elem - (_BYTE *)v53) / 12, &pConfig);
    v60 = (char *)elem;
    if ( v53 != elem )
    {
      do
      {
        v61 = v53;
        v53 += 3;
        *v61 = pConfig;
        v61[1] = v162;
        v61[2] = v163;
      }
      while ( v53 != (int *)v60 );
    }
    elem = (char *)elem + 12;
  }
  else
  {
    if ( g_nSceneMode && (unsigned int)(((int)elem - g_nSceneMode) / 12) > 1 )
      v54 = ((Array *)&g_nSceneFlags)->Size();
    else
      v54 = 1;
    v55 = ((Array *)&g_nSceneFlags)->Size();
    v11 = v54 + v55 < 0;
    v56 = v54 + v55;
    v57 = v54 + v55;
    if ( v11 )
      v57 = 0;
    v58 = (char *)((operator *)12 * v57)->new();
    v150 = (char *)((void *)g_nSceneMode)->Insert(v53, v58);
    v150->Erase(1, &pConfig);
    v53->Insert(elem, v150 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v58[12 * v56];
    v59 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v58;
    elem = &v58[12 * v59 + 12];
  }
  pConfig = 312;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(312);
  v62 = (int *)elem;
  if ( (dword_C0437C - (int)elem) / 12 )
  {
    elem->Insert(elem, (char *)elem + 12);
    elem->Erase(1 - ((_BYTE *)elem - (_BYTE *)v62) / 12, &pConfig);
    v69 = (char *)elem;
    if ( v62 != elem )
    {
      do
      {
        v70 = v62;
        v62 += 3;
        *v70 = pConfig;
        v70[1] = v162;
        v70[2] = v163;
      }
      while ( v62 != (int *)v69 );
    }
    elem = (char *)elem + 12;
  }
  else
  {
    if ( g_nSceneMode && (unsigned int)(((int)elem - g_nSceneMode) / 12) > 1 )
      v63 = ((Array *)&g_nSceneFlags)->Size();
    else
      v63 = 1;
    v64 = ((Array *)&g_nSceneFlags)->Size();
    v11 = v63 + v64 < 0;
    v65 = v63 + v64;
    v66 = v63 + v64;
    if ( v11 )
      v66 = 0;
    v67 = (char *)((operator *)12 * v66)->new();
    v151 = (char *)((void *)g_nSceneMode)->Insert(v62, v67);
    v151->Erase(1, &pConfig);
    v62->Insert(elem, v151 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v67[12 * v65];
    v68 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v67;
    elem = &v67[12 * v68 + 12];
  }
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[120].z) = 14;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[129].z) = 5594;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[121].x) = ((Role *)2)->CreateXueJian(14);
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[121].y) = ((Role *)2)->CreateLongKui(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[120].z));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[121].z) = ((Role *)2)->CreateZiXuan(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[120].z));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[122].x) = ((Role *)2)->CreateChangQing(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[120].z));
  v71 = ((Role *)2)->CreateHuaYing(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[120].z));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[152].x) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[124].x) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[122].y) = v71;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[152].y) = 6;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[124].y) = 6;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[150].z) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[122].z) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[151].x) = 5;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[123].x) = 5;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[151].y) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[123].y) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[151].z) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[123].z) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[152].z) = 5;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[124].z) = 5;
  ((RoleSystem *)&g_SceneMgr.m_npc[0].m_path.points[68])->LoadData(1);
  for ( n = 972; n < 1020; n += 4 )
  {
    v73 = *(_DWORD *)((char *)&g_SceneMgr.m_npc[0].m_path.points[68].x + n);
    v74 = *(_DWORD *)((char *)&g_SceneMgr.m_npc[0].m_path.points[64].x + n);
    if ( v73 < v74 )
    {
      if ( v73 <= 0 )
        *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.points[68].x + n) = 0.0;
    }
    else
    {
      *(_DWORD *)((char *)&g_SceneMgr.m_npc[0].m_path.points[68].x + n) = v74;
    }
  }
  g_SceneMgr.m_npc[0].m_path.totallength = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[0] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[1] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[2] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[3] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[4] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[5] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[6] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[7] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[8] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[9] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[10] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[11] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[12] = 0.0;
  g_SceneMgr.m_npc[0].m_path.length[13] = 0.0;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[14]) = 82301;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[15]) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[16]) = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82301);
  pConfig = 4401;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(4401);
  v75 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((void *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((void *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v75) / 12, &pConfig);
    for ( ii = g_nSceneType; v75 != (int *)ii; v83[2] = v163 )
    {
      v83 = v75;
      v75 += 3;
      *v83 = pConfig;
      v83[1] = v162;
    }
    g_nSceneType += 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)((g_nSceneType - g_nSceneState) / 12) > 1 )
      v76 = ((Array *)&dword_C04380)->Size();
    else
      v76 = 1;
    v77 = ((Array *)&dword_C04380)->Size();
    v11 = v76 + v77 < 0;
    v78 = v76 + v77;
    v79 = v76 + v77;
    if ( v11 )
      v79 = 0;
    v80 = (void *)((operator *)12 * v79)->new();
    v152 = (char *)((void *)g_nSceneState)->Insert(v75, v80);
    v152->Erase(1, &pConfig);
    v75->Insert((void *)g_nSceneType, v152 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)v80 + 12 * v78;
    v81 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v80;
    g_nSceneType = (int)v80 + 12 * v81 + 12;
  }
  pConfig = 316;
  v162 = 2949123;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(316);
  v84 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((void *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((void *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v84) / 12, &pConfig);
    for ( jj = g_nSceneType; v84 != (int *)jj; v92[2] = v163 )
    {
      v92 = v84;
      v84 += 3;
      *v92 = pConfig;
      v92[1] = v162;
    }
    g_nSceneType += 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)((g_nSceneType - g_nSceneState) / 12) > 1 )
      v85 = (g_nSceneType - g_nSceneState) / 12;
    else
      v85 = 1;
    v86 = ((Array *)&dword_C04380)->Size();
    v11 = v85 + v86 < 0;
    v87 = v85 + v86;
    v88 = v85 + v86;
    if ( v11 )
      v88 = 0;
    v89 = (void *)((operator *)12 * v88)->new();
    v153 = (char *)((void *)g_nSceneState)->Insert(v84, v89);
    v153->Erase(1, &pConfig);
    v84->Insert((void *)g_nSceneType, v153 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)v89 + 12 * v87;
    v90 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v89;
    g_nSceneType = (int)v89 + 12 * v90 + 12;
  }
  pConfig = 317;
  v162 = 983043;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(317);
  v93 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((void *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((void *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v93) / 12, &pConfig);
    for ( kk = g_nSceneType; v93 != (int *)kk; v101[2] = v163 )
    {
      v101 = v93;
      v93 += 3;
      *v101 = pConfig;
      v101[1] = v162;
    }
    g_nSceneType += 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)((g_nSceneType - g_nSceneState) / 12) > 1 )
      v94 = (g_nSceneType - g_nSceneState) / 12;
    else
      v94 = 1;
    v95 = ((Array *)&dword_C04380)->Size();
    v11 = v94 + v95 < 0;
    v96 = v94 + v95;
    v97 = v94 + v95;
    if ( v11 )
      v97 = 0;
    v98 = (void *)((operator *)12 * v97)->new();
    v154 = (char *)((void *)g_nSceneState)->Insert(v93, v98);
    v154->Erase(1, &pConfig);
    v93->Insert((void *)g_nSceneType, v154 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)v98 + 12 * v96;
    v99 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v98;
    g_nSceneType = (int)v98 + 12 * v99 + 12;
  }
  pConfig = 318;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(318);
  v102 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((void *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((void *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v102) / 12, &pConfig);
    for ( mm = g_nSceneType; v102 != (int *)mm; v110[2] = v163 )
    {
      v110 = v102;
      v102 += 3;
      *v110 = pConfig;
      v110[1] = v162;
    }
    g_nSceneType += 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)((g_nSceneType - g_nSceneState) / 12) > 1 )
      v103 = (g_nSceneType - g_nSceneState) / 12;
    else
      v103 = 1;
    v104 = ((Array *)&dword_C04380)->Size();
    v11 = v103 + v104 < 0;
    v105 = v103 + v104;
    v106 = v103 + v104;
    if ( v11 )
      v106 = 0;
    v107 = (void *)((operator *)12 * v106)->new();
    v155 = (char *)((void *)g_nSceneState)->Insert(v102, v107);
    v155->Erase(1, &pConfig);
    v102->Insert((void *)g_nSceneType, v155 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)v107 + 12 * v105;
    v108 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v107;
    g_nSceneType = (int)v107 + 12 * v108 + 12;
  }
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[238].x) = 10;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[247].x) = 1943;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[238].y) = ((Role *)3)->CreateXueJian(10);
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[238].z) = ((Role *)3)->CreateLongKui(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[238].x));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[239].x) = ((Role *)3)->CreateZiXuan(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[238].x));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[239].y) = ((Role *)3)->CreateChangQing(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[238].x));
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[239].z) = ((Role *)3)->CreateHuaYing(SLODWORD(g_SceneMgr.m_npc[0].m_path.points[238].x));
  v111 = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[36]) = 6;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[240].z) = 6;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[34]) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[240].x) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[35]) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[240].y) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[37]) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[241].x) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[38]) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[241].y) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[39]) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[241].z) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.length[40]) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.points[242].x) = 2;
  ((RoleSystem *)&g_SceneMgr.m_npc[0].m_path.points[185].y)->LoadData(1);
  for ( nn = 972; nn < 1020; nn += 4 )
  {
    v113 = *(_DWORD *)((char *)&g_SceneMgr.m_npc[0].m_path.points[185].y + nn);
    v114 = *(_DWORD *)((char *)&g_SceneMgr.m_npc[0].m_path.points[181].y + nn);
    if ( v113 < v114 )
    {
      if ( v113 <= 0 )
        *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.points[185].y + nn) = 0.0;
    }
    else
    {
      *(_DWORD *)((char *)&g_SceneMgr.m_npc[0].m_path.points[185].y + nn) = v114;
    }
  }
  g_SceneMgr.m_npc[0].m_path.normal[31].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[32].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[32].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[32].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[33].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[33].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[33].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[34].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[34].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[34].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[35].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[35].y = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[35].z = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[36].x = 0.0;
  g_SceneMgr.m_npc[0].m_path.normal[36].y = 0.0;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[36].z) = 82001;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[37].x) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[37].y) = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82001);
  pConfig = 4501;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(4501);
  v115 = (int *)*(int **)&g_SceneMgr.m_info.cityname[8];
  if ( (*(_DWORD *)&g_SceneMgr.m_info.cityname[12] - *(_DWORD *)&g_SceneMgr.m_info.cityname[8]) / 12 )
  {
    ((Array *)*(void **)&g_SceneMgr.m_info.cityname[8])->Insert(*(void **)&g_SceneMgr.m_info.cityname[8], (void *)(*(_DWORD *)&g_SceneMgr.m_info.cityname[8] + 12));
    ((Array *)*(void **)&g_SceneMgr.m_info.cityname[8])->Erase(1 - (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - (int)v115) / 12, &pConfig);
    for ( i1 = *(int **)&g_SceneMgr.m_info.cityname[8]; v115 != i1; v122[2] = v163 )
    {
      v122 = v115;
      v115 += 3;
      *v122 = pConfig;
      v122[1] = v162;
    }
    *(_DWORD *)&g_SceneMgr.m_info.cityname[8] += 12;
  }
  else
  {
    if ( !*(_DWORD *)&g_SceneMgr.m_info.cityname[4] )
      goto LABEL_148;
    if ( (unsigned int)((*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12) > 1 )
      v111 = (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12;
    if ( *(_DWORD *)&g_SceneMgr.m_info.cityname[4] )
      v116 = (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12;
    else
LABEL_148:
      v116 = 0;
    v117 = v116 + v111;
    v118 = v116 + v111;
    if ( v116 + v111 < 0 )
      v118 = 0;
    v119 = (char *)((operator *)12 * v118)->new();
    v156 = (char *)((Array *)*(void **)&g_SceneMgr.m_info.cityname[4])->Insert(v115, v119);
    v156->Erase(1, &pConfig);
    v115->Insert(*(void **)&g_SceneMgr.m_info.cityname[8], v156 + 12);
    nullsub_2(*(_DWORD *)&g_SceneMgr.m_info.cityname[4], *(_DWORD *)&g_SceneMgr.m_info.cityname[8]);
    operator delete(*(void **)&g_SceneMgr.m_info.cityname[4]);
    *(_DWORD *)&g_SceneMgr.m_info.cityname[12] = &v119[12 * v117];
    if ( *(_DWORD *)&g_SceneMgr.m_info.cityname[4] )
      v120 = (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12;
    else
      v120 = 0;
    *(_DWORD *)&g_SceneMgr.m_info.cityname[4] = v119;
    *(_DWORD *)&g_SceneMgr.m_info.cityname[8] = &v119[12 * v120 + 12];
  }
  pConfig = 306;
  v162 = 2949123;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(306);
  v123 = (int *)*(int **)&g_SceneMgr.m_info.cityname[8];
  if ( (*(_DWORD *)&g_SceneMgr.m_info.cityname[12] - *(_DWORD *)&g_SceneMgr.m_info.cityname[8]) / 12 )
  {
    ((Array *)*(void **)&g_SceneMgr.m_info.cityname[8])->Insert(*(void **)&g_SceneMgr.m_info.cityname[8], (void *)(*(_DWORD *)&g_SceneMgr.m_info.cityname[8] + 12));
    ((Array *)*(void **)&g_SceneMgr.m_info.cityname[8])->Erase(1 - (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - (int)v123) / 12, &pConfig);
    for ( i2 = *(int **)&g_SceneMgr.m_info.cityname[8]; v123 != i2; v132[2] = v163 )
    {
      v132 = v123;
      v123 += 3;
      *v132 = pConfig;
      v132[1] = v162;
    }
    *(_DWORD *)&g_SceneMgr.m_info.cityname[8] += 12;
  }
  else
  {
    if ( *(_DWORD *)&g_SceneMgr.m_info.cityname[4]
      && (unsigned int)((*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12) > 1 )
    {
      v124 = (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12;
    }
    else
    {
      v124 = 1;
    }
    if ( *(_DWORD *)&g_SceneMgr.m_info.cityname[4] )
      v125 = (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12;
    else
      v125 = 0;
    v126 = v125 + v124;
    v157 = v125 + v124;
    if ( v125 + v124 < 0 )
      v126 = 0;
    v127 = ((operator *)12 * v126)->new();
    v128 = (char *)*(char **)&g_SceneMgr.m_info.cityname[4];
    v159 = v127;
    for ( i3 = v127; v128 != (char *)v123; i3 += 12 )
    {
      ((void *)i3)->Copy(v128);
      v128 += 12;
    }
    ((void *)i3)->Erase(1, &pConfig);
    v123->Insert(*(void **)&g_SceneMgr.m_info.cityname[8], (void *)(i3 + 12));
    nullsub_2(*(_DWORD *)&g_SceneMgr.m_info.cityname[4], *(_DWORD *)&g_SceneMgr.m_info.cityname[8]);
    operator delete(*(void **)&g_SceneMgr.m_info.cityname[4]);
    *(_DWORD *)&g_SceneMgr.m_info.cityname[12] = v159 + 12 * v157;
    v130 = ((int *)g_SceneMgr.m_info.cityname)->Size();
    *(_DWORD *)&g_SceneMgr.m_info.cityname[4] = v159;
    *(_DWORD *)&g_SceneMgr.m_info.cityname[8] = v159 + 12 * (v130 + 1);
  }
  pConfig = 307;
  v162 = 983043;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(307);
  v133 = (int *)*(int **)&g_SceneMgr.m_info.cityname[8];
  if ( (*(_DWORD *)&g_SceneMgr.m_info.cityname[12] - *(_DWORD *)&g_SceneMgr.m_info.cityname[8]) / 12 )
  {
    ((Array *)*(void **)&g_SceneMgr.m_info.cityname[8])->Insert(*(void **)&g_SceneMgr.m_info.cityname[8], (void *)(*(_DWORD *)&g_SceneMgr.m_info.cityname[8] + 12));
    ((Array *)*(void **)&g_SceneMgr.m_info.cityname[8])->Erase(1 - (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - (int)v133) / 12, &pConfig);
    for ( i4 = *(int **)&g_SceneMgr.m_info.cityname[8]; v133 != i4; v142[2] = v163 )
    {
      v142 = v133;
      v133 += 3;
      *v142 = pConfig;
      v142[1] = v162;
    }
    *(_DWORD *)&g_SceneMgr.m_info.cityname[8] += 12;
  }
  else
  {
    if ( *(_DWORD *)&g_SceneMgr.m_info.cityname[4]
      && (unsigned int)((*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12) > 1 )
    {
      v134 = (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12;
    }
    else
    {
      v134 = 1;
    }
    if ( *(_DWORD *)&g_SceneMgr.m_info.cityname[4] )
      v135 = (*(_DWORD *)&g_SceneMgr.m_info.cityname[8] - *(_DWORD *)&g_SceneMgr.m_info.cityname[4]) / 12;
    else
      v135 = 0;
    v136 = v135 + v134;
    v160 = v135 + v134;
    if ( v135 + v134 < 0 )
      v136 = 0;
    v137 = ((operator *)12 * v136)->new();
    v138 = (char *)*(char **)&g_SceneMgr.m_info.cityname[4];
    v158 = v137;
    for ( i5 = v137; v138 != (char *)v133; i5 += 12 )
    {
      ((void *)i5)->Copy(v138);
      v138 += 12;
    }
    ((void *)i5)->Erase(1, &pConfig);
    v133->Insert(*(void **)&g_SceneMgr.m_info.cityname[8], (void *)(i5 + 12));
    nullsub_2(*(_DWORD *)&g_SceneMgr.m_info.cityname[4], *(_DWORD *)&g_SceneMgr.m_info.cityname[8]);
    operator delete(*(void **)&g_SceneMgr.m_info.cityname[4]);
    *(_DWORD *)&g_SceneMgr.m_info.cityname[12] = v158 + 12 * v160;
    v140 = ((int *)g_SceneMgr.m_info.cityname)->Size();
    *(_DWORD *)&g_SceneMgr.m_info.cityname[4] = v158;
    *(_DWORD *)&g_SceneMgr.m_info.cityname[8] = v158 + 12 * (v140 + 1);
  }
  pConfig = 308;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(308);
  ((Scene *)&g_SceneMgr)->LoadConfig(&pConfig);
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[22].y) = 4341;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[13].y) = 13;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[13].z) = ((Role *)4)->CreateXueJian(13);
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[14].x) = ((Role *)4)->CreateLongKui(SLODWORD(g_SceneMgr.m_npc[0].m_path.normal[13].y));
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[14].y) = ((Role *)4)->CreateZiXuan(SLODWORD(g_SceneMgr.m_npc[0].m_path.normal[13].y));
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[14].z) = ((Role *)4)->CreateChangQing(SLODWORD(g_SceneMgr.m_npc[0].m_path.normal[13].y));
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[15].x) = ((Role *)4)->CreateHuaYing(SLODWORD(g_SceneMgr.m_npc[0].m_path.normal[13].y));
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[44].y) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[16].y) = 4;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[44].x) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[16].x) = 1;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[43].y) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[15].y) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[43].z) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[15].z) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[44].z) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[16].z) = 3;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[45].x) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[17].x) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[45].y) = 2;
  LODWORD(g_SceneMgr.m_npc[0].m_path.normal[17].y) = 2;
  ((RoleSystem *)&g_SceneMgr.m_npc[0].m_path.length[138])->LoadData(1);
  ((RoleSystem *)&g_SceneMgr.m_npc[0].m_path.length[138])->Init();
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[106].y) = 4101;
  g_SceneMgr.m_npc[5].m_path.normal[106].z = NAN;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[107].x) = 4102;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[107].y) = 4;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[107].z) = 4103;
  g_SceneMgr.m_npc[5].m_path.normal[108].x = NAN;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[108].y) = 4104;
  g_SceneMgr.m_npc[5].m_path.normal[108].z = NAN;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[109].x) = 4105;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[109].y) = 44;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[109].z) = 4106;
  g_SceneMgr.m_npc[5].m_path.normal[110].x = NAN;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[110].y) = 4201;
  g_SceneMgr.m_npc[5].m_path.normal[110].z = NAN;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[111].x) = 4202;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[111].y) = 15;
  g_SceneMgr.m_npc[5].m_path.normal[114].x = NAN;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[114].z) = 3;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[116].x) = 15;
  g_SceneMgr.m_npc[5].m_path.normal[117].y = NAN;
  g_SceneMgr.m_npc[5].m_path.normal[118].x = NAN;
  g_SceneMgr.m_npc[5].m_path.normal[119].y = NAN;
  g_SceneMgr.m_npc[5].m_path.normal[122].x = NAN;
  g_SceneMgr.m_npc[5].m_path.normal[126].x = NAN;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[120].x) = 13;
  memset(&g_SceneMgr.m_npc[5].m_path.normal[73], 0, 0x190u);
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[111].z) = 4203;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[112].x) = 20;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[112].y) = 4204;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[112].z) = 55;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[113].x) = 4205;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[113].y) = 50;
  g_SceneMgr.m_npc[5].m_path.normal[113].z = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[114].y) = 4301;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[115].x) = 4302;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[115].y) = 10;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[115].z) = 4303;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[116].y) = 4304;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[116].z) = 20;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[117].x) = 4305;
  g_SceneMgr.m_npc[5].m_path.normal[117].z = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[118].y) = 4401;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[118].z) = 4;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[119].x) = 4402;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[119].z) = 4403;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[120].y) = 4404;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[120].z) = 35;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[121].x) = 4405;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[121].y) = 58;
  g_SceneMgr.m_npc[5].m_path.normal[121].z = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[122].y) = 4501;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[122].z) = 8;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[123].x) = 4502;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[123].y) = 24;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[123].z) = 4503;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[124].x) = 38;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[124].y) = 4504;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[124].z) = 50;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[125].x) = 4505;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[125].y) = 64;
  g_SceneMgr.m_npc[5].m_path.normal[125].z = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[73].x) = 301;
  g_SceneMgr.m_npc[5].m_path.normal[74].x = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[73].z) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[74].y) = 302;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[75].y) = 4;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[75].x) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[75].z) = 303;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[76].z) = 5;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[76].y) = 15;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[77].x) = 304;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[78].x) = 20;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[77].z) = 50;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[78].y) = 305;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[79].y) = 30;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[79].x) = 60;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[79].z) = 321;
  g_SceneMgr.m_npc[5].m_path.normal[80].z = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[80].y) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[81].x) = 322;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[82].x) = 5;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[81].z) = 30;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[82].y) = 323;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[83].y) = 14;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[83].x) = 15;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[83].z) = 324;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[84].z) = 23;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[84].y) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[85].x) = 325;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[96].y) = 30;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[86].x) = 32;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[85].z) = 50;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[86].y) = 311;
  g_SceneMgr.m_npc[5].m_path.normal[87].y = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[87].x) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[87].z) = 312;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[88].z) = 5;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[88].y) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[89].x) = 313;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[90].x) = 15;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[89].z) = 15;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[90].y) = 314;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[91].y) = 25;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[91].x) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[91].z) = 315;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[92].z) = 35;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[92].y) = 60;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[93].x) = 316;
  g_SceneMgr.m_npc[5].m_path.normal[94].x = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[93].z) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[94].y) = 317;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[95].y) = 3;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[95].x) = 15;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[95].z) = 318;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[96].z) = 10;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[97].x) = 319;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[98].x) = 20;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[97].z) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[98].y) = 320;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[99].y) = 28;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[99].x) = 20;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[99].z) = 306;
  g_SceneMgr.m_npc[5].m_path.normal[100].z = 0.0;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[100].y) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[101].x) = 307;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[102].x) = 6;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[101].z) = 15;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[102].y) = 308;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[103].y) = 14;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[103].x) = 45;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[103].z) = 309;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[104].z) = 22;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[104].y) = 50;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[105].x) = 310;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[106].x) = 32;
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[105].z) = 60;
  NPC::InitAll();
  for ( i6 = 0; i6 < 5; ++i6 )
  {
    result = 1408 * i6;
    g_SceneMgr.m_npc[0].m_actor.m_szTexture[result + 25] = 0;
    g_SceneMgr.m_npc[0].m_actor.m_szTexture[result + 26] = 0;
    g_SceneMgr.m_npc[0].m_actor.m_szTexture[result + 27] = 0;
    g_SceneMgr.m_npc[0].m_actor.m_szTexture[result + 28] = 0;
    g_SceneMgr.m_npc[0].m_actor.m_szTexture[result + 29] = 1;
    g_SceneMgr.m_npc[0].m_actor.m_szTexture[result + 24] = 0;
    switch ( i6 )
    {
      case 0:
        *(_DWORD *)&g_SceneMgr.m_info.cityname[1408 * i6 + 16] = 101;
        break;
      case 1:
        *(_DWORD *)&g_SceneMgr.m_info.cityname[1408 * i6 + 16] = 104;
        break;
      case 2:
        *(_DWORD *)&g_SceneMgr.m_info.cityname[1408 * i6 + 16] = 106;
        break;
      case 3:
        *(_DWORD *)&g_SceneMgr.m_info.cityname[1408 * i6 + 16] = 107;
        break;
      case 4:
        *(_DWORD *)&g_SceneMgr.m_info.cityname[1408 * i6 + 16] = 102;
        break;
      default:
        continue;
    }
  }
  g_Input.KeyInfo[194].Data = 50529027;
  g_Input.KeyInfo[194].HoldTime = 50529027;
  return result;
}

// 0x004118D0
int PAL3::UpdateSubsystems()
{
  int v1; // [esp+4h] [ebp+4h]
  int v2; // [esp+8h] [ebp+8h]
  int v3; // [esp+Ch] [ebp+Ch]
  int v4; // [esp+10h] [ebp+10h]
  int v5; // [esp+14h] [ebp+14h]
  _DWORD *v6; // [esp+18h] [ebp+18h]

  return sub_569020(v1, v2, v3, v4, v5, v6);
}

// 0x0041EE40
int PAL3::UIPostProcess()
{
  int result; // eax

  if ( *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[140] )
  {
    ((gbSound2DNode *)*(gbSound2DNode **)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[140])->Stop();
    *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[140] = 0;
  }
  return result;
}
