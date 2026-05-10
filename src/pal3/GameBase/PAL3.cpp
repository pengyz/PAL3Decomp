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
int CombatEffectUpdate(...);
int EffectUpdate(...);
int FileSysInit(...);
int InputUpdate(...);
int NPCAnimUpdate(...);
int SceneMgrUpdate(...);
int SceneUpdate(...);
int ScriptUpdate(...);
int UINotifyUpdate(...);
int UIPostUpdate(...);
int UISceneUpdate(...);
int UIUpdate(...);
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
extern int dword_C116F4;
extern int dword_C11700;
extern int nullsub_2;
extern int nullsub_3;
extern void *off_56A66C;
extern void *off_56A694;
extern void *off_56A6A8;
extern void *off_56A6B4;
extern void *off_583A1C;
extern void *off_586180;
extern int stru_BFAB60;
extern int stru_D8C2B8;
extern int unk_8ACBF0;
extern int unk_C11718;
extern int unk_C1171C;
extern int unk_C11720;
extern int unk_C11740;
extern int unk_C11744;
extern int unk_C11748;
extern int unk_C11750;
extern int unk_C11751;
extern int unk_C11754;
extern int unk_C11758;
extern int unk_C12B28;
extern int unk_C12B2C;
extern int unk_C12B30;

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
  &unk_8ACBF0;
}

// 0x004047F0
// attributes: thunk
PAL3::~PAL3()
{
  PAL3::Destroy();
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
  CEffectSystem *v16; // eax
  RenderTarget *v17; // eax
  RenderTarget3 *v18; // eax
  RenderTarget2 *v19; // eax
  RenderTarget4 *v20; // eax
  CEffectSystem *v21; // eax
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
  ((UIManager *)&unk_C11758)->LoadShadowTexture();
  ((Logger *)g_Logger)->RegisterCallbacks();
  ((Logger *)g_Logger)->Write("%s Bulid %s %s", aV104, aJan52004, a163941);
  ((Logger *)g_Logger)->Write(aGameCreateOk);
  v7 = (CCBSystem *)operator new(0x162D8u);
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
  v9 = (SceneMgr *)operator new(0xA930u);
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
    v21 = (CEffectSystem *)CEffectSystem::DestroyAllEffect();
    v21->IsVisible();
    PAL3::GetCommandLineParam();
  }
  else
  {
    ((CGameData *)&g_GameData)->Init();
    CGameData_Load((int)&g_GameData, (CUtil *)4);
    v12 = (RenderTarget *)CRenderTarget::GetInstance();
    v12->Create();
    v13 = (RenderTarget3 *)RenderTarget3::GetInstance();
    v13->Init();
    v14 = (RenderTarget2 *)CRenderTarget2::GetInstance();
    v14->Init();
    v15 = (RenderTarget4 *)RenderTarget4::GetInstance();
    v15->Init();
    v16 = (CEffectSystem *)CEffectSystem::DestroyAllEffect();
    v16->IsVisible();
  }
  (*(void (__stdcall **)(_DWORD, char *))(**(_DWORD **)(g_Input.KeyInfo[177].Data + 1816) + 28))(
    *(_DWORD *)(g_Input.KeyInfo[177].Data + 1816),
    v35);
  if ( !v36 )
    BYTE1(g_Input.KeyInfo[180].Data) = 1;
  SoundSystem::Init();
  ((OpenBaseFile *)&v32)->OpenBaseFile();
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
  *(_DWORD *)g_GDB.m_ItemData[360].name = v24;
  v24->LoadFromFile(aObjectG02Cvd, 0, 0);
  v25 = (gbVFileSystem *)operator new(0x118u);
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
  return ((OpenNULLFile *)&v32)->OpenNULLFile();
}

// 0x00404FF0
void PAL3::InitGFX()
{
  gbActorMgr *v0; // eax
  gbActorMgr *v1; // eax
  char *v2; // eax
  char *v3; // eax
  _DWORD *v4; // esi
  _BYTE v5[1040]; // [esp+20h] [ebp-81Ch] BYREF
  char ArgList[1024]; // [esp+430h] [ebp-40Ch] BYREF
  int v7; // [esp+838h] [ebp-4h]

  g_Input.KeyInfo[177].Data = (int)gbCreateGraphManager((struct gbGfxDriverInfo *)&g_Input.KeyInfo[119].CountMode);
  if ( !g_Input.KeyInfo[177].Data )
  {
    qmemcpy(&v5[16], ((Logger *)ArgList)->FormatException(aCreateGfxManag, aDProjectPal3Ga_0, 401), 0x400u);
    _CxxThrowException(&v5[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v0 = (gbActorMgr *)operator new(0xCu);
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
  v2 = (char *)operator new(0x220u);
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
  sub_41D100((_DWORD *)g_Input.KeyInfo[177].CountMode, 0);
  ((CameraCtrl *)g_Input.KeyInfo[177].CountMode)->SetAsCurrent(3);
  *(_DWORD *)&v5[12] = 3;
  *(_DWORD *)v5 = -16777216;
  *(_DWORD *)&v5[4] = 1065353216;
  ((gbGfxManager *)g_Input.KeyInfo[177].Data)->SetClearParam((struct gbClearParam *)v5);
  v4 = (_DWORD *)operator new(0xD8u);
  v7 = 2;
  if ( v4 )
  {
    v4[1] = 1;
    * v4 = (*)gbRefObject::`vftable';
    * v4 = (*)gbVolumeModifier::`vftable';
    v4[24] = 0;
    v4[25] = 0;
    v4[26] = 0;
    LOBYTE(v7) = 3;
    v4[40] = 0;
    v4[41] = 0;
    v4[42] = 0;
    ((gbVec3D *)(v4 + 43))->gbVec3D(0.0, 0.0, 0.0);
    * v4 = (*)&off_56A694;
  }
  else
  {
    v4 = 0;
  }
  v7 = -1;
  v4->Init(2);
  v4[7] = 1065353216;
  v4[8] = 1065353216;
  v4[9] = 1065353216;
  v4[10] = 1065353216;
  v4[12] = 1;
  v4[11] = 1;
  v4[3] = 1049582633;
  v4[4] = 1049582633;
  v4[5] = 1049582633;
  v4[16] = 1092616192;
  v4[15] = 1092616192;
  v4[6] = 1065353216;
  ((gbVolModNode *)&g_GDB.m_ItemData[360].name[12])->SetVolModObj((struct gbVolumeModifier *)v4);
  ((gbRefObject *)v4)->Release();
}

// 0x00405330
char PAL3::CreateEffectSystem()
{
  gbSnow *v0; // esi
  gbRain *v1; // eax
  gbRain *v2; // esi
  char *v3; // eax
  float *v4; // eax
  char v5; // al
  OpenBaseFile v7; // [esp+8h] [ebp-85Ch] BYREF
  void *v8; // [esp+Ch] [ebp-858h]
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
  v0 = (gbSnow *)operator new(0x58u);
  v8 = v0;
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
  v1 = (gbRain *)operator new(0x50u);
  v2 = v1;
  v8 = v1;
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
  v3 = (char *)operator new(0x158u);
  v8 = v3;
  LOBYTE(v13) = 3;
  if ( v3 )
    v4 = (float *)sub_4C5820(v3, g_Input.KeyInfo[177].Data);
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
    ((OpenNULLFile *)&v7)->OpenNULLFile();
    return 1;
  }
  else
  {
    ((OpenNULLFile *)&v7)->OpenNULLFile();
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
    sub_4C5840((int *)g_Input.KeyInfo[178].Data);
    operator delete(Data);
  }
  g_Input.KeyInfo[178].Data = 0;
  return 1;
}

// 0x004055D0
int PAL3::Update@<eax>(double st6_0@<st1>, int a1)
{
  int v2; // edi
  unsigned __int16 *v3; // esi
  __int16 KeyState; // ax
  BOOL v5; // eax
  DWORD Time; // eax
  int PressTime; // esi
  int v8; // ebx
  int v9; // eax
  _DWORD *v10; // eax
  float *m_pCollisionNode; // ebp
  int v12; // ebx
  __int8 *v13; // esi
  double v14; // st7
  double v15; // st7
  int *v16; // eax
  double v17; // st7
  _DWORD *v18; // eax
  void *v19; // ecx
  int *v20; // eax
  PtrArray *v21; // eax
  float *Instance; // eax
  _DWORD *v23; // eax
  void *v24; // ecx
  char *v25; // eax
  char *v26; // eax
  CUtil *Mode; // eax
  char *v28; // eax
  gbAudioManager *AudioManager; // esi
  char *v30; // eax
  char *v31; // eax
  ScreenEffect *v32; // eax
  int result; // eax
  int v34; // [esp+4h] [ebp-2Ch]
  int v35; // [esp+4h] [ebp-2Ch]
  float dt; // [esp+18h] [ebp-18h]
  float dt_4; // [esp+1Ch] [ebp-14h]
  float v38; // [esp+20h] [ebp-10h]
  gbVec3D v39; // [esp+24h] [ebp-Ch] BYREF

  *(float *)&g_Input.KeyInfo[181].Data = *(float *)&g_Input.KeyInfo[181].Data + *(float *)&a1;
  ((GRPinput *)&g_Input)->GRPinput();
  v2 = 0;
  v3 = (unsigned __int16 *)(&g_PAL3Data + 224);
  do
  {
    KeyState = ((GRPinput *)&g_Input)->GetKeyState(*v3);
    v5 = KeyState == 1 || KeyState == 3;
    v34 = v5;
    Time = timeGetTime();
    ((GRPinput *)&g_Input)->SetMouseAbs(Time, v2, v34);
    ++v3;
    ++v2;
  }
  while ( (int)v3 < (int)((unsigned __int16 *)&g_PAL3Data + 153) );
  PressTime = g_Input.KeyInfo[177].PressTime;
  v8 = SceneUpdate((int)&g_GameData, a1, 1);
  v9 = g_Input.KeyInfo[177].PressTime;
  if ( g_Input.KeyInfo[177].PressTime != PressTime )
  {
    PressTime->IfHideFightSucceed();
    v9 = g_Input.KeyInfo[177].PressTime;
  }
  switch ( v9 )
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
      if ( BYTE1(stru_D8C2B8.m_keyStates[6]) )
      {
        BYTE1(stru_D8C2B8.m_keyStates[6]) = 0;
        a1->RunSceneScript();
      }
      InputUpdate(g_Input.KeyInfo[177].CountMode, a1);
      if ( g_Input.KeyInfo[177].PressTime != 9 )
      {
        if ( v8 )
        {
          UIQuadManager::GetInstance();
          UIQuadManager_Reset();
        }
        else
        {
          CameraUpdate_Internal(*(float *)&a1);
        }
        ScriptUpdate(a1);
      }
      v23 = (_DWORD *)UISceneUpdate();
      UIUpdate(v23, st6_0, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      SceneMgrUpdate((float *)g_Input.KeyInfo[178].CountMode, *(float *)&g_Input.KeyInfo[176].PressTime);
      UIPostUpdate(v24);
      v25 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v25)->AudioUpdate();
      if ( g_Input.KeyInfo[177].PressTime != 2 && g_Input.KeyInfo[177].PressTime != 9 )
        PressTime->IfHideFightSucceed();
      goto LABEL_64;
    case 3:
      ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->CombatUpdate(*(float *)&a1);
      CombatEffectUpdate(g_Input.KeyInfo[178].Data, *(float *)&a1);
      v26 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v26)->AudioUpdate();
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
      Mode = (CUtil *)((CGameData *)&g_GameData)->GetMode();
      CGameData_Load((int)&g_GameData, Mode);
      CombatEnter();
      if ( (g_nGameFlags & 4) == 0 )
        goto LABEL_54;
      v28 = (char *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)v28)->GetAudioManager();
      if ( !AudioManager )
        goto LABEL_54;
      if ( unk_C11751 )
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
        v30 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v30)->AudioStopAll();
        goto LABEL_54;
      }
      v31 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v31)->AudioFadeOut();
LABEL_54:
      if ( byte_5833D0 || !dword_5833CC )
      {
        if ( unk_C11754 )
          *(_DWORD *)(unk_C11754 + 632) = 0;
      }
      else
      {
        CGameData_Load((int)&g_GameData, (CUtil *)0xF);
        PalScriptMgr::IfHaveScript();
      }
LABEL_59:
      unk_C11748 = 0;
      unk_C11750 = 0;
      unk_C1171C = 0x7FFFFFFF;
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
      MiniGame2Update((_DWORD **)g_Input.KeyInfo[178].PressTime, a1);
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
          CGameData_Load((int)&g_GameData, (CUtil *)4);
        }
      }
      else if ( *(float *)&g_Input.KeyInfo[176].CountMode >= 60.0 )
      {
        ((PAL3 *)-1)->EndWolf();
        goto LABEL_64;
      }
      a1->RunSceneScript();
      InputUpdate(g_Input.KeyInfo[177].CountMode, a1);
      ScriptUpdate(a1);
      v10 = (_DWORD *)UISceneUpdate();
      UIUpdate(v10, st6_0, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      if ( g_Input.KeyInfo[174].Data )
        goto LABEL_64;
      if ( !v8 )
        CameraUpdate_Internal(*(float *)&a1);
      m_pCollisionNode = (float *)g_SceneMgr.m_pCollisionNode;
      v12 = 1;
      v13 = (__int8 *)&g_SceneMgr._midRegion[12];
      while ( 1 )
      {
        if ( *((_DWORD *)v13 + 155) )
        {
          dt = m_pCollisionNode[1] - *((float *)v13 - 2);
          v14 = m_pCollisionNode[2] - *((float *)v13 - 1);
          v39.x = dt;
          dt_4 = v14;
          v15 = m_pCollisionNode[3] - *(float *)v13;
          v39.y = dt_4;
          v38 = v15;
          v39.z = v38;
          if ( 12.0 + 12.0 > ((gbVec3D *)&v39)->Length() )
            break;
        }
        v13 += 8704;
        ++v12;
        if ( (int)v13 >= (int)&g_SceneMgr.m_pScriptCtrl )
          goto LABEL_64;
      }
      v12->EndWolf();
      goto LABEL_64;
    case 8:
      if ( PAL3::EntryCatchGhost() )
      {
        PAL3::EndHideFight();
        RoleSystemNotify(g_SceneMgr.m_pCollisionNode);
        v16 = ((PalScriptMgr *)0x6A5u)->Destroy(0);
LABEL_33:
        v35 = (int)v16;
        v21 = (PtrArray *)SoundContext::GetInstance();
        CScreenMode_SetResolution(v21, 0, v35);
        a1->RunSceneScript();
        goto LABEL_64;
      }
      v17 = *(float *)&g_Input.KeyInfo[176].CountMode + *(float *)&a1;
      *(float *)&g_Input.KeyInfo[176].CountMode = v17;
      if ( v17 >= 180.0 )
        goto LABEL_32;
      a1->RunSceneScript();
      InputUpdate(g_Input.KeyInfo[177].CountMode, a1);
      ScriptUpdate(a1);
      v18 = (_DWORD *)UISceneUpdate();
      UIUpdate(v18, st6_0, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      if ( !v8 )
        CameraUpdate_Internal(*(float *)&a1);
      UIPostUpdate(v19);
      if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) != 4 )
      {
        v20 = (int *)UISceneUpdate();
        if ( UINotifyUpdate(v20) )
        {
LABEL_32:
          RoleSystemNotify(g_SceneMgr.m_pCollisionNode);
          PAL3::EndHideFight();
          v16 = ((PalScriptMgr *)0x6A6u)->Destroy(0);
          goto LABEL_33;
        }
      }
LABEL_64:
      v32 = (ScreenEffect *)ScreenEffectMgr::GetInstance();
      RenderPost((int)v32, a1);
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
  UIRenderObj *v22; // eax
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
      v3->Rotate(unk_C12B28, &v27);
      v28.x = 0.0;
      v28.y = 1.0;
      v28.z = 0.0;
      v3->Rotate(unk_C12B2C, &v28);
      v29.x = 0.0;
      v29.y = 0.0;
      v29.z = 1.0;
      v3->Rotate(unk_C12B30, &v29);
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
      if ( stru_D8C2B8.KeyTransformation[9] == 2 )
      {
        Top = (gbMatrix4 *)v3->GetTop();
        Top->TransformPlane();
        (*(void (**)(int, int *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 112))(
          g_Input.KeyInfo[177].Data,
          &stru_D8C2B8.KeyTransformation[9]);
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
      ((UIManager *)&unk_C11758)->Render();
      ((SceneMgr *)g_Input.KeyInfo[178].CountMode)->RenderAll();
      if ( g_Input.KeyInfo[177].CountMode )
        v12 = (struct gbCamera *)(g_Input.KeyInfo[177].CountMode + 4);
      else
        v12 = 0;
      ((gbSceneGraph *)v0)->Begin(v12);
      *(_BYTE *)(v0 + 19244) = 0;
      UIScene::CombatCheck();
      sub_410430(v3);
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
  v22 = (UIRenderObj *)UIQuadManager::GetInstance();
  v22->UIRenderObj();
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
  if ( !g_SceneMgr.m_slot4[832]
    && !g_SceneMgr.m_slot4[833]
    && !g_SceneMgr.m_slot4[834]
    && !g_SceneMgr.m_slot4[835]
    && !g_SceneMgr.m_slot4[836] )
  {
    g_SceneMgr.m_slot4[832] = 1;
    g_SceneMgr.m_slot4[833] = 1;
    g_SceneMgr.m_slot4[834] = 0;
    g_SceneMgr.m_slot4[835] = 1;
    g_SceneMgr.m_slot4[836] = 0;
  }
  if ( !unk_C11718 )
    PAL3::UpdateSubsystems();
  ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->ProcMagicWait((int)dword_C11700, 1);
  return CGameData_Load((int)&g_GameData, (CUtil *)6);
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
    ((GRPinput *)&g_PAL3Data)->GetKeyState(v13);
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
  ((std *)&g_PAL3Data)->string::_Freeze();
  if ( v8 )
    v9 = v8 - *((_DWORD *)&g_PAL3Data + 1);
  else
    v9 = 0;
  if ( v6 )
    v6 -= v8;
  if ( *((_DWORD *)&g_PAL3Data + 2) < v9 )
    std::_Xran();
  ((std *)&g_PAL3Data)->string::_Split();
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
  __int8 *midRegion; // esi
  int (***v2)(_DWORD, _DWORD); // eax
  int result; // eax

  g_Input.KeyInfo[174].Data = 0;
  g_Input.KeyInfo[173].PressTime = a1;
  if ( a1 )
  {
    *(_DWORD *)(g_Input.KeyInfo[177].CountMode + 448) = 1;
    ((RoleSystem *)g_Input.KeyInfo[177].CountMode)->SetActive((int)&g_SceneMgr.m_slot4[840]);
  }
  sub_4070A0(aSoftwareSoftst, (DWORD)aSGameA, 1);
  ((PalScriptMgr *)0x63u)->Destroy(0);
  midRegion = (__int8 *)g_SceneMgr._midRegion;
  do
  {
    sub_419AE0(midRegion);
    midRegion += 8704;
  }
  while ( (int)midRegion < (int)&g_SceneMgr.m_pGameData );
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
  __int8 *v1; // esi
  void (***v2)(_DWORD, int); // eax
  PtrArray *v3; // eax
  PtrArray *Instance; // eax
  int *v5; // [esp-4h] [ebp-18h]
  int *v6; // [esp-4h] [ebp-18h]
  _DWORD v7[5]; // [esp+0h] [ebp-14h]
  void *retaddr; // [esp+14h] [ebp+0h]

  v1 = (__int8 *)&g_SceneMgr._midRegion[1264];
  do
  {
    RoleSystemNotify((int)(v1 - 1264));
    *(_DWORD *)v1 = 2;
    v1 += 8704;
  }
  while ( (int)v1 < (int)&g_SceneMgr.m_szUIString[280] );
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
      Instance = (PtrArray *)SoundContext::GetInstance();
      CScreenMode_SetResolution(Instance, 0, (int)v6);
    }
    else
    {
      v5 = ((PalScriptMgr *)0x62u)->Destroy(0);
      v3 = (PtrArray *)SoundContext::GetInstance();
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
  __int32 m_pCollisionNode; // ebx
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
  m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
  if ( g_SceneMgr.m_pCollisionNode )
  {
    v6 = (RoleSystem *)UISceneUpdate();
    RolePtr = v6->GetRolePtr(*(_DWORD *)(m_pCollisionNode + 628));
    v8 = (__int64)((*(float *)(m_pCollisionNode + 4) - *(float *)(RolePtr + 128))
                 / *(float *)&g_Input.KeyInfo[171].HoldTime);
    v9 = (__int64)((*(float *)(m_pCollisionNode + 12) - *(float *)(RolePtr + 136))
                 / *(float *)&g_Input.KeyInfo[171].HoldTime);
    if ( v8 < 0 || (v10 = *(_DWORD *)(RolePtr + 152), v8 >= v10) || (int)v9 < 0 || (int)v9 >= *(_DWORD *)(RolePtr + 156) )
      v11 = 2;
    else
      v11 = *(unsigned __int8 *)(*(_DWORD *)(RolePtr + 160) + 8 * (v8 + v9 * v10) + 5);
    for ( i = 0; i < 6; ++i )
      dword_C11700[i] = *(_DWORD *)(a1 + 4 * i);
    v13 = UISceneUpdate();
    v14 = (const char *)UISceneUpdate();
    sprintf(Buffer, "%s_%s", v14, (const char *)(v13 + 32));
    ((PalScript *)&stru_BFAB60)->SetDirectory(Buffer);
    sprintf(Buffer, "%d", v11);
    if ( !sub_431C10(&stru_BFAB60, Buffer, unk_C11720, 32) )
      sub_431C10(&stru_BFAB60, aDefault, unk_C11720, 32);
    ((PalScript *)&stru_BFAB60)->SetDirectory(dir);
    if ( sub_431C10(&stru_BFAB60, unk_C11720, Buffer, 256) )
      unk_C11740 = atoi(Buffer);
    else
      unk_C11740 = 1;
    if ( a2 == 1 )
      unk_C11744 = 2;
    else
      unk_C11744 = a2 == 2;
    unk_C11754 = a3;
    unk_C11751 = a4;
    result = ((CCBSystem *)g_Input.KeyInfo[178].HoldTime)->ProcMagicWait((int)dword_C11700, 0);
    if ( result )
    {
      if ( !a4 || !CScreenMode::GetInstance()[4] )
      {
        v15 = (char *)UISceneUpdate();
        Instance = (char *)CScreenMode::GetInstance();
        sub_53E680((int)Instance, v15);
      }
      return CGameData_Load((int)&g_GameData, (CUtil *)6);
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
  if ( g_SceneMgr._gap_c5e0[849] )
    LOBYTE(v14[32]) = 6;
  PAL3::UpdateSubsystems();
  return ((PAL3 *)v4)->StartCombat(a2, a3, 0);
}

// 0x00407640
char PAL3::EntryCatchGhost()
{
  int v0; // esi
  int *i; // edi
  __int32 m_pCollisionNode; // esi
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
      if ( CCBStageRole_GetByIndex(&g_SceneMgr.m_slot4[792], &v11) )
        break;
      if ( ++v0 >= 3 )
        return 0;
    }
  }
  else
  {
    m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
    v7 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
    v4 = (RoleSystem *)UISceneUpdate();
    RolePtr = v4->GetRolePtr(v7);
    v6 = (__int64)((*(float *)(m_pCollisionNode + 4) - *(float *)(RolePtr + 128))
                 / *(float *)&g_Input.KeyInfo[171].HoldTime);
    v9 = (__int64)((*(float *)(m_pCollisionNode + 12) - *(float *)(RolePtr + 136))
                 / *(float *)&g_Input.KeyInfo[171].HoldTime);
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
    RoleSystemNotify(g_SceneMgr.m_pCollisionNode);
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
  ((UIWnd *)&g_SceneMgr.m_pCameraCtrl)->Create(0, pRect, 0);
  ((UIScene *)&g_SceneMgr.m_pCameraCtrl)->LoadResource(aUiSceneTiao);
  ((MvcViewport *)&g_SceneMgr.m_pCameraCtrl)->SetController(1082130432);
  ((UIWnd *)&g_SceneMgr.m_pCameraCtrl)->Destroy(0);
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
  __int8 *v2; // esi
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
  _DWORD *v14; // edi
  int v15; // eax
  int j; // eax
  int *v17; // ecx
  int k; // eax
  int v19; // ecx
  __int32 v20; // edx
  int v21; // eax
  int *v22; // esi
  int v23; // edi
  int v24; // eax
  int v25; // ebp
  int v26; // eax
  _DWORD *v27; // edi
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
  _DWORD *v40; // edi
  int v41; // eax
  char *v42; // eax
  int *v43; // edx
  int *v44; // esi
  int v45; // edi
  int v46; // eax
  int v47; // ebp
  int v48; // eax
  _DWORD *v49; // edi
  int v50; // eax
  char *v51; // eax
  int *v52; // ecx
  int *v53; // esi
  int v54; // edi
  int v55; // eax
  int v56; // ebp
  int v57; // eax
  _DWORD *v58; // edi
  int v59; // eax
  char *v60; // eax
  int *v61; // ecx
  int *v62; // esi
  int v63; // edi
  int v64; // eax
  int v65; // ebp
  int v66; // eax
  _DWORD *v67; // edi
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
  _DWORD *v80; // edi
  int v81; // eax
  int ii; // eax
  int *v83; // ecx
  int *v84; // esi
  int v85; // edi
  int v86; // eax
  int v87; // ebp
  int v88; // eax
  _DWORD *v89; // edi
  int v90; // eax
  int jj; // eax
  int *v92; // ecx
  int *v93; // esi
  int v94; // edi
  int v95; // eax
  int v96; // ebp
  int v97; // eax
  _DWORD *v98; // edi
  int v99; // eax
  int kk; // eax
  int *v101; // ecx
  int *v102; // esi
  int v103; // edi
  int v104; // eax
  int v105; // ebp
  int v106; // eax
  _DWORD *v107; // edi
  int v108; // eax
  int mm; // eax
  int *v110; // ecx
  __int32 v111; // ebp
  int nn; // eax
  int v113; // ecx
  int v114; // edx
  int *m_pAddEffect2; // esi
  __int32 v116; // edx
  __int32 v117; // edi
  __int32 v118; // eax
  _DWORD *v119; // ebp
  __int32 v120; // edx
  __int32 i1; // eax
  int *v122; // edx
  int *v123; // esi
  __int32 v124; // ebp
  __int32 v125; // edx
  __int32 v126; // eax
  _DWORD *v127; // eax
  char *m_pSceneRoot; // ebp
  _DWORD *i3; // edi
  int v130; // eax
  __int32 i2; // eax
  int *v132; // ecx
  int *v133; // esi
  __int32 v134; // ebp
  __int32 v135; // edx
  __int32 v136; // eax
  _DWORD *v137; // eax
  char *v138; // ebp
  _DWORD *i5; // edi
  int v140; // eax
  __int32 i4; // eax
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
  __int32 v157; // [esp+10h] [ebp-28h]
  __int32 v158; // [esp+10h] [ebp-28h]
  __int32 v159; // [esp+14h] [ebp-24h]
  __int32 v160; // [esp+14h] [ebp-24h]
  int pConfig; // [esp+18h] [ebp-20h] BYREF
  int v162; // [esp+1Ch] [ebp-1Ch]
  int v163; // [esp+20h] [ebp-18h]
  _DWORD v164[5]; // [esp+24h] [ebp-14h] BYREF

  memset(byte_DE5220, 0, 0x28u);
  if ( *(_DWORD *)&g_SceneMgr._gap_c5e0[844] )
  {
    (***(void (****)(_DWORD, int))&g_SceneMgr._gap_c5e0[844])(*(_DWORD *)&g_SceneMgr._gap_c5e0[844], 1);
    *(_DWORD *)&g_SceneMgr._gap_c5e0[844] = 0;
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
  *(_DWORD *)&g_SceneMgr._gap_c93c[8] = 0;
  *(_DWORD *)g_SceneMgr._gap_c93c = 0;
  CCBStageRole_Reset(&g_SceneMgr.m_slot4[792]);
  *(_DWORD *)&g_SceneMgr.m_slot4[784] = *(_DWORD *)&g_SceneMgr.m_slot4[780];
  dword_586158 = 35;
  v1 = g_RoleTeam2;
  do
  {
    * v1 = (*)*(v1 - 1);
    v1 += 4;
  }
  while ( (int)v1 < (int)&g_SceneMgr.m_pCamera );
  g_SceneMgr._gap_c5e0[849] = 0;
  memset(&g_Input.KeyInfo[196], 0, 0x20u);
  g_Input.KeyInfo[197].HoldTime = 31;
  *(_DWORD *)&g_SceneMgr._gap_c93c[4] = 0;
  memset(&g_SceneMgr.m_pAddEffect, 0, 0x1B80u);
  v164[0] = dword_58619C;
  v164[1] = dword_586198;
  v164[2] = dword_586194;
  v164[3] = &dword_586190;
  v164[4] = dword_58618C;
  v145 = 0;
  v2 = (__int8 *)&g_SceneMgr.m_slot4[1014];
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
  while ( (int)v2 < (int)&g_SceneMgr._gap_c5e0[158] );
  ((Camera *)dword_C020F8)->SetParams((int)"109");
  byte_C021A4 = 5;
  v5 = *(_DWORD *)g_SceneMgr._gap_c93c;
  strcpy(byte_C021A6, "109");
  dword_C025E8 = 0;
  dword_C02370 = 0;
  dword_C02374 = 1;
  byte_C021A5 = -1;
  v5->SetParams();
  ((Camera *)dword_BFFDB0)->SetParams((int)"DXD");
  strcpy(byte_BFFE5E, "DXD");
  dword_C002A0 = 1;
  dword_C00028 = 0;
  ((Camera *)&g_Input.KeyInfo[198])->SetParams((int)&off_586180);
  strcpy((char *)&g_Input.KeyInfo[208].PressTime + 2, (const char *)&off_586180);
  dword_BFE0A0 = 1;
  g_Input.KeyInfo[237].CountMode = 0;
  ((CameraSystem *)&g_SceneMgr.m_slot4[840])->Init();
  g_SceneMgr.m_nCameraState = 0;
  ((RoleSystem *)g_Input.KeyInfo[177].CountMode)->SetActive((int)&g_SceneMgr.m_slot4[840]);
  g_SceneMgr.m_slot4[832] = 1;
  g_SceneMgr.m_slot4[833] = 0;
  g_SceneMgr.m_slot4[834] = 0;
  g_SceneMgr.m_slot4[835] = 0;
  g_SceneMgr.m_slot4[836] = 0;
  g_SceneMgr.m_slot0[774] = 3;
  g_SceneMgr.m_slot1[774] = 5;
  g_SceneMgr.m_slot2[774] = 1;
  g_SceneMgr.m_slot3[774] = 2;
  g_SceneMgr.m_slot4[774] = 4;
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
  *(_DWORD *)&g_SceneMgr.m_slot0[388] = 2224;
  *(_DWORD *)&g_SceneMgr.m_slot0[392] = 10;
  *(_DWORD *)&g_SceneMgr.m_slot0[220] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[224] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[228] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[232] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[236] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[240] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[244] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[248] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[252] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[256] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[260] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[264] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[268] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[272] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[276] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[280] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[284] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot0[288] = 0;
  pConfig = 301;
  v162 = 0;
  RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(301);
  v8 = (int *)g_RoleTeam2[0];
  v163 = RoleNum;
  if ( (dword_C0435C - g_RoleTeam2[0]) / 12 )
  {
    ((Array *)g_RoleTeam2[0])->Insert((void *)g_RoleTeam2[0], (void *)(g_RoleTeam2[0] + 12));
    ((Array *)g_RoleTeam2[0])->Erase(1 - (g_RoleTeam2[0] - (int)v8) / 12, &pConfig);
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
    v14 = (_DWORD *)operator new(12 * v13);
    v146 = (char *)g_RoleTeam1->Insert(v8, v14);
    v146->Erase(1, &pConfig);
    v8->Insert((void *)g_RoleTeam2[0], v146 + 12);
    nullsub_2(g_RoleTeam1, g_RoleTeam2[0]);
    operator delete(g_RoleTeam1);
    dword_C0435C = (int)&v14[3 * v12];
    v15 = ((Array *)&dword_C04350)->Size();
    g_RoleTeam1 = v14;
    g_RoleTeam2[0] = (int)&v14[3 * v15 + 3];
  }
  *(_DWORD *)&g_SceneMgr.m_slot0[108] = 0;
  *(_DWORD *)g_SceneMgr.m_slot0 = 1;
  *(_DWORD *)&g_SceneMgr.m_slot0[4] = ((Role *)0)->CreateXueJian(1);
  *(_DWORD *)&g_SceneMgr.m_slot0[8] = ((Role *)0)->CreateLongKui(*(int *)g_SceneMgr.m_slot0);
  *(_DWORD *)&g_SceneMgr.m_slot0[12] = ((Role *)0)->CreateZiXuan(*(int *)g_SceneMgr.m_slot0);
  *(_DWORD *)&g_SceneMgr.m_slot0[16] = ((Role *)0)->CreateChangQing(*(int *)g_SceneMgr.m_slot0);
  *(_DWORD *)&g_SceneMgr.m_slot0[20] = ((Role *)0)->CreateHuaYing(*(int *)g_SceneMgr.m_slot0);
  *(_DWORD *)&g_SceneMgr.m_slot0[360] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot0[24] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot0[368] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot0[32] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot0[372] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot0[36] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot0[364] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot0[28] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot0[384] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot0[48] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot0[376] = 6;
  *(_DWORD *)&g_SceneMgr.m_slot0[40] = 6;
  *(_DWORD *)&g_SceneMgr.m_slot0[380] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot0[44] = 1;
  ((RoleSystem *)&g_SceneMgr.m_pAddEffect)->LoadData(1);
  for ( k = 972; k < 1020; k += 4 )
  {
    v19 = *(__int32 *)((char *)&g_SceneMgr.m_pAddEffect + k);
    v20 = *(int *)((char *)&g_nSceneFlags + k);
    if ( v19 < v20 )
    {
      if ( v19 <= 0 )
        *(__int32 *)((char *)&g_SceneMgr.m_pAddEffect + k) = 0;
    }
    else
    {
      *(__int32 *)((char *)&g_SceneMgr.m_pAddEffect + k) = v20;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_slot1[220] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[224] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[228] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[232] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[236] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[240] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[244] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[248] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[252] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[256] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[260] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[264] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[268] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[272] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[276] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot1[280] = 82201;
  *(_DWORD *)&g_SceneMgr.m_slot1[284] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot1[288] = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82201);
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
    v27 = (_DWORD *)operator new(12 * v26);
    v147 = (char *)arr->Insert(v22, v27);
    v147->Erase(1, &pConfig);
    v22->Insert(end, v147 + 12);
    nullsub_2(arr, end);
    operator delete(arr);
    dword_C0436C = (int)&v27[3 * v25];
    v28 = ((Array *)&dword_C04360)->Size();
    arr = v27;
    end = &v27[3 * v28 + 3];
  }
  *(_DWORD *)&g_SceneMgr.m_slot1[108] = 0;
  *(_DWORD *)g_SceneMgr.m_slot1 = 1;
  *(_DWORD *)&g_SceneMgr.m_slot1[4] = ((Role *)1)->CreateXueJian(1);
  *(_DWORD *)&g_SceneMgr.m_slot1[8] = ((Role *)1)->CreateLongKui(*(int *)g_SceneMgr.m_slot1);
  *(_DWORD *)&g_SceneMgr.m_slot1[12] = ((Role *)1)->CreateZiXuan(*(int *)g_SceneMgr.m_slot1);
  *(_DWORD *)&g_SceneMgr.m_slot1[16] = ((Role *)1)->CreateChangQing(*(int *)g_SceneMgr.m_slot1);
  HuaYing = ((Role *)1)->CreateHuaYing(*(int *)g_SceneMgr.m_slot1);
  *(_DWORD *)&g_SceneMgr.m_slot1[368] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot1[32] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot1[376] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot1[40] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot1[20] = HuaYing;
  *(_DWORD *)&g_SceneMgr.m_slot1[380] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot1[44] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot1[360] = 5;
  *(_DWORD *)&g_SceneMgr.m_slot1[24] = 5;
  *(_DWORD *)&g_SceneMgr.m_slot1[364] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot1[28] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot1[372] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot1[36] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot1[384] = 5;
  *(_DWORD *)&g_SceneMgr.m_slot1[48] = 5;
  ((RoleSystem *)&g_SceneMgr.m_slot0[776])->LoadData(1);
  for ( m = 972; m < 1020; m += 4 )
  {
    v33 = *(_DWORD *)&g_SceneMgr.m_slot0[m + 776];
    v34 = *(_DWORD *)&g_SceneMgr.m_slot0[m + 728];
    if ( v33 < v34 )
    {
      if ( v33 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_slot0[m + 776] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_slot0[m + 776] = v34;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_slot2[220] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[224] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[228] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[232] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[236] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[240] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[244] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[248] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[252] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[256] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[260] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[264] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[268] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[272] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[276] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot2[280] = 82101;
  *(_DWORD *)&g_SceneMgr.m_slot2[284] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot2[288] = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82101);
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
    v40 = (_DWORD *)operator new(12 * v39);
    v148 = (char *)((Array *)g_nSceneMode)->Insert(v35, v40);
    v148->Erase(1, &pConfig);
    v35->Insert(elem, v148 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v40[3 * v38];
    v41 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v40;
    elem = &v40[3 * v41 + 3];
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
    v49 = (_DWORD *)operator new(12 * v48);
    v149 = (char *)((Array *)g_nSceneMode)->Insert(v44, v49);
    v149->Erase(1, &pConfig);
    v44->Insert(elem, v149 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v49[3 * v47];
    v50 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v49;
    elem = &v49[3 * v50 + 3];
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
    v58 = (_DWORD *)operator new(12 * v57);
    v150 = (char *)((Array *)g_nSceneMode)->Insert(v53, v58);
    v150->Erase(1, &pConfig);
    v53->Insert(elem, v150 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v58[3 * v56];
    v59 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v58;
    elem = &v58[3 * v59 + 3];
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
    v67 = (_DWORD *)operator new(12 * v66);
    v151 = (char *)((Array *)g_nSceneMode)->Insert(v62, v67);
    v151->Erase(1, &pConfig);
    v62->Insert(elem, v151 + 12);
    nullsub_2(g_nSceneMode, elem);
    operator delete((void *)g_nSceneMode);
    dword_C0437C = (int)&v67[3 * v65];
    v68 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneMode = (int)v67;
    elem = &v67[3 * v68 + 3];
  }
  *(_DWORD *)g_SceneMgr.m_slot2 = 14;
  *(_DWORD *)&g_SceneMgr.m_slot2[108] = 5594;
  *(_DWORD *)&g_SceneMgr.m_slot2[4] = ((Role *)2)->CreateXueJian(14);
  *(_DWORD *)&g_SceneMgr.m_slot2[8] = ((Role *)2)->CreateLongKui(*(int *)g_SceneMgr.m_slot2);
  *(_DWORD *)&g_SceneMgr.m_slot2[12] = ((Role *)2)->CreateZiXuan(*(int *)g_SceneMgr.m_slot2);
  *(_DWORD *)&g_SceneMgr.m_slot2[16] = ((Role *)2)->CreateChangQing(*(int *)g_SceneMgr.m_slot2);
  v71 = ((Role *)2)->CreateHuaYing(*(int *)g_SceneMgr.m_slot2);
  *(_DWORD *)&g_SceneMgr.m_slot2[376] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot2[40] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot2[20] = v71;
  *(_DWORD *)&g_SceneMgr.m_slot2[380] = 6;
  *(_DWORD *)&g_SceneMgr.m_slot2[44] = 6;
  *(_DWORD *)&g_SceneMgr.m_slot2[360] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot2[24] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot2[364] = 5;
  *(_DWORD *)&g_SceneMgr.m_slot2[28] = 5;
  *(_DWORD *)&g_SceneMgr.m_slot2[368] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot2[32] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot2[372] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot2[36] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot2[384] = 5;
  *(_DWORD *)&g_SceneMgr.m_slot2[48] = 5;
  ((RoleSystem *)&g_SceneMgr.m_slot1[776])->LoadData(1);
  for ( n = 972; n < 1020; n += 4 )
  {
    v73 = *(_DWORD *)&g_SceneMgr.m_slot1[n + 776];
    v74 = *(_DWORD *)&g_SceneMgr.m_slot1[n + 728];
    if ( v73 < v74 )
    {
      if ( v73 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_slot1[n + 776] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_slot1[n + 776] = v74;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_slot3[220] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[224] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[228] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[232] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[236] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[240] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[244] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[248] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[252] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[256] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[260] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[264] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[268] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[272] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[276] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot3[280] = 82301;
  *(_DWORD *)&g_SceneMgr.m_slot3[284] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot3[288] = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82301);
  pConfig = 4401;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(4401);
  v75 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((Array *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((Array *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v75) / 12, &pConfig);
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
    v80 = (_DWORD *)operator new(12 * v79);
    v152 = (char *)((Array *)g_nSceneState)->Insert(v75, v80);
    v152->Erase(1, &pConfig);
    v75->Insert((void *)g_nSceneType, v152 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)&v80[3 * v78];
    v81 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v80;
    g_nSceneType = (int)&v80[3 * v81 + 3];
  }
  pConfig = 316;
  v162 = 2949123;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(316);
  v84 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((Array *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((Array *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v84) / 12, &pConfig);
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
    v89 = (_DWORD *)operator new(12 * v88);
    v153 = (char *)((Array *)g_nSceneState)->Insert(v84, v89);
    v153->Erase(1, &pConfig);
    v84->Insert((void *)g_nSceneType, v153 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)&v89[3 * v87];
    v90 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v89;
    g_nSceneType = (int)&v89[3 * v90 + 3];
  }
  pConfig = 317;
  v162 = 983043;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(317);
  v93 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((Array *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((Array *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v93) / 12, &pConfig);
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
    v98 = (_DWORD *)operator new(12 * v97);
    v154 = (char *)((Array *)g_nSceneState)->Insert(v93, v98);
    v154->Erase(1, &pConfig);
    v93->Insert((void *)g_nSceneType, v154 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)&v98[3 * v96];
    v99 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v98;
    g_nSceneType = (int)&v98[3 * v99 + 3];
  }
  pConfig = 318;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(318);
  v102 = (int *)g_nSceneType;
  if ( (dword_C0438C - g_nSceneType) / 12 )
  {
    ((Array *)g_nSceneType)->Insert((void *)g_nSceneType, (void *)(g_nSceneType + 12));
    ((Array *)g_nSceneType)->Erase(1 - (g_nSceneType - (int)v102) / 12, &pConfig);
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
    v107 = (_DWORD *)operator new(12 * v106);
    v155 = (char *)((Array *)g_nSceneState)->Insert(v102, v107);
    v155->Erase(1, &pConfig);
    v102->Insert((void *)g_nSceneType, v155 + 12);
    nullsub_2(g_nSceneState, g_nSceneType);
    operator delete((void *)g_nSceneState);
    dword_C0438C = (int)&v107[3 * v105];
    v108 = ((Array *)&dword_C04380)->Size();
    g_nSceneState = (int)v107;
    g_nSceneType = (int)&v107[3 * v108 + 3];
  }
  *(_DWORD *)g_SceneMgr.m_slot3 = 10;
  *(_DWORD *)&g_SceneMgr.m_slot3[108] = 1943;
  *(_DWORD *)&g_SceneMgr.m_slot3[4] = ((Role *)3)->CreateXueJian(10);
  *(_DWORD *)&g_SceneMgr.m_slot3[8] = ((Role *)3)->CreateLongKui(*(int *)g_SceneMgr.m_slot3);
  *(_DWORD *)&g_SceneMgr.m_slot3[12] = ((Role *)3)->CreateZiXuan(*(int *)g_SceneMgr.m_slot3);
  *(_DWORD *)&g_SceneMgr.m_slot3[16] = ((Role *)3)->CreateChangQing(*(int *)g_SceneMgr.m_slot3);
  *(_DWORD *)&g_SceneMgr.m_slot3[20] = ((Role *)3)->CreateHuaYing(*(int *)g_SceneMgr.m_slot3);
  v111 = 1;
  *(_DWORD *)&g_SceneMgr.m_slot3[368] = 6;
  *(_DWORD *)&g_SceneMgr.m_slot3[32] = 6;
  *(_DWORD *)&g_SceneMgr.m_slot3[360] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot3[24] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot3[364] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot3[28] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot3[372] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot3[36] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot3[376] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot3[40] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot3[380] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot3[44] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot3[384] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot3[48] = 2;
  ((RoleSystem *)&g_SceneMgr.m_slot2[776])->LoadData(1);
  for ( nn = 972; nn < 1020; nn += 4 )
  {
    v113 = *(_DWORD *)&g_SceneMgr.m_slot2[nn + 776];
    v114 = *(_DWORD *)&g_SceneMgr.m_slot2[nn + 728];
    if ( v113 < v114 )
    {
      if ( v113 <= 0 )
        *(_DWORD *)&g_SceneMgr.m_slot2[nn + 776] = 0;
    }
    else
    {
      *(_DWORD *)&g_SceneMgr.m_slot2[nn + 776] = v114;
    }
  }
  *(_DWORD *)&g_SceneMgr.m_slot4[220] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[224] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[228] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[232] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[236] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[240] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[244] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[248] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[252] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[256] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[260] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[264] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[268] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[272] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[276] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[280] = 82001;
  *(_DWORD *)&g_SceneMgr.m_slot4[284] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot4[288] = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(82001);
  pConfig = 4501;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(4501);
  m_pAddEffect2 = (int *)g_SceneMgr.m_pAddEffect2;
  if ( (g_SceneMgr.m_pAlphaEffect2 - g_SceneMgr.m_pAddEffect2) / 12 )
  {
    ((Array *)g_SceneMgr.m_pAddEffect2)->Insert((void *)g_SceneMgr.m_pAddEffect2, (void *)(g_SceneMgr.m_pAddEffect2 + 12));
    ((Array *)g_SceneMgr.m_pAddEffect2)->Erase(1 - (g_SceneMgr.m_pAddEffect2 - (int)m_pAddEffect2) / 12, &pConfig);
    for ( i1 = g_SceneMgr.m_pAddEffect2; m_pAddEffect2 != (int *)i1; v122[2] = v163 )
    {
      v122 = m_pAddEffect2;
      m_pAddEffect2 += 3;
      *v122 = pConfig;
      v122[1] = v162;
    }
    g_SceneMgr.m_pAddEffect2 += 12;
  }
  else
  {
    if ( !g_SceneMgr.m_pSceneRoot )
      goto LABEL_148;
    if ( (unsigned int)((g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12) > 1 )
      v111 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    if ( g_SceneMgr.m_pSceneRoot )
      v116 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    else
LABEL_148:
      v116 = 0;
    v117 = v116 + v111;
    v118 = v116 + v111;
    if ( v116 + v111 < 0 )
      v118 = 0;
    v119 = (_DWORD *)operator new(12 * v118);
    v156 = (char *)((Array *)g_SceneMgr.m_pSceneRoot)->Insert(m_pAddEffect2, v119);
    v156->Erase(1, &pConfig);
    m_pAddEffect2->Insert((void *)g_SceneMgr.m_pAddEffect2, v156 + 12);
    nullsub_2(g_SceneMgr.m_pSceneRoot, g_SceneMgr.m_pAddEffect2);
    operator delete((void *)g_SceneMgr.m_pSceneRoot);
    g_SceneMgr.m_pAlphaEffect2 = (__int32)&v119[3 * v117];
    if ( g_SceneMgr.m_pSceneRoot )
      v120 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    else
      v120 = 0;
    g_SceneMgr.m_pSceneRoot = (__int32)v119;
    g_SceneMgr.m_pAddEffect2 = (__int32)&v119[3 * v120 + 3];
  }
  pConfig = 306;
  v162 = 2949123;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(306);
  v123 = (int *)g_SceneMgr.m_pAddEffect2;
  if ( (g_SceneMgr.m_pAlphaEffect2 - g_SceneMgr.m_pAddEffect2) / 12 )
  {
    ((Array *)g_SceneMgr.m_pAddEffect2)->Insert((void *)g_SceneMgr.m_pAddEffect2, (void *)(g_SceneMgr.m_pAddEffect2 + 12));
    ((Array *)g_SceneMgr.m_pAddEffect2)->Erase(1 - (g_SceneMgr.m_pAddEffect2 - (int)v123) / 12, &pConfig);
    for ( i2 = g_SceneMgr.m_pAddEffect2; v123 != (int *)i2; v132[2] = v163 )
    {
      v132 = v123;
      v123 += 3;
      *v132 = pConfig;
      v132[1] = v162;
    }
    g_SceneMgr.m_pAddEffect2 += 12;
  }
  else
  {
    if ( g_SceneMgr.m_pSceneRoot && (unsigned int)((g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12) > 1 )
      v124 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    else
      v124 = 1;
    if ( g_SceneMgr.m_pSceneRoot )
      v125 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    else
      v125 = 0;
    v126 = v125 + v124;
    v157 = v125 + v124;
    if ( v125 + v124 < 0 )
      v126 = 0;
    v127 = (_DWORD *)operator new(12 * v126);
    m_pSceneRoot = (char *)g_SceneMgr.m_pSceneRoot;
    v159 = (__int32)v127;
    for ( i3 = v127; m_pSceneRoot != (char *)v123; i3 += 3 )
    {
      i3->Copy(m_pSceneRoot);
      m_pSceneRoot += 12;
    }
    i3->Erase(1, &pConfig);
    v123->Insert((void *)g_SceneMgr.m_pAddEffect2, i3 + 3);
    nullsub_2(g_SceneMgr.m_pSceneRoot, g_SceneMgr.m_pAddEffect2);
    operator delete((void *)g_SceneMgr.m_pSceneRoot);
    g_SceneMgr.m_pAlphaEffect2 = v159 + 12 * v157;
    v130 = ((Array *)&g_SceneMgr.m_pGfxMgr)->Size();
    g_SceneMgr.m_pSceneRoot = v159;
    g_SceneMgr.m_pAddEffect2 = v159 + 12 * (v130 + 1);
  }
  pConfig = 307;
  v162 = 983043;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(307);
  v133 = (int *)g_SceneMgr.m_pAddEffect2;
  if ( (g_SceneMgr.m_pAlphaEffect2 - g_SceneMgr.m_pAddEffect2) / 12 )
  {
    ((Array *)g_SceneMgr.m_pAddEffect2)->Insert((void *)g_SceneMgr.m_pAddEffect2, (void *)(g_SceneMgr.m_pAddEffect2 + 12));
    ((Array *)g_SceneMgr.m_pAddEffect2)->Erase(1 - (g_SceneMgr.m_pAddEffect2 - (int)v133) / 12, &pConfig);
    for ( i4 = g_SceneMgr.m_pAddEffect2; v133 != (int *)i4; v142[2] = v163 )
    {
      v142 = v133;
      v133 += 3;
      *v142 = pConfig;
      v142[1] = v162;
    }
    g_SceneMgr.m_pAddEffect2 += 12;
  }
  else
  {
    if ( g_SceneMgr.m_pSceneRoot && (unsigned int)((g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12) > 1 )
      v134 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    else
      v134 = 1;
    if ( g_SceneMgr.m_pSceneRoot )
      v135 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    else
      v135 = 0;
    v136 = v135 + v134;
    v160 = v135 + v134;
    if ( v135 + v134 < 0 )
      v136 = 0;
    v137 = (_DWORD *)operator new(12 * v136);
    v138 = (char *)g_SceneMgr.m_pSceneRoot;
    v158 = (__int32)v137;
    for ( i5 = v137; v138 != (char *)v133; i5 += 3 )
    {
      i5->Copy(v138);
      v138 += 12;
    }
    i5->Erase(1, &pConfig);
    v133->Insert((void *)g_SceneMgr.m_pAddEffect2, i5 + 3);
    nullsub_2(g_SceneMgr.m_pSceneRoot, g_SceneMgr.m_pAddEffect2);
    operator delete((void *)g_SceneMgr.m_pSceneRoot);
    g_SceneMgr.m_pAlphaEffect2 = v158 + 12 * v160;
    v140 = ((Array *)&g_SceneMgr.m_pGfxMgr)->Size();
    g_SceneMgr.m_pSceneRoot = v158;
    g_SceneMgr.m_pAddEffect2 = v158 + 12 * (v140 + 1);
  }
  pConfig = 308;
  v162 = 0;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(308);
  ((Scene *)&g_SceneMgr)->LoadConfig(&pConfig);
  *(_DWORD *)&g_SceneMgr.m_slot4[108] = 4341;
  *(_DWORD *)g_SceneMgr.m_slot4 = 13;
  *(_DWORD *)&g_SceneMgr.m_slot4[4] = ((Role *)4)->CreateXueJian(13);
  *(_DWORD *)&g_SceneMgr.m_slot4[8] = ((Role *)4)->CreateLongKui(*(int *)g_SceneMgr.m_slot4);
  *(_DWORD *)&g_SceneMgr.m_slot4[12] = ((Role *)4)->CreateZiXuan(*(int *)g_SceneMgr.m_slot4);
  *(_DWORD *)&g_SceneMgr.m_slot4[16] = ((Role *)4)->CreateChangQing(*(int *)g_SceneMgr.m_slot4);
  *(_DWORD *)&g_SceneMgr.m_slot4[20] = ((Role *)4)->CreateHuaYing(*(int *)g_SceneMgr.m_slot4);
  *(_DWORD *)&g_SceneMgr.m_slot4[372] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot4[36] = 4;
  *(_DWORD *)&g_SceneMgr.m_slot4[368] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot4[32] = 1;
  *(_DWORD *)&g_SceneMgr.m_slot4[360] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot4[24] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot4[364] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot4[28] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot4[376] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot4[40] = 3;
  *(_DWORD *)&g_SceneMgr.m_slot4[380] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot4[44] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot4[384] = 2;
  *(_DWORD *)&g_SceneMgr.m_slot4[48] = 2;
  ((RoleSystem *)&g_SceneMgr.m_slot3[776])->LoadData(1);
  ((RoleSystem *)&g_SceneMgr.m_slot3[776])->Init();
  *(_DWORD *)&g_SceneMgr._gap_c5e0[560] = 4101;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[564] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[568] = 4102;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[572] = 4;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[576] = 4103;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[580] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[584] = 4104;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[588] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[592] = 4105;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[596] = 44;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[600] = 4106;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[604] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[608] = 4201;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[612] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[616] = 4202;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[620] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[652] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[660] = 3;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[676] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[692] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[700] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[716] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[748] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[796] = -1;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[724] = 13;
  memset(&g_SceneMgr._gap_c5e0[160], 0, 0x190u);
  *(_DWORD *)&g_SceneMgr._gap_c5e0[624] = 4203;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[628] = 20;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[632] = 4204;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[636] = 55;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[640] = 4205;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[644] = 50;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[648] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[656] = 4301;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[664] = 4302;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[668] = 10;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[672] = 4303;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[680] = 4304;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[684] = 20;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[688] = 4305;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[696] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[704] = 4401;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[708] = 4;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[712] = 4402;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[720] = 4403;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[728] = 4404;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[732] = 35;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[736] = 4405;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[740] = 58;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[744] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[752] = 4501;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[756] = 8;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[760] = 4502;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[764] = 24;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[768] = 4503;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[772] = 38;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[776] = 4504;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[780] = 50;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[784] = 4505;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[788] = 64;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[792] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[160] = 301;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[172] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[168] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[176] = 302;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[188] = 4;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[184] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[192] = 303;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[204] = 5;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[200] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[208] = 304;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[220] = 20;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[216] = 50;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[224] = 305;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[236] = 30;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[232] = 60;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[240] = 321;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[252] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[248] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[256] = 322;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[268] = 5;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[264] = 30;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[272] = 323;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[284] = 14;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[280] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[288] = 324;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[300] = 23;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[296] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[304] = 325;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[440] = 30;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[316] = 32;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[312] = 50;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[320] = 311;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[332] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[328] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[336] = 312;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[348] = 5;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[344] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[352] = 313;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[364] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[360] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[368] = 314;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[380] = 25;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[376] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[384] = 315;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[396] = 35;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[392] = 60;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[400] = 316;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[412] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[408] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[416] = 317;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[428] = 3;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[424] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[432] = 318;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[444] = 10;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[448] = 319;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[460] = 20;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[456] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[464] = 320;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[476] = 28;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[472] = 20;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[480] = 306;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[492] = 0;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[488] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[496] = 307;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[508] = 6;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[504] = 15;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[512] = 308;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[524] = 14;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[520] = 45;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[528] = 309;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[540] = 22;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[536] = 50;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[544] = 310;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[556] = 32;
  *(_DWORD *)&g_SceneMgr._gap_c5e0[552] = 60;
  NPC::InitAll();
  for ( i6 = 0; i6 < 5; ++i6 )
  {
    result = 1408 * i6;
    g_SceneMgr.m_slot0[result + 769] = 0;
    g_SceneMgr.m_slot0[result + 770] = 0;
    g_SceneMgr.m_slot0[result + 771] = 0;
    g_SceneMgr.m_slot0[result + 772] = 0;
    g_SceneMgr.m_slot0[result + 773] = 1;
    g_SceneMgr.m_slot0[result + 768] = 0;
    switch ( i6 )
    {
      case 0:
        *(&g_SceneMgr.m_pAddEffect + 352 * i6) = 101;
        break;
      case 1:
        *(&g_SceneMgr.m_pAddEffect + 352 * i6) = 104;
        break;
      case 2:
        *(&g_SceneMgr.m_pAddEffect + 352 * i6) = 106;
        break;
      case 3:
        *(&g_SceneMgr.m_pAddEffect + 352 * i6) = 107;
        break;
      case 4:
        *(&g_SceneMgr.m_pAddEffect + 352 * i6) = 102;
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

  if ( dword_C116F4 )
  {
    dword_C116F4->Stop();
    dword_C116F4 = 0;
  }
  return result;
}
