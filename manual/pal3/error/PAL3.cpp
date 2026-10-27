// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/PAL3.h"
#include "Role/Actor.h"
#include "Misc/Array.h"
#include "Misc/CCBPanelSlot.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffect.h"
#include "Effect/CEffectSystem.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/Camera.h"
#include "Scene/CameraCtrl.h"
#include "Scene/CameraSystem.h"
#include "GameBase/Config.h"
#include "GameBase/GRPinput.h"
#include "GameBase/Logger.h"
#include "MiniGame/MiniGame1.h"
#include "MiniGame/MiniGame3.h"
#include "Role/NPC.h"
#include "Misc/NPCInfo.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Render/RenderTarget2.h"
#include "Render/RenderTarget3.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Misc/SaleUI.h"
#include "Scene/Scene.h"
#include "Misc/SceneMapPlayer.h"
#include "Scene/SceneMgr.h"
#include "Scene/SceneObj.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "Misc/ScriptCounter.h"
#include "Misc/ScriptPoolPage.h"
#include "Script/ScriptSystem.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/SystemUI.h"
#include "Misc/TextureLibDataBase.h"
#include "UI/UIManager.h"
#include "UI/UINote.h"
#include "Misc/UIProgressBar.h"
#include "UI/UIQuadManager.h"
#include "UI/UIRenderObj.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "UI/UISystem.h"
#include "UI/UIWnd.h"
#include "Misc/_Console.h"
#include "Misc/_PlugInfo.h"
#include "Misc/_Texture_Info.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/tagC10Data.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4C5CD0(...);
int sub_4CE5C0(...);
int sub_53D1D0(...);

// Unnamed globals (extern)
extern char aSceneData[];
extern CHAR aSoftwareSoftst_2[];
void __cdecl nullsub_2(...);

// 0x00401BC0
void * PAL3::InitVFileSystem()
{
  void *result; // eax

  ((gbVFileSystem *)&g_BaseVFileSystem)->gbVFileSystem::gbVFileSystem();
  return result;
}

// 0x00401C00
void * PAL3::InitVFileSystem2()
{
  void *result; // eax

  ((gbVFileSystem *)&g_VFileSystem)->gbVFileSystem::gbVFileSystem();
  return result;
}

// 0x00404530
void PAL3::InitVolModNode()
{
}

// 0x00404760
PAL3::PAL3()
{
  unsigned int v1; // eax

  memset(&g_DrvInfo, 0, sizeof(g_DrvInfo));
  g_nPAL3_5833B8 = 1;
  (((PAL3 *)0))->PAL3::TestCombat();
  g_pCBSystem = 0;
  g_nCombatMode = 0;
  g_bTestCombat = 0;
  v1 = g_dwGameFlags;
  g_nRenderFlags = 0;
  LOBYTE(v1) = g_dwGameFlags & 0xF4 | 3;
  g_dwGameFlags = v1;
  g_nRenderMode = 0;
}

// 0x004047F0
// attributes: thunk
PAL3::~PAL3()
{
  this->PAL3::Destroy();
}

// 0x00404FF0
void PAL3::InitGFX()
{
  gbActorMgr *v1; // eax
  gbActorMgr *v2; // eax
  Camera *v3; // eax
  CameraCtrl *v4; // eax
  gbLightObj *v5; // esi
  struct gbClearParam v6; // [esp+0x20] [ebp-0x81C] BYREF
  char pExceptionObject[1024]; // [esp+0x30] [ebp-0x80C] BYREF
  char ArgList[1024]; // [esp+0x430] [ebp-0x40C] BYREF
  int v9; // [esp+0x838] [ebp-0x4]

  gfxMgr = gbCreateGraphManager(&g_DrvInfo);
  if ( !gfxMgr )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&path[208], &path[72], 401),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v1 = (gbActorMgr *)operator new(0xCu);
  v9 = 0;
  if ( v1 )
    v1->gbActorMgr::gbActorMgr(gfxMgr);
  else
    v2 = 0;
  v9 = -1;
  g_pActorMgr = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&path[180], &path[72], 405),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v3 = (Camera *)operator new(0x220u);
  v9 = 1;
  if ( v3 )
    v3->Camera::Camera(gfxMgr);
  else
    v4 = 0;
  v9 = -1;
  g_pCameraCtrl = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&path[164], &path[72], 409),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((CameraCtrl *)v4))->CameraCtrl::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  (((ScriptPoolPage *)g_pCameraCtrl))->ScriptPoolPage::ScriptPoolPage_Manage(0);
  (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetAsCurrent(3);
  v6.clearflag = 3;
  v6.color = -16777216;
  v6.depth = 1.0;
  (((gbGfxManager *)gfxMgr))->gbGfxManager::SetClearParam(&v6);
  v5 = (gbLightObj *)operator new(0xD8u);
  v9 = 2;
  if ( v5 )
  {
    *((_DWORD *)((gbVolumeModifier *)v5) + 1) = 1;
    v5->m_BoundSphere.center.x = 0.0f;
    v5->m_BoundSphere.center.y = 0.0f;
    v5->m_BoundSphere.center.z = 0.0f;
    LOBYTE(v9) = 3;
    v5->m_SysLight.position.x = 0.0f;
    v5->m_SysLight.position.y = 0.0f;
    v5->m_SysLight.position.z = 0.0f;
  }
  else
  {
    v5 = 0;
  }
  v9 = -1;
  (((gbLightObj *)v5))->gbLightObj::Init(LIGHT_SPOT);
  v5->m_Ambient.Red = 1.0f;
  v5->m_Ambient.Green = 1.0f;
  v5->m_Ambient.Blue = 1.0f;
  v5->m_Ambient.Alpha = 1.0f;
  v5->m_UseSpecular = 1;
  v5->m_UseDiffuse = 1;
  v5->m_Color.Red = 0.2800000011920929f;
  v5->m_Color.Green = 0.2800000011920929f;
  v5->m_Color.Blue = 0.2800000011920929f;
  v5->m_FarEnd = 10.0f;
  v5->m_FarStart = 10.0f;
  v5->m_Color.Alpha = 1.0f;
  (((gbVolModNode *)&g_pVolModNode))->gbVolModNode::SetVolModObj(v5);
  (((gbRefObject *)v5))->gbRefObject::Release();
}

// 0x00405330
bool PAL3::CreateEffectSystem()
{
  gbSnow *v1; // esi
  gbRain *v2; // eax
  int v3; // esi
  CEffectSystem *v4; // eax
  PAL3 *v5; // eax
  char RenderEffects; // al
  OpenBaseFile v8; // [esp+0x8] [ebp-0x85C] BYREF
  void *v9; // [esp+0xC] [ebp-0x858]
  struct gbDropDesc v10; // [esp+0x10] [ebp-0x854] BYREF
  struct gbDropDesc v11; // [esp+0x34] [ebp-0x830] BYREF
  char pExceptionObject[1024]; // [esp+0x58] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x458] [ebp-0x40C] BYREF
  int v14; // [esp+0x860] [ebp-0x4]

  v11.emitrate = 500;
  v11.minheight = -10.0;
  v11.maxheight = 50.0;
  v11.maxlife = 2.0;
  v11.minlife = 0.40000001;
  v11.maxvelocity = 40.0;
  v11.minvelocity = 20.0;
  v11.range = 100.0;
  v11.unitsize = 0.079999998;
  v10.emitrate = 200;
  v10.minheight = -10.0;
  v10.maxheight = 50.0;
  v10.maxlife = 3.0;
  v10.minlife = 1.0;
  v10.maxvelocity = 10.0;
  v10.minvelocity = 6.0;
  v10.range = 100.0;
  v10.unitsize = 0.5;
  v14 = 0;
  v1 = (gbSnow *)operator new(0x58u);
  v9 = (void *)v1;
  LOBYTE(v14) = 1;
  if ( v1 )
    v1->gbSnow::gbSnow(500, &v10, "effect\\snow.tga", 2.0);
  else
    v1 = 0;
  LOBYTE(v14) = 0;
  g_pDropGroup = v1;
  v2 = (gbRain *)operator new(0x50u);
  v3 = (int)v2;
  v9 = (void *)v2;
  LOBYTE(v14) = 2;
  if ( v2 )
    v2->gbRain::gbRain(500, &v11, 0);
  else
    v3 = 0;
  LOBYTE(v14) = 0;
  g_nPAL3_BFDA3C = v3;
  v4 = (CEffectSystem *)operator new(0x158u);
  v9 = (void *)v4;
  LOBYTE(v14) = 3;
  if ( v4 )
    v5 = (PAL3 *)(((CEffectSystem *)v4))->CEffectSystem::Create((int)gfxMgr);
  else
    v5 = 0;
  LOBYTE(v14) = 0;
  g_pEffectSystem = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&path[236], &path[72], 483),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  RenderEffects = (((PAL3 *)v5))->PAL3::CreateRenderEffects();
  v14 = -1;
  if ( RenderEffects )
  {
    ((OpenNULLFile *)&v8)->OpenNULLFile::OpenNULLFile();
    return 1;
  }
  else
  {
    ((OpenNULLFile *)&v8)->OpenNULLFile::OpenNULLFile();
    return 0;
  }
}

// 0x004055A0
bool PAL3::DestroyEffectSystem()
{
  void *v1; // esi

  v1 = g_pEffectSystem;
  if ( g_pEffectSystem )
  {
    (((CEffectSystem *)g_pEffectSystem))->CEffectSystem::DestroyEffects();
    operator delete(v1);
  }
  g_pEffectSystem = 0;
  return 1;
}

// 0x004055D0
void PAL3::Update(float dt)
{
    unsigned long reg_EBP = 0;
    unsigned long reg_ESI = 0;

  double v2; // rdi
  int v3; // edi
  unsigned __int16 *v4; // esi
  __int16 KeyState; // ax
  BOOL v6; // eax
  DWORD Time; // eax
  int v8; // esi
  PAL3 *v9; // ecx
  int v10; // ebx
  int v11; // eax
  Scene *v13; // eax
  int v15; // ebx

  char v19; // al
  PalScriptMgr *v20; // ecx
  Scene *v22; // eax
  CameraCtrl *v23; // ecx
  Scene *v24; // eax

  int v26; // eax
  CScreenMode *v27; // ecx
  PtrArray *SoundList; // eax

  RenderTarget2 *Instance_fd20; // eax
  CameraCtrl *v31; // ecx
  Scene *v32; // eax
  gbSound2DNode *v33; // ecx
  CScreenMode *Instance; // eax
  CScreenMode *v35; // eax
  CUtil *Mode; // eax
  CScreenMode *v37; // eax
  gbAudioManager *AudioManager; // esi
  CScreenMode *v39; // eax
  CScreenMode *v40; // eax
  PalScriptMgr *v41; // ecx
  gbCamera *v42; // eax
  double result; // [esp+0x0] [ebp-0x30]
  double resulta; // [esp+0x0] [ebp-0x30]
  double resultb; // [esp+0x0] [ebp-0x30]
  double resultc; // [esp+0x0] [ebp-0x30]
  int result_4; // [esp+0x4] [ebp-0x2C]
  int result_4a; // [esp+0x4] [ebp-0x2C]
  double v49; // [esp+0x8] [ebp-0x28]
  float pData; // [esp+0x18] [ebp-0x18]
  double pDataa; // [esp+0x18] [ebp-0x18]
  float pData_4; // [esp+0x1C] [ebp-0x14]
  float v53; // [esp+0x20] [ebp-0x10]
  gbVec3D v54; // [esp+0x24] [ebp-0xC] BYREF

  __asm
  {
    fld     g_fGameTimer
    fadd    [esp+dt]
  }
  __asm { fstp    g_fGameTimer }
  v49 = v2;
  v3 = 0;
  v4 = (unsigned __int16 *)(&g_PAL3_Instance.m_Image2D + 1);
  do
  {
    KeyState = (((GRPinput *)&g_Input))->GRPinput::GetKeyState(*v4);
    v6 = KeyState == 1 || KeyState == 3;
    result_4 = v6;
    Time = timeGetTime();
    (((GRPinput *)&g_Input))->GRPinput::SetMouseAbs(Time, v3, result_4);
    ++v4;
    ++v3;
  }
  while ( (int)v4 < (int)((unsigned __int16 *)&g_PAL3_Instance.m_Image2D + 141) );
  v8 = g_nSceneState;
  v10 = (((CGameData *)&g_gamefrm))->CGameData::SceneUpdate(SLODWORD(dt), 1);
  v11 = g_nSceneState;
  if ( g_nSceneState != v8 )
  {
    PAL3::IfHideFightSucceed();
    v11 = g_nSceneState;
  }
  switch ( v11 )
  {
    case 0:
    case 1:
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      goto LABEL_64;
    case 2:
    case 9:
      __asm
      {
        fld     g_fTimeScale; jumptable 00405676 cases 2,9
        fadd    [esp+0x28+dt]
      }
      __asm { fstp    g_fTimeScale }
      (*(void (**)(int))(*(_DWORD *)g_nRenderFlags + 20))(g_nRenderFlags);
      (*(void (**)(int))(*(_DWORD *)g_nRenderMode + 20))(g_nRenderMode);
      Instance_fd20 = (RenderTarget2 *)this->PAL3::GetInstance_fd20();
      (((RenderTarget2 *)Instance_fd20))->RenderTarget2::Update(dt);
      StopSceneScripts((const char *)LODWORD(dt));
      if ( byte_D8C339 )
      {
        byte_D8C339 = 0;
        StopSceneScripts((const char *)LODWORD(dt));
      }
      InputUpdate(dt);
      if ( g_nSceneState != 9 )
      {
        if ( v10 )
        {
          UIQuadManager::GetInstance();
          crt_sub_00541590();
        }
        else
        {
          (((CameraCtrl *)v31))->CameraCtrl::UpdateInternal(dt);
        }
        ScriptUpdate(SLODWORD(dt));
      }
      // __asm { fld     [esp+0x28+dt] }
      // __asm { fstp    [esp+0x30+result]; result }
      v32 = UISceneUpdate();
      (((SystemUI *)v32))->SystemUI::UIUpdate(resultb, v49);
      EffectUpdate(dt);
      SceneMgrUpdate(g_fTimeScale);
      (((gbSound2DNode *)v33))->gbSound2DNode::UIPostUpdate();
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioUpdate();
      if ( g_nSceneState != 2 && g_nSceneState != 9 )
        PAL3::IfHideFightSucceed();
      goto LABEL_64;
    case 3:
      // __asm { fld     [esp+0x28+dt]; jumptable 00405676 case 3 }
      // __asm { fstp    [esp+0x28+pData] }
      (((CCBSystem *)&g_pCBSystem))->CCBSystem::CombatUpdate(pDataa);
      CombatEffectUpdate(pDataa);
      v35 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v35))->CScreenMode::AudioUpdate();
      LOBYTE(v9) = g_pCBSystem->m_bQuitFlag;
      if ( !(_BYTE)v9 )
        goto LABEL_64;
      LOBYTE(v9) = g_bTestCombat;
      if ( g_bTestCombat )
      {
        (((PAL3 *)v9))->PAL3::GetCommandLineParam();
        (((CCBSystem *)&g_pCBSystem))->CCBSystem::CombatUpdate(0.0);
        CombatEffectUpdate(0.0);
        goto LABEL_59;
      }
      g_szGamePath[0] = *(_DWORD *)&g_pCBSystem->m_eResult == 2;
      Mode = (CUtil *)(((CGameData *)&g_gamefrm))->CGameData::GetMode();
      (((CGameData *)&g_gamefrm))->CGameData::Load(Mode);
      CombatEnter();
      if ( (g_dwGameFlags & 4) == 0 )
        goto LABEL_54;
      v37 = (CScreenMode *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)(((CScreenMode *)v37))->CScreenMode::GetAudioManager();
      if ( !AudioManager )
        goto LABEL_54;
      if ( byte_C11751 )
      {
        LOBYTE(v9) = (unsigned long)CScreenMode::GetInstance()->m_bRenderAlt;
        if ( (_BYTE)v9 )
          goto LABEL_54;
        goto LABEL_51;
      }
      (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(1);
      (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(0);
      if ( !CScreenMode::GetInstance()->m_bRenderAlt )
      {
LABEL_51:
        (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(2);
        (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(1);
        v39 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v39))->CScreenMode::AudioStopAll();
        goto LABEL_54;
      }
      v40 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v40))->CScreenMode::AudioFadeOut();
LABEL_54:
      if ( g_szGamePath[0] || !g_nKeyMap3 )
      {
        if ( unk_C11720.m_nTodo_34 )
          *(_DWORD *)(unk_C11720.m_nTodo_34 + 632) = 0;
      }
      else
      {
        (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)0xF);
        (((PalScriptMgr *)v41))->PalScriptMgr::IfHaveScript();
      }
LABEL_59:
      byte_C11748 = 0;
      byte_C11750 = 0;
      dword_C1171C = 0x7FFFFFFF;
      g_nKeyMap3 = 1;
      goto LABEL_64;
    case 4:
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      // __asm { fld     [esp+0x28+dt] }
      // __asm { fstp    [esp+0x30+result]; pData }
      MiniGame1Update(resultc);
      goto LABEL_64;
    case 5:
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      MiniGame2Update(dt);
      goto LABEL_63;
    case 6:
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      MiniGame3Update(dt);
LABEL_63:
      NPCAnimUpdate(dt);
      goto LABEL_64;
    case 7:
      __asm
      {
        fld     g_fFadeAngle; jumptable 00405676 case 7
        fadd    [esp+0x28+dt]
      }
      __asm { fstp    g_fFadeAngle }
      if ( LODWORD(g_fDeltaTime) )
      {
        if ( !(((PalScriptMgr *)v9))->PalScriptMgr::_CON_CloseScript() )
        {
          LOBYTE(g_bGameUpdating) = 1;
          (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)4);
        }
      }
      else
      {
        __asm
        {
          fld     g_fFadeAngle
          fcomp   _flt_60_0
          fnstsw  ax
        }
        if ( (_AX & 0x100) == 0 )
        {
          PAL3::EndWolf();
          goto LABEL_64;
        }
      }
      StopSceneScripts((const char *)LODWORD(dt));
      InputUpdate(dt);
      ScriptUpdate(SLODWORD(dt));
      // __asm { fld     [esp+0x2C+dt] }
      // __asm { fstp    [esp+0x30+result]; result }
      v13 = UISceneUpdate();
      (((SystemUI *)v13))->SystemUI::UIUpdate(result, v49);
      EffectUpdate(dt);
      if ( LODWORD(g_fDeltaTime) )
        goto LABEL_64;
      if ( !v10 )
        (((CameraCtrl *)v9))->CameraCtrl::UpdateInternal(dt);
      reg_EBP = g_pRoleSystem;
      v15 = 1;
      reg_ESI = (unsigned long)&flt_C0816C;
      while ( 1 )
      {
        if ( *((_DWORD *)reg_ESI + 155) )
        {
          __asm
          {
            fld     dword ptr [ebp+4]
            fsub    dword ptr [esi-8]
            fstp    dword ptr [esp+0x28+pData]
            fld     dword ptr [ebp+8]
            fsub    dword ptr [esi-4]
          }
          v54.x = pData;
          __asm
          {
            fstp    dword ptr [esp+0x28+pData+4]
            fld     dword ptr [ebp+0x0C]
            fsub    dword ptr [esi]
          }
          v54.y = pData_4;
          // __asm { fstp    [esp+0x28+var_10] }
          v54.z = v53;
          (((gbVec3D *)&v54))->gbVec3D::Length();
          __asm
          {
            fld     _flt_12_0
            fadd    st, st
            fcompp
            fnstsw  ax
          }
          if ( (_AX & 0x4100) == 0 )
            break;
        }
        reg_ESI += 2176;
        ++v15;
        if ( (int)reg_ESI >= (int)flt_C1096C )
          goto LABEL_64;
      }
      PAL3::EndWolf();
      goto LABEL_64;
    case 8:
      (((PAL3 *)v9))->PAL3::EntryCatchGhost();
      if ( v19 )
      {
        this->PAL3::EndHideFight();
        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
LABEL_33:
        (((PalScriptMgr *)v20))->PalScriptMgr::Destroy();
        result_4a = v26;
        SoundList = (((CScreenMode *)v27))->CScreenMode::GetSoundList();
        (((PtrArray *)SoundList))->PtrArray::SetResolution(0, result_4a);
        StopSceneScripts((const char *)LODWORD(dt));
        goto LABEL_64;
      }
      __asm
      {
        fld     g_fFadeAngle
        fadd    [esp+0x28+dt]
        fst     g_fFadeAngle
        fcomp   _flt_180_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0 )
        goto LABEL_32;
      StopSceneScripts((const char *)LODWORD(dt));
      InputUpdate(dt);
      ScriptUpdate(SLODWORD(dt));
      // __asm { fld     [esp+0x2C+dt] }
      // __asm { fstp    [esp+0x30+result]; result }
      v22 = UISceneUpdate();
      (((SystemUI *)v22))->SystemUI::UIUpdate(resulta, v49);
      EffectUpdate(dt);
      if ( !v10 )
        (((CameraCtrl *)v23))->CameraCtrl::UpdateInternal(dt);
      (((gbSound2DNode *)v23))->gbSound2DNode::UIPostUpdate();
      v9 = (PAL3 *)g_pRoleSystem;
      if ( g_pRoleSystem->m_nMoveMode != 4 )
      {
        v24 = UISceneUpdate();
        if ( (((SceneMgr *)v24))->SceneMgr::UINotifyUpdate() )
        {
LABEL_32:
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
          this->PAL3::EndHideFight();
          goto LABEL_33;
        }
      }
LABEL_64:
      v42 = (gbCamera *)(((ScreenEffectMgr *)v9))->ScreenEffectMgr::GetInstance();
      (((gbCamera *)v42))->gbCamera::RenderPost(SLODWORD(dt));
      if ( !g_nSceneState )
        (((CScreenMode *)&g_InputState))->CScreenMode::SetState(1);
      return;
    default:
      goto LABEL_64;
  }
}

// 0x00405C00
void PAL3::Render()
{

  RenderTarget3 *Instance; // eax

  RenderTarget2 *Instance_fd20; // eax
  gbSceneGraph *pSceneGraph; // edi
  gbCamera *p_m_fMinDist; // eax
  UIScene *v7; // ecx
  int v8; // ebx
  gbMatrixStack *v9; // esi
  gbMatrix4 *Top; // eax
  ScriptSystem *v11; // ecx
  gbCamera *v12; // eax
  gbCamera *v13; // eax
  Scene *v14; // eax
  gbCamera *v15; // eax
  UIScene *v16; // ecx
  Scene *v17; // eax
  gbCamera *v18; // eax
  UIScene *v19; // ecx
  Scene *v20; // eax

  RenderTarget3 *v22; // eax

  RenderTarget2 *v24; // eax
  RenderTarget3 *v25; // ecx
  RenderTarget3 *v26; // eax
  Scene *v27; // ecx
  int v28; // edi
  __int64 v29; // rax
  gbPrintFont *v30; // esi
  float v31; // st7
  ScreenEffectMgr *v32; // ecx
  ScreenEffect *v33; // eax
  UIQuadManager *v34; // eax

  float v36; // [esp+0x0] [ebp-0x94]
  float v37; // [esp+0x4] [ebp-0x90]
  int v38; // [esp+0xC] [ebp-0x88]
  float *v39; // [esp+0x10] [ebp-0x84]
  _DWORD v40[3]; // [esp+0x18] [ebp-0x7C] BYREF
  struct gbVec3D v41; // [esp+0x24] [ebp-0x70] BYREF
  struct gbVec3D v42; // [esp+0x30] [ebp-0x64] BYREF
  struct gbVec3D v43; // [esp+0x3C] [ebp-0x58] BYREF
  struct gbVec3D v44; // [esp+0x48] [ebp-0x4C] BYREF
  struct gbVec3D v45; // [esp+0x54] [ebp-0x40] BYREF
  gbQuaternion v46; // [esp+0x60] [ebp-0x34] BYREF
  gbQuaternion v47; // [esp+0x70] [ebp-0x24] BYREF
  struct gbQuaternion v48; // [esp+0x80] [ebp-0x14] BYREF
  int v49; // [esp+0x90] [ebp-0x4]

  (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 48))(gfxMgr);
  switch ( g_nSceneState )
  {
    case 0:
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 52))(gfxMgr);
      return;
    case 2:
    case 7:
    case 8:
    case 9:
      Instance = (RenderTarget3 *)this->PAL3::GetInstance();
      (((RenderTarget3 *)Instance))->RenderTarget3::End();
      Instance_fd20 = (RenderTarget2 *)this->PAL3::GetInstance_fd20();
      (((RenderTarget2 *)Instance_fd20))->RenderTarget2::Begin();
      pSceneGraph = gfxMgr->pSceneGraph;
      if ( g_pCameraCtrl )
        p_m_fMinDist = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
      else
        p_m_fMinDist = 0;
      (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(p_m_fMinDist);
      v8 = (((UIScene *)v7))->UIScene::CombatCheck();
      v9 = gfxMgr->pMatrixStack[1];
      (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetAsCurrent(3);
      v41.x = 1.0;
      v41.y = 0.0;
      v41.z = 0.0;
      (((gbMatrixStack *)v9))->gbMatrixStack::Rotate(g_fPalScript_C12B28,  v41);
      v42.x = 0.0;
      v42.y = 1.0;
      v42.z = 0.0;
      (((gbMatrixStack *)v9))->gbMatrixStack::Rotate(g_fPalScript_C12B2C,  v42);
      v43.x = 0.0;
      v43.y = 0.0;
      v43.z = 1.0;
      (((gbMatrixStack *)v9))->gbMatrixStack::Rotate(g_fPalScript_C12B30,  v43);
      if ( !v8 && UISceneUpdate()->m_pCapacity[22] != (char *)1 )
      {
        memset(&v46, 0, 12);
        memset(&v47, 0, 12);
        memset(&v48, 0, 12);
        v44.y = 0.0;
        v44.z = 0.0;
        v46.w = 1.0f;
        v47.w = 1.0f;
        v48.w = 1.0;
        v44.x = 1.0;
        (((gbQuaternion *)&v46))->gbQuaternion::SetAxisAngle(&v44, 45.0);
        v45.x = 0.0;
        v45.y = 1.0;
        v45.z = 0.0;
        (((gbQuaternion *)&v47))->gbQuaternion::SetAxisAngle(&v45, 90.0);
        (((gbQuaternion *)&v47))->gbQuaternion::MultiplyBy(&v46, &v48);
        (((gbQuaternion *)&v48))->gbQuaternion::GetMatrix((gbMatrix4 *)&dword_A3A750);
        (((gbVolModNode *)&g_pVolModNode))->gbVolModNode::Attach(0);
      }
      if ( g_nPAL3_D8E488 == 2 )
      {
        Top = (((gbMatrixStack *)v9))->gbMatrixStack::GetTop();
        (((gbMatrix4 *)Top))->gbMatrix4::TransformPlane(v39);
        (*(void ( **)(gbGfxManager *, int *))(*(_DWORD *)*(void**)(gfxMgr) + 112))(gfxMgr, &g_nPAL3_D8E488);
      }
      else
      {
        (*(void ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)*(void**)(gfxMgr) + 112))(gfxMgr, 0);
      }
      UISceneUpdate();
      SystemUI_RenderWithStack((int)v9);
      if ( g_nSceneState != 9 )
        (((ScriptSystem *)v11))->ScriptSystem::Render(v9);
      (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
      if ( g_pDropGroup && (_BYTE)byte_BFDA40 )
      {
        if ( g_pCameraCtrl )
          v12 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
        else
          v12 = 0;
        (((gbDropGroup *)g_pDropGroup))->gbDropGroup::Render(v12);
      }
      if ( g_nPAL3_BFDA3C && (_BYTE)byte_BFDA41 )
      {
        if ( g_pCameraCtrl )
          v13 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
        else
          v13 = 0;
        (((gbDropGroup *)g_nPAL3_BFDA3C))->gbDropGroup::Render(v13);
      }
      v14 = UISceneUpdate();
      (((UIScene *)v14))->UIScene::NotifyRender();
      if ( g_pCameraCtrl )
        v15 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
      else
        v15 = 0;
      (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(v15);
      LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
      if ( UISceneUpdate()->m_pCapacity[22] != (char *)1 )
        (((UIScene *)v16))->UIScene::CombatCheck();
      v17 = UISceneUpdate();
      (((SystemUI *)v17))->SystemUI::Render((int)v9);
      (((SceneMgr *)g_pSceneManager))->SceneMgr::RenderUpdate();
      (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
      if ( g_nSceneState == 8 )
      {
        UISceneUpdate();
        SceneMgr_RenderActiveRoles(v38);
      }
      (((UIManager *)&g_UIManager))->UIManager::Render();
      (((SceneMgr *)g_pSceneManager))->SceneMgr::RenderAll();
      if ( g_pCameraCtrl )
        v18 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
      else
        v18 = 0;
      (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(v18);
      LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
      (((UIScene *)v19))->UIScene::CombatCheck();
      RoleSystem::RenderMainRole(v9);
      v20 = UISceneUpdate();
      (((UIScene *)v20))->UIScene::OverlayRender((int)v9);
      (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
      v22 = (RenderTarget3 *)this->PAL3::GetInstance();
      (((RenderTarget3 *)v22))->RenderTarget3::Resolve();
      v24 = (RenderTarget2 *)this->PAL3::GetInstance_fd20();
      (((RenderTarget2 *)v24))->RenderTarget2::Resolve();
      v26 = (((RenderTarget3 *)v25))->RenderTarget3::GetInstance();
      (((RenderTarget3 *)v26))->RenderTarget3::Begin();
      if ( !g_bGameFlag2 )
        break;
      goto LABEL_42;
    case 3:
      (((CCBSystem *)&g_pCBSystem))->CCBSystem::RenderCheck();
      break;
    case 4:
      (((MiniGame1 *)g_pMiniGame1))->MiniGame1::Render();
      break;
    case 5:
      (((gbMatrixStack *)g_pMiniGame2))->gbMatrixStack::SceneRenderWithRotation();
      goto LABEL_42;
    case 6:
      (((MiniGame3 *)g_pMiniGame3))->MiniGame3::Render();
LABEL_42:
      (((Scene *)v27))->Scene::Render2();
      break;
    default:
      break;
  }
  if ( g_nSceneState == 8 )
  {
    v28 = (__int64)(180.0 - g_fFadeAngle);
    goto LABEL_46;
  }
  if ( g_nSceneState == 7 )
  {
    v28 = (int)(__int64)(60.0 - g_fFadeAngle) < 0 ? 0 : (__int64)(60.0 - g_fFadeAngle);
LABEL_46:
    sprintf((char *const)&v47.z, "%03d", v28);
    LOBYTE(v29) = 0;
    v30 = gfxMgr->pFontMgr->pAllFont[3];
    if ( v28 < 30 )
      v29 = (__int64)(sin(g_fFadeAngle * 4.0) * 255.0);
    v31 = 60.0f / (float)g_DrvInfo.height;
    v30->ScaleX = 60.0f / (float)g_DrvInfo.width;
    v30->ScaleY = v31;
    if ( (_BYTE)v29 )
    {
      if ( gbColorQuad::ColorQuadFmt )
      {
        BYTE2(v40[0]) = v29;
        LOWORD(v40[0]) = 29338;
      }
      else
      {
        *(_WORD *)((char *)v40 + 1) = -25998;
        LOBYTE(v40[0]) = v29;
      }
      HIBYTE(v40[0]) = -56;
      v30->curColor.Color = v40[0];
    }
    else
    {
      if ( gbColorQuad::ColorQuadFmt )
      {
        *(_WORD *)((char *)v40 + 1) = 214;
        LOBYTE(v40[0]) = -2;
      }
      else
      {
        *(_WORD *)((char *)v40 + 1) = -298;
        LOBYTE(v40[0]) = 0;
      }
      HIBYTE(v40[0]) = -56;
      v30->curColor.Color = v40[0];
    }
    v37 = 1.0f - 64.0f / (float)g_DrvInfo.height;
    v36 = 1380.0f / (float)g_DrvInfo.width - 1.0f;
    ((void ( *)(gbPrintFont *, float *, _DWORD, _DWORD, int, int))v30->pGfxMgr->DrvInfo.subtype)(
      v30,
      &v47.z,
      LODWORD(v36),
      LODWORD(v37),
      1176256512,
      1176256512);
    ((void ( *)(gbPrintFont *))v30->pGfxMgr->hGfxWnd)(v30);
  }
  if ( g_nSceneState && g_nSceneState != 3 && g_bGameFlag2 )
  {
    PushMatrixStacks(v40);
    v49 = 0;
    v33 = (((ScreenEffectMgr *)v32))->ScreenEffectMgr::GetInstance();
    (((ScreenEffectMgr *)v33))->ScreenEffectMgr::UpdateFrontEffect();
    (((CGameData *)&g_gamefrm))->CGameData::ProcessDialog();
    if ( LODWORD(g_fGameSpeed) )
      (*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(g_fGameSpeed) + 4))(LODWORD(g_fGameSpeed));
    if ( !g_bEditorMode )
      (((Logger *)&g_InputState))->Logger::Render();
    v49 = -1;
    PopMatrixStacks(v40);
  }
  v34 = (UIQuadManager *)UIQuadManager::GetInstance();
  ((UIRenderObj *)v34)->UIRenderObj::UIRenderObj();
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 52))(gfxMgr);
  if ( g_bEditorMode )
  {
    this->PAL3::PrintScreen();
    g_bEditorMode = 0;
  }
}

// 0x00406230
void PAL3::Destroy()
{
  PAL3 *Instance_db10; // eax

  PAL3 *Instance_fd20; // eax
  UIQuadManager *Instance; // eax
  ScriptSystem *v5; // ecx
  UISystem *v6; // ecx
  TextureLibDataBase *v7; // ecx
  PalScriptMgr *v8; // ecx
  CCBSystem *v9; // esi

  gbActorMgr *v11; // esi
  CScreenMode *v12; // eax
  void *v13; // [esp+0x0] [ebp-0x8]

  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((PAL3 *)Instance_db10))->PAL3::InvalidateSnapH();
  Instance_fd20 = (PAL3 *)this->PAL3::GetInstance_fd20();
  (((PAL3 *)Instance_fd20))->PAL3::ClearAdditiveEffects();
  Instance = (UIQuadManager *)UIQuadManager::GetInstance();
  crt_sub_005415C0(Instance);
  (((ScriptSystem *)v5))->ScriptSystem::Destroy();
  (((UISystem *)v6))->UISystem::Destroy();
  (((TextureLibDataBase *)v7))->TextureLibDataBase::_TextureLib_Data();
  (((PalScriptMgr *)v8))->PalScriptMgr::_CON_ReLoadScript();
  if ( g_pCBSystem )
  {
    (((CCBSystem *)&g_pCBSystem))->CCBSystem::ProcFling();
    v9 = g_pCBSystem;
    if ( g_pCBSystem )
    {
      NullCallback(v13);
      operator delete(v9);
    }
    g_pCBSystem = 0;
  }
  (((CGameData *)&g_gamefrm))->CGameData::Cleanup();
  this->PAL3::DestroyEffectSystem();
  if ( g_pCameraCtrl )
  {
    COERCE_VOID_THISCALL_DWORD_DWORD_(g_pCameraCtrl->m_pCamera->fov)(g_pCameraCtrl, 1);
    g_pCameraCtrl = 0;
  }
  v11 = g_pActorMgr;
  if ( g_pActorMgr )
  {
    (((gbActorMgr *)g_pActorMgr))->gbActorMgr::~gbActorMgr();
    operator delete(v11);
    g_pActorMgr = 0;
  }
  if ( gfxMgr )
  {
    (**(void ( ***)(gbGfxManager *, int))*(void**)(gfxMgr))((gbGfxManager *)(gfxMgr), (int)(1));
    gfxMgr = 0;
  }
  FileSysDestory();
  v12 = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)v12))->CScreenMode::Restore();
}

// 0x00406310
void PAL3::CheckSystemRequire(HINSTANCE hinst)
{
  char *v2; // edi
  char *v3; // esi
  _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v5; // esp
  DWORD v6; // esi
  HWND Window; // eax
  char *v8; // [esp-0x10] [ebp-0x116C]
  void *v9; // [esp-0x10] [ebp-0x116C]
  CHAR ClassName[20]; // [esp+0x0] [ebp-0x115C] BYREF
  tagRECT rc; // [esp+0x14] [ebp-0x1148] BYREF
  WNDCLASSA WndClass; // [esp+0x24] [ebp-0x1138] BYREF
  Config Buffer[7]; // [esp+0x4C] [ebp-0x1110] BYREF
  _BYTE v14[1024]; // [esp+0x150] [ebp-0x100C] BYREF
  char pExceptionObject[1024]; // [esp+0x550] [ebp-C0Ch] BYREF
  char ArgList; // [esp+0x950] [ebp-0x80C] BYREF
  char v17; // [esp+D50h] [ebp-0x40C] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v18; // [esp+0x1150] [ebp-0xC]
  void *v19; // [esp+0x1154] [ebp-0x8]
  int v20; // [esp+0x1158] [ebp-0x4]

  v20 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v19 = ((void*)0);
  v18 = (_EXCEPTION_REGISTRATION_RECORD *)ExceptionList;
  v5 = alloca(4432);
  strcpy(ClassName, "PAL3--SOFTSTAR.sh");
  WndClass.style = 32;
  WndClass.lpfnWndProc = WinProc;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hInstance = hinst;
  memset(&WndClass.hIcon, 0, 16);
  WndClass.lpszClassName = ClassName;
  if ( !RegisterClassA(&WndClass) )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException("RegisterClass Failed.", &path[72], 1094),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((Config *)Buffer))->Config::ReadINIInt(v2, v3);
  v20 = 0;
  (((Config *)Buffer))->Config::FormatSectionPath(filename, v8);
  g_DrvInfo.type = 2;
  g_DrvInfo.subtype = 0;
  (((Config *)Buffer))->Config::ReadSectionAsInt("display", section);
  (((Config *)Buffer))->Config::ReadSectionAsInt("display", "height");
  (((Config *)Buffer))->Config::ReadSectionAsInt("display", "colorbits");
  (((Config *)Buffer))->Config::ReadSectionAsInt("display", "depthbits");
  (((Config *)Buffer))->Config::ReadSectionAsInt("display", "rate");
  g_DrvInfo.nbackbuf = 2;
  g_DrvInfo.waitforverticalblank = (unsigned __int8)(g_dwGameFlags & 0x10) >> 4;
  g_DrvInfo.fullscreen = 1;
  g_DrvInfo.stensilbits = 0;
  strcpy(g_DrvInfo.winname, ClassName);
  g_DrvInfo.hinst = (unsigned int)hinst;
  g_DrvInfo.newwindow = 0;
  v6 = g_DrvInfo.fullscreen != 0 ? 8 : 0;
  SetRect(&rc, 0, 0, g_DrvInfo.width, g_DrvInfo.height);
  AdjustWindowRect(&rc, 0x96080000, 0);
  Window = CreateWindowExA(
             v6,
             ClassName,
             ClassName,
             0x96080000,
             0,
             0,
             rc.right - rc.left,
             rc.bottom - rc.top,
             0,
             0,
             hinst,
             0);
  if ( !Window )
  {
    qmemcpy(v14, (((Logger *)&v17))->Logger::FormatException("Window create failed", &path[72], 1152), sizeof(v14));
    _CxxThrowException(v14, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_DrvInfo.hgfxwnd = (unsigned int)Window;
  g_todo_BFDA4C = (int)Window;
  v20 = -1;
  NullCallback(v9);
}

// 0x004065F0
void PAL3::CreateGfxWindow()
{


  char v3; // al
  char v4; // al

  char v6; // al
  unsigned int v7; // eax
  char v8; // al
  unsigned int v9; // eax
  bool v10; // cc

  unsigned int v12; // eax

  char v14; // al
  bool v15; // zf
  unsigned int v16; // eax
  char v17; // al
  unsigned int v18; // eax

  g_nCombatMode = (int)GetCommandLineA();
  if ( g_nCombatMode )
  {
    this->PAL3::ParseCmdLine(CmdLine);
    if ( v3 || (this->PAL3::ParseCmdLine("softcursor"), v4) )
      g_bPAL3_BFDA91 = 1;
    this->PAL3::ParseCmdLine("xsnd");
    if ( v6 )
    {
      v7 = g_dwGameFlags;
      LOBYTE(v7) = g_dwGameFlags & 0xFE;
      g_dwGameFlags = v7;
    }
    this->PAL3::ParseCmdLine("xmusic");
    if ( v8 )
    {
      v9 = g_dwGameFlags;
      LOBYTE(v9) = g_dwGameFlags & 0xFB;
      g_dwGameFlags = v9;
    }
    v10 = PAL3::HasCommandLineParam() <= 0;
    v12 = g_dwGameFlags;
    if ( v10 )
      LOBYTE(v12) = g_dwGameFlags & 0xEF;
    else
      LOBYTE(v12) = g_dwGameFlags | 0x10;
    g_dwGameFlags = v12;
    this->PAL3::ParseCmdLine("motionblur");
    v15 = v14 == 0;
    v16 = g_dwGameFlags;
    if ( v15 )
      LOBYTE(v16) = g_dwGameFlags & 0xF7;
    else
      LOBYTE(v16) = g_dwGameFlags | 8;
    g_dwGameFlags = v16;
    this->PAL3::ParseCmdLine("scursor");
    if ( v17 )
      UIQuadManager::GetInstance()[7]._tail_000[1] = 1;
    v10 = PAL3::HasCommandLineParam() <= 60;
    v18 = g_dwGameFlags;
    if ( v10 )
      LOBYTE(v18) = g_dwGameFlags & 0xDF;
    else
      LOBYTE(v18) = g_dwGameFlags | 0x20;
    g_dwGameFlags = v18;
  }
}

// 0x004066F0
void PAL3::ParseCmdLine(const char *lpCmdLine)
{
  char *v2; // [esp+0x0] [ebp-0x340]
  char *v3; // [esp+0x0] [ebp-0x340]
  void *v4; // [esp+0x0] [ebp-0x340]
  char *v5; // [esp+0x4] [ebp-0x33C]
  char Buffer[32]; // [esp+0x10] [ebp-0x330] BYREF
  Config FileName[7]; // [esp+0x30] [ebp-0x310] BYREF
  char Str[512]; // [esp+0x134] [ebp-0x20C] BYREF
  int v9; // [esp+0x33C] [ebp-0x4]

  if ( strlen(lpCmdLine) < 0x14 && strlen(GetCommandLineA()) < 0x200 )
  {
    if ( strlen(GetCommandLineA()) )
    {
      strcpy((char *)Str, GetCommandLineA());
      sprintf(Buffer, aS, lpCmdLine);
      _strlwr(Str);
      _strlwr(Buffer);
      if ( !strstr(Str, Buffer) )
      {
        sprintf(Buffer, byte_583A1C, lpCmdLine);
        if ( !strstr(Str, Buffer) || strlen((const char *)Str) != strstr(Str, Buffer) - Str + strlen((const char *)Buffer) )
        {
          (((Config *)FileName))->Config::ReadINIInt(v2, v5);
          v9 = 0;
          (((Config *)FileName))->Config::FormatSectionPath(filename, v3);
          (((Config *)FileName))->Config::ReadSectionAsInt("misc", (char *)lpCmdLine);
          v9 = -1;
          NullCallback(v4);
        }
      }
    }
  }
}

// 0x004068C0
BOOL PAL3::HasCommandLineParam()
{
  BOOL result; // eax
  char *v1; // [esp+0x0] [ebp-0x11C]
  char *v2; // [esp+0x0] [ebp-0x11C]
  void *v3; // [esp+0x0] [ebp-0x11C]
  char *v4; // [esp+0x4] [ebp-0x118]
  Config Buffer[7]; // [esp+0xC] [ebp-0x110] BYREF
  int v6; // [esp+0x118] [ebp-0x4]
  char *lpKeyName; // [esp+0x120] [ebp+0x4]

  result = 0;
  if ( strlen(lpKeyName) < 0x14 )
  {
    (((Config *)Buffer))->Config::ReadINIInt(v1, v4);
    v6 = 0;
    (((Config *)Buffer))->Config::FormatSectionPath(filename, v2);
    (((Config *)Buffer))->Config::ReadSectionAsInt("display", lpKeyName);
    v6 = -1;
    NullCallback(v3);
    return 0;
  }
  return result;
}

// 0x00406980
int PAL3::GetCommandLineParam()
{
  LOBYTE(this) = *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 592);
  if ( !*((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 592)
    && !*((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 593)
    && !*((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 594)
    && !*((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 595)
    && !*((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 596) )
  {
    *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 592) = 1;
    *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 593) = 1;
    *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 594) = 0;
    *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 595) = 1;
    *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 596) = 0;
  }
  if ( !g_nPartyCount )
    this->PAL3::UpdateSubsystems();
  (((CCBSystem *)&g_pCBSystem))->CCBSystem::ProcMagicWait((unsigned int)g_nPartyRoles, 1);
  return (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)6);
}

// 0x00406A10
void PAL3::TestCombat()
{
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 108) = 27;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 111) = 9;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 112) = 9;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 117) = 27;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 124) = 9;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 100) = 256;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 101) = 257;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 102) = 134;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 103) = 135;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 104) = 136;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 105) = 137;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 106) = 32;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 107) = 13;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 110) = 154;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 109) = 155;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 113) = 97;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 114) = 100;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 115) = 256;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 116) = 257;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 118) = 13;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 119) = 32;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 120) = 134;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 121) = 135;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 122) = 136;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 123) = 137;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 125) = 119;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 126) = 138;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 127) = 139;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 128) = 140;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 129) = 141;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 130) = 142;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 131) = 130;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 132) = 132;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 133) = 112;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 134) = 114;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 135) = 102;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 136) = 107;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 137) = 101;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 138) = 130;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 139) = 132;
  *((_WORD *)&g_PAL3_Instance.m_Image2D + 140) = 128;
}

// 0x00406B80
void PAL3::DefaultKeyMap(int nVal, int nVal2)
{
  gbRenderEffect *v3; // eax
  bool v4; // zf
  char v5; // cl
  unsigned int v6; // esi
  char v7; // cl
  gbRenderEffect *v8; // ebx
  unsigned int v9; // edi
  unsigned int v10; // edi
  unsigned int v11; // kr04_4
  unsigned int v12; // ebx
  gbRenderEffect *m_pAdditiveEffect2; // edi
  char v14; // al
  int v15; // [esp+0x18] [ebp+0xC]

  g_bEditorMode = 1;
  if ( nVal )
  {
    v11 = strlen((const char *)nVal) + 1;
    v12 = v11 - 1;
    if ( (((std::string *)&g_PAL3_Instance.m_pAdditiveEffect))->max_size() < v11 - 1 )
      std::_Xlen();
    m_pAdditiveEffect2 = (gbRenderEffect *)g_PAL3_Instance.m_pAdditiveEffect2;
    if ( g_PAL3_Instance.m_pAdditiveEffect2
      && (v14 = HIBYTE(g_PAL3_Instance.m_pAdditiveEffect2[-1].m_ParamHandle[7])) != 0
      && v14 != -1 )
    {
      if ( v11 == 1 )
      {
        HIBYTE(g_PAL3_Instance.m_pAdditiveEffect2[-1].m_ParamHandle[7]) = v14 - 1;
        (((std::string *)0))->_Tidy();
        goto LABEL_43;
      }
    }
    else
    {
      if ( v11 == 1 )
      {
        (((std::string *)1))->_Tidy();
        goto LABEL_43;
      }
      if ( *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 2) <= 0x1Fu
        && *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 2) >= v12 )
      {
LABEL_42:
        qmemcpy(m_pAdditiveEffect2, (const void *)nVal, v12);
        *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) = v11 - 1;
        *((_BYTE *)((gbRefObject *)g_PAL3_Instance.m_pAdditiveEffect2) + v12) = 0;
        goto LABEL_43;
      }
      (((std::string *)1))->_Tidy();
    }
    (((GRPinput *)&g_PAL3_Instance.m_pAdditiveEffect))->GRPinput::PollInputState(v12);
    m_pAdditiveEffect2 = (gbRenderEffect *)g_PAL3_Instance.m_pAdditiveEffect2;
    goto LABEL_42;
  }
  v3 = (gbRenderEffect *)g_PAL3_Instance.m_pAdditiveEffect2;
  v4 = (bool)g_PAL3_Instance.m_pAdditiveEffect2 == 0;
  if ( g_PAL3_Instance.m_pAdditiveEffect2 )
  {
    v5 = HIBYTE(g_PAL3_Instance.m_pAdditiveEffect2[-1].m_ParamHandle[7]);
    if ( v5 && v5 != -1 )
    {
      (((SceneObj *)&g_PAL3_Instance.m_pAdditiveEffect))->SceneObj::UpdateAutoDelete(*((unsigned int *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1));
      v3 = (gbRenderEffect *)g_PAL3_Instance.m_pAdditiveEffect2;
    }
    v4 = (bool)v3 == 0;
    if ( v3 )
    {
      HIBYTE(v3[-1].m_ParamHandle[7]) = -1;
      v3 = (gbRenderEffect *)g_PAL3_Instance.m_pAdditiveEffect2;
      v4 = (bool)g_PAL3_Instance.m_pAdditiveEffect2 == 0;
    }
  }
  if ( v4 )
    v6 = 0;
  else
    v6 = (unsigned int)v3 + *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1);
  if ( v3 )
  {
    v7 = HIBYTE(v3[-1].m_ParamHandle[7]);
    if ( v7 && v7 != -1 )
    {
      (((SceneObj *)&g_PAL3_Instance.m_pAdditiveEffect))->SceneObj::UpdateAutoDelete(*((unsigned int *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1));
      v3 = (gbRenderEffect *)g_PAL3_Instance.m_pAdditiveEffect2;
    }
    if ( v3 )
    {
      HIBYTE(v3[-1].m_ParamHandle[7]) = -1;
      v3 = (gbRenderEffect *)g_PAL3_Instance.m_pAdditiveEffect2;
    }
  }
  v8 = (gbRenderEffect *)v3;
  (((std::string *)&g_PAL3_Instance.m_pAdditiveEffect))->_Freeze();
  if ( v8 )
    v9 = (char *)v8 - (char *)g_PAL3_Instance.m_pAdditiveEffect2;
  else
    v9 = 0;
  if ( v6 )
    v6 -= (unsigned int)v8;
  if ( *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) < v9 )
    std::_Xran();
  (((std::string *)&g_PAL3_Instance.m_pAdditiveEffect))->_Split();
  if ( *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v9 < v6 )
    v6 = *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v9;
  if ( v6 )
  {
    memcpy(
      (char *)g_PAL3_Instance.m_pAdditiveEffect2 + v9,
      (char *)g_PAL3_Instance.m_pAdditiveEffect2 + v6 + v9,
      *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v6 - v9);
    v10 = *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v6;
    if ( (((SceneObj *)&g_PAL3_Instance.m_pAdditiveEffect))->SceneObj::UpdateAutoDelete(*((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v6) )
    {
      *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) = v10;
      *((_BYTE *)((gbRefObject *)g_PAL3_Instance.m_pAdditiveEffect2) + v10) = 0;
    }
  }
LABEL_43:
  g_nKeyMap1 = nVal2;
  g_nKeyMap2 = v15;
}

// 0x00406D70
void PAL3::PrintScreen()
{
  int isdiskinfo; // edi
  unsigned __int8 *v2; // ebx
  unsigned int v3; // eax
  unsigned __int8 *v4; // ebx
  char *v5; // edx
  unsigned __int8 *v6; // edi
  unsigned __int8 *Image; // eax
  _BYTE *pBits; // ecx
  _BYTE *v9; // esi
  int v10; // edi
  int v11; // edx
  int v12; // ecx
  _BYTE *v13; // edx
  unsigned __int8 *v14; // ebx
  int v15; // edi
  int v16; // edx
  int v17; // esi
  unsigned int v18; // edx
  _BYTE *v19; // eax
  int v20; // edi
  int v21; // edx
  int v22; // esi
  _BYTE *v23; // eax
  int v24; // [esp+0x20] [ebp-F0h] BYREF
  int v25; // [esp+0x24] [ebp-ECh]
  int v26; // [esp+0x28] [ebp-E8h]
  int v27; // [esp+0x2C] [ebp-E4h]
  int v28; // [esp+0x30] [ebp-E0h]
  int v29; // [esp+0x34] [ebp-DCh]
  char *v30; // [esp+0x38] [ebp-D8h]
  gbImage2D v31; // [esp+0x3C] [ebp-D4h] BYREF
  int v32; // [esp+0x10C] [ebp-0x4]

  if ( (*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)*(void**)(gfxMgr) + 84))(gfxMgr, &v24, 1) )
  {
    v32 = 0;
    if ( v26 != 3 )
    {
      if ( v26 == 8 )
      {
        isdiskinfo = 32;
LABEL_8:
        v29 = isdiskinfo;
        v2 = (((gbImage2D *)&v31))->gbImage2D::CreateImage(v24, v25, isdiskinfo);
        v31.ImgInfo.goal = 0;
        v3 = isdiskinfo * v26 / 8;
        v4 = (unsigned __int8 *)&v2[v3 * (v27 - 1)];
        v5 = (char *)v30;
        if ( v27 > 0 )
        {
          do
          {
            qmemcpy(v4, v5, 4 * (v3 >> 2));
            v6 = (unsigned __int8 *)&v4[4 * (v3 >> 2)];
            v4 -= v3;
            qmemcpy(v6, &v5[4 * (v3 >> 2)], v3 & 3);
            v5 += v29;
            ++v31.ImgInfo.goal;
          }
          while ( v31.ImgInfo.goal < v27 );
          isdiskinfo = v31.ImgInfo.isdiskinfo;
        }
        (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 88))(gfxMgr);
        (((gbImage2D *)&g_PAL3_Instance.m_Image2D))->gbImage2D::Release();
        Image = (((gbImage2D *)&g_PAL3_Instance.m_Image2D))->gbImage2D::CreateImage(v27, v28, 24);
        pBits = (_BYTE *)v31.pBits;
        v9 = (_BYTE *)v31.pBits;
        if ( isdiskinfo == 32 )
        {
          v10 = 0;
          if ( v25 > 0 )
          {
            v11 = v24;
            do
            {
              v12 = 0;
              if ( v11 > 0 )
              {
                do
                {
                  v13 = (_BYTE *)v9;
                  v14 = (unsigned __int8 *)Image;
                  v9 += 4;
                  Image += 3;
                  ++v12;
                  *(_WORD *)v14 = *(_WORD *)v13;
                  v14[2] = v13[2];
                  v11 = v24;
                }
                while ( v12 < v24 );
              }
              ++v10;
            }
            while ( v10 < v25 );
          }
        }
        else if ( v26 == 9 )
        {
          v15 = 0;
          if ( v25 > 0 )
          {
            v16 = v24;
            do
            {
              v17 = 0;
              if ( v16 > 0 )
              {
                do
                {
                  LOBYTE(v16) = (unsigned long)*pBits;
                  pBits += 2;
                  *Image = 8 * v16;
                  LOWORD(v16) = *((_WORD *)pBits - 1);
                  v18 = (unsigned int)v16 >> 2;
                  v19 = (_BYTE *)(Image + 1);
                  *v19 = v18 & 0xF8;
                  LOWORD(v18) = *((_WORD *)pBits - 1);
                  *++v19 = (v18 >> 7) & 0xF8;
                  v16 = v24;
                  Image = (unsigned __int8 *)(v19 + 1);
                  ++v17;
                }
                while ( v17 < v24 );
              }
              ++v15;
            }
            while ( v15 < v25 );
          }
        }
        else
        {
          v20 = 0;
          if ( v25 > 0 )
          {
            v21 = v24;
            do
            {
              v22 = 0;
              if ( v21 > 0 )
              {
                do
                {
                  LOBYTE(v21) = (unsigned long)*pBits;
                  pBits += 2;
                  *Image = 8 * v21;
                  LOWORD(v21) = *((_WORD *)pBits - 1);
                  v23 = (_BYTE *)(Image + 1);
                  *v23++ = ((unsigned int)v21 >> 3) & 0xFC;
                  *v23 = *(pBits - 1) & 0xF8;
                  v21 = v24;
                  Image = (unsigned __int8 *)(v23 + 1);
                  ++v22;
                }
                while ( v22 < v24 );
              }
              ++v20;
            }
            while ( v20 < v25 );
          }
        }
        if ( g_nKeyMap1 != -1 && g_nKeyMap2 != -1 )
          (((gbImage2D *)&g_PAL3_Instance.m_Image2D))->gbImage2D::ScaleTo(g_nKeyMap1, g_nKeyMap2);
        (((gbImage2D *)&v31))->gbImage2D::Release();
        goto LABEL_34;
      }
      if ( v26 != 9 )
      {
        (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 88))(gfxMgr);
LABEL_34:
        v32 = -1;
        (((gbImage2D *)&v31))->gbImage2D::~gbImage2D();
        return;
      }
    }
    isdiskinfo = 16;
    goto LABEL_8;
  }
}

// 0x00406FF0
void PAL3::SnapScreen()
{
  PalScriptMgr *v0; // ecx
  RoleSystem *v1; // esi
  scAsmDecoder *v2; // ecx
  void (***v3)(_DWORD, _DWORD); // eax
  int v4; // [esp+0x4] [ebp+0x4]

  g_fDeltaTime = 0.0;
  g_nTickCount = v4;
  if ( v4 )
  {
    *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = 1;
    (((_Console *)g_pCameraCtrl))->_Console::SetActive((int)(&g_RoleSlotBuf.dword_17AA450 + 150));
  }
  PAL3::ReadRegistryValue(szSubKey, szValueName, 1);
  (((PalScriptMgr *)v0))->PalScriptMgr::Destroy();
  v1 = (RoleSystem *)&unk_C08160;
  do
  {
    (((RoleSystem *)v1))->RoleSystem::NotifyAndSetMode6();
    v1 = (RoleSystem *)((char *)v1 + 8704);
  }
  while ( (int)v1 < (int)&g_RoleSystemArrayEnd );
  (((scAsmDecoder *)v2))->scAsmDecoder::Execute(0, 1);
  g_nSceneState = 7;
  v3 = (void ( ***)(_DWORD, _DWORD))(((CGameData *)&g_gamefrm))->CGameData::SetMode(0);
  (**v3)((_DWORD)(v3), (_DWORD)(0));
  g_fFadeAngle = 0.0;
}

// 0x004070A0
bool PAL3::ReadRegistryValue(const CHAR *szSubKey, const CHAR *szValueName, ...)
{
  const CHAR *v2; // esi
  bool result; // al
  const CHAR *v4; // edi
  char v5; // al
  const char *Key; // eax
  const char *v7; // eax
  va_list Data; // [esp+0x18] [ebp+0xC] BYREF

  va_start(Data, szValueName);
  v2 = szSubKey;
  if ( !szSubKey )
    return 0;
  v4 = szValueName;
  if ( !szValueName )
    return 0;
  szValueName = (const CHAR *)1;
  PAL3::StartWolf(HKEY_LOCAL_MACHINE, (CHAR *)szSubKey);
  if ( !v5 )
  {
    Key = (const char *)RegCreateKeyExA(
                          HKEY_LOCAL_MACHINE,
                          v2,
                          0,
                          0,
                          0,
                          0xF003Fu,
                          0,
                          (PHKEY)&szSubKey,
                          (LPDWORD)&szValueName);
    result = ShowMessageBox(Key, szCaption);
    if ( !result )
      return result;
    RegCloseKey((HKEY)szSubKey);
  }
  RegOpenKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0x20006u, (PHKEY)&szSubKey);
  v7 = (const char *)RegSetValueExA((HKEY)szSubKey, v4, 0, 4u, (const BYTE *)Data, 4u);
  result = ShowMessageBox(v7, "Write Reg Error");
  if ( result )
  {
    RegCloseKey((HKEY)szSubKey);
    return 1;
  }
  return result;
}

// 0x00407180
void PAL3::StartWolf(HKEY hKey, CHAR *lpSubKey)
{
  RegOpenKeyExA(hKey, lpSubKey, 0, 0x20019u, (PHKEY)&lpSubKey);
  RegCloseKey((HKEY)lpSubKey);
}

// 0x004071C0
void PAL3::EndWolf()
{
  _DWORD *v0; // esi
  PalScriptMgr *v1; // ecx
  float v2; // eax
  void ( ***v3)(_DWORD, int); // eax
  PalScriptMgr *v4; // ecx
  int v5; // eax
  CScreenMode *v6; // ecx
  PtrArray *v7; // eax
  int v8; // eax
  CScreenMode *v9; // ecx
  PtrArray *SoundList; // eax
  int v11; // [esp-0x4] [ebp-0x18]
  int v12; // [esp-0x4] [ebp-0x18]
  int nSkillGDBID[5]; // [esp+0x0] [ebp-0x14]
  void *retaddr; // [esp+0x14] [ebp+0x0]

  v0 = (_DWORD *)&unk_C08160.m_nMoveMode;
  do
  {
    (((RoleSystem *)(v0 - 316)))->RoleSystem::Notify();
    *v0 = 2;
    v0 += 2176;
  }
  while ( (int)v0 < (int)dword_C10E50 );
  if ( g_nTickCount )
  {
    nSkillGDBID[0] = 0;
    (((PalScriptMgr *)v1))->PalScriptMgr::Destroy();
    g_fDeltaTime = v2;
  }
  else
  {
    g_nSceneState = 2;
    v3 = (void ( ***)(_DWORD, int))(((CGameData *)&g_gamefrm))->CGameData::SetMode(0);
    (**v3)((_DWORD)((_DWORD)(v3)), (int)(1));
    if ( retaddr == (void *)-1 )
    {
      (((PalScriptMgr *)v4))->PalScriptMgr::Destroy();
      v12 = v8;
      SoundList = (((CScreenMode *)v9))->CScreenMode::GetSoundList();
      (((PtrArray *)SoundList))->PtrArray::SetResolution(0, v12);
    }
    else
    {
      (((PalScriptMgr *)v4))->PalScriptMgr::Destroy();
      v11 = v5;
      v7 = (((CScreenMode *)v6))->CScreenMode::GetSoundList();
      (((PtrArray *)v7))->PtrArray::SetResolution(0, v11);
      if ( (unsigned int)g_nWolfIndex < 4 )
      {
        nSkillGDBID[0] = 80015;
        nSkillGDBID[1] = 83012;
        nSkillGDBID[2] = 8153;
        nSkillGDBID[3] = 8154;
        PalScriptMgr::HandleGetItem(nSkillGDBID[g_nWolfIndex]);
      }
      ++g_nWolfIndex;
    }
  }
}

// 0x004072D0
void PAL3::StartHideFight()
{
  void (***v1)(_DWORD, _DWORD); // eax

  g_nSceneState = 8;
  g_fFadeAngle = 0.0;
  v1 = (void ( ***)(_DWORD, _DWORD))(((CGameData *)&g_gamefrm))->CGameData::SetMode(0);
  (**v1)((_DWORD)(v1), (_DWORD)(0));
}

// 0x00407300
void PAL3::EndHideFight()
{
  void ( ***v1)(_DWORD, int); // eax

  g_nSceneState = 2;
  v1 = (void ( ***)(_DWORD, int))(((CGameData *)&g_gamefrm))->CGameData::SetMode(0);
  (**v1)((_DWORD)((_DWORD)(v1)), (int)(1));
}

// 0x00407320
void PAL3::StartCombat(unsigned int *const pdwVal, int monsterid, Role *side, char pMonster)
{
  PAL3 *v4; // ecx
  RoleSystem *v5; // ebx
  RoleSystem *v6; // eax
  int RolePtr; // esi
  int v8; // edi
  __int64 v9; // rax
  int v10; // ecx
  int v11; // esi
  int i; // eax
  Scene *v13; // edi
  Scene *v14; // eax
  char *v15; // esi
  CScreenMode *Instance; // eax
  int v17; // [esp+0x0] [ebp-0x11C] BYREF
  char Buffer[256]; // [esp+0xC] [ebp-0x110] BYREF
  int *v19; // [esp+0x10C] [ebp-0x10]
  int v20; // [esp+0x118] [ebp-0x4]

  v20 = 0;
  v19 = (int *)&v17;
  (((PAL3 *)v4))->PAL3::UIPostProcess();
  v5 = g_pRoleSystem;
  if ( g_pRoleSystem )
  {
    v6 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v6))->RoleSystem::GetRolePtr(v5->m_partyActor.m_nState);
    v8 = (__int64)((*(float *)&v5->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_nGameTime);
    v9 = (__int64)((*(float *)&v5->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_nGameTime);
    if ( v8 < 0 || (v10 = *(_DWORD *)(RolePtr + 152), v8 >= v10) || (int)v9 < 0 || (int)v9 >= *(_DWORD *)(RolePtr + 156) )
      v11 = 2;
    else
      v11 = *(unsigned __int8 *)(*(_DWORD *)(RolePtr + 160) + 8 * (v8 + v9 * v10) + 5);
    for ( i = 0; i < 6; ++i )
      g_nPartyRoles[i] = pdwVal[i];
    v13 = UISceneUpdate();
    v14 = UISceneUpdate();
    sprintf(Buffer, (const char *)&dir[24], v14, &v13->m_pCapacity[5]);
    (((PalScript *)g_ScriptSlots))->PalScript::SetDirectory(Buffer);
    sprintf(Buffer, (const char *)&dir[20], v11);
    if ( !(((PalScript *)g_ScriptSlots))->PalScript::FindSaveStateString((PalScript *)Buffer, (char *)&unk_C11720, (char *)0x20, v17) )
      (((PalScript *)g_ScriptSlots))->PalScript::FindSaveStateString((PalScript *)&dir[12], (char *)&unk_C11720, (char *)0x20, v17);
    (((PalScript *)g_ScriptSlots))->PalScript::SetDirectory(dir);
    if ( (((PalScript *)g_ScriptSlots))->PalScript::FindSaveStateString(&unk_C11720, Buffer, (char *)0x100, v17) )
      unk_C11720.m_bEnabled = atoi((const char *)Buffer);
    else
      unk_C11720.m_bEnabled = 1;
    if ( monsterid == 1 )
      unk_C11720.m_nTodo_024 = 2;
    else
      unk_C11720.m_nTodo_024 = monsterid == 2;
    unk_C11720.m_nTodo_34 = (int)side;
    byte_C11751 = pMonster;
    if ( (((CCBSystem *)&g_pCBSystem))->CCBSystem::ProcMagicWait((unsigned int)g_nPartyRoles, 0) )
    {
      if ( !pMonster || !CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v15 = (char *)UISceneUpdate();
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::PlayCombatMusic(v15);
      }
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)6);
    }
  }
}

// 0x00407560
char PAL3::StartCombatFromNPC(const NPCInfo *pNPCInfo, int tmp, Role *side)
{
  char result; // al
  unsigned int pdwVal[8]; // [esp+0xC] [ebp-0x220] BYREF
  char v5[4]; // [esp+0x2C] [ebp-0x200] BYREF
  int v6; // [esp+0x4C] [ebp-0x1E0]
  int v7; // [esp+0x50] [ebp-0x1DC]
  char v8; // [esp+0x54] [ebp-0x1D8]
  int v9; // [esp+0x58] [ebp-0x1D4]
  char v10; // [esp+0x5C] [ebp-0x1D0]
  char v11; // [esp+0x5E] [ebp-0x1CE]
  int v12; // [esp+0x60] [ebp-0x1CC]
  PAL3 *v13[114]; // [esp+0x64] [ebp-0x1C8] BYREF

  v8 = 0;
  pdwVal[7] = 0x7FFFFFFF;
  strcpy((char *)v5, (const char *)&dir[32]);
  v6 = 1;
  v11 = 1;
  v9 = -1;
  v7 = 0;
  v12 = 0;
  v10 = 0;
  qmemcpy(v13, pNPCInfo, sizeof(v13));
  if ( byte_C10CC1 )
    LOBYTE(v13[32]) = 6;
  (((PAL3 *)v13[29]))->PAL3::UpdateSubsystems();
  PAL3::StartCombat(pdwVal, tmp, side, 0);
  return result;
}

// 0x00407640
void PAL3::EntryCatchGhost()
{
  int v1; // esi
  int *p_pPoint; // edi
  RoleSystem *v3; // esi
  RoleSystem *v4; // eax
  int RolePtr; // edi
  int v6; // ebx
  int m_nState; // [esp-0x8] [ebp-0x2C]
  int pPoint; // [esp+0x8] [ebp-0x1C] BYREF
  int v9; // [esp+0xC] [ebp-0x18]
  int v10; // [esp+0x10] [ebp-0x14]
  int p_DWORD; // [esp+0x14] [ebp-0x10] BYREF
  int v12; // [esp+0x18] [ebp-0xC]
  int v13; // [esp+0x1C] [ebp-0x8]
  int v14; // [esp+0x20] [ebp-0x4]

  v1 = 0;
  if ( UIScene::ProcessInput(&dir[36], 0) )
  {
    pPoint = 6308;
    v9 = 6309;
    v10 = 6310;
    v12 = 0;
    v13 = 0;
    p_pPoint = (int *)&pPoint;
    do
    {
      p_DWORD = (unsigned long)*p_pPoint;
      if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD) )
        break;
      ++v1;
      ++p_pPoint;
    }
    while ( v1 < 3 );
  }
  else
  {
    v3 = g_pRoleSystem;
    m_nState = g_pRoleSystem->m_partyActor.m_nState;
    v4 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v4))->RoleSystem::GetRolePtr(m_nState);
    v6 = (__int64)((*(float *)&v3->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_nGameTime);
    v9 = (__int64)((*(float *)&v3->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_nGameTime);
    pPoint = v6;
    p_DWORD = 23;
    v12 = 93;
    v13 = 30;
    v14 = 96;
    PointInRect(&p_DWORD, &pPoint);
  }
}

// 0x00407740
int PAL3::IfHideFightSucceed()
{
  PAL3 *v0; // ecx
  int result; // eax
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  int v4; // [esp+0x4] [ebp+0x4]

  result = v4 - 2;
  if ( v4 == 2 )
  {
    if ( (g_dwGameFlags & 1) != 0 )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
      (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
    }
    (((PAL3 *)v0))->PAL3::UIPostProcess();
    (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
    UIQuadManager::GetInstance();
    return crt_sub_00541590();
  }
  return result;
}

// 0x00408BE0
int PAL3::InitSubsystems()
{

  tagRECT pRect; // [esp+0x0] [ebp-0x10] BYREF

  pRect.left = 0;
  pRect.top = 0;
  pRect.right = 40;
  pRect.bottom = 32;
  (((UIWnd *)&g_palScript))->UIWnd::Create(0, &pRect, 0);
  (((UIScene *)&g_palScript))->UIScene::LoadResource("ui\\scene\\tiao");
  UIScene_SetController(1082130432);
  (((CCBPanelSlot *)&g_palScript))->CCBPanelSlot::ShowClipped(0);
  (((UINote *)&dword_BFDAB0))->UINote::Create(1, (int)&pRect, 0, "ui\\flex\\note");
  (((UIScene *)&dword_BFDAB0))->UIScene::SetState(1);
  g_C10Data.m_nEffParamBase[0] = 1101838418;
  g_C10Data.m_nEffParamBase[1] = 0;
  g_C10Data.m_nEffParamBase[2] = -1038795408;
  g_C10Data.m_nEffParam0 = -1037468958;
  g_C10Data.m_nEffParam10 = 0;
  g_C10Data.m_nEffParam14 = -1040166416;
  g_C10Data.m_nEffParam1 = -1043495648;
  g_C10Data.m_nEffParam1C = 0;
  g_C10Data.m_nEffTypeID = -1030531316;
  g_C10Data.m_nEffParam24 = 1105702418;
  g_C10Data.m_nEffTypeCode = 0;
  g_C10Data.m_nEffParam2C = -1029309724;
  g_C10Data.m_nEffParam30 = 1105702418;
  g_C10Data.m_nEffParam34 = 0;
  g_C10Data.m_nEffParam38 = -1024066844;
  return this->PAL3::FullInit();
}

// 0x00408FD0
int PAL3::FullInit()
{
  ScriptCounter *v1; // eax
  char **p_m_pData; // edx
  char *v3; // esi
  const char **v4; // ebp
  const char *v5; // edi
  int v6; // eax
  int i; // esi
  int RoleNum; // eax
  char *m_pData; // esi
  int v10; // edi
  int v11; // eax
  bool v12; // sf
  int v13; // ebp
  int v14; // eax
  char *v15; // edi
  int v16; // eax
  char *j; // eax
  _DWORD *v18; // ecx
  int k; // eax
  int v20; // ecx
  int v21; // edx
  int v22; // eax
  char *v23; // esi
  int v24; // edi
  int v25; // eax
  int v26; // ebp
  int v27; // eax
  char *v28; // edi
  int v29; // eax
  char *m; // eax
  _DWORD *v31; // ecx
  int n; // eax
  int v33; // ecx
  int v34; // edx
  char *v35; // esi
  int v36; // edi
  int v37; // eax
  int v38; // ebp
  int v39; // eax
  char *v40; // edi
  int v41; // eax
  char *ii; // eax
  _DWORD *v43; // edx
  char *v44; // esi
  int v45; // edi
  int v46; // eax
  int v47; // ebp
  int v48; // eax
  char *v49; // edi
  int v50; // eax
  char *jj; // eax
  _DWORD *v52; // ecx
  char *v53; // esi
  int v54; // edi
  int v55; // eax
  int v56; // ebp
  int v57; // eax
  char *v58; // edi
  int v59; // eax
  char *kk; // eax
  _DWORD *v61; // ecx
  char *v62; // esi
  int v63; // edi
  int v64; // eax
  int v65; // ebp
  int v66; // eax
  char *v67; // edi
  int v68; // eax
  char *mm; // eax
  _DWORD *v70; // ecx
  int v71; // eax
  int nn; // eax
  int v73; // ecx
  int v74; // edx
  char *v75; // esi
  int v76; // edi
  int v77; // eax
  int v78; // ebp
  int v79; // eax
  char *v80; // edi
  int v81; // eax
  char *i1; // eax
  _DWORD *v83; // ecx
  char *v84; // esi
  int v85; // edi
  int v86; // eax
  int v87; // ebp
  int v88; // eax
  char *v89; // edi
  int v90; // eax
  char *i2; // eax
  _DWORD *v92; // ecx
  char *v93; // esi
  int v94; // edi
  int v95; // eax
  int v96; // ebp
  int v97; // eax
  char *v98; // edi
  int v99; // eax
  char *i3; // eax
  _DWORD *v101; // ecx
  char *v102; // esi
  int v103; // edi
  int v104; // eax
  int v105; // ebp
  int v106; // eax
  char *v107; // edi
  int v108; // eax
  char *i4; // eax
  _DWORD *v110; // ecx
  int v111; // ebp
  int i5; // eax
  int v113; // ecx
  int v114; // edx
  char *v115; // esi
  int v116; // edx
  int v117; // edi
  int v118; // eax
  gbVec3D *v119; // ebp
  int v120; // edx
  char *v121; // eax
  _DWORD *v122; // edx
  gbVec3D *v123; // esi
  int v124; // ebp
  int v125; // edx
  int v126; // eax
  gbVec3D *v127; // eax
  gbVec3D *v128; // ebp
  gbVec3D *i6; // edi
  int v130; // eax
  gbVec3D *v131; // eax
  _DWORD *p_x; // ecx
  gbVec3D *v133; // esi
  int v134; // ebp
  int v135; // edx
  int v136; // eax
  gbVec3D *v137; // eax
  gbVec3D *v138; // ebp
  gbVec3D *i7; // edi
  int v140; // eax
  gbVec3D *v141; // eax
  _DWORD *v142; // ecx
  int i8; // ecx
  int result; // eax
  void *pSceneName; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  int pRoleTriple[3]; // [esp+0x18] [ebp-0x20] BYREF
  _DWORD aSceneData[5]; // [esp+0x24] [ebp-0x14] BYREF

  memset(g_SaveSlotFlags, 0, sizeof(g_SaveSlotFlags));
  if ( dword_C10CBC )
  {
    (**(void ( ***)(int, int))dword_C10CBC)((int)(dword_C10CBC), (int)(1));
    dword_C10CBC = 0;
  }
  memset(g_ScriptCounters, 0, sizeof(g_ScriptCounters));
  v1 = g_ScriptCounters;
  do
  {
    v1->nState = 1;
    v1->nMaxCount = 10;
    v1->nResourceID = 0;
    ++v1;
  }
  while ( (int)v1 < (int)&g_ScriptCountersEnd );
  g_ScriptCounters[0].nMaxCount = 30;
  g_ScriptCounters[1].nMaxCount = 30;
  g_ScriptCounters[4].nResourceID = 6701;
  g_ScriptCounters[2].nMaxCount = 20;
  g_ScriptCounters[3].nMaxCount = 20;
  g_ScriptCounters[5].nResourceID = 6702;
  g_ScriptCounters[6].nResourceID = 6703;
  g_ScriptCounters[7].nResourceID = 6704;
  g_ScriptCounters[8].nResourceID = 6705;
  g_ScriptCounters[9].nResourceID = 84018;
  dword_C10CD4 = 0;
  nVal = 0;
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::Reset();
  *(&g_RoleSlotBuf.dword_17AA450 + 136) = *(&g_RoleSlotBuf.dword_17AA450 + 135);
  g_nFrameRate = 35;
  p_m_pData = (char **)&g_SceneMgrPrefix.m_pData;
  do
  {
    *p_m_pData = *(p_m_pData - 1);
    p_m_pData += 4;
  }
  while ( (int)p_m_pData < (int)&g_RoleSlotBuf.m_wndcolor );
  byte_C10CC1 = 0;
  memset(&g_nScriptEventParam, 0, 0x20u);
  g_nCurrentEventId = 31;
  dword_C10CD0 = 0;
  memset(&g_RoleSlotBuf, 0, 0x1B80u);
  aSceneData[0] = dword_58619C;
  aSceneData[1] = (unsigned long)&g_pszSceneSlot1;
  aSceneData[2] = (unsigned long)&g_pszSceneSlot2;
  aSceneData[3] = g_szFormat105;
  aSceneData[4] = g_pfnUpdateFuncs;
  pSceneName = 0;
  v3 = (char *)&g_RoleSlotBuf.dword_17AA450 + 774;
  v4 = (const char **)aSceneData;
  do
  {
    v5 = (const char *)*v4;
    (((Camera *)(v3 - 174)))->Camera::InitFromScene(*v4);
    strncpy(v3, v5, 0x1Fu);
    *(_DWORD *)(v3 + 1090) = 1;
    *(_DWORD *)(v3 + 1086) = 1;
    *(_DWORD *)(v3 + 458) = 0;
    *(v3 - 1) = -1;
    *(v3 - 2) = pSceneName;
    v3 += 8704;
    ++v4;
    ++pSceneName;
  }
  while ( (int)v3 < (int)byte_C10A0E );
  (((Camera *)&g_RoleSystemMain))->Camera::InitFromScene(g_pszScene2);
  g_RoleSystemMain.m_nFacing = 5;
  v6 = nVal;
  strcpy(&g_RoleSystemMain.m_nAnimState, g_pszScene2);
  g_RoleSystemMain.m_nMoveMode = 0;
  g_RoleSystemMain.m_partyActor.m_pRoleObj = 0;
  g_RoleSystemMain.m_partyActor.m_nPathEnabled = 1;
  g_RoleSystemMain.m_nActionState = -1;
  NPC::SetRoleMode(v6);
  (((Camera *)&g_RoleSystemExtra1))->Camera::InitFromScene(g_pszScene1);
  strcpy(&g_RoleSystemExtra1.m_nAnimState, g_pszScene1);
  g_RoleSystemExtra1.m_nMoveMode = 1;
  g_RoleSystemExtra1.m_partyActor.m_pRoleObj = 0;
  (((Camera *)&g_RoleSystemExtra0))->Camera::InitFromScene(g_pszDefaultScene);
  strcpy(&g_RoleSystemExtra0.m_nAnimState, g_pszDefaultScene);
  g_RoleSystemExtra0.m_nMoveMode = 1;
  g_RoleSystemExtra0.m_partyActor.m_pRoleObj = 0;
  CameraSystem::BindToRoleSlot((int)(&g_RoleSlotBuf.dword_17AA450 + 150));
  dword_C10CC8 = 0;
  (((_Console *)g_pCameraCtrl))->_Console::SetActive((int)(&g_RoleSlotBuf.dword_17AA450 + 150));
  *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 592) = 1;
  *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 593) = 0;
  *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 594) = 0;
  *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 595) = 0;
  *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 596) = 0;
  BYTE2(g_RoleSlotBuf.m_nAnimCopy2) = 3;
  *((_BYTE *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state + 1130) = 5;
  BYTE2(g_RoleSlotBuf.m_configData[31]) = 1;
  BYTE2(g_RoleSlotBuf.m_teamData3[219]) = 2;
  *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 534) = 4;
  g_fCamRoleParams[0] = 0.60000002;
  g_fCamRoleParams[1] = 0.80000001;
  g_fCamRoleParams[2] = 0.40000001;
  g_fCamRoleParams[3] = 0.40000001;
  g_fCamRoleParams[4] = 0.40000001;
  g_fCamRoleParams[5] = 0.40000001;
  g_fCamRoleParams[6] = 0.2;
  g_fCamRoleParams[7] = 0.2;
  g_fCamRoleParams[8] = 0.40000001;
  g_fCamRoleParams[9] = 0.40000001;
  g_fCamRoleParams[10] = 0.050000001;
  g_fCamRoleParams[11] = 0.2;
  g_fCamRoleParams[12] = 0.050000001;
  g_fCamRoleParams[13] = 0.1;
  g_fCamRoleParams[14] = 0.050000001;
  g_fCamRoleParams[15] = 0.40000001;
  g_fCamRoleParams[16] = 0.40000001;
  g_fCamRoleParams[17] = 0.80000001;
  g_fCamRoleParams[18] = 0.60000002;
  g_fCamRoleParams[19] = 0.40000001;
  g_fCamRoleParams[20] = 0.2;
  g_fCamRoleParams[21] = 0.1;
  g_fCamRoleParams[22] = 0.1;
  g_fCamRoleParams[23] = 0.40000001;
  g_fCamRoleParams[24] = 0.2;
  g_fCamRoleParams[25] = 0.89999998;
  g_fCamRoleParams[26] = 1.0;
  g_fCamRoleParams[27] = 0.89999998;
  g_fCamRoleParams[28] = 0.89999998;
  g_fCamRoleParams[29] = 0.89999998;
  g_fCamRoleParams[30] = 0.2;
  g_fCamRoleParams[31] = 0.1;
  g_fCamRoleParams[32] = 0.1;
  g_fCamRoleParams[33] = 0.2;
  g_fCamRoleParams[34] = 0.40000001;
  g_fCamRoleParams[35] = 0.050000001;
  g_fCamRoleParams[36] = 0.050000001;
  g_fCamRoleParams[37] = 0.2;
  g_fCamRoleParams[38] = 0.1;
  g_fCamRoleParams[39] = 0.050000001;
  for ( i = 0; i < 5; ++i )
  {
    NPC::Create(i);
    NPC::Init(i);
  }
  memset32(g_nRoleInitLevel, 20, 6u);
  *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[11] = 2224;
  *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[15] = 10;
  g_RoleSlotBuf.m_partyActor.m_nModelParamB = 0;
  g_RoleSlotBuf.m_partyActor.m_nRoleState1 = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 = ((RoleAtt *)0);
  g_RoleSlotBuf.m_partyActor.m_nAnimFrames = 0;
  g_RoleSlotBuf.m_partyActor.m_nTransitionParam = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[0] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[1] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[2] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[0] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[1] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[2] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[3] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[4] = 0;
  g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[5] = 0;
  g_RoleSlotBuf.m_partyActor.m_fBlendWeight = 0.0;
  g_RoleSlotBuf.m_partyActor.m_obbox = 0;
  *(&g_RoleSlotBuf.m_partyActor.m_obbox + 1) = 0;
  g_RoleSlotBuf.m_partyActor.m_pSelfAtt = ((void *)0);
  pRoleTriple[0] = 301;
  pRoleTriple[1] = 0;
  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(301);
  m_pData = (char *)g_SceneMgrPrefix.m_pData;
  pRoleTriple[2] = RoleNum;
  if ( (int)(g_SceneMgrPrefix.m_nCapacity - (unsigned int)g_SceneMgrPrefix.m_pData) / 12 )
  {
    (((Array *)&g_SceneMgrPrefix))->Array::Insert(g_SceneMgrPrefix.m_pData, g_SceneMgrPrefix.m_pData);
    (((Array *)&g_SceneMgrPrefix))->Array::Erase((int)g_SceneMgrPrefix.m_pData, 1 - (g_SceneMgrPrefix.m_pData - m_pData) / 12);
    for ( j = g_SceneMgrPrefix.m_pData; m_pData != j; v18[2] = pRoleTriple[2] )
    {
      v18 = (_DWORD *)m_pData;
      m_pData += 12;
      *v18 = pRoleTriple[0];
      v18[1] = pRoleTriple[1];
    }
    g_SceneMgrPrefix.m_pData += 12;
  }
  else
  {
    if ( (unsigned int)(((Array *)&g_SceneMgrPrefix))->Array::Size() <= 1 )
      v10 = 1;
    else
      v10 = (((Array *)&g_SceneMgrPrefix))->Array::Size();
    v11 = (((Array *)&g_SceneMgrPrefix))->Array::Size();
    v12 = v10 + v11 < 0;
    v13 = v10 + v11;
    v14 = v10 + v11;
    if ( v12 )
      v14 = 0;
    v15 = (char *)operator new(12 * v14);
    pNewBuffer = (((Array *)&g_SceneMgrPrefix))->Array::Insert((void *)g_SceneMgrPrefix.m_nSize, m_pData);
    (((Array *)&g_SceneMgrPrefix))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_SceneMgrPrefix))->Array::Insert(m_pData, g_SceneMgrPrefix.m_pData);
    nullsub_2(g_SceneMgrPrefix.m_nSize, g_SceneMgrPrefix.m_pData);
    operator delete((void *)g_SceneMgrPrefix.m_nSize);
    g_SceneMgrPrefix.m_nCapacity = (int)&v15[12 * v13];
    v16 = (((Array *)&g_SceneMgrPrefix))->Array::Size();
    g_SceneMgrPrefix.m_nSize = (int)v15;
    g_SceneMgrPrefix.m_pData = ((char *)(&v15[12 * v16 + 12]));
  }
  g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z = 0.0;
  g_RoleSlotBuf.m_partyActor.m_pRoleObj = 1;
  g_RoleSlotBuf.m_partyActor.m_nPathEnabled = Role::CalcXueJianInit(0, 1);
  *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fScale = Role::CalcLongKuiInit(0, g_RoleSlotBuf.m_partyActor.m_pRoleObj);
  LODWORD(g_RoleSlotBuf.m_partyActor.m_fMatrixA) = Role::CalcZiXuanInit(0, g_RoleSlotBuf.m_partyActor.m_pRoleObj);
  *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixB = Role::CalcChangQingInit(0, g_RoleSlotBuf.m_partyActor.m_pRoleObj);
  LODWORD(g_RoleSlotBuf.m_partyActor.m_fMatrixC) = Role::CalcHuaYingInit(0, g_RoleSlotBuf.m_partyActor.m_pRoleObj);
  g_RoleSlotBuf.m_partyActor.m_dwMatMsg[7] = 3;
  g_RoleSlotBuf.m_partyActor.m_nMatrixParam = 3;
  g_RoleSlotBuf.m_partyActor.m_dwMatMsg[9] = 3;
  LODWORD(g_RoleSlotBuf.m_partyActor.m_fMatrixParamB) = 3;
  g_RoleSlotBuf.m_partyActor.m_dwMatMsg[10] = 3;
  LODWORD(g_RoleSlotBuf.m_partyActor.m_fMatrixE) = 3;
  g_RoleSlotBuf.m_partyActor.m_dwMatMsg[8] = 2;
  LODWORD(g_RoleSlotBuf.m_partyActor.m_fMatrixParamA) = 2;
  *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[7] = 2;
  g_RoleSlotBuf.m_partyActor.m_Actor = 2;
  *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_bChangedMat = 6;
  LODWORD(g_RoleSlotBuf.m_partyActor.m_fMatrixF) = 6;
  *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[3] = 1;
  LODWORD(g_RoleSlotBuf.m_partyActor.m_fMatrixParamC) = 1;
  (((RoleSystem *)&g_RoleSlotBuf))->RoleSystem::RecalcAggregatedStats(1);
  for ( k = 972; k < 1020; k += 4 )
  {
    v20 = *(_DWORD *)((char *)((UIWnd *)&g_RoleSlotBuf) + k);
    v21 = *(int *)((char *)&g_nSceneFlags.m_pDataStart + k);
    if ( v20 < v21 )
    {
      if ( v20 <= 0 )
        *(_DWORD *)((char *)((UIWnd *)&g_RoleSlotBuf) + k) = 0;
    }
    else
    {
      *(_DWORD *)((char *)((UIWnd *)&g_RoleSlotBuf) + k) = v21;
    }
  }
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 58) = 0;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 59) = 0;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 60) = 0;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 61) = 0;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 62) = 0;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 63) = 0;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 64) = 0;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 65) = 0x1411900000000i64;
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = 1;
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(82201);
  pRoleTriple[0] = 321;
  pRoleTriple[1] = 0;
  v22 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(321);
  v23 = (char *)g_RoleTeamArray.m_pData;
  pRoleTriple[2] = v22;
  if ( (int)(g_RoleTeamArray.m_nCapacity - (unsigned int)g_RoleTeamArray.m_pData) / 12 )
  {
    (((Array *)&g_RoleTeamArray))->Array::Insert(g_RoleTeamArray.m_pData, g_RoleTeamArray.m_pData);
    (((Array *)&g_RoleTeamArray))->Array::Erase((int)g_RoleTeamArray.m_pData, 1 - (g_RoleTeamArray.m_pData - v23) / 12);
    for ( m = g_RoleTeamArray.m_pData; v23 != m; v31[2] = pRoleTriple[2] )
    {
      v31 = (_DWORD *)v23;
      v23 += 12;
      *v31 = pRoleTriple[0];
      v31[1] = pRoleTriple[1];
    }
    g_RoleTeamArray.m_pData += 12;
  }
  else
  {
    if ( (unsigned int)(((Array *)&g_RoleTeamArray))->Array::Size() <= 1 )
      v24 = 1;
    else
      v24 = (((Array *)&g_RoleTeamArray))->Array::Size();
    v25 = (((Array *)&g_RoleTeamArray))->Array::Size();
    v12 = v24 + v25 < 0;
    v26 = v24 + v25;
    v27 = v24 + v25;
    if ( v12 )
      v27 = 0;
    v28 = (char *)operator new(12 * v27);
    pNewBuffer = (((Array *)&g_RoleTeamArray))->Array::Insert((void *)g_RoleTeamArray.m_nSize, v23);
    (((Array *)&g_RoleTeamArray))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_RoleTeamArray))->Array::Insert(v23, g_RoleTeamArray.m_pData);
    nullsub_2(g_RoleTeamArray.m_nSize, g_RoleTeamArray.m_pData);
    operator delete((void *)g_RoleTeamArray.m_nSize);
    g_RoleTeamArray.m_nCapacity = (int)&v28[12 * v26];
    v29 = (((Array *)&g_RoleTeamArray))->Array::Size();
    g_RoleTeamArray.m_nSize = (int)v28;
    g_RoleTeamArray.m_pData = ((char *)(&v28[12 * v29 + 12]));
  }
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = 0;
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = 1;
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = Role::CalcXueJianInit(1, 1);
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = Role::CalcLongKuiInit(
                                                      1,
                                                      (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0]);
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = Role::CalcZiXuanInit(
                                                      1,
                                                      (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0]);
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = Role::CalcChangQingInit(
                                                      1,
                                                      (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0]);
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = Role::CalcHuaYingInit(
                                                      1,
                                                      (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0]);
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 78) = 0x500000003i64;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 36) = 0x500000003i64;
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = 5;
  (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = 5;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 76) = 0x200000004i64;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 34) = 0x200000004i64;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 77) = 0x200000004i64;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state.m_nTodo_704 + 35) = 0x200000004i64;
  (((RoleSystem *)&g_RoleSlotBuf.m_nAnimCopy3))->RoleSystem::RecalcAggregatedStats(1);
  for ( n = 972; n < 1020; n += 4 )
  {
    v33 = *(int *)((char *)&g_RoleSlotBuf.m_nAnimCopy3 + n);
    v34 = *(int *)((char *)&g_RoleSlotBuf.m_FrameA.m_childs.m_nSize + n);
    if ( v33 < v34 )
    {
      if ( v33 <= 0 )
        *(int *)((char *)&g_RoleSlotBuf.m_nAnimCopy3 + n) = 0;
    }
    else
    {
      *(int *)((char *)&g_RoleSlotBuf.m_nAnimCopy3 + n) = v34;
    }
  }
  *(_QWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat.m_nCCBUISelectedRole = 0;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_nCCBUIIdx + 1) = 0;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 6) = 0;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 14) = 0;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 22) = 0;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 30) = 0;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 38) = 0;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 46) = 0x140B500000000i64;
  *(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 54) = 1;
  *(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 58) = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(82101);
  pRoleTriple[0] = 4301;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(4301);
  v35 = (char *)g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    (((Array *)&g_nSceneFlags))->Array::Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v35) / 12);
    for ( ii = g_nSceneFlags.m_pData; v35 != ii; v43[2] = pRoleTriple[2] )
    {
      v43 = (_DWORD *)v35;
      v35 += 12;
      *v43 = pRoleTriple[0];
      v43[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v36 = (((Array *)&g_nSceneFlags))->Array::Size();
    else
      v36 = 1;
    v37 = (((Array *)&g_nSceneFlags))->Array::Size();
    v12 = v36 + v37 < 0;
    v38 = v36 + v37;
    v39 = v36 + v37;
    if ( v12 )
      v39 = 0;
    v40 = (char *)operator new(12 * v39);
    pNewBuffer = (((Array *)&g_nSceneFlags))->Array::Insert((void *)g_nSceneFlags.m_nSize, v35);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_nSceneFlags))->Array::Insert(v35, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v40[12 * v38];
    v41 = (((Array *)&g_nSceneFlags))->Array::Size();
    g_nSceneFlags.m_nSize = (int)v40;
    g_nSceneFlags.m_pData = ((char *)(&v40[12 * v41 + 12]));
  }
  pRoleTriple[0] = 4302;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(4302);
  v44 = (char *)g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    (((Array *)&g_nSceneFlags))->Array::Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v44) / 12);
    for ( jj = g_nSceneFlags.m_pData; v44 != jj; v52[2] = pRoleTriple[2] )
    {
      v52 = (_DWORD *)v44;
      v44 += 12;
      *v52 = pRoleTriple[0];
      v52[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v45 = (((Array *)&g_nSceneFlags))->Array::Size();
    else
      v45 = 1;
    v46 = (((Array *)&g_nSceneFlags))->Array::Size();
    v12 = v45 + v46 < 0;
    v47 = v45 + v46;
    v48 = v45 + v46;
    if ( v12 )
      v48 = 0;
    v49 = (char *)operator new(12 * v48);
    pNewBuffer = (((Array *)&g_nSceneFlags))->Array::Insert((void *)g_nSceneFlags.m_nSize, v44);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_nSceneFlags))->Array::Insert(v44, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v49[12 * v47];
    v50 = (((Array *)&g_nSceneFlags))->Array::Size();
    g_nSceneFlags.m_nSize = (int)v49;
    g_nSceneFlags.m_pData = ((char *)(&v49[12 * v50 + 12]));
  }
  pRoleTriple[0] = 311;
  pRoleTriple[1] = SUBGROUP_FLAG_MASK;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(311);
  v53 = (char *)g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    (((Array *)&g_nSceneFlags))->Array::Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v53) / 12);
    for ( kk = g_nSceneFlags.m_pData; v53 != kk; v61[2] = pRoleTriple[2] )
    {
      v61 = (_DWORD *)v53;
      v53 += 12;
      *v61 = pRoleTriple[0];
      v61[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v54 = (((Array *)&g_nSceneFlags))->Array::Size();
    else
      v54 = 1;
    v55 = (((Array *)&g_nSceneFlags))->Array::Size();
    v12 = v54 + v55 < 0;
    v56 = v54 + v55;
    v57 = v54 + v55;
    if ( v12 )
      v57 = 0;
    v58 = (char *)operator new(12 * v57);
    pNewBuffer = (((Array *)&g_nSceneFlags))->Array::Insert((void *)g_nSceneFlags.m_nSize, v53);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_nSceneFlags))->Array::Insert(v53, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v58[12 * v56];
    v59 = (((Array *)&g_nSceneFlags))->Array::Size();
    g_nSceneFlags.m_nSize = (int)v58;
    g_nSceneFlags.m_pData = ((char *)(&v58[12 * v59 + 12]));
  }
  pRoleTriple[0] = 312;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(312);
  v62 = (char *)g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    (((Array *)&g_nSceneFlags))->Array::Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v62) / 12);
    for ( mm = g_nSceneFlags.m_pData; v62 != mm; v70[2] = pRoleTriple[2] )
    {
      v70 = (_DWORD *)v62;
      v62 += 12;
      *v70 = pRoleTriple[0];
      v70[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v63 = (((Array *)&g_nSceneFlags))->Array::Size();
    else
      v63 = 1;
    v64 = (((Array *)&g_nSceneFlags))->Array::Size();
    v12 = v63 + v64 < 0;
    v65 = v63 + v64;
    v66 = v63 + v64;
    if ( v12 )
      v66 = 0;
    v67 = (char *)operator new(12 * v66);
    pNewBuffer = (((Array *)&g_nSceneFlags))->Array::Insert((void *)g_nSceneFlags.m_nSize, v62);
    (((Array *)&g_nSceneFlags))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_nSceneFlags))->Array::Insert(v62, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v67[12 * v65];
    v68 = (((Array *)&g_nSceneFlags))->Array::Size();
    g_nSceneFlags.m_nSize = (int)v67;
    g_nSceneFlags.m_pData = ((char *)(&v67[12 * v68 + 12]));
  }
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 94) = 14;
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 121) = 5594;
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 95) = Role::CalcXueJianInit(2, 14);
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 96) = Role::CalcLongKuiInit(
                                                           2,
                                                           *((int *)&g_RoleSlotBuf.m_teamSlotsB.combat + 94));
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 97) = Role::CalcZiXuanInit(
                                                           2,
                                                           *((int *)&g_RoleSlotBuf.m_teamSlotsB.combat + 94));
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 98) = Role::CalcChangQingInit(
                                                           2,
                                                           *((int *)&g_RoleSlotBuf.m_teamSlotsB.combat + 94));
  v71 = Role::CalcHuaYingInit(2, *((int *)&g_RoleSlotBuf.m_teamSlotsB.combat + 94));
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 146) = 0x600000003i64;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 52) = 0x600000003i64;
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 99) = v71;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 130) = 0x500000004i64;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 50) = 0x500000004i64;
  *(_QWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 138) = 0x200000004i64;
  *((_QWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 51) = 0x200000004i64;
  *(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 154) = 5;
  *((_DWORD *)&g_RoleSlotBuf.m_teamSlotsB.combat + 106) = 5;
  (((RoleSystem *)((char *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state + 1132)))->RoleSystem::RecalcAggregatedStats(1);
  for ( nn = 243; nn < 255; ++nn )
  {
    v73 = (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0];
    v74 = (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0];
    if ( v73 < v74 )
    {
      if ( v73 <= 0 )
        (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = 0;
    }
    else
    {
      (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = v74;
    }
  }
  g_RoleSlotBuf.m_teamData3[81] = 0;
  g_RoleSlotBuf.m_teamData3[82] = 0;
  g_RoleSlotBuf.m_teamData3[83] = 0;
  g_RoleSlotBuf.m_teamData3[84] = 0;
  g_RoleSlotBuf.m_teamData3[85] = 0;
  g_RoleSlotBuf.m_teamData3[86] = 0;
  g_RoleSlotBuf.m_teamData3[87] = 0;
  g_RoleSlotBuf.m_teamData3[88] = 0;
  g_RoleSlotBuf.m_teamData3[89] = 0;
  g_RoleSlotBuf.m_teamData3[90] = 0;
  g_RoleSlotBuf.m_teamData3[91] = 0;
  g_RoleSlotBuf.m_teamData3[92] = 0;
  g_RoleSlotBuf.m_teamData3[93] = 0;
  g_RoleSlotBuf.m_teamData3[94] = 0;
  g_RoleSlotBuf.m_teamData3[95] = 0;
  g_RoleSlotBuf.m_teamData3[96] = 82301;
  g_RoleSlotBuf.m_teamData3[97] = 1;
  g_RoleSlotBuf.m_teamData3[98] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(82301);
  pRoleTriple[0] = 4401;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(4401);
  v75 = (char *)g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    (((Array *)&g_SceneArray))->Array::Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    (((Array *)&g_SceneArray))->Array::Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v75) / 12);
    for ( i1 = g_SceneArray.m_pData; v75 != i1; v83[2] = pRoleTriple[2] )
    {
      v83 = (_DWORD *)v75;
      v75 += 12;
      *v83 = pRoleTriple[0];
      v83[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v76 = (((Array *)&g_SceneArray))->Array::Size();
    else
      v76 = 1;
    v77 = (((Array *)&g_SceneArray))->Array::Size();
    v12 = v76 + v77 < 0;
    v78 = v76 + v77;
    v79 = v76 + v77;
    if ( v12 )
      v79 = 0;
    v80 = (char *)operator new(12 * v79);
    pNewBuffer = (((Array *)&g_SceneArray))->Array::Insert((void *)g_SceneArray.m_nSize, v75);
    (((Array *)&g_SceneArray))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_SceneArray))->Array::Insert(v75, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v80[12 * v78];
    v81 = (((Array *)&g_SceneArray))->Array::Size();
    g_SceneArray.m_nSize = (int)v80;
    g_SceneArray.m_pData = ((char *)(&v80[12 * v81 + 12]));
  }
  pRoleTriple[0] = 316;
  pRoleTriple[1] = SUBGROUP_FLAG_MASK;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(316);
  v84 = (char *)g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    (((Array *)&g_SceneArray))->Array::Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    (((Array *)&g_SceneArray))->Array::Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v84) / 12);
    for ( i2 = g_SceneArray.m_pData; v84 != i2; v92[2] = pRoleTriple[2] )
    {
      v92 = (_DWORD *)v84;
      v84 += 12;
      *v92 = pRoleTriple[0];
      v92[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v85 = (int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12;
    else
      v85 = 1;
    v86 = (((Array *)&g_SceneArray))->Array::Size();
    v12 = v85 + v86 < 0;
    v87 = v85 + v86;
    v88 = v85 + v86;
    if ( v12 )
      v88 = 0;
    v89 = (char *)operator new(12 * v88);
    pNewBuffer = (((Array *)&g_SceneArray))->Array::Insert((void *)g_SceneArray.m_nSize, v84);
    (((Array *)&g_SceneArray))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_SceneArray))->Array::Insert(v84, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v89[12 * v87];
    v90 = (((Array *)&g_SceneArray))->Array::Size();
    g_SceneArray.m_nSize = (int)v89;
    g_SceneArray.m_pData = ((char *)(&v89[12 * v90 + 12]));
  }
  pRoleTriple[0] = 317;
  pRoleTriple[1] = SUBGROUP_FLAG_ALT;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(317);
  v93 = (char *)g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    (((Array *)&g_SceneArray))->Array::Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    (((Array *)&g_SceneArray))->Array::Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v93) / 12);
    for ( i3 = g_SceneArray.m_pData; v93 != i3; v101[2] = pRoleTriple[2] )
    {
      v101 = (_DWORD *)v93;
      v93 += 12;
      *v101 = pRoleTriple[0];
      v101[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v94 = (int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12;
    else
      v94 = 1;
    v95 = (((Array *)&g_SceneArray))->Array::Size();
    v12 = v94 + v95 < 0;
    v96 = v94 + v95;
    v97 = v94 + v95;
    if ( v12 )
      v97 = 0;
    v98 = (char *)operator new(12 * v97);
    pNewBuffer = (((Array *)&g_SceneArray))->Array::Insert((void *)g_SceneArray.m_nSize, v93);
    (((Array *)&g_SceneArray))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_SceneArray))->Array::Insert(v93, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v98[12 * v96];
    v99 = (((Array *)&g_SceneArray))->Array::Size();
    g_SceneArray.m_nSize = (int)v98;
    g_SceneArray.m_pData = ((char *)(&v98[12 * v99 + 12]));
  }
  pRoleTriple[0] = 318;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(318);
  v102 = (char *)g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    (((Array *)&g_SceneArray))->Array::Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    (((Array *)&g_SceneArray))->Array::Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v102) / 12);
    for ( i4 = g_SceneArray.m_pData; v102 != i4; v110[2] = pRoleTriple[2] )
    {
      v110 = (_DWORD *)v102;
      v102 += 12;
      *v110 = pRoleTriple[0];
      v110[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v103 = (int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12;
    else
      v103 = 1;
    v104 = (((Array *)&g_SceneArray))->Array::Size();
    v12 = v103 + v104 < 0;
    v105 = v103 + v104;
    v106 = v103 + v104;
    if ( v12 )
      v106 = 0;
    v107 = (char *)operator new(12 * v106);
    pNewBuffer = (((Array *)&g_SceneArray))->Array::Insert((void *)g_SceneArray.m_nSize, v102);
    (((Array *)&g_SceneArray))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_SceneArray))->Array::Insert(v102, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v107[12 * v105];
    v108 = (((Array *)&g_SceneArray))->Array::Size();
    g_SceneArray.m_nSize = (int)v107;
    g_SceneArray.m_pData = ((char *)(&v107[12 * v108 + 12]));
  }
  g_RoleSlotBuf.m_teamData3[26] = 10;
  g_RoleSlotBuf.m_teamData3[53] = 1943;
  g_RoleSlotBuf.m_teamData3[27] = Role::CalcXueJianInit(3, 10);
  g_RoleSlotBuf.m_teamData3[28] = Role::CalcLongKuiInit(3, g_RoleSlotBuf.m_teamData3[26]);
  g_RoleSlotBuf.m_teamData3[29] = Role::CalcZiXuanInit(3, g_RoleSlotBuf.m_teamData3[26]);
  g_RoleSlotBuf.m_teamData3[30] = Role::CalcChangQingInit(3, g_RoleSlotBuf.m_teamData3[26]);
  g_RoleSlotBuf.m_teamData3[31] = Role::CalcHuaYingInit(3, g_RoleSlotBuf.m_teamData3[26]);
  v111 = 1;
  g_RoleSlotBuf.m_teamData3[118] = 6;
  g_RoleSlotBuf.m_teamData3[34] = 6;
  g_RoleSlotBuf.m_teamData3[116] = 4;
  g_RoleSlotBuf.m_teamData3[32] = 4;
  g_RoleSlotBuf.m_teamData3[117] = 1;
  g_RoleSlotBuf.m_teamData3[33] = 1;
  g_RoleSlotBuf.m_teamData3[119] = 3;
  g_RoleSlotBuf.m_teamData3[35] = 3;
  g_RoleSlotBuf.m_teamData3[120] = 4;
  g_RoleSlotBuf.m_teamData3[36] = 4;
  g_RoleSlotBuf.m_teamData3[121] = 3;
  g_RoleSlotBuf.m_teamData3[37] = 3;
  g_RoleSlotBuf.m_teamData3[122] = 2;
  g_RoleSlotBuf.m_teamData3[38] = 2;
  (((RoleSystem *)&g_RoleSlotBuf.m_configData[32]))->RoleSystem::RecalcAggregatedStats(1);
  for ( i5 = 243; i5 < 255; ++i5 )
  {
    v113 = g_RoleSlotBuf.m_configData[i5 + 32];
    v114 = g_RoleSlotBuf.m_configData[i5 + 20];
    if ( v113 < v114 )
    {
      if ( v113 <= 0 )
        g_RoleSlotBuf.m_configData[i5 + 32] = 0;
    }
    else
    {
      g_RoleSlotBuf.m_configData[i5 + 32] = v114;
    }
  }
  g_RoleSlotBuf.m_teamData3[433] = 0;
  g_RoleSlotBuf.m_teamData3[434] = 0;
  g_RoleSlotBuf.m_teamData3[435] = 0;
  g_RoleSlotBuf.m_teamData3[436] = 0;
  g_RoleSlotBuf.m_teamData3[437] = 0;
  g_RoleSlotBuf.dword_17AA450 = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 1) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 2) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 3) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 4) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 5) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 6) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 7) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 8) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 9) = 0;
  *(&g_RoleSlotBuf.dword_17AA450 + 10) = 82001;
  *(&g_RoleSlotBuf.dword_17AA450 + 11) = 1;
  *(&g_RoleSlotBuf.dword_17AA450 + 12) = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(82001);
  pRoleTriple[0] = 4501;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(4501);
  v115 = (char *)pEnd;
  if ( ((char *)g_SceneMgr.m_pAlphaEffect2 - (_BYTE *)pEnd) / 12 )
  {
    (((Array *)&g_SceneMgr))->Array::Insert(pEnd, pEnd);
    (((Array *)&g_SceneMgr))->Array::Erase((int)pEnd, 1 - ((_BYTE *)pEnd - v115) / 12);
    v121 = (char *)pEnd;
    if ( v115 != pEnd )
    {
      do
      {
        v122 = (_DWORD *)v115;
        v115 += 12;
        *v122 = pRoleTriple[0];
        v122[1] = pRoleTriple[1];
        v122[2] = pRoleTriple[2];
      }
      while ( v115 != v121 );
    }
    pEnd = (char *)pEnd + 12;
  }
  else
  {
    if ( !pElem )
      goto LABEL_148;
    if ( (unsigned int)(((_BYTE *)pEnd - (_BYTE *)pElem) / 12) > 1 )
      v111 = ((_BYTE *)pEnd - (_BYTE *)pElem) / 12;
    if ( pElem )
      v116 = ((_BYTE *)pEnd - (_BYTE *)pElem) / 12;
    else
LABEL_148:
      v116 = 0;
    v117 = v116 + v111;
    v118 = v116 + v111;
    if ( v116 + v111 < 0 )
      v118 = 0;
    v119 = (gbVec3D *)operator new(12 * v118);
    pNewBuffer = (((Array *)&g_SceneMgr))->Array::Insert(pElem, v115);
    (((Array *)&g_SceneMgr))->Array::Erase((int)pNewBuffer, 1);
    (((Array *)&g_SceneMgr))->Array::Insert(v115, pEnd);
    nullsub_2(pElem, pEnd);
    operator delete(pElem);
    g_SceneMgr.m_pAlphaEffect2 = ((gbRenderEffect *)((int *)&v119[v117]));
    if ( pElem )
      v120 = ((_BYTE *)pEnd - (_BYTE *)pElem) / 12;
    else
      v120 = 0;
    pElem = v119;
    pEnd = &v119[v120 + 1];
  }
  pRoleTriple[0] = 306;
  pRoleTriple[1] = SUBGROUP_FLAG_MASK;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(306);
  v123 = (gbVec3D *)pEnd;
  if ( ((char *)g_SceneMgr.m_pAlphaEffect2 - (_BYTE *)pEnd) / 12 )
  {
    (((Array *)&g_SceneMgr))->Array::Insert(pEnd, pEnd);
    (((Array *)&g_SceneMgr))->Array::Erase((int)pEnd, 1 - ((_BYTE *)pEnd - (_BYTE *)v123) / 12);
    v131 = (gbVec3D *)pEnd;
    if ( v123 != pEnd )
    {
      do
      {
        p_x = (_DWORD *)&v123->x;
        ++v123;
        *p_x = pRoleTriple[0];
        p_x[1] = pRoleTriple[1];
        p_x[2] = pRoleTriple[2];
      }
      while ( v123 != v131 );
    }
    pEnd = (char *)pEnd + 12;
  }
  else
  {
    if ( pElem && (unsigned int)(((_BYTE *)pEnd - (_BYTE *)pElem) / 12) > 1 )
      v124 = ((_BYTE *)pEnd - (_BYTE *)pElem) / 12;
    else
      v124 = 1;
    if ( pElem )
      v125 = ((_BYTE *)pEnd - (_BYTE *)pElem) / 12;
    else
      v125 = 0;
    v126 = v125 + v124;
    pNewBuffer = v125 + v124;
    if ( v125 + v124 < 0 )
      v126 = 0;
    v127 = (gbVec3D *)operator new(12 * v126);
    v128 = pElem;
    pSceneName = (void *)v127;
    for ( i6 = v127; v128 != v123; ++i6 )
    {
      Array::Copy(i6);
      ++v128;
    }
    (((Array *)&g_SceneMgr))->Array::Erase((int)i6, 1);
    (((Array *)&g_SceneMgr))->Array::Insert(v123, pEnd);
    nullsub_2(pElem, pEnd);
    operator delete(pElem);
    g_SceneMgr.m_pAlphaEffect2 = ((gbRenderEffect *)((int *)&pSceneName[pNewBuffer]));
    v130 = (((Array *)&g_SceneMgr))->Array::Size();
    pElem = pSceneName;
    pEnd = &pSceneName[v130 + 1];
  }
  pRoleTriple[0] = 307;
  pRoleTriple[1] = SUBGROUP_FLAG_ALT;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(307);
  v133 = (gbVec3D *)pEnd;
  if ( ((char *)g_SceneMgr.m_pAlphaEffect2 - (_BYTE *)pEnd) / 12 )
  {
    (((Array *)&g_SceneMgr))->Array::Insert(pEnd, pEnd);
    (((Array *)&g_SceneMgr))->Array::Erase((int)pEnd, 1 - ((_BYTE *)pEnd - (_BYTE *)v133) / 12);
    v141 = (gbVec3D *)pEnd;
    if ( v133 != pEnd )
    {
      do
      {
        v142 = (_DWORD *)&v133->x;
        ++v133;
        *v142 = pRoleTriple[0];
        v142[1] = pRoleTriple[1];
        v142[2] = pRoleTriple[2];
      }
      while ( v133 != v141 );
    }
    pEnd = (char *)pEnd + 12;
  }
  else
  {
    if ( pElem && (unsigned int)(((_BYTE *)pEnd - (_BYTE *)pElem) / 12) > 1 )
      v134 = ((_BYTE *)pEnd - (_BYTE *)pElem) / 12;
    else
      v134 = 1;
    if ( pElem )
      v135 = ((_BYTE *)pEnd - (_BYTE *)pElem) / 12;
    else
      v135 = 0;
    v136 = v135 + v134;
    pSceneName = v135 + v134;
    if ( v135 + v134 < 0 )
      v136 = 0;
    v137 = (gbVec3D *)operator new(12 * v136);
    v138 = pElem;
    pNewBuffer = (void *)v137;
    for ( i7 = v137; v138 != v133; ++i7 )
    {
      Array::Copy(i7);
      ++v138;
    }
    (((Array *)&g_SceneMgr))->Array::Erase((int)i7, 1);
    (((Array *)&g_SceneMgr))->Array::Insert(v133, pEnd);
    nullsub_2(pElem, pEnd);
    operator delete(pElem);
    g_SceneMgr.m_pAlphaEffect2 = ((gbRenderEffect *)((int *)&pNewBuffer[pSceneName]));
    v140 = (((Array *)&g_SceneMgr))->Array::Size();
    pElem = pNewBuffer;
    pEnd = &pNewBuffer[v140 + 1];
  }
  pRoleTriple[0] = 308;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(308);
  (((Scene *)&g_SceneMgr))->Scene::AddRoleEntry(pRoleTriple);
  g_RoleSlotBuf.m_teamData3[405] = 4341;
  g_RoleSlotBuf.m_teamData3[378] = 13;
  g_RoleSlotBuf.m_teamData3[379] = Role::CalcXueJianInit(4, 13);
  g_RoleSlotBuf.m_teamData3[380] = Role::CalcLongKuiInit(4, g_RoleSlotBuf.m_teamData3[378]);
  g_RoleSlotBuf.m_teamData3[381] = Role::CalcZiXuanInit(4, g_RoleSlotBuf.m_teamData3[378]);
  g_RoleSlotBuf.m_teamData3[382] = Role::CalcChangQingInit(4, g_RoleSlotBuf.m_teamData3[378]);
  g_RoleSlotBuf.m_teamData3[383] = Role::CalcHuaYingInit(4, g_RoleSlotBuf.m_teamData3[378]);
  *(&g_RoleSlotBuf.dword_17AA450 + 33) = 4;
  g_RoleSlotBuf.m_teamData3[387] = 4;
  *(&g_RoleSlotBuf.dword_17AA450 + 32) = 1;
  g_RoleSlotBuf.m_teamData3[386] = 1;
  *(&g_RoleSlotBuf.dword_17AA450 + 30) = 3;
  g_RoleSlotBuf.m_teamData3[384] = 3;
  *(&g_RoleSlotBuf.dword_17AA450 + 31) = 3;
  g_RoleSlotBuf.m_teamData3[385] = 3;
  *(&g_RoleSlotBuf.dword_17AA450 + 34) = 3;
  g_RoleSlotBuf.m_teamData3[388] = 3;
  *(&g_RoleSlotBuf.dword_17AA450 + 35) = 2;
  g_RoleSlotBuf.m_teamData3[389] = 2;
  *(&g_RoleSlotBuf.dword_17AA450 + 36) = 2;
  g_RoleSlotBuf.m_teamData3[390] = 2;
  (((RoleSystem *)&g_RoleSlotBuf.m_teamData3[220]))->RoleSystem::RecalcAggregatedStats(1);
  (((RoleSystem *)&g_RoleSlotBuf.m_teamData3[220]))->RoleSystem::Init();
  dword_C10BA0 = 4101;
  dword_C10BA4 = -1;
  dword_C10BA8 = 4102;
  dword_C10BAC = 4;
  dword_C10BB0 = 4103;
  dword_C10BB4 = -1;
  dword_C10BB8 = 4104;
  dword_C10BBC = -1;
  dword_C10BC0 = 4105;
  dword_C10BC4 = 44;
  dword_C10BC8 = 4106;
  dword_C10BCC = -1;
  dword_C10BD0 = 4201;
  dword_C10BD4 = -1;
  dword_C10BD8 = 4202;
  dword_C10BDC = 15;
  dword_C10BFC = -1;
  dword_C10C04 = 3;
  dword_C10C14 = 15;
  dword_C10C24 = -1;
  dword_C10C2C = -1;
  dword_C10C3C = -1;
  dword_C10C5C = -1;
  dword_C10C8C = -1;
  dword_C10C44 = 13;
  memset(&g_palScript.m_nItemCheck, 0, 0x190u);
  dword_C10BE0 = 4203;
  dword_C10BE4 = 20;
  dword_C10BE8 = 4204;
  dword_C10BEC = 55;
  dword_C10BF0 = 4205;
  dword_C10BF4 = 50;
  dword_C10BF8 = 0;
  dword_C10C00 = 4301;
  dword_C10C08 = 4302;
  dword_C10C0C = 10;
  dword_C10C10 = 4303;
  dword_C10C18 = 4304;
  dword_C10C1C = 20;
  dword_C10C20 = 4305;
  dword_C10C28 = 0;
  dword_C10C30 = 4401;
  dword_C10C34 = 4;
  dword_C10C38 = 4402;
  dword_C10C40 = 4403;
  dword_C10C48 = 4404;
  dword_C10C4C = 35;
  dword_C10C50 = 4405;
  dword_C10C54 = 58;
  dword_C10C58 = 0;
  dword_C10C60 = 4501;
  dword_C10C64 = 8;
  dword_C10C68 = 4502;
  dword_C10C6C = 24;
  dword_C10C70 = 4503;
  dword_C10C74 = 38;
  dword_C10C78 = 4504;
  dword_C10C7C = 50;
  dword_C10C80 = 4505;
  dword_C10C84 = 64;
  dword_C10C88 = 0;
  g_palScript.m_nItemCheck = 301;
  dword_C10A1C = 0;
  g_palScript.m_RoleEmoteData = 45;
  dword_C10A20 = 302;
  g_palScript.m_pTexture = ((gbTexture *)4);
  dword_C10A28 = 45;
  g_palScript.m_pTextureInfo = ((_PlugInfo *)303);
  g_palScript.m_RoleEmoteSub = 5;
  dword_C10A38 = 15;
  g_palScript.m_nTodo_0D8 = 304;
  dword_C10A4C = 20;
  dword_C10A48 = 50;
  dword_C10A50 = 305;
  g_palScript.m_bSoundType = 30;
  g_palScript.m_bCamActive = 60;
  g_palScript.m_fCamScale = 321;
  *(_DWORD *)&g_palScript.m_WaitObjList = 0;
  g_palScript.m_nUpdateState = 45;
  g_palScript.m_WaitObjList.capacity = 322;
  g_palScript.m_fRenderScaleX = 5;
  g_palScript.m_WaitObjList.m_needscriptdel = 30;
  g_palScript.m_fScaleY = 323;
  g_palScript.m_fInterval = 14;
  dword_C10A88 = 15;
  g_palScript.m_fElapsed = 324;
  dword_C10A9C = 23;
  dword_C10A98 = 45;
  g_palScript.m_nTodo_138 = 325;
  dword_C10B28 = 30;
  dword_C10AAC = 32;
  dword_C10AA8 = 50;
  dword_C10AB0 = 311;
  dword_C10ABC = 0;
  dword_C10AB8 = 45;
  dword_C10AC0 = 312;
  dword_C10ACC = 5;
  g_palScript.m_EncampConfig = 45;
  dword_C10AD0 = 313;
  g_palScript.m_nMaxRepeats = 15;
  g_palScript.m_nRepeatCount = 15;
  g_palScript.m_nCycleCount = 314;
  dword_C10AEC = 25;
  dword_C10AE8 = 45;
  dword_C10AF0 = 315;
  dword_C10AFC = 35;
  dword_C10AF8 = 60;
  dword_C10B00 = 316;
  dword_C10B0C = 0;
  dword_C10B08 = 45;
  dword_C10B10 = 317;
  dword_C10B1C = 3;
  dword_C10B18 = 15;
  dword_C10B20 = 318;
  dword_C10B2C = 10;
  dword_C10B30 = 319;
  dword_C10B3C = 20;
  dword_C10B38 = 45;
  dword_C10B40 = 320;
  dword_C10B4C = 28;
  dword_C10B48 = 20;
  dword_C10B50 = 306;
  dword_C10B5C = 0;
  dword_C10B58 = 45;
  dword_C10B60 = 307;
  dword_C10B6C = 6;
  dword_C10B68 = 15;
  dword_C10B70 = 308;
  dword_C10B7C = 14;
  dword_C10B78 = 45;
  dword_C10B80 = 309;
  dword_C10B8C = 22;
  dword_C10B88 = 50;
  dword_C10B90 = 310;
  dword_C10B9C = 32;
  dword_C10B98 = 60;
  NPC::InitAll();
  for ( i8 = 0; i8 < 5; ++i8 )
  {
    result = 1408 * i8;
    *((_BYTE *)&g_RoleSlotBuf.m_nAnimCopy1 + result + 1) = 0;
    *((_BYTE *)&g_RoleSlotBuf.m_nAnimCopy1 + result + 2) = 0;
    *((_BYTE *)&g_RoleSlotBuf.m_nAnimCopy1 + result + 3) = 0;
    *((_BYTE *)&g_RoleSlotBuf.m_nAnimCopy2 + result) = 0;
    *((_BYTE *)&g_RoleSlotBuf.m_nAnimCopy2 + result + 1) = 1;
    *((_BYTE *)&g_RoleSlotBuf.m_nAnimCopy1 + result) = 0;
    switch ( i8 )
    {
      case 0:
        *((_DWORD *)((UIWnd *)&g_RoleSlotBuf) + 352 * i8) = 101;
        break;
      case 1:
        *((_DWORD *)((UIWnd *)&g_RoleSlotBuf) + 352 * i8) = 104;
        break;
      case 2:
        *((_DWORD *)((UIWnd *)&g_RoleSlotBuf) + 352 * i8) = 106;
        break;
      case 3:
        *((_DWORD *)((UIWnd *)&g_RoleSlotBuf) + 352 * i8) = 107;
        break;
      case 4:
        *((_DWORD *)((UIWnd *)&g_RoleSlotBuf) + 352 * i8) = 102;
        break;
      default:
        continue;
    }
  }
  g_nMagicSlotCountA = MAGIC_SLOT_INIT;
  g_nMagicSlotCountB = MAGIC_SLOT_INIT;
  return result;
}

// 0x004118D0
int PAL3::UpdateSubsystems()
{
  int nVal; // [esp+0x4] [ebp+0x4]
  int nVal2; // [esp+0x8] [ebp+0x8]
  int nVal3; // [esp+0xC] [ebp+0xC]

  return PAL3::RandomPickValues(nVal, nVal2, nVal3);
}

// 0x0041EE40
int PAL3::UIPostProcess()
{
  int result; // eax

  if ( g_pCurrentBGM )
  {
    (((gbSound2DNode *)g_pCurrentBGM))->gbSound2DNode::Stop();
    g_pCurrentBGM = 0;
  }
  return result;
}

// 0x0041F9F0
void PAL3::LoadingTimerCallback()
{
  DWORD Time; // eax

  float DeltaTime; // [esp+0x4] [ebp-0x4]

  Time = timeGetTime();
  if ( Time - g_lastupdateloading >= 0x32 )
  {
    g_lastupdateloading = Time;
    if ( g_nsub_41FA90_DC10FC )
    {
      (((UIScrollBar *)(g_nsub_41FA90_DC10FC + 72)))->UIScrollBar::SetRange(1.0);
      (((UIProgressBar *)(g_nsub_41FA90_DC10FC + 72)))->UIProgressBar::FindChildByName(*(float *)&g_nLastUpdateTime);
      DeltaTime = (((gbGfxManager *)gfxMgr))->gbGfxManager::GetDeltaTime();
      (*(void ( **)(int, _DWORD, int))(*(_DWORD *)g_nsub_41FA90_DC10FC + 8))(
        g_nsub_41FA90_DC10FC,
        LODWORD(DeltaTime),
        1);
      this->PAL3::Render();
    }
  }
}

// 0x00437E60
bool PAL3::WriteRegistryValue(CHAR *lpSubKey, DWORD dwDisposition, ...)
{
  CHAR *v2; // esi
  bool result; // al
  const CHAR *v4; // edi
  char v5; // al
  const char *v6; // eax
  const char *v7; // eax
  va_list Data; // [esp+0x18] [ebp+0xC] BYREF

  va_start(Data, dwDisposition);
  v2 = lpSubKey;
  if ( !lpSubKey )
    return 0;
  v4 = (const CHAR *)dwDisposition;
  if ( !dwDisposition )
    return 0;
  dwDisposition = 1;
  PAL3::StartWolf(HKEY_LOCAL_MACHINE, lpSubKey);
  if ( !v5 )
  {
    v6 = (const char *)RegCreateKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0, 0, 0xF003Fu, 0, (PHKEY)&lpSubKey, &dwDisposition);
    result = ShowMessageBox(v6, szCaption);
    if ( !result )
      return result;
    RegCloseKey((HKEY)lpSubKey);
  }
  RegOpenKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0x20006u, (PHKEY)&lpSubKey);
  v7 = (const char *)RegSetValueExA((HKEY)lpSubKey, v4, 0, 4u, (const BYTE *)Data, 4u);
  result = ShowMessageBox(v7, "Write Reg Error");
  if ( result )
  {
    RegCloseKey((HKEY)lpSubKey);
    return 1;
  }
  return result;
}

// 0x0044E2B0
bool PAL3::WriteRegistryDword(CHAR *lpSubKey, const CHAR *szValueName, ...)
{
  CHAR *v2; // esi
  bool result; // al
  const CHAR *v4; // edi
  char v5; // al
  const char *Key; // eax
  const char *v7; // eax
  va_list Data; // [esp+0x18] [ebp+0xC] BYREF

  va_start(Data, szValueName);
  v2 = lpSubKey;
  if ( !lpSubKey )
    return 0;
  v4 = szValueName;
  if ( !szValueName )
    return 0;
  szValueName = (const CHAR *)1;
  PAL3::StartWolf(HKEY_LOCAL_MACHINE, lpSubKey);
  if ( !v5 )
  {
    Key = (const char *)RegCreateKeyExA(
                          HKEY_LOCAL_MACHINE,
                          v2,
                          0,
                          0,
                          0,
                          0xF003Fu,
                          0,
                          (PHKEY)&lpSubKey,
                          (LPDWORD)&szValueName);
    result = ShowMessageBox(Key, szCaption);
    if ( !result )
      return result;
    RegCloseKey((HKEY)lpSubKey);
  }
  RegOpenKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0x20006u, (PHKEY)&lpSubKey);
  v7 = (const char *)RegSetValueExA((HKEY)lpSubKey, v4, 0, 4u, (const BYTE *)Data, 4u);
  result = ShowMessageBox(v7, "Write Reg Error");
  if ( result )
  {
    RegCloseKey((HKEY)lpSubKey);
    return 1;
  }
  return result;
}

// 0x0044E390
void PAL3::LoadRoleByIndex(int nVal)
{
  PAL3 *v1; // ecx
  int v2; // edi
  int v3; // esi
  int i; // ecx
  int v5; // eax
  int v6; // ecx
  unsigned __int8 *v7; // eax

  if ( nVal < 52 )
  {
    (((PAL3 *)v1))->PAL3::LoadUnlockFlags();
    *((_BYTE *)&g_bRoleLoadFlags + nVal) = 1;
    v2 = 0;
    v3 = 0;
    for ( i = 0; i < 32; ++i )
      v2 |= *((unsigned __int8 *)&g_bRoleLoadFlags + i) << i;
    v5 = i;
    v6 = 0;
    v7 = (unsigned __int8 *)&g_bRoleLoadFlags + v5;
    do
    {
      v3 |= *v7++ << v6;
      if ( (int)v7 >= (int)&g_bGameUpdating )
        break;
      ++v6;
    }
    while ( v6 < 32 );
    PAL3::WriteRegistryDword(aSoftwareSoftst_2, ValueName, v2);
    PAL3::WriteRegistryDword(aSoftwareSoftst_2, "MOVIE_B", v3);
  }
}

// 0x0044E410
char * PAL3::LoadUnlockFlags()
{
  char *result; // eax
  int v2; // eax
  int i; // ecx
  int v4; // esi
  int v5; // eax
  int v6; // ecx
  BYTE Data[4]; // [esp+0x8] [ebp-0x8] BYREF
  BYTE v8[4]; // [esp+0xC] [ebp-0x4] BYREF

  memset(&g_bRoleLoadFlags, 0, 0x34u);
  *(_DWORD *)Data = 0;
  *(_DWORD *)v8 = 0;
  result = (char *)ReadRegistryString(aSoftwareSoftst_2, ValueName, (char *)Data);
  if ( (_BYTE)result )
  {
    result = (char *)ReadRegistryString(aSoftwareSoftst_2, "MOVIE_B", (char *)v8);
    if ( (_BYTE)result )
    {
      v2 = *(_DWORD *)Data;
      for ( i = 0; i < 32; ++i )
        *((_BYTE *)&g_bRoleLoadFlags + i) = ((1 << i) & v2) != 0;
      v4 = *(_DWORD *)v8;
      v5 = i;
      v6 = 0;
      result = (char *)&g_bRoleLoadFlags + v5;
      do
      {
        *result++ = ((1 << v6) & v4) != 0;
        if ( (int)result >= (int)&g_bGameUpdating )
          break;
        ++v6;
      }
      while ( v6 < 32 );
    }
  }
  return result;
}

// 0x00456590
bool PAL3::WriteRegistryKey(CHAR *lpSubKey, DWORD dwDisposition, ...)
{
  CHAR *v2; // esi
  bool result; // al
  const CHAR *v4; // edi
  char v5; // al
  const char *v6; // eax
  const char *v7; // eax
  va_list Data; // [esp+0x18] [ebp+0xC] BYREF

  va_start(Data, dwDisposition);
  v2 = lpSubKey;
  if ( !lpSubKey )
    return 0;
  v4 = (const CHAR *)dwDisposition;
  if ( !dwDisposition )
    return 0;
  dwDisposition = 1;
  PAL3::StartWolf(HKEY_LOCAL_MACHINE, lpSubKey);
  if ( !v5 )
  {
    v6 = (const char *)RegCreateKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0, 0, 0xF003Fu, 0, (PHKEY)&lpSubKey, &dwDisposition);
    result = ShowMessageBox(v6, szCaption);
    if ( !result )
      return result;
    RegCloseKey((HKEY)lpSubKey);
  }
  RegOpenKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0x20006u, (PHKEY)&lpSubKey);
  v7 = (const char *)RegSetValueExA((HKEY)lpSubKey, v4, 0, 4u, (const BYTE *)Data, 4u);
  result = ShowMessageBox(v7, "Write Reg Error");
  if ( result )
  {
    RegCloseKey((HKEY)lpSubKey);
    return 1;
  }
  return result;
}

// 0x00459860
char PAL3::HandleDeviceReset()
{
  PAL3 *Instance_db10; // eax
  float m_snaph; // ecx
  int v4; // eax
  PAL3 *v5; // eax
  gbTexture *ActiveTexture; // eax

  unsigned __int8 v8; // bl
  PAL3 *v9; // eax
  PAL3 *v10; // eax

  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(1);
  m_snaph = PAL3::GetInstance_db10()->m_snaph;
  v4 = 1061158912;
  if ( m_snaph != 0.0f )
    v4 = 1065353216;
  this->m_nTodo_CD0 = v4;
  this->m_nTodo_CCC = v4;
  v5 = (PAL3 *)PAL3::GetInstance_db10();
  LOBYTE(ActiveTexture) = (((RenderTarget *)v5))->RenderTarget::OnResetDevice(1);
  if ( (_BYTE)ActiveTexture )
  {
    v8 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    this->PAL3::Render();
    g_bGameFlag2 = v8;
    v9 = (PAL3 *)PAL3::GetInstance_db10();
    (((RenderTarget *)v9))->RenderTarget::RenderToScreen();
    this->m_pDeviceTex = ((gbTexture *)0);
    v10 = (PAL3 *)PAL3::GetInstance_db10();
    ActiveTexture = (((RenderTarget *)v10))->RenderTarget::GetActiveTexture();
    if ( ActiveTexture && *(_DWORD *)((gbRefObject *)&ActiveTexture[1]) )
      this->m_pDeviceTex = ((gbTexture *)(ActiveTexture));
  }
  else
  {
    this->m_pDeviceTex = ((gbTexture *)0);
  }
  return (char)ActiveTexture;
}

// 0x00461BF0
int PAL3::EnterGameMode(int nVal)
{
  int result; // eax

  (((SaleUI *)this))->SaleUI::DestroySubFrames() /* [ROWTABLE] */;
  UIFrameWnd_OnPaintUpdate(nVal);
  (((SaleUI *)this))->SaleUI::SetValue(0) /* [ROWTABLE] */;
  (((SaleUI *)this))->SaleUI::SetRange(1u) /* [ROWTABLE] */;
  (((SaleUI *)this))->SaleUI::SendInputToRole(1u) /* [ROWTABLE] */;
  sub_445E50((int)&this[20].m_gametime + 36);
  result = (((SaleUI *)this))->SaleUI::SetRange(1u) /* [ROWTABLE] */;
  *(&this[21].m_nTodo_894 + 3) = 0;
  return result;
}

// 0x00462030
int PAL3::SetPanelStates(unsigned __int8 pData)
{
  sub_445E50((int)(&this[20].m_nTodo_F9C + 182));
  sub_445E50((int)&this[21].m_Image2D.ImgInfo.hdiv[6]);
  sub_445E50((int)&this[21].m_gametime + 28);
  sub_445E50((int)&this[21].m_gametime + 372);
  return sub_445E50((int)&this[21].m_gametime + 716);
}

// 0x004B2840
bool PAL3::WriteRegistry(CHAR *lpSubKey, DWORD dwDisposition, ...)
{
  CHAR *v2; // esi
  bool result; // al
  const CHAR *v4; // edi
  char v5; // al
  const char *v6; // eax
  const char *v7; // eax
  va_list Data; // [esp+0x18] [ebp+0xC] BYREF

  va_start(Data, dwDisposition);
  v2 = lpSubKey;
  if ( !lpSubKey )
    return 0;
  v4 = (const CHAR *)dwDisposition;
  if ( !dwDisposition )
    return 0;
  dwDisposition = 1;
  PAL3::StartWolf(HKEY_LOCAL_MACHINE, lpSubKey);
  if ( !v5 )
  {
    v6 = (const char *)RegCreateKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0, 0, 0xF003Fu, 0, (PHKEY)&lpSubKey, &dwDisposition);
    result = ShowMessageBox(v6, szCaption);
    if ( !result )
      return result;
    RegCloseKey((HKEY)lpSubKey);
  }
  RegOpenKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0x20006u, (PHKEY)&lpSubKey);
  v7 = (const char *)RegSetValueExA((HKEY)lpSubKey, v4, 0, 4u, (const BYTE *)Data, 4u);
  result = ShowMessageBox(v7, "Write Reg Error");
  if ( result )
  {
    RegCloseKey((HKEY)lpSubKey);
    return 1;
  }
  return result;
}

// 0x004B6D30
RenderTarget3 * PAL3::GetInstance()
{
  if ( (*(_BYTE *)(&g_RenderTarget3.m_ptr_4 + 1) & 1) == 0 )
  {
    *((_BYTE *)&g_RenderTarget3.m_ptr_4 + 4) |= 1u;
    (((RenderTarget3 *)&g_RenderTarget3))->RenderTarget3::Reset();
    atexit(SingletonThunk_004B6D70);
  }
  return &g_RenderTarget3;
}

// 0x004BDA60
int * PAL3::CreateTextures()
{
  this->m_snaph = NAN;
  this->m_Image2D.PixelFmt.r_shift = 0;
  return (int *)this;
}

// 0x004BDB10
PAL3 * PAL3::GetInstance_db10()
{
  if ( (g_PAL3.m_Image2D.PixelFmt.g_shift & 1) == 0 )
  {
    LOBYTE(g_PAL3.m_Image2D.PixelFmt.g_shift) |= 1u;
    (((PAL3 *)&g_PAL3))->PAL3::CreateTextures();
    atexit(InitPal3Singleton);
  }
  return &g_PAL3;
}

// 0x004BDED0
void PAL3::InvalidateSnapH()
{
  this->m_snaph = NAN;
}

// 0x004BFD20
ScreenEffectMgr * PAL3::GetInstance_fd20()
{
  if ( (*(_BYTE *)(&g_PAL3.m_nTodo_F9C + 71) & 1) == 0 )
  {
    *((_BYTE *)&g_PAL3.m_nTodo_F9C + 284) |= 1u;
    (((ScreenEffectMgr *)(&g_PAL3.m_nTodo_F9C + 65)))->ScreenEffectMgr::ResetFadeState();
    atexit(SingletonThunk_004BFD60);
  }
  return (ScreenEffectMgr *)(&g_PAL3.m_nTodo_F9C + 65);
}

// 0x004C0400
void PAL3::ClearAdditiveEffects()
{
  gbRenderEffect *m_pAdditiveEffect; // eax
  gbTexture *m_pScnFrameTex; // eax
  gbRenderEffect *m_pAdditiveEffect2; // eax

  m_pAdditiveEffect = (gbRenderEffect *)this->m_pAdditiveEffect;
  if ( m_pAdditiveEffect )
  {
    (*(void ( **)(gbRenderEffect *))(*(_DWORD *)((gbRefObject *)m_pAdditiveEffect) + 8))(m_pAdditiveEffect);
    this->m_pAdditiveEffect = ((gbRenderEffect *)0);
  }
  m_pScnFrameTex = (gbTexture *)this->m_pScnFrameTex;
  if ( m_pScnFrameTex )
  {
    (*(void ( **)(gbTexture *))(*(_DWORD *)((gbRefObject *)m_pScnFrameTex) + 8))(this->m_pScnFrameTex);
    this->m_pScnFrameTex = ((gbTexture *)0);
  }
  m_pAdditiveEffect2 = (gbRenderEffect *)this->m_pAdditiveEffect2;
  if ( m_pAdditiveEffect2 )
  {
    (*(void ( **)(gbRenderEffect *))(*(_DWORD *)((gbRefObject *)m_pAdditiveEffect2) + 8))(this->m_pAdditiveEffect2);
    this->m_pAdditiveEffect2 = ((gbRenderEffect *)0);
  }
}

// 0x004C58C0
char PAL3::CreateRenderEffects()
{
  gbRenderEffect *v2; // eax
  float m_snaph; // ecx
  char result; // al

  sub_4C5CD0();
  v2 = (((gbEffectMgr *)*(gbEffectMgr **)(LODWORD(this->m_snaph) + 200)))->gbEffectMgr::NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0);
  m_snaph = this->m_snaph;
  this->m_pAdditiveEffect = ((gbRenderEffect *)(v2));
  this->m_pAdditiveEffect2 = ((gbRenderEffect *)((((gbEffectMgr *)*(gbEffectMgr **)(LODWORD(m_snaph) + 200)))->gbEffectMgr::NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0)));
  result = 1;
  *((_BYTE *)&this->m_Image2D + 240) = 1;
  return result;
}

// 0x00527C30
int * PAL3::HandleDeviceLost()
{
  PAL3 *Instance_db10; // eax
  float m_snaph; // ecx
  int v4; // eax
  PAL3 *v5; // eax

  unsigned __int8 v7; // bl
  PAL3 *v8; // eax
  PAL3 *v9; // eax
  int *result; // eax

  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(1);
  m_snaph = PAL3::GetInstance_db10()->m_snaph;
  v4 = 1061158912;
  if ( m_snaph != 0.0f )
    v4 = 1065353216;
  this->m_nTodo_6D8 = v4;
  this->m_nTodo_6D4 = v4;
  v5 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)v5))->RenderTarget::OnResetDevice(1);
  if ( !this->m_nTodo_6C8 )
  {
    v7 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    this->PAL3::Render();
    g_bGameFlag2 = v7;
  }
  v8 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)v8))->RenderTarget::RenderToScreen();
  this->m_nTodo_6D0 = 0;
  v9 = (PAL3 *)PAL3::GetInstance_db10();
  result = (int *)(((RenderTarget *)v9))->RenderTarget::GetActiveTexture();
  if ( result )
  {
    if ( result[21] )
      this->m_nTodo_6D0 = (int)result;
  }
  return result;
}

// 0x0052F570
bool PAL3::WriteRegistryDwordEx(CHAR *lpSubKey, DWORD dwDisposition, ...)
{
  CHAR *v2; // esi
  bool result; // al
  const CHAR *v4; // edi
  char v5; // al
  const char *v6; // eax
  const char *v7; // eax
  va_list Data; // [esp+0x18] [ebp+0xC] BYREF

  va_start(Data, dwDisposition);
  v2 = lpSubKey;
  if ( !lpSubKey )
    return 0;
  v4 = (const CHAR *)dwDisposition;
  if ( !dwDisposition )
    return 0;
  dwDisposition = 1;
  PAL3::StartWolf(HKEY_LOCAL_MACHINE, lpSubKey);
  if ( !v5 )
  {
    v6 = (const char *)RegCreateKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0, 0, 0xF003Fu, 0, (PHKEY)&lpSubKey, &dwDisposition);
    result = ShowMessageBox(v6, szCaption);
    if ( !result )
      return result;
    RegCloseKey((HKEY)lpSubKey);
  }
  RegOpenKeyExA(HKEY_LOCAL_MACHINE, v2, 0, 0x20006u, (PHKEY)&lpSubKey);
  v7 = (const char *)RegSetValueExA((HKEY)lpSubKey, v4, 0, 4u, (const BYTE *)Data, 4u);
  result = ShowMessageBox(v7, "Write Reg Error");
  if ( result )
  {
    RegCloseKey((HKEY)lpSubKey);
    return 1;
  }
  return result;
}

// 0x00532F60
char PAL3::CheckViewCollision()
{
  Scene *v2; // eax
  int m_nTodo_e0e0; // ecx
  float *p_m_active; // ebx
  float v5; // st7
  float v6; // st7
  float v7; // st6
  float v8; // st7
  int v10; // [esp+0x10] [ebp-0x78]
  int v11; // [esp+0x14] [ebp-0x74]
  gbVec3D v12; // [esp+0x18] [ebp-0x70] BYREF
  int ngrade; // [esp+0x28] [ebp-0x60]
  float v14; // [esp+0x2C] [ebp-0x5C]
  float v15; // [esp+0x34] [ebp-0x54]
  float v16; // [esp+0x38] [ebp-0x50]
  float v17[19]; // [esp+0x3C] [ebp-0x4C] BYREF

  v2 = UISceneUpdate();
  m_nTodo_e0e0 = v2->m_nTodo_e0e0;
  v10 = 0;
  v11 = m_nTodo_e0e0;
  if ( m_nTodo_e0e0 <= 0 )
  {
LABEL_8:
    BYTE1(this->m_Image2D.ImgInfo.hdiv[6]) = 1;
    return 0;
  }
  p_m_active = (float *)&v2->m_roles[0].m_active;
  while ( 1 )
  {
    this->m_Image2D.ImgInfo.wrap_u = (int)(p_m_active - 158);
    if ( !*((_DWORD *)p_m_active - 122) || !*(_DWORD *)p_m_active )
      goto LABEL_7;
    memset(&v12, 0, sizeof(v12));
    v5 = *(p_m_active - 157);
    ngrade = this->m_Image2D.ImgInfo.ngrade;
    v14 = *(p_m_active - 155);
    v6 = *(float *)&this->m_Image2D.ImgInfo.goal - v5;
    v15 = *(float *)&this->m_Image2D.ImgInfo.ngrade - *(float *)&ngrade;
    v7 = *(float *)this->m_Image2D.ImgInfo.detail - v14;
    v12.y = v15;
    v16 = v7;
    v12.x = v6;
    v12.z = v16;
    v8 = (((gbVec3D *)&v12))->gbVec3D::Length();
    qmemcpy(v17, (const void *)(LODWORD(this->m_snaph) + 12), sizeof(v17));
    if ( *(float *)(this->m_Image2D.ImgInfo.wrap_u + 16) > fabs(v8 - v17[18] * 0.5) )
      break;
    m_nTodo_e0e0 = v11;
LABEL_7:
    p_m_active += 2176;
    if ( ++v10 >= m_nTodo_e0e0 )
      goto LABEL_8;
  }
  (((RoleSystem *)this->m_Image2D.ImgInfo.wrap_u))->RoleSystem::Notify();
  byte_C11748 = 0;
  byte_C11750 = 0;
  g_nKeyMap3 = 1;
  dword_C1171C = 0x7FFFFFFF;
  PAL3::StartCombatFromNPC((const NPCInfo *)(this->m_Image2D.ImgInfo.wrap_u + 172), 0, 0);
  *(_DWORD *)(this->m_Image2D.ImgInfo.wrap_u + 632) = 0;
  if ( unk_C11720.m_nTodo_34 )
    *(_DWORD *)(unk_C11720.m_nTodo_34 + 632) = 0;
  BYTE1(this->m_Image2D.ImgInfo.hdiv[6]) = 0;
  return 1;
}

// 0x00569020
int PAL3::RandomPickValues(int nVal, int nVal2, int nVal3)
{
  int v3; // eax
  int v4; // ecx
  int v5; // ebx
  int result; // eax
  int *v7; // esi
  int v8; // edi
  int v9; // eax
  int v10; // edx
  int v11; // et2
  int v12; // edx
  int v13; // [esp+0x10] [ebp-0x4]
  int v14; // [esp+0x24] [ebp+0x10]
  int v15; // [esp+0x28] [ebp+0x14]
  _DWORD *v16; // [esp+0x2C] [ebp+0x18]

  memset(v16, 0, 0x18u);
  v3 = nVal3;
  v13 = 0;
  v16[6] = 0;
  if ( !nVal2 )
  {
    if ( !nVal3 )
    {
      v3 = v14;
      v14 = 0;
    }
    nVal2 = v3;
    goto LABEL_5;
  }
  if ( !nVal3 )
  {
LABEL_5:
    v4 = v14;
    v14 = 0;
    nVal3 = v4;
  }
  if ( nVal2 )
    v13 = 1;
  if ( nVal3 )
    ++v13;
  if ( v14 )
    ++v13;
  v5 = nVal;
  if ( v15 )
  {
    v5 = nVal + 1;
    *v16 = v15;
  }
  result = v15 != 0;
  if ( result < v5 )
  {
    v7 = (int *)&v16[result];
    v8 = v5 - result;
    do
    {
      v9 = rand();
      v11 = v9 % v13;
      result = v9 / v13;
      v10 = v11;
      if ( v11 )
      {
        v12 = v10 - 1;
        if ( v12 )
        {
          if ( v12 == 1 )
          {
            result = v14;
            *v7 = v14;
          }
        }
        else
        {
          *v7 = nVal3;
        }
      }
      else
      {
        *v7 = nVal2;
      }
      ++v7;
      --v8;
    }
    while ( v8 );
  }
  v16[6] = v5;
  return result;
}

// 0x00569110
void PAL3::ResetForNewScene()
{
  CScreenMode *v0; // ecx
  PtrArray *SoundList; // eax
  PAL3 *v2; // ecx
  RenderTarget3 *v3; // ecx
  RenderTarget3 *Instance; // eax
  CScreenMode *v5; // eax
  gbAudioManager *AudioManager; // eax
  RoleSystem *v7; // esi
  Actor *SaveDataManager; // eax
  Actor *v9; // eax
  char *v10; // [esp-0x8] [ebp-0x8]
  int *v11; // [esp-0x4] [ebp-0x4]
  char *v12; // [esp-0x4] [ebp-0x4]
  char v13; // [esp+0x4] [ebp+0x4]

  g_fEffectTimer = 10.0;
  (((RoleSystem *)&g_ScriptSystemData))->RoleSystem::Reset();
  (((RoleSystem *)&unk_D8B4A0))->RoleSystem::Reset();
  SoundList = (((CScreenMode *)v0))->CScreenMode::GetSoundList();
  sub_53D1D0(SoundList);
  (((PAL3 *)v2))->PAL3::UIPostProcess();
  sub_4CE5C0(g_pSceneManager);
  (((CEffMgr *)g_pSceneManager))->CEffMgr::ReleaseCompletedEffects();
  Instance = (((RenderTarget3 *)v3))->RenderTarget3::GetInstance();
  (((RenderTarget3 *)Instance))->RenderTarget3::SwapBuffers();
  g_nPAL3_D8E488 = 0;
  LOBYTE(byte_BFDA40) = 0;
  if ( (g_dwGameFlags & 1) == 0 )
    JUMPOUT(0x2EE3E9A);
  v5 = (CScreenMode *)CScreenMode::GetInstance();
  AudioManager = (gbAudioManager *)(((CScreenMode *)v5))->CScreenMode::GetAudioManager();
  (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
  g_fPalScript_C12B28 = 0.0;
  g_fPalScript_C12B2C = 0.0;
  g_fPalScript_C12B30 = 0.0;
  v7 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
  do
  {
    (((RoleSystem *)v7))->RoleSystem::Notify();
    v7 = (RoleSystem *)((char *)v7 + 8704);
  }
  while ( (int)v7 < (int)&g_RoleSystemArrayEnd );
  if ( *(&dword_C9A63C + 123289 * (g_ScriptSystemData.m_nGameMode == 1)) )
  {
    (((Scene *)(493156 * (g_ScriptSystemData.m_nGameMode == 1) + 12722152)))->Scene::_todo_421870();
    if ( v13 )
    {
      v11 = (int *)(493156 * (g_ScriptSystemData.m_nGameMode == 1) + 12722152);
      SaveDataManager = (Actor *)GetSaveDataManager();
      (((Actor *)SaveDataManager))->Actor::BuildCollisionMesh(v11);
      v12 = (char *)(493156 * (g_ScriptSystemData.m_nGameMode == 1) + 12722184);
      v10 = (char *)(493156 * (g_ScriptSystemData.m_nGameMode == 1) + 12722152);
      v9 = (Actor *)GetSaveDataManager();
      (((Actor *)v9))->Actor::RegisterAnim(v10, v12);
    }
  }
}
