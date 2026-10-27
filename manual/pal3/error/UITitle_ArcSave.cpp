#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_ArcSave.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Misc/LineupComp.h"
#include "Misc/NameSys.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Scene/SceneObj.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int PalScript_Cleanup(...);

// 0x0047BBF0
UITitle_ArcSave::UITitle_ArcSave()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  (((UIFrameContainer *)&this->m_YesNo.m_bvisible))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_YesNo.m_bk.m_texs.m_ptex[3]))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  ((LineupComp *)((char *)&this->m_YesNo + 1848))->LineupComp::LineupComp();
  this->m_YesNo.m_rect.left = 88;
  this->m_YesNo.m_rect.top = 138;
  this->m_YesNo.m_pfather = ((UIWnd *)((UIWnd *)90));
  this->m_YesNo.m_childs.m_pData = ((char *)((char *)26));
  this->m_YesNo.m_rect.right = 800;
  this->m_YesNo.m_rect.bottom = 64;
  this->m_YesNo.m_bcreateok = 0;
  *((_DWORD *)&this->m_YesNo + 979) = 0;
  *((_BYTE *)&this->m_YesNo + 3928) = 1;
}

// 0x0047BD20
UITitle_ArcSave::~UITitle_ArcSave()
{
  this->UITitle_ArcSave::Destroy();
  PalScript_Cleanup((PalScript *)((char *)&this->m_YesNo + 1848));
  (((UICaption *)((char *)&this->m_YesNo + 1504)))->UICaption::Destroy2();
  (((UICaption *)(&this->m_YesNo.pCallbackVtable2 + 46)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_YesNo.m_btRc + 184)))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_YesNo.m_bk.m_texs.m_ptex[3]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_YesNo.m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0047BDF0
void UITitle_ArcSave::Destroy()
{
  int m_needscriptdel; // ecx

  m_needscriptdel = this->m_YesNo.m_childs.m_needscriptdel;
  if ( m_needscriptdel )
  {
    (*(void ( **)(int, int))(*(_DWORD *)m_needscriptdel + 20))(m_needscriptdel, 3);
    this->m_YesNo.m_childs.m_needscriptdel = 0;
  }
  Destroy__ovl_03((int)this);
}

// 0x0047C370
void UITitle_ArcSave::Render()
{
  int m_bcreateok; // eax
  int v3; // [esp+0x0] [ebp-0x4]
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0x4]

  PAL3_Render_47c260(v3);
  m_bcreateok = this->m_YesNo.m_bcreateok;
  if ( m_bcreateok )
  {
    if ( m_bcreateok == 1 )
      (*(void ( **)(int))(*(_DWORD *)this->m_YesNo.m_childs.m_needscriptdel + 4))(this->m_YesNo.m_childs.m_needscriptdel);
  }
  else
  {
    (((CCBControlWindow *)this))->CCBControlWindow::Render(v4) /* [ROWTABLE] */;
  }
}

// 0x0047C3A0
int UITitle_ArcSave::ProcessPageAction(PalScript *p, int nVal)
{
  int result; // eax

  switch ( this->m_YesNo.m_bcreateok )
  {
    case 0:
      StopSceneScripts((const char *)p);
      (((SceneObj *)this))->SceneObj::Update((int)p, nVal) /* [ROWTABLE] */;
      result = 1;
      break;
    case 1:
      (*(void ( **)(int, PalScript *, int))(*(_DWORD *)this->m_YesNo.m_childs.m_needscriptdel
                                                                      + 8))(
        this->m_YesNo.m_childs.m_needscriptdel,
        p,
        nVal);
      result = 1;
      break;
    case 2:
      (((CGameData *)&g_gamefrm))->CGameData::Load(0);
      result = 1;
      break;
    case 3:
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)4);
      goto LABEL_6;
    default:
LABEL_6:
      result = 1;
      break;
  }
  return result;
}

// 0x0047C430
int UITitle_ArcSave::OnMessage(int nVal, int nVal2, int nVal3)
{
  CScreenMode *v5; // eax
  CScreenMode *v6; // eax
  CScreenMode *Instance; // eax
  PalScriptMgr *v8; // ecx
  const void *v9; // [esp-0x8] [ebp-0xC]
  const void *v10; // [esp-0x8] [ebp-0xC]
  const void *v11; // [esp-0x8] [ebp-0xC]

  if ( nVal == 1000 )
  {
    if ( nVal2 )
      g_nSceneState = 1;
  }
  else
  {
    if ( nVal != 1001 )
      return this->UIWnd::OnMessage(nVal, nVal2, nVal3);
    switch ( nVal2 )
    {
      case 1027:
        if ( dword_DBA240 )
        {
          v11 = (const void *)off_5BF000;
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v11, 1);
          PAL3_DispatchModeCommand(2);
          (((PalScriptMgr *)v8))->PalScriptMgr::Destroy();
          return 1;
        }
        break;
      case 1028:
        PAL3_DispatchModeCommand(1);
        v10 = (const void *)off_5BF000;
        v6 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v6))->CScreenMode::AudioSetPosition(v10, 1);
        return 1;
      case 1029:
        PAL3_DispatchModeCommand(2);
        v9 = (const void *)off_5BF000;
        v5 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v5))->CScreenMode::AudioSetPosition(v9, 1);
        return 1;
    }
  }
  return 1;
}
