#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PAL3.h"
#include "pal3/gen/Array.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/CRenderTarget2.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/Camera.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/CameraSystem.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/MvcViewport.h"
#include "pal3/gen/NPC.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/Role.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/Scene.h"
#include "pal3/gen/ScreenEffectMgr.h"
#include "pal3/gen/SoundContext.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/UIQuadManager.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int CombatEffectUpdate(...);
int EffectUpdate(...);
int InputUpdate(...);
int NPCAnimUpdate(...);
int SceneMgrUpdate(...);
int SceneUpdate(...);
int ScriptUpdate(...);
int UINotifyUpdate(...);
int UIPostUpdate(...);
int UISceneUpdate(...);
int UIUpdate(...);
int sub_41BE80(...);
int sub_41D100(...);
int sub_569020(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aCreateActorman[];
extern char aCreateGfxManag[];
extern char aDProjectPal3Ga_0[];
extern char aUiFlexNote_0[];
extern char aUiSceneTiao[];
extern unsigned char byte_5833D0;
extern unsigned char byte_BFFE5E;
extern unsigned char byte_C020F0;
extern unsigned char byte_C021A4;
extern unsigned char byte_C021A5;
extern unsigned char byte_C021A6;
extern unsigned char byte_D8C339;
extern unsigned char byte_D924E8;
extern unsigned char byte_DE5220;
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
extern int nullsub_2;
extern void *off_56A694;
extern void *off_586180;
extern int unk_C1171C;
extern int unk_C11748;
extern int unk_C11750;
extern int unk_C11751;
extern int unk_C11754;

// 0x00404FF0
void PAL3::InitGFX()
{
  gbActorMgr *v0; // eax
  gbActorMgr *v1; // eax
  char *v2; // eax
  char *v3; // eax
  char *v4; // esi
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
  sub_41D100((_DWORD *)g_Input.KeyInfo[177].CountMode, 0);
  ((CameraCtrl *)g_Input.KeyInfo[177].CountMode)->SetAsCurrent(3);
  *(_DWORD *)&v5[12] = 3;
  *(_DWORD *)v5 = -16777216;
  *(_DWORD *)&v5[4] = 1065353216;
  ((gbGfxManager *)g_Input.KeyInfo[177].Data)->SetClearParam((struct gbClearParam *)v5);
  v4 = (char *)((operator *)0xD8u)->new();
  v7 = 2;
  if ( v4 )
  {
    *((_DWORD *)v4 + 1) = 1;
    *(_DWORD *)v4 = gbRefObject::`vftable';
    *(_DWORD *)v4 = gbVolumeModifier::`vftable';
    *((_DWORD *)v4 + 24) = 0;
    *((_DWORD *)v4 + 25) = 0;
    *((_DWORD *)v4 + 26) = 0;
    LOBYTE(v7) = 3;
    *((_DWORD *)v4 + 40) = 0;
    *((_DWORD *)v4 + 41) = 0;
    *((_DWORD *)v4 + 42) = 0;
    ((gbVec3D *)(v4 + 172))->gbVec3D(0.0, 0.0, 0.0);
    *(_DWORD *)v4 = &off_56A694;
  }
  else
  {
    v4 = 0;
  }
  v7 = -1;
  v4->Init(2);
  *((_DWORD *)v4 + 7) = 1065353216;
  *((_DWORD *)v4 + 8) = 1065353216;
  *((_DWORD *)v4 + 9) = 1065353216;
  *((_DWORD *)v4 + 10) = 1065353216;
  *((_DWORD *)v4 + 12) = 1;
  *((_DWORD *)v4 + 11) = 1;
  *((_DWORD *)v4 + 3) = 1049582633;
  *((_DWORD *)v4 + 4) = 1049582633;
  *((_DWORD *)v4 + 5) = 1049582633;
  *((_DWORD *)v4 + 16) = 1092616192;
  *((_DWORD *)v4 + 15) = 1092616192;
  *((_DWORD *)v4 + 6) = 1065353216;
  ((gbVolModNode *)&g_GDB.m_ItemData[360].name[12])->SetVolModObj((struct gbVolumeModifier *)v4);
  ((gbRefObject *)v4)->Release();
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
  float *m_pCollisionNode; // ebp
  int v11; // ebx
  __int8 *v12; // esi
  double v13; // st7
  double v14; // st7
  int *v15; // eax
  double v16; // st7
  _DWORD *v17; // eax
  void *v18; // ecx
  int *v19; // eax
  PtrArray *v20; // eax
  float *Instance; // eax
  _DWORD *v22; // eax
  void *v23; // ecx
  char *v24; // eax
  char *v25; // eax
  CUtil *Mode; // eax
  char *v27; // eax
  gbAudioManager *AudioManager; // esi
  char *v29; // eax
  char *v30; // eax
  ScreenEffect *v31; // eax
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
      InputUpdate(g_Input.KeyInfo[177].CountMode, a1);
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
        ScriptUpdate(a1);
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
      Mode = (CUtil *)((CGameData *)&g_GameData)->GetMode();
      CGameData_Load((int)&g_GameData, Mode);
      CombatEnter();
      if ( (g_nGameFlags & 4) == 0 )
        goto LABEL_54;
      v27 = (char *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)v27)->GetAudioManager();
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
        v29 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v29)->AudioStopAll();
        goto LABEL_54;
      }
      v30 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v30)->AudioFadeOut();
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
      v9 = (_DWORD *)UISceneUpdate();
      UIUpdate(v9, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      if ( g_Input.KeyInfo[174].Data )
        goto LABEL_64;
      if ( !v7 )
        CameraUpdate_Internal(*(float *)&a1);
      m_pCollisionNode = (float *)g_SceneMgr.m_pCollisionNode;
      v11 = 1;
      v12 = (__int8 *)&g_SceneMgr._midRegion[12];
      while ( 1 )
      {
        if ( *((_DWORD *)v12 + 155) )
        {
          dt = m_pCollisionNode[1] - *((float *)v12 - 2);
          v13 = m_pCollisionNode[2] - *((float *)v12 - 1);
          v38.x = dt;
          dt_4 = v13;
          v14 = m_pCollisionNode[3] - *(float *)v12;
          v38.y = dt_4;
          v37 = v14;
          v38.z = v37;
          if ( 12.0 + 12.0 > ((gbVec3D *)&v38)->Length() )
            break;
        }
        v12 += 8704;
        ++v11;
        if ( (int)v12 >= (int)&g_SceneMgr.m_pScriptCtrl )
          goto LABEL_64;
      }
      v11->EndWolf();
      goto LABEL_64;
    case 8:
      if ( PAL3::EntryCatchGhost() )
      {
        PAL3::EndHideFight();
        RoleSystemNotify(g_SceneMgr.m_pCollisionNode);
        v15 = ((PalScriptMgr *)0x6A5u)->Destroy(0);
LABEL_33:
        v34 = (int)v15;
        v20 = (PtrArray *)SoundContext::GetInstance();
        CScreenMode_SetResolution(v20, 0, v34);
        a1->RunSceneScript();
        goto LABEL_64;
      }
      v16 = *(float *)&g_Input.KeyInfo[176].CountMode + *(float *)&a1;
      *(float *)&g_Input.KeyInfo[176].CountMode = v16;
      if ( v16 >= 180.0 )
        goto LABEL_32;
      a1->RunSceneScript();
      InputUpdate(g_Input.KeyInfo[177].CountMode, a1);
      ScriptUpdate(a1);
      v17 = (_DWORD *)UISceneUpdate();
      UIUpdate(v17, *(float *)&a1);
      EffectUpdate(*(float *)&a1);
      if ( !v7 )
        CameraUpdate_Internal(*(float *)&a1);
      UIPostUpdate(v18);
      if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) != 4 )
      {
        v19 = (int *)UISceneUpdate();
        if ( UINotifyUpdate(v19) )
        {
LABEL_32:
          RoleSystemNotify(g_SceneMgr.m_pCollisionNode);
          PAL3::EndHideFight();
          v15 = ((PalScriptMgr *)0x6A6u)->Destroy(0);
          goto LABEL_33;
        }
      }
LABEL_64:
      v31 = (ScreenEffect *)ScreenEffectMgr::GetInstance();
      RenderPost((int)v31, a1);
      result = g_Input.KeyInfo[177].PressTime;
      if ( !g_Input.KeyInfo[177].PressTime )
        return ((CScreenMode *)g_Logger)->SetState(1);
      return result;
    default:
      goto LABEL_64;
  }
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
  void *v14; // edi
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
  __int32 v111; // ebp
  int nn; // eax
  int v113; // ecx
  int v114; // edx
  int *m_pAddEffect2; // esi
  __int32 v116; // edx
  __int32 v117; // edi
  __int32 v118; // eax
  void *v119; // ebp
  __int32 v120; // edx
  __int32 i1; // eax
  int *v122; // edx
  int *v123; // esi
  __int32 v124; // ebp
  __int32 v125; // edx
  __int32 v126; // eax
  char *v127; // eax
  char *m_pSceneRoot; // ebp
  char *i3; // edi
  int v130; // eax
  __int32 i2; // eax
  int *v132; // ecx
  int *v133; // esi
  __int32 v134; // ebp
  __int32 v135; // edx
  __int32 v136; // eax
  char *v137; // eax
  char *v138; // ebp
  char *i5; // edi
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
  ((int)&g_SceneMgr.m_slot4[840])->Init();
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
    v14 = ((operator *)12 * v13)->new();
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
    v80 = ((operator *)12 * v79)->new();
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
    v89 = ((operator *)12 * v88)->new();
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
    v98 = ((operator *)12 * v97)->new();
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
    v107 = ((operator *)12 * v106)->new();
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
    ((void *)g_SceneMgr.m_pAddEffect2)->Insert((void *)g_SceneMgr.m_pAddEffect2, (void *)(g_SceneMgr.m_pAddEffect2 + 12));
    ((void *)g_SceneMgr.m_pAddEffect2)->Erase(1 - (g_SceneMgr.m_pAddEffect2 - (int)m_pAddEffect2) / 12, &pConfig);
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
    v119 = ((operator *)12 * v118)->new();
    v156 = (char *)((void *)g_SceneMgr.m_pSceneRoot)->Insert(m_pAddEffect2, v119);
    v156->Erase(1, &pConfig);
    m_pAddEffect2->Insert((void *)g_SceneMgr.m_pAddEffect2, v156 + 12);
    nullsub_2(g_SceneMgr.m_pSceneRoot, g_SceneMgr.m_pAddEffect2);
    operator delete((void *)g_SceneMgr.m_pSceneRoot);
    g_SceneMgr.m_pAlphaEffect2 = (__int32)v119 + 12 * v117;
    if ( g_SceneMgr.m_pSceneRoot )
      v120 = (g_SceneMgr.m_pAddEffect2 - g_SceneMgr.m_pSceneRoot) / 12;
    else
      v120 = 0;
    g_SceneMgr.m_pSceneRoot = (__int32)v119;
    g_SceneMgr.m_pAddEffect2 = (__int32)v119 + 12 * v120 + 12;
  }
  pConfig = 306;
  v162 = 2949123;
  v163 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(306);
  v123 = (int *)g_SceneMgr.m_pAddEffect2;
  if ( (g_SceneMgr.m_pAlphaEffect2 - g_SceneMgr.m_pAddEffect2) / 12 )
  {
    ((void *)g_SceneMgr.m_pAddEffect2)->Insert((void *)g_SceneMgr.m_pAddEffect2, (void *)(g_SceneMgr.m_pAddEffect2 + 12));
    ((void *)g_SceneMgr.m_pAddEffect2)->Erase(1 - (g_SceneMgr.m_pAddEffect2 - (int)v123) / 12, &pConfig);
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
    v127 = (char *)((operator *)12 * v126)->new();
    m_pSceneRoot = (char *)g_SceneMgr.m_pSceneRoot;
    v159 = (__int32)v127;
    for ( i3 = v127; m_pSceneRoot != (char *)v123; i3 += 12 )
    {
      i3->Copy(m_pSceneRoot);
      m_pSceneRoot += 12;
    }
    i3->Erase(1, &pConfig);
    v123->Insert((void *)g_SceneMgr.m_pAddEffect2, i3 + 12);
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
    ((void *)g_SceneMgr.m_pAddEffect2)->Insert((void *)g_SceneMgr.m_pAddEffect2, (void *)(g_SceneMgr.m_pAddEffect2 + 12));
    ((void *)g_SceneMgr.m_pAddEffect2)->Erase(1 - (g_SceneMgr.m_pAddEffect2 - (int)v133) / 12, &pConfig);
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
    v137 = (char *)((operator *)12 * v136)->new();
    v138 = (char *)g_SceneMgr.m_pSceneRoot;
    v158 = (__int32)v137;
    for ( i5 = v137; v138 != (char *)v133; i5 += 12 )
    {
      i5->Copy(v138);
      v138 += 12;
    }
    i5->Erase(1, &pConfig);
    v133->Insert((void *)g_SceneMgr.m_pAddEffect2, i5 + 12);
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
