#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/PAL3.h"

// Forward declarations for unnamed functions
int CombatEffectUpdate(int _this, double pData); // from annotations
void EffectUpdate(float fVal); // from annotations
void * GetSaveDataManager(void); // from annotations
int InputUpdate(int _this, int nVal); // from annotations
int MiniGame1Update(int ***_this, double pData); // from annotations
void MiniGame2Update(int **_this, int nVal); // from annotations
void MiniGame3Update(int *_this, float fVal); // from annotations
int NPCAnimUpdate(float fVal); // from annotations
char SceneMgrUpdate(float *_this, float fVal); // from annotations
int SceneUpdate(...);
char * ScriptUpdate(int dt); // from annotations
int UINotifyUpdate(int *_this); // from annotations
void UIPostUpdate(gbSound2DNode *_this); // from annotations
int UISceneUpdate(void); // from annotations
void sub_421870(struct gbVisNode **_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_4C5CD0(...);
int sub_4CE5C0(...);
int sub_53D1D0(...);
int todo_408BD0(...);

gbGfxManager * CombatEnter(void); // from annotations
int crt_sub_00540D20(void); // from annotations
int crt_sub_00541590(void); // from annotations
int PAL3_RandomPickValues(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int *p_DWORD); // from annotations
BOOL PointInRect(int *pRect, int *pPoint); // from annotations
BOOL ReadRegistryString(const char *szSubKey, const char *szValueName, char *szOutBuf); // from annotations
int RenderPost(int _this, int nVal); // from annotations
BOOL ShowMessageBox(const char *szMessage, const char *szCaption); // from annotations

// Unnamed globals (extern)
extern char aSceneData[];
extern char byte_BFDA40;
extern char byte_BFDA41;
extern unsigned __int8 byte_D924B4[];
extern int dword_1000000;
extern int dword_A3A750;
extern std::ios_base dword_BFDAB0;
extern int dword_C042F8;
extern int dword_C042FC;
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
extern int * dword_C0439C;
extern int dword_C10A10;
extern int dword_C10A18;
extern int dword_C10A1C;
extern int dword_C10A20;
extern int dword_C10A28;
extern int dword_C10A2C;
extern int dword_C10A30;
extern int dword_C10A38;
extern int dword_C10A3C;
extern int dword_C10A40;
extern int dword_C10A48;
extern int dword_C10A4C;
extern int dword_C10A50;
extern int dword_C10A58;
extern int dword_C10A5C;
extern int dword_C10A60;
extern int dword_C10A68;
extern int dword_C10A6C;
extern int dword_C10A70;
extern int dword_C10A78;
extern int dword_C10A7C;
extern int dword_C10A80;
extern int dword_C10A88;
extern int dword_C10A8C;
extern int dword_C10A90;
extern int dword_C10A98;
extern int dword_C10A9C;
extern int dword_C10AA0;
extern int dword_C10AA8;
extern int dword_C10AAC;
extern int dword_C10AB0;
extern int dword_C10AB8;
extern int dword_C10ABC;
extern int dword_C10AC0;
extern int dword_C10AC8;
extern int dword_C10ACC;
extern int dword_C10AD0;
extern int dword_C10AD8;
extern int dword_C10ADC;
extern int dword_C10AE0;
extern int dword_C10AE8;
extern int dword_C10AEC;
extern int dword_C10AF0;
extern int dword_C10AF8;
extern int dword_C10AFC;
extern int dword_C10B00;
extern int dword_C10B08;
extern int dword_C10B0C;
extern int dword_C10B10;
extern int dword_C10B18;
extern int dword_C10B1C;
extern int dword_C10B20;
extern int dword_C10B28;
extern int dword_C10B2C;
extern int dword_C10B30;
extern int dword_C10B38;
extern int dword_C10B3C;
extern int dword_C10B40;
extern int dword_C10B48;
extern int dword_C10B4C;
extern int dword_C10B50;
extern int dword_C10B58;
extern int dword_C10B5C;
extern int dword_C10B60;
extern int dword_C10B68;
extern int dword_C10B6C;
extern int dword_C10B70;
extern int dword_C10B78;
extern int dword_C10B7C;
extern int dword_C10B80;
extern int dword_C10B88;
extern int dword_C10B8C;
extern int dword_C10B90;
extern int dword_C10B98;
extern int dword_C10B9C;
extern int dword_C10BA0[];
extern int dword_C10BA4;
extern int dword_C10BA8;
extern int dword_C10BAC;
extern int dword_C10BB0;
extern int dword_C10BB4;
extern int dword_C10BB8;
extern int dword_C10BBC;
extern int dword_C10BC0;
extern int dword_C10BC4;
extern int dword_C10BC8;
extern int dword_C10BCC;
extern int dword_C10BD0;
extern int dword_C10BD4;
extern int dword_C10BD8;
extern int dword_C10BDC;
extern int dword_C10BE0;
extern int dword_C10BE4;
extern int dword_C10BE8;
extern int dword_C10BEC;
extern int dword_C10BF0;
extern int dword_C10BF4;
extern int dword_C10BF8;
extern int dword_C10BFC;
extern int dword_C10C00;
extern int dword_C10C04;
extern int dword_C10C08;
extern int dword_C10C0C;
extern int dword_C10C10;
extern int dword_C10C14;
extern int dword_C10C18;
extern int dword_C10C1C;
extern int dword_C10C20;
extern int dword_C10C24;
extern int dword_C10C28;
extern int dword_C10C2C;
extern int dword_C10C30;
extern int dword_C10C34;
extern int dword_C10C38;
extern int dword_C10C3C;
extern int dword_C10C40;
extern int dword_C10C44;
extern int dword_C10C48;
extern int dword_C10C4C;
extern int dword_C10C50;
extern int dword_C10C54;
extern int dword_C10C58;
extern int dword_C10C5C;
extern int dword_C10C60;
extern int dword_C10C64;
extern int dword_C10C68;
extern int dword_C10C6C;
extern int dword_C10C70;
extern int dword_C10C74;
extern int dword_C10C78;
extern int dword_C10C7C;
extern int dword_C10C80;
extern int dword_C10C84;
extern int dword_C10C88;
extern int dword_C10C8C;
extern int dword_C10CD4;
extern int dword_C10E50;
extern int dword_C1171C;
extern int dword_C9A63C[];
extern int dword_D8BBEC;
extern int dword_DC3B3C;
void __cdecl nullsub_2(...);
extern const char * off_583A1C;
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C08160;
extern PalScript stru_C11720;
extern SceneMapPlayer stru_D8B4A0;
extern GRPinput stru_D8C2B8;
extern unsigned __int8 unk_D924E8;
void __cdecl unknown_libname_416(void);
void __cdecl unknown_libname_427(void);
void __cdecl unknown_libname_437(void);

// 0x00401BC0
void * PAL3::InitVFileSystem()
{
  return ((gbVFileSystem *)&g_BaseVFileSystem); // ctor auto-called
}

// 0x00401C00
void * PAL3::InitVFileSystem2()
{
  return ((gbVFileSystem *)&g_VFileSystem); // ctor auto-called
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
  PAL3::TestCombat();
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
void PAL3::_PAL3()
{

}

// 0x00404FF0
void PAL3::InitGFX()
{
  gbActorMgr *v1; // eax
  gbActorMgr *v2; // eax
  Camera *v3; // eax
  Camera *v4; // eax
  char *v5; // esi
  struct gbClearParam v6; // [esp+0x20] [ebp-0x81C] BYREF
  char pExceptionObject[1024]; // [esp+0x30] [ebp-0x80C] BYREF
  char ArgList[1024]; // [esp+0x430] [ebp-0x40C] BYREF
  int v9; // [esp+0x838] [ebp-0x4]

  gfxMgr = gbCreateGraphManager(&g_DrvInfo);
  if ( !gfxMgr )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(&path[208], &path[72], 401),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v1 = (gbActorMgr *)operator new(0xCu);
  v9 = 0;
  if ( v1 )
    // [AUTO-COMMENTED] v2 = ((gbActorMgr *)v1)->gbActorMgr(gfxMgr);
  else
    v2 = 0;
  v9 = -1;
  g_pActorMgr = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(&path[180], &path[72], 405),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v3 = (Camera *)operator new(0x220u);
  v9 = 1;
  if ( v3 )
    // [AUTO-COMMENTED] v4 = ((Camera *)v3)->Camera(gfxMgr);
  else
    v4 = 0;
  v9 = -1;
  g_pCameraCtrl = (CameraCtrl *)v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(&path[164], &path[72], 409),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((CameraCtrl *)v4)->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  old_sbh_page_manage((__old_sbh_page_struct *)g_pCameraCtrl, 0);
  ((CameraCtrl *)&g_pCameraCtrl)->SetAsCurrent(3);
  v6.clearflag = 3;
  v6.color = -16777216;
  v6.depth = 1.0;
  ((gbGfxManager *)gfxMgr)->SetClearParam(&v6);
  v5 = (char *)operator new(0xD8u);
  v9 = 2;
  if ( v5 )
  {
    *((_DWORD *)v5 + 1) = 1;
    *((_DWORD *)v5 + 24) = 0;
    *((_DWORD *)v5 + 25) = 0;
    *((_DWORD *)v5 + 26) = 0;
    LOBYTE(v9) = 3;
    *((_DWORD *)v5 + 40) = 0;
    *((_DWORD *)v5 + 41) = 0;
    *((_DWORD *)v5 + 42) = 0;
  }
  else
  {
    v5 = 0;
  }
  v9 = -1;
  ((gbLightObj *)v5)->Init(2);
  *((_DWORD *)v5 + 7) = 1065353216;
  *((_DWORD *)v5 + 8) = 1065353216;
  *((_DWORD *)v5 + 9) = 1065353216;
  *((_DWORD *)v5 + 10) = 1065353216;
  *((_DWORD *)v5 + 12) = 1;
  *((_DWORD *)v5 + 11) = 1;
  *((_DWORD *)v5 + 3) = 1049582633;
  *((_DWORD *)v5 + 4) = 1049582633;
  *((_DWORD *)v5 + 5) = 1049582633;
  *((_DWORD *)v5 + 16) = 1092616192;
  *((_DWORD *)v5 + 15) = 1092616192;
  *((_DWORD *)v5 + 6) = 1065353216;
  ((gbVolModNode *)&g_pVolModNode)->SetVolModObj((gbVolumeModifier *)v5);
  ((gbRefObject *)v5)->Release();
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
  v9 = v1;
  LOBYTE(v14) = 1;
  if ( v1 )
  {
  }
  else
    v1 = 0;
  LOBYTE(v14) = 0;
  g_pDropGroup = v1;
  v2 = (gbRain *)operator new(0x50u);
  v3 = (int)v2;
  v9 = v2;
  LOBYTE(v14) = 2;
  if ( v2 )
  {
  }
  else
    v3 = 0;
  LOBYTE(v14) = 0;
  g_nPAL3_BFDA3C = v3;
  v4 = (CEffectSystem *)operator new(0x158u);
  v9 = v4;
  LOBYTE(v14) = 3;
  if ( v4 )
    v5 = (PAL3 *)((CEffectSystem *)v4)->Create((int)gfxMgr);
  else
    v5 = 0;
  LOBYTE(v14) = 0;
  g_pEffectSystem = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[236], &path[72], 483),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  RenderEffects = ((PAL3 *)v5)->CreateRenderEffects();
  v14 = -1;
  if ( RenderEffects )
  {
    return 1;
  }
  else
  {
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
    ((CEffectSystem *)&g_pEffectSystem)->Destroy_5840();
    operator delete(v1);
  }
  g_pEffectSystem = 0;
  return 1;
}

// 0x004055D0
void PAL3::Update(float dt)
{
  double v2; // rdi
  int v3; // edi
  int *p_subtype; // esi
  __int16 KeyState; // ax
  BOOL v6; // eax
  DWORD Time; // eax
  int v8; // esi
  PAL3 *v9; // ecx
  int v10; // ebx
  int v11; // eax
  SystemUI *v13; // eax
  int v15; // ebx

  char v19; // al
  PalScriptMgr *v20; // ecx
  SystemUI *v22; // eax
  CameraCtrl *v23; // ecx
  int *v24; // eax

  int v26; // eax
  CScreenMode *v27; // ecx
  PtrArray *SoundList; // eax
  PalScriptMgr *v29; // ecx

  RenderTarget2 *Instance_fd20; // eax
  PalScriptMgr *v32; // ecx
  PalScriptMgr *v33; // ecx
  CameraCtrl *v34; // ecx
  SystemUI *v35; // eax
  gbSound2DNode *v36; // ecx
  CScreenMode *Instance; // eax
  CScreenMode *v38; // eax
  CUtil *Mode; // eax
  CScreenMode *v40; // eax
  gbAudioManager *AudioManager; // esi
  CScreenMode *v42; // eax
  CScreenMode *v43; // eax
  PalScriptMgr *v44; // ecx
  ScreenEffect *v45; // eax
  double result; // [esp+0x0] [ebp-0x30]
  double resulta; // [esp+0x0] [ebp-0x30]
  double resultb; // [esp+0x0] [ebp-0x30]
  double resultc; // [esp+0x0] [ebp-0x30]
  int result_4; // [esp+0x4] [ebp-0x2C]
  int result_4a; // [esp+0x4] [ebp-0x2C]
  double v52; // [esp+0x8] [ebp-0x28]
  float pData; // [esp+0x18] [ebp-0x18]
  double pDataa; // [esp+0x18] [ebp-0x18]
  float pData_4; // [esp+0x1C] [ebp-0x14]
  float v56; // [esp+0x20] [ebp-0x10]
  gbVec3D v57; // [esp+0x24] [ebp-0xC] BYREF

  __asm
  {
    fld     g_fGameTimer
    fadd    [esp+dt]
  }
  __asm { fstp    g_fGameTimer }
  v52 = v2;
  v3 = 0;
  p_subtype = &g_PAL3_Instance.s_drvinfo.subtype;
  do
  {
    KeyState = ((GRPinput *)&g_Input)->GetKeyState(*(_WORD *)p_subtype);
    v6 = KeyState == 1 || KeyState == 3;
    result_4 = v6;
    Time = timeGetTime();
    ((GRPinput *)&g_Input)->SetMouseAbs(Time, v3, result_4);
    p_subtype = (int *)((char *)p_subtype + 2);
    ++v3;
  }
  while ( (int)p_subtype < (int)&g_PAL3_Instance.s_drvinfo.winname[46] );
  v8 = g_nSceneState;
  v10 = SceneUpdate((int)&g_gamefrm, SLODWORD(dt));
  v11 = g_nSceneState;
  if ( g_nSceneState != v8 )
  {
    ((PAL3 *)v8)->IfHideFightSucceed();
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
      Instance_fd20 = (RenderTarget2 *)this->GetInstance_fd20();
      ((RenderTarget2 *)Instance_fd20)->Update(dt);
      ((PalScriptMgr *)v32)->RunSceneScript((const char *)LODWORD(dt));
      if ( ((GRPinput *)&stru_D8C2B8)->m_keyStates[25] )
      {
        ((GRPinput *)&stru_D8C2B8)->m_keyStates[25] = 0;
        ((PalScriptMgr *)v33)->RunSceneScript((const char *)LODWORD(dt));
      }
      InputUpdate((int)g_pCameraCtrl, SLODWORD(dt));
      if ( g_nSceneState != 9 )
      {
        if ( v10 )
        {
          UIQuadManager::GetInstance();
          crt_sub_00541590();
        }
        else
        {
          ((CameraCtrl *)v34)->UpdateInternal(dt);
        }
        ScriptUpdate(SLODWORD(dt));
      }
      // __asm { fld     [esp+0x28+dt] }
      // __asm { fstp    [esp+0x30+result]; result }
      v35 = (SystemUI *)UISceneUpdate();
      ((SystemUI *)v35)->UIUpdate(resultb, v52);
      EffectUpdate(dt);
      SceneMgrUpdate((float *)g_pSceneManager, g_fTimeScale);
      UIPostUpdate(v36);
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioUpdate();
      if ( g_nSceneState != 2 && g_nSceneState != 9 )
        ((PAL3 *)v8)->IfHideFightSucceed();
      goto LABEL_64;
    case 3:
      // __asm { fld     [esp+0x28+dt]; jumptable 00405676 case 3 }
      // __asm { fstp    [esp+0x28+pData] }
      ((CCBSystem *)&g_pCBSystem)->CombatUpdate(pDataa);
      CombatEffectUpdate((int)g_pEffectSystem, pDataa);
      v38 = CScreenMode::GetInstance();
      ((CScreenMode *)v38)->AudioUpdate();
      LOBYTE(v9) = g_pCBSystem->m_bQuitFlag;
      if ( !(_BYTE)v9 )
        goto LABEL_64;
      LOBYTE(v9) = g_bTestCombat;
      if ( g_bTestCombat )
      {
        ((PAL3 *)v9)->GetCommandLineParam();
        ((CCBSystem *)&g_pCBSystem)->CombatUpdate(0.0);
        CombatEffectUpdate((int)g_pEffectSystem, 0.0);
        goto LABEL_59;
      }
      g_szGamePath[0] = *(_DWORD *)&g_pCBSystem->m_eResult == 2;
      Mode = (CUtil *)((CGameData *)&g_gamefrm)->GetMode();
      ((CGameData *)&g_gamefrm)->Load(Mode);
      CombatEnter();
      if ( (g_dwGameFlags & 4) == 0 )
        goto LABEL_54;
      v40 = CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)v40)->GetAudioManager();
      if ( !AudioManager )
        goto LABEL_54;
      if ( BYTE1(((PalScript *)&stru_C11720)->_todo_48) )
      {
        LOBYTE(v9) = CScreenMode::GetInstance()->m_bRenderAlt;
        if ( (_BYTE)v9 )
          goto LABEL_54;
        goto LABEL_51;
      }
      ((gbAudioManager *)AudioManager)->StopSoundStream(1);
      ((gbAudioManager *)AudioManager)->StopSoundStream(0);
      if ( !CScreenMode::GetInstance()->m_bRenderAlt )
      {
LABEL_51:
        ((gbAudioManager *)AudioManager)->StopSoundStream(2);
        ((gbAudioManager *)AudioManager)->StopSoundStream(1);
        v42 = CScreenMode::GetInstance();
        ((CScreenMode *)v42)->AudioStopAll();
        goto LABEL_54;
      }
      v43 = CScreenMode::GetInstance();
      ((CScreenMode *)v43)->AudioFadeOut();
LABEL_54:
      if ( g_szGamePath[0] || !g_nKeyMap3 )
      {
        if ( ((PalScript *)&stru_C11720)->_todo_034 )
          *(_DWORD *)(((PalScript *)&stru_C11720)->_todo_034 + 632) = 0;
      }
      else
      {
        ((CGameData *)&g_gamefrm)->Load((CUtil *)0xF);
        ((PalScriptMgr *)v44)->IfHaveScript();
      }
LABEL_59:
      LOBYTE(((PalScript *)&stru_C11720)->_todo_028) = 0;
      LOBYTE(((PalScript *)&stru_C11720)->_todo_48) = 0;
      dword_C1171C = 0x7FFFFFFF;
      g_nKeyMap3 = 1;
      goto LABEL_64;
    case 4:
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      // __asm { fld     [esp+0x28+dt] }
      // __asm { fstp    [esp+0x30+result]; pData }
      MiniGame1Update((int ***)g_pMiniGame1, resultc);
      goto LABEL_64;
    case 5:
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      MiniGame2Update((int **)g_pMiniGame2, SLODWORD(dt));
      goto LABEL_63;
    case 6:
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      MiniGame3Update((int *)g_pMiniGame3, dt);
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
        if ( !((PalScriptMgr *)v9)->_CON_CloseScript() )
        {
          unk_D924E8 = 1;
          ((CGameData *)&g_gamefrm)->Load((CUtil *)4);
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
          ((PAL3 *)-1)->EndWolf();
          goto LABEL_64;
        }
      }
      ((PalScriptMgr *)v9)->RunSceneScript((const char *)LODWORD(dt));
      InputUpdate((int)g_pCameraCtrl, SLODWORD(dt));
      ScriptUpdate(SLODWORD(dt));
      // __asm { fld     [esp+0x2C+dt] }
      // __asm { fstp    [esp+0x30+result]; result }
      v13 = (SystemUI *)UISceneUpdate();
      ((SystemUI *)v13)->UIUpdate(result, v52);
      EffectUpdate(dt);
      if ( LODWORD(g_fDeltaTime) )
        goto LABEL_64;
      if ( !v10 )
        ((CameraCtrl *)v9)->UpdateInternal(dt);
      _EBP = g_pRoleSystem;
      v15 = 1;
      _ESI = &((RoleSystem *)&stru_C08160)->m_id;
      while ( 1 )
      {
        if ( _ESI[155] )
        {
          __asm
          {
            fld     dword ptr [ebp+4]
            fsub    dword ptr [esi-8]
            fstp    dword ptr [esp+0x28+pData]
            fld     dword ptr [ebp+8]
            fsub    dword ptr [esi-4]
          }
          v57.x = pData;
          __asm
          {
            fstp    dword ptr [esp+0x28+pData+4]
            fld     dword ptr [ebp+0x0C]
            fsub    dword ptr [esi]
          }
          v57.y = pData_4;
          // __asm { fstp    [esp+0x28+var_10] }
          v57.z = v56;
          ((gbVec3D *)&v57)->Length();
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
        _ESI += 2176;
        ++v15;
        if ( (int)_ESI >= (int)&g_pScriptArrayEnd2 )
          goto LABEL_64;
      }
      ((PAL3 *)v15)->EndWolf();
      goto LABEL_64;
    case 8:
      ((PAL3 *)v9)->EntryCatchGhost();
      if ( v19 )
      {

        ((RoleSystem *)&g_pRoleSystem)->Notify();
LABEL_33:
        ((PalScriptMgr *)v20)->Destroy();
        result_4a = v26;
        SoundList = ((CScreenMode *)v27)->GetSoundList();
        ((PtrArray *)SoundList)->SetResolution(0, result_4a);
        ((PalScriptMgr *)v29)->RunSceneScript((const char *)LODWORD(dt));
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
      ((PalScriptMgr *)this)->RunSceneScript((const char *)LODWORD(dt));
      InputUpdate((int)g_pCameraCtrl, SLODWORD(dt));
      ScriptUpdate(SLODWORD(dt));
      // __asm { fld     [esp+0x2C+dt] }
      // __asm { fstp    [esp+0x30+result]; result }
      v22 = (SystemUI *)UISceneUpdate();
      ((SystemUI *)v22)->UIUpdate(resulta, v52);
      EffectUpdate(dt);
      if ( !v10 )
        ((CameraCtrl *)v23)->UpdateInternal(dt);
      UIPostUpdate((gbSound2DNode *)v23);
      v9 = (PAL3 *)g_pRoleSystem;
      if ( g_pRoleSystem->m_FrameA.m_rect.right != 4 )
      {
        v24 = (int *)UISceneUpdate();
        if ( UINotifyUpdate(v24) )
        {
LABEL_32:
          ((RoleSystem *)&g_pRoleSystem)->Notify();

          goto LABEL_33;
        }
      }
LABEL_64:
      v45 = ((ScreenEffectMgr *)v9)->GetInstance();
      RenderPost((int)v45, SLODWORD(dt));
      if ( !g_nSceneState )
        ((CScreenMode *)&g_InputState)->SetState(1);
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
  SystemUI *v11; // eax
  ScriptSystem *v12; // ecx
  gbCamera *v13; // eax
  gbCamera *v14; // eax
  UIScene *v15; // eax
  gbCamera *v16; // eax
  UIScene *v17; // ecx
  SystemUI *v18; // eax
  SceneMgr *v19; // eax
  gbCamera *v20; // eax
  UIScene *v21; // ecx
  UIScene *v22; // eax

  RenderTarget3 *v24; // eax

  RenderTarget2 *v26; // eax
  RenderTarget3 *v27; // ecx
  RenderTarget3 *v28; // eax
  Scene *v29; // ecx
  int v30; // edi
  __int64 v31; // rax
  gbPrintFont *v32; // esi
  double v33; // st7
  ScreenEffectMgr *v34; // ecx
  ScreenEffect *v35; // eax
  UIQuadManager *v36; // eax

  float v38; // [esp+0x0] [ebp-0x94]
  float v39; // [esp+0x4] [ebp-0x90]
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

  (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 48))(gfxMgr);
  switch ( g_nSceneState )
  {
    case 0:
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 52))(gfxMgr);
      return;
    case 2:
    case 7:
    case 8:
    case 9:
      Instance = this->GetInstance();
      ((RenderTarget3 *)Instance)->End();
      Instance_fd20 = (RenderTarget2 *)this->GetInstance_fd20();
      ((RenderTarget2 *)Instance_fd20)->Begin();
      pSceneGraph = gfxMgr->pSceneGraph;
      if ( g_pCameraCtrl )
        p_m_fMinDist = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
      else
        p_m_fMinDist = 0;
      ((gbSceneGraph *)pSceneGraph)->Begin(p_m_fMinDist);
      v8 = ((UIScene *)v7)->CombatCheck();
      v9 = gfxMgr->pMatrixStack[1];
      ((CameraCtrl *)&g_pCameraCtrl)->SetAsCurrent(3);
      v41.x = 1.0;
      v41.y = 0.0;
      v41.z = 0.0;
      ((gbMatrixStack *)v9)->Rotate(g_fPalScript_C12B28, v41);
      v42.x = 0.0;
      v42.y = 1.0;
      v42.z = 0.0;
      ((gbMatrixStack *)v9)->Rotate(g_fPalScript_C12B2C, v42);
      v43.x = 0.0;
      v43.y = 0.0;
      v43.z = 1.0;
      ((gbMatrixStack *)v9)->Rotate(g_fPalScript_C12B30, v43);
      if ( !v8 && *(_DWORD *)(UISceneUpdate() + 100) != 1 )
      {
        memset(&v46, 0, 12);
        memset(&v47, 0, 12);
        memset(&v48, 0, 12);
        v44.y = 0.0;
        v44.z = 0.0;
        v46.w = 1.0;
        v47.w = 1.0;
        v48.w = 1.0;
        v44.x = 1.0;
        ((gbQuaternion *)&v46)->SetAxisAngle(&v44, 45.0);
        v45.x = 0.0;
        v45.y = 1.0;
        v45.z = 0.0;
        ((gbQuaternion *)&v47)->SetAxisAngle(&v45, 90.0);
        ((gbQuaternion *)&v47)->MultiplyBy(&v46, &v48);
        ((gbQuaternion *)&v48)->GetMatrix((gbMatrix4 *)dword_A3A750);
        ((gbVolModNode *)&g_pVolModNode)->Attach(0);
      }
      if ( ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].CountMode == 2 )
      {
        Top = ((gbMatrixStack *)v9)->GetTop();
        ((gbMatrix4 *)Top)->TransformPlane();
        (*(void ( **)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 112))(
          gfxMgr,
          &((GRPinput *)&stru_D8C2B8)->KeyInfo[149].CountMode);
      }
      else
      {
        (*(void ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr + 112))(gfxMgr, 0);
      }
      v11 = (SystemUI *)UISceneUpdate();
      ((SystemUI *)v11)->RenderWithStack(v9);
      if ( g_nSceneState != 9 )
        ((ScriptSystem *)v12)->Render(v9);
      ((gbSceneGraph *)pSceneGraph)->End();
      if ( g_pDropGroup && byte_BFDA40 )
      {
        if ( g_pCameraCtrl )
          v13 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
        else
          v13 = 0;
        ((gbDropGroup *)g_pDropGroup)->Render(v13);
      }
      if ( g_nPAL3_BFDA3C && byte_BFDA41 )
      {
        if ( g_pCameraCtrl )
          v14 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
        else
          v14 = 0;
        ((gbDropGroup *)g_nPAL3_BFDA3C)->Render(v14);
      }
      v15 = (UIScene *)UISceneUpdate();
      ((UIScene *)v15)->NotifyRender();
      if ( g_pCameraCtrl )
        v16 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
      else
        v16 = 0;
      ((gbSceneGraph *)pSceneGraph)->Begin(v16);
      LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
      if ( *(_DWORD *)(UISceneUpdate() + 100) != 1 )
        ((UIScene *)v17)->CombatCheck();
      v18 = (SystemUI *)UISceneUpdate();
      ((SystemUI *)v18)->Render((int)v9);
      ((SceneMgr *)g_pSceneManager)->RenderUpdate();
      ((gbSceneGraph *)pSceneGraph)->End();
      if ( g_nSceneState == 8 )
      {
        v19 = (SceneMgr *)UISceneUpdate();
        ((SceneMgr *)v19)->RenderActiveRoles();
      }
      ((UIManager *)&((PalScript *)&stru_C11720)->m_bCreated)->Render();
      ((SceneMgr *)g_pSceneManager)->RenderAll();
      if ( g_pCameraCtrl )
        v20 = (gbCamera *)&g_pCameraCtrl->m_fMinDist;
      else
        v20 = 0;
      ((gbSceneGraph *)pSceneGraph)->Begin(v20);
      LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
      ((UIScene *)v21)->CombatCheck();
      ((RoleSystem *)v9)->RenderMainRole();
      v22 = (UIScene *)UISceneUpdate();
      ((UIScene *)v22)->OverlayRender((int)v9);
      ((gbSceneGraph *)pSceneGraph)->End();
      v24 = this->GetInstance();
      ((RenderTarget3 *)v24)->Resolve();
      v26 = (RenderTarget2 *)this->GetInstance_fd20();
      ((RenderTarget2 *)v26)->Resolve();
      v28 = ((RenderTarget3 *)v27)->GetInstance();
      ((RenderTarget3 *)v28)->Begin();
      if ( !g_bGameFlag2 )
        break;
      goto LABEL_42;
    case 3:
      ((CCBSystem *)&g_pCBSystem)->RenderCheck();
      break;
    case 4:
      ((MiniGame1 *)g_pMiniGame1)->Render();
      break;
    case 5:
      ((gbMatrixStack *)g_pMiniGame2)->SceneRenderWithRotation();
      goto LABEL_42;
    case 6:
      ((MiniGame3 *)g_pMiniGame3)->Render();
LABEL_42:
      ((Scene *)v29)->Render2();
      break;
    default:
      break;
  }
  if ( g_nSceneState == 8 )
  {
    v30 = (__int64)(180.0 - g_fFadeAngle);
    goto LABEL_46;
  }
  if ( g_nSceneState == 7 )
  {
    v30 = (int)(__int64)(60.0 - g_fFadeAngle) < 0 ? 0 : (__int64)(60.0 - g_fFadeAngle);
LABEL_46:
    sprintf((char *const)&v47.z, "%03d", v30);
    LOBYTE(v31) = 0;
    v32 = gfxMgr->pFontMgr->pAllFont[3];
    if ( v30 < 30 )
      v31 = (__int64)(sin(g_fFadeAngle * 4.0) * 255.0);
    v33 = 60.0 / (double)g_DrvInfo.height;
    v32->ScaleX = 60.0 / (double)g_DrvInfo.width;
    v32->ScaleY = v33;
    if ( (_BYTE)v31 )
    {
      if ( gbColorQuad::ColorQuadFmt )
      {
        BYTE2(v40[0]) = v31;
        LOWORD(v40[0]) = 29338;
      }
      else
      {
        *(_WORD *)((char *)v40 + 1) = -25998;
        LOBYTE(v40[0]) = v31;
      }
      HIBYTE(v40[0]) = -56;
      v32->curColor.Color = v40[0];
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
      v32->curColor.Color = v40[0];
    }
    v39 = 1.0 - 64.0 / (double)g_DrvInfo.height;
    v38 = 1380.0 / (double)g_DrvInfo.width - 1.0;
    ((void ( *)(gbPrintFont *, float *, _DWORD, _DWORD, int, int))v32->pGfxMgr->DrvInfo.subtype)(
      v32,
      &v47.z,
      LODWORD(v38),
      LODWORD(v39),
      1176256512,
      1176256512);
    ((void ( *)(gbPrintFont *))v32->pGfxMgr->hGfxWnd)(v32);
  }
  if ( g_nSceneState && g_nSceneState != 3 && g_bGameFlag2 )
  {
    PushMatrixStacks(v40);
    v49 = 0;
    v35 = ((ScreenEffectMgr *)v34)->GetInstance();
    ((ScreenEffectMgr *)v35)->UpdateFrontEffect();
    ((CGameData *)&g_gamefrm)->ProcessDialog();
    if ( LODWORD(g_fGameSpeed) )
      (*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(g_fGameSpeed) + 4))(LODWORD(g_fGameSpeed));
    if ( !g_bEditorMode )
      ((Logger *)&g_InputState)->Render();
    v49 = -1;
    PopMatrixStacks(v40);
  }
  v36 = UIQuadManager::GetInstance();
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 52))(gfxMgr);
  if ( g_bEditorMode )
  {

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

  Instance_db10 = this->GetInstance_db10();
  ((PAL3 *)Instance_db10)->InvalidateSnapH();
  Instance_fd20 = (PAL3 *)this->GetInstance_fd20();
  ((PAL3 *)Instance_fd20)->ClearAdditiveEffects();
  Instance = UIQuadManager::GetInstance();
  crt_sub_005415C0(Instance);
  ((ScriptSystem *)v5)->Destroy();
  ((UISystem *)v6)->Destroy();
  ((TextureLibDataBase *)v7)->_TextureLib_Data();
  ((PalScriptMgr *)v8)->_CON_ReLoadScript();
  if ( g_pCBSystem )
  {
    ((CCBSystem *)&g_pCBSystem)->ProcFling();
    v9 = g_pCBSystem;
    if ( g_pCBSystem )
    {
      todo_408BD0(v13);
      operator delete(v9);
    }
    g_pCBSystem = 0;
  }
  ((CGameData *)&g_gamefrm)->Cleanup();

  if ( g_pCameraCtrl )
  {
    COERCE_VOID_THISCALL_DWORD_DWORD_(g_pCameraCtrl->m_pCamera->fov)(g_pCameraCtrl, 1);
    g_pCameraCtrl = 0;
  }
  v11 = g_pActorMgr;
  if ( g_pActorMgr )
  {
    operator delete(v11);
    g_pActorMgr = 0;
  }
  if ( gfxMgr )
  {
    (**(void ( ***)(gbGfxManager *, int))gfxMgr)(gfxMgr, 1);
    gfxMgr = 0;
  }
  FileSysDestory();
  v12 = CScreenMode::GetInstance();
  ((CScreenMode *)v12)->Restore();
}

// 0x00406310
void PAL3::CheckSystemRequire(HINSTANCE hinst)
{
  char *v2; // edi
  char *v3; // esi
// [IDA_MISID]   _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v5; // esp
  DWORD v6; // esi
  HWND Window; // eax
  char *v8; // [esp-0x10] [ebp-0x116C]
  void *v9; // [esp-0x10] [ebp-0x116C]
  CHAR ClassName[20]; // [esp+0x0] [ebp-0x115C] BYREF
  struct tagRECT rc; // [esp+0x14] [ebp-0x1148] BYREF
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
// [IDA_MISID]   ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v19 = ((void*)0);
// [IDA_MISID]   v18 = ExceptionList;
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
      ((Logger *)&ArgList)->FormatException("RegisterClass Failed.", &path[72], 1094),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((Config *)Buffer)->ReadINIInt(v2, v3);
  v20 = 0;
  ((Config *)Buffer)->FormatSectionPath(filename, v8);
  g_DrvInfo.type = 2;
  g_DrvInfo.subtype = 0;
  ((Config *)Buffer)->ReadSectionAsInt("display", section);
  ((Config *)Buffer)->ReadSectionAsInt("display", "height");
  ((Config *)Buffer)->ReadSectionAsInt("display", "colorbits");
  ((Config *)Buffer)->ReadSectionAsInt("display", "depthbits");
  ((Config *)Buffer)->ReadSectionAsInt("display", "rate");
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
    qmemcpy(v14, ((Logger *)&v17)->FormatException("Window create failed", &path[72], 1152), sizeof(v14));
    _CxxThrowException(v14, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_DrvInfo.hgfxwnd = (unsigned int)Window;
  hWnd = Window;
  v20 = -1;
  todo_408BD0(v9);
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
  int v10; // eax

  bool v12; // cc
  unsigned int v13; // eax

  char v15; // al
  bool v16; // zf
  unsigned int v17; // eax
  char v18; // al
  int v19; // eax
  unsigned int v20; // eax

  g_nCombatMode = (int)GetCommandLineA();
  if ( g_nCombatMode )
  {
    this->ParseCmdLine(CmdLine);
    if ( v3 || (this->ParseCmdLine("softcursor"), v4) )
      g_bPAL3_BFDA91 = 1;
    this->ParseCmdLine("xsnd");
    if ( v6 )
    {
      v7 = g_dwGameFlags;
      LOBYTE(v7) = g_dwGameFlags & 0xFE;
      g_dwGameFlags = v7;
    }
    this->ParseCmdLine("xmusic");
    if ( v8 )
    {
      v9 = g_dwGameFlags;
      LOBYTE(v9) = g_dwGameFlags & 0xFB;
      g_dwGameFlags = v9;
    }
    LOBYTE(v10) = ((PAL3 *)KeyName)->HasCommandLineParam();
    v12 = v10 <= 0;
    v13 = g_dwGameFlags;
    if ( v12 )
      LOBYTE(v13) = g_dwGameFlags & 0xEF;
    else
      LOBYTE(v13) = g_dwGameFlags | 0x10;
    g_dwGameFlags = v13;
    this->ParseCmdLine("motionblur");
    v16 = v15 == 0;
    v17 = g_dwGameFlags;
    if ( v16 )
      LOBYTE(v17) = g_dwGameFlags & 0xF7;
    else
      LOBYTE(v17) = g_dwGameFlags | 8;
    g_dwGameFlags = v17;
    this->ParseCmdLine("scursor");
    if ( v18 )
      UIQuadManager::GetInstance()[7]._tail_000[1] = 1;
    LOBYTE(v19) = ((PAL3 *)"rate")->HasCommandLineParam();
    v12 = v19 <= 60;
    v20 = g_dwGameFlags;
    if ( v12 )
      LOBYTE(v20) = g_dwGameFlags & 0xDF;
    else
      LOBYTE(v20) = g_dwGameFlags | 0x20;
    g_dwGameFlags = v20;
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
      strcpy(Str, GetCommandLineA());
      sprintf(Buffer, aS, lpCmdLine);
      _strlwr(Str);
      _strlwr(Buffer);
      if ( !strstr(Str, Buffer) )
      {
        sprintf(Buffer, (const char *const)&off_583A1C, lpCmdLine);
        if ( !strstr(Str, Buffer) || strlen(Str) != strstr(Str, Buffer) - Str + strlen(Buffer) )
        {
          ((Config *)FileName)->ReadINIInt(v2, v5);
          v9 = 0;
          ((Config *)FileName)->FormatSectionPath(filename, v3);
          ((Config *)FileName)->ReadSectionAsInt("misc", (char *)lpCmdLine);
          v9 = -1;
          todo_408BD0(v4);
        }
      }
    }
  }
}

// 0x004068C0
bool PAL3::HasCommandLineParam()
{
  bool result; // al
  char *v2; // [esp+0x0] [ebp-0x11C]
  char *v3; // [esp+0x0] [ebp-0x11C]
  void *v4; // [esp+0x0] [ebp-0x11C]
  char *v5; // [esp+0x4] [ebp-0x118]
  Config Buffer[7]; // [esp+0xC] [ebp-0x110] BYREF
  int v7; // [esp+0x118] [ebp-0x4]

  result = 0;
  if ( strlen(lpKeyName) < 0x14 )
  {
    ((Config *)Buffer)->ReadINIInt(v2, v5);
    v7 = 0;
    ((Config *)Buffer)->FormatSectionPath(filename, v3);
    ((Config *)Buffer)->ReadSectionAsInt("display", lpKeyName);
    v7 = -1;
    todo_408BD0(v4);
    return 0;
  }
  return result;
}

// 0x00406980
int PAL3::GetCommandLineParam()
{
  LOBYTE(this) = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather;
  if ( !LOBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather)
    && __PAIR16__(BYTE1(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather), 0) == BYTE2(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather)
    && __PAIR16__(HIBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather), 0) == LOBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_pData) )
  {
    ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather = (UIWnd *)(dword_1000000 + 257);
    LOBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_pData) = 0;
  }
  if ( !g_nPartyCount )

  ((CCBSystem *)&g_pCBSystem)->ProcMagicWait((unsigned int)g_nPartyRoles, 1);
  return ((CGameData *)&g_gamefrm)->Load((CUtil *)6);
}

// 0x00406A10
void PAL3::TestCombat()
{
  g_PAL3_Instance.s_drvinfo.depthbits = 10158107;
  g_PAL3_Instance.s_drvinfo.nbackbuf = 6357001;
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[12], "\t");
  g_PAL3_Instance.s_drvinfo.subtype = 16843008;
  g_PAL3_Instance.s_drvinfo.width = 8847494;
  g_PAL3_Instance.s_drvinfo.height = 8978568;
  g_PAL3_Instance.s_drvinfo.colorbits = 852000;
  g_PAL3_Instance.s_drvinfo.stensilbits = 589978;
  g_PAL3_Instance.s_drvinfo.fullscreen = 16777316;
  g_PAL3_Instance.s_drvinfo.refreshrate = 1769729;
  strcpy(g_PAL3_Instance.s_drvinfo.winname, "\r");
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[2], " ");
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[4] = 134;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[6] = 135;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[8] = 136;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[10] = 137;
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[14], "w");
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[16] = 138;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[18] = 139;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[20] = 140;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[22] = 141;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[24] = 142;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[26] = 130;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[28] = 132;
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[30], "p");
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[32], "r");
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[34], "f");
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[36], "k");
  strcpy(&g_PAL3_Instance.s_drvinfo.winname[38], "e");
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[40] = 130;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[42] = 132;
  *(_WORD *)&g_PAL3_Instance.s_drvinfo.winname[44] = 128;
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
    if ( ((std *)&g_PAL3_Instance.m_pAdditiveEffect)->string::max_size() < v11 - 1 )
// [IDA_MISID]       std::_Xlen();
    m_pAdditiveEffect2 = g_PAL3_Instance.m_pAdditiveEffect2;
    if ( g_PAL3_Instance.m_pAdditiveEffect2
      && (v14 = HIBYTE(g_PAL3_Instance.m_pAdditiveEffect2[-1].m_ParamHandle[7])) != 0
      && v14 != -1 )
    {
      if ( v11 == 1 )
      {
        HIBYTE(g_PAL3_Instance.m_pAdditiveEffect2[-1].m_ParamHandle[7]) = v14 - 1;
        ((std *)0)->string::_Tidy();
        goto LABEL_43;
      }
    }
    else
    {
      if ( v11 == 1 )
      {
        ((std *)1)->string::_Tidy();
        goto LABEL_43;
      }
      if ( *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 2) <= 0x1Fu
        && *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 2) >= v12 )
      {
LABEL_42:
        qmemcpy(m_pAdditiveEffect2, (const void *)nVal, v12);
        *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) = v11 - 1;
// [VFTABLE] *((_BYTE *)&g_PAL3_Instance.m_pAdditiveEffect2->__vftable + v12) = 0;
        goto LABEL_43;
      }
      ((std *)1)->string::_Tidy();
    }
    ((GRPinput *)&g_PAL3_Instance.m_pAdditiveEffect)->PollInputState(v12);
    m_pAdditiveEffect2 = g_PAL3_Instance.m_pAdditiveEffect2;
    goto LABEL_42;
  }
  v3 = g_PAL3_Instance.m_pAdditiveEffect2;
  v4 = g_PAL3_Instance.m_pAdditiveEffect2 == 0;
  if ( g_PAL3_Instance.m_pAdditiveEffect2 )
  {
    v5 = HIBYTE(g_PAL3_Instance.m_pAdditiveEffect2[-1].m_ParamHandle[7]);
    if ( v5 && v5 != -1 )
    {
      ((SceneObj *)&g_PAL3_Instance.m_pAdditiveEffect)->UpdateAutoDelete(*((unsigned int *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1));
      v3 = g_PAL3_Instance.m_pAdditiveEffect2;
    }
    v4 = v3 == 0;
    if ( v3 )
    {
      HIBYTE(v3[-1].m_ParamHandle[7]) = -1;
      v3 = g_PAL3_Instance.m_pAdditiveEffect2;
      v4 = g_PAL3_Instance.m_pAdditiveEffect2 == 0;
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
      ((SceneObj *)&g_PAL3_Instance.m_pAdditiveEffect)->UpdateAutoDelete(*((unsigned int *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1));
      v3 = g_PAL3_Instance.m_pAdditiveEffect2;
    }
    if ( v3 )
    {
      HIBYTE(v3[-1].m_ParamHandle[7]) = -1;
      v3 = g_PAL3_Instance.m_pAdditiveEffect2;
    }
  }
  v8 = v3;
  ((std *)&g_PAL3_Instance.m_pAdditiveEffect)->string::_Freeze();
  if ( v8 )
    v9 = (char *)v8 - (char *)g_PAL3_Instance.m_pAdditiveEffect2;
  else
    v9 = 0;
  if ( v6 )
    v6 -= (unsigned int)v8;
  if ( *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) < v9 )
// [IDA_MISID]     std::_Xran();
  ((std *)&g_PAL3_Instance.m_pAdditiveEffect)->string::_Split();
  if ( *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v9 < v6 )
    v6 = *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v9;
  if ( v6 )
  {
    memcpy(
      (char *)g_PAL3_Instance.m_pAdditiveEffect2 + v9,
      (char *)g_PAL3_Instance.m_pAdditiveEffect2 + v6 + v9,
      *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v6 - v9);
    v10 = *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v6;
    if ( ((SceneObj *)&g_PAL3_Instance.m_pAdditiveEffect)->UpdateAutoDelete(*((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) - v6) )
    {
      *((_DWORD *)&g_PAL3_Instance.m_pAdditiveEffect2 + 1) = v10;
// [VFTABLE] *((_BYTE *)&g_PAL3_Instance.m_pAdditiveEffect2->__vftable + v10) = 0;
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

  if ( (*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)gfxMgr + 84))(gfxMgr, &v24, 1) )
  {
    v32 = 0;
    if ( v26 != 3 )
    {
      if ( v26 == 8 )
      {
        isdiskinfo = 32;
LABEL_8:
        v29 = isdiskinfo;
        v2 = ((gbImage2D *)&v31)->CreateImage(v24, v25, isdiskinfo);
        v31.ImgInfo.goal = 0;
        v3 = isdiskinfo * v26 / 8;
        v4 = &v2[v3 * (v27 - 1)];
        v5 = v30;
        if ( v27 > 0 )
        {
          do
          {
            qmemcpy(v4, v5, 4 * (v3 >> 2));
            v6 = &v4[4 * (v3 >> 2)];
            v4 -= v3;
            qmemcpy(v6, &v5[4 * (v3 >> 2)], v3 & 3);
            v5 += v29;
            ++v31.ImgInfo.goal;
          }
          while ( v31.ImgInfo.goal < v27 );
          isdiskinfo = v31.ImgInfo.isdiskinfo;
        }
        (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 88))(gfxMgr);
        ((gbImage2D *)(&g_PAL3_Instance.m_pAdditiveEffect2 + 5))->Release();
        Image = ((gbImage2D *)(&g_PAL3_Instance.m_pAdditiveEffect2 + 5))->CreateImage(v27, v28, 24);
        pBits = v31.pBits;
        v9 = v31.pBits;
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
                  v13 = v9;
                  v14 = Image;
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
                  LOBYTE(v16) = *pBits;
                  pBits += 2;
                  *Image = 8 * v16;
                  LOWORD(v16) = *((_WORD *)pBits - 1);
                  v18 = (unsigned int)v16 >> 2;
                  v19 = Image + 1;
                  *v19 = v18 & 0xF8;
                  LOWORD(v18) = *((_WORD *)pBits - 1);
                  *++v19 = (v18 >> 7) & 0xF8;
                  v16 = v24;
                  Image = v19 + 1;
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
                  LOBYTE(v21) = *pBits;
                  pBits += 2;
                  *Image = 8 * v21;
                  LOWORD(v21) = *((_WORD *)pBits - 1);
                  v23 = Image + 1;
                  *v23++ = ((unsigned int)v21 >> 3) & 0xFC;
                  *v23 = *(pBits - 1) & 0xF8;
                  v21 = v24;
                  Image = v23 + 1;
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
          ((gbImage2D *)(&g_PAL3_Instance.m_pAdditiveEffect2 + 5))->ScaleTo(g_nKeyMap1, g_nKeyMap2);
        ((gbImage2D *)&v31)->Release();
        goto LABEL_34;
      }
      if ( v26 != 9 )
      {
        (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 88))(gfxMgr);
LABEL_34:
        v32 = -1;
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
  PalScriptMgr *v1; // ecx
  RoleSystem *v2; // esi
  scAsmDecoder *v3; // ecx
  void (***v4)(_DWORD, _DWORD); // eax

  g_fDeltaTime = 0.0;
  g_nTickCount = (int)pszName;
  if ( pszName )
  {
    *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = 1;
    ((_Console *)g_pCameraCtrl)->SetActive((int)&((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity);
  }
  ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_S_GAME")->ReadRegistryValue((DWORD)"S_GAME_A", 1);
  ((PalScriptMgr *)v1)->Destroy();
  v2 = &stru_C08160;
  do
  {
    ((RoleSystem *)v2)->NotifyAndSetMode6();
    v2 = (RoleSystem *)((char *)v2 + 8704);
  }
  while ( (int)v2 < (int)&g_pScriptArrayEnd );
  ((scAsmDecoder *)v3)->Execute(0, 1);
  g_nSceneState = 7;
  v4 = (void ( ***)(_DWORD, _DWORD))((CGameData *)&g_gamefrm)->SetMode(0);
  (**v4)(v4, 0);
  g_fFadeAngle = 0.0;
}

// 0x004070A0
bool PAL3::ReadRegistryValue(DWORD dwDisposition, ...)
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
  ((PAL3 *)HKEY_LOCAL_MACHINE)->StartWolf(lpSubKey);
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

// 0x00407180
void PAL3::StartWolf(HKEY hKey, CHAR *lpSubKey)
{
  RegOpenKeyExA(hKey, lpSubKey, 0, 0x20019u, (PHKEY)&lpSubKey);
  RegCloseKey((HKEY)lpSubKey);
}

// 0x004071C0
void PAL3::EndWolf(int nVal)
{
  LONG *p_right; // esi
  PalScriptMgr *v2; // ecx
  float v3; // eax
  void ( ***v4)(_DWORD, int); // eax
  PalScriptMgr *v5; // ecx
  int v6; // eax
  CScreenMode *v7; // ecx
  PtrArray *v8; // eax
  int v9; // eax
  CScreenMode *v10; // ecx
  PtrArray *SoundList; // eax
  int v12; // [esp-0x4] [ebp-0x18]
  int v13; // [esp-0x4] [ebp-0x18]
  int nSkillGDBID[5]; // [esp+0x0] [ebp-0x14]
  void *retaddr; // [esp+0x14] [ebp+0x0]

  p_right = &((RoleSystem *)&stru_C08160)->m_FrameA.m_rect.right;
  do
  {
    ((RoleSystem *)(p_right - 316))->Notify();
    *p_right = 2;
    p_right += 2176;
  }
  while ( (int)p_right < (int)dword_C10E50 );
  if ( g_nTickCount )
  {
    nSkillGDBID[0] = 0;
    ((PalScriptMgr *)v2)->Destroy();
    g_fDeltaTime = v3;
  }
  else
  {
    g_nSceneState = 2;
    v4 = (void ( ***)(_DWORD, int))((CGameData *)&g_gamefrm)->SetMode(0);
    (**v4)(v4, 1);
    if ( retaddr == (void *)-1 )
    {
      ((PalScriptMgr *)v5)->Destroy();
      v13 = v9;
      SoundList = ((CScreenMode *)v10)->GetSoundList();
      ((PtrArray *)SoundList)->SetResolution(0, v13);
    }
    else
    {
      ((PalScriptMgr *)v5)->Destroy();
      v12 = v6;
      v8 = ((CScreenMode *)v7)->GetSoundList();
      ((PtrArray *)v8)->SetResolution(0, v12);
      if ( (unsigned int)g_nWolfIndex < 4 )
      {
        nSkillGDBID[0] = 80015;
        nSkillGDBID[1] = 83012;
        nSkillGDBID[2] = 8153;
        nSkillGDBID[3] = 8154;
        ((PalScriptMgr *)nSkillGDBID[g_nWolfIndex])->HandleGetItem();
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
  v1 = (void ( ***)(_DWORD, _DWORD))((CGameData *)&g_gamefrm)->SetMode(0);
  (**v1)(v1, 0);
}

// 0x00407300
void PAL3::EndHideFight()
{
  void ( ***v1)(_DWORD, int); // eax

  g_nSceneState = 2;
  v1 = (void ( ***)(_DWORD, int))((CGameData *)&g_gamefrm)->SetMode(0);
  (**v1)(v1, 1);
}

// 0x00407320
void PAL3::StartCombat(int monsterid, Role *side, char pMonster)
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
  int v13; // edi
  int v14; // eax
  char *v15; // esi
  CScreenMode *Instance; // eax
  int v17; // [esp+0x0] [ebp-0x11C] BYREF
  char Buffer[256]; // [esp+0xC] [ebp-0x110] BYREF
  int *v19; // [esp+0x10C] [ebp-0x10]
  int v20; // [esp+0x118] [ebp-0x4]

  v20 = 0;
  v19 = &v17;
  ((PAL3 *)v4)->UIPostProcess();
  v5 = g_pRoleSystem;
  if ( g_pRoleSystem )
  {
    v6 = (RoleSystem *)UISceneUpdate();
    RolePtr = ((RoleSystem *)v6)->GetRolePtr(*(_DWORD *)v5->m_partyActor.m_szTexture);
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
    sprintf(Buffer, &dir[24], v14, v13 + 32);
    ((PalScript *)g_ScriptSlots)->SetDirectory(Buffer);
    sprintf(Buffer, &dir[20], v11);
    if ( !((PalScript *)g_ScriptSlots)->FindSaveStateString((PalScript *)Buffer, (char *)&stru_C11720, (char *)0x20, v17) )
      ((PalScript *)g_ScriptSlots)->FindSaveStateString((PalScript *)&dir[12], (char *)&stru_C11720, (char *)0x20, v17);
    ((PalScript *)g_ScriptSlots)->SetDirectory(dir);
    if ( ((PalScript *)g_ScriptSlots)->FindSaveStateString(&stru_C11720, Buffer, (char *)0x100, v17) )
      ((PalScript *)&stru_C11720)->m_bEnabled = atoi(Buffer);
    else
      ((PalScript *)&stru_C11720)->m_bEnabled = 1;
    if ( monsterid == 1 )
      *(_DWORD *)&((PalScript *)&stru_C11720)->_todo_024 = 2;
    else
      *(_DWORD *)&((PalScript *)&stru_C11720)->_todo_024 = monsterid == 2;
    ((PalScript *)&stru_C11720)->_todo_034 = (int)side;
    BYTE1(((PalScript *)&stru_C11720)->_todo_48) = pMonster;
    if ( ((CCBSystem *)&g_pCBSystem)->ProcMagicWait((unsigned int)g_nPartyRoles, 0) )
    {
      if ( !pMonster || !CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v15 = (char *)UISceneUpdate();
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->PlayCombatMusic(v15);
      }
      ((CGameData *)&g_gamefrm)->Load((CUtil *)6);
    }
  }
}

// 0x00407560
char PAL3::StartCombatFromNPC(int tmp, Role *side)
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
  strcpy(v5, &dir[32]);
  v6 = 1;
  v11 = 1;
  v9 = -1;
  v7 = 0;
  v12 = 0;
  v10 = 0;
  qmemcpy(v13, pNPCInfo, sizeof(v13));
  if ( g_nSceneTransitionParam2 )
    LOBYTE(v13[32]) = 6;
  ((PAL3 *)v13[29])->UpdateSubsystems();
  ((PAL3 *)pdwVal)->StartCombat(tmp, side, 0);
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
  int v7; // [esp-0x8] [ebp-0x2C]
  int pPoint; // [esp+0x8] [ebp-0x1C] BYREF
  int v9; // [esp+0xC] [ebp-0x18]
  int v10; // [esp+0x10] [ebp-0x14]
  int p_DWORD; // [esp+0x14] [ebp-0x10] BYREF
  int v12; // [esp+0x18] [ebp-0xC]
  int v13; // [esp+0x1C] [ebp-0x8]
  int v14; // [esp+0x20] [ebp-0x4]

  v1 = 0;
  if ( ((UIScene *)&dir[36])->ProcessInput(0) )
  {
    pPoint = 6308;
    v9 = 6309;
    v10 = 6310;
    v12 = 0;
    v13 = 0;
    p_pPoint = &pPoint;
    do
    {
      p_DWORD = *p_pPoint;
      if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD) )
        break;
      ++v1;
      ++p_pPoint;
    }
    while ( v1 < 3 );
  }
  else
  {
    v3 = g_pRoleSystem;
    v7 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
    v4 = (RoleSystem *)UISceneUpdate();
    RolePtr = ((RoleSystem *)v4)->GetRolePtr(v7);
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
bool PAL3::IfHideFightSucceed(bool bFlag)
{
  PAL3 *v1; // ecx
  bool result; // al
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax

  result = bFlag - 2;
  if ( bFlag == 2 )
  {
    if ( (g_dwGameFlags & 1) != 0 )
    {
      Instance = CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
      ((gbAudioManager *)AudioManager)->DetachAll3D();
    }
    ((PAL3 *)v1)->UIPostProcess();
    ((RoleSystem *)&g_pRoleSystem)->Notify();
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
  ((PalScript *)&g_UIScript)->Create(0, &pRect, 0);
  ((UIScene *)&g_UIScript)->LoadResource("ui\\scene\\tiao");
  ((UIScene *)&g_UIScript)->SetController(1082130432);
  ((PalScript *)&g_UIScript)->ShowWindow(0);
  ((UINote *)dword_BFDAB0)->Create(1, (int)&pRect, 0, "ui\\flex\\note");
  ((UIScene *)dword_BFDAB0)->SetState();
  dword_C042F8 = 1101838418;
  dword_C042FC = 0;
  g_nPtrArray_C04300 = -1038795408;
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
  return this->FullInit();
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
  void *v21; // edx
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
  int v32; // eax
  int n; // eax
  int v34; // ecx
  int v35; // edx
  char *v36; // esi
  int v37; // edi
  int v38; // eax
  int v39; // ebp
  int v40; // eax
  char *v41; // edi
  int v42; // eax
  char *ii; // eax
  _DWORD *v44; // edx
  char *v45; // esi
  int v46; // edi
  int v47; // eax
  int v48; // ebp
  int v49; // eax
  char *v50; // edi
  int v51; // eax
  char *jj; // eax
  _DWORD *v53; // ecx
  char *v54; // esi
  int v55; // edi
  int v56; // eax
  int v57; // ebp
  int v58; // eax
  char *v59; // edi
  int v60; // eax
  char *kk; // eax
  _DWORD *v62; // ecx
  char *v63; // esi
  int v64; // edi
  int v65; // eax
  int v66; // ebp
  int v67; // eax
  char *v68; // edi
  int v69; // eax
  char *mm; // eax
  _DWORD *v71; // ecx
  int v72; // eax
  int nn; // eax
  int v74; // ecx
  int v75; // edx
  char *v76; // esi
  int v77; // edi
  int v78; // eax
  int v79; // ebp
  int v80; // eax
  char *v81; // edi
  int v82; // eax
  char *i1; // eax
  _DWORD *v84; // ecx
  char *v85; // esi
  int v86; // edi
  int v87; // eax
  int v88; // ebp
  int v89; // eax
  char *v90; // edi
  int v91; // eax
  char *i2; // eax
  _DWORD *v93; // ecx
  char *v94; // esi
  int v95; // edi
  int v96; // eax
  int v97; // ebp
  int v98; // eax
  char *v99; // edi
  int v100; // eax
  char *i3; // eax
  _DWORD *v102; // ecx
  char *v103; // esi
  int v104; // edi
  int v105; // eax
  int v106; // ebp
  int v107; // eax
  char *v108; // edi
  int v109; // eax
  char *i4; // eax
  _DWORD *v111; // ecx
  int v112; // ebp
  int i5; // eax
  int v114; // ecx
  int v115; // edx
  char *v116; // esi
  int v117; // edx
  int v118; // edi
  int v119; // eax
  char *v120; // ebp
  int v121; // edx
  char *v122; // eax
  _DWORD *v123; // edx
  char *v124; // esi
  int v125; // ebp
  int v126; // edx
  int v127; // eax
  char *v128; // eax
  char *v129; // ebp
  char *v130; // edi
  int v131; // eax
  char *v132; // eax
  _DWORD *v133; // ecx
  char *v134; // esi
  int v135; // ebp
  int v136; // edx
  int v137; // eax
  char *v138; // eax
  char *v139; // ebp
  char *v140; // edi
  int v141; // eax
  char *v142; // eax
  _DWORD *v143; // ecx
  int i6; // ecx
  int result; // eax
  int nSlotIndex; // [esp+0x0] [ebp-0x38]
  int pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  void *pNewBuffer; // [esp+0x10] [ebp-0x28]
  int pNewBuffer; // [esp+0x10] [ebp-0x28]
  char *pNewBuffer; // [esp+0x10] [ebp-0x28]
  char *pSceneName; // [esp+0x14] [ebp-0x24]
  int pSceneName; // [esp+0x14] [ebp-0x24]
  int pRoleTriple[3]; // [esp+0x18] [ebp-0x20] BYREF
  _DWORD aSceneData[5]; // [esp+0x24] [ebp-0x14] BYREF

  memset(g_SaveSlotFlags, 0, sizeof(g_SaveSlotFlags));
  if ( g_pCurrentScript )
  {
    (*(void ( **)(PalScript *, int))g_pCurrentScript->m_bLoadSceneScript)(g_pCurrentScript, 1);
    g_pCurrentScript = 0;
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
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Reset();
  ((RoleSystem *)&stru_C059A0)->m_fMoveRole = ((RoleSystem *)&stru_C059A0)->m_fMoveTargetZ;
  g_nFrameRate = 35;
  p_m_pData = &g_SceneMgrPrefix.m_pData;
  do
  {
    *p_m_pData = *(p_m_pData - 1);
    p_m_pData += 4;
  }
  while ( (int)p_m_pData < (int)&Buffer.m_wndcolor );
  g_nSceneTransitionParam2 = 0;
  memset(&g_nScriptEventParam, 0, 0x20u);
  g_nCurrentEventId = 31;
  g_fFadeTimer = 0.0;
  memset(&Buffer, 0, 0x1B80u);
  aSceneData[0] = &g_pfnUpdateFuncs[4];
  aSceneData[1] = &g_pfnUpdateFuncs[3];
  aSceneData[2] = &g_pfnUpdateFuncs[2];
  aSceneData[3] = &g_pfnUpdateFuncs[1];
  aSceneData[4] = g_pfnUpdateFuncs;
  pNewBuffer = 0;
  v3 = (char *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[36] + 2;
  v4 = (const char **)aSceneData;
  do
  {
    v5 = *v4;
    ((Camera *)(v3 - 174))->InitFromScene(*v4);
    strncpy(v3, v5, 0x1Fu);
    *(_DWORD *)(v3 + 1090) = 1;
    *(_DWORD *)(v3 + 1086) = 1;
    *(_DWORD *)(v3 + 458) = 0;
    *(v3 - 1) = -1;
    *(v3 - 2) = pNewBuffer;
    v3 += 8704;
    ++v4;
    ++pNewBuffer;
  }
  while ( (int)v3 < (int)&g_pRoleSystemArrayEnd );
  ((Camera *)&g_RoleSystemMain)->InitFromScene((const char *)&g_pszScene2);
  g_RoleSystemMain.m_nFacing = 5;
  v6 = nVal;
  strcpy(&g_RoleSystemMain.m_nAnimState, (const char *)&g_pszScene2);
  g_RoleSystemMain.m_FrameA.m_rect.right = 0;
  *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] = 0;
  *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[8] = 1;
  g_RoleSystemMain.m_nActionState = -1;
  ((NPC *)v6)->SetRoleMode();
  ((Camera *)&g_RoleSystemExtra1)->InitFromScene((const char *)&g_pszScene1);
  strcpy(&g_RoleSystemExtra1.m_nAnimState, (const char *)&g_pszScene1);
  g_RoleSystemExtra1.m_FrameA.m_rect.right = 1;
  *(_DWORD *)&g_RoleSystemExtra1.m_partyActor.m_szTexture[4] = 0;
  ((Camera *)&g_RoleSystemExtra0)->InitFromScene((const char *)&g_pszDefaultScene);
  strcpy(&g_RoleSystemExtra0.m_nAnimState, (const char *)&g_pszDefaultScene);
  g_RoleSystemExtra0.m_FrameA.m_rect.right = 1;
  *(_DWORD *)&g_RoleSystemExtra0.m_partyActor.m_szTexture[4] = 0;
  ((CameraSystem *)&((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity)->BindToRoleSlot();
  g_nCurrentRoleSlot = 0;
  ((_Console *)g_pCameraCtrl)->SetActive((int)&((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity);
  ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather = (UIWnd *)1;
  LOBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_pData) = 0;
  BYTE2(Buffer.m_fMoveTargetX) = 3;
  BYTE2(Buffer.m_StaticSlotArray.m_bfocus) = 5;
  *((_BYTE *)&Buffer.m_partyUI3._todo_05C + 45) = 1;
  g_SceneMgr = 2;
  BYTE2(((RoleSystem *)&stru_C059A0)->m_fMoveTargetX) = 4;
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
    ((NPC *)i)->Create();
    ((NPC *)i)->Init();
  }
  memset32(g_nRoleInitLevel, 20, 6u);
  *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 3) = 2224;
  LODWORD(Buffer.m_partyActor.m_fAngleDeg) = 10;
  *((_DWORD *)&Buffer.m_partyActor.m_nAnimFrame + 1) = 0;
  *((_DWORD *)&Buffer.m_partyActor.m_nAnimFrame + 2) = 0;
  Buffer.m_partyActor.m_pParticleData = 0;
  *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 1) = 0;
  *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 2) = 0;
  *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 3) = 0;
  *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 4) = 0;
  *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 5) = 0;
  Buffer.m_partyActor.m_fAnimDelta = 0.0;
  Buffer.m_partyActor.m_dwMatMsg[0] = 0;
  Buffer.m_partyActor.m_dwMatMsg[1] = 0;
  Buffer.m_partyActor.m_dwMatMsg[2] = 0;
  Buffer.m_partyActor.m_dwMatMsg[3] = 0;
  Buffer.m_partyActor.m_dwMatMsg[4] = 0;
  Buffer.m_partyActor.m_dwMatMsg[5] = 0;
  Buffer.m_partyActor.m_dwMatMsg[6] = 0;
  Buffer.m_partyActor.m_dwMatMsg[7] = 0;
  Buffer.m_partyActor.m_dwMatMsg[8] = 0;
  pRoleTriple[0] = 301;
  pRoleTriple[1] = 0;
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(301);
  m_pData = g_SceneMgrPrefix.m_pData;
  pRoleTriple[2] = RoleNum;
  if ( (int)(g_SceneMgrPrefix.m_nCapacity - (unsigned int)g_SceneMgrPrefix.m_pData) / 12 )
  {
    ((Array *)&g_SceneMgrPrefix)->Insert(g_SceneMgrPrefix.m_pData, g_SceneMgrPrefix.m_pData);
    ((Array *)&g_SceneMgrPrefix)->Erase((int)g_SceneMgrPrefix.m_pData, 1 - (g_SceneMgrPrefix.m_pData - m_pData) / 12);
    for ( j = g_SceneMgrPrefix.m_pData; m_pData != j; v18[2] = pRoleTriple[2] )
    {
      v18 = m_pData;
      m_pData += 12;
      *v18 = pRoleTriple[0];
      v18[1] = pRoleTriple[1];
    }
    g_SceneMgrPrefix.m_pData += 12;
  }
  else
  {
    if ( (unsigned int)((Array *)&g_SceneMgrPrefix)->Size() <= 1 )
      v10 = 1;
    else
      v10 = ((Array *)&g_SceneMgrPrefix)->Size();
    v11 = ((Array *)&g_SceneMgrPrefix)->Size();
    v12 = v10 + v11 < 0;
    v13 = v10 + v11;
    v14 = v10 + v11;
    if ( v12 )
      v14 = 0;
    v15 = (char *)operator new(12 * v14);
    pNewBuffer = ((Array *)&g_SceneMgrPrefix)->Insert((void *)g_SceneMgrPrefix.m_nSize, m_pData);
    ((Array *)&g_SceneMgrPrefix)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_SceneMgrPrefix)->Insert(m_pData, g_SceneMgrPrefix.m_pData);
    nullsub_2(g_SceneMgrPrefix.m_nSize, g_SceneMgrPrefix.m_pData);
    operator delete((void *)g_SceneMgrPrefix.m_nSize);
    g_SceneMgrPrefix.m_nCapacity = (int)&v15[12 * v13];
    v16 = ((Array *)&g_SceneMgrPrefix)->Size();
    g_SceneMgrPrefix.m_nSize = (int)v15;
    g_SceneMgrPrefix.m_pData = &v15[12 * v16 + 12];
  }
  Buffer.m_partyActor.m_fActionAssignParam = 0.0;
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[4] = 1;
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[8] = Role::CalcXueJianInit(1);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[12] = Role::CalcLongKuiInit(*(int *)&Buffer.m_partyActor.m_szTexture[4]);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[16] = Role::CalcZiXuanInit(*(int *)&Buffer.m_partyActor.m_szTexture[4]);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[20] = Role::CalcChangQingInit(*(int *)&Buffer.m_partyActor.m_szTexture[4]);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[24] = Role::CalcHuaYingInit(*(int *)&Buffer.m_partyActor.m_szTexture[4]);
  LODWORD(Buffer.m_partyActor.m_fNormX) = 3;
  LODWORD(Buffer.m_partyActor.m_vecLocalPos.x) = 3;
  LODWORD(Buffer.m_partyActor.m_fNormZ) = 3;
  LODWORD(Buffer.m_partyActor.m_vecLocalPos.z) = 3;
  LODWORD(Buffer.m_partyActor.m_fDistAccum) = 3;
  *((_DWORD *)&Buffer.m_partyActor.m_vecLocalPos + 3) = 3;
  LODWORD(Buffer.m_partyActor.m_fNormY) = 2;
  LODWORD(Buffer.m_partyActor.m_vecLocalPos.y) = 2;
  *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 2) = 2;
  *(_DWORD *)&Buffer.m_partyActor.m_nActionType = 2;
  LODWORD(Buffer.m_partyActor.m_fSpeed) = 6;
  *((_DWORD *)&Buffer.m_partyActor.m_vecLocalPos + 4) = 6;
  *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 1) = 1;
  *(_DWORD *)&Buffer.m_partyActor.m_nAnimState = 1;
  ((RoleSystem *)&Buffer)->RecalcAggregatedStats(1);
  for ( k = 972; k < 1020; k += 4 )
  {
// [VFTABLE] v20 = *(int *)((char *)&Buffer.__vftable + k);
    v21 = *(void **)((char *)&g_nSceneFlags.m_pDataStart + k);
    if ( v20 < (int)v21 )
    {
      if ( v20 <= 0 )
// [VFTABLE] *(vtbl_0056AE2C **)((char *)&Buffer.__vftable + k) = 0;
    }
    else
    {
// [VFTABLE] *(vtbl_0056AE2C **)((char *)&Buffer.__vftable + k) = v21;
    }
  }
  Buffer.m_teamSlots[190] = 0;
  Buffer.m_teamSlots[191] = 0;
  Buffer.m_teamSlots[192] = 0;
  Buffer.m_teamSlots[193] = 0;
  Buffer.m_teamSlots[194] = 0;
  Buffer.m_teamSlots[195] = 0;
  Buffer.m_teamSlots[196] = 0;
  Buffer.m_teamSlots[197] = 0;
  Buffer.m_teamSlots[198] = 0;
  Buffer.m_teamSlots[199] = 0;
  Buffer.m_teamSlots[200] = 0;
  Buffer.m_teamSlots[201] = 0;
  Buffer.m_teamSlots[202] = 0;
  Buffer.m_teamSlots[203] = 0;
  Buffer.m_teamSlots[204] = 0;
  Buffer.m_teamSlots[205] = 82201;
  Buffer.m_teamSlots[206] = 1;
  Buffer.m_teamSlots[207] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(82201);
  pRoleTriple[0] = 321;
  pRoleTriple[1] = 0;
  v22 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(321);
  v23 = g_RoleTeamArray.m_pData;
  pRoleTriple[2] = v22;
  if ( (int)(g_RoleTeamArray.m_nCapacity - (unsigned int)g_RoleTeamArray.m_pData) / 12 )
  {
    ((Array *)&g_RoleTeamArray)->Insert(g_RoleTeamArray.m_pData, g_RoleTeamArray.m_pData);
    ((Array *)&g_RoleTeamArray)->Erase((int)g_RoleTeamArray.m_pData, 1 - (g_RoleTeamArray.m_pData - v23) / 12);
    for ( m = g_RoleTeamArray.m_pData; v23 != m; v31[2] = pRoleTriple[2] )
    {
      v31 = v23;
      v23 += 12;
      *v31 = pRoleTriple[0];
      v31[1] = pRoleTriple[1];
    }
    g_RoleTeamArray.m_pData += 12;
  }
  else
  {
    if ( (unsigned int)((Array *)&g_RoleTeamArray)->Size() <= 1 )
      v24 = 1;
    else
      v24 = ((Array *)&g_RoleTeamArray)->Size();
    v25 = ((Array *)&g_RoleTeamArray)->Size();
    v12 = v24 + v25 < 0;
    v26 = v24 + v25;
    v27 = v24 + v25;
    if ( v12 )
      v27 = 0;
    v28 = (char *)operator new(12 * v27);
    pNewBuffer = ((Array *)&g_RoleTeamArray)->Insert((void *)g_RoleTeamArray.m_nSize, v23);
    ((Array *)&g_RoleTeamArray)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_RoleTeamArray)->Insert(v23, g_RoleTeamArray.m_pData);
    nullsub_2(g_RoleTeamArray.m_nSize, g_RoleTeamArray.m_pData);
    operator delete((void *)g_RoleTeamArray.m_nSize);
    g_RoleTeamArray.m_nCapacity = (int)&v28[12 * v26];
    v29 = ((Array *)&g_RoleTeamArray)->Size();
    g_RoleTeamArray.m_nSize = (int)v28;
    g_RoleTeamArray.m_pData = &v28[12 * v29 + 12];
  }
  Buffer.m_teamSlots[162] = 0;
  Buffer.m_teamSlots[135] = 1;
  Buffer.m_teamSlots[136] = ((Role *)1)->CalcXueJianInit(1);
  Buffer.m_teamSlots[137] = ((Role *)1)->CalcLongKuiInit(Buffer.m_teamSlots[135]);
  Buffer.m_teamSlots[138] = ((Role *)1)->CalcZiXuanInit(Buffer.m_teamSlots[135]);
  Buffer.m_teamSlots[139] = ((Role *)1)->CalcChangQingInit(Buffer.m_teamSlots[135]);
  v32 = ((Role *)1)->CalcHuaYingInit(Buffer.m_teamSlots[135]);
  Buffer.m_teamSlots[227] = 2;
  Buffer.m_teamSlots[143] = 2;
  Buffer.m_teamSlots[229] = 2;
  Buffer.m_teamSlots[145] = 2;
  Buffer.m_teamSlots[140] = v32;
  Buffer.m_teamSlots[230] = 3;
  Buffer.m_teamSlots[146] = 3;
  Buffer.m_teamSlots[225] = 5;
  Buffer.m_teamSlots[141] = 5;
  Buffer.m_teamSlots[226] = 4;
  Buffer.m_teamSlots[142] = 4;
  Buffer.m_teamSlots[228] = 4;
  Buffer.m_teamSlots[144] = 4;
  Buffer.m_teamSlots[231] = 5;
  Buffer.m_teamSlots[147] = 5;
  ((RoleSystem *)&Buffer.m_fMoveTargetY)->RecalcAggregatedStats(1);
  for ( n = 972; n < 1020; n += 4 )
  {
    v34 = *(int *)((char *)&Buffer.m_fMoveTargetY + n);
    v35 = *(int *)((char *)&Buffer.m_nMoveReset + n);
    if ( v34 < v35 )
    {
      if ( v34 <= 0 )
        *(int *)((char *)&Buffer.m_fMoveTargetY + n) = 0;
    }
    else
    {
      *(int *)((char *)&Buffer.m_fMoveTargetY + n) = v35;
    }
  }
  Buffer.m_configData[0] = 0;
  Buffer.m_configData[1] = 0;
  Buffer.m_configData[2] = 0;
  Buffer.m_configData[3] = 0;
  Buffer.m_configData[4] = 0;
  Buffer.m_configData[5] = 0;
  Buffer.m_configData[6] = 0;
  Buffer.m_configData[7] = 0;
  Buffer.m_configData[8] = 0;
  Buffer.m_configData[9] = 0;
  Buffer.m_configData[10] = 0;
  Buffer.m_configData[11] = 0;
  Buffer.m_configData[12] = 0;
  Buffer.m_configData[13] = 0;
  Buffer.m_configData[14] = 0;
  Buffer.m_configData[15] = 82101;
  Buffer.m_configData[16] = 1;
  Buffer.m_configData[17] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(82101);
  pRoleTriple[0] = 4301;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(4301);
  v36 = g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    ((Array *)&g_nSceneFlags)->Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    ((Array *)&g_nSceneFlags)->Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v36) / 12);
    for ( ii = g_nSceneFlags.m_pData; v36 != ii; v44[2] = pRoleTriple[2] )
    {
      v44 = v36;
      v36 += 12;
      *v44 = pRoleTriple[0];
      v44[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v37 = ((Array *)&g_nSceneFlags)->Size();
    else
      v37 = 1;
    v38 = ((Array *)&g_nSceneFlags)->Size();
    v12 = v37 + v38 < 0;
    v39 = v37 + v38;
    v40 = v37 + v38;
    if ( v12 )
      v40 = 0;
    v41 = (char *)operator new(12 * v40);
    pNewBuffer = ((Array *)&g_nSceneFlags)->Insert((void *)g_nSceneFlags.m_nSize, v36);
    ((Array *)&g_nSceneFlags)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_nSceneFlags)->Insert(v36, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v41[12 * v39];
    v42 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneFlags.m_nSize = (int)v41;
    g_nSceneFlags.m_pData = &v41[12 * v42 + 12];
  }
  pRoleTriple[0] = 4302;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(4302);
  v45 = g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    ((Array *)&g_nSceneFlags)->Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    ((Array *)&g_nSceneFlags)->Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v45) / 12);
    for ( jj = g_nSceneFlags.m_pData; v45 != jj; v53[2] = pRoleTriple[2] )
    {
      v53 = v45;
      v45 += 12;
      *v53 = pRoleTriple[0];
      v53[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v46 = ((Array *)&g_nSceneFlags)->Size();
    else
      v46 = 1;
    v47 = ((Array *)&g_nSceneFlags)->Size();
    v12 = v46 + v47 < 0;
    v48 = v46 + v47;
    v49 = v46 + v47;
    if ( v12 )
      v49 = 0;
    v50 = (char *)operator new(12 * v49);
    pNewBuffer = ((Array *)&g_nSceneFlags)->Insert((void *)g_nSceneFlags.m_nSize, v45);
    ((Array *)&g_nSceneFlags)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_nSceneFlags)->Insert(v45, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v50[12 * v48];
    v51 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneFlags.m_nSize = (int)v50;
    g_nSceneFlags.m_pData = &v50[12 * v51 + 12];
  }
  pRoleTriple[0] = 311;
  pRoleTriple[1] = SUBGROUP_FLAG_MASK;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(311);
  v54 = g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    ((Array *)&g_nSceneFlags)->Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    ((Array *)&g_nSceneFlags)->Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v54) / 12);
    for ( kk = g_nSceneFlags.m_pData; v54 != kk; v62[2] = pRoleTriple[2] )
    {
      v62 = v54;
      v54 += 12;
      *v62 = pRoleTriple[0];
      v62[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v55 = ((Array *)&g_nSceneFlags)->Size();
    else
      v55 = 1;
    v56 = ((Array *)&g_nSceneFlags)->Size();
    v12 = v55 + v56 < 0;
    v57 = v55 + v56;
    v58 = v55 + v56;
    if ( v12 )
      v58 = 0;
    v59 = (char *)operator new(12 * v58);
    pNewBuffer = ((Array *)&g_nSceneFlags)->Insert((void *)g_nSceneFlags.m_nSize, v54);
    ((Array *)&g_nSceneFlags)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_nSceneFlags)->Insert(v54, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v59[12 * v57];
    v60 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneFlags.m_nSize = (int)v59;
    g_nSceneFlags.m_pData = &v59[12 * v60 + 12];
  }
  pRoleTriple[0] = 312;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(312);
  v63 = g_nSceneFlags.m_pData;
  if ( (int)(g_nSceneFlags.m_nCapacity - (unsigned int)g_nSceneFlags.m_pData) / 12 )
  {
    ((Array *)&g_nSceneFlags)->Insert(g_nSceneFlags.m_pData, g_nSceneFlags.m_pData);
    ((Array *)&g_nSceneFlags)->Erase((int)g_nSceneFlags.m_pData, 1 - (g_nSceneFlags.m_pData - v63) / 12);
    for ( mm = g_nSceneFlags.m_pData; v63 != mm; v71[2] = pRoleTriple[2] )
    {
      v71 = v63;
      v63 += 12;
      *v71 = pRoleTriple[0];
      v71[1] = pRoleTriple[1];
    }
    g_nSceneFlags.m_pData += 12;
  }
  else
  {
    if ( g_nSceneFlags.m_nSize && (unsigned int)((int)&g_nSceneFlags.m_pData[-g_nSceneFlags.m_nSize] / 12) > 1 )
      v64 = ((Array *)&g_nSceneFlags)->Size();
    else
      v64 = 1;
    v65 = ((Array *)&g_nSceneFlags)->Size();
    v12 = v64 + v65 < 0;
    v66 = v64 + v65;
    v67 = v64 + v65;
    if ( v12 )
      v67 = 0;
    v68 = (char *)operator new(12 * v67);
    pNewBuffer = ((Array *)&g_nSceneFlags)->Insert((void *)g_nSceneFlags.m_nSize, v63);
    ((Array *)&g_nSceneFlags)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_nSceneFlags)->Insert(v63, g_nSceneFlags.m_pData);
    nullsub_2(g_nSceneFlags.m_nSize, g_nSceneFlags.m_pData);
    operator delete((void *)g_nSceneFlags.m_nSize);
    g_nSceneFlags.m_nCapacity = (int)&v68[12 * v66];
    v69 = ((Array *)&g_nSceneFlags)->Size();
    g_nSceneFlags.m_nSize = (int)v68;
    g_nSceneFlags.m_pData = &v68[12 * v69 + 12];
  }
  Buffer.m_teamSlotsB[158] = 14;
  Buffer.m_teamSlotsB[185] = 5594;
  Buffer.m_teamSlotsB[159] = ((Role *)2)->CalcXueJianInit(14);
  Buffer.m_teamSlotsB[160] = ((Role *)2)->CalcLongKuiInit(Buffer.m_teamSlotsB[158]);
  Buffer.m_teamSlotsB[161] = ((Role *)2)->CalcZiXuanInit(Buffer.m_teamSlotsB[158]);
  Buffer.m_teamSlotsB[162] = ((Role *)2)->CalcChangQingInit(Buffer.m_teamSlotsB[158]);
  v72 = ((Role *)2)->CalcHuaYingInit(Buffer.m_teamSlotsB[158]);
  Buffer.m_configData[39] = 3;
  Buffer.m_teamSlotsB[168] = 3;
  Buffer.m_teamSlotsB[163] = v72;
  Buffer.m_configData[40] = 6;
  Buffer.m_teamSlotsB[169] = 6;
  Buffer.m_configData[35] = 4;
  Buffer.m_teamSlotsB[164] = 4;
  Buffer.m_configData[36] = 5;
  Buffer.m_teamSlotsB[165] = 5;
  Buffer.m_configData[37] = 4;
  Buffer.m_teamSlotsB[166] = 4;
  Buffer.m_configData[38] = 2;
  Buffer.m_teamSlotsB[167] = 2;
  Buffer.m_configData[41] = 5;
  Buffer.m_teamSlotsB[170] = 5;
  ((RoleSystem *)Buffer.m_teamSlotsB)->RecalcAggregatedStats(1);
  for ( nn = 243; nn < 255; ++nn )
  {
    v74 = Buffer.m_teamSlotsB[nn];
    v75 = Buffer.m_teamSlotsB[nn - 12];
    if ( v74 < v75 )
    {
      if ( v74 <= 0 )
        Buffer.m_teamSlotsB[nn] = 0;
    }
    else
    {
      Buffer.m_teamSlotsB[nn] = v75;
    }
  }
  g_SceneMgr.m_partyInitData[10] = 0;
  g_SceneMgr.m_partyInitData[11] = 0;
  g_SceneMgr.m_partyInitData[12] = 0;
  g_SceneMgr.m_partyInitData[13] = 0;
  g_SceneMgr.m_partyInitData[14] = 0;
  g_SceneMgr.m_partyInitData[15] = 0;
  g_SceneMgr.m_partyInitData[16] = 0;
  g_SceneMgr.m_partyInitData[17] = 0;
  g_SceneMgr.m_partyInitData[18] = 0;
  g_SceneMgr.m_partyInitData[19] = 0;
  g_SceneMgr.m_partyInitData[20] = 0;
  g_SceneMgr.m_partyInitData[21] = 0;
  g_SceneMgr.m_partyInitData[22] = 0;
  g_SceneMgr.m_partyInitData[23] = 0;
  g_SceneMgr.m_partyInitData[24] = 0;
  g_SceneMgr.m_partyInitData[25] = 82301;
  g_SceneMgr.m_partyInitData[26] = 1;
  g_SceneMgr.m_partyInitData[27] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(82301);
  pRoleTriple[0] = 4401;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(4401);
  v76 = g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    ((Array *)&g_SceneArray)->Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    ((Array *)&g_SceneArray)->Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v76) / 12);
    for ( i1 = g_SceneArray.m_pData; v76 != i1; v84[2] = pRoleTriple[2] )
    {
      v84 = v76;
      v76 += 12;
      *v84 = pRoleTriple[0];
      v84[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v77 = ((Array *)&g_SceneArray)->Size();
    else
      v77 = 1;
    v78 = ((Array *)&g_SceneArray)->Size();
    v12 = v77 + v78 < 0;
    v79 = v77 + v78;
    v80 = v77 + v78;
    if ( v12 )
      v80 = 0;
    v81 = (char *)operator new(12 * v80);
    pNewBuffer = ((Array *)&g_SceneArray)->Insert((void *)g_SceneArray.m_nSize, v76);
    ((Array *)&g_SceneArray)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_SceneArray)->Insert(v76, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v81[12 * v79];
    v82 = ((Array *)&g_SceneArray)->Size();
    g_SceneArray.m_nSize = (int)v81;
    g_SceneArray.m_pData = &v81[12 * v82 + 12];
  }
  pRoleTriple[0] = 316;
  pRoleTriple[1] = SUBGROUP_FLAG_MASK;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(316);
  v85 = g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    ((Array *)&g_SceneArray)->Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    ((Array *)&g_SceneArray)->Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v85) / 12);
    for ( i2 = g_SceneArray.m_pData; v85 != i2; v93[2] = pRoleTriple[2] )
    {
      v93 = v85;
      v85 += 12;
      *v93 = pRoleTriple[0];
      v93[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v86 = (int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12;
    else
      v86 = 1;
    v87 = ((Array *)&g_SceneArray)->Size();
    v12 = v86 + v87 < 0;
    v88 = v86 + v87;
    v89 = v86 + v87;
    if ( v12 )
      v89 = 0;
    v90 = (char *)operator new(12 * v89);
    pNewBuffer = ((Array *)&g_SceneArray)->Insert((void *)g_SceneArray.m_nSize, v85);
    ((Array *)&g_SceneArray)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_SceneArray)->Insert(v85, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v90[12 * v88];
    v91 = ((Array *)&g_SceneArray)->Size();
    g_SceneArray.m_nSize = (int)v90;
    g_SceneArray.m_pData = &v90[12 * v91 + 12];
  }
  pRoleTriple[0] = 317;
  pRoleTriple[1] = SUBGROUP_FLAG_ALT;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(317);
  v94 = g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    ((Array *)&g_SceneArray)->Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    ((Array *)&g_SceneArray)->Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v94) / 12);
    for ( i3 = g_SceneArray.m_pData; v94 != i3; v102[2] = pRoleTriple[2] )
    {
      v102 = v94;
      v94 += 12;
      *v102 = pRoleTriple[0];
      v102[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v95 = (int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12;
    else
      v95 = 1;
    v96 = ((Array *)&g_SceneArray)->Size();
    v12 = v95 + v96 < 0;
    v97 = v95 + v96;
    v98 = v95 + v96;
    if ( v12 )
      v98 = 0;
    v99 = (char *)operator new(12 * v98);
    pNewBuffer = ((Array *)&g_SceneArray)->Insert((void *)g_SceneArray.m_nSize, v94);
    ((Array *)&g_SceneArray)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_SceneArray)->Insert(v94, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v99[12 * v97];
    v100 = ((Array *)&g_SceneArray)->Size();
    g_SceneArray.m_nSize = (int)v99;
    g_SceneArray.m_pData = &v99[12 * v100 + 12];
  }
  pRoleTriple[0] = 318;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(318);
  v103 = g_SceneArray.m_pData;
  if ( (int)(g_SceneArray.m_nCapacity - (unsigned int)g_SceneArray.m_pData) / 12 )
  {
    ((Array *)&g_SceneArray)->Insert(g_SceneArray.m_pData, g_SceneArray.m_pData);
    ((Array *)&g_SceneArray)->Erase((int)g_SceneArray.m_pData, 1 - (g_SceneArray.m_pData - v103) / 12);
    for ( i4 = g_SceneArray.m_pData; v103 != i4; v111[2] = pRoleTriple[2] )
    {
      v111 = v103;
      v103 += 12;
      *v111 = pRoleTriple[0];
      v111[1] = pRoleTriple[1];
    }
    g_SceneArray.m_pData += 12;
  }
  else
  {
    if ( g_SceneArray.m_nSize && (unsigned int)((int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12) > 1 )
      v104 = (int)&g_SceneArray.m_pData[-g_SceneArray.m_nSize] / 12;
    else
      v104 = 1;
    v105 = ((Array *)&g_SceneArray)->Size();
    v12 = v104 + v105 < 0;
    v106 = v104 + v105;
    v107 = v104 + v105;
    if ( v12 )
      v107 = 0;
    v108 = (char *)operator new(12 * v107);
    pNewBuffer = ((Array *)&g_SceneArray)->Insert((void *)g_SceneArray.m_nSize, v103);
    ((Array *)&g_SceneArray)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_SceneArray)->Insert(v103, g_SceneArray.m_pData);
    nullsub_2(g_SceneArray.m_nSize, g_SceneArray.m_pData);
    operator delete((void *)g_SceneArray.m_nSize);
    g_SceneArray.m_nCapacity = (int)&v108[12 * v106];
    v109 = ((Array *)&g_SceneArray)->Size();
    g_SceneArray.m_nSize = (int)v108;
    g_SceneArray.m_pData = &v108[12 * v109 + 12];
  }
  nVal2 = 10;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3[21] = 1943;
  g_SceneMgr = ((Role *)3)->CalcXueJianInit(10);
  g_SceneMgr = ((Role *)3)->CalcLongKuiInit(nVal2);
  g_SceneMgr = ((Role *)3)->CalcZiXuanInit(nVal2);
  g_SceneMgr = ((Role *)3)->CalcChangQingInit(nVal2);
  g_SceneMgr = ((Role *)3)->CalcHuaYingInit(nVal2);
  v112 = 1;
  g_SceneMgr.m_partyInitData[47] = 6;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3[2] = 6;
  g_SceneMgr.m_partyInitData[45] = 4;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3 = 4;
  g_SceneMgr.m_partyInitData[46] = 1;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3[1] = 1;
  g_SceneMgr.m_partyInitData[48] = 3;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3[3] = 3;
  g_SceneMgr.m_partyInitData[49] = 4;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3[4] = 4;
  g_SceneMgr.m_partyInitData[50] = 3;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3[5] = 3;
  g_SceneMgr.m_partyInitData[51] = 2;
  g_SceneMgr.((RoleSystem *)&stru_C059A0)->m_teamData3[6] = 2;
  ((RoleSystem *)((char *)&Buffer.m_partyUI3._todo_05C + 47))->RecalcAggregatedStats(1);
  for ( i5 = 243; i5 < 255; ++i5 )
  {
    v114 = Buffer.m_teamData3[i5 - 24];
    v115 = Buffer.m_teamData3[i5 - 36];
    if ( v114 < v115 )
    {
      if ( v114 <= 0 )
        Buffer.m_teamData3[i5 - 24] = 0;
    }
    else
    {
      Buffer.m_teamData3[i5 - 24] = v115;
    }
  }
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_nAnimFrame + 1) = 0;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_nAnimFrame + 2) = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_pParticleData = 0;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_pParticleData + 1) = 0;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_pParticleData + 2) = 0;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_pParticleData + 3) = 0;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_pParticleData + 4) = 0;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_pParticleData + 5) = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_fAnimDelta = 0.0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[0] = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[1] = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[2] = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[3] = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[4] = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[5] = 0;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[6] = 82001;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[7] = 1;
  ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[8] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(82001);
  pRoleTriple[0] = 4501;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(4501);
  v116 = (char *)g_SceneMgr.m_pAddEffect2;
  if ( ((char *)dword_C0439C - (_BYTE *)g_SceneMgr.m_pAddEffect2) / 12 )
  {
    ((Array *)&g_SceneMgr)->Insert(g_SceneMgr.m_pAddEffect2, g_SceneMgr.m_pAddEffect2);
    ((Array *)&g_SceneMgr)->Erase((int)g_SceneMgr.m_pAddEffect2, 1 - ((_BYTE *)g_SceneMgr.m_pAddEffect2 - v116) / 12);
    v122 = (char *)g_SceneMgr.m_pAddEffect2;
    if ( v116 != g_SceneMgr.m_pAddEffect2 )
    {
      do
      {
        v123 = v116;
        v116 += 12;
        *v123 = pRoleTriple[0];
        v123[1] = pRoleTriple[1];
        v123[2] = pRoleTriple[2];
      }
      while ( v116 != v122 );
    }
    g_SceneMgr.m_pAddEffect2 = (char *)g_SceneMgr.m_pAddEffect2 + 12;
  }
  else
  {
    if ( !g_SceneMgr.m_pSceneRoot )
      goto LABEL_148;
    if ( (unsigned int)(((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12) > 1 )
      v112 = ((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12;
    if ( g_SceneMgr.m_pSceneRoot )
      v117 = ((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12;
    else
LABEL_148:
      v117 = 0;
    v118 = v117 + v112;
    v119 = v117 + v112;
    if ( v117 + v112 < 0 )
      v119 = 0;
    v120 = (char *)operator new(12 * v119);
    pNewBuffer = ((Array *)&g_SceneMgr)->Insert(g_SceneMgr.m_pSceneRoot, v116);
    ((Array *)&g_SceneMgr)->Erase((int)pNewBuffer, 1);
    ((Array *)&g_SceneMgr)->Insert(v116, g_SceneMgr.m_pAddEffect2);
    nullsub_2(g_SceneMgr.m_pSceneRoot, g_SceneMgr.m_pAddEffect2);
    operator delete(src);
    dword_C0439C = (int *)&v120[12 * v118];
    if ( g_SceneMgr.m_pSceneRoot )
      v121 = ((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12;
    else
      v121 = 0;
    g_SceneMgr.m_pSceneRoot = v120;
    g_SceneMgr.m_pAddEffect2 = &v120[12 * v121 + 12];
  }
  pRoleTriple[0] = 306;
  pRoleTriple[1] = SUBGROUP_FLAG_MASK;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(306);
  v124 = (char *)g_SceneMgr.m_pAddEffect2;
  if ( ((char *)dword_C0439C - (_BYTE *)g_SceneMgr.m_pAddEffect2) / 12 )
  {
    ((Array *)&g_SceneMgr)->Insert(g_SceneMgr.m_pAddEffect2, g_SceneMgr.m_pAddEffect2);
    ((Array *)&g_SceneMgr)->Erase((int)g_SceneMgr.m_pAddEffect2, 1 - ((_BYTE *)g_SceneMgr.m_pAddEffect2 - v124) / 12);
    v132 = (char *)g_SceneMgr.m_pAddEffect2;
    if ( v124 != g_SceneMgr.m_pAddEffect2 )
    {
      do
      {
        v133 = v124;
        v124 += 12;
        *v133 = pRoleTriple[0];
        v133[1] = pRoleTriple[1];
        v133[2] = pRoleTriple[2];
      }
      while ( v124 != v132 );
    }
    g_SceneMgr.m_pAddEffect2 = (char *)g_SceneMgr.m_pAddEffect2 + 12;
  }
  else
  {
    if ( g_SceneMgr.m_pSceneRoot && (unsigned int)(((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12) > 1 )
      v125 = ((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12;
    else
      v125 = 1;
    if ( g_SceneMgr.m_pSceneRoot )
      v126 = ((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12;
    else
      v126 = 0;
    v127 = v126 + v125;
    pNewBuffer = v126 + v125;
    if ( v126 + v125 < 0 )
      v127 = 0;
    v128 = (char *)operator new(12 * v127);
    v129 = (char *)g_SceneMgr.m_pSceneRoot;
    pSceneName = v128;
    v130 = v128;
    if ( g_SceneMgr.m_pSceneRoot != v124 )
    {
      do
      {
        ((Array *)v130)->Copy(v129);
        v129 += 12;
        v130 += 12;
      }
      while ( v129 != v124 );
    }
    ((Array *)&g_SceneMgr)->Erase((int)v130, 1);
    ((Array *)&g_SceneMgr)->Insert(v124, g_SceneMgr.m_pAddEffect2);
    nullsub_2(g_SceneMgr.m_pSceneRoot, g_SceneMgr.m_pAddEffect2);
    operator delete(src);
    dword_C0439C = (int *)&pSceneName[12 * pNewBuffer];
    v131 = ((Array *)&g_SceneMgr)->Size();
    g_SceneMgr.m_pSceneRoot = pSceneName;
    g_SceneMgr.m_pAddEffect2 = &pSceneName[12 * v131 + 12];
  }
  pRoleTriple[0] = 307;
  pRoleTriple[1] = SUBGROUP_FLAG_ALT;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(307);
  v134 = (char *)g_SceneMgr.m_pAddEffect2;
  if ( ((char *)dword_C0439C - (_BYTE *)g_SceneMgr.m_pAddEffect2) / 12 )
  {
    ((Array *)&g_SceneMgr)->Insert(g_SceneMgr.m_pAddEffect2, g_SceneMgr.m_pAddEffect2);
    ((Array *)&g_SceneMgr)->Erase((int)g_SceneMgr.m_pAddEffect2, 1 - ((_BYTE *)g_SceneMgr.m_pAddEffect2 - v134) / 12);
    v142 = (char *)g_SceneMgr.m_pAddEffect2;
    if ( v134 != g_SceneMgr.m_pAddEffect2 )
    {
      do
      {
        v143 = v134;
        v134 += 12;
        *v143 = pRoleTriple[0];
        v143[1] = pRoleTriple[1];
        v143[2] = pRoleTriple[2];
      }
      while ( v134 != v142 );
    }
    g_SceneMgr.m_pAddEffect2 = (char *)g_SceneMgr.m_pAddEffect2 + 12;
  }
  else
  {
    if ( g_SceneMgr.m_pSceneRoot && (unsigned int)(((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12) > 1 )
      v135 = ((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12;
    else
      v135 = 1;
    if ( g_SceneMgr.m_pSceneRoot )
      v136 = ((_BYTE *)g_SceneMgr.m_pAddEffect2 - (_BYTE *)g_SceneMgr.m_pSceneRoot) / 12;
    else
      v136 = 0;
    v137 = v136 + v135;
    pSceneName = v136 + v135;
    if ( v136 + v135 < 0 )
      v137 = 0;
    v138 = (char *)operator new(12 * v137);
    v139 = (char *)g_SceneMgr.m_pSceneRoot;
    pNewBuffer = v138;
    v140 = v138;
    if ( g_SceneMgr.m_pSceneRoot != v134 )
    {
      do
      {
        ((Array *)v140)->Copy(v139);
        v139 += 12;
        v140 += 12;
      }
      while ( v139 != v134 );
    }
    ((Array *)&g_SceneMgr)->Erase((int)v140, 1);
    ((Array *)&g_SceneMgr)->Insert(v134, g_SceneMgr.m_pAddEffect2);
    nullsub_2(g_SceneMgr.m_pSceneRoot, g_SceneMgr.m_pAddEffect2);
    operator delete(src);
    dword_C0439C = (int *)&pNewBuffer[12 * pSceneName];
    v141 = ((Array *)&g_SceneMgr)->Size();
    g_SceneMgr.m_pSceneRoot = pNewBuffer;
    g_SceneMgr.m_pAddEffect2 = &pNewBuffer[12 * v141 + 12];
  }
  pRoleTriple[0] = 308;
  pRoleTriple[1] = 0;
  pRoleTriple[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(308);
  ((Scene *)&g_SceneMgr)->AddRoleEntry(pRoleTriple);
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_fActionAssignParam) = 4341;
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[4] = 13;
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[8] = ((Role *)4)->CalcXueJianInit(13);
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[12] = ((Role *)4)->CalcLongKuiInit(*(int *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[4]);
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[16] = ((Role *)4)->CalcZiXuanInit(*(int *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[4]);
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[20] = ((Role *)4)->CalcChangQingInit(*(int *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[4]);
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[24] = ((Role *)4)->CalcHuaYingInit(*(int *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_szTexture[4]);
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_fDistAccum) = 4;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_vecLocalPos + 3) = 4;
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_fNormZ) = 1;
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_vecLocalPos.z) = 1;
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_fNormX) = 3;
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_vecLocalPos.x) = 3;
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_fNormY) = 3;
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_vecLocalPos.y) = 3;
  LODWORD(((RoleSystem *)&stru_C059A0)->m_partyActor.m_fSpeed) = 3;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_vecLocalPos + 4) = 3;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_fSpeed + 1) = 2;
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_nAnimState = 2;
  *((_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_fSpeed + 2) = 2;
  *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_nActionType = 2;
  ((RoleSystem *)&stru_C059A0)->RecalcAggregatedStats(1);
  ((RoleSystem *)&stru_C059A0)->Init();
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
  memset(&dword_C10A10, 0, 0x190u);
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
  dword_C10A10 = 301;
  dword_C10A1C = 0;
  dword_C10A18 = 45;
  dword_C10A20 = 302;
  dword_C10A2C = 4;
  dword_C10A28 = 45;
  dword_C10A30 = 303;
  dword_C10A3C = 5;
  dword_C10A38 = 15;
  dword_C10A40 = 304;
  dword_C10A4C = 20;
  dword_C10A48 = 50;
  dword_C10A50 = 305;
  dword_C10A5C = 30;
  dword_C10A58 = 60;
  dword_C10A60 = 321;
  dword_C10A6C = 0;
  dword_C10A68 = 45;
  dword_C10A70 = 322;
  dword_C10A7C = 5;
  dword_C10A78 = 30;
  dword_C10A80 = 323;
  dword_C10A8C = 14;
  dword_C10A88 = 15;
  dword_C10A90 = 324;
  dword_C10A9C = 23;
  dword_C10A98 = 45;
  dword_C10AA0 = 325;
  dword_C10B28 = 30;
  dword_C10AAC = 32;
  dword_C10AA8 = 50;
  dword_C10AB0 = 311;
  dword_C10ABC = 0;
  dword_C10AB8 = 45;
  dword_C10AC0 = 312;
  dword_C10ACC = 5;
  dword_C10AC8 = 45;
  dword_C10AD0 = 313;
  dword_C10ADC = 15;
  dword_C10AD8 = 15;
  dword_C10AE0 = 314;
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
  ((NPC *)nSlotIndex)->InitAll();
  for ( i6 = 0; i6 < 5; ++i6 )
  {
    result = 1408 * i6;
    *((_BYTE *)&Buffer.m_fCachePosZ + result + 1) = 0;
    *((_BYTE *)&Buffer.m_fCachePosZ + result + 2) = 0;
    *((_BYTE *)&Buffer.m_fCachePosZ + result + 3) = 0;
    *((_BYTE *)&Buffer.m_fMoveTargetX + result) = 0;
    *((_BYTE *)&Buffer.m_fMoveTargetX + result + 1) = 1;
    *((_BYTE *)&Buffer.m_fCachePosZ + result) = 0;
    switch ( i6 )
    {
      case 0:
// [VFTABLE] *((_DWORD *)&Buffer.__vftable + 352 * i6) = 101;
        break;
      case 1:
// [VFTABLE] *((_DWORD *)&Buffer.__vftable + 352 * i6) = 104;
        break;
      case 2:
// [VFTABLE] *((_DWORD *)&Buffer.__vftable + 352 * i6) = 106;
        break;
      case 3:
// [VFTABLE] *((_DWORD *)&Buffer.__vftable + 352 * i6) = 107;
        break;
      case 4:
// [VFTABLE] *((_DWORD *)&Buffer.__vftable + 352 * i6) = 102;
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
  int nVal4; // [esp+0x10] [ebp+0x10]
  int nVal5; // [esp+0x14] [ebp+0x14]
  int *p_DWORD; // [esp+0x18] [ebp+0x18]

  return PAL3_RandomPickValues(nVal, nVal2, nVal3, nVal4, nVal5, p_DWORD);
}

// 0x0041EE40
int PAL3::UIPostProcess()
{
  int result; // eax

  if ( g_pCurrentBGM )
  {
    ((gbSound2DNode *)g_pCurrentBGM)->Stop();
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
      ((UIScrollBar *)(g_nsub_41FA90_DC10FC + 72))->SetRange(1.0);
      ((UIProgressBar *)(g_nsub_41FA90_DC10FC + 72))->FindChildByName(*(float *)&g_nLastUpdateTime);
      DeltaTime = ((gbGfxManager *)gfxMgr)->GetDeltaTime();
      (*(void ( **)(int, _DWORD, int))(*(_DWORD *)g_nsub_41FA90_DC10FC + 8))(
        g_nsub_41FA90_DC10FC,
        LODWORD(DeltaTime),
        1);

    }
  }
}

// 0x00437E60
bool PAL3::WriteRegistryValue(DWORD dwDisposition, ...)
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
  ((PAL3 *)HKEY_LOCAL_MACHINE)->StartWolf(lpSubKey);
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
bool PAL3::WriteRegistryDword(DWORD dwDisposition, ...)
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
  ((PAL3 *)HKEY_LOCAL_MACHINE)->StartWolf(lpSubKey);
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
    ((PAL3 *)v1)->LoadUnlockFlags();
    byte_D924B4[nVal] = 1;
    v2 = 0;
    v3 = 0;
    for ( i = 0; i < 32; ++i )
      v2 |= byte_D924B4[i] << i;
    v5 = i;
    v6 = 0;
    v7 = &byte_D924B4[v5];
    do
    {
      v3 |= *v7++ << v6;
      if ( (int)v7 >= (int)&unk_D924E8 )
        break;
      ++v6;
    }
    while ( v6 < 32 );
    ((PAL3 *)szSubKey)->WriteRegistryDword((DWORD)szValueName, v2);
    ((PAL3 *)szSubKey)->WriteRegistryDword((DWORD)"MOVIE_B", v3);
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

  memset(byte_D924B4, 0, 0x34u);
  *(_DWORD *)Data = 0;
  *(_DWORD *)v8 = 0;
  result = (char *)ReadRegistryString(szSubKey, szValueName, (char *)Data);
  if ( (_BYTE)result )
  {
    result = (char *)ReadRegistryString(szSubKey, "MOVIE_B", (char *)v8);
    if ( (_BYTE)result )
    {
      v2 = *(_DWORD *)Data;
      for ( i = 0; i < 32; ++i )
        byte_D924B4[i] = ((1 << i) & v2) != 0;
      v4 = *(_DWORD *)v8;
      v5 = i;
      v6 = 0;
      result = (char *)&byte_D924B4[v5];
      do
      {
        *result++ = ((1 << v6) & v4) != 0;
        if ( (int)result >= (int)&unk_D924E8 )
          break;
        ++v6;
      }
      while ( v6 < 32 );
    }
  }
  return result;
}

// 0x00456590
bool PAL3::WriteRegistryKey(DWORD dwDisposition, ...)
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
  ((PAL3 *)HKEY_LOCAL_MACHINE)->StartWolf(lpSubKey);
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
  int v5; // eax
  PAL3 *v6; // eax
  gbTexture *ActiveTexture; // eax

  unsigned __int8 v9; // bl

  PAL3 *v11; // eax

  PAL3 *v13; // eax

  Instance_db10 = this->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(1);
  m_snaph = this->GetInstance_db10()->m_snaph;
  v5 = 1061158912;
  if ( m_snaph != 0.0 )
    v5 = 1065353216;
  this->_todo_CD0 = v5;
  this->_todo_CCC = v5;
  v6 = ((PAL3 *)LODWORD(m_snaph))->GetInstance_db10();
  LOBYTE(ActiveTexture) = ((RenderTarget *)v6)->OnResetDevice(1);
  if ( (_BYTE)ActiveTexture )
  {
    v9 = g_bGameFlag2;
    g_bGameFlag2 = 0;

    g_bGameFlag2 = v9;
    v11 = this->GetInstance_db10();
    ((RenderTarget *)v11)->RenderToScreen();
    this->m_pDeviceTex = 0;
    v13 = this->GetInstance_db10();
    ActiveTexture = ((RenderTarget *)v13)->GetActiveTexture();
    if ( ActiveTexture && ActiveTexture[1] )
      this->m_pDeviceTex = ActiveTexture;
  }
  else
  {
    this->m_pDeviceTex = 0;
  }
  return (char)ActiveTexture;
}

// 0x00461BF0
int PAL3::EnterGameMode(int nVal)
{
  int result; // eax

  ((SaleUI *)this)->DestroySubFrames();
  ((UIFrameWnd *)*((UIFrameWnd **)this + 26476))->OnPaintUpdate();
  this->SetValue(0);
  this->SetRange(1u);
  ((PlayerMgr *)this)->SendInputToRole(1u);
  sub_445E50((int)this + 99204);
  result = this->SetRange(1u);
  *((_DWORD *)this + 26466) = 0;
  return result;
}

// 0x00461FD0
int PAL3::SetValue(unsigned __int8 nValue)
{
  (**((void ( ***)(char *, _DWORD))this + 25861))((char *)this + 103444, nValue);
  (**((void ( ***)(char *, _DWORD))this + 25947))((char *)this + 103788, nValue);
  (**((void ( ***)(char *, _DWORD))this + 26033))((char *)this + 104132, nValue);
  (**((void ( ***)(char *, _DWORD))this + 26119))((char *)this + 104476, nValue);
  return (**((int ( ***)(char *, _DWORD))this + 26205))((char *)this + 104820, nValue);
}

// 0x00462030
int PAL3::SetPanelStates(unsigned __int8 pData)
{
  sub_445E50((int)this + 103444);
  sub_445E50((int)this + 103788);
  sub_445E50((int)this + 104132);
  sub_445E50((int)this + 104476);
  return sub_445E50((int)this + 104820);
}

// 0x00462080
int PAL3::SetRange(unsigned __int8 nMax)
{
  sub_445E50((int)this + 103084);
  sub_445E50((int)this + 102000);
  if ( this->s_drvinfo.winname[109] && *((int *)this + 26473) > 0 )
    sub_445E50((int)this + 102364);
  return sub_445E50((int)this + 102724);
}

// 0x00462220
int PAL3::GetValue(unsigned __int8 nIndex)
{
  char *v3; // edi

  v3 = (char *)this + 96604;
  if ( nIndex )
    ((UICaption *)((char *)this + 96604))->SetEnable((int)dword_DC3B3C, 0);
  else
    ((UICaption *)((char *)this + 96604))->SetEnable((int)g_szSceneUIText, 0);
  (**(void ( ***)(char *, _DWORD))v3)(v3, nIndex);
  (**((void ( ***)(char *, _DWORD))this + 23979))((char *)this + 95916, nIndex);
  return (**((int ( ***)(char *, _DWORD))this + 24065))((char *)this + 96260, nIndex);
}

// 0x0047C260
void PAL3::Render_47c260()
{
  if ( this->_todo_F94 )
    crt_sub_00540D20();
}

// 0x0047C2D0
void PAL3::DispatchModeCommand(int nVal)
{
  int v3; // ecx
  int v4; // ecx

  switch ( nVal )
  {
    case 0:
      (*(void ( **)(PAL3 *, int, int, _DWORD))(LODWORD(this->m_snaph) + 24))(this, 1000, 1, 0);
      goto LABEL_6;
    case 1:
      (*(void ( **)(PAL3 *, int, _DWORD, _DWORD))(LODWORD(this->m_snaph) + 24))(this, 1000, 0, 0);
      v3 = *((_DWORD *)&this->m_fViewZ + 19);
      if ( !v3 )
        goto LABEL_10;
      (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v3 + 24))(v3, 1000, 1, 0);
      *((_DWORD *)&this->m_fViewZ + 20) = nVal;
      return;
    case 2:
      (*(void ( **)(PAL3 *, int, _DWORD, _DWORD))(LODWORD(this->m_snaph) + 24))(this, 1000, 0, 0);
LABEL_6:
      v4 = *((_DWORD *)&this->m_fViewZ + 19);
      if ( v4 )
        goto LABEL_9;
      goto LABEL_10;
    case 3:
      (*(void ( **)(PAL3 *, int, _DWORD, _DWORD))(LODWORD(this->m_snaph) + 24))(this, 1000, 0, 0);
      v4 = *((_DWORD *)&this->m_fViewZ + 19);
      if ( v4 )
LABEL_9:
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(v4, 1000, 0, 0);
      goto LABEL_10;
    default:
LABEL_10:
      *((_DWORD *)&this->m_fViewZ + 20) = nVal;
      return;
  }
}

// 0x004B2840
bool PAL3::WriteRegistry(DWORD dwDisposition, ...)
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
  ((PAL3 *)HKEY_LOCAL_MACHINE)->StartWolf(lpSubKey);
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
    ((RenderTarget3 *)&g_RenderTarget3)->Reset();
    atexit(unknown_libname_416);
  }
  return &g_RenderTarget3;
}

// 0x004BDA60
int * PAL3::CreateTextures()
{
  this->m_snaph = NAN;
  *((_DWORD *)&this->m_pCollisionObj + 14) = 0;
  return (int *)this;
}

// 0x004BDB10
PAL3 * PAL3::GetInstance_db10()
{
  if ( (*(_BYTE *)(&g_PAL3.m_pCollisionObj + 15) & 1) == 0 )
  {
    *((_BYTE *)&g_PAL3.m_pCollisionObj + 60) |= 1u;
    ((PAL3 *)&g_PAL3)->CreateTextures();
    atexit(unknown_libname_427);
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
  if ( (*(_BYTE *)(&g_PAL3._todo_F9C + 71) & 1) == 0 )
  {
    *((_BYTE *)&g_PAL3._todo_F9C + 284) |= 1u;
    ((ScreenEffectMgr *)(&g_PAL3._todo_F9C + 65))->ResetFadeState();
    atexit(unknown_libname_437);
  }
  return (ScreenEffectMgr *)(&g_PAL3._todo_F9C + 65);
}

// 0x004C0400
void PAL3::ClearAdditiveEffects()
{
  gbRenderEffect *m_pAdditiveEffect; // eax
  gbTexture *m_pScnFrameTex; // eax
  gbRenderEffect *m_pAdditiveEffect2; // eax

  m_pAdditiveEffect = this->m_pAdditiveEffect;
  if ( m_pAdditiveEffect )
  {
// [VFTABLE] (*((void ( **)(gbRenderEffect *))m_pAdditiveEffect->__vftable + 2))(m_pAdditiveEffect);
    this->m_pAdditiveEffect = 0;
  }
  m_pScnFrameTex = this->m_pScnFrameTex;
  if ( m_pScnFrameTex )
  {
    ((void ( *)(gbTexture *))m_pScnFrameTex->CreateForRenderTarget)(this->m_pScnFrameTex);
    this->m_pScnFrameTex = 0;
  }
  m_pAdditiveEffect2 = this->m_pAdditiveEffect2;
  if ( m_pAdditiveEffect2 )
  {
// [VFTABLE] (*((void ( **)(gbRenderEffect *))m_pAdditiveEffect2->__vftable + 2))(this->m_pAdditiveEffect2);
    this->m_pAdditiveEffect2 = 0;
  }
}

// 0x004C58C0
char PAL3::CreateRenderEffects()
{
  gbRenderEffect *v2; // eax
  float m_snaph; // ecx

  sub_4C5CD0();
  v2 = ((gbEffectMgr *)*(gbEffectMgr **)(LODWORD(this->m_snaph) + 200))->NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0);
  m_snaph = this->m_snaph;
  this->m_pAdditiveEffect = v2;
  this->m_pAdditiveEffect2 = ((gbEffectMgr *)*(gbEffectMgr **)(LODWORD(m_snaph) + 200))->NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0);
  this->s_drvinfo.winname[4] = 1;
  return 1;
}

// 0x00527C30
int * PAL3::HandleDeviceLost()
{
  PAL3 *Instance_db10; // eax

  float m_snaph; // ecx
  int v5; // eax
  PAL3 *v6; // eax

  unsigned __int8 v8; // bl
  PAL3 *v9; // eax

  PAL3 *v11; // eax
  int *result; // eax

  Instance_db10 = this->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(1);
  m_snaph = this->GetInstance_db10()->m_snaph;
  v5 = 1061158912;
  if ( m_snaph != 0.0 )
    v5 = 1065353216;
  this->_todo_6D8 = v5;
  this->_todo_6D4 = v5;
  v6 = ((PAL3 *)LODWORD(m_snaph))->GetInstance_db10();
  ((RenderTarget *)v6)->OnResetDevice(1);
  if ( !this->_todo_6C8 )
  {
    v8 = g_bGameFlag2;
    g_bGameFlag2 = 0;

    g_bGameFlag2 = v8;
  }
  v9 = this->GetInstance_db10();
  ((RenderTarget *)v9)->RenderToScreen();
  this->_todo_6D0 = 0;
  v11 = this->GetInstance_db10();
  result = (int *)((RenderTarget *)v11)->GetActiveTexture();
  if ( result )
  {
    if ( result[21] )
      this->_todo_6D0 = (int)result;
  }
  return result;
}

// 0x0052F570
bool PAL3::WriteRegistryDwordEx(DWORD dwDisposition, ...)
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
  ((PAL3 *)HKEY_LOCAL_MACHINE)->StartWolf(lpSubKey);
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
  int v2; // eax
  int v3; // ecx
  float *v4; // ebx
  double v5; // st7
  double v6; // st7
  double v7; // st6
  double v8; // st7
  int v10; // [esp+0x10] [ebp-0x78]
  int v11; // [esp+0x14] [ebp-0x74]
  gbVec3D v12; // [esp+0x18] [ebp-0x70] BYREF
  float m_fViewY; // [esp+0x28] [ebp-0x60]
  float v14; // [esp+0x2C] [ebp-0x5C]
  float v15; // [esp+0x34] [ebp-0x54]
  float v16; // [esp+0x38] [ebp-0x50]
  float v17[19]; // [esp+0x3C] [ebp-0x4C] BYREF

  v2 = UISceneUpdate();
  v3 = *(_DWORD *)(v2 + 57568);
  v10 = 0;
  v11 = v3;
  if ( v3 <= 0 )
  {
LABEL_8:
    this->_todo_085 = 1;
    return 0;
  }
  v4 = (float *)(v2 + 58204);
  while ( 1 )
  {
    this->m_pCollisionObj = (RoleSystem *)(v4 - 158);
    if ( !*((_DWORD *)v4 - 122) || !*(_DWORD *)v4 )
      goto LABEL_7;
    memset(&v12, 0, sizeof(v12));
    v5 = *(v4 - 157);
    m_fViewY = this->m_fViewY;
    v14 = *(v4 - 155);
    v6 = this->m_fViewX - v5;
    v15 = this->m_fViewY - m_fViewY;
    v7 = this->m_fViewZ - v14;
    v12.y = v15;
    v16 = v7;
    v12.x = v6;
    v12.z = v16;
    v8 = ((gbVec3D *)&v12)->Length();
    qmemcpy(v17, (const void *)(LODWORD(this->m_snaph) + 12), sizeof(v17));
    if ( *(float *)&this->m_pCollisionObj->m_rect.left > fabs(v8 - v17[18] * 0.5) )
      break;
    v3 = v11;
LABEL_7:
    v4 += 2176;
    if ( ++v10 >= v3 )
      goto LABEL_8;
  }
  ((RoleSystem *)this->m_pCollisionObj)->Notify();
  LOBYTE(((PalScript *)&stru_C11720)->_todo_028) = 0;
  LOBYTE(((PalScript *)&stru_C11720)->_todo_48) = 0;
  g_nKeyMap3 = 1;
  dword_C1171C = 0x7FFFFFFF;
  ((PAL3 *)&this->m_pCollisionObj->m_nFacing)->StartCombatFromNPC(0, 0);
  *(_DWORD *)&this->m_pCollisionObj->m_partyActor.m_szTexture[4] = 0;
  if ( ((PalScript *)&stru_C11720)->_todo_034 )
    *(_DWORD *)(((PalScript *)&stru_C11720)->_todo_034 + 632) = 0;
  this->_todo_085 = 0;
  return 1;
}

// 0x00569110
void PAL3::ResetForNewScene(char bSaveData)
{
  CScreenMode *v1; // ecx
  PtrArray *SoundList; // eax
  PAL3 *v3; // ecx
  RenderTarget3 *v4; // ecx
  RenderTarget3 *Instance; // eax
  CScreenMode *v6; // eax
  gbAudioManager *AudioManager; // eax
  int *p_capacity; // esi
  Actor *SaveDataManager; // eax
  Actor *v10; // eax
  char *v11; // [esp-0x8] [ebp-0x8]
  int *v12; // [esp-0x4] [ebp-0x4]
  char *v13; // [esp-0x4] [ebp-0x4]

  g_fEffectTimer = 10.0;
  ((SceneMapPlayer *)g_ScriptSystemData.m_mapPlayer)->Reset();
  ((SceneMapPlayer *)&stru_D8B4A0)->Reset();
  SoundList = ((CScreenMode *)v1)->GetSoundList();
  sub_53D1D0(SoundList);
  ((PAL3 *)v3)->UIPostProcess();
  sub_4CE5C0(g_pSceneManager);
  ((CEffMgr *)g_pSceneManager)->ReleaseCompletedEffects();
  Instance = ((RenderTarget3 *)v4)->GetInstance();
  ((RenderTarget3 *)Instance)->SwapBuffers();
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].CountMode = 0;
  byte_BFDA40 = 0;
  if ( (g_dwGameFlags & 1) == 0 )
    JUMPOUT(0x2EE3E9A);
  v6 = CScreenMode::GetInstance();
  AudioManager = (gbAudioManager *)((CScreenMode *)v6)->GetAudioManager();
  ((gbAudioManager *)AudioManager)->DetachAll3D();
  g_fPalScript_C12B28 = 0.0;
  g_fPalScript_C12B2C = 0.0;
  g_fPalScript_C12B30 = 0.0;
  p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
  do
  {
    ((RoleSystem *)p_capacity)->Notify();
    p_capacity += 2176;
  }
  while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
  if ( dword_C9A63C[123289 * (dword_D8BBEC == 1)] )
  {
    sub_421870((gbVisNode **)(493156 * (dword_D8BBEC == 1) + 12722152));
    if ( bSaveData )
    {
      v12 = (int *)(493156 * (dword_D8BBEC == 1) + 12722152);
      SaveDataManager = (Actor *)GetSaveDataManager();
      ((Actor *)SaveDataManager)->BuildCollisionMesh(v12);
      v13 = (char *)(493156 * (dword_D8BBEC == 1) + 12722184);
      v11 = (char *)(493156 * (dword_D8BBEC == 1) + 12722152);
      v10 = (Actor *)GetSaveDataManager();
      ((Actor *)v10)->RegisterAnim(v11, v13);
    }
  }
}
