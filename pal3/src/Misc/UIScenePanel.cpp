#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIScenePanel.h"

// Forward declarations for unnamed functions
int sub_407790(...);
int sub_43FD90(float *_this, int a2); // from annotations
int sub_43FEC0(void *a2); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

BOOL ReadRegistryString(const char *szSubKey, const char *szValueName, char *szOutBuf); // from annotations

// Unnamed globals (extern)
extern const char * off_5707D0;
extern void *off_59DDB4;
extern void *off_59DDB8;
extern void *off_59DDBC;
extern void *off_59DDC0;
extern void *off_59DDC4;
extern void *off_59DDC8;
extern unsigned __int8 unk_D924E8;

// 0x0043B3E0
void UIScenePanel::_UIScenePanel()
{
  unsigned int v2; // [esp+0x4] [ebp-0x4]

  UIScene::GetSys();
  *(&this->m_SlotData + 3) = 32;
  this->m_SlotData = 0;
  *(&this->m_SlotData + 1) = 0;
  *(&this->m_SlotData + 2) = 0;
// [VFTABLE] this->m_Static_360.__vftable = (vtbl_0056AE2C *)1;
  if ( gbColorQuad::ColorQuadFmt )
  {
    LOBYTE(v2) = 0x80;
    *(_WORD *)((char *)&v2 + 1) = 17476;
  }
  else
  {
    *(_WORD *)((char *)&v2 + 1) = -32700;
    LOBYTE(v2) = 68;
  }
  HIBYTE(v2) = -1;
  this->m_Static_360.m_fontcolor.Color = v2;
  this->m_Static_360.m_wndcolor.Color = -16777216;
  this->m_Static_360.m_id = (void *)-16119286;
}

// 0x0044BA60
int UIScenePanel::ctor_BA60()
{
  sub_4422E0(&this->m_Static_360);
  sub_4422E0(&this->m_Static_10496);
  sub_4422E0(&this->m_Static_10648);
  sub_4422E0(&this->m_Static_10800);
  sub_4422E0(&this->m_Static_10952);
  ((CCBResultWindow *)&this->m_Wnd_11116)->Create();
  ((CCBResultWindow *)&this->m_Wnd_11308)->Create();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  *(&this->m_hSettingsUI + 1) = 0;
  *(_DWORD *)&this->m_bPanelFlagA = 0;
  this->m_nPanelState = 0;
  this->m_nSceneIdx = 0;
  this->m_bFlags0 = 1;
  this->m_bFlags1 = 1;
  *(&this->m_bFlags1 + 1) = 0;
  sub_4422E0(&this->m_Static_13904);
  sub_4422E0(&this->m_Static_14080);
  this->m_fScaleX = 0.0;
  this->m_fScaleY = 0.0;
  *(_DWORD *)&this->_todo_050 = 800;
  this->m_nScrollState = 600;
  *((_BYTE *)&this->_todo_362C + 4) = 0;
  *((_BYTE *)&this->_todo_362C + 5) = 0;
  *(&this->_todo_362C + 2) = 0;
  *(&this->_todo_362C + 3) = 0;
  this->m_hSettingsUI = 0;
  return (int)this;
}

// 0x0044BE80
void UIScenePanel::ctor()
{

  ((UIFrameWnd *)&this->m_Static_14080)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_13904)->UIFrameWnd::_UIFrameWnd();
  if ( this->m_nPanelState )
  {
    operator delete((void *)this->m_nPanelState);
    this->m_nPanelState = 0;
  }
  ((UICaption *)&this->m_SceneF)->Destroy2();
  ((UICaption *)&this->m_SceneE)->Destroy2();
  ((UICaption *)&this->m_SceneD)->Destroy2();
  ((UICaption *)&this->m_SceneC)->Destroy2();
  ((UICaption *)&this->m_SceneB)->Destroy2();
  ((UICaption *)&this->m_SceneA)->Destroy2();
  ((UIFrameWnd *)&this->m_Wnd_11308)->DestroyCallingCtor();
  ((UIFrameWnd *)&this->m_Wnd_11116)->DestroyCallingCtor();
  ((UIFrameWnd *)&this->m_Static_10952)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_10800)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_10648)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_10496)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_360)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0044C120
void UIScenePanel::CreateSettingsUI()
{
  float *p_m_fScaleY; // ebp
  void *vftable; // edx
  void *v4; // eax
  void *v5; // edx
  void *v6; // edx
  void *v7; // eax
  void *v8; // edx
  void *v9; // eax
  int v10; // eax
  void *v11; // edx
  int v12; // eax
  void *v13; // edx
  int v14; // eax
  void *v15; // edx
  int v16; // eax
  void *v17; // edx
  int v18; // eax
  void *v19; // edx
  int v20; // eax
  void *v21; // edx
  CCBRoleState *v22; // eax
  CCBRoleState *v23; // eax
  CCBUIPanel *v24; // eax
  RoleShadow *v25; // eax
  TaskBookUI *v26; // eax
  TaskBookUI *v27; // eax
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v30; // edi
  CScreenMode *v31; // eax
  UICursor *v32; // ecx
  void *m_nPanelState; // eax
  void *v34; // edi
  unsigned int v35; // edx
  int v36; // [esp+D4h] [ebp-0x78]
  int v37; // [esp+D8h] [ebp-0x74]
  int v38; // [esp+DCh] [ebp-0x70]
  BYTE Data[4]; // [esp+E4h] [ebp-0x68] BYREF
  BYTE v40[4]; // [esp+E8h] [ebp-0x64] BYREF
  BYTE v41[4]; // [esp+ECh] [ebp-0x60] BYREF
  int v42; // [esp+F0h] [ebp-0x5C] BYREF
  int v43; // [esp+F4h] [ebp-0x58]
  int v44; // [esp+F8h] [ebp-0x54]
  int v45; // [esp+FCh] [ebp-0x50]
  int v46; // [esp+0x100] [ebp-0x4C] BYREF
  int v47; // [esp+0x104] [ebp-0x48]
  int v48; // [esp+0x108] [ebp-0x44]
  int v49; // [esp+0x10C] [ebp-0x40]
  int v50; // [esp+0x110] [ebp-0x3C] BYREF
  int v51; // [esp+0x114] [ebp-0x38]
  int v52; // [esp+0x118] [ebp-0x34]
  int v53; // [esp+0x11C] [ebp-0x30]
  _DWORD v54[4]; // [esp+0x120] [ebp-0x2C] BYREF
  _DWORD v55[4]; // [esp+0x130] [ebp-0x1C] BYREF
  int v56; // [esp+0x148] [ebp-0x4]

  p_m_fScaleY = &this->m_fScaleY;
  ((UIListBox *)this)->SetSelTexture(0, LODWORD(this->m_fScaleY), LODWORD(this->m_fScaleX), *(_DWORD *)&this->_todo_050, this->m_nScrollState, 0);
  g_nSceneState = 1;
// [VFTABLE] vftable = this->m_Static_360.__vftable;
  v54[1] = 80;
  v54[0] = 169;
  v54[2] = 611;
  v54[3] = 526;
  ((void ( *)(UIStatic *, _DWORD, _DWORD *, UIScenePanel *))vftable->Create)(
    &this->m_Static_360,
    0,
    v54,
    this);
  ((UIStatic *)&this->m_Static_360)->CreateFromTemplate();
  ((RoleSystem *)this)->InitUICtrlArray();
// [VFTABLE] v4 = this->m_Static_10496.__vftable;
  v47 = 192;
  v46 = 79;
  v48 = 409;
  v49 = 424;
  ((void ( *)(UIStatic *, _DWORD, int *, UIScenePanel *))v4->Create)(&this->m_Static_10496, 0, &v46, this);
  ((UIStatic *)&this->m_Static_10496)->CreateFromTemplate();
  ((UITitle_XJTM *)this)->CreateSubWidgets();
// [VFTABLE] v5 = this->m_Static_10648.__vftable;
  v47 = 203;
  v46 = 556;
  v48 = 610;
  v49 = 318;
  ((void ( *)(UIStatic *, _DWORD, int *, UIScenePanel *))v5->Create)(&this->m_Static_10648, 0, &v46, this);
  ((UIStatic *)&this->m_Static_10648)->CreateFromTemplate();
  ((Actor *)this)->InitParticles();
// [VFTABLE] v6 = this->m_Static_14080.__vftable;
  *((_DWORD *)&this->m_Static_13904 + 42) = 1099264164;
  *((_DWORD *)&this->m_Static_13904 + 43) = 1140948992;
  *((_DWORD *)&this->m_Static_13904 + 39) = 518;
  *((_DWORD *)&this->m_Static_13904 + 38) = 220;
  *((_DWORD *)&this->m_Static_13904 + 40) = 586;
  *((_DWORD *)&this->m_Static_13904 + 41) = 1542;
  ((void ( *)(UIStatic *, _DWORD, UIStatic *, UIScenePanel *))v6->Create)(
    &this->m_Static_14080,
    0,
    &this->m_Static_13904 + 1,
    this);
  ((UIStatic *)&this->m_Static_14080)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_Static_14080.__vftable->ShowWindow)(&this->m_Static_14080, 0);
// [VFTABLE] v7 = this->m_Static_10952.__vftable;
  *((_BYTE *)this + 14232) = 0;
  v55[1] = 223;
  v55[0] = 200;
  v55[2] = 581;
  v55[3] = 366;
  ((void ( *)(UIStatic *, _DWORD, _DWORD *, UIScenePanel *))v7->Create)(&this->m_Static_10952, 0, v55, this);
  ((UIStatic *)&this->m_Static_10952)->CreateFromTemplate();
// [VFTABLE] v8 = this->m_Wnd_11116.__vftable;
  v51 = 83;
  v50 = 170;
  v52 = 502;
  v53 = 519;
  ((void ( *)(UIWnd *, _DWORD, int *, UIScenePanel *))v8->Create)(&this->m_Wnd_11116, 0, &v50, this);
  ((UIStatic *)&this->m_Wnd_11116)->CreateFromTemplate();
  ((UIBigMap *)&this->m_Wnd_11116)->SetViewParams(406, 590);
  *((_DWORD *)&this->m_Wnd_11116 + 42) = 0;
  *((_DWORD *)&this->m_Wnd_11116 + 39) = 1;
  *((_DWORD *)&this->m_Wnd_11116 + 40) = 1118044160;
  *((_BYTE *)&this->m_Wnd_11116 + 172) = 0;
  *((_DWORD *)&this->m_Wnd_11116 + 41) = 0;
  *((_BYTE *)&this->m_Wnd_11116 + 172) = 1;
// [VFTABLE] v9 = this->m_Wnd_11308.__vftable;
  v51 = 86;
  v50 = 278;
  v52 = 610;
  v53 = 522;
  ((void ( *)(UIWnd *, _DWORD, int *, UIScenePanel *))v9->Create)(&this->m_Wnd_11308, 0, &v50, this);
  ((UIStatic *)&this->m_Wnd_11308)->CreateFromTemplate();
  ((UIBigMap *)&this->m_Wnd_11308)->SetViewParams(336, 28);
  *((_DWORD *)&this->m_Wnd_11308 + 42) = 0;
  *((_DWORD *)&this->m_Wnd_11308 + 39) = 1;
  *((_DWORD *)&this->m_Wnd_11308 + 40) = 1118044160;
  *((_BYTE *)&this->m_Wnd_11308 + 172) = 0;
  *((_DWORD *)&this->m_Wnd_11308 + 41) = 0;
  *((_BYTE *)&this->m_Wnd_11308 + 172) = 1;
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD, float *, UIScenePanel *))this->m_Static_10800.__vftable->Create)(
// [VFTABLE]   &this->m_Static_10800,
// [VFTABLE]   0,
// [VFTABLE]   p_m_fScaleY,
// [VFTABLE]   this);
  ((UIStatic *)&this->m_Static_10800)->CreateFromTemplate();
  LOBYTE(v10) = g_bSceneLoaded;
// [VFTABLE] v11 = this->m_SceneA.__vftable;
  v43 = 0;
  v42 = 152;
  v44 = 388;
  v45 = 156;
  v12 = ((int ( *)(UIScene *, int, int *, UIScenePanel *, char *, int))v11[1].Render)(
          &this->m_SceneA,
          161,
          &v42,
          this,
          off_59DDB4[0],
          v10);
  LOBYTE(v12) = g_bSceneLoaded;
// [VFTABLE] v13 = this->m_SceneB.__vftable;
  v43 = 175;
  v42 = 59;
  v44 = 187;
  v45 = 431;
  v14 = ((int ( *)(UIScene *, int, int *, UIScenePanel *, char *, int))v13[1].Render)(
          &this->m_SceneB,
          162,
          &v42,
          this,
          off_59DDB8[0],
          v12);
  LOBYTE(v14) = g_bSceneLoaded;
// [VFTABLE] v15 = this->m_SceneC.__vftable;
  v43 = 446;
  v42 = 142;
  v44 = 378;
  v45 = 602;
  v16 = ((int ( *)(UIScene *, int, int *, UIScenePanel *, char *, int))v15[1].Render)(
          &this->m_SceneC,
          163,
          &v42,
          this,
          off_59DDBC[0],
          v14);
  v43 = 446;
  v42 = 410;
  LOBYTE(v16) = g_bSceneLoaded;
// [VFTABLE] v17 = this->m_SceneD.__vftable;
  v44 = 646;
  v45 = 602;
  v18 = ((int ( *)(UIScene *, int, int *, UIScenePanel *, char *, int))v17[1].Render)(
          &this->m_SceneD,
          164,
          &v42,
          this,
          off_59DDC0[0],
          v16);
  LOBYTE(v18) = g_bSceneLoaded;
// [VFTABLE] v19 = this->m_SceneE.__vftable;
  v43 = 179;
  v42 = 585;
  v44 = 713;
  v45 = 435;
  v20 = ((int ( *)(UIScene *, int, int *, UIScenePanel *, char *, int))v19[1].Render)(
          &this->m_SceneE,
          165,
          &v42,
          this,
          off_59DDC4[0],
          v18);
  LOBYTE(v20) = g_bSceneLoaded;
// [VFTABLE] v21 = this->m_SceneF.__vftable;
  v43 = 0;
  v42 = 416;
  v44 = 652;
  v45 = 156;
  ((void ( *)(UIScene *, int, int *, UIScenePanel *, char *, int))v21[1].Render)(
    &this->m_SceneF,
    166,
    &v42,
    this,
    off_59DDC8[0],
    v20);
  v22 = (CCBRoleState *)operator new(0x5058u);
  *(_DWORD *)v41 = v22;
  v56 = 0;
  if ( v22 )
    v23 = (CCBRoleState *)((CCBRoleState *)v22)->ctor();
  else
    v23 = 0;
  v56 = -1;
  *(&this->_todo_362C + 2) = (int)v23;
  ((CCBRoleState *)v23)->_CCBRoleState();
  v24 = (CCBUIPanel *)operator new(0x14C4u);
  *(_DWORD *)v41 = v24;
  v56 = 1;
  if ( v24 )
    v25 = (RoleShadow *)((CCBUIPanel *)v24)->ctor_3D10();
  else
    v25 = 0;
  v56 = -1;
  *(&this->_todo_362C + 3) = (int)v25;
  ((RoleShadow *)v25)->InitFromTemplate((int)this);
  v26 = (TaskBookUI *)operator new(0x207F0u);
  *(_DWORD *)v41 = v26;
  v56 = 2;
  if ( v26 )
    ((TaskBookUI *)v26)->_TaskBookUI();
  else
    v27 = 0;
  v56 = -1;
  this->m_hSettingsUI = (int)v27;
  ((TaskBookUI *)v27)->CreateEntry((int)this, v36, v37, v38);
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v30 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->DetachAll3D();
      ((gbAudioManager *)v30)->StopSoundStream(0);
      ((gbAudioManager *)v30)->StopSoundStream(2);
      v31 = CScreenMode::GetInstance();
      ((SoundMgr *)v31)->PlayCPKStream();
    }
  }
  *(_DWORD *)Data = 0;
  *(_DWORD *)v40 = 0;
  *(_DWORD *)v41 = 0;
  ReadRegistryString("SOFTWARE\\SOFTSTAR\\PAL3_S_GAME", "S_GAME_A", (char *)Data);
  ReadRegistryString("SOFTWARE\\SOFTSTAR\\PAL3_S_GAME", "S_GAME_B", (char *)v40);
  ReadRegistryString("SOFTWARE\\SOFTSTAR\\PAL3_S_GAME", "S_GAME_C", (char *)v41);
  LOBYTE(g_dwUISettings) = *(_DWORD *)Data != 0;
  BYTE1(g_dwUISettings) = *(_DWORD *)v40 != 0;
  LOBYTE(v32) = *(_DWORD *)v41 != 0;
  BYTE2(g_dwUISettings) = *(_DWORD *)v41 != 0;
  *(&this->m_bFlags1 + 3) = 0;
  *((_BYTE *)&this->_todo_362C + 5) = 0;
  *((_DWORD *)&this->m_Static_10952 + 39) = 0;
  *((_BYTE *)&this->m_Static_10952 + 152) = 1;
  ((UICursor *)v32)->IRender();
  m_nPanelState = (void *)this->m_nPanelState;
  *(_DWORD *)&this->m_bPanelFlagA = 16;
  if ( m_nPanelState )
  {
    operator delete(m_nPanelState);
    this->m_nPanelState = 0;
  }
  v34 = operator new(4 * *(_DWORD *)&this->m_bPanelFlagA);
  v35 = 4 * *(_DWORD *)&this->m_bPanelFlagA;
  this->m_nPanelState = (int)v34;
  memset(v34, 0, v35);
  this->m_nSceneIdx = 0;
  this->m_bFlags0 = 1;
  this->m_bFlags1 = 0;
  *(&this->m_bFlags1 + 1) = 0;
  if ( ((CGameData *)&g_gamefrm)->GetMode() == 8
    || ((CGameData *)&g_gamefrm)->GetMode() == 11
    || unk_D924E8 )
  {
    ((ChoseCompose *)this)->Init(3);
    unk_D924E8 = 0;
  }
}

// 0x0044DB70
int UIScenePanel::StopAllSounds(float fFade, int nFlags)
{
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  __int64 v6; // rcx
  int v7; // esi
  int v8; // esi
  CScreenMode *v9; // eax
  gbAudioManager *v10; // eax
  gbAudioManager *v11; // esi
  CScreenMode *v13; // eax
  gbAudioManager *v14; // eax
  gbAudioManager *v15; // esi
  CScreenMode *v16; // eax
  gbAudioManager *v17; // eax
  gbAudioManager *v18; // esi
  PalScriptMgr *v19; // ecx
  char v20; // al
  unsigned int v21; // ecx
  unsigned int v22; // edx
  float *m_nPanelState; // eax
  int v24; // edx
  double v25; // st7
  double v26; // st7
  void *vftable; // edx
  int v28; // ecx
  int m_hSettingsUI; // eax
  CScreenMode *v30; // eax
  gbAudioManager *v31; // eax
  gbAudioManager *v32; // esi
  CScreenMode *v33; // eax
  double v34; // [esp-0x4] [ebp-0x18]

  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    ((gbAudioManager *)AudioManager)->DetachAll3D();
  }
  HIDWORD(v6) = 0;
  if ( !*(&this->m_bFlags1 + 3) )
  {
    switch ( *(&this->m_hSettingsUI + 1) )
    {
      case 0:
        if ( !*((_BYTE *)&this->_todo_362C + 4) )
        {
          if ( !this->m_bFlags1 )
          {
            if ( this->m_bFlags0 )
              this->m_bFlags0 = 0;
            *(float *)(this->m_nPanelState + 4 * this->m_nSceneIdx) = fFade;
            v20 = *(&this->m_bFlags1 + 1);
            v21 = this->m_nSceneIdx + 1;
            this->m_nSceneIdx = v21;
            v22 = v21;
            if ( !v20 )
              *(&this->m_bFlags1 + 1) = v21 >= *(_DWORD *)&this->m_bPanelFlagA;
            LODWORD(v6) = *(_DWORD *)&this->m_bPanelFlagA;
            *(&this->m_nPanelState + 1) = 0;
            this->m_nSceneIdx = v22 < (unsigned int)v6 ? v22 : 0;
            if ( (_DWORD)v6 )
            {
              m_nPanelState = (float *)this->m_nPanelState;
              v24 = v6;
              do
              {
                v25 = *m_nPanelState++ + *((float *)&this->m_nPanelState + 1);
                --v24;
                *((float *)&this->m_nPanelState + 1) = v25;
              }
              while ( v24 );
            }
            fFade = *((float *)&this->m_nPanelState + 1) / (double)v6;
          }
          if ( !*(&this->m_bFlags1 + 1) )
            return 1;
          ((CCCTData *)this)->InitEntries(fFade);
          if ( *((_BYTE *)this + 14232) )
          {
            if ( !((UICoverFrm *)this)->UpdateAnimation(fFade) )
            {
              v26 = *((float *)&this->m_Static_10952 + 39) - fFade * 80.0;
              *((float *)&this->m_Static_10952 + 39) = v26;
              if ( v26 <= 0.0 )
                *((_DWORD *)&this->m_Static_10952 + 39) = 0;
              if ( (((NPC *)&this->m_Static_10952)->NPC::UpdateAnim(), g_Input.KeyInfo[0].PressTime == 1)
                && (g_Input.KeyInfo[0].Data & 0xF) == 1
                || g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
              {
                ((UICoverFrm *)this)->SetDefaultValues();
// [VFTABLE] vftable = this->m_Static_14080.__vftable;
                *((_BYTE *)this + 14232) = 0;
                ((void ( *)(UIStatic *, _DWORD))vftable->ShowWindow)(&this->m_Static_14080, 0);
                *((_BYTE *)&this->m_Static_10952 + 152) = 1;
                ((UIListBox *)this)->Update(SLODWORD(fFade), nFlags);
                goto LABEL_43;
              }
            }
          }
          else
          {
            ((JusticeBookUI *)this)->UpdateFadeAnim(fFade);
          }
          ((UIListBox *)this)->Update(SLODWORD(fFade), nFlags);
          goto LABEL_43;
        }
        sub_407790();
        g_nSceneState = 2;
        ((PalScriptMgr *)v19)->Destroy();
        ((CGameData *)&g_gamefrm)->Load(0);
        ((GRPinput *)&g_Input)->Reset();
        return 1;
      case 1:
        v28 = *(&this->_todo_362C + 2);
        goto LABEL_42;
      case 3:
        v28 = *(&this->_todo_362C + 3);
LABEL_42:
        (*(void ( **)(int, _DWORD, int))(*(_DWORD *)v28 + 8))(v28, LODWORD(fFade), nFlags);
        goto LABEL_43;
      case 4:
        (*(void ( **)(int, _DWORD, int))(*(_DWORD *)this->m_hSettingsUI + 8))(
          this->m_hSettingsUI,
          LODWORD(fFade),
          nFlags);
        m_hSettingsUI = this->m_hSettingsUI;
        if ( !*(_DWORD *)(m_hSettingsUI + 130360) )
          goto LABEL_43;
        LODWORD(v34) = *(_DWORD *)(m_hSettingsUI + 130352);
        ((TaskBookUI *)v34)->_todo_456200();
        return 1;
      case 5:
        if ( (g_dwGameFlags & 4) != 0 )
        {
          v30 = CScreenMode::GetInstance();
          v31 = (gbAudioManager *)((CScreenMode *)v30)->GetAudioManager();
          v32 = v31;
          if ( v31 )
          {
            ((gbAudioManager *)v31)->StopSoundStream(1);
            ((gbAudioManager *)v32)->StopSoundStream(2);
            v33 = CScreenMode::GetInstance();
            ((CScreenMode *)v33)->AudioStopAll();
          }
        }
        ((CGameData *)&g_gamefrm)->Load(0);
        return 1;
      default:
LABEL_43:
        if ( *((_BYTE *)&this->_todo_362C + 5)
          && *((_BYTE *)&this->m_Wnd_11116 + 172)
          && *((_BYTE *)&this->m_Wnd_11308 + 172) )
        {
          PostQuitMessage(0);
        }
        return 1;
    }
  }
  v7 = *(_DWORD *)(&this->m_bFlags1 + 7) - 1;
  if ( v7 )
  {
    v8 = v7 - 1;
    if ( v8 )
    {
      if ( v8 == 1 )
      {
        v9 = CScreenMode::GetInstance();
        v10 = (gbAudioManager *)((CScreenMode *)v9)->GetAudioManager();
        v11 = v10;
        if ( v10 )
        {
          ((gbAudioManager *)v10)->DetachAll3D();
          ((gbAudioManager *)v11)->StopSoundStream(0);
          ((gbAudioManager *)v11)->StopSoundStream(2);
          ((gbAudioManager *)v11)->StopSoundStream(1);
        }
        ((CGameData *)&g_gamefrm)->Load((CUtil *)0xB);
        return 1;
      }
      else
      {
        return 1;
      }
    }
    else
    {
      v13 = CScreenMode::GetInstance();
      v14 = (gbAudioManager *)((CScreenMode *)v13)->GetAudioManager();
      v15 = v14;
      if ( v14 )
      {
        ((gbAudioManager *)v14)->DetachAll3D();
        ((gbAudioManager *)v15)->StopSoundStream(0);
        ((gbAudioManager *)v15)->StopSoundStream(2);
        ((gbAudioManager *)v15)->StopSoundStream(1);
      }
      ((CGameData *)&g_gamefrm)->Load((CUtil *)8);
      return 1;
    }
  }
  else
  {
    v16 = CScreenMode::GetInstance();
    v17 = (gbAudioManager *)((CScreenMode *)v16)->GetAudioManager();
    v18 = v17;
    if ( v17 )
    {
      ((gbAudioManager *)v17)->DetachAll3D();
      ((gbAudioManager *)v18)->StopSoundStream(0);
      ((gbAudioManager *)v18)->StopSoundStream(2);
      ((gbAudioManager *)v18)->StopSoundStream(1);
    }
    ((PAL3 *)1)->SnapScreen();
    return 1;
  }
}

// 0x0046DF10
char UIScenePanel::ValidateIndex(int nVal)
{
  if ( nVal >= this->m_Static_13904.m_textx )
    return 0;
  if ( nVal >= 0 )
    return *((_BYTE *)this + nVal + 17392);
  return 0;
}

// 0x0052CAF0
int UIScenePanel::ActivatePanel(int id)
{
  char *v3; // edi
  int v4; // edx
  const char *v5; // eax
  void (***v6)(_DWORD, _DWORD); // ebx
  int v7; // edx
  int result; // eax
  UIStatic *v9; // [esp+0x70] [ebp-0x3C]
  UIStatic *v10; // [esp+0x74] [ebp-0x38]
  void (***v11)(_DWORD, _DWORD); // [esp+0x78] [ebp-0x34]
  void (***v12)(_DWORD, _DWORD); // [esp+0x7C] [ebp-0x30]
  void (***v13)(_DWORD, _DWORD); // [esp+0x80] [ebp-0x2C]
  void (***v14)(_DWORD, _DWORD); // [esp+0x84] [ebp-0x28]
  void (***v15)(_DWORD, _DWORD); // [esp+0x88] [ebp-0x24]
  _BYTE v16[16]; // [esp+0x8C] [ebp-0x20] BYREF
  _DWORD v17[4]; // [esp+0x9C] [ebp-0x10] BYREF

  v3 = (char *)this + 1552 * id;
  v9 = (UIStatic *)(v3 + 2424);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 606) + 16))(
    (&off_5707D0)[id],
    v16,
    this);
  ((UIStatic *)(v3 + 2424))->CreateFromTemplate();
  v11 = (void ( ***)(_DWORD, _DWORD))(v3 + 2576);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 644) + 16))(
    (&off_5707D0)[id],
    v16,
    this);
  v10 = (UIStatic *)(v3 + 2728);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 682) + 16))(
    (&off_5707D0)[id],
    v16,
    this);
  ((UIStatic *)(v3 + 2728))->CreateFromTemplate();
  v4 = *((_DWORD *)v3 + 758);
  v17[1] = 0;
  v17[0] = 0;
  v5 = (&off_5707D0)[id];
  v17[2] = 76;
  v17[3] = 12;
  v13 = (void ( ***)(_DWORD, _DWORD))(v3 + 3032);
  (*(void ( **)(const char *, _DWORD *, UIScenePanel *))(v4 + 16))(v5, v17, this);
  v12 = (void ( ***)(_DWORD, _DWORD))(v3 + 2880);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 720) + 16))(
    (&off_5707D0)[id],
    v16,
    this);
  v6 = (void ( ***)(_DWORD, _DWORD))(v3 + 3276);
  (*(void ( **)(char *, const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 819) + 16))(
    v3 + 3276,
    (&off_5707D0)[id],
    v16,
    this);
  sub_446010(v3 + 3276);
  v15 = (void ( ***)(_DWORD, _DWORD))(v3 + 3580);
  (*(void ( **)(const char *, _DWORD *, UIScenePanel *))(*((_DWORD *)v3 + 895) + 16))(
    (&off_5707D0)[id],
    v17,
    this);
  v14 = (void ( ***)(_DWORD, _DWORD))(v3 + 3428);
  (*(void ( **)(const char *, _BYTE *, UIScenePanel *))(*((_DWORD *)v3 + 857) + 16))(
    (&off_5707D0)[id],
    v16,
    this);
  v7 = *((_DWORD *)v3 + 956);
  v3 += 3824;
  (*(void ( **)(char *, const char *, _BYTE *, UIScenePanel *))(v7 + 16))(v3, (&off_5707D0)[id], v16, this);
  sub_446010(v3);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v9->__vftable->ShowWindow)(v9, 0);
  (**v11)(v11, 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10->__vftable->ShowWindow)(v10, 0);
  (**v12)(v12, 0);
  (**v13)(v13, 0);
  (**v6)(v6, 0);
  (**v14)(v14, 0);
  (**v15)(v15, 0);
  result = (**(int ( ***)(char *, _DWORD))v3)(v3, 0);
  this->m_bPanelActive = 1;
  return result;
}

// 0x0052CD40
int UIScenePanel::LayoutSlot(int arg0, int nVal, int nVal2, int nVal3, int nVal4)
{
  char *v6; // esi
  _DWORD a2[8]; // [esp+0x4C] [ebp-0x40] BYREF
  _DWORD v9[8]; // [esp+0x6C] [ebp-0x20] BYREF

  v6 = (char *)this + 1552 * arg0;
  sub_445FA0(v6 + 2424);
  sub_445FA0(v6 + 2576);
  sub_445FA0(v6 + 2728);
  sub_445FA0(v6 + 2880);
  ((UIStatic *)(v6 + 2880))->CreateFromTemplate();
  a2[0] = nVal + 56;
  a2[1] = nVal2 + 138;
  a2[2] = nVal + 132;
  a2[3] = nVal2 + 150;
  sub_43FEC0(a2);
  ((UIScene *)(v6 + 3032))->GetChildCount();
  ((UIScene *)(v6 + 3032))->GetChildAt();
  sub_43FD90((float *)v6 + 758, 2);
  ((UIWnd *)(v6 + 3032))->GetWidth(2);
  ((UIWnd *)(v6 + 3032))->GetHeight(2);
  ((UIWnd *)(v6 + 3032))->GetPosition(1);
  a2[5] = nVal2 + 116;
  a2[4] = nVal + 66;
  a2[7] = nVal2 + 148;
  a2[6] = nVal + 146;
  sub_445FA0(v6 + 3276);
  sub_445FA0(v6 + 3428);
  ((UIStatic *)(v6 + 3428))->CreateFromTemplate();
  v9[0] = nVal + 56;
  v9[1] = nVal2 + 164;
  v9[2] = nVal + 132;
  v9[3] = nVal2 + 176;
  sub_43FEC0(v9);
  ((UIScene *)(v6 + 3580))->GetChildCount();
  ((UIScene *)(v6 + 3580))->GetChildAt();
  sub_43FD90((float *)v6 + 895, 2);
  ((UIWnd *)(v6 + 3580))->GetWidth(2);
  ((UIWnd *)(v6 + 3580))->GetHeight(2);
  ((UIWnd *)(v6 + 3580))->GetPosition(1);
  v9[5] = nVal2 + 142;
  v9[4] = nVal + 66;
  v9[7] = nVal2 + 174;
  v9[6] = nVal + 146;
  return sub_445FA0(v6 + 3824);
}
