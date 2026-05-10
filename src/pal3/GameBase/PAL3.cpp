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
int sub_406B80(...);
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

  memset(&MEMORY[0xBFD6C8], 0, 0xB8u);
  g_bGameActive = 1;
  PAL3::TestCombat();
  g_pCBSystem = 0;
  g_pUIManager = 0;
  g_pEffMgr = 0;
  v0 = g_nGameFlags;
  MEMORY[0xA3A6EC] = 0;
  LOBYTE(v0) = g_nGameFlags & 0xF4 | 3;
  g_nGameFlags = v0;
  MEMORY[0xA3A6F0] = 0;
  return &unk_8ACBF0;
}

// 0x004047F0
// attributes: thunk
int PAL3::~PAL3()
{
  return PAL3::Destroy();
}

// 0x00404800
struct gbVFileSystem * PAL3::Create@<eax>(char *a1@<edi>, HINSTANCE hInstance)
{
  PalScript *v2; // ecx
  char *Instance; // eax
  HCURSOR CursorA; // eax
  HWND v5; // edi
  _BYTE *v6; // eax
  CCBSystem *v7; // eax
  CCBSystem *v8; // eax
  SceneMgr *v9; // eax
  char *v10; // ecx
  CGameData *v11; // eax
  _DWORD *v12; // eax
  RenderTarget3 *v13; // eax
  RenderTarget2 *v14; // eax
  RenderTarget4 *v15; // eax
  void *v16; // eax
  _DWORD *v17; // eax
  RenderTarget3 *v18; // eax
  RenderTarget2 *v19; // eax
  RenderTarget4 *v20; // eax
  void *v21; // eax
  gbGeomNode *v22; // eax
  gbGeomNode *v23; // esi
  gbGeomNode *v24; // ecx
  struct gbVFileSystem *v25; // eax
  struct gbVFileSystem *v26; // esi
  gbGeomNode *v27; // ecx
  int Width; // eax
  int v30; // [esp+Ch] [ebp-960h]
  int v31; // [esp+14h] [ebp-958h]
  struct gbVFileSystem *v32; // [esp+20h] [ebp-94Ch] BYREF
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
  PalScript::LoadFromFile(&stru_BFAB60, filename);
  (PalScript *->LoadScript()(&g_PAL3Data + 312), (int)aDatascriptLang);
  (PalScript *->SetAppName()(&g_PAL3Data + 312), aAppname);
  Instance = (char *)CScreenMode::GetInstance();
  (CScreenMode *->SetMode()Instance, v31);
  CursorA = LoadCursorA(hInstance, (LPCSTR)0x73);
  v5 = MEMORY[0xBFD774];
  g_pLogger = (Logger *)CursorA;
  ShowWindow(MEMORY[0xBFD774], 5);
  UpdateWindow(v5);
  if ( !GRPinput::Create(&g_Input, hInstance, (int)v5, 0) )
  {
    qmemcpy(
      pExceptionObject,
      (Logger *->FormatException()ArgList, aInputDeviceCre, aDProjectPal3Ga_0, 180),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  GRPinput::SetMouseLimits(&g_Input, 0, 0, MEMORY[0xBFD6D0], MEMORY[0xBFD6D4]);
  GRPinput::SetMode(&g_Input, 0x40000000);
  (CScreenMode *->InitCPK()&MEMORY[0xA3A7D8], 0, 1);
  memset(pParams, 0, sizeof(pParams));
  (CameraCtrl *->InitParams()g_pCamera, pParams);
  if ( !g_GDB->PAL_GDB() )
  {
    qmemcpy(
      pExceptionObject,
      (Logger *->FormatException()ArgList, aFightDatabaseL, aDProjectPal3Ga_0, 191),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (PAL_GDB *->LoadLanguage()(&g_PAL3Data + 328), path);
  PAL3::InitSubsystems();
  v6 = (_BYTE *)UIQuadManager::GetInstance();
  UIRenderQuadList(v6);
  (UIManager *->LoadShadowTexture()&g_SceneMgr.?[5].?.normal[220].y);
  (Logger *->RegisterCallbacks()g_Logger);
  (Logger *->Write()g_Logger, "%s Bulid %s %s", aV104, aJan52004, a163941);
  (Logger *->Write()g_Logger, aGameCreateOk);
  v7 = (CCBSystem *)operator new(0x162D8u);
  v38 = 0;
  if ( v7 )
    v8 = (CCBSystem *)v7->CCBSystem();
  else
    v8 = 0;
  g_pCBSystem = v8;
  v38 = -1;
  if ( !v8 )
  {
    qmemcpy(
      pExceptionObject,
      (Logger *->FormatException()ArgList, aCouldNotAlloca, aDProjectPal3Ga_0, 214),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v8->ProcNormalAttack();
  v9 = (SceneMgr *)operator new(0xA930u);
  v38 = 1;
  if ( v9 )
  {
    if ( g_pCamera )
      v10 = (char *)&g_pCamera->OrthoSize;
    else
      v10 = 0;
    v11 = (CGameData *)v9->Create((int)g_pGfxManager, (int)v10, 0);
  }
  else
  {
    v11 = 0;
  }
  v38 = -1;
  g_pGameData = v11;
  if ( !v11 )
  {
    qmemcpy(
      pExceptionObject,
      (Logger *->FormatException()ArgList, aCouldNotAlloca_0, aDProjectPal3Ga_0, 222),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( (_BYTE)g_pEffMgr )
  {
    if ( byte_5833C0 )
      (CGameData *->Init()&g_GameData);
    v17 = (_DWORD *)CRenderTarget::GetInstance();
    v17->Create();
    v18 = (RenderTarget3 *)RenderTarget3::GetInstance();
    v18->Init();
    v19 = (RenderTarget2 *)CRenderTarget2::GetInstance();
    v19->Init();
    v20 = (RenderTarget4 *)RenderTarget4::GetInstance();
    v20->Init();
    v21 = (void *)CEffectSystem::DestroyAllEffect();
    CEffectSystem::IsVisible((int)v21);
    PAL3::GetCommandLineParam();
  }
  else
  {
    (CGameData *->Init()&g_GameData);
    CGameData_Load((int)&g_GameData, 4);
    v12 = (_DWORD *)CRenderTarget::GetInstance();
    v12->Create();
    v13 = (RenderTarget3 *)RenderTarget3::GetInstance();
    v13->Init();
    v14 = (RenderTarget2 *)CRenderTarget2::GetInstance();
    v14->Init();
    v15 = (RenderTarget4 *)RenderTarget4::GetInstance();
    v15->Init();
    v16 = (void *)CEffectSystem::DestroyAllEffect();
    CEffectSystem::IsVisible((int)v16);
  }
  (*(void (__stdcall **)(_DWORD, char *))(**(_DWORD **)&g_pGfxManager[1816] + 28))(
    *(_DWORD *)&g_pGfxManager[1816],
    v35);
  if ( !v36 )
    MEMORY[0xBFDA91] = 1;
  SoundSystem::Init();
  OpenBaseFile::OpenBaseFile(&v32);
  v38 = 2;
  v22 = (gbGeomNode *)operator new(0x118u);
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
  MEMORY[0xA3A6EC] = v24;
  v24->LoadFromFile(aObjectG02Cvd, 0, 0);
  v25 = (struct gbVFileSystem *)operator new(0x118u);
  v26 = v25;
  v32 = v25;
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
  MEMORY[0xA3A6F0] = v27;
  v27->LoadFromFile(aObjectG03Cvd, 0, 0);
  (CScreenMode *->CreateDevice()&MEMORY[0xA3A7D8], (int)aMovieLogoBik, (int)MEMORY[0xBFDA4C], 0, 0);
  v30 = (600 - (CScreenMode *->GetHeight()&MEMORY[0xA3A7D8])) / 2;
  Width = (CScreenMode *->GetWidth()&MEMORY[0xA3A7D8]);
  (CScreenMode *->SetViewport()&MEMORY[0xA3A7D8], (800 - Width) / 2, v30);
  (CScreenMode *->PlayVideo()&MEMORY[0xA3A7D8], 1);
  v38 = -1;
  return OpenNULLFile::OpenNULLFile(&v32);
}

// 0x00404FF0
void PAL3::InitGFX()
{
  gbActorMgr *v0; // eax
  gbActorMgr *v1; // eax
  int v2; // eax
  gbRefObject *v3; // esi
  _DWORD v4[4]; // [esp+20h] [ebp-81Ch] BYREF
  char pExceptionObject[1024]; // [esp+30h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+430h] [ebp-40Ch] BYREF
  int v7; // [esp+838h] [ebp-4h]

  g_pGfxManager = (int)gbCreateGraphManager((struct gbGfxDriverInfo *)&MEMORY[0xBFD6C8]);
  if ( !g_pGfxManager )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCreateGfxManag, (int)aDProjectPal3Ga_0, 401),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v0 = (gbActorMgr *)operator new(0xCu);
  v7 = 0;
  if ( v0 )
    v1 = (gbActorMgr *)v0->gbActorMgr((struct gbGfxManager *)g_pGfxManager);
  else
    v1 = 0;
  v7 = -1;
  g_pActorMgr = v1;
  if ( !v1 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCreateActorman, (int)aDProjectPal3Ga_0, 405),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = 1;
  if ( operator new(0x220u) )
    v2 = sub_41BE80(g_pGfxManager);
  else
    v2 = 0;
  v7 = -1;
  g_pCamera = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Ga_0, 409),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  CameraCtrl::SetDimention(MEMORY[0xBFD6D0], MEMORY[0xBFD6D4]);
  sub_41D100(0);
  CameraCtrl::SetAsCurrent(3);
  v4[3] = 3;
  v4[0] = -16777216;
  v4[1] = 1065353216;
  (gbGfxManager *->SetClearParam()g_pGfxManager, (struct gbClearParam *)v4);
  v3 = (gbRefObject *)operator new(0xD8u);
  v7 = 2;
  if ( v3 )
  {
    v3[1].RefCount = 1;
    v3->RefCount = (int)gbRefObject::`vftable';
    v3->RefCount = (int)gbVolumeModifier::`vftable';
    v3[24].RefCount = 0;
    v3[25].RefCount = 0;
    v3[26].RefCount = 0;
    LOBYTE(v7) = 3;
    v3[40].RefCount = 0;
    v3[41].RefCount = 0;
    v3[42].RefCount = 0;
    (gbVec3D *->gbVec3D()&v3[43], 0.0, 0.0, 0.0);
    v3->RefCount = (int)&off_56A694;
  }
  else
  {
    v3 = 0;
  }
  v7 = -1;
  v3->Init(2);
  v3[7].RefCount = 1065353216;
  v3[8].RefCount = 1065353216;
  v3[9].RefCount = 1065353216;
  v3[10].RefCount = 1065353216;
  v3[12].RefCount = 1;
  v3[11].RefCount = 1;
  v3[3].RefCount = 1049582633;
  v3[4].RefCount = 1049582633;
  v3[5].RefCount = 1049582633;
  v3[16].RefCount = 1092616192;
  v3[15].RefCount = 1092616192;
  v3[6].RefCount = 1065353216;
  (gbVolModNode *->SetVolModObj()&MEMORY[0xA3A6F8], (struct gbVolumeModifier *)v3);
  v3->Release();
}

// 0x00405330
char PAL3::CreateEffectSystem()
{
  gbSnow *v0; // esi
  gbRain *v1; // eax
  gbRain *v2; // esi
  SceneMgr *v3; // eax
  char v4; // al
  struct gbVFileSystem *v6; // [esp+8h] [ebp-85Ch] BYREF
  void *v7; // [esp+Ch] [ebp-858h]
  _DWORD v8[9]; // [esp+10h] [ebp-854h] BYREF
  _DWORD v9[9]; // [esp+34h] [ebp-830h] BYREF
  char pExceptionObject[1024]; // [esp+58h] [ebp-80Ch] BYREF
  char ArgList; // [esp+458h] [ebp-40Ch] BYREF
  int v12; // [esp+860h] [ebp-4h]

  v9[2] = 500;
  v9[7] = -1054867456;
  v9[8] = 1112014848;
  v9[4] = 0x40000000;
  v9[3] = 1053609165;
  v9[6] = 1109393408;
  v9[5] = 1101004800;
  v9[1] = 1120403456;
  v9[0] = 1034147594;
  v8[2] = 200;
  v8[7] = -1054867456;
  v8[8] = 1112014848;
  v8[4] = 1077936128;
  v8[3] = 1065353216;
  v8[6] = 1092616192;
  v8[5] = 1086324736;
  v8[1] = 1120403456;
  v8[0] = 1056964608;
  OpenBaseFile::OpenBaseFile(&v6);
  v12 = 0;
  v0 = (gbSnow *)operator new(0x58u);
  v7 = v0;
  LOBYTE(v12) = 1;
  if ( v0 )
  {
    v0->gbSnow(500, (const struct gbDropDesc *)v8, aEffectSnowTga, 2.0);
    v0->m_MaxUnit = (int)&off_56A6B4;
  }
  else
  {
    v0 = 0;
  }
  LOBYTE(v12) = 0;
  MEMORY[0xBFDA38] = v0;
  v1 = (gbRain *)operator new(0x50u);
  v2 = v1;
  v7 = v1;
  LOBYTE(v12) = 2;
  if ( v1 )
  {
    v1->gbRain(500, (const struct gbDropDesc *)v9, 0);
    *(_DWORD *)v2 = &off_56A6A8;
  }
  else
  {
    v2 = 0;
  }
  LOBYTE(v12) = 0;
  MEMORY[0xBFDA3C] = (gbDropGroup *)v2;
  v7 = (void *)operator new(0x158u);
  LOBYTE(v12) = 3;
  if ( v7 )
    v3 = (SceneMgr *)((SceneMgr *(__stdcall *)(gbGfxManager *))sub_4C5820)(g_pGfxManager);
  else
    v3 = 0;
  LOBYTE(v12) = 0;
  g_pSceneMgr = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)((int (*)@<eax>(char@<cl>, int, int, int))Logger::FormatException)(
                      (char)&ArgList,
                      (int)aCouldnTMallocM,
                      (int)aDProjectPal3Ga_0,
                      483),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v4 = sub_4C58C0(v3);
  v12 = -1;
  if ( v4 )
  {
    OpenNULLFile::OpenNULLFile(&v6);
    return 1;
  }
  else
  {
    OpenNULLFile::OpenNULLFile(&v6);
    return 0;
  }
}

// 0x004055A0
char PAL3::DestroyEffectSystem()
{
  void *v0; // esi

  v0 = g_pSceneMgr;
  if ( g_pSceneMgr )
  {
    sub_4C5840(g_pSceneMgr);
    operator delete(v0);
  }
  g_pSceneMgr = 0;
  return 1;
}

// 0x004055D0
int PAL3::Update(float a1)
{
  int v1; // edi
  unsigned __int16 *v2; // esi
  __int16 v3; // ax
  BOOL v4; // eax
  DWORD Time; // eax
  int v6; // esi
  int v7; // ebx
  int v8; // eax
  float *v9; // ebp
  int v10; // ebx
  float *v11; // esi
  double v12; // st7
  double v13; // st7
  int v14; // eax
  double v15; // st7
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  gbAudioManager *v21; // esi
  int v22; // eax
  int v23; // eax
  int result; // eax
  int v25; // [esp+4h] [ebp-2Ch]
  int v26; // [esp+4h] [ebp-2Ch]
  float v27; // [esp+18h] [ebp-18h]
  float v28; // [esp+1Ch] [ebp-14h]
  float v29; // [esp+20h] [ebp-10h]
  _DWORD v30[3]; // [esp+24h] [ebp-Ch] BYREF

  g_pTextureLib = g_pTextureLib + a1;
  GRPinput::GRPinput((int)&g_Input);
  v1 = 0;
  v2 = (unsigned __int16 *)&MEMORY[0x8ACCD8];
  do
  {
    v3 = (unsigned __int8 *->GetKeyState()&g_Input, *v2);
    v4 = v3 == 1 || v3 == 3;
    v25 = v4;
    Time = timeGetTime();
    GRPinput::SetMouseAbs(&g_Input, Time, v1, v25);
    ++v2;
    ++v1;
  }
  while ( (int)v2 < (int)MEMORY[0x8ACD2A] );
  v6 = g_nGameState;
  v7 = SceneUpdate(LODWORD(a1), 1);
  v8 = g_nGameState;
  if ( g_nGameState != v6 )
  {
    v6->IfHideFightSucceed();
    v8 = g_nGameState;
  }
  switch ( v8 )
  {
    case 0:
    case 1:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset(0);
      goto LABEL_64;
    case 2:
    case 9:
      MEMORY[0xBFDA5C] = MEMORY[0xBFDA5C] + a1;
      (*(void (**)(int))(*(_DWORD *)MEMORY[0xA3A6EC] + 20))(MEMORY[0xA3A6EC]);
      (*(void (**)(int))(*(_DWORD *)MEMORY[0xA3A6F0] + 20))(MEMORY[0xA3A6F0]);
      CRenderTarget2::GetInstance();
      CRenderTarget2_Update(a1);
      PalScriptMgr::RunSceneScript(LODWORD(a1));
      if ( byte_D8C339 )
      {
        byte_D8C339 = 0;
        PalScriptMgr::RunSceneScript(LODWORD(a1));
      }
      InputUpdate(a1);
      if ( g_nGameState != 9 )
      {
        if ( v7 )
        {
          UIQuadManager::GetInstance();
          UIQuadManager_Reset(0);
        }
        else
        {
          CameraUpdate_Internal(a1);
        }
        ScriptUpdate(a1);
      }
      UISceneUpdate();
      UIUpdate(a1);
      EffectUpdate(a1);
      SceneMgrUpdate(MEMORY[0xBFDA5C]);
      UIPostUpdate();
      v17 = CScreenMode::GetInstance();
      v17->AudioUpdate();
      if ( g_nGameState != 2 && g_nGameState != 9 )
        v6->IfHideFightSucceed();
      goto LABEL_64;
    case 3:
      CCBSystem::CombatUpdate(COERCE_FLOAT(COERCE_UNSIGNED_INT64(a1)), HIDWORD(COERCE_UNSIGNED_INT64(a1)));
      CombatEffectUpdate(a1);
      v18 = CScreenMode::GetInstance();
      v18->AudioUpdate();
      if ( !*((_BYTE *)g_pCBSystem + 116) )
        goto LABEL_64;
      if ( g_pEffMgr )
      {
        PAL3::GetCommandLineParam();
        CCBSystem::CombatUpdate(0.0, 0);
        CombatEffectUpdate(0.0);
        goto LABEL_59;
      }
      byte_5833D0 = *((_DWORD *)g_pCBSystem + 31) == 2;
      v19 = CGameData::GetMode(&g_GameData);
      CGameData_Load(v19);
      CombatEnter();
      if ( (g_nGameFlags & 4) == 0 )
        goto LABEL_54;
      v20 = CScreenMode::GetInstance();
      v21 = (gbAudioManager *)v20->GetAudioManager();
      if ( !v21 )
        goto LABEL_54;
      if ( MEMORY[0xC11751] )
      {
        if ( *(_BYTE *)(CScreenMode::GetInstance() + 4) )
          goto LABEL_54;
        goto LABEL_51;
      }
      v21->StopSoundStream(1);
      v21->StopSoundStream(0);
      if ( !*(_BYTE *)(CScreenMode::GetInstance() + 4) )
      {
LABEL_51:
        v21->StopSoundStream(2);
        v21->StopSoundStream(1);
        v22 = CScreenMode::GetInstance();
        v22->AudioStopAll();
        goto LABEL_54;
      }
      v23 = CScreenMode::GetInstance();
      v23->AudioFadeOut();
LABEL_54:
      if ( byte_5833D0 || !dword_5833CC )
      {
        if ( MEMORY[0xC11754] )
          *(_DWORD *)(MEMORY[0xC11754] + 632) = 0;
      }
      else
      {
        CGameData_Load(15);
        PalScriptMgr::IfHaveScript();
      }
LABEL_59:
      MEMORY[0xC11748] = 0;
      MEMORY[0xC11750] = 0;
      MEMORY[0xC1171C] = 0x7FFFFFFF;
      dword_5833CC = 1;
      goto LABEL_64;
    case 4:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset(0);
      MiniGame1Update(a1);
      goto LABEL_64;
    case 5:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset(0);
      MiniGame2Update(a1);
      goto LABEL_63;
    case 6:
      UIQuadManager::GetInstance();
      UIQuadManager_Reset(0);
      MiniGame3Update(a1);
LABEL_63:
      NPCAnimUpdate(a1);
      goto LABEL_64;
    case 7:
      MEMORY[0xBFDA58] = MEMORY[0xBFDA58] + a1;
      if ( MEMORY[0xBFDA30] )
      {
        if ( !(unsigned __int8)PalScriptMgr::_CON_CloseScript() )
        {
          byte_D924E8 = 1;
          CGameData_Load(4);
        }
      }
      else if ( MEMORY[0xBFDA58] >= 60.0 )
      {
        PAL3::EndWolf(-1);
        goto LABEL_64;
      }
      PalScriptMgr::RunSceneScript(LODWORD(a1));
      InputUpdate(a1);
      ScriptUpdate(a1);
      UISceneUpdate();
      UIUpdate(a1);
      EffectUpdate(a1);
      if ( MEMORY[0xBFDA30] )
        goto LABEL_64;
      if ( !v7 )
        CameraUpdate_Internal(a1);
      v9 = (float *)MEMORY[0xC116EC];
      v10 = 1;
      v11 = (float *)&MEMORY[0xC0816C];
      while ( 1 )
      {
        if ( *((_DWORD *)v11 + 155) )
        {
          v27 = v9[1] - *(v11 - 2);
          v12 = v9[2] - *(v11 - 1);
          *(float *)v30 = v27;
          v28 = v12;
          v13 = v9[3] - *v11;
          *(float *)&v30[1] = v28;
          v29 = v13;
          *(float *)&v30[2] = v29;
          if ( 12.0 + 12.0 > (gbVec3D *->Length()v30) )
            break;
        }
        v11 += 2176;
        ++v10;
        if ( (int)v11 >= (int)MEMORY[0xC1096C] )
          goto LABEL_64;
      }
      v10->EndWolf();
      goto LABEL_64;
    case 8:
      if ( (unsigned __int8)PAL3::EntryCatchGhost(0) )
      {
        PAL3::EndHideFight();
        RoleSystemNotify(MEMORY[0xC116EC]);
        v14 = PalScriptMgr::Destroy(1701, 0);
LABEL_33:
        v26 = v14;
        SoundContext::GetInstance();
        CScreenMode_SetResolution(0, v26);
        PalScriptMgr::RunSceneScript(LODWORD(a1));
        goto LABEL_64;
      }
      v15 = MEMORY[0xBFDA58] + a1;
      MEMORY[0xBFDA58] = v15;
      if ( v15 >= 180.0 )
        goto LABEL_32;
      PalScriptMgr::RunSceneScript(LODWORD(a1));
      InputUpdate(a1);
      ScriptUpdate(a1);
      UISceneUpdate();
      UIUpdate(a1);
      EffectUpdate(a1);
      if ( !v7 )
        CameraUpdate_Internal(a1);
      UIPostUpdate();
      if ( *(_DWORD *)(MEMORY[0xC116EC] + 1264) != 4 )
      {
        v16 = UISceneUpdate();
        if ( UINotifyUpdate(v16) )
        {
LABEL_32:
          RoleSystemNotify(MEMORY[0xC116EC]);
          PAL3::EndHideFight();
          v14 = PalScriptMgr::Destroy(1702, 0);
          goto LABEL_33;
        }
      }
LABEL_64:
      ScreenEffectMgr::GetInstance();
      RenderPost(LODWORD(a1));
      result = g_nGameState;
      if ( !g_nGameState )
        return CScreenMode::SetState(1);
      return result;
    default:
      goto LABEL_64;
  }
}

// 0x00405C00
int PAL3::Render()
{
  int result; // eax
  int v1; // eax
  int v2; // eax
  gbSceneGraph *v3; // edi
  struct gbCamera *v4; // eax
  int v5; // ebx
  gbMatrixStack *v6; // esi
  gbMatrix4 *Top; // eax
  struct gbCamera *v8; // eax
  struct gbCamera *v9; // eax
  int v10; // eax
  struct gbCamera *v11; // eax
  int v12; // eax
  struct gbCamera *v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edi
  __int64 v18; // rax
  int v19; // esi
  double v20; // st7
  int v21; // eax
  int v22; // eax
  float v23; // [esp+0h] [ebp-94h]
  float v24; // [esp+4h] [ebp-90h]
  _DWORD v25[3]; // [esp+18h] [ebp-7Ch] BYREF
  _DWORD v26[3]; // [esp+24h] [ebp-70h] BYREF
  _DWORD v27[3]; // [esp+30h] [ebp-64h] BYREF
  _DWORD v28[3]; // [esp+3Ch] [ebp-58h] BYREF
  _DWORD v29[3]; // [esp+48h] [ebp-4Ch] BYREF
  _DWORD v30[3]; // [esp+54h] [ebp-40h] BYREF
  _DWORD v31[4]; // [esp+60h] [ebp-34h] BYREF
  _DWORD v32[2]; // [esp+70h] [ebp-24h] BYREF
  _DWORD Buffer[2]; // [esp+78h] [ebp-1Ch] BYREF
  _DWORD v34[4]; // [esp+80h] [ebp-14h] BYREF
  int v35; // [esp+90h] [ebp-4h]

  (*(void (**)(int))(*(_DWORD *)g_pGfxManager + 48))(g_pGfxManager);
  switch ( g_nGameState )
  {
    case 0:
      return (*(int (**)(int))(*(_DWORD *)g_pGfxManager + 52))(g_pGfxManager);
    case 2:
    case 7:
    case 8:
    case 9:
      v1 = RenderTarget4::GetInstance();
      v1->End();
      v2 = CRenderTarget2::GetInstance();
      v2->Begin();
      v3 = (gbSceneGraph *)*(gbSceneGraph **)(g_pGfxManager + 448);
      if ( g_pCamera )
        v4 = (struct gbCamera *)(g_pCamera + 4);
      else
        v4 = 0;
      v3->Begin(v4);
      v5 = UIScene::CombatCheck();
      v6 = (gbMatrixStack *)*(gbMatrixStack **)(g_pGfxManager + 216);
      CameraCtrl::SetAsCurrent(3);
      v26[0] = 1065353216;
      v26[1] = 0;
      v26[2] = 0;
      v6->Rotate(*(float *)&MEMORY[0xC12B28], (struct gbVec3D *)v26);
      v27[0] = 0;
      v27[1] = 1065353216;
      v27[2] = 0;
      v6->Rotate(*(float *)&MEMORY[0xC12B2C], (struct gbVec3D *)v27);
      v28[0] = 0;
      v28[1] = 0;
      v28[2] = 1065353216;
      v6->Rotate(*(float *)&MEMORY[0xC12B30], (struct gbVec3D *)v28);
      if ( !v5 && *(_DWORD *)(UISceneUpdate() + 100) != 1 )
      {
        memset(v31, 0, 12);
        Buffer[0] = 0;
        v32[1] = 0;
        v32[0] = 0;
        memset(v34, 0, 12);
        v29[1] = 0;
        v29[2] = 0;
        v31[3] = 1065353216;
        Buffer[1] = 1065353216;
        v34[3] = 1065353216;
        v29[0] = 1065353216;
        (gbQuaternion *->SetAxisAngle()v31, (struct gbVec3D *)v29, 45.0);
        v30[0] = 0;
        v30[1] = 1065353216;
        v30[2] = 0;
        (gbQuaternion *->SetAxisAngle()v32, (struct gbVec3D *)v30, 90.0);
        (gbQuaternion *->MultiplyBy()v32, (struct gbQuaternion *)v31, (struct gbQuaternion *)v34);
        (gbQuaternion *->GetMatrix()v34, (struct gbMatrix4 *)&MEMORY[0xA3A750]);
        (gbVolModNode *->Attach()&MEMORY[0xA3A6F8], 0);
      }
      if ( dword_D8E488 == 2 )
      {
        Top = (gbMatrix4 *)v6->GetTop();
        Top->TransformPlane();
        (*(void (**)(int, int *))(*(_DWORD *)g_pGfxManager + 112))(g_pGfxManager, &dword_D8E488);
      }
      else
      {
        (*(void (**)(int, _DWORD))(*(_DWORD *)g_pGfxManager + 112))(g_pGfxManager, 0);
      }
      UISceneUpdate();
      v6->RenderWithStack();
      if ( g_nGameState != 9 )
        v6->Render();
      v3->End();
      if ( MEMORY[0xBFDA38] && MEMORY[0xBFDA40] )
      {
        if ( g_pCamera )
          v8 = (struct gbCamera *)(g_pCamera + 4);
        else
          v8 = 0;
        (gbDropGroup *->Render()MEMORY[0xBFDA38], v8);
      }
      if ( MEMORY[0xBFDA3C] && MEMORY[0xBFDA41] )
      {
        if ( g_pCamera )
          v9 = (struct gbCamera *)(g_pCamera + 4);
        else
          v9 = 0;
        (gbDropGroup *->Render()MEMORY[0xBFDA3C], v9);
      }
      v10 = UISceneUpdate();
      v10->NotifyRender();
      if ( g_pCamera )
        v11 = (struct gbCamera *)(g_pCamera + 4);
      else
        v11 = 0;
      v3->Begin(v11);
      v3->pAllRObj[19244] = 0;
      if ( *(_DWORD *)(UISceneUpdate() + 100) != 1 )
        UIScene::CombatCheck();
      UISceneUpdate();
      v6->Render();
      SceneMgr::RenderUpdate(g_pGameData);
      v3->End();
      if ( g_nGameState == 8 )
      {
        v12 = UISceneUpdate();
        v12->EffectRender();
      }
      UIManager::Render(&MEMORY[0xC11758]);
      SceneMgr::RenderAll(g_pGameData);
      if ( g_pCamera )
        v13 = (struct gbCamera *)(g_pCamera + 4);
      else
        v13 = 0;
      v3->Begin(v13);
      v3->pAllRObj[19244] = 0;
      UIScene::CombatCheck();
      sub_410430(v6);
      UISceneUpdate();
      v6->OverlayRender();
      v3->End();
      v14 = RenderTarget4::GetInstance();
      v14->Resolve();
      v15 = CRenderTarget2::GetInstance();
      v15->Resolve();
      v16 = RenderTarget3::GetInstance();
      v16->Begin();
      if ( !g_bRenderUI )
        break;
      goto LABEL_42;
    case 3:
      CCBSystem::RenderCheck(g_pCBSystem);
      break;
    case 4:
      MiniGame1::Render(g_pInput);
      break;
    case 5:
      sub_52F2E0(g_pScreenMode);
      goto LABEL_42;
    case 6:
      MiniGame3::Render(g_pRoleSystem);
LABEL_42:
      ScriptSystem::Render2();
      break;
    default:
      break;
  }
  if ( g_nGameState == 8 )
  {
    v17 = (__int64)(180.0 - MEMORY[0xBFDA58]);
    goto LABEL_46;
  }
  if ( g_nGameState == 7 )
  {
    v17 = (int)(__int64)(60.0 - MEMORY[0xBFDA58]) < 0 ? 0 : (__int64)(60.0 - MEMORY[0xBFDA58]);
LABEL_46:
    sprintf((char *const)Buffer, "%03d", v17);
    LOBYTE(v18) = 0;
    v19 = *(_DWORD *)(*(_DWORD *)(g_pGfxManager + 208) + 12);
    if ( v17 < 30 )
      v18 = (__int64)(sin(MEMORY[0xBFDA58] * 4.0) * 255.0);
    v20 = 60.0 / (double)MEMORY[0xBFD6D4];
    *(float *)(v19 + 48) = 60.0 / (double)MEMORY[0xBFD6D0];
    *(float *)(v19 + 52) = v20;
    if ( (_BYTE)v18 )
    {
      if ( gbColorQuad::ColorQuadFmt )
      {
        BYTE2(v25[0]) = v18;
        LOWORD(v25[0]) = 29338;
      }
      else
      {
        *(_WORD *)((char *)v25 + 1) = -25998;
        LOBYTE(v25[0]) = v18;
      }
      HIBYTE(v25[0]) = -56;
      *(_DWORD *)(v19 + 44) = v25[0];
    }
    else
    {
      if ( gbColorQuad::ColorQuadFmt )
      {
        *(_WORD *)((char *)v25 + 1) = 214;
        LOBYTE(v25[0]) = -2;
      }
      else
      {
        *(_WORD *)((char *)v25 + 1) = -298;
        LOBYTE(v25[0]) = 0;
      }
      HIBYTE(v25[0]) = -56;
      *(_DWORD *)(v19 + 44) = v25[0];
    }
    v24 = 1.0 - 64.0 / (double)MEMORY[0xBFD6D4];
    v23 = 1380.0 / (double)MEMORY[0xBFD6D0] - 1.0;
    (*(void (**)(int, _DWORD *, _DWORD, _DWORD, int, int))(*(_DWORD *)v19 + 16))(
      v19,
      Buffer,
      LODWORD(v23),
      LODWORD(v24),
      1176256512,
      1176256512);
    (*(void (**)(int))(*(_DWORD *)v19 + 8))(v19);
  }
  if ( g_nGameState && g_nGameState != 3 && g_bRenderUI )
  {
    PushMatrixStacks(v25);
    v35 = 0;
    v21 = ScreenEffectMgr::GetInstance();
    v21->Render();
    CGameData::Render(&g_GameData);
    if ( MEMORY[0xBFDA34] )
      (*(void (**)(int))(*(_DWORD *)MEMORY[0xBFDA34] + 4))(MEMORY[0xBFDA34]);
    if ( !g_pPalScript )
      Logger::Render(&g_Logger);
    v35 = -1;
    PopMatrixStacks(v25);
  }
  v22 = UIQuadManager::GetInstance();
  v22->UIRenderObj();
  result = (*(int (**)(int))(*(_DWORD *)g_pGfxManager + 52))(g_pGfxManager);
  if ( g_pPalScript )
  {
    result = PAL3::PrintScreen();
    g_pPalScript = 0;
  }
  return result;
}

// 0x00406230
int PAL3::Destroy()
{
  int v0; // eax
  int v1; // eax
  int v2; // eax
  void *v3; // esi
  void *v4; // esi
  int v5; // eax

  v0 = CRenderTarget::GetInstance();
  v0->Destroy();
  v1 = CRenderTarget2::GetInstance();
  v1->Destroy();
  v2 = UIQuadManager::GetInstance();
  v2->Destroy();
  ScriptSystem::Destroy();
  UISystem::Destroy();
  _TextureLib_Data::_TextureLib_Data();
  PalScriptMgr::_CON_ReLoadScript();
  if ( g_pCBSystem )
  {
    CCBSystem::ProcFling();
    v3 = g_pCBSystem;
    if ( g_pCBSystem )
    {
      nullsub_3(g_pCBSystem);
      operator delete(v3);
    }
    g_pCBSystem = 0;
  }
  CGameData::Destroy(&g_GameData);
  PAL3::DestroyEffectSystem();
  if ( g_pCamera )
  {
    (**(void (***)(int, int))g_pCamera)(g_pCamera, 1);
    g_pCamera = 0;
  }
  v4 = g_pActorMgr;
  if ( g_pActorMgr )
  {
    gbActorMgr::~gbActorMgr((gbActorMgr *)g_pActorMgr);
    operator delete(v4);
    g_pActorMgr = 0;
  }
  if ( g_pGfxManager )
  {
    (**(void (***)(int, int))g_pGfxManager)(g_pGfxManager, 1);
    g_pGfxManager = 0;
  }
  FileSysDestory();
  v5 = CScreenMode::GetInstance();
  return v5->Restore();
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
      (Logger *->FormatException()ArgList, aRegisterclassF, aDProjectPal3Ga_0, 1094),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (Config *->ReadINIInt()Buffer, a1, a2);
  v18 = 0;
  (Config *->ReadINIString()Buffer, aConfigIni, v7);
  MEMORY[0xBFD6C8] = 2;
  MEMORY[0xBFD6CC] = 0;
  (Config *->ReadINI()Buffer, aDisplay, section);
  (Config *->ReadINI()Buffer, aDisplay, aHeight);
  (Config *->ReadINI()Buffer, aDisplay, aColorbits);
  (Config *->ReadINI()Buffer, aDisplay, aDepthbits);
  (Config *->ReadINI()Buffer, aDisplay, aRate);
  MEMORY[0xBFD6E4] = 2;
  MEMORY[0xBFD77C] = (unsigned __int8)(g_nGameFlags & 0x10) >> 4;
  MEMORY[0xBFD6E8] = 1;
  MEMORY[0xBFD6E0] = 0;
  strcpy(MEMORY[0xBFD6F0], ClassName);
  MEMORY[0xBFD770] = (int)hInstance;
  MEMORY[0xBFD778] = 0;
  v5 = MEMORY[0xBFD6E8] != 0 ? 8 : 0;
  SetRect(&rc, 0, 0, MEMORY[0xBFD6D0], MEMORY[0xBFD6D4]);
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
    qmemcpy(v12, (Logger *->FormatException()v15, aWindowCreateFa, aDProjectPal3Ga_0, 1152), sizeof(v12));
    _CxxThrowException(v12, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  MEMORY[0xBFD774] = Window;
  MEMORY[0xBFDA4C] = Window;
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
  g_pUIManager = (int)CommandLineA;
  if ( CommandLineA )
  {
    if ( (unsigned __int8)aSc->ParseCmdLine() || (unsigned __int8)aSoftcursor->ParseCmdLine() )
      MEMORY[0xBFDA91] = 1;
    if ( (unsigned __int8)aXsnd->ParseCmdLine() )
    {
      v1 = g_nGameFlags;
      LOBYTE(v1) = g_nGameFlags & 0xFE;
      g_nGameFlags = v1;
    }
    if ( (unsigned __int8)aXmusic->ParseCmdLine() )
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
    v5 = (unsigned __int8)aMotionblur->ParseCmdLine() == 0;
    v6 = g_nGameFlags;
    if ( v5 )
      LOBYTE(v6) = g_nGameFlags & 0xF7;
    else
      LOBYTE(v6) = g_nGameFlags | 8;
    g_nGameFlags = v6;
    if ( (unsigned __int8)aScursor->ParseCmdLine() )
      *(_BYTE *)(UIQuadManager::GetInstance() + 29) = 1;
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
    (Config *->ReadINIInt()FileName, v2, v4);
    v8 = 0;
    (Config *->ReadINIString()FileName, aConfigIni, v3);
    (Config *->ReadINI()FileName, aMisc, lpKeyName);
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
    (Config *->ReadINIInt()Buffer, v2, v4);
    v6 = 0;
    (Config *->ReadINIString()Buffer, aConfigIni, v3);
    (Config *->ReadINI()Buffer, aDisplay, lpKeyName);
    v6 = -1;
    nullsub_3(Buffer);
    return 0;
  }
  return result;
}

// 0x00406980
int PAL3::GetCommandLineParam()
{
  if ( !(_BYTE)MEMORY[0xC05F58]
    && __PAIR16__(BYTE1(MEMORY[0xC05F58]), 0) == BYTE2(MEMORY[0xC05F58])
    && __PAIR16__(HIBYTE(MEMORY[0xC05F58]), 0) == (unsigned __int8)MEMORY[0xC05F5C] )
  {
    MEMORY[0xC05F58] = 16777473;
    MEMORY[0xC05F5C] = 0;
  }
  if ( !MEMORY[0xC11718] )
    PAL3::UpdateSubsystems(2, 7304, 7305, 0, 0, &MEMORY[0xC11700]);
  CCBSystem::ProcMagicWait(&MEMORY[0xC11700], 1);
  return CGameData_Load(6);
}

// 0x00406A10
int PAL3::TestCombat()
{
  MEMORY[0x8ACCE8] = 27;
  MEMORY[0x8ACCEE] = 9;
  MEMORY[0x8ACCF0] = 9;
  MEMORY[0x8ACCFA] = 27;
  MEMORY[0x8ACD08] = 9;
  MEMORY[0x8ACCD8] = 256;
  MEMORY[0x8ACCDA] = 257;
  MEMORY[0x8ACCDC] = 134;
  MEMORY[0x8ACCDE] = 135;
  MEMORY[0x8ACCE0] = 136;
  MEMORY[0x8ACCE2] = 137;
  MEMORY[0x8ACCE4] = 32;
  MEMORY[0x8ACCE6] = 13;
  MEMORY[0x8ACCEC] = 154;
  MEMORY[0x8ACCEA] = 155;
  MEMORY[0x8ACCF2] = 97;
  MEMORY[0x8ACCF4] = 100;
  MEMORY[0x8ACCF6] = 256;
  MEMORY[0x8ACCF8] = 257;
  MEMORY[0x8ACCFC] = 13;
  MEMORY[0x8ACCFE] = 32;
  MEMORY[0x8ACD00] = 134;
  MEMORY[0x8ACD02] = 135;
  MEMORY[0x8ACD04] = 136;
  MEMORY[0x8ACD06] = 137;
  MEMORY[0x8ACD0A] = 119;
  MEMORY[0x8ACD0C] = 138;
  MEMORY[0x8ACD0E] = 139;
  MEMORY[0x8ACD10] = 140;
  MEMORY[0x8ACD12] = 141;
  MEMORY[0x8ACD14] = 142;
  MEMORY[0x8ACD16] = 130;
  MEMORY[0x8ACD18] = 132;
  MEMORY[0x8ACD1A] = 112;
  MEMORY[0x8ACD1C] = 114;
  MEMORY[0x8ACD1E] = 102;
  MEMORY[0x8ACD20] = 107;
  MEMORY[0x8ACD22] = 101;
  MEMORY[0x8ACD24] = 130;
  MEMORY[0x8ACD26] = 132;
  MEMORY[0x8ACD28] = 128;
  return 132;
}

// 0x00406B80
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int __cdecl sub_406B80(const char *a1, int a2, int a3)
{
  int v3; // eax
  bool v4; // zf
  char v5; // cl
  unsigned int v6; // esi
  char v7; // cl
  int v8; // ebx
  unsigned int v9; // edi
  int result; // eax
  int v11; // edi
  unsigned int v12; // kr04_4
  unsigned int v13; // ebx
  char *v14; // edi
  char v15; // al

  g_pPalScript = 1;
  if ( a1 )
  {
    v12 = strlen(a1) + 1;
    v13 = v12 - 1;
    if ( std::string::max_size(&g_PAL3Data) < v12 - 1 )
      std::_Xlen();
    v14 = (char *)MEMORY[0x8ACBFC];
    if ( MEMORY[0x8ACBFC] && (v15 = *(_BYTE *)(MEMORY[0x8ACBFC] - 1)) != 0 && v15 != -1 )
    {
      if ( v12 == 1 )
      {
        *(_BYTE *)(MEMORY[0x8ACBFC] - 1) = v15 - 1;
        std::string::_Tidy(&g_PAL3Data, 0);
        goto LABEL_43;
      }
    }
    else
    {
      if ( v12 == 1 )
      {
        std::string::_Tidy(&g_PAL3Data, 1);
        goto LABEL_43;
      }
      if ( (unsigned int)MEMORY[0x8ACC04] <= 0x1F && MEMORY[0x8ACC04] >= v13 )
      {
LABEL_42:
        qmemcpy(v14, a1, v13);
        result = MEMORY[0x8ACBFC];
        MEMORY[0x8ACC00] = v12 - 1;
        *(_BYTE *)(MEMORY[0x8ACBFC] + v13) = 0;
        goto LABEL_43;
      }
      std::string::_Tidy(&g_PAL3Data, 1);
    }
    GRPinput::GetKeyState((int)&g_PAL3Data, v13);
    v14 = (char *)MEMORY[0x8ACBFC];
    goto LABEL_42;
  }
  v3 = MEMORY[0x8ACBFC];
  v4 = MEMORY[0x8ACBFC] == 0;
  if ( MEMORY[0x8ACBFC] )
  {
    v5 = *(_BYTE *)(MEMORY[0x8ACBFC] - 1);
    if ( v5 && v5 != -1 )
    {
      SceneObj::Update(MEMORY[0x8ACC00], 0);
      v3 = MEMORY[0x8ACBFC];
    }
    v4 = v3 == 0;
    if ( v3 )
    {
      *(_BYTE *)(v3 - 1) = -1;
      v3 = MEMORY[0x8ACBFC];
      v4 = MEMORY[0x8ACBFC] == 0;
    }
  }
  if ( v4 )
    v6 = 0;
  else
    v6 = MEMORY[0x8ACC00] + v3;
  if ( v3 )
  {
    v7 = *(_BYTE *)(v3 - 1);
    if ( v7 && v7 != -1 )
    {
      SceneObj::Update(MEMORY[0x8ACC00], 0);
      v3 = MEMORY[0x8ACBFC];
    }
    if ( v3 )
    {
      *(_BYTE *)(v3 - 1) = -1;
      v3 = MEMORY[0x8ACBFC];
    }
  }
  v8 = v3;
  std::string::_Freeze(&g_PAL3Data);
  if ( v8 )
    v9 = v8 - MEMORY[0x8ACBFC];
  else
    v9 = 0;
  if ( v6 )
    v6 -= v8;
  if ( MEMORY[0x8ACC00] < v9 )
    std::_Xran();
  std::string::_Split(&g_PAL3Data);
  result = MEMORY[0x8ACC00];
  if ( MEMORY[0x8ACC00] - v9 < v6 )
    v6 = MEMORY[0x8ACC00] - v9;
  if ( v6 )
  {
    memcpy((void *)(v9 + MEMORY[0x8ACBFC]), (const void *)(v9 + MEMORY[0x8ACBFC] + v6), MEMORY[0x8ACC00] - v6 - v9);
    v11 = MEMORY[0x8ACC00] - v6;
    result = SceneObj::Update(MEMORY[0x8ACC00] - v6, 0);
    if ( (_BYTE)result )
    {
      result = MEMORY[0x8ACBFC];
      MEMORY[0x8ACC00] = v11;
      *(_BYTE *)(MEMORY[0x8ACBFC] + v11) = 0;
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

  if ( (*(int (**)(gbGfxManager *, int *, int))(*(_DWORD *)g_pGfxManager + 84))(g_pGfxManager, &v23, 1) )
  {
    (gbImage2D *->gbImage2D()&v30);
    v33 = 0;
    if ( v25 != 3 )
    {
      if ( v25 == 8 )
      {
        v0 = 32;
LABEL_8:
        v28 = v0;
        Image = (gbImage2D *->CreateImage()&v30, v23, v24, v0);
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
        (*(void (**)(gbGfxManager *))(*(_DWORD *)g_pGfxManager + 88))(g_pGfxManager);
        (gbImage2D *->Release()(&g_PAL3Data + 24));
        v6 = (gbImage2D *->CreateImage()(&g_PAL3Data + 24), v26, v27, 24);
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
          (gbImage2D *->ScaleTo()(&g_PAL3Data + 24), dword_5833C4, dword_5833C8);
        (gbImage2D *->Release()&v30);
        goto LABEL_34;
      }
      if ( v25 != 9 )
      {
        (*(void (**)(gbGfxManager *))(*(_DWORD *)g_pGfxManager + 88))(g_pGfxManager);
LABEL_34:
        v33 = -1;
        gbImage2D::~gbImage2D((gbImage2D *)&v30);
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
  char *v1; // esi
  int (***v2)(_DWORD, _DWORD); // eax
  int result; // eax

  MEMORY[0xBFDA30] = 0;
  MEMORY[0xBFDA2C] = a1;
  if ( a1 )
  {
    *(_DWORD *)(g_pCamera + 448) = 1;
    RoleSystem::SetActive(&MEMORY[0xC05F60]);
  }
  sub_4070A0(aSoftwareSoftst, (DWORD)aSGameA, 1u);
  PalScriptMgr::Destroy(99, 0);
  v1 = (char *)&MEMORY[0xC08160];
  do
  {
    sub_419AE0(v1);
    v1 += 8704;
  }
  while ( (int)v1 < (int)MEMORY[0xC10960] );
  ScriptSystem::Execute(0, 1);
  g_nGameState = 7;
  v2 = (int (***)(_DWORD, _DWORD))CGameData::SetMode(0);
  result = (**v2)(v2, 0);
  MEMORY[0xBFDA58] = 0.0;
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
int PAL3::EndWolf(int a1)
{
  _DWORD *v1; // esi
  int result; // eax
  void (***v3)(_DWORD, int); // eax
  int v4; // [esp-4h] [ebp-18h]
  int v5; // [esp-4h] [ebp-18h]
  _DWORD v6[5]; // [esp+0h] [ebp-14h]
  void *retaddr; // [esp+14h] [ebp+0h]

  v1 = (_DWORD *)&MEMORY[0xC08650];
  do
  {
    RoleSystemNotify(v1 - 316);
    *v1 = 2;
    v1 += 2176;
  }
  while ( (int)v1 < (int)MEMORY[0xC10E50] );
  if ( MEMORY[0xBFDA2C] )
  {
    v6[0] = 0;
    if ( a1 == -1 )
      result = PalScriptMgr::Destroy(95, v6[0]);
    else
      result = PalScriptMgr::Destroy(96, v6[0]);
    MEMORY[0xBFDA30] = result;
  }
  else
  {
    g_nGameState = 2;
    v3 = (void (***)(_DWORD, int))CGameData::SetMode(0);
    (**v3)(v3, 1);
    if ( retaddr == (void *)-1 )
    {
      v5 = PalScriptMgr::Destroy(97, 0);
      SoundContext::GetInstance();
      return CScreenMode_SetResolution(0, v5);
    }
    else
    {
      v4 = PalScriptMgr::Destroy(98, 0);
      SoundContext::GetInstance();
      CScreenMode_SetResolution(0, v4);
      result = MEMORY[0xBFDA44];
      if ( (unsigned int)MEMORY[0xBFDA44] < 4 )
      {
        v6[0] = 80015;
        v6[1] = 83012;
        v6[2] = 8153;
        v6[3] = 8154;
        result = sub_42BEF0(v6[MEMORY[0xBFDA44]]);
      }
      ++MEMORY[0xBFDA44];
    }
  }
  return result;
}

// 0x004072D0
int PAL3::StartHideFight()
{
  int (***v0)(_DWORD, _DWORD); // eax

  g_nGameState = 8;
  MEMORY[0xBFDA58] = 0.0;
  v0 = (int (***)(_DWORD, _DWORD))CGameData::SetMode(0);
  return (**v0)(v0, 0);
}

// 0x00407300
int PAL3::EndHideFight()
{
  int (***v0)(_DWORD, int); // eax

  g_nGameState = 2;
  v0 = (int (***)(_DWORD, int))CGameData::SetMode(0);
  return (**v0)(v0, 1);
}

// 0x00407320
int PAL3::StartCombat(int a1, int a2, int a3, char a4)
{
  int result; // eax
  int v5; // ebx
  int v6; // esi
  int v7; // edi
  __int64 v8; // rax
  int v9; // ecx
  int v10; // esi
  int i; // eax
  int v12; // edi
  int v13; // ecx
  const char *v14; // eax
  int v15; // ecx
  char *v16; // esi
  int v17; // [esp+0h] [ebp-11Ch] BYREF
  char Buffer[256]; // [esp+Ch] [ebp-110h] BYREF
  int *v19; // [esp+10Ch] [ebp-10h]
  int v20; // [esp+118h] [ebp-4h]

  v20 = 0;
  v19 = (int *)&v17;
  result = PAL3::UIPostProcess();
  v5 = MEMORY[0xC116EC];
  if ( MEMORY[0xC116EC] )
  {
    ((void (*)(void))UISceneUpdate)();
    v6 = RoleSystem::GetRolePtr(*(_DWORD *)(v5 + 628));
    v7 = (__int64)((*(float *)(v5 + 4) - *(float *)(v6 + 128)) / MEMORY[0xBFDA04]);
    v8 = (__int64)((*(float *)(v5 + 12) - *(float *)(v6 + 136)) / MEMORY[0xBFDA04]);
    if ( v7 < 0 || (v9 = *(_DWORD *)(v6 + 152), v7 >= v9) || (int)v8 < 0 || (int)v8 >= *(_DWORD *)(v6 + 156) )
      v10 = 2;
    else
      v10 = *(unsigned __int8 *)(*(_DWORD *)(v6 + 160) + 8 * (v7 + v8 * v9) + 5);
    for ( i = 0; i < 6; ++i )
      MEMORY[0xC11700][i] = *(_DWORD *)(a1 + 4 * i);
    v12 = UISceneUpdate(a1);
    v14 = (const char *)UISceneUpdate(v13);
    sprintf(Buffer, "%s_%s", v14, (const char *)(v12 + 32));
    stru_BFAB60->SetDirectory(Buffer);
    sprintf(Buffer, "%d", v10);
    if ( !(unsigned __int8)sub_431C10(stru_BFAB60, Buffer, MEMORY[0xC11720], 32) )
      sub_431C10(stru_BFAB60, aDefault, MEMORY[0xC11720], 32);
    stru_BFAB60->SetDirectory(dir);
    if ( (unsigned __int8)sub_431C10(stru_BFAB60, MEMORY[0xC11720], Buffer, 256) )
      MEMORY[0xC11740] = atoi(Buffer);
    else
      MEMORY[0xC11740] = 1;
    if ( a2 == 1 )
      MEMORY[0xC11744] = 2;
    else
      MEMORY[0xC11744] = a2 == 2;
    MEMORY[0xC11754] = a3;
    MEMORY[0xC11751] = a4;
    result = CCBSystem::ProcMagicWait(MEMORY[0xC11700], 0);
    if ( (_BYTE)result )
    {
      if ( !a4 || (LOBYTE(v15) = *(_BYTE *)(CScreenMode::GetInstance() + 4), !(_BYTE)v15) )
      {
        v16 = (char *)UISceneUpdate(v15);
        CScreenMode::GetInstance();
        sub_53E680(v16);
      }
      return CGameData_Load(6);
    }
  }
  return result;
}

// 0x00407560
int PAL3::StartCombat(const void *a1, int a2, int a3)
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
  if ( MEMORY[0xC10CC1] )
    LOBYTE(v14[32]) = 6;
  PAL3::UpdateSubsystems(LOBYTE(v14[32]), v14[29], v14[30], v14[31], 0, v4);
  return PAL3::StartCombat((int)v4, a2, a3, 0);
}

// 0x00407640
char PAL3::EntryCatchGhost()
{
  int v0; // esi
  int v1; // ecx
  int *i; // edi
  int v4; // esi
  int v5; // edi
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
  if ( (unsigned __int8)aQ01->ProcessInput(0) )
  {
    v8 = 6308;
    v9 = 6309;
    v10 = 6310;
    v12 = 0;
    v13 = 0;
    for ( i = &v8; ; ++i )
    {
      v11 = *i;
      if ( CCBStageRole_GetByIndex(&v11) )
        break;
      if ( ++v0 >= 3 )
        return 0;
    }
  }
  else
  {
    v4 = MEMORY[0xC116EC];
    v7 = *(_DWORD *)(MEMORY[0xC116EC] + 628);
    UISceneUpdate(v1);
    v5 = v7->GetRolePtr();
    v6 = (__int64)((*(float *)(v4 + 4) - *(float *)(v5 + 128)) / MEMORY[0xBFDA04]);
    v9 = (__int64)((*(float *)(v4 + 12) - *(float *)(v5 + 136)) / MEMORY[0xBFDA04]);
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
int PAL3::IfHideFightSucceed(int a1)
{
  int result; // eax
  int v2; // eax
  gbAudioManager *v3; // eax

  result = a1 - 2;
  if ( a1 == 2 )
  {
    if ( (g_nGameFlags & 1) != 0 )
    {
      v2 = CScreenMode::GetInstance();
      v3 = (gbAudioManager *)v2->GetAudioManager();
      v3->DetachAll3D();
    }
    PAL3::UIPostProcess();
    RoleSystemNotify(MEMORY[0xC116EC]);
    UIQuadManager::GetInstance();
    return UIQuadManager_Reset(0);
  }
  return result;
}

// 0x00408BE0
int PAL3::InitSubsystems()
{
  _DWORD v1[4]; // [esp+0h] [ebp-10h] BYREF

  v1[0] = 0;
  v1[1] = 0;
  v1[2] = 40;
  v1[3] = 32;
  UIWnd::Create(0, v1, 0);
  aUiSceneTiao->LoadResource();
  MvcViewport::SetController(1082130432);
  UIWnd::Destroy(0);
  UINote::Create(1, v1, 0, aUiFlexNote_0);
  UIWnd::SetState(1);
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
  int v5; // eax
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
  char *v80; // edi
  int v81; // eax
  char *v82; // eax
  int *v83; // ecx
  int *v84; // esi
  int v85; // edi
  int v86; // eax
  int v87; // ebp
  int v88; // eax
  char *v89; // edi
  int v90; // eax
  char *v91; // eax
  int *v92; // ecx
  int *v93; // esi
  int v94; // edi
  int v95; // eax
  int v96; // ebp
  int v97; // eax
  char *v98; // edi
  int v99; // eax
  char *v100; // eax
  int *v101; // ecx
  int *v102; // esi
  int v103; // edi
  int v104; // eax
  int v105; // ebp
  int v106; // eax
  char *v107; // edi
  int v108; // eax
  char *v109; // eax
  int *v110; // ecx
  int v111; // ebp
  int ii; // eax
  int v113; // ecx
  int v114; // edx
  int *v115; // esi
  int v116; // edx
  int v117; // edi
  int v118; // eax
  char *v119; // ebp
  int v120; // edx
  int *jj; // eax
  int *v122; // edx
  int *v123; // esi
  int v124; // ebp
  int v125; // edx
  int v126; // eax
  int v127; // eax
  char *v128; // ebp
  int mm; // edi
  int v130; // eax
  int *kk; // eax
  int *v132; // ecx
  int *v133; // esi
  int v134; // ebp
  int v135; // edx
  int v136; // eax
  int v137; // eax
  char *v138; // ebp
  int i1; // edi
  int v140; // eax
  int *nn; // eax
  int *v142; // ecx
  int i2; // ecx
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
  if ( *(_DWORD *)&g_SceneMgr.m_info[51500] )
  {
    (***(void (****)(_DWORD, int))&g_SceneMgr.m_info[51500])(*(_DWORD *)&g_SceneMgr.m_info[51500], 1);
    *(_DWORD *)&g_SceneMgr.m_info[51500] = 0;
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
  *(_DWORD *)&g_SceneMgr.m_info[51524] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[51516] = 0;
  CCBStageRole_Reset(&g_SceneMgr.m_info[7072]);
  *(_DWORD *)&g_SceneMgr.m_info[7064] = *(_DWORD *)&g_SceneMgr.m_info[7060];
  dword_586158 = 35;
  v1 = g_RoleTeam2;
  do
  {
    * v1 = (*)*(v1 - 1);
    v1 += 4;
  }
  while ( (int)v1 < (int)&g_SceneMgr.m_info[24] );
  g_SceneMgr.m_info[51505] = 0;
  memset(&MEMORY[0xBFDB90], 0, 0x20u);
  MEMORY[0xBFDBA4] = 31;
  *(_DWORD *)&g_SceneMgr.m_info[51520] = 0;
  memset(&g_SceneMgr.m_info[16], 0, 0x1B80u);
  v164[0] = dword_58619C;
  v164[1] = dword_586198;
  v164[2] = dword_586194;
  v164[3] = &dword_586190;
  v164[4] = dword_58618C;
  v145 = 0;
  v2 = (char *)&g_SceneMgr.m_info[7294];
  v3 = v164;
  do
  {
    v4 = (const char *)*v3;
    (Camera *->SetParams()(v2 - 174), *v3);
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
  while ( (int)v2 < (int)&g_SceneMgr.m_info[50814] );
  (Camera *->SetParams()dword_C020F8, (int)"109");
  byte_C021A4 = 5;
  v5 = *(_DWORD *)&g_SceneMgr.m_info[51516];
  strcpy(byte_C021A6, "109");
  dword_C025E8 = 0;
  dword_C02370 = 0;
  dword_C02374 = 1;
  byte_C021A5 = -1;
  v5->SetParams();
  (Camera *->SetParams()dword_BFFDB0, (int)"DXD");
  strcpy(byte_BFFE5E, "DXD");
  dword_C002A0 = 1;
  dword_C00028 = 0;
  (Camera *->SetParams()MEMORY[0xBFDBB0], (int)&off_586180);
  strcpy(MEMORY[0xBFDC5E], (const char *)&off_586180);
  dword_BFE0A0 = 1;
  MEMORY[0xBFDE28] = 0;
  CameraSystem::Init((int)&g_SceneMgr.m_info[7120]);
  *(_DWORD *)&g_SceneMgr.m_info[51512] = 0;
  (RoleSystem *->SetActive()g_pCamera, (int)&g_SceneMgr.m_info[7120]);
  g_SceneMgr.m_info[7112] = 1;
  g_SceneMgr.m_info[7113] = 0;
  g_SceneMgr.m_info[7114] = 0;
  g_SceneMgr.m_info[7115] = 0;
  g_SceneMgr.m_info[7116] = 0;
  g_SceneMgr.m_info[1422] = 3;
  g_SceneMgr.m_info[2830] = 5;
  g_SceneMgr.m_info[4238] = 1;
  g_SceneMgr.m_info[5646] = 2;
  g_SceneMgr.m_info[7054] = 4;
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
  *(_DWORD *)&g_SceneMgr.m_info[1036] = 2224;
  *(_DWORD *)&g_SceneMgr.m_info[1040] = 10;
  *(_DWORD *)&g_SceneMgr.m_info[868] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[872] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[876] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[880] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[884] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[888] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[892] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[896] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[900] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[904] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[908] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[912] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[916] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[920] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[924] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[928] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[932] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[936] = 0;
  pConfig = 301;
  v162 = 0;
  RoleNum = g_GDB->GDB_GetRoleNum(301);
  v8 = (int *)g_RoleTeam2[0];
  v163 = RoleNum;
  if ( (dword_C0435C - g_RoleTeam2[0]) / 12 )
  {
    (void *->Insert()g_RoleTeam2[0], (void *)g_RoleTeam2[0], (void *)(g_RoleTeam2[0] + 12));
    (void *->Erase()g_RoleTeam2[0], 1 - (g_RoleTeam2[0] - (int)v8) / 12, &pConfig);
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
    if ( (unsigned int)Array::Size(&dword_C04350) <= 1 )
      v9 = 1;
    else
      v9 = Array::Size(&dword_C04350);
    v10 = Array::Size(&dword_C04350);
    v11 = v9 + v10 < 0;
    v12 = v9 + v10;
    v13 = v9 + v10;
    if ( v11 )
      v13 = 0;
    v14 = (void *)operator new(12 * v13);
    v146 = (char *)g_RoleTeam1->Insert(v8, v14);
    v146->Erase(1, &pConfig);
    v8->Insert((void *)g_RoleTeam2[0], v146 + 12);
    nullsub_2(g_RoleTeam1, g_RoleTeam2[0]);
    operator delete(g_RoleTeam1);
    dword_C0435C = (int)v14 + 12 * v12;
    v15 = Array::Size(&dword_C04350);
    g_RoleTeam1 = v14;
    g_RoleTeam2[0] = (int)v14 + 12 * v15 + 12;
  }
  *(_DWORD *)&g_SceneMgr.m_info[756] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[648] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[652] = Role::CreateXueJian(0, 1);
  *(_DWORD *)&g_SceneMgr.m_info[656] = Role::CreateLongKui(0, *(int *)&g_SceneMgr.m_info[648]);
  *(_DWORD *)&g_SceneMgr.m_info[660] = Role::CreateZiXuan(0, *(int *)&g_SceneMgr.m_info[648]);
  *(_DWORD *)&g_SceneMgr.m_info[664] = Role::CreateChangQing(0, *(int *)&g_SceneMgr.m_info[648]);
  *(_DWORD *)&g_SceneMgr.m_info[668] = Role::CreateHuaYing(0, *(int *)&g_SceneMgr.m_info[648]);
  *(_DWORD *)&g_SceneMgr.m_info[1008] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[672] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[1016] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[680] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[1020] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[684] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[1012] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[676] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[1032] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[696] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[1024] = 6;
  *(_DWORD *)&g_SceneMgr.m_info[688] = 6;
  *(_DWORD *)&g_SceneMgr.m_info[1028] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[692] = 1;
  (RoleSystem *->LoadData()&g_SceneMgr.m_info[16], 1);
  for ( k = 243; k < 255; ++k )
  {
    v19 = *(_DWORD *)&g_SceneMgr.m_info[k * 4 + 16];
    v20 = g_nSceneFlags[k];
    if ( v19 < v20 )
    {
      if ( v19 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_info[k * 4 + 16] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_info[k * 4 + 16] = v20;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_info[2276] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2280] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2284] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2288] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2292] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2296] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2300] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2304] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2308] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2312] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2316] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2320] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2324] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2328] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2332] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2336] = 82201;
  *(_DWORD *)&g_SceneMgr.m_info[2340] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[2344] = g_GDB->GDB_GetSkillNum(82201);
  pConfig = 321;
  v162 = 0;
  v21 = g_GDB->GDB_GetRoleNum(321);
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
    if ( (unsigned int)Array::Size(&dword_C04360) <= 1 )
      v23 = 1;
    else
      v23 = Array::Size(&dword_C04360);
    v24 = Array::Size(&dword_C04360);
    v11 = v23 + v24 < 0;
    v25 = v23 + v24;
    v26 = v23 + v24;
    if ( v11 )
      v26 = 0;
    v27 = (char *)operator new(12 * v26);
    v147 = (char *)arr->Insert(v22, v27);
    v147->Erase(1, &pConfig);
    v22->Insert(end, v147 + 12);
    nullsub_2(arr, end);
    operator delete(arr);
    dword_C0436C = (int)&v27[12 * v25];
    v28 = Array::Size(&dword_C04360);
    arr = v27;
    end = &v27[12 * v28 + 12];
  }
  *(_DWORD *)&g_SceneMgr.m_info[2164] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[2056] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[2060] = Role::CreateXueJian(1, 1);
  *(_DWORD *)&g_SceneMgr.m_info[2064] = Role::CreateLongKui(1, *(int *)&g_SceneMgr.m_info[2056]);
  *(_DWORD *)&g_SceneMgr.m_info[2068] = Role::CreateZiXuan(1, *(int *)&g_SceneMgr.m_info[2056]);
  *(_DWORD *)&g_SceneMgr.m_info[2072] = Role::CreateChangQing(1, *(int *)&g_SceneMgr.m_info[2056]);
  HuaYing = Role::CreateHuaYing(1, *(int *)&g_SceneMgr.m_info[2056]);
  *(_DWORD *)&g_SceneMgr.m_info[2424] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[2088] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[2432] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[2096] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[2076] = HuaYing;
  *(_DWORD *)&g_SceneMgr.m_info[2436] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[2100] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[2416] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[2080] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[2420] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[2084] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[2428] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[2092] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[2440] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[2104] = 5;
  (RoleSystem *->LoadData()&g_SceneMgr.m_info[1424], 1);
  for ( m = 972; m < 1020; m += 4 )
  {
    v33 = *(_DWORD *)&g_SceneMgr.m_info[m + 1424];
    v34 = *(_DWORD *)&g_SceneMgr.m_info[m + 1376];
    if ( v33 < v34 )
    {
      if ( v33 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_info[m + 1424] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_info[m + 1424] = v34;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_info[3684] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3688] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3692] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3696] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3700] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3704] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3708] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3712] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3716] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3720] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3724] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3728] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3732] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3736] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3740] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[3744] = 82101;
  *(_DWORD *)&g_SceneMgr.m_info[3748] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[3752] = g_GDB->GDB_GetSkillNum(82101);
  pConfig = 4301;
  v162 = 0;
  v163 = g_GDB->GDB_GetRoleNum(4301);
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
    if ( g_nSceneMode && (unsigned int)(((_BYTE *)elem - (_BYTE *)g_nSceneMode) / 12) > 1 )
      v36 = g_nSceneFlags->Size();
    else
      v36 = 1;
    v37 = g_nSceneFlags->Size();
    v11 = v36 + v37 < 0;
    v38 = v36 + v37;
    v39 = v36 + v37;
    if ( v11 )
      v39 = 0;
    v40 = (char *)operator new(12 * v39);
    v148 = (char *)g_nSceneMode->Insert(v35, v40);
    v148->Erase(1, &pConfig);
    v35->Insert(elem, v148 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete(g_nSceneMode);
    dword_C0437C = (int)&v40[12 * v38];
    v41 = g_nSceneFlags->Size();
    g_nSceneMode = v40;
    elem = &v40[12 * v41 + 12];
  }
  pConfig = 4302;
  v162 = 0;
  v163 = g_GDB->GDB_GetRoleNum(4302);
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
    if ( g_nSceneMode && (unsigned int)(((_BYTE *)elem - (_BYTE *)g_nSceneMode) / 12) > 1 )
      v45 = g_nSceneFlags->Size();
    else
      v45 = 1;
    v46 = g_nSceneFlags->Size();
    v11 = v45 + v46 < 0;
    v47 = v45 + v46;
    v48 = v45 + v46;
    if ( v11 )
      v48 = 0;
    v49 = (char *)operator new(12 * v48);
    v149 = (char *)g_nSceneMode->Insert(v44, v49);
    v149->Erase(1, &pConfig);
    v44->Insert(elem, v149 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete(g_nSceneMode);
    dword_C0437C = (int)&v49[12 * v47];
    v50 = g_nSceneFlags->Size();
    g_nSceneMode = v49;
    elem = &v49[12 * v50 + 12];
  }
  pConfig = 311;
  v162 = 2949123;
  v163 = g_GDB->GDB_GetRoleNum(311);
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
    if ( g_nSceneMode && (unsigned int)(((_BYTE *)elem - (_BYTE *)g_nSceneMode) / 12) > 1 )
      v54 = g_nSceneFlags->Size();
    else
      v54 = 1;
    v55 = g_nSceneFlags->Size();
    v11 = v54 + v55 < 0;
    v56 = v54 + v55;
    v57 = v54 + v55;
    if ( v11 )
      v57 = 0;
    v58 = (char *)operator new(12 * v57);
    v150 = (char *)g_nSceneMode->Insert(v53, v58);
    v150->Erase(1, &pConfig);
    v53->Insert(elem, v150 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete(g_nSceneMode);
    dword_C0437C = (int)&v58[12 * v56];
    v59 = g_nSceneFlags->Size();
    g_nSceneMode = v58;
    elem = &v58[12 * v59 + 12];
  }
  pConfig = 312;
  v162 = 0;
  v163 = g_GDB->GDB_GetRoleNum(312);
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
    if ( g_nSceneMode && (unsigned int)(((_BYTE *)elem - (_BYTE *)g_nSceneMode) / 12) > 1 )
      v63 = g_nSceneFlags->Size();
    else
      v63 = 1;
    v64 = g_nSceneFlags->Size();
    v11 = v63 + v64 < 0;
    v65 = v63 + v64;
    v66 = v63 + v64;
    if ( v11 )
      v66 = 0;
    v67 = (char *)operator new(12 * v66);
    v151 = (char *)g_nSceneMode->Insert(v62, v67);
    v151->Erase(1, &pConfig);
    v62->Insert(elem, v151 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete(g_nSceneMode);
    dword_C0437C = (int)&v67[12 * v65];
    v68 = g_nSceneFlags->Size();
    g_nSceneMode = v67;
    elem = &v67[12 * v68 + 12];
  }
  *(_DWORD *)&g_SceneMgr.m_info[3464] = 14;
  *(_DWORD *)&g_SceneMgr.m_info[3572] = 5594;
  *(_DWORD *)&g_SceneMgr.m_info[3468] = Role::CreateXueJian(2, 14);
  *(_DWORD *)&g_SceneMgr.m_info[3472] = Role::CreateLongKui(2, *(int *)&g_SceneMgr.m_info[3464]);
  *(_DWORD *)&g_SceneMgr.m_info[3476] = Role::CreateZiXuan(2, *(int *)&g_SceneMgr.m_info[3464]);
  *(_DWORD *)&g_SceneMgr.m_info[3480] = Role::CreateChangQing(2, *(int *)&g_SceneMgr.m_info[3464]);
  v71 = Role::CreateHuaYing(2, *(int *)&g_SceneMgr.m_info[3464]);
  *(_DWORD *)&g_SceneMgr.m_info[3840] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[3504] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[3484] = v71;
  *(_DWORD *)&g_SceneMgr.m_info[3844] = 6;
  *(_DWORD *)&g_SceneMgr.m_info[3508] = 6;
  *(_DWORD *)&g_SceneMgr.m_info[3824] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[3488] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[3828] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[3492] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[3832] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[3496] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[3836] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[3500] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[3848] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[3512] = 5;
  (RoleSystem *->LoadData()&g_SceneMgr.m_info[2832], 1);
  for ( n = 972; n < 1020; n += 4 )
  {
    v73 = *(_DWORD *)&g_SceneMgr.m_info[n + 2832];
    v74 = *(_DWORD *)&g_SceneMgr.m_info[n + 2784];
    if ( v73 < v74 )
    {
      if ( v73 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_info[n + 2832] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_info[n + 2832] = v74;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_info[5092] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5096] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5100] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5104] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5108] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5112] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5116] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5120] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5124] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5128] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5132] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5136] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5140] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5144] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5148] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[5152] = 82301;
  *(_DWORD *)&g_SceneMgr.m_info[5156] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[5160] = g_GDB->GDB_GetSkillNum(82301);
  pConfig = 4401;
  v162 = 0;
  v163 = g_GDB->GDB_GetRoleNum(4401);
  v75 = (int *)g_nSceneType;
  if ( (dword_C0438C - (int)g_nSceneType) / 12 )
  {
    g_nSceneType->Insert(g_nSceneType, (char *)g_nSceneType + 12);
    g_nSceneType->Erase(1 - ((_BYTE *)g_nSceneType - (_BYTE *)v75) / 12, &pConfig);
    v82 = (char *)g_nSceneType;
    if ( v75 != g_nSceneType )
    {
      do
      {
        v83 = v75;
        v75 += 3;
        *v83 = pConfig;
        v83[1] = v162;
        v83[2] = v163;
      }
      while ( v75 != (int *)v82 );
    }
    g_nSceneType = (char *)g_nSceneType + 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)(((_BYTE *)g_nSceneType - (_BYTE *)g_nSceneState) / 12) > 1 )
      v76 = Array::Size(&dword_C04380);
    else
      v76 = 1;
    v77 = Array::Size(&dword_C04380);
    v11 = v76 + v77 < 0;
    v78 = v76 + v77;
    v79 = v76 + v77;
    if ( v11 )
      v79 = 0;
    v80 = (char *)operator new(12 * v79);
    v152 = (char *)g_nSceneState->Insert(v75, v80);
    v152->Erase(1, &pConfig);
    v75->Insert(g_nSceneType, v152 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete(g_nSceneState);
    dword_C0438C = (int)&v80[12 * v78];
    v81 = Array::Size(&dword_C04380);
    g_nSceneState = v80;
    g_nSceneType = &v80[12 * v81 + 12];
  }
  pConfig = 316;
  v162 = 2949123;
  v163 = g_GDB->GDB_GetRoleNum(316);
  v84 = (int *)g_nSceneType;
  if ( (dword_C0438C - (int)g_nSceneType) / 12 )
  {
    g_nSceneType->Insert(g_nSceneType, (char *)g_nSceneType + 12);
    g_nSceneType->Erase(1 - ((_BYTE *)g_nSceneType - (_BYTE *)v84) / 12, &pConfig);
    v91 = (char *)g_nSceneType;
    if ( v84 != g_nSceneType )
    {
      do
      {
        v92 = v84;
        v84 += 3;
        *v92 = pConfig;
        v92[1] = v162;
        v92[2] = v163;
      }
      while ( v84 != (int *)v91 );
    }
    g_nSceneType = (char *)g_nSceneType + 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)(((_BYTE *)g_nSceneType - (_BYTE *)g_nSceneState) / 12) > 1 )
      v85 = ((_BYTE *)g_nSceneType - (_BYTE *)g_nSceneState) / 12;
    else
      v85 = 1;
    v86 = Array::Size(&dword_C04380);
    v11 = v85 + v86 < 0;
    v87 = v85 + v86;
    v88 = v85 + v86;
    if ( v11 )
      v88 = 0;
    v89 = (char *)operator new(12 * v88);
    v153 = (char *)g_nSceneState->Insert(v84, v89);
    v153->Erase(1, &pConfig);
    v84->Insert(g_nSceneType, v153 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete(g_nSceneState);
    dword_C0438C = (int)&v89[12 * v87];
    v90 = Array::Size(&dword_C04380);
    g_nSceneState = v89;
    g_nSceneType = &v89[12 * v90 + 12];
  }
  pConfig = 317;
  v162 = 983043;
  v163 = g_GDB->GDB_GetRoleNum(317);
  v93 = (int *)g_nSceneType;
  if ( (dword_C0438C - (int)g_nSceneType) / 12 )
  {
    g_nSceneType->Insert(g_nSceneType, (char *)g_nSceneType + 12);
    g_nSceneType->Erase(1 - ((_BYTE *)g_nSceneType - (_BYTE *)v93) / 12, &pConfig);
    v100 = (char *)g_nSceneType;
    if ( v93 != g_nSceneType )
    {
      do
      {
        v101 = v93;
        v93 += 3;
        *v101 = pConfig;
        v101[1] = v162;
        v101[2] = v163;
      }
      while ( v93 != (int *)v100 );
    }
    g_nSceneType = (char *)g_nSceneType + 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)(((_BYTE *)g_nSceneType - (_BYTE *)g_nSceneState) / 12) > 1 )
      v94 = ((_BYTE *)g_nSceneType - (_BYTE *)g_nSceneState) / 12;
    else
      v94 = 1;
    v95 = Array::Size(&dword_C04380);
    v11 = v94 + v95 < 0;
    v96 = v94 + v95;
    v97 = v94 + v95;
    if ( v11 )
      v97 = 0;
    v98 = (char *)operator new(12 * v97);
    v154 = (char *)g_nSceneState->Insert(v93, v98);
    v154->Erase(1, &pConfig);
    v93->Insert(g_nSceneType, v154 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete(g_nSceneState);
    dword_C0438C = (int)&v98[12 * v96];
    v99 = Array::Size(&dword_C04380);
    g_nSceneState = v98;
    g_nSceneType = &v98[12 * v99 + 12];
  }
  pConfig = 318;
  v162 = 0;
  v163 = g_GDB->GDB_GetRoleNum(318);
  v102 = (int *)g_nSceneType;
  if ( (dword_C0438C - (int)g_nSceneType) / 12 )
  {
    g_nSceneType->Insert(g_nSceneType, (char *)g_nSceneType + 12);
    g_nSceneType->Erase(1 - ((_BYTE *)g_nSceneType - (_BYTE *)v102) / 12, &pConfig);
    v109 = (char *)g_nSceneType;
    if ( v102 != g_nSceneType )
    {
      do
      {
        v110 = v102;
        v102 += 3;
        *v110 = pConfig;
        v110[1] = v162;
        v110[2] = v163;
      }
      while ( v102 != (int *)v109 );
    }
    g_nSceneType = (char *)g_nSceneType + 12;
  }
  else
  {
    if ( g_nSceneState && (unsigned int)(((_BYTE *)g_nSceneType - (_BYTE *)g_nSceneState) / 12) > 1 )
      v103 = ((_BYTE *)g_nSceneType - (_BYTE *)g_nSceneState) / 12;
    else
      v103 = 1;
    v104 = Array::Size(&dword_C04380);
    v11 = v103 + v104 < 0;
    v105 = v103 + v104;
    v106 = v103 + v104;
    if ( v11 )
      v106 = 0;
    v107 = (char *)operator new(12 * v106);
    v155 = (char *)g_nSceneState->Insert(v102, v107);
    v155->Erase(1, &pConfig);
    v102->Insert(g_nSceneType, v155 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete(g_nSceneState);
    dword_C0438C = (int)&v107[12 * v105];
    v108 = Array::Size(&dword_C04380);
    g_nSceneState = v107;
    g_nSceneType = &v107[12 * v108 + 12];
  }
  *(_DWORD *)&g_SceneMgr.m_info[4872] = 10;
  *(_DWORD *)&g_SceneMgr.m_info[4980] = 1943;
  *(_DWORD *)&g_SceneMgr.m_info[4876] = Role::CreateXueJian(3, 10);
  *(_DWORD *)&g_SceneMgr.m_info[4880] = Role::CreateLongKui(3, *(int *)&g_SceneMgr.m_info[4872]);
  *(_DWORD *)&g_SceneMgr.m_info[4884] = Role::CreateZiXuan(3, *(int *)&g_SceneMgr.m_info[4872]);
  *(_DWORD *)&g_SceneMgr.m_info[4888] = Role::CreateChangQing(3, *(int *)&g_SceneMgr.m_info[4872]);
  *(_DWORD *)&g_SceneMgr.m_info[4892] = Role::CreateHuaYing(3, *(int *)&g_SceneMgr.m_info[4872]);
  v111 = 1;
  *(_DWORD *)&g_SceneMgr.m_info[5240] = 6;
  *(_DWORD *)&g_SceneMgr.m_info[4904] = 6;
  *(_DWORD *)&g_SceneMgr.m_info[5232] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[4896] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[5236] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[4900] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[5244] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[4908] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[5248] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[4912] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[5252] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[4916] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[5256] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[4920] = 2;
  (RoleSystem *->LoadData()&g_SceneMgr.m_info[4240], 1);
  for ( ii = 972; ii < 1020; ii += 4 )
  {
    v113 = *(_DWORD *)&g_SceneMgr.m_info[ii + 4240];
    v114 = *(_DWORD *)&g_SceneMgr.m_info[ii + 4192];
    if ( v113 < v114 )
    {
      if ( v113 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_info[ii + 4240] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_info[ii + 4240] = v114;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_info[6500] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6504] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6508] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6512] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6516] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6520] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6524] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6528] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6532] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6536] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6540] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6544] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6548] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6552] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6556] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[6560] = 82001;
  *(_DWORD *)&g_SceneMgr.m_info[6564] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[6568] = g_GDB->GDB_GetSkillNum(82001);
  pConfig = 4501;
  v162 = 0;
  v163 = g_GDB->GDB_GetRoleNum(4501);
  v115 = (int *)*(int **)&g_SceneMgr.m_info[8];
  if ( (*(_DWORD *)&g_SceneMgr.m_info[12] - *(_DWORD *)&g_SceneMgr.m_info[8]) / 12 )
  {
    Array::Insert(
      *(void **)&g_SceneMgr.m_info[8],
      *(void **)&g_SceneMgr.m_info[8],
      (void *)(*(_DWORD *)&g_SceneMgr.m_info[8] + 12));
    Array::Erase(*(void **)&g_SceneMgr.m_info[8], 1 - (*(_DWORD *)&g_SceneMgr.m_info[8] - (int)v115) / 12, &pConfig);
    for ( jj = *(int **)&g_SceneMgr.m_info[8]; v115 != jj; v122[2] = v163 )
    {
      v122 = v115;
      v115 += 3;
      *v122 = pConfig;
      v122[1] = v162;
    }
    *(_DWORD *)&g_SceneMgr.m_info[8] += 12;
  }
  else
  {
    if ( !*(_DWORD *)&g_SceneMgr.m_info[4] )
      goto LABEL_148;
    if ( (unsigned int)((*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12) > 1 )
      v111 = (*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12;
    if ( *(_DWORD *)&g_SceneMgr.m_info[4] )
      v116 = (*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12;
    else
LABEL_148:
      v116 = 0;
    v117 = v116 + v111;
    v118 = v116 + v111;
    if ( v116 + v111 < 0 )
      v118 = 0;
    v119 = (char *)operator new(12 * v118);
    v156 = (char *)Array::Insert(*(void **)&g_SceneMgr.m_info[4], v115, v119);
    v156->Erase(1, &pConfig);
    v115->Insert(*(void **)&g_SceneMgr.m_info[8], v156 + 12);
    nullsub_2(*(_DWORD *)&g_SceneMgr.m_info[4], *(_DWORD *)&g_SceneMgr.m_info[8]);
    operator delete(*(void **)&g_SceneMgr.m_info[4]);
    *(_DWORD *)&g_SceneMgr.m_info[12] = &v119[12 * v117];
    if ( *(_DWORD *)&g_SceneMgr.m_info[4] )
      v120 = (*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12;
    else
      v120 = 0;
    *(_DWORD *)&g_SceneMgr.m_info[4] = v119;
    *(_DWORD *)&g_SceneMgr.m_info[8] = &v119[12 * v120 + 12];
  }
  pConfig = 306;
  v162 = 2949123;
  v163 = g_GDB->GDB_GetRoleNum(306);
  v123 = (int *)*(int **)&g_SceneMgr.m_info[8];
  if ( (*(_DWORD *)&g_SceneMgr.m_info[12] - *(_DWORD *)&g_SceneMgr.m_info[8]) / 12 )
  {
    Array::Insert(
      *(void **)&g_SceneMgr.m_info[8],
      *(void **)&g_SceneMgr.m_info[8],
      (void *)(*(_DWORD *)&g_SceneMgr.m_info[8] + 12));
    Array::Erase(*(void **)&g_SceneMgr.m_info[8], 1 - (*(_DWORD *)&g_SceneMgr.m_info[8] - (int)v123) / 12, &pConfig);
    for ( kk = *(int **)&g_SceneMgr.m_info[8]; v123 != kk; v132[2] = v163 )
    {
      v132 = v123;
      v123 += 3;
      *v132 = pConfig;
      v132[1] = v162;
    }
    *(_DWORD *)&g_SceneMgr.m_info[8] += 12;
  }
  else
  {
    if ( *(_DWORD *)&g_SceneMgr.m_info[4]
      && (unsigned int)((*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12) > 1 )
    {
      v124 = (*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12;
    }
    else
    {
      v124 = 1;
    }
    if ( *(_DWORD *)&g_SceneMgr.m_info[4] )
      v125 = (*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12;
    else
      v125 = 0;
    v126 = v125 + v124;
    v157 = v125 + v124;
    if ( v125 + v124 < 0 )
      v126 = 0;
    v127 = operator new(12 * v126);
    v128 = (char *)*(char **)&g_SceneMgr.m_info[4];
    v159 = v127;
    for ( mm = v127; v128 != (char *)v123; mm += 12 )
    {
      (void *->Copy()mm, v128);
      v128 += 12;
    }
    (void *->Erase()mm, 1, &pConfig);
    v123->Insert(*(void **)&g_SceneMgr.m_info[8], (void *)(mm + 12));
    nullsub_2(*(_DWORD *)&g_SceneMgr.m_info[4], *(_DWORD *)&g_SceneMgr.m_info[8]);
    operator delete(*(void **)&g_SceneMgr.m_info[4]);
    *(_DWORD *)&g_SceneMgr.m_info[12] = v159 + 12 * v157;
    v130 = (int *->Size()g_SceneMgr.m_info);
    *(_DWORD *)&g_SceneMgr.m_info[4] = v159;
    *(_DWORD *)&g_SceneMgr.m_info[8] = v159 + 12 * (v130 + 1);
  }
  pConfig = 307;
  v162 = 983043;
  v163 = g_GDB->GDB_GetRoleNum(307);
  v133 = (int *)*(int **)&g_SceneMgr.m_info[8];
  if ( (*(_DWORD *)&g_SceneMgr.m_info[12] - *(_DWORD *)&g_SceneMgr.m_info[8]) / 12 )
  {
    Array::Insert(
      *(void **)&g_SceneMgr.m_info[8],
      *(void **)&g_SceneMgr.m_info[8],
      (void *)(*(_DWORD *)&g_SceneMgr.m_info[8] + 12));
    Array::Erase(*(void **)&g_SceneMgr.m_info[8], 1 - (*(_DWORD *)&g_SceneMgr.m_info[8] - (int)v133) / 12, &pConfig);
    for ( nn = *(int **)&g_SceneMgr.m_info[8]; v133 != nn; v142[2] = v163 )
    {
      v142 = v133;
      v133 += 3;
      *v142 = pConfig;
      v142[1] = v162;
    }
    *(_DWORD *)&g_SceneMgr.m_info[8] += 12;
  }
  else
  {
    if ( *(_DWORD *)&g_SceneMgr.m_info[4]
      && (unsigned int)((*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12) > 1 )
    {
      v134 = (*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12;
    }
    else
    {
      v134 = 1;
    }
    if ( *(_DWORD *)&g_SceneMgr.m_info[4] )
      v135 = (*(_DWORD *)&g_SceneMgr.m_info[8] - *(_DWORD *)&g_SceneMgr.m_info[4]) / 12;
    else
      v135 = 0;
    v136 = v135 + v134;
    v160 = v135 + v134;
    if ( v135 + v134 < 0 )
      v136 = 0;
    v137 = operator new(12 * v136);
    v138 = (char *)*(char **)&g_SceneMgr.m_info[4];
    v158 = v137;
    for ( i1 = v137; v138 != (char *)v133; i1 += 12 )
    {
      (void *->Copy()i1, v138);
      v138 += 12;
    }
    (void *->Erase()i1, 1, &pConfig);
    v133->Insert(*(void **)&g_SceneMgr.m_info[8], (void *)(i1 + 12));
    nullsub_2(*(_DWORD *)&g_SceneMgr.m_info[4], *(_DWORD *)&g_SceneMgr.m_info[8]);
    operator delete(*(void **)&g_SceneMgr.m_info[4]);
    *(_DWORD *)&g_SceneMgr.m_info[12] = v158 + 12 * v160;
    v140 = (int *->Size()g_SceneMgr.m_info);
    *(_DWORD *)&g_SceneMgr.m_info[4] = v158;
    *(_DWORD *)&g_SceneMgr.m_info[8] = v158 + 12 * (v140 + 1);
  }
  pConfig = 308;
  v162 = 0;
  v163 = g_GDB->GDB_GetRoleNum(308);
  Scene::LoadConfig(&g_SceneMgr, &pConfig);
  *(_DWORD *)&g_SceneMgr.m_info[6388] = 4341;
  *(_DWORD *)&g_SceneMgr.m_info[6280] = 13;
  *(_DWORD *)&g_SceneMgr.m_info[6284] = Role::CreateXueJian(4, 13);
  *(_DWORD *)&g_SceneMgr.m_info[6288] = Role::CreateLongKui(4, *(int *)&g_SceneMgr.m_info[6280]);
  *(_DWORD *)&g_SceneMgr.m_info[6292] = Role::CreateZiXuan(4, *(int *)&g_SceneMgr.m_info[6280]);
  *(_DWORD *)&g_SceneMgr.m_info[6296] = Role::CreateChangQing(4, *(int *)&g_SceneMgr.m_info[6280]);
  *(_DWORD *)&g_SceneMgr.m_info[6300] = Role::CreateHuaYing(4, *(int *)&g_SceneMgr.m_info[6280]);
  *(_DWORD *)&g_SceneMgr.m_info[6652] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[6316] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[6648] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[6312] = 1;
  *(_DWORD *)&g_SceneMgr.m_info[6640] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[6304] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[6644] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[6308] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[6656] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[6320] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[6660] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[6324] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[6664] = 2;
  *(_DWORD *)&g_SceneMgr.m_info[6328] = 2;
  (RoleSystem *->LoadData()&g_SceneMgr.m_info[5648], 1);
  (RoleSystem *->Init()&g_SceneMgr.m_info[5648]);
  *(_DWORD *)&g_SceneMgr.m_info[51216] = 4101;
  *(_DWORD *)&g_SceneMgr.m_info[51220] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51224] = 4102;
  *(_DWORD *)&g_SceneMgr.m_info[51228] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[51232] = 4103;
  *(_DWORD *)&g_SceneMgr.m_info[51236] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51240] = 4104;
  *(_DWORD *)&g_SceneMgr.m_info[51244] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51248] = 4105;
  *(_DWORD *)&g_SceneMgr.m_info[51252] = 44;
  *(_DWORD *)&g_SceneMgr.m_info[51256] = 4106;
  *(_DWORD *)&g_SceneMgr.m_info[51260] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51264] = 4201;
  *(_DWORD *)&g_SceneMgr.m_info[51268] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51272] = 4202;
  *(_DWORD *)&g_SceneMgr.m_info[51276] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[51308] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51316] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[51332] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[51348] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51356] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51372] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51404] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51452] = -1;
  *(_DWORD *)&g_SceneMgr.m_info[51380] = 13;
  memset(&g_SceneMgr.m_info[50816], 0, 0x190u);
  *(_DWORD *)&g_SceneMgr.m_info[51280] = 4203;
  *(_DWORD *)&g_SceneMgr.m_info[51284] = 20;
  *(_DWORD *)&g_SceneMgr.m_info[51288] = 4204;
  *(_DWORD *)&g_SceneMgr.m_info[51292] = 55;
  *(_DWORD *)&g_SceneMgr.m_info[51296] = 4205;
  *(_DWORD *)&g_SceneMgr.m_info[51300] = 50;
  *(_DWORD *)&g_SceneMgr.m_info[51304] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[51312] = 4301;
  *(_DWORD *)&g_SceneMgr.m_info[51320] = 4302;
  *(_DWORD *)&g_SceneMgr.m_info[51324] = 10;
  *(_DWORD *)&g_SceneMgr.m_info[51328] = 4303;
  *(_DWORD *)&g_SceneMgr.m_info[51336] = 4304;
  *(_DWORD *)&g_SceneMgr.m_info[51340] = 20;
  *(_DWORD *)&g_SceneMgr.m_info[51344] = 4305;
  *(_DWORD *)&g_SceneMgr.m_info[51352] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[51360] = 4401;
  *(_DWORD *)&g_SceneMgr.m_info[51364] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[51368] = 4402;
  *(_DWORD *)&g_SceneMgr.m_info[51376] = 4403;
  *(_DWORD *)&g_SceneMgr.m_info[51384] = 4404;
  *(_DWORD *)&g_SceneMgr.m_info[51388] = 35;
  *(_DWORD *)&g_SceneMgr.m_info[51392] = 4405;
  *(_DWORD *)&g_SceneMgr.m_info[51396] = 58;
  *(_DWORD *)&g_SceneMgr.m_info[51400] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[51408] = 4501;
  *(_DWORD *)&g_SceneMgr.m_info[51412] = 8;
  *(_DWORD *)&g_SceneMgr.m_info[51416] = 4502;
  *(_DWORD *)&g_SceneMgr.m_info[51420] = 24;
  *(_DWORD *)&g_SceneMgr.m_info[51424] = 4503;
  *(_DWORD *)&g_SceneMgr.m_info[51428] = 38;
  *(_DWORD *)&g_SceneMgr.m_info[51432] = 4504;
  *(_DWORD *)&g_SceneMgr.m_info[51436] = 50;
  *(_DWORD *)&g_SceneMgr.m_info[51440] = 4505;
  *(_DWORD *)&g_SceneMgr.m_info[51444] = 64;
  *(_DWORD *)&g_SceneMgr.m_info[51448] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[50816] = 301;
  *(_DWORD *)&g_SceneMgr.m_info[50828] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[50824] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[50832] = 302;
  *(_DWORD *)&g_SceneMgr.m_info[50844] = 4;
  *(_DWORD *)&g_SceneMgr.m_info[50840] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[50848] = 303;
  *(_DWORD *)&g_SceneMgr.m_info[50860] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[50856] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[50864] = 304;
  *(_DWORD *)&g_SceneMgr.m_info[50876] = 20;
  *(_DWORD *)&g_SceneMgr.m_info[50872] = 50;
  *(_DWORD *)&g_SceneMgr.m_info[50880] = 305;
  *(_DWORD *)&g_SceneMgr.m_info[50892] = 30;
  *(_DWORD *)&g_SceneMgr.m_info[50888] = 60;
  *(_DWORD *)&g_SceneMgr.m_info[50896] = 321;
  *(_DWORD *)&g_SceneMgr.m_info[50908] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[50904] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[50912] = 322;
  *(_DWORD *)&g_SceneMgr.m_info[50924] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[50920] = 30;
  *(_DWORD *)&g_SceneMgr.m_info[50928] = 323;
  *(_DWORD *)&g_SceneMgr.m_info[50940] = 14;
  *(_DWORD *)&g_SceneMgr.m_info[50936] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[50944] = 324;
  *(_DWORD *)&g_SceneMgr.m_info[50956] = 23;
  *(_DWORD *)&g_SceneMgr.m_info[50952] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[50960] = 325;
  *(_DWORD *)&g_SceneMgr.m_info[51096] = 30;
  *(_DWORD *)&g_SceneMgr.m_info[50972] = 32;
  *(_DWORD *)&g_SceneMgr.m_info[50968] = 50;
  *(_DWORD *)&g_SceneMgr.m_info[50976] = 311;
  *(_DWORD *)&g_SceneMgr.m_info[50988] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[50984] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[50992] = 312;
  *(_DWORD *)&g_SceneMgr.m_info[51004] = 5;
  *(_DWORD *)&g_SceneMgr.m_info[51000] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[51008] = 313;
  *(_DWORD *)&g_SceneMgr.m_info[51020] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[51016] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[51024] = 314;
  *(_DWORD *)&g_SceneMgr.m_info[51036] = 25;
  *(_DWORD *)&g_SceneMgr.m_info[51032] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[51040] = 315;
  *(_DWORD *)&g_SceneMgr.m_info[51052] = 35;
  *(_DWORD *)&g_SceneMgr.m_info[51048] = 60;
  *(_DWORD *)&g_SceneMgr.m_info[51056] = 316;
  *(_DWORD *)&g_SceneMgr.m_info[51068] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[51064] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[51072] = 317;
  *(_DWORD *)&g_SceneMgr.m_info[51084] = 3;
  *(_DWORD *)&g_SceneMgr.m_info[51080] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[51088] = 318;
  *(_DWORD *)&g_SceneMgr.m_info[51100] = 10;
  *(_DWORD *)&g_SceneMgr.m_info[51104] = 319;
  *(_DWORD *)&g_SceneMgr.m_info[51116] = 20;
  *(_DWORD *)&g_SceneMgr.m_info[51112] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[51120] = 320;
  *(_DWORD *)&g_SceneMgr.m_info[51132] = 28;
  *(_DWORD *)&g_SceneMgr.m_info[51128] = 20;
  *(_DWORD *)&g_SceneMgr.m_info[51136] = 306;
  *(_DWORD *)&g_SceneMgr.m_info[51148] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[51144] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[51152] = 307;
  *(_DWORD *)&g_SceneMgr.m_info[51164] = 6;
  *(_DWORD *)&g_SceneMgr.m_info[51160] = 15;
  *(_DWORD *)&g_SceneMgr.m_info[51168] = 308;
  *(_DWORD *)&g_SceneMgr.m_info[51180] = 14;
  *(_DWORD *)&g_SceneMgr.m_info[51176] = 45;
  *(_DWORD *)&g_SceneMgr.m_info[51184] = 309;
  *(_DWORD *)&g_SceneMgr.m_info[51196] = 22;
  *(_DWORD *)&g_SceneMgr.m_info[51192] = 50;
  *(_DWORD *)&g_SceneMgr.m_info[51200] = 310;
  *(_DWORD *)&g_SceneMgr.m_info[51212] = 32;
  *(_DWORD *)&g_SceneMgr.m_info[51208] = 60;
  NPC::InitAll();
  for ( i2 = 0; i2 < 5; ++i2 )
  {
    result = 1408 * i2;
    g_SceneMgr.m_info[result + 1417] = 0;
    g_SceneMgr.m_info[result + 1418] = 0;
    g_SceneMgr.m_info[result + 1419] = 0;
    g_SceneMgr.m_info[result + 1420] = 0;
    g_SceneMgr.m_info[result + 1421] = 1;
    g_SceneMgr.m_info[result + 1416] = 0;
    switch ( i2 )
    {
      case 0:
        *(_DWORD *)&g_SceneMgr.m_info[1408 * i2 + 16] = 101;
        break;
      case 1:
        *(_DWORD *)&g_SceneMgr.m_info[1408 * i2 + 16] = 104;
        break;
      case 2:
        *(_DWORD *)&g_SceneMgr.m_info[1408 * i2 + 16] = 106;
        break;
      case 3:
        *(_DWORD *)&g_SceneMgr.m_info[1408 * i2 + 16] = 107;
        break;
      case 4:
        *(_DWORD *)&g_SceneMgr.m_info[1408 * i2 + 16] = 102;
        break;
      default:
        continue;
    }
  }
  MEMORY[0xBFDB70] = 50529027;
  MEMORY[0xBFDB74] = 50529027;
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

  if ( *(_DWORD *)&g_SceneMgr.m_info[54116] )
  {
    gbSound2DNode::Stop(*(gbSound2DNode **)&g_SceneMgr.m_info[54116]);
    *(_DWORD *)&g_SceneMgr.m_info[54116] = 0;
  }
  return result;
}
