// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/CScreenMode.h"
#include "Role/Actor.h"
#include "Misc/ArcPastScene.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Data/CGameData.h"
#include "Combat/CUtil.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Misc/LineupUI.h"
#include "Misc/MainEquipUI.h"
#include "Role/NPC.h"
#include "Misc/NameSys.h"
#include "Role/Object3D.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Misc/PalScriptIdleObj.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "UI/PropUI.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleShadow.h"
#include "Role/RoleSystem.h"
#include "Misc/RoleTask.h"
#include "Misc/SaleUI.h"
#include "Scene/Scene.h"
#include "Scene/SceneObj.h"
#include "Misc/SceneProp.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "Misc/ScriptVM.h"
#include "Misc/SoundMgr.h"
#include "UI/StateUI.h"
#include "Misc/TaskBookUI.h"
#include "Misc/UIAnimateCtrlEX.h"
#include "Misc/UIButton.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UILoadingFrm.h"
#include "Misc/UIParticle.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "UI/UIQuadManager.h"
#include "UI/UIRenderObj.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "Misc/UIRoleSelectDialog.h"
#include "UI/UIScene.h"
#include "Misc/UISceneFrm.h"
#include "Misc/UISceneMap.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "Misc/UITitle_JDHY.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_528190(...);

class PtrArray;

// Unnamed globals (extern)
extern CHAR byte_DC773C[256];
extern int dword_D92780;
extern PalScriptMgr * dword_DBA24C;
extern char dword_DCD63C[];
extern char dword_DCD93C[];
extern char dword_DCE83C[];
extern char dword_DD393C[];
extern char dword_DD3A3C[];
extern char dword_DD3B3C[];
extern PtrArray stru_17B3EB0;

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
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        if ( nVal2 > 5 )
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa010", 1);
        else
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa009", 1);
      }
      else
      {
        v3 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v3))->CScreenMode::AudioSetPosition("wa008", 1);
      }
    }
    else
    {
      v2 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v2))->CScreenMode::AudioSetPosition("wa048", 1);
    }
  }
}

// 0x0042C1C0
bool CScreenMode::sub_42C1C0(int thisa)
{
  bool result; // al
  char m_nUIState; // cl
  bool v4; // zf
  char v5; // cl

  if ( !BYTE1(this->m_pfnPlayVideo) )
    return 1;
  switch ( LOBYTE(this->m_nBarTotalSize) )
  {
    case 5:
      if ( this->m_Static_816.m_bvisible )
        goto LABEL_13;
      m_nUIState = this->m_nUIState;
      if ( !m_nUIState )
        goto LABEL_8;
      v4 = m_nUIState == 3;
      goto LABEL_7;
    case 0x16:
      if ( !this->m_Static_816.m_bvisible )
      {
        v5 = this->m_nUIState;
        if ( !v5 )
          goto LABEL_8;
        v4 = v5 == 2;
LABEL_7:
        if ( v4 )
          goto LABEL_8;
      }
      goto LABEL_13;
    case 0x1A:
      if ( LOBYTE(this->m_nUIState) < 2u )
LABEL_8:
        result = 1;
      else
LABEL_13:
        result = 0;
      break;
    case 0x24:
      result = this->m_Static_816.m_bvisible == 0;
      break;
    default:
      result = (((ScriptVM *)this))->ScriptVM::IsRunning();
      break;
  }
  return result;
}

// 0x0043AFA0
void CScreenMode::SetTooltipText(int nVal1)
{
  if ( nVal1 )
    strncpy(this->m_szTooltip, (const char *)nVal1, 0x7Fu);
  else
    memset(this->m_szTooltip, 0, 0x80u);
}

// 0x0043C550
void CScreenMode::SetProgress(float fProgress)
{
  float v3; // st7
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
      this->m_fProgressMax = (float)this->m_nBarPosY
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
    this->m_fProgressMax = (float)this->m_nBarPosX
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
  p_m_nBarTotalSize = (int *)&this->m_nBarTotalSize;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_nBarTotalSize)(p_m_nBarTotalSize, 0);
    p_m_nBarTotalSize += 41;
    --v4;
  }
  while ( v4 );
  if ( dwVal <= 0xC )
  {
    m_pEnumeration = (char *)this->m_pEnumeration;
    *((_DWORD *)&this->m_nPageCounter + 242) = nVal;
    this->m_nLayoutParam = dwVal;
    (*(void ( **)(CScreenMode *, int))m_pEnumeration)(this, 1);
    ProjectWorldToScreen();
    (**((void ( ***)(int *, int))&this->m_nUIState + 41 * this->m_nLayoutParam))((int *)(&this->m_nUIState + 41 * this->m_nLayoutParam), (int)(1));
    (((UIScene *)(&this->m_nUIState + 41 * this->m_nLayoutParam)))->UIScene::ResetState();
    m_nLayoutParam = this->m_nLayoutParam;
    v8 = *((_DWORD *)&this->m_nPageCounter + m_nLayoutParam + 244);
    *((_DWORD *)&this->m_nPageCounter + 243) = v8;
    (((UIScene *)(&this->m_nUIState + 41 * m_nLayoutParam)))->UIScene::SetColors(v8);
  }
  if ( dwVal == 1 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("we06", 1);
  }
  else if ( dwVal == 11 )
  {
    v9 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v9))->CScreenMode::AudioSetPosition("we05", 1);
  }
}

// 0x00456280
char CScreenMode::GetMouseScroll()
{
  unsigned int v1; // eax

  v1 = (unsigned int)((unsigned __int64)(2290649225i64 * *(int *)&g_Input.MouseState[8]) >> 32) >> 31;
  if ( *(_DWORD *)&g_Input.MouseState[8] / 120 <= 0 )
  {
    if ( *(_DWORD *)&g_Input.MouseState[8] / 120 < 0 )
      LOBYTE(v1) = TaskBookUI_ScrollUp(1);
  }
  else
  {
    LOBYTE(v1) = TaskBookUI_ScrollDown(1);
  }
  return v1;
}

// 0x00456E20
void CScreenMode::PauseAllStreams(void *pStreams, unsigned __int8 a2)
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
    (unsigned __int8)pStreams);
  v4 = 0;
  p_m_ratioh = (float *)&this->m_StaticArray.m_ratioh;
  do
  {
    v6 = *(void ( ***)(float *, _DWORD))p_m_ratioh;
    if ( (_BYTE)pStreams )
      (*v6)(p_m_ratioh, g_bStateFlags[v4]);
    else
      (*v6)(p_m_ratioh, 0);
    ++v4;
    p_m_ratioh += 94;
  }
  while ( v4 < 52 );
  (*(void ( **)(int *, _DWORD))this[3].m_RoleDialog.m_childs.m_nSize)(
    &this[3].m_RoleDialog.m_childs.m_nSize,
    (unsigned __int8)pStreams);
  (**((void ( ***)(int *, _DWORD))&this[3].m_ScenePanelC.m_hTexture + 15))((int *)(&this[3].m_ScenePanelC.m_hTexture + 15), (_DWORD)((unsigned __int8)pStreams));
  if ( (_BYTE)pStreams )
  {
    if ( (g_dwGameFlags & 4) != 0 )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
      if ( AudioManager )
        (((gbAudioManager *)AudioManager))->gbAudioManager::ResumeSoundStream(1);
    }
  }
  else if ( (g_dwGameFlags & 4) != 0 )
  {
    v9 = (CScreenMode *)CScreenMode::GetInstance();
    v10 = (gbAudioManager *)(((CScreenMode *)v9))->CScreenMode::GetAudioManager();
    if ( v10 )
      (((gbAudioManager *)v10))->gbAudioManager::PauseSoundStream(1);
  }
}

// 0x004593C0
void CScreenMode::InitGameUI()
{
  int *p_m_nUIState; // ebx
  int m_nBarWidth; // ecx
  int m_nBarHeight; // eax
  float m_wndAssistA; // edx
  int v6; // eax
  int v7; // eax
  PtrArray *p_m_childs; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  SaleUI *v15; // eax
  int v16; // eax
  PropUI *v17; // eax
  int inited; // eax
  int v19; // eax
  SaleUI *v20; // ecx
  UICursor *v21; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v24; // edi
  CScreenMode *v25; // eax
  int v26; // [esp+A4h] [ebp-0x24]
  int v27; // [esp+B8h] [ebp-0x10]

  p_m_nUIState = (int *)&this->m_nUIState;
  this->m_nUIMode = 0;
  this->m_nUIState = 0;
  this->m_nScreenWidth = 800;
  this->m_nScreenHeight = 600;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, this->m_nUIState, this->m_nUIMode, this->m_nScreenWidth, this->m_nScreenHeight) /* [ROWTABLE] */;
  m_nBarWidth = this->m_nBarWidth;
  m_nBarHeight = this->m_nBarHeight;
  m_wndAssistA = this->m_wndAssistA;
  this->m_nLayoutState = m_nBarHeight;
  this->m_nProgressBase = m_nBarWidth;
  this->m_nLayoutOffX = m_nBarWidth + 68;
  this->m_nLayoutOffY = m_nBarHeight + 32;
  v6 = (*(int ( **)(float *, int, int *, CScreenMode *))(LODWORD(m_wndAssistA) + 16))(
         &this->m_wndAssistA,
         2,
         &this->m_nProgressBase,
         this);
  LOBYTE(v6) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (((UIPushButton *)&this->m_wndAssistA))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagT.tga", v6);
  v7 = (*((int ( **)(PtrArray *, int, int *, CScreenMode *))this->m_FrameB.m_childs.m_pData + 4))(
         &this->m_FrameB.m_childs,
         2,
         &this->m_nProgressBase,
         this);
  LOBYTE(v7) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (((UIPushButton *)&this->m_FrameB.m_childs))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagB.tga", v7);
  p_m_childs = (PtrArray *)&this->m_StaticArray.m_childs;
  v27 = 5;
  do
  {
    v9 = (*((int ( **)(PtrArray *, int, int *, CScreenMode *))p_m_childs->m_pData + 4))(
           p_m_childs,
           2,
           &this->m_nProgressBase,
           this);
    LOBYTE(v9) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
    (((UIPushButton *)p_m_childs))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", v9);
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs->m_pData)(p_m_childs, 0);
    p_m_childs = (PtrArray *)((char *)p_m_childs + 152);
    --v27;
  }
  while ( v27 );
  LOBYTE(v10) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*(void ( **)(char *, int, int *, CScreenMode *, char *, _DWORD, int))(*((_DWORD *)&this->m_Static_816
                                                                                              + 103)
                                                                                            + 28))(
    (char *)&this->m_Static_816 + 412,
    4,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v10);
  (((CScreenMode *)((char *)&this->m_Static_816 + 412)))->CScreenMode::SetTooltipText((int)dword_DD393C);
  AllocObject((char *)&this->m_Static_816 + 412);
  (**((void ( ***)(char *, _DWORD))&this->m_Static_816 + 103))((char *)((char *)&this->m_Static_816 + 412), (_DWORD)(0));
  LOBYTE(v11) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*(void ( **)(int *, int, int *, CScreenMode *, char *, _DWORD, int))(*(&this->m_nPageCounter.m_hTexture + 30) + 28))(
    &this->m_nPageCounter.m_hTexture + 30,
    5,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v11);
  (((CScreenMode *)(&this->m_nPageCounter.m_hTexture + 30)))->CScreenMode::SetTooltipText((int)dword_DD3A3C);
  AllocObject(&this->m_nPageCounter.m_hTexture + 30);
  (**((void ( ***)(int *, _DWORD))&this->m_nPageCounter.m_hTexture + 30))((int *)(&this->m_nPageCounter.m_hTexture + 30), (_DWORD)(0));
  LOBYTE(v12) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*(void ( **)(char *, int, int *, CScreenMode *, char *, _DWORD, int))(*((_DWORD *)&this->m_nPageCounter
                                                                                              + 168)
                                                                                            + 28))(
    (char *)&this->m_nPageCounter + 672,
    6,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v12);
  (((CScreenMode *)((char *)&this->m_nPageCounter + 672)))->CScreenMode::SetTooltipText((int)dword_DD3B3C);
  AllocObject((char *)&this->m_nPageCounter + 672);
  (**((void ( ***)(char *, _DWORD))&this->m_nPageCounter + 168))((char *)((char *)&this->m_nPageCounter + 672), (_DWORD)(0));
  LOBYTE(v13) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*(void ( **)(UIButton *, int, int *, CScreenMode *, char *, _DWORD, int))(*(_DWORD *)((UIWnd *)&this->m_BtnTooltipC)
                                                                                                + 28))(
    &this->m_BtnTooltipC,
    7,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v13);
  (((CScreenMode *)&this->m_BtnTooltipC))->CScreenMode::SetTooltipText((int)dword_DCD63C);
  AllocObject(&this->m_BtnTooltipC);
  (**(void ( ***)(UIButton *, _DWORD))((UIWnd *)&this->m_BtnTooltipC))((UIButton *)(&this->m_BtnTooltipC), (_DWORD)(0));
  LOBYTE(v14) = *((_BYTE *)&this->m_ScenePanelB.m_hTexture + 112);
  (*((void ( **)(void **, int, int *, CScreenMode *, char *, _DWORD, int))this->m_pGameUI + 7))(
    &this->m_pGameUI,
    8,
    p_m_nUIState,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v14);
  (((CScreenMode *)&this->m_pGameUI))->CScreenMode::SetTooltipText((int)dword_DCD93C);
  AllocObject(&this->m_pGameUI);
  (*(void ( **)(void **, _DWORD))this->m_pGameUI)(&this->m_pGameUI, 0);
  v15 = (SaleUI *)operator new(0x19DB8u);
  if ( v15 )
    v15->SaleUI::SaleUI();
  else
    v16 = 0;
  *(&this->m_ScenePanelB.m_hTexture + 22) = v16;
  v17 = (PropUI *)operator new(0x70DCu);
  if ( v17 )
    inited = (((PropUI *)v17))->PropUI::InitUI();
  else
    inited = 0;
  *(&this->m_ScenePanelB.m_hTexture + 23) = inited;
  if ( operator new(0x1E56Cu) )
    v19 = UIListBox_InitWithPalScript(v26);
  else
    v19 = 0;
  v20 = (SaleUI *)*(&this->m_ScenePanelB.m_hTexture + 22);
  *(&this->m_ScenePanelB.m_hTexture + 24) = v19;
  (((SaleUI *)v20))->SaleUI::InitCombatUI((int)this);
  (((PropUI *)*((PropUI **)&this->m_ScenePanelB.m_hTexture + 23)))->PropUI::InitPlayerList((int)this);
  LineupUI_InitListView((int)this);
  (((PAL3 *)this))->PAL3::HandleDeviceReset();
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    v24 = (gbAudioManager *)AudioManager;
    if ( AudioManager )
    {
      (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v24))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v24))->gbAudioManager::StopSoundStream(2);
      v25 = (CScreenMode *)CScreenMode::GetInstance();
      (((SoundMgr *)v25))->SoundMgr::PlayCPKStream(1);
    }
  }
  (((UICursor *)v21))->UICursor::_todo_541CC0();
  LOBYTE(this->m_bCameraInit) = 1;
}

// 0x0047BE20
void CScreenMode::InitEquipScreen()
{
  int m_nProgressPos; // eax
  int v3; // edx
  int v4; // ecx
  UIPushButton *p_m_StaticArray; // edi
  int v6; // ebx
  int v7; // edx
  int v8; // eax
  int m_nLayoutOffX; // edx
  int m_nLayoutOffY; // ecx
  int v11; // edx
  int v12; // eax
  int m_align; // edx
  int v14; // ecx
  int v15; // eax
  MainEquipUI *v16; // eax
  MainEquipUI *v17; // eax
  UICursor *v18; // ecx
  int a2; // [esp+0x74] [ebp-0x2C] BYREF
  int v20; // [esp+0x78] [ebp-0x28]
  int v21; // [esp+0x7C] [ebp-0x24]
  int v22; // [esp+0x80] [ebp-0x20]
  int v23; // [esp+0x84] [ebp-0x1C] BYREF
  int v24; // [esp+0x88] [ebp-0x18]
  int v25; // [esp+0x8C] [ebp-0x14]
  int v26; // [esp+0x90] [ebp-0x10]
  int v27; // [esp+0x9C] [ebp-0x4]

  this->m_nLayoutParam = 0;
  this->m_nPosY = 0;
  this->m_nUIState = 800;
  this->m_nUIMode = 600;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, this->m_nPosY, this->m_nLayoutParam, this->m_nUIState, this->m_nUIMode) /* [ROWTABLE] */;
  m_nProgressPos = this->m_nProgressPos;
  v24 = 136;
  v23 = 360;
  v25 = 428;
  v26 = 168;
  (*(void ( **)(int *, int, int *, CScreenMode *))(m_nProgressPos + 16))(
    &this->m_nProgressPos,
    1025,
    &v23,
    this);
  LOBYTE(v3) = this->m_RoleDialog.m_static.m_id;
  (((UIPushButton *)&this->m_nProgressPos))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagT.tga", v3);
  (*(void ( **)(UIStatic *, int, int *, CScreenMode *))(*(_DWORD *)((UIWnd *)&this->m_FrameB) + 16))(
    &this->m_FrameB,
    1025,
    &v23,
    this);
  LOBYTE(v4) = this->m_RoleDialog.m_static.m_id;
  (((UIPushButton *)&this->m_FrameB))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagB.tga", v4);
  p_m_StaticArray = (UIPushButton *)&this->m_StaticArray;
  v6 = 3;
  do
  {
    (*(void ( **)(UIPushButton *, int, int *, CScreenMode *))(*(_DWORD *)((UIWnd *)p_m_StaticArray) + 16))(
      p_m_StaticArray,
      1025,
      &v23,
      this);
    LOBYTE(v7) = this->m_RoleDialog.m_static.m_id;
    (((UIPushButton *)p_m_StaticArray))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", v7);
    p_m_StaticArray = (UIPushButton *)((char *)p_m_StaticArray + 152);
    --v6;
  }
  while ( v6 );
  v8 = v24 + 32;
  m_nLayoutOffX = this->m_nLayoutOffX;
  a2 = v23 - 10;
  m_nLayoutOffY = this->m_nLayoutOffY;
  v20 = v24 + 32;
  LOBYTE(v8) = this->m_RoleDialog.m_static.m_id;
  v22 = v24 + 32 + m_nLayoutOffY;
  v21 = v23 - 10 + m_nLayoutOffX;
  (*(void ( **)(char *, int, int *, CScreenMode *, char *, _DWORD, int))(*((_DWORD *)&this->m_Static_816 + 104)
                                                                                 + 28))(
    (char *)&this->m_Static_816 + 416,
    1028,
    &a2,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v8);
  AllocObject((char *)&this->m_Static_816 + 416);
  (((CScreenMode *)((char *)&this->m_Static_816 + 416)))->CScreenMode::SetTooltipText((int)dword_DCE83C);
  this->m_nPageCounter.m_pTexture = ((gbTexture *)((gbTexture *)1));
  this->m_nPageCounter.m_nShowState = 1;
  this->m_nPageCounter.m_pChildWnd = ((UIWnd *)((UIWnd *)3));
  (((UIWnd *)&this->m_StaticArray))->UIWnd::sub_445FA0(&a2);
  v11 = this->m_nLayoutOffY;
  v20 = v22;
  v12 = v11 + v22;
  m_align = this->m_Static_816.m_align;
  v22 = v12;
  LOBYTE(v12) = this->m_RoleDialog.m_static.m_id;
  (*(void ( **)(int *, int, int *, CScreenMode *, char *, _DWORD, int))(m_align + 28))(
    &this->m_Static_816.m_align,
    1027,
    &a2,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v12);
  AllocObject(&this->m_Static_816.m_align);
  (((CScreenMode *)&this->m_Static_816.m_align))->CScreenMode::SetTooltipText((int)dword_DCD63C);
  *((_DWORD *)&this->m_Static_816 + 70) = 1;
  *((_DWORD *)&this->m_Static_816 + 44) = 1;
  *((_DWORD *)&this->m_Static_816 + 45) = 3;
  ((UIWnd *)(&this->m_StaticArray + 1))->UIWnd::sub_445FA0(&a2);
  v14 = v22;
  v15 = v22 - 2;
  LOBYTE(v14) = this->m_RoleDialog.m_static.m_id;
  v22 = v22 - 2 + this->m_nLayoutOffY;
  v20 = v15;
  (*(void ( **)(int *, int, int *, CScreenMode *, char *, _DWORD, int))(*(&this->m_nPageCounter.m_hTexture + 31) + 28))(
    &this->m_nPageCounter.m_hTexture + 31,
    1029,
    &a2,
    this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v14);
  AllocObject(&this->m_nPageCounter.m_hTexture + 31);
  (((CScreenMode *)(&this->m_nPageCounter.m_hTexture + 31)))->CScreenMode::SetTooltipText((int)dword_DCD93C);
  *((_DWORD *)&this->m_nPageCounter + 135) = 1;
  *((_DWORD *)&this->m_nPageCounter + 109) = 1;
  *((_DWORD *)&this->m_nPageCounter + 110) = 3;
  (((UIWnd *)&this->_embed_UIFrameWnd_968.m_wndcolor))->UIWnd::sub_445FA0(&a2);
  v24 = v22;
  v23 = 360;
  v25 = 428;
  v26 = v22 + 11;
  (((UIWnd *)&this->m_FrameB))->UIWnd::sub_445FA0(&v23);
  (((UITitle_JDHY *)this))->UITitle_JDHY::HandleDeviceLostA() /* [ROWTABLE] */;
  v16 = (MainEquipUI *)operator new(0x33070u);
  v27 = 0;
  if ( v16 )
    v16->MainEquipUI::MainEquipUI();
  else
    v17 = 0;
  v27 = -1;
  this->m_nProgressValA = (int)v17;
  (((MainEquipUI *)v17))->MainEquipUI::InitMainEquipUI((int)this);
  (((UICursor *)v18))->UICursor::_todo_541CC0();
}

// 0x00483260
StateUI * CScreenMode::_scalar_deleting_destructor_(StateUI *Block, char a2)
{
  (((StateUI *)this))->StateUI::ctor() /* [ROWTABLE] */;
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (StateUI *)this;
}

// 0x004850E0
int CScreenMode::sub_4850E0()
{
  int v2; // edi
  UIStatic *p_m_StaticArray; // ebx
  char *v4; // edi
  int v5; // ebx
  int i; // edi
  gbVec3D v8; // [esp-0x4] [ebp-0x20]
  gbVec3D v9; // [esp-0x4] [ebp-0x20]
  gbMatrixStack *v10; // [esp+0x8] [ebp-0x14]
  gbMatrixStack *v11; // [esp+0x8] [ebp-0x14]
  _BYTE v12[4]; // [esp+0xC] [ebp-0x10] BYREF
  int v13; // [esp+0x18] [ebp-0x4]

  v8.x = 0.0f;
  (((Object3D *)v8))->Object3D::RenderObjectScene(v10);
  v2 = 0;
  p_m_StaticArray = (UIStatic *)&this[29].m_StaticArray;
  do
  {
    if ( *((_BYTE *)&this->m_FrameB.m_ratioh + v2 + 1) )
    {
      v9.x = 0.0f;
      (((Object3D *)v9))->Object3D::RenderObjectScene(v11);
    }
    ++v2;
    ++p_m_StaticArray;
  }
  while ( v2 < 5 );
  v4 = (char *)&this[29].m_Static_816 + 408;
  v5 = 6;
  do
  {
    v9.x = 0.0f;
    (((Object3D *)v9))->Object3D::RenderObjectScene(v11);
    v4 += 152;
    --v5;
  }
  while ( v5 );
  PushMatrixStacks(v12);
  v13 = 0;
  (((CCBControlWindow *)this))->CCBControlWindow::Render((CCBMagicWindow *)LODWORD(v9.y)) /* [ROWTABLE] */;
  if ( *((_BYTE *)&this[28]._embed_UIFrameWnd_968.m_rect.left + this[28]._embed_UIFrameWnd_968.m_rect.right) )
  {
    for ( i = 0; i < 16; ++i )
    {
      if ( IsVisible((RenderTarget *)&this->m_RoleDialog._todo_3d0[9344 * this[28]._embed_UIFrameWnd_968.m_rect.right
                                                                 + 148
                                                                 + 584 * i]) )
        (((UIParticle *)&this->m_RoleDialog._todo_3d0[9344 * this[28]._embed_UIFrameWnd_968.m_rect.right + 148 + 584 * i]))->UIParticle::Apply(11);
      if ( IsVisible((RenderTarget *)(&this[14].m_ScenePanel.m_hFont
                                    + 2336 * this[28]._embed_UIFrameWnd_968.m_rect.right
                                    + 146 * i)) )
        ((UIParticle *)((UIParticle *)&this[14].m_ScenePanel.m_hFont + 16 * this[28]._embed_UIFrameWnd_968.m_rect.right + i))->UIParticle::Apply(10);
    }
  }
  v13 = -1;
  return PopMatrixStacks(v12);
}

// 0x00493290
void CScreenMode::GetPlayerAttByIndex(int nIndex)
{
  char *v2; // ecx
  int v3; // edx
  signed __int16 *v4; // eax
  int v5; // esi

  v2 = (char *)&this[37].m_BtnTooltipC.m_caption[852 * nIndex + 32];
  v3 = 12;
  v4 = (signed __int16 *)(&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 704 * nIndex);
  do
  {
    v5 = *(_DWORD *)v4;
    v4 += 2;
    *(_DWORD *)v2 = v5;
    v2 += 4;
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
      (((UIListBox *)&(&this[28].m_nPageCounter.m_bFieldCC)[2495 * m_nProgressBase]))->UIListBox::GetCurSel();
      (((UIListBox *)&this[28].m_BtnTooltipC.m_caption[9980 * this->m_nProgressBase + 64]))->UIListBox::GetCurSel();
      (((UIListBox *)((char *)&this[28].m_nPageCounter + 9980 * this->m_nProgressBase + 724)))->UIListBox::GetCurSel();
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        "%d/%d",
        (int)*((float *)&this[28].m_nPageCounter.m_hTexture + 2495 * this->m_nProgressBase + 31),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->m_nProgressBase));
      SetEnable((UICaption *)((char *)&this[28].m_nPageCounter + 9980 * this->m_nProgressBase + 420));
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        "%d/%d",
        (int)*((float *)&this[28].m_ScenePanel.m_bcreateok + 2495 * this->m_nProgressBase),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->m_nProgressBase + 1));
      SetEnable((UICaption *)(&this[28].m_ScenePanel.m_nLoadResource + 2495 * this->m_nProgressBase));
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        "%d/%d",
        (int)*((float *)&this[28].m_nPageCounter + 2495 * this->m_nProgressBase + 220),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->m_nProgressBase + 2));
      SetEnable((UICaption *)((char *)&this[28].m_nPageCounter + 9980 * this->m_nProgressBase + 968));
      (((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 162424)))->CScreenMode::SetTooltipText((int)unk_C10D38);
      (((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 162768)))->CScreenMode::SetTooltipText((int)unk_C10D38);
      (((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 163112)))->CScreenMode::SetTooltipText((int)unk_C10D38);
      (((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 163456)))->CScreenMode::SetTooltipText((int)unk_C10D38);
      (((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 163800)))->CScreenMode::SetTooltipText((int)unk_C10D38);
      (((CScreenMode *)((char *)this + 9980 * this->m_nProgressBase + 164144)))->CScreenMode::SetTooltipText((int)unk_C10D38);
      for ( i = 0; i < 1520; i += 152 )
      {
        SetEnable((UICaption *)((char *)&this[28].m_SceneBlock + 9980 * this->m_nProgressBase + i + 136));
        SetEnable((UICaption *)((char *)&this[28].m_RoleDialog + 9980 * this->m_nProgressBase + i + 1468));
      }
    }
    v4 = this->m_nProgressBase + 1;
    this->m_nProgressBase = v4;
  }
  while ( v4 < 5 );
  SetEnable((UICaption *)((char *)&this[37].m_Static_816 + 256));
  SetEnable((UICaption *)&this[37].m_nPageCounter.m_nPosX);
  SetEnable((UICaption *)(&this[37].m_nPageCounter.m_hTexture + 19));
  *((_DWORD *)&this[39].m_RoleDialog + 383) = 0;
  this->m_FrameB.m_texty = ((void *)((void *)-1));
  return (((UIListBox *)&this[39].m_ScenePanelB.m_nClipY))->UIListBox::ClearAll();
}

// 0x004B30C0
char CScreenMode::GetMouseDelta()
{
  unsigned int v1; // eax

  v1 = (unsigned int)((unsigned __int64)(2290649225i64 * *(int *)&g_Input.MouseState[8]) >> 32) >> 31;
  if ( *(_DWORD *)&g_Input.MouseState[8] / 120 <= 0 )
  {
    if ( *(_DWORD *)&g_Input.MouseState[8] / 120 < 0 )
      LOBYTE(v1) = UITitle_JDHY_ScrollDown(1);
  }
  else
  {
    LOBYTE(v1) = UITitle_JDHY_ScrollUp(1);
  }
  return v1;
}

// 0x00523F30
CScreenMode::CScreenMode()
{
  _DWORD *v2; // ecx
  char *v3; // eax
  int v4; // edx
  char *v5; // ebp
  char *v6; // ebp
  _DWORD *v7; // ebp

  ((UIListBox *)this)->UIListBox::UIListBox();
  this->m_nScreenWidth = 800;
  this->m_nScreenHeight = 600;
  this->m_nProgressBase = 0;
  this->m_nLayoutState = 0;
  (((UIFrameContainer *)&this->m_FrameB.m_ratioh))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_StaticArray.m_ratioh))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->_embed_UIFrameWnd_816.m_rect.bottom))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_816))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->m_Static_816 + 1)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->m_Static_816 + 2)))->UIFrameContainer::ResetContainerState();
  (((UIScene *)&this->m_nPageCounter.m_rect.bottom))->UIScene::ctor();
  NameSys::GetSys();
  NameSys::GetSys();
  *((_DWORD *)&this->m_nPageCounter + 247) = 0;
  ((CCBStageRole *)((char *)&this->m_nPageCounter + 992))->CCBStageRole::CCBStageRole();
  this->m_bActive = 0;
  this->m_nScreenActive = 0;
  v2 = (_DWORD *)((char *)&this->m_RoleDialog + 1420);
  *((_DWORD *)&this->m_RoleDialog + 342) = 0;
  *((_DWORD *)&this->m_RoleDialog + 343) = 0;
  *((_DWORD *)&this->m_RoleDialog + 344) = 0;
  *((_DWORD *)&this->m_RoleDialog + 345) = 0;
  *((_DWORD *)&this->m_RoleDialog + 347) = 0;
  *((_DWORD *)&this->m_RoleDialog + 348) = 0;
  v3 = (char *)&this->m_RoleDialog + 1456;
  v4 = 4;
  do
  {
    v5 = (char *)(v3 - 24);
    *v2 = 0;
    *((_DWORD *)v3 - 8) = 0;
    *((_DWORD *)v3 - 7) = 0;
    *(_DWORD *)v5 = 0;
    v2 += 12;
    *((_DWORD *)v5 + 1) = 0;
    *((_DWORD *)v5 + 2) = 0;
    v6 = (char *)(v3 - 12);
    *((_DWORD *)v3 - 3) = 0;
    *((_DWORD *)v6 + 1) = 0;
    *((_DWORD *)v6 + 2) = 0;
    v7 = (_DWORD *)v3;
    v3 += 48;
    --v4;
    *v7 = 0;
    v7[1] = 0;
    v7[2] = 0;
  }
  while ( v4 );
  *((_BYTE *)&this->m_RoleDialog + 1396) = 0;
  *((_BYTE *)&this->m_RoleDialog + 1397) = 0;
  *((_BYTE *)&this->m_RoleDialog + 1398) = 0;
  *((_BYTE *)&this->m_RoleDialog + 1399) = 0;
  *((_BYTE *)&this->m_RoleDialog + 1400) = 0;
  *((_BYTE *)&this->m_RoleDialog + 1401) = 0;
  *((_BYTE *)&this->m_RoleDialog + 1402) = 0;
  *((_DWORD *)&this->m_RoleDialog + 351) = 1065353216;
  *((_DWORD *)&this->m_RoleDialog + 352) = 0;
  *((_DWORD *)&this->m_RoleDialog + 353) = 0;
  *((_DWORD *)&this->m_RoleDialog + 354) = 0;
  *((_DWORD *)&this->m_RoleDialog + 403) = 0;
  memset((char *)&this->m_RoleDialog + 1420, 0, 0xC0u);
}

// 0x00524130
CScreenMode::~CScreenMode()
{
  (((UIRoleDialog *)&this->m_RoleDialog))->UIRoleDialog::~UIRoleDialog();
  (((CCBStage *)((char *)&this->m_nPageCounter + 992)))->CCBStage::CleanupScript();
  (((UICaption *)((char *)&this->m_nPageCounter + 644)))->UICaption::Destroy2();
  (((UICaption *)(&this->m_nPageCounter.m_hTexture + 23)))->UICaption::Destroy2();
  (((CCBResultWindow *)&this->m_nPageCounter.m_rect.bottom))->CCBResultWindow::~CCBResultWindow();
  (((UIFrameContainer *)(&this->m_Static_816 + 2)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(&this->m_Static_816 + 1)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Static_816))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->_embed_UIFrameWnd_816.m_rect.bottom))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_StaticArray.m_ratioh))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_FrameB.m_ratioh))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x00524980
int CScreenMode::ForwardMessage(int nVal, int nVal2)
{
  (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return 1;
}

// 0x005249A0
int CScreenMode::OnRenderAlt(int nVal1)
{
  int v4; // eax
  CScreenMode *v5; // eax
  CScreenMode *Instance; // eax
  int v7; // eax
  int v8; // ecx
  double v9; // st7
  int v10; // eax
  double v11; // st7
  unsigned __int8 v13; // c0
  unsigned __int8 v14; // c3
  int v15; // ecx
  DWORD Time; // eax
  CScreenMode *v17; // eax
  int v18; // eax
  double v19; // st7
  const void *v20; // [esp-0x4] [ebp-0x10]
  const char *v21; // [esp-0x4] [ebp-0x10]
  const char *v22; // [esp-0x4] [ebp-0x10]
  float fVal; // [esp+0x0] [ebp-0xC]
  int *nMsg; // [esp+0x14] [ebp+0x8]
  int nMsga; // [esp+0x14] [ebp+0x8]
  int wParam; // [esp+0x18] [ebp+0xC]

  if ( nVal1 == 1000 )
  {
    if ( nMsg )
    {
      v18 = *((_DWORD *)&this->m_RoleDialog + 345);
      if ( v18 + *(&g_RoleSlotBuf.dword_17AA450 + 147) <= 500000 )
        v19 = (double)*(&g_RoleSlotBuf.dword_17AA450 + 147);
      else
        v19 = (double)(500000 - v18);
      fVal = v19;
      (((UIScene *)&this->m_nPageCounter.m_rect.bottom))->UIScene::UpdateLayout(fVal);
      *((_DWORD *)&this->m_RoleDialog + 346) = 0;
      sub_445E50((int)(&this->m_nPageCounter.m_hTexture + 23));
      (((UIScene *)&this->m_nPageCounter.m_rect.bottom))->UIScene::RefreshLayout();
      sprintf(
        (char *const)&this->m_nLayoutOffX,
        (const char *)&dir[20],
        *(&g_RoleSlotBuf.dword_17AA450 + 147) - *((_DWORD *)&this->m_RoleDialog + 346));
      SetEnable((UICaption *)&this->m_StaticArray.m_ratioh);
      sprintf((char *const)&this->m_nLayoutOffX, (const char *)&dir[20], *((_DWORD *)&this->m_RoleDialog + 346));
      SetEnable((UICaption *)&this->_embed_UIFrameWnd_816.m_rect.bottom);
      sprintf((char *const)&this->m_nLayoutOffX, (const char *)&dir[20], 500000);
      SetEnable((UICaption *)&this->m_Static_816);
      sprintf((char *const)&this->m_nLayoutOffX, (const char *)&dir[20], *((_DWORD *)&this->m_RoleDialog + 345));
      SetEnable((UICaption *)(&this->m_Static_816 + 1));
      switch ( *((_DWORD *)&this->m_RoleDialog + 347) )
      {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
          break;
        default:
          sprintf((char *const)&this->m_nLayoutOffX, "%s", &dword_DCA33C);
          break;
      }
      SetEnable((UICaption *)(&this->m_Static_816 + 2));
      *((_DWORD *)&this->m_RoleDialog + 348) = *((_DWORD *)&this->m_RoleDialog + 347);
    }
    return 1;
  }
  if ( nVal1 == 1001 )
  {
    if ( nMsg != &byte_A00B07 )
    {
      if ( (char *)nMsg - (char *)&byte_A00B07 == 1 )
      {
        (((RoleShadow *)this))->RoleShadow::UpdateShadow();
        v21 = (const char *)off_5E524C;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v21, 1);
        return 1;
      }
      return 1;
    }
    v7 = *((_DWORD *)&this->m_RoleDialog + 346);
    v8 = v7 + *((_DWORD *)&this->m_RoleDialog + 345);
    *((_DWORD *)&this->m_RoleDialog + 345) = v8;
    if ( v8 <= 0 )
    {
LABEL_36:
      v22 = (const char *)off_5E524C;
      v17 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v17))->CScreenMode::AudioSetPosition(v22, 1);
      return 1;
    }
    *(&g_RoleSlotBuf.dword_17AA450 + 147) -= v7;
    v9 = (double)*((int *)&this->m_RoleDialog + 345);
    *(float *)&nMsga = v9;
    if ( v9 > 500000.0 )
    {
      v10 = 4;
LABEL_32:
      v15 = *((_DWORD *)&this->m_RoleDialog + 348);
      *((_DWORD *)&this->m_RoleDialog + 347) = v10;
      if ( v10 <= v15 )
      {
        this->m_bActive = 0;
      }
      else
      {
        this->m_bActive = 1;
        *((_DWORD *)&this->m_RoleDialog + 348) = v10;
        Time = timeGetTime();
        CRT_set_new_handler(Time);
      }
      CUtil_Update(2);
      goto LABEL_36;
    }
    if ( *(float *)&nMsga <= 0.0f )
    {
      v10 = 6;
      goto LABEL_32;
    }
    v11 = 100.0 / (500000.0 / *(float *)&nMsga) * 0.01;
    *((float *)&this->m_nPageCounter + 247) = v11;
    if ( v13 | v14 )
    {
      if ( v11 < 0.25 )
      {
        if ( v11 < 0.5 )
          goto LABEL_26;
        goto LABEL_24;
      }
    }
    else if ( v11 < 0.25 )
    {
LABEL_19:
      v10 = 0;
      goto LABEL_32;
    }
    if ( v11 < 0.5 )
    {
      v10 = 1;
      goto LABEL_32;
    }
LABEL_24:
    if ( v11 < 0.75 )
    {
      v10 = 2;
      goto LABEL_32;
    }
LABEL_26:
    if ( v11 < 0.75 )
    {
      if ( v11 < 1.0 )
        goto LABEL_19;
    }
    else if ( v11 < 1.0 )
    {
      v10 = 3;
      goto LABEL_32;
    }
    v10 = 4;
    goto LABEL_32;
  }
  if ( nVal1 != 1019 )
    return (((UIWnd *)this))->UIWnd::OnMessage(nVal1, (int)nMsg, wParam) /* [ROWTABLE] */;
  if ( nMsg != &byte_A00B01 || wParam == *((_DWORD *)&this->m_RoleDialog + 346) )
    return 1;
  v4 = *((_DWORD *)&this->m_RoleDialog + 345);
  *((_DWORD *)&this->m_RoleDialog + 346) = wParam;
  if ( v4 + wParam >= 500000 )
    *((_DWORD *)&this->m_RoleDialog + 346) = 500000 - v4;
  sprintf(
    (char *const)&this->m_nLayoutOffX,
    (const char *)&dir[20],
    *(&g_RoleSlotBuf.dword_17AA450 + 147) - *((_DWORD *)&this->m_RoleDialog + 346));
  SetEnable((UICaption *)&this->m_StaticArray.m_ratioh);
  sprintf((char *const)&this->m_nLayoutOffX, (const char *)&dir[20], *((_DWORD *)&this->m_RoleDialog + 346));
  SetEnable((UICaption *)&this->_embed_UIFrameWnd_816.m_rect.bottom);
  sprintf(
    (char *const)&this->m_nLayoutOffX,
    (const char *)&dir[20],
    *((_DWORD *)&this->m_RoleDialog + 345) + *((_DWORD *)&this->m_RoleDialog + 346));
  SetEnable((UICaption *)(&this->m_Static_816 + 1));
  sub_445E50((int)(&this->m_nPageCounter.m_hTexture + 23));
  v20 = (const void *)off_5E525C;
  v5 = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)v5))->CScreenMode::AudioSetPosition(v20, 1);
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
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
        v9 = (gbAudioManager *)AudioManager;
        if ( AudioManager )
        {
          (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(0);
          (((gbAudioManager *)v9))->gbAudioManager::StopSoundStream(2);
          v10 = (CScreenMode *)CScreenMode::GetInstance();
          (((SoundMgr *)v10))->SoundMgr::PlayCPKStream(1);
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
          v18 = (CScreenMode *)CScreenMode::GetInstance();
          v19 = (gbAudioManager *)(((CScreenMode *)v18))->CScreenMode::GetAudioManager();
          v20 = (gbAudioManager *)v19;
          if ( v19 )
          {
            (((gbAudioManager *)v19))->gbAudioManager::DetachAll3D();
            (((gbAudioManager *)v20))->gbAudioManager::StopSoundStream(0);
            (((gbAudioManager *)v20))->gbAudioManager::StopSoundStream(2);
            (((gbAudioManager *)v20))->gbAudioManager::StopSoundStream(1);
          }
        }
      }
      else
      {
        (((SceneObj *)this))->SceneObj::GetCommonData() /* [ROWTABLE] */;
        sub_528190(szSubKey, (DWORD)"S_GAME_B", 1);
        if ( (g_dwGameFlags & 4) != 0 )
        {
          v13 = (CScreenMode *)CScreenMode::GetInstance();
          v14 = (gbAudioManager *)(((CScreenMode *)v13))->CScreenMode::GetAudioManager();
          v15 = (gbAudioManager *)v14;
          if ( v14 )
          {
            (((gbAudioManager *)v14))->gbAudioManager::StopSoundStream(1);
            (((gbAudioManager *)v15))->gbAudioManager::StopSoundStream(2);
          }
          if ( CScreenMode::GetInstance()->m_bRenderAlt )
          {
            v16 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v16))->CScreenMode::AudioFadeOut();
          }
          else
          {
            v17 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v17))->CScreenMode::AudioStopAll();
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
  float v5; // st7
  __int64 v6; // rax
  CScreenMode *v7; // eax
  unsigned int *v8; // edi
  unsigned int *v9; // eax
  int v10; // ebp
  int v11; // edx
  CScreenMode *v12; // eax
  float v13; // st7
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
  if ( (((UIRoleSelectDialog *)this))->UIRoleSelectDialog::IsRoleSelectable(0) /* [ROWTABLE] */ )
  {
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] = *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame;
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[3] = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 1);
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[4] = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 2);
    sprintf((char *const)&this->m_nProgressBase, "\\n          %s%s", g_szRoleNameTable, (const char *)&dword_DCCD3C);
    v2 = 1;
    v21 = (const void *)off_5EFF98;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v21, 1);
  }
  if ( (((UIRoleSelectDialog *)this))->UIRoleSelectDialog::IsRoleSelectable(4) /* [ROWTABLE] */ )
  {
    *(&g_RoleSlotBuf.dword_17AA450 + 25) = *(&g_RoleSlotBuf.dword_17AA450 + 13);
    *(&g_RoleSlotBuf.dword_17AA450 + 26) = *(&g_RoleSlotBuf.dword_17AA450 + 14);
    *(&g_RoleSlotBuf.dword_17AA450 + 27) = *(&g_RoleSlotBuf.dword_17AA450 + 15);
    sprintf((char *const)&this->m_nProgressBase, "\\n          %s%s", byte_DC773C, (const char *)&dword_DCCD3C);
    v2 = 1;
    v22 = (const void *)off_5EFF98;
    v4 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v4))->CScreenMode::AudioSetPosition(v22, 1);
  }
  if ( (((UIRoleSelectDialog *)this))->UIRoleSelectDialog::IsRoleSelectable(1) /* [ROWTABLE] */ )
  {
    v5 = *(float *)&this[1].m_RoleDialog._todo_278[180]
       * 0.0099999998
       * (double)(&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0]
       + (double)(&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0];
    g_nRoleInitLevel[1] += 10;
    (&g_RoleSlotBuf.m_teamSlotOverlay.m_teamSlots)[0] = (__int64)v5;
    sprintf(
      (char *const)&this->m_nProgressBase,
      "\\n            %s%s+10",
      (const char *)&dword_DC743C,
      (const char *)&dword_DCCE3C);
    v2 = 1;
    v23 = (const void *)off_5EFF48;
LABEL_11:
    v7 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v7))->CScreenMode::AudioSetPosition(v23, 1);
    goto LABEL_12;
  }
  if ( (((UIRoleSelectDialog *)this))->UIRoleSelectDialog::IsRoleSelectable(2) /* [ROWTABLE] */ )
  {
    *(_DWORD *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 110) = (__int64)(*(float *)&this[1].m_RoleDialog._todo_278[180]
                                                                                     * 0.0099999998
                                                                                     * (double)*(int *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 62)
                                                                                     + (double)*(int *)(&g_RoleSlotBuf.m_teamSlotsB.combat.m_bCommandEdited + 110));
    g_nRoleInitLevel[2] += 10;
    sprintf(
      (char *const)&this->m_nProgressBase,
      "\\n            %s%s+10",
      (const char *)&dword_DC753C,
      (const char *)&dword_DCCE3C);
    v2 = 1;
    v23 = (const void *)off_5EFF48;
    goto LABEL_11;
  }
  if ( (((UIRoleSelectDialog *)this))->UIRoleSelectDialog::IsRoleSelectable(3) /* [ROWTABLE] */ )
  {
    v6 = (__int64)(*(float *)&this[1].m_RoleDialog._todo_278[180] * 0.0099999998 * (double)g_RoleSlotBuf.m_teamData3[99]
                 + (double)g_RoleSlotBuf.m_teamData3[111]);
    g_nRoleInitLevel[3] += 10;
    g_RoleSlotBuf.m_teamData3[111] = v6;
    sprintf(
      (char *const)&this->m_nProgressBase,
      "\\n            %s%s+10",
      (const char *)&dword_DC763C,
      (const char *)&dword_DCCE3C);
    v2 = 1;
    v23 = (const void *)off_5EFF48;
    goto LABEL_11;
  }
LABEL_12:
  v25 = 0;
  v8 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
  do
  {
    if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v25) )
    {
      *v8 = (__int64)(*(float *)&this[1].m_RoleDialog._todo_278[180] * 0.0099999998 * (double)(int)*(v8 - 12)
                    + (double)(int)*v8);
      v9 = (unsigned int *)v8;
      v10 = 12;
      do
      {
        v11 = *(v9 - 12);
        if ( (int)*v9 < v11 )
        {
          if ( (int)*v9 <= 0 )
            *v9 = 0;
        }
        else
        {
          *v9 = v11;
        }
        ++v9;
        --v10;
      }
      while ( v10 );
    }
    v20 = (const void *)off_5EFF90;
    v12 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(v20, 1);
    v8 += 352;
    ++v25;
  }
  while ( (int)v8 < (int)dword_C062EC );
  memset(String2, 0, sizeof(String2));
  v13 = *(float *)&this[1].m_RoleDialog._todo_278[180];
  v27 = 0;
  v28 = 0;
  sprintf(
    String2,
    "          %s%s%s%d%%",
    (const char *)&dword_DCEC3C,
    (const char *)&dword_DCCF3C,
    (const char *)&dword_DC413C,
    (unsigned int)(__int64)v13);
  p_m_nProgressBase = (int *)&this->m_nProgressBase;
  if ( v2 )
    lstrcatA((LPSTR)p_m_nProgressBase, aN);
  else
    lstrcpyA((LPSTR)p_m_nProgressBase, aN);
  lstrcatA((char *)(LPSTR)&this->m_nProgressBase, String2);
  SetEnable((UICaption *)&this[1].m_RoleDialog._todo_3d0[316]);
  (((UIRoleSelect *)&this[1].m_RoleDialog._todo_278[204]))->UIRoleSelect::SetByte(1);
  v14 = 0;
  v15 = (RoleSystem *)&g_RoleSlotBuf;
  do
  {
    LOBYTE(v16) = *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v14);
    if ( (_BYTE)v16 )
    {
      (((RoleSystem *)v15))->RoleSystem::RecalcAggregatedStats(0);
      v16 = (int *)&v15->m_partyActor.m_dwMatMsg[2];
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
  while ( (int)v15 < (int)(&g_RoleSlotBuf.dword_17AA450 + 134) );
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
    v3->gbCamera::gbCamera(pGfx);
  else
    v4 = 0;
  this->m_pEnumeration = ((char *)(v4));
  (((gbCamera *)v4))->gbCamera::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  m_pEnumeration = (char *)this->m_pEnumeration;
  *((_DWORD *)m_pEnumeration + 1) = 0;
  *(_DWORD *)m_pEnumeration = 1112014848;
  (((gbCamera *)this->m_pEnumeration))->gbCamera::SetLookAt((gbVec3D *)&this->m_bRenderAlt, (gbVec3D *)&this->m_fFadeStart, (gbVec3D *)&this->m_fFadeAlpha);
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
  void *inited; // eax
  gbOBBox *v9; // eax
  OBBox *BBox; // eax
  CScreenMode *v11; // ecx
  int v12; // edi
  int v13; // ecx
  int v14; // ebx
  int v15; // edx
  float *v16; // eax
  float v17; // st7
  float v18; // ebp
  float m_fFadeStart; // eax
  float *v20; // ebp
  int v21; // ebx
  int v22; // ebp
  int v23; // edi
  int TableEntry; // eax
  int v25; // ebx
  int v26; // edx
  float *v27; // edx
  float v28; // st7
  float v29; // eax
  gbLightObj *v30; // eax
  gbLightObj *v31; // edi
  char *m_pArrayData; // eax
  char *v33; // edi
  unsigned int v34; // edx
  ScreenEffectMgr *v35; // ecx
  ScreenEffect *Instance; // eax
  CScreenMode *v37; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v39; // esi
  CScreenMode *v40; // eax
  OBBox *v41; // [esp+0x0] [ebp-0x44]
  float *p_m_fFadeAlpha; // [esp+0x10] [ebp-0x34]
  int v43; // [esp+0x10] [ebp-0x34]
  int v44; // [esp+0x14] [ebp-0x30]
  int v45; // [esp+0x18] [ebp-0x2C]
  float v46; // [esp+0x20] [ebp-0x24]
  float v47; // [esp+0x24] [ebp-0x20]
  float v48; // [esp+0x2C] [ebp-0x18]
  float v49; // [esp+0x30] [ebp-0x14]

  v2 = (CScreenMode *)operator new(0x338u);
  if ( v2 )
    VolModNode = (char *)(((CScreenMode *)v2))->CScreenMode::CreateVolModNode();
  else
    VolModNode = 0;
  this->m_pEnumeration = ((char *)(VolModNode));
  v4 = (UILoadingFrm *)operator new(0x138u);
  if ( v4 )
    v5 = (((UILoadingFrm *)v4))->UILoadingFrm::ResetState();
  else
    v5 = 0;
  *(_DWORD *)&this->m_bRenderAlt = v5;
  v6 = (RoleSystem *)operator new(0x1DB0u);
  if ( v6 )
    (((RoleSystem *)v6))->RoleSystem::_todo_531D20();
  else
    v7 = 0;
  this->m_nScreenFlags = v7;
  if ( operator new(8u) )
    inited = ZeroInitPair();
  else
    inited = 0;
  this->m_nTodo_0C = (int)inited;
  v9 = (gbOBBox *)operator new(0xEB8u);
  if ( v9 )
    BBox = (((gbOBBox *)v9))->gbOBBox::GetBBox(v41);
  else
    BBox = 0;
  v11 = (CScreenMode *)(*(CScreenMode **)&this->m_bRenderAlt);
  LODWORD(this->m_fFadeStart) = (unsigned long)BBox;
  (((CScreenMode *)v11))->CScreenMode::InitCamera(gfxMgr);
  (((RoleAtt *)this->m_pEnumeration))->RoleAtt::LoadModelAndInit();
  (((RoleAtt *)this->m_pEnumeration))->RoleAtt::SetSAIDAndImage(*(int **)&this->m_bRenderAlt);
  this->m_pEnumeration[772] = this->m_FrameB.m_rect.top != 4;
  RoleSystem_InitAllSystems((int)v41);
  RoleAtt_SetPageParam((int)this->m_pEnumeration);
  RoleAtt_SetPageParam2((int)this);
  (((SceneObj *)this->m_nTodo_0C))->SceneObj::LoadDefaultModel();
  (((SceneObj *)this->m_nTodo_0C))->SceneObj::SetScriptDel(*(_DWORD *)&this->m_bRenderAlt);
  (((SceneObj *)LODWORD(this->m_fFadeStart)))->SceneObj::LoadObstruction();
  (((UISceneMap *)LODWORD(this->m_fFadeStart)))->UISceneMap::SetCurrentMapID(*(_DWORD *)&this->m_bRenderAlt);
  memset(&this->m_fFadeAlpha, 0, 0x18u);
  v12 = 0;
  p_m_fFadeAlpha = (float *)&this->m_fFadeAlpha;
  v13 = 0;
  v45 = (*((_DWORD *)this->m_pEnumeration + 141) - 1560) / 6;
  v14 = v45 + 300;
  v15 = 32 * (v45 + 300);
  do
  {
    v13 += 12;
    *(_DWORD *)p_m_fFadeAlpha = v14;
    v16 = (float *)(v15 + *((_DWORD *)this->m_pEnumeration + 142));
    v17 = *v16;
    v18 = v16[1];
    v47 = v16[2];
    m_fFadeStart = this->m_fFadeStart;
    v46 = v18;
    *(float *)(v13 + LODWORD(m_fFadeStart) + 1668) = v17;
    v20 = (float *)(v12 + LODWORD(m_fFadeStart) + 1808);
    v12 += 76;
    *(float *)(v13 + LODWORD(m_fFadeStart) + 1672) = v46;
    *(float *)(v13 + LODWORD(m_fFadeStart) + 1676) = v47;
    *(float *)(v12 + LODWORD(m_fFadeStart) + 1724) = *(float *)(v13 + LODWORD(m_fFadeStart) + 1668)
                                                   + *(float *)(v12 + LODWORD(m_fFadeStart) + 1724);
    *(float *)(v12 + LODWORD(m_fFadeStart) + 1728) = *(float *)(v13 + LODWORD(m_fFadeStart) + 1672)
                                                   + *(float *)(v12 + LODWORD(m_fFadeStart) + 1728);
    v14 += v45;
    *v20 = *(float *)(v13 + LODWORD(m_fFadeStart) + 1676) + *v20;
    v15 += 32 * v45;
    ++p_m_fFadeAlpha;
  }
  while ( v13 < 72 );
  v21 = 0;
  v22 = 0;
  v44 = 0;
  v23 = 0;
  do
  {
    if ( this->m_FrameB.m_rect.top == 4 )
    {
      *(_BYTE *)(v21 + LODWORD(this->m_fFadeStart) + 3328) = 0;
    }
    else
    {
      TableEntry = GetTableEntry(v21);
      *(_BYTE *)(v21 + LODWORD(this->m_fFadeStart) + 3328) = !(((PAL_GDB *)this))->PAL_GDB::SetupSkillData(TableEntry);
      v25 = *((_DWORD *)this->m_pEnumeration + 141);
      v43 = (__int64)*((float *)this->m_pEnumeration + 121);
      v26 = rand() % v25;
      v21 = v44;
      v27 = (float *)(*((_DWORD *)this->m_pEnumeration + 142) + 32 * (v26 + 100));
      v28 = *v27;
      v29 = this->m_fFadeStart;
      v48 = (float)(v43 / 3) + (float)v43 + v27[1];
      v49 = v27[2];
      *(float *)(LODWORD(v29) + v23 + 3068) = v48;
      *(float *)(LODWORD(v29) + v23 + 3064) = v28;
      *(float *)(LODWORD(v29) + v23 + 3072) = v49;
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
    v44 = v21;
  }
  while ( v23 < 36 );
  UIAnimateCtrlEX_SetTextBottom(LODWORD(this->m_fFadeStart));
  (((RenderTarget *)this->m_pEnumeration))->RenderTarget::SetState(this->m_nScreenFlags);
  v30 = (gbLightObj *)operator new(0xD8u);
  if ( v30 )
  {
    v31 = (gbLightObj *)v30;
    *((_DWORD *)((gbVolumeModifier *)v30) + 1) = 1;
    v30->m_BoundSphere.center.x = 0.0f;
    v30->m_BoundSphere.center.y = 0.0f;
    v30->m_BoundSphere.center.z = 0.0f;
    v30->m_SysLight.position.x = 0.0f;
    v30->m_SysLight.position.y = 0.0f;
    v30->m_SysLight.position.z = 0.0f;
    v30->m_SysLight.direction.x = 0.0f;
    v30->m_SysLight.direction.y = 0.0f;
    v30->m_SysLight.direction.z = 0.0f;
  }
  else
  {
    v31 = 0;
  }
  (((gbLightObj *)v31))->gbLightObj::Init(LIGHT_SPOT);
  v31->m_Ambient.Red = 0.10000000149011612f;
  v31->m_Ambient.Green = 0.10000000149011612f;
  v31->m_Ambient.Blue = 0.10000000149011612f;
  v31->m_Ambient.Alpha = 1.0f;
  v31->m_UseSpecular = 1;
  v31->m_UseDiffuse = 1;
  v31->m_Color.Red = 0.2800000011920929f;
  v31->m_Color.Green = 0.2800000011920929f;
  v31->m_Color.Blue = 0.2800000011920929f;
  v31->m_FarEnd = 10.0f;
  v31->m_FarStart = 10.0f;
  v31->m_Color.Alpha = 1.0f;
  (((gbVolModNode *)&this->m_VolMod))->gbVolModNode::SetVolModObj(v31);
  (((gbRefObject *)v31))->gbRefObject::Release();
  m_pArrayData = (char *)this->m_pArrayData;
  this->m_nArrayCapacity = 62;
  if ( m_pArrayData )
  {
    operator delete(m_pArrayData);
    this->m_pArrayData = ((char *)0);
  }
  v33 = (char *)operator new(4 * this->m_nArrayCapacity);
  v34 = 4 * this->m_nArrayCapacity;
  this->m_pArrayData = ((char *)(v33));
  memset(v33, 0, v34);
  this->m_FrameB.m_fontcolor.Color = 0;
  LOBYTE(this->m_FrameB.m_id) = 1;
  BYTE1(this->m_FrameB.m_id) = 0;
  BYTE2(this->m_FrameB.m_id) = 0;
  LOBYTE(this->m_FrameB.m_rect.left) = 0;
  (((UICursor *)0))->UICursor::_todo_541CC0();
  BYTE2(g_dwUISettings) = 1;
  LOBYTE(this->m_nFadeState) = 0;
  this->m_fFadeTarget = 0.0f;
  Instance = (((ScreenEffectMgr *)v35))->ScreenEffectMgr::GetInstance();
  (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(2);
  if ( (g_dwGameFlags & 4) != 0 )
  {
    v37 = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)v37))->CScreenMode::GetAudioManager();
    v39 = (gbAudioManager *)AudioManager;
    if ( AudioManager )
    {
      (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v39))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v39))->gbAudioManager::StopSoundStream(2);
      v40 = (CScreenMode *)CScreenMode::GetInstance();
      (((SoundMgr *)v40))->SoundMgr::PlayCPKStream(1);
    }
  }
}

// 0x00530440
int CScreenMode::CreateVolModNode()
{
  int v3; // [esp+0x0] [ebp-0x18]
  int v4; // [esp+0x0] [ebp-0x18]

  ((gbMatrix4 *)&this->m_StaticArray.m_bvisible)->gbMatrix4::gbMatrix4();
  MiniGame2_ClearState();
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
  *(_DWORD *)((UIWnd *)&this->_embed_UIFrameWnd_816) = 0;
  this->_embed_UIFrameWnd_816.m_fontcolor.Color = 0;
  this->_embed_UIFrameWnd_816.m_wndcolor.Color = 0;
  this->_embed_UIFrameWnd_816.m_id = 0;
  this->_embed_UIFrameWnd_816.m_rect.left = 0;
  LOBYTE(this->_embed_UIFrameWnd_816.m_bfocus) = 0;
  this->_embed_UIFrameWnd_816.m_benable = 0;
  this->_embed_UIFrameWnd_816.m_bvisible = 0;
  LOBYTE(this->_embed_UIFrameWnd_968.m_wndcolor.Color) = 0;
  this->_embed_UIFrameWnd_968.m_fontcolor.Color = 0;
  *(_DWORD *)((UIWnd *)&this->_embed_UIFrameWnd_968) = 0;
  LOBYTE(this->_embed_UIFrameWnd_968.m_rect.right) = 0;
  this->_embed_UIFrameWnd_968.m_rect.top = 0;
  this->_embed_UIFrameWnd_968.m_rect.left = 0;
  LOBYTE(this->_embed_UIFrameWnd_968.m_childs.m_pData) = 0;
  this->_embed_UIFrameWnd_968.m_pfather = ((UIWnd *)0);
  this->_embed_UIFrameWnd_968.m_rect.bottom = 0;
  UIGameOver_ClearState(v3);
  UIGameOver_ResetState(v4);
  LOBYTE(this->_embed_UIFrameWnd_816.m_pbktex) = 0;
  return (int)this;
}

// 0x00530660
void CScreenMode::FreeNPCBuffer()
{
  char *m_pEnumeration; // edi
  void ( ***v3)(_DWORD, int); // ecx

  m_pEnumeration = (char *)this->m_pEnumeration;
  if ( this->m_pEnumeration )
  {
    (((NPC *)this->m_pEnumeration))->NPC::FreeBuffer();
    operator delete(m_pEnumeration);
    this->m_pEnumeration = ((char *)0);
  }
  v3 = *(void ( ****)(_DWORD, int))&this->m_bRenderAlt;
  if ( v3 )
  {
    (**v3)((_DWORD)((_DWORD)(v3)), (int)(1));
    *(_DWORD *)&this->m_bRenderAlt = 0;
  }
}

// 0x00533250
double CScreenMode::LoadScreenScene(double result, float result_4)
{
  float v3; // st7
  int m_nBarWidth; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  void ( **v9)(int, bool); // edx
  float v11; // st7
  float *p_m_fFadeSpeed; // edi
  unsigned __int8 v13; // c0
  unsigned __int8 v14; // c3
  float v15; // st7
  float v16; // st6
  float v17; // st7
  float v18; // st7
  float v19; // st7
  float v20; // st7
  float v21; // st7
  float v22; // st7
  float v23; // st7
  float v24; // st7
  long double v25; // st7
  long double v26; // st7
  RoleSystem *v27; // edx
  float *p_m_fRotAxisX; // eax
  int v29; // edi
  int v30; // eax
  int v31; // eax
  void ( **v32)(int, bool); // edx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v35; // esi
  CScreenMode *v36; // eax
  CScreenMode *v37; // eax
  float v38; // st7
  float fValue; // [esp+0x0] [ebp-0x38]
  float fValuea; // [esp+0x0] [ebp-0x38]
  float fValueb; // [esp+0x0] [ebp-0x38]
  float fValuec; // [esp+0x0] [ebp-0x38]
  int v43; // [esp+0x4] [ebp-0x34]
  float v44; // [esp+0x14] [ebp-0x24]
  float v45; // [esp+0x18] [ebp-0x20]
  float v46; // [esp+0x1C] [ebp-0x1C]
  float v47; // [esp+0x1C] [ebp-0x1C]
  int m_nTodo_0C; // [esp+0x20] [ebp-0x18]
  float m_fFadeStart; // [esp+0x24] [ebp-0x14]
  float v50; // [esp+0x34] [ebp-0x4]
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
    v3 = this->m_fCountdown - 0.5f;
    this->m_fCountdown = v3;
    if ( v3 <= *(float *)&this->m_nLayoutOffY )
      LODWORD(this->m_fCountdown) = this->m_nLayoutOffY;
    (((UIAnimateCtrlEX *)this->m_pEnumeration))->UIAnimateCtrlEX::NormalizeVector(LODWORD(this->m_fFadeSpeed), LODWORD(this->m_fCountdown), LODWORD(this->m_fFadeParam), this->m_nUIMode);
    v6 = *((_DWORD *)this->m_pEnumeration + 56);
    if ( *(_BYTE *)(v6 + 356) )
    {
      v7 = *(_DWORD *)(v6 + 352);
      resultb = v7;
      if ( v7 >= 1000 )
        v7 = 1000;
      *(_DWORD *)(v6 + 348) = v7;
      fValue = (float)resultb;
      (((UIScrollBar *)(v6 + 3096)))->UIScrollBar::SetRange(fValue);
      v3 = (float)*(int *)(v6 + 348);
      fValuea = v3;
      (((UIProgressBar *)(v6 + 3096)))->UIProgressBar::FindChildByName(fValuea);
      v8 = *(_DWORD *)(v6 + 348);
      v9 = *(void ( ***)(int, bool))(v6 + 3096);
      *(_BYTE *)(v6 + 356) = v8 <= 0;
      (*v9)(v6 + 3096, v8 > 0);
      (**(void ( ***)(int, bool))(v6 + 3340))((int)(v6 + 3340), (bool)(*(_DWORD *)(v6 + 348) > 0));
      g_nMiniGameState = 0;
      g_nMiniGameParam = dword_D92780;
      LoadOverlayTexture(*(UISceneFrm **)&this->m_bRenderAlt);
      UITabCtrl_Render(v43);
    }
    return v3;
  }
  (((UIScene *)this))->UIScene::UpdateAlpha() /* [ROWTABLE] */;
  (((SceneProp *)this))->SceneProp::CalculateWorldPos(resulta);
  if ( !this->m_bLoadFlag )
  {
    v50 = this->m_fFadeTarget + this->m_fFadeMaxAlpha;
    v15 = (((Scene *)**(_DWORD **)&this->m_bRenderAlt))->Scene::GetTileHeight(0, (__int64)((*(float *)&this->m_nTodo_0C + this->m_fFadeProgress - *(float *)(this->m_nScreenFlags + 128))
                    / g_fSceneScale), (__int64)((v50 - *(float *)(this->m_nScreenFlags + 136)) / g_fSceneScale), 0)
        + *(float *)&this->m_nPosY;
    *(float *)&this->m_nLayoutParam = v15;
    v46 = this->m_fScreenTimer + this->m_fCountdown;
    v44 = v15 - v46;
    v16 = this->m_fCountdown - this->m_fScreenTimer;
    v45 = v15 - v16;
    if ( v15 <= v46 )
    {
      if ( v15 >= v16 )
      {
        this->m_bFadeActive = 1;
        *(float *)&this->m_nLayoutParam = v46;
      }
      else
      {
        if ( this->m_fFadeAlpha >= (double)v45 )
        {
          if ( this->m_fFadeAlpha > (double)v45 )
          {
            v20 = this->m_fFadeAlpha - resulta * *(float *)&this->m_nPosX;
            this->m_fFadeAlpha = v20;
            if ( v20 <= v45 )
              this->m_fFadeAlpha = v45;
          }
        }
        else
        {
          v19 = resulta * *(float *)&this->m_nPosX + this->m_fFadeAlpha;
          this->m_fFadeAlpha = v19;
          if ( v19 >= v45 )
          {
            this->m_bFadeActive = 0;
            this->m_fFadeAlpha = v45;
            goto LABEL_35;
          }
        }
        this->m_bFadeActive = 0;
      }
    }
    else
    {
      if ( this->m_fFadeAlpha <= (double)v44 )
      {
        if ( this->m_fFadeAlpha < (double)v44 )
        {
          v18 = resulta * *(float *)&this->m_nPosX + this->m_fFadeAlpha;
          this->m_fFadeAlpha = v18;
          if ( v18 >= v44 )
            this->m_fFadeAlpha = v44;
        }
      }
      else
      {
        v17 = this->m_fFadeAlpha - resulta * *(float *)&this->m_nPosX;
        this->m_fFadeAlpha = v17;
        if ( v17 <= v44 )
        {
          this->m_bFadeActive = 0;
          this->m_fFadeAlpha = v44;
          goto LABEL_35;
        }
      }
      this->m_bFadeActive = 0;
    }
LABEL_35:
    if ( this->m_bFadeActive )
    {
      if ( this->m_fFadeAlpha <= 0.0f )
      {
        if ( this->m_fFadeAlpha >= 0.0f )
          goto LABEL_42;
        v22 = resulta * *(float *)&this->m_nPosX + this->m_fFadeAlpha;
        this->m_fFadeAlpha = v22;
        if ( v22 < 0.0f )
          goto LABEL_42;
        goto LABEL_41;
      }
      v21 = this->m_fFadeAlpha - resulta * *(float *)&this->m_nPosX;
      this->m_fFadeAlpha = v21;
      if ( v21 <= 0.0f )
LABEL_41:
        this->m_fFadeAlpha = 0.0f;
    }
LABEL_42:
    v23 = resulta * *(float *)&this->m_nFadeState * 1.9600000381469727f + *(float *)&this->m_nTodo_0C;
    *(float *)&this->m_nTodo_0C = v23;
    v47 = resulta * this->m_fFadeAlpha;
    this->m_fFadeStart = v47;
    resultc = resulta * *(float *)&this->m_nScreenHeight;
    this->m_fFadeTarget = resultc;
    if ( v23 > resultc )
      *(float *)&this->m_nTodo_0C = resultc;
    v24 = -resultc;
    if ( v24 > *(float *)&this->m_nTodo_0C )
      *(float *)&this->m_nTodo_0C = v24;
    if ( v47 > (double)resultc )
      this->m_fFadeStart = resultc;
    if ( v24 > this->m_fFadeStart )
      this->m_fFadeStart = v24;
    m_nTodo_0C = this->m_nTodo_0C;
    v25 = CalcAngleBetweenVectors(0, 0, 1065353216, m_nTodo_0C, 0.0, resultc);
    *(float *)&this->m_nUIMode = v25;
    if ( *(float *)&m_nTodo_0C < 0.0f )
      *(float *)&this->m_nUIMode = 180.0 - v25 + 180.0 - 360.0;
    m_fFadeStart = this->m_fFadeStart;
    v26 = CalcAngleBetweenVectors(0, 0, 1065353216, 0, m_fFadeStart, 1.0);
    *(float *)&this->m_nScreenWidth = v26;
    if ( m_fFadeStart < 0.0f )
      *(float *)&this->m_nScreenWidth = 180.0 - v26 + 180.0 - 360.0;
    if ( *(float *)&this->m_nScreenWidth < -36.0f )
      this->m_nScreenWidth = -1039138816;
    if ( *(float *)&this->m_nScreenWidth > 36.0f )
      this->m_nScreenWidth = 1108344832;
    p_m_fFadeSpeed = (float *)&this->m_fFadeSpeed;
    *((float *)this->m_pEnumeration + 49) = *(float *)&this->m_nScreenWidth;
    this->m_fFadeSpeed = this->m_fFadeSpeed + *(float *)&this->m_nTodo_0C;
    this->m_fCountdown = this->m_fFadeStart + this->m_fCountdown;
    v3 = this->m_fFadeTarget + this->m_fFadeParam;
    this->m_fFadeParam = v3;
    this->m_fFadeProgress = this->m_fFadeSpeed;
    this->m_VolMod = LODWORD(this->m_fCountdown);
    this->m_fFadeMaxAlpha = this->m_fFadeParam;
    goto LABEL_59;
  }
  v11 = resulta * 1.5800000429153442f;
  p_m_fFadeSpeed = (float *)&this->m_fFadeSpeed;
  if ( v13 | v14 )
  {
    *p_m_fFadeSpeed = *p_m_fFadeSpeed - v11;
    v3 = resulta * 0.6800000071525574f + *(float *)&this->m_nProgressPos;
    *(float *)&this->m_nProgressPos = v3;
    if ( v3 >= 0.0f )
    {
      this->m_nProgressPos = 0;
      this->m_bLoadFlag = 0;
    }
  }
  else
  {
    *p_m_fFadeSpeed = v11 + *p_m_fFadeSpeed;
    v3 = *(float *)&this->m_nProgressPos - resulta * 0.6800000071525574f;
    *(float *)&this->m_nProgressPos = v3;
    if ( v3 <= 0.0f )
    {
      this->m_nProgressPos = 0;
      this->m_bLoadFlag = 0;
    }
  }
LABEL_59:
  (((RoleSystem *)**(RoleSystem ***)&this->m_bRenderAlt))->RoleSystem::SetRoleGridPosition(*p_m_fFadeSpeed, *((_DWORD *)p_m_fFadeSpeed + 1), p_m_fFadeSpeed[2], 0);
  (((PAL3 *)this))->PAL3::CheckViewCollision();
  (((UIAnimateCtrlEX *)this->m_pEnumeration))->UIAnimateCtrlEX::NormalizeVector(*(_DWORD *)p_m_fFadeSpeed, *((_DWORD *)p_m_fFadeSpeed + 1), *((_DWORD *)p_m_fFadeSpeed + 2), this->m_nUIMode);
  v27 = g_pRoleSystem;
  g_pRoleSystem->m_fontcolor.Color = *(unsigned int *)p_m_fFadeSpeed;
  v27->m_wndcolor.Color = (unsigned int)p_m_fFadeSpeed[1];
  v27->m_id = (unsigned int)p_m_fFadeSpeed[2];
  g_pRoleSystem->m_wndcolor.Color = 0;
  p_m_fRotAxisX = (float *)&g_pRoleSystem->m_fRotAxisX;
  LODWORD(g_pRoleSystem->m_fRotAxisX) = this->m_nTodo_0C;
  p_m_fRotAxisX[1] = this->m_fFadeStart;
  p_m_fRotAxisX[2] = this->m_fFadeTarget;
  (((RoleSystem *)&g_pRoleSystem))->RoleSystem::UpdatePosition();
  if ( (((SceneProp *)this))->SceneProp::CalcScreenPosition() )
  {
    g_nSceneState = 2;
    v29 = *((_DWORD *)this->m_pEnumeration + 56);
    v30 = *(_DWORD *)(v29 + 352);
    resultd = v30;
    if ( v30 >= 1000 )
      v30 = 1000;
    *(_DWORD *)(v29 + 348) = v30;
    fValueb = (float)resultd;
    (((UIScrollBar *)(v29 + 3096)))->UIScrollBar::SetRange(fValueb);
    v3 = (float)*(int *)(v29 + 348);
    fValuec = v3;
    (((UIProgressBar *)(v29 + 3096)))->UIProgressBar::FindChildByName(fValuec);
    v31 = *(_DWORD *)(v29 + 348);
    v32 = *(void ( ***)(int, bool))(v29 + 3096);
    *(_BYTE *)(v29 + 356) = v31 <= 0;
    (*v32)(v29 + 3096, v31 > 0);
    (**(void ( ***)(int, bool))(v29 + 3340))((int)(v29 + 3340), (bool)(*(_DWORD *)(v29 + 348) > 0));
    (((PalScriptMgr *)dword_DBA24C))->PalScriptMgr::Destroy();
    (((CGameData *)&g_gamefrm))->CGameData::Load(0);
    HIBYTE(this->m_nProgress) = 1;
    (((GRPinput *)&g_Input))->GRPinput::Reset();
    if ( (g_dwGameFlags & 4) != 0 )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
      v35 = (gbAudioManager *)AudioManager;
      if ( AudioManager )
      {
        (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(1);
        (((gbAudioManager *)v35))->gbAudioManager::StopSoundStream(2);
      }
      if ( CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v36 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v36))->CScreenMode::AudioFadeOut();
      }
      else
      {
        v37 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v37))->CScreenMode::AudioStopAll();
      }
    }
  }
  else if ( (((ArcPastScene *)this))->ArcPastScene::LoadCityData() )
  {
    g_nMiniGameState = *(_DWORD *)(*(_DWORD *)&this->m_bRenderAlt + 8);
    switch ( *(_DWORD *)(*(_DWORD *)&this->m_bRenderAlt + 8) )
    {
      case 1:
        g_nMiniGameParam = 2;
        LoadOverlayTexture(*(UISceneFrm **)&this->m_bRenderAlt);
        UITabCtrl_Render(v43);
        break;
      case 2:
        g_nMiniGameParam = 3;
        LoadOverlayTexture(*(UISceneFrm **)&this->m_bRenderAlt);
        UITabCtrl_Render(v43);
        break;
      case 3:
        g_nMiniGameParam = 4;
        LoadOverlayTexture(*(UISceneFrm **)&this->m_bRenderAlt);
        UITabCtrl_Render(v43);
        break;
      case 4:
        g_nMiniGameParam = 5;
        LoadOverlayTexture(*(UISceneFrm **)&this->m_bRenderAlt);
        UITabCtrl_Render(v43);
        break;
      case 5:
        g_nMiniGameParam = 0;
        g_nMiniGameState = 0;
        g_bSceneLoaded_0 = 1;
        goto LABEL_75;
      default:
LABEL_75:
        UITabCtrl_Render(v43);
        break;
    }
  }
  else if ( *(int *)(*((_DWORD *)this->m_pEnumeration + 56) + 348) <= 0 )
  {
    v38 = (((Scene *)**(_DWORD **)&this->m_bRenderAlt))->Scene::GetTileHeight(0, (__int64)((*p_m_fFadeSpeed - *(float *)(this->m_nScreenFlags + 128)) / g_fSceneScale), (__int64)((p_m_fFadeSpeed[2] - *(float *)(this->m_nScreenFlags + 136)) / g_fSceneScale), 0)
        + *(float *)&this->m_nPosY;
    BYTE2(this->m_nProgress) = 1;
    BYTE1(this->m_nProgress) = 1;
    v3 = v38 - 86.0f;
    *(float *)&this->m_nLayoutOffY = v3;
  }
  return v3;
}

// 0x0053C420
int CScreenMode::CloseBinkVideo()
{
  int result; // eax

  result = this->m_nTodo_0C;
  if ( result )
  {
    result = BinkClose(this->m_nTodo_0C);
    this->m_nTodo_0C = 0;
  }
  return result;
}

// 0x0053C440
int CScreenMode::CreateDevice(int a, int b, int c, int d)
{
  return CScreenMode::OpenBinkVideo(this, (const char *)a, b, c, d);
}

// 0x0053C460
int CScreenMode::WaitBinkFrame()
{
  int result; // eax

  result = this->m_nTodo_0C;
  if ( result )
    return BinkWait(this->m_nTodo_0C);
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

  if ( !this->m_nTodo_0C )
    return 1;
  v3 = gfxMgr;
  if ( !(*(int ( **)(int *, _DWORD))(*(_DWORD *)*(void**)(gfxMgr) + 84))((int *)(v6), 0) )
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
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 88))(gfxMgr);
      return 1;
  }
  v5 = this->CScreenMode::CheckFieldReady(nVal, nVal2, v6[1], *(_DWORD *)&this->m_bRenderAlt, this->m_nScreenFlags, v4);
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 88))(gfxMgr);
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
  int m_nTodo_0C; // eax

  if ( !this->m_nTodo_0C )
    return 1;
  BinkDoFrame(this->m_nTodo_0C);
  BinkCopyToBuffer(this->m_nTodo_0C, nVal, nVal2, nVal3, nVal4, nVal5, nVal6 | 0x80000000);
  m_nTodo_0C = this->m_nTodo_0C;
  if ( *(_DWORD *)(m_nTodo_0C + 12) == *(_DWORD *)(m_nTodo_0C + 8) )
    return 1;
  BinkNextFrame(m_nTodo_0C);
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
  tagMSG Msg; // [esp+0x4C] [ebp-0x1C] BYREF

  if ( this->m_nTodo_0C )
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
    Instance = (UIQuadManager *)UIQuadManager::GetInstance();
    (((UIRenderObj *)Instance))->UIRenderObj::_sdtor_call_dtor(0);
    do
    {
      while ( PeekMessageA(&Msg, 0, 0, 0, 1u) )
      {
        if ( Msg.message == 18 )
        {
          PostQuitMessage(Msg.wParam);
LABEL_13:
          this->CScreenMode::CloseBinkVideo();
          (((UICursor *)v5))->UICursor::_todo_541CC0();
          v6 = (UIQuadManager *)UIQuadManager::GetInstance();
          (((UIRenderObj *)v6))->UIRenderObj::_sdtor_call_dtor(1);
          return 0;
        }
        if ( nVal && Msg.message == 258 && Msg.wParam == 27 )
          goto LABEL_13;
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
      }
    }
    while ( this->CScreenMode::WaitBinkFrame() || !this->CScreenMode::IsSceneReady() );
    this->CScreenMode::CloseBinkVideo();
    (((UICursor *)v8))->UICursor::_todo_541CC0();
    v9 = (UIQuadManager *)UIQuadManager::GetInstance();
    (((UIRenderObj *)v9))->UIRenderObj::_sdtor_call_dtor(1);
  }
  return 1;
}

// 0x0053C6F0
int CScreenMode::SetViewport(int x, int y)
{
  int result; // eax

  result = x;
  *(_DWORD *)&this->m_bRenderAlt = x;
  this->m_nScreenFlags = y;
  return result;
}

// 0x0053C710
int CScreenMode::GetWidth()
{
  int result; // eax

  result = this->m_nTodo_0C;
  if ( result )
    return *(_DWORD *)result;
  return result;
}

// 0x0053C720
int CScreenMode::GetHeight()
{
  int result; // eax

  result = this->m_nTodo_0C;
  if ( result )
    return *(_DWORD *)(result + 4);
  return result;
}

// 0x0053C8C0
int CScreenMode::InitDisplayState()
{
  this->m_RoleDialog._todo_278[146] = 0;
  this->m_RoleDialog._todo_278[145] = 0;
  this->m_RoleDialog._todo_278[144] = 0;
  this->m_RoleDialog._todo_278[147] = -56;
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(this[1].m_Static_816.m_FVF) = -6;
    BYTE1(this[1].m_Static_816.m_FVF) = -1;
    LOBYTE(this[1].m_Static_816.m_FVF) = -1;
  }
  else
  {
    LOBYTE(this[1].m_Static_816.m_FVF) = -6;
    BYTE2(this[1].m_Static_816.m_FVF) = -1;
    BYTE1(this[1].m_Static_816.m_FVF) = -1;
  }
  HIBYTE(this[1].m_Static_816.m_FVF) = -1;
  *(_DWORD *)&this->m_RoleDialog._todo_278[136] = 0;
  *(_DWORD *)&this->m_RoleDialog._todo_278[140] = 0;
  memset(&this->m_RoleDialog._todo_278[148], 0, 0x64u);
  this->m_RoleDialog._todo_278[148] = 95;
  *(_DWORD *)&this->m_RoleDialog._todo_278[124] = 0;
  *(_DWORD *)&this->m_RoleDialog._todo_278[120] = 0;
  *(_DWORD *)&this->m_RoleDialog._todo_278[128] = 800;
  *(_DWORD *)&this->m_RoleDialog._todo_278[132] = 300;
  memset(&this->m_RoleDialog._todo_278[248], 0, 0x6A4u);
  memset(&this->m_bRenderAlt, 0, 0x1210u);
  return (int)this;
}

// 0x0053CDD0
int CScreenMode::SetState(int state)
{
  int result; // eax

  result = state;
  *(_DWORD *)&this->m_RoleDialog._todo_278[136] = state;
  return result;
}

// 0x0053D150
PtrArray * CScreenMode::GetSoundList()
{
  if ( (byte_17B3ED0 & 1) == 0 )
  {
    LOBYTE(byte_17B3ED0) = byte_17B3ED0 | 1;
    (((PtrArray *)&stru_17B3EB0))->PtrArray::ClearBoth();
    atexit(RefreshSoundListBox);
  }
  return &stru_17B3EB0;
}

// 0x0053D1E0
void CScreenMode::SetAudioParam()
{
  int i; // edi
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int j; // edi
  CScreenMode *v7; // ecx
  int v8; // eax
  int k; // edi
  int v10; // [esp+0x0] [ebp-0x8]

  for ( i = 0; i < SLODWORD(this->m_fFadeTarget); ++i )
  {
    PalScriptMgr::ClearAllScript();
    if ( !v3 && i >= 0 && i < SLODWORD(this->m_fFadeTarget) )
      *(_DWORD *)(LODWORD(this->m_fFadeStart) + 4 * i) = 0;
  }
  v4 = 0;
  while ( v4 < SLODWORD(this->m_fFadeTarget) )
  {
    if ( v4 >= 0 && v4 < SLODWORD(this->m_fFadeTarget) && *(_DWORD *)(LODWORD(this->m_fFadeStart) + 4 * v4) )
      ++v4;
    else
      (((PtrArray *)&this->m_fFadeStart))->PtrArray::RemoveAt(v4, 1);
  }
  v5 = *(_DWORD *)&this->m_bRenderAlt;
  for ( j = 0; j < v5; ++j )
  {
    if ( j < 0 || j >= v5 )
      v7 = 0;
    else
      v7 = (CScreenMode *)(*(CScreenMode **)&this->m_pEnumeration[4 * j]);
    if ( (((CScreenMode *)v7))->CScreenMode::sub_42C1C0(v10) && j >= 0 && j < *(_DWORD *)&this->m_bRenderAlt )
      *(_DWORD *)&this->m_pEnumeration[4 * j] = 0;
    v5 = *(_DWORD *)&this->m_bRenderAlt;
  }
  v8 = *(_DWORD *)&this->m_bRenderAlt;
  for ( k = 0; k < v8; v8 = *(_DWORD *)&this->m_bRenderAlt )
  {
    if ( k >= 0 && k < v8 && *(_DWORD *)&this->m_pEnumeration[4 * k] )
      ++k;
    else
      (((PtrArray *)this))->PtrArray::RemoveAt(k, 1);
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
  int i; // esi
  _BYTE *v4; // eax
  int m_nTodo_0C; // eax
  _BYTE *v6; // ecx
  char v7; // al

  (((CPK *)&this->m_Static_816.m_rect))->CPK::~CPK();
  Color = this->m_Static_816.m_fontcolor.Color;
  for ( i = (int)((UIWnd *)&this->m_Static_816); i != Color; i += 20 )
  {
    if ( *(_DWORD *)(i + 4) )
    {
      if ( !*(_BYTE *)nearby_53edd0(*(_DWORD *)(i + 4)) || *(_BYTE *)nearby_53edd0(*(_DWORD *)(i + 4)) == 0xFF )
      {
        (((CScreenMode *)i))->CScreenMode::FreeSoundBuffer((void *)(*(_DWORD *)(i + 4) - 1), *(_DWORD *)(i + 12) + 2);
      }
      else
      {
        v4 = (_BYTE *)nearby_53edd0(*(_DWORD *)(i + 4));
        --*v4;
      }
    }
    *(_DWORD *)(i + 4) = 0;
    *(_DWORD *)(i + 8) = 0;
    *(_DWORD *)(i + 12) = 0;
  }
  operator delete(*(void **)((UIWnd *)&this->m_Static_816));
  *(_DWORD *)((UIWnd *)&this->m_Static_816) = 0;
  this->m_Static_816.m_fontcolor.Color = 0;
  this->m_Static_816.m_wndcolor.Color = 0;
  (((PalScript *)&this->m_FrameB.m_fontcolor))->PalScript::Cleanup();
  m_nTodo_0C = this->m_nTodo_0C;
  if ( m_nTodo_0C )
  {
    v6 = (_BYTE *)(m_nTodo_0C - 1);
    v7 = *(_BYTE *)(m_nTodo_0C - 1);
    if ( !v7 || v7 == -1 )
      operator delete(v6);
    else
      *v6 = v7 - 1;
  }
  this->m_nTodo_0C = 0;
  this->m_fFadeStart = 0.0f;
  this->m_fFadeTarget = 0.0f;
}

// 0x0053DD70
void CScreenMode::SetMode(int mode)
{
  gbAudioManager *v3; // eax
  gbAudioManager *v4; // eax
  gbAudioManager *v5; // edi
  bool v6; // zf
  unsigned int v7; // eax
  tagRECT *p_m_rect; // esi
  int v9; // [esp+0xC] [ebp-0x268] BYREF
  OpenBaseFile v10; // [esp+0x10] [ebp-0x264] BYREF
  gbAudioManager *v11; // [esp+0x14] [ebp-0x260]
  char Buffer[324]; // [esp+0x18] [ebp-0x25C] BYREF
  gbAudioMgrDesc v13; // [esp+0x15C] [ebp-0x118] BYREF
  int v14; // [esp+0x270] [ebp-0x4]

  if ( (g_dwGameFlags & 5) != 0 )
  {
    v3 = (gbAudioManager *)operator new(0xF4u);
    v11 = (gbAudioManager *)v3;
    v14 = 0;
    if ( v3 )
    {
      v3->gbAudioManager::gbAudioManager(&v9, &v13);
      v5 = (gbAudioManager *)v4;
    }
    else
    {
      v5 = 0;
    }
    v14 = -1;
    v6 = v9 == 0;
    this->m_pAudioMgr = ((gbAudioManager *)(v5));
    if ( v6 )
    {
      if ( v5 )
      {
        (((gbAudioManager *)v5))->gbAudioManager::~gbAudioManager();
        operator delete(v5);
      }
      this->m_pAudioMgr = ((gbAudioManager *)0);
      v7 = g_dwGameFlags;
      LOBYTE(v7) = g_dwGameFlags & 0xFA;
      g_dwGameFlags = v7;
    }
    else
    {
      this->m_Static_816.m_id = 0;
      this->m_nFadeState = 0;
      v14 = 1;
      (((PalScript *)&this->m_FrameB.m_fontcolor))->PalScript::LoadFromFile("datascript\\music.txt");
      if ( (g_dwGameFlags & 2) != 0 )
      {
        p_m_rect = (tagRECT *)&this->m_Static_816.m_rect;
        (((CPK *)p_m_rect))->CPK::SetOpenMode(CPKM_Normal);
        if ( (((CPK *)p_m_rect))->CPK::IsValidCPK("music\\music.cpk") )
        {
          (((CPK *)p_m_rect))->CPK::Load("music\\music.cpk");
        }
        else
        {
          sprintf(Buffer, "%s%s", (const char *)&Data, "music\\music.cpk");
          if ( (((CPK *)p_m_rect))->CPK::IsValidCPK(Buffer) )
            (((CPK *)p_m_rect))->CPK::Load(Buffer);
        }
      }
      v14 = -1;
      ((OpenNULLFile *)&v10)->OpenNULLFile::OpenNULLFile();
    }
  }
}

// 0x0053DEF0
void CScreenMode::Restore()
{
  gbAudioManager *m_pAudioMgr; // esi

  this->CScreenMode::ApplyColorFilter();
  m_pAudioMgr = (gbAudioManager *)this->m_pAudioMgr;
  if ( m_pAudioMgr )
  {
    (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::~gbAudioManager();
    operator delete(m_pAudioMgr);
    this->m_pAudioMgr = ((gbAudioManager *)0);
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

  v2 = (unsigned __int8 *)*(unsigned __int8 **)(nVal2 + 4);
  if ( !v2 )
    v2 = (unsigned __int8 *)&g_bActorFlag;
  v3 = (unsigned __int8 *)*(unsigned __int8 **)(nVal + 4);
  if ( !v3 )
    v3 = (unsigned __int8 *)&g_bActorFlag;
  return _strcmpi((const char *)v3, (const char *)v2) == 0;
}

// 0x0053DFB0
int CScreenMode::PlaySoundStream(const void *pData)
{
  unsigned int Color; // ebp
  int i; // edi
  gbSound2DNode *v6; // eax
  void *v7; // eax
  void *v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // esi
  int v13; // esi
  int v14; // ecx
  unsigned int v15; // edx
  int *v16; // edi
  gbSound2DNode *v17; // ecx
  gbSound2DNode *v18; // edi
  unsigned int v19; // ebp
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
  InitAction((Actor *)&v25, &pActionType);
  v34 = 0;
  (((PalScriptIdleObj *)&v25))->PalScriptIdleObj::UpdateWait(unk_C10D38, strlen(unk_C10D38));
  Block = 0;
  v34 = 1;
  (((PalScriptIdleObj *)&v25))->PalScriptIdleObj::UpdateWait(pData, strlen((const char *)pData));
  Color = this->m_Static_816.m_fontcolor.Color;
  for ( i = (int)((UIWnd *)&this->m_Static_816); i != Color; i += 20 )
  {
    if ( CScreenMode::GetByteParam(i, (int)&v25) )
      break;
  }
  if ( i == this->m_Static_816.m_fontcolor.Color || (((gbSound2DNode *)*(gbSound2DNode **)(i + 16)))->gbSound2DNode::IsPlaying() )
  {
    v6 = (gbSound2DNode *)operator new(0x10u);
    v32 = (gbSound2DNode *)v6;
    LOBYTE(v34) = 2;
    if ( v6 )
      v6->gbSound2DNode::gbSound2DNode();
    else
      v7 = 0;
    LOBYTE(v34) = 1;
    Block = (void *)v7;
    sprintf(Buffer, "snd\\%s.wav", (const char *)pData);
    if ( (((gbSound2DNode *)Block))->gbSound2DNode::LoadFromFile(Buffer) )
    {
      v9 = (int)((UIWnd *)&this->m_Static_816);
      if ( v9 && (unsigned int)((int)(this->m_Static_816.m_fontcolor.Color - v9) / 20) >= 0x20 )
      {
        v14 = (int)((UIWnd *)&this->m_Static_816);
        v15 = 5 * this->m_Static_816.m_id;
        LOBYTE(v27) = pActionType;
        v16 = (int *)(v14 + 4 * v15);
        (((std::string *)0))->_Tidy();
        LOBYTE(v34) = 3;
        (((PalScript *)&v27))->PalScript::InitScriptObj(v16, 0, 0xFFFFFFFF);
        v17 = (gbSound2DNode *)v16[4];
        v31 = (gbSound2DNode *)v17;
        LOBYTE(v34) = 4;
        v18 = (gbSound2DNode *)v17;
        if ( v17 )
        {
          (((gbSound2DNode *)v17))->gbSound2DNode::~gbSound2DNode();
          operator delete(v18);
        }
        v19 = 20 * this->m_Static_816.m_id;
        v20 = (PalScript *)(v19 + *(_DWORD *)((UIWnd *)&this->m_Static_816));
        if ( v20 != (PalScript *)&v25 )
        {
          (((PalScript *)v20))->PalScript::InitScriptObj((int *)&v25, 0, 0xFFFFFFFF);
          v20->m_nState = (int)Block;
        }
        v21 = this->m_Static_816.m_id + 1;
        this->m_Static_816.m_id = v21;
        if ( v21 >= 32 )
          this->m_Static_816.m_id = 0;
        v13 = v19 + *(_DWORD *)((UIWnd *)&this->m_Static_816);
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
        (((CScreenMode *)&this->m_pSoundStream))->CScreenMode::AddSoundEntry((char *)this->m_Static_816.m_fontcolor.Color, (char *)&v25);
        v10 = (int)((UIWnd *)&this->m_Static_816);
        if ( v10 )
          v11 = (int)(this->m_Static_816.m_fontcolor.Color - v10) / 20;
        else
          v11 = 0;
        v12 = (int)((UIWnd *)&this->m_Static_816);
        v34 = -1;
        v13 = v12 + 20 * v11 - 20;
        (((std::string *)1))->_Tidy();
      }
      return v13;
    }
    else
    {
      v8 = (void *)Block;
      if ( Block )
      {
        (((gbSound2DNode *)Block))->gbSound2DNode::~gbSound2DNode();
        operator delete(v8);
      }
      v34 = -1;
      (((std::string *)1))->_Tidy();
      return 0;
    }
  }
  else
  {
    v34 = -1;
    (((std::string *)1))->_Tidy();
    return i;
  }
}

// 0x0053E2E0
void CScreenMode::AudioSetPosition(const void *pData, int nVal)
{
  int v3; // eax

  if ( (g_dwGameFlags & 1) != 0 )
  {
    v3 = this->CScreenMode::PlaySoundStream(pData);
    if ( v3 )
    {
      *(_DWORD *)(*(_DWORD *)(v3 + 16) + 8) = nVal;
      (((gbSound2DNode *)*(gbSound2DNode **)(v3 + 16)))->gbSound2DNode::Play();
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
      (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::SetListenerPosition(g_pCameraCtrl->m_vecLookAt);
      (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::SetListenerOrientation(g_pCameraCtrl->m_vecLookAt + 1,  g_pCameraCtrl->m_vecUpDir);
    }
  }
}

// 0x0053E4E0
void CScreenMode::PlaySoundIfEnabled(void *pSound, int nMode)
{
  if ( (g_dwGameFlags & 1) != 0 )
    this->CScreenMode::AudioSetPosition(pSound, nMode);
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
    (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(1);
    (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(2);
    (((PalScript *)&this->m_FrameB.m_fontcolor))->PalScript::SetDirectory("scene");
    sprintf(Buffer, (const char *)&dir[24], pszScene, pszArea);
    if ( (((PalScript *)&this->m_FrameB.m_fontcolor))->PalScript::FindSaveStateString((PalScript *)Buffer, String1, (char *)0x100, v5)
      || (((PalScript *)&this->m_FrameB.m_fontcolor))->PalScript::FindSaveStateString((PalScript *)pszScene, String1, (char *)0x100, v6) )
    {
      sprintf(Buffer, "music\\%s.mp3", String1);
      if ( _strcmpi(String1, (const char *)&this->m_fFadeAlpha)
        || (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::GetStreamStatus(0) != 1 )
      {
        strcpy((char *)&this->m_fFadeAlpha, (const char *)String1);
        if ( _strcmpi(String1, "NONE") )
        {
          (((SoundMgr *)this))->SoundMgr::PlayCPKStream(0);
          if ( nVal )
            (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::PauseSoundStream(0);
        }
        else
        {
          (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(0);
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
    (((PalScript *)&this->m_FrameB.m_fontcolor))->PalScript::SetDirectory("combat");
    if ( (((PalScript *)&this->m_FrameB.m_fontcolor))->PalScript::FindSaveStateString((PalScript *)pszSceneName, Destination, (char *)0x100, v3) )
    {
      sprintf(Buffer, "music\\%s.mp3", Destination);
      (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(2);
      (((SoundMgr *)this))->SoundMgr::PlayCPKStream(1);
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
    result = this->CScreenMode::StopAll();
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
  int m_nTodo_0C; // ecx
  char v8; // al
  unsigned int m_fFadeTarget_low; // eax
  int v10; // ecx
  char v12[256]; // [esp+0xC] [ebp-0x100] BYREF
if ( (g_dwGameFlags & 4) == 0 )
    return;
  (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(1);
  (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(0);
  p_m_nScreenFlags = (int *)&this->m_nScreenFlags;
  v5 = strlen(pszName) + 1;
  v6 = v5 - 1;
  if ( v5 - 1 > 0xFFFFFFFD )
    std::_Xlen();
  m_nTodo_0C = this->m_nTodo_0C;
  if ( !m_nTodo_0C || (v8 = *(_BYTE *)(m_nTodo_0C - 1)) == 0 || v8 == -1 )
  {
    if ( v5 == 1 )
    {
      (((std::string *)1))->_Tidy();
      goto LABEL_16;
    }
    m_fFadeTarget_low = LODWORD(this->m_fFadeTarget);
    if ( m_fFadeTarget_low <= 0x1F && m_fFadeTarget_low >= v6 )
    {
LABEL_15:
      qmemcpy((void *)this->m_nTodo_0C, pszName, v6);
      v10 = this->m_nTodo_0C;
p_m_nScreenFlags[2] = v6;
      *(_BYTE *)(v10 + v6) = 0;
      goto LABEL_16;
    }
    (((std::string *)1))->_Tidy();
LABEL_14:
    (((GRPinput *)&this->m_nScreenFlags))->GRPinput::PollInputState(v6);
    goto LABEL_15;
  }
  if ( v5 != 1 )
    goto LABEL_14;
  *(_BYTE *)(m_nTodo_0C - 1) = v8 - 1;
  this->m_nTodo_0C = 0;
  this->m_fFadeStart = 0.0f;
  this->m_fFadeTarget = 0.0f;
LABEL_16:
  this->m_nFadeState = (int)pAudioMgr;
  if ( pszName && _strcmpi("NONE", pszName) )
  {
    sprintf(v12, "music\\%s.mp3", pszName);
    (((SoundMgr *)this))->SoundMgr::PlayCPKStream(2);
  }
  else
  {
    (((gbAudioManager *)this->m_pAudioMgr))->gbAudioManager::StopSoundStream(2);
  }
}

// 0x0053E890
void CScreenMode::ApplyColorFilter()
{
  unsigned int v1; // edi
  int i; // ebp
  int v4; // eax
  int v5; // ecx
  void *v6; // esi
  unsigned int v7; // edi
  unsigned int Color; // ebp
  unsigned int j; // esi

  v1 = 0;
  for ( i = 0; ; i += 20 )
  {
    v4 = (int)((UIWnd *)&this->m_Static_816);
    if ( !v4 || v1 >= (int)(this->m_Static_816.m_fontcolor.Color - v4) / 20 )
      break;
    v5 = (int)((UIWnd *)&this->m_Static_816);
    v6 = (void *)*(void **)(v5 + i + 16);
    if ( v6 )
    {
      (((gbSound2DNode *)*(gbSound2DNode **)(v5 + i + 16)))->gbSound2DNode::~gbSound2DNode();
      operator delete(v6);
    }
    ++v1;
  }
  v7 = (unsigned int)((UIWnd *)&this->m_Static_816);
  Color = this->m_Static_816.m_fontcolor.Color;
  for ( j = v7; j != Color; j += 20 )
    (((std::string *)j))->~string();
  this->m_Static_816.m_fontcolor.Color = v7;
}

// 0x0053E950
void CScreenMode::AudioStopAll()
{
  char *v2; // eax
  const char *v3; // [esp-0x8] [ebp-0xC]

  v3 = (const char *)&UISceneUpdate()->m_pCapacity[5];
  v2 = (char *)UISceneUpdate();
  this->CScreenMode::PlaySceneMusic(v2, v3, 0);
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
    result = (unsigned int)((UIWnd *)&this->m_Static_816);
    if ( !result )
      break;
    v5 = this->m_Static_816.m_fontcolor.Color - result;
    result = (unsigned int)((unsigned __int64)(1717986919i64 * v5) >> 32) >> 31;
    if ( v1 >= v5 / 20 )
      break;
    (((gbSound2DNode *)*(gbSound2DNode **)(*(_DWORD *)((UIWnd *)&this->m_Static_816) + i + 16)))->gbSound2DNode::Stop();
    ++v1;
  }
  return result;
}

// 0x0053EA60
void CScreenMode::AudioFadeOut()
{
  char *m_nTodo_0C; // eax

  if ( LODWORD(this->m_fFadeStart) )
  {
    m_nTodo_0C = (char *)this->m_nTodo_0C;
    if ( !m_nTodo_0C )
      m_nTodo_0C = (char *)&g_bActorFlag;
    this->CScreenMode::PlayAmbientSound(m_nTodo_0C, (gbAudioManager *)this->m_nFadeState);
  }
}

// 0x0053EB50
int CScreenMode::IterateChildList()
{
  int m_nScreenFlags; // ebx
  int i; // esi
  int result; // eax

  m_nScreenFlags = this->m_nScreenFlags;
  for ( i = *(_DWORD *)&this->m_bRenderAlt; i != m_nScreenFlags; i += 20 )
    (((std::string *)i))->~string();
  operator delete(*(void **)&this->m_bRenderAlt);
  result = 0;
  *(_DWORD *)&this->m_bRenderAlt = 0;
  this->m_nScreenFlags = 0;
  this->m_nTodo_0C = 0;
  return result;
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
  if ( (this->m_nTodo_0C - (int)m_nScreenFlags) / 20 )
  {
    if ( ((char *)m_nScreenFlags - pszBuf) / 20 )
    {
      this->CScreenMode::ComparePointers(m_nScreenFlags - 5, m_nScreenFlags, m_nScreenFlags);
      SceneObj::LoadFromConfig((int *)pszBuf, (int *)(this->m_nScreenFlags - 20), this->m_nScreenFlags);
      (((SceneObj *)(pszBuf + 20)))->SceneObj::StringCopyReplace((SceneObj *)pszBuf, pszBuf + 20, pszBuf2);
    }
    else
    {
      this->CScreenMode::ComparePointers((int *)pszBuf, m_nScreenFlags, (int *)pszBuf + 5);
      this->CScreenMode::InitSceneObjects((int *)this->m_nScreenFlags, 1 - (this->m_nScreenFlags - (int)pszBuf) / 20, (int *)pszBuf2);
      (((SceneObj *)v15))->SceneObj::StringCopyReplace((SceneObj *)pszBuf, (char *)this->m_nScreenFlags, pszBuf2);
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
    v12 = (SceneObj *)(*(SceneObj **)&this->m_bRenderAlt);
    v17 = (SceneObj *)v10;
    for ( i = v10; v12 != (SceneObj *)pszBuf; i = (SceneObj *)((char *)i + 20) )
    {
      (((SceneObj *)v11))->SceneObj::StringCopyCat(i, v12);
      v12 = (SceneObj *)((char *)v12 + 20);
    }
    (((SceneObj *)v11))->SceneObj::StringCopyCat(i, (SceneObj *)pszBuf2);
    this->CScreenMode::ComparePointers((int *)pszBuf, (int *)this->m_nScreenFlags, &i->m_rect.top);
    this->CScreenMode::DestroyString(*(int **)&this->m_bRenderAlt, (int *)this->m_nScreenFlags);
    operator delete(*(void **)&this->m_bRenderAlt);
    this->m_nTodo_0C = (int)v17 + 20 * (_DWORD)pszBufa;
    SoundCount = this->CScreenMode::GetSoundCount();
    *(_DWORD *)&this->m_bRenderAlt = (_DWORD)v17;
    this->m_nScreenFlags = (int)(&v17->m_rect.top + 5 * SoundCount);
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

  v4 = (int *)p_DWORD;
  if ( p_DWORD == p_DWORD2 )
    return p_DWORD3;
  v5 = (int *)p_DWORD3;
  do
  {
    (((SceneObj *)this))->SceneObj::StringCopyCat((SceneObj *)v5, (SceneObj *)v4) /* [ROWTABLE] */;
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
    (((SceneObj *)this))->SceneObj::StringCopyCat((SceneObj *)p_DWORD, (SceneObj *)p_DWORD2) /* [ROWTABLE] */;
    p_DWORD += 5;
  }
}

// 0x0053F220
char CScreenMode::UpdateRenderState(int *lpString)
{
  double v3; // st7
  char *v4; // eax
  __int64 v5; // rcx
  unsigned int v6; // edx
  unsigned int v7; // eax
  double v8; // st7
  double v9; // st6
  double v10; // st7
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  float v14; // edx
  int v15; // eax
  int v16; // ecx
  float v17; // edx
  float v18; // eax
  char result; // al
  int v20; // edx
  float v21; // eax
  float v22; // ecx
  int v23; // edx
  int v24; // eax
  float v25; // ecx
  float v26; // edx
  int v27; // eax
  int v28; // ecx
  float v29; // edx
  float v30; // eax
  int v31; // ecx
  int v32; // edx
  float v33; // [esp+0x14] [ebp-0x34]
  float v34; // [esp+0x18] [ebp-0x30]
  __int64 v35; // [esp+0x20] [ebp-0x28]
  __int64 v36; // [esp+0x20] [ebp-0x28]
  char v37; // [esp+0x28] [ebp-0x20] BYREF
  float v38; // [esp+0x2C] [ebp-0x1C]
  int v39; // [esp+0x30] [ebp-0x18]
  int v40; // [esp+0x34] [ebp-0x14]
  float v41; // [esp+0x38] [ebp-0x10]
  float v42; // [esp+0x3C] [ebp-0xC]
  int v43; // [esp+0x40] [ebp-0x8]
  int v44; // [esp+0x44] [ebp-0x4]

  *((_BYTE *)&this->m_Static_816 + 268) = 0;
  if ( lstrlenA((LPCSTR)this) <= 0
    || lstrlenA((LPCSTR)&this->m_StaticArray.m_ratioh) <= 0
    || !*((_DWORD *)&this->m_Static_816 + 56)
    || !*((_DWORD *)&this->m_Static_816 + 57) )
  {
    return 0;
  }
  v5 = *((unsigned int *)&this->m_Static_816 + 52);
  v3 = (double)v5;
  v4 = (char *)&v37;
  LODWORD(v5) = 4;
  v33 = 1.0f / v3;
  v34 = 1.0f / (float)*((unsigned int *)&this->m_Static_816 + 53);
  do
  {
    *(_DWORD *)v4 = 0;
    *((_DWORD *)v4 + 1) = 0;
    v4 += 8;
    LODWORD(v5) = v5 - 1;
  }
  while ( (_DWORD)v5 );
  v6 = *((_DWORD *)&this->m_Static_816 + 53);
  v7 = v6 - *((_DWORD *)&this->m_Static_816 + 55);
  v8 = (double)*((unsigned int *)&this->m_Static_816 + 54) * v33;
  v9 = (double)*((unsigned int *)&this->m_Static_816 + 52);
  v35 = v7 - *((_DWORD *)&this->m_Static_816 + 57);
  LODWORD(v5) = *((_DWORD *)&this->m_Static_816 + 56) + *((_DWORD *)&this->m_Static_816 + 54);
  *((_DWORD *)&this->m_Static_816 + 55) = v7;
  v10 = v8 - 0.5 / v9;
  v38 = ((float)v35 - 0.5f) * v34;
  v36 = v7;
  v11 = *((_DWORD *)&this->m_Static_816 + 66);
  v41 = ((float)v5 - 0.5f) * v33;
  v42 = (float)v36 * v34 - 0.5f / (float)v6;
  if ( v11 )
  {
    v12 = v11 - 1;
    if ( v12 )
    {
      if ( v12 == 1 )
      {
        v13 = v44;
        v14 = v38;
        *((_DWORD *)&this->m_Static_816 + 58) = v43;
        v15 = v39;
        *((_DWORD *)&this->m_Static_816 + 59) = v13;
        *((float *)&this->m_Static_816 + 60) = v10;
        v16 = v40;
        *((float *)&this->m_Static_816 + 61) = v14;
        v17 = v41;
        *((_DWORD *)&this->m_Static_816 + 62) = v15;
        v18 = v42;
        *((_DWORD *)&this->m_Static_816 + 63) = v16;
        *((float *)&this->m_Static_816 + 65) = v18;
        result = 1;
        *((float *)&this->m_Static_816 + 64) = v17;
      }
      else
      {
        result = 1;
      }
      *((_BYTE *)&this->m_Static_816 + 268) = 1;
    }
    else
    {
      v20 = v40;
      v21 = v41;
      *((_DWORD *)&this->m_Static_816 + 58) = v39;
      v22 = v42;
      *((_DWORD *)&this->m_Static_816 + 59) = v20;
      v23 = v43;
      *((float *)&this->m_Static_816 + 60) = v21;
      v24 = v44;
      *((float *)&this->m_Static_816 + 61) = v22;
      v25 = v38;
      *((_DWORD *)&this->m_Static_816 + 63) = v24;
      *((_DWORD *)&this->m_Static_816 + 62) = v23;
      result = 1;
      *((float *)&this->m_Static_816 + 64) = v10;
      *((float *)&this->m_Static_816 + 65) = v25;
      *((_BYTE *)&this->m_Static_816 + 268) = 1;
    }
  }
  else
  {
    v26 = v38;
    v27 = v39;
    *((float *)&this->m_Static_816 + 58) = v10;
    v28 = v40;
    *((float *)&this->m_Static_816 + 59) = v26;
    v29 = v41;
    *((_DWORD *)&this->m_Static_816 + 60) = v27;
    v30 = v42;
    *((_DWORD *)&this->m_Static_816 + 61) = v28;
    v31 = v43;
    *((float *)&this->m_Static_816 + 62) = v29;
    v32 = v44;
    *((float *)&this->m_Static_816 + 63) = v30;
    result = 1;
    *((_DWORD *)&this->m_Static_816 + 64) = v31;
    *((_DWORD *)&this->m_Static_816 + 65) = v32;
    *((_BYTE *)&this->m_Static_816 + 268) = 1;
  }
  return result;
}

// 0x0053F4C0
_DWORD * CScreenMode::_nearby_53f4c0()
{
  return &this->m_pEnumeration;
}

// 0x00569320
int CScreenMode::LoadAudioFromFile(int *p_DWORD, FILE *Stream, int *p_DWORD2)
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
  int v17; // [esp+0x10] [ebp-0x14] BYREF
  int Buffer; // [esp+0x14] [ebp-0x10] BYREF
  float v19; // [esp+0x18] [ebp-0xC] BYREF
  float v20; // [esp+0x1C] [ebp-0x8]
  float v21; // [esp+0x20] [ebp-0x4]

  v3 = (FILE *)Stream;
  v4 = ftell(Stream);
  v5 = (int *)p_DWORD2;
  p_DWORD2[40] = v4;
  Buffer = g_nPtrArray_D8E46C;
  fwrite(&Buffer, 4u, 1u, v3);
  v6 = 0;
  if ( Buffer > 0 )
  {
    v7 = 0;
    do
    {
      fwrite((const void *)(v7 + Block), 0x18u, 1u, v3);
      ++v6;
      v7 += 24;
    }
    while ( v6 < Buffer );
  }
  v5[41] = ftell(v3);
  v8 = 0;
  v9 = (unsigned long)p_DWORD[1];
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
      VecEntry_Write((Actor *)(p_DWORD[1] + v15), v3);
      ++v8;
      v15 += 164;
    }
    while ( v8 < (int)Stream );
    v5 = (int *)p_DWORD2;
  }
  v5[42] = ftell(v3);
  v19 = 1.0f;
  v20 = 1.0f;
  v21 = 1.0f;
  Instance = (CScreenMode *)CScreenMode::GetInstance();
  AudioManager = (float *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
  v12 = 0;
  if ( AudioManager )
  {
    v19 = AudioManager[52];
    v20 = AudioManager[51];
    v21 = AudioManager[53];
  }
  fwrite(&v19, 0xCu, 1u, v3);
  v5[46] = ftell(v3);
  v13 = (unsigned long)p_DWORD[5];
  if ( v13 )
    v17 = (p_DWORD[6] - v13) >> 6;
  else
    v17 = 0;
  fwrite(&v17, 4u, 1u, v3);
  result = v17;
  if ( v17 > 0 )
  {
    v16 = 0;
    do
    {
      fwrite((const void *)(v16 + p_DWORD[5]), 0x40u, 1u, v3);
      result = v17;
      ++v12;
      v16 += 64;
    }
    while ( v12 < v17 );
  }
  return result;
}

// 0x005694F0
int CScreenMode::OpenBinkVideo(CScreenMode *pScreen, const char *szFilename, int nVal, int nVal2, int nFlags)
{
  float *p_m_fFadeStart; // edi
  CPKFile *v7; // ebx
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  int v10; // eax

  (((CScreenMode *)pScreen))->CScreenMode::CloseBinkVideo();
  if ( !*((_BYTE *)&pScreen[166].m_RoleDialog + 1476) && !*((_BYTE *)&pScreen[333].m_RoleDialog + 1592) )
  {
    pScreen->m_nTodo_0C = BinkOpen(szFilename, nFlags);
    goto LABEL_4;
  }
  p_m_fFadeStart = (float *)&pScreen->m_fFadeStart;
  v7 = (((CPK *)&pScreen->m_fFadeStart))->CPK::Open(szFilename);
  if ( v7 )
  {
    v10 = *((_DWORD *)&pScreen[166].m_RoleDialog + 370);
  }
  else
  {
    p_m_fFadeStart = (float *)&pScreen[167].m_nProgress;
    v7 = (((CPK *)&pScreen[167].m_nProgress))->CPK::Open(szFilename);
    if ( !v7 )
      goto LABEL_4;
    v10 = *((_DWORD *)&pScreen[333].m_RoleDialog + 399);
  }
  pScreen->m_nTodo_0C = BinkOpen(v10, (unsigned int)&dword_800000 | nFlags);
  (((CPK *)p_m_fFadeStart))->CPK::Close(v7);
LABEL_4:
  if ( !pScreen->m_nTodo_0C )
    return 0;
  Instance = (CScreenMode *)CScreenMode::GetInstance();
  AudioManager = (((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
  if ( AudioManager )
    BinkSetVolume(pScreen->m_nTodo_0C, (__int64)(*(float *)(AudioManager + 208) * 65535.0));
  return 1;
}
