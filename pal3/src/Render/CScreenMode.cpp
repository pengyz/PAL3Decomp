#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/CScreenMode.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations
bool sub_42C1C0(int _this); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
int sub_44E9F0(void); // from annotations
int sub_528190(...);
int sub_52FC50(int a2); // from annotations
_DWORD * sub_530270(void); // from annotations

long double CalcAngleBetweenVectors(int nX1, int nY1, int nZ1, int nX2, float fY2, float fZ2); // from annotations

// Unnamed globals (extern)
extern char byte_17B3ED0;
extern char byte_5967B0[3];
extern char byte_A00B01;
extern char byte_A00B07;
extern CHAR byte_DC773C[256];
extern int dword_800000;
extern int dword_C057EC[5];
extern PalScriptMgr * dword_DBA24C;
extern int dword_DC413C;
extern int dword_DC743C;
extern int dword_DC753C;
extern int dword_DC763C;
extern int dword_DCA33C;
extern int dword_DCCD3C;
extern int dword_DCCE3C;
extern int dword_DCCF3C;
extern int dword_DCEC3C;
extern int dword_DDB23C;
extern int dword_DDB33C;
extern int dword_DDB43C;
extern int dword_DDB53C;
extern int dword_DDB63C;
extern float flt_5FC3A8;
extern void * off_5E525C;
extern void * off_5EFF48;
extern void * off_5EFF90;
extern void * off_5EFF98;
extern PtrArray stru_17B3EB0;
extern RoleSystem stru_C059A0;
extern GRPinput stru_D8C2B8;
extern const char * unk_5E524C;
extern int unknown_libname_491;
void __cdecl unknown_libname_513(void);

// 0x0040EB10
void CScreenMode::ProcessGameMode(int nVal, int nVal2)
{
  CScreenMode *v2; // eax
  CScreenMode *v3; // eax
  CScreenMode *Instance; // eax

  g_nRoleInitLevel[nVal] += nVal2;
  if ( nVal2 )
  {
    if ( nVal2 >= 0 )
    {
      if ( nVal2 > 3 )
      {
        Instance = CScreenMode::GetInstance();
        if ( nVal2 > 5 )
          ((CScreenMode *)Instance)->AudioSetPosition("wa010", 1);
        else
          ((CScreenMode *)Instance)->AudioSetPosition("wa009", 1);
      }
      else
      {
        v3 = CScreenMode::GetInstance();
        ((CScreenMode *)v3)->AudioSetPosition("wa008", 1);
      }
    }
    else
    {
      v2 = CScreenMode::GetInstance();
      ((CScreenMode *)v2)->AudioSetPosition("wa048", 1);
    }
  }
}

// 0x0043AFA0
void CScreenMode::SetTooltipText()
{
  char *Source; // [esp+0x4] [ebp+0x4]

  if ( Source )
    strncpy(this->m_szTooltip, Source, 0x7Fu);
  else
    memset(this->m_szTooltip, 0, 0x80u);
}

// 0x0043C550
void CScreenMode::SetProgress(float fProgress)
{
  double v3; // st7
  int m_nProgressTimer; // eax
  int m_nBarPosY; // edi
  int m_nBarHeight; // ecx
  int m_nBarParam; // eax
  int m_nProgressBase; // ebx
  __int64 v9; // rax
  int v10; // ecx
  int v11; // edi
  __int64 v12; // rax
  int v13; // ecx
  int m_nBarPosX; // ebx
  int m_nBarWidth; // ecx
  int v16; // eax
  int v17; // ebp
  int v18; // edi
  __int64 v19; // rax
  int m_nScreenHeight; // ecx
  int v21; // ebp
  int v22; // ebx
  int v23; // edi
  __int64 v24; // rax
  int fProgressa; // [esp+0x18] [ebp+0x4]

  v3 = this->m_fProgressCur / this->m_fProgressMax;
  this->m_fProgress = fProgress;
  m_nProgressTimer = this->m_nProgressTimer;
  this->m_fProgressNorm = v3;
  this->m_fProgressRatio = fProgress / v3;
  if ( m_nProgressTimer )
  {
    if ( m_nProgressTimer == 1 )
    {
      m_nBarPosY = this->m_nBarPosY;
      m_nBarHeight = this->m_nBarHeight;
      m_nBarParam = this->m_nBarParam;
      this->m_fProgressMax = (double)this->m_nBarPosY
                           - this->m_fProgressParam
                           + this->m_fAccum
                           - ((double)m_nBarHeight
                            + this->m_fBarOffsetW
                            + this->m_fProgressParam);
      if ( m_nBarParam )
      {
        if ( m_nBarParam == 1 )
        {
          m_nProgressBase = this->m_nProgressBase;
          v9 = (__int64)((double)(m_nBarPosY - m_nProgressBase / 2)
                       - this->m_fProgressParam
                       + this->m_fAccum
                       - this->m_fProgressRatio);
          HIDWORD(v9) = this->m_nScreenHeight;
          v10 = this->m_nBarPosX + this->m_nBarTotalSize - HIDWORD(v9);
          this->m_nProgressValB = v9;
          this->m_nProgressValA = v10;
          this->m_nProgressPos = HIDWORD(v9) + v10;
          this->m_nProgress = m_nProgressBase + v9;
        }
      }
      else
      {
        v11 = this->m_nProgressBase;
        v12 = (__int64)((double)(m_nBarHeight - v11 / 2)
                      + this->m_fBarOffsetW
                      + this->m_fProgressParam
                      + this->m_fProgressRatio);
        HIDWORD(v12) = this->m_nScreenHeight;
        v13 = this->m_nBarWidth + this->m_nBarTotalSize - HIDWORD(v12);
        this->m_nProgressValB = v12;
        this->m_nProgressValA = v13;
        this->m_nProgressPos = HIDWORD(v12) + v13;
        this->m_nProgress = v11 + v12;
      }
    }
  }
  else
  {
    m_nBarPosX = this->m_nBarPosX;
    m_nBarWidth = this->m_nBarWidth;
    v16 = this->m_nBarParam;
    this->m_fProgressMax = (double)this->m_nBarPosX
                         - this->m_fProgressParam
                         + this->m_fBarOffsetY
                         - ((double)m_nBarWidth
                          + this->m_fBarOffsetX
                          + this->m_fProgressParam);
    if ( v16 )
    {
      if ( v16 == 1 )
      {
        v17 = this->m_nProgressBase;
        v18 = this->m_nBarHeight + this->m_nBarTotalSize - v17;
        fProgressa = m_nBarPosX - this->m_nScreenHeight / 2;
        this->m_nProgressValB = v18;
        v19 = (__int64)((double)fProgressa - this->m_fProgressParam + this->m_fBarOffsetY - this->m_fProgressRatio);
        m_nScreenHeight = this->m_nScreenHeight;
        this->m_nProgressValA = v19;
        this->m_nProgress = v17 + v18;
        this->m_nProgressPos = m_nScreenHeight + v19;
      }
    }
    else
    {
      v21 = this->m_nScreenHeight;
      v22 = this->m_nProgressBase;
      v23 = this->m_nBarHeight + this->m_nBarTotalSize - v22;
      this->m_nProgressValB = v23;
      v24 = (__int64)((double)(m_nBarWidth - v21 / 2)
                    + this->m_fBarOffsetX
                    + this->m_fProgressParam
                    + this->m_fProgressRatio);
      this->m_nProgressValA = v24;
      this->m_nProgressPos = v21 + v24;
      this->m_nProgress = v22 + v23;
    }
  }
}

// 0x0043DC40
void CScreenMode::SetPosition(int nX,   int nY)
{
  this->m_nPosX = nX;
  this->m_nPosY = nY;
}

// 0x0044E8B0
void CScreenMode::HideUIBars(int nVal, unsigned int dwVal)
{
  int v4; // ebx
  int *p_m_nBarTotalSize; // edi
  char *m_pEnumeration; // edx
  int m_nLayoutParam; // eax
  int v8; // ecx
  CScreenMode *v9; // eax
  CScreenMode *Instance; // eax

  v4 = 12;
  p_m_nBarTotalSize = &this->m_nBarTotalSize;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_nBarTotalSize)(p_m_nBarTotalSize, 0);
    p_m_nBarTotalSize += 41;
    --v4;
  }
  while ( v4 );
  if ( dwVal <= 0xC )
  {
    m_pEnumeration = this->m_pEnumeration;
    *((_DWORD *)&this->m_nPageCounter + 242) = nVal;
    this->m_nLayoutParam = dwVal;
    (*(void ( **)(CScreenMode *, int))m_pEnumeration)(this, 1);
    sub_44E9F0();
    (**((void ( ***)(int *, int))&this->m_nUIState + 41 * this->m_nLayoutParam))(
      &this->m_nUIState + 41 * this->m_nLayoutParam,
      1);
    ((UIScene *)(&this->m_nUIState + 41 * this->m_nLayoutParam))->ResetState();
    m_nLayoutParam = this->m_nLayoutParam;
    v8 = *((_DWORD *)&this->m_nPageCounter + m_nLayoutParam + 244);
    *((_DWORD *)&this->m_nPageCounter + 243) = v8;
    ((UIScene *)(&this->m_nUIState + 41 * m_nLayoutParam))->SetColors(v8);
  }
  if ( dwVal == 1 )
  {
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("we06", 1);
  }
  else if ( dwVal == 11 )
  {
    v9 = CScreenMode::GetInstance();
    ((CScreenMode *)v9)->AudioSetPosition("we05", 1);
  }
}

// 0x00456280
char CScreenMode::GetMouseScroll()
{
  unsigned int v1; // eax

  v1 = (unsigned int)((unsigned __int64)(2290649225LL * *(int *)&g_Input.MouseState[8]) >> 32) >> 31;
  if ( *(_DWORD *)&g_Input.MouseState[8] / 120 <= 0 )
  {
    if ( *(_DWORD *)&g_Input.MouseState[8] / 120 < 0 )
      LOBYTE(v1) = ((TaskBookUI *)this)->ScrollUp(1);
  }
  else
  {
    LOBYTE(v1) = ((TaskBookUI *)this)->ScrollDown(1);
  }
  return v1;
}

// 0x00456E20
void CScreenMode::PauseAllStreams(
        
        void ( ***thisa)(_DWORD, _DWORD),
        unsigned __int8 a2)
{
  int v4; // edi
  float *p_m_ratioh; // esi
  void ( **v6)(float *, _DWORD); // edx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  CScreenMode *v9; // eax
  gbAudioManager *v10; // eax

  (*(void ( **)(float *, _DWORD))LODWORD(this->m_FrameB.m_ratioh))(
    &this->m_FrameB.m_ratioh,
    (unsigned __int8)thisa);
  v4 = 0;
  p_m_ratioh = &this->m_StaticArray.m_ratioh;
  do
  {
    v6 = *(void ( ***)(float *, _DWORD))p_m_ratioh;
    if ( (_BYTE)thisa )
      (*v6)(p_m_ratioh, g_bStateFlags[v4]);
    else
      (*v6)(p_m_ratioh, 0);
    ++v4;
    p_m_ratioh += 94;
  }
  while ( v4 < 52 );
  (**((void ( ***)(char *, _DWORD))this + 5102))((char *)this + 20408, (unsigned __int8)thisa);
  (**((void ( ***)(char *, _DWORD))this + 5016))((char *)this + 20064, (unsigned __int8)thisa);
  if ( (_BYTE)thisa )
  {
    if ( (g_dwGameFlags & 4) != 0 )
    {
      Instance = CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
      if ( AudioManager )
        ((gbAudioManager *)AudioManager)->ResumeSoundStream(1);
    }
  }
  else if ( (g_dwGameFlags & 4) != 0 )
  {
    v9 = CScreenMode::GetInstance();
    v10 = (gbAudioManager *)((CScreenMode *)v9)->GetAudioManager();
    if ( v10 )
      ((gbAudioManager *)v10)->PauseSoundStream(1);
  }
}

// 0x004593C0
void CScreenMode::InitGameUI()
{
  int *p_m_nUIState; // ebx
  int m_nBarWidth; // ecx
  int m_nBarHeight; // eax
  float m_wndAssistA; // edx
  PtrArray *p_m_childs; // edi
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  SaleUI *v12; // eax
  int v13; // eax
  PropUI *v14; // eax
  int inited; // eax
  UIListBox *v16; // eax
  int v17; // eax
  PlayerMgr *v18; // ecx
  UICursor *v19; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v22; // edi
  CScreenMode *v23; // eax
  int v24; // [esp+A4h] [ebp-0x24]
  int v25; // [esp+A8h] [ebp-0x20]
  int v26; // [esp+B8h] [ebp-0x10]

  p_m_nUIState = &this->m_nUIState;
  this->m_nUIMode = 0;
  this->m_nUIState = 0;
  this->m_nScreenWidth = 800;
  this->m_nScreenHeight = 600;
  ((UIListBox *)this)->SetSelTexture(-1, this->m_nUIState, this->m_nUIMode, this->m_nScreenWidth, this->m_nScreenHeight, 0);
  m_nBarWidth = this->m_nBarWidth;
  m_nBarHeight = this->m_nBarHeight;
  m_wndAssistA = this->m_wndAssistA;
  this->m_nLayoutState = m_nBarHeight;
  this->m_nProgressBase = m_nBarWidth;
  this->m_nLayoutOffX = m_nBarWidth + 68;
  this->m_nLayoutOffY = m_nBarHeight + 32;
  (*(void ( **)(float *, int, int *, CScreenMode *))(LODWORD(m_wndAssistA) + 16))(
    &this->m_wndAssistA,
    2,
    &this->m_nProgressBase,
    this);
  ((UIStatic *)&this->m_wndAssistA)->CreateFromTemplate();
  (*((void ( **)(PtrArray *, int, int *, CScreenMode *))this->m_FrameB.m_childs.m_pData + 4))(
    &this->m_FrameB.m_childs,
    2,
    &this->m_nProgressBase,
    this);
  ((UIStatic *)&this->m_FrameB.m_childs)->CreateFromTemplate();
  p_m_childs = &this->m_StaticArray.m_childs;
  v26 = 5;
  do
  {
    (*((void ( **)(PtrArray *, int, int *, CScreenMode *))p_m_childs->m_pData + 4))(
      p_m_childs,
      2,
      &this->m_nProgressBase,
      this);
    ((UIStatic *)p_m_childs)->CreateFromTemplate();
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs->m_pData)(p_m_childs, 0);
    p_m_childs = (PtrArray *)((char *)p_m_childs + 152);
    --v26;
  }
  while ( v26 );
  LOBYTE(v7) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*(void ( **)(char *, int, int *, CScreenMode *, char *, _DWORD, int))(*((_DWORD *)&this->m_Static_816
                                                                                              + 103)
                                                                                            + 28))(
    (char *)&this->m_Static_816 + 412,
    4,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v7);
  ((CScreenMode *)((char *)&this->m_Static_816 + 412))->SetTooltipText();
  sub_446010((char *)&this->m_Static_816 + 412);
  (**((void ( ***)(char *, _DWORD))&this->m_Static_816 + 103))((char *)&this->m_Static_816 + 412, 0);
  LOBYTE(v8) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*(void ( **)(int *, int, int *, CScreenMode *, char *, _DWORD, int))(*(&this->m_nPageCounter.m_hTexture + 30) + 28))(
    &this->m_nPageCounter.m_hTexture + 30,
    5,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v8);
  ((CScreenMode *)(&this->m_nPageCounter.m_hTexture + 30))->SetTooltipText();
  sub_446010(&this->m_nPageCounter.m_hTexture + 30);
  (**((void ( ***)(int *, _DWORD))&this->m_nPageCounter.m_hTexture + 30))(
    &this->m_nPageCounter.m_hTexture + 30,
    0);
  LOBYTE(v9) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*(void ( **)(char *, int, int *, CScreenMode *, char *, _DWORD, int))(*((_DWORD *)&this->m_nPageCounter
                                                                                              + 168)
                                                                                            + 28))(
    (char *)&this->m_nPageCounter + 672,
    6,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v9);
  ((CScreenMode *)((char *)&this->m_nPageCounter + 672))->SetTooltipText();
  sub_446010((char *)&this->m_nPageCounter + 672);
  (**((void ( ***)(char *, _DWORD))&this->m_nPageCounter + 168))((char *)&this->m_nPageCounter + 672, 0);
  LOBYTE(v10) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
// [VFTABLE] ((void ( *)(UIButton *, int, int *, CScreenMode *, char *, _DWORD, int))this->m_BtnTooltipC.__vftable[1].ShowWindow)(
// [VFTABLE]   &this->m_BtnTooltipC,
// [VFTABLE]   7,
// [VFTABLE]   p_m_nUIState,
// [VFTABLE]   this,
// [VFTABLE]   aSubgameHocksho_0,
// [VFTABLE]   0,
// [VFTABLE]   v10);
  ((CScreenMode *)&this->m_BtnTooltipC)->SetTooltipText();
  sub_446010(&this->m_BtnTooltipC);
// [VFTABLE] ((void ( *)(UIButton *, _DWORD))this->m_BtnTooltipC.__vftable->ShowWindow)(&this->m_BtnTooltipC, 0);
  LOBYTE(v11) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*((void ( **)(void **, int, int *, CScreenMode *, char *, _DWORD, int))this->m_pGameUI + 7))(
    &this->m_pGameUI,
    8,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v11);
  ((CScreenMode *)&this->m_pGameUI)->SetTooltipText();
  sub_446010(&this->m_pGameUI);
  (*(void ( **)(void **, _DWORD))this->m_pGameUI)(&this->m_pGameUI, 0);
  v12 = (SaleUI *)operator new(0x19DB8u);
  if ( v12 )
    // [AUTO-COMMENTED] v13 = ((SaleUI *)v12)->SaleUI();
  else
    v13 = 0;
  *(&this->m_ScenePanelB.m_hTexture + 22) = v13;
  v14 = (PropUI *)operator new(0x70DCu);
  if ( v14 )
    inited = ((PropUI *)v14)->InitUI();
  else
    inited = 0;
  *(&this->m_ScenePanelB.m_hTexture + 23) = inited;
  v16 = (UIListBox *)operator new(0x1E56Cu);
  if ( v16 )
    v17 = ((UIListBox *)v16)->InitWithPalScript(v24, v25);
  else
    v17 = 0;
  v18 = (PlayerMgr *)*(&this->m_ScenePanelB.m_hTexture + 22);
  *(&this->m_ScenePanelB.m_hTexture + 24) = v17;
  ((PlayerMgr *)v18)->InitCombatUI((int)this);
  ((PropUI *)*((PropUI **)&this->m_ScenePanelB.m_hTexture + 23))->InitPlayerList((int)this);
  ((LineupUI *)*((LineupUI **)&this->m_ScenePanelB.m_hTexture + 24))->InitListView();
  ((PAL3 *)this)->HandleDeviceReset();
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v22 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->DetachAll3D();
      ((gbAudioManager *)v22)->StopSoundStream(0);
      ((gbAudioManager *)v22)->StopSoundStream(2);
      v23 = CScreenMode::GetInstance();
      ((SoundMgr *)v23)->PlayCPKStream();
    }
  }
  ((UICursor *)v19)->IRender();
  LOBYTE(this->m_bCameraInit) = 1;
}

// 0x0047BE20
void CScreenMode::InitEquipScreen()
{
  int m_nProgressPos; // eax
  UIStatic *p_m_StaticArray; // edi
  int v4; // ebx
  int v5; // eax
  int m_nLayoutOffX; // edx
  int m_nLayoutOffY; // ecx
  int v8; // edx
  int v9; // eax
  int m_align; // edx
  int v11; // ecx
  int v12; // eax
  MainEquipUI *v13; // eax
  MainEquipUI *v14; // eax
  UICursor *v15; // ecx
  int v16; // [esp+0x74] [ebp-0x2C] BYREF
  int v17; // [esp+0x78] [ebp-0x28]
  int v18; // [esp+0x7C] [ebp-0x24]
  int v19; // [esp+0x80] [ebp-0x20]
  int v20; // [esp+0x84] [ebp-0x1C] BYREF
  int v21; // [esp+0x88] [ebp-0x18]
  int v22; // [esp+0x8C] [ebp-0x14]
  int v23; // [esp+0x90] [ebp-0x10]
  int v24; // [esp+0x9C] [ebp-0x4]

  this->m_nLayoutParam = 0;
  this->m_nPosY = 0;
  this->m_nUIState = 800;
  this->m_nUIMode = 600;
  ((UIListBox *)this)->SetSelTexture(-1, this->m_nPosY, this->m_nLayoutParam, this->m_nUIState, this->m_nUIMode, 0);
  m_nProgressPos = this->m_nProgressPos;
  v21 = 136;
  v20 = 360;
  v22 = 428;
  v23 = 168;
  (*(void ( **)(int *, int, int *, CScreenMode *))(m_nProgressPos + 16))(
    &this->m_nProgressPos,
    1025,
    &v20,
    this);
  ((UIStatic *)&this->m_nProgressPos)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CScreenMode *))this->m_FrameB.__vftable->Create)(
// [VFTABLE]   &this->m_FrameB,
// [VFTABLE]   1025,
// [VFTABLE]   &v20,
// [VFTABLE]   this);
  ((UIStatic *)&this->m_FrameB)->CreateFromTemplate();
  p_m_StaticArray = &this->m_StaticArray;
  v4 = 3;
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CScreenMode *))p_m_StaticArray->__vftable->Create)(
// [VFTABLE]   p_m_StaticArray,
// [VFTABLE]   1025,
// [VFTABLE]   &v20,
// [VFTABLE]   this);
    ((UIStatic *)p_m_StaticArray++)->CreateFromTemplate();
    --v4;
  }
  while ( v4 );
  v5 = v21 + 32;
  m_nLayoutOffX = this->m_nLayoutOffX;
  v16 = v20 - 10;
  m_nLayoutOffY = this->m_nLayoutOffY;
  v17 = v21 + 32;
  LOBYTE(v5) = this->m_RoleDialog.m_bk.m_childs.m_nSize;
  v19 = v21 + 32 + m_nLayoutOffY;
  v18 = v20 - 10 + m_nLayoutOffX;
  (*(void ( **)(char *, int, int *, CScreenMode *, char *, _DWORD, int))(*((_DWORD *)&this->m_Static_816 + 104)
                                                                                 + 28))(
    (char *)&this->m_Static_816 + 416,
    1028,
    &v16,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v5);
  sub_446010((char *)&this->m_Static_816 + 416);
  ((CScreenMode *)((char *)&this->m_Static_816 + 416))->SetTooltipText();
  this->m_nPageCounter.m_pTexture = (gbTexture *)1;
  this->m_nPageCounter.m_nShowState = 1;
  this->m_nPageCounter.m_pChildWnd = (UIWnd *)3;
  sub_445FA0(&this->m_StaticArray);
  v8 = this->m_nLayoutOffY;
  v17 = v19;
  v9 = v8 + v19;
  m_align = this->m_Static_816.m_align;
  v19 = v9;
  LOBYTE(v9) = this->m_RoleDialog.m_bk.m_childs.m_nSize;
  (*(void ( **)(int *, int, int *, CScreenMode *, char *, _DWORD, int))(m_align + 28))(
    &this->m_Static_816.m_align,
    1027,
    &v16,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v9);
  sub_446010(&this->m_Static_816.m_align);
  ((CScreenMode *)&this->m_Static_816.m_align)->SetTooltipText();
  *((_DWORD *)&this->m_Static_816 + 70) = 1;
  *((_DWORD *)&this->m_Static_816 + 44) = 1;
  *((_DWORD *)&this->m_Static_816 + 45) = 3;
  sub_445FA0(&this->m_StaticArray + 1);
  v11 = v19;
  v12 = v19 - 2;
  LOBYTE(v11) = this->m_RoleDialog.m_bk.m_childs.m_nSize;
  v19 = v19 - 2 + this->m_nLayoutOffY;
  v17 = v12;
  (*(void ( **)(int *, int, int *, CScreenMode *, char *, _DWORD, int))(*(&this->m_nPageCounter.m_hTexture + 31) + 28))(
    &this->m_nPageCounter.m_hTexture + 31,
    1029,
    &v16,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v11);
  sub_446010(&this->m_nPageCounter.m_hTexture + 31);
  ((CScreenMode *)(&this->m_nPageCounter.m_hTexture + 31))->SetTooltipText();
  *((_DWORD *)&this->m_nPageCounter + 135) = 1;
  *((_DWORD *)&this->m_nPageCounter + 109) = 1;
  *((_DWORD *)&this->m_nPageCounter + 110) = 3;
  sub_445FA0(&this->_embed_UIFrameWnd_968.m_wndcolor);
  v21 = v19;
  v20 = 360;
  v22 = 428;
  v23 = v19 + 11;
  sub_445FA0(&this->m_FrameB);
  ((UITitle_JDHY *)this)->HandleDeviceLostA();
  v13 = (MainEquipUI *)operator new(0x33070u);
  v24 = 0;
  if ( v13 )
    v14 = (MainEquipUI *)((MainEquipUI *)v13)->ctor_9300();
  else
    v14 = 0;
  v24 = -1;
  this->m_nProgressValA = (int)v14;
  ((MainEquipUI *)v14)->InitMainEquipUI((int)this);
  ((UICursor *)v15)->IRender();
}

// 0x00493290
void CScreenMode::GetPlayerAttByIndex(int nIndex)
{
  CScreenMode *v2; // ecx
  int v3; // edx
  unsigned int *v4; // eax
  char *v5; // esi

  v2 = (CScreenMode *)((char *)this + 852 * nIndex + 205836);
  v3 = 12;
  v4 = &Buffer.m_partyActor.m_dwMatMsg[352 * nIndex + 9];
  do
  {
    v5 = (char *)*v4++;
    v2->m_pEnumeration = v5;
    v2 = (CScreenMode *)((char *)v2 + 4);
    --v3;
  }
  while ( v3 );
}

// 0x00494250
int CScreenMode::ResetProgressList()
{
  int m_nProgressBase; // eax
  int i; // edi
  int v4; // eax

  this->m_nProgressBase = 0;
  do
  {
    m_nProgressBase = this->m_nProgressBase;
    if ( *((_BYTE *)&this->m_FrameB.m_ratioh + m_nProgressBase + 1) )
    {
      ((UIListBox *)((char *)this + 9980 * m_nProgressBase + 155308))->GetCurSel();
      ((UIListBox *)((char *)this + 9980 * this->m_nProgressBase + 156404))->GetCurSel();
      ((UIListBox *)((char *)this + 9980 * this->m_nProgressBase + 155856))->GetCurSel();
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        "%d/%d",
        (int)*((float *)this + 2495 * this->m_nProgressBase + 38866),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_nProgressBase + 9]);
      ((UICaption *)((char *)this + 9980 * this->m_nProgressBase + 155552))->SetEnable((int)&this->m_nLayoutOffX, 0);
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        "%d/%d",
        (int)*((float *)this + 2495 * this->m_nProgressBase + 39140),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_nProgressBase + 10]);
      ((UICaption *)((char *)this + 9980 * this->m_nProgressBase + 156648))->SetEnable((int)&this->m_nLayoutOffX, 0);
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        "%d/%d",
        (int)*((float *)this + 2495 * this->m_nProgressBase + 39003),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_nProgressBase + 11]);
      ((UICaption *)((char *)this + 9980 * this->m_nProgressBase + 156100))->SetEnable((int)&this->m_nLayoutOffX, 0);
      ((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 162424))->SetTooltipText();
      ((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 162768))->SetTooltipText();
      ((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 163112))->SetTooltipText();
      ((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 163456))->SetTooltipText();
      ((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 163800))->SetTooltipText();
      ((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 164144))->SetTooltipText();
      for ( i = 0; i < 1520; i += 152 )
      {
        ((UICaption *)((char *)this + 9980 * this->m_nProgressBase + i + 157712))->SetEnable((int)g_szSceneUIText, 0);
        ((UICaption *)((char *)this + 9980 * this->m_nProgressBase + i + 159232))->SetEnable((int)g_szSceneUIText, 0);
      }
    }
    v4 = this->m_nProgressBase + 1;
    this->m_nProgressBase = v4;
  }
  while ( v4 < 5 );
  ((UICaption *)((char *)this + 204424))->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)((char *)this + 204728))->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)((char *)this + 204880))->SetEnable((int)g_szSceneUIText, 0);
  *((_DWORD *)this + 54938) = 0;
  this->m_FrameB.m_texty = -1;
  return ((UIListBox *)((char *)this + 217412))->ClearAll();
}

// 0x004B30C0
char CScreenMode::GetMouseDelta()
{
  unsigned int v1; // eax

  v1 = (unsigned int)((unsigned __int64)(2290649225LL * *(int *)&g_Input.MouseState[8]) >> 32) >> 31;
  if ( *(_DWORD *)&g_Input.MouseState[8] / 120 <= 0 )
  {
    if ( *(_DWORD *)&g_Input.MouseState[8] / 120 < 0 )
      LOBYTE(v1) = ((UITitle_JDHY *)this)->ScrollDown();
  }
  else
  {
    LOBYTE(v1) = ((UITitle_JDHY *)this)->ScrollUp();
  }
  return v1;
}

// 0x00523F30
CScreenMode::CScreenMode()
{
  CScreenMode *v2; // ecx
  char *v3; // eax
  int v4; // edx
  char *v5; // ebp
  char *v6; // ebp
  _DWORD *v7; // ebp

  this->m_nScreenWidth = 800;
  this->m_nScreenHeight = 600;
  this->m_nProgressBase = 0;
  this->m_nLayoutState = 0;
  sub_4422E0(&this->m_FrameB.m_ratioh);
  sub_4422E0(&this->m_StaticArray.m_ratioh);
  sub_4422E0(&this->_embed_UIFrameWnd_816.m_rect.bottom);
  sub_4422E0(&this->m_Static_816);
  sub_4422E0(&this->m_Static_816 + 1);
  sub_4422E0(&this->m_Static_816 + 2);
  ((UIScene *)&this->m_nPageCounter.m_rect.bottom)->ctor();
  UIScene::GetSys();
  UIScene::GetSys();
  *((_DWORD *)&this->m_nPageCounter + 247) = 0;
  this->m_bActive = 0;
  this->m_nScreenActive = 0;
  ((ARC_PlayerAtt *)&this->m_RoleDialog)->Refresh();
  v2 = (CScreenMode *)((char *)this + 5296);
  *((_DWORD *)this + 1311) = 0;
  *((_DWORD *)this + 1312) = 0;
  *((_DWORD *)this + 1313) = 0;
  *((_DWORD *)this + 1314) = 0;
  *((_DWORD *)this + 1316) = 0;
  *((_DWORD *)this + 1317) = 0;
  v3 = (char *)this + 5332;
  v4 = 4;
  do
  {
    v5 = v3 - 24;
    v2->m_pEnumeration = 0;
    *((_DWORD *)v3 - 8) = 0;
    *((_DWORD *)v3 - 7) = 0;
    *(_DWORD *)v5 = 0;
    v2 = (CScreenMode *)((char *)v2 + 48);
    *((_DWORD *)v5 + 1) = 0;
    *((_DWORD *)v5 + 2) = 0;
    v6 = v3 - 12;
    *((_DWORD *)v3 - 3) = 0;
    *((_DWORD *)v6 + 1) = 0;
    *((_DWORD *)v6 + 2) = 0;
    v7 = v3;
    v3 += 48;
    --v4;
    *v7 = 0;
    v7[1] = 0;
    v7[2] = 0;
  }
  while ( v4 );
  *((_BYTE *)this + 5272) = 0;
  *((_BYTE *)this + 5273) = 0;
  *((_BYTE *)this + 5274) = 0;
  *((_BYTE *)this + 5275) = 0;
  *((_BYTE *)this + 5276) = 0;
  *((_BYTE *)this + 5277) = 0;
  *((_BYTE *)this + 5278) = 0;
  *((_DWORD *)this + 1320) = 1065353216;
  *((_DWORD *)this + 1321) = 0;
  *((_DWORD *)this + 1322) = 0;
  *((_DWORD *)this + 1323) = 0;
  *((_DWORD *)this + 1372) = 0;
  memset((char *)this + 5296, 0, 0xC0u);
}

// 0x00524130
void CScreenMode::_CScreenMode()
{
  ((UIRoleDialog *)&this->m_RoleDialog)->_UIRoleDialog();
  ((CCBStageRole *)((char *)&this->m_nPageCounter + 992))->CleanupScript();
  ((UICaption *)((char *)&this->m_nPageCounter + 644))->Destroy2();
  ((UICaption *)(&this->m_nPageCounter.m_hTexture + 23))->Destroy2();
  ((CCBResultWindow *)&this->m_nPageCounter.m_rect.bottom)->_CCBResultWindow();
  ((UIFrameWnd *)(&this->m_Static_816 + 2))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->m_Static_816 + 1))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_816)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->_embed_UIFrameWnd_816.m_rect.bottom)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_StaticArray.m_ratioh)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_FrameB.m_ratioh)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00524980
int CScreenMode::ForwardMessage(int nVal, int nVal2)
{
  ((UIListBox *)this)->Update(nVal, nVal2);
  return 1;
}

// 0x005249A0
int CScreenMode::OnRenderAlt()
{
  int v3; // eax
  CScreenMode *v4; // eax
  CScreenMode *Instance; // eax
  int v6; // eax
  int v7; // ecx
  double v8; // st7
  int v9; // eax
  double v10; // st7
  unsigned __int8 v12; // c0
  unsigned __int8 v13; // c3
  int v14; // ecx
  DWORD Time; // eax
  CScreenMode *v16; // eax
  int v17; // eax
  double bottom; // st7
  const void *v19; // [esp-0x4] [ebp-0x10]
  const char *v20; // [esp-0x4] [ebp-0x10]
  const char *v21; // [esp-0x4] [ebp-0x10]
  float fVal; // [esp+0x0] [ebp-0xC]
  int nVal; // [esp+0x10] [ebp+0x4]
  char *nMsg; // [esp+0x14] [ebp+0x8]
  int nMsga; // [esp+0x14] [ebp+0x8]
  int wParam; // [esp+0x18] [ebp+0xC]

  if ( nVal == 1000 )
  {
    if ( nMsg )
    {
      v17 = *((_DWORD *)this + 1314);
      if ( v17 + ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom <= 500000 )
        bottom = (double)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
      else
        bottom = (double)(500000 - v17);
      fVal = bottom;
      ((UIScene *)&this->m_nPageCounter.m_rect.bottom)->UpdateLayout(fVal);
      *((_DWORD *)this + 1315) = 0;
      sub_445E50((int)(&this->m_nPageCounter.m_hTexture + 23));
      ((UIScene *)&this->m_nPageCounter.m_rect.bottom)->RefreshLayout();
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        &dir[20],
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom - *((_DWORD *)this + 1315));
      ((UICaption *)&this->m_StaticArray.m_ratioh)->SetEnable((int)&this->m_nLayoutOffX, 0);
      sprintf((char *const)&this->m_nLayoutOffX, &dir[20], *((_DWORD *)this + 1315));
      ((UICaption *)&this->_embed_UIFrameWnd_816.m_rect.bottom)->SetEnable((int)&this->m_nLayoutOffX, 0);
      sprintf((char *const)&this->m_nLayoutOffX, &dir[20], 500000);
      ((UICaption *)&this->m_Static_816)->SetEnable((int)&this->m_nLayoutOffX, 0);
      sprintf((char *const)&this->m_nLayoutOffX, &dir[20], *((_DWORD *)this + 1314));
      ((UICaption *)(&this->m_Static_816 + 1))->SetEnable((int)&this->m_nLayoutOffX, 0);
      switch ( *((_DWORD *)this + 1316) )
      {
        case 0:
          ((UICaption *)(&this->m_Static_816 + 2))->SetEnable((int)dword_DDB63C, 0);
          break;
        case 1:
          ((UICaption *)(&this->m_Static_816 + 2))->SetEnable((int)dword_DDB53C, 0);
          break;
        case 2:
          ((UICaption *)(&this->m_Static_816 + 2))->SetEnable((int)dword_DDB43C, 0);
          break;
        case 3:
          ((UICaption *)(&this->m_Static_816 + 2))->SetEnable((int)dword_DDB33C, 0);
          break;
        case 4:
          ((UICaption *)(&this->m_Static_816 + 2))->SetEnable((int)dword_DDB23C, 0);
          break;
        default:
          sprintf((char *const)&this->m_nLayoutOffX, byte_5967B0, dword_DCA33C);
          ((UICaption *)(&this->m_Static_816 + 2))->SetEnable((int)&this->m_nLayoutOffX, 0);
          break;
      }
      *((_DWORD *)this + 1317) = *((_DWORD *)this + 1316);
    }
    return 1;
  }
  if ( nVal == 1001 )
  {
    if ( nMsg != &byte_A00B07 )
    {
      if ( nMsg - &byte_A00B07 == 1 )
      {
        ((RoleShadow *)this)->UpdateShadow();
        v20 = unk_5E524C;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v20, 1);
        return 1;
      }
      return 1;
    }
    v6 = *((_DWORD *)this + 1315);
    v7 = v6 + *((_DWORD *)this + 1314);
    *((_DWORD *)this + 1314) = v7;
    if ( v7 <= 0 )
    {
LABEL_36:
      v21 = unk_5E524C;
      v16 = CScreenMode::GetInstance();
      ((CScreenMode *)v16)->AudioSetPosition(v21, 1);
      return 1;
    }
    ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom -= v6;
    v8 = (double)*((int *)this + 1314);
    *(float *)&nMsga = v8;
    if ( v8 > 500000.0 )
    {
      v9 = 4;
LABEL_32:
      v14 = *((_DWORD *)this + 1317);
      *((_DWORD *)this + 1316) = v9;
      if ( v9 <= v14 )
      {
        this->m_bActive = 0;
      }
      else
      {
        this->m_bActive = 1;
        *((_DWORD *)this + 1317) = v9;
        Time = timeGetTime();
        CRT_set_new_handler(Time);
      }
      ((CUtil *)*((CUtil **)this + 1312))->Update(2.0f);
      goto LABEL_36;
    }
    if ( *(float *)&nMsga <= 0.0 )
    {
      v9 = 6;
      goto LABEL_32;
    }
    v10 = 100.0 / (500000.0 / *(float *)&nMsga) * 0.01;
    *((float *)&this->m_nPageCounter + 247) = v10;
    if ( v12 | v13 )
    {
      if ( v10 < 0.25 )
      {
        if ( v10 < 0.5 )
          goto LABEL_26;
        goto LABEL_24;
      }
    }
    else if ( v10 < 0.25 )
    {
LABEL_19:
      v9 = 0;
      goto LABEL_32;
    }
    if ( v10 < 0.5 )
    {
      v9 = 1;
      goto LABEL_32;
    }
LABEL_24:
    if ( v10 < 0.75 )
    {
      v9 = 2;
      goto LABEL_32;
    }
LABEL_26:
    if ( v10 < 0.75 )
    {
      if ( v10 < 1.0 )
        goto LABEL_19;
    }
    else if ( v10 < 1.0 )
    {
      v9 = 3;
      goto LABEL_32;
    }
    v9 = 4;
    goto LABEL_32;
  }
  if ( nVal != 1019 )
    return ((PalScript *)this)->OnMessage(nVal, (int)nMsg, wParam);
  if ( nMsg != &byte_A00B01 || wParam == *((_DWORD *)this + 1315) )
    return 1;
  v3 = *((_DWORD *)this + 1314);
  *((_DWORD *)this + 1315) = wParam;
  if ( v3 + wParam >= 500000 )
    *((_DWORD *)this + 1315) = 500000 - v3;
  sprintf(
    (char *const)&this->m_nLayoutOffX,
    &dir[20],
    ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom - *((_DWORD *)this + 1315));
  ((UICaption *)&this->m_StaticArray.m_ratioh)->SetEnable((int)&this->m_nLayoutOffX, 0);
  sprintf((char *const)&this->m_nLayoutOffX, &dir[20], *((_DWORD *)this + 1315));
  ((UICaption *)&this->_embed_UIFrameWnd_816.m_rect.bottom)->SetEnable((int)&this->m_nLayoutOffX, 0);
  sprintf((char *const)&this->m_nLayoutOffX, &dir[20], *((_DWORD *)this + 1314) + *((_DWORD *)this + 1315));
  ((UICaption *)(&this->m_Static_816 + 1))->SetEnable((int)&this->m_nLayoutOffX, 0);
  sub_445E50((int)(&this->m_nPageCounter.m_hTexture + 23));
  v19 = off_5E525C;
  v4 = CScreenMode::GetInstance();
  ((CScreenMode *)v4)->AudioSetPosition(v19, 1);
  return 1;
}

// 0x00527F50
int CScreenMode::InitSceneAudio(int nVal)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v9; // edi
  CScreenMode *v10; // eax
  int v11; // ecx
  int v12; // ecx
  CScreenMode *v13; // eax
  gbAudioManager *v14; // eax
  gbAudioManager *v15; // edi
  CScreenMode *v16; // eax
  CScreenMode *v17; // eax
  CScreenMode *v18; // eax
  gbAudioManager *v19; // eax
  gbAudioManager *v20; // edi
  int result; // eax

  this->m_FrameB.m_align = nVal;
  switch ( nVal )
  {
    case 0:
      (*((void ( **)(CScreenMode *, int, int, _DWORD))this->m_pEnumeration + 6))(this, 1000, 1, 0);
      v3 = *((_DWORD *)&this->m_nPageCounter + 120);
      if ( v3 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v3 + 24))(v3, 1000, 0, 0);
      v4 = *((_DWORD *)&this->m_nPageCounter + 121);
      if ( v4 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(v4, 1000, 0, 0);
      break;
    case 1:
      v5 = *((_DWORD *)&this->m_nPageCounter + 120);
      if ( v5 )
        (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v5 + 24))(v5, 1000, 1, 0);
      (*((void ( **)(CScreenMode *, int, _DWORD, _DWORD))this->m_pEnumeration + 6))(this, 1000, 0, 0);
      v6 = *((_DWORD *)&this->m_nPageCounter + 121);
      if ( v6 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v6 + 24))(v6, 1000, 0, 0);
      if ( (g_dwGameFlags & 4) != 0 )
      {
        Instance = CScreenMode::GetInstance();
        AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
        v9 = AudioManager;
        if ( AudioManager )
        {
          ((gbAudioManager *)AudioManager)->StopSoundStream(0);
          ((gbAudioManager *)v9)->StopSoundStream(2);
          v10 = CScreenMode::GetInstance();
          ((SoundMgr *)v10)->PlayCPKStream();
        }
      }
      break;
    case 2:
      v11 = *((_DWORD *)&this->m_nPageCounter + 121);
      if ( v11 )
        (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 1, 0);
      v12 = *((_DWORD *)&this->m_nPageCounter + 120);
      if ( v12 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 0, 0);
      (*((void ( **)(CScreenMode *, int, _DWORD, _DWORD))this->m_pEnumeration + 6))(this, 1000, 0, 0);
      break;
    case 3:
      if ( *((_DWORD *)&this->m_nPageCounter + 123) )
      {
        if ( (g_dwGameFlags & 4) != 0 )
        {
          v18 = CScreenMode::GetInstance();
          v19 = (gbAudioManager *)((CScreenMode *)v18)->GetAudioManager();
          v20 = v19;
          if ( v19 )
          {
            ((gbAudioManager *)v19)->DetachAll3D();
            ((gbAudioManager *)v20)->StopSoundStream(0);
            ((gbAudioManager *)v20)->StopSoundStream(2);
            ((gbAudioManager *)v20)->StopSoundStream(1);
          }
        }
      }
      else
      {
        ((SceneObj *)this)->fn_527D60();
        sub_528190("SOFTWARE\\SOFTSTAR\\PAL3_S_GAME", (DWORD)"S_GAME_B", 1u);
        if ( (g_dwGameFlags & 4) != 0 )
        {
          v13 = CScreenMode::GetInstance();
          v14 = (gbAudioManager *)((CScreenMode *)v13)->GetAudioManager();
          v15 = v14;
          if ( v14 )
          {
            ((gbAudioManager *)v14)->StopSoundStream(1);
            ((gbAudioManager *)v15)->StopSoundStream(2);
          }
          if ( CScreenMode::GetInstance()->m_bRenderAlt )
          {
            v16 = CScreenMode::GetInstance();
            ((CScreenMode *)v16)->AudioFadeOut();
          }
          else
          {
            v17 = CScreenMode::GetInstance();
            ((CScreenMode *)v17)->AudioStopAll();
          }
        }
      }
      break;
    default:
      break;
  }
  result = *((_DWORD *)&this->m_nPageCounter + 123);
  if ( result )
  {
    g_nSceneState = 1;
  }
  else
  {
    result = (this->m_FrameB.m_align == 3) + 1;
    g_nSceneState = result;
  }
  return result;
}

// 0x0052D230
char CScreenMode::InitPlayerData()
{
  char v2; // bl
  CScreenMode *Instance; // eax
  CScreenMode *v4; // eax
  double v5; // st7
  __int64 v6; // rax
  CScreenMode *v7; // eax
  char *v8; // edi
  char *v9; // eax
  int v10; // ebp
  int v11; // edx
  CScreenMode *v12; // eax
  double v13; // st7
  int v14; // ebx
  RoleSystem *v15; // esi
  int *v16; // eax
  int v17; // edi
  int v18; // edx
  const void *v20; // [esp-0xC] [ebp-0x11C]
  const void *v21; // [esp-0x8] [ebp-0x118]
  const void *v22; // [esp-0x8] [ebp-0x118]
  const void *v23; // [esp-0x8] [ebp-0x118]
  int *p_m_nProgressBase; // [esp-0x8] [ebp-0x118]
  int v25; // [esp+0xC] [ebp-0x104]
  CHAR String2[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v27; // [esp+0x10D] [ebp-0x3]
  char v28; // [esp+0x10F] [ebp-0x1]

  v2 = 0;
  if ( ((UIRoleSelectDialog *)this)->IsRoleSelectable(0) )
  {
    *(_DWORD *)&Buffer.m_partyActor.m_curact[39] = Buffer.m_partyActor.m_dwMatMsg[9];
    *(_DWORD *)&Buffer.m_partyActor.m_curact[43] = Buffer.m_partyActor.m_dwMatMsg[10];
    Buffer.m_partyActor.m_fDirX = *(float *)&Buffer.m_partyActor.m_bChangedMat;
    sprintf((char *const)&this->m_nProgressBase, "\\n          %s%s", g_szRoleNameTable, (const char *)dword_DCCD3C);
    v2 = 1;
    v21 = off_5EFF98;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v21, 1);
  }
  if ( ((UIRoleSelectDialog *)this)->IsRoleSelectable(4) )
  {
    *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_curact[39] = ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[9];
    *(_DWORD *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_curact[43] = ((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[10];
    ((RoleSystem *)&stru_C059A0)->m_partyActor.m_fDirX = *(float *)&((RoleSystem *)&stru_C059A0)->m_partyActor.m_bChangedMat;
    sprintf((char *const)&this->m_nProgressBase, "\\n          %s%s", byte_DC773C, (const char *)dword_DCCD3C);
    v2 = 1;
    v22 = off_5EFF98;
    v4 = CScreenMode::GetInstance();
    ((CScreenMode *)v4)->AudioSetPosition(v22, 1);
  }
  if ( ((UIRoleSelectDialog *)this)->IsRoleSelectable(1) )
  {
    v5 = *((float *)this + 2546) * 0.0099999998 * (double)Buffer.m_teamSlots[208] + (double)Buffer.m_teamSlots[220];
    g_nRoleInitLevel[1] += 10;
    Buffer.m_teamSlots[220] = (__int64)v5;
    sprintf(
      (char *const)&this->m_nProgressBase,
      "\\n            %s%s+10",
      (const char *)dword_DC743C,
      (const char *)dword_DCCE3C);
    v2 = 1;
    v23 = off_5EFF48;
LABEL_11:
    v7 = CScreenMode::GetInstance();
    ((CScreenMode *)v7)->AudioSetPosition(v23, 1);
    goto LABEL_12;
  }
  if ( ((UIRoleSelectDialog *)this)->IsRoleSelectable(2) )
  {
    Buffer.m_configData[30] = (__int64)(*((float *)this + 2546) * 0.0099999998 * (double)Buffer.m_configData[18]
                                      + (double)Buffer.m_configData[30]);
    g_nRoleInitLevel[2] += 10;
    sprintf(
      (char *const)&this->m_nProgressBase,
      "\\n            %s%s+10",
      (const char *)dword_DC753C,
      (const char *)dword_DCCE3C);
    v2 = 1;
    v23 = off_5EFF48;
    goto LABEL_11;
  }
  if ( ((UIRoleSelectDialog *)this)->IsRoleSelectable(3) )
  {
    v6 = (__int64)(*((float *)this + 2546) * 0.0099999998 * (double)g_SceneMgr.m_partyInitData[28] + (double)dword_C057EC[0]);
    g_nRoleInitLevel[3] += 10;
    dword_C057EC[0] = v6;
    sprintf(
      (char *const)&this->m_nProgressBase,
      "\\n            %s%s+10",
      (const char *)dword_DC763C,
      (const char *)dword_DCCE3C);
    v2 = 1;
    v23 = off_5EFF48;
    goto LABEL_11;
  }
LABEL_12:
  v25 = 0;
  v8 = &Buffer.m_partyActor.m_curact[39];
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v25) )
    {
      *(_DWORD *)v8 = (__int64)(*((float *)this + 2546) * 0.0099999998 * (double)*((int *)v8 - 12) + (double)*(int *)v8);
      v9 = v8;
      v10 = 12;
      do
      {
        v11 = *((_DWORD *)v9 - 12);
        if ( *(_DWORD *)v9 < v11 )
        {
          if ( *(int *)v9 <= 0 )
            *(_DWORD *)v9 = 0;
        }
        else
        {
          *(_DWORD *)v9 = v11;
        }
        v9 += 4;
        --v10;
      }
      while ( v10 );
    }
    v20 = off_5EFF90;
    v12 = CScreenMode::GetInstance();
    ((CScreenMode *)v12)->AudioSetPosition(v20, 1);
    v8 += 1408;
    ++v25;
  }
  while ( (int)v8 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] );
  memset(String2, 0, sizeof(String2));
  v13 = *((float *)this + 2546);
  v27 = 0;
  v28 = 0;
  sprintf(
    String2,
    "          %s%s%s%d%%",
    (const char *)dword_DCEC3C,
    (const char *)dword_DCCF3C,
    (const char *)dword_DC413C,
    (unsigned int)(__int64)v13);
  p_m_nProgressBase = &this->m_nProgressBase;
  if ( v2 )
    lstrcatA((LPSTR)p_m_nProgressBase, aN);
  else
    lstrcpyA((LPSTR)p_m_nProgressBase, aN);
  lstrcatA((LPSTR)&this->m_nProgressBase, String2);
  ((UICaption *)((char *)this + 10664))->SetEnable((int)&this->m_nProgressBase, 0);
  ((UIRoleSelect *)((char *)this + 10208))->SetByte(1);
  v14 = 0;
  v15 = &Buffer;
  do
  {
    LOBYTE(v16) = *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v14);
    if ( (_BYTE)v16 )
    {
      ((RoleSystem *)v15)->RecalcAggregatedStats(0);
      v16 = (int *)&v15->m_partyActor.m_curact[39];
      v17 = 12;
      do
      {
        v18 = *(v16 - 12);
        if ( *v16 < v18 )
        {
          if ( *v16 <= 0 )
            *v16 = 0;
        }
        else
        {
          *v16 = v18;
        }
        ++v16;
        --v17;
      }
      while ( v17 );
    }
    v15 = (RoleSystem *)((char *)v15 + 1408);
    ++v14;
  }
  while ( (int)v15 < (int)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY );
  return (char)v16;
}

// 0x0052DF40
void CScreenMode::InitCamera(gbGfxManager *pGfx)
{
  gbCamera *v3; // eax
  char *v4; // eax
  char *m_pEnumeration; // eax

  v3 = (gbCamera *)operator new(0x178u);
  if ( v3 )
  {
  }
  else
    v4 = 0;
  this->m_pEnumeration = v4;
  ((gbCamera *)v4)->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  m_pEnumeration = this->m_pEnumeration;
  *((_DWORD *)m_pEnumeration + 1) = 0;
  *(_DWORD *)m_pEnumeration = 1112014848;
  ((gbCamera *)this->m_pEnumeration)->SetLookAt((gbVec3D *)&this->m_bRenderAlt, (gbVec3D *)&this->m_fFadeStart, (gbVec3D *)&this->m_fFadeAlpha);
  LOBYTE(this->m_bCameraInit) = 0;
}

// 0x0052ED30
void CScreenMode::InitEndScreen()
{
  CScreenMode *v2; // eax
  char *VolModNode; // eax
  UILoadingFrm *v4; // eax
  int v5; // eax
  RoleSystem *v6; // eax
  int v7; // eax
  _DWORD *v8; // eax
  OBBox *v9; // eax
  OBBox *BBox; // eax
  CScreenMode *v11; // ecx
  int v12; // edi
  int v13; // ecx
  int v14; // ebx
  int v15; // edx
  float *v16; // eax
  double v17; // st7
  float v18; // ebp
  float m_fFadeStart; // eax
  float *v20; // ebp
  int v21; // ebx
  int v22; // ebp
  int v23; // edi
  int v24; // eax
  int v25; // ebx
  int v26; // edx
  float *v27; // edx
  double v28; // st7
  float v29; // eax
  gbVolumeModifier *v30; // eax
  gbVolumeModifier *v31; // edi
  char *m_pArrayData; // eax
  char *v33; // edi
  unsigned int v34; // edx
  ScreenEffectMgr *v35; // ecx
  ScreenEffect *Instance; // eax
  CScreenMode *v37; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v39; // esi
  CScreenMode *v40; // eax
  float *p_m_fFadeAlpha; // [esp+0x10] [ebp-0x34]
  int v42; // [esp+0x10] [ebp-0x34]
  int v43; // [esp+0x14] [ebp-0x30]
  int v44; // [esp+0x18] [ebp-0x2C]
  float v45; // [esp+0x20] [ebp-0x24]
  float v46; // [esp+0x24] [ebp-0x20]
  float v47; // [esp+0x2C] [ebp-0x18]
  float v48; // [esp+0x30] [ebp-0x14]

  v2 = (CScreenMode *)operator new(0x338u);
  if ( v2 )
    VolModNode = (char *)((CScreenMode *)v2)->CreateVolModNode();
  else
    VolModNode = 0;
  this->m_pEnumeration = VolModNode;
  v4 = (UILoadingFrm *)operator new(0x138u);
  if ( v4 )
    v5 = ((UILoadingFrm *)v4)->ResetState();
  else
    v5 = 0;
  *(_DWORD *)&this->m_bRenderAlt = v5;
  v6 = (RoleSystem *)operator new(0x1DB0u);
  if ( v6 )
    v7 = ((RoleSystem *)v6)->ctor_1D20();
  else
    v7 = 0;
  this->m_nScreenFlags = v7;
  if ( operator new(8u) )
    v8 = sub_530270();
  else
    v8 = 0;
  this->m_nField0C = (int)v8;
  v9 = (OBBox *)operator new(0xEB8u);
  if ( v9 )
    BBox = ((OBBox *)v9)->GetBBox();
  else
    BBox = 0;
  v11 = *(CScreenMode **)&this->m_bRenderAlt;
  LODWORD(this->m_fFadeStart) = BBox;
  ((CScreenMode *)v11)->InitCamera(gfxMgr);
  ((RoleAtt *)this->m_pEnumeration)->LoadModelAndInit();
  ((RoleAtt *)this->m_pEnumeration)->SetSAIDAndImage(*(int **)&this->m_bRenderAlt);
  this->m_pEnumeration[772] = this->m_FrameB.m_rect.top != 4;
  ((RoleSystem *)this->m_nScreenFlags)->InitAllSystems();
  ((RoleAtt *)this->m_nScreenFlags)->SetPageParam((int)this->m_pEnumeration);
  ((RoleAtt *)this->m_nScreenFlags)->SetPageParam2((int)this);
  ((SceneObj *)this->m_nField0C)->LoadDefaultModel();
  ((SceneObj *)this->m_nField0C)->SetScriptDel(*(_DWORD *)&this->m_bRenderAlt);
  ((SceneObj *)LODWORD(this->m_fFadeStart))->LoadObstruction();
  ((UISceneMap *)LODWORD(this->m_fFadeStart))->SetCurrentMapID(*(_DWORD *)&this->m_bRenderAlt);
  memset(&this->m_fFadeAlpha, 0, 0x18u);
  v12 = 0;
  p_m_fFadeAlpha = &this->m_fFadeAlpha;
  v13 = 0;
  v44 = (*((_DWORD *)this->m_pEnumeration + 141) - 1560) / 6;
  v14 = v44 + 300;
  v15 = 32 * (v44 + 300);
  do
  {
    v13 += 12;
    *(_DWORD *)p_m_fFadeAlpha = v14;
    v16 = (float *)(v15 + *((_DWORD *)this->m_pEnumeration + 142));
    v17 = *v16;
    v18 = v16[1];
    v46 = v16[2];
    m_fFadeStart = this->m_fFadeStart;
    v45 = v18;
    *(float *)(v13 + LODWORD(m_fFadeStart) + 1668) = v17;
    v20 = (float *)(v12 + LODWORD(m_fFadeStart) + 1808);
    v12 += 76;
    *(float *)(v13 + LODWORD(m_fFadeStart) + 1672) = v45;
    *(float *)(v13 + LODWORD(m_fFadeStart) + 1676) = v46;
    *(float *)(v12 + LODWORD(m_fFadeStart) + 1724) = *(float *)(v13 + LODWORD(m_fFadeStart) + 1668)
                                                   + *(float *)(v12 + LODWORD(m_fFadeStart) + 1724);
    *(float *)(v12 + LODWORD(m_fFadeStart) + 1728) = *(float *)(v13 + LODWORD(m_fFadeStart) + 1672)
                                                   + *(float *)(v12 + LODWORD(m_fFadeStart) + 1728);
    v14 += v44;
    *v20 = *(float *)(v13 + LODWORD(m_fFadeStart) + 1676) + *v20;
    v15 += 32 * v44;
    ++p_m_fFadeAlpha;
  }
  while ( v13 < 72 );
  v21 = 0;
  v22 = 0;
  v43 = 0;
  v23 = 0;
  do
  {
    if ( this->m_FrameB.m_rect.top == 4 )
    {
      *(_BYTE *)(v21 + LODWORD(this->m_fFadeStart) + 3328) = 0;
    }
    else
    {
      v24 = sub_52FC50(v21);
      *(_BYTE *)(v21 + LODWORD(this->m_fFadeStart) + 3328) = !((PAL_GDB *)this)->SetupSkillData(v24);
      v25 = *((_DWORD *)this->m_pEnumeration + 141);
      v42 = (__int64)*((float *)this->m_pEnumeration + 121);
      v26 = rand() % v25;
      v21 = v43;
      v27 = (float *)(*((_DWORD *)this->m_pEnumeration + 142) + 32 * (v26 + 100));
      v28 = *v27;
      v29 = this->m_fFadeStart;
      v47 = (double)(v42 / 3) + (double)v42 + v27[1];
      v48 = v27[2];
      *(float *)(LODWORD(v29) + v23 + 3068) = v47;
      *(float *)(LODWORD(v29) + v23 + 3064) = v28;
      *(float *)(LODWORD(v29) + v23 + 3072) = v48;
      *(float *)(LODWORD(v29) + v22 + 3148) = *(float *)(LODWORD(v29) + v23 + 3064)
                                            + *(float *)(LODWORD(v29) + v22 + 3148);
      *(float *)(LODWORD(v29) + v22 + 3152) = *(float *)(LODWORD(v29) + v23 + 3068)
                                            + *(float *)(LODWORD(v29) + v22 + 3152);
      *(float *)(LODWORD(v29) + v22 + 3156) = *(float *)(LODWORD(v29) + v23 + 3072)
                                            + *(float *)(LODWORD(v29) + v22 + 3156);
    }
    v23 += 12;
    ++v21;
    v22 += 76;
    v43 = v21;
  }
  while ( v23 < 36 );
  ((UIAnimateCtrlEX *)this->m_pEnumeration)->SetTextBottom(LODWORD(this->m_fFadeStart));
  ((RenderTarget *)this->m_pEnumeration)->SetState();
  v30 = (gbVolumeModifier *)operator new(0xD8u);
  if ( v30 )
  {
    v31 = v30;
// [VFTABLE] v30[1].__vftable = (void *)1;
// [VFTABLE] v30[24].__vftable = 0;
// [VFTABLE] v30[25].__vftable = 0;
// [VFTABLE] v30[26].__vftable = 0;
// [VFTABLE] v30[40].__vftable = 0;
// [VFTABLE] v30[41].__vftable = 0;
// [VFTABLE] v30[42].__vftable = 0;
// [VFTABLE] v30[43].__vftable = 0;
// [VFTABLE] v30[44].__vftable = 0;
// [VFTABLE] v30[45].__vftable = 0;
  }
  else
  {
    v31 = 0;
  }
  ((gbLightObj *)v31)->Init(2);
// [VFTABLE] v31[7].__vftable = (void *)1036831949;
// [VFTABLE] v31[8].__vftable = (void *)1036831949;
// [VFTABLE] v31[9].__vftable = (void *)1036831949;
// [VFTABLE] v31[10].__vftable = (void *)1065353216;
// [VFTABLE] v31[12].__vftable = (void *)1;
// [VFTABLE] v31[11].__vftable = (void *)1;
// [VFTABLE] v31[3].__vftable = (void *)1049582633;
// [VFTABLE] v31[4].__vftable = (void *)1049582633;
// [VFTABLE] v31[5].__vftable = (void *)1049582633;
// [VFTABLE] v31[16].__vftable = (void *)1092616192;
// [VFTABLE] v31[15].__vftable = (void *)1092616192;
// [VFTABLE] v31[6].__vftable = (void *)1065353216;
  ((gbVolModNode *)&this->m_VolMod)->SetVolModObj(v31);
  ((gbRefObject *)v31)->Release();
  m_pArrayData = this->m_pArrayData;
  this->m_nArrayCapacity = 62;
  if ( m_pArrayData )
  {
    operator delete(m_pArrayData);
    this->m_pArrayData = 0;
  }
  v33 = (char *)operator new(4 * this->m_nArrayCapacity);
  v34 = 4 * this->m_nArrayCapacity;
  this->m_pArrayData = v33;
  memset(v33, 0, v34);
  this->m_FrameB.m_fontcolor.Color = 0;
  LOBYTE(this->m_FrameB.m_id) = 1;
  BYTE1(this->m_FrameB.m_id) = 0;
  BYTE2(this->m_FrameB.m_id) = 0;
  LOBYTE(this->m_FrameB.m_rect.left) = 0;
  UICursor::IRender();
  BYTE2(g_dwUISettings) = 1;
  LOBYTE(this->m_nFadeState) = 0;
  this->m_fFadeTarget = 0.0;
  Instance = ((ScreenEffectMgr *)v35)->GetInstance();
  ((ScreenEffectMgr *)Instance)->ProcessEffect();
  if ( (g_dwGameFlags & 4) != 0 )
  {
    v37 = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)v37)->GetAudioManager();
    v39 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->DetachAll3D();
      ((gbAudioManager *)v39)->StopSoundStream(0);
      ((gbAudioManager *)v39)->StopSoundStream(2);
      v40 = CScreenMode::GetInstance();
      ((SoundMgr *)v40)->PlayCPKStream();
    }
  }
}

// 0x00530440
int CScreenMode::CreateVolModNode()
{
  unknown_libname_491(&this->m_StaticArray.m_disablepicInfo);
  *((_DWORD *)&this->m_StaticArray + 38) = 0;
  *((_DWORD *)&this->m_StaticArray + 39) = 0;
  *((_DWORD *)&this->m_StaticArray + 40) = 0;
  *((_DWORD *)&this->m_StaticArray + 41) = 0;
  *((_DWORD *)&this->m_StaticArray + 42) = 0;
  *((_DWORD *)&this->m_StaticArray + 43) = 0;
  *((_DWORD *)&this->m_StaticArray + 44) = 0;
  *((_DWORD *)&this->m_StaticArray + 45) = 0;
  this->m_nVolNode0 = 0;
  this->m_nVolNode1 = 0;
  this->m_nVolNode2 = 0;
  this->m_nVolNode3 = 0;
  this->m_nVolNode4 = 0;
// [VFTABLE] this->_embed_UIFrameWnd_816.__vftable = 0;
  this->_embed_UIFrameWnd_816.m_fontcolor.Color = 0;
  this->_embed_UIFrameWnd_816.m_wndcolor.Color = 0;
  this->_embed_UIFrameWnd_816.m_id = 0;
  this->_embed_UIFrameWnd_816.m_rect.left = 0;
  LOBYTE(this->_embed_UIFrameWnd_816.m_bfocus) = 0;
  this->_embed_UIFrameWnd_816.m_benable = 0;
  this->_embed_UIFrameWnd_816.m_bvisible = 0;
  LOBYTE(this->_embed_UIFrameWnd_968.m_wndcolor.Color) = 0;
  this->_embed_UIFrameWnd_968.m_fontcolor.Color = 0;
// [VFTABLE] this->_embed_UIFrameWnd_968.__vftable = 0;
  LOBYTE(this->_embed_UIFrameWnd_968.m_rect.right) = 0;
  this->_embed_UIFrameWnd_968.m_rect.top = 0;
  this->_embed_UIFrameWnd_968.m_rect.left = 0;
  LOBYTE(this->_embed_UIFrameWnd_968.m_childs.m_pData) = 0;
  this->_embed_UIFrameWnd_968.m_pfather = 0;
  this->_embed_UIFrameWnd_968.m_rect.bottom = 0;
  ((UIGameOver *)this)->ClearState();
  ((UIGameOver *)this)->ResetState();
  LOBYTE(this->_embed_UIFrameWnd_816.m_pbktex) = 0;
  return (int)this;
}

// 0x00530660
void CScreenMode::FreeNPCBuffer()
{
  char *m_pEnumeration; // edi
  void ( ***v3)(_DWORD, int); // ecx

  m_pEnumeration = this->m_pEnumeration;
  if ( this->m_pEnumeration )
  {
    ((NPC *)this->m_pEnumeration)->FreeBuffer();
    operator delete(m_pEnumeration);
    this->m_pEnumeration = 0;
  }
  v3 = *(void ( ****)(_DWORD, int))&this->m_bRenderAlt;
  if ( v3 )
  {
    (**v3)(v3, 1);
    *(_DWORD *)&this->m_bRenderAlt = 0;
  }
}

// 0x00533250
double CScreenMode::LoadScreenScene(double result, float result_4)
{
  double v3; // st7
  int m_nBarWidth; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  void ( **v9)(int, bool); // edx
  double v11; // st7
  float *p_m_fFadeSpeed; // edi
  unsigned __int8 v13; // c0
  unsigned __int8 v14; // c3
  double v15; // st7
  double v16; // st6
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  long double v25; // st7
  long double v26; // st7
  RoleSystem *v27; // edx
  int *p_m_bvisible; // eax
  int v29; // edi
  int v30; // eax
  int v31; // eax
  void ( **v32)(int, bool); // edx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v35; // esi
  CScreenMode *v36; // eax
  CScreenMode *v37; // eax
  double v38; // st7
  double fValue; // [esp+0x0] [ebp-0x38]
  float fValuea; // [esp+0x0] [ebp-0x38]
  float fValueb; // [esp+0x0] [ebp-0x38]
  int v42; // [esp+0x8] [ebp-0x30]
  float v43; // [esp+0x14] [ebp-0x24]
  float v44; // [esp+0x18] [ebp-0x20]
  float v45; // [esp+0x1C] [ebp-0x1C]
  float v46; // [esp+0x1C] [ebp-0x1C]
  int m_nField0C; // [esp+0x20] [ebp-0x18]
  float m_fFadeStart; // [esp+0x24] [ebp-0x14]
  float v49; // [esp+0x34] [ebp-0x4]
  float resulta; // [esp+0x3C] [ebp+0x4]
  int resultb; // [esp+0x3C] [ebp+0x4]
  float resultc; // [esp+0x3C] [ebp+0x4]
  int resultd; // [esp+0x3C] [ebp+0x4]

  m_nBarWidth = this->m_nBarWidth;
  if ( m_nBarWidth <= 2 )
  {
    this->m_nBarWidth = m_nBarWidth + 1;
  }
  else if ( !*(_BYTE *)(*((_DWORD *)this->m_pEnumeration + 56) + 345) )
  {
    return v3;
  }
  resulta = flt_5FC3A8 * *(float *)&result;
  if ( BYTE2(this->m_nProgress) )
  {
    v3 = this->m_fCountdown - 0.5;
    this->m_fCountdown = v3;
    if ( v3 <= *(float *)&this->m_nLayoutOffY )
      LODWORD(this->m_fCountdown) = this->m_nLayoutOffY;
    ((UIAnimateCtrlEX *)this->m_pEnumeration)->NormalizeVector(LODWORD(this->m_fFadeSpeed), LODWORD(this->m_fCountdown), LODWORD(this->m_fFadeParam), this->m_nUIMode);
    v6 = *((_DWORD *)this->m_pEnumeration + 56);
    if ( *(_BYTE *)(v6 + 356) )
    {
      v7 = *(_DWORD *)(v6 + 352);
      resultb = v7;
      if ( v7 >= 1000 )
        v7 = 1000;
      *(_DWORD *)(v6 + 348) = v7;
      *(float *)&fValue = (float)resultb;
      ((UIScrollBar *)(v6 + 3096))->SetRange(*(float *)&fValue);
      v3 = (double)*(int *)(v6 + 348);
      *(float *)&fValue = v3;
      ((UIProgressBar *)(v6 + 3096))->FindChildByName(*(float *)&fValue);
      v8 = *(_DWORD *)(v6 + 348);
      v9 = *(void ( ***)(int, bool))(v6 + 3096);
      *(_BYTE *)(v6 + 356) = v8 <= 0;
      (*v9)(v6 + 3096, v8 > 0);
      (**(void ( ***)(int, bool))(v6 + 3340))(v6 + 3340, *(_DWORD *)(v6 + 348) > 0);
      g_nMiniGameState = 0;
      g_nMiniGameParam = LODWORD(thisa);
      LODWORD(fValue) = LODWORD(thisa);
      ((UISceneMap *)*(UISceneMap **)&this->m_bRenderAlt)->LoadOverlayTexture(fValue, v42);
      ((UITabCtrl *)this)->Render();
    }
    return v3;
  }
  ((UIScene *)this)->UpdateAlpha();
  ((SceneProp *)this)->CalculateWorldPos(resulta);
  if ( !this->m_bLoadFlag )
  {
    v49 = this->m_fFadeTarget + this->m_fFadeMaxAlpha;
    v15 = ((Scene *)**(_DWORD **)&this->m_bRenderAlt)->GetTileHeight(0, (__int64)((*(float *)&this->m_nField0C + this->m_fFadeProgress - *(float *)(this->m_nScreenFlags + 128))
                    / g_fSceneScale), (__int64)((v49 - *(float *)(this->m_nScreenFlags + 136)) / g_fSceneScale), 0)
        + *(float *)&this->m_nPosY;
    *(float *)&this->m_nLayoutParam = v15;
    v45 = this->m_fScreenTimer + this->m_fCountdown;
    v43 = v15 - v45;
    v16 = this->m_fCountdown - this->m_fScreenTimer;
    v44 = v15 - v16;
    if ( v15 <= v45 )
    {
      if ( v15 >= v16 )
      {
        this->m_bFadeActive = 1;
        *(float *)&this->m_nLayoutParam = v45;
      }
      else
      {
        if ( this->m_fFadeAlpha >= (double)v44 )
        {
          if ( this->m_fFadeAlpha > (double)v44 )
          {
            v20 = this->m_fFadeAlpha - resulta * *(float *)&this->m_nPosX;
            this->m_fFadeAlpha = v20;
            if ( v20 <= v44 )
              this->m_fFadeAlpha = v44;
          }
        }
        else
        {
          v19 = resulta * *(float *)&this->m_nPosX + this->m_fFadeAlpha;
          this->m_fFadeAlpha = v19;
          if ( v19 >= v44 )
          {
            this->m_bFadeActive = 0;
            this->m_fFadeAlpha = v44;
            goto LABEL_35;
          }
        }
        this->m_bFadeActive = 0;
      }
    }
    else
    {
      if ( this->m_fFadeAlpha <= (double)v43 )
      {
        if ( this->m_fFadeAlpha < (double)v43 )
        {
          v18 = resulta * *(float *)&this->m_nPosX + this->m_fFadeAlpha;
          this->m_fFadeAlpha = v18;
          if ( v18 >= v43 )
            this->m_fFadeAlpha = v43;
        }
      }
      else
      {
        v17 = this->m_fFadeAlpha - resulta * *(float *)&this->m_nPosX;
        this->m_fFadeAlpha = v17;
        if ( v17 <= v43 )
        {
          this->m_bFadeActive = 0;
          this->m_fFadeAlpha = v43;
          goto LABEL_35;
        }
      }
      this->m_bFadeActive = 0;
    }
LABEL_35:
    if ( this->m_bFadeActive )
    {
      if ( this->m_fFadeAlpha <= 0.0 )
      {
        if ( this->m_fFadeAlpha >= 0.0 )
          goto LABEL_42;
        v22 = resulta * *(float *)&this->m_nPosX + this->m_fFadeAlpha;
        this->m_fFadeAlpha = v22;
        if ( v22 < 0.0 )
          goto LABEL_42;
        goto LABEL_41;
      }
      v21 = this->m_fFadeAlpha - resulta * *(float *)&this->m_nPosX;
      this->m_fFadeAlpha = v21;
      if ( v21 <= 0.0 )
LABEL_41:
        this->m_fFadeAlpha = 0.0;
    }
LABEL_42:
    v23 = resulta * *(float *)&this->m_nFadeState * 1.96 + *(float *)&this->m_nField0C;
    *(float *)&this->m_nField0C = v23;
    v46 = resulta * this->m_fFadeAlpha;
    this->m_fFadeStart = v46;
    resultc = resulta * *(float *)&this->m_nScreenHeight;
    this->m_fFadeTarget = resultc;
    if ( v23 > resultc )
      *(float *)&this->m_nField0C = resultc;
    v24 = -resultc;
    if ( v24 > *(float *)&this->m_nField0C )
      *(float *)&this->m_nField0C = v24;
    if ( v46 > (double)resultc )
      this->m_fFadeStart = resultc;
    if ( v24 > this->m_fFadeStart )
      this->m_fFadeStart = v24;
    m_nField0C = this->m_nField0C;
    v25 = CalcAngleBetweenVectors(0, 0, 1065353216, m_nField0C, 0.0, resultc);
    *(float *)&this->m_nUIMode = v25;
    if ( *(float *)&m_nField0C < 0.0 )
      *(float *)&this->m_nUIMode = 180.0 - v25 + 180.0 - 360.0;
    m_fFadeStart = this->m_fFadeStart;
    v26 = CalcAngleBetweenVectors(0, 0, 1065353216, 0, m_fFadeStart, 1.0);
    *(float *)&this->m_nScreenWidth = v26;
    if ( m_fFadeStart < 0.0 )
      *(float *)&this->m_nScreenWidth = 180.0 - v26 + 180.0 - 360.0;
    if ( *(float *)&this->m_nScreenWidth < -36.0 )
      this->m_nScreenWidth = -1039138816;
    if ( *(float *)&this->m_nScreenWidth > 36.0 )
      this->m_nScreenWidth = 1108344832;
    p_m_fFadeSpeed = &this->m_fFadeSpeed;
    *((float *)this->m_pEnumeration + 49) = *(float *)&this->m_nScreenWidth;
    this->m_fFadeSpeed = this->m_fFadeSpeed + *(float *)&this->m_nField0C;
    this->m_fCountdown = this->m_fFadeStart + this->m_fCountdown;
    v3 = this->m_fFadeTarget + this->m_fFadeParam;
    this->m_fFadeParam = v3;
    this->m_fFadeProgress = this->m_fFadeSpeed;
    this->m_VolMod = LODWORD(this->m_fCountdown);
    this->m_fFadeMaxAlpha = this->m_fFadeParam;
    goto LABEL_59;
  }
  v11 = resulta * 1.58;
  p_m_fFadeSpeed = &this->m_fFadeSpeed;
  if ( v13 | v14 )
  {
    *p_m_fFadeSpeed = *p_m_fFadeSpeed - v11;
    v3 = resulta * 0.68000001 + *(float *)&this->m_nProgressPos;
    *(float *)&this->m_nProgressPos = v3;
    if ( v3 >= 0.0 )
    {
      this->m_nProgressPos = 0;
      this->m_bLoadFlag = 0;
    }
  }
  else
  {
    *p_m_fFadeSpeed = v11 + *p_m_fFadeSpeed;
    v3 = *(float *)&this->m_nProgressPos - resulta * 0.68000001;
    *(float *)&this->m_nProgressPos = v3;
    if ( v3 <= 0.0 )
    {
      this->m_nProgressPos = 0;
      this->m_bLoadFlag = 0;
    }
  }
LABEL_59:
  ((RoleSystem *)**(RoleSystem ***)&this->m_bRenderAlt)->SetRoleGridPosition(*p_m_fFadeSpeed, *((_DWORD *)p_m_fFadeSpeed + 1), p_m_fFadeSpeed[2], 0);
  ((PAL3 *)this)->CheckViewCollision();
  ((UIAnimateCtrlEX *)this->m_pEnumeration)->NormalizeVector(*(_DWORD *)p_m_fFadeSpeed, *((_DWORD *)p_m_fFadeSpeed + 1), *((_DWORD *)p_m_fFadeSpeed + 2), this->m_nUIMode);
  v27 = g_pRoleSystem;
  g_pRoleSystem->m_fontcolor.Color = *(unsigned int *)p_m_fFadeSpeed;
  v27->m_wndcolor.Color = (unsigned int)p_m_fFadeSpeed[1];
  v27->m_id = (void *)p_m_fFadeSpeed[2];
  g_pRoleSystem->m_wndcolor.Color = 0;
  p_m_bvisible = &g_pRoleSystem->m_FrameA.m_bvisible;
  g_pRoleSystem->m_FrameA.m_bvisible = this->m_nField0C;
  p_m_bvisible[1] = LODWORD(this->m_fFadeStart);
  p_m_bvisible[2] = LODWORD(this->m_fFadeTarget);
  ((RoleSystem *)&g_pRoleSystem)->UpdatePosition();
  if ( ((SceneProp *)this)->CalcScreenPosition() )
  {
    g_nSceneState = 2;
    v29 = *((_DWORD *)this->m_pEnumeration + 56);
    v30 = *(_DWORD *)(v29 + 352);
    resultd = v30;
    if ( v30 >= 1000 )
      v30 = 1000;
    *(_DWORD *)(v29 + 348) = v30;
    fValuea = (float)resultd;
    ((UIScrollBar *)(v29 + 3096))->SetRange(fValuea);
    v3 = (double)*(int *)(v29 + 348);
    fValueb = v3;
    ((UIProgressBar *)(v29 + 3096))->FindChildByName(fValueb);
    v31 = *(_DWORD *)(v29 + 348);
    v32 = *(void ( ***)(int, bool))(v29 + 3096);
    *(_BYTE *)(v29 + 356) = v31 <= 0;
    (*v32)(v29 + 3096, v31 > 0);
    (**(void ( ***)(int, bool))(v29 + 3340))(v29 + 3340, *(_DWORD *)(v29 + 348) > 0);
    ((PalScriptMgr *)dword_DBA24C)->Destroy();
    ((CGameData *)&g_gamefrm)->Load(0);
    HIBYTE(this->m_nProgress) = 1;
    ((GRPinput *)&g_Input)->Reset();
    if ( (g_dwGameFlags & 4) != 0 )
    {
      Instance = CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
      v35 = AudioManager;
      if ( AudioManager )
      {
        ((gbAudioManager *)AudioManager)->StopSoundStream(1);
        ((gbAudioManager *)v35)->StopSoundStream(2);
      }
      if ( CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v36 = CScreenMode::GetInstance();
        ((CScreenMode *)v36)->AudioFadeOut();
      }
      else
      {
        v37 = CScreenMode::GetInstance();
        ((CScreenMode *)v37)->AudioStopAll();
      }
    }
  }
  else if ( ((ArcPastScene *)this)->LoadCityData() )
  {
    g_nMiniGameState = *(_DWORD *)(*(_DWORD *)&this->m_bRenderAlt + 8);
    switch ( *(_DWORD *)(*(_DWORD *)&this->m_bRenderAlt + 8) )
    {
      case 1:
        g_nMiniGameParam = 2;
        LODWORD(fValue) = 2;
        ((UISceneMap *)*(UISceneMap **)&this->m_bRenderAlt)->LoadOverlayTexture(fValue, v42);
        ((UITabCtrl *)this)->Render();
        break;
      case 2:
        g_nMiniGameParam = 3;
        LODWORD(fValue) = 3;
        ((UISceneMap *)*(UISceneMap **)&this->m_bRenderAlt)->LoadOverlayTexture(fValue, v42);
        ((UITabCtrl *)this)->Render();
        break;
      case 3:
        g_nMiniGameParam = 4;
        LODWORD(fValue) = 4;
        ((UISceneMap *)*(UISceneMap **)&this->m_bRenderAlt)->LoadOverlayTexture(fValue, v42);
        ((UITabCtrl *)this)->Render();
        break;
      case 4:
        g_nMiniGameParam = 5;
        LODWORD(fValue) = 5;
        ((UISceneMap *)*(UISceneMap **)&this->m_bRenderAlt)->LoadOverlayTexture(fValue, v42);
        ((UITabCtrl *)this)->Render();
        break;
      case 5:
        g_nMiniGameParam = 0;
        g_nMiniGameState = 0;
        g_bSceneLoaded_0 = 1;
        goto LABEL_75;
      default:
LABEL_75:
        ((UITabCtrl *)this)->Render();
        break;
    }
  }
  else if ( *(int *)(*((_DWORD *)this->m_pEnumeration + 56) + 348) <= 0 )
  {
    v38 = ((Scene *)**(_DWORD **)&this->m_bRenderAlt)->GetTileHeight(0, (__int64)((*p_m_fFadeSpeed - *(float *)(this->m_nScreenFlags + 128)) / g_fSceneScale), (__int64)((p_m_fFadeSpeed[2] - *(float *)(this->m_nScreenFlags + 136)) / g_fSceneScale), 0)
        + *(float *)&this->m_nPosY;
    BYTE2(this->m_nProgress) = 1;
    BYTE1(this->m_nProgress) = 1;
    v3 = v38 - 86.0;
    *(float *)&this->m_nLayoutOffY = v3;
  }
  return v3;
}

// 0x0053C420
int CScreenMode::CloseBinkVideo()
{
  int result; // eax

  result = this->m_nField0C;
  if ( result )
  {
    result = BinkClose(this->m_nField0C);
    this->m_nField0C = 0;
  }
  return result;
}

// 0x0053C440
int CScreenMode::CreateDevice(int a, int b, int c, int d)
{
  return this->OpenBinkVideo((const char *)a, b, c, d);
}

// 0x0053C460
int CScreenMode::WaitBinkFrame()
{
  int result; // eax

  result = this->m_nField0C;
  if ( result )
    return BinkWait(this->m_nField0C);
  return result;
}

// 0x0053C470
int CScreenMode::IsSceneReady()
{
  gbGfxManager *v3; // edi
  int v4; // eax
  int v5; // esi
  int v6[2]; // [esp+0x8] [ebp-0x14] BYREF
  int v7; // [esp+0x10] [ebp-0xC]
  int nVal2; // [esp+0x14] [ebp-0x8]
  int nVal; // [esp+0x18] [ebp-0x4]

  if ( !this->m_nField0C )
    return 1;
  v3 = gfxMgr;
  if ( !(*(int ( **)(int *, _DWORD))(*(_DWORD *)gfxMgr + 84))(v6, 0) )
    return 1;
  switch ( v7 )
  {
    case 3:
      v4 = 10;
      break;
    case 8:
      v4 = 3;
      break;
    case 9:
      v4 = 9;
      break;
    default:
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 88))(gfxMgr);
      return 1;
  }
  v5 = this->CheckFieldReady(nVal, nVal2, v6[1], *(_DWORD *)&this->m_bRenderAlt, this->m_nScreenFlags, v4);
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 88))(gfxMgr);
  (*(void ( **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 68))(
    LODWORD(v3[1].InvViewMatrix.xy),
    0,
    0,
    0,
    0);
  return v5;
}

// 0x0053C530
int CScreenMode::CheckFieldReady(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        int nVal6)
{
  int m_nField0C; // eax

  if ( !this->m_nField0C )
    return 1;
  BinkDoFrame(this->m_nField0C);
  BinkCopyToBuffer(this->m_nField0C, nVal, nVal2, nVal3, nVal4, nVal5, nVal6 | 0x80000000);
  m_nField0C = this->m_nField0C;
  if ( *(_DWORD *)(m_nField0C + 12) == *(_DWORD *)(m_nField0C + 8) )
    return 1;
  BinkNextFrame(m_nField0C);
  return 0;
}

// 0x0053C5A0
int CScreenMode::PlayVideo(int nVal)
{
  gbGfxManager *v3; // esi
  UIQuadManager *Instance; // eax
  UICursor *v5; // ecx
  UIQuadManager *v6; // eax
  UICursor *v8; // ecx
  UIQuadManager *v9; // eax
  struct tagMSG Msg; // [esp+0x4C] [ebp-0x1C] BYREF

  if ( this->m_nField0C )
  {
    v3 = gfxMgr;
    (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                         + 172))(
      LODWORD(gfxMgr[1].InvViewMatrix.xy),
      0,
      0,
      1,
      -16777216,
      1065353216,
      0);
    (*(void ( **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy) + 68))(
      LODWORD(v3[1].InvViewMatrix.xy),
      0,
      0,
      0,
      0);
    (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy)
                                                                         + 172))(
      LODWORD(v3[1].InvViewMatrix.xy),
      0,
      0,
      1,
      -16777216,
      1065353216,
      0);
    Instance = UIQuadManager::GetInstance();
    ((UIRenderObj *)Instance)->_UIRenderObj();
    do
    {
      while ( PeekMessageA(&Msg, 0, 0, 0, 1u) )
      {
        if ( Msg.message == 18 )
        {
          PostQuitMessage(Msg.wParam);
LABEL_13:

          ((UICursor *)v5)->IRender();
          v6 = UIQuadManager::GetInstance();
          ((UIRenderObj *)v6)->_UIRenderObj();
          return 0;
        }
        if ( nVal && Msg.message == 258 && Msg.wParam == 27 )
          goto LABEL_13;
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
      }
    }
    while ( this->WaitBinkFrame() || !this->IsSceneReady() );

    ((UICursor *)v8)->IRender();
    v9 = UIQuadManager::GetInstance();
    ((UIRenderObj *)v9)->_UIRenderObj();
  }
  return 1;
}

// 0x0053C6F0
int CScreenMode::SetViewport(int x, int y)
{
  *(_DWORD *)&this->m_bRenderAlt = x;
  this->m_nScreenFlags = y;
  return x;
}

// 0x0053C710
int CScreenMode::GetWidth()
{
  int result; // eax

  result = this->m_nField0C;
  if ( result )
    return *(_DWORD *)result;
  return result;
}

// 0x0053C720
int CScreenMode::GetHeight()
{
  int result; // eax

  result = this->m_nField0C;
  if ( result )
    return *(_DWORD *)(result + 4);
  return result;
}

// 0x0053C8C0
int CScreenMode::InitDisplayState()
{
  *((_BYTE *)&this->m_RoleDialog + 778) = 0;
  *((_BYTE *)&this->m_RoleDialog + 777) = 0;
  *((_BYTE *)&this->m_RoleDialog + 776) = 0;
  *((_BYTE *)&this->m_RoleDialog + 779) = -56;
  if ( gbColorQuad::ColorQuadFmt )
  {
    *((_BYTE *)this + 6458) = -6;
    *((_BYTE *)this + 6457) = -1;
    *((_BYTE *)this + 6456) = -1;
  }
  else
  {
    *((_BYTE *)this + 6456) = -6;
    *((_BYTE *)this + 6458) = -1;
    *((_BYTE *)this + 6457) = -1;
  }
  *((_BYTE *)this + 6459) = -1;
  *((_DWORD *)&this->m_RoleDialog + 192) = 0;
  *((_DWORD *)&this->m_RoleDialog + 193) = 0;
  memset((char *)&this->m_RoleDialog + 780, 0, 0x64u);
  *((_BYTE *)&this->m_RoleDialog + 780) = 95;
  *((_DWORD *)&this->m_RoleDialog + 189) = 0;
  *((_DWORD *)&this->m_RoleDialog + 188) = 0;
  *((_DWORD *)&this->m_RoleDialog + 190) = 800;
  *((_DWORD *)&this->m_RoleDialog + 191) = 300;
  memset((char *)&this->m_RoleDialog + 880, 0, 0x6A4u);
  memset(&this->m_bRenderAlt, 0, 0x1210u);
  return (int)this;
}

// 0x0053CDD0
int CScreenMode::SetState(int state)
{
  *((_DWORD *)&this->m_RoleDialog + 192) = state;
  return state;
}

// 0x0053D150
PtrArray * CScreenMode::GetSoundList()
{
  if ( (byte_17B3ED0 & 1) == 0 )
  {
    byte_17B3ED0 |= 1u;
    ((PtrArray *)&stru_17B3EB0)->ClearBoth();
    atexit(unknown_libname_513);
  }
  return &stru_17B3EB0;
}

// 0x0053D1E0
void CScreenMode::SetAudioParam()
{
  int i; // edi
  void *v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int j; // edi
  int v8; // ecx
  int v9; // eax
  int k; // edi

  for ( i = 0; i < SLODWORD(this->m_fFadeTarget); ++i )
  {
    if ( i < 0 || i >= SLODWORD(this->m_fFadeTarget) )
      v3 = 0;
    else
      v3 = *(void **)(LODWORD(this->m_fFadeStart) + 4 * i);
    ((PalScriptMgr *)v3)->ClearAllScript();
    if ( !v4 && i >= 0 && i < SLODWORD(this->m_fFadeTarget) )
      *(_DWORD *)(LODWORD(this->m_fFadeStart) + 4 * i) = 0;
  }
  v5 = 0;
  while ( v5 < SLODWORD(this->m_fFadeTarget) )
  {
    if ( v5 >= 0 && v5 < SLODWORD(this->m_fFadeTarget) && *(_DWORD *)(LODWORD(this->m_fFadeStart) + 4 * v5) )
      ++v5;
    else
      ((PtrArray *)&this->m_fFadeStart)->RemoveAt(v5, 1);
  }
  v6 = *(_DWORD *)&this->m_bRenderAlt;
  for ( j = 0; j < v6; ++j )
  {
    if ( j < 0 || j >= v6 )
      v8 = 0;
    else
      v8 = *(_DWORD *)&this->m_pEnumeration[4 * j];
    if ( sub_42C1C0(v8) && j >= 0 && j < *(_DWORD *)&this->m_bRenderAlt )
      *(_DWORD *)&this->m_pEnumeration[4 * j] = 0;
    v6 = *(_DWORD *)&this->m_bRenderAlt;
  }
  v9 = *(_DWORD *)&this->m_bRenderAlt;
  for ( k = 0; k < v9; v9 = *(_DWORD *)&this->m_bRenderAlt )
  {
    if ( k >= 0 && k < v9 && *(_DWORD *)&this->m_pEnumeration[4 * k] )
      ++k;
    else
      ((PtrArray *)this)->RemoveAt(k, 1);
  }
}

// 0x0053D2D0
char CScreenMode::IsAudioReady()
{
  return *(int *)&this->m_bRenderAlt <= 0 && SLODWORD(this->m_fFadeTarget) <= 0;
}

// 0x0053DC50
void CScreenMode::CleanupSoundList()
{
  unsigned int Color; // ebp
  void *i; // esi
  _BYTE *v4; // eax
  int m_nField0C; // eax
  _BYTE *v6; // ecx
  char v7; // al

  Color = this->m_Static_816.m_fontcolor.Color;
// [VFTABLE] for ( i = this->m_Static_816.__vftable; i != (vtbl_0056AE2C *)Color; i = (vtbl_0056AE2C *)((char *)i + 20) )
  {
    if ( i->Render )
    {
      if ( !*(_BYTE *)nearby_53edd0((int)i->Render) || *(_BYTE *)nearby_53edd0((int)i->Render) == 0xFF )
      {
        ((CScreenMode *)i)->FreeSoundBuffer((char *)i->Render - 1, (int)i->Destroy + 2);
      }
      else
      {
        v4 = (_BYTE *)nearby_53edd0((int)i->Render);
        --*v4;
      }
    }
    i->Render = 0;
    i->Update_2ff0 = 0;
    i->Destroy = 0;
  }
// [VFTABLE] operator delete(this->m_Static_816.__vftable);
// [VFTABLE] this->m_Static_816.__vftable = 0;
  this->m_Static_816.m_fontcolor.Color = 0;
  this->m_Static_816.m_wndcolor.Color = 0;
  ((PalScript *)&this->m_FrameB.m_fontcolor)->Cleanup();
  m_nField0C = this->m_nField0C;
  if ( m_nField0C )
  {
    v6 = (_BYTE *)(m_nField0C - 1);
    v7 = *(_BYTE *)(m_nField0C - 1);
    if ( !v7 || v7 == -1 )
      operator delete(v6);
    else
      *v6 = v7 - 1;
  }
  this->m_nField0C = 0;
  this->m_fFadeStart = 0.0;
  this->m_fFadeTarget = 0.0;
}

// 0x0053DD70
void CScreenMode::SetMode(int mode)
{
  gbAudioManager *v3; // eax
  gbAudioManager *v4; // edi
  bool v5; // zf
  unsigned int v6; // eax
  tagRECT *p_m_rect; // esi
  int v8; // [esp+0xC] [ebp-0x268] BYREF
  OpenBaseFile v9; // [esp+0x10] [ebp-0x264] BYREF
  gbAudioManager *v10; // [esp+0x14] [ebp-0x260]
  char Buffer[324]; // [esp+0x18] [ebp-0x25C] BYREF
  gbAudioMgrDesc v12; // [esp+0x15C] [ebp-0x118] BYREF
  int v13; // [esp+0x270] [ebp-0x4]

  if ( (g_dwGameFlags & 5) != 0 )
  {
    v3 = (gbAudioManager *)operator new(0xF4u);
    v10 = v3;
    v13 = 0;
    if ( v3 )
      // [AUTO-COMMENTED] v4 = ((gbAudioManager *)v3)->gbAudioManager(&v8, &v12);
    else
      v4 = 0;
    v13 = -1;
    v5 = v8 == 0;
    this->m_pAudioMgr = v4;
    if ( v5 )
    {
      if ( v4 )
      {
        operator delete(v4);
      }
      this->m_pAudioMgr = 0;
      v6 = g_dwGameFlags;
      LOBYTE(v6) = g_dwGameFlags & 0xFA;
      g_dwGameFlags = v6;
    }
    else
    {
      this->m_Static_816.m_id = 0;
      this->m_nFadeState = 0;
      v13 = 1;
      ((PalScript *)&this->m_FrameB.m_fontcolor)->LoadFromFile("datascript\\music.txt");
      if ( (g_dwGameFlags & 2) != 0 )
      {
        p_m_rect = &this->m_Static_816.m_rect;
        ((CPK *)p_m_rect)->SetOpenMode(1);
        if ( ((CPK *)p_m_rect)->IsValidCPK("music\\music.cpk") )
        {
          ((CPK *)p_m_rect)->Load("music\\music.cpk");
        }
        else
        {
          sprintf(Buffer, "%s%s", (const char *)&Data, "music\\music.cpk");
          if ( ((CPK *)p_m_rect)->IsValidCPK(Buffer) )
            ((CPK *)p_m_rect)->Load(Buffer);
        }
      }
      v13 = -1;
    }
  }
}

// 0x0053DEF0
void CScreenMode::Restore()
{
  gbAudioManager *m_pAudioMgr; // esi

  m_pAudioMgr = this->m_pAudioMgr;
  if ( m_pAudioMgr )
  {
    operator delete(m_pAudioMgr);
    this->m_pAudioMgr = 0;
  }
}

// 0x0053DF70
CScreenMode * CScreenMode::GetInstance()
{
  return &g_CScreenMode;
}

// 0x0053DF80
BOOL CScreenMode::GetByteParam(int nVal, int nVal2)
{
  unsigned __int8 *v2; // eax
  unsigned __int8 *v3; // ecx

  v2 = *(unsigned __int8 **)(nVal2 + 4);
  if ( !v2 )
    v2 = &g_bActorFlag;
  v3 = *(unsigned __int8 **)(nVal + 4);
  if ( !v3 )
    v3 = &g_bActorFlag;
  return _strcmpi((const char *)v3, (const char *)v2) == 0;
}

// 0x0053DFB0
int CScreenMode::PlaySoundStream(const void *pData)
{
  unsigned int Color; // ebp
  void *i; // edi
  gbSound2DNode *v6; // eax
  gbSound2DNode *v7; // eax
  void *v8; // esi
  void *vftable; // eax
  void *v10; // eax
  int v11; // edx
  void *v12; // esi
  char *v13; // esi
  void *v14; // ecx
  int v15; // edx
  int *v16; // edi
  gbSound2DNode *v17; // ecx
  gbSound2DNode *v18; // edi
  int v19; // ebp
  PalScript *v20; // edi
  int v21; // eax
  char v22; // al
  char Color_high; // al
  char pActionType; // [esp+0x13] [ebp-0x13D] BYREF
  PalScriptIdleObj v25; // [esp+0x14] [ebp-0x13C] BYREF
  void *Block; // [esp+0x24] [ebp-0x12C]
  int v27; // [esp+0x28] [ebp-0x128] BYREF
  int v28; // [esp+0x2C] [ebp-0x124]
  int v29; // [esp+0x30] [ebp-0x120]
  int v30; // [esp+0x34] [ebp-0x11C]
  gbSound2DNode *v31; // [esp+0x38] [ebp-0x118]
  gbSound2DNode *v32; // [esp+0x3C] [ebp-0x114]
  char Buffer[260]; // [esp+0x40] [ebp-0x110] BYREF
  int v34; // [esp+0x14C] [ebp-0x4]

  if ( !pData )
    return 0;
  ((Actor *)&v25)->InitAction(&pActionType);
  v34 = 0;
  ((PalScriptIdleObj *)&v25)->UpdateWait(g_szSceneUIText, strlen(g_szSceneUIText));
  Block = 0;
  v34 = 1;
  ((PalScriptIdleObj *)&v25)->UpdateWait(pData, strlen((const char *)pData));
  Color = this->m_Static_816.m_fontcolor.Color;
// [VFTABLE] for ( i = this->m_Static_816.__vftable; i != (vtbl_0056AE2C *)Color; i = (vtbl_0056AE2C *)((char *)i + 20) )
  {
    if ( ((CScreenMode *)i)->GetByteParam((int)&v25) )
      break;
  }
  if ( i == (void *)this->m_Static_816.m_fontcolor.Color
    || ((gbSound2DNode *)i->Create)->IsPlaying() )
  {
    v6 = (gbSound2DNode *)operator new(0x10u);
    v32 = v6;
    LOBYTE(v34) = 2;
    if ( v6 )
      // [AUTO-COMMENTED] v7 = ((gbSound2DNode *)v6)->gbSound2DNode();
    else
      v7 = 0;
    LOBYTE(v34) = 1;
    Block = v7;
    sprintf(Buffer, "snd\\%s.wav", (const char *)pData);
    if ( ((gbSound2DNode *)Block)->LoadFromFile(Buffer) )
    {
// [VFTABLE] vftable = this->m_Static_816.__vftable;
      if ( vftable && (unsigned int)((int)(this->m_Static_816.m_fontcolor.Color - (int)vftable) / 20) >= 0x20 )
      {
// [VFTABLE] v14 = this->m_Static_816.__vftable;
        v15 = 5 * (int)this->m_Static_816.m_id;
        LOBYTE(v27) = pActionType;
        v16 = (int *)(&v14->ShowWindow + v15);
        ((std *)0)->string::_Tidy();
        LOBYTE(v34) = 3;
        ((PalScript *)&v27)->InitScriptObj(v16, 0, 0xFFFFFFFF);
        v17 = (gbSound2DNode *)v16[4];
        v31 = v17;
        LOBYTE(v34) = 4;
        v18 = v17;
        if ( v17 )
        {
          operator delete(v18);
        }
        v19 = 20 * (int)this->m_Static_816.m_id;
// [VFTABLE] v20 = (PalScript *)((char *)this->m_Static_816.__vftable + v19);
        if ( v20 != (PalScript *)&v25 )
        {
          ((PalScript *)v20)->InitScriptObj((int *)&v25, 0, 0xFFFFFFFF);
          v20->m_nState = (int)Block;
        }
        v21 = (int)this->m_Static_816.m_id + 1;
        this->m_Static_816.m_id = (void *)v21;
        if ( v21 >= 32 )
          this->m_Static_816.m_id = 0;
// [VFTABLE] v13 = (char *)this->m_Static_816.__vftable + v19;
        if ( v28 )
        {
          v22 = *(_BYTE *)(v28 - 1);
          if ( !v22 || v22 == -1 )
            operator delete((void *)(v28 - 1));
          else
            *(_BYTE *)(v28 - 1) = v22 - 1;
        }
        v28 = 0;
        v29 = 0;
        v30 = 0;
        if ( v25.m_needscriptdel )
        {
          Color_high = HIBYTE(v25.m_needscriptdel[-1].ColorKey.Color);
          if ( !Color_high || Color_high == -1 )
            operator delete((char *)&v25.m_needscriptdel[-1].ColorKey.Color + 3);
          else
            HIBYTE(v25.m_needscriptdel[-1].ColorKey.Color) = Color_high - 1;
        }
      }
      else
      {
        ((CScreenMode *)&this->m_pSoundStream)->AddSoundEntry((char *)this->m_Static_816.m_fontcolor.Color, (char *)&v25);
// [VFTABLE] v10 = this->m_Static_816.__vftable;
        if ( v10 )
          v11 = (int)(this->m_Static_816.m_fontcolor.Color - (int)v10) / 20;
        else
          v11 = 0;
// [VFTABLE] v12 = this->m_Static_816.__vftable;
        v34 = -1;
        v13 = (char *)v12 + 20 * v11 - 20;
        ((std *)1)->string::_Tidy();
      }
      return (int)v13;
    }
    else
    {
      v8 = Block;
      if ( Block )
      {
        operator delete(v8);
      }
      v34 = -1;
      ((std *)1)->string::_Tidy();
      return 0;
    }
  }
  else
  {
    v34 = -1;
    ((std *)1)->string::_Tidy();
    return (int)i;
  }
}

// 0x0053E2E0
void CScreenMode::AudioSetPosition(const void *pData, int nVal)
{
  int v3; // eax

  if ( (g_dwGameFlags & 1) != 0 )
  {
    v3 = this->PlaySoundStream(pData);
    if ( v3 )
    {
      *(_DWORD *)(*(_DWORD *)(v3 + 16) + 8) = nVal;
      ((gbSound2DNode *)*(gbSound2DNode **)(v3 + 16))->Play();
    }
  }
}

// 0x0053E490
void CScreenMode::AudioUpdate()
{
  if ( (g_dwGameFlags & 1) != 0 )
  {
    if ( g_pCameraCtrl )
    {
      ((gbAudioManager *)this->m_pAudioMgr)->SetListenerPosition(g_pCameraCtrl->m_vecLookAt);
      ((gbAudioManager *)this->m_pAudioMgr)->SetListenerOrientation(g_pCameraCtrl->m_vecLookAt + 1, g_pCameraCtrl->m_vecUpDir);
    }
  }
}

// 0x0053E4E0
void CScreenMode::PlaySoundIfEnabled(void *pSound, int nMode)
{
  if ( (g_dwGameFlags & 1) != 0 )
    this->AudioSetPosition(pSound, nMode);
}

// 0x0053E500
int CScreenMode::GetAudioManager()
{
  return (int)this->m_pAudioMgr;
}

// 0x0053E510
void CScreenMode::PlaySceneMusic(char *pszScene, const char *pszArea, int nVal)
{
  int v5; // [esp+0x0] [ebp-0x210]
  int v6; // [esp+0x0] [ebp-0x210]
  char String1[256]; // [esp+0x10] [ebp-0x200] BYREF
  char Buffer[256]; // [esp+0x110] [ebp-0x100] BYREF

  if ( (g_dwGameFlags & 4) != 0 )
  {
    ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(1);
    ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(2);
    ((PalScript *)&this->m_FrameB.m_fontcolor)->SetDirectory("scene");
    sprintf(Buffer, &dir[24], pszScene, pszArea);
    if ( ((PalScript *)&this->m_FrameB.m_fontcolor)->FindSaveStateString((PalScript *)Buffer, String1, (char *)0x100, v5)
      || ((PalScript *)&this->m_FrameB.m_fontcolor)->FindSaveStateString((PalScript *)pszScene, String1, (char *)0x100, v6) )
    {
      sprintf(Buffer, "music\\%s.mp3", String1);
      if ( _strcmpi(String1, (const char *)&this->m_fFadeAlpha)
        || ((gbAudioManager *)this->m_pAudioMgr)->GetStreamStatus(0) != 1 )
      {
        strcpy((char *)&this->m_fFadeAlpha, String1);
        if ( _strcmpi(String1, "NONE") )
        {
          ((SoundMgr *)this)->PlayCPKStream();
          if ( nVal )
            ((gbAudioManager *)this->m_pAudioMgr)->PauseSoundStream(0);
        }
        else
        {
          ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(0);
        }
      }
    }
  }
}

// 0x0053E680
void CScreenMode::PlayCombatMusic(char *pszSceneName)
{
  int v3; // [esp+0x0] [ebp-0x208]
  char Destination[256]; // [esp+0x8] [ebp-0x200] BYREF
  char Buffer[256]; // [esp+0x108] [ebp-0x100] BYREF

  if ( (g_dwGameFlags & 4) != 0 )
  {
    ((PalScript *)&this->m_FrameB.m_fontcolor)->SetDirectory("combat");
    if ( ((PalScript *)&this->m_FrameB.m_fontcolor)->FindSaveStateString((PalScript *)pszSceneName, Destination, (char *)0x100, v3) )
    {
      sprintf(Buffer, "music\\%s.mp3", Destination);
      ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(0);
      ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(2);
      ((SoundMgr *)this)->PlayCPKStream();
    }
  }
}

// 0x0053E720
unsigned int CScreenMode::StopAllAudio()
{
  unsigned int result; // eax

  result = (unsigned int)this->m_pAudioMgr;
  if ( result )
  {
    result = this->StopAll();
    this->m_bRenderAlt = 0;
  }
  return result;
}

// 0x0053E740
void CScreenMode::PlayAmbientSound(char *pszName, gbAudioManager *pAudioMgr)
{
  CScreenMode *v3; // esi
  int *p_m_nScreenFlags; // ebp
  unsigned int v5; // kr04_4
  unsigned int v6; // ebx
  int m_nField0C; // ecx
  char v8; // al
  unsigned int m_fFadeTarget_low; // eax
  int v10; // ecx
  char v12[256]; // [esp+0xC] [ebp-0x100] BYREF
if ( (g_dwGameFlags & 4) == 0 )
    return;
  ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(1);
  ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(0);
  p_m_nScreenFlags = &this->m_nScreenFlags;
  v5 = strlen(pszName) + 1;
  v6 = v5 - 1;
  if ( v5 - 1 > 0xFFFFFFFD )
// [IDA_MISID]     std::_Xlen();
  m_nField0C = this->m_nField0C;
  if ( !m_nField0C || (v8 = *(_BYTE *)(m_nField0C - 1)) == 0 || v8 == -1 )
  {
    if ( v5 == 1 )
    {
      ((std *)1)->string::_Tidy();
      goto LABEL_16;
    }
    m_fFadeTarget_low = LODWORD(this->m_fFadeTarget);
    if ( m_fFadeTarget_low <= 0x1F && m_fFadeTarget_low >= v6 )
    {
LABEL_15:
      qmemcpy((void *)this->m_nField0C, pszName, v6);
      v10 = this->m_nField0C;
p_m_nScreenFlags[2] = v6;
      *(_BYTE *)(v10 + v6) = 0;
      goto LABEL_16;
    }
    ((std *)1)->string::_Tidy();
LABEL_14:
    ((GRPinput *)&this->m_nScreenFlags)->PollInputState(v6);
    goto LABEL_15;
  }
  if ( v5 != 1 )
    goto LABEL_14;
  *(_BYTE *)(m_nField0C - 1) = v8 - 1;
  this->m_nField0C = 0;
  this->m_fFadeStart = 0.0;
  this->m_fFadeTarget = 0.0;
LABEL_16:
  this->m_nFadeState = (int)pAudioMgr;
  if ( pszName && _strcmpi("NONE", pszName) )
  {
    sprintf(v12, "music\\%s.mp3", pszName);
    ((SoundMgr *)v3)->PlayCPKStream();
  }
  else
  {
    ((gbAudioManager *)this->m_pAudioMgr)->StopSoundStream(2);
  }
}

// 0x0053E890
void CScreenMode::ApplyColorFilter()
{
  unsigned int v1; // edi
  int i; // ebp
  void *vftable; // eax
  void *v5; // ecx
  void *v6; // esi
  void *v7; // edi
  unsigned int Color; // ebp
  void *j; // esi

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
// [VFTABLE] vftable = this->m_Static_816.__vftable;
    if ( !vftable || v1 >= (int)(this->m_Static_816.m_fontcolor.Color - (int)vftable) / 20 )
      break;
// [VFTABLE] v5 = this->m_Static_816.__vftable;
    v6 = *(int (**)(int, int))((char *)&v5->Create + i);
    if ( v6 )
    {
      operator delete(v6);
    }
    ++v1;
  }
// [VFTABLE] v7 = this->m_Static_816.__vftable;
  Color = this->m_Static_816.m_fontcolor.Color;
  for ( j = v7; j != (void *)Color; j = (void *)((char *)j + 20) )
    ((std *)j)->string::~string();
  this->m_Static_816.m_fontcolor.Color = (unsigned int)v7;
}

// 0x0053E950
void CScreenMode::AudioStopAll()
{
  char *v2; // eax
  const char *v3; // [esp-0x8] [ebp-0xC]

  v3 = (const char *)(UISceneUpdate() + 32);
  v2 = (char *)UISceneUpdate();
  this->PlaySceneMusic(v2, v3, 0);
}

// 0x0053E970
unsigned int CScreenMode::StopAll()
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  int v5; // ecx

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
// [VFTABLE] result = (unsigned int)this->m_Static_816.__vftable;
    if ( !result )
      break;
    v5 = this->m_Static_816.m_fontcolor.Color - result;
    result = (unsigned int)((unsigned __int64)(1717986919LL * v5) >> 32) >> 31;
    if ( v1 >= v5 / 20 )
      break;
// [VFTABLE] ((gbSound2DNode *)*(gbSound2DNode **)((char *)&this->m_Static_816.__vftable->Create + i))->Stop();
    ++v1;
  }
  return result;
}

// 0x0053EA60
void CScreenMode::AudioFadeOut()
{
  char *m_nField0C; // eax

  if ( LODWORD(this->m_fFadeStart) )
  {
    m_nField0C = (char *)this->m_nField0C;
    if ( !m_nField0C )
      m_nField0C = (char *)&g_bActorFlag;
    this->PlayAmbientSound(m_nField0C, (gbAudioManager *)this->m_nFadeState);
  }
}

// 0x0053EB50
int CScreenMode::IterateChildList()
{
  int m_nScreenFlags; // ebx
  int i; // esi

  m_nScreenFlags = this->m_nScreenFlags;
  for ( i = *(_DWORD *)&this->m_bRenderAlt; i != m_nScreenFlags; i += 20 )
    ((std *)i)->string::~string();
  operator delete(*(void **)&this->m_bRenderAlt);
  *(_DWORD *)&this->m_bRenderAlt = 0;
  this->m_nScreenFlags = 0;
  this->m_nField0C = 0;
  return 0;
}

// 0x0053EB90
int CScreenMode::AddSoundEntry(char *pszBuf, char *pszBuf2)
{
  int v5; // ebx
  int *m_nScreenFlags; // ecx
  unsigned int v7; // ebp
  int v8; // edx
  unsigned int v9; // eax
  SceneObj *v10; // eax
  SceneObj *v11; // ecx
  SceneObj *v12; // ebx
  SceneObj *i; // ebp
  int SoundCount; // eax
  SceneObj *v15; // ecx
  SceneObj *v17; // [esp+0x10] [ebp-0x8]
  int v18; // [esp+0x14] [ebp-0x4]
  char *pszBufa; // [esp+0x1C] [ebp+0x4]

  v5 = *(_DWORD *)&this->m_bRenderAlt;
  m_nScreenFlags = (int *)this->m_nScreenFlags;
  v18 = (int)&pszBuf[-v5] / 20;
  if ( (this->m_nField0C - (int)m_nScreenFlags) / 20 )
  {
    if ( ((char *)m_nScreenFlags - pszBuf) / 20 )
    {
      this->ComparePointers(m_nScreenFlags - 5, m_nScreenFlags, m_nScreenFlags);
      ((SceneObj *)pszBuf)->LoadFromConfig((int *)(this->m_nScreenFlags - 20), this->m_nScreenFlags);
      ((SceneObj *)(pszBuf + 20))->StringCopyReplace((SceneObj *)pszBuf, pszBuf + 20, pszBuf2);
    }
    else
    {
      this->ComparePointers((int *)pszBuf, m_nScreenFlags, (int *)pszBuf + 5);
      this->InitSceneObjects((int *)this->m_nScreenFlags, 1 - (this->m_nScreenFlags - (int)pszBuf) / 20, (int *)pszBuf2);
      ((SceneObj *)v15)->StringCopyReplace((SceneObj *)pszBuf, (char *)this->m_nScreenFlags, pszBuf2);
    }
    this->m_nScreenFlags += 20;
  }
  else
  {
    if ( !v5 || (v7 = ((int)m_nScreenFlags - v5) / 20, v7 <= 1) )
      v7 = 1;
    if ( v5 )
      v8 = ((int)m_nScreenFlags - v5) / 20;
    else
      v8 = 0;
    v9 = v8 + v7;
    pszBufa = (char *)(v8 + v7);
    if ( (int)(v8 + v7) < 0 )
      v9 = 0;
    v10 = (SceneObj *)operator new(20 * v9);
    v12 = *(SceneObj **)&this->m_bRenderAlt;
    v17 = v10;
    for ( i = v10; v12 != (SceneObj *)pszBuf; i = (SceneObj *)((char *)i + 20) )
    {
      ((SceneObj *)v11)->StringCopyCat(i, v12);
      v12 = (SceneObj *)((char *)v12 + 20);
    }
    ((SceneObj *)v11)->StringCopyCat(i, (SceneObj *)pszBuf2);
    this->ComparePointers((int *)pszBuf, (int *)this->m_nScreenFlags, &i->m_nPass);
    this->DestroyString(*(int **)&this->m_bRenderAlt, (int *)this->m_nScreenFlags);
    operator delete(*(void **)&this->m_bRenderAlt);
    this->m_nField0C = (int)v17 + 20 * (_DWORD)pszBufa;
    SoundCount = this->GetSoundCount();
    *(_DWORD *)&this->m_bRenderAlt = v17;
    this->m_nScreenFlags = (int)(&v17->m_nPass + 5 * SoundCount);
  }
  return *(_DWORD *)&this->m_bRenderAlt + 20 * v18;
}

// 0x0053ED70
int CScreenMode::GetSoundCount()
{
  int result; // eax

  result = *(_DWORD *)&this->m_bRenderAlt;
  if ( result )
    return (this->m_nScreenFlags - result) / 20;
  return result;
}

// 0x0053EDA0
void CScreenMode::DestroyString(int *p_DWORD, int *p_DWORD2)
{
  int *i; // esi

  for ( i = p_DWORD; i != p_DWORD2; i += 5 )
    ((std *)i)->string::~string();
}

// 0x0053EDE0
void CScreenMode::FreeSoundBuffer(void *Block, int nVal)
{
  operator delete(Block);
}

// 0x0053EDF0
int * CScreenMode::ComparePointers(int *p_DWORD, int *p_DWORD2, int *p_DWORD3)
{
  int *v4; // esi
  int *v5; // edi

  v4 = p_DWORD;
  if ( p_DWORD == p_DWORD2 )
    return p_DWORD3;
  v5 = p_DWORD3;
  do
  {
    ((SceneObj *)this)->StringCopyCat((SceneObj *)v5, (SceneObj *)v4);
    v4 += 5;
    v5 += 5;
  }
  while ( v4 != p_DWORD2 );
  return v5;
}

// 0x0053EE30
void CScreenMode::InitSceneObjects(int *p_DWORD, int nVal, int *p_DWORD2)
{
  int i; // edi

  for ( i = nVal; i; --i )
  {
    ((SceneObj *)this)->StringCopyCat((SceneObj *)p_DWORD, (SceneObj *)p_DWORD2);
    p_DWORD += 5;
  }
}

// 0x0053F220
char CScreenMode::UpdateRenderState(int *lpString)
{
  __int64 v3; // rcx
  double v4; // st7
  char *v5; // eax
  int v6; // ecx
  unsigned int v7; // edx
  unsigned int v8; // eax
  double v9; // st7
  double v10; // st6
  __int64 v11; // rcx
  double v12; // st7
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  float v16; // edx
  int v17; // eax
  int v18; // ecx
  float v19; // edx
  float v20; // eax
  char result; // al
  int v22; // edx
  float v23; // eax
  float v24; // ecx
  int v25; // edx
  int v26; // eax
  float v27; // ecx
  float v28; // edx
  int v29; // eax
  int v30; // ecx
  float v31; // edx
  float v32; // eax
  int v33; // ecx
  int v34; // edx
  float v35; // [esp+0x14] [ebp-0x34]
  __int64 v36; // [esp+0x18] [ebp-0x30]
  float v37; // [esp+0x18] [ebp-0x30]
  __int64 v38; // [esp+0x20] [ebp-0x28]
  __int64 v39; // [esp+0x20] [ebp-0x28]
  char v40; // [esp+0x28] [ebp-0x20] BYREF
  float v41; // [esp+0x2C] [ebp-0x1C]
  int v42; // [esp+0x30] [ebp-0x18]
  int v43; // [esp+0x34] [ebp-0x14]
  float v44; // [esp+0x38] [ebp-0x10]
  float v45; // [esp+0x3C] [ebp-0xC]
  int v46; // [esp+0x40] [ebp-0x8]
  int v47; // [esp+0x44] [ebp-0x4]

  HIDWORD(v3) = 0;
  *((_BYTE *)&this->m_Static_816 + 268) = 0;
  if ( lstrlenA((LPCSTR)this) <= 0
    || lstrlenA((LPCSTR)&this->m_StaticArray.m_ratioh) <= 0
    || !*((_DWORD *)&this->m_Static_816 + 56)
    || !*((_DWORD *)&this->m_Static_816 + 57) )
  {
    return 0;
  }
  LODWORD(v3) = *((_DWORD *)&this->m_Static_816 + 52);
  v36 = v3;
  v4 = (double)v3;
  LODWORD(v36) = *((_DWORD *)&this->m_Static_816 + 53);
  v5 = &v40;
  v6 = 4;
  v35 = 1.0 / v4;
  v37 = 1.0 / (double)v36;
  do
  {
    *(_DWORD *)v5 = 0;
    *((_DWORD *)v5 + 1) = 0;
    v5 += 8;
    --v6;
  }
  while ( v6 );
  v7 = *((_DWORD *)&this->m_Static_816 + 53);
  v8 = v7 - *((_DWORD *)&this->m_Static_816 + 55);
  v38 = *((unsigned int *)&this->m_Static_816 + 52);
  v9 = (double)*((unsigned int *)&this->m_Static_816 + 54) * v35;
  v10 = (double)v38;
  LODWORD(v38) = v8 - *((_DWORD *)&this->m_Static_816 + 57);
  v11 = (unsigned int)(*((_DWORD *)&this->m_Static_816 + 56) + *((_DWORD *)&this->m_Static_816 + 54));
  *((_DWORD *)&this->m_Static_816 + 55) = v8;
  v12 = v9 - 0.5 / v10;
  v41 = ((double)v38 - 0.5) * v37;
  v39 = v8;
  v13 = *((_DWORD *)&this->m_Static_816 + 66);
  v44 = ((double)v11 - 0.5) * v35;
  v45 = (double)v39 * v37 - 0.5 / (double)v7;
  if ( v13 )
  {
    v14 = v13 - 1;
    if ( v14 )
    {
      if ( v14 == 1 )
      {
        v15 = v47;
        v16 = v41;
        *((_DWORD *)&this->m_Static_816 + 58) = v46;
        v17 = v42;
        *((_DWORD *)&this->m_Static_816 + 59) = v15;
        *((float *)&this->m_Static_816 + 60) = v12;
        v18 = v43;
        *((float *)&this->m_Static_816 + 61) = v16;
        v19 = v44;
        *((_DWORD *)&this->m_Static_816 + 62) = v17;
        v20 = v45;
        *((_DWORD *)&this->m_Static_816 + 63) = v18;
        *((float *)&this->m_Static_816 + 65) = v20;
        result = 1;
        *((float *)&this->m_Static_816 + 64) = v19;
      }
      else
      {
        result = 1;
      }
      *((_BYTE *)&this->m_Static_816 + 268) = 1;
    }
    else
    {
      v22 = v43;
      v23 = v44;
      *((_DWORD *)&this->m_Static_816 + 58) = v42;
      v24 = v45;
      *((_DWORD *)&this->m_Static_816 + 59) = v22;
      v25 = v46;
      *((float *)&this->m_Static_816 + 60) = v23;
      v26 = v47;
      *((float *)&this->m_Static_816 + 61) = v24;
      v27 = v41;
      *((_DWORD *)&this->m_Static_816 + 63) = v26;
      *((_DWORD *)&this->m_Static_816 + 62) = v25;
      *((float *)&this->m_Static_816 + 64) = v12;
      *((float *)&this->m_Static_816 + 65) = v27;
      *((_BYTE *)&this->m_Static_816 + 268) = 1;
      return 1;
    }
  }
  else
  {
    v28 = v41;
    v29 = v42;
    *((float *)&this->m_Static_816 + 58) = v12;
    v30 = v43;
    *((float *)&this->m_Static_816 + 59) = v28;
    v31 = v44;
    *((_DWORD *)&this->m_Static_816 + 60) = v29;
    v32 = v45;
    *((_DWORD *)&this->m_Static_816 + 61) = v30;
    v33 = v46;
    *((float *)&this->m_Static_816 + 62) = v31;
    v34 = v47;
    *((float *)&this->m_Static_816 + 63) = v32;
    *((_DWORD *)&this->m_Static_816 + 64) = v33;
    *((_DWORD *)&this->m_Static_816 + 65) = v34;
    *((_BYTE *)&this->m_Static_816 + 268) = 1;
    return 1;
  }
  return result;
}

// 0x00569320
int CScreenMode::LoadAudioFromFile(FILE *Stream, int *p_DWORD2)
{
  FILE *v3; // esi
  int v4; // eax
  int *v5; // ebp
  int v6; // edi
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  CScreenMode *Instance; // eax
  float *AudioManager; // eax
  int v12; // edi
  int v13; // eax
  int result; // eax
  int v15; // ebp
  int v16; // ebp
  int v17; // [esp+0x0] [ebp-0x24]
  int v18; // [esp+0x10] [ebp-0x14] BYREF
  int Buffer; // [esp+0x14] [ebp-0x10] BYREF
  float v20; // [esp+0x18] [ebp-0xC] BYREF
  float v21; // [esp+0x1C] [ebp-0x8]
  float v22; // [esp+0x20] [ebp-0x4]

  v3 = Stream;
  v4 = ftell(Stream);
  v5 = p_DWORD2;
  p_DWORD2[40] = v4;
  Buffer = ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].PressTime;
  fwrite(&Buffer, 4u, 1u, v3);
  v6 = 0;
  if ( Buffer > 0 )
  {
    v7 = 0;
    do
    {
      fwrite((const void *)(v7 + ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].Data), 0x18u, 1u, v3);
      ++v6;
      v7 += 24;
    }
    while ( v6 < Buffer );
  }
  v5[41] = ftell(v3);
  v8 = 0;
  v9 = p_DWORD[1];
  if ( v9 )
    Stream = (FILE *)((p_DWORD[2] - v9) / 164);
  else
    Stream = 0;
  fwrite(&Stream, 4u, 1u, v3);
  if ( (int)Stream > 0 )
  {
    v15 = 0;
    do
    {
      ((Actor *)(p_DWORD[1] + v15))->GetAnimDataBuffer((void **)&v3->_ptr, v17);
      ++v8;
      v15 += 164;
    }
    while ( v8 < (int)Stream );
    v5 = p_DWORD2;
  }
  v5[42] = ftell(v3);
  v20 = 1.0;
  v21 = 1.0;
  v22 = 1.0;
  Instance = CScreenMode::GetInstance();
  AudioManager = (float *)((CScreenMode *)Instance)->GetAudioManager();
  v12 = 0;
  if ( AudioManager )
  {
    v20 = AudioManager[52];
    v21 = AudioManager[51];
    v22 = AudioManager[53];
  }
  fwrite(&v20, 0xCu, 1u, v3);
  v5[46] = ftell(v3);
  v13 = p_DWORD[5];
  if ( v13 )
    v18 = (p_DWORD[6] - v13) >> 6;
  else
    v18 = 0;
  fwrite(&v18, 4u, 1u, v3);
  result = v18;
  if ( v18 > 0 )
  {
    v16 = 0;
    do
    {
      fwrite((const void *)(v16 + p_DWORD[5]), 0x40u, 1u, v3);
      result = v18;
      ++v12;
      v16 += 64;
    }
    while ( v12 < v18 );
  }
  return result;
}

// 0x005694F0
int CScreenMode::OpenBinkVideo(const char *szFilename, int nVal, int nVal2, int nFlags)
{
  float *p_m_fFadeStart; // edi
  CPKFile *v7; // ebx
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  void *vftable; // eax

  ((CScreenMode *)pScreen)->CloseBinkVideo();
  if ( !LOBYTE(pScreen[184].m_nVolNode4) && !*((_BYTE *)&pScreen[368].m_nPageCounter.m_hTexture + 72) )
  {
    pScreen->m_nField0C = BinkOpen(szFilename, nFlags);
    goto LABEL_4;
  }
  p_m_fFadeStart = &pScreen->m_fFadeStart;
  v7 = ((CPK *)&pScreen->m_fFadeStart)->Open(szFilename);
  if ( v7 )
  {
// [VFTABLE] vftable = pScreen[184]._embed_UIFrameWnd_816.__vftable;
  }
  else
  {
    p_m_fFadeStart = (float *)&pScreen[184].m_Static_816.m_fonttype;
    v7 = ((CPK *)&pScreen[184].m_Static_816.m_fonttype)->Open(szFilename);
    if ( !v7 )
      goto LABEL_4;
    vftable = (void *)*(&pScreen[368].m_nPageCounter.m_hTexture + 19);
  }
  pScreen->m_nField0C = BinkOpen(vftable, (unsigned int)dword_800000 | nFlags);
  ((CPK *)p_m_fFadeStart)->Close(v7);
LABEL_4:
  if ( !pScreen->m_nField0C )
    return 0;
  Instance = CScreenMode::GetInstance();
  AudioManager = ((CScreenMode *)Instance)->GetAudioManager();
  if ( AudioManager )
    BinkSetVolume(pScreen->m_nField0C, (__int64)(*(float *)(AudioManager + 208) * 65535.0));
  return 1;
}
